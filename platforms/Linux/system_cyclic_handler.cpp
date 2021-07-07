#include "system_common.h"
#include "system_wrapper.h"

typedef struct {
	int             use;
	
	int				active;
	HANDLER_FUNC	*pfunc;
	int				cycletime;
	
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	syswrap_timeval_t prevtime;
} cyclic_info_t;

#define	NUM_OF_CYCLIC_HANDLER	2

pthread_mutex_t 	mutex;
cyclic_info_t		info_list[NUM_OF_CYCLIC_HANDLER];

#define CYCLE_TIME_MS 10

void execute_cyclic_handler(syswrap_timeval_t *curtime)
{
	for (int i = 0; i < NUM_OF_CYCLIC_HANDLER; i++) {
		cyclic_info_t *info = &info_list[i];

		if (info->use == false)
			continue;

		if (info->active == false)
			continue;

		syswrap_timeval_t prev = info->prevtime;
		syswrap_add_time_ms(&prev, info->cycletime);
		if (syswrap_diff_time(&prev, curtime) > 0) {
			info->pfunc();

			// ŠJŽnŽž‚ð•Û‘¶
			pthread_mutex_lock(&(info->mutex));
			info->prevtime = *curtime;
			pthread_mutex_unlock(&(info->mutex));
		}
	}
}

void create_cycle_thread()
{
	syswrap_timeval_t tv;
	struct timespec to;
	int ret;

	pthread_mutex_t mutex;
	pthread_cond_t  cond;

	mutex_init(&mutex);
	pthread_cond_init(&cond, NULL);

	pthread_mutex_lock(&mutex);

	syswrap_get_time(&tv);
	syswrap_add_time_ms(&tv, CYCLE_TIME_MS);

	do {
		to.tv_sec = tv.tv_sec;
		to.tv_nsec = tv.tv_usec * 1000;
		ret = pthread_cond_timedwait(&cond, &mutex, &to);
		if (ETIMEDOUT == ret) {
			
			syswrap_get_time(&tv);
			execute_cyclic_handler(&tv);
			
			syswrap_add_time_ms(&tv, CYCLE_TIME_MS);
		}
		else if (0 != ret) {
			break;
		}
	} while (1);

	pthread_mutex_unlock(&mutex);
}


SYSWRAP_ERROR syswrap_cyclic_handler_initial()
{

	create_cycle_thread();
	
	mutex_init(&mutex);
	
	ZERO_CLEAR(info_list);
	for (int i = 0; i < NUM_OF_CYCLIC_HANDLER; i++) {
		info_list[i].use = false;
	}

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, HANDLER_FUNC *pfunc, int cycletime)
{
	unsigned int i;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;

	if (cyclic_handler == NULL)
		return SYSWRAP_ERR_PAR;

	pthread_mutex_lock(&mutex);

	for (i = 0; i < NUM_OF_CYCLIC_HANDLER; i++) {
		if (info_list[i].use == true)
			continue;

		info_list[i].use = true;
		info_list[i].active = true;
		info_list[i].pfunc = pfunc;
		info_list[i].cycletime = cycletime;
		
		mutex_init(&(info_list[i].mutex));
		pthread_cond_init(&(info_list[i].cond), NULL);
		
		cyclic_handler->sysinfo = &info_list[i];
		break;
	}
	if (i >= NUM_OF_CYCLIC_HANDLER)
		errcode = SYSWRAP_ERR_RESOVER;

	pthread_mutex_unlock(&mutex);

	return errcode;
}

SYSWRAP_ERROR syswrap_delete_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((cyclic_handler == NULL) || (cyclic_handler->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	cyclic_info_t *info = (cyclic_info_t *)cyclic_handler->sysinfo;
	
	pthread_mutex_lock(&mutex);

	if (false == info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	if (pthread_mutex_destroy(&(info->mutex)) != 0)
		errcode = SYSWRAP_ERR_SYS;

	if (pthread_cond_destroy(&(info->cond)) != 0)
		errcode = SYSWRAP_ERR_SYS;
	
	ZERO_CLEAR(*info);
	cyclic_handler->sysinfo = NULL;
	
	pthread_mutex_unlock(&mutex);

	return errcode;
}


static SYSWRAP_ERROR active_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, bool active)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((cyclic_handler == NULL) || (cyclic_handler->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	cyclic_info_t *info = (cyclic_info_t *)cyclic_handler->sysinfo;
	
	pthread_mutex_lock(&(info->mutex));
	info->active = active;
	syswrap_get_time(&info->prevtime);
	pthread_mutex_unlock(&(info->mutex));

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_stop_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	return active_cyclic_handler(cyclic_handler, false);
}


SYSWRAP_ERROR syswrap_start_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	return active_cyclic_handler(cyclic_handler, true);
}


