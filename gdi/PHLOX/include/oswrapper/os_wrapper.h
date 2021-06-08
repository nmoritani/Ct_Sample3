/*
  Copyright (c) 2011-2012, Digital Media Professionals. All rights reserved.
*/
#ifndef __OS_WRAPPER_H__
#define __OS_WRAPPER_H__

#include <oswrapper/oswplatform.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define OSW_VERSION_1_0 1

/* Åö NULLÇÃêÈåæÇí«â¡ */
#define NULL ((void*)0)


/****************************************************************************/
/* Error                                                                    */
/****************************************************************************/
typedef enum {
    OSWRAP_SUCCESS			= 0,
    OSWRAP_BAD_ACCESS,
    OSWRAP_BAD_ALLOC,
    OSWRAP_BAD_PARAMETER,
    OSWRAP_TIMEOUT,
    OSWRAP_INTR,
    OSWRAP_ALREADY_EXISTS
} OSWrapError;

/****************************************************************************/
/* Mutex                                                                    */
/****************************************************************************/

/****************************************************************************/
/* Semaphore                                                                */
/****************************************************************************/
#define OSWRAP_SEMAPHORE_NAME       "DMP_OSW_SEMAPHORE"

/****************************************************************************/
/* Event                                                                    */
/****************************************************************************/
#define OSWRAP_EVENT_NAME           "DMP_OSW_EVENT"

typedef struct {
    unsigned int             flgptn;
    unsigned int             waiptn;
    unsigned int             wfmode;
    unsigned int            *pflgptn;
    unsigned int             timerval;
} OSWRAP_EVENT_PARAM;

/****************************************************************************/
/* Message                                                                  */
/****************************************************************************/
#define OSWRAP_MESSAGE_NAME         "DMP_OSW_MESSAGE"

typedef struct {
    void                    *msg;
    unsigned int             timerval;
    unsigned int             message_max;
} OSWRAP_MESSAGE_PARAM;

/****************************************************************************/
/* ProcessID                                                                */
/****************************************************************************/

/****************************************************************************/
/* Time                                                                     */
/****************************************************************************/


/****************************************************************************/
/* Thread                                                                   */
/****************************************************************************/
#define OSWRAP_THREAD_DEFAULT_PRIORITY      -1
#define OSWRAP_THREAD_DEFAULT_STACKSIZE     -1

typedef struct {
    void                     (*address)(void *);
    void                    *parameter;
    int                      priority;
    int                      stksize;
} OSWRAP_THREAD_PARAM;

/****************************************************************************/
/* PerformanceCounter                                                       */
/****************************************************************************/

/****************************************************************************/
/* Buffer                                                                   */
/****************************************************************************/
typedef void *                              OSWRAP_BUFFER_ID;

typedef enum {

    OSWRAP_COMPONENT1       = 1,
    OSWRAP_COMPONENT4       = 4,
    OSWRAP_COMPONENT8       = 8,
    OSWRAP_COMPONENT16      = 16,
    OSWRAP_COMPONENT24      = 24,
    OSWRAP_COMPONENT32      = 32

} OSWRAP_COMPONENT_BITS;


/*
 * BUFFER TYPE
 */

/* 1D Shared Memory */
#define OSWRAP_MEMORY_TYPE_SHAREDMEMORY         0x1001  /* generic */
#define OSWRAP_BUFFER_TYPE_SHAREDMEMORY         OSWRAP_MEMORY_TYPE_SHAREDMEMORY
#define OSWRAP_MEMORY_TYPE_MESSAGE              0x1002
#define OSWRAP_MEMORY_TYPE_INFO_COMMANDBUFFER   0x1003
#define OSWRAP_MEMORY_TYPE_INFO_OBJECT          0x1004
#define OSWRAP_MEMORY_TYPE_INFO_DEBUG           0x1005

/* BUFFER1D */
#define OSWRAP_BUFFER_TYPE_COMMAND              0x4001
#define OSWRAP_BUFFER_TYPE_INTERM               0x4002  /* OpenVG */
#define OSWRAP_BUFFER_TYPE_TRACE_LOG            0x4003

#define OSWRAP_BUFFER_TYPE_VERTEX               0x4101  /* OpenGL ES : VBO */

/* BUFFER2D/3D */
#define OSWRAP_BUFFER_TYPE_FRAME                0x8000
#define OSWRAP_BUFFER_TYPE_COLOR                0x8001
#define OSWRAP_BUFFER_TYPE_DEPTH                0x8002	/* OpenGL ES */
#define OSWRAP_BUFFER_TYPE_STENCIL              0x8003	/* OpenGL ES */
#define OSWRAP_BUFFER_TYPE_DEPTH_STENCIL        0x8004	/* OpenGL ES */
#define OSWRAP_BUFFER_TYPE_ALPHA_MASK           0x8005  /* OpenVG */
#define OSWRAP_BUFFER_TYPE_PIXMAP               0x8006
#define OSWRAP_BUFFER_TYPE_NATIVE_BUFFER        0x8007

