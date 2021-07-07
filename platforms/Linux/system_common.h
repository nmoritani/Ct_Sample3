/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: system_wrapper.h
 */

#ifndef __SYSTEM_COMMON_H__
#define __SYSTEM_COMMON_H__

#include <pthread.h>
#include "system_wrapper.h"

/* macro */
#define ARRAY_NUM(array) (sizeof(array) / sizeof(array[0]))
#define	ZERO_CLEAR(var)	 (memset(&(var), 0, sizeof(var)))

typedef struct _objlink {
	struct _objlink	*next;
	
} objlink_t;

typedef enum event_type {
	event_type_memorypool,
	event_type_flag,
	event_type_semaphore,
	event_type_mutex,
	event_type_message,
	event_type_timer,
} EVENT_TYPE;
	


extern int mutex_init(pthread_mutex_t *mutex);


#endif

