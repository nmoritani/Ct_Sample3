/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           draw function of line block
 */
#ifndef __LINE_DRAW_H__
#define __LINE_DRAW_H__

#include "sys_type.h"
#include "line_api.h"
#include "line_ctrl.h"

#define LINE_LINE_NUM_MAX		5  /* 描画する線 MAX */

/* オブジェクト識別ID */
typedef enum _LINE_OBJECT_ID_ {
	LINE_OBJ_FOLLOW_FRAME,	/* 追っかけ枠 */
	LINE_OBJ_AREA_FRAME,	/* エリア枠 */
	LINE_OBJ_GUIDELINE,		/* ガイドライン/FA枠 */
    LINE_OBJ_AF_RANGE,		/* AF AREA(RANGE)枠 */
	LINE_OBJ_SAFETY_ZONE,	/* セーフティゾーン */
	LINE_OBJ_FRAME_MARKER,	/* フレームマーカー */
	LINE_OBJ_CENTER_MARKER,	/* センターマーカー */
	LINE_OBJ_SPOT_METER_MARKER,	/* スポットメーターマーカー */
	LINE_OBJ_FACE_FRAME00,	/* 顔枠 0 */
	LINE_OBJ_FACE_FRAME01,	/* 顔枠 1 */
	LINE_OBJ_FACE_FRAME02,	/* 顔枠 2 */
	LINE_OBJ_FACE_FRAME03,	/* 顔枠 3 */
	LINE_OBJ_FACE_FRAME04,	/* 顔枠 4 */
	LINE_OBJ_FACE_FRAME05,	/* 顔枠 5 */
	LINE_OBJ_FACE_FRAME06,	/* 顔枠 6 */
	LINE_OBJ_FACE_FRAME07,	/* 顔枠 7 */
	LINE_OBJ_FACE_FRAME08,	/* 顔枠 8 */
	LINE_OBJ_FACE_FRAME09,	/* 顔枠 9 */
	LINE_OBJ_FACE_FRAME10,	/* 顔枠 10 */
	LINE_OBJ_FACE_FRAME11,	/* 顔枠 11 */
	LINE_OBJ_FACE_FRAME12,	/* 顔枠 12 */
	LINE_OBJ_FACE_FRAME13,	/* 顔枠 13 */
	LINE_OBJ_FACE_FRAME14,	/* 顔枠 14 */
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
	UH start;					/* 開始位置 */
	UH bold;					/* 太さ */
	UH interval;				/* 次の線までの間隔 */
} LINE_GRID_LINE;

typedef struct _LINE_EDGE_ {
	UH width;					/* 縁幅 */
	GUI_COLOR_ID color;			/* 色(パレットID) */
} LINE_EDGE;

typedef struct _LINE_CROSS_LINE_ {
	LINE_POS start;		/* 開始位置 */
	LINE_AREA area;		/* 領域 */
	UH blank;					/* 線の間隔 */
} LINE_CROSS_LINE;

typedef struct _LINE_LINE_ {
	LINE_POS start;		/* 開始位置 */
	LINE_POS end;			/* 終了位置 */
	UH bold;					/* 太さ */
	GUI_COLOR_ID color;			/* 色(パレットID) */
} LINE_LINE;

typedef struct _LINE_DRAW_LINES_ {
	UB num;										 /* 描画数 */
	LINE_LINE line[LINE_LINE_NUM_MAX]; /* 各線情報 */
} LINE_DRAW_LINES;

typedef struct _LINE_DRAW_GRID_ {
	LINE_POS start;		  /* 格子領域開始位置 */
	LINE_AREA area;		  /* 格子領域の幅、高さ */
	LINE_GRID_LINE horizon;  /* 水平線情報 */
	LINE_GRID_LINE vertical; /* 垂直線情報 */
	GUI_COLOR_ID color;			  /* 色(パレットID) */
} LINE_DRAW_GRID;

typedef struct _LINE_DRAW_BOX_ {
	LINE_POS start;		/* 開始位置 */
	LINE_AREA area;		/* 幅、高さ */
	UH bold;					/* 太さ */
	GUI_COLOR_ID color;			/* 色 */
	LINE_EDGE edge;		/* 縁情報 */
} LINE_DRAW_BOX;

typedef struct _LINE_DRAW_BRACKET_ {
	LINE_POS start;		/* 開始位置 */
	LINE_AREA area;		/* 描画領域の幅、高さ */
	LINE_AREA hook;		/* 鉤の幅、高さ */
	UH bold;					/* 太さ */
	GUI_COLOR_ID color;			/* 色 */
	LINE_EDGE edge;		/* 縁情報 */
} LINE_DRAW_BRACKET;

typedef struct _LINE_DRAW_CROSS_ {
	LINE_CROSS_LINE horizon;  /* 水平線情報 */
	LINE_CROSS_LINE vertical; /* 垂直線情報 */
	GUI_COLOR_ID color;			   /* 色 (水平・垂直共通) */
	LINE_EDGE edge;		   /* 縁情報 (水平・垂直共通) */
} LINE_DRAW_CROSS;

typedef struct _LINE_DRAW_SIGHT_ {
	LINE_DRAW_BRACKET bracket;
	LINE_DRAW_CROSS cross;
} LINE_DRAW_SIGHT;

typedef enum _LINE_DRAW_TYPE_ {
	LINE_DRAW_TYPE_LINES,	 /* 線 */
	LINE_DRAW_TYPE_GRID,	 /* 格子 */
	LINE_DRAW_TYPE_BOX,	 /* 四角 */
	LINE_DRAW_TYPE_BRACKET, /* 鉤括弧 */
	LINE_DRAW_TYPE_CROSS,	 /* 十字架 */
	LINE_DRAW_TYPE_SIGHT	 /* 鉤括弧+十字架 */
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
