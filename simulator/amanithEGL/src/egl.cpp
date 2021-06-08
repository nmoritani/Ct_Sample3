#include "amanithVG.h"
#include "EGL/egl.h"
#include "EGL/egl_types.h"
#include "amanithvg/vgext.h"
#include "libOvgMng.h"


// Windows variables
char vgSurfaceBitmapBuffer[sizeof(BITMAPINFO) + 16];
BITMAPINFO *vgSurfaceBitmapInfo = NULL;
static void (*callback)(int, int, int, void*) = NULL;

// OpenVG variables
static EGLContext s_lcd_context = EGL_NO_CONTEXT;
static EGLContext s_current_context = EGL_NO_CONTEXT;
static EGLSurface s_lcd_surface = EGL_NO_SURFACE;
static EGLSurface s_current_surface = EGL_NO_SURFACE;


//egl関数(とりあえず最低限のみ実装)
EGLBoolean eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
	return EGL_TRUE;
}

EGLint eglGetError(void)
{
	VGErrorCode err;
	err = vgGetError();
	if (VG_NO_CONTEXT_ERROR == err) err = VG_NO_ERROR;
	return (VG_NO_ERROR == err) ? EGL_SUCCESS : EGL_BAD_ACCESS;
}

static void CreateBitmapHeader(VGImageFormat surfaceFormat, int surfaceWidth, int surfaceHeight)
{
	// create bitmap header
	if (NULL == vgSurfaceBitmapInfo) {
		int i;
		for (i = 0; i < sizeof(BITMAPINFOHEADER) + 16; ++i)
			vgSurfaceBitmapBuffer[i] = 0;
		vgSurfaceBitmapInfo = (BITMAPINFO *)&vgSurfaceBitmapBuffer;
		vgSurfaceBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		vgSurfaceBitmapInfo->bmiHeader.biPlanes = 1;
		vgSurfaceBitmapInfo->bmiHeader.biCompression = BI_BITFIELDS;
	}

	switch (surfaceFormat) {

		// RGB{A,X} channel ordering
	case VG_sRGBX_8888:
	case VG_sRGBA_8888:
	case VG_sRGBA_8888_PRE:
	case VG_lRGBX_8888:
	case VG_lRGBA_8888:
	case VG_lRGBA_8888_PRE:
		vgSurfaceBitmapInfo->bmiHeader.biBitCount = 32;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[0] = 0xFF000000;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[1] = 0x00FF0000;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[2] = 0x0000FF00;
		break;

		// {A,X}RGB channel ordering
	case VG_sXRGB_8888:
	case VG_sARGB_8888:
	case VG_sARGB_8888_PRE:
	case VG_lXRGB_8888:
	case VG_lARGB_8888:
	case VG_lARGB_8888_PRE:
		vgSurfaceBitmapInfo->bmiHeader.biBitCount = 32;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[0] = 0x00FF0000;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[1] = 0x0000FF00;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[2] = 0x000000FF;
		break;

		// BGR{A,X} channel ordering
	case VG_sBGRX_8888:
	case VG_sBGRA_8888:
	case VG_sBGRA_8888_PRE:
	case VG_lBGRX_8888:
	case VG_lBGRA_8888:
	case VG_lBGRA_8888_PRE:
		vgSurfaceBitmapInfo->bmiHeader.biBitCount = 32;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[0] = 0x0000FF00;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[1] = 0x00FF0000;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[2] = 0xFF000000;
		break;

		// {A,X}BGR channel ordering
	case VG_sXBGR_8888:
	case VG_sABGR_8888:
	case VG_sABGR_8888_PRE:
	case VG_lXBGR_8888:
	case VG_lABGR_8888:
	case VG_lABGR_8888_PRE:
		vgSurfaceBitmapInfo->bmiHeader.biBitCount = 32;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[0] = 0x000000FF;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[1] = 0x0000FF00;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[2] = 0x00FF0000;
		break;

		// support for AmanithVG SRE Lite (16bpp internal drawing surfaces)
	case VG_sRGB_565:
		vgSurfaceBitmapInfo->bmiHeader.biBitCount = 16;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[0] = 0xF800;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[1] = 0x07E0;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[2] = 0x001F;
		break;

	case VG_sBGR_565:
		vgSurfaceBitmapInfo->bmiHeader.biBitCount = 16;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[0] = 0x001F;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[1] = 0x07E0;
		((unsigned long *)vgSurfaceBitmapInfo->bmiColors)[2] = 0xF800;
		break;
	}

	vgSurfaceBitmapInfo->bmiHeader.biWidth = surfaceWidth;
	vgSurfaceBitmapInfo->bmiHeader.biHeight = -surfaceHeight;
}


