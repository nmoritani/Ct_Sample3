/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#include "DTversion.h"

/*--------------------------------------------------------------*/
DT_void DigiTypeAPIGetVersion(DigiTypeAPIVer *ver)
{

DBG_MSG_SHOW_FUNC_NAME();

	ver->major = (DIGITYPEAPI_VERSION & 0xFFFF0000)>>16;
	ver->minor = (DIGITYPEAPI_VERSION & 0x0000FFFF);
	ver->maintain = (DIGITYPEAPI_BUILDNUM & 0xFFFF0000)>>16;
	ver->buildnum = (DIGITYPEAPI_BUILDNUM & 0x0000FFFF);
}
