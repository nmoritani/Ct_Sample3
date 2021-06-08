/*!
 * \file        geman.c
 * \brief       Graphic Engine 管理
 * \date        2011/10/12 新規作成
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
				マクロ定義
***************************************************************/

/***************************************************************
				ｅｎｕｍ
***************************************************************/

/***************************************************************
				構造体
***************************************************************/

/***************************************************************
				プロトタイプ
***************************************************************/
	
/***************************************************************
				変数宣言
***************************************************************/

//------------------------------------------------------------
//! Graphic Manager Task
/*!
 * \param[] 
 * \param[] 
 * \return  
 * \note    
 * @date       12.02.09 API層の処理をタスクに移植
 */
void initGEman(void)
{
	// 変数宣言
	sDRV_CKGEN_PLL_SELECT		psSetPllSelect;		// PLL変更用
	sDRV_CKGEN_FREQ				psSetFreq;			// クロック周波数変更用
	sDRV_CKGEN_SET_CLOCK_PD 	psSetClockPd;		// パワードメイン制御用
	sDRV_CKGEN_RESET_MODE		psSetResetMode;		// ソフトウェアリセット解除用
	sDRV_CKGEN_RESET_MODE_PD	psSetResetModePd;	// PD用ソフトウェアリセット解除用
	
	// PLL1に変更
	psSetPllSelect.ePllCk 		= DRV_CKG_CLOCK_AXI_D;
	psSetPllSelect.ePllValue 	= DRV_CKG_PLL1;
	eLdCKGEN_ChangePll(&psSetPllSelect);
	
	// クロック周波数を264MHz(PLL1前提)に変更
	psSetFreq.eFreqCk 			= DRV_CKG_FREQ_SET_AXI_D;
	psSetFreq.eFreqValue		= DRV_CKG_FREQ_264;
	eLdCKGEN_ChangeValue(&psSetFreq);
	
	// グラフィックエンジンの電源ON
	psSetClockPd.eClockPd 		= DRV_CKG_CLOCK_PD27;
	psSetClockPd.eClockPdValue 	= DRV_CKG_CLOCK_START;
	eLdCKGEN_SetClockPowerDomain(&psSetClockPd);
	
	// グラフィックエンジンへのクロック供給開始
	mCKGEN_START_AXI_D_MCU_CK();					// GEライブラリ内でクロック制御を行います(レジューム/サスペンド機能)
	mCKGEN_START_AHB_CPU_MCU_CK();					// 他ブロックと共有されるクロック、システムとして制御すべきもの
	
	// ソフトウェアリセット解除
	psSetResetMode.eReset 		= DRV_CKG_SFTRST_AXI_D | DRV_CKG_SFTRST_AHB_CPU;
	psSetResetMode.eResetValue 	= DRV_CKG_RESET_DISABLE;
	eLdCKGEN_SetSoftReset(&psSetResetMode);
	
	// PDのソフトウェアリセット解除
	psSetResetModePd.eResetPd 		= DRV_CKG_SFTRST_PD27;
	psSetResetModePd.eResetPdValue 	= DRV_CKG_RESET_DISABLE;
	eLdCKGEN_SetSoftResetPowerDomain(&psSetResetModePd);
	

	// グラフィックエンジンからの割り込み許可
	ena_int(256);
	ena_int(257);
	ena_int(258);

	// アプリで直接OSラッパー/eglNative を使用する場合、明示的に初期化が必要
	OsWrap_Initialize(0);
	eglNativeInitialize();
	
	// GEライブラリの初期化はEGLの初期化に併せて実施される
	//   ⇒OsWrapper、eglNative、dmpNative、DMPAlloc、レンダリングマネージャの初期化を行われる
}


// セミホスティング対応
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


// 物理アドレスを論理アドレスに変換
void *GE_CnvLogicAddr(unsigned int addr)
{
	return (void *)addr;
}

// 論理アドレスを物理アドレスに変換
void *GE_CnvPhysicalAddr(unsigned int addr)
{
	return (void *)addr;
}

void GE_suspend(void)
{
#if 0	// Movieでは走らせっぱなしが仕様です 2013/12/19 moritani
    unsigned int ulPsw;                                      /* 状態保存用    */
    DRV_CMN_SPIN_LOCK(DRV_CMN_EXCLUSION_CKGEN, &ulPsw);      /* 排他制御開始 */
    mCKGEN_STOP_AXI_D_MCU_CK();                              /* (*((volatile unsigned long *)
																0x7C015054)) |= 0x00010000; */
    DRV_CMN_SPIN_UNLOCK(DRV_CMN_EXCLUSION_CKGEN, &ulPsw);	/* 排他制御終了 */
#endif
}

void GE_resume(void)
{
#if 0	// Movieでは走らせっぱなしが仕様です 2013/12/19 moritani
    unsigned int ulPsw;                                      /* 状態保存用    */
    DRV_CMN_SPIN_LOCK(DRV_CMN_EXCLUSION_CKGEN, &ulPsw);      /* 排他制御開始 */
    mCKGEN_START_AXI_D_MCU_CK ();                            /* (*((volatile unsigned long *)
																0x7C015054)) &= 0xFFFEFFFF; */
    DRV_CMN_SPIN_UNLOCK(DRV_CMN_EXCLUSION_CKGEN, &ulPsw);	/* 排他制御終了 */
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


// DMP内部から参照されてるため消すとコンパイルエラーになる
////////////////////////////
void utl_armcom_cachePurgeALL(void){}
void snprintf(){}
////////////////////////////
