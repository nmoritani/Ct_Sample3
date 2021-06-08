/****************************************************************************
 *	Copylight(C) 2007-2011 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	kprintf.c
 *
 *	@brief	�f�o�b�O���j�^�E�N���C�A���g�̌��J�֐�.
 *
 *	@author	���V �閾
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

static HINSTANCE	DllInstance = NULL;			//!< DLL�̃C���X�^���X�E�n���h��.
KDBMONPROC			kprintf = dummy_kprintf;

/****************************************************************************/
/*!
 *	@brief	�f�o�b�O���j�^�E�N���C�A���g���N������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
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
 *	@brief	�f�o�b�O���j�^�E�N���C�A���g���I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
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
 *	@brief	DLL�������Ƃ��̃_�~�[�֐� (UNICODE�p).
 *
 *	@param	[in]	fmt		�����t���b�Z�[�W������̃|�C���^.
 *
 *	@retval	���b�Z�[�W�̃o�C�g��.(���0��Ԃ�)
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
 *	@brief	DLL�������Ƃ��̃_�~�[�֐� (ANSI�p).
 *
 *	@param	[in]	fmt		�����t���b�Z�[�W������̃|�C���^.
 *
 *	@retval	���b�Z�[�W�̃o�C�g��.(���0��Ԃ�)
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
