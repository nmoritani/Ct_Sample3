/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/**
* @file   CtViewDesign.h
* @brief  VIEW�f�U�C��
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

#ifndef __CtViewDesign_H__
#define __CtViewDesign_H__

/*******************************************************************************
    �C���N���[�h�t�@�C��
*******************************************************************************/


/*******************************************************************************
  �萔�̒�`
*******************************************************************************/
/* WINDOW */
#define VIEW_WINDOW_SIZE_X	0
#define VIEW_WINDOW_SIZE_Y	0
#define VIEW_WINDOW_SIZE_W	960
#define VIEW_WINDOW_SIZE_H	640

/* ���уT�C�Y */
#define VIEW_OSD_V		50
#define VIEW_THROUGH_V	VIEW_WINDOW_SIZE_H - (VIEW_OSD_V * 2)

/* Expand */
#define VIEW_EXPAND_MARKER_SIZE_W	120
#define VIEW_EXPAND_MARKER_SIZE_H	72
#define VIEW_EXPAND_MARKER_POS_X	4
#define VIEW_EXPAND_MARKER_POS_Y	VIEW_WINDOW_SIZE_H - VIEW_EXPAND_MARKER_SIZE_H - 4 - 20

/* LevelGauge */
#define VIEW_LEVELGAUGE_WIDE_W		12
#define VIEW_LEVELGAUGE_SHORT_W		8
#define VIEW_LEVELGAUGE_MARGIN_W	((VIEW_LEVELGAUGE_WIDE_W-VIEW_LEVELGAUGE_SHORT_W)/2)


#endif /* __CtViewDesign_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
