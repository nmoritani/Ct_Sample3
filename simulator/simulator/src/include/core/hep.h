/**
 *  Hyper Operating System V4 Advance
 *
 * @file  hep.h
 * @brief %jp{�������q�[�v�̃w�b�_�t�@�C��}%en{memory heap heder file}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__core__hep_h_
#define _KERNEL__core__hep_h_


#include "itron.h"


#define _KERNEL_HEP_MEMALIGN		32			/**< %jp{�������A���C�����g} */
#define _KERNEL_HEP_USING			0x1234		/**< %jp{�g�p��} */
#define _KERNEL_HEP_FREE			0xabcd		/**< %jp{���g�p} */



/** %jp{�T�C�Y�A���C�����g} */
#define _KERNEL_HEP_ALIGNED(size)	(((size) + _KERNEL_HEP_MEMALIGN - 1) & ~(_KERNEL_HEP_MEMALIGN - 1))


/** %jp{�q�[�v�������u���b�N} */
typedef struct _kernel_t_hepblk
{
	struct _kernel_t_hepblk* prev;	/**< %jp{�O�̃u���b�N} */
	SIZE   size;					/**< %jp{�u���b�N�̃T�C�Y} */
	INT    flag;					/**< %jp{�g�p���t���O} */
} _KERNEL_T_HEPBLK;


/** %jp{�q�[�v����u���b�N} */
typedef struct _kernel_t_hepcb
{
	_KERNEL_T_HEPBLK *base;			/**< %jp{�J�[�l���p�������擪�u���b�N�̃A�h���X} */
	SIZE            heapsz;			/**< %jp{�J�[�l���p�������T�C�Y} */
} _KERNEL_T_HEPCB;


/** %jp{�J�[�l���������Ǘ��u���b�N�T�C�Y} */
#define _KERNEL_HEP_BLKSIZE			_KERNEL_HEP_ALIGNED(sizeof(_KERNEL_T_HEPBLK))


#ifdef __cplusplus
extern "C" {
#endif

void    _kernel_cre_hep(_KERNEL_T_HEPCB *hepcb, SIZE hepsz, VP hep);					/**< %jp{�������q�[�v�𐶐�} */
VP      _kernel_alc_hep(_KERNEL_T_HEPCB *hepcb, SIZE size);								/**< %jp{�������̊��蓖��} */
void    _kernel_fre_hep(_KERNEL_T_HEPCB *hepcb, VP ptr);								/**< %jp{�������̉��} */

#ifdef __cplusplus
}
#endif


#define _KERNEL_CRE_HEP(hepcb, hepsz, hep)	_kernel_cre_hep((hepcb), (hepsz), (hep))	/**< %jp{�������q�[�v�𐶐�} */
#define _KERNEL_DEL_HEP(hepcb)				do {} while(0)								/**< %jp{�������q�[�v���폜} */
#define _KERNEL_ALC_HEP(hepcb, size)		_kernel_alc_hep((hepcb), (size))			/**< %jp{�������̊��蓖��} */
#define _KERNEL_FRE_HEP(hepcb, ptr)			_kernel_fre_hep((hepcb), (ptr))				/**< %jp{�������̉��} */
#define _KERNEL_ALG_HEP(hepcb, size)		_KERNEL_HEP_ALIGNED(size)					/**< %jp{�������T�C�Y�̃A���C�����g�����킹��} */



#endif	/* _KERNEL__core__hep_h_ */


/* end of file */
