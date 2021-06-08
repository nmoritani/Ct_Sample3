/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/**
* @file   CtMessageDesign.h
* @brief  MESSAGE�f�U�C��
*
* @author  -      : 
* @author  -      : 
* @author  -      : 
* @author  -      : 
*
* @date   20XX.0X.0X [XX.XX.XX]  �V�K�쐬
*
* <b> �ύX���� </b> <!-- �쐬  �o�[�W����  �S����  �ύX���R -->
*
*/

#ifndef __CtMessageDesign_H__
#define __CtMessageDesign_H__

/*******************************************************************************
    �C���N���[�h�t�@�C��
*******************************************************************************/


/*******************************************************************************
  �萔�̒�`
*******************************************************************************/
/* WINDOW */
#define MESSAGE_WINDOW_SIZE_X	0
#define MESSAGE_WINDOW_SIZE_Y	0
#define MESSAGE_WINDOW_SIZE_W	960
#define MESSAGE_WINDOW_SIZE_H	540

#define MESSAGE_DEFAULT_MARGIN	14

/* �^�C�g�� */
#define MESSAGE_TITLE_FONT		CtFontSet(FontTypeNormal, CtColor::White)
#define MESSAGE_TITLE_BG_COLOR  0x666974FF
#define MESSAGE_TITLE_AREA		44
#define MESSAGE_TITLE_AREA_W	MESSAGE_WINDOW_SIZE_W - (MESSAGE_DEFAULT_MARGIN*2)

/* ���C���G���A */
#define MESSAGE_MAIN_AREA_BG_COLOR	0x262626ff
#define MESSAGE_MAIN_AREA		MESSAGE_WINDOW_SIZE_H - MESSAGE_TITLE_AREA

/* �e�L�X�g */
#define MESSAGE_TEXT_FONT		CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White)
#define MESSAGE_TEXT_AREA		MESSAGE_WINDOW_SIZE_H - (MESSAGE_DEFAULT_MARGIN*2)

/* �R���g���[�� */
#define MESSAGE_CONTORL_AREA	92
#define MESSAGE_BUTTON_W		78
#define MESSAGE_BUTTON_H		66

/* �e���b�v�̈� */
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
