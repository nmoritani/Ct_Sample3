/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#include <string.h>
#include "CtDebugPrint.h"

#ifdef WIN32_GUI_SIM
#include <windows.h>
#include "win_itron.h"
#include "wi_resource.h"
#include "kernel_id.h"
#include "egl.h"
#include "openvg.h"
typedef unsigned int	uint32;
#else
#include <kernel.h>
#include <kernel_id.h>
#include "SysIf.h"
#include "AvcIf.h"
#include "AvcGuiIf.h"
#include "Tmr.h"
#define PANA_ORG_FUNC
#define _DMPNATIVE_
#include "EGL/egl.h"

#include "DMP/eglNative.h"
#include "DMP/eglNativePhlox.h"
#include "DMP/eglDMP.h"
#include "DMP/vgDMPX.h"

#include "geman.h"
#include "gui_main.h"
#include "GUI_OsdDispIf.h"
#endif

#include "mem_mng.h"
#include "gdi.h"

#include "freetype_mono_ovg.h"
#include "freetype_api.h"

#include "gdi_config.h"
#include "gdi_local.h"

//Freetypeを使うときはこのdefineを有効化する
#define USE_FREETYPE_FONTAPI

extern EGLNativeDisplayType native_display;
extern EGLDisplay egldisplay;

extern void dmp_allocator_addr_size_set(uint32 pmem_addr , uint32 logical_addr , uint32 pmem_size);  /* should be called before using lib to set env. */
																										

typedef struct _gfx_plane_info
{
	gdi_window_context *window_context;

} gfx_plane_info;

static gfx_plane_info gfx_plane[GFX_PLANE_MAX] = { NULL, NULL, NULL };


//------------------------------------------------------------------------------
// internal functions
//
// tkmalloc用初期化情報
static SMemMngInit tkMemInfo =
{
	MEM_MNG_STATIC_MEMADDR, MEM_MNG_STATIC_MEMAREA_SIZE,
	{
		{GEVG_MEM_CONF_ID00_SIZE, GEVG_MEM_CONF_ID00_NUM},
		{GEVG_MEM_CONF_ID01_SIZE, GEVG_MEM_CONF_ID01_NUM},
		{GEVG_MEM_CONF_ID02_SIZE, GEVG_MEM_CONF_ID02_NUM},
		{GEVG_MEM_CONF_ID03_SIZE, GEVG_MEM_CONF_ID03_NUM},
		{GEVG_MEM_CONF_ID04_SIZE, GEVG_MEM_CONF_ID04_NUM},
		{GEVG_MEM_CONF_ID05_SIZE, GEVG_MEM_CONF_ID05_NUM},
		{GEVG_MEM_CONF_ID06_SIZE, GEVG_MEM_CONF_ID06_NUM},
		{GEVG_MEM_CONF_ID07_SIZE, GEVG_MEM_CONF_ID07_NUM},
		{GEVG_MEM_CONF_ID08_SIZE, GEVG_MEM_CONF_ID08_NUM},
		{GEVG_MEM_CONF_ID09_SIZE, GEVG_MEM_CONF_ID09_NUM},
		{GEVG_MEM_CONF_ID10_SIZE, GEVG_MEM_CONF_ID10_NUM},
		//		{GEVG_MEM_CONF_ID11_SIZE, GEVG_MEM_CONF_ID11_NUM},
		//		{GEVG_MEM_CONF_ID12_SIZE, GEVG_MEM_CONF_ID12_NUM},
		//		{GEVG_MEM_CONF_ID13_SIZE, GEVG_MEM_CONF_ID13_NUM},
		//		{GEVG_MEM_CONF_ID14_SIZE, GEVG_MEM_CONF_ID14_NUM},
	}
};

GDI_ERRCODE gdi_switch_screen(GDI_HANDLER hdr)
{
	GDI_ERRCODE result;

	if ((gdi_context_base*)hdr == NULL)
		return GDI_CONTEXT_ERROR;

	switch (((gdi_context_base*)hdr)->type) {
	case GDI_CONTEXT_WINDOW:
		result = gdi_switch_window((gdi_window_context*)hdr);
		break;
	case GDI_CONTEXT_PBUFFER:
		result = gdi_switch_pbuffer((gdi_pbuffer_context*)hdr, GDI_DIR_DRAW);
		break;
	default:
		return GDI_CONTEXT_ERROR;
	}
	
	return result;
}


#ifdef WIN32_GUI_SIM
NativeWindowType native_window[GFX_PLANE_MAX];
void GDI_SetNativeWindow(GFX_PLANE_ID plane, NativeWindowType window)
{
	native_window[plane] = window;
}


NativeWindowType GDI_GetNativeWindow(GFX_PLANE_ID plane)
{
	if (NULL == native_window[plane]) {
		native_window[plane] = (NativeWindowType)0x5a5a5a5a;	// dummy
	}

	return native_window[plane];
}
#endif

void GDI_Init(void)
{
	// CPUメモリ初期化(キャッシュ領域可)
	tkMemMngInitialize(&tkMemInfo);

#ifdef WIN32_GUI_SIM
#if defined(USE_SHIVA_VG) || defined(USE_AMANITH_VG)
	InitLibOpenVG(960, 540);
#endif
#else
	// バッファアロケータ初期化(非キャッシュ領域のみ)
    CPU_PurgeCache();  // 非キャッシュ領域書込み前にCacheをPurge
	memset((void *)((unsigned long)GFX_GM_START), 0, GFX_GM_SIZE);
	
	dmp_allocator_addr_size_set((unsigned long)GFX_GM_START, (unsigned long)GFX_GM_START, GFX_GM_SIZE);

	// エンジン初期化
	initGEman();
#endif
	gdi_vg_init(GDI_COLOR_FORMAT_RGBA4444);
}

void GDI_Terminate(void)
{
	gdi_vg_end();
}

#ifndef WIN32_GUI_SIM
// 起動初期のOSD出力設定
void GDI_DisplayOn(void)
{
	// LCD	----------------------
	GUI_ST_DISPLAY_LCD	Display_Lcd;
	Display_Lcd.mIsOn = TRUE;
	Display_Lcd.mOsd.mLcdEvf = (GUI_OUTPUT_LCDEVF)(GUI_OUTPUT_LCDEVF_LCD | GUI_OUTPUT_LCDEVF_EVF);

    // APL用のIFを廃止したため、
	GUIAVC_DisplayOsdLcd(&Display_Lcd);

	// LOUT	----------------------
	GUI_ST_DISPLAY_LOUT Display_Lout;
	Display_Lout.mIsOn = FALSE;
	Display_Lout.mOsd.mTerminal = (GUI_OUTPUT_TERMINAL)(GUI_OUTPUT_TERMINAL_HDMI | GUI_OUTPUT_TERMINAL_SDI);

	GUI_setDisplayOsdLout(&Display_Lout);
}
#endif

GDI_ERRCODE GDI_Update(GDI_HANDLER hdr)
{
	GDI_ERRCODE err = GDI_NO_ERROR;
	gdi_context_base *current_context = NULL;
#ifndef WIN32_GUI_SIM
	static UW last_addr[GFX_PLANE_MAX] = {0,0,0};
#endif
	
	wai_sem(GDI_SEMID_DRAW);

	if (hdr == GDI_INVALID_ID) {
		hdr = (GDI_HANDLER)gdi_get_current_context();
	} else {
		err = gdi_switch_screen(hdr);
		if (GDI_NO_ERROR != err)
			goto EXIT;
	}
	
	if ((current_context = gdi_get_current_context()) == NULL) {
		err = GDI_CONTEXT_ERROR;
		goto EXIT;
	}
#ifdef WIN32_GUI_SIM
	if (current_context->type == GDI_CONTEXT_WINDOW) {
		gdi_window_context * window_context = (gdi_window_context *)current_context;
		eglSwapBuffers(egldisplay, window_context->eglsurface);
	} else if (current_context->type == GDI_CONTEXT_PBUFFER) {
		vgFinish();
	}
#else	
	if (current_context->type == GDI_CONTEXT_WINDOW) {
		gdi_window_context * window_context = (gdi_window_context *)current_context;
		void *addr = NULL;

		
		BOOL isLcd = TRUE;
		BOOL isRGBA8888 = FALSE;

		switch (window_context->plane_id) {
		case GFX_PLANE_LCD:{
			eglNativeQueryWindowPointer(native_display, window_context->window, EGL_NATIVE_PHYSICAL_ADDRESS, (void **)&addr);

			// 描画バッファのアドレスが、前回表示面としてAVCへ通知したアドレスと同じだった場合、表示面側に描画する事になってしまう為スキップする
			if((UW)addr != last_addr[GFX_PLANE_LCD]){
				eglSwapBuffers(egldisplay, window_context->eglsurface);
				
				//入力プレーンサイズ設定	RGBA4444/8888を同時にAVCへ通知する
				isLcd = TRUE;
				switch(window_context->format){
				case GDI_COLOR_FORMAT_RGBA8888:
					isRGBA8888 = TRUE;
					break;
				case GDI_COLOR_FORMAT_RGBA4444:
				default:
					isRGBA8888 = FALSE;
					break;
				}
				GUIAVC_ChangeColorFormat(isLcd, isRGBA8888);

			}else{
				err = GDI_HW_BUSY_ERROR;

				if (addr != window_context->plane_buffer0) {
					addr = window_context->plane_buffer0;
				} else if (addr != window_context->plane_buffer1) {
					addr = window_context->plane_buffer1;
				} else {
					CtDebugPrint(CtDbg, "GDI Plane addr error\n");
				}
			}
			
			//入力プレーンサイズwithカラーフォーマット設定
			GUIAVC_setOsdPlaneSizeLcd();
			//OSD表示アドレス設定
			GUIAVC_DisplayOsdLcdInfo((UW)addr);

			GUIAVC_updateOsd(GUIAVC_DISP_LCD, GUIAVC_UPDATE_NORMAL);
			last_addr[GFX_PLANE_LCD] = (UW)addr;
			break;
		}
		case GFX_PLANE_LOUT:{
			eglNativeQueryWindowPointer(native_display, window_context->window, EGL_NATIVE_PHYSICAL_ADDRESS, (void **)&addr);

			// 描画バッファのアドレスが、前回表示面としてAVCへ通知したアドレスと同じだった場合、表示面側に描画する事になってしまう為スキップする
			if((UW)addr != last_addr[GFX_PLANE_LOUT]){
				eglSwapBuffers(egldisplay, window_context->eglsurface);
				
				//入力プレーンサイズ設定	RGBA4444/8888を同時にAVCへ通知する
				isLcd = FALSE;
				switch(window_context->format){
				case GDI_COLOR_FORMAT_RGBA8888:
					isRGBA8888 = TRUE;
					break;
				case GDI_COLOR_FORMAT_RGBA4444:
				default:
					isRGBA8888 = FALSE;
					break;
				}

				GUIAVC_ChangeColorFormat(isLcd, isRGBA8888);

			}else{
				err = GDI_HW_BUSY_ERROR;
				
				if (addr != window_context->plane_buffer0) {
					addr = window_context->plane_buffer0;
				} else if (addr != window_context->plane_buffer1) {
					addr = window_context->plane_buffer1;
				} else {
					CtDebugPrint(CtDbg, "GDI Plane addr error\n");
				}
			}

			//入力プレーンサイズwithカラーフォーマット設定
			GUIAVC_setOsdPlaneSizeLout();
			//OSD表示アドレス設定
			GUIAVC_DisplayOsdLoutInfo((UW)addr);

			//	if (gd_vf_change == TRUE) {
			//[外部出力OSD表示 90％/100％縮尺切替]
			AVC_ST_LOUT_SCALE	Scale;
			Scale.mOsd.mTerminal = (AVC_OUTPUT_TERMINAL)( AVC_OUTPUT_TERMINAL_HDMI | AVC_OUTPUT_TERMINAL_D | AVC_OUTPUT_TERMINAL_RCA | AVC_OUTPUT_TERMINAL_SDI);

			//スケール設定
			if( GD_isLoutScale90Percent() == TRUE ){
				Scale.mScale = AVC_VIDEO_SCALE_90;
			} else {
				Scale.mScale = AVC_VIDEO_SCALE_100;
			}
			//ZOM1表示へ反映
			Scale.mOsd.mLayer = AVC_OSD_LAYER_1;
			AVD_setOsdLoutScale(&Scale);
			//ZOM2表示へ反映
			Scale.mOsd.mLayer = AVC_OSD_LAYER_2;
			AVD_setOsdLoutScale(&Scale);
			
			//		gd_vf_change = FALSE;
			//	}
			

			// AVIOへ表示更新要求
			GUIAVC_updateOsd(GUIAVC_DISP_LOUT, GUIAVC_UPDATE_NORMAL);
			last_addr[GFX_PLANE_LOUT] = (UW)addr;
			break;
		}
		default:
			break;
		}
		
	} else if (current_context->type == GDI_CONTEXT_PBUFFER) {
		vgFinish();
	}
#endif
 EXIT:
	sig_sem(GDI_SEMID_DRAW);
	
	return err;
}



