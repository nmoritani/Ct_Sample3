
#if !defined(__CTOBJECT_H__)
#define __CTOBJECT_H__

#include <stdio.h>
#include "../Include/CtDebugPrint.h"
#include "../Include/CtAssert.h"
#include "../Include/CtClassType.h"

#if defined(WIN32_GUI_SIM)
// 以下のコメントアウトを解除するとitronのmplからメモリを確保せずに
// OSからメモリを確保するようになり、ダブルフリーの検出ができます
//#define CT_CHECK_DOUBLE_FREE
#endif

class CtObject
{

public:
	virtual ~CtObject();

#if !defined(CT_CHECK_DOUBLE_FREE)
	void *operator new(size_t Size) throw();
	void *operator new[](size_t Size) throw();
	void operator delete(void *pObj);
	void operator delete[](void *pObj);
#endif
	
	inline CtClassType getClassType() const;
	
protected:
	CtObject();
	
	CtObject(const CtObject& Obj);

	void setClassType(const CtClassType classType);

private:
	CtClassType m_ClassType;

};

inline CtClassType CtObject::getClassType() const
{
	return m_ClassType;
}



#endif // !defined(__CTOBJECT_H__)
