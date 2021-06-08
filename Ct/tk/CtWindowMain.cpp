/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtWindowMain
 */

#include "CtWindowMain.h"

void CtWindowMain::ctor()
{
	setClassType(CtClassType_WindowMain);

	m_pWindow = NULL;
	m_FrameCount = 0;
	m_bFastUpdated = false;
	m_bVisible = true;
	m_PostKeyEvent = EventNone;

	m_WindowInfo.ScreenSel = ScreenNone;
	m_WindowInfo.EventFilter = EventDefault;
	m_WindowInfo.TransEvent = false;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_WindowState[i] = StateInvalid;
		m_WindowClip[i] = NoRegion;
	}
}
	
CtWindowMain::CtWindowMain()
{
	ctor();
}

CtWindowMain::CtWindowMain(CtWindowContents *pContents)
{
	ctor();
	setContents(pContents);
}

CtWindowMain::~CtWindowMain()
{
}

CtWindow* CtWindowMain::create(CtScreenSel ScreenSel)
{
	if (m_pWindow == NULL) {
		if ((m_pWindow = createWindow()) == NULL)
			return NULL;
		m_pWindow->setMain(this);
		m_pWindow->setWindowID(m_WindowInfo.WindowID);
	}

	CtScreenSel CurrentSel = m_pWindow->getScreenSel();
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		CtScreenSel sel = toSelScreen(i);
		if (!(ScreenSel & sel)) continue;	// 要求スクリーンでなければスキップ
		if (CurrentSel & sel)	continue;	// カレントスクリーンがすでにあればスキップ

		m_pWindow->layoutWindow(i);
		CurrentSel = (CtScreenSel)(CurrentSel | sel);
	}

	m_pWindow->setScreenSel(CurrentSel);
	m_WindowInfo.ScreenSel = m_pWindow->getScreenSel();
	
	if (ScreenSel == ScreenLCD) {
		m_pWindow->initialFocus(m_WindowInfo.FocusSilent);
		m_pWindow->setDialIndex();
		m_pWindow->setEventFilter(EventNone);
	}
	
	setAlive(false);
	
	return m_pWindow;
}


bool CtWindowMain::destroyWindow()
{
	return true;
}

bool CtWindowMain::restart()
{
	if (m_pWindow == NULL)
		return false;

	CtDebugPrint(CtDbg, "#### WindowMain(%p): restart!!! #### \n", this);
	
	terminateContainer();
	
	m_pWindow->initialFocus(m_WindowInfo.FocusSilent);
	m_pWindow->setDialIndex();
	m_pWindow->setEventFilter(EventNone);
	startupContainer();
	return true;
}

bool CtWindowMain::startupWindow()
{
	return false;
}

bool CtWindowMain::startup()
{
	if (m_pWindow == NULL)
		return false;

	startupContainer();

	if (isAlive() != true) {
		startupWindow();
		setAlive(true);
	}

	return true;
}

bool CtWindowMain::setContents(const CtWindowContents* pContents)
{
	return false;
}

bool CtWindowMain::destroy(CtScreenSel ScreenSel)
{
	bool bRet = false;
	if (m_pWindow == NULL)
		return false;
	
	CtScreenSel CurrentSel = m_pWindow->getScreenSel();

	if (CurrentSel == ScreenNone)
		return false;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		CtScreenSel sel = toSelScreen(i);
		if (!(ScreenSel & sel))		 continue;	// 要求スクリーンでなければスキップ
		if (!(CurrentSel & sel))	continue;	// カレントスクリーンがすでにあればスキップ

		CurrentSel = (CtScreenSel)(CurrentSel & ~sel);
		setState(StateInvalid, toNoScreen((CtScreenSel)i));
	}
	m_pWindow->setScreenSel(CurrentSel);
	m_WindowInfo.ScreenSel = m_pWindow->getScreenSel();
	
	if (CurrentSel == ScreenNone) {
		destroyWindow();
		terminateContainer();
		if (m_pWindow != NULL)
			delete m_pWindow;
		m_pWindow = NULL;
		bRet = true;
		
		// 非表示を通知
		CtEventInterface::requestFuncCmd(ScreenAll, getWindowID(), FuncID_Window_Close);
	}
	
	return bRet;
}

