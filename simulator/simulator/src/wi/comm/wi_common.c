/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_common.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (���̑����ʊ֐�).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "wi_common.h"
#include "wi_task.h"
#include "wi_cycle_handler.h"
#include "wi_alarm_handler.h"

/****************************************************************************
 *
 * ���[�J���֐���`.
 *
 ****************************************************************************/
static unsigned int __stdcall TimerTask( void* arg );

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static HANDLE		CommMutex;			//!< �T�[�r�X�R�[���S�̂Ŏg�p����~���[�e�b�N�X�̃n���h��.
static HANDLE		TimerThread;		//!< �����^�C�}��X���b�h�̃n���h��.
static BOOL			ExitFlag;			//!< TRUE = �V�X�e���̏I���v��.
static DWORDLONG	SystemTime;			//!< �V�X�e������.

/****************************************************************************/
/*!
 *	@brief	���ʊ֐��̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	TRUE = OK. / FALSE = NG.
 */
BOOL	wi_CommonInit( void )
{
	unsigned int tid;

	CommMutex   = NULL;
	TimerThread = NULL;
	ExitFlag    = FALSE;
	SystemTime  = 0;

	//! �~���[�e�b�N�X���쐬����.
	CommMutex = CreateMutex( NULL, FALSE, NULL );
	if( !CommMutex ){
		return FALSE;
	}
	//! �����^�C�}��X���b�h���N������.
	TimerThread = (HANDLE)_beginthreadex( NULL, 0, &TimerTask, NULL, 0, &tid );

	//! �^�X�N�̗D��x��ݒ肷��.
	SetThreadPriority( TimerThread, THREAD_PRIORITY_ABOVE_NORMAL );

	return TRUE;
}

/****************************************************************************/
/*!
 *	@brief	���ʊ֐��̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_CommonQuit( void )
{
	ExitFlag = TRUE;

	if( TimerThread ){
		//! �X���b�h����~����̂��m�F����.
		wi_DormantThread( TimerThread, 1000 );

		//! �����^�C�}��X���b�h�̃n���h�����������.
		CloseHandle( TimerThread );
	}

	//! �쐬�����~���[�e�b�N�X���N���[�Y����.
	if( CommMutex ){
		CloseHandle( CommMutex );
		CommMutex = NULL;
	}
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�����b�N����.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_CommonLock( void )
{
	//! �~���[�e�b�N�X�̏��L�����l������.
	if( CommMutex ){
		WaitForSingleObject( CommMutex, INFINITE );
	}
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X���A�����b�N����.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_CommonUnlock( void )
{
	//! �~���[�e�b�N�X�̏��L�����������.
	if( CommMutex ){
		ReleaseMutex( CommMutex );
	}
}

/****************************************************************************/
/*!
 *	@brief	�X���b�h���~������.
 *
 *	@param	[in]	hThread		�X���b�h��n���h��.
 *	@param	[in]	wait_time	�X���b�h��~�̑҂�����.
 *
 *	@retval	�Ȃ�.
 */
void	wi_DormantThread( HANDLE hThread, DWORD wait_time )
{
	DWORD	i;
	DWORD	loop = (wait_time / 10) + 1;

	for( i = 0; i < loop; i++ ){
		//! �X���b�h�̏I���R�[�h���擾����.
		DWORD code;
		if( !GetExitCodeThread( hThread, &code ) ){
			TerminateThread( hThread, 0 );
			return;
		}
		//! �X���b�h����~���Ă���ꍇ�A�������I������.
		if( code != STILL_ACTIVE ){
			return;
		}
		Sleep( 10 );
	}
	//! �X���b�h�������I�ɏI������.
	TerminateThread( hThread, 0 );
}

/****************************************************************************/
/*!
 *	@brief	�V�X�e�������̐ݒ�.
 *
 *	@param	[in]	stime	�ݒ肷�鎞��.
 *
 *	@retval	�Ȃ�.
 */
void	wi_SetSystemTime( DWORDLONG stime )
{
	SystemTime = stime;
}

/****************************************************************************/
/*!
 *	@brief	�V�X�e�������̎Q��.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�V�X�e������.
 */
