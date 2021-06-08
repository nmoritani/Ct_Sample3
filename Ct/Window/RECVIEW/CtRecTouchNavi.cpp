/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#include "CtRecTouchNavi.h"
#include "CtParameterConvIf.h"
#include "CtStyle.h"
 /*

 残課題：ボタン文言、シーンボタンフォーカス枠

 */

CtRecTouchNavi::CtRecTouchNavi() :
	m_pAll(NULL),
	m_pPreScene(NULL),
	m_pSceneFile1(NULL),
	m_pSceneFile2(NULL),
	m_pSceneFile3(NULL),
	m_pSceneFile4(NULL),
	m_pSceneFile5(NULL),
	m_pSceneFile6(NULL),
	m_pUser8(NULL),
	m_pUser9(NULL),
	m_pUser10(NULL),
	m_pUser11(NULL),
	m_pUser12(NULL),
	m_bOpenFirstPressFlg(false)
{
	//setPostEvent(EventTouch);
}

CtRecTouchNavi::~CtRecTouchNavi()
{
	m_pPreScene = NULL;
}

CtWindow* CtRecTouchNavi::createWindow()
{
	m_fSet_Center = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::White);
	m_fSet_Center.edgeColor = CtColor::NoColor;


	m_pAll = new CtVLayout();
	{
		CtLayout* pSceneBtns = createSceneBtns();
		CtLayout* pUserBtns = createUserBtns();

		m_pAll->addStretch(1, ScreenLCD);
		m_pAll->addWidget(pSceneBtns, 2);
		m_pAll->addStretch(1);

		CtHLayout* pUserLayout = new CtHLayout();
		{
			pUserLayout->addStretch(1);
			pUserLayout->addWidget(pUserBtns, 16);
			pUserLayout->addStretch(35);
		}
		m_pAll->addWidget(pUserLayout, 9);
		m_pAll->addStretch(1, ScreenLCD);
	}

	CtWindow* pWin = new CtWindow();
	pWin->addWidget(m_pAll);
	pWin->setVisible(true);
	pWin->setRoundFocus(true);
	setTransView(true);

	switch (APL_PARAM_GET_DATA(AplParamSceneMode)) {
	case APL_SYS_PARAM_SCENE_MODE_1:
		pWin->setDefaultFocus(m_pSceneFile1);
		break;
	case APL_SYS_PARAM_SCENE_MODE_2:
		pWin->setDefaultFocus(m_pSceneFile2);
		break;
	case APL_SYS_PARAM_SCENE_MODE_3:
		pWin->setDefaultFocus(m_pSceneFile3);
		break;
	case APL_SYS_PARAM_SCENE_MODE_4:
		pWin->setDefaultFocus(m_pSceneFile4);
		break;
	case APL_SYS_PARAM_SCENE_MODE_5:
		pWin->setDefaultFocus(m_pSceneFile5);
		break;
	case APL_SYS_PARAM_SCENE_MODE_6:
		pWin->setDefaultFocus(m_pSceneFile6);
		break;
	default:
		break;
	}
	return pWin;
}


