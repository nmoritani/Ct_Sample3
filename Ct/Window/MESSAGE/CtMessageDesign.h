/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/**
* @file   CtMessageDesign.h
* @brief  MESSAGEデザイン
*
* @author  -      : 
* @author  -      : 
* @author  -      : 
* @author  -      : 
*
* @date   20XX.0X.0X [XX.XX.XX]  新規作成
*
* <b> 変更履歴 </b> <!-- 作成  バージョン  担当者  変更理由 -->
*
*/

#ifndef __CtMessageDesign_H__
#define __CtMessageDesign_H__

/*******************************************************************************
    インクルードファイル
*******************************************************************************/


/*******************************************************************************
  定数の定義
*******************************************************************************/
/* WINDOW */
#define MESSAGE_WINDOW_SIZE_X	0
#define MESSAGE_WINDOW_SIZE_Y	0
#define MESSAGE_WINDOW_SIZE_W	960
#define MESSAGE_WINDOW_SIZE_H	540

#define MESSAGE_DEFAULT_MARGIN	14

/* タイトル */
#define MESSAGE_TITLE_FONT		CtFontSet(FontTypeNormal, CtColor::White)
#define MESSAGE_TITLE_BG_COLOR  0x666974FF
#define MESSAGE_TITLE_AREA		44
#define MESSAGE_TITLE_AREA_W	MESSAGE_WINDOW_SIZE_W - (MESSAGE_DEFAULT_MARGIN*2)

/* メインエリア */
#define MESSAGE_MAIN_AREA_BG_COLOR	0x262626ff
#define MESSAGE_MAIN_AREA		MESSAGE_WINDOW_SIZE_H - MESSAGE_TITLE_AREA

/* テキスト */
#define MESSAGE_TEXT_FONT		CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White)
#define MESSAGE_TEXT_AREA		MESSAGE_WINDOW_SIZE_H - (MESSAGE_DEFAULT_MARGIN*2)

/* コントロール */
#define MESSAGE_CONTORL_AREA	92
#define MESSAGE_BUTTON_W		78
#define MESSAGE_BUTTON_H		66

/* テロップ領域 */
#define MESSAGE_TELOP_AREA_UP_SPACE			4
#define MESSAGE_TELOP_AREA_H				5
#define MESSAGE_TELOP_AREA_W		MESSAGE_WINDOW_SIZE_W - (MESSAGE_DEFAULT_MARGIN*2)
#define MESSAGE_TELOP_AREA_BOTTOM_SPACE		18
#define MESSAGE_TELOP_BASE_COLOR	0x00000037
#define MESSAGE_TELOP_AREA_STR				(MESSAGE_WINDOW_SIZE_H / (MESSAGE_TELOP_AREA_UP_SPACE+MESSAGE_TELOP_AREA_H+MESSAGE_TELOP_AREA_BOTTOM_SPACE)) * MESSAGE_TELOP_AREA_H

#endif /* __CtMessageDesign_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
