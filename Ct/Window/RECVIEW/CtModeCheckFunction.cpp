/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#include "CtModeCheckFunction.h"

CtModeCheckFunction::CtModeCheckFunction() :
	m_pAll(NULL)
{
}

CtModeCheckFunction::~CtModeCheckFunction()
{
}

CtLayout* CtModeCheckFunction::createContainer()
{
	CtRecViewFontSet fset = CtRecViewFontSet();

	m_pAll = new CtLayout(CtColor::Trans);

	CtVLayout* pV = new CtVLayout();
	{
		pV->addStretch(1, ScreenLCD);
		CtHLayout* pVideoOutHdrSdr = new CtHLayout();
		{
			pVideoOutHdrSdr->addStretch(2);
			CtVLayout* pVideoOut = new CtVLayout();
			{
				CtHLayout* pVideoOutTitle = new CtHLayout();
				{
					pVideoOutTitle->addStretch(8);
					CtHLayout* pH = new CtHLayout();
					{
						pH->addWidget(new CtLabel("-- ", fset), 3);
						pH->addWidget(new CtLabel(STR_ID_NO_11505, fset), 9);
						pH->addWidget(new CtLabel(" --", fset), 3);
						pVideoOutTitle->addWidget(pH, 15);
					}
					pVideoOutTitle->addStretch(10);
				}
				pVideoOut->addWidget(pVideoOutTitle, 1);

				CtHLayout* pVideoOutSel = new CtHLayout();
				{
					pVideoOutSel->addWidget(new CtLabel(STR_ID_NO_11506, fset), AlignLeft, 15);
					pVideoOutSel->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pVideoOutSel->addStretch(1);
					m_pVideoOutSel = new CtLabel("", fset);
					pVideoOutSel->addWidget(m_pVideoOutSel, AlignLeft, 16);
				}
				pVideoOut->addWidget(pVideoOutSel, 1);

				CtHLayout* pSdiOutFormat = new CtHLayout();
				{
					m_pSdiOutFormatTitle = new CtLabel(STR_ID_NO_11507, fset);
					pSdiOutFormat->addWidget(m_pSdiOutFormatTitle, AlignLeft, 15);
					pSdiOutFormat->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pSdiOutFormat->addStretch(1);
					m_pSdiOutFormat = new CtLabel("", fset);
					pSdiOutFormat->addWidget(m_pSdiOutFormat, AlignLeft, 16);
				}
				pVideoOut->addWidget(pSdiOutFormat, 1);

				CtHLayout* pSdiOutChar = new CtHLayout();
				{
					m_pSdiOutCharTitle = new CtLabel(STR_ID_NO_11509, fset);
					pSdiOutChar->addWidget(m_pSdiOutCharTitle, AlignLeft, 15);
					pSdiOutChar->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pSdiOutChar->addStretch(1);
					m_pSdiOutChar = new CtLabel("", fset);
					pSdiOutChar->addWidget(m_pSdiOutChar, AlignLeft, 16);
				}
				pVideoOut->addWidget(pSdiOutChar, 1);

				CtHLayout* pHdmiOutFormat = new CtHLayout();
				{
					pHdmiOutFormat->addWidget(new CtLabel(STR_ID_NO_11511, fset), AlignLeft, 15);
					pHdmiOutFormat->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pHdmiOutFormat->addStretch(1);
					m_pHdmiOutFormat = new CtLabel("", fset);
					pHdmiOutFormat->addWidget(m_pHdmiOutFormat, AlignLeft, 16);
				}
				pVideoOut->addWidget(pHdmiOutFormat, 1);

				CtHLayout* pHdmiOutChar = new CtHLayout();
				{
					pHdmiOutChar->addWidget(new CtLabel(STR_ID_NO_11512, fset), AlignLeft, 15);
					pHdmiOutChar->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pHdmiOutChar->addStretch(1);
					m_pHdmiOutChar = new CtLabel("", fset);
					pHdmiOutChar->addWidget(m_pHdmiOutChar, AlignLeft, 16);
				}
				pVideoOut->addWidget(pHdmiOutChar, 1);
			}
			pVideoOutHdrSdr->addWidget(pVideoOut, 33);
			pVideoOutHdrSdr->addStretch(2);
			CtVLayout* pHdrSdr = new CtVLayout();
			{
				CtHLayout* pH = new CtHLayout();
				pH->addWidget(new CtLabel("-- ", fset), 3);
				pH->addWidget(new CtLabel(STR_ID_NO_11513, fset), 7);
				pH->addWidget(new CtLabel(" --", fset), 3);

				pHdrSdr->addWidget(pH);

				CtHLayout* pSdiOutLine = new CtHLayout();
				{
					m_pSdiOutTitle = new CtLabel(STR_ID_NO_10795, fset);
					pSdiOutLine->addWidget(m_pSdiOutTitle, AlignLeft, 8);
					pSdiOutLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pSdiOutLine->addStretch(1);
					m_pSdiOut = new CtLabel("", fset);
					pSdiOutLine->addWidget(m_pSdiOut, AlignLeft, 3);
				}
				pHdrSdr->addWidget(pSdiOutLine, 1);

				CtHLayout* pHdmiOutLine = new CtHLayout();
				{
					pHdmiOutLine->addWidget(new CtLabel(STR_ID_NO_10796, fset), AlignLeft, 8);
					pHdmiOutLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pHdmiOutLine->addStretch(1);
					m_pHdmiOut = new CtLabel("", fset);
					pHdmiOutLine->addWidget(m_pHdmiOut, AlignLeft, 3);
				}
				pHdrSdr->addWidget(pHdmiOutLine, 1);

				CtHLayout* pLcdVfLine = new CtHLayout();
				{
					pLcdVfLine->addWidget(new CtLabel(STR_ID_NO_11517, fset), AlignLeft, 8);
					pLcdVfLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pLcdVfLine->addStretch(1);
					m_pLcdEvf = new CtLabel("", fset);
					pLcdVfLine->addWidget(m_pLcdEvf, AlignLeft, 3);
				}
				pHdrSdr->addWidget(pLcdVfLine, 1);

				pHdrSdr->addStretch(2);
			}
			pVideoOutHdrSdr->addWidget(pHdrSdr, 13);
			pVideoOutHdrSdr->addStretch(3);
		}
		pV->addWidget(pVideoOutHdrSdr, 6);
		pV->addStretch(1);
		CtHLayout* pCardStatus = new CtHLayout();
		{
			pCardStatus->addStretch(13);

			CtVLayout* pCardStatusBlock = new CtVLayout();
			{
				CtHLayout* pCardStatusTitleLine = new CtHLayout();
				{
					pCardStatusTitleLine->addStretch(5);
					CtHLayout* pH = new CtHLayout();
					{
						pH->addWidget(new CtLabel("-- ", fset), 3);
						pH->addWidget(new CtLabel(STR_ID_NO_11518, fset), 11);
						pH->addWidget(new CtLabel(" --", fset), 3);
						pCardStatusTitleLine->addWidget(pH, 17);
					}


					pCardStatusTitleLine->addStretch(5);
				}
				pCardStatusBlock->addWidget(pCardStatusTitleLine, 1);

				CtHLayout* pTotalRemainLine = new CtHLayout();
				{
					pTotalRemainLine->addWidget(new CtLabel(STR_ID_NO_11519, fset), AlignLeft, 5);
					pTotalRemainLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pTotalRemainLine->addStretch(11);
					m_pTotalRemain = new CtLabel("", fset);
					pTotalRemainLine->addWidget(m_pTotalRemain, AlignLeft, 10);
				}
				pCardStatusBlock->addWidget(pTotalRemainLine, 1);

				CtHLayout* pSlot1Line = new CtHLayout();
				{
					pSlot1Line->addWidget(new CtLabel(STR_ID_NO_11520, fset), AlignLeft, 5);
					pSlot1Line->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pSlot1Line->addStretch(1);
					m_pStkSlot1Line = new CtStackLabel();
					{
						CtLayout* pSlot1StatusLine = new CtLayout();
						{
							m_pSlot1Status = new CtLabel("", fset);
							pSlot1StatusLine->addWidget(m_pSlot1Status, AlignLeft);
						}
						m_pStkSlot1Line->addLabel(pSlot1StatusLine, 0);

						CtHLayout* pSlot1Line = new CtHLayout();
						{
							m_pSlot1RemainPer = new CtLabel("", fset);
							pSlot1Line->addWidget(m_pSlot1RemainPer, AlignLeft, 10);
							m_pSlot1Remain = new CtLabel("", fset);
							pSlot1Line->addWidget(m_pSlot1Remain, AlignLeft, 10);
						}
						m_pStkSlot1Line->addLabel(pSlot1Line, 1);
					}
					pSlot1Line->addWidget(m_pStkSlot1Line, 20);
				}
				pCardStatusBlock->addWidget(pSlot1Line, 1);

				CtHLayout* pSlot2Line = new CtHLayout();
				{
					pSlot2Line->addWidget(new CtLabel(STR_ID_NO_11521, fset), AlignLeft, 5);
					pSlot2Line->addWidget(new CtLabel(":", fset), AlignLeft, 1);
					pSlot2Line->addStretch(1);

					m_pStkSlot2Line = new CtStackLabel();
					{
						CtLayout* pSlot2StatusLine = new CtLayout();
						{
							m_pSlot2Status = new CtLabel("", fset);
							pSlot2StatusLine->addWidget(m_pSlot2Status, AlignLeft);
						}
						m_pStkSlot2Line->addLabel(pSlot2StatusLine, 0);

						CtHLayout* pSlot2Line = new CtHLayout();
						{
							m_pSlot2RemainPer = new CtLabel("",  fset);
							pSlot2Line->addWidget(m_pSlot2RemainPer, AlignLeft, 10);
							m_pSlot2Remain = new CtLabel("", fset);
							pSlot2Line->addWidget(m_pSlot2Remain, AlignLeft, 10);
						}
						m_pStkSlot2Line->addLabel(pSlot2Line, 1);
					}
					pSlot2Line->addWidget(m_pStkSlot2Line, 20);
				}
				pCardStatusBlock->addWidget(pSlot2Line, 1);
			}
			pCardStatus->addWidget(pCardStatusBlock, 27);
			pCardStatus->addStretch(13);
		}
		pV->addWidget(pCardStatus, 4);
		pV->addStretch(1);
		pV->addStretch(1, ScreenLCD);
	}
	m_pAll->addWidget(pV);
	return m_pAll;
}

