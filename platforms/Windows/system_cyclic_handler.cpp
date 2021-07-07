#include "system_common.h"

typedef struct {
	BOOL			use;
	
	BOOL			active;
	HANDLER_FUNC	*func;
	int				cycletime;
	
	unsigned long	prevtime;
} cyclic_info_t;

#define	NUM_OF_CYCLIC_HANDLER	2

cyclic_info_t		info_list[NUM_OF_CYCLIC_HANDLER];

#define CYCLE_TIME 10

static HANDLE h_cyclic_thread;
static BOOL exitflag;
static unsigned int tid;
static unsigned int __stdcall cyclic_thread(void* arg);

void execute_cyclic_handler(unsigned long curtime)
{
	for (int i = 0; i < NUM_OF_CYCLIC_HANDLER; i++) {
		cyclic_info_t *cyclic_info = &info_list[i];

		if (cyclic_info->use == FALSE)
			continue;

		if (cyclic_info->active == FALSE)
			continue;

		if (syswrap_sub_sec(curtime, cyclic_info->prevtime) > cyclic_info->cycletime) {
			cyclic_info->func();

			cyclic_info->prevtime = curtime;
		}
	}
}

static unsigned __stdcall cyclic_thread(void *arg)
{
	while (exitflag) {
		unsigned long time1, time2;

		time1 = syswrap_get_msec();
		Sleep(CYCLE_TIME);
		time2 = syswrap_get_msec();

		execute_cyclic_handler(syswrap_sub_sec(time2, time1));
	}
	
	_endthreadex(0);
	
	return 0;
}


SYSWRAP_ERROR syswrap_cyclic_handler_initial()
{

	ZERO_CLEAR(info_list);

	h_cyclic_thread = (HANDLE)_beginthreadex(NULL, 0, &cyclic_thread, NULL, 0, &tid);
	SetThreadPriority(cyclic_thread, THREAD_PRIORITY_ABOVE_NORMAL);
	
	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, HANDLER_FUNC *func, int cycletime)
{
	unsigned int i;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;

	if (cyclic_handler == NULL)
		return SYSWRAP_ERR_PAR;

	for (i = 0; i < NUM_OF_CYCLIC_HANDLER; i++) {
		if (info_list[i].use == TRUE)
			continue;

		info_list[i].use = TRUE;
		info_list[i].active = TRUE;
		info_list[i].func = func;
		info_list[i].cycletime = cycletime;
		
		cyclic_handler->sysinfo = &info_list[i];
		break;
	}
	if (i >= NUM_OF_CYCLIC_HANDLER)
		errcode = SYSWRAP_ERR_RESOVER;

	return errcode;
}

SYSWRAP_ERROR syswrap_delete_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((cyclic_handler == NULL) || (cyclic_handler->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	cyclic_info_t *cyclic_info = (cyclic_info_t *)cyclic_handler->sysinfo;
	
	if (FALSE == cyclic_info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	ZERO_CLEAR(*cyclic_info);
	cyclic_handler->sysinfo = NULL;
	
	return errcode;
}


static SYSWRAP_ERROR active_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, bool active)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((cyclic_handler == NULL) || (cyclic_handler->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	cyclic_info_t *cyclic_info = (cyclic_info_t *)cyclic_handler->sysinfo;
	
	cyclic_info->active = active;
	cyclic_info->prevtime = syswrap_get_msec();

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


