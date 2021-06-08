/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           interface of line block
 */
#include "line_api.h"
#include "line_ctrl.h"
#include "line_color.h"
#include "line_task.h"
#include "line_layer.h"

/**
   @brief   LINE �u���b�N�̏�����
   @param[in] �Ȃ�
   @retval �Ȃ�
*/
void GUI_LineInit(void)
{
	Line_InitTask();			/* �ŏ��ɌĂԂ���!! */
	Line_InitLayer();
	Line_InitColor();
	Line_InitCtrl();
}

/**
   @brief   �w��g�̕`��/�������s��
   @retval �Ȃ�
*/
void GUI_DrawAfRange(GUI_OUTPUT_DEV output, GUI_AF_RANGE_INFO layoutInfo, BOOL isDisp){
    Line_DrawAfRange(output, &layoutInfo, isDisp);
}

/**
   @brief   �w��g�̕`��/�������s��
   @param[in] output      : �o�͐�w��
   @param[in] faceFrameId : ��g����ID 0-14 ����g�ȊO�͖���
   @param[in] layoutInfo  : �g�̕\���ʒu��� (960�~540 �x�[�X)
   @param[in] styleId     : �g�̌`��w��
   @param[in] isDisp      : �\��/�����w��
   @param[in] color       : �F (�J���[�p���b�gID)
   @retval �Ȃ�
*/
void GUI_DrawFaceFrame(GUI_OUTPUT_DEV output, UW faceFrameId, GUI_FACE_FRAME_INFO layoutInfo, GUI_FACE_FRAME_STYLE styleId, BOOL isDisp, GUI_COLOR_ID color)
{
	switch (styleId) {
	case GUI_FRAME_STYLE_FOURSQUARE: /* �l�p�g */
		Line_DrawFaceFrame(output, faceFrameId, &layoutInfo, isDisp, color);
		break;
	case GUI_FRAME_STYLE_BRACKET:	 /* �ꊇ�� + �\�� */
		Line_DrawAreaFrame(output, &layoutInfo, isDisp, color);
		break;
	case GUI_FRAME_STYLE_BRACKET_OK: /* �ꊇ�� (��) */
	case GUI_FRAME_STYLE_BRACKET_NG: /* �ꊇ�� (��) */
		Line_DrawFollowFrame(output, &layoutInfo, isDisp, color);
		break;
	default:
		break;
	}
}

/**
   @brief   �Z�[�t�e�B�]�[���̕`��/�������s��
   @param[in] output      : �o�͐�w��
   @param[in] info        : �Z�[�t�e�B�]�[���}�[�J�̕`����
   @retval �Ȃ�
*/
void GUI_DrawSafetyZone(GUI_OUTPUT_DEV output, GUI_SAFETY_ZONE_INFO *info)
{
	if (info == NULL) {
		return;
	}
	Line_DrawSafetyzone(output, info->type, info->size, info->color);
}

/**
   @brief   �t���[���}�[�J�[�̕`��/�������s��
   @param[in] output      : �o�͐�w��
   @param[in] info        : �t���[���}�[�J�[�̕`����
   @retval �Ȃ�
*/
void GUI_DrawFrameMarker(GUI_OUTPUT_DEV output, GUI_FRAME_MARKER_INFO *info)
{
	if (info == NULL) {
		return;
	}
	if (info->angle >= GUI_FRAME_MARKER_NUM) {
		return;
	}
	Line_DrawFrameMarker(output, info->angle, info->color);
}

/**
   @brief   �Z���^�[�}�[�J�[�̕`��/�������s��
   @param[in] output      : �o�͐�w��
   @param[in] info        : �Z���^�[�}�[�J�[�̕`����
   @retval �Ȃ�
*/
void GUI_DrawCenterMarker(GUI_OUTPUT_DEV output, GUI_CENTER_MARKER_INFO *info)
{
	if (info == NULL) {
		return;
	}
	Line_DrawCenterMarker(output, info->type, info->color);
}

/**
   @brief   �Z���^�[�}�[�J�[�̕`��/�������s��
   @param[in] output      : �o�͐�w��
   @param[in] info        : �Z���^�[�}�[�J�[�̕`����
   @retval �Ȃ�
*/
void GUI_DrawSpotMeterMarker(GUI_OUTPUT_DEV output, GUI_SPOT_METER_MARKER_INFO *info)
{
	if (info == NULL) {
		return;
	}
	Line_DrawSpotMeterMarker(output, info->type, info->color);
}

/**
   @brief   �e�o�͖��̗L���f����p��ʒm ���f�� ON/OFF�A�y�щ�p�ω������������ꍇ�ɒʒm���ĉ������B
   @param[in] output      : �o�͐�w��
   @param[in] *signale    : �o�͐M���̗L����p
   @param[in] *image      : �o�͉f���̗L����p
   @retval �Ȃ�
*/
void GUI_SetEffectiveOutputVideoFormat(GUI_OUTPUT_DEV output, GUI_VIDEO_FORMAT *signal, GUI_VIDEO_FORMAT *image)
{
	if (image == NULL) {		/* �f�����Ȃ��ꍇ (�T���l�C���\�����ł��蓾��) */
		image = signal;			/* �M����p�����̂܂܎g�� */
	}
	Line_RequestChangeResolution(output, signal, image); /* �M�����Ȃ��ꍇ�͖��M�������Ȃ̂ł��̂܂ܓn�� */
}

/**
   @brief   �K�C�h���C���܂��̓t�H�[�J�X�A�V�X�g�g�̕`��/�������s��
   @param[in] output      : �o�͐�w��
   @param[in] type        : �K�C�h���C�����
   @retval �Ȃ�
*/
void GUI_GuideSetMode(GUI_OUTPUT_DEV output, GUI_GUIDELINE_TYPE type)
{
	switch (type) {
	case GUI_GUIDELINE_TYPE_NONE:		  /* �K�C�h���C��/FA OFF */
		Line_DrawGuideLine(output, type); /* FA ��������ŏ�����݌v */
		break;
	case GUI_GUIDELINE_TYPE_HORIZONTAL: /* �����K�C�h���C�� (������) */
	case GUI_GUIDELINE_TYPE_LATTICE1: /* �i�q1 �K�C�h���C�� (3 ����) */
	case GUI_GUIDELINE_TYPE_LATTICE2: /* �i�q2 �K�C�h���C�� (����) */
		Line_DrawGuideLine(output, type);
		break;
	case GUI_GUIDELINE_TYPE_FA:	/* �t�H�[�J�X�A�V�X�g�ݒ� */
		Line_DrawFocusAssist(output, FALSE);
		break;
	default:
		break;
	}
}

/**
   @brief   �t�H�[�J�X�A�V�X�g�g�̐F�ݒ���s��
   @param[in] color       : �J���[�p���b�gID
   @retval �Ȃ�
*/
void GUI_SetFAColor(GUI_COLOR_ID color)
{
	Line_SetColorFocusAssist(GUI_OUTPUT_LCD, color);
	Line_SetColorFocusAssist(GUI_OUTPUT_HDMI, color);
	Line_SetColorFocusAssist(GUI_OUTPUT_SDI, color);
}

/**
   @brief   MARKER ���̋P�x��ݒ肷��
   @param[in] output      : �o�͐�w��
   @param[in] luminance   : �P�x% (0�`100)
   @retval �Ȃ�
*/
void GUI_SetMarkerLuminance(GUI_OUTPUT_DEV output, UB luminance)
{
	if (luminance > 100) {
		return;
	}

	Line_SetMarkerLuminance(output, luminance);
}
