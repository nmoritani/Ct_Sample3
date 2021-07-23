#include "itronwrapper_common.h"
#include <stdlib.h>

#ifdef SYSTEM_ITRON

SYSWRAP_ERROR syswrap_create_memorypool(syswrap_memorypool_t *mempool, int size, int align_size, void *addr)
{
	T_CMPL cmpl = {0};

	if (mempool == NULL)
		return SYSWRAP_ERR_PAR;
	
	cmpl.mplatr = TA_TFIFO;
	cmpl.mplsz = size;
	cmpl.mpl = addr;

	if (mempool->id == 0) {
		if ((mempool->id = acre_mpl(&cmpl)) <=0)
			return SYSWRAP_ERR_SYS;
		
	} else {
		if (cre_mpl(mempool->id, &cmpl) != E_OK)
			return SYSWRAP_ERR_SYS;
	}
	
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_destroy_memorypool(syswrap_memorypool_t *mempool)
{
	if (mempool == NULL)
		return SYSWRAP_ERR_PAR;

	if (mempool->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (del_mpl(mempool->id) != E_OK)
		return SYSWRAP_ERR_SYS;
	
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_alloc_memory(syswrap_memorypool_t *mempool, void **dst, int size)
{
	if (mempool == NULL)
		return SYSWRAP_ERR_PAR;

	if (mempool->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (get_mpl(mempool->id, size, dst) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_free_memory(syswrap_memorypool_t *mempool, void* dst)
{
	if (mempool == NULL)
		return SYSWRAP_ERR_PAR;

	if (mempool->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (rel_mpl(mempool->id, dst) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

#endif
