/*************************************************************************/
/**
 * @file      gemng_api.h
 * @brief     GEMNG �����w�b�_
 * @date      2011/10/12 �V�K�쐬
 * @copyright Panasonic Co.,Ltd.
 * @author    ���c
 *************************************************************************/
#ifndef __GEMNG_LOCAL_H__
#define __GEMNG_LOCAL_H__

/***************************************************************
                    �C���N���[�h�t�@�C��
***************************************************************/
#define _DMPNATIVE_

//#include <common.h>
#include "geman.h"
#include "ext_DrvCKGEN.h"
#include "EGL/egl.h"
#include "dmpallocator/dmp_allocator.h"
#include "oswrapper/os_wrapper.h"
#include "DMP/eglNative.h"
/***************************************************************
                        �}�N����`
***************************************************************/
#define UNUSED_VARIABLE(x)\
{\
	void *a;\
	a = (void*)x;\
}\

extern eDRV_ERR eLdCKGEN_ChangePll(sDRV_CKGEN_PLL_SELECT *psPllSel);


/* GE�N���b�N���� */
#define	GE_CLOCK_START()	do {mCKGEN_START_GEVG1_CK(); mCKGEN_START_GEVG2_CK();} while(0)
#define	GE_CLOCK_STOP()		do {mCKGEN_STOP_GEVG1_CK(); mCKGEN_STOP_GEVG2_CK();} while(0)

/* GE���Z�b�g���� */
#define mRST_GE_ENABLE()	(unCKG_SFTRST2_ASM &= 0xfffb)
#define mRST_GE_DISABLE()	(unCKG_SFTRST2_ASM |= 0x0004)
#define GE_SFTRST_DISABLE()	do {mRST_GE_DISABLE();} while(0)
#define GE_SFTRST_ENABLE()	do {mRST_GE_ENABLE(); } while(0)

/* GE�̃}�b�v�擪�A�h���X ���l:[ge_ml 680] */
#if KCSPEC_ASIC_TYPE == _VENUS7_FHD_
#define GV_MMREG_BASE	(0x9c00f000)
#elif KCSPEC_ASIC_TYPE == _VENUS7_HD2_
#define GV_MMREG_BASE	(0x9c00e000)
#elif KCSPEC_ASIC_TYPE == _VENUS8_FHD_
#define GV_MMREG_BASE	(0x9c00f000)
#elif KCSPEC_ASIC_TYPE == _VENUS9_AHD_
#define GV_MMREG_BASE	(0x7c168000)
#else
#error "UNKNOWN ASIC"
#endif

/***************************************************************
                        �^��`
***************************************************************/
/***************************************************************
                        �\����
***************************************************************/

/***************************************************************
                        �v���g�^�C�v�錾
***************************************************************/


#endif /* __GEMNG_LOCAL_H__ */
