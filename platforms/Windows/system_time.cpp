#include "system_common.h"

#include    <windows.h>
#include    <time.h>

#define EPOCHFILETIME (116444736000000000i64)

SYSWRAP_ERROR syswrap_get_time(syswrap_timeval_t *ts)
{
	FILETIME        tagFileTime;
	LARGE_INTEGER   largeInt;
	__int64         val64;

	if (ts == NULL)
		return SYSWRAP_ERR_PAR;
	
	GetSystemTimeAsFileTime(&tagFileTime);

	largeInt.LowPart = tagFileTime.dwLowDateTime;
	largeInt.HighPart = tagFileTime.dwHighDateTime;
	val64 = largeInt.QuadPart;
	val64 = val64 - EPOCHFILETIME;
	val64 = val64 / 10;
	ts->tv_sec = (long)(val64 / 1000000);
	ts->tv_usec = (long)(val64 % 1000000);

	return SYSWRAP_ERR_OK;
}

//Œo‰ßŒãŽžŽæ“¾
SYSWRAP_ERROR syswrap_add_time_ms(syswrap_timeval_t *tv, int msec)
{
	long sec = 0, usec = 0;

	/* divide msec to sec and usec */
	sec = msec / 1000;
	usec = (msec % 1000) * 1000;

	/* add current time */
	sec = tv->tv_sec + sec;
	usec = tv->tv_usec + usec;

	/* move up and store */
	tv->tv_sec = sec + usec / (1000 * 1000 * 1000);
	tv->tv_usec = usec % (1000 * 1000 * 1000);

	return SYSWRAP_ERR_OK;
}

long syswrap_sub_time(syswrap_timeval_t *tv1, syswrap_timeval_t *tv2)
{
	long usec1 = 0, usec2 = 0;

	usec1 = tv1->tv_sec * 1000 + tv1->tv_usec;
	usec2 = tv2->tv_sec * 1000 + tv2->tv_usec;

	return (usec1 - usec2);
}


unsigned long syswrap_get_usec()
{
	unsigned long usec = 0;

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	
	LARGE_INTEGER sec;
	QueryPerformanceCounter(&sec);

	usec = (unsigned long)(sec.QuadPart/freq.QuadPart);
	
	return usec;
}

unsigned long syswrap_get_msec()
{
	unsigned long msec = 0;

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	
	LARGE_INTEGER sec;
	QueryPerformanceCounter(&sec);

	msec = (unsigned long)(sec.QuadPart/freq.QuadPart) * 1000;
	
	return msec;
}

long syswrap_sub_sec(unsigned long sec1, unsigned long sec2)
{
	long difftime;

	if (sec1 > sec2) {
		difftime = sec1 - sec2;

	} else {
		difftime = (unsigned long)(-1) - sec2;
		difftime += sec1;
	}

	return difftime;
}

