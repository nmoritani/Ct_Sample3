#include "win32wrapper_common.h"

#ifdef SYSTEM_WINDOWS

typedef struct {
	BOOL            use;
	THREAD_ATTR		thread_attribute;
	thread_info_t	*thread_queue;

	unsigned int	event_value;
	
} event_info_t;

/* global */
event_info_t	event_info_list[NUM_OF_EVENTFLAG] = {0};



SYSWRAP_ERROR syswrap_event_init()
{
	ZERO_CLEAR(event_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_event_term()
{
	ZERO_CLEAR(event_info_list);

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_event(syswrap_event_t *event, THREAD_ATTR thread_attribute, unsigned int init_value)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;

	if (event == NULL)
		return SYSWRAP_ERR_PAR;
	
	lock_common_mutex(21);
	
	for (int i = 0; i < NUM_OF_EVENTFLAG; i++) {
		if (event_info_list[i].use == TRUE)
			continue;

		event_info_list[i].use = TRUE;
		event_info_list[i].thread_attribute = thread_attribute;
		event_info_list[i].event_value = init_value;

		event->sysinfo = &event_info_list[i];
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	unlock_common_mutex();
	
	return errcode;
}


SYSWRAP_ERROR syswrap_destroy_event(syswrap_event_t *event)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((event == NULL) || (event->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(22);
	
	event_info_t *event_info = (event_info_t *)event->sysinfo;
	
	if (false == event_info->use)
		errcode = SYSWRAP_ERR_PAR;
	
	ZERO_CLEAR(*event_info);
	event->sysinfo = NULL;

	unlock_common_mutex();
	
	return errcode;
}


SYSWRAP_ERROR syswrap_set_event(syswrap_event_t *event, unsigned int set_pattern)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	thread_info_t *thread_info, *next_thread_info;
	BOOL event_on = FALSE;
	unsigned int wait_pattern, wait_fmode;
	
	if ((event == NULL) || (event->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	if (set_pattern == 0)
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(23);
	
	event_info_t *event_info = (event_info_t *)event->sysinfo;

	event_info->event_value |= set_pattern;

	thread_info = event_info->thread_queue;

	while (thread_info != NULL) {
		event_on = FALSE;
		wait_pattern = thread_info->param[0];
		wait_fmode = thread_info->param[1];

		if (wait_fmode & SYSWRAP_WAITFMODE_ORW) {
			if (wait_pattern & event_info->event_value) {
				event_on = TRUE;
			}
		} else {
			if ((wait_pattern & event_info->event_value) == wait_pattern) {
				event_on = TRUE;
			}
		}
		next_thread_info = thread_info->next;

		if (event_on == TRUE) {
			thread_info->param[2] = event_info->event_value;

			if (wait_fmode & SYSWRAP_WAITFMODE_CLEAR) {
				event_info->event_value = 0;
			}
			wakeup_thread(thread_info, WAIT_TYPE_EVENT, &event_info->thread_queue);
		}
		thread_info = next_thread_info;
	}
	
	unlock_common_mutex();

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_wait_event(syswrap_event_t *event, unsigned int wait_pattern, unsigned int wait_fmode, unsigned int *flag_pattern, long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_PAR;
	BOOL event_on = FALSE;

	if ((event == NULL) || (event->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	if ((flag_pattern == NULL) || (wait_pattern == 0))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(24);
	
	event_info_t *event_info = (event_info_t *)event->sysinfo;

	*flag_pattern = 0;
	if (wait_fmode & SYSWRAP_WAITFMODE_ORW) {
		if (wait_pattern & event_info->event_value) {
			event_on = TRUE;
		}
	} else {
		if ((wait_pattern & event_info->event_value) == wait_pattern) {
			event_on = TRUE;
		}
	}

	if (event_on == TRUE) {
		*flag_pattern = event_info->event_value;

		if (wait_fmode & SYSWRAP_WAITFMODE_CLEAR) {
			event_info->event_value = 0;
		}
		errcode =  SYSWRAP_ERR_OK;
		goto exit;
	}

	thread_info_t *thread_info = NULL;

	if ((thread_info = get_current_thread_info()) == NULL) {
		errcode = SYSWRAP_ERR_CTX;
		goto exit;
	}

	thread_info->param[0] = wait_pattern;
	thread_info->param[1] = wait_fmode;
	thread_info->param[2] = 0;

	if ((errcode = wait_thread(thread_info, WAIT_TYPE_EVENT, event_info->thread_attribute, timeout, &event_info->thread_queue)) == SYSWRAP_ERR_OK) {
		*flag_pattern = thread_info->param[2];
	}

  exit:
	unlock_common_mutex();
	
	return errcode;
}


SYSWRAP_ERROR syswrap_clear_event(syswrap_event_t *event, unsigned int clrptn)
{
	if ((event == NULL) || (event->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(25);
	
	event_info_t *info = (event_info_t *)event->sysinfo;
	
	info->event_value &= clrptn;

	unlock_common_mutex();
	
	return SYSWRAP_ERR_OK;
}

#endif
