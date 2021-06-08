/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           layer controler of line block
 */
#include "line_layer.h"
#include "line_task.h"
#include "line_debug.h"

#define LINE_REQUEST_MAX				60 /* �`��v���ł��鐔 */
#define LINE_DRAW_OBJECT_CONTAINER_MAX	60 /* ���C���ɓo�^�ł���R���e�i�� */

typedef enum _LINE_COMMAND_ {
	LINE_COMMAND_SKIP,			/* �������Ȃ� */
	LINE_COMMAND_DRAW,			/* �`�悷�� */
	LINE_COMMAND_ERASE,			/* �������� */
	LINE_COMMAND_UPDATE			/* DRAW �� ERASE �̌��ʁA�ĕ`�悷�� */
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
   @brief   ���C�����䏉����
   @param[in] �Ȃ�
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_InitLayer(void)
{
	/* �Ǘ��ϐ��̃N���A �c�́A static �̈悾����ȗ� */
	/* memset(&ContainerResource, 0, sizeof(ContainerResource)); */
	/* memset(&LcdInfo, 0, sizeof(LcdInfo)); */
	/* memset(&HdmiInfo, 0, sizeof(HdmiInfo)); */
	/* memset(&SdiInfo, 0, sizeof(SdiInfo)); */
	return LINE_OK;
}

/**
   @brief   �`��v�� ���C���\����ۂ��`�悷��
   @param[in] output     : �\����̑I��
   @param[in] layerIndex : �ǂ̃��C���ɕ\�����邩
   @param[in] isDisp     : �\���� ON/OFF �w��
   @param[in] *object    : �`�悷�镔�i
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
   @brief   ���C��������{
   @param[in] �Ȃ�
   @retval LINE_ERR (@ref line_ctrl.h)
*/
void Line_ExecLayer()
{
	BOOL isExecLcd = FALSE;
	BOOL isExecHdmi = FALSE;
	BOOL isExecSdi = FALSE;

	/* �v�����ꂽ���e�Ń��C�����X�g�X�V */
	LINE_LOCK_LAYERINFO();
	isExecLcd = line_DischargeRequest(&LcdInfo);
	isExecHdmi = line_DischargeRequest(&HdmiInfo);
	isExecSdi = line_DischargeRequest(&SdiInfo);
	LINE_UNLOCK_LAYERINFO();

	LineDebugPrint("dischargeReq LCD:%d HDMI:%d SDI:%d\n", isExecLcd, isExecHdmi, isExecSdi);

	/* ���C�����X�g�ɍX�V������Ε`����s */
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

/* ---���[�J���֐�--- */
/**
   @brief   ���C���Ǘ����̎擾 (�\���f�o�C�X���ɊǗ���񂪂���)
   @param[in] output   : �\����̑I��
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
   @brief   �`��v�������C�����̃L���[�ɐς�
   @param[in] info       : ���C���Ǘ����
   @param[in] layerIndex : �ǂ̃��C���ɕ\�����邩
   @param[in] isDisp     : �\���� ON/OFF �w��
   @param[in] *object    : �`�悷�镔�i
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
   @brief   �v�����������Ă���
   @param[in] info     : ���C���Ǘ����
   @retval BOOL ���C���������K�v
*/
BOOL line_DischargeRequest(LINE_LAYER_INFO *info)
{
	LINE_DRAW_QUEUE *queue;
	UB ii;
	BOOL isExec = FALSE;

	if (info == NULL) {
		return LINE_ERR_BADARG;
	}

	/* �`��v�������C�����̃L���[������o���ď����B�L���[�\���蔲�������̂� pop �����͍�ꂸw */
	for (ii = 0; ii < info->requestQueueNum; ii++) {
		LINE_LAYER *layer;
		queue = &(info->requestQueue[ii]);
		/* �L���[����I�u�W�F�N�g�����o���ă��C���ɓo�^ */
		layer = line_GetLayer(info, queue->layerIndex);
		line_AddObjectToLayer(layer, queue->isDisp, queue->object); /* NULL �`�F�b�N�� Add �Ŏ��{ */
		isExec = TRUE;
	}
	info->requestQueueNum = 0;	/* �L���[����ɂ��� */

	return isExec;
}

/**
   @brief   ���C�����擾
   @param[in] *layerInfo : �Ǘ����
   @param[in] layerIndex : �ǂ̃��C���ɕ\�����邩
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
   @brief   ���C���ɃI�u�W�F�N�g��ǉ�
   @param[in] *layer     : �ǉ��Ώۃ��C��
   @param[in] isDisp     : �\������
   @param[in] *objdect   : �`��I�u�W�F�N�g�{��
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR line_AddObjectToLayer(LINE_LAYER *layer, BOOL isDisp, LINE_DRAW_OBJECT *object)
{
	LINE_DRAW_OBJECT_CONTAINER *container;

	if ((layer == NULL) || (object == NULL)) {
		Line_DeleteDrawObj(object); /* object ���c��̂ō폜 (NULL �ł����Ȃ�) */
		return LINE_ERR_BADARG;
	}

	container = line_SearchContainerInLayer(layer, object->id); /* �I�u�W�F�N�g���o�^�ς݂����� */

	if (isDisp == TRUE) {		 /* �`�悷�� */
		if (container != NULL) { /* ���C���ɓo�^����Ă��遨�X�V */
			container->command = LINE_COMMAND_DRAW;
			if (container->redraw != NULL) { /* ���������o�^�����ɑ��݂���ꍇ */
				Line_DeleteDrawObj(container->redraw); /* �㏟���ɂ���̂ō폜 */
			}
			container->redraw = object;	/* ���������o�^ */
		} else {				/* ���C���ɓo�^����Ă��Ȃ����ǉ� */
			LINE_DRAW_OBJECT_CONTAINER *new;

			/* ���C�����X�g�ǉ��p�̃R���e�i�쐬 */
			new = line_CreateObjectContainer(LINE_COMMAND_DRAW, object);
			if (new == NULL) {
				Line_DeleteDrawObj(object); /* object ���c��̂ō폜 */
				return LINE_ERR_NOMEM;
			}

			/* ���X�g�ɒǉ� */
			if (layer->list == NULL) { /* ���X�g���� */
				layer->list = new;
			} else {
				LINE_DRAW_OBJECT_CONTAINER *end = layer->list;
				/* ���X�g��[�ɒǉ�����̂ŁA��[���T�[�` */
				while( end->next != NULL ){
					end = end->next;
				}
				/* ���X�g�ڑ� */
				end->next = new;
				new->next = NULL;
			}
		}
	} else {					 /* �폜���� */
		if (container != NULL) { /* ���C���ɓo�^����Ă��� */
			container->command = LINE_COMMAND_ERASE;
			if (container->redraw != NULL) { /* ���������o�^�����ɑ��݂���ꍇ */
				Line_DeleteDrawObj(container->redraw); /* �㏟�� i.e. �����Ȃ̂ŕ`��̕K�v�Ȃ� */
				container->redraw = NULL;
			}
		}
		Line_DeleteDrawObj(object); /* �����̃I�u�W�F�N�g�͂����s�v�Ȃ̂ō폜 */
	}
	return LINE_OK;
}

