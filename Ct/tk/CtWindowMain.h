/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowMain
 */


#ifndef __CtWindowMain_H__
#define __CtWindowMain_H__

#include <CtVector.h>
#include "Ct.h"
#include "CtEvent.h"
#include "CtWindow.h"
#include "CtContainer.h"
#include "CtWindowContents.h"
#include "CtEventInterface.h"

class CtWindowMain : public CtEventHandler {
public :
	enum State {
		StateInvalid,
		StateAlive,
		StateInvisible,
		StateDrawing,
		StateViewing,
		StateMax
	};

	typedef CtVector::Vector<CtWindowMain*> Array;
	typedef CtVector::Vector<CtWindowMain*>::iterator ArrayItr;
    typedef CtList::list<CtWindowMain*> List;
    typedef CtList::list<CtWindowMain*>::iterator ListItr;
	
    CtWindowMain();
    CtWindowMain(CtWindowContents *pContents);

    virtual ~CtWindowMain();

	CtScreenSel getScreenSel() const;
	
	void setWindowID(const CtWindowID WindowID);
	CtWindowID getWindowID() const;
	
	void setTransEvent(const bool TransEvent);
	bool isTransEvent() const;
	
	bool setEventFilter(const CtEventFilter EventFiter);
	CtEventFilter getEventFilter() const;
	
	bool putKeyEvent(const CtEventKey& Key);
	bool putTouchEvent(const CtEventTouch& Touch);
	bool putParamEvent(const CtEventParam& Param);
	bool putTimerEvent(const CtEventTimer& Timer);
	bool putFlashEvent(const CtEventFlash& Flash);
	bool putButtonEvent(const CtEventButton& Button);
	bool putWidgetEvent(const CtEventWidget& Widget);
	bool putDrawResult(const CtEventDrawResult& Result);
	bool putRequestEvent(const CtEventRequest& Request);
	
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
	virtual bool handleFlashEvent(const CtEventFlash& Flash);
	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleWidgetEvent(const CtEventWidget& Widget);
	virtual bool handleRequestEvent(const CtEventRequest& Request);
	bool cancelPressing();

	virtual bool updateContents();
	
	virtual bool setContents(const CtWindowContents* pContents);
	
	CtWindowInfo* getWindowInfo();
	CtRegion getRegion(int Screen = 0) const;
    
	bool setTransView(bool bTrans);
	bool isTransView() const;

	bool setFocusSilent(bool bSilent);
	
	CtWindow* create(CtScreenSel ScreenSel = ScreenLCD);
	bool destroy(CtScreenSel ScreenSel = ScreenLCD);
	bool startup();
	bool restart();
	bool haveWindow(CtScreenSel ScreenSel = ScreenLCD) const;

	virtual bool setInvalidate();
	virtual bool isInvalidate() const;
	virtual bool getInvalidates(CtWidget::RegionArray& Array, int Screen = 0);
	virtual bool clearInvalidates(int Screen = 0);

	bool updateFastDraw(unsigned long FrameCount);
	bool getInvalidatesFast(CtWidget::RegionArray& Array, int Screen = 0);
	bool clearInvalidatesFast(int Screen = 0);
	
	bool draw(const CtRegion& Clip, int Screen = 0);
	bool drawFast(const CtRegion& Clip, int Screen = 0);
	bool updated(int Screen = 0);
	
	bool addContainer(CtContainer* pContainer);
	bool removeContainer(CtContainer* pContainer);

	virtual void setScreenSel(CtScreenSel ScreenSel);

	bool setState(CtWindowMain::State State, int Screen = 0);
	CtWindowMain::State getState(int Screen = 0);
	bool isViewing(int Screen) const;
	bool isDrawing(int Screen) const;
	bool isAlive() const;
	bool setAlive(bool bAlive);

	bool setWindowClip(const CtRegion& Clip, int Screen = 0);
	CtRegion getWindowClip(int Screen = 0);
	bool setVisible(bool bVisible);
	bool isVisible() const;

	void setPostEvent(CtEventFilter eType);
	bool isPostEvent(CtEventFilter eType) const;
	
	void outputOutline(int Screen = 0) const;
protected:
    CtWindow 		*m_pWindow;
private :
	void ctor();
	virtual CtWindow* createWindow() = 0;
	virtual bool destroyWindow();
	virtual bool startupWindow();
	bool startupContainer();
	bool terminateContainer();
	
	CtWindowInfo	m_WindowInfo;
	
	State			m_WindowState[CT_SCREEN_NUM];
	CtRegion		m_WindowClip[CT_SCREEN_NUM];
	
	CtContainer::Array	m_Containers;
	unsigned long		m_FrameCount;
	bool				m_bFastUpdated;	// 同FrameCountで以前に高速描画アップデートしたか
	bool				m_bVisible;
	CtEventFilter		m_PostKeyEvent;
};

inline void CtWindowMain::setWindowID(const CtWindowID WindowID)
{
	m_WindowInfo.WindowID = WindowID;
	
	if (m_pWindow != NULL) {
		m_pWindow->setWindowID(WindowID);
	}
}

inline CtWindowID CtWindowMain::getWindowID() const
{
	return m_WindowInfo.WindowID;
}

inline bool CtWindowMain::setEventFilter(const CtEventFilter EventFilter)
{
	m_WindowInfo.EventFilter = EventFilter;
	return true;
}

inline CtEventFilter CtWindowMain::getEventFilter() const
{
	return m_WindowInfo.EventFilter;
}

inline void CtWindowMain::setTransEvent(const bool TransEvent)
{
	m_WindowInfo.TransEvent = TransEvent;
}

inline bool CtWindowMain::isTransEvent() const
{
	return m_WindowInfo.TransEvent;
}

inline void CtWindowMain::setScreenSel(CtScreenSel ScreenSel)
{
	if (m_pWindow != NULL)
		m_pWindow->setScreenSel(ScreenSel);
}

inline void CtWindowMain::setPostEvent(CtEventFilter eType)
{
	m_PostKeyEvent = (CtEventFilter)(m_PostKeyEvent | eType);
}

inline bool CtWindowMain::isPostEvent(CtEventFilter eType) const
{
	return m_PostKeyEvent & eType? true:false;
}

#endif
