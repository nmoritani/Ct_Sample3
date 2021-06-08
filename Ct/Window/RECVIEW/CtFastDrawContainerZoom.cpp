/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtFastDrawContainerZoom
 */
#include "CtFastDrawContainerZoom.h"

#ifdef WIN32_GUI_SIM
static int m_value = 880;
static int m_add = 9;
#endif

CtFastDrawContainerZoom::CtFastDrawContainerZoom()
{
	setClassType(CtClassType_LayoutMain);
	memset(m_pLabel, 0, sizeof(m_pLabel));

	m_Type = ZoomDispType_Nodisp;
	m_bStatusMode = false;
	m_bFastZoomAct = false;
	m_bIaMode = false;
}


CtLayout* CtFastDrawContainerZoom::createContainer()
{
	CtRecViewFontSet fSet = CtRecViewFontSet();
	CtFontSet fSetAct = CtRecViewFontSet(FontTypeNormal_alignCenter, CtColor::Black);
	fSetAct.edgeColor = CtColor::NoColor;

	m_pAll = new CtHLayout();
	{
		CtHLayout* pZoomVal = new CtHLayout();

		for (int i = 0; i < ZoomDigit; i++) {
			m_pLabel[i] = new CtStackLabel();
			m_pLabel[i]->setFastDraw(true);

			m_pLabel[i]->addLabel("0", fSet, ZoomPartsNumber_0);
			m_pLabel[i]->addLabel("1", fSet, ZoomPartsNumber_1);
			m_pLabel[i]->addLabel("2", fSet, ZoomPartsNumber_2);
			m_pLabel[i]->addLabel("3", fSet, ZoomPartsNumber_3);
			m_pLabel[i]->addLabel("4", fSet, ZoomPartsNumber_4);
			m_pLabel[i]->addLabel("5", fSet, ZoomPartsNumber_5);
			m_pLabel[i]->addLabel("6", fSet, ZoomPartsNumber_6);
			m_pLabel[i]->addLabel("7", fSet, ZoomPartsNumber_7);
			m_pLabel[i]->addLabel("8", fSet, ZoomPartsNumber_8);
			m_pLabel[i]->addLabel("9", fSet, ZoomPartsNumber_9);
			m_pLabel[i]->addLabel("i", fSet, ZoomPartsNumber_i);

			CtLayout* pIaAct = new CtLayout(CtColor::White);
			pIaAct->addWidget(new CtLabel("i", fSetAct));
			m_pLabel[i]->addLabel(pIaAct, ZoomPartsNumber_IaAct);

			m_pLabel[i]->addLabel("Z", fSet, ZoomPartsNumber_Z);

			CtLayout* pFastAct = new CtLayout(CtColor::White);
			pFastAct->addWidget(new CtLabel("Z", fSetAct));
			m_pLabel[i]->addLabel(pFastAct, ZoomPartsNumber_FastAct);

			m_pLabel[i]->addLabel("m", fSet, ZoomPartsNumber_m);
			m_pLabel[i]->addLabel(".", fSet, ZoomPartsNumber_dot);
			m_pLabel[i]->addLabel(" ", fSet, ZoomPartsNumber_Space);

			pZoomVal->addWidget(m_pLabel[i], AlignCenter);
			// ちら見え防止
			m_pLabel[i]->index(ZoomPartsNumber_Space);
		}
		m_pAll->addWidget(pZoomVal, 6);
	}
	return m_pAll;
}

bool CtFastDrawContainerZoom::destroyContainer()
{
	return true;
}

CtFastDrawContainerZoom::~CtFastDrawContainerZoom()
{
}

bool CtFastDrawContainerZoom::startupContainer() {
	setDispMode();
	setIaActState();
	setFastActState(APL_PARAM_GET_DATA(AplParamEnableFastZoom) == APL_SYS_PARAM_SWITCH_ON);
	return true;
}