/**
   @brief   ���C������w��I�u�W�F�N�g��ς�ł���R���e�i������
   @param[in] *layer : �����Ώۃ��C��
   @param[in] id     : ��������I�u�W�F�N�g���� ID
   @retval LINE_DRAW_OBJECT_CONTAINER* ���t�������R���e�i (���t����Ȃ������� NULL ��Ԃ�)
*/
LINE_DRAW_OBJECT_CONTAINER* line_SearchContainerInLayer(LINE_LAYER *layer, LINE_OBJECT_ID id)
{
	LINE_DRAW_OBJECT_CONTAINER* find = NULL;

	if (layer == NULL) {
		return NULL;
	}

	find = layer->list;
	while (find != NULL) {
		if (find->object->id == id) { /* �o�^����Ă��� */
			break;
		}
		find = find->next;
	}
	return find;
}

/**
   @brief   ���C�����X�g�ǉ��p�̃R���e�i�쐬
   @param[in] command : �`��R�}���h
   @param[in] object  : �`�悷��I�u�W�F�N�g
   @retval LINE_DRAW_OBJECT_CONTAINER* �쐬�����R���e�i (�G���[�Ȃ� NULL ��Ԃ�)
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
   @brief   ���C�����X�g�ǉ��p�̃R���e�i�J��
   @param[in] container : �J������R���e�i
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
   @brief   ���C�����X�g����
   @param[in] *info  : ���C�����
   @retval �Ȃ�
*/
void line_ExecLayer(LINE_LAYER_INFO *info)
{
	if (info == NULL) {
		return;
	}
	info->isBusy = TRUE;		/* �`��v���̏����֎~ */

	line_CareOverlapping(info->layer); /* ���i���m�̏d�Ȃ���P�A */
	line_DrawAll(info->layer); /* ���C����̕K�v�ȃI�u�W�F�N�g��`�� */

	info->isBusy = FALSE;		/* �`��v���̏����󂯕t���J�n */
}

