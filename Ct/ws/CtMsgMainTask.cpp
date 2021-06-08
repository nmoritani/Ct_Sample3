/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version: 7.5.1
 *  Element:          CtComMainTask
 */


#include "CtMsgMainTask.h"
#include "CtMsg.h"
#include "CtAssert.h"

bool CtMsgMainTask::receiveMsg(CtMsg*& pMsg)
{
    ER Err;
    CtMsg::CtMsgHeader* pMsgHeader;
	
    Err = prcv_mbx(CT_MBXID_MAIN, (T_MSG**)&pMsgHeader);
	switch (Err) {
	case E_RLWAI:
		//タスクの終了通知で強制的に抜けた場合
		pMsg = NULL;
		return true;
	case E_TMOUT:
		return true;
	default:
		break;
	}
	
    // 受信したメッセージ構造体より、CtMesssageクラスのポインタを取得する。
    pMsg = (CtMsg*)(pMsgHeader->pMsg);
	
    // メールボックス内にまだメールがあるか確認
    T_RMBX Rmbx;
    Err= ref_mbx(CT_MBXID_MAIN, &Rmbx);
    CtAssert(E_OK == Err);
	
    if (NULL != Rmbx.pk_msg) {
		return false;
	}
    
    return true;
}

void CtMsgMainTask::sendMsg(CtMsg& Msg)
{
    // リクエストメール送信
    ER err;
    const CtMsg::CtMsgHeader* pHeader = Msg.getMsgHeader();  
    err = snd_mbx(CT_MBXID_MAIN, (T_MSG*)&(pHeader->Header));
    CtAssert(E_OK == err);

    err = set_flg(CT_FLGID_MAINTASK, CtMsgMainTask::FLGPTN_MAIN_MSG);

	
    return;
}
