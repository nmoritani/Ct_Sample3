/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  irc.h
 * @brief XILINX AXI INTC
 *
 * Copyright (C) 1998-2011 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__irc__xilinx_axi_intc__irc_h__
#define _KERNEL__arch__irc__xilinx_axi_intc__irc_h__


/* %jp{�������}�b�v�h���W�X�^��`} */
#define _KERNEL_IRC_ISR					((volatile UW *)_kernel_irc_reg_base + 0)
#define _KERNEL_IRC_IPR					((volatile UW *)_kernel_irc_reg_base + 1)
#define _KERNEL_IRC_IER					((volatile UW *)_kernel_irc_reg_base + 2)
#define _KERNEL_IRC_IAR					((volatile UW *)_kernel_irc_reg_base + 3)
#define _KERNEL_IRC_SIE					((volatile UW *)_kernel_irc_reg_base + 4)
#define _KERNEL_IRC_CIE					((volatile UW *)_kernel_irc_reg_base + 5)
#define _KERNEL_IRC_IVR					((volatile UW *)_kernel_irc_reg_base + 6)
#define _KERNEL_IRC_MER					((volatile UW *)_kernel_irc_reg_base + 7)


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


#endif	/* _KERNEL__arch__irc__xilinx_axi_intc__irc_h__ */


/* end of file */