CtLayout* CtRecTouchNavi::createSceneBtns() {
	CtHLayout* pSceneBtns = new CtHLayout();

	CtVLayout* pScene1Layout = new CtVLayout();
	{	// F1:
		char ScName[AplParamSceneFileName_Size] = { 0 };
		APL_PARAM_GET_DATA_AREA(AplParamSceneFileName_S1, (unsigned char *)ScName, AplParamSceneFileName_Size);
		CtLabel* pScene1Label = new CtLabel(STR_ID_NO_6588, m_fSet_Center);
		m_pSceneFileName1 = new CtLabel(ScName, m_fSet_Center);
		pScene1Layout->addWidget(pScene1Label);
		pScene1Layout->addWidget(m_pSceneFileName1);
	}

	CtVLayout* pScene2Layout = new CtVLayout();
	{
		char ScName[AplParamSceneFileName_Size] = { 0 };
		APL_PARAM_GET_DATA_AREA(AplParamSceneFileName_S2, (unsigned char *)ScName, AplParamSceneFileName_Size);
		CtLabel* pScene2Label = new CtLabel(STR_ID_NO_6590, m_fSet_Center);
		m_pSceneFileName2 = new CtLabel(ScName, m_fSet_Center);
		pScene2Layout->addWidget(pScene2Label);
		pScene2Layout->addWidget(m_pSceneFileName2);
	}

	CtVLayout* pScene3Layout = new CtVLayout();
	{
		char ScName[AplParamSceneFileName_Size] = { 0 };
		APL_PARAM_GET_DATA_AREA(AplParamSceneFileName_S3, (unsigned char *)ScName, AplParamSceneFileName_Size);
		CtLabel* pScene3Label = new CtLabel(STR_ID_NO_6592, m_fSet_Center);
		m_pSceneFileName3 = new CtLabel(ScName, m_fSet_Center);
		pScene3Layout->addWidget(pScene3Label);
		pScene3Layout->addWidget(m_pSceneFileName3);
	}

	CtVLayout* pScene4Layout = new CtVLayout();
	{
		char ScName[AplParamSceneFileName_Size] = { 0 };
		APL_PARAM_GET_DATA_AREA(AplParamSceneFileName_S4, (unsigned char *)ScName, AplParamSceneFileName_Size);

		CtLabel* pScene4Label = new CtLabel(STR_ID_NO_6594, m_fSet_Center);
		m_pSceneFileName4 = new CtLabel(ScName, m_fSet_Center);
		pScene4Layout->addWidget(pScene4Label);
		pScene4Layout->addWidget(m_pSceneFileName4);
	}

	CtVLayout* pScene5Layout = new CtVLayout();
	{
		char ScName[AplParamSceneFileName_Size] = { 0 };
		APL_PARAM_GET_DATA_AREA(AplParamSceneFileName_S5, (unsigned char *)ScName, AplParamSceneFileName_Size);

		CtLabel* pScene5Label = new CtLabel(STR_ID_NO_6596, m_fSet_Center);
		m_pSceneFileName5 = new CtLabel(ScName, m_fSet_Center);
		pScene5Layout->addWidget(pScene5Label);
		pScene5Layout->addWidget(m_pSceneFileName5);
	}

	CtVLayout* pScene6Layout = new CtVLayout();
	{
		char ScName[AplParamSceneFileName_Size] = { 0 };
		APL_PARAM_GET_DATA_AREA(AplParamSceneFileName_S6, (unsigned char *)ScName, AplParamSceneFileName_Size);

		CtLabel* pScene6Label = new CtLabel(STR_ID_NO_6598, m_fSet_Center);
		m_pSceneFileName6 = new CtLabel(ScName, m_fSet_Center);
		pScene6Layout->addWidget(pScene6Label);
		pScene6Layout->addWidget(m_pSceneFileName6);
	}

	pSceneBtns->addStretch(1);
	CtSize BtnAutoSize = CtSize(0, 0);

	m_pSceneFile1 = new CtToggleButton(BtnAutoSize, CtToggleButton::Stroke);
	{
		m_pSceneFile1->setTop(pScene1Layout);
		m_pSceneFile1->setButtonShape(CtButton::RoundRect, 3);
		m_pSceneFile1->setAutoSelectMode(false);
	}
	pSceneBtns->addWidget(m_pSceneFile1, 7);
	pSceneBtns->addStretch(2);

	m_pSceneFile2 = new CtToggleButton(BtnAutoSize, CtToggleButton::Stroke);
	{
		m_pSceneFile2->setTop(pScene2Layout);
		m_pSceneFile2->setButtonShape(CtButton::RoundRect, 3);
		m_pSceneFile2->setAutoSelectMode(false);
	}
	pSceneBtns->addWidget(m_pSceneFile2, 7);
	pSceneBtns->addStretch(2);

	m_pSceneFile3 = new CtToggleButton(BtnAutoSize, CtToggleButton::Stroke);
	{
		m_pSceneFile3->setTop(pScene3Layout);
		m_pSceneFile3->setButtonShape(CtButton::RoundRect, 3);
		m_pSceneFile3->setAutoSelectMode(false);
	}
	pSceneBtns->addWidget(m_pSceneFile3, 7);
	pSceneBtns->addStretch(2);

	m_pSceneFile4 = new CtToggleButton(BtnAutoSize, CtToggleButton::Stroke);
	{
		m_pSceneFile4->setTop(pScene4Layout);
		m_pSceneFile4->setButtonShape(CtButton::RoundRect, 3);
		m_pSceneFile4->setAutoSelectMode(false);
	}
	pSceneBtns->addWidget(m_pSceneFile4, 7);
	pSceneBtns->addStretch(2);

	m_pSceneFile5 = new CtToggleButton(BtnAutoSize, CtToggleButton::Stroke);
	{
		m_pSceneFile5->setTop(pScene5Layout);
		m_pSceneFile5->setButtonShape(CtButton::RoundRect, 3);
		m_pSceneFile5->setAutoSelectMode(false);
	}
	pSceneBtns->addWidget(m_pSceneFile5, 7);
	pSceneBtns->addStretch(2);

	m_pSceneFile6 = new CtToggleButton(BtnAutoSize, CtToggleButton::Stroke);
	{
		m_pSceneFile6->setTop(pScene6Layout);
		m_pSceneFile6->setButtonShape(CtButton::RoundRect, 3);
		m_pSceneFile6->setAutoSelectMode(false);
	}
	pSceneBtns->addWidget(m_pSceneFile6, 7);
	pSceneBtns->addStretch(1);

	m_pPreScene = m_pSceneFile6;

	return pSceneBtns;
}

