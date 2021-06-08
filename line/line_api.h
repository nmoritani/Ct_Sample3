/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           interface of line block
 */
#ifndef __GUI_LINE_API_H__
#define __GUI_LINE_API_H__

#include "sys_type.h"

/* ��g�̐� */
#define GUI_FACE_FRAME_NUM	15

/* �F ID */
typedef enum _GUI_COLOR_ID_ {
	GUI_COLOR_ID_DELETE,	/* �F�Ȃ� (���S����) */
	GUI_COLOR_ID_WHITE,		/* �� */
	GUI_COLOR_ID_BLACK,		/* �� */
	GUI_COLOR_ID_GRAY,		/* �D */
	GUI_COLOR_ID_BLUE,		/* �� */
	GUI_COLOR_ID_CYAN,		/* ���F */
	GUI_COLOR_ID_GREEN,		/* �� */
	GUI_COLOR_ID_YELLOW,	/* �� */
	GUI_COLOR_ID_ORANGE,	/* �� */
	GUI_COLOR_ID_RED,		/* �� */
	GUI_COLOR_ID_PINK,		/* ���F */
	GUI_COLOR_ID_PURPLE,	/* �� */
	GUI_COLOR_ID_MARKER_WHITE,	/* �}�[�J�[�F (��) ���P�x�����t���̂��ߑ��Ƌ�� */
	GUI_COLOR_ID_MARKER_BLACK,	/* �}�[�J�[�F (��) ���P�x�����t���̂��ߑ��Ƌ�� */
	GUI_COLOR_ID_MARKER_RED,	/* �}�[�J�[�F (��) ���P�x�����t���̂��ߑ��Ƌ�� */
	GUI_COLOR_ID_MARKER_GREEN,	/* �}�[�J�[�F (��) ���P�x�����t���̂��ߑ��Ƌ�� */
	GUI_COLOR_ID_MARKER_BLUE,	/* �}�[�J�[�F (��) ���P�x�����t���̂��ߑ��Ƌ�� */
	GUI_COLOR_ID_MARKER_YELLOW,	/* �}�[�J�[�F (��) ���P�x�����t���̂��ߑ��Ƌ�� */
	GUI_COLOR_ID_MAX			/* ����ȍ~�͒ǉ��֎~ */
} GUI_COLOR_ID;

/* �o�͐�w�� */
typedef enum _GUI_OUTPUT_DEV_ {
	GUI_OUTPUT_LCD,				/* LCD */
	GUI_OUTPUT_HDMI,			/* HDMI */
	GUI_OUTPUT_SDI,				/* SDI */
} GUI_OUTPUT_DEV;

/* �g�̌`��w�� */
typedef enum _GUI_FACE_FRAME_STYLE_ {
	GUI_FRAME_STYLE_FOURSQUARE,	/* �l�p�g */
	GUI_FRAME_STYLE_BRACKET,	/* �ꊇ�� + �\�� */
	GUI_FRAME_STYLE_BRACKET_OK,	/* �ꊇ�� (��) */
	GUI_FRAME_STYLE_BRACKET_NG,	/* �ꊇ�� (��) */
} GUI_FACE_FRAME_STYLE;

/* �Z�[�t�e�B�]�[���`��w�� */
typedef enum _GUI_SAFETY_ZONE_TYPE_ {
	GUI_SAFETY_ZONE_TYPE_OFF,	 /* OFF */
	GUI_SAFETY_ZONE_TYPE_BOX,	 /* �{�b�N�X */
	GUI_SAFETY_ZONE_TYPE_CORNER, /* �R�[�i�[�g */
} GUI_SAFETY_ZONE_TYPE;

/* �t���[���}�[�J�[��p��� */
typedef enum _GUI_FRAME_MARKER_ANGLE_ {
	GUI_FRAME_MARKER_OFF,		/* �\���I�t */
	GUI_FRAME_MARKER_1_33,		/* 1.33:1 */
	GUI_FRAME_MARKER_1_44,		/* 1.44:1 */
	GUI_FRAME_MARKER_1_56,		/* 1.56:1 */
	GUI_FRAME_MARKER_1_78,		/* 1.78:1 */
	GUI_FRAME_MARKER_1_85,		/* 1.85:1 */
	GUI_FRAME_MARKER_2_00,		/* 2.00:1 */
	GUI_FRAME_MARKER_2_201,		/* 2.201:1 */
	GUI_FRAME_MARKER_2_35,		/* 2.35:1 */
	GUI_FRAME_MARKER_2_39,		/* 2.39:1 */
	GUI_FRAME_MARKER_NUM		/* ��`�̌� */
} GUI_FRAME_MARKER_ANGLE;

/* �K�C�h���C����� */
typedef enum _GUI_GUIDELINE_TYPE_ {
	GUI_GUIDELINE_TYPE_NONE,	   /* �K�C�h���C��/FA OFF */
	GUI_GUIDELINE_TYPE_HORIZONTAL, /* �����K�C�h���C�� (������) */
	GUI_GUIDELINE_TYPE_LATTICE1,   /* �i�q1 �K�C�h���C�� (3 ����) */
	GUI_GUIDELINE_TYPE_LATTICE2,   /* �i�q2 �K�C�h���C�� (����) */
	GUI_GUIDELINE_TYPE_FA,		   /* �t�H�[�J�X�A�V�X�g�ݒ� */
} GUI_GUIDELINE_TYPE;

