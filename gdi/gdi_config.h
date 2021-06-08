#ifndef __GDI_CONFIG_H__
#define __GDI_CONFIG_H__

#ifdef WIN32_GUI_SIM
#include "ext_gevg_malloc.h"
#else
#include "gui_config.h"
#endif

/* [AVC-IF用]入力プレーンサイズ設定 (guiif_avc.c)*/
/* 幅/高さ係数 */
#define LCD_W              960
#define LCD_H              640
#define LOUT_W             960
#define LOUT_H             540
/* メモリ幅係数 */
#define COLOR_SIZE_RGBA4444	2	/* byte/pix */
#define COLOR_SIZE_RGBA8888	4	/* byte/pix */



/* バッファ */ 
/* サイズ */

/* パーティション */



// ----------------------------------------------------------------------
// 定義値 (必要なメモリ量を割りあててください)
// ----------------------------------------------------------------------
// メモリ開始アドレス
#define	MEM_MNG_STATIC_MEMADDR		(char *)(GFX_TK_START)

// メモリブロックサイズ
#define	GEVG_MEM_CONF_ID00_SIZE		(0x20)		// 32
#define	GEVG_MEM_CONF_ID01_SIZE		(0x40)		// 64
#define	GEVG_MEM_CONF_ID02_SIZE		(0x80)		// 128
#define	GEVG_MEM_CONF_ID03_SIZE		(0x100)		// 256
#define	GEVG_MEM_CONF_ID04_SIZE		(0x200)		// 512
#define	GEVG_MEM_CONF_ID05_SIZE		(0x400)		// 1024
#define	GEVG_MEM_CONF_ID06_SIZE		(0x800)		// 2048
#define	GEVG_MEM_CONF_ID07_SIZE		(0x1000)	// 4096
#define	GEVG_MEM_CONF_ID08_SIZE		(0x2000)	// 8192
#define	GEVG_MEM_CONF_ID09_SIZE		(0x4000)	// 16384
#define	GEVG_MEM_CONF_ID10_SIZE		(0x8000)	// 32768
#if 0
#define	GEVG_MEM_CONF_ID11_SIZE		(0x10000)	// 65535
#define	GEVG_MEM_CONF_ID12_SIZE		(0x20000)	// 131072
#define	GEVG_MEM_CONF_ID13_SIZE		(0x40000)	// 262144
#define	GEVG_MEM_CONF_ID14_SIZE		(0x80000)	// 524288
#endif

// メモリブロック数
#define	GEVG_MEM_CONF_ID00_NUM		(1024*2)	// 32    
#define	GEVG_MEM_CONF_ID01_NUM		(1024)		// 64    
#define	GEVG_MEM_CONF_ID02_NUM		(1024*2)	// 128   
#define	GEVG_MEM_CONF_ID03_NUM		(1024)		// 256   
#define	GEVG_MEM_CONF_ID04_NUM		(512)		// 512   
#define	GEVG_MEM_CONF_ID05_NUM		(1024)		// 1024  
#define	GEVG_MEM_CONF_ID06_NUM		(512)		// 2048  
#define	GEVG_MEM_CONF_ID07_NUM		(256)		// 4096  
#define	GEVG_MEM_CONF_ID08_NUM		(128)		// 8192  
#define	GEVG_MEM_CONF_ID09_NUM		(128)		// 16384 
#define	GEVG_MEM_CONF_ID10_NUM		(64)		// 32768
#if 0
#define	GEVG_MEM_CONF_ID11_NUM		(0)		// 65535 
#define	GEVG_MEM_CONF_ID12_NUM		(0)		// 131072
#define	GEVG_MEM_CONF_ID13_NUM		(0)			// 262144
#define	GEVG_MEM_CONF_ID14_NUM		(0)			// 524288
#endif

#define MEM_MNG_STATIC_MEMAREA_SIZE									\
	(MEM_TSZ_MPF(GEVG_MEM_CONF_ID00_SIZE, GEVG_MEM_CONF_ID00_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID01_SIZE, GEVG_MEM_CONF_ID01_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID02_SIZE, GEVG_MEM_CONF_ID02_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID03_SIZE, GEVG_MEM_CONF_ID03_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID04_SIZE, GEVG_MEM_CONF_ID04_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID05_SIZE, GEVG_MEM_CONF_ID05_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID06_SIZE, GEVG_MEM_CONF_ID06_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID07_SIZE, GEVG_MEM_CONF_ID07_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID08_SIZE, GEVG_MEM_CONF_ID08_NUM)	\
	+MEM_TSZ_MPF(GEVG_MEM_CONF_ID09_SIZE, GEVG_MEM_CONF_ID09_NUM)	\
    +MEM_TSZ_MPF(GEVG_MEM_CONF_ID10_SIZE, GEVG_MEM_CONF_ID10_NUM))
	

