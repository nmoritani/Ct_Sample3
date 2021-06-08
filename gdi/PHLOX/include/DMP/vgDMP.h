/*
  Copyright (c) 2010-2013, Digital Media Professionals. All rights reserved.
*/
#ifndef _VGDMP_H
#define _VGDMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <VG/openvg.h>
#include <VG/vgu.h>

#ifndef VG_API_ENTRYP
#	define VG_API_ENTRYP VG_API_ENTRY*
#endif

#ifndef VGU_API_ENTRYP
#	define VGU_API_ENTRYP VGU_API_ENTRY*
#endif

#ifndef VG_VGDMP_PROTOTYPES
#	define VG_VGDMP_PROTOTYPES
#endif

/* Header file version number */
#define VG_VGDMP_VERSION	1

/*******************************/

/*----------------
 * DMP extensions
 *----------------
*/

/*
###############################################################################

# DMP: 0xC000-0xCFFF

# DMP_future_use: 0xC110-0xC11F
#                 0xC1C0-0xC1FF
#                 0xC400-0xCFFF

###############################################################################
*/

#ifndef	_VG_OFFSET_ENUM_DMP
#	define _VG_OFFSET_ENUM_DMP		0xC000
#endif /* _VG_OFFSET_ENUM_DMP */


/*
###############################################################################

# #001 VG_DMP_LA_88

###############################################################################
*/
#ifndef VG_DMP_LA_88
#define VG_DMP_LA_88 1

#define VG_sLA_88_DMP		((VGImageFormat)15)
#define VG_sLA_88_PRE_DMP	((VGImageFormat)16)
#define VG_lLA_88_DMP		((VGImageFormat)17)
#define VG_lLA_88_PRE_DMP	((VGImageFormat)18)

#define VG_sAL_88_DMP		((VGImageFormat)(VG_sLA_88_DMP		| (1 << 6)))
#define VG_sAL_88_PRE_DMP	((VGImageFormat)(VG_sLA_88_PRE_DMP	| (1 << 6)))
#define VG_lAL_88_DMP		((VGImageFormat)(VG_lLA_88_DMP		| (1 << 6)))
#define VG_lAL_88_PRE_DMP	((VGImageFormat)(VG_lLA_88_PRE_DMP	| (1 << 6)))

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMP_LA_88 */

/*
###############################################################################

# #002 VG_DMP_ETC1

###############################################################################
*/
#ifndef VG_DMP_ETC1
#define VG_DMP_ETC1 1

#define VG_sETC1_DMP		((VGImageFormat)19)
#define VG_lETC1_DMP		((VGImageFormat)20)

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMP_ETC1 */

/*
###############################################################################

# #003 VG_DMP_image_native_format_direct_load, VG_DMP_image_native_format
#      0xC000-0xC00F

###############################################################################
*/
#ifndef VG_DMP_image_native_format
#define VG_DMP_image_native_format 1

#endif /* VG_DMP_image_native_format */


#ifndef VG_DMP_image_native_format_direct_load
#define VG_DMP_image_native_format_direct_load 1

/* 
 * UPPER_LEFT NATIVE format
 */

/* RGB{A,X} channel ordering */
#define VG_sRGBX_8888_NATIVE_DMP				((VGImageFormat)(VG_sRGBX_8888		| (1 << 10) | (1 << 11)))
#define VG_sRGBA_8888_NATIVE_DMP				((VGImageFormat)(VG_sRGBA_8888		| (1 << 10) | (1 << 11)))
#define VG_sRGBA_8888_PRE_NATIVE_DMP			((VGImageFormat)(VG_sRGBA_8888_PRE	| (1 << 10) | (1 << 11)))
#define VG_sRGB_565_NATIVE_DMP					((VGImageFormat)(VG_sRGB_565		| (1 << 10) | (1 << 11)))
#define VG_sRGBA_5551_NATIVE_DMP				((VGImageFormat)(VG_sRGBA_5551		| (1 << 10) | (1 << 11)))
#define VG_sRGBA_4444_NATIVE_DMP				((VGImageFormat)(VG_sRGBA_4444		| (1 << 10) | (1 << 11)))
#define VG_sL_8_NATIVE_DMP						((VGImageFormat)(VG_sL_8			| (1 << 10) | (1 << 11)))
#define VG_lRGBX_8888_NATIVE_DMP				((VGImageFormat)(VG_lRGBX_8888		| (1 << 10) | (1 << 11)))
#define VG_lRGBA_8888_NATIVE_DMP				((VGImageFormat)(VG_lRGBA_8888		| (1 << 10) | (1 << 11)))
#define VG_lRGBA_8888_PRE_NATIVE_DMP			((VGImageFormat)(VG_lRGBA_8888_PRE	| (1 << 10) | (1 << 11)))
#define VG_lL_8_NATIVE_DMP						((VGImageFormat)(VG_lL_8			| (1 << 10) | (1 << 11)))
#define VG_A_8_NATIVE_DMP						((VGImageFormat)(VG_A_8				| (1 << 10) | (1 << 11)))
#define VG_BW_1_NATIVE_DMP						((VGImageFormat)(VG_BW_1			| (1 << 10) | (1 << 11)))
#define VG_A_1_NATIVE_DMP						((VGImageFormat)(VG_A_1				| (1 << 10) | (1 << 11)))
#define VG_A_4_NATIVE_DMP						((VGImageFormat)(VG_A_4				| (1 << 10) | (1 << 11)))

