/*
  Copyright (c) 2013, Digital Media Professionals. All rights reserved.
*/

#ifndef __GLDMPX_H_
#define __GLDMPX_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <GLES/gl.h>

#ifndef GL_APIENTRYP
#   define GL_APIENTRYP GL_APIENTRY*
#endif

#ifndef GL_GLDMPX_PROTOTYPES
#define GL_GLDMPX_PROTOTYPES
#endif

/*-------------------------------------------------------------------------*
 * DMP extension tokens
 *-------------------------------------------------------------------------*/

/*
###############################################################################

# #007 GL_DMPX_conversion_YUV_hw_raw_setting

###############################################################################
*/
#ifndef GL_DMPX_conversion_YUV_hw_raw_setting
#define GL_YUV_RGB_CONVERSION_DMPX					0x6820
#define GL_YUV_RGB_MATRIX_COEFFICIENT_DMPX			0x6821
#define GL_YUV_RGB_SCALING_OFFSET_DMPX				0x6822
#define GL_YUV_RGB_SCALING_GAIN_DMPX				0x6823
#define GL_RGB_YUV_MATRIX_COEFFICIENT_DMPX			0x6824
#define GL_RGB_YUV_SCALING_OFFSET_DMPX				0x6825
#define GL_RGB_YUV_SCALING_GAIN_DMPX				0x6826
#define GL_YUV422_CONVERSION_SAMPLING_MODE_DMPX		0x6827
#define GL_YUV420_CONVERSION_SAMPLING_MODE_DMPX		0x6828

#define GL_YUV422_SAMPLING_MODE_EVEN_DMPX			0x6830
#define GL_YUV422_SAMPLING_MODE_ODD_DMPX			0x6831
#define GL_YUV422_SAMPLING_MODE_AVERAGE_DMPX		0x6832
#define GL_YUV420_SAMPLING_MODE_TAKE0_DMPX			0x6833
#define GL_YUV420_SAMPLING_MODE_TAKE1_DMPX			0x6834
#define GL_YUV420_SAMPLING_MODE_TAKE2_DMPX			0x6835
#define GL_YUV420_SAMPLING_MODE_TAKE3_DMPX			0x6836
#define GL_YUV420_SAMPLING_MODE_AVERAGE_DMPX		0x6837
#define GL_YUV420_SAMPLING_MODE_AVERAGE_EVEN_DMPX	0x6838
#define GL_YUV420_SAMPLING_MODE_AVERAGE_ODD_DMPX	0x6839
#endif

/*-------------------------------------------------------------------------*
 * DMP extension functions
 *-------------------------------------------------------------------------*/

/* GL_DMPX_conversion_YUV_hw_raw_setting */
#ifndef GL_DMPX_conversion_YUV_hw_raw_setting
#define GL_DMPX_conversion_YUV_hw_raw_setting 1
#ifdef GL_GLDMPX_PROTOTYPES
GL_API void GL_APIENTRY glFramebufferParameterivDMPX( GLenum target, GLenum pname, const GLint *params);
GL_API void GL_APIENTRY glGetFramebufferParameterivDMPX( GLenum target, GLenum pname, GLint *params);
#endif
typedef void (GL_APIENTRYP PFNGLFRAMEBUFFERPARAMETERIVDMPXPROC) ( GLenum target, GLenum pname, const GLint *params);
typedef void (GL_APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVDMPXPROC) ( GLenum target, GLenum pname, GLint *params);
#endif


#ifdef __cplusplus
}
#endif

#endif /* __GLDMPX_H_ */


