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
    //���[���󂯎��
    CtMsg::CtMsgHeader* pMsgHeader;
    Err = rcv_mbx(CT_MBXID_DRAW, (T_MSG**)&pMsgHeader);
    CtAssert(E_OK == Err);

	if (E_RLWAI == Err) {
		//�^�X�N�̏I���ʒm�ŋ����I�ɔ������ꍇ
		pMsg = NULL;
		return;
	}

    // ��M�������b�Z�[�W�\���̂��ACtMesssage�N���X�̃|�C���^���擾����B
    pMsg = (CtMsg*)(pMsgHeader->pMsg);
    
    return;
}

void CtMsgDrawTask::sendMsg(CtMsg& Msg)
{
    // ���N�G�X�g���[�����M
    ER err;
    const CtMsg::CtMsgHeader* pHeader = Msg.getMsgHeader();  
    err = snd_mbx(CT_MBXID_DRAW, (T_MSG*)&(pHeader->Header));
    CtAssert(E_OK == err);

    return;
}
