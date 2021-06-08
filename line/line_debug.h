/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           debug of line block
 */
#ifndef __LINE_DEBUG_H__
#define __LINE_DEBUG_H__

#include "smDebugSerial.h"

#ifdef CT_DEBUG_ENABLE
#define LineDebugPrint(fmt, ...)		smDebugPrintf(0, "%s: " fmt, __FUNCTION__, ##__VA_ARGS__)
#else  /* CT_DEBUG_ENABLE */
#define LineDebugPrint(...)
#endif	/* CT_DEBUG_ENABLE */

#endif	/* __LINE_DEBUG_H__ */
