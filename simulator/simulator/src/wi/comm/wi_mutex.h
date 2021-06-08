/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_mutex.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�~���[�e�b�N�X).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_MUTEX_H__
#define	__WI_MUTEX_H__

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
 * @brief �~���[�e�b�N�X��I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute;		//!< �~���[�e�b�N�X����.
	PRI			CeilPri;		//!< �~���[�e�b�N�X�̏���D��x.
	INT			LockId;			//!< �~���[�e�b�N�X�����b�N���Ă���^�X�N��ID�ԍ�.
	WIHDR		*WaitQue;		//!< �Z�}�t�H�l���҂��̑҂��s��̃|�C���^.
} WIMTXOBJ;

/*!
 *
 * @brief �~���[�e�b�N�X�̏�ԎQ�Ɨp�\����.
 *
 */
typedef struct {
	INT			LockId;			//!< �~���[�e�b�N�X�����b�N���Ă���^�X�N��ID�ԍ�.
	INT			WaitId;			//!< �~���[�e�b�N�X�҂��s��̐擪�̃^�X�NID�ԍ�.
} WIMTXSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitMutex( void );
void	wi_QuitMutex( void );
ER		wi_CreateMutex( INT id, const WIMTXOBJ *obj );
ER		wi_DeleteMutex( INT id );
ER		wi_LockMutex( INT id, TMO tmout );
ER		wi_UnlockMutex( INT id );
ER		wi_RefarenceMutex( INT id, WIMTXSTAT *sts );
void	wi_AllReleaseMutex( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_MUTEX_H__
/* End of file */
