/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_005
 */


#ifndef __CtWindow_005_H__
#define __CtWindow_005_H__

#include "CtWindowCommon.h"

class CtWindow_005 : public CtWindowMain
{
public:
	CtWindow_005(CtWindowContents *pContents);
	~CtWindow_005();
	virtual bool handleButtonEvent(const CtEventButton& Button);
private:
	CtWindow* createWindow();
	bool destroyWindow();
	CtToggleButton* pSymbolBtn;
	CtStackLabel* pSymbol;
	CtStackLabel* pSymbol2;
	CtWindow *m_pWin;
};

#endif
