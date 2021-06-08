/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtRecView2
 */

#include "CtRecView2.h"
#include <string.h>

#include "CtWindowCommon.h"
#include "CtICManager.h"
#include "CtSysEventTranslator.h"


CtRecView2::CtRecView2() :
	m_pWin(NULL),
	m_pTC(NULL),
	m_pAutoMnl(NULL),
	m_pCard1(NULL),
	m_pCard2(NULL),
	m_pSlotFunc(NULL),
	m_pStreamingState(NULL),
	m_pWifi(NULL),
	m_pBat(NULL),
	m_pLineAndFreq(NULL),
	m_pVfrRecFrameRate(NULL),
	m_pBondingDeckState(NULL),
	m_pLayoutRecRemoteAll(NULL),
	m_pRecRemoteIcon(NULL),
	m_pRecMode(NULL),
	m_pFlashBand(NULL),
	m_pHdr_Drs(NULL),
	m_pOis(NULL),

	m_pMainCodec(NULL),
	m_pCom(NULL),
	m_pSceneFileName(NULL),
	m_pArea_AfArea(NULL),
	m_pNdFilterWarn(NULL),
	m_pIrRec(NULL),
	m_pMML(NULL),
	m_pDzoom(NULL),
	m_pWbData(NULL),
	m_pYget(NULL),
	m_pDateTime(NULL),
	m_pHighSens(NULL),
	m_pFocus(NULL),

	m_pAudioLevelMeter(NULL),
	m_pGain(NULL),
	m_pNdFilter(NULL),
	m_pShutterSpeed(NULL),
	m_pIris(NULL),
	m_pZoom(NULL),
	m_pTotalLine(NULL),

	m_pAudioMonitorVol(NULL),
	m_pRecContainerExpand(NULL)
{
	setTransView(true);
	m_PreAudioVol = APL_PARAM_GET_DATA(AplParamAudioVol);
	if (m_PreAudioVol <= 0 || 28 <= m_PreAudioVol) m_PreAudioVol = 1;
}

CtRecView2::~CtRecView2() {
	resetIcManager();
}

CtWindow* CtRecView2::createWindow()
{
	m_fSetDef = CtRecViewFontSet();

	CtLayout* pLine1 = createLine1();
	CtLayout* pLine2 = createLine2();
	CtLayout* pLine3 = createLine3();
	CtLayout* pLine5 = createLine5();
	CtLayout* pLine6 = createLine6();
	CtLayout* pLine7 = createLine7();
	CtLayout* pLine8 = createLine8();

	m_pLevelGaugeLayout = new CtVLayout();
	{
		CtHLayout* pLbevelGaugeLayout = new CtHLayout();
		{
			m_pLevelL = new CtFastContainerLevelGaugeL();
			m_pLevelR = new CtFastContainerLevelGaugeR();
			pLbevelGaugeLayout->addContainer(m_pLevelL, 24);
			pLbevelGaugeLayout->addStretch(960 - 24 - 24);
			pLbevelGaugeLayout->addContainer(m_pLevelR, 24);
		}
		m_pLevelGaugeLayout->addStretch(95);
		m_pLevelGaugeLayout->addWidget(pLbevelGaugeLayout, 450);
		m_pLevelGaugeLayout->addStretch(95);
	}

	CtVLayout* pTotalLine = new CtVLayout();
	{
		pTotalLine->addWidget(pLine1, 1);
		// 表示切り替わりエリア
		CtLayout* pL = new CtLayout();
		{
			m_pSwitchLine = new CtVLayout();
			{
				m_pSwitchLine->addWidget(pLine2, 1);
				m_pSwitchLine->addWidget(pLine3, 2);// 2行
				m_pSwitchLine->addStretch(2);
				m_pSwitchLine->addStretch(2, ScreenLCD);
				m_pSwitchLine->addStretch(2);
				m_pSwitchLine->addWidget(pLine5, 1);
				m_pSwitchLine->addWidget(pLine6, 1);
				m_pSwitchLine->addWidget(pLine7, 1);
			}
			pL->addWidget(m_pSwitchLine);// 切り替わり領域①

			m_pExpand = new CtLayout();
			{
				m_pRecContainerExpand = new CtRecContainerExpand();
				m_pExpand->setScreenSel(ScreenLCD);
				m_pExpand->addContainer(m_pRecContainerExpand);
			}
			pL->addWidget(m_pExpand, 1);
			m_pExpand->setVisible(false);
		}
		pTotalLine->addWidget(pL, 12);
		pTotalLine->setStretch(pL, 10, ScreenLOUT);
		pTotalLine->addWidget(pLine8, 1);
	}
	CtLayout* pALL = new CtLayout();
	{
		pALL->addWidget(m_pLevelGaugeLayout);
		pALL->addWidget(pTotalLine);

	}
	m_pTotalLine = pTotalLine;

	m_pWin = new CtWindow(CtColor::Trans);
	m_pWin->addWidget(pALL);
	m_pWin->setVisible(true);

	return m_pWin;
}

bool CtRecView2::startupWindow()
{
	CtWidget::List List;
	CtLayout* pLayout = NULL;

	if (m_pLevelL != NULL) {
		if ((pLayout = m_pLevelL->getLayout()) != NULL) {
			for (int i = 0; i < CT_SCREEN_NUM; i++) {
				List.clear();
				m_pTotalLine->getWidgets(CtWidget::RegisteredCollisions, &List, WidgetLabel, i, pLayout->getRegion(i));
				if (List.size() != 0)
					m_pLevelL->setCollisions(List, i);
			}
		}
	}

	if (m_pLevelR != NULL) {
		if ((pLayout = m_pLevelR->getLayout()) != NULL) {
			for (int i = 0; i < CT_SCREEN_NUM; i++) {
				List.clear();
				m_pTotalLine->getWidgets(CtWidget::RegisteredCollisions, &List, WidgetLabel, i, pLayout->getRegion(i));
				if (List.size() != 0)
					m_pLevelR->setCollisions(List, i);
			}
		}
	}

	init();
	return true;
}

void CtRecView2::init() {
	updateAutoMnlMode(AplParamAutoManualSwState, APL_PARAM_GET_DATA(AplParamAutoManualSwState));
	updateSystemRecMode(AplParamSystemRecMode, APL_PARAM_GET_DATA(AplParamSystemRecMode));
	updateSlotFunc(AplParamRelayBackup, APL_PARAM_GET_DATA(AplParamRelayBackup));
	updateStreamState(AplParamStreamingStatus, APL_PARAM_GET_DATA(AplParamStreamingStatus));
	updateVFRValue();
	updateBondingStatus(AplParamBondingDeviceStatus, APL_PARAM_GET_DATA(AplParamBondingDeviceStatus));
	updateBondingStatus(AplParamBondingConnectStatus, APL_PARAM_GET_DATA(AplParamBondingConnectStatus));
	updateBondingStatus(AplParamBondingBatteryRemain, APL_PARAM_GET_DATA(AplParamBondingBatteryRemain));
	updateBondingStatus(AplParamBondingError, APL_PARAM_GET_DATA(AplParamBondingError));
	updateRemoteRec();
	updateRecMode(AplParamRecFunctionMode, APL_PARAM_GET_DATA(AplParamRecFunctionMode));
	updateFBC(AplParamFlashBandCorrection, APL_PARAM_GET_DATA(AplParamFlashBandCorrection));
	updateDRS(AplParamSceneDRS, APL_PARAM_GET_DATA(AplParamSceneDRS));
	updateOIS(AplParamOisMode, APL_PARAM_GET_DATA(AplParamOisMode));
	updateMainCodec(AplParamSystemRecMode, APL_PARAM_GET_DATA(AplParamSystemRecMode));
	updateSceneFileName(AplParamSceneFileName, APL_PARAM_GET_DATA(AplParamSceneFileName));
	updateAreaMode(AplParamAFRange, APL_PARAM_GET_DATA(AplParamAFRange));
	updateNdFilterWarn(AplParamNdFilterWarning, APL_PARAM_GET_DATA(AplParamNdFilterWarning));
	updateFanStopped(APL_PARAM_GET_DATA(AplParamAlertFanStopped));
	updateIrRec(AplParamIRRec, APL_PARAM_GET_DATA(AplParamIRRec));
	updateDzoom(AplParamDigitalZoomVal, APL_PARAM_GET_DATA(AplParamDigitalZoomVal));
	updateWB();

	updateH_Sens(AplParamShootingMode, APL_PARAM_GET_DATA(AplParamShootingMode));
	updateGain();
	updateNdFilter();
	updateShutterSpeed();

	m_pMML->registLinkLabels(m_pWbDataLayout, m_pShutterSpeedLayout, m_pVfrRecFrameRateLayout);
	setIcManager();

	m_pLevelL->setScreenSel(ScreenLCD);
	m_pLevelR->setScreenSel(ScreenLCD);

}

