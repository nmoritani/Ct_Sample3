/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_common.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (���̑����ʊ֐�).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_COMMON_H__
#define	__WI_COMMON_H__

#include "win_itron.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * �}�N����`.
 *
 ****************************************************************************/
#ifdef	SAFE_RELEASE
#undef	SAFE_RELEASE
#endif
#define	SAFE_RELEASE( _a )	if( _a ){ free( _a ); _a = NULL; }

/****************************************************************************
 *
 * �\���̒�`.
 *
 ****************************************************************************/
/*!
 *
 * @brief �I�u�W�F�N�g��w�b�_�\����.
 *
 */
typedef struct _WIHDR {
	struct _WIHDR	*Next;		//!< �����N��|�C���^.
	INT				Id;			//!< �I�u�W�F�N�g���ʎq.
} WIHDR, * LPWIHDR;

/****************************************************************************
 *
 * �֐���`.
 *
 ****************************************************************************/
BOOL		wi_CommonInit( void );
void		wi_CommonQuit( void );
void		wi_CommonLock( void );
void		wi_CommonUnlock( void );
void		wi_DormantThread( HANDLE hThread, DWORD wait_time );
void		wi_SetSystemTime( DWORDLONG tim );
DWORDLONG	wi_GetSystemTime( void );
ID			wi_GetTaskId( void );
void		wi_AddObject( LPWIHDR new_obj, LPWIHDR *obj_list );
void		wi_DelObject( LPWIHDR new_obj, LPWIHDR *obj_list );
void		*wi_GetObject( INT id,  LPWIHDR obj_list );
WIHDR		*wi_CreateObject( INT id, INT max_id, INT size, const void *param, WIHDR *obj_list, ER *ercd );
WIHDR		*wi_FindObject( INT id, INT max_id, WIHDR *obj_list, ER *ercd );
DWORD		wi_IncRingPositon( DWORD pos, DWORD size );
DWORD		wi_CvtTimeOutValue( TMO tmout );

// win_itron_main.c�Ɏ��̂�����.
void		wi_DeleteTaskReq( ID id );

#ifdef __cplusplus
}
#endif
#endif	// __WI_COMMON_H__
/* End of file */
