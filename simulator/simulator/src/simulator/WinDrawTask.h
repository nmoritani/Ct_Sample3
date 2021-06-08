/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   WINDOWSアプリ側描画用タスク
 */
#ifndef __WIN_DRAW_TASK_H__
#define __WIN_DRAW_TASK_H__

#include "win_itron.h"
#include "kernel_id.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

typedef enum {
	MBX_DRAWTEST_TYPE_SETPOINT = 0,
	MBX_DRAWTEST_TYPE_PUSH_KEY,
	MBX_DRAWTEST_TYPE_STOP,
	MBX_DRAWTEST_TYPE_TEST,
} MBX_DRAWTEST_TYPE;


//コールバック用
typedef void (*CALLBACK_WIN_DRAWTASK)(); //関数ポインタのtypedef
void WinDrawTask_Init(CALLBACK_WIN_DRAWTASK callbackfunc);

BOOL WinDrawTask_sendMsg(int mbxid, USHORT msgtype, int length, USHORT *data);
void SimulatorWindowDraw();

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif
