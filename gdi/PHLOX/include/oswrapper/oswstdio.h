/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_STDIO_H__
#define __OSW_STDIO_H__

#include <oswrapper/oswplatform.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSWSTDCAPIENTRY
#	define OSWSTDCAPIENTRY
#endif
#ifndef OSWSTDCAPIENTRYP
#	define OSWSTDCAPIENTRYP OSWSTDCAPIENTRY *
#endif

/* 20130917 ZANTEI */
extern void vGELogWrite(const char *szFormat, ...);	// main.c ‚Å‰¼’u‚«‚µ‚Ä‚¢‚é


typedef FILE *(OSWSTDCAPIENTRYP PFNOSWFOPENPROC) (const char *path, const char *mode);
typedef int (OSWSTDCAPIENTRYP PFNOSWFCLOSEPROC) (FILE *fp);
typedef size_t (OSWSTDCAPIENTRYP PFNOSWFREADPROC) (void *ptr, size_t size, size_t nmemb, FILE *stream);
typedef size_t (OSWSTDCAPIENTRYP PFNOSWFWRITEPROC) (const  void  *ptr,  size_t  size,  size_t  nmemb,  FILE *stream);
typedef char *(OSWSTDCAPIENTRYP PFNOSWFGETSPROC) (char *s, int size, FILE *stream);
typedef int (OSWSTDCAPIENTRYP PFNOSWFEOFPROC) (FILE *stream);
typedef int (OSWSTDCAPIENTRYP PFNOSWFERRORPROC) (FILE *stream);
typedef void (OSWSTDCAPIENTRYP PFNOSWCLEARERRPROC) (FILE *stream);

typedef int (OSWSTDCAPIENTRYP PFNOSWPRINTFPROC) (const char *format, ...);
typedef int (OSWSTDCAPIENTRYP PFNOSWFPRINTFPROC) (FILE *stream, const char *format, ...);
typedef int (OSWSTDCAPIENTRYP PFNOSWSPRINTFPROC) (char *str, const char *format, ...);
typedef int (OSWSTDCAPIENTRYP PFNOSWSNPRINTFPROC) (char *str, size_t size, const char *format, ...);


/* OSW_FOPEN: Open a file from the file system. */
/* OSW_FCLOSE: Close an open file. */
/* OSW_FREAD: Read from a file. */
/* OSW_FWRITE: Write to a file. */
/* OSW_FGETS: Read a line of text from an open file. */
/* OSW_FEOF: Check for end of file. */
/* OSW_FERROR: Check for an error condition on an open file. */
/* OSW_CLEARERR: Clear a file's error and end-of-file indicators. */

/* OSW_FPRINTF: Formatted output to an open file. */
/* OSW_SNPRINTF: Formatted output to a buffer. */


extern OSW_API PFNOSWFOPENPROC		OSW_fopen;
extern OSW_API PFNOSWFCLOSEPROC		OSW_fclose;
extern OSW_API PFNOSWFREADPROC		OSW_fread;
extern OSW_API PFNOSWFWRITEPROC		OSW_fwrite;
extern OSW_API PFNOSWFGETSPROC		OSW_fgets;
extern OSW_API PFNOSWFEOFPROC		OSW_feof;
extern OSW_API PFNOSWFERRORPROC		OSW_ferror;
extern OSW_API PFNOSWCLEARERRPROC	OSW_clearerr;
extern OSW_API PFNOSWPRINTFPROC		OSW_printf;
extern OSW_API PFNOSWFPRINTFPROC	OSW_fprintf;
extern OSW_API PFNOSWSNPRINTFPROC	OSW_snprintf;


#ifdef USE_STDC_LIB

#	define	OSW_FOPEN		fopen
#	define	OSW_FCLOSE		fclose
#	define	OSW_FREAD		fread
#	define	OSW_FWRITE		fwrite
#	define	OSW_FGETS		fgets
#	define	OSW_FEOF		feof
#	define	OSW_FERROR		ferror
#	define	OSW_CLEARERR	clearerr
#	define	OSW_PRINTF(fmt)		smDebugPrintf(1,fmt) //printf
#	define	OSW_FPRINTF		fprintf
#	define	OSW_SNPRINTF	snprintf

#else /* USE_STDC_LIB */

#	define	OSW_FOPEN		OSW_fopen
#	define	OSW_FCLOSE		OSW_fclose
#	define	OSW_FREAD		OSW_fread
#	define	OSW_FWRITE		OSW_fwrite
#	define	OSW_FGETS		OSW_fgets
#	define	OSW_FEOF		OSW_feof
#	define	OSW_FERROR		OSW_ferror
#	define	OSW_CLEARERR	OSW_clearerr
#	define	OSW_PRINTF		OSW_printf
#	define	OSW_FPRINTF		OSW_fprintf
#	define	OSW_SNPRINTF	OSW_snprintf

#endif /* USE_STDC_LIB */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __OSW_STDIO_H__ */