GDI_ERRCODE GDI_CreateContext(GDI_COLOR_FORMAT format)
{
	gdi_create_context(format);
#ifdef USE_FREETYPE_FONTAPI
	ft_service_terminate();
	ft_service_init();
#else
	font_service_quit();
	font_service_init();
#endif
	
	//bmpfont_service_quit();
	//bmpfont_service_init();
	
	return GDI_NO_ERROR;
}
	
void GDI_DeleteContext(void)
{
#ifdef USE_FREETYPE_FONTAPI
	ft_service_terminate();
#endif
	gdi_delete_context();
}
	
GDI_HANDLER GDI_CreateScreen(int width, int height, GDI_COLOR_FORMAT format, GFX_PLANE_ID plane)
{
	gdi_window_context *window_context;
	unsigned char *buf0 = NULL, *buf1 = NULL;
	GDI_HANDLER hdr = GDI_INVALID_ID;

	wai_sem(GDI_SEMID_DRAW);
	
#ifdef WIN32_GUI_SIM
	if ((window_context = gdi_create_window(width, height, format, plane, NULL, NULL)) == NULL) {
		window_context = GDI_INVALID_ID;
		goto EXIT;
	}
#else
	switch (plane) {
	case GFX_PLANE_LCD:
		buf0 = GFX_PLANE_LCD0;
		buf1 = GFX_PLANE_LCD1;
		break;
	case GFX_PLANE_LOUT:
		buf0 = GFX_PLANE_LOUT0;
		buf1 = GFX_PLANE_LOUT1;
		break;
	default:
		window_context = GDI_INVALID_ID;
		goto EXIT;
	}
	
	if ((window_context = gdi_create_window(width, height, format, plane, buf0, buf1)) == NULL) {
		window_context = GDI_INVALID_ID;
		goto EXIT;
	}
#endif
	gfx_plane[plane].window_context = window_context;
	
 EXIT:
	sig_sem(GDI_SEMID_DRAW);

	return (GDI_HANDLER)window_context;
}

extern GDI_ERRCODE GDI_DeleteScreen(GDI_HANDLER hdr)
{
	gdi_window_context *window_context;
	GDI_ERRCODE err = GDI_NO_ERROR;

	wai_sem(GDI_SEMID_DRAW);

	window_context = (gdi_window_context *)hdr;

	if (hdr == (GDI_HANDLER)NULL) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}

	gdi_delete_window(window_context);

 EXIT:
	sig_sem(GDI_SEMID_DRAW);

	return err;
}

GDI_ERRCODE GDI_SwitchScreen(GDI_HANDLER hdr)
{
	GDI_ERRCODE err;

	wai_sem(GDI_SEMID_DRAW);
	err = gdi_switch_window((gdi_window_context *)hdr);
	sig_sem(GDI_SEMID_DRAW);

	return err;
}


GDI_HANDLER GDI_CreateDrawable(int width, int height, GDI_COLOR_FORMAT format)
{
	gdi_pbuffer_context *pbuffer_context;

	wai_sem(GDI_SEMID_DRAW);
	if ((pbuffer_context = gdi_create_pbuffer(width, height, format)) == NULL) {
		sig_sem(GDI_SEMID_DRAW);
		return GDI_INVALID_ID;
	}
	sig_sem(GDI_SEMID_DRAW);

	return (GDI_HANDLER)pbuffer_context;
}

GDI_ERRCODE GDI_DeleteDrawable(GDI_HANDLER hdr)
{
	wai_sem(GDI_SEMID_DRAW);
	gdi_delete_pbuffer((gdi_pbuffer_context *)hdr);
	sig_sem(GDI_SEMID_DRAW);

	return GDI_NO_ERROR;
}

GDI_ERRCODE GDI_SwitchDrawable(GDI_HANDLER hdr, GDI_DIR dir)
{
	GDI_ERRCODE result;
	
	wai_sem(GDI_SEMID_DRAW);
	result = gdi_switch_pbuffer((gdi_pbuffer_context *)hdr, dir);
	sig_sem(GDI_SEMID_DRAW);
	
	return result;
}

GDI_HANDLER GDI_GetCurrentHandler(void)
{
	GDI_HANDLER hdr;

	wai_sem(GDI_SEMID_DRAW);
	hdr = (GDI_HANDLER)gdi_get_current_context();
	sig_sem(GDI_SEMID_DRAW);

	return hdr;
}





//------------------------------------------------------------------------------
// matrix
//
#define GDI_MATRIX_SIZE	9

static void gdi_transform_loadIdentity(VGfloat *currentBaseMatrix)
{
	if (currentBaseMatrix == NULL)
		return;
	
	currentBaseMatrix[0] = 1.0f;
	currentBaseMatrix[1] = 0.0f;
	currentBaseMatrix[2] = 0.0f;
	currentBaseMatrix[3] = 0.0f;
	currentBaseMatrix[4] = 1.0f;
	currentBaseMatrix[5] = 0.0f;
	currentBaseMatrix[6] = 0.0f;
	currentBaseMatrix[7] = 0.0f;
	currentBaseMatrix[8] = 1.0f;
}

static void gdi_transform_multMatrix(VGfloat *currentBaseMatrix, VGfloat *srcMatrix)
{
	VGfloat tmpMatrix[GDI_MATRIX_SIZE];
	int i;

	if (currentBaseMatrix == NULL || srcMatrix == NULL)
		return;
	
	for (i = 0; i < GDI_MATRIX_SIZE; i++) {
		tmpMatrix[i] = *(currentBaseMatrix+i);
	}
	
	currentBaseMatrix[0] = *(tmpMatrix+0) * *(srcMatrix+0) + *(tmpMatrix+3) * *(srcMatrix+1) + *(tmpMatrix+6) * *(srcMatrix+2);
	currentBaseMatrix[3] = *(tmpMatrix+0) * *(srcMatrix+3) + *(tmpMatrix+3) * *(srcMatrix+4) + *(tmpMatrix+6) * *(srcMatrix+5);
	currentBaseMatrix[6] = *(tmpMatrix+0) * *(srcMatrix+6) + *(tmpMatrix+3) * *(srcMatrix+7) + *(tmpMatrix+6) * *(srcMatrix+8);
	currentBaseMatrix[1] = *(tmpMatrix+1) * *(srcMatrix+0) + *(tmpMatrix+4) * *(srcMatrix+1) + *(tmpMatrix+7) * *(srcMatrix+2);
	currentBaseMatrix[4] = *(tmpMatrix+1) * *(srcMatrix+3) + *(tmpMatrix+4) * *(srcMatrix+4) + *(tmpMatrix+7) * *(srcMatrix+5);
	currentBaseMatrix[7] = *(tmpMatrix+1) * *(srcMatrix+6) + *(tmpMatrix+4) * *(srcMatrix+7) + *(tmpMatrix+7) * *(srcMatrix+8);
	currentBaseMatrix[2] = *(tmpMatrix+2) * *(srcMatrix+0) + *(tmpMatrix+5) * *(srcMatrix+1) + *(tmpMatrix+8) * *(srcMatrix+2);
	currentBaseMatrix[5] = *(tmpMatrix+2) * *(srcMatrix+3) + *(tmpMatrix+5) * *(srcMatrix+4) + *(tmpMatrix+8) * *(srcMatrix+5);
	currentBaseMatrix[8] = *(tmpMatrix+2) * *(srcMatrix+6) + *(tmpMatrix+5) * *(srcMatrix+7) + *(tmpMatrix+8) * *(srcMatrix+8);
}

static void gdi_transform_translate(VGfloat *currentBaseMatrix, VGfloat tx, VGfloat ty)
{
	VGfloat tmpMatrix[GDI_MATRIX_SIZE];

	if (currentBaseMatrix == NULL)
		return;
	
	tmpMatrix[0] = 1.0f;
	tmpMatrix[3] = 0.0f;
	tmpMatrix[6] = tx;
	tmpMatrix[1] = 0.0f;
	tmpMatrix[4] = 1.0f;
	tmpMatrix[7] = ty;
	tmpMatrix[2] = 0.0f;
	tmpMatrix[5] = 0.0f;
	tmpMatrix[8] = 1.0f;
	
	gdi_transform_multMatrix(currentBaseMatrix, tmpMatrix);
}

static void gdi_transform_scale(VGfloat *currentBaseMatrix, VGfloat sx, VGfloat sy)
{
	VGfloat tmpMatrix[GDI_MATRIX_SIZE];

	if (currentBaseMatrix == NULL)
		return;
	
	tmpMatrix[0] = sx;
	tmpMatrix[3] = 0.0f;
	tmpMatrix[6] = 0.0f;
	tmpMatrix[1] = 0.0f;
	tmpMatrix[4] = sy;
	tmpMatrix[7] = 0.0f;
	tmpMatrix[2] = 0.0f;
	tmpMatrix[5] = 0.0f;
	tmpMatrix[8] = 1.0f;
	
	gdi_transform_multMatrix(currentBaseMatrix, tmpMatrix);
}


//------------------------------------------------------------------------------
// draw
//
static VGBlendMode gdi_get_vgblend(GDI_BLEND_MODE blend)
{
	VGBlendMode blend_mode;
	
	switch (blend) {
	case GDI_BLEND_MODE_SRC:
		blend_mode = VG_BLEND_SRC;
		break;
	case GDI_BLEND_MODE_SRC_OVER:
	default:
		blend_mode = VG_BLEND_SRC_OVER;
		break;
	}
	
	return blend_mode;
}

static void gdi_get_vgcoords(gdi_context_base *context, VGint *coords, GDI_REGION *region)
{
	if (context == NULL || coords == NULL || region == NULL)
		return;
	
	coords[0] = region->x;
	coords[1] = (context->type == GDI_CONTEXT_WINDOW)
		? context->aln_height - (region->y + region->height)
		: region->y;	//context->height - (region->y + region->height);
	coords[2] = region->width;
	coords[3] = region->height;
}

static void gdi_enable_scissoring(VGint *clip)
{
	if (NULL == clip) {
		return;
	}
	vgSeti(VG_SCISSORING, VG_TRUE);
	vgSetiv(VG_SCISSOR_RECTS, 4, clip);/* parasoft-suppress BD-PB-NOTINIT */
}

static void gdi_disable_scissoring()
{
	vgSeti(VG_SCISSORING, VG_FALSE);
}


typedef struct _DRAW_AREA_INFO {
	GDI_REGION		area;
	VGint		clipArea[4];
	VGfloat			draw_x;	//描画開始位置(X)微調整用
	VGfloat			draw_y;	//描画開始位置(Y)微調整用
	VGfloat			tx;
	VGfloat			ty;
	VGfloat			sx;
	VGfloat			sy;

} DRAW_AREA_INFO;

