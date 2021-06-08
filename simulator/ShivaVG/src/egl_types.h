#ifndef _EGL_TYPES_H_
#define _EGL_TYPES_H_
#include <windows.h>
#include "egl.h"

typedef struct {
	HGLRC	hglrc;
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
	void		*color_buffer0;
	void		*color_buffer1;
	int			surface_width;
	int			surface_height;
	unsigned int	fb;
	unsigned int	tex;
	unsigned int	tex_depth_stencil;
} EGLsurface;

/* �T�[�t�F�[�X�̕����擾 */
#define gmw_SurfaceGetWidth(surface)		(((EGLsurface *)(surface))->surface_width)
/* �T�[�t�F�[�X�̕������� */
#define gmw_SurfaceGetHeight(surface)		(((EGLsurface *)(surface))->surface_height)
/* �T�[�t�F�[�X�̈ꃉ�C���̃o�C�g�����擾 */
#define gmw_SurfaceGetStride(surface)		((((EGLsurface *)(surface))->surface_width * ((EGLsurface *)(surface))->config->buffer_size) >> 3)
/* �T�[�t�F�[�X�̈�s�N�Z���̃o�C�g�����擾 */
#define gmw_SurfaceGetPixelSize(surface)	((((EGLsurface *)(surface))->config->buffer_size) >> 3)
/* �T�[�t�F�[�X�̃o�b�N�o�b�t�@�ԍ����擾 */
#define gmw_SurfaceGetBackBuffer(surface)	(((EGLsurface *)(surface))->back_buffer)
/* �T�[�t�F�[�X�̃J���[�o�b�t�@�O���擾 */
#define gmw_SurfaceGetColorBuffer0(surface)	(((EGLsurface *)(surface))->color_buffer0)
/* �T�[�t�F�[�X�̃J���[�o�b�t�@�P���擾 */
#define gmw_SurfaceGetColorBuffer1(surface)	(((EGLsurface *)(surface))->color_buffer1)

#endif