/* {A,X}RGB channel ordering */
#define VG_sXRGB_8888_NATIVE_DMP				((VGImageFormat)(VG_sXRGB_8888		| (1 << 10) | (1 << 11)))
#define VG_sARGB_8888_NATIVE_DMP				((VGImageFormat)(VG_sARGB_8888		| (1 << 10) | (1 << 11)))
#define VG_sARGB_8888_PRE_NATIVE_DMP			((VGImageFormat)(VG_sARGB_8888_PRE	| (1 << 10) | (1 << 11)))
#define VG_sARGB_1555_NATIVE_DMP				((VGImageFormat)(VG_sARGB_1555		| (1 << 10) | (1 << 11)))
#define VG_sARGB_4444_NATIVE_DMP				((VGImageFormat)(VG_sARGB_4444		| (1 << 10) | (1 << 11)))
#define VG_lXRGB_8888_NATIVE_DMP				((VGImageFormat)(VG_lXRGB_8888		| (1 << 10) | (1 << 11)))
#define VG_lARGB_8888_NATIVE_DMP				((VGImageFormat)(VG_lARGB_8888		| (1 << 10) | (1 << 11)))
#define VG_lARGB_8888_PRE_NATIVE_DMP			((VGImageFormat)(VG_lARGB_8888_PRE	| (1 << 10) | (1 << 11)))

/* BGR{A,X} channel ordering */
#define VG_sBGRX_8888_NATIVE_DMP				((VGImageFormat)(VG_sBGRX_8888		| (1 << 10) | (1 << 11)))
#define VG_sBGRA_8888_NATIVE_DMP				((VGImageFormat)(VG_sBGRA_8888		| (1 << 10) | (1 << 11)))
#define VG_sBGRA_8888_PRE_NATIVE_DMP			((VGImageFormat)(VG_sBGRA_8888_PRE	| (1 << 10) | (1 << 11)))
#define VG_sBGR_565_NATIVE_DMP					((VGImageFormat)(VG_sBGR_565		| (1 << 10) | (1 << 11)))
#define VG_sBGRA_5551_NATIVE_DMP				((VGImageFormat)(VG_sBGRA_5551		| (1 << 10) | (1 << 11)))
#define VG_sBGRA_4444_NATIVE_DMP				((VGImageFormat)(VG_sBGRA_4444		| (1 << 10) | (1 << 11)))
#define VG_lBGRX_8888_NATIVE_DMP				((VGImageFormat)(VG_lBGRX_8888		| (1 << 10) | (1 << 11)))
#define VG_lBGRA_8888_NATIVE_DMP				((VGImageFormat)(VG_lBGRA_8888		| (1 << 10) | (1 << 11)))
#define VG_lBGRA_8888_PRE_NATIVE_DMP			((VGImageFormat)(VG_lBGRA_8888_PRE	| (1 << 10) | (1 << 11)))

