/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtWindow
 */


#ifndef __CtWindow_H__
#define __CtWindow_H__

#include <CtList.h>
#include <CtVector.h>
#include "Ct.h"
#include "CtEvent.h"
#include "CtLayout.h"
#include "CtButton.h"
#include "CtWidget.h"
#include "CtWindowID.h"
#include "CtFuncID.h"
#include "CtEventInterface.h"
class CtWindowMain;

enum CtOpenType {
	OpenChange = CtEventWindow::Change,
	OpenPopup = CtEventWindow::Popup,
	OpenSwap = CtEventWindow::Swap,
	Close = CtEventWindow::Close,
	Return = CtEventWindow::Return
};

class CtWindow : public CtLayout {
public :
    CtWindow();
    CtWindow(const CtColor& Color);
    CtWindow(const CtSize& Size, const CtColor& Color);
    CtWindow(const CtRegion& Region, const CtColor& Color);

    virtual ~CtWindow();
	
	void setMain(CtWindowMain *pMain);
	CtWindowMain* getMain() const;
	
	bool layoutWindow(int Screen = 0);
	
	void setWindowID(const CtWindowID WindowID);
	CtWindowID getWindowID() const;
	
	virtual bool setDefaultFocus(CtWidget* pWidget);
	virtual bool initialFocus(bool bSilent);
	virtual void setRoundFocus(bool bRound);
	virtual bool isRoundFocus();
	
	virtual CtWidget* getFocusWidget();
	virtual bool setFocusWidget(CtWidget* pWidget);
	virtual bool clearFocusWidget(CtWidget* pWidget);
	
	virtual bool moveFocus(const CtDirection Dir, bool Silent);
	virtual bool setDialIndex();
	virtual void setDialIndexMax(int max);
	virtual int getDialIndexMax();
	virtual bool dialFocus(const bool bPlus, bool Silent);

	virtual bool putKeyEvent(const CtEventKey& Key);
	virtual bool putTouchEvent(const CtEventTouch& Touch);
	virtual bool putParamEvent(const CtEventParam& Param);
	virtual bool putButtonEvent(const CtEventButton& Button);
	virtual bool putWidgetEvent(const CtEventWidget& Widget);
	
	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
	virtual bool handleFlashEvent(const CtEventFlash& Flash);
	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleWidgetEvent(const CtEventWidget& Widget);
	bool cancelPressing();
	
	virtual bool isWindow() const;
	virtual bool isLayout() const;

	bool setVisible(bool bVisible);
	
	bool requestWindow(CtWindowID id, CtOpenType type, void* addr) {
		return false;
	}

	bool requestFunction(const CtFuncID id, CtWindowContents *pContents) {
		return false;
	}
	
protected :
	void ctor();
	
private :
	CtWindowID		m_WindowID;
	CtWidget*		m_pCurrentFocus;
	CtWidget*		m_pDefaultFocus;
	int				m_DialIndexMax;
	bool			m_bRoundFocus;
	
	CtWindowMain*	m_pWindowMain;
};

inline void CtWindow::setMain(CtWindowMain *pMain)
{
	m_pWindowMain = pMain;
}

inline void CtWindow::setWindowID(const CtWindowID Id)
{
	m_WindowID = Id;
}

inline CtWindowID CtWindow::getWindowID() const
{
	return m_WindowID;
}

inline bool CtWindow::isWindow() const
{
	return true;
}

inline bool CtWindow::isLayout() const
{
	return true;
}

inline void CtWindow::setRoundFocus(bool bRound)
{
	m_bRoundFocus = bRound;
}

inline bool CtWindow::isRoundFocus()
{
	return m_bRoundFocus;
}
inline void CtWindow::setDialIndexMax(int max)
{
	m_DialIndexMax = max;
}

inline int CtWindow::getDialIndexMax()
{
	return m_DialIndexMax;
}

#endif
