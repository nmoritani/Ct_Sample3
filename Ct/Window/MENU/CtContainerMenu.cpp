/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerMenu.h"
#include "CtAplParam.h"

CtContainerMenu::CtContainerMenu(CtWindowID _id, CtWindowContents* pContents) :
	m_WindowID(_id),
	m_pMenuList(NULL),
	m_pCtrl(NULL),
	m_OldWidth(0),
	m_RetWidth(0),
	m_ParentParam(AplParamIdMax),
	m_ParentValue(0)
{
	if (pContents != NULL) {
		m_OldWidth = ((CtWindowContentsMenuPos*)pContents)->getWidth();
	}
	else {
		m_OldWidth = 126;
	}

	setClassType(CtClassType_LayoutMain);
}
CtContainerMenu::~CtContainerMenu()
{
	destroyContainer();
}
bool CtContainerMenu::destroyContainer()
{
	return true;
}
CtLayout* CtContainerMenu::createContainer()
{
	bool bExit = CtMenuInfo::checkExit(m_WindowID);

	CtMenuBuilder* pBuilder = new CtMenuBuilder();
	pBuilder->setWindowID(m_WindowID);
	pBuilder->setOldWidth(m_OldWidth);
	m_pMenuList = pBuilder->createMenuList(MENU_BUTTON_LINE, bExit);
	short WindowSize = pBuilder->getTotalWidth();
	delete pBuilder;

	CtMenuInfo::getParentId(m_WindowID, m_ParentParam, m_ParentValue);
//	CtDebugPrint(CtDbg,"param = %d , value = %d\n", m_ParentParam, m_ParentValue);

	short leftPos, mainPos, rightPos;
	short hie = CtMenuInfo::getHierarchy(m_WindowID);


	if (hie != 0) {
		leftPos = 126 + ((hie - 1) * 100);	/* pgr0351 */
		mainPos = WindowSize;
		rightPos = 960 - leftPos - WindowSize;	/* pgr0351 */
	}
	else {
		// Pop or Check
		leftPos = (short)m_OldWidth;
		mainPos = WindowSize;
		rightPos = 960 - leftPos - WindowSize;	/* pgr0351 */
	}

	if (rightPos < 20) {
		leftPos = leftPos +(-20 + rightPos);	/* pgr0351 */
		rightPos = 20;
	}

	CtHLayout *pMid = new CtHLayout();
	pMid->addStretch(leftPos);
	pMid->addWidget(m_pMenuList, mainPos);
	pMid->addStretch(rightPos);

	m_pCtrl = new CtContainerCtrlButton(false, true, true, true);
	CtLayout* pAll = new CtLayout();
	pAll->addContainer(m_pCtrl);
	pAll->addWidget(pMid);

	m_RetWidth = leftPos;

	checkPage();

	return pAll;
}

CtListView* CtContainerMenu::getMenuList() const
{
	return m_pMenuList;
}


//----------------------------------------------------------------------------------------------------
// HandleEvent
//----------------------------------------------------------------------------------------------------
bool CtContainerMenu::handleParamEvent(const CtEventParam& Param)
{
	return checkParentState();
}
bool CtContainerMenu::handleButtonEvent(const CtEventButton& Button)
{
	/* Release‚Å‚Ì‚Ýˆ— */
	if ((Button.getPressType() != CtEventButton::Release) &&
		(Button.getPressType() != CtEventButton::RepeatPress)) {
		return false;
	}
	bool bRet = false;
	switch (Button.getWidgetID()){
	case 0:
		break;
	case WidgetID_SET:
		break;
	case WidgetID_UP:
		bRet = m_pMenuList->prevPage();
		checkPage();
		break;
	case WidgetID_DOWN:
		bRet = m_pMenuList->nextPage();
		checkPage();
		break;
	case WidgetID_RET:
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, m_WindowID);
		bRet = true;
		break;
	default:
		break;
	}

	return bRet;
}
bool CtContainerMenu::handleKeyEvent(const CtEventKey& Key)
{
	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Up:
	case CtEventKey::KeyCode_MmrPlus:
		if ((Key.getKeyAction() == CtEventKey::Press) ||
			(Key.getKeyAction() == CtEventKey::RepeatPress)) {
			m_pMenuList->prevElement();
			checkPage();
			return true;
		}
		break;
	case CtEventKey::KeyCode_DialPressUp:
		if (Key.getKeyAction() == CtEventKey::RepeatPress) {
			m_pMenuList->prevElement();
			checkPage();
			return true;
		}
		break;
	case CtEventKey::KeyCode_Down:
	case CtEventKey::KeyCode_MmrMinus:
		if ((Key.getKeyAction() == CtEventKey::Press) ||
			(Key.getKeyAction() == CtEventKey::RepeatPress)) {
			m_pMenuList->nextElement();
			checkPage();
			return true;
		}
		break;
	case CtEventKey::KeyCode_DialPressDown:
		if (Key.getKeyAction() == CtEventKey::RepeatPress) {
			m_pMenuList->nextElement();
			checkPage();
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}
bool CtContainerMenu::handleTouchEvent(const CtEventTouch& Touch)
{
	if (Touch.getAction() == CtEventTouch::Release) {
		short Pos_X = (Touch.getPosition()).m_X;
		short Pos_Y = (Touch.getPosition()).m_Y;
		if (126 < Pos_X && Pos_X < m_RetWidth) {
			CtDebugPrint(CtDbg, "handleTouchEvent [ X = %3d , Y = %3d ]\n", Pos_X, Pos_Y);
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, m_WindowID);
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
void CtContainerMenu::checkPage()
{
	int max = m_pMenuList->getMaxPage();
	int cur = m_pMenuList->getCurrentPage();

	if (cur <= 1) {
		m_pCtrl->setInvalid(WidgetID_UP, true);
	}
	else {
		m_pCtrl->setInvalid(WidgetID_UP, false);
	}

	if (cur >= max) {
		m_pCtrl->setInvalid(WidgetID_DOWN, true);
	}
	else {
		m_pCtrl->setInvalid(WidgetID_DOWN, false);
	}
}
bool CtContainerMenu::checkParentState()
{
	bool bRet = false;

	switch (CtAplParam::getState(m_ParentParam, m_ParentValue)){
	case CtParamState_Invalid:
	case CtParamState_Invisible:
		CtDebugPrint(CtDbg, "CtContainerMenu::checkParentState CloseWindow\n");
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, m_WindowID);
		bRet = true;
		break;
	case CtParamState_Visible:
	case CtParamState_End:
	default:
		break;
	}

	return bRet;
}
