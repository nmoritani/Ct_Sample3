/****************************************************************************
 *	Copylight(C) 2007-2011 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	kprintf.h
 *
 *	@brief	�f�o�b�O���j�^�E�N���C�A���g.
 *
 *	@author	���V �閾
 */
#ifndef	__KPRINTF_H__
#define	__KPRINTF_H__

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef	_UNICODE
/****************************************************************************/
/*!
 *	@brief	�f�o�b�O���j�^�Ƀ��b�Z�[�W�𑗂�.
 *
 *	@param	[in]	fmt		�����t���b�Z�[�W������̃|�C���^.
 *
 *	@retval	���b�Z�[�W�̃o�C�g��.
 */
//typedef int (*KDBMONPROC)( const wchar_t *fmt, ... );
typedef int (*KDBMONPROC)( const char *fmt, ... );

extern KDBMONPROC	kprintf;

#else

/****************************************************************************/
/*!
 *	@brief	�f�o�b�O���j�^�Ƀ��b�Z�[�W�𑗂�.
 *
 *	@param	[in]	fmt		�����t���b�Z�[�W������̃|�C���^.
 *
 *	@retval	���b�Z�[�W�̃o�C�g��.
 */
typedef int (*KDBMONPROC)( const char *fmt, ... );

extern KDBMONPROC	kprintf;
#endif

/****************************************************************************/
/*!
 *	@brief	�f�o�b�O���j�^�E�N���C�A���g���N������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	kprint_init( void );

/****************************************************************************/
/*!
 *	@brief	�f�o�b�O���j�^�E�N���C�A���g���I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	kprint_exit( void );

#ifdef  __cplusplus
}
#endif

#endif	// __KPRINTF_H__
/* End of file */
