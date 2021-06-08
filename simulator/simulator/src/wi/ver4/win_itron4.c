/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron4.c
 *
 *	@brief	iTRON(Ver4.0)のサービスコール.
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include <stdio.h>
#include "kprintf.h"
#include "wi_config.h"

#ifdef	__ITRON4__
#include "win_itron4.h"
#include "wi_task.h"
#include "wi_semaphore.h"
#include "wi_event_flag.h"
#include "wi_data_queue.h"
#include "wi_mail_box.h"
#include "wi_mutex.h"
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
	ercd = wi_CreateTask( (DWORD)tskid, &obj );

	//! TA_ACTが設定されている場合はタスクを起動する.
	if( ercd == E_OK && (pk_ctsk->tskatr & TA_ACT) != 0 ){
		wi_StartTask( (DWORD)tskid, 0, FALSE );
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_ctsk	タスク生成情報構造体のポインタ.
 *
 *	@retval	生成したタスクのタスクIDまたはエラーコード.
 */
ER_ID	acre_tsk( const T_CTSK *pk_ctsk )
{
	ER_ID		ercd;
	DWORD		tskid;
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
	for( tskid = 1; tskid < TMAX_MAXTSK; tskid++ ){

		//! タスクを生成する.
		ercd = wi_CreateTask( tskid, &obj );
		if( ercd == E_OK ){

			//! 戻り値を生成したタスクID番号にする.
			ercd = (ER_ID)tskid;

			//! TA_ACTが設定されている場合はタスクを起動する.
			if( (pk_ctsk->tskatr & TA_ACT) != 0 ){
				wi_StartTask( tskid, 0, FALSE );
			}
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd = E_NOID;
	}
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
 *
 *	@retval	エラーコード.
 */
ER		act_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! タスクを起動する.
	ercd = wi_StartTask( tskid, 0, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの起動 (非タスクコンテキストからの呼出し用).
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		iact_tsk( ID tskid )
{
	return act_tsk( tskid );
}

/****************************************************************************/
/*!
 *	@brief	タスク起動要求のキャンセル.
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER_UINT		can_act( ID tskid )
{
	ER_UINT ercd;

	wi_CommonLock();

	//! タスクの起動要求をキャンセルする.
	ercd = (ER_UINT)wi_CancelStartReq( tskid );

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
 *	@brief	タスク優先度の参照.
 *
 *	@param	[in]	tskid		タスクID番号.
 *	@param	[out]	p_tskpri	現在のタスク優先度を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		get_pri( ID tskid, PRI *p_tskpri )
{
	ER ercd;

	wi_CommonLock();

	//! タスクの優先度を取得する.
	ercd = wi_RefarenceTaskPriority( tskid, p_tskpri );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの状態参照.
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[out]	pk_rtsk	タスク状態を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_tsk( ID tskid, T_RTSK *pk_rtsk )
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
		pk_rtsk->tskstat = sts.TaskState;
		pk_rtsk->tskpri  = sts.TaskPri;
		pk_rtsk->tskbpri = sts.TaskPri;
		pk_rtsk->tskwait = sts.EventType;
		pk_rtsk->wobjid  = sts.WaitId;
		pk_rtsk->lefttmo = 0;
		pk_rtsk->actcnt  = sts.ActiveCnt;
		pk_rtsk->wupcnt  = sts.WakeupCnt;
		pk_rtsk->suscnt  = sts.SuspendCnt;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	タスクの状態参照 (簡易版).
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[out]	pk_rtst	タスク状態を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_tst( ID tskid, T_RTST *pk_rtst )
{
	ER			ercd;
	WITSKSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rtst ){
		return E_PAR;
	}
	wi_CommonLock();

	//! タスクの状態を簡易参照する.
	ercd = wi_RefarenceTask( tskid, &sts );

	//! 取得したタスクの料体を戻り値として構造体にセットする.
	if( ercd == E_OK ){
		pk_rtst->tskstat = sts.TaskState;
		pk_rtst->tskwait = sts.WaitId;
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
 *	@brief	起床待ち(タイムアウトなし).
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
 *	@brief	起床待ち(タイムアウトあり).
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
 *	@brief	タスクの起床 (非タスクコンテキストからの呼出し用).
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		iwup_tsk( ID tskid )
{
	return wup_tsk( tskid );
}

/****************************************************************************/
/*!
 *	@brief	タスクの起床要求を無効化.
 *
 *	@param	[in]	tskid		タスクID番号.
 *
 *	@retval	キューイングされていた起床要求回数またはエラーコード.
 */
ER_UINT		can_wup( ID tskid )
{
	ER	ercd;
	INT	wupcnt;

	wi_CommonLock();

	//! タスクへの起床要求をクリアする.
	ercd = wi_CancelWakeup( tskid, &wupcnt );
	if( ercd == E_OK ){
		ercd = wupcnt;
	}
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
 *	@brief	待ち状態の強制解除 (非タスクコンテキストからの呼出し用).
 *
 *	@param	[in]	tskid	タスクID番号.
 *
 *	@retval	エラーコード.
 */
ER		irel_wai( ID tskid )
{
	return rel_wai( tskid );
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

	ercd = wi_DelayTask( (TMO)(dlytim) );

	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * タスク例外処理機能.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	タスク例外処理の定義.
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[in]	pk_dtex	タスク例外処理定義用構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		def_tex( ID tskid, T_DTEX *pk_dtex )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	タスク例外処理の要求.
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[in]	pk_dtex	要求するタスク例外処理の例外要因.
 *
 *	@retval	エラーコード.
 */
ER		ras_tex( ID tskid, TEXPTN rasptn )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	タスク例外処理の要求 (非タスクコンテキストからの呼出し用).
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[in]	pk_dtex	要求するタスク例外処理の例外要因.
 *
 *	@retval	エラーコード.
 */
ER		iras_tex( ID tskid, TEXPTN rasptn )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	タスク例外処理の禁止.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		dis_tex( void )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	タスク例外処理の許可.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		ena_tex( void )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	タスク例外処理禁止状態の参照.
 *
 *	@param	なし.
 *
 *	@retval	TRUE = タスク例外処理禁止 / FALSE = タスク例外処理許可.
 */
INT		sns_tex( void )
{
	return TRUE;
}

/****************************************************************************/
/*!
 *	@brief	タスク例外処理の状態参照.
 *
 *	@param	[in]	tskid	タスクID番号.
 *	@param	[out]	pk_rtex	タスク例外処理状態を格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_tex( ID tskid, T_RTEX *pk_rtex )
{
	return E_NOSPT;
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

	wi_CommonLock();

	//! セマフォを生成する.
	ercd = wi_CreateSemaphore( semid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	セマフォの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_csem	セマフォ生成情報構造体のポインタ.
 *
 *	@retval	セマフォID番号またはエラーコード.
 */
ER_ID	acre_sem( const T_CSEM *pk_csem )
{
	ID			semid;
	ER_ID		ercd;
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

	wi_CommonLock();

	for( semid = 1; semid < TMAX_MAXSEM; semid++ ){

		//! セマフォを生成する.
		ercd = wi_CreateSemaphore( semid, &obj );
		if( ercd == E_OK ){
			ercd  = semid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
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
 *	@brief	セマフォ資源の返却 (非タスクコンテキストからの呼出し用).
 *
 *	@param	[in]	semid	セマフォID番号.
 *
 *	@retval	エラーコード.
 */
ER		isig_sem( ID semid )
{
	//! 非タスクコンテキストからセマフォの資源を解放する.
	return sig_sem( semid );
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
 *	@param	[in]	semid	セマフォID番号.
 *	@param	[out]	pk_rsem	セマフォ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_sem( ID semid, T_RSEM *pk_rsem )
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
		pk_rsem->wtskid = sts.WaitId;
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
	obj.Attribute = pk_cflg->flgatr;
	obj.FlgVal    = (UINT)pk_cflg->iflgptn;

	wi_CommonLock();

	//! イベントフラグを生成する.
	ercd = wi_CreateEvFlag( flgid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_cflg	イベントフラグ生成情報構造体のポインタ.
 *
 *	@retval	イベントフラグID番号またはエラーコード.
 */
ER_ID	acre_flg( const T_CFLG *pk_cflg )
{
	ID			flgid;
	ER_ID		ercd;
	WIFLGOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cflg ){
		return E_PAR;
	}
	//! イベントフラグ生成情報をコピーする.
	memset( &obj, 0, sizeof(WIFLGOBJ) );
	obj.Attribute = pk_cflg->flgatr;
	obj.FlgVal    = (UINT)pk_cflg->iflgptn;

	wi_CommonLock();
	for( flgid = 1; flgid < TMAX_MAXFLG; flgid++ ){

		//! イベントフラグを生成する.
		ercd = wi_CreateEvFlag( flgid, &obj );
		if( ercd == E_OK ){
			ercd = (ER_ID)flgid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
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
ER		set_flg( ID flgid, FLGPTN setptn )
{
	ER ercd;

	wi_CommonLock();

	//! イベントフラグをセットする.
	ercd = wi_SetEvFlag( flgid, (UINT)setptn );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグのセット (非タスクコンテキストからの呼出し用).
 *
 *	@param	[in]	flgid	イベントフラグID番号.
 *	@param	[in]	setptn	セットするビットパターン.
 *
 *	@retval	エラーコード.
 */
ER		iset_flg( ID flgid, FLGPTN setptn )
{
	//! イベントフラグをセットする.
	return set_flg( flgid, setptn );
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
ER		clr_flg( ID flgid, FLGPTN clrptn )
{
	ER ercd;

	wi_CommonLock();

	//! イベントフラグをクリアする.
	ercd = wi_ClearEvFlag( flgid, (UINT)clrptn );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ待ち (タイムアウトなし).
 *
 *	@param	[in]	flgid		イベントフラグID番号.
 *	@param	[in]	waiptn		待ちビットパターン.
 *	@param	[in]	wfmode		待ちモード.
 *	@param	[out]	p_flgptn	待ち解除時のビットパターンを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		wai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn )
{
	//! タイムアウトなしでイベント待ちをする.
	return twai_flg( flgid, waiptn, wfmode, p_flgptn, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ待ち (ポーリング).
 *
 *	@param	[in]	flgid		イベントフラグID番号.
 *	@param	[in]	waiptn		待ちビットパターン.
 *	@param	[in]	wfmode		待ちモード.
 *	@param	[out]	p_flgptn	待ち解除時のビットパターンを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		pol_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn )
{
	//! イベントが発生しているかどうかを調べる.
	return twai_flg( flgid, waiptn, wfmode, p_flgptn, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ待ち (タイムアウトあり).
 *
 *	@param	[in]	flgid		イベントフラグID番号.
 *	@param	[in]	waiptn		待ちビットパターン.
 *	@param	[in]	wfmode		待ちモード.
 *	@param	[out]	p_flgptn	待ち解除時のビットパターンを格納する領域のポインタ.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		twai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! イベント待ちをする.
	ercd = wi_WaitEvFlag( flgid, p_flgptn, waiptn, wfmode & ~TWF_CLR, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	イベントフラグ状態の参照.
 *
 *	@param	[in]	flgid	イベントフラグID番号.
 *	@param	[out]	pk_rflg	イベントフラグ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_flg( ID flgid, T_RFLG *pk_rflg )
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
		pk_rflg->wtskid = sts.WaitId;
		pk_rflg->flgptn = (FLGPTN)sts.FlgVal;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 同期･通信機能 (データキュー).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	データキューの生成.
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[in]	pk_cdtq	データキュー生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_dtq( ID dtqid, const T_CDTQ *pk_cdtq )
{
	ER			ercd;
	WIDTQOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cdtq ){
		return E_PAR;
	}
	//! データキュー生成情報をコピーする.
	memset( &obj, 0, sizeof(WIDTQOBJ) );
	obj.Attribute = pk_cdtq->dtqatr;
	obj.QueSize   = pk_cdtq->dtqcnt;

	wi_CommonLock();

	//! データキューを生成する.
	ercd = wi_CreateDataQueue( (DWORD)dtqid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	データキューの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_cdtq	データキュー生成情報構造体のポインタ.
 *
 *	@retval	生成したデータキューのデータキューIDまたはエラーコード.
 */
ER_ID	acre_dtq( const T_CDTQ *pk_cdtq )
{
	ID			dtqid;
	ER			ercd;
	WIDTQOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cdtq ){
		return E_PAR;
	}
	//! データキュー生成情報をコピーする.
	memset( &obj, 0, sizeof(WIDTQOBJ) );
	obj.Attribute = pk_cdtq->dtqatr;
	obj.QueSize   = pk_cdtq->dtqcnt;

	wi_CommonLock();

	for( dtqid = 1; dtqid < TMAX_MAXDTQ; dtqid++ ){
		//! データキューを生成する.
		ercd = wi_CreateDataQueue( dtqid, &obj );
		if( ercd == E_OK ){
			ercd  = dtqid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	データキューの削除.
 *
 *	@param	[in]	dtqid	データキューID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_dtq( ID dtqid )
{
	ER ercd;

	wi_CommonLock();

	//! データキューを削除する.
	ercd = wi_DeleteDataQueue( dtqid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	データキューへの送信 (タイムアウトなし).
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[in]	data	データキューに送信するデータ.
 *
 *	@retval	エラーコード.
 */
ER		snd_dtq( ID dtqid, VP_INT data )
{
	//! タイムアウトなしでデータキューへデータを送信する.
	return tsnd_dtq( dtqid, data, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	データキューへの送信 (ポーリング).
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[in]	data	データキューに送信するデータ.
 *
 *	@retval	エラーコード.
 */
ER		psnd_dtq( ID dtqid, VP_INT data )
{
	//! 送信待ちなしでデータキューへデータを送信する.
	return tsnd_dtq( dtqid, data, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	データキューへの送信 (非タスクコンテキストからの呼出し用).
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[in]	data	データキューに送信するデータ.
 *
 *	@retval	エラーコード.
 */
ER		ipsnd_dtq( ID dtqid, VP_INT data )
{
	//! データキューへデータを送信する.
	return psnd_dtq( dtqid, data );
}

/****************************************************************************/
/*!
 *	@brief	データキューへの送信 (タイムアウトあり).
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[in]	data	データキューに送信するデータ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tsnd_dtq( ID dtqid, VP_INT data, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! データキューへデータを送信する.
	ercd = wi_SendDataQueue( dtqid, (DWORD)data, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	データキューへ強制送信.
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[in]	data	データキューに送信するデータ.
 *
 *	@retval	エラーコード.
 */
ER		fsnd_dtq( ID dtqid, VP_INT data )
{
	ER ercd;

	wi_CommonLock();

	//! データキューへデータを強制送信する.
	ercd = wi_ForceSendDataQueue( dtqid, (DWORD)data );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	データキューへ強制送信 (非タスクコンテキストからの呼出し用).
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[in]	data	データキューに送信するデータ.
 *
 *	@retval	エラーコード.
 */
ER		ifsnd_dtq( ID dtqid, VP_INT data )
{
	//! データキューへデータを強制送信する.
	return fsnd_dtq( dtqid, data );
}

/****************************************************************************/
/*!
 *	@brief	データキューからの受信 (タイムアウトなし).
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[out]	p_data	データキューから受信したデータを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		rcv_dtq( ID dtqid, VP_INT *p_data )
{
	//! タイムアウトなしでデータキューからデータを受信する.
	return trcv_dtq( dtqid, p_data, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	データキューからの受信 (ポーリング).
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[out]	p_data	データキューから受信したデータを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		prcv_dtq( ID dtqid, VP_INT *p_data )
{
	//! データ受信待ちなしでデータキューからデータを受信する.
	return trcv_dtq( dtqid, p_data, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	データキューからの受信 (タイムアウトあり).
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[out]	p_data	データキューから受信したデータを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		trcv_dtq( ID dtqid, VP_INT *p_data, TMO tmout )
{
	ER		ercd;
	DWORD	data;

	//! 引数が不正な場合はエラーにする.
	if( !p_data ){
		return E_PAR;
	}
	wi_CommonLock();

	//! データキューからデータを受信する.
	ercd = wi_ReceiveDataQueue( dtqid, &data, tmout );
	if( ercd == E_OK ){
		*p_data = (VP_INT)data;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	データキューの状態参照.
 *
 *	@param	[in]	dtqid	データキューID番号.
 *	@param	[out]	pk_rdtq	データキュー状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_dtq( ID dtqid, T_RDTQ *pk_rdtq )
{
	ER			ercd;
	WIDTQSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rdtq ){
		return E_PAR;
	}
	wi_CommonLock();

	//! データキューの状態を取得する.
	ercd = wi_RefarenceDataQueue( dtqid, &sts );
	if( ercd == E_OK ){
		pk_rdtq->stskid  = sts.SndWaitId;
		pk_rdtq->rtskid  = sts.RcvWaitId;
		pk_rdtq->sdtqcnt = sts.DataCnt;
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
	obj.MaxPriority = pk_cmbx->maxmpri;

	wi_CommonLock();

	//! メールボックスを生成する.
	ercd = wi_CreateMailBox( mbxid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メールボックスの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_cmbx	メールボックス生成情報構造体のポインタ.
 *
 *	@retval	生成したメールボックスのメールボックスIDまたはエラーコード.
 */
ER_ID	acre_mbx( const T_CMBX *pk_cmbx )
{
	ID			mbxid;
	ER			ercd;
	WIMBXOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmbx ){
		return E_PAR;
	}
	//! メールボックス生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMBXOBJ) );
	obj.Attribute   = pk_cmbx->mbxatr;
	obj.MaxPriority = pk_cmbx->maxmpri;

	wi_CommonLock();

	for( mbxid = 1; mbxid < TMAX_MAXMBX; mbxid++ ){
		//! メールボックスを生成する.
		ercd = wi_CreateMailBox( mbxid, &obj );
		if( ercd == E_OK ){
			ercd = mbxid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
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
 *	@param	[in]	mbxid	メールボックスID番号.
 *	@param	[out]	ppk_msg	メッセージ･パケットのアドレスを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		rcv_msg( ID mbxid, T_MSG **ppk_msg )
{
	//! タイムアウトなしでメールボックスからメッセージを受信する.
	return trcv_msg( mbxid, ppk_msg, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	メールボックスからの受信 (ポーリング).
 *
 *	@param	[in]	mbxid	メールボックスID番号.
 *	@param	[out]	ppk_msg	メッセージ･パケットのアドレスを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		prcv_msg( ID mbxid, T_MSG **ppk_msg )
{
	//! 受信待ちなしでメールボックスからメッセージを受信する.
	return trcv_msg( mbxid, ppk_msg, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	メールボックスからの受信 (タイムアウトあり).
 *
 *	@param	[in]	mbxid	メールボックスID番号.
 *	@param	[out]	ppk_msg	メッセージ･パケットのアドレスを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		trcv_msg( ID mbxid, T_MSG **ppk_msg, TMO tmout )
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
 *	@param	[in]	mbxid	メールボックスID番号.
 *	@param	[out]	pk_rmbx	メールボックス状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_mbx( ID mbxid, T_RMBX *pk_rmbx )
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
		pk_rmbx->wtskid = sts.WaitId;
		pk_rmbx->pk_msg = sts.NextMsg;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 拡張同期･通信機能 (ミューテックス).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	ミューテックスの生成.
 *
 *	@param	[in]	mtxid	ミューテックスID番号.
 *	@param	[in]	pk_cmtx	ミューテックス生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_mtx( ID mtxid, const T_CMTX *pk_cmtx )
{
	ER			ercd;
	WIMTXOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmtx ){
		return E_PAR;
	}
	//! ミューテックス生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMTXOBJ) );
	obj.Attribute = pk_cmtx->mtxatr;
	obj.CeilPri   = pk_cmtx->ceilpri;

	wi_CommonLock();

	//! ミューテックスを生成する.
	ercd = wi_CreateMutex( mtxid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_cmtx	ミューテックス生成情報構造体のポインタ.
 *
 *	@retval	生成したミューテックスのID番号またはエラーコード.
 */
ER_ID	acre_mtx( const T_CMTX *pk_cmtx )
{
	ID			mtxid;
	ER			ercd;
	WIMTXOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmtx ){
		return E_PAR;
	}
	//! ミューテックス生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMTXOBJ) );
	obj.Attribute = pk_cmtx->mtxatr;
	obj.CeilPri   = pk_cmtx->ceilpri;

	wi_CommonLock();

	for( mtxid = 1; mtxid < TMAX_MAXMTX; mtxid++ ){
		//! ミューテックスを生成する.
		ercd = wi_CreateMutex( mtxid, &obj );
		if( ercd == E_OK ){
			ercd  = mtxid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスの削除.
 *
 *	@param	[in]	mtxid	ミューテックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_mtx( ID mtxid )
{
	ER ercd;

	wi_CommonLock();

	//! ミューテックスを削除する.
	ercd = wi_DeleteMutex( mtxid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスのロック (タイムアウトなし).
 *
 *	@param	[in]	mtxid	ミューテックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		loc_mtx( ID mtxid )
{
	//! タイムアウトなしでミューテックスをロックする.
	return tloc_mtx( mtxid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスのロック (ポーリング).
 *
 *	@param	[in]	mtxid	ミューテックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		ploc_mtx( ID mtxid )
{
	//! ミューテックスをロックできるかどうか調べる.
	return tloc_mtx( mtxid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスのロック (タイムアウトあり).
 *
 *	@param	[in]	mtxid	ミューテックスID番号.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tloc_mtx( ID mtxid, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! ミューテックスをロックする.
	ercd = wi_LockMutex( mtxid, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスのロックを解除.
 *
 *	@param	[in]	mtxid	ミューテックスID番号.
 *
 *	@retval	エラーコード.
 */
ER		unl_mtx( ID mtxid )
{
	ER ercd;

	wi_CommonLock();

	//! ミューテックスのロックを解除する.
	ercd = wi_UnlockMutex( mtxid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ミューテックスの状態参照.
 *
 *	@param	[in]	mtxid	ミューテックスID番号.
 *	@param	[out]	pk_rmbx	ミューテックス状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_mtx( ID mtxid, T_RMTX *pk_rmtx )
{
	ER			ercd;
	WIMTXSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rmtx ){
		return E_PAR;
	}
	wi_CommonLock();

	//! ミューテックスの状態を取得する.
	ercd = wi_RefarenceMutex( mtxid, &sts );
	if( ercd == E_OK ){
		pk_rmtx->htskid = sts.LockId;
		pk_rmtx->wtskid = sts.WaitId;
	}
	wi_CommonUnlock();
	return E_OK;
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
	obj.SndAttr = pk_cmbf->mbfatr;
	obj.RcvAttr = pk_cmbf->mbfatr & ~TA_TPRI;
	obj.MsgSize = pk_cmbf->mbfsz;
	obj.MaxMsg  = pk_cmbf->maxmsz;

	wi_CommonLock();

	//! メッセージバッファを生成する.
	ercd = wi_CreateMsgBuffer( mbfid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_cmbf	メッセージバッファ生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER_ID	acre_mbf( const T_CMBF *pk_cmbf )
{
	ID			mbfid;
	ER			ercd;
	WIMBFOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmbf ){
		return E_PAR;
	}
	//! メッセージバッファ生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMBFOBJ) );
	obj.SndAttr = pk_cmbf->mbfatr;
	obj.RcvAttr = pk_cmbf->mbfatr & ~TA_TPRI;
	obj.MsgSize = pk_cmbf->mbfsz;
	obj.MaxMsg  = pk_cmbf->maxmsz;

	wi_CommonLock();

	for( mbfid = 1; mbfid < TMAX_MAXMBF; mbfid++ ){
		//! メッセージバッファを生成する.
		ercd = wi_CreateMsgBuffer( mbfid, &obj );
		if( ercd == E_OK ){
			ercd  = mbfid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
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
ER		snd_mbf( ID mbfid, VP msg, UINT msgsz )
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
ER		psnd_mbf( ID mbfid, VP msg, UINT msgsz )
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
ER		tsnd_mbf( ID mbfid, VP msg, UINT msgsz, TMO tmout )
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
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[out]	msg		メッセージを格納する領域のポインタ.
 *
 *	@retval	メッセージサイズまたはエラーコード.
 */
ER_UINT	rcv_mbf( ID mbfid, VP msg )
{
	//! タイムアウトなしでメッセージバッファからメッセージを受信する.
	return trcv_mbf( mbfid, msg, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファからの受信 (ポーリング).
 *
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[out]	msg		メッセージを格納する領域のポインタ.
 *
 *	@retval	メッセージサイズまたはエラーコード.
 */
ER_UINT	prcv_mbf( ID mbfid, VP msg )
{
	//! 受信待ちなしでメッセージバッファからメッセージを受信する.
	return trcv_mbf( mbfid, msg, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファからの受信 (タイムアウトあり).
 *
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[out]	msg		メッセージを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	メッセージサイズまたはエラーコード.
 */
ER_UINT	trcv_mbf( ID mbfid, VP msg, TMO tmout )
{
	ER		ercd;
	INT		size;

	wi_CommonLock();

	//! メッセージバッファからメッセージを受信する.
	ercd = wi_ReceiveMsgBuffer( mbfid, msg, &size, tmout );
	if( ercd == E_OK ){
		ercd  = size;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	メッセージバッファの状態参照.
 *
 *	@param	[in]	mbfid	メッセージバッファID番号.
 *	@param	[out]	pk_rmbf	メッセージバッファ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_mbf( ID mbfid, T_RMBF *pk_rmbf )
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
		pk_rmbf->rtskid  = sts.RcvWaitId;
		pk_rmbf->stskid  = sts.SndWaitId;
		pk_rmbf->smsgcnt = sts.MsgSize;
		pk_rmbf->fmbfsz  = sts.FreeSize;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * 拡張同期･通信機能 (ランデブポート).
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

	wi_CommonLock();

	//! ランデブポートを生成する.
	ercd = wi_CreateRendPort( porid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブポートの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_cpor	ランデブポート生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER_ID	acre_por( const T_CPOR *pk_cpor )
{
	ID			porid;
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

	wi_CommonLock();

	for( porid = 1; porid < TMAX_MAXPOR; porid++ ){
		//! ランデブポートを生成する.
		ercd = wi_CreateRendPort( porid, &obj );
		if( ercd == E_OK ){
			ercd  = porid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
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
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	calptn		呼び出し側選択条件のビットパターン.
 *	@param	[in]	msg			メッセージのアドレス.
 *	@param	[in]	cmsgsz		呼び出しメッセージのサイズ.
 *
 *	@retval	応答メッセージのサイズまたはエラーコード.
 */
ER_UINT	cal_por( ID porid, RDVPTN calptn, VP msg, UINT cmsgsz )
{
	//! タイムアウトなしでランデブを呼び出す.
	return tcal_por( porid, calptn, msg, cmsgsz, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	ランデブ呼び出し (タイムアウトあり).
 *
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	calptn		呼び出し側選択条件のビットパターン.
 *	@param	[in]	msg			メッセージのアドレス.
 *	@param	[in]	cmsgsz		呼び出しメッセージのサイズ.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	応答メッセージのサイズまたはエラーコード.
 */
ER_UINT	tcal_por( ID porid, RDVPTN calptn, VP msg, UINT cmsgsz, TMO tmout )
{
	ER	ercd;
	INT	size;

	wi_CommonLock();

	//! ランデブを呼び出す.
	ercd = wi_CallRendPort( porid, calptn, msg, cmsgsz, &size, tmout );
	if( ercd == E_OK ){
		ercd  = size;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブ受け付け (タイムアウトなし).
 *
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	acpptn		受け付け側選択条件のビットパターン.
 *	@param	[out]	p_rdvno		ランデブ番号を格納する領域のポインタ.
 *	@param	[out]	msg			呼び出しメッセージを格納する領域のポインタ.
 *
 *	@retval	呼び出しメッセージのサイズまたはエラーコード.
 */
ER_UINT	acp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg )
{
	//! タイムアウトなしでランデブを受け付ける.
	return tacp_por( porid, acpptn, p_rdvno, msg, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	ランデブ受け付け (ポーリング).
 *
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	acpptn		受け付け側選択条件のビットパターン.
 *	@param	[out]	p_rdvno		ランデブ番号を格納する領域のポインタ.
 *	@param	[out]	msg			呼び出しメッセージを格納する領域のポインタ.
 *
 *	@retval	呼び出しメッセージのサイズまたはエラーコード.
 */
ER_UINT	pacp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg )
{
	//! 呼び出し待ちなしでランデブを受け付ける.
	return tacp_por( porid, acpptn, p_rdvno, msg, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	ランデブ受け付け (タイムアウトあり).
 *
 *	@param	[in]	porid		ランデブポートID番号.
 *	@param	[in]	acpptn		受け付け側選択条件のビットパターン.
 *	@param	[out]	p_rdvno		ランデブ番号を格納する領域のポインタ.
 *	@param	[out]	msg			呼び出しメッセージを格納する領域のポインタ.
 *	@param	[in]	tmout		タイムアウト設定.
 *
 *	@retval	呼び出しメッセージのサイズまたはエラーコード.
 */
ER_UINT	tacp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg, TMO tmout )
{
	ER	ercd;
	INT	size;

	wi_CommonLock();

	//! ランデブを受け付ける.
	ercd = wi_AcceptRendPort( porid, acpptn, p_rdvno, msg, &size, tmout );
	if( ercd == E_OK ){
		ercd  = size;
	}
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
ER		fwd_por( ID porid, RDVPTN calptn, RDVNO rdvno, VP msg, UINT cmsgsz )
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
ER		rpl_rdv( RDVNO rdvno, VP msg, UINT cmsgsz )
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
 *	@param	[in]	porid	ランデブ･ポートID番号.
 *	@param	[out]	pk_rpor	ランデブポート状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_por( ID porid, T_RPOR *pk_rpor )
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
		pk_rpor->ctskid = sts.CalWaitId;
		pk_rpor->atskid = sts.AcpWaitId;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	ランデブ状態の参照.
 *
 *	@param	[in]	rdvno	ランデブ番号.
 *	@param	[out]	pk_rrdv	ランデブ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_rdv( RDVNO rdvno, T_RRDV *pk_rrdv )
{
	ER			ercd;
	WIRDVSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rrdv ){
		return E_PAR;
	}
	wi_CommonLock();

	//! ランデブ状態を取得する.
	ercd = wi_RefarenceRendStat( rdvno, &sts );
	if( ercd == E_OK ){
		pk_rrdv->wtskid = sts.WaitId;
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
	obj.Attribute = pk_cmpf->mpfatr;
	obj.BlockCnt  = pk_cmpf->blkcnt;
	obj.BlockSize = pk_cmpf->blfsz;

	wi_CommonLock();

	//! 固定長メモリプールを生成する.
	ercd = wi_CreateFixedMemPool( mpfid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリプールの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_cmpf	メモリプール生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		acre_mpf( const T_CMPF *pk_cmpf )
{
	ID			mpfid;
	ER			ercd;
	WIMPFOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmpf ){
		return E_PAR;
	}
	//! 固定長メモリプール生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMPFOBJ) );
	obj.Attribute = pk_cmpf->mpfatr;
	obj.BlockCnt  = pk_cmpf->blkcnt;
	obj.BlockSize = pk_cmpf->blfsz;

	wi_CommonLock();

	for( mpfid = 1; mpfid < TMAX_MAXMPF; mpfid++ ){
		//! 固定長メモリプールを生成する.
		ercd = wi_CreateFixedMemPool( mpfid, &obj );
		if( ercd == E_OK ){
			ercd  = mpfid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
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
 *	@param	[in]	mpfid	メモリプールID番号.
 *	@param	[out]	p_blf	メモリブロックのアドレスを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		get_blf(ID mpfid, VP *p_blf )
{
	//! タイムアウトなしで固定長メモリブロックを獲得する.
	return tget_blf( mpfid, p_blf, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリブロックの獲得 (ポーリング).
 *
 *	@param	[in]	mpfid	メモリプールID番号.
 *	@param	[out]	p_blf	メモリブロックのアドレスを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		pget_blf(ID mpfid, VP *p_blf )
{
	//! 獲得待ちなしで固定長メモリブロックを獲得する.
	return tget_blf( mpfid, p_blf, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	固定長メモリブロックの獲得 (タイムアウトあり).
 *
 *	@param	[in]	mpfid	メモリプールID番号.
 *	@param	[out]	p_blf	メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tget_blf(ID mpfid, VP *p_blf, TMO tmout )
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
 *	@brief	固定長メモリ･ブロックの返却.
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
 *	@param	[in]	mpfid	メモリプールID番号.
 *	@param	[out]	pk_rmpf	メモリプール状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_mpf( ID mpfid , T_RMPF *pk_rmpf )
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
		pk_rmpf->wtskid  = sts.WaitId;
		pk_rmpf->fblkcnt = sts.FreeBlock;
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
 *	@param	[in]	mplid	メモリプールID番号.
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
 *	@brief	可変長メモリプールの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_cmpl	メモリプール生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		acre_mpl( const T_CMPL *pk_cmpl )
{
	ID			mplid;
	ER			ercd;
	WIMPLOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_cmpl ){
		return E_PAR;
	}
	//! 可変長メモリプール生成情報をコピーする.
	memset( &obj, 0, sizeof(WIMPLOBJ) );
	obj.Attribute = pk_cmpl->mplatr;
	obj.MemSize   = pk_cmpl->mplsz;

	wi_CommonLock();

	for( mplid = 1; mplid < TMAX_MAXMPL; mplid++ ){
		//! 可変長メモリプールを生成する.
		ercd = wi_CreateVarMemPool( mplid, &obj );
		if( ercd == E_OK ){
			ercd  = mplid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの削除.
 *
 *	@param	[in]	mpfid	メモリプールID番号.
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
 *	@param	[in]	mplid	メモリプールID番号.
 *	@param	[in]	blksz	メモリブロックのサイズ.
 *	@param	[in]	p_blk	メモリブロックのアドレスを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		get_mpl( ID mplid, UINT blksz, VP *p_blk )
{
	//! タイムアウトなしで可変長メモリブロックを獲得する.
	return tget_mpl( mplid, blksz, p_blk, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリブロックの獲得 (ポーリング).
 *
 *	@param	[in]	mplid	メモリプールID番号.
 *	@param	[in]	blksz	メモリブロックのサイズ.
 *	@param	[in]	p_blk	メモリブロックのアドレスを格納する領域のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		pget_mpl( ID mplid, UINT blksz, VP *p_blk )
{
	//! 獲得待ちなしで可変長メモリブロックを獲得する.
	return tget_mpl( mplid, blksz, p_blk, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリブロックの獲得 (タイムアウトあり).
 *
 *	@param	[in]	mplid	メモリプールID番号.
 *	@param	[in]	blksz	メモリブロックのサイズ.
 *	@param	[in]	p_blk	メモリブロックのアドレスを格納する領域のポインタ.
 *	@param	[in]	tmout	タイムアウト設定.
 *
 *	@retval	エラーコード.
 */
ER		tget_mpl( ID mplid, UINT blksz, VP *p_blk, TMO tmout )
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

ER rel_mpl(ID mplid, VP blk)
{
	return rel_blk(mplid, blk);
}

/****************************************************************************/
/*!
 *	@brief	可変長メモリプールの参照.
 *
 *	@param	[in]	mpfid	メモリプールID番号.
 *	@param	[out]	pk_rmpl	メモリプール状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_mpl( ID mpfid, T_RMPL *pk_rmpl )
{
	ER			ercd;
	WIMPLSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rmpl ){
		return E_PAR;
	}
	wi_CommonLock();

	//! 可変長メモリプールの状態を取得する.
	ercd = wi_RefarenceVarMemPool( mpfid, &sts );
	if( ercd == E_OK ){
		pk_rmpl->wtskid = sts.WaitId;
		pk_rmpl->fmplsz = sts.TotalFreeSize;
		pk_rmpl->fblksz = sts.MaxFreeSize;
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

/****************************************************************************/
/*!
 *	@brief	タイムティックの供給.
 *
 *	@param	なし.
 *
 *	@retval	エラーコード.
 */
ER		isig_tim( void )
{
	return E_NOSPT;
}

/***************************************
 *
 * 時間管理機能 (周期ハンドラ).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	周期ハンドラの生成.
 *
 *	@param	[in]	cycid	周期ハンドラID番号.
 *	@param	[in]	pk_ccyc	周期ハンドラ生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_cyc( ID cycid, const T_CCYC *pk_ccyc )
{
	ER			ercd;
	WICYCOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_ccyc ){
		return E_PAR;
	}
	//! 周期ハンドラ定義情報をコピーする.
	memset( &obj, 0, sizeof(WICYCOBJ) );
	obj.Attribute = pk_ccyc->cycatr;
	obj.CycAdr    = pk_ccyc->cychdr;
	obj.Active    = (pk_ccyc->cycatr & TA_STA) ? TRUE : FALSE;
	obj.ExtInfo   = pk_ccyc->exinf;
	obj.CycleTime = ((DWORDLONG)(pk_ccyc->cyctim.utime) << 32) + (DWORDLONG)(pk_ccyc->cyctim.ltime);
	obj.CyclePhs  = ((DWORDLONG)(pk_ccyc->cycphs.utime) << 32) + (DWORDLONG)(pk_ccyc->cycphs.ltime);

	wi_CommonLock();

	//! 周期ハンドラを登録する.
	ercd = wi_DefineCycleHadler( cycid, &obj, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_ccyc	周期ハンドラ生成情報構造体のポインタ.
 *
 *	@retval	生成した周期ハンドラのハンドラIDまたはエラーコード.
 */
ER		acre_cyc( const T_CCYC *pk_ccyc )
{
	ER_ID		ercd;
	ID			cycid;
	WICYCOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_ccyc ){
		return E_PAR;
	}
	//! 周期ハンドラ定義情報をコピーする.
	memset( &obj, 0, sizeof(WICYCOBJ) );
	obj.Attribute = pk_ccyc->cycatr;
	obj.CycAdr    = pk_ccyc->cychdr;
	obj.Active    = (pk_ccyc->cycatr & TA_STA) ? TRUE : FALSE;
	obj.ExtInfo   = pk_ccyc->exinf;
	obj.CycleTime = ((DWORDLONG)(pk_ccyc->cyctim.utime) << 32) + (DWORDLONG)(pk_ccyc->cyctim.ltime);
	obj.CyclePhs  = ((DWORDLONG)(pk_ccyc->cycphs.utime) << 32) + (DWORDLONG)(pk_ccyc->cycphs.ltime);

	wi_CommonLock();

	for( cycid = 1; cycid < TMAX_MAXCYC; cycid++ ){

		//! 周期ハンドラを登録する.
		ercd = wi_DefineCycleHadler( cycid, &obj, FALSE );
		if( ercd == E_OK ){
			ercd = cycid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの削除.
 *
 *	@param	[in]	cycid	周期ハンドラID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_cyc( ID cycid )
{
	ER ercd;

	wi_CommonLock();

	//! 周期ハンドラを削除する.
	ercd = wi_DeleteCycleHadler( cycid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの起動.
 *
 *	@param	[in]	cycid	周期ハンドラID番号.
 *
 *	@retval	エラーコード.
 */
ER		sta_cyc( ID cycid )
{
	ER ercd;

	wi_CommonLock();

	//! 周期ハンドラを起動する.
	ercd = wi_ActionCycleHadler( cycid, TRUE, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの停止.
 *
 *	@param	[in]	cycid	周期ハンドラID番号.
 *
 *	@retval	エラーコード.
 */
ER		stp_cyc( ID cycid )
{
	ER ercd;

	wi_CommonLock();

	//! 周期ハンドラを停止する.
	ercd = wi_ActionCycleHadler( cycid, FALSE, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	周期ハンドラの状態参照.
 *
 *	@param	[in]	cycid	周期ハンドラID番号.
 *	@param	[out]	pk_rcyc	周期ハンドラ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_cyc( ID cycid, T_RCYC *pk_rcyc )
{
	ER			ercd;
	WICYCSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_rcyc ){
		return E_PAR;
	}
	wi_CommonLock();

	//! 周期ハンドラの状態を取得する.
	ercd = wi_RefarenceCycleHadler( cycid, &sts );
	if( ercd == E_OK ){
		pk_rcyc->cycstat       = sts.Active ? TCYC_STA : TCYC_STP;
		pk_rcyc->lefttim.utime = (short)(sts.LeftTime >> 32 & 0x0000FFFF);
		pk_rcyc->lefttim.ltime = (long )(sts.LeftTime       & 0xFFFFFFFF);
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
 *	@brief	アラーム･ハンドラの生成.
 *
 *	@param	[in]	almid	アラーム･ハンドラID番号.
 *	@param	[in]	pk_calm	アラーム･ハンドラ生成情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		cre_alm( ID almid, const T_CALM *pk_calm )
{
	ER			ercd;
	WIALMOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_calm ){
		return E_PAR;
	}
	//! アラーム･ハンドラ登録情報をコピーする.
	memset( &obj, 0, sizeof(WIALMOBJ) );
	obj.Attribute = pk_calm->almatr;
	obj.ExtInfo   = pk_calm->exinf;
	obj.AlmAdr    = pk_calm->almhdr;

	wi_CommonLock();

	//! アラーム･ハンドラを登録する.
	ercd = wi_DefineAlarmHadler( almid, &obj, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの生成 (ID番号自動割り付け).
 *
 *	@param	[in]	pk_calm	アラーム･ハンドラ生成情報構造体のポインタ.
 *
 *	@retval	生成したアラーム･ハンドラのハンドラIDまたはエラーコード.
 */
ER_ID	acre_alm( const T_CALM *pk_calm )
{
	ER_ID		ercd;
	ID			almid;
	WIALMOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_calm ){
		return E_PAR;
	}
	//! アラーム･ハンドラ登録情報をコピーする.
	memset( &obj, 0, sizeof(WIALMOBJ) );
	obj.Attribute = pk_calm->almatr;
	obj.ExtInfo   = pk_calm->exinf;
	obj.AlmAdr    = pk_calm->almhdr;

	wi_CommonLock();

	for( almid = 1; almid < TMAX_MAXALM; almid++ ){

		//! アラーム･ハンドラを登録する.
		ercd = wi_DefineAlarmHadler( almid, &obj, FALSE );
		if( ercd == E_OK ){
			ercd  = almid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの削除.
 *
 *	@param	[in]	almid	アラーム･ハンドラID番号.
 *
 *	@retval	エラーコード.
 */
ER		del_alm( ID almid )
{
	ER ercd;

	wi_CommonLock();

	//! アラーム･ハンドラを削除する.
	ercd = wi_DeleteAlarmHadler( almid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの起動.
 *
 *	@param	[in]	almid	アラーム･ハンドラID番号.
 *
 *	@retval	エラーコード.
 */
ER		sta_alm( ID almid, RELTIM almtim )
{
	ER ercd;

	wi_CommonLock();

	//! アラーム･ハンドラを起動する.
	ercd = wi_StartAlarmHadler( almid, ((DWORDLONG)(almtim.utime) << 32) + (DWORDLONG)(almtim.ltime) );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの停止.
 *
 *	@param	[in]	almid	アラーム･ハンドラID番号.
 *
 *	@retval	エラーコード.
 */
ER		stp_alm( ID almid )
{
	ER ercd;

	wi_CommonLock();

	//! アラーム･ハンドラを停止する.
	ercd = wi_StopAlarmHadler( almid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	アラーム･ハンドラの状態参照.
 *
 *	@param	[in]	almid	アラーム･ハンドラID番号.
 *	@param	[out]	pk_ralm	アラーム･ハンドラ状態を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		ref_alm( ID almid, T_RALM *pk_ralm )
{
	ER			ercd;
	WIALMSTAT	sts;

	//! 引数が不正な場合はエラーにする.
	if( !pk_ralm ){
		return E_PAR;
	}
	wi_CommonLock();

	//! アラーム･ハンドラの状態を取得する.
	ercd = wi_RefarenceAlarmHadler( almid, &sts );
	if( ercd == E_OK ){
		pk_ralm->almstat       = sts.Active ? TALM_STA : TALM_STP;
		pk_ralm->lefttim.utime = (short)(sts.LeftTime >> 32 & 0x0000FFFF);
		pk_ralm->lefttim.ltime = (long )(sts.LeftTime       & 0xFFFFFFFF);
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
 *	@param	[in]	intno		割り込みハンドラ番号.
 *	@param	[in]	pk_dinh		割り込みハンドラ定義情報構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		def_inh( INTNO intno, const T_DINH *pk_dinh )
{
	ER			ercd;
	WIINTOBJ	obj;

	//! 引数が不正な場合はエラーにする.
	if( !pk_dinh ){
		return E_PAR;
	}
	//! 割り込みハンドラ定義情報をコピーする.
	memset( &obj, 0, sizeof(WIINTOBJ) );
	obj.Attribute = pk_dinh->inhatr;
	obj.IntrAdr   = pk_dinh->inthdr;

	wi_CommonLock();

	//! 割り込みハンドラを登録する.
	ercd = wi_DefineIntrruptHander( intno, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	割り込みの禁止.
 *
 *	@param	[in]	intno		割り込みハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		dis_int( INTNO intno )
{
	ER ercd;

	wi_CommonLock();

	//! 割り込みを禁止する.
	ercd = wi_DisableIntrrupt( intno );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	割り込みの許可.
 *
 *	@param	[in]	intno		割り込みハンドラ番号.
 *
 *	@retval	エラーコード.
 */
ER		ena_int( INTNO intno )
{
	ER ercd;

	wi_CommonLock();

	//! 割り込みを許可する.
	ercd = wi_EnableIntrrupt( intno );

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

ER iloc_cpu(void)
{
	return loc_cpu();
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

ER iunl_cpu(void)
{
    return unl_cpu();
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
 *	@param	[out]	pk_rver		バージョン情報を格納する構造体のポインタ.
 *
 *	@retval	エラーコード.
 */
ER		get_ver( T_RVER *pk_rver )
{
	ER ercd;

	wi_CommonLock();

	//! バージョン情報を取得する.
	ercd = wi_GetVersion( pk_rver );

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

#endif	// __ITRON4__

/* End of file */