bool CtModeCheckFunction::destroyWindow()
{
	return true;
}

bool CtModeCheckFunction::startupContainer() {
	updateSdiOut();
	updateHdmiOutFormat(APL_PARAM_GET_DATA(AplParamHdmiOutFormat));
	updateHdmiOutChar(APL_PARAM_GET_DATA(AplParamHdmiOutChar));
	updateHdmiOut(APL_PARAM_GET_DATA(AplParamHdmiOutHdr));
	updateLcdEvf(APL_PARAM_GET_DATA(AplParamLcdVfOutHdr));
	updateTotalRemain();
	updateSlot1();
	updateSlot2();
	return true;
}

bool CtModeCheckFunction::handleButtonEvent(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	return false;
}

bool CtModeCheckFunction::handleKeyEvent(const CtEventKey& Key) {

	switch (Key.getKeyAction()) {
	case CtEventKey::Press:
		switch (Key.getKeyCode()) {
		case CtEventKey::KeyCode_MmrMinus:
		case CtEventKey::KeyCode_MmrPlus:
		case CtEventKey::KeyCode_Up:
			return true;
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

bool CtModeCheckFunction::handleParamEvent(const CtEventParam& Param)
{
	bool bRet = false;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamOutputSelect:
	case AplParamSdiOutChar:
	case AplParamAvOutChar:
	case AplParamSdiOutFormat:
	case AplParamSdiOutHdr:
		return updateSdiOut();
		break;
	case AplParamHdmiOutFormat:
		return updateHdmiOutFormat(int_Data);
		break;
	case AplParamHdmiOutChar:
		return updateHdmiOutChar(int_Data);
		break;
	case AplParamHdmiOutHdr:
		return updateHdmiOut(int_Data);
		break;
	case AplParamLcdVfOutHdr:
		return updateLcdEvf(int_Data);
		break;
	case AplParamTotalCapacity:
	case AplParamTotalRemain:
		return updateTotalRemain();
		break;
	case AplParamSlot1Remain:
	case AplParamSlot1RemainAll:
	case AplParamSlot1ErrStatus:
		return updateSlot1();
		break;
	case AplParamSlot2Remain:
	case AplParamSlot2RemainAll:
	case AplParamSlot2ErrStatus:
		return updateSlot2();
		break;
	case AplParamSceneGammaModeSel:
		updateSdiOut();
		updateHdmiOut(APL_PARAM_GET_DATA(AplParamHdmiOutHdr));
		updateLcdEvf(APL_PARAM_GET_DATA(AplParamLcdVfOutHdr));
		return true;
	case AplParamNetworkFunc:
		updateTotalRemain();
		updateSlot1();
		updateSlot2();
		return true;
	default:
		break;
	}

	return bRet;
}

bool CtModeCheckFunction::updateSdiOut() {
	bool bRet = false;
	int OutputSelect = APL_PARAM_GET_DATA(AplParamOutputSelect);
	int SdiOutChar = APL_PARAM_GET_DATA(AplParamSdiOutChar);
	int AvOutChar = APL_PARAM_GET_DATA(AplParamAvOutChar);
	int SdiOutFormat = APL_PARAM_GET_DATA(AplParamSdiOutFormat);
	int SdiOutHdr = APL_PARAM_GET_DATA(AplParamSdiOutHdr);

	// Title更新
	switch (OutputSelect) {
	case APL_SYS_PARAM_OUTPUT_SELECT_SDI_HDMI:
		m_pSdiOutFormatTitle->setStringID(STR_ID_NO_11507);
		m_pSdiOutCharTitle->setStringID(STR_ID_NO_11509);
		m_pSdiOutTitle->setStringID(STR_ID_NO_10795);
		break;
	case APL_SYS_PARAM_OUTPUT_SELECT_HDMI_AV:
		m_pSdiOutFormatTitle->setStringID(STR_ID_NO_11508);
		m_pSdiOutCharTitle->setStringID(STR_ID_NO_11510);
		m_pSdiOutTitle->setStringID(STR_ID_NO_11514);
		break;
	default:
		break;
	}

	switch (OutputSelect) {
	case APL_SYS_PARAM_OUTPUT_SELECT_SDI_HDMI:
		bRet |= m_pVideoOutSel->setStringID(STR_ID_NO_11209);	/* pgr2711 */
		if (SdiOutChar == APL_SYS_PARAM_SWITCH_ON) {
			bRet |= m_pSdiOutChar->setStringID(STR_ID_NO_10836);	/* pgr2711 */
		}
		else {
			bRet |= m_pSdiOutChar->setStringID(STR_ID_NO_10792);	/* pgr2711 */
		}
		if (SdiOutHdr == APL_SYS_PARAM_SDI_OUT_HDR_SDR) {
			bRet |= m_pSdiOut->setStringID(STR_ID_NO_11515);	/* pgr2711 */
		}
		else {
			if (APL_SYS_PARAM_GAMMA_MODE_SEL_HLG == APL_PARAM_GET_DATA(AplParamSceneGammaModeSel)) {
				bRet |= m_pSdiOut->setStringID(STR_ID_NO_11516);	/* pgr2711 */
			}
			else {
				bRet |= m_pSdiOut->setStringID(STR_ID_NO_11515);	/* pgr2711 */
			}
		}
		break;
	case APL_SYS_PARAM_OUTPUT_SELECT_HDMI_AV:
		bRet |= m_pVideoOutSel->setStringID(STR_ID_NO_11210);	/* pgr2711 */
		if (AvOutChar == APL_SYS_PARAM_SWITCH_ON) {
			bRet |= m_pSdiOutChar->setStringID(STR_ID_NO_10836);	/* pgr2711 */
		}
		else {
			bRet |= m_pSdiOutChar->setStringID(STR_ID_NO_10792);	/* pgr2711 */
		}
		bRet |= m_pSdiOut->setStringID(STR_ID_NO_11515);	/* pgr2711 */
		break;
	default:
		return false;
		break;
	}

	if (OutputSelect == APL_SYS_PARAM_OUTPUT_SELECT_HDMI_AV) {
		if (APL_PARAM_GET_DATA(AplParamSystemFrequency) == APL_SYS_PARAM_SYSTEM_FREQUENCY_59HZ) {
			m_pSdiOutFormat->setStringID(STR_ID_NO_11211);
		}
		else {
			m_pSdiOutFormat->setStringID(STR_ID_NO_11212);
		}
	}
	else {
		switch (SdiOutFormat) {
		case APL_SYS_PARAM_SDI_FORMAT_1920_1080P:
			bRet |= m_pSdiOutFormat->setStringID(STR_ID_NO_10437);	/* pgr2711 */
			break;
		case APL_SYS_PARAM_SDI_FORMAT_1920_1080I:
			bRet |= m_pSdiOutFormat->setStringID(STR_ID_NO_10438);	/* pgr2711 */
			break;
		case APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF:
			bRet |= m_pSdiOutFormat->setStringID(STR_ID_NO_10439);	/* pgr2711 */
			break;
		case APL_SYS_PARAM_SDI_FORMAT_1280_720P:
			bRet |= m_pSdiOutFormat->setStringID(STR_ID_NO_10440);	/* pgr2711 */
			break;
		case APL_SYS_PARAM_SDI_FORMAT_720_480I:
			bRet |= m_pSdiOutFormat->setStringID(STR_ID_NO_11211);	/* pgr2711 */
			break;
		case APL_SYS_PARAM_SDI_FORMAT_720_576I:
			bRet |= m_pSdiOutFormat->setStringID(STR_ID_NO_11212);	/* pgr2711 */
			break;
		default:
			break;
		}
	}
	return bRet;
}

bool CtModeCheckFunction::updateHdmiOutFormat(int int_Data) {
	bool bRet = false;

	switch (int_Data) {
	case APL_SYS_PARAM_HDMI_FORMAT_3840_2160P:
		bRet |= m_pHdmiOutFormat->setStringID(STR_ID_NO_10436);	/* pgr2711 */
		break;
	case APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit:
		bRet |= m_pHdmiOutFormat->setStringID(STR_ID_NO_10449);	/* pgr2711 */
		break;
	case APL_SYS_PARAM_HDMI_FORMAT_1920_1080P:
		bRet |= m_pHdmiOutFormat->setStringID(STR_ID_NO_10437);	/* pgr2711 */
		break;
	case APL_SYS_PARAM_HDMI_FORMAT_1920_1080I:
		bRet |= m_pHdmiOutFormat->setStringID(STR_ID_NO_10438);	/* pgr2711 */
		break;
	case APL_SYS_PARAM_HDMI_FORMAT_1280_720P:
		bRet |= m_pHdmiOutFormat->setStringID(STR_ID_NO_10440);	/* pgr2711 */
		break;
	case APL_SYS_PARAM_HDMI_FORMAT_720_480P:
		bRet |= m_pHdmiOutFormat->setStringID(STR_ID_NO_10450);	/* pgr2711 */
		break;
	case APL_SYS_PARAM_HDMI_FORMAT_720_576P:
		bRet |= m_pHdmiOutFormat->setStringID(STR_ID_NO_10451);	/* pgr2711 */
		break;
	default:
		break;
	}
	return bRet;
}

bool CtModeCheckFunction::updateHdmiOutChar(int int_Data) {
	if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
		return m_pHdmiOutChar->setStringID(STR_ID_NO_10836);
	}
	else {
		return m_pHdmiOutChar->setStringID(STR_ID_NO_10792);
	}
}

bool CtModeCheckFunction::updateHdmiOut(int int_Data) {
	switch (int_Data) {
	case APL_SYS_PARAM_HDMI_OUT_HDR_SDR:
		return m_pHdmiOut->setStringID(STR_ID_NO_11515);
		break;
	case APL_SYS_PARAM_HDMI_OUT_HDR_HDR:
		if (APL_SYS_PARAM_GAMMA_MODE_SEL_HLG == APL_PARAM_GET_DATA(AplParamSceneGammaModeSel)) {
			return m_pHdmiOut->setStringID(STR_ID_NO_11516);
		}
		else {
			return m_pHdmiOut->setStringID(STR_ID_NO_11515);
		}
		break;
	default:
		return false;
		break;
	}
}

bool CtModeCheckFunction::updateLcdEvf(int int_Data) {
	switch (int_Data) {
	case APL_SYS_PARAM_LCDVF_OUT_HDR_SDR:
		return m_pLcdEvf->setStringID(STR_ID_NO_11515);

	case APL_SYS_PARAM_LCDVF_OUT_HDR_HDR:
		if (APL_SYS_PARAM_GAMMA_MODE_SEL_HLG == APL_PARAM_GET_DATA(AplParamSceneGammaModeSel)) {
			return m_pLcdEvf->setStringID(STR_ID_NO_11516);
		}
		else {
			return m_pLcdEvf->setStringID(STR_ID_NO_11515);
		}
		break;

	default:
		return false;
		break;
	}
}

bool CtModeCheckFunction::updateTotalRemain() {
	int totalRemain = APL_PARAM_GET_DATA(AplParamTotalRemain);
	int totalCapacity = APL_PARAM_GET_DATA(AplParamTotalCapacity);

	char RemainValue[30];
	memset(RemainValue, 0, sizeof(RemainValue));

	sprintf(RemainValue, "%3d/%3dmin", totalRemain, totalCapacity);
	m_pTotalRemain->setText(RemainValue);
	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		// NDI|HX時は常時非表示
		return m_pTotalRemain->setVisible(false);
	}
	return true;
}

