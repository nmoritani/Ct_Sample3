#include "CtPlatforms.h"

#ifdef LINUX_GUI_SIM
#include "li_platform.h"
#define		CT_PLATFOMR_INIT			(li_init)
#define		CT_PLATFORM_CRE_TSK			(li_cre_tsk)
#define		CT_PLATFORM_DLY_TSK			(li_dly_tsk)
#define		CT_PLATFORM_ACT_TSK			(li_act_tsk)
#define		CT_PLATFORM_STA_TSK			(li_sta_tsk)
#define		CT_PLATFORM_DEL_TSK			(li_del_tsk)
#define		CT_PLATFORM_REF_TSK			(li_ref_tsk)
#define		CT_PLATFORM_GET_TID			(li_get_tid)
#define		CT_PLATFORM_CRE_MPL			(li_cre_mpl)
#define		CT_PLATFORM_TGET_MPL		(li_tget_mpl)
#define		CT_PLATFORM_REL_MPL			(li_rel_mpl)
#define		CT_PLATFORM_DEL_MPL			(li_del_mpl)
#define		CT_PLATFORM_REF_MPL			(li_ref_mpl)
#define		CT_PLATFORM_CRE_CYC			(li_cre_cyc)
#define		CT_PLATFORM_STP_CYC			(li_stp_cyc)
#define		CT_PLATFORM_DEL_CYC			(li_del_cyc)
#define		CT_PLATFORM_STA_CYC			(li_sta_cyc)
#define		CT_PLATFORM_REF_CYC			(li_ref_cyc)
#define		CT_PLATFORM_LOC_CPU			(li_loc_cpu)
#define		CT_PLATFORM_ILOC_CPU		(li_iloc_cpu)
#define		CT_PLATFORM_UNL_CPU			(li_unl_cpu)
#define		CT_PLATFORM_IUNL_CPU		(li_iunl_cpu)
#define		CT_PLATFORM_REL_WAI			(li_rel_wai)
#define		CT_PLATFORM_IREL_WAI		(li_irel_wai)
#define		CT_PLATFORM_CRE_SEM			(li_cre_sem)
#define		CT_PLATFORM_DEL_SEM			(li_del_sem)
#define		CT_PLATFORM_SIG_SEM			(li_sig_sem)
#define		CT_PLATFORM_WAI_SEM			(li_wai_sem)
#define		CT_PLATFORM_POL_SEM			(li_pol_sem)
#define		CT_PLATFORM_CRE_FLG			(li_cre_flg)
#define		CT_PLATFORM_DEL_FLG			(li_del_flg)
#define		CT_PLATFORM_SET_FLG			(li_set_flg)
#define		CT_PLATFORM_ISET_FLG		(li_iset_flg)
#define		CT_PLATFORM_WAI_FLG			(li_wai_flg)
#define		CT_PLATFORM_TWAI_FLG		(li_twai_flg)
#define		CT_PLATFORM_CLR_FLG			(li_clr_flg)
#define		CT_PLATFORM_CRE_MBX			(li_cre_mbx)
#define		CT_PLATFORM_DEL_MBX			(li_del_mbx)
#define		CT_PLATFORM_SND_MSG			(li_snd_msg)
#define		CT_PLATFORM_SND_MBX			(li_snd_mbx)
#define		CT_PLATFORM_RCV_MSG			(li_rcv_msg)
#define		CT_PLATFORM_RCV_MBX			(li_rcv_mbx)
#define		CT_PLATFORM_PRCV_MBX		(li_prcv_mbx)
#define		CT_PLATFORM_TRCV_MSG		(li_trcv_msg)
#define		CT_PLATFORM_REF_MBX			(li_ref_mbx)
#define		CT_PLATFORM_CYCLETIMER		(li_cycle_timer)
#define		CT_PLATFORM_CYCLETHREAD		(li_cycle_thread)

