#ifndef __GUI_CONFIG_H__
#define __GUI_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "itron.h"



/* rel_mpfに置き換えたら不要となる。削除予定 */
extern void gfx_free_mpf(VP blk);


/*---------------------------------------------
	GUIメモリマップ上に確保するサイズ
	このサイズでセクション領域を確保する事

	※印： kernelに影響（xxx.CFGで参照）する為、変更したらALLMAKEが必要
---------------------------------------------*/
/* GUI MPF ※ */
extern UB GfxMpfMem[];
#define GUI_MPF_BLKCNT			300	/**< メモリブロック数 */
#define GUI_MPF_BLKSZ			64	/**< メモリブロックサイズ */
#define	GUI_MPF_SIZE	(TSZ_MPF(GUI_MPF_BLKCNT, GUI_MPF_BLKSZ))

/*--------------
	GUI WORK	※
--------------*/
extern unsigned char _gui_work_start[];
#define GUI_WORK_START     (_gui_work_start)
#define GUI_WORK_SIZE	(33338880) 		/* K519メモリマップ相当 */

/*--------------
	GFX RES	※
--------------*/
extern unsigned char _gfx_res_start[];
#define GFX_RES_START		 (_gfx_res_start)
#define	GFX_RES_SIZE	(500*1024)

/*--------------
	CT WORK	※
--------------*/
extern unsigned char _ct_work_start[];
#define CT_WORK_START		 (_ct_work_start)
#define CT_MPLSIZE	(2*1024*1024)

/*--------------
	CT FAST	※
--------------*/
extern unsigned char _ct_fast_start[];
#define CT_FAST_START		 (_ct_fast_start)
#define CT_FAST_MPLSIZE	(100*1024)

/*--------------
	GFX TK
--------------*/
extern unsigned char _gfx_tk_start[];
#define GFX_TK_START		 (_gfx_tk_start)
#define GFX_TK_SIZE		(10*1024*1024)	/* K519メモリマップ相当 */

/*--------------
	GFX GM
--------------*/
extern unsigned char _gfx_gm_start[];
#define GFX_GM_START		 (_gfx_gm_start)
#define GFX_GM_SIZE		(12*1024*1024)


/*--------------
	GFX PLANE
--------------*/
extern unsigned char _gfx_plane_lcd0[];
extern unsigned char _gfx_plane_lcd1[];
extern unsigned char _gfx_plane_lout0[];
extern unsigned char _gfx_plane_lout1[];
/* GFXプレーン定義	(gdi.c) */
#define GFX_PLANE_LCD0	 (_gfx_plane_lcd0)
#define GFX_PLANE_LCD1	 (_gfx_plane_lcd1)
#define GFX_PLANE_LOUT0	 (_gfx_plane_lout0)
#define GFX_PLANE_LOUT1	 (_gfx_plane_lout1)
/* 描画プレーン１面のサイズ定義 (RGBA8888) (guiif_avc.c) */
#define GFX_PLANE_LCD_SIZE	(960*640*4)
#define GFX_PLANE_LOUT_SIZE	(960*544*4)// DMP制約により32bitアライメント


/*--------------
	OSD PLANE(LINE)
--------------*/
extern unsigned char _gui_line_plane_lcd0[];
extern unsigned char _gui_line_plane_lcd1[];
extern unsigned char _gui_line_plane_hdmi0[];
extern unsigned char _gui_line_plane_hdmi1[];
extern unsigned char _gui_line_plane_sdi0[];
extern unsigned char _gui_line_plane_sdi1[];
/* OSDプレーンメモリ領域の定義(line_ctrl.c) */
#define LINE_PLANE_LCD0	 (_gui_line_plane_lcd0)
#define LINE_PLANE_HDMI0 (_gui_line_plane_hdmi0)
#define LINE_PLANE_SDI0	 (_gui_line_plane_sdi0)
/* 描画プレーン１面のサイズ定義 (line_ctrl.c) */
#define LINE_MEM_WIDTH_LCD		1024
#define LINE_MEM_HEIGHT_LCD		576
#define LINE_MEM_WIDTH_HDMI		960 // K519ではLOUTなし
#define LINE_MEM_HEIGHT_HDMI	540 // K519ではLOUTなし
#define LINE_MEM_WIDTH_SDI		960 // K519ではLOUTなし
#define LINE_MEM_HEIGHT_SDI		540 // K519ではLOUTなし
#define LINE_PLANE_LCD_SIZE		(LINE_MEM_WIDTH_LCD*LINE_MEM_HEIGHT_LCD)
#define LINE_PLANE_HDMI_SIZE	(LINE_MEM_WIDTH_HDMI*LINE_MEM_HEIGHT_HDMI)
#define LINE_PLANE_SDI_SIZE		(LINE_MEM_WIDTH_SDI*LINE_MEM_HEIGHT_SDI)



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
