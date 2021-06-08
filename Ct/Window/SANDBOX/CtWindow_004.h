/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_004
 */


#ifndef __CtWindow_004_H__
#define __CtWindow_004_H__

#include "CtWindowCommon.h"

class CtWindow_004 : public CtWindowMain
{
public:
	CtWindow_004(CtWindowContents *pContents);
	~CtWindow_004();

	bool handleTouchEvent(const CtEventTouch& Touch);
	bool handleKeyEvent(const CtEventKey& Key);
	bool handleButtonEvent(const CtEventButton& Button);
private:
	CtWindow* createWindow();
	bool destroyWindow();
	CtLabel *m_pLabel;
	int		m_TouchCnt;

	CtWindow *m_pWin;
};

#endif