bool CtModeCheckFunction::updateSlot1() {
	char RemainValue[30];
	memset(RemainValue, 0, sizeof(RemainValue));
	CtRecViewFontSet fset = CtRecViewFontSet();

	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		// NDI|HX時は常時非表示
		m_pStkSlot1Line->setVisible(false);
		return true;
	}
	else {
		m_pStkSlot1Line->setVisible(true);
	}

	int nTempSlot1Error = APL_PARAM_GET_DATA(AplParamSlot1ErrStatus);
	int nTempSlot1Remain = APL_PARAM_GET_DATA(AplParamSlot1Remain);
	int nTempSlot1RemainAll = APL_PARAM_GET_DATA(AplParamSlot1RemainAll);

	switch (nTempSlot1Error)
	{
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_WP:
		m_pStkSlot1Line->index(0);
		m_pSlot1Status->setStringID(STR_ID_NO_10730);
		break;
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SDXC:
		m_pStkSlot1Line->index(0);
		m_pSlot1Status->setStringID(STR_ID_NO_10732);
		break;
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_CARD:
		m_pSlot1Status->setStringID(STR_ID_NO_10727);
		m_pStkSlot1Line->index(0);
		break;
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SUPPORTED:
		m_pSlot1Status->setStringID(STR_ID_NO_10728);
		m_pStkSlot1Line->index(0);
		break;
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_FORMAT_ERROR:
		m_pSlot1Status->setStringID(STR_ID_NO_10729);
		m_pStkSlot1Line->index(0);
		break;
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_REMAIN:
		m_pStkSlot1Line->index(1);
		m_pSlot1RemainPer->setStringID(STR_ID_NO_10731, fset);
		break;
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_INCOMPATIBLE_CARD:
		m_pStkSlot1Line->index(1);
		if (0 == nTempSlot1RemainAll) {
			sprintf(RemainValue, "  0%%");
		}
		else {
			sprintf(RemainValue, "%3d%%", ((nTempSlot1Remain * 100) / nTempSlot1RemainAll));
		}
		{
			m_pSlot1RemainPer->setText(RemainValue, fset);
		}
		break;
	default:
		break;
	}

	if (m_pStkSlot2Line->getIndex() == 0 && m_pStkSlot1Line->getIndex() == 0) {
		m_pTotalRemain->setVisible(false);
	}
	else {
		m_pTotalRemain->setVisible(true);
		memset(RemainValue, 0, sizeof(RemainValue));
		sprintf(RemainValue, "%3d/%3dmin", nTempSlot1Remain, nTempSlot1RemainAll);
		m_pSlot1Remain->setText(RemainValue);
	}

	return true;
}

