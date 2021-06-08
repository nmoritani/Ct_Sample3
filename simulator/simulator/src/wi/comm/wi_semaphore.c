/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_semaphore.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�Z�}�t�H).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "wi_semaphore.h"
#include "CtDebugPrint.h"

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< �Z�}�t�H����X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�Ǘ��̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitSemaphore( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�Ǘ��̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitSemaphore( void )
{
	WIHDR		*next_ptr;
	WISEMOBJ	*p = (WISEMOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! �Z�}�t�H�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃Z�}�t�H�\���̂����o��.
		p = (WISEMOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�̐���.
 *
 *	@param	[in]	id		�Z�}�t�HID�ԍ�.
 *	@param	[in]	obj		�Z�}�t�H�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateSemaphore( INT id, const WISEMOBJ *obj )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( obj->SemCnt > obj->MaxCnt || obj->MaxCnt == 0 ){
		return E_PAR;
	}
	//! �Z�}�t�H��I�u�W�F�N�g���쐬����.
	p = (WISEMOBJ *)wi_CreateObject( id, TMAX_MAXSEM, sizeof(WISEMOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g�ɃZ�}�t�H��ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�̍폜.
 *
 *	@param	[in]	id		�Z�}�t�HID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteSemaphore( INT id )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! �Z�}�t�HID�̃I�u�W�F�N�g���擾����.
	p = (WISEMOBJ *)wi_FindObject( id, TMAX_MAXSEM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y������Z�}�t�H����菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->WaitQue );

	//! �Z�}�t�H��I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�����̕ԋp.
 *
 *	@param	[in]	id		�Z�}�t�HID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_SignalSemaphore( INT id )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! �Z�}�t�HID�̃I�u�W�F�N�g���擾����.
	p = (WISEMOBJ *)wi_FindObject( id, TMAX_MAXSEM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �Z�}�t�H�J�E���g��+1����.
	if( p->SemCnt < p->MaxCnt ){
		p->SemCnt++;
	}
	//! �Z�}�t�H�̊l���҂������Ă���^�X�N������ꍇ�̓^�X�N���N��������.
	if( p->WaitQue ){
		wi_TaskWakeup( p->WaitQue->Id, TTW_SEM, &(p->WaitQue) );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�����̊l��.
 *
 *	@param	[in]	id		�Z�}�t�HID�ԍ�.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_WaitSemaphore( INT id, TMO tmout )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! �Z�}�t�HID�̃I�u�W�F�N�g���擾����.
	p = (WISEMOBJ *)wi_FindObject( id, TMAX_MAXSEM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �Z�}�t�H�l���҂�������ꍇ�́A���g��҂��s��ɓ���
	//! �l���҂��������A�Z�}�t�H��J�E���^��0�łȂ���΁A�Z�}�t�H�������l�������ďI������.
	if((p->WaitCnt == 0) && (p->SemCnt > 0)){
		p->SemCnt--;
		return E_OK;
	}

	//! �Z�}�t�H�������ԋp�����܂Ń^�X�N���X���[�v������.
	p->WaitCnt = 1;
	ercd = wi_TaskWait( id, TTW_SEM, tmout, p->Attribute, &(p->WaitQue) );
	if (p->WaitCnt > 0) {
		p->WaitCnt = 0;
	}
	if( ercd == E_OK ){
		if( p->SemCnt > 0 ){
			p->SemCnt--;
		} else {
			//			CtDebugPrint(CtDbg, "!!! sem get error !!!\n");
			return E_TMOUT;
		}
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H��Ԃ̎Q��.
 *
 *	@param	[in]	id		�Z�}�t�HID�ԍ�.
 *	@param	[in]	sts		�Z�}�t�H��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceSemaphore( INT id, WISEMSTAT *sts )
{
	ER			ercd;
	WISEMOBJ	*p;

	//! �Z�}�t�HID�̃I�u�W�F�N�g���擾����.
	p = (WISEMOBJ *)wi_FindObject( id, TMAX_MAXSEM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �Z�}�t�H�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->WaitId  = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->SemCnt  = p->SemCnt;
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
void	wi_AllReleaseSemaphore( INT id )
{
	WISEMOBJ *p;

	for( p = (WISEMOBJ *)ObjList; p; p = (WISEMOBJ *)p->Hdr.Next ){

		//! �폜�����^�X�N��҂��s�񂩂�폜����.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
	}
}

/* End of file */
