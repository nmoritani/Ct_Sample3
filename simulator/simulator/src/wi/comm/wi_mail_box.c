/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_mail_box.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (���[���{�b�N�X).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_mail_box.h"

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< ���[���{�b�N�X����X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�Ǘ��̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitMailBox( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�Ǘ��̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitMailBox( void )
{
	WIHDR		*next_ptr;
	WIMBXOBJ	*p = (WIMBXOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! ���[���{�b�N�X��I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃��[���{�b�N�X��I�u�W�F�N�g�\���̂����o��.
		p = (WIMBXOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�̐���.
 *
 *	@param	[in]	id		���[���{�b�N�XID�ԍ�.
 *	@param	[in]	obj		���[���{�b�N�X��I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateMailBox( INT id, const WIMBXOBJ *obj )
{
	ER			ercd;
	WIMBXOBJ	*p;

	//! �s���Ȉ����̏ꍇ�̓G���[�ɂ���.
	if( (obj->Attribute & TA_MPRI) != 0 && (obj->MaxPriority == 0 || obj->MaxPriority > TMAX_MPRI) ){
		return E_PAR;
	}
	//! ���[���{�b�N�X��I�u�W�F�N�g���쐬����.
	p = (WIMBXOBJ *)wi_CreateObject( id, TMAX_MAXMBX, sizeof(WIMBXOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g�Ƀ��[���{�b�N�X��ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�̍폜.
 *
 *	@param	[in]	id		���[���{�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteMailBox( INT id )
{
	ER			ercd;
	WIMBXOBJ	*p;

	//! ���[���{�b�N�XID�̃I�u�W�F�N�g���擾����.
	p = (WIMBXOBJ *)wi_FindObject( id, TMAX_MAXMBX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y�����郁�[���{�b�N�X����菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->WaitQue );

	//! ���[���{�b�N�X��I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�ւ̑��M.
 *
 *	@param	[in]	id		���[���{�b�N�XID�ԍ�.
 *	@param	[in]	msg		���b�Z�[�W��p�P�b�g�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_SendMailBox( INT id, T_MSG *msg )
{
	ER			ercd;
	WIMBXOBJ	*p;
	T_MSG		*msg_ptr;

	//! ���[���{�b�N�XID�̃I�u�W�F�N�g���擾����.
	p = (WIMBXOBJ *)wi_FindObject( id, TMAX_MAXMBX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �s���Ȉ����̏ꍇ�̓G���[�ɂ���.
	if( !msg ){
		return E_PAR;
	}
	msg->nextmsg = NULL;
	if( (p->Attribute & TA_MPRI) != 0 ){
		//! �D��x���Ƀ��b�Z�[�W���i�[����ꍇ.
		if( !(p->MsgQue) ){
			//! ���b�Z�[�W�L���[�Ƀ��b�Z�[�W���Ȃ��ꍇ�̓��b�Z�[�W�L���[�̐擪�Ɋi�[����.
			p->MsgQue = msg;
		}else
		if( p->MsgQue->msgpri > msg->msgpri ){
			//! ���b�Z�[�W�L���[�̐擪���b�Z�[�W���D��x�������ꍇ�����b�Z�[�W�L���[�̐擪�Ɋi�[����.
			msg->nextmsg = p->MsgQue;
			p->MsgQue    = msg;
		}else{
			msg_ptr = p->MsgQue;
			while( msg_ptr ){
				if( !(msg_ptr->nextmsg) ){
					//! ���̃��b�Z�[�W���Ȃ��ꍇ�̓��b�Z�[�W�L���[�̍Ō�Ƀ��b�Z�[�W���i�[����.
					msg_ptr->nextmsg = msg;
					break;
				}
				if( msg_ptr->nextmsg->msgpri > msg->msgpri ){
					//! ���̃��b�Z�[�W���D��x�������ꍇ�A���̃��b�Z�[�W�̑O�Ƀ��b�Z�[�W���i�[����.
					msg->nextmsg     = msg_ptr->nextmsg;
					msg_ptr->nextmsg = msg->nextmsg;
					break;
				}
				msg_ptr = msg_ptr->nextmsg;
			}
		}
	}else{
		//! ���b�Z�[�W��p�P�b�g����X�g�Ƀ����N����Ă���Ō�̃��b�Z�[�W��T��.
		msg_ptr = p->MsgQue;
		while( msg_ptr ){
			if( !(msg_ptr->nextmsg) ){
				break;
			}
			msg_ptr = msg_ptr->nextmsg;
		}
		//! ���b�Z�[�W��p�P�b�g����X�g�̍Ō�Ɉ����̃��b�Z�[�W��p�P�b�g��ǉ�����.
		if( msg_ptr ){
			msg_ptr->nextmsg = msg;
		}else{
			p->MsgQue = msg;
		}
	}
	//! ���b�Z�[�W�҂������Ă���^�X�N������ꍇ�̓^�X�N���N��������.
	if( p->WaitQue ){
		wi_TaskWakeup( p->WaitQue->Id, TTW_MBX, &(p->WaitQue) );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X����̎�M.
 *
 *	@param	[in]	id		���[���{�b�N�XID�ԍ�.
 *	@param	[out]	ppk_msg	���b�Z�[�W��p�P�b�g�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ReceiveMailBox( INT id, T_MSG **msg, TMO tmout )
{
	ER			ercd;
	WIMBXOBJ	*p;

	//! ���[���{�b�N�XID�̃I�u�W�F�N�g���擾����.
	p = (WIMBXOBJ *)wi_FindObject( id, TMAX_MAXMBX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �s���Ȉ����̏ꍇ�̓G���[�ɂ���.
	if( !msg ){
		return E_PAR;
	}
	//! ���b�Z�[�W��p�P�b�g����X�g�Ƀ��b�Z�[�W������ꍇ�̓��b�Z�[�W�����o���ďI������.
	if( p->MsgQue ){
		*msg      = p->MsgQue;
		p->MsgQue = p->MsgQue->nextmsg;
		return E_OK;
	}
	//! ���b�Z�[�W����M����܂Ń^�X�N���X���[�v������.
	ercd = wi_TaskWait( id, TTW_MBX, tmout, p->Attribute, &(p->WaitQue) );
	if( ercd == E_OK ){
		if( p->MsgQue ){
			*msg      = p->MsgQue;
			p->MsgQue = p->MsgQue->nextmsg;
		}
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�̏�ԎQ��.
 *
 *	@param	[in]	id		���[���{�b�N�XID�ԍ�.
 *	@param	[out]	sts		���[���{�b�N�X��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceMailBox( INT id, WIMBXSTAT *sts )
{
	ER			ercd;
	WIMBXOBJ	*p;

	//! ���[���{�b�N�XID�̃I�u�W�F�N�g���擾����.
	p = (WIMBXOBJ *)wi_FindObject( id, TMAX_MAXMBX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���[���{�b�N�X�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->WaitId  = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->NextMsg = p->MsgQue;
	sts->ExtInfo = p->ExtInfo;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�폜�����^�X�N��҂��s�񂩂�폜����.
 *
 *	@param	[in]	id		�폜�����^�X�NID�ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_AllReleaseMailBox( INT id )
{
	WIMBXOBJ *p;

	for( p = (WIMBXOBJ *)ObjList; p; p = (WIMBXOBJ *)p->Hdr.Next ){

		//! �폜�����^�X�N��҂��s�񂩂�폜����.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
	}
}

/* End of file */
