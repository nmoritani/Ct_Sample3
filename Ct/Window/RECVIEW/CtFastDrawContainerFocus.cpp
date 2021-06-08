/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtFastDrawContainerFocus
 */
#include "CtFastDrawContainerFocus.h"
#include <math.h>

int digit_length(int num) {
	int count = 0;
	while (num) {
		num = num / 10;
		++count;
	}
	return count;
}

#ifdef WIN32_GUI_SIM
static int m_value = 0;
static int m_add = 33;
#endif

CtFastDrawContainerFocus::CtFastDrawContainerFocus() :
	m_pAll(NULL),
	m_bMacroMode(false),
	m_bMnlMode(false),
	m_bMfAutoAssistMode(false),
	m_pFocusInvalidvalue(false),
	m_FocusDispMode(APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_OFF)
{
	setClassType(CtClassType_LayoutMain);
	memset(m_pFocusValue, 0, sizeof(m_pFocusValue));
}

CtLayout* CtFastDrawContainerFocus::createContainer()
{
	CtRecViewFontSet fSet = CtRecViewFontSet();

	CtFontSet fSetAct = CtRecViewFontSet(FontTypeBold_alignCenter, CtColor::Black);
	fSetAct.edgeColor = CtColor::NoColor;

	unsigned short inf[] = { 0x221e,0x0000 };

	m_pMugenMacro = new CtStackLabel();
	{
		m_pNumberLayout = new CtHLayout();
		{
			m_pNumberLayout->addStretch(4);
			m_pNumMacro = new CtLabel(IC_OSD_MACRO);
			m_pNumberLayout->addWidget(m_pNumMacro, 2);
			m_pNumberLayout->addStretch(4);
		}
		m_pMugenMacro->addLabel(m_pNumberLayout, APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_NUMBER);

		m_pFeetLayout = new CtHLayout();
		{
			m_pFeetMacro = new CtLabel(IC_OSD_MACRO);
			m_pFeetLayout->addWidget(m_pFeetMacro, AlignRight, 2);
			m_pFeetLayout->addStretch(4);
			m_pFeetMugen = new CtLabel(inf, fSet);
			m_pFeetLayout->addWidget(m_pFeetMugen, AlignLeft, 2);
			m_pFeetLayout->addStretch(2);
		}
		m_pMugenMacro->addLabel(m_pFeetLayout, APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_MM_FEET);

		m_pMmLayout = new CtHLayout();
		{
			m_pMmLayout->addStretch(1);
			m_pMmMacro = new CtLabel(IC_OSD_MACRO);
			m_pMmLayout->addWidget(m_pMmMacro, AlignRight, 2);
			m_pMmLayout->addStretch(4);
			m_pMmMugen = new CtLabel(inf, fSet);
			m_pMmLayout->addWidget(m_pMmMugen, AlignLeft, 2);
			m_pMmLayout->addStretch(1);
		}
		m_pMugenMacro->addLabel(m_pMmLayout, APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_MM_M);
	}
	m_pAll = new CtLayout();
	m_pAll->addWidget(m_pMugenMacro);

	CtHLayout* pL = new CtHLayout();
	for (int i = 0; i < FOCUS_WORD_COUNT; i++) {
		m_pFocusValue[i] = new CtStackLabel();
		m_pFocusValue[i]->setFastDraw(true);

		m_pFocusValue[i]->addLabel("0", fSet, F_0);
		m_pFocusValue[i]->addLabel("1", fSet, F_1);
		m_pFocusValue[i]->addLabel("2", fSet, F_2);
		m_pFocusValue[i]->addLabel("3", fSet, F_3);
		m_pFocusValue[i]->addLabel("4", fSet, F_4);
		m_pFocusValue[i]->addLabel("5", fSet, F_5);
		m_pFocusValue[i]->addLabel("6", fSet, F_6);
		m_pFocusValue[i]->addLabel("7", fSet, F_7);
		m_pFocusValue[i]->addLabel("8", fSet, F_8);
		m_pFocusValue[i]->addLabel("9", fSet, F_9);
		//m_pFocusValue[i]->addLabel(inf, fSet, F_Inf);
		m_pFocusValue[i]->addLabel("F", fSet, F_F);

		CtLayout* pF_Macro = new CtLayout(CtColor::White);
		pF_Macro->addWidget(new CtLabel("F", fSetAct));
		m_pFocusValue[i]->addLabel(pF_Macro, F_F_Macro);

		m_pFocusValue[i]->addLabel("A", fSet, F_A);

		CtLayout* pA_Macro = new CtLayout(CtColor::White);
		pA_Macro->addWidget(new CtLabel("A", fSetAct));
		m_pFocusValue[i]->addLabel(pA_Macro, F_A_Macro);

		m_pFocusValue[i]->addLabel("M", fSet, F_M);

		CtLayout* pM_Macro = new CtLayout(CtColor::White);
		pM_Macro->addWidget(new CtLabel("M", fSetAct));
		m_pFocusValue[i]->addLabel(pM_Macro, F_M_Macro);

		m_pFocusValue[i]->addLabel("m", fSet, F_m);
		m_pFocusValue[i]->addLabel("f", fSet, F_f);
		m_pFocusValue[i]->addLabel("t", fSet, F_t);
		m_pFocusValue[i]->addLabel(".", fSet, F_Dot);
		m_pFocusValue[i]->addLabel(" ", fSet, F_Space);
		//m_pFocusValue[i]->addLabel(IC_OSD_MACRO, F_MacroIcon);


		pL->addWidget(m_pFocusValue[i], 1);

		m_pFocusValue[i]->index(F_Space);
	}
	m_pAll->addWidget(pL);
	return m_pAll;
}