/* {A,X}BGR channel ordering */
#define VG_sXBGR_8888_NATIVE_DMP				((VGImageFormat)(VG_sXBGR_8888		| (1 << 10) | (1 << 11)))
#define VG_sABGR_8888_NATIVE_DMP				((VGImageFormat)(VG_sABGR_8888		| (1 << 10) | (1 << 11)))
#define VG_sABGR_8888_PRE_NATIVE_DMP			((VGImageFormat)(VG_sABGR_8888_PRE	| (1 << 10) | (1 << 11)))
#define VG_sABGR_1555_NATIVE_DMP				((VGImageFormat)(VG_sABGR_1555		| (1 << 10) | (1 << 11)))
#define VG_sABGR_4444_NATIVE_DMP				((VGImageFormat)(VG_sABGR_4444		| (1 << 10) | (1 << 11)))
#define VG_lXBGR_8888_NATIVE_DMP				((VGImageFormat)(VG_lXBGR_8888		| (1 << 10) | (1 << 11)))
#define VG_lABGR_8888_NATIVE_DMP				((VGImageFormat)(VG_lABGR_8888		| (1 << 10) | (1 << 11)))
#define VG_lABGR_8888_PRE_NATIVE_DMP			((VGImageFormat)(VG_lABGR_8888_PRE	| (1 << 10) | (1 << 11)))

/* RGB{A,X} channel ordering */
#define VG_sLA_88_NATIVE_DMP					((VGImageFormat)(VG_sLA_88_DMP		| (1 << 10) | (1 << 11)))
#define VG_sLA_88_PRE_NATIVE_DMP				((VGImageFormat)(VG_sLA_88_PRE_DMP	| (1 << 10) | (1 << 11)))
#define VG_lLA_88_NATIVE_DMP					((VGImageFormat)(VG_lLA_88_DMP		| (1 << 10) | (1 << 11)))
#define VG_lLA_88_PRE_NATIVE_DMP				((VGImageFormat)(VG_lLA_88_PRE_DMP	| (1 << 10) | (1 << 11)))
#define VG_sETC1_NATIVE_DMP						((VGImageFormat)(VG_sETC1_DMP		| (1 << 10) | (1 << 11)))
#define VG_lETC1_NATIVE_DMP						((VGImageFormat)(VG_lETC1_DMP		| (1 << 10) | (1 << 11)))

/* {A,X}RGB channel ordering */
#define VG_sAL_88_NATIVE_DMP					((VGImageFormat)(VG_sAL_88_DMP		| (1 << 10) | (1 << 11)))
#define VG_sAL_88_PRE_NATIVE_DMP				((VGImageFormat)(VG_sAL_88_PRE_DMP	| (1 << 10) | (1 << 11)))
#define VG_lAL_88_NATIVE_DMP					((VGImageFormat)(VG_lAL_88_DMP		| (1 << 10) | (1 << 11)))
#define VG_lAL_88_PRE_NATIVE_DMP				((VGImageFormat)(VG_lAL_88_PRE_DMP	| (1 << 10) | (1 << 11)))

/* 
 * LOWER_LEFT NATIVE format
 */

/* RGB{A,X} channel ordering */
#define VG_sRGBX_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sRGBX_8888		| (1 << 10)))
#define VG_sRGBA_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sRGBA_8888		| (1 << 10)))
#define VG_sRGBA_8888_PRE_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_sRGBA_8888_PRE	| (1 << 10)))
#define VG_sRGB_565_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sRGB_565		| (1 << 10)))
#define VG_sRGBA_5551_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sRGBA_5551		| (1 << 10)))
#define VG_sRGBA_4444_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sRGBA_4444		| (1 << 10)))
#define VG_sL_8_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_sL_8			| (1 << 10)))
#define VG_lRGBX_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lRGBX_8888		| (1 << 10)))
#define VG_lRGBA_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lRGBA_8888		| (1 << 10)))
#define VG_lRGBA_8888_PRE_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_lRGBA_8888_PRE	| (1 << 10)))
#define VG_lL_8_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_lL_8			| (1 << 10)))
#define VG_A_8_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_A_8				| (1 << 10)))
#define VG_BW_1_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_BW_1			| (1 << 10)))
#define VG_A_1_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_A_1				| (1 << 10)))
#define VG_A_4_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_A_4				| (1 << 10)))

/* {A,X}RGB channel ordering */
#define VG_sXRGB_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sXRGB_8888		| (1 << 10)))
#define VG_sARGB_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sARGB_8888		| (1 << 10)))
#define VG_sARGB_8888_PRE_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_sARGB_8888_PRE	| (1 << 10)))
#define VG_sARGB_1555_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sARGB_1555		| (1 << 10)))
#define VG_sARGB_4444_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sARGB_4444		| (1 << 10)))
#define VG_lXRGB_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lXRGB_8888		| (1 << 10)))
#define VG_lARGB_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lARGB_8888		| (1 << 10)))
#define VG_lARGB_8888_PRE_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_lARGB_8888_PRE	| (1 << 10)))

