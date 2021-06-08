/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   Window への描画用タスク (シミュレーター用)
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "SysIf.h"
#include "WinDrawTask.h"
#include "gdi.h"
#include "gdi_draw_test.h"

#include "CtMsgMainTask.h"
#include "CtMsgDrawTask.h"
#include "CtMsgDbgTask.h"

#define MSGBOX_MAX_DATA_LENGTH	10

typedef struct {
	T_MSG	hdr;
	USHORT msgtype;
	USHORT data_length;
	USHORT data[MSGBOX_MAX_DATA_LENGTH];
} WIN_DRAW_TASK_MSG;

static CALLBACK_WIN_DRAWTASK s_callbackfunc;

/****************************************************************************/
void WinDrawTask_Init(CALLBACK_WIN_DRAWTASK callbackfunc)
{
	s_callbackfunc = callbackfunc;
}

/****************************************************************************/

static void wait_task_terminate(ID id)
{
	T_RTSK rtsk;
	ER err;
	do {
		rtsk.tskstat = 0;
		err = ref_tsk(id, &rtsk);
		if ((E_OK == err) && (rtsk.tskstat & TTS_DMT)) {
			return;
		}
	} while (1);
}

void Simulator_terminate()
{
	//まとめて止めに行くと順番問題で落ちそうだから1つずつ確実に停止させていく。。。

	//周期ハンドラ停止
	stp_cyc(CT_CYC_ID);
	stp_cyc(AVDF_CYC_ID);

	//CtDrawTask停止
	set_flg(CT_FLGID_DRAWTASK, CtMsgDrawTask::FLGPTN_DRAW_STOP);	//終了通知セット
	//ter_tsk(CT_FLGID_DRAWTASK);
	rel_wai(CT_DRAW_TSKID);		//タスクの待ちを強制解除
	wait_task_terminate(CT_DRAW_TSKID);								//終了待ち

	//CtMainTask停止
	set_flg(CT_FLGID_MAINTASK, CtMsgMainTask::FLGPTN_MAIN_STOP);	//終了通知セット
	rel_wai(CT_MAIN_TSKID);											//タスクの待ちを強制解除
	wait_task_terminate(CT_MAIN_TSKID);								//終了待ち

	//CtDbgTask停止
	set_flg(CT_FLGID_DBGTASK, CtMsgDbgTask::FLGPTN_DBG_STOP);		//終了通知セット
	rel_wai(CT_DBG_TSKID);											//タスクの待ちを強制解除
	wait_task_terminate(CT_DBG_TSKID);								//終了待ち

	//各メッセージの削除
	del_mbx(CT_MBXID_DRAW);
	del_mbx(CT_MBXID_MAIN);
	del_mbx(MBXID_WIN_DRAW_TASK);
	del_mbx(CT_MBXID_DBG);

	// セマフォ削除
	del_sem(CT_SEMID_RECEIVER);
	del_sem(CT_SEMID_OBJECT);
	del_sem(CT_SEMID_SYNCHRO);
	del_sem(CT_SEMID_GDI);
	del_sem(GDI_SEMID_FONTAPI);
	del_sem(GDI_SEMID_DRAW);
	del_sem(GDI_SEMID_CREATE_CACHE);
	del_sem(GDI_SEMID_CONTEXT);

	//フラグの削除
	del_flg(CT_FLGID_MAINTASK);
	del_flg(CT_FLGID_DRAWTASK);
	del_flg(CT_FLGID_DBGTASK);

	//周期ハンドラの削除
	del_cyc(CT_CYC_ID);
	del_cyc(AVDF_CYC_ID);

	//各タスクの削除
	del_tsk(CT_DRAW_TSKID);
	del_tsk(CT_MAIN_TSKID);
	del_tsk(CT_DBG_TSKID);

	// メモリプール削除
	del_mpl(GFX_RESMPL_ID);
  del_mpl(FONT_LIBMPL_ID);
	del_mpl(GUI_WORKMPL_ID);
	del_mpl(CT_MPL_ID);

}

/****************************************************************************/
/*!
 *	@brief	シミュレータ描画用
 */
void SimulatorWindowDraw(void)
{
#if 1
	ER result;
	T_MSG *pMsg;
	BOOL bIsDrawEnable = TRUE;

	while (1) {
		result = trcv_msg(MBXID_WIN_DRAW_TASK, &pMsg, 5);
		if ((E_ID == result)
			|| (E_NOEXS == result)
			|| (E_PAR == result)
			|| (E_CTX == result)) {
			//エラー処理
			break;
		}

		if (E_TMOUT != result) {
			WIN_DRAW_TASK_MSG* pDrawTaskMsg = (WIN_DRAW_TASK_MSG*)pMsg;
			USHORT msgtype = pDrawTaskMsg->msgtype;
			USHORT data_length = pDrawTaskMsg->data_length;
			USHORT *rcvData = pDrawTaskMsg->data;

			switch (msgtype) {
			case MBX_DRAWTEST_TYPE_STOP:
				//終了処理
				Simulator_terminate();
				bIsDrawEnable = FALSE;
				s_callbackfunc();
				return;
			}
		}
	};
#endif
}

static WIN_DRAW_TASK_MSG msg;
BOOL WinDrawTask_sendMsg(int mbxid, USHORT msgtype, int length, USHORT *data)
{
	ER result;
	int i;
	if (MSGBOX_MAX_DATA_LENGTH < length) {
		return FALSE;
	}

	msg.hdr.msgpri = 1;
	msg.msgtype = msgtype;
	msg.data_length = length;

	for (i = 0; i < length; i++) {
		msg.data[i] = data[i];
	}

	result = snd_msg(mbxid, (T_MSG *)&msg);
	return (result == E_OK);
}

