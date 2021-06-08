/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#include <string.h>
#include "CtDebugPrint.h"

#ifdef WIN32_GUI_SIM
#include "egl.h"
#include "openvg.h"
#else
#define PANA_ORG_FUNC
#define _DMPNATIVE_
#include "EGL/egl.h"

#include "DMP/eglNative.h"
#include "DMP/eglNativePhlox.h"
#include "DMP/eglDMP.h"
#include "DMP/vgDMPX.h"
#endif

#include "gdi.h"
#include "gdi_local.h"
#include "gdi_config.h"

#include "gdi_performance_meas.h"

//------------------------------------------------------------------------------


#ifdef WIN32_GUI_SIM
#if defined(USE_SHIVA_VG) || defined(USE_AMANITH_VG)
EGLint attribs_rgba_window_surface[] = {
	EGL_VG_COLORSPACE,		EGL_VG_COLORSPACE_sRGB,
	EGL_VG_ALPHA_FORMAT,	EGL_VG_ALPHA_FORMAT_NONPRE,
	EGL_WIDTH,				960,
	EGL_HEIGHT,				540,
	EGL_NONE
};
#else
EGLint attribs_rgba_window_surface[] = {
	EGL_VG_COLORSPACE,		EGL_VG_COLORSPACE_sRGB,
	EGL_VG_ALPHA_FORMAT,	EGL_VG_ALPHA_FORMAT_NONPRE,
	EGL_NONE
};
#endif


static EGLint attribs_rgba_surface[] =
{
    EGL_ALPHA_FORMAT,	EGL_ALPHA_FORMAT_NONPRE,
    EGL_COLORSPACE,		EGL_COLORSPACE_sRGB,
	EGL_WIDTH,			0,
	EGL_HEIGHT,			0,
	EGL_COLOR_BUFFER0_ADDRESS_EXT,    0,
	EGL_NONE
};

#else
EGLint attribs_native_window_single[] = {
	EGL_NATIVE_FRAMEBUFFER_TYPE,		EGL_NATIVE_SINGLE_BUFFER,
	EGL_NATIVE_FRAMEBUFFER_ADDRESS1,	(EGLint)NULL,
	EGL_NONE
};

EGLint attribs_native_window_double[] = {
	EGL_NATIVE_FRAMEBUFFER_TYPE,		EGL_NATIVE_DOUBLE_BUFFER,
	EGL_NATIVE_FRAMEBUFFER_ADDRESS1,	(EGLint)NULL,
	EGL_NATIVE_FRAMEBUFFER_ADDRESS2,	(EGLint)NULL,
	EGL_NONE
};

EGLint attribs_rgba_window_surface[] = {
	EGL_VG_COLORSPACE,		EGL_VG_COLORSPACE_sRGB,
	EGL_VG_ALPHA_FORMAT,	EGL_VG_ALPHA_FORMAT_NONPRE,
	EGL_NONE
};

static EGLint attribs_rgba_surface[] =
{
    EGL_ALPHA_FORMAT,	EGL_ALPHA_FORMAT_NONPRE,
    EGL_COLORSPACE,		EGL_COLORSPACE_sRGB,
	EGL_WIDTH,			0,
	EGL_HEIGHT,			0,
    EGL_COLOR_BUFFER0_ADDRESS_EXT,    0,
    EGL_NONE
};
static EGLint attribs_yuv_surface[] =
{
    EGL_ALPHA_FORMAT,	EGL_ALPHA_FORMAT_NONPRE,
    EGL_COLORSPACE,		EGL_COLORSPACE_sRGB,
	EGL_WIDTH,			0,
	EGL_HEIGHT,			0,
	EGL_COLOR_BUFFER0_Y_PLANE_ADDRESS_EXT,	0,
	EGL_COLOR_BUFFER0_UV_PLANE_ADDRESS_EXT,	0,
    EGL_NONE
};

#endif


#ifdef WIN32_GUI_SIM
static const EGLint attribs_rgba8888_config[] = {
	EGL_RED_SIZE,		8,
	EGL_GREEN_SIZE, 	8,
	EGL_BLUE_SIZE,		8,
	EGL_ALPHA_SIZE, 	8,
	EGL_LUMINANCE_SIZE, EGL_DONT_CARE,			//EGL_DONT_CARE
	EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
	EGL_SAMPLES,		1,
	EGL_NONE
};

static const EGLint attribs_rgba4444_config[] = {
	EGL_RED_SIZE,		4,
	EGL_GREEN_SIZE, 	4,
	EGL_BLUE_SIZE,		4,
	EGL_ALPHA_SIZE, 	4,
	EGL_LUMINANCE_SIZE, EGL_DONT_CARE,			//EGL_DONT_CARE
	EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
	EGL_SAMPLES,		1,
	EGL_NONE
};
#else
static const EGLint attribs_rgba8888_config[] = {
	EGL_CONFIG_ID, 6,          /* 6 = RGBA8888, 30 = YUV */
	EGL_NONE
};

static const EGLint attribs_rgba4444_config[] = {
	EGL_CONFIG_ID, 24,          /* 24 = RGBA4444, 30 = YUV */
	EGL_NONE
};

static const EGLint attribs_yuv422sp_config[] = {
	EGL_CONFIG_ID, 30,         /* 30 = YUV422SP */
	EGL_NONE
};

static const EGLint attribs_yuv420sp_config[] = {
	EGL_CONFIG_ID, 36,         /* 36 = YUV420SP */
	EGL_NONE
};
#endif


//------------------------------------------------------------------------------

EGLNativeDisplayType native_display = 0;
EGLDisplay	egldisplay;

