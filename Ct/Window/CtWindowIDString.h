/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtWindowIDString
*/


#ifndef __CtWindowIDString_H__
#define __CtWindowIDString_H__

#include "CtWindowID.h"
#include "CtObject.h"

static const unsigned int InvalidateWinID = WindowID_MAX;
static const unsigned int DefaultWinID = WindowNone;

class CtWindowIDString : public CtObject
{
public:
	static const char* getString(CtWindowID id);
	static const char* getString(unsigned int tableIndex);
	static CtWindowID getWindowID(unsigned int Index);
	static CtWindowID getWindowID(const char* str);
private:
	struct CtFactoryTable {
		CtWindowID id;
		const char* name;
	};
	static const CtFactoryTable m_Table[];
};

#endif