/* BGR{A,X} channel ordering */
#define VG_sBGRX_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sBGRX_8888		| (1 << 10)))
#define VG_sBGRA_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sBGRA_8888		| (1 << 10)))
#define VG_sBGRA_8888_PRE_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_sBGRA_8888_PRE	| (1 << 10)))
#define VG_sBGR_565_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sBGR_565		| (1 << 10)))
#define VG_sBGRA_5551_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sBGRA_5551		| (1 << 10)))
#define VG_sBGRA_4444_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sBGRA_4444		| (1 << 10)))
#define VG_lBGRX_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lBGRX_8888		| (1 << 10)))
#define VG_lBGRA_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lBGRA_8888		| (1 << 10)))
#define VG_lBGRA_8888_PRE_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_lBGRA_8888_PRE	| (1 << 10)))

/* {A,X}BGR channel ordering */
#define VG_sXBGR_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sXBGR_8888		| (1 << 10)))
#define VG_sABGR_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sABGR_8888		| (1 << 10)))
#define VG_sABGR_8888_PRE_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_sABGR_8888_PRE	| (1 << 10)))
#define VG_sABGR_1555_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sABGR_1555		| (1 << 10)))
#define VG_sABGR_4444_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sABGR_4444		| (1 << 10)))
#define VG_lXBGR_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lXBGR_8888		| (1 << 10)))
#define VG_lABGR_8888_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lABGR_8888		| (1 << 10)))
#define VG_lABGR_8888_PRE_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_lABGR_8888_PRE	| (1 << 10)))

/* RGB{A,X} channel ordering */
#define VG_sLA_88_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_sLA_88_DMP		| (1 << 10)))
#define VG_sLA_88_PRE_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sLA_88_PRE_DMP	| (1 << 10)))
#define VG_lLA_88_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_lLA_88_DMP		| (1 << 10)))
#define VG_lLA_88_PRE_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lLA_88_PRE_DMP	| (1 << 10)))
#define VG_sETC1_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_sETC1_DMP		| (1 << 10)))
#define VG_lETC1_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_lETC1_DMP		| (1 << 10)))

/* {A,X}RGB channel ordering */
#define VG_sAL_88_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_sAL_88_DMP		| (1 << 10)))
#define VG_sAL_88_PRE_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_sAL_88_PRE_DMP	| (1 << 10)))
#define VG_lAL_88_LOWER_LEFT_NATIVE_DMP			((VGImageFormat)(VG_lAL_88_DMP		| (1 << 10)))
#define VG_lAL_88_PRE_LOWER_LEFT_NATIVE_DMP		((VGImageFormat)(VG_lAL_88_PRE_DMP	| (1 << 10)))


#define VG_NUM_DIRECT_LOAD_IMAGE_NATIVE_FORMATS_DMP	((VGParamType)(0x0000 + _VG_OFFSET_ENUM_DMP))
#define VG_DIRECT_LOAD_IMAGE_NATIVE_FORMATS_DMP		((VGParamType)(0x0001 + _VG_OFFSET_ENUM_DMP))
#define VG_NUM_IMAGE_NATIVE_FORMATS_DMP				VG_NUM_DIRECT_LOAD_IMAGE_NATIVE_FORMATS_DMP
#define VG_IMAGE_NATIVE_FORMATS_DMP					VG_DIRECT_LOAD_IMAGE_NATIVE_FORMATS_DMP

#ifdef VG_VGDMP_PROTOTYPES
VG_API_CALL VGImage VG_API_ENTRY vgCreateImageDataDMP(VGImageFormat format, VGint width, VGint height, VGint size, const void* data, VGbitfield allowedQuality) VG_API_EXIT;
#endif
typedef VGImage (VG_API_ENTRYP PFNVGCREATEIMAGEDATADMPPROC) (VGImageFormat format, VGint width, VGint height, VGint size, const void* data, VGbitfield allowedQuality);

#endif /* VG_DMP_image_native_format_direct_load */

/*
###############################################################################

# #004 VG_DMP_limit_resource
#      0xC010-0xC01F

###############################################################################
*/
#ifndef VG_DMP_limit_resource
#define VG_DMP_limit_resource 1

