/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#ifndef __GDI_LOCAL_H__
#define __GDI_LOCAL_H__

//#include "gfx.h"
//#include "gdi_ovrb_local.h"


#define GDI_PIXMAP_MAX_VIRTUAL_WIDTH	(424)
#define GDI_PIXMAP_MAX_VIRTUAL_HEIGHT	(240)

#define GDI_ATTRIB_FIXED		(1 << 0)
#define GDI_ATTRIB_HISTOGRAM	(1 << 1)
#define GDI_ATTRIB_TIMESTAMP	(1 << 2)
typedef enum {
	PIXMAP_BLOCK_REC,
	PIXMAP_BLOCK_MJPEG,
	PIXMAP_BLOCK_THUMB,
	PIXMAP_BLOCK_RGBA_LCD,
	PIXMAP_BLOCK_RGBA_LOUT,
	PIXMAP_BLOCK_MAX,

} PIXMAP_BLOCK;

typedef enum {
	TIMESTAMP_LAYOUT_NORMAL,
	TIMESTAMP_LAYOUT_NORMAL_LOUT,
	TIMESTAMP_LAYOUT_90PERCENT,
	TIMESTAMP_LAYOUT_480P_SIDECUT,
	TIMESTAMP_LAYOUT_480I,
	TIMESTAMP_LAYOUT_480I_SIDECUT,
	TIMESTAMP_LAYOUT_480I_LB_100,
	TIMESTAMP_LAYOUT_480I_LB,
	TIMESTAMP_LAYOUT_720P,
	TIMESTAMP_LAYOUT_MAX,
	
} TIMESTAMP_LAYOUT;

typedef enum {
	DATETIME_TYPE_TIME,
	DATETIME_TYPE_DATE,
	DATETIME_TYPE_DATETIME,
	DATETIME_TYPE_MAX,
	
} DATETIME_TYPE;

typedef enum {
	TIMESTAMP_VFORMAT_TYPE_1920_1080,		/* 1920x1080 */ 
	TIMESTAMP_VFORMAT_TYPE_3840_2160,		/* 3840x2160 */
	TIMESTAMP_VFORMAT_TYPE_4096_2160,		/* 4096x2160 */
	TIMESTAMP_VFORMAT_TYPE_1280_720,		/* 1280x720  */
	TIMESTAMP_VFORMAT_TYPE_1440_1080,		/* 1440x1080 */
	TIMESTAMP_VFORMAT_TYPE_MAX,
	
} TIMESTAMP_VFORMAT_TYPE;

#define GDI_TRANS_INDEX			63

#define GDI_DEFAULT_MAX_CROSS	512

#define	GDI_MAKE_RGBA(r, g, b, a)	(((r) << 24) + ((g) << 16) + ((b) << 8) + (a))

#define gdi_itof100(n)		gdi_int_to_float_100[ n ]
#define gdi_itof255(n)		gdi_int_to_float_255[ n ]

#ifdef WIN32_GUI_SIM
#define GDI_TO_PHYADDR(addr)	(unsigned long)addr;
#else
#define GDI_TO_PHYADDR(addr)	(((unsigned long)addr & 0x3FFFFFFF));
#endif

#define	GDI_MAKE_F_RGB(gc_color, gf_color)\
{\
	gf_color[0] = gdi_itof255( ( gc_color >> 24 ) & 0xff );\
	gf_color[1] = gdi_itof255( ( gc_color >> 16 ) & 0xff );\
	gf_color[2] = gdi_itof255( ( gc_color >> 8  ) & 0xff );\
	gf_color[3] = 1.0; /* ïsìßñæ	*/\
}

#define	GDI_MAKE_F_RGBA(gc_color, gf_color)\
{\
	gf_color[0] = gdi_itof255(  ( gc_color >> 24 ) & 0xff  );\
	gf_color[1] = gdi_itof255(  ( gc_color >> 16 ) & 0xff  );\
	gf_color[2] = gdi_itof255(  ( gc_color >> 8  ) & 0xff  );\
	gf_color[3] = gdi_itof255(  ( gc_color       ) & 0xff  );\
}