void swapBuffers(EGLSurface surface)
{
	EGLsurface		*internal_surface = (EGLsurface*)surface;

	// get AmanithVG surface dimensions and pixels pointer
	int surfaceWidth = amanith_vg_privgetsurfacewidthAM(internal_surface->vgWindowSurface);
	int surfaceHeight = amanith_vg_privgetsurfaceheightAM(internal_surface->vgWindowSurface);
	VGImageFormat surfaceFormat = amanith_vg_privgetsurfaceformatAM(internal_surface->vgWindowSurface);
	void* surfacePixels = (void*)amanith_vg_privgetsurfacepixelsAM(internal_surface->vgWindowSurface);

	CreateBitmapHeader(surfaceFormat, surfaceWidth, surfaceHeight);

	if (callback) {
		// 画像データを通知
		int dpy = (surface == s_lcd_surface) ? 0 : 1;
		callback(dpy, surfaceWidth, surfaceHeight, surfacePixels);
	}
}

void eglSetSwapCallback(void(*draw_callback)(int dpy, int w, int h, void* bmp_data) )
{
	callback = draw_callback;
}

EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	EGLsurface		*internal_surface = (EGLsurface*)surface;

	/* 描画完了待ち */
	swapBuffers(surface);
	internal_surface->back_buffer ^= 1;

	amanith_vg_postswapbuffersAM();

	return EGL_TRUE;
}


EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	EGLsurface		*internal_surface = (EGLsurface*)surface;
	BOOL			IsCurrentSurface = (surface == s_current_surface);

	if (NULL == internal_surface) {
		return EGL_TRUE;
	}

	if (NULL != internal_surface->color_buffer0) {
		if (internal_surface->type == PBUFFER) {
			//PBUFFERのカラーバッファはクライアント側から作らせるので、ここでfreeしない
			//free(internal_surface->color_buffer0);
		} else {
			free(internal_surface->color_buffer0);
			internal_surface->color_buffer0 = NULL;
		}
	}
	if (NULL != internal_surface->color_buffer1) {
		if (internal_surface->type == PBUFFER) {
			//PBUFFERのカラーバッファはクライアント側から作らせるので、ここでfreeしない
			//free(internal_surface->color_buffer1);
		} else {
			free(internal_surface->color_buffer1);
			internal_surface->color_buffer1 = NULL;
		}
	}
	if (EGL_NO_SURFACE != internal_surface->vgWindowSurface) {
		amanith_vg_privsurfacedestroyAM(internal_surface->vgWindowSurface);
		internal_surface->vgWindowSurface = EGL_NO_SURFACE;
	}

	if (VG_INVALID_HANDLE != internal_surface->vgImage_Pbuffer) {
	    vgDestroyImage(internal_surface->vgImage_Pbuffer);
	}

	if (EGL_NO_SURFACE != internal_surface->vgPbufferSurface) {
		amanith_vg_privsurfacedestroyAM(internal_surface->vgPbufferSurface);
		internal_surface->vgPbufferSurface = EGL_NO_SURFACE;
	}

	if (NULL != internal_surface->config) {
		free(internal_surface->config);
		internal_surface->config = NULL;
	}
	if (NULL != internal_surface) {
		free(internal_surface);
	}
	internal_surface = NULL;

	if (IsCurrentSurface) {
		s_current_surface = EGL_NO_SURFACE;
	}

	return EGL_TRUE;
}


EGLSurface eglGetCurrentSurface(EGLint readdraw)
{
	return s_current_surface;
}


EGLContext eglGetCurrentContext(void)
{
	return s_current_context;
}


EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	EGLcontext		*internal_ctx = (EGLcontext*)ctx;
	EGLsurface		*internal_surface = (EGLsurface*)draw;
	VGboolean		err;

	if (s_current_surface != EGL_NO_SURFACE) {
		vgFinish();
	}

	if (ctx == EGL_NO_CONTEXT || draw == EGL_NO_SURFACE) {
		amanith_vg_privmakecurrentAM(NULL, NULL);
		s_current_surface = EGL_NO_SURFACE;
		s_current_context = EGL_NO_CONTEXT;
		return EGL_TRUE;
	}

	/* コンテキストが未作成なら作成 */
	if (NULL == internal_ctx->vgContext) {
		/* コンテキスト作成 */
		internal_ctx->vgContext = amanith_vg_privcontextcreateAM(NULL);

		if (NULL == internal_ctx->vgContext) {
			return EGL_FALSE;
		}
	} else {
		//作成済みの場合はリサイズ
		amanith_vg_resizesurfaceAM(internal_surface->surface_width, internal_surface->surface_height);
	}

	void *surface = (PBUFFER == internal_surface->type) ? internal_surface->vgPbufferSurface : internal_surface->vgWindowSurface;

	// コンテキストとサーフェイスのバインド
	err = amanith_vg_privmakecurrentAM(internal_ctx->vgContext, surface);
	if (VG_FALSE == err) {
		eglDestroySurface(dpy, draw);
		s_current_surface = EGL_NO_SURFACE;
		eglDestroyContext(dpy, ctx);
		s_current_context = EGL_NO_CONTEXT;
		return EGL_FALSE;
	}

	s_current_context = ctx;
	s_current_surface = draw;

	if (s_lcd_surface == EGL_NO_SURFACE) {
		s_lcd_surface = draw;
	}

	return EGL_TRUE;
}


EGLBoolean eglBindAPI(EGLenum api)
{
	return EGL_TRUE;
}


EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint *attrib_list)
{
	int				width, height;
	int				bufsize;
	int				pixelformat = 32;
	EGLsurface		*internal_surface;
	int				i;
	EGLenum			render_buffer = EGL_BACK_BUFFER;
	LPRECT rc = NULL;

	/* attribute解析 */
	if (attrib_list != NULL) {
		for (i = 0;  attrib_list[i] != EGL_NONE; i += 2) {
			switch (attrib_list[i]) {
				case EGL_VG_COLORSPACE:
				case EGL_VG_ALPHA_FORMAT:

				case EGL_WIDTH:
					width = attrib_list[i + 1];
					break;

				case EGL_HEIGHT:
					height = attrib_list[i + 1];
					break;

				case EGL_RENDER_BUFFER:
					render_buffer = attrib_list[i + 1];
					break;
				default:
					break;
			}
		}
	}

	/* サーフェイス作成 */
	internal_surface = (EGLsurface*)malloc(sizeof(EGLsurface));
	memset (internal_surface, 0, sizeof(EGLsurface));
	/* 値設定 */
	bufsize = width * height * (pixelformat >> 3);

	internal_surface->type = WINDOW_SURFACE;
	internal_surface->config = (EGLconfig*)malloc(sizeof(EGLconfig));
	internal_surface->config->buffer_size = pixelformat;		//ピクセルフォーマット32bit
	internal_surface->color_buffer0 = malloc(bufsize);
	if (render_buffer == EGL_BACK_BUFFER) {
		internal_surface->back_buffer = 1;
		internal_surface->color_buffer1 = malloc(bufsize);
	} else {
		internal_surface->back_buffer = 0;
		internal_surface->color_buffer1 = NULL;
	}
	internal_surface->surface_width = width;
	internal_surface->surface_height = height;

	internal_surface->vgPbufferSurface = EGL_NO_SURFACE;
	internal_surface->vgImage_Pbuffer = VG_INVALID_HANDLE;

	//ShivaVGからの改造：amanithVG側のサーフェイスバッファを生成し、ポインタを保持
	internal_surface->vgWindowSurface = amanith_vg_privsurfacecreateAM(width, height, VG_FALSE, VG_FALSE, VG_TRUE);

	if (NULL == internal_surface->vgWindowSurface) {
		eglDestroySurface(dpy, internal_surface);
		return NULL;
	}

	return (EGLSurface)internal_surface;
}


EGLBoolean eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	return EGL_TRUE;
}


EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id)
{
	return (EGLDisplay)display_id;
}


EGLBoolean eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	*num_config = 1;

	return EGL_TRUE;
}


EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
	EGLcontext *ctx;

	ctx = (EGLcontext*)malloc(sizeof(EGLcontext));
	ctx->vgContext = amanith_vg_privcontextcreateAM(share_context);
	if (NULL == ctx->vgContext) {
		free(ctx);
		ctx = NULL;
        return EGL_NO_CONTEXT;
	}

	if (EGL_NO_CONTEXT == s_lcd_context) {
		s_lcd_context = (EGLContext)ctx;
	}

	return (EGLContext)ctx;
}




EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext context)
{
	EGLcontext *internal_context = (EGLcontext*)context;
	BOOL	IsCurrentContext = (context == s_current_context);

	if (NULL != internal_context) {
		amanith_vg_privcontextdestroyAM(internal_context->vgContext);
	}
	free(internal_context);
	if (IsCurrentContext) {
		s_current_context = EGL_NO_CONTEXT;
	}

	return EGL_TRUE;
}


EGLSurface eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	EGLsurface		*surface;
    VGImage			vgImage_Pbuffer;
	int				width = 0, height = 0;
 	int				pixelformat = 32;
	int				bufsize;
	int				i;
	int				color_buffer = 0;

	/* attribute解析 */
	if (attrib_list != NULL) {
		for (i = 0;  attrib_list[i] != EGL_NONE; i += 2) {
			switch (attrib_list[i]) {
				case EGL_WIDTH:
					width = attrib_list[i + 1];
					break;
				case EGL_HEIGHT:
					height = attrib_list[i + 1];
					break;
				case EGL_COLOR_BUFFER0_ADDRESS_EXT:
					color_buffer = attrib_list[i + 1];
					break;
				default:
					break;
			}
		}
	}

	if (width == 0 || height == 0) {
		return EGL_NO_SURFACE;
	}


	/* サーフェイス作成 */
	surface = (EGLsurface*)malloc(sizeof(EGLsurface));
	memset (surface, 0, sizeof(EGLsurface));
	/* 値設定 */
	bufsize = width * height * (pixelformat >> 3);
	surface->type = PBUFFER;
	surface->config = (EGLconfig*)malloc(sizeof(EGLconfig));
	surface->config->buffer_size = pixelformat;
	surface->hWnd = NULL;
	surface->hdc = NULL;
	surface->color_buffer0 = (void*)color_buffer;
	surface->color_buffer1 = NULL;
	surface->back_buffer = 0;

	surface->surface_width = width;
	surface->surface_height = height;

	if ((EGL_NO_CONTEXT == s_current_context) && (EGL_NO_SURFACE == s_current_surface)) {
		//makecurrentされていない状態で呼ばれるとvgImageが生成できないので、仮で作っておく
		if (VG_FALSE == amanith_vg_privmakecurrentAM(NULL, NULL)) {
			return EGL_NO_SURFACE;
		}

		surface->vgWindowSurface = amanith_vg_privsurfacecreateAM(width, height, VG_FALSE, VG_FALSE, VG_TRUE);
		if (VG_FALSE == amanith_vg_privmakecurrentAM(((EGLcontext*)s_lcd_context)->vgContext, surface->vgWindowSurface)) {
			return EGL_NO_SURFACE;
		}

		vgImage_Pbuffer = vgCreateImage(VG_sRGBA_4444, width, height, VG_IMAGE_QUALITY_FASTER);

		if (VG_NO_ERROR != vgGetError()) {
			return EGL_NO_SURFACE;
		}

		if (VG_FALSE == amanith_vg_privmakecurrentAM(NULL, NULL)) {
			return EGL_NO_SURFACE;
		}
	} else {
		surface->vgWindowSurface = NULL;
		vgImage_Pbuffer = vgCreateImage(VG_sRGBA_4444, width, height, VG_IMAGE_QUALITY_FASTER);
	}

	surface->vgPbufferSurface = amanith_vg_privsurfacecreatefromimageAM(vgImage_Pbuffer, VG_TRUE);
	surface->vgImage_Pbuffer = vgImage_Pbuffer;

	return (EGLSurface)surface;
}


EGLBoolean eglTerminate(EGLDisplay dpy)
{
	eglDestroySurface(dpy, s_current_surface);
	s_current_surface = EGL_NO_SURFACE;
	eglDestroyContext(dpy, s_current_context);
	s_current_context = EGL_NO_CONTEXT;

	return EGL_TRUE;
}

VGImage eglCreateImageForPbuffer(VGImageFormat format, VGint width, VGint height, VGint size, const void* data, VGbitfield allowedQuality)
{
	EGLcontext *context = (EGLcontext*)s_current_context;
	EGLsurface	*surface = (EGLsurface*)s_current_surface;

	if (EGL_NO_CONTEXT == context) {
		return VG_INVALID_HANDLE;
	}

	if (EGL_NO_SURFACE == surface) {
		return VG_INVALID_HANDLE;
	}

	//カレントバッファがPBUFFER以外だった場合は反映しない
	if (WINDOW_SURFACE == surface->type) {
		return VG_INVALID_HANDLE;
	}
	return surface->vgImage_Pbuffer;
}

