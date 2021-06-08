/**
 *  Copyright (c) 2017-2018 Panasonic Corporation
 *  Element:			CtWindowIDString
 */


#ifndef __AplParamIDString_H__
#define __AplParamIDString_H__

#include "AplParam.h"
#include "CtObject.h"

class AplParamIDString : public CtObject
{
public:
	static const char* getString(int id);

private:
	struct ParamFactoryTable {
		int id;
		const char* name;
	};
	static const ParamFactoryTable m_ParamTable[];
};

#endif