#define	GDI_MAKE_F_RGB_A(gc_color, gf_color)\
{\
	gf_color[0] = gdi_itof255(  ( gc_color >> 24 ) & 0xff  );\
	gf_color[1] = gdi_itof255(  ( gc_color >> 16 ) & 0xff  );\
	gf_color[2] = gdi_itof255(  ( gc_color >> 8  ) & 0xff  );\
	gf_color[3] = gdi_itof100(  ( gc_color       ) & 0xff  );\
}

#define	GDI_MAKE_F_ARGB(gc_color, gf_color)\
{\
	gf_color[0] = gdi_itof255(  ( gc_color >> 16 ) & 0xff  );\
	gf_color[1] = gdi_itof255(  ( gc_color >> 8  ) & 0xff  );\
	gf_color[2] = gdi_itof255(  ( gc_color       ) & 0xff  );\
	gf_color[3] = gdi_itof255(  ( gc_color >> 24 ) & 0xff  );\
}

//äOïîêÈåæ
extern VGfloat gdi_int_to_float_100[101];
extern VGfloat gdi_int_to_float_255[256];

typedef enum
{
	GDI_SCREEN_LCD,
	GDI_SCREEN_LOUT,
	GDI_SCREEN_REC_HD,
	GDI_SCREEN_MAX,
	GDI_SCREEN_VIRTUAL,
	
} GDI_SCREEN_TYPE;

#if 0
typedef struct _GDI_CONTEXT
{
	EGLSurface read_surface;
	EGLSurface draw_surface;
	EGLContext context;
	EGLenum api;
	
} GDI_CONTEXT;
#endif

typedef enum
{
	GDI_CONTEXT_WINDOW = 1,
	GDI_CONTEXT_PBUFFER,
	GDI_CONTEXT_MAX
	
} GDI_CONTEXT_TYPE;


typedef struct _gdi_context_base
{
	GDI_CONTEXT_TYPE	type;
	GDI_COLOR_FORMAT	format;
	BOOL				update;
	
	VGint				width;
	VGint				height;
	VGint				aln_width;
	VGint				aln_height;
	
} gdi_context_base;


typedef struct _gdi_window_context
{
	GDI_CONTEXT_TYPE	type;
	GDI_COLOR_FORMAT	format;
	BOOL				update;
	
	VGint				width;
	VGint				height;
	VGint				aln_width;
	VGint				aln_height;
	
	GFX_PLANE_ID		plane_id;
	
	unsigned char		*plane_buffer0;
	unsigned char		*plane_buffer1;

	EGLConfig			eglconfig;
	EGLContext			eglcontext;
	EGLNativeWindowType window;
	EGLSurface			eglsurface;
	
} gdi_window_context;

typedef struct _gdi_pbuffer_context
{
	GDI_CONTEXT_TYPE	type;
	GDI_COLOR_FORMAT	format;
	EGLint				*attribs;
	BOOL				update;
	
	VGint				width;
	VGint				height;
	VGint				aln_width;
	VGint				aln_height;

	unsigned char		*color_buffer0;
	unsigned char		*color_buffer1;
	unsigned char		*color_buffer2;
		
	EGLConfig			eglconfig;
	EGLContext			eglcontext;
	EGLSurface			eglsurface;
	
	VGImage				vg_image;
	
} gdi_pbuffer_context;


extern GDI_ERRCODE gdi_vg_init(GDI_COLOR_FORMAT format);
extern void gdi_vg_end();

extern GDI_CACHE_PATH *gdi_alloc_cache_path(void);
extern void gdi_free_cache_path(GDI_CACHE_PATH *path);

extern GDI_CACHE_BITMAP *gdi_alloc_cache_image(void);
extern void gdi_free_cache_image(GDI_CACHE_BITMAP *bitmap);

