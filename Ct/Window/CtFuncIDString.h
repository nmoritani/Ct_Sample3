/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtFuncIDString
*/


#ifndef __CtFuncIDString_H__
#define __CtFuncIDString_H__

#include "CtFuncID.h"
#include "CtObject.h"

class CtFuncIDString : public CtObject
{
public:
	static const char* getString(CtFuncID id);
private:
	struct CtFactoryTable {
		CtFuncID id;
		const char* name;
	};
	static const CtFactoryTable m_Table[];
};

#endif
