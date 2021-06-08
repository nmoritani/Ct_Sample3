/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#include "CtModeCheckAudio.h"

CtModeCheckAudio::CtModeCheckAudio() :
	m_pAll(NULL)
{

}

CtModeCheckAudio::~CtModeCheckAudio()
{
}

CtLayout* CtModeCheckAudio::createContainer()
{
	CtRecViewFontSet fset = CtRecViewFontSet();
	CtRecViewFontSet fBlackSet = CtRecViewFontSet();
	fBlackSet.fontColor = CtColor::Black;
	fBlackSet.edgeColor = CtColor::NoColor;

	m_pAll = new CtLayout();
	{
		CtVLayout* pV = new CtVLayout();
		{
			pV->addStretch(1, ScreenLCD);
			CtHLayout* pH = new CtHLayout();
			{
				pH->addStretch(4);
				CtVLayout* pAudioBlock = new CtVLayout();
				{
					CtHLayout* pAudioTitleLine = new CtHLayout();
					{
						pAudioTitleLine->addStretch(17);
						CtHLayout* pH = new CtHLayout();
						{
							pH->addWidget(new CtLabel("-- ", fset), 3);
							pH->addWidget(new CtLabel(STR_ID_NO_10669, fset), 5);
							pH->addWidget(new CtLabel(" --", fset), 3);
							pAudioTitleLine->addWidget(pH,11);
						}
						pAudioTitleLine->addStretch(17);
					}
					pAudioBlock->addWidget(pAudioTitleLine, 1);

					CtHLayout* pAudioOutLine = new CtHLayout();
					{
						pAudioOutLine->addWidget(new CtLabel(STR_ID_NO_11522, fset), AlignLeft, 9);
						pAudioOutLine->addWidget(new CtLabel(":", fset), AlignLeft, 1);
						pAudioOutLine->addStretch(1);
						m_pAudioOut = new CtLabel("", fset);
						pAudioOutLine->addWidget(m_pAudioOut, AlignLeft, 12);
						pAudioOutLine->addStretch(26);
					}
					pAudioBlock->addWidget(pAudioOutLine, 1);
					pAudioBlock->addStretch(1);

					CtHLayout* pAudioAudioSwLine = new CtHLayout();
					{
						CtVLayout* pAudioSwName = new CtVLayout();
						{
							pAudioSwName->addStretch(1);
							CtHLayout* pH = new CtHLayout();
							{
								pH->addWidget(new CtLabel(STR_ID_NO_10840, fset), AlignLeft, 3);
								pH->addWidget(new CtLabel(":", fset), AlignLeft, 1);
								pAudioSwName->addWidget(pH, 1);
							}
							pH = new CtHLayout();
							{
								pH->addWidget(new CtLabel(STR_ID_NO_10841, fset), AlignLeft, 3);
								pH->addWidget(new CtLabel(":", fset), AlignLeft, 1);
								pAudioSwName->addWidget(pH, 1);
							}
						}
						pAudioAudioSwLine->addWidget(pAudioSwName, 4);
						pAudioAudioSwLine->addStretch(1);

						CtVLayout* pAudioSwPos = new CtVLayout();
						{
							CtLayout* pAudioSw = new CtLayout();
							pAudioSw->addWidget(new CtLabel(STR_ID_NO_11525, fBlackSet), AlignLeft);
							pAudioSw->setColor(CtColor::White);
							pAudioSwPos->addWidget(pAudioSw, AlignLeft, 1);

							m_pCh1Select = new CtLabel("", fset);
							pAudioSwPos->addWidget(m_pCh1Select, AlignLeft, 1);
							m_pCh2Select = new CtLabel("", fset);
							pAudioSwPos->addWidget(m_pCh2Select, AlignLeft, 1);
						}
						pAudioAudioSwLine->addWidget(pAudioSwPos, 6);
						pAudioAudioSwLine->addStretch(2);

						CtVLayout* pLineMic = new CtVLayout();
						{
							CtLayout* pLevel = new CtLayout();
							pLevel->addWidget(new CtLabel(STR_ID_NO_11526, fBlackSet), AlignLeft);
							pLevel->setColor(CtColor::White);
							pLineMic->addWidget(pLevel, 1);

							m_pCh1LineMic = new CtLabel("", fset);
							pLineMic->addWidget(m_pCh1LineMic, AlignLeft, 1);
							m_pCh2LineMic = new CtLabel("", fset);
							pLineMic->addWidget(m_pCh2LineMic, AlignLeft, 1);
						}
						pAudioAudioSwLine->addWidget(pLineMic, 8);
						pAudioAudioSwLine->addStretch(2);

						CtVLayout* pAudioLevel = new CtVLayout();
						{
							CtLayout* pLevel = new CtLayout();
							pLevel->addWidget(new CtLabel(STR_ID_NO_11528, fBlackSet));
							pLevel->setColor(CtColor::White);
							pAudioLevel->addWidget(pLevel, AlignLeft, 1);

							m_pCh1Level = new CtLabel("", fset);
							pAudioLevel->addWidget(m_pCh1Level, AlignLeft, 1);
							m_pCh2Level = new CtLabel("", fset);
							pAudioLevel->addWidget(m_pCh2Level, AlignLeft, 1);
						}
						pAudioAudioSwLine->addWidget(pAudioLevel, 5);
						pAudioAudioSwLine->addStretch(2);

						CtVLayout* pAudioLimiter = new CtVLayout();
						{
							CtLayout* pLimiter = new CtLayout();
							pLimiter->addWidget(new CtLabel(STR_ID_NO_10722, fBlackSet), AlignLeft);
							pLimiter->setColor(CtColor::White);
							pAudioLimiter->addWidget(pLimiter, 1);

							m_pCh1Limiter = new CtLabel("", fset);
							pAudioLimiter->addWidget(m_pCh1Limiter, AlignLeft, 1);
							m_pCh2Limiter = new CtLabel("", fset);
							pAudioLimiter->addWidget(m_pCh2Limiter, AlignLeft, 1);
						}
						pAudioAudioSwLine->addWidget(pAudioLimiter, 7);
						pAudioAudioSwLine->addStretch(2);

						CtVLayout* pAudioLowcut = new CtVLayout();
						{
							CtLayout* pLowcut = new CtLayout();
							pLowcut->addWidget(new CtLabel(STR_ID_NO_10719, fBlackSet), AlignLeft);
							pLowcut->setColor(CtColor::White);
							pAudioLowcut->addWidget(pLowcut, 1);

							m_pCh1Lowcut = new CtLabel("", fset);
							pAudioLowcut->addWidget(m_pCh1Lowcut, AlignLeft, 1);
							m_pCh2Lowcut = new CtLabel("", fset);
							pAudioLowcut->addWidget(m_pCh2Lowcut, AlignLeft, 1);
						}
						pAudioAudioSwLine->addWidget(pAudioLowcut, 6);
					}
					pAudioBlock->addWidget(pAudioAudioSwLine, 3);

					CtHLayout* pAudioLevelLine = new CtHLayout();
					{
						pAudioLevelLine->addStretch(9);
						m_pAudioLevel = new CtFastContainerAudioLevel_Home();
						pAudioLevelLine->addContainer(m_pAudioLevel, 27);
						pAudioLevelLine->addStretch(9);
					}
					pAudioBlock->addWidget(pAudioLevelLine, 4);
				}
				pH->addWidget(pAudioBlock, 45);
				pH->addStretch(4);
			}
			pV->addWidget(pH, 10);
			pV->addStretch(2);
			pV->addStretch(1, ScreenLCD);
		}
		m_pAll->addWidget(pV);
	}
	return m_pAll;
}