CtLayout* CtRecView2::createLine1() {
	CtHLayout* pLine = new CtHLayout();

	m_pTC = new CtFastContainerTimeCode(true, CT_COMMON_TYPE_REC);
	pLine->addContainer(m_pTC, AlignLeft, 15);

	pLine->addStretch(1);

	m_pAutoMnl = new CtLabel(IC_OSD_AUTO);
	pLine->addWidget(m_pAutoMnl, AlignLeft, 2);

	pLine->addStretch(3);

	// Card1
	m_pCard1 = new CtContainerCard1(CT_COMMON_TYPE_REC);
	pLine->addContainer(m_pCard1, AlignLeft, 9);

	// Card2
	m_pCard2 = new CtContainerCard2(CT_COMMON_TYPE_REC);
	pLine->addContainer(m_pCard2, AlignLeft, 9);

	// SLOT FUNC
	m_pSlotFunc = new CtLabel(IC_OSD_SUB_OFF);
	pLine->addWidget(m_pSlotFunc, AlignLeft, 6);

	m_pStreamingState = new CtLabel(IC_OSD_STREAM_OFF);
	pLine->addWidget(m_pStreamingState, AlignLeft, 3);

	m_pWifi = new CtContainerWifi(CT_COMMON_TYPE_REC);
	pLine->addContainer(m_pWifi, AlignLeft, 2);

	m_pBat = new CtContainerBattery(CT_COMMON_TYPE_REC);
	pLine->addContainer(m_pBat, AlignLeft, 3);

	return pLine;
}

CtLayout* CtRecView2::createLine2() {
	CtHLayout* pLine = new CtHLayout();
	{
		m_pLineAndFreq = new CtLabel("", m_fSetDef);
		pLine->addWidget(m_pLineAndFreq, AlignLeft, 11);
		pLine->addStretch(1);

		m_pStkVfrArea = new CtStackLabel();

		{
			m_pVfrRecFrameRateLayout = new CtMmlLayout();
			m_pVfrRecFrameRate = new CtLabel("", m_fSetDef);
			m_pVfrRecFrameRateLayout->addWidget(m_pVfrRecFrameRate, AlignLeft);

			CtHLayout* ph = new CtHLayout();
			ph->addWidget(m_pVfrRecFrameRateLayout, 5);
			ph->addStretch(1);

			m_pStkVfrArea->addLabel(ph);

			m_pS_Slow = new CtLabel();
			m_pStkVfrArea->addLabel(m_pS_Slow);
		}
		pLine->addWidget(m_pStkVfrArea, 6);
		pLine->addStretch(1);

		m_pBondingDeckState = new CtHLayout();
		{
			m_pBondingDeviceStatus = new CtLabel("", m_fSetDef);
			m_pBondingConnectStatus = new CtLabel();
			m_pBondingBatteryRemain = new CtLabel();
			m_pBondingErrorStatus = new CtLayout();
			CtRecViewFontSet fset = m_fSetDef;
			fset.setColor(CtColor::Black);
			fset.edgeColor = CtColor::NoColor;
			m_pBondingErrorStatus->addWidget(new CtLabel("E", fset));
			m_pBondingErrorStatus->setColor(CtColor::White);

			m_pBondingDeckState->addWidget(m_pBondingDeviceStatus, AlignLeft, 4);
			m_pBondingDeckState->addWidget(m_pBondingConnectStatus, AlignLeft, 2);
			m_pBondingDeckState->addWidget(m_pBondingBatteryRemain, AlignLeft, 3);
			m_pBondingDeckState->addWidget(m_pBondingErrorStatus, AlignLeft, 1);
		}
		pLine->addWidget(m_pBondingDeckState, 11);

		m_pLayoutRecRemoteAll = new CtHLayout();
		{
			// RecRemote
			m_pRecRemoteIcon = new CtLabel(IC_OSD_REC);
			m_pRecRemoteStr = new CtLabel("", m_fSetDef);
			m_pLayoutRecRemoteAll->addWidget(m_pRecRemoteIcon, AlignLeft, 2);
			m_pLayoutRecRemoteAll->addWidget(m_pRecRemoteStr, AlignLeft, 4);
		}
		pLine->addWidget(m_pLayoutRecRemoteAll, 6);
		pLine->addStretch(1);

		m_pRecMode = new CtLabel();
		pLine->addWidget(m_pRecMode, AlignLeft, 6);

		pLine->addStretch(1);

		m_pFlashBand = new CtLabel(IC_OSD_FBC);
		pLine->addWidget(m_pFlashBand, AlignLeft, 3);

		m_pHdr_Drs = new CtLabel();
		pLine->addWidget(m_pHdr_Drs, AlignLeft, 3);

		m_pOis = new CtLabel("", m_fSetDef);
		pLine->addWidget(m_pOis, AlignLeft, 3);
	}

	return pLine;
}

CtLayout* CtRecView2::createLine3() {
	// 2行分
	CtHLayout* pLine1 = new CtHLayout();

	pLine1->addStretch(1);
	CtVLayout* pV = new CtVLayout();
	{
		m_pMainCodec = new CtLabel("", m_fSetDef);
		pV->addWidget(m_pMainCodec, AlignLeft);
		pV->addStretch(1);
	}
	pLine1->addWidget(pV, 14);

	pLine1->addStretch(2);

	pV = new CtVLayout();
	{
		CtFontSet fset = CtFontSet(FontTypeOutline_alignCenter, CtColor::White);
		fset.edgeColor = CtColor::Black;
		m_pFanStopped = new CtLabel(STR_ID_NO_10737, fset);
		pV->addWidget(m_pFanStopped, AlignCenter, 1);

		CtHLayout* pNdWarnLine = new CtHLayout();
		{
			pNdWarnLine->addStretch(6);
			m_pNdFilterWarn = new CtLabel("", m_fSetDef);
			pNdWarnLine->addWidget(m_pNdFilterWarn, AlignLeft, 6);
			pNdWarnLine->addStretch(7);
		}
		pV->addWidget(pNdWarnLine, 1);
	}
	pLine1->addWidget(pV, 19);

	pLine1->addStretch(1);

	m_pCom = new CtContainerCom();
	pLine1->addContainer(m_pCom, AlignLeft, 6);

	pLine1->addStretch(1);

	pV = new CtVLayout();
	{
		m_pSceneFileName = new CtLabel("", m_fSetDef);
		pV->addWidget(m_pSceneFileName, AlignRight);

		CtHLayout* pAreaBlock = new CtHLayout();
		pAreaBlock->addStretch(3);

		m_pArea_AfArea = new CtLabel();
		pAreaBlock->addWidget(m_pArea_AfArea, 5);

		pV->addWidget(pAreaBlock);
	}
	pLine1->addWidget(pV, 8);

	pLine1->addStretch(1);

	return pLine1;
}

CtLayout* CtRecView2::createLine5() {
	CtHLayout* pLine = new CtHLayout();

	pLine->addStretch(51);
	m_pIrRec = new CtLabel(STR_ID_NO_10667, m_fSetDef);
	pLine->addWidget(m_pIrRec, AlignLeft, 2);
	pLine->addStretch(1);

	return pLine;
}

CtLayout* CtRecView2::createLine6() {
	CtHLayout* pLine = new CtHLayout();

	pLine->addStretch(1);
	m_pMML = new CtContainerMml();
	pLine->addContainer(m_pMML, AlignLeft, 12);

	pLine->addStretch(35);

	m_pDzoom = new CtLabel("", m_fSetDef);
	pLine->addWidget(m_pDzoom, AlignLeft, 4);

	pLine->addStretch(1);
	return pLine;
}

