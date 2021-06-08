/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_task.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�^�X�N�@�\).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_TASK_H__
#define	__WI_TASK_H__

#include "wi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * �\���̒�`.
 *
 ****************************************************************************/
/*!
 *
 * @brief �^�X�N��I�u�W�F�N�g�\����.
 *
 */
typedef struct _WITSKOBJ {
	WIHDR				Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	struct _WITSKOBJ	*QueLink;		//!< �҂��s��ւ̃����N�p�|�C���^.
	HANDLE				hThread;		//!< �X���b�h��n���h��.
	HANDLE				hEvent;			//!< �C�x���g��n���h��.
	INT					EventType;		//!< �C�x���g���.
	UINT				TaskState;		//!< �^�X�N���.
	unsigned int		ThreadId;		//!< �X���b�hID�ԍ�.
	ATR					TaskAtr;		//!< �^�X�N����.
	FP					TaskAdr;		//!< �^�X�N�N���A�h���X.
	PRI					TaskPri;		//!< �^�X�N�D��x.
	PRI					InitPri;		//!< �^�X�N�N�����̏����D��x.
	INT					StackSize;		//!< �X�^�b�N�T�C�Y.
	VP					ExtInfo;		//!< �g�����.
	DWORD				StartCode;		//!< �^�X�N�N���R�[�h.
	INT					SuspendCnt;		//!< �^�X�N�����f������.
	INT					WakeupCnt;		//!< �^�X�N�̋N���v����.
	INT					ActiveCnt;		//!< �^�X�N�̋N���v����.
	ID					WaitId;			//!< �҂��I�u�W�F�N�g��ID.
	VP					Param[5];		//!< ���������p�̍�Ɨ̈�.
	BOOL				DelRes;			//!< TRUE = ���\�[�X�폜�ɂ��^�X�N�̋N��.
	BOOL				RelRes;			//!< TRUE = �҂���Ԃ̋��������ɂ��^�X�N�̋N��.
} WITSKOBJ;

/*!
 *
 * @brief �^�X�N�̏�ԎQ�Ɨp�\����.
 *
 */
typedef struct {
	ATR					TaskAtr;		//!< �^�X�N����.
	FP					TaskAdr;		//!< �^�X�N�N���A�h���X.
	UINT				TaskState;		//!< �^�X�N���.
	PRI					TaskPri;		//!< �^�X�N�D��x.
	PRI					InitPri;		//!< �^�X�N�N�����̏����D��x.
	ID					WaitId;			//!< �҂��I�u�W�F�N�g��ID.
	INT					EventType;		//!< �C�x���g���.
	INT					SuspendCnt;		//!< �^�X�N�����f������.
	INT					WakeupCnt;		//!< �^�X�N�̋N���v����.
	INT					ActiveCnt;		//!< �^�X�N�̋N���v����.
	INT					StackSize;		//!< �X�^�b�N�T�C�Y.
	VP					ExtInfo;		//!< �g�����.
} WITSKSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void		wi_InitTask( void );
void		wi_QuitTask( void );
ER			wi_CreateTask( INT id, const WITSKOBJ *obj );
ER			wi_DeleteTask( INT id );
ER			wi_StartTask( INT id, DWORD start_code, BOOL exist_stcd );
int			wi_CancelStartReq( INT id );
void		wi_ExitTask( void );
void		wi_ExpendTask( void );
ER			wi_TermTask( INT id );
ER			wi_ChangeTaskPriority( INT id, PRI priority );
ER			wi_RefarenceTaskPriority( INT id, PRI *priority );
ER			wi_RefarenceTask( INT id, WITSKSTAT *sts );
ER			wi_SleepTask( TMO tmout );
ER			wi_WakeupTask( INT id );
ER			wi_CancelWakeup( INT id, INT *p_wupcnt );
ER			wi_ReleaseWait( INT id );
ER			wi_SuspendTask( INT id );
ER			wi_ResumeTask( INT id );
ER			wi_ForceResumeTask( INT id );
ER			wi_DelayTask( TMO dlytim );
WITSKOBJ	*wi_GetTaskObject( INT id );
DWORD		wi_GetActiveTaskId( void );
ER			wi_TaskWait( INT wid, INT type, TMO tmout, ATR pri, WIHDR **que );
ER			wi_TaskWakeup( INT id, INT type, WIHDR **que );
WIHDR		*wi_AddWaitTaskList( INT id, ATR pri, WIHDR *que );
WIHDR		*wi_DelWaitTaskList( INT id, WIHDR *que );
DWORD		wi_GetWaitTaskListFirstId( WIHDR *que );
void		wi_WakeupDelResource( WIHDR *que );

#ifdef __cplusplus
}
#endif
#endif	// __WI_TASK_H__
/* End of file */