CtLayout* CtRecTouchNavi::createUserBtns() {
	CtVLayout* pUserBtns = new CtVLayout();

	m_fSet_Center = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::White);
	m_fSet_Center.edgeColor = CtColor::NoColor;

	CtSize sizeUserBtn = CtSize(0, 0);// AutoSize

	m_pUser8Func = new CtLabel(getUserFuncNameStrId(APL_PARAM_GET_DATA(AplParamUserButton8)), m_fSet_Center);
	m_pUser9Func = new CtLabel(getUserFuncNameStrId(APL_PARAM_GET_DATA(AplParamUserButton9)), m_fSet_Center);
	m_pUser10Func = new CtLabel(getUserFuncNameStrId(APL_PARAM_GET_DATA(AplParamUserButton10)), m_fSet_Center);
	m_pUser11Func = new CtLabel(getUserFuncNameStrId(APL_PARAM_GET_DATA(AplParamUserButton11)), m_fSet_Center);
	m_pUser12Func = new CtLabel(getUserFuncNameStrId(APL_PARAM_GET_DATA(AplParamUserButton12)), m_fSet_Center);


	m_pUser8 = new CtButton(sizeUserBtn);
	{
		m_pUser8->setTop(m_pUser8Func, CtMargin(6, 10));
		m_pUser8->setButtonStyleChange();
	}
	pUserBtns->addWidget(m_pUser8, 4);
	pUserBtns->addStretch(2);

	m_pUser9 = new CtButton(sizeUserBtn);
	{
		m_pUser9->setTop(m_pUser9Func, CtMargin(6, 10));
		m_pUser9->setButtonStyleChange();
	}
	pUserBtns->addWidget(m_pUser9, 4);
	pUserBtns->addStretch(2);

	m_pUser10 = new CtButton(sizeUserBtn);
	{
		m_pUser10->setTop(m_pUser10Func, CtMargin(6, 10));
		m_pUser10->setButtonStyleChange();
	}
	pUserBtns->addWidget(m_pUser10, 4);
	pUserBtns->addStretch(2);

	m_pUser11 = new CtButton(sizeUserBtn);
	{
		m_pUser11->setTop(m_pUser11Func, CtMargin(6, 10));
		m_pUser11->setButtonStyleChange();
	}
	pUserBtns->addWidget(m_pUser11, 4);
	pUserBtns->addStretch(2);

	m_pUser12 = new CtButton(sizeUserBtn);
	{
		m_pUser12->setTop(m_pUser12Func, CtMargin(6, 10));
		m_pUser12->setButtonStyleChange();
	}
	pUserBtns->addWidget(m_pUser12, 4);

	return pUserBtns;
}

