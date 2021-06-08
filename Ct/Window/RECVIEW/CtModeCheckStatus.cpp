/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#include "CtModeCheckStatus.h"
#include "CtICManager.h"
CtModeCheckStatus::CtModeCheckStatus() :
	m_pAll(NULL),
	m_pIpRemote(NULL),
	m_pWarnLine1(NULL),
	m_pWarnLine2(NULL),
	m_pAwbNg(NULL),
	m_pAbbNg(NULL)
{
}

CtModeCheckStatus::~CtModeCheckStatus()
{
	destroyWindow();
}

bool CtModeCheckStatus::destroyWindow()
{
	CtICManager::getInstance()->setStatusMode(false);
	return true;
}

CtLayout* CtModeCheckStatus::createContainer() {

	m_pAll = new CtLayout();
	{
		CtVLayout* pV = new CtVLayout();
		{
			//pV->addStretch(1, ScreenLCD);
			pV->addStretch(4);
			pV->addWidget(createLineWarn(), 2);
			pV->addStretch(2, ScreenLCD);
			pV->addWidget(createLineAwbNg(), 1);
			pV->addWidget(createLineAbbNg(), 1);
			pV->addWidget(createLineIpRemote(), 1);
			pV->addStretch(3);
			
		}
		m_pAll->addWidget(pV);
	}
	return m_pAll;
};

bool CtModeCheckStatus::startupContainer() {
	CtICManager::getInstance()->setStatusMode(true);
	updateWarningState();
	updateAwbNg(AplParamAWBErrInfo, APL_PARAM_GET_DATA(AplParamAWBErrInfo));
	updateAbbNg(AplParamABBErrInfo, APL_PARAM_GET_DATA(AplParamABBErrInfo));
	updateIpRemote(AplParamIpRemoteStatus, APL_PARAM_GET_DATA(AplParamIpRemoteStatus));
	return true;
}
bool CtModeCheckStatus::setHide() {
	return CtICManager::getInstance()->setStatusMode(false);
}

bool CtModeCheckStatus::handleButtonEvent(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	return false;
}

bool CtModeCheckStatus::handleKeyEvent(const CtEventKey& Key) {

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_MmrMinus:
		case CtEventKey::KeyCode_MmrPlus:
		case CtEventKey::KeyCode_Up:
			break;
		case CtEventKey::KeyCode_Down:
			return true;
			break;
		case CtEventKey::KeyCode_Right:
			return true;
			break;
		case CtEventKey::KeyCode_Left:
			break;
		case CtEventKey::KeyCode_Enter:
		case CtEventKey::KeyCode_ManualFunction:
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;

}

bool CtModeCheckStatus::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();
	bool isRedraw = false;
	switch (t_Id) {
	case AplParamWarning:
	case AplParamAlert:
	case AplParamAlertIncompatibleCardSd1:
	case AplParamAlertIncompatibleCardSd2:
	case AplParamSlot2ErrStatus:
	case AplParamSlot1ErrStatus:
	case AplParamSimulErrSd1:
	case AplParamSimulErrSd2:
	case AplParamOverClipSd1:
	case AplParamOverClipSd2:
	case AplParamBackGrErrSd1:
	case AplParamBackGrErrSd2:
		isRedraw |= updateWarningState();	/* pgr2711 */
		break;
	case AplParamIpRemoteStatus:
		isRedraw |= updateIpRemote(t_Id, int_Data);	/* pgr2711 */
		break;
	case AplParamABBErrInfo:
		isRedraw |= updateAbbNg(t_Id, int_Data);	/* pgr2711 */
		break;
	case AplParamAWBErrInfo:
		isRedraw |= updateAwbNg(t_Id, int_Data);	/* pgr2711 */
		break;
	case AplParamLensStatus:
	default:
		break;
	}

	return isRedraw;
}

CtLayout* CtModeCheckStatus::createLineWarn() {
	//CtRecViewFontSet fSet = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::White);
	//fSet.edgeColor = CtColor::Black;

	CtFontSet fSet = CtFontSet(FontTypeOutline_alignCenter, CtColor::White);
	fSet.edgeColor = CtColor::Black;

	CtHLayout* pLine = new CtHLayout();

	pLine->addStretch(2);

	CtVLayout* pV = new CtVLayout();
	{
		m_pWarnLine1 = new CtLabel("", fSet);
		pV->addWidget(m_pWarnLine1, AlignCenter, 1);
		m_pWarnLine2 = new CtLabel("", fSet);
		pV->addWidget(m_pWarnLine2, AlignCenter, 1);
	}
	pLine->addWidget(pV, 49);

	pLine->addStretch(2);

	return pLine;
}

