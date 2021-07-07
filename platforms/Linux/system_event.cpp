#include "system_common.h"
#include "system_wrapper.h"

typedef struct {
	int             use;
	pthread_mutex_t signal_mutex;
	pthread_cond_t  signal_cond;
	pthread_mutex_t wait_mutex;
	pthread_cond_t  wait_cond;
	unsigned int	pattern;
	unsigned int	Attribute;
	unsigned int	init_val;
} event_info_t;

/* global */
pthread_mutex_t 	mutex;
event_info_t		info_list[NUM_OF_EVENTFLAG];

SYSWRAP_ERROR syswrap_event_initial()
{
	ZERO_CLEAR(info_list);
	for (int i = 0; i < NUM_OF_EVENTFLAG; i++) {
		info_list[i].use = false;
	}

	mutex_init(&mutex);
	
	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_event(syswrap_event_t *event, unsigned int attr, unsigned int init_val)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;

	pthread_mutex_lock(&mutex);

	for (int i = 0; i < NUM_OF_EVENTFLAG; i++) {
		if (info_list[i].use == true)
			continue;

		info_list[i].use = true;
		mutex_init(&info_list[i].signal_mutex);
		mutex_init(&info_list[i].wait_mutex);
		pthread_cond_init(&(info_list[i].signal_cond), (const pthread_condattr_t *)NULL);
		pthread_cond_init(&(info_list[i].wait_cond), (const pthread_condattr_t *)NULL);
		
		info_list[i].pattern = init_val;
		info_list[i].Attribute = attr;

		event->sysinfo = &info_list[i];
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	pthread_mutex_unlock(&mutex);
	return errcode;
}


SYSWRAP_ERROR syswrap_delete_eventflag(syswrap_event_t *event)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((event == NULL) || (event->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	event_info_t *info = (event_info_t *)event->sysinfo;
	
	pthread_mutex_lock(&mutex);

	if (false == info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	if (pthread_mutex_destroy(&(info->wait_mutex)) != 0)
		errcode = SYSWRAP_ERR_SYS;
	
	if (pthread_cond_destroy(&(info->wait_cond)) != 0)
		errcode = SYSWRAP_ERR_SYS;

	if (pthread_mutex_destroy(&(info->signal_mutex)) != 0)
		errcode = SYSWRAP_ERR_SYS;
	
	if (pthread_cond_destroy(&(info->signal_cond)) != 0)
		errcode = SYSWRAP_ERR_SYS;

	ZERO_CLEAR(*info);
	event->sysinfo = NULL;

	pthread_mutex_unlock(&mutex);
	
	return errcode;
}


SYSWRAP_ERROR syswrap_set_event(syswrap_event_t *event, unsigned int setptn)
{
	if ((event == NULL) || (event->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	event_info_t *info = (event_info_t *)event->sysinfo;
	
	if (info->pattern & setptn) {
		//既にセット済みだったら送らない
	} else {
		pthread_mutex_lock(&info->signal_mutex);
		info->pattern |= setptn;
		pthread_cond_signal(&info->wait_cond);
		pthread_mutex_unlock(&info->signal_mutex);
	}

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_wait_event(syswrap_event_t *event, unsigned int waiptn, unsigned int wfmode, unsigned int *p_flgptn, long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_PAR;
	bool event_on = false;
	syswrap_timeval_t tv;
	struct timespec to;
	int ret;
	unsigned int flgPtn;

	if ((event == NULL) || (event->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	event_info_t *info = (event_info_t *)event->sysinfo;
	
	pthread_mutex_lock(&info->wait_mutex);
	
	do {
		syswrap_get_time(&tv);
		syswrap_add_time_ms(&tv, (0 < timeout) ? timeout : 10);
		to.tv_sec = tv.tv_sec;
		to.tv_nsec = tv.tv_usec * 1000;
		ret = pthread_cond_timedwait(&info->wait_cond, &info->wait_mutex, &to);
		if (ETIMEDOUT == ret) {
			if (0 < timeout) {
				errcode = SYSWRAP_ERR_TMOUT;
				break;
			}
		} else if (0 != ret) {
			errcode = SYSWRAP_ERR_SYS;
			break;
		}

		flgPtn = info->pattern;

		//! フラグのクリア設定がされている場合はフラグをクリアする.
		if (((wfmode & SYSWRAP_WAITFLAG_CLR) != 0) || ((info->Attribute & SYSWRAP_WAITATTR_FLAGCLEAR) != 0)) {
			info->pattern = 0;
		}

		if (wfmode & SYSWRAP_WAITFLAG_ORW) {
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
			errcode = SYSWRAP_ERR_OK;
			break;
		}
	} while(1);
	
	pthread_mutex_unlock(&info->wait_mutex);

	return errcode;
}


SYSWRAP_ERROR syswrap_clear_event(syswrap_event_t *event, unsigned int clrptn)
{
	if ((event == NULL) || (event->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	event_info_t *info = (event_info_t *)event->sysinfo;
	
	info->pattern &= clrptn;

	return SYSWRAP_ERR_OK;
}

