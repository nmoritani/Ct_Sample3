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
   @brief   LINE ブロックの初期化
   @param[in] なし
   @retval なし
*/
void GUI_LineInit(void)
{
	Line_InitTask();			/* 最初に呼ぶこと!! */
	Line_InitLayer();
	Line_InitColor();
	Line_InitCtrl();
}

/**
   @brief   指定枠の描画/消去を行う
   @retval なし
*/
void GUI_DrawAfRange(GUI_OUTPUT_DEV output, GUI_AF_RANGE_INFO layoutInfo, BOOL isDisp){
    Line_DrawAfRange(output, &layoutInfo, isDisp);
}

/**
   @brief   指定枠の描画/消去を行う
   @param[in] output      : 出力先指定
   @param[in] faceFrameId : 顔枠識別ID 0-14 ※顔枠以外は無効
   @param[in] layoutInfo  : 枠の表示位置情報 (960×540 ベース)
   @param[in] styleId     : 枠の形状指定
   @param[in] isDisp      : 表示/消去指定
   @param[in] color       : 色 (カラーパレットID)
   @retval なし
*/
void GUI_DrawFaceFrame(GUI_OUTPUT_DEV output, UW faceFrameId, GUI_FACE_FRAME_INFO layoutInfo, GUI_FACE_FRAME_STYLE styleId, BOOL isDisp, GUI_COLOR_ID color)
{
	switch (styleId) {
	case GUI_FRAME_STYLE_FOURSQUARE: /* 四角枠 */
		Line_DrawFaceFrame(output, faceFrameId, &layoutInfo, isDisp, color);
		break;
	case GUI_FRAME_STYLE_BRACKET:	 /* 鉤括弧 + 十字 */
		Line_DrawAreaFrame(output, &layoutInfo, isDisp, color);
		break;
	case GUI_FRAME_STYLE_BRACKET_OK: /* 鉤括弧 (白) */
	case GUI_FRAME_STYLE_BRACKET_NG: /* 鉤括弧 (赤) */
		Line_DrawFollowFrame(output, &layoutInfo, isDisp, color);
		break;
	default:
		break;
	}
}

/**
   @brief   セーフティゾーンの描画/消去を行う
   @param[in] output      : 出力先指定
   @param[in] info        : セーフティゾーンマーカの描画情報
   @retval なし
*/
void GUI_DrawSafetyZone(GUI_OUTPUT_DEV output, GUI_SAFETY_ZONE_INFO *info)
{
	if (info == NULL) {
		return;
	}
	Line_DrawSafetyzone(output, info->type, info->size, info->color);
}

/**
   @brief   フレームマーカーの描画/消去を行う
   @param[in] output      : 出力先指定
   @param[in] info        : フレームマーカーの描画情報
   @retval なし
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
   @brief   センターマーカーの描画/消去を行う
   @param[in] output      : 出力先指定
   @param[in] info        : センターマーカーの描画情報
   @retval なし
*/
void GUI_DrawCenterMarker(GUI_OUTPUT_DEV output, GUI_CENTER_MARKER_INFO *info)
{
	if (info == NULL) {
		return;
	}
	Line_DrawCenterMarker(output, info->type, info->color);
}

/**
   @brief   センターマーカーの描画/消去を行う
   @param[in] output      : 出力先指定
   @param[in] info        : センターマーカーの描画情報
   @retval なし
*/
void GUI_DrawSpotMeterMarker(GUI_OUTPUT_DEV output, GUI_SPOT_METER_MARKER_INFO *info)
{
	if (info == NULL) {
		return;
	}
	Line_DrawSpotMeterMarker(output, info->type, info->color);
}

/**
   @brief   各出力毎の有効映像画角を通知 ※映像 ON/OFF、及び画角変化が発生した場合に通知して下さい。
   @param[in] output      : 出力先指定
   @param[in] *signale    : 出力信号の有効画角
   @param[in] *image      : 出力映像の有効画角
   @retval なし
*/
void GUI_SetEffectiveOutputVideoFormat(GUI_OUTPUT_DEV output, GUI_VIDEO_FORMAT *signal, GUI_VIDEO_FORMAT *image)
{
	if (image == NULL) {		/* 映像がない場合 (サムネイル表示等であり得る) */
		image = signal;			/* 信号画角をそのまま使う */
	}
	Line_RequestChangeResolution(output, signal, image); /* 信号がない場合は無信号扱いなのでそのまま渡す */
}

/**
   @brief   ガイドラインまたはフォーカスアシスト枠の描画/消去を行う
   @param[in] output      : 出力先指定
   @param[in] type        : ガイドライン種別
   @retval なし
*/
void GUI_GuideSetMode(GUI_OUTPUT_DEV output, GUI_GUIDELINE_TYPE type)
{
	switch (type) {
	case GUI_GUIDELINE_TYPE_NONE:		  /* ガイドライン/FA OFF */
		Line_DrawGuideLine(output, type); /* FA もこちらで消える設計 */
		break;
	case GUI_GUIDELINE_TYPE_HORIZONTAL: /* 水平ガイドライン (水平線) */
	case GUI_GUIDELINE_TYPE_LATTICE1: /* 格子1 ガイドライン (3 分割) */
	case GUI_GUIDELINE_TYPE_LATTICE2: /* 格子2 ガイドライン (方眼) */
		Line_DrawGuideLine(output, type);
		break;
	case GUI_GUIDELINE_TYPE_FA:	/* フォーカスアシスト設定 */
		Line_DrawFocusAssist(output, FALSE);
		break;
	default:
		break;
	}
}

/**
   @brief   フォーカスアシスト枠の色設定を行う
   @param[in] color       : カラーパレットID
   @retval なし
*/
void GUI_SetFAColor(GUI_COLOR_ID color)
{
	Line_SetColorFocusAssist(GUI_OUTPUT_LCD, color);
	Line_SetColorFocusAssist(GUI_OUTPUT_HDMI, color);
	Line_SetColorFocusAssist(GUI_OUTPUT_SDI, color);
}

/**
   @brief   MARKER 線の輝度を設定する
   @param[in] output      : 出力先指定
   @param[in] luminance   : 輝度% (0～100)
   @retval なし
*/
void GUI_SetMarkerLuminance(GUI_OUTPUT_DEV output, UB luminance)
{
	if (luminance > 100) {
		return;
	}

	Line_SetMarkerLuminance(output, luminance);
}
