/**
 *	Copyright(c) 2018 Persol AVC Technology.
 *	$Id$
 *
 *	@file
 *	@brief	メインタスクのエントリ関数
*/

#include "CtDbgThread.h"

#include "CtComDbgThread.h"
#include "CtDbgCmndReceiver.h"
#include "CtTimer.h"

CtDbgThread* CtDbgThread::m_pInstance = NULL;
syswrap_thread_t CtDbgThread::m_Thread = {0};

CtDbgThread::CtDbgThread()
{
	m_Thread.id = CT_TASKID_DBG;
	syswrap_create_thread(&m_Thread, ThreadMain, 0x2000, THREAD_PRI_NORMAL_LOW);
	CtComDbgThread::init();
}

CtDbgThread::~CtDbgThread()
{
	CtComDbgThread::term();
	syswrap_term_thread(&m_Thread);
	syswrap_destroy_thread(&m_Thread);
}

CtDbgThread* CtDbgThread::getInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new CtDbgThread();

	return m_pInstance;
}

void CtDbgThread::ThreadMain()
{
	CtDebugPrint(CtDbg, "★★★★ ActDbgThread ★★★★\n");
	CtDbgCmndReceiver* pCmndRcvr = CtDbgCmndReceiver::getInstance();
	CtTimer *pTimer = CtTimer::getInstance();
	
	unsigned int flgptn;
	
	/* イベント処理ループ */
	while (1) {
		CtMsg* pMsg = NULL;
		flgptn = 0;
		CtComDbgThread::waitEvent((CtComDbgThread::FLGPTN_ALL), SYSWRAP_WAITFMODE_ORW, &flgptn, SYSWRAP_TIMEOUT_FOREVER);
		
#ifdef WIN32_GUI_SIM
		if (0 != (flgptn & CtComDbgThread::FLGPTN_DBG_STOP)) {
			break;
		}
#endif
		if (flgptn & CtComDbgThread::FLGPTN_DBG_MSG) {
			// メールボックスからMsgを取得する。
			bool ret;
			do {
				ret = CtComDbgThread::receiveMsg(pMsg);	/* pgr0522	*/
				if (pMsg != NULL) {
					pCmndRcvr->receiveMsg(*pMsg);
					
					// Receiver側で削除
					// if(pMsg != NULL) delete pMsg;
				}
			} while (!ret);
		}
		if (flgptn & CtComDbgThread::FLGPTN_DBG_TIMER) {
			pTimer->receiveFlg(CtComDbgThread::FLGPTN_DBG_TIMER);
		}
	}
	if (pCmndRcvr != NULL) {
		delete pCmndRcvr;
		pCmndRcvr = NULL;
	}
	return;
}

void CtDbgThread::startThread()
{
	syswrap_start_thread(&m_Thread);
}

void CtDbgThread::termThread()
{
	syswrap_term_thread(&m_Thread);
}
