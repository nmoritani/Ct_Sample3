/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           control module of line block
 */
#ifndef __LINE_CTRL_H__
#define __LINE_CTRL_H__

#include "line_api.h"

typedef enum LINE_ERR {
	LINE_OK,					/* ���� */
	LINE_ERR_BADARG,			/* �s������ */
	LINE_ERR_NOMEM,				/* ���\�[�X�s�� */
	LINE_ERR_HARD,				/* �n�[�h�E�F�A�G���[ */
	LINE_ERR_NOT_SUPPORTED,		/* ��T�|�[�g */
	LINE_ERR_UNEXPECTED,		/* ���̑��G���[ */
} LINE_ERR;

typedef struct _LINE_MEMORY_ {
	UH lineOffset;				/* �������� (���C���I�t�Z�b�g) */
	UH height;					/* ���������� */
	UB *addr;					/* �x�[�X�A�h���X */
	struct {					/* �������ݎ��̃I�t�Z�b�g */
		UH x;
		UH y;
	} drawOffset;
} LINE_MEMORY;

extern LINE_ERR Line_InitCtrl(void);
extern LINE_ERR Line_RequestChangeResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image);
extern LINE_ERR Line_ChangeResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image);
extern LINE_ERR Line_SetColorFocusAssist(GUI_OUTPUT_DEV output, GUI_COLOR_ID color);
extern LINE_ERR Line_DrawAfRange(GUI_OUTPUT_DEV output, GUI_AF_RANGE_INFO *layoutInfo, BOOL isDisp);
extern LINE_ERR Line_DrawFaceFrame(GUI_OUTPUT_DEV output, UW faceFrameId, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color);
extern LINE_ERR Line_DrawFollowFrame(GUI_OUTPUT_DEV output, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color);
extern LINE_ERR Line_DrawAreaFrame(GUI_OUTPUT_DEV output, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color);
extern LINE_ERR Line_DrawGuideLine(GUI_OUTPUT_DEV output, GUI_GUIDELINE_TYPE guideType);
extern LINE_ERR Line_DrawFocusAssist(GUI_OUTPUT_DEV output, BOOL isDisp);
extern LINE_ERR Line_DrawSafetyzone(GUI_OUTPUT_DEV output, GUI_SAFETY_ZONE_TYPE type, float size, GUI_COLOR_ID color);
extern LINE_ERR Line_DrawFrameMarker(GUI_OUTPUT_DEV output, GUI_FRAME_MARKER_ANGLE angle, GUI_COLOR_ID color);
extern LINE_ERR Line_DrawCenterMarker(GUI_OUTPUT_DEV output, GUI_CENTER_MARKER_TYPE type, GUI_COLOR_ID color);
extern LINE_ERR Line_DrawSpotMeterMarker(GUI_OUTPUT_DEV output, GUI_SPOT_METER_MARKER_TYPE type, GUI_COLOR_ID color);

#endif	/* __LINE_CTRL_H__ */
