/*
  Copyright (c) 2011, Digital Media Professionals. All rights reserved.
*/
#ifndef __OSW_MATH_H__
#define __OSW_MATH_H__

#include <oswrapper/oswplatform.h>

#ifdef _MSC_VER
#   define _USE_MATH_DEFINES
#endif

#include <math.h>

#ifndef M_PI
#   define M_PI 3.14159265358979323846f
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSWSTDCAPIENTRY
#	define OSWSTDCAPIENTRY
#endif
#ifndef OSWSTDCAPIENTRYP
#	define OSWSTDCAPIENTRYP OSWSTDCAPIENTRY *
#endif


typedef double (OSWSTDCAPIENTRYP PFNOSWACOSPROC) (double x);
typedef double (OSWSTDCAPIENTRYP PFNOSWATAN2PROC) (double x, double y);
typedef double (OSWSTDCAPIENTRYP PFNOSWCOSPROC) (double x);
typedef double (OSWSTDCAPIENTRYP PFNOSWSINPROC) (double x);
typedef double (OSWSTDCAPIENTRYP PFNOSWTANPROC) (double x);
typedef double (OSWSTDCAPIENTRYP PFNOSWEXPPROC) (double x);
typedef double (OSWSTDCAPIENTRYP PFNOSWLOGPROC) (double x);
typedef double (OSWSTDCAPIENTRYP PFNOSWPOWPROC) (double x, double y);
typedef double (OSWSTDCAPIENTRYP PFNOSWSQRTPROC) (double x);
typedef double (OSWSTDCAPIENTRYP PFNOSWCEILPROC) (double x);
typedef double (OSWSTDCAPIENTRYP PFNOSWFLOORPROC) (double x);

typedef float (OSWSTDCAPIENTRYP PFNOSWACOSFPROC) (float x);
typedef float (OSWSTDCAPIENTRYP PFNOSWEXPFPROC) (float x);
typedef float (OSWSTDCAPIENTRYP PFNOSWLOGFPROC) (float x);
typedef float (OSWSTDCAPIENTRYP PFNOSWFABSFPROC) (float x);
typedef float (OSWSTDCAPIENTRYP PFNOSWPOWFPROC) (float x, float y);
typedef float (OSWSTDCAPIENTRYP PFNOSWSQRTFPROC) (float x);
typedef float (OSWSTDCAPIENTRYP PFNOSWCEILFPROC) (float x);
typedef float (OSWSTDCAPIENTRYP PFNOSWFLOORFPROC) (float x);


/* OSW_ACOS: Arc cosine function. */
/* OSW_ASIN: Arc sine function. */
/* OSW_ATAN: Arc tangent function. */
/* OSW_ATAN2: Arc tangent function. */
/* OSW_COS: Cosine function. */
/* OSW_SIN: Sine function. */
/* OSW_TAN: Tangent function. */
/* OSW_EXP: Exponential function. */
/* OSW_LOG: Natural logarithm function. */
/* OSW_FABS: Absolute value. */
/* OSW_POW: Power function. */
/* OSW_SQRT: Square root function. */
/* OSW_CEIL: Return ceiling value. */
/* OSW_FLOOR: Return floor value. */
/* OSW_ROUND: Round value to nearest integer. */
/* OSW_INVSQRT: Inverse square root function. */
/* OSW_FMOD: Calculate floating point remainder. */

extern OSW_API PFNOSWACOSPROC		OSW_acos;
extern OSW_API PFNOSWATAN2PROC		OSW_atan2;
extern OSW_API PFNOSWCOSPROC		OSW_cos;
extern OSW_API PFNOSWSINPROC		OSW_sin;
extern OSW_API PFNOSWTANPROC		OSW_tan;
extern OSW_API PFNOSWEXPPROC		OSW_exp;
extern OSW_API PFNOSWLOGPROC		OSW_log;
extern OSW_API PFNOSWPOWPROC		OSW_pow;
extern OSW_API PFNOSWSQRTPROC		OSW_sqrt;
extern OSW_API PFNOSWCEILPROC		OSW_ceil;
extern OSW_API PFNOSWFLOORPROC		OSW_floor;

