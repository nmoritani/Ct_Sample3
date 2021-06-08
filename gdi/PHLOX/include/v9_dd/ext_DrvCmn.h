/********************************************************************************/
/*!
 * @file	ext_DrvCmn.h
 *
 * @brief	ドライバ共通 外部公開ヘッダ
 *
 * @author	パナソニック（株）
 *
 * @date	2007/11/12	新規作成
 *
 * Copyright(c) Panasonic Co.,Ltd.		http://panasonic.jp/
 * <HR>
 ********************************************************************************/
#ifndef __EXT_DRV_CMN_H__
#define __EXT_DRV_CMN_H__

/*********************************************************************************
	インクルードファイル
*********************************************************************************/
#if 0
/* SC社使用時及びリリース時は1を設定、AVC社様にて値を0に変更して使用する */
#include 	<stdio.h>
#include 	<string.h>
#include 	<stdarg.h>
#endif

#include	"ext_DrvDef.h"

/*********************************************************************************
	マクロ定義
*********************************************************************************/


/*********************************************************************************
	ユーザー定義領域　開始
*********************************************************************************/

/*------------------------------------------------------------------------------*/
/*!
 * @def		unDRV_CMN_LOCK_REG
 * @brief	LOCK_REGアクセス用
 *			ドライバ初期値を0xXXXXXXXXに設定します。
 */
/* -----------------------------------------------------------------------------*/
#define		unDRV_CMN_LOCK_REG	0x93E0001F

/*------------------------------------------------------------------------------*/
/*!
 * @def		unDRV_CMN_SRAM_ADDR
 * @brief	SRAMアドレス
 *			ドライバ初期値は0xXXXXXXXXに設定します。
 */
/* -----------------------------------------------------------------------------*/
#define		DRV_CMN_SRAM_ADDR	0x93F01F80

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_MMU_MODE_ON
 * @brief	MMU ON/OFF
 *			MMU ONなら1、OFFなら0に設定
 */
/* -----------------------------------------------------------------------------*/
#define DRV_CMN_MMU_MODE_ON	1


/*********************************************************************************
	ユーザー定義領域　終了
*********************************************************************************/

/*------------------------------------------------------------------------------*/
/*!
 * @def		unDRV_CMN_SRAM_ADDR
 * @brief	SSCのSRAMアドレス
 */
/* -----------------------------------------------------------------------------*/
#define		unDRV_CMN_SRAM_CPU_DMAC0_ASM	(DRV_CMN_SRAM_ADDR)											/* CPU DMAC0	*/
#define		unDRV_CMN_SRAM_CPU_DMAC1_ASM	(unDRV_CMN_SRAM_CPU_DMAC0_ASM + DRV_RESOURCE_CH_CPU_DMAC0)	/* CPU DMAC1	*/
#define		unDRV_CMN_SRAM_STU_DMAC_ASM		(unDRV_CMN_SRAM_CPU_DMAC1_ASM + DRV_RESOURCE_CH_CPU_DMAC1)	/* STU DMAC		*/
#define		unDRV_CMN_SRAM_MEMIO_ASM		(unDRV_CMN_SRAM_STU_DMAC_ASM + DRV_RESOURCE_CH_STU_DMAC)	/* MEMIO		*/
#define		unDRV_CMN_SRAM_TIMER32_ASM		(unDRV_CMN_SRAM_MEMIO_ASM + DRV_RESOURCE_CH_MEMIO)			/* TIMER32		*/
#define		unDRV_CMN_SRAM_ARM_TIMER_ASM	(unDRV_CMN_SRAM_TIMER32_ASM + DRV_RESOURCE_CH_TIMER32)		/* ARM TIMER	*/
#define		unDRV_CMN_SRAM_SSP_ASM			(unDRV_CMN_SRAM_ARM_TIMER_ASM + DRV_RESOURCE_CH_ARM_TIMER)	/* SSP			*/
#define		unDRV_CMN_SRAM_UART_ASM			(unDRV_CMN_SRAM_SSP_ASM + DRV_RESOURCE_CH_SSP)				/* UART			*/
#define		unDRV_CMN_SRAM_I2C_ASM			(unDRV_CMN_SRAM_UART_ASM + DRV_RESOURCE_CH_UART)			/* I2C			*/
#define		unDRV_CMN_SRAM_AD0_ASM			(unDRV_CMN_SRAM_I2C_ASM + DRV_RESOURCE_CH_I2C)				/* AD0			*/
#define		unDRV_CMN_SRAM_AD1_ASM			(unDRV_CMN_SRAM_AD0_ASM + DRV_RESOURCE_CH_AD0)				/* AD1			*/
#define		unDRV_CMN_SRAM_AD2_ASM			(unDRV_CMN_SRAM_AD1_ASM + DRV_RESOURCE_CH_AD1)				/* AD2			*/
#define		unDRV_CMN_SRAM_CDU_ASM			(unDRV_CMN_SRAM_AD2_ASM + DRV_RESOURCE_CH_AD2)				/* CDU			*/
#define		unDRV_CMN_SRAM_PIC1_ASM			(unDRV_CMN_SRAM_CDU_ASM + DRV_RESOURCE_CH_CDU)				/* PIC1			*/
#define		unDRV_CMN_SRAM_PIC2_ASM			(unDRV_CMN_SRAM_PIC1_ASM + DRV_RESOURCE_CH_PIC1)			/* PIC2			*/
#define		unDRV_CMN_SRAM_OSD1_ASM			(unDRV_CMN_SRAM_PIC2_ASM + DRV_RESOURCE_CH_PIC2)			/* OSD1			*/
#define		unDRV_CMN_SRAM_OSD2_ASM			(unDRV_CMN_SRAM_OSD1_ASM + DRV_RESOURCE_CH_OSD1)			/* OSD2			*/
#define		unDRV_CMN_SRAM_OSD3_ASM			(unDRV_CMN_SRAM_OSD2_ASM + DRV_RESOURCE_CH_OSD2)			/* OSD3			*/
#define		unDRV_CMN_SRAM_GFX_ASM			(unDRV_CMN_SRAM_OSD3_ASM + DRV_RESOURCE_CH_OSD3)			/* GFX			*/
#define		unDRV_CMN_SRAM_ADU_ASM			(unDRV_CMN_SRAM_GFX_ASM + DRV_RESOURCE_CH_GFX)				/* ADU			*/
#define		unDRV_CMN_SRAM_TCC_ASM			(unDRV_CMN_SRAM_ADU_ASM + DRV_RESOURCE_CH_ADU)				/* TCC			*/
#define		unDRV_CMN_SRAM_GENERAL_ASM		(unDRV_CMN_SRAM_TCC_ASM + DRV_RESOURCE_CH_TCC)				/* General		*/
#define		unDRV_CMN_SRAM_END				(unDRV_CMN_SRAM_GENERAL_ASM + DRV_RESOURCE_CH_GENERAL)		/* End Address	*/

/*------------------------------------------------------------------------------*/
/*!
 * @def		 CPU間排他制御時のコヒーレンシ保持用
 * @brief	 グローバル変数およびstatic変数の前後にオフセットを挿入
 */
/*------------------------------------------------------------------------------*/
#define		DUMMY_DATA_SIZE		64


/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_ENABLE_IRQ_VALID
 * @brief	ドライバ内での割り込み禁止／許可の有効無効の切り替えスイッチ
 */
/* -----------------------------------------------------------------------------*/
#define		DRV_ENABLE_IRQ_VALID


/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_ENTER_CRITICAL
 * @brief	クリティカルセクション開始
 * @param	
 */
/*------------------------------------------------------------------------------*/
#define DRV_CMN_ENTER_CRITICAL

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_EXIT_CRITICAL
 * @brief	クリティカルセクション終了
 * @param	
 */
/*------------------------------------------------------------------------------*/
#define DRV_CMN_EXIT_CRITICAL

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_CMN_AGENT_SOCKET
 * @brief	Agent socket指定パラメータ
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_CMN_AGENT_SOCKET_PPM			= 0x10100000,	//!< PPMW0、PPMW1、PPMWBMW、PPMWBMR、PPMBR、PPMXRのTLB初期化
	DRV_CMN_AGENT_SOCKET_PPM_DW			= 0x10100002,	//!< PPMDW0、PPMDW1のTLB初期化
	DRV_CMN_AGENT_SOCKET_PPM_BMW		= 0x10100004,	//!< PPMBMWのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMR_FG		= 0x100A0009,	//!< YCMR0 FGのTLB初期化	"A"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_YCMR_BG		= 0x100B0009,	//!< YCMR0 BGのTLB初期化	"B"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_YCMR_ALL		= 0x10100009,	//!< YCMR0のTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMR_FG_1		= 0x100A000A,	//!< YCMR1 FGのTLB初期化	"A"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_YCMR_BG_1		= 0x100B000A,	//!< YCMR1 BGのTLB初期化	"B"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_YCMR_ALL_1		= 0x1010000A,	//!< YCMR1のTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMR_FG_2		= 0x1000000B,	//!< YCMR2 FGのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMR_BG_2		= 0x1001000B,	//!< YCMR2 BGのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMR_ALL_2		= 0x1010000B,	//!< YCMR2のTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMR_FG_3		= 0x1000000C,	//!< YCMR3 FGのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMR_BG_3		= 0x1001000C,	//!< YCMR3 BGのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMR_ALL_3		= 0x1010000C,	//!< YCMR3のTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMW_FG		= 0x100A000D,	//!< YCMW0 FGのTLB初期化	"A"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_YCMW_BG		= 0x100B000D,	//!< YCMW0 FGのTLB初期化	"B"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_YCMW_ALL		= 0x1010000D,	//!< YCMW0のTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMW_FG_1		= 0x100A000E,	//!< YCMW1 FGのTLB初期化	"A"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_YCMW_BG_1		= 0x100B000E,	//!< YCMW1 BGのTLB初期化	"B"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_YCMW_ALL_1		= 0x1010000E,	//!< YCMW1のTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMW_FG_2		= 0x1000000F,	//!< YCMW2 FGのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMW_BG_2		= 0x1001000F,	//!< YCMW2 BGのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMW_ALL_2		= 0x1010000F,	//!< YCMW2のTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMW_FG_3		= 0x10000010,	//!< YCMW3 FGのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMW_BG_3		= 0x10010010,	//!< YCMW3 BGのTLB初期化
	DRV_CMN_AGENT_SOCKET_YCMW_ALL_3		= 0x10100010,	//!< YCMW3のTLB初期化
	DRV_CMN_AGENT_SOCKET_MONL			= 0x10100011,	//!< MONL0、MONL1のTLB初期化
	DRV_CMN_AGENT_SOCKET_MONT0			= 0x10100013,	//!< MONT0のTLB初期化
	DRV_CMN_AGENT_SOCKET_MONT1			= 0x10100014,	//!< MONT1のTLB初期化
	DRV_CMN_AGENT_SOCKET_MONM_PRO		= 0x10100015,	//!< MONT2のTLB初期化
	DRV_CMN_AGENT_SOCKET_MON			= 0x100A0013,	//!< MONL0、MONT0、MONL1、MONT1、MONT2のTLB初期化	"A"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_MONW			= 0x10100016,	//!< MONWのTLB初期化
	DRV_CMN_AGENT_SOCKET_TCCR_STREAM	= 0x10000017,	//!< TCCR STREAM-ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_TCCR_Y			= 0x10010017,	//!< TCCR Y-ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_TCCR_C			= 0x10020017,	//!< TCCR C-ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_TCCW_STREAM	= 0x10000018,	//!< TCCW STREAM-ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_TCCW_Y			= 0x10010018,	//!< TCCW Y-ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_TCCW_C			= 0x10020018,	//!< TCCW C-ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR0			= 0x10100019,	//!< FRMR0のTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR1			= 0x1010001A,	//!< FRMR1のTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR2_TNR_PREY	= 0x1000001B,	//!< FRMR2 TNR用Pre画YのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR2_TNR_PREC	= 0x1001001B,	//!< FRMR2 TNR用Pre画CのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR3			= 0x1010001C,	//!< FRMR3のTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR4_HDR_PREY	= 0x1000001D,	//!< FRMR4 HDR用Pre画YのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR4_HDR_PREC	= 0x1001001D,	//!< FRMR4 HDR用Pre画CのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR5			= 0x1010001E,	//!< FRMR5のTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR6			= 0x1010001F,	//!< FRMR6のTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMR7			= 0x20100000,	//!< FRMR7のTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMW0_TNR_Y	= 0x20000001,	//!< FRMW0 TNR主力画YのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMW0_TNR_C	= 0x20010001,	//!< FRMW0 TNR主力画CのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMW1			= 0x20100002,	//!< FRMW1のTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMW2_Y		= 0x20000003,	//!< FRMW2 FUR主力1画YのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMW2_C		= 0x20010003,	//!< FRMW2 FRU主力1画CのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMW3_Y		= 0x20000004,	//!< FRMW3 FRU主力2画YのTLB初期化
	DRV_CMN_AGENT_SOCKET_FRMW3_C		= 0x20010004,	//!< FRMW3 FRU主力2画CのTLB初期化
	DRV_CMN_AGENT_SOCKET_JPM			= 0x20100005,	//!< CODER0、CODER1、CODEW、IMGCR0、IMGYR0、IMGCW0、IMGYW0のTLB初期化
	DRV_CMN_AGENT_SOCKET_BACD			= 0x20100008,	//!< BACDR、BACDWのTLB初期化
	DRV_CMN_AGENT_SOCKET_JPM_1			= 0x2010000E,	//!< CODER0_1、CODER1_1、CODEW_1、IMGCR1、IMGYR1、IMGCW1、IMGYW1のTLB初期化
	DRV_CMN_AGENT_SOCKET_BACD_1			= 0x20100011,	//!< BACDR、BACDWのTLB初期化
	DRV_CMN_AGENT_SOCKET_SYCUR0			= 0x20100017,	//!< SUBYCU 0 readのTLB初期化
	DRV_CMN_AGENT_SOCKET_SYCUR1			= 0x20100018,	//!< SUBYCU 1 readのTLB初期化
	DRV_CMN_AGENT_SOCKET_SYCUW0			= 0x20100019,	//!< SUBYCU 0 write のTLB初期化
	DRV_CMN_AGENT_SOCKET_SYCUW1			= 0x2010001A,	//!< SUBYCU 1 write のTLB初期化
	DRV_CMN_AGENT_SOCKET_SYCU_ALL		= 0x200A0017,	//!< SUBYCUのTLB初期化	"A"は識別用マジックナンバ
	DRV_CMN_AGENT_SOCKET_SDC			= 0x2010001B,	//!< SDC0のTLB初期化
	DRV_CMN_AGENT_SOCKET_SDC_1			= 0x2010001D,	//!< SDC1のTLB初期化
	DRV_CMN_AGENT_SOCKET_SDC_2			= 0x2010001F,	//!< SDC2のTLB初期化
	DRV_CMN_AGENT_SOCKET_SDC_3			= 0x30100001,	//!< SDC3のTLB初期化
	DRV_CMN_AGENT_SOCKET_USBR			= 0x30100003,	//!< USB ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_USBW			= 0x30100004,	//!< USB WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_MEMIOR			= 0x30100005,	//!< MEMIO ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_MEMIOW			= 0x30100006,	//!< MEMIO WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_ETHR			= 0x30100007,	//!< ETH ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_ETHW			= 0x30100008,	//!< ETH WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_ODUR			= 0x30100009,	//!< ODU ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_ODUW			= 0x3010000A,	//!< ODU WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_AVMDR			= 0x3010000B,	//!< AVMD ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_AVMDW			= 0x3010000C,	//!< AVMD WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_GEVGR			= 0x3010000D,	//!< GEVG ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_GEVGW			= 0x3010000E,	//!< GEVG WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_ADUR_MON		= 0x30000010,	//!< ADUモニタ再生用データReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_ADUR_HDMI		= 0x30010010,	//!< ADUHDMI再生用データReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_ADUR_CLIP		= 0x30020010,	//!< ADUクリップ音再生用データReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_ADUW			= 0x30100011,	//!< ADU WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_APU0			= 0x30100012,	//!< APU0のTLB初期化
	DRV_CMN_AGENT_SOCKET_APU1			= 0x30100013,	//!< APU1のTLB初期化
	DRV_CMN_AGENT_SOCKET_ARMR			= 0x30100014,	//!< ARM_ACE ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_ARMW			= 0x30100015,	//!< ARM_ACE WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_DMA0R			= 0x30100016,	//!< ARM_DMAC 0 ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_DMA0W			= 0x30100017,	//!< ARM_DMAC 0 WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_DMA1R			= 0x30100018,	//!< ARM_DMAC 1 ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_DMA1W			= 0x30100019,	//!< ARM_DMAC 1 WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_STDMAR			= 0x3010001A,	//!< STU_DMAC ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_STDMAW			= 0x3010001B,	//!< STU_DMAC WriteのTLB初期化
	DRV_CMN_AGENT_SOCKET_JPR			= 0x3010001C,	//!< JPU ReadのTLB初期化
	DRV_CMN_AGENT_SOCKET_JPW			= 0x3010001D	//!< JPU WriteのTLB初期化

} eDRV_CMN_AGENT_SOCKET;

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_AGENT_DRAM_CHANGE_***
 * @brief	DRAM切り替え用定義 (DRV_CMN_CHANGE_AGENT_DRAMで使用)
 */
