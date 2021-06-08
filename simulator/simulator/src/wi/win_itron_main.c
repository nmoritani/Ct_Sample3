/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
 /*!
  *	@file	win_itron_main.c
  *
  *	@brief	Windows版 iTRONサービスコールのメインルーチン.
  *
  *	@author	金澤 宣明
  */

#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "kprintf.h"
#include "win_itron.h"
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
#include "wi_interrupt.h"
#include "wi_systemmgr.h"
#include "wi_resource.h"
#include "kernel_id.h"
#include "VMI.h"
#include "gdi_draw_test.h"
#include "gdi_config.h"
#include "WinDrawTask.h"



  /****************************************************************************
   *
   * システム管理スレッドへのメッセージ.
   *
   ****************************************************************************/
#define	WM_SYSTEM_EXIT	(WM_USER + 1)		//!< システムの終了.
#define	WM_DELETE_TASK	(WM_USER + 2)		//!< タスクの削除.

   /****************************************************************************
	*
	* ローカル関数定義.
	*
	****************************************************************************/
static BOOL			WinITRON_Init(void);
static void			WinITRON_Quit(void);
static unsigned int __stdcall SystemTask(void* arg);
static TASK			InitTask(VP_INT stacd);

/****************************************************************************
 *
 * ローカル変数定義.
 *
 ****************************************************************************/
static HANDLE	SystemThread = NULL;		//!< システム管理スレッドのハンドル.
static DWORD	ThreadId = 0;			//!< システム管理スレッドの識別子.


/****************************************************************************/
/*!
 *	@brief	iTRONサービスコールの初期処理.
 *
 *	@param	なし.
 *
 *	@retval	TRUE = OK. / FALSE = NG.
 */
static BOOL		WinITRON_Init(void)
{
	unsigned int tid;

	//! システム管理スレッドを起動する.
	SystemThread = (HANDLE)_beginthreadex(NULL, 0, &SystemTask, NULL, 0, &tid);

	//! タスクの優先度を設定する.
	SetThreadPriority(SystemThread, THREAD_PRIORITY_HIGHEST);

	//! プロセスの優先順位クラスを通常のアプリケーションより少し低くする.
	if (!SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS)) {
		return FALSE;
	}
	//! システム状態管理機能の初期処理.
	wi_InitSysMgr();

	//	//! 割り込み機能の初期処理.
	//	wi_InitInterrupt();

	//! 共通関数の初期処理.
	if (!wi_CommonInit()) {
		return FALSE;
	}
	//! 割り込み機能の初期処理.
	wi_InitInterrupt();

	//! タスク管理の初期処理.
	wi_InitTask();

	//! セマフォの初期処理.
	wi_InitSemaphore();

	//! イベントフラグの初期処理.
	wi_InitEvFlag();

	//! メールボックスの初期処理.
	wi_InitMailBox();

	//! メッセージ･バッファの初期処理.
	wi_InitMsgBuffer();

	//! 固定長メモリプールの初期処理.
	wi_InitFixedMemPool();

	//! 可変長メモリプールの初期処理.
	wi_InitVarMemPool();

	return TRUE;
}

/****************************************************************************/
/*!
 *	@brief	iTRONサービスコールの終了処理.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
static void		WinITRON_Quit(void)
{
	//! システム管理スレッドを終了させる.
	if (SystemThread) {
		//! - システム管理スレッドに終了を通知する.
		PostThreadMessage(ThreadId, WM_SYSTEM_EXIT, 0, 0);

		//! - スレッドが停止するのを確認する.
		wi_DormantThread(SystemThread, 1000);

		//! - システム管理スレッドのハンドルを解放する.
		CloseHandle(SystemThread);
	}
	//! システム状態管理機能の終了処理.
	wi_QuitSysMgr();

	//! 割り込み機能の終了処理.
	wi_QuitInterrupt();

	//! タスク管理の終了処理.
	wi_QuitTask();

	//! セマフォの終了処理.
	wi_QuitSemaphore();

	//! イベントフラグの終了処理.
	wi_QuitEvFlag();

	//! メールボックスの終了処理.
	wi_QuitMailBox();

	//! メッセージ･バッファの終了処理.
	wi_QuitMsgBuffer();

	//! 固定長メモリプールの終了処理.
	wi_QuitFixedMemPool();

	//! 可変長メモリプールの終了処理.
	wi_QuitVarMemPool();

	//! 共通関数の終了処理.
	wi_CommonQuit();
}

/****************************************************************************/
/*!
 *	@brief	ユーザー･アプリケーションの起動タスク.
 *
 *	@param	[in]	stacd	タスクの起動コード.
 *
 *	@retval	なし.
 */

