/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_STDARG_H__
#define __OSW_STDARG_H__

#include <oswrapper/oswplatform.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif


#define OSW_va_list     va_list
#define OSW_va_start    va_start
#define OSW_va_end      va_end
#define OSW_va_arg      va_arg

/*
void va_start(va_list arg_ptr, prev_param);
void va_end(va_list arg_ptr);
type va_arg(va_list arg_ptr, type);
*/

#ifdef USE_STDC_LIB

#   define OSW_VA_LIST     va_list
#   define OSW_VA_START    va_start
#   define OSW_VA_END      va_end
#   define OSW_VA_ARG      va_arg

#else /* USE_STDC_LIB */

#   define OSW_VA_LIST     OSW_va_list
#   define OSW_VA_START    OSW_va_start
#   define OSW_VA_END      OSW_va_end
#   define OSW_VA_ARG      OSW_va_arg

#endif /* USE_STDC_LIB */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __OSW_STDARG_H__ */
