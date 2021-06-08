/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_message_buffer.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (���b�Z�[�W�o�b�t�@).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_message_buffer.h"

/****************************************************************************
 *
 * ���[�J���֐���`.
 *
 ****************************************************************************/
static void		RestoreMessageData( WIMBFOBJ *p );
static INT		GetNextMessageSize( WIMBFOBJ *p );
static INT		GetFreeSize( WIMBFOBJ *p );
static BOOL		PutMesageData( WIMBFOBJ *p, BYTE* msg, INT len );
static INT		GetMessageData( WIMBFOBJ *p, BYTE* msg );

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR	*ObjList;		//!< ���b�Z�[�W�o�b�t�@����X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitMsgBuffer( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitMsgBuffer( void )
{
	WIHDR		*next_ptr;
	WIMBFOBJ	*p = (WIMBFOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! ���b�Z�[�W�o�b�t�@���������.
		SAFE_RELEASE( p->MsgBuf );

		//! ���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃��b�Z�[�W�o�b�t�@��I�u�W�F�N�g�\���̂����o��.
		p = (WIMBFOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̐���.
 *
 *	@param	[in]	id		���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[in]	obj		���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateMsgBuffer( INT id, const WIMBFOBJ *obj )
{
	ER			ercd;
	WIMBFOBJ	*p;

	//! �s���Ȉ����̏ꍇ�̓G���[�ɂ���.
	if( obj->MaxMsg == 0 ){
		return E_PAR;
	}
	//! ���b�Z�[�W�o�b�t�@��I�u�W�F�N�g���쐬����.
	p = (WIMBFOBJ *)wi_CreateObject( id, TMAX_MAXMBF, sizeof(WIMBFOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���b�Z�[�W�o�b�t�@���m�ۂ���.
	if( p->MsgSize > 0 ){
		p->MsgBuf = (BYTE *)malloc( p->MsgSize );
		if( !p->MsgBuf ){
			SAFE_RELEASE( p );
			return E_NOMEM;
		}
		//! �m�ۂ������b�Z�[�W�o�b�t�@���N���A����.
		memset( p->MsgBuf, 0, p->MsgSize );
	}
	p->GetPos = 0;
	p->PutPos = 0;

	//! ���X�g�Ƀ��b�Z�[�W�o�b�t�@��ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̍폜.
 *
 *	@param	[in]	id		���b�Z�[�W�o�b�t�@ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteMsgBuffer( INT id )
{
	ER			ercd;
	WIMBFOBJ	*p;

	//! ���b�Z�[�W�o�b�t�@ID�̃I�u�W�F�N�g���擾����.
	p = (WIMBFOBJ *)wi_FindObject( id, TMAX_MAXMBF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y�����郁�b�Z�[�W�o�b�t�@����菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->SndWaitQue );
	wi_WakeupDelResource( p->RcvWaitQue );

	//! ���b�Z�[�W�o�b�t�@���������.
	SAFE_RELEASE( p->MsgBuf );

	//! ���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W��o�b�t�@�ւ̑��M.
 *
 *	@param	[in]	id		���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[in]	msg		���b�Z�[�W�̃|�C���^.
 *	@param	[in]	size	���b�Z�[�W�̃T�C�Y.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_SendMsgBuffer( INT id, VP msg, INT size, TMO tmout )
{
	ER			ercd;
	WIMBFOBJ	*p;
	WITSKOBJ	*tsk1,*tsk2;

	//! ���b�Z�[�W�o�b�t�@ID�̃I�u�W�F�N�g���擾����.
	p = (WIMBFOBJ *)wi_FindObject( id, TMAX_MAXMBF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !msg || !size ){
		return E_PAR;
	}
	//! ���b�Z�[�W�҂������Ă���^�X�N������ꍇ.
	if( p->RcvWaitQue ){

		//! ���b�Z�[�W�҂������Ă���^�X�N�Ƀ��b�Z�[�W��n��.
		tsk1 = (WITSKOBJ *)(p->RcvWaitQue);
		if( tsk1->Param[0] ){
			memcpy( tsk1->Param[0], msg, size );
			tsk1->Param[1] = (VP)size;
		}
		//! ���b�Z�[�W�҂������Ă���^�X�N���N������.
		wi_TaskWakeup( tsk1->Hdr.Id, TTW_RMBF, &(p->RcvWaitQue) );
		return E_OK;
	}
	//! ���^�X�N�̃^�X�N�R���e�L�X�g�����o��.
	tsk1 = wi_GetTaskObject( TSK_SELF );

	//! ��^�X�N�R���e�L�X�g����̌Ăяo���̏ꍇ�̓G���[�ɂ���.
	if( !tsk1 ){
		return E_CTX;
	}
	//! ���M�҂��̃^�X�N������ꍇ.
	if( p->SndWaitQue ){

		/*!
		 * �҂��s�񂪃^�X�N�D��x���̏ꍇ�A�҂��s��̐擪�̃^�X�N�̗D��x���
		 * ����̃^�X�N(���^�X�N)�̗D��x���傫������΁A���b�Z�[�W�o�b�t�@��
		 * �҂��s��̃^�X�N������ɑ��M���b�Z�[�W���i�[����.
		 */
		if( p->SndAttr & TA_TPRI ){
			tsk2 = (WITSKOBJ *)(p->SndWaitQue);
			if( tsk1->TaskPri > tsk2->TaskPri ){
				if( PutMesageData( p, msg, size ) ){
					return E_OK;
				}
			}
		}
	}else{
		//! ���b�Z�[�W�o�b�t�@�̍Ō�ɑ��M���b�Z�[�W���i�[����.
		if( PutMesageData( p, msg, size ) ){
			return E_OK;
		}
	}
	//! �^�X�N�R���e�L�X�g�ɑ��M���b�Z�[�W���i�[���Ă���.
	tsk1->Param[0] = msg;
	tsk1->Param[1] = (VP)size;

	//! �o�b�t�@���󂭂܂Ń^�X�N���X���[�v������.
	return wi_TaskWait( id, TTW_SMBF, tmout, p->SndAttr, &(p->SndWaitQue) );
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@����̎�M.
 *
 *	@param	[in]	id		���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[out]	msg		���b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[out]	size	���b�Z�[�W��T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ReceiveMsgBuffer( INT id, VP msg, INT *size, TMO tmout )
{
	ER			ercd;
	WIMBFOBJ	*p;
	WITSKOBJ	*tsk;

	//! ���b�Z�[�W�o�b�t�@ID�̃I�u�W�F�N�g���擾����.
	p = (WIMBFOBJ *)wi_FindObject( id, TMAX_MAXMBF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !msg || !size ){
		return E_PAR;
	}
	//! ���b�Z�[�W�o�b�t�@���烁�b�Z�[�W�����o��.
	*size = GetMessageData( p, (BYTE *)msg );
	if( *size > 0 ){
		//! ���b�Z�[�W�o�b�t�@���󂢂��̂ő��M�҂������Ă��郁�b�Z�[�W���o�b�t�@�ɏ�������.
		RestoreMessageData( p );
		return E_OK;
	}
	/*!
	 * ���b�Z�[�W���M�҂������Ă���^�X�N������ꍇ�A
	 * ���b�Z�[�W���M�^�X�N���璼�ڃ��b�Z�[�W���󂯎��.
	 */
	if( p->SndWaitQue ){

		//! ���b�Z�[�W���M�҂������Ă���^�X�N�̃R���e�L�X�g�����o��.
		tsk = (WITSKOBJ *)(p->SndWaitQue);

		if( tsk->Param[0] ){
			//! ���b�Z�[�W���M�^�X�N���璼�ڃ��b�Z�[�W���R�s�[����.
			memcpy( msg, tsk->Param[0], (INT)(tsk->Param[1]) );
			tsk->Param[0] = NULL;
			tsk->Param[1] = 0;

			/*!
			 * ���b�Z�[�W�o�b�t�@�ɏ������߂邩������Ȃ��̂�
			 * ���M�҂������Ă��郁�b�Z�[�W���o�b�t�@�ɏ�������.
			 */
			RestoreMessageData( p );

			return E_OK;
		}else{
			/*!
			 * ���M���b�Z�[�W�������̂ɑ��M�҂������Ă���^�X�N���������ꍇ�A
			 * ���M�҂������Ă���^�X�N�͋N��������.
			 */
			wi_TaskWakeup( tsk->Hdr.Id, TTW_SMBF, &(p->SndWaitQue) );
			return E_SYS;
		}
	}
	//! ���^�X�N�̃^�X�N�R���e�L�X�g�Ƀ��b�Z�[�W�i�[�o�b�t�@�̃|�C���^���Z�b�g����.
	tsk = wi_GetTaskObject( TSK_SELF );
	if( !tsk ){
		return E_CTX;
	}
	tsk->Param[0] = msg;
	tsk->Param[1] = 0;

	//! ���b�Z�[�W����M����܂Ń^�X�N���X���[�v������.
	ercd = wi_TaskWait( id, TTW_RMBF, tmout, p->RcvAttr, &(p->RcvWaitQue) );
	if( ercd == E_OK ){
		*size = (INT)tsk->Param[1];
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̏�ԎQ��.
 *
 *	@param	[in]	id		���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[out]	sts		���b�Z�[�W�o�b�t�@��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceMsgBuffer( INT id, WIMBFSTAT *sts )
{
	ER			ercd;
	WIMBFOBJ	*p;

	//! ���b�Z�[�W�o�b�t�@ID�̃I�u�W�F�N�g���擾����.
	p = (WIMBFOBJ *)wi_FindObject( id, TMAX_MAXMBF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���b�Z�[�W�o�b�t�@�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->SndWaitId = wi_GetWaitTaskListFirstId( p->SndWaitQue );
	sts->RcvWaitId = wi_GetWaitTaskListFirstId( p->RcvWaitQue );
	sts->MsgSize   = GetNextMessageSize( p );
	sts->FreeSize  = GetFreeSize( p );
	sts->ExtInfo   = p->ExtInfo;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W���M�҂������Ă���f�[�^���o�b�t�@�ɏ�������.
 *
 *	@param	[in]	p		���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	�Ȃ�.
 */
static void		RestoreMessageData( WIMBFOBJ *p )
{
	WITSKOBJ *tsk;

	tsk = (WITSKOBJ *)(p->SndWaitQue);
	while( tsk ){

		//! ���b�Z�[�W���o�b�t�@�ɏ������߂Ȃ��ꍇ�͏������I���ɂ���.
		if( tsk->Param[0] ){
			if( !PutMesageData( p, (BYTE *)(tsk->Param[0]), (INT)(tsk->Param[1]) ) ){
				break;
			}
		}
		//! ���b�Z�[�W�̑��M��҂��Ă���^�X�N���N��������.
		wi_TaskWakeup( tsk->Hdr.Id, TTW_SMBF, NULL );

		//! �҂��s�񂩂玟�̃^�X�N�����o��.
		tsk = tsk->QueLink;
	}
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̐擪���b�Z�[�W�̃T�C�Y�����擾����.
 *
 *	@param	[in]	p		���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	���b�Z�[�W�o�b�t�@�̐擪���b�Z�[�W�̃T�C�Y.
 */
static INT		GetNextMessageSize( WIMBFOBJ *p )
{
	INT i,pos;
	INT msg_size = 0;

	if( p->GetPos == p->PutPos || !p->MsgBuf ){
		msg_size = 0;
	}else{
		pos = p->GetPos;
		for( i = 0; i < 4; i++ ){
			//! ���b�Z�[�W�̃T�C�Y��1�o�C�g�Â��o��.
			msg_size = (msg_size << 8) + ((INT)p->MsgBuf[pos] & 0xFF);

			pos = wi_IncRingPositon( pos, p->MsgSize );
		}
	}
	return msg_size;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̋󂫗̈�̃T�C�Y���擾����.
 *
 *	@param	[in]	p		���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	���b�Z�[�W�o�b�t�@�̋󂫗̈�̃T�C�Y.
 */
static INT		GetFreeSize( WIMBFOBJ *p )
{
	INT free_size = 0;

	if( p->GetPos == p->PutPos ){
		if( !p->MsgBuf || p->MsgSize == 0 ){
			free_size = 0;
		}else{
			free_size = p->MsgSize - sizeof(DWORD);
		}
	}else{
		if( p->GetPos <= p->PutPos ){
			free_size = p->MsgSize - (p->PutPos - p->GetPos) - sizeof(DWORD);
		}else{
			free_size = (p->GetPos - p->PutPos) - sizeof(DWORD);
		}
	}
	if( free_size < 0 ){
		free_size = 0;
	}
	return free_size;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�Ƀ��b�Z�[�W���i�[����.
 *
 *	@param	[in]	p		���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�̃|�C���^.
 *	@param	[in]	msg		���b�Z�[�W���i�[�����̈�̃|�C���^.
 *	@param	[in]	len		���b�Z�[�W�̃T�C�Y.
 *
 *	@retval	TRUE = OK. / FALSE = NG.
 */
static BOOL	PutMesageData( WIMBFOBJ *p, BYTE* msg, INT len )
{
	INT i;
	INT free_size;

	//! ���b�Z�[�W�o�b�t�@�ɋ󂫂��Ȃ��ꍇ�͏������I������.
	free_size = GetFreeSize( p );
	if( free_size < len ){
		return FALSE;
	}
	/*!
	 * ���b�Z�[�W��T�C�Y�̓r���Ń����O�o�b�t�@��܂�Ԃ�����������Ȃ��̂�
	 * ���b�Z�[�W��T�C�Y��1�o�C�g�Âo�b�t�@�Ɋi�[����.
	 */
	for( i = 0; i < 4; i++ ){
		static int shift[4] = { 24, 16, 8, 0 };

		//! ���b�Z�[�W�̃T�C�Y��1�o�C�g�Âi�[����.
		p->MsgBuf[p->PutPos] = (BYTE)((((DWORD)len) >> shift[i]) & 0xFF);

		//! �o�b�t�@�̏������݈ʒu���X�V����.
		p->PutPos = wi_IncRingPositon( p->PutPos, p->MsgSize );
	}
	//! ���b�Z�[�W�������O�o�b�t�@��܂�Ԃ��ꍇ��2��ɕ����ă��b�Z�[�W���i�[����.
	if( (p->PutPos + len) > p->MsgSize ){
		DWORD size1,size2;

		//! �����O�o�b�t�@�̍Ō�Ƀ��b�Z�[�W�̐擪�f�[�^���R�s�[����.
		size1 = p->MsgSize - p->PutPos;
		memcpy( &p->MsgBuf[p->PutPos], msg, size1 );

		//! �����O�o�b�t�@�̐擪�Ɏc��̃��b�Z�[�W���R�s�[����.
		size2 = len - size1;
		memcpy( p->MsgBuf, &msg[size1], size2 );

		//! �o�b�t�@�̏������݈ʒu���X�V����.
		p->PutPos = size2;
	}else{
		//! �o�b�t�@�Ƀ��b�Z�[�W���R�s�[����.
		memcpy( &p->MsgBuf[p->PutPos], msg, len );

		//! �o�b�t�@�̏������݈ʒu���X�V����.
		p->PutPos += len;
	}
	return (INT)len;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@���烁�b�Z�[�W�����o��.
 *
 *	@param	[in]	p		���b�Z�[�W�o�b�t�@��I�u�W�F�N�g�̃|�C���^.
 *	@param	[out]	msg		���b�Z�[�W���i�[����̈�̃|�C���^.
 *
 *	@retval	���o�������b�Z�[�W�̃T�C�Y.
 */
static INT	GetMessageData( WIMBFOBJ *p, BYTE* msg )
{
	int		i;
	DWORD	len;

	//! ���b�Z�[�W�o�b�t�@�Ƀf�[�^���Ȃ��ꍇ�͏������I������.
	if( !p->MsgBuf || p->GetPos == p->PutPos ){
		return 0;
	}
	/*!
	 * ���b�Z�[�W��T�C�Y�̓r���Ń����O�o�b�t�@��܂�Ԃ�����������Ȃ��̂�
	 * ���b�Z�[�W��T�C�Y��1�o�C�g�Âo�b�t�@������o��.
	 */
	len = 0;
	for( i = 0; i < 4; i++ ){
		//! ���b�Z�[�W�̃T�C�Y��1�o�C�g�Â��o��.
		len = (len << 8) + ((DWORD)p->MsgBuf[p->GetPos] & 0x000000FF);

		//! �o�b�t�@�̓ǂݏo���ʒu���X�V����.
		p->GetPos = wi_IncRingPositon( p->GetPos, p->MsgSize );
	}
	//! ���b�Z�[�W�������O�o�b�t�@��܂�Ԃ��ꍇ��2��ɕ����ă��b�Z�[�W�����o��.
	if( (p->GetPos + len) > p->MsgSize ){
		DWORD size1,size2;

		//! �����O�o�b�t�@�̍Ōォ�烁�b�Z�[�W�̐擪�f�[�^���R�s�[����.
		size1 = p->MsgSize - p->GetPos;
		memcpy( msg, &p->MsgBuf[p->GetPos], size1 );

		//! �����O�o�b�t�@�̐擪����c��̃��b�Z�[�W���R�s�[����.
		size2 = len - size1;
		memcpy( &msg[size1], p->MsgBuf, size2 );

		//! �o�b�t�@�̓ǂݏo���ʒu���X�V����.
		p->GetPos = size2;
	}else{
		//! �o�b�t�@���烁�b�Z�[�W���R�s�[����.
		memcpy( msg, &p->MsgBuf[p->GetPos], len );

		//! �o�b�t�@�̓ǂݏo���ʒu���X�V����.
		p->GetPos += len;
	}
	return (INT)len;
}

/****************************************************************************/
/*!
 *	@brief	�폜�����^�X�N��҂��s�񂩂�폜����.
 *
 *	@param	[in]	id		�폜�����^�X�NID�ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_AllReleaseMsgBuffer( INT id )
{
	WIMBFOBJ *p;

	for( p = (WIMBFOBJ *)ObjList; p; p = (WIMBFOBJ *)p->Hdr.Next ){

		//! �폜�����^�X�N��҂��s�񂩂�폜����.
		p->SndWaitQue = wi_DelWaitTaskList( id, p->SndWaitQue );
		p->RcvWaitQue = wi_DelWaitTaskList( id, p->RcvWaitQue );
	}
}

/* End of file */
