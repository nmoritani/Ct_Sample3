/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __EGL_NATIVE_H__
#define __EGL_NATIVE_H__

#include <EGL/egl.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef EGLNATIVE_API
#ifdef EGLNATIVE_STATIC_LIBRARY
#	define EGLNATIVE_API
#else /* EGLNATIVE_STATIC_LIBRARY */
#	if defined(_WIN32) || defined(__VC32__)
#		ifdef EGLNATIVE_DLL_EXPORTS
#			define EGLNATIVE_API __declspec(dllexport)
#		else /* EGLNATIVE_DLL_EXPORTS */
#			define EGLNATIVE_API __declspec(dllimport)
#		endif /* EGLNATIVE_DLL_EXPORTS */
#	else
#		define EGLNATIVE_API
#	endif
#endif /* EGLNATIVE_STATIC_LIBRARY */
#endif /* EGLNATIVE_API */

#ifndef EGLNATIVE_APIENTRY
#	if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
#		define EGLNATIVE_APIENTRY	__stdcall
#	else
#		define EGLNATIVE_APIENTRY
#	endif
#endif /* EGLNATIVE_APIENTRY */


#if defined(__ANDROID__) || defined(ANDROID)

#	ifdef BUILD_JELLY_BEAN	/* 4.1 */

#include <system/window.h>
#include <hardware/gralloc.h>
#include <android/native_window.h>

typedef ANativeWindowBuffer_t*	EGLNativeBufferTypeDMP;

#	else /* BUILD_GINGERBREAD_MR1 2.3.3 */

#include <ui/android_native_buffer.h>

typedef android_native_buffer_t*	EGLNativeBufferTypeDMP;

#	endif

#else /* __ANDROID__ || ANDROID */

typedef void*	EGLNativeBufferTypeDMP;

#endif /* __ANDROID__ || ANDROID */


#define	EGL_NATIVE_FRAMEBUFFER_TYPE			0x8000
#define	EGL_NATIVE_SINGLE_BUFFER			0x8001
#define	EGL_NATIVE_DOUBLE_BUFFER			0x8002
#define	EGL_NATIVE_TRIPLE_BUFFER			0x8003
#define	EGL_NATIVE_FRAMEBUFFER_COLOR_FORMAT	0x8010

#define	EGL_NATIVE_SWAP_INTERVAL			0x8100

#define	EGL_NATIVE_VISIBLE_WIDTH			0x8200
#define	EGL_NATIVE_VISIBLE_HEIGHT			0x8201
#define	EGL_NATIVE_VIRTUAL_WIDTH			0x8210
#define	EGL_NATIVE_VIRTUAL_HEIGHT			0x8211
#define	EGL_NATIVE_PHYSICAL_ADDRESS			0x8220
#define	EGL_NATIVE_LOGICAL_ADDRESS			0x8221

#define	EGL_NATIVE_YPLANE_VISIBLE_WIDTH		0x8300
#define	EGL_NATIVE_YPLANE_VISIBLE_HEIGHT	0x8301
#define	EGL_NATIVE_YPLANE_VIRTUAL_WIDTH		0x8310
#define	EGL_NATIVE_YPLANE_VIRTUAL_HEIGHT	0x8311
#define	EGL_NATIVE_YPLANE_PHYSICAL_ADDRESS	0x8320
#define	EGL_NATIVE_YPLANE_LOGICAL_ADDRESS	0x8321

#define	EGL_NATIVE_UVPLANE_VISIBLE_WIDTH	0x8400
#define	EGL_NATIVE_UVPLANE_VISIBLE_HEIGHT	0x8401
#define	EGL_NATIVE_UVPLANE_VIRTUAL_WIDTH	0x8410
#define	EGL_NATIVE_UVPLANE_VIRTUAL_HEIGHT	0x8411
#define	EGL_NATIVE_UVPLANE_PHYSICAL_ADDRESS	0x8420
#define	EGL_NATIVE_UVPLANE_LOGICAL_ADDRESS	0x8421