EGLConfig	eglconfig_window = (EGLConfig)VG_INVALID_HANDLE;
EGLConfig	eglconfig_yuv422sp = (EGLConfig)VG_INVALID_HANDLE;
EGLConfig	eglconfig_yuv420sp = (EGLConfig)VG_INVALID_HANDLE;

EGLContext	eglcontext_window = (EGLContext)VG_INVALID_HANDLE;
EGLContext	eglcontext_yuv422sp = (EGLContext)VG_INVALID_HANDLE;
EGLContext	eglcontext_yuv420sp = (EGLContext)VG_INVALID_HANDLE;

GDI_COLOR_FORMAT format_window = GDI_COLOR_FORMAT_NONE;

gdi_context_base *current_context = NULL;

VGErrorCode vg_error = VG_NO_ERROR;

#ifdef WIN32_GUI_SIM
extern NativeWindowType GDI_GetNativeWindow(GFX_PLANE_ID plane);
#endif


//------------------------------------------------------------------------------

extern void rm_setEdgeBufferSize(int size);

static GDI_ERRCODE gdi_create_window_surface(gdi_window_context *window_context);
static void gdi_delete_window_surface(gdi_window_context *window_context);

static GDI_ERRCODE gdi_create_pbuffer_surface(gdi_pbuffer_context *pbuffer_context);
static void gdi_delete_pbuffer_surface(gdi_pbuffer_context *pbuffer_context);
static GDI_ERRCODE gdi_alloc_color_buffer(gdi_pbuffer_context *pbuffer_context);
static void gdi_free_color_buffer(gdi_pbuffer_context *pbuffer_context);
static GDI_ERRCODE gdi_bind_pbuffer_image(gdi_pbuffer_context *pbuffer_context);
static void gdi_unbind_pbuffer_image(gdi_pbuffer_context *pbuffer_context);

//------------------------------------------------------------------------------

static EGLint gdi_get_buffer_align(void)
{
	return 128;			// DMP制限 128bytes アラインメント　Phloxソフトウェア仕様書 5.24.2.1章参照
}

void gdi_get_surface_align(int format, EGLint *width, EGLint *height)
{
	if ((width == NULL) || (height == NULL))
		return;
	
	switch (format) {
	case GDI_COLOR_FORMAT_RGBA4444:
	case GDI_COLOR_FORMAT_RGBA8888:
	case GDI_COLOR_FORMAT_YUV422SP:
	case GDI_COLOR_FORMAT_YUV420SP:
		*width = 16;	// DMP制限 横16pixel 単位　Phloxソフトウェア仕様書 3.1.章参照
		*height = 8;	// DMP制限 縦8line 単位　Phloxソフトウェア仕様書 3.1.章参照
		break;
	default:
		*width = 1;
		*height = 1;
		break;
	}
}

static void gdi_get_surface_area(VGint width, VGint height, VGint area[4])
{
	VGint aligned_width, aligned_height;

	if (area == NULL)
		return;
	
	area[0] = width;
	area[1] = height;
	aligned_width = 16;	// DMP制限 横16pixel 単位　Phloxソフトウェア仕様書 3.1.章参照
	aligned_height = 8;	// DMP制限 縦8line 単位　Phloxソフトウェア仕様書 3.1.章参照
	
	// align_*** にアライメントを調整する
	area[2] = (width  + (aligned_width  - 1)) & ~(aligned_width  - 1);
	area[3] = (height + (aligned_height - 1)) & ~(aligned_height - 1);
}



void vg_check(void)
{
	if ((vg_error = vgGetError()) != VG_NO_ERROR) {
//		moridbg(vg_error);
	}
}	


gdi_context_base *gdi_get_current_context(void)
{
	return current_context;
}


//------------------------------------------------------------------------------

