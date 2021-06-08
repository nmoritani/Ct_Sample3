/*------------------------------------------------------------------------------*/
/*	envdep.h																	*/
/*																				*/
/*	Copyright (c) 2011, Digital Media Professionals Inc. All rights reserved.	*/
/*																				*/
/*------------------------------------------------------------------------------*/
#ifndef	ENVDEP_H
#define	ENVDEP_H

/*------------------------------------------*/
/*  Definition of the 64bit integer type    */
/*------------------------------------------*/

/* Microsoft compiler */
#ifdef _MSC_VER
	typedef unsigned __int64		uint64;
	typedef signed   __int64		int64;
/* GNU Compiler */
#elif defined(__GNUC__)
	typedef unsigned long long		uint64;
	typedef signed   long long		int64;
/* Unsupported */
#else
#endif

typedef unsigned int			uint32;
typedef signed   int			int32;
typedef unsigned short			uint16;
typedef signed   short			int16;
typedef unsigned char			uint8;
typedef signed   char			int8;



#endif	/* ENVDEP_H */
