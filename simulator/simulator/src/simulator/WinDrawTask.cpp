/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   Window �ւ̕`��p�^�X�N (�V�~�����[�^�[�p)
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "SysIf.h"
#include "WinDrawTask.h"
#include "gdi.h"
#include "gdi_draw_test.h"

#include "CtMsgMainTask.h"
#include "CtMsgDrawTask.h"
#include "CtMsgDbgTask.h"

#define MSGBOX_MAX_DATA_LENGTH	10

typedef struct {
	T_MSG	hdr;
	USHORT msgtype;
	USHORT data_length;
	USHORT data[MSGBOX_MAX_DATA_LENGTH];
} WIN_DRAW_TASK_MSG;

static CALLBACK_WIN_DRAWTASK s_callbackfunc;

/****************************************************************************/
void WinDrawTask_Init(CALLBACK_WIN_DRAWTASK callbackfunc)
{
	s_callbackfunc = callbackfunc;
}

/****************************************************************************/

static void wait_task_terminate(ID id)
{
	T_RTSK rtsk;
	ER err;
	do {
		rtsk.tskstat = 0;
		err = ref_tsk(id, &rtsk);
		if ((E_OK == err) && (rtsk.tskstat & TTS_DMT)) {
			return;
		}
	} while (1);
}

void Simulator_terminate()
{
	//�܂Ƃ߂Ď~�߂ɍs���Ə��Ԗ��ŗ�������������1���m���ɒ�~�����Ă����B�B�B

	//�����n���h����~
	stp_cyc(CT_CYC_ID);
	stp_cyc(AVDF_CYC_ID);

	//CtDrawTask��~
	set_flg(CT_FLGID_DRAWTASK, CtMsgDrawTask::FLGPTN_DRAW_STOP);	//�I���ʒm�Z�b�g
	//ter_tsk(CT_FLGID_DRAWTASK);
	rel_wai(CT_DRAW_TSKID);		//�^�X�N�̑҂�����������
	wait_task_terminate(CT_DRAW_TSKID);								//�I���҂�

	//CtMainTask��~
	set_flg(CT_FLGID_MAINTASK, CtMsgMainTask::FLGPTN_MAIN_STOP);	//�I���ʒm�Z�b�g
	rel_wai(CT_MAIN_TSKID);											//�^�X�N�̑҂�����������
	wait_task_terminate(CT_MAIN_TSKID);								//�I���҂�

	//CtDbgTask��~
	set_flg(CT_FLGID_DBGTASK, CtMsgDbgTask::FLGPTN_DBG_STOP);		//�I���ʒm�Z�b�g
	rel_wai(CT_DBG_TSKID);											//�^�X�N�̑҂�����������
	wait_task_terminate(CT_DBG_TSKID);								//�I���҂�

	//�e���b�Z�[�W�̍폜
	del_mbx(CT_MBXID_DRAW);
	del_mbx(CT_MBXID_MAIN);
	del_mbx(MBXID_WIN_DRAW_TASK);
	del_mbx(CT_MBXID_DBG);

	// �Z�}�t�H�폜
	del_sem(CT_SEMID_RECEIVER);
	del_sem(CT_SEMID_OBJECT);
	del_sem(CT_SEMID_SYNCHRO);
	del_sem(CT_SEMID_GDI);
	del_sem(GDI_SEMID_FONTAPI);
	del_sem(GDI_SEMID_DRAW);
	del_sem(GDI_SEMID_CREATE_CACHE);
	del_sem(GDI_SEMID_CONTEXT);

	//�t���O�̍폜
	del_flg(CT_FLGID_MAINTASK);
	del_flg(CT_FLGID_DRAWTASK);
	del_flg(CT_FLGID_DBGTASK);

	//�����n���h���̍폜
	del_cyc(CT_CYC_ID);
	del_cyc(AVDF_CYC_ID);

	//�e�^�X�N�̍폜
	del_tsk(CT_DRAW_TSKID);
	del_tsk(CT_MAIN_TSKID);
	del_tsk(CT_DBG_TSKID);

	// �������v�[���폜
	del_mpl(GFX_RESMPL_ID);
  del_mpl(FONT_LIBMPL_ID);
	del_mpl(GUI_WORKMPL_ID);
	del_mpl(CT_MPL_ID);

}

/****************************************************************************/
/*!
 *	@brief	�V�~�����[�^�`��p
 */
void SimulatorWindowDraw(void)
{
#if 1
	ER result;
	T_MSG *pMsg;
	BOOL bIsDrawEnable = TRUE;

	while (1) {
		result = trcv_msg(MBXID_WIN_DRAW_TASK, &pMsg, 5);
		if ((E_ID == result)
			|| (E_NOEXS == result)
			|| (E_PAR == result)
			|| (E_CTX == result)) {
			//�G���[����
			break;
		}

		if (E_TMOUT != result) {
			WIN_DRAW_TASK_MSG* pDrawTaskMsg = (WIN_DRAW_TASK_MSG*)pMsg;
			USHORT msgtype = pDrawTaskMsg->msgtype;
			USHORT data_length = pDrawTaskMsg->data_length;
			USHORT *rcvData = pDrawTaskMsg->data;

			switch (msgtype) {
			case MBX_DRAWTEST_TYPE_STOP:
				//�I������
				Simulator_terminate();
				bIsDrawEnable = FALSE;
				s_callbackfunc();
				return;
			}
		}
	};
#endif
}

static WIN_DRAW_TASK_MSG msg;
BOOL WinDrawTask_sendMsg(int mbxid, USHORT msgtype, int length, USHORT *data)
{
	ER result;
	int i;
	if (MSGBOX_MAX_DATA_LENGTH < length) {
		return FALSE;
	}

	msg.hdr.msgpri = 1;
	msg.msgtype = msgtype;
	msg.data_length = length;

	for (i = 0; i < length; i++) {
		msg.data[i] = data[i];
	}

	result = snd_msg(mbxid, (T_MSG *)&msg);
	return (result == E_OK);
}

