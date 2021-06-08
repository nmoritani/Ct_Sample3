/**
 *	Copyright(c) 2018 Persol AVC Technology.
 *	$Id$
 *
 *	@file
 *	@brief	メインタスクのエントリ関数
*/

#include "CtMsgDbgTask.h"
#include "CtTimer.h"
#include "CtDbgCmndReceiver.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

	void Ct_DbgTask()
	{
		CtDebugPrint(CtDbg, "★★★★ ActDbgTsk ★★★★\n");
		CtDbgCmndReceiver* pCmndRcvr = CtDbgCmndReceiver::getInstance();
		CtTimer *pTimer = CtTimer::getInstance();

		FLGPTN flgptn;
		ER err;

		/* イベント処理ループ */
		while (1) {
			CtMsg* pMsg = NULL;
			flgptn = 0;
			err = wai_flg(CT_FLGID_DBGTASK, (CtMsgDbgTask::FLGPTN_ALL), TWF_ORW, &flgptn);

#ifdef WIN32_GUI_SIM
			if (0 != (flgptn & CtMsgDbgTask::FLGPTN_DBG_STOP)) {
				break;
			}
#endif
			if (flgptn & CtMsgDbgTask::FLGPTN_DBG_MSG) {
				// メールボックスからMsgを取得する。
				bool ret;
				do {
					ret = CtMsgDbgTask::receiveMsg(pMsg);	/* pgr0522	*/
					if (pMsg != NULL) {
						pCmndRcvr->receiveMsg(*pMsg);
						
						// Receiver側で削除
						//if(pMsg != NULL) delete pMsg;
					}
				} while (!ret);
			}
			if (flgptn & CtMsgDbgTask::FLGPTN_DBG_TIMER) {
				pTimer->receiveFlg(CtMsgDbgTask::FLGPTN_DBG_TIMER);
			}
		}
		if (pCmndRcvr != NULL) {
			delete pCmndRcvr;
			pCmndRcvr = NULL;
		}
		return;
	}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

