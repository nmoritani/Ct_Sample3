/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[��.
 *
 *	@author	���V �閾
 */
#ifndef	__WIN_ITRON_H__
#define	__WIN_ITRON_H__

#include "wi_config.h"
#ifdef	__ITRON3__
#include "win_itron3.h"
#endif
#ifdef	__ITRON4__
#include "win_itron4.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * �O���֐���`.
 *
 ****************************************************************************/
extern void		startup_target( void );
extern void		request_interrupt( UINT num );
extern void		clear_interrupt_request( UINT num );

#ifdef __cplusplus
}
#endif
#endif	// __WIN_ITRON_H__
/* End of file */