bool CtFastDrawContainerFocus::destroyContainer()
{
	return true;
}

bool CtFastDrawContainerFocus::startupContainer() {
	updateFocusDispMode();
	updateMacroMode();
	updateMnlMode();
	updateMfAutoAstMode();
	return true;
}

CtFastDrawContainerFocus::~CtFastDrawContainerFocus()
{
}

bool CtFastDrawContainerFocus::updateFastDraw()
{
	int PaddingNum = FOCUS_WORD_COUNT - 1;

	// 表示初期化
	for (int i = PaddingNum; 0 <= i; i--) {
		m_pFocusValue[i]->setVisible(true);
	}

	unsigned int focusValue = 0; // ***(.)***
	int valLength = 0;// 桁数 6: ***/ 5:**.* / 4:*.**
	bool bFocusInfi = false;

	if (m_FocusDispMode == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_OFF) {
		//m_pAll->setVisible(false);
		return true;
	}
	else {
		//m_pAll->setVisible(true);
	}

	if (m_FocusDispMode == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_NUMBER) {
#ifdef WIN32_GUI_SIM
		m_value += m_add;
		if (m_value > 10000) {
			focusValue = 0xFF;
		}
		else {
			focusValue = m_value;
		}
		if (m_value > 30000) {
			m_value = 0;
		}
		
		/*focusValue = m_value;*/
		if (focusValue == 0xFF) {
			m_pFocusInvalidvalue = true;
		}
		else {
			m_pFocusInvalidvalue = false;
		}
#else
		focusValue = APL_PARAM_GET_DATA(AplParamFocusOSD_Num);// 取得値 *** 6桁(整数部:3桁+小数部:3桁)
		if (focusValue == 0xFF) {
			m_pFocusInvalidvalue = true;
		}
		else {
			m_pFocusInvalidvalue = false;
		}
#endif
		buildStringNumType(focusValue, PaddingNum);
	}
	else if (m_FocusDispMode == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_MM_M) {
#ifdef WIN32_GUI_SIM
		m_value += m_add;
		if (m_value > 70000) m_value = 1;
		focusValue = m_value;
		if (focusValue == 0xFFFE) {
			m_pFocusInvalidvalue = true;
		}
		else {
			m_pFocusInvalidvalue = false;
		}
#else
		focusValue = APL_PARAM_GET_DATA(AplParamFocusOSD_MM); // 取得値 ***(.)*** 6桁(整数部:3桁+小数部:3桁)
		if (focusValue == 0xFFFE) {
			m_pFocusInvalidvalue = true;
		}
		else {
			m_pFocusInvalidvalue = false;
		}
#endif
		valLength = digit_length(focusValue);


		if (focusValue >= 0xFFFF) {
			bFocusInfi = true;
			focusValue = 0xFFFF;
			buildStringMmType(focusValue, valLength, bFocusInfi, PaddingNum);
		}
		else {
			double roundVal = 0;
			switch (valLength)
			{
				// 正規化
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:// *.*** → *.**(*)
				   // **** → ***.*にして四捨五入
				if (focusValue % 10 < 5) {
					focusValue = focusValue / 10;
				}
				else {
					focusValue = focusValue / 10 + 1;
				}
				break;
			case 5:// **.*** → **.*(**)
				if (focusValue % 100 < 50) {
					focusValue = focusValue / 100;
				}
				else {
					focusValue = focusValue / 100 + 1;
				}
				break;
			default:
				break;
			}
			buildStringMmType(focusValue, valLength, bFocusInfi, PaddingNum);
		}
	}
	else if (m_FocusDispMode == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_MM_FEET) {
		/*
		フォーカス値の表示設定がフィート単位の場合。
		****は数字、小数点、∞。1桁なら*.**、2桁なら**.*の形式で表示する。
		3桁なら***の形式で右詰め表示する。∞なら右詰めで表示する。
		*/
#ifdef WIN32_GUI_SIM
		m_value += m_add;
		if (m_value > 70000) m_value = 1;
		focusValue = m_value;
		if (focusValue == 0xFFFE) {
			m_pFocusInvalidvalue = true;
		}
		else {
			m_pFocusInvalidvalue = false;
		}
#else
		focusValue = APL_PARAM_GET_DATA(AplParamFocusOSD_MM); // 取得値 ***(.)*** 6桁(整数部:3桁+小数部:3桁)
		if (focusValue == 0xFFFE) {
			m_pFocusInvalidvalue = true;
		}
		else {
			m_pFocusInvalidvalue = false;
		}
#endif
		unsigned int focusFeetValue = focusValue * 1000 / 305;
		valLength = digit_length(focusFeetValue);

		if (focusValue >= 0xFFFF) {
			bFocusInfi = true;
			focusValue = 0xFFFF;
			buildStringFeetType(focusValue, valLength, bFocusInfi, PaddingNum);
		}
		else {
			focusValue = focusFeetValue;
			double roundVal = 0;
			switch (valLength)
			{
				// 正規化
			case 0:
			case 1:
			case 2:
			case 3:
			case 4: // *.*** → *.**(*)
				// **** → ***.*にして四捨五入
				if (focusValue % 10 < 5) {
					focusValue = focusValue / 10;
				}
				else {
					focusValue = focusValue / 10 + 1;
				}
				break;
			case 5: // **.*** → **.*(**)
				if (focusValue % 100 < 50) {
					focusValue = focusValue / 100;
				}
				else {
					focusValue = focusValue / 100 + 1;
				}
				break;
			case 6: // ***.*** → ***(***)
				if (focusValue % 1000 < 500) {
					focusValue = focusValue / 1000;
				}
				else {
					focusValue = focusValue / 1000 + 1;
				}
				break;
			default:
				break;
			}
			buildStringFeetType(focusValue, valLength, bFocusInfi, PaddingNum);
		}
	}


	if (m_bMnlMode/* MF */) {
		if (m_bMfAutoAssistMode) {
			if (APL_PARAM_GET_DATA(AplParamReverseFocusDisplay)/* マクロ動作中 */) {
				m_pFocusValue[PaddingNum--]->index(F_A_Macro);
				m_pFocusValue[PaddingNum--]->index(F_M_Macro);
			}
			else {
				m_pFocusValue[PaddingNum--]->index(F_A);
				m_pFocusValue[PaddingNum--]->index(F_M);
			}
		}
		else if (APL_PARAM_GET_DATA(AplParamReverseFocusDisplay)/* マクロ動作中 */) {
			m_pFocusValue[PaddingNum--]->index(F_F_Macro);
			m_pFocusValue[PaddingNum--]->index(F_M_Macro);
		}
		else {
			m_pFocusValue[PaddingNum--]->index(F_F);
			m_pFocusValue[PaddingNum--]->index(F_M);
		}
	}
	else {
		if (APL_PARAM_GET_DATA(AplParamReverseFocusDisplay)/* マクロ動作中 */) {
			m_pFocusValue[PaddingNum--]->index(F_F_Macro);
			m_pFocusValue[PaddingNum--]->index(F_A_Macro);
		}
		else {
			m_pFocusValue[PaddingNum--]->index(F_F);
			m_pFocusValue[PaddingNum--]->index(F_A);
		}
	}

	// 不要部分パディング
	for (int i = PaddingNum; 0 <= i; i--) {
		m_pFocusValue[i]->setVisible(false);
	}
	if (m_pFocusInvalidvalue == true) {
		for (int i = FOCUS_WORD_COUNT - 1; 0 <= i; i--) {
			m_pFocusValue[i]->setVisible(false);
		}
		m_pMugenMacro->setVisible(false);
	}
	else {
		m_pMugenMacro->setVisible(true);
	}
	return true;
}

