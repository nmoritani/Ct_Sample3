/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	Drawタスク
*/

#include "CtDrawThread.h"

CtDrawThread* 			CtDrawThread::m_pInstance = NULL;
CtDraw* 				CtDrawThread::m_pDraw = NULL;
CtWindowController* 	CtDrawThread::m_pWinCtrl = NULL;

syswrap_thread_t		CtDrawThread::m_Thread = {0};
syswrap_cyclic_handler_t CtDrawThread::m_Cyclic = {0};

CtDrawThread::CtDrawThread()
{
	CtComDrawThread::init();

	syswrap_create_thread(&m_Thread, ThreadMain, 0x2000, THREAD_PRI_NORMAL);
	syswrap_create_cyclic_handler(&m_Cyclic, CyclicDraw, 14);
}

CtDrawThread::~CtDrawThread()
{
	if (m_pWinCtrl != NULL)
		delete m_pWinCtrl;

	if (m_pDraw != NULL)
		delete m_pDraw;
	
	syswrap_destroy_thread(&m_Thread);
	m_Thread = {0};
	CtComDrawThread::term();
}

CtDrawThread* CtDrawThread::getInstance()
{
	if (!m_pInstance) {
		m_pInstance = new CtDrawThread();
	}
	return m_pInstance;
}

void CtDrawThread::ThreadMain()
{
	unsigned int flgptn;
	unsigned long frame_count = 0;

	m_pDraw = CtDraw::getInstance();
	m_pWinCtrl = CtWindowController::getInstance();
	
	syswrap_start_cyclic_handler(&m_Cyclic);
	
    /* イベント処理ループ */
	while (1) {
		flgptn = 0;
		CtComDrawThread::waitEvent(CtComDrawThread::FLGPTN_ALL, SYSWRAP_WAITFMODE_ORW, &flgptn, SYSWRAP_TIMEOUT_FOREVER);

		if (flgptn & CtComDrawThread::FLGPTN_DRAW_STOP) {
			if (m_pDraw != NULL) {
				delete m_pDraw;
				m_pDraw = NULL;
			}
			break;
		}
		else if (flgptn & CtComDrawThread::FLGPTN_TIMER_DRAW) {
			frame_count++;
			m_pWinCtrl->handleFrameSync(frame_count);
		}
    }
}

void CtDrawThread::startThread()
{
	syswrap_start_thread(&m_Thread);
}

void CtDrawThread::termThread()
{
	syswrap_term_thread(&m_Thread);
}

void CtDrawThread::CyclicDraw()
{
	CtComDrawThread::setEvent(CtComDrawThread::FLGPTN_TIMER_DRAW);
}

bool CtDrawThread::isOwnThread()
{
	int id;

	if ((id = syswrap_get_threadid(NULL)) == 0)
		return false;

	if (id == syswrap_get_threadid(&m_Thread))
		return true;

	return false;
}
