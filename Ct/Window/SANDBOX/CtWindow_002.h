/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_002
 */


#ifndef __CtWindow_002_H__
#define __CtWindow_002_H__

#include "CtWindowCommon.h"
#include "CtKeyboad.h"

class CtWindow_002 : public CtWindowMain
{
public:
	CtWindow_002(CtWindowContents *pContents);
	~CtWindow_002();

private:
	CtWindow* createWindow();

	CtContainer *m_pKeyContainer;
};

#endif
