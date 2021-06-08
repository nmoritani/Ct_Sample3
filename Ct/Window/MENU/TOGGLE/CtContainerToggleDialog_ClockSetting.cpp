/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerToggleDialog_ClockSetting.h"
//#include <stdlib.h>

CtContainerToggleDialog_ClockSetting::CtContainerToggleDialog_ClockSetting(CtWindowID id) :CtContainerToggleDialog(id)
{
	memset(&m_Clock, 0, sizeof(m_Clock));
	setClassType(CtClassType_LayoutMain);
}
CtContainerToggleDialog_ClockSetting::~CtContainerToggleDialog_ClockSetting()
{
	destroyContainer();
}

//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------
CtLayout* CtContainerToggleDialog_ClockSetting::createToggle()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtHLayout* pLayout = new CtHLayout();
	pLayout->addStretch(172);
	if (getClockType() == DateFormat_YMD) {
		/* Date */
		CtLayout* pDate = createLayoutDate();
		/* Time */
		CtLayout* pTime = createLayoutTime();
		pLayout->addWidget(pDate, AlignLeft, 430);
		pLayout->addStretch(70);
		pLayout->addWidget(pTime, AlignRight, 260);
	}
	else {
		/* Time */
		CtLayout* pTime = createLayoutTime();
		/* Date */
		CtLayout* pDate = createLayoutDate();
		pLayout->addWidget(pTime, AlignLeft, 260);
		pLayout->addStretch(70);
		pLayout->addWidget(pDate, AlignRight, 430);
	}
	pLayout->addStretch(58);

	/* Clockèâä˙âª */
	unsigned char Data[AplParamDispClockDate_Size] = { 0 };
	APL_PARAM_GET_DATA_AREA(AplParamDispClockDate, (unsigned char*)Data, AplParamDispClockDate_Size);
	bool bFlag = false;

	if (Data[5] == 0xFF && Data[4] == 0xFF && Data[3] == 0xFF && Data[2] == 0xFF && Data[1] == 0xFF) {
		bFlag = true;
	}
	m_Toggle[m_Clock[ClockType_Year]].Data = (bFlag ? 2019 : (Data[5] | (Data[6] << 8)));
	m_Toggle[m_Clock[ClockType_Month]].Data = (bFlag ? 1 : Data[4]);
	m_Toggle[m_Clock[ClockType_Date]].Data = (bFlag ? 1 : Data[3]);
	m_Toggle[m_Clock[ClockType_Hour]].Data = (bFlag ? 0 : Data[2]);
	m_Toggle[m_Clock[ClockType_Min]].Data = (bFlag ? 0 : Data[1]);

	m_Toggle[0].Stack->index(m_Toggle[0].Data - m_Toggle[0].offset);
	m_Toggle[1].Stack->index(m_Toggle[1].Data - m_Toggle[1].offset);
	m_Toggle[2].Stack->index(m_Toggle[2].Data - m_Toggle[2].offset);
	m_Toggle[3].Stack->index(m_Toggle[3].Data - m_Toggle[3].offset);
	m_Toggle[4].Stack->index(m_Toggle[4].Data - m_Toggle[4].offset);

	m_Toggle[0].Button->setPressed();
	m_Toggle[0].Button->cancelPressed();

	return pLayout;
}
CtLayout* CtContainerToggleDialog_ClockSetting::createLayoutDate()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White);
	CtHLayout*	pLayout = new CtHLayout();

	switch (getClockType()) {
	case DateFormat_YMD:
	default:
	{
		// Year
		createYear();
		// Month
		createMonth();
		// Date
		createDate();
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Year]].Button, 122);
		pLayout->addWidget(new CtLabel(".", fSet), CtMargin(0, 10), AlignCenter, 56);
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Month]].Button, 112);
		pLayout->addWidget(new CtLabel(".", fSet), CtMargin(0, 10), AlignCenter, 56);
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Date]].Button, 87);
	}
	break;
	case DateFormat_MDY:
	{
		// Month
		createMonth();
		// Date
		createDate();
		// Year
		createYear();
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Month]].Button, 112);
		pLayout->addWidget(new CtLabel(".", fSet), CtMargin(0, 10), AlignCenter, 56);
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Date]].Button, 87);
		pLayout->addWidget(new CtLabel(".", fSet), CtMargin(0, 10), AlignCenter, 56);
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Year]].Button, 122);
	}
	break;
	case DateFormat_DMY:
	{
		// Date
		createDate();
		// Month
		createMonth();
		// Year
		createYear();
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Date]].Button, 87);
		pLayout->addWidget(new CtLabel(".", fSet), CtMargin(0, 10), AlignCenter, 56);
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Month]].Button, 112);
		pLayout->addWidget(new CtLabel(".", fSet), CtMargin(0, 10), AlignCenter, 56);
		pLayout->addWidget(m_Toggle[m_Clock[ClockType_Year]].Button, 122);
	}
	break;
	}

	return pLayout;
}
CtLayout* CtContainerToggleDialog_ClockSetting::createLayoutTime()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White);
	// Hour
	createHour();
	// Min
	createMin();

	CtHLayout*	pLayout = new CtHLayout();
	pLayout->addWidget(m_Toggle[m_Clock[ClockType_Hour]].Button, 87);
	pLayout->addWidget(new CtLabel(":", fSet),  CtMargin(0, 10), AlignCenter, 56);
	pLayout->addWidget(m_Toggle[m_Clock[ClockType_Min]].Button, 87);

	return pLayout;
}
void CtContainerToggleDialog_ClockSetting::createYear()
{
	int StartYear = 2000 + APL_PARAM_GET_DATA(AplParamLifeStartYear);
	int EndYear = 2000 + APL_PARAM_GET_DATA(AplParamLifeEndYear);

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 0; i <= EndYear - StartYear; i++) {
		char str[5] = { 0 };
		sprintf(str, "%d", i + StartYear);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack  = pStackLabel;
	Toggle.Data   = StartYear;
	Toggle.Max    = EndYear;
	Toggle.offset = Toggle.Data;

	m_Clock[ClockType_Year] = m_Toggle.size();
	m_Toggle.push_back(Toggle);
}
void CtContainerToggleDialog_ClockSetting::createMonth()
{

	char* pMonth[12] = {
		"JAN",
		"FEB",
		"MAR",
		"APR",
		"MAY",
		"JUN",
		"JUL",
		"AUG",
		"SEP",
		"OCT",
		"NOV",
		"DEC"
	};

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 0; i < 12; i++) {
		char str[5] = { 0 };
		sprintf(str, "%s", pMonth[i]);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack  = pStackLabel;
	Toggle.Data   = 1;
	Toggle.Max    = 12;
	Toggle.offset = Toggle.Data;

	m_Clock[ClockType_Month] = m_Toggle.size();
	m_Toggle.push_back(Toggle);
}
void CtContainerToggleDialog_ClockSetting::createDate()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 1; i <= 31; i++) {
		char str[5] = { 0 };
		sprintf(str, "%d", i);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i-1);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack  = pStackLabel;
	Toggle.Data   = 1;
	Toggle.Max    = 31;
	Toggle.offset = Toggle.Data;

	m_Clock[ClockType_Date] = m_Toggle.size();
	m_Toggle.push_back(Toggle);

}
void CtContainerToggleDialog_ClockSetting::createHour()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 0; i <= 23; i++) {
		char str[5] = { 0 };
		sprintf(str, "%d", i);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack  = pStackLabel;
	Toggle.Data   = 0;
	Toggle.Max    = 23;
	Toggle.offset = Toggle.Data;

	m_Clock[ClockType_Hour] = m_Toggle.size();
	m_Toggle.push_back(Toggle);

}
void CtContainerToggleDialog_ClockSetting::createMin()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	for (int i = 0; i <= 59; i++) {
		char str[5] = { 0 };
		sprintf(str, "%d", i);
		pStackLabel->addLabel(new CtLabel(str, fSet), CtMargin(0), AlignCenter, i);
	}
	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack  = pStackLabel;
	Toggle.Data   = 0;
	Toggle.Max    = 59;
	Toggle.offset = Toggle.Data;

	m_Clock[ClockType_Min] = m_Toggle.size();
	m_Toggle.push_back(Toggle);

}


