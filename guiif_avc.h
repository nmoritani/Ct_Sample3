#ifndef __GUI_IF_AVC_H__
#define __GUI_IF_AVC_H__
#include "GUI_OsdDispIf.h"
#include "AvcIf.h"

typedef enum {
	GUIAVC_UPDATE_NORMAL = 0,	/* í èÌóvãÅ */
	GUIAVC_UPDATE_RETRY,		/* çƒóvãÅ */
	GUIAVC_UPDATE_MAX
} GUIAVC_UPDATE_ID;


typedef enum {
	GUIAVC_DISP_LCD = 0,
	GUIAVC_DISP_LOUT,
	GUIAVC_DISP_REC,
	GUIAVC_DISP_MAX
} GUIAVC_DISP_ID;


extern void GUIAVC_RequestUpdateOsd(GUIAVC_DISP_ID disp_id, GUIAVC_UPDATE_ID id );
extern void GUIAVC_ExecUpdateOsdLcd(void);
extern void GUIAVC_ExecUpdateOsdLout(void);
extern void GUIAVC_updateOsd( GUIAVC_DISP_ID disp_id, GUIAVC_UPDATE_ID id );
extern void GUIAVC_DisplayOsdLcd( GUI_ST_DISPLAY_LCD* pDisplay );
extern void GUIAVC_DisplayOsdLout( GUI_ST_DISPLAY_LOUT* pDisplay );
extern void GUIAVC_DisplayOsdLcdInfo( UW addr );
extern void GUIAVC_DisplayOsdLoutInfo( UW addr );
extern void GUIAVC_OsdLoutScale(BOOL is90percent);
extern void GUIAVC_setOsdPlaneSizeLcd(void);
extern void GUIAVC_setOsdPlaneSizeLout(void);
extern void GUIAVC_ChangeColorFormat(BOOL isLcd, BOOL isRGBA8888);
#endif