bool CtFastDrawContainerFocus::buildStringNumType(unsigned int FocusVal, int& PaddingNum) {
	// △**□□**
	m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
	FocusVal /= 10;
	m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
	return true;
}

bool CtFastDrawContainerFocus::buildStringMmType(unsigned int FocusVal, int valLen, bool bFocusInfi, int& PaddingNum) {
	if (bFocusInfi == true) {
		// △**□□□∞m

		m_pFocusValue[PaddingNum--]->index(F_m);
		
		m_pFocusValue[PaddingNum--]->setVisible(false);
		m_pFocusValue[PaddingNum--]->setVisible(false);
		m_pFocusValue[PaddingNum--]->setVisible(false);
		m_pFocusValue[PaddingNum--]->setVisible(false);
		m_pMmMugen->setVisible(true);
	}
	else {
		m_pMmMugen->setVisible(false);
		// △***.**m
		// △****.*m
		m_pFocusValue[PaddingNum--]->index(F_m);
		switch (valLen) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:// *.**
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(F_Dot);
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			break;
		case 5:// **.*
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(F_Dot);
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			break;
		default:
			break;
		}
	}
	return true;
}

bool CtFastDrawContainerFocus::buildStringFeetType(unsigned int FocusVal, int valLen, bool bFocusInfi, int& PaddingNum) {
	if (bFocusInfi == true) {
		// △**□□□∞ft
		m_pFocusValue[PaddingNum--]->index(F_t);
		m_pFocusValue[PaddingNum--]->index(F_f);
		
		m_pFocusValue[PaddingNum--]->setVisible(false);
		m_pFocusValue[PaddingNum--]->setVisible(false);
		m_pFocusValue[PaddingNum--]->setVisible(false);
		m_pFocusValue[PaddingNum--]->setVisible(false);
		
		// Mugen文字表示
		m_pFeetMugen->setVisible(true);
	}
	else {
		m_pFeetMugen->setVisible(false);
		// △***.**ft
		// △****.*ft
		// △** ***ft
		m_pFocusValue[PaddingNum--]->index(F_t);
		m_pFocusValue[PaddingNum--]->index(F_f);
		switch (valLen) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:// *.**
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(F_Dot);
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			break;
		case 5:// **.*
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(F_Dot);
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			break;
		case 6:// □***
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			FocusVal /= 10;
			m_pFocusValue[PaddingNum--]->index(FocusVal % 10);
			m_pFocusValue[PaddingNum--]->index(F_Space);
			break;
		default:
			break;
		}
	}
	return true;
}