bool CtModeCheckAudio::destroyWindow()
{
	return true;
}

bool CtModeCheckAudio::startupContainer() {
	bool bRet = false;
	bRet |= updateHpOut(APL_PARAM_GET_DATA(AplParamHpOut));	/* pgr2711 */
	bRet |= updateCh1Select(APL_PARAM_GET_DATA(AplParamInSelectCH1));	/* pgr2711 */
	bRet |= updateCh1LineMic();	/* pgr2711 */
	bRet |= updateCh2Select(APL_PARAM_GET_DATA(AplParamInSelectCH2));	/* pgr2711 */
	bRet |= updateCh2LineMic();	/* pgr2711 */
	bRet |= updateCh1Level(APL_PARAM_GET_DATA(AplParamCh1Adjust));	/* pgr2711 */
	bRet |= updateCh1Limiter();	/* pgr2711 */
	bRet |= updateCh2Level(APL_PARAM_GET_DATA(AplParamCh2Adjust));	/* pgr2711 */
	bRet |= updateCh2Limiter();	/* pgr2711 */
	bRet |= updateCh1Lowcut(APL_PARAM_GET_DATA(AplParamLowCut));	/* pgr2711 */
	bRet |= updateCh2Lowcut(APL_PARAM_GET_DATA(AplParamLowCut2));	/* pgr2711 */
	return bRet;
}

