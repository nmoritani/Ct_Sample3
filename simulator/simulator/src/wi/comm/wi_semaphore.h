/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_semaphore.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�Z�}�t�H).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_SEMAPHORE_H__
#define	__WI_SEMAPHORE_H__

#include "wi_common.h"
#include "wi_task.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * �\���̒�`.
 *
 ****************************************************************************/
/*!
 *
 * @brief �Z�}�t�H��I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute;		//!< �Z�}�t�H����.
	INT			SemCnt;			//!< ���݂̃Z�}�t�H��J�E���g.
	INT			MaxCnt;			//!< �Z�}�t�H��J�E���g�̍ő吔.
	INT			WaitCnt;		//!< �Z�}�t�H�l���҂���
	VP			ExtInfo;		//!< �g�����.
	WIHDR		*WaitQue;		//!< �Z�}�t�H�l���҂��̑҂��s��̃|�C���^.
} WISEMOBJ;

/*!
 *
 * @brief �Z�}�t�H�̏�ԎQ�Ɨp�\����.
 *
 */
typedef struct {
	INT			WaitId;			//!< �Z�}�t�H�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT			SemCnt;			//!< ���݂̃Z�}�t�H�J�E���g�l.
	VP			ExtInfo;		//!< �g�����.
} WISEMSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitSemaphore( void );
void	wi_QuitSemaphore( void );
ER		wi_CreateSemaphore( INT id, const WISEMOBJ *obj );
ER		wi_DeleteSemaphore( INT id );
ER		wi_SignalSemaphore( INT id );
ER		wi_WaitSemaphore( INT id, TMO tmout );
ER		wi_RefarenceSemaphore( INT id, WISEMSTAT *sts );
void	wi_AllReleaseSemaphore( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_SEMAPHORE_H__
/* End of file */
