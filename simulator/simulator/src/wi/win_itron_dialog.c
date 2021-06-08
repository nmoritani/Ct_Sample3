/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron_dialog.c
 *
 *	@brief	Windows版 iTRONサービスコールのダイアログ.
 *
 *	@author	金澤 宣明
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
 * ローカル関数定義.
 *
 ****************************************************************************/
static LRESULT CALLBACK	DlgProc( HWND hDlg, UINT msgId, WPARAM wparam, LPARAM lparam );
static void				OnInitDialog( HWND hDlg );
static void				OnCommand( HWND hDlg, WORD id, WORD status );

/****************************************************************************/
/*!
 *	@brief	ダイアログを開く.
 *
 *	@param	[in]	hInst		現在のインスタンスのハンドル.
 *
 *	@retval	ダイアログからの戻り値.
 */
int		OpenMainDialog( HINSTANCE hInst )
{
	//! ダイアログを開く.
	return DialogBox( hInst, MAKEINTRESOURCE( IDD_WIN_ITRON ), NULL, (DLGPROC)DlgProc );
}

/****************************************************************************/
/*!
 *	@brief	メッセージ・プロシージャ関数.
 *
 *	@param	[in]	hDlg	ダイアログ・ウインドウ・ハンドル.
 *	@param	[in]	msgId	メッセージID.
 *	@param	[in]	wparam	付加情報.
 *	@param	[in]	lparam	付加情報.
 *
 *	@retval	TRUE	メッセージ処理 完了.
 *	@retval	FALSE	Windowsでメッセージを処理する.
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
 *	@brief	ダイアログが作成されるときの処理.
 *
 *	@param	[in]	hDlg	ダイアログ・ウインドウ・ハンドル.
 *
 *	@retval	なし.
 */
static void		OnInitDialog( HWND hDlg )
{
}

/****************************************************************************/
/*!
 *	@brief	ダイアログのコマンド処理.
 *
 *	@param	[in]	hDlg	ダイアログ・ウインドウ・ハンドル.
 *	@param	[in]	id		ダイアログ・アイテムID.
 *	@param	[in]	status	ダイアログ・アイテム・ステータス.
 *
 *	@retval	なし.
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
