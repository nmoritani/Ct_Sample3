/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           layer controler of line block
 */
#ifndef __LINE_LAYER_H__
#define __LINE_LAYER_H__

#include "sys_type.h"
#include "line_api.h"
#include "line_draw.h"

typedef enum _LINE_LAYER_INDEX_ {
	/* �`�揇 (�\���D�揇�ʂ��Ⴂ���̂�����ׂ�) */
	LINE_LAYER_GUIDELINE,		/* �K�C�h���C���w */
	LINE_LAYER_SAFETY_ZONE,		/* �Z�[�t�e�B�]�[���w */
	LINE_LAYER_FACE,			/* ��g�w */
    LINE_LAYER_AF_RANGE,        /* AF RANGE�w */
	LINE_LAYER_FOLLOW,			/* �ǂ������w */
	LINE_LAYER_SPOT_METER,		/* �X�|�b�g���[�^�[�w */
	LINE_LAYER_NUM				/* ���C������ */
} LINE_LAYER_INDEX;
#define LINE_LAYER_BASE	LINE_LAYER_GUIDELINE /* ��ꃌ�C�� */

extern LINE_ERR Line_InitLayer(void);
extern LINE_ERR Line_RequestLayer(GUI_OUTPUT_DEV output, LINE_LAYER_INDEX layerIndex, BOOL isDisp, LINE_DRAW_OBJECT *object);
extern void Line_ExecLayer(void);

#endif	/* __LINE_LAYER_H__ */
