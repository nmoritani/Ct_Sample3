/*!
  @file    GuiIf.h
  @author  Kato Yukiko
  @brief   GUI初期化ヘッダ
*/
#ifndef _GUI_IF_H_
#define _GUI_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../Mid/Gui/line/line_api.h"
#include "../Mid/Gui/GUI_OsdDispIf.h"
#include "../Mid/Gui/string/language_id.h"
#include "../Mid/Gui/TimeStamp/gui_timestamp_api.h"
	
extern void GUI_Init (void);
extern unsigned short* GDI_GetString ( LANGUAGE_ID language_id, unsigned short string_id );

/* 
 * メモリプロファイル結果の参照
 */
#ifdef ENABLE_MEM_PROFILE
  extern W GUI_GetMplUsed (void);
  extern W GUI_GetMplPeak (void);
#else
# define GUI_GetMplUsed()  0
# define GUI_GetMplPeak()  0
#endif


#ifdef __cplusplus
}
#endif

#endif /* _GUI_IF_H_ */
