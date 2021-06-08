/*
	Copyright (c) 2013, Digital Media Professionals. All rights reserved.
*/
#ifndef __GLDMP_H_
#define __GLDMP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <GLES/gl.h>

#ifndef GL_APIENTRYP
#   define GL_APIENTRYP GL_APIENTRY*
#endif

#ifndef GL_GLDMP_PROTOTYPES
#define GL_GLDMP_PROTOTYPES
#endif

/*------------------------------------------------------------------------*
 * DMP extension tokens
 *------------------------------------------------------------------------*/

/*
###############################################################################

# #001 GL_DMP_blend_color

###############################################################################
*/
#ifndef GL_DMP_blend_color
#define GL_CONSTANT_COLOR_DMP                                   0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR_DMP                         0x8002
#define GL_CONSTANT_ALPHA_DMP                                   0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA_DMP                         0x8004
#define GL_BLEND_COLOR_DMP                                      0x8005
#endif

/*
###############################################################################

# #002 GL_DMP_texture_native_format_direct_load
       GL_DMP_native_load, GL_DMP_texture_native_load

###############################################################################
*/
#if !defined(GL_DMP_texture_native_load) && !defined(GL_DMP_native_load) && !defined(GL_DMP_texture_native_format_direct_load)
#define GL_TEXTURE_NATIVE_LOAD_DMP                              0x1011
#endif

#ifndef GL_DMP_texture_native_format_direct_load
#define GL_TEXTURE_NATIVE_FORMAT_DIRECT_LOAD_DMP                GL_TEXTURE_NATIVE_LOAD_DMP
#endif

/*
###############################################################################

# #003 GL_DMP_texture_standard_format_direct_load

###############################################################################
*/
#ifndef GL_DMP_texture_standard_format_direct_load
#define GL_TEXTURE_STANDARD_FORMAT_DIRECT_LOAD_DMP              0x6800
#endif

/*
###############################################################################

# #004 GL_DMP_rg8

###############################################################################
*/
#ifndef GL_DMP_rg8
#define GL_RG8_DMP                                              0x822B
#endif

/*
###############################################################################

# #005 GL_DMP_texture_YUV_422_420_semiplanar

###############################################################################
*/
#ifndef GL_DMP_texture_YUV_422_420_semiplanar
#define GL_YUV_422_SEMIPLANAR_DMP                               0x6810
#define GL_YUV_420_SEMIPLANAR_DMP                               0x6811
#ifndef GL_UNSIGNED_SHORT_8_8_DMP
#	define GL_UNSIGNED_SHORT_8_8_DMP                            0x85BA
#endif /* GL_UNSIGNED_SHORT_8_8_DMP */
#endif

/*
###############################################################################

# #006 GL_DMP_read_format_YUV

###############################################################################
*/
#ifndef GL_DMP_read_format_YUV
#define GL_YUV_422_SEMIPLANAR_YPLANE_DMP                        0x6812
#define GL_YUV_422_SEMIPLANAR_UVPLANE_DMP                       0x6813
#define GL_YUV_420_SEMIPLANAR_YPLANE_DMP                        0x6814
#define GL_YUV_420_SEMIPLANAR_UVPLANE_DMP                       0x6815
#endif

/*
###############################################################################

# #009 GL_DMP_line_stipple

###############################################################################
*/
#ifndef GL_DMP_line_stipple
#define GL_LINE_STIPPLE_DMP                                     0x0B24
#endif

/*
###############################################################################

# #010 GL_DMP_debug_query

###############################################################################
*/
#ifndef GL_DMP_debug_query
#define GL_DRAW_VERTEX_ARRAY_BUFFERED_DMP                       0x1012
#define GL_COMMANDBUFFER_FULL_DMP                               0x1013
#define GL_COMMANDBUFFER_OVERFLOW_DMP							0x1014
#endif

/*
###############################################################################

# #011 GL_DMP_texture_lod_bias

###############################################################################
*/
#ifndef GL_DMP_texture_lod_bias
#define GL_TEXTURE_LOD_BIAS_DMP                                 0x8501
#endif

