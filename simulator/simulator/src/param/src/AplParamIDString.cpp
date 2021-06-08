/**
 *  Copyright (c) 2017-2018 Panasonic Corporation
 *  Element:										AplParamIDString
 */
#include "AplParamIDString.h"

#define STR(var) #var

const AplParamIDString::ParamFactoryTable AplParamIDString::m_ParamTable[] = {
	#include "paramString.def"
};

const char* AplParamIDString::getString(int id)
{
	if (id == AplParamIdMax) return "AplParamIdMax";

	for (int i = 0; i < sizeof(m_ParamTable) / sizeof(ParamFactoryTable); i++) {    /* pgr0360 */
		if (m_ParamTable[i].id == id) return m_ParamTable[i].name;
	}
	return "Unknown";
}
