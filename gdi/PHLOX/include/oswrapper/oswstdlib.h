/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_STDLIB_H__
#define __OSW_STDLIB_H__

#include <oswrapper/oswplatform.h>
#include <local_malloc/ext_gevg_malloc.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSWSTDCAPIENTRY
#	define OSWSTDCAPIENTRY
#endif
#ifndef OSWSTDCAPIENTRYP
#	define OSWSTDCAPIENTRYP OSWSTDCAPIENTRY *
#endif


typedef void * (OSWSTDCAPIENTRYP PFNOSWMALLOCPROC) (size_t size);
typedef void (OSWSTDCAPIENTRYP PFNOSWFREEPROC) (void *ptr);
typedef void * (OSWSTDCAPIENTRYP PFNOSWREALLOCPROC) (void *ptr, size_t size);
typedef void (OSWSTDCAPIENTRYP PFNOSWABORT) (void);


/* OSW_MALLOC: Allocate memory. */
/* OSW_FREE: Free allocated memory block. */
/* OSW_REALLOC: Resize memory block. */

extern OSW_API PFNOSWMALLOCPROC		OSW_malloc;
extern OSW_API PFNOSWFREEPROC		OSW_free;
extern OSW_API PFNOSWREALLOCPROC	OSW_realloc;
extern OSW_API PFNOSWABORT			OSW_abort;


#ifdef USE_STDC_LIB

#	define	OSW_MALLOC		tkmalloc
#	define	OSW_FREE		tkfree
#	define	OSW_REALLOC		tkrealloc
#	define	OSW_ABORT		abort

#else /* USE_STDC_LIB */

#	define	OSW_MALLOC		OSW_malloc
#	define	OSW_FREE		OSW_free
#	define	OSW_REALLOC		OSW_realloc
#	define	OSW_ABORT		OSW_abort

#endif /* USE_STDC_LIB */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __OSW_STDLIB_H__ */