/* -----------------------------------------------------------------------------*/
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMW0			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMW1			0x00000002
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMDW0		0x00000004
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMDW1		0x00000008
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMBMW		0x00000010
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMWBMW		0x00000020
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMWBMR		0x00000040
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMBR			0x00000080
#define DRV_CMN_AGENT_DRAM_CHANGE_PPMXR			0x00000100

#define DRV_CMN_AGENT_DRAM_CHANGE_YCUAR			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_YCUBR			0x00000002
#define DRV_CMN_AGENT_DRAM_CHANGE_YCUCR			0x00000004
#define DRV_CMN_AGENT_DRAM_CHANGE_YCUDR			0x00000008
#define DRV_CMN_AGENT_DRAM_CHANGE_YCUAW			0x00000010
#define DRV_CMN_AGENT_DRAM_CHANGE_YCUBW			0x00000020
#define DRV_CMN_AGENT_DRAM_CHANGE_YCUCW			0x00000040
#define DRV_CMN_AGENT_DRAM_CHANGE_YCUDW			0x00000080

#define DRV_CMN_AGENT_DRAM_CHANGE_MONL0			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_MONL1			0x00000002
#define DRV_CMN_AGENT_DRAM_CHANGE_MONT0			0x00000004
#define DRV_CMN_AGENT_DRAM_CHANGE_MONT1			0x00000008
#define DRV_CMN_AGENT_DRAM_CHANGE_MONT2			0x00000010
#define DRV_CMN_AGENT_DRAM_CHANGE_MONW			0x00000020

#define DRV_CMN_AGENT_DRAM_CHANGE_TCCR			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_TCCW			0x00000002

#define DRV_CMN_AGENT_DRAM_CHANGE_FRMR0			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMR1			0x00000002
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMR2			0x00000004
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMR3			0x00000008
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMR4			0x00000010
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMR5			0x00000020
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMR6			0x00000040
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMR7			0x00000080
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMW0			0x00000100
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMW1			0x00000200
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMW2			0x00000400
#define DRV_CMN_AGENT_DRAM_CHANGE_FRMW3			0x00000800

#define DRV_CMN_AGENT_DRAM_CHANGE_CODER0_0		0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_CODER1_0		0x00000002
#define DRV_CMN_AGENT_DRAM_CHANGE_CODEW_0		0x00000004
#define DRV_CMN_AGENT_DRAM_CHANGE_BACDR0		0x00000008
#define DRV_CMN_AGENT_DRAM_CHANGE_BACDW0		0x00000010
#define DRV_CMN_AGENT_DRAM_CHANGE_IMGCR0		0x00000020
#define DRV_CMN_AGENT_DRAM_CHANGE_IMGYR0		0x00000040
#define DRV_CMN_AGENT_DRAM_CHANGE_IMGCW0		0x00000080
#define DRV_CMN_AGENT_DRAM_CHANGE_IMGYW0		0x00000100
#define DRV_CMN_AGENT_DRAM_CHANGE_CODER0_1		0x00000200
#define DRV_CMN_AGENT_DRAM_CHANGE_CODER1_1		0x00000400
#define DRV_CMN_AGENT_DRAM_CHANGE_CODEW_1		0x00000800
#define DRV_CMN_AGENT_DRAM_CHANGE_BACDR1		0x00001000
#define DRV_CMN_AGENT_DRAM_CHANGE_BACDW1		0x00002000
#define DRV_CMN_AGENT_DRAM_CHANGE_IMGCR1		0x00004000
#define DRV_CMN_AGENT_DRAM_CHANGE_IMGYR1		0x00008000
#define DRV_CMN_AGENT_DRAM_CHANGE_IMGCW1		0x00010000
#define DRV_CMN_AGENT_DRAM_CHANGE_IMGYW1		0x00020000

#define DRV_CMN_AGENT_DRAM_CHANGE_SYCUR0		0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_SYCUR1		0x00000002
#define DRV_CMN_AGENT_DRAM_CHANGE_SYCUW0		0x00000004
#define DRV_CMN_AGENT_DRAM_CHANGE_SYCUW1		0x00000008

#define DRV_CMN_AGENT_DRAM_CHANGE_SDC0R			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_SDC0W			0x00000002
#define DRV_CMN_AGENT_DRAM_CHANGE_SDC1R			0x00000004
#define DRV_CMN_AGENT_DRAM_CHANGE_SDC1W			0x00000008
#define DRV_CMN_AGENT_DRAM_CHANGE_SDC2R			0x00000010
#define DRV_CMN_AGENT_DRAM_CHANGE_SDC2W			0x00000020
#define DRV_CMN_AGENT_DRAM_CHANGE_SDC3R			0x00000040
#define DRV_CMN_AGENT_DRAM_CHANGE_SDC3W			0x00000080
#define DRV_CMN_AGENT_DRAM_CHANGE_USBR			0x00000100
#define DRV_CMN_AGENT_DRAM_CHANGE_USBW			0x00000200
#define DRV_CMN_AGENT_DRAM_CHANGE_MEMIOR		0x00000400
#define DRV_CMN_AGENT_DRAM_CHANGE_MEMIOW		0x00000800
#define DRV_CMN_AGENT_DRAM_CHANGE_ETHR			0x00001000
#define DRV_CMN_AGENT_DRAM_CHANGE_ETHW			0x00002000

#define DRV_CMN_AGENT_DRAM_CHANGE_ODUR			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_ODUW			0x00000002

#define DRV_CMN_AGENT_DRAM_CHANGE_AVMDR			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_AVMDW			0x00000002

#define DRV_CMN_AGENT_DRAM_CHANGE_GEVGR			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_GEVGW			0x00000002

#define DRV_CMN_AGENT_DRAM_CHANGE_HOST			0x00000001

#define DRV_CMN_AGENT_DRAM_CHANGE_ADR			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_ADW			0x00000002

#define DRV_CMN_AGENT_DRAM_CHANGE_APM0			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_APM1			0x00000002

#define DRV_CMN_AGENT_DRAM_CHANGE_ARMR			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_ARMW			0x00000002

#define DRV_CMN_AGENT_DRAM_CHANGE_DMA0R			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_DMA0W			0x00000002
#define DRV_CMN_AGENT_DRAM_CHANGE_DMA1R			0x00000004
#define DRV_CMN_AGENT_DRAM_CHANGE_DMA1W			0x00000008
#define DRV_CMN_AGENT_DRAM_CHANGE_STDMAR		0x00000010
#define DRV_CMN_AGENT_DRAM_CHANGE_STDMAW		0x00000020

#define DRV_CMN_AGENT_DRAM_CHANGE_JPR			0x00000001
#define DRV_CMN_AGENT_DRAM_CHANGE_JPW			0x00000002


/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_CMN_AGENT_GROUP
 * @brief	Agentグループ選択
 */
/* -----------------------------------------------------------------------------*/
typedef	enum {
	DRV_CMN_AGENT_GROUP_PPU		= 0,
	DRV_CMN_AGENT_GROUP_YCU,
	DRV_CMN_AGENT_GROUP_VOU,
	DRV_CMN_AGENT_GROUP_TCC,
	DRV_CMN_AGENT_GROUP_FRM,
	DRV_CMN_AGENT_GROUP_CDU,
	DRV_CMN_AGENT_GROUP_SYCU,
	DRV_CMN_AGENT_GROUP_STU,
	DRV_CMN_AGENT_GROUP_ODU,
	DRV_CMN_AGENT_GROUP_AVMDU,
	DRV_CMN_AGENT_GROUP_GEVG,
	DRV_CMN_AGENT_GROUP_HOST,
	DRV_CMN_AGENT_GROUP_ADU,
	DRV_CMN_AGENT_GROUP_APU,
	DRV_CMN_AGENT_GROUP_ARM,
	DRV_CMN_AGENT_GROUP_DMAC,
	DRV_CMN_AGENT_GROUP_JPU
} eDRV_CMN_AGENT_GROUP;

/*------------------------------------------------------------------------------*/
/*!
 * @defgroup 	DRV_CHK_ERR		ドライバエラー処理スイッチ(cond.mk内)
 * @{
 */
