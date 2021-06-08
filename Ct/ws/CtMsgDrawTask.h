/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtMsgDrawTask
 */


#ifndef __CtMsgDrawTask_H__
#define __CtMsgDrawTask_H__

#include "kernel.h"
#include "kernel_id.h"
class CtMsg;

class CtMsgDrawTask {
    ////    Constructors and destructors    ////
    
private :
    inline CtMsgDrawTask() {
    }
    
    inline ~CtMsgDrawTask() {
    }
    
    ////    Operations    ////
public :
    static void receiveMsg(CtMsg*& pMsg);
	
    static void sendMsg(CtMsg& Msg);
    
    ////    Attributes    ////
	static const FLGPTN FLGPTN_TIMER_DRAW = 0x00000200;
	static const FLGPTN FLGPTN_DRAW_STOP = 0x00000400;
	static const FLGPTN FLGPTN_ALL = FLGPTN_TIMER_DRAW| FLGPTN_DRAW_STOP;
};

#endif
