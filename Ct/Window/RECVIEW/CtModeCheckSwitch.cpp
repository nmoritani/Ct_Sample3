/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#include "CtModeCheckSwitch.h"
#include "CtParameterConvIf.h"

#define CT_TEST_MODE_CHECK

CtModeCheckSwitch::CtModeCheckSwitch() :
	m_pAll(NULL)
{
}

CtModeCheckSwitch::~CtModeCheckSwitch()
{
}

CtLayout* CtModeCheckSwitch::createContainer()
{
	CtParamConvIf paramConIf;
	CtRecViewFontSet fset = CtRecViewFontSet();

	m_pAll = new CtLayout();
	{
		CtVLayout* pV = new CtVLayout();
		pV->addStretch(1, ScreenLCD);
		CtHLayout* pH = new CtHLayout();
		{
			pH->addStretch(4);
			CtVLayout* pUserLayout = new CtVLayout();
			{
				CtHLayout* pTitleLine = new CtHLayout();
				{
					pTitleLine->addStretch(3);
					CtHLayout* pH = new CtHLayout();
					{
						pH->addWidget(new CtLabel("-- ", fset), 3);
						pH->addWidget(new CtLabel(STR_ID_NO_11530, fset), 7);// STR_ID_NO_11530
						pH->addWidget(new CtLabel(" --", fset), 3);
						pTitleLine->addWidget(pH, 13);
					}
					
					pTitleLine->addStretch(5);
				}
				pUserLayout->addWidget(pTitleLine, 1);

				CtHLayout* pUser1Line = new CtHLayout();
				{
					pUser1Line->addWidget(new CtLabel("1", fset), AlignLeft, 1);
					pUser1Line->addWidget(new CtLabel(":", fset), 1);
					pUser1Line->addStretch(1);
					m_pUser1 = new CtLabel(paramConIf.convFromUserParamToStringId(APL_PARAM_GET_DATA(AplParamUserButton1)), fset);
					pUser1Line->addWidget(m_pUser1, AlignLeft, 18);
				}
				pUserLayout->addWidget(pUser1Line, 1);

				CtHLayout* pUser2Line = new CtHLayout();
				{
					pUser2Line->addWidget(new CtLabel("2", fset), AlignLeft, 1);
					pUser2Line->addWidget(new CtLabel(":", fset), 1);
					pUser2Line->addStretch(1);
					m_pUser2 = new CtLabel(paramConIf.convFromUserParamToStringId(APL_PARAM_GET_DATA(AplParamUserButton2)), fset);
					pUser2Line->addWidget(m_pUser2, AlignLeft, 18);
				}
				pUserLayout->addWidget(pUser2Line, 1);

				CtHLayout* pUser3Line = new CtHLayout();
				{
					pUser3Line->addWidget(new CtLabel("3", fset), AlignLeft, 1);
					pUser3Line->addWidget(new CtLabel(":", fset), 1);
					pUser3Line->addStretch(1);
					m_pUser3 = new CtLabel(paramConIf.convFromUserParamToStringId(APL_PARAM_GET_DATA(AplParamUserButton3)), fset);
					pUser3Line->addWidget(m_pUser3, AlignLeft, 18);
				}
				pUserLayout->addWidget(pUser3Line, 1);

				CtHLayout* pUser4Line = new CtHLayout();
				{
					pUser4Line->addWidget(new CtLabel("4", fset), AlignLeft, 1);
					pUser4Line->addWidget(new CtLabel(":", fset), 1);
					pUser4Line->addStretch(1);
					m_pUser4 = new CtLabel(paramConIf.convFromUserParamToStringId(APL_PARAM_GET_DATA(AplParamUserButton4)), fset);
					pUser4Line->addWidget(m_pUser4, AlignLeft, 18);
				}
				pUserLayout->addWidget(pUser4Line, 1);

				CtHLayout* pUser5Line = new CtHLayout();
				{
					pUser5Line->addWidget(new CtLabel("5", fset), AlignLeft, 1);
					pUser5Line->addWidget(new CtLabel(":", fset), 1);
					pUser5Line->addStretch(1);
					m_pUser5 = new CtLabel(paramConIf.convFromUserParamToStringId(APL_PARAM_GET_DATA(AplParamUserButton5)), fset);
					pUser5Line->addWidget(m_pUser5, AlignLeft, 18);
				}
				pUserLayout->addWidget(pUser5Line, 1);

				CtHLayout* pUser6Line = new CtHLayout();
				{
					pUser6Line->addWidget(new CtLabel("6", fset), AlignLeft, 1);
					pUser6Line->addWidget(new CtLabel(":", fset), 1);
					pUser6Line->addStretch(1);
					m_pUser6 = new CtLabel(paramConIf.convFromUserParamToStringId(APL_PARAM_GET_DATA(AplParamUserButton6)), fset);
					pUser6Line->addWidget(m_pUser6, AlignLeft, 18);
				}
				pUserLayout->addWidget(pUser6Line, 1);

				CtHLayout* pUser7Line = new CtHLayout();
				{
					pUser7Line->addWidget(new CtLabel("7", fset), AlignLeft, 1);
					pUser7Line->addWidget(new CtLabel(":", fset), 1);
					pUser7Line->addStretch(1);
					m_pUser7 = new CtLabel(paramConIf.convFromUserParamToStringId(APL_PARAM_GET_DATA(AplParamUserButton7)), fset);
					pUser7Line->addWidget(m_pUser7, AlignLeft, 18);
				}
				pUserLayout->addWidget(pUser7Line, 1);

				pUserLayout->addStretch(1);
				pUserLayout->addStretch(1);
			}
			pH->addWidget(pUserLayout, 21);
			pH->addStretch(3);
			CtVLayout* pCameraLayout = new CtVLayout();
			{
				//////////////////// GAIN ////////////////////
				CtHLayout* pOtherAssignLine = new CtHLayout();
				{
					pOtherAssignLine->addStretch(1);
					CtHLayout* pH = new CtHLayout();
					{
						pH->addWidget(new CtLabel("-- ", fset), 3);
						pH->addWidget(new CtLabel(STR_ID_NO_11535, fset), 12);
						pH->addWidget(new CtLabel(" --", fset), 3);
						pOtherAssignLine->addWidget(pH, 18);
					}
					
					pOtherAssignLine->addStretch(3);
				}
				pCameraLayout->addWidget(pOtherAssignLine, 1);

				CtHLayout* pGainL_Line = new CtHLayout();
				{
					pGainL_Line->addWidget(new CtLabel("GAIN ", fset), AlignRight, 5);
					pGainL_Line->addWidget(new CtLabel("L", fset), AlignRight, 1);
					
					pGainL_Line->addWidget(new CtLabel(":", fset), 1);
					pGainL_Line->addStretch(1);
					m_pGainL = new CtLabel("", fset);
					pGainL_Line->addWidget(m_pGainL, AlignLeft, 4);
					pGainL_Line->addStretch(10);
				}
				pCameraLayout->addWidget(pGainL_Line, 1);

				CtHLayout* pGainM_Line = new CtHLayout();
				{
					pGainM_Line->addStretch(5);
					pGainM_Line->addWidget(new CtLabel("M", fset), AlignLeft, 1);
					pGainM_Line->addWidget(new CtLabel(":", fset), 1);
					pGainM_Line->addStretch(1);
					m_pGainM = new CtLabel("", fset);
					pGainM_Line->addWidget(m_pGainM, AlignLeft, 4);
					pGainM_Line->addStretch(10);
				}
				pCameraLayout->addWidget(pGainM_Line, 1);

				CtHLayout* pGainH_Line = new CtHLayout();
				{
					pGainH_Line->addStretch(5);
					pGainH_Line->addWidget(new CtLabel("H", fset), AlignLeft, 1);
					pGainH_Line->addWidget(new CtLabel(":", fset), 1);
					pGainH_Line->addStretch(1);
					m_pGainH = new CtLabel("", fset);
					pGainH_Line->addWidget(m_pGainH, AlignLeft, 4);
					pGainH_Line->addStretch(10);
				}
				pCameraLayout->addWidget(pGainH_Line, 1);

				CtHLayout* pS_Gain_Line = new CtHLayout();
				{
					pS_Gain_Line->addWidget(new CtLabel("S.GAI", fset), AlignRight, 5);
					pS_Gain_Line->addWidget(new CtLabel("N", fset), AlignRight, 1);
					pS_Gain_Line->addWidget(new CtLabel(":", fset), 1);
					pS_Gain_Line->addStretch(1);
					m_pS_Gain = new CtLabel("", fset);
					pS_Gain_Line->addWidget(m_pS_Gain, AlignLeft, 14);
				}
				pCameraLayout->addWidget(pS_Gain_Line, 1);

				pCameraLayout->addStretch(1);

				//////////////////// WB ////////////////////
				CtHLayout* pWbLine = new CtHLayout();
				{
					pWbLine->addWidget(new CtLabel(STR_ID_NO_11537, fset), 9);
					pWbLine->addStretch(13);
				}
				pCameraLayout->addWidget(pWbLine, 1);

				CtHLayout* pWbA_Line = new CtHLayout();
				{
					pWbA_Line->addStretch(5);
					pWbA_Line->addWidget(new CtLabel("A", fset), AlignRight, 1);
					pWbA_Line->addWidget(new CtLabel(":", fset), 1);
					pWbA_Line->addStretch(1);
					m_pWbA = new CtLabel("", fset); // Val
					pWbA_Line->addWidget(m_pWbA, AlignLeft, 6);
					pWbA_Line->addStretch(8);
				}
				pCameraLayout->addWidget(pWbA_Line, 1);

				CtHLayout* pWbB_Line = new CtHLayout();
				{
					// ‰EŠñ‚¹‚Ì‚½‚ßAStretch•ªLabel‚Ì—Ìˆæ‚Æ‚·‚é
					pWbB_Line->addStretch(5);
					pWbB_Line->addWidget(new CtLabel("B", fset), AlignRight, 1);
					pWbB_Line->addWidget(new CtLabel(":", fset), 1);
					pWbB_Line->addStretch(1);
					m_pWbB = new CtLabel("", fset);
					pWbB_Line->addWidget(m_pWbB, AlignLeft, 6); // Val
					pWbB_Line->addStretch(8);
				}
				pCameraLayout->addWidget(pWbB_Line, 1);

				CtHLayout* pWbPrst_Line = new CtHLayout();
				{
					pWbPrst_Line->addStretch(2);
					pWbPrst_Line->addWidget(new CtLabel("PRST", fset), AlignRight, 4);
					pWbPrst_Line->addWidget(new CtLabel(":",fset), 1);
					pWbPrst_Line->addStretch(1);
					m_pWbPrst = new CtLabel("", fset); // Val
					pWbPrst_Line->addWidget(m_pWbPrst, AlignLeft, 10);
					pWbPrst_Line->addStretch(4);
				}
				pCameraLayout->addWidget(pWbPrst_Line, 1);
			}
			pH->addWidget(pCameraLayout, 22);
			pH->addStretch(3);
		}
		pV->addWidget(pH, 10);
		pV->addStretch(2);
		pV->addStretch(1, ScreenLCD);

		m_pAll->addWidget(pV);
	}

	return m_pAll;
}

