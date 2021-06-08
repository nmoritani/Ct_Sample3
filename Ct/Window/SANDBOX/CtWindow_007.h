/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_007
 */


#ifndef __CtWindow_007_H__
#define __CtWindow_007_H__

#include "CtWindowCommon.h"
#include "CtListContainer.h"
class CtWindow_007 : public CtWindowMain
{
public:
	CtWindow_007(CtWindowContents *pContents);
	~CtWindow_007();
	virtual bool handleKeyEvent(const CtEventKey& Key);
private:
	CtWindow* createWindow();
	bool destroyWindow();

	bool handleButtonEvent(const CtEventButton& Button);
	
	CtWindow* m_pWin;
	CtListContainer* m_pList;
};

#endif