bool CtFastDrawContainerZoom::updateFastDraw()
{
	int value = 0;

#ifdef WIN32_GUI_SIM
	value = m_value;
	m_value = m_value + m_add;
	if (value < 10) {
		value = 0;
	}
	if (m_Type == ZoomDispType_Mm) {
		if (value % 10 >= 5) {
			// 小数点第2位の四捨五入
			value += 10;
		}
		if (value > 17600) {
			m_value = 880;
		}

	}
	else if (m_Type == ZoomDispType_Pos) {
		if (value > 999) {
			m_value = 0;
		}
	}

#else
	if (m_Type == ZoomDispType_Mm) {
		// Mm/Feet
		value = APL_PARAM_GET_DATA(AplParamZoomMm);// 88 ~ 1760
		if (value == 0xFFFF) {
			m_ZoomInvalidValue = true;
		}
		else {
			m_ZoomInvalidValue = false;
		}
		value *= 10;// UX180での仕様に合わせるため、880 ~ 17600に変更
		if (value % 10 >= 5) {
			// 小数点第2位の四捨五入
			value += 10;
		}
	}
	else if (m_Type == ZoomDispType_Pos) {
		// NUMBER
		value = APL_PARAM_GET_DATA(AplParamZoomVal);
		if (value == 0xFFFF) {
			m_ZoomInvalidValue = true;
		}
		else {
			m_ZoomInvalidValue = false;
		}
		if (value > 999) {
			value = 999;
		}
	}
	else {
		value = 0;
	}

#endif
	int rank_10000, rank_1000, rank_100, rank_10, rank_1;

	/* 10000の位 */
	rank_10000 = value / 10000;

	/* 1000の位 */
	rank_1000 = (value % 10000) / 1000;

	/* 100の位 */
	rank_100 = (value % 1000) / 100;

	/* 10の位 */
	rank_10 = (value % 100) / 10;

	/* 1の位 */
	rank_1 = value % 10;

	/* Open表示 */
	if (m_Type == ZoomDispType_Nodisp) {
		for (int i = 0; i < ZoomDigit; i++) {
			m_pLabel[i]->index(ZoomPartsNumber_Space);
		}
	}
	else if (m_Type == ZoomDispType_Mm) {
		int i = ZoomDigit - 1;
		// mm表示 iZ**.*mm
		// 末から設定
		m_pLabel[i--]->index(ZoomPartsNumber_m);
		m_pLabel[i--]->index(ZoomPartsNumber_m);
		if (rank_10000 == 0) {
			// iz**.*mm
			m_pLabel[i--]->index(rank_10);
			m_pLabel[i--]->index(ZoomPartsNumber_dot);
			m_pLabel[i--]->index(rank_100);
			if (rank_1000 != 0) {
				m_pLabel[i--]->index(rank_1000);
			}
			else {
				m_pLabel[i--]->index(ZoomPartsNumber_Space);
			}
		}
		else {
			// iz ***mm
			m_pLabel[i--]->index(rank_100);
			m_pLabel[i--]->index(rank_1000);
			m_pLabel[i--]->index(rank_10000);
			m_pLabel[i--]->index(ZoomPartsNumber_Space);
		}

		if (m_bFastZoomAct) {
			m_pLabel[i--]->index(ZoomPartsNumber_FastAct);
		}
		else {
			m_pLabel[i--]->index(ZoomPartsNumber_Z);
		}
		if (m_bIaMode) {
			if (APL_PARAM_GET_DATA(AplParamIaZoomActFlag)) {
				m_pLabel[i--]->index(ZoomPartsNumber_IaAct);
			}
			else {
				m_pLabel[i--]->index(ZoomPartsNumber_i);
			}
		}
		else {
			m_pLabel[i--]->index(ZoomPartsNumber_Space);
		}
		for (int padding = i; 0 < padding; padding--) {
			m_pLabel[padding]->index(ZoomPartsNumber_Space);
		}
	}
	else {

		// Number表示
		int i = ZoomDigit - 1;

		// iZ***
		// 末から設定
		m_pLabel[i--]->index(rank_1);
		m_pLabel[i--]->index(rank_10);
		m_pLabel[i--]->index(rank_100);

		if (m_bFastZoomAct) {
			m_pLabel[i--]->index(ZoomPartsNumber_FastAct);
		}
		else {
			m_pLabel[i--]->index(ZoomPartsNumber_Z);
		}

		if (m_bIaMode) {
			if (APL_PARAM_GET_DATA(AplParamIaZoomActFlag)) {
				m_pLabel[i--]->index(ZoomPartsNumber_IaAct);
			}
			else {
				m_pLabel[i--]->index(ZoomPartsNumber_i);
			}
		}
		else {
			m_pLabel[i--]->index(ZoomPartsNumber_Space);
		}
		for (int padding = i; 0 <= padding; padding--) {
			m_pLabel[padding]->index(ZoomPartsNumber_Space);
		}

	}
	if (m_ZoomInvalidValue == true) {
		for (int padding = ZoomDigit - 1; 0 <= padding; padding--) {
			m_pLabel[padding]->index(ZoomPartsNumber_Space);
		}
	}
	return true;
}

bool CtFastDrawContainerZoom::setDispMode()
{
	int nZoomFocusDisp = APL_PARAM_GET_DATA(AplParamIndicatorZoomFocus);

	if (APL_PARAM_GET_DATA(AplParamZoomLensValid) == APL_SYS_PARAM_SWITCH_OFF) {
		return m_pAll->setVisible(false);
	}
	if (nZoomFocusDisp == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_OFF)
	{
		if (m_bStatusMode == true) {
			m_pAll->setVisible(true);
			m_Type = ZoomDispType_Pos;
		}
		else {
			m_pAll->setVisible(false);
			m_Type = ZoomDispType_Nodisp;
		}
	}
	else if (nZoomFocusDisp == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_MM_FEET
		|| nZoomFocusDisp == APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_MM_M) {
		m_pAll->setVisible(true);
		m_Type = ZoomDispType_Mm;
	}
	else {
		m_pAll->setVisible(true);
		m_Type = ZoomDispType_Pos;
	}

	return true;
}

bool CtFastDrawContainerZoom::handleParamEvent(const CtEventParam& Param) {
	int int_Data = Param.getParamVal();
	switch (Param.getParamId()) {
	case AplParamIAZoom: // iAzoom動作中判定「i」表示
		return setIaActState();
		break;
	case AplParamEnableFastZoom:
		// FastZoom 動作中判定
		return setFastActState(int_Data == APL_SYS_PARAM_SWITCH_ON);
		break;
	case AplParamZoomLensValid:
	case AplParamIndicatorZoomFocus:
	case AplParamDispModeCheck:
		return setDispMode();
		break;
	default:
		break;
	}
	return false;
}

bool CtFastDrawContainerZoom::setIaActState() {
	m_bIaMode = APL_PARAM_GET_DATA(AplParamIAZoom) == APL_SYS_PARAM_SWITCH_ON;

	return true;
}

bool CtFastDrawContainerZoom::setFastActState(bool bAct) {
	m_bFastZoomAct = bAct;
	return false;
}

bool CtFastDrawContainerZoom::setStatusMode(bool bStatusMode) {
	m_bStatusMode = bStatusMode;
	return setDispMode();
}