DWORDLONG	wi_GetSystemTime( void )
{
	return SystemTime;
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N�̃^�X�NID���擾����.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	���^�X�N�̃^�X�NID.
 */
ID		wi_GetTaskId( void )
{
	return wi_GetActiveTaskId();
}

/****************************************************************************/
/*!
 *	@brief	�I�u�W�F�N�g����X�g�ɃI�u�W�F�N�g��ǉ�����.
 *
 *	@param	[in]	new_obj		�ǉ�����I�u�W�F�N�g�\���̂̃|�C���^.
 *	@param	[out]	obj_list	�I�u�W�F�N�g�\���̃��X�g�̃|�C���^.
 *
 *	@retval	�Ȃ�.
 */
void	wi_AddObject( LPWIHDR new_obj, LPWIHDR *obj_list )
{
	LPWIHDR p = *obj_list;
	for( ; p && p->Next; p = p->Next ) ;

	if( !p ){
		*obj_list = new_obj;
	}else{
		p->Next = new_obj;
	}
}

/****************************************************************************/
/*!
 *	@brief	�I�u�W�F�N�g����X�g����I�u�W�F�N�g���폜����.
 *
 *	@param	[in]	del_obj		�폜����I�u�W�F�N�g�\���̂̃|�C���^.
 *	@param	[out]	obj_list	�I�u�W�F�N�g�\���̃��X�g�̃|�C���^.
 *
 *	@retval	�Ȃ�.
 */
void	wi_DelObject( LPWIHDR del_obj, LPWIHDR *obj_list )
{
	if( *obj_list ){
		//! ���X�g�̐擪�̃I�u�W�F�N�g���폜����I�u�W�F�N�g�̏ꍇ.
		if( *obj_list == del_obj ){
			*obj_list =  del_obj->Next;
		}else{
			LPWIHDR p;
			for( p = *obj_list; p->Next; p = p->Next ){
				//! ��v����I�u�W�F�N�g���������ꍇ�A���X�g����폜����.
				if( p->Next == del_obj ){
					p->Next  = del_obj->Next;
					break;
				}
			}
		}
	}
}

/****************************************************************************/
/*!
 *	@brief	�w�肳�ꂽ���ʎq�̃I�u�W�F�N�g�\���̂����o��.
 *
 *	@param	[in]	id			�I�u�W�F�N�g���ʎq.
 *	@param	[out]	obj_list	�I�u�W�F�N�g�\���̃��X�g�̃|�C���^.
 *
 *	@retval	�I�u�W�F�N�g�\���̂̃|�C���^.
 */
void	*wi_GetObject( INT id, LPWIHDR obj_list )
{
	while( obj_list ){
		if( obj_list->Id == id ){
			return obj_list;
		}
		obj_list = obj_list->Next;
	}
	return NULL;
}

/****************************************************************************/
/*!
 *	@brief	�I�u�W�F�N�g���쐬����.
 *
 *	@param	[in]	id			�I�u�W�F�N�gID�ԍ�.
 *	@param	[in]	max_id		�I�u�W�F�N�gID�ԍ��̍ő�l.
 *	@param	[in]	size		�I�u�W�F�N�gID�ԍ��̍ő�l.
 *	@param	[in]	param		�I�u�W�F�N�g�������̃|�C���^.
 *	@param	[in]	obj_list	�I�u�W�F�N�g����X�g�̃|�C���^.
 *	@param	[out]	ercd		�G���[�R�[�h���i�[����̈�̃|�C���^.
 *
 *	@retval	�쐬�����I�u�W�F�N�g�̃|�C���^.
 */
WIHDR	*wi_CreateObject( INT id, INT max_id, INT size, const void *param, WIHDR *obj_list, ER *ercd )
{
	WIHDR *p;

	//! �s����ID�̏ꍇ�̓G���[�ɂ���.
	if( id == 0 || id >= max_id ){
		*ercd = E_ID;
		return NULL;
	}
	//! ���ɐ������Ă���I�u�W�F�N�g�̏ꍇ�̓G���[�ɂ���.
	if( wi_GetObject( id, obj_list ) != NULL ){
		*ercd = E_OBJ;
		return NULL;
	}
	//! �I�u�W�F�N�g�\���̂��m�ۂ���.
	p = (WIHDR *)malloc( size );
	if( !p ){
		*ercd = E_NOMEM;
		return NULL;
	}
	//! �I�u�W�F�N�g�̐�������ۑ�����.
	memcpy( p, param, size );
	p->Id = id;
	*ercd = E_OK;
	return p;
}

/****************************************************************************/
/*!
 *	@brief	�w�肵��ID�ԍ��̃I�u�W�F�N�g�����X�g���猟������.
 *
 *	@param	[in]	id			�I�u�W�F�N�gID�ԍ�.
 *	@param	[in]	max_id		�I�u�W�F�N�gID�ԍ��̍ő�l.
 *	@param	[in]	obj_list	�I�u�W�F�N�g����X�g�̃|�C���^.
 *	@param	[out]	ercd		�G���[�R�[�h���i�[����̈�̃|�C���^.
 *
 *	@retval	���o�����I�u�W�F�N�g�̃|�C���^.
 */
WIHDR	*wi_FindObject( INT id, INT max_id, WIHDR *obj_list, ER *ercd )
{
	WIHDR *p;

	//! �s����ID�̏ꍇ�̓G���[�ɂ���.
	if( id == 0 || id >= max_id ){
		*ercd = E_ID;
		return NULL;
	}
	//! ���X�g����I�u�W�F�N�g���擾����.
	p = (WIHDR *)wi_GetObject( id, obj_list );
	if( !p ){
		*ercd = E_NOEXS;
		return NULL;
	}
	*ercd = E_OK;
	return p;
}

/****************************************************************************/
/*!
 *	@brief	�����O�o�b�t�@�̃J�E���^���C���N�������g����.
 *
 *	@param	[in]	pos		�����O�o�b�t�@�̃J�E���^.
 *	@param	[in]	size	�����O�o�b�t�@�̃T�C�Y.
 *
 *	@retval	�C���N�������g��̃J�E���^�l.
 */
DWORD	wi_IncRingPositon( DWORD pos, DWORD size )
{
	return ((pos + 1) >= size) ? 0 : (pos + 1);
}

/****************************************************************************/
/*!
 *	@brief	iTRON�̃^�C�}���Ԃ�Windows�p�^�C�}���Ԃɕϊ�����.
 *
 *	@param	[in]	tmout		iTRON�p�^�C�}�ݒ莞��.
 *
 *	@retval	Windows�p�^�C�}�̎���.
 */
DWORD	wi_CvtTimeOutValue( TMO tmout )
{
	switch( tmout ){
	  case TMO_POL : return 0;
	  case TMO_FEVR: return INFINITE;
	  default      : return tmout;
	}
}

/****************************************************************************/
/*!
 *	@brief	�����^�C�}��^�X�N.
 *
 *	@param	[in]	arg		�^�X�N���\�[�X�\���̂̃|�C���^.
 *
 *	@retval	���0��Ԃ�.
 */
static unsigned __stdcall TimerTask( void* arg )
{
	while( !ExitFlag ){

		DWORD btime,ntime,dtime;

		//! �X���[�v�O�̃^�C���J�E���^���擾����.
		btime = GetTickCount();

		//! ��莞�ԃX���[�v������.
//		timeBeginPeriod( 1 );
		Sleep( CYCLETIME );
//		timeEndPeriod ( 1 );

		//! �X���[�v��̃^�C���J�E���^���擾����.
		ntime = GetTickCount();

		//! ���ۂɃX���[�v�������Ԃ��v�Z����.
		if( ntime >= btime ){
			dtime = ntime - btime;
		}else{
			dtime = btime - ntime;
		}
		//! �V�X�e���������J�E���g�A�b�v����.
		SystemTime += dtime;

		//! �����N���n���h�����Ăяo��.
		wi_CycleTimer( SystemTime );

		//! �A���[����n���h�����Ăяo��.
		wi_CallAlarmHandler( SystemTime );
	}
	_endthreadex( 0 );
	return 0;
}

/* End of file */
