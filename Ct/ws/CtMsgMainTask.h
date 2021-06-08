/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtComMainTask
 */


#ifndef __CtMsgMainTask_H__
#define __CtMsgMainTask_H__

#include "kernel.h"
#include "kernel_id.h"
class CtMsg;

class CtMsgMainTask {
    ////    Constructors and destructors    ////
    
private :
    inline CtMsgMainTask() {
    }
    
    inline ~CtMsgMainTask() {
    }
    
    ////    Operations    ////
public :
    static bool receiveMsg(CtMsg*& pMsg);
	
    static void sendMsg(CtMsg& Msg);
    
    ////    Attributes    ////
	static const FLGPTN FLGPTN_MAIN_TIMER = 0x00000100;
	static const FLGPTN FLGPTN_MAIN_MSG   = 0x00000200;
	static const FLGPTN FLGPTN_MAIN_STOP  = 0x00000800;
	static const FLGPTN FLGPTN_ALL        = (FLGPTN_MAIN_TIMER|FLGPTN_MAIN_MSG|FLGPTN_MAIN_STOP);

};

#endif
