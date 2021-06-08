/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_systemmgr.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�V�X�e����ԊǗ��@�\).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_systemmgr.h"

static BOOL	DisEnabled = TRUE;;

/****************************************************************************/
/*!
 *	@brief	�V�X�e����ԊǗ��@�\�̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitSysMgr( void )
{
}

/****************************************************************************/
/*!
 *	@brief	�V�X�e����ԊǗ��@�\�̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitSysMgr( void )
{
}

/****************************************************************************/
/*!
 *	@brief	�^�X�N�̗D�揇�ʂ̉�].
 *
 *	@param	[in]	tskpri	�D�揇�ʂ���]����D��x.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RotateTaskPriority( PRI tskpri )
{
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	���s��Ԃ̃^�X�NID�̎Q��.
 *
 *	@param	[out]	p_tskid		�^�X�NID�ԍ����i�[����̈�̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_GetTid( ID *p_tskid )
{
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !p_tskid ){
		return E_PAR;
	}
	//! �{�T�[�r�X�R�[�����s�����^�X�N��ID��Ԃ�.
	*p_tskid = wi_GetTaskId();

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�f�B�X�p�b�`�̋֎~.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DisabledDispatch( void )
{
	DisEnabled = FALSE;
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	�f�B�X�p�b�`�̋���.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_EnabledDispatch( void )
{
	DisEnabled = TRUE;
	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	�V�X�e����Ԃ̎Q��.
 *
 *	@param	[out]	pk_rsys		�V�X�e����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_GetSystemInfo( T_RSYS *pk_rsys )
{
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rsys ){
		return E_PAR;
	}
	//! �\���̂��N���A����.
	memset( pk_rsys, 0, sizeof(T_RSYS) );

	return E_NOSPT;
}

/****************************************************************************/
/*!
 *	@brief	�o�[�W�������̎Q��.
 *
 *	@param	[out]	pk_ver		�o�[�W���������i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
#ifdef __WIN_ITRON3_H__
ER		wi_GetVersion( T_VER *pk_ver )
{
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_ver ){
		return E_PAR;
	}
	//! �\���̂��N���A����.
	memset( pk_ver, 0, sizeof(T_VER) );

	return E_NOSPT;
}
#else
ER		wi_GetVersion( T_RVER *pk_ver )
{
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_ver ){
		return E_PAR;
	}
	//! �\���̂��N���A����.
	memset( pk_ver, 0, sizeof(T_RVER) );

	return E_NOSPT;
}
#endif

/****************************************************************************/
/*!
 *	@brief	�R���t�B�O���[�V�������̎Q��.
 *
 *	@param	[out]	pk_rcfg		�R���t�B�O���[�V���������i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_GetConfigInfo( T_RCFG *pk_rcfg )
{
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !pk_rcfg ){
		return E_PAR;
	}
	//! �\���̂��N���A����.
	memset( pk_rcfg, 0, sizeof(T_RCFG) );

	return E_NOSPT;
}

/* End of file */
