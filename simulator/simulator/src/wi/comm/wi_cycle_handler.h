/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_cycle_handler.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�����n���h��).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_CYCLE_HANDLER_H__
#define	__WI_CYCLE_HANDLER_H__

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
 * @brief �����n���h������\�[�X�\����.
 *
 */
typedef struct {
	WIHDR			Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR				Attribute; 		//!< �����n���h������.
	FP				CycAdr;			//!< �����n���h���̃A�h���X.
	BOOL			Active;			//!< �����n���h���̊������.
	DWORDLONG		CycleTime;		//!< �����N�����ԊԊu.
	DWORDLONG		StartTime;		//!< �Ō�Ɏ����n���h�����Ăяo��������.
	DWORDLONG		CyclePhs; 		//!< �����N���ʑ�.
	VP				ExtInfo;		//!< �g�����.
} WICYCOBJ;

/*!
 *
 * @brief �����n���h����Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	VP			ExtInfo;			//!< �g�����.
	DWORDLONG	LeftTime; 			//!< ���̋N�������܂ł̎���.
	BOOL		Active;				//!< �����n���h���̊������.
} WICYCSTAT;


/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitCycleHadler( void );
void	wi_QuitCycleHadler( void );
ER		wi_DefineCycleHadler( INT no, const WICYCOBJ *obj, BOOL ovr );
ER		wi_DeleteCycleHadler( INT no );
ER		wi_ActionCycleHadler( INT no, BOOL act, BOOL init );
ER		wi_RefarenceCycleHadler( INT no, WICYCSTAT *sts );
void	wi_CycleTimer( DWORDLONG now_time );

#ifdef __cplusplus
}
#endif
#endif	// __WI_CYCLE_HANDLER_H__
/* End of file */
