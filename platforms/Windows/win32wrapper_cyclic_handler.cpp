#include "win32wrapper_common.h"

#ifdef SYSTEM_WINDOWS

typedef struct {
	BOOL			use;
	
	BOOL			active;
	FUNC			func;
	void			*extinfo;
	int				cycletime;
	
	unsigned long	prevtime;
} cyclic_info_t;

#define	NUM_OF_CYCLIC_HANDLER	2

cyclic_info_t	cyclic_info_list[NUM_OF_CYCLIC_HANDLER] = {0};

#define CYCLE_TIME 10

static HANDLE h_cyclic_thread;
static BOOL cyclic_alive;
static THREAD_STATE cyclic_state;
static unsigned int tid;
static unsigned int __stdcall cyclic_thread(void* arg);

void execute_cyclic_handler(unsigned long curtime)
{
	for (int i = 0; i < NUM_OF_CYCLIC_HANDLER; i++) {
		cyclic_info_t *cyclic_info = &cyclic_info_list[i];

		if (cyclic_info->use == FALSE)
			continue;

		if (cyclic_info->active == FALSE)
			continue;

		if (syswrap_sub_sec(curtime, cyclic_info->prevtime) > cyclic_info->cycletime) {
			cyclic_info->func();
		}
		cyclic_info->prevtime = curtime;
	}
}

static unsigned __stdcall cyclic_thread(void *arg)
{
	while (cyclic_alive == TRUE) {
		cyclic_state = THREAD_STATE_RUN;
		unsigned long time1, time2;

		time1 = syswrap_get_msec();
		Sleep(CYCLE_TIME);
		time2 = syswrap_get_msec();

		execute_cyclic_handler(syswrap_sub_sec(time2, time1));
	}
	_endthreadex(0);
	
	cyclic_state = THREAD_STATE_DORMANT;
	return 0;
}


SYSWRAP_ERROR syswrap_cyclic_handler_init()
{
	cyclic_alive = TRUE;
	ZERO_CLEAR(cyclic_info_list);

	h_cyclic_thread = (HANDLE)_beginthreadex(NULL, 0, &cyclic_thread, NULL, 0, &tid);
	SetThreadPriority(cyclic_thread, THREAD_PRIORITY_HIGHEST);
	
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_cyclic_handler_term()
{

	cyclic_alive = FALSE;

	while (cyclic_state != THREAD_STATE_DORMANT) {
		Sleep(1);
	}
	
	ZERO_CLEAR(cyclic_info_list);

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, FUNC func, int cycletime)
{
	unsigned int i;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;

	if (cyclic_handler == NULL)
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(10);
	
	for (i = 0; i < NUM_OF_CYCLIC_HANDLER; i++) {
		if (cyclic_info_list[i].use == TRUE)
			continue;

		cyclic_info_list[i].use = TRUE;
		cyclic_info_list[i].active = FALSE;
		cyclic_info_list[i].func = func;
		cyclic_info_list[i].cycletime = cycletime;
		
		cyclic_handler->sysinfo = &cyclic_info_list[i];
		break;
	}
	if (i >= NUM_OF_CYCLIC_HANDLER)
		errcode = SYSWRAP_ERR_RESOVER;

	unlock_common_mutex();
	
	return errcode;
}

SYSWRAP_ERROR syswrap_destroy_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((cyclic_handler == NULL) || (cyclic_handler->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(11);
	
	cyclic_info_t *cyclic_info = (cyclic_info_t *)cyclic_handler->sysinfo;
	
	if (FALSE == cyclic_info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	ZERO_CLEAR(*cyclic_info);
	cyclic_handler->sysinfo = NULL;
	
	unlock_common_mutex();
	
	return errcode;
}


static SYSWRAP_ERROR active_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, bool active)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((cyclic_handler == NULL) || (cyclic_handler->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(13);
	
	cyclic_info_t *cyclic_info = (cyclic_info_t *)cyclic_handler->sysinfo;
	
	cyclic_info->active = active;
	cyclic_info->prevtime = syswrap_get_msec();

	unlock_common_mutex();
	
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_stop_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	return active_cyclic_handler(cyclic_handler, FALSE);
}


SYSWRAP_ERROR syswrap_start_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	return active_cyclic_handler(cyclic_handler, TRUE);
}

#endif

