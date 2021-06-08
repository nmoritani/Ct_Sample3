/****************************************************************************
 *	Copylight(C) 2007-2011 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	kprintf.c
 *
 *	@brief	デバッグモニタ・クライアントの公開関数.
 *
 *	@author	金澤 宣明
 */
#include <windows.h>
#include "kprintf.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef	_UNICODE
//static int			dummy_kprintf( const wchar_t *fmt, ... );
static int			dummy_kprintf( const char *fmt, ... );
#else
static int			dummy_kprintf( const char *fmt, ... );
#endif

static HINSTANCE	DllInstance = NULL;			//!< DLLのインスタンス・ハンドル.
KDBMONPROC			kprintf = dummy_kprintf;

/****************************************************************************/
/*!
 *	@brief	デバッグモニタ・クライアントを起動する.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	kprint_init( void )
{
	KDBMONPROC	proc;

#ifdef	_UNICODE
	DllInstance = LoadLibrary( L"kprint.dll" );
#else
	DllInstance = LoadLibrary( "kprint.dll" );
#endif
	if( !DllInstance ){
		kprintf = dummy_kprintf;
		return;
	}
#ifdef	_UNICODE
	proc = (KDBMONPROC)GetProcAddress( DllInstance, "kwprintf" );
#else
	proc = (KDBMONPROC)GetProcAddress( DllInstance, "kprintf" );
#endif
	if( !proc ){
		kprintf = dummy_kprintf;
		return;
	}
	kprintf = proc;
}

/****************************************************************************/
/*!
 *	@brief	デバッグモニタ・クライアントを終了する.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	kprint_exit( void )
{
	kprintf = dummy_kprintf;

	if( DllInstance ){
		FreeLibrary( DllInstance );
		DllInstance = NULL;
	}
}

#ifdef	_UNICODE
/****************************************************************************/
/*!
 *	@brief	DLLが無いときのダミー関数 (UNICODE用).
 *
 *	@param	[in]	fmt		書式付メッセージ文字列のポインタ.
 *
 *	@retval	メッセージのバイト数.(常に0を返す)
 */
//static int	dummy_kprintf( const wchar_t *fmt, ... )
//{
//	return 0;
//}
static int	dummy_kprintf( const char *fmt, ... )
{
	return 0;
}
#else
/****************************************************************************/
/*!
 *	@brief	DLLが無いときのダミー関数 (ANSI用).
 *
 *	@param	[in]	fmt		書式付メッセージ文字列のポインタ.
 *
 *	@retval	メッセージのバイト数.(常に0を返す)
 */
static int	dummy_kprintf( const char *fmt, ... )
{
	return 0;
}
#endif

#ifdef  __cplusplus
}
#endif

/* End of file */
