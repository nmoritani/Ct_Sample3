/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  cfghok.h
 * @brief %jp{�J�[�l���t�b�N�̃R���t�B�M�����[�V�����p�w�b�_�t�@�C��}
 *
 * Copyright (C) 1998-2008 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


/*
%jp{
  �{�t�@�C���ɂāA�J�[�l���t�b�N�@�\�̃R���t�B�M�����[�V�������s���B
  
  �܂��A�{�t�@�C���̓Z���u������̑O�����ɂ��g������z�肵�Ă���̂ŁA
C����\��(�Ⴆ��typedef�Ȃ�)�͂��̒��ɂ͋L�ڂ����A�}�N����`�Ȃǂ�
�v���v���Z�b�T�f�B���N�e�B�u�݂̂��L�ڂ��鎖�Ƃ���B}
*/



#ifndef _KERNEL__config__cfghok_h__
#define _KERNEL__config__cfghok_h__


/* �ȉ��\�� */
#define _KERNEL_CFG_HOK_SVCCAL		FALSE		/**< �T�[�r�X�R�[���̌Ăяo�� */
#define _KERNEL_CFG_HOK_SVCRET		FALSE		/**< �T�[�r�X�R�[���̃��^�[�� */

#define _KERNEL_CFG_HOK_TSKSWI		FALSE		/**< �^�X�N�X�C�b�`�̃t�b�N */

#define _KERNEL_CFG_HOK_INHSTA		FALSE		/**< �����݃n���h���J�n�̃t�b�N */
#define _KERNEL_CFG_HOK_INHEND		FALSE		/**< �����݃n���h���I���̃t�b�N */

#define _KERNEL_CFG_HOK_ISRSTA		FALSE		/**< �����݃T�[�r�X���[�`���J�n�̃t�b�N */
#define _KERNEL_CFG_HOK_ISREND		FALSE		/**< �����݃T�[�r�X���[�`���I���̃t�b�N */

#define _KERNEL_CFG_HOK_MTXPRI		FALSE		/**< �~���[�e�b�N�X�̗D��x�ω��̃t�b�N */


#endif	/* _KERNEL__config__cfghok_h__ */


/* end of file */