static int get_draw_start_x(HALIGN halign, int src_width, int draw_width)
{
	switch (halign) {
	case HALIGN_CENTER:
		return (int)((draw_width * 0.5f) - (src_width * 0.5f));	/* pgr0351 */

	case HALIGN_RIGHT:
		return draw_width - src_width;

	case HALIGN_LEFT:
	default:
		return 0;
	}
}

static int get_draw_start_y(VALIGN valign, int src_height, int draw_height)
{
	float y;


	//	if (draw_height <= src_height) {
	//		return 0;	//描画領域が元サイズ以下の場合は縦位置の調整しない
	//	}

	//描画エリアの縦サイズよりソースの方が小さい場合、上下方向の位置を合わせる
	y = (float)(draw_height - src_height);

	switch (valign) {
	case VALIGN_TOP:
		y = 0.0f;
		break;
	case VALIGN_MIDDLE:
		y *= 0.5f;
		break;
	case VALIGN_BOTTOM:
		y *= 1.0f;
		break;
	case VALIGN_DEFAULT:
	default:
		y *= 0.6f;		//やや下寄せ
		break;
	}
	return (int)y;
}

static void get_draw_area_font(
	DRAW_AREA_INFO		*pDrawAreaInfo,
	int					areaWidth,
	int					areaHeight,
	int					fontWidth,
	int					fontHeight,
	float				strokeWidth,
	int					bmpHeight,
	int					lineUnder,
	GDI_FONT_STYLE		*pStyle)
{
	float	draw_width = 0;
	float	draw_height = 0;
	float	image_width = 0.0f;
	float	image_height = 0.0f;
	float	draw_x = 0.0f;
	float	draw_y = 0.0f;
	float	sx = 1.0f;
	float	sy = 1.0f;
	int		tx = 0;
	int 	ty = 0;

	if ((NULL == pDrawAreaInfo) || (NULL == pStyle)) {
		pDrawAreaInfo->area.x = 0;
		pDrawAreaInfo->area.y = 0;
		pDrawAreaInfo->area.width = 0;
		pDrawAreaInfo->area.height = 0;
		pDrawAreaInfo->sx = 1.0f;
		pDrawAreaInfo->sy = 1.0f;
		return;
	}

	draw_width = (float)areaWidth;
	draw_height = (float)areaHeight;
	
	// 拡縮倍率設定
	image_width = fontWidth + strokeWidth;
	draw_x = (float)(strokeWidth * 0.5f);

	if ((pStyle->auto_adjust == AUTO_ADJUST_ENABLE) && ((pStyle->font_size == 0) || (pStyle->font_size > draw_height))) {
		image_height = bmpHeight + strokeWidth;					//自動調整ありの場合、フォントの絵(空白部分も含む)を使用

		//拡縮倍率計算
		sy = (float)draw_height / (float)image_height;
		sx = sy;								//フォントの縦横比は縦に合わせる
		if (draw_width < (image_width * sx)) {	//ただし、描画領域を出る場合、描画領域に合わせる
			float sa = draw_width / (image_width * sx);
			sx *= sa;
		}

	} else {
		image_height = fontHeight + lineUnder + strokeWidth;	//自動調整なしの場合、フォントの形をそのまま使用
		ty = get_draw_start_y(pStyle->valign, (int)image_height, (int)draw_height);		//縦位置の調整(上寄せ、下寄せなど)
	}

	tx = get_draw_start_x(pStyle->halign, (int)(image_width * sx), (int)draw_width);

	pDrawAreaInfo->area.x = (short)(tx + draw_x);
	pDrawAreaInfo->area.y = (short)(ty + draw_y);
	pDrawAreaInfo->area.width = (short)(draw_x + (image_width * sx));
	pDrawAreaInfo->area.height = (short)(draw_y + (image_height * sy));
	pDrawAreaInfo->sx = sx;
	pDrawAreaInfo->sy = sy;
}

static void get_draw_area_image(
	DRAW_AREA_INFO		*pDrawAreaInfo,
	int					areaWidth,
	int					areaHeight,
	int					imageWidth,
	int					imageHeight,
	GDI_IMAGE_STYLE		*pStyle)
{
	float	draw_width = 0;
	float	draw_height = 0;
	float	image_width = 0;
	float	image_height = 0;
	int		draw_x = 0;
	int		draw_y = 0;
	float	sx = 1.0f;
	float	sy = 1.0f;

	if ((NULL == pDrawAreaInfo) || (NULL == pStyle)) {
		pDrawAreaInfo->area.x = 0;
		pDrawAreaInfo->area.y = 0;
		pDrawAreaInfo->area.width = 0;
		pDrawAreaInfo->area.height = 0;
		pDrawAreaInfo->sx = 1.0f;
		pDrawAreaInfo->sy = 1.0f;
		return;
	}

	draw_width = (float)areaWidth;
	draw_height = (float)areaHeight;
	image_width = (float)imageWidth;
	image_height = (float)imageHeight;
	
	// 拡縮倍率設定
	if (pStyle->auto_adjust == AUTO_ADJUST_ENABLE) {
		switch (pStyle->aspect_ratio) {
		case ASPECT_RATIO_SAME:
			sx = draw_width / image_width;
			if ((image_height * sx) > draw_height) {
				sx = draw_height / image_height;
				sy = sx;
				draw_x = get_draw_start_x(pStyle->halign, (int)(image_width * sx), (int)draw_width);
			} else {
				sy = sx;
				draw_y = get_draw_start_y(pStyle->valign, (int)(image_height * sy), (int)draw_height);
			}
			break;
		case ASPECT_RATIO_DEFAULT:
		default:
			sx = draw_width / image_width;
			sy = draw_height / image_height;
			break;
			break;
		}
	} else {
		draw_x = get_draw_start_x(pStyle->halign, (int)image_width, (int)draw_width);
		draw_y = get_draw_start_y(pStyle->valign, (int)image_height, (int)draw_height);
	}

	
	pDrawAreaInfo->area.x = draw_x;
	pDrawAreaInfo->area.y = draw_y;
	pDrawAreaInfo->area.width = (short)(draw_x + (image_width * sx));
	pDrawAreaInfo->area.height = (short)(draw_y + (image_height * sy));
	pDrawAreaInfo->sx = sx;
	pDrawAreaInfo->sy = sy;
	return;
}


/**
 * キャッシュされたPATHからSVGデータをSurfaceへ描画
 *
 * [in/out]
 *  @param res:SVGのリソース情報
 *    -member type          ロータイプ
 *  @param cliprect:描画範囲
 * [out]
 *  @retrun なし
 *
 */
static GDI_CACHE_SVG * gdi_create_cache_svg(GDI_IMAGE_SVG *svg)
{
	GDI_CACHE_SVG *cache_svg = NULL;

	if (svg == NULL)
		goto EXIT;
	
	if (svg->type != GDI_IMAGE_TYPE_SVG) {
		goto EXIT;
	}

	if ((cache_svg = gdi_alloc_cache_svg()) == NULL) {
		goto EXIT;
	}

	if ((cache_svg->path = gdi_create_parts(svg)) == NULL) {
		gdi_free_cache_svg(cache_svg);
		cache_svg = NULL;
		goto EXIT;
	}

 EXIT:
	return cache_svg;
}

GDI_CACHE_SVG * GDI_CreateCacheSVG(GDI_IMAGE_SVG *svg)
{
	GDI_CACHE_SVG *cache_svg = NULL;
	
	wai_sem(GDI_SEMID_DRAW);
	cache_svg = gdi_create_cache_svg(svg);
	sig_sem(GDI_SEMID_DRAW);

	return cache_svg;
}

GDI_ERRCODE GDI_DrawSVG(GDI_DRAW_BASE *info, GDI_DRAW_SVG *info_svg, GDI_CACHE_SVG *cache)
{
	GDI_ERRCODE err = GDI_NO_ERROR;
	GDI_CACHE_SVG *cache_svg = NULL;
	VGPaint	stroke_paint = VG_INVALID_HANDLE;
	VGPaint	fill_paint = VG_INVALID_HANDLE;
	
	DRAW_AREA_INFO	drawAreaInfo;
	VGint draw_width, draw_height;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat tx, ty;
	VGfloat matrix[9] = {0.0f};
	gdi_context_base* context = gdi_get_current_context();
	int tmp = 0;
	

	if ((info == NULL) || (info_svg == NULL))
		return GDI_ILLEGAL_ARGUMENT_ERROR;


	wai_sem(GDI_SEMID_DRAW);

	if ((info->draw_area.width <= 0.0f) || (info->draw_area.height <= 0.0f)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}

	if ((cache_svg = cache) == NULL) {
		if ((cache_svg = gdi_create_cache_svg(info_svg->svg)) == NULL) {
			err = GDI_OUT_OF_MEMORY_ERROR;
			goto EXIT;
		}
	}

	if (info_svg->stroke.type != 0) {	/* pgr0838 */
		err = gdi_create_color(&info_svg->stroke, &stroke_paint, 1.0f);
		if (GDI_NO_ERROR != err) {
			goto EXIT;
		}
	}

	if (info_svg->fill.type != 0) {		/* pgr0838 */
		err = gdi_create_color(&info_svg->fill, &fill_paint, 1.0f);
		if (GDI_NO_ERROR != err) {
			goto EXIT;
		}
	}

	if (info_svg->image_style.valign == VALIGN_BOTTOM) {
		tmp = 1;
	}

	
	draw_width = info->draw_area.width;
	draw_height = info->draw_area.height;
	
#if WIN32_GUI_SIM
	//AmanithVGのバグ対策。クリップエリアの境界線上に描画すると図が正しく描画されないことがあるので、拡縮倍率計算で図を小さくして回避する
	if (info->draw_area.width == info->clip_area.width) {
		draw_width = (int)(info->draw_area.width - (info->draw_area.width * 0.0001));
	}
	if (info->draw_area.height == info->clip_area.height) {
		draw_height = (int)(info->draw_area.height - (info->draw_area.height * 0.0001));
	}
#endif
	
	get_draw_area_image(&drawAreaInfo, draw_width, draw_height,
						info_svg->svg->width, info_svg->svg->height, &info_svg->image_style);
	drawAreaInfo.area.x += info->draw_area.x;
	drawAreaInfo.area.y += info->draw_area.y;
	
	gdi_get_vgcoords(context, rect, &drawAreaInfo.area);
	gdi_get_vgcoords(context, clip, &info->clip_area);

	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)(rect[1] + rect[3]) : (VGfloat)rect[1];
	drawAreaInfo.sy *= (context->type == GDI_CONTEXT_WINDOW)  ? -1.0f : 1.0f;	//パスは上下が反転しているため、引っくり返す
	
	gdi_enable_scissoring(clip);
	
	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	
	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, drawAreaInfo.sx, drawAreaInfo.sy);
	vgLoadMatrix(matrix);

	gdi_draw_parts(cache_svg->path, stroke_paint, fill_paint, 1.0f);

	gdi_disable_scissoring();

 EXIT:
	if ((cache == NULL) && (cache_svg != NULL)) {
		gdi_free_cache_svg(cache_svg);
	}

	if (stroke_paint != VG_INVALID_HANDLE)	vgDestroyPaint(stroke_paint);
	if (fill_paint != VG_INVALID_HANDLE)	vgDestroyPaint(fill_paint);
	sig_sem(GDI_SEMID_DRAW);

	return err;
}

