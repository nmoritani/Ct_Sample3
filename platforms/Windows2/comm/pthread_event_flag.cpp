#include "pthread_common.h"
#include "pthread_event_flag.h"
#include "pthread_semaphore.h"

/* global */
pthread_mutex_t g_eventflag_mutex;	//メールボックスの生成・破棄用
eventflag		g_eventflag[NUM_OF_EVENTFLAG];

static int get_eventflag_index(unsigned int id)
{
	int i;
	for (i = 0; i < ARRAY_NUM(g_eventflag); i++) {
		if (!g_eventflag[i].use) {
			continue;
		}

		if (g_eventflag[i].id == id) {
			return i;
		}
	}
	return -1;
}


static eventflag * find_object(int id)
{
	int index = get_eventflag_index(id);
	if ((index < 0) || (NUM_OF_EVENTFLAG <= index)) {
		return NULL;
	}
	return &g_eventflag[index];
}

static void create_object(int index, int id, unsigned int attr, unsigned int init_val)
{
	g_eventflag[index].use = true;
	g_eventflag[index].id = id;
	init_mutex(&(g_eventflag[index].signal_mutex));
	pthread_cond_init(&(g_eventflag[index].signal_cond), NULL);
	init_mutex(&(g_eventflag[index].wait_mutex));
	pthread_cond_init(&(g_eventflag[index].wait_cond), NULL);

	g_eventflag[index].pattern = init_val;
	g_eventflag[index].Attribute = attr;
}


int init_eventflag_table()
{
	unsigned int i;

	init_mutex(&g_eventflag_mutex);
	for (i = 0; i < ARRAY_NUM(g_eventflag); i++) {
		g_eventflag[i].use = false;
		g_eventflag[i].id = 0;
	}

	return ERR_OK;
}



int pthread_create_eventflag(int id, unsigned int attr, unsigned int init_val)
{
	unsigned int i;
	int   errcode = ERR_NOEXS;

	pthread_mutex_lock(&g_eventflag_mutex);

	eventflag *obj = find_object(id);
	if (NULL != obj) {
		//既に作成されている場合
		return ERR_OBJ;
	}

	for (i = 0; i < ARRAY_NUM(g_eventflag); i++) {
		if (g_eventflag[i].use) {
			/*使用済みのIDは飛ばす*/
			continue;
		}

		/*新規イベントフラグ作成*/
		create_object(i, id, attr, init_val);
		errcode = ERR_OK;
		break;
	}

	pthread_mutex_unlock(&g_eventflag_mutex);
	return errcode;
}


int pthread_delete_eventflag(int id)
{
	int ercd;

	eventflag *obj = find_object(id);
	if (NULL == obj) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&g_eventflag_mutex);

	if (false == obj->use) {
		ercd = ERR_PAR;
	} else if (pthread_mutex_destroy(&(obj->wait_mutex)) != 0) {
		ercd = ERR_SYS;
	} else if (pthread_cond_destroy(&(obj->wait_cond)) != 0) {
		ercd = ERR_SYS;
	} else {
		ZERO_CLEAR(*obj);
		ercd = ERR_OK;
	}

	pthread_mutex_unlock(&g_eventflag_mutex);
	return ercd;
}


int	pthread_event_set_flag(int id, unsigned int setptn)
{
	//! 引数が不正な場合はエラーにする.
	if (setptn == 0) {
		return ERR_PAR;
	}

	eventflag *flag = find_object(id);
	if (NULL == flag) {
		return ERR_PAR;
	}

	if (flag->pattern & setptn) {
		//既にセット済みだったら送らない
	} else {
		pthread_mutex_lock(&flag->signal_mutex);
		flag->pattern |= setptn;
		pthread_cond_signal(&flag->wait_cond);
		pthread_mutex_unlock(&flag->signal_mutex);
	}

	return ERR_OK;
}


int wait_event_flag(int id, unsigned int waiptn, unsigned int wfmode, unsigned int *p_flgptn, long timeout)
{
	bool			event_on = false;
	struct timespec ts;
	int				errcode = ERR_PAR;
	int				ret;
	int				flgPtn;
	//! 引数が不正な場合はエラー
	if ((NULL == p_flgptn) || (0 == waiptn)) {
		return ERR_PAR;
	}

	eventflag *flag = find_object(id);
	if (NULL == flag) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&flag->wait_mutex);
	do {
		get_passage_time(&ts, (0 < timeout) ? timeout : 100);
		ret = pthread_cond_timedwait(&flag->wait_cond, &flag->wait_mutex, &ts);
		if (ETIMEDOUT == ret) {
			if (0 < timeout) {
				errcode = ERR_TMOUT;
				break;
			}
		} else if (0 != ret) {
			errcode = ERR_SYS;
			break;
		}

		flgPtn = flag->pattern;

		//! フラグのクリア設定がされている場合はフラグをクリアする.
		if (((wfmode & TWF_CLR) != 0) || ((flag->Attribute & TA_CLR) != 0)) {
			flag->pattern = 0;
		}

		if (wfmode & TWF_ORW) {
			//! OR待ちの場合、いずれかのビットが一致すれば「イベントあり」にする
			if ((waiptn & flgPtn) != 0) {
				event_on = true;
			}
		} else {
			//! AND待ちの場合、全てのビットが一致すれば「イベントあり」にする
			if ((waiptn & flgPtn) == waiptn) {
				event_on = true;
			}
		}

		if (event_on) {
			//! イベント発生時のフラグパターンを戻り値にセットする.
			*p_flgptn = flgPtn;
			errcode = ERR_OK;
			break;
		}
	} while (1);
	pthread_mutex_unlock(&flag->wait_mutex);

	return	errcode;
}


int pthread_event_t_wait_flag(int flgid, unsigned int waiptn, unsigned int wfmode, unsigned int *p_flgptn, long tmout)
{
	return wait_event_flag(flgid, waiptn, wfmode, p_flgptn, tmout);
}


int pthread_event_wait_flag(int flgid, unsigned int waiptn, unsigned int wfmode, unsigned int *p_flgptn)
{
	return wait_event_flag(flgid, waiptn, wfmode, p_flgptn, TMO_FEVR);
}


int pthread_event_clear_flag(int flgid, unsigned int clrptn)
{
	eventflag *flag = find_object(flgid);
	if (NULL == flag) {
		return ERR_PAR;
	}
	flag->pattern &= clrptn;

	return ERR_OK;
}

