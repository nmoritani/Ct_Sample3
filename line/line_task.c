/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           task of draw control in line block
 */
/* line 描画制御タスク */
#include "line_task.h"
#include "line_layer.h"
#include "line_dd.h"
#include "line_debug.h"

typedef enum {
	LINE_MSG_FLAG,
	LINE_MSG_CHANGE_RESOLUTION,
} LINE_MSG_ID;

typedef struct {
	T_MSG head;
	struct {
		LINE_MSG_ID id;
		union {
			LINE_MSG_DATA_FLAG flag;
			struct {
				GUI_OUTPUT_DEV output;
				GUI_VIDEO_FORMAT signal;
				GUI_VIDEO_FORMAT image;
			} resolution;
		} data;
	} body;
} LINE_MSG;

typedef struct {				/* メッセージ用のメモリ管理構造体 */
	BOOL isUsed;
	LINE_MSG body;
} LINE_MSG_MEMORY;

static LINE_MSG_MEMORY MsgMemory[64];
static const UB MsgMemoryIdMax = sizeof MsgMemory / sizeof(LINE_MSG_MEMORY);

static void line_InitMemory(void);
static LINE_MSG* line_GetMsgMemory(void);
static void line_ReleaseMsgMemory(LINE_MSG *msg);

/**
   @brief   初期処理
   @param  なし
   @retval なし
*/
void Line_InitTask(void)
{
	line_InitMemory();
	act_tsk(GUI_LINE_TSK_ID);
}

/**
   @brief   Line Task にフラグ型のメッセージを送る
   @param[in] flag  : フラグ情報
   @retval なし
*/
void Line_SendMessageFlag(LINE_MSG_DATA_FLAG flag)
{
	LINE_MSG *msg = line_GetMsgMemory();
	if (msg == NULL) {
		LineDebugPrint("Memory Get Error!! No memory.\n");
		return;
	}

	msg->body.id = LINE_MSG_FLAG;
	msg->body.data.flag = flag;
	snd_mbx(GUI_MBXID_LINE, &(msg->head));
}

/**
   @brief   Line Task に解像度変更メッセージを送る
   @param[in] output  : 出力先
   @param[in] signal  : OSD 信号画角
   @param[in] image   : OSD 映像画角
   @retval なし
*/
void Line_SendMessageChangeResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image)
{
	LINE_MSG *msg = line_GetMsgMemory();

	if ((signal == NULL) || (image == NULL)) {
		LineDebugPrint("parameter error!! sig=%08x img=%08x\n", signal, image);
		return;
	}

	if (msg == NULL) {
		LineDebugPrint("Memory Get Error!! No memory.\n");
		return;
	}

	msg->body.id = LINE_MSG_CHANGE_RESOLUTION;
	msg->body.data.resolution.output = output;
	msg->body.data.resolution.signal = *signal;
	msg->body.data.resolution.image = *image;
	snd_mbx(GUI_MBXID_LINE, &(msg->head));
}

/**
   @brief   Line Task メイン処理
   @param  なし
   @retval なし
*/
void Line_Main(void)
{
	static LINE_MSG_DATA_FLAG flags = 0;

	while (1) {
		T_MSG *pMsg = NULL;
		LINE_MSG *pLineMsg;
		T_RMBX rmbx;
		ER result;

		result = rcv_mbx(GUI_MBXID_LINE, &pMsg);
		pLineMsg = (LINE_MSG*)pMsg;
		if (result != E_OK) {
			line_ReleaseMsgMemory(pLineMsg);
			/* エラー発生!! でも、どうしようもない… */
			LineDebugPrint("Error on rcv_msg!! err=%d\n", result);
			continue;
		}
		if (pLineMsg == NULL) {
			LineDebugPrint("Error!! no message.\n");
			continue;
		}

		switch (pLineMsg->body.id) {
		case LINE_MSG_FLAG:		/* 要求を溜めておいて後で処理する */
			flags |= pLineMsg->body.data.flag;
			break;
		case LINE_MSG_CHANGE_RESOLUTION:
			Line_ChangeResolution(pLineMsg->body.data.resolution.output, &pLineMsg->body.data.resolution.signal, &pLineMsg->body.data.resolution.image);
			break;
		default:
			LineDebugPrint("Error!! irregular message %d\n", pLineMsg->body.id);
			break;
		}
		line_ReleaseMsgMemory(pLineMsg);

		/* メールボックスが空になったらフラグ処理 */
		result = ref_mbx(GUI_MBXID_LINE, &rmbx);
		if (result != E_OK) {
			/* エラー発生!! でも、どうしようもない… */
			LineDebugPrint("Error on ref_mbx!! err=%d\n", result);
			continue;
		}
		if (rmbx.pk_msg == NULL) {
			if (flags & LINE_FLG_DRAW_EXEC) {
				Line_ExecLayer();
			}

			flags = 0;
		}
	}
}

/**
   @brief   メッセージ用のメモリ初期化
   @param  なし
   @retval メモリアドレス (取得失敗時は NULL)
*/
void line_InitMemory(void)
{
	UB memId;

	for (memId = 0; memId < MsgMemoryIdMax; memId++) {
		MsgMemory[memId].isUsed = FALSE;
	}
}

/**
   @brief   メッセージ用のメモリを取得
   @param  なし
   @retval メモリアドレス (取得失敗時は NULL)
*/
LINE_MSG* line_GetMsgMemory(void)
{
	LINE_MSG *memory = NULL;
	UB memId;

	for (memId = 0; memId < MsgMemoryIdMax; memId++) {
		if (MsgMemory[memId].isUsed == FALSE) {
			memory = &MsgMemory[memId].body;
			MsgMemory[memId].isUsed = TRUE;
			break;
		}
	}

	return memory;
}

/**
   @brief   メッセージ用のメモリを解放
   @param[in] msg  : 解放するメモリのアドレス
   @retval なし
*/
void line_ReleaseMsgMemory(LINE_MSG *memory)
{
	UB memId;

	for (memId = 0; memId < MsgMemoryIdMax; memId++) {
		if (memory == &MsgMemory[memId].body) {
			if (MsgMemory[memId].isUsed != TRUE) {
				LineDebugPrint("Error!! memory (%08x) is released already.\n", memory);
			}
			MsgMemory[memId].isUsed = FALSE;
			break;
		}
	}
}
