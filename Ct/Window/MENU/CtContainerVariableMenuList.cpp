/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:           CtContainerVariableMenuList
 */
#include "CtContainerVariableMenuList.h"

#define LIST_ROW            7

CtContainerVariableMenuList::CtContainerVariableMenuList(CtWindowID id) :
	m_WindowID(id),
	m_pList(NULL),
	m_pPage(NULL),
	m_pCtrl(NULL),
	m_Max(0),
	m_Current(0)
{
}
CtContainerVariableMenuList::~CtContainerVariableMenuList()
{
}
bool CtContainerVariableMenuList::destroyContainer()
{
	return true;
}

CtLayout* CtContainerVariableMenuList::createContainer()
{
	/* Title */
	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(m_WindowID);
	m_pPage = new CtLabel("0/0", CtFontSet(FontTypeNormal_alignRight, CtColor::White));
	pTitle->setPage(m_pPage);

	/* List */
	if (m_pList == NULL) {
		m_pList = new CtMenuListView(LIST_ROW);
		m_Current = 0;
	}
	m_pList->setCurrentElement(m_Current);
	m_pList->setLeftKeyAction(false);

	/* Ctrl */
	m_pCtrl = new CtContainerCtrlButton(false, true, true, true);
	m_pCtrl->setTransColor(true);
	m_pCtrl->setTrans(true);

	CtHLayout* pMain = new CtHLayout();
	pMain->addStretch(126);
	pMain->addWidget(m_pList,960-126);

	CtColor color = CtMenuInfo::getMenuBackColor();

	CtVLayout *pLayout = new CtVLayout();
	pLayout->addContainer(pTitle, 80);
	pLayout->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2);
	pLayout->addWidget(pMain, 640 - 80);

	CtLayout* pAll = new CtLayout(color);
	pAll->addContainer(m_pCtrl);
	pAll->addWidget(pLayout);

	update_PageNo();

    return pAll;
}

void CtContainerVariableMenuList::setCurrentIndex(int index)
{
	m_Current = index;
}

/* ================================================================================== */
/* 前回表示部品を破棄 =============================================================== */
/* ================================================================================== */
void CtContainerVariableMenuList::cleanupList()
{
	CtWidget *pWidget = NULL;
    if( m_Max == 0 ) return;
    if( m_pList == NULL ) return;

#if 1
	m_pList->clear();
#else
    for (unsigned long i = 0; i < m_Max; i++) {
		pWidget = m_pList->getWidget(0);
    	if(pWidget != NULL ){
        	m_pList->removeWidget(pWidget);
    	}
    }
#endif
	m_Max = 0;
}

/* ================================================================================== */
/* List操作 ========================================================================= */
/* ================================================================================== */
void CtContainerVariableMenuList::addButton(CtButton* pButton)
{
	if (pButton == NULL)return;
	if (m_pList == NULL) {
		m_pList = new CtMenuListView(LIST_ROW);
	}
	pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
	m_pList->addWidget(pButton);
	m_Max++;
}
void CtContainerVariableMenuList::updateEnd()
{
	if (m_pList != NULL) {
		m_pList->setCurrentElement(m_Current);
	}
	update_PageNo();
}

/* ================================================================================== */
/* ページ更新・ボタンの排他更新 ===================================================== */
/* ================================================================================== */
void CtContainerVariableMenuList::update_PageNo()
{
	if (m_pList == NULL) return;
	if (m_pPage == NULL) return;
	if (m_pCtrl == NULL) return;

	char str[10];
	int max = m_pList->getMaxPage();
	int cur = m_pList->getCurrentPage();
	int index = m_pList->getCurrentIndex() + 1;
	
	if (max > 0) {
		sprintf(str, "%d/%d", index, m_Max);
	}

	m_pPage->setText(str);

	if (max <= 1) {
		m_pCtrl->setInvalid(WidgetID_UP, true);
		m_pCtrl->setInvalid(WidgetID_DOWN, true);
	}
	else {
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
}

/* ================================================================================== */
/* handleEvent ====================================================================== */
/* ================================================================================== */
bool CtContainerVariableMenuList::handleButtonEvent(const CtEventButton& Button)
{
    bool bFlag = false;

    /* Releaseでのみ処理 */
    if ((Button.getPressType() != CtEventButton::Release) &&
        (Button.getPressType() != CtEventButton::RepeatPress)) {
        return false;
    }


    switch(Button.getWidgetID()) {
    case WidgetID_UP:
        m_pList->prevPage();
        update_PageNo();
        bFlag = true;
        break;
    case WidgetID_DOWN:
        m_pList->nextPage();
        update_PageNo();
        bFlag = true;
        break;
    case WidgetID_RET:
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
		bFlag = true;
        break;
    default:
		break;
    }

    return bFlag;
}

bool CtContainerVariableMenuList::handleKeyEvent(const CtEventKey& Key)
{
    bool bRet = false;
    CtWindow* pWin = NULL;
    
	switch (Key.getKeyCode()) {
	case CtEventKey::KeyCode_Up:
	case CtEventKey::KeyCode_MmrPlus:
		if ((Key.getKeyAction() == CtEventKey::Press) ||
			(Key.getKeyAction() == CtEventKey::RepeatPress)) {
			m_pList->prevElement();
			update_PageNo();
			return true;
		}
		break;
	case CtEventKey::KeyCode_DialPressUp:
		if (Key.getKeyAction() == CtEventKey::RepeatPress) {
			m_pList->prevElement();
			update_PageNo();
			return true;
		}
		break;
	case CtEventKey::KeyCode_Down:
	case CtEventKey::KeyCode_MmrMinus:
		if ((Key.getKeyAction() == CtEventKey::Press) ||
			(Key.getKeyAction() == CtEventKey::RepeatPress)) {
			m_pList->nextElement();
			update_PageNo();
			return true;
		}
		break;
	case CtEventKey::KeyCode_DialPressDown:
		if (Key.getKeyAction() == CtEventKey::RepeatPress) {
			m_pList->nextElement();
			update_PageNo();
			return true;
		}
		break;
	case CtEventKey::KeyCode_Exit:
	case CtEventKey::KeyCode_GripUser1:
		if (Key.getKeyAction() == CtEventKey::Release) {
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
			return true;
		}
		break;
	default:
		break;
	}
	return bRet;
}
