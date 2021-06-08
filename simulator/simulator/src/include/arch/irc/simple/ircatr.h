/**
 *  Hyper Operating System V4 Advance
 *
 * @file  ircatr.h
 * @brief %jp{�����݃R���g���[���ŗL������`}%jp{Interrupt controler attribute}
 *  %jp{�����݃n���h���Ɗ����݃T�[�r�X���[�`�����P���Ή�����ꍇ}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__simple__ircatr_h__
#define _KERNEL__arch__simple__ircatr_h__


#define _KERNEL_IRCATR_INC_PATH		"simple"

#define _KERNEL_IRCATR_IRC			TRUE							/**< %jp{IRC�̗L��} */
#define _KERNEL_IRCATR_REG_BASE		FALSE							/**< %jp{IRC���W�X�^�x�[�X�A�h���X�̗L��} */

#define _KERNEL_IRCATR_TMIN_INTNO	_KERNEL_PROCATR_TMIN_INHNO		/**< %jp{�����݃n���h���ԍ��̍ŏ��l} */
#define _KERNEL_IRCATR_TMAX_INTNO	_KERNEL_PROCATR_TMAX_INHNO		/**< %jp{�����݃n���h���ԍ��̍ő�l} */


#endif	/* _KERNEL__arch__simple__ircatr_h__ */


/* end of file */