bool CtModeCheckSwitch::destroyWindow()
{
	return true;
}

bool CtModeCheckSwitch::startupContainer() {
	updateUserSw(AplParamUserButton1, m_pUser1);
	updateUserSw(AplParamUserButton2, m_pUser2);
	updateUserSw(AplParamUserButton3, m_pUser3);
	updateUserSw(AplParamUserButton4, m_pUser4);
	updateUserSw(AplParamUserButton5, m_pUser5);
	updateUserSw(AplParamUserButton6, m_pUser6);
	updateUserSw(AplParamUserButton7, m_pUser7);

	updateGainSwLow(APL_PARAM_GET_DATA(AplParamGainLow));
	updateGainSwMid(APL_PARAM_GET_DATA(AplParamGainMid));
	updateGainSwHigh(APL_PARAM_GET_DATA(AplParamGainHigh));
	updateS_Gain(APL_PARAM_GET_DATA(AplParamSuperGainSW));
	updateWBSw();
	return true;
}

bool CtModeCheckSwitch::handleButtonEvent(const CtEventButton& Button)
{
	/* Release‚Å‚Ì‚İˆ— */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	return false;
}

bool CtModeCheckSwitch::handleKeyEvent(const CtEventKey& Key) {

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_MmrMinus:
		case CtEventKey::KeyCode_MmrPlus:
		case CtEventKey::KeyCode_Up:
		case CtEventKey::KeyCode_Down:
		case CtEventKey::KeyCode_Right:
		case CtEventKey::KeyCode_Left:
		case CtEventKey::KeyCode_Enter:
		case CtEventKey::KeyCode_ManualFunction:
			return true;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;
}