bool CtModeCheckFunction::updateSlot2() {
	char RemainValue[30];
	CtRecViewFontSet fset = CtRecViewFontSet();
	memset(RemainValue, 0, sizeof(RemainValue));

	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		// NDI|HX時は常時非表示
		m_pStkSlot2Line->setVisible(false);
		return true;
	}
	else {
		m_pStkSlot2Line->setVisible(true);
	}

	int nTempSlot2Error = APL_PARAM_GET_DATA(AplParamSlot2ErrStatus);
	int nTempSlot2Remain = APL_PARAM_GET_DATA(AplParamSlot2Remain);
	int nTempSlot2RemainAll = APL_PARAM_GET_DATA(AplParamSlot2RemainAll);

	switch (nTempSlot2Error)
	{
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_WP:
		m_pStkSlot2Line->index(0);
		m_pSlot2Status->setStringID(STR_ID_NO_10730, fset);
		break;
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC:
		m_pSlot2Status->setStringID(STR_ID_NO_10732, fset);
		m_pStkSlot2Line->index(0);
		break;
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_CARD:
		m_pSlot2Status->setStringID(STR_ID_NO_10727, fset);
		m_pStkSlot2Line->index(0);
		break;
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED:
		m_pSlot2Status->setStringID(STR_ID_NO_10728, fset);
		m_pStkSlot2Line->index(0);
		break;
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR:
		m_pSlot2Status->setStringID(STR_ID_NO_10729, fset);
		m_pStkSlot2Line->index(0);
		break;
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_REMAIN:
		m_pStkSlot2Line->index(1);
		m_pSlot2RemainPer->setStringID(STR_ID_NO_10731, fset);
		break;
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_INCOMPATIBLE_CARD:
		m_pStkSlot2Line->index(1);
		if (0 == nTempSlot2RemainAll) {
			sprintf(RemainValue, "  0%%");
		}
		else {
			sprintf(RemainValue, "%3d%%", ((nTempSlot2Remain * 100) / nTempSlot2RemainAll));
		}
		{
			m_pSlot2RemainPer->setText(RemainValue, fset);
		}
		break;
	default:
		break;
	}
	if (m_pStkSlot2Line->getIndex() == 0 && m_pStkSlot1Line->getIndex() == 0) {
		m_pTotalRemain->setVisible(false);
	}
	else {
		m_pTotalRemain->setVisible(true);
		memset(RemainValue, 0, sizeof(RemainValue));
		sprintf(RemainValue, "%3d/%3dmin", nTempSlot2Remain, nTempSlot2RemainAll);
		m_pSlot2Remain->setText(RemainValue, fset);
	}
	return true;
}
