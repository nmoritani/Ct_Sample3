/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtWindowFactory
*/

#include "CtWindowIDString.h"
#include <string.h>

#define STR(var) #var
// CtWinodwID->•¶Žš—ñ•ÏŠ·ƒe[ƒuƒ‹
const CtWindowIDString::CtFactoryTable CtWindowIDString::m_Table[] = {
#include "CtWindowIDString.def"
};

const char* CtWindowIDString::getString(unsigned int tableIndex)
{
	if (tableIndex >= sizeof(m_Table) / sizeof(CtFactoryTable)) {
		return "Unknown";
	}
	return m_Table[tableIndex].name;
}
const char* CtWindowIDString::getString(CtWindowID id)
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
CtWindowID CtWindowIDString::getWindowID(unsigned int Index)
{
	if (Index >= sizeof(m_Table) / sizeof(CtFactoryTable)) {
		return WindowID_MAX;
	}
	return m_Table[Index].id;
}

CtWindowID CtWindowIDString::getWindowID(const char* str)
{
	if (str == NULL) { return WindowID_MAX; }
	unsigned int i = 0;
	while (i < sizeof(m_Table) / sizeof(CtFactoryTable)) {
		if (strcmp(m_Table[i].name, str) == 0) {
			return m_Table[i].id;
		}
		i++;
	}
	return WindowID_MAX;
}
