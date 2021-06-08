/* $Id: language_id.h,v 1.2 2005/02/28 08:44:35 hosoi Exp $ */

#ifndef __LANGUAGE_ID_H__
#define __LANGUAGE_ID_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup language_id
 *  @{ */
/** �t�H���g�^�C�v */
typedef enum _language_id
  {
    LANGUAGE_ID_JA,             /**< [0]    ���{��                  */
    LANGUAGE_ID_EN,             /**< [1]    �p��            PAL     */
    LANGUAGE_ID_UE,             /**< [2]    �p��            NTSC    */
    LANGUAGE_ID_GE,             /**< [3]    �ƌ�                    */
    LANGUAGE_ID_FR,             /**< [4]    ����            PAL     */
//    LANGUAGE_ID_CA,             /**< [5]    ����            NTSC    */
    LANGUAGE_ID_IT,             /**< [6]    �Ɍ�                    */
    LANGUAGE_ID_SP,             /**< [7]    ����            PAL     */
//    LANGUAGE_ID_US,             /**< [8]    ����            NTSC    */
    LANGUAGE_ID_DU,             /**< [9]    ����                    */
    LANGUAGE_ID_SW,             /**< [10]   �X�E�F�[�f����          */
    LANGUAGE_ID_PO,             /**< [11]   �|�[�����h��            */
    LANGUAGE_ID_RU,             /**< [12]   �I��                    */
//    LANGUAGE_ID_AR,             /**< [13]   �A���r�A��              */
//    LANGUAGE_ID_PE,             /**< [14]   �y���V����              */
//    LANGUAGE_ID_KO,             /**< [15]   �؍���                  */
    LANGUAGE_ID_SC,             /**< [16]   �ȑ̌�                  */
    LANGUAGE_ID_TC,             /**< [17]   �ɑ̌�          PAL     */
    LANGUAGE_ID_TW,             /**< [18]   �ɑ̌�          NTSC    */
    LANGUAGE_ID_CZ,             /**< [19]   �`�F�R��                */
//    LANGUAGE_ID_TH,             /**< [20]   �^�C��                  */
//    LANGUAGE_ID_HI,             /**< [21]   �q���f�B��              */
    LANGUAGE_ID_JE,             /**< [22]   �p��(���{����)  NTSC    */
    LANGUAGE_ID_TU,             /**< [23]   �g���R��                */
    LANGUAGE_ID_HU,             /**< [24]   �n���K���[��            */
//    LANGUAGE_ID_PT,             /**< [25]   �|���g�K����            */
    LANGUAGE_ID_MAX,             /* ����MAX                          */
	LANGUAGE_ID_NONE = 0xFFFF	/* ����w��Ȃ�(����) */
  } LANGUAGE_ID;
/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __LANGUAGE_ID_H__ */
