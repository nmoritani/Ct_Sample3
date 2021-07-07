/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: system_wrapper.h
 */

#include "system_common.h"

typedef struct {
	BOOL			use;
	THREAD_ATTR		thread_attribute;
	thread_info_t	*thread_queue;
	
	unsigned int	locked_thread;

} mutex_info_t;

mutex_info_t	info_list[NUM_OF_MUTEX];

SYSWRAP_ERROR syswrap_mutex_initial()
{
	ZERO_CLEAR(info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_create_mutex(syswrap_mutex_t *mutex, THREAD_ATTR thread_attribute)
{
	unsigned int i;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_PAR;

	if (mutex == NULL)
		return errcode;
	
	for (i = 0; i < NUM_OF_MUTEX; i++) {
		if (info_list[i].use == TRUE)
			continue;

		/*新規ミューテックス作成*/
		info_list[i].use = TRUE;
		info_list[i].thread_attribute = thread_attribute;
		info_list[i].thread_queue = NULL;
		info_list[i].locked_thread = 0;
		
		mutex->sysinfo = &info_list[i];
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	return errcode;
}

SYSWRAP_ERROR syswrap_delete_mutex(syswrap_mutex_t *mutex)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	mutex_info_t *mutex_info = (mutex_info_t*)mutex->sysinfo;
	
	if (false == mutex_info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	ZERO_CLEAR(*mutex_info);
	mutex->sysinfo = NULL;

	return errcode;
}

SYSWRAP_ERROR syswrap_lock_mutex(syswrap_mutex_t *mutex, long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	int	thread_id = 0;

	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	mutex_info_t *mutex_info = (mutex_info_t*)mutex->sysinfo;

	syswrap_get_threadid(&thread_id);
	if (thread_id == 0)
		return SYSWRAP_ERR_CTX;

	if (mutex_info->locked_thread == 0) {
		mutex_info->locked_thread = thread_id;
		return SYSWRAP_ERR_OK;
	}

	thread_info_t *thread_info = NULL;

	if ((thread_info = get_current_thread()) == NULL)
		return SYSWRAP_ERR_CTX;
	
	if ((errcode = wait_thread(thread_info, WAIT_TYPE_MUTEX, mutex_info->thread_attribute, timeout, &mutex_info->thread_queue)) == SYSWRAP_ERR_OK) {
		mutex_info->locked_thread = thread_id;
	}

	return errcode;
}

SYSWRAP_ERROR syswrap_unlock_mutex(syswrap_mutex_t *mutex)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	int	thread_id = 0;
	
	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	mutex_info_t *mutex_info = (mutex_info_t*)mutex->sysinfo;

	syswrap_get_threadid(&thread_id);
	if (mutex_info->locked_thread != thread_id) {
		return SYSWRAP_ERR_ILLIGALUSE;
	}

	mutex_info->locked_thread = 0;

	if (mutex_info->thread_queue) {
		errcode = wakeup_thread(mutex_info->thread_queue, WAIT_TYPE_MUTEX, &mutex_info->thread_queue);
	}
	
	return errcode;
}
