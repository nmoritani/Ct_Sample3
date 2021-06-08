/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/
#include "CtCtnrDateTime.h"


CtCtnrDateTime::CtCtnrDateTime()
{
}

CtCtnrDateTime::~CtCtnrDateTime()
{
}

CtLayout* CtCtnrDateTime::createContainer()
{
	CtRecViewFontSet m_fSet_Center = CtRecViewFontSet(FontTypeOutline_alignCenter, CtColor::white);
	m_pAll = new CtLayout();
	m_pDateTime = new CtLabel("", m_fSet_Center);
	m_pAll->addWidget(m_pDateTime);

	return m_pAll;
}

bool CtCtnrDateTime::destroyWindow()
{
	// 周期Timerのみ(Alarmは放置)
	if (CtTimer::getInstance()->isActTimerId(CT_TIMER_ID_DATE_TIME, this) == true) {
		CtTimer::getInstance()->stopCyclic(CT_TIMER_ID_DATE_TIME, this);
	}
	return true;
}
bool CtCtnrDateTime::startupContainer() {
	updateDateTime();
	return true;
}
bool CtCtnrDateTime::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	bool isRedraw = false;
	
	switch (t_Id) {
	case AplParamDispClockDate:
	case AplParamIndicatorDateTime:
	case AplParamDateFormatMode:
	case AplParamTimeStamp:
		isRedraw |= updateDateTime();	/* pgr2711 */
		break;
	default:
		break;
	}
	return isRedraw;
}

bool CtCtnrDateTime::handleTimerEvent(const CtEventTimer& Timer) {
	bool isRedraw = false;

	switch (Timer.getTimeUid())
	{
	case CT_TIMER_ID_DATE_TIME:
		isRedraw |= updateDateTime();	/* pgr2711 */
		break;
	default:
		break;
	}

	return isRedraw;
}

bool CtCtnrDateTime::setStatusMode(bool bStatusMode) {
	m_bStatusMode = bStatusMode;
	
	//if(bStatusMode) m_pAll->setScreenSel(ScreenAll);
	
	updateDateTime();
	return true;
}

