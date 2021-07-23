#include "win32wrapper_common.h"

#ifdef SYSTEM_WINDOWS

static HANDLE h_common_mutex = NULL;

SYSWRAP_ERROR syswrap_common_init()
{
	h_common_mutex = CreateMutex(NULL, FALSE, NULL);
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_common_term()
{
	if (h_common_mutex != NULL) {
		CloseHandle(h_common_mutex);
		h_common_mutex = NULL;
	}
	return SYSWRAP_ERR_OK;
}

void lock_common_mutex(int locker)
{
	if (h_common_mutex != NULL) {
		WaitForSingleObject(h_common_mutex, INFINITE);
	}
}

void unlock_common_mutex()
{
	if (h_common_mutex != NULL) {
		ReleaseMutex(h_common_mutex);
	}
}


HANDLE create_mutex()
{
	return CreateMutex(NULL, FALSE, NULL);
}

void destroy_mutex(HANDLE *h_mutex)
{
	if (h_mutex != NULL) {
		CloseHandle(*h_mutex);
		h_mutex = NULL;
	}
}

void lock_mutex(HANDLE h_mutex, long timeout)
{
	if (h_mutex != NULL) {
		WaitForSingleObject(h_mutex, timeout);
	}
}

void unlock_mutex(HANDLE h_mutex)
{
	if (h_mutex != NULL) {
		ReleaseMutex(h_mutex);
	}
}

void system_wrapper_init()
{
	syswrap_common_init();
	syswrap_cyclic_handler_init();
	syswrap_thread_init();
	syswrap_memorypool_init();
	
	syswrap_mutex_init();
	syswrap_semaphore_init();
	syswrap_message_init();
	syswrap_event_init();
}


void system_wrapper_term()
{
	syswrap_event_term();
	syswrap_message_term();
	syswrap_semaphore_term();
	syswrap_mutex_term();
	
	syswrap_memorypool_term();
	syswrap_thread_term();
	syswrap_cyclic_handler_term();
	syswrap_common_term();
}

#include "CtPlatforms.h"
#include "CtMainThread.h"
#include "CtDrawThread.h"
#include "CtDbgThread.h"

syswrap_cyclic_handler_t ct_cyclic_handler;

syswrap_memorypool_t ct_mempool_normal;
syswrap_memorypool_t ct_mempool_fast;

CtMainThread *ct_main = NULL;
CtDrawThread *ct_draw = NULL;
CtDbgThread *ct_dbg = NULL;

void Ct_Init()
{
	system_wrapper_init();

	syswrap_create_memorypool(&ct_mempool_normal, 2*1024*1024, 0, NULL);
	syswrap_create_memorypool(&ct_mempool_fast, 512*1024, 0, NULL);
	
	ct_main = CtMainThread::getInstance();
	ct_draw = CtDrawThread::getInstance();
	ct_dbg = CtDbgThread::getInstance();
	
	//	syswrap_create_cyclic_handler(&ct_cyclic_handler, CtCycHandler, 10);
}


void Ct_Term()
{
	if (ct_dbg != NULL)
		delete ct_dbg;
	
	if (ct_draw != NULL)
		delete ct_draw;
	
	if (ct_main != NULL)
		delete ct_main;

	syswrap_destroy_memorypool(&ct_mempool_fast);
	syswrap_destroy_memorypool(&ct_mempool_normal);
	
	system_wrapper_term();
}

#endif
