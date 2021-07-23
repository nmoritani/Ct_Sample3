/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtComDrawThread
 */

#include "CtMsg.h"
#include "CtAssert.h"
#include "CtComDrawThread.h"

syswrap_mailbox_t CtComDrawThread::m_Mailbox = {0};
syswrap_event_t CtComDrawThread::m_Event = {0};

void CtComDrawThread::init()
{
	m_Mailbox.id = CT_MBXID_DRAW;
	syswrap_create_mailbox(&m_Mailbox, THREAD_ATTR_FIFO);
	
	m_Event.id = CT_FLGID_DRAW;
	syswrap_create_event(&m_Event, THREAD_ATTR_FIFO, 0);
}

void CtComDrawThread::term()
{
	syswrap_destroy_event(&m_Event);
	syswrap_destroy_mailbox(&m_Mailbox);
	
	m_Mailbox = {0};
	m_Event = {0};
}

void CtComDrawThread::receiveMsg(CtMsg*& pMsg)
{
    SYSWRAP_ERROR Err;
    //メール受け取り
    Err = syswrap_receive_message(&m_Mailbox, (void **)&pMsg, SYSWRAP_TIMEOUT_FOREVER);
    CtAssert(SYSWRAP_ERR_OK == Err);

	if (SYSWRAP_ERR_RLWAI == Err) {
		//タスクの終了通知で強制的に抜けた場合
		pMsg = NULL;
		return;
	}
	
    return;
}

void CtComDrawThread::sendMsg(CtMsg& Msg)
{
    // リクエストメール送信
    SYSWRAP_ERROR err;
    err = syswrap_send_message(&m_Mailbox, (void *)&Msg, Msg.getPriority());
    CtAssert(SYSWRAP_ERR_OK == err);

    return;
}

void CtComDrawThread::waitEvent(unsigned int WaitPattern, unsigned int WaitMode, unsigned int *EventPattern, long Timeout)
{
	syswrap_wait_event(&m_Event, WaitPattern, WaitMode, EventPattern, Timeout);
}

void CtComDrawThread::setEvent(unsigned int WaitPattern)
{
	syswrap_set_event(&m_Event, WaitPattern);
}

