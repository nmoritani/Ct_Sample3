/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           task of draw control in line block
 */
#ifndef __LINE_TASK_H__
#define __LINE_TASK_H__

#include "kernel.h"
#include "kernel_id.h"
#include "line_api.h"

/* イベントフラグ */
typedef UW LINE_MSG_DATA_FLAG;
#define LINE_FLG_DRAW_EXEC			0x00000001

/* データ資源の排他 (セマフォで実現) */
#define LINE_LOCK_LAYERINFO()	wai_sem(GUI_SEMID_LINE)
#define LINE_UNLOCK_LAYERINFO()	sig_sem(GUI_SEMID_LINE)

extern void Line_InitTask(void);
extern void Line_SendMessageFlag(LINE_MSG_DATA_FLAG flag);
extern void Line_SendMessageChangeResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image);
extern void Line_Main(void);

#endif	/* __LINE_TASK_H__ */
