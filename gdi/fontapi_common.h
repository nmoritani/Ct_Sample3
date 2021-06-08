/**
@file     fontapi_common.h
@brief    フォントI/F（通称「フォントサービス」）内共通ヘッダー
@author   Yuji Nomura @DSC BU, Panasonic Corp.
@date     2013.3.14 コード整理に伴い新規作成
@par      更新履歴: Subversionのログ参照
*/

#ifndef ___FONTAPI_COMMON_H
#define ___FONTAPI_COMMON_H

#include <string.h>  /* for memmove(), memcpy(), memset() */
#include "fontapi.h"
#include "DigiTypeApi.h"
#include "fontdata.h"
#include "fontapi_config.h"


#if defined(FONT_DEBUG) || defined(FONTAPI_LOGGER)
#if CFG_ENABLE_HJ_SHELL != 1
#undef FONT_DEBUG
#undef FONTAPI_LOGGER
#else
#ifdef __arm__
#include <hj_debug.h>
#define dbgprintf hj_DebugArm_WriteFormat
#define dbgprint hj_DebugArm_WriteFormat
#else
#include <hj_fw/hj_debug.h>
#endif
#endif
#endif

#ifdef FONTAPI_LOGGER
extern void print_tim(void);
extern void record_tim(int mark);
extern void reset_tim(void);
#endif

#if defined(FONT_DEBUG) && !defined(__arm__)
#include <common.h>
#include <eeprom.h>
#include <eepf_3d.h>
#endif

/* ロケール特有の文字コード範囲 */
#define isASCII(c) ((c) >= 0x0020 && (c) <= 0x007f)
#define isCJK(c) ((c) >= 0x3000 && (c) <= 0xfaff && !((c) >= 0xe100 && (c) <= 0xe3ff))
#define isArabic(c)														\
	(((c) >= 0x0600 && (c) <= 0x07ff) ||  /* Basic Arabic */			\
	 ((c) >= 0xfb50 && (c) <= 0xfdff) ||  /* Arabic Form A */			\
	 ((c) >= 0xfe70 && (c) <= 0xfeff) ||  /* Arabic Form B */			\
	 ((c) >= 0xe000 && (c) <= 0xe08f) /* Arabic PUA */ )
#define isArabicOrRLM(c) (isArabic(c) || (c) == 0x200f)
#define isBidiControlCode(c) (0x200b <= (c) && (c) <= 0x200f || 0x202a <= (c) && (c) <= 0x202e)
#define isThai(c) ((c) >= 0x0e00 && (c) <= 0x0e7f)
#define isIndicDevanagari(ch) (( ((ch)>=0x0900 && (ch)<=0x097f)        \
                                    || ((ch)>=0xE300 && (ch)<=0xE308)  \
                                    || ((ch)>=0xEF00 && (ch)<=0xEFFF)  \
                                    || ((ch)>=0xF200 && (ch)<=0xF3FF)  \
                                    || (ch)==0x25CC)?1:0)  /* borrowed from DcwDevanagari.h */

#endif  /* ___FONTAPI_COMMON_H */
