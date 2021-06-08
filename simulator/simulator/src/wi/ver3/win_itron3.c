/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron3.c
 *
 *	@brief	iTRON(Ver3.0)�̃T�[�r�X�R�[��.
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <stdio.h>
#include "kprintf.h"
#include "wi_config.h"

#ifdef	__ITRON3__
#include "win_itron3.h"
#include "wi_task.h"
#include "wi_semaphore.h"
#include "wi_event_flag.h"
#include "wi_mail_box.h"
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
	ercd = wi_CreateTask( tskid, &obj );

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
 *	@brief	�^�X�N�̏�ԎQ��.
 *
 *	@param	[in]	pk_rtsk	�^�X�N��Ԃ��i�[����̈�̃|�C���^.
 *	@param	[in]	tskid	�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_tsk( T_RTSK *pk_rtsk, ID tskid )
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
		pk_rtsk->exinf   = sts.ExtInfo;
		pk_rtsk->tskpri  = sts.TaskPri;
		pk_rtsk->tskstat = sts.TaskState;
		pk_rtsk->tskwait = sts.EventType;
		pk_rtsk->wid     = sts.WaitId;
		pk_rtsk->wupcnt  = sts.WakeupCnt;
		pk_rtsk->suscnt  = sts.SuspendCnt;
		pk_rtsk->tskatr  = sts.TaskAtr;
		pk_rtsk->task    = sts.TaskAdr;
		pk_rtsk->itskpri = sts.InitPri;
		pk_rtsk->stksz   = sts.StackSize;
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
 *	@brief	�N���҂� (�^�C���A�E�g�Ȃ�).
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
 *	@brief	�N���҂� (�^�C���A�E�g����).
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
 *	@brief	�^�X�N�̋N���v���𖳌���.
 *
 *	@param	[in]	p_wupcnt	�L���[�C���O����Ă����N���v���񐔂��i�[����̈�̃|�C���^.
 *	@param	[in]	tskid		�^�X�NID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		can_wup( INT *p_wupcnt, ID tskid )
{
	ER ercd;

	wi_CommonLock();

	//! �^�X�N�ւ̋N���v�����N���A����.
	ercd = wi_CancelWakeup( tskid, p_wupcnt );

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

	ercd = wi_DelayTask( (TMO)dlytim );

	wi_CommonUnlock();
	return ercd;
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
	obj.ExtInfo   = pk_csem->exinf;

	wi_CommonLock();

	//! �Z�}�t�H�𐶐�����.
	ercd = wi_CreateSemaphore( semid, &obj );

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
 *	@param	[out]	pk_rsem	�Z�}�t�H��Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	semid	�Z�}�t�HID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_sem( T_RSEM *pk_rsem, ID semid )
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
		pk_rsem->exinf  = sts.ExtInfo;
		pk_rsem->wtsk   = sts.WaitId;
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
	obj.Attribute = pk_cflg->flgatr & ~TA_CLR;
	obj.FlgVal    = pk_cflg->iflgptn;
	obj.ExtInfo   = pk_cflg->exinf;

	wi_CommonLock();

	//! �C�x���g�t���O�𐶐�����.
	ercd = wi_CreateEvFlag( flgid, &obj );

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
ER		set_flg( ID flgid, UINT setptn )
{
	ER ercd;

	wi_CommonLock();

	//! �C�x���g�t���O���Z�b�g����.
	ercd = wi_SetEvFlag( flgid, setptn );

	wi_CommonUnlock();
	return ercd;
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
ER		clr_flg( ID flgid, UINT clrptn )
{
	ER ercd;

	wi_CommonLock();

	//! �C�x���g�t���O���N���A����.
	ercd = wi_ClearEvFlag( flgid, clrptn );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�҂� (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[out]	p_flgptn	�҂��������̃r�b�g�p�^�[�����i�[����̈�̃|�C���^.
 *	@param	[in]	flgid		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	waiptn		�҂��r�b�g�p�^�[��.
 *	@param	[in]	wfmode		�҂����[�h.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wai_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode )
{
	//! �^�C���A�E�g�Ȃ��ŃC�x���g�҂�������.
	return twai_flg( p_flgptn, flgid, waiptn, wfmode, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�҂� (�|�[�����O).
 *
 *	@param	[out]	p_flgptn	�҂��������̃r�b�g�p�^�[�����i�[����̈�̃|�C���^.
 *	@param	[in]	flgid		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	waiptn		�҂��r�b�g�p�^�[��.
 *	@param	[in]	wfmode		�҂����[�h.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pol_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode )
{
	//! �C�x���g���������Ă��邩�ǂ����𒲂ׂ�.
	return twai_flg( p_flgptn, flgid, waiptn, wfmode, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O�҂� (�^�C���A�E�g����).
 *
 *	@param	[out]	p_flgptn	�҂��������̃r�b�g�p�^�[�����i�[����̈�̃|�C���^.
 *	@param	[in]	flgid		�C�x���g�t���OID�ԍ�.
 *	@param	[in]	waiptn		�҂��r�b�g�p�^�[��.
 *	@param	[in]	wfmode		�҂����[�h.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		twai_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �C�x���g�҂�������.
	ercd = wi_WaitEvFlag( flgid, p_flgptn, waiptn, wfmode, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�C�x���g�t���O��Ԃ̎Q��.
 *
 *	@param	[out]	pk_rflg	�C�x���g�t���O��Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	flgid	�C�x���g�t���OID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_flg( T_RFLG *pk_rflg, ID flgid )
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
		pk_rflg->exinf  = sts.ExtInfo;
		pk_rflg->wtsk   = (BOOL_ID)sts.WaitId;
		pk_rflg->flgptn = sts.FlgVal;
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
	obj.ExtInfo     = pk_cmbx->exinf;
	obj.MaxPriority = TMAX_MPRI;

	wi_CommonLock();

	//! ���[���{�b�N�X�𐶐�����.
	ercd = wi_CreateMailBox( mbxid, &obj );

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
 *	@param	[out]	ppk_msg	���b�Z�[�W��p�P�b�g�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rcv_msg( T_MSG **ppk_msg, ID mbxid )
{
	//! �^�C���A�E�g�Ȃ��Ń��[���{�b�N�X���烁�b�Z�[�W����M����.
	return trcv_msg( ppk_msg, mbxid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X����̎�M (�|�[�����O).
 *
 *	@param	[out]	ppk_msg	���b�Z�[�W��p�P�b�g�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		prcv_msg( T_MSG **ppk_msg, ID mbxid )
{
	//! ��M�҂��Ȃ��Ń��[���{�b�N�X���烁�b�Z�[�W����M����.
	return trcv_msg( ppk_msg, mbxid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	���[���{�b�N�X����̎�M (�^�C���A�E�g����).
 *
 *	@param	[out]	ppk_msg	���b�Z�[�W��p�P�b�g�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		trcv_msg( T_MSG **ppk_msg, ID mbxid, TMO tmout )
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
 *	@param	[out]	pk_rmbx	���[���{�b�N�X��Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	mbxid	���[���{�b�N�XID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mbx( T_RMBX *pk_rmbx, ID mbxid )
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
		pk_rmbx->exinf  = sts.ExtInfo;
		pk_rmbx->wtsk   = (BOOL_ID)sts.WaitId;
		pk_rmbx->pk_msg = sts.NextMsg;
	}
	wi_CommonUnlock();
	return ercd;
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
	obj.SndAttr = pk_cmbf->mbfatr & ~TA_TPRI;
	obj.RcvAttr = pk_cmbf->mbfatr;
	obj.MsgSize = pk_cmbf->bufsz;
	obj.MaxMsg  = pk_cmbf->maxmsz;
	obj.ExtInfo = pk_cmbf->exinf;

	wi_CommonLock();

	//! ���b�Z�[�W�o�b�t�@�𐶐�����.
	ercd = wi_CreateMsgBuffer( mbfid, &obj );

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
ER		snd_mbf( ID mbfid, VP msg, INT msgsz )
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
ER		psnd_mbf( ID mbfid, VP msg, INT msgsz )
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
ER		tsnd_mbf( ID mbfid, VP msg, INT msgsz, TMO tmout )
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
 *	@param	[out]	msg		���b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[out]	msg		���b�Z�[�W�T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		rcv_mbf( VP msg, INT *p_msgsz, ID mbfid )
{
	//! �^�C���A�E�g�Ȃ��Ń��b�Z�[�W�o�b�t�@���烁�b�Z�[�W����M����.
	return trcv_mbf( msg, p_msgsz, mbfid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@����̎�M (�|�[�����O).
 *
 *	@param	[out]	msg		���b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[out]	msg		���b�Z�[�W�T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		prcv_mbf( VP msg, INT *p_msgsz, ID mbfid )
{
	//! ��M�҂��Ȃ��Ń��b�Z�[�W�o�b�t�@���烁�b�Z�[�W����M����.
	return trcv_mbf( msg, p_msgsz, mbfid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@����̎�M (�^�C���A�E�g����).
 *
 *	@param	[out]	msg		���b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[out]	msg		���b�Z�[�W�T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		trcv_mbf( VP msg, INT *p_msgsz, ID mbfid, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! ���b�Z�[�W�o�b�t�@���烁�b�Z�[�W����M����.
	ercd = wi_ReceiveMsgBuffer( mbfid, msg, p_msgsz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�o�b�t�@�̏�ԎQ��.
 *
 *	@param	[out]	pk_rmbf	���b�Z�[�W�o�b�t�@��Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	mbfid	���b�Z�[�W�o�b�t�@ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mbf( T_RMBF *pk_rmbf, ID mbfid )
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
		pk_rmbf->exinf   = sts.ExtInfo;
		pk_rmbf->wtsk    = (BOOL_ID)sts.RcvWaitId;
		pk_rmbf->stsk    = (BOOL_ID)sts.SndWaitId;
		pk_rmbf->msgsz   = sts.MsgSize;
		pk_rmbf->frbufsz = sts.FreeSize;
	}
	wi_CommonUnlock();
	return ercd;
}

/***************************************
 *
 * �g��������ʐM�@�\ (�����f�u).
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
	obj.ExtInfo   = pk_cpor->exinf;

	wi_CommonLock();

	//! �����f�u�|�[�g�𐶐�����.
	ercd = wi_CreateRendPort( porid, &obj );

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
 *	@param	[in]	msg			�Ăяo�����b�Z�[�W�̃A�h���X.
 *	@param	[out]	p_rmsgsz	�������b�Z�[�W�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	calptn		�Ăяo�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	cmsgsz		�Ăяo�����b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		cal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz )
{
	//! �^�C���A�E�g�Ȃ��Ń����f�u���Ăяo��.
	return tcal_por( msg, p_rmsgsz, porid, calptn, cmsgsz, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�Ăяo�� (�|�[�����O).
 *
 *	@param	[in]	msg			�Ăяo�����b�Z�[�W�̃A�h���X.
 *	@param	[out]	p_rmsgsz	�������b�Z�[�W�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	calptn		�Ăяo�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	cmsgsz		�Ăяo�����b�Z�[�W�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pcal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz )
{
	//! ��t�҂��Ȃ��Ń����f�u���Ăяo��.
	return tcal_por( msg, p_rmsgsz, porid, calptn, cmsgsz, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�Ăяo�� (�^�C���A�E�g����).
 *
 *	@param	[in]	msg			�Ăяo�����b�Z�[�W�̃A�h���X.
 *	@param	[out]	p_rmsgsz	�������b�Z�[�W�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	calptn		�Ăяo�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	cmsgsz		�Ăяo�����b�Z�[�W�̃T�C�Y.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tcal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �����f�u���Ăяo��.
	ercd = wi_CallRendPort( porid, calptn, msg, cmsgsz, p_rmsgsz, tmout );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�󂯕t�� (�^�C���A�E�g�Ȃ�).
 *
 *	@param	[out]	p_rdvno		�����f�u�ԍ����i�[����̈�̃|�C���^.
 *	@param	[out]	msg			�Ăяo�����b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[out]	p_cmsgsz	�Ăяo�����b�Z�[�W�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	acpptn		�󂯕t�����I�������̃r�b�g�p�^�[��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		acp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn )
{
	//! �^�C���A�E�g�Ȃ��Ń����f�u���󂯕t����.
	return tacp_por( p_rdvno, msg, p_cmsgsz, porid, acpptn, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�󂯕t�� (�|�[�����O).
 *
 *	@param	[out]	p_rdvno		�����f�u�ԍ����i�[����̈�̃|�C���^.
 *	@param	[out]	msg			�Ăяo�����b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[out]	p_cmsgsz	�Ăяo�����b�Z�[�W�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	acpptn		�󂯕t�����I�������̃r�b�g�p�^�[��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pacp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn )
{
	//! �Ăяo���҂��Ȃ��Ń����f�u���󂯕t����.
	return tacp_por( p_rdvno, msg, p_cmsgsz, porid, acpptn, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�����f�u�󂯕t�� (�^�C���A�E�g����).
 *
 *	@param	[out]	p_rdvno		�����f�u�ԍ����i�[����̈�̃|�C���^.
 *	@param	[out]	msg			�Ăяo�����b�Z�[�W���i�[����̈�̃|�C���^.
 *	@param	[out]	p_cmsgsz	�Ăяo�����b�Z�[�W�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	porid		�����f�u�|�[�gID�ԍ�.
 *	@param	[in]	acpptn		�󂯕t�����I�������̃r�b�g�p�^�[��.
 *	@param	[in]	tmout		�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tacp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn, TMO tmout )
{
	ER ercd;

	wi_CommonLock();

	//! �����f�u���󂯕t����.
	ercd = wi_AcceptRendPort( porid, acpptn, p_rdvno, msg, p_cmsgsz, tmout );

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
ER		fwd_por( ID porid, UINT calptn, RNO rdvno, VP msg, INT cmsgsz )
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
ER		rpl_rdv( RNO rdvno, VP msg, INT cmsgsz )
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
 *	@param	[out]	pk_rpor	�����f�u�|�[�g��Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	porid	�����f�u�|�[�gID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_por( T_RPOR *pk_rpor, ID porid )
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
		pk_rpor->exinf = sts.ExtInfo;
		pk_rpor->wtsk  = (BOOL_ID)sts.CalWaitId;
		pk_rpor->atsk  = (BOOL_ID)sts.AcpWaitId;
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
	obj.ExtInfo   = pk_cmpf->exinf;
	obj.Attribute = pk_cmpf->mpfatr;
	obj.BlockCnt  = pk_cmpf->mpfcnt;
	obj.BlockSize = pk_cmpf->blfsz;

	wi_CommonLock();

	//! �Œ蒷�������v�[���𐶐�����.
	ercd = wi_CreateFixedMemPool( mpfid, &obj );

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
 *	@param	[in]	p_blf	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_blf( VP *p_blf, ID mpfid )
{
	//! �^�C���A�E�g�Ȃ��ŌŒ蒷�������u���b�N���l������.
	return tget_blf( p_blf, mpfid, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������u���b�N�̊l�� (�|�[�����O).
 *
 *	@param	[in]	p_blf	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pget_blf( VP *p_blf, ID mpfid )
{
	//! �l���҂��Ȃ��ŌŒ蒷�������u���b�N���l������.
	return tget_blf( p_blf, mpfid, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�Œ蒷�������u���b�N�̊l�� (�^�C���A�E�g����).
 *
 *	@param	[in]	p_blf	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tget_blf( VP *p_blf, ID mpfid, TMO tmout )
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
 *	@brief	�Œ蒷�������u���b�N�̕ԋp.
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
 *	@param	[out]	pk_rmpf	�������v�[����Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	mpfid	�������v�[��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mpf( T_RMPF *pk_rmpf, ID mpfid )
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
		pk_rmpf->exinf  = sts.ExtInfo;
		pk_rmpf->wtsk   = (BOOL_ID)sts.WaitId;
		pk_rmpf->frbcnt = sts.FreeBlock;
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
 *	@param	[in]	mplid	��������v�[��ID�ԍ�.
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
	obj.ExtInfo   = pk_cmpl->exinf;
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
 *	@brief	�ϒ��������v�[���̍폜.
 *
 *	@param	[in]	mpfid	��������v�[��ID�ԍ�.
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
 *	@param	[in]	p_blk	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *	@param	[in]	blksz	�������u���b�N�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_blk( VP p_blk, ID mplid, INT blksz )
{
	//! �^�C���A�E�g�Ȃ��ŉϒ��������u���b�N���l������.
	return tget_blk( p_blk, mplid, blksz, TMO_FEVR );
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������u���b�N�̊l�� (�|�[�����O).
 *
 *	@param	[in]	p_blk	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *	@param	[in]	blksz	�������u���b�N�̃T�C�Y.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		pget_blk( VP p_blk, ID mplid, INT blksz )
{
	//! �l���҂��Ȃ��ŉϒ��������u���b�N���l������.
	return tget_blk( p_blk, mplid, blksz, TMO_POL );
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������u���b�N�̊l�� (�^�C���A�E�g����).
 *
 *	@param	[in]	p_blk	�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *	@param	[in]	blksz	�������u���b�N�̃T�C�Y.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		tget_blk( VP p_blk, ID mplid, INT blksz, TMO tmout )
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

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̎Q��.
 *
 *	@param	[out]	pk_rmpl	�������v�[����Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	mplid	�������v�[��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_mpl( T_RMPL *pk_rmpl, ID mplid )
{
	ER			ercd;
	WIMPLSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rmpl ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �ϒ��������v�[���̏�Ԃ��擾����.
	ercd = wi_RefarenceVarMemPool( mplid, &sts );
	if( ercd == E_OK ){
		pk_rmpl->exinf = sts.ExtInfo;
		pk_rmpl->wtsk  = (BOOL_ID)sts.WaitId;
		pk_rmpl->frsz  = sts.TotalFreeSize;
		pk_rmpl->maxsz = sts.MaxFreeSize;
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

/***************************************
 *
 * ���ԊǗ��@�\ (�����n���h��).
 *
 **************************************/
/****************************************************************************/
/*!
 *	@brief	�����n���h����`.
 *
 *	@param	[in]	cycno	�����n���h���ԍ�.
 *	@param	[in]	pk_dcyc	�����n���h����`���.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		def_cyc( HNO cycno, const T_DCYC *pk_dcyc )
{
	ER			ercd;
	WICYCOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_dcyc ){
		return E_PAR;
	}
	//! �����n���h����`�����R�s�[����.
	memset( &obj, 0, sizeof(WICYCOBJ) );
	obj.Attribute = pk_dcyc->cycatr;
	obj.CycAdr    = pk_dcyc->cychdr;
	obj.Active    = (pk_dcyc->cycact & TCY_ON) ? TRUE : FALSE;
	obj.ExtInfo   = pk_dcyc->exinf;
	obj.CycleTime = ((DWORDLONG)(pk_dcyc->cyctim.utime) << 32) + (DWORDLONG)(pk_dcyc->cyctim.ltime);

	wi_CommonLock();

	//! �����n���h����o�^����.
	ercd = wi_DefineCycleHadler( cycno, &obj, TRUE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̊�������.
 *
 *	@param	[in]	cycno	�����n���h���ԍ�.
 *	@param	[in]	cycact	�����n���h���������.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		act_cyc( HNO cycno, UINT cycact )
{
	ER ercd;

	wi_CommonLock();

	//! �����n���h���̋N��/��~��ݒ肷��.
	ercd = wi_ActionCycleHadler( cycno,
								((cycact & TCY_ON ) != 0) ? TRUE : FALSE,
								((cycact & TCY_INI) != 0) ? TRUE : FALSE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̏�ԎQ��.
 *
 *	@param	[out]	pk_rcyc	�����n���h����Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	cycno	�����n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_cyc( T_RCYC *pk_rcyc, HNO cycno )
{
	ER			ercd;
	WICYCSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rcyc ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �����n���h���̏�Ԃ��擾����.
	ercd = wi_RefarenceCycleHadler( cycno, &sts );
	if( ercd == E_OK ){
		pk_rcyc->exinf        = sts.ExtInfo;
		pk_rcyc->lfttim.utime = (short)(sts.LeftTime >> 32 & 0x0000FFFF);
		pk_rcyc->lfttim.ltime = (long )(sts.LeftTime       & 0xFFFFFFFF);
		pk_rcyc->cycact       = (sts.Active ? TCY_ON : TCY_OFF);
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
 *	@brief	�A���[����n���h����`.
 *
 *	@param	[in]	almno	�A���[����n���h���ԍ�.
 *	@param	[in]	pk_dalm	�A���[����n���h����`���.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		def_alm( HNO almno, const T_DALM *pk_dalm )
{
	ER			ercd;
	WIALMOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_dalm ){
		return E_PAR;
	}
	//! �A���[����n���h���o�^�����R�s�[����.
	memset( &obj, 0, sizeof(WIALMOBJ) );
	obj.Attribute = pk_dalm->almatr;
	obj.AlmAdr    = pk_dalm->almhdr;
	obj.TimeMode  = pk_dalm->tmmode;
	obj.AlmTime   = ((DWORDLONG)(pk_dalm->almtim.utime) << 32) + (DWORDLONG)(pk_dalm->almtim.ltime);
	obj.ExtInfo   = pk_dalm->exinf;
	obj.Active    = pk_dalm->almhdr ? TRUE : FALSE;

	//! �A���[����n���h���̋N�����������ݎ�������̑��Ύ����ɂ���.
	if( (obj.TimeMode & TTM_REL) != 0 ){
		obj.AlmTime += wi_GetSystemTime();
	}
	wi_CommonLock();

	//! �A���[����n���h����o�^����.
	ercd = wi_DefineAlarmHadler( almno, &obj, TRUE );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̏�ԎQ��.
 *
 *	@param	[out]	pk_ralm	�A���[����n���h����Ԃ��i�[����\���̂̃|�C���^.
 *	@param	[in]	almno	�A���[����n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ref_alm( T_RALM *pk_ralm, HNO almno )
{
	ER			ercd;
	WIALMSTAT	sts;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_ralm ){
		return E_PAR;
	}
	wi_CommonLock();

	//! �A���[����n���h���̏�Ԃ��擾����.
	ercd = wi_RefarenceAlarmHadler( almno, &sts );
	if( ercd == E_OK ){
		pk_ralm->exinf        = sts.ExtInfo;
		pk_ralm->lfttim.utime = (short)(sts.LeftTime >> 32 & 0x0000FFFF);
		pk_ralm->lfttim.ltime = (long )(sts.LeftTime       & 0xFFFFFFFF);
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
 *	@param	[in]	dintno		���荞�݃n���h���ԍ�.
 *	@param	[in]	pk_dint		���荞�݃n���h����`���\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		def_int( UINT dintno, const T_DINT *pk_dint )
{
	ER			ercd;
	WIINTOBJ	obj;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_dint ){
		return E_PAR;
	}
	//! ���荞�݃n���h����`�����R�s�[����.
	memset( &obj, 0, sizeof(WIINTOBJ) );
	obj.Attribute = pk_dint->intatr;
	obj.IntrAdr   = pk_dint->inthdr;

	wi_CommonLock();

	//! ���荞�݃n���h����o�^����.
	ercd = wi_DefineIntrruptHander( dintno, &obj );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���荞�݂̋֎~.
 *
 *	@param	[in]	eintno		���荞�݃n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		dis_int( UINT eintno )
{
	ER ercd;

	wi_CommonLock();

	//! ���荞�݂��֎~����.
	ercd = wi_DisableIntrrupt( eintno );

	wi_CommonUnlock();
	return ercd;
}

/****************************************************************************/
/*!
 *	@brief	���荞�݂̋���.
 *
 *	@param	[in]	eintno		���荞�݃n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		ena_int( UINT eintno )
{
	ER ercd;

	wi_CommonLock();

	//! ���荞�݂�������.
	ercd = wi_EnableIntrrupt( eintno );

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
 *	@param	[out]	pk_ver		�o�[�W���������i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		get_ver( T_VER *pk_ver )
{
	ER ercd;

	wi_CommonLock();

	//! �o�[�W���������擾����.
	ercd = wi_GetVersion( pk_ver );

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
#endif	// __ITRON3__

/* End of file */
