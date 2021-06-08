
#include "GUI_OsdDispIf.h"
#include "guiif_avc.h"

void GUI_setDisplayOsdLcd( GUI_ST_DISPLAY_LCD* pDisplay )
{
	// LCD	----------------------
	GUIAVC_DisplayOsdLcd( pDisplay );
}
void GUI_setDisplayOsdLout( GUI_ST_DISPLAY_LOUT* pDisplay )
{
	// LOUT	----------------------
	GUIAVC_DisplayOsdLout( pDisplay );
}

//OSD表示アドレス設定
void GUI_DisplayOsdLcdWithColorFormat( UW addr )
{
	//OSD表示アドレス設定
	GUIAVC_DisplayOsdLcdInfo(addr);
	//入力プレーンサイズ設定	RGBA4444/8888を動的に切り替える為、表示面切替と同時にAVCへ通知する
	GUIAVC_setOsdPlaneSizeLcd();
}

void GUI_DisplayOsdLoutWithColorFormat( UW addr )
{
	//OSD表示アドレス設定
	GUIAVC_DisplayOsdLoutInfo(addr);
	//入力プレーンサイズ設定	RGBA4444/8888を動的に切り替える為、表示面切替と同時にAVCへ通知する
	GUIAVC_setOsdPlaneSizeLout();
}


//OSD外部出力スケール設定
void GUI_OsdLoutScale(BOOL is90percent)
{
	GUIAVC_OsdLoutScale(is90percent);
}