bool CtModeCheckSwitch::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();
	bool bRet = false;

	switch (t_Id) {
	case AplParamUserButton1:
		bRet |= updateUserSw(t_Id, m_pUser1);	/* pgr2711 */
		break;
	case AplParamUserButton2:
		bRet |= updateUserSw(t_Id, m_pUser2);	/* pgr2711 */
		break;
	case AplParamUserButton3:
		bRet |= updateUserSw(t_Id, m_pUser3);	/* pgr2711 */
		break;
	case AplParamUserButton4:
		bRet |= updateUserSw(t_Id, m_pUser4);	/* pgr2711 */
		break;
	case AplParamUserButton5:
		bRet |= updateUserSw(t_Id, m_pUser5);	/* pgr2711 */
		break;
	case AplParamUserButton6:
		bRet |= updateUserSw(t_Id, m_pUser6);	/* pgr2711 */
		break;
	case AplParamUserButton7:
		bRet |= updateUserSw(t_Id, m_pUser7);	/* pgr2711 */
		break;
	case AplParamGainLow:
		bRet |= updateGainSwLow(int_Data);	/* pgr2711 */
		break;
	case AplParamGainMid:
		bRet |= updateGainSwMid(int_Data);	/* pgr2711 */
		break;
	case AplParamGainHigh:
		bRet |= updateGainSwHigh(int_Data);	/* pgr2711 */
		break;
	case AplParamSuperGainSW:
		bRet |= updateS_Gain(int_Data);	/* pgr2711 */
		break;
	case AplParamWhiteBalancePreSetMode:
	case AplParamATWSet:
	case AplParamWbVar:
	case AplParamSceneAchColorTemp:
	case AplParamSceneBchColorTemp:
		updateWBSw();
		break;
	default:
		break;
	}

	return bRet;
}