#define OSWRAP_BUFFER_TYPE_TEXTURE_1D           0x8101
#define OSWRAP_BUFFER_TYPE_TEXTURE_2D           0x8102
#define OSWRAP_BUFFER_TYPE_TEXTURE_3D           0x8103
#define OSWRAP_BUFFER_TYPE_TEXTURE_CUBE         0x8104
#define OSWRAP_BUFFER_TYPE_TEXTURE_RECT         0x8105

#define OSWRAP_BUFFER_TYPE_IMAGE                0x8201  /* OpenVG */

#define OSWRAP_BUFFER_TYPE_EGL_IMAGE            0x8301

#define OSWRAP_BUFFER_TYPE_MASK_LAYER           0x8401  /* OpenVG */

/* Capabilities */
#define OSWRAP_BUFFER_CAPS_SYSTEMMEMORY         0x00010000
#define OSWRAP_BUFFER_CAPS_VIDEOMEMORY          0x00020000
#define OSWRAP_BUFFER_CAPS_SHAREDMEMORY         0x00080000
#define OSWRAP_BUFFER_CAPS_LINK					0x01000000
#define OSWRAP_BUFFER_CAPS_ARRAY				0x02000000

/* bit mask */
#define OSWRAP_BUFFER_BITMASK_TYPE              0x0000ffff
#define OSWRAP_BUFFER_BITMASK_CAPS              0xffff0000


typedef struct {
    unsigned int            width;
    unsigned int            height;
    OSWRAP_COMPONENT_BITS   bpp;            /* bits per pixel */
    unsigned int            alignment;
} OSWRAP_BUFFER_PARAM;

/****************************************************************************/
/* Memory                                                                   */
/****************************************************************************/
typedef void *                              OSWRAP_MEMORY_ID;

typedef struct {
    unsigned int            memsize;
    unsigned int            alignment;
} OSWRAP_MEMORY_PARAM;

/****************************************************************************/
/* Common                                                                   */
/****************************************************************************/
#define OSWRAP_CLIENT           0
#define OSWRAP_RENDERINGMANAGER 1

/****************************************************************************/
/* Function                                                                 */
/****************************************************************************/
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_Initialize( int isRendMng );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_UnInitialize( int isRendMng );

#if defined(_NO_OS_)
#define OsWrap_GetProcessID()	(OSWRAP_PROCESS_ID)(1)		/* dummy process id */
#define OsWrap_GetThreadID()	(OSWRAP_THREAD_ID)(1)		/* dummy thread id */

#define	OsWrap_MutexCreate( _mutex )	(OSWRAP_SUCCESS)
#define	OsWrap_MutexDelete( _mutex )	(OSWRAP_SUCCESS)
#define	OsWrap_MutexLock( _mutex )		(OSWRAP_SUCCESS)
#define	OsWrap_MutexUnlock( _mutex)		(OSWRAP_SUCCESS)

#define OsWrap_SemaphoreCreate( _semaphore )	(OSWRAP_SUCCESS)
#define OsWrap_SemaphoreDelete( _semaphore )	(OSWRAP_SUCCESS)
#define OsWrap_SemaphoreSignal( _semaphore )	(OSWRAP_SUCCESS)
#define OsWrap_SemaphoreWait( _semaphore )		(OSWRAP_SUCCESS)

#else /* _NO_OS_ */
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_MutexCreate( OSWRAP_MUTEX *mutex );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_MutexDelete( OSWRAP_MUTEX *mutex );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_MutexLock( OSWRAP_MUTEX *mutex );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_MutexUnlock( OSWRAP_MUTEX *mutex );

extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SemaphoreCreate( OSWRAP_SEMAPHORE *semaphore );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SemaphoreDelete( OSWRAP_SEMAPHORE *semaphore );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SemaphoreSignal( OSWRAP_SEMAPHORE *semaphore );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_SemaphoreWait( OSWRAP_SEMAPHORE *semaphore );

extern OSW_API OSWrapError OSW_APIENTRY OsWrap_EventCreate( OSWRAP_EVENT *event );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_EventDelete( OSWRAP_EVENT *event );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_EventSet( OSWRAP_EVENT *event, OSWRAP_EVENT_PARAM *eparam );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_EventWait( OSWRAP_EVENT *event, OSWRAP_EVENT_PARAM *eparam );

extern OSW_API OSWrapError OSW_APIENTRY OsWrap_MessageCreate( OSWRAP_MESSAGE *message, OSWRAP_MESSAGE_PARAM *mparam );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_MessageDelete( OSWRAP_MESSAGE *message );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_MessageSend( OSWRAP_MESSAGE *message, OSWRAP_MESSAGE_PARAM *mparam );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_MessageReceive( OSWRAP_MESSAGE *message, OSWRAP_MESSAGE_PARAM *mparam );

extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadSleep( int sleepval );
extern OSW_API OSWRAP_PROCESS_ID OSW_APIENTRY OsWrap_GetProcessID( void );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_GetTime( OSW_INT64_T *time );

extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadCreateStart( OSWRAP_THREAD *thread, OSWRAP_THREAD_PARAM *tparam );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadDelete( OSWRAP_THREAD *thread );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadWait( OSWRAP_THREAD *thread );
extern OSW_API void OSW_APIENTRY OsWrap_MyThreadExit( void );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ThreadTerminate( OSWRAP_THREAD *thread );
extern OSW_API OSWRAP_THREAD_ID OSW_APIENTRY OsWrap_GetThreadID( void );
extern OSWrapError OsWrap_ThreadWaitWakeup( OSWRAP_THREAD *thread );
extern OSWrapError OsWrap_ThreadWakeup( OSWRAP_THREAD *thread );

extern OSW_API void OSW_APIENTRY OsWrap_InitPerformanceCounter( void );
extern OSW_API void OSW_APIENTRY OsWrap_QueryPerformanceCounter( OSW_INT64_T *time );
extern OSW_API void OSW_APIENTRY OsWrap_QueryPerformanceFrequency( OSW_INT64_T *time );
extern OSW_API double OSW_APIENTRY OsWrap_CnvPerformanceCounter( const OSW_INT64_T *time );
#endif /* _NO_OS_ */

extern OSW_API OSWRAP_BUFFER_ID OSW_APIENTRY OsWrap_CreateBuffer1D( unsigned int type, const OSWRAP_BUFFER_PARAM *mparam );
extern OSW_API OSWRAP_BUFFER_ID OSW_APIENTRY OsWrap_CreateBuffer2D( unsigned int type, const OSWRAP_BUFFER_PARAM *mparam );
extern OSW_API OSWRAP_BUFFER_ID OSW_APIENTRY OsWrap_MakeLinkBuffer( OSWRAP_BUFFER_ID id, unsigned int offset );
extern OSW_API OSWRAP_BUFFER_ID OSW_APIENTRY OsWrap_MakeLinkBuffer1D( unsigned int type, const void *ladr, const void *padr, const OSWRAP_BUFFER_PARAM *mparam );
extern OSW_API OSWRAP_BUFFER_ID OSW_APIENTRY OsWrap_MakeLinkBuffer2D( unsigned int type, const void *ladr, const void *padr, const OSWRAP_BUFFER_PARAM *mparam );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_LinkBufferAttrib( OSWRAP_BUFFER_ID id, const void *ladr, const void *padr, const OSWRAP_BUFFER_PARAM *mparam );
extern OSW_API void OSW_APIENTRY OsWrap_DeleteBuffer( OSWRAP_BUFFER_ID id );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_CreateBuffer1DArray( unsigned int n, OSWRAP_BUFFER_ID *buffers, unsigned int type, const OSWRAP_BUFFER_PARAM *mparam );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_DeleteBufferArray( unsigned int n, const OSWRAP_BUFFER_ID *buffers );
extern OSW_API void * OSW_APIENTRY OsWrap_GetLogicalBufferAdr( OSWRAP_BUFFER_ID id );
extern OSW_API void * OSW_APIENTRY OsWrap_GetPhysicalBufferAdr( OSWRAP_BUFFER_ID id );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ReadBuffer( OSWRAP_BUFFER_ID id, unsigned int offset, unsigned int size, void *dst );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_WriteBuffer( OSWRAP_BUFFER_ID id, unsigned int offset, unsigned int size, const void *src );

extern OSW_API OSWRAP_MEMORY_ID OSW_APIENTRY OsWrap_CreateMemory( unsigned int type, const OSWRAP_MEMORY_PARAM *mparam );
extern OSW_API OSWRAP_MEMORY_ID OSW_APIENTRY OsWrap_ReCreateMemory( OSWRAP_MEMORY_ID id, const OSWRAP_MEMORY_PARAM *mparam );
extern OSW_API void OSW_APIENTRY OsWrap_DeleteMemory( OSWRAP_MEMORY_ID id );
extern OSW_API void * OSW_APIENTRY OsWrap_GetLogicalMemoryAdr( OSWRAP_MEMORY_ID id );
extern OSW_API void * OSW_APIENTRY OsWrap_GetPhysicalMemoryAdr( OSWRAP_MEMORY_ID id );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_ReadMemory( OSWRAP_MEMORY_ID id, unsigned int offset, unsigned int size, void *dst );
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_WriteMemory( OSWRAP_MEMORY_ID id, unsigned int offset, unsigned int size, const void *src );

extern OSW_API int OSW_APIENTRY OsWrap_IsValidLogicalAddress( void *addr );
extern OSW_API void * OSW_APIENTRY OsWrap_CnvPhysicalToLogical( void *addr );

extern OSW_API OSWrapError OSW_APIENTRY OsWrap_DumpBASEMemory( void );

extern OSW_API OSWrapError OSW_APIENTRY OsWrap_CreateRefDumpFile(const char* dumpFileName, const char *mode, void *padr, size_t size);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __OS_WRAPPER_H__ */