CtWindowInfo* CtWindowMain::getWindowInfo()
{
	return &m_WindowInfo;
}

CtRegion CtWindowMain::getRegion(int Screen) const
{
	if (m_pWindow == NULL){
		CtRegion region(0,0,0,0);
		return region;
	}
	return m_pWindow->getRegion(Screen);
}

CtScreenSel CtWindowMain::getScreenSel() const
{
	return m_WindowInfo.ScreenSel;
}

bool CtWindowMain::putKeyEvent(const CtEventKey& Key)
{
	CtContainer* pContainer;
	
	if ((isViewing(0) != true) || !(m_WindowInfo.EventFilter & EventKey))
		return false;

	if (isPostEvent(EventKey) != true) {
		if (handleKeyEvent(Key) == true)
			return true;
	}

	if (m_pWindow == NULL)
		return false;

	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if (pContainer->isPostEvent(EventKey) == true)
			continue;
		
		if (pContainer->handleKeyEvent(Key) == true) {
			return true;
		}
	}

	if (m_pWindow->putKeyEvent(Key) == true)
		return true;

	if (isPostEvent(EventKey) == true) {
		if (handleKeyEvent(Key) == true)
			return true;
	}

	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if (pContainer->isPostEvent(EventKey) == false)
			continue;
		
		if (pContainer->handleKeyEvent(Key) == true) {
			return true;
		}
	}
	
	return false;
}

bool CtWindowMain::putTouchEvent(const CtEventTouch& Touch)
{
	CtContainer* pContainer;
	
	if ((isViewing(0) != true) || !(m_WindowInfo.EventFilter & EventTouch))
		return false;

	if (isPostEvent(EventTouch) != true) {
		if (handleTouchEvent(Touch) == true)
			return true;
	}

	if (m_pWindow == NULL)
		return false;
	
	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if (pContainer->isPostEvent(EventTouch) == true)
			continue;
		if (pContainer->handleTouchEvent(Touch) == true) {
			return true;
		}
	}
			
	if (m_pWindow->putTouchEvent(Touch) == true)
		return true;
	
	if (isPostEvent(EventTouch) == true) {
		if (handleTouchEvent(Touch) == true)
			return true;
	}
	
	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if (pContainer->isPostEvent(EventTouch) == false)
			continue;
		if (pContainer->handleTouchEvent(Touch) == true) {
			return true;
		}
	}
	return false;
}

bool CtWindowMain::putParamEvent(const CtEventParam& Param)
{
	bool bRet = false;
	CtContainer* pContainer;
	
	if (!(m_WindowInfo.EventFilter & EventParam))
		return false;

	if (isPostEvent(EventParam) != true) {
		if (handleParamEvent(Param) == true)
			bRet = true;
	}
		
	if (m_pWindow == NULL)
		return bRet;

	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if (pContainer->isPostEvent(EventParam) == true)
			continue;
		
		if (pContainer->handleParamEvent(Param) == true) {
			bRet = true;
		}
	}
			
	if (m_pWindow->putParamEvent(Param) == true)
		bRet = true;
	
	if (isPostEvent(EventParam) == true) {
		if (handleParamEvent(Param) == true)
			bRet = true;
	}
	
	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if  (pContainer->isPostEvent(EventParam) == false)
			continue;
		
		if (pContainer->handleParamEvent(Param) == true) {
			bRet = true;
		}
	}
			
	return bRet;
}

bool CtWindowMain::putTimerEvent(const CtEventTimer& Timer)
{
	return false;
}

bool CtWindowMain::putFlashEvent(const CtEventFlash& Flash)
{
	return false;
}

