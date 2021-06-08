/*
  Copyright (c) 2011-2013, Digital Media Professionals. All rights reserved.
*/
#ifndef _EGLDMP_H
#define _EGLDMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <EGL/egl.h>
#include <EGL/eglext.h>

#ifndef EGL_API_ENTRYP
#	define EGL_API_ENTRYP EGL_API_ENTRY*
#endif

#ifndef EGL_EGLDMP_PROTOTYPES
#	define EGL_EGLDMP_PROTOTYPES
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

/*
###############################################################################

# DMP: 0x3FA0-0x3FFF

# DMP_future_use: 
#               : 0x3FAB-0x3FAF,
#               : 0x3FD7,
#               : 0x3FE8-0x3FEF

###############################################################################
*/

/* Header file version number */
#define EGL_EGLDMP_VERSION	3


/*
###############################################################################

# #001 EGL_DMP_limit_resource
#      0x3FF0-0x3FF1

###############################################################################
*/
#ifndef EGL_DMP_limit_resource
#define EGL_DMP_limit_resource 1

#define EGL_VG_MAX_TOTAL_COORDS_DMP			0x3FF0
#define EGL_VG_MAX_TOTAL_IMAGE_SIZE_DMP		0x3FF1

#ifndef EGL_UNLIMIT_DMP
#	define EGL_UNLIMIT_DMP					0x7FFFFFFF
#endif /* EGL_UNLIMIT_DMP */

#ifdef EGL_EGLDMP_PROTOTYPES
#endif

#endif /* EGL_DMP_limit_resource */

/*
###############################################################################

# #002
# Reserved 0x3FF2-0x3FF4

###############################################################################
*/

/*
###############################################################################

# #003 EGL_DMP_display_query

###############################################################################
*/
#ifndef EGL_DMP_display_query
#define EGL_DMP_display_query 1

#ifdef EGL_EGLDMP_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglQueryDisplayDMP(EGLDisplay dpy, EGLint attribute, EGLint *value);
#endif
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYDISPLAYDMPPROC) (EGLDisplay dpy, EGLint attribute, EGLint *value);

#endif /* EGL_DMP_display_query */

/*
###############################################################################

# #004 EGL_DMP_context_priority
#      0x3FF5

###############################################################################
*/
#ifndef EGL_DMP_context_priority
#define EGL_DMP_context_priority 1

#define EGL_CONTEXT_PRIORITY_LEVEL_DMP		0x3100
#define EGL_CONTEXT_PRIORITY_HIGH_DMP		0x3101
#define EGL_CONTEXT_PRIORITY_MEDIUM_DMP		0x3102
#define EGL_CONTEXT_PRIORITY_LOW_DMP		0x3103

#define EGL_CONTEXT_PRIORITY_VALUES_DMP		0x3FF5

#ifdef EGL_EGLDMP_PROTOTYPES
#endif

#endif /* EGL_DMP_context_priority */

/*
###############################################################################

# #005 EGL_DMP_commandbuffer_attributes
#      0x3FCD-0x3FCF, 0x3FD4-0x3FD6, 0x3FF6-0x3FFA, 0x3FFC-0x3FFE

###############################################################################
*/
#ifndef EGL_DMP_commandbuffer_attributes
#define EGL_DMP_commandbuffer_attributes 1

#define EGL_VG_NUM_COMMANDBUFFERS_DMP                       0x3FF6
#define EGL_VG_COMMANDBUFFER_PATH_SIZE_DMP                  0x3FF7
#define EGL_VG_COMMANDBUFFER_FILL_SIZE_DMP                  0x3FF8
#define EGL_VG_COMMANDBUFFER_PATH_FLUSH_SIZE_DMP            0x3FF9
#define EGL_VG_COMMANDBUFFER_FILL_FLUSH_SIZE_DMP            0x3FFA

#define EGL_GL_ES_NUM_COMMANDBUFFERS_DMP                    0x3FFC
#define EGL_GL_ES_COMMANDBUFFER_SIZE_DMP                    0x3FFD
#define EGL_GL_ES_COMMANDBUFFER_FLUSH_SIZE_DMP              0x3FFE