/*
###############################################################################

# #013 GL_DMP_texture_border_color

###############################################################################
*/
#ifndef GL_DMP_texture_border_color
#define GL_TEXTURE_BORDER_COLOR_DMP                             0x1004
#define GL_CLAMP_TO_BORDER_DMP                                  0x812D
#endif


/*------------------------------------------------------------------------*
 * DMP extension functions
 *------------------------------------------------------------------------*/

/* GL_DMP_line_stipple(DMP add) */
#ifndef GL_DMP_line_stipple
#define GL_DMP_line_stipple 1
#ifdef GL_GLDMP_PROTOTYPES
GL_API void GL_APIENTRY glLineStippleDMP (GLint factor, GLushort pattern);
#endif
typedef void (GL_APIENTRYP PFNGLLINESTIPPLEDMPPROC) (GLint factor, GLushort pattern);
#endif

/* GL_DMP_blend_color(DMP add) */
#ifndef GL_DMP_blend_color
#define GL_DMP_blend_color 1
#ifdef GL_GLDMP_PROTOTYPES
GL_API void GL_APIENTRY glBlendColorDMP ( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
#endif
typedef void (GL_APIENTRYP PFNGLBLENDCOLORDMPPROC) ( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
#endif

/* GL_DMP_texture_border_color(DMP add) */
#ifndef GL_DMP_texture_border_color
#define GL_DMP_texture_border_color 1
#endif

/* GL_DMP_rg8(DMP add) */
#ifndef GL_DMP_rg8
#define GL_DMP_rg8 1
#endif

/* GL_DMP_texture_lod_bias(DMP add) */
#ifndef GL_DMP_texture_lod_bias
#define GL_DMP_texture_lod_bias 1
#endif

/* GL_DMP_texture_native_load(DMP add) */
#ifndef GL_DMP_texture_native_load
#define GL_DMP_texture_native_load 1
#endif

/* GL_DMP_debug_query(DMP add) */
#ifndef GL_DMP_debug_query
#define GL_DMP_debug_query 1
#endif

/* GL_DMP_texture_YUV_422_420_semiplanar */
#ifndef GL_DMP_texture_YUV_422_420_semiplanar
#define GL_DMP_texture_YUV_422_420_semiplanar 1
#ifdef GL_GLDMP_PROTOTYPES
GL_API void GL_APIENTRY glTexImage2DYUVsemiplanarDMP ( GLenum target, GLint level, GLint internalformat, GLsizei width,
	GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *Yplane, const GLvoid *UVplane);
#endif
typedef void (GL_APIENTRYP PFNGLTEXIMAGE2DYUVSEMIPLANARDMPPROC) ( GLenum target, GLint level, GLint internalformat, GLsizei width,
	GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *Yplane, const GLvoid *UVplane);
#endif

/* GL_DMP_read_format_YUV */
#ifndef GL_DMP_read_format_YUV
#define GL_DMP_read_format_YUV 1
#endif

/* GL_DMP_texture_2D_limited_npot */
#ifndef GL_DMP_texture_2D_limited_npot
#define GL_DMP_texture_2D_limited_npot 1
#ifdef GL_GLDMP_PROTOTYPES
GL_API void GL_APIENTRY glRenderbufferStorageTexture2DDMP( GLenum target, GLenum internalformat, GLenum textarget,
	GLuint texture, GLint level);
#endif
typedef void (GL_APIENTRYP PFNGLRENDERBUFFERSTORAGETEXTURE2DDMPPROC) ( GLenum target, GLenum internalformat, GLenum textarget,
	GLuint texture, GLint level);
#endif

/* GL_DMP_texture_native_format_direct_load */
#ifndef GL_DMP_texture_native_format_direct_load
#define GL_DMP_texture_native_format_direct_load 1
#endif

/* GL_DMP_texture_standard_format_direct_load */
#ifndef GL_DMP_texture_standard_format_direct_load
#define GL_DMP_texture_standard_format_direct_load 1
#endif

#ifdef __cplusplus
}
#endif

#endif /* __GLDMP_H_ */