#define VG_MAX_TOTAL_COORDS_DMP         ((VGParamType)(0x0010 + _VG_OFFSET_ENUM_DMP))
#define VG_MAX_TOTAL_IMAGE_SIZE_DMP     ((VGParamType)(0x0011 + _VG_OFFSET_ENUM_DMP))

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMP_limit_resource */

/*
###############################################################################

# #005
#      0xC020-0xC02F

###############################################################################
*/

/*
###############################################################################

# #006 VG_DMP_color_buffer_dither
#      0xC030-0xC03F

###############################################################################
*/
#ifndef VG_DMP_color_buffer_dither
#define VG_DMP_color_buffer_dither 1

#define VG_COLOR_BUFFER_DITHER_DMP		((VGParamType)(0x0030 + _VG_OFFSET_ENUM_DMP))

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMP_color_buffer_dither */

/*
###############################################################################

# #007 VG_DMP_draw_subimage

###############################################################################
*/
#ifndef VG_DMP_draw_subimage
#define VG_DMP_draw_subimage 1

#ifdef VG_VGDMP_PROTOTYPES
VG_API_CALL void VG_API_ENTRY vgDrawSubImageDMP(VGImage image, VGint x, VGint y, VGint width, VGint height) VG_API_EXIT;
VG_API_CALL void VG_API_ENTRY vgDrawSubImagesDMP(VGImage image, VGuint imageCount, const VGfloat *matrixes, const VGuint *imageIndices, VGuint areaCount, const VGint *areas) VG_API_EXIT;
#endif
typedef void (VG_API_ENTRYP PFNVGDRAWSUBIMAGEDMPPROC) (VGImage image, VGint x, VGint y, VGint width, VGint height);
typedef void (VG_API_ENTRYP PFNVGDRAWSUBIMAGESDMPPROC) (VGImage image, VGuint imageCount, const VGfloat *matrixes, const VGuint *imageIndices, VGuint areaCount, const VGint *areas);

#endif /* VG_DMP_draw_subimage */

/*
###############################################################################

# #008 VG_DMP_multi_draw_image

###############################################################################
*/
#ifndef VG_DMP_multi_draw_image
#define VG_DMP_multi_draw_image 1

#ifdef VG_VGDMP_PROTOTYPES
VG_API_CALL void VG_API_ENTRY vgMultiDrawImageDMP(VGuint imageCount, const VGImage *images, const VGfloat *matrixes) VG_API_EXIT;
#endif
typedef void (VG_API_ENTRYP PFNVGMULTIDRAWIMAGEDMPPROC) (VGuint imageCount, const VGImage *images, const VGfloat *matrixes);

#endif /* VG_DMP_multi_draw_image */

/*
###############################################################################

# #009 VG_DMP_draw_path_data

###############################################################################
*/
#ifndef VG_DMP_draw_path_data
#define VG_DMP_draw_path_data 1

#ifdef VG_VGDMP_PROTOTYPES
VG_API_CALL void VG_API_ENTRY vgDrawPathDataDMP(VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint numSegments, const VGubyte *pathSegments, const void *pathData, VGbitfield paintModes) VG_API_EXIT;
VG_API_CALL void VG_API_ENTRY vgDrawPathDataArraysDMP(VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint numPaths, const VGint *numSegments, const VGubyte **pathSegments, const void **pathData, VGbitfield paintModes) VG_API_EXIT;
#endif
typedef void (VG_API_ENTRYP PFNVGDRAWPATHDATADMPPROC) (VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint numSegments, const VGubyte *pathSegments, const void *pathData, VGbitfield paintModes);
typedef void (VG_API_ENTRYP PFNVGDRAWPATHDATAARRAYSDMPPROC) (VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint numPaths, const VGint *numSegments, const VGubyte **pathSegments, const void **pathData, VGbitfield paintModes);

#endif /* VG_DMP_draw_path_data */

/*
###############################################################################

# Reserved 0xC040-0xC07F

###############################################################################
*/

/*
###############################################################################

# #010 VG_DMP_procedural_gradient
#      0xC080-0xC0FF

###############################################################################
*/
#ifndef VG_DMP_procedural_gradient
#define VG_DMP_procedural_gradient 1

