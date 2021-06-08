/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#include "CtContainerMml.h"
#include "CtICManager.h"

int ACT_TIMER_SEC = 3000;

CtContainerMml::CtContainerMml() :
	m_pAll(NULL),
	m_MmlMode(SELECT)
{
	m_MmlCheckBox = ICONS;
	m_bMmrExec = false;
	m_bFastPress = false;
}

CtContainerMml::~CtContainerMml()
{
}

CtLayout* CtContainerMml::createContainer()
{
	m_fset = CtRecViewFontSet();
	m_pAll = new CtLayout();
	{
		CtHLayout* pMmlLine = new CtHLayout();
		{
			m_pMmlIcon = new CtLabel(IC_OSD_DIAL);
			pMmlLine->addWidget(m_pMmlIcon, 2);

			m_pMml = new CtLabel(STR_ID_NO_11472, m_fset);
			m_pMml->setWidgetID(IC_SEL_MML);
			pMmlLine->addWidget(m_pMml,AlignLeft, 10);
		}
		m_pAll->addWidget(pMmlLine);
	}
	m_pCrntConfig = NULL;
	return m_pAll;
}

bool CtContainerMml::registLinkLabels(CtMmlLayout* pWb, CtMmlLayout* pShutter, CtMmlLayout* pFrameRate) {
	m_pWb = pWb;
	m_pWb->setWidgetID(IC_SEL_WHITE);

	m_pShutter = pShutter;
	m_pShutter->setWidgetID(IC_SEL_SHUTTER);

	m_pFrameRate = pFrameRate;
	m_pFrameRate->setWidgetID(IC_SEL_FRAME_RATE);

	return false;
}

bool CtContainerMml::destroyWindow()
{
	return true;
}

bool CtContainerMml::handleKeyEvent(const CtEventKey& Key) {
	bool bRet = false;
	if (APL_PARAM_GET_DATA(AplParamLcdFocusExpandUserSw) == APL_SYS_PARAM_SWITCH_ON) {
		return false;
	}
	if (APL_PARAM_GET_DATA(AplParamLcdSw) == APL_SYS_PARAM_LCD_SW_MIRROR) {
		return false;
	}
	if (m_MmlCheckBox == AREA && m_MmlMode == CONFIG) {
		switch (Key.getKeyAction()) {
		case CtEventKey::Press:
		case CtEventKey::RepeatPress:
			if (areaPos(Key.getKeyCode()) == true) {
				return true;
			}
			break;
		default:
			break;
		}
	}

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
	case CtEventKey::RepeatPress:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Up:
		case CtEventKey::KeyCode_MmrPlus:
		
			m_bMmrExec = false;
			
			bRet |= inc(Key.getTimLv());	/* pgr2711 */
			bRet |= setActionMode(true);	/* pgr2711 */
			break;
		case CtEventKey::KeyCode_Down:
		case CtEventKey::KeyCode_MmrMinus:
		
			m_bMmrExec = false;
			
			bRet |= dec(Key.getTimLv());					/* pgr2711 */
			bRet |= setActionMode(true);	/* pgr2711 */
			break;
		case CtEventKey::KeyCode_Exit:
			bRet |= cancel();				/* pgr2711 */
			break;
		case CtEventKey::KeyCode_ManualFunction:
		case CtEventKey::KeyCode_Enter:
			m_bMmrExec = true;
			break;
		case CtEventKey::KeyCode_DialPressUp:
			m_bFastPress = true;
			bRet |= inc(Key.getTimLv());	/* pgr2711 */
			bRet |= setActionMode(true);	/* pgr2711 */
			break;

		case CtEventKey::KeyCode_DialPressDown:
			m_bFastPress = true;
			bRet |= dec(Key.getTimLv());					/* pgr2711 */
			bRet |= setActionMode(true);	/* pgr2711 */
			break;
		default:
			break;
		}
		break;
	case CtEventKey::Release:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_Enter:
		case CtEventKey::KeyCode_ManualFunction:
			if (m_bFastPress == true) {
				m_bFastPress = false;  
				return false;
			}
			if ( m_bMmrExec == false) return false;
			bRet |= exec();					/* pgr2711 */
			bRet |= setActionMode(true);	/* pgr2711 */
			break;
		case CtEventKey::KeyCode_DialPressDown:
		case CtEventKey::KeyCode_DialPressUp:
			m_bFastPress = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return bRet;
}