CtLayout* CtRecView2::createLine7() {
	CtHLayout* pLine = new CtHLayout();

	m_pWbDataLayout = new CtMmlLayout();
	{
		m_pWbData = new CtLabel("", m_fSetDef);
		m_pWbDataLayout->addWidget(m_pWbData, AlignLeft);
	}
	pLine->addWidget(m_pWbDataLayout, 7);

	pLine->addStretch(1);

	// Spot
	m_pYget = new CtFastDrawContainerSpotMeterVal();
	pLine->addContainer(m_pYget, AlignLeft, 4);

	pLine->addStretch(3);

	m_pDateTime = new CtCtnrDateTime();
	pLine->addContainer(m_pDateTime, AlignLeft, 20);

	pLine->addStretch(1);

	m_pHighSens = new CtLabel(STR_ID_NO_11471, m_fSetDef);
	pLine->addWidget(m_pHighSens, AlignLeft, 7);

	m_pFocus = new CtFastDrawContainerFocus();
	pLine->addContainer(m_pFocus, AlignLeft, 10);

	return pLine;
}

CtLayout* CtRecView2::createLine8() {
	CtHLayout* pLine = new CtHLayout();
	{
		// AudioLevelMeter
		m_pAudioLevelMeter = new CtFastContainerAudioLevel_View(true);
		pLine->addContainer(m_pAudioLevelMeter, AlignLeft, 13);

		CtHLayout* pSwitchLine = new CtHLayout();
		{
			// GAIN
			m_pGain = new CtLabel("", m_fSetDef);
			pSwitchLine->addWidget(m_pGain, AlignLeft, 4);

			pSwitchLine->addStretch(1);

			// ND FILTER
			m_pNdFilter = new CtLabel("", m_fSetDef);
			pSwitchLine->addWidget(m_pNdFilter, AlignLeft, 6);

			pSwitchLine->addStretch(1);

			// SHUTTER
			m_pShutterSpeedLayout = new CtMmlLayout();
			{
				m_pShutterSpeed = new CtLabel("", m_fSetDef);
				m_pShutterSpeedLayout->addWidget(m_pShutterSpeed, AlignLeft);
			}
			pSwitchLine->addWidget(m_pShutterSpeedLayout, 7);

			pSwitchLine->addStretch(1);

			// IRIS
			m_pIris = new CtFastDrawContainerIris();
			pSwitchLine->addContainer(m_pIris, AlignLeft, 11);

			pSwitchLine->addStretch(1);

			// ZOOM
			m_pZoom = new CtFastDrawContainerZoom();
			pSwitchLine->addContainer(m_pZoom, AlignLeft, 8);
		}

		m_pAudioCameraSwitchArea = new CtStackLabel();
		{
			m_pAudioCameraSwitchArea->addLabel(pSwitchLine);

			m_pAudioMonitorVolArea = new CtHLayout();
			{
				m_pAudioMonitorVolArea->addStretch(1);
				CtRecViewFontSet fset = m_fSetDef;
				fset.setFontAttribute(FontTypeOutline_alignRight);
				m_pAudioMonitorVolArea->addWidget(new CtLabel("VOLUME[-]", fset), AlignLeft, 9);
				int i = 0;
				while (i < 27) {
					m_pVolumeVal[i] = new CtStackLabel();
					{
						m_pVolumeVal[i]->addLabel(new CtLabel(IC_OSD_VOL_OFF), 0);
						m_pVolumeVal[i]->addLabel(new CtLabel(IC_OSD_VOL_ON), 1);
					}
					m_pAudioMonitorVolArea->addWidget(m_pVolumeVal[i], AlignCenter, 1);
					m_pVolumeVal[i]->index(0);
					i++;
				}
				fset.setFontAttribute(FontTypeOutline);
				m_pAudioMonitorVolArea->addWidget(new CtLabel("[+]", fset), AlignLeft, 3);

				m_pVolumeVal[m_PreAudioVol - 1]->index(1);
			}
			m_pAudioCameraSwitchArea->addLabel(m_pAudioMonitorVolArea);

			m_pAudioCameraSwitchArea->index(0);
		}
		pLine->addWidget(m_pAudioCameraSwitchArea, 40);
	}

	return pLine;
}

bool CtRecView2::handleTouchEvent(const CtEventTouch& Touch) {
	if (APL_PARAM_GET_DATA(AplParamLcdFocusExpandUserSw) == APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_OFF) {
		if (Touch.getAction() == CtEventTouch::Press) {
			CtTimer::getInstance()->setAlarm(CT_TIMER_ID_TOUCH_NAVI_DISP, 1000, this);
		}
		else if (Touch.getAction() == CtEventTouch::Release) {
			CtTimer::getInstance()->cancelAlarm(CT_TIMER_ID_TOUCH_NAVI_DISP, this);
		}
		return true;
	}
	return false;
}

bool CtRecView2::handleKeyEvent(const CtEventKey& Key) {
	if (Key.getKeyAction() == CtEventKey::Press) {
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Exit:
			CtEventInterface::requestFuncCmd(Window_RecView, FuncID_Exit_Press);
			break;
		case CtEventKey::KeyCode_DispCheck:
			CtTimer::getInstance()->setAlarm(CT_TIMER_ID_DISP_CHECK, 1000, this);
			break;
		default:
			break;
		}
	}
	else if (Key.getKeyAction() == CtEventKey::Release) {
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Exit:
			CtEventInterface::requestFuncCmd(Window_RecView, FuncID_Exit_Release);
			return true;
			break;
		case CtEventKey::KeyCode_DispCheck:
			if (CtTimer::getInstance()->isActTimerId(CT_TIMER_ID_DISP_CHECK, this) == true) {
				// 短押し
				if (APL_PARAM_GET_DATA(AplParamDispModeCheck) == APL_SYS_PARAM_SWITCH_ON) {
					APL_PARAM_SET_DATA(AplParamDispModeCheck, APL_SYS_PARAM_SWITCH_OFF);
				}
				else {
					APL_PARAM_SET_DATA(AplParamDispModeCheck, APL_SYS_PARAM_SWITCH_ON);
				}
			}
			CtTimer::getInstance()->cancelAlarm(CT_TIMER_ID_DISP_CHECK, this);
			break;

		default:
			break;
		}
	}
	return false;
}

bool CtRecView2::handleTimerEvent(const CtEventTimer& Timer)
{
	switch (Timer.getTimeUid())
	{
	case CT_TIMER_ID_AUDIO_VOL:
		m_pAudioCameraSwitchArea->index(0);
		break;
	case CT_TIMER_ID_TOUCH_NAVI_DISP:
		if (APL_PARAM_GET_DATA(AplParamLcdSw) != APL_SYS_PARAM_LCD_SW_MIRROR) {
			CtEventInterface::requestFuncCmd(Window_RecView, FuncID_ICONS);
		}
		CtTimer::getInstance()->cancelAlarm(CT_TIMER_ID_TOUCH_NAVI_DISP, this);
		break;
	case CT_TIMER_ID_DISP_CHECK:
		// 長押し
		if (APL_PARAM_GET_DATA(AplParamLcdSw) != APL_SYS_PARAM_LCD_SW_MIRROR) {
			CtEventInterface::requestFuncCmd(Window_RecView, FuncID_ModeCheckDispPreOn);
		}

		break;
	default:
		break;
	}

	return true;
}