#elif defined(WIN32_GUI_SIM)
#include "wi_platform.h"
#define		CT_PLATFOMR_INIT			(wi_init)
#define		CT_PLATFORM_CRE_TSK			(wi_cre_tsk)
#define		CT_PLATFORM_DLY_TSK			(wi_dly_tsk)
#define		CT_PLATFORM_ACT_TSK			(wi_act_tsk)
#define		CT_PLATFORM_STA_TSK			(wi_sta_tsk)
#define		CT_PLATFORM_DEL_TSK			(wi_del_tsk)
#define		CT_PLATFORM_REF_TSK			(wi_ref_tsk)
#define		CT_PLATFORM_GET_TID			(wi_get_tid)
#define		CT_PLATFORM_CRE_MPL			(wi_cre_mpl)
#define		CT_PLATFORM_TGET_MPL		(wi_tget_mpl)
#define		CT_PLATFORM_REL_MPL			(wi_rel_mpl)
#define		CT_PLATFORM_DEL_MPL			(wi_del_mpl)
#define		CT_PLATFORM_REF_MPL			(wi_ref_mpl)
#define		CT_PLATFORM_CRE_CYC			(wi_cre_cyc)
#define		CT_PLATFORM_STP_CYC			(wi_stp_cyc)
#define		CT_PLATFORM_DEL_CYC			(wi_del_cyc)
#define		CT_PLATFORM_STA_CYC			(wi_sta_cyc)
#define		CT_PLATFORM_REF_CYC			(wi_ref_cyc)
#define		CT_PLATFORM_LOC_CPU			(wi_loc_cpu)
#define		CT_PLATFORM_ILOC_CPU		(wi_iloc_cpu)
#define		CT_PLATFORM_UNL_CPU			(wi_unl_cpu)
#define		CT_PLATFORM_IUNL_CPU		(wi_iunl_cpu)
#define		CT_PLATFORM_REL_WAI			(wi_rel_wai)
#define		CT_PLATFORM_IREL_WAI		(wi_irel_wai)
#define		CT_PLATFORM_CRE_SEM			(wi_cre_sem)
#define		CT_PLATFORM_DEL_SEM			(wi_del_sem)
#define		CT_PLATFORM_SIG_SEM			(wi_sig_sem)
#define		CT_PLATFORM_WAI_SEM			(wi_wai_sem)
#define		CT_PLATFORM_POL_SEM			(wi_pol_sem)
#define		CT_PLATFORM_CRE_FLG			(wi_cre_flg)
#define		CT_PLATFORM_DEL_FLG			(wi_del_flg)
#define		CT_PLATFORM_SET_FLG			(wi_set_flg)
#define		CT_PLATFORM_ISET_FLG		(wi_iset_flg)
#define		CT_PLATFORM_WAI_FLG			(wi_wai_flg)
#define		CT_PLATFORM_TWAI_FLG		(wi_twai_flg)
#define		CT_PLATFORM_CLR_FLG			(wi_clr_flg)
#define		CT_PLATFORM_CRE_MBX			(wi_cre_mbx)
#define		CT_PLATFORM_DEL_MBX			(wi_del_mbx)
#define		CT_PLATFORM_SND_MSG			(wi_snd_msg)
#define		CT_PLATFORM_SND_MBX			(wi_snd_mbx)
#define		CT_PLATFORM_RCV_MSG			(wi_rcv_msg)
#define		CT_PLATFORM_RCV_MBX			(wi_rcv_mbx)
#define		CT_PLATFORM_PRCV_MBX		(wi_prcv_mbx)
#define		CT_PLATFORM_TRCV_MSG		(wi_trcv_msg)
#define		CT_PLATFORM_REF_MBX			(wi_ref_mbx)

#define		CT_PLATFORM_CYCLETIMER		(wi_cycle_timer)
#define		CT_PLATFORM_CYCLETHREAD		(wi_cycle_thread)

