/*************************************************************************/
/**
 * @file      egl.c
 * @brief     EGLスタブ
 * @date
 * @copyright Panasonic Co.,Ltd.
 * @author
 *************************************************************************/
/***************************************************************
				インクルードファイル
***************************************************************/
#define VG_API_EXPORT
#include <windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include "egl.h"
#include "openvg.h"
#include "egl_types.h"
#include "vxlib.h"

#define SUPPORT_PBUFFER	0

#if SUPPORT_PBUFFER
 //ShivaVGのオブジェクトを参照するため
 #include "shImage.h"
#endif

/***************************************************************
				変数宣言
***************************************************************/

static int s_CreateVGContext = 0;
static EGLContext s_current_ctx = EGL_NO_CONTEXT;
static EGLSurface s_current_surface = EGL_NO_SURFACE;

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef GL_EXT_framebuffer_object
#define GL_INVALID_FRAMEBUFFER_OPERATION_EXT 0x0506
#define GL_MAX_RENDERBUFFER_SIZE_EXT      0x84E8
#define GL_FRAMEBUFFER_BINDING_EXT        0x8CA6
#define GL_RENDERBUFFER_BINDING_EXT       0x8CA7
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE_EXT       0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT    0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS_EXT      0x8CDF
#define GL_COLOR_ATTACHMENT0_EXT          0x8CE0
#define GL_COLOR_ATTACHMENT1_EXT          0x8CE1
#define GL_COLOR_ATTACHMENT2_EXT          0x8CE2
#define GL_COLOR_ATTACHMENT3_EXT          0x8CE3
#define GL_COLOR_ATTACHMENT4_EXT          0x8CE4
#define GL_COLOR_ATTACHMENT5_EXT          0x8CE5
#define GL_COLOR_ATTACHMENT6_EXT          0x8CE6
#define GL_COLOR_ATTACHMENT7_EXT          0x8CE7
#define GL_COLOR_ATTACHMENT8_EXT          0x8CE8
#define GL_COLOR_ATTACHMENT9_EXT          0x8CE9
#define GL_COLOR_ATTACHMENT10_EXT         0x8CEA
#define GL_COLOR_ATTACHMENT11_EXT         0x8CEB
#define GL_COLOR_ATTACHMENT12_EXT         0x8CEC
#define GL_COLOR_ATTACHMENT13_EXT         0x8CED
#define GL_COLOR_ATTACHMENT14_EXT         0x8CEE
#define GL_COLOR_ATTACHMENT15_EXT         0x8CEF
#define GL_DEPTH_ATTACHMENT_EXT           0x8D00
#define GL_STENCIL_ATTACHMENT_EXT         0x8D20
#define GL_FRAMEBUFFER_EXT                0x8D40
#define GL_RENDERBUFFER_EXT               0x8D41
#define GL_RENDERBUFFER_WIDTH_EXT         0x8D42
#define GL_RENDERBUFFER_HEIGHT_EXT        0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT 0x8D44
#define GL_STENCIL_INDEX1_EXT             0x8D46
#define GL_STENCIL_INDEX4_EXT             0x8D47
#define GL_STENCIL_INDEX8_EXT             0x8D48
#define GL_STENCIL_INDEX16_EXT            0x8D49
#define GL_RENDERBUFFER_RED_SIZE_EXT      0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_EXT    0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_EXT     0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_EXT    0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_EXT    0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_EXT  0x8D55
#endif

#ifndef GL_ARB_texture_rectangle
#define GL_TEXTURE_RECTANGLE_ARB          0x84F5
#define GL_TEXTURE_BINDING_RECTANGLE_ARB  0x84F6
#define GL_PROXY_TEXTURE_RECTANGLE_ARB    0x84F7
#define GL_MAX_RECTANGLE_TEXTURE_SIZE_ARB 0x84F8
#endif

#ifndef GL_EXT_packed_depth_stencil
#define GL_DEPTH_STENCIL_EXT              0x84F9
#define GL_UNSIGNED_INT_24_8_EXT          0x84FA
#define GL_DEPTH24_STENCIL8_EXT           0x88F0
#define GL_TEXTURE_STENCIL_SIZE_EXT       0x88F1
#endif

typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFEREXTPROC) (GLuint renderbuffer);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFEREXTPROC) (GLenum target, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSEXTPROC) (GLsizei n, const GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSEXTPROC) (GLsizei n, GLuint *renderbuffers);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEEXTPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC) (GLenum target, GLenum pname, GLint *params);
typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFEREXTPROC) (GLuint framebuffer);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFEREXTPROC) (GLenum target, GLuint framebuffer);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSEXTPROC) (GLsizei n, const GLuint *framebuffers);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSEXTPROC) (GLsizei n, GLuint *framebuffers);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC) (GLenum target);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) (GLenum target, GLenum attachment, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPEXTPROC) (GLenum target);

static PFNGLGENFRAMEBUFFERSEXTPROC			glGenFramebuffersEXT = NULL;
static PFNGLDELETEFRAMEBUFFERSEXTPROC		glDeleteFramebuffersEXT = NULL;
static PFNGLBINDFRAMEBUFFEREXTPROC			glBindFramebufferEXT = NULL;
static PFNGLFRAMEBUFFERTEXTURE2DEXTPROC		glFramebufferTexture2DEXT = NULL;
static PFNGLGENRENDERBUFFERSEXTPROC			glGenRenderbuffersEXT = NULL;
static PFNGLDELETERENDERBUFFERSEXTPROC		glDeleteRenderbuffersEXT = NULL;
static PFNGLBINDRENDERBUFFEREXTPROC			glBindRenderbufferEXT = NULL;
static PFNGLRENDERBUFFERSTORAGEEXTPROC		glRenderbufferStorageEXT = NULL;
static PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC	glFramebufferRenderbufferEXT = NULL;
static PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC	glCheckFramebufferStatusEXT = NULL;

/***************************************************************
				関数宣言
***************************************************************/

static HDC GetRenderDC(HWND hWnd, int width, int height);
static void CheckFBOStatus(void);
static void GetFBOProcAddr(void);
static void DrawFinish(EGLSurface surface);
static DWORD dwLastError = 0;
static BOOL s_bIsCreateContextSH = FALSE;

/***************************************************************
				関数
***************************************************************/
VG_API_CALL EGLint eglGetError(void)
{
	VGErrorCode err;
	if (!s_bIsCreateContextSH) {
		return EGL_SUCCESS;
	}
	err = vgGetError();
	return (VG_NO_ERROR == err) ? EGL_SUCCESS : EGL_BAD_ACCESS;
}

VG_API_CALL EGLBoolean eglReleaseThread(void)
{
	//ダミー
	return EGL_TRUE;
}

VG_API_CALL EGLBoolean eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
#if 0	//本当はこんな感じらしい
	SurfaceRef _s(surface);
    if (!_s.get()) {
		return setError(EGL_BAD_SURFACE, EGL_FALSE);
	}

    if (!validate_display_surface(dpy, surface)) {
        return EGL_FALSE;
    }

    egl_display_t const * const dp = get_display(dpy);
    egl_surface_t const * const s = get_surface(surface);

    if (s->cnx->egl.eglSurfaceAttrib) {
        return s->cnx->egl.eglSurfaceAttrib(dp->disp[s->impl].dpy, s->surface, attribute, value);
    }
    return setError(EGL_BAD_SURFACE, EGL_FALSE);
#else
	//ダミー
	return EGL_TRUE;
#endif
}


EGLSurface eglGetCurrentSurface(EGLint readdraw)
{
 #if 0	//本当はこんな感じらしい
   // could be called before eglInitialize(), but we wouldn't have a context
    // then, and this function would correctly return EGL_NO_SURFACE.

    EGLContext ctx = getContext();
    if (ctx) {
        egl_context_t const * const c = get_context(ctx);
        if (!c) return setError(EGL_BAD_CONTEXT, EGL_NO_SURFACE);
        switch (readdraw) {
            case EGL_READ: return c->read;
            case EGL_DRAW: return c->draw;            
            default: return setError(EGL_BAD_PARAMETER, EGL_NO_SURFACE);
        }
    }
    return EGL_NO_SURFACE;
#else
	//本当は描画面と読み出し面で２つあるはずだが、eglMakeCurrentするときにread側が使われている無いので、draw側を常に返してみる
	return s_current_surface;
#endif
}

VG_API_CALL EGLBoolean eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
	return EGL_TRUE;
}

VG_API_CALL EGLBoolean eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	*num_config = 1;
	
	return EGL_TRUE;
}

VG_API_CALL EGLBoolean eglBindAPI(EGLenum api)
{
	return EGL_TRUE;
}

VG_API_CALL EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id)
{
	return (EGLDisplay)display_id;
}

