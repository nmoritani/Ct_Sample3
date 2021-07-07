#include "system_common.h"
#include "system_wrapper.h"

#ifdef WIN32
#include    <windows.h>
#include    <time.h>
#else
#include <sys/time.h>
#endif

#define EPOCHFILETIME (116444736000000000i64)

#ifdef WIN32
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
#endif

#ifdef Linux
SYSWRAP_ERROR syswrap_get_time(syswrap_timeval_t *tv)
{
	struct timeval cur;

	if (tv == NULL)
		return SYSWRAP_ERR_PAR;
	
	gettimeofday(&cur, NULL);
	
	tv->tv_sec = cur.tv_sec;
	tv->tv_usec = cur.tv_usec;
	
	return SYSWRAP_ERR_OK;
}

#endif


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
}

long syswrap_diff_time(syswrap_timeval_t *tv1, syswrap_timeval_t *tv2)
{
	long usec1 = 0, usec2 = 0;

	usec1 = tv1->tv_sec * 1000 + tv1->tv_usec;
	usec2 = tv2->tv_sec * 1000 + tv2->tv_usec;

	return (usec1 - usec2);
}
