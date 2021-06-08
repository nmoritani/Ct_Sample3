/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtContainer
 */

#include "CtContainer.h"
#include "CtEvent.h"
#include "CtLayout.h"
#include "CtWindow.h"

CtContainer::CtContainer() :
	m_pLayout(NULL),
	m_ScreenSel(ScreenAll),
	m_bFastDraw(false),
	m_State(StateInvalid),
	m_bVisible(true),
	m_PostKeyEvent(EventNone)
{
	setClassType(CtClassType_Container);
}

CtContainer::CtContainer(CtScreenSel ScreenSel) :
	m_pLayout(NULL),
	m_ScreenSel(ScreenSel),
	m_bFastDraw(false),
	m_State(StateInvalid),
	m_PostKeyEvent(EventNone)
{
	setClassType(CtClassType_Container);
}

bool CtContainer::destroyContainer()
{
	return false;
}

CtLayout* CtContainer::create()
{
	if (m_pLayout == NULL) {
		m_pLayout = createContainer();
	}
	
	if (m_pLayout == NULL)
		return NULL;
	
	m_pLayout->setScreenSel(m_ScreenSel);
	return m_pLayout;
}

bool CtContainer::destroy()
{
	setAlive(false);
	return destroyContainer();
}

CtContainer::~CtContainer()
{
}

bool CtContainer::startup()
{
	if (m_pLayout == NULL)
		return false;

	m_pLayout->setVisible(m_bVisible);
	m_pLayout->setScreenSel(m_ScreenSel);
	setAlive(true);
	
	startupContainer();
	setViewing(true);

	return true;
}

bool CtContainer::isVisible() const
{
	return m_bVisible;
}

bool CtContainer::setVisible(const bool bVisible)
{
	bool bRet = false;
	
	if (m_bVisible == bVisible)
		return false;

	m_bVisible = bVisible;
	
	if (m_pLayout != NULL) {
		if (m_pLayout->setVisible(bVisible) == true) {
			CtEventInterface::requestWidgetCmd(m_pLayout->getWidgetID(), m_pLayout, CtEventWidget::RestartWindow);
		}
	}
	return bRet;
}

CtScreenSel CtContainer::getScreenSel() const
{
	return m_ScreenSel;
}

bool CtContainer::setScreenSel(const CtScreenSel ScreenSel)
{
	if (m_ScreenSel == ScreenSel)
		return false;

	m_ScreenSel = ScreenSel;
	
	if (m_pLayout != NULL) {
		m_pLayout->setScreenSel(ScreenSel);
	}
	
	return true;
}

bool CtContainer::handleKeyEvent(const CtEventKey& Key)
{
	return false;
}

bool CtContainer::handleTouchEvent(const CtEventTouch& Touch)
{
	return false;
}

bool CtContainer::handleParamEvent(const CtEventParam& Param)
{
	return false;
}

bool CtContainer::handleTimerEvent(const CtEventTimer& Timer)
{
	return false;
}

bool CtContainer::handleFlashEvent(const CtEventFlash& Flash)
{
	return false;
}

bool CtContainer::handleButtonEvent(const CtEventButton& Button)
{
	return false;
}

bool CtContainer::handleWidgetEvent(const CtEventWidget& Widget)
{
	return false;
}

bool CtContainer::setContents(const CtWindowContents* pContents)
{
	return false;
}

bool CtContainer::isAlive() const
{
	if (m_State >= StateAlive)
		return true;

	return false;
}

bool CtContainer::setAlive(bool bAlive)
{
	State state;
	
	if (bAlive == true)	state = StateAlive;
	else				state = StateInvalid;
	
	if (m_State == state)
		return false;
	
	m_State = state;
	return true;
}

bool CtContainer::isViewing() const
{
	if (m_State >= StateViewing)
		return true;

	return false;
}

bool CtContainer::setViewing(bool bViewing)
{
	State state;

	if (bViewing == true) state = StateViewing;
	else				  state = StateAlive;

	if (m_State == state)
		return false;

	m_State = state;
	return true;
}

bool CtContainer::startupContainer()
{
	return false;
}
	
bool CtContainer::initialFastDraw()
{
	if (m_pLayout == NULL)
		return false;

	CtDraw::getInstance()->getDrawing(true);
	m_bFastDraw = m_pLayout->initialFastDraw();
	CtDraw::getInstance()->freeDrawing();
			
	return m_bFastDraw;
}

bool CtContainer::cleanupFastDraw()
{
	if (m_pLayout == NULL)
		return false;
	
	if (m_bFastDraw != true)
		return false;

	return m_pLayout->cleanupFastDraw();
}

bool CtContainer::updateFastDraw()
{
	return false;
}

bool CtContainer::setCollisions(CtWidget::List& _List, int Screen)
{
	bool bRet = false;
	
	if (_List.size() <= 0)
		return false;

	if (Screen < 0 || CT_SCREEN_NUM <= Screen)
		return false;
	
	if (m_Collisions[Screen].size() > 0)
		m_Collisions[Screen].clear();

	for (CtWidget::ListItr Itr = _List.begin(); Itr != _List.end(); ++Itr) {
		m_Collisions[Screen].push_back((*Itr));
		bRet = true;
	}
	
	return bRet;
}

bool CtContainer::draw(const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtWidget* pWidget = NULL;
	
	if (m_pLayout == NULL)
		return bRet;

	if (haveFastDraw() != true)
		return bRet;

	m_pLayout->clearInvalidate(Screen);
		
	if (isViewing() == true) {
		if (m_pLayout->draw(Clip, Screen) == true)
			bRet = true;
	}

	for (int i = 0; i < m_Collisions[Screen].size(); i++) {
		if ((pWidget = m_Collisions[Screen][i]) == NULL) continue;
		if (pWidget->isCollision(Clip, Screen) != true) continue;
		if (pWidget->isVisible2(Screen) != true) continue;	// Windowã‚Å•\Ž¦•s—v‚©‚Ç‚¤‚©
		if (pWidget->draw(Clip, Screen) == true)
			bRet = true;
	}
	
	return bRet;
}


