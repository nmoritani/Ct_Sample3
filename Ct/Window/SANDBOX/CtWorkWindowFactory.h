/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWorkWindowFactory
 */


#ifndef __CtWorkWindowFactory_H__
#define __CtWorkWindowFactory_H__

#include "Ct.h"
#include "CtWindow_001.h"
#include "CtWindow_002.h"
#include "CtWindow_003.h"
#include "CtWindow_004.h"
#include "CtWindow_005.h"
#include "CtWindow_006.h"
#include "CtWindow_007.h"
#include "CtWindow_008.h"
#include "CtWindow_TransitionTest.h"

class CtWorkWindowFactory : public CtObject
{
public:
	CtWorkWindowFactory(){};
	~CtWorkWindowFactory(){};
	static CtWindowMain* create(CtWindowID id,  CtWindowContents *pContents);
private:
};

#endif
