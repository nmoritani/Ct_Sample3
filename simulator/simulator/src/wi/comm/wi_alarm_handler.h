/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_alarm_handler.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�A���[����n���h��).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_ALARM_HANDLER_H__
#define	__WI_ALARM_HANDLER_H__

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
 * @brief �A���[����n���h��.�I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;				//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute; 			//!< �A���[����n���h������.
	FP			AlmAdr;				//!< �A���[����n���h���̃A�h���X.
	BOOL		Active;				//!< �A���[����n���h���̋N�����.
	UINT		TimeMode;			//!< �N�������w�胂�[�h.
	DWORDLONG	AlmTime; 			//!< �N������.
	VP			ExtInfo;			//!< �g�����.
} WIALMOBJ;

/*!
 *
 * @brief �A���[����n���h����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	DWORDLONG	LeftTime; 			//!< �N�������܂ł̎���.
	BOOL		Active;				//!< �A���[����n���h���̋N�����.
	VP			ExtInfo;			//!< �g�����.
} WIALMSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitAlarmHadler( void );
void	wi_QuitAlarmHadler( void );
ER		wi_DefineAlarmHadler( INT no, const WIALMOBJ *obj, BOOL ovr );
ER		wi_DeleteAlarmHadler( INT no );
ER		wi_StartAlarmHadler( INT no, DWORDLONG almtim );
ER		wi_StopAlarmHadler( INT no );
ER		wi_RefarenceAlarmHadler( INT no, WIALMSTAT *sts );
void	wi_CallAlarmHandler( DWORDLONG now_time );

#ifdef __cplusplus
}
#endif
#endif	// __WI_ALARM_HANDLER_H__
/* End of file */
