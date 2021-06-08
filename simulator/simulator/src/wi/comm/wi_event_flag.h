/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_event_flag.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�C�x���g�t���O).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_EVENT_FLAG_H__
#define	__WI_EVENT_FLAG_H__

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
 * @brief �C�x���g�t���O��I�u�W�F�N�g�\����.
 *
 */
typedef struct {
	WIHDR		Hdr;			//!< �I�u�W�F�N�g��w�b�_.
	ATR			Attribute;		//!< �C�x���g�t���O����.
	UINT		FlgVal;			//!< �C�x���g�t���O�̃r�b�g�p�^�[��.
	VP			ExtInfo;		//!< �g�����.
	WIHDR		*WaitQue;		//!< �^�X�N�̑҂��s��̃|�C���^.
} WIFLGOBJ;

/*!
 *
 * @brief �C�x���g�t���O�̏�ԎQ�Ɨp�\����.
 *
 */
typedef struct {
	UINT		FlgVal;			//!< �C�x���g�t���O�̃r�b�g�p�^�[��.
	INT			WaitId;			//!< �C�x���g�t���O�҂��s��̐擪�̃^�X�N��ID�ԍ�.
	VP			ExtInfo;		//!< �g�����.
} WIFLGSTAT;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
void	wi_InitEvFlag( void );
void	wi_QuitEvFlag( void );
ER		wi_CreateEvFlag( INT id, WIFLGOBJ *obj );
ER		wi_DeleteEvFlag( INT id );
ER		wi_SetEvFlag( INT id, UINT setptn );
ER		wi_ClearEvFlag( INT id, UINT clrptn );
ER		wi_WaitEvFlag( INT id, UINT *p_flgptn, UINT waiptn, UINT wfmode, TMO tmout );
ER		wi_RefarenceEvFlag( INT id, WIFLGSTAT *sts );
void	wi_AllReleaseEvFlag( INT id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_EVENT_FLAG_H__
/* End of file */
