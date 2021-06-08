#include "CtDebugPrint.h"
#include "smDebugSerial.h"

#define CtDbgMSKPTN		0xFFFFFFFF /* �S�o�� */
#define CtDbgDtMSKPTN	CtDt /* Date�o�� */
#define SM_LEVEL 		(1)		// ��肠����smDebugPrintf�ɓn���K���Ȓl

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#if defined CT_DEBUG_PRINT_FUNC
void CtDebug(unsigned long int id, const char *funcname, int linenum, const char *fmt, ...)
#else
void CtDebug(unsigned long int id, const char *idname, const char *fmt, ...)
#endif
{
#ifndef CT_DEBUG_ENABLE
	if ((id & CtLog) == false) return;
#endif
	va_list vl;
	char logdata[256];

	/* NULL�΍�*/
	if (fmt == NULL) {
		return;
	}
	if (id & CtDbgMSKPTN) {
		/* �����𕶎���ɕϊ� */
		memset(logdata, 0, sizeof(logdata));
		va_start(vl, fmt);
		vsprintf(logdata, fmt, vl);
		va_end(vl);

		/* ���O�o�� */
#if defined CT_DEBUG_PRINT_FUNC
		smDebugPrintf(SM_LEVEL, "[%s]#%d: %s", funcname, linenum, logdata);
#else
		if (id & CtDbgDtMSKPTN) {
			SMDEBUG_LOGOUT_DT("[%s] %s", idname, logdata);
		}
		else {
			smDebugPrintf(SM_LEVEL, "[%s] %s", idname, logdata);
		}
#endif
	}
}
