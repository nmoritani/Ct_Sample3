/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  procatr.h
 * @brief %jp{�v���Z�b�T�A�[�L�e�N�`���ŗL�@�\(XILINX MicroBlaze)}
 *
 * Copyright (C) 1998-2011 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__proc__mb__mb__proc_h__
#define _KERNEL__arch__proc__mb__mb__proc_h__


/** %jp{�R���e�L�X�g���ۑ��u���b�N}%en{Execution context control block} */
typedef struct _kernel_t_ctxcb
{
	VP_INT  sp;
} _KERNEL_T_CTXCB;

/** %jp{�����݃R���e�L�X�g����u���b�N} */
typedef struct _kernel_t_ictxcb
{
	VP	isp;
} _KERNEL_T_ICTXCB;


extern _KERNEL_T_ICTXCB _kernel_ictxcb;		/**< %jp{�����݃R���e�L�X�g����u���b�N} */


#ifdef __cplusplus
extern "C" {
#endif

void    _kernel_ena_int(void);																		/**< %jp{�����݋���}%en{Enable interrupt} */
void    _kernel_dis_int(void);																		/**< %jp{�����݋֎~}%en{Disable interrupt} */
void    _kernel_wai_int(void);																		/**< %jp{�����ݑ҂�(�A�C�h�����̏���)}%en{Wait for interrupt(sleep)} */
                                                                                                    
void    _kernel_cre_ctx(_KERNEL_T_CTXCB *pk_ctxcb, VP isp, FP entry, VP_INT par1, VP_INT par2);		/**< %jp{���s�R���e�L�X�g�̍쐬}%en{Create execution context)} */
void    _kernel_sta_ctx(_KERNEL_T_CTXCB *pk_ctxcb);													/**< %jp{���s�R���e�L�X�g�̊J�n}%en{Stert context)} */
void    _kernel_rst_ctx(VP_INT par1, VP_INT par2, VP isp, FP entry);								/**< %jp{���s�R���e�L�X�g�̃��X�^�[�g}%en{Restert context)} */
void    _kernel_swi_ctx(_KERNEL_T_CTXCB *pk_ctxcb_nxt, _KERNEL_T_CTXCB *pk_ctxcb_now);				/**< %jp{���s�R���e�L�X�g�̐ؑ�}%en{Switch context)} */


#ifdef __cplusplus
}
#endif



#define _KERNEL_INI_PRC()	do{}while(0)															/**< %jp{�v���Z�b�T�̏�����}%en{Initialize processor} */

#define _KERNEL_INI_INT(stksz, stk)	do { _kernel_ictxcb.isp = (VB *)(stk) + (stksz); } while (0)
#define _KERNEL_ENA_INT()			_kernel_ena_int()												/**< %jp{�����݋���}%en{Enable interrupt} */
#define _KERNEL_DIS_INT()			_kernel_dis_int()												/**< %jp{�����݋֎~}%en{Disable interrupt} */
#define _KERNEL_WAI_INT()			_kernel_wai_int()												/**< %jp{�����ݑ҂�(�A�C�h�����̏���)}%en{Wait for interrupt(sleep)} */

#define _KERNEL_CRE_CTX(pk_ctxcb, stksz, stk, isp, entry, par1, par2)		\
									_kernel_cre_ctx((pk_ctxcb), (isp), (entry), (par1), (par2))		/**< %jp{���s�R���e�L�X�g����}%en{Create execution context)} */
#define _KERNEL_DEL_CTX(pk_ctxcb)	_kernel_del_ctx(pk_ctxcb)
#define _KERNEL_RST_CTX(pk_ctxcb, stksz, stk, isp, entry, par1, par2)		\
									_kernel_rst_ctx((par1), (par2), (isp), (entry))					/**< %jp{���s�R���e�L�X�g���X�^�[�g}%en{Restert context)} */
#define _KERNEL_STA_CTX(pk_ctxcb)	_kernel_sta_ctx(pk_ctxcb)
#define _KERNEL_SWI_CTX(pk_ctxcb_now, pk_ctxcb_nxt)							\
									_kernel_swi_ctx((pk_ctxcb_nxt), (pk_ctxcb_now))					/**< %jp{�R���e�L�X�g�̃X�C�b�`}%en{Switch context)} */




#endif	/* _KERNEL__arch__proc__mb__mb__proc_h__ */



/* end of file */
