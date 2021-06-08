/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_mutex.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�~���[�e�b�N�X).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_mutex.h"

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< �~���[�e�b�N�X����X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitMutex( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitMutex( void )
{
	WIHDR		*next_ptr;
	WIMTXOBJ	*p = (WIMTXOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! �~���[�e�b�N�X��I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃~���[�e�b�N�X��I�u�W�F�N�g�\���̂����o��.
		p = (WIMTXOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̐���.
 *
 *	@param	[in]	id		�~���[�e�b�N�XID�ԍ�.
 *	@param	[in]	obj		�~���[�e�b�N�X��I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateMutex( INT id, const WIMTXOBJ *obj )
{
	ER			ercd;
	WIMTXOBJ	*p;

	//! �~���[�e�b�N�X��I�u�W�F�N�g���쐬����.
	p = (WIMTXOBJ *)wi_CreateObject( id, TMAX_MAXMTX, sizeof(WIMTXOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g�Ƀ~���[�e�b�N�X��ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̍폜.
 *
 *	@param	[in]	id		�~���[�e�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteMutex( INT id )
{
	ER			ercd;
	WIMTXOBJ	*p;

	//! �~���[�e�b�N�XID�̃I�u�W�F�N�g���擾����.
	p = (WIMTXOBJ *)wi_FindObject( id, TMAX_MAXMTX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y������~���[�e�b�N�X����菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->WaitQue );

	//! �~���[�e�b�N�X��I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�����b�N����.
 *
 *	@param	[in]	id		�~���[�e�b�N�XID�ԍ�.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_LockMutex( INT id, TMO tmout )
{
	INT			tsk_id;
	ER			ercd;
	WIMTXOBJ	*p;

	//! �~���[�e�b�N�XID�̃I�u�W�F�N�g���擾����.
	p = (WIMTXOBJ *)wi_FindObject( id, TMAX_MAXMTX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ��R���e�L�X�g�̃^�X�N����Ăяo���ꂽ�ꍇ�̓G���[�ɂ���.
	tsk_id = wi_GetActiveTaskId();
	if( tsk_id == 0 ){
		return E_CTX;
	}
	//! ���d���b�N�̓G���[�ɂ���.
	if( p->LockId == tsk_id ){
		return E_ILUSE;
	}
	//! �~���[�e�b�N�X�����b�N����Ă��Ȃ���΁A���b�N���ďI������.
	if( p->LockId == 0 ){
		p->LockId  = tsk_id;
		return E_OK;
	}
	//! ���b�N�����������܂Ń^�X�N���X���[�v������.
	ercd = wi_TaskWait( id, TTW_MTX, tmout, p->Attribute, &(p->WaitQue) );
	if( ercd == E_OK ){
		p->LockId = tsk_id;
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̃��b�N����������.
 *
 *	@param	[in]	id		�~���[�e�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_UnlockMutex( INT id )
{
	ER			ercd;
	WIMTXOBJ	*p;

	//! �~���[�e�b�N�XID�̃I�u�W�F�N�g���擾����.
	p = (WIMTXOBJ *)wi_FindObject( id, TMAX_MAXMTX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �~���[�e�b�N�X�����b�N���Ă���^�X�N�ƈႤ�ꍇ�̓G���[�ɂ���.
	if( p->LockId != wi_GetActiveTaskId() ){
		return E_ILUSE;
	}
	p->LockId = 0;

	//! ���b�N�����҂������Ă���^�X�N������ꍇ�̓^�X�N���N��������.
	if( p->WaitQue ){
		wi_TaskWakeup( p->WaitQue->Id, TTW_MTX, &(p->WaitQue) );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̏�ԎQ��.
 *
 *	@param	[in]	id		�~���[�e�b�N�XID�ԍ�.
 *	@param	[in]	sts		�~���[�e�b�N�X��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceMutex( INT id, WIMTXSTAT *sts )
{
	ER			ercd;
	WIMTXOBJ	*p;

	//! �~���[�e�b�N�XID�̃I�u�W�F�N�g���擾����.
	p = (WIMTXOBJ *)wi_FindObject( id, TMAX_MAXMTX, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �~���[�e�b�N�X�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->LockId = p->LockId;
	sts->WaitId = wi_GetWaitTaskListFirstId( p->WaitQue );
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
void	wi_AllReleaseMutex( INT id )
{
	WIMTXOBJ *p;

	for( p = (WIMTXOBJ *)ObjList; p; p = (WIMTXOBJ *)p->Hdr.Next ){

		//! �폜�����^�X�N��҂��s�񂩂�폜����.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
	}
}

/* End of file */