/**
 * BitmapイメージからvgImageを生成
 *
*/
static VGImage gdi_create_bitmap_image(GDI_IMAGE_BITMAP *bitmap)
{
	VGImage vg_image = VG_INVALID_HANDLE;
	VGImageFormat format;

	if (bitmap == NULL) {
		return VG_INVALID_HANDLE;
	}
	
	switch (bitmap->type) {
	case GDI_IMAGE_TYPE_16BPP:
		format = VG_sRGBA_4444;
		break;
	case GDI_IMAGE_TYPE_32BPP:
		format = VG_sRGBA_8888;
		break;
	default:
		return VG_INVALID_HANDLE;
	}

#ifdef WIN32_GUI_SIM
	vg_image = vgCreateImage(format, bitmap->width, bitmap->height, VG_IMAGE_QUALITY_FASTER);
	vgImageSubData(vg_image, bitmap->data, bitmap->buf_width, format, 0, 0, bitmap->buf_width, bitmap->height);
#else
	VGint buf_size = bitmap->buf_width * bitmap->buf_height;
	void *buf_addr = (void *)((unsigned long)bitmap->data & 0x3FFFFF80);	// DMP対応。アドレス指定の上位2bitを０固定とする
	vg_image = vgCreateImageStandardDataDMP(format, bitmap->width, bitmap->height, buf_size, buf_addr, VG_IMAGE_QUALITY_FASTER);
#endif
	return vg_image;
}

/**
 * キャッシュされたPNGデータをBitmapに変換し、Surfaceへ描画
 *
 * [in/out]
 *  @param hdr:
 *  @param info:
 *    -member blend         描画方法
 *    -member clip_area     クリップ範囲
 *    -member draw_area     描画範囲
 *    -member bitmap        bitmapイメージのアドレス
 *    -member cache_bitmap  キャッシュ情報
 *  @param cache:キャッシュ情報
 * [out]
 *  @retrun エラーコード
 *
 */
static GDI_CACHE_BITMAP *gdi_create_cache_bitmap(GDI_IMAGE_BITMAP *bitmap)
{
	GDI_CACHE_BITMAP *cache_bitmap = NULL;
	VGint buf_size;
	void *buf_addr;

	if (bitmap == NULL)
		goto EXIT;
	
	if ((bitmap->type != GDI_IMAGE_TYPE_16BPP) && (bitmap->type != GDI_IMAGE_TYPE_32BPP)) {
		goto EXIT;
	}

	if ((cache_bitmap = gdi_alloc_cache_bitmap()) == NULL) {
		goto EXIT;
	}

	buf_size = bitmap->buf_width * bitmap->buf_height;
	buf_addr = (void *)((unsigned long)bitmap->data & 0x3FFFFF80);	// DMP対応。アドレス指定の上位2bitを０固定とする
	
	cache_bitmap->vg_image = gdi_create_bitmap_image(bitmap);

	if (cache_bitmap->vg_image == VG_INVALID_HANDLE) {
		gdi_free_cache_bitmap(cache_bitmap);
		cache_bitmap = NULL;
		goto EXIT;
	}

 EXIT:
	return cache_bitmap;
}

GDI_CACHE_BITMAP *GDI_CreateCacheBitmap(GDI_IMAGE_BITMAP *bitmap)
{
	GDI_CACHE_BITMAP *cache_bitmap = NULL;
	
	wai_sem(GDI_SEMID_DRAW);
	cache_bitmap = gdi_create_cache_bitmap(bitmap);
	sig_sem(GDI_SEMID_DRAW);

	return cache_bitmap;
}


GDI_ERRCODE GDI_DrawBitmap(GDI_DRAW_BASE *info, GDI_DRAW_BITMAP* info_bitmap, GDI_CACHE_BITMAP *cache)
{
	GDI_CACHE_BITMAP *cache_bitmap = NULL;
	GDI_IMAGE_BITMAP *bitmap = NULL;
	VGfloat tx, ty;
	
	DRAW_AREA_INFO	drawAreaInfo;
	VGint draw_width, draw_height;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat matrix[9] = {0.0f};
	GDI_ERRCODE	err = GDI_NO_ERROR;
	gdi_context_base* context = gdi_get_current_context();

	if ((info == NULL) || (info_bitmap == NULL) || ((bitmap = info_bitmap->bitmap) == NULL)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}
	
	wai_sem(GDI_SEMID_DRAW);

	if ((info->draw_area.width <= 0.0f) || (info->draw_area.height <= 0.0f)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}

	if ((cache_bitmap = cache) == NULL) {
		if ((cache_bitmap = gdi_create_cache_bitmap(bitmap)) == NULL) {
			err = GDI_OUT_OF_MEMORY_ERROR;
			goto EXIT;
		}
	}

	draw_width = info->draw_area.width;
	draw_height = info->draw_area.height;
	
	get_draw_area_image(&drawAreaInfo, draw_width, draw_height,
						info_bitmap->bitmap->width, info_bitmap->bitmap->height, &info_bitmap->image_style);
	drawAreaInfo.area.x += info->draw_area.x;
	drawAreaInfo.area.y += info->draw_area.y;
	
	gdi_get_vgcoords(context, rect, &drawAreaInfo.area);
	gdi_get_vgcoords(context, clip, &info->clip_area);

	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)(rect[1] + rect[3]) : (VGfloat)rect[1];
	drawAreaInfo.sy *= (context->type == GDI_CONTEXT_WINDOW)  ? -1.0f : 1.0f;	//パスは上下が反転しているため、引っくり返す
	
	gdi_enable_scissoring(clip);

	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, drawAreaInfo.sx, drawAreaInfo.sy);
	vgLoadMatrix(matrix);

	vgDrawImage(cache_bitmap->vg_image);

	gdi_disable_scissoring();				//終了処理

	if (cache == NULL) {
		gdi_free_cache_bitmap(cache_bitmap);
	}

 EXIT:
	sig_sem(GDI_SEMID_DRAW);

	return err;
}

/**
 * YUVイメージからvgImageを生成
 *
*/
static VGImage gdi_create_yuv_image(GDI_IMAGE_YUV *yuv)
{
	VGImage vg_image = VG_INVALID_HANDLE;
	
	if (yuv == NULL)
		return VG_INVALID_HANDLE;
	
#ifdef WIN32_GUI_SIM
	//シミュレータではYUV変換ができないので処理せずにそのまま返す.
#else
	int y_addr = ((int)yuv->y_plane) & 0x3FFFFF80;	// DMP対応。アドレス指定の上位2bitを０固定とする
	int c_addr = ((int)yuv->c_plane) & 0x3FFFFF80;	// DMP対応。アドレス指定の上位2bitを０固定とする
	int y_plane_size = yuv->plane_stride * yuv->plane_height;
	int c_plane_size = yuv->plane_stride * (yuv->plane_height / 2);
	VGImageFormat format;

	switch (yuv->type) {
	case GDI_IMAGE_TYPE_YCbCr:
	case GDI_IMAGE_TYPE_YUV420S:
		format = VG_sYUV_420_SEMIPLANAR_DMP;
		break;

	default:
		return VG_INVALID_HANDLE;
	}

	vg_image = vgCreateImageStandardDataYUVsemiplanarDMP(
		format, yuv->plane_stride, yuv->plane_height,
		y_plane_size, c_plane_size, (const void*)y_addr, (const void*)c_addr,
		VG_IMAGE_QUALITY_FASTER);
#endif
	return vg_image;
}

/**
 * YUVイメージの描画関数
 *
*/
GDI_ERRCODE GDI_DrawYUV(GDI_DRAW_BASE *info, GDI_DRAW_YUV* info_yuv)
{
	GDI_IMAGE_YUV* yuv = NULL;
	VGfloat tx, ty;
	VGint draw_width, draw_height;
	DRAW_AREA_INFO	drawAreaInfo;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat matrix[9] = {0.0f};
	GDI_ERRCODE	err = GDI_NO_ERROR;

	VGImage vg_image = VG_INVALID_HANDLE;
	gdi_context_base* context = gdi_get_current_context();

	if ((info == NULL) || (info_yuv == NULL) || ((yuv = info_yuv->yuv) == NULL)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}
	
	wai_sem(GDI_SEMID_DRAW);
	
	//VGImageの作成
	vg_image = gdi_create_yuv_image(yuv);
	if (VG_INVALID_HANDLE == vg_image) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	};

	draw_width = info->draw_area.width;
	draw_height = info->draw_area.height;

	get_draw_area_image(&drawAreaInfo, draw_width, draw_height,
						info_yuv->yuv->width, info_yuv->yuv->height, &info_yuv->image_style);
	drawAreaInfo.area.x += info->draw_area.x;
	drawAreaInfo.area.y += info->draw_area.y;
	
	gdi_get_vgcoords(context, rect, &drawAreaInfo.area);
	gdi_get_vgcoords(context, clip, &info->clip_area);

	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)(rect[1] + rect[3]) : (VGfloat)rect[1];
	drawAreaInfo.sy *= (context->type == GDI_CONTEXT_WINDOW)  ? -1.0f : 1.0f;	//パスは上下が反転しているため、引っくり返す

	gdi_enable_scissoring(clip);		//描画領域の準備

	//画像描画
	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, drawAreaInfo.sx, drawAreaInfo.sy);
	vgLoadMatrix(matrix);

	vgDrawImage(vg_image);

	gdi_disable_scissoring();				//終了処理

EXIT:
	if (vg_image != VG_INVALID_HANDLE)	vgDestroyImage(vg_image);
	sig_sem(GDI_SEMID_DRAW);
	return err;
}

GDI_ERRCODE GDI_DrawDrawable(GDI_DRAW_BASE *info, GDI_DRAW_DRAWABLE* info_drawable)
{
	GDI_HANDLER drawable = GDI_INVALID_ID;
	GDI_ERRCODE err = GDI_NO_ERROR;
	
	DRAW_AREA_INFO	drawAreaInfo;
	VGint draw_width, draw_height;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat tx, ty;
	VGfloat matrix[9] ={0.0f};
	gdi_pbuffer_context *pbuffer_context;
	gdi_context_base* context = gdi_get_current_context();

	wai_sem(GDI_SEMID_DRAW);

	if ((info == NULL) || (info_drawable == NULL) || ((drawable = info_drawable->drawable) == GDI_INVALID_ID)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}
	
	pbuffer_context = (gdi_pbuffer_context *)drawable;

	draw_width = info->draw_area.width;
	draw_height = info->draw_area.height;

#ifdef WIN32_GUI_SIM
	// シミュレータ上でのサムネイル描画用処理
	// 通常のDrawableではcolor_buffer0は使用しないが
	// color_buffer0に画像データが格納されているようであれば
	// vg_imageに描画してからsurfaceへ反映する
	if (pbuffer_context->color_buffer0 && *((int*)pbuffer_context->color_buffer0) != 0x00) {
		BOOL isRGBA8888 = (pbuffer_context->format == GDI_COLOR_FORMAT_RGBA8888);
		VGImageFormat vgFormat = isRGBA8888 ? VG_sRGBA_8888 : VG_sRGBA_4444;
		int dataStride = pbuffer_context->width * (isRGBA8888 ? 4 : 2);

		vgImageSubData(pbuffer_context->vg_image, pbuffer_context->color_buffer0, dataStride, vgFormat, 0, 0, pbuffer_context->width, pbuffer_context->height);
	}
#endif

	get_draw_area_image(&drawAreaInfo, draw_width, draw_height,
						pbuffer_context->width, pbuffer_context->height, &info_drawable->image_style);
	drawAreaInfo.area.x += info->draw_area.x;
	drawAreaInfo.area.y += info->draw_area.y;
	
	gdi_get_vgcoords(context, rect, &drawAreaInfo.area);
	gdi_get_vgcoords(context, clip, &info->clip_area);

	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)(rect[1] + rect[3]) : (VGfloat)rect[1];
	drawAreaInfo.sy *= (context->type == GDI_CONTEXT_WINDOW)  ? -1.0f : 1.0f;	//パスは上下が反転しているため、引っくり返す
	
	gdi_enable_scissoring(clip);		//描画領域の準備

	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, drawAreaInfo.sx, drawAreaInfo.sy);
	vgLoadMatrix(matrix);
	vgDrawImage(pbuffer_context->vg_image);

	gdi_disable_scissoring();				//終了処理

 EXIT:
	sig_sem(GDI_SEMID_DRAW);

	return err;
}