bool CtContainerMml::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamAutoManualSwState:
	case AplParamAutoSwitchAutoShutter:
	case AplParamSuperSlowRec:
	case AplParamSynchroScanMode:
		if (isValidMmlFunc(m_MmlCheckBox)) {
			return false;
		}
		else {
			return setSelectMode(getNextMmlCheckBoxItem());
		}
		break;
	case AplParamShutterSwitch:
		if (isValidMmlFunc(SHUTTER)) {
			return setSelectMode(SHUTTER);
		}
		else {
			if (m_MmlCheckBox != SHUTTER && m_MmlCheckBox != SYNCRO) return false;
			return setSelectMode(getNextMmlCheckBoxItem());
		}
		break;
	case AplParamSceneVFRMode:
		if (isValidMmlFunc(VFR)) {
			return setSelectMode(VFR);
		}
		else {
			if (m_MmlCheckBox != VFR) return false;
			return setSelectMode(getNextMmlCheckBoxItem());
		}
		break;
	case AplParamMmFuncFrameRateInvalidFlag:
		if (m_MmlCheckBox != VFR) return false;
		exec();
		return setSelectMode(getNextMmlCheckBoxItem());
		break;
	case AplParamIRRec:
	case AplParamWhiteBalanceModeOSD:
		if (isValidMmlFunc(WHITE)) {
			return setSelectMode(WHITE);
		}
		else {
			if (m_MmlCheckBox != WHITE) return false;
			return setSelectMode(getNextMmlCheckBoxItem());
		}
		break;
	case AplParamAFRange:
		if (isValidMmlFunc(AF_AREA)) {
			return setConfigMode(AF_AREA);
		}
		else {
			if (m_MmlCheckBox != AF_AREA) return false;
			return setSelectMode(getNextMmlCheckBoxItem());
		}
		break;
	case AplParamAreaMode:
		if (isValidMmlFunc(AREA)) {
			return setConfigMode(AREA);
		}
		else {
			if (m_MmlCheckBox != AREA) return false;
			return setSelectMode(getNextMmlCheckBoxItem());
		}
		break;
	default:
		break;
	}

	return false;
}

bool CtContainerMml::handleTimerEvent(const CtEventTimer& Timer) {
	bool bRet = false;
	switch (Timer.getTimeUid()) {
	case CT_TIMER_ID_MML_ACT:
		return setActionMode(false);
	default:
		break;
	}
	return bRet;
}

bool CtContainerMml::setConfigMode(CHECKBOX configId) {
	if (configId == CHECKBOX_MAX) configId = m_MmlCheckBox;
	setActionMode(false);

	if (configId == ICONS) {
		m_pCrntConfig = NULL;
		//CtEventInterface::requestWindowCmd(CtEventWindow::Popup, ScreenAll, Window_TouchNavi);
		CtEventInterface::requestFuncCmd(Window_RecView, FuncID_ICONS);

	}
	if (configId == WHITE) {
		m_pCrntConfig = m_pWb;
	}
	if (configId == SHUTTER || configId == SYNCRO) {
		m_pCrntConfig = m_pShutter;
	}
	if (configId == VFR) {
		m_pCrntConfig = m_pFrameRate;
	}
	if (configId == AREA) {
		if (m_pCrntConfig)m_pCrntConfig->setMmlAct(false);
		m_pCrntConfig = NULL;
	    CtICManager::getInstance()->setMmlAct(true, (CtMenuOutputId)m_pMml->getWidgetID());
		CtEventInterface::requestFuncCmd(Window_RecView, FuncID_AREA_MML_EXEC);
	}
	if (configId == AF_AREA) {
		if (m_pCrntConfig)m_pCrntConfig->setMmlAct(false);
		m_pCrntConfig = NULL;
	    CtICManager::getInstance()->setMmlAct(true, (CtMenuOutputId)m_pMml->getWidgetID());
		CtEventInterface::requestFuncCmd(Window_RecView, FuncID_AF_AREA_MML_EXEC);
	}
	if (m_pCrntConfig) CtICManager::getInstance()->setMmlAct(true, (CtMenuOutputId)m_pCrntConfig->getWidgetID());

	m_MmlCheckBox = configId;
	setMmlString(configId);

	if (configId != ICONS) {
		if (m_pCrntConfig)m_pCrntConfig->setMmlAct(true);
		m_MmlMode = CONFIG;
	}
	return true;
}

