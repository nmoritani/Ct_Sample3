#include "win32wrapper_common.h"

#ifdef SYSTEM_WINDOWS

typedef struct {
	BOOL			use;
	THREAD_ATTR		thread_attribute;
	thread_info_t	*thread_queue;
	HANDLE			mutex;
	
	unsigned int	max_count;
	unsigned int	count;
	BOOL			waiting;
} semaphore_info_t;

semaphore_info_t	semaphore_info_list[NUM_OF_SEMAPHORE] = {0};

SYSWRAP_ERROR syswrap_semaphore_init()
{
	ZERO_CLEAR(semaphore_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_semaphore_term()
{
	ZERO_CLEAR(semaphore_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_create_semaphore(syswrap_semaphore_t *semaphore, unsigned int count, THREAD_ATTR thread_attribute)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((semaphore == NULL) || (count <= 0))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(51);
	
	for (int i = 0; i < NUM_OF_SEMAPHORE; i++) {
		if (semaphore_info_list[i].use)
			continue;

		semaphore_info_list[i].use = TRUE;
		semaphore_info_list[i].thread_queue = NULL;
		semaphore_info_list[i].thread_attribute = thread_attribute;
		semaphore_info_list[i].max_count = count;
		semaphore_info_list[i].count = count;
		semaphore_info_list[i].waiting = FALSE;
		semaphore->sysinfo = &semaphore_info_list[i];

		errcode = SYSWRAP_ERR_OK;
		break;
	}
	
	unlock_common_mutex();
	return errcode;
}

SYSWRAP_ERROR syswrap_destroy_semaphore(syswrap_semaphore_t *semaphore)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;
	
	lock_common_mutex(52);
	semaphore_info_t *semaphore_info = (semaphore_info_t *)semaphore->sysinfo;
	
	if (false == semaphore_info->use)
		errcode = SYSWRAP_ERR_PAR;

	ZERO_CLEAR(*semaphore_info);
	semaphore_info->use = false;
	semaphore->sysinfo = NULL;

	unlock_common_mutex();
	return errcode;
}

SYSWRAP_ERROR syswrap_wait_semaphore(syswrap_semaphore_t *semaphore, long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	
	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(54);

	semaphore_info_t *semaphore_info = (semaphore_info_t *)semaphore->sysinfo;
	thread_info_t *thread_info = NULL;

	if ((thread_info = get_current_thread_info()) == NULL) {
		errcode = SYSWRAP_ERR_CTX;
		goto exit;
	}

	if (semaphore_info->count > 0) {
		if (semaphore_info->waiting != TRUE) {
			semaphore_info->count--;
			errcode = SYSWRAP_ERR_OK;
			goto exit;
		}
	}
	if (timeout == SYSWRAP_TIMEOUT_POLLING) {
		errcode = SYSWRAP_ERR_TIMEOUT;
		goto exit;
	}
	
	if ((timeout == SYSWRAP_TIMEOUT_POLLING) && (semaphore_info->count == 0)) {
		errcode = SYSWRAP_ERR_TIMEOUT;
		goto exit;
	}
	
	semaphore_info->waiting = TRUE;
	
	errcode = wait_thread(thread_info, WAIT_TYPE_SEMAPHORE, semaphore_info->thread_attribute, timeout, &semaphore_info->thread_queue);
	
	semaphore_info->waiting = FALSE;
	if (errcode == SYSWRAP_ERR_OK) {
		if (semaphore_info->count > 0) {
			semaphore_info->count--;
		} else {
			errcode = SYSWRAP_ERR_TIMEOUT;
		}
	}

  exit:
	unlock_common_mutex();
	return errcode;
}

SYSWRAP_ERROR syswrap_post_semaphore(syswrap_semaphore_t *semaphore)
{
	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;
	
	lock_common_mutex(53);
	semaphore_info_t *semaphore_info = (semaphore_info_t *)semaphore->sysinfo;

	if (semaphore_info->count < semaphore_info->max_count) {
		semaphore_info->count++;
	}
	if (semaphore_info->thread_queue) {
		wakeup_thread(semaphore_info->thread_queue, WAIT_TYPE_SEMAPHORE, &semaphore_info->thread_queue);
	}
	
	unlock_common_mutex();
	return SYSWRAP_ERR_OK;
}

int syswrap_get_semaphore_count(syswrap_semaphore_t *semaphore)
{
	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return 0;

	semaphore_info_t *semaphore_info = (semaphore_info_t *)semaphore->sysinfo;

	return semaphore_info->count;
}

#endif

