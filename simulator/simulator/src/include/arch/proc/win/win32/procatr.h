/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �v���Z�b�T���ۉ��R���|�[�l���g (Windows�p)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef _KERNEL__arch__proc__win__win32__procatr_h__
#define _KERNEL__arch__proc__win__win32__procatr_h__


/* %jp{�v���Z�b�T�A�[�L�e�N�`����`�̂���C���N���[�h�p�X} */
#define _KERNEL_PROCATR_INC_PATH			"win/win32"


/* %jp{�v���Z�b�T�A�[�L�e�N�`���Ɉˑ���������} */
#define _KERNEL_PROCATR_CTX_STK				FALSE		/**< %jp{�R���e�L�X�g�����ɃX�^�b�N�̈�̎w�肪�K�v���H} */
#define _KERNEL_PROCATR_CTX_STKSZ			FALSE		/**< %jp{�R���e�L�X�g�����ɃX�^�b�N�T�C�Y�̎w�肪�K�v���H} */
#define _KERNEL_PROCATR_CTX_ISP				TRUE		/**< %jp{�R���e�L�X�g�����ɏ����X�^�b�N�|�C���^�l���K�v���H} */
#define _KERNEL_PROCATR_CTX_DEL				TRUE		/**< %jp{�ʃR���e�L�X�g����̃R���e�L�X�g�폜���K�v���H} */
#define _KERNEL_PROCATR_CTX_RST				FALSE		/**< %jp{���R���e�L�X�g�̃��X�^�[�g���\���H} */

#define _KERNEL_PROCATR_TMIN_STKSZ			(4*32)		/**< %jp{�Œ���K�v�ȃX�^�b�N�T�C�Y(byte�P��)} */
#define _KERNEL_PROCATR_DEF_SYSSTKSZ		64
#define _KERNEL_PROCATR_DEF_INTSTKSZ		256

#define _KERNEL_PROCATR_SPT_SMP				FALSE		/**< %jp{SMP�ɑΉ����Ă��邩�H} */
#define _KERNEL_PROCATR_SPT_MULTINT			FALSE		/**< %jp{���d�����݂ɑΉ����Ă��邩�H} */

#define _KERNEL_PROCATR_TMIN_INHNO			1			/**< %jp{�����݃n���h���ԍ��̍ŏ��l} */
#define _KERNEL_PROCATR_TMAX_INHNO			256			/**< %jp{�����݃n���h���ԍ��̍ő�l} */

#define _KERNEL_PROCATR_TMIN_EXCNO			1			/**< %jp{CPU��O�n���h���ԍ��̍ŏ��l} */
#define _KERNEL_PROCATR_TMAX_EXCNO			1			/**< %jp{CPU��O�n���h���ԍ��̍ő�l} */

#define _KERNEL_PROCATR_SYSSTK_NUM			1			/**< %jp{�V�X�e���X�^�b�N�͉��{�K�v���H} */

#define _KERNEL_PROCATR_SIGNED_INT			0			/**< %jp{�����t�����ƕ������������̂ǂ��炪���ӂ��H(�����t��:1, ��������:-1, ����:0)} */
#define _KERNEL_PROCATR_TBIT_INT			32			/**< %jp{�v���Z�b�T�ɍœK�Ȑ����^�̃r�b�g��} */
#define _KERNEL_PROCATR_TBIT_PTR			32			/**< %jp{�|�C���^�̃r�b�g��} */
#define _KERNEL_PROCATR_MEM_ALIGN			32			/**< %jp{�K�؂ȃ������̃A���C�����g(byte�P��)} */
#define _KERNEL_PROCATR_STK_ALIGN			1			/**< %jp{�K�؂ȃX�^�b�N�̃A���C�����g(byte�P��)} */
#define _KERNEL_PROCATR_ALLOW_UNALIGN		TRUE		/**< %jp{�A���A���C���A�N�Z�X�͉\���H} */

#define _KERNEL_PROCATR_SYS_CTX				FALSE		/**< %jp{�R���e�L�X�g��ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */
#define _KERNEL_PROCATR_SYS_LOC				FALSE		/**< %jp{CPU���b�N��ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */
#define _KERNEL_PROCATR_SYS_DSP				FALSE		/**< %jp{�f�B�X�p�b�`�֎~��ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */
#define _KERNEL_PROCATR_SYS_SYS				FALSE		/**< %jp{�V�X�e����ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */
#define _KERNEL_PROCATR_SYS_DLY				FALSE		/**< %jp{�x���f�B�X�p�b�`�ۗ���ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */


#endif	/* _KERNEL__arch__proc__win__win32__procatr_h__ */


/* end of file */
