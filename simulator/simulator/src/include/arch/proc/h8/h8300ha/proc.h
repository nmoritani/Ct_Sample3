/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  ctxctl.h
 * @brief %jp{�R���e�L�X�g����}%en{context control}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__proc__h8__h8300ha__proc_h__
#define _KERNEL__arch__proc__h8__h8300ha__proc_h__


#define _KERNEL_IMSK_I		0x80		/**< %jp{�����݃}�X�N�r�b�g} */
#define _KERNEL_IMSK_UI		0x40		/**< %jp{���[�U�[�r�b�g�^�����݃}�X�N�r�b�g} */

#define _KERNEL_IMSK_LV0	0xc0		/**< %jp{�����݃}�X�N���x��0(���ׂă}�X�N)} */
#define _KERNEL_IMSK_LV1	0x80		/**< %jp{�����݃}�X�N���x��1(���D�抄���݂̂݋���)} */
#define _KERNEL_IMSK_LV2	0x00		/**< %jp{�����݃}�X�N���x��2(���ׂċ���)} */


/** %jp{�R���e�L�X�g���ۑ��u���b�N} */
typedef struct _kernel_t_ctxcb
{
	VP	sp;								/**< %jp{�X�^�b�N�|�C���^}%en{Stack pointer} */
} _KERNEL_T_CTXCB;


/** %jp{�����݃R���e�L�X�g���ۑ��u���b�N} */
typedef struct _kernel_t_ictxcb
{
	UB	imsk;							/**< %jp{�����݃}�X�N}%en{Interrupt mask} */
	UB	intcnt;							/**< %jp{�����݃l�X�g�J�E���^}%en{Interrupt nest counter} */
	VP	isp;							/**< %jp{�����ݏ����X�^�b�N�|�C���^}%en{Initial stack pointer for interrupt} */
} _KERNEL_T_ICTXCB;



/* %jp{�L��ϐ���`} */
extern _KERNEL_T_ICTXCB _kernel_ictxcb;	/**< %jp{�����݃R���e�L�X�g���ۑ��u���b�N} */


#ifdef __cplusplus
extern "C" {
#endif

void    _kernel_ena_int(void);																		/**< %jp{�����݋���} */
void    _kernel_dis_int(void);																		/**< %jp{�����݋֎~} */
void    _kernel_wai_int(void);																		/**< %jp{�����ݑ҂�(�A�C�h�����̏���)} */

void    _kernel_cre_ctx(_KERNEL_T_CTXCB *pk_ctxcb, VP isp, FP entry, VP_INT par1, VP_INT par2);		/**< %jp{���s�R���e�L�X�g�̍쐬} */
void    _kernel_del_ctx(_KERNEL_T_CTXCB *pk_ctxcb);													/**< %jp{���s�R���e�L�X�g�̍폜} */
void    _kernel_rst_ctx(VP_INT par1, VP_INT par2, FP entry, VP isp);								/**< %jp{���s�R���e�L�X�g�̃��X�^�[�g} */
void    _kernel_sta_ctx(_KERNEL_T_CTXCB *pk_ctxcb);													/**< %jp{���s�R���e�L�X�g�̊J�n} */
void    _kernel_swi_ctx(_KERNEL_T_CTXCB *pk_ctxinf_nxt, _KERNEL_T_CTXCB *pk_ctxcb_now);				/**< %jp{���s�R���e�L�X�g�̐ؑ�} */

#ifdef __cplusplus
}
#endif


#define _KERNEL_INI_PRC()	do {} while (0)

#define _KERNEL_INI_INT(stksz, stk)	do { _kernel_ictxcb.isp = (VB *)(stk) + (stksz); } while (0)
#define _KERNEL_ENA_INT()			_kernel_ena_int()												/**< %jp{�����݋���} */
#define _KERNEL_DIS_INT()			_kernel_dis_int()												/**< %jp{�����݋֎~} */
#define _KERNEL_WAI_INT()			_kernel_wai_int()												/**< %jp{�����ݑ҂�(�A�C�h�����̏���)} */

#define _KERNEL_CRE_CTX(pk_ctxcb, stksz, stk, isp, entry, exinf1, exinf2)		\
									_kernel_cre_ctx((pk_ctxcb), (isp), (entry), (exinf1), (exinf2))
#define _KERNEL_DEL_CTX(pk_ctxcb)	_kernel_del_ctx(pk_ctxcb)
#define _KERNEL_RST_CTX(pk_ctxcb, stksz, stk, isp, entry, exinf1, exinf2)		\
									_kernel_rst_ctx((exinf1), (exinf2), (entry), (isp))
#define _KERNEL_STA_CTX(pk_ctxcb)	_kernel_sta_ctx(pk_ctxcb)
#define _KERNEL_SWI_CTX(pk_ctxcb_now, pk_ctxinf_nxt)							\
									_kernel_swi_ctx((pk_ctxinf_nxt), (pk_ctxcb_now))


#endif	/* _KERNEL__arch__proc__h8__h8300ha__proc_h__ */


/* end of file */