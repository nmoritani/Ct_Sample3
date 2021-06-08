/**
 *  Persol AVC Technology
 *  Element:	Comfortable Toolkit Configuration
 */

#ifndef __CtConfig_H__
#define __CtConfig_H__

#include <stdio.h>
#include <string.h>
#include "CtType.h"

#define CT_SCREEN_NUM	2

static const CtScreenConfig	ScreenConfig[CT_SCREEN_NUM] = {
	{ScreenLCD,		GDI_COLOR_FORMAT_RGBA4444,	CtSize(960,640), GFX_PLANE_LCD},
	{ScreenLOUT,	GDI_COLOR_FORMAT_RGBA4444,	CtSize(960,540), GFX_PLANE_LOUT}
};

static const CtSize		DefaultSize = CtSize(0, 0);
static const CtSize		AutoSize = CtSize(0, 0); 
static const CtSize		StyleSize = CtSize(-1, -1);

static const CtRegion	DefaultRegion = CtRegion(0, 0, 0, 0);
static const CtRegion	NoRegion = CtRegion(0, 0, 0, 0);

#endif