VG_API_CALL EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
	EGLcontext *ctx;
	
	ctx = (EGLcontext*)malloc(sizeof(EGLcontext));
	ctx->hglrc = NULL;	//ウインドウが必要なので最初のeglMakeCurrent時に作る
	
	return (EGLContext)ctx;
}

VG_API_CALL EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	EGLcontext *internal_ctx;

	internal_ctx = (EGLcontext*)ctx;
	
	/* GLコンテキスト削除 */
	if (internal_ctx->hglrc != NULL) {
		wglDeleteContext(internal_ctx->hglrc);
	}
	free(internal_ctx);

	internal_ctx = NULL;

	return EGL_TRUE;
}

VG_API_CALL EGLBoolean eglTerminate(EGLDisplay dpy)
{
//	if (s_CreateVGContext) {
		/* ShivaVGコンテキスト削除 */
		vgDestroyContextSH();
		/* ShivaVGコンテキスト作成フラグクリア */
		s_CreateVGContext = 0;
//	}

	return EGL_TRUE;
}

VG_API_CALL EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	EGLcontext		*internal_ctx = (EGLcontext*)ctx;
	EGLsurface		*internal_surface = (EGLsurface*)draw;
	
	if (s_current_surface != EGL_NO_SURFACE) {
		DrawFinish(s_current_surface);
	}
	
	if (ctx == EGL_NO_CONTEXT || draw == EGL_NO_SURFACE) {
		s_current_ctx = EGL_NO_SURFACE;
		s_current_surface = EGL_NO_SURFACE;
		wglMakeCurrent(NULL, NULL);
		return EGL_TRUE;
	}
	
	/* HGLRCが未作成ならサーフェイスのHDCから作成 */
	if (internal_ctx->hglrc == NULL) {
		/* GLコンテキスト作成 */
		internal_ctx->hglrc = wglCreateContext(internal_surface->hdc);
		if (internal_ctx->hglrc == NULL) {
			dwLastError = GetLastError();
			return EGL_FALSE;
		}
	}
	
	if (internal_surface->fb) {
		/* FBOを設定 */
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, internal_surface->fb);
	} else {
		/* GLに設定 */
		if (!wglMakeCurrent(internal_surface->hdc, internal_ctx->hglrc)) {
			dwLastError = GetLastError();
			return EGL_FALSE;
		}

		/* FBO関連関数のアドレス未取得なら取得 */
		if (glGenFramebuffersEXT == NULL) {
			GetFBOProcAddr();
		}
		if (glBindFramebufferEXT != NULL) {
			/* FBOを解除 */
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		}
	}

	/* ShivaVGコンテキスト作成 */
	/* wglMakeCurrent後でなければ作成できない */
	if (s_CreateVGContext == 0) {
		vgCreateContextSH(internal_surface->surface_width, internal_surface->surface_height);
		s_bIsCreateContextSH = TRUE;
		s_CreateVGContext = 1;
	} else {
		/* 2回目以降はサイズのみ設定 */
		vgResizeSurfaceSH(internal_surface->surface_width, internal_surface->surface_height);
	}

	/* サーフェイス作成直後の描画がうまくいかないのでバッファクリア */
	glClear(GL_STENCIL_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

	s_current_ctx = ctx;
	s_current_surface = draw;

	return EGL_TRUE;
}


static unsigned char eglSwap_copy_Buffer[960*544*4];

VG_API_CALL EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	EGLsurface		*internal_surface = (EGLsurface*)surface;

	/* 描画完了待ち */
	DrawFinish(surface);
	
	SwapBuffers(internal_surface->hdc);
	internal_surface->back_buffer ^= 1;

	//フロントバッファ→バックバッファコピー
	{
		// フロントバッファ読み取り
		glReadBuffer( GL_FRONT );

		//読み込んだバッファをバックバッファに反映
		glReadPixels(0, 0, internal_surface->surface_width, internal_surface->surface_height, GL_RGBA, GL_UNSIGNED_BYTE, eglSwap_copy_Buffer);
		glDrawPixels(internal_surface->surface_width, internal_surface->surface_height, GL_RGBA,GL_UNSIGNED_BYTE,eglSwap_copy_Buffer);
	}

	return EGL_TRUE;
}

VG_API_CALL EGLContext eglGetCurrentContext(void)
{
	HGLRC	hglrc;

	hglrc = wglGetCurrentContext();

	return (EGLContext)hglrc;
}

