#include "CtObject.h"
#include "CtMplDbg.h"

#include <CtPlatforms.h>

#if !defined(CT_CHECK_DOUBLE_FREE)

void* CtObject::operator new(size_t Size) throw()
{
	void *mem = NULL;
	
	if (syswrap_alloc_memory(&ct_mempool_normal, &mem, Size) != SYSWRAP_ERR_OK) {
		CtDebugPrint(CtDbg, "!!! CT_MPL allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}

	MPLDBG_ADD(mem, Size);
	
	return mem;
}

void* CtObject::operator new[](size_t Size) throw()
{
	void *mem = NULL;

	if (syswrap_alloc_memory(&ct_mempool_normal, &mem, Size) != SYSWRAP_ERR_OK) {
		CtDebugPrint(CtDbg, "!!! allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}
	
	CtDebugPrint(CtDbg, "getMPL %d\n", Size);

	MPLDBG_ADD(mem, Size);

	return mem;
}

void CtObject::operator delete(void* pObj)
{
	SYSWRAP_ERROR er;
    er = syswrap_free_memory(&ct_mempool_normal, pObj);

	MPLDBG_DEL(pObj);
}

void CtObject::operator delete[](void* pObj)
{
	SYSWRAP_ERROR er;
	er = syswrap_free_memory(&ct_mempool_normal, pObj);

	MPLDBG_DEL(pObj);
}

#endif // !defined(CT_CHECK_DOUBLE_FREE)

CtObject::CtObject() :
	m_ClassType(CtClassType_MIN)
{
}

CtObject::~CtObject()
{
}

void CtObject::setClassType(const CtClassType ClassType)
{
	m_ClassType = ClassType;
	return;
}

CtObject::CtObject(const CtObject& Obj) :
	m_ClassType(Obj.getClassType())
{
}
