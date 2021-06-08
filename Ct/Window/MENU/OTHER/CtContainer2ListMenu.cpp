/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainer2ListMenu.h"


CtContainer2ListMenu::CtContainer2ListMenu(CtWindowID _id) :
	m_WindowID(_id),
	m_pMenuList(NULL),
	m_pCtrl(NULL)
{
	setClassType(CtClassType_LayoutMain);
}
CtContainer2ListMenu::~CtContainer2ListMenu()
{
	destroyContainer();
}
bool CtContainer2ListMenu::destroyContainer()
{
	return true;
}
CtLayout* CtContainer2ListMenu::createContainer()
{
	/* Title */
	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(m_WindowID);

	/* List */
	CtLayout* pList = createList();

	/* Ctrl */
	m_pCtrl = new CtContainerCtrlButton(false, true, true, true);
	m_pCtrl->setTransColor(true);
	m_pCtrl->setTrans(true);

	CtHLayout* pMain = new CtHLayout();
	pMain->addStretch(126);
	pMain->addWidget(pList, 960 - 126);

	CtColor color = CtMenuInfo::getMenuBackColor();

	CtVLayout *pLayout = new CtVLayout();
	pLayout->addContainer(pTitle, 80);
	pLayout->addWidget(new CtLabel(CtSize(960, 2), CtColor::White), 2);
	pLayout->addWidget(pMain, 640 - 80);

	CtLayout* pAll = new CtLayout(color);
	pAll->addContainer(m_pCtrl);
	pAll->addWidget(pLayout);

	return pAll;
}
bool CtContainer2ListMenu::startupContainer()
{
	m_pMenuList->setCurrentElement(0);
	checkPage();
	return true;
}


//----------------------------------------------------------------------------------------------------
// HandleEvent
//----------------------------------------------------------------------------------------------------
bool CtContainer2ListMenu::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();

	switch (t_Id) {
	case AplParamLanguage:
	{
		return false;
	}
	default:
		break;
	}
	return false;
}
bool CtContainer2ListMenu::handleButtonEvent(const CtEventButton& Button)
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
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
		break;
	default:
		break;
	}

	return bRet;
}
bool CtContainer2ListMenu::handleKeyEvent(const CtEventKey& Key) {
	bool bRet = false;
	switch (Key.getKeyAction()) {
	case CtEventKey::Release:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Exit:
		case CtEventKey::KeyCode_GripUser1:
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
			return true;
		default:
			bRet = checkPage();
			break;
		}
		break;
	default:
		break;
	}
	return bRet;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------

