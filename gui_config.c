#include "gui_config.h"


unsigned char _gfx_res_start[GFX_RES_SIZE] __attribute__ ((aligned(64), section (".gfx_res_start"), zero_init));
unsigned char _ct_work_start[CT_MPLSIZE] __attribute__ ((aligned(64), section (".ct_work_start"), zero_init));
unsigned char _ct_fast_start[CT_FAST_MPLSIZE] __attribute__ ((aligned(64), section (".ct_fast_start"), zero_init));
unsigned char _gui_work_start[GUI_WORK_SIZE] __attribute__ ((aligned(64), section (".gui_work_start"), zero_init));
unsigned char _gfx_gm_start[GFX_GM_SIZE] __attribute__ ((aligned(64), section (".gfx_gm_start"), zero_init));

//RGBA8888
unsigned char _gfx_plane_lcd0[GFX_PLANE_LCD_SIZE] __attribute__ ((aligned(64), section (".gfx_plane_lcd0"), zero_init));
unsigned char _gfx_plane_lcd1[GFX_PLANE_LCD_SIZE] __attribute__ ((aligned(64), section (".gfx_plane_lcd1"), zero_init));
unsigned char _gfx_plane_lout0[GFX_PLANE_LOUT_SIZE] __attribute__ ((aligned(64), section (".gfx_plane_lout0"), zero_init));
unsigned char _gfx_plane_lout1[GFX_PLANE_LOUT_SIZE] __attribute__ ((aligned(64), section (".gfx_plane_lout1"), zero_init));

unsigned char _gui_line_plane_lcd0[LINE_PLANE_LCD_SIZE] __attribute__ ((aligned(64), section (".gui_line_plane_lcd0"), zero_init));
unsigned char _gui_line_plane_lcd1[LINE_PLANE_LCD_SIZE] __attribute__ ((aligned(64), section (".gui_line_plane_lcd1"), zero_init));
unsigned char _gui_line_plane_hdmi0[LINE_PLANE_HDMI_SIZE] __attribute__ ((aligned(64), section (".gui_line_plane_hdmi0"), zero_init));
unsigned char _gui_line_plane_hdmi1[LINE_PLANE_HDMI_SIZE] __attribute__ ((aligned(64), section (".gui_line_plane_hdmi1"), zero_init));
unsigned char _gui_line_plane_sdi0[LINE_PLANE_SDI_SIZE] __attribute__ ((aligned(64), section (".gui_line_plane_sdi0"), zero_init));
unsigned char _gui_line_plane_sdi1[LINE_PLANE_SDI_SIZE] __attribute__ ((aligned(64), section (".gui_line_plane_sdi1"), zero_init));