VG_API_CALL EGLSurface eglCreateWindowSurface(EGLDisplay egldisplay, EGLConfig config,
				  EGLNativeWindowType win,
				  const EGLint *attrib_list)
{
	HDC				hdcWindow;
	HWND			hWnd = (HWND)win;
	int				width, height;
	int				bufsize;
	int				pixelformat = 32;
	EGLsurface		*surface;
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

#if 0
	/* ウインドウサイズ取得 */
	VXQueryWindow(egldisplay, win, VX_WIDTH, (VXuint *)&width);
	VXQueryWindow(egldisplay, win, VX_HEIGHT, (VXuint *)&height);
	/* ウインドウからHDC作成 */
	VXQueryWindow(egldisplay, win, VX_HWND, (VXuint *)&hWnd);
#endif

	hdcWindow = GetRenderDC(hWnd, width, height);

	/* サーフェイス作成 */
	surface = (EGLsurface*)malloc(sizeof(EGLsurface));
	memset (surface, 0, sizeof(EGLsurface));
	/* 値設定 */
	bufsize = width * height * (pixelformat >> 3);


	surface->type = WINDOW_SURFACE;
	surface->config = (EGLconfig*)malloc(sizeof(EGLconfig));
	surface->config->buffer_size = pixelformat;		//ピクセルフォーマット32bit
	surface->hWnd = hWnd;
	surface->hdc = hdcWindow;
	surface->color_buffer0 = malloc(bufsize);
	if (render_buffer == EGL_BACK_BUFFER) {
		surface->back_buffer = 1;
		surface->color_buffer1 = malloc(bufsize);
	} else {
		surface->back_buffer = 0;
		surface->color_buffer1 = NULL;
	}
	surface->surface_width = width;
	surface->surface_height = height;

	return (EGLSurface)surface;
}

VG_API_CALL EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	EGLsurface		*internal_surface = (EGLsurface*)surface;

	if (NULL == internal_surface) {
		return EGL_TRUE;
	}

	if (internal_surface->fb) {
		/* FBOの結合を解除する */
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		/* FBO削除 */
		glDeleteFramebuffersEXT(1, &internal_surface->fb);
		/* テクスチャ削除 */
		if (internal_surface->tex_depth_stencil) {
			glDeleteTextures(1, &internal_surface->tex_depth_stencil);
		}
		if (internal_surface->tex) {
			glDeleteTextures(1, &internal_surface->tex);
		}
		if (internal_surface->type == PBUFFER) {
			/* PBUFFERはカラーバッファも解放 */
			free(internal_surface->color_buffer0);
		}
	} else {
		ReleaseDC(internal_surface->hWnd, internal_surface->hdc);
		free(internal_surface->color_buffer0);
		free(internal_surface->color_buffer1);
	}
	free(internal_surface->config);
	free(internal_surface);
	internal_surface = NULL;

	return EGL_TRUE;
}

VG_API_CALL EGLSurface eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
	EGLsurface		*surface;
#if 0
	GLuint			tex, tex_depth_stencil, fb;
	int				width, height;
 	int				pixelformat = 32;
 	SHImage			*image;

	if (glGenFramebuffersEXT == NULL) {
		return EGL_NO_SURFACE;
	}
	
	if (buftype != EGL_OPENVG_IMAGE) {
		return EGL_NO_SURFACE;
	}
	
	image = (SHImage*)buffer;
	tex = image->texture;

	/* テクスチャ情報取得 */
	glBindTexture(GL_TEXTURE_2D, tex);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	/* テクスチャ設定(これを設定しないとなぜかUnsupportedになる) */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	/* デプス・ステンシル用テクスチャ作成・設定 */
	glGenTextures(1, &tex_depth_stencil);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_DEPTH24_STENCIL8_EXT, width, height, 0, GL_DEPTH_STENCIL_EXT, GL_UNSIGNED_INT_24_8_EXT, 0);
	/* フレームバッファ作成・設定 */
	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tex, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil, 0);
	/* チェック */
	CheckFBOStatus();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
	/* サーフェイス作成 */
	surface = (EGLsurface*)malloc(sizeof(EGLsurface));
	memset (surface, 0, sizeof(EGLsurface));
	/* 値設定 */
	surface->type = PBUFFER_FROM_CLIENT_BUFFER;
	surface->config = (EGLconfig*)malloc(sizeof(EGLconfig));
	surface->config->buffer_size = pixelformat;
	surface->back_buffer = 0;
	surface->surface_width = width;
	surface->surface_height = height;
	surface->fb = fb;
	surface->tex_depth_stencil = tex_depth_stencil;