CtLayout* CtContainer2ListMenu::createList()
{
	m_pMenuList = new Ct2ListView(7);
	m_pMenuList->setColumn(2);
	m_pMenuList->setSelectLabel(new CtLabel(CtRect(CtColor::Trans, 2, CtColor(255, 216, 0, 255))), CtMargin(2, 2, 2, 2));
	CtMenuInfo::CtMenuWindowInfo* pInfo = CtMenuInfo::getWindowInfo(m_WindowID);

	if (pInfo != NULL) {
		for (unsigned int i = 0; i < pInfo->child.num; i += 2) {
			CtLayout* pButton = createButton(pInfo->child.id[i]);
			if (pButton == NULL) {
				break;
			}
			m_pMenuList->addWidget(pButton);
		}
	}
//	m_pMenuList->setCurrentElement(0);
//	m_pMenuList->setLeftKeyAction(false);

	return m_pMenuList;
}
CtLayout* CtContainer2ListMenu::createButton(unsigned int index)
{
	CtMenuInfo::CtMenuButtonInfo* pInfoSat = CtMenuInfo::getButtonInfo(index);
	if (pInfoSat == NULL)return NULL;
	CtMenuInfo::CtMenuButtonInfo* pInfoPhase = CtMenuInfo::getButtonInfo(index+1);
	if (pInfoPhase == NULL)return NULL;

	CtHLayout* pLayout = new CtHLayout();

	/* Layout\’z  960                                             */
	/* |     |--|- 519 ---------------|-- 100 --|--|-- 100 --|--|  */
	/* | 126 |15|   Label             |   SAT   |50|  PHASE  |50|  */
	/* |     |__|_____________________|_________|__|_________|__|  */


	/* Stretch */
	{
		pLayout->addStretch(15);
	}

	/* Label */
	{
		CtVLayout* pLabel = new CtVLayout();
		CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor::White);

		pLabel->addStretch(MENU_POP_TOP);
		if (pInfoSat->StringId != STR_ID_MAX_SIZE) {
			pLabel->addWidget(new CtLabel(pInfoSat->StringId, fSet), MENU_POP_LABEL);
		}
		else {
			pLabel->addWidget(new CtLabel(pInfoSat->str, fSet), MENU_POP_LABEL);
		}
		pLabel->addStretch(MENU_POP_BOTTOM);
		pLayout->addWidget(pLabel, AlignLeft, 500);
	}

	/* SAT */
	{
		/* ButtonLabel */
		CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
		CtParamLabel* pParamLabel = new CtParamLabel(pInfoSat->value.id, fSet);
		pParamLabel->setLabelType(CtParamLabel::TypeNumeric);
//		pParamLabel->setFontSet(fSet);
		pParamLabel->setRange(-1, 1);
//		pParamLabel->setCorrection(0, pInfoSat->value.coef);
		pParamLabel->setForm(pInfoSat->value.suffix);

		/* Button */
		CtMenuButton* pButton = new CtMenuButton(AutoSize, pParamLabel, CtButton::Rect);
		pButton->setLinkAction(pInfoSat->action.WindowID, pInfoSat->action.OpenType, NULL);
		pButton->setStateInfo(pInfoSat->exclution.id, pInfoSat->exclution.value);
		pButton->setRightKeyAction(false);
		pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
		pButton->setFocusedButtonColors(CtColor(255, 216, 0, 255), CtColor(255, 216, 0, 255), CtColor(0, 0, 0, 255));
		pButton->setPressedButtonColors(CtColor(255, 216, 0, 255), CtColor(255, 216, 0, 255), CtColor(0, 0, 0, 255));

		/* Layout */
		CtVLayout* pBtn = new CtVLayout();
		pBtn->addStretch(7);
		pBtn->addWidget(pButton, 60);
		pBtn->addStretch(9);

		pLayout->addWidget(pBtn, 100);
	}

	/* Stretch */
	{
		pLayout->addStretch(50);
	}

	/* SAT */
	{
		/* ButtonLabel */
		CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
		CtParamLabel* pParamLabel = new CtParamLabel(pInfoPhase->value.id, fSet);
		pParamLabel->setLabelType(CtParamLabel::TypeNumeric);
//		pParamLabel->setFontSet(fSet);
		pParamLabel->setRange(-1, 1);
//		pParamLabel->setCorrection(0, pInfoPhase->value.coef);
		pParamLabel->setForm(pInfoPhase->value.suffix);

		/* Button */
		CtMenuButton* pButton = new CtMenuButton(AutoSize, pParamLabel, CtButton::Rect);
		pButton->setLinkAction(pInfoPhase->action.WindowID, pInfoPhase->action.OpenType, NULL);
		pButton->setStateInfo(pInfoPhase->exclution.id, pInfoPhase->exclution.value);
		pButton->setRightKeyAction(false);
		pButton->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);
		pButton->setFocusedButtonColors(CtColor(255, 216, 0, 255), CtColor(255, 216, 0, 255), CtColor(0, 0, 0, 255));
		pButton->setPressedButtonColors(CtColor(255, 216, 0, 255), CtColor(255, 216, 0, 255), CtColor(0, 0, 0, 255));

		/* Layout */
		CtVLayout* pBtn = new CtVLayout();
		pBtn->addStretch(7);
		pBtn->addWidget(pButton,60);
		pBtn->addStretch(9);

		pLayout->addWidget(pBtn, 100);
	}

	/* Stretch */
	{
		pLayout->addStretch(50);
	}

	CtLayout* pAll= new CtLayout();
	pAll->addWidget(pLayout);
	pAll->addWidget(new CtLabel(CtLine(UpperLine, 1, CtColor::White)), AlignTop);
	pAll->addWidget(new CtLabel(CtLine(UnderLine, 1, CtColor::White)), AlignBottom);

	return pAll;
}
bool CtContainer2ListMenu::checkPage()
{
	bool bUp = false;
	bool bDown = false;
	int max = m_pMenuList->getMaxPage();
	int cur = m_pMenuList->getCurrentPage();
	CtDebugPrint(CtDbg, "CtContainer2ListMenu::checkPage max %d  cur %d\n", max, cur);
	if (cur <= 1) {
		bUp = m_pCtrl->setInvalid(WidgetID_UP, true);
	}
	else {
		bUp = m_pCtrl->setInvalid(WidgetID_UP, false);
	}

	if (cur >= max) {
		bDown = m_pCtrl->setInvalid(WidgetID_DOWN, true);
	}
	else {
		bDown = m_pCtrl->setInvalid(WidgetID_DOWN, false);
	}
	if (bUp || bDown) {
		return true;
	}
	return false;
}
