/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_interrupt.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (���荞�݋@�\).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "wi_interrupt.h"

/****************************************************************************
 *
 * ���荞�݃X���b�h�ւ̃��b�Z�[�W.
 *
 ****************************************************************************/
#define	WM_SYSTEM_EXIT	(WM_USER + 1)		//!< �V�X�e���̏I��.
#define	WM_INTRRUPT_REQ	(WM_USER + 2)		//!< ���荞�ݗv��.

/****************************************************************************
 *
 * ���[�J���֐���`.
 *
 ****************************************************************************/
static unsigned int __stdcall	IntrTask( void* arg );
static void			CallIntrruptHandler( INT no );

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR		*ObjList;			//!< ���荞�݃n���h������X�g�̃|�C���^.
static HANDLE		IntrThread;			//!< ���荞�݃X���b�h�̃n���h��.
static DWORD		IntrTid;			//!< ���荞�݃X���b�h�̎��ʎq.
static BOOL			CpuLockFlg;			//!< TRUE = CPU���b�N��.

/****************************************************************************/
/*!
 *	@brief	���荞�݋@�\�̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitInterrupt( void )
{
	unsigned int tid;

	ObjList    = NULL;
	IntrThread = NULL;
	IntrTid    = 0;
	CpuLockFlg = FALSE;

	//! ���荞�݃X���b�h���N������.
	IntrThread = (HANDLE)_beginthreadex( NULL, 0, &IntrTask, NULL, 0, &tid );

	//! �^�X�N�̗D��x��ݒ肷��.
	SetThreadPriority( IntrThread, THREAD_PRIORITY_HIGHEST );

}

/****************************************************************************/
/*!
 *	@brief	���荞�݋@�\�̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitInterrupt( void )
{
	WIHDR		*next_ptr;
	WIINTOBJ	*p;

	//! �V�X�e���Ǘ��X���b�h���I��������.
	if( IntrThread ){
		//! ���荞�݃X���b�h�ɏI����ʒm����.
		PostThreadMessage( IntrTid, WM_SYSTEM_EXIT, 0, 0 );

		//! - �X���b�h����~����̂��m�F����.
		wi_DormantThread( IntrThread, 1000 );

		//! - ���荞�݃X���b�h�̃n���h�����������.
		CloseHandle( IntrThread );
	}
	p = (WIINTOBJ *)ObjList;
	while( p ){
		next_ptr = p->Hdr.Next;

		//! ���荞�݃n���h���\���̂��������.
		SAFE_RELEASE( p );

		//! ���̊��荞�݃n���h���\���̂����o��.
		p = (WIINTOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	���荞�݃n���h���̒�`.
 *
 *	@param	[in]	no		���荞�݃n���h���ԍ�.
 *	@param	[in]	obj		���荞�݃n���h��.�I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DefineIntrruptHander( INT no, const WIINTOBJ *obj )
{
	ER			ercd;
	WIINTOBJ	*p;

	//! ���ɐ������Ă���n���h���ԍ��̏ꍇ�̓G���g���A�h���X���X�V����.
	p = (WIINTOBJ *)wi_GetObject( no, ObjList );
	if( p ){
		p->IntrAdr = obj->IntrAdr;
		p->Enabled = FALSE;
		p->IntrCnt = 0;
		return E_OK;
	}
	//! ���荞�݃n���h����I�u�W�F�N�g���쐬����.
	p = (WIINTOBJ *)wi_CreateObject( no, TMAX_MAXINT, sizeof(WIINTOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g�Ɋ��荞�݃n���h����ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���荞�݂̋֎~.
 *
 *	@param	[in]	no		���荞�݃n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DisableIntrrupt( INT no )
{
	ER			ercd;
	WIINTOBJ	*p;

	//! �n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WIINTOBJ *)wi_FindObject( no, TMAX_MAXINT, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���荞�݂��֎~����.
	p->Enabled = FALSE;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���荞�݂̋���.
 *
 *	@param	[in]	no		���荞�݃n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_EnableIntrrupt( INT no )
{
	ER			ercd;
	WIINTOBJ	*p;

	//! �n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WIINTOBJ *)wi_FindObject( no, TMAX_MAXINT, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���荞�݂�������.
	p->Enabled = TRUE;

	//! ���荞�݂��ۗ�����Ă����ꍇ�͊��荞�݂𔭐�������.
	if( p->IntrCnt > 0 ){
		wi_IntrruptRequest( no );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	CPU���b�N��Ԃւ̈ڍs.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_LockCPU( void )
{
	//! CPU���b�N�t���O���Z�b�g����.
	CpuLockFlg = TRUE;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	CPU���b�N��Ԃ̉���.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_UnLockCPU( void )
{
	//! CPU���b�N�t���O����������.
	CpuLockFlg = FALSE;

	//! �ۗ�����Ă������荞�݃n���h���̌Ăяo�����s��.
	wi_DelayedIntrrupt();

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	CPU���b�N��Ԃ̎Q��.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	TRUE = CPU���b�N��. / FALSE = CPU�񃍃b�N��.
 */
