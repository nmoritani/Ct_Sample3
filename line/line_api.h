/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           interface of line block
 */
#ifndef __GUI_LINE_API_H__
#define __GUI_LINE_API_H__

#include "sys_type.h"

/* 顔枠の数 */
#define GUI_FACE_FRAME_NUM	15

/* 色 ID */
typedef enum _GUI_COLOR_ID_ {
	GUI_COLOR_ID_DELETE,	/* 色なし (完全透過) */
	GUI_COLOR_ID_WHITE,		/* 白 */
	GUI_COLOR_ID_BLACK,		/* 黒 */
	GUI_COLOR_ID_GRAY,		/* 灰 */
	GUI_COLOR_ID_BLUE,		/* 青 */
	GUI_COLOR_ID_CYAN,		/* 水色 */
	GUI_COLOR_ID_GREEN,		/* 緑 */
	GUI_COLOR_ID_YELLOW,	/* 黄 */
	GUI_COLOR_ID_ORANGE,	/* 橙 */
	GUI_COLOR_ID_RED,		/* 赤 */
	GUI_COLOR_ID_PINK,		/* 桃色 */
	GUI_COLOR_ID_PURPLE,	/* 紫 */
	GUI_COLOR_ID_MARKER_WHITE,	/* マーカー色 (白) ※輝度調整付きのため他と区別 */
	GUI_COLOR_ID_MARKER_BLACK,	/* マーカー色 (黒) ※輝度調整付きのため他と区別 */
	GUI_COLOR_ID_MARKER_RED,	/* マーカー色 (赤) ※輝度調整付きのため他と区別 */
	GUI_COLOR_ID_MARKER_GREEN,	/* マーカー色 (緑) ※輝度調整付きのため他と区別 */
	GUI_COLOR_ID_MARKER_BLUE,	/* マーカー色 (青) ※輝度調整付きのため他と区別 */
	GUI_COLOR_ID_MARKER_YELLOW,	/* マーカー色 (黄) ※輝度調整付きのため他と区別 */
	GUI_COLOR_ID_MAX			/* これ以降は追加禁止 */
} GUI_COLOR_ID;

/* 出力先指定 */
typedef enum _GUI_OUTPUT_DEV_ {
	GUI_OUTPUT_LCD,				/* LCD */
	GUI_OUTPUT_HDMI,			/* HDMI */
	GUI_OUTPUT_SDI,				/* SDI */
} GUI_OUTPUT_DEV;

/* 枠の形状指定 */
typedef enum _GUI_FACE_FRAME_STYLE_ {
	GUI_FRAME_STYLE_FOURSQUARE,	/* 四角枠 */
	GUI_FRAME_STYLE_BRACKET,	/* 鉤括弧 + 十字 */
	GUI_FRAME_STYLE_BRACKET_OK,	/* 鉤括弧 (白) */
	GUI_FRAME_STYLE_BRACKET_NG,	/* 鉤括弧 (赤) */
} GUI_FACE_FRAME_STYLE;

/* セーフティゾーン形状指定 */
typedef enum _GUI_SAFETY_ZONE_TYPE_ {
	GUI_SAFETY_ZONE_TYPE_OFF,	 /* OFF */
	GUI_SAFETY_ZONE_TYPE_BOX,	 /* ボックス */
	GUI_SAFETY_ZONE_TYPE_CORNER, /* コーナー枠 */
} GUI_SAFETY_ZONE_TYPE;

/* フレームマーカー画角種別 */
typedef enum _GUI_FRAME_MARKER_ANGLE_ {
	GUI_FRAME_MARKER_OFF,		/* 表示オフ */
	GUI_FRAME_MARKER_1_33,		/* 1.33:1 */
	GUI_FRAME_MARKER_1_44,		/* 1.44:1 */
	GUI_FRAME_MARKER_1_56,		/* 1.56:1 */
	GUI_FRAME_MARKER_1_78,		/* 1.78:1 */
	GUI_FRAME_MARKER_1_85,		/* 1.85:1 */
	GUI_FRAME_MARKER_2_00,		/* 2.00:1 */
	GUI_FRAME_MARKER_2_201,		/* 2.201:1 */
	GUI_FRAME_MARKER_2_35,		/* 2.35:1 */
	GUI_FRAME_MARKER_2_39,		/* 2.39:1 */
	GUI_FRAME_MARKER_NUM		/* 定義の個数 */
} GUI_FRAME_MARKER_ANGLE;

/* ガイドライン種別 */
typedef enum _GUI_GUIDELINE_TYPE_ {
	GUI_GUIDELINE_TYPE_NONE,	   /* ガイドライン/FA OFF */
	GUI_GUIDELINE_TYPE_HORIZONTAL, /* 水平ガイドライン (水平線) */
	GUI_GUIDELINE_TYPE_LATTICE1,   /* 格子1 ガイドライン (3 分割) */
	GUI_GUIDELINE_TYPE_LATTICE2,   /* 格子2 ガイドライン (方眼) */
	GUI_GUIDELINE_TYPE_FA,		   /* フォーカスアシスト設定 */
} GUI_GUIDELINE_TYPE;

