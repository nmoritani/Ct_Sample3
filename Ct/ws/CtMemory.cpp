#include <CtPlatforms.h>

#include "CtMemory.h"

#include "CtDebugPrint.h"

static unsigned int error = 0;

void* CtMemory::get(size_t Size)
{
	void *mem = NULL;
	
	if (syswrap_alloc_memory(&ct_mempool_normal, &mem, Size) != SYSWRAP_ERR_OK) {
		error = 1;
		return NULL;
	}
	return mem;
}

void CtMemory::free(void* ptr)
{
	SYSWRAP_ERROR er = syswrap_free_memory(&ct_mempool_normal, ptr);
}