/* -----------------------------------------------------------------------------*/
#ifdef	DRV_ENABLE_CHK_ERR
#define	DRV_CMN_ENABLE_CHK_ERR		ON		//!< CMNブロックエラー処理
#define	DRV_ADC_ENABLE_CHK_ERR		ON		//!< ADCブロックエラー処理
#define	DRV_ADU_ENABLE_CHK_ERR		ON		//!< ADUブロックエラー処理
#define	DRV_CDU_ENABLE_CHK_ERR		ON		//!< CDUブロックエラー処理
#define	DRV_CKGEN_ENABLE_CHK_ERR	ON		//!< CKGENブロックエラー処理
#define	DRV_CPUTOP_ENABLE_CHK_ERR	ON		//!< CPUTOPブロックエラー処理
#define	DRV_DAC_ENABLE_CHK_ERR		ON		//!< DACブロックエラー処理
#define	DRV_DIS_ENABLE_CHK_ERR		ON		//!< DISブロックエラー処理
#define	DRV_DTC_ENABLE_CHK_ERR		ON		//!< DTCブロックエラー処理
#define	DRV_EBC_ENABLE_CHK_ERR		ON		//!< EBCブロックエラー処理
#define	DRV_ENC_ENABLE_CHK_ERR		ON		//!< ENCブロックエラー処理
#define	DRV_EXTDMA_ENABLE_CHK_ERR	ON		//!< EXTDMAブロックエラー処理
#define	DRV_GDC_ENABLE_CHK_ERR		ON		//!< GDCブロックエラー処理
#define	DRV_GPIOU_ENABLE_CHK_ERR	ON		//!< GPIOUブロックエラー処理
#define	DRV_HSF_ENABLE_CHK_ERR		ON		//!< HSFブロックエラー処理
#define	DRV_HSZ_ENABLE_CHK_ERR		ON		//!< HSZブロックエラー処理
#define	DRV_HIST_ENABLE_CHK_ERR		ON		//!< HISTブロックエラー処理
#define	DRV_IRS_ENABLE_CHK_ERR		ON		//!< IRSブロックエラー処理
#define	DRV_LIN_ENABLE_CHK_ERR		ON		//!< LINブロックエラー処理
#define	DRV_LCDIF_ENABLE_CHK_ERR	ON		//!< LCDIFブロックエラー処理
#define	DRV_MEIFU_ENABLE_CHK_ERR	ON		//!< MEIFUブロックエラー処理
#define	DRV_MEMIO_ENABLE_CHK_ERR	ON		//!< MEMIOブロックエラー処理
#define	DRV_MMU_ENABLE_CHK_ERR		ON		//!< MMUブロックエラー処理
#define	DRV_MONM_ENABLE_CHK_ERR		ON		//!< MONMブロックエラー処理
#define	DRV_MTX_ENABLE_CHK_ERR		ON		//!< MTXブロックエラー処理
#define	DRV_OIS_ENABLE_CHK_ERR		ON		//!< OISブロックエラー処理
#define	DRV_PID_ENABLE_CHK_ERR		ON		//!< PIDブロックエラー処理
#define	DRV_PPU_ENABLE_CHK_ERR		ON		//!< PPUブロックエラー処理
#define	DRV_SERIAL_ENABLE_CHK_ERR	ON		//!< SERIALブロックエラー処理
#define	DRV_SSG_ENABLE_CHK_ERR		ON		//!< SSGブロックエラー処理
#define	DRV_TIMER_ENABLE_CHK_ERR	ON		//!< TIMERブロックエラー処理
#define	DRV_USBIFU_ENABLE_CHK_ERR	ON		//!< USBIFUブロックエラー処理
#define	DRV_XMC_ENABLE_CHK_ERR		ON		//!< XMCブロックエラー処理
#define	DRV_YCU_ENABLE_CHK_ERR		ON		//!< YCUブロックエラー処理
#define	DRV_NRU_ENABLE_CHK_ERR		ON		//!< NRUブロックエラー処理
#else
#define	DRV_CMN_ENABLE_CHK_ERR		OFF		//!< CMNブロックエラー処理
#define	DRV_ADC_ENABLE_CHK_ERR		OFF		//!< ADCブロックエラー処理
#define	DRV_ADU_ENABLE_CHK_ERR		OFF		//!< ADUブロックエラー処理
#define	DRV_CDU_ENABLE_CHK_ERR		OFF		//!< CDUブロックエラー処理
#define	DRV_CKGEN_ENABLE_CHK_ERR	OFF		//!< CKGENブロックエラー処理
#define	DRV_CPUTOP_ENABLE_CHK_ERR	OFF		//!< CPUTOPブロックエラー処理
#define	DRV_DAC_ENABLE_CHK_ERR		OFF		//!< DACブロックエラー処理
#define	DRV_DIS_ENABLE_CHK_ERR		OFF		//!< DISブロックエラー処理
#define	DRV_DTC_ENABLE_CHK_ERR		OFF		//!< DTCブロックエラー処理
#define	DRV_EBC_ENABLE_CHK_ERR		OFF		//!< EBCブロックエラー処理
#define	DRV_ENC_ENABLE_CHK_ERR		OFF		//!< ENCブロックエラー処理
#define	DRV_EXTDMA_ENABLE_CHK_ERR	OFF		//!< EXTDMAブロックエラー処理
#define	DRV_GDC_ENABLE_CHK_ERR		OFF		//!< GDCブロックエラー処理
#define	DRV_GPIOU_ENABLE_CHK_ERR	OFF		//!< GPIOUブロックエラー処理
#define	DRV_HSF_ENABLE_CHK_ERR		OFF		//!< HSFブロックエラー処理
#define	DRV_HSZ_ENABLE_CHK_ERR		OFF		//!< HSZブロックエラー処理
#define	DRV_HIST_ENABLE_CHK_ERR		OFF		//!< HISTブロックエラー処理
#define	DRV_IRS_ENABLE_CHK_ERR		OFF		//!< IRSブロックエラー処理
#define	DRV_LIN_ENABLE_CHK_ERR		OFF		//!< LINブロックエラー処理
#define	DRV_LCDIF_ENABLE_CHK_ERR	OFF		//!< LCDIFブロックエラー処理
#define	DRV_MEIFU_ENABLE_CHK_ERR	OFF		//!< MEIFUブロックエラー処理
#define	DRV_MEMIO_ENABLE_CHK_ERR	OFF		//!< MEMIOブロックエラー処理
#define	DRV_MMU_ENABLE_CHK_ERR		OFF		//!< MMUブロックエラー処理
#define	DRV_MONM_ENABLE_CHK_ERR		OFF		//!< MONMブロックエラー処理
#define	DRV_MTX_ENABLE_CHK_ERR		OFF		//!< MTXブロックエラー処理
#define	DRV_OIS_ENABLE_CHK_ERR		OFF		//!< OISブロックエラー処理
#define	DRV_PID_ENABLE_CHK_ERR		OFF		//!< PIDブロックエラー処理
#define	DRV_PPU_ENABLE_CHK_ERR		OFF		//!< PPUブロックエラー処理
#define	DRV_SERIAL_ENABLE_CHK_ERR	OFF		//!< SERIALブロックエラー処理
#define	DRV_SSG_ENABLE_CHK_ERR		OFF		//!< SSGブロックエラー処理
#define	DRV_TIMER_ENABLE_CHK_ERR	OFF		//!< TIMERブロックエラー処理
#define	DRV_USBIFU_ENABLE_CHK_ERR	OFF		//!< USBIFUブロックエラー処理
#define	DRV_XMC_ENABLE_CHK_ERR		OFF		//!< XMCブロックエラー処理
#define	DRV_YCU_ENABLE_CHK_ERR		OFF		//!< YCUブロックエラー処理
#define	DRV_NRU_ENABLE_CHK_ERR		OFF		//!< NRUブロックエラー処理
#endif
/*! @} -------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*!
 * @defgroup 	DRV_MMU_CLEAR	MMUソケットクリアを行う場合の割り込み禁止／許可(cond.mk内)
 * @{
 */
/* -----------------------------------------------------------------------------*/
#ifdef	DRV_ENABLE_IRQ_MMU_CLEAR
	#define	DRV_PPM_IRQ_MMU_CLEAR	ON		//!< PPMブロック
	#define	DRV_MON_IRQ_MMU_CLEAR	ON		//!< MONブロック
	#define	DRV_MIF_IRQ_MMU_CLEAR	ON		//!< MIFブロック
	#define	DRV_DMA_IRQ_MMU_CLEAR	ON		//!< DMAブロック
	#define	DRV_YCM_IRQ_MMU_CLEAR	ON		//!< YCMブロック
	#define	DRV_JPM_IRQ_MMU_CLEAR	ON		//!< JPMブロック
#else
	#define	DRV_PPM_IRQ_MMU_CLEAR	OFF		//!< PPMブロック
	#define	DRV_MON_IRQ_MMU_CLEAR	OFF		//!< MONブロック
	#define	DRV_MIF_IRQ_MMU_CLEAR	OFF		//!< MIFブロック
	#define	DRV_DMA_IRQ_MMU_CLEAR	OFF		//!< DMAブロック
	#define	DRV_YCM_IRQ_MMU_CLEAR	OFF		//!< YCMブロック
	#define	DRV_JPM_IRQ_MMU_CLEAR	OFF		//!< JPMブロック
#endif
/*! @} -------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*!
 * @defgroup 	VIDEO_BLK_END	VIDEO系ブランキング終了位置
 * @{
 */
/* -----------------------------------------------------------------------------*/
#define	NTSC_VIDEO_HBLK_END			293		//!< VIDEO系内部水平ブランキング終了位置(NTSC)
#define	PAL_VIDEO_HBLK_END			323		//!< VIDEO系内部水平ブランキング終了位置(PAL)	
#define	NTSC_VIDEO_VBLK_END			 33		//!< VIDEO系内部垂直ブランキング終了位置(NTSC)
#define	PAL_VIDEO_VBLK_END			 45		//!< VIDEO系内部垂直ブランキング終了位置(PAL)	
/*! @} -------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*!
 * @defgroup 	DRV_FAF_SW		高速AF対応
 * @{
 */
/* -----------------------------------------------------------------------------*/
#define DRV_CMN_FAF_GET_MODE(MODE)	((MODE) & 0xf000)	//!< 高速AFモード取得
#define DRV_CMN_FAF_MODE060			0x0000 				//!< 高速AF (60fps)
#define DRV_CMN_FAF_MODE120			0x1000 				//!< 高速AF (120fps)
#define DRV_SSG_FAF_VD_MAXCNT		0x01   				//!< CCD系垂直同期信号周期
#define DRV_SSG_FAF_VD_BLK_WIDTH	0x02				//!< CCD系垂直同期信号ブランキング幅
#define DRV_SSG_FAF_LAST_HDHEAD		0x04				//!< CCD系水平同期信号最終HDHEADのCLK数
#define DRV_PP1_FAF_CCDW_START_VPOS	0x08				//!< 取込み開始位置
#define DRV_PP1_FAF_CCDW_STOP_VPOS	0x10				//!< 取込み終了位置
#define DRV_YCM_FAF_FG_CCDR_LIMITV	0x20				//!< 読み込み水平画素数
#define DRV_MONM_FAF_VMAX_PIC		0x40 				//!< 読み出しライン数
#define DRV_MONM_FAF_VPOS_PIC		0x80 				//!< 読み出し開始位置
/*! @} -------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*!
 * @defgroup	VIDEO_SYNC_DLY			Video系内部同期信号位相調整
 *
 *	<b>水平位相 制限事項：</b>
 *		- CASIO製LCD：(6n+5)の値を定義してください。
 *		- SANYO製LCD：LCDの仕様に合わせてください。(推奨値：0x5D)	<BR>
 *			（以降、::eLdVOU_SetPictureSourc関数の水平方向開始位置によって変動。）
 * @{
 */
/*------------------------------------------------------------------------------*/
#define	VIDEO_SYNC_H	0x2F					//!< 内部同期信号 水平位相調整
#define	VIDEO_SYNC_V	0x00					//!< 内部同期信号 垂直位相調整
/*! @} -------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_BYTE_PER_PAGE
 * @brief	 システムの転送単位を規定
 */
/*------------------------------------------------------------------------------*/
#define DRV_BYTE_PER_PAGE		64

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_BYTE_PER_SPREAD
 * @brief	 １スプレッド当たりのバイト数
 */
/*------------------------------------------------------------------------------*/
#define DRV_BYTE_PER_SPREAD		32

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_BYTE_PER_WSPREAD
 * @brief	 ２スプレッド当たりのバイト数
 */
/*------------------------------------------------------------------------------*/
#define DRV_BYTE_PER_WSPREAD		64

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_DIV_ROUNDUP
 * @brief	 割り算（切り上げ）
 */
/*------------------------------------------------------------------------------*/
#define DRV_DIV_ROUNDUP(a, b)		(((a) + (b) - 1) / (b))

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_DIV_ROUNDUP_MINUS
 * @brief	 割り算（切り上げ）負数対応
 */
/*------------------------------------------------------------------------------*/
#define DRV_DIV_ROUNDUP_MINUS(a, b)		\
	((a > 0) ? (((a) + (b) - 1) / (b)) : ((-1) * ((((-1) * a) + (b) - 1) / (b))))

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_GET_ALIGN
 * @brief	 アライメント
 */
/*------------------------------------------------------------------------------*/
#define	DRV_GET_ALIGN(VAL, ALIGN)		(DRV_DIV_ROUNDUP((VAL), (ALIGN)) * (ALIGN))

/*------------------------------------------------------------------------------*/
/*!
 * @def		GET_FAST_PAGE_PADDING			
 * @brief	ラインオフセット(4N+2)補正後の水平画素数
 */
/* -----------------------------------------------------------------------------*/
#define  GET_FAST_PAGE_PADDING(PIX)											\
(																			\
	(((DRV_DIV_ROUNDUP(PIX,DRV_BYTE_PER_PAGE) / 4) * 4 + 2) >= DRV_DIV_ROUNDUP(PIX,DRV_BYTE_PER_PAGE)) \
	? (((DRV_DIV_ROUNDUP(PIX,DRV_BYTE_PER_PAGE) / 4) * 4 + 2) * DRV_BYTE_PER_PAGE)			\
	: ((((DRV_DIV_ROUNDUP(PIX,DRV_BYTE_PER_PAGE) / 4) + 1) * 4 + 2) * DRV_BYTE_PER_PAGE)	\
)

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_LOCK_REG_ON
 * @brief	排他制御用セマフォをON
 */
/*------------------------------------------------------------------------------*/
#define	DRV_CMN_LOCK_REG_ON

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_LOCK_REG_OFF
 * @brief	排他制御用セマフォをOFF
 */
/*------------------------------------------------------------------------------*/
#define	DRV_CMN_LOCK_REG_OFF

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_RESOURCE_CH_xxx
* @brief	リソース管理用　リソースCH数
 */