BOOL	wi_IsCPULock( void )
{
	return CpuLockFlg;
}

/****************************************************************************/
/*!
 *	@brief	�ۗ�����Ă������荞�݃n���h���̌Ăяo�����s��.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_DelayedIntrrupt( void )
{
	WIINTOBJ *p = (WIINTOBJ *)ObjList;
	while( p ){
		//! ���荞�݂��ۗ�����Ă����ꍇ�͊��荞�݂𔭐�������.
		if( p->IntrCnt > 0 ){
			wi_IntrruptRequest( p->Hdr.Id );
		}
		p = (WIINTOBJ *)p->Hdr.Next;
	}
}

/****************************************************************************/
/*!
 *	@brief	���荞�݂𔭐�������.
 *
 *	@param	[in]	no		���荞�݃n���h���ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_IntrruptRequest( INT no )
{
	if( IntrTid ){
		PostThreadMessage( IntrTid, WM_INTRRUPT_REQ, (WPARAM)no, 0 );
	}
}

/****************************************************************************/
/*!
 *	@brief	���荞�ݗv�����N���A����.
 *
 *	@param	[in]	no		���荞�݃n���h���ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_ClearIntrruptRequest( INT no )
{
	ER			ercd;
	WIINTOBJ	*p;

	//! �n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WIINTOBJ *)wi_FindObject( no, TMAX_MAXINT, ObjList, &ercd );
	if( p ){
		//! ���荞�ݗv�����N���A����.
		p->IntrCnt = 0;
	}
}

/****************************************************************************/
/*!
 *	@brief	���荞�݃^�X�N.
 *
 *	@param	[in]	arg		�^�X�N���\�[�X�\���̂̃|�C���^.
 *
 *	@retval	���0��Ԃ�.
 */
static unsigned __stdcall IntrTask( void* arg )
{
	MSG	msg;

	//! �X���b�h���ʎq���擾����.
	IntrTid = GetCurrentThreadId();

	//! ���b�Z�[�W���[�v.
	while( GetMessage( &msg, NULL, 0, 0 ) ){

		//! �V�X�e���̏I���̏ꍇ�̓��b�Z�[�W���[�v�𔲂���.
		if( msg.message == WM_SYSTEM_EXIT ){
			break;
		}
		switch( msg.message ){
		case WM_INTRRUPT_REQ:
			CallIntrruptHandler( (INT)msg.wParam );
			break;
		}
	}
	_endthreadex( 0 );
	return 0;
}

/****************************************************************************/
/*!
 *	@brief	���荞�݃n���h�����Ăяo��.
 *
 *	@param	[in]	no		���荞�݃n���h���ԍ�.
 *
 *	@retval	�Ȃ�.
 */
static void		CallIntrruptHandler( INT no )
{
	wi_CommonLock();
	do {
		FP			intr_adr;
		ER			ercd;
		WIINTOBJ	*p;

		//! ���荞�݃n���h���\���̂����o��.
		p = (WIINTOBJ *)wi_FindObject( no, TMAX_MAXINT, ObjList, &ercd );
		if( !p ){
			break;
		}
		//! ���荞�݃G���g����A�h���X���Ȃ��ꍇ�͌Ăяo���Ȃ�.
		if( !p->IntrAdr ){
			break;
		}
		//! ���荞�݋֎~�̏ꍇ�͌Ăяo���Ȃ�.
		if( !p->Enabled || wi_IsCPULock() ){
			p->IntrCnt++;
			break;
		}
		p->IntrCnt = 0;

		intr_adr = p->IntrAdr;

		wi_CommonUnlock();

		//! ���荞�݃n���h�����Ăяo��.
		intr_adr();
		return;

	} while( FALSE );

	wi_CommonUnlock();
}

/* End of file */
