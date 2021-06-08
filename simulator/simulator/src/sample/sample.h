#ifndef __SAMPLE_H
#define __SAMPLE_H
#if defined(__cplusplus)
extern "C"{
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#ifdef HG_FLAT_INCLUDES
#	include "openvg.h"
#	include "vgu.h"
#	include "egl.h"
#else
#	include "VG/openvg.h"
#	include "VG/vgu.h"
#	include "EGL/egl.h"
#endif

/*------------------------------------------------------------------------
 *
 * OpenVG 1.0.1 Reference Implementation sample code
 * -------------------------------------------------
 *
 * Copyright (c) 2007 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and /or associated documentation files
 * (the "Materials "), to deal in the Materials without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Materials,
 * and to permit persons to whom the Materials are furnished to do so,
 * subject to the following conditions: 
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Materials. 
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR
 * THE USE OR OTHER DEALINGS IN THE MATERIALS.
 *
 *//**
 * \file
 * \brief	Header for including the Tiger image data.
 * \note	
 *//*-------------------------------------------------------------------*/

void init(NativeWindowType window);
int sample_main(void);
void render(int w, int h);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __SAMPLE_H */