/*------------------------------------------------------------------------------*/
#define	DRV_RESOURCE_CH_CPU_DMAC0	8	//!< CPU DMAC0
#define	DRV_RESOURCE_CH_CPU_DMAC1	8	//!< CPU DMAC1
#define	DRV_RESOURCE_CH_STU_DMAC	8	//!< STU DMAC
#define	DRV_RESOURCE_CH_MEMIO		6	//!< MEMIO DMA
#define	DRV_RESOURCE_CH_TIMER32		26	//!< TIMER32
#define	DRV_RESOURCE_CH_ARM_TIMER	1	//!< ARM TIMER
#define	DRV_RESOURCE_CH_SSP			8	//!< SSP
#define	DRV_RESOURCE_CH_UART		4	//!< UART
#define	DRV_RESOURCE_CH_I2C			5	//!< I2C
#define	DRV_RESOURCE_CH_AD0			12	//!< AD0
#define	DRV_RESOURCE_CH_AD1			7	//!< AD1
#define	DRV_RESOURCE_CH_AD2			4	//!< AD2
#define	DRV_RESOURCE_CH_CDU			2	//!< Shadow Core
#define	DRV_RESOURCE_CH_PIC1		1	//!< VOU PIC1
#define	DRV_RESOURCE_CH_PIC2		1	//!< VOU PIC2
#define	DRV_RESOURCE_CH_OSD1		1	//!< VOU OSD1
#define	DRV_RESOURCE_CH_OSD2		1	//!< VOU OSD2
#define	DRV_RESOURCE_CH_OSD3		1	//!< VOU OSD3
#define	DRV_RESOURCE_CH_GFX			1	//!< VOU GFX
#define	DRV_RESOURCE_CH_ADU			1	//!< ADU
#define	DRV_RESOURCE_CH_TCC			8	//!< TCC
#define	DRV_RESOURCE_CH_GENERAL		16	//!< General (ch0 - ch15)

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_ID
 * @brief	ドライバID
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DRV_ID_CMN = 0,							/*!<  0 : CMN		*/
	DRV_ID_ADC,								/*!<  1 : ADC		*/
	DRV_ID_ADU,								/*!<  2 : ADU		*/
	DRV_ID_CDU,								/*!<  3 : CDU		*/
	DRV_ID_CKGEN,							/*!<  4 : CKGEN		*/
	DRV_ID_CPUTOP,							/*!<  5 : CPUTOP	*/
	DRV_ID_DAC,								/*!<  6 : DAC		*/
	DRV_ID_DIS,								/*!<  7 : DIS		*/
	DRV_ID_DTC,								/*!<  8 : DTC		*/
	DRV_ID_EBC,								/*!<  9 : EBC		*/
	DRV_ID_EXTDMA,							/*!< 10 : EXTDMA	*/
	DRV_ID_GDC,								/*!< 11 : GDC		*/
	DRV_ID_GPIOU,							/*!< 12 : GPIOU		*/
	DRV_ID_HSF,								/*!< 13 : HSF		*/
	DRV_ID_HSZ,								/*!< 14 : HSZ		*/
	DRV_ID_IRS,								/*!< 15 : IRS		*/
	DRV_ID_LIN,								/*!< 16 : LIN		*/
	DRV_ID_MEIF,							/*!< 17 : MEIFU		*/
	DRV_ID_MEM,								/*!< 18 : MEMIO		*/
	DRV_ID_MMU,								/*!< 19 : MMU		*/
	DRV_ID_OIS,								/*!< 20 : OIS		*/
	DRV_ID_PID,								/*!< 21 : PID		*/
	DRV_ID_PPU,								/*!< 22 : PPU		*/
	DRV_ID_SERIAL,							/*!< 23 : SERIAL	*/
	DRV_ID_SSG,								/*!< 24 : SSG		*/
	DRV_ID_TIMER,							/*!< 25 : TIMER		*/
	DRV_ID_USBIF,							/*!< 26 : USBIFU	*/
	DRV_ID_VOU,								/*!< 27 : VOU		*/
	DRV_ID_XMC,								/*!< 28 : XMC		*/
	DRV_ID_EMC = DRV_ID_XMC,				/*!< 28 : EMC		*/
	DRV_ID_YCU,								/*!< 29 : YCU		*/
	DRV_ID_FRU,								/*!< 30 : FRU		*/
	DRV_ID_RTC,								/*!< 31 : RTC		*/
	DRV_ID_IRQC,							/*!< 32 : IRQC		*/
	DRV_ID_KAOU,							/*!< 33 : KAOU		*/
	DRV_ID_CACHEIF,							/*!< 34 : CACHEIF	*/
	DRV_ID_VPP,								/*!< 35 : VPP		*/
	DRV_ID_TCC,								/*!< 36 : TCC		*/
	DRV_ID_PMU,								/*!< 37 : PMU		*/
	DRV_ID_DMAC,							/*!< 38 : DMAC		*/
	DRV_ID_MAXNUM
} eDRV_ID;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_ERR
 * @brief	ドライバエラーコード
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	/* CMN */
	DRV_ERR_CMN_HARDWARE_CONFLICT = 0,		/*!< CMN	: ハードウェア衝突			*/
	DRV_ERR_CMN_HARDWARE_NORESOURCE,		/*!< CMN	: ハードウェアリソースなし	*/
	DRV_ERR_CMN_INIT_OK,					/*!< CMN	: 正常終了					*/
	DRV_ERR_CMN_FAF_OK,						/*!< CMN	: 高速AF正常設定			*/
	DRV_ERR_CMN_RESOURCE_OK,				/*!< CMN	: リソース管理 正常終了		*/
	DRV_ERR_CMN_RESOURCE_ALLREADY_GOT,		/*!< CMN	: リソース管理 指定チャネル使用中	*/
	DRV_ERR_CMN_RESOURCE_ALLREADY_RELEASED,	/*!< CMN	: リソース管理 指定チャネル解放済み	*/
	/* ADC */
	DRV_ERR_ADC_OK = DRV_ID_ADC * 100,		/*!< ADC	: 正常終了					*/
	DRV_ERR_ADC_RUN,						/*!< ADC	: A/D変換中					*/
	DRV_ERR_ADC_STOP,						/*!< ADC	: A/D変換停止中				*/
	DRV_ERR_ADC_PAUSE,						/*!< ADC	: A/D変換待機中				*/
	DRV_ERR_ADC_PRM,						/*!< ADC	: パラメータエラー			*/
	DRV_ERR_ADC_UNDER_CONVERSION,			/*!< ADC	: 変換中エラー	 			*/
	DRV_ERR_ADC_NOT_CONVERSION,				/*!< ADC	: 未変換エラー				*/
	DRV_ERR_ADC_NOT_SET,					/*!< ADC	: 設定エラー				*/
	DRV_ERR_ADC_POWDN,						/*!< ADC	: パワーダウンエラー		*/
	DRV_ERR_ADC_OTHER,						/*!< ADC	: その他のエラー			*/
	/* ADU */
	DRV_ERR_ADU_OK = DRV_ID_ADU * 100, 		/*!< ADU	: 正常終了 					*/
	DRV_ERR_ADU_HWERROR, 					/*!< ADU	: ADUハードウェアエラー 	*/
	DRV_ERR_ADU_PRM, 						/*!< ADU	: パラメータエラー 			*/
	DRV_ERR_ADU_STATUS_RUN, 				/*!< ADU	: ADU動作中エラー 			*/
	DRV_ERR_ADU_STATUS_STOP, 				/*!< ADU	: 対象パス停止エラー  		*/
	DRV_ERR_ADU_NOT_CONF, 					/*!< ADU	: 動作モード未設定エラー  	*/
	DRV_ERR_ADU_DMA_ALREADY_GOT,			/*!< ADU	: リソース取得エラー		*/
	DRV_ERR_ADU_DTC_ALREADY_GOT,			/*!< ADU	: DTCリソース取得エラー		*/
	DRV_ERR_ADU_MEMIO_ALREADY_GOT,			/*!< ADU	: MEMIOリソース取得エラー	*/
	DRV_ERR_ADU_TRANSMIT,					/*!< ADU	: 転送中でないエラー		*/
	DRV_ERR_ADU_ALREADY_GOT,				/*!< ADU	: DMAリソース確保失敗		*/
	DRV_ERR_ADU_RESTART_DMA,				/*!< ADU	: DMAマイコン時エラー		*/
	/* CDU */
	DRV_ERR_CDU_OK = DRV_ID_CDU * 100,		/*!< CDU	: 正常終了					*/
	DRV_ERR_CDU_H264_OK,					/*!< CDU,H.264	: 正常終了				*/
	DRV_ERR_CDU_MPEG4_OK,					/*!< CDU,H.264	: 正常終了				*/
	DRV_ERR_CDU_PRM,						/*!< CDU	: パラメータエラー			*/
	DRV_ERR_CDU_ALIGNMENT,					/*!< CDU	: アライメントエラー		*/
	DRV_ERR_CDU_DUMMY_ACCESS_TIMEOUT,		/*!< CDU	: タイムアウトエラー		*/
	/* CKGEN */
	DRV_ERR_CKGEN_OK = DRV_ID_CKGEN * 100,	/*!< CKGEN	: 正常終了					*/
	DRV_ERR_CKGEN_PRM,						/*!< CKGEN	: パラメータエラー			*/
	DRV_ERR_CKGEN_TIMEOUT,					/*!< CKGEN	: タイムアウトエラー		*/
	/* CPUTOP */
	DRV_ERR_CPUTOP_OK = DRV_ID_CPUTOP * 100,/*!< CPUTOP : 正常終了					*/
	DRV_ERR_CPUTOP_PRM,						/*!< CPUTOP : パラメータエラー			*/
	DRV_ERR_CPUTOP_DMA_OK,					/*!< CPUTOP : DMA設定OK					*/
	DRV_ERR_CPUTOP_DMA_PRM,					/*!< CPUTOP : DMAパラメータエラー		*/
	DRV_ERR_CPUTOP_DMA_ALLREADY_GOT,		/*!< CPUTOP : DMA確保済み				*/
	DRV_ERR_CPUTOP_DMA_ALLREADY_RELEASED,  	/*!< CPUTOP : DMA解放済み				*/
	DRV_ERR_CPUTOP_DMA_NOT_GET,				/*!< CPUTOP : DMAリソース未取得エラー	*/
	DRV_ERR_CPUTOP_DMA_NOT_SETUP, 			/*!< CPUTOP : DMA動作未設定エラー		*/
	DRV_ERR_CPUTOP_DMA_TRANSMIT_BUSY, 		/*!< CPUTOP : DMA転送中エラー			*/
	DRV_ERR_CPUTOP_DMA_STATUS_RUN,			/*!< CPUTOP	: DMA転送中					*/
	DRV_ERR_CPUTOP_DMA_STATUS_STOP,			/*!< CPUTOP : DMA停止中					*/
	/* DAC */
	DRV_ERR_DAC_OK = DRV_ID_DAC * 100,		/*!< DAC	: 正常終了					*/
	DRV_ERR_DAC_PRM,						/*!< DAC	: パラメータエラー			*/
	DRV_ERR_DAC_BSY,						/*!< DAC	: ビジーエラー				*/
	/* DIS */
	DRV_ERR_DIS_OK = DRV_ID_DIS * 100,		/*!< DIS	: 正常終了					*/
	DRV_ERR_DIS_PRM,						/*!< DIS	: パラメータエラー			*/
	/* DTC */
	DRV_ERR_DTC_OK = DRV_ID_DTC * 100,		/*!< DTC	: 正常終了					*/
	DRV_ERR_DTC_PRM,						/*!< DTC	: パラメータエラー			*/
	DRV_ERR_DTC_ALLREADY_GOT,				/*!< DTC	: リソース取得済みエラー	*/
	DRV_ERR_DTC_ALLREADY_RELEASED,  		/*!< DTC	: リソース開放済みエラー	*/
	DRV_ERR_DTC_NOT_GET,					/*!< DTC	: リソース未取得エラー		*/
	DRV_ERR_DTC_TRANSMIT_BSY,				/*!< DTC	: 転送中エラー				*/
	DRV_ERR_DTC_NOT_SETUP,					/*!< DTC	: 動作未設定エラー			*/
	DRV_ERR_DTC_TRANSMIT,					/*!< DTC	: 未転送開始エラー			*/
	DRV_ERR_DTC_NOT_RELEASE,				/*!< DTC	: リソース開放できないエラー*/
	DRV_ERR_DTC_DUMMY_ACCESS_TIMEOUT,		/*!< DTC	: タイムアウトエラー		*/
	DRV_ERR_DTC_MEMIO_PRM,					/*!< DTC	: MEMIOとDTCの設定が不一致	*/
	DRV_ERR_DTC_MEMIO_MMU_PRM,				/*!< DTC	: MEMIOバッファがディスティネーションアドレスの場合に、該当チャネルでMMUアクセス制御設定されているとエラー */
	DRV_ERR_DTC_MEMIO_NOT_RESET,			/*!< DTC	: 転送元 or 転送先のMEMIODMAチャネルのリセットが解除されてない場合	*/

	/* EBC */
	DRV_ERR_EBC_OK = DRV_ID_EBC * 100,		/*!< EBC	: 正常終了					*/
	DRV_ERR_EBC_PRM,						/*!< EBC	: パラメータエラー			*/
	DRV_ERR_EBC_BSY,						/*!< EBC	: ビジーエラー				*/
	/* EXTDMA */
	DRV_ERR_EXTDMA_OK = DRV_ID_EXTDMA * 100,/*!< EXTDMA	: 正常終了					*/
	DRV_ERR_EXTDMA_PRM,						/*!< EXTDMA	: パラメータエラー			*/
	/* GDC */
	DRV_ERR_GDC_OK = DRV_ID_GDC * 100,		/*!< GDC	: 正常終了					*/
	DRV_ERR_GDC_PRM,						/*!< GDC	: パラメータエラー			*/
	DRV_ERR_GDC_BSY,						/*!< GDC	: ビジーエラー				*/
	DRV_ERR_GDC_ALIGNMENT,					/*!< GDC	: アライメントエラー		*/
	/* GPIO */
	DRV_ERR_GPIO_OK = DRV_ID_GPIOU * 100,	/*!< GPIOU	: 正常終了					*/
	DRV_ERR_GPIO_PRM,						/*!< GPIOU	: パラメータエラー			*/
	DRV_ERR_GPIO_BSY,						/*!< GPIOU	: ビジーエラー				*/
	DRV_ERR_GPIO_FUNCTION,					/*!< GPIOU	: ポートエラー				*/
	DRV_ERR_GPIO_DIRECTION,					/*!< GPIOU	: ディレクションエラー		*/
	DRV_ERR_GPIO_OUTPORTS_REG_USED,			/*!< GPIOU	: リソースエラー			*/
	/* HSF */
	DRV_ERR_HSF_OK = DRV_ID_HSF * 100,		/*!< HSF	: 正常終了					*/
	DRV_ERR_HSF_PRM,						/*!< HSF	: パラメータエラー			*/
	/* HSZ */
	DRV_ERR_HSZ_OK = DRV_ID_HSZ * 100,		/*!< HSZ	: 正常終了					*/
	DRV_ERR_HSZ_PRM,						/*!< HSZ	: パラメータエラー			*/
	/* IRS */
	DRV_ERR_IRS_OK = DRV_ID_IRS * 100,		/*!< IRS	: 正常終了					*/
	/* LIN */
	DRV_ERR_LIN_OK = DRV_ID_LIN * 100,		/*!< LIN	: 正常終了					*/
	/* MEIFU */
	DRV_ERR_MEIF_OK = DRV_ID_MEIF * 100,	/*!< MEIFU	: 正常終了					*/
	DRV_ERR_MEIF_PRM,						/*!< MEIFU	: パラメータエラー			*/
	/* MEMIO */
	DRV_ERR_MEM_OK = DRV_ID_MEM * 100,		/*!< MEMIO	: 正常終了					*/
	DRV_ERR_MEM_PRM,						/*!< MEMIO	: パラメータエラー			*/
	DRV_ERR_MEM_ALLREADY_GOT,        		/*!< MEMIO	: リソース確保済みエラー    */
	DRV_ERR_MEM_ALLREADY_RELEASED,   		/*!< MEMIO	: リソース開放済みエラー    */
	DRV_ERR_MEM_NOT_GET,					/*!< MEMIO	: リソース未取得エラー		*/
	DRV_ERR_MEM_NOT_SET_MMU,				/*!< MEMIO	: MMU制御設定不可エラー		*/
	DRV_ERR_MEM_DMA_ACTIVE,					/*!< MEMIO	: 転送中エラー				*/
	DRV_ERR_MEM_DMA_INACTIVE,				/*!< MEMIO	: 未転送エラー				*/
	DRV_ERR_MEM_DMA_SRC_RSIZE,				/*!< MEMIO	: 転送データサイズエラー	*/
	DRV_ERR_MEM_NOT_RELEASE,				/*!< MEMIO	: リソース開放不可エラー	*/

	/* MMU */
	DRV_ERR_MMU_OK = DRV_ID_MMU * 100,		/*!< MMU	: リソース開放不可エラー	*/
	DRV_ERR_MMU_FATAL,						/*!< MMU	: 致命的エラー				*/
	DRV_ERR_MMU_INIT_FAIL,					/*!< MMU	: Initial失敗				*/
	DRV_ERR_MMU_SEGMENT_FULL,				/*!< MMU	: セグメントフル			*/
	DRV_ERR_MMU_MAP_FAIL,					/*!< MMU	: Map失敗					*/
	DRV_ERR_MMU_MAP_VALID_SEGMENT,			/*!< MMU	: 二重Map（既にMapされているセグメントに対するMap）			*/
	DRV_ERR_MMU_CLOSE_NOT_VALID_SEGMENT,	/*!< MMU	: 二重Close（既にCloseされているセグメントに対するClose）	*/
	/* OIS */
	DRV_ERR_OIS_OK = DRV_ID_OIS * 100,		/*!< OIS	: 正常終了					*/
	DRV_ERR_OIS_PRM,						/*!< OIS	: パラメータエラー			*/
	DRV_ERR_OIS_BSY,						/*!< OIS	: ビジーエラー				*/
	DRV_ERR_OIS_GET_DC,						/*!< OIS	: DC値取得におけるレジスタReadエラー						*/
	DRV_ERR_OIS_GET_PWM_OFFSET,				/*!< OIS	: PWMオフセット取得におけるレジスタReadエラー				*/
	DRV_ERR_OIS_GET_INTERVAL_AD,			/*!< OIS	: インターバルAD値取り込みにおけるレジスタReadエラー		*/
	DRV_ERR_OIS_GET_AD,						/*!< OIS	: AD値取り込みにおけるレジスタReadエラー					*/
	DRV_ERR_OIS_GET_DCLPFOUT,				/*!< OIS	: LPF出力値読み込みにおけるレジスタReadエラー				*/
	DRV_ERR_OIS_GET_DCCPSOUT,				/*!< OIS	: DC調整後の出力値読み込みにおけるレジスタReadエラー		*/
	DRV_ERR_OIS_GET_CORINGOUT,				/*!< OIS	: コアリング補正後の出力値読み込みにおけるレジスタReadエラー*/
	DRV_ERR_OIS_GET_PHASEOUT,				/*!< OIS	: 位相補償制御出力値読み込みにおけるレジスタReadエラー		*/
	DRV_ERR_OIS_GET_INTEGOUT,				/*!< OIS	: 積分処理出力値読み込みにおけるレジスタReadエラー			*/
	DRV_ERR_OIS_GET_HPFOUT,					/*!< OIS	: HPF処理出力値読み込みにおけるレジスタReadエラー			*/
	DRV_ERR_OIS_GET_GAINOUT,				/*!< OIS	: ゲイン処理出力値読み込みにおけるレジスタReadエラー		*/
	DRV_ERR_OIS_GET_PWMOUT,					/*!< OIS	: PWM出力値読み込みにおけるレジスタReadエラー				*/
	DRV_ERR_OIS_GET_OUTDATA,				/*!< OIS	: 最終出力値読み込みにおけるレジスタReadエラー				*/
	DRV_ERR_OIS_GET_HOLE_OUT,				/*!< OIS	: ホール素子出力値読み込みにおけるレジスタReadエラー		*/
	DRV_ERR_OIS_GET_MPEF,					/*!< OIS	: 基準電圧読み込みにおけるレジスタReadエラー				*/
	/* PID */
	DRV_ERR_PID_OK = DRV_ID_PID * 100,		/*!< PID	: 正常終了					*/
	DRV_ERR_PID_FATAL,						/*!< PID	: 致命的エラー				*/
	DRV_ERR_PID_PRM,                 		/*!< PID	: パラメータエラー    		*/
	DRV_ERR_PID_ALLREADY_GOT,        		/*!< PID	: 確保済みエラー      		*/
	DRV_ERR_PID_ALLREADY_RELEASED,   		/*!< PID	: 解放済みエラー      		*/
   	 DRV_ERR_PID_BSY,                 		/*!< PID	: ビジーエラー        		*/
	/* PPU */
	DRV_ERR_PPU_OK = DRV_ID_PPU * 100,		/*!< PPU	: 正常終了					*/
	DRV_ERR_PPU_FATAL,						/*!< PPU	: 致命的エラー				*/
	DRV_ERR_PPU_PRM,        				/*!< PPU	: パラメータエラー     		*/
    DRV_ERR_PPU_ORVERFLOW,  				/*!< PPU	: オーバーフローエラー 		*/
    DRV_ERR_PPU_UNDERFLOW,  				/*!< PPU	: アンダーフローエラー 		*/
    DRV_ERR_PPU_ALIGNMENT,  				/*!< PPU	: アライメントエラー   		*/
    DRV_ERR_PPU_BSY,        				/*!< PPU	: バッファビジーエラー		*/
    DRV_ERR_PPU_DUMMY_ACCESS_TIMEOUT,  		/*!< PPU	: ダミーアクセスタイムアウト*/
    DRV_ERR_PPU_DECREMENT_BKM_H_BLOCK,		/*!< PPU	: 画素数制限のためBKMブロック水平分割数を4ブロック減らす	*/
    DRV_ERR_PPU_DECREMENT_BKM_V_BLOCK,		/*!< PPU	: 画素数制限のためBKMブロック垂直分割数を4ブロック減らす	*/
    DRV_ERR_PPU_BM_H_BLOCK_CHANGE,         	/*!< PPU	: AUTO設定モードで、積算領域水平方向のブロック分割数を調整した */
    DRV_ERR_PPU_BM_V_BLOCK_CHANGE,         	/*!< PPU	: AUTO設定モードで、積算領域垂直方向のブロック分割数を調整した */
	/* SERIAL */
	DRV_ERR_SERIAL_OK = DRV_ID_SERIAL * 100,/*!< SERIAL	: 正常終了					*/
	DRV_ERR_SERIAL_PRM,						/*!< SERIAL	: パラメータエラー			*/
	DRV_ERR_SERIAL_BSY,						/*!< SERIAL	: ビジーエラー				*/
	DRV_ERR_SERIAL_INIT,					/*!< SERIAL	: シリアル未設定エラー		*/
	DRV_ERR_SERIAL_CH4_MODE,				/*!< SERIAL	: チャネル4受信エラー		*/
	DRV_ERR_SERIAL_ALLREADY_SET,			/*!< SERIAL	: シリアル既設定エラー		*/
	DRV_ERR_SERIAL_TIMEOUT,					/*!< SERIAL	: 通信タイムアウトエラー	*/
	DRV_ERR_SERIAL_IIC_NACK,				/*!< SERIAL	: IIC NACK受信エラー		*/
    /* SSG */
	DRV_ERR_SSG_OK = DRV_ID_SSG * 100,		/*!< SSG	: 正常終了					*/
	DRV_ERR_SSG_FATAL,						/*!< SSG	: 致命的エラー				*/
	DRV_ERR_SSG_PRM,       					/*!< SSG	: パラメータエラー     		*/
    DRV_ERR_SSG_BSY,       					/*!< SSG	: ビジーエラー         		*/
	/* TIMER */
	DRV_ERR_TIMER_OK = DRV_ID_TIMER * 100,	/*!< TIMER	: 正常終了					*/
	DRV_ERR_TIMER_PRM,						/*!< TIMER	: パラメータエラー			*/
	DRV_ERR_TIMER_BSY,						/*!< TIMER	: ビジーエラー				*/
	DRV_ERR_TIMER_ALLREADY_GOT,				/*!< TIMER	: リソース既取得エラー		*/
	DRV_ERR_TIMER_ALLREADY_RELEASED,		/*!< TIMER	: リソース解放済みエラー	*/
	DRV_ERR_TIMER_NOT_GET,					/*!< TIMER	: リソース未取得エラー		*/
	DRV_ERR_TIMER_NOT_SETUP,				/*!< TIMER	: 動作モード未設定エラー	*/
	DRV_ERR_TIMER_BR,						/*!< TIMER	: 分周比未設定エラー		*/
	DRV_ERR_TIMER_DUTY,						/*!< TIMER	: デューティー未設定エラー	*/
	DRV_ERR_TIMER_RESET,					/*!< TIMER	: タイマ未初期化エラー		*/
	DRV_ERR_TIMER_COUNT,					/*!< TIMER	: 起動エラー				*/
	/* USBIFU */
	DRV_ERR_USBIF_OK = DRV_ID_USBIF * 100,	/*!< USBIFU	: 正常終了					*/
	DRV_ERR_USBIF_PRM,						/*!< USBIFU	: パラメータエラー			*/
  	/* VOU */
	DRV_ERR_VOU_OK = DRV_ID_VOU * 100,		/*!< VOU	: 正常終了					*/
	DRV_ERR_VOU_PRM,						/*!< VOU	: パラメータエラー			*/
	DRV_ERR_VOU_BSY,						/*!< VOU	: ビジーエラー				*/
	DRV_ERR_VOU_MEASURE,					/*!< VOU	: HIST計測中警告			*/
	DRV_ERR_VOU_SWITCHING,					/*!< VOU	: HIST切り替え中警告		*/
	DRV_ERR_VOU_OVERFLOW_WARNING,			/*!< VOU	: オーバーフロー警告		*/
	DRV_ERR_VOU_UNDERFLOW_WARNING,			/*!< VOU	: アンダーフロー警告		*/
	DRV_ERR_VOU_ES1BUG14_PIX4,				/*!< VOU	: 4画素ずらしNGエラー		*/
	DRV_ERR_VOU_ALIGNMENT,					/*!< VOU	: アライメントエラー		*/
	DRV_ERR_VOU_ES2BUG47_HALF_TRANS,		/*!< VOU	: COLP半透過エラー			*/
	DRV_ERR_VOU_AUTO_MODE,					/*!< VOU	: NTSC/PAL切、・悗ィAUTOモードチェック警ケ・*/
	DRV_ERR_VOU_NOT_SET,					/*!< VOU	: HDMI レジスタ設定バイパス	*/
	/* XMC */
	DRV_ERR_XMC_OK = DRV_ID_XMC * 100,		/*!< XMC	: 正常終了					*/
	DRV_ERR_XMC_PRM,						/*!< XMC	: パラメータエラー			*/
	DRV_ERR_XMC_BSY,						/*!< XMC	: ビジーエラー				*/
	/* EMC */
	DRV_ERR_EMC_OK = DRV_ID_XMC * 100,		/*!< EMC	: 正常終了					*/
	DRV_ERR_EMC_PRM,						/*!< EMC	: パラメータエラー			*/
	DRV_ERR_EMC_BSY,						/*!< EMC	: ビジーエラー				*/
	DRV_ERR_EMC_ADJ,						/*!< EMC	: 位相調整エラー			*/
	DRV_ERR_EMC_DRAMINIT,					/*!< EMC	: DRAM初期化エラー			*/
  	/* YCU */
	DRV_ERR_YCU_OK = DRV_ID_YCU * 100,		/*!< YCU	: 正常終了					*/
	DRV_ERR_YCU_FATAL,						/*!< YCU	: 致命的エラー				*/
	DRV_ERR_YCU_PRM,        				/*!< YCU	: パラメータエラー     		*/
    DRV_ERR_YCU_ORVERFLOW,  				/*!< YCU	: オーバーフローエラー 		*/
    DRV_ERR_YCU_UNDERFLOW,  				/*!< YCU	: アンダーフローエラー 		*/
    DRV_ERR_YCU_ALIGNMENT,  				/*!< YCU	: アライメントエラー   		*/
    DRV_ERR_YCU_BSY,        				/*!< YCU	: ビジーエラー 				*/
    DRV_ERR_YCU_DUMMY_ACCESS_TIMEOUT,  		/*!< YCU	: ダミーアクセスタイムアウト*/
	DRV_ERR_YCU_SRZ_MAGNI,					/*!< YCU	: 超解像拡大倍率エラー(要望No.60) */
	/* FRU */
	DRV_ERR_FRU_OK = DRV_ID_FRU * 100,		/*!< FRU	: 正常終了					*/

	/* RTC */
	DRV_ERR_RTC_OK = DRV_ID_RTC * 100,		/*!< RTC	: 正常終了					*/
	DRV_ERR_RTC_NO_SET,						/*!< RTC	: アラーム設定なしエラー	*/

	/* IRQC */
	DRV_ERR_IRQC_OK = DRV_ID_IRQC * 100,	/*!< IRQC	: 正常終了					*/
	
	/* KAOU */
	DRV_ERR_KAOU_OK = DRV_ID_KAOU * 100,	/*!< KAOU	: 正常終了					*/
	DRV_ERR_KAOU_PRM,						/*!< KAOU	: パラメータエラー			*/
	DRV_ERR_KAOU_STATUS_RUN,				/*!< KAOU	: 動作中					*/
	DRV_ERR_KAOU_EYE_1,						/*!< KAOU	: 設定エラー(1人目)			*/
	DRV_ERR_KAOU_EYE_2,						/*!< KAOU	: 設定エラー(2人目)			*/
	DRV_ERR_KAOU_EYE_1_2,					/*!< KAOU	: 設定エラー(1,2人目)		*/
	DRV_ERR_KAOU_EYE_3,						/*!< KAOU	: 設定エラー(3人目)			*/
	DRV_ERR_KAOU_EYE_1_3,					/*!< KAOU	: 設定エラー(1,3人目)		*/
	DRV_ERR_KAOU_EYE_2_3,					/*!< KAOU	: 設定エラー(2,3人目)		*/
	DRV_ERR_KAOU_EYE_1_2_3,					/*!< KAOU	: 設定エラー(1,2,3人目)		*/
	DRV_ERR_KAOU_EYE_4,						/*!< KAOU	: 設定エラー(4人目)			*/
	DRV_ERR_KAOU_EYE_1_4,					/*!< KAOU	: 設定エラー(1,4人目)		*/
	DRV_ERR_KAOU_EYE_2_4,					/*!< KAOU	: 設定エラー(2,4人目)		*/
	DRV_ERR_KAOU_EYE_1_2_4,					/*!< KAOU	: 設定エラー(1,2,4人目)		*/
	DRV_ERR_KAOU_EYE_3_4,					/*!< KAOU	: 設定エラー(3,4人目)		*/
	DRV_ERR_KAOU_EYE_1_3_4,					/*!< KAOU	: 設定エラー(1,3,4人目)		*/
	DRV_ERR_KAOU_EYE_2_3_4,					/*!< KAOU	: 設定エラー(2,3,4人目)		*/
	DRV_ERR_KAOU_EYE_1_2_3_4,				/*!< KAOU	: 設定エラー(1,2,3,4人目)	*/

	/* CACHEIF */
	DRV_ERR_CACHEIF_OK = DRV_ID_CACHEIF * 100,/*!< KAOU	: 正常終了					*/
	
	/* VPP */
	DRV_ERR_VPP_OK = DRV_ID_VPP * 100,		/*!< VPP	: 正常終了					*/

	/* SUBYCU */
	DRV_ERR_SUBYCU_OK,						/*!< SUBYCU	: 正常終了					*/
	DRV_ERR_SUBYCU_PRM,						/*!< SUBYCU	: パラメータエラー			*/
	DRV_ERR_SUBYCU_ALINGMENT,				/*!< SUBYCU	: アライメントエラー		*/
	DRV_ERR_SUBYCU_BSY,						/*!< SUBYCU	: ビジーエラー				*/

	/* TCC */
	DRV_ERR_TCC_OK = DRV_ID_TCC * 100,		/*!< TCC	: 正常終了					*/
	DRV_ERR_TCC_FIFO_FULL,					/*!< TCC	: コマンドFIFOエラー		*/

	/* PMU */
	DRV_ERR_PMU_OK = DRV_ID_PMU * 100,		/*!< PMU	: 正常終了					*/

	/* DMAC*/
	DRV_ERR_DMAC_OK = DRV_ID_DMAC * 100,	/*!< DMAC	: 正常終了					*/
	DRV_ERR_DMAC_PRM,						/*!< DMAC	: パラメータエラー			*/
	DRV_ERR_DMAC_ALLREADY_GOT,				/*!< DMAC	: リソース取得済みエラー	*/
	DRV_ERR_DMAC_ALLREADY_RELEASED,  		/*!< DMAC	: リソース開放済みエラー	*/
	DRV_ERR_DMAC_NOT_GET,					/*!< DMAC	: リソース未取得エラー		*/
	DRV_ERR_DMAC_NOT_RELEASE,				/*!< DMAC	: リソース開放できないエラー*/
	DRV_ERR_DMAC_TRANSMISSION_ERR,			/*!< DMAC	: 転送エラー				*/

	DRV_ERR_MAXNUM
} eDRV_ERR;


