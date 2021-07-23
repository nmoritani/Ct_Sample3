#include "win32wrapper_common.h"

#ifdef SYSTEM_WINDOWS

/* global */
thread_info_t thread_info_list[NUM_OF_THREAD] = {0};

static int conv_thread_priority(THREAD_PRIORITY pri)
{
	int win32_pri = 0;

	switch (pri) {
	case THREAD_PRI_LOWEST:
		win32_pri = THREAD_PRIORITY_LOWEST;
		break;
	case THREAD_PRI_NORMAL_LOW:
		win32_pri = THREAD_PRIORITY_BELOW_NORMAL;
		break;
	case THREAD_PRI_NORMAL:
		win32_pri = THREAD_PRIORITY_NORMAL;
		break;
	case THREAD_PRI_NORMAL_HIGH:
		win32_pri = THREAD_PRIORITY_ABOVE_NORMAL;
		break;
	case THREAD_PRI_HIGHEST:
		win32_pri = THREAD_PRIORITY_HIGHEST;
		break;
	default:
		win32_pri = THREAD_PRIORITY_NORMAL;
		break;
	}
	return win32_pri;
}

thread_info_t * get_current_thread_info()
{
	DWORD active_tid = GetCurrentThreadId();
	
	for (int i = 0; i < NUM_OF_THREAD; i++) {
		if ((thread_info_list[i].use == true) &&
			(thread_info_list[i].tid == active_tid)) {
			return &thread_info_list[i];
		}
	}
	
	return NULL;
}

static thread_info_t * addto_thread_queue(thread_info_t *thread, THREAD_ATTR attr, thread_info_t *queue)
{
	thread_info_t *tmp = NULL;

	if (queue == NULL)
		return thread;

	if (thread == NULL)
		return queue;
	
	if (attr == THREAD_ATTR_PRI) {
		tmp = queue;
		if (thread->priority > tmp->priority){
			thread->next = tmp;
			return thread;
		}
		
		while (tmp->next != NULL) {
			if (thread->priority > tmp->next->priority) {
				thread->next = tmp->next;
				break;
			}
			tmp = tmp->next;
		}
		tmp->next = thread;
		
	} else {
		tmp = queue;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = thread;
	}
	
	return queue;	
}

static thread_info_t * delete_thread_queue(thread_info_t *thread, thread_info_t *queue)
{
	thread_info_t *tmp = NULL;

	if (queue == NULL)
		return NULL;

	if (thread == NULL)
		return queue;

	tmp = queue;
	if (tmp == thread) {
		tmp = tmp->next;
		thread->next = NULL;
		return tmp;
	}

	while (tmp->next != NULL) {
		if (tmp->next == thread) {
			tmp->next = thread->next;
			thread->next = NULL;
			break;
		}
		tmp = tmp->next;
	}

	return queue;
}


