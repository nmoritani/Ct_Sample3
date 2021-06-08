/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_data_queue.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�f�[�^�L���[).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_data_queue.h"

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< �f�[�^�L���[����X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitDataQueue( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitDataQueue( void )
{
	WIHDR		*next_ptr;
	WIDTQOBJ	*p = (WIDTQOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! �f�[�^�L���[�o�b�t�@���������.
		SAFE_RELEASE( p->QueBuf );

		//! �f�[�^�L���[��I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃f�[�^�L���[��I�u�W�F�N�g�\���̂����o��.
		p = (WIDTQOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̐���.
 *
 *	@param	[in]	id		�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	obj		�f�[�^�L���[��I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateDataQueue( INT id, const WIDTQOBJ *obj )
{
	ER			ercd;
	WIDTQOBJ	*p;

	//! �f�[�^�L���[��I�u�W�F�N�g���쐬����.
	p = (WIDTQOBJ *)wi_CreateObject( id, TMAX_MAXDTQ, sizeof(WIDTQOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	if( p->QueSize > 0 ){
		//! �o�b�t�@FULL����ׂ̈�1�]�v�Ƀo�b�t�@���m�ۂ���.
		p->QueSize++;

		//! �f�[�^�L���[�o�b�t�@���m�ۂ���.
		p->QueBuf = (DWORD *)malloc( sizeof(DWORD) * p->QueSize );
		if( !p->QueBuf ){
			SAFE_RELEASE( p );
			return E_NOMEM;
		}
		//! �m�ۂ����f�[�^�L���[�o�b�t�@���N���A����.
		memset( p->QueBuf, 0, sizeof(DWORD) * p->QueSize );
	}
	p->GetPos = 0;
	p->PutPos = 0;

	//! ���X�g�Ƀf�[�^�L���[��ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̍폜.
 *
 *	@param	[in]	id		�f�[�^�L���[ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteDataQueue( INT id )
{
	ER			ercd;
	WIDTQOBJ	*p;

	//! �f�[�^�L���[ID�̃I�u�W�F�N�g���擾����.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y������f�[�^�L���[����菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->SndWaitQue );
	wi_WakeupDelResource( p->RcvWaitQue );

	//! �f�[�^�L���[�o�b�t�@���������.
	SAFE_RELEASE( p->QueBuf );

	//! �f�[�^�L���[��I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�ւ̑��M.
 *
 *	@param	[in]	id		�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	data	�f�[�^�L���[�ɑ��M����f�[�^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_SendDataQueue( INT id, DWORD data, TMO tmout )
{
	WITSKOBJ	*tsk;
	WIDTQOBJ	*p;
	DWORD		pos;
	ER			ercd;

	//! �f�[�^�L���[ID�̃I�u�W�F�N�g���擾����.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �f�[�^�L���[�o�b�t�@���m�ۂ��Ă��Ȃ��ꍇ.
	if( p->QueSize == 0 || !p->QueBuf ){

		if( p->RcvWaitQue ){
			tsk = (WITSKOBJ *)(p->RcvWaitQue);

			//! ���b�Z�[�W����M�^�X�N�ɕۑ�����.
			tsk->Param[0] = (VP)data;

			//! ���b�Z�[�W�҂������Ă���^�X�N������ꍇ�̓^�X�N���N��������.
			wi_TaskWakeup( tsk->Hdr.Id, TTW_RDTQ, &(p->RcvWaitQue) );
			return E_OK;
		}else{
			//! ���b�Z�[�W�𑗐M�^�X�N(���^�X�N)�ɕۑ�����.
			tsk = wi_GetTaskObject( TSK_SELF );
			if( tsk ){
				tsk->Param[0] = (VP)data;
			}
			//! ��M�^�X�N�������܂Ń^�X�N���X���[�v������.
			ercd = wi_TaskWait( id, TTW_SDTQ, tmout, p->Attribute, &(p->SndWaitQue) );
			return ercd;
		}
	}
	pos = wi_IncRingPositon( p->PutPos, p->QueSize );
	if( pos == p->GetPos ){
		//! �f�[�^�L���[�o�b�t�@���󂭂܂Ń^�X�N���X���[�v������.
		ercd = wi_TaskWait( id, TTW_SDTQ, tmout, p->Attribute, &(p->SndWaitQue) );
		if( ercd != E_OK ){
			return ercd;
		}
	}
	//! �f�[�^�L���[�ɑ��M�f�[�^���i�[����.
	p->QueBuf[p->PutPos] = data;

	//! �f�[�^�L���[�̏����݈ʒu���X�V����.
	p->PutPos = pos;

	//! �f�[�^��M�҂������Ă���^�X�N������ꍇ�̓^�X�N���N��������.
	if( p->RcvWaitQue ){
		wi_TaskWakeup( p->RcvWaitQue->Id, TTW_RDTQ, &(p->RcvWaitQue) );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�ւ̋������M.
 *
 *	@param	[in]	id		�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	data	�f�[�^�L���[�ɑ��M����f�[�^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ForceSendDataQueue( INT id, DWORD data )
{
	ER			ercd;
	WIDTQOBJ	*p;
	DWORD		pos;

	//! �f�[�^�L���[ID�̃I�u�W�F�N�g���擾����.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �f�[�^�L���[�o�b�t�@���m�ۂ��Ă��Ȃ��ꍇ�̓G���[�ɂ���.
	if( p->QueSize == 0 ){
		return E_ILUSE;
	}
	//! �f�[�^�L���[�ɋ󂫂��Ȃ��ꍇ�̓f�[�^�L���[�̐擪�f�[�^��p������.
	pos = wi_IncRingPositon( p->PutPos, p->QueSize );
	if( pos == p->GetPos ){
		p->GetPos = wi_IncRingPositon( p->GetPos, p->QueSize );
	}
	//! �f�[�^�L���[�̃f�[�^���M�������Ăяo��.
	return wi_SendDataQueue( id, data, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[����̎�M.
 *
 *	@param	[in]	id		�f�[�^�L���[ID�ԍ�.
 *	@param	[out]	data	�f�[�^�L���[�����M�����f�[�^���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ReceiveDataQueue( INT id, DWORD *data, TMO tmout )
{
	ER			ercd;
	WIDTQOBJ	*p;
	WITSKOBJ	*tsk;

	//! �f�[�^�L���[ID�̃I�u�W�F�N�g���擾����.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !data ){
		return E_PAR;
	}
	//! �f�[�^�L���[�o�b�t�@���m�ۂ��Ă��Ȃ��ꍇ.
	if( p->QueSize == 0 || !p->QueBuf ){

		if( p->SndWaitQue ){
			tsk = (WITSKOBJ *)(p->SndWaitQue);

			//! ���M���b�Z�[�W�����o��.
			*data = (DWORD)(tsk->Param[0]);

			//! ���b�Z�[�W��M���҂��Ă���^�X�N���N��������.
			wi_TaskWakeup( tsk->Hdr.Id, TTW_SDTQ, &(p->SndWaitQue) );
			return E_OK;
		}else{
			//! ���b�Z�[�W�����M�����܂Ń^�X�N���X���[�v������.
			ercd = wi_TaskWait( id, TTW_RDTQ, tmout, p->Attribute, &(p->RcvWaitQue) );
			if( ercd == E_OK ){
				//! ���M���b�Z�[�W�����o��.
				tsk = wi_GetTaskObject( TSK_SELF );
				if( tsk ){
					*data = (DWORD)(tsk->Param[0]);
				}
			}
			return ercd;
		}
	}
	//! �f�[�^�L���[�Ƀf�[�^������ꍇ�A�f�[�^�����o���ďI������.
	if( p->GetPos != p->PutPos ){

		//! �f�[�^�L���[�̐擪����f�[�^�����o��.
		*data = p->QueBuf[p->GetPos];

		//! �f�[�^�L���[�̓ǂݏo���ʒu���X�V����.
		p->GetPos = wi_IncRingPositon( p->GetPos, p->QueSize );

		//! �o�b�t�@���󂭂̂�҂��Ă���^�X�N������ꍇ�̓^�X�N���N��������.
		if( p->SndWaitQue ){
			wi_TaskWakeup( p->SndWaitQue->Id, TTW_SDTQ, &(p->SndWaitQue) );
		}
		return E_OK;
	}
	//! ���b�Z�[�W����M����܂Ń^�X�N���X���[�v������.
	ercd = wi_TaskWait( id, TTW_RDTQ, tmout, p->Attribute, &(p->RcvWaitQue) );
	if( ercd == E_OK ){
		if( p->GetPos != p->PutPos ){
			//! �f�[�^�L���[�̐擪����f�[�^�����o��.
			*data = p->QueBuf[p->GetPos];

			//! �f�[�^�L���[�̓ǂݏo���ʒu���X�V����.
			p->GetPos = wi_IncRingPositon( p->GetPos, p->QueSize );
		}
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̏�ԎQ��.
 *
 *	@param	[in]	id		�f�[�^�L���[ID�ԍ�.
 *	@param	[out]	sts		�f�[�^�L���[��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceDataQueue( INT id, WIDTQSTAT *sts )
{
	ER			ercd;
	WIDTQOBJ	*p;
	DWORD		cnt;

	//! �f�[�^�L���[ID�̃I�u�W�F�N�g���擾����.
	p = (WIDTQOBJ *)wi_FindObject( id, TMAX_MAXDTQ, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �f�[�^�L���[�ɓ����Ă���f�[�^�̌����v�Z����.
	if( p->GetPos <= p->PutPos ){
		cnt = p->PutPos - p->GetPos;
	}else{
		cnt = (p->QueSize + p->PutPos) - p->GetPos;
	}
	//! �f�[�^�L���[�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->SndWaitId = wi_GetWaitTaskListFirstId( p->SndWaitQue );
	sts->RcvWaitId = wi_GetWaitTaskListFirstId( p->RcvWaitQue );
	sts->DataCnt   = cnt;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�폜�����^�X�N��҂��s�񂩂�폜����.
 *
 *	@param	[in]	id	�폜�����^�X�NID�ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_AllReleaseDataQueue( INT id )
{
	WIDTQOBJ *p;

	for( p = (WIDTQOBJ *)ObjList; p; p = (WIDTQOBJ *)p->Hdr.Next ){

		//! �폜�����^�X�N��҂��s�񂩂�폜����.
		p->SndWaitQue = wi_DelWaitTaskList( id, p->SndWaitQue );
		p->SndWaitQue = wi_DelWaitTaskList( id, p->SndWaitQue );
	}
}

/* End of file */
