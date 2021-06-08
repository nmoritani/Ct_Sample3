# include "kernel.h"
# include "kernel_id.h"

#include "GUI_OsdDispIf.h"
#include "guiif_avc.h"
#include "AvcGuiIf.h"
#include "gdi_config.h"

BOOL guiavc_update_lcd = FALSE;
BOOL guiavc_update_lout = FALSE;


// カラーフォーマット。初期値は16bitRGBA4444
static AVC_VIDEO_COLOR guiavc_color_format_lcd = AVC_VIDEO_COLOR_OSD_RGBA4444;
static AVC_VIDEO_COLOR guiavc_color_format_lout = AVC_VIDEO_COLOR_OSD_RGBA4444;

void GUIAVC_ChangeColorFormat(BOOL isLcd, BOOL isRGBA8888)
{
	if(isLcd == TRUE){
		if(isRGBA8888 == TRUE){
			guiavc_color_format_lcd = AVC_VIDEO_COLOR_OSD_RGBA8888;
		}else{
			guiavc_color_format_lcd = AVC_VIDEO_COLOR_OSD_RGBA4444;
		}
	}else{
		if(isRGBA8888 == TRUE){
			guiavc_color_format_lout = AVC_VIDEO_COLOR_OSD_RGBA8888;
		}else{
			guiavc_color_format_lout = AVC_VIDEO_COLOR_OSD_RGBA4444;
		}
	}
}

AVC_VIDEO_COLOR GUIAVC_GetColorFormat(BOOL isLcd)
{
	if(isLcd == TRUE){
		return	guiavc_color_format_lcd;
	}else{
		return	guiavc_color_format_lout;
	}
}


void GUIAVC_RequestUpdateOsd(GUIAVC_DISP_ID disp_id, GUIAVC_UPDATE_ID id )
{
//	GUIAVC_updateOsd( disp_id,  id );
	if(disp_id == GUIAVC_DISP_LCD){
		guiavc_update_lcd = TRUE;
	}else{
		guiavc_update_lout = TRUE;
	}
}

void GUIAVC_ExecUpdateOsdLcd(void)
{
	if(guiavc_update_lcd == TRUE){
		GUIAVC_updateOsd( GUIAVC_DISP_LCD,  GUIAVC_UPDATE_NORMAL );
		guiavc_update_lcd = FALSE;
	}
}
void GUIAVC_ExecUpdateOsdLout(void)
{
	if(guiavc_update_lout == TRUE){
		GUIAVC_updateOsd( GUIAVC_DISP_LOUT,  GUIAVC_UPDATE_NORMAL );
		guiavc_update_lout = FALSE;
	}
}

void GUIAVC_DisplayOsdLcd( GUI_ST_DISPLAY_LCD* pDisplay )
{
	if(pDisplay == NULL) return;

	// LCD	----------------------
	AVC_ST_DISPLAY_LCD	Display_Lcd;
	Display_Lcd.mIsOn = pDisplay->mIsOn;
	Display_Lcd.mOsd.mLcdEvf = (AVC_OUTPUT_LCDEVF)(pDisplay->mOsd.mLcdEvf);

	//OSD面
	// ZOM1
	Display_Lcd.mOsd.mLayer = AVC_OSD_LAYER_1;
	AVD_setDisplayOsdLcd(&Display_Lcd);
	// GFX面
	// ZOM2
	Display_Lcd.mOsd.mLayer = AVC_OSD_LAYER_2;
	AVD_setDisplayOsdLcd(&Display_Lcd);

//	GUIAVC_RequestUpdateOsd(GUIAVC_DISP_LCD, GUIAVC_UPDATE_NORMAL);
	GUIAVC_updateOsd(GUIAVC_DISP_LCD, GUIAVC_UPDATE_NORMAL);

}

void GUIAVC_DisplayOsdLout( GUI_ST_DISPLAY_LOUT* pDisplay )
{
	if(pDisplay == NULL) return;

	// LOUT	----------------------
	AVC_ST_DISPLAY_LOUT Display_Lout;
	Display_Lout.mIsOn = pDisplay->mIsOn;
	Display_Lout.mOsd.mTerminal = (AVC_OUTPUT_TERMINAL)(pDisplay->mOsd.mTerminal);
	//OSD面
	// ZOM1
	Display_Lout.mOsd.mLayer = AVC_OSD_LAYER_1;
	AVD_setDisplayOsdLout(&Display_Lout);
	// GFX面
	// ZOM2
	Display_Lout.mOsd.mLayer = AVC_OSD_LAYER_2;
	AVD_setDisplayOsdLout(&Display_Lout);

//	GUIAVC_RequestUpdateOsd(GUIAVC_DISP_LOUT, GUIAVC_UPDATE_NORMAL);
	GUIAVC_updateOsd(GUIAVC_DISP_LOUT, GUIAVC_UPDATE_NORMAL);
}

