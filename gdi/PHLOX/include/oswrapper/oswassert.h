/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_ASSERT_H__
#define __OSW_ASSERT_H__

#include <oswrapper/oswplatform.h>

#ifdef USE_STDC_LIB
#include <assert.h>
#endif /* USE_STDC_LIB */


#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSWSTDCAPIENTRY
#	define OSWSTDCAPIENTRY
#endif
#ifndef OSWSTDCAPIENTRYP
#	define OSWSTDCAPIENTRYP OSWSTDCAPIENTRY *
#endif


typedef void (OSWSTDCAPIENTRYP PFNOSWASSERTPROC) (int x);


extern OSW_API PFNOSWASSERTPROC		OSW_assert;


#ifdef USE_STDC_LIB
#	define	OSW_ASSERT		OSW_assert
#else /* USE_STDC_LIB */
#	define	OSW_ASSERT		OSW_assert
#endif /* USE_STDC_LIB */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __OSW_ASSERT_H__ */
