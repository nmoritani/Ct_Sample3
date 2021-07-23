/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	メインタスクのエントリ関数
*/

#include "CtComMainThread.h"
#include "CtMsg.h"
#include "CtTimer.h"
#include "CtMainThread.h"
#include "CtDrawThread.h"

CtMainThread* CtMainThread::m_pInstance = NULL;
syswrap_thread_t CtMainThread::m_Thread = {0};
syswrap_cyclic_handler_t CtMainThread::m_Cyclic = {0};

CtMainThread::CtMainThread()
{
	CtComMainThread::init();

	syswrap_create_thread(&m_Thread, ThreadMain, 0x4000, THREAD_PRI_NORMAL_LOW);
	syswrap_create_cyclic_handler(&m_Cyclic, CyclicMain, 10);
}

CtMainThread::~CtMainThread()
{
	termThread();

	syswrap_destroy_cyclic_handler(&m_Cyclic);
	m_Cyclic = {0};
	
	syswrap_destroy_thread(&m_Thread);
	m_Thread = {0};
	
	CtComMainThread::term();
}

CtMainThread* CtMainThread::getInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new CtMainThread();

	return m_pInstance;
}


void CtMainThread::ThreadMain()
{
	CtDebugPrint(CtDbg, "------------------------------------Ct_MainTask\n");
	unsigned int flgptn;

	CtDrawThread::startThread();

	syswrap_start_cyclic_handler(&m_Cyclic);
	
    /* イベント処理ループ */
	while (1) {
		CtMsg* pMsg = NULL;
		flgptn = 0;

		CtComMainThread::waitEvent((CtComMainThread::FLGPTN_ALL), SYSWRAP_WAITFMODE_ORW, &flgptn, SYSWRAP_TIMEOUT_FOREVER);
#ifdef WIN32_GUI_SIM
		if (0 != (flgptn & CtComMainThread::FLGPTN_MAIN_STOP)) {
			break;
		}
#endif
		if (flgptn & CtComMainThread::FLGPTN_MAIN_MSG) {
			// メールボックスからMsgを取得する。
			bool ret;
			do {
				ret = CtComMainThread::receiveMsg(pMsg);	/* pgr0522	*/
				if (pMsg != NULL) {
					// Cmd実行
					static_cast<CtEvent*>(pMsg)->operationCmd();
					delete pMsg;
				}
			} while (!ret);
			
		}
		
		if (flgptn & CtComMainThread::FLGPTN_MAIN_TIMER) {
			CtTimer::getInstance()->receiveFlg(CtComMainThread::FLGPTN_MAIN_TIMER);
		}
    }

	return;
}

void CtMainThread::startThread()
{
	syswrap_start_thread(&m_Thread);
}

void CtMainThread::termThread()
{
	syswrap_term_thread(&m_Thread);
}

void CtMainThread::CyclicMain()
{
	CtTimer::CycHandler();
}

bool CtMainThread::isOwnThread()
{
	int id;

	if ((id = syswrap_get_threadid(NULL)) == 0)
		return false;

	if (id == syswrap_get_threadid(&m_Thread))
		return true;

	return false;
}

