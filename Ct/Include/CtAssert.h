/**
 *  Copyright (c) 2009 Copyright(c) 2018 Persol AVC Technology.
 *  $Id$
 *
 *  @file
 *  @brief      ComfortToolkit アサーション ヘッダファイル
 */

#if !defined(__CT_ASSERT_H__)
#define __CT_ASSERT_H__

#if defined(__cplusplus)
extern "C"{
#endif /* __cplusplus */

#define CT_ASSERT_BREAK asm("	.byte	0xff")

#define	CT_PRINT_COL_DEF			"\033[0m"
#define	CT_PRINT_COL_RED			"\033[31m"
#define	CT_PRINT_COL_REV_RED		"\033[41;37m"

#if defined(WIN32_GUI_SIM)
#define __PRETTY_FUNCTION__	__FUNCTION__
#endif

#if (!defined CT_DEBUG_ENABLE)
#define CtAssert(arg)	if (arg) {}
#define CtAssertEx(arg,fmt,...)	if (arg) {}
#else	
#include "smDebugSerial.h"

#if defined(CT_ASSERT_ENABLE)

#define CtAssert(arg) \
            if (arg) {} else { \
            smDebugPrintf(1,"%s[%s]#%d: Assertion Failed%s\n",CT_PRINT_COL_REV_RED,__PRETTY_FUNCTION__,__LINE__,CT_PRINT_COL_DEF); \
            smDebugAssert(); \
			CT_ASSERT_BREAK;}
#define CtAssertEx(arg, fmt, ...) \
            if (arg) {} else { \
            smDebugPrintf(1,"%s[%s]#%d: Assertion Failed%s :",CT_PRINT_COL_REV_RED,__PRETTY_FUNCTION__,__LINE__,CT_PRINT_COL_DEF); \
            smDebugPrintf(1,"" fmt "\n",##__VA_ARGS__); \
            smDebugAssert(); \
			CT_ASSERT_BREAK;}
	
#else  /* CT_ASSERT_ENABLE */

#define CtAssert(arg) \
			if (arg) {} else { \
			smDebugPrintf(1,"%s[%s]#%d: Assertion Failed%s\n",CT_PRINT_COL_REV_RED,__PRETTY_FUNCTION__,__LINE__,CT_PRINT_COL_DEF); \
			}
	
#define CtAssertEx(arg, fmt, ...) \
            if (arg) {} else { \
            smDebugPrintf(1,"%s[%s]#%d: Assertion Failed%s :" fmt "\n",CT_PRINT_COL_REV_RED,__PRETTY_FUNCTION__,__LINE__,CT_PRINT_COL_DEF,##__VA_ARGS__);\
			}
#endif /* CT_ASSERT_ENABLE */

#endif /* __i386__ */ /* CT_SIMULATOR */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __CT_ASSERT_H__ */
