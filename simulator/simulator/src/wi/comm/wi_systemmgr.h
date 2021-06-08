/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_systemmgr.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�V�X�e����ԊǗ��@�\).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_SYSTEMMGR_H__
#define	__WI_SYSTEMMGR_H__

#include "wi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitSysMgr( void );
void	wi_QuitSysMgr( void );
ER		wi_RotateTaskPriority( PRI tskpri );
ER		wi_GetTid( ID *p_tskid );
ER		wi_DisabledDispatch( void );
ER		wi_EnabledDispatch( void );
ER		wi_GetSystemInfo( T_RSYS *pk_rsys );
ER		wi_GetConfigInfo( T_RCFG *pk_rcfg );
#ifdef __WIN_ITRON3_H__
ER		wi_GetVersion( T_VER *pk_ver );
#else
ER		wi_GetVersion( T_RVER *pk_ver );
#endif

#ifdef __cplusplus
}
#endif
#endif	// __WI_SYSTEMMGR_H__
/* End of file */