bool CtRecTouchNavi::startupWindow() {
	return restartWindow();
}

bool CtRecTouchNavi::restartWindow() {
	setTimeLimit(true);
	updateSceneBtns(APL_PARAM_GET_DATA(AplParamSceneMode));
	return true;
}

bool CtRecTouchNavi::setVisible(bool bVisible) {
	return m_pAll->setVisible(bVisible);
}

bool CtRecTouchNavi::isVisible() {
	return m_pAll->isVisible();
}

void CtRecTouchNavi::setTimeLimit(bool bSet) {
	if (bSet) {
		CtTimer::getInstance()->setAlarm(CT_TIMER_ID_TOUCH_NAVI_TIME, 5000, this);
	}
	else {
		CtTimer::getInstance()->cancelAlarm(CT_TIMER_ID_TOUCH_NAVI_TIME, this);
	}
}

bool CtRecTouchNavi::handleTimerEvent(const CtEventTimer& Timer) {
	switch (Timer.getTimeUid()) {
	case CT_TIMER_ID_TOUCH_NAVI_TIME:
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, Window_TouchNavi);
		return true;
		break;
	default:
		break;
	}
	return false;
}

bool CtRecTouchNavi::handleTouchEvent(const CtEventTouch& Touch) {
	// アイコン以外にEventがあった
	if (Touch.getAction() == CtEventTouch::Press) {
		m_bOpenFirstPressFlg = true;
		setPostEvent(EventTouch);

		//Timer停止
		setTimeLimit(false);
		return false;
	} else if (m_bOpenFirstPressFlg == true && Touch.getAction() == CtEventTouch::Release) {
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, Window_TouchNavi);
		return true;
	}
	if (m_bOpenFirstPressFlg == false) {
		return true;
	}
	return false;
}

bool CtRecTouchNavi::handleButtonEvent(const CtEventButton& Button)
{
	if (Button.getPressType() == CtEventButton::PressInvalid) {
		return false;
	}
	// アイコンにEventがあった
	if (Button.getPressType() == CtEventButton::ShortPress || Button.getPressType() == CtEventButton::LongPress) {
		m_bOpenFirstPressFlg = true;
		// 期間延長
		setTimeLimit(true);
	}
	else if (Button.getPressType() == CtEventButton::Release) {
		// 期間延長
		setTimeLimit(true);
		if (m_bOpenFirstPressFlg == false) {
			return false;
		}
	}

	if (m_pSceneFile1 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_TOUCH_NAVI_SCENE1);
			return true;
		}
		return false;
	}
	else if (m_pSceneFile2 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_TOUCH_NAVI_SCENE2);
			return true;
		}
		return false;
	}
	else if (m_pSceneFile3 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_TOUCH_NAVI_SCENE3);
			return true;
		}
		return false;
	}
	else if (m_pSceneFile4 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_TOUCH_NAVI_SCENE4);
			return true;
		}
		return false;
	}
	else if (m_pSceneFile5 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_TOUCH_NAVI_SCENE5);
			return true;
		}
		return false;
	}
	else if (m_pSceneFile6 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_TOUCH_NAVI_SCENE6);
			return true;
		}
		return false;
	}
	else if (m_pUser8 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER8_Press);
		}
		else if (Button.getPressType() == CtEventButton::Release) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER8_Release);
		}
		return true;
	}
	else if (m_pUser9 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER9_Press);
		}
		else if (Button.getPressType() == CtEventButton::Release) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER9_Release);
		}
		return true;
	}
	else if (m_pUser10 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER10_Press);
		}
		else if (Button.getPressType() == CtEventButton::Release) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER10_Release);
		}
		return true;
	}
	else if (m_pUser11 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER11_Press);
		}
		else if (Button.getPressType() == CtEventButton::Release) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER11_Release);
		}
		return true;
	}
	else if (m_pUser12 == Button.getWidget()) {
		if (Button.getPressType() == CtEventButton::ShortPress) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER12_Press);
		}
		else if (Button.getPressType() == CtEventButton::Release) {
			CtEventInterface::requestFuncCmd(Window_TouchNavi, FuncID_USER12_Release);
		}
		return true;
	}
	return false;
}