GDI_ERRCODE gdi_switch_context(EGLContext eglcontext, EGLSurface eglsurface)
{
	if ((eglcontext == eglGetCurrentContext()) &&
		(eglsurface == eglGetCurrentSurface(EGL_DRAW))) {	// DRAW側だけでいいでしょ！？
		return GDI_NO_ERROR;
	}

	eglMakeCurrent(egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	if (eglcontext != EGL_NO_CONTEXT) {
		eglBindAPI(EGL_OPENVG_API);
		eglMakeCurrent(egldisplay, eglsurface, eglsurface, eglcontext);
	}
	
	return GDI_NO_ERROR;
}

GDI_ERRCODE gdi_create_context(GDI_COLOR_FORMAT format)
{
	EGLint			num_config;
	const EGLint 	*attribs_gfx_config;
	
	if (eglcontext_window != VG_INVALID_HANDLE)
		return GDI_CONTEXT_ERROR;
	
	switch (format) {
	case GDI_COLOR_FORMAT_RGBA8888:
		attribs_gfx_config = attribs_rgba8888_config;
		break;
	case GDI_COLOR_FORMAT_RGBA4444:
		attribs_gfx_config = attribs_rgba4444_config;
		break;
	default:
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	eglChooseConfig(egldisplay, attribs_gfx_config, &eglconfig_window, 1, &num_config);
	if (eglGetError() != EGL_SUCCESS || num_config == 0) {
		eglTerminate( egldisplay ) ;
		return GDI_EGL_ERROR;
	}

	eglcontext_window = eglCreateContext(egldisplay, eglconfig_window, EGL_NO_CONTEXT, NULL);
	if (eglGetError() != EGL_SUCCESS) {
		eglTerminate( egldisplay ) ;
		return GDI_EGL_ERROR;
	}
	format_window = format;

#ifndef WIN32_GUI_SIM
	// YUV422SP コンフィグ取得、コンテキスト取得
	eglChooseConfig(egldisplay, attribs_yuv422sp_config, &eglconfig_yuv422sp, 1, &num_config);
	if (eglGetError() != EGL_SUCCESS || num_config != 1) {
		eglTerminate(egldisplay);
		return GDI_EGL_ERROR;
	}

	eglcontext_yuv422sp = eglCreateContext(egldisplay, eglconfig_yuv422sp, eglcontext_window, NULL);
	if (eglGetError() != EGL_SUCCESS) {
		eglTerminate(egldisplay);
		return GDI_EGL_ERROR;
	}
	
	// YUV420SP コンフィグ取得、取得
	eglChooseConfig(egldisplay, attribs_yuv420sp_config, &eglconfig_yuv420sp, 1, &num_config);
	if (eglGetError() != EGL_SUCCESS || num_config != 1) {
		eglTerminate(egldisplay);
		return GDI_EGL_ERROR;
	}

	eglcontext_yuv420sp = eglCreateContext(egldisplay, eglconfig_yuv420sp, eglcontext_window, NULL);
	if (eglGetError() != EGL_SUCCESS) {
		eglTerminate(egldisplay);
		return GDI_EGL_ERROR;
	}
#endif

	vgSeti(VG_SCISSORING, VG_FALSE) ;
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER) ; /* クオリティ設定 */
#ifndef WIN32_GUI_SIM
	vgSeti(VG_NUM_MAX_CROSS_DMPX, 2048);
#endif
	
	return GDI_NO_ERROR;
}

void gdi_delete_context(void)
{
	gdi_switch_context(EGL_NO_CONTEXT, EGL_NO_SURFACE);
	current_context = NULL;
	
	if (eglcontext_window != VG_INVALID_HANDLE) {
		eglDestroyContext(egldisplay, eglcontext_window);
		eglcontext_window = (EGLContext)VG_INVALID_HANDLE;
		eglconfig_window = (EGLConfig)VG_INVALID_HANDLE;
		format_window = GDI_COLOR_FORMAT_NONE;
	}
#ifndef WIN32_GUI_SIM
	if (eglcontext_yuv422sp != VG_INVALID_HANDLE) {
		eglDestroyContext(egldisplay, eglcontext_yuv422sp);
		eglcontext_yuv422sp = (EGLContext)VG_INVALID_HANDLE;
		eglconfig_yuv422sp = (EGLConfig)VG_INVALID_HANDLE;
	}
	if (eglcontext_yuv420sp != VG_INVALID_HANDLE) {
		eglDestroyContext(egldisplay, eglcontext_yuv420sp);
		eglcontext_yuv420sp = (EGLContext)VG_INVALID_HANDLE;
		eglconfig_yuv420sp = (EGLConfig)VG_INVALID_HANDLE;
	}
#endif	
}
	

GDI_COLOR_FORMAT gdi_get_window_format(void)
{
	return format_window;
}

GDI_ERRCODE gdi_switch_window(gdi_window_context *window_context)
{
	GDI_ERRCODE result;

	if (window_context == NULL)
		return GDI_CONTEXT_ERROR;
	
	result = gdi_switch_context(window_context->eglcontext, window_context->eglsurface);
	current_context = (gdi_context_base *)window_context;
	
	return result;
}

gdi_window_context *gdi_create_window(VGint width, VGint height, GDI_COLOR_FORMAT format, GFX_PLANE_ID plane, unsigned char *buf0, unsigned char *buf1)
{
#ifndef WIN32_GUI_SIM
	VGint area[4];
#endif
	gdi_window_context *window_context = NULL;

	if (eglcontext_window == VG_INVALID_HANDLE) {
		gdi_create_context(format);
	}

	if ((window_context = gdi_alloc(sizeof(*window_context))) == NULL) {
		return NULL;
	}
	
	memset(window_context, 0, sizeof(*window_context));
	
	window_context->type       = GDI_CONTEXT_WINDOW;
	window_context->eglconfig  = eglconfig_window;
	window_context->eglcontext = eglcontext_window;
	window_context->eglsurface = (EGLSurface)VG_INVALID_HANDLE;
	window_context->format     = format;
	window_context->plane_id   = plane;
	window_context->width      = width;
	window_context->height     = height;
	
	window_context->plane_buffer0 = (unsigned char *)GDI_TO_PHYADDR(buf0);
	window_context->plane_buffer1 = (unsigned char *)GDI_TO_PHYADDR(buf1);
	
#ifdef WIN32_GUI_SIM
	window_context->aln_width  = width;		//シミュレータではサイズアライメントは不要
	window_context->aln_height = height;
#else
	gdi_get_surface_area(width, height, area);
	window_context->aln_width  = area[2];
	window_context->aln_height = area[3];
#endif
	
	if (gdi_create_window_surface(window_context) != GDI_NO_ERROR) {
		gdi_free(window_context);
		return NULL;
	}

	gdi_switch_context(window_context->eglcontext, window_context->eglsurface);
	current_context = (gdi_context_base *)window_context;
	
	vgSeti(VG_SCISSORING, VG_FALSE) ;
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER) ; /* クオリティ設定 */
#ifndef WIN32_GUI_SIM
	vgSeti(VG_NUM_MAX_CROSS_DMPX, 2048);
#endif
	
	return window_context;
}

void gdi_delete_window(gdi_window_context *window_context)
{
	int err = 0;
	if (window_context == NULL)
		return;

	gdi_switch_context(EGL_NO_CONTEXT, EGL_NO_SURFACE);
	current_context = NULL;
	
	gdi_delete_window_surface(window_context);
	gdi_free(window_context);
}

