/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_event_flag.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�C�x���g�t���O).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_event_flag.h"

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR		*ObjList;		//!< �C�x���g�t���O����X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�Ǘ��̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitEvFlag( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�Ǘ��̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitEvFlag( void )
{
	WIHDR		*next_ptr;
	WIFLGOBJ	*p = (WIFLGOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! �C�x���g�t���O��I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃C�x���g�t���O��I�u�W�F�N�g�\���̂����o��.
		p = (WIFLGOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̐���.
 *
 *	@param	[in]	id		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	obj		�C�x���g�t���O��I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateEvFlag( INT id, WIFLGOBJ *obj )
{
	ER			ercd;
	WIFLGOBJ	*p;

	//! �C�x���g�t���O��I�u�W�F�N�g���쐬����.
	p = (WIFLGOBJ *)wi_CreateObject( id, TMAX_MAXFLG, sizeof(WIFLGOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g�ɃC�x���g�t���O��ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̍폜.
 *
 *	@param	[in]	id		�C�x���g�t���OID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteEvFlag( INT id )
{
	ER			ercd;
	WIFLGOBJ	*p;

	//! �C�x���g�t���OID�̃I�u�W�F�N�g���擾����.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y������C�x���g�t���O����菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->WaitQue );

	//! �C�x���g�t���O��I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̃Z�b�g.
 *
 *	@param	[in]	id		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	setptn	�Z�b�g����r�b�g�p�^�[��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_SetEvFlag( INT id, UINT setptn )
{
	ER			ercd;
	WIFLGOBJ	*p;
	WITSKOBJ	*tsk,*next_link;
	UINT		tsk_flg,event_mode;
	BOOL		event_on;

	//! �C�x���g�t���OID�̃I�u�W�F�N�g���擾����.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( setptn == 0 ){
		return E_PAR;
	}
	//! �w�肳�ꂽ�t���O���Z�b�g����.
	p->FlgVal |= setptn;

	tsk = (WITSKOBJ *)(p->WaitQue);
	while( tsk ){
		event_on   = FALSE;
		tsk_flg    = (UINT)tsk->Param[0];
		event_mode = (UINT)tsk->Param[1];

		if( event_mode & TWF_ORW ){
			//! OR�҂��̏ꍇ�A�����ꂩ�̃r�b�g����v����΃C�x���g�𔭍s����.
			if( (tsk_flg & p->FlgVal) != 0 ){
				event_on = TRUE;
			}
		}else{
			//! AND�҂��̏ꍇ�A�S�Ẵr�b�g����v����΃C�x���g�𔭍s����.
			if( (tsk_flg & p->FlgVal) == tsk_flg ){
				event_on = TRUE;
			}
		}
		//! ���̃C�x���g�҂��^�X�N�����o��.
		next_link = tsk->QueLink;

		if( event_on ){
			//! �C�x���g�������̃t���O�p�^�[�����^�X�N��I�u�W�F�N�g�ɕۑ�����.
			tsk->Param[2] = (VP)(p->FlgVal);

			//! �t���O�̃N���A�ݒ肪����Ă���ꍇ�̓t���O���N���A����.
			if( (event_mode & TWF_CLR) != 0 || (p->Attribute & TA_CLR) != 0 ){
				p->FlgVal = 0;
			}
			//! �C�x���g�҂������Ă���^�X�N���N��������.
			wi_TaskWakeup( tsk->Hdr.Id, TTW_FLG, &(p->WaitQue) );
		}
		tsk = next_link;
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̃N���A.
 *
 *	@param	[in]	id		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	clrptn	�N���A����r�b�g�p�^�[��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ClearEvFlag( INT id, UINT clrptn )
{
	ER			ercd;
	WIFLGOBJ	*p;

	//! �C�x���g�t���OID�̃I�u�W�F�N�g���擾����.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �w�肳�ꂽ�t���O���N���A����.
	p->FlgVal &= clrptn;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�҂�.
 *
 *	@param	[in]	id			�C�x���g�t���OID�ԍ�.
 *	@param	[out]	flgptn		�҂��������̃r�b�g�p�^�[�����i�[����̈�̃|�C���^.
 *	@param	[in]	waiptn		�҂��r�b�g�p�^�[��.
 *	@param	[in]	wfmode		�҂����[�h.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_WaitEvFlag( INT id, UINT *flgptn, UINT waiptn, UINT wfmode, TMO tmout )
{
	WITSKOBJ	*tsk;
	WIFLGOBJ	*p;
	ER			ercd;
	BOOL		event_on;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !flgptn || waiptn == 0 ){
		return E_PAR;
	}
	//! �C�x���g�t���OID�̃I�u�W�F�N�g���擾����.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	*flgptn  = 0;
	event_on = FALSE;
	if( wfmode & TWF_ORW ){
		//! OR�҂��̏ꍇ�A�����ꂩ�̃r�b�g����v����΁u�C�x���g����v�ɂ���.
		if( (waiptn & p->FlgVal) != 0 ){
			event_on = TRUE;
		}
	}else{
		//! AND�҂��̏ꍇ�A�S�Ẵr�b�g����v����΁u�C�x���g����v�ɂ���.
		if( (waiptn & p->FlgVal) == waiptn ){
			event_on = TRUE;
		}
	}
	if( event_on ){
		//! �C�x���g�������̃t���O�p�^�[����߂�l�ɃZ�b�g����.
		*flgptn = p->FlgVal;

		//! �t���O�̃N���A�ݒ肪����Ă���ꍇ�̓t���O���N���A����.
		if( (wfmode & TWF_CLR) != 0 || (p->Attribute & TA_CLR) != 0 ){
			p->FlgVal = 0;
		}
		return E_OK;
	}
	//! �����^�X�N�̑҂��������Ȃ��ݒ�ŁA�҂��s��ɑ��̃^�X�N������ꍇ�̓G���[�ɂ���.
	if( (p->Attribute & TA_WMUL) == 0 && p->WaitQue ){
		return E_ILUSE;
	}
	//! ���^�X�N�̃^�X�N��I�u�W�F�N�g���擾����.
	tsk = wi_GetTaskObject( TSK_SELF );
	if( !tsk ){
		return E_CTX;
	}
	//! �҂��t���O�p�^�[�����^�X�N��I�u�W�F�N�g�ɕۑ�����.
	tsk->Param[0] = (VP)waiptn;
	tsk->Param[1] = (VP)wfmode;
	tsk->Param[2] = 0;

	//! �C�x���g�t���O����������܂Ń^�X�N���X���[�v������.
	ercd = wi_TaskWait( id, TTW_FLG, tmout, p->Attribute, &(p->WaitQue) );

	//! �C�x���g�������̃t���O�p�^�[����߂�l�ɃZ�b�g����.
	if( ercd == E_OK ){
		*flgptn = (UINT)(tsk->Param[2]);
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O��Ԃ̎Q��.
 *
 *	@param	[in]	id		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	sts		�C�x���g�t���O��Ԃ��i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceEvFlag( INT id, WIFLGSTAT *sts )
{
	ER			ercd;
	WIFLGOBJ	*p;

	//! �C�x���g�t���OID�̃I�u�W�F�N�g���擾����.
	p = (WIFLGOBJ *)wi_FindObject( id, TMAX_MAXFLG, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �C�x���g�t���O�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->WaitId  = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->FlgVal  = p->FlgVal;
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
void	wi_AllReleaseEvFlag( INT id )
{
	WIFLGOBJ *p;

	for( p = (WIFLGOBJ *)ObjList; p; p = (WIFLGOBJ *)p->Hdr.Next ){

		//! �폜�����^�X�N��҂��s�񂩂�폜����.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
	}
}

/* End of file */
