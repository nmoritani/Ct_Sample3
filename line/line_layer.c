/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           layer controler of line block
 */
#include "line_layer.h"
#include "line_task.h"
#include "line_debug.h"

#define LINE_REQUEST_MAX				60 /* 描画要求できる数 */
#define LINE_DRAW_OBJECT_CONTAINER_MAX	60 /* レイヤに登録できるコンテナ数 */

typedef enum _LINE_COMMAND_ {
	LINE_COMMAND_SKIP,			/* 何もしない */
	LINE_COMMAND_DRAW,			/* 描画する */
	LINE_COMMAND_ERASE,			/* 消去する */
	LINE_COMMAND_UPDATE			/* DRAW や ERASE の結果、再描画する */
} LINE_COMMAND;

typedef struct _LINE_DRAW_QUEUE_ {
	LINE_LAYER_INDEX layerIndex;
	BOOL isDisp;
	LINE_DRAW_OBJECT *object;
} LINE_DRAW_QUEUE;

typedef struct _LINE_DRAW_OBJECT_CONTAINER_ {
	LINE_DRAW_OBJECT *object;
	LINE_DRAW_OBJECT *redraw;
	LINE_COMMAND command;
	struct _LINE_DRAW_OBJECT_CONTAINER_ *next;
} LINE_DRAW_OBJECT_CONTAINER;

typedef struct _LINE_DRAW_OBJECT_CONTAINER_RESOURCE_ {
	LINE_DRAW_OBJECT_CONTAINER container;
	BOOL isUse;
} LINE_DRAW_OBJECT_CONTAINER_RESOURCE;

typedef struct _LINE_LAYER_ {
	LINE_DRAW_OBJECT_CONTAINER *list;
} LINE_LAYER;

typedef struct _LINE_LAYER_INFO_ {
	LINE_DRAW_QUEUE requestQueue[LINE_REQUEST_MAX];
	UB requestQueueNum;
	LINE_LAYER layer[LINE_LAYER_NUM];
	BOOL isBusy;
} LINE_LAYER_INFO;

static LINE_DRAW_OBJECT_CONTAINER_RESOURCE ContainerResource[LINE_DRAW_OBJECT_CONTAINER_MAX];
static LINE_LAYER_INFO LcdInfo;
static LINE_LAYER_INFO HdmiInfo;
static LINE_LAYER_INFO SdiInfo;

static LINE_LAYER_INFO* line_GetLayerInfo(GUI_OUTPUT_DEV output);
static LINE_ERR line_PushRequest(LINE_LAYER_INFO *info, LINE_LAYER_INDEX layerIndex, BOOL isDisp, LINE_DRAW_OBJECT *object);
static BOOL line_DischargeRequest(LINE_LAYER_INFO *info);
static LINE_LAYER* line_GetLayer(LINE_LAYER_INFO *layerInfo, LINE_LAYER_INDEX layerIndex);
static LINE_ERR line_AddObjectToLayer(LINE_LAYER *layer, BOOL isDisp, LINE_DRAW_OBJECT *object);
static LINE_DRAW_OBJECT_CONTAINER* line_SearchContainerInLayer(LINE_LAYER *layer, LINE_OBJECT_ID id);
static LINE_DRAW_OBJECT_CONTAINER* line_CreateObjectContainer(LINE_COMMAND command, LINE_DRAW_OBJECT *object);
static LINE_ERR line_DeleteObjectContainer(LINE_DRAW_OBJECT_CONTAINER *container);
static void line_ExecLayer(LINE_LAYER_INFO *info);
static void line_CareOverlapping(LINE_LAYER *layer);
static void line_CheckOverlappingAll(LINE_LAYER *layer, LINE_DRAW_OBJECT *object);
static void line_DrawAll(LINE_LAYER *layer);