#ifndef EGL_NATIVE_FRAMEBUFFER_ADDRESS_SIZE
#	define	EGL_NATIVE_FRAMEBUFFER_ADDRESS_SIZE		0xE200
#endif /* EGL_NATIVE_FRAMEBUFFER_ADDRESS_SIZE */

#define	EGL_NATIVE_WINDOW_STYLE				0x8500
#define	EGL_NATIVE_DEFAULT_WINDOW			0x8501
#define	EGL_NATIVE_POPUP_WINDOW				0x8502


typedef enum {

	EGL_NATIVE_UNKNOWN_COLOR_FORMAT = -1,

    /* RGB{A,X} channel ordering */
	EGL_NATIVE_RGBX_8888,
	EGL_NATIVE_RGBA_8888,
	EGL_NATIVE_RGB_565,
	EGL_NATIVE_RGBX_5551,
	EGL_NATIVE_RGBA_5551,
	EGL_NATIVE_RGBX_4444,
	EGL_NATIVE_RGBA_4444,

    /* {A,X}RGB channel ordering */
	EGL_NATIVE_XRGB_8888,
	EGL_NATIVE_ARGB_8888,
	EGL_NATIVE_XRGB_1555,
	EGL_NATIVE_ARGB_1555,
	EGL_NATIVE_XRGB_4444,
	EGL_NATIVE_ARGB_4444,

    /* BGR{A,X} channel ordering */
	EGL_NATIVE_BGRX_8888,
	EGL_NATIVE_BGRA_8888,
	EGL_NATIVE_BGR_565,
	EGL_NATIVE_BGRX_5551,
	EGL_NATIVE_BGRA_5551,
	EGL_NATIVE_BGRX_4444,
	EGL_NATIVE_BGRA_4444,

    /* {A,X}BGR channel ordering */
	EGL_NATIVE_XBGR_8888,
	EGL_NATIVE_ABGR_8888,
	EGL_NATIVE_XBGR_1555,
	EGL_NATIVE_ABGR_1555,
	EGL_NATIVE_XBGR_4444,
	EGL_NATIVE_ABGR_4444,

    /* U, Y, V, Y ordering */
	EGL_NATIVE_UYVY,

    /* Y, U, Y, V ordering */
	EGL_NATIVE_YUYV,			/* reserved */

	EGL_NATIVE_YUV422_SP,
	EGL_NATIVE_YUV420_SP,

	EGL_NUM_NATIVE_COLOR_FORMAT

} EGL_NATIVE_COLOR_FORMAT;


typedef enum {

	EGL_NATIVE_UNKNOWN_ORIENTATION = -1,

	EGL_NATIVE_LOWER_LEFT,
	EGL_NATIVE_UPPER_LEFT,

	EGL_NUM_NATIVE_ORIENTATION

} EGL_NATIVE_ORIENTATION;



/*
 * EGL Native
 */

extern EGLNATIVE_API void EGLNATIVE_APIENTRY eglNativeInitialize(void);
extern EGLNATIVE_API void EGLNATIVE_APIENTRY eglNativeUninitialize(void);

extern EGLNATIVE_API EGLNativeDisplayType EGLNATIVE_APIENTRY eglNativeGetDefaultDisplay(void);
extern EGLNATIVE_API void EGLNATIVE_APIENTRY eglNativeWaitNative(void);

/*
 * Window
 */

extern EGLNATIVE_API EGLNativeWindowType EGLNATIVE_APIENTRY eglNativeCreateFullScreenWindow(EGLNativeDisplayType display, EGLint *attrib_list);
extern EGLNATIVE_API EGLNativeWindowType EGLNATIVE_APIENTRY eglNativeCreateWindow(EGLNativeDisplayType display, int width, int height, const EGL_NATIVE_COLOR_FORMAT colorFormat, EGLint *attrib_list);
extern EGLNATIVE_API void EGLNATIVE_APIENTRY eglNativeDestroyWindow(EGLNativeDisplayType display, EGLNativeWindowType window);

extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeIsWindow(EGLNativeDisplayType display, EGLNativeWindowType window);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetWindowSize(EGLNativeDisplayType display, EGLNativeWindowType window, int *width, int *height, int *stride);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetWindowColorFormat(EGLNativeDisplayType display, EGLNativeWindowType window, EGL_NATIVE_COLOR_FORMAT *colorFormat);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetWindowOrientation(EGLNativeDisplayType display, EGLNativeWindowType window, EGL_NATIVE_ORIENTATION *orientation);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeQueryWindow(EGLNativeDisplayType display, EGLNativeWindowType window, EGLint attribute, EGLint *value);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeQueryWindowPointer(EGLNativeDisplayType display, EGLNativeWindowType window, EGLint attribute, void **value);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeMapWindow(EGLNativeDisplayType display, EGLNativeWindowType window, void **ptr);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeUnmapWindow(EGLNativeDisplayType display, EGLNativeWindowType window);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetWindowPhysicalAddress(EGLNativeDisplayType display, EGLNativeWindowType window, void **ptr);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeIsMatchWindowColorFormat(EGLNativeDisplayType display, EGLNativeWindowType window, const EGL_NATIVE_COLOR_FORMAT colorFormat);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeBeginSwapBuffers(EGLNativeDisplayType display, EGLNativeWindowType window, EGLint *attrib_list, void **ptr);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeEndSwapBuffers(EGLNativeDisplayType display, EGLNativeWindowType window, EGLint *attrib_list);

/*
 * Pixmap
 */

extern EGLNATIVE_API EGLNativePixmapType EGLNATIVE_APIENTRY eglNativeCreatePixmap(EGLNativeDisplayType display, int width, int height, const EGL_NATIVE_COLOR_FORMAT colorFormat, EGLint *attrib_list);
extern EGLNATIVE_API void EGLNATIVE_APIENTRY eglNativeDestroyPixmap(EGLNativeDisplayType display, EGLNativePixmapType pixmap);

extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeIsPixmap(EGLNativeDisplayType display, EGLNativePixmapType pixmap);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetPixmapSize(EGLNativeDisplayType display, EGLNativePixmapType pixmap, int *width, int *height, int *stride);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetPixmapColorFormat(EGLNativeDisplayType display, EGLNativePixmapType pixmap, EGL_NATIVE_COLOR_FORMAT *colorFormat);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetPixmapOrientation(EGLNativeDisplayType display, EGLNativePixmapType pixmap, EGL_NATIVE_ORIENTATION *orientation);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeQueryPixmap(EGLNativeDisplayType display, EGLNativePixmapType pixmap, EGLint attribute, EGLint *value);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeQueryPixmapPointer(EGLNativeDisplayType display, EGLNativePixmapType pixmap, EGLint attribute, void **value);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeMapPixmap(EGLNativeDisplayType display, EGLNativePixmapType pixmap, void **ptr);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeUnmapPixmap(EGLNativeDisplayType display, EGLNativePixmapType pixmap);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetPixmapPhysicalAddress(EGLNativeDisplayType display, EGLNativePixmapType pixmap, void **ptr);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeIsMatchPixmapColorFormat(EGLNativeDisplayType display, EGLNativePixmapType pixmap, const EGL_NATIVE_COLOR_FORMAT colorFormat);

/*
 * Buffer
 */

extern EGLNATIVE_API EGLNativeBufferTypeDMP EGLNATIVE_APIENTRY eglNativeCreateBuffer(EGLNativeDisplayType display, int width, int height, const EGL_NATIVE_COLOR_FORMAT colorFormat, EGLint *attrib_list);
extern EGLNATIVE_API void EGLNATIVE_APIENTRY eglNativeDestroyBuffer(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeIsBuffer(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetBufferSize(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer, int *width, int *height, int *stride);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetBufferColorFormat(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer, EGL_NATIVE_COLOR_FORMAT *colorFormat);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetBufferOrientation(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer, EGL_NATIVE_ORIENTATION *orientation);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeQueryBuffer(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer, EGLint attribute, EGLint *value);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeMapBuffer(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer, void **ptr);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeUnmapBuffer(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer);
extern EGLNATIVE_API EGLBoolean EGLNATIVE_APIENTRY eglNativeGetBufferPhysicalAddress(EGLNativeDisplayType display, EGLNativeBufferTypeDMP buffer, void **ptr);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __EGL_NATIVE_H__ */
