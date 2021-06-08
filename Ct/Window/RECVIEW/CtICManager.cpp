/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtViewPlayIndicatorController
 */

#include "CtICManager.h"

CtICManager* CtICManager::m_pThis(NULL);

CtIcReactDataSet CtICManager::m_pIcDataSet[IC_SEL_MAX] = {
	// IC ID NO.					// AplParamIC						// DispMode	// Mml	// ExpandReact  // Instance
	{ IC_SEL_TC,					AplParamIdMax,						NoReact,	false,	false,			NULL },
	{ IC_SEL_FULL_AUTO,				AplParamIndicatorFullAuto,			React, 		false,	false,			NULL },
	{ IC_SEL_CARD_STATUS,			AplParamLcdIndicatorSlotStatus,		React,		false,	false,			NULL },
	{ IC_SEL_CARD_STATUS2,			AplParamLcdIndicatorSlotStatus,		React,		false,	false,			NULL },
	{ IC_SEL_REMAIN1,				AplParamLcdIndicatorSlotStatus,		React,		false,	false,			NULL },
	{ IC_SEL_REMAIN2,				AplParamLcdIndicatorSlotStatus,		React,		false,	false,			NULL },
	{ IC_SEL_2SLOT_FUNC,			AplParamLcdIndicator2SlotFunc,		React, 		false,	false,			NULL },
	{ IC_SEL_STREAMING,				AplParamIndicatorStreaming,			React, 		false,	false,			NULL },
	{ IC_SEL_NETWORK,				AplParamLcdIndicatorWlan,			React, 		false,	false,			NULL },
	{ IC_SEL_BAT_REMAIN,			AplParamLcdIndicatorBatteryRemain,	React, 		false,	false,			NULL },
	{ IC_SEL_REC_FORMAT_LINE_FREQ,	AplParamLcdIndicatorRecFormat,		React, 		false,	true,			NULL },
	{ IC_SEL_FRAME_RATE,			AplParamLcdIndicatorFps,			React, 		true, 	true,			NULL },
	{ IC_SEL_REC_FORMAT,			AplParamLcdIndicatorRecFormat,		React, 		false,	true,			NULL },
	{ IC_SEL_BONDING_DEVICE,		AplParamIndicatorBondingDevice,		React, 		false,	true,			NULL },
	{ IC_SEL_REC_REMOTE,			AplParamLcdIndicatorRecRemote, 		React, 		false,	true,			NULL },
	{ IC_SEL_REC_MODE,				AplParamLcdIndicatorRecFuncMode,	React, 		false,	true,			NULL },
	{ IC_SEL_FBC,					AplParamIndicatorFbc, 				React, 		false,	true,			NULL },
	{ IC_SEL_HDR_DRS,				AplParamIndicatorHdrDrs, 			React, 		false,	true,			NULL },
	{ IC_SEL_OIS,					AplParamIndicatorOis, 				React, 		false,	true,			NULL },
	{ IC_SEL_SCENE_FILE,			AplParamIndicatorSceneFile, 		React, 		false,	true,			NULL },
	{ IC_SEL_AREA,					AplParamIndicatorArea, 				React, 		false,	true,			NULL },
	{ IC_SEL_AUDIO_LEVEL_M,			AplParamLcdIndicatorAudioLevelMeter,React, 		false,	false,			NULL },
	{ IC_SEL_GAIN,					AplParamIndicatorGain, 				React, 		false,	false,			NULL },
	{ IC_SEL_ND_FILTER,				AplParamLcdIndicatorNdFilter, 		React, 		false,	false,			NULL },
	{ IC_SEL_SHUTTER,				AplParamLcdIndicatorShutter, 		React, 		true,	false,			NULL },
	{ IC_SEL_IRIS,					AplParamIndicatorIris, 				React, 		false,	false,			NULL },
	{ IC_SEL_ZOOM,					AplParamIdMax, 						React,		false,	false,			NULL },
	{ IC_SEL_WHITE,					AplParamLcdIndicatorWhite, 			React, 		true,	true,			NULL },
	{ IC_SEL_SPOT_M,				AplParamIdMax, 						NoReact,	false,	true,			NULL },
	{ IC_SEL_DATE_TIME,				AplParamIdMax, 						React,		false,	true,			NULL },
	{ IC_SEL_SHOOTING_MODE,			AplParamIndicatorShootingMode, 		React, 		false,	true,			NULL },
	{ IC_SEL_FOCUS,					AplParamIdMax, 						React,		false,	true,			NULL },
	{ IC_SEL_MML,					AplParamIndicatorMultiManual, 		React, 		true,	true,			NULL },
	{ IC_SEL_D_ZOOM,				AplParamIndicatorDZoom, 			React, 		false,	true,			NULL },
	{ IC_SEL_IR_REC,				AplParamLcdIndicatorIRRec, 			React, 		false,	true,			NULL },
	{ IC_SEL_COM,					AplParamIdMax, 						NoReact,	false,	true,			NULL },
	{ IC_SEL_AUDIO_VOL,				AplParamIdMax, 						NoReact,	false,	false,			NULL },
	{ IC_SEL_ND_WARN,				AplParamIdMax, 						NoReact,	false,	true,			NULL },
	{ IC_SEL_LEVEL_GAUGE,			AplParamIdMax, 						NoReact,	false,	false,			NULL },
	{ IC_SEL_FAN_STOPPED,			AplParamIdMax, 						NoReact,	false,	false,			NULL },
};


