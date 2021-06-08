/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __NATIVE_CORE_H__
#define __NATIVE_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {

  DMPNative_FALSE   = 0,
  DMPNative_TRUE    = 1

} DMPNative_Boolean;


typedef enum {

    DMPNative_ErrNone               = 0,
    DMPNative_ErrMemFull,
//  DMPNative_ErrOutOfSequence,
//  DMPNative_ErrBadState,
    DMPNative_ErrInvalidParameter,
//  DMPNative_ErrDuplicateElement,
//  DMPNative_ErrIsBusy,
//  DMPNative_ErrNotFound,
//  DMPNative_ErrOperationCancelled,
    DMPNative_ErrTimedOut,
    DMPNative_ErrUnknown,
    DMPNative_ErrAlreadyExists

} DMPNative_Error;


typedef struct {
  short  x;     /* offset x     */
  short  y;     /* offset y     */
  short  w;     /* width        */
  short  h;     /* height       */
} DMPNative_Rectangle;


typedef enum {

	DMPNative_OrientationUnknown	= -1,
	DMPNative_LowerLeft,
	DMPNative_UpperLeft

} DMPNative_Orientation;


typedef enum {

  DMPNative_PixelFormatUnknown		= -1,
  DMPNative_PixelFormatRGBA8888, 
  DMPNative_PixelFormatABGR8888, 
  DMPNative_PixelFormatRGB565, 
  DMPNative_PixelFormatRGBA4444, 
  DMPNative_PixelFormatRGBA5551, 
  DMPNative_PixelFormatUYVY,
  DMPNative_PixelFormatYUV422_SP,
  DMPNative_PixelFormatYUV420_SP

} DMPNative_PixelFormat;


#define DMP_NONE								0

#define	DMP_NATIVE_FRAMEBUFFER_TYPE				0x8000
#define	DMP_NATIVE_SINGLE_BUFFER				0x8001
#define	DMP_NATIVE_DOUBLE_BUFFER				0x8002
#define	DMP_NATIVE_TRIPLE_BUFFER				0x8003
#define DMP_NATIVE_FRAMEBUFFER_COLOR_FORMAT		0x8010

#define DMP_NATIVE_SWAP_INTERVAL				0x8100

#define	DMP_NATIVE_WIDTH						0x8200
#define	DMP_NATIVE_HEIGHT						0x8201
#define	DMP_NATIVE_STRIDE						0x8202
#define	DMP_NATIVE_VWIDTH						0x8210
#define	DMP_NATIVE_VHEIGHT						0x8211
#define	DMP_NATIVE_PHYSICAL_ADDRESS				0x8220
#define	DMP_NATIVE_LOGICAL_ADDRESS				0x8221

#define	DMP_NATIVE_YPLANE_WIDTH					0x8300
#define	DMP_NATIVE_YPLANE_HEIGHT				0x8301
#define	DMP_NATIVE_YPLANE_STRIDE				0x8302
#define	DMP_NATIVE_YPLANE_VWIDTH				0x8310
#define	DMP_NATIVE_YPLANE_VHEIGHT				0x8311
#define	DMP_NATIVE_YPLANE_PHYSICAL_ADDRESS		0x8320
#define	DMP_NATIVE_YPLANE_LOGICAL_ADDRESS		0x8321

#define	DMP_NATIVE_UVPLANE_WIDTH				0x8400
#define	DMP_NATIVE_UVPLANE_HEIGHT				0x8401
#define	DMP_NATIVE_UVPLANE_STRIDE				0x8402
#define	DMP_NATIVE_UVPLANE_VWIDTH				0x8413
#define	DMP_NATIVE_UVPLANE_VHEIGHT				0x8414
#define	DMP_NATIVE_UVPLANE_PHYSICAL_ADDRESS		0x8420
#define	DMP_NATIVE_UVPLANE_LOGICAL_ADDRESS		0x8421

#ifndef	DMP_NATIVE_FRAMEBUFFER_ADDRESS_SIZE
#	define	DMP_NATIVE_FRAMEBUFFER_ADDRESS_SIZE		0xE200
#endif	/* DMP_NATIVE_FRAMEBUFFER_ADDRESS_SIZE */


extern DMPNative_Error dmpNativeInitialize(void);
extern DMPNative_Error dmpNativeUninitialize(void);


#ifdef __cplusplus
}
#endif

#endif /* __NATIVE_CORE_H__ */
