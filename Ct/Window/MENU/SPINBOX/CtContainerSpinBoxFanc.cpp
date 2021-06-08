/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerSpinBoxFanc.h"
//#include <stdlib.h>

CtContainerSpinBoxFanc::CtContainerSpinBoxFanc(CtWindowID id) : CtContainerSpinBox(id)
{
	setClassType(CtClassType_LayoutMain);
}
CtContainerSpinBoxFanc::~CtContainerSpinBoxFanc()
{
	destroyContainer();
}

//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------

CtLayout* CtContainerSpinBoxFanc::createLabel()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	/* Layout */
	CtLayout *pLayout = createLabelLayout();

	CtParamLabel* pLabel = NULL;

	switch (m_WindowID) {
	case WindowID_Menu_SYNCHRO_SCAN:
	{
		if (APL_PARAM_GET_DATA(AplParamSceneSyncScanType) == APL_SYS_PARAM_SYNC_SCAN_TYPE_SEC) {
			pLabel = new CtParamLabel(AplParamSceneSyncScanSecValue, fSet);
			pLabel->setLabelType(CtParamLabel::TypeNumeric);
			pLabel->setCorrection(0, 0.1F);
			pLabel->setForm("1/%.1f");
//			pLabel->setFontSet(fSet);
		}
		else {
			pLabel = new CtParamLabel(AplParamSceneSyncScanDegValue, fSet);
			pLabel->setLabelType(CtParamLabel::TypeNumeric);
			pLabel->setForm("%0.1fd");
			pLabel->setCorrection(0, 0.1F);
//			pLabel->setFontSet(fSet);
		}
		break;
	}
	default:
		pLabel = new CtParamLabel(m_Info->ParamId, fSet);
		pLabel->setLabelType(CtParamLabel::TypeNumeric);
		pLabel->setRange(m_Info->disp.min, m_Info->disp.max);
		pLabel->setForm(m_Info->disp.str);
		pLabel->setCorrection(0, m_Info->disp.coef);
//		pLabel->setFontSet(fSet);
		break;
	}

	pLayout->addWidget(pLabel, CtMargin(5, 5), AlignCenter);

	return pLayout;
}

//----------------------------------------------------------------------------------------------------
// HandleEvent
//----------------------------------------------------------------------------------------------------
bool CtContainerSpinBoxFanc::handleParamEvent(const CtEventParam& Param)
{
	bool bRet = false;
	int t_Id = Param.getParamId();

	switch (t_Id) {
	case AplParamUpButtonInvalid:
	case AplParamDownButtonInvalid:
	{
		checkInvalid();
		bRet = true;
		break;
	}
	default:
		break;
	}
	return bRet;

}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
bool CtContainerSpinBoxFanc::executionUp()
{
	CtWindowContentsPressLevel* pContents = new CtWindowContentsPressLevel(m_WindowID, m_Laval);
	CtEventInterface::requestFuncCmd(getScreenSel(), m_WindowID, FuncID_UP, pContents);
	delete pContents;
	return true;
}

bool CtContainerSpinBoxFanc::executionDown()
{
	CtWindowContentsPressLevel* pContents = new CtWindowContentsPressLevel(m_WindowID, m_Laval);
	CtEventInterface::requestFuncCmd(getScreenSel(), m_WindowID, FuncID_DOWN, pContents);
	delete pContents;
	return true;
}

bool CtContainerSpinBoxFanc::executionRet(bool bDestructor)
{
	if (m_bPressBtn == false) {
		CtEventInterface::requestFuncCmd(getScreenSel(), m_WindowID, FuncID_RET, NULL);
		if (bDestructor == false) {
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
		}
	}
	m_bPressBtn = true;
	return true;
}
bool CtContainerSpinBoxFanc::executionSet()
{
	CtEventInterface::requestFuncCmd(getScreenSel(), m_WindowID, FuncID_SET, NULL);
	CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
	m_bPressBtn = true;
	return true;
}
void CtContainerSpinBoxFanc::checkInvalid()
{
	bool pUp = APL_PARAM_GET_DATA(AplParamUpButtonInvalid) == APL_SYS_PARAM_SWITCH_ON ? true : false;
	bool pDown = APL_PARAM_GET_DATA(AplParamDownButtonInvalid) == APL_SYS_PARAM_SWITCH_ON ? true : false;

	m_pCtrl->setInvalid(WidgetID_UP, pUp);
	m_pCtrl->setInvalid(WidgetID_DOWN, pDown);
}