GDI_ERRCODE GDI_DrawImage(GDI_DRAW_BASE *info, GDI_HANDLER drawable)
{
	GDI_ERRCODE err = GDI_NO_ERROR;
	VGfloat sx, sy;
	INT src_width, src_height, draw_width, draw_height;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat matrix[9] ={0.0f};
	gdi_pbuffer_context *pbuffer_context;
	gdi_context_base* context = gdi_get_current_context();

	wai_sem(GDI_SEMID_DRAW);

	if ((info == NULL) || (drawable == GDI_INVALID_ID)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}
	
	pbuffer_context = (gdi_pbuffer_context *)drawable;

	// 拡縮倍率設定
	src_width = pbuffer_context->width;
	src_height = pbuffer_context->height;

	draw_width = info->draw_area.width;
	draw_height = info->draw_area.height;

#ifdef WIN32_GUI_SIM
	// シミュレータ上でのサムネイル描画用処理
	// 通常のDrawableではcolor_buffer0は使用しないが
	// color_buffer0に画像データが格納されているようであれば
	// vg_imageに描画してからsurfaceへ反映する
	if (pbuffer_context->color_buffer0 && *((int*)pbuffer_context->color_buffer0) != 0x00) {
		BOOL isRGBA8888 = (pbuffer_context->format == GDI_COLOR_FORMAT_RGBA8888);
		VGImageFormat vgFormat = isRGBA8888 ? VG_sRGBA_8888 : VG_sRGBA_4444;
		int dataStride = src_width * (isRGBA8888 ? 4 : 2);

		vgImageSubData(pbuffer_context->vg_image, pbuffer_context->color_buffer0, dataStride, vgFormat, 0, 0, src_width, src_height);
	}
#endif

	sx = (VGfloat)draw_width / (VGfloat)src_width;
	sy = (VGfloat)draw_height / (VGfloat)src_height;
	sy *= -1.0f;	//パスは上下が反転しているため、引っくり返す

	gdi_get_vgcoords(context, rect, &info->draw_area);
	gdi_get_vgcoords(context, clip, &info->clip_area);

	gdi_enable_scissoring(clip);		//描画領域の準備

	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, (VGfloat)rect[0], (VGfloat)rect[1] + rect[3]);
	gdi_transform_scale(matrix, sx, sy);
	vgLoadMatrix(matrix);
	vgDrawImage(pbuffer_context->vg_image);

	gdi_disable_scissoring();				//終了処理

 EXIT:
	sig_sem(GDI_SEMID_DRAW);

	return err;
}



/**
 * パスの描画
 *
 * [in/out]
 *  @param path:描画する図形のパス
 *  @param stroke_width:描画する図形の線幅
 *  @param stroke_color:描画する図形の縁線色
 *  @param fill_color:描画する図形の塗りつぶし色
 * [out]
 *  @retrun 描画結果のエラーコード
 *
 */
static GDI_ERRCODE gdi_draw_path(VGPath path, VGfloat stroke_width, GDI_COLOR *stroke_color, GDI_COLOR *fill_color, VGfloat alpha_factor)
{
	VGPaintMode mode = 0;
	VGPaint stroke_paint = VG_INVALID_HANDLE;
	VGPaint fill_paint = VG_INVALID_HANDLE;
	GDI_ERRCODE	err = GDI_NO_ERROR;

	//縁線カラーの設定
	if ((stroke_color != NULL) && (stroke_color->type != 0) && (stroke_width != 0.0f)) {	/* pgr0838 */
		err = gdi_create_color(stroke_color, &stroke_paint, alpha_factor);
		if (GDI_NO_ERROR != err) {
			goto EXIT;
		}

		mode |= VG_STROKE_PATH;
		vgSetf(VG_STROKE_LINE_WIDTH, stroke_width);
		vgSetPaint(stroke_paint, VG_STROKE_PATH);
	}

	//塗りつぶしカラーの設定
	if ((fill_color != NULL) && (fill_color->type != 0)) {	/* pgr0838	*/
		err = gdi_create_color(fill_color, &fill_paint, alpha_factor);
		if (GDI_NO_ERROR != err) {
			goto EXIT;
		}

		mode |= VG_FILL_PATH;
		vgSetPaint(fill_paint, VG_FILL_PATH);
	}

	vgDrawPath(path, mode);
	switch (vgGetError()) {
	case VG_NO_ERROR:
		err = GDI_NO_ERROR;
		break;
	default:
		err = GDI_EGL_ERROR;
		break;
	}

 EXIT:
	if (VG_INVALID_HANDLE != stroke_paint) vgDestroyPaint(stroke_paint);
	if (VG_INVALID_HANDLE != fill_paint) vgDestroyPaint(fill_paint);

	return err;
}

/**
 * 図形パスの描画
 *
 * [in/out]
 *  @param path:描画する図形のパス
 *  @param stroke_width:描画する図形の線幅
 *  @param stroke_color:描画する図形の縁線色
 *  @param fill_color:描画する図形の塗りつぶし色
 * [out]
 *  @retrun 描画結果のエラーコード
 *
 */
static GDI_ERRCODE gdi_draw_shape_path(VGPath path, VGfloat stroke_width, GDI_COLOR *stroke_color, GDI_COLOR *fill_color, VGfloat alpha_factor)
{
	//###mada ここで設定しているものを外から渡せるようにする必要はある？

	// 塗りつぶしカラー用の準備
	if ((fill_color != NULL) && (0 != fill_color->type)) {	/* pgr0838 */
		vgSeti(VG_FILL_RULE, VG_NON_ZERO);
	}

	// 外縁カラー用の準備
	// 既存のfont_service_draw_path_hereだと外縁の太さはフォントサイズから計算して出してたけど・・・？
	if ((stroke_color != NULL) && (0 != stroke_color->type) && (0 != stroke_width)) {	/* pgr0838 */
		/* 外周線の点線パターン */
		vgSetfv(VG_STROKE_DASH_PATTERN, 0, NULL);
		/* 線端形状 */
		vgSeti( VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
		/* 線継ぎ目形状 */
		vgSeti( VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
		/* マイター限界を指定 */
		vgSetf( VG_STROKE_MITER_LIMIT, stroke_width);
	}

	//パスの描画
	return gdi_draw_path(path, stroke_width, stroke_color, fill_color, alpha_factor);
}


/**
 * 図形パスの生成
 *
 * [in/out]
 *  @param type:描画する図形のタイプ
 *  @param shape:描画する図形の情報
 * [out]
 *  @retrun 図形のパス
 *
 */
static VGPath gdi_create_shape_path(GDI_SHAPE_TYPE type, void *shape)
{
	VGPath path = VG_INVALID_HANDLE;
	
	if (shape == NULL) {
		goto ERROR_EXIT;
	}

	path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	
	if (VG_INVALID_HANDLE == path || vgGetError() != VG_NO_ERROR) {
		goto ERROR_EXIT;
	}

	if (GDI_NO_ERROR != gdi_set_figure_data(path, type, shape)) {
		goto ERROR_EXIT;
	}

	return path;

 ERROR_EXIT:
	if (VG_INVALID_HANDLE != path) vgDestroyPath(path);
	return VG_INVALID_HANDLE;
}

/**
 * 指定されたパラメータから四角形をSurfaceへ描画
 *
 * [in/out]
 *  @param hdr:
 *  @param info:
 *    -member blend         描画方法
 *    -member clip_area     クリップ範囲
 *    -member x0            描画開始x座標
 *    -member y0            描画開始y座標
 *    -member x1            描画終了x座標
 *    -member y1            描画終了y座標
 *    -member stroke_width  縁線幅
 *    -member *stroke_color 縁線色
 *    -member *fill_color   塗りつぶし色
 * [out]
 *  @retrun エラーコード
 *
 */
GDI_ERRCODE GDI_DrawLine(GDI_DRAW_BASE *info, GDI_DRAW_LINE* info_shape)
{
	VGPath path = VG_INVALID_HANDLE;
	GDI_ERRCODE	err = GDI_NO_ERROR;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat tx, ty, sy;
	VGfloat matrix[9] = {0.0f};
	VGfloat x0, y0, x1,y1;
	gdi_context_base* context = gdi_get_current_context();

	if ((info == NULL) || (info_shape == NULL))
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
	wai_sem(GDI_SEMID_DRAW);

	x0 = (VGfloat)info_shape->x0;
	y0 = (VGfloat)info_shape->y0;
	x1 = (VGfloat)info_shape->x1;
	y1 = (VGfloat)info_shape->y1;

	if (x0 == 0 && x1 == 0) {
		x0 += (VGfloat)info_shape->line_width * 0.5f;
		x1 += (VGfloat)info_shape->line_width * 0.5f;
	} else if (x0 == info->draw_area.width && x1 == info->draw_area.width) {
		x0 -= (VGfloat)info_shape->line_width * 0.5f;
		x1 -= (VGfloat)info_shape->line_width * 0.5f;
	} else if (y0 == 0 && y1 == 0) {
		y0 += (VGfloat)info_shape->line_width * 0.5f;
		y1 += (VGfloat)info_shape->line_width * 0.5f;
	} else if (y0 == info->draw_area.height && y1 == info->draw_area.height) {
		y0 -= (VGfloat)info_shape->line_width * 0.5f;
		y1 -= (VGfloat)info_shape->line_width * 0.5f;
	}
	
	gdi_get_vgcoords(context, rect, &info->draw_area);
	gdi_get_vgcoords(context, clip, &info->clip_area);

	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)(rect[1] + rect[3]) : (VGfloat)rect[1];				/* parasoft-suppress BD-PB-NP */
	sy = (context->type == GDI_CONTEXT_WINDOW)  ? -1.0f : 1.0f;	//パスは上下が反転しているため、引っくり返す	/* parasoft-suppress BD-PB-NP */
	
	path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	
	if (VG_INVALID_HANDLE == path || vgGetError() != VG_NO_ERROR)
		goto EXIT;
		
	if (gdi_append_path_line(path,x0, y0, x1, y1) != GDI_NO_ERROR) {
		goto EXIT;
	}
	if (VG_INVALID_HANDLE == path) {
		err = GDI_EGL_ERROR;
		goto EXIT;
	}

	gdi_enable_scissoring(clip);

	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, 1.0f, sy);
	vgLoadMatrix(matrix);

	err = gdi_draw_shape_path(path, (VGfloat)info_shape->line_width, &info_shape->line_color, NULL, 1.0f);

	gdi_disable_scissoring();

 EXIT:
	if (VG_INVALID_HANDLE != path) vgDestroyPath(path);
	sig_sem(GDI_SEMID_DRAW);

	return err;
}

/**
 * 指定されたパラメータから四角形をSurfaceへ描画
 *
 * [in/out]
 *  @param hdr:
 *  @param info:
 *    -member blend         描画方法
 *    -member clip_area     クリップ範囲
 *    -member x             描画開始x座標
 *    -member y             描画開始y座標
 *    -member width         描画する角丸四角の横幅
 *    -member height        描画する角丸四角の縦幅
 *    -member stroke_width  縁線幅
 *    -member *stroke_color 縁線色
 *    -member *fill_color   塗りつぶし色
 * [out]
 *  @retrun エラーコード
 *
 */
