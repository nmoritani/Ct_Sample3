/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  irc.h
 * @brief %jp{Analog Devices ADuC7000�V���[�Y�p�����݃R���g���[������}%en{Analog Devices ADuC7000 series}
 *
 * Copyright (C) 1998-2007 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__irc__aduc7000__irc_h__
#define _KERNEL__arch__irc__aduc7000__irc_h__


/* %jp{�������}�b�v�h���W�X�^��`} */
#define _KERNEL_IRC_IRQSTA		((volatile UW *)0xffff0000)
#define _KERNEL_IRC_IRQSIG		((volatile UW *)0xffff0004)
#define _KERNEL_IRC_IRQEN		((volatile UW *)0xffff0008)
#define _KERNEL_IRC_IRQCLR		((volatile UW *)0xffff000c)

#define _KERNEL_IRC_FIQSTA		((volatile UW *)0xffff0100)
#define _KERNEL_IRC_FIQSIG		((volatile UW *)0xffff0104)
#define _KERNEL_IRC_FIQEN		((volatile UW *)0xffff0108)
#define _KERNEL_IRC_FIQCLR		((volatile UW *)0xffff010c)


#ifdef __cplusplus
extern "C" {
#endif

void _kernel_ini_irc(void);			/**< %jp{�����݃R���g���[���̏�����} */
void _kernel_exe_irc(INHNO inhno);	/**< %jp{�����ݏ���} */

#ifdef __cplusplus
}
#endif


#define _KERNEL_INI_IRC()		_kernel_ini_irc()		/**< %jp{�����݃R���g���[���̏�����} */
#define _KERNEL_EXE_IRC(inhno)	_kernel_exe_irc(inhno)	/**< %jp{�����ݏ���} */


#endif	/* _KERNEL__arch__irc__aduc7000__irc_h__ */


/* end of file */

