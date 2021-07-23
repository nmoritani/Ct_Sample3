#pragma once

/*************************************************
*
*      Virtual Middle InterFace
*
**************************************************/
#include "SysIf.h"
#include "TclIf.h"
#include <Windows.h>
static SYS_EVENT_CALLBACK callbackFunc = NULL;

void SYS_TPanel_SetSlideEventEnable(BOOL flag)
{
}

SYS_KEY_STATUS SYS_Key_GetStatus(void) {
	SYS_KEY_STATUS keyStatus = { 0 };
	return keyStatus;
}

void SYS_Event_AddCallback(SYS_EVENT_CALLBACK callback)
{
	callbackFunc = callback;
}

SYSTEMTIME SysDateTimeToSystemTime(const SYS_DATE_TIME *systime)
{
	SYSTEMTIME ret;
	memset(&ret, 0, sizeof(ret));

	if (!systime) return ret;

	ret.wYear = systime->Year;
	ret.wMonth = systime->Month;
	ret.wDayOfWeek = 0;
	ret.wDay = systime->Day;
	ret.wHour = systime->Hour;
	ret.wMinute = systime->Min;
	ret.wSecond = systime->Sec;
	ret.wMilliseconds = 0;

	return ret;
}

SYS_DATE_TIME SystemTimeToSysDateTime(const SYSTEMTIME *systemtime)
{
	SYS_DATE_TIME ret;
	memset(&ret, 0, sizeof(ret));

	if (!systemtime) return ret;

	ret.Year = systemtime->wYear;
	ret.Month = (UB)systemtime->wMonth;
	ret.Day = (UB)systemtime->wDay;
	ret.Hour = (UB)systemtime->wHour;
	ret.Min = (UB)systemtime->wMinute;
	ret.Sec = (UB)systemtime->wSecond;

	return ret;
}

SYS_DATE_TIME SYS_DateTime_GetValue(void)
{
	SYSTEMTIME systime;

	GetLocalTime(&systime);

	return SystemTimeToSysDateTime(&systime);
}

SYS_DATE_TIME_DATA SYS_DateTime_GetValueData()
{
	SYS_DATE_TIME_DATA ret;

	ret.Value = SYS_DateTime_GetValue();
	ret.Enabled = TRUE;

	return ret;
}

SYS_RET SYS_DateTime_GetAddSec(SYS_DATE_TIME *Dst, const SYS_DATE_TIME *DateTime, long long Sec)
{
	if (!DateTime || !Dst) return SYS_NG;

	SYSTEMTIME systime;
	FILETIME filetime;		// 100nano’PˆÊ
	long long ftSec;

	systime = SysDateTimeToSystemTime(DateTime);

	if (SystemTimeToFileTime(&systime, &filetime) == 0) {
		return SYS_NG;
	}

	ftSec = (((long long)filetime.dwHighDateTime << 32) + filetime.dwLowDateTime);
	
	// 100ƒiƒm•b’PˆÊ‚Å·•ª‚ð‰ÁŽZ
	ftSec += (Sec * 1000 * 1000 * 10);

	// filetime‚Ö•ÏŠ·
	filetime.dwHighDateTime = ftSec >> 32;
	filetime.dwLowDateTime = ftSec & 0xffffffff;
	
	if (FileTimeToSystemTime(&filetime, &systime) == 0) {
		return SYS_NG;
	}

	*Dst = SystemTimeToSysDateTime(&systime);
	
	return SYS_OK;
}

TCL_ER TCL_GetDateTimeDelay(SYS_DATE_TIME *pValue, W delay)
{
	*pValue = SYS_DateTime_GetValue();
	return TCL_ER_OK;
}

#if 1
#include "AvcIf.h"
static AVDF_CALLBACK avdf_callback = NULL;
static void* avdf_callback_param = NULL;

AVC_ER AVDF_AddCallback(AVDF_CALLBACK p_CbAdr, VP vp_Param, BOOL bl_ExeOnBlank)
{
	avdf_callback = p_CbAdr;
	avdf_callback_param = vp_Param;
	return AVC_ER_OK;
}

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
	void AvdfCycHandler(VP_INT exinf)
	{
		if (avdf_callback) {
			avdf_callback(avdf_callback_param);
		}
	}
#ifdef __cplusplus
}
#endif 
#endif	/* __cplusplus */