CtLayout* CtModeCheckStatus::createLineAwbNg() {
	/*CtRecViewFontSet fSet = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::White);
	fSet.edgeColor = CtColor::Black;*/

	CtFontSet fSet = CtFontSet(FontTypeOutline_alignCenter, CtColor::White);
	fSet.edgeColor = CtColor::Black;

	CtHLayout* pLine = new CtHLayout();

	pLine->addStretch(2);

	m_pAwbNg = new CtLabel("", fSet);
	pLine->addWidget(m_pAwbNg, AlignCenter, 49);

	pLine->addStretch(2);

	return pLine;
}

CtLayout* CtModeCheckStatus::createLineAbbNg() {
	//CtRecViewFontSet fSet = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::White);
	//fSet.edgeColor = CtColor::Black;

	CtFontSet fSet = CtFontSet(FontTypeOutline_alignCenter, CtColor::White);
	fSet.edgeColor = CtColor::Black;


	CtHLayout* pLine = new CtHLayout();

	pLine->addStretch(2);

	m_pAbbNg = new CtLabel("", fSet);
	pLine->addWidget(m_pAbbNg, AlignCenter, 49);

	pLine->addStretch(2);

	return pLine;
}

CtLayout* CtModeCheckStatus::createLineIpRemote() {
	CtRecViewFontSet fSet = CtRecViewFontSet();

	CtHLayout* pLine = new CtHLayout();

	pLine->addStretch(1);

	m_pIpRemote = new CtLabel(STR_ID_NO_11476, fSet);
	pLine->addWidget(m_pIpRemote, AlignLeft, 9);

	pLine->addStretch(43);

	return pLine;
}

bool CtModeCheckStatus::updateWarningState() {
	bool bRet = false;

	int warning = APL_PARAM_GET_DATA(AplParamWarning);
	int alert = APL_PARAM_GET_DATA(AplParamAlert);

	bool Sd1OverMax = APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamOverClipSd1) ? true : false;
	bool Sd2OverMax = APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamOverClipSd2) ? true : false;

	bool Sd1Incmp = APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamAlertIncompatibleCardSd1) ? true : false;
	bool Sd2Incmp = APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamAlertIncompatibleCardSd2) ? true : false;

	bool Sd1SimulErr = APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamSimulErrSd1) ? true : false;
	bool Sd2SimulErr = APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamSimulErrSd2) ? true : false;

	bool Sd1BackGrErr = APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamBackGrErrSd1) ? true : false;
	bool Sd2BackGrErr = APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamBackGrErrSd2) ? true : false;

	int Slot1Err = APL_PARAM_GET_DATA(AplParamSlot1ErrStatus);
	int Slot2Err = APL_PARAM_GET_DATA(AplParamSlot2ErrStatus);

	switch (warning) {
	case APL_SYS_PARAM_WARNING_NONE:
	case APL_SYS_PARAM_WARNING_BATTERY_NEAR_END:
	case APL_SYS_PARAM_WARNING_REMAIN_LESS_2MIN:
	case APL_SYS_PARAM_WARNING_HIGH_TEMP:
	case APL_SYS_PARAM_WARNING_NO_REMAIN:
		bRet |= m_pWarnLine1->setText(""); // NONE	/* pgr2711 */
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		goto ALERT;
		break;
	case APL_SYS_PARAM_WARNING_LOW_BATTERY:
		bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10736); // LOW BATTERY	/* pgr2711 */
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		return bRet;
		break;
	case APL_SYS_PARAM_WARNING_FAN_STOPPED:
		bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10737); // FAN STOPPED	/* pgr2711 */
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		return bRet;
		break;
	case APL_SYS_PARAM_WARNING_REC_WARNING:
		bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10738); // REC WARNING	/* pgr2711 */
		if (Sd1OverMax || Sd2OverMax) {
			bRet |= m_pWarnLine2->setStringID(STR_ID_NO_10884);	/* pgr2711 */
		}
		else {
			bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		}
		return bRet;
		break;
		// case APL_SYS_PARAM_WARNING_CARD_ERROR:
	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING:
	case APL_SYS_PARAM_WARNING_CARD_ERROR_SLOT1:
	case APL_SYS_PARAM_WARNING_CARD_ERROR_SLOT2:
	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING_SLOT1:
	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING_SLOT2:
		if (Slot1Err != APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10923);	/* pgr2711 */
		}
		else if (Slot2Err != APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10924);	/* pgr2711 */
		}
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		return bRet;
		break;
	default:
		return m_pWarnLine1->setText("GUI Not Support Warning"); // None
		break;
	}

