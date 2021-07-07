#include "pthread_common.h"

#define	CYC_ATTR_FLG_CRE_WITH_STAT	(0x02)	//サイクルタイマ生成時にタイマ開始

extern int init_cyclehandler_table();
extern int create_cycle_handler(unsigned int id, const cycle_time_arg *arg);
extern int delete_cycle_handler(unsigned int id);
extern int stop_cycle_handler(unsigned int id);
extern int active_cycle_handler(unsigned int id, bool act, bool init);
extern int start_cycle_handler(unsigned int id);
extern int thread_cycletimer();
extern int reference_cycle_handler(unsigned int id, cycle_handler_state *pk_rcyc);
