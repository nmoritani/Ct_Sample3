/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_008
 */


#ifndef __CtWindow_008_H__
#define __CtWindow_008_H__

#include "CtWindowCommon.h"
#include "CtTimer.h"
#include "CtFastContainerTimeCode.h"

class CtWindow_008 : public CtWindowMain
{
public:
	CtWindow_008(CtWindowContents *pContents);
	~CtWindow_008();

	bool handleTouchEvent(const CtEventTouch& Touch);

	
	CtFastContainerTimeCode *pContainer01;
	CtLabel *pTest;

	int index;

private:
	CtWindow* createWindow();
	bool destroyWindow();
	int m_TimerState;
	CtLayout *m_pLayout1;
	CtLayout *m_pLayout2;
};

#endif
