/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_fixed_mempool.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�Œ蒷�������v�[��).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_FIXED_MEMPOOL_H__
#define	__WI_FIXED_MEMPOOL_H__

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
 * @brief �Œ蒷�������v�[����I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute; 		//!< �Œ蒷�������v�[���̑���.
	INT			BlockCnt; 		//!< �Œ蒷�������v�[���S�̂̃u���b�N��.
	INT			BlockSize;		//!< �Œ蒷�������u���b�N�̃T�C�Y.
	BYTE*		MemBuf;			//!< �������o�b�t�@�̃|�C���^.
	WIHDR		*FreeQue;		//!< ���g�p�̌Œ蒷�������u���b�N������N�̃|�C���^.
	WIHDR		*UsedQue;		//!< �݂��o�����̌Œ蒷�������u���b�N������N�̃|�C���^.
	WIHDR		*WaitQue;		//!< �^�X�N�̑҂��s��̃|�C���^.
	VP			ExtInfo;		//!< �g�����.
} WIMPFOBJ;

/*!
 *
 * @brief �Œ蒷�������v�[���̏�ԎQ�Ɨp�\����.
 *
 */
typedef struct {
	INT			WaitId;				//!< �������u���b�N�l���҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT			FreeBlock;			//!< �󂫃u���b�N�̌�.
	VP			ExtInfo;			//!< �g�����.
	INT			BlockCnt; 		//!< �Œ蒷�������v�[���S�̂̃u���b�N��.
	INT			BlockSize;		//!< �Œ蒷�������u���b�N�̃T�C�Y.
	BYTE*		MemBuf;			//!< �������o�b�t�@�̃|�C���^.
} WIMPFSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitFixedMemPool( void );
void	wi_QuitFixedMemPool( void );
ER		wi_CreateFixedMemPool( INT id, const WIMPFOBJ *obj );
ER		wi_DeleteFixedMemPool( INT id );
ER		wi_GetFixedMemPool( INT id, VP buf, TMO tmout );
ER		wi_ReleaseFixedMemPool( INT id, VP blf );
ER		wi_RefarenceFixedMemPool( INT id, WIMPFSTAT *sts );
void	wi_AllReleaseFixedMemPool( INT task_id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_FIXED_MEMPOOL_H__
/* End of file */