//OSD表示アドレス設定
void GUIAVC_DisplayOsdLcdInfo( UW addr )
{
	AVC_ST_OSD_LCD_INFO Info_lcd;
	Info_lcd.mColor = GUIAVC_GetColorFormat(TRUE);
	Info_lcd.mTopAddr = addr;
	Info_lcd.mOsd.mLcdEvf = (AVC_OUTPUT_LCDEVF)(AVC_OUTPUT_LCDEVF_LCD | AVC_OUTPUT_LCDEVF_EVF);
	Info_lcd.mOsd.mLayer = AVC_OSD_LAYER_2;
	AVD_setDisplayOsdLcdInfo(&Info_lcd);
}

void GUIAVC_DisplayOsdLoutInfo( UW addr )
{
	AVC_ST_OSD_LOUT_INFO Info_lout;
	Info_lout.mColor = GUIAVC_GetColorFormat(FALSE);
	Info_lout.mTopAddr = addr;
	Info_lout.mOsd.mTerminal = (AVC_OUTPUT_TERMINAL)(AVC_OUTPUT_TERMINAL_HDMI | AVC_OUTPUT_TERMINAL_D | AVC_OUTPUT_TERMINAL_RCA | AVC_OUTPUT_TERMINAL_SDI);
	Info_lout.mOsd.mLayer = AVC_OSD_LAYER_2;
	AVD_setDisplayOsdLoutInfo(&Info_lout);
}


//OSD外部出力スケール設定
void GUIAVC_OsdLoutScale(BOOL is90percent)
{
	AVC_ST_LOUT_SCALE	Scale;
	Scale.mOsd.mTerminal = (AVC_OUTPUT_TERMINAL)( AVC_OUTPUT_TERMINAL_HDMI | AVC_OUTPUT_TERMINAL_D | AVC_OUTPUT_TERMINAL_RCA | AVC_OUTPUT_TERMINAL_SDI);

	if( is90percent == TRUE ){
		Scale.mScale = AVC_VIDEO_SCALE_90;
	} else {
		Scale.mScale = AVC_VIDEO_SCALE_100;
	}

	//ZOM2表示へ反映
	Scale.mOsd.mLayer = AVC_OSD_LAYER_2;
	AVD_setOsdLoutScale(&Scale);

	GUIAVC_RequestUpdateOsd(GUIAVC_DISP_LOUT, GUIAVC_UPDATE_NORMAL);
}


//入力プレーンサイズ設定
void GUIAVC_setOsdPlaneSizeLcd(void)
{
	AVC_ST_OSD_PLANE_LCD	PlaneLcd;
	PlaneLcd.mWidth = LCD_W;       // プレーン幅
	PlaneLcd.mHeight = LCD_H;      // プレーン高さ
	PlaneLcd.mOsd.mLcdEvf = (AVC_OUTPUT_LCDEVF)(AVC_OUTPUT_LCDEVF_LCD | AVC_OUTPUT_LCDEVF_EVF);         // LCD/EVF用OSD情報
	// 	ZOM1
	//	PlaneLcd.mMemW = LCD_W;        // メモリ幅
	//	PlaneLcd.mOsd.mLayer = AVC_OSD_LAYER_1;
	//	AVD_setOsdPlaneSizeLcd( &PlaneLcd );
    
	// 	ZOM2
	UH memwidth;
	if(GUIAVC_GetColorFormat(TRUE) == AVC_VIDEO_COLOR_OSD_RGBA8888){
		memwidth = LCD_W * COLOR_SIZE_RGBA8888;      // メモリ幅
	}else{
		memwidth = LCD_W * COLOR_SIZE_RGBA4444;      // メモリ幅
	}
	PlaneLcd.mMemW = memwidth;      // メモリ幅
	PlaneLcd.mOsd.mLayer = AVC_OSD_LAYER_2;
	AVD_setOsdPlaneSizeLcd( &PlaneLcd );
}
void GUIAVC_setOsdPlaneSizeLout(void)
{
	AVC_ST_OSD_PLANE_LOUT	PlaneLout;
	PlaneLout.mWidth = LOUT_W;       // プレーン幅
	PlaneLout.mHeight = LOUT_H;      // プレーン高さ
	PlaneLout.mOsd.mTerminal = (AVC_OUTPUT_TERMINAL)(AVC_OUTPUT_TERMINAL_HDMI | AVC_OUTPUT_TERMINAL_D | AVC_OUTPUT_TERMINAL_RCA | AVC_OUTPUT_TERMINAL_SDI);         // LCD/EVF用OSD情報
	// 	ZOM1
	//	PlaneLout.mMemW = LOUT_W;        // メモリ幅
	//	PlaneLout.mOsd.mLayer = AVC_OSD_LAYER_1;
	//	AVD_setOsdPlaneSizeLout( &PlaneLout );
	// 	ZOM2
	UH memwidth;
	if(GUIAVC_GetColorFormat(FALSE) == AVC_VIDEO_COLOR_OSD_RGBA8888){
		memwidth = LOUT_W * COLOR_SIZE_RGBA8888;      // メモリ幅
	}else{
		memwidth = LOUT_W * COLOR_SIZE_RGBA4444;      // メモリ幅
	}
	PlaneLout.mMemW = memwidth;      // メモリ幅
	PlaneLout.mOsd.mLayer = AVC_OSD_LAYER_2;
	AVD_setOsdPlaneSizeLout( &PlaneLout );
}
