/******************************************************************************
 * Copyright(C) by 2009-2017 Panasonic Corporation.
 ******************************************************************************/

/**
* @file   CtThumbDesign.h
* @brief  THUMB�f�U�C��
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

#ifndef __CtThumbDesign_H__
#define __CtThumbDesign_H__

/*******************************************************************************
    �C���N���[�h�t�@�C��
*******************************************************************************/


/*******************************************************************************
  �萔�̒�`
*******************************************************************************/
/* WINDOW */
#define THUMB_WINDOW_SIZE_X	0
#define THUMB_WINDOW_SIZE_Y	0
#define THUMB_WINDOW_SIZE_W	960
#define THUMB_WINDOW_SIZE_H	640

/* ���уT�C�Y */
#define THUMB_UPPER_V		40
#define THUMB_SEPARATOR_V	2
#define THUMB_LOWER_V	THUMB_WINDOW_SIZE_H - THUMB_UPPER_V - THUMB_SEPARATOR_V

/* ��i */
#define THUMB_SPACE		14
#define THUMB_SLOT_SEL	495 - THUMB_SPACE
#define THUMB_ERR_ICON  32
#define THUMB_MOV		80
#define THUMB_AVCHD		80

/* Scroll�o�[ */
#define THUMB_SCROLL_H	8

/* �T���l�C���\���� */
#define THUMB_COL	3
#define THUMB_ROW	3
#define THUMB_ALL	THUMB_COL * THUMB_ROW

/* �T���l�C���T�C�Y */
#define THUMB_SIZE_W 218
#define THUMB_SIZE_H 155

#endif /* __CtThumbDesign_H__ */
/**********************************************************************************
 * Copyright(C) by 2009-2014 Panasonic Corporation.
**********************************************************************************/