#else				//とりあえずitronとWindows用
#define		CT_PLATFORM_DLY_TSK			(dly_tsk)
#define		CT_PLATFORM_WAI_FLG			(wai_flg)
#define		CT_PLATFORM_SET_FLG			(set_flg)
#define		CT_PLATFORM_ACT_TSK			(act_tsk)
#define		CT_PLATFORM_GET_TID			(get_tid)
#define		CT_PLATFORM_TGET_MPL		(tget_mpl)
#define		CT_PLATFORM_REL_MPL			(rel_mpl)
#define		CT_PLATFORM_RCV_MBX			(rcv_msg)
#define		CT_PLATFORM_SND_MBX			(snd_msg)
#define		CT_PLATFORM_SIG_SEM			(sig_sem)
#define		CT_PLATFORM_PRCV_MBX		(prcv_mbx)
#define		CT_PLATFORM_REF_MBX			(ref_mbx)
#define		CT_PLATFORM_WAI_SEM			(wai_sem)
#define		CT_PLATFORM_TWAI_FLG		(twai_flg)
#define		CT_PLATFORM_CLR_FLG			(clr_flg)
#define		CT_PLATFORM_STA_CYC			(sta_cyc)
#define		CT_PLATFORM_REF_CYC			(ref_cyc)
#define		CT_PLATFORM_POL_SEM			(pol_sem)
#define		CT_PLATFORM_ISET_FLG		(iset_flg)
#define		CT_PLATFORM_REF_MPL			(ref_mpl)
#define		CT_PLATFORM_UNL_CPU			(unl_cpu)
#define		CT_PLATFORM_IUNL_CPU		(iunl_cpu)
#define		CT_PLATFORM_LOC_CPU			(loc_cpu)
#define		CT_PLATFORM_ILOC_CPU		(iloc_cpu)
#define		CT_PLATFORM_SND_MSG			(snd_msg)
#define		CT_PLATFORM_RCV_MSG			(rcv_msg)
#endif

#ifdef WIN32
#include "WinDrawTask.h"
#endif
#include "CtMainTask.h"
#include "CtDrawTask.h"
#include "IoTask.h"


void ct_start(void)
{
	//! 生成したタスクをを起動する.
	ct_sta_tsk(TSKID_WINITRON, 0);
	ct_sta_tsk(TSKID_IO_TASK, 0);
}



void ct_start_cycletimer()
{
	static const T_CTSK ct_cycle_task = { TA_HLNG | TA_STA, 0, CT_PLATFORM_CYCLETHREAD, 50, 0x4000, 0 };
	CT_PLATFORM_CYCLETIMER(TSKID_CYCTIMER, &ct_cycle_task);
}



void ct_init_platforms()
{
#ifdef WIN32
	static const T_CTSK	ctsk = { TA_HLNG, 0, SimulatorWindowDraw, 1, 0, 0 };
#endif
	static const T_CTSK ct_main_task = { TA_HLNG, 0, Ct_MainTask, 50, 0x4000, 0 };
	static const T_CTSK ct_draw_task = { TA_HLNG, 0, Ct_DrawTask, 40, 0x2000, 0 };
	static const T_CTSK io_task = { TA_HLNG, 0, IoTask,      10, 0x1000, 0 };

//	static const T_CMPL ct_mpl = { TA_TFIFO, 0x80000, 0 };
//	static const T_CMPL ct_fastmpl = { TA_TFIFO, 0x80000, 0 };
//	static const T_CMPL gfxres_mpl = { TA_TFIFO, GFX_RES_SIZE, GUI_WORK_START };
//	static const T_CMPL guiwork_mpl = { TA_TFIFO, GUI_WORK_SIZE, GFX_RES_START };

	static const T_CMBX ct_main_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	static const T_CMBX ct_draw_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	static const T_CMBX io_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	static const T_CMBX win_draw_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };				//WINDOWSアプリ側のウィンドウ描画更新用

	static const T_CSEM ct_sem_timer = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_receiver = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_object = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_synchro = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_fontapi = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_draw = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_create_cache = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_context = { TA_TFIFO, 1, 1 };

	static const T_CCYC ct_cyc = { TA_HLNG, 0, (void(*)())((CtCycHandler)),{ 0, 10 }, 0 };
	static const T_CCYC avdf_cyc = { TA_HLNG | TA_STA, 0, (void(*)())((AvdfCycHandler)),{ 0, 14 }, 0 };	// 疑似AVDFタスク (本来は16.6ms周期だが16にすると動作周期が16,32とバラつくため14に設定)

	// Flag definition
	static const T_CFLG ct_flg_main = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG ct_flg_draw = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG ct_flg_synchro = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };

	CT_PLATFOMR_INIT();

	//! iTRONサービスコールの初期処理.
	//! アプリケーションの起動タスクを生成する.
#ifdef WIN32
	ct_cre_tsk(TSKID_WINITRON, &ctsk);
#endif

	// メモリプール生成
