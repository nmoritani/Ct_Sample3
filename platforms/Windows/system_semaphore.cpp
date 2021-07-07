#include "system_common.h"

typedef struct {
	BOOL			use;
	THREAD_ATTR		thread_attribute;
	thread_info_t	*thread_queue;
	
	unsigned int	max_count;
	unsigned int	count;
} semaphore_info_t;

static semaphore_info_t	info_list[NUM_OF_SEMAPHORE];

SYSWRAP_ERROR syswrap_semaphore_initial()
{
	ZERO_CLEAR(info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_create_semaphore(syswrap_semaphore_t *semaphore, unsigned int count, THREAD_ATTR thread_attribute)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((semaphore == NULL) || (count <= 0))
		return SYSWRAP_ERR_PAR;

	for (int i = 0; i < NUM_OF_SEMAPHORE; i++) {
		if (info_list[i].use)
			continue;

		info_list[i].use = TRUE;
		info_list[i].thread_queue = NULL;
		info_list[i].thread_attribute = thread_attribute;
		info_list[i].max_count = count;
		semaphore->sysinfo = &info_list[i];

		errcode = SYSWRAP_ERR_OK;
		break;
	}
	
	return errcode;
}

SYSWRAP_ERROR delete_semaphore(syswrap_semaphore_t *semaphore)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;
	
	semaphore_info_t *semaphore_info = (semaphore_info_t *)semaphore->sysinfo;
	
	if (false == semaphore_info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	ZERO_CLEAR(*semaphore_info);
	semaphore_info->use = false;
	semaphore->sysinfo = NULL;

	return errcode;
}

SYSWRAP_ERROR signal_semaphore(syswrap_semaphore_t *semaphore)
{
	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	semaphore_info_t *semaphore_info = (semaphore_info_t *)semaphore->sysinfo;

	if (semaphore_info->count < semaphore_info->max_count) {
		semaphore_info->count++;
	}
	if (semaphore_info->thread_queue) {
		wakeup_thread(semaphore_info->thread_queue, WAIT_TYPE_SEMAPHORE, &semaphore_info->thread_queue);
	}
	
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_wait_semaphore(syswrap_semaphore_t *semaphore, long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	
	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	semaphore_info_t *semaphore_info = (semaphore_info_t *)semaphore->sysinfo;

	if ((semaphore_info->thread_queue == NULL) && (semaphore_info->count > 0)) {
		semaphore_info->count--;
		SYSWRAP_ERR_OK;
	}

	thread_info_t *thread_info = NULL;

	if ((thread_info = get_current_thread()) == NULL)
		return SYSWRAP_ERR_CTX;
	
	errcode = wait_thread(thread_info, WAIT_TYPE_SEMAPHORE, semaphore_info->thread_attribute, timeout, &semaphore_info->thread_queue);

	if (errcode == SYSWRAP_ERR_OK) {
		if (semaphore_info->count > 0) {
			semaphore_info->count--;
		} else {
			return SYSWRAP_ERR_TIMEOUT;
		}
	}
	
	return errcode;
}

