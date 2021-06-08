/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_STRING_H__
#define __OSW_STRING_H__

#include <oswrapper/oswplatform.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSWSTDCAPIENTRY
#	define OSWSTDCAPIENTRY
#endif
#ifndef OSWSTDCAPIENTRYP
#	define OSWSTDCAPIENTRYP OSWSTDCAPIENTRY *
#endif


typedef int (OSWSTDCAPIENTRYP PFNOSWMEMCMPPROC) (const void *ptr1, const void *ptr2, size_t size);
typedef void * (OSWSTDCAPIENTRYP PFNOSWMEMCPYPROC) (void *ptr_dst, const void *ptr_src, size_t size);
typedef void * (OSWSTDCAPIENTRYP PFNOSWMEMMOVEPROC) (void *ptr_dst, const void *ptr_src, size_t size);
typedef void * (OSWSTDCAPIENTRYP PFNOSWMEMSETPROC) (void *ptr, int val, size_t size);
typedef int (OSWSTDCAPIENTRYP PFNOSWSTRCMPPROC) (const char *ptr1, const char *ptr2);
typedef size_t (OSWSTDCAPIENTRYP PFNOSWSTRLENPROC) (const char *ptr);
typedef char * (OSWSTDCAPIENTRYP PFNOSWSTRNCATPROC) (char *ptr_dst, const char *ptr_src, size_t size);
typedef int (OSWSTDCAPIENTRYP PFNOSWSTRNCMPPROC) (const char *ptr1, const char *ptr2, size_t size);
typedef char * (OSWSTDCAPIENTRYP PFNOSWSTRNCPYPROC) (char *ptr_dst, const char *ptr_src, size_t size);

/* OSW_MEMCHR: Scan memory for a byte value. */
/* OSW_MEMCMP: Compare two memory regions. */
/* OSW_MEMCPY: Copy a memory region, no overlapping. */
/* OSW_MEMMOVE: Copy a memory region, overlapping allowed. */
/* OSW_MEMSET: Set bytes in memory to a value. */
/* OSW_STRCHR: Scan string for a byte value. */
/* OSW_STRCMP: Compares two strings. */
/* OSW_STRLEN: Determine the length of a string. */
/* OSW_STRNLEN: Determine the length of a string. */
/* OSW_STRNCAT_S: Concatenate two strings. */
/* OSW_STRNCMP: Compares two strings with length limit. */
/* OSW_STRCPY_S: Copy a string with an overrun check. */
/* OSW_STRNCPY_S: Copy a string with an overrun check. */

extern OSW_API PFNOSWMEMCMPPROC		OSW_memcmp;
extern OSW_API PFNOSWMEMCPYPROC		OSW_memcpy;
extern OSW_API PFNOSWMEMMOVEPROC	OSW_memmove;
extern OSW_API PFNOSWMEMSETPROC		OSW_memset;
extern OSW_API PFNOSWSTRCMPPROC		OSW_strcmp;
extern OSW_API PFNOSWSTRLENPROC		OSW_strlen;
extern OSW_API PFNOSWSTRNCATPROC	OSW_strncat;
extern OSW_API PFNOSWSTRNCMPPROC	OSW_strncmp;
extern OSW_API PFNOSWSTRNCPYPROC	OSW_strncpy;


#ifdef USE_STDC_LIB

#	define	OSW_MEMCMP		memcmp
#	define	OSW_MEMCPY		memcpy
#	define	OSW_MEMMOVE		memmove
#	define	OSW_MEMSET		memset
#	define	OSW_STRCMP		strcmp
#	define	OSW_STRLEN		strlen
#	define	OSW_STRNCAT		strncat
#	define	OSW_STRNCMP		strncmp
#	define	OSW_STRNCPY		strncpy

#else /* USE_STDC_LIB */

#	define	OSW_MEMCMP		OSW_memcmp
#	define	OSW_MEMCPY		OSW_memcpy
#	define	OSW_MEMMOVE		OSW_memmove
#	define	OSW_MEMSET		OSW_memset
#	define	OSW_STRCMP		OSW_strcmp
#	define	OSW_STRLEN		OSW_strlen
#	define	OSW_STRNCAT		OSW_strncat
#	define	OSW_STRNCMP		OSW_strncmp
#	define	OSW_STRNCPY		OSW_strncpy

#endif /* USE_STDC_LIB */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __OSW_STRING_H__ */
