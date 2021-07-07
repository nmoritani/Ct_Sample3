#include "pthread.h"
#include "pthread_common.h"
#include "pthread_cycle_handler.h"
#include "pthread_semaphore.h"


typedef struct _cycle_obj {
	int             use;
	int             id;
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	bool			active;
	struct timespec starttime;
	struct timespec currenttime;
	cycle_time_arg	arg;
} cycle_obj;

#define	NUM_OF_CYCLE_HANDLER	10

/* global */
pthread_mutex_t g_cycle_mutex;	//メールボックスの生成・破棄用
cycle_obj		g_cycle_obj[NUM_OF_CYCLE_HANDLER];

static int get_index(unsigned int id)
{
	int i;
	for (i = 0; i < ARRAY_NUM(g_cycle_obj); i++) {
		if (!g_cycle_obj[i].use) {
			continue;
		}

		if (g_cycle_obj[i].id == id) {
			return i;
		}
	}
	return -1;
}

static cycle_obj * find_object(int id)
{
	int index = get_index(id);
	if ((index < 0) || (NUM_OF_CYCLE_HANDLER <= index)) {
		return NULL;
	}
	return &g_cycle_obj[index];
}


int init_cyclehandler_table()
{
	unsigned int i;

	init_mutex(&g_cycle_mutex);
	for (i = 0; i < ARRAY_NUM(g_cycle_obj); i++) {
		ZERO_CLEAR(g_cycle_obj[i]);
	}

	return ERR_OK;
}


static void create_object(int index, int id, const cycle_time_arg *arg)
{
	g_cycle_obj[index].use = true;
	g_cycle_obj[index].id = id;

	init_mutex(&(g_cycle_obj[index].mutex));
	pthread_cond_init(&(g_cycle_obj[index].cond), NULL);

	g_cycle_obj[index].arg = *arg;

	if (arg->attr & CYC_ATTR_FLG_CRE_WITH_STAT) {
		get_currentTimer(&g_cycle_obj[index].starttime);
		g_cycle_obj[index].active = true;
	} else {
		g_cycle_obj[index].active = false;
	}
}



int create_cycle_handler(unsigned int id, const cycle_time_arg *arg)
{
	unsigned int i;
	int   errcode = ERR_NOEXS;

	pthread_mutex_lock(&g_cycle_mutex);

	cycle_obj *obj = find_object(id);
	if (NULL != obj) {
		//既に作成されている場合
		return ERR_OBJ;
	}

	for (i = 0; i < ARRAY_NUM(g_cycle_obj); i++) {
		if (g_cycle_obj[i].use) {
			/*使用済みのIDは飛ばす*/
			continue;
		}

		create_object(i, id, arg);

		errcode = ERR_OK;
		break;
	}

	pthread_mutex_unlock(&g_cycle_mutex);

	return errcode;
}

int delete_cycle_handler(unsigned int id)
{
	int ercd;

	cycle_obj *obj = find_object(id);
	if (NULL == obj) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&g_cycle_mutex);

	obj->active = false;

	if (false == obj->use) {
		ercd = ERR_PAR;
	} else if (pthread_mutex_destroy(&(obj->mutex)) != 0) {
		ercd = ERR_SYS;
	} else if (pthread_cond_destroy(&(obj->cond)) != 0) {
		ercd = ERR_SYS;
	} else {
		ZERO_CLEAR(*obj);
		ercd = ERR_OK;
	}

	pthread_mutex_unlock(&g_cycle_mutex);

	return ercd;
}


int stop_cycle_handler(unsigned int id)
{
	return active_cycle_handler(id, false, false);
}


int active_cycle_handler(unsigned int id, bool act, bool init)
{
	cycle_obj *obj = find_object(id);
	if (NULL == obj) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&(obj->mutex));
	obj->active = act;
	get_currentTimer(&obj->starttime);
	pthread_mutex_unlock(&(obj->mutex));

	return ERR_OK;
}

int start_cycle_handler(unsigned int id)
{
	return active_cycle_handler(id, true, false);
}


int thread_cycletimer()
{
	int i;
	struct timespec currenttime;

	for (i = 0; i < ARRAY_NUM(g_cycle_obj); i++) {
		cycle_obj *p = &g_cycle_obj[i];

		if (!p->use) {
			continue;
		}

		if (!p->active) {
			continue;
		}

		if (Is_msec_timeout(&p->starttime, p->arg.cycle_time, &currenttime)) {
			p->arg.func();

			// 開始時刻を保存
			pthread_mutex_lock(&(p->mutex));
			p->starttime = currenttime;
			pthread_mutex_unlock(&(p->mutex));
		}
	}
	return ERR_OK;
}

int reference_cycle_handler(unsigned int id, cycle_handler_state *pk_rcyc)
{
	long elapsed_time, cycle_time;

	cycle_obj *obj = find_object(id);
	if (NULL == obj) {
		return ERR_PAR;
	}

	//タイマが活性状態ではなかったら即return
	if (!obj->active) {
		pk_rcyc->active = false;
		pk_rcyc->remain_time = obj->arg.cycle_time;
		return ERR_OK;
	}

	elapsed_time = get_elapsed_time_msec(&obj->starttime);
	cycle_time = obj->arg.cycle_time;

	//! 起動時刻までの時間を計算する
	pk_rcyc->remain_time = (cycle_time <= elapsed_time) ? 0 : cycle_time - elapsed_time;

	return ERR_OK;
}

