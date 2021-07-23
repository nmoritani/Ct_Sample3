/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: system_wrapper.h
 */

#include "itronwrapper_common.h"

#ifdef SYSTEM_ITRON

SYSWRAP_ERROR syswrap_create_mutex(syswrap_mutex_t *mutex, THREAD_ATTR thread_attribute)
{
	T_CMTX cmtx = {0};

	if (mutex == NULL)
		return SYSWRAP_ERR_PAR;

	cmtx.mtxatr = TA_TFIFO;
	cmtx.ceilpri = 0;

	if (mutex->id == 0) {
		if ((mutex->id = acre_mtx(&cmtx)) <= 0)
			return SYSWRAP_ERR_SYS;

	} else {
		if (cre_mtx(mutex->id, &cmtx) != E_OK)
			return SYSWRAP_ERR_SYS;
	}

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_destroy_mutex(syswrap_mutex_t *mutex)
{
	if (mutex == NULL)
		return SYSWRAP_ERR_PAR;

	if (mutex->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (del_mtx(mutex->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_lock_mutex(syswrap_mutex_t *mutex, long timeout)
{
	if (mutex == NULL)
		return SYSWRAP_ERR_PAR;

	if (mutex->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (loc_mtx(mutex->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_unlock_mutex(syswrap_mutex_t *mutex)
{
	if (mutex == NULL)
		return SYSWRAP_ERR_PAR;

	if (mutex->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (unl_mtx(mutex->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

#endif