/* �Z���^�[�}�[�J�[�`���� */
typedef enum GUI_CENTER_MARKER_TYPE {
	GUI_CENTER_MARKER_OFF,		  /* �\���I�t */
	GUI_CENTER_MARKER_LARGE,	  /* + (��) */
	GUI_CENTER_MARKER_LARGE_HOLE, /* ���� (��) */
	GUI_CENTER_MARKER_SMALL,	  /* + (��) */
	GUI_CENTER_MARKER_SMALL_HOLE, /* ���� (��) */
	GUI_CENTER_MARKER_NUM
} GUI_CENTER_MARKER_TYPE;

/* �X�|�b�g���[�^�[�}�[�J�[�`���� */
typedef enum GUI_SPOT_METER_MARKER_TYPE {
	GUI_SPOT_METER_MARKER_OFF,	  /* �\���I�t */
	GUI_SPOT_METER_MARKER_SMALL,  /* S */
	GUI_SPOT_METER_MARKER_MIDDLE, /* M */
	GUI_SPOT_METER_MARKER_LARGE,  /* L */
	GUI_SPOT_METER_MARKER_NUM
} GUI_SPOT_METER_MARKER_TYPE;

/* ��g/�ǂ������g/�G���A�g�ʒu�w�� */
typedef struct _GUI_FACE_FRAME_INFO_ {
	UH hpos;					/* ���������̕\���J�n */
	UH vpos;					/* ���������̕\���J�n�ʒu */
	UH width;					/* ���������̑傫�� */
	UH height;					/* ���������̑傫�� */
	UH vsize;					/* �c���̑��� */
	UH hsize;					/* �����̑��� */
	UH waku_size;				/* ���̑��� */
	UH kagi_hsize; /* �ꊇ�ʂ̐��������̑傫���A�\���̐����������� 1/2 */
	UH kagi_vsize; /* �ꊇ�ʂ̐��������̑傫���A�\���̐����������� 1/2 */
} GUI_FACE_FRAME_INFO;

/* �Z�[�t�e�B�]�[���`���� */
typedef struct _GUI_SAFETY_ZONE_INFO_ {
	GUI_SAFETY_ZONE_TYPE type;	/* �g�̎�� */
	float size;					/* �T�C�Y (1.0 �` 100.0%) */
	GUI_COLOR_ID color;			/* �F�w�� */
} GUI_SAFETY_ZONE_INFO;

/* �t���[���}�[�J�[�`���� */
typedef struct _GUI_FRAME_MARKER_INFO_ {
	GUI_FRAME_MARKER_ANGLE angle; /* ��p�w�� */
	GUI_COLOR_ID color;			  /* �F�w�� */
} GUI_FRAME_MARKER_INFO;

/* �Z���^�[�}�[�J�[�`���� */
typedef struct GUI_CENTER_MARKER_INFO {
	GUI_CENTER_MARKER_TYPE type;
	GUI_COLOR_ID color;
} GUI_CENTER_MARKER_INFO;

/* �X�|�b�g���[�^�[�}�[�J�[�`���� */
typedef struct GUI_SPOT_METER_MARKER_INFO {
	GUI_SPOT_METER_MARKER_TYPE type;
	GUI_COLOR_ID color;
} GUI_SPOT_METER_MARKER_INFO;

/* �o�͉f���̗L����p */
typedef struct _GUI_VIDEO_FORMAT_ {
	UH width;					/* �� */
	UH height;					/* ���� */
} GUI_VIDEO_FORMAT;

/* AF RANGE */
typedef struct _GUI_AF_RANGE_INFO_ {
	UH x;					/* ���������̕\���J�n */
	UH y;					/* ���������̕\���J�n�ʒu */
	UH w;					/* ���������̑傫�� */
	UH h;					/* ���������̑傫�� */
    UH bold;
} GUI_AF_RANGE_INFO;

/* �A�v������ API */
extern void GUI_DrawAfRange(GUI_OUTPUT_DEV output, GUI_AF_RANGE_INFO layoutInfo, BOOL isDisp);
extern void GUI_DrawFaceFrame(GUI_OUTPUT_DEV output, UW faceFrameId, GUI_FACE_FRAME_INFO layoutInfo, GUI_FACE_FRAME_STYLE styleId, BOOL isDisp, GUI_COLOR_ID color);
extern void GUI_DrawSafetyZone(GUI_OUTPUT_DEV output, GUI_SAFETY_ZONE_INFO *info);
extern void GUI_DrawFrameMarker(GUI_OUTPUT_DEV output, GUI_FRAME_MARKER_INFO *info);
extern void GUI_DrawCenterMarker(GUI_OUTPUT_DEV output, GUI_CENTER_MARKER_INFO *info);
extern void GUI_DrawSpotMeterMarker(GUI_OUTPUT_DEV output, GUI_SPOT_METER_MARKER_INFO *info);
extern void GUI_SetMarkerLuminance(GUI_OUTPUT_DEV output, UB luminance);

/* AVC ���� API */
extern void GUI_SetEffectiveOutputVideoFormat(GUI_OUTPUT_DEV output, GUI_VIDEO_FORMAT *signal, GUI_VIDEO_FORMAT *image);
extern void GUI_GuideSetMode(GUI_OUTPUT_DEV output, GUI_GUIDELINE_TYPE type);
extern void GUI_SetFAColor(GUI_COLOR_ID color);

/* GUI ���� API */
extern void GUI_LineInit(void);

#endif  /* __GUI_LINE_API_H__ */
