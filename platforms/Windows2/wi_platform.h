#include "kernel.h"

#if !defined(__WI_PLATFORMS_H__)
#define __WI_PLATFORMS_H__

#ifdef WIN32_GUI_SIM
extern ER wi_init();
extern ER wi_cre_tsk(ID tskid, const T_CTSK *pk_ctsk);
extern ER wi_dly_tsk(DLYTIME dlytim);
extern ER wi_act_tsk(ID tskid);
extern ER wi_sta_tsk(ID tskid, VP_INT stacd);
extern ER wi_del_tsk(ID tskid);
extern ER wi_ref_tsk(ID tskid, T_RTSK * pk_rtsk);
extern ER wi_get_tid(ID *p_tskid);
extern ER wi_cre_mpl(ID mplid, const T_CMPL *pk_cmpl);
extern ER wi_tget_mpl(ID mplid, UINT blksz, VP *p_blk, TMO tmout);
extern ER wi_rel_mpl(ID mplid, VP blk);
extern ER wi_del_mpl(ID mplid);
extern ER wi_ref_mpl(ID mpfid, T_RMPL *pk_rmpl);
extern ER wi_cre_cyc(ID cycid, const T_CCYC *pk_ccyc);
extern ER wi_stp_cyc(ID cycid);
extern ER wi_del_cyc(ID cycid);
extern ER wi_sta_cyc(ID cycid);
extern ER wi_ref_cyc(ID cycid, T_RCYC *pk_rcyc);
extern ER wi_loc_cpu(void);
extern ER wi_iloc_cpu(void);
extern ER wi_unl_cpu(void);
extern ER wi_iunl_cpu(void);
extern ER wi_rel_wai(ID tskid);
extern ER wi_irel_wai(ID tskid);
extern ER wi_cre_sem(ID semid, const T_CSEM *pk_csem);
extern ER wi_del_sem(ID semid);
extern ER wi_sig_sem(ID semid);
extern ER wi_wai_sem(ID semid);
extern ER wi_pol_sem(ID semid);
extern ER wi_cre_flg(ID flgid, const T_CFLG *pk_cflg);
extern ER wi_del_flg(ID flgid);
extern ER wi_set_flg(ID flgid, FLGPTN setptn);
extern ER wi_iset_flg(ID flgid, FLGPTN setptn);
extern ER wi_wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
extern ER wi_twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
extern ER wi_clr_flg(ID flgid, FLGPTN clrptn);
extern ER wi_cre_mbx(ID mbxid, const T_CMBX *pk_cmbx);
extern ER wi_del_mbx(ID mbxid);
extern ER wi_snd_msg(ID mbxid, T_MSG *pk_msg);
extern ER wi_snd_mbx(ID mbxid, T_MSG *pk_msg);
extern ER wi_rcv_msg(ID mbxid, T_MSG **ppk_msg);
extern ER wi_rcv_mbx(ID mbxid, T_MSG **ppk_msg);
extern ER wi_prcv_mbx(ID mbxid, T_MSG **ppk_msg);
extern ER wi_trcv_msg(ID mbxid, T_MSG **ppk_msg, TMO tmout);
extern ER wi_ref_mbx(ID mbxid, T_RMBX *pk_rmbx);

extern ER wi_cycle_timer(ID id, const T_CTSK *pk_ctsk);
extern void wi_cycle_thread();


#endif

#endif	// !defined(__WI_PLATFORMS_H__)


