/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_003
 */


#ifndef __CtWindow_003_H__
#define __CtWindow_003_H__

#include "CtWindowCommon.h"
#include "CtSlideLabel.h"

class CtWindow_003 : public CtWindowMain
{
public:
	CtWindow_003(CtWindowContents *pContents);
	~CtWindow_003();
	bool handleTouchEvent(const CtEventTouch& Touch);

private:
	CtWindow* createWindow();
	bool destroyWindow();

	CtWindow *m_pWin;
	CtSlideLabel *m_pSlideLabel;
};

#endif
