/**
 *  Copyright (c) 2009 Copyright(c) 2018 Persol AVC Technology.
 *
 *  @brief      GUI デバッグプリント ヘッダファイル
 */
#ifndef __CT_DEBUG_PRINT_H__
#define __CT_DEBUG_PRINT_H__

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#include "CtAssert.h"
#include "SysIf.h"

#define CtLog			0xF0000000		// システムリリース版でも出力
#define CtDt			0x0F000000		// Date出力あり
#define CtLogDt			CtLog | CtDt	// システムリリース版でもDate出力
#define CtDbg			0x00000001		// 通常Debug用
#define CtDbgDt			CtDbg | CtDt	// 通常DebugでDate出力
#define CtDbgIdCmd		0x00000002		// DebugCommand出力用
/*
*    CtDebugPrint()
*/
#if defined CT_DEBUG_PRINT_FUNC
	void CtDebug(unsigned long int id, const char *funcname, int linenum, const char *fmt, ...);

	/* 関数名のみ */
	#define CtDebugPrint(id, fmt, ...)		CtDebug(id, __PRETTY_FUNCTION__, __LINE__, fmt, ##__VA_ARGS__);
#else
	void CtDebug(unsigned long int id, const char *idname, const char *fmt, ...);

	/* 文字列のみ表示 */
	#define CtDebugPrint(id, fmt, ...)		CtDebug(id, #id, fmt, ##__VA_ARGS__);
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __CT_DEBUG_PRINT_H__ */
