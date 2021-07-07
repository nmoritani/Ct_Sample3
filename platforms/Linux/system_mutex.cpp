/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: system_wrapper.h
 */

#include "system_common.h"
#include "system_wrapper.h"

typedef struct {
	int             use;
	pthread_mutex_t mutex;
} mutex_info_t;

pthread_mutex_t _mutex;	//mutexリストの生成・破棄用
mutex_info_t	_info_list[NUM_OF_MUTEX];

SYSWRAP_ERROR syswrap_mutex_initial()
{
	ZERO_CLEAR(_info_list);
	for (int i = 0; i < NUM_OF_MUTEX; i++) {
		_info_list[i].use = false;
	}

	mutex_init(&_mutex);
	
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_create_mutex(syswrap_mutex_t *mutex)
{
	unsigned int i;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_PAR;

	if (mutex == NULL)
		return errcode;
	
	pthread_mutex_lock(&_mutex);

	for (i = 0; i < NUM_OF_MUTEX; i++) {
		if (_info_list[i].use == true)
			continue;

		/*新規ミューテックス作成*/
		_info_list[i].use = true;

		mutex_init(&_info_list[i].mutex);
		mutex->sysinfo = &_info_list[i];
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	pthread_mutex_unlock(&_mutex);
	return errcode;
}

SYSWRAP_ERROR syswrap_delete_mutex(syswrap_mutex_t *mutex)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	mutex_info_t *info = (mutex_info_t*)mutex->sysinfo;
	
	pthread_mutex_lock(&_mutex);

	if (false == info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	if (pthread_mutex_destroy(&(info->mutex)) != 0) 
		errcode = SYSWRAP_ERR_SYS;
	
	ZERO_CLEAR(*info);
	info->use = false;
	mutex->sysinfo = NULL;

	pthread_mutex_unlock(&_mutex);
	return errcode;
}

SYSWRAP_ERROR syswrap_lock_mutex(syswrap_mutex_t *mutex)
{
	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	mutex_info_t *info = (mutex_info_t*)mutex->sysinfo;
	
	int result = pthread_mutex_lock(&(info->mutex));
	return	(0 == result) ? SYSWRAP_ERR_OK : SYSWRAP_ERR_PAR;
}

SYSWRAP_ERROR syswrap_unlock_mutex(syswrap_mutex_t *mutex)
{
	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	mutex_info_t *info = (mutex_info_t*)mutex->sysinfo;
	
	int result = pthread_mutex_unlock(&(info->mutex));
	return	(0 == result) ? SYSWRAP_ERR_OK : SYSWRAP_ERR_PAR;
}
