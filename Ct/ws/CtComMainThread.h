/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtComMainThread
 */


#ifndef __CtComMainThread_H__
#define __CtComMainThread_H__

#include <CtPlatforms.h>

class CtMsg;

class CtComMainThread
{
public :
	static void init();
	static void term();
	
    static bool receiveMsg(CtMsg*& pMsg);
    static void sendMsg(CtMsg& Msg);

	static const unsigned int FLGPTN_MAIN_TIMER = 0x00000100;
	static const unsigned int FLGPTN_MAIN_MSG   = 0x00000200;
	static const unsigned int FLGPTN_MAIN_STOP  = 0x00000800;
	static const unsigned int FLGPTN_ALL        = (FLGPTN_MAIN_TIMER|FLGPTN_MAIN_MSG|FLGPTN_MAIN_STOP);
	
	static void waitEvent(unsigned int WaitPattern, unsigned int WaitMode, unsigned int *EventPattern, long Timeout);
	static void setEvent(unsigned int WaitPattern);

private :
    inline CtComMainThread() {
    }
    
    inline ~CtComMainThread() {
    }
	
	static syswrap_mailbox_t	m_Mailbox;
	static syswrap_event_t		m_Event;
};

#endif
