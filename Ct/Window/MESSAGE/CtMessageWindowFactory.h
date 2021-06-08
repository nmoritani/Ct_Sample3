/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMessageWindowFactory
 */


#ifndef __CtMessageWindowFactory_H__
#define __CtMessageWindowFactory_H__

#include "CtWindowCommon.h"

class CtMessageWindowFactory : public CtObject
{
public:
	CtMessageWindowFactory(){};
	~CtMessageWindowFactory(){};
	static CtWindowMain* create(CtWindowID id,  CtWindowContents *pContents);

private:
};

#endif
