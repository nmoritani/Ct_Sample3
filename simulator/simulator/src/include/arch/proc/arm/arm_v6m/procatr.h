/**
 *  Hyper Operating System V4 Advance
 *
 * @file  procatr.h
 * @brief %jp{ARMv6-M}%en{ARMv6-M}
 *
 * Copyright (C) 1998-2011 by Project HOS
 * http://sourceforge.jp/projects/hos/
 */


#ifndef _KERNEL__arch__proc__arm__arm_v6m__procatr_h__
#define _KERNEL__arch__proc__arm__arm_v6m__procatr_h__


#define _KERNEL_PROCATR_ARM_CORTEX_M3


/* %jp{�v���Z�b�T�A�[�L�e�N�`����`�̂���C���N���[�h�p�X} */
#define _KERNEL_PROCATR_INC_PATH			"arm/arm_v6m"


/* %jp{�v���Z�b�T�A�[�L�e�N�`���Ɉˑ���������} */
#define _KERNEL_PROCATR_CTX_STK				FALSE		/**< %jp{�R���e�L�X�g�����ɃX�^�b�N�̈�̎w�肪�K�v���H} */
#define _KERNEL_PROCATR_CTX_STKSZ			FALSE		/**< %jp{�R���e�L�X�g�����ɃX�^�b�N�T�C�Y�̎w�肪�K�v���H} */
#define _KERNEL_PROCATR_CTX_ISP				TRUE		/**< %jp{�R���e�L�X�g�����ɏ����X�^�b�N�|�C���^�l���K�v���H} */
#define _KERNEL_PROCATR_CTX_DEL				FALSE		/**< %jp{�ʃR���e�L�X�g����̃R���e�L�X�g�폜���K�v���H} */
#define _KERNEL_PROCATR_CTX_RST				TRUE		/**< %jp{���R���e�L�X�g�̃��X�^�[�g���\���H} */

#define _KERNEL_PROCATR_TMIN_STKSZ			(4*16)		/**< %jp{�Œ���K�v�ȃX�^�b�N�T�C�Y(byte�P��)} */
#define _KERNEL_PROCATR_DEF_SYSSTKSZ		64
#define _KERNEL_PROCATR_DEF_INTSTKSZ		256

#define _KERNEL_PROCATR_SPT_SMP				FALSE		/**< %jp{SMP�ɑΉ����Ă��邩�H} */
#define _KERNEL_PROCATR_SPT_MULTINT			TRUE		/**< %jp{���d�����݂ɑΉ����Ă��邩�H} */

#define _KERNEL_PROCATR_TMIN_INHNO			0			/**< %jp{�����݃n���h���ԍ��̍ŏ��l} */
#define _KERNEL_PROCATR_TMAX_INHNO			255			/**< %jp{�����݃n���h���ԍ��̍ő�l} */

#define _KERNEL_PROCATR_TMIN_EXCNO			0			/**< %jp{CPU��O�n���h���ԍ��̍ŏ��l} */
#define _KERNEL_PROCATR_TMAX_EXCNO			15			/**< %jp{CPU��O�n���h���ԍ��̍ő�l} */

#define _KERNEL_PROCATR_SYSSTK_NUM			1			/**< %jp{�V�X�e���X�^�b�N�͉��{�K�v���H} */

#define _KERNEL_PROCATR_SIGNED_INT			0			/**< %jp{�����t�����ƕ������������̂ǂ��炪���ӂ��H(�����t��:1, ��������:-1, ����:0)} */
#define _KERNEL_PROCATR_TBIT_INT			32			/**< %jp{�v���Z�b�T�ɍœK�Ȑ����^�̃r�b�g��} */
#define _KERNEL_PROCATR_TBIT_PTR			32			/**< %jp{�|�C���^�̃r�b�g��} */
#define _KERNEL_PROCATR_MEM_ALIGN			4			/**< %jp{�K�؂ȃ������̃A���C�����g(byte�P��)} */
#define _KERNEL_PROCATR_STK_ALIGN			8			/**< %jp{�K�؂ȃX�^�b�N�̃A���C�����g(byte�P��)} */
#define _KERNEL_PROCATR_ALLOW_UNALIGN		FALSE		/**< %jp{�A���A���C���A�N�Z�X�͉\���H} */

#define _KERNEL_PROCATR_SYS_CTX				TRUE		/**< %jp{�R���e�L�X�g��ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */
#define _KERNEL_PROCATR_SYS_LOC				FALSE		/**< %jp{CPU���b�N��ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */
#define _KERNEL_PROCATR_SYS_DSP				FALSE		/**< %jp{�f�B�X�p�b�`�֎~��ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */
#define _KERNEL_PROCATR_SYS_SYS				FALSE		/**< %jp{�V�X�e����ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */
#define _KERNEL_PROCATR_SYS_DLY				TRUE		/**< %jp{�x���f�B�X�p�b�`�ۗ���ԊǗ����v���Z�b�T�Ŏ��{���邩�H} */



#endif	/* _KERNEL__arch__proc__arm__arm_v6m__procatr_h__ */


/* end of file */
