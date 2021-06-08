/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OS_WRAP_EXT_H__
#define __OS_WRAP_EXT_H__

/* currently only works for Linux/Unix */
#include <oswrapper/oswplatform.h>
#include <oswrapper/os_wrapper.h>

#if defined(__unix__)
#   include <sys/types.h>
#   include <sys/ipc.h>
#   include <sys/sem.h>
#   include <sys/shm.h>
#   include <signal.h>
#   include <unistd.h>
#	include <time.h>
#	include <sys/time.h>
/* for thread priority */
#	include <sched.h>
#elif defined(_WIN32)
#else
    #error "ext does not support this OS"
#endif /* OS depend */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* System V API only... not POSIX */
/* not correct at all but.. */
#if defined(__unix__)
    typedef key_t               OSW_key_t;
    typedef int                 OSW_signo_t;
#elif defined(_WIN32)
    typedef unsigned char *     OSW_key_t;
    typedef unsigned char *     OSW_signo_t;
#endif /* OS depend */

/***************************************************************************/
/* IPC Semaphore                                                           */
/* Currently only supports for system V. Since there is no named semaphore */
/***************************************************************************/
typedef struct {
#if defined(_WIN32)
    HANDLE                sem; 
#elif defined(__unix__)
    int                   sem; 
#endif /* OS depend */
} OSWRAP_IPCSEMAPHORE;

typedef struct {
#if defined(_WIN32)
    HANDLE                shm; 
#elif defined(__unix__)
    int                   shm; 
#endif /* OS depend */
} OSWRAP_SHM;

typedef struct {
#if defined(_WIN32)
    HANDLE                sig; 
#elif defined(__unix__)
    int                   sig; 
#else
    #error  "Not Supported OS!"
#endif /* OS depend */
} OSWRAP_SIGNAL;

/* IPC Semaphore */
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_IPCSemaphoreCreate( OSWRAP_IPCSEMAPHORE *semaphore, OSW_key_t key );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_IPCSemaphoreAttach( OSWRAP_IPCSEMAPHORE *semaphore, OSW_key_t key );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_IPCSemaphoreDelete( OSWRAP_IPCSEMAPHORE *semaphore );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_IPCSemaphoreSignal( OSWRAP_IPCSEMAPHORE *semaphore );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_IPCSemaphoreWaitBlocked( OSWRAP_IPCSEMAPHORE *semaphore );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_IPCSemaphoreWaitUnblocked( OSWRAP_IPCSEMAPHORE *semaphore );


/* IPC Shared Mem */
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ShmCreate( OSWRAP_SHM *shm, OSW_key_t key, OSW_int32_t size );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ShmAttach( OSWRAP_SHM *shm, OSW_key_t key );
extern OSW_API void* OSW_APIENTRY OsWrap_ShmMap( OSWRAP_SHM *shm, int addr );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ShmUnmap( const void *shmaddr);
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ShmDelete( OSWRAP_SHM *shm );

/* IPC Signal */
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SignalCreate( OSWRAP_SIGNAL* sig, OSW_signo_t signo );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SignalSend(OSWRAP_SIGNAL* sig, OSW_signo_t signo, OSWRAP_PROCESS_ID pid );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SignalWaitBlocked( OSWRAP_SIGNAL* sig );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SignalCheckAndRebuild( OSWRAP_SIGNAL* sig );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SignalDelete( OSWRAP_SIGNAL* sig );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SignalCreateWithHandle( void* handler, OSW_signo_t signo );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SignalSendWithHandle( OSWRAP_PROCESS_ID pid, OSW_signo_t signo );
/* Thread priority - since this priority parameter is very different from other OS.
 */
/* It only works on sched RR */
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SetThreadPriorityHighest( OSWRAP_THREAD* thread );
/* EXIT func */
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SetAtExitFunc( void* func );

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* __OS_WRAP_EXT_H__ */
