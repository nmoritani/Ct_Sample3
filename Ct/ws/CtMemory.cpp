#include "CtMemory.h"

#include "kernel.h"
#include "kernel_id.h"
#include "CtDebugPrint.h"

static unsigned int error = 0;

void* CtMemory::get(size_t Size)
{
	void *mem = NULL;
	
	if (tget_mpl(CT_MPL_ID, (UINT)Size, &mem, 500) != E_OK) {
		error = 1;
		return NULL;
	}
	return mem;
}

void CtMemory::free(void* ptr)
{
	ER er = rel_mpl(CT_MPL_ID, ptr);
}

