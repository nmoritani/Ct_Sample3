#include "itronwrapper_common.h"

#ifdef SYSTEM_ITRON

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

void lock_common_mutex()
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

void lock_mutex(HANDLE h_mutex)
{
	if (h_mutex != NULL) {
		WaitForSingleObject(h_mutex, INFINITE);
	}
}

void unlock_mutex(HANDLE h_mutex)
{
	if (h_mutex != NULL) {
		ReleaseMutex(h_mutex);
	}
}

#include "CtMainThread.h"
#include "CtDrawThread.h"
#include "CtDbgThread.h"

#ifdef __cplusplus
extern "C" {
#endif
extern BOOL ITRON_Init();
extern void ITRON_Quit();
#ifdef __cplusplus
}
#endif

syswrap_cyclic_handler_t ct_cyclic_handler;

syswrap_memorypool_t ct_mempool_normal;
syswrap_memorypool_t ct_mempool_fast;

CtMainThread *ct_main = NULL;
CtDrawThread *ct_draw = NULL;
CtDbgThread *ct_dbg = NULL;

void Ct_Init()
{
	//	system_wrapper_init();

	ITRON_Init();
	
	ct_mempool_normal.id = CT_MPLID_NORMAL;
	syswrap_create_memorypool(&ct_mempool_normal, 2*1024*1024, 0, NULL);
							   
	ct_mempool_fast.id = CT_MPLID_FAST;
	syswrap_create_memorypool(&ct_mempool_fast, 512*1024, 0, NULL);
	
	ct_main = CtMainThread::getInstance();
	ct_draw = CtDrawThread::getInstance();
	ct_dbg = CtDbgThread::getInstance();
	
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
	
	ITRON_Quit();
	//	system_wrapper_term();
}

#endif
