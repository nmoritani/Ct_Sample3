/****************************************************************************
 *	Copylight(C) 2007-2011 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	kprintf.h
 *
 *	@brief	デバッグモニタ・クライアント.
 *
 *	@author	金澤 宣明
 */
#ifndef	__KPRINTF_H__
#define	__KPRINTF_H__

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef	_UNICODE
/****************************************************************************/
/*!
 *	@brief	デバッグモニタにメッセージを送る.
 *
 *	@param	[in]	fmt		書式付メッセージ文字列のポインタ.
 *
 *	@retval	メッセージのバイト数.
 */
//typedef int (*KDBMONPROC)( const wchar_t *fmt, ... );
typedef int (*KDBMONPROC)( const char *fmt, ... );

extern KDBMONPROC	kprintf;

#else

/****************************************************************************/
/*!
 *	@brief	デバッグモニタにメッセージを送る.
 *
 *	@param	[in]	fmt		書式付メッセージ文字列のポインタ.
 *
 *	@retval	メッセージのバイト数.
 */
typedef int (*KDBMONPROC)( const char *fmt, ... );

extern KDBMONPROC	kprintf;
#endif

/****************************************************************************/
/*!
 *	@brief	デバッグモニタ・クライアントを起動する.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	kprint_init( void );

/****************************************************************************/
/*!
 *	@brief	デバッグモニタ・クライアントを終了する.
 *
 *	@param	なし.
 *
 *	@retval	なし.
 */
void	kprint_exit( void );

#ifdef  __cplusplus
}
#endif

#endif	// __KPRINTF_H__
/* End of file */
