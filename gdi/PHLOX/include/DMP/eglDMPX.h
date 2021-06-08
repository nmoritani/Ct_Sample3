/*
  Copyright (c) 2013, Digital Media Professionals. All rights reserved.
  For Phlox
*/
#ifndef _EGLDMPX_H
#define _EGLDMPX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <EGL/egl.h>
#include <EGL/eglext.h>

#ifndef EGL_API_ENTRYP
#	define EGL_API_ENTRYP EGL_API_ENTRY*
#endif

#ifndef EGL_EGLDMPX_PROTOTYPES
#	define EGL_EGLDMPX_PROTOTYPES
#endif

/* */

#ifndef KHRONOS_APIENTRY
#	define KHRONOS_APIENTRY        /* empty */
#endif

#ifndef EGLAPIENTRY
#	define EGLAPIENTRY  KHRONOS_APIENTRY
#endif

#ifndef EGLAPIENTRYP
#	define EGLAPIENTRYP KHRONOS_APIENTRY*
#endif

/* Header file version number */
#define EGL_EGLDMPX_VERSION	1


/*
###############################################################################

# #002
# Reserved 0x3FF2-0x3FF4

###############################################################################
*/

/*
###############################################################################

# #006

###############################################################################
*/

/*
###############################################################################

# #007
# Reserved 0x3FFB

###############################################################################
*/

/*
###############################################################################

# #009
# Reserved 0x3FE6

###############################################################################
*/

/*
###############################################################################

# #010
# Reserved 0x3FE0-0x3FE5

###############################################################################
*/

/*
###############################################################################

# #013
# Reserved 0x3FE7

###############################################################################
*/

/*
###############################################################################

# #014
# Reserved 0x3FD8-0x3FDF

###############################################################################
*/

/*
###############################################################################

# #015
# Reserved 0x3FD0

###############################################################################
*/

/*
###############################################################################

# #017
# Reserved 0x3FE0, 0x3FD1-0x3FD3

###############################################################################
*/

/*
###############################################################################

# #018

###############################################################################
*/

/*
###############################################################################

# #020 EGL_DMPX_YUV_attributes_hw_raw_setting
#      0x3FA0-0x3FAA,
#      0x3FB2-0x3FCC

###############################################################################
*/
#ifndef EGL_DMPX_YUV_attributes_hw_raw_setting
#define EGL_DMPX_YUV_attributes_hw_raw_setting 1

#define EGL_RGB_YUV_CONVERSION_RY_DMPX				0x3FB2
#define EGL_RGB_YUV_CONVERSION_RU_DMPX				0x3FB3
#define EGL_RGB_YUV_CONVERSION_RV_DMPX				0x3FB4
#define EGL_RGB_YUV_CONVERSION_GY_DMPX				0x3FB5
#define EGL_RGB_YUV_CONVERSION_GU_DMPX				0x3FB6
#define EGL_RGB_YUV_CONVERSION_GV_DMPX				0x3FB7
#define EGL_RGB_YUV_CONVERSION_BY_DMPX				0x3FB8
#define EGL_RGB_YUV_CONVERSION_BU_DMPX				0x3FB9
#define EGL_RGB_YUV_CONVERSION_BV_DMPX				0x3FBA
#define EGL_RGB_YUV_CONVERSION_SYOFFSETR_DMPX		0x3FBB
#define EGL_RGB_YUV_CONVERSION_SYOFFSETF_DMPX		0x3FBC
#define EGL_RGB_YUV_CONVERSION_SYGAIN_DMPX			0x3FBD
#define EGL_RGB_YUV_CONVERSION_SUGAIN_DMPX			0x3FBE
#define EGL_RGB_YUV_CONVERSION_SVGAIN_DMPX			0x3FBF
#define EGL_YUV422_CONVERSION_SAMPLING_MODE_DMPX	0x3FC0
#define EGL_YUV420_CONVERSION_SAMPLING_MODE_DMPX	0x3FC1
#define EGL_VG_YUV_AVERAGE_COMPLEMENT_DMPX			0x3FC2

