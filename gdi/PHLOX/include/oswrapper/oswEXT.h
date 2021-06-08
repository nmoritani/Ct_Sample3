/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_EXT_H__
#define __OSW_EXT_H__

#include <oswrapper/oswplatform.h>
#include <oswrapper/os_wrapper.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#if defined(__unix__)
#	include <pthread.h>
#elif defined(_WIN32)
#	include <windows.h>
#else
//#	error "oswEXT does not support this OS"
#endif


#define OSW_EXT_VERSION_2_0 1
#define OSW_EXT_VERSION_1_0 1


#ifndef OSW_EXT_thread_mutex
#define OSW_EXT_thread_mutex 1

#if defined(__unix__)
typedef	pthread_mutex_t			OSW_THREAD_MUTEX_EXT;
typedef	pthread_mutexattr_t		OSW_THREAD_MUTEXATTR_EXT;
#elif defined(_WIN32)
typedef struct {
    CRITICAL_SECTION                 hmutex;
} OSW_THREAD_MUTEX_EXT;
typedef	void*					OSW_THREAD_MUTEXATTR_EXT;
#else
typedef	void*					OSW_THREAD_MUTEX_EXT;
typedef	void*					OSW_THREAD_MUTEXATTR_EXT;
#endif /* OS depend */

extern OSW_API OSW_THREAD_MUTEX_EXT *OSW_APIENTRY OsWrap_ThreadMutexCreateEXT( const OSW_THREAD_MUTEXATTR_EXT *attr );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadMutexDestroyEXT( OSW_THREAD_MUTEX_EXT *mutex );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadMutexLockEXT( OSW_THREAD_MUTEX_EXT *mutex );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadMutexUnlockEXT( OSW_THREAD_MUTEX_EXT *mutex );

#endif	/* OSW_EXT_thread_mutex */


#ifndef OSW_EXT_thread_cond
#define OSW_EXT_thread_cond 1

#if defined(__unix__)
typedef	pthread_cond_t			OSW_THREAD_COND_EXT;
typedef	pthread_condattr_t		OSW_THREAD_CONDATTR_EXT;
#elif defined(_WIN32)
typedef struct _OSW_THREAD_COND_OBJ {
    HANDLE                      hevent;
    struct _OSW_THREAD_COND_OBJ	*prev_ptr;
    struct _OSW_THREAD_COND_OBJ *next_ptr;
} OSW_THREAD_COND_OBJ;

typedef struct {
    HANDLE                      hevent_broadcast;
    OSW_THREAD_COND_OBJ         *start_ptr;
    OSW_THREAD_COND_OBJ         *tail_ptr;
} OSW_THREAD_COND_EXT;
typedef	void*					OSW_THREAD_CONDATTR_EXT;
#else
typedef	void*					OSW_THREAD_COND_EXT;
typedef	void*					OSW_THREAD_CONDATTR_EXT;
#endif /* OS depend */

extern OSW_API OSW_THREAD_COND_EXT *OSW_APIENTRY OsWrap_ThreadCondCreateEXT( const OSW_THREAD_CONDATTR_EXT *attr );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadCondDestroyEXT( OSW_THREAD_COND_EXT *cond );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadCondSignalEXT( OSW_THREAD_COND_EXT *cond );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadCondBroadcastEXT( OSW_THREAD_COND_EXT *cond );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadCondWaitEXT( OSW_THREAD_COND_EXT *cond, OSW_THREAD_MUTEX_EXT *mutex );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadCondTimedwaitEXT( OSW_THREAD_COND_EXT *cond, OSW_THREAD_MUTEX_EXT *mutex, const OSW_UINT64_T *timeout );

#endif	/* OSW_EXT_thread_cond */


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __OSW_EXT_H__ */
