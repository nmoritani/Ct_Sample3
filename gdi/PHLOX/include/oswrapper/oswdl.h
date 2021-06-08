/*
  Copyright (c) 2013, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSWDL_H__
#define __OSWDL_H__

#include <oswrapper/os_wrapper.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef void * OSWRAP_LIBRARY;

#define OSWRAP_INVALID_LIBRARY	(OSWRAP_LIBRARY)NULL


extern OSW_API OSWRAP_LIBRARY OSW_APIENTRY OsWrap_DLOpen(const char *name, int *attrib);
extern OSW_API OSWrapError OSW_APIENTRY OsWrap_DLClose(OSWRAP_LIBRARY library);
extern OSW_API void * OSW_APIENTRY OsWrap_DLGetProcAddress(OSWRAP_LIBRARY library, const char *name);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __OSWDL_H__ */
