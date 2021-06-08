/*
  Copyright (c) 2012-2013, Digital Media Professionals. All rights reserved.
  For Phlox
*/
#ifndef _VGDMPX_H
#define _VGDMPX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <VG/openvg.h>
#include <VG/vgu.h>
#include <DMP/vgDMP.h>

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
#define VG_VGDMPX_VERSION	1

/*******************************/

/*----------------
 * DMPX extensions
 *----------------
*/

/*
###############################################################################

# DMP: 0xC000-0xCFFF

###############################################################################
*/

#ifndef	_VG_OFFSET_ENUM_DMP
#	define _VG_OFFSET_ENUM_DMP		0xC000
#endif /* _VG_OFFSET_ENUM_DMP */

/*
###############################################################################

# #005
# Reserved 0xC020-0xC02F

###############################################################################
*/

/*
###############################################################################

# #012
# Reserved 0xC060-0xC06F

###############################################################################
*/

/*
###############################################################################

# #013 VG_DMPX_clear_linear_gradient_vertical
#      0xC040-0xC04F

###############################################################################
*/
#ifndef VG_DMPX_clear_linear_gradient_vertical
#define VG_DMPX_clear_linear_gradient_vertical 1

#define VG_CLEAR_TYPE_DMPX							((VGParamType)(0x0040 + _VG_OFFSET_ENUM_DMP))
#define VG_CLEAR_LINEAR_GRADIENT_DMPX				((VGParamType)(0x0041 + _VG_OFFSET_ENUM_DMP))
#define VG_CLEAR_COLOR_RAMP_SPREAD_MODE_DMPX		((VGParamType)(0x0042 + _VG_OFFSET_ENUM_DMP))
#define VG_CLEAR_COLOR_RAMP_STOPS_DMPX				((VGParamType)(0x0043 + _VG_OFFSET_ENUM_DMP))
#define VG_CLEAR_COLOR_RAMP_PREMULTIPLIED_DMPX		((VGParamType)(0x0044 + _VG_OFFSET_ENUM_DMP))
#define VG_MAX_CLEAR_COLOR_RAMP_STOPS_DMPX			((VGParamType)(0x0045 + _VG_OFFSET_ENUM_DMP))

#define VG_CLEAR_TYPE_NORMAL_DMPX					((VGParamType)(0x0047 + _VG_OFFSET_ENUM_DMP))
#define VG_CLEAR_TYPE_LINEAR_GRADIENT_VERTICAL_DMPX	((VGParamType)(0x0048 + _VG_OFFSET_ENUM_DMP))

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif	/* VG_DMPX_clear_linear_gradient_vertical */

/*
###############################################################################

# #014 VG_DMPX_paint_non_affine_matrix
#      0xC050-0xC05F

###############################################################################
*/
#ifndef VG_DMPX_paint_non_affine_matrix
#define VG_DMPX_paint_non_affine_matrix 1

#define VG_PAINT_NON_AFFINE_MATRIX_DMPX				((VGParamType)(0x0050 + _VG_OFFSET_ENUM_DMP))

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMPX_paint_non_affine_matrix */

/*
###############################################################################

# #016 VG_DMPX_conversion_YUV_hw_raw_setting
#      0xC120-0xC12F

###############################################################################
*/
#ifndef VG_DMPX_conversion_YUV_hw_raw_setting
#define VG_DMPX_conversion_YUV_hw_raw_setting 1

#define VG_YUV_RGB_MATRIX_COEFFICIENT_DMPX	((VGParamType)(0x0120 + _VG_OFFSET_ENUM_DMP))
#define VG_YUV_RGB_SCALING_OFFSET_DMPX		((VGParamType)(0x0121 + _VG_OFFSET_ENUM_DMP))
#define VG_YUV_RGB_SCALING_GAIN_DMPX		((VGParamType)(0x0122 + _VG_OFFSET_ENUM_DMP))
#define VG_RGB_YUV_MATRIX_COEFFICIENT_DMPX	((VGParamType)(0x0123 + _VG_OFFSET_ENUM_DMP))
#define VG_RGB_YUV_SCALING_OFFSET_DMPX		((VGParamType)(0x0124 + _VG_OFFSET_ENUM_DMP))
#define VG_RGB_YUV_SCALING_GAIN_DMPX		((VGParamType)(0x0125 + _VG_OFFSET_ENUM_DMP))

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMPX_conversion_YUV_hw_raw_setting */

/*
###############################################################################

# #017

###############################################################################
*/

/*
###############################################################################

# #019 VG_DMPX_max_cross_config
#      0xC070-0xC07F

###############################################################################
*/
#ifndef VG_DMPX_max_cross_config
#define VG_DMPX_max_cross_config 1

#define VG_NUM_MAX_CROSS_DMPX				((VGParamType)(0x0070 + _VG_OFFSET_ENUM_DMP))

#ifdef VG_VGDMP_PROTOTYPES
#endif

#endif /* VG_DMPX_max_cross_config */

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
# Reserved 0xC130-0xC13F

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

#endif /* _VGDMPX_H */
