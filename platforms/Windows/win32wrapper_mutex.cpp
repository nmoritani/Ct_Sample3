/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: system_wrapper.h
 */

#include "win32wrapper_common.h"

#ifdef SYSTEM_WINDOWS

typedef struct {
	BOOL			use;
	HANDLE			h_mutex;
} mutex_info_t;

mutex_info_t	mutex_info_list[NUM_OF_MUTEX] = {0};

SYSWRAP_ERROR syswrap_mutex_init()
{
	ZERO_CLEAR(mutex_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_mutex_term()
{
	ZERO_CLEAR(mutex_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_create_mutex(syswrap_mutex_t *mutex)
{
	unsigned int i;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_PAR;

	if (mutex == NULL)
		return errcode;

	lock_common_mutex(41);
	
	for (i = 0; i < NUM_OF_MUTEX; i++) {
		if (mutex_info_list[i].use == TRUE)
			continue;

		/*新規ミューテックス作成*/
		mutex_info_list[i].use = TRUE;
		mutex_info_list[i].h_mutex = CreateMutex(NULL, FALSE, NULL);
		
		mutex->sysinfo = &mutex_info_list[i];
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	unlock_common_mutex();
	return errcode;
}

SYSWRAP_ERROR syswrap_destroy_mutex(syswrap_mutex_t *mutex)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(42);
	mutex_info_t *mutex_info = (mutex_info_t*)mutex->sysinfo;

	if (mutex_info->h_mutex != NULL)
		CloseHandle(mutex_info->h_mutex);

	ZERO_CLEAR(*mutex_info);
	mutex->sysinfo = NULL;

	unlock_common_mutex();
	return errcode;
}

SYSWRAP_ERROR syswrap_lock_mutex(syswrap_mutex_t *mutex, long timeout)
{
	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	mutex_info_t *mutex_info = (mutex_info_t*)mutex->sysinfo;
	if (mutex_info->h_mutex != NULL) {
		WaitForSingleObject(mutex_info->h_mutex, timeout);
	} else {
		return SYSWRAP_ERR_SYS;
	}
	
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_unlock_mutex(syswrap_mutex_t *mutex)
{
	if ((mutex == NULL) || (mutex->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	mutex_info_t *mutex_info = (mutex_info_t*)mutex->sysinfo;
	if (mutex_info->h_mutex != NULL) {
		ReleaseMutex(mutex_info->h_mutex);
	} else {
		return SYSWRAP_ERR_SYS;
	}
	return SYSWRAP_ERR_OK;
}

#endif

