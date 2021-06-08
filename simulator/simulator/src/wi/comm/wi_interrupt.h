/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_interrupt.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (���荞�݋@�\).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_INTERRUPT_H__
#define	__WI_INTERRUPT_H__

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
 * @brief ���荞�݃n���h����I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute; 		//!< ���荞�݃n���h������.
	FP			IntrAdr;		//!< ���荞�݃n���h���̃A�h���X.
	BOOL		Enabled;		//!< TRUE = ���荞�݋���.
	UINT		IntrCnt;		//!< ���荞�݂�ۗ�������.
} WIINTOBJ;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitInterrupt( void );
void	wi_QuitInterrupt( void );
ER		wi_DefineIntrruptHander( INT no, const WIINTOBJ *obj );
ER		wi_DisableIntrrupt( INT no );
ER		wi_EnableIntrrupt( INT no );
ER		wi_LockCPU( void );
ER		wi_UnLockCPU( void );
BOOL	wi_IsCPULock( void );
void	wi_DelayedIntrrupt( void );
void	wi_IntrruptRequest( INT no );
void	wi_ClearIntrruptRequest( INT no );

#ifdef __cplusplus
}
#endif
#endif	// __WI_INTERRUPT_H__
/* End of file */
