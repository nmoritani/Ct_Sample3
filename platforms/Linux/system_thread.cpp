#include "system_common.h"
#include "system_wrapper.h"

typedef enum thread_state {
	thread_state_domant = 0,	// 休止中
	thread_state_suspend,		// 強制待ち状態
	thread_state_wait,			// 待ち状態
	thread_state_ready,			// 実行可能状態
	thread_state_run,			// 実行状態
	thread_state_max
} THREAD_STATE;

typedef struct {
	objlink_t		*head;
	int             use;
	int				priority;
	THREAD_STATE	state;
	int				stack_size;
	THREAD_FUNC		*pfunc;
	
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	pthread_t		tid;
	int				active_count;
} thread_info_t;

/* global */
pthread_mutex_t		mutex;			// スレッド生成・破棄用
thread_info_t		info_list[NUM_OF_THREAD];

SYSWRAP_ERROR syswrap_thread_initial()
{
	mutex_init(&mutex);

	ZERO_CLEAR(info_list);

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_thread(syswrap_thread_t *thread, THREAD_FUNC func, unsigned int stack_size, int pri)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	int i;

	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	pthread_mutex_lock(&mutex);

	for (i = 0; i < NUM_OF_THREAD; i++) {
		if (info_list[i].use) {
			continue;
		}

		info_list[i].use = true;

		mutex_init(&info_list[i].mutex);
		pthread_cond_init(&info_list[i].cond, NULL);

		info_list[i].tid = 0;
		info_list[i].state = thread_state_idle;
		info_list[i].priority = pri;
		info_list[i].stack_size = stack_size;
		info_list[i].pfunc = func;
		thread->sysinfo = &info_list[i];
		
		errcode = SYSWRAP_ERR_OK;
		break;
	}
	if (i >= NUM_OF_THREAD)
		errcode = SYSWRAP_ERR_RESOVER;

	pthread_mutex_unlock(&mutex);
	return errcode;
}


SYSWRAP_ERROR syswrap_delete_thread(syswrap_thread_t *thread)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;


	thread_info_t *info = (thread_info_t *)thread->sysinfo;
	
	pthread_cancel(info->tid);
	pthread_join(info->tid, NULL);

	pthread_mutex_lock(&mutex);

	if (false == info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	if (pthread_mutex_destroy(&(info->mutex)) != 0)
		errcode = SYSWRAP_ERR_SYS;
	
	if (pthread_cond_destroy(&(info->cond)) != 0)
		errcode = SYSWRAP_ERR_SYS;
	
	ZERO_CLEAR(info);
	thread->sysinfo = NULL;

	pthread_mutex_unlock(&mutex);
	
	return errcode;
}


SYSWRAP_ERROR syswrap_get_threadid(int *tid)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	pthread_t active_tid = pthread_self();
	int id = -1;

	for (int i = 0; i < NUM_OF_THREAD; i++) {
		if (0 != pthread_equal(info_list[i].tid, active_tid)) {
			id = info_list[i].tid;
			break;
		}
	}
	if (id < 0) {
		errcode = SYSWRAP_ERR_RESOVER;
		*tid = 0;
	} else {
		*tid = id;	//生成時のタスクIDを返す
	}
	
	return errcode;
}

SYSWRAP_ERROR syswrap_start_thread(syswrap_thread_t *thread)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	pthread_attr_t th_att;
	struct sched_param scp;

	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;
	
	thread_info_t *info = (thread_info_t *)thread->sysinfo;
	
	if (thread_state_active == info->state) {
		return SYSWRAP_ERR_OK;
	}

	scp.sched_priority = (99 - info->priority);
	pthread_attr_init(&th_att);
	pthread_attr_setschedpolicy(&th_att, SCHED_FIFO);
	pthread_attr_setschedparam(&th_att, &scp);

	// スレッドを起動する
	if (pthread_create(&info->tid, &th_att, info->pfunc, NULL) == 0) {
		info->state = thread_state_active;
	}  else {
		errcode = SYSWRAP_ERR_SYS;
	}

	return errcode;
}

SYSWRAP_ERROR syswrap_delay_thread(long timeout)
{
	syswrap_timeval_t tv;
	struct timespec to;
	
	int ret;
	SYSWRAP_ERROR  errcode = SYSWRAP_ERR_OK;
	pthread_t active_tid = pthread_self();
	thread_info_t *info = NULL;

	for (int i = 0; i < NUM_OF_THREAD; i++) {
		if (0 != pthread_equal(info_list[i].tid, active_tid)) {
			info = &info_list[i];
			break;
		}
	}
	if (info == NULL)
		return SYSWRAP_ERR_RESOVER;

	pthread_mutex_lock(&(info->mutex));

	syswrap_get_time(&tv);
	syswrap_add_time_ms(&tv, ms_time);
	to.tv_sec = tv.tv_sec;
	to.tv_nsec = tv.tv_usec * 1000;

	while (1) {
		ret = pthread_cond_timedwait(&(info->cond), &(info->mutex), &to);
		if (ETIMEDOUT == ret) {
			errcode = SYSWRAP_ERR_TMOUT;
			break;
		} else if (EINTR == ret) {
			/* continue (check ring buffer) */
		} else if (0 != ret) {
			errcode = SYSWRAP_ERR_SYS;
			break;
		} else {
			/* continue (check ring buffer) */
		}
	}

	pthread_mutex_unlock(&(info->mutex));
	if (errcode == SYSWRAP_ERR_TMOUT) {
		errcode = SYSWRAP_ERR_OK;
	}
	return errcode;
}

SYSWRAP_ERROR syswrap_wait_thread(syswrap_thread_t *thread, unsigned int type, long timeout, int pri, thread_link_t *list)
{
	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	if (timeout == TIMEOUT_POLLING)
		return SYSWRAP_ERR_PAR;

	if 

	
}


SYSWRAP_ERROR syswrap_stop_thread(syswrap_thread_t *thread)
{
	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	thread_info_t *info = (thread_info_t *)thread->sysinfo;
	
	pthread_join(info->tid, NULL);
	
	return SYSWRAP_ERR_OK;
}