GDI_ERRCODE GDI_DrawRectangle(GDI_DRAW_BASE *info, GDI_DRAW_RECT* info_shape)
{
	VGPath path = VG_INVALID_HANDLE;
	GDI_ERRCODE	err = GDI_NO_ERROR;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat tx, ty, sy;
	VGfloat matrix[9] = {0.0f};
	VGfloat x, y, width, height;
	gdi_context_base* context = gdi_get_current_context();

	if ((info == NULL) || (info_shape == NULL))
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
	wai_sem(GDI_SEMID_DRAW);
	
	if ((info->draw_area.width <= 0.0f) || (info->draw_area.height <= 0.0f)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}
	
	gdi_get_vgcoords(context, rect, &info->draw_area);
	gdi_get_vgcoords(context, clip, &info->clip_area);
	
	x = y = 0 + (VGfloat)info_shape->stroke_width * 0.5f;
	if ((width = (VGfloat)info->draw_area.width - (VGfloat)info_shape->stroke_width) <= 0.0f)
		width = 1;
	if ((height = (VGfloat)info->draw_area.height - (VGfloat)info_shape->stroke_width) <= 0.0f)
		height = 1;

	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)(rect[1] + rect[3]) : (VGfloat)rect[1];
	sy = (context->type == GDI_CONTEXT_WINDOW)  ? -1.0f : 1.0f;	//パスは上下が反転しているため、引っくり返す

	path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	if (VG_INVALID_HANDLE == path || vgGetError() != VG_NO_ERROR)
		goto EXIT;
		
	if (gdi_append_path_rect(path, x, y, width, height) != GDI_NO_ERROR) {
		goto EXIT;
	}
	if (VG_INVALID_HANDLE == path) {
		err = GDI_EGL_ERROR;
		goto EXIT;
	}

	gdi_enable_scissoring(clip);

	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, 1.0f, sy);
	vgLoadMatrix(matrix);

	err = gdi_draw_shape_path(path, (VGfloat)info_shape->stroke_width, &info_shape->stroke_color, &info_shape->fill_color, 1.0f);

	gdi_disable_scissoring();

 EXIT:
	if (VG_INVALID_HANDLE != path) vgDestroyPath(path);
	sig_sem(GDI_SEMID_DRAW);

	return err;
}

/**
 * 指定されたパラメータから角丸四角をSurfaceへ描画
 *
 * [in/out]
 *  @param hdr:
 *  @param info:
 *    -member blend         描画方法
 *    -member clip_area     クリップ範囲
 *    -member x             描画開始x座標
 *    -member y             描画開始y座標
 *    -member width         描画する角丸四角の横幅
 *    -member height        描画する角丸四角の縦幅
 *    -member arc_width     描画する角の丸部分の横半径
 *    -member arc_height    描画する角の丸部分の縦半径
 *    -member stroke_width  縁線幅
 *    -member *stroke_color 縁線色
 *    -member *fill_color   塗りつぶし色
 * [out]
 *  @retrun エラーコード
 *
 */
GDI_ERRCODE GDI_DrawRoundRect(GDI_DRAW_BASE *info, GDI_DRAW_ROUNDRECT *info_shape)
{
	VGPath path = VG_INVALID_HANDLE;
	GDI_ERRCODE	err = GDI_NO_ERROR;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat tx, ty, sy;
	VGfloat matrix[9] = {0.0f};
	VGfloat x, y, width, height;
	gdi_context_base* context = gdi_get_current_context();

	if ((info == NULL) || (info_shape == NULL))
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
	wai_sem(GDI_SEMID_DRAW);
	
	if ((info->draw_area.width <= 0.0f) || (info->draw_area.height <= 0.0f)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}
	
	gdi_get_vgcoords(context, rect, &info->draw_area);
	gdi_get_vgcoords(context, clip, &info->clip_area);

	x = y = 0 + (VGfloat)info_shape->stroke_width * 0.5f;
	if ((width = (VGfloat)info->draw_area.width - (VGfloat)info_shape->stroke_width) <= 0.0f)
		width = 1;
	if ((height = (VGfloat)info->draw_area.height - (VGfloat)info_shape->stroke_width) <= 0.0f)
		height = 1;

	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)(rect[1] + rect[3]) : (VGfloat)rect[1];
	sy = (context->type == GDI_CONTEXT_WINDOW)  ? -1.0f : 1.0f;	//パスは上下が反転しているため、引っくり返す

	path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	if (VG_INVALID_HANDLE == path || vgGetError() != VG_NO_ERROR)
		goto EXIT;
		
	if (gdi_append_path_roundrect(path, x, y, width, height, (VGfloat)info_shape->arc_width, (VGfloat)info_shape->arc_height) != GDI_NO_ERROR) {
		goto EXIT;
	}
	if (VG_INVALID_HANDLE == path) {
		err = GDI_EGL_ERROR;
		goto EXIT;
	}

	gdi_enable_scissoring(clip);

	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, 1.0f, sy);
	vgLoadMatrix(matrix);

	err = gdi_draw_shape_path(path, (VGfloat)info_shape->stroke_width, &info_shape->stroke_color, &info_shape->fill_color, 1.0f);

	gdi_disable_scissoring();

 EXIT:
	if (VG_INVALID_HANDLE != path) vgDestroyPath(path);
	sig_sem(GDI_SEMID_DRAW);

	return err;
}


/**
 * 指定されたパラメータから円をSurfaceへ描画
 *
 * [in/out]
 *  @param hdr:
 *  @param info:
 *    -member blend         描画方法
 *    -member clip_area     クリップ範囲
 *    -member x             描画開始x座標
 *    -member y             描画開始y座標
 *    -member width         描画する円の横幅
 *    -member height        描画する円の縦幅
 *    -member stroke_width  縁線幅
 *    -member *stroke_color 縁線色
 *    -member *fill_color   塗りつぶし色
 * [out]
 *  @retrun エラーコード
 *
 */
GDI_ERRCODE GDI_DrawEllipse(GDI_DRAW_BASE *info, GDI_DRAW_ELLIPSE *info_shape)
{
	VGPath path = VG_INVALID_HANDLE;
	GDI_ERRCODE	err = GDI_NO_ERROR;
	VGint rect[4] = {0}, clip[4] = {0};
	VGfloat tx, ty, sy;
	VGfloat matrix[9] = {0.0f};
	VGfloat x, y, width, height;
	gdi_context_base* context = gdi_get_current_context();

	if ((info == NULL) || (info_shape == NULL))
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
	wai_sem(GDI_SEMID_DRAW);
	
	if ((info->draw_area.width <= 0.0f) || (info->draw_area.height <= 0.0f)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}

	gdi_get_vgcoords(context, rect, &info->draw_area);
	gdi_get_vgcoords(context, clip, &info->clip_area);
	
	//	x = 0 + (VGfloat)info_shape->stroke_width * 0.5f;
	//	y = 0 + (VGfloat)info_shape->stroke_width * 0.5f;
	x = (VGfloat)info->draw_area.width * 0.5f + (VGfloat)info_shape->stroke_width * 0.5f;
	y = (VGfloat)info->draw_area.height * 0.5f + (VGfloat)info_shape->stroke_width * 0.5f;
	if ((width = (VGfloat)info->draw_area.width - (VGfloat)info_shape->stroke_width) <= 0.0f)
		width = 1;
	if ((height = (VGfloat)info->draw_area.height - (VGfloat)info_shape->stroke_width) <= 0.0f)
		height = 1;

	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)(rect[1] + rect[3]) : (VGfloat)rect[1];
	sy = (context->type == GDI_CONTEXT_WINDOW)  ? -1.0f : 1.0f;	//パスは上下が反転しているため、引っくり返す

	path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	if (VG_INVALID_HANDLE == path || vgGetError() != VG_NO_ERROR)
		goto EXIT;
		
	if (gdi_append_path_ellipse(path, x, y, width, height) != GDI_NO_ERROR) {
		goto EXIT;
	}
	if (VG_INVALID_HANDLE == path) {
		err = GDI_EGL_ERROR;
		goto EXIT;
	}

	gdi_enable_scissoring(clip);

	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, 1.0f, sy);
	vgLoadMatrix(matrix);

	err = gdi_draw_shape_path(path, (VGfloat)info_shape->stroke_width, &info_shape->stroke_color, &info_shape->fill_color, 1.0f);

	gdi_disable_scissoring();

 EXIT:
	if (VG_INVALID_HANDLE != path) vgDestroyPath(path);
	sig_sem(GDI_SEMID_DRAW);

	return err;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*	//###mada noda コメント修正 */
/**
 * フォントパスを生成する	//###mada コメント
 *
 * [in/out]
 * [out]
 *
 */
static BOOL IsUseDescentArea(USHORT str)
{
	return (('Q' == str)
		 || ('g' == str)
		 || ('j' == str)
		 || ('p' == str)
		 || ('q' == str)
		 || ('y' == str));
}

void gdi_cnv_font_style(FONT_STYLE *f_style, GDI_FONT_STYLE *gdi_f_style, BOOL bIsMono)
{
	if (f_style == NULL || gdi_f_style == NULL)
		return;
	
	if (gdi_f_style->font_size == 0) {
		f_style->size_x = 24;
		f_style->size_y = 24;
	} else {
		f_style->size_x = gdi_f_style->font_size;
		f_style->size_y = gdi_f_style->font_size;
	}

	switch (gdi_f_style->aspect_ratio) {
	case ASPECT_RATIO_SAME:		//全角文字基準で横:縦=10:10(半角だと横:縦= 5:10)
		/* 等倍なので何もしない */
		break;

	case ASPECT_RATIO_WIDE:		//全角文字基準で横:縦=20:10(半角だと横:縦=10:10)
		f_style->size_x *= 2;			//横幅を倍にする
		break;

	case ASPECT_RATIO_RECVIEW:		//半角文字基準で横:縦=12:20(RecView画面の上下黒帯専用)
		f_style->size_x = 22;			//外枠分で太るので12pt(全角24pt)-2ptしておく
		f_style->size_y = 20;
		break;

	case ASPECT_RATIO_DEFAULT:
	default:
		f_style->size_x = (unsigned char)(f_style->size_x * 0.8f);	/* pgr0247	*/	//横幅を0.8倍する	
		break;
	}

	f_style->bold = FALSE;
	f_style->italic = FALSE;
	f_style->underline = FALSE;
	f_style->strike = FALSE;
	f_style->spacing = (char)((bIsMono) ? 1 : 0);	/* pgr0247	*/
	f_style->righttoleft = FALSE;
	f_style->edge = (FONT_ATTRIBUTE_OUTLINE == gdi_f_style->attr);
	f_style->edge_color = 0;
	f_style->mono = (unsigned char)((bIsMono) ? 1 : 0);	/* pgr0247	*/
}

static VGPath gdi_create_font_path_oneline(GDI_FONT_STYLE *gdi_font_style, unsigned short *str, int len, FONT_DRAW_INFO *draw_info)
{
	VGPath path = VG_INVALID_HANDLE;
	FONT_STYLE f_style = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if (NULL == gdi_font_style) {
		return VG_INVALID_HANDLE;
	}
	
#ifdef USE_FREETYPE_FONTAPI
	if (!ft_service_set_lang(gdi_font_style->locale)) {
		return VG_INVALID_HANDLE;
	}
	gdi_cnv_font_style(&f_style, gdi_font_style, (gdi_font_style->attr == FONT_ATTRIBUTE_MONO));
#else
	if (0 != font_service_set_lang(gdi_font_style->locale)) {
		return VG_INVALID_HANDLE;
	}
	gdi_cnv_font_style(&f_style, gdi_font_style, FALSE);

	if (gdi_font_style->isWriteOneChar) {
		path = gdi_fontapi_CombineCharsToStrPath(&f_style, str, draw_info);
	} else {
		path = gdi_fontapi_get_path(&f_style, str, len, draw_info);
	}
#endif
	return path;
}


/**
 * フォントパスの描画処理	//###mada コメント
 *
 * [in/out]
 * [out]
 *
 */
