/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtContainer
 */


#ifndef __CtContainer_H__
#define __CtContainer_H__

#include "Ct.h"
#include "CtEvent.h"
#include "CtWidget.h"

class CtButton;
class CtLayout;
class CtWindow;

class CtContainer : public CtEventHandler {
public :
	enum State {
		StateInvalid,
		StateAlive,
		StateViewing,
		StateMax
	};
	
	typedef CtVector::Vector<CtContainer*>	Array;
	typedef CtVector::Vector<CtContainer*>::iterator ArrayItr;
	
    typedef CtList::list<CtContainer*> List;
    typedef CtList::list<CtContainer*>::iterator ListItr;
	
    CtContainer();
    CtContainer(CtScreenSel ScreenSel);

    virtual ~CtContainer();

	CtScreenSel getScreenSel() const;
	bool setScreenSel(const CtScreenSel ScreenSel);

	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
	virtual bool handleFlashEvent(const CtEventFlash& Flash);
	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleWidgetEvent(const CtEventWidget& Widget);
	virtual bool setContents(const CtWindowContents* pContents);

	bool isAlive() const;
	bool setAlive(bool bAlive);
	bool isViewing() const;
	bool setViewing(bool bViewing);
	
	bool startup();
	
	virtual bool updateFastDraw();
	bool initialFastDraw();
	bool cleanupFastDraw();
	bool haveFastDraw() const;
	
	virtual bool draw(const CtRegion& Clip, int Screen = 0);
	
	void setParent(CtContainer *pParent);
	CtContainer* getParent();

	CtLayout* getLayout();

	// ToolKità»äOÇ©ÇÁÇÃåƒÇ—èoÇµNG
	CtLayout* create();
	bool destroy();

	void setPostEvent(CtEventFilter eType);
	bool isPostEvent(CtEventFilter eType) const;
	bool isVisible() const;
	bool setVisible(const bool bVisible);

	virtual bool startupContainer();

	bool setCollisions(CtWidget::List& List, int Screen = 0);

protected:	
	CtLayout *m_pLayout;
	CtContainer *m_pParent;
	bool	 m_bFastDraw;
	
private :
	virtual CtLayout* createContainer() = 0;
	virtual bool destroyContainer();
	
	CtScreenSel			m_ScreenSel;
	State				m_State;
	bool				m_bVisible;
	CtEventFilter		m_PostKeyEvent;
	CtVector::Vector<CtWidget*>	m_Collisions[CT_SCREEN_NUM];
};

inline void CtContainer::setParent(CtContainer *pParent)
{
	m_pParent = pParent;
}

inline CtContainer* CtContainer::getParent()
{
	return m_pParent;
}

inline CtLayout* CtContainer::getLayout()
{
	return m_pLayout;
}

inline bool CtContainer::haveFastDraw() const
{
	return m_bFastDraw;
}

inline void CtContainer::setPostEvent(CtEventFilter eType)
{
	m_PostKeyEvent = (CtEventFilter)(m_PostKeyEvent | eType) ;
}

inline bool CtContainer::isPostEvent(CtEventFilter eType) const
{
	return m_PostKeyEvent & eType ? true : false;
}

#endif
