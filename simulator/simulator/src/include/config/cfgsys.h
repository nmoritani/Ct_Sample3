/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  cfgsys.h
 * @brief %jp{ITRON�V�X�e���̃R���t�B�M�����[�V�����p�w�b�_�t�@�C��}%en{ITRON system configuration heder file}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


/*
%jp{
  �{�t�@�C���ɂāAITRON�V�X�e���̃R���t�B�M�����[�V�������s���B
  �R���t�B�M�����[�V�����̌��ʂɂ��A��{�^�ȂǃA�v���P�[�V������
���p�����`���ω�����ׁA�{�t�@�C���̕ύX��̓J�[�l���݂̂Ȃ炸�A
itron.h �� kernel.h �𗘗p���Ă���A�A�v���P�[�V���������܂߂�
�V�X�e���S�̂����r���h����K�v������B
  �܂��A�{�t�@�C���̓Z���u������̑O�����ɂ��g������z�肵�Ă���̂ŁA
C����\��(�Ⴆ��typedef�Ȃ�)�͂��̒��ɂ͋L�ڂ����A�}�N����`�Ȃǂ�
�v���v���Z�b�T�f�B���N�e�B�u�݂̂��L�ڂ��鎖�Ƃ���B
}
*/



#ifndef _KERNEL__config__cfgsys_h__
#define _KERNEL__config__cfgsys_h__


/* %jp{�������̃A���C���T�C�Y}%jp{Memory alignment size} */
#define _KERNEL_CFG_MEM_ALIGN			(-1)				/**< �������̃A���C���T�C�Y(-1�̎��f�t�H���g�l)}%en{Memory alignment size (-1:default)} */


/* %jp{ITRON�d�l���ʃf�[�^�^}%en{ITRON General Data Type} */
#define _KERNEL_CFG_TBIT_INT			(-1)				/**< %jp{INT     �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in INT     (-1:default)} */
#define _KERNEL_CFG_TBIT_UINT			(-1)				/**< %jp{UINT    �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in UINT    (-1:default)} */
#define _KERNEL_CFG_TBIT_BOOL			(-1)				/**< %jp{BOOL    �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in BOOL    (-1:default)} */
#define _KERNEL_CFG_TBIT_FN				(-1)				/**< %jp{FN      �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in FN      (-1:default)} */
#define _KERNEL_CFG_TBIT_ER				(-1)				/**< %jp{ER      �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in ER      (-1:default)} */
#define _KERNEL_CFG_TBIT_ID				(-1)				/**< %jp{ID      �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in ID      (-1:default)} */
#define _KERNEL_CFG_TBIT_ATR			(-1)				/**< %jp{ATR     �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in ATR     (-1:default)} */
#define _KERNEL_CFG_TBIT_STAT			(-1)				/**< %jp{STAT    �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in STAT    (-1:default)} */
#define _KERNEL_CFG_TBIT_MODE			(-1)				/**< %jp{MODE    �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in MODE    (-1:default)} */
#define _KERNEL_CFG_TBIT_PRI			(-1)				/**< %jp{PRI     �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in PRI     (-1:default)} */
#define _KERNEL_CFG_TBIT_SIZE			(-1)				/**< %jp{SIZE    �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in SIZE    (-1:default)} */
#define _KERNEL_CFG_TBIT_TMO			(-1)				/**< %jp{TMO     �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in TMO     (-1:default)} */
#define _KERNEL_CFG_TBIT_RELTIM			(-1)				/**< %jp{RELTIM  �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in RELTIM  (-1:default)} */
#define _KERNEL_CFG_SYSTIM_STRUCT		FALSE				/**< %jp{SYSTIM�^���\���̂ɂ��邩�ǂ���} */
#define _KERNEL_CFG_TBIT_SYSTIM			32					/**< %jp{SYSTIM�^�̃r�b�g��} */
#define _KERNEL_CFG_VP_INT_PTR			FALSE				/**< %jp{VP_INT�^���|�C���^�^�ɂ��邩�ǂ���} */
#define _KERNEL_CFG_TBIT_VP_INT			(-1)				/**< %jp{VP_INT  �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in VP_INT  (-1:default)} */
#define _KERNEL_CFG_TBIT_ER_BOOL		(-1)				/**< %jp{ER_BOOL �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in ER_BOOL (-1:default)} */
#define _KERNEL_CFG_TBIT_ER_ID			(-1)				/**< %jp{ER_ID   �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in ER_ID   (-1:default)} */
#define _KERNEL_CFG_TBIT_ER_UINT		(-1)				/**< %jp{ER_UINT �̃r�b�g�� (-1�̎��f�t�H���g�l)}%en{Number of bits in ER_UINT (-1:default)} */

/* %jp{�J�[�l���̃f�[�^�^}%en{Kernel Data Type} */
#define _KERNEL_CFG_TBIT_TEXPTN			(-1)				/**< %jp{�^�X�N��O�v���̃r�b�g��(-1�̎��f�t�H���g�l)} */
#define _KERNEL_CFG_TBIT_FLGPTN			(-1)				/**< %jp{�C�x���g�t���O�̃r�b�g��(-1�̎��f�t�H���g�l)} */
#define _KERNEL_CFG_TBIT_RDVPTN			(-1)				/**< %jp{�����f�u�����̃r�b�g��(-1�̎��f�t�H���g�l)} */
#define _KERNEL_CFG_TBIT_RDVNO			(-1)
#define _KERNEL_CFG_TBIT_OVRTIM			(-1)
#define _KERNEL_CFG_TBIT_INHNO			(-1)
#define _KERNEL_CFG_TBIT_INTNO			(-1)
#define _KERNEL_CFG_TBIT_EXCNO			(-1)


/* %jp{�D��x�͈̔�}%en{Priority Range} */
#define _KERNEL_CFG_TMAX_TPRI			127					/**< %jp{�^�X�N�D��x�̍ő�l(-1�̎��f�t�H���g�l)}%en{Maximum task priority} */
#define _KERNEL_CFG_TMAX_MPRI			127					/**< %jp{���b�Z�[�W�D��x�̍ő�l(-1�̎��f�t�H���g�l)}%en{Maximum message priority} */

/* %jp{�L���[�C���O�^�l�X�g�񐔂̍ő�l}%en{Maximum Nesting/Queueing Count} */
#define _KERNEL_CFG_TMAX_ACTCNT			127					/**< %jp{�^�X�N�N���v���L���[�C���O���̍ő�l(-1�̎��f�t�H���g�l)} */
#define _KERNEL_CFG_TMAX_WUPCNT			127					/**< %jp{�^�X�N�N���v���L���[�C���O���̍ő�l(-1�̎��f�t�H���g�l)} */
#define _KERNEL_CFG_TMAX_SUSCNT			127					/**< %jp{�^�X�N�����҂��v���l�X�g���̍ő�l(-1�̎��f�t�H���g�l)} */

/* %jp{�r�b�g�p�^�[���̃r�b�g��} %en{Number of Bits in Bitpatterns}*/
#define _KERNEL_CFG_TEX_TBIT_TEXPTN		(-1)				/**< %jp{�^�X�N��O�v���̃r�b�g��(-1�̎��f�t�H���g�l)} */
#define _KERNEL_CFG_FLG_TBIT_FLGPTN		(-1)				/**< %jp{�C�x���g�t���O�̃r�b�g��(-1�̎��f�t�H���g�l)} */
#define _KERNEL_CFG_RDV_TBIT_RDVPTN		(-1)				/**< %jp{�����f�u�����̃r�b�g��(-1�̎��f�t�H���g�l)} */

/* %jp{�Z�}�t�H�̍ő�l}%en{Maximum value of the maximum definable semaphore resource count} */
#define _KERNEL_CFG_TMAX_MAXSEM			(-1)				/**< %jp{�Z�}�t�H�̍ő�l}%en{Maximum value of the maximum definable semaphore resource count} */


/* %jp{T_RTSK�̕ύX}%en{T_RTSK�̕ύX} */
#define _KERNEL_CFG_RTSK_TSKATR			TRUE				/**< %jp{T_RTSK�� tskatr ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_CFG_RTSK_EXINF			TRUE				/**< %jp{T_RTSK�� exinf ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_CFG_RTSK_TASK			TRUE				/**< %jp{T_RTSK�� task ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_CFG_RTSK_ITSKPRI		TRUE				/**< %jp{T_RTSK�� itskpri ���܂߂邩(HOS�Ǝ��g���@�\)} */	
#define _KERNEL_CFG_RTSK_STKSZ			TRUE				/**< %jp{T_RTSK�� stksz ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_CFG_RTSK_STK			TRUE				/**< %jp{T_RTSK�� stk ���܂߂邩(HOS�Ǝ��g���@�\)} */


/* %jp{T_RTST�̍\��}%en{T_RTST} */
#define _KERNEL_CFG_RTST_TSKATR			FALSE				/**< %jp{T_RTST�� tskatr ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_CFG_RTST_EXINF			TRUE				/**< %jp{T_RTST�� exinf ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_CFG_RTST_TASK			FALSE				/**< %jp{T_RTST�� task ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_CFG_RTST_ITSKPRI		FALSE				/**< %jp{T_RTST�� itskpri ���܂߂邩(HOS�Ǝ��g���@�\)} */	
#define _KERNEL_CFG_RTST_STKSZ			FALSE				/**< %jp{T_RTST�� stksz ���܂߂邩(HOS�Ǝ��g���@�\)} */
#define _KERNEL_CFG_RTST_STK			FALSE				/**< %jp{T_RTST�� stk ���܂߂邩(HOS�Ǝ��g���@�\)} */



#endif	/* _KERNEL__config__cfgsys_h__ */



/* end of file */
