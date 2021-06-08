/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#include "CtRecViewModeCheck.h"

#define CT_TEST_MODE_CHECK

CtRecViewModeCheck::CtRecViewModeCheck(CtWindowContents *pContents) :
	m_pWin(NULL),
	m_pAll(NULL),
	m_pStkModeChk(NULL) {
	APL_PARAM_SET_CACHE_DATA(AplParamWFM, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_CACHE_DATA(AplParamLcdFocusExpandUserSw, APL_SYS_PARAM_SWITCH_OFF);
}

CtRecViewModeCheck::~CtRecViewModeCheck()
{
	destroyWindow();
}

CtWindow* CtRecViewModeCheck::createWindow()
{
	m_pAll = new CtLayout(CtColor::Trans);

	m_pStkModeChk = new CtStackLabel();
	{
		m_pStatus = new CtModeCheckStatus();
		m_pStkModeChk->addContainer(m_pStatus);

		m_pFunction = new CtModeCheckFunction();
		m_pStkModeChk->addContainer(m_pFunction);

		m_pAudio = new CtModeCheckAudio();
		m_pStkModeChk->addContainer(m_pAudio);

		m_pSwitch = new CtModeCheckSwitch();
		m_pStkModeChk->addContainer(m_pSwitch);

		m_pNetWork = new CtModeCheckNetwork();
		m_pStkModeChk->addContainer(m_pNetWork);

	}
	m_pAll->addWidget(m_pStkModeChk);

	// Window
	m_pWin = new CtWindow();
	m_pWin->addWidget(m_pAll);
	m_pWin->setVisible(true);

	return m_pWin;
}

bool CtRecViewModeCheck::startupWindow() {
	CtTimer::getInstance()->setAlarm(CT_TIMER_ID_MODE_CHECK, 5000, this);
	CtEventInterface::requestFuncCmd(FuncID_ModeCheckDispOn, m_pWin, NULL);
	return m_pStkModeChk->index(0);
}

bool CtRecViewModeCheck::destroyWindow()
{
	CtTimer::getInstance()->cancelAlarm(CT_TIMER_ID_MODE_CHECK, this);
	CtEventInterface::requestFuncCmd(FuncID_ModeCheckDispOff, m_pWin, NULL);
	APL_PARAM_SET_DATA(AplParamLcdFocusExpandUserSw, APL_PARAM_GET_MASTER_DATA(AplParamLcdFocusExpandUserSw));
	APL_PARAM_SET_DATA(AplParamWFM, APL_PARAM_GET_MASTER_DATA(AplParamWFM));
	return true;
}

bool CtRecViewModeCheck::handleButtonEvent(const CtEventButton& Button)
{
	return false;
}

bool CtRecViewModeCheck::handleTimerEvent(const CtEventTimer& Timer) {
	switch (Timer.getTimeUid()) {
	case CT_TIMER_ID_MODE_CHECK:
		CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowCategory_RecInfo);
		return true;
	default:
		return false;
		break;
	}
}

bool CtRecViewModeCheck::handleKeyEvent(const CtEventKey& Key) {
	if (Key.getKeyAction() == CtEventKey::Press) {
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Exit:
			// ModeCheck‰æ–Ê•Â‚¶‚é
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowCategory_RecInfo);
			return true;
			break;
		case CtEventKey::KeyCode_DispCheck:
			// Žõ–½‚ð‰„‚Î‚·
			//CtTimer::getInstance()->setAlarm(CT_TIMER_ID_MODE_CHECK, 5000, this);
			if (m_pStkModeChk->inc() != true) CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowCategory_RecInfo);
			else if (m_pStkModeChk->getIndex() != 0) {
				m_pStatus->setHide();
				setTransView(true);
			}
			return true;
		default:
			break;
		}
	}
	else if (Key.getKeyAction() == CtEventKey::RepeatPress) {
		switch (Key.getKeyCode()) {
			case CtEventKey::KeyCode_DispCheck:
				CtTimer::getInstance()->setAlarm(CT_TIMER_ID_MODE_CHECK, 5000, this);
				return false;
				break;
			default:
				break;
		}
	}
	else if (Key.getKeyAction() == CtEventKey::Release) {
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Exit:
			// shortpress
			break;
		case CtEventKey::KeyCode_DispCheck:
			CtTimer::getInstance()->setAlarm(CT_TIMER_ID_MODE_CHECK, 5000, this);
			return false;
		default:
			break;
		}
	}

	return false;
}

bool CtRecViewModeCheck::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();
	if (t_Id == AplParamLcdSw) {
		if (int_Data == APL_SYS_PARAM_LCD_SW_MIRROR) {
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowCategory_RecInfo);
		}
	}
	return false;
}