static TASK	SimulatorTask(VP_INT stacd)
{
	//! ユーザー･アプリケーションの起動.
	SimulatorWindowDraw();
	exd_tsk();
}


/****************************************************************************/
/*!
 *	@brief	割り込みを発生させる.
 *
 *	@param	[in]	num		割り込みハンドラ番号.
 *
 *	@retval	なし.
 */
void	request_interrupt(UINT num)
{
	wi_IntrruptRequest(num);
}

/****************************************************************************/
/*!
 *	@brief	割り込み要求をクリアする.
 *
 *	@param	[in]	no		割り込みハンドラ番号.
 *
 *	@retval	なし.
 */
void	clear_interrupt_request(UINT num)
{
	wi_ClearIntrruptRequest(num);
}

/****************************************************************************/
/*!
 *	@brief	システム管理タスクにタスク･リソースの削除を要求する.
 *
 *	@param	[in]	id		タスクID識別子.
 *
 *	@retval	なし.
 */
void	wi_DeleteTaskReq(ID id)
{
	if (ThreadId) {
		PostThreadMessage(ThreadId, WM_DELETE_TASK, (WPARAM)id, 0);
	}
}

/****************************************************************************/
/*!
 *	@brief	システム管理タスク.
 *
 *	@param	[in]	arg		タスクリソース構造体のポインタ.
 *
 *	@retval	常に0を返す.
 */
static unsigned __stdcall SystemTask(void* arg)
{
	MSG	msg;

	//! スレッド識別子を取得する.
	ThreadId = GetCurrentThreadId();

	//! メッセージループ.
	while (GetMessage(&msg, NULL, 0, 0)) {

		//! システムの終了の場合はメッセージループを抜ける.
		if (msg.message == WM_SYSTEM_EXIT) {
			break;
		}
		switch (msg.message) {
		case WM_DELETE_TASK:
			del_tsk((ID)msg.wParam);
			break;
		}
	}
	_endthreadex(0);
	return 0;
}

/****************************************************************************/
extern void Ct_MainTask();
extern void Ct_DrawTask();
extern void Ct_DbgTask();
extern void CtCycHandler(VP_INT exinf);
extern void AvdfCycHandler(VP_INT exinf);
extern void GUI_TsTask();


#include "gdi_config.h"

BOOL ITRON_Init(void)
{
#ifdef __ITRON3__
	static const T_CTSK	ctsk = { NULL, TA_HLNG, InitTask, 1, 0 };
#else
	static const T_CTSK	ctsk = { TA_HLNG, NULL, SimulatorTask, 100, 0, NULL };
	static const T_CTSK ct_main_task = { TA_HLNG, 0, Ct_MainTask, 50, 0x4000, 0 };
	static const T_CTSK ct_draw_task = { TA_HLNG, 0, Ct_DrawTask, 40, 0x2000, 0 };
	static const T_CTSK ct_dbg_task = { TA_HLNG, 0, Ct_DbgTask, 60, 0x2000, 0 };
	static const T_CTSK gui_ts_task = { TA_HLNG, 0, GUI_TsTask, 99, 0x4000, 0 };

	static const T_CMPL ct_mpl = { TA_TFIFO, 0x80000*4, NULL };
	static const T_CMPL ct_fastmpl = { TA_TFIFO, 0x20000, NULL };
	static const T_CMPL gfxres_mpl = { TA_TFIFO, GFX_RES_SIZE, GUI_WORK_START };
	static const T_CMPL guiwork_mpl = { TA_TFIFO, GUI_WORK_SIZE, GFX_RES_START };
	static const T_CMPL gui_ts_mpl = { TA_TFIFO, 0x2000, NULL };

	static const T_CMBX ct_main_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	static const T_CMBX ct_draw_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };
	static const T_CMBX win_draw_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };				//WINDOWSアプリ側のウィンドウ描画更新用
	static const T_CMBX ct_dbg_mbx = { TA_TFIFO | TA_MFIFO, 0, 0 };

	static const T_CDTQ gui_ts_dtq = { TA_TFIFO, 10, NULL };

	static const T_CSEM ct_sem_receiver = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_object = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_synchro = { TA_TFIFO, 1, 1 };
	static const T_CSEM ct_sem_gdi 		= {TA_TFIFO, 1, 1};
	static const T_CSEM gdi_sem_fontapi = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_draw = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_create_cache = { TA_TFIFO, 1, 1 };
	static const T_CSEM gdi_sem_context = { TA_TFIFO, 1, 1 };

	static const T_CCYC ct_cyc = { TA_HLNG, 0, CtCycHandler,{ 0, 10 }, 0 };
	static const T_CCYC avdf_cyc = { TA_HLNG | TA_STA, 0, AvdfCycHandler, {0, 14}, 0 };	// 疑似AVDFタスク (本来は16.6ms周期だが16にすると動作周期が16,32とバラつくため14に設定)

	// Flag definition
	static const T_CFLG ct_flg_main = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG ct_flg_draw = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG ct_flg_synchro = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG ct_flg_dbg = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
	static const T_CFLG gui_ts_flgid = { TA_TFIFO | TA_WMUL | TA_CLR, 0 };