#endif
	return (EGLSurface)surface;
}

VG_API_CALL EGLSurface eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	EGLsurface		*surface;
	GLuint			tex, tex_depth_stencil, fb;
	int				width = 0, height = 0;
 	int				pixelformat = 32;
	int				bufsize;
	int				i;

	if (glGenFramebuffersEXT == NULL) {
		return EGL_NO_SURFACE;
	}
	
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
				default:
					return EGL_NO_SURFACE;
			}
		}
	}

	if (width == 0 || height == 0) {
		return EGL_NO_SURFACE;
	}

	/* カラーバッファ作成 */
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	
	/* デプス・ステンシル用テクスチャ作成・設定 */
	glGenTextures(1, &tex_depth_stencil);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_DEPTH24_STENCIL8_EXT, width, height, 0, GL_DEPTH_STENCIL_EXT, GL_UNSIGNED_INT_24_8_EXT, 0);
	/* フレームバッファ作成・設定 */
	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tex, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil, 0);
	/* チェック */
	CheckFBOStatus();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
	/* サーフェイス作成 */
	surface = (EGLsurface*)malloc(sizeof(EGLsurface));
	memset (surface, 0, sizeof(EGLsurface));
	/* 値設定 */
	bufsize = width * height * (pixelformat >> 3);
	surface->type = PBUFFER;
	surface->config = (EGLconfig*)malloc(sizeof(EGLconfig));
	surface->config->buffer_size = pixelformat;
	surface->back_buffer = 0;
	surface->surface_width = width;
	surface->surface_height = height;
	surface->color_buffer0 = malloc(bufsize);
	surface->fb = fb;
	surface->tex = tex;
	surface->tex_depth_stencil = tex_depth_stencil;

	return (EGLSurface)surface;
}

VG_API_CALL EGLSurface eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint *attrib_list)
{
	EGLsurface		*surface;
	GLuint			tex, tex_depth_stencil, fb;
	int				width = 0, height = 0;
 	int				pixelformat = 32;
	void			*buf_addr = NULL;

	if (glGenFramebuffersEXT == NULL) {
		return EGL_NO_SURFACE;
	}
	
	/* サイズ取得 */
	VXQueryWindow(dpy, pixmap, VX_WIDTH, (VXuint *)&width);
	VXQueryWindow(dpy, pixmap, VX_HEIGHT, (VXuint *)&height);
	/* バッファアドレス取得 */
	VXQueryWindow(dpy, pixmap, VX_ADDR, (VXuint *)&buf_addr);

	if (width == 0 || height == 0) {
		return EGL_NO_SURFACE;
	}

	/* カラーバッファ作成 */
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	
	/* デプス・ステンシル用テクスチャ作成・設定 */
	glGenTextures(1, &tex_depth_stencil);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_DEPTH24_STENCIL8_EXT, width, height, 0, GL_DEPTH_STENCIL_EXT, GL_UNSIGNED_INT_24_8_EXT, 0);
	/* フレームバッファ作成・設定 */
	glGenFramebuffersEXT(1, &fb);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tex, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_TEXTURE_RECTANGLE_ARB, tex_depth_stencil, 0);
	/* チェック */
	CheckFBOStatus();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
	/* サーフェイス作成 */
	surface = (EGLsurface*)malloc(sizeof(EGLsurface));
	memset (surface, 0, sizeof(EGLsurface));
	/* 値設定 */
	surface->config = (EGLconfig*)malloc(sizeof(EGLconfig));
	surface->config->buffer_size = pixelformat;
	surface->back_buffer = 0;
	surface->surface_width = width;
	surface->surface_height = height;
	surface->color_buffer0 = buf_addr;
	surface->fb = fb;
	surface->tex = tex;
	surface->tex_depth_stencil = tex_depth_stencil;

	return (EGLSurface)surface;
}

