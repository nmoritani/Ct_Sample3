/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron3.c
 *
 *	@brief	iTRON(Ver3.0)のサービスコール.
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <stdio.h>
#include "kprintf.h"
#include "wi_config.h"

#ifdef	__ITRON3__
#include "win_itron3.h"
#include "wi_task.h"
#include "wi_semaphore.h"
#include "wi_event_flag.h"
#include "wi_mail_box.h"
#include "wi_message_buffer.h"
#include "wi_rendezvous_port.h"
#include "wi_fixed_mempool.h"
#include "wi_variable_mempool.h"
#include "wi_cycle_handler.h"
#include "wi_alarm_handler.h"
#include "wi_systemmgr.h"
#include "wi_interrupt.h"

/***************************************
 *
 * タスク管理機能.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	タスクの生成.
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[in]	pk_ctsk	タスク生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_tsk( ID tskid, const T_CTSK *pk_ctsk )
{
	ER			ercd;
	WITSKOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_ctsk ){
		return E_PAR;
	}
	//! タスク生成情報をコピーする.
	memset( &obj, 0, sizeof(WITSKOBJ) );
	obj.TaskAtr   = pk_ctsk->tskatr;
	obj.TaskAdr   = pk_ctsk->task;
	obj.TaskPri   = pk_ctsk->itskpri;
	obj.InitPri   = pk_ctsk->itskpri;
	obj.StackSize = pk_ctsk->stksz;
	obj.ExtInfo   = pk_ctsk->exinf;

	wi_CommonLock();

	//! タスクを生成する.
	ercd = wi_CreateTask( tskid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの削除.
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! タスクを削除する.
	ercd = wi_DeleteTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの起動.
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[in]	stacd	タスク起動コード.
 *
 *	@retval	エラーコード.
 */
