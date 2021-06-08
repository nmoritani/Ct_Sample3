/*!
 * \file        geman.c
 * \brief       Graphic Engine �Ǘ�
 * \date        2011/10/12 �V�K�쐬
 * \copyright   Panasonic
 * \author      Natsuko Masuda
 */
#include "asic_reg.h"
#include <kernel.h>
#include <kernel_id.h>
#include "SysIf.h"

#define PANA_ORG_FUNC
#define _DMPNATIVE_
#include "EGL/egl.h"
#include "oswrapper/os_wrapper.h"
#include "DMP/eglNative.h"

#include "ext_DrvCKGEN.h"

#include "geman.h"

extern eDRV_ERR eLdCKGEN_ChangePll(sDRV_CKGEN_PLL_SELECT *psPllSel);
extern void CPU_PurgeCache(void);


/***************************************************************
				�}�N����`
***************************************************************/

/***************************************************************
				��������
***************************************************************/

/***************************************************************
				�\����
***************************************************************/

/***************************************************************
				�v���g�^�C�v
***************************************************************/
	
/***************************************************************
				�ϐ��錾
***************************************************************/

//------------------------------------------------------------
//! Graphic Manager Task
/*!
 * \param[] 
 * \param[] 
 * \return  
 * \note    
 * @date       12.02.09 API�w�̏������^�X�N�ɈڐA
 */
void initGEman(void)
{
	// �ϐ��錾
	sDRV_CKGEN_PLL_SELECT		psSetPllSelect;		// PLL�ύX�p
	sDRV_CKGEN_FREQ				psSetFreq;			// �N���b�N���g���ύX�p
	sDRV_CKGEN_SET_CLOCK_PD 	psSetClockPd;		// �p���[�h���C������p
	sDRV_CKGEN_RESET_MODE		psSetResetMode;		// �\�t�g�E�F�A���Z�b�g�����p
	sDRV_CKGEN_RESET_MODE_PD	psSetResetModePd;	// PD�p�\�t�g�E�F�A���Z�b�g�����p
	
	// PLL1�ɕύX
	psSetPllSelect.ePllCk 		= DRV_CKG_CLOCK_AXI_D;
	psSetPllSelect.ePllValue 	= DRV_CKG_PLL1;
	eLdCKGEN_ChangePll(&psSetPllSelect);
	
	// �N���b�N���g����264MHz(PLL1�O��)�ɕύX
	psSetFreq.eFreqCk 			= DRV_CKG_FREQ_SET_AXI_D;
	psSetFreq.eFreqValue		= DRV_CKG_FREQ_264;
	eLdCKGEN_ChangeValue(&psSetFreq);
	
	// �O���t�B�b�N�G���W���̓d��ON
	psSetClockPd.eClockPd 		= DRV_CKG_CLOCK_PD27;
	psSetClockPd.eClockPdValue 	= DRV_CKG_CLOCK_START;
	eLdCKGEN_SetClockPowerDomain(&psSetClockPd);
	
	// �O���t�B�b�N�G���W���ւ̃N���b�N�����J�n
	mCKGEN_START_AXI_D_MCU_CK();					// GE���C�u�������ŃN���b�N������s���܂�(���W���[��/�T�X�y���h�@�\)
	mCKGEN_START_AHB_CPU_MCU_CK();					// ���u���b�N�Ƌ��L�����N���b�N�A�V�X�e���Ƃ��Đ��䂷�ׂ�����
	
	// �\�t�g�E�F�A���Z�b�g����
	psSetResetMode.eReset 		= DRV_CKG_SFTRST_AXI_D | DRV_CKG_SFTRST_AHB_CPU;
	psSetResetMode.eResetValue 	= DRV_CKG_RESET_DISABLE;
	eLdCKGEN_SetSoftReset(&psSetResetMode);
	
	// PD�̃\�t�g�E�F�A���Z�b�g����
	psSetResetModePd.eResetPd 		= DRV_CKG_SFTRST_PD27;
	psSetResetModePd.eResetPdValue 	= DRV_CKG_RESET_DISABLE;
	eLdCKGEN_SetSoftResetPowerDomain(&psSetResetModePd);
	

	// �O���t�B�b�N�G���W������̊��荞�݋���
	ena_int(256);
	ena_int(257);
	ena_int(258);

	// �A�v���Œ���OS���b�p�[/eglNative ���g�p����ꍇ�A�����I�ɏ��������K�v
	OsWrap_Initialize(0);
	eglNativeInitialize();
	
	// GE���C�u�����̏�������EGL�̏������ɕ����Ď��{�����
	//   ��OsWrapper�AeglNative�AdmpNative�ADMPAlloc�A�����_�����O�}�l�[�W���̏��������s����
}


// �Z�~�z�X�e�B���O�Ή�
int $Sub$$_sys_open(const char *name, int openmode)
{
	/* Dummy */
	return (0);
}

void $Sub$$_sys_exit(int retcode)
{
	/* Dummy */
}

void $Sub$$_ttywrch(int ch)
{
	/* Dummy */
}

void __assert_fail(void)
{
}


// �����A�h���X��_���A�h���X�ɕϊ�
void *GE_CnvLogicAddr(unsigned int addr)
{
	return (void *)addr;
}

// �_���A�h���X�𕨗��A�h���X�ɕϊ�
void *GE_CnvPhysicalAddr(unsigned int addr)
{
	return (void *)addr;
}

void GE_suspend(void)
{
#if 0	// Movie�ł͑��点���ςȂ����d�l�ł� 2013/12/19 moritani
    unsigned int ulPsw;                                      /* ��ԕۑ��p    */
    DRV_CMN_SPIN_LOCK(DRV_CMN_EXCLUSION_CKGEN, &ulPsw);      /* �r������J�n */
    mCKGEN_STOP_AXI_D_MCU_CK();                              /* (*((volatile unsigned long *)
																0x7C015054)) |= 0x00010000; */
    DRV_CMN_SPIN_UNLOCK(DRV_CMN_EXCLUSION_CKGEN, &ulPsw);	/* �r������I�� */
#endif
}

void GE_resume(void)
{
#if 0	// Movie�ł͑��点���ςȂ����d�l�ł� 2013/12/19 moritani
    unsigned int ulPsw;                                      /* ��ԕۑ��p    */
    DRV_CMN_SPIN_LOCK(DRV_CMN_EXCLUSION_CKGEN, &ulPsw);      /* �r������J�n */
    mCKGEN_START_AXI_D_MCU_CK ();                            /* (*((volatile unsigned long *)
																0x7C015054)) &= 0xFFFEFFFF; */
    DRV_CMN_SPIN_UNLOCK(DRV_CMN_EXCLUSION_CKGEN, &ulPsw);	/* �r������I�� */
#endif
}

void GE_Irq_gp_signal()
{
	rm_hwif_interrupt_gp_signal();
	clr_int(GEVG_INTNO_IRQ1);
}

void GE_Irq_psc_signal()
{
	rm_hwif_interrupt_psc_signal();
	clr_int(GEVG_INTNO_IRQ2);
}

void GE_Irq_ppf_signal()
{
	rm_hwif_interrupt_ppf_signal();
	clr_int(GEVG_INTNO_IRQ3);
}


// DMP��������Q�Ƃ���Ă邽�ߏ����ƃR���p�C���G���[�ɂȂ�
////////////////////////////
void utl_armcom_cachePurgeALL(void){}
void snprintf(){}
////////////////////////////
