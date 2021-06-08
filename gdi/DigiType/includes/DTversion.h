/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#ifndef __DTVERSION_H
#define __DTVERSION_H

#include "DTplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DIGITYPEAPI_VERSION		0x00020005	/* major minor*/
#define DIGITYPEAPI_BUILDNUM	0x003C0009	/* 0xmmmmbbbb */

typedef struct _DigiType_Version
{
	DT32_int major;
	DT32_int minor;
	DT32_int maintain;
	DT32_int buildnum;
}DigiTypeAPIVer, *pDigiTypeAPIVer;

DT_void DigiTypeAPIGetVersion(DigiTypeAPIVer *ver);

#ifdef __cplusplus
}
#endif

#endif