/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SWITCH
 * @brief	OFF/ON
 */
/*------------------------------------------------------------------------------*/
typedef enum {
    DRV_SWITCH_OFF,			//!< OFF
    DRV_SWITCH_ON,			//!< ON

	DRV_SWITCH_RESERVED
} eDRV_SWITCH;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_LV
 * @brief	LOW／HIGH
 */
/*------------------------------------------------------------------------------*/
typedef enum{
    DRV_LV_LOW,				//!< LOW
    DRV_LV_HIGH				//!< HIGH
} eDRV_LV;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_VALID
 * @brief	DISABLE（禁止）／ENABLE（許可）
 */
/*------------------------------------------------------------------------------*/
typedef enum{
    DRV_VALID_DISABLE,		//!< DISABLE（禁止）
    DRV_VALID_ENABLE		//!< ENABLE （許可）
} eDRV_VALID;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_HEAD_MODE
 * @brief	HEADモード（CCD/MIX/MAICO）
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_CCD_MIX_NON	= 0x00,		/*!< 画素混合なし	*/
	DRV_CCD_MIX_4	= 0x10,		/*!< 4画素混合		*/
	DRV_CCD_MIX_9	= 0x20,		/*!< 9画素混合		*/
	DRV_MAICO_H3	= 0x40,		/*!< MAICO(水平3画素混合)	*/
	DRV_CCD_SMEAR	= 0x100,	/*!< スミア対応		*/
	DRV_CCD_4CH		= 0x200,	/*!< 4ch入力		*/
	DRV_CCD_HITLC21	= 0x400,	/*!< 水平インターレース 2:1	*/
	DRV_CCD_HITLC31	= 0x800,	/*!< 水平インターレース 3:1	*/
	DRV_CCD_HITLC41	= 0x1000,	/*!< 水平インターレース 4:1	*/
	DRV_CCD_SUB		= 0x2000,	/*!< 汎用センサ		*/
	DRV_CCD_2LINE	= 0x4000,	/*!< 2LINE入力		*/
	DRV_CCD_FAST	= 0x8000	/*!< 高速			*/
}eDRV_HEAD_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SCAN_MODE
 * @brief	CCD読み出しモード
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_CCD_SCAN_PROGRES	= 0x01,		/*!< プログレッシブ   */
	DRV_CCD_SCAN_21INTER	= 0x02,		/*!< 21インターレース */
	DRV_CCD_SCAN_31INTER	= 0x03,		/*!< 31インターレース */
	DRV_CCD_SCAN_41INTER	= 0x04,		/*!< 41インターレース */
	DRV_CCD_SCAN_61INTER	= 0x06,		/*!< 61インターレース */
	DRV_CCD_SCAN_81INTER	= 0x08,		/*!< 81インターレース */
	DRV_CCD_SCAN_121INTER	= 0x0C		/*!< 121インターレース */
}eDRV_SCAN_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_CCD_PIX_MODE
 * @brief	CCDサイズ
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_CCD_PIX_PROGRES			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ   */
	DRV_CCD_PIX_21INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_21INTER,		/*!< 21インターレース */
	DRV_CCD_PIX_31INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_31INTER,		/*!< 31インターレース */
	DRV_CCD_PIX_41INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_41INTER,		/*!< 41インターレース */
	DRV_CCD_PIX_61INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_61INTER,		/*!< 61インターレース */
	DRV_CCD_PIX_81INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_81INTER,		/*!< 81インターレース */
	DRV_CCD_PIX_121INTER		= DRV_CCD_MIX_NON | DRV_CCD_SCAN_121INTER,		/*!< 121インターレース */

	DRV_CCD_PIX_PROGRES_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , 4画素混合 */
	DRV_CCD_PIX_21INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, 4画素混合 */
	DRV_CCD_PIX_31INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, 4画素混合 */
    DRV_CCD_PIX_41INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_41INTER,		/*!< 41インターレース, 4画素混合 */
	DRV_CCD_PIX_61INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, 4画素混合 */
	DRV_CCD_PIX_81INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, 4画素混合 */
	DRV_CCD_PIX_121INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_121INTER,		/*!< 121インターレース, 4画素混合 */

	DRV_CCD_PIX_PROGRES_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , 9画素混合 */
	DRV_CCD_PIX_21INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, 9画素混合 */
	DRV_CCD_PIX_31INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, 9画素混合 */
    DRV_CCD_PIX_41INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_31INTER,		/*!< 41インターレース, 9画素混合 */
	DRV_CCD_PIX_61INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, 9画素混合 */
	DRV_CCD_PIX_81INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, 9画素混合 */
	DRV_CCD_PIX_121INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_121INTER,		/*!< 121インターレース, 9画素混合 */

	DRV_MAICO_PIX_PROGRES_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , MAICO(水平3画素) */
	DRV_MAICO_PIX_21INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, MAICO(水平3画素) */
	DRV_MAICO_PIX_31INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, MAICO(水平3画素) */
    DRV_MAICO_PIX_41INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_31INTER,		/*!< 41インターレース, MAICO(水平3画素) */
	DRV_MAICO_PIX_61INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, MAICO(水平3画素) */
	DRV_MAICO_PIX_81INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, MAICO(水平3画素) */
	DRV_MAICO_PIX_121INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_121INTER,		/*!< 121インターレース, MAICO(水平3画素) */

	DRV_SMEAR_PIX_PROGRES		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , スミア対応 */
	DRV_SMEAR_PIX_21INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, スミア対応 */
	DRV_SMEAR_PIX_31INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, スミア対応 */
    DRV_SMEAR_PIX_41INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_41INTER,		/*!< 41インターレース, スミア対応 */
	DRV_SMEAR_PIX_61INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, スミア対応 */
	DRV_SMEAR_PIX_81INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, スミア対応 */
	DRV_SMEAR_PIX_121INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_121INTER,		/*!< 121インターレース, スミア対応 */

	DRV_4CH_PIX_PROGRES			= DRV_CCD_4CH		| DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , 4ch入力 */
	DRV_4CH_PIX_21INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, 4ch入力 */
	DRV_4CH_PIX_31INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, 4ch入力 */
    DRV_4CH_PIX_41INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_41INTER,		/*!< 41インターレース, 4ch入力 */
	DRV_4CH_PIX_61INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, 4ch入力 */
	DRV_4CH_PIX_81INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, 4ch入力 */
	DRV_4CH_PIX_121INTER		= DRV_CCD_4CH		| DRV_CCD_SCAN_121INTER,	/*!< 121インターレース, 4ch入力 */

	DRV_HI2_1_PIX_PROGRES		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , 水平インターレース2:1 */
	DRV_HI2_1_PIX_21INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, 水平インターレース2:1 */
	DRV_HI2_1_PIX_31INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, 水平インターレース2:1 */
	DRV_HI2_1_PIX_41INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_41INTER,		/*!< 41インターレース, 水平インターレース2:1 */
	DRV_HI2_1_PIX_61INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, 水平インターレース2:1 */
	DRV_HI2_1_PIX_81INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, 水平インターレース2:1 */
	DRV_HI2_1_PIX_121INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_121INTER,	/*!< 121インターレース, 水平インターレース2:1 */

	DRV_HI3_1_PIX_PROGRES		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , 水平インターレース3:1 */
	DRV_HI3_1_PIX_21INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, 水平インターレース3:1 */
	DRV_HI3_1_PIX_31INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, 水平インターレース3:1 */
	DRV_HI3_1_PIX_41INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_41INTER,		/*!< 41インターレース, 水平インターレース3:1 */
	DRV_HI3_1_PIX_61INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, 水平インターレース3:1 */
	DRV_HI3_1_PIX_81INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, 水平インターレース3:1 */
	DRV_HI3_1_PIX_121INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_121INTER,	/*!< 121インターレース, 水平インターレース3:1 */

	DRV_HI4_1_PIX_PROGRES		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_PROGRES,		/*!<  プログレッシブ  , 水平インターレース4:1 */
	DRV_HI4_1_PIX_21INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_21INTER,		/*!<  21インターレース, 水平インターレース4:1 */
	DRV_HI4_1_PIX_31INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_31INTER,		/*!<  31インターレース, 水平インターレース4:1 */
	DRV_HI4_1_PIX_41INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_41INTER,		/*!<  41インターレース, 水平インターレース4:1 */
	DRV_HI4_1_PIX_61INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_61INTER,		/*!<  61インターレース, 水平インターレース4:1 */
	DRV_HI4_1_PIX_81INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_81INTER,		/*!<  81インターレース, 水平インターレース4:1 */
	DRV_HI4_1_PIX_121INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_121INTER,	/*!< 121インターレース, 水平インターレース4:1 */

	DRV_SUB_PIX_PROGRES			= DRV_CCD_SUB	| DRV_CCD_SCAN_PROGRES,			/*!<  プログレッシブ  , 汎用センサ */
	DRV_SUB_PIX_21INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_21INTER,			/*!<  21インターレース, 汎用センサ */
	DRV_SUB_PIX_31INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_31INTER,			/*!<  31インターレース, 汎用センサ */
	DRV_SUB_PIX_41INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_41INTER,			/*!<  41インターレース, 汎用センサ */
	DRV_SUB_PIX_61INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_61INTER,			/*!<  61インターレース, 汎用センサ */
	DRV_SUB_PIX_81INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_81INTER,			/*!<  81インターレース, 汎用センサ */
	DRV_SUB_PIX_121INTER		= DRV_CCD_SUB	| DRV_CCD_SCAN_121INTER,			/*!< 121インターレース, 汎用センサ */
	/* 2LINE同時出力 */
	DRV_2LINE_PIX_PROGRES			= DRV_CCD_2LINE		| DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , 2Line入力 */
	DRV_2LINE_PIX_21INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, 2Line入力 */
	DRV_2LINE_PIX_31INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, 2Line入力 */
    DRV_2LINE_PIX_41INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_41INTER,		/*!< 41インターレース, 2Line入力 */
	DRV_2LINE_PIX_61INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, 2Line入力 */
	DRV_2LINE_PIX_81INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, 2Line入力 */
	DRV_2LINE_PIX_121INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_121INTER,	/*!< 121インターレース, 2Line入力 */
	
	DRV_2LINE_HI2_1_PIX_PROGRES		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , 水平インターレース2:1 2Line */
	DRV_2LINE_HI2_1_PIX_21INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, 水平インターレース2:1 2Line */
	DRV_2LINE_HI2_1_PIX_31INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, 水平インターレース2:1 2Line */
	DRV_2LINE_HI2_1_PIX_41INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_41INTER,		/*!< 41インターレース, 水平インターレース2:1 2Line */
	DRV_2LINE_HI2_1_PIX_61INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, 水平インターレース2:1 2Line */
	DRV_2LINE_HI2_1_PIX_81INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, 水平インターレース2:1 2Line */
	DRV_2LINE_HI2_1_PIX_121INTER	= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_121INTER,	/*!< 121インターレース, 水平インターレース2:1 2Line */
	
	DRV_2LINE_HI3_1_PIX_PROGRES		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_PROGRES,		/*!< プログレッシブ  , 水平インターレース3:1 2Line */
	DRV_2LINE_HI3_1_PIX_21INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_21INTER,		/*!< 21インターレース, 水平インターレース3:1 2Line */
	DRV_2LINE_HI3_1_PIX_31INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_31INTER,		/*!< 31インターレース, 水平インターレース3:1 2Line */
	DRV_2LINE_HI3_1_PIX_41INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_41INTER,		/*!< 41インターレース, 水平インターレース3:1 2Line */
	DRV_2LINE_HI3_1_PIX_61INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_61INTER,		/*!< 61インターレース, 水平インターレース3:1 2Line */
	DRV_2LINE_HI3_1_PIX_81INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_81INTER,		/*!< 81インターレース, 水平インターレース3:1 2Line */
	DRV_2LINE_HI3_1_PIX_121INTER	= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_121INTER,	/*!< 121インターレース, 水平インターレース3:1 2Line */

	DRV_2LINE_HI4_1_PIX_PROGRES		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_PROGRES,		/*!<  プログレッシブ  , 水平インターレース4:1 2Line */
	DRV_2LINE_HI4_1_PIX_21INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_21INTER,		/*!<  21インターレース, 水平インターレース4:1 2Line */
	DRV_2LINE_HI4_1_PIX_31INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_31INTER,		/*!<  31インターレース, 水平インターレース4:1 2Line */
	DRV_2LINE_HI4_1_PIX_41INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_41INTER,		/*!<  41インターレース, 水平インターレース4:1 2Line */
	DRV_2LINE_HI4_1_PIX_61INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_61INTER,		/*!<  61インターレース, 水平インターレース4:1 2Line */
	DRV_2LINE_HI4_1_PIX_81INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_81INTER,		/*!<  81インターレース, 水平インターレース4:1 2Line */
	DRV_2LINE_HI4_1_PIX_121INTER	= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_121INTER,	/*!< 121インターレース, 水平インターレース4:1 2Line */
	
	/* 高速 */
	DRV_FAST_PIX_PROGRES		= DRV_CCD_FAST	| DRV_CCD_SCAN_PROGRES			/*!< 高速 */
} eDRV_CCD_PIX_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_MODE_3DNR
 * @brief	3DNRの動作選択
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	D3NR_OFF,
	D3NR_FIR,
	D3NR_IIR,
	D3NR_MAX,
	D3NR_MIN
} eDRV_MODE_3DNR;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PPU_3DNRIN
 * @brief	PP1 3DNRの入力選択
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_PPU_3DNRIN_SENSOR,
	DRV_PPU_3DNRIN_DRAM_RAW,
	DRV_PPU_3DNRIN_DRAM_Y,
	DRV_PPU_3DNRIN_DRAM_C
} eDRV_PPU_3DNRIN;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PPU_SET_MODE_SW
 * @brief	BM、BKM、BKEDGE枠の設定モード選択（Auto/Manual）
 */
