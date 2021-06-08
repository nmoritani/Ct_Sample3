/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_rendezvous_port.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�����f�u).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_RENDEZVOUS_PORT_H__
#define	__WI_RENDEZVOUS_PORT_H__

#include "wi_common.h"
#include "wi_task.h"

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
 * @brief �����f�u�|�[�g��I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute;		//!< �����f�u�|�[�g����.
	INT			MaxCalMsg;		//!< �ďo���̃��b�Z�[�W�̍ő咷.
	INT			MaxRepMsg;		//!< �ԓ����̃��b�Z�[�W�̍ő咷.
	WIHDR		*CalWaitQue;	//!< �����f�u�ďo�҂��^�X�N�̑҂��s��̃|�C���^.
	WIHDR		*AcpWaitQue;	//!< �����f�u��t�҂��^�X�N�̑҂��s��̃|�C���^.
	VP			ExtInfo;		//!< �g�����.
} WIPOROBJ;

/*!
 *
 * @brief �����f�u�|�[�g��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	INT			CalWaitId;		//!< �����f�u�ďo�҂��^�X�N�̑҂��s��̐擪�̃^�X�N��ID�ԍ�.
	INT			AcpWaitId;		//!< �����f�u��t�҂��^�X�N�̑҂��s��̐擪�̃^�X�N��ID�ԍ�.
	VP			ExtInfo;		//!< �g�����.
} WIPORSTAT;

/*!
 *
 * @brief �����f�u��I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	INT			TaskId;			//!< �����f�u�I���҂������Ă���^�X�NID�ԍ�.
	INT			MaxRepMsg;		//!< �ԓ����̃��b�Z�[�W�̍ő咷.
} WIRDVOBJ;

/*!
 *
 * @brief �����f�u��Ԃ̎Q�Ɨp�\����.
 *
 */
typedef struct {
	DWORD		WaitId;			//!< �����f�u�I���҂��^�X�N��ID�ԍ�.
} WIRDVSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitRendPort( void );
void	wi_QuitRendPort( void );
ER		wi_CreateRendPort( INT id, const WIPOROBJ *pk_cpor );
ER		wi_DeleteRendPort( INT id );
ER		wi_CallRendPort( INT id, UINT ptn, VP msg, INT csize, INT *rsize, TMO tmout );
ER		wi_AcceptRendPort( INT id, UINT ptn, INT *no, VP msg, INT *size, TMO tmout );
ER		wi_FowardRendPort( INT id, UINT ptn, INT no, VP msg, INT cmsgsz );
ER		wi_ReplayRendPort( INT no, VP msg, INT size );
ER		wi_RefarenceRendPort( INT id, WIPORSTAT *sts );
ER		wi_RefarenceRendStat( INT no, WIRDVSTAT *sts );
void	wi_AllReleaseRendPort( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_RENDEZVOUS_PORT_H__
/* End of file */