bool CtModeCheckSwitch::updateUserSw(int t_Id, CtLabel*& pUserSwNo) {

	CtParamConvIf paramConvIf;
	if (pUserSwNo)
		return pUserSwNo->setStringID(paramConvIf.convFromUserParamToStringId(APL_PARAM_GET_DATA(t_Id)));
	return false;
}

bool CtModeCheckSwitch::updateGainSwLow(int int_Data) {
	char str[64] = { 0 };
	char gainLow = (char)(int_Data);
	sprintf(str, "%2ddB", gainLow);
	return m_pGainL->setText(str);
}

bool CtModeCheckSwitch::updateGainSwMid(int int_Data) {
	char str[64] = { 0 };
	char gainMid = (char)(int_Data);
	sprintf(str, "%2ddB", gainMid);
	return m_pGainM->setText(str);
}

bool CtModeCheckSwitch::updateGainSwHigh(int int_Data) {
	char str[64] = { 0 };
	char gainHigh = (char)(int_Data);
	sprintf(str, "%2ddB", gainHigh);
	return m_pGainH->setText(str);
}

bool CtModeCheckSwitch::updateS_Gain(int int_Data) {
	char str[64] = { 0 };

	switch (int_Data) {
	case APL_SYS_PARAM_SUPER_GAIN_SW_24DB:
		sprintf(str, "%-14s", "24dB");
		break;
	case APL_SYS_PARAM_SUPER_GAIN_SW_30DB:
		sprintf(str, "%-14s", "30dB");
		break;
	case APL_SYS_PARAM_SUPER_GAIN_SW_36DB:
		sprintf(str, "%-14s", "36dB");
		break;
	case APL_SYS_PARAM_SUPER_GAIN_SW_ALL:
		sprintf(str, "%-14s","24dB,30dB,36dB");
		break;
	default:
		break;
	}

	return m_pS_Gain->setText(str);
}

