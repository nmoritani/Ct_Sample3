/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	メインタスクのエントリ関数
*/
#ifndef _CtDbgThread_h_
#define _CtDbgThread_h_

#include "Ct.h"
#include "CtObject.h"

#include <CtPlatforms.h>

class CtDbgThread
{	
public:
	static CtDbgThread* getInstance();
	~CtDbgThread();
	
	 void startThread();
	 void termThread();

private:
	CtDbgThread();
	static void ThreadMain();

	static CtDbgThread*		m_pInstance;
	static syswrap_thread_t	m_Thread;
	
};
	
#endif
