#include "pthread_common.h"
#include "pthread_thread.h"

int create_cycle_timer_thread(unsigned int id, thread_arg *parg)
{
	if (ERR_OK != create_thread(id, parg)) {
		return ERR_OBJ;
	}

	return thread_active(id);
}