bool CtFastDrawContainerFocus::handleParamEvent(const CtEventParam& Param) {
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();
	switch (t_Id) {
	case AplParamFocusMacro:
		return updateMacroMode(int_Data);
		break;
	case AplParamFocusMode:
		return updateMnlMode(int_Data);
		break;
	case AplParamForceAF:
		return updateMnlMode();
		break;
	case AplParamMfAutoAssist:
		return updateMfAutoAstMode(int_Data);
		break;
	case AplParamIndicatorZoomFocus:
		return updateFocusDispMode(int_Data);
		break;
	case AplParamDispModeCheck:
		return updateFocusDispMode();
		break;
	default:
		break;
	}
	return false;
}

bool CtFastDrawContainerFocus::updateMacroMode(int int_Data) {
	if (int_Data == -1) int_Data = APL_PARAM_GET_DATA(AplParamFocusMacro);
	if (int_Data == APL_SYS_PARAM_SWITCH_ON) m_bMacroMode = true;
	else m_bMacroMode = false;

	if (m_bMacroMode/* マクロ 入切 */) {
		m_pNumMacro->setVisible(true);
		m_pFeetMacro->setVisible(true);
		m_pMmMacro->setVisible(true);
	}
	else {
		m_pNumMacro->setVisible(false);
		m_pMmMacro->setVisible(false);
		m_pFeetMacro->setVisible(false);
	}
	return true;
}