/*------------------------------------------------------------------------------*/
typedef  enum{
	DRV_PPU_SET_MODE_MANUAL = 0,     //!< Manual設定モード選択
	DRV_PPU_SET_MODE_AUTO             //!< AUTO設定モード選択
} eDRV_PPU_SET_MODE_SW;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PP1_DRAMOUT
 * @brief	PP1 DRAMへの出力切り替え
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_PPU_DRAMOUT_AFTER_3DNR,
	//DRV_PPU_DRAMOUT_AFTER_DPF	//DPF削除のため、名称変更
	DRV_PPU_DRAMOUT_AFTER_EVF
} eDRV_PPU_DRAMOUT;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	sDRV_MMU_MODE
 * @brief	MMUスイッチ
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_MMU_OFF = 0,				//!< MMU OFF
	DRV_MMU_ON  = 1					//!< MMU ON
} sDRV_MMU_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_MMU_AUTO_CLOSE
 * @brief	Write AutoClose
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	AUTO_CLOSE_OFF,
	AUTO_CLOSE_ON,

	DRV_MMU_AUTO_CLOSE_RESERVED
} eDRV_MMU_AUTO_CLOSE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_MMU_AUTO_PURGE
 * @brief	Write AutoPurge
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
    AUTO_PURGE_OFF,
	AUTO_PURGE_ON,

	DRV_MMU_AUTO_PURGE_RESERVED
} eDRV_MMU_AUTO_PURGE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_RESOURCE
 * @brief	リソースの空き状態／使用中
 */
