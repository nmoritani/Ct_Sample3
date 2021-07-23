/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtComDrawThread
 */


#ifndef __CtComDrawThread_H__
#define __CtComDrawThread_H__

#include <CtPlatforms.h>

class CtMsg;

class CtComDrawThread
{
public :
	static void init();
	static void term();
	
    static void receiveMsg(CtMsg*& pMsg);
    static void sendMsg(CtMsg& Msg);
    
	static const unsigned int FLGPTN_TIMER_DRAW = 0x00000200;
	static const unsigned int FLGPTN_DRAW_STOP = 0x00000400;
	static const unsigned int FLGPTN_ALL = FLGPTN_TIMER_DRAW| FLGPTN_DRAW_STOP;

	static void waitEvent(unsigned int WaitPattern, unsigned int WaitMode, unsigned int *EventPattern, long Timeout);
	static void setEvent(unsigned int WaitPattern);
	
private :
    inline CtComDrawThread() {
    }
    
    inline ~CtComDrawThread() {
    }
	
	static syswrap_mailbox_t	m_Mailbox;
	static syswrap_event_t		m_Event;
};

#endif
