/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_message_buffer.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (���b�Z�[�W�o�b�t�@).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_MESSAGE_BUFFER_H__
#define	__WI_MESSAGE_BUFFER_H__

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
 * @brief ���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			SndAttr;		//!< ���b�Z�[�W�o�b�t�@���� (���b�Z�[�W���M��).
	ATR			RcvAttr;		//!< ���b�Z�[�W�o�b�t�@���� (���b�Z�[�W��M��).
	UINT		MaxMsg; 		//!< ���b�Z�[�W�̍ő咷.
	UINT		MsgSize;		//!< ���b�Z�[�W�o�b�t�@�̈�̃T�C�Y.
	BYTE		*MsgBuf;		//!< ���b�Z�[�W�o�b�t�@�̈�̐擪�A�h���X.
	UINT		GetPos;			//!< ���[���̓ǂݏo���ʒu.
	UINT		PutPos;			//!< ���[���̏����o���ʒu.
	WIHDR		*SndWaitQue;	//!< �^�X�N�̑��M�҂��s��̃|�C���^.
	WIHDR		*RcvWaitQue;	//!< �^�X�N�̎�M�҂��s��̃|�C���^.
	VP			ExtInfo;		//!< �g�����.
} WIMBFOBJ;

/*!
 *
 * @brief ���b�Z�[�W�o�b�t�@��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	INT			SndWaitId;		//!< ���b�Z�[�W�o�b�t�@�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT			RcvWaitId;		//!< ���b�Z�[�W�o�b�t�@�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	VP			ExtInfo;		//!< �g�����.
	INT			MsgSize;		//!< ���Ɏ�M����郁�b�Z�[�W�̃T�C�Y.
	INT			FreeSize;		//!< �󂫃o�b�t�@�̃T�C�Y.
} WIMBFSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitMsgBuffer( void );
void	wi_QuitMsgBuffer( void );
ER		wi_CreateMsgBuffer( INT id, const WIMBFOBJ *obj );
ER		wi_DeleteMsgBuffer( INT id );
ER		wi_SendMsgBuffer( INT id, VP msg, int size, TMO tmout );
ER		wi_ReceiveMsgBuffer( INT id, VP msg, int *size, TMO tmout );
ER		wi_RefarenceMsgBuffer( INT id, WIMBFSTAT *sts );
void	wi_AllReleaseMsgBuffer( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_MESSAGE_BUFFER_H__
/* End of file */
