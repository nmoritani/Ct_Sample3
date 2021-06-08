/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtFastDrawContainerSpotMeterVal
 */
#include "CtFastDrawContainerSpotMeterVal.h"
#include <stdlib.h>

#ifdef WIN32_GUI_SIM
	static int m_value = 0;
#endif

const char TotalChar[] = "0123456789%.-+ ";
CtFastDrawContainerSpotMeterVal::CtFastDrawContainerSpotMeterVal()
{
	setClassType(CtClassType_LayoutMain);
	//memset(m_pLabel, 0, sizeof(m_pLabel));
}

CtLayout* CtFastDrawContainerSpotMeterVal::createContainer()
{
	CtRecViewFontSet fSet = CtRecViewFontSet();
	// 全体レイアウト
	m_pAll = new CtHLayout();
	// メータ部
	/*
	for (int i = 0; i < DigitNum; i++) {
		m_pLabel[i] = new CtStackLabel();
		m_pLabel[i]->addLabels(TotalChar, fSet);
		m_pLabel[i]->setFastDraw(true);
		m_pLabel[i]->index(getCharIndex(' '));
		m_pAll->addWidget(m_pLabel[i], 1);
	}
	*/
	m_pSpotMeterVal = new CtLabel("", fSet);
	m_pAll->addWidget(m_pSpotMeterVal);
	m_pAll->setVisible(false);
	return m_pAll;
}

bool CtFastDrawContainerSpotMeterVal::destroyContainer()
{
	return true;
}

CtFastDrawContainerSpotMeterVal::~CtFastDrawContainerSpotMeterVal()
{
}

bool CtFastDrawContainerSpotMeterVal::startupContainer()
{
	updateDisp();
	return true;
}

bool CtFastDrawContainerSpotMeterVal::draw() {
	char Str[DigitNum + 1];
	memset(Str, 0, sizeof(Str));
#ifdef WIN32_GUI_SIM
	m_value++;
	if (m_value > 109) m_value = 0;
	sprintf(Str, "%3d%%", m_value);
#else
	sprintf(Str, "%3d%%", APL_PARAM_GET_DATA(AplParamSpotMeterPerVal));
#endif
	return m_pSpotMeterVal->setText(Str);
}

bool CtFastDrawContainerSpotMeterVal::updateFastDraw()
{
	char Str[DigitNum + 1];
	memset(Str, 0, sizeof(Str));

	if (m_bDisp){
#ifdef WIN32_GUI_SIM
		m_value++;
		if (m_value > 109) m_value = 0;
		sprintf(Str, "%3d%%", m_value);
#else
		sprintf(Str, "%3d%%", APL_PARAM_GET_DATA(AplParamSpotMeterPerVal));
#endif
	}

#if 0
	for (int i = 0; i < DigitNum; i++) {
		m_pLabel[i]->index(getCharIndex(Str[i]));
	}
#endif
	return true;
}

int CtFastDrawContainerSpotMeterVal::getCharIndex(char c)
{
	const char* p = TotalChar;

	while (*p) {
		if (*p == c) return p - TotalChar;
		p++;
	}

	return 0;
}


bool CtFastDrawContainerSpotMeterVal::handleParamEvent(const CtEventParam& Param) {
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamColorBar:
	case AplParamSpotMeterUserSw:
	case AplParamLcdFocusExpandUserSw:
	case AplParamAreaFunction:
	case AplParamAreaMode:
		updateDisp();
		return true;
	default:
		break;
	}
	return false;
}

bool CtFastDrawContainerSpotMeterVal::handleTimerEvent(const CtEventTimer& Timer) {
	if (Timer.getTimeUid() == CT_TIMER_ID_SPOTMETER) {
		return draw();
	}
	return false;
}

bool CtFastDrawContainerSpotMeterVal::updateDisp() {
	bool bDisp = false;

	// 表示条件
	if (APL_PARAM_GET_DATA(AplParamAreaMode) == APL_SYS_PARAM_SWITCH_ON) {
		if (APL_PARAM_GET_DATA(AplParamAreaFunction) == APL_SYS_PARAM_AREA_FUNCTION_Y_GET
		 || APL_PARAM_GET_DATA(AplParamAreaFunction) == APL_SYS_PARAM_AREA_FUNCTION_FOCUS_YGET)
		{
			bDisp = true;
		}
	}
	// 表示条件
	if (APL_PARAM_GET_DATA(AplParamSpotMeterUserSw) == APL_SYS_PARAM_SWITCH_ON) {
		bDisp = true;
	}

	// 排他条件
	if (APL_PARAM_GET_DATA(AplParamColorBar) == APL_SYS_PARAM_SWITCH_ON) {
		bDisp = false;
	}
	// 排他条件
	if (APL_PARAM_GET_DATA(AplParamLcdFocusExpandUserSw) == APL_SYS_PARAM_SWITCH_ON) {
		bDisp = false;
	}

	// 優先度高
	if (m_bStatusMode == true) {
		bDisp = true;
	}

	m_bDisp = bDisp;
	if (m_bDisp == true) {
		CtTimer::getInstance()->startCyclic(CT_TIMER_ID_SPOTMETER, 250, this);
	}
	else {
		CtTimer::getInstance()->stopCyclic(CT_TIMER_ID_SPOTMETER, this);
	}
	return m_pAll->setVisible(m_bDisp);
}

bool CtFastDrawContainerSpotMeterVal::setStatusMode(bool bStatusMode) {
	m_bStatusMode = bStatusMode;
	if (m_bStatusMode == true) {
		//m_bDisp = true;
		//m_pAll->setVisible(true);
		return updateDisp();
	}
	else {
		updateDisp();
	}
	return true;
}