/*------------------------------------------------------------------------------*/
typedef enum {
    DRV_RESOURCE_EMPTY,		//!< リソース空き状態
    DRV_RESOURCE_USED,		//!< リソース使用中

	DRV_RESOURCE_RESERVED
}  eDRV_RESOURCE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_DMA_DIRECTION
 * @brief	DMA転送方向設定 (MEIFU,USBIFUで使用)
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DMA_DISABLE,			//!< ディセーブル	// Dummy（使用しない）
	DMA_READ,				//!< メディア、外部デバイス等 → 該当ブロック
	DMA_WRITE				//!< 該当ブロック → メディア、外部デバイス等
}eDRV_DMA_DIRECTION;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_NTPAL_MODE
 * @brief	NTSC/PALモード
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DRV_NTPAL_MODE_NTSC,		//!< NTSCモード
	DRV_NTPAL_MODE_HDTV_525_60,	//!< NTSCモード(60i)
	DRV_NTPAL_MODE_PAL,			//!< PALモード
	DRV_NTPAL_MODE_HDTV_1125,	//!< HDTVモード（1125i/p/4K2K）
	DRV_NTPAL_MODE_HDTV_1125_60,//!< HDTVモード（1125i/p/4K2K）60Hz	
	DRV_NTPAL_MODE_HDTV_750,	//!< HDTVモード（750p）
	DRV_NTPAL_MODE_HDTV_750_60,	//!< HDTVモード（750p）60Hz
	DRV_NTPAL_MODE_HDTV_1250,	//!< HDTVモード（1250i）
	DRV_NTPAL_MODE_EVF_5994,	//!< EVFモード（59.94p）
	DRV_NTPAL_MODE_EVF_50,		//!< EVFモード（50p）
	DRV_NTPAL_MODE_EVF_24,		//!< EVFモード（24p）
	DRV_NTPAL_MODE_EVF_2398,	//!< EVFモード（23.98p）
	DRV_NTPAL_MODE_AUTO,		//!< NTSC(EVF) ⇔ PAL(EVF)

	DRV_NTPAL_MODE_RESERVED
} eDRV_NTPAL_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_IMAGE_ASPECT
 * @brief	映像アスペクト比設定
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	IMAGE_ASPECT_4_3,		//!< アスペクト比	 4:3
	IMAGE_ASPECT_16_9		//!< アスペクト比	16:9
} eDRV_IMAGE_ASPECT;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_LCD_MODE
 * @brief	LCDモード（YC出力／RGB出力／その他）
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_NOMAL_LCD = 0x1,			//!< 通常設定
	DRV_YC_LCD = 0x2,				//!< YC出力液晶設定
	DRV_RGB_LCD = 0x4,				//!< RGB出力液晶設定

	DRV_LCD_RESERVED
} eDRV_LCD_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_LCD_CLK_SEL
 * @brief	LCD用クロック周波数
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DRV_LCD_CLK_SEL_9M,				//!< 9MHz
	DRV_LCD_CLK_SEL_6M,				//!< 6.75MHz

	DRV_LCD_CLK_SEL_RESERVED
} eDRV_LCD_CLK_SEL;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_MONM_SEL
 * @brief	モニタメモコン選択
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DRV_MONM_SEL_MONL,				//!< LCD対応モニタメモコン
	DRV_MONM_SEL_MONT,				//!< TV対応モニタメモコン
	DRV_MONM_SEL_MONM_PRO,			//!< PRO対応モニタメモコン
	DRV_MONM_SEL_MONLT,				//!< LCD＆TV対応モニタメモコン

	DRV_MONM_SEL_RESERVED
} eDRV_MONM_SEL;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_VOU_PROFILE
 * @brief	表示サイズ・表示位置自動設定用プロファイル選択

 */
/*------------------------------------------------------------------------------*/
typedef enum {
	
	DRV_VOU_PROF_CINEMA_5994P_4K1K,					//!< フォーマット：4ｋ2ｋcimema(4k1k)、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_CINEMA_50P_4K1K,					//!< フォーマット：4ｋ2ｋcimema(4k1k)、フレーム周波数：50p
	DRV_VOU_PROF_2160P_5994P_4K1K,					//!< フォーマット：2160p(4k1k)、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_2160P_50P_4K1K,					//!< フォーマット：2160p(4k1k)、フレーム周波数：50p
	DRV_VOU_PROF_CINEMA_5994P_2K2K,					//!< フォーマット：4ｋ2ｋcimema(2k2k)、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_CINEMA_50P_2K2K,					//!< フォーマット：4ｋ2ｋcimema(2k2k)、フレーム周波数：50p
	DRV_VOU_PROF_2160P_5994P_2K2K,					//!< フォーマット：2160p(2k2k)、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_2160P_50P_2K2K,					//!< フォーマット：2160p(2k2k)、フレーム周波数：50p
	DRV_VOU_PROF_CINEMA_5994P_3GBPS,				//!< フォーマット：4ｋ2ｋcimema(3gbps)、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_CINEMA_50P_3GBPS,					//!< フォーマット：4ｋ2ｋcimema(3gbps)、フレーム周波数：50p
	DRV_VOU_PROF_2160P_5994P_3GBPS,					//!< フォーマット：2160p(3gbps)、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_2160P_50P_3GBPS,					//!< フォーマット：2160p(3gbps)、フレーム周波数：50p
	DRV_VOU_PROF_2160P_2997P,						//!< フォーマット：2160p、フレーム周波数：30p/29.97p
	DRV_VOU_PROF_2160P_25P,							//!< フォーマット：2160p、フレーム周波数：25p
	DRV_VOU_PROF_2160P_2398P,						//!< フォーマット：2160p、フレーム周波数：24p/23.98p
	DRV_VOU_PROF_2160P_24P_SMPTE,					//!< フォーマット：2160p(SMPTE)、フレーム周波数：24p
	DRV_VOU_PROF_UPCNV_720P_1080P_5994P,			//!< フォーマット：1080p、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_UPCNV_1080I_1080P_5994P,			//!< フォーマット：1080p、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_1080P_THR_5994P,					//!< フォーマット：1080p、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_UPCNV_720P_1080P_50P,				//!< フォーマット：1080p、フレーム周波数：50p
	DRV_VOU_PROF_UPCNV_1080I_1080P_50P,				//!< フォーマット：1080p、フレーム周波数：50p
	DRV_VOU_PROF_1080P_THR_50P,						//!< フォーマット：1080p、フレーム周波数：50p
	DRV_VOU_PROF_1080P_2398P,						//!< フォーマット：1080p、フレーム周波数：24p/23.98p
	DRV_VOU_PROF_DWCNV_1080P_1080I_5994I,			//!< フォーマット：1080i、フレーム周波数：59.94i/60i
	DRV_VOU_PROF_UPCNV_720P_1080I_5994I,			//!< フォーマット：1080i、フレーム周波数：59.94i/60i
	DRV_VOU_PROF_1080I_THR_5994I,					//!< フォーマット：1080i、フレーム周波数：59.94i/60i
	DRV_VOU_PROF_DWCNV_1080P_1080I_50I,				//!< フォーマット：1080i、フレーム周波数：50i
	DRV_VOU_PROF_UPCNV_720P_1080I_50I,				//!< フォーマット：1080i、フレーム周波数：50i
	DRV_VOU_PROF_1080I_THR_50I,						//!< フォーマット：1080i、フレーム周波数：50i
	DRV_VOU_PROF_DWCNV_1080P_720P_5994P,			//!< フォーマット：720p、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_DWCNV_1080I_720P_5994P,			//!< フォーマット：720p、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_720P_THR_5994P,						//!< フォーマット：720p、フレーム周波数：59.94p/60p 
	DRV_VOU_PROF_DWCNV_1080P_720P_50P,				//!< フォーマット：720p、フレーム周波数：50p
	DRV_VOU_PROF_DWCNV_1080I_720P_50P,				//!< フォーマット：720p、フレーム周波数：50p
	DRV_VOU_PROF_720P_THR_50P,						//!< フォーマット：720p、フレーム周波数：50p
	DRV_VOU_PROF_UPCNV_480I_480P_5994P,				//!< フォーマット：480p、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_480P_5994P,						//!< フォーマット：480p、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_UPCNV_576I_576P_50P,				//!< フォーマット：576p、フレーム周波数：50p
	DRV_VOU_PROF_576P_50P,							//!< フォーマット：576p、フレーム周波数：50p
	DRV_VOU_PROF_DWCNV_480P_480I_5994P,				//!< フォーマット：480i、フレーム周波数：59.94i/60i
	DRV_VOU_PROF_480I_THR_5994I,					//!< フォーマット：480i、フレーム周波数：59.94i/60i
	DRV_VOU_PROF_DWCNV_576P_576I_50I,				//!< フォーマット：576i、フレーム周波数：50i
	DRV_VOU_PROF_576I_THR_50I,						//!< フォーマット：576i、フレーム周波数：50i
	DRV_VOU_PROF_NTSC_5994I,						//!< フォーマット：NTSC、フレーム周波数：59.94i/60i
	DRV_VOU_PROF_PAL_50I,							//!< フォーマット：PAL、フレーム周波数：50i
	DRV_VOU_PROF_MANUAL,							//!< フォーマット：手動設定、フレーム周波数：任意 

	DRV_VOU_PROF_2160P_2997P_PRO,					//!< フォーマット：2160p、フレーム周波数：30p/29.97p
	DRV_VOU_PROF_2160P_25P_PRO,						//!< フォーマット：2160p、フレーム周波数：25p
	DRV_VOU_PROF_2160P_2398P_PRO,					//!< フォーマット：2160p、フレーム周波数：24p/23.98p
	DRV_VOU_PROF_2160P_24P_SMPTE_PRO,				//!< フォーマット：2160p(SMPTE)、フレーム周波数：24p
	DRV_VOU_PROF_1080P_5994P_PRO,					//!< フォーマット：1080p、フレーム周波数：50p
	DRV_VOU_PROF_1080P_50P_PRO,						//!< フォーマット：1080p、フレーム周波数：50p
	DRV_VOU_PROF_1080P_2398P_PRO,					//!< フォーマット：1080p、フレーム周波数：24p/23.98p
	DRV_VOU_PROF_1080I_5994I_PRO,					//!< フォーマット：1080i、フレーム周波数：59.94i/60i
	DRV_VOU_PROF_1080I_50I_PRO,						//!< フォーマット：1080i、フレーム周波数：50i
	DRV_VOU_PROF_1080I_48I_PRO,						//!< フォーマット：1080i、フレーム周波数：48i
	DRV_VOU_PROF_720P_5994P_PRO,					//!< フォーマット：720p、フレーム周波数：59.94p/60p 
	DRV_VOU_PROF_720P_50P_PRO,						//!< フォーマット：720p、フレーム周波数：50p
	DRV_VOU_PROF_720P_30P_PRO,						//!< フォーマット：720p、フレーム周波数：30p
	DRV_VOU_PROF_720P_25P_PRO,						//!< フォーマット：720p、フレーム周波数：25p
	DRV_VOU_PROF_720P_24P_PRO,						//!< フォーマット：720p、フレーム周波数：24p
	DRV_VOU_PROF_480P_5994P_PRO,					//!< フォーマット：480p、フレーム周波数：59.94p/60p
	DRV_VOU_PROF_576P_50P_PRO,						//!< フォーマット：576p、フレーム周波数：50p
	DRV_VOU_PROF_480I_5994I_PRO,					//!< フォーマット：480i、フレーム周波数：59.94i/60i
	DRV_VOU_PROF_576I_50I_PRO,						//!< フォーマット：576i、フレーム周波数：50i
	DRV_VOU_PROF_MANUAL_PRO,						//!< フォーマット：手動設定、フレーム周波数：任意 
	                                                                              
	DRV_VOU_PROF_RESERVED
} eDRV_VOU_PROFILE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PPU_CNT_RST_EDGE
 * @brief	ラインカウンタをリセットするタイミング（水平インターレース用）
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_PPU_RST_AT_NEGEDGE = 0,		//!< VD立下りでカウンタリセット
	DRV_PPU_RST_AT_POSEDGE = 1,		//!< VD立上がりでカウンタリセット

	DRV_PPU_RST_AT_RESERVED
} eDRV_PPU_CNT_RST_EDGE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PPU_HI21_WADR_INCMODE
 * @brief	2:1水平インターレース時のアドレス加算モード
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_PPU_HI21_WADR_INC1_3 = 0,		//!< 1or3加算
	DRV_PPU_HI21_WADR_INC2   = 1,		//!< 2加算

	DRV_PPU_HI21_WADR_INC2_RESERVED
} eDRV_PPU_HI21_WADR_INCMODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PPU_FAST_LINE_SEL
 * @brief	CCD系QMIX 高速モード時の出力ライン選択
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_PPU_ODD = 0,				//!< 偶数データを出力
	DRV_PPU_EVEN					//!< 奇数データを出力
} eDRV_PPU_FAST_LINE_SEL;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_READ_START_FIELD
 * @brief	取り込み開始field
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_READ_FIRST_RAW  	= 1,						/*!<  1Field目から取り込み	*/
	DRV_READ_SECOND_RAW 	= 2,						/*!<  2Field目から取り込み	*/
	DRV_READ_THIRD_RAW  	= 3,						/*!<  3Field目から取り込み	*/
	DRV_READ_FOURTH_RAW 	= 4,						/*!<  4Field目から取り込み	*/
	DRV_READ_FIFTH_RAW  	= 5,						/*!<  5Field目から取り込み	*/
	DRV_READ_SIXTH_RAW  	= 6,						/*!<  6Field目から取り込み	*/
	DRV_READ_SEVENTH_RAW  	= 7,						/*!<  7Field目から取り込み	*/
	DRV_READ_EIGHTH_RAW  	= 8,						/*!<  8Field目から取り込み	*/
	DRV_READ_NINTH_RAW  	= 9,						/*!<  9Field目から取り込み	*/
	DRV_READ_TENTH_RAW  	= 10,						/*!<  10Field目から取り込み	*/
	DRV_READ_ELEVENTH_RAW  	= 11,						/*!<  11Field目から取り込み	*/
	DRV_READ_TWELFTH_RAW  	= 12						/*!<  12Field目から取り込み	*/

} eDRV_READ_START_FIELD;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SSG_CCDVD_RESET_SEL
 * @brief	CCD系 VDHEADの周期リセットの選択
 */
