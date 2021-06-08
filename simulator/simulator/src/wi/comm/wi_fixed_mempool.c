/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_fixed_mempool.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�Œ蒷�������v�[��).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_fixed_mempool.h"

/****************************************************************************
 *
 * ���[�J���֐���`.
 *
 ****************************************************************************/
static BYTE	*GetFreeMem( WIMPFOBJ *mpf, INT tskid );
static void	ReleaseFreeMem( WIMPFOBJ *mpf, WIHDR* blk );
static void	MemAllocWaitTask( WIMPFOBJ *mpf );

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR	*ObjList;			//!< �Œ蒷�������v�[������X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitFixedMemPool( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitFixedMemPool( void )
{
	WIHDR		*next_ptr;
	WIMPFOBJ	*p = (WIMPFOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! �������o�b�t�@���������.
		SAFE_RELEASE( p->MemBuf );

		//! �Œ蒷�������v�[����I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃������v�[����I�u�W�F�N�g�\���̂����o��.
		p = (WIMPFOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̐���.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *	@param	[in]	obj		�������v�[����I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateFixedMemPool( INT id, const WIMPFOBJ *obj )
{
	INT			i;
	DWORD		size;
	WIHDR		*ptr;
	ER			ercd;
	WIMPFOBJ	*p;

	//! �Œ蒷�������v�[����I�u�W�F�N�g���쐬����.
	p = (WIMPFOBJ *)wi_CreateObject( id, TMAX_MAXMPF, sizeof(WIMPFOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( obj->BlockCnt <= 0 || obj->BlockSize <= 0 ){
		return E_PAR;
	}
	//! �������u���b�N��1�u���b�N�̃T�C�Y���v�Z����.
	size = obj->BlockSize + sizeof(WIHDR);

	//! �������v�[���̃o�b�t�@���m�ۂ���.
	p->MemBuf = (BYTE*)malloc( obj->BlockCnt * size );
	if( !p->MemBuf ){
		SAFE_RELEASE( p );
		return E_NOMEM;
	}
	//! �m�ۂ����o�b�t�@���N���A����.
	memset( p->MemBuf, 0, obj->BlockCnt * size );

	//! ���g�p�������u���b�N�L���[�Ƀo�b�t�@��o�^����.
	ptr = (WIHDR *)(p->MemBuf);
	for( i = 0; i < obj->BlockCnt - 1; i++ ){
		ptr->Next = (WIHDR *)((DWORD)ptr + size);
		ptr       = (WIHDR *)((DWORD)ptr + size);
	}
	p->FreeQue = (WIHDR *)(p->MemBuf);
	p->UsedQue = NULL;
	p->WaitQue = NULL;

	//! ���X�g�ɌŒ蒷�������v�[����ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̍폜.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteFixedMemPool( INT id )
{
	ER			ercd;
	WIMPFOBJ	*p;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPFOBJ *)wi_FindObject( id, TMAX_MAXMPF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y�����郁�����v�[������菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->WaitQue );

	//! �������v�[���̃o�b�t�@���������.
	SAFE_RELEASE( p->MemBuf );

	//! �Œ蒷�������v�[����I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������u���b�N�̊l��.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *	@param	[out]	buf		�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_GetFixedMemPool( INT id, VP buf, TMO tmout )
{
	ER			ercd;
	WIMPFOBJ	*p;
	WITSKOBJ	*tsk;
	BYTE		*blk;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPFOBJ *)wi_FindObject( id, TMAX_MAXMPF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !buf ){
		return E_PAR;
	}
	//! �^�X�N�ȊO����̌Ăяo���̏ꍇ�̓G���[�ɂ���.
	tsk = wi_GetTaskObject( TSK_SELF );
	if( !tsk ){
		return E_CTX;
	}
	//! ���g�p�̃������u���b�N���擾����.
	blk = GetFreeMem( p, tsk->Hdr.Id );

	//! ���g�p�̃������u���b�N���Ȃ��ꍇ�A�������u���b�N���ԋp�����܂Ń^�X�N���X���[�v������.
	if( !blk ){
		ercd = wi_TaskWait( id, TTW_MPF, tmout, p->Attribute, &(p->WaitQue) );
		if( ercd != E_OK ){
			return ercd;
		}
		blk = tsk->Param[0];
	}
	//! �݂��o���������u���b�N���烊���N�w�b�_���폜����.
	*((DWORD *)buf) = (DWORD)blk;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������u���b�N�̕ԋp.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *	@param	[in]	buf		�ԋp���郁�����u���b�N�̃A�h���X.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ReleaseFixedMemPool( INT id, VP buf )
{
	ER			ercd;
	WIMPFOBJ	*p;
	WIHDR		*blk,*ptr;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPFOBJ *)wi_FindObject( id, TMAX_MAXMPF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !buf ){
		return E_PAR;
	}
	//! �ԋp���ꂽ�A�h���X���烁�����u���b�N�̃w�b�_���̃A�h���X���v�Z����.
	blk = (WIHDR *)((DWORD)buf - sizeof(WIHDR) );

	//! �݂��o�����������u���b�N�L���[�ɕԋp���ꂽ�������u���b�N�����邩�ǂ����𒲂ׂ�.
	for( ptr = p->UsedQue; ptr && ptr != blk; ptr = ptr->Next ) ;
	if( !ptr ){
		return E_OBJ;
	}
	//! �ԋp���ꂽ�������u���b�N���������.
	ReleaseFreeMem( p, blk );

	//! �������u���b�N�l���҂��̃^�X�N������ꍇ�A�������u���b�N��݂��o���ă^�X�N���N������.
	MemAllocWaitTask( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̎Q��.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *	@param	[out]	sts		�������v�[����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceFixedMemPool( INT id, WIMPFSTAT *sts )
{
	ER			ercd;
	WIMPFOBJ	*p;
	WIHDR		*ptr;
	INT			cnt;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPFOBJ *)wi_FindObject( id, TMAX_MAXMPF, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���g�p�̃������u���b�N�����J�E���g����.
	cnt = 0;
	ptr = p->FreeQue;
	while( ptr ){
		ptr = ptr->Next;
		cnt++;
	}
	//! �Œ蒷�������v�[���̏�Ԃ��\���̂ɃZ�b�g����.
	sts->WaitId    = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->FreeBlock = cnt;
	sts->ExtInfo   = p->ExtInfo;
	sts->MemBuf    = p->MemBuf;
	sts->BlockSize = p->BlockSize;
	sts->BlockCnt  = p->BlockCnt;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�폜�����^�X�N���m�ۂ����������u���b�N���������.
 *
 *	@param	[in]	id		�폜�����^�X�NID�ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_AllReleaseFixedMemPool( INT id )
{
	WIHDR		*ptr;
	WIMPFOBJ	*p = (WIMPFOBJ *)ObjList;

	while( p ){
		//! �݂��o�����������u���b�N�L���[�ɍ폜�����^�X�N�ɑ݂��o���������������邩�ǂ����𒲂ׂ�.
		ptr = p->UsedQue;
		while( ptr ){
			WIHDR *next_ptr;
			next_ptr = ptr->Next;

			//! �݂��o�������������������ꍇ�A�݂��o�������������������.
			if( ptr->Id == id ){
				ReleaseFreeMem( p, ptr );
			}
			ptr = next_ptr;
		}
		//! �҂��s�񂩂���ł���^�X�N���폜����.
		if( p->WaitQue ){
			p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );
		}
		//! �������u���b�N�l���҂��̃^�X�N������ꍇ�A�������u���b�N��݂��o���ă^�X�N���N������.
		MemAllocWaitTask( p );

		//! ���̃������v�[���\���̂������o��.
		p = (WIMPFOBJ *)(p->Hdr.Next);
	}
}

/****************************************************************************/
/*!
 *	@brief	�󂢂Ă��郁�����u���b�N���擾����.
 *
 *	@param	[in]	mpf		�Œ蒷�������v�[����I�u�W�F�N�g�̃|�C���^.
 *	@param	[in]	tskid	���������擾����^�X�N��ID.
 *
 *	@retval	�擾�����������u���b�N�̃|�C���^.
 */
static BYTE	*GetFreeMem( WIMPFOBJ *mpf, INT tskid )
{
	WIHDR *blk,*ptr;

	if( !mpf->FreeQue ){
		return NULL;
	}
	//! �݂��o���������u���b�N�𖢎g�p�������u���b�N�L���[�̐擪������o��.
	blk = mpf->FreeQue;

	//! ���g�p�������u���b�N�L���[�̐擪����݂��o�����������u���b�N���폜����.
	mpf->FreeQue = mpf->FreeQue->Next;

	//! �݂��o�����������u���b�N�L���[�ɑ݂��o�����������u���b�N��ǉ�����.
	if( !mpf->UsedQue ){
		mpf->UsedQue = blk;
	}else{
		for( ptr = mpf->UsedQue; ptr->Next; ptr = ptr->Next ) ;
		ptr->Next = blk;
	}
	blk->Next = NULL;
	blk->Id   = tskid;

	//! �݂��o���������u���b�N���烊���N�w�b�_���폜����.
	return (BYTE *)((DWORD)blk + sizeof(WIHDR));
}

/****************************************************************************/
/*!
 *	@brief	�������u���b�N��ԋp���ċ󂫃u���b�N�ɂ���.
 *
 *	@param	[in]	mpf		�Œ蒷�������v�[����I�u�W�F�N�g�̃|�C���^.
 *	@param	[in]	blk		�ԋp���郁�����u���b�N�̃|�C���^.
 *
 *	@retval	�Ȃ�.
 */
static void		ReleaseFreeMem( WIMPFOBJ *mpf, WIHDR* blk )
{
	WIHDR *ptr;

	//! ���g�p�������u���b�N�L���[�ɕԋp���ꂽ�������u���b�N��ǉ�����.
	if( !mpf->FreeQue ){
		mpf->FreeQue = blk;
	}else{
		for( ptr = mpf->FreeQue; ptr->Next; ptr = ptr->Next ) ;
		ptr->Next = blk;
	}
	//! �݂��o�����̃������u���b�N�L���[����ԋp���ꂽ�������u���b�N���폜����.
	if( mpf->UsedQue == blk ){
		mpf->UsedQue  = blk->Next;
	}else{
		ptr = mpf->UsedQue;
		while( ptr ){
			if( ptr->Next == blk ){
				ptr->Next = blk->Next;
				break;
			}
			ptr = ptr->Next;
		}
	}
	//! �ԋp���ꂽ�������u���b�N�̃����N�|�C���^���N���A����.
	blk->Next = NULL;
	blk->Id   = 0;
}

/****************************************************************************/
/*!
 *	@brief	�������u���b�N�l���҂������Ă���^�X�N�Ƀ�������݂��o��.
 *
 *	@param	[in]	mpf		�Œ蒷�������v�[����I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	�Ȃ�.
 */
static void		MemAllocWaitTask( WIMPFOBJ *mpf )
{
	WITSKOBJ *tsk;

	tsk = (WITSKOBJ *)mpf->WaitQue;
	while( tsk ){
		//! �󂢂Ă��郁�����u���b�N���擾����.
		tsk->Param[0] = GetFreeMem( mpf, tsk->Hdr.Id );
		if( !tsk->Param[0] ){
			break;
		}
		//! �X���[�v���Ă���^�X�N���N��������.
		wi_TaskWakeup( tsk->Hdr.Id, TTW_MPF, NULL );

		//! �҂��s�񂩂玟�̃^�X�N�����o��.
		tsk = tsk->QueLink;
	}
}

/* End of file */
