#include "itronwrapper_common.h"

#ifdef SYSTEM_ITRON

SYSWRAP_ERROR syswrap_create_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, FUNC func, int cycletime)
{
	T_CCYC ccyc = {0};
	ID id = 0;

	if (cyclic_handler == NULL)
		return SYSWRAP_ERR_PAR;

	ccyc.cycatr = TA_HLNG;
	ccyc.exinf = 0;
	ccyc.cychdr = func;
	ccyc.cyctim.utime = 0;
	ccyc.cyctim.ltime = cycletime;
	ccyc.cycphs.utime = 0;
	ccyc.cycphs.ltime = 0;

	if (cyclic_handler->id == 0) {
		if ((cyclic_handler->id = acre_cyc(&ccyc)) <= 0)
			return SYSWRAP_ERR_SYS;
		
	} else {
		if (cre_cyc(cyclic_handler->id, &ccyc) != E_OK)
			return SYSWRAP_ERR_SYS;
	}

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_destroy_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	if (cyclic_handler == NULL)
		return SYSWRAP_ERR_PAR;

	if (cyclic_handler->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (del_cyc(cyclic_handler->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_stop_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	if (cyclic_handler == NULL)
		return SYSWRAP_ERR_PAR;

	if (cyclic_handler->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (stp_cyc(cyclic_handler->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_start_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	if (cyclic_handler == NULL)
		return SYSWRAP_ERR_PAR;

	if (cyclic_handler->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (sta_cyc(cyclic_handler->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

#endif
