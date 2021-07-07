/**
*	Copyright (c) 2018  Panasonic Corporation, All rights reserved
*	$Id$
*
*	@file
*	@brief	CtPlatforms.h
*/

#include "kernel.h"
#include "kernel_id.h"

#if !defined(__CT_PLATFORMS_H__)
#define __CT_PLATFORMS_H__

#if 0
#define	TWF_ANDW		0x0000			//!< AND待ち.
#define	TWF_ORW 		0x0002			//!< OR待ち.
#define E_TMOUT 		(-50)			//!< ポーリング失敗またはタイムアウト.
#define	TBIT_FLGPTN		32				//!< イベントフラグのビット数.
#define	TCYC_STP		0x00			//!< 周期ハンドラが動作していない.

typedef int				W;
typedef	int				ID;				//!< ID番号.
typedef	int				ER;				//!< エラーコード.
typedef int				BOOL;
typedef int				INT;			//!< 符号付き整数.
typedef unsigned int	UINT;			//!< 符号無し整数.
typedef unsigned int	UW;
typedef	unsigned int	FLGPTN;			//!< イベントフラグ・パターン.
typedef unsigned int	uint32;
typedef unsigned int	size_t;

typedef	INT				ID;				//!< ID番号.
typedef	INT				ER;				//!< エラーコード.
typedef UINT			STAT;			//!< 符号無し整数.
typedef	SYSTIME			RELTIM;			//!< 周期ハンドラの時間.

typedef struct {
	ID 					wtskid;			//!< メールボックス待ち行列の先頭のタスクのID番号.
	T_MSG				*pk_msg;		//!< メッセージキューの先頭のメッセージパケットのアドレス.
} T_RMBX;

typedef struct {
	short				utime;			//!< 上位16ビット.
	unsigned long		ltime;			//!< 下位32ビット.
} SYSTIME;

typedef struct {
	ID 					wtskid;			//!< 可変長メモリプールの待ち行列の先頭のタスクのID番号.
	INT	/*SIZE*/		fmplsz;			//!< 可変長メモリプールの空き領域の合計サイズ.
	UINT				fblksz;			//!< 獲得可能な最大の連続空き領域のサイズ.
} T_RMPL;

typedef struct {
	STAT				cycstat;		//!< 周期ハンドラの動作状態.
	RELTIM				lefttim; 		//!< 次の起動周期までの時間.
} T_RCYC;


#define TMO_FEVR			(-1)		//!< 永久待ち.
#define E_OK				0			//!< 正常終了.

#define TRUE				1
#define FALSE				0

#define E_OK				0			//!< 正常終了.
#define E_CTX				(-25)		//!< コンテキストエラー.
#define	NULL				0
#endif

typedef int BOOL;
#define TRUE	1
#define FALSE	0

typedef unsigned int	uint32;
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

	extern void CtCycHandler(VP_INT exinf);
	extern void AvdfCycHandler(VP_INT exinf);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

extern void ct_init_platforms();
extern void ct_start(void);


////////////////////////////////////////////////////////////
extern ER ct_cre_tsk(ID tskid, const T_CTSK *pk_ctsk);
extern ER ct_dly_tsk(DLYTIME dlytim);
extern ER ct_act_tsk(ID tskid);
extern ER ct_sta_tsk(ID tskid, VP_INT stacd);
extern ER ct_del_tsk(ID tskid);
extern ER ct_ref_tsk(ID tskid, T_RTSK * pk_rtsk);
extern ER ct_get_tid(ID *p_tskid);
extern ER ct_tget_mpl(ID mplid, UINT blksz, VP *p_blk, TMO tmout);
extern ER ct_cre_mpl(ID mplid, const T_CMPL *pk_cmpl);
extern ER ct_rel_mpl(ID mplid, VP blk);
extern ER ct_del_mpl(ID mplid);
extern ER ct_ref_mpl(ID mpfid, T_RMPL *pk_rmpl);
extern ER ct_cre_cyc(ID cycid, const T_CCYC *pk_ccyc);
extern ER ct_stp_cyc(ID cycid);
extern ER ct_del_cyc(ID cycid);
extern ER ct_sta_cyc(ID cycid);
extern ER ct_ref_cyc(ID cycid, T_RCYC *pk_rcyc);
extern ER ct_loc_cpu(void);
extern ER ct_iloc_cpu(void);
extern ER ct_unl_cpu(void);
extern ER ct_iunl_cpu(void);
extern ER ct_rel_wai(ID tskid);
extern ER ct_irel_wai(ID tskid);
extern ER ct_cre_sem(ID semid, const T_CSEM *pk_csem);
extern ER ct_del_sem(ID semid);
extern ER ct_sig_sem(ID semid);
extern ER ct_wai_sem(ID semid);
extern ER ct_pol_sem(ID semid);
extern ER ct_cre_flg(ID flgid, const T_CFLG *pk_cflg);
extern ER ct_del_flg(ID flgid);
extern ER ct_set_flg(ID flgid, FLGPTN setptn);
extern ER ct_iset_flg(ID flgid, FLGPTN setptn);
extern ER ct_wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
extern ER ct_twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
extern ER ct_clr_flg(ID flgid, FLGPTN clrptn);
extern ER ct_cre_mbx(ID mbxid, const T_CMBX *pk_cmbx);
extern ER ct_del_mbx(ID mbxid);
extern ER ct_snd_msg(ID mbxid, T_MSG *pk_msg);
extern ER ct_snd_mbx(ID mbxid, T_MSG *pk_msg);
extern ER ct_rcv_msg(ID mbxid, T_MSG **ppk_msg);
extern ER ct_rcv_mbx(ID mbxid, T_MSG **ppk_msg);
extern ER ct_prcv_mbx(ID mbxid, T_MSG **ppk_msg);
extern ER ct_trcv_msg(ID mbxid, T_MSG **ppk_msg, TMO tmout);
extern ER ct_ref_mbx(ID mbxid, T_RMBX *pk_rmbx);


#endif // !defined(__CT_PLATFORMS_H__)


