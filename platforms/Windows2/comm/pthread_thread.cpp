#include "pthread_thread.h"
#include "pthread_semaphore.h"

typedef enum thread_state {
	thread_state_idle = 0,
	thread_state_active,
	thread_state_max
} THREAD_STATE;

typedef struct _thread_obj {
	int             use;
	int             id;
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	pthread_t		tid;
	thread_arg		arg;
	THREAD_STATE	state;
	int				active_count;
} thread_obj;

/* global */
pthread_mutex_t		g_thread_mutex;			// スレッド生成・破棄用
thread_obj			g_thread[NUM_OF_THREAD];

static int get_thread_index(unsigned int id)
{
	int i;
	for (i = 0; i < ARRAY_NUM(g_thread); i++) {
		if (!g_thread[i].use) {
			continue;
		}

		if (g_thread[i].id == id) {
			return i;
		}
	}
	return -1;
}


static thread_obj * find_object(int id)
{
	int index = get_thread_index(id);
	if ((index < 0) || (NUM_OF_THREAD <= index)) {
		return NULL;
	}
	return &g_thread[index];
}


static void create_object(int index, int id, const thread_arg *pk_ctsk)
{
	g_thread[index].use = true;
	g_thread[index].id = id;

	init_mutex(&(g_thread[index].mutex));
	pthread_cond_init(&(g_thread[index].cond), NULL);

	memcpy(&g_thread[index].arg, pk_ctsk, sizeof(thread_arg));
}


int init_thread_table()
{
	unsigned int i;

	init_mutex(&g_thread_mutex);
	for (i = 0; i < ARRAY_NUM(g_thread); i++) {
		ZERO_CLEAR(g_thread[i]);
	}

	return ERR_OK;
}


int create_thread(unsigned int id, const thread_arg *pk_ctsk)
{
	unsigned int i;
	int   errcode = ERR_NOEXS;

	pthread_mutex_lock(&g_thread_mutex);

	thread_obj *obj = find_object(id);
	if (NULL != obj) {
		//既に作成されている場合
		return ERR_OBJ;
	}

	for (i = 0; i < ARRAY_NUM(g_thread); i++) {
		if (g_thread[i].use) {
			/*使用済みのIDは飛ばす*/
			continue;
		}

		/*新規スレッド用のオブジェクト作成*/
		/*itronの動きと合わせるため、ここではpthread_create()しない*/
		create_object(i, id, pk_ctsk);
		errcode = ERR_OK;
		break;
	}

	pthread_mutex_unlock(&g_thread_mutex);
	return errcode;
}


int delete_thread(unsigned int id)
{
	int ercd;

	thread_obj *obj = find_object(id);
	if (NULL == obj) {
		return ERR_PAR;
	}

	pthread_cancel(obj->tid);
	pthread_join(obj->tid, NULL);

	pthread_mutex_lock(&g_thread_mutex);

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

	pthread_mutex_unlock(&g_thread_mutex);
	return ercd;
}


int get_thread_id(int *p_tid)
{
	int i;
	pthread_t active_tid = pthread_self();
	unsigned int id = 0;

	for (i = 0; i < ARRAY_NUM(g_thread); i++) {
		if (0 != pthread_equal(g_thread[i].tid, active_tid)) {
			id = g_thread[i].id;
			break;
		}
	}

	*p_tid = id;	//生成時のタスクIDを返す
	return ERR_OK;
}


static int thread_startup(thread_obj *obj)
{
	int policy;
	pthread_attr_t th_att;
	struct sched_param scp;
	int ercd;

	// スレッドの優先度を設定する
	scp.sched_priority = (99 - obj->arg.itskpri);
	policy = SCHED_FIFO;
	pthread_attr_init(&th_att);
	pthread_attr_setschedpolicy(&th_att, SCHED_FIFO);
	pthread_attr_setschedparam(&th_att, &scp);

	// スレッドを起動する
	ercd = pthread_create(&obj->tid, &th_att, obj->arg.task, NULL);
	if (ERR_OK == ercd) {
		obj->state = thread_state_active;
	}
	return ercd;
}


static int thread_start_from_obj(unsigned int id, bool exist_stcd)
{
	int ercd;

	thread_obj *obj = find_object(id);
	if (NULL == obj) {
		return ERR_ID;
	}

	//スレッドがすでに起動しているか確認
	{
		if (thread_state_active == obj->state) {
			//! スレッドが起動中の場合
			if (exist_stcd) {
				//sta_tsk()からの呼び出しの場合はエラーにする
				return ERR_OBJ;
			}

			//! act_tsk(),iact_tsk()からの呼び出しの場合は起動要求回数をカウントアップする
			//カウントがTMAX_ACTCNTを超えたらE_QOVRを返す
			if (TMAX_ACTCNT <= obj->active_count) {
				return ERR_QOVR;
			}

			obj->active_count++;
			return ERR_OK;
		}
	}

	//スレッド起動処理
	ercd = thread_startup(obj);
	if (ERR_OK == ercd) {
		obj->state = thread_state_active;
	}
	return ercd;
}


int thread_active(unsigned int id)
{
	return thread_start_from_obj(id, false);
}


int thread_start(unsigned int id, unsigned int stacd)
{
	return thread_start_from_obj(id, true);
}

int thread_delay(long ms_time)
{
	struct timespec ts;
	
	int ret;
	int ercd = ERR_OK;
	int i;
	pthread_t active_tid = pthread_self();
	unsigned int id = 0;
	thread_obj *obj = NULL;

	for (i = 0; i < ARRAY_NUM(g_thread); i++) {
		if (0 != pthread_equal(g_thread[i].tid, active_tid)) {
			obj = &g_thread[i];
			break;
		}
	}

	if (NULL == obj) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&(obj->mutex));

	get_passage_time(&ts, ms_time);

	while (1) {
		ret = pthread_cond_timedwait(&(obj->cond), &(obj->mutex), &ts);
		if (ETIMEDOUT == ret) {
			ercd = ERR_TMOUT;
			break;
		} else if (EINTR == ret) {
			/* continue (check ring buffer) */
		} else if (0 != ret) {
			ercd = ERR_SYS;
			break;
		} else {
			/* continue (check ring buffer) */
		}
	}

	pthread_mutex_unlock(&(obj->mutex));
	if (ercd == ERR_TMOUT) {
		ercd = ERR_OK;
	}
	return ercd;
}

int thread_join(unsigned int id)
{
	thread_obj *obj = find_object(id);
	if (NULL == obj) {
		return ERR_PAR;
	}

	pthread_join(obj->tid, NULL);
	return ERR_OK;
}