bool CtContainerMml::setSelectMode(CHECKBOX selectMode) {
	if (CHECKBOX_MAX == selectMode) selectMode = m_MmlCheckBox;
	if (SYNCRO == selectMode) selectMode = SHUTTER;

	if (m_MmlMode == CONFIG && selectMode != m_MmlCheckBox) {
		// Config’†‚É•Ê‚ÌCheckBox‚ðŽw’è‚³‚ê‚½‚çCancel“®ì‚³‚¹‚é
		cancel();
	}

	if (m_pCrntConfig) {
		m_pCrntConfig->setMmlAct(false);
		if (m_pCrntConfig) CtICManager::getInstance()->setMmlAct(false, (CtMenuOutputId)m_pCrntConfig->getWidgetID());
	}
	m_MmlCheckBox = selectMode;
	m_MmlMode = SELECT;
	m_pCrntConfig = NULL;
	setMmlString(selectMode);

	setActionMode(true);	/* pgr2711 */
	return true;
}

bool CtContainerMml::inc(const CtEventKey::KeyTimerLevel _lv) {

	if (m_MmlMode == SELECT) {
		m_MmlCheckBox = (CHECKBOX)getNextMmlCheckBoxItem(true);
		setMmlString(m_MmlCheckBox);
	}
	else if (m_MmlMode == CONFIG) {
		CtFuncID funcId = FuncID_MAX;
		if (m_MmlCheckBox == SHUTTER)	funcId = FuncID_SHUTTER_MML_UP;// Shutter/Syncro“¯“™
		if (m_MmlCheckBox == VFR)		funcId = FuncID_VFR_MML_UP;
		if (m_MmlCheckBox == AREA)		funcId = FuncID_AREA_MML_UP;
		if (m_MmlCheckBox == AF_AREA)	funcId = FuncID_AF_AREA_MML_UP;
		if (m_MmlCheckBox == SYNCRO) {
			switch (_lv) {
				case CtEventKey::Level1:
				case CtEventKey::Level_Default:		funcId = FuncID_SYNCRO_MML_UP;		break;
				case CtEventKey::Level2:			funcId = FuncID_SYNCRO_MML_UP_LV_2;	break;
				case CtEventKey::Level3:			funcId = FuncID_SYNCRO_MML_UP_LV_5;	break;
				case CtEventKey::Level4:
				default:							funcId = FuncID_SYNCRO_MML_UP_LV_10;break;
			}
		}
		if (m_MmlCheckBox == WHITE) {
			switch (_lv) {
				case CtEventKey::Level_Default:
				case CtEventKey::Level1:				funcId = FuncID_WB_MML_UP;			break;
				case CtEventKey::Level2:				funcId = FuncID_WB_MML_UP_LV_2;		break;
				case CtEventKey::Level3:				funcId = FuncID_WB_MML_UP_LV_5;		break;
				case CtEventKey::Level4:
				default:								funcId = FuncID_WB_MML_UP_LV_10;	break;
			}
		}
		CtEventInterface::requestFuncCmd(Window_RecView, funcId);
	}

	if (m_pCrntConfig)CtICManager::getInstance()->setMmlAct(true, (CtMenuOutputId)m_pCrntConfig->getWidgetID());
	return true;
}

bool CtContainerMml::dec(const CtEventKey::KeyTimerLevel _lv) {

	if (m_MmlMode == SELECT) {
		m_MmlCheckBox = (CHECKBOX)getNextMmlCheckBoxItem(false);
		setMmlString(m_MmlCheckBox);
	}
	else if (m_MmlMode == CONFIG) {
		CtFuncID funcId = FuncID_MAX;

		if (m_MmlCheckBox == SHUTTER)	funcId = FuncID_SHUTTER_MML_DOWN;
		if (m_MmlCheckBox == VFR)		funcId = FuncID_VFR_MML_DOWN;
		if (m_MmlCheckBox == AREA)		funcId = FuncID_AREA_MML_DOWN;
		if (m_MmlCheckBox == AF_AREA)	funcId = FuncID_AF_AREA_MML_DOWN;
		if (m_MmlCheckBox == SYNCRO) {
			switch (_lv) {
				case CtEventKey::Level1:
				case CtEventKey::Level_Default:	funcId = FuncID_SYNCRO_MML_DOWN; break;
				case CtEventKey::Level2:		funcId = FuncID_SYNCRO_MML_DOWN_LV_2; break;
				case CtEventKey::Level3:		funcId = FuncID_SYNCRO_MML_DOWN_LV_5; break;
				case CtEventKey::Level4:
				default:						funcId = FuncID_SYNCRO_MML_DOWN_LV_10; break;
			}
		}
		if (m_MmlCheckBox == WHITE) {
			switch (_lv) {
			case CtEventKey::Level_Default:
			case CtEventKey::Level1:			funcId = FuncID_WB_MML_DOWN; break;
			case CtEventKey::Level2:			funcId = FuncID_WB_MML_DOWN_LV_2; break;
			case CtEventKey::Level3:			funcId = FuncID_WB_MML_DOWN_LV_5; break;
			case CtEventKey::Level4:
			default:							funcId = FuncID_WB_MML_DOWN_LV_10; break;
			}
		}
		CtEventInterface::requestFuncCmd(Window_RecView, funcId);
	}
	return true;
}

