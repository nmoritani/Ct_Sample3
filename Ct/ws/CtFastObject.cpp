#include <stdio.h>
#include "CtFastObject.h"


#if !defined(CT_CHECK_DOUBLE_FREE)

void* CtFastObject::operator new(size_t Size) throw()
{
	void *mem = NULL;
		
	if (tget_mpl(CT_FASTMPL_ID, (UINT)Size, &mem, 500) != E_OK) {
		CtDebugPrint(CtDbg, "!!! FAST_MPL allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}
	return mem;
}

void* CtFastObject::operator new[](size_t Size) throw()
{
	void *mem = NULL;

	if (tget_mpl(CT_FASTMPL_ID, (UINT)Size, &mem, 500) != E_OK) {
		CtDebugPrint(CtDbg, "!!! allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}
	return mem;
}

void CtFastObject::operator delete(void* pObj)
{
	ER er;
    er = rel_mpl(CT_FASTMPL_ID, pObj);
}

void CtFastObject::operator delete[](void* pObj)
{
	ER er;
	er = rel_mpl(CT_FASTMPL_ID, pObj);
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