//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
void CtContainerToggleDialog_ClockSetting::executionUpdate()
{
	executionCheckData();

	/* DateCheck DateÇÕYearÇ‚MonthÇ…ÇÊÇ¡Çƒç≈ëÂílÇ™ïœÇÌÇÈ */
	int date   = m_Toggle[m_Clock[ClockType_Date]].Data;
	int offset = m_Toggle[m_Clock[ClockType_Date]].offset;
	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int maxday = days[m_Toggle[m_Clock[ClockType_Month]].Data - offset];
	if ((2 == m_Toggle[m_Clock[ClockType_Month]].Data) && (CLOCKSET_CHECK_LEAP_YEAR(m_Toggle[m_Clock[ClockType_Year]].Data))) {
		maxday = 29;
	}
	if (date > maxday) {
		date = 0 + offset;
	}
	m_Toggle[m_Clock[ClockType_Date]].Data = date;
	m_Toggle[m_Clock[ClockType_Date]].Max  = maxday;
	m_Toggle[m_Clock[ClockType_Date]].Stack->index(m_Toggle[m_Clock[ClockType_Date]].Data - offset);

	executionPrintDebug();
}

bool CtContainerToggleDialog_ClockSetting::executionSet()
{
	CtWindow *pWindow = NULL;
	if (m_CurSelect == m_Toggle.size() - 1) {
		unsigned char Data[AplParamClockDate_Size] = { 0 };
		Data[6] = (unsigned char)((m_Toggle[m_Clock[ClockType_Year]].Data & 0xFF00) >> 8);
		Data[5] = (unsigned char)( m_Toggle[m_Clock[ClockType_Year]].Data & 0xFF);
		Data[4] = (unsigned char)m_Toggle[m_Clock[ClockType_Month]].Data;
		Data[3] = (unsigned char)m_Toggle[m_Clock[ClockType_Date]].Data;
		Data[2] = (unsigned char)m_Toggle[m_Clock[ClockType_Hour]].Data;
		Data[1] = (unsigned char)m_Toggle[m_Clock[ClockType_Min]].Data;
		Data[0] = (unsigned char)0x00;
		APL_PARAM_SET_DATA_AREA(AplParamClockDate, (unsigned char*)(Data), AplParamClockDate_Size);
		CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);
	}
	else {
		m_CurSelect++;
		m_Toggle[m_CurSelect].Button->setPressed();
		m_Toggle[m_CurSelect].Button->cancelPressed();
	}

	return true;
}

CtContainerToggleDialog_ClockSetting::DateFormat CtContainerToggleDialog_ClockSetting::getClockType()
{
	DateFormat format = DateFormat_YMD;
	switch (APL_PARAM_GET_DATA(AplParamDateFormatMode)) {
	case APL_SYS_PARAM_DATE_FORMAT_YEAR:
		format = DateFormat_YMD;
		break;
	case APL_SYS_PARAM_DATE_FORMAT_MONTH:
		format = DateFormat_MDY;
		break;
	case APL_SYS_PARAM_DATE_FORMAT_DATE:
		format = DateFormat_DMY;
		break;
	default:
		break;
	}
	return format;
}