ALERT:
	switch (alert) {
	case APL_SYS_PARAM_ALERT_NONE:
	case APL_SYS_PARAM_ALERT_BACKUP_BATT_EMPTY:
		bRet |= m_pWarnLine1->setText(""); // None	/* pgr2711 */
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		return bRet;
		break;

	case APL_SYS_PARAM_ALERT_SUB_REC_WARNING:
		bRet |= m_pWarnLine1->setStringID(STR_ID_NO_11546); // PROXY REC WARNING	/* pgr2711 */
		if (Sd1OverMax || Sd2OverMax) {
			bRet |= m_pWarnLine2->setStringID(STR_ID_NO_10884); // <OVER MAX NUM. OF CLIPS>	/* pgr2711 */
		}
		else {
			bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		}
		return bRet;
		break;
	case APL_SYS_PARAM_ALERT_SIMUL_REC_WARNING:
		// 1行目
		if (Sd1SimulErr || Sd1OverMax) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10925); // SIMUL REC WARNING <SLOT 1>	/* pgr2711 */
		}
		else if (Sd2SimulErr || Sd2OverMax) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10926); // SIMUL REC WARNING <SLOT 2>	/* pgr2711 */
		}

		// 2行目
		if (Sd1OverMax || Sd2OverMax) {
			bRet |= m_pWarnLine2->setStringID(STR_ID_NO_10884); // <OVER MAX NUM. OF CLIPS>	/* pgr2711 */
		}
		else {
			bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		}
		return bRet;
		break;
	case APL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING:
		// 1行目
		if (Sd1BackGrErr || Sd1OverMax) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_11565); // BACKGROUND REC WARNING <SLOT 1>	/* pgr2711 */
		}
		else if (Sd2BackGrErr || Sd2OverMax) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_11566); // BACKGROUND REC WARNING <SLOT 2>	/* pgr2711 */
		}

		// 2行目
		if (Sd1OverMax || Sd2OverMax) {
			bRet |= m_pWarnLine2->setStringID(STR_ID_NO_10884); // <OVER MAX NUM. OF CLIPS>	/* pgr2711 */
		}
		else {
			bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		}
		return bRet;
		break;
	case APL_SYS_PARAM_ALERT_NOT_SDXC_CARD:
		if (Slot1Err == APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SDXC && Slot2Err == APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10939); // NOT SDXC CARD <SLOT 1,2>	/* pgr2711 */
		}
		else if (Slot1Err == APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SDXC) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10931); // NOT SDXC CARD <SLOT 1>	/* pgr2711 */
		}
		else if (Slot2Err == APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10932); // NOT SDXC CARD <SLOT 2>	/* pgr2711 */
		}
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		return bRet;
		break;
	case APL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD:
		if (Slot1Err == APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SUPPORTED && Slot2Err == APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10937); // CHECK CARD <SLOT 1,2>	/* pgr2711 */
		}
		else if (Slot1Err == APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SUPPORTED) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10927); // CHECK CARD <SLOT 1>	/* pgr2711 */
		}
		else if (Slot2Err == APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10928); // CHECK CARD <SLOT 2>	/* pgr2711 */
		}
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		return bRet;
		break;
	case APL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD:
		if (Slot1Err == APL_SYS_PARAM_SLOT1_ERR_STATUS_FORMAT_ERROR && Slot2Err == APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10938); // FORMAT ERROR <SLOT 1,2>	/* pgr2711 */
		}
		else if (Slot1Err == APL_SYS_PARAM_SLOT1_ERR_STATUS_FORMAT_ERROR) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10929); // FORMAT ERROR <SLOT 1>	/* pgr2711 */
		}
		else if (Slot2Err == APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10930); // FORMAT ERROR <SLOT 2>	/* pgr2711 */
		}
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		return bRet;
		break;
	case APL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD:
		if (Sd1Incmp && Sd2Incmp) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10940); // INCOMPATIBLE CARD <SLOT 1,2>	/* pgr2711 */
		}
		else if (Sd1Incmp) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10933); // INCOMPATIBLE CARD <SLOT 1>	/* pgr2711 */
		}
		else if (Sd2Incmp) {
			bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10934); // INCOMPATIBLE CARD <SLOT 2>	/* pgr2711 */
		}
		bRet |= m_pWarnLine2->setText("");	/* pgr2711 */
		return bRet;
		break;
	case APL_SYS_PARAM_ALERT_FAN_STOPPED:
		//bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10737); // FAN STOPPED	/* pgr2711 */
		bRet |= m_pWarnLine1->setText(""); /* pgr2711 */
		bRet |= m_pWarnLine2->setText(""); /* pgr2711 */
		return bRet;
		break;
	case APL_SYS_PARAM_ALERT_CLOCK_RESET:
		bRet |= m_pWarnLine1->setStringID(STR_ID_NO_10885); // INTERNAL CLOCK HAS RESET	/* pgr2711 */
		bRet |= m_pWarnLine2->setStringID(STR_ID_NO_10886); // <OVER MAX NUM. OF CLIPS>	/* pgr2711 */
		return bRet;
		break;
	default:
		return m_pWarnLine1->setText(""); // None
		break;
	}
	return bRet;
}