bool CtRecView2::handleParamEvent(const CtEventParam& Param) {
	bool isRedraw = true;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamWhiteBalanceModeOSD:
	case AplParamSceneAchColorTemp:
	case AplParamSceneBchColorTemp:
	case AplParamWbVar:
		isRedraw |= updateWB();/* pgr2711 */
		break;
	case AplParamAudioVol:
		isRedraw |= updateAudioVol(int_Data);/* pgr2711 */
		break;
	case AplParamAutoManualSwState:
		isRedraw |= updateAutoMnlMode(t_Id, int_Data);/* pgr2711 */
		isRedraw |= updateShutterSpeed();/* pgr2711 */
		isRedraw |= updateGain();/* pgr2711 */
		isRedraw |= updateWB();/* pgr2711 */
		break;
	case AplParamGainValue:
	case AplParamAutoSwitchAGC:
		isRedraw |= updateGain();/* pgr2711 */
		break;
	case AplParamStreamingStatus:
		isRedraw |= updateStreamState(t_Id, int_Data);/* pgr2711 */
		break;

	case AplParamSystemRecMode:
		isRedraw |= updateSystemRecMode(t_Id, int_Data);/* pgr2711 */
		isRedraw |= updateMainCodec(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamSceneVFRMode:
	case AplParamSceneVFRValue:
	case AplParamSystemFrequency:
	case AplParamSuperSlowRec:
		isRedraw |= updateVFRValue();/* pgr2711 */
		break;
	case AplParamNetworkDeviceSel:
	case AplParamBondingDeviceStatus:
	case AplParamBondingConnectStatus:
	case AplParamBondingBatteryRemain:
	case AplParamBondingError:
		isRedraw |= updateBondingStatus(t_Id, int_Data);/* pgr2711 */
		break;

	case AplParamSdiHdmiRecRemoteStatus:
	case AplParamSdiRemote:
	case AplParamHdmiRecRemote:
	case AplParamHdmiTcOutput:
		isRedraw |= updateRemoteRec();/* pgr2711 */
		break;
	case AplParamRecFunctionMode:
	case AplParamRecFunctionStatus:
		isRedraw |= updateRecMode(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamFlashBandCorrection:
		isRedraw |= updateFBC(t_Id, int_Data);/* pgr2711 */
		break;

	case AplParamSceneGammaModeSel:
	case AplParamSceneDRS:
		isRedraw |= updateDRS(t_Id, int_Data);/* pgr2711 */
		break;

	case AplParamOisMode:
	case AplParam4AxisOis:
		isRedraw |= updateOIS(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamAreaMode:
	case AplParamAFRange:
		isRedraw |= updateAreaMode(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamSceneFileName:
		isRedraw |= updateSceneFileName(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamIRRec:
		isRedraw |= updateIrRec(t_Id, int_Data);/* pgr2711 */
		isRedraw |= updateNdFilter();/* pgr2711 */
		isRedraw |= updateWB();/* pgr2711 */
		break;
	case AplParamNDFilterIr:
	case AplParamNDFilter:
		isRedraw |= updateNdFilter();/* pgr2711 */
		break;
	case AplParamNdFilterWarning:
		isRedraw |= updateNdFilterWarn(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamDigitalZoomVal:
		isRedraw |= updateDzoom(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamATWSet:
		isRedraw |= updateWB();/* pgr2711 */
		break;
	case AplParamShootingMode:
		isRedraw |= updateH_Sens(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamAutoSwitchAutoShutter:
	case AplParamShutterSwitch:
	case AplParamSceneSyncScanType:
	case AplParamShutterSpeedSec:
	case AplParamSceneSyncScanDegValue:
	case AplParamSceneSyncScanSecValue:
	case AplParamSynchroScanMode:
		isRedraw |= updateShutterSpeed();/* pgr2711 */
		break;
	case AplParamRelayBackup:
	case AplParamProxyRecMode:
	case AplParamRelayBackupErrStatus:
		isRedraw |= updateSlotFunc(t_Id, int_Data);/* pgr2711 */
		break;
	case AplParamLcdFocusExpandUserSw:
		if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
			isRedraw |= m_pExpand->setVisible(true);/* pgr2711 */
		}
		else {
			isRedraw |= m_pExpand->setVisible(false);/* pgr2711 */
		}
		break;
	case AplParamNetworkFunc:
		isRedraw |= updateRecMode(AplParamRecFunctionMode, APL_PARAM_GET_DATA(AplParamRecFunctionMode));/* pgr2711 */
		isRedraw |= updateSlotFunc(AplParamRelayBackup, APL_PARAM_GET_DATA(AplParamRelayBackup));/* pgr2711 */
		isRedraw |= updateMainCodec(AplParamSystemRecMode, APL_PARAM_GET_DATA(AplParamSystemRecMode));/* pgr2711 */
		break;
	case AplParamAlertFanStopped:
		// FanStopped
		isRedraw |= updateFanStopped(int_Data);/* pgr2711 */
		break;
	default:
		isRedraw = false;
		break;
	}
	isRedraw |= CtICManager::getInstance()->updateParam(t_Id, int_Data);/* pgr2711 */
	return isRedraw;
}

bool CtRecView2::updateAudioVol(int nVol) {
	// Vol値反映
	if (nVol > 27) {
		nVol = 27;
	}
	else if (nVol <= 0) {
		nVol = 1;
	}

	m_pVolumeVal[m_PreAudioVol - 1]->index(0);

	m_pVolumeVal[nVol - 1]->index(1);
	m_PreAudioVol = nVol;
	m_pAudioCameraSwitchArea->index(1);
	CtTimer::getInstance()->setAlarm(CT_TIMER_ID_AUDIO_VOL, 3000, this);
	return true;
}

bool CtRecView2::updateAutoMnlMode(int t_Id, int int_Data) {
	if (t_Id != AplParamAutoManualSwState) return false;
	if (int_Data == APL_SYS_PARAM_AUTO_MNL_SW_MANUAL) {
		m_pAutoMnl->setVisible(false);
	}
	else if (int_Data == APL_SYS_PARAM_AUTO_MNL_SW_AUTO) {
		m_pAutoMnl->setVisible(true);
	}
	return false;
}

bool CtRecView2::updateSlotFunc(int t_Id, int int_Data) {
	int SubRec = APL_SYS_PARAM_PROXY_REC_MODE_OFF;
	int SlotFunc = APL_SYS_PARAM_RELAY_BACKUP_OFF;
	int SlotFuncErr = APL_SYS_PARAM_RELAY_BACKUP_ERR_NO_ERR;
	GDI_IMAGE_ID img = IC_OSD_SUB_OFF;

	if (t_Id == AplParamProxyRecMode) {
		SubRec = int_Data;
		SlotFunc = APL_PARAM_GET_DATA(AplParamRelayBackup);
		SlotFuncErr = APL_PARAM_GET_DATA(AplParamRelayBackupErrStatus);
	}
	else if (t_Id == AplParamRelayBackup) {
		SubRec = APL_PARAM_GET_DATA(AplParamProxyRecMode);
		SlotFunc = int_Data;
		SlotFuncErr = APL_PARAM_GET_DATA(AplParamRelayBackupErrStatus);
	}
	else if (t_Id == AplParamRelayBackupErrStatus) {
		SubRec = APL_PARAM_GET_DATA(AplParamProxyRecMode);
		SlotFunc = APL_PARAM_GET_DATA(AplParamRelayBackup);
		SlotFuncErr = int_Data;
	}
	m_pSlotFunc->setVisible(true);

	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		// NDI|HX時は常時表示
		m_pSlotFunc->setStringID(STR_ID_NO_11283, m_fSetDef);
		m_pSlotFunc->setAlign(AlignLeft);
		return true;
	}

	if (SubRec != APL_SYS_PARAM_PROXY_REC_MODE_OFF) {
		// PROXY
		if (APL_SYS_PARAM_RELAY_BACKUP_ERR_SUB != SlotFuncErr)
			return m_pSlotFunc->setImage(IC_OSD_SUB_ON);
		else return m_pSlotFunc->setImage(IC_OSD_SUB_OFF);
	}
	else {
		switch (SlotFunc) {
		case APL_SYS_PARAM_RELAY_BACKUP_OFF:
			return m_pSlotFunc->setVisible(false);
			// OFF
			break;
		case APL_SYS_PARAM_RELAY_BACKUP_RELAY:
			// RELAY
			if (APL_SYS_PARAM_RELAY_BACKUP_ERR_RELAY != SlotFuncErr)
				return m_pSlotFunc->setImage(IC_OSD_RELAY_ON);
			else return m_pSlotFunc->setImage(IC_OSD_RELAY_OFF);
			break;
		case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:
			// BACKGROUND
			if (APL_SYS_PARAM_RELAY_BACKUP_ERR_BACKUP != SlotFuncErr)
				return m_pSlotFunc->setImage(IC_OSD_BACKGR_ON);
			else return m_pSlotFunc->setImage(IC_OSD_BACKGR_OFF);
			break;
		case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:
			// SIMUL
			if (APL_SYS_PARAM_RELAY_BACKUP_ERR_SIMUL != SlotFuncErr)
				return m_pSlotFunc->setImage(IC_OSD_SIMUL_ON);
			else return m_pSlotFunc->setImage(IC_OSD_SIMUL_OFF);
			break;
		default:
			return m_pSlotFunc->setVisible(false);
			break;
		}
	}
}

bool CtRecView2::updateStreamState(int t_Id, int int_Data) {
	if (m_pStreamingState->isFlashing() == true) m_pStreamingState->stopFlash();

	if (m_pStreamingState->isVisible() == false)m_pStreamingState->setVisible(true);
	switch (int_Data) {
	case APL_SYS_PARAM_STREAMING_STATUS_RUN:
		return m_pStreamingState->setImage(IC_OSD_STREAMING);
		break;
	case APL_SYS_PARAM_STREAMING_STATUS_WAIT:
		m_pStreamingState->startFlash(CtEventFlash::Freq_1Hz);
		return m_pStreamingState->setImage(IC_OSD_STREAMING);
		break;
	case APL_SYS_PARAM_STREAMING_STATUS_STOP:
		return m_pStreamingState->setImage(IC_OSD_STREAM_STANDBY);
		break;
	case APL_SYS_PARAM_STREAMING_STATUS_ERROR:
		return m_pStreamingState->setImage(IC_OSD_STREAM_OFF);
		break;
	case APL_SYS_PARAM_STREAMING_STATUS_DISABLE:
		return m_pStreamingState->setVisible(false);
		break;
	default:
		return m_pStreamingState->setVisible(false);
		break;
	}
}

bool CtRecView2::updateSystemRecMode(int t_Id, int int_Data) {
	bool b59HZ = true, bRet = false;
	if (APL_PARAM_GET_DATA(AplParamSystemFrequency) == APL_SYS_PARAM_SYSTEM_FREQUENCY_50HZ) {
		b59HZ = false;
	}
	m_pLineAndFreq->setVisible(true);

	switch (int_Data) {
	case APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_60P_150M:
	case APL_SYS_PARAM_RECMODE_MOV_HEVC_UHD_60P_200M:
		if (b59HZ) bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11434);/* pgr2711 */
		else  bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11435);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_30P_100M:
	case APL_SYS_PARAM_RECMODE_MOV_HEVC_UHD_30P_150M:
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_UHD_30P_150M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_UHD_30P_400M:
		if (b59HZ) bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11436);/* pgr2711 */
		else  bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11437);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_2398P_100M:
	case APL_SYS_PARAM_RECMODE_MOV_HEVC_UHD_2398P_150M:
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_UHD_2398P_150M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_UHD_2398P_400M:
		bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11438);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_60P_100M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_60P_200M:
	case APL_SYS_PARAM_RECMODE_AVCHD_PS:
		if (b59HZ) bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11439);/* pgr2711 */
		else  bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11440);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_60I_50M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_60I_100M:
	case APL_SYS_PARAM_RECMODE_AVCHD_PH:
	case APL_SYS_PARAM_RECMODE_AVCHD_HA:
		if (b59HZ) bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11444);/* pgr2711 */
		else  bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11445);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_30P_50M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_30P_100M:
		if (b59HZ) bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11441);/* pgr2711 */
		else  bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11442);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_2398P_50M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_2398P_100M:
	case APL_SYS_PARAM_RECMODE_AVCHD_PH_2398P:
		bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11443);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_AVCHD_PM:
		if (b59HZ) bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11446);/* pgr2711 */
		else  bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11447);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_AVCHD_SA:
		if (b59HZ) bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11448);/* pgr2711 */
		else  bRet |= m_pLineAndFreq->setStringID(STR_ID_NO_11449);/* pgr2711 */
		break;
	default:
		m_pLineAndFreq->setVisible(false);
		break;
	}

	m_pLineAndFreq->setFontSet(m_fSetDef);
	return true;
}

