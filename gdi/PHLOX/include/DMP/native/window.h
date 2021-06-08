/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __NATIVE_WINDOW_H__
#define __NATIVE_WINDOW_H__

#include <DMP/native/core.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef void * DMPNative_Window;

extern DMPNative_Boolean dmpNativeIsWindow(DMPNative_Window window);

extern DMPNative_Error dmpNativeWindowAddReference( 
    DMPNative_Window        window  
);

extern DMPNative_Error dmpNativeWindowRelease( 
    DMPNative_Window        window  
);

extern DMPNative_Error dmpNativeWindowCreate(
	const char						*fb,
	const int						*attrib_list,
    DMPNative_Window                *windowOut
);

extern DMPNative_Error dmpNativeWindowCreateSpecial( 
	const char						*fb,
	short                            width,
	short                            height,
	DMPNative_PixelFormat            format,
	short                            alignment,
	short                            rowPixelAlignment,
	const int						*attrib_list,
    DMPNative_Window                *windowOut
);

extern DMPNative_Error dmpNativeWindowGetRectangle(
    DMPNative_Window        window,
    DMPNative_Rectangle     *rect
);

extern DMPNative_Error dmpNativeWindowGetSubRectangle(
    DMPNative_Window        window,
    DMPNative_Rectangle     *subRect
);

extern DMPNative_Error dmpNativeWindowGetRowBytes(
    DMPNative_Window        window,
    short                   *rowBytes
);

extern DMPNative_Error dmpNativeWindowGetFormat(
    DMPNative_Window        window,
    DMPNative_PixelFormat   *format
);

extern DMPNative_Error dmpNativeWindowGetOrientation(
    DMPNative_Window        window,
    DMPNative_Orientation   *orientation
);

extern DMPNative_Error dmpNativeWindowQuery(
    DMPNative_Window        window,
	int						attribute,
	int						*value
);

extern DMPNative_Error dmpNativeWindowQueryPointer(
    DMPNative_Window        window,
	int						attribute,
	void					**value
);

extern DMPNative_Error dmpNativeWindowGetPhysicalAddress(
    DMPNative_Window        window,  
    void                    **phyAddr   
);

extern DMPNative_Error dmpNativeWindowLockBits(
    DMPNative_Window        window, 
    void                    **bitsOut
);

extern DMPNative_Error dmpNativeWindowUnlockBits( 
    DMPNative_Window        window
);

extern DMPNative_Error dmpNativeBeginSwapBuffers(
    DMPNative_Window        window,
	const int				*attrib_list,
	void					**ptr
);

extern DMPNative_Error dmpNativeEndSwapBuffers(
    DMPNative_Window        window,
	const int				*attrib_list
);


#ifdef __cplusplus
}
#endif

#endif /* __NATIVE_WINDOW_H__ */