bool CtWindowMain::putButtonEvent(const CtEventButton& Button)
{
	CtContainer* pContainer;

	if ((isViewing(0) != true) || !(m_WindowInfo.EventFilter & EventButton))
		return false;

	if (isPostEvent(EventButton) != true) {
		if (handleButtonEvent(Button) == true)
			return true;
	}

	if (m_pWindow == NULL)
		return false;

	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if (pContainer->isPostEvent(EventButton) == true)
			continue;
		
		if (pContainer->handleButtonEvent(Button) == true) {
			return true;
		}
	}
	
	if (m_pWindow->putButtonEvent(Button) == true)
		return true;
	
	if (isPostEvent(EventButton) == true) {
		if (handleButtonEvent(Button) == true)
			return true;
	}

	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if  (pContainer->isPostEvent(EventButton) != true)
			continue;
		
		if (pContainer->handleButtonEvent(Button) == true) {
			return true;
		}
	}
	
	return false;
}

bool CtWindowMain::putWidgetEvent(const CtEventWidget& Widget)
{
	CtContainer* pContainer;
	
	if ((isAlive() != true) || !(m_WindowInfo.EventFilter & EventParam))
		return false;

	if (Widget.getRequest() == CtEventWidget::RestartWindow) {
		restart();
		return true;
	}

	if (handleWidgetEvent(Widget) == true)
		return true;

	if (m_pWindow == NULL)
		return false;

	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		
		if (pContainer->handleWidgetEvent(Widget) == true) {
			return true;
		}
	}
	
	return false;
}

bool CtWindowMain::putDrawResult(const CtEventDrawResult& Result)
{
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		setState(StateViewing, i);
	}
	
	return true;
}

bool CtWindowMain::putRequestEvent(const CtEventRequest& Request)
{
	if (isViewing(0) == false)
		return false;
	
	if (handleRequestEvent(Request) == true)
		return true;

	return false;
}

bool CtWindowMain::handleKeyEvent(const CtEventKey& Event)
{
	return false;
}

bool CtWindowMain::handleTouchEvent(const CtEventTouch& Event)
{
	return false;
}

bool CtWindowMain::handleParamEvent(const CtEventParam& Event)
{
	return false;
}

bool CtWindowMain::handleTimerEvent(const CtEventTimer& Event)
{
	return false;
}

bool CtWindowMain::handleFlashEvent(const CtEventFlash& Event)
{
	return false;
}

bool CtWindowMain::handleButtonEvent(const CtEventButton& Event)
{
	return false;
}

bool CtWindowMain::handleWidgetEvent(const CtEventWidget& Widget)
{
	return false;
}

bool CtWindowMain::handleRequestEvent(const CtEventRequest& Request)
{
	return false;
}

bool CtWindowMain::cancelPressing()
{
	bool bRet = false;
	
	if (m_pWindow == NULL)
		return bRet;
	
	if (m_pWindow->cancelPressing() == true) {
		bRet = true;
	}

	return bRet;
}

bool CtWindowMain::updateContents()
{
	return false;
}

bool CtWindowMain::haveWindow(CtScreenSel ScreenSel) const
{
	if (m_pWindow == NULL)
		return false;

	if (ScreenSel & m_WindowInfo.ScreenSel)
		return true;
	
	return false;
}

bool CtWindowMain::setInvalidate()
{
	if (m_pWindow == NULL)
		return false;
	
	return m_pWindow->setInvalidate();
}

bool CtWindowMain::isInvalidate() const
{
	if (m_pWindow == NULL)
		return false;

	return m_pWindow->isInvalidate();
}

bool CtWindowMain::getInvalidates(CtWidget::RegionArray& _Array, int Screen)
{
	if (m_pWindow == NULL)
		return false;

	return m_pWindow->getInvalidates(_Array, Screen);
}

bool CtWindowMain::clearInvalidates(int Screen)
{
	if (m_pWindow == NULL)
		return false;
	
	return m_pWindow->clearInvalidates(Screen);
}