bool CtModeCheckAudio::handleButtonEvent(const CtEventButton& Button)
{
	/* Release‚Å‚Ì‚Ýˆ— */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	return false;
}

bool CtModeCheckAudio::handleKeyEvent(const CtEventKey& Key) {

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
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;

}

bool CtModeCheckAudio::handleParamEvent(const CtEventParam& Param)
{
	bool bRet = false;
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamHpOut:
		bRet |= updateHpOut(int_Data);	/* pgr2711 */
		break;
	case AplParamInSelectCH1:
	case AplParamInSelectCH2:
	case AplParamSelInput1:
	case AplParamMicPower1:
	case AplParamSelInput2:
	case AplParamMicPower2:
		bRet |= updateCh1Select(int_Data);	/* pgr2711 */
		bRet |= updateCh1LineMic();	/* pgr2711 */
		bRet |= updateCh2Select(int_Data);	/* pgr2711 */
		bRet |= updateCh2LineMic();	/* pgr2711 */
		break;
	case AplParamCh1Adjust:
		bRet |= updateCh1Level(int_Data);	/* pgr2711 */
		bRet |= updateCh1Limiter();	/* pgr2711 */
		break;
	case AplParamCh2Adjust:
		bRet |= updateCh2Level(int_Data);	/* pgr2711 */
		bRet |= updateCh2Limiter();	/* pgr2711 */
		break;
	case AplParamLimiterCH1:
		bRet |= updateCh1Limiter();	/* pgr2711 */
		break;
	case AplParamLimiterCH2:
		bRet |= updateCh2Limiter();	/* pgr2711 */
		break;
	case AplParamLowCut:
		bRet |= updateCh1Lowcut(int_Data);	/* pgr2711 */
		break;
	case AplParamLowCut2:
		bRet |= updateCh2Lowcut(int_Data);	/* pgr2711 */
		break;
	default:
		break;
	}

	return bRet;
}


bool CtModeCheckAudio::updateHpOut(int int_Data) {
	switch (int_Data) {
	case APL_SYS_PARAM_HP_OUT_CH1:
		return m_pAudioOut->setStringID(STR_ID_NO_10840);
		break;
	case APL_SYS_PARAM_HP_OUT_CH2:
		return m_pAudioOut->setStringID(STR_ID_NO_10841);
		break;
	case APL_SYS_PARAM_HP_OUT_STEREO:
		return m_pAudioOut->setStringID(STR_ID_NO_11523);
		break;
	case APL_SYS_PARAM_HP_OUT_MIX:
		return m_pAudioOut->setStringID(STR_ID_NO_11524);
		break;
	case APL_SYS_PARAM_HP_OUT_CH3:
		return m_pAudioOut->setText("CH3");// Vup‘Î‰ž
		break;
	case APL_SYS_PARAM_HP_OUT_CH4:
		return m_pAudioOut->setText("CH4");// Vup‘Î‰ž
		break;
	case APL_SYS_PARAM_HP_OUT_CH34_STEREO:
		return m_pAudioOut->setText("CH3/4 STEREO");// Vup‘Î‰ž
		break;
	case APL_SYS_PARAM_HP_OUT_CH34_MIX:
		return m_pAudioOut->setText("CH3/4 MIX");// Vup‘Î‰ž
		break;
	default:
		return false;
		break;
	}
}


