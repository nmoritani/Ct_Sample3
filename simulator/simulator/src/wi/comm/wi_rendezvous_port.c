/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_rendezvous_port.cpp
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�����f�u).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_rendezvous_port.h"

/****************************************************************************
 *
 * ���[�J���֐���`.
 *
 ****************************************************************************/
static WITSKOBJ	*SatisfyRendezvous( WITSKOBJ *tsk, UINT ptn );
static ER		CreateRdv( INT tskid, INT rsize );
static void		DeleteRdv( INT no );

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static INT			RdvSeqNo;		//!< �����f�u�ԍ��̐����p�J�E���^.
static WIHDR		*PortList;		//!< �����f�u�|�[�g����X�g�̃|�C���^.
static WIHDR		*RdvList;		//!< �����f�u����X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�����f�u�̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitRendPort( void )
{
	RdvSeqNo = 0;
	PortList = NULL;
	RdvList  = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitRendPort( void )
{
	WIHDR		*next_ptr;
	WIPOROBJ	*port;
	WIRDVOBJ	*rdv;

	//! �����f�u�|�[�g��I�u�W�F�N�g���������.
	port = (WIPOROBJ *)PortList;
	while( port ){
		next_ptr = port->Hdr.Next;

		//! �����f�u�|�[�g��I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( port );

		//! ���̃����f�u�|�[�g��I�u�W�F�N�g�\���̂����o��.
		port = (WIPOROBJ *)next_ptr;
	}

	//! �������������f�u��I�u�W�F�N�g���������.
	rdv = (WIRDVOBJ *)RdvList;
	while( rdv ){
		next_ptr = rdv->Hdr.Next;

		//! �����f�u��I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( rdv );

		//! ���̃����f�u��I�u�W�F�N�g�\���̂����o��.
		rdv = (WIRDVOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�|�[�g�̐���.
 *
 *	@param	[in]	id		�����f�u��|�[�gID�ԍ�.
 *	@param	[in]	obj		�����f�u��I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateRendPort( INT id, const WIPOROBJ *obj )
{
	ER			ercd;
	WIPOROBJ	*p;

	//! �s���Ȉ����̏ꍇ�̓G���[�ɂ���.
	if( obj->MaxCalMsg == 0 || obj->MaxRepMsg == 0 ){
		return E_PAR;
	}
	//! �����f�u�|�[�g��I�u�W�F�N�g���쐬����.
	p = (WIPOROBJ *)wi_CreateObject( id, TMAX_MAXPOR, sizeof(WIPOROBJ), obj, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g�Ƀ����f�u�|�[�g��ǉ�����.
	wi_AddObject( (WIHDR *)p, &PortList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�|�[�g�̍폜.
 *
 *	@param	[in]	id		�����f�u�|�[�gID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteRendPort( INT id )
{
	ER			ercd;
	WIPOROBJ	*p;

	//! �����f�u�|�[�gID�̃I�u�W�F�N�g���擾����.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y�����郉���f�u�|�[�g����菜��.
	wi_DelObject( (WIHDR *)p, &PortList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->CalWaitQue );
	wi_WakeupDelResource( p->AcpWaitQue );

	//! �����f�u�|�[�g��I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�Ăяo��.
 *
 *	@param	[in]	id			�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	ptn			�Ăяo�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	msg			���b�Z�[�W�̃A�h���X.
 *	@param	[in]	csize		�Ăяo�����b�Z�[�W�̃T�C�Y.
 *	@param	[out]	rsize		�������b�Z�[�W�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CallRendPort( INT id, UINT ptn, VP msg, INT csize, INT *rsize, TMO tmout )
{
	ER			ercd;
	WIPOROBJ	*p;
	WITSKOBJ	*acp_tsk,*cal_tsk;

	//! �����f�u�|�[�gID�̃I�u�W�F�N�g���擾����.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !rsize || p->MaxCalMsg < csize ){
		return E_PAR;
	}
	//! ���^�X�N�̃^�X�N�R���e�L�X�g�����o��.
	cal_tsk = wi_GetTaskObject( TSK_SELF );
	if( !cal_tsk ){
		return E_CTX;
	}
	cal_tsk->Param[0] = (VP)ptn;
	cal_tsk->Param[1] = (VP)msg;
	cal_tsk->Param[2] = (VP)csize;

	//! �����f�u��t�҂������Ă���^�X�N�ɑ΂��ă����f�u���������邩�ǂ����𒲂ׂ�.
	acp_tsk = SatisfyRendezvous( (WITSKOBJ *)(p->AcpWaitQue), ptn );

	if( !acp_tsk ){
		//! �����f�u����������܂Ń^�X�N���X���[�v������.
		ercd = wi_TaskWait( id, TTW_CAL, tmout, p->Attribute, &(p->CalWaitQue) );
		if( ercd == E_OK ){
			*rsize = (INT)cal_tsk->Param[2];
		}
	}else{
		//! �������������f�u��o�^����.
		ercd = CreateRdv( cal_tsk->Hdr.Id, p->MaxRepMsg );
		if( ercd != E_OK ){
			return ercd;
		}
		//! �������������f�u�ԍ�����t�^�X�N�ɒʒm����.
		acp_tsk->Param[3] = (VP)RdvSeqNo;

		//! �����f�u��t�^�X�N�Ƀ����f�u�Ăяo�����b�Z�[�W���R�s�[����.
		if( acp_tsk->Param[1] && msg && csize > 0 ){
			memcpy( acp_tsk->Param[1], msg, csize );
			acp_tsk->Param[2] = (VP)csize;
		}else{
			acp_tsk->Param[2] = 0;
		}
		wi_TaskWakeup( acp_tsk->Hdr.Id, TTW_ACP, &(p->AcpWaitQue) );

		//! �����f�u���I������܂Ń^�X�N���X���[�v������.
		ercd = wi_TaskWait( RdvSeqNo, TTW_RDV, tmout, 0, NULL );
		if( ercd == E_OK ){
			*rsize = (INT)cal_tsk->Param[2];
		}
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�󂯕t��.
 *
 *	@param	[in]	id			�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	ptn			�󂯕t�����I�������̃r�b�g�p�^�[��.
 *	@param	[out]	no			�����f�u�ԍ����i�[����̈�̃|�C���^.
 *	@param	[out]	msg			�Ăяo�����b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[out]	size		�Ăяo�����b�Z�[�W�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_AcceptRendPort( INT id, UINT ptn, INT *no, VP msg, INT *size, TMO tmout )
{
	ER			ercd;
	WIPOROBJ	*p;
	WITSKOBJ	*cal_tsk,*acp_tsk;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !no || !size ){
		return E_PAR;
	}
	//! �����f�u�|�[�gID�̃I�u�W�F�N�g���擾����.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���^�X�N�̃^�X�N�R���e�L�X�g�����o��.
	acp_tsk = wi_GetTaskObject( TSK_SELF );
	if( !acp_tsk ){
		return E_CTX;
	}
	acp_tsk->Param[0] = (VP)ptn;
	acp_tsk->Param[1] = (VP)msg;
	acp_tsk->Param[2] = (VP)0;

	//! �����f�u�Ăяo�������Ă���^�X�N�ɑ΂��ă����f�u���������邩�ǂ����𒲂ׂ�.
	cal_tsk = SatisfyRendezvous( (WITSKOBJ *)(p->CalWaitQue), ptn );

	if( !cal_tsk ){
		//! �����f�u����������܂Ń^�X�N���X���[�v������.
		ercd = wi_TaskWait( id, TTW_ACP, tmout, p->Attribute, &(p->AcpWaitQue) );
		if( ercd != E_OK ){
			return ercd;
		}
		*size = (INT)acp_tsk->Param[2];
		*no   = (INT)acp_tsk->Param[3];
	}else{
		//! �������������f�u��o�^����.
		ercd = CreateRdv( cal_tsk->Hdr.Id, p->MaxRepMsg );
		if( ercd != E_OK ){
			return ercd;
		}
		//! �����f�u�ԍ���߂�l�ɃZ�b�g����.
		*no = RdvSeqNo;

		//! �Ăяo�����b�Z�[�W���Ăяo�����^�X�N����R�s�[����.
		if( cal_tsk->Param[1] && (INT)cal_tsk->Param[2] > 0 ){
			memcpy( msg, cal_tsk->Param[1], (INT)cal_tsk->Param[2] );
			*size = (INT)cal_tsk->Param[2];
		}else{
			*size = 0;
		}
		//! �Ăяo�����^�X�N��҂��s�񂩂�폜����.
		p->CalWaitQue = wi_DelWaitTaskList( cal_tsk->Hdr.Id, p->CalWaitQue );

		//! �Ăяo�����^�X�N�̃C�x���g�҂���Ԃ��u�����f�u�I���҂��v�ɂ���.
		cal_tsk->EventType = TTW_RDV;
		cal_tsk->WaitId    = RdvSeqNo;
		cal_tsk->QueLink   = NULL;

		ercd = E_OK;
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�̉�
 *
 *	@param	[in]	id		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	ptn		�󂯕t�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	no		�����f�u�ԍ�.
 *	@param	[in]	msg		�Ăяo�����b�Z�[�W�̃|�C���^.
 *	@param	[in]	size	�Ăяo�����b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_FowardRendPort( INT id, UINT ptn, INT no, VP msg, INT size )
{
	ER			ercd;
	WIPOROBJ	*p;
	WITSKOBJ	*acp_tsk,*rdv_tsk;
	WIRDVOBJ	*rdv;

	//! �����f�u�|�[�gID�̃I�u�W�F�N�g���擾����.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �����f�u�ԍ��̃I�u�W�F�N�g���擾����.
	rdv = (WIRDVOBJ *)wi_FindObject( no, TMAX_MAXRDV, RdvList, &ercd );
	if( !rdv ){
		return E_OBJ;
	}
	//! �����f�u�I���҂������Ă���^�X�N�̃R���e�L�X�g���擾����.
	rdv_tsk = wi_GetTaskObject( rdv->TaskId );
	if( !rdv_tsk ){
		return E_OBJ;
	}
	//! �����f�u��t�҂������Ă���^�X�N�ɑ΂��ă����f�u���������邩�ǂ����𒲂ׂ�.
	acp_tsk = SatisfyRendezvous( (WITSKOBJ *)(p->AcpWaitQue), ptn );
	if( !acp_tsk ){

		//! �����f�u�I���҂��^�X�N�̃C�x���g�҂���Ԃ��u�����f�u�����҂��v�ɂ���.
		rdv_tsk->EventType = TTW_CAL;
		rdv_tsk->WaitId    = p->Hdr.Id;

		//! �����f�u�Ăяo���҂��s��Ƀ����f�u�I���҂��^�X�N��ǉ�����.
		p->CalWaitQue = wi_AddWaitTaskList( rdv->TaskId, p->Attribute, p->CalWaitQue );
	}else{
		//! �������������f�u��o�^����.
		ercd = CreateRdv( rdv_tsk->Hdr.Id, p->MaxRepMsg );
		if( ercd != E_OK ){
			return ercd;
		}
		acp_tsk->Param[2] = 0;
		acp_tsk->Param[3] = (VP)RdvSeqNo;

		//! �����f�u��t�^�X�N�Ƀ����f�u�񑗃��b�Z�[�W���R�s�[����.
		if( acp_tsk->Param[1] && msg && size > 0 ){
			memcpy( acp_tsk->Param[1], msg, size );
			acp_tsk->Param[2] = (VP)size;
		}
		//! �����f�u��t�҂������Ă���^�X�N���N������.
		wi_TaskWakeup( acp_tsk->Hdr.Id, TTW_ACP, &(p->AcpWaitQue) );
	}
	//! �����f�u��I�u�W�F�N�g���폜����.
	DeleteRdv( no );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�̏I��.
 *
 *	@param	[in]	rdvno		�����f�u�ԍ�.
 *	@param	[in]	msg			�ԓ����b�Z�[�W�̃|�C���^.
 *	@param	[in]	size		�ԓ����b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ReplayRendPort( INT no, VP msg, INT size )
{
	ER			ercd;
	WIRDVOBJ	*rdv;
	WITSKOBJ	*tsk;

	//! �����f�u�ԍ��̃I�u�W�F�N�g���擾����.
	rdv = (WIRDVOBJ *)wi_FindObject( no, TMAX_MAXRDV, RdvList, &ercd );
	if( !rdv ){
		return E_OBJ;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( rdv->MaxRepMsg < size ){
		return E_PAR;
	}
	//! �����f�u�I���҂������Ă���^�X�N�̃R���e�L�X�g���擾����.
	tsk = wi_GetTaskObject( rdv->TaskId );
	if( !tsk ){
		ercd = E_OBJ;
	}else{
		//! �ԓ����b�Z�[�W�������f�u�I���҂������Ă���^�X�N�̃��b�Z�[�W�̈�ɃR�s�[����.
		ercd = E_OK;
		if( tsk->Param[1] && msg ){
			if( (INT)tsk->Param[2] < size ){
				tsk->Param[2] = 0;
				ercd          = E_PAR;
			}else{
				memcpy( tsk->Param[1], msg, size );
				tsk->Param[2] = (VP)size;
			}
		}else{
			tsk->Param[2] = 0;
		}
		//! �����f�u�I���҂������Ă���^�X�N���N������.
		wi_TaskWakeup( rdv->TaskId, TTW_RDV, NULL );
	}
	//! �����f�u��I�u�W�F�N�g���폜����.
	DeleteRdv( no );
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�|�[�g�̏�ԎQ��.
 *
 *	@param	[in]	id		�����f�u�|�[�gID�ԍ�.
 *	@param	[out]	sts		�����f�u�|�[�g��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceRendPort( INT id, WIPORSTAT *sts )
{
	ER			ercd;
	WIPOROBJ	*p;

	//! �����f�u�|�[�gID�̃I�u�W�F�N�g���擾����.
	p = (WIPOROBJ *)wi_FindObject( id, TMAX_MAXPOR, PortList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �����f�u�|�[�g�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->CalWaitId = wi_GetWaitTaskListFirstId( p->CalWaitQue );
	sts->AcpWaitId = wi_GetWaitTaskListFirstId( p->AcpWaitQue );
	sts->ExtInfo   = p->ExtInfo;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u��Ԃ̎Q��.
 *
 *	@param	[in]	no		�����f�u�ԍ�.
 *	@param	[out]	sts		�����f�u��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceRendStat( INT no, WIRDVSTAT *sts )
{
	ER			ercd;
	WIRDVOBJ	*p;

	//! �����f�u�ԍ��̃I�u�W�F�N�g���擾����.
	p = (WIRDVOBJ *)wi_FindObject( no, TMAX_MAXRDV, RdvList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �����f�u�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->WaitId = p->TaskId;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u���������邩�ǂ����𒲂ׂ�.
 *
 *	@param	[in]	tsk		�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^..
 *	@param	[in]	ptn		�I�������̃r�b�g�p�^�[��.
 *
 *	@retval	�����f�u�����������^�X�N��I�u�W�F�N�g�̃|�C���^.
 */
static WITSKOBJ	*SatisfyRendezvous( WITSKOBJ *tsk, UINT ptn )
{
	while( tsk ){
		if( ((UINT)(tsk->Param[0]) & ptn) != 0 ){
			break;
		}
		tsk = tsk->QueLink;
	}
	return tsk;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�̐���.
 *
 *	@param	[in]	tskid	�����f�u�I���҂��̃^�X�N��ID�ԍ�.
 *	@param	[in]	rsize	�ԓ����b�Z�[�W�̍ő�T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
static ER	CreateRdv( INT tskid, INT rsize )
{
	WIRDVOBJ *rdv;

	//! �����f�u�ԍ����C���N�������g����.
	if( RdvSeqNo >= TMAX_MAXRDV ){
		RdvSeqNo  = 1;
	}else{
		RdvSeqNo++;
	}
	//! �����f�u��I�u�W�F�N�g�\���̂��m�ۂ���.
	rdv = (WIRDVOBJ *)malloc( sizeof(WIRDVOBJ) );
	if( !rdv ){
		return E_NOMEM;
	}
	memset( rdv, 0, sizeof(WIRDVOBJ) );
	rdv->Hdr.Id    = RdvSeqNo;
	rdv->TaskId    = tskid;
	rdv->MaxRepMsg = rsize;

	//! ���X�g�ɐ������������f�u��ǉ�����.
	wi_AddObject( (WIHDR *)rdv, &RdvList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�̍폜.
 *
 *	@param	[in]	no		�����f�u�ԍ�.
 *
 *	@retval	�Ȃ�.
 */
static void	DeleteRdv( INT no )
{
	ER			ercd;
	WIRDVOBJ	*p;

	//! �����f�u�|�[�gID�̃I�u�W�F�N�g���擾����.
	p = (WIRDVOBJ *)wi_FindObject( no, TMAX_MAXRDV, RdvList, &ercd );
	if( p ){
		//! ���X�g����Y�����郉���f�u�|�[�g����菜��.
		wi_DelObject( (WIHDR *)p, &RdvList );

		//! �����f�u��I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );
	}
}

/****************************************************************************/
/*!
 *	@brief	�폜�����^�X�N��҂��s�񂩂�폜����.
 *
 *	@param	[in]	id		�폜�����^�X�NID�ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_AllReleaseRendPort( INT id )
{
	WIPOROBJ *p;

	for( p = (WIPOROBJ *)PortList; p; p = (WIPOROBJ *)p->Hdr.Next ){

		//! �폜�����^�X�N��҂��s�񂩂�폜����.
		p->CalWaitQue = wi_DelWaitTaskList( id, p->CalWaitQue );
		p->AcpWaitQue = wi_DelWaitTaskList( id, p->AcpWaitQue );
	}
}

/* End of file */
