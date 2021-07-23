#include "itronwrapper_common.h"

#ifdef SYSTEM_ITRON

SYSWRAP_ERROR syswrap_create_event(syswrap_event_t *event, THREAD_ATTR thread_attribute, unsigned int init_value)
{
	T_CFLG cflg = {0};

	if (event == NULL)
		return SYSWRAP_ERR_PAR;
	
	cflg.flgatr = TA_TFIFO|TA_WMUL|TA_CLR;
	cflg.iflgptn = init_value;

	if (event->id == 0) {
		if ((event->id = acre_flg(&cflg)) <= 0)
			return SYSWRAP_ERR_SYS;
		
	} else {
		if (cre_flg(event->id, &cflg) != E_OK)
			return SYSWRAP_ERR_SYS;
	}

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_destroy_event(syswrap_event_t *event)
{
	if (event == NULL)
		return SYSWRAP_ERR_PAR;
	
	if (event->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (del_flg(event->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_set_event(syswrap_event_t *event, unsigned int set_pattern)
{
	if (event == NULL)
		return SYSWRAP_ERR_PAR;

	if (event->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (set_flg(event->id, set_pattern) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_wait_event(syswrap_event_t *event, unsigned int wait_pattern, unsigned int wait_fmode, unsigned int *flag_pattern, long timeout)
{
	MODE wmode = 0;
	
	if (event == NULL)
		return SYSWRAP_ERR_PAR;

	if (event->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (wait_fmode & SYSWRAP_WAITFMODE_ORW)
		wmode |= TWF_ORW;
	if (wait_fmode & SYSWRAP_WAITFMODE_CLEAR)
		wmode |= TWF_CLR;
	
	if (twai_flg(event->id, wait_pattern, wmode, flag_pattern, timeout) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_clear_event(syswrap_event_t *event, unsigned int clrptn)
{
	if (event == NULL)
		return SYSWRAP_ERR_PAR;

	if (event->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (clr_flg(event->id, clrptn) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

#endif