/* --- API --- */
/**
   @brief   レイヤ制御初期化
   @param[in] なし
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_InitLayer(void)
{
	/* 管理変数のクリア …は、 static 領域だから省略 */
	/* memset(&ContainerResource, 0, sizeof(ContainerResource)); */
	/* memset(&LcdInfo, 0, sizeof(LcdInfo)); */
	/* memset(&HdmiInfo, 0, sizeof(HdmiInfo)); */
	/* memset(&SdiInfo, 0, sizeof(SdiInfo)); */
	return LINE_OK;
}

/**
   @brief   描画要求 レイヤ構成を保ちつつ描画する
   @param[in] output     : 表示先の選択
   @param[in] layerIndex : どのレイヤに表示するか
   @param[in] isDisp     : 表示の ON/OFF 指定
   @param[in] *object    : 描画する部品
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_RequestLayer(GUI_OUTPUT_DEV output, LINE_LAYER_INDEX layerIndex, BOOL isDisp, LINE_DRAW_OBJECT *object)
{
	LINE_LAYER_INFO *info = line_GetLayerInfo(output);
	if ((info == NULL) || (object == NULL)) {
		return LINE_ERR_BADARG;
	}

	return line_PushRequest(info, layerIndex, isDisp, object);
}

/**
   @brief   レイヤ制御実施
   @param[in] なし
   @retval LINE_ERR (@ref line_ctrl.h)
*/
void Line_ExecLayer()
{
	BOOL isExecLcd = FALSE;
	BOOL isExecHdmi = FALSE;
	BOOL isExecSdi = FALSE;

	/* 要求された内容でレイヤリスト更新 */
	LINE_LOCK_LAYERINFO();
	isExecLcd = line_DischargeRequest(&LcdInfo);
	isExecHdmi = line_DischargeRequest(&HdmiInfo);
	isExecSdi = line_DischargeRequest(&SdiInfo);
	LINE_UNLOCK_LAYERINFO();

	LineDebugPrint("dischargeReq LCD:%d HDMI:%d SDI:%d\n", isExecLcd, isExecHdmi, isExecSdi);

	/* レイヤリストに更新があれば描画実行 */
	if (isExecLcd == TRUE) {
		line_ExecLayer(&LcdInfo);
	}
	if (isExecHdmi == TRUE) {
		line_ExecLayer(&HdmiInfo);
	}
	if (isExecSdi == TRUE) {
		line_ExecLayer(&SdiInfo);
	}
}

/* ---ローカル関数--- */
/**
   @brief   レイヤ管理情報の取得 (表示デバイス毎に管理情報がある)
   @param[in] output   : 表示先の選択
   @retval LINE_LAYER_INFO*
*/
LINE_LAYER_INFO* line_GetLayerInfo(GUI_OUTPUT_DEV output)
{
	LINE_LAYER_INFO *info;

	switch( output ){
	case GUI_OUTPUT_LCD:
		info = &LcdInfo;
		break;
	case GUI_OUTPUT_HDMI:
		info = &HdmiInfo;
		break;
	case GUI_OUTPUT_SDI:
		info = &SdiInfo;
		break;
	default:
		info = NULL;
		break;
	}
	return info;
}