/* センターマーカー描画情報 */
typedef enum GUI_CENTER_MARKER_TYPE {
	GUI_CENTER_MARKER_OFF,		  /* 表示オフ */
	GUI_CENTER_MARKER_LARGE,	  /* + (大) */
	GUI_CENTER_MARKER_LARGE_HOLE, /* 中空き (大) */
	GUI_CENTER_MARKER_SMALL,	  /* + (小) */
	GUI_CENTER_MARKER_SMALL_HOLE, /* 中空き (小) */
	GUI_CENTER_MARKER_NUM
} GUI_CENTER_MARKER_TYPE;

/* スポットメーターマーカー描画情報 */
typedef enum GUI_SPOT_METER_MARKER_TYPE {
	GUI_SPOT_METER_MARKER_OFF,	  /* 表示オフ */
	GUI_SPOT_METER_MARKER_SMALL,  /* S */
	GUI_SPOT_METER_MARKER_MIDDLE, /* M */
	GUI_SPOT_METER_MARKER_LARGE,  /* L */
	GUI_SPOT_METER_MARKER_NUM
} GUI_SPOT_METER_MARKER_TYPE;

/* 顔枠/追っかけ枠/エリア枠位置指定 */
typedef struct _GUI_FACE_FRAME_INFO_ {
	UH hpos;					/* 水平方向の表示開始 */
	UH vpos;					/* 垂直方向の表示開始位置 */
	UH width;					/* 水平方向の大きさ */
	UH height;					/* 垂直方向の大きさ */
	UH vsize;					/* 縦線の太さ */
	UH hsize;					/* 横線の太さ */
	UH waku_size;				/* 縁の太さ */
	UH kagi_hsize; /* 鉤括弧の水平方向の大きさ、十字の水平線長さの 1/2 */
	UH kagi_vsize; /* 鉤括弧の垂直方向の大きさ、十字の垂直線長さの 1/2 */
} GUI_FACE_FRAME_INFO;

/* セーフティゾーン描画情報 */
typedef struct _GUI_SAFETY_ZONE_INFO_ {
	GUI_SAFETY_ZONE_TYPE type;	/* 枠の種類 */
	float size;					/* サイズ (1.0 ～ 100.0%) */
	GUI_COLOR_ID color;			/* 色指定 */
} GUI_SAFETY_ZONE_INFO;

/* フレームマーカー描画情報 */
typedef struct _GUI_FRAME_MARKER_INFO_ {
	GUI_FRAME_MARKER_ANGLE angle; /* 画角指定 */
	GUI_COLOR_ID color;			  /* 色指定 */
} GUI_FRAME_MARKER_INFO;

/* センターマーカー描画情報 */
typedef struct GUI_CENTER_MARKER_INFO {
	GUI_CENTER_MARKER_TYPE type;
	GUI_COLOR_ID color;
} GUI_CENTER_MARKER_INFO;

/* スポットメーターマーカー描画情報 */
typedef struct GUI_SPOT_METER_MARKER_INFO {
	GUI_SPOT_METER_MARKER_TYPE type;
	GUI_COLOR_ID color;
} GUI_SPOT_METER_MARKER_INFO;

/* 出力映像の有効画角 */
typedef struct _GUI_VIDEO_FORMAT_ {
	UH width;					/* 幅 */
	UH height;					/* 高さ */
} GUI_VIDEO_FORMAT;

/* AF RANGE */
typedef struct _GUI_AF_RANGE_INFO_ {
	UH x;					/* 水平方向の表示開始 */
	UH y;					/* 垂直方向の表示開始位置 */
	UH w;					/* 水平方向の大きさ */
	UH h;					/* 垂直方向の大きさ */
    UH bold;
} GUI_AF_RANGE_INFO;

/* アプリ向け API */
extern void GUI_DrawAfRange(GUI_OUTPUT_DEV output, GUI_AF_RANGE_INFO layoutInfo, BOOL isDisp);
extern void GUI_DrawFaceFrame(GUI_OUTPUT_DEV output, UW faceFrameId, GUI_FACE_FRAME_INFO layoutInfo, GUI_FACE_FRAME_STYLE styleId, BOOL isDisp, GUI_COLOR_ID color);
extern void GUI_DrawSafetyZone(GUI_OUTPUT_DEV output, GUI_SAFETY_ZONE_INFO *info);
extern void GUI_DrawFrameMarker(GUI_OUTPUT_DEV output, GUI_FRAME_MARKER_INFO *info);
extern void GUI_DrawCenterMarker(GUI_OUTPUT_DEV output, GUI_CENTER_MARKER_INFO *info);
extern void GUI_DrawSpotMeterMarker(GUI_OUTPUT_DEV output, GUI_SPOT_METER_MARKER_INFO *info);
extern void GUI_SetMarkerLuminance(GUI_OUTPUT_DEV output, UB luminance);

/* AVC 向け API */
extern void GUI_SetEffectiveOutputVideoFormat(GUI_OUTPUT_DEV output, GUI_VIDEO_FORMAT *signal, GUI_VIDEO_FORMAT *image);
extern void GUI_GuideSetMode(GUI_OUTPUT_DEV output, GUI_GUIDELINE_TYPE type);
extern void GUI_SetFAColor(GUI_COLOR_ID color);

/* GUI 向け API */
extern void GUI_LineInit(void);

#endif  /* __GUI_LINE_API_H__ */