bool CtModeCheckStatus::updateAwbNg(int t_Id, int int_Data) {
	m_pAwbNg->setVisible(true);
	switch (int_Data) {
	case APL_SYS_PARAM_AWB_ERR_INFO_NONE:
		return m_pAwbNg->setText("");
		break;
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_TIME_OVER:
		return m_pAwbNg->setStringID(STR_ID_NO_10697);	//"AWB NG <TIME OVER>"
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_SELECT_TEST_SIG:
		return m_pAwbNg->setStringID(STR_ID_NO_10698);	//"AWB NG <SELECT TEST SIG>"
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_COL_TEMP_LOW:
		return m_pAwbNg->setStringID(STR_ID_NO_10699);	//"AWB NG <COLOR TEMP LOW>"
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_COL_TEMP_HIGH:
		return m_pAwbNg->setStringID(STR_ID_NO_10700);	//"AWB NG <COLOR TEMP HIGH>"
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_GMG_OVER:
		return m_pAwbNg->setStringID(STR_ID_NO_10921);	//"AWB NG <GMg OVER>"
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_LEVEL_OVER:
		return m_pAwbNg->setStringID(STR_ID_NO_10701);	//"AWB NG <LEVEL OVER>"
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_LOW_LIGHT:
		return m_pAwbNg->setStringID(STR_ID_NO_10702);	//"AWB NG <LOW LIGHT>"
	}
	return false;
}

bool CtModeCheckStatus::updateAbbNg(int t_Id, int int_Data) {
	m_pAbbNg->setVisible(true);
	switch (int_Data) {
	case APL_SYS_PARAM_ABB_ERR_INFO_NONE:
		return m_pAbbNg->setText("");
	case APL_SYS_PARAM_ABB_ERR_INFO_ABB_NG:
		return m_pAbbNg->setStringID(STR_ID_NO_10663);
	case APL_SYS_PARAM_ABB_ERR_INFO_ABB_NG_TIME_OVER:
		return m_pAbbNg->setStringID(STR_ID_NO_10694);
	case APL_SYS_PARAM_ABB_ERR_INFO_ABB_NG_SELECT_TEST_SIG:
		return m_pAbbNg->setStringID(STR_ID_NO_10695);
	case APL_SYS_PARAM_ABB_ERR_INFO_ABB_NG_LENS_NOT_CLOSE:
		return m_pAbbNg->setStringID(STR_ID_NO_10696);
	default:
		break;
	}
	return false;
}

bool CtModeCheckStatus::updateIpRemote(int t_Id, int int_Data) {
	bool bRet = false;
	switch (int_Data) {
	case APL_SYS_PARAM_IP_REMOTE_STATUS_CONNECTD:
		bRet |= m_pIpRemote->setVisible(true);	/* pgr2711 */
		bRet |= m_pIpRemote->stopFlash();	/* pgr2711 */
		break;
	case APL_SYS_PARAM_IP_REMOTE_STATUS_WAIT:
		bRet |= m_pIpRemote->setVisible(true);	/* pgr2711 */
		bRet |= m_pIpRemote->startFlash(CtEventFlash::Freq_1Hz);	/* pgr2711 */
		break;
	case APL_SYS_PARAM_IP_REMOTE_STATUS_DISABLE:
		bRet |= m_pIpRemote->stopFlash();	/* pgr2711 */
		bRet |= m_pIpRemote->setVisible(false);	/* pgr2711 */
		break;
	}
	return bRet;

}