CtICManager::CtICManager() :
	m_bRecIc(false),
	m_bMmlAct(false),
	m_bStatusMode(false),
	m_MmlActIcId(IC_SEL_MAX)
{
	m_pThis = NULL;
	for (int i = 0; i < IC_SEL_MAX; i++) {
		m_pIcDataSet[i].Instance.pWidget = NULL;
		m_pIcDataSet[i].Instance.pContainer = NULL;
	}
}

CtICManager::~CtICManager()
{
	if (!m_pThis) {
		delete m_pThis;
		m_pThis = NULL;
	}
}

CtICManager* CtICManager::getInstance() {
	if (m_pThis == NULL) {
		m_pThis = new CtICManager();
	}
	return m_pThis;
}

bool CtICManager::setStatusMode(const bool bStatusMode) {
	if (m_bStatusMode == bStatusMode) return false;
	m_bStatusMode = bStatusMode;

	// 一部はStatus状態独自の処理をする Instanceに通知
	for (int i = 0; i < IC_SEL_MAX; i++) {
		switch (m_pIcDataSet[i].IcId) {
		case IC_SEL_TC:
		case IC_SEL_FOCUS:
		case IC_SEL_ZOOM:
		case IC_SEL_DATE_TIME:
		case IC_SEL_SPOT_M:
			if (m_pIcDataSet[i].Instance.pContainer) m_pIcDataSet[i].Instance.pContainer->setStatusMode(bStatusMode);
			break;
		default:
			break;
		}
		if (m_pIcDataSet[i].Instance.pWidget != NULL || m_pIcDataSet[i].Instance.pContainer != NULL) {
			updateWidgetDispScreen(m_pIcDataSet[i]);
		}
	}
	return true;
}

bool CtICManager::setMmlAct(const bool bMmlAct, CtMenuOutputId IcId) {
	if (m_bMmlAct == bMmlAct && IcId == m_MmlActIcId) return false;
	bool bRet = false;
	// MML前状態更新
	m_bMmlAct = bMmlAct;
	if (m_MmlActIcId != IC_SEL_MML) {
		for (int idCnt = 0; idCnt < IC_SEL_MAX; idCnt++) {
			if (m_pIcDataSet[idCnt].IcId == m_MmlActIcId) {
				m_MmlActIcId = IC_SEL_MAX;
				bRet |= updateWidgetDispScreen(m_pIcDataSet[idCnt]);	/* pgr2711 */
			}
		}
	}
	// 動作IC更新
	m_MmlActIcId = IcId;

	for (int idCnt = 0; idCnt < IC_SEL_MAX; idCnt++) {
		if (m_pIcDataSet[idCnt].IcId == m_MmlActIcId) {
			bRet |= updateWidgetDispScreen(m_pIcDataSet[idCnt]);	/* pgr2711 */
		}
	}
	// IC_MMLは各設定モードと同時に動作すること
	bRet |= updateWidgetDispScreen(m_pIcDataSet[IC_SEL_MML]);	/* pgr2711 */
	return bRet;
}

