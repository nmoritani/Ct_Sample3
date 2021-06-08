/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_PLATFORM_H__
#define __OSW_PLATFORM_H__

#include <uitronw/itron.h>


#ifdef __cplusplus
extern "C" {
#endif


#if defined(__ANDROID__) || defined(ANDROID)
#	ifndef	__unix__
#		define	__unix__
#	endif
#endif


#if defined(_NO_OS_)
	/* There is no os */

#elif defined(__SKELETON_OS__)
	/* skeleton os */

#elif defined(_WIN32)

#   include <windows.h>

#elif defined(__unix__)

#   include <pthread.h>
#   include <semaphore.h>

#elif defined(USE_ITRON4)

#   include "itron.h"
#   include "kernel.h"

#endif /* OS depend */


#ifndef OSW_API
#if defined(OSW_STATIC_LIBRARY)
#	define OSW_API
#else
#	if defined(_WIN32) || defined(__VC32__)
#		ifdef OSW_DLL_EXPORTS
#			define OSW_API __declspec(dllexport)
#		else /* OSW_DLL_EXPORTS */
#			define OSW_API __declspec(dllimport)
#		endif /* OSW_DLL_EXPORTS */
#	else
#		define OSW_API
#	endif
#endif /* OSW_STATIC_LIBRARY */
#endif /* OSW_API */

#ifndef OSW_APIENTRY
#	define OSW_APIENTRY
#endif /* OSW_APIENTRY */


/* ------------------------------------------------------------------------ */
/*  Little or big endian machine?                                           */
/* ------------------------------------------------------------------------ */

#if defined( i386 ) || defined(_WIN32) || defined(__arm__) || defined(__SKELETON_OS__)
#   define OSW_LITTLE_ENDIAN    1
#elif defined( __ppc__ ) || defined( sparc ) || defined( __hppa )
#   define OSW_BIG_ENDIAN       1
#endif


#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)

/*
 * Using <stdint.h>
 */
#include <stdint.h>
typedef int32_t                 OSW_int32_t;
typedef uint32_t                OSW_uint32_t;
typedef int64_t                 OSW_int64_t;
typedef uint64_t                OSW_uint64_t;
#define OSW_SUPPORT_INT64       1

#elif defined(__SKELETON_OS__)
typedef int                     OSW_int32_t;
typedef unsigned int            OSW_uint32_t;
#define OSW_SUPPORT_INT64       0

#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)

/*
 * Win32
 */
typedef __int32                 OSW_int32_t;
typedef unsigned __int32        OSW_uint32_t;
typedef __int64                 OSW_int64_t;
typedef unsigned __int64        OSW_uint64_t;
#define OSW_SUPPORT_INT64       1

#elif defined (__CC103__)
typedef int                     OSW_int32_t;
typedef unsigned int            OSW_uint32_t;
#define OSW_SUPPORT_INT64       0


#else

/*
 * Generic fallback
 */
#include <stdint.h>
typedef int32_t                 OSW_int32_t;
typedef uint32_t                OSW_uint32_t;
typedef int64_t                 OSW_int64_t;
typedef uint64_t                OSW_uint64_t;
#define OSW_SUPPORT_INT64       1

#endif


typedef struct {

#ifdef OSW_BIG_ENDIAN
    int             hi;
    unsigned int    lo;
#else
    unsigned int    lo;
    int             hi;
#endif

} OSW_INT64_T;


typedef struct {

#ifdef OSW_BIG_ENDIAN
    unsigned int    hi;
    unsigned int    lo;
#else
    unsigned int    lo;
    unsigned int    hi;
#endif

} OSW_UINT64_T;


/****************************************************************************/
/* Mutex                                                                    */
/****************************************************************************/
typedef struct {
#if defined(_NO_OS_)
    void*			         mtxid;
#elif defined(__SKELETON_OS__)
	ID						 mtxid;
#elif defined(USE_T_KERNEL) || defined(__CC103__)
    ID                       mtxid;
#elif defined(_WIN32)
    CRITICAL_SECTION         mtxid;
#elif defined(__unix__)
    pthread_mutex_t          mutex_t;
#else
    void*			         mtxid;
#endif /* OS depend */
} OSWRAP_MUTEX;

/****************************************************************************/
/* Semaphore                                                                */
/****************************************************************************/
typedef struct {
#if defined(_NO_OS_)
    void*		             semid;
#elif defined(__SKELETON_OS__)
	ID						 semid;
#elif defined(USE_T_KERNEL) || defined(__CC103__)
    ID                       semid;
#elif defined(_WIN32)
    unsigned int             semid;
#elif defined(__unix__)
    sem_t                   *semid;
#else
    void*		             semid;
#endif /* OS depend */
} OSWRAP_SEMAPHORE;

/****************************************************************************/
/* Event                                                                    */
/****************************************************************************/
#if defined(_NO_OS_)

#elif defined(USE_T_KERNEL)
#define OSWRAP_EVENT_TWF_ANDW       TWF_ANDW
#define OSWRAP_EVENT_TWF_ORW        TWF_ORW
#define OSWRAP_EVENT_TWF_CLR        TWF_CLR
#define OSWRAP_EVENT_TWF_BITCLR     TWF_BITCLR
#define OSWRAP_EVENT_TIMER_POL      (unsigned int)TMO_POL
#define OSWRAP_EVENT_TIMER_FEVR     (unsigned int)TMO_FEVR
#elif defined(__CC103__)
#define OSWRAP_EVENT_TWF_ANDW       TWF_ANDW
#define OSWRAP_EVENT_TWF_ORW        TWF_ORW
#define OSWRAP_EVENT_TWF_CLR        0
#define OSWRAP_EVENT_TWF_BITCLR     0
#define OSWRAP_EVENT_TIMER_POL      (unsigned int)TMO_POL
#define OSWRAP_EVENT_TIMER_FEVR     (unsigned int)TMO_FEVR
#elif defined(_WIN32)
#define OSWRAP_EVENT_TWF_ANDW       0x00
#define OSWRAP_EVENT_TWF_ORW        0x01
#define OSWRAP_EVENT_TWF_CLR        0x10
#define OSWRAP_EVENT_TWF_BITCLR     0x20
#define OSWRAP_EVENT_TIMER_POL      (unsigned int)0
#define OSWRAP_EVENT_TIMER_FEVR     (unsigned int)INFINITE
#elif defined(__unix__)
#define OSWRAP_EVENT_TWF_ANDW       0x00
#define OSWRAP_EVENT_TWF_ORW        0x01
#define OSWRAP_EVENT_TWF_CLR        0x10
#define OSWRAP_EVENT_TWF_BITCLR     0x20
#define OSWRAP_EVENT_TIMER_POL      (unsigned int)0
#define OSWRAP_EVENT_TIMER_FEVR     (unsigned int)-1
#else
#define OSWRAP_EVENT_TWF_ANDW       0x00
#define OSWRAP_EVENT_TWF_ORW        0x01
#define OSWRAP_EVENT_TWF_CLR        0x10
#define OSWRAP_EVENT_TWF_BITCLR     0x20
#define OSWRAP_EVENT_TIMER_POL      (unsigned int)0
#define OSWRAP_EVENT_TIMER_FEVR     (unsigned int)-1
#endif /* OS depend */

typedef struct {
#if defined(_NO_OS_)
    void*		             flgid;
#elif defined(__SKELETON_OS__)
    void*		             flgid;
#elif defined(USE_T_KERNEL) || defined(__CC103__)
    ID                       flgid;
#elif defined(_WIN32)
    unsigned int             flgid;
#elif defined(__unix__)
    unsigned int             flgid;
#else
    void*		             flgid;
#endif /* OS depend */
} OSWRAP_EVENT;

/****************************************************************************/
/* Message                                                                  */
/****************************************************************************/
#if defined(_NO_OS_)

#elif defined(USE_T_KERNEL) || defined(__CC103__)
#define OSWRAP_MESSAGE_TIMER_POL    (unsigned int)TMO_POL
#define OSWRAP_MESSAGE_TIMER_FEVR   (unsigned int)TMO_FEVR
#elif defined(_WIN32)
#define OSWRAP_MESSAGE_TIMER_POL    (unsigned int)0
#define OSWRAP_MESSAGE_TIMER_FEVR   (unsigned int)INFINITE
#elif defined(__unix__)
#define OSWRAP_MESSAGE_TIMER_POL    (unsigned int)0
#define OSWRAP_MESSAGE_TIMER_FEVR   (unsigned int)-1
#else
#define OSWRAP_MESSAGE_TIMER_POL    (unsigned int)0
#define OSWRAP_MESSAGE_TIMER_FEVR   (unsigned int)-1
#endif /* OS depend */

typedef struct {
#if defined(_NO_OS_)
    void*		             mbfid;
#elif defined(__SKELETON_OS__)
    void*		             mbfid;
#elif defined(USE_T_KERNEL) || defined(__CC103__)
    ID                       mbfid;
#elif defined(_WIN32)
    unsigned int             mbfid;
#elif defined(__unix__)
    unsigned int             mbfid;
#else
    void*		             mbfid;
#endif /* OS depend */
} OSWRAP_MESSAGE;

/****************************************************************************/
/* ProcessID                                                                */
/****************************************************************************/
typedef void *OSWRAP_PROCESS_ID;

/****************************************************************************/
/* Time                                                                     */
/****************************************************************************/

/****************************************************************************/
/* Thread                                                                   */
/****************************************************************************/
typedef void *OSWRAP_THREAD_ID;

typedef struct {
    OSWRAP_THREAD_ID         tid;
#if defined(_NO_OS_)

#elif defined(__SKELETON_OS__)
	ER						 err;
#elif defined(USE_T_KERNEL) || defined(__CC103__)
    ER                       ercd;
#elif defined(_WIN32)
    HANDLE                   handle;
    DWORD                    err;
#elif defined(__unix__)
    int                      err;
#endif /* OS depend */
} OSWRAP_THREAD;

/****************************************************************************/
/* PerformanceCounter                                                       */
/****************************************************************************/

/****************************************************************************/
/* Buffer                                                                   */
/****************************************************************************/

/****************************************************************************/
/* Memory                                                                   */
/****************************************************************************/

/****************************************************************************/
/* Common                                                                   */
/****************************************************************************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __OSW_PLATFORM_H__ */
