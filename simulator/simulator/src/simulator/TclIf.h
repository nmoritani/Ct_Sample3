/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   TCLブロック ヘッダーファイル (シミュレーター用)
 */
#ifndef _TCL_IF_H_
#define _TCL_IF_H_

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#include "SysIf.h"
	
//エラー定義
typedef enum tcl_err {
	TCL_ER_OK = 0,
	TCL_ER_NG,
	TCL_ER_INVALID,						/* 値無効 ⇒「※」表示,尚、Pb時OSD表示,HDMI-TC用 */
	TCL_ER_CANCEL,						/* キャンセル通知用 */
	TCL_ER_CONTINUE						/* 内部処理用 処理継続指示 */
} TCL_ER;

	
TCL_ER TCL_GetDateTimeDelay(SYS_DATE_TIME *pValue, W delay );

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* _TCL_IF_H_ */