/**
   @brief   描画要求をレイヤ毎のキューに積む
   @param[in] info       : レイヤ管理情報
   @param[in] layerIndex : どのレイヤに表示するか
   @param[in] isDisp     : 表示の ON/OFF 指定
   @param[in] *object    : 描画する部品
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR line_PushRequest(LINE_LAYER_INFO *info, LINE_LAYER_INDEX layerIndex, BOOL isDisp, LINE_DRAW_OBJECT *object)
{
	LINE_DRAW_QUEUE *queue;

	if ((info == NULL) || (object == NULL)) {
		return LINE_ERR_BADARG;
	}

	if (info->requestQueueNum >= LINE_REQUEST_MAX) {
		return LINE_ERR_NOMEM;
	}

	LINE_LOCK_LAYERINFO();
	queue = &(info->requestQueue[info->requestQueueNum++]);
	queue->layerIndex = layerIndex;
	queue->isDisp = isDisp;
	queue->object = object;
	LINE_UNLOCK_LAYERINFO();
	Line_SendMessageFlag(LINE_FLG_DRAW_EXEC);
	return LINE_OK;
}

/**
   @brief   要求を処理していく
   @param[in] info     : レイヤ管理情報
   @retval BOOL レイヤ処理が必要
*/
BOOL line_DischargeRequest(LINE_LAYER_INFO *info)
{
	LINE_DRAW_QUEUE *queue;
	UB ii;
	BOOL isExec = FALSE;

	if (info == NULL) {
		return LINE_ERR_BADARG;
	}

	/* 描画要求をレイヤ毎のキューから取り出して処理。キュー構造手抜きしたので pop 処理は作れずw */
	for (ii = 0; ii < info->requestQueueNum; ii++) {
		LINE_LAYER *layer;
		queue = &(info->requestQueue[ii]);
		/* キューからオブジェクトを取り出してレイヤに登録 */
		layer = line_GetLayer(info, queue->layerIndex);
		line_AddObjectToLayer(layer, queue->isDisp, queue->object); /* NULL チェックは Add で実施 */
		isExec = TRUE;
	}
	info->requestQueueNum = 0;	/* キューを空にする */

	return isExec;
}

/**
   @brief   レイヤを取得
   @param[in] *layerInfo : 管理情報
   @param[in] layerIndex : どのレイヤに表示するか
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_LAYER* line_GetLayer(LINE_LAYER_INFO *layerInfo, LINE_LAYER_INDEX layerIndex)
{
	if ((layerInfo == NULL) || (layerIndex >= LINE_LAYER_NUM)) {
		return NULL;
	}

	return &(layerInfo->layer[layerIndex]);
}

/**
   @brief   レイヤにオブジェクトを追加
   @param[in] *layer     : 追加対象レイヤ
   @param[in] isDisp     : 表示制御
   @param[in] *objdect   : 描画オブジェクト本体
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR line_AddObjectToLayer(LINE_LAYER *layer, BOOL isDisp, LINE_DRAW_OBJECT *object)
{
	LINE_DRAW_OBJECT_CONTAINER *container;

	if ((layer == NULL) || (object == NULL)) {
		Line_DeleteDrawObj(object); /* object が残るので削除 (NULL でも問題ない) */
		return LINE_ERR_BADARG;
	}

	container = line_SearchContainerInLayer(layer, object->id); /* オブジェクトが登録済みか検索 */

	if (isDisp == TRUE) {		 /* 描画する */
		if (container != NULL) { /* レイヤに登録されている→更新 */
			container->command = LINE_COMMAND_DRAW;
			if (container->redraw != NULL) { /* 書き換え登録が既に存在する場合 */
				Line_DeleteDrawObj(container->redraw); /* 後勝ちにするので削除 */
			}
			container->redraw = object;	/* 書き換え登録 */
		} else {				/* レイヤに登録されていない→追加 */
			LINE_DRAW_OBJECT_CONTAINER *new;

			/* レイヤリスト追加用のコンテナ作成 */
			new = line_CreateObjectContainer(LINE_COMMAND_DRAW, object);
			if (new == NULL) {
				Line_DeleteDrawObj(object); /* object が残るので削除 */
				return LINE_ERR_NOMEM;
			}

			/* リストに追加 */
			if (layer->list == NULL) { /* リストが空 */
				layer->list = new;
			} else {
				LINE_DRAW_OBJECT_CONTAINER *end = layer->list;
				/* リスト先端に追加するので、先端をサーチ */
				while( end->next != NULL ){
					end = end->next;
				}
				/* リスト接続 */
				end->next = new;
				new->next = NULL;
			}
		}
	} else {					 /* 削除する */
		if (container != NULL) { /* レイヤに登録されている */
			container->command = LINE_COMMAND_ERASE;
			if (container->redraw != NULL) { /* 書き換え登録が既に存在する場合 */
				Line_DeleteDrawObj(container->redraw); /* 後勝ち i.e. 消去なので描画の必要なし */
				container->redraw = NULL;
			}
		}
		Line_DeleteDrawObj(object); /* 引数のオブジェクトはもう不要なので削除 */
	}
	return LINE_OK;
}