/**
   @brief   ���C����̑S�I�u�W�F�N�g�ɂ��āA���̃I�u�W�F�N�g�Əd�Ȃ��Ă���Ε`��ݒ�ɂ���
   @param[in] *info  : ���C�����
   @retval �Ȃ�
*/
void line_CareOverlapping(LINE_LAYER *layer)
{
	UB ii;

	if (layer == NULL) {
		return;
	}

	/* �`��w�肪����R���e�i��T�� �� ���̃I�u�W�F�N�g�Ɣ�r */
	for (ii = LINE_LAYER_BASE; ii < LINE_LAYER_NUM; ii++) {
		LINE_DRAW_OBJECT_CONTAINER *container = layer[ii].list;
		while (container != NULL) {
			if ((container->command == LINE_COMMAND_DRAW) || (container->command == LINE_COMMAND_ERASE)) {
				line_CheckOverlappingAll(layer, container->object); /* �d�Ȃ���`�F�b�N */;
				if (container->redraw != NULL) { /* �X�V�Ώۂ̃I�u�W�F�N�g�����݂���ꍇ�́A��������`�F�b�N */
					line_CheckOverlappingAll(layer, container->redraw);
				}
			}
			container = container->next;
		}
	}
}

/**
   @brief   �w��R���e�i��̃I�u�W�F�N�g�ɂ��āA���̃I�u�W�F�N�g�Əd�Ȃ��Ă���Ε`��ݒ�ɂ���
   @param[in] *info      : ���C�����
   @param[in] *container : ��r���I�u�W�F�N�g
   @retval �Ȃ�
*/
void line_CheckOverlappingAll(LINE_LAYER *layer, LINE_DRAW_OBJECT *object)
{
	UB ii;
	if ((layer == NULL) || (object == NULL)) {
		return;
	}

	/* ��r��̃I�u�W�F�N�g��{�� */
	for (ii = LINE_LAYER_BASE; ii < LINE_LAYER_NUM; ii++) {
		LINE_DRAW_OBJECT_CONTAINER *container = layer[ii].list;
		while (container != NULL) {
			/* �������g�Ɣ�r���Ȃ��悤 object->id �ɂ��`�F�b�N�����Ă����������A
			   ��r���͏����������m�肵�Ă��� (command �� SKIP) ���߁A command �̃`�F�b�N�����ŏ[�� */
			if (container->command == LINE_COMMAND_SKIP) { /* ���ɕ`�揈�����K�v�ɂȂ��Ă�����̂̓`�F�b�N�̕K�v�Ȃ� */
				if (Line_IsOverlapping(object, container->object) == TRUE) {
					container->command = LINE_COMMAND_UPDATE;
					line_CheckOverlappingAll(layer, container->object); /* ��r�悪�X�V���ꂽ�̂ŁA���̉e�����`�F�b�N */
				}
			}
			container = container->next;
		}
	}
}

/**
   @brief   ���C����̕`��w��I�u�W�F�N�g��S�ĕ`�悷��
   @param[in] *info  : ���C�����
   @retval �Ȃ�
*/
void line_DrawAll(LINE_LAYER *layer)
{
	UB ii;

	if (layer == NULL) {
		return;
	}

	/* �`������ɏ����Ƃ܂����̂ŁA������������ (�X�V�p�̍폜���܂�) ���ŏ��ɂ��� */
	for (ii = LINE_LAYER_BASE; ii < LINE_LAYER_NUM; ii++) {
		LINE_DRAW_OBJECT_CONTAINER *container = layer[ii].list;
		LINE_DRAW_OBJECT_CONTAINER *prev = NULL;
		while (container != NULL) {
			if (container->command == LINE_COMMAND_ERASE) {
				Line_Erase(container->object);
				/* ���X�g��������ꍇ�A prev �ɕω��Ȃ� */
				if (prev == NULL) { /* ���X�g�擪�̏ꍇ */
					layer[ii].list = container->next;
					line_DeleteObjectContainer(container);
					container = layer[ii].list; /* ����Ώۂ̃|�C���^ */
				} else {
					prev->next = container->next;
					line_DeleteObjectContainer(container);
					container = prev->next; /* ����Ώۂ̃|�C���^ */
				}
			} else if ((container->redraw != NULL) && (container->command == LINE_COMMAND_DRAW)) {
				Line_Erase(container->object);
				Line_DeleteDrawObj(container->object); /* �X�V�̏ꍇ�̓��X�g�Ɏc��̂ŁA�R���e�i���폜����K�v�͂Ȃ� */
				container->object = container->redraw; /* �X�V�Ώۂ�}���ւ� */
				container->redraw = NULL;
				prev = container;	/* ��O��ێ� */
				container = container->next;
			} else {
				prev = container;	/* ��O��ێ� */
				container = container->next;
			}
		}
	}

	/* �`�揈�� */
	for (ii = LINE_LAYER_BASE; ii < LINE_LAYER_NUM; ii++) {
		LINE_DRAW_OBJECT_CONTAINER *container = layer[ii].list;
		while (container != NULL) {
			if (container->command != LINE_COMMAND_SKIP) { /* �폜�͊��ɍς�ł���̂ŁA DRAW �� UPDATE �����Ȃ� */
				Line_Draw(container->object);
				container->command = LINE_COMMAND_SKIP;
			}
			container = container->next;
		}
	}
}
