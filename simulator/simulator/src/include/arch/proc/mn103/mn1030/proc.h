/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  ctxctl.h
 * @brief %jp{�R���e�L�X�g����}%en{context control}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__proc__mn1030__proc_h__
#define _KERNEL__arch__proc__mn1030__proc_h__



/** %jp{�R���e�L�X�g���ۑ��u���b�N} */
typedef struct _kernel_t_ctxcb
{
	VP_INT  sp;
} _KERNEL_T_CTXCB;


/** %jp{�����݃R���e�L�X�g����u���b�N} */
typedef struct _kernel_t_ictxcb
{
	VP	isp;
	UB	intcnt;
} _KERNEL_T_ICTXCB;


extern _KERNEL_T_ICTXCB _kernel_ictxcb;		/**< %jp{�����݃R���e�L�X�g����u���b�N} */



#ifdef __cplusplus
extern "C" {
#endif

void    _kernel_ini_prc(void);																		/**< %jp{�v���Z�b�T�ŗL�̏�����} */

void    _kernel_ena_int(void);																		/**< %jp{�����݋���} */
void    _kernel_dis_int(void);																		/**< %jp{�����݋֎~} */
void    _kernel_wai_int(void);																		/**< %jp{�����ݑ҂�(�A�C�h�����̏���)} */

void    _kernel_cre_ctx(UW par1, UW par2, _KERNEL_T_CTXCB *pk_ctxcb, VP isp, FP entry);				/**< %jp{���s�R���e�L�X�g�̍쐬} */
void    _kernel_del_ctx(_KERNEL_T_CTXCB *pk_ctxcb);													/**< %jp{���s�R���e�L�X�g�̍폜} */
void    _kernel_rst_ctx(UW par1, UW par2, FP entry, VP isp);										/**< %jp{���s�R���e�L�X�g�̃��X�^�[�g} */
void    _kernel_sta_ctx(_KERNEL_T_CTXCB *pk_ctxcb);													/**< %jp{���s�R���e�L�X�g�̊J�n} */
void    _kernel_swi_ctx(_KERNEL_T_CTXCB *pk_ctxinf_nxt, _KERNEL_T_CTXCB *pk_ctxcb_now);				/**< %jp{���s�R���e�L�X�g�̐ؑ�} */

#ifdef __cplusplus
}
#endif


#define _KERNEL_INI_PRC()			_kernel_ini_prc()												/**< %jp{�v���Z�b�T�ŗL�̏�����} */

#define _KERNEL_INI_INT(stksz, stk)	do { _kernel_ictxcb.isp = (VB *)(stk) + (stksz); } while (0)	/**< %jp{�����ݏ�����} */
#define _KERNEL_ENA_INT()			_kernel_ena_int()												/**< %jp{�����݋���} */
#define _KERNEL_DIS_INT()			_kernel_dis_int()												/**< %jp{�����݋֎~} */
#define _KERNEL_WAI_INT()			_kernel_wai_int()												/**< %jp{�����ݑ҂�(�A�C�h�����̏���)} */

#define _KERNEL_CRE_CTX(pk_ctxcb, stksz, stk, isp, entry, par1, par2)			\
									_kernel_cre_ctx((UW)(par1), (UW)(par2), (pk_ctxcb), (isp), (entry))
#define _KERNEL_DEL_CTX(pk_ctxcb)	_kernel_del_ctx(pk_ctxcb)
#define _KERNEL_RST_CTX(pk_ctxcb, stksz, stk, isp, entry, exinf1, exinf2)		\
									_kernel_rst_ctx((exinf1), (exinf2), (entry), (isp))
#define _KERNEL_STA_CTX(pk_ctxcb)	_kernel_sta_ctx(pk_ctxcb)
#define _KERNEL_SWI_CTX(pk_ctxcb_now, pk_ctxinf_nxt)							\
									_kernel_swi_ctx((pk_ctxinf_nxt), (pk_ctxcb_now))


#endif	/* _KERNEL__arch__proc__arm__arm_v4__proc_h__ */


/* end of file */