bool CtCtnrDateTime::updateDateTime() {
	if (APL_PARAM_GET_DATA(AplParamTimeStamp) != APL_SYS_PARAM_TIMESTAMP_OFF ) {
		if (CtTimer::getInstance()->isActTimerId(CT_TIMER_ID_DATE_TIME, this) == true) CtTimer::getInstance()->stopCyclic(CT_TIMER_ID_DATE_TIME, this);
		return m_pDateTime->setVisible(false);
	}
	//if (m_bStatusMode == false && APL_PARAM_GET_DATA(AplParamDispModeCheck) == APL_SYS_PARAM_SWITCH_ON) {
	//else {
	//	//m_pDateTime->setScreenSel(ScreenAll);
	//}
	bool bRet = false;
	int Year = 0;
	int Month = 0;
	int Day = 0;
	int Hour = 0;
	int Min = 0;
	int Sec = 0;

	int LifeStartYear = 0;
	int LifeEndYear = 0;
	int lastd = 0;
	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	/* Clock初期化 */
	unsigned char Data[AplParamDispClockDate_Size] = { 0 };
	APL_PARAM_GET_DATA_AREA(AplParamDispClockDate, (unsigned char*)Data, AplParamDispClockDate_Size);

	LifeStartYear = 2000 + APL_PARAM_GET_DATA(AplParamLifeStartYear);
	LifeEndYear = 2000 + APL_PARAM_GET_DATA(AplParamLifeEndYear);

	if (Data[5] == 0xFF && Data[4] == 0xFF && Data[3] == 0xFF && Data[2] == 0xFF && Data[1] == 0xFF) {
		Year = 2019;
		Month = 1;
		Day = 1;
		Hour = 0;
		Min = 0;
		Sec = 0;
	}
	else {
		Year = (Data[5] | (Data[6] << 8));
		Month = Data[4];
		Day = Data[3];
		Hour = Data[2];
		Min = Data[1];
		Sec = Data[0];
	}

	/* LifeYearCheck */
	if (Year > LifeEndYear) {
		Year = LifeStartYear;
	}
	else if (Year < LifeStartYear) {
		Year = LifeEndYear;
	}
	/* MonthCheck */
	if (Month > 12) {
		Month = 1;
	}
	else if (Month < 1) {
		Month = 12;
	}
	/* DateCheck */
	lastd = days[Month - 1];
	if (Month == 2 && CLOCKSET_CHECK_LEAP_YEAR(Year)) {
		lastd = 29;
	}
	/* うるう年チェック */
	if (Day > lastd) {
		Day = 1;
	}
	else if (Day < 1) {
		Day = lastd;
	}

	/* HourCheck */
	if (Hour > 23) {
		Hour = 0;
	}
	else if (Hour < 0) {
		Hour = 23;
	}
	/* MinCheck */
	if (Min > 59) {
		Min = 0;
	}
	else if (Min < 0) {
		Min = 59;
	}
	
	char Str[50] = { 0 };
	char Date[30] = { 0 };
	char Time[20] = { 0 };

	int DateTimeDispMode = APL_PARAM_GET_DATA(AplParamIndicatorDateTime);

	if (m_bStatusMode) {
		DateTimeDispMode = APL_SYS_PARAM_INDICATOR_DATETIME_DATE_TIME;
	}
    else if (DateTimeDispMode == APL_SYS_PARAM_INDICATOR_DATETIME_OFF) {
		if (CtTimer::getInstance()->isActTimerId(CT_TIMER_ID_DATE_TIME, this) == true) CtTimer::getInstance()->stopCyclic(CT_TIMER_ID_DATE_TIME, this);
		return m_pDateTime->setVisible(false);
	}
	
	m_pDateTime->setVisible(true);

	if( DateTimeDispMode == APL_SYS_PARAM_INDICATOR_DATETIME_TIME
	 || DateTimeDispMode == APL_SYS_PARAM_INDICATOR_DATETIME_DATE_TIME) {
		sprintf(Time, "%2d:%02d:%02d", Hour, Min, Sec);
	}

	if (DateTimeDispMode == APL_SYS_PARAM_INDICATOR_DATETIME_DATE
		|| DateTimeDispMode == APL_SYS_PARAM_INDICATOR_DATETIME_DATE_TIME) {
		switch (APL_PARAM_GET_DATA(AplParamDateFormatMode)) {
		case APL_SYS_PARAM_DATE_FORMAT_YEAR:
			sprintf(Date, "%d %s %d", Year, convertMonthToString(Month), Day);
			break;
		case APL_SYS_PARAM_DATE_FORMAT_MONTH:
			sprintf(Date, "%s %d %d", convertMonthToString(Month), Day, Year);
			break;
		case APL_SYS_PARAM_DATE_FORMAT_DATE:
			sprintf(Date, "%d %s %d", Day, convertMonthToString(Month), Year);
			break;
		default:
			break;
		}
	}
	if (Date != NULL && Time != NULL) {
		sprintf(Str, "%s %s", Date, Time);
	}
	else if (Data != NULL) {
		sprintf(Str, "%s", Date);
	}
	else {
		sprintf(Str, "%s", Time);
	}
	
	bRet |= m_pDateTime->setText(Str);	/* pgr2711 */

	CtTimer::getInstance()->startCyclic(CT_TIMER_ID_DATE_TIME, 500, this);
	return bRet;
}

char* CtCtnrDateTime::convertMonthToString(int Month) {
	char* pStr = NULL;

	switch (Month) {
	case 1:
		pStr = "JAN";  // STR_ID_JAN
		break;
	case 2:
		pStr = "FEB";  // STR_ID_FEB
		break;
	case 3:
		pStr = "MAR";  // STR_ID_MAR
		break;
	case 4:
		pStr = "APR";  // STR_ID_APR
		break;
	case 5:
		pStr = "MAY";  // STR_ID_MAY
		break;
	case 6:
		pStr = "JUN";  // STR_ID_JUN
		break;
	case 7:
		pStr = "JUL";  // STR_ID_JUL
		break;
	case 8:
		pStr = "AUG";  // STR_ID_AUG
		break;
	case 9:
		pStr = "SEP";  // STR_ID_SEP
		break;
	case 10:
		pStr = "OCT";  // STR_ID_OCT
		break;
	case 11:
		pStr = "NOV";  // STR_ID_NOV
		break;
	case 12:
		pStr = "DEC";  // STR_ID_DEC
		break;
	default:
		return NULL;
	}
	return pStr;
}