/* -----------------------------------------------------------------------------*/
typedef	enum {
	DRV_SSG_CCD_RST = 0,			//!<  CCDVD リセット設定	*/
	DRV_SSG_NRST_VDH_EXT			//!<  CCDVD リセットしない	*/
} eDRV_SSG_CCDVD_RESET_SEL;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SSG_DIV_VD_SUB
 * @brief	CCD系 汎用センサモード時の外部VD分割設定
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_SSG_CLKDIV_NON = 0,				//!< 分割なし
	DRV_SSG_CLKDIV_4,					//!< 4分割
	DRV_SSG_CLKDIV_8,					//!< 8分割
	DRV_SSG_CLKDIV_16					//!< 16分割
} eDRV_SSG_DIV_VD_SUB;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_RESOURCE_ID
 * @brief	リソースID番号
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_RESOURCE_ID_CPU_DMAC0 = 0,	//!< CPU DMAC0		*/
	DRV_RESOURCE_ID_CPU_DMAC1,		//!< CPU DMAC1		*/
	DRV_RESOURCE_ID_STU_DMAC,		//!< STU DMAC		*/
	DRV_RESOURCE_ID_MEMIO,			//!< MEMIO DMA		*/
	DRV_RESOURCE_ID_TIMER32,		//!< TIMER32		*/
	DRV_RESOURCE_ID_ARM_TIMER,		//!< ARM TIMER		*/
	DRV_RESOURCE_ID_SSP,			//!< SSP			*/
	DRV_RESOURCE_ID_UART,			//!< UART			*/
	DRV_RESOURCE_ID_I2C,			//!< I2C			*/
	DRV_RESOURCE_ID_AD0,			//!< AD0			*/
	DRV_RESOURCE_ID_AD1,			//!< AD1			*/
	DRV_RESOURCE_ID_AD2,			//!< AD2			*/
	DRV_RESOURCE_ID_CDU,			//!< CDU			*/
	DRV_RESOURCE_ID_VOU_PIC1,		//!< VOU PIC1		*/
	DRV_RESOURCE_ID_VOU_PIC2,		//!< VOU PIC2		*/
	DRV_RESOURCE_ID_VOU_OSD1,		//!< VOU OSD1		*/
	DRV_RESOURCE_ID_VOU_OSD2,		//!< VOU OSD2		*/
	DRV_RESOURCE_ID_VOU_OSD3,		//!< VOU OSD3		*/
	DRV_RESOURCE_ID_VOU_GFX,		//!< VOU GFX		*/
	DRV_RESOURCE_ID_ADU,			//!< ADU			*/
	DRV_RESOURCE_ID_TCC,			//!< TCC			*/
	DRV_RESOURCE_ID_GENERAL,		//!< General		*/
	DRV_RESOURCE_ID_RESERVED
} eDRV_RESOURCE_ID;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_CMN_RESOURCE_STATE
 * @brief	リソース使用状況
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_CMN_RESOURCE_EMPTY = 0,
	DRV_CMN_RESOURCE_USED
} eDRV_CMN_RESOURCE_STATE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_CMN_EXCLUSION
 * @brief	排他制御管理用
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_CMN_EXCLUSION_RSRC = 0,			/* リソース管理用SRAM（ドライバ内部で使用） */
	DRV_CMN_EXCLUSION_TLB,				/* TLB（ドライバ内部で使用） */
	DRV_CMN_EXCLUSION_CKGEN,			/* CKG */
	DRV_CMN_EXCLUSION_GPIOU,			/* GPIO */
	DRV_CMN_EXCLUSION_OTHER,			/* 汎用 */
	DRV_CMN_EXCLUSION_RESERVED
} eDRV_CMN_EXCLUSION;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SELECT_MEMCON
 * @brief	メモコンのチャネル選択（CDU/SUBYCU）
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_MEMCON_CH_0 = 0,
	DRV_MEMCON_CH_1,
	DRV_MEMCON_CH_ALL
} eDRV_SELECT_MEMCON;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_DMAC_DMA_BLOCK
 * @brief	DMAブロック選択
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DRV_DMAC_MIU0 = 0x0,						//!< MIU DMAC0
	DRV_DMAC_MIU1,								//!< MIU DMAC1
	DRV_DMAC_STU,								//!< STU DMAC
	
	DRV_DMAC_BLOCK_RESERVED
}eDRV_DMAC_DMA_BLOCK;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_DMAC_DMA_CH
 * @brief	DMAチャネル選択
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DRV_DMAC_CH0 = 0x0,							//!< DMA CH0
	DRV_DMAC_CH1,								//!< DMA CH1
	DRV_DMAC_CH2,								//!< DMA CH2
	DRV_DMAC_CH3,								//!< DMA CH3
	DRV_DMAC_CH4,								//!< DMA CH4
	DRV_DMAC_CH5, 								//!< DMA CH5
	DRV_DMAC_CH6, 								//!< DMA CH6
	DRV_DMAC_CH7, 								//!< DMA CH7
	
	DRV_DMAC_CH_RESERVED
}eDRV_DMAC_DMA_CH;


/*********************************************************************************
	構造体宣言
*********************************************************************************/
/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_IMG_SIZE
 * @brief	H/V方向サイズ
 */
/* -----------------------------------------------------------------------------*/
typedef struct {
	ULONG ulHsize;			//!< H方向サイズ
	ULONG ulVsize;			//!< V方向サイズ
} sDRV_IMG_SIZE;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_IMG_POS
 * @brief	H/V方向位置
 */
/* -----------------------------------------------------------------------------*/
typedef struct {
	ULONG ulHpos;			//!< H方向位置
	ULONG ulVpos;			//!< V方向位置
} sDRV_IMG_POS;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_DISP_IMAGE
 * @brief	表示サイズ・表示開始位置設定
 */
/*------------------------------------------------------------------------------*/
typedef struct {
	sDRV_IMG_SIZE  	sAreaSize;			//!< 表示エリアサイズ
	ULONG			sStartPosH;			//!< 水平表示開始位置
	ULONG			sStartPosV;			//!< 垂直表示開始位置
	ULONG			sStartPosVEven;		//!< 垂直表示開始位置(EVEN)
} sDRV_DISP_IMAGE;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_CMN_RESOURCE
 * @brief	リソース対象選択用構造体
 */
/* -----------------------------------------------------------------------------*/
typedef	struct	{
	eDRV_RESOURCE_ID	eResourceId;				/*!< リソースID番号	*/
	UCHAR				ucResourceCh;				/*!< リソースCH番号	*/
}sDRV_CMN_RESOURCE;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_CMN_INIT_AGENT_SOCKET_DMAC
 * @brief	DMAC用TLB初期化構造体
 */
/* -----------------------------------------------------------------------------*/
typedef	struct	{
	eDRV_DMAC_DMA_BLOCK	eSelectBlock;					//!< ブロック選択（MIU0、MIU1とSTU）
	eDRV_DMAC_DMA_CH	eDmaCh;							//!< DMAチャネル選択
	UCHAR				*pucInstructionStartAddress;	//!< インストラクションアクセスのスタートアドレス
}sDRV_CMN_INIT_AGENT_SOCKET_DMAC;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_DMAC_USE_BURST_TRANS	
 * @brief	DMACでレジスタのバーストリードとライト用
 */
/* -----------------------------------------------------------------------------*/
typedef struct{
	eDRV_SWITCH			eDmaTransSw;					//!< DMACでレジスタリードSW
	eDRV_DMAC_DMA_BLOCK	eSelectBlock;					//!< ブロック選択（MIU0、MIU1とSTU）
	eDRV_DMAC_DMA_CH	eDmaCh;							//!< DMAチャネル選択
	UCHAR				ucMmuidNum;						//!< ARMからDMAへのアドレス変換用空間ID（0～7）
	UCHAR				*pucInstructionStartAddress;	//!< インストラクションアクセスのスタートアドレス
}sDRV_DMAC_USE_BURST_TRANS;


/*********************************************************************************
	プロトタイプ宣言
*********************************************************************************/
eDRV_ERR	eLdCMN_GetEmptyResource(sDRV_CMN_RESOURCE *psResource);
eDRV_ERR	eLdCMN_ReleaseResource(sDRV_CMN_RESOURCE *psResource);
eDRV_ERR	eLdCMN_ReferenceResource(eDRV_RESOURCE_ID eResourceId,void *psRefResource);
eDRV_ERR	eLdCMN_InitializeResource(void);
void DRV_CMN_INIT_AGENT_SOCKET(eDRV_CMN_AGENT_SOCKET AGENT);
void DRV_CMN_INIT_AGENT_SOCKET_DMAC(sDRV_CMN_INIT_AGENT_SOCKET_DMAC *);
void DRV_CMN_CHANGE_AGENT_DRAM(eDRV_CMN_AGENT_GROUP, ULONG, ULONG);

#endif	/* __EXT_DRV_CMN_H__ */
