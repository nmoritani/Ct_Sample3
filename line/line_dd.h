/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           line block device driver
 */
#ifndef __LINE_DD_H__
#define __LINE_DD_H__

#include "line_api.h"
#include "line_ctrl.h"

typedef void (*LINE_DD_CALLBACK_FUNC)(void);

extern void Line_DD_SetColorPalette(GUI_OUTPUT_DEV output, const UW *source, GUI_COLOR_ID start, UB num);
extern void Line_DD_SetMemory(GUI_OUTPUT_DEV output, UB *address);
extern void Line_DD_Display(GUI_OUTPUT_DEV output, BOOL isOn);
extern void Line_DD_SetResolution(GUI_OUTPUT_DEV output, const LINE_MEMORY *memory, const GUI_VIDEO_FORMAT *signal);
extern void Line_DD_SetHandlerVsync(LINE_DD_CALLBACK_FUNC func);

#endif	/* __LINE_DD_H__ */
