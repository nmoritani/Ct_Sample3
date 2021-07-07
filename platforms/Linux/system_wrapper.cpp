#include "system_wrapper.h"
#include "system_common.h"



void system_wrapper_initial()
{
	if (syswrap_common_initial() != SYSWRAP_ERR_OK) {
	}
	
	if (syswrap_thread_initial() != SYSWRAP_ERR_OK) {
	}
	
	if (syswrap_cyclic_handler_initial() != SYSWRAP_ERR_OK) {
	}
		
	if (syswrap_mutex_initial() != SYSWRAP_ERR_OK) {
	}
	
	if (syswrap_semaphore_initial() != SYSWRAP_ERR_OK) {
	}
	
	if (syswrap_message_initial() != SYSWRAP_ERR_OK) {
	}
	
	if (syswrap_event_initial() != SYSWRAP_ERR_OK) {
	}
	
	if (syswrap_memorypool_initial() != SYSWRAP_ERR_OK) {
	}
}


void system_wrapper_terminate()
{
}

