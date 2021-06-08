/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron_dialog.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[���̃_�C�A���O.
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include "kprintf.h"
#include "win_itron.h"
#include "wi_resource.h"
#include "wi_common.h"
#include "win_itron_dialog.h"

/****************************************************************************
 *
 * ���[�J���֐���`.
 *
 ****************************************************************************/
static LRESULT CALLBACK	DlgProc( HWND hDlg, UINT msgId, WPARAM wparam, LPARAM lparam );
static void				OnInitDialog( HWND hDlg );
static void				OnCommand( HWND hDlg, WORD id, WORD status );

/****************************************************************************/
/*!
 *	@brief	�_�C�A���O���J��.
 *
 *	@param	[in]	hInst		���݂̃C���X�^���X�̃n���h��.
 *
 *	@retval	�_�C�A���O����̖߂�l.
 */
int		OpenMainDialog( HINSTANCE hInst )
{
	//! �_�C�A���O���J��.
	return DialogBox( hInst, MAKEINTRESOURCE( IDD_WIN_ITRON ), NULL, (DLGPROC)DlgProc );
}

/****************************************************************************/
/*!
 *	@brief	���b�Z�[�W�E�v���V�[�W���֐�.
 *
 *	@param	[in]	hDlg	�_�C�A���O�E�E�C���h�E�E�n���h��.
 *	@param	[in]	msgId	���b�Z�[�WID.
 *	@param	[in]	wparam	�t�����.
 *	@param	[in]	lparam	�t�����.
 *
 *	@retval	TRUE	���b�Z�[�W���� ����.
 *	@retval	FALSE	Windows�Ń��b�Z�[�W����������.
 */
static LRESULT CALLBACK	DlgProc( HWND hDlg, UINT msgId, WPARAM wparam, LPARAM lparam )
{
	switch( msgId ){
	case WM_INITDIALOG:
		OnInitDialog( hDlg );
		break;

	case WM_COMMAND:
		OnCommand( hDlg, LOWORD( wparam ), HIWORD( wparam ) );
		break;

	default:
		return FALSE;
	}
	return TRUE;
}

/****************************************************************************/
/*!
 *	@brief	�_�C�A���O���쐬�����Ƃ��̏���.
 *
 *	@param	[in]	hDlg	�_�C�A���O�E�E�C���h�E�E�n���h��.
 *
 *	@retval	�Ȃ�.
 */
static void		OnInitDialog( HWND hDlg )
{
}

/****************************************************************************/
/*!
 *	@brief	�_�C�A���O�̃R�}���h����.
 *
 *	@param	[in]	hDlg	�_�C�A���O�E�E�C���h�E�E�n���h��.
 *	@param	[in]	id		�_�C�A���O�E�A�C�e��ID.
 *	@param	[in]	status	�_�C�A���O�E�A�C�e���E�X�e�[�^�X.
 *
 *	@retval	�Ȃ�.
 */
static void		OnCommand( HWND hDlg, WORD id, WORD status )
{
	switch( id ){
	case IDCANCEL:
		EndDialog( hDlg, 0 );
		break;
	}
}

/* End of file */
