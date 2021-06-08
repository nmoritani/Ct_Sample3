/**
 *	Copyright(c) 2018 Persol AVC Technology.ogy., All rights reserved
 *	$Id$
 *
 *	@file
 *	@brief	メインタスクのエントリ関数
*/

#include "kernel.h"
#include "kernel_id.h"
#include "gui_timestamp_task.h"
#include "CtTimeStamp.h"

static GuiTsInfo m_TsInfo[GUI_TIMESTAMP_MAX];
static bool m_Initialize = false;

static GuiTsMsg *createMsg();
static void destroyMsg(GuiTsMsg *pMsg);
static int sndMsg(GuiTsMsg *pMsg);
static int prcvMsg(GuiTsMsg *&msg);

#define FLGPTN_TS_WAKEUP	0x00000800
#define FLGPTN_TS_STOP		0x00000400
#define FLGPTN_TS_ALL		(FLGPTN_TS_WAKEUP|FLGPTN_TS_STOP)

int GUI_TS_Init(const GuiTsInfo *info)
{
	if (!m_Initialize) {
		m_Initialize = true;
		memset(&m_TsInfo, 0, sizeof(m_TsInfo));
		act_tsk(GUI_TS_TSKID);
	}

	if (info == NULL)
		return -1;
	
	for (int i = 0; i < GUI_TIMESTAMP_MAX; i++) {
		if (m_TsInfo[i].pTimeStamp == NULL) {

			m_TsInfo[i] = *info;

			m_TsInfo[i].pTimeStamp = new CtTimeStamp(info->Size, info->coloFormat, info->colorDepth, info->DispMode);

			return i;
		}
	}

	return -1;
}

int GUI_TS_Create(int id, GUI_TS_CALLBACK cbFunc)
{
	if (!m_Initialize) {
		return -1;
	}

	GuiTsMsg *pMsg = createMsg();

	if (!pMsg) return -1;

	pMsg->type = TsMsgCreate;
	pMsg->data.create.id = id;
	pMsg->data.create.callback = cbFunc;

	return sndMsg(pMsg);
}

int GUI_TS_Get(int id, GUI_TS_INFO  *info)
{
	if (!m_Initialize || !m_TsInfo[id].pTimeStamp) {
		return -1;
	}

	bool ret = m_TsInfo[id].pTimeStamp->getCurrent(info);

	return ret ? 0 : -1;
}

int GUI_TS_Destroy(int id)
{
	if (!m_Initialize || !m_TsInfo[id].pTimeStamp) {
		return -1;
	}

	m_TsInfo[id].pTimeStamp->setInvalid();
	
	GuiTsMsg *pMsg = createMsg();

	if (!pMsg) return -1;

	pMsg->type = TsMsgDestroy;
	pMsg->data.destroy.id = id;

	return sndMsg(pMsg);
}

//////////////////////////////////
// タスク間通信用関数群
//////////////////////////////////
GuiTsMsg *createMsg()
{
	GuiTsMsg *pMsg = NULL;
	ER err = get_mpl(GUI_TS_MPLID, sizeof(GuiTsMsg), (VP*)&pMsg);
	if (err != E_OK || !pMsg) {
		return NULL;
	}
	return pMsg;
}

void destroyMsg(GuiTsMsg *pMsg)
{
	rel_mpl(GUI_TS_MPLID, pMsg);
}

int sndMsg(GuiTsMsg *pMsg)
{
	if (!pMsg) return -1;

	ER err = snd_dtq(GUI_TS_DTQID, pMsg);
	if (err != E_OK) {
		destroyMsg(pMsg);
		return -1;
	}
	return 0;
}

int prcvMsg(GuiTsMsg *&msg)
{
	msg = NULL;

	ER err = prcv_dtq(GUI_TS_DTQID, (VP_INT*)&msg);
	if (msg != NULL) {
		return 0;
	}
	return -1;
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

//////////////////////////////////
// タスクエントリポイント
//////////////////////////////////
void GUI_TsTask()
{
	ER err;
	GuiTsMsg *pMsg = NULL;
	FLGPTN	flgptn;

	/* イベント処理ループ */
	while (1) {
		wai_flg(GUI_TS_FLGID, FLGPTN_TS_ALL, TWF_ORW, &flgptn);

		if (flgptn & FLGPTN_TS_STOP) {
			break;
		}

		if ((err = prcvMsg(pMsg)) < 0) {
			for (int i = 0; i < GUI_TIMESTAMP_MAX; i++) {
				CtTimeStamp *pTs = m_TsInfo[i].pTimeStamp;
				
				if (pTs && pTs->isCreated()) {
					pTs->update();
				}
			}
			continue;
		}
		
		// 他タスクからのメッセージ処理
		switch (pMsg->type) {
		case TsMsgCreate:
		{
			int id = pMsg->data.create.id;
			m_TsInfo[id].pTimeStamp->create();
			
			if (pMsg->data.create.callback) {
				pMsg->data.create.callback(id);
			}
			
			break;
		}
		case TsMsgDestroy:
		{
			W id = pMsg->data.destroy.id;
			m_TsInfo[id].pTimeStamp->destroy();
			
			delete m_TsInfo[id].pTimeStamp;
			memset(&m_TsInfo[id], 0, sizeof(GuiTsInfo));
			break;
		}
		default:
			break;
		}
		destroyMsg(pMsg);
	}
}

void GUI_TsWakeup()
{
	set_flg(GUI_TS_FLGID, FLGPTN_TS_WAKEUP);
}
	
#if defined(__cplusplus)
}
#endif /* __cplusplus */