bool CtContainerMml::exec() {
	if (m_MmlMode == SELECT) {
		return setConfigMode();
	}
	else if (m_MmlMode == CONFIG) {
		CtFuncID funcId = FuncID_MAX;

		switch (m_MmlCheckBox) {
		case WHITE:	funcId = FuncID_WB_MML_DECIDE;	break;
		case SHUTTER:
			if (isValidMmlFunc(SYNCRO)) {
				m_MmlCheckBox = SYNCRO;
				setMmlString(SYNCRO);
				return true;
			}
			else {
				funcId = FuncID_SHUTTER_MML_DECIDE;
			}
			break;
		case VFR:		funcId = FuncID_VFR_MML_DECIDE;		break;
		case AREA:		funcId = FuncID_AREA_MML_DECIDE;	break;
		case AF_AREA:	funcId = FuncID_AF_AREA_MML_DECIDE;	break;
		case SYNCRO:	funcId = FuncID_SYNCRO_MML_DECIDE;	break;
		default:
			break;
		}
		CtEventInterface::requestFuncCmd(Window_RecView, funcId);

		setSelectMode();
		return true;
	}
	return false;
}

bool CtContainerMml::cancel() {
	if (m_MmlMode != CONFIG) {
		return false;
	}
	CtFuncID funcId = FuncID_MAX;
	switch (m_MmlCheckBox) {
		case WHITE:		funcId = FuncID_WB_MML_CANCEL;		break;
		case SHUTTER:	funcId = FuncID_SHUTTER_MML_CANCEL;	break;
		case VFR:		funcId = FuncID_VFR_MML_CANCEL;		break;
		case AREA:		funcId = FuncID_AREA_MML_CANCEL;	break;
		case AF_AREA:	funcId = FuncID_AF_AREA_MML_CANCEL;	break;
		case SYNCRO:	funcId = FuncID_SYNCRO_MML_CANCEL;	break;
		default:		break;
	}
	CtEventInterface::requestFuncCmd(Window_RecView, funcId);
	
	m_MmlMode = SELECT;
	setSelectMode();
	return true;
}

bool CtContainerMml::areaPos(CtEventKey::KeyCode KeyCode) {
	// AREA ‘€ì
	switch (KeyCode) {
	case CtEventKey::KeyCode_Up:
		CtEventInterface::requestFuncCmd(Window_RecView, FuncID_AREA_UP);
		return true;
		break;
	case CtEventKey::KeyCode_Down:
		CtEventInterface::requestFuncCmd(Window_RecView, FuncID_AREA_DOWN);
		return true;
		break;
	case CtEventKey::KeyCode_Left:
		CtEventInterface::requestFuncCmd(Window_RecView, FuncID_AREA_LEFT);
		return true;
	case CtEventKey::KeyCode_Right:
		CtEventInterface::requestFuncCmd(Window_RecView, FuncID_AREA_RIGHT);
		return true;
	default:
		break;
	}
	return false;
}

