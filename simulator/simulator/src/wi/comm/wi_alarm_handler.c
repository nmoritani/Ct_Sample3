/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_alarm_handler.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�A���[����n���h��).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_alarm_handler.h"

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR	*ObjList;		//!< �A���[����n���h������X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitAlarmHadler( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitAlarmHadler( void )
{
	WIHDR		*next_ptr;
	WIALMOBJ	*p = (WIALMOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! �A���[����n���h����I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃A���[����n���h����I�u�W�F�N�g�\���̂����o��.
		p = (WIALMOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h����`.
 *
 *	@param	[in]	no		�A���[����n���h���ԍ�.
 *	@param	[in]	obj		�A���[����n���h��.�I�u�W�F�N�g�\���̂̃|�C���^.
 *	@param	[in]	ovr		TRUE = �o�^�ς�ID�ɏ㏑��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DefineAlarmHadler( INT no, const WIALMOBJ *obj, BOOL ovr )
{
	ER			ercd;
	WIALMOBJ	*p;

	p = (WIALMOBJ *)wi_GetObject( no, ObjList );
	if( p ){
		//! �o�^�ς݃n���h���ɏ㏑���֎~�̏ꍇ�̓G���[�I���ɂ���.
		if( !ovr ){
			return E_OBJ;
		}
		//! ���ɓo�^���Ă���n���h���ԍ��̏ꍇ�͓o�^���㏑������.
		p->Attribute = obj->Attribute;
		p->AlmAdr    = obj->AlmAdr;
		p->TimeMode  = obj->TimeMode;
		p->AlmTime   = obj->AlmTime;
		p->ExtInfo   = obj->ExtInfo;
		p->Active    = obj->Active;
		return E_OK;
	}
	//! �A���[����n���h����I�u�W�F�N�g���쐬����.
	p = (WIALMOBJ *)wi_CreateObject( no, TMAX_MAXALM, sizeof(WIALMOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g�ɃA���[����n���h����ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̍폜.
 *
 *	@param	[in]	no		�A���[����n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteAlarmHadler( INT no )
{
	ER			ercd;
	WIALMOBJ	*p;

	//! �A���[����n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WIALMOBJ *)wi_FindObject( no, TMAX_MAXALM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y������A���[����n���h������菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �A���[����n���h����I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̋N��.
 *
 *	@param	[in]	no		�A���[����n���h���ԍ�.
 *	@param	[in]	almtim	�N������.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_StartAlarmHadler( INT no, DWORDLONG almtim )
{
	ER			ercd;
	WIALMOBJ	*p;

	//! �A���[����n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WIALMOBJ *)wi_FindObject( no, TMAX_MAXALM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �A���[����n���h���̋N�����������ݎ�������̑��Ύ����ŃZ�b�g����.
	p->AlmTime = wi_GetSystemTime() + almtim;

	//! �A���[����n���h���̓����Ԃ��u�N�����v�ɂ���.
	p->Active  = TRUE;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̒�~.
 *
 *	@param	[in]	no		�A���[����n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_StopAlarmHadler( INT no )
{
	ER			ercd;
	WIALMOBJ	*p;

	//! �A���[����n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WIALMOBJ *)wi_FindObject( no, TMAX_MAXALM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �A���[����n���h���̓����Ԃ��u��~���v�ɂ���.
	p->Active = FALSE;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̏�ԎQ��.
 *
 *	@param	[in]	no		�A���[����n���h���ԍ�.
 *	@param	[out]	sts		�A���[����n���h����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceAlarmHadler( INT no, WIALMSTAT *sts )
{
	ER			ercd;
	WIALMOBJ	*p;
	DWORDLONG	now_time;

	//! �A���[����n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WIALMOBJ *)wi_FindObject( no, TMAX_MAXALM, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���ݎ������擾����.
	now_time = wi_GetSystemTime();

	//! �N�������܂ł̎��Ԃ��v�Z����.
	if( now_time >= p->AlmTime ){
		sts->LeftTime = 0;
	}else{
		sts->LeftTime = p->AlmTime - now_time;
	}
	//! �A���[����n���h���̏�Ԃ��\���̂ɃZ�b�g����.
	sts->Active  = p->Active;
	sts->ExtInfo = p->ExtInfo;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�A���[����n���h���̎�������.
 *
 *	@param	[in]	now_time	���ݎ���.
 *
 *	@retval	�Ȃ�.
 */
void	wi_CallAlarmHandler( DWORDLONG now_time )
{
	WIALMOBJ *next_ptr;
	WIALMOBJ *p = (WIALMOBJ *)ObjList;
	while( p ){

		next_ptr = (WIALMOBJ *)p->Hdr.Next;

		if( now_time >= p->AlmTime ){
			if( p->Active ){
				if( p->AlmAdr ){
					p->AlmAdr();
				}
				p->Active = FALSE;
			}
			//! ���X�g����Y������A���[����n���h������菜��.
			wi_DelObject( (WIHDR *)p, &ObjList );

			//! �A���[����n���h����I�u�W�F�N�g�\���̂��������.
			SAFE_RELEASE( p );
		}
		p = next_ptr;
	}
}

/* End of file */