bool CtRecView2::updateVFRValue() {
	//char *pStr = NULL;
	bool isDisp = false;
	char Str[10] = { 0 };

	int vfrVal = APL_PARAM_GET_DATA(AplParamSceneVFRValue);

	bool b59HZ = APL_PARAM_GET_DATA(AplParamSystemFrequency) == APL_SYS_PARAM_SYSTEM_FREQUENCY_59HZ;

	if (APL_PARAM_GET_DATA(AplParamSuperSlowRec) == APL_SYS_PARAM_SWITCH_ON) {
		isDisp = true;

		m_pStkVfrArea->index(1);
		if (b59HZ)m_pS_Slow->setImage(IC_OSD_S_SLOW_120);
		else m_pS_Slow->setImage(IC_OSD_S_SLOW_100);
	}
	else {
		if (APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamSceneVFRMode)) {
			isDisp = true;
		}
		m_pStkVfrArea->index(0);
		sprintf(Str, "%2d%s", vfrVal, "fps");
		m_pVfrRecFrameRate->setText(Str, m_fSetDef);
	}
	m_pVfrRecFrameRate->setVisible(isDisp);
	return true;
}

bool CtRecView2::updateBondingStatus(int t_Id, int int_Data) {
	switch (t_Id) {
	case AplParamBondingDeviceStatus:
	{
		char BonDevSta[AplParamBondingDeviceStatus_Size] = { 0 };
		m_pBondingDeviceStatus->setVisible(true);
		APL_PARAM_GET_DATA_AREA(AplParamBondingDeviceStatus, (unsigned char *)BonDevSta, AplParamBondingDeviceStatus_Size);
		m_pBondingDeviceStatus->setText(BonDevSta);
	}
	break;
	case AplParamBondingConnectStatus:
		m_pBondingConnectStatus->setVisible(true);
		switch (int_Data) {
		case APL_SYS_PARAM_BONDING_CONNECT_STATUS_LV0:
			m_pBondingConnectStatus->setImage(IC_OSD_BONDING_ANTENNA_0);
			break;
		case APL_SYS_PARAM_BONDING_CONNECT_STATUS_LV1:
			m_pBondingConnectStatus->setImage(IC_OSD_BONDING_ANTENNA_1);
			break;
		case APL_SYS_PARAM_BONDING_CONNECT_STATUS_LV2:
			m_pBondingConnectStatus->setImage(IC_OSD_BONDING_ANTENNA_2);
			break;
		case APL_SYS_PARAM_BONDING_CONNECT_STATUS_LV3:
			m_pBondingConnectStatus->setImage(IC_OSD_BONDING_ANTENNA_3);
			break;
		case APL_SYS_PARAM_BONDING_CONNECT_STATUS_LV4:
			m_pBondingConnectStatus->setImage(IC_OSD_BONDING_ANTENNA_4);
			break;
		case APL_SYS_PARAM_BONDING_CONNECT_STATUS_LV5:
			m_pBondingConnectStatus->setImage(IC_OSD_BONDING_ANTENNA_5);
			break;
		default:
			// DisConnect
			m_pBondingConnectStatus->setVisible(false);
			break;
		}
		break;
	case AplParamBondingBatteryRemain:
		m_pBondingBatteryRemain->setVisible(true);
		switch (int_Data) {
		case APL_SYS_PARAM_BATTERY_REMAIN_FULL:
			m_pBondingBatteryRemain->setImage(IC_OSD_BATT_LV5);
			break;
		case APL_SYS_PARAM_BATTERY_REMAIN_PER_80:
			m_pBondingBatteryRemain->setImage(IC_OSD_BATT_LV4);
			break;
		case APL_SYS_PARAM_BATTERY_REMAIN_PER_60:
			m_pBondingBatteryRemain->setImage(IC_OSD_BATT_LV3);
			break;
		case APL_SYS_PARAM_BATTERY_REMAIN_PER_40:
			m_pBondingBatteryRemain->setImage(IC_OSD_BATT_LV2);
			break;
		case APL_SYS_PARAM_BATTERY_REMAIN_PER_20:
			m_pBondingBatteryRemain->setImage(IC_OSD_BATT_LV1);
			break;
		case APL_SYS_PARAM_BATTERY_REMAIN_NEAREND:
			m_pBondingBatteryRemain->setImage(IC_OSD_BATT_LV0_RED);
			break;
		case APL_SYS_PARAM_BATTERY_REMAIN_UNDERCUT:
			m_pBondingBatteryRemain->setImage(IC_OSD_BATT_LV0_RED);
			break;
		case APL_SYS_PARAM_BATTERY_REMAIN_DC_IN:
			m_pBondingBatteryRemain->setImage(IC_OSD_AC);
			break;
		default:
			m_pBondingBatteryRemain->setVisible(false);
			break;
		}
		break;
	case AplParamBondingError:
		if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
			m_pBondingErrorStatus->setVisible(true);
		}
		else {
			m_pBondingErrorStatus->setVisible(false);
		}
		break;
	}

	if (APL_PARAM_GET_DATA(AplParamNetworkDeviceSel) == APL_SYS_PARAM_NETWORK_DEVICE_SEL_OFF) {
		return m_pBondingDeckState->setVisible(false);
	}
	else {
		if (APL_PARAM_GET_DATA(AplParamBondingConnectStatus) == APL_SYS_PARAM_BONDING_CONNECT_STATUS_DISCONNECT) {
			return m_pBondingDeckState->setVisible(false);
		}
		else {
			return m_pBondingDeckState->setVisible(true);
		}
	}
	return true;
}