bool CtRecTouchNavi::handleKeyEvent(const CtEventKey& Key) {
	if (isVisible() == false) return false;

	if (Key.getKeyAction() == CtEventKey::Press) {
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_MmrMinus:
		case CtEventKey::KeyCode_MmrPlus:
		case CtEventKey::KeyCode_ManualFunction:
			// フォーカス遷移
			return false;
			break;
		case CtEventKey::KeyCode_Enter:
		case CtEventKey::KeyCode_Right:

			// Dial/Touchのみ
			return false;
		case CtEventKey::KeyCode_Up:
			if (m_pUser8->isFocused() == true) {
				m_pSceneFile1->setFocus();
				return true;
			}
			else if (m_pSceneFile4->isFocused() == true) {
				m_pUser12->setFocus();
				return true;
			}
			else if (m_pSceneFile5->isFocused() == true) {
				m_pUser12->setFocus();
				return true;
			}
			else if (m_pSceneFile6->isFocused() == true) {
				m_pUser12->setFocus();
				return true;
			}
			return false;
		case CtEventKey::KeyCode_Down:
			if (m_pUser12->isFocused() == true) {
				m_pSceneFile1->setFocus();
				return true;
			}
			return false;
		case CtEventKey::KeyCode_Left:
			if (m_pUser8->isFocused()
				|| m_pUser9->isFocused()
				|| m_pUser10->isFocused()
				|| m_pUser11->isFocused()
				|| m_pUser12->isFocused()) {
				m_pSceneFile6->setFocus();
				return true;
			}
			break;
		case CtEventKey::KeyCode_Exit:
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, Window_TouchNavi);
			return true;
			break;
		default:
			break;
		}
	}
	else if (Key.getKeyAction() == CtEventKey::Release) {
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_MmrMinus:
		case CtEventKey::KeyCode_MmrPlus:
		case CtEventKey::KeyCode_ManualFunction:
			// 期間延長
			setTimeLimit(true);
			// フォーカス遷移
			return false;
			break;
		case CtEventKey::KeyCode_Enter:
		case CtEventKey::KeyCode_Right:
		case CtEventKey::KeyCode_Left:
		case CtEventKey::KeyCode_Up:
		case CtEventKey::KeyCode_Down:
			// Dial/Touchのみ
			setTimeLimit(true);
			return false;
		case CtEventKey::KeyCode_Exit:
			return true;
		case CtEventKey::KeyCode_DispCheck:
			// 短押し
			if (APL_PARAM_GET_DATA(AplParamDispModeCheck) == APL_SYS_PARAM_SWITCH_ON) {
				APL_PARAM_SET_DATA(AplParamDispModeCheck, APL_SYS_PARAM_SWITCH_OFF);
			}
			else {
				APL_PARAM_SET_DATA(AplParamDispModeCheck, APL_SYS_PARAM_SWITCH_ON);
			}
			return true;
		default:
			break;
		}
	}

	return false;
}

