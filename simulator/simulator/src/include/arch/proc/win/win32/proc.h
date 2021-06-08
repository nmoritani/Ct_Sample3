/**
 *  Hyper Operating System V4 Advance
 *
 * @file  proc.h
 * @brief %jp{�v���Z�b�T�A�[�L�e�N�`���ŗL�@�\}%en{Processor archtecture}
 *
 * Copyright (C) 1998-2006 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__win32__proc_h__
#define _KERNEL__win32__proc_h__


/** %jp{Windows �w�b�_�t�@�C���̓ǂ݂���} */
#define SIZE	WIN_SIZE
#define BOOL	WIN_BOOL
#include <windows.h>
#include <tchar.h>
#undef	SIZE
#undef	BOOL

#include <setjmp.h>



/** %jp{�R���e�L�X�g���ۑ��u���b�N} */
typedef struct _kernel_t_ctxcb
{
	FP					entry;				/**< %jp{�G���g���[�A�h���X} */
	VP_INT				exinf1;				/**< %jp{�p�����[�^�P} */
	VP_INT				exinf2;				/**< %jp{�p�����[�^�Q} */
	jmp_buf				jmpenv;				/**< %jp{�R���e�L�X�g���Z�b�g�p��longjmp�f�[�^} */

	BOOL				blInterrupt;		/**< %jp{�����ݏ������t���O} */
	HANDLE				hEvent;				/**< %jp{�C�x���g�n���h��} */
	HANDLE				hThread;			/**< %jp{�X���b�h�n���h��} */
	DWORD				dwThreadId;			/**< %jp{�X���b�hID} */
	HANDLE				hIntEvent;			/**< %jp{�C�x���g�n���h��} */
	HANDLE				hIntThread;			/**< %jp{�X���b�h�n���h��} */
	DWORD				dwIntThreadId;		/**< %jp{�X���b�hID} */
} _KERNEL_T_CTXCB;


/** %jp{�����݃R���e�L�X�g����u���b�N} */
typedef struct _kernel_t_ictxcb
{
	_KERNEL_T_CTXCB		*runctxcb;			/**< %jp{���s���̃R���e�L�X�g} */
	INHNO				inhno;

	CRITICAL_SECTION	CriticalSection;	/**< %jp{�N���e�B�J���Z�N�V����} */
	HANDLE				hSemIntLock;		/**< %jp{�V�X�e���̔r������p�Z�}�t�H} */
	volatile BOOL		blIntCtx;			/**< %jp{�����ݏ������t���O} */
	volatile BOOL		blDisInt;			/**< %jp{�����݋֎~�t���O} */
	DWORD				dwPrimaryThreadId;	/**< %jp{�v���C�}���X���b�hID} */
} _KERNEL_T_ICTXCB;


extern _KERNEL_T_ICTXCB _kernel_ictxcb;		/**< %jp{�����݃R���e�L�X�g����u���b�N} */



#ifdef __cplusplus
extern "C" {
#endif

void    _kernel_ini_prc(void);																/**< %jp{�A�[�L�e�N�`���ŗL�̏�����} */

void    _kernel_ena_int(void);																/**< %jp{�����݋���} */
void    _kernel_dis_int(void);																/**< %jp{�����݋֎~} */
void    _kernel_wai_int(void);																/**< %jp{�����ݑ҂�(�A�C�h�����̏���)} */

void    _kernel_cre_ctx(_KERNEL_T_CTXCB *ctxcb, FP entry, VP_INT exinf1, VP_INT exinf2);	/**< %jp{���s�R���e�L�X�g�̍쐬} */
void    _kernel_del_ctx(_KERNEL_T_CTXCB *ctxcb);											/**< %jp{���s�R���e�L�X�g�̍폜} */
void    _kernel_rst_ctx(_KERNEL_T_CTXCB *ctxcb);											/**< %jp{���s�R���e�L�X�g�̃��X�^�[�g} */
void    _kernel_sta_ctx(_KERNEL_T_CTXCB *ctxcb);											/**< %jp{���s�R���e�L�X�g�̊J�n} */
void    _kernel_swi_ctx(_KERNEL_T_CTXCB *ctxcb_now, _KERNEL_T_CTXCB *ctxinf_nxt);			/**< %jp{���s�R���e�L�X�g�̐ؑ�} */

void     vsig_int(int inhno);																/**< %jp{�[�������݃T�|�[�gAPI} */

#ifdef __cplusplus
}
#endif


#define _KERNEL_INI_PRC()				_kernel_ini_prc()

#define _KERNEL_INI_INT(stksz, stk)		do {} while(0)
#define _KERNEL_ENA_INT()				_kernel_ena_int()									/**< %jp{�����݋���} */
#define _KERNEL_DIS_INT()				_kernel_dis_int()									/**< %jp{�����݋֎~} */
#define _KERNEL_WAI_INT()				_kernel_wai_int()									/**< %jp{�����ݑ҂�(�A�C�h�����̏���)} */


#define _KERNEL_CRE_CTX(ctxcb, stksz, stk, isp, entry, par1, par2)		\
							_kernel_cre_ctx(ctxcb, entry, par1, par2)
#define _KERNEL_DEL_CTX(ctxcb)	_kernel_del_ctx(ctxcb)
#define _KERNEL_RST_CTX(ctxcb, stksz, stk, isp, entry, par1, par2)		\
							_kernel_rst_ctx(ctxcb)
#define _KERNEL_STA_CTX(ctxcb)	_kernel_sta_ctx(ctxcb)
#define _KERNEL_SWI_CTX(ctxcb_now, ctxcb_nxt)							\
							_kernel_swi_ctx(ctxcb_now, ctxcb_nxt)



#endif	/* _KERNEL__win32__proc_h__ */


/* end of file */