extern GDI_CACHE_FONT *gdi_alloc_cache_font(void);
extern void gdi_free_cache_font(GDI_CACHE_FONT *font);

extern GDI_CACHE_PATH *gdi_create_parts(const GDI_IMAGE_SVG *svg);
extern void gdi_draw_parts(GDI_CACHE_PATH *cache, VGPaint stroke, VGPaint fill, VGfloat alpha_factor);
//extern void gdi_draw_path(VGPath path, VGint stroke_width, VGPaint stroke, VGPaint fill);

extern GDI_CACHE_SVG *gdi_alloc_cache_svg(void);
extern void gdi_free_cache_svg(GDI_CACHE_SVG *cache_svg);
extern GDI_CACHE_BITMAP *gdi_alloc_cache_bitmap(void);
extern void gdi_free_cache_bitmap(GDI_CACHE_BITMAP *cache_bitmap);
extern GDI_CACHE_FONT *gdi_alloc_cache_font(void);
extern void gdi_free_cache_font(GDI_CACHE_FONT *cache_font);
extern GDI_CACHE_BITMAP_FONT *gdi_alloc_cache_bitmap_font(void);
extern void gdi_free_cache_bitmap_font(GDI_CACHE_BITMAP_FONT *cache_font);
extern GDI_CACHE_PATH *gdi_alloc_cache_path(void);
extern void gdi_free_cache_path(GDI_CACHE_PATH *cache_path);


extern void gdi_get_surface_align(int format, EGLint *width, EGLint *height);

extern GDI_ERRCODE gdi_create_context(GDI_COLOR_FORMAT format);
extern void gdi_delete_context(void);

extern GDI_ERRCODE gdi_switch_context(EGLContext eglcontext, EGLSurface eglsurface);
extern GDI_ERRCODE gdi_switch_pbuffer(gdi_pbuffer_context *pbuffer_context, GDI_DIR pbuffer_dir);

extern GDI_ERRCODE gdi_switch_window(gdi_window_context *window_context);
extern gdi_window_context *gdi_create_window(VGint width, VGint height, GDI_COLOR_FORMAT format, GFX_PLANE_ID plane, unsigned char *buf0, unsigned char *buf1);
extern void gdi_delete_window(gdi_window_context *window_context);
extern gdi_pbuffer_context *gdi_create_pbuffer(INT width, INT height, GDI_COLOR_FORMAT format);
extern gdi_pbuffer_context *gdi_create_pbuffer_static(INT width, INT height, GDI_COLOR_FORMAT format, unsigned char *color_buffer0, unsigned char *color_buffer1);
extern void gdi_delete_pbuffer(gdi_pbuffer_context *pbuffer_context);

VGErrorCode gdi_append_path_line(VGPath path, VGfloat x0, VGfloat y0, VGfloat x1, VGfloat y1);
VGErrorCode gdi_append_path_rect(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height);
VGErrorCode gdi_append_path_roundrect(VGPath path, VGfloat x, VGfloat y, VGfloat width, VGfloat height, VGfloat arc_width, VGfloat arc_height);
VGErrorCode gdi_append_path_ellipse(VGPath path, VGfloat cx, VGfloat cy, VGfloat width, VGfloat height);
VGErrorCode gdi_append_path_polygon(VGPath path, const VGfloat * points, VGint count, VGboolean closed);

extern void *gdi_alloc(int size);
extern void gdi_free(void *ptr);

extern void *gdi_bmp_alloc(int size, int align);
extern void gdi_bmp_free(void *ptr);

extern GDI_ERRCODE gdi_create_color(GDI_COLOR *color_set, VGPaint *ppaint, VGfloat alpha_factor);
extern GDI_ERRCODE gdi_set_figure_data(VGPath path, short figure_type, void *figure_data);

extern gdi_context_base *gdi_get_current_context(void);

#ifdef WIN32_GUI_SIM
extern int gdi_remain_mem_percent();
extern int gdi_bmp_remain_mem_percent();
extern int gui_remain_mem_percent();
#endif

#endif
