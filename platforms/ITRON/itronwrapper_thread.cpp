#include "itronwrapper_common.h"

#ifdef SYSTEM_ITRON

static int conv_thread_priority(THREAD_PRIORITY pri)
{
#if 1
	return 120;
#else
	int itron_pri = 0;
	
	switch (pri) {
	case THREAD_PRI_LOWEST:
		itron_pri = 110;
		break;
	case THREAD_PRI_NORMAL_LOW:
		itron_pri = 90;
		break;
	case THREAD_PRI_NORMAL:
		itron_pri = 40;
		break;
	case THREAD_PRI_NORMAL_HIGH:
		itron_pri = 5;
		break;
	case THREAD_PRI_HIGHEST:
		itron_pri = 1;
		break;
	default:
		itron_pri = 40;
		break;
	}
	return itron_pri;
#endif
}

SYSWRAP_ERROR syswrap_create_thread(syswrap_thread_t *thread, FUNC func, unsigned int stack_size, THREAD_PRIORITY pri)
{
	T_CTSK ctsk = {0};

	if (thread == NULL)
		return SYSWRAP_ERR_PAR;
	
	ctsk.tskatr = TA_HLNG;
	ctsk.exinf = NULL;
	ctsk.task = func;
	ctsk.itskpri = conv_thread_priority(pri);
	ctsk.stksz = stack_size;
	ctsk.stk = NULL;

	if (thread->id == 0) {
		if ((thread->id = acre_tsk(&ctsk)) <= 0)
			return SYSWRAP_ERR_SYS;

	} else {	
		if (cre_tsk(thread->id, &ctsk) != E_OK)
			return SYSWRAP_ERR_SYS;
	}
	
	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_destroy_thread(syswrap_thread_t *thread)
{
	if (thread == NULL)
		return SYSWRAP_ERR_PAR;

	if (thread->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (del_tsk(thread->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}


int syswrap_get_threadid(syswrap_thread_t *thread)
{
	if (thread != NULL)
		return thread->id;

	return 0;
}

SYSWRAP_ERROR syswrap_start_thread(syswrap_thread_t *thread)
{
	if (thread == NULL)
		return SYSWRAP_ERR_PAR;

	if (thread->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (act_tsk(thread->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_delay_thread(long timeout)
{
	if (dly_tsk(timeout) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}	
	
SYSWRAP_ERROR syswrap_term_thread(syswrap_thread_t *thread)
{
	if (thread == NULL)
		return SYSWRAP_ERR_PAR;

	if (thread->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (ter_tsk(thread->id) != E_OK)
		return SYSWRAP_ERR_SYS;
	
	return SYSWRAP_ERR_OK;
}

#endif