typedef enum {
  VG_PROCGRADIENT_DMP					= 0x0080 + _VG_OFFSET_ENUM_DMP,

  /* glTexEnvf() */
  VG_PROCGRADIENT_CLAMP_U_DMP			= 0x0082 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_CLAMP_V_DMP			= 0x0083 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_1DMAPPING_RGB_DMP		= 0x0086 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_1DMAPPING_A_DMP		= 0x0087 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_BIAS_DMP				= 0x0088 + _VG_OFFSET_ENUM_DMP,
  /* noise related functions */
  VG_PROCGRADIENT_NOISE_U_DMP			= 0x008E + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_NOISE_V_DMP			= 0x008F + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_ENABLE_NOISE_DMP		= 0x0091 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_NOISE_LUT_DMP			= 0x0092 + _VG_OFFSET_ENUM_DMP,

  VG_PROCGRADIENT_SHIFTU_ENABLE_DMP		= 0x0093 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_SHIFTV_ENABLE_DMP		= 0x0094 + _VG_OFFSET_ENUM_DMP,

  VG_PROCGRADIENT_TEXTURE_FILTER_DMP	= 0x0095 + _VG_OFFSET_ENUM_DMP,

  /* functions using LUT table */
  VG_PROCGRADIENT_U_DMP					= 0x009A + _VG_OFFSET_ENUM_DMP, /* Register value PFS_U 0 -->increment of 1 for next values */
  VG_PROCGRADIENT_U2_DMP				= VG_PROCGRADIENT_U_DMP			+ 1,	/* 1 */
  VG_PROCGRADIENT_V_DMP				  	= VG_PROCGRADIENT_U2_DMP		+ 1,	/* 2 */
  VG_PROCGRADIENT_V2_DMP				= VG_PROCGRADIENT_V_DMP			+ 1,	/* 3 */
  VG_PROCGRADIENT_ADD_DMP				= VG_PROCGRADIENT_V2_DMP		+ 1,	/* 4 */
  VG_PROCGRADIENT_ADD2_DMP				= VG_PROCGRADIENT_ADD_DMP		+ 1,	/* 5 */
  VG_PROCGRADIENT_ADDSQRT2_DMP			= VG_PROCGRADIENT_ADD2_DMP		+ 1,	/* 6 */
  VG_PROCGRADIENT_MIN_DMP				= VG_PROCGRADIENT_ADDSQRT2_DMP	+ 1,	/* 7 */
  VG_PROCGRADIENT_MAX_DMP				= VG_PROCGRADIENT_MIN_DMP		+ 1,	/* 8 */
  VG_PROCGRADIENT_RMAX_DMP				= VG_PROCGRADIENT_MAX_DMP		+ 1,	/* 9 */
  VG_PROCGRADIENT_ALPHA_SEPARATE_DMP	= 0x00A5 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_RGB_LUT_DMP			= 0x00B0 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_A_LUT_DMP				= 0x00B3 + _VG_OFFSET_ENUM_DMP,
  VG_PROCGRADIENT_COLOR_RAMP_DMP		= 0x00B4 + _VG_OFFSET_ENUM_DMP,

  VG_CLAMP_TO_ZERO_DMP					= 0x00C0 + _VG_OFFSET_ENUM_DMP,			/* 0 */
  VG_CLAMP_TO_EDGE_DMP					= VG_CLAMP_TO_ZERO_DMP			+ 1,	/* 1 */
  VG_REPEAT_DMP							= VG_CLAMP_TO_EDGE_DMP			+ 1,	/* 2 */
  VG_MIRRORED_REPEAT_DMP				= VG_REPEAT_DMP					+ 1,	/* 3 */
  VG_PULSE_DMP							= VG_MIRRORED_REPEAT_DMP		+ 1,	/* 4 */

  VG_NONE_DMP							= 0x00D0 + _VG_OFFSET_ENUM_DMP,			/* 0 */
  VG_ODD_DMP							= VG_NONE_DMP					+ 1,	/* 1 */
  VG_EVEN_DMP		     				= VG_ODD_DMP					+ 1,	/* 2 */

  VG_NEAREST_DMP						= 0x00E0 + _VG_OFFSET_ENUM_DMP,			/* 0 */
  VG_LINEAR_DMP							= VG_NEAREST_DMP				+ 1,	/* 1 */

  VG_PROC_GRADIENT_PARAM_DMP_FORCE_SIZE	= VG_MAX_ENUM
} VGProcGradientParamDMP;


#define VG_PAINT_TYPE_PROCGRADIENT_DMP	((VGParamType)(0x00F0 + _VG_OFFSET_ENUM_DMP))


