
# include "kernel.h"
# include "kernel_id.h"
#include "line_api.h"

#ifdef WIN32_GUI_SIM
#else
# include "SysIf.h"
#define IMG_DATA_LOAD_NONE  0
#define IMG_DATA_LOAD_NG   -1
#define IMG_DATA_LOAD_OK    1
static INT load_result = IMG_DATA_LOAD_NONE;
#endif



#ifdef WIN32_GUI_SIM
#else
static void load_callback(SYS_RET Result, const char *SectionName) 
{
  if( Result == SYS_OK )
	{
	  load_result = IMG_DATA_LOAD_OK;
	}
  else
	{
	  load_result = IMG_DATA_LOAD_NG;
	}
}
#endif

#ifdef CT_DBG_TSK_ACT
    #include "CtActDbgTsk.h"
    extern BOOL act_DbgTsk();
#endif

void
GUI_Init (void)
{

#ifdef WIN32_GUI_SIM
#else
	SYS_Section_LoadReq(".guidata", load_callback);	
	while(load_result == IMG_DATA_LOAD_NONE){
	  dly_tsk(1);
	}
#endif
	act_tsk(CT_DRAW_TSKID);
	act_tsk(GUI_TSK_ID);
	act_tsk(CT_MAIN_TSKID);

#ifdef CT_DBG_TSK_ACT
    act_DbgTsk();
#endif
	
    GUI_LineInit();
}
