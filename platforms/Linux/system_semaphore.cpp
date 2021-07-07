#include "system_common.h"
#include "system_wrapper.h"
#include <semaphore.h>

typedef struct {
	int             use;
	sem_t 			semaphore;
} semaphore_info_t;

pthread_mutex_t 	mutex;	//mutexリストの生成・破棄用
semaphore_info_t	info_list[NUM_OF_SEMAPHORE];

SYSWRAP_ERROR syswrap_semaphore_initial()
{
	ZERO_CLEAR(info_list);
	for (int i = 0; i < NUM_OF_SEMAPHORE; i++) {
		info_list[i].use = false;
	}

	mutex_init(&mutex);
	
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_create_semaphore(syswrap_semaphore_t *semaphore, unsigned int count)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_PAR;

	if (semaphore == NULL)
		return errcode;

	pthread_mutex_lock(&mutex);
	
	for (int i = 0; i < NUM_OF_SEMAPHORE; i++) {
		if (info_list[i].use)
			continue;

		if (sem_init(&info_list[i].semaphore, 0, count) == -1) {
			errcode = SYSWRAP_ERR_SYS;
			break;
		}
		errcode = SYSWRAP_ERR_OK;
		semaphore->sysinfo = &info_list[i];
		break;
	}
	
	pthread_mutex_unlock(&mutex);
	return errcode;
}

SYSWRAP_ERROR delete_semaphore(syswrap_semaphore_t *semaphore)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;
	
	pthread_mutex_lock(&mutex);

	semaphore_info_t *info = (semaphore_info_t *)semaphore->sysinfo;
	
	if (false == info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	if (sem_destroy(&(info->semaphore)) != 0) 
		errcode = SYSWRAP_ERR_SYS;
	
	ZERO_CLEAR(*info);
	info->use = false;
	semaphore->sysinfo = NULL;

	pthread_mutex_unlock(&mutex);
	
	return errcode;
}

SYSWRAP_ERROR syswrap_wait_semaphore(syswrap_semaphore_t *semaphore)
{
	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	semaphore_info_t *info = (semaphore_info_t *)semaphore->sysinfo;
	
	int result = sem_wait(&info->semaphore);
	return	(0 == result) ? SYSWRAP_ERR_OK : SYSWRAP_ERR_PAR;
}

SYSWRAP_ERROR signal_semaphore(syswrap_semaphore_t *semaphore)
{
	if ((semaphore == NULL) || (semaphore->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	semaphore_info_t *info = (semaphore_info_t *)semaphore->sysinfo;

	int result = sem_post(&info->semaphore);
	return	(0 == result) ? SYSWRAP_ERR_OK : SYSWRAP_ERR_PAR;
}