#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMP_procedural_gradient */

/*
###############################################################################

# #011 VG_DMP_debug_query
#      0xC100-0xC10F

###############################################################################
*/
#ifndef VG_DMP_debug_query
#define VG_DMP_debug_query 1

#define VG_COMMANDBUFFER_FULL_DMP			((VGParamType)(0x0100 + _VG_OFFSET_ENUM_DMP))
#define VG_PATH_COMMANDBUFFER_FULL_DMP		((VGParamType)(0x0101 + _VG_OFFSET_ENUM_DMP))
#define VG_FILL_COMMANDBUFFER_FULL_DMP		((VGParamType)(0x0102 + _VG_OFFSET_ENUM_DMP))
#define VG_PATH_COMMANDBUFFER_OVERFLOW_DMP	((VGParamType)(0x0103 + _VG_OFFSET_ENUM_DMP))
#define VG_FILL_COMMANDBUFFER_OVERFLOW_DMP	((VGParamType)(0x0104 + _VG_OFFSET_ENUM_DMP))

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMP_debug_query */

/*
###############################################################################

# #012
# Reserved 0xC060-0xC06F

###############################################################################
*/

/*
###############################################################################

# #013
# Reserved 0xC040-0xC04F

###############################################################################
*/

/*
###############################################################################

# #014
# Reserved 0xC050-0xC05F

###############################################################################
*/

/*
###############################################################################

# #015 VG_DMP_YUV_422_420_semiplanar

###############################################################################
*/
#ifndef VG_DMP_YUV_422_420_semiplanar
#define VG_DMP_YUV_422_420_semiplanar 1

#define VG_sYUV_422_SEMIPLANAR_DMP						((VGImageFormat)21)
#define VG_lYUV_422_SEMIPLANAR_DMP						((VGImageFormat)22)
#define VG_sYUV_420_SEMIPLANAR_DMP						((VGImageFormat)23)
#define VG_lYUV_420_SEMIPLANAR_DMP						((VGImageFormat)24)

#define VG_sYUV_422_SEMIPLANAR_NATIVE_DMP				((VGImageFormat)(VG_sYUV_422_SEMIPLANAR_DMP | (1 << 10) | (1 << 11)))
#define VG_lYUV_422_SEMIPLANAR_NATIVE_DMP				((VGImageFormat)(VG_lYUV_422_SEMIPLANAR_DMP | (1 << 10) | (1 << 11)))
#define VG_sYUV_420_SEMIPLANAR_NATIVE_DMP				((VGImageFormat)(VG_sYUV_420_SEMIPLANAR_DMP | (1 << 10) | (1 << 11)))
#define VG_lYUV_420_SEMIPLANAR_NATIVE_DMP				((VGImageFormat)(VG_lYUV_420_SEMIPLANAR_DMP | (1 << 10) | (1 << 11)))

#define VG_sYUV_422_SEMIPLANAR_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_sYUV_422_SEMIPLANAR_DMP | (1 << 10)))
#define VG_lYUV_422_SEMIPLANAR_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_lYUV_422_SEMIPLANAR_DMP | (1 << 10)))
#define VG_sYUV_420_SEMIPLANAR_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_sYUV_420_SEMIPLANAR_DMP | (1 << 10)))
#define VG_lYUV_420_SEMIPLANAR_LOWER_LEFT_NATIVE_DMP	((VGImageFormat)(VG_lYUV_420_SEMIPLANAR_DMP | (1 << 10)))

#ifdef VG_VGDMP_PROTOTYPES
VG_API_CALL void VG_API_ENTRY vgImageSubDataYUVsemiplanarDMP(VGImage image, const void * Yplane, const void * UVplane, VGint YPlaneDataStride, VGint UVPlaneDataStride,
			VGImageFormat dataFormat, VGint x, VGint y, VGint width, VGint height) VG_API_EXIT;
VG_API_CALL VGImage VG_API_ENTRY vgCreateImageDataYUVsemiplanarDMP(
			VGImageFormat format, VGint width, VGint height,
			VGint size_Yplane, VGint size_UVplane,
			const void* Yplane, const void* UVPlane, VGbitfield allowedQuality) VG_API_EXIT;
VG_API_CALL VGImage VG_API_ENTRY vgCreateImageStandardDataYUVsemiplanarDMP(
			VGImageFormat format, VGint width, VGint height,
			VGint size_Yplane, VGint size_UVplane,
			const void* Yplane, const void* UVPlane, VGbitfield allowedQuality) VG_API_EXIT;