//	ct_cre_mpl(CT_MPL_ID, &ct_mpl);
//	ct_cre_mpl(CT_FASTMPL_ID, &ct_fastmpl);
//	ct_cre_mpl(GFX_RESMPL_ID, &gfxres_mpl);
//	ct_cre_mpl(GUI_WORKMPL_ID, &guiwork_mpl);

	// タスク生成
	ct_cre_tsk(CT_MAIN_TSKID, &ct_main_task);
	ct_cre_tsk(CT_DRAW_TSKID, &ct_draw_task);
	ct_cre_tsk(TSKID_IO_TASK, &io_task);

	// メールボックス生成
	ct_cre_mbx(CT_MBXID_MAIN, &ct_main_mbx);
	ct_cre_mbx(CT_MBXID_DRAW, &ct_draw_mbx);
	ct_cre_mbx(MBXID_IO_TASK, &io_mbx);
	ct_cre_mbx(MBXID_WIN_DRAW_TASK, &win_draw_mbx);

	// セマフォ 生成
	ct_cre_sem(CT_SEMID_TIMER, &ct_sem_timer);
	ct_cre_sem(CT_SEMID_RECEIVER, &ct_sem_receiver);
	ct_cre_sem(CT_SEMID_OBJECT, &ct_sem_object);
	ct_cre_sem(CT_SEMID_SYNCHRO, &ct_sem_synchro);
	ct_cre_sem(GDI_SEMID_FONTAPI, &gdi_sem_fontapi);
	ct_cre_sem(GDI_SEMID_DRAW, &gdi_sem_draw);
	ct_cre_sem(GDI_SEMID_CREATE_CACHE, &gdi_sem_create_cache);
	ct_cre_sem(GDI_SEMID_CONTEXT, &gdi_sem_context);

	// Flag definition
	ct_cre_flg(CT_FLGID_MAINTASK, &ct_flg_main);
	ct_cre_flg(CT_FLGID_DRAWTASK, &ct_flg_draw);
	ct_cre_flg(CT_FLGID_SYNCHRO, &ct_flg_synchro);

		// Cyclic Handler
	ct_cre_cyc(CT_CYC_ID, &ct_cyc); // For AplTimerService
	ct_cre_cyc(AVDF_CYC_ID, &avdf_cyc);

	ct_start_cycletimer();
}


ER ct_cre_tsk(ID tskid, const T_CTSK * pk_ctsk)
{
	return CT_PLATFORM_CRE_TSK(tskid, pk_ctsk);
}

ER	ct_dly_tsk( DLYTIME dlytim )
{
	return	CT_PLATFORM_DLY_TSK(dlytim);
}

ER	ct_wai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn )
{
	return	CT_PLATFORM_WAI_FLG(flgid, waiptn, wfmode, p_flgptn);
}

ER	ct_set_flg( ID flgid, FLGPTN setptn )
{
	return	CT_PLATFORM_SET_FLG(flgid, setptn);
}

ER	ct_act_tsk( ID tskid )
{
	return	CT_PLATFORM_ACT_TSK(tskid);
}

ER ct_sta_tsk(ID tskid, VP_INT stacd)
{
	return CT_PLATFORM_STA_TSK(tskid, stacd);
}

ER	ct_get_tid( ID *p_tskid )
{
	return	CT_PLATFORM_GET_TID(p_tskid);
}

ER	ct_cre_mpl(ID mplid, const T_CMPL *pk_cmpl)
{
	return CT_PLATFORM_CRE_MPL(mplid, pk_cmpl);
}

ER	ct_tget_mpl( ID mplid, UINT blksz, VP *p_blk, TMO tmout )
{
	return	CT_PLATFORM_TGET_MPL(mplid, blksz, p_blk, tmout);
}

ER	ct_rel_mpl(ID mplid, VP blk)
{
	return	CT_PLATFORM_REL_MPL(mplid, blk);
}

ER	ct_sig_sem( ID semid )
{
	return	CT_PLATFORM_SIG_SEM(semid);
}

ER	ct_wai_sem( ID semid )
{
	return	CT_PLATFORM_WAI_SEM(semid);
}

ER	ct_twai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout )
{
	return	CT_PLATFORM_TWAI_FLG(flgid, waiptn, wfmode, p_flgptn, tmout);
}

ER	ct_clr_flg( ID flgid, FLGPTN clrptn )
{
	return	CT_PLATFORM_CLR_FLG(flgid, clrptn);
}

ER	ct_sta_cyc( ID cycid )
{
	return	CT_PLATFORM_STA_CYC(cycid);
}