#define EGL_GL_ES_COMMANDBUFFER_CARRIAGE_RETURN_SIZE_DMP	0x3FCD
#define EGL_VG_COMMANDBUFFER_PATH_CARRIAGE_RETURN_SIZE_DMP	0x3FCE
#define EGL_VG_COMMANDBUFFER_FILL_CARRIAGE_RETURN_SIZE_DMP	0x3FCF

#define EGL_VG_MIN_COMMANDBUFFER_PATH_SIZE_DMP				0x3FD4
#define EGL_VG_MIN_COMMANDBUFFER_FILL_SIZE_DMP				0x3FD5
#define EGL_GL_ES_MIN_COMMANDBUFFER_SIZE_DMP				0x3FD6

#ifndef EGL_UNLIMIT_DMP
#	define EGL_UNLIMIT_DMP					0x7FFFFFFF
#endif /* EGL_UNLIMIT_DMP */

#ifdef EGL_EGLDMP_PROTOTYPES
#endif

#endif /* EGL_DMP_commandbuffer_attributes */

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

# #008 EGL_DMP_image_invalidate

###############################################################################
*/
#ifndef EGL_DMP_image_invalidate
#define EGL_DMP_image_invalidate 1

#ifdef EGL_EGLDMP_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglInvalidateImageDMP(EGLDisplay dpy, EGLImageKHR image);
#endif
typedef EGLBoolean (EGLAPIENTRYP PFNEGLINVALIDATEIMAGEDMPPROC) (EGLDisplay dpy, EGLImageKHR image);

#endif /* EGL_DMP_image_invalidate */

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

# #011 EGL_DMP_resume

###############################################################################
*/
#ifndef EGL_DMP_resume
#define EGL_DMP_resume 1

#ifdef EGL_EGLDMP_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSuspendDMP(void);
EGLAPI EGLBoolean EGLAPIENTRY eglResumeDMP(void);
#endif
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSUSPENDDMPPROC) (void);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLRESUMEDMPPROC) (void);

#endif /* EGL_DMP_resume */

/*
###############################################################################

# #012 EGL_DMP_hw_state

###############################################################################
*/
#ifndef EGL_DMP_hw_state
#define EGL_DMP_hw_state 1

#ifdef EGL_EGLDMP_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglSetHardwareStateDMP(EGLenum pname, EGLint param);
#endif
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSETHARDWARESTATEDMPPROC) (EGLenum pname, EGLint param);

#endif /* EGL_DMP_hw_state */

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

# #016 EGL_DMP_colorbuffer_format_attribute
#      0x3FDD-0x3FDF

###############################################################################
*/
#ifndef EGL_DMP_colorbuffer_format_attribute
#define EGL_DMP_colorbuffer_format_attribute 1

#define EGL_BUFFER_FORMAT_STANDARD_BIT_DMP			0x100000
#define EGL_BUFFER_FORMAT_NATIVE_BIT_DMP			0x200000

#define EGL_COLOR_BUFFER_FORMAT_DMP					0x3FDD

#define EGL_COLOR_BUFFER_FORMAT_STANDARD_DMP		0x3FDE
#define EGL_COLOR_BUFFER_FORMAT_NATIVE_DMP			0x3FDF

#endif /* EGL_DMP_colorbuffer_format_attribute */

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

# #019 EGL_DMP_YUV_semiplanar_buffer
#      0x3FB0-0x3FB1

###############################################################################
*/
#ifndef EGL_DMP_YUV_semiplanar_buffer
#define EGL_DMP_YUV_semiplanar_buffer 1

#define EGL_YUV422_SEMIPLANAR_BUFFER_DMP			0x3FB0
#define EGL_YUV420_SEMIPLANAR_BUFFER_DMP			0x3FB1

#endif /* EGL_DMP_YUV_semiplanar_buffer */

/*
###############################################################################

# #020
# Reserved 0x3FA0-0x3FAA, 0x3FB2-0x3FCC

###############################################################################
*/

/*
###############################################################################

# #021
# Reserved 0x3FFF

###############################################################################
*/


#ifdef __cplusplus
} /* extern "C" */
#endif

#include <DMP/eglDMPX.h>

#endif /* _EGLDMP_H */