static GDI_ERRCODE gdi_draw_font_path(VGPath path, VGfloat stroke_width, GDI_COLOR *stroke_color, GDI_COLOR *fill_color, VGfloat alpha_factor)
{
	VGPaint stroke_paint = VG_INVALID_HANDLE;
	VGPaint fill_paint = VG_INVALID_HANDLE;
	GDI_ERRCODE	err = GDI_NO_ERROR;

	vgSeti(VG_FILL_RULE, VG_NON_ZERO);
	vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_ROUND);

	//フォントの場合、縁線と塗りつぶしは分けて書かないと、文字の図の中に線が入る

	//縁線カラーの設定
	if ((stroke_color != NULL) && (stroke_color->type != 0) && (stroke_width != 0.0f)) {	/* pgr0838 */
		err = gdi_create_color(stroke_color, &stroke_paint, alpha_factor);
		if (GDI_NO_ERROR != err) {
			goto EXIT;
		}

		vgSetfv(VG_STROKE_DASH_PATTERN, 0, NULL);
		vgSetf(VG_STROKE_LINE_WIDTH, stroke_width);
		vgSetPaint(stroke_paint, VG_STROKE_PATH);

		vgDrawPath(path, VG_STROKE_PATH);
		if (vgGetError() != VG_NO_ERROR) {
			err = GDI_EGL_ERROR;
			goto EXIT;
		}
	}

	//塗りつぶしカラーの設定
	if ((fill_color != NULL) && (fill_color->type != 0)) {	/* pgr0838 */
		err = gdi_create_color(fill_color, &fill_paint, alpha_factor);
		if (GDI_NO_ERROR != err) {
			goto EXIT;
		}

		vgSetPaint(fill_paint, VG_FILL_PATH);

		vgDrawPath(path, VG_FILL_PATH);
		if (vgGetError() != VG_NO_ERROR) {
			err = GDI_EGL_ERROR;
			goto EXIT;
		}
	}

 EXIT:
	if (VG_INVALID_HANDLE != stroke_paint) vgDestroyPaint(stroke_paint);
	if (VG_INVALID_HANDLE != fill_paint) vgDestroyPaint(fill_paint);

	return err;
}

typedef struct _CREATE_FONT_WORK {
	VGPath			path;
	FONT_DRAW_INFO	draw_info;
} CREATE_FONT_WORK;

static VGPath gdi_combine_font_path_multi_line(GDI_FONT_STYLE *gdi_font_style, CREATE_FONT_WORK *str_line, int line_count, int max_width, FONT_DRAW_INFO *pdraw_info)
{
	//パスを作る
	int i;
	int start_y;
	VGPath return_handle = VG_INVALID_HANDLE;
	VGPath tmppath = VG_INVALID_HANDLE;

	if (gdi_font_style == NULL || str_line == NULL || pdraw_info == NULL)
		return VG_INVALID_HANDLE;
	
	//複数行の場合はパスを結合する
	if (((return_handle = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL)) == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
		return VG_INVALID_HANDLE;
	}
	start_y = 0;

	for (i = line_count - 1; 0 <= i; i--) {
		//X座標の開始位置調整
		VGfloat start_x;
		switch (gdi_font_style->halign) {
		case HALIGN_CENTER:		//中央揃え
			start_x = ((max_width - str_line[i].draw_info.width) * 0.5f);
			break;

		case HALIGN_RIGHT:		//右寄せ
			start_x = (VGfloat)(max_width - str_line[i].draw_info.width);
			break;

		case HALIGN_LEFT:		//左寄せ
		default:
			start_x = 0;
			break;
		}

		if (((tmppath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL)) == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
			return VG_INVALID_HANDLE;
		}
		vgAppendPath(tmppath, str_line[i].path);
		vgLoadIdentity();
		vgTranslate(start_x, (VGfloat)start_y);
		vgClearPath(str_line[i].path, VG_PATH_CAPABILITY_ALL);
		vgTransformPath(str_line[i].path, tmppath);

		vgAppendPath(return_handle, str_line[i].path);
		vgDestroyPath(tmppath);
		vgDestroyPath(str_line[i].path);

		//Y座標の開始位置更新
		start_y += str_line[i].draw_info.bmpheight;
	}

	pdraw_info->bmpheight = start_y;
	pdraw_info->bmpwidth = max_width;
	pdraw_info->lineUnderflow = str_line[line_count - 1].draw_info.lineUnderflow;
	pdraw_info->height = start_y;
	pdraw_info->width = max_width;

	return return_handle;
}


static int IsNewLine(const USHORT *ucs_str)
{
	if (ucs_str == NULL)
		return 0;
	
	if ((0x0D == *ucs_str) && (0x0A == *(ucs_str + 1))) {
		return 2; //CR + LF(改行コードが2char)
	}

	if (0x0D == *ucs_str) {
		return 1; //CRのみ
	}

	if (0x0A == *ucs_str) {
		return 1; //LFのみ
	}

	return 0;	//改行コードなし
}


#define GDI_FONT_MAX_STR_LINE		(10)			//TODO：改行は最大10行までとする。それ以上必要であれば定義を拡張すること
static VGPath gdi_create_font_path_multi_line(GDI_FONT_STYLE *gdi_font_style, unsigned short *str, int line_count, FONT_DRAW_INFO *pdraw_info)
{
	CREATE_FONT_WORK str_line[GDI_FONT_MAX_STR_LINE] = { 0 };	//←TODO:ここをmalloc(サイズはline_count)みたいな感じにすれば可変にはできるが。。。
	unsigned short *str_top = NULL;
	unsigned short *str_current = NULL;
	int line_indx = 0;
	int crlf;
	int max_width = 0;

	if (NULL == str) {
		return VG_INVALID_HANDLE;
	}

	//1行分の文字列を取得する
	if (GDI_FONT_MAX_STR_LINE < line_count) {
		line_count = GDI_FONT_MAX_STR_LINE;
	}

	str_top = str;
	str_current = str;

	while (line_indx < line_count) {

		//改行チェック
		crlf = IsNewLine(str_current);

		if ((0 < crlf) || (0x00 == *str_current)) {
			str_line[line_indx].path = gdi_create_font_path_oneline(gdi_font_style, str_top, (str_current - str_top), &str_line[line_indx].draw_info);
			if (max_width < (int)str_line[line_indx].draw_info.bmpwidth) {
				max_width = str_line[line_indx].draw_info.bmpwidth;
			}
			str_current += crlf;								//文字位置を更新
			str_top = str_current;								//文字開始位置の更新
			line_indx++;

			if (0x0000 == *str_current) {
				break;
			}
		} else {
			str_current++;
		}
	}

	return gdi_combine_font_path_multi_line(gdi_font_style, str_line, line_count, max_width, pdraw_info);
}


VGPath gdi_create_font_path(GDI_FONT_STYLE *gdi_font_style, unsigned short *str, FONT_DRAW_INFO *pdraw_info)
{
	int line_count = 1;
	int crlf;
	int len;

	if (gdi_font_style == NULL || str == NULL)
		return VG_INVALID_HANDLE;
	
	//先頭1文字目がNULLの場合は即終了
	if (0x00 == *str) {
		return VG_INVALID_HANDLE;
	}

	for (len = 0; (0x0000 != str[len]); len++) {
		crlf = IsNewLine(&str[len]);
		if (0 < crlf) {
			line_count++;
			len += (crlf - 1);
		}
	}

	if (1 < line_count) {
		//複数行のパス生成
		return gdi_create_font_path_multi_line(gdi_font_style, str, line_count, pdraw_info);
	}

	return gdi_create_font_path_oneline(gdi_font_style, str, len, pdraw_info);
}



static GDI_CACHE_FONT * gdi_create_cache_font(GDI_FONT_STYLE *gdi_font_style, unsigned short *str)
{
	GDI_CACHE_FONT *cache_font = NULL;
#ifndef USE_FREETYPE_FONTAPI
	int			len;
	FONT_DRAW_INFO draw_info = { 0, 0, 0, 0, 0 };

	if (gdi_font_style == NULL || str == NULL) {
		goto EXIT;
	}

	for (len = 0; str[len]; len++);
	if (len <= 0) {
		goto EXIT;
	}

	if ((cache_font = gdi_alloc_cache_font()) == NULL) {
		goto EXIT;
	}

	cache_font->path = gdi_create_font_path(gdi_font_style, str, &draw_info);
	if (VG_INVALID_HANDLE == cache_font->path) {
		gdi_free_cache_font(cache_font);
		cache_font = NULL;
		goto EXIT;
	}

	cache_font->type			=	GDI_CACHE_TYPE_FONT;
	cache_font->width			=	draw_info.width;	/* pgr0351 */
	cache_font->height			=	draw_info.height;	/* pgr0351 */
	cache_font->lineUnderflow	=	draw_info.lineUnderflow;	/* pgr0351 */
	cache_font->bmpheight		=	draw_info.bmpheight;	/* pgr0351 */

EXIT:
#endif
	return cache_font;
}

GDI_CACHE_FONT * GDI_CreateCacheFont(GDI_FONT_STYLE *gdi_font_style, unsigned short *str)
{
	GDI_CACHE_FONT *cache_font = NULL;
	
	wai_sem(GDI_SEMID_DRAW);
	cache_font = gdi_create_cache_font(gdi_font_style, str);
	sig_sem(GDI_SEMID_DRAW);

	return cache_font;
}


GDI_ERRCODE GDI_GetDrawRect(GDI_FONT_STYLE *gdi_font_style, unsigned short *str, unsigned short int *pWidth, unsigned short int *pHeight)
{
	FONT_STYLE f_style = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned short int width = 0, height = 0, xbytes = 0;
	GDI_ERRCODE		err = GDI_NO_ERROR;

	if (gdi_font_style == NULL || pWidth == NULL || pHeight == NULL) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}
	
#ifdef USE_FREETYPE_FONTAPI
	if (FONT_ATTRIBUTE_MONO == gdi_font_style->attr) {
        if (!ft_service_set_lang(gdi_font_style->locale)) {
            return GDI_ILLEGAL_ARGUMENT_ERROR;
        }        
		return Freetype_GetDrawRect(gdi_font_style, str, pWidth, pHeight);
	}
#endif
    
	if (0 != font_service_set_lang(gdi_font_style->locale)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}
    
	gdi_cnv_font_style(&f_style, gdi_font_style, FALSE);

	if (0 != gdi_fontapi_get_rect(&f_style, str, &width, &height, &xbytes, FALSE)) {
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}

	*pWidth = width;
	*pHeight = height;

 EXIT:
	return err;
}



/**
 * キャッシュされたPATHからフォントをSurfaceへ描画
 *
 * [in/out]
 *  @param hdr:
 *  @param info:
 *    -member blend         描画方法
 *    -member clip_area     クリップ範囲
 *    -member draw_area     描画範囲
 *    -member len           文字列長
 *    -member str           文字列
 *    -member font_style    フォント形式
 *    -member auto_adjust   0：サイズ自動調整なし / 1：draw_areaに収まるようにサイズの自動調整を行う
 *    -member stroke_width  縁線幅
 *    -member stroke_color  縁線色
 *    -member fill_color    塗りつぶし色
 *  @param cache:キャッシュ情報
 * [out]
 *  @retrun エラーコード
 *
 */
