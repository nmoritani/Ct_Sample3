#include "system_common.h"

/* global */
HANDLE				h_mutex;
thread_info_t		info_list[NUM_OF_THREAD];

thread_info_t * get_current_thread()
{
	DWORD active_tid = GetCurrentThreadId();
	
	for (int i = 0; i < NUM_OF_THREAD; i++) {
		if ((info_list[i].use == true) &&
			(info_list[i].tid == active_tid)) {
			return &info_list[i];
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


SYSWRAP_ERROR syswrap_thread_initial()
{
	h_mutex = create_mutex();

	ZERO_CLEAR(info_list);

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_thread(syswrap_thread_t *thread, THREAD_FUNC func, void *extinfo, unsigned int stack_size, int pri)
{
	thread_info_t *thread_info = NULL;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	int i;

	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	lock_mutex(h_mutex);

	for (i = 0; i < NUM_OF_THREAD; i++) {
		if (info_list[i].use)
			continue;
		
		thread_info = &info_list[i];
		
		thread_info->use = true;
		thread_info->h_event = CreateEvent(NULL, FALSE, FALSE, NULL);
		thread_info->h_thread = 0;
		thread_info->state = THREAD_STATE_DORMANT;
		thread_info->tid = 0;
		thread_info->stack_size = stack_size;
		thread_info->priority = pri;
		thread_info->func = func;
		thread_info->extinfo = extinfo;
		
		thread->sysinfo = thread_info;
		errcode = SYSWRAP_ERR_OK;
	}
	
	if (i >= NUM_OF_THREAD)
		errcode = SYSWRAP_ERR_RESOVER;
	
	unlock_mutex(h_mutex);
	return errcode;
}


SYSWRAP_ERROR syswrap_destroy_thread(syswrap_thread_t *thread)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	
	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	lock_mutex(h_mutex);
	
	thread_info_t *thread_info = (thread_info_t *)thread->sysinfo;
	
	if (thread_info->state != THREAD_STATE_DORMANT) {
		return SYSWRAP_ERR_OBJ;
	}
	
	if (thread_info->h_thread != 0) {
		syswrap_stop_thread(thread, 10);
		CloseHandle(thread_info->h_thread);
		thread_info->h_thread = 0;
	}
	
	if (thread_info->h_event != 0) {
		CloseHandle(thread_info->h_event);
		thread_info->h_event = 0;
	}

	ZERO_CLEAR(thread_info);
	thread->sysinfo = NULL;
		
	unlock_mutex(h_mutex);
	
	return errcode;
}


SYSWRAP_ERROR syswrap_get_threadid(int *tid)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	thread_info_t * thread = get_current_thread();
	
	if (thread != NULL) {
		*tid = thread->tid;
	} else {
		*tid = 0;
		errcode = SYSWRAP_ERR_RESOVER;
	}
	
	return errcode;
}

static unsigned __stdcall user_task(void* arg)
{
	thread_info_t *thread_info = (thread_info_t *)arg;
	
	if (thread_info != NULL) {
		thread_info->state = THREAD_STATE_RUN;
		thread_info->func(thread_info->extinfo);
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
	
	thread_info_t *thread_info = (thread_info_t *)thread->sysinfo;

	if (thread_info->h_thread != NULL) {
		DWORD ret;
		if (!GetExitCodeThread(thread_info->h_thread, &ret))
			return SYSWRAP_ERR_SYS;

		CloseHandle(thread_info->h_thread);
		thread_info->h_thread = NULL;
	}

	thread_info->state = THREAD_STATE_READY;
	thread_info->h_thread = (HANDLE)_beginthreadex(NULL, 0, user_task, thread_info, CREATE_SUSPENDED, &(thread_info->tid));
	SetThreadPriority(thread_info->h_thread, thread_info->priority);

	if (ResumeThread(thread_info->h_thread) < 0)
		return SYSWRAP_ERR_SYS;
	
	return errcode;
}


SYSWRAP_ERROR syswrap_delay_thread(long timeout)
{
	return wait_thread(NULL, WAIT_TYPE_TIMEOUT, THREAD_ATTR_FIFO, timeout, NULL);
}	
	
SYSWRAP_ERROR syswrap_stop_thread(syswrap_thread_t *thread, long timeout)
{
	if ((thread == NULL) || (thread->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	thread_info_t *thread_info = (thread_info_t *)thread->sysinfo;
	
	HANDLE hThread = thread_info->h_thread;

	for (int i = 0; i < (timeout/10)+1; i++) {
		DWORD code;
		if (!GetExitCodeThread(hThread, &code)) {
			TerminateThread(hThread, 0);
			return SYSWRAP_ERR_OK;
		}
		if (code != STILL_ACTIVE) {
			return SYSWRAP_ERR_OK;
		}
		Sleep(10);
	}
	TerminateThread(hThread, 0);

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR wait_thread(thread_info_t *thread, WAIT_TYPE type, THREAD_ATTR attr, long timeout, thread_info_t **queue)
{
	DWORD			ret;
	SYSWRAP_ERROR	errcode = SYSWRAP_ERR_OK;
	thread_info_t * thread_info = NULL;

	if (thread == NULL) {
		thread_info = get_current_thread();
	} else {
		thread_info = thread;
	}

	thread_info->wait_type = type;
	thread_info->state = THREAD_STATE_WAIT;
	thread_info->next = NULL;
	if (queue != NULL) {
		*queue = addto_thread_queue(thread_info, attr, *queue);
	}

	ret = WaitForSingleObject(thread_info->h_event, timeout);

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
	thread_info_t *thread_info = NULL;
	
	if (thread == NULL) {
		thread_info = get_current_thread();
	} else {
		thread_info = thread;
	}

	if (thread_info->h_event == 0)
		return SYSWRAP_ERR_NOEXS;
	
	if ((thread_info->wait_type == 0) || (thread_info->wait_type != type))
		return SYSWRAP_ERR_OACV;
	
	if (thread_info->state == THREAD_STATE_DORMANT)
		return SYSWRAP_ERR_OBJ;
	
	if (SetEvent(thread_info->h_event) != TRUE)
		return SYSWRAP_ERR_SYS;

	if (queue != NULL) {
		*queue = delete_thread_queue(thread_info, *queue);
	}

	thread_info->wait_type = WAIT_TYPE_NONE;
	
	return SYSWRAP_ERR_OK;
}
