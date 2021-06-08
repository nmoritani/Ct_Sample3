/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           draw function of line block
 */
#ifndef __LINE_DRAW_H__
#define __LINE_DRAW_H__

#include "sys_type.h"
#include "line_api.h"
#include "line_ctrl.h"

#define LINE_LINE_NUM_MAX		5  /* �`�悷��� MAX */

/* �I�u�W�F�N�g����ID */
typedef enum _LINE_OBJECT_ID_ {
	LINE_OBJ_FOLLOW_FRAME,	/* �ǂ������g */
	LINE_OBJ_AREA_FRAME,	/* �G���A�g */
	LINE_OBJ_GUIDELINE,		/* �K�C�h���C��/FA�g */
    LINE_OBJ_AF_RANGE,		/* AF AREA(RANGE)�g */
	LINE_OBJ_SAFETY_ZONE,	/* �Z�[�t�e�B�]�[�� */
	LINE_OBJ_FRAME_MARKER,	/* �t���[���}�[�J�[ */
	LINE_OBJ_CENTER_MARKER,	/* �Z���^�[�}�[�J�[ */
	LINE_OBJ_SPOT_METER_MARKER,	/* �X�|�b�g���[�^�[�}�[�J�[ */
	LINE_OBJ_FACE_FRAME00,	/* ��g 0 */
	LINE_OBJ_FACE_FRAME01,	/* ��g 1 */
	LINE_OBJ_FACE_FRAME02,	/* ��g 2 */
	LINE_OBJ_FACE_FRAME03,	/* ��g 3 */
	LINE_OBJ_FACE_FRAME04,	/* ��g 4 */
	LINE_OBJ_FACE_FRAME05,	/* ��g 5 */
	LINE_OBJ_FACE_FRAME06,	/* ��g 6 */
	LINE_OBJ_FACE_FRAME07,	/* ��g 7 */
	LINE_OBJ_FACE_FRAME08,	/* ��g 8 */
	LINE_OBJ_FACE_FRAME09,	/* ��g 9 */
	LINE_OBJ_FACE_FRAME10,	/* ��g 10 */
	LINE_OBJ_FACE_FRAME11,	/* ��g 11 */
	LINE_OBJ_FACE_FRAME12,	/* ��g 12 */
	LINE_OBJ_FACE_FRAME13,	/* ��g 13 */
	LINE_OBJ_FACE_FRAME14,	/* ��g 14 */
} LINE_OBJECT_ID;
#define LINE_OBJ_FACE_FRAME_MIN	LINE_OBJ_FACE_FRAME00
#define LINE_OBJ_FACE_FRAME_MAX	(LINE_OBJ_FACE_FRAME00 + GUI_FACE_FRAME_NUM - 1)

typedef struct _LINE_POS_ {
	UH x;
	UH y;
} LINE_POS;

typedef struct _LINE_AREA_ {
	UH w;
	UH h;
} LINE_AREA;

typedef struct _LINE_GRID_LINE_ {
	UH start;					/* �J�n�ʒu */
	UH bold;					/* ���� */
	UH interval;				/* ���̐��܂ł̊Ԋu */
} LINE_GRID_LINE;

typedef struct _LINE_EDGE_ {
	UH width;					/* ���� */
	GUI_COLOR_ID color;			/* �F(�p���b�gID) */
} LINE_EDGE;

typedef struct _LINE_CROSS_LINE_ {
	LINE_POS start;		/* �J�n�ʒu */
	LINE_AREA area;		/* �̈� */
	UH blank;					/* ���̊Ԋu */
} LINE_CROSS_LINE;

typedef struct _LINE_LINE_ {
	LINE_POS start;		/* �J�n�ʒu */
	LINE_POS end;			/* �I���ʒu */
	UH bold;					/* ���� */
	GUI_COLOR_ID color;			/* �F(�p���b�gID) */
} LINE_LINE;

typedef struct _LINE_DRAW_LINES_ {
	UB num;										 /* �`�搔 */
	LINE_LINE line[LINE_LINE_NUM_MAX]; /* �e����� */
} LINE_DRAW_LINES;

typedef struct _LINE_DRAW_GRID_ {
	LINE_POS start;		  /* �i�q�̈�J�n�ʒu */
	LINE_AREA area;		  /* �i�q�̈�̕��A���� */
	LINE_GRID_LINE horizon;  /* ��������� */
	LINE_GRID_LINE vertical; /* ��������� */
	GUI_COLOR_ID color;			  /* �F(�p���b�gID) */
} LINE_DRAW_GRID;

typedef struct _LINE_DRAW_BOX_ {
	LINE_POS start;		/* �J�n�ʒu */
	LINE_AREA area;		/* ���A���� */
	UH bold;					/* ���� */
	GUI_COLOR_ID color;			/* �F */
	LINE_EDGE edge;		/* ����� */
} LINE_DRAW_BOX;

typedef struct _LINE_DRAW_BRACKET_ {
	LINE_POS start;		/* �J�n�ʒu */
	LINE_AREA area;		/* �`��̈�̕��A���� */
	LINE_AREA hook;		/* ��̕��A���� */
	UH bold;					/* ���� */
	GUI_COLOR_ID color;			/* �F */
	LINE_EDGE edge;		/* ����� */
} LINE_DRAW_BRACKET;

typedef struct _LINE_DRAW_CROSS_ {
	LINE_CROSS_LINE horizon;  /* ��������� */
	LINE_CROSS_LINE vertical; /* ��������� */
	GUI_COLOR_ID color;			   /* �F (�����E��������) */
	LINE_EDGE edge;		   /* ����� (�����E��������) */
} LINE_DRAW_CROSS;

typedef struct _LINE_DRAW_SIGHT_ {
	LINE_DRAW_BRACKET bracket;
	LINE_DRAW_CROSS cross;
} LINE_DRAW_SIGHT;

typedef enum _LINE_DRAW_TYPE_ {
	LINE_DRAW_TYPE_LINES,	 /* �� */
	LINE_DRAW_TYPE_GRID,	 /* �i�q */
	LINE_DRAW_TYPE_BOX,	 /* �l�p */
	LINE_DRAW_TYPE_BRACKET, /* �ꊇ�� */
	LINE_DRAW_TYPE_CROSS,	 /* �\���� */
	LINE_DRAW_TYPE_SIGHT	 /* �ꊇ��+�\���� */
} LINE_DRAW_TYPE;

typedef struct _LINE_DRAW_OBJECT_ {
	LINE_OBJECT_ID id;
	LINE_DRAW_TYPE drawType;
	LINE_MEMORY *memory;
	union {
		LINE_DRAW_LINES lines;
		LINE_DRAW_GRID grid;
		LINE_DRAW_BOX box;
		LINE_DRAW_BRACKET bracket;
		LINE_DRAW_CROSS cross;
		LINE_DRAW_SIGHT sight;
	} param;
} LINE_DRAW_OBJECT;

/* API */
extern LINE_ERR Line_ClearMemory(const LINE_MEMORY *memory);
extern LINE_DRAW_OBJECT* Line_CreateDrawObj(LINE_OBJECT_ID objectId);
extern LINE_ERR Line_DeleteDrawObj(const LINE_DRAW_OBJECT *object);
extern LINE_ERR Line_Draw(const LINE_DRAW_OBJECT *object);
extern LINE_ERR Line_Erase(LINE_DRAW_OBJECT *object);
extern BOOL Line_IsOverlapping(const LINE_DRAW_OBJECT *source, const LINE_DRAW_OBJECT *dest);

#endif	/* __LINE_DRAW_H__ */