GDI_ERRCODE GDI_DrawFont(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font, GDI_CACHE_FONT *cache)
{
	GDI_CACHE_FONT	*cache_font = NULL;
	DRAW_AREA_INFO	drawAreaInfo;
	GDI_ERRCODE		err = GDI_NO_ERROR;
	VGfloat			matrix[9];
	VGfloat			tx, ty;
	float			stroke_width = 0.0f;
	AUTO_ADJUST 	adjust;
	gdi_context_base* context = gdi_get_current_context();
	VGint rect[4] = {0}, clip[4] = {0};

	//描画色の準備
	GDI_COLOR	*stroke_color;
	GDI_COLOR	*fill_color;
	GDI_COLOR	clear_color = { VG_PAINT_TYPE_COLOR, 0, NULL };

	if (NULL == info || NULL == info_font || NULL == info_font->str || info_font->str[0] == 0) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

#ifdef USE_FREETYPE_FONTAPI
	if (FONT_ATTRIBUTE_MONO != info_font->font_style.attr) {
		wai_sem(GDI_SEMID_DRAW);
		err = FreeType_DrawFont(info, info_font, NULL);
		sig_sem(GDI_SEMID_DRAW);
	}
	return err;
#endif


	adjust = info_font->font_style.auto_adjust;
	
	wai_sem(GDI_SEMID_DRAW);
	
	stroke_color = &info_font->stroke_color;
	fill_color = &info_font->fill_color;

	if ((info->draw_area.width <= 0.0f) || (info->draw_area.height <= 0.0f)) {
		err =  GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}

	if (cache == NULL) {
		if ((cache_font = gdi_create_cache_font(&info_font->font_style, info_font->str)) == NULL) {
			err =  GDI_OUT_OF_MEMORY_ERROR;
			goto EXIT;
		}
	} else {
		cache_font = cache;
	}
	
	if (cache_font == NULL) {
		err = GDI_OUT_OF_MEMORY_ERROR;
		goto EXIT;
	}
	
	//描画色と線幅を設定
	switch (info_font->font_style.attr) {
	case FONT_ATTRIBUTE_BOLD:
		if (info_font->stroke_width < 0) {
			stroke_width = 11.0f * (float)(cache_font->height) / 100.0f;
		} else {
			stroke_width = info_font->stroke_width;
		}
		stroke_color = fill_color;
		break;

	case FONT_ATTRIBUTE_OUTLINE:
		{
			if (info_font->stroke_width < 0) {
				int stroke = (int)(11.0f * (float)(cache_font->height) / 100.0f);	/* pgr0247	*/
				stroke_width = (float)stroke;	//端数切捨て
			} else {
				stroke_width = info_font->stroke_width;
			}

			//縁線のみ描画で塗りつぶしがなかった場合、透過色で塗り潰す
			if ((NULL != stroke_color) && (0.0f != stroke_width) && (NULL == fill_color)) {
				fill_color = &clear_color;	//TODO:透過色はどこから持ってきたらいい？
			}
		}
		break;

	case FONT_ATTRIBUTE_NORMAL:
	default:
		/* 何もしない */
		break;
	}

	//描画開始位置(tx, ty)、拡縮倍率(sx, sy)、描画エリア(draw、clipのgdi_get_vgcoords後の領域)を取得
	get_draw_area_font(&drawAreaInfo, info->draw_area.width, info->draw_area.height,
					   cache_font->width, cache_font->height,
					   stroke_width, cache_font->bmpheight, cache_font->lineUnderflow,
					   &info_font->font_style);
	drawAreaInfo.area.x += info->draw_area.x;
	drawAreaInfo.area.y += info->draw_area.y;
	
	gdi_get_vgcoords(context, rect, &drawAreaInfo.area);
	gdi_get_vgcoords(context, clip, &info->clip_area);
	
	tx = (VGfloat)rect[0];
	ty = (context->type == GDI_CONTEXT_WINDOW) ? (VGfloat)rect[1] : (VGfloat)(rect[1] + rect[3]);
	drawAreaInfo.sy *= (context->type == GDI_CONTEXT_WINDOW)  ? 1.0f : -1.0f;	//パスは上下が反転しているため、引っくり返す

	//描画
	gdi_enable_scissoring(clip);

	vgSeti(VG_BLEND_MODE, gdi_get_vgblend(info->blend));
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, tx, ty);
	gdi_transform_scale(matrix, drawAreaInfo.sx, drawAreaInfo.sy);
	vgLoadMatrix(matrix);

	err = gdi_draw_font_path(cache_font->path, stroke_width, stroke_color, fill_color, 1.0f);
	vgFinish();
	gdi_disable_scissoring();

 EXIT:
	if ((NULL == cache) && (NULL != cache_font)) {
		gdi_free_cache_font(cache_font);
	}
	sig_sem(GDI_SEMID_DRAW);

	return err;
}

GDI_ERRCODE GDI_DeleteCache(GDI_CACHE_BASE *cache)
{
	GDI_ERRCODE err = GDI_NO_ERROR;

	if (cache == NULL) {
		return err;
	}

	wai_sem(GDI_SEMID_DRAW);

	switch (cache->type) {
	case GDI_CACHE_TYPE_SVG:
		gdi_free_cache_svg((GDI_CACHE_SVG *)cache);
		break;
	case GDI_CACHE_TYPE_FONT:
		gdi_free_cache_font((GDI_CACHE_FONT *)cache);
		break;
	default:
		err = GDI_ILLEGAL_ARGUMENT_ERROR;
		goto EXIT;
	}

 EXIT:
	sig_sem(GDI_SEMID_DRAW);
	return err;
}

GDI_ERRCODE GDI_Clear(signed short int x, signed short int y, signed short int width, signed short int height, unsigned long rgba)
{
	GDI_ERRCODE err = GDI_NO_ERROR;
	VGfloat		color[4] = {0.0f};
	GDI_REGION	draw_area = { x, y, width, height };
	VGint		rect[4] = {0};
	gdi_context_base* context = gdi_get_current_context();

	wai_sem(GDI_SEMID_DRAW);
	
	gdi_get_vgcoords(context, rect, &draw_area);

	GDI_MAKE_F_RGBA(rgba, color);

	vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
	vgSeti(VG_SCISSORING, VG_FALSE);
	vgSetfv(VG_CLEAR_COLOR, 4, color);
	vgClear(rect[0], rect[1], rect[2], rect[3]);

	sig_sem(GDI_SEMID_DRAW);
	return err;
}

GDI_ERRCODE GDI_DrawFill(GDI_DRAW_BASE *info, GDI_COLOR color)
{
	/* vgClearだとBLEND_MODEを考慮せずに塗りつぶすため
	 * GDI_DrawRectangleへ呼び換える
	*/
	GDI_DRAW_RECT rect;

	if (NULL == info) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	rect.stroke_width = 0;
	rect.stroke_color = color;
	rect.fill_color = color;

	return GDI_DrawRectangle(info, &rect);
}

void GDI_CopyRectYUV422(unsigned short int src_width, unsigned short int src_height,
						void* src_Y, void* src_UV,
						unsigned short int dst_width, unsigned short int dst_height,
						void* dst_Y, void* dst_UV)
{
	void *src, *dst;
	unsigned char *temp_src;
	unsigned char *temp_dst;
	unsigned short int dst_stride;

	// アライメント 16の倍数
	dst_stride = dst_width / 16;	/* pgr0351 */
	dst_stride += (0 == (dst_width % 16)) ? 0 : 1;	/* pgr0351 */
	dst_stride *= 16;

	//Yプレーンのコピー
	unsigned short int i;

	src = src_Y;
	dst = dst_Y;
	temp_src = src;
	temp_dst = dst;

	for (i = 0; i < dst_height; i++) {
		memcpy(temp_dst, temp_src, dst_width);
		temp_src += src_width;
		temp_dst += dst_stride;
	}
	src = temp_src;
	dst = temp_dst;

	//UVプレーンのコピー
	src = src_UV;
	dst = dst_UV;
	temp_src = src;
	temp_dst = dst;
	for (i = 0; i < (unsigned short int)(dst_height/2); i++) {	/* pgr0247 */
		memcpy(temp_dst, temp_src, dst_width);
		temp_src += src_width;
		temp_dst += dst_stride;
	}
	src = temp_src;
	dst = temp_dst;
}


void GDI_Error(int dat, int dat2)
{
	CtDebugPrint(CtDbg, "< [Seq:%3d] WinItron Sem Signal %d\n", dat, dat2);
	return;
}

void GDI_Error2(int dat, int dat2)
{
	CtDebugPrint(CtDbg, "> [Seq:%3d] WinItron Sem kakutoku %d\n", dat, dat2);
	return;
}

#ifdef USE_FREETYPE_FONTAPI
////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void GDI_DrawBitmapFontExec(DRAW_AREA_INFO *drawAreaInfo, VGImage vg_image)
{
	VGfloat			matrix[9];

	gdi_enable_scissoring(drawAreaInfo->clipArea);

	vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);		//ビットマップでVG_BLEND_SRCにすると、背景が黒塗りになってしまうため、VG_BLEND_SRC_OVER固定とする
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);

	gdi_transform_loadIdentity(matrix);
	gdi_transform_translate(matrix, drawAreaInfo->tx, drawAreaInfo->ty);
	gdi_transform_scale(matrix, drawAreaInfo->sx, drawAreaInfo->sy);
	vgLoadMatrix(matrix);

	vgDrawImage(vg_image);
	vgFinish();

	gdi_disable_scissoring();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void GDI_DrawBitmapFont_SetDrawAreaInfo(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font, DRAW_AREA_INFO *pDrawAreaInfo, VGfloat src_height, int ajustX, int ajustY)
{
	VGfloat				ty = 0.0f;
	VGfloat				sy = 0.0f;
	VGint				rect[4] = { 0 };
	gdi_context_base* context = gdi_get_current_context();

	gdi_get_vgcoords(context, rect, &info->draw_area);
	gdi_get_vgcoords(context, pDrawAreaInfo->clipArea, &info->clip_area);

	if (context->type == GDI_CONTEXT_WINDOW) {
		ty = (VGfloat)(rect[1] + rect[3]);
		ty -= get_draw_start_y(info_font->font_style.valign, (int)src_height, (int)info->draw_area.height);
		ty -= ajustY;
		sy = -1.0f;
	} else {
		ty = (VGfloat)rect[1];	//y座標
		ty += get_draw_start_y(info_font->font_style.valign, (int)src_height, (int)info->draw_area.height);
		ty += ajustY;
		sy = 1.0f;
	}

	pDrawAreaInfo->draw_x = 0.0f; //描画開始位置(X)微調整用
	pDrawAreaInfo->draw_y = 0.0f;	 //描画開始位置(Y)微調整用
	pDrawAreaInfo->tx = (VGfloat)(rect[0] + ajustX);
	pDrawAreaInfo->ty = ty;
	pDrawAreaInfo->sx = 1.0f;
	pDrawAreaInfo->sy = sy;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
GDI_ERRCODE GDI_DrawBitmapFont_OneChar(GDI_DRAW_BASE *info, GDI_CACHE_FONT *cache, unsigned short ucs_str, GDI_DRAW_FONT *info_font, int *draw_width)
{
	GDI_CACHE_BITMAP_FONT	cache_font;
	DRAW_AREA_INFO	drawAreaInfo;
	GDI_ERRCODE		err = GDI_NO_ERROR;
	VGfloat			src_height;

	//描画色の準備
	GDI_COLOR	clear_color = { VG_PAINT_TYPE_COLOR, 0, NULL };

	memset(&cache_font, 0, sizeof(cache_font));

	err = FreetypeCreateMonoFontImage(&cache_font, &info_font->font_style, ucs_str, &info_font->fill_color, &info_font->stroke_color);
	if (GDI_NO_ERROR != err) {
		goto EXIT;
	}

	//描画開始位置(tx, ty)、拡縮倍率(sx, sy)、描画エリア(draw、clipのgdi_get_vgcoords後の領域)を取得
	src_height = (VGfloat)cache_font.height + (VGfloat)cache_font.lineUnderflow;
	GDI_DrawBitmapFont_SetDrawAreaInfo(info, info_font, &drawAreaInfo, src_height, cache_font.x_pos, cache_font.y_pos);

	//描画
	GDI_DrawBitmapFontExec(&drawAreaInfo, cache_font.vg_image);

	*draw_width = cache_font.advanceX;

EXIT:
	if (cache_font.vg_image != VG_INVALID_HANDLE) {
		vgDestroyImage(cache_font.vg_image);
	}

	if (cache_font.raw_data != NULL) {
		gdi_bmp_free(cache_font.raw_data);
	}

	return err;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GDI_Convert_FontStyle(FONT_STYLE *f_style, GDI_FONT_STYLE *gdi_f_style, BOOL bIsMono)
{
	gdi_cnv_font_style(f_style, gdi_f_style, bIsMono);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
GDI_CACHE_BITMAP_FONT *GDI_AllocCache_BitmapFont(void)
{
	return gdi_alloc_cache_bitmap_font();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GDI_FreeCache_BitmapFont(GDI_CACHE_BITMAP_FONT *cache_font)
{
	gdi_free_cache_bitmap_font(cache_font);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void *GDI_Alloc_Memory(int size)
{
	return gdi_bmp_alloc(size, 128);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