static HDC GetRenderDC(HWND hWnd, int width, int height)
{
	HDC					hdc;
	int					pixel_format;
	//http://msdn.microsoft.com/ja-jp/library/dd368826.aspx
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof (PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_DOUBLEBUFFER |
		PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA,
		32,
		8, 0,
		8, 0,
		8, 0,
		8, 0,
		0,
		0, 0, 0, 0,
		32,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	/* デバイスコンテキスト作成 */
	hdc = GetDC(hWnd);
	/* パラメータ設定 */
	pixel_format = ChoosePixelFormat( hdc , &pfd );
	if(pixel_format == 0) {
		return NULL;
	}
	if(SetPixelFormat( hdc , pixel_format , &pfd ) == FALSE) {
		dwLastError = GetLastError();
		return NULL;
	}

	return hdc;
}

/* FBO関連APIのアドレスを取得する */
static void GetFBOProcAddr(void)
{
	glGenFramebuffersEXT = (PFNGLGENFRAMEBUFFERSEXTPROC)wglGetProcAddress("glGenFramebuffersEXT");
	glDeleteFramebuffersEXT = (PFNGLDELETEFRAMEBUFFERSEXTPROC)wglGetProcAddress("glDeleteFramebuffersEXT");
	glBindFramebufferEXT = (PFNGLBINDFRAMEBUFFEREXTPROC)wglGetProcAddress("glBindFramebufferEXT");
	glFramebufferTexture2DEXT = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)wglGetProcAddress("glFramebufferTexture2DEXT");
	glGenRenderbuffersEXT = (PFNGLGENRENDERBUFFERSEXTPROC)wglGetProcAddress("glGenRenderbuffersEXT");
	glDeleteRenderbuffersEXT = (PFNGLDELETERENDERBUFFERSEXTPROC)wglGetProcAddress("glDeleteRenderbuffersEXT");
	glBindRenderbufferEXT = (PFNGLBINDRENDERBUFFEREXTPROC)wglGetProcAddress("glBindRenderbufferEXT");
	glRenderbufferStorageEXT = (PFNGLRENDERBUFFERSTORAGEEXTPROC)wglGetProcAddress("glRenderbufferStorageEXT");
	glFramebufferRenderbufferEXT = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)wglGetProcAddress("glFramebufferRenderbufferEXT");
	glCheckFramebufferStatusEXT = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)wglGetProcAddress("glCheckFramebufferStatusEXT");
}

static void CheckFBOStatus(void)
{
#if 0
	GLenum status;
	TCHAR errmsg[256];
	
	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status) {
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		_sntprintf(errmsg, 256, _T("FBO OK %04x\n"), status);
		MessageBox(NULL, errmsg, _T(""), MB_OK);
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		MessageBox(NULL, _T("Unsupported\n"), _T(""), MB_OK);
		break;
	default:
		_sntprintf(errmsg, 256, _T("FBO error %04x\n"), status);
		MessageBox(NULL, errmsg, _T(""), MB_OK);
		break;
	}
#endif
}

/* 描画を完了させてメモリに取り込む */
static void DrawFinish(EGLSurface surface)
{
	EGLsurface		*internal_surface = (EGLsurface*)surface;
	unsigned char	*buf;
    unsigned char	*tmpbuf, *p;
	int				i;
	int				mem_width;
	

	/* 描画完了待ち */
	glFlush();
	/* 描画結果をメモリに取り込む */
	if (internal_surface->back_buffer == 0) {
		buf = internal_surface->color_buffer0;
	} else {
		buf = internal_surface->color_buffer1;
	}
	if (buf == NULL) {
		return;
	}
	tmpbuf = malloc(internal_surface->surface_width * internal_surface->surface_height * 4);
	glReadBuffer(GL_BACK);
	glLoadIdentity(); 
	glReadPixels(
				0, 0,
				internal_surface->surface_width, internal_surface->surface_height,
				GL_RGBA,
				//GL_BGRA,
				GL_UNSIGNED_BYTE,
				tmpbuf);
	/* 上下さかさまなので反転してカラーバッファにコピー */
	mem_width = internal_surface->surface_width * 4;
	p = tmpbuf;
	p += (internal_surface->surface_height - 1) * mem_width;	//最終行の先頭に移動
	for (i = 0; i < internal_surface->surface_height; i++) {
		memcpy(buf, p, mem_width);
		buf += mem_width;
		p -= mem_width;
	}
	free(tmpbuf);
}

//GUIシミュレータ用に追加。glut系の初期化処理を行う
VG_API_CALL void InitLibOpenVG(int width, int height)
{
	int argc = 1;
	char title[] = "Open VG Library";
	char path[MAX_PATH+1];
	char *argv[1];
	argv[0] = path;

	GetModuleFileName(NULL, path, MAX_PATH);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA |
					  GLUT_STENCIL | GLUT_MULTISAMPLE);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(width, height);
	glutCreateWindow(title);

	vgCreateContextSH(width, height);
}