bool CtRecTouchNavi::handleParamEvent(const CtEventParam& Param)
{
	if (isVisible() == false) return false;

	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamUserButton8:
	case AplParamUserButton9:
	case AplParamUserButton10:
	case AplParamUserButton11:
	case AplParamUserButton12:
		updateUserBtns(t_Id, int_Data);
		return true;
	case AplParamSceneMode:
		updateSceneBtns(int_Data);
		return true;
	case AplParamSceneFileName_S1:
	case AplParamSceneFileName_S2:
	case AplParamSceneFileName_S3:
	case AplParamSceneFileName_S4:
	case AplParamSceneFileName_S5:
	case AplParamSceneFileName_S6:
		updateSceneFileName(t_Id);
		return true;
	case AplParamLcdSw:
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, Window_TouchNavi);
		return true;
	default:
		break;
	}

	return false;
}
bool CtRecTouchNavi::updateSceneBtns(int currentSceneNo) {
	CtToggleButton* pUpdateScnFile = NULL;

	// Focus枠設定
	switch (currentSceneNo) {
	case APL_SYS_PARAM_SCENE_MODE_1:
		pUpdateScnFile = m_pSceneFile1;
		break;
	case APL_SYS_PARAM_SCENE_MODE_2:
		pUpdateScnFile = m_pSceneFile2;
		break;
	case APL_SYS_PARAM_SCENE_MODE_3:
		pUpdateScnFile = m_pSceneFile3;
		break;
	case APL_SYS_PARAM_SCENE_MODE_4:
		pUpdateScnFile = m_pSceneFile4;
		break;
	case APL_SYS_PARAM_SCENE_MODE_5:
		pUpdateScnFile = m_pSceneFile5;
		break;
	case APL_SYS_PARAM_SCENE_MODE_6:
		pUpdateScnFile = m_pSceneFile6;
		break;
	default:
		return false;
		break;
	}
	if (pUpdateScnFile != NULL) {
		// 選択状態枠解除
		m_pPreScene->setSelect(false);
		m_pPreScene->setHold(false);
		// 選択状態枠設定
		pUpdateScnFile->setSelect(true);
		pUpdateScnFile->setHold(true);
		m_pPreScene = pUpdateScnFile;
	}
	return true;
}

bool CtRecTouchNavi::updateSceneFileName(int changeSceneNo) {
	char ScName[AplParamSceneFileName_Size] = { 0 };
	APL_PARAM_GET_DATA_AREA(changeSceneNo, (unsigned char *)ScName, AplParamSceneFileName_Size);
	switch (changeSceneNo) {
	case AplParamSceneFileName_S1:
		return m_pSceneFileName1->setText(ScName);
		break;
	case AplParamSceneFileName_S2:
		return m_pSceneFileName2->setText(ScName);
		break;
	case AplParamSceneFileName_S3:
		return m_pSceneFileName3->setText(ScName);
		break;
	case AplParamSceneFileName_S4:
		return m_pSceneFileName4->setText(ScName);
		break;
	case AplParamSceneFileName_S5:
		return m_pSceneFileName5->setText(ScName);
		break;
	case AplParamSceneFileName_S6:
		return m_pSceneFileName6->setText(ScName);
		break;
	default:
		return false;
		break;
	}
}

void CtRecTouchNavi::updateUserBtns(int changeUserNo, int changeUserFuncNo) {
	switch (changeUserNo)
	{
	case APL_SYS_PARAM_USER_SWITCHES_MENU_USER8:
		m_pUser8Func->setStringID(getUserFuncNameStrId(changeUserFuncNo));
		break;
	case APL_SYS_PARAM_USER_SWITCHES_MENU_USER9:
		m_pUser9Func->setStringID(getUserFuncNameStrId(changeUserFuncNo));
		break;
	case APL_SYS_PARAM_USER_SWITCHES_MENU_USER10:
		m_pUser10Func->setStringID(getUserFuncNameStrId(changeUserFuncNo));
		break;
	case APL_SYS_PARAM_USER_SWITCHES_MENU_USER11:
		m_pUser11Func->setStringID(getUserFuncNameStrId(changeUserFuncNo));
		break;
	case APL_SYS_PARAM_USER_SWITCHES_MENU_USER12:
		m_pUser12Func->setStringID(getUserFuncNameStrId(changeUserFuncNo));
		break;
	default:
		break;
	}
}

GDI_STRING_ID CtRecTouchNavi::getUserFuncNameStrId(int UserFuncNo) {

	CtParamConvIf paramConIf;
	return paramConIf.convFromUserParamToStringId(UserFuncNo);
}
