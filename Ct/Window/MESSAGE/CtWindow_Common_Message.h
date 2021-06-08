/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindow_Common_Message
 */


#ifndef __CtWindow_Common_Message_H__
#define __CtWindow_Common_Message_H__

#include "CtWindows.h"
#include "CtWindowCommon.h"
#include "CtMessageDesign.h"
#include "CtWindowContentsMessage.h"
#include "CtWindowContentsWizardMessage.h"
#include "CtTimer.h"

const int CT_COMMON_MSG_TIMER_ID = 0;

class CtWindow_Common_Message : public CtWindowMain
{
public:
	CtWindow_Common_Message( CtWindowContents *pContents );
	~CtWindow_Common_Message();
	virtual CtWindow* createWindow();

	bool handleButtonEvent(const CtEventButton& Button);
	bool handleTouchEvent(const CtEventTouch& Touch);
	bool handleTimerEvent(const CtEventTimer& Timer);

	virtual bool setContents(const CtWindowContents* pContents); // WindowContentのセット
//	virtual void updateContents();    // コンテンツ更新通知
	virtual bool startupWindow();
	virtual void closeWindow();
	
private:
	CtWindowContentsMessage*	m_pContent;
	
	CtLayout* createDialog();
	CtLayout* createTitle();
	CtLayout* createMain();
	CtLayout* createControl( bool bSet, bool bRet );  /*変数と関数同名です*/
	
	CtLayout* createTelop();

	void initMessage();
	void updateTelop();
	void updateDialog();

	bool destroyWindow();
	
	CtWindow*	m_pWin;
	
	bool set();
	bool ret();
	CtButton*	m_pSet;
	CtButton*	m_pRet;
	
	
	CtLayout*	m_pDialogMainLayout;
	CtLabel*	m_pDialogTitle;
	CtLabel*	m_pDialogMsg;

	CtLayout*	m_pTelopMainLayout;
	CtLabel*	m_pTelopMsg;
	CtHLayout*	m_pTelop;
	
};

class CtWindow_Wizard_Message : public CtWindow_Common_Message
{
public:
	CtWindow_Wizard_Message(CtWindowContents *pContents);
	~CtWindow_Wizard_Message();
	virtual void closeWindow();
private:
	CtWindowContentsWizardMessage*	m_pContent;
};


#endif
