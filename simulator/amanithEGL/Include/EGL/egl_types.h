#ifndef _EGL_TYPES_H_
#define _EGL_TYPES_H_
#include <windows.h>
#include "egl.h"

typedef struct {
	void *vgContext;
} EGLcontext;

typedef struct EGLconfig
{
	EGLint	buffer_size;
}EGLconfig;

typedef enum {
	WINDOW_SURFACE,
	PBUFFER,
	PBUFFER_FROM_CLIENT_BUFFER,
	SUFACE_TYPE_END
} SURFACETYPE;

typedef struct EGLsurface
{
	SURFACETYPE	type;
    EGLconfig	*config;
	int			buffer_size;
	int			back_buffer;
	HWND		hWnd;
	HDC			hdc;
	void		*vgWindowSurface;
	void		*vgPbufferSurface;
    VGImage		vgImage_Pbuffer;
	void		*color_buffer0;
	void		*color_buffer1;
	int			surface_width;
	int			surface_height;
} EGLsurface;

/* サーフェースの幅を取得 */
#define gmw_SurfaceGetWidth(surface)		(((EGLsurface *)(surface))->surface_width)
/* サーフェースの幅を高さ */
#define gmw_SurfaceGetHeight(surface)		(((EGLsurface *)(surface))->surface_height)
/* サーフェースの一ラインのバイト数を取得 */
#define gmw_SurfaceGetStride(surface)		((((EGLsurface *)(surface))->surface_width * ((EGLsurface *)(surface))->config->buffer_size) >> 3)
/* サーフェースの一ピクセルのバイト数を取得 */
#define gmw_SurfaceGetPixelSize(surface)	((((EGLsurface *)(surface))->config->buffer_size) >> 3)
/* サーフェースのバックバッファ番号を取得 */
#define gmw_SurfaceGetBackBuffer(surface)	(((EGLsurface *)(surface))->back_buffer)
/* サーフェースのカラーバッファ０を取得 */
#define gmw_SurfaceGetColorBuffer0(surface)	(((EGLsurface *)(surface))->color_buffer0)
/* サーフェースのカラーバッファ１を取得 */
#define gmw_SurfaceGetColorBuffer1(surface)	(((EGLsurface *)(surface))->color_buffer1)

#endif
