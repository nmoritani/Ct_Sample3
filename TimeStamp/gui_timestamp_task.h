#ifndef __GUI_TIMESTAMP_TASK_H__
#define __GUI_TIMESTAMP_TASK_H__

#include "gui_timestamp_api.h"
#include "CtTimeStamp.h"

enum GuiTsMsgType {
	TsMsgCreate,
	TsMsgUpdate,
	TsMsgDestroy,
};

struct GuiTsMsg {
	GuiTsMsgType type;
	union {
		struct {
			W id;
			GUI_TS_CALLBACK callback;
		} create;
		struct {
			W id;
		} destroy;
	} data;
};

struct GuiTsInfo
{
	CtColorFormat coloFormat;
	int colorDepth;
	CtTimeStamp::CtTsDisp DispMode;		
	CtSize Size;
	CtTimeStamp *pTimeStamp;
};

extern int GUI_TS_Init(const GuiTsInfo *info);
extern int GUI_TS_Create(int id, GUI_TS_CALLBACK cbfunc);
extern int GUI_TS_Get(int id, GUI_TS_INFO  *info);
extern int GUI_TS_Destroy(int id);

#endif