bool CtContainerMml::isValidMmlFunc(CtContainerMml::CHECKBOX MmrCheckBox) {
	switch (MmrCheckBox) {
	case ICONS:	
		return true; 
		break;
	case WHITE:
		if (APL_PARAM_GET_DATA(AplParamIRRec) == APL_SYS_PARAM_SWITCH_ON) {
			return false;
		}else if (APL_PARAM_GET_DATA(AplParamWhiteBalanceModeOSD) == 14/* VARÝ’è */) {
			return true;
		}
		else {
			CtDebugPrint(CtDbg, "WHITE INVALID\n");
			return false;
		}
		break;
	case SHUTTER:
		if (APL_PARAM_GET_DATA(AplParamAutoSwitchAutoShutter) == APL_SYS_PARAM_SWITCH_ON && APL_PARAM_GET_DATA(AplParamAutoManualSwState) == APL_SYS_PARAM_SWITCH_ON) {
			return false;
		}
		else if (APL_PARAM_GET_DATA(AplParamShutterSwitch) == APL_SYS_PARAM_SWITCH_ON) {
			return true;
		}
		else {
			CtDebugPrint(CtDbg, "SHUTTER INVALID\n");
			return false;
		}
		break;
	case SYNCRO:
		if (APL_PARAM_GET_DATA(AplParamSynchroScanMode) == APL_SYS_PARAM_SWITCH_ON) {
			if (APL_PARAM_GET_DATA(AplParamShutterSwitch) == APL_SYS_PARAM_SWITCH_ON) {
				return true;
			}
			else {
				CtDebugPrint(CtDbg, "SYNCRO INVALID\n");
				return false;
			}
		}
		else {
			CtDebugPrint(CtDbg, "SYNCRO INVALID\n");
			return false;
		}
		break;
	case VFR:
		if ( APL_PARAM_GET_DATA(AplParamMmFuncFrameRateInvalidFlag) == APL_SYS_PARAM_SWITCH_OFF
			&& APL_PARAM_GET_DATA(AplParamSceneVFRMode) == APL_SYS_PARAM_SWITCH_ON
			&& APL_PARAM_GET_DATA(AplParamSuperSlowRec) != APL_SYS_PARAM_SWITCH_ON) {
			return true;
		}
		else {
			CtDebugPrint(CtDbg, "VFR INVALID\n");
			return false;
		}
		break;
	case AREA:
		if (APL_PARAM_GET_DATA(AplParamAreaMode) == APL_SYS_PARAM_SWITCH_ON) {
			return true;
		}
		else {
			CtDebugPrint(CtDbg, "AREA INVALID\n");
			return false;
		}
		break;
	case AF_AREA:
		if (APL_PARAM_GET_DATA(AplParamAFRange) == APL_SYS_PARAM_SWITCH_ON) {
			return true;
		}
		else {
			CtDebugPrint(CtDbg, "AF AREA INVALID\n");
			return false;
		}
		break;
	default:
		break;
	}
	return false;
}

CtContainerMml::CHECKBOX CtContainerMml::getNextMmlCheckBoxItem(bool bNext) {
	if (bNext == true) {
		int next = m_MmlCheckBox;
		// ‰ÁŽZ•ûŒü
		do {
			next++;
			if (next >= CHECKBOX_MAX) {
				// ãŒÀ
				next = ICONS;
			}
			// 1Žü‚µ‚½‚ç”²‚¯‚é
			if (next == m_MmlCheckBox) break;
		} while (isValidMmlFunc((CHECKBOX)next) == false);
		return (CHECKBOX)next;
	}
	else {
		int prev = m_MmlCheckBox;
		do {
			prev--;
			if (ICONS > prev) {
				// ‰ºŒÀ
				prev = AF_AREA;
			}
			// 1Žü‚µ‚½‚ç”²‚¯‚é
			if (prev == m_MmlCheckBox) break;
		} while (isValidMmlFunc((CHECKBOX)prev) == false);
		return (CHECKBOX)prev;
	}
	return ICONS;
}

bool CtContainerMml::setMmlString(CHECKBOX selectMode) {
	GDI_STRING_ID strId = STR_ID_NO_11472;
	switch (selectMode) {
	case ICONS:		strId = STR_ID_NO_11472; break;
	case WHITE:		strId = STR_ID_NO_10673; break;
	case SHUTTER:	strId = STR_ID_NO_10790; break;
	case SYNCRO:	strId = STR_ID_NO_11473; break;
	case VFR:		strId = STR_ID_NO_11474; break;
	case AREA:		strId = STR_ID_NO_11478; break;
	case AF_AREA:	strId = STR_ID_NO_11475; break;
	default:								 return false;
	}
	return m_pMml->setStringID(strId);
}

bool CtContainerMml::setActionMode(bool bAction) {
	if (bAction == true) {
		if (m_MmlMode != SELECT) return false;
		m_fset.setColor(CtColor::orange);
		m_pMml->setFontSet(m_fset);

		m_pMmlIcon->setImage(IC_OSD_DIAL_SELECT);
		CtTimer::getInstance()->setAlarm(CT_TIMER_ID_MML_ACT, ACT_TIMER_SEC, this);
		CtICManager::getInstance()->setMmlAct(true, IC_SEL_MML);
		return true;
	}
	else {
		m_fset.setColor(CtColor::White);
		m_pMml->setFontSet(m_fset);

		m_pMmlIcon->setImage(IC_OSD_DIAL);
		CtTimer::getInstance()->cancelAlarm(CT_TIMER_ID_MML_ACT, this);
		CtICManager::getInstance()->setMmlAct(false, IC_SEL_MML);
		return true;
	}
	return false;
}
