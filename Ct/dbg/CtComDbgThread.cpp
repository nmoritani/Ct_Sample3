/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtComDbgThread
 */
#include <stdlib.h>
#include <CtPlatforms.h>

#include "CtComDbgThread.h"
#include "CtMsg.h"
#include "CtMsgDbgCmnd.h"

syswrap_mailbox_t CtComDbgThread::m_Mailbox = {0};
syswrap_event_t CtComDbgThread::m_Event = {0};

void CtComDbgThread::init()
{
	syswrap_create_mailbox(&m_Mailbox, THREAD_ATTR_FIFO);
	syswrap_create_event(&m_Event, THREAD_ATTR_FIFO, 0);
}

void CtComDbgThread::term()
{
	syswrap_destroy_event(&m_Event);
	syswrap_destroy_mailbox(&m_Mailbox);
	
	m_Mailbox = {0};
	m_Event = {0};
}

bool CtComDbgThread::receiveMsg(CtMsg*& pMsg)
{
	
	SYSWRAP_ERROR result = syswrap_receive_message(&m_Mailbox, (void **)&pMsg, SYSWRAP_TIMEOUT_FOREVER);
	switch (result) {
	case SYSWRAP_ERR_RLWAI:
		//タスクの終了通知で強制的に抜けた場合
		pMsg = NULL;
		return true;
	case SYSWRAP_ERR_TIMEOUT:
		return true;
	default:
		break;
	}
	// メールボックス内にまだメールがあるか確認
	if (syswrap_get_remain_message(&m_Mailbox) >= 1)
		return false;
	
	return true;
}

bool CtComDbgThread::sendMsg(CtMsg& Msg)
{
	bool bRet = false;

	if (syswrap_send_message(&m_Mailbox, (void *)&Msg, Msg.getPriority()) == SYSWRAP_ERR_OK)  {
		bRet = true;
	}
	setEvent(CtComDbgThread::FLGPTN_DBG_MSG);
	
	return bRet;
}

void CtComDbgThread::waitEvent(unsigned int WaitPattern, unsigned int WaitMode, unsigned int *EventPattern, long Timeout)
{
	syswrap_wait_event(&m_Event, WaitPattern, WaitMode, EventPattern, Timeout);
}

void CtComDbgThread::setEvent(unsigned int WaitPattern)
{
	syswrap_set_event(&m_Event, WaitPattern);
}

