/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_mail_box.h
 *
 *	@brief	Windows�� iTRON(Ver3.0)�T�[�r�X�R�[�� (���[���{�b�N�X).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_MAIL_BOX_H__
#define	__WI_MAIL_BOX_H__

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
 * @brief ���[���{�b�N�X��I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute;		//!< ���[���{�b�N�X����.
	PRI			MaxPriority;	//!< ���M����郁�b�Z�[�W�D��x�̍ő�l.
	VP			ExtInfo;		//!< �g�����.
	T_MSG		*MsgQue;		//!< ���b�Z�[�W��p�P�b�g����X�g�̃|�C���^.
	WIHDR		*WaitQue;		//!< �^�X�N�̑҂��s��̃|�C���^.
} WIMBXOBJ;

/*!
 *
 * @brief ���[���{�b�N�X�̏�ԎQ�Ɨp�\����.
 *
 */
typedef struct {
	INT			WaitId;			//!< ���b�Z�[�W�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	T_MSG		*NextMsg;		//!< ���Ɏ�M����郁�b�Z�[�W.
	VP			ExtInfo;		//!< �g�����.
} WIMBXSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitMailBox( void );
void	wi_QuitMailBox( void );
ER		wi_CreateMailBox( INT id, const WIMBXOBJ *obj );
ER		wi_DeleteMailBox( INT id );
ER		wi_SendMailBox( INT id, T_MSG *msg );
ER		wi_ReceiveMailBox( INT id, T_MSG **msg, TMO tmout );
ER		wi_RefarenceMailBox( INT id, WIMBXSTAT *sts );
void	wi_AllReleaseMailBox( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_MAIL_BOX_H__
/* End of file */