/**
   @brief   レイヤから指定オブジェクトを積んでいるコンテナを検索
   @param[in] *layer : 検索対象レイヤ
   @param[in] id     : 検索するオブジェクト識別 ID
   @retval LINE_DRAW_OBJECT_CONTAINER* 見付かったコンテナ (見付からなかったら NULL を返す)
*/
LINE_DRAW_OBJECT_CONTAINER* line_SearchContainerInLayer(LINE_LAYER *layer, LINE_OBJECT_ID id)
{
	LINE_DRAW_OBJECT_CONTAINER* find = NULL;

	if (layer == NULL) {
		return NULL;
	}

	find = layer->list;
	while (find != NULL) {
		if (find->object->id == id) { /* 登録されている */
			break;
		}
		find = find->next;
	}
	return find;
}

/**
   @brief   レイヤリスト追加用のコンテナ作成
   @param[in] command : 描画コマンド
   @param[in] object  : 描画するオブジェクト
   @retval LINE_DRAW_OBJECT_CONTAINER* 作成したコンテナ (エラーなら NULL を返す)
*/
LINE_DRAW_OBJECT_CONTAINER* line_CreateObjectContainer(LINE_COMMAND command, LINE_DRAW_OBJECT *object)
{
	UB ii;
	LINE_DRAW_OBJECT_CONTAINER *container = NULL;

	for (ii = 0; ii < LINE_DRAW_OBJECT_CONTAINER_MAX; ii++) {
		if (ContainerResource[ii].isUse != TRUE) {
			ContainerResource[ii].isUse = TRUE;
			container = &(ContainerResource[ii].container);
			container->command = command;
			container->object = object;
			container->next = NULL;
			container->redraw = NULL;
			break;
		}
	}
	return container;
}

/**
   @brief   レイヤリスト追加用のコンテナ開放
   @param[in] container : 開放するコンテナ
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR line_DeleteObjectContainer(LINE_DRAW_OBJECT_CONTAINER *container)
{
	UB ii;

	if (container == NULL) {
		return LINE_ERR_BADARG;
	}

	for (ii = 0; ii < LINE_DRAW_OBJECT_CONTAINER_MAX; ii++) {
		if ((ContainerResource[ii].isUse == TRUE) && (&(ContainerResource[ii].container) == container)) {
			Line_DeleteDrawObj(container->object);
			Line_DeleteDrawObj(container->redraw);
			ContainerResource[ii].isUse = FALSE;
			break;
		}
	}
	return LINE_OK;
}

/**
   @brief   レイヤリスト制御
   @param[in] *info  : レイヤ情報
   @retval なし
*/
void line_ExecLayer(LINE_LAYER_INFO *info)
{
	if (info == NULL) {
		return;
	}
	info->isBusy = TRUE;		/* 描画要求の処理禁止 */

	line_CareOverlapping(info->layer); /* 部品同士の重なりをケア */
	line_DrawAll(info->layer); /* レイヤ上の必要なオブジェクトを描画 */

	info->isBusy = FALSE;		/* 描画要求の処理受け付け開始 */
}

/**
   @brief   レイヤ上の全オブジェクトについて、他のオブジェクトと重なっていれば描画設定にする
   @param[in] *info  : レイヤ情報
   @retval なし
*/
void line_CareOverlapping(LINE_LAYER *layer)
{
	UB ii;

	if (layer == NULL) {
		return;
	}

	/* 描画指定があるコンテナを探す → 他のオブジェクトと比較 */
	for (ii = LINE_LAYER_BASE; ii < LINE_LAYER_NUM; ii++) {
		LINE_DRAW_OBJECT_CONTAINER *container = layer[ii].list;
		while (container != NULL) {
			if ((container->command == LINE_COMMAND_DRAW) || (container->command == LINE_COMMAND_ERASE)) {
				line_CheckOverlappingAll(layer, container->object); /* 重なりをチェック */;
				if (container->redraw != NULL) { /* 更新対象のオブジェクトが存在する場合は、そちらもチェック */
					line_CheckOverlappingAll(layer, container->redraw);
				}
			}
			container = container->next;
		}
	}
}

