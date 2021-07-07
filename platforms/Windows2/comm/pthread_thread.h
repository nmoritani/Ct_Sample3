#include "pthread.h"
#include "pthread_common.h"


#define NUM_OF_THREAD	5
#define	TMAX_ACTCNT		1

extern int init_thread_table();
extern int create_thread(unsigned int id, const thread_arg *pk_ctsk);
extern int delete_thread(unsigned int id);
extern int get_thread_id(int *p_tid);
extern int thread_active(unsigned int id);
extern int thread_start(unsigned int id, unsigned int stacd);
extern int thread_delay(long ms_time);
extern int thread_join(unsigned int id);
