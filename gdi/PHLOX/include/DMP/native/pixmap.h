/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __NATIVE_PIXMAP_H__
#define __NATIVE_PIXMAP_H__

#include <DMP/native/core.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef void * DMPNative_Pixmap;

extern DMPNative_Boolean dmpNativeIsPixmap(DMPNative_Pixmap pixmap);

extern DMPNative_Error dmpNativePixmapAddReference( 
    DMPNative_Pixmap        pixmap  
);

extern DMPNative_Error dmpNativePixmapRelease( 
    DMPNative_Pixmap        pixmap  
);

extern DMPNative_Error dmpNativePixmapCreate( 
    short                           width, 
    short                           height,  
    DMPNative_PixelFormat           format,
    short                           alignment,          // address alignment
    short                           rowPixelAlignment,  // x16
    DMPNative_Pixmap                *pixmapOut  
);

extern DMPNative_Error dmpNativePixmapGetRectangle(
    DMPNative_Pixmap        pixmap,
    DMPNative_Rectangle     *rect
);

extern DMPNative_Error dmpNativePixmapGetSubRectangle(
    DMPNative_Pixmap        pixmap,
    DMPNative_Rectangle     *subRect
);

extern DMPNative_Error dmpNativePixmapGetRowBytes(
    DMPNative_Pixmap        pixmap,
    short					*rowBytes
);

extern DMPNative_Error dmpNativePixmapGetFormat(
    DMPNative_Pixmap        pixmap,
    DMPNative_PixelFormat   *format
);

extern DMPNative_Error dmpNativePixmapGetOrientation(
    DMPNative_Pixmap        pixmap,
    DMPNative_Orientation   *orientation
);

extern DMPNative_Error dmpNativePixmapQuery(
    DMPNative_Pixmap        pixmap,
	int						attribute,
	int						*value
);

extern DMPNative_Error dmpNativePixmapQueryPointer(
    DMPNative_Pixmap        pixmap,
	int						attribute,
	void					**value
);

extern DMPNative_Error dmpNativePixmapGetPhysicalAddress(
    DMPNative_Pixmap        pixmap,  
    void                    **phyAddr   
);

extern DMPNative_Error dmpNativePixmapLockBits(
    DMPNative_Pixmap        pixmap, 
    void                    **bitsOut
);

extern DMPNative_Error dmpNativePixmapUnlockBits( 
    DMPNative_Pixmap        pixmap
);


#ifdef __cplusplus
}
#endif

#endif /* __NATIVE_PIXMAP_H__ */
