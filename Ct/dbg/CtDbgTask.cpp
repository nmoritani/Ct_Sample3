/**
 *	Copyright(c) 2018 Persol AVC Technology.
 *	$Id$
 *
 *	@file
 *	@brief	���C���^�X�N�̃G���g���֐�
*/

#include "CtMsgDbgTask.h"
#include "CtTimer.h"
#include "CtDbgCmndReceiver.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

	void Ct_DbgTask()
	{
		CtDebugPrint(CtDbg, "�������� ActDbgTsk ��������\n");
		CtDbgCmndReceiver* pCmndRcvr = CtDbgCmndReceiver::getInstance();
		CtTimer *pTimer = CtTimer::getInstance();

		FLGPTN flgptn;
		ER err;

		/* �C�x���g�������[�v */
		while (1) {
			CtMsg* pMsg = NULL;
			flgptn = 0;
			err = wai_flg(CT_FLGID_DBGTASK, (CtMsgDbgTask::FLGPTN_ALL), TWF_ORW, &flgptn);

#ifdef WIN32_GUI_SIM
			if (0 != (flgptn & CtMsgDbgTask::FLGPTN_DBG_STOP)) {
				break;
			}
#endif
			if (flgptn & CtMsgDbgTask::FLGPTN_DBG_MSG) {
				// ���[���{�b�N�X����Msg���擾����B
				bool ret;
				do {
					ret = CtMsgDbgTask::receiveMsg(pMsg);	/* pgr0522	*/
					if (pMsg != NULL) {
						pCmndRcvr->receiveMsg(*pMsg);
						
						// Receiver���ō폜
						//if(pMsg != NULL) delete pMsg;
					}
				} while (!ret);
			}
			if (flgptn & CtMsgDbgTask::FLGPTN_DBG_TIMER) {
				pTimer->receiveFlg(CtMsgDbgTask::FLGPTN_DBG_TIMER);
			}
		}
		if (pCmndRcvr != NULL) {
			delete pCmndRcvr;
			pCmndRcvr = NULL;
		}
		return;
	}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

