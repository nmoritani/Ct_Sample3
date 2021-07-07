/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: system_wrapper.h
 */

#ifndef __SYSTEM_COMMON_H__
#define __SYSTEM_COMMON_H__

#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>

#include "../system_wrapper.h"

/* macro */
#define ARRAY_NUM(array) (sizeof(array) / sizeof(array[0]))
#define	ZERO_CLEAR(var)	 (memset(&(var), 0, sizeof(var)))

extern void common_mutex_lock();
extern void common_mutex_unlock();

typedef enum {
	THREAD_STATE_DORMANT = 0,	// 休止中
	THREAD_STATE_SUSPEND,		// 強制待ち状態
	THREAD_STATE_WAIT,			// 待ち状態
	THREAD_STATE_READY,			// 実行可能状態
	THREAD_STATE_RUN,			// 実行状態
	THREAD_STATE_MAX
} THREAD_STATE;

typedef enum {
	WAIT_TYPE_NONE,
	WAIT_TYPE_SEMAPHORE,
	WAIT_TYPE_MUTEX,
	WAIT_TYPE_THREAD,
	WAIT_TYPE_EVENT,
	WAIT_TYPE_MESSAGE,
	WAIT_TYPE_TIMEOUT
} WAIT_TYPE;

typedef struct _thread_info {
	struct _thread_info	*next;
	bool            use;
	int				priority;
	THREAD_STATE	state;
	int				stack_size;
	THREAD_FUNC		*func;
	void			*extinfo;
	WAIT_TYPE		wait_type;
	unsigned int	param[5];
	
	HANDLE			h_event;
	HANDLE			h_thread;
	unsigned int	tid;
} thread_info_t;

extern thread_info_t * get_current_thread();
extern SYSWRAP_ERROR wait_thread(thread_info_t *pthread, WAIT_TYPE type, THREAD_ATTR attr, long timeout, thread_info_t **queue);
extern SYSWRAP_ERROR wakeup_thread(thread_info_t *pthread, WAIT_TYPE type, thread_info_t **queue);

extern HANDLE create_mutex();
extern void delete_mutex(HANDLE mutex);
extern void lock_mutex(HANDLE mutex);
extern void unlock_mutex(HANDLE mutex);


#endif

