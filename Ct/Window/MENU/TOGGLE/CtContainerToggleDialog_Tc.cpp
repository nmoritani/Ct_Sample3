/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerToggleDialog_Tc.h"
//#include <stdlib.h>

CtContainerToggleDialog_Tc::CtContainerToggleDialog_Tc(CtWindowID id) : CtContainerToggleDialog(id)
{
	setClassType(CtClassType_LayoutMain);
}
CtContainerToggleDialog_Tc::~CtContainerToggleDialog_Tc()
{
	destroyContainer();
}


//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------
CtLayout* CtContainerToggleDialog_Tc::createTitle()
{
	/* Title */
	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(m_WindowID);

	CtLayout *pLayout = new CtLayout();
	pLayout->addContainer(pTitle);

	return pLayout;
}

CtLayout* CtContainerToggleDialog_Tc::createToggle()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	m_Toggle.push_back(createTch());
	m_Toggle.push_back(createTcm());
	m_Toggle.push_back(createTcs());
	m_Toggle.push_back(createTcf());

	/* TC‰Šú‰» */
	unsigned int TC = APL_PARAM_GET_DATA(AplParamDispTc);
	m_Toggle[0].Data = (char)((TC & 0xFF000000) >> 24);
	m_Toggle[1].Data = (char)((TC & 0x00FF0000) >> 16);
	m_Toggle[2].Data = (char)((TC & 0x0000FF00) >> 8);
	m_Toggle[3].Data = (char)((TC & 0x000000FF) >> 0);

	m_Toggle[0].Stack->index(m_Toggle[0].Data);
	m_Toggle[1].Stack->index(m_Toggle[1].Data);
	m_Toggle[2].Stack->index(m_Toggle[2].Data);
	m_Toggle[3].Stack->index(m_Toggle[3].Data);

	m_Toggle[0].Button->setPressed();
	m_Toggle[0].Button->cancelPressed();

	CtHLayout* pLayout = new CtHLayout();
	pLayout->addStretch(222);
	pLayout->addWidget(m_Toggle[0].Button, 87);
	pLayout->addWidget(new CtLabel("h", fSet), CtMargin(0, 10), AlignLeft, 56);
	pLayout->addWidget(m_Toggle[1].Button, 87);
	pLayout->addWidget(new CtLabel("m", fSet), CtMargin(0, 10), AlignLeft, 56);
	pLayout->addWidget(m_Toggle[2].Button, 87);
	pLayout->addWidget(new CtLabel("s", fSet), CtMargin(0, 10), AlignLeft, 56);
	pLayout->addWidget(m_Toggle[3].Button, 87);
	pLayout->addWidget(new CtLabel("f", fSet), CtMargin(0, 10), AlignLeft, 222);

	return pLayout;
}
CtContainerToggleDialog::ToggleButton CtContainerToggleDialog_Tc::createTch()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 0; i <= 23; i++) {
		char str[5] = { 0 };
		sprintf(str, "%02d", i);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack  = pStackLabel;
	Toggle.Data   = 0;
	Toggle.Max    = 23;

	return Toggle;
}
CtContainerToggleDialog::ToggleButton CtContainerToggleDialog_Tc::createTcm()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 0; i <= 59; i++) {
		char str[5] = { 0 };
		sprintf(str, "%02d", i);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack = pStackLabel;
	Toggle.Data  = 0;
	Toggle.Max = 59;

	return Toggle;
}
CtContainerToggleDialog::ToggleButton CtContainerToggleDialog_Tc::createTcs()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 0; i <= 59; i++) {
		char str[5] = { 0 };
		sprintf(str, "%02d", i);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack = pStackLabel;
	Toggle.Data = 0;
	Toggle.Max = 59;

	return Toggle;
}
CtContainerToggleDialog::ToggleButton CtContainerToggleDialog_Tc::createTcf()
{
	int max = APL_PARAM_GET_DATA(AplParamTcFrameMax);

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 0; i <= max; i++) {
		char str[5] = { 0 };
		sprintf(str, "%02d", i);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack = pStackLabel;
	Toggle.Data = 0;
	Toggle.Max = max;

	return Toggle;
}



//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------


bool CtContainerToggleDialog_Tc::executionSet()
{
	CtWindow *pWindow = NULL;
	if (m_CurSelect == m_Toggle.size() - 1) {
		unsigned int TC = 0;
		TC = TC | (m_Toggle[0].Data << 24);
		TC = TC | (m_Toggle[1].Data << 16);
		TC = TC | (m_Toggle[2].Data << 8);
		TC = TC | (m_Toggle[3].Data << 0);
		APL_PARAM_SET_DATA(AplParamSetTc, (int)TC);
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);
	}
	else {
		m_CurSelect++;
		m_Toggle[m_CurSelect].Button->setPressed();
		m_Toggle[m_CurSelect].Button->cancelPressed();
	}

	return true;
}
bool CtContainerToggleDialog_Tc::executionReset()
{
	m_Toggle[0].Data = 0;
	m_Toggle[1].Data = 0;
	m_Toggle[2].Data = 0;
	m_Toggle[3].Data = 0;

	m_Toggle[0].Stack->index(m_Toggle[0].Data);
	m_Toggle[1].Stack->index(m_Toggle[1].Data);
	m_Toggle[2].Stack->index(m_Toggle[2].Data);
	m_Toggle[3].Stack->index(m_Toggle[3].Data);

	return true;
}