/* OSW_ACOSF: Arc cosine function. */
/* OSW_ASINF: Arc sine function. */
/* OSW_ATANF: Arc tangent function. */
/* OSW_ATAN2F: Arc tangent function. */
/* OSW_COSF: Cosine function. */
/* OSW_SINF: Sine function. */
/* OSW_TANF: Tangent function. */
/* OSW_EXPF: Exponential function. */
/* OSW_LOGF: Natural logarithm function. */
/* OSW_FABSF: Absolute value. */
/* OSW_POWF: Power function. */
/* OSW_SQRTF: Square root function. */
/* OSW_CEILF: Return ceiling value. */
/* OSW_FLOORF: Return floor value. */
/* OSW_ROUNDF: Round value to nearest integer. */
/* OSW_INVSQRTF: Inverse square root function. */
/* OSW_FMODF: Calculate floating point remainder. */

extern OSW_API PFNOSWACOSFPROC		OSW_acosf;
extern OSW_API PFNOSWEXPFPROC		OSW_expf;
extern OSW_API PFNOSWLOGFPROC		OSW_logf;
extern OSW_API PFNOSWFABSFPROC		OSW_fabsf;
extern OSW_API PFNOSWPOWFPROC		OSW_powf;
extern OSW_API PFNOSWSQRTFPROC		OSW_sqrtf;
extern OSW_API PFNOSWCEILFPROC		OSW_ceilf;
extern OSW_API PFNOSWFLOORFPROC	OSW_floorf;


#ifdef USE_STDC_LIB

#	define	OSW_ACOS		acos
#	define	OSW_ATAN2		atan2
#	define	OSW_COS			cos
#	define	OSW_SIN			sin
#	define	OSW_TAN			tan
#	define	OSW_EXP			exp
#	define	OSW_LOG			log
#	define	OSW_POW			pow
#	define	OSW_SQRT		sqrt
#	define	OSW_CEIL		ceil
#	define	OSW_FLOOR		floor

//#	define	OSW_ACOSF		acosf
#	define	OSW_ACOSF		OSW_acosf
//#	define	OSW_EXPF		expf
#	define	OSW_EXPF		OSW_expf
#	define	OSW_LOGF		logf
//#	define	OSW_FABSF		fabsf
#	define	OSW_FABSF		OSW_fabsf
//#	define	OSW_POWF		powf
#	define	OSW_POWF		OSW_powf
//#	define	OSW_SQRTF		sqrtf
#	define	OSW_SQRTF		OSW_sqrtf
#	define	OSW_CEILF		ceilf
#	define	OSW_FLOORF		floorf

#else /* USE_STDC_LIB */

#	define	OSW_ACOS		OSW_acos
#	define	OSW_ATAN2		OSW_atan2
#	define	OSW_COS			OSW_cos
#	define	OSW_SIN			OSW_sin
#	define	OSW_TAN			OSW_tan
#	define	OSW_EXP			OSW_exp
#	define	OSW_LOG			OSW_log
#	define	OSW_POW			OSW_pow
#	define	OSW_SQRT		OSW_sqrt
#	define	OSW_CEIL		OSW_ceil
#	define	OSW_FLOOR		OSW_floor

#	define	OSW_ACOSF		OSW_acosf
#	define	OSW_EXPF		OSW_expf
#	define	OSW_LOGF		OSW_logf
#	define	OSW_FABSF		OSW_fabsf
#	define	OSW_POWF		OSW_powf
#	define	OSW_SQRTF		OSW_sqrtf
#	define	OSW_CEILF		OSW_ceilf
#	define	OSW_FLOORF		OSW_floorf

#endif /* USE_STDC_LIB */


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __OSW_MATH_H__ */