#define EGL_YUV422_SAMPLING_MODE_EVEN_DMPX			0x3FC3
#define EGL_YUV422_SAMPLING_MODE_ODD_DMPX			0x3FC4
#define EGL_YUV422_SAMPLING_MODE_AVERAGE_DMPX		0x3FC5

#define EGL_YUV420_SAMPLING_MODE_TAKE0_DMPX			0x3FC6
#define EGL_YUV420_SAMPLING_MODE_TAKE1_DMPX			0x3FC7
#define EGL_YUV420_SAMPLING_MODE_TAKE2_DMPX			0x3FC8
#define EGL_YUV420_SAMPLING_MODE_TAKE3_DMPX			0x3FC9
#define EGL_YUV420_SAMPLING_MODE_AVERAGE_DMPX		0x3FCA
#define EGL_YUV420_SAMPLING_MODE_AVERAGE_EVEN_DMPX	0x3FCB
#define EGL_YUV420_SAMPLING_MODE_AVERAGE_ODD_DMPX	0x3FCC

#define EGL_YUV_RGB_CONVERSION_UR_DMPX				0x3FA0
#define EGL_YUV_RGB_CONVERSION_UG_DMPX				0x3FA1
#define EGL_YUV_RGB_CONVERSION_UB_DMPX				0x3FA2
#define EGL_YUV_RGB_CONVERSION_VR_DMPX				0x3FA3
#define EGL_YUV_RGB_CONVERSION_VG_DMPX				0x3FA4
#define EGL_YUV_RGB_CONVERSION_VB_DMPX				0x3FA5
#define EGL_YUV_RGB_CONVERSION_SYOFFSETR_DMPX		0x3FA6
#define EGL_YUV_RGB_CONVERSION_SYOFFSETF_DMPX		0x3FA7
#define EGL_YUV_RGB_CONVERSION_SYGAIN_DMPX			0x3FA8
#define EGL_YUV_RGB_CONVERSION_SUGAIN_DMPX			0x3FA9
#define EGL_YUV_RGB_CONVERSION_SVGAIN_DMPX			0x3FAA

#endif /* EGL_DMPX_YUV_attributes_hw_raw_setting */

/*
###############################################################################

# #021 EGL_DMPX_query_cross_error
#      0x3FFF

###############################################################################
*/
#ifndef EGL_DMPX_query_cross_error
#define EGL_DMPX_query_cross_error 1

#define EGL_DRAW_MODE_NO_CHECK_CROSS_ERROR_DMPX	0x0000
#define EGL_DRAW_MODE_CHECK_CROSS_ERROR_DMPX	0x0003

#define EGL_CROSS_ERROR_DMPX			0x3FFF

#ifndef EGL_DMP_unlimited_cross
#ifdef EGL_EGLDMP_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDrawFrameModeDMP(EGLDisplay dpy, EGLint mode);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryFrameDMP(EGLDisplay dpy, EGLint attribute, EGLint *value);
#endif
EGLAPI EGLBoolean EGLAPIENTRY eglDrawFrameModeDMP(EGLDisplay dpy, EGLint mode);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYFRAMEDMPPROC) (EGLDisplay dpy, EGLint attribute, EGLint *value);
#endif /* EGL_DMP_unlimited_crosss */

#endif /* EGL_DMPX_query_cross_error */

/*
###############################################################################

# #022 EGL_DMPX_dump_reference_colorbuffer

###############################################################################
*/
#ifndef EGL_DMPX_dump_reference_colorbuffer
#define EGL_DMPX_dump_reference_colorbuffer 1

#ifdef EGL_EGLDMP_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglDumpReferenceColorBufferDMPX(EGLDisplay dpy, EGLSurface surface);
#endif
typedef EGLBoolean (EGLAPIENTRYP EGLDUMPREFERENCECOLORBUFFERDMPXPROC) (EGLDisplay dpy, EGLSurface surface);

#endif /* EGL_DMPX_dump_reference_colorbuffer */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* _EGLDMPX_H */
