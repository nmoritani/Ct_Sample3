/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtFuncFactory
*/

#include "CtFuncIDString.h"
#include <string.h>

#define STR(var) #var
// CtFuncID->•¶š—ñ•ÏŠ·ƒe[ƒuƒ‹
const CtFuncIDString::CtFactoryTable CtFuncIDString::m_Table[] = {
#include "CtFuncIdString.def"
};

const char* CtFuncIDString::getString(CtFuncID id)
{
	unsigned int i = 0;
	while (i < sizeof(m_Table) / sizeof(CtFactoryTable)) {
		if (m_Table[i].id == id) {
			return m_Table[i].name;
		}
		i++;
	}
	return "Unknown";
}
