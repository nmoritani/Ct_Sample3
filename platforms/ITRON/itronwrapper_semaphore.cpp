#include "itronwrapper_common.h"

#ifdef SYSTEM_ITRON

SYSWRAP_ERROR syswrap_create_semaphore(syswrap_semaphore_t *semaphore, unsigned int count, THREAD_ATTR thread_attribute)
{
	T_CSEM csem = {0};

	if (semaphore == NULL)
		return SYSWRAP_ERR_PAR;
	
	csem.sematr = TA_TFIFO;
	csem.isemcnt = count;
	csem.maxsem = count;

	if (semaphore->id == 0) {
		if ((semaphore->id = acre_sem(&csem)) <= 0)
			return SYSWRAP_ERR_SYS;

	} else {
		if (cre_sem(semaphore->id, &csem) != E_OK)
			return SYSWRAP_ERR_SYS;
	}

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_destroy_semaphore(syswrap_semaphore_t *semaphore)
{
	if (semaphore == NULL)
		return SYSWRAP_ERR_PAR;

	if (semaphore->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (del_sem(semaphore->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_post_semaphore(syswrap_semaphore_t *semaphore)
{
	if (semaphore == NULL)
		return SYSWRAP_ERR_PAR;

	if (semaphore->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (sig_sem(semaphore->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_wait_semaphore(syswrap_semaphore_t *semaphore, long timeout)
{
	if (semaphore == NULL)
		return SYSWRAP_ERR_PAR;

	if (semaphore->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (wai_sem(semaphore->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

#endif