ER		sta_tsk( ID tskid, VP_INT stacd )
{
	ER ercd;

	wi_CommonLock();

	//! タスクを起動する.
	ercd = wi_StartTask( tskid, (DWORD)stacd, TRUE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	自タスクの終了.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	ext_tsk( void )
{
	//! タスクを終了させる.
	wi_ExitTask();
}

/****************************************************************************/
/*!
 *	@brief	自タスクの終了と削除.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	exd_tsk( void )
{
	//! タスクを終了させてコンテキストを削除する.
	wi_ExpendTask();
}

/****************************************************************************/
/*!
 *	@brief	タスクの強制終了.
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		ter_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! タスクを強制終了する.
	ercd = wi_TermTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスク優先度の変更.
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[in]	tskpri	タスク優先度.
 *
 *	@retval	エラーコード.
 */
ER		chg_pri( ID tskid, PRI tskpri )
{
	ER ercd;

	wi_CommonLock();

	//! タスクの優先度を変更する.
	ercd = wi_ChangeTaskPriority( tskid, tskpri );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの状態参照.
 *
 *	@param	[in]	pk_rtsk	タスク状態を格納する領域のポインタ.
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_tsk( T_RTSK *pk_rtsk, ID tskid )
{
	ER			ercd;
	WITSKSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rtsk ){
		return E_PAR;
	}
	wi_CommonLock();

	//! 取得したタスクの料体を戻り値として構造体にセットする.
	ercd = wi_RefarenceTask( tskid, &sts );
	if( ercd == E_OK ){
		pk_rtsk->exinf   = sts.ExtInfo;
		pk_rtsk->tskpri  = sts.TaskPri;
		pk_rtsk->tskstat = sts.TaskState;
		pk_rtsk->tskwait = sts.EventType;
		pk_rtsk->wid     = sts.WaitId;
		pk_rtsk->wupcnt  = sts.WakeupCnt;
		pk_rtsk->suscnt  = sts.SuspendCnt;
		pk_rtsk->tskatr  = sts.TaskAtr;
		pk_rtsk->task    = sts.TaskAdr;
		pk_rtsk->itskpri = sts.InitPri;
		pk_rtsk->stksz   = sts.StackSize;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * タスク付属同期機能.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	起床待ち (タイムアウトなし).
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		slp_tsk( void )
{
	//! タイムアウトなしでタスクを起床待ちにする.
	return tslp_tsk( TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	起床待ち (タイムアウトあり).
 *
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tslp_tsk( TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! タスクを起床待ちにする.
	ercd = wi_SleepTask( tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの起床.
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		wup_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! タスクを起床する.
	ercd = wi_WakeupTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの起床要求を無効化.
 *
 *	@param	[in]	p_wupcnt	キューイングされていた起床要求回数を格納する領域のポインタ.
 *	@param	[in]	tskid		タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		can_wup( INT *p_wupcnt, ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! タスクへの起床要求をクリアする.
	ercd = wi_CancelWakeup( tskid, p_wupcnt );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	待ち状態の強制解除.
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		rel_wai( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! タスクの待ち状態を強制的に解除する.
	ercd = wi_ReleaseWait( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	強制待ち状態への移行.
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		sus_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! タスクを中断(強制待ち状態)にする.
	ercd = wi_SuspendTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	強制待ち状態からの再開.
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		rsm_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! タスクを待ち状態から再開する.
	ercd = wi_ResumeTask( tskid );

	wi_CommonUnlock();
	return ercd;
}


/****************************************************************************/
/*!
 *	@brief	強制待ち状態からの強制再開.
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		frsm_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! 強制待ちをしているタスクを強制的に再開させる.
	ercd = wi_ForceResumeTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	自タスクの遅延.
 *
 *	@param	[in]	dlytim	遅延時間.
 *
 *	@retval	エラーコード.
 */
ER		dly_tsk( DLYTIME dlytim )
{
	ER	ercd;

	wi_CommonLock();

	ercd = wi_DelayTask( (TMO)dlytim );

	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 同期･通信機能 (セマフォ).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	セマフォの生成.
 *
 *	@param	[in]	semid	セマフォID番号.
 *	@param	[in]	pk_csem	セマフォ生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_sem( ID semid, const T_CSEM *pk_csem )
{
	ER			ercd;
	WISEMOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_csem ){
		return E_PAR;
	}
	//! セマフォ生成情報をコピーする.
	memset( &obj, 0, sizeof(WISEMOBJ) );
	obj.Attribute = pk_csem->sematr;
	obj.SemCnt    = pk_csem->isemcnt;
	obj.MaxCnt    = pk_csem->maxsem;
	obj.ExtInfo   = pk_csem->exinf;

	wi_CommonLock();

	//! セマフォを生成する.
	ercd = wi_CreateSemaphore( semid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	セマフォの削除.
 *
 *	@param	[in]	semid	セマフォID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_sem( ID semid )
{
	ER ercd;

	wi_CommonLock();

	//! セマフォを削除する.
	ercd = wi_DeleteSemaphore( semid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	セマフォ資源の返却.
 *
 *	@param	[in]	semid	セマフォID番号.
 *
 *	@retval	エラーコード.
 */
ER		sig_sem( ID semid )
{
	ER ercd;

	wi_CommonLock();

	//! セマフォの資源を返却する.
	ercd = wi_SignalSemaphore( semid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	セマフォ資源の獲得 (タイムアウトなし).
 *
 *	@param	[in]	semid	セマフォID番号.
 *
 *	@retval	エラーコード.
 */
ER		wai_sem( ID semid )
{
	//! タイムアウトなしでセマフォ資源を獲得する.
	return twai_sem( semid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	セマフォ資源の獲得 (ポーリング).
 *
 *	@param	[in]	semid	セマフォID番号.
 *
 *	@retval	エラーコード.
 */
ER		pol_sem( ID semid )
{
	//! 獲得待ちなしでセマフォ資源を獲得する.
	return twai_sem( semid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	セマフォ資源の獲得 (タイムアウトあり).
 *
 *	@param	[in]	semid	セマフォID番号.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		twai_sem( ID semid, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! セマフォの資源を獲得する.
	ercd = wi_WaitSemaphore( semid, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	セマフォ状態の参照.
 *
 *	@param	[out]	pk_rsem	セマフォ状態を格納する構造体のポインタ.
 *	@param	[in]	semid	セマフォID番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_sem( T_RSEM *pk_rsem, ID semid )
{
	ER			ercd;
	WISEMSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rsem ){
		return E_PAR;
	}
	wi_CommonLock();

	//! セマフォの状態を取得する.
	ercd = wi_RefarenceSemaphore( semid, &sts );
	if( ercd == E_OK ){
		pk_rsem->exinf  = sts.ExtInfo;
		pk_rsem->wtsk   = sts.WaitId;
		pk_rsem->semcnt = sts.SemCnt;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 同期･通信機能 (イベントフラグ).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	イベントフラグの生成.
 *
 *	@param	[in]	flgid	イベントフラグID番号.
 *	@param	[in]	pk_cflg	イベントフラグ生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_flg( ID flgid, const T_CFLG *pk_cflg )
{
	ER			ercd;
	WIFLGOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cflg ){
		return E_PAR;
	}
	//! イベントフラグ生成情報をコピーする.
	memset( &obj, 0, sizeof(WIFLGOBJ) );
	obj.Attribute = pk_cflg->flgatr & ~TA_CLR;
	obj.FlgVal    = pk_cflg->iflgptn;
	obj.ExtInfo   = pk_cflg->exinf;

	wi_CommonLock();

	//! イベントフラグを生成する.
	ercd = wi_CreateEvFlag( flgid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグの削除.
 *
 *	@param	[in]	flgid	イベントフラグID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_flg( ID flgid )
{
	ER ercd;

	wi_CommonLock();

	//! イベントフラグを削除する.
	ercd = wi_DeleteEvFlag( flgid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグのセット.
 *
 *	@param	[in]	flgid	イベントフラグID番号.
 *	@param	[in]	setptn	セットするビットパターン.
 *
 *	@retval	エラーコード.
 */
ER		set_flg( ID flgid, UINT setptn )
{
	ER ercd;

	wi_CommonLock();

	//! イベントフラグをセットする.
	ercd = wi_SetEvFlag( flgid, setptn );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグのクリア.
 *
 *	@param	[in]	flgid	イベントフラグID番号.
 *	@param	[in]	clrptn	クリアするビットパターン.
 *
 *	@retval	エラーコード.
 */
ER		clr_flg( ID flgid, UINT clrptn )
{
	ER ercd;

	wi_CommonLock();

	//! イベントフラグをクリアする.
	ercd = wi_ClearEvFlag( flgid, clrptn );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ待ち (タイムアウトなし).
 *
 *	@param	[out]	p_flgptn	待ち解除時のビットパターンを格納する領域のポインタ.
 *	@param	[in]	flgid		イベントフラグID番号.
 *	@param	[in]	waiptn		待ちビットパターン.
 *	@param	[in]	wfmode		待ちモード.
 *
 *	@retval	エラーコード.
 */
ER		wai_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode )
{
	//! タイムアウトなしでイベント待ちをする.
	return twai_flg( p_flgptn, flgid, waiptn, wfmode, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ待ち (ポーリング).
 *
 *	@param	[out]	p_flgptn	待ち解除時のビットパターンを格納する領域のポインタ.
 *	@param	[in]	flgid		イベントフラグID番号.
 *	@param	[in]	waiptn		待ちビットパターン.
 *	@param	[in]	wfmode		待ちモード.
 *
 *	@retval	エラーコード.
 */
ER		pol_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode )
{
	//! イベントが発生しているかどうかを調べる.
	return twai_flg( p_flgptn, flgid, waiptn, wfmode, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ待ち (タイムアウトあり).
 *
 *	@param	[out]	p_flgptn	待ち解除時のビットパターンを格納する領域のポインタ.
 *	@param	[in]	flgid		イベントフラグID番号.
 *	@param	[in]	waiptn		待ちビットパターン.
 *	@param	[in]	wfmode		待ちモード.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		twai_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! イベント待ちをする.
	ercd = wi_WaitEvFlag( flgid, p_flgptn, waiptn, wfmode, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ状態の参照.
 *
 *	@param	[out]	pk_rflg	イベントフラグ状態を格納する構造体のポインタ.
 *	@param	[in]	flgid	イベントフラグID番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_flg( T_RFLG *pk_rflg, ID flgid )
{
	ER			ercd;
	WIFLGSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rflg ){
		return E_PAR;
	}
	wi_CommonLock();

	//! イベントフラグの状態を取得する.
	ercd = wi_RefarenceEvFlag( flgid, &sts );
	if( ercd == E_OK ){
		pk_rflg->exinf  = sts.ExtInfo;
		pk_rflg->wtsk   = (BOOL_ID)sts.WaitId;
		pk_rflg->flgptn = sts.FlgVal;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 同期･通信機能 (メールボックス).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	メールボックスの生成.
 *
 *	@param	[in]	mbxid	メールボックスID番号.
 *	@param	[in]	pk_cmbx	メールボックス生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_mbx( ID mbxid, const T_CMBX *pk_cmbx )
{
	ER			ercd;
	WIMBXOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmbx ){
		return E_PAR;
	}
	//! メールボックス生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMBXOBJ) );
	obj.Attribute   = pk_cmbx->mbxatr;
	obj.ExtInfo     = pk_cmbx->exinf;
	obj.MaxPriority = TMAX_MPRI;

	wi_CommonLock();

	//! メールボックスを生成する.
	ercd = wi_CreateMailBox( mbxid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスの削除.
 *
 *	@param	[in]	mbxid	メールボックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_mbx( ID mbxid )
{
	ER ercd;

	wi_CommonLock();

	//! メールボックスを削除する.
	ercd = wi_DeleteMailBox( mbxid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスへの送信.
 *
 *	@param	[in]	mbxid	メールボックスID番号.
 *	@param	[in]	pk_msg	メッセージ･パケットのポインタ.
 *
 *	@retval	エラーコード.
 */
ER		snd_msg( ID mbxid, T_MSG *pk_msg )
{
	ER ercd;

	wi_CommonLock();

	//! メールボックスへメッセージを送信する.
	ercd = wi_SendMailBox( mbxid, pk_msg );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスからの受信 (タイムアウトなし).
 *
 *	@param	[out]	ppk_msg	メッセージ･パケットのアドレスを格納する領域のポインタ.
 *	@param	[in]	mbxid	メールボックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		rcv_msg( T_MSG **ppk_msg, ID mbxid )
{
	//! タイムアウトなしでメールボックスからメッセージを受信する.
	return trcv_msg( ppk_msg, mbxid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	メールボックスからの受信 (ポーリング).
 *
 *	@param	[out]	ppk_msg	メッセージ･パケットのアドレスを格納する領域のポインタ.
 *	@param	[in]	mbxid	メールボックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		prcv_msg( T_MSG **ppk_msg, ID mbxid )
{
	//! 受信待ちなしでメールボックスからメッセージを受信する.
	return trcv_msg( ppk_msg, mbxid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	メールボックスからの受信 (タイムアウトあり).
 *
 *	@param	[out]	ppk_msg	メッセージ･パケットのアドレスを格納する領域のポインタ.
 *	@param	[in]	mbxid	メールボックスID番号.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		trcv_msg( T_MSG **ppk_msg, ID mbxid, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! メールボックスからメッセージを受信する.
	ercd = wi_ReceiveMailBox( mbxid, ppk_msg, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスの状態参照.
 *
 *	@param	[out]	pk_rmbx	メールボックス状態を格納する構造体のポインタ.
 *	@param	[in]	mbxid	メールボックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_mbx( T_RMBX *pk_rmbx, ID mbxid )
{
	ER			ercd;
	WIMBXSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rmbx ){
		return E_PAR;
	}
	wi_CommonLock();

	//! メールボックスの状態を取得する.
	ercd = wi_RefarenceMailBox( mbxid, &sts );
	if( ercd == E_OK ){
		pk_rmbx->exinf  = sts.ExtInfo;
		pk_rmbx->wtsk   = (BOOL_ID)sts.WaitId;
		pk_rmbx->pk_msg = sts.NextMsg;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 拡張同期･通信機能 (メッセージバッファ).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	メッセージバッファの生成.
 *
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[in]	pk_cmbf	メッセージバッファ生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_mbf( ID mbfid, const T_CMBF *pk_cmbf )
{
	ER			ercd;
	WIMBFOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmbf ){
		return E_PAR;
	}
	//! メッセージバッファ生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMBFOBJ) );
	obj.SndAttr = pk_cmbf->mbfatr & ~TA_TPRI;
	obj.RcvAttr = pk_cmbf->mbfatr;
	obj.MsgSize = pk_cmbf->bufsz;
	obj.MaxMsg  = pk_cmbf->maxmsz;
	obj.ExtInfo = pk_cmbf->exinf;

	wi_CommonLock();

	//! メッセージバッファを生成する.
	ercd = wi_CreateMsgBuffer( mbfid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの削除.
 *
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_mbf( ID mbfid )
{
	ER ercd;

	wi_CommonLock();

	//! メッセージバッファを削除する.
	ercd = wi_DeleteMsgBuffer( mbfid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファへの送信 (タイムアウトなし).
 *
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[in]	msg		メッセージのポインタ.
 *	@param	[in]	msgsz	メッセージのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		snd_mbf( ID mbfid, VP msg, INT msgsz )
{
	//! タイムアウトなしでメッセージバッファへメッセージを送信する.
	return tsnd_mbf( mbfid, msg, msgsz, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファへの送信 (ポーリング).
 *
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[in]	msg		メッセージのポインタ.
 *	@param	[in]	msgsz	メッセージのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		psnd_mbf( ID mbfid, VP msg, INT msgsz )
{
	//! 送信待ちなしでメッセージバッファへメッセージを送信する.
	return tsnd_mbf( mbfid, msg, msgsz, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファへの送信 (タイムアウトあり).
 *
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[in]	msg		メッセージのポインタ.
 *	@param	[in]	msgsz	メッセージのサイズ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tsnd_mbf( ID mbfid, VP msg, INT msgsz, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! メッセージバッファへメッセージを送信する.
	ercd = wi_SendMsgBuffer( mbfid, msg, msgsz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファからの受信 (タイムアウトなし).
 *
 *	@param	[out]	msg		メッセージを格納する領域のポインタ.
 *	@param	[out]	msg		メッセージサイズを格納する領域のポインタ.
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *
 *	@retval	エラーコード.
 */
ER		rcv_mbf( VP msg, INT *p_msgsz, ID mbfid )
{
	//! タイムアウトなしでメッセージバッファからメッセージを受信する.
	return trcv_mbf( msg, p_msgsz, mbfid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファからの受信 (ポーリング).
 *
 *	@param	[out]	msg		メッセージを格納する領域のポインタ.
 *	@param	[out]	msg		メッセージサイズを格納する領域のポインタ.
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *
 *	@retval	エラーコード.
 */
ER		prcv_mbf( VP msg, INT *p_msgsz, ID mbfid )
{
	//! 受信待ちなしでメッセージバッファからメッセージを受信する.
	return trcv_mbf( msg, p_msgsz, mbfid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファからの受信 (タイムアウトあり).
 *
 *	@param	[out]	msg		メッセージを格納する領域のポインタ.
 *	@param	[out]	msg		メッセージサイズを格納する領域のポインタ.
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		trcv_mbf( VP msg, INT *p_msgsz, ID mbfid, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! メッセージバッファからメッセージを受信する.
	ercd = wi_ReceiveMsgBuffer( mbfid, msg, p_msgsz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの状態参照.
 *
 *	@param	[out]	pk_rmbf	メッセージバッファ状態を格納する構造体のポインタ.
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_mbf( T_RMBF *pk_rmbf, ID mbfid )
{
	ER			ercd;
	WIMBFSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rmbf ){
		return E_PAR;
	}
	wi_CommonLock();

	//! メッセージバッファの状態を取得する.
	ercd = wi_RefarenceMsgBuffer( mbfid, &sts );
	if( ercd == E_OK ){
		pk_rmbf->exinf   = sts.ExtInfo;
		pk_rmbf->wtsk    = (BOOL_ID)sts.RcvWaitId;
		pk_rmbf->stsk    = (BOOL_ID)sts.SndWaitId;
		pk_rmbf->msgsz   = sts.MsgSize;
		pk_rmbf->frbufsz = sts.FreeSize;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 拡張同期･通信機能 (ランデブ).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	ランデブポートの生成.
 *
 *	@param	[in]	porid	ランデブポートID番号.
 *	@param	[in]	pk_cpor	ランデブポート生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_por( ID porid, const T_CPOR *pk_cpor )
{
	ER			ercd;
	WIPOROBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cpor ){
		return E_PAR;
	}
	//! ランデブポート生成情報をコピーする.
	memset( &obj, 0, sizeof(WIPOROBJ) );
	obj.Attribute = pk_cpor->poratr;
	obj.MaxCalMsg = pk_cpor->maxcmsz;
	obj.MaxRepMsg = pk_cpor->maxrmsz;
	obj.ExtInfo   = pk_cpor->exinf;

	wi_CommonLock();

	//! ランデブポートを生成する.
	ercd = wi_CreateRendPort( porid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブポートの削除.
 *
 *	@param	[in]	porid	ランデブポートID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_por( ID porid )
{
	ER ercd;

	wi_CommonLock();

	//! ランデブポートを削除する.
	ercd = wi_DeleteRendPort( porid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブ呼び出し (タイムアウトなし).
 *
 *	@param	[in]	msg			呼び出しメッセージのアドレス.
 *	@param	[out]	p_rmsgsz	応答メッセージのサイズを格納する領域のポインタ.
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	calptn		呼び出し側選択条件のビットパターン.
 *	@param	[in]	cmsgsz		呼び出しメッセージのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		cal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz )
{
	//! タイムアウトなしでランデブを呼び出す.
	return tcal_por( msg, p_rmsgsz, porid, calptn, cmsgsz, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	ランデブ呼び出し (ポーリング).
 *
 *	@param	[in]	msg			呼び出しメッセージのアドレス.
 *	@param	[out]	p_rmsgsz	応答メッセージのサイズを格納する領域のポインタ.
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	calptn		呼び出し側選択条件のビットパターン.
 *	@param	[in]	cmsgsz		呼び出しメッセージのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		pcal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz )
{
	//! 受付待ちなしでランデブを呼び出す.
	return tcal_por( msg, p_rmsgsz, porid, calptn, cmsgsz, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	ランデブ呼び出し (タイムアウトあり).
 *
 *	@param	[in]	msg			呼び出しメッセージのアドレス.
 *	@param	[out]	p_rmsgsz	応答メッセージのサイズを格納する領域のポインタ.
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	calptn		呼び出し側選択条件のビットパターン.
 *	@param	[in]	cmsgsz		呼び出しメッセージのサイズ.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tcal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! ランデブを呼び出す.
	ercd = wi_CallRendPort( porid, calptn, msg, cmsgsz, p_rmsgsz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブ受け付け (タイムアウトなし).
 *
 *	@param	[out]	p_rdvno		ランデブ番号を格納する領域のポインタ.
 *	@param	[out]	msg			呼び出しメッセージを格納する領域のポインタ.
 *	@param	[out]	p_cmsgsz	呼び出しメッセージのサイズを格納する領域のポインタ.
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	acpptn		受け付け側選択条件のビットパターン.
 *
 *	@retval	エラーコード.
 */
ER		acp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn )
{
	//! タイムアウトなしでランデブを受け付ける.
	return tacp_por( p_rdvno, msg, p_cmsgsz, porid, acpptn, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	ランデブ受け付け (ポーリング).
 *
 *	@param	[out]	p_rdvno		ランデブ番号を格納する領域のポインタ.
 *	@param	[out]	msg			呼び出しメッセージを格納する領域のポインタ.
 *	@param	[out]	p_cmsgsz	呼び出しメッセージのサイズを格納する領域のポインタ.
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	acpptn		受け付け側選択条件のビットパターン.
 *
 *	@retval	エラーコード.
 */
ER		pacp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn )
{
	//! 呼び出し待ちなしでランデブを受け付ける.
	return tacp_por( p_rdvno, msg, p_cmsgsz, porid, acpptn, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	ランデブ受け付け (タイムアウトあり).
 *
 *	@param	[out]	p_rdvno		ランデブ番号を格納する領域のポインタ.
 *	@param	[out]	msg			呼び出しメッセージを格納する領域のポインタ.
 *	@param	[out]	p_cmsgsz	呼び出しメッセージのサイズを格納する領域のポインタ.
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	acpptn		受け付け側選択条件のビットパターン.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tacp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! ランデブを受け付ける.
	ercd = wi_AcceptRendPort( porid, acpptn, p_rdvno, msg, p_cmsgsz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブの回送
 *
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	calptn		受け付け側選択条件のビットパターン.
 *	@param	[in]	rdvno		ランデブ番号.
 *	@param	[in]	msg			呼び出しメッセージのポインタ.
 *	@param	[in]	cmsgsz		呼び出しメッセージのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		fwd_por( ID porid, UINT calptn, RNO rdvno, VP msg, INT cmsgsz )
{
	ER ercd;

	wi_CommonLock();

	//! ランデブを他のランデブ･ポートに回送する.
	ercd = wi_FowardRendPort( porid, calptn, rdvno, msg, cmsgsz );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブの終了.
 *
 *	@param	[in]	rdvno		ランデブ番号.
 *	@param	[in]	msg			返答メッセージのポインタ.
 *	@param	[in]	cmsgsz		返答メッセージのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		rpl_rdv( RNO rdvno, VP msg, INT cmsgsz )
{
	ER ercd;

	wi_CommonLock();

	//! ランデブの終了を通知する.
	ercd = wi_ReplayRendPort( rdvno, msg, cmsgsz );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブポートの状態参照.
 *
 *	@param	[out]	pk_rpor	ランデブポート状態を格納する構造体のポインタ.
 *	@param	[in]	porid	ランデブポートID番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_por( T_RPOR *pk_rpor, ID porid )
{
	ER			ercd;
	WIPORSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rpor ){
		return E_PAR;
	}
	wi_CommonLock();

	//! ランデブポートの状態を取得する.
	ercd = wi_RefarenceRendPort( porid, &sts );
	if( ercd == E_OK ){
		pk_rpor->exinf = sts.ExtInfo;
		pk_rpor->wtsk  = (BOOL_ID)sts.CalWaitId;
		pk_rpor->atsk  = (BOOL_ID)sts.AcpWaitId;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * メモリプール管理機能 (固定長メモリプール).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの生成.
 *
 *	@param	[in]	mpfid	メモリプールID番号.
 *	@param	[in]	pk_cmpf	メモリプール生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_mpf( ID mpfid, const T_CMPF *pk_cmpf )
{
	ER			ercd;
	WIMPFOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmpf ){
		return E_PAR;
	}
	//! 固定長メモリプール生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMPFOBJ) );
	obj.ExtInfo   = pk_cmpf->exinf;
	obj.Attribute = pk_cmpf->mpfatr;
	obj.BlockCnt  = pk_cmpf->mpfcnt;
	obj.BlockSize = pk_cmpf->blfsz;

	wi_CommonLock();

	//! 固定長メモリプールを生成する.
	ercd = wi_CreateFixedMemPool( mpfid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの削除.
 *
 *	@param	[in]	mpfid	メモリプールID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_mpf( ID mpfid )
{
	ER ercd;

	wi_CommonLock();

	//! 固定長メモリプールを削除する.
	ercd = wi_DeleteFixedMemPool( mpfid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリブロックの獲得 (タイムアウトなし).
 *
 *	@param	[in]	p_blf	メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	mpfid	メモリプールID番号.
 *
 *	@retval	エラーコード.
 */
ER		get_blf( VP *p_blf, ID mpfid )
{
	//! タイムアウトなしで固定長メモリブロックを獲得する.
	return tget_blf( p_blf, mpfid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリブロックの獲得 (ポーリング).
 *
 *	@param	[in]	p_blf	メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	mpfid	メモリプールID番号.
 *
 *	@retval	エラーコード.
 */
ER		pget_blf( VP *p_blf, ID mpfid )
{
	//! 獲得待ちなしで固定長メモリブロックを獲得する.
	return tget_blf( p_blf, mpfid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリブロックの獲得 (タイムアウトあり).
 *
 *	@param	[in]	p_blf	メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	mpfid	メモリプールID番号.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tget_blf( VP *p_blf, ID mpfid, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! 固定長メモリブロックを獲得する.
	ercd = wi_GetFixedMemPool( mpfid, p_blf, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリブロックの返却.
 *
 *	@param	[in]	mpfid	メモリプールID番号.
 *	@param	[in]	blf		返却するメモリブロックのアドレス.
 *
 *	@retval	エラーコード.
 */
ER		rel_blf( ID mpfid, VP blf )
{
	ER ercd;

	wi_CommonLock();

	//! 固定長メモリブロックを返却する.
	ercd = wi_ReleaseFixedMemPool( mpfid, blf );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの参照.
 *
 *	@param	[out]	pk_rmpf	メモリプール状態を格納する構造体のポインタ.
 *	@param	[in]	mpfid	メモリプールID番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_mpf( T_RMPF *pk_rmpf, ID mpfid )
{
	ER			ercd;
	WIMPFSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rmpf ){
		return E_PAR;
	}
	wi_CommonLock();

	//! 固定長メモリプールの状態を取得する.
	ercd = wi_RefarenceFixedMemPool( mpfid, &sts );
	if( ercd == E_OK ){
		pk_rmpf->exinf  = sts.ExtInfo;
		pk_rmpf->wtsk   = (BOOL_ID)sts.WaitId;
		pk_rmpf->frbcnt = sts.FreeBlock;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * メモリプール管理機能 (可変長メモリプール).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの生成.
 *
 *	@param	[in]	mplid	メモリ･プールID番号.
 *	@param	[in]	pk_cmpl	メモリプール生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_mpl( ID mplid, const T_CMPL *pk_cmpl )
{
	ER			ercd;
	WIMPLOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmpl ){
		return E_PAR;
	}
	//! 可変長メモリプール生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMPLOBJ) );
	obj.ExtInfo   = pk_cmpl->exinf;
	obj.Attribute = pk_cmpl->mplatr;
	obj.MemSize   = pk_cmpl->mplsz;

	wi_CommonLock();

	//! 可変長メモリプールを生成する.
	ercd = wi_CreateVarMemPool( mplid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの削除.
 *
 *	@param	[in]	mpfid	メモリ･プールID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_mpl( ID mplid )
{
	ER ercd;

	wi_CommonLock();

	//! 可変長メモリプールを削除する.
	ercd = wi_DeleteVarMemPool( mplid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリブロックの獲得 (タイムアウトなし).
 *
 *	@param	[in]	p_blk	メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	mplid	メモリプールID番号.
 *	@param	[in]	blksz	メモリブロックのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		get_blk( VP p_blk, ID mplid, INT blksz )
{
	//! タイムアウトなしで可変長メモリブロックを獲得する.
	return tget_blk( p_blk, mplid, blksz, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリブロックの獲得 (ポーリング).
 *
 *	@param	[in]	p_blk	メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	mplid	メモリプールID番号.
 *	@param	[in]	blksz	メモリブロックのサイズ.
 *
 *	@retval	エラーコード.
 */
ER		pget_blk( VP p_blk, ID mplid, INT blksz )
{
	//! 獲得待ちなしで可変長メモリブロックを獲得する.
	return tget_blk( p_blk, mplid, blksz, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリブロックの獲得 (タイムアウトあり).
 *
 *	@param	[in]	p_blk	メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	mplid	メモリプールID番号.
 *	@param	[in]	blksz	メモリブロックのサイズ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tget_blk( VP p_blk, ID mplid, INT blksz, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! 可変長メモリブロックを獲得する.
	ercd = wi_GetVarMemPool( mplid, p_blk, blksz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリブロックの返却.
 *
 *	@param	[in]	mplid	メモリプールID番号.
 *	@param	[in]	blk		返却するメモリブロックのアドレス.
 *
 *	@retval	エラーコード.
 */
ER		rel_blk( ID mplid, VP blk )
{
	ER ercd;

	wi_CommonLock();

	//! 可変長メモリブロックを返却する.
	ercd = wi_ReleaseVarMemPool( mplid, blk );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの参照.
 *
 *	@param	[out]	pk_rmpl	メモリプール状態を格納する構造体のポインタ.
 *	@param	[in]	mplid	メモリプールID番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_mpl( T_RMPL *pk_rmpl, ID mplid )
{
	ER			ercd;
	WIMPLSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rmpl ){
		return E_PAR;
	}
	wi_CommonLock();

	//! 可変長メモリプールの状態を取得する.
	ercd = wi_RefarenceVarMemPool( mplid, &sts );
	if( ercd == E_OK ){
		pk_rmpl->exinf = sts.ExtInfo;
		pk_rmpl->wtsk  = (BOOL_ID)sts.WaitId;
		pk_rmpl->frsz  = sts.TotalFreeSize;
		pk_rmpl->maxsz = sts.MaxFreeSize;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 時間管理機能.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	システム時刻の設定.
 *
 *	@param	[in]	pk_tim		設定する時刻を格納した構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		set_tim( const SYSTIME *pk_tim )
{
	if( !pk_tim ){
		return E_PAR;
	}
	wi_CommonLock();

	//! システム時刻を設定する.
	wi_SetSystemTime( ((DWORDLONG)(pk_tim->utime) << 32) + (DWORDLONG)(pk_tim->ltime) );

	wi_CommonUnlock();
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	システム時刻の参照.
 *
 *	@param	[in]	pk_tim		システム時刻を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		get_tim( SYSTIME *pk_tim )
{
	DWORDLONG sys_time;

	if( !pk_tim ){
		return E_PAR;
	}
	wi_CommonLock();

	//! システム時刻を参照する.
	sys_time      = wi_GetSystemTime();
	pk_tim->utime = (short)(sys_time >> 32 & 0x0000FFFF);
	pk_tim->ltime = (long )(sys_time       & 0xFFFFFFFF);

	wi_CommonUnlock();
	return E_OK;
}

/***************************************
 *
 * 時間管理機能 (周期ハンドラ).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	周期ハンドラ定義.
 *
 *	@param	[in]	cycno	周期ハンドラ番号.
 *	@param	[in]	pk_dcyc	周期ハンドラ定義情報.
 *
 *	@retval	エラーコード.
 */
ER		def_cyc( HNO cycno, const T_DCYC *pk_dcyc )
{
	ER			ercd;
	WICYCOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_dcyc ){
		return E_PAR;
	}
	//! 周期ハンドラ定義情報をコピーする.
	memset( &obj, 0, sizeof(WICYCOBJ) );
	obj.Attribute = pk_dcyc->cycatr;
	obj.CycAdr    = pk_dcyc->cychdr;
	obj.Active    = (pk_dcyc->cycact & TCY_ON) ? TRUE : FALSE;
	obj.ExtInfo   = pk_dcyc->exinf;
	obj.CycleTime = ((DWORDLONG)(pk_dcyc->cyctim.utime) << 32) + (DWORDLONG)(pk_dcyc->cyctim.ltime);

	wi_CommonLock();

	//! 周期ハンドラを登録する.
	ercd = wi_DefineCycleHadler( cycno, &obj, TRUE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの活性制御.
 *
 *	@param	[in]	cycno	周期ハンドラ番号.
 *	@param	[in]	cycact	周期ハンドラ活性情報.
 *
 *	@retval	エラーコード.
 */
ER		act_cyc( HNO cycno, UINT cycact )
{
	ER ercd;

	wi_CommonLock();

	//! 周期ハンドラの起動/停止を設定する.
	ercd = wi_ActionCycleHadler( cycno,
								((cycact & TCY_ON ) != 0) ? TRUE : FALSE,
								((cycact & TCY_INI) != 0) ? TRUE : FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの状態参照.
 *
 *	@param	[out]	pk_rcyc	周期ハンドラ状態を格納する構造体のポインタ.
 *	@param	[in]	cycno	周期ハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_cyc( T_RCYC *pk_rcyc, HNO cycno )
{
	ER			ercd;
	WICYCSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rcyc ){
		return E_PAR;
	}
	wi_CommonLock();

	//! 周期ハンドラの状態を取得する.
	ercd = wi_RefarenceCycleHadler( cycno, &sts );
	if( ercd == E_OK ){
		pk_rcyc->exinf        = sts.ExtInfo;
		pk_rcyc->lfttim.utime = (short)(sts.LeftTime >> 32 & 0x0000FFFF);
		pk_rcyc->lfttim.ltime = (long )(sts.LeftTime       & 0xFFFFFFFF);
		pk_rcyc->cycact       = (sts.Active ? TCY_ON : TCY_OFF);
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 時間管理機能 (アラーム･ハンドラ).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラ定義.
 *
 *	@param	[in]	almno	アラーム･ハンドラ番号.
 *	@param	[in]	pk_dalm	アラーム･ハンドラ定義情報.
 *
 *	@retval	エラーコード.
 */
ER		def_alm( HNO almno, const T_DALM *pk_dalm )
{
	ER			ercd;
	WIALMOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_dalm ){
		return E_PAR;
	}
	//! アラーム･ハンドラ登録情報をコピーする.
	memset( &obj, 0, sizeof(WIALMOBJ) );
	obj.Attribute = pk_dalm->almatr;
	obj.AlmAdr    = pk_dalm->almhdr;
	obj.TimeMode  = pk_dalm->tmmode;
	obj.AlmTime   = ((DWORDLONG)(pk_dalm->almtim.utime) << 32) + (DWORDLONG)(pk_dalm->almtim.ltime);
	obj.ExtInfo   = pk_dalm->exinf;
	obj.Active    = pk_dalm->almhdr ? TRUE : FALSE;

	//! アラーム･ハンドラの起動時刻を現在時刻からの相対時刻にする.
	if( (obj.TimeMode & TTM_REL) != 0 ){
		obj.AlmTime += wi_GetSystemTime();
	}
	wi_CommonLock();

	//! アラーム･ハンドラを登録する.
	ercd = wi_DefineAlarmHadler( almno, &obj, TRUE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの状態参照.
 *
 *	@param	[out]	pk_ralm	アラーム･ハンドラ状態を格納する構造体のポインタ.
 *	@param	[in]	almno	アラーム･ハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		ref_alm( T_RALM *pk_ralm, HNO almno )
{
	ER			ercd;
	WIALMSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_ralm ){
		return E_PAR;
	}
	wi_CommonLock();

	//! アラーム･ハンドラの状態を取得する.
	ercd = wi_RefarenceAlarmHadler( almno, &sts );
	if( ercd == E_OK ){
		pk_ralm->exinf        = sts.ExtInfo;
		pk_ralm->lfttim.utime = (short)(sts.LeftTime >> 32 & 0x0000FFFF);
		pk_ralm->lfttim.ltime = (long )(sts.LeftTime       & 0xFFFFFFFF);
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 割り込み管理機能.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	割り込みハンドラの定義.
 *
 *	@param	[in]	dintno		割り込みハンドラ番号.
 *	@param	[in]	pk_dint		割り込みハンドラ定義情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		def_int( UINT dintno, const T_DINT *pk_dint )
{
	ER			ercd;
	WIINTOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_dint ){
		return E_PAR;
	}
	//! 割り込みハンドラ定義情報をコピーする.
	memset( &obj, 0, sizeof(WIINTOBJ) );
	obj.Attribute = pk_dint->intatr;
	obj.IntrAdr   = pk_dint->inthdr;

	wi_CommonLock();

	//! 割り込みハンドラを登録する.
	ercd = wi_DefineIntrruptHander( dintno, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	割り込みの禁止.
 *
 *	@param	[in]	eintno		割り込みハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		dis_int( UINT eintno )
{
	ER ercd;

	wi_CommonLock();

	//! 割り込みを禁止する.
	ercd = wi_DisableIntrrupt( eintno );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	割り込みの許可.
 *
 *	@param	[in]	eintno		割り込みハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		ena_int( UINT eintno )
{
	ER ercd;

	wi_CommonLock();

	//! 割り込みを許可する.
	ercd = wi_EnableIntrrupt( eintno );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	CPUロック状態への移行.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		loc_cpu( void )
{
	ER ercd;

	wi_CommonLock();

	//! CPUをロックする.
	ercd = wi_LockCPU();

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	CPUロック状態の解除.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		unl_cpu( void )
{
	ER ercd;

	wi_CommonLock();

	//! CPUのロックを解除する.
	ercd = wi_UnLockCPU();

	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * システム状態管理機能.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	タスクの優先順位の回転.
 *
 *	@param	[in]	tskpri	優先順位を回転する優先度.
 *
 *	@retval	エラーコード.
 */
ER		rot_rdq( PRI tskpri )
{
	ER ercd;

	wi_CommonLock();

	//! タスクの優先順位を回転させる.
	ercd = wi_RotateTaskPriority( tskpri );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	実行状態のタスクIDの参照.
 *
 *	@param	[out]	p_tskid		タスクID番号を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		get_tid( ID *p_tskid )
{
	ER ercd;

	wi_CommonLock();

	//! 実行状態にあるタスクのIDを取得する.
	ercd = wi_GetTid( p_tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ディスパッチの禁止.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		dis_dsp( void )
{
	ER ercd;

	wi_CommonLock();

	//! タスクのディスパッチを禁止する.
	ercd = wi_DisabledDispatch();

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ディスパッチの許可.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		ena_dsp( void )
{
	ER ercd;

	wi_CommonLock();

	//! タスクのディスパッチを許可する.
	ercd = wi_EnabledDispatch();

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	システム状態の参照.
 *
 *	@param	[out]	pk_rsys		システム状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_sys( T_RSYS *pk_rsys )
{
	ER ercd;

	wi_CommonLock();

	//! システム情報を取得する.
	ercd = wi_GetSystemInfo( pk_rsys );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	バージョン情報の参照.
 *
 *	@param	[out]	pk_ver		バージョン情報を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		get_ver( T_VER *pk_ver )
{
	ER ercd;

	wi_CommonLock();

	//! バージョン情報を取得する.
	ercd = wi_GetVersion( pk_ver );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	コンフィグレーション情報の参照.
 *
 *	@param	[out]	pk_rcfg		コンフィグレーション情報を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_cfg( T_RCFG *pk_rcfg )
{
	ER ercd;

	wi_CommonLock();

	//! コンフィグレーション情報を取得する.
	ercd = wi_GetConfigInfo( pk_rcfg );

	wi_CommonUnlock();
	return ercd;
}
#endif	// __ITRON3__

/* End of file */
