/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version: 7.5.1
 *  Element:          CtMsgDbgTask
 */
#include <stdlib.h>

#include "CtMsgDbgTask.h"
#include "CtMsg.h"
#include "CtMsgDbgCmnd.h"

bool CtMsgDbgTask::receiveMsg(CtMsg*& pMsg)
{
	ER Err;

	T_MSG_PRI *pMsgSystem;

	ER result = prcv_mbx(CT_MBXID_DBG, (T_MSG **)&pMsgSystem);
	switch (result) {
	case E_RLWAI:
		//タスクの終了通知で強制的に抜けた場合
		pMsg = NULL;
		return true;
	case E_TMOUT:
		return true;
	default:
		CtMsg::CtMsgHeader* pMsgHeader = (CtMsg::CtMsgHeader*)pMsgSystem;
		pMsg = (CtMsg*)(pMsgHeader->pMsg);
		break;
	}
	// メールボックス内にまだメールがあるか確認
	T_RMBX Rmbx;
	Err = ref_mbx(CT_MBXID_DBG, &Rmbx);
	CtAssert(E_OK == Err);

	if (NULL != Rmbx.pk_msg) {
		return false;
	}
	return true;
}

ER CtMsgDbgTask::sendMsg(CtMsg& Msg) {
	// リクエストメール送信
	ER err;
	const CtMsg::CtMsgHeader* pHeader = Msg.getMsgHeader();
	err = snd_mbx(CT_MBXID_DBG, (T_MSG*)&(pHeader->Header));
	CtAssert(E_OK == err);

	set_flg(CT_FLGID_DBGTASK, CtMsgDbgTask::FLGPTN_DBG_MSG);
	return err;
}
