/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron4.c
 *
 *	@brief	iTRON(Ver4.0)�̃T�[�r�X�R�[��.
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <stdio.h>
#include "kprintf.h"
#include "wi_config.h"

#ifdef	__ITRON4__
#include "win_itron4.h"
#include "wi_task.h"
#include "wi_semaphore.h"
#include "wi_event_flag.h"
#include "wi_data_queue.h"
#include "wi_mail_box.h"
#include "wi_mutex.h"
#include "wi_message_buffer.h"
#include "wi_rendezvous_port.h"
#include "wi_fixed_mempool.h"
#include "wi_variable_mempool.h"
#include "wi_cycle_handler.h"
#include "wi_alarm_handler.h"
#include "wi_systemmgr.h"
#include "wi_interrupt.h"

/***************************************
 *
 * �^�X�N�Ǘ��@�\.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�^�X�N�̐���.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[in]	pk_ctsk	�^�X�N�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_tsk( ID tskid, const T_CTSK *pk_ctsk )
{
	ER			ercd;
	WITSKOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_ctsk ){
		return E_PAR;
	}
	//! �^�X�N���������R�s�[����.
	memset( &obj, 0, sizeof(WITSKOBJ) );
	obj.TaskAtr   = pk_ctsk->tskatr;
	obj.TaskAdr   = pk_ctsk->task;
	obj.TaskPri   = pk_ctsk->itskpri;
	obj.InitPri   = pk_ctsk->itskpri;
	obj.StackSize = pk_ctsk->stksz;
	obj.ExtInfo   = pk_ctsk->exinf;

	wi_CommonLock();

	//! �^�X�N�𐶐�����.
	ercd = wi_CreateTask( (DWORD)tskid, &obj );

	//! TA_ACT���ݒ肳��Ă���ꍇ�̓^�X�N���N������.
	if( ercd == E_OK && (pk_ctsk->tskatr & TA_ACT) != 0 ){
		wi_StartTask( (DWORD)tskid, 0, FALSE );
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_ctsk	�^�X�N�������\���̂̃|�C���^.
 *
 *	@retval	���������^�X�N�̃^�X�NID�܂��̓G���[�R�[�h.
 */
ER_ID	acre_tsk( const T_CTSK *pk_ctsk )
{
	ER_ID		ercd;
	DWORD		tskid;
	WITSKOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_ctsk ){
		return E_PAR;
	}
	//! �^�X�N���������R�s�[����.
	memset( &obj, 0, sizeof(WITSKOBJ) );
	obj.TaskAtr   = pk_ctsk->tskatr;
	obj.TaskAdr   = pk_ctsk->task;
	obj.TaskPri   = pk_ctsk->itskpri;
	obj.InitPri   = pk_ctsk->itskpri;
	obj.StackSize = pk_ctsk->stksz;
	obj.ExtInfo   = pk_ctsk->exinf;

	wi_CommonLock();
	for( tskid = 1; tskid < TMAX_MAXTSK; tskid++ ){

		//! �^�X�N�𐶐�����.
		ercd = wi_CreateTask( tskid, &obj );
		if( ercd == E_OK ){

			//! �߂�l�𐶐������^�X�NID�ԍ��ɂ���.
			ercd = (ER_ID)tskid;

			//! TA_ACT���ݒ肳��Ă���ꍇ�̓^�X�N���N������.
			if( (pk_ctsk->tskatr & TA_ACT) != 0 ){
				wi_StartTask( tskid, 0, FALSE );
			}
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̍폜.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N���폜����.
	ercd = wi_DeleteTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N��.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		act_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N���N������.
	ercd = wi_StartTask( tskid, 0, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N�� (��^�X�N�R���e�L�X�g����̌ďo���p).
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		iact_tsk( ID tskid )
{
	return act_tsk( tskid );
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�N���v���̃L�����Z��.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER_UINT		can_act( ID tskid )
{
	ER_UINT ercd;

	wi_CommonLock();

	//! �^�X�N�̋N���v�����L�����Z������.
	ercd = (ER_UINT)wi_CancelStartReq( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N��.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[in]	stacd	�^�X�N�N���R�[�h.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		sta_tsk( ID tskid, VP_INT stacd )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N���N������.
	ercd = wi_StartTask( tskid, (DWORD)stacd, TRUE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N�̏I��.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	ext_tsk( void )
{
	//! �^�X�N���I��������.
	wi_ExitTask();
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N�̏I���ƍ폜.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	exd_tsk( void )
{
	//! �^�X�N���I�������ăR���e�L�X�g���폜����.
	wi_ExpendTask();
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋����I��.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ter_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�������I������.
	ercd = wi_TermTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�D��x�̕ύX.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[in]	tskpri	�^�X�N�D��x.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		chg_pri( ID tskid, PRI tskpri )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�̗D��x��ύX����.
	ercd = wi_ChangeTaskPriority( tskid, tskpri );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�D��x�̎Q��.
 *
 *	@param	[in]	tskid		�^�X�NID�ԍ�.
 *	@param	[out]	p_tskpri	���݂̃^�X�N�D��x���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_pri( ID tskid, PRI *p_tskpri )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�̗D��x���擾����.
	ercd = wi_RefarenceTaskPriority( tskid, p_tskpri );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̏�ԎQ��.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[out]	pk_rtsk	�^�X�N��Ԃ��i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_tsk( ID tskid, T_RTSK *pk_rtsk )
{
	ER			ercd;
	WITSKSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rtsk ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �擾�����^�X�N�̗��̂�߂�l�Ƃ��č\���̂ɃZ�b�g����.
	ercd = wi_RefarenceTask( tskid, &sts );
	if( ercd == E_OK ){
		pk_rtsk->tskstat = sts.TaskState;
		pk_rtsk->tskpri  = sts.TaskPri;
		pk_rtsk->tskbpri = sts.TaskPri;
		pk_rtsk->tskwait = sts.EventType;
		pk_rtsk->wobjid  = sts.WaitId;
		pk_rtsk->lefttmo = 0;
		pk_rtsk->actcnt  = sts.ActiveCnt;
		pk_rtsk->wupcnt  = sts.WakeupCnt;
		pk_rtsk->suscnt  = sts.SuspendCnt;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̏�ԎQ�� (�ȈՔ�).
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[out]	pk_rtst	�^�X�N��Ԃ��i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_tst( ID tskid, T_RTST *pk_rtst )
{
	ER			ercd;
	WITSKSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rtst ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �^�X�N�̏�Ԃ��ȈՎQ�Ƃ���.
	ercd = wi_RefarenceTask( tskid, &sts );

	//! �擾�����^�X�N�̗��̂�߂�l�Ƃ��č\���̂ɃZ�b�g����.
	if( ercd == E_OK ){
		pk_rtst->tskstat = sts.TaskState;
		pk_rtst->tskwait = sts.WaitId;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * �^�X�N�t�������@�\.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�N���҂�(�^�C���A�E�g�Ȃ�).
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		slp_tsk( void )
{
	//! �^�C���A�E�g�Ȃ��Ń^�X�N���N���҂��ɂ���.
	return tslp_tsk( TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�N���҂�(�^�C���A�E�g����).
 *
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tslp_tsk( TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N���N���҂��ɂ���.
	ercd = wi_SleepTask( tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N��.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wup_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N���N������.
	ercd = wi_WakeupTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N�� (��^�X�N�R���e�L�X�g����̌ďo���p).
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		iwup_tsk( ID tskid )
{
	return wup_tsk( tskid );
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̋N���v���𖳌���.
 *
 *	@param	[in]	tskid		�^�X�NID�ԍ�.
 *
 *	@retval	�L���[�C���O����Ă����N���v���񐔂܂��̓G���[�R�[�h.
 */
ER_UINT		can_wup( ID tskid )
{
	ER	ercd;
	INT	wupcnt;

	wi_CommonLock();

	//! �^�X�N�ւ̋N���v�����N���A����.
	ercd = wi_CancelWakeup( tskid, &wupcnt );
	if( ercd == E_OK ){
		ercd = wupcnt;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�҂���Ԃ̋�������.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rel_wai( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�̑҂���Ԃ������I�ɉ�������.
	ercd = wi_ReleaseWait( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�҂���Ԃ̋������� (��^�X�N�R���e�L�X�g����̌ďo���p).
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		irel_wai( ID tskid )
{
	return rel_wai( tskid );
}

/****************************************************************************/
/*!
 *	@brief	�����҂���Ԃւ̈ڍs.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		sus_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�𒆒f(�����҂����)�ɂ���.
	ercd = wi_SuspendTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����҂���Ԃ���̍ĊJ.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rsm_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N��҂���Ԃ���ĊJ����.
	ercd = wi_ResumeTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����҂���Ԃ���̋����ĊJ.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		frsm_tsk( ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �����҂������Ă���^�X�N�������I�ɍĊJ������.
	ercd = wi_ForceResumeTask( tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���^�X�N�̒x��.
 *
 *	@param	[in]	dlytim	�x������.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		dly_tsk( DLYTIME dlytim )
{
	ER	ercd;

	wi_CommonLock();

	ercd = wi_DelayTask( (TMO)(dlytim) );

	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * �^�X�N��O�����@�\.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�^�X�N��O�����̒�`.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[in]	pk_dtex	�^�X�N��O������`�p�\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		def_tex( ID tskid, T_DTEX *pk_dtex )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N��O�����̗v��.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[in]	pk_dtex	�v������^�X�N��O�����̗�O�v��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ras_tex( ID tskid, TEXPTN rasptn )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N��O�����̗v�� (��^�X�N�R���e�L�X�g����̌ďo���p).
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[in]	pk_dtex	�v������^�X�N��O�����̗�O�v��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		iras_tex( ID tskid, TEXPTN rasptn )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N��O�����̋֎~.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		dis_tex( void )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N��O�����̋���.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ena_tex( void )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N��O�����֎~��Ԃ̎Q��.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	TRUE = �^�X�N��O�����֎~ / FALSE = �^�X�N��O��������.
 */
INT		sns_tex( void )
{
	return TRUE;
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N��O�����̏�ԎQ��.
 *
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *	@param	[out]	pk_rtex	�^�X�N��O������Ԃ��i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_tex( ID tskid, T_RTEX *pk_rtex )
{
	return E_NOSPT;
}


/***************************************
 *
 * ������ʐM�@�\ (�Z�}�t�H).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�̐���.
 *
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *	@param	[in]	pk_csem	�Z�}�t�H�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_sem( ID semid, const T_CSEM *pk_csem )
{
	ER			ercd;
	WISEMOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_csem ){
		return E_PAR;
	}
	//! �Z�}�t�H���������R�s�[����.
	memset( &obj, 0, sizeof(WISEMOBJ) );
	obj.Attribute = pk_csem->sematr;
	obj.SemCnt    = pk_csem->isemcnt;
	obj.MaxCnt    = pk_csem->maxsem;

	wi_CommonLock();

	//! �Z�}�t�H�𐶐�����.
	ercd = wi_CreateSemaphore( semid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_csem	�Z�}�t�H�������\���̂̃|�C���^.
 *
 *	@retval	�Z�}�t�HID�ԍ��܂��̓G���[�R�[�h.
 */
ER_ID	acre_sem( const T_CSEM *pk_csem )
{
	ID			semid;
	ER_ID		ercd;
	WISEMOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_csem ){
		return E_PAR;
	}
	//! �Z�}�t�H���������R�s�[����.
	memset( &obj, 0, sizeof(WISEMOBJ) );
	obj.Attribute = pk_csem->sematr;
	obj.SemCnt    = pk_csem->isemcnt;
	obj.MaxCnt    = pk_csem->maxsem;

	wi_CommonLock();

	for( semid = 1; semid < TMAX_MAXSEM; semid++ ){

		//! �Z�}�t�H�𐶐�����.
		ercd = wi_CreateSemaphore( semid, &obj );
		if( ercd == E_OK ){
			ercd  = semid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�̍폜.
 *
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_sem( ID semid )
{
	ER ercd;

	wi_CommonLock();

	//! �Z�}�t�H���폜����.
	ercd = wi_DeleteSemaphore( semid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�����̕ԋp.
 *
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		sig_sem( ID semid )
{
	ER ercd;

	wi_CommonLock();

	//! �Z�}�t�H�̎�����ԋp����.
	ercd = wi_SignalSemaphore( semid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�����̕ԋp (��^�X�N�R���e�L�X�g����̌ďo���p).
 *
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		isig_sem( ID semid )
{
	//! ��^�X�N�R���e�L�X�g����Z�}�t�H�̎������������.
	return sig_sem( semid );
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�����̊l�� (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wai_sem( ID semid )
{
	//! �^�C���A�E�g�Ȃ��ŃZ�}�t�H�������l������.
	return twai_sem( semid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�����̊l�� (�|�[�����O).
 *
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pol_sem( ID semid )
{
	//! �l���҂��Ȃ��ŃZ�}�t�H�������l������.
	return twai_sem( semid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H�����̊l�� (�^�C���A�E�g����).
 *
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		twai_sem( ID semid, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �Z�}�t�H�̎������l������.
	ercd = wi_WaitSemaphore( semid, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Z�}�t�H��Ԃ̎Q��.
 *
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *	@param	[out]	pk_rsem	�Z�}�t�H��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_sem( ID semid, T_RSEM *pk_rsem )
{
	ER			ercd;
	WISEMSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rsem ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �Z�}�t�H�̏�Ԃ��擾����.
	ercd = wi_RefarenceSemaphore( semid, &sts );
	if( ercd == E_OK ){
		pk_rsem->wtskid = sts.WaitId;
		pk_rsem->semcnt = sts.SemCnt;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * ������ʐM�@�\ (�C�x���g�t���O).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̐���.
 *
 *	@param	[in]	flgid	�C�x���g�t���OID�ԍ�.
 *	@param	[in]	pk_cflg	�C�x���g�t���O�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_flg( ID flgid, const T_CFLG *pk_cflg )
{
	ER			ercd;
	WIFLGOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cflg ){
		return E_PAR;
	}
	//! �C�x���g�t���O���������R�s�[����.
	memset( &obj, 0, sizeof(WIFLGOBJ) );
	obj.Attribute = pk_cflg->flgatr;
	obj.FlgVal    = (UINT)pk_cflg->iflgptn;

	wi_CommonLock();

	//! �C�x���g�t���O�𐶐�����.
	ercd = wi_CreateEvFlag( flgid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_cflg	�C�x���g�t���O�������\���̂̃|�C���^.
 *
 *	@retval	�C�x���g�t���OID�ԍ��܂��̓G���[�R�[�h.
 */
ER_ID	acre_flg( const T_CFLG *pk_cflg )
{
	ID			flgid;
	ER_ID		ercd;
	WIFLGOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cflg ){
		return E_PAR;
	}
	//! �C�x���g�t���O���������R�s�[����.
	memset( &obj, 0, sizeof(WIFLGOBJ) );
	obj.Attribute = pk_cflg->flgatr;
	obj.FlgVal    = (UINT)pk_cflg->iflgptn;

	wi_CommonLock();
	for( flgid = 1; flgid < TMAX_MAXFLG; flgid++ ){

		//! �C�x���g�t���O�𐶐�����.
		ercd = wi_CreateEvFlag( flgid, &obj );
		if( ercd == E_OK ){
			ercd = (ER_ID)flgid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̍폜.
 *
 *	@param	[in]	flgid	�C�x���g�t���OID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_flg( ID flgid )
{
	ER ercd;

	wi_CommonLock();

	//! �C�x���g�t���O���폜����.
	ercd = wi_DeleteEvFlag( flgid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̃Z�b�g.
 *
 *	@param	[in]	flgid	�C�x���g�t���OID�ԍ�.
 *	@param	[in]	setptn	�Z�b�g����r�b�g�p�^�[��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		set_flg( ID flgid, FLGPTN setptn )
{
	ER ercd;

	wi_CommonLock();

	//! �C�x���g�t���O���Z�b�g����.
	ercd = wi_SetEvFlag( flgid, (UINT)setptn );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̃Z�b�g (��^�X�N�R���e�L�X�g����̌ďo���p).
 *
 *	@param	[in]	flgid	�C�x���g�t���OID�ԍ�.
 *	@param	[in]	setptn	�Z�b�g����r�b�g�p�^�[��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		iset_flg( ID flgid, FLGPTN setptn )
{
	//! �C�x���g�t���O���Z�b�g����.
	return set_flg( flgid, setptn );
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�̃N���A.
 *
 *	@param	[in]	flgid	�C�x���g�t���OID�ԍ�.
 *	@param	[in]	clrptn	�N���A����r�b�g�p�^�[��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		clr_flg( ID flgid, FLGPTN clrptn )
{
	ER ercd;

	wi_CommonLock();

	//! �C�x���g�t���O���N���A����.
	ercd = wi_ClearEvFlag( flgid, (UINT)clrptn );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�҂� (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	flgid		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	waiptn		�҂��r�b�g�p�^�[��.
 *	@param	[in]	wfmode		�҂����[�h.
 *	@param	[out]	p_flgptn	�҂��������̃r�b�g�p�^�[�����i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn )
{
	//! �^�C���A�E�g�Ȃ��ŃC�x���g�҂�������.
	return twai_flg( flgid, waiptn, wfmode, p_flgptn, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�҂� (�|�[�����O).
 *
 *	@param	[in]	flgid		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	waiptn		�҂��r�b�g�p�^�[��.
 *	@param	[in]	wfmode		�҂����[�h.
 *	@param	[out]	p_flgptn	�҂��������̃r�b�g�p�^�[�����i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pol_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn )
{
	//! �C�x���g���������Ă��邩�ǂ����𒲂ׂ�.
	return twai_flg( flgid, waiptn, wfmode, p_flgptn, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�҂� (�^�C���A�E�g����).
 *
 *	@param	[in]	flgid		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	waiptn		�҂��r�b�g�p�^�[��.
 *	@param	[in]	wfmode		�҂����[�h.
 *	@param	[out]	p_flgptn	�҂��������̃r�b�g�p�^�[�����i�[����̈�̃|�C���^.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		twai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �C�x���g�҂�������.
	ercd = wi_WaitEvFlag( flgid, p_flgptn, waiptn, wfmode & ~TWF_CLR, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O��Ԃ̎Q��.
 *
 *	@param	[in]	flgid	�C�x���g�t���OID�ԍ�.
 *	@param	[out]	pk_rflg	�C�x���g�t���O��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_flg( ID flgid, T_RFLG *pk_rflg )
{
	ER			ercd;
	WIFLGSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rflg ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �C�x���g�t���O�̏�Ԃ��擾����.
	ercd = wi_RefarenceEvFlag( flgid, &sts );
	if( ercd == E_OK ){
		pk_rflg->wtskid = sts.WaitId;
		pk_rflg->flgptn = (FLGPTN)sts.FlgVal;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * ������ʐM�@�\ (�f�[�^�L���[).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̐���.
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	pk_cdtq	�f�[�^�L���[�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_dtq( ID dtqid, const T_CDTQ *pk_cdtq )
{
	ER			ercd;
	WIDTQOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cdtq ){
		return E_PAR;
	}
	//! �f�[�^�L���[���������R�s�[����.
	memset( &obj, 0, sizeof(WIDTQOBJ) );
	obj.Attribute = pk_cdtq->dtqatr;
	obj.QueSize   = pk_cdtq->dtqcnt;

	wi_CommonLock();

	//! �f�[�^�L���[�𐶐�����.
	ercd = wi_CreateDataQueue( (DWORD)dtqid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_cdtq	�f�[�^�L���[�������\���̂̃|�C���^.
 *
 *	@retval	���������f�[�^�L���[�̃f�[�^�L���[ID�܂��̓G���[�R�[�h.
 */
ER_ID	acre_dtq( const T_CDTQ *pk_cdtq )
{
	ID			dtqid;
	ER			ercd;
	WIDTQOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cdtq ){
		return E_PAR;
	}
	//! �f�[�^�L���[���������R�s�[����.
	memset( &obj, 0, sizeof(WIDTQOBJ) );
	obj.Attribute = pk_cdtq->dtqatr;
	obj.QueSize   = pk_cdtq->dtqcnt;

	wi_CommonLock();

	for( dtqid = 1; dtqid < TMAX_MAXDTQ; dtqid++ ){
		//! �f�[�^�L���[�𐶐�����.
		ercd = wi_CreateDataQueue( dtqid, &obj );
		if( ercd == E_OK ){
			ercd  = dtqid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̍폜.
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_dtq( ID dtqid )
{
	ER ercd;

	wi_CommonLock();

	//! �f�[�^�L���[���폜����.
	ercd = wi_DeleteDataQueue( dtqid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�ւ̑��M (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	data	�f�[�^�L���[�ɑ��M����f�[�^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		snd_dtq( ID dtqid, VP_INT data )
{
	//! �^�C���A�E�g�Ȃ��Ńf�[�^�L���[�փf�[�^�𑗐M����.
	return tsnd_dtq( dtqid, data, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�ւ̑��M (�|�[�����O).
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	data	�f�[�^�L���[�ɑ��M����f�[�^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		psnd_dtq( ID dtqid, VP_INT data )
{
	//! ���M�҂��Ȃ��Ńf�[�^�L���[�փf�[�^�𑗐M����.
	return tsnd_dtq( dtqid, data, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�ւ̑��M (��^�X�N�R���e�L�X�g����̌ďo���p).
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	data	�f�[�^�L���[�ɑ��M����f�[�^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ipsnd_dtq( ID dtqid, VP_INT data )
{
	//! �f�[�^�L���[�փf�[�^�𑗐M����.
	return psnd_dtq( dtqid, data );
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�ւ̑��M (�^�C���A�E�g����).
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	data	�f�[�^�L���[�ɑ��M����f�[�^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tsnd_dtq( ID dtqid, VP_INT data, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �f�[�^�L���[�փf�[�^�𑗐M����.
	ercd = wi_SendDataQueue( dtqid, (DWORD)data, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�֋������M.
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	data	�f�[�^�L���[�ɑ��M����f�[�^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		fsnd_dtq( ID dtqid, VP_INT data )
{
	ER ercd;

	wi_CommonLock();

	//! �f�[�^�L���[�փf�[�^���������M����.
	ercd = wi_ForceSendDataQueue( dtqid, (DWORD)data );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�֋������M (��^�X�N�R���e�L�X�g����̌ďo���p).
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[in]	data	�f�[�^�L���[�ɑ��M����f�[�^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ifsnd_dtq( ID dtqid, VP_INT data )
{
	//! �f�[�^�L���[�փf�[�^���������M����.
	return fsnd_dtq( dtqid, data );
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[����̎�M (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[out]	p_data	�f�[�^�L���[�����M�����f�[�^���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rcv_dtq( ID dtqid, VP_INT *p_data )
{
	//! �^�C���A�E�g�Ȃ��Ńf�[�^�L���[����f�[�^����M����.
	return trcv_dtq( dtqid, p_data, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[����̎�M (�|�[�����O).
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[out]	p_data	�f�[�^�L���[�����M�����f�[�^���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		prcv_dtq( ID dtqid, VP_INT *p_data )
{
	//! �f�[�^��M�҂��Ȃ��Ńf�[�^�L���[����f�[�^����M����.
	return trcv_dtq( dtqid, p_data, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[����̎�M (�^�C���A�E�g����).
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[out]	p_data	�f�[�^�L���[�����M�����f�[�^���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		trcv_dtq( ID dtqid, VP_INT *p_data, TMO tmout )
{
	ER		ercd;
	DWORD	data;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !p_data ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �f�[�^�L���[����f�[�^����M����.
	ercd = wi_ReceiveDataQueue( dtqid, &data, tmout );
	if( ercd == E_OK ){
		*p_data = (VP_INT)data;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�[�^�L���[�̏�ԎQ��.
 *
 *	@param	[in]	dtqid	�f�[�^�L���[ID�ԍ�.
 *	@param	[out]	pk_rdtq	�f�[�^�L���[��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_dtq( ID dtqid, T_RDTQ *pk_rdtq )
{
	ER			ercd;
	WIDTQSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rdtq ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �f�[�^�L���[�̏�Ԃ��擾����.
	ercd = wi_RefarenceDataQueue( dtqid, &sts );
	if( ercd == E_OK ){
		pk_rdtq->stskid  = sts.SndWaitId;
		pk_rdtq->rtskid  = sts.RcvWaitId;
		pk_rdtq->sdtqcnt = sts.DataCnt;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * ������ʐM�@�\ (���[���{�b�N�X).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�̐���.
 *
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *	@param	[in]	pk_cmbx	���[���{�b�N�X�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_mbx( ID mbxid, const T_CMBX *pk_cmbx )
{
	ER			ercd;
	WIMBXOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmbx ){
		return E_PAR;
	}
	//! ���[���{�b�N�X���������R�s�[����.
	memset( &obj, 0, sizeof(WIMBXOBJ) );
	obj.Attribute   = pk_cmbx->mbxatr;
	obj.MaxPriority = pk_cmbx->maxmpri;

	wi_CommonLock();

	//! ���[���{�b�N�X�𐶐�����.
	ercd = wi_CreateMailBox( mbxid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_cmbx	���[���{�b�N�X�������\���̂̃|�C���^.
 *
 *	@retval	�����������[���{�b�N�X�̃��[���{�b�N�XID�܂��̓G���[�R�[�h.
 */
ER_ID	acre_mbx( const T_CMBX *pk_cmbx )
{
	ID			mbxid;
	ER			ercd;
	WIMBXOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmbx ){
		return E_PAR;
	}
	//! ���[���{�b�N�X���������R�s�[����.
	memset( &obj, 0, sizeof(WIMBXOBJ) );
	obj.Attribute   = pk_cmbx->mbxatr;
	obj.MaxPriority = pk_cmbx->maxmpri;

	wi_CommonLock();

	for( mbxid = 1; mbxid < TMAX_MAXMBX; mbxid++ ){
		//! ���[���{�b�N�X�𐶐�����.
		ercd = wi_CreateMailBox( mbxid, &obj );
		if( ercd == E_OK ){
			ercd = mbxid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�̍폜.
 *
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_mbx( ID mbxid )
{
	ER ercd;

	wi_CommonLock();

	//! ���[���{�b�N�X���폜����.
	ercd = wi_DeleteMailBox( mbxid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�ւ̑��M.
 *
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *	@param	[in]	pk_msg	���b�Z�[�W��p�P�b�g�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		snd_msg( ID mbxid, T_MSG *pk_msg )
{
	ER ercd;

	wi_CommonLock();

	//! ���[���{�b�N�X�փ��b�Z�[�W�𑗐M����.
	ercd = wi_SendMailBox( mbxid, pk_msg );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X����̎�M (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *	@param	[out]	ppk_msg	���b�Z�[�W��p�P�b�g�̃A�h���X���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rcv_msg( ID mbxid, T_MSG **ppk_msg )
{
	//! �^�C���A�E�g�Ȃ��Ń��[���{�b�N�X���烁�b�Z�[�W����M����.
	return trcv_msg( mbxid, ppk_msg, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X����̎�M (�|�[�����O).
 *
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *	@param	[out]	ppk_msg	���b�Z�[�W��p�P�b�g�̃A�h���X���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		prcv_msg( ID mbxid, T_MSG **ppk_msg )
{
	//! ��M�҂��Ȃ��Ń��[���{�b�N�X���烁�b�Z�[�W����M����.
	return trcv_msg( mbxid, ppk_msg, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X����̎�M (�^�C���A�E�g����).
 *
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *	@param	[out]	ppk_msg	���b�Z�[�W��p�P�b�g�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		trcv_msg( ID mbxid, T_MSG **ppk_msg, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! ���[���{�b�N�X���烁�b�Z�[�W����M����.
	ercd = wi_ReceiveMailBox( mbxid, ppk_msg, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X�̏�ԎQ��.
 *
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *	@param	[out]	pk_rmbx	���[���{�b�N�X��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mbx( ID mbxid, T_RMBX *pk_rmbx )
{
	ER			ercd;
	WIMBXSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rmbx ){
		return E_PAR;
	}
	wi_CommonLock();

	//! ���[���{�b�N�X�̏�Ԃ��擾����.
	ercd = wi_RefarenceMailBox( mbxid, &sts );
	if( ercd == E_OK ){
		pk_rmbx->wtskid = sts.WaitId;
		pk_rmbx->pk_msg = sts.NextMsg;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * �g��������ʐM�@�\ (�~���[�e�b�N�X).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̐���.
 *
 *	@param	[in]	mtxid	�~���[�e�b�N�XID�ԍ�.
 *	@param	[in]	pk_cmtx	�~���[�e�b�N�X�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_mtx( ID mtxid, const T_CMTX *pk_cmtx )
{
	ER			ercd;
	WIMTXOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmtx ){
		return E_PAR;
	}
	//! �~���[�e�b�N�X���������R�s�[����.
	memset( &obj, 0, sizeof(WIMTXOBJ) );
	obj.Attribute = pk_cmtx->mtxatr;
	obj.CeilPri   = pk_cmtx->ceilpri;

	wi_CommonLock();

	//! �~���[�e�b�N�X�𐶐�����.
	ercd = wi_CreateMutex( mtxid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_cmtx	�~���[�e�b�N�X�������\���̂̃|�C���^.
 *
 *	@retval	���������~���[�e�b�N�X��ID�ԍ��܂��̓G���[�R�[�h.
 */
ER_ID	acre_mtx( const T_CMTX *pk_cmtx )
{
	ID			mtxid;
	ER			ercd;
	WIMTXOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmtx ){
		return E_PAR;
	}
	//! �~���[�e�b�N�X���������R�s�[����.
	memset( &obj, 0, sizeof(WIMTXOBJ) );
	obj.Attribute = pk_cmtx->mtxatr;
	obj.CeilPri   = pk_cmtx->ceilpri;

	wi_CommonLock();

	for( mtxid = 1; mtxid < TMAX_MAXMTX; mtxid++ ){
		//! �~���[�e�b�N�X�𐶐�����.
		ercd = wi_CreateMutex( mtxid, &obj );
		if( ercd == E_OK ){
			ercd  = mtxid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̍폜.
 *
 *	@param	[in]	mtxid	�~���[�e�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_mtx( ID mtxid )
{
	ER ercd;

	wi_CommonLock();

	//! �~���[�e�b�N�X���폜����.
	ercd = wi_DeleteMutex( mtxid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̃��b�N (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	mtxid	�~���[�e�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		loc_mtx( ID mtxid )
{
	//! �^�C���A�E�g�Ȃ��Ń~���[�e�b�N�X�����b�N����.
	return tloc_mtx( mtxid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̃��b�N (�|�[�����O).
 *
 *	@param	[in]	mtxid	�~���[�e�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ploc_mtx( ID mtxid )
{
	//! �~���[�e�b�N�X�����b�N�ł��邩�ǂ������ׂ�.
	return tloc_mtx( mtxid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̃��b�N (�^�C���A�E�g����).
 *
 *	@param	[in]	mtxid	�~���[�e�b�N�XID�ԍ�.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tloc_mtx( ID mtxid, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �~���[�e�b�N�X�����b�N����.
	ercd = wi_LockMutex( mtxid, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̃��b�N������.
 *
 *	@param	[in]	mtxid	�~���[�e�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		unl_mtx( ID mtxid )
{
	ER ercd;

	wi_CommonLock();

	//! �~���[�e�b�N�X�̃��b�N����������.
	ercd = wi_UnlockMutex( mtxid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�~���[�e�b�N�X�̏�ԎQ��.
 *
 *	@param	[in]	mtxid	�~���[�e�b�N�XID�ԍ�.
 *	@param	[out]	pk_rmbx	�~���[�e�b�N�X��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mtx( ID mtxid, T_RMTX *pk_rmtx )
{
	ER			ercd;
	WIMTXSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rmtx ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �~���[�e�b�N�X�̏�Ԃ��擾����.
	ercd = wi_RefarenceMutex( mtxid, &sts );
	if( ercd == E_OK ){
		pk_rmtx->htskid = sts.LockId;
		pk_rmtx->wtskid = sts.WaitId;
	}
	wi_CommonUnlock();
	return E_OK;
}

/***************************************
 *
 * �g��������ʐM�@�\ (���b�Z�[�W�o�b�t�@).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̐���.
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[in]	pk_cmbf	���b�Z�[�W�o�b�t�@�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_mbf( ID mbfid, const T_CMBF *pk_cmbf )
{
	ER			ercd;
	WIMBFOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmbf ){
		return E_PAR;
	}
	//! ���b�Z�[�W�o�b�t�@���������R�s�[����.
	memset( &obj, 0, sizeof(WIMBFOBJ) );
	obj.SndAttr = pk_cmbf->mbfatr;
	obj.RcvAttr = pk_cmbf->mbfatr & ~TA_TPRI;
	obj.MsgSize = pk_cmbf->mbfsz;
	obj.MaxMsg  = pk_cmbf->maxmsz;

	wi_CommonLock();

	//! ���b�Z�[�W�o�b�t�@�𐶐�����.
	ercd = wi_CreateMsgBuffer( mbfid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_cmbf	���b�Z�[�W�o�b�t�@�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER_ID	acre_mbf( const T_CMBF *pk_cmbf )
{
	ID			mbfid;
	ER			ercd;
	WIMBFOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmbf ){
		return E_PAR;
	}
	//! ���b�Z�[�W�o�b�t�@���������R�s�[����.
	memset( &obj, 0, sizeof(WIMBFOBJ) );
	obj.SndAttr = pk_cmbf->mbfatr;
	obj.RcvAttr = pk_cmbf->mbfatr & ~TA_TPRI;
	obj.MsgSize = pk_cmbf->mbfsz;
	obj.MaxMsg  = pk_cmbf->maxmsz;

	wi_CommonLock();

	for( mbfid = 1; mbfid < TMAX_MAXMBF; mbfid++ ){
		//! ���b�Z�[�W�o�b�t�@�𐶐�����.
		ercd = wi_CreateMsgBuffer( mbfid, &obj );
		if( ercd == E_OK ){
			ercd  = mbfid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̍폜.
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_mbf( ID mbfid )
{
	ER ercd;

	wi_CommonLock();

	//! ���b�Z�[�W�o�b�t�@���폜����.
	ercd = wi_DeleteMsgBuffer( mbfid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�ւ̑��M (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[in]	msg		���b�Z�[�W�̃|�C���^.
 *	@param	[in]	msgsz	���b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		snd_mbf( ID mbfid, VP msg, UINT msgsz )
{
	//! �^�C���A�E�g�Ȃ��Ń��b�Z�[�W�o�b�t�@�փ��b�Z�[�W�𑗐M����.
	return tsnd_mbf( mbfid, msg, msgsz, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�ւ̑��M (�|�[�����O).
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[in]	msg		���b�Z�[�W�̃|�C���^.
 *	@param	[in]	msgsz	���b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		psnd_mbf( ID mbfid, VP msg, UINT msgsz )
{
	//! ���M�҂��Ȃ��Ń��b�Z�[�W�o�b�t�@�փ��b�Z�[�W�𑗐M����.
	return tsnd_mbf( mbfid, msg, msgsz, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�ւ̑��M (�^�C���A�E�g����).
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[in]	msg		���b�Z�[�W�̃|�C���^.
 *	@param	[in]	msgsz	���b�Z�[�W�̃T�C�Y.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tsnd_mbf( ID mbfid, VP msg, UINT msgsz, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! ���b�Z�[�W�o�b�t�@�փ��b�Z�[�W�𑗐M����.
	ercd = wi_SendMsgBuffer( mbfid, msg, msgsz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@����̎�M (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[out]	msg		���b�Z�[�W���i�[����̈�̃|�C���^.
 *
 *	@retval	���b�Z�[�W�T�C�Y�܂��̓G���[�R�[�h.
 */
ER_UINT	rcv_mbf( ID mbfid, VP msg )
{
	//! �^�C���A�E�g�Ȃ��Ń��b�Z�[�W�o�b�t�@���烁�b�Z�[�W����M����.
	return trcv_mbf( mbfid, msg, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@����̎�M (�|�[�����O).
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[out]	msg		���b�Z�[�W���i�[����̈�̃|�C���^.
 *
 *	@retval	���b�Z�[�W�T�C�Y�܂��̓G���[�R�[�h.
 */
ER_UINT	prcv_mbf( ID mbfid, VP msg )
{
	//! ��M�҂��Ȃ��Ń��b�Z�[�W�o�b�t�@���烁�b�Z�[�W����M����.
	return trcv_mbf( mbfid, msg, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@����̎�M (�^�C���A�E�g����).
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[out]	msg		���b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	���b�Z�[�W�T�C�Y�܂��̓G���[�R�[�h.
 */
ER_UINT	trcv_mbf( ID mbfid, VP msg, TMO tmout )
{
	ER		ercd;
	INT		size;

	wi_CommonLock();

	//! ���b�Z�[�W�o�b�t�@���烁�b�Z�[�W����M����.
	ercd = wi_ReceiveMsgBuffer( mbfid, msg, &size, tmout );
	if( ercd == E_OK ){
		ercd  = size;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̏�ԎQ��.
 *
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[out]	pk_rmbf	���b�Z�[�W�o�b�t�@��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mbf( ID mbfid, T_RMBF *pk_rmbf )
{
	ER			ercd;
	WIMBFSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rmbf ){
		return E_PAR;
	}
	wi_CommonLock();

	//! ���b�Z�[�W�o�b�t�@�̏�Ԃ��擾����.
	ercd = wi_RefarenceMsgBuffer( mbfid, &sts );
	if( ercd == E_OK ){
		pk_rmbf->rtskid  = sts.RcvWaitId;
		pk_rmbf->stskid  = sts.SndWaitId;
		pk_rmbf->smsgcnt = sts.MsgSize;
		pk_rmbf->fmbfsz  = sts.FreeSize;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * �g��������ʐM�@�\ (�����f�u�|�[�g).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�����f�u�|�[�g�̐���.
 *
 *	@param	[in]	porid	�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	pk_cpor	�����f�u�|�[�g�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_por( ID porid, const T_CPOR *pk_cpor )
{
	ER			ercd;
	WIPOROBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cpor ){
		return E_PAR;
	}
	//! �����f�u�|�[�g���������R�s�[����.
	memset( &obj, 0, sizeof(WIPOROBJ) );
	obj.Attribute = pk_cpor->poratr;
	obj.MaxCalMsg = pk_cpor->maxcmsz;
	obj.MaxRepMsg = pk_cpor->maxrmsz;

	wi_CommonLock();

	//! �����f�u�|�[�g�𐶐�����.
	ercd = wi_CreateRendPort( porid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�|�[�g�̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_cpor	�����f�u�|�[�g�������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER_ID	acre_por( const T_CPOR *pk_cpor )
{
	ID			porid;
	ER			ercd;
	WIPOROBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cpor ){
		return E_PAR;
	}
	//! �����f�u�|�[�g���������R�s�[����.
	memset( &obj, 0, sizeof(WIPOROBJ) );
	obj.Attribute = pk_cpor->poratr;
	obj.MaxCalMsg = pk_cpor->maxcmsz;
	obj.MaxRepMsg = pk_cpor->maxrmsz;

	wi_CommonLock();

	for( porid = 1; porid < TMAX_MAXPOR; porid++ ){
		//! �����f�u�|�[�g�𐶐�����.
		ercd = wi_CreateRendPort( porid, &obj );
		if( ercd == E_OK ){
			ercd  = porid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�|�[�g�̍폜.
 *
 *	@param	[in]	porid	�����f�u�|�[�gID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_por( ID porid )
{
	ER ercd;

	wi_CommonLock();

	//! �����f�u�|�[�g���폜����.
	ercd = wi_DeleteRendPort( porid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�Ăяo�� (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	calptn		�Ăяo�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	msg			���b�Z�[�W�̃A�h���X.
 *	@param	[in]	cmsgsz		�Ăяo�����b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�������b�Z�[�W�̃T�C�Y�܂��̓G���[�R�[�h.
 */
ER_UINT	cal_por( ID porid, RDVPTN calptn, VP msg, UINT cmsgsz )
{
	//! �^�C���A�E�g�Ȃ��Ń����f�u���Ăяo��.
	return tcal_por( porid, calptn, msg, cmsgsz, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�Ăяo�� (�^�C���A�E�g����).
 *
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	calptn		�Ăяo�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	msg			���b�Z�[�W�̃A�h���X.
 *	@param	[in]	cmsgsz		�Ăяo�����b�Z�[�W�̃T�C�Y.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�������b�Z�[�W�̃T�C�Y�܂��̓G���[�R�[�h.
 */
ER_UINT	tcal_por( ID porid, RDVPTN calptn, VP msg, UINT cmsgsz, TMO tmout )
{
	ER	ercd;
	INT	size;

	wi_CommonLock();

	//! �����f�u���Ăяo��.
	ercd = wi_CallRendPort( porid, calptn, msg, cmsgsz, &size, tmout );
	if( ercd == E_OK ){
		ercd  = size;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�󂯕t�� (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	acpptn		�󂯕t�����I�������̃r�b�g�p�^�[��.
 *	@param	[out]	p_rdvno		�����f�u�ԍ����i�[����̈�̃|�C���^.
 *	@param	[out]	msg			�Ăяo�����b�Z�[�W���i�[����̈�̃|�C���^.
 *
 *	@retval	�Ăяo�����b�Z�[�W�̃T�C�Y�܂��̓G���[�R�[�h.
 */
ER_UINT	acp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg )
{
	//! �^�C���A�E�g�Ȃ��Ń����f�u���󂯕t����.
	return tacp_por( porid, acpptn, p_rdvno, msg, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�󂯕t�� (�|�[�����O).
 *
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	acpptn		�󂯕t�����I�������̃r�b�g�p�^�[��.
 *	@param	[out]	p_rdvno		�����f�u�ԍ����i�[����̈�̃|�C���^.
 *	@param	[out]	msg			�Ăяo�����b�Z�[�W���i�[����̈�̃|�C���^.
 *
 *	@retval	�Ăяo�����b�Z�[�W�̃T�C�Y�܂��̓G���[�R�[�h.
 */
ER_UINT	pacp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg )
{
	//! �Ăяo���҂��Ȃ��Ń����f�u���󂯕t����.
	return tacp_por( porid, acpptn, p_rdvno, msg, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�󂯕t�� (�^�C���A�E�g����).
 *
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	acpptn		�󂯕t�����I�������̃r�b�g�p�^�[��.
 *	@param	[out]	p_rdvno		�����f�u�ԍ����i�[����̈�̃|�C���^.
 *	@param	[out]	msg			�Ăяo�����b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�Ăяo�����b�Z�[�W�̃T�C�Y�܂��̓G���[�R�[�h.
 */
ER_UINT	tacp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg, TMO tmout )
{
	ER	ercd;
	INT	size;

	wi_CommonLock();

	//! �����f�u���󂯕t����.
	ercd = wi_AcceptRendPort( porid, acpptn, p_rdvno, msg, &size, tmout );
	if( ercd == E_OK ){
		ercd  = size;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�̉�
 *
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	calptn		�󂯕t�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	rdvno		�����f�u�ԍ�.
 *	@param	[in]	msg			�Ăяo�����b�Z�[�W�̃|�C���^.
 *	@param	[in]	cmsgsz		�Ăяo�����b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		fwd_por( ID porid, RDVPTN calptn, RDVNO rdvno, VP msg, UINT cmsgsz )
{
	ER ercd;

	wi_CommonLock();

	//! �����f�u�𑼂̃����f�u��|�[�g�ɉ񑗂���.
	ercd = wi_FowardRendPort( porid, calptn, rdvno, msg, cmsgsz );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�̏I��.
 *
 *	@param	[in]	rdvno		�����f�u�ԍ�.
 *	@param	[in]	msg			�ԓ����b�Z�[�W�̃|�C���^.
 *	@param	[in]	cmsgsz		�ԓ����b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rpl_rdv( RDVNO rdvno, VP msg, UINT cmsgsz )
{
	ER ercd;

	wi_CommonLock();

	//! �����f�u�̏I����ʒm����.
	ercd = wi_ReplayRendPort( rdvno, msg, cmsgsz );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�|�[�g�̏�ԎQ��.
 *
 *	@param	[in]	porid	�����f�u��|�[�gID�ԍ�.
 *	@param	[out]	pk_rpor	�����f�u�|�[�g��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_por( ID porid, T_RPOR *pk_rpor )
{
	ER			ercd;
	WIPORSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rpor ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �����f�u�|�[�g�̏�Ԃ��擾����.
	ercd = wi_RefarenceRendPort( porid, &sts );
	if( ercd == E_OK ){
		pk_rpor->ctskid = sts.CalWaitId;
		pk_rpor->atskid = sts.AcpWaitId;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u��Ԃ̎Q��.
 *
 *	@param	[in]	rdvno	�����f�u�ԍ�.
 *	@param	[out]	pk_rrdv	�����f�u��Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_rdv( RDVNO rdvno, T_RRDV *pk_rrdv )
{
	ER			ercd;
	WIRDVSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rrdv ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �����f�u��Ԃ��擾����.
	ercd = wi_RefarenceRendStat( rdvno, &sts );
	if( ercd == E_OK ){
		pk_rrdv->wtskid = sts.WaitId;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * �������v�[���Ǘ��@�\ (�Œ蒷�������v�[��).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̐���.
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *	@param	[in]	pk_cmpf	�������v�[���������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_mpf( ID mpfid, const T_CMPF *pk_cmpf )
{
	ER			ercd;
	WIMPFOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmpf ){
		return E_PAR;
	}
	//! �Œ蒷�������v�[�����������R�s�[����.
	memset( &obj, 0, sizeof(WIMPFOBJ) );
	obj.Attribute = pk_cmpf->mpfatr;
	obj.BlockCnt  = pk_cmpf->blkcnt;
	obj.BlockSize = pk_cmpf->blfsz;

	wi_CommonLock();

	//! �Œ蒷�������v�[���𐶐�����.
	ercd = wi_CreateFixedMemPool( mpfid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_cmpf	�������v�[���������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		acre_mpf( const T_CMPF *pk_cmpf )
{
	ID			mpfid;
	ER			ercd;
	WIMPFOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmpf ){
		return E_PAR;
	}
	//! �Œ蒷�������v�[�����������R�s�[����.
	memset( &obj, 0, sizeof(WIMPFOBJ) );
	obj.Attribute = pk_cmpf->mpfatr;
	obj.BlockCnt  = pk_cmpf->blkcnt;
	obj.BlockSize = pk_cmpf->blfsz;

	wi_CommonLock();

	for( mpfid = 1; mpfid < TMAX_MAXMPF; mpfid++ ){
		//! �Œ蒷�������v�[���𐶐�����.
		ercd = wi_CreateFixedMemPool( mpfid, &obj );
		if( ercd == E_OK ){
			ercd  = mpfid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̍폜.
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_mpf( ID mpfid )
{
	ER ercd;

	wi_CommonLock();

	//! �Œ蒷�������v�[�����폜����.
	ercd = wi_DeleteFixedMemPool( mpfid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������u���b�N�̊l�� (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *	@param	[out]	p_blf	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_blf(ID mpfid, VP *p_blf )
{
	//! �^�C���A�E�g�Ȃ��ŌŒ蒷�������u���b�N���l������.
	return tget_blf( mpfid, p_blf, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������u���b�N�̊l�� (�|�[�����O).
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *	@param	[out]	p_blf	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pget_blf(ID mpfid, VP *p_blf )
{
	//! �l���҂��Ȃ��ŌŒ蒷�������u���b�N���l������.
	return tget_blf( mpfid, p_blf, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������u���b�N�̊l�� (�^�C���A�E�g����).
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *	@param	[out]	p_blf	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tget_blf(ID mpfid, VP *p_blf, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �Œ蒷�������u���b�N���l������.
	ercd = wi_GetFixedMemPool( mpfid, p_blf, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷��������u���b�N�̕ԋp.
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *	@param	[in]	blf		�ԋp���郁�����u���b�N�̃A�h���X.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rel_blf( ID mpfid, VP blf )
{
	ER ercd;

	wi_CommonLock();

	//! �Œ蒷�������u���b�N��ԋp����.
	ercd = wi_ReleaseFixedMemPool( mpfid, blf );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������v�[���̎Q��.
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *	@param	[out]	pk_rmpf	�������v�[����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mpf( ID mpfid , T_RMPF *pk_rmpf )
{
	ER			ercd;
	WIMPFSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rmpf ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �Œ蒷�������v�[���̏�Ԃ��擾����.
	ercd = wi_RefarenceFixedMemPool( mpfid, &sts );
	if( ercd == E_OK ){
		pk_rmpf->wtskid  = sts.WaitId;
		pk_rmpf->fblkcnt = sts.FreeBlock;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * �������v�[���Ǘ��@�\ (�ϒ��������v�[��).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̐���.
 *
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *	@param	[in]	pk_cmpl	�������v�[���������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_mpl( ID mplid, const T_CMPL *pk_cmpl )
{
	ER			ercd;
	WIMPLOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmpl ){
		return E_PAR;
	}
	//! �ϒ��������v�[�����������R�s�[����.
	memset( &obj, 0, sizeof(WIMPLOBJ) );
	obj.Attribute = pk_cmpl->mplatr;
	obj.MemSize   = pk_cmpl->mplsz;

	wi_CommonLock();

	//! �ϒ��������v�[���𐶐�����.
	ercd = wi_CreateVarMemPool( mplid, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_cmpl	�������v�[���������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		acre_mpl( const T_CMPL *pk_cmpl )
{
	ID			mplid;
	ER			ercd;
	WIMPLOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_cmpl ){
		return E_PAR;
	}
	//! �ϒ��������v�[�����������R�s�[����.
	memset( &obj, 0, sizeof(WIMPLOBJ) );
	obj.Attribute = pk_cmpl->mplatr;
	obj.MemSize   = pk_cmpl->mplsz;

	wi_CommonLock();

	for( mplid = 1; mplid < TMAX_MAXMPL; mplid++ ){
		//! �ϒ��������v�[���𐶐�����.
		ercd = wi_CreateVarMemPool( mplid, &obj );
		if( ercd == E_OK ){
			ercd  = mplid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̍폜.
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_mpl( ID mplid )
{
	ER ercd;

	wi_CommonLock();

	//! �ϒ��������v�[�����폜����.
	ercd = wi_DeleteVarMemPool( mplid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������u���b�N�̊l�� (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *	@param	[in]	blksz	�������u���b�N�̃T�C�Y.
 *	@param	[in]	p_blk	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_mpl( ID mplid, UINT blksz, VP *p_blk )
{
	//! �^�C���A�E�g�Ȃ��ŉϒ��������u���b�N���l������.
	return tget_mpl( mplid, blksz, p_blk, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������u���b�N�̊l�� (�|�[�����O).
 *
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *	@param	[in]	blksz	�������u���b�N�̃T�C�Y.
 *	@param	[in]	p_blk	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pget_mpl( ID mplid, UINT blksz, VP *p_blk )
{
	//! �l���҂��Ȃ��ŉϒ��������u���b�N���l������.
	return tget_mpl( mplid, blksz, p_blk, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������u���b�N�̊l�� (�^�C���A�E�g����).
 *
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *	@param	[in]	blksz	�������u���b�N�̃T�C�Y.
 *	@param	[in]	p_blk	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tget_mpl( ID mplid, UINT blksz, VP *p_blk, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �ϒ��������u���b�N���l������.
	ercd = wi_GetVarMemPool( mplid, p_blk, blksz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������u���b�N�̕ԋp.
 *
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *	@param	[in]	blk		�ԋp���郁�����u���b�N�̃A�h���X.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rel_blk( ID mplid, VP blk )
{
	ER ercd;

	wi_CommonLock();

	//! �ϒ��������u���b�N��ԋp����.
	ercd = wi_ReleaseVarMemPool( mplid, blk );

	wi_CommonUnlock();
	return ercd;
}

ER rel_mpl(ID mplid, VP blk)
{
	return rel_blk(mplid, blk);
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̎Q��.
 *
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *	@param	[out]	pk_rmpl	�������v�[����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mpl( ID mpfid, T_RMPL *pk_rmpl )
{
	ER			ercd;
	WIMPLSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rmpl ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �ϒ��������v�[���̏�Ԃ��擾����.
	ercd = wi_RefarenceVarMemPool( mpfid, &sts );
	if( ercd == E_OK ){
		pk_rmpl->wtskid = sts.WaitId;
		pk_rmpl->fmplsz = sts.TotalFreeSize;
		pk_rmpl->fblksz = sts.MaxFreeSize;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * ���ԊǗ��@�\.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�V�X�e�������̐ݒ�.
 *
 *	@param	[in]	pk_tim		�ݒ肷�鎞�����i�[�����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		set_tim( const SYSTIME *pk_tim )
{
	if( !pk_tim ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �V�X�e��������ݒ肷��.
	wi_SetSystemTime( ((DWORDLONG)(pk_tim->utime) << 32) + (DWORDLONG)(pk_tim->ltime) );

	wi_CommonUnlock();
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�V�X�e�������̎Q��.
 *
 *	@param	[in]	pk_tim		�V�X�e���������i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_tim( SYSTIME *pk_tim )
{
	DWORDLONG sys_time;

	if( !pk_tim ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �V�X�e���������Q�Ƃ���.
	sys_time      = wi_GetSystemTime();
	pk_tim->utime = (short)(sys_time >> 32 & 0x0000FFFF);
	pk_tim->ltime = (long )(sys_time       & 0xFFFFFFFF);

	wi_CommonUnlock();
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�^�C���e�B�b�N�̋���.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		isig_tim( void )
{
	return E_NOSPT;
}

/***************************************
 *
 * ���ԊǗ��@�\ (�����n���h��).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�����n���h���̐���.
 *
 *	@param	[in]	cycid	�����n���h��ID�ԍ�.
 *	@param	[in]	pk_ccyc	�����n���h���������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_cyc( ID cycid, const T_CCYC *pk_ccyc )
{
	ER			ercd;
	WICYCOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_ccyc ){
		return E_PAR;
	}
	//! �����n���h����`�����R�s�[����.
	memset( &obj, 0, sizeof(WICYCOBJ) );
	obj.Attribute = pk_ccyc->cycatr;
	obj.CycAdr    = pk_ccyc->cychdr;
	obj.Active    = (pk_ccyc->cycatr & TA_STA) ? TRUE : FALSE;
	obj.ExtInfo   = pk_ccyc->exinf;
	obj.CycleTime = ((DWORDLONG)(pk_ccyc->cyctim.utime) << 32) + (DWORDLONG)(pk_ccyc->cyctim.ltime);
	obj.CyclePhs  = ((DWORDLONG)(pk_ccyc->cycphs.utime) << 32) + (DWORDLONG)(pk_ccyc->cycphs.ltime);

	wi_CommonLock();

	//! �����n���h����o�^����.
	ercd = wi_DefineCycleHadler( cycid, &obj, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_ccyc	�����n���h���������\���̂̃|�C���^.
 *
 *	@retval	�������������n���h���̃n���h��ID�܂��̓G���[�R�[�h.
 */
ER		acre_cyc( const T_CCYC *pk_ccyc )
{
	ER_ID		ercd;
	ID			cycid;
	WICYCOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_ccyc ){
		return E_PAR;
	}
	//! �����n���h����`�����R�s�[����.
	memset( &obj, 0, sizeof(WICYCOBJ) );
	obj.Attribute = pk_ccyc->cycatr;
	obj.CycAdr    = pk_ccyc->cychdr;
	obj.Active    = (pk_ccyc->cycatr & TA_STA) ? TRUE : FALSE;
	obj.ExtInfo   = pk_ccyc->exinf;
	obj.CycleTime = ((DWORDLONG)(pk_ccyc->cyctim.utime) << 32) + (DWORDLONG)(pk_ccyc->cyctim.ltime);
	obj.CyclePhs  = ((DWORDLONG)(pk_ccyc->cycphs.utime) << 32) + (DWORDLONG)(pk_ccyc->cycphs.ltime);

	wi_CommonLock();

	for( cycid = 1; cycid < TMAX_MAXCYC; cycid++ ){

		//! �����n���h����o�^����.
		ercd = wi_DefineCycleHadler( cycid, &obj, FALSE );
		if( ercd == E_OK ){
			ercd = cycid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̍폜.
 *
 *	@param	[in]	cycid	�����n���h��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_cyc( ID cycid )
{
	ER ercd;

	wi_CommonLock();

	//! �����n���h�����폜����.
	ercd = wi_DeleteCycleHadler( cycid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̋N��.
 *
 *	@param	[in]	cycid	�����n���h��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		sta_cyc( ID cycid )
{
	ER ercd;

	wi_CommonLock();

	//! �����n���h�����N������.
	ercd = wi_ActionCycleHadler( cycid, TRUE, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̒�~.
 *
 *	@param	[in]	cycid	�����n���h��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		stp_cyc( ID cycid )
{
	ER ercd;

	wi_CommonLock();

	//! �����n���h�����~����.
	ercd = wi_ActionCycleHadler( cycid, FALSE, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̏�ԎQ��.
 *
 *	@param	[in]	cycid	�����n���h��ID�ԍ�.
 *	@param	[out]	pk_rcyc	�����n���h����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_cyc( ID cycid, T_RCYC *pk_rcyc )
{
	ER			ercd;
	WICYCSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rcyc ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �����n���h���̏�Ԃ��擾����.
	ercd = wi_RefarenceCycleHadler( cycid, &sts );
	if( ercd == E_OK ){
		pk_rcyc->cycstat       = sts.Active ? TCYC_STA : TCYC_STP;
		pk_rcyc->lefttim.utime = (short)(sts.LeftTime >> 32 & 0x0000FFFF);
		pk_rcyc->lefttim.ltime = (long )(sts.LeftTime       & 0xFFFFFFFF);
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * ���ԊǗ��@�\ (�A���[����n���h��).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̐���.
 *
 *	@param	[in]	almid	�A���[����n���h��ID�ԍ�.
 *	@param	[in]	pk_calm	�A���[����n���h���������\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cre_alm( ID almid, const T_CALM *pk_calm )
{
	ER			ercd;
	WIALMOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_calm ){
		return E_PAR;
	}
	//! �A���[����n���h���o�^�����R�s�[����.
	memset( &obj, 0, sizeof(WIALMOBJ) );
	obj.Attribute = pk_calm->almatr;
	obj.ExtInfo   = pk_calm->exinf;
	obj.AlmAdr    = pk_calm->almhdr;

	wi_CommonLock();

	//! �A���[����n���h����o�^����.
	ercd = wi_DefineAlarmHadler( almid, &obj, FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̐��� (ID�ԍ���������t��).
 *
 *	@param	[in]	pk_calm	�A���[����n���h���������\���̂̃|�C���^.
 *
 *	@retval	���������A���[����n���h���̃n���h��ID�܂��̓G���[�R�[�h.
 */
ER_ID	acre_alm( const T_CALM *pk_calm )
{
	ER_ID		ercd;
	ID			almid;
	WIALMOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_calm ){
		return E_PAR;
	}
	//! �A���[����n���h���o�^�����R�s�[����.
	memset( &obj, 0, sizeof(WIALMOBJ) );
	obj.Attribute = pk_calm->almatr;
	obj.ExtInfo   = pk_calm->exinf;
	obj.AlmAdr    = pk_calm->almhdr;

	wi_CommonLock();

	for( almid = 1; almid < TMAX_MAXALM; almid++ ){

		//! �A���[����n���h����o�^����.
		ercd = wi_DefineAlarmHadler( almid, &obj, FALSE );
		if( ercd == E_OK ){
			ercd  = almid;
			break;
		}
	}
	if( ercd == E_OBJ ){
		ercd  = E_NOID;
	}
	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̍폜.
 *
 *	@param	[in]	almid	�A���[����n���h��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		del_alm( ID almid )
{
	ER ercd;

	wi_CommonLock();

	//! �A���[����n���h�����폜����.
	ercd = wi_DeleteAlarmHadler( almid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̋N��.
 *
 *	@param	[in]	almid	�A���[����n���h��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		sta_alm( ID almid, RELTIM almtim )
{
	ER ercd;

	wi_CommonLock();

	//! �A���[����n���h�����N������.
	ercd = wi_StartAlarmHadler( almid, ((DWORDLONG)(almtim.utime) << 32) + (DWORDLONG)(almtim.ltime) );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̒�~.
 *
 *	@param	[in]	almid	�A���[����n���h��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		stp_alm( ID almid )
{
	ER ercd;

	wi_CommonLock();

	//! �A���[����n���h�����~����.
	ercd = wi_StopAlarmHadler( almid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̏�ԎQ��.
 *
 *	@param	[in]	almid	�A���[����n���h��ID�ԍ�.
 *	@param	[out]	pk_ralm	�A���[����n���h����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_alm( ID almid, T_RALM *pk_ralm )
{
	ER			ercd;
	WIALMSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_ralm ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �A���[����n���h���̏�Ԃ��擾����.
	ercd = wi_RefarenceAlarmHadler( almid, &sts );
	if( ercd == E_OK ){
		pk_ralm->almstat       = sts.Active ? TALM_STA : TALM_STP;
		pk_ralm->lefttim.utime = (short)(sts.LeftTime >> 32 & 0x0000FFFF);
		pk_ralm->lefttim.ltime = (long )(sts.LeftTime       & 0xFFFFFFFF);
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * ���荞�݊Ǘ��@�\.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	���荞�݃n���h���̒�`.
 *
 *	@param	[in]	intno		���荞�݃n���h���ԍ�.
 *	@param	[in]	pk_dinh		���荞�݃n���h����`���\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		def_inh( INTNO intno, const T_DINH *pk_dinh )
{
	ER			ercd;
	WIINTOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_dinh ){
		return E_PAR;
	}
	//! ���荞�݃n���h����`�����R�s�[����.
	memset( &obj, 0, sizeof(WIINTOBJ) );
	obj.Attribute = pk_dinh->inhatr;
	obj.IntrAdr   = pk_dinh->inthdr;

	wi_CommonLock();

	//! ���荞�݃n���h����o�^����.
	ercd = wi_DefineIntrruptHander( intno, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���荞�݂̋֎~.
 *
 *	@param	[in]	intno		���荞�݃n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		dis_int( INTNO intno )
{
	ER ercd;

	wi_CommonLock();

	//! ���荞�݂��֎~����.
	ercd = wi_DisableIntrrupt( intno );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���荞�݂̋���.
 *
 *	@param	[in]	intno		���荞�݃n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ena_int( INTNO intno )
{
	ER ercd;

	wi_CommonLock();

	//! ���荞�݂�������.
	ercd = wi_EnableIntrrupt( intno );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	CPU���b�N��Ԃւ̈ڍs.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		loc_cpu( void )
{
	ER ercd;

	wi_CommonLock();

	//! CPU�����b�N����.
	ercd = wi_LockCPU();

	wi_CommonUnlock();
	return ercd;
}

ER iloc_cpu(void)
{
	return loc_cpu();
}


/****************************************************************************/
/*!
 *	@brief	CPU���b�N��Ԃ̉���.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		unl_cpu( void )
{
	ER ercd;

	wi_CommonLock();

	//! CPU�̃��b�N����������.
	ercd = wi_UnLockCPU();

	wi_CommonUnlock();
	return ercd;
}

ER iunl_cpu(void)
{
    return unl_cpu();
}


/***************************************
 *
 * �V�X�e����ԊǗ��@�\.
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�^�X�N�̗D�揇�ʂ̉�].
 *
 *	@param	[in]	tskpri	�D�揇�ʂ���]����D��x.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rot_rdq( PRI tskpri )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�̗D�揇�ʂ���]������.
	ercd = wi_RotateTaskPriority( tskpri );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���s��Ԃ̃^�X�NID�̎Q��.
 *
 *	@param	[out]	p_tskid		�^�X�NID�ԍ����i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_tid( ID *p_tskid )
{
	ER ercd;

	wi_CommonLock();

	//! ���s��Ԃɂ���^�X�N��ID���擾����.
	ercd = wi_GetTid( p_tskid );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�B�X�p�b�`�̋֎~.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		dis_dsp( void )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�̃f�B�X�p�b�`���֎~����.
	ercd = wi_DisabledDispatch();

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�f�B�X�p�b�`�̋���.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ena_dsp( void )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�̃f�B�X�p�b�`��������.
	ercd = wi_EnabledDispatch();

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�V�X�e����Ԃ̎Q��.
 *
 *	@param	[out]	pk_rsys		�V�X�e����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_sys( T_RSYS *pk_rsys )
{
	ER ercd;

	wi_CommonLock();

	//! �V�X�e�������擾����.
	ercd = wi_GetSystemInfo( pk_rsys );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�o�[�W�������̎Q��.
 *
 *	@param	[out]	pk_rver		�o�[�W���������i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_ver( T_RVER *pk_rver )
{
	ER ercd;

	wi_CommonLock();

	//! �o�[�W���������擾����.
	ercd = wi_GetVersion( pk_rver );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�R���t�B�O���[�V�������̎Q��.
 *
 *	@param	[out]	pk_rcfg		�R���t�B�O���[�V���������i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_cfg( T_RCFG *pk_rcfg )
{
	ER ercd;

	wi_CommonLock();

	//! �R���t�B�O���[�V���������擾����.
	ercd = wi_GetConfigInfo( pk_rcfg );

	wi_CommonUnlock();
	return ercd;
}

#endif	// __ITRON4__

/* End of file */