bool CtRecView2::updateRemoteRec() {
	int int_Data = APL_PARAM_GET_DATA(AplParamSdiHdmiRecRemoteStatus);
	GDI_STRING_ID strId = STR_ID_NO_10657;
	bool RemoteDisp = false;
	bool RecIconDisp = false;

	switch (int_Data) {
	case APL_SYS_PARAM_REC_REMOTE_STATUS_SDI_HDMI_RECORDING:
		RecIconDisp = true;
		if ((APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamSdiRemote)) ||
			(APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamHdmiRecRemote))) {
			RemoteDisp = true;
			strId = STR_ID_NO_10655;
		}
		else {
			RemoteDisp = false;
			RecIconDisp = false;
		}
		break;
	case APL_SYS_PARAM_REC_REMOTE_STATUS_SDI_HDMI_PAUSE:
		if ((APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamSdiRemote)) ||
			(APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamHdmiRecRemote))) {
			RemoteDisp = true;
			strId = STR_ID_NO_10655;
		}
		else {
			RemoteDisp = false;
			RecIconDisp = false;
		}
		break;
	case APL_SYS_PARAM_REC_REMOTE_STATUS_SDI_RECORDING:
		RecIconDisp = true;
		if (APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamSdiRemote)) {
			RemoteDisp = true;
			strId = STR_ID_NO_10656;
		}
		else {
			RemoteDisp = false;
			RecIconDisp = false;
		}
		break;
	case APL_SYS_PARAM_REC_REMOTE_STATUS_SDI_PAUSE:
		if (APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamSdiRemote)) {
			RemoteDisp = true;
			strId = STR_ID_NO_10656;
		}
		else {
			RemoteDisp = false;
			RecIconDisp = false;
		}
		break;
	case APL_SYS_PARAM_REC_REMOTE_STATUS_HDMI_RECORDING:
		RecIconDisp = true;
		if (APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamHdmiRecRemote)
			&& APL_PARAM_GET_DATA(AplParamHdmiTcOutput) == APL_SYS_PARAM_SWITCH_ON) {
			RemoteDisp = true;
			strId = STR_ID_NO_10657;
		}
		else {
			RemoteDisp = false;
			RecIconDisp = false;
		}
		break;
	case APL_SYS_PARAM_REC_REMOTE_STATUS_HDMI_PAUSE:
		if (APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamHdmiRecRemote)
			&& APL_PARAM_GET_DATA(AplParamHdmiTcOutput) == APL_SYS_PARAM_SWITCH_ON) {
			RemoteDisp = true;
			strId = STR_ID_NO_10657;
		}
		else {
			RemoteDisp = false;
			RecIconDisp = false;
		}
		break;
	default:
		RemoteDisp = false;
		RecIconDisp = false;
		break;
	}
	if (RemoteDisp == false) {
		m_pLayoutRecRemoteAll->setVisible(false);
	}
	else {
		m_pLayoutRecRemoteAll->setVisible(true);
		m_pRecRemoteStr->setVisible(RemoteDisp);
		m_pRecRemoteStr->setStringID(strId);
		m_pRecRemoteIcon->setVisible(RecIconDisp);
	}
	return true;
}

bool CtRecView2::updateRecMode(int t_Id, int int_Data) {
	bool isDisp = true, bRet = false;
	int RecMode = 0, RecModeState = 0;
	GDI_STRING_ID strId = STR_ID_NO_10652;
	CtRecViewFontSet fset = m_fSetDef;

	if (t_Id == AplParamRecFunctionMode) {
		RecMode = int_Data;
		RecModeState = APL_PARAM_GET_DATA(AplParamRecFunctionStatus);
	}
	else {
		RecMode = APL_PARAM_GET_DATA(AplParamRecFunctionMode);
		RecModeState = int_Data;
	}

	if (RecModeState != APL_SYS_PARAM_REC_FUNC_STATE_LOOP_INVALID && m_RecModeFlush == true) {
		m_RecModeFlush = false;
		bRet |= m_pRecMode->stopFlash(); /* pgr2711 */
	}

	if (APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL == RecMode) {
		isDisp = false;
	}
	else if (APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT == RecMode
		|| APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL == RecMode) {
		if (RecModeState == APL_SYS_PARAM_REC_FUNC_STATE_INTRVL_REC_STOP) {
			strId = STR_ID_NO_10652;
		}
		else if (RecModeState == APL_SYS_PARAM_REC_FUNC_STATE_INTRVL_RECORDING) {
			strId = STR_ID_NO_10653;
			fset.setColor(CtColor::red);
		}
		else if (RecModeState == APL_SYS_PARAM_REC_FUNC_STATE_INTRVL_REC_PAUSE) {
			strId = STR_ID_NO_10653;
			fset.setColor(CtColor::red);
		}
		else {
			isDisp = false;
		}
	}
	else if (APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP == RecMode) {
		if (RecModeState == APL_SYS_PARAM_REC_FUNC_STATE_LOOP) {
			strId = STR_ID_NO_10761;
		}
		else if (RecModeState == APL_SYS_PARAM_REC_FUNC_STATE_LOOP_INVALID) {
			strId = STR_ID_NO_10761;
			m_RecModeFlush = true;
			bRet |= m_pRecMode->startFlash(CtEventFlash::Freq_1Hz);/* pgr2711 */
		}
		else {
			isDisp = false;
		}
	}

	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		// NDI|HX時は常時非表示
		isDisp = false;
	}

	bRet |= m_pRecMode->setVisible(isDisp);/* pgr2711 */
	bRet |= m_pRecMode->setStringID(strId, fset);/* pgr2711 */
	return bRet;
}

bool CtRecView2::updateFBC(int t_Id, int int_Data) {
	if (t_Id != AplParamFlashBandCorrection) {
		return false;
	}
	else {
		if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
			return m_pFlashBand->setVisible(true);
		}
		else {
			return m_pFlashBand->setVisible(false);
		}
	}
}

bool CtRecView2::updateDRS(int t_Id, int int_Data) {
	bool bGamma = false, bHlg = false, isDisp = false, bRet = false;

	if (t_Id == AplParamSceneGammaModeSel) {
		bGamma = APL_PARAM_GET_DATA(AplParamSceneDRS) == APL_SYS_PARAM_SWITCH_ON ? true : false;
		bHlg = int_Data == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG ? true : false;
	}
	else if (t_Id == AplParamSceneDRS) {
		bGamma = int_Data == APL_SYS_PARAM_SWITCH_ON ? true : false;
		bHlg = APL_PARAM_GET_DATA(AplParamSceneGammaModeSel) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG ? true : false;
	}

	isDisp = true;
	if (bHlg == true) {
		bRet |= m_pHdr_Drs->setImage(IC_OSD_HDR);/* pgr2711 */
	}
	else if (bGamma == true) {
		bRet |= m_pHdr_Drs->setImage(IC_OSD_DRS);/* pgr2711 */
	}
	else {
		isDisp = false;
	}
	bRet |= m_pHdr_Drs->setVisible(isDisp);/* pgr2711 */
	return bRet;
}

bool CtRecView2::updateOIS(int t_Id, int int_Data) {
	bool bOis = false, bHybrid = false, isDisp = false, bRet = false;
	if (t_Id == AplParamOisMode) {
		bOis = int_Data == APL_SYS_PARAM_OIS_MODE_ACTIVE ? true : false;
		bHybrid = APL_PARAM_GET_DATA(AplParam4AxisOis) == APL_SYS_PARAM_SWITCH_ON ? true : false;
	}
	else if (t_Id == AplParam4AxisOis) {
		bOis = APL_PARAM_GET_DATA(AplParamOisMode) == APL_SYS_PARAM_OIS_MODE_ACTIVE ? true : false;
		bHybrid = int_Data == APL_SYS_PARAM_SWITCH_ON ? true : false;
	}

	if (bOis == true) {
		isDisp = true;
		if (bHybrid == true) {
			bRet |= m_pOis->setImage(IC_OSD_TEBURE_HYBRID);/* pgr2711 */
		}
		else {
			bRet |= m_pOis->setImage(IC_OSD_TEBURE);/* pgr2711 */
		}
	}
	else {
		isDisp = false;
	}
	bRet |= m_pOis->setVisible(isDisp);/* pgr2711 */
	return bRet;
}

