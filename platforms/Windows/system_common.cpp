#include "system_common.h"

static HANDLE h_common_mutex = NULL;


SYSWRAP_ERROR syswrap_common_initial()
{
	h_common_mutex = CreateMutex(NULL, FALSE, NULL);
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_common_terminate()
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

