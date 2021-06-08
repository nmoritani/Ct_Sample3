/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtMsgDbgTask
 */


#ifndef __CtMsgDbgTask_H__
#define __CtMsgDbgTask_H__

#include "kernel.h"
#include "kernel_id.h"

class CtMsg;

class CtMsgDbgTask {
	////    Constructors and destructors    ////
public:

private:
	inline CtMsgDbgTask() {
	}

	inline ~CtMsgDbgTask() {
	}

	////    Operations    ////
public:
	static bool receiveMsg(CtMsg*& pMsg);

	static ER CtMsgDbgTask::sendMsg(CtMsg& Msg);
	////    Attributes    ////
	static const FLGPTN FLGPTN_DBG_TIMER	= 0x00000001;
	static const FLGPTN FLGPTN_DBG_MSG		= 0x00000002;
	static const FLGPTN FLGPTN_DBG_STOP		= 0x00000004;
	static const FLGPTN FLGPTN_ALL = (FLGPTN_DBG_TIMER | FLGPTN_DBG_MSG | FLGPTN_DBG_STOP );

};
#endif
