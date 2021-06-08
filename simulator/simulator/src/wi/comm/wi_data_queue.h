/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_data_queue.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�f�[�^�L���[).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_DATA_QUEUE_H__
#define	__WI_DATA_QUEUE_H__

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
 * @brief �f�[�^�L���[��I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute;		//!< �f�[�^�L���[����.
	UINT		QueSize;		//!< �f�[�^�L���[�̈�̌�.
	DWORD		*QueBuf;		//!< �f�[�^�L���[�̈�̐擪�A�h���X.
	DWORD		GetPos;			//!< ���[���̓ǂݏo���ʒu.
	DWORD		PutPos;			//!< ���[���̏����o���ʒu.
	WIHDR		*SndWaitQue;	//!< �^�X�N�̑��M�҂��s��̃|�C���^.
	WIHDR		*RcvWaitQue;	//!< �^�X�N�̎�M�҂��s��̃|�C���^.
} WIDTQOBJ;

/*!
 *
 * @brief �f�[�^�L���[��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	INT			SndWaitId;			//!< �f�[�^�L���[�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT			RcvWaitId;			//!< �f�[�^�L���[�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT			DataCnt;			//!< �f�[�^�L���[�ɓ����Ă���f�[�^��.
} WIDTQSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitDataQueue( void );
void	wi_QuitDataQueue( void );
ER		wi_CreateDataQueue( INT id, const WIDTQOBJ *obj );
ER		wi_DeleteDataQueue( INT id );
ER		wi_SendDataQueue( INT id, DWORD data, TMO tmout );
ER		wi_ForceSendDataQueue( INT id, DWORD data );
ER		wi_ReceiveDataQueue( INT id, DWORD *data, TMO tmout );
ER		wi_RefarenceDataQueue(  INT id, WIDTQSTAT *sts );
void	wi_AllReleaseDataQueue( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_DATA_QUEUE_H__
/* End of file */
