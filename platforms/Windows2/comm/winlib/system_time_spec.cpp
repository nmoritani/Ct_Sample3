#include "pthread_common.h"
#include "system_time_spec.h"

//////////////////////////////////////////////////////////////////
// WIN32用API
//////////////////////////////////////////////////////////////////
#ifdef WIN32_GUI_SIM

struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};

//日付時刻取得
static int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	FILETIME        tagFileTime;
	LARGE_INTEGER   largeInt;
	__int64         val64;
	static int      tzflag;

	if (tv) {
		GetSystemTimeAsFileTime(&tagFileTime);

		largeInt.LowPart = tagFileTime.dwLowDateTime;
		largeInt.HighPart = tagFileTime.dwHighDateTime;
		val64 = largeInt.QuadPart;
		val64 = val64 - EPOCHFILETIME;
		val64 = val64 / 10;
		tv->tv_sec = (long)(val64 / 1000000);
		tv->tv_usec = (long)(val64 % 1000000);
	}

	if (tz) {
		if (!tzflag) {
			_tzset();
			tzflag++;
		}

		long _Timezone = 0;
		_get_timezone(&_Timezone);
		tz->tz_minuteswest = _Timezone / 60;

		int _Daylight = 0;
		_get_daylight(&_Daylight);
		tz->tz_dsttime = _Daylight;
	}

	return 0;
}
#endif
//////////////////////////////////////////////////////////////////

//タイムアウト判定
bool Is_msec_timeout(struct timespec *starttime, long msec, struct timespec *current_time)
{
	int elapsed_time;
	get_currentTimer(current_time);
	elapsed_time = get_elapsed_time_msec(starttime);
	return (msec <= elapsed_time);
}

//経過後時刻取得
void get_passage_time(struct timespec *ts, int msec)
{
	struct timeval tv;
	int		sec = 0, nsec = 0;

	/* divide msec to sec and nsec */
	if (0 < msec) {
		sec = msec / 1000;
		nsec = (msec % 1000) * 1000 * 1000;
	}

	/* add current time */
	gettimeofday(&tv, NULL);
	sec = tv.tv_sec + sec;
	nsec = tv.tv_usec * 1000 + nsec;

	/* move up and store */
	ts->tv_sec = sec + nsec / (1000 * 1000 * 1000);
	ts->tv_nsec = nsec % (1000 * 1000 * 1000);
}

//時刻差分演算
long diff_timespec(struct timespec *start, struct timespec *stop)
{
	struct timespec result;

	if (stop->tv_sec < start->tv_sec) {
		return 0;
	}

	if ((stop->tv_sec == start->tv_sec) && (stop->tv_nsec <= start->tv_nsec)) {
		return 0;
	}

	if ((stop->tv_nsec - start->tv_nsec) < 0) {
		result.tv_sec = stop->tv_sec - start->tv_sec - 1;
		result.tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
	} else {
		result.tv_sec = stop->tv_sec - start->tv_sec;
		result.tv_nsec = stop->tv_nsec - start->tv_nsec;
	}

	return (long)((result.tv_sec * 1000.0) + ((result.tv_nsec / 1000.0) / 1000.0));
}

//現在時間取得
void get_currentTimer(struct timespec *ts)
{
	get_passage_time(ts, 0);
}

//経過時間取得(ms単位)
long get_elapsed_time_msec(struct timespec *start)
{
	struct timespec current;

	//現在時刻取得
	get_currentTimer(&current);

	return diff_timespec(start, &current);
}

