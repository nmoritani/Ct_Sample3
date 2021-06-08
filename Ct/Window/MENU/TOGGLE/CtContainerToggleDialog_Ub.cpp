/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerToggleDialog_Ub.h"

CtContainerToggleDialog_Ub::CtContainerToggleDialog_Ub(CtWindowID id) : CtContainerToggleDialog(id)
{
	setClassType(CtClassType_LayoutMain);
}
CtContainerToggleDialog_Ub::~CtContainerToggleDialog_Ub()
{
	destroyContainer();
}

//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------
CtLayout* CtContainerToggleDialog_Ub::createTitle() 
{
	/* Title */
	CtContainerMenuTitle* pTitle = new CtContainerMenuTitle(m_WindowID);

	CtLayout *pLayout = new CtLayout();
	pLayout->addContainer(pTitle);

	return pLayout;
}
CtLayout* CtContainerToggleDialog_Ub::createToggle()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = NULL;
	CtButton*     pButton = NULL;

	for (int i = 0; i < 4; i++) {
		pStackLabel = new CtStackLabel();
		for (int j = 0; j <= 255; j++) {
			char str[5] = { 0 };
			sprintf(str, "%02X", j);
			pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, j);
		}
		pButton = new CtButton(AutoSize, pStackLabel);

		ToggleButton Toggle;
		memset(&Toggle, 0, sizeof(Toggle));
		Toggle.Button = pButton;
		Toggle.Stack = pStackLabel;
		Toggle.Data = 0;
		Toggle.Max = 255;
		m_Toggle.push_back(Toggle);

	}

	/* UB‰Šú‰» */
	unsigned int USERSBIT = APL_PARAM_GET_DATA(AplParamSetUb);
	m_Toggle[0].Data = ((USERSBIT & 0xFF000000) >> 24);
	m_Toggle[1].Data = ((USERSBIT & 0x00FF0000) >> 16);
	m_Toggle[2].Data = ((USERSBIT & 0x0000FF00) >> 8);
	m_Toggle[3].Data = ((USERSBIT & 0x000000FF) >> 0);

	m_Toggle[0].Stack->index(m_Toggle[0].Data);
	m_Toggle[1].Stack->index(m_Toggle[1].Data);
	m_Toggle[2].Stack->index(m_Toggle[2].Data);
	m_Toggle[3].Stack->index(m_Toggle[3].Data);

	m_Toggle[0].Button->setPressed();
	m_Toggle[0].Button->cancelPressed();

	CtHLayout* pLayout = new CtHLayout();
	pLayout->addStretch(222);
	pLayout->addWidget(m_Toggle[0].Button, 87);
	pLayout->addStretch(56);
	pLayout->addWidget(m_Toggle[1].Button, 87);
	pLayout->addStretch(56);
	pLayout->addWidget(m_Toggle[2].Button, 87);
	pLayout->addStretch(56);
	pLayout->addWidget(m_Toggle[3].Button, 87);
	pLayout->addStretch(222);

	return pLayout;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
bool CtContainerToggleDialog_Ub::executionSet()
{
	CtWindow *pWindow = NULL;
	if (m_CurSelect == m_Toggle.size() - 1) {
		unsigned int USERSBIT = 0;
		USERSBIT = USERSBIT | (m_Toggle[0].Data << 24);
		USERSBIT = USERSBIT | (m_Toggle[1].Data << 16);
		USERSBIT = USERSBIT | (m_Toggle[2].Data << 8);
		USERSBIT = USERSBIT | (m_Toggle[3].Data << 0);
		APL_PARAM_SET_DATA(AplParamSetUb, (int)USERSBIT);
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);
	}
	else {
		m_CurSelect++;
		m_Toggle[m_CurSelect].Button->setPressed();
		m_Toggle[m_CurSelect].Button->cancelPressed();
	}

	return true;
}
bool CtContainerToggleDialog_Ub::executionReset()
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
