#include <stdio.h>
#include "CtObject.h"
#include "CtMplDbg.h"


#if !defined(CT_CHECK_DOUBLE_FREE)

void* CtObject::operator new(size_t Size) throw()
{
	void *mem = NULL;
	
	if (tget_mpl(CT_MPL_ID, (UINT)Size, &mem, 500) != E_OK) {
		CtDebugPrint(CtDbg, "!!! CT_MPL allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}

	MPLDBG_ADD(mem, Size, CT_MPL_ID);
	
	return mem;
}

void* CtObject::operator new[](size_t Size) throw()
{
	void *mem = NULL;

	if (tget_mpl(CT_MPL_ID, (UINT)Size, &mem, 500) != E_OK) {
		CtDebugPrint(CtDbg, "!!! allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}
	
	CtDebugPrint(CtDbg, "getMPL %d\n", Size);

	MPLDBG_ADD(mem, Size, CT_MPL_ID);

	return mem;
}

void CtObject::operator delete(void* pObj)
{
	ER er;
    er = rel_mpl(CT_MPL_ID, pObj);

	MPLDBG_DEL(pObj);
}

void CtObject::operator delete[](void* pObj)
{
	ER er;
	er = rel_mpl(CT_MPL_ID, pObj);

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
