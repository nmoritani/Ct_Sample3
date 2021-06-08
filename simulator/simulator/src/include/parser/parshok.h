/** 
 *  Hyper Operating System V4 Advance
 *
 * @file  parshok.h
 * @brief %jp{�J�[�l���t�b�N�̃R���t�B�M�����[�V�������}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */



#ifndef _KERNEL__parser__parshok_h__
#define _KERNEL__parser__parshok_h__


#ifdef _KERNEL_HOK_TSK
#define _KERNEL_SPT_HOK_TSKSWI		TRUE						/**< �^�X�N�X�C�b�`�̃t�b�N */
#else
#define _KERNEL_SPT_HOK_TSKSWI		_KERNEL_CFG_HOK_TSKSWI		/**< �^�X�N�X�C�b�`�̃t�b�N */
#endif

#ifdef _KERNEL_HOK_INH
#define _KERNEL_SPT_HOK_INHSTA		TRUE						/**< �����݃n���h���J�n�̃t�b�N */
#define _KERNEL_SPT_HOK_INHEND		TRUE						/**< �����݃n���h���I���̃t�b�N */
#else
#define _KERNEL_SPT_HOK_INHSTA		_KERNEL_CFG_HOK_INHSTA		/**< �����݃n���h���J�n�̃t�b�N */
#define _KERNEL_SPT_HOK_INHEND		_KERNEL_CFG_HOK_INHEND		/**< �����݃n���h���I���̃t�b�N */
#endif

#ifdef _KERNEL_HOK_ISR
#define _KERNEL_SPT_HOK_ISRSTA		TRUE						/**< �����݃T�[�r�X���[�`���J�n�̃t�b�N */
#define _KERNEL_SPT_HOK_ISREND		TRUE						/**< �����݃T�[�r�X���[�`���I���̃t�b�N */
#else
#define _KERNEL_SPT_HOK_ISRSTA		_KERNEL_CFG_HOK_ISRSTA		/**< �����݃T�[�r�X���[�`���J�n�̃t�b�N */
#define _KERNEL_SPT_HOK_ISREND		_KERNEL_CFG_HOK_ISREND		/**< �����݃T�[�r�X���[�`���I���̃t�b�N */
#endif


#endif	/* _KERNEL__parser__parshok_h__ */


/* end of file */
