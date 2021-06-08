/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_001
 */


#ifndef __CtWindow_006_H__
#define __CtWindow_006_H__

#include "CtWindowCommon.h"

#include "Ct2ListView.h"

class CtWindow_006 : public CtWindowMain
{
public:
	CtWindow_006(CtWindowContents *pContents);
	virtual ~CtWindow_006() {}
	
	virtual bool handleButtonEvent(const CtEventButton& Button);

private:
	virtual CtWindow* createWindow();
	virtual bool destroyWindow() { return true; }
	virtual bool startupWindow();

	CtButton* createButton();

    CtLayout* createRectTest();
    CtLayout* createButtonColorTest();
    CtLayout* createProgressBarTest();
	CtLayout* createCtrlButtonTest();
	CtLayout* createCtFontSetTest();
	CtLayout* createCtLineTest();
	CtLayout* createLanguageTest();
	CtLayout* createLanguageTest2();
	CtLayout* createLanguageTest3();
	CtLayout* createButtonColorTest2();
	bool startupWindow_ButtonColorTest2();


private:
	const int IndexOffset = 200;
	int m_Index;
	CtStackLabel* m_pTest;

	CtLabel* m_pLabel1_ButtonColorTest2;
	CtLabel* m_pLabel2_ButtonColorTest2;


};

#endif