bool CtWindowMain::draw(const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	
	if (m_pWindow == NULL)
		return false;

	if (isVisible() != true)
		return false;
	
	CtRegion WinClip = getWindowClip(Screen);
	WinClip &= Clip;
	
	if (WinClip.isValid() != true)
		return bRet;
	
	if (m_pWindow->draw(WinClip, Screen) == true) {
		bRet = true;

		switch (getState(Screen)) {
		case StateDrawing:
		case StateViewing:
			break;
		default:
			setState(StateDrawing, Screen);
			break;
		}
	}
	
	return bRet;
}

bool CtWindowMain::updated(int Screen)
{
	bool bRet = false;
	
	switch (getState(Screen)) {
	case StateDrawing:
	case StateViewing:
		setState(StateViewing, Screen);
		bRet = true;
		break;
	default:
		break;
	}
	return bRet;
}


bool CtWindowMain::setTransView(bool bTrans)
{
	if (m_WindowInfo.TransView == bTrans)
		return false;
	
	m_WindowInfo.TransView = bTrans;
	return true;
}

bool CtWindowMain::isTransView() const
{
	if ((m_WindowInfo.TransView == true) ||
		((m_pWindow != NULL) && (m_pWindow->getColor().isTransColor() == false)))
		return true;
	
	return false;
}

bool CtWindowMain::setFocusSilent(bool bSilent)
{
	if (m_WindowInfo.FocusSilent != bSilent)
		m_WindowInfo.FocusSilent = bSilent;

	return true;
}

bool CtWindowMain::setState(CtWindowMain::State State, int Screen)
{
	if (m_WindowState[Screen] == State)
		return false;

	m_WindowState[Screen] = State;
	return true;
}

bool CtWindowMain::setAlive(bool bAlive)
{
	State state;
	
	if (bAlive == true)	state = StateAlive;
	else				state = StateInvalid;
	
	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_WindowState[i] = state;
	}
	return true;
}

CtWindowMain::State CtWindowMain::getState(int Screen)
{
	return m_WindowState[Screen];
}

bool CtWindowMain::isViewing(int Screen) const
{
	if (m_WindowState[Screen] >= StateViewing)
		return true;
	
	return false;
}

bool CtWindowMain::isDrawing(int Screen) const
{
	if (m_WindowState[Screen] == StateDrawing)
		return true;

	return false;
}

bool CtWindowMain::isAlive() const
{
	if (m_pWindow == NULL)
		return false;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		if (m_WindowState[i] >= StateAlive)
			return true;
	}
	return false;
}

bool CtWindowMain::setWindowClip(const CtRegion& Clip, int Screen)
{
	if (m_WindowClip[Screen] == Clip)
		return false;
	
	m_WindowClip[Screen] = Clip;
	return true;
}

CtRegion CtWindowMain::getWindowClip(int Screen)
{
	return m_WindowClip[Screen];
}

bool CtWindowMain::setVisible(bool bVisible)
{
	if (m_bVisible == bVisible)
		return false;

	m_bVisible = bVisible;
	setInvalidate();
	
	return true;
}

bool CtWindowMain::isVisible() const
{
	return m_bVisible;
}

bool CtWindowMain::startupContainer()
{
	bool bRet = false;
	CtWidget::List widget_list;

	if (m_pWindow == NULL)
		return bRet;

	for (int i = 0; i < CT_SCREEN_NUM; i++) {
		m_pWindow->getWidgets(CtLayout::Registered, &widget_list, WidgetLayout, i);
	}
	for (CtWidget::ListItr Widget = widget_list.begin(); Widget != widget_list.end(); ++Widget) {
		if((*Widget)->isLayout() != true)
			continue;
		
		CtContainer* pContainer = (*Widget)->getContainer();
		if (pContainer == NULL)
			continue;
		
		if (addContainer(pContainer) == true) {
			if (pContainer->isAlive() != true) {
				pContainer->initialFastDraw();
				pContainer->startup();
			}
			bRet = true;
		}
	}
	return bRet;
}

bool CtWindowMain::terminateContainer()
{
	CtContainer* pContainer;
	
	for (int i = 0; i < m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		pContainer->destroy();
	}
	m_Containers.erase(m_Containers.begin(), m_Containers.end());
	return true;
}