SYSWRAP_ERROR syswrap_thread_init()
{
	ZERO_CLEAR(thread_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_thread_term()
{
	ZERO_CLEAR(thread_info_list);

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_thread(syswrap_thread_t *thread, FUNC func, unsigned int stack_size, THREAD_PRIORITY pri)
{
	thread_info_t *thread_info = NULL;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	int i;

	if ((thread == NULL) || (func == NULL))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(1);
	
	for (i = 0; i < NUM_OF_THREAD; i++) {
		if (thread_info_list[i].use)
			continue;
		
		thread_info = &thread_info_list[i];
		
		thread_info->use = true;
		thread_info->h_event = CreateEvent(NULL, FALSE, FALSE, NULL);
		thread_info->h_thread = 0;
		thread_info->state = THREAD_STATE_DORMANT;
		thread_info->tid = 0;
		thread_info->stack_size = stack_size;
		thread_info->priority = pri;
		thread_info->func = func;
		
		thread->sysinfo = thread_info;
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	unlock_common_mutex();
	
	if (i >= NUM_OF_THREAD)
		errcode = SYSWRAP_ERR_RESOVER;
	
	return errcode;
}


SYSWRAP_ERROR syswrap_destroy_thread(syswrap_thread_t *thread)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	
	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	lock_common_mutex(2);
	
	thread_info_t *thread_info = (thread_info_t *)thread->sysinfo;
	
	if (thread_info->state != THREAD_STATE_DORMANT) {
		return SYSWRAP_ERR_OBJ;
	}
	
	if (thread_info->h_thread != 0) {
		syswrap_term_thread(thread);
		CloseHandle(thread_info->h_thread);
		thread_info->h_thread = 0;
	}
	
	if (thread_info->h_event != 0) {
		CloseHandle(thread_info->h_event);
		thread_info->h_event = 0;
	}

	ZERO_CLEAR(*thread_info);
	thread->sysinfo = NULL;

	unlock_common_mutex();
		
	return errcode;
}


int syswrap_get_threadid(syswrap_thread_t *thread)
{
	thread_info_t * thread_info = NULL;
	int threadid = 0;
		
	lock_common_mutex(3);
	
	if (thread == NULL) {
		thread_info = get_current_thread_info();
		
		if (thread_info != NULL) {
			threadid = thread_info->tid;
		}
	} else {
		if ((thread_info = (thread_info_t *)thread->sysinfo) == NULL) {
			goto exit;
		}
		threadid =  thread_info->tid;
	}

  exit:
	unlock_common_mutex();
	return threadid;
}

static unsigned __stdcall user_task(void* arg)
{
	thread_info_t *thread_info = (thread_info_t *)arg;
	
	if (thread_info != NULL) {
		thread_info->state = THREAD_STATE_RUN;
		thread_info->func();
		thread_info->state = THREAD_STATE_DORMANT;
	}
	_endthreadex( 0 );
	return 0;
}

SYSWRAP_ERROR syswrap_start_thread(syswrap_thread_t *thread)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;
	
	lock_common_mutex(4);
	
	thread_info_t *thread_info = (thread_info_t *)thread->sysinfo;

	if (thread_info->h_thread != NULL) {
		DWORD ret;
		if (!GetExitCodeThread(thread_info->h_thread, &ret)) {
			errcode = SYSWRAP_ERR_SYS;
			goto exit;
		}

		CloseHandle(thread_info->h_thread);
		thread_info->h_thread = NULL;
	}

	thread_info->state = THREAD_STATE_READY;
	thread_info->h_thread = (HANDLE)_beginthreadex(NULL, 0, user_task, thread_info, CREATE_SUSPENDED, &(thread_info->tid));
	SetThreadPriority(thread_info->h_thread, conv_thread_priority(thread_info->priority));

	if (ResumeThread(thread_info->h_thread) < 0) {
		errcode = SYSWRAP_ERR_SYS;
		goto exit;
	}

  exit:
	unlock_common_mutex();
	return errcode;
}


THREAD_STATE syswrap_get_thread_state(syswrap_thread_t *thread)
{
	thread_info_t * thread_info = NULL;
	THREAD_STATE state = THREAD_STATE_ERROR;
		
	lock_common_mutex(5);
	
	if (thread == NULL) {
		if ((thread_info = get_current_thread_info()) == NULL)
			goto exit;
		
	} else {
		if ((thread_info = (thread_info_t *)thread->sysinfo) == NULL)
			goto exit;
		
	}
	state = thread_info->state;

  exit:
	unlock_common_mutex();
	return state;
}



SYSWRAP_ERROR syswrap_delay_thread(long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	
	lock_common_mutex(6);
	errcode = wait_thread(NULL, WAIT_TYPE_TIMEOUT, THREAD_ATTR_FIFO, timeout, NULL);
	unlock_common_mutex();

	return errcode;
}	
	
SYSWRAP_ERROR syswrap_term_thread(syswrap_thread_t *thread)
{
	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	thread_info_t *thread_info = (thread_info_t *)thread->sysinfo;

	if ((THREAD_STATE_SUSPEND <= thread_info->state) && (thread_info->state <= THREAD_STATE_RUN)) {
		TerminateThread(thread_info->h_thread, 0);
	}
	thread_info->state = THREAD_STATE_DORMANT;

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_wait_term_thread(syswrap_thread_t *thread, long timeout)
{
	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	thread_info_t *thread_info = (thread_info_t *)thread->sysinfo;
	long wait_time = 0;

	while (wait_time < timeout) {
		if (thread_info->state == THREAD_STATE_DORMANT)
			break;

		Sleep(1);
		wait_time++;
	}

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR wait_thread(thread_info_t *thread, WAIT_TYPE type, THREAD_ATTR attr, long timeout, thread_info_t **queue)
{
	DWORD			ret;
	SYSWRAP_ERROR	errcode = SYSWRAP_ERR_OK;
	thread_info_t * thread_info = NULL;

	if (timeout == SYSWRAP_TIMEOUT_POLLING)
		return SYSWRAP_ERR_TIMEOUT;
	
	if (thread == NULL) {
		thread_info = get_current_thread_info();
	} else {
		thread_info = thread;
	}

	thread_info->wait_type = type;
	thread_info->state = THREAD_STATE_WAIT;
	thread_info->next = NULL;
	if (queue != NULL) {
		*queue = addto_thread_queue(thread_info, attr, *queue);
	}

	unlock_common_mutex();
	ret = WaitForSingleObject(thread_info->h_event, timeout);
	lock_common_mutex(7);

	if (queue != NULL) {
		*queue = delete_thread_queue(thread_info, *queue);
	}

	thread_info->wait_type = WAIT_TYPE_NONE;
	thread_info->state = THREAD_STATE_RUN;
	thread_info->next = NULL;

	switch (ret) {
	case WAIT_OBJECT_0:	// OK!
		break;
	case WAIT_TIMEOUT:
		errcode = SYSWRAP_ERR_TIMEOUT;
		break;
	case WAIT_ABANDONED: //Mutex待ちでかつそのMutex削除されちゃった
	default:
		errcode = SYSWRAP_ERR_SYS;
		break;
	}

	return errcode;
}

SYSWRAP_ERROR wakeup_thread(thread_info_t *thread, WAIT_TYPE type, thread_info_t **queue)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	thread_info_t *thread_info = NULL;

	if (thread == NULL) {
		thread_info = get_current_thread_info();
	} else {
		thread_info = thread;
	}

	if (thread_info->h_event == 0) {
		errcode = SYSWRAP_ERR_NOEXS;
		goto exit;
	}
	
	if ((thread_info->wait_type == 0) || (thread_info->wait_type != type)) {
		errcode = SYSWRAP_ERR_OACV;
		goto exit;
	}
	
	if (thread_info->state == THREAD_STATE_DORMANT) {
		errcode = SYSWRAP_ERR_OBJ;
		goto exit;
	}

	if (SetEvent(thread_info->h_event) != TRUE) {
		errcode = SYSWRAP_ERR_SYS;
		goto exit;
	}

	if (queue != NULL) {
		*queue = delete_thread_queue(thread_info, *queue);
	}

	thread_info->wait_type = WAIT_TYPE_NONE;

  exit:
	return errcode;
}

#endif
