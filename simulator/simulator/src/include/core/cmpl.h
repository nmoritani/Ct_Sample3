/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  cmpl.h
 * @brief %jp{�R���p�C������w�b�_�t�@�C��}%en{uITRON4.0 kernel type header file}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__core__cmpl_h__
#define _KERNEL__core__cmpl_h__

#if !defined(__STDC_VERSION__)
#define __STDC_VERSION__	0
#endif

#if __STDC_VERSION__ >= 199901L && !defined(SDCC)

/* C99(ISO/IEC 9899:1999) */
#define _KERNEL_CMPL_STDINT_H			TRUE						/**< %jp{stdint.h�͗��p�\���H} */

#elif defined(__GNUC__) && !defined(__STRICT_ANSI__)

/* gcc */
#if defined(__LONG_LONG_MAX__)

#define _KERNEL_CMPL_STDINT_H			FALSE						/**< %jp{stdint.h�͗��p�\���H} */
#define _KERNEL_CMPL_64BIT				TRUE						/**< %jp{64�r�b�g�����͗��p�\���H} */
#define _KERNEL_CMPL_INT64				long long					/**< %jp{�����t��64�r�b�g�����̐錾��} */
#define _KERNEL_CMPL_UINT64				unsigned long long			/**< %jp{��������64�r�b�g�����̐錾��} */
#define _KERNEL_CMPL_CONSTNAT_INT64(x)	(x ## LL)					/**< %jp{�����t��64�r�b�g�����̒萔����} */
#define _KERNEL_CMPL_CONSTNAT_UINT64(x)	(x ## ULL)					/**< %jp{��������64�r�b�g�����̒萔����} */
#define _KERNEL_CMPL_TMIN_INT64			(-__LONG_LONG_MAX__-1)		/**< %jp{�����t��64�r�b�g�����̍ŏ��l} */
#define _KERNEL_CMPL_TMAX_INT64			__LONG_LONG_MAX__ 			/**< %jp{�����t��64�r�b�g�����̍ő�l} */
#define _KERNEL_CMPL_TMIN_UINT64		(0ULL)						/**< %jp{��������64�r�b�g�����̍ŏ��l} */
#define _KERNEL_CMPL_TMAX_UINT64		(__LONG_LONG_MAX__*2ULL+1)	/**< %jp{��������64�r�b�g�����̍ő�l} */
#define _KERNEL_CMPL_PTR_SIZE			32							/**< %jp{�|�C���^�T�C�Y���`���邩�H} */

#endif

#elif defined(_MSC_VER)

/* Visual-C++ */
#define _KERNEL_CMPL_STDINT_H			FALSE						/**< %jp{stdint.h�͗��p�\���H} */

#define _KERNEL_CMPL_64BIT				TRUE						/**< %jp{64�r�b�g�����͗��p�\���H} */
#define _KERNEL_CMPL_INT64				signed __int64				/**< %jp{�����t��64�r�b�g�����̐錾��} */
#define _KERNEL_CMPL_UINT64				unsigned __int64			/**< %jp{��������64�r�b�g�����̐錾��} */
#define _KERNEL_CMPL_CONSTNAT_INT64(x)	(x)							/**< %jp{�����t��64�r�b�g�����̒萔����} */
#define _KERNEL_CMPL_CONSTNAT_UINT64(x)	(x)							/**< %jp{��������64�r�b�g�����̒萔����} */
#define _KERNEL_CMPL_TMIN_INT64			(-9223372036854775808)		/**< %jp{�����t��64�r�b�g�����̍ŏ��l} */
#define _KERNEL_CMPL_TMAX_INT64			9223372036854775807			/**< %jp{�����t��64�r�b�g�����̍ő�l} */
#define _KERNEL_CMPL_TMIN_UINT64		0							/**< %jp{��������64�r�b�g�����̍ŏ��l} */
#define _KERNEL_CMPL_TMAX_UINT64		18446744073709551615		/**< %jp{��������64�r�b�g�����̍ő�l} */
#define _KERNEL_CMPL_PTR_SIZE			32							/**< %jp{�|�C���^�T�C�Y���`���邩�H} */


#elif defined(__ARMCC_VERSION) && !defined(__STRICT_ANSI__)

/* armcc */
#define _KERNEL_CMPL_STDINT_H			TRUE						/**< %jp{stdint.h�͗��p�\���H} */

#else

/* ANSI-C (ISO/IEC 9899:1990) standard compiler */
#define _KERNEL_CMPL_STDINT_H			FALSE						/**< %jp{stdint.h�͗��p�\���H} */
#define _KERNEL_CMPL_64BIT				FALSE						/**< %jp{64�r�b�g�����͗��p�\���H} */

#endif


#endif	/* _KERNEL__core__cmpl_h__ */


/* end of file */
