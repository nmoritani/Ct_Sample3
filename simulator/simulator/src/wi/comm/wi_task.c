/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_task.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�^�X�N�@�\).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include <process.h>
#include "wi_task.h"
#include "wi_semaphore.h"
#include "wi_event_flag.h"
#include "wi_mail_box.h"
#include "wi_data_queue.h"
#include "wi_mutex.h"
#include "wi_message_buffer.h"
#include "wi_rendezvous_port.h"
#include "wi_fixed_mempool.h"
#include "wi_variable_mempool.h"

/****************************************************************************
 *
 * ���[�J���֐���`.
 *
 ****************************************************************************/
static unsigned int __stdcall UserTask( void* arg );
static int			ConvertPriority( PRI tskpri );
static WITSKOBJ		*FindTaskObject( INT id, ER *ercd );

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR		*ObjList;		//!< �^�X�N����X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�^�X�N�Ǘ��̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitTask( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�Ǘ��̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitTask( void )
{
	WITSKOBJ *p = (WITSKOBJ *)ObjList;
	while( p ){
		WIHDR *next_ptr;
		next_ptr = p->Hdr.Next;

		//! �C�x���g��n���h�����������.
		if( p->hEvent ){
			CloseHandle( p->hEvent );
		}
		if( p->hThread ){
			//! �X���b�h����~����̂��m�F����.
			wi_DormantThread( p->hThread, 10 );

			//! �X���b�h��n���h�����������.
			CloseHandle( p->hThread );
		}
		//! �^�X�N��I�u�W�F�N�g���������.
		SAFE_RELEASE( p );

		//! ���̃^�X�N��I�u�W�F�N�g�����o��.
		p = (WITSKOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�𐶐�����.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *	@param	[in]	obj		�^�X�N��I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER	wi_CreateTask( INT id, const WITSKOBJ *obj )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�N��I�u�W�F�N�g���쐬����.
	p = (WITSKOBJ *)wi_CreateObject( id, TMAX_MAXTSK, sizeof(WITSKOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !obj->TaskAdr || obj->InitPri == 0 ){
		return E_PAR;
	}
	//! �^�X�N�̏�Ԃ��u�x�~���v�ɂ���.
	p->TaskState = TTS_DMT;

	//! �C�x���g��n���h�����쐬����.
	p->hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	if( !p->hEvent ){
		SAFE_RELEASE( p );
		return E_SYS;
	}
	//! ���X�g�Ƀ^�X�N��ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���[�U�[�^�X�N���N������.
 *
 *	@param	[in]	arg		�^�X�N��I�u�W�F�N�g�\���̂̃|�C���^.
 *
 *	@retval	���0��Ԃ�.
 */
static unsigned __stdcall UserTask( void* arg )
{
	WITSKOBJ *p = (WITSKOBJ *)arg;
	if( p ){
		//! �^�X�N�̏�Ԃ��u���s���v�ɂ���.
		p->TaskState = TTS_RUN;

		//! ���[�U�[�^�X�N���Ăяo��.
		p->TaskAdr( p->StartCode );

		//! �^�X�N�̏�Ԃ��u�x�~���v�ɂ���.
		p->TaskState = TTS_DMT;
	}
	_endthreadex( 0 );
	return 0;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̍폜.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteTask( INT id )
{
	WITSKOBJ	*p      = (WITSKOBJ *)ObjList;
	WIHDR		**b_ptr = &ObjList;

	//! ���^�X�N�͍폜�ł��Ȃ�.
	if( id == TSK_SELF ){
		return E_OBJ;
	}
	//! �s���ȃ^�X�NID�̏ꍇ�̓G���[�ɂ���.
	if( id >= TMAX_MAXTSK ){
		return E_ID;
	}
	while( p ){
		//! �w�肳�ꂽID�ƈ�v����^�X�N���������ꍇ�A�^�X�N���N���[�Y����.
		if( p->Hdr.Id == id ){

			//! �X���b�h���x�~��ԂłȂ��ꍇ�͍폜���Ȃ�.
			if( p->TaskState != TTS_DMT ){
				return E_OBJ;
			}
			//! ���X�g����Y������^�X�N����菜��.
			*b_ptr = (WIHDR *)(p->Hdr.Next);

			if( p->hThread ){
				//! �X���b�h����~���Ă��邱�Ƃ��m�F����.
				wi_DormantThread( p->hThread, 10 );

				//! �X���b�h��n���h�����������.
				CloseHandle( p->hThread );
				 p->hThread = NULL;
			}
			//! �C�x���g��n���h�����������.
			if( p->hEvent ){
				CloseHandle( p->hEvent );
				p->hEvent = NULL;
			}
			//! �҂��s�񂩂�^�X�N���폜����.
			wi_AllReleaseSemaphore( id );
			wi_AllReleaseEvFlag( id );
			wi_AllReleaseMailBox( id );
			wi_AllReleaseDataQueue( id );
			wi_AllReleaseMutex( id );
			wi_AllReleaseMsgBuffer( id );
			wi_AllReleaseRendPort( id );

			//! �������v�[������l�������������u���b�N��ԋp����.
			wi_AllReleaseFixedMemPool( id );
			wi_AllReleaseVarMemPool( id );

			//! �^�X�N�\���̂��������.
			SAFE_RELEASE( p );
			return E_OK;
		}
		//! ���X�g���玟�̃^�X�N�����o��.
		b_ptr = &(p->Hdr.Next);
		p     = (WITSKOBJ *)(p->Hdr.Next);
	}
	return E_NOEXS;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N��.
 *
 *	@param	[in]	id			�^�X�NID�ԍ�.
 *	@param	[in]	start_code	�^�X�N�N���R�[�h.
 *	@param	[in]	exist_stcd	TRUE = �^�X�N�N���R�[�h����.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_StartTask( INT id, DWORD start_code, BOOL exist_stcd )
{
	WITSKOBJ *p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = wi_GetTaskObject( id );
	if( !p ){
		return E_ID;
	}
	if( p->hThread ){
		//! �X���b�h���I�����Ă��邩�ǂ����𒲂ׂ�.
		DWORD code;
		if( !GetExitCodeThread( p->hThread, &code ) ){
			return E_SYS;
		}
		//! �X���b�h���N�����̏ꍇ.
		if( code == STILL_ACTIVE ){
			if( !exist_stcd ){
				//! act_tsk(),iact_tsk()����̌Ăяo���̏ꍇ�͋N���v���񐔂��J�E���g�A�b�v����.
				if( p->ActiveCnt + 1 > TMAX_ACTCNT ){
					return E_QOVR;
				}
				//! �N���v���񐔂��J�E���g�A�b�v����.
				p->ActiveCnt++;
				return E_OK;
			}else{
				//! sta_tsk()����̌Ăяo���̏ꍇ�̓G���[�ɂ���.
				return E_OBJ;
			}
		}
		//! �x�~���̃X���b�h�̃X���b�h�n���h�����N���[�Y����.
		CloseHandle( p->hThread );
		p->hThread = NULL;
	}
	p->SuspendCnt = 0;
	p->WakeupCnt  = 0;
	p->ActiveCnt  = 0;

	if( exist_stcd ){
		//! sta_tsk()����̌Ăяo���̏ꍇ�͈����̋N���R�[�h���g�p����.
		p->StartCode = start_code;
	}else{
		//! act_tsk(),iact_tsk()����̌Ăяo���̏ꍇ��cre_tsk()���̊g�������N���R�[�h�Ƃ���.
		p->StartCode = (DWORD)p->ExtInfo;
	}

	//! �^�X�N�̏�Ԃ��u���s�\��ԁv�ɂ���.
	p->TaskState = TTS_RDY;

	//! �X���b�h���x�~��ԂŋN������.
	p->hThread = (HANDLE)_beginthreadex( NULL, 0, &UserTask, p, CREATE_SUSPENDED, &(p->ThreadId) );

	//! �X���b�h�̗D��x��ݒ肷��.
	SetThreadPriority( p->hThread, ConvertPriority( p->InitPri ) );

	//! �X���b�h�̋x�~��Ԃ���������.
	if( ResumeThread( p->hThread ) == -1 ){
		return E_SYS;
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�N���v���̃L�����Z��.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�L���[�C���O����Ă����N���v���񐔂܂��̓G���[�R�[�h.
 */
int		wi_CancelStartReq( INT id )
{
	int			cnt;
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	//! �N���v���񐔂����o��.
	cnt = p->ActiveCnt;

	//! �N���v���񐔂��N���A����.
	p->ActiveCnt = 0;

	return cnt;
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N�̏I��.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_ExitTask( void )
{
	WITSKOBJ *p;

	wi_CommonLock();

	//! ���^�X�N�̃^�X�N��I�u�W�F�N�g���擾����.
	p = wi_GetTaskObject( TSK_SELF );
	if( p ){
		p->TaskState = TTS_DMT;
	}
	wi_CommonUnlock();

	_endthreadex( 0 );
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N�̏I���ƍ폜.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */

void	wi_ExpendTask( void )
{
	WITSKOBJ *p;

	wi_CommonLock();

	//! ���^�X�N�̃^�X�N��I�u�W�F�N�g���擾����.
	p = wi_GetTaskObject( TSK_SELF );
	if( p ){
		p->TaskState = TTS_DMT;
		p->Hdr.Id    = -1;

		//! �폜�}�[�N�̕t�����^�X�N���V�X�e���Ǘ��^�X�N�o�R�ō폜����.
		wi_DeleteTaskReq( p->Hdr.Id );
	}
	wi_CommonUnlock();

	_endthreadex( 0 );
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋����I��.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_TermTask( INT id )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	//! �X���b�h�������I������.
	if( p->hThread ){
		TerminateThread( p->hThread, 0 );
	}
	p->TaskState = TTS_DMT;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�D��x�̕ύX.
 *
 *	@param	[in]	id			�^�X�NID�ԍ�.
 *	@param	[in]	priority	�^�X�N�D��x.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ChangeTaskPriority( INT id, PRI priority )
{
	int			curpri,newpri;
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! �s���ȃ^�X�N�D��x�̏ꍇ�̓G���[�ɂ���.
	if( priority == 0 ){
		return E_PAR;
	}
	p->TaskPri = priority;

	//! ���݂̃X���b�h�̑��ΗD�揇�ʒl���擾����.
	curpri = GetThreadPriority( p->hThread );

	//! �ύX����^�X�N�D��x���X���b�h�̑��ΗD�揇�ʒl�ɕϊ�����.
	newpri = ConvertPriority( priority );

	//! �X���b�h�̑��ΗD�揇�ʒl���ύX�����ꍇ�A�X���b�h�̃v���C�I���e�B��ύX����.
	if( curpri != newpri ){
		SetThreadPriority( p->hThread, newpri );
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�D��x�̎Q��.
 *
 *	@param	[in]	id			�^�X�NID�ԍ�.
 *	@param	[in]	priority	���݂̃^�X�N�D��x���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceTaskPriority( INT id, PRI *priority )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !priority ){
		return E_PAR;
	}
	//! �^�X�N�̗D��x��߂�l�ɃZ�b�g����.
	*priority = p->TaskPri;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̏�ԎQ��.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *	@param	[in]	sts		�^�X�N��Ԃ��i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceTask( INT id, WITSKSTAT *sts )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	//! �^�X�N�̏�Ԃ��\���̂ɃZ�b�g����.
	sts->ExtInfo    = p->ExtInfo;
	sts->TaskPri    = p->TaskPri;
	sts->TaskState  = p->TaskState;
	sts->EventType  = p->EventType;
	sts->WaitId     = p->WaitId;
	sts->WakeupCnt  = p->WakeupCnt;
	sts->SuspendCnt = p->SuspendCnt;
	sts->TaskAtr    = p->TaskAtr;
	sts->TaskAdr    = p->TaskAdr;
	sts->InitPri    = p->InitPri;
	sts->StackSize  = p->StackSize;
	sts->ActiveCnt  = p->ActiveCnt;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�N���҂�.
 *
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_SleepTask( TMO tmout )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! ���^�X�N�̃^�X�N��I�u�W�F�N�g���擾����.
	p = FindTaskObject( TSK_SELF, &ercd );
	if( !p ){
		return E_OBJ;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! �N���v���J�E���^�����܂��Ă���ꍇ�̓C�x���g�҂������Ȃ��Ő���I���ɂ���.
	if( p->WakeupCnt > 0 ){
		p->WakeupCnt--;
		return E_OK;
	}
	//! �C�x���g�҂�������.
	return wi_TaskWait( p->Hdr.Id, TTW_SLP, tmout, 0, NULL );
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N��.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_WakeupTask( INT id )
{
	ER ercd;

	//! �w�肳�ꂽ�^�X�N�ɑ΂��ăC�x���g�𔭍s����.
	ercd = wi_TaskWakeup( id, TTW_SLP, NULL );

	//! �w�肳�ꂽ�^�X�N��slp_tsk()�ŃC�x���g�҂������Ă��Ȃ��ꍇ�͋N���v���J�E���^��+1����.
	if( ercd == E_OACV ){
		WITSKOBJ *p = wi_GetTaskObject( id );
		if( p ){
			p->WakeupCnt++;
		}
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N���v���𖳌���.
 *
 *	@param	[in]	id			�^�X�NID�ԍ�.
 *	@param	[in]	p_wupcnt	�L���[�C���O����Ă����N���v���񐔂��i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CancelWakeup( INT id, INT *p_wupcnt )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! �N���v���񐔂�߂�l�Ɋi�[����.
	if( p_wupcnt ){
		*p_wupcnt = p->WakeupCnt;
	}
	//! �^�X�N�̋N���v���񐔂��N���A����.
	p->WakeupCnt = 0;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�҂���Ԃ̋�������.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ReleaseWait( INT id )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! ���^�X�N���w�肳�ꂽ�ꍇ�̓G���[�ɂ���.
	if( id == TSK_SELF ){
		return E_OBJ;
	}
	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! �C�x���g�҂������Ă��Ȃ��ꍇ�̓G���[�ɂ���.
	if( p->EventType == 0 ){
		return E_OBJ;
	}
	//! �҂���Ԃ̋��������t���O���Z�b�g���ăC�x���g�𔭍s����.
	p->RelRes = TRUE;
	if( !SetEvent( p->hEvent ) ){
		return E_SYS;
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����҂���Ԃւ̈ڍs.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_SuspendTask( INT id )
{
	DWORD		cnt;
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! �X���b�h�̎��s�𒆒f����.
	cnt = SuspendThread( p->hThread );
	if( cnt == -1 ){
		return E_SYS;
	}
	p->TaskState = TTS_SUS;

	//! �X���b�h�̒��f�J�E���^��+1����.
	p->SuspendCnt = cnt + 1;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����҂���Ԃ���̍ĊJ.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ResumeTask( INT id )
{
	DWORD		cnt;
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! �X���b�h�̎��s���ĊJ����.
	cnt = ResumeThread( p->hThread );
	if( cnt == -1 ){
		return E_SYS;
	}
	//! �X���b�h���ĊJ����Ƃ��ɃX�e�[�^�X���u�^�X�N���s���v�ɖ߂�.
	if( cnt == 1 ){
		if( p->EventType == 0 ){
			p->TaskState = TTS_RUN;
		}else{
			p->TaskState = TTS_WAI;
		}
	}
	//! �X���b�h�����f���Ă��Ȃ������ꍇ�̓G���[�ɂ���.
	if( cnt == 0 ){
		p->SuspendCnt = 0;
		return E_OBJ;
	}
	//! �X���b�h�̒��f�J�E���^��-1����.
	p->SuspendCnt = cnt - 1;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����҂���Ԃ���̋����ĊJ.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ForceResumeTask( INT id )
{
	DWORD		cnt;
	ER			ercd;
	WITSKOBJ	*p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = FindTaskObject( id, &ercd );
	if( !p ){
		return ercd;
	}
	if( !p->hThread ){
		return E_OBJ;
	}
	//! �X���b�h�̃��W���[����Ԃ����������܂ŌJ��Ԃ�.
	do {
		cnt = ResumeThread( p->hThread );
	} while( cnt > 1 );

	if( cnt == -1 ){
		return E_SYS;
	}
	//! �X���b�h���ĊJ����Ƃ��ɃX�e�[�^�X���u�^�X�N���s���v�ɖ߂�.
	if( p->EventType == 0 ){
		p->TaskState = TTS_RUN;
	}else{
		p->TaskState = TTS_WAI;
	}
	//! �X���b�h�̒��f�J�E���^���N���A����.
	p->SuspendCnt = 0;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N�̒x��.
 *
 *	@param	[in]	dlytim	�x������.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DelayTask( TMO dlytim )
{
	ER			ercd;
	WITSKOBJ	*p;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( dlytim == TMO_FEVR ){
		return E_PAR;
	}
	//! ���^�X�N�̃^�X�N��I�u�W�F�N�g���擾����.
	p = FindTaskObject( TSK_SELF, &ercd );
	if( !p || !p->hThread ){
		return E_CTX;
	}
	//! �C�x���g�҂��Ń^�C���A�E�g��������.
	ercd = wi_TaskWait( p->Hdr.Id, TTW_DLY, dlytim, 0, NULL );
	if( ercd == E_TMOUT ){
		ercd  = E_OK;
	}
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�w�肳�ꂽ�^�X�NID�̃I�u�W�F�N�g�����o��.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *
 *	@retval	�^�X�N��I�u�W�F�N�g�\���̂̃|�C���^.
 */
WITSKOBJ	*wi_GetTaskObject( INT id )
{
	//! ���^�X�N�̃I�u�W�F�N�g���擾����.
	if( id == TSK_SELF ){
		DWORD		tid = GetCurrentThreadId();
		WITSKOBJ	*p  = (WITSKOBJ *)ObjList;
		while( p ){
			if( p->ThreadId == tid ){
				return p;
			}
			p = (WITSKOBJ *)(p->Hdr.Next);
		}
		return NULL;
	}
	//! �w�肳�ꂽ�^�X�NID�̃I�u�W�F�N�g���擾����.
	return (WITSKOBJ *)wi_GetObject( id, ObjList );
}

/****************************************************************************/
/*!
 *	@brief	�w�肳�ꂽ�^�X�NID�̃I�u�W�F�N�g�����o��.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *	@param	[in]	ercd	�G���[�R�[�h���i�[����̈�̃|�C���^.
 *
 *	@retval	�^�X�N��I�u�W�F�N�g�\���̂̃|�C���^.
 */
static WITSKOBJ	*FindTaskObject( INT id, ER *ercd )
{
	WITSKOBJ *p;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	p = wi_GetTaskObject( id );
	if( !p ){
		*ercd = (id == TSK_SELF || id >= TMAX_MAXTSK) ? E_ID : E_NOEXS;
		return NULL;
	}
	*ercd = E_OK;
	return p;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�D��x��Windows�X���b�h�̑��ΗD�揇�ʒl�ɕύX����.
 *
 *	@param	[in]	tskpri	�^�X�N�D��x.
 *
 *	@retval	�X���b�h�̑��ΗD�揇�ʒl.
 */
static int		ConvertPriority( PRI tskpri )
{
	if( tskpri < 10 ){
		return THREAD_PRIORITY_ABOVE_NORMAL;
	}else
	if( tskpri < 50 ){
		return THREAD_PRIORITY_NORMAL;
	}else
	if( tskpri < 100 ){
		return THREAD_PRIORITY_BELOW_NORMAL;
	}
	return THREAD_PRIORITY_LOWEST;
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N�̃^�X�NID���擾����.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	���^�X�N�̃^�X�NID.
 */
DWORD	wi_GetActiveTaskId( void )
{
	DWORD		tid = GetCurrentThreadId();
	WITSKOBJ	*p  = (WITSKOBJ *)ObjList;
	while( p ){
		if( p->ThreadId == tid ){
			return p->Hdr.Id;
		}
		p = (WITSKOBJ *)(p->Hdr.Next);
	}
	return 0;
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N���C�x���g�҂��ɂ���.
 *
 *	@param	[in]	wid		�҂��I�u�W�F�N�g��ID.
 *	@param	[in]	type	�C�x���g���.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *	@param	[in]	pri		�I�u�W�F�N�g�̑���.
 *	@param	[out]	que		�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_TaskWait( INT wid, INT type, TMO tmout, ATR pri, WIHDR **que )
{
	DWORD		ret_code;
	ER			ercd;
	WITSKOBJ	*tsk;

	//! �|�[�����O�̏ꍇ�̓^�C���A�E�g�ŏI������.
	if( tmout == TMO_POL ){
		return E_TMOUT;
	}
	//! ���^�X�N�̃^�X�N��I�u�W�F�N�g���擾����.
	tsk = FindTaskObject( TSK_SELF, &ercd );
	if( !tsk ){
		return E_CTX;
	}
	//! �C�x���g��n���h�����쐬���Ă��Ȃ��ꍇ�̓G���[�ɂ���.
	if( !tsk->hEvent ){
		return E_NOEXS;
	}
	//! ���̃I�u�W�F�N�g���C�x���g�҂������Ă���ꍇ�͏������I���ɂ���.
	if( tsk->EventType != 0 ){
		return E_OACV;
	}
	//! �C�x���g��n���h�����u�g�p���v�ɂ���.
	tsk->EventType = type;
	tsk->WaitId    = wid;
	tsk->QueLink   = NULL;
	tsk->TaskState = TTS_WAI;

	//! �^�X�N��҂��s��ɒǉ�����.
	if( que ){
		*que = wi_AddWaitTaskList( TSK_SELF, pri, *que );
	}
	//! �~���[�e�b�N�X����U��������.
	wi_CommonUnlock();

	//! �C�x���g�̔�����҂�.
	ret_code = WaitForSingleObject( tsk->hEvent, wi_CvtTimeOutValue( tmout ) );

	//! �ēx�~���[�e�b�N�X���|����.
	wi_CommonLock();

	//! �^�X�N��҂��s�񂩂�폜����.
	if( que ){
		*que = wi_DelWaitTaskList( TSK_SELF, *que );
	}
	//! �C�x���g��n���h�����u���g�p�v�ɖ߂�.
	tsk->EventType = 0;
	tsk->WaitId    = 0;
	tsk->QueLink   = NULL;
	tsk->TaskState = TTS_RUN;

	switch( ret_code ){
	case WAIT_OBJECT_0:
		if( tsk->DelRes ){
			ercd = E_DLT;
		}else
		if( tsk->RelRes ){
			ercd = E_RLWAI;
		}else{
			ercd = E_OK;
		}
		break;

	case WAIT_TIMEOUT:
		ercd = E_TMOUT;
		break;

	default:
		ercd = E_SYS;
		break;
	}
	tsk->DelRes = FALSE;
	tsk->RelRes = FALSE;
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�҂����Ă���^�X�N���N��������.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *	@param	[in]	type	�C�x���g���.
 *	@param	[out]	que		�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_TaskWakeup( INT id, INT type, WIHDR **que )
{
	ER			ercd;
	WITSKOBJ	*tsk;

	//! �^�X�NID�̃I�u�W�F�N�g���擾����.
	tsk = FindTaskObject( id, &ercd );
	if( !tsk ){
		return ercd;
	}
	//! �C�x���g��n���h�����쐬���Ă��Ȃ��ꍇ�̓G���[�ɂ���.
	if( !tsk->hEvent ){
		return E_NOEXS;
	}
	//! �C�x���g�҂������Ă��Ȃ��ꍇ�̓G���[�ɂ���.
	if( tsk->EventType == 0 ){
		return E_OACV;
	}
	//! �^�X�N���x�~���̏ꍇ�̓G���[�ɂ���.
	if( tsk->TaskState == TTS_DMT ){
		return E_OBJ;
	}
	//! ���̃I�u�W�F�N�g���C�x���g�҂������Ă���ꍇ�̓G���[�ɂ���.
	if( tsk->EventType != type ){
		return E_OACV;
	}
	//! �C�x���g�𔭍s����.
	if( !SetEvent( tsk->hEvent ) ){
		return E_SYS;
	}
	//! �N�������^�X�N��҂��s�񂩂�폜����.
	if( que ){
		*que = wi_DelWaitTaskList( id, *que );
	}
	//! �C�x���g��n���h�����u���g�p�v�ɖ߂�.
	tsk->EventType = 0;
	tsk->WaitId    = 0;
	tsk->QueLink   = NULL;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�҂��s��Ƀ^�X�N��ǉ�����.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *	@param	[in]	pri		�I�u�W�F�N�g�̑���.
 *	@param	[in]	que		�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^.
 */
WIHDR	*wi_AddWaitTaskList( INT id, ATR pri, WIHDR *que )
{
	ER			ercd;
	WITSKOBJ	*add_tsk,*que_tsk;

	//! �w�肳�ꂽ�^�X�N�̃^�X�N��I�u�W�F�N�g���擾����.
	add_tsk = FindTaskObject( id, &ercd );
	if( !add_tsk ){
		return que;
	}
	//! �҂��s��Ƀ^�X�N���Ȃ��ꍇ�́A���̃^�X�N��҂��s��̐擪�ɂ���.
	if( !que ){
		return (WIHDR *)add_tsk;
	}
	if( pri & TA_TPRI ){
		/*!
		 * �҂��s��̐擪�^�X�N���w�肳�ꂽ�^�X�N�̕����D��x�������ꍇ��
		 * �w�肳�ꂽ�^�X�N��҂��s��̐擪�ɂ���.
		 */
		que_tsk = (WITSKOBJ *)que;
		if( que_tsk->TaskPri > add_tsk->TaskPri ){
			add_tsk->QueLink = que_tsk;
			return (WIHDR *)add_tsk;
		}
		/*!
		 * �҂��s�񒆂̃^�X�N�̗D��x���w�肳�ꂽ�^�X�N�̗D��x�������Ȃ����Ƃ����
		 * �w�肳�ꂽ�^�X�N��}������.
		 */
		while( que_tsk->QueLink ){
			if( que_tsk->QueLink->TaskPri > add_tsk->TaskPri ){
				add_tsk->QueLink = que_tsk->QueLink;
				break;
			}
			que_tsk = que_tsk->QueLink;
		}
		que_tsk->QueLink = add_tsk;
	}else{
		//! FIFO���̏ꍇ�A�҂��s��̍Ō�Ƀ^�X�N��ǉ�����.
		que_tsk = (WITSKOBJ *)que;
		while( que_tsk->QueLink ){
			que_tsk = que_tsk->QueLink;
		}
		que_tsk->QueLink = add_tsk;
	}
	return que;
}

/****************************************************************************/
/*!
 *	@brief	�҂��s�񂩂�^�X�N���폜����.
 *
 *	@param	[in]	id		�^�X�NID�ԍ�.
 *	@param	[in]	que		�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^.
 */
WIHDR	*wi_DelWaitTaskList( INT id, WIHDR *que )
{
	ER			ercd;
	WITSKOBJ	*del_tsk,*que_tsk;

	//! �҂��s��Ƀ^�X�N���Ȃ��ꍇ�������Ȃ�.
	if( !que ){
		return NULL;
	}
	//! �^�X�N��I�u�W�F�N�g���擾����.
	del_tsk = FindTaskObject( id, &ercd );
	if( !del_tsk ){
		return que;
	}
	/*!
	 * �҂��s��̐擪���w�肳�ꂽ�^�X�N�̏ꍇ�͑҂��s��̐擪�^�X�N���폜����.
	 * (�߂�l�͎��̃^�X�N��I�u�W�F�N�g�̃|�C���^�ƂȂ�.)
	 */
	que_tsk = (WITSKOBJ *)que;
	if( que_tsk->Hdr.Id == del_tsk->Hdr.Id ){
		WIHDR *wk        = (WIHDR *)del_tsk->QueLink;
		del_tsk->QueLink = NULL;
		return wk;
	}
	/*!
	 * �҂��s�񂩂�w�肳�ꂽ�^�X�N���폜����.
	 * (�҂��s��̐擪�̃^�X�N�͕ς��Ȃ�.)
	 */
	while( que_tsk->QueLink ){
		if( que_tsk->QueLink->Hdr.Id == del_tsk->Hdr.Id ){
			que_tsk->QueLink = del_tsk->QueLink;
			del_tsk->QueLink = NULL;
			break;
		}
		que_tsk = que_tsk->QueLink;
	}
	return que;
}

/****************************************************************************/
/*!
 *	@brief	�҂��s��̐擪�̃^�X�N��ID�ԍ����擾����.
 *
 *	@param	[in]	que		�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	�҂��s��̐擪�̃^�X�N��ID�ԍ�.
 */
DWORD	wi_GetWaitTaskListFirstId( WIHDR *que )
{
	//! �҂��s��Ƀ^�X�N���Ȃ��ꍇ�������Ȃ�.
	if( !que ){
		return 0;
	}
	//! �҂��s��̐擪�̃^�X�N�̃^�X�NID�ԍ���Ԃ�.
	return que->Id;
}

/****************************************************************************/
/*!
 *	@brief	���\�[�X���폜�����Ƃ��ɑ҂��s��ɂ���^�X�N���������.
 *
 *	@param	[in]	que		�҂��s��̐擪�̃^�X�N��I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	�Ȃ�.
 */
void	wi_WakeupDelResource( WIHDR *que )
{
	WITSKOBJ *p;

	p = (WITSKOBJ *)que;
	while( p ){
		//! �C�x���g��n���h�����u���g�p�v�ɖ߂�.
		p->EventType = 0;
		p->WaitId    = 0;
		if( p->hThread && p->hEvent ){
			//! ���\�[�X���폜����邱�Ƃ������t���O���Z�b�g���ăC�x���g�𔭍s����.
			p->DelRes = TRUE;
			SetEvent( p->hEvent );
		}
		//! �҂��s�񂩂玟�̃^�X�N��I�u�W�F�N�g�����o��.
		p = p->QueLink;

		//! �҂��L���[����^�X�N���폜����.
		if (p != NULL) {
			p->QueLink = NULL;
		}
	}
}

/* End of file */
