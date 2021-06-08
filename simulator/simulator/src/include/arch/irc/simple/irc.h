/**
 *  Hyper Operating System V4 Advance
 *
 * @file  irc.h
 * @brief %jp{�����݃R���g���[���ŗL������`}%jp{Interrupt controler attribute}
 *  %jp{�����݃n���h���Ɗ����݃T�[�r�X���[�`�����P���Ή�����ꍇ}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__irc_none_h__
#define _KERNEL__arch__irc_none_h__


#ifdef __cplusplus
extern "C" {
#endif

void _kernel_exe_isr(INTNO intno);

#ifdef __cplusplus
}
#endif


#define _KERNEL_INI_IRC()			do {} while (0)						/**< %jp{IRC�̏������n���h��} */
#define _KERNEL_EXE_IRC(inhno)		_kernel_exe_isr((INTNO)(inhno))		/**< %jp{IRC�̏������[�`��} */


#endif	/* _KERNEL__arch__irc_none_h__ */


/* end of file */
