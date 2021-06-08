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
	/* 描画順 (表示優先順位が低いものから並べる) */
	LINE_LAYER_GUIDELINE,		/* ガイドライン層 */
	LINE_LAYER_SAFETY_ZONE,		/* セーフティゾーン層 */
	LINE_LAYER_FACE,			/* 顔枠層 */
    LINE_LAYER_AF_RANGE,        /* AF RANGE層 */
	LINE_LAYER_FOLLOW,			/* 追っかけ層 */
	LINE_LAYER_SPOT_METER,		/* スポットメーター層 */
	LINE_LAYER_NUM				/* レイヤ総数 */
} LINE_LAYER_INDEX;
#define LINE_LAYER_BASE	LINE_LAYER_GUIDELINE /* 基底レイヤ */

extern LINE_ERR Line_InitLayer(void);
extern LINE_ERR Line_RequestLayer(GUI_OUTPUT_DEV output, LINE_LAYER_INDEX layerIndex, BOOL isDisp, LINE_DRAW_OBJECT *object);
extern void Line_ExecLayer(void);

#endif	/* __LINE_LAYER_H__ */