bool CtModeCheckSwitch::updateWBSw() {
	int ATW_SW = APL_PARAM_GET_DATA(AplParamATWSet);
	char val[32];
	memset(val, NULL, sizeof(val));

	if(ATW_SW == APL_SYS_PARAM_ATW_SET_PRST) {
		m_pWbPrst->setStringID(STR_ID_NO_10762);
		
		sprintf(val, "%-dK", APL_PARAM_GET_DATA(AplParamSceneAchColorTemp));
		m_pWbA->setText(val);

		memset(val, NULL, sizeof(val));
		sprintf(val, "%-dK", APL_PARAM_GET_DATA(AplParamSceneBchColorTemp));
		m_pWbB->setText(val);

	}else if (ATW_SW == APL_SYS_PARAM_ATW_SET_A_CH) {
		m_pWbA->setStringID(STR_ID_NO_10762);
		
		sprintf(val, "%-dK", APL_PARAM_GET_DATA(AplParamSceneBchColorTemp));
		m_pWbB->setText(val);

		if (APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_VAR) {
			memset(val, NULL, sizeof(val));
			sprintf(val, "%-dK VAR", APL_PARAM_GET_DATA(AplParamWbVar));
			m_pWbPrst->setText(val);
		}
		else if (APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_3200K) {
			m_pWbPrst->setText("3200K");
		}
		else if (APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_5600K) {
			m_pWbPrst->setText("5600K");
		}

	}else if (ATW_SW == APL_SYS_PARAM_ATW_SET_B_CH) {
		m_pWbB->setStringID(STR_ID_NO_10762);
		
		sprintf(val, "%-dK", APL_PARAM_GET_DATA(AplParamSceneAchColorTemp));
		m_pWbA->setText(val);

		if (APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_VAR) {
			memset(val, NULL, sizeof(val));
			sprintf(val, "%-dK VAR", APL_PARAM_GET_DATA(AplParamWbVar));
			m_pWbPrst->setText(val);
		}
		else if (APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_3200K) {
			m_pWbPrst->setText("3200K");
		}
		else if (APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_5600K) {
			m_pWbPrst->setText("5600K");
		}

	}
	else {
		char val[32];
		memset(val, NULL, sizeof(val));
		sprintf(val, "%-dK", APL_PARAM_GET_DATA(AplParamSceneAchColorTemp));
		m_pWbA->setText(val);

		memset(val, NULL, sizeof(val));
		sprintf(val, "%-dK", APL_PARAM_GET_DATA(AplParamSceneBchColorTemp));
		m_pWbB->setText(val);

		if (APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_VAR) {
			memset(val, NULL, sizeof(val));
			sprintf(val, "%-dK VAR", APL_PARAM_GET_DATA(AplParamWbVar));
			m_pWbPrst->setText(val);
		}
		else if(APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_3200K){
			m_pWbPrst->setText("3200K");
		}
		else if (APL_PARAM_GET_DATA(AplParamWhiteBalancePreSetMode) == APL_SYS_PARAM_WB_PRE_SET_MODE_5600K) {
			m_pWbPrst->setText("5600K");
		}

	}
	return true;
}