static GDI_ERRCODE gdi_create_window_surface(gdi_window_context *window_context)
{
	EGLSurface surface;
	NativeWindowType window;

	if (window_context == NULL)
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
#ifdef WIN32_GUI_SIM
	window = GDI_GetNativeWindow(window_context->plane_id);
	attribs_rgba_window_surface[5] = window_context->aln_width;
	attribs_rgba_window_surface[7] = window_context->aln_height;;
#else
	EGL_NATIVE_COLOR_FORMAT eglformat;
	switch (window_context->format) {
	case GDI_COLOR_FORMAT_RGBA4444:		eglformat = EGL_NATIVE_RGBA_4444;		break;
	case GDI_COLOR_FORMAT_RGBA8888:		eglformat = EGL_NATIVE_RGBA_8888;		break;
	default:							return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	if (window_context->plane_buffer1 == NULL) {
		attribs_native_window_single[3] = (EGLint)window_context->plane_buffer0 & 0x3FFFFF80;
		memset(window_context->plane_buffer0, 0, (window_context->aln_width * window_context->aln_height *4));
		if ((window = eglNativeCreateWindow(native_display, window_context->aln_width, window_context->aln_height, eglformat, attribs_native_window_single)) == NULL)
			return GDI_EGL_ERROR;
	} else {
		attribs_native_window_double[3] = (EGLint)window_context->plane_buffer0 & 0x3FFFFF80;
		attribs_native_window_double[5] = (EGLint)window_context->plane_buffer1 & 0x3FFFFF80;
		memset(window_context->plane_buffer0, 0, (window_context->aln_width * window_context->aln_height *4));
		memset(window_context->plane_buffer1, 0, (window_context->aln_width * window_context->aln_height *4));
		if ((window = eglNativeCreateWindow(native_display, window_context->aln_width, window_context->aln_height, eglformat, attribs_native_window_double)) == NULL)
			return GDI_EGL_ERROR;
	}
#endif
	if ((surface = eglCreateWindowSurface(egldisplay, eglconfig_window, window, attribs_rgba_window_surface)) == EGL_NO_SURFACE)
		return GDI_EGL_ERROR;
	
	window_context->window  = window;
	window_context->eglsurface = surface;

	// カラーバッファを直接参照するため、カラーバッファフォーマットを
	// DMPネイティブから標準フォーマットに変更 - Phlox ソフトウェア仕様書 5.5章
#ifdef WIN32_GUI_SIM
	eglSurfaceAttrib(egldisplay, window_context->eglsurface, 0, 0);
#else
	eglSurfaceAttrib(egldisplay, window_context->eglsurface, EGL_COLOR_BUFFER_FORMAT_DMP, EGL_COLOR_BUFFER_FORMAT_STANDARD_DMP);
#endif
	if (window_context->plane_buffer1 == NULL) {
		eglSurfaceAttrib(egldisplay, window_context->eglsurface, EGL_SWAP_BEHAVIOR, EGL_BUFFER_DESTROYED);
	}

	if (eglGetError() != EGL_SUCCESS) {
		eglDestroySurface(egldisplay, window_context->eglsurface);
		return GDI_CONTEXT_ERROR;
	}

	return GDI_NO_ERROR;
}

static void gdi_delete_window_surface(gdi_window_context *window_context)
{
	if (window_context == NULL)
		return;
	
	if (window_context->eglsurface != VG_INVALID_HANDLE) {
		eglDestroySurface(egldisplay, window_context->eglsurface);
		window_context->eglsurface = (EGLSurface)VG_INVALID_HANDLE;
	}
#ifndef WIN32_GUI_SIM
	if (window_context->window != VG_INVALID_HANDLE) {
		eglNativeDestroyWindow(native_display, window_context->window);
		window_context->window = (EGLContext)VG_INVALID_HANDLE;
	}
#endif
}


GDI_ERRCODE gdi_vg_init(GDI_COLOR_FORMAT format)
{
	/* EGLのディスプレイを取得し初期化 */
	egldisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(egldisplay, NULL, NULL);

	/* レンダリングAPIとしてOpenVGを指定(OpenGL ESとのEGL共存ができるため) */
	gdi_switch_context(EGL_NO_CONTEXT, EGL_NO_SURFACE);
	current_context = NULL;
	
	eglBindAPI(EGL_OPENVG_API);
#if 1
	vgSeti(VG_SCISSORING, VG_FALSE) ;
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER) ; /* クオリティ設定 */
#ifndef WIN32_GUI_SIM
	vgSeti(VG_NUM_MAX_CROSS_DMPX, 2048);
#endif
#endif	
	return GDI_NO_ERROR;
}


void gdi_vg_end()
{
	eglDestroyContext(egldisplay, eglcontext_window);
	eglcontext_window = (EGLContext)VG_INVALID_HANDLE;
	format_window = GDI_COLOR_FORMAT_NONE;

	//終了処理
	gdi_switch_context(EGL_NO_CONTEXT, EGL_NO_SURFACE);
	current_context = NULL;
	
	eglTerminate(egldisplay);
#if USE_AMANITH_VG
	TerminateLibOvg();
#endif
}


