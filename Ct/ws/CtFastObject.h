
#if !defined(__CTFASTOBJECT_H__)
#define __CTFASTOBJECT_H__

#include <stdio.h>
#include "../Include/CtDebugPrint.h"
#include "../Include/CtAssert.h"
#include "../Include/CtClassType.h"

#if defined(WIN32_GUI_SIM)
// �ȉ��̃R�����g�A�E�g�����������itron��mpl���烁�������m�ۂ�����
// OS���烁�������m�ۂ���悤�ɂȂ�A�_�u���t���[�̌��o���ł��܂�
//#define CT_CHECK_DOUBLE_FREE
#endif

class CtFastObject
{

public:
	virtual ~CtFastObject();

#if !defined(CT_CHECK_DOUBLE_FREE)
	void *operator new(size_t Size) throw();
	void *operator new[](size_t Size) throw();
	void operator delete(void *pObj);
	void operator delete[](void *pObj);
#endif
	
	inline CtClassType getClassType() const;
	
protected:
	CtFastObject();
	
	CtFastObject(const CtFastObject& Obj);

	void setClassType(const CtClassType classType);

private:
	CtClassType m_ClassType;

};

inline CtClassType CtFastObject::getClassType() const
{
	return m_ClassType;
}



#endif // !defined(__CTFASTOBJECT_H__)