bool CtFastDrawContainerFocus::updateMnlMode(int int_Data) {
	if (APL_PARAM_GET_DATA(AplParamForceAF) == APL_SYS_PARAM_SWITCH_ON) {
		// 優先的に判定する
		m_bMnlMode = false;
		return true;
	}

	if (int_Data == -1) int_Data = APL_PARAM_GET_DATA(AplParamFocusMode);
	if (APL_SYS_PARAM_FOCUS_MANUAL == int_Data) m_bMnlMode = true;
	else m_bMnlMode = false;
	return true;
}

bool CtFastDrawContainerFocus::updateMfAutoAstMode(int int_Data) {
	if (int_Data == -1) int_Data = APL_PARAM_GET_DATA(AplParamMfAutoAssist);
	if (int_Data == APL_SYS_PARAM_SWITCH_ON) m_bMfAutoAssistMode = true;
	else m_bMfAutoAssistMode = false;
	return true;
}

bool CtFastDrawContainerFocus::updateFocusDispMode(int int_Data) {
	if (int_Data == -1) {
		int_Data = APL_PARAM_GET_DATA(AplParamIndicatorZoomFocus);
	}
	m_FocusDispMode = (APL_SYS_PARAM_INDICATOR_ZOOMFOCUS)int_Data;

	if (m_bStatusMode == true && m_FocusDispMode == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_OFF) {
		m_FocusDispMode = APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_NUMBER;
	}

	if (m_FocusDispMode == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_OFF) {
		m_pAll->setVisible(false);
		//return true;

		//m_pMugenMacro->setVisible(false);
	}
	else {
		m_pAll->setVisible(true);
		m_pMugenMacro->setVisible(true);
		m_pMugenMacro->index(m_FocusDispMode);
	}
	return true;
}

bool CtFastDrawContainerFocus::setStatusMode(bool bStatusMode) {
	m_bStatusMode = bStatusMode;
	return updateFocusDispMode();
}
