/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	Drawタスク
*/

#include "CtDrawTask.h"
#include "CtWindowController.h"
#include "CtDraw.h"
#include "AvcIf.h"

#ifdef WIN32_GUI_SIM
typedef enum {
	GUIAVC_DISP_LCD = 0,
	GUIAVC_DISP_LOUT,
	GUIAVC_DISP_REC,
	GUIAVC_DISP_MAX
} GUIAVC_DISP_ID;

BOOL GUIAVC_isUpdateEnable(GUIAVC_DISP_ID disp_id)
{
	return TRUE;
}
#else
#include "gui_main.h"
#endif

#ifdef WIN32_GUI_SIM
#define GUITASK_WAIT (3000)
#else
#define GUITASK_WAIT (500)
#endif

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* Drawタスクのエントリ関数 */
void Ct_DrawTask()
{
	//	dly_tsk(GUITASK_WAIT);
	CtDrawTask::getInstance()->loop();
	return;
}

/* V周期コールバック */
AVC_ER Ct_AvdfCallback(VP vp)
{
	CtDrawTask::getInstance()->wake();
	return AVC_ER_CALL_NEXT_FIELD;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */


CtDrawTask* CtDrawTask::m_pInstance = NULL;

CtDrawTask::CtDrawTask()
{
	m_pDraw = CtDraw::getInstance();
	m_pWinCtrl = CtWindowController::getInstance();
	
	AVDF_AddCallback(Ct_AvdfCallback, NULL, true);
}

CtDrawTask::~CtDrawTask()
{
}

CtDrawTask* CtDrawTask::getInstance()
{
	if (!m_pInstance) {
		m_pInstance = new CtDrawTask();
	}
	return m_pInstance;
}

/* ハングアップ検出定義 */
#define CT_DRAW_TASK_TIMEOUT 		(1000*5)
#define CT_DRAW_TASK_HANGUP_CHECK_NAME		"CT_DRAW"

void CtDrawTask::loop()
{
	FLGPTN flgptn;
	unsigned long frame_count = 0;

#ifndef WIN32_GUI_SIM
	ID	HangTaskId = SYS_HangDet_Open ((const char*)CT_DRAW_TASK_HANGUP_CHECK_NAME, CT_DRAW_TASK_TIMEOUT);		//ハング検出設定しIDを取得
	if(HangTaskId >= 0){
		SYS_HangDet_Start(HangTaskId);	//ハング検出開始
	}
#endif

    /* イベント処理ループ */
	while (1) {
		// 起床待ち
		wait(flgptn);

		if (flgptn & CtMsgDrawTask::FLGPTN_DRAW_STOP) {
			if (m_pDraw != NULL) {
				delete m_pDraw;
			}
			break;
		}
		else if (flgptn & CtMsgDrawTask::FLGPTN_TIMER_DRAW) {
			frame_count++;
			m_pWinCtrl->handleFrameSync(frame_count);
#ifndef WIN32_GUI_SIM
			SYS_HangDet_Alive (HangTaskId);	//SYSに生存通知
#endif
		}
    }
}

void CtDrawTask::wait(FLGPTN &flg)
{
	flg = 0;
	wai_flg(CT_FLGID_DRAWTASK, CtMsgDrawTask::FLGPTN_ALL, TWF_ORW, &flg);
}

#include "../../TimeStamp/gui_timestamp_api.h"
// Drawタスク起床
void CtDrawTask::wake()
{
	set_flg(CT_FLGID_DRAWTASK, CtMsgDrawTask::FLGPTN_TIMER_DRAW);
	GUI_TsWakeup();
}


