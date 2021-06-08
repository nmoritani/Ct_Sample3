/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_variable_mempool.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�ϒ��������v�[��).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_VARIABLE_MEMPOOL_H__
#define	__WI_VARIABLE_MEMPOOL_H__

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
 * @brief �ϒ���������I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;				//!< �I�u�W�F�N�g��w�b�_.
	VP			ExtInfo;			//!< �g�����.
	ATR			Attribute; 			//!< �ϒ��������v�[������.
	INT			MemSize;			//!< �ϒ��������v�[���̃T�C�Y.
	BYTE		*MemBuf;			//!< �ϒ��������v�[���̃f�[�^�o�b�t�@�̃|�C���^.
	WIHDR		*WaitQue;			//!< �^�X�N�̑҂��s��̃|�C���^.
} WIMPLOBJ;

/*!
 *
 * @brief �ϒ��������̏�ԎQ�Ɨp�\����.
 *
 */
typedef struct {
	INT			WaitId;				//!< �҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT			TotalFreeSize;		//!< �󂫗̈�̍��v�T�C�Y.
	INT			MaxFreeSize;		//!< �ő�̘A���󂫗̈�̃T�C�Y.
	VP			ExtInfo;			//!< �g�����.
	INT			MemSize;			//!< �ϒ��������v�[���̃T�C�Y.
	BYTE		*MemBuf;			//!< �ϒ��������v�[���̃f�[�^�o�b�t�@�̃|�C���^.
} WIMPLSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitVarMemPool( void );
void	wi_QuitVarMemPool( void );
ER		wi_CreateVarMemPool( INT id, const WIMPLOBJ *obj );
ER		wi_DeleteVarMemPool( INT id );
ER		wi_GetVarMemPool( INT id, VP adr, INT size, TMO tmout );
ER		wi_ReleaseVarMemPool( INT id, VP adr );
ER		wi_RefarenceVarMemPool( INT id, WIMPLSTAT *sts );
void	wi_AllReleaseVarMemPool( INT id );
void	wi_RefarenceAllocatedVarMemPool(INT id);

#ifdef __cplusplus
}
#endif
#endif	// __WI_VARIABLE_MEMPOOL_H__
/* End of file */
