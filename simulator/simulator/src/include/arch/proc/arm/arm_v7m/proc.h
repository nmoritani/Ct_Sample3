/**
 *  Hyper Operating System V4 Advance
 *
 * @file  proc.h
 * @brief %jp{ARMv7-M}%en{ARMv7-M}
 *
 * Copyright (C) 1998-2011 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__proc__arm__arm_v7m__proc_h__
#define _KERNEL__arch__proc__arm__arm_v7m__proc_h__

#define _KERNEL_REG_INT_CONTROL			((volatile UW *)0xE000ED04)		/**< %jp{���荞�ݐ����ԃ��W�X�^}%en{Interrupt Control State Register} */

#define _KERNEL_REG_INT_SETENA_BASE		((volatile UW *)0xE000E100)		/**< %jp{���荞�݃C�l�[�u���Z�b�g���W�X�^} */
#define _KERNEL_REG_INT_CLRENA_BASE		((volatile UW *)0xE000E180)		/**< %jp{���荞�݃C�l�[�u���N���A���W�X�^} */
#define _KERNEL_REG_INT_SETPEND_BASE	((volatile UW *)0xE000E200)		/**< %jp{���荞�ݕۗ��Z�b�g���W�X�^} */
#define _KERNEL_REG_INT_CLRPEND_BASE	((volatile UW *)0xE000E280)		/**< %jp{���荞�ݕۗ��N���A���W�X�^} */


/** %jp{�R���e�L�X�g����u���b�N} */
typedef struct _kernel_t_ctxcb
{
	VP	sp;
} _KERNEL_T_CTXCB;



#ifdef __cplusplus
extern "C" {
#endif

void    _kernel_reset_handler(void);
void    _kernel_nmi_handler(void);
void    _kernel_hw_fault_handler(void);
void    _kernel_pendsv_handler(void);

int     _kernel_ref_cpu_control(void);																/**< %jp{CONTROL���W�X�^�̎擾} */


void    _kernel_ena_int(void);																		/**< %jp{�����݋���} */
void    _kernel_dis_int(void);																		/**< %jp{�����݋֎~} */
void    _kernel_wai_int(void);																		/**< %jp{�����ݑ҂�(�A�C�h�����̏���)} */

void    _kernel_cre_ctx(_KERNEL_T_CTXCB *pk_ctxcb, VP isp, FP entry, VP_INT par1, VP_INT par2);		/**< %jp{���s�R���e�L�X�g�̍쐬} */
void    _kernel_rst_ctx(VP_INT par1, VP_INT par2, FP entry, VP isp);								/**< %jp{���s�R���e�L�X�g�̃��X�^�[�g} */
void    _kernel_sta_ctx(_KERNEL_T_CTXCB *pk_ctxcb);													/**< %jp{���s�R���e�L�X�g�̊J�n} */
void    _kernel_swi_ctx(_KERNEL_T_CTXCB *pk_ctxinf_nxt, _KERNEL_T_CTXCB *pk_ctxcb_now);				/**< %jp{���s�R���e�L�X�g�̐ؑ�} */

#ifdef __cplusplus
}
#endif



#define _KERNEL_INI_PRC()			do {} while (0)													/**< %jp{�v���Z�b�T�ŗL�̏�����} */

#define _KERNEL_INI_INT(stksz, stk)	do {} while (0)													/**< %jp{�����ݏ�����} */
#define _KERNEL_ENA_INT()			_kernel_ena_int()												/**< %jp{�����݋���} */
#define _KERNEL_DIS_INT()			_kernel_dis_int()												/**< %jp{�����݋֎~} */
#define _KERNEL_WAI_INT()			_kernel_wai_int()												/**< %jp{�����ݑ҂�(�A�C�h�����̏���)} */

#define _KERNEL_CRE_CTX(pk_ctxcb, stksz, stk, isp, entry, exinf1, exinf2)		\
									_kernel_cre_ctx((pk_ctxcb), (isp), (entry), (exinf1), (exinf2))	/**< %jp{���s�R���e�L�X�g�̍쐬} */
#define _KERNEL_DEL_CTX(pk_ctxcb)	do {} while (0)													/**< %jp{���s�R���e�L�X�g�̍폜} */
#define _KERNEL_RST_CTX(pk_ctxcb, stksz, stk, isp, entry, exinf1, exinf2)		\
									_kernel_rst_ctx((exinf1), (exinf2), (entry), (isp))				/**< %jp{���s�R���e�L�X�g�̃��X�^�[�g} */
#define _KERNEL_STA_CTX(pk_ctxcb)	_kernel_sta_ctx(pk_ctxcb)
#define _KERNEL_SWI_CTX(pk_ctxcb_now, pk_ctxinf_nxt)							\
									_kernel_swi_ctx((pk_ctxinf_nxt), (pk_ctxcb_now))				/**< %jp{���s�R���e�L�X�g�̐ؑ�} */


#define	_KERNEL_PROC_SET_CTX()		do { } while (0)
#define	_KERNEL_PROC_CLR_CTX()		do { } while (0)
#define	_KERNEL_PROC_SNS_CTX()		((_kernel_ref_cpu_control() & 0x00000002) == 0)

#define	_KERNEL_PROC_SET_DLY()		do { *_KERNEL_REG_INT_CONTROL |= 0x10000000; } while (0)
#define	_KERNEL_PROC_CLR_DLY()		do { *_KERNEL_REG_INT_CONTROL |= 0x08000000; } while (0)
#define	_KERNEL_PROC_SNS_DLY()		((*_KERNEL_REG_INT_CONTROL & 0x10000000) != 0)


#endif	/* _KERNEL__arch__proc__arm__arm_v7m__proc_h__ */



/* end of file */