bool CtICManager::setRecIcMode(const bool bRecIc) {
	if (m_bRecIc == bRecIc) return false;
	m_bRecIc = bRecIc;
	m_bStatusMode = false;
	m_bMmlAct = false;
	return updateICs();
}

CtScreenSel CtICManager::getDispIcMode(CtMenuOutputId Id) {
	switch (Id) {
	case IC_SEL_CARD_STATUS:	// 残量は2分以下のみ
	case IC_SEL_CARD_STATUS2:	// 残量は2分以下のみ(ENDは非表示)
	case IC_SEL_REMAIN1:
	case IC_SEL_REMAIN2:
	{
		CtRecViewContainer* pCon = m_pIcDataSet[Id].Instance.pContainer;
		if (pCon != NULL) {
			return pCon->getDispIcModeSel(Id);
		}
	}
	break;
	case IC_SEL_BAT_REMAIN:		// ニアエンド、アンダーカットのみ
	{
		CtRecViewContainer* pCon = m_pIcDataSet[Id].Instance.pContainer;
		if (pCon != NULL) {
			return pCon->getDispIcModeSel();
		}
	}
	break;
	default:
		return ScreenNone;
		break;
	}
	return ScreenNone;
}

CtScreenSel CtICManager::getWidgetDispScreen(CtMenuOutputId Id, bool isRecOsd)
{
	CtScreenSel Screen = ScreenAll;
	// Menu設定
	if (m_pIcDataSet[Id].IcParam != AplParamIdMax) {
		if (APL_PARAM_GET_DATA(m_pIcDataSet[Id].IcParam) == APL_SYS_PARAM_SWITCH_OFF)
			Screen = getDispIcMode(Id);
		if (IC_SEL_2SLOT_FUNC == Id && APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
			Screen = ScreenAll;
		}
	}
	// DISP MODE
	if (APL_PARAM_GET_DATA(AplParamDispModeCheck) == APL_SYS_PARAM_SWITCH_ON) {
		if (m_pIcDataSet[Id].DispMode != NoReact) Screen = getDispIcMode(Id);
	}

	// MM機能
	if ( m_pIcDataSet[Id].MmlReact == true 
	 &&( m_MmlActIcId == m_pIcDataSet[Id].IcId || m_pIcDataSet[Id].IcId == IC_SEL_MML) 
	 && m_bMmlAct == true) 
	{
		if (m_pIcDataSet[Id].IcId == IC_SEL_MML) {
			int a = 0;
		}
		Screen = ScreenAll;
	}

	// Expand
	if (m_pIcDataSet[Id].ExpandReact == true) {
		if (APL_PARAM_GET_DATA(AplParamLcdFocusExpandUserSw) == APL_SYS_PARAM_SWITCH_ON) {
			if (Screen == ScreenAll) {
				Screen = ScreenLOUT;
			}
			else if (Screen == ScreenLCD) {
				Screen = ScreenNone;
			}
		}
	}

	// Status画面
	if (m_bStatusMode == true) {
		Screen = ScreenAll;
	}

	// LCD Mirror
	if (APL_PARAM_GET_DATA(AplParamLcdSw) == APL_SYS_PARAM_LCD_SW_MIRROR) {
		if (Screen == ScreenAll || Screen == ScreenLOUT) {
			Screen = ScreenLOUT;
		}
		else {
			Screen = ScreenNone;
		}
	}
	return Screen;
}

bool CtICManager::registInstance(CtWidget* pWidget, CtMenuOutputId targetId) {
	if (pWidget == NULL || IC_SEL_MAX < targetId) return false;
	for (int i = 0; i < IC_SEL_MAX; i++) {
		if (m_pIcDataSet[i].IcId == targetId) {
			m_pIcDataSet[i].Instance.pWidget = pWidget;
			return true;
		}
	}
	return true;
}

bool CtICManager::registInstance(CtRecViewContainer* pContainer, CtMenuOutputId targetId) {
	if (pContainer == NULL || IC_SEL_MAX < targetId) return false;
	for (int i = 0; i < IC_SEL_MAX; i++) {
		if (m_pIcDataSet[i].IcId == targetId) {
			m_pIcDataSet[i].Instance.pContainer = pContainer;
			return true;
		}
	}
	return true;
}