static GDI_ERRCODE gdi_alloc_color_buffer(gdi_pbuffer_context *pbuffer_context)
{
	const EGLint align = gdi_get_buffer_align();
	int size0, size1;
	
	if (pbuffer_context == NULL)
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
	switch (pbuffer_context->format) {
	case GDI_COLOR_FORMAT_RGBA8888:
		size0 = pbuffer_context->aln_width * pbuffer_context->aln_height * 4;
		size1 = 0;
		break;
	case GDI_COLOR_FORMAT_RGBA4444:
		size0 = pbuffer_context->aln_width * pbuffer_context->aln_height * 2;
		size1 = 0;
		break;
	case GDI_COLOR_FORMAT_YUV422SP:
		size0 = pbuffer_context->aln_width * pbuffer_context->aln_height;	// Y  size = width * height
		size1 = size0;														// CbCr size = Y size
		break;
	case GDI_COLOR_FORMAT_YUV420SP:
		size0 = pbuffer_context->aln_width * pbuffer_context->aln_height;	// Y size = width * height
		size1 = size0/2;													// CbCr size = Y size/2
		break;
	default:
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	if (size0 != 0) {
		pbuffer_context->color_buffer0 = (unsigned char *)gdi_bmp_alloc(size0, align);
		if (pbuffer_context->color_buffer0 == NULL) {
			return GDI_OUT_OF_MEMORY_ERROR;
		}
		memset(pbuffer_context->color_buffer0, 0, size0);
	} else {
		pbuffer_context->color_buffer0 = NULL;
	}

	if (size1 != 0) {
		pbuffer_context->color_buffer1 = (unsigned char *)gdi_bmp_alloc(size1, align);
		if (pbuffer_context->color_buffer1 == NULL) {
			return GDI_OUT_OF_MEMORY_ERROR;
		}
		memset(pbuffer_context->color_buffer1, 0, size1);
	} else {
		pbuffer_context->color_buffer1 = NULL;
	}

	return GDI_NO_ERROR;
}

static void gdi_free_color_buffer(gdi_pbuffer_context *pbuffer_context)
{
	if (pbuffer_context == NULL)
		return;
	
	if (pbuffer_context->color_buffer0) {
		gdi_bmp_free(pbuffer_context->color_buffer0);
		pbuffer_context->color_buffer0 = NULL;
	}
	
	if (pbuffer_context->color_buffer1) {
		gdi_bmp_free(pbuffer_context->color_buffer1);
		pbuffer_context->color_buffer1 = NULL;
	}
}

gdi_pbuffer_context *gdi_create_pbuffer(VGint width, VGint height, GDI_COLOR_FORMAT format)
{
	gdi_pbuffer_context *pbuffer_context = NULL;
	VGint area[4];
	int err = 0;
	
	if ((pbuffer_context = gdi_alloc(sizeof(*pbuffer_context))) == NULL) {
		CtDebugPrint(CtDbg, "create pbuffer failed... allocate memory error\n");
		return NULL;
	}
	memset(pbuffer_context, 0, sizeof(*pbuffer_context));
	
	switch (format) {
	case GDI_COLOR_FORMAT_RGBA8888:
		pbuffer_context->eglconfig = eglconfig_window;
		pbuffer_context->eglcontext = eglcontext_window;
		pbuffer_context->attribs = attribs_rgba_surface;
		pbuffer_context->format = format;
		break;
	case GDI_COLOR_FORMAT_RGBA4444:
	case GDI_COLOR_FORMAT_DEFAULT:
		pbuffer_context->eglconfig = eglconfig_window;
		pbuffer_context->eglcontext = eglcontext_window;
		pbuffer_context->attribs = attribs_rgba_surface;
		pbuffer_context->format = GDI_COLOR_FORMAT_RGBA4444;
		break;
#ifndef WIN32_GUI_SIM
	case GDI_COLOR_FORMAT_YUV422SP:
		pbuffer_context->eglconfig = eglconfig_yuv422sp;
		pbuffer_context->eglcontext = eglcontext_yuv422sp;
		pbuffer_context->attribs = attribs_yuv_surface;
		pbuffer_context->format = format;
		break;
	case GDI_COLOR_FORMAT_YUV420SP:
		pbuffer_context->eglconfig = eglconfig_yuv420sp;
		pbuffer_context->eglcontext = eglcontext_yuv420sp;
		pbuffer_context->attribs = attribs_yuv_surface;
		pbuffer_context->format = format;
		break;
#endif
	default:	return NULL;
	}
	
	pbuffer_context->type   = GDI_CONTEXT_PBUFFER;
	pbuffer_context->eglsurface = (EGLSurface)VG_INVALID_HANDLE;
	
	pbuffer_context->width  = width;
	pbuffer_context->height = height;
	
	gdi_get_surface_area(width, height, area);
	pbuffer_context->aln_width  = area[2];
	pbuffer_context->aln_height = area[3];

	if (gdi_alloc_color_buffer(pbuffer_context) != GDI_NO_ERROR) {
		gdi_free(pbuffer_context);
		CtDebugPrint(CtDbg, "create pbuffer failed... allocate color buffer error\n");
		return NULL;
	}
	if (gdi_create_pbuffer_surface(pbuffer_context) != GDI_NO_ERROR) {
		CtDebugPrint(CtDbg, "create pbuffer failed... create surface error\n");
		gdi_free_color_buffer(pbuffer_context);
		gdi_free(pbuffer_context);
		return NULL;
	}

	gdi_switch_context(pbuffer_context->eglcontext, pbuffer_context->eglsurface);
	current_context = (gdi_context_base *)pbuffer_context;
	
	vgSeti(VG_SCISSORING, VG_FALSE) ;
	vgSeti(VG_RENDERING_QUALITY, VG_RENDERING_QUALITY_BETTER) ; /* クオリティ設定 */
#ifndef WIN32_GUI_SIM
	vgSeti(VG_NUM_MAX_CROSS_DMPX, 2048);
#endif

	return pbuffer_context;
}

gdi_pbuffer_context *gdi_create_pbuffer_static(VGint width, VGint height, GDI_COLOR_FORMAT format, unsigned char *color_buffer0, unsigned char *color_buffer1)
{
	gdi_pbuffer_context *pbuffer_context = NULL;
	VGint area[4];
	
	if ((pbuffer_context = gdi_alloc(sizeof(*pbuffer_context))) == NULL) {
		return NULL;
	}
	
	memset(pbuffer_context, 0, sizeof(*pbuffer_context));
	
	switch (format) {
	case GDI_COLOR_FORMAT_RGBA8888:
		pbuffer_context->eglconfig = eglconfig_window;
		pbuffer_context->eglcontext = eglcontext_window;
		pbuffer_context->attribs = attribs_rgba_surface;
		pbuffer_context->format = format;
		break;
	case GDI_COLOR_FORMAT_RGBA4444:
	case GDI_COLOR_FORMAT_DEFAULT:
		pbuffer_context->eglconfig = eglconfig_window;
		pbuffer_context->eglcontext = eglcontext_window;
		pbuffer_context->attribs = attribs_rgba_surface;
		pbuffer_context->format = format;
		break;
#ifndef WIN32_GUI_SIM
	case GDI_COLOR_FORMAT_YUV422SP:
		pbuffer_context->eglconfig = eglconfig_yuv422sp;
		pbuffer_context->eglcontext = eglcontext_yuv422sp;
		pbuffer_context->attribs = attribs_yuv_surface;
		pbuffer_context->format = format;
		break;
	case GDI_COLOR_FORMAT_YUV420SP:
		pbuffer_context->eglconfig = eglconfig_yuv420sp;
		pbuffer_context->eglcontext = eglcontext_yuv420sp;
		pbuffer_context->attribs = attribs_yuv_surface;
		pbuffer_context->format = format;
		break;
#endif
	default:	return NULL;
	}
	
	pbuffer_context->type   = GDI_CONTEXT_PBUFFER;
	pbuffer_context->eglsurface = (EGLSurface)VG_INVALID_HANDLE;
	
	pbuffer_context->width = width;
	pbuffer_context->height = height;
	
	gdi_get_surface_area(width, height, area);
	pbuffer_context->aln_width = area[2];
	pbuffer_context->aln_height = area[3];
	
	pbuffer_context->color_buffer0 = color_buffer0;
	pbuffer_context->color_buffer1 = color_buffer1;

	if (gdi_create_pbuffer_surface(pbuffer_context) != GDI_NO_ERROR) {
		gdi_free(pbuffer_context);
		return NULL;
	}
	
	return pbuffer_context;
}

void gdi_delete_pbuffer(gdi_pbuffer_context *pbuffer_context)
{
	int err = 0;
	
	if (pbuffer_context == NULL) {
		return;
	}
	
	gdi_unbind_pbuffer_image(pbuffer_context);
	gdi_delete_pbuffer_surface(pbuffer_context);
	gdi_free_color_buffer(pbuffer_context);
	gdi_free(pbuffer_context);

	if ((err = eglGetError()) != EGL_SUCCESS) {
	}
}

static GDI_ERRCODE gdi_create_pbuffer_surface(gdi_pbuffer_context *pbuffer_context)
{
	int err = 0;
	EGLint *attribs = NULL;

	if (pbuffer_context == NULL)		return GDI_ILLEGAL_ARGUMENT_ERROR;
	if (pbuffer_context->attribs == NULL)	return GDI_CONTEXT_ERROR;
	
	attribs = pbuffer_context->attribs;
	attribs[ 5] = (EGLint)pbuffer_context->aln_width;
	attribs[ 7] = (EGLint)pbuffer_context->aln_height;
#ifdef WIN32_GUI_SIM
	attribs[ 9] = (EGLint)pbuffer_context->color_buffer0;
	if (pbuffer_context->format == GDI_COLOR_FORMAT_YUV422SP || pbuffer_context->format == GDI_COLOR_FORMAT_YUV420SP)
		attribs[11] = (EGLint)pbuffer_context->color_buffer1;
#else
	attribs[ 9] = (EGLint)pbuffer_context->color_buffer0 & 0x3FFFFF80;
	if (pbuffer_context->format == GDI_COLOR_FORMAT_YUV422SP || pbuffer_context->format == GDI_COLOR_FORMAT_YUV420SP)
		attribs[11] = (EGLint)pbuffer_context->color_buffer1 & 0x3FFFFF80;
#endif
	pbuffer_context->eglsurface = eglCreatePbufferSurface(egldisplay, pbuffer_context->eglconfig, attribs);
	if (eglGetError() != EGL_SUCCESS) {
		CtDebugPrint(CtDbg, " create pbuffer failed1\n");
		goto error;
	}
	
#ifdef WIN32_GUI_SIM
	eglSurfaceAttrib(egldisplay, pbuffer_context->eglsurface, 0, 0);
#else
	// カラーバッファを直接参照するため、カラーバッファフォーマットを
	// DMPネイティブから標準フォーマットに変更 - Phlox ソフトウェア仕様書 5.5章
	eglSurfaceAttrib(egldisplay, pbuffer_context->eglsurface, EGL_COLOR_BUFFER_FORMAT_DMP, EGL_COLOR_BUFFER_FORMAT_STANDARD_DMP);
#endif
	if (eglGetError() != EGL_SUCCESS) {
		CtDebugPrint(CtDbg, " create pbuffer failed2\n");
		goto error;
	}

	return GDI_NO_ERROR;

  error:
	if (pbuffer_context->eglsurface != VG_INVALID_HANDLE) {
		eglDestroySurface(egldisplay, pbuffer_context->eglsurface);
		pbuffer_context->eglsurface = (EGLSurface)VG_INVALID_HANDLE;
	}
	pbuffer_context->eglconfig  = (EGLConfig)VG_INVALID_HANDLE; 
	pbuffer_context->eglcontext = (EGLContext)VG_INVALID_HANDLE; 
	return GDI_CONTEXT_ERROR;
}

static GDI_ERRCODE gdi_bind_pbuffer_image(gdi_pbuffer_context *pbuffer_context)
{
	unsigned char* buf0 = NULL;
	unsigned char* buf1 = NULL;
	EGLint width = 0;
	EGLint height = 0;
	EGLint size0 = 0, size1 = 0;
	VGImageFormat format;
	
	if (pbuffer_context == NULL)
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	
#ifdef WIN32_GUI_SIM
	buf0 = pbuffer_context->color_buffer0;
	buf1 = pbuffer_context->color_buffer1;
#else
	buf0 = (unsigned char*)((long)pbuffer_context->color_buffer0 & 0x3FFFFF80);
	buf1 = (unsigned char*)((long)pbuffer_context->color_buffer1 & 0x3FFFFF80);
#endif
	width = pbuffer_context->aln_width;
	height = pbuffer_context->aln_height;

	if (pbuffer_context->vg_image != VG_INVALID_HANDLE) return GDI_NO_ERROR;
	
	switch (pbuffer_context->format) {
	case GDI_COLOR_FORMAT_RGBA8888:
		format = VG_sRGBA_8888;
		size0 = width * height *4;
		pbuffer_context->vg_image = vgCreateImageStandardDataDMP(format, width, height, size0, buf0, VG_IMAGE_QUALITY_FASTER);
		break;
	case GDI_COLOR_FORMAT_RGBA4444:
	case GDI_COLOR_FORMAT_DEFAULT:
		format = VG_sRGBA_4444;
		size0 = width * height *2;
		pbuffer_context->vg_image = vgCreateImageStandardDataDMP(format, width, height, size0, buf0, VG_IMAGE_QUALITY_FASTER);
		break;
#ifndef WIN32_GUI_SIM
	case GDI_COLOR_FORMAT_YUV422SP:
		format = VG_sYUV_422_SEMIPLANAR_DMP;
		size0 = width * height;
		size1 = size0;
		pbuffer_context->vg_image = vgCreateImageStandardDataYUVsemiplanarDMP(format, width, height, size0, size1, buf0, buf1, VG_IMAGE_QUALITY_FASTER);
		break;
	case GDI_COLOR_FORMAT_YUV420SP:
		format = VG_sYUV_420_SEMIPLANAR_DMP;
		size0 = width * height;
		size1 = size0 / 2;
		pbuffer_context->vg_image = vgCreateImageStandardDataYUVsemiplanarDMP(format, width, height, size0, size1, buf0, buf1, VG_IMAGE_QUALITY_FASTER);
		break;
#endif
	default:
		CtDebugPrint(CtDbg, "bind pbuffer failed... color format error\n");
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	if ((vg_error = vgGetError()) != VG_NO_ERROR) {
		CtDebugPrint(CtDbg, "pbuffer bind image failed... hdr: %p, err: 0x%08x\n", pbuffer_context, vg_error);
		pbuffer_context->vg_image = VG_INVALID_HANDLE;
		return GDI_CONTEXT_ERROR;
	}

	return GDI_NO_ERROR;
}


static void gdi_delete_pbuffer_surface(gdi_pbuffer_context *pbuffer_context)
{
	if (pbuffer_context == NULL)
		return;

	if (pbuffer_context->eglsurface != VG_INVALID_HANDLE) {
		eglDestroySurface(egldisplay, pbuffer_context->eglsurface);
		pbuffer_context->eglsurface = (EGLSurface)VG_INVALID_HANDLE;
	}
}

GDI_ERRCODE gdi_switch_pbuffer(gdi_pbuffer_context *pbuffer_context, GDI_DIR pbuffer_dir)
{
	GDI_ERRCODE result;

	if (pbuffer_context == NULL)
		return GDI_ILLEGAL_ARGUMENT_ERROR;

	if (pbuffer_dir == GDI_DIR_DRAW) {
		if (pbuffer_context->vg_image != VG_INVALID_HANDLE) {
			gdi_unbind_pbuffer_image(pbuffer_context);
		}
		if (pbuffer_context->eglsurface == VG_INVALID_HANDLE) {
			if ((result = gdi_create_pbuffer_surface(pbuffer_context)) != GDI_NO_ERROR) {
				return result;
			}
		}
		gdi_switch_context(pbuffer_context->eglcontext, pbuffer_context->eglsurface);
		current_context = (gdi_context_base *)pbuffer_context;
		
	} else {
		if (pbuffer_context->vg_image == VG_INVALID_HANDLE) {
			return gdi_bind_pbuffer_image(pbuffer_context);
		}
	}
	
	return GDI_NO_ERROR;
}

static void gdi_unbind_pbuffer_image(gdi_pbuffer_context *pbuffer_context)
{
	if (pbuffer_context == NULL)
		return;
	
	if (pbuffer_context->vg_image != VG_INVALID_HANDLE) {
		vgDestroyImage(pbuffer_context->vg_image);
		pbuffer_context->vg_image = VG_INVALID_HANDLE;
	}
}


#if 0
/* サーフェースのバックバッファ番号を取得 */
int gdi_get_surface_backbuffer(EGLSurface surface)
{
	EGLNativeWindowType	window;
	VGint value;
	
	/* NativeWindow取得 */
	eglGetNativeWindow(egldisplay, surface, &window);
	/* パラメータ取得 */
	eglNativeQueryWindow(native_display, window, EGL_NATIVE_BACK_BUFFER_INDEX, &value);
	
	return (int)value;
}

/* サーフェースのカラーバッファ０を取得 */
void* gdi_get_colorbuffer0(EGLSurface surface)
{
	EGLNativeWindowType	window;
	void *value;
	
	/* NativeWindow取得 */
	eglGetNativeWindow(egldisplay, surface, &window);
	/* パラメータ取得 */
	eglNativeQueryWindowPointer(native_display, window, EGL_NATIVE_PHYSICAL_ADDRESS0, &value);
	
	return value;
}

/* サーフェースのカラーバッファ１を取得 */
void* gdi_get_colorbuffer1(EGLSurface surface)
{
	EGLNativeWindowType	window;
	void *value;
	
	/* NativeWindow取得 */
	eglGetNativeWindow(egldisplay, surface, &window);
	/* パラメータ取得 */
	eglNativeQueryWindowPointer(native_display, window, EGL_NATIVE_PHYSICAL_ADDRESS1, &value);
	
	return value;
}

short gdi_vg_flush( EGLSurface egl_surface, int *back_buffer )
{
	DBGPRINTF(dbgprintf("gmw_VgFlush\n"));


    /* 描画面と表示面を切換え */
    eglSwapBuffers( s_win_egl_display, egl_surface );
    /* バックバッファ番号返す */
    *back_buffer = gdi_get_surface_backbuffer(egl_surface);

	return TRUE;
}


void gdi_vg_finish(void)
{
	DBGPRINTF(dbgprintf("gmw_VgFinish\n"));
	
	vgFinish();

#if 0
	{
		VGint	path_full, fill_full;
		VGint	path_overflow, fill_overflow;
		
		/* コマンドバッファフルチェック */
		path_full = vgGeti(VG_PATH_COMMANDBUFFER_FULL_DMP);
		fill_full = vgGeti(VG_FILL_COMMANDBUFFER_FULL_DMP);
		path_overflow = vgGeti(VG_PATH_COMMANDBUFFER_OVERFLOW_DMP);
		fill_overflow = vgGeti(VG_FILL_COMMANDBUFFER_OVERFLOW_DMP);
		if (path_full || fill_full || path_overflow || fill_overflow) {
			dbgprintf("CB: path_full=%d fill_full=%d path_overflow=%d fill_overflow=%d\r\n",
				path_full, fill_full, path_overflow, fill_overflow);
		}
	}
#endif

}

/*
 *	<summary>		:	描画内容を裏面にコピーする
 *
 *	<parameter>		:	GMW_SURFACE_INFO  *surface_info		サーフェイス情報
 *						short			  x				    X座標
 *						short			  y				    Y座標
 *						short			  width			    幅
 *						short			  height			高さ
 *						unsigned short	  color_depth		色深度
 *
 *	<return>		:	TRUE		: 処理成功
 *						FALSE		: 処理失敗
 *
 *	<description>	:	本関数は、OpenVGを使用して描画した内容をディスプレイに
 *						反映させる。
 *		
 */
short gmw_VgCopyToBack( GMW_SURFACE_INFO *surface_info, short x, short y, short width, short height,  unsigned short color_depth )
{
	DBGPRINTF(dbgprintf("gmw_VgCopyToBack\n"));
	{
		VGImage src_image;
		VGImageFormat format = VG_sRGBA_8888_PRE;
		unsigned char *src_buffer;
		int surface_width, surface_height;

		if (surface_info == NULL)
			return FALSE;
		
		/* 色深度による設定変更 */
		if (GMW_BYTE_PER_PIXEL_4444 == color_depth) {
			format = VG_sRGBA_4444;
		}

		if(surface_info->back_buffer == 0) {
			src_buffer = (unsigned char*)surface_info->color_buffer1;
		} else {
			src_buffer = (unsigned char*)surface_info->color_buffer0;
		}
		surface_width = surface_info->width;
		surface_height = surface_info->height;

		src_image = vgCreateImageStandardDataDMP(format, surface_width, surface_height,
												surface_width * surface_height * color_depth,
												(void*)MEM_CNV_LSIADR_TO_CPUADR_NC((ULONG)src_buffer),
												VG_IMAGE_QUALITY_NONANTIALIASED);		//フィルタ無効
		{
			static VGfloat matrix_ini[] = { ( VGfloat )GMW_SIZE_X / ( VGfloat )GMW_SIZE_X, 0.0f, 0.0f,
											0.0f, ( VGfloat )-GMW_SIZE_Y / ( VGfloat )GMW_SIZE_Y, 0.0f,
											0.0f, ( VGfloat )GMW_SIZE_Y, 1.0f } ;

			/* 上下反転の高さを表示画面にあわせる */
			matrix_ini[6] = (VGfloat)x;
			matrix_ini[7] = (VGfloat)(surface_height - y);
			/* イメージに対して変形設定 */
			vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
			vgLoadMatrix( matrix_ini );
		}
		/* ブレンドモードを上書きに設定 */
		vgSeti( VG_BLEND_MODE, VG_BLEND_SRC );
		/* クリップOFF */
		gmw_VgSetClipArea( FALSE, 0, 0, 0, 0 );
		/* イメージの部分描画 */
		vgDrawSubImageDMP(src_image, x, y, width, height);
		/* 変換行列を戻す */
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
		vgLoadIdentity();
#if 0	/* vgCreateImageStandardDataDMPで作成したイメージは削除前にvgFinishが必要であるが
		   サーフェイスのメモリは解放されないので省略して高速化 */
		vgFinish();
#endif
		vgDestroyImage(src_image);
		gmw_VgSetAlphaBlendMode( GMW_ALPHA_OVER );
	}
	
	return TRUE;
}

#endif