#endif

	//! iTRONサービスコールの初期処理.
	if (WinITRON_Init()) {
		//! アプリケーションの起動タスクを生成する.
		cre_tsk(TSKID_WINITRON, &ctsk);

		// メモリプール生成
		cre_mpl(CT_MPL_ID, &ct_mpl);
		cre_mpl(CT_FASTMPL_ID, &ct_fastmpl);
		cre_mpl(GFX_RESMPL_ID, &gfxres_mpl);
    cre_mpl(FONT_LIBMPL_ID, &gfxres_mpl);
		cre_mpl(GUI_WORKMPL_ID, &guiwork_mpl);
		cre_mpl(GUI_TS_MPLID, &gui_ts_mpl);

		// タスク生成
		cre_tsk(CT_MAIN_TSKID, &ct_main_task);
		cre_tsk(CT_DRAW_TSKID, &ct_draw_task);
		cre_tsk(CT_DBG_TSKID, &ct_dbg_task);
		cre_tsk(GUI_TS_TSKID, &gui_ts_task);

		// メールボックス生成
		cre_mbx(CT_MBXID_MAIN, &ct_main_mbx);
		cre_mbx(CT_MBXID_DRAW, &ct_draw_mbx);
		cre_mbx(MBXID_WIN_DRAW_TASK, &win_draw_mbx);
		cre_mbx(CT_MBXID_DBG, &ct_dbg_mbx);

		// データキュー生成
		cre_dtq(GUI_TS_DTQID, &gui_ts_dtq);

		// セマフォ 生成
		cre_sem(CT_SEMID_RECEIVER, &ct_sem_receiver);
		cre_sem(CT_SEMID_OBJECT, &ct_sem_object);
		cre_sem(CT_SEMID_SYNCHRO, &ct_sem_synchro);
		cre_sem(CT_SEMID_GDI, &ct_sem_gdi);
		cre_sem(GDI_SEMID_FONTAPI, &gdi_sem_fontapi);
		cre_sem(GDI_SEMID_DRAW, &gdi_sem_draw);
		cre_sem(GDI_SEMID_CREATE_CACHE, &gdi_sem_create_cache);
		cre_sem(GDI_SEMID_CONTEXT, &gdi_sem_context);

		// Flag definition
		cre_flg(CT_FLGID_MAINTASK, &ct_flg_main);
		cre_flg(CT_FLGID_DRAWTASK, &ct_flg_draw);
		cre_flg(CT_FLGID_SYNCHRO, &ct_flg_synchro);
		cre_flg(CT_FLGID_DBGTASK, &ct_flg_dbg);
		cre_flg(GUI_TS_FLGID, &gui_ts_flgid);

		// Cyclic Handler
		cre_cyc(CT_CYC_ID, &ct_cyc); // For AplTimerService
		cre_cyc(AVDF_CYC_ID, &avdf_cyc);

		return TRUE;
	}
	return FALSE;
}


void ITRON_START(void)
{
	//! 生成したタスクをを起動する.
	sta_tsk(TSKID_WINITRON, 0);
}

void ITRON_Quit(void)
{
	//TODO:タスクを閉じて回る際に落ちるので、終了処理を呼べない。各タスクに終了通知して回る必要がある
	WinITRON_Quit();
}

/* 非タスク処理からのiset_flg呼び出し用 */
void ITRON_iset_flg(int flagid, UINT setptn)
{
	iset_flg(flagid, setptn);
}
/* End of file */