VG_API_CALL void VG_API_ENTRY vgReadPixelsYUVsemiplanarDMP(void * Yplane, void * UVplane, VGint YPlanelataStride, VGint UVPlaneDataStride,
			VGImageFormat dataFormat,
			VGint sx, VGint sy, VGint width, VGint height) VG_API_EXIT;
#endif
typedef void (VG_API_ENTRYP PFNVGIMAGESUBDATAYUVSEMIPLANARDMPPROC) (VGImage image, const void * Yplane, const void * UVplane, VGint YPlaneDataStride, VGint UVPlaneDataStride,
			VGImageFormat dataFormat, VGint x, VGint y, VGint width, VGint height);
typedef VGImage (VG_API_ENTRYP PFNVGCREATEIMAGEDATAYUVSEMIPLANARDMPPROC) (
			VGImageFormat format, VGint width, VGint height,
			VGint size_Yplane, VGint size_UVplane,
			const void* Yplane, const void* UVPlane, VGbitfield allowedQuality);
typedef VGImage (VG_API_ENTRYP PFNVGCREATEIMAGESTANDARDDATAYUVSEMIPLANARDMPPROC) (
			VGImageFormat format, VGint width, VGint height,
			VGint size_Yplane, VGint size_UVplane,
			const void* Yplane, const void* UVPlane, VGbitfield allowedQuality);
typedef void (VG_API_ENTRYP PFNVGREADPIXELSYUVSEMIPLANARDMPPROC) (
			void * Yplane, void * UVplane, VGint YPlanelataStride, VGint UVPlaneDataStride,
			VGImageFormat dataFormat,
			VGint sx, VGint sy, VGint width, VGint height);

#endif /* VG_DMP_YUV_422_420_semiplanar */

/*
###############################################################################

# #016
# Reserved 0xC120-0xC12F

###############################################################################
*/

/*
###############################################################################

# #017

###############################################################################
*/

/*
###############################################################################

# #018 VG_DMP_image_standard_format_direct_load
#      0xC190-0xC19F

###############################################################################
*/
#ifndef VG_DMP_image_standard_format_direct_load
#define VG_DMP_image_standard_format_direct_load 1

#define VG_NUM_DIRECT_LOAD_IMAGE_STANDARD_FORMATS_DMP	((VGParamType)(0x0190 + _VG_OFFSET_ENUM_DMP))
#define VG_DIRECT_LOAD_IMAGE_STANDARD_FORMATS_DMP		((VGParamType)(0x0191 + _VG_OFFSET_ENUM_DMP))

#ifdef VG_VGDMP_PROTOTYPES
VG_API_CALL VGImage VG_API_ENTRY vgCreateImageStandardDataDMP(
	VGImageFormat format, VGint width, VGint height,
	VGint size, const void* data, VGbitfield allowedQuality) VG_API_EXIT;
#endif
typedef VGImage (VG_API_ENTRYP PFNVGCREATEIMAGESTANDARDDATADMPPROC) (
	VGImageFormat format, VGint width, VGint height,
	VGint size, const void* data, VGbitfield allowedQuality);

#endif /* VG_DMP_image_standard_format_direct_load */

/*
###############################################################################

# #019
# Reserved 0xC070-0xC07F

###############################################################################
*/

/*
###############################################################################

# #020

###############################################################################
*/

/*
###############################################################################

# #021
# Reserved 0xC140-0xC14F

###############################################################################
*/

/*
###############################################################################

# #022
# Reserved 0xC170-0xC18F

###############################################################################
*/

/*
###############################################################################

# #023
# Reserved 0xC150-0xC15F

###############################################################################
*/

/*
###############################################################################

# #024
# Reserved 0xC160-0xC16F

###############################################################################
*/

/*
###############################################################################

# #025

###############################################################################
*/

/*
###############################################################################

# #026
# Reserved 0xC130

###############################################################################
*/

/*
###############################################################################

# #027
# Reserved 0xC1A0-0xC1AF, 0xC200-0xC2FF, 0xC300-0xC3FF

###############################################################################
*/

/*
###############################################################################

# #028
# Reserved 0xC1B0-0xC1BF

###############################################################################
*/


#ifdef __cplusplus
} /* extern "C" */
#endif

#include <DMP/vgDMPX.h>

#endif /* _VGDMP_H */