/**
   @brief   指定コンテナ上のオブジェクトについて、他のオブジェクトと重なっていれば描画設定にする
   @param[in] *info      : レイヤ情報
   @param[in] *container : 比較元オブジェクト
   @retval なし
*/
void line_CheckOverlappingAll(LINE_LAYER *layer, LINE_DRAW_OBJECT *object)
{
	UB ii;
	if ((layer == NULL) || (object == NULL)) {
		return;
	}

	/* 比較先のオブジェクトを捜査 */
	for (ii = LINE_LAYER_BASE; ii < LINE_LAYER_NUM; ii++) {
		LINE_DRAW_OBJECT_CONTAINER *container = layer[ii].list;
		while (container != NULL) {
			/* 自分自身と比較しないよう object->id によるチェックもしておきたいが、
			   比較元は書き換えが確定している (command ≠ SKIP) ため、 command のチェックだけで充分 */
			if (container->command == LINE_COMMAND_SKIP) { /* 既に描画処理が必要になっているものはチェックの必要なし */
				if (Line_IsOverlapping(object, container->object) == TRUE) {
					container->command = LINE_COMMAND_UPDATE;
					line_CheckOverlappingAll(layer, container->object); /* 比較先が更新されたので、その影響をチェック */
				}
			}
			container = container->next;
		}
	}
}

/**
   @brief   レイヤ上の描画指定オブジェクトを全て描画する
   @param[in] *info  : レイヤ情報
   @retval なし
*/
void line_DrawAll(LINE_LAYER *layer)
{
	UB ii;

	if (layer == NULL) {
		return;
	}

	/* 描いた後に消すとまずいので、消す処理だけ (更新用の削除も含む) を最初にする */
	for (ii = LINE_LAYER_BASE; ii < LINE_LAYER_NUM; ii++) {
		LINE_DRAW_OBJECT_CONTAINER *container = layer[ii].list;
		LINE_DRAW_OBJECT_CONTAINER *prev = NULL;
		while (container != NULL) {
			if (container->command == LINE_COMMAND_ERASE) {
				Line_Erase(container->object);
				/* リストから消す場合、 prev に変化なし */
				if (prev == NULL) { /* リスト先頭の場合 */
					layer[ii].list = container->next;
					line_DeleteObjectContainer(container);
					container = layer[ii].list; /* 次回対象のポインタ */
				} else {
					prev->next = container->next;
					line_DeleteObjectContainer(container);
					container = prev->next; /* 次回対象のポインタ */
				}
			} else if ((container->redraw != NULL) && (container->command == LINE_COMMAND_DRAW)) {
				Line_Erase(container->object);
				Line_DeleteDrawObj(container->object); /* 更新の場合はリストに残るので、コンテナを削除する必要はない */
				container->object = container->redraw; /* 更新対象を挿げ替え */
				container->redraw = NULL;
				prev = container;	/* 一つ前を保持 */
				container = container->next;
			} else {
				prev = container;	/* 一つ前を保持 */
				container = container->next;
			}
		}
	}

	/* 描画処理 */
	for (ii = LINE_LAYER_BASE; ii < LINE_LAYER_NUM; ii++) {
		LINE_DRAW_OBJECT_CONTAINER *container = layer[ii].list;
		while (container != NULL) {
			if (container->command != LINE_COMMAND_SKIP) { /* 削除は既に済んでいるので、 DRAW か UPDATE しかない */
				Line_Draw(container->object);
				container->command = LINE_COMMAND_SKIP;
			}
			container = container->next;
		}
	}
}
