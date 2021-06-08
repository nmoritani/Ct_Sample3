/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_cycle_handler.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�����n���h��).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_cycle_handler.h"

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR		*ObjList;		//!< �����n���h������X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�����n���h���̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitCycleHadler( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitCycleHadler( void )
{
	WIHDR		*next_ptr;
	WICYCOBJ	*p = (WICYCOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! �����n���h����I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̎����n���h����I�u�W�F�N�g�\���̂����o��.
		p = (WICYCOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�����n���h����`.
 *
 *	@param	[in]	no		�����n���h���ԍ�.
 *	@param	[in]	obj		�����n���h����I�u�W�F�N�g�\���̂̃|�C���^.
 *	@param	[in]	ovr		TRUE = �o�^�ς�ID�ɏ㏑��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DefineCycleHadler( INT no, const WICYCOBJ *obj, BOOL ovr )
{
	ER			ercd;
	WICYCOBJ	*p;

	p = (WICYCOBJ *)wi_GetObject( no, ObjList );
	if( p ){
		//! �o�^�ς݃n���h���ɏ㏑���֎~�̏ꍇ�̓G���[�I���ɂ���.
		if( !ovr ){
			return E_OBJ;
		}
		//! ���ɓo�^���Ă���n���h���ԍ��̏ꍇ�͓o�^���㏑������.
		p->Hdr.Id    = no;
		p->Attribute = obj->Attribute;
		p->CycAdr    = obj->CycAdr;
		p->Active    = obj->Active;
		p->ExtInfo   = obj->ExtInfo;
		p->CycleTime = obj->CycleTime;
		p->StartTime = wi_GetSystemTime();
		return E_OK;
	}
	//! �����n���h����I�u�W�F�N�g���쐬����.
	p = (WICYCOBJ *)wi_CreateObject( no, TMAX_MAXCYC, sizeof(WICYCOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g�Ɏ����n���h����ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̍폜.
 *
 *	@param	[in]	no		�����n���h���ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteCycleHadler( INT no )
{
	ER			ercd;
	WICYCOBJ	*p;

	//! �����n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WICYCOBJ *)wi_FindObject( no, TMAX_MAXCYC, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y����������n���h������菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �����n���h����I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̊�������.
 *
 *	@param	[in]	no		�����n���h���ԍ�.
 *	@param	[in]	act		TRUE = �N�� / FALSE = ��~.
 *	@param	[in]	init	TRUE = �������v��.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ActionCycleHadler( INT no, BOOL act, BOOL init )
{
	ER			ercd;
	WICYCOBJ	*p;

	//! �����n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WICYCOBJ *)wi_FindObject( no, TMAX_MAXCYC, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �����n���h���̊��������Z�b�g����.
	p->Active = act;

	//! �����J�E���^������������.
	if( init ){
		p->StartTime = wi_GetSystemTime();
	}
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̏�ԎQ��.
 *
 *	@param	[in]	no		�����n���h���ԍ�.
 *	@param	[out]	sts		�����n���h����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceCycleHadler( INT no, WICYCSTAT *sts )
{
	ER			ercd;
	WICYCOBJ	*p;
	DWORDLONG	now_time;

	//! �����n���h���ԍ��̃I�u�W�F�N�g���擾����.
	p = (WICYCOBJ *)wi_FindObject( no, TMAX_MAXCYC, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���ݎ������擾����.
	now_time = wi_GetSystemTime();

	//! �N�������܂ł̎��Ԃ��v�Z����.
	if( (now_time - p->StartTime) >= p->CycleTime ){
		sts->LeftTime = 0;
	}else{
		sts->LeftTime = p->CycleTime - (now_time - p->StartTime);
	}
	//! �����n���h���̏�Ԃ��\���̂ɃZ�b�g����.
	sts->Active  = p->Active;
	sts->ExtInfo = p->ExtInfo;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�����n���h���̃^�C�}����.
 *
 *	@param	[in]	now_time	���ݎ���.
 *
 *	@retval	�Ȃ�.
 */
void	wi_CycleTimer( DWORDLONG now_time )
{
	WICYCOBJ *p = (WICYCOBJ *)ObjList;

	while( p ){
		if( p->Active ){
			//! �����J�E���^���������Ԍo�߂������ǂ������`�F�b�N����.
			if( (now_time - p->StartTime) >= p->CycleTime ){

				//! �����n���h�����Ăяo��.
				if( p->CycAdr ){
					p->CycAdr();
				}
				//! �����n���h�����Ăяo����������ۑ�����.
				p->StartTime = now_time;
			}
		}
		//! ���X�g���玟�̎����n���h�������o��.
		p = (WICYCOBJ *)(p->Hdr.Next);
	}
}

/* End of file */
