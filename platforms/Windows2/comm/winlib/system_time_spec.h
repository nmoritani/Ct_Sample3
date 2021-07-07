#include    <windows.h>
#include    <time.h>

#define EPOCHFILETIME (116444736000000000i64)

extern void get_passage_time(struct timespec *ts, int msec);
extern void get_currentTimer(struct timespec *ts);
extern bool Is_msec_timeout(struct timespec *starttime, long msec, struct timespec *current_time);

extern long get_elapsed_time_msec(struct timespec *start);
