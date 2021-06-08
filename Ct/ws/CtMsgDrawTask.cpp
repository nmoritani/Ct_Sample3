/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtMsgDrawTask
 */


#include "CtMsgDrawTask.h"
#include "CtMsg.h"
#include "CtAssert.h"

void CtMsgDrawTask::receiveMsg(CtMsg*& pMsg)
{
    ER Err;
    //メール受け取り
    CtMsg::CtMsgHeader* pMsgHeader;
    Err = rcv_mbx(CT_MBXID_DRAW, (T_MSG**)&pMsgHeader);
    CtAssert(E_OK == Err);

	if (E_RLWAI == Err) {
		//タスクの終了通知で強制的に抜けた場合
		pMsg = NULL;
		return;
	}

    // 受信したメッセージ構造体より、CtMesssageクラスのポインタを取得する。
    pMsg = (CtMsg*)(pMsgHeader->pMsg);
    
    return;
}

void CtMsgDrawTask::sendMsg(CtMsg& Msg)
{
    // リクエストメール送信
    ER err;
    const CtMsg::CtMsgHeader* pHeader = Msg.getMsgHeader();  
    err = snd_mbx(CT_MBXID_DRAW, (T_MSG*)&(pHeader->Header));
    CtAssert(E_OK == err);

    return;
}