bool CtICManager::registInstance(CtWidget* pWidget, CtRecViewContainer* pContainer, CtMenuOutputId targetId) {
	if (pWidget == NULL || pContainer == NULL || IC_SEL_MAX < targetId) return false;
	for (int i = 0; i < IC_SEL_MAX; i++) {
		if (m_pIcDataSet[i].IcId == targetId) {
			m_pIcDataSet[i].Instance.pContainer = pContainer;
			m_pIcDataSet[i].Instance.pWidget = pWidget;
			return true;
		}
	}
	return true;
}

bool CtICManager::releaseInstance(CtMenuOutputId targetId) {
	if (IC_SEL_MAX < targetId) return false;
	for (int i = 0; i < IC_SEL_MAX; i++) {
		if (m_pIcDataSet[i].IcId == targetId) {
			m_pIcDataSet[i].Instance.pWidget = NULL;
			m_pIcDataSet[i].Instance.pContainer = NULL;
			return true;
		}
	}
	return true;
}

bool CtICManager::updateICs() {
	bool bRet = false;
	for (int idCnt = 0; idCnt < IC_SEL_MAX; idCnt++) {
		if (m_pIcDataSet[idCnt].Instance.pWidget != NULL || m_pIcDataSet[idCnt].Instance.pContainer != NULL) {
			bRet |= updateWidgetDispScreen(m_pIcDataSet[idCnt]);	/* pgr2711 */
		}
	}
	return bRet;
}

bool CtICManager::updateIC(int targetParamId) {
	bool bRet = false;
	for (int i = 0; i < IC_SEL_MAX; i++) {
		if (m_pIcDataSet[i].IcParam == targetParamId) {
			bRet |= updateWidgetDispScreen(m_pIcDataSet[i]);	/* pgr2711 */

		}
	}
	return bRet;
}

bool CtICManager::updateIC(CtMenuOutputId targetId) {
	if (IC_SEL_MAX < targetId) return false;
	return updateWidgetDispScreen(m_pIcDataSet[targetId]);
}

bool CtICManager::updateWidgetDispScreen(CtIcReactDataSet& targetDataSet) {
	CtScreenSel	sel = getWidgetDispScreen(targetDataSet.IcId);
	// Screen設定更新 (pWidget, pContainer両方保持の場合はWidgetのみ設定)
	if (targetDataSet.Instance.pWidget != NULL) return targetDataSet.Instance.pWidget->setScreenSel(sel);
	else if (targetDataSet.Instance.pContainer != NULL) return targetDataSet.Instance.pContainer->setScreenSel(sel);
	return false;
}

bool CtICManager::updateParam(int t_id, int int_Data) {
	switch (t_id) {
	case AplParamIndicatorFullAuto:
	case AplParamLcdIndicator2SlotFunc:
	case AplParamIndicatorStreaming:
	case AplParamLcdIndicatorFps:
	case AplParamLcdIndicatorRecFormat:
	case AplParamIndicatorBondingDevice:
	case AplParamLcdIndicatorRecRemote:
	case AplParamLcdIndicatorRecFuncMode:
	case AplParamIndicatorFbc:
	case AplParamIndicatorHdrDrs:
	case AplParamIndicatorOis:
	case AplParamIndicatorSceneFile:
	case AplParamIndicatorArea:
	case AplParamIndicatorGain:
	case AplParamLcdIndicatorNdFilter:
	case AplParamLcdIndicatorShutter:
	case AplParamIndicatorIris:
	case AplParamIndicatorZoomFocus:
	case AplParamLcdIndicatorWhite:
	case AplParamIndicatorDateTime:
	case AplParamIndicatorShootingMode:
	case AplParamIndicatorMultiManual:
	case AplParamIndicatorDZoom:
	case AplParamLcdIndicatorIRRec:
	case AplParamLcdIndicatorPlayBackStatus:
	case AplParamLcdIndicatorSlotStatus:
	case AplParamLcdIndicatorBatteryRemain:
	case AplParamLcdIndicatorWlan:
	case AplParamLcdIndicatorAudioLevelMeter:
		return updateIC(t_id);
		break;
	case AplParamDispModeCheck:
	case AplParamLcdSw:
	case AplParamLcdFocusExpandUserSw:
		return updateICs();
	default:
		break;
	}
	return false;
}