bool CtModeCheckAudio::updateCh1Select(int int_Data) {
	switch (APL_PARAM_GET_DATA(AplParamInSelectCH1)) {
	case APL_SYS_PARAM_CH_IN_SELECT_INT:
		return m_pCh1Select->setStringID(STR_ID_NO_10764);
		break;
	case APL_SYS_PARAM_CH_IN_SELECT_INPUT1:
		return m_pCh1Select->setStringID(STR_ID_NO_10798);
		break;
	case APL_SYS_PARAM_CH_IN_SELECT_INPUT2:
		return m_pCh1Select->setStringID(STR_ID_NO_10799);
		break;
	default:
		return false;
		break;
	}
}


bool CtModeCheckAudio::updateCh2Select(int int_Data) {
	switch (APL_PARAM_GET_DATA(AplParamInSelectCH2)) {
	case APL_SYS_PARAM_CH_IN_SELECT_INT:
		return m_pCh2Select->setStringID(STR_ID_NO_10765);
		break;
	case APL_SYS_PARAM_CH_IN_SELECT_INPUT1:
		return m_pCh2Select->setStringID(STR_ID_NO_10798);
		break;
	case APL_SYS_PARAM_CH_IN_SELECT_INPUT2:
		return m_pCh2Select->setStringID(STR_ID_NO_10799);
		break;
	default:
		return false;
		break;
	}
}

bool CtModeCheckAudio::updateCh1LineMic() {
	if (APL_PARAM_GET_DATA(AplParamInSelectCH1) == APL_SYS_PARAM_CH_IN_SELECT_INT) {
		return m_pCh1LineMic->setText("---");
	}
	else if (APL_PARAM_GET_DATA(AplParamInSelectCH1) == APL_SYS_PARAM_CH_IN_SELECT_INPUT1) {
		switch (APL_PARAM_GET_DATA(AplParamSelInput1)) {
		case APL_SYS_PARAM_SELECT_INPUT_LINE:
			return m_pCh1LineMic->setStringID(STR_ID_NO_10767);
			break;
		case APL_SYS_PARAM_SELECT_INPUT_MIC:
			if (APL_PARAM_GET_DATA(AplParamMicPower1) == APL_SYS_PARAM_SWITCH_ON) {
				return m_pCh1LineMic->setStringID(STR_ID_NO_11527);
			}
			else {
				return m_pCh1LineMic->setStringID(STR_ID_NO_10766);
			}
			break;
		default:
			return false;
			break;
		}
	}
	else if (APL_PARAM_GET_DATA(AplParamInSelectCH1) == APL_SYS_PARAM_CH_IN_SELECT_INPUT2) {
		switch (APL_PARAM_GET_DATA(AplParamSelInput2)) {
		case APL_SYS_PARAM_SELECT_INPUT_LINE:
			return m_pCh1LineMic->setStringID(STR_ID_NO_10767);
			break;
		case APL_SYS_PARAM_SELECT_INPUT_MIC:
			if (APL_PARAM_GET_DATA(AplParamMicPower2) == APL_SYS_PARAM_SWITCH_ON) {
				return m_pCh1LineMic->setStringID(STR_ID_NO_11527);
			}
			else {
				return m_pCh1LineMic->setStringID(STR_ID_NO_10766);
			}
			break;
		default:
			return false;
			break;
		}
	}
	return false;

}


