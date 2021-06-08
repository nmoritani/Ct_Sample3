/* $Id: language_id.h,v 1.2 2005/02/28 08:44:35 hosoi Exp $ */

#ifndef __LANGUAGE_ID_H__
#define __LANGUAGE_ID_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup language_id
 *  @{ */
/** フォントタイプ */
typedef enum _language_id
  {
    LANGUAGE_ID_JA,             /**< [0]    日本語                  */
    LANGUAGE_ID_EN,             /**< [1]    英語            PAL     */
    LANGUAGE_ID_UE,             /**< [2]    英語            NTSC    */
    LANGUAGE_ID_GE,             /**< [3]    独語                    */
    LANGUAGE_ID_FR,             /**< [4]    仏語            PAL     */
//    LANGUAGE_ID_CA,             /**< [5]    仏語            NTSC    */
    LANGUAGE_ID_IT,             /**< [6]    伊語                    */
    LANGUAGE_ID_SP,             /**< [7]    西語            PAL     */
//    LANGUAGE_ID_US,             /**< [8]    西語            NTSC    */
    LANGUAGE_ID_DU,             /**< [9]    蘭語                    */
    LANGUAGE_ID_SW,             /**< [10]   スウェーデン語          */
    LANGUAGE_ID_PO,             /**< [11]   ポーランド語            */
    LANGUAGE_ID_RU,             /**< [12]   露語                    */
//    LANGUAGE_ID_AR,             /**< [13]   アラビア語              */
//    LANGUAGE_ID_PE,             /**< [14]   ペルシャ語              */
//    LANGUAGE_ID_KO,             /**< [15]   韓国語                  */
    LANGUAGE_ID_SC,             /**< [16]   簡体語                  */
    LANGUAGE_ID_TC,             /**< [17]   繁体語          PAL     */
    LANGUAGE_ID_TW,             /**< [18]   繁体語          NTSC    */
    LANGUAGE_ID_CZ,             /**< [19]   チェコ語                */
//    LANGUAGE_ID_TH,             /**< [20]   タイ語                  */
//    LANGUAGE_ID_HI,             /**< [21]   ヒンディ語              */
    LANGUAGE_ID_JE,             /**< [22]   英語(日本向け)  NTSC    */
    LANGUAGE_ID_TU,             /**< [23]   トルコ語                */
    LANGUAGE_ID_HU,             /**< [24]   ハンガリー語            */
//    LANGUAGE_ID_PT,             /**< [25]   ポルトガル語            */
    LANGUAGE_ID_MAX,             /* 言語MAX                          */
	LANGUAGE_ID_NONE = 0xFFFF	/* 言語指定なし(自動) */
  } LANGUAGE_ID;
/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LANGUAGE_ID_H__ */