bool CtWindowMain::addContainer(CtContainer* pContainer)
{
	bool bRet = false;
	
	if (pContainer == NULL)
		return bRet;
	
	CtContainer::ArrayItr Itr = m_Containers.find(m_Containers.begin(), m_Containers.end(), pContainer);
	if (Itr == m_Containers.end()) {
		m_Containers.push_back(pContainer);
		bRet = true;
	}
	
	return bRet;
}

bool CtWindowMain::removeContainer(CtContainer* pContainer)
{
	bool bRet = false;

	if (pContainer == NULL)
		return bRet;
	
	CtContainer::ArrayItr Itr = m_Containers.find(m_Containers.begin(), m_Containers.end(), pContainer);
	if (Itr != m_Containers.end()) {
		pContainer->cleanupFastDraw();
		m_Containers.erase(Itr);
		bRet = true;
	}
	
	return bRet;
}

bool CtWindowMain::getInvalidatesFast(CtWidget::RegionArray& _Array, int Screen)
{
	bool bRet = false;
	CtContainer* pContainer;
	CtLayout* pLayout;

	if (isAlive() != true)
		return false;
	
	for (int i = 0; i< m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if ((pContainer->haveFastDraw() != true) || (pContainer->isViewing() != true))
			continue;

		if ((pLayout = pContainer->getLayout()) != NULL) {
			if (pLayout->getInvalidates(_Array, Screen) == true)
				bRet = true;
		}
	}

	return bRet;
}

bool CtWindowMain::clearInvalidatesFast(int Screen)
{
	bool bRet = false;
	CtContainer* pContainer;
	CtLayout* pLayout;
	
	if (isAlive() != true)
		return false;
	
	for (int i = 0; i< m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if ((pContainer->haveFastDraw() != true) || (pContainer->isViewing() != true))
			continue;

		if ((pLayout = pContainer->getLayout()) != NULL) {
			if (pLayout->clearInvalidates(Screen) == true)
				bRet = true;
		}
	}

	return bRet;
}

bool CtWindowMain::updateFastDraw(unsigned long FrameCount)
{
	CtContainer* pContainer = NULL;

	if ((isViewing(0) != true) && (isViewing(1) != true))
		return false;
	
	if (isVisible() != true)
		return false;
	
	if (m_FrameCount == FrameCount)
		return m_bFastUpdated;
	else {
		m_FrameCount = FrameCount;
		m_bFastUpdated = false;
	}
	
	for (int i = 0; i< m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if ((pContainer->haveFastDraw() != true) || (pContainer->isViewing() != true))
			continue;
		
		if (pContainer->updateFastDraw() != true)
			continue;

		m_bFastUpdated = true;
	}
		
	return m_bFastUpdated;
}

bool CtWindowMain::drawFast(const CtRegion& Clip, int Screen)
{
	bool bRet = false;
	CtContainer* pContainer = NULL;
	CtLayout* pLayout = NULL;
	
	if ((isViewing(0) != true) && (isViewing(1) != true))
		return false;
	
	if (m_pWindow == NULL)
		return false;

	if (isVisible() != true)
		return false;
	
	for (int i = 0; i< m_Containers.size(); i++) {
		if ((pContainer = m_Containers[i]) == NULL)
			continue;
		if ((pContainer->haveFastDraw() != true) || (pContainer->isViewing() != true))
			continue;

		if (pContainer->draw(Clip, Screen) == true)
				bRet = true;
	}

	
	// 高速描画の無いWindowはそのまま描画
	if (bRet != true) {
		CtColor Color = m_pWindow->getColor();
		if (Color.RGBA & 0x000000ff) {
			draw(Clip, Screen);
		}
	}
	
	return bRet;
}


void CtWindowMain::outputOutline(int Screen) const
{
	CtDebugPrint(CtDbg, "----- [CtWindowMain] %p Screen:%d --------------------------\n\n", this, Screen);
	m_pWindow->outputOutline(0, NULL, Screen);
	CtDebugPrint(CtDbg, "------------------------------------------------------------\n\n");
}
