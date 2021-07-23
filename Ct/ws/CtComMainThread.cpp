/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtComMainThread
 */

#include "CtMsg.h"
#include "CtAssert.h"
#include "CtComMainThread.h"

syswrap_mailbox_t CtComMainThread::m_Mailbox = {0};
syswrap_event_t CtComMainThread::m_Event = {0};

void CtComMainThread::init()
{
	m_Mailbox.id = CT_MBXID_MAIN;
	syswrap_create_mailbox(&m_Mailbox, THREAD_ATTR_FIFO);

	m_Event.id = CT_FLGID_MAIN;
	syswrap_create_event(&m_Event, THREAD_ATTR_FIFO, 0);
}

void CtComMainThread::term()
{
	syswrap_destroy_event(&m_Event);
	syswrap_destroy_mailbox(&m_Mailbox);
	
	m_Mailbox = {0};
	m_Event = {0};
}

bool CtComMainThread::receiveMsg(CtMsg*& pMsg)
{
    SYSWRAP_ERROR Err;
	
    Err = syswrap_receive_message(&m_Mailbox, (void **)&pMsg, SYSWRAP_TIMEOUT_POLLING);
	switch (Err) {
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

void CtComMainThread::sendMsg(CtMsg& Msg)
{
    // リクエストメール送信
    SYSWRAP_ERROR err;
    err = syswrap_send_message(&m_Mailbox, (void *)&Msg, Msg.getPriority());
    CtAssert(SYSWRAP_ERR_OK == err);
	
	setEvent(FLGPTN_MAIN_MSG);
    return;
}

void CtComMainThread::waitEvent(unsigned int WaitPattern, unsigned int WaitMode, unsigned int *EventPattern, long Timeout)
{
	syswrap_wait_event(&m_Event, WaitPattern, WaitMode, EventPattern, Timeout);
}

void CtComMainThread::setEvent(unsigned int WaitPattern)
{
	syswrap_set_event(&m_Event, WaitPattern);
}

