/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	メインタスクのエントリ関数
*/
#ifndef _CtMainThread_h_
#define _CtMainThread_h_

#include "Ct.h"
#include "CtObject.h"

#include <CtPlatforms.h>

class CtMainThread
{	
public:
	static CtMainThread* getInstance();
	virtual ~CtMainThread();
	
	static void startThread();
	static void termThread();
	static bool isOwnThread();
	

private:
	CtMainThread();
	static void ThreadMain();
	static void CyclicMain();

	static CtMainThread*	m_pInstance;
	static syswrap_thread_t	m_Thread;
	static syswrap_cyclic_handler_t m_Cyclic;
	
};
	
#endif