#ifdef WIN32_GUI_SIM
# define  LOUT_TOP_ADDR      (_gui_lout_top_frame_start0)
# define  LOUT_MID_ADDR      (_gui_lout_mid_frame_start)
# define  LOUT_BOT_ADDR      (_gui_lout_bot_frame_start)
# define  LCD_TOP_ADDR       (_gui_lcd_top_frame_start)
# define  LCD_MID_ADDR       (_gui_lcd_mid_frame_start)
# define  LCD_BOT_ADDR       (_gui_lcd_bot_frame_start)
# define  TEMP_LUT_START	 (_gui_temp_lut_start)
# define  TEMP_LUT1_START	 (_gui_temp_lut1_start)
# define  TEMP_LUT1_END		 (_gui_temp_lut1_end)
# define  TEMP_LUT2_START	 (_gui_temp_lut2_start)
# define  TEMP_LUT2_END		 (_gui_temp_lut2_end)
# define  TEMP_LUT_END		 (_gui_temp_lut_end)
# define  REC_ADDR           (_gui_rec_frame_start)
# define  WORK_ADDR          (_gui_work_start)
# define  GUI_WORK_START     (_gui_work_start)
# define  GUI_WORK_END		 (_gui_work_end)
# define  GUI_WORK_SIZE		 (27*1024*1024-960*544*4*4-419456*4-13184*2-7040*2-156800*4)
# define  GFX_TOP_ADDR		 (_gui_ovg_area)
# define  GFX_TOP_ADDR_T	 (_gui_ovg_area_t) // MMS T.Arakawa 2013/06/28 Add
# define  GFX_PLANE_LCD0	 (_gfx_plane_lcd0)
# define  GFX_PLANE_LCD1	 (_gfx_plane_lcd1)
# define  GFX_SHADOW_LCD_LAYER0		(_gfx_shadow_lcd_layer0)
# define  GFX_SHADOW_LCD_LAYER2		(_gfx_shadow_lcd_layer2)
# define  GFX_PLANE_LOUT0	 (_gfx_plane_lout0)
# define  GFX_PLANE_LOUT1	 (_gfx_plane_lout1)
# define  GFX_SHADOW_LOUT_LAYER0	(_gfx_shadow_lout_layer0)
# define  GFX_SHADOW_LOUT_LAYER2	(_gfx_shadow_lout_layer2)
# define  GFX_WORK_ADDR      (_gui_ovg_work)   // MMS T.Arakawa 2013/07/30 Add
# define  FONT_WORK          (_gui_font_work)  // MMS T.Arakawa 2013/07/30 Add
# define  REC_TITLE          0xC2F8C400        // MMS T.Arakawa 2013/08/08 Add
# define  TWINCAM_REC_FRAME  (_gui_twincam_rec_frame_start) // MMS T.Arakawa 2013/11/28 Add

# define  GFX_RES_START		 (_gfx_res_start)
# define  CT_WORK_START		 (_ct_work_start)
# define  CT_WORK_END		 (_ct_work_end)
# define  CT_MPLSIZE         (2*1024*1024)     /* 2MB */

# define  CT_FAST_START		 (_ct_fast_start)
# define  CT_FAST_END		 (_ct_fast_end)
# define  CT_FAST_MPLSIZE    (100*1024)     /* 100KB */

# define  GFX_RES_END		 (_gfx_res_end)
# define  GFX_RES_SIZE		 (500*1024)
# define  GFX_TK_START		 (_gfx_tk_start)
# define  GFX_TK_END		 (_gfx_tk_end)
# define  GFX_TK_SIZE		 (6*1024*1024)
# define  GFX_GM_START		 (_gfx_gm_start)
# define  GFX_GM_END		 (_gfx_gm_end)
# define  GFX_GM_SIZE		 (10*1024*1024)

# define  GDI_TCC_AREA0_START	(_gdi_tcc_area0_start)
# define  GDI_TCC_AREA0_END		(_gdi_tcc_area0_end)
# define  GDI_TCC_AREA0			(GDI_TCC_AREA0_START)
# define  GDI_TCC_AREA1_START	(_gdi_tcc_area1_start)
# define  GDI_TCC_AREA1_END		(_gdi_tcc_area1_end)
# define  GDI_TCC_AREA1			(GDI_TCC_AREA1_START)
# define  GDI_TCC_AREA0_SIZE	(GDI_TCC_AREA0_END - GDI_TCC_AREA0_START)
# define  GDI_TCC_AREA1_SIZE	(GDI_TCC_AREA1_END - GDI_TCC_AREA1_START)

unsigned char _gui_lout_top_frame_start0[];
unsigned char _gui_lout_mid_frame_start[];
unsigned char _gui_lout_bot_frame_start[];
unsigned char _gui_lcd_top_frame_start[];
unsigned char _gui_lcd_mid_frame_start[];
unsigned char _gui_lcd_bot_frame_start[];
unsigned char _gui_rec_frame_start[];
unsigned char _gui_work_start[GUI_WORK_SIZE];
unsigned char _gui_ovg_area[];
unsigned char _gfx_plane_lcd0[];
unsigned char _gfx_plane_lcd1[];
unsigned char _gfx_shadow_lcd_layer0[];
unsigned char _gfx_shadow_lcd_layer2[];
unsigned char _gfx_plane_lout0[];
unsigned char _gfx_plane_lout1[];
unsigned char _gfx_shadow_lout_layer0[];
unsigned char _gfx_shadow_lout_layer2[];
unsigned char _gui_ovg_area_t[];
unsigned char _gui_ovg_work[];
unsigned char _gui_font_work[];
unsigned char _gui_twincam_rec_frame_start[];
unsigned char _gfx_res_start[GFX_RES_SIZE];
unsigned char _ct_work_start[CT_MPLSIZE];
unsigned char _ct_fast_start[CT_FAST_MPLSIZE];
unsigned char _gfx_res_end[];
unsigned char _gfx_tk_start[MEM_MNG_STATIC_MEMAREA_SIZE];
unsigned char _gfx_tk_end[];
unsigned char _gfx_gm_start[];
unsigned char _gfx_gm_end[];
unsigned char _gdi_tcc_area0_start[];
unsigned char _gdi_tcc_area0_end[];
unsigned char _gdi_tcc_area1_start[];
unsigned char _gdi_tcc_area1_end[];
#endif

#endif