ER	ct_ref_cyc( ID cycid, T_RCYC *pk_rcyc )
{
	return	CT_PLATFORM_REF_CYC(cycid, pk_rcyc);
}

ER	ct_pol_sem( ID semid )
{
	return	CT_PLATFORM_POL_SEM(semid);
}

ER ct_cre_flg(ID flgid, const T_CFLG * pk_cflg)
{
	return CT_PLATFORM_CRE_FLG(flgid, pk_cflg);
}

ER	ct_iset_flg( ID flgid, FLGPTN setptn )
{
	return	CT_PLATFORM_ISET_FLG(flgid, setptn);
}

ER	ct_ref_mpl( ID mpfid, T_RMPL *pk_rmpl )
{
	return	CT_PLATFORM_REF_MPL(mpfid, pk_rmpl);
}

ER	ct_unl_cpu( void )
{
	return	CT_PLATFORM_UNL_CPU();
}

ER	ct_iunl_cpu(void)
{
	return	CT_PLATFORM_IUNL_CPU();
}

ER	ct_loc_cpu( void )
{
	return	CT_PLATFORM_LOC_CPU();
}

ER	ct_iloc_cpu(void)
{
	return	CT_PLATFORM_ILOC_CPU();
}

ER	ct_cre_cyc(ID cycid, const T_CCYC *pk_ccyc)
{
	return CT_PLATFORM_CRE_CYC(cycid, pk_ccyc);
}

ER	ct_stp_cyc(ID cycid)
{
	return CT_PLATFORM_STP_CYC(cycid);
}

ER	ct_irel_wai(ID tskid)
{
	return CT_PLATFORM_IREL_WAI(tskid);
}

ER ct_cre_sem(ID semid, const T_CSEM * pk_csem)
{
	return CT_PLATFORM_CRE_SEM(semid, pk_csem);
}

ER	ct_del_sem(ID semid)
{
	return CT_PLATFORM_DEL_SEM(semid);
}

ER	ct_del_flg(ID flgid)
{
	return CT_PLATFORM_DEL_FLG(flgid);
}

ER	ct_del_cyc(ID cycid)
{
	return CT_PLATFORM_DEL_CYC(cycid);
}

ER	ct_del_tsk(ID tskid)
{
	return CT_PLATFORM_DEL_TSK(tskid);
}

ER	ct_del_mpl(ID mplid)
{
	return CT_PLATFORM_DEL_MPL(mplid);
}

ER	ct_ref_tsk(ID tskid, T_RTSK *pk_rtsk) 
{
	return CT_PLATFORM_REF_TSK(tskid, pk_rtsk);
}

ER	ct_rel_wai(ID tskid) 
{
	return CT_PLATFORM_REL_WAI(tskid);
}

//メールボックス
ER	ct_cre_mbx(ID mbxid, const T_CMBX *pk_cmbx)
{
	return CT_PLATFORM_CRE_MBX(mbxid, pk_cmbx);
}

ER	ct_del_mbx(ID mbxid)
{
	return CT_PLATFORM_DEL_MBX(mbxid);
}

ER	ct_snd_msg(ID mbxid, T_MSG *pk_msg)
{
	return	CT_PLATFORM_SND_MSG(mbxid, pk_msg);
}

ER	ct_rcv_msg(ID mbxid, T_MSG **ppk_msg)
{
	return	CT_PLATFORM_RCV_MSG(mbxid, ppk_msg);
}

ER	ct_snd_mbx(ID mbxid, T_MSG *pk_msg)
{
	return	CT_PLATFORM_SND_MBX(mbxid, pk_msg);
}

ER	ct_rcv_mbx(ID mbxid, T_MSG **ppk_msg)
{
	return	CT_PLATFORM_RCV_MBX(mbxid, ppk_msg);
}

ER	ct_prcv_mbx(ID mbxid, T_MSG **ppk_msg)
{
	return	CT_PLATFORM_PRCV_MBX(mbxid, ppk_msg);
}

ER	ct_trcv_msg(ID mbxid, T_MSG **ppk_msg, TMO tmout)
{
	return CT_PLATFORM_TRCV_MSG(mbxid, ppk_msg, tmout);
}

ER	ct_ref_mbx(ID mbxid, T_RMBX *pk_rmbx)
{
	return	CT_PLATFORM_REF_MBX(mbxid, pk_rmbx);
}


//sns_ctx();