bool CtRecView2::updateMainCodec(int t_Id, int int_Data) {
	bool bRet = false;

	switch (int_Data) {
	case APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_60P_150M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11450);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_HEVC_UHD_60P_200M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11455);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_30P_100M:
	case APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_2398P_100M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11451);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_HEVC_UHD_30P_150M:
	case APL_SYS_PARAM_RECMODE_MOV_HEVC_UHD_2398P_150M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11456);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_UHD_30P_150M:
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_UHD_2398P_150M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11452);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_UHD_30P_400M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_UHD_2398P_400M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11457);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_60P_100M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11453);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_60P_200M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11458);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_60I_50M:
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_30P_50M:
	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_2398P_50M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11454);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_60I_100M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_30P_100M:
	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_2398P_100M:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11459);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_AVCHD_PS:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_10622);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_AVCHD_PH:
	case APL_SYS_PARAM_RECMODE_AVCHD_PH_2398P:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_10623);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_AVCHD_HA:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_10624);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_AVCHD_PM:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_10625);/* pgr2711 */
		break;
	case APL_SYS_PARAM_RECMODE_AVCHD_SA:
		bRet |= m_pMainCodec->setStringID(STR_ID_NO_11428);/* pgr2711 */
		break;
	default:
		break;
	}
	m_pMainCodec->setFontSet(m_fSetDef);

	// NDI|HX時は表示種類分ける
	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		// NDI|HX時は常時非表示
		return m_pMainCodec->setVisible(false);
	}
	else {
		return m_pMainCodec->setVisible(true);
	}

	return bRet;
}

bool CtRecView2::updateSceneFileName(int t_Id, int int_Data) {
	char ScName[AplParamSceneFileName_Size] = { 0 };
	APL_PARAM_GET_DATA_AREA(AplParamSceneFileName, (unsigned char *)ScName, AplParamSceneFileName_Size);
	return m_pSceneFileName->setText(ScName);
}

bool CtRecView2::updateAreaMode(int t_Id, int int_Data) {
	bool bArea = false, bAfArea = false, isDisp = false, bRet = false;
	bAfArea = APL_PARAM_GET_DATA(AplParamAFRange) == APL_SYS_PARAM_SWITCH_ON ? true : false;
	bArea = APL_PARAM_GET_DATA(AplParamAreaMode) == APL_SYS_PARAM_SWITCH_ON ? true : false;


	if (bAfArea == true) {
		bRet |= m_pArea_AfArea->setImage(IC_OSD_AF_AREA);/* pgr2711 */
		m_pArea_AfArea->setAlign(AlignLeft);
		bRet |= m_pArea_AfArea->setVisible(true);/* pgr2711 */
	}
	else if (bArea) {
		m_pArea_AfArea->setAlign(AlignRight);
		bRet |= m_pArea_AfArea->setImage(IC_OSD_AREA);/* pgr2711 */
		bRet |= m_pArea_AfArea->setVisible(true);/* pgr2711 */
	}
	else {
		bRet |= m_pArea_AfArea->setVisible(false);/* pgr2711 */
	}
	return bRet;
}

bool CtRecView2::updateNdFilterWarn(int t_Id, int int_Data) {
	bool bRet = false;

	switch (int_Data) {
	case APL_SYS_PARAM_ND_WARN_CLEAR:
		bRet |= m_pNdFilterWarn->setStringID(STR_ID_NO_11463);/* pgr2711 */
		bRet |= m_pNdFilterWarn->startFlash(CtEventFlash::Freq_1Hz);/* pgr2711 */
		bRet |= m_pNdFilterWarn->setVisible(true);/* pgr2711 */
		break;
	case APL_SYS_PARAM_ND_WARN_4:
		bRet |= m_pNdFilterWarn->setStringID(STR_ID_NO_11464);/* pgr2711 */
		bRet |= m_pNdFilterWarn->startFlash(CtEventFlash::Freq_1Hz);/* pgr2711 */
		bRet |= m_pNdFilterWarn->setVisible(true);/* pgr2711 */
		break;
	case APL_SYS_PARAM_ND_WARN_16:
		bRet |= m_pNdFilterWarn->setStringID(STR_ID_NO_11465);/* pgr2711 */
		bRet |= m_pNdFilterWarn->startFlash(CtEventFlash::Freq_1Hz);/* pgr2711 */
		bRet |= m_pNdFilterWarn->setVisible(true);/* pgr2711 */
		break;
	case APL_SYS_PARAM_ND_WARN_64:
		bRet |= m_pNdFilterWarn->setStringID(STR_ID_NO_11466);/* pgr2711 */
		bRet |= m_pNdFilterWarn->startFlash(CtEventFlash::Freq_1Hz);/* pgr2711 */
		bRet |= m_pNdFilterWarn->setVisible(true);/* pgr2711 */
		break;
	case APL_SYS_PARAM_ND_WARN_NONE:
	default:
		// None
		bRet |= m_pNdFilterWarn->stopFlash();/* pgr2711 */
		bRet |= m_pNdFilterWarn->setVisible(false);/* pgr2711 */
	}
	return bRet;
}

bool CtRecView2::updateIrRec(int t_Id, int int_Data) {
	bool bRet = false, isDisp = false;
	if (APL_SYS_PARAM_SWITCH_ON == int_Data) {
		isDisp = true;
	}
	else {
		isDisp = false;
	}
	bRet |= m_pIrRec->setVisible(isDisp);/* pgr2711 */
	return bRet;
}

bool CtRecView2::updateDzoom(int t_Id, int int_Data) {
	bool bRet = false, isDisp = false;

	switch (int_Data) {
	case APL_SYS_PARAM_DZOOM_OFF:
		isDisp = false;
		break;
	case APL_SYS_PARAM_DZOOM_2:
		isDisp = true;
		isDisp |= m_pDzoom->setText("D2x");/* pgr2711 */
		break;
	case APL_SYS_PARAM_DZOOM_5:
		isDisp = true;
		isDisp |= m_pDzoom->setText("D5x");/* pgr2711 */
		break;
	case APL_SYS_PARAM_DZOOM_10:
		isDisp = true;
		isDisp |= m_pDzoom->setText("D10x");/* pgr2711 */
		break;
	default:
		break;
	}
	bRet |= m_pDzoom->setVisible(isDisp);/* pgr2711 */
	return bRet;
}

bool CtRecView2::updateWB() {
	//型 : AplCamWhiteBalanceMode
	/* AplCameraCommon - Foundationのデータに依存
	typedef enum AplCamWhiteBalanceMode {
		AplWhiteBalanceMode_Auto = 0, ///AUTO
		AplWhiteBalanceMode_AutoLock = 1, ///AUTO LOCK
		AplWhiteBalanceMode_Indoor1 = 2, ///屋内1/3200K
		AplWhiteBalanceMode_Sunny = 3, ///晴れ/5600K
		AplWhiteBalanceMode_A_Hold = 4,5,6 ///WB固定/Ach固定
		AplWhiteBalanceMode_B_Hold = 7,8,9 ///Bch固定
		AplWhiteBalanceMode_Var = 14, ///Var
	} AplCamWhiteBalanceMode;
	*/
	char str[50] = "";
	if (APL_PARAM_GET_DATA(AplParamIRRec) == APL_SYS_PARAM_SWITCH_ON) {
		m_pWbData->setText("");
	}
	else {
		switch (APL_PARAM_GET_DATA(AplParamWhiteBalanceModeOSD)) {
		case 0: // ATW
			m_pWbData->setStringID(STR_ID_NO_10762);
			break;
		case 1: // LOCK
			m_pWbData->setStringID(STR_ID_NO_11470);
			break;
		case 2: // 3200K
			sprintf(str, "P 3200K");
			break;
		case 3: // 5600K
			sprintf(str, "P 5600K");
			break;
		case 4:
		case 5:
		case 6:
			sprintf(str, "A%5dK", APL_PARAM_GET_DATA(AplParamSceneAchColorTemp));
			break;
		case 7:
		case 8:
		case 9:
			sprintf(str, "B%5dK", APL_PARAM_GET_DATA(AplParamSceneBchColorTemp));
			break;
		case 14: // VAR
			sprintf(str, "V%5dK", APL_PARAM_GET_DATA(AplParamWbVar));
			break;
		default:
			break;
		}
	}
	if (strcmp(str, "") != 0) {
		m_pWbData->setText(str);
	}

	return true;
}

