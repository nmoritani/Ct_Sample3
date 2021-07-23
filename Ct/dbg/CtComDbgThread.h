/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtComDbgThread
 */

#ifndef __CtComDbgThread_H__
#define __CtComDbgThread_H__

#include <CtPlatforms.h>

class CtMsg;

class CtComDbgThread
{
public:
	static void init();
	static void term();
	
	static bool receiveMsg(CtMsg*& pMsg);
	static bool sendMsg(CtMsg& Msg);

	static const unsigned int FLGPTN_DBG_TIMER	= 0x00000001;
	static const unsigned int FLGPTN_DBG_MSG		= 0x00000002;
	static const unsigned int FLGPTN_DBG_STOP		= 0x00000004;
	static const unsigned int FLGPTN_ALL = (FLGPTN_DBG_TIMER | FLGPTN_DBG_MSG | FLGPTN_DBG_STOP );

	static void waitEvent(unsigned int WaitPattern, unsigned int WaitMode, unsigned int *EventPattern, long Timeout);
	static void setEvent(unsigned int WaitPattern);
	
private:
	inline CtComDbgThread() {
	}

	inline ~CtComDbgThread() {
	}
	
	static syswrap_mailbox_t	m_Mailbox;
	static syswrap_event_t		m_Event;
};
#endif
