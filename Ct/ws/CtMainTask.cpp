/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	���C���^�X�N�̃G���g���֐�
*/

#include "CtMsgMainTask.h"
#include "CtMsg.h"
#include "CtTimer.h"

#if defined(__cplusplus)
extern "C"{
#endif /* __cplusplus */

/* �n���O�A�b�v���o��` */
#define CT_MAIN_TASK_TIMEOUT 		(1000*5)
#define CT_MAIN_TASK_HANGUP_CHECK_NAME		"CT_MAIN"

void Ct_MainTask()
{
	CtDebugPrint(CtDbg, "------------------------------------Ct_MainTask\n");
	FLGPTN flgptn;
	ER err;

#ifndef WIN32_GUI_SIM
	ID	HangTaskId = SYS_HangDet_Open ((const char*)CT_MAIN_TASK_HANGUP_CHECK_NAME, CT_MAIN_TASK_TIMEOUT);		//�n���O���o�ݒ肵ID���擾
	if(HangTaskId >= 0){
		SYS_HangDet_Start(HangTaskId);	//�n���O���o�J�n
	}
#endif
	act_tsk(CT_DRAW_TSKID);
	
    /* �C�x���g�������[�v */
	while (1) {
		CtMsg* pMsg = NULL;
		flgptn = 0;
		err = wai_flg(CT_FLGID_MAINTASK, (CtMsgMainTask::FLGPTN_ALL), TWF_ORW, &flgptn);
		
#ifdef WIN32_GUI_SIM
		if (0 != (flgptn & CtMsgMainTask::FLGPTN_MAIN_STOP)) {
			break;
		}
#endif
		if (flgptn & CtMsgMainTask::FLGPTN_MAIN_MSG) {
			// ���[���{�b�N�X����Msg���擾����B
			bool ret;
			do {
				ret = CtMsgMainTask::receiveMsg(pMsg);	/* pgr0522	*/
				if (pMsg != NULL) {
					// Cmd���s
					static_cast<CtEvent*>(pMsg)->operationCmd();
					delete pMsg;
				}
			} while (!ret);
			
		}
		
		if (flgptn & CtMsgMainTask::FLGPTN_MAIN_TIMER) {
			CtTimer::getInstance()->receiveFlg(CtMsgMainTask::FLGPTN_MAIN_TIMER);
		}
#ifndef WIN32_GUI_SIM
		SYS_HangDet_Alive (HangTaskId);	//SYS�ɐ����ʒm
#endif		
    }

	return;
}

void CtCycHandler(VP_INT exinf)
{
	CtTimer::CycHandler(exinf);
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