bool CtRecView2::updateH_Sens(int t_Id, int int_Data) {
	bool bRet = false;
	if (int_Data == APL_SYS_PARAM_SHOOTING_MODE_NORMAL) {
		bRet |= m_pHighSens->setVisible(false);/* pgr2711 */
	}
	else if (int_Data == APL_SYS_PARAM_SHOOTING_MODE_HIGH_SENS) {
		bRet |= m_pHighSens->setVisible(true);/* pgr2711 */
	}
	return bRet;
}

bool CtRecView2::updateGain() {
	bool bRet = false;
	if (APL_PARAM_GET_DATA(AplParamAutoSwitchAGC) == APL_SYS_PARAM_SWITCH_ON
		&& APL_PARAM_GET_DATA(AplParamAutoManualSwState) == APL_SYS_PARAM_SWITCH_ON) {
		m_pGain->setStringID(STR_ID_NO_11462);
	}
	else {
		char gainVal = (char)APL_PARAM_GET_DATA(AplParamGainValue);
		char str[50];
		memset(str, 0, sizeof(str));
		sprintf(str, "%2ddB", gainVal);
		m_pGain->setText(str);
	}
	return bRet;
}

bool CtRecView2::updateNdFilter() {
	bool bRet = false;
	int data = 0;
	/* IR SHOOTING によって見るAplParamが異なる */
	/* 設定されるENUM値は同じ */
	if (APL_PARAM_GET_DATA(AplParamIRRec) == APL_SYS_PARAM_SWITCH_OFF) {
		data = APL_PARAM_GET_DATA(AplParamNDFilter);
	}
	else {
		data = APL_PARAM_GET_DATA(AplParamNDFilterIr);
	}
	bRet |= m_pNdFilter->setVisible(true); /* pgr2711 */
	switch (data) {
	case APL_SYS_PARAM_NDFILTER_CLEAR:
		bRet |= m_pNdFilter->setStringID(STR_ID_NO_11463);/* pgr2711 */
		break;
	case APL_SYS_PARAM_NDFILTER_4:
		bRet |= m_pNdFilter->setStringID(STR_ID_NO_11464);/* pgr2711 */
		break;
	case APL_SYS_PARAM_NDFILTER_16:
		bRet |= m_pNdFilter->setStringID(STR_ID_NO_11465);/* pgr2711 */
		break;
	case APL_SYS_PARAM_NDFILTER_64:
		bRet |= m_pNdFilter->setStringID(STR_ID_NO_11466);/* pgr2711 */
		break;
	default:
		m_pNdFilter->setVisible(false);
		break;
	}
	return bRet;
}

bool CtRecView2::updateShutterSpeed() {
	bool isDisp = false;
	char Str[10] = { 0 };

	if (APL_PARAM_GET_DATA(AplParamAutoSwitchAutoShutter)
		&& APL_PARAM_GET_DATA(AplParamAutoManualSwState)) {
		m_pShutterSpeed->setVisible(true);
		m_pShutterSpeed->setStringID(STR_ID_NO_11467);
	}
	else if (APL_SYS_PARAM_SWITCH_OFF == APL_PARAM_GET_DATA(AplParamShutterSwitch)) {
		// Shutterの表示/非表示
		m_pShutterSpeed->setVisible(false);
	}
	else {
		m_pShutterSpeed->setVisible(true);
		// Shutter / Syncro
		if (APL_PARAM_GET_DATA(AplParamSynchroScanMode) == APL_SYS_PARAM_SWITCH_OFF) {
			// Shutter
			// 値 : AplParamShutterSpeedSec
			sprintf(Str, "1/%d", APL_PARAM_GET_DATA(AplParamShutterSpeedSec) / 10);
			m_pShutterSpeed->setText(Str);
		}
		else {
			// Syncro
			if (APL_PARAM_GET_DATA(AplParamSceneSyncScanType) == APL_SYS_PARAM_SYNC_SCAN_TYPE_SEC) {
				// 値 : AplParamSynchroScanSec
				float syncroSec = ((float)APL_PARAM_GET_DATA(AplParamSceneSyncScanSecValue)) / 10;
				sprintf(Str, "1/%-.1f", syncroSec);
				m_pShutterSpeed->setText(Str);
			}
			else {
				// APL_SYS_PARAM_SYNC_SCAN_TYPE_DEG
				// 値 : AplParamSynchroScanDeg
				float syncroDeg = ((float)APL_PARAM_GET_DATA(AplParamSceneSyncScanDegValue)) / 10;
				sprintf(Str, "%5.1fd", syncroDeg);
				m_pShutterSpeed->setText(Str);
			}
		}
	}

	return true;
}

bool CtRecView2::updateFanStopped(int int_Data) {
	if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
		return m_pFanStopped->setVisible(true);
	}
	else {
		return m_pFanStopped->setVisible(false);
	}
}

bool CtRecView2::setIcManager() {
	CtICManager* pIcMan = CtICManager::getInstance();

	pIcMan->registInstance(m_pTC, IC_SEL_TC);
	pIcMan->registInstance(m_pAutoMnl, IC_SEL_FULL_AUTO);
	pIcMan->registInstance(m_pSlotFunc, IC_SEL_2SLOT_FUNC);
	pIcMan->registInstance(m_pStreamingState, IC_SEL_STREAMING);
	pIcMan->registInstance(m_pWifi, IC_SEL_NETWORK);
	pIcMan->registInstance(m_pBat, IC_SEL_BAT_REMAIN);
	pIcMan->registInstance(m_pLineAndFreq, IC_SEL_REC_FORMAT_LINE_FREQ);
	pIcMan->registInstance(m_pMainCodec, IC_SEL_REC_FORMAT);
	pIcMan->registInstance(m_pStkVfrArea, IC_SEL_FRAME_RATE);
	pIcMan->registInstance(m_pBondingDeckState, IC_SEL_BONDING_DEVICE);
	pIcMan->registInstance(m_pLayoutRecRemoteAll, IC_SEL_REC_REMOTE);
	pIcMan->registInstance(m_pRecMode, IC_SEL_REC_MODE);
	pIcMan->registInstance(m_pFlashBand, IC_SEL_FBC);
	pIcMan->registInstance(m_pHdr_Drs, IC_SEL_HDR_DRS);
	pIcMan->registInstance(m_pOis, IC_SEL_OIS);
	pIcMan->registInstance(m_pArea_AfArea, IC_SEL_AREA);
	pIcMan->registInstance(m_pAudioLevelMeter, IC_SEL_AUDIO_LEVEL_M);
	pIcMan->registInstance(m_pGain, IC_SEL_GAIN);
	pIcMan->registInstance(m_pNdFilter, IC_SEL_ND_FILTER);
	pIcMan->registInstance(m_pShutterSpeedLayout, IC_SEL_SHUTTER);
	pIcMan->registInstance(m_pIris, IC_SEL_IRIS);
	pIcMan->registInstance(m_pZoom, IC_SEL_ZOOM);
	pIcMan->registInstance(m_pMML, IC_SEL_MML);
	pIcMan->registInstance(m_pWbDataLayout, IC_SEL_WHITE);
	pIcMan->registInstance(m_pDateTime, IC_SEL_DATE_TIME);
	pIcMan->registInstance(m_pHighSens, IC_SEL_SHOOTING_MODE);
	pIcMan->registInstance(m_pFocus, IC_SEL_FOCUS);
	pIcMan->registInstance(m_pDzoom, IC_SEL_D_ZOOM);
	pIcMan->registInstance(m_pIrRec, IC_SEL_IR_REC);
	pIcMan->registInstance(m_pYget, IC_SEL_SPOT_M);
	pIcMan->registInstance(m_pSceneFileName, IC_SEL_SCENE_FILE);
	pIcMan->registInstance(m_pCom, IC_SEL_COM);
	pIcMan->registInstance(m_pAudioMonitorVolArea, IC_SEL_AUDIO_VOL);
	pIcMan->registInstance(m_pNdFilterWarn, IC_SEL_ND_WARN);
	pIcMan->registInstance(m_pLevelGaugeLayout, IC_SEL_LEVEL_GAUGE);
	pIcMan->registInstance(m_pFanStopped, IC_SEL_FAN_STOPPED);
	pIcMan->setRecIcMode(true);
	return true;
}

bool CtRecView2::resetIcManager() {
	CtICManager* pIcMan = CtICManager::getInstance();
	int i = 0;
	while (i < IC_SEL_MAX)
	{
		pIcMan->releaseInstance((CtMenuOutputId)i);
		i++;
	}
	pIcMan->setRecIcMode(false);
	return true;
}
