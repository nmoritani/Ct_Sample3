/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  parsknl.h
 * @brief %jp{�J�[�l���R���t�B�M�����[�V�����̉��}%en{kernel configuration parser}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */



#ifndef _KERNEL__parser__parsknl_h__
#define _KERNEL__parser__parsknl_h__


/* ------------------------------------------------------------------ */
/*  Processor Attribute                                               */
/* ------------------------------------------------------------------ */

/* �����ݗp�X�^�b�N�̖{�� */
#ifndef _KERNEL_PROCATR_INTSTK_NUM
#define _KERNE_INTSTK_NUM			1
#else
#define _KERNE_INTSTK_NUM			_KERNEL_PROCATR_INTSTK_NUM
#endif


/* ------------------------------------------------------------------ */
/*  Optimize                                                          */
/* ------------------------------------------------------------------ */

/* %jp{���l�̏��������̂�D�悵�čœK������} */
#define _KERNEL_OPT_RW_SIZE			_KERNEL_CFG_OPT_RW_SIZE		/**< %jp{���[�h���C�g�f�[�^�T�C�Y(�ʏ��RAM�z�u)�̗D��x} */
#define _KERNEL_OPT_RO_SIZE			_KERNEL_CFG_OPT_RO_SIZE		/**< %jp{���[�h�I�����[�f�[�^(�ʏ��ROM�z�u)�̃T�C�Y�̗D��x} */
#define _KERNEL_OPT_CODE_SIZE		_KERNEL_CFG_OPT_CODE_SIZE	/**< %jp{�R�[�h�T�C�Y(�ʏ��ROM�z�u)�̗D��x} */
#define _KERNEL_OPT_SPEED			_KERNEL_CFG_OPT_SPEED		/**< %jp{���s���x�̗D��x} */


/* %jp{�R�[�h�T�C�Y/���x���d�����Ȃ�����A�R���g���[���u���b�N�̓T�C�Y�D��} */
#if (_KERNEL_OPT_RW_SIZE <= _KERNEL_OPT_CODE_SIZE) && (_KERNEL_OPT_RW_SIZE <= _KERNEL_OPT_SPEED)
#define _KERNEL_OPT_CB_SIZE			TRUE
#else
#define _KERNEL_OPT_CB_SIZE			FALSE
#endif

/* %jp{�����t�������ӂȃv���Z�b�T�Ȃ畄���t����D�悵�čœK������} */
#if defined(_KERNEL_PROCATR_SIGNED_INT) && _KERNEL_PROCATR_SIGNED_INT > 0
#define _KERNEL_OPT_SIGNED_INT		TRUE
#else
#define _KERNEL_OPT_SIGNED_INT		FALSE
#endif




/* ------------------------------------------------------------------ */
/*  Kernel                                                            */
/* ------------------------------------------------------------------ */

/* %jp{�x���v���V�[�W���[�R�[��(�����Ɠ���������)} */
#define _KERNEL_SPT_DPC				_KERNEL_CFG_DPC				/**< Deferred Procedure Call */

/* %jp{�Ώ̌^�}���`�v���Z�b�T�Ή�(�����Ɖi���ɖ�����)} */
#define _KERNEL_SPT_SMP				_KERNEL_CFG_SMP				/**< Symmetric Multiple Processor */

/* %jp{���d������} */
#define _KERNEL_SPT_MULTIPLE_INT	_KERNEL_CFG_MULTIPLE_INT



/* %jp{�V�X�e���^�X�N(�A�C�h��)��TCB�����蓖�Ă�} */
#define _KERNEL_SYSTSK_TCB			_KERNEL_CFG_SYSTSK_TCB

/* %jp{���s���Ƀ^�X�N�����f�B�[�L���[�Ɍq�����܂܂Ƃ���} */
#define _KERNEL_RUNTSK_ON_RDQ		_KERNEL_CFG_RUNTSK_ON_RDQ

/* %jp{�T�X�y���h���Ƀ^�X�N�����f�B�[�L���[�Ɍq�����܂܂Ƃ���} */
#define _KERNEL_SUSTSK_ON_RDQ		_KERNEL_CFG_SUSTSK_ON_RDQ



/* ------------------------------------------------------------------ */
/*  service call support                                              */
/* ------------------------------------------------------------------ */

/* Task management functions */
#define _KERNEL_SPT_CRE_TSK			_KERNEL_CFG_CRE_TSK			/* cre_tsk */
#define _KERNEL_SPT_ACRE_TSK		_KERNEL_CFG_ACRE_TSK		/* acre_tsk */
#define _KERNEL_SPT_DEL_TSK			_KERNEL_CFG_DEL_TSK			/* del_tsk */
#define _KERNEL_SPT_ACT_TSK			_KERNEL_CFG_ACT_TSK			/* act_tsk */
#define _KERNEL_SPT_IACT_TSK		_KERNEL_CFG_IACT_TSK		/* iact_tsk */
#define _KERNEL_SPT_CAN_ACT 		_KERNEL_CFG_CAN_ACT 		/* can_act */
#define _KERNEL_SPT_STA_TSK 		_KERNEL_CFG_STA_TSK 		/* sta_tsk */
#define _KERNEL_SPT_EXT_TSK 		_KERNEL_CFG_EXT_TSK 		/* ext_tsk */
#define _KERNEL_SPT_EXD_TSK 		_KERNEL_CFG_EXD_TSK 		/* exd_tsk */
#define _KERNEL_SPT_TER_TSK 		_KERNEL_CFG_TER_TSK 		/* ter_tsk */
#define _KERNEL_SPT_CHG_PRI 		_KERNEL_CFG_CHG_PRI 		/* chg_pri */
#define _KERNEL_SPT_GET_PRI 		_KERNEL_CFG_GET_PRI 		/* get_pri */
#define _KERNEL_SPT_REF_TSK 		_KERNEL_CFG_REF_TSK 		/* ref_tsk */
#define _KERNEL_SPT_REF_TST 		_KERNEL_CFG_REF_TST 		/* ref_tst */

/* Task dependent synchronization functions */
#define _KERNEL_SPT_SLP_TSK 		_KERNEL_CFG_SLP_TSK 		/* slp_tsk */
#define _KERNEL_SPT_TSLP_TSK		_KERNEL_CFG_TSLP_TSK		/* tslp_tsk */
#define _KERNEL_SPT_WUP_TSK 		_KERNEL_CFG_WUP_TSK 		/* wup_tsk */
#define _KERNEL_SPT_IWUP_TSK		_KERNEL_CFG_IWUP_TSK		/* iwup_tsk */
#define _KERNEL_SPT_CAN_WUP 		_KERNEL_CFG_CAN_WUP 		/* can_wup */
#define _KERNEL_SPT_REL_WAI 		_KERNEL_CFG_REL_WAI 		/* rel_wai */
#define _KERNEL_SPT_IREL_WAI		_KERNEL_CFG_IREL_WAI		/* irel_wai */
#define _KERNEL_SPT_SUS_TSK 		_KERNEL_CFG_SUS_TSK 		/* sus_tsk */
#define _KERNEL_SPT_RSM_TSK 		_KERNEL_CFG_RSM_TSK 		/* rsm_tsk */
#define _KERNEL_SPT_FRSM_TSK		_KERNEL_CFG_FRSM_TSK		/* frsm_tsk */
#define _KERNEL_SPT_DLY_TSK 		_KERNEL_CFG_DLY_TSK 		/* dly_tsk */


/* Task exception handling functions */
#define _KERNEL_SPT_DEF_TEX 		_KERNEL_CFG_DEF_TEX 		/* def_tex */
#define _KERNEL_SPT_RAS_TEX 		_KERNEL_CFG_RAS_TEX 		/* ras_tex */
#define _KERNEL_SPT_IRAS_TEX		_KERNEL_CFG_IRAS_TEX		/* iras_tex */
#define _KERNEL_SPT_DIS_TEX 		_KERNEL_CFG_DIS_TEX 		/* dis_tex */
#define _KERNEL_SPT_ENA_TEX 		_KERNEL_CFG_ENA_TEX 		/* ena_tex */
#define _KERNEL_SPT_SNS_TEX 		_KERNEL_CFG_SNS_TEX 		/* sns_tex */
#define _KERNEL_SPT_REF_TEX 		_KERNEL_CFG_REF_TEX 		/* ref_tex */


/* Semaphores */
#define _KERNEL_SPT_CRE_SEM 		_KERNEL_CFG_CRE_SEM 		/* cre_sem */
#define _KERNEL_SPT_ACRE_SEM		_KERNEL_CFG_ACRE_SEM		/* acre_sem */
#define _KERNEL_SPT_DEL_SEM 		_KERNEL_CFG_DEL_SEM 		/* del_sem */
#define _KERNEL_SPT_SIG_SEM 		_KERNEL_CFG_SIG_SEM 		/* sig_sem */
#define _KERNEL_SPT_ISIG_SEM		_KERNEL_CFG_ISIG_SEM		/* isig_sem */
#define _KERNEL_SPT_WAI_SEM 		_KERNEL_CFG_WAI_SEM 		/* wai_sem */
#define _KERNEL_SPT_POL_SEM 		_KERNEL_CFG_POL_SEM 		/* pol_sem */
#define _KERNEL_SPT_TWAI_SEM		_KERNEL_CFG_TWAI_SEM		/* twai_sem */
#define _KERNEL_SPT_REF_SEM 		_KERNEL_CFG_REF_SEM 		/* ref_sem */

#if _KERNEL_SPT_TWAI_SEM || (_KERNEL_SPT_WAI_SEM && _KERNEL_SPT_POL_SEM)
#define _KERNEL_SPT_KWAI_SEM		TRUE
#else
#define _KERNEL_SPT_KWAI_SEM		FALSE
#endif


/* Eventflags */
#define _KERNEL_SPT_CRE_FLG 		_KERNEL_CFG_CRE_FLG 		/* cre_flg */
#define _KERNEL_SPT_ACRE_FLG		_KERNEL_CFG_ACRE_FLG		/* acre_flg */
#define _KERNEL_SPT_DEL_FLG 		_KERNEL_CFG_DEL_FLG 		/* del_flg */
#define _KERNEL_SPT_SET_FLG 		_KERNEL_CFG_SET_FLG 		/* set_flg */
#define _KERNEL_SPT_ISET_FLG		_KERNEL_CFG_ISET_FLG		/* iset_flg */
#define _KERNEL_SPT_CLR_FLG 		_KERNEL_CFG_CLR_FLG 		/* clr_flg */
#define _KERNEL_SPT_WAI_FLG 		_KERNEL_CFG_WAI_FLG 		/* wai_flg */
#define _KERNEL_SPT_POL_FLG 		_KERNEL_CFG_POL_FLG 		/* pol_flg */
#define _KERNEL_SPT_TWAI_FLG		_KERNEL_CFG_TWAI_FLG		/* twai_flg */
#define _KERNEL_SPT_REF_FLG 		_KERNEL_CFG_REF_FLG 		/* ref_flg */

#if _KERNEL_SPT_TWAI_FLG || (_KERNEL_SPT_WAI_FLG && _KERNEL_SPT_POL_FLG)
#define _KERNEL_SPT_KWAI_FLG		TRUE
#else
#define _KERNEL_SPT_KWAI_FLG		FALSE
#endif


/* Data queues */
#define _KERNEL_SPT_CRE_DTQ 		_KERNEL_CFG_CRE_DTQ 		/* cre_dtq */
#define _KERNEL_SPT_ACRE_DTQ		_KERNEL_CFG_ACRE_DTQ		/* acre_dtq */
#define _KERNEL_SPT_DEL_DTQ 		_KERNEL_CFG_DEL_DTQ 		/* del_dtq */
#define _KERNEL_SPT_SND_DTQ 		_KERNEL_CFG_SND_DTQ 		/* snd_dtq */
#define _KERNEL_SPT_PSND_DTQ		_KERNEL_CFG_PSND_DTQ		/* psnd_dtq */
#define _KERNEL_SPT_IPSND_DTQ		_KERNEL_CFG_IPSND_DTQ		/* ipsnd_dtq */
#define _KERNEL_SPT_TSND_DTQ		_KERNEL_CFG_TSND_DTQ		/* tsnd_dtq */
#define _KERNEL_SPT_FSND_DTQ		_KERNEL_CFG_FSND_DTQ		/* fsnd_dtq */
#define _KERNEL_SPT_IFSND_DT		_KERNEL_CFG_IFSND_DT		/* ifsnd_dtq */
#define _KERNEL_SPT_RCV_DTQ 		_KERNEL_CFG_RCV_DTQ 		/* rcv_dtq */
#define _KERNEL_SPT_PRCV_DTQ		_KERNEL_CFG_PRCV_DTQ		/* prcv_dtq */
#define _KERNEL_SPT_TRCV_DTQ		_KERNEL_CFG_TRCV_DTQ		/* trcv_dtq */
#define _KERNEL_SPT_REF_DTQ 		_KERNEL_CFG_REF_DTQ 		/* ref_dtq */

#if _KERNEL_SPT_TSND_DTQ || (_KERNEL_SPT_SND_DTQ && _KERNEL_SPT_PSND_DTQ)
#define _KERNEL_SPT_KSND_DTQ		TRUE
#else
#define _KERNEL_SPT_KSND_DTQ		FALSE
#endif

#if _KERNEL_SPT_TRCV_DTQ || (_KERNEL_SPT_RCV_DTQ && _KERNEL_SPT_PRCV_DTQ)
#define _KERNEL_SPT_KRCV_DTQ		TRUE
#else
#define _KERNEL_SPT_KRCV_DTQ		FALSE
#endif


/* Mailboxes */
#define _KERNEL_SPT_CRE_MBX 		_KERNEL_CFG_CRE_MBX 		/* cre_mbx */
#define _KERNEL_SPT_ACRE_MBX		_KERNEL_CFG_ACRE_MBX		/* acre_mbx */
#define _KERNEL_SPT_DEL_MBX 		_KERNEL_CFG_DEL_MBX 		/* del_mbx */
#define _KERNEL_SPT_SND_MBX 		_KERNEL_CFG_SND_MBX 		/* snd_mbx */
#define _KERNEL_SPT_RCV_MBX 		_KERNEL_CFG_RCV_MBX 		/* rcv_mbx */
#define _KERNEL_SPT_PRCV_MBX		_KERNEL_CFG_PRCV_MBX		/* prcv_mbx */
#define _KERNEL_SPT_TRCV_MBX		_KERNEL_CFG_TRCV_MBX		/* trcv_mbx */
#define _KERNEL_SPT_REF_MBX 		_KERNEL_CFG_REF_MBX 		/* ref_mbx */

/* Mutexes */
#define _KERNEL_SPT_CRE_MTX 		_KERNEL_CFG_CRE_MTX 		/* cre_mtx */
#define _KERNEL_SPT_ACRE_MTX		_KERNEL_CFG_ACRE_MTX		/* acre_mtx */
#define _KERNEL_SPT_DEL_MTX 		_KERNEL_CFG_DEL_MTX 		/* del_mtx */
#define _KERNEL_SPT_LOC_MTX 		_KERNEL_CFG_LOC_MTX 		/* loc_mtx */
#define _KERNEL_SPT_PLOC_MTX		_KERNEL_CFG_PLOC_MTX		/* ploc_mtx */
#define _KERNEL_SPT_TLOC_MTX		_KERNEL_CFG_TLOC_MTX		/* tloc_mtx */
#define _KERNEL_SPT_UNL_MTX 		_KERNEL_CFG_UNL_MTX 		/* unl_mtx */
#define _KERNEL_SPT_REF_MTX 		_KERNEL_CFG_REF_MTX 		/* ref_mtx */

#if _KERNEL_SPT_TLOC_MTX || (_KERNEL_SPT_LOC_MTX && _KERNEL_SPT_LOC_MTX)
#define _KERNEL_SPT_KLOC_MTX		TRUE
#else
#define _KERNEL_SPT_KLOC_MTX		FALSE
#endif


/* Message buffers */
#define _KERNEL_SPT_CRE_MBF 		_KERNEL_CFG_CRE_MBF 		/* cre_mbf */
#define _KERNEL_SPT_ACRE_MBF		_KERNEL_CFG_ACRE_MBF		/* acre_mbf */
#define _KERNEL_SPT_DEL_MBF 		_KERNEL_CFG_DEL_MBF 		/* del_mbf */
#define _KERNEL_SPT_SND_MBF 		_KERNEL_CFG_SND_MBF 		/* snd_mbf */
#define _KERNEL_SPT_PSND_MBF		_KERNEL_CFG_PSND_MBF		/* psnd_mbf */
#define _KERNEL_SPT_TSND_MBF		_KERNEL_CFG_TSND_MBF		/* tsnd_mbf */
#define _KERNEL_SPT_RCV_MBF 		_KERNEL_CFG_RCV_MBF 		/* rcv_mbf */
#define _KERNEL_SPT_PRCV_MBF		_KERNEL_CFG_PRCV_MBF		/* prcv_mbf */
#define _KERNEL_SPT_TRCV_MBF		_KERNEL_CFG_TRCV_MBF		/* trcv_mbf */
#define _KERNEL_SPT_REF_MBF 		_KERNEL_CFG_REF_MBF 		/* ref_mbf */

/* Rendezvous */
#define _KERNEL_SPT_CRE_POR 		_KERNEL_CFG_CRE_POR 		/* cre_por */
#define _KERNEL_SPT_ACRE_POR		_KERNEL_CFG_ACRE_POR		/* acre_por */
#define _KERNEL_SPT_DEL_POR 		_KERNEL_CFG_DEL_POR 		/* del_por */
#define _KERNEL_SPT_CAL_POR 		_KERNEL_CFG_CAL_POR 		/* cal_por */
#define _KERNEL_SPT_TCAL_POR		_KERNEL_CFG_TCAL_POR		/* tcal_por */
#define _KERNEL_SPT_ACP_POR 		_KERNEL_CFG_ACP_POR 		/* acp_por */
#define _KERNEL_SPT_PACP_POR		_KERNEL_CFG_PACP_POR		/* pacp_por */
#define _KERNEL_SPT_TACP_POR		_KERNEL_CFG_TACP_POR		/* tacp_por */
#define _KERNEL_SPT_FWD_POR 		_KERNEL_CFG_FWD_POR 		/* fwd_por */
#define _KERNEL_SPT_RPL_RDV 		_KERNEL_CFG_RPL_RDV 		/* rpl_rdv */
#define _KERNEL_SPT_REF_POR 		_KERNEL_CFG_REF_POR 		/* ref_por */
#define _KERNEL_SPT_REF_RDV 		_KERNEL_CFG_REF_RDV 		/* ref_rdv */

/* Fixed-sized memory pools */
#define _KERNEL_SPT_CRE_MPF 		_KERNEL_CFG_CRE_MPF 		/* cre_mpf */
#define _KERNEL_SPT_ACRE_MPF		_KERNEL_CFG_ACRE_MPF		/* acre_mpf */
#define _KERNEL_SPT_DEL_MPF 		_KERNEL_CFG_DEL_MPF 		/* del_mpf */
#define _KERNEL_SPT_GET_MPF 		_KERNEL_CFG_GET_MPF 		/* get_mpf */
#define _KERNEL_SPT_PGET_MPF		_KERNEL_CFG_PGET_MPF		/* pget_mpf */
#define _KERNEL_SPT_TGET_MPF		_KERNEL_CFG_TGET_MPF		/* tget_mpf */
#define _KERNEL_SPT_REL_MPF 		_KERNEL_CFG_REL_MPF 		/* rel_mpf */
#define _KERNEL_SPT_REF_MPF 		_KERNEL_CFG_REF_MPF 		/* ref_mpf */

/* Variable-sized memory pools */
#define _KERNEL_SPT_CRE_MPL 		_KERNEL_CFG_CRE_MPL 		/* cre_mpl */
#define _KERNEL_SPT_ACRE_MPL		_KERNEL_CFG_ACRE_MPL		/* acre_mpl */
#define _KERNEL_SPT_DEL_MPL 		_KERNEL_CFG_DEL_MPL 		/* del_mpl */
#define _KERNEL_SPT_GET_MPL 		_KERNEL_CFG_GET_MPL 		/* get_mpl */
#define _KERNEL_SPT_PGET_MPL		_KERNEL_CFG_PGET_MPL		/* pget_mpl */
#define _KERNEL_SPT_TGET_MPL		_KERNEL_CFG_TGET_MPL		/* tget_mpl */
#define _KERNEL_SPT_REL_MPL 		_KERNEL_CFG_REL_MPL 		/* rel_mpl */
#define _KERNEL_SPT_REF_MPL 		_KERNEL_CFG_REF_MPL 		/* ref_mpl */

/* System time management */
#define _KERNEL_SPT_SET_TIM 		_KERNEL_CFG_SET_TIM 		/* set_tim */
#define _KERNEL_SPT_GET_TIM 		_KERNEL_CFG_GET_TIM 		/* get_tim */
#define _KERNEL_SPT_ISIG_TIM		_KERNEL_CFG_ISIG_TIM		/* isig_tim */

/* Cyclic handlers */
#define _KERNEL_SPT_CRE_CYC 		_KERNEL_CFG_CRE_CYC 		/* cre_cyc */
#define _KERNEL_SPT_ACRE_CYC		_KERNEL_CFG_ACRE_CYC		/* acre_cyc */
#define _KERNEL_SPT_DEL_CYC 		_KERNEL_CFG_DEL_CYC 		/* del_cyc */
#define _KERNEL_SPT_STA_CYC 		_KERNEL_CFG_STA_CYC 		/* sta_cyc */
#define _KERNEL_SPT_STP_CYC 		_KERNEL_CFG_STP_CYC 		/* stp_cyc */
#define _KERNEL_SPT_REF_CYC 		_KERNEL_CFG_REF_CYC 		/* ref_cyc */

/* Alarm handlers */
#define _KERNEL_SPT_CRE_ALM 		_KERNEL_CFG_CRE_ALM 		/* cre_alm */
#define _KERNEL_SPT_ACRE_ALM		_KERNEL_CFG_ACRE_ALM		/* acre_alm */
#define _KERNEL_SPT_DEL_ALM 		_KERNEL_CFG_DEL_ALM 		/* del_alm */
#define _KERNEL_SPT_STA_ALM 		_KERNEL_CFG_STA_ALM 		/* sta_alm */
#define _KERNEL_SPT_STP_ALM 		_KERNEL_CFG_STP_ALM 		/* stp_alm */
#define _KERNEL_SPT_REF_ALM 		_KERNEL_CFG_REF_ALM 		/* ref_alm */

/* Overrun handlers */
#define _KERNEL_SPT_DEF_OVR 		_KERNEL_CFG_DEF_OVR 		/* def_ovr */
#define _KERNEL_SPT_STA_OVR 		_KERNEL_CFG_STA_OVR 		/* sta_ovr */
#define _KERNEL_SPT_STP_OVR 		_KERNEL_CFG_STP_OVR 		/* stp_ovr */
#define _KERNEL_SPT_REF_OVR 		_KERNEL_CFG_REF_OVR 		/* ref_ovr */

/* System management functions */
#define _KERNEL_SPT_ROT_RDQ 		_KERNEL_CFG_ROT_RDQ 		/* rot_rdq */
#define _KERNEL_SPT_IROT_RDQ		_KERNEL_CFG_IROT_RDQ		/* irot_rdq */
#define _KERNEL_SPT_GET_TID 		_KERNEL_CFG_GET_TID 		/* get_tid */
#define _KERNEL_SPT_IGET_TID		_KERNEL_CFG_IGET_TID		/* iget_tid */
#define _KERNEL_SPT_LOC_CPU 		_KERNEL_CFG_LOC_CPU 		/* loc_cpu */
#define _KERNEL_SPT_ILOC_CPU		_KERNEL_CFG_ILOC_CPU		/* iloc_cpu */
#define _KERNEL_SPT_UNL_CPU 		_KERNEL_CFG_UNL_CPU 		/* unl_cpu */
#define _KERNEL_SPT_ILNL_CPU		_KERNEL_CFG_ILNL_CPU		/* ilnl_cpu */
#define _KERNEL_SPT_DIS_DSP 		_KERNEL_CFG_DIS_DSP 		/* dis_dsp */
#define _KERNEL_SPT_ENA_DSP 		_KERNEL_CFG_ENA_DSP 		/* ena_dsp */
#define _KERNEL_SPT_SNS_CTX 		_KERNEL_CFG_SNS_CTX 		/* sns_ctx */
#define _KERNEL_SPT_SNS_LOC 		_KERNEL_CFG_SNS_LOC 		/* sns_loc */
#define _KERNEL_SPT_SNS_DSP 		_KERNEL_CFG_SNS_DSP 		/* sns_dsp */
#define _KERNEL_SPT_SNS_DPN 		_KERNEL_CFG_SNS_DPN 		/* sns_dpn */
#define _KERNEL_SPT_REF_SYS 		_KERNEL_CFG_REF_SYS 		/* ref_sys */

/* Interrupt management functions */
#define _KERNEL_SPT_DEF_INH 		_KERNEL_CFG_DEF_INH 		/* def_inh */
#define _KERNEL_SPT_CRE_ISR 		_KERNEL_CFG_CRE_ISR 		/* cre_isr */
#define _KERNEL_SPT_ACRE_ISR		_KERNEL_CFG_ACRE_ISR		/* acre_isr */
#define _KERNEL_SPT_DEL_ISR 		_KERNEL_CFG_DEL_ISR 		/* del_isr */
#define _KERNEL_SPT_REF_ISR 		_KERNEL_CFG_REF_ISR 		/* ref_isr */
#define _KERNEL_SPT_DIS_INT 		_KERNEL_CFG_DIS_INT 		/* dis_int */
#define _KERNEL_SPT_ENA_INT 		_KERNEL_CFG_ENA_INT 		/* ena_int */
#define _KERNEL_SPT_CHG_ILV 		_KERNEL_CFG_CHG_ILV 		/* chg_ilv */
#define _KERNEL_SPT_GET_ILV 		_KERNEL_CFG_GET_ILV 		/* get_ilv */

/* Service call management functions */
#define _KERNEL_SPT_DEF_SVC 		_KERNEL_CFG_DEF_SVC 		/* def_svc */
#define _KERNEL_SPT_CAL_SVC 		_KERNEL_CFG_CAL_SVC 		/* cal_svc */

/* System configulation management functions */
#define _KERNEL_SPT_DEF_EXC 		_KERNEL_CFG_DEF_EXC 		/* def_exc */
#define _KERNEL_SPT_REF_CFG 		_KERNEL_CFG_REF_CFG 		/* ref_cfg */
#define _KERNEL_SPT_REF_VER 		_KERNEL_CFG_REF_VER 		/* ref_ver */

/* Static API */
#define _KERNEL_SPT_SCRE_TSK		_KERNEL_CFG_SCRE_TSK		/* CRE_TSK */
#define _KERNEL_SPT_SDEF_TEX		_KERNEL_CFG_SDEF_TEX		/* DEF_TEX */
#define _KERNEL_SPT_SCRE_SEM		_KERNEL_CFG_SCRE_SEM		/* CRE_SEM */
#define _KERNEL_SPT_SCRE_FLG		_KERNEL_CFG_SCRE_FLG		/* CRE_FLG */
#define _KERNEL_SPT_SCRE_DTQ		_KERNEL_CFG_SCRE_DTQ		/* CRE_DTQ */
#define _KERNEL_SPT_SCRE_MBX		_KERNEL_CFG_SCRE_MBX		/* CRE_MBX */
#define _KERNEL_SPT_SCRE_MTX		_KERNEL_CFG_SCRE_MTX		/* CRE_MTX */
#define _KERNEL_SPT_SCRE_MBF		_KERNEL_CFG_SCRE_MBF		/* CRE_MBF */
#define _KERNEL_SPT_SCRE_POR		_KERNEL_CFG_SCRE_POR		/* CRE_POR */
#define _KERNEL_SPT_SCRE_MPF		_KERNEL_CFG_SCRE_MPF		/* CRE_MPF */
#define _KERNEL_SPT_SCRE_MPL		_KERNEL_CFG_SCRE_MPL		/* CRE_MPL */
#define _KERNEL_SPT_SCRE_CYC		_KERNEL_CFG_SCRE_CYC		/* CRE_CYC */
#define _KERNEL_SPT_SCRE_ALM		_KERNEL_CFG_SCRE_ALM		/* CRE_ALM */
#define _KERNEL_SPT_SDEF_OVR		_KERNEL_CFG_SDEF_OVR		/* DEF_OVR */
#define _KERNEL_SPT_SDEF_INH		_KERNEL_CFG_SDEF_INH		/* DEF_INH */
#define _KERNEL_SPT_SCRE_ISR		_KERNEL_CFG_SCRE_ISR		/* CRE_ISR */
#define _KERNEL_SPT_SDEF_SVC		_KERNEL_CFG_SDEF_SVC		/* DEF_SVC */
#define _KERNEL_SPT_SDEF_EXC		_KERNEL_CFG_SDEF_EXC		/* DEF_EXC */
#define _KERNEL_SPT_SATT_INI		_KERNEL_CFG_SATT_INI		/* ATT_INI */
#define _KERNEL_SPT_SINCLUDE		_KERNEL_CFG_SINCLUDE		/* INCLUDE */


/* %jp{�^�X�N�I�u�W�F�N�g�T�|�[�g�̔���} */
#if ((_KERNEL_CFG_CRE_TSK)|| (_KERNEL_CFG_ACRE_TSK) || (_KERNEL_CFG_SCRE_TSK)) && (_KERNEL_CFG_TMAX_TSKID) > 0
#define _KERNEL_SPT_TSK				TRUE
#else
#define _KERNEL_SPT_TSK				FALSE
#endif

/* %jp{�^�X�N��O�����T�|�[�g�̔���} */
#if ((_KERNEL_CFG_DEF_TEX)|| (_KERNEL_CFG_SDEF_TEX)) && (_KERNEL_CFG_TMAX_TSKID) > 0
#define _KERNEL_SPT_TEX				TRUE
#else
#define _KERNEL_SPT_TEX				FALSE
#endif


#define _KERNEL_SPT_SEM				TRUE
#define _KERNEL_SPT_FLG				TRUE
#define _KERNEL_SPT_DTQ				FALSE
#define _KERNEL_SPT_MBX				FALSE


/* %jp{�~���[�e�b�N�X�I�u�W�F�N�g�T�|�[�g�̔���} */
#if ((_KERNEL_CFG_CRE_MTX)|| (_KERNEL_CFG_ACRE_MTX) || (_KERNEL_CFG_SCRE_MTX)) && (_KERNEL_CFG_TMAX_MTXID) > 0
#define _KERNEL_SPT_MTX				TRUE
#else
#define _KERNEL_SPT_MTX				FALSE
#endif

#define _KERNEL_SPT_MBF				FALSE
#define _KERNEL_SPT_MPF				FALSE
#define _KERNEL_SPT_MPL				FALSE
#define _KERNEL_SPT_CYC				FALSE
#define _KERNEL_SPT_ALM				FALSE
#define _KERNEL_SPT_OVR				FALSE

/* %jp{�����݃n���h���T�|�[�g�̔���} */
#if _KERNEL_SPT_DEF_INH || _KERNEL_SPT_SDEF_INH
#define _KERNEL_SPT_INH				TRUE
#else
#define _KERNEL_SPT_INH				FALSE
#endif

/* %jp{�����݃T�[�r�X���[�`���T�|�[�g�̔���} */
#if _KERNEL_IRCATR_IRC && (_KERNEL_SPT_CRE_ISR || _KERNEL_SPT_SCRE_ISR) && (_KERNEL_CFG_TMAX_ISRID) > 0
#define _KERNEL_SPT_ISR				TRUE
#else
#define _KERNEL_SPT_ISR				FALSE
#endif


/* %jp{�I�u�W�F�N�g���I�����T�|�[�g�̔���} */
#if (_KERNEL_SPT_CRE_TSK)			\
	|| (_KERNEL_SPT_ACRE_TSK)		\
	|| (_KERNEL_SPT_DEF_TEX)		\
	|| (_KERNEL_SPT_CRE_SEM)		\
	|| (_KERNEL_SPT_ACRE_SEM)		\
	|| (_KERNEL_SPT_CRE_FLG)		\
	|| (_KERNEL_SPT_ACRE_FLG)		\
	|| (_KERNEL_SPT_CRE_DTQ)		\
	|| (_KERNEL_SPT_ACRE_DTQ)		\
	|| (_KERNEL_SPT_CRE_MBX)		\
	|| (_KERNEL_SPT_ACRE_MBX)		\
	|| (_KERNEL_SPT_CRE_MTX)		\
	|| (_KERNEL_SPT_ACRE_MTX)		\
	|| (_KERNEL_SPT_CRE_MBF)		\
	|| (_KERNEL_SPT_ACRE_MBF)		\
	|| (_KERNEL_SPT_CRE_MPF)		\
	|| (_KERNEL_SPT_ACRE_MPF)		\
	|| (_KERNEL_SPT_CRE_MPL)		\
	|| (_KERNEL_SPT_ACRE_MPL)		\
	|| (_KERNEL_SPT_CRE_CYC)		\
	|| (_KERNEL_SPT_ACRE_CYC)		\
	|| (_KERNEL_SPT_CRE_ALM)		\
	|| (_KERNEL_SPT_ACRE_ALM)		\
	|| (_KERNEL_SPT_DEF_OVR)		\
	|| (_KERNEL_SPT_CRE_ISR)		\
	|| (_KERNEL_SPT_ACRE_ISR)
#define _KERNEL_SPT_CREOBJ			TRUE
#else
#define _KERNEL_SPT_CREOBJ			FALSE
#endif


/* %jp{�I�u�W�F�N�g���I�폜�T�|�[�g�̔���} */
#if (_KERNEL_SPT_DEL_TSK)			\
	|| (_KERNEL_SPT_DEL_SEM)		\
	|| (_KERNEL_SPT_DEL_FLG)		\
	|| (_KERNEL_SPT_DEL_DTQ)		\
	|| (_KERNEL_SPT_DEL_MBX)		\
	|| (_KERNEL_SPT_DEL_MTX)		\
	|| (_KERNEL_SPT_DEL_MBF)		\
	|| (_KERNEL_SPT_DEL_MPF)		\
	|| (_KERNEL_SPT_DEL_MPL)		\
	|| (_KERNEL_SPT_DEL_CYC)		\
	|| (_KERNEL_SPT_DEL_ALM)		\
	|| (_KERNEL_SPT_DEL_ISR)
#define _KERNEL_SPT_DELOBJ			TRUE
#else
#define _KERNEL_SPT_DELOBJ			FALSE
#endif


/* %jp{�^�C���A�E�g�T�|�[�g�̔���} */
#if (_KERNEL_SPT_TSLP_TSK)			\
	|| (_KERNEL_SPT_TWAI_SEM)		\
	|| (_KERNEL_SPT_TWAI_FLG)		\
	|| (_KERNEL_SPT_TSND_DTQ)		\
	|| (_KERNEL_SPT_TRCV_DTQ)		\
	|| (_KERNEL_SPT_TRCV_MBX)		\
	|| (_KERNEL_SPT_TLOC_MTX)		\
	|| (_KERNEL_SPT_TSND_MBF)		\
	|| (_KERNEL_SPT_TRCV_MBF)		\
	|| (_KERNEL_SPT_TCAL_POR)		\
	|| (_KERNEL_SPT_TACP_POR)		\
	|| (_KERNEL_SPT_TGET_MPF)		\
	|| (_KERNEL_SPT_TGET_MPL)
#define _KERNEL_SPT_TMOUT			TRUE
#else
#define _KERNEL_SPT_TMOUT			FALSE
#endif



/* ------------------------------------------------------------------ */
/*  Task queue                                                        */
/* ------------------------------------------------------------------ */

#define _KERNEL_QUE_ALG_ONEWAYLIST		1
#define _KERNEL_QUE_ALG_TWOWAYLIST		2

#define _KERNEL_QUE_ALGORITHM			_KERNEL_CFG_QUE_ALGORITHM


/* ------------------------------------------------------------------ */
/*  Ready queue                                                       */
/* ------------------------------------------------------------------ */

#define _KERNEL_RDQ_ALG_SINGLE_QUE				1
#define _KERNEL_RDQ_ALG_ARRAYED_QUE				2
#define _KERNEL_RDQ_ALG_BITMAP_ARRAYED_QUE		3

#define _KERNEL_RDQ_ALGORITHM			_KERNEL_CFG_RDQ_ALGORITHM


/* ------------------------------------------------------------------ */
/*  Timeout queue                                                     */
/* ------------------------------------------------------------------ */

#define _KERNEL_SPT_TOQ					_KERNEL_SPT_TMOUT || _KERNEL_SPT_DLY_TSK


/* ------------------------------------------------------------------ */
/*  Timer queue                                                       */
/* ------------------------------------------------------------------ */

#define _KERNEL_SPT_TMQ					TRUE


/* ------------------------------------------------------------------ */
/*  Kernel memory heap                                                */
/* ------------------------------------------------------------------ */

#define _KERNEL_SPT_HEP					_KERNEL_SPT_CREOBJ



/* ------------------------------------------------------------------ */
/*  ID                                                                */
/* ------------------------------------------------------------------ */

/* ---------------------------------- */
/*            Task-ID                 */
/* ---------------------------------- */

/* %jp{�^�X�NID�̍ŏ��l} */
#define _KERNEL_TMIN_TSKID			1

/* %jp{�^�X�NID�̍ő�l} */
#if _KERNEL_CFG_TMAX_TSKID < 0
#define _KERNEL_TMAX_TSKID			_KERNEL_TMAX_ID					
#else
#define _KERNEL_TMAX_TSKID			_KERNEL_CFG_TMAX_TSKID
#endif

/**< %jp{�^�X�NID�������̂ɍŒ���K�v��bit��} */
#define _KERNEL_TBIT_TSKID			_KERNEL_MAXNUM2BIT(_KERNEL_TMAX_TSKID)


/* ---------------------------------- */
/*          Semaphore-ID              */
/* ---------------------------------- */

/* %jp{�Z�}�t�HID�̍ŏ��l} */
#define _KERNEL_TMIN_SEMID		1		

/* %jp{�Z�}�t�HID�̍ő�l} */
#if _KERNEL_CFG_TMAX_SEMID < 0
#define _KERNEL_TMAX_SEMID			_KERNEL_TMAX_ID					
#else
#define _KERNEL_TMAX_SEMID			_KERNEL_CFG_TMAX_SEMID
#endif


#define _KERNEL_DEF_TMAX_TSKID		_KERNEL_CFG_DEF_TMAX_TSKID
#define _KERNEL_DEF_TMAX_SEMID		_KERNEL_CFG_DEF_TMAX_SEMID
#define _KERNEL_DEF_TMAX_FLGID		_KERNEL_CFG_DEF_TMAX_FLGID
#define _KERNEL_DEF_TMAX_DTQID		_KERNEL_CFG_DEF_TMAX_DTQID
#define _KERNEL_DEF_TMAX_MBXID		_KERNEL_CFG_DEF_TMAX_MBXID
#define _KERNEL_DEF_TMAX_MTXID		_KERNEL_CFG_DEF_TMAX_MTXID
#define _KERNEL_DEF_TMAX_MBFID		_KERNEL_CFG_DEF_TMAX_MBFID
#define _KERNEL_DEF_TMAX_PORID		_KERNEL_CFG_DEF_TMAX_PORID
#define _KERNEL_DEF_TMAX_MPFID		_KERNEL_CFG_DEF_TMAX_MPFID
#define _KERNEL_DEF_TMAX_MPLID		_KERNEL_CFG_DEF_TMAX_MPLID
#define _KERNEL_DEF_TMAX_CYCID		_KERNEL_CFG_DEF_TMAX_CYCID
#define _KERNEL_DEF_TMAX_ALMID		_KERNEL_CFG_DEF_TMAX_ALMID
#define _KERNEL_DEF_TMAX_OVRID		_KERNEL_CFG_DEF_TMAX_OVRID
#define _KERNEL_DEF_TMAX_ISRID		_KERNEL_CFG_DEF_TMAX_ISRID


#define _KERNEL_TMAX_FLGID			_KERNEL_CFG_TMAX_FLGID
#define _KERNEL_TMAX_DTQID			_KERNEL_CFG_TMAX_DTQID
#define _KERNEL_TMAX_MBXID			_KERNEL_CFG_TMAX_MBXID
#define _KERNEL_TMAX_MTXID			_KERNEL_CFG_TMAX_MTXID
#define _KERNEL_TMAX_MBFID			_KERNEL_CFG_TMAX_MBFID
#define _KERNEL_TMAX_PORID			_KERNEL_CFG_TMAX_PORID
#define _KERNEL_TMAX_MPFID			_KERNEL_CFG_TMAX_MPFID
#define _KERNEL_TMAX_MPLID			_KERNEL_CFG_TMAX_MPLID
#define _KERNEL_TMAX_CYCID			_KERNEL_CFG_TMAX_CYCID
#define _KERNEL_TMAX_ALMID			_KERNEL_CFG_TMAX_ALMID
#define _KERNEL_TMAX_OVRID			_KERNEL_CFG_TMAX_OVRID
#define _KERNEL_TMAX_ISRID			_KERNEL_CFG_TMAX_ISRID




/* ---------------------------------- */
/*               Handle               */
/* ---------------------------------- */

#define _KERNEL_TSKHDL_ID			_KERNEL_CFG_TSKHDL_ID
#define _KERNEL_MTXHDL_ID			_KERNEL_CFG_MTXHDL_ID
#define _KERNEL_ISRHDL_ID			_KERNEL_CFG_ISRHDL_ID




/* ------------------------------------------------------------------ */
/*  TCB                                                               */
/* ------------------------------------------------------------------ */


#define _KERNEL_TCB_ALG_BLKARRAY	1
#define _KERNEL_TCB_ALG_PTRARRAY	2


#define _KERNEL_TCB_BITFIELD		_KERNEL_CFG_TCB_BITFIELD
#define _KERNEL_TCB_ALGORITHM		_KERNEL_CFG_TCB_ALGORITHM

#define _KERNEL_SPT_TSK_TA_ACT		_KERNEL_CFG_TSK_TA_ACT

#if (_KERNEL_TCB_ALGORITHM == _KERNEL_TCB_ALG_BLKARRAY) && (_KERNEL_SPT_CRE_TSK || _KERNEL_SPT_ACRE_TSK)
#define _KERNEL_TCB_SPLIT_RO		FALSE
#else
#define _KERNEL_TCB_SPLIT_RO		_KERNEL_CFG_TCB_SPLIT_RO
#endif




/* ---------------------------------- */
/*           Task-state               */
/* ---------------------------------- */

/* Task State */
#define _KERNEL_TTS_RUN				TTS_RUN			/**< %jp{���s���} */
#define _KERNEL_TTS_RDY				TTS_RDY			/**< %jp{���s�\���} */
#define _KERNEL_TTS_WAI				TTS_WAI			/**< %jp{�҂����} */
#define _KERNEL_TTS_SUS				TTS_SUS			/**< %jp{�����҂����} */
#define _KERNEL_TTS_WAS				TTS_WAS			/**< %jp{��d�҂����} */
#define _KERNEL_TTS_DMT				0				/**< %jp{�x�~���} */

#define _KERNEL_TSK_TBIT_TSKSTAT	4				/**< %jp{�^�X�N��Ԃ������̂ɍŒ���K�v�ȃr�b�g��(5�r�b�g)} */

#define _KERNEL_ENC_TTS(x)			((x) & 0xf)
#define _KERNEL_DEC_TTS(x)			((x) == 0 ? TTS_DMT : (x))


/* ---------------------------------- */
/*           Task priopity            */
/* ---------------------------------- */

/* %jp{�D��x�͈̔�}%en{Priority Range} */
#if _KERNEL_CFG_TMAX_TPRI < 0
#define _KERNEL_TSK_TMAX_TPRI		_KERNEL_TMAX_PRI
#else
#define _KERNEL_TSK_TMAX_TPRI		_KERNEL_CFG_TMAX_TPRI
#endif

#define _KERNEL_TSK_TBIT_TPRI		_KERNEL_MAXNUM2BIT(_KERNEL_TSK_TMAX_TPRI)



/* ---------------------------------- */
/*           Task wait                */
/* ---------------------------------- */

/* Task Wait */
#if _KERNEL_OPT_CB_SIZE								/**< %jp{�T�C�Y�D��Ȃ�p�b�L���O���ĕۑ�} */

#define _KERNEL_TTW_SLP				0				/**< %jp{�N���҂����} */
#define _KERNEL_TTW_DLY				1				/**< %jp{���Ԍo�ߑ҂����} */
#define _KERNEL_TTW_SEM				2				/**< %jp{�Z�}�t�H�����̊l���҂����} */
#define _KERNEL_TTW_FLG				3				/**< %jp{�C�x���g�t���O�҂����} */
#define _KERNEL_TTW_SDTQ			4				/**< %jp{�f�[�^�L���[�ւ̑��M�҂����} */
#define _KERNEL_TTW_RDTQ			5				/**< %jp{�f�[�^�L���[����̎�M�҂����} */
#define _KERNEL_TTW_MBX				6				/**< %jp{���[���{�b�N�X����̎�M�҂����} */
#define _KERNEL_TTW_MTX				7				/**< %jp{�~���[�e�b�N�X�̃��b�N�҂����} */
#define _KERNEL_TTW_SMBF			8				/**< %jp{���b�Z�[�W�o�b�t�@�ւ̑��M�҂����} */
#define _KERNEL_TTW_RMBF			9				/**< %jp{���b�Z�[�W�o�b�t�@����̎�M�҂����} */
#define _KERNEL_TTW_CAL				10				/**< %jp{�����f�u�̌Ăяo���҂����} */
#define _KERNEL_TTW_ACP				11				/**< %jp{�����f�u�̎�t�҂����} */
#define _KERNEL_TTW_RDV				12				/**< %jp{�����f�u�̏I���҂����} */
#define _KERNEL_TTW_MPF				13				/**< %jp{�Œ蒷�������u���b�N�̊l���҂����} */
#define _KERNEL_TTW_MPL				14				/**< %jp{�ϒ��������u���b�N�̊l���҂����} */

#define _KERNEL_DEC_TTW(x)			(1 << (x))

#define _KERNEL_TSK_TBIT_TSKWAIT	4				/**< %jp{�r�b�g��4�r�b�g} */
#define _KERNEL_TSK_TMIN_TSKWAIT	_KERNEL_TTW_SLP
#define _KERNEL_TSK_TMAX_TSKWAIT	_KERNEL_TTW_MPL

#else												/**< %jp{�҂���Ԃ��p�b�N���Ȃ��Ȃ�} */

#define _KERNEL_TTW_SLP				TTW_SLP			/* �N���҂���� */
#define _KERNEL_TTW_DLY				TTW_DLY			/* ���Ԍo�ߑ҂���� */
#define _KERNEL_TTW_SEM				TTW_SEM			/* �Z�}�t�H�����̊l���҂���� */
#define _KERNEL_TTW_FLG				TTW_FLG			/* �C�x���g�t���O�҂���� */
#define _KERNEL_TTW_SDTQ			TTW_SDTQ		/* �f�[�^�L���[�ւ̑��M�҂���� */
#define _KERNEL_TTW_RDTQ			TTW_RDTQ		/* �f�[�^�L���[����̎�M�҂���� */
#define _KERNEL_TTW_MBX				TTW_MBX			/* ���[���{�b�N�X����̎�M�҂���� */
#define _KERNEL_TTW_MTX				TTW_MTX			/* �~���[�e�b�N�X�̃��b�N�҂���� */
#define _KERNEL_TTW_SMBF			TTW_SMBF		/* ���b�Z�[�W�o�b�t�@�ւ̑��M�҂���� */
#define _KERNEL_TTW_RMBF			TTW_RMBF		/* ���b�Z�[�W�o�b�t�@����̎�M�҂���� */
#define _KERNEL_TTW_CAL				TTW_CAL			/* �����f�u�̌Ăяo���҂���� */
#define _KERNEL_TTW_ACP				TTW_ACP			/* �����f�u�̎�t�҂���� */
#define _KERNEL_TTW_RDV				TTW_RDV			/* �����f�u�̏I���҂���� */
#define _KERNEL_TTW_MPF				TTW_MPF			/* �Œ蒷�������u���b�N�̊l���҂���� */
#define _KERNEL_TTW_MPL				TTW_MPL			/* �ϒ��������u���b�N�̊l���҂���� */

#define _KERNEL_DEC_TTW(x)			(x)

#define _KERNEL_TSK_TBIT_TSKWAIT	15				/**< %jp{�r�b�g��15�r�b�g} */
#define _KERNEL_TSK_TMIN_TSKWAIT	_KERNEL_TTW_SLP
#define _KERNEL_TSK_TMAX_TSKWAIT	_KERNEL_TTW_MPL

#endif


/* ---------------------------------- */
/*           Waitbject-ID             */
/* ---------------------------------- */

/* %jp{ID�̍ŏ��l} */
#define _KERNEL_TMIN_TSK_WOBJID		1

/* %jp{ID�̍ő�l} */
#define _KERNEL_TSK_TMAX_WOBJID		1
#if _KERNEL_TMAX_SEMID > _KERNEL_TSK_TMAX_WOBJID
#undef _KERNEL_TSK_TMAX_WOBJID
#define _KERNEL_TSK_TMAX_WOBJID		_KERNEL_TMAX_SEMID
#endif

#if _KERNEL_TMAX_FLGID > _KERNEL_TSK_TMAX_WOBJID
#undef _KERNEL_TSK_TMAX_WOBJID
#define _KERNEL_TSK_TMAX_WOBJID		_KERNEL_TMAX_FLGID
#endif

#if _KERNEL_TMAX_DTQID > _KERNEL_TSK_TMAX_WOBJID
#undef _KERNEL_TSK_TMAX_WOBJID
#define _KERNEL_TSK_TMAX_WOBJID		_KERNEL_TMAX_DTQID
#endif

#if _KERNEL_TMAX_MBXID > _KERNEL_TSK_TMAX_WOBJID
#undef _KERNEL_TSK_TMAX_WOBJID
#define _KERNEL_TSK_TMAX_WOBJID		_KERNEL_TMAX_MBXID
#endif

#if _KERNEL_TMAX_MTXID > _KERNEL_TSK_TMAX_WOBJID
#undef _KERNEL_TSK_TMAX_WOBJID
#define _KERNEL_TSK_TMAX_WOBJID		_KERNEL_TMAX_MTXID
#endif

#if _KERNEL_TMAX_MBFID > _KERNEL_TSK_TMAX_WOBJID
#undef _KERNEL_TSK_TMAX_WOBJID
#define _KERNEL_TSK_TMAX_WOBJID		_KERNEL_TMAX_MBFID
#endif

/**< %jp{ID�������̂ɍŒ���K�v��bit��} */
#define _KERNEL_TSK_TBIT_WOBJID		_KERNEL_MAXNUM2BIT(_KERNEL_TSK_TMAX_WOBJID)


/* ---------------------------------- */
/*       activate queuing count       */
/* ---------------------------------- */

/* %jp{�^�X�N�N���v���L���[�C���O���̍ő�l} */
#define _KERNEL_TSK_TMAX_ACTCNT		_KERNEL_TMAX_ACTCNT
#define _KERNEL_TSK_TBIT_ACTCNT		_KERNEL_MAXNUM2BIT(_KERNEL_TSK_TMAX_ACTCNT)


/* ---------------------------------- */
/*       wakeup queuing count         */
/* ---------------------------------- */

/* %jp{�^�X�N�N���v���L���[�C���O���̍ő�l} */
#define _KERNEL_TSK_TMAX_WUPCNT		_KERNEL_TMAX_WUPCNT
#define _KERNEL_TSK_TBIT_WUPCNT		_KERNEL_MAXNUM2BIT(_KERNEL_TSK_TMAX_WUPCNT)


/* ---------------------------------- */
/*         suspend nest count         */
/* ---------------------------------- */

/* %jp{�^�X�N�����҂��v���l�X�g���̍ő�l} */
#define _KERNEL_TSK_TMAX_SUSCNT		_KERNEL_TMAX_SUSCNT
#define _KERNEL_TSK_TBIT_SUSCNT		_KERNEL_MAXNUM2BIT(_KERNEL_TSK_TMAX_SUSCNT)


/* ---------------------------------- */
/*           task data                */
/* ---------------------------------- */

#define _KERNEL_TSK_TBIT_DATA		_KERNEL_TBIT_VP_INT


/* ---------------------------------- */
/*            error code              */
/* ---------------------------------- */

#define _KERNEL_TSK_TBIT_ERCD		7


/* ---------------------------------- */
/*          Task-ID                   */
/* ---------------------------------- */

#define _KERNEL_TSK_TMAX_TSKID		_KERNEL_TMAX_TSKID


/* ---------------------------------- */
/*          reltime                   */
/* ---------------------------------- */

#define _KERNEL_TSK_TMIN_RELTIM		_KERNEL_TMIN_RELTIM
#define _KERNEL_TSK_TMAX_RELTIM		_KERNEL_TMAX_RELTIM



/* ---------------------------------- */
/*      Task exception state          */
/* ---------------------------------- */

#define  _KERNEL_TXS_ENA			1
#define  _KERNEL_TXS_DIS			0


/* ---------------------------------- */
/*            TCB member              */
/* ---------------------------------- */

/* %jp{�K�{} */
#define _KERNEL_TCB_CTXCB			TRUE
#define _KERNEL_TCB_QUE				TRUE
#define _KERNEL_TCB_QUEOBJ			TRUE
#define _KERNEL_TCB_TSKSTAT			TRUE

/* %jp{�^�C���A�E�g�L���[}*/
#define _KERNEL_TCB_TOQOBJ			_KERNEL_SPT_TOQ


#if _KERNEL_TMAX_TPRI <= 1
/* %jp{�D��x�P��(�S��FIFO��)�Ȃ�D��x�Ǘ��s�v}*/
#define _KERNEL_TCB_TSKPRI			FALSE
#define _KERNEL_TCB_TSKBPRI			FALSE
#define _KERNEL_TCB_ITSKPRI			FALSE
#else
/* %jp{���I�ɗD��x��ύX����Ȃ�tskpri�̊Ǘ����K�v}*/
#define _KERNEL_TCB_TSKPRI			(_KERNEL_SPT_CHG_PRI || _KERNEL_SPT_MTX)
/* %jp{�~���[�e�b�N�X���T�|�[�g����Ȃ�tskbpri�̊Ǘ����K�v}*/
#define _KERNEL_TCB_TSKBPRI			_KERNEL_SPT_MTX
/* %jp{itskpri�͕K�{}*/
#define _KERNEL_TCB_ITSKPRI			TRUE
#endif

/* %jp{ref_tsk�ɂ��t�����̕K�v������Ȃ�܂߂�(ter_tsk�ł��v�邩��)} */
#define _KERNEL_TCB_TSKWAIT			_KERNEL_SPT_REF_TSK
#define _KERNEL_TCB_WOBJID			_KERNEL_SPT_REF_TSK	


/* %jp{�L���[�C���O�^�l�X�g���K�v�Ȃ�܂߂�} */
#define _KERNEL_TCB_ACTCNT			(_KERNEL_TMAX_ACTCNT > 0)
#define _KERNEL_TCB_WUPCNT			(_KERNEL_TMAX_WUPCNT > 0)
#define _KERNEL_TCB_SUSCNT			(_KERNEL_TMAX_SUSCNT > 0)

/**< %jp{���L����~���[�e�b�N�X�̃��X�g} */	
#define _KERNEL_TCB_MTXHDL			_KERNEL_SPT_MTX

/* %jp{E_OK�ȊO�̑҂������v��������ΕK�v} */
#define _KERNEL_TCB_ERCD			(_KERNEL_SPT_REL_WAI || _KERNEL_SPT_TER_TSK || _KERNEL_SPT_TMOUT || _KERNEL_SPT_DELOBJ)

/* %jp{�f�[�^�n���̕K�v�ȃI�u�W�F�N�g���g���Ȃ�K�v} */
#define _KERNEL_TCB_DATA			(_KERNEL_SPT_FLG || _KERNEL_SPT_DTQ || _KERNEL_SPT_MBX || _KERNEL_SPT_MPF || _KERNEL_SPT_MPL)

/* %jp{ID�̍����t�������ɕK�v} */
#define _KERNEL_TCB_TSKID			FALSE								/**< %jp{TCB��tskid���܂߂邩} */

/* %jp{�܂߂闝�R�����܂�Ȃ�?} */
#define _KERNEL_TCB_TSKATR			FALSE								/**< %jp{TCB��tskatr���܂߂邩} */

/* %jp{�^�X�N�̊g�������g��Ȃ��Ȃ�s�v} */
#define _KERNEL_TCB_EXINF			TRUE								/**< %jp{TCB��exinf���܂߂邩} */

#if !(_KERNEL_SPT_ACT_TSK) && !(_KERNEL_SPT_IACT_TSK) && !(_KERNEL_SPT_STA_TSK)
/* %jp{�^�X�N��������TA_ACT�ň�񂾂��N������Ȃ�A�������̕ێ��͕s�v} */
#define _KERNEL_TCB_TASK			FALSE								/**< %jp{TCB��task���܂߂邩} */
#define _KERNEL_TCB_STKSZ			FALSE								/**< %jp{TCB��tsksz���܂߂邩} */
#define _KERNEL_TCB_STK				FALSE								/**< %jp{TCB��tsk���܂߂邩} */
#define _KERNEL_TCB_ISP				FALSE								/**< %jp{TCB��isp���܂߂邩} */
#else
/* %jp{�A�[�L�e�N�`���ˑ��ŕK�v�ȏ����܂߂�} */
#define _KERNEL_TCB_TASK			TRUE								/**< %jp{TCB��task���܂߂邩} */
#define _KERNEL_TCB_STKSZ			_KERNEL_PROCATR_CTX_STKSZ			/**< %jp{TCB��tsksz���܂߂邩} */
#define _KERNEL_TCB_STK				_KERNEL_PROCATR_CTX_STK				/**< %jp{TCB��tsk���܂߂邩} */
#define _KERNEL_TCB_ISP				_KERNEL_PROCATR_CTX_ISP				/**< %jp{TCB��isp���܂߂邩} */
#endif

/* Task Exception Handling Routine */
#define _KERNEL_TCB_TEXSTAT			_KERNEL_SPT_TEX						/**< %jp{�^�X�N��O�������} */
#define _KERNEL_TCB_RASPTN			_KERNEL_SPT_TEX						/**< %jp{�^�X�N��O�����v��} */
#define _KERNEL_TCB_TEXATR			FALSE								/**< %jp{�^�X�N��O�������[�`������} */
#define _KERNEL_TCB_TEXRTN			_KERNEL_SPT_TEX						/**< %jp{�^�X�N��O�������[�`���̋N���Ԓn} */



/* ------------------------------------------------------------------ */
/*  Semaphore                                                         */
/* ------------------------------------------------------------------ */

/* Definitions */
#define _KERNEL_SEMCB_ALG_BLKARRAY	1
#define _KERNEL_SEMCB_ALG_PTRARRAY	2


/* Control block */
#define _KERNEL_SEMCB_ALGORITHM		_KERNEL_CFG_SEMCB_ALGORITHM
#define _KERNEL_SEMCB_BITFIELD		_KERNEL_CFG_SEMCB_BITFIELD

/* %jp{�u���b�N�z��œ��I����������ꍇ��RO�����͕s��} */
#if (_KERNEL_SEMCB_ALGORITHM == _KERNEL_SEMCB_ALG_BLKARRAY) && (_KERNEL_SPT_CRE_SEM || _KERNEL_SPT_ACRE_SEM)
#define _KERNEL_SEMCB_SPLIT_RO		FALSE
#else
#define _KERNEL_SEMCB_SPLIT_RO		_KERNEL_CFG_SEMCB_SPLIT_RO
#endif


#define _KERNEL_SEM_TMAX_SEMCNT		_KERNEL_TMAX_MAXSEM
#define _KERNEL_SEM_TBIT_SEMCNT		_KERNEL_MAXNUM2BIT(_KERNEL_SEM_TMAX_SEMCNT)


/* Attributes */
#define _KERNEL_SPT_SEM_TA_TFIFO	_KERNEL_CFG_SEM_TA_TFIFO
#define _KERNEL_SPT_SEM_TA_TPRI		_KERNEL_CFG_SEM_TA_TPRI


/* Member variables */
#define _KERNEL_SEMCB_QUE			TRUE
#define _KERNEL_SEMCB_SEMCNT		TRUE
#define _KERNEL_SEMCB_SEMATR		(_KERNEL_SPT_SEM_TA_TFIFO && _KERNEL_SPT_SEM_TA_TPRI)
#define _KERNEL_SEMCB_MAXSEM		_KERNEL_CFG_SEM_MAXSEM



/* ------------------------------------------------------------------ */
/*  Eventflags                                                        */
/* ------------------------------------------------------------------ */

/* Definitions */
#define _KERNEL_FLGCB_ALG_BLKARRAY	1
#define _KERNEL_FLGCB_ALG_PTRARRAY	2


/* Control block */
#define _KERNEL_FLGCB_ALGORITHM		_KERNEL_CFG_FLGCB_ALGORITHM
#define _KERNEL_FLGCB_BITFIELD		_KERNEL_CFG_FLGCB_BITFIELD

/* %jp{�u���b�N�z��œ��I���������̏ꍇ�ȊO��RO�����͕s��} */
#if !((_KERNEL_FLGCB_ALGORITHM == _KERNEL_FLGCB_ALG_BLKARRAY) && (!_KERNEL_SPT_CRE_FLG && !_KERNEL_SPT_ACRE_FLG))
#define _KERNEL_FLGCB_SPLIT_RO		FALSE
#else
#define _KERNEL_FLGCB_SPLIT_RO		_KERNEL_CFG_FLGCB_SPLIT_RO
#endif


/* Attributes */
#define _KERNEL_SPT_FLG_TA_TFIFO	_KERNEL_CFG_FLG_TA_TFIFO			/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_SPT_FLG_TA_TPRI		_KERNEL_CFG_FLG_TA_TPRI				/**< %jp{TA_TPRI�����ɑΉ�����} */
#define _KERNEL_SPT_FLG_TA_WSGL		_KERNEL_CFG_FLG_TA_WSGL				/**< %jp{TA_WSGL�����ɑΉ�����} */
#define _KERNEL_SPT_FLG_TA_WMUL		_KERNEL_CFG_FLG_TA_WMUL				/**< %jp{TA_WMUL�����ɑΉ�����} */
#define _KERNEL_SPT_FLG_TA_CLR		_KERNEL_CFG_FLG_TA_CLR				/**< %jp{TA_CLR�����ɑΉ�����} */


/* Member variables  */
#define _KERNEL_FLGCB_QUE			TRUE
#define _KERNEL_FLGCB_FLGPTN		TRUE

#if (!_KERNEL_CFG_FLG_TA_TFIFO || !_KERNEL_CFG_FLG_TA_TPRI) && (!_KERNEL_CFG_FLG_TA_WSGL || !_KERNEL_CFG_FLG_TA_WSGL) && !_KERNEL_CFG_FLG_TA_CLR
#define _KERNEL_FLGCB_FLGATR		FALSE
#else
#define _KERNEL_FLGCB_FLGATR		TRUE
#endif


/* ------------------------------------------------------------------ */
/*  Data queues                                                       */
/* ------------------------------------------------------------------ */

/* Definitions */
#define _KERNEL_DTQCB_ALG_BLKARRAY	1
#define _KERNEL_DTQCB_ALG_PTRARRAY	2


/* Control block */
#define _KERNEL_DTQCB_ALGORITHM		_KERNEL_CFG_DTQCB_ALGORITHM
#define _KERNEL_DTQCB_BITFIELD		_KERNEL_CFG_DTQCB_BITFIELD

/* %jp{�u���b�N�z��œ��I����������ꍇ��RO�����͕s��} */
#if (_KERNEL_DTQCB_ALGORITHM == _KERNEL_DTQCB_ALG_BLKARRAY) && (_KERNEL_SPT_CRE_DTQ || _KERNEL_SPT_ACRE_DTQ)
#define _KERNEL_DTQCB_SPLIT_RO		FALSE
#else
#define _KERNEL_DTQCB_SPLIT_RO		_KERNEL_CFG_DTQCB_SPLIT_RO
#endif

/* Configuration */
#define _KERNEL_SPT_DTQ_DTQCNT_ZERO		_KERNEL_CFG_DTQ_DTQCNT_ZERO		/**< %jp{�L���[�T�C�Y0�ɑΉ�����} */
#define _KERNEL_SPT_DTQ_DTQCNT_NONZERO	_KERNEL_CFG_DTQ_DTQCNT_NONZERO	/**< %jp{�L���[�T�C�Y��0�ɑΉ�����} */
#if !_KERNEL_SPT_DTQ_DTQCNT_ZERO && !_KERNEL_SPT_DTQ_DTQCNT_NONZERO
#error "!_KERNEL_SPT_DTQ_DTQCNT_ZERO && !_KERNEL_SPT_DTQ_DTQCNT_NONZERO"
#endif

/* Attribute */
#define _KERNEL_SPT_DTQ_TA_TFIFO	_KERNEL_CFG_DTQ_TA_TFIFO			/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_SPT_DTQ_TA_TPRI		_KERNEL_CFG_DTQ_TA_TPRI				/**< %jp{TA_TPRI�����ɑΉ�����} */

#define _KERNEL_DTQ_TMAX_DTQCNT		_KERNEL_TMAX_INT

/* Member variables  */
#define _KERNEL_DTQCB_SQUE			TRUE
#define _KERNEL_DTQCB_RQUE			TRUE
#define _KERNEL_DTQCB_SDTQCNT		TRUE
#define _KERNEL_DTQCB_HEAD			TRUE
#define _KERNEL_DTQCB_DTQATR		TRUE
#define _KERNEL_DTQCB_DTQCNT		TRUE
#define _KERNEL_DTQCB_DTQ			TRUE



/* ------------------------------------------------------------------ */
/*  Mailboxes                                                         */
/* ------------------------------------------------------------------ */

#define _KERNEL_MBXCB_ALG_BLKARRAY	1
#define _KERNEL_MBXCB_ALG_PTRARRAY	2

/* Attribute */
#define _KERNEL_SPT_MBX_TA_TFIFO	_KERNEL_CFG_MBX_TA_TFIFO		/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_SPT_MBX_TA_TPRI		_KERNEL_CFG_MBX_TA_TPRI			/**< %jp{TA_TPRI�����ɑΉ�����} */
#define _KERNEL_SPT_MBX_TA_MFIFO	_KERNEL_CFG_MBX_TA_MFIFO		/**< %jp{TA_MFIFO�����ɑΉ�����} */
#define _KERNEL_SPT_MBX_TA_MPRI		_KERNEL_CFG_MBX_TA_MPRI			/**< %jp{TA_MPRI�����ɑΉ�����} */

/* Control block */
#define _KERNEL_MBXCB_ALGORITHM		_KERNEL_CFG_MBXCB_ALGORITHM
#define _KERNEL_MBXCB_BITFIELD		_KERNEL_CFG_MBXCB_BITFIELD		/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */

/* %jp{�u���b�N�z��œ��I����������ꍇ��RO�����͕s��} */
#if (_KERNEL_MBXCB_ALGORITHM == _KERNEL_MBXCB_ALG_BLKARRAY) && (_KERNEL_SPT_CRE_MBX || _KERNEL_SPT_ACRE_MBX)
#define _KERNEL_MBXCB_SPLIT_RO		FALSE
#else
#define _KERNEL_MBXCB_SPLIT_RO		_KERNEL_CFG_MBXCB_SPLIT_RO
#endif


#define _KERNEL_MBXCB_QUE			TRUE
#define _KERNEL_MBXCB_MSGQUE		TRUE
#define _KERNEL_MBXCB_MBXATR		TRUE
#define _KERNEL_MBXCB_MAXMPRI		TRUE



/* ------------------------------------------------------------------ */
/*  Mutexes                                                           */
/* ------------------------------------------------------------------ */

#define _KERNEL_MTXCB_ALG_BLKARRAY	1
#define _KERNEL_MTXCB_ALG_PTRARRAY	2

/* Attribute */
#define _KERNEL_SPT_MTX_TA_TFIFO	_KERNEL_CFG_MTX_TA_TFIFO		/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_SPT_MTX_TA_TPRI		_KERNEL_CFG_MTX_TA_TPRI			/**< %jp{TA_TPRI�����ɑΉ�����} */
#define _KERNEL_SPT_MTX_TA_INHERIT	_KERNEL_CFG_MTX_TA_INHERIT		/**< %jp{TA_INHERIT�����ɑΉ�����} */
#define _KERNEL_SPT_MTX_TA_CEILING	_KERNEL_CFG_MTX_TA_CEILING		/**< %jp{TA_CEILING�����ɑΉ�����} */

/* Control block */
#define _KERNEL_MTXCB_ALGORITHM		_KERNEL_CFG_MTXCB_ALGORITHM
#define _KERNEL_MTXCB_BITFIELD		_KERNEL_CFG_MTXCB_BITFIELD		/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */

/* %jp{�u���b�N�z��œ��I����������ꍇ��RO�����͕s��} */
#if (_KERNEL_MTXCB_ALGORITHM == _KERNEL_MTXCB_ALG_BLKARRAY) && (_KERNEL_SPT_CRE_MTX || _KERNEL_SPT_ACRE_MTX)
#define _KERNEL_MTXCB_SPLIT_RO		FALSE
#else
#define _KERNEL_MTXCB_SPLIT_RO		_KERNEL_CFG_MTXCB_SPLIT_RO
#endif


#define _KERNEL_MTXCB_QUE			TRUE
#define _KERNEL_MTXCB_TSKHDL		TRUE
#define _KERNEL_MTXCB_MTXATR		TRUE
#define _KERNEL_MTXCB_NEXT			TRUE
#define _KERNEL_MTXCB_PREV			TRUE
#define _KERNEL_MTXCB_CEILPRI		TRUE


/* ---------------------------------------------- */
/*  Fixed-sized memory pools                      */
/* ---------------------------------------------- */


#define _KERNEL_MPF_ALG_CHAIN_PTR	1
#define _KERNEL_MPF_ALG_CHAIN_NUM	2

#define _KERNEL_MPFCB_ALG_BLKARRAY	1
#define _KERNEL_MPFCB_ALG_PTRARRAY	2


/* Attribute */
#define _KERNEL_SPT_MPF_TA_TFIFO	_KERNEL_CFG_MPF_TA_TFIFO		/**< %jp{TA_TFIFO�����ɑΉ�����} */
#define _KERNEL_SPT_MPF_TA_TPRI		_KERNEL_CFG_MPF_TA_TPRI			/**< %jp{TA_TPRI�����ɑΉ�����} */

#define _KERNEL_MPF_ALGORITHM		_KERNEL_CFG_MPF_ALGORITHM


/* Control block */
#define _KERNEL_MPFCB_ALGORITHM		_KERNEL_MPFCB_ALG_BLKARRAY
#define _KERNEL_MPFCB_BITFIELD		_KERNEL_CFG_MPFCB_BITFIELD		/**< %jp{�r�b�g�t�B�[���h�𗘗p����TCB�����k���邩} */

/* %jp{�u���b�N�z��œ��I����������ꍇ��RO�����͕s��} */
#if (_KERNEL_MPFCB_ALGORITHM == _KERNEL_MPFCB_ALG_BLKARRAY) && (_KERNEL_SPT_CRE_MPF || _KERNEL_SPT_ACRE_MPF)
#define _KERNEL_MPFCB_SPLIT_RO		FALSE
#else
#define _KERNEL_MPFCB_SPLIT_RO		_KERNEL_CFG_MPFCB_SPLIT_RO
#endif


#if _KERNEL_CFG_MPF_TMAX_BLKCNT <= 0
#define _KERNEL_MPF_TMAX_BLKCNT		_KERNEL_TMAX_UINT
#else
#define _KERNEL_MPF_TMAX_BLKCNT		_KERNEL_CFG_MPF_TMAX_BLKCNT
#endif

#if _KERNEL_CFG_MPF_TMAX_BLKSZ <= 0
#define _KERNEL_MPF_TMAX_BLKSZ		_KERNEL_TMAX_UINT
#else
#define _KERNEL_MPF_TMAX_BLKSZ		_KERNEL_CFG_MPF_TMAX_BLKSZ
#endif


#define _KERNEL_MPFCB_QUE			TRUE
#define _KERNEL_MPFCB_FREBLK		TRUE
#define _KERNEL_MPFCB_FBLKCNT		FALSE
#define _KERNEL_MPFCB_MPFATR		TRUE
#define _KERNEL_MPFCB_BLKCNT		TRUE
#define _KERNEL_MPFCB_BLKSZ			TRUE
#define _KERNEL_MPFCB_MPF			TRUE



/* ------------------------------------------------------------------ */
/*  System Time Management                                            */
/* ------------------------------------------------------------------ */

#define _KERNEL_FRACTIONAL_TIMTIC	_KERNEL_CFG_FRACTIONAL_TIMTIC	/**< %jp{�^�C���e�B�b�N�̕����w�������} */
#define _KERNEL_TIC_NUME			_KERNEL_CFG_TIC_NUME			/**< %jp{�f�t�H���g�̃^�C���e�B�b�N�����̕��q} */
#define _KERNEL_TIC_DENO			_KERNEL_CFG_TIC_DENO			/**< %jp{�f�t�H���g�̃^�C���e�B�b�N�����̕���} */


#define _KERNEL_TIMCB_TICDIV		TRUE
#define _KERNEL_TIMCB_TICMOD		_KERNEL_FRACTIONAL_TIMTIC
#define _KERNEL_TIMCB_TICDENO		_KERNEL_FRACTIONAL_TIMTIC
#define _KERNEL_TIMCB_TICCNT		_KERNEL_FRACTIONAL_TIMTIC
#define _KERNEL_TIMCB_TICNXT		TRUE

#define _KERNEL_TIMCB_SYSTIM		(_KERNEL_CFG_SET_TIM || _KERNEL_SPT_GET_TIM)



/* ------------------------------------------------------------------ */
/*  Cyclic Handlers                                                   */
/* ------------------------------------------------------------------ */

/* Definitions */
#define _KERNEL_CYCCB_ALG_BLKARRAY	1
#define _KERNEL_CYCCB_ALG_PTRARRAY	2

/* Control block */
#define _KERNEL_CYCCB_ALGORITHM		_KERNEL_CFG_CYCCB_ALGORITHM
#define _KERNEL_CYCCB_BITFIELD		_KERNEL_CFG_CYCCB_BITFIELD

/* %jp{�u���b�N�z��œ��I����������ꍇ��RO�����͕s��} */
#if (_KERNEL_CYCCB_ALGORITHM == _KERNEL_CYCCB_ALG_BLKARRAY) && (_KERNEL_SPT_CRE_CYC || _KERNEL_SPT_ACRE_CYC)
#define _KERNEL_CYCCB_SPLIT_RO		FALSE
#else
#define _KERNEL_CYCCB_SPLIT_RO		_KERNEL_CFG_CYCCB_SPLIT_RO
#endif

/* Attributes */
#define _KERNEL_SPT_CYC_TA_STA		_KERNEL_CFG_CYC_TA_STA
#define _KERNEL_SPT_CYC_TA_PHS		_KERNEL_CFG_CYC_TA_PHS

/* Member variables */
#define _KERNEL_CYCCB_TIMOBJ		TRUE
#define _KERNEL_CYCCB_CYCATR		TRUE
#define _KERNEL_CYCCB_EXINF			TRUE
#define _KERNEL_CYCCB_CYCHDR		TRUE
#define _KERNEL_CYCCB_CYCTIM		TRUE
#define _KERNEL_CYCCB_CYCPHS		TRUE



/* ------------------------------------------------------------------ */
/*  inh                                                               */
/* ------------------------------------------------------------------ */

#define _KERNEL_TMIN_INH_INHNO		_KERNEL_PROCATR_TMIN_INHNO
#define _KERNEL_TMAX_INH_INHNO		_KERNEL_PROCATR_TMAX_INHNO



/* ---------------------------------------------- */
/*  Interrupt Service Routines                    */
/* ---------------------------------------------- */

#define _KERNEL_ISRCB_ALG_BLKARRAY	1
#define _KERNEL_ISRCB_ALG_PTRARRAY	2

/* Control block */
#define _KERNEL_ISRCB_ALGORITHM		_KERNEL_CFG_ISRCB_ALGORITHM
#define _KERNEL_ISRCB_BITFIELD		_KERNEL_CFG_ISRCB_BITFIELD

/* %jp{�u���b�N�z��œ��I����������ꍇ��RO�����͕s��} */
#if (_KERNEL_ISRCB_ALGORITHM == _KERNEL_ISRCB_ALG_BLKARRAY) && (_KERNEL_SPT_CRE_ISR || _KERNEL_SPT_ACRE_ISR)
#define _KERNEL_ISRCB_SPLIT_RO		FALSE
#else
#define _KERNEL_ISRCB_SPLIT_RO		_KERNEL_CFG_MBXCB_SPLIT_RO
#endif

#define _KERNEL_ISRCB_NEXT			TRUE
#define _KERNEL_ISRCB_EXINF			TRUE
#define _KERNEL_ISRCB_ISR			TRUE


#endif	/* _KERNEL__parser__parsknl_h__ */



/* end of file */