bool CtModeCheckAudio::updateCh2LineMic() {
	if (APL_PARAM_GET_DATA(AplParamInSelectCH2) == APL_SYS_PARAM_CH_IN_SELECT_INT) {
		return m_pCh2LineMic->setText("---");
	}
	else if (APL_PARAM_GET_DATA(AplParamInSelectCH2) == APL_SYS_PARAM_CH_IN_SELECT_INPUT1) {
		switch (APL_PARAM_GET_DATA(AplParamSelInput1)) {
		case APL_SYS_PARAM_SELECT_INPUT_LINE:
			return m_pCh2LineMic->setStringID(STR_ID_NO_10767);
			break;
		case APL_SYS_PARAM_SELECT_INPUT_MIC:
			if (APL_PARAM_GET_DATA(AplParamMicPower1) == APL_SYS_PARAM_SWITCH_ON) {
				return m_pCh2LineMic->setStringID(STR_ID_NO_11527);
			}
			else {
				return m_pCh2LineMic->setStringID(STR_ID_NO_10766);
			}
			break;
		default:
			return false;
			break;
		}
	}
	else if (APL_PARAM_GET_DATA(AplParamInSelectCH2) == APL_SYS_PARAM_CH_IN_SELECT_INPUT2) {
		switch (APL_PARAM_GET_DATA(AplParamSelInput2)) {
		case APL_SYS_PARAM_SELECT_INPUT_LINE:
			return m_pCh2LineMic->setStringID(STR_ID_NO_10767);
			break;
		case APL_SYS_PARAM_SELECT_INPUT_MIC:
			if (APL_PARAM_GET_DATA(AplParamMicPower2) == APL_SYS_PARAM_SWITCH_ON) {
				return m_pCh2LineMic->setStringID(STR_ID_NO_11527);
			}
			else {
				return m_pCh2LineMic->setStringID(STR_ID_NO_10766);
			}
			break;
		default:
			return false;
			break;
		}
	}
	return false;
}


bool CtModeCheckAudio::updateCh1Level(int int_Data) {
	if (int_Data == APL_SYS_PARAM_CH_ADJUST_AUTO) {
		return m_pCh1Level->setStringID(STR_ID_NO_10837);
	}
	else {
		return m_pCh1Level->setStringID(STR_ID_NO_11529);
	}
}


bool CtModeCheckAudio::updateCh2Level(int int_Data) {
	if (int_Data == APL_SYS_PARAM_CH_ADJUST_AUTO) {
		return m_pCh2Level->setStringID(STR_ID_NO_10837);
	}
	else {
		return m_pCh2Level->setStringID(STR_ID_NO_11529);
	}
}

bool CtModeCheckAudio::updateCh1Limiter() {
	if (APL_PARAM_GET_DATA(AplParamCh1Adjust) == APL_SYS_PARAM_CH_ADJUST_AUTO) {
		return m_pCh1Limiter->setText("---");
	}
	else {
		if (APL_PARAM_GET_DATA(AplParamLimiterCH1) == APL_SYS_PARAM_SWITCH_ON) {
			return m_pCh1Limiter->setStringID(STR_ID_NO_10836);
		}
		else {
			return m_pCh1Limiter->setStringID(STR_ID_NO_10792);
		}
	}
}

bool CtModeCheckAudio::updateCh2Limiter() {
	if (APL_PARAM_GET_DATA(AplParamCh2Adjust) == APL_SYS_PARAM_CH_ADJUST_AUTO) {
		return m_pCh2Limiter->setText("---");
	}
	else {
		if (APL_PARAM_GET_DATA(AplParamLimiterCH2) == APL_SYS_PARAM_SWITCH_ON) {
			return m_pCh2Limiter->setStringID(STR_ID_NO_10836);
		}
		else {
			return m_pCh2Limiter->setStringID(STR_ID_NO_10792);
		}
	}
}

bool CtModeCheckAudio::updateCh1Lowcut(int int_Data) {
	if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
		return m_pCh1Lowcut->setStringID(STR_ID_NO_10836);
	}
	else {
		return m_pCh1Lowcut->setStringID(STR_ID_NO_10792);
	}

}

bool CtModeCheckAudio::updateCh2Lowcut(int int_Data) {
	if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
		return m_pCh2Lowcut->setStringID(STR_ID_NO_10836);
	}
	else {
		return m_pCh2Lowcut->setStringID(STR_ID_NO_10792);
	}
}
