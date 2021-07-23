/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	Drawタスククラス
*/

#ifndef _CtDrawThread_h_
#define _CtDrawThread_h_

#include "Ct.h"
#include "CtComDrawThread.h"
#include "CtMsg.h"
#include "CtDraw.h"
#include "CtWindowController.h"

#include <CtPlatforms.h>

class CtDrawThread
{
public:
	static CtDrawThread* getInstance();
	virtual ~CtDrawThread();

	static void startThread();
	static void termThread();
	static bool isOwnThread();
	
private:
	CtDrawThread();
	static void ThreadMain();
	static void CyclicDraw();
	
	static CtDraw* 				m_pDraw;
	static CtWindowController* 	m_pWinCtrl;

	static CtDrawThread* 		m_pInstance;
	static syswrap_thread_t		m_Thread;
	static syswrap_cyclic_handler_t m_Cyclic;
};

#endif

