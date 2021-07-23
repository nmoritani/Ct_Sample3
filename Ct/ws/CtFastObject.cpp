#include <CtPlatforms.h>
#include "CtFastObject.h"

#include <CtPlatforms.h>

#if !defined(CT_CHECK_DOUBLE_FREE)

void* CtFastObject::operator new(size_t Size) throw()
{
	void *mem = NULL;

	if (syswrap_alloc_memory(&ct_mempool_fast, &mem, Size) != SYSWRAP_ERR_OK) {
		CtDebugPrint(CtDbg, "!!! FAST_MPL allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}
	return mem;
}

void* CtFastObject::operator new[](size_t Size) throw()
{
	void *mem = NULL;

	if (	syswrap_alloc_memory(&ct_mempool_fast, &mem, Size) != SYSWRAP_ERR_OK) {
		CtDebugPrint(CtDbg, "!!! allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}
	return mem;
}

void CtFastObject::operator delete(void* pObj)
{
	SYSWRAP_ERROR er;
    er = syswrap_free_memory(&ct_mempool_fast, pObj);
}

void CtFastObject::operator delete[](void* pObj)
{
	SYSWRAP_ERROR er;
	er = syswrap_free_memory(&ct_mempool_fast, pObj);
}

#endif // !defined(CT_CHECK_DOUBLE_FREE)

CtFastObject::CtFastObject() :
	m_ClassType(CtClassType_MIN)
{
}

CtFastObject::~CtFastObject()
{
}

void CtFastObject::setClassType(const CtClassType ClassType)
{
	m_ClassType = ClassType;
	return;
}

CtFastObject::CtFastObject(const CtFastObject& Obj) :
	m_ClassType(Obj.getClassType())
{
}
