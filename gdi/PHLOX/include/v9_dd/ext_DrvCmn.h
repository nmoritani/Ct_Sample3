/********************************************************************************/
/*!
 * @file	ext_DrvCmn.h
 *
 * @brief	�h���C�o���� �O�����J�w�b�_
 *
 * @author	�p�i�\�j�b�N�i���j
 *
 * @date	2007/11/12	�V�K�쐬
 *
 * Copyright(c) Panasonic Co.,Ltd.		http://panasonic.jp/
 * <HR>
 ********************************************************************************/
#ifndef __EXT_DRV_CMN_H__
#define __EXT_DRV_CMN_H__

/*********************************************************************************
	�C���N���[�h�t�@�C��
*********************************************************************************/
#if 0
/* SC�Ўg�p���y�у����[�X����1��ݒ�AAVC�Зl�ɂĒl��0�ɕύX���Ďg�p���� */
#include 	<stdio.h>
#include 	<string.h>
#include 	<stdarg.h>
#endif

#include	"ext_DrvDef.h"

/*********************************************************************************
	�}�N����`
*********************************************************************************/


/*********************************************************************************
	���[�U�[��`�̈�@�J�n
*********************************************************************************/

/*------------------------------------------------------------------------------*/
/*!
 * @def		unDRV_CMN_LOCK_REG
 * @brief	LOCK_REG�A�N�Z�X�p
 *			�h���C�o�����l��0xXXXXXXXX�ɐݒ肵�܂��B
 */
/* -----------------------------------------------------------------------------*/
#define		unDRV_CMN_LOCK_REG	0x93E0001F

/*------------------------------------------------------------------------------*/
/*!
 * @def		unDRV_CMN_SRAM_ADDR
 * @brief	SRAM�A�h���X
 *			�h���C�o�����l��0xXXXXXXXX�ɐݒ肵�܂��B
 */
/* -----------------------------------------------------------------------------*/
#define		DRV_CMN_SRAM_ADDR	0x93F01F80

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_MMU_MODE_ON
 * @brief	MMU ON/OFF
 *			MMU ON�Ȃ�1�AOFF�Ȃ�0�ɐݒ�
 */
/* -----------------------------------------------------------------------------*/
#define DRV_CMN_MMU_MODE_ON	1


/*********************************************************************************
	���[�U�[��`�̈�@�I��
*********************************************************************************/

/*------------------------------------------------------------------------------*/
/*!
 * @def		unDRV_CMN_SRAM_ADDR
 * @brief	SSC��SRAM�A�h���X
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
 * @def		 CPU�Ԕr�����䎞�̃R�q�[�����V�ێ��p
 * @brief	 �O���[�o���ϐ������static�ϐ��̑O��ɃI�t�Z�b�g��}��
 */
/*------------------------------------------------------------------------------*/
#define		DUMMY_DATA_SIZE		64


/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_ENABLE_IRQ_VALID
 * @brief	�h���C�o���ł̊��荞�݋֎~�^���̗L�������̐؂�ւ��X�C�b�`
 */
/* -----------------------------------------------------------------------------*/
#define		DRV_ENABLE_IRQ_VALID


/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_ENTER_CRITICAL
 * @brief	�N���e�B�J���Z�N�V�����J�n
 * @param	
 */
/*------------------------------------------------------------------------------*/
#define DRV_CMN_ENTER_CRITICAL

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_EXIT_CRITICAL
 * @brief	�N���e�B�J���Z�N�V�����I��
 * @param	
 */
/*------------------------------------------------------------------------------*/
#define DRV_CMN_EXIT_CRITICAL

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_CMN_AGENT_SOCKET
 * @brief	Agent socket�w��p�����[�^
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_CMN_AGENT_SOCKET_PPM			= 0x10100000,	//!< PPMW0�APPMW1�APPMWBMW�APPMWBMR�APPMBR�APPMXR��TLB������
	DRV_CMN_AGENT_SOCKET_PPM_DW			= 0x10100002,	//!< PPMDW0�APPMDW1��TLB������
	DRV_CMN_AGENT_SOCKET_PPM_BMW		= 0x10100004,	//!< PPMBMW��TLB������
	DRV_CMN_AGENT_SOCKET_YCMR_FG		= 0x100A0009,	//!< YCMR0 FG��TLB������	"A"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_YCMR_BG		= 0x100B0009,	//!< YCMR0 BG��TLB������	"B"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_YCMR_ALL		= 0x10100009,	//!< YCMR0��TLB������
	DRV_CMN_AGENT_SOCKET_YCMR_FG_1		= 0x100A000A,	//!< YCMR1 FG��TLB������	"A"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_YCMR_BG_1		= 0x100B000A,	//!< YCMR1 BG��TLB������	"B"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_YCMR_ALL_1		= 0x1010000A,	//!< YCMR1��TLB������
	DRV_CMN_AGENT_SOCKET_YCMR_FG_2		= 0x1000000B,	//!< YCMR2 FG��TLB������
	DRV_CMN_AGENT_SOCKET_YCMR_BG_2		= 0x1001000B,	//!< YCMR2 BG��TLB������
	DRV_CMN_AGENT_SOCKET_YCMR_ALL_2		= 0x1010000B,	//!< YCMR2��TLB������
	DRV_CMN_AGENT_SOCKET_YCMR_FG_3		= 0x1000000C,	//!< YCMR3 FG��TLB������
	DRV_CMN_AGENT_SOCKET_YCMR_BG_3		= 0x1001000C,	//!< YCMR3 BG��TLB������
	DRV_CMN_AGENT_SOCKET_YCMR_ALL_3		= 0x1010000C,	//!< YCMR3��TLB������
	DRV_CMN_AGENT_SOCKET_YCMW_FG		= 0x100A000D,	//!< YCMW0 FG��TLB������	"A"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_YCMW_BG		= 0x100B000D,	//!< YCMW0 FG��TLB������	"B"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_YCMW_ALL		= 0x1010000D,	//!< YCMW0��TLB������
	DRV_CMN_AGENT_SOCKET_YCMW_FG_1		= 0x100A000E,	//!< YCMW1 FG��TLB������	"A"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_YCMW_BG_1		= 0x100B000E,	//!< YCMW1 BG��TLB������	"B"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_YCMW_ALL_1		= 0x1010000E,	//!< YCMW1��TLB������
	DRV_CMN_AGENT_SOCKET_YCMW_FG_2		= 0x1000000F,	//!< YCMW2 FG��TLB������
	DRV_CMN_AGENT_SOCKET_YCMW_BG_2		= 0x1001000F,	//!< YCMW2 BG��TLB������
	DRV_CMN_AGENT_SOCKET_YCMW_ALL_2		= 0x1010000F,	//!< YCMW2��TLB������
	DRV_CMN_AGENT_SOCKET_YCMW_FG_3		= 0x10000010,	//!< YCMW3 FG��TLB������
	DRV_CMN_AGENT_SOCKET_YCMW_BG_3		= 0x10010010,	//!< YCMW3 BG��TLB������
	DRV_CMN_AGENT_SOCKET_YCMW_ALL_3		= 0x10100010,	//!< YCMW3��TLB������
	DRV_CMN_AGENT_SOCKET_MONL			= 0x10100011,	//!< MONL0�AMONL1��TLB������
	DRV_CMN_AGENT_SOCKET_MONT0			= 0x10100013,	//!< MONT0��TLB������
	DRV_CMN_AGENT_SOCKET_MONT1			= 0x10100014,	//!< MONT1��TLB������
	DRV_CMN_AGENT_SOCKET_MONM_PRO		= 0x10100015,	//!< MONT2��TLB������
	DRV_CMN_AGENT_SOCKET_MON			= 0x100A0013,	//!< MONL0�AMONT0�AMONL1�AMONT1�AMONT2��TLB������	"A"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_MONW			= 0x10100016,	//!< MONW��TLB������
	DRV_CMN_AGENT_SOCKET_TCCR_STREAM	= 0x10000017,	//!< TCCR STREAM-Read��TLB������
	DRV_CMN_AGENT_SOCKET_TCCR_Y			= 0x10010017,	//!< TCCR Y-Read��TLB������
	DRV_CMN_AGENT_SOCKET_TCCR_C			= 0x10020017,	//!< TCCR C-Read��TLB������
	DRV_CMN_AGENT_SOCKET_TCCW_STREAM	= 0x10000018,	//!< TCCW STREAM-Read��TLB������
	DRV_CMN_AGENT_SOCKET_TCCW_Y			= 0x10010018,	//!< TCCW Y-Read��TLB������
	DRV_CMN_AGENT_SOCKET_TCCW_C			= 0x10020018,	//!< TCCW C-Read��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR0			= 0x10100019,	//!< FRMR0��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR1			= 0x1010001A,	//!< FRMR1��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR2_TNR_PREY	= 0x1000001B,	//!< FRMR2 TNR�pPre��Y��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR2_TNR_PREC	= 0x1001001B,	//!< FRMR2 TNR�pPre��C��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR3			= 0x1010001C,	//!< FRMR3��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR4_HDR_PREY	= 0x1000001D,	//!< FRMR4 HDR�pPre��Y��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR4_HDR_PREC	= 0x1001001D,	//!< FRMR4 HDR�pPre��C��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR5			= 0x1010001E,	//!< FRMR5��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR6			= 0x1010001F,	//!< FRMR6��TLB������
	DRV_CMN_AGENT_SOCKET_FRMR7			= 0x20100000,	//!< FRMR7��TLB������
	DRV_CMN_AGENT_SOCKET_FRMW0_TNR_Y	= 0x20000001,	//!< FRMW0 TNR��͉�Y��TLB������
	DRV_CMN_AGENT_SOCKET_FRMW0_TNR_C	= 0x20010001,	//!< FRMW0 TNR��͉�C��TLB������
	DRV_CMN_AGENT_SOCKET_FRMW1			= 0x20100002,	//!< FRMW1��TLB������
	DRV_CMN_AGENT_SOCKET_FRMW2_Y		= 0x20000003,	//!< FRMW2 FUR���1��Y��TLB������
	DRV_CMN_AGENT_SOCKET_FRMW2_C		= 0x20010003,	//!< FRMW2 FRU���1��C��TLB������
	DRV_CMN_AGENT_SOCKET_FRMW3_Y		= 0x20000004,	//!< FRMW3 FRU���2��Y��TLB������
	DRV_CMN_AGENT_SOCKET_FRMW3_C		= 0x20010004,	//!< FRMW3 FRU���2��C��TLB������
	DRV_CMN_AGENT_SOCKET_JPM			= 0x20100005,	//!< CODER0�ACODER1�ACODEW�AIMGCR0�AIMGYR0�AIMGCW0�AIMGYW0��TLB������
	DRV_CMN_AGENT_SOCKET_BACD			= 0x20100008,	//!< BACDR�ABACDW��TLB������
	DRV_CMN_AGENT_SOCKET_JPM_1			= 0x2010000E,	//!< CODER0_1�ACODER1_1�ACODEW_1�AIMGCR1�AIMGYR1�AIMGCW1�AIMGYW1��TLB������
	DRV_CMN_AGENT_SOCKET_BACD_1			= 0x20100011,	//!< BACDR�ABACDW��TLB������
	DRV_CMN_AGENT_SOCKET_SYCUR0			= 0x20100017,	//!< SUBYCU 0 read��TLB������
	DRV_CMN_AGENT_SOCKET_SYCUR1			= 0x20100018,	//!< SUBYCU 1 read��TLB������
	DRV_CMN_AGENT_SOCKET_SYCUW0			= 0x20100019,	//!< SUBYCU 0 write ��TLB������
	DRV_CMN_AGENT_SOCKET_SYCUW1			= 0x2010001A,	//!< SUBYCU 1 write ��TLB������
	DRV_CMN_AGENT_SOCKET_SYCU_ALL		= 0x200A0017,	//!< SUBYCU��TLB������	"A"�͎��ʗp�}�W�b�N�i���o
	DRV_CMN_AGENT_SOCKET_SDC			= 0x2010001B,	//!< SDC0��TLB������
	DRV_CMN_AGENT_SOCKET_SDC_1			= 0x2010001D,	//!< SDC1��TLB������
	DRV_CMN_AGENT_SOCKET_SDC_2			= 0x2010001F,	//!< SDC2��TLB������
	DRV_CMN_AGENT_SOCKET_SDC_3			= 0x30100001,	//!< SDC3��TLB������
	DRV_CMN_AGENT_SOCKET_USBR			= 0x30100003,	//!< USB Read��TLB������
	DRV_CMN_AGENT_SOCKET_USBW			= 0x30100004,	//!< USB Write��TLB������
	DRV_CMN_AGENT_SOCKET_MEMIOR			= 0x30100005,	//!< MEMIO Read��TLB������
	DRV_CMN_AGENT_SOCKET_MEMIOW			= 0x30100006,	//!< MEMIO Write��TLB������
	DRV_CMN_AGENT_SOCKET_ETHR			= 0x30100007,	//!< ETH Read��TLB������
	DRV_CMN_AGENT_SOCKET_ETHW			= 0x30100008,	//!< ETH Write��TLB������
	DRV_CMN_AGENT_SOCKET_ODUR			= 0x30100009,	//!< ODU Read��TLB������
	DRV_CMN_AGENT_SOCKET_ODUW			= 0x3010000A,	//!< ODU Write��TLB������
	DRV_CMN_AGENT_SOCKET_AVMDR			= 0x3010000B,	//!< AVMD Read��TLB������
	DRV_CMN_AGENT_SOCKET_AVMDW			= 0x3010000C,	//!< AVMD Write��TLB������
	DRV_CMN_AGENT_SOCKET_GEVGR			= 0x3010000D,	//!< GEVG Read��TLB������
	DRV_CMN_AGENT_SOCKET_GEVGW			= 0x3010000E,	//!< GEVG Write��TLB������
	DRV_CMN_AGENT_SOCKET_ADUR_MON		= 0x30000010,	//!< ADU���j�^�Đ��p�f�[�^Read��TLB������
	DRV_CMN_AGENT_SOCKET_ADUR_HDMI		= 0x30010010,	//!< ADUHDMI�Đ��p�f�[�^Read��TLB������
	DRV_CMN_AGENT_SOCKET_ADUR_CLIP		= 0x30020010,	//!< ADU�N���b�v���Đ��p�f�[�^Read��TLB������
	DRV_CMN_AGENT_SOCKET_ADUW			= 0x30100011,	//!< ADU Write��TLB������
	DRV_CMN_AGENT_SOCKET_APU0			= 0x30100012,	//!< APU0��TLB������
	DRV_CMN_AGENT_SOCKET_APU1			= 0x30100013,	//!< APU1��TLB������
	DRV_CMN_AGENT_SOCKET_ARMR			= 0x30100014,	//!< ARM_ACE Read��TLB������
	DRV_CMN_AGENT_SOCKET_ARMW			= 0x30100015,	//!< ARM_ACE Write��TLB������
	DRV_CMN_AGENT_SOCKET_DMA0R			= 0x30100016,	//!< ARM_DMAC 0 Read��TLB������
	DRV_CMN_AGENT_SOCKET_DMA0W			= 0x30100017,	//!< ARM_DMAC 0 Write��TLB������
	DRV_CMN_AGENT_SOCKET_DMA1R			= 0x30100018,	//!< ARM_DMAC 1 Read��TLB������
	DRV_CMN_AGENT_SOCKET_DMA1W			= 0x30100019,	//!< ARM_DMAC 1 Write��TLB������
	DRV_CMN_AGENT_SOCKET_STDMAR			= 0x3010001A,	//!< STU_DMAC Read��TLB������
	DRV_CMN_AGENT_SOCKET_STDMAW			= 0x3010001B,	//!< STU_DMAC Write��TLB������
	DRV_CMN_AGENT_SOCKET_JPR			= 0x3010001C,	//!< JPU Read��TLB������
	DRV_CMN_AGENT_SOCKET_JPW			= 0x3010001D	//!< JPU Write��TLB������

} eDRV_CMN_AGENT_SOCKET;

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_AGENT_DRAM_CHANGE_***
 * @brief	DRAM�؂�ւ��p��` (DRV_CMN_CHANGE_AGENT_DRAM�Ŏg�p)
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
 * @brief	Agent�O���[�v�I��
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
 * @defgroup 	DRV_CHK_ERR		�h���C�o�G���[�����X�C�b�`(cond.mk��)
 * @{
 */
/* -----------------------------------------------------------------------------*/
#ifdef	DRV_ENABLE_CHK_ERR
#define	DRV_CMN_ENABLE_CHK_ERR		ON		//!< CMN�u���b�N�G���[����
#define	DRV_ADC_ENABLE_CHK_ERR		ON		//!< ADC�u���b�N�G���[����
#define	DRV_ADU_ENABLE_CHK_ERR		ON		//!< ADU�u���b�N�G���[����
#define	DRV_CDU_ENABLE_CHK_ERR		ON		//!< CDU�u���b�N�G���[����
#define	DRV_CKGEN_ENABLE_CHK_ERR	ON		//!< CKGEN�u���b�N�G���[����
#define	DRV_CPUTOP_ENABLE_CHK_ERR	ON		//!< CPUTOP�u���b�N�G���[����
#define	DRV_DAC_ENABLE_CHK_ERR		ON		//!< DAC�u���b�N�G���[����
#define	DRV_DIS_ENABLE_CHK_ERR		ON		//!< DIS�u���b�N�G���[����
#define	DRV_DTC_ENABLE_CHK_ERR		ON		//!< DTC�u���b�N�G���[����
#define	DRV_EBC_ENABLE_CHK_ERR		ON		//!< EBC�u���b�N�G���[����
#define	DRV_ENC_ENABLE_CHK_ERR		ON		//!< ENC�u���b�N�G���[����
#define	DRV_EXTDMA_ENABLE_CHK_ERR	ON		//!< EXTDMA�u���b�N�G���[����
#define	DRV_GDC_ENABLE_CHK_ERR		ON		//!< GDC�u���b�N�G���[����
#define	DRV_GPIOU_ENABLE_CHK_ERR	ON		//!< GPIOU�u���b�N�G���[����
#define	DRV_HSF_ENABLE_CHK_ERR		ON		//!< HSF�u���b�N�G���[����
#define	DRV_HSZ_ENABLE_CHK_ERR		ON		//!< HSZ�u���b�N�G���[����
#define	DRV_HIST_ENABLE_CHK_ERR		ON		//!< HIST�u���b�N�G���[����
#define	DRV_IRS_ENABLE_CHK_ERR		ON		//!< IRS�u���b�N�G���[����
#define	DRV_LIN_ENABLE_CHK_ERR		ON		//!< LIN�u���b�N�G���[����
#define	DRV_LCDIF_ENABLE_CHK_ERR	ON		//!< LCDIF�u���b�N�G���[����
#define	DRV_MEIFU_ENABLE_CHK_ERR	ON		//!< MEIFU�u���b�N�G���[����
#define	DRV_MEMIO_ENABLE_CHK_ERR	ON		//!< MEMIO�u���b�N�G���[����
#define	DRV_MMU_ENABLE_CHK_ERR		ON		//!< MMU�u���b�N�G���[����
#define	DRV_MONM_ENABLE_CHK_ERR		ON		//!< MONM�u���b�N�G���[����
#define	DRV_MTX_ENABLE_CHK_ERR		ON		//!< MTX�u���b�N�G���[����
#define	DRV_OIS_ENABLE_CHK_ERR		ON		//!< OIS�u���b�N�G���[����
#define	DRV_PID_ENABLE_CHK_ERR		ON		//!< PID�u���b�N�G���[����
#define	DRV_PPU_ENABLE_CHK_ERR		ON		//!< PPU�u���b�N�G���[����
#define	DRV_SERIAL_ENABLE_CHK_ERR	ON		//!< SERIAL�u���b�N�G���[����
#define	DRV_SSG_ENABLE_CHK_ERR		ON		//!< SSG�u���b�N�G���[����
#define	DRV_TIMER_ENABLE_CHK_ERR	ON		//!< TIMER�u���b�N�G���[����
#define	DRV_USBIFU_ENABLE_CHK_ERR	ON		//!< USBIFU�u���b�N�G���[����
#define	DRV_XMC_ENABLE_CHK_ERR		ON		//!< XMC�u���b�N�G���[����
#define	DRV_YCU_ENABLE_CHK_ERR		ON		//!< YCU�u���b�N�G���[����
#define	DRV_NRU_ENABLE_CHK_ERR		ON		//!< NRU�u���b�N�G���[����
#else
#define	DRV_CMN_ENABLE_CHK_ERR		OFF		//!< CMN�u���b�N�G���[����
#define	DRV_ADC_ENABLE_CHK_ERR		OFF		//!< ADC�u���b�N�G���[����
#define	DRV_ADU_ENABLE_CHK_ERR		OFF		//!< ADU�u���b�N�G���[����
#define	DRV_CDU_ENABLE_CHK_ERR		OFF		//!< CDU�u���b�N�G���[����
#define	DRV_CKGEN_ENABLE_CHK_ERR	OFF		//!< CKGEN�u���b�N�G���[����
#define	DRV_CPUTOP_ENABLE_CHK_ERR	OFF		//!< CPUTOP�u���b�N�G���[����
#define	DRV_DAC_ENABLE_CHK_ERR		OFF		//!< DAC�u���b�N�G���[����
#define	DRV_DIS_ENABLE_CHK_ERR		OFF		//!< DIS�u���b�N�G���[����
#define	DRV_DTC_ENABLE_CHK_ERR		OFF		//!< DTC�u���b�N�G���[����
#define	DRV_EBC_ENABLE_CHK_ERR		OFF		//!< EBC�u���b�N�G���[����
#define	DRV_ENC_ENABLE_CHK_ERR		OFF		//!< ENC�u���b�N�G���[����
#define	DRV_EXTDMA_ENABLE_CHK_ERR	OFF		//!< EXTDMA�u���b�N�G���[����
#define	DRV_GDC_ENABLE_CHK_ERR		OFF		//!< GDC�u���b�N�G���[����
#define	DRV_GPIOU_ENABLE_CHK_ERR	OFF		//!< GPIOU�u���b�N�G���[����
#define	DRV_HSF_ENABLE_CHK_ERR		OFF		//!< HSF�u���b�N�G���[����
#define	DRV_HSZ_ENABLE_CHK_ERR		OFF		//!< HSZ�u���b�N�G���[����
#define	DRV_HIST_ENABLE_CHK_ERR		OFF		//!< HIST�u���b�N�G���[����
#define	DRV_IRS_ENABLE_CHK_ERR		OFF		//!< IRS�u���b�N�G���[����
#define	DRV_LIN_ENABLE_CHK_ERR		OFF		//!< LIN�u���b�N�G���[����
#define	DRV_LCDIF_ENABLE_CHK_ERR	OFF		//!< LCDIF�u���b�N�G���[����
#define	DRV_MEIFU_ENABLE_CHK_ERR	OFF		//!< MEIFU�u���b�N�G���[����
#define	DRV_MEMIO_ENABLE_CHK_ERR	OFF		//!< MEMIO�u���b�N�G���[����
#define	DRV_MMU_ENABLE_CHK_ERR		OFF		//!< MMU�u���b�N�G���[����
#define	DRV_MONM_ENABLE_CHK_ERR		OFF		//!< MONM�u���b�N�G���[����
#define	DRV_MTX_ENABLE_CHK_ERR		OFF		//!< MTX�u���b�N�G���[����
#define	DRV_OIS_ENABLE_CHK_ERR		OFF		//!< OIS�u���b�N�G���[����
#define	DRV_PID_ENABLE_CHK_ERR		OFF		//!< PID�u���b�N�G���[����
#define	DRV_PPU_ENABLE_CHK_ERR		OFF		//!< PPU�u���b�N�G���[����
#define	DRV_SERIAL_ENABLE_CHK_ERR	OFF		//!< SERIAL�u���b�N�G���[����
#define	DRV_SSG_ENABLE_CHK_ERR		OFF		//!< SSG�u���b�N�G���[����
#define	DRV_TIMER_ENABLE_CHK_ERR	OFF		//!< TIMER�u���b�N�G���[����
#define	DRV_USBIFU_ENABLE_CHK_ERR	OFF		//!< USBIFU�u���b�N�G���[����
#define	DRV_XMC_ENABLE_CHK_ERR		OFF		//!< XMC�u���b�N�G���[����
#define	DRV_YCU_ENABLE_CHK_ERR		OFF		//!< YCU�u���b�N�G���[����
#define	DRV_NRU_ENABLE_CHK_ERR		OFF		//!< NRU�u���b�N�G���[����
#endif
/*! @} -------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*!
 * @defgroup 	DRV_MMU_CLEAR	MMU�\�P�b�g�N���A���s���ꍇ�̊��荞�݋֎~�^����(cond.mk��)
 * @{
 */
/* -----------------------------------------------------------------------------*/
#ifdef	DRV_ENABLE_IRQ_MMU_CLEAR
	#define	DRV_PPM_IRQ_MMU_CLEAR	ON		//!< PPM�u���b�N
	#define	DRV_MON_IRQ_MMU_CLEAR	ON		//!< MON�u���b�N
	#define	DRV_MIF_IRQ_MMU_CLEAR	ON		//!< MIF�u���b�N
	#define	DRV_DMA_IRQ_MMU_CLEAR	ON		//!< DMA�u���b�N
	#define	DRV_YCM_IRQ_MMU_CLEAR	ON		//!< YCM�u���b�N
	#define	DRV_JPM_IRQ_MMU_CLEAR	ON		//!< JPM�u���b�N
#else
	#define	DRV_PPM_IRQ_MMU_CLEAR	OFF		//!< PPM�u���b�N
	#define	DRV_MON_IRQ_MMU_CLEAR	OFF		//!< MON�u���b�N
	#define	DRV_MIF_IRQ_MMU_CLEAR	OFF		//!< MIF�u���b�N
	#define	DRV_DMA_IRQ_MMU_CLEAR	OFF		//!< DMA�u���b�N
	#define	DRV_YCM_IRQ_MMU_CLEAR	OFF		//!< YCM�u���b�N
	#define	DRV_JPM_IRQ_MMU_CLEAR	OFF		//!< JPM�u���b�N
#endif
/*! @} -------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*!
 * @defgroup 	VIDEO_BLK_END	VIDEO�n�u�����L���O�I���ʒu
 * @{
 */
/* -----------------------------------------------------------------------------*/
#define	NTSC_VIDEO_HBLK_END			293		//!< VIDEO�n���������u�����L���O�I���ʒu(NTSC)
#define	PAL_VIDEO_HBLK_END			323		//!< VIDEO�n���������u�����L���O�I���ʒu(PAL)	
#define	NTSC_VIDEO_VBLK_END			 33		//!< VIDEO�n���������u�����L���O�I���ʒu(NTSC)
#define	PAL_VIDEO_VBLK_END			 45		//!< VIDEO�n���������u�����L���O�I���ʒu(PAL)	
/*! @} -------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*!
 * @defgroup 	DRV_FAF_SW		����AF�Ή�
 * @{
 */
/* -----------------------------------------------------------------------------*/
#define DRV_CMN_FAF_GET_MODE(MODE)	((MODE) & 0xf000)	//!< ����AF���[�h�擾
#define DRV_CMN_FAF_MODE060			0x0000 				//!< ����AF (60fps)
#define DRV_CMN_FAF_MODE120			0x1000 				//!< ����AF (120fps)
#define DRV_SSG_FAF_VD_MAXCNT		0x01   				//!< CCD�n���������M������
#define DRV_SSG_FAF_VD_BLK_WIDTH	0x02				//!< CCD�n���������M���u�����L���O��
#define DRV_SSG_FAF_LAST_HDHEAD		0x04				//!< CCD�n���������M���ŏIHDHEAD��CLK��
#define DRV_PP1_FAF_CCDW_START_VPOS	0x08				//!< �捞�݊J�n�ʒu
#define DRV_PP1_FAF_CCDW_STOP_VPOS	0x10				//!< �捞�ݏI���ʒu
#define DRV_YCM_FAF_FG_CCDR_LIMITV	0x20				//!< �ǂݍ��ݐ�����f��
#define DRV_MONM_FAF_VMAX_PIC		0x40 				//!< �ǂݏo�����C����
#define DRV_MONM_FAF_VPOS_PIC		0x80 				//!< �ǂݏo���J�n�ʒu
/*! @} -------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------*/
/*!
 * @defgroup	VIDEO_SYNC_DLY			Video�n���������M���ʑ�����
 *
 *	<b>�����ʑ� ���������F</b>
 *		- CASIO��LCD�F(6n+5)�̒l���`���Ă��������B
 *		- SANYO��LCD�FLCD�̎d�l�ɍ��킹�Ă��������B(�����l�F0x5D)	<BR>
 *			�i�ȍ~�A::eLdVOU_SetPictureSourc�֐��̐��������J�n�ʒu�ɂ���ĕϓ��B�j
 * @{
 */
/*------------------------------------------------------------------------------*/
#define	VIDEO_SYNC_H	0x2F					//!< ���������M�� �����ʑ�����
#define	VIDEO_SYNC_V	0x00					//!< ���������M�� �����ʑ�����
/*! @} -------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_BYTE_PER_PAGE
 * @brief	 �V�X�e���̓]���P�ʂ��K��
 */
/*------------------------------------------------------------------------------*/
#define DRV_BYTE_PER_PAGE		64

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_BYTE_PER_SPREAD
 * @brief	 �P�X�v���b�h������̃o�C�g��
 */
/*------------------------------------------------------------------------------*/
#define DRV_BYTE_PER_SPREAD		32

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_BYTE_PER_WSPREAD
 * @brief	 �Q�X�v���b�h������̃o�C�g��
 */
/*------------------------------------------------------------------------------*/
#define DRV_BYTE_PER_WSPREAD		64

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_DIV_ROUNDUP
 * @brief	 ����Z�i�؂�グ�j
 */
/*------------------------------------------------------------------------------*/
#define DRV_DIV_ROUNDUP(a, b)		(((a) + (b) - 1) / (b))

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_DIV_ROUNDUP_MINUS
 * @brief	 ����Z�i�؂�グ�j�����Ή�
 */
/*------------------------------------------------------------------------------*/
#define DRV_DIV_ROUNDUP_MINUS(a, b)		\
	((a > 0) ? (((a) + (b) - 1) / (b)) : ((-1) * ((((-1) * a) + (b) - 1) / (b))))

/*------------------------------------------------------------------------------*/
/*!
 * @def		 DRV_GET_ALIGN
 * @brief	 �A���C�����g
 */
/*------------------------------------------------------------------------------*/
#define	DRV_GET_ALIGN(VAL, ALIGN)		(DRV_DIV_ROUNDUP((VAL), (ALIGN)) * (ALIGN))

/*------------------------------------------------------------------------------*/
/*!
 * @def		GET_FAST_PAGE_PADDING			
 * @brief	���C���I�t�Z�b�g(4N+2)�␳��̐�����f��
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
 * @brief	�r������p�Z�}�t�H��ON
 */
/*------------------------------------------------------------------------------*/
#define	DRV_CMN_LOCK_REG_ON

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_CMN_LOCK_REG_OFF
 * @brief	�r������p�Z�}�t�H��OFF
 */
/*------------------------------------------------------------------------------*/
#define	DRV_CMN_LOCK_REG_OFF

/*------------------------------------------------------------------------------*/
/*!
 * @def		DRV_RESOURCE_CH_xxx
* @brief	���\�[�X�Ǘ��p�@���\�[�XCH��
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
 * @brief	�h���C�oID
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
 * @brief	�h���C�o�G���[�R�[�h
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	/* CMN */
	DRV_ERR_CMN_HARDWARE_CONFLICT = 0,		/*!< CMN	: �n�[�h�E�F�A�Փ�			*/
	DRV_ERR_CMN_HARDWARE_NORESOURCE,		/*!< CMN	: �n�[�h�E�F�A���\�[�X�Ȃ�	*/
	DRV_ERR_CMN_INIT_OK,					/*!< CMN	: ����I��					*/
	DRV_ERR_CMN_FAF_OK,						/*!< CMN	: ����AF����ݒ�			*/
	DRV_ERR_CMN_RESOURCE_OK,				/*!< CMN	: ���\�[�X�Ǘ� ����I��		*/
	DRV_ERR_CMN_RESOURCE_ALLREADY_GOT,		/*!< CMN	: ���\�[�X�Ǘ� �w��`���l���g�p��	*/
	DRV_ERR_CMN_RESOURCE_ALLREADY_RELEASED,	/*!< CMN	: ���\�[�X�Ǘ� �w��`���l������ς�	*/
	/* ADC */
	DRV_ERR_ADC_OK = DRV_ID_ADC * 100,		/*!< ADC	: ����I��					*/
	DRV_ERR_ADC_RUN,						/*!< ADC	: A/D�ϊ���					*/
	DRV_ERR_ADC_STOP,						/*!< ADC	: A/D�ϊ���~��				*/
	DRV_ERR_ADC_PAUSE,						/*!< ADC	: A/D�ϊ��ҋ@��				*/
	DRV_ERR_ADC_PRM,						/*!< ADC	: �p�����[�^�G���[			*/
	DRV_ERR_ADC_UNDER_CONVERSION,			/*!< ADC	: �ϊ����G���[	 			*/
	DRV_ERR_ADC_NOT_CONVERSION,				/*!< ADC	: ���ϊ��G���[				*/
	DRV_ERR_ADC_NOT_SET,					/*!< ADC	: �ݒ�G���[				*/
	DRV_ERR_ADC_POWDN,						/*!< ADC	: �p���[�_�E���G���[		*/
	DRV_ERR_ADC_OTHER,						/*!< ADC	: ���̑��̃G���[			*/
	/* ADU */
	DRV_ERR_ADU_OK = DRV_ID_ADU * 100, 		/*!< ADU	: ����I�� 					*/
	DRV_ERR_ADU_HWERROR, 					/*!< ADU	: ADU�n�[�h�E�F�A�G���[ 	*/
	DRV_ERR_ADU_PRM, 						/*!< ADU	: �p�����[�^�G���[ 			*/
	DRV_ERR_ADU_STATUS_RUN, 				/*!< ADU	: ADU���쒆�G���[ 			*/
	DRV_ERR_ADU_STATUS_STOP, 				/*!< ADU	: �Ώۃp�X��~�G���[  		*/
	DRV_ERR_ADU_NOT_CONF, 					/*!< ADU	: ���샂�[�h���ݒ�G���[  	*/
	DRV_ERR_ADU_DMA_ALREADY_GOT,			/*!< ADU	: ���\�[�X�擾�G���[		*/
	DRV_ERR_ADU_DTC_ALREADY_GOT,			/*!< ADU	: DTC���\�[�X�擾�G���[		*/
	DRV_ERR_ADU_MEMIO_ALREADY_GOT,			/*!< ADU	: MEMIO���\�[�X�擾�G���[	*/
	DRV_ERR_ADU_TRANSMIT,					/*!< ADU	: �]�����łȂ��G���[		*/
	DRV_ERR_ADU_ALREADY_GOT,				/*!< ADU	: DMA���\�[�X�m�ێ��s		*/
	DRV_ERR_ADU_RESTART_DMA,				/*!< ADU	: DMA�}�C�R�����G���[		*/
	/* CDU */
	DRV_ERR_CDU_OK = DRV_ID_CDU * 100,		/*!< CDU	: ����I��					*/
	DRV_ERR_CDU_H264_OK,					/*!< CDU,H.264	: ����I��				*/
	DRV_ERR_CDU_MPEG4_OK,					/*!< CDU,H.264	: ����I��				*/
	DRV_ERR_CDU_PRM,						/*!< CDU	: �p�����[�^�G���[			*/
	DRV_ERR_CDU_ALIGNMENT,					/*!< CDU	: �A���C�����g�G���[		*/
	DRV_ERR_CDU_DUMMY_ACCESS_TIMEOUT,		/*!< CDU	: �^�C���A�E�g�G���[		*/
	/* CKGEN */
	DRV_ERR_CKGEN_OK = DRV_ID_CKGEN * 100,	/*!< CKGEN	: ����I��					*/
	DRV_ERR_CKGEN_PRM,						/*!< CKGEN	: �p�����[�^�G���[			*/
	DRV_ERR_CKGEN_TIMEOUT,					/*!< CKGEN	: �^�C���A�E�g�G���[		*/
	/* CPUTOP */
	DRV_ERR_CPUTOP_OK = DRV_ID_CPUTOP * 100,/*!< CPUTOP : ����I��					*/
	DRV_ERR_CPUTOP_PRM,						/*!< CPUTOP : �p�����[�^�G���[			*/
	DRV_ERR_CPUTOP_DMA_OK,					/*!< CPUTOP : DMA�ݒ�OK					*/
	DRV_ERR_CPUTOP_DMA_PRM,					/*!< CPUTOP : DMA�p�����[�^�G���[		*/
	DRV_ERR_CPUTOP_DMA_ALLREADY_GOT,		/*!< CPUTOP : DMA�m�ۍς�				*/
	DRV_ERR_CPUTOP_DMA_ALLREADY_RELEASED,  	/*!< CPUTOP : DMA����ς�				*/
	DRV_ERR_CPUTOP_DMA_NOT_GET,				/*!< CPUTOP : DMA���\�[�X���擾�G���[	*/
	DRV_ERR_CPUTOP_DMA_NOT_SETUP, 			/*!< CPUTOP : DMA���얢�ݒ�G���[		*/
	DRV_ERR_CPUTOP_DMA_TRANSMIT_BUSY, 		/*!< CPUTOP : DMA�]�����G���[			*/
	DRV_ERR_CPUTOP_DMA_STATUS_RUN,			/*!< CPUTOP	: DMA�]����					*/
	DRV_ERR_CPUTOP_DMA_STATUS_STOP,			/*!< CPUTOP : DMA��~��					*/
	/* DAC */
	DRV_ERR_DAC_OK = DRV_ID_DAC * 100,		/*!< DAC	: ����I��					*/
	DRV_ERR_DAC_PRM,						/*!< DAC	: �p�����[�^�G���[			*/
	DRV_ERR_DAC_BSY,						/*!< DAC	: �r�W�[�G���[				*/
	/* DIS */
	DRV_ERR_DIS_OK = DRV_ID_DIS * 100,		/*!< DIS	: ����I��					*/
	DRV_ERR_DIS_PRM,						/*!< DIS	: �p�����[�^�G���[			*/
	/* DTC */
	DRV_ERR_DTC_OK = DRV_ID_DTC * 100,		/*!< DTC	: ����I��					*/
	DRV_ERR_DTC_PRM,						/*!< DTC	: �p�����[�^�G���[			*/
	DRV_ERR_DTC_ALLREADY_GOT,				/*!< DTC	: ���\�[�X�擾�ς݃G���[	*/
	DRV_ERR_DTC_ALLREADY_RELEASED,  		/*!< DTC	: ���\�[�X�J���ς݃G���[	*/
	DRV_ERR_DTC_NOT_GET,					/*!< DTC	: ���\�[�X���擾�G���[		*/
	DRV_ERR_DTC_TRANSMIT_BSY,				/*!< DTC	: �]�����G���[				*/
	DRV_ERR_DTC_NOT_SETUP,					/*!< DTC	: ���얢�ݒ�G���[			*/
	DRV_ERR_DTC_TRANSMIT,					/*!< DTC	: ���]���J�n�G���[			*/
	DRV_ERR_DTC_NOT_RELEASE,				/*!< DTC	: ���\�[�X�J���ł��Ȃ��G���[*/
	DRV_ERR_DTC_DUMMY_ACCESS_TIMEOUT,		/*!< DTC	: �^�C���A�E�g�G���[		*/
	DRV_ERR_DTC_MEMIO_PRM,					/*!< DTC	: MEMIO��DTC�̐ݒ肪�s��v	*/
	DRV_ERR_DTC_MEMIO_MMU_PRM,				/*!< DTC	: MEMIO�o�b�t�@���f�B�X�e�B�l�[�V�����A�h���X�̏ꍇ�ɁA�Y���`���l����MMU�A�N�Z�X����ݒ肳��Ă���ƃG���[ */
	DRV_ERR_DTC_MEMIO_NOT_RESET,			/*!< DTC	: �]���� or �]�����MEMIODMA�`���l���̃��Z�b�g����������ĂȂ��ꍇ	*/

	/* EBC */
	DRV_ERR_EBC_OK = DRV_ID_EBC * 100,		/*!< EBC	: ����I��					*/
	DRV_ERR_EBC_PRM,						/*!< EBC	: �p�����[�^�G���[			*/
	DRV_ERR_EBC_BSY,						/*!< EBC	: �r�W�[�G���[				*/
	/* EXTDMA */
	DRV_ERR_EXTDMA_OK = DRV_ID_EXTDMA * 100,/*!< EXTDMA	: ����I��					*/
	DRV_ERR_EXTDMA_PRM,						/*!< EXTDMA	: �p�����[�^�G���[			*/
	/* GDC */
	DRV_ERR_GDC_OK = DRV_ID_GDC * 100,		/*!< GDC	: ����I��					*/
	DRV_ERR_GDC_PRM,						/*!< GDC	: �p�����[�^�G���[			*/
	DRV_ERR_GDC_BSY,						/*!< GDC	: �r�W�[�G���[				*/
	DRV_ERR_GDC_ALIGNMENT,					/*!< GDC	: �A���C�����g�G���[		*/
	/* GPIO */
	DRV_ERR_GPIO_OK = DRV_ID_GPIOU * 100,	/*!< GPIOU	: ����I��					*/
	DRV_ERR_GPIO_PRM,						/*!< GPIOU	: �p�����[�^�G���[			*/
	DRV_ERR_GPIO_BSY,						/*!< GPIOU	: �r�W�[�G���[				*/
	DRV_ERR_GPIO_FUNCTION,					/*!< GPIOU	: �|�[�g�G���[				*/
	DRV_ERR_GPIO_DIRECTION,					/*!< GPIOU	: �f�B���N�V�����G���[		*/
	DRV_ERR_GPIO_OUTPORTS_REG_USED,			/*!< GPIOU	: ���\�[�X�G���[			*/
	/* HSF */
	DRV_ERR_HSF_OK = DRV_ID_HSF * 100,		/*!< HSF	: ����I��					*/
	DRV_ERR_HSF_PRM,						/*!< HSF	: �p�����[�^�G���[			*/
	/* HSZ */
	DRV_ERR_HSZ_OK = DRV_ID_HSZ * 100,		/*!< HSZ	: ����I��					*/
	DRV_ERR_HSZ_PRM,						/*!< HSZ	: �p�����[�^�G���[			*/
	/* IRS */
	DRV_ERR_IRS_OK = DRV_ID_IRS * 100,		/*!< IRS	: ����I��					*/
	/* LIN */
	DRV_ERR_LIN_OK = DRV_ID_LIN * 100,		/*!< LIN	: ����I��					*/
	/* MEIFU */
	DRV_ERR_MEIF_OK = DRV_ID_MEIF * 100,	/*!< MEIFU	: ����I��					*/
	DRV_ERR_MEIF_PRM,						/*!< MEIFU	: �p�����[�^�G���[			*/
	/* MEMIO */
	DRV_ERR_MEM_OK = DRV_ID_MEM * 100,		/*!< MEMIO	: ����I��					*/
	DRV_ERR_MEM_PRM,						/*!< MEMIO	: �p�����[�^�G���[			*/
	DRV_ERR_MEM_ALLREADY_GOT,        		/*!< MEMIO	: ���\�[�X�m�ۍς݃G���[    */
	DRV_ERR_MEM_ALLREADY_RELEASED,   		/*!< MEMIO	: ���\�[�X�J���ς݃G���[    */
	DRV_ERR_MEM_NOT_GET,					/*!< MEMIO	: ���\�[�X���擾�G���[		*/
	DRV_ERR_MEM_NOT_SET_MMU,				/*!< MEMIO	: MMU����ݒ�s�G���[		*/
	DRV_ERR_MEM_DMA_ACTIVE,					/*!< MEMIO	: �]�����G���[				*/
	DRV_ERR_MEM_DMA_INACTIVE,				/*!< MEMIO	: ���]���G���[				*/
	DRV_ERR_MEM_DMA_SRC_RSIZE,				/*!< MEMIO	: �]���f�[�^�T�C�Y�G���[	*/
	DRV_ERR_MEM_NOT_RELEASE,				/*!< MEMIO	: ���\�[�X�J���s�G���[	*/

	/* MMU */
	DRV_ERR_MMU_OK = DRV_ID_MMU * 100,		/*!< MMU	: ���\�[�X�J���s�G���[	*/
	DRV_ERR_MMU_FATAL,						/*!< MMU	: �v���I�G���[				*/
	DRV_ERR_MMU_INIT_FAIL,					/*!< MMU	: Initial���s				*/
	DRV_ERR_MMU_SEGMENT_FULL,				/*!< MMU	: �Z�O�����g�t��			*/
	DRV_ERR_MMU_MAP_FAIL,					/*!< MMU	: Map���s					*/
	DRV_ERR_MMU_MAP_VALID_SEGMENT,			/*!< MMU	: ��dMap�i����Map����Ă���Z�O�����g�ɑ΂���Map�j			*/
	DRV_ERR_MMU_CLOSE_NOT_VALID_SEGMENT,	/*!< MMU	: ��dClose�i����Close����Ă���Z�O�����g�ɑ΂���Close�j	*/
	/* OIS */
	DRV_ERR_OIS_OK = DRV_ID_OIS * 100,		/*!< OIS	: ����I��					*/
	DRV_ERR_OIS_PRM,						/*!< OIS	: �p�����[�^�G���[			*/
	DRV_ERR_OIS_BSY,						/*!< OIS	: �r�W�[�G���[				*/
	DRV_ERR_OIS_GET_DC,						/*!< OIS	: DC�l�擾�ɂ����郌�W�X�^Read�G���[						*/
	DRV_ERR_OIS_GET_PWM_OFFSET,				/*!< OIS	: PWM�I�t�Z�b�g�擾�ɂ����郌�W�X�^Read�G���[				*/
	DRV_ERR_OIS_GET_INTERVAL_AD,			/*!< OIS	: �C���^�[�o��AD�l��荞�݂ɂ����郌�W�X�^Read�G���[		*/
	DRV_ERR_OIS_GET_AD,						/*!< OIS	: AD�l��荞�݂ɂ����郌�W�X�^Read�G���[					*/
	DRV_ERR_OIS_GET_DCLPFOUT,				/*!< OIS	: LPF�o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[				*/
	DRV_ERR_OIS_GET_DCCPSOUT,				/*!< OIS	: DC������̏o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[		*/
	DRV_ERR_OIS_GET_CORINGOUT,				/*!< OIS	: �R�A�����O�␳��̏o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[*/
	DRV_ERR_OIS_GET_PHASEOUT,				/*!< OIS	: �ʑ��⏞����o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[		*/
	DRV_ERR_OIS_GET_INTEGOUT,				/*!< OIS	: �ϕ������o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[			*/
	DRV_ERR_OIS_GET_HPFOUT,					/*!< OIS	: HPF�����o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[			*/
	DRV_ERR_OIS_GET_GAINOUT,				/*!< OIS	: �Q�C�������o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[		*/
	DRV_ERR_OIS_GET_PWMOUT,					/*!< OIS	: PWM�o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[				*/
	DRV_ERR_OIS_GET_OUTDATA,				/*!< OIS	: �ŏI�o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[				*/
	DRV_ERR_OIS_GET_HOLE_OUT,				/*!< OIS	: �z�[���f�q�o�͒l�ǂݍ��݂ɂ����郌�W�X�^Read�G���[		*/
	DRV_ERR_OIS_GET_MPEF,					/*!< OIS	: ��d���ǂݍ��݂ɂ����郌�W�X�^Read�G���[				*/
	/* PID */
	DRV_ERR_PID_OK = DRV_ID_PID * 100,		/*!< PID	: ����I��					*/
	DRV_ERR_PID_FATAL,						/*!< PID	: �v���I�G���[				*/
	DRV_ERR_PID_PRM,                 		/*!< PID	: �p�����[�^�G���[    		*/
	DRV_ERR_PID_ALLREADY_GOT,        		/*!< PID	: �m�ۍς݃G���[      		*/
	DRV_ERR_PID_ALLREADY_RELEASED,   		/*!< PID	: ����ς݃G���[      		*/
   	 DRV_ERR_PID_BSY,                 		/*!< PID	: �r�W�[�G���[        		*/
	/* PPU */
	DRV_ERR_PPU_OK = DRV_ID_PPU * 100,		/*!< PPU	: ����I��					*/
	DRV_ERR_PPU_FATAL,						/*!< PPU	: �v���I�G���[				*/
	DRV_ERR_PPU_PRM,        				/*!< PPU	: �p�����[�^�G���[     		*/
    DRV_ERR_PPU_ORVERFLOW,  				/*!< PPU	: �I�[�o�[�t���[�G���[ 		*/
    DRV_ERR_PPU_UNDERFLOW,  				/*!< PPU	: �A���_�[�t���[�G���[ 		*/
    DRV_ERR_PPU_ALIGNMENT,  				/*!< PPU	: �A���C�����g�G���[   		*/
    DRV_ERR_PPU_BSY,        				/*!< PPU	: �o�b�t�@�r�W�[�G���[		*/
    DRV_ERR_PPU_DUMMY_ACCESS_TIMEOUT,  		/*!< PPU	: �_�~�[�A�N�Z�X�^�C���A�E�g*/
    DRV_ERR_PPU_DECREMENT_BKM_H_BLOCK,		/*!< PPU	: ��f�������̂���BKM�u���b�N������������4�u���b�N���炷	*/
    DRV_ERR_PPU_DECREMENT_BKM_V_BLOCK,		/*!< PPU	: ��f�������̂���BKM�u���b�N������������4�u���b�N���炷	*/
    DRV_ERR_PPU_BM_H_BLOCK_CHANGE,         	/*!< PPU	: AUTO�ݒ胂�[�h�ŁA�ώZ�̈搅�������̃u���b�N�������𒲐����� */
    DRV_ERR_PPU_BM_V_BLOCK_CHANGE,         	/*!< PPU	: AUTO�ݒ胂�[�h�ŁA�ώZ�̈搂�������̃u���b�N�������𒲐����� */
	/* SERIAL */
	DRV_ERR_SERIAL_OK = DRV_ID_SERIAL * 100,/*!< SERIAL	: ����I��					*/
	DRV_ERR_SERIAL_PRM,						/*!< SERIAL	: �p�����[�^�G���[			*/
	DRV_ERR_SERIAL_BSY,						/*!< SERIAL	: �r�W�[�G���[				*/
	DRV_ERR_SERIAL_INIT,					/*!< SERIAL	: �V���A�����ݒ�G���[		*/
	DRV_ERR_SERIAL_CH4_MODE,				/*!< SERIAL	: �`���l��4��M�G���[		*/
	DRV_ERR_SERIAL_ALLREADY_SET,			/*!< SERIAL	: �V���A�����ݒ�G���[		*/
	DRV_ERR_SERIAL_TIMEOUT,					/*!< SERIAL	: �ʐM�^�C���A�E�g�G���[	*/
	DRV_ERR_SERIAL_IIC_NACK,				/*!< SERIAL	: IIC NACK��M�G���[		*/
    /* SSG */
	DRV_ERR_SSG_OK = DRV_ID_SSG * 100,		/*!< SSG	: ����I��					*/
	DRV_ERR_SSG_FATAL,						/*!< SSG	: �v���I�G���[				*/
	DRV_ERR_SSG_PRM,       					/*!< SSG	: �p�����[�^�G���[     		*/
    DRV_ERR_SSG_BSY,       					/*!< SSG	: �r�W�[�G���[         		*/
	/* TIMER */
	DRV_ERR_TIMER_OK = DRV_ID_TIMER * 100,	/*!< TIMER	: ����I��					*/
	DRV_ERR_TIMER_PRM,						/*!< TIMER	: �p�����[�^�G���[			*/
	DRV_ERR_TIMER_BSY,						/*!< TIMER	: �r�W�[�G���[				*/
	DRV_ERR_TIMER_ALLREADY_GOT,				/*!< TIMER	: ���\�[�X���擾�G���[		*/
	DRV_ERR_TIMER_ALLREADY_RELEASED,		/*!< TIMER	: ���\�[�X����ς݃G���[	*/
	DRV_ERR_TIMER_NOT_GET,					/*!< TIMER	: ���\�[�X���擾�G���[		*/
	DRV_ERR_TIMER_NOT_SETUP,				/*!< TIMER	: ���샂�[�h���ݒ�G���[	*/
	DRV_ERR_TIMER_BR,						/*!< TIMER	: �����䖢�ݒ�G���[		*/
	DRV_ERR_TIMER_DUTY,						/*!< TIMER	: �f���[�e�B�[���ݒ�G���[	*/
	DRV_ERR_TIMER_RESET,					/*!< TIMER	: �^�C�}���������G���[		*/
	DRV_ERR_TIMER_COUNT,					/*!< TIMER	: �N���G���[				*/
	/* USBIFU */
	DRV_ERR_USBIF_OK = DRV_ID_USBIF * 100,	/*!< USBIFU	: ����I��					*/
	DRV_ERR_USBIF_PRM,						/*!< USBIFU	: �p�����[�^�G���[			*/
  	/* VOU */
	DRV_ERR_VOU_OK = DRV_ID_VOU * 100,		/*!< VOU	: ����I��					*/
	DRV_ERR_VOU_PRM,						/*!< VOU	: �p�����[�^�G���[			*/
	DRV_ERR_VOU_BSY,						/*!< VOU	: �r�W�[�G���[				*/
	DRV_ERR_VOU_MEASURE,					/*!< VOU	: HIST�v�����x��			*/
	DRV_ERR_VOU_SWITCHING,					/*!< VOU	: HIST�؂�ւ����x��		*/
	DRV_ERR_VOU_OVERFLOW_WARNING,			/*!< VOU	: �I�[�o�[�t���[�x��		*/
	DRV_ERR_VOU_UNDERFLOW_WARNING,			/*!< VOU	: �A���_�[�t���[�x��		*/
	DRV_ERR_VOU_ES1BUG14_PIX4,				/*!< VOU	: 4��f���炵NG�G���[		*/
	DRV_ERR_VOU_ALIGNMENT,					/*!< VOU	: �A���C�����g�G���[		*/
	DRV_ERR_VOU_ES2BUG47_HALF_TRANS,		/*!< VOU	: COLP�����߃G���[			*/
	DRV_ERR_VOU_AUTO_MODE,					/*!< VOU	: NTSC/PAL�؁A�E���BAUTO���[�h�`�F�b�N�x�P�E*/
	DRV_ERR_VOU_NOT_SET,					/*!< VOU	: HDMI ���W�X�^�ݒ�o�C�p�X	*/
	/* XMC */
	DRV_ERR_XMC_OK = DRV_ID_XMC * 100,		/*!< XMC	: ����I��					*/
	DRV_ERR_XMC_PRM,						/*!< XMC	: �p�����[�^�G���[			*/
	DRV_ERR_XMC_BSY,						/*!< XMC	: �r�W�[�G���[				*/
	/* EMC */
	DRV_ERR_EMC_OK = DRV_ID_XMC * 100,		/*!< EMC	: ����I��					*/
	DRV_ERR_EMC_PRM,						/*!< EMC	: �p�����[�^�G���[			*/
	DRV_ERR_EMC_BSY,						/*!< EMC	: �r�W�[�G���[				*/
	DRV_ERR_EMC_ADJ,						/*!< EMC	: �ʑ������G���[			*/
	DRV_ERR_EMC_DRAMINIT,					/*!< EMC	: DRAM�������G���[			*/
  	/* YCU */
	DRV_ERR_YCU_OK = DRV_ID_YCU * 100,		/*!< YCU	: ����I��					*/
	DRV_ERR_YCU_FATAL,						/*!< YCU	: �v���I�G���[				*/
	DRV_ERR_YCU_PRM,        				/*!< YCU	: �p�����[�^�G���[     		*/
    DRV_ERR_YCU_ORVERFLOW,  				/*!< YCU	: �I�[�o�[�t���[�G���[ 		*/
    DRV_ERR_YCU_UNDERFLOW,  				/*!< YCU	: �A���_�[�t���[�G���[ 		*/
    DRV_ERR_YCU_ALIGNMENT,  				/*!< YCU	: �A���C�����g�G���[   		*/
    DRV_ERR_YCU_BSY,        				/*!< YCU	: �r�W�[�G���[ 				*/
    DRV_ERR_YCU_DUMMY_ACCESS_TIMEOUT,  		/*!< YCU	: �_�~�[�A�N�Z�X�^�C���A�E�g*/
	DRV_ERR_YCU_SRZ_MAGNI,					/*!< YCU	: ���𑜊g��{���G���[(�v�]No.60) */
	/* FRU */
	DRV_ERR_FRU_OK = DRV_ID_FRU * 100,		/*!< FRU	: ����I��					*/

	/* RTC */
	DRV_ERR_RTC_OK = DRV_ID_RTC * 100,		/*!< RTC	: ����I��					*/
	DRV_ERR_RTC_NO_SET,						/*!< RTC	: �A���[���ݒ�Ȃ��G���[	*/

	/* IRQC */
	DRV_ERR_IRQC_OK = DRV_ID_IRQC * 100,	/*!< IRQC	: ����I��					*/
	
	/* KAOU */
	DRV_ERR_KAOU_OK = DRV_ID_KAOU * 100,	/*!< KAOU	: ����I��					*/
	DRV_ERR_KAOU_PRM,						/*!< KAOU	: �p�����[�^�G���[			*/
	DRV_ERR_KAOU_STATUS_RUN,				/*!< KAOU	: ���쒆					*/
	DRV_ERR_KAOU_EYE_1,						/*!< KAOU	: �ݒ�G���[(1�l��)			*/
	DRV_ERR_KAOU_EYE_2,						/*!< KAOU	: �ݒ�G���[(2�l��)			*/
	DRV_ERR_KAOU_EYE_1_2,					/*!< KAOU	: �ݒ�G���[(1,2�l��)		*/
	DRV_ERR_KAOU_EYE_3,						/*!< KAOU	: �ݒ�G���[(3�l��)			*/
	DRV_ERR_KAOU_EYE_1_3,					/*!< KAOU	: �ݒ�G���[(1,3�l��)		*/
	DRV_ERR_KAOU_EYE_2_3,					/*!< KAOU	: �ݒ�G���[(2,3�l��)		*/
	DRV_ERR_KAOU_EYE_1_2_3,					/*!< KAOU	: �ݒ�G���[(1,2,3�l��)		*/
	DRV_ERR_KAOU_EYE_4,						/*!< KAOU	: �ݒ�G���[(4�l��)			*/
	DRV_ERR_KAOU_EYE_1_4,					/*!< KAOU	: �ݒ�G���[(1,4�l��)		*/
	DRV_ERR_KAOU_EYE_2_4,					/*!< KAOU	: �ݒ�G���[(2,4�l��)		*/
	DRV_ERR_KAOU_EYE_1_2_4,					/*!< KAOU	: �ݒ�G���[(1,2,4�l��)		*/
	DRV_ERR_KAOU_EYE_3_4,					/*!< KAOU	: �ݒ�G���[(3,4�l��)		*/
	DRV_ERR_KAOU_EYE_1_3_4,					/*!< KAOU	: �ݒ�G���[(1,3,4�l��)		*/
	DRV_ERR_KAOU_EYE_2_3_4,					/*!< KAOU	: �ݒ�G���[(2,3,4�l��)		*/
	DRV_ERR_KAOU_EYE_1_2_3_4,				/*!< KAOU	: �ݒ�G���[(1,2,3,4�l��)	*/

	/* CACHEIF */
	DRV_ERR_CACHEIF_OK = DRV_ID_CACHEIF * 100,/*!< KAOU	: ����I��					*/
	
	/* VPP */
	DRV_ERR_VPP_OK = DRV_ID_VPP * 100,		/*!< VPP	: ����I��					*/

	/* SUBYCU */
	DRV_ERR_SUBYCU_OK,						/*!< SUBYCU	: ����I��					*/
	DRV_ERR_SUBYCU_PRM,						/*!< SUBYCU	: �p�����[�^�G���[			*/
	DRV_ERR_SUBYCU_ALINGMENT,				/*!< SUBYCU	: �A���C�����g�G���[		*/
	DRV_ERR_SUBYCU_BSY,						/*!< SUBYCU	: �r�W�[�G���[				*/

	/* TCC */
	DRV_ERR_TCC_OK = DRV_ID_TCC * 100,		/*!< TCC	: ����I��					*/
	DRV_ERR_TCC_FIFO_FULL,					/*!< TCC	: �R�}���hFIFO�G���[		*/

	/* PMU */
	DRV_ERR_PMU_OK = DRV_ID_PMU * 100,		/*!< PMU	: ����I��					*/

	/* DMAC*/
	DRV_ERR_DMAC_OK = DRV_ID_DMAC * 100,	/*!< DMAC	: ����I��					*/
	DRV_ERR_DMAC_PRM,						/*!< DMAC	: �p�����[�^�G���[			*/
	DRV_ERR_DMAC_ALLREADY_GOT,				/*!< DMAC	: ���\�[�X�擾�ς݃G���[	*/
	DRV_ERR_DMAC_ALLREADY_RELEASED,  		/*!< DMAC	: ���\�[�X�J���ς݃G���[	*/
	DRV_ERR_DMAC_NOT_GET,					/*!< DMAC	: ���\�[�X���擾�G���[		*/
	DRV_ERR_DMAC_NOT_RELEASE,				/*!< DMAC	: ���\�[�X�J���ł��Ȃ��G���[*/
	DRV_ERR_DMAC_TRANSMISSION_ERR,			/*!< DMAC	: �]���G���[				*/

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
 * @brief	LOW�^HIGH
 */
/*------------------------------------------------------------------------------*/
typedef enum{
    DRV_LV_LOW,				//!< LOW
    DRV_LV_HIGH				//!< HIGH
} eDRV_LV;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_VALID
 * @brief	DISABLE�i�֎~�j�^ENABLE�i���j
 */
/*------------------------------------------------------------------------------*/
typedef enum{
    DRV_VALID_DISABLE,		//!< DISABLE�i�֎~�j
    DRV_VALID_ENABLE		//!< ENABLE �i���j
} eDRV_VALID;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_HEAD_MODE
 * @brief	HEAD���[�h�iCCD/MIX/MAICO�j
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_CCD_MIX_NON	= 0x00,		/*!< ��f�����Ȃ�	*/
	DRV_CCD_MIX_4	= 0x10,		/*!< 4��f����		*/
	DRV_CCD_MIX_9	= 0x20,		/*!< 9��f����		*/
	DRV_MAICO_H3	= 0x40,		/*!< MAICO(����3��f����)	*/
	DRV_CCD_SMEAR	= 0x100,	/*!< �X�~�A�Ή�		*/
	DRV_CCD_4CH		= 0x200,	/*!< 4ch����		*/
	DRV_CCD_HITLC21	= 0x400,	/*!< �����C���^�[���[�X 2:1	*/
	DRV_CCD_HITLC31	= 0x800,	/*!< �����C���^�[���[�X 3:1	*/
	DRV_CCD_HITLC41	= 0x1000,	/*!< �����C���^�[���[�X 4:1	*/
	DRV_CCD_SUB		= 0x2000,	/*!< �ėp�Z���T		*/
	DRV_CCD_2LINE	= 0x4000,	/*!< 2LINE����		*/
	DRV_CCD_FAST	= 0x8000	/*!< ����			*/
}eDRV_HEAD_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SCAN_MODE
 * @brief	CCD�ǂݏo�����[�h
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_CCD_SCAN_PROGRES	= 0x01,		/*!< �v���O���b�V�u   */
	DRV_CCD_SCAN_21INTER	= 0x02,		/*!< 21�C���^�[���[�X */
	DRV_CCD_SCAN_31INTER	= 0x03,		/*!< 31�C���^�[���[�X */
	DRV_CCD_SCAN_41INTER	= 0x04,		/*!< 41�C���^�[���[�X */
	DRV_CCD_SCAN_61INTER	= 0x06,		/*!< 61�C���^�[���[�X */
	DRV_CCD_SCAN_81INTER	= 0x08,		/*!< 81�C���^�[���[�X */
	DRV_CCD_SCAN_121INTER	= 0x0C		/*!< 121�C���^�[���[�X */
}eDRV_SCAN_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_CCD_PIX_MODE
 * @brief	CCD�T�C�Y
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_CCD_PIX_PROGRES			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u   */
	DRV_CCD_PIX_21INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X */
	DRV_CCD_PIX_31INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X */
	DRV_CCD_PIX_41INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X */
	DRV_CCD_PIX_61INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X */
	DRV_CCD_PIX_81INTER			= DRV_CCD_MIX_NON | DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X */
	DRV_CCD_PIX_121INTER		= DRV_CCD_MIX_NON | DRV_CCD_SCAN_121INTER,		/*!< 121�C���^�[���[�X */

	DRV_CCD_PIX_PROGRES_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , 4��f���� */
	DRV_CCD_PIX_21INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, 4��f���� */
	DRV_CCD_PIX_31INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, 4��f���� */
    DRV_CCD_PIX_41INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X, 4��f���� */
	DRV_CCD_PIX_61INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, 4��f���� */
	DRV_CCD_PIX_81INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, 4��f���� */
	DRV_CCD_PIX_121INTER_4MIX	= DRV_CCD_MIX_4   | DRV_CCD_SCAN_121INTER,		/*!< 121�C���^�[���[�X, 4��f���� */

	DRV_CCD_PIX_PROGRES_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , 9��f���� */
	DRV_CCD_PIX_21INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, 9��f���� */
	DRV_CCD_PIX_31INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, 9��f���� */
    DRV_CCD_PIX_41INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_31INTER,		/*!< 41�C���^�[���[�X, 9��f���� */
	DRV_CCD_PIX_61INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, 9��f���� */
	DRV_CCD_PIX_81INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, 9��f���� */
	DRV_CCD_PIX_121INTER_9MIX	= DRV_CCD_MIX_9   | DRV_CCD_SCAN_121INTER,		/*!< 121�C���^�[���[�X, 9��f���� */

	DRV_MAICO_PIX_PROGRES_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , MAICO(����3��f) */
	DRV_MAICO_PIX_21INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, MAICO(����3��f) */
	DRV_MAICO_PIX_31INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, MAICO(����3��f) */
    DRV_MAICO_PIX_41INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_31INTER,		/*!< 41�C���^�[���[�X, MAICO(����3��f) */
	DRV_MAICO_PIX_61INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, MAICO(����3��f) */
	DRV_MAICO_PIX_81INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, MAICO(����3��f) */
	DRV_MAICO_PIX_121INTER_H3	= DRV_MAICO_H3    | DRV_CCD_SCAN_121INTER,		/*!< 121�C���^�[���[�X, MAICO(����3��f) */

	DRV_SMEAR_PIX_PROGRES		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , �X�~�A�Ή� */
	DRV_SMEAR_PIX_21INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, �X�~�A�Ή� */
	DRV_SMEAR_PIX_31INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, �X�~�A�Ή� */
    DRV_SMEAR_PIX_41INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X, �X�~�A�Ή� */
	DRV_SMEAR_PIX_61INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, �X�~�A�Ή� */
	DRV_SMEAR_PIX_81INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, �X�~�A�Ή� */
	DRV_SMEAR_PIX_121INTER		= DRV_CCD_SMEAR   | DRV_CCD_SCAN_121INTER,		/*!< 121�C���^�[���[�X, �X�~�A�Ή� */

	DRV_4CH_PIX_PROGRES			= DRV_CCD_4CH		| DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , 4ch���� */
	DRV_4CH_PIX_21INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, 4ch���� */
	DRV_4CH_PIX_31INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, 4ch���� */
    DRV_4CH_PIX_41INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X, 4ch���� */
	DRV_4CH_PIX_61INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, 4ch���� */
	DRV_4CH_PIX_81INTER			= DRV_CCD_4CH		| DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, 4ch���� */
	DRV_4CH_PIX_121INTER		= DRV_CCD_4CH		| DRV_CCD_SCAN_121INTER,	/*!< 121�C���^�[���[�X, 4ch���� */

	DRV_HI2_1_PIX_PROGRES		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , �����C���^�[���[�X2:1 */
	DRV_HI2_1_PIX_21INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, �����C���^�[���[�X2:1 */
	DRV_HI2_1_PIX_31INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, �����C���^�[���[�X2:1 */
	DRV_HI2_1_PIX_41INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X, �����C���^�[���[�X2:1 */
	DRV_HI2_1_PIX_61INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, �����C���^�[���[�X2:1 */
	DRV_HI2_1_PIX_81INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, �����C���^�[���[�X2:1 */
	DRV_HI2_1_PIX_121INTER		= DRV_CCD_HITLC21	| DRV_CCD_SCAN_121INTER,	/*!< 121�C���^�[���[�X, �����C���^�[���[�X2:1 */

	DRV_HI3_1_PIX_PROGRES		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , �����C���^�[���[�X3:1 */
	DRV_HI3_1_PIX_21INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, �����C���^�[���[�X3:1 */
	DRV_HI3_1_PIX_31INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, �����C���^�[���[�X3:1 */
	DRV_HI3_1_PIX_41INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X, �����C���^�[���[�X3:1 */
	DRV_HI3_1_PIX_61INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, �����C���^�[���[�X3:1 */
	DRV_HI3_1_PIX_81INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, �����C���^�[���[�X3:1 */
	DRV_HI3_1_PIX_121INTER		= DRV_CCD_HITLC31	| DRV_CCD_SCAN_121INTER,	/*!< 121�C���^�[���[�X, �����C���^�[���[�X3:1 */

	DRV_HI4_1_PIX_PROGRES		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_PROGRES,		/*!<  �v���O���b�V�u  , �����C���^�[���[�X4:1 */
	DRV_HI4_1_PIX_21INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_21INTER,		/*!<  21�C���^�[���[�X, �����C���^�[���[�X4:1 */
	DRV_HI4_1_PIX_31INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_31INTER,		/*!<  31�C���^�[���[�X, �����C���^�[���[�X4:1 */
	DRV_HI4_1_PIX_41INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_41INTER,		/*!<  41�C���^�[���[�X, �����C���^�[���[�X4:1 */
	DRV_HI4_1_PIX_61INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_61INTER,		/*!<  61�C���^�[���[�X, �����C���^�[���[�X4:1 */
	DRV_HI4_1_PIX_81INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_81INTER,		/*!<  81�C���^�[���[�X, �����C���^�[���[�X4:1 */
	DRV_HI4_1_PIX_121INTER		= DRV_CCD_HITLC41	| DRV_CCD_SCAN_121INTER,	/*!< 121�C���^�[���[�X, �����C���^�[���[�X4:1 */

	DRV_SUB_PIX_PROGRES			= DRV_CCD_SUB	| DRV_CCD_SCAN_PROGRES,			/*!<  �v���O���b�V�u  , �ėp�Z���T */
	DRV_SUB_PIX_21INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_21INTER,			/*!<  21�C���^�[���[�X, �ėp�Z���T */
	DRV_SUB_PIX_31INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_31INTER,			/*!<  31�C���^�[���[�X, �ėp�Z���T */
	DRV_SUB_PIX_41INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_41INTER,			/*!<  41�C���^�[���[�X, �ėp�Z���T */
	DRV_SUB_PIX_61INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_61INTER,			/*!<  61�C���^�[���[�X, �ėp�Z���T */
	DRV_SUB_PIX_81INTER			= DRV_CCD_SUB	| DRV_CCD_SCAN_81INTER,			/*!<  81�C���^�[���[�X, �ėp�Z���T */
	DRV_SUB_PIX_121INTER		= DRV_CCD_SUB	| DRV_CCD_SCAN_121INTER,			/*!< 121�C���^�[���[�X, �ėp�Z���T */
	/* 2LINE�����o�� */
	DRV_2LINE_PIX_PROGRES			= DRV_CCD_2LINE		| DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , 2Line���� */
	DRV_2LINE_PIX_21INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, 2Line���� */
	DRV_2LINE_PIX_31INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, 2Line���� */
    DRV_2LINE_PIX_41INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X, 2Line���� */
	DRV_2LINE_PIX_61INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, 2Line���� */
	DRV_2LINE_PIX_81INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, 2Line���� */
	DRV_2LINE_PIX_121INTER			= DRV_CCD_2LINE		| DRV_CCD_SCAN_121INTER,	/*!< 121�C���^�[���[�X, 2Line���� */
	
	DRV_2LINE_HI2_1_PIX_PROGRES		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , �����C���^�[���[�X2:1 2Line */
	DRV_2LINE_HI2_1_PIX_21INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, �����C���^�[���[�X2:1 2Line */
	DRV_2LINE_HI2_1_PIX_31INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, �����C���^�[���[�X2:1 2Line */
	DRV_2LINE_HI2_1_PIX_41INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X, �����C���^�[���[�X2:1 2Line */
	DRV_2LINE_HI2_1_PIX_61INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, �����C���^�[���[�X2:1 2Line */
	DRV_2LINE_HI2_1_PIX_81INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, �����C���^�[���[�X2:1 2Line */
	DRV_2LINE_HI2_1_PIX_121INTER	= DRV_CCD_2LINE	| DRV_CCD_HITLC21	| DRV_CCD_SCAN_121INTER,	/*!< 121�C���^�[���[�X, �����C���^�[���[�X2:1 2Line */
	
	DRV_2LINE_HI3_1_PIX_PROGRES		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_PROGRES,		/*!< �v���O���b�V�u  , �����C���^�[���[�X3:1 2Line */
	DRV_2LINE_HI3_1_PIX_21INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_21INTER,		/*!< 21�C���^�[���[�X, �����C���^�[���[�X3:1 2Line */
	DRV_2LINE_HI3_1_PIX_31INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_31INTER,		/*!< 31�C���^�[���[�X, �����C���^�[���[�X3:1 2Line */
	DRV_2LINE_HI3_1_PIX_41INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_41INTER,		/*!< 41�C���^�[���[�X, �����C���^�[���[�X3:1 2Line */
	DRV_2LINE_HI3_1_PIX_61INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_61INTER,		/*!< 61�C���^�[���[�X, �����C���^�[���[�X3:1 2Line */
	DRV_2LINE_HI3_1_PIX_81INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_81INTER,		/*!< 81�C���^�[���[�X, �����C���^�[���[�X3:1 2Line */
	DRV_2LINE_HI3_1_PIX_121INTER	= DRV_CCD_2LINE	| DRV_CCD_HITLC31	| DRV_CCD_SCAN_121INTER,	/*!< 121�C���^�[���[�X, �����C���^�[���[�X3:1 2Line */

	DRV_2LINE_HI4_1_PIX_PROGRES		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_PROGRES,		/*!<  �v���O���b�V�u  , �����C���^�[���[�X4:1 2Line */
	DRV_2LINE_HI4_1_PIX_21INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_21INTER,		/*!<  21�C���^�[���[�X, �����C���^�[���[�X4:1 2Line */
	DRV_2LINE_HI4_1_PIX_31INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_31INTER,		/*!<  31�C���^�[���[�X, �����C���^�[���[�X4:1 2Line */
	DRV_2LINE_HI4_1_PIX_41INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_41INTER,		/*!<  41�C���^�[���[�X, �����C���^�[���[�X4:1 2Line */
	DRV_2LINE_HI4_1_PIX_61INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_61INTER,		/*!<  61�C���^�[���[�X, �����C���^�[���[�X4:1 2Line */
	DRV_2LINE_HI4_1_PIX_81INTER		= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_81INTER,		/*!<  81�C���^�[���[�X, �����C���^�[���[�X4:1 2Line */
	DRV_2LINE_HI4_1_PIX_121INTER	= DRV_CCD_2LINE	| DRV_CCD_HITLC41	| DRV_CCD_SCAN_121INTER,	/*!< 121�C���^�[���[�X, �����C���^�[���[�X4:1 2Line */
	
	/* ���� */
	DRV_FAST_PIX_PROGRES		= DRV_CCD_FAST	| DRV_CCD_SCAN_PROGRES			/*!< ���� */
} eDRV_CCD_PIX_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_MODE_3DNR
 * @brief	3DNR�̓���I��
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
 * @brief	PP1 3DNR�̓��͑I��
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
 * @brief	BM�ABKM�ABKEDGE�g�̐ݒ胂�[�h�I���iAuto/Manual�j
 */
/*------------------------------------------------------------------------------*/
typedef  enum{
	DRV_PPU_SET_MODE_MANUAL = 0,     //!< Manual�ݒ胂�[�h�I��
	DRV_PPU_SET_MODE_AUTO             //!< AUTO�ݒ胂�[�h�I��
} eDRV_PPU_SET_MODE_SW;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PP1_DRAMOUT
 * @brief	PP1 DRAM�ւ̏o�͐؂�ւ�
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	DRV_PPU_DRAMOUT_AFTER_3DNR,
	//DRV_PPU_DRAMOUT_AFTER_DPF	//DPF�폜�̂��߁A���̕ύX
	DRV_PPU_DRAMOUT_AFTER_EVF
} eDRV_PPU_DRAMOUT;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	sDRV_MMU_MODE
 * @brief	MMU�X�C�b�`
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
 * @brief	���\�[�X�̋󂫏�ԁ^�g�p��
 */
/*------------------------------------------------------------------------------*/
typedef enum {
    DRV_RESOURCE_EMPTY,		//!< ���\�[�X�󂫏��
    DRV_RESOURCE_USED,		//!< ���\�[�X�g�p��

	DRV_RESOURCE_RESERVED
}  eDRV_RESOURCE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_DMA_DIRECTION
 * @brief	DMA�]�������ݒ� (MEIFU,USBIFU�Ŏg�p)
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DMA_DISABLE,			//!< �f�B�Z�[�u��	// Dummy�i�g�p���Ȃ��j
	DMA_READ,				//!< ���f�B�A�A�O���f�o�C�X�� �� �Y���u���b�N
	DMA_WRITE				//!< �Y���u���b�N �� ���f�B�A�A�O���f�o�C�X��
}eDRV_DMA_DIRECTION;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_NTPAL_MODE
 * @brief	NTSC/PAL���[�h
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DRV_NTPAL_MODE_NTSC,		//!< NTSC���[�h
	DRV_NTPAL_MODE_HDTV_525_60,	//!< NTSC���[�h(60i)
	DRV_NTPAL_MODE_PAL,			//!< PAL���[�h
	DRV_NTPAL_MODE_HDTV_1125,	//!< HDTV���[�h�i1125i/p/4K2K�j
	DRV_NTPAL_MODE_HDTV_1125_60,//!< HDTV���[�h�i1125i/p/4K2K�j60Hz	
	DRV_NTPAL_MODE_HDTV_750,	//!< HDTV���[�h�i750p�j
	DRV_NTPAL_MODE_HDTV_750_60,	//!< HDTV���[�h�i750p�j60Hz
	DRV_NTPAL_MODE_HDTV_1250,	//!< HDTV���[�h�i1250i�j
	DRV_NTPAL_MODE_EVF_5994,	//!< EVF���[�h�i59.94p�j
	DRV_NTPAL_MODE_EVF_50,		//!< EVF���[�h�i50p�j
	DRV_NTPAL_MODE_EVF_24,		//!< EVF���[�h�i24p�j
	DRV_NTPAL_MODE_EVF_2398,	//!< EVF���[�h�i23.98p�j
	DRV_NTPAL_MODE_AUTO,		//!< NTSC(EVF) �� PAL(EVF)

	DRV_NTPAL_MODE_RESERVED
} eDRV_NTPAL_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_IMAGE_ASPECT
 * @brief	�f���A�X�y�N�g��ݒ�
 */
/*------------------------------------------------------------------------------*/
typedef	enum {
	IMAGE_ASPECT_4_3,		//!< �A�X�y�N�g��	 4:3
	IMAGE_ASPECT_16_9		//!< �A�X�y�N�g��	16:9
} eDRV_IMAGE_ASPECT;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_LCD_MODE
 * @brief	LCD���[�h�iYC�o�́^RGB�o�́^���̑��j
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_NOMAL_LCD = 0x1,			//!< �ʏ�ݒ�
	DRV_YC_LCD = 0x2,				//!< YC�o�͉t���ݒ�
	DRV_RGB_LCD = 0x4,				//!< RGB�o�͉t���ݒ�

	DRV_LCD_RESERVED
} eDRV_LCD_MODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_LCD_CLK_SEL
 * @brief	LCD�p�N���b�N���g��
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
 * @brief	���j�^�����R���I��
 */
/*------------------------------------------------------------------------------*/
typedef enum {
	DRV_MONM_SEL_MONL,				//!< LCD�Ή����j�^�����R��
	DRV_MONM_SEL_MONT,				//!< TV�Ή����j�^�����R��
	DRV_MONM_SEL_MONM_PRO,			//!< PRO�Ή����j�^�����R��
	DRV_MONM_SEL_MONLT,				//!< LCD��TV�Ή����j�^�����R��

	DRV_MONM_SEL_RESERVED
} eDRV_MONM_SEL;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_VOU_PROFILE
 * @brief	�\���T�C�Y�E�\���ʒu�����ݒ�p�v���t�@�C���I��

 */
/*------------------------------------------------------------------------------*/
typedef enum {
	
	DRV_VOU_PROF_CINEMA_5994P_4K1K,					//!< �t�H�[�}�b�g�F4��2��cimema(4k1k)�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_CINEMA_50P_4K1K,					//!< �t�H�[�}�b�g�F4��2��cimema(4k1k)�A�t���[�����g���F50p
	DRV_VOU_PROF_2160P_5994P_4K1K,					//!< �t�H�[�}�b�g�F2160p(4k1k)�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_2160P_50P_4K1K,					//!< �t�H�[�}�b�g�F2160p(4k1k)�A�t���[�����g���F50p
	DRV_VOU_PROF_CINEMA_5994P_2K2K,					//!< �t�H�[�}�b�g�F4��2��cimema(2k2k)�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_CINEMA_50P_2K2K,					//!< �t�H�[�}�b�g�F4��2��cimema(2k2k)�A�t���[�����g���F50p
	DRV_VOU_PROF_2160P_5994P_2K2K,					//!< �t�H�[�}�b�g�F2160p(2k2k)�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_2160P_50P_2K2K,					//!< �t�H�[�}�b�g�F2160p(2k2k)�A�t���[�����g���F50p
	DRV_VOU_PROF_CINEMA_5994P_3GBPS,				//!< �t�H�[�}�b�g�F4��2��cimema(3gbps)�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_CINEMA_50P_3GBPS,					//!< �t�H�[�}�b�g�F4��2��cimema(3gbps)�A�t���[�����g���F50p
	DRV_VOU_PROF_2160P_5994P_3GBPS,					//!< �t�H�[�}�b�g�F2160p(3gbps)�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_2160P_50P_3GBPS,					//!< �t�H�[�}�b�g�F2160p(3gbps)�A�t���[�����g���F50p
	DRV_VOU_PROF_2160P_2997P,						//!< �t�H�[�}�b�g�F2160p�A�t���[�����g���F30p/29.97p
	DRV_VOU_PROF_2160P_25P,							//!< �t�H�[�}�b�g�F2160p�A�t���[�����g���F25p
	DRV_VOU_PROF_2160P_2398P,						//!< �t�H�[�}�b�g�F2160p�A�t���[�����g���F24p/23.98p
	DRV_VOU_PROF_2160P_24P_SMPTE,					//!< �t�H�[�}�b�g�F2160p(SMPTE)�A�t���[�����g���F24p
	DRV_VOU_PROF_UPCNV_720P_1080P_5994P,			//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_UPCNV_1080I_1080P_5994P,			//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_1080P_THR_5994P,					//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_UPCNV_720P_1080P_50P,				//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F50p
	DRV_VOU_PROF_UPCNV_1080I_1080P_50P,				//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F50p
	DRV_VOU_PROF_1080P_THR_50P,						//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F50p
	DRV_VOU_PROF_1080P_2398P,						//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F24p/23.98p
	DRV_VOU_PROF_DWCNV_1080P_1080I_5994I,			//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F59.94i/60i
	DRV_VOU_PROF_UPCNV_720P_1080I_5994I,			//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F59.94i/60i
	DRV_VOU_PROF_1080I_THR_5994I,					//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F59.94i/60i
	DRV_VOU_PROF_DWCNV_1080P_1080I_50I,				//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F50i
	DRV_VOU_PROF_UPCNV_720P_1080I_50I,				//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F50i
	DRV_VOU_PROF_1080I_THR_50I,						//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F50i
	DRV_VOU_PROF_DWCNV_1080P_720P_5994P,			//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_DWCNV_1080I_720P_5994P,			//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_720P_THR_5994P,						//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F59.94p/60p 
	DRV_VOU_PROF_DWCNV_1080P_720P_50P,				//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F50p
	DRV_VOU_PROF_DWCNV_1080I_720P_50P,				//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F50p
	DRV_VOU_PROF_720P_THR_50P,						//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F50p
	DRV_VOU_PROF_UPCNV_480I_480P_5994P,				//!< �t�H�[�}�b�g�F480p�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_480P_5994P,						//!< �t�H�[�}�b�g�F480p�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_UPCNV_576I_576P_50P,				//!< �t�H�[�}�b�g�F576p�A�t���[�����g���F50p
	DRV_VOU_PROF_576P_50P,							//!< �t�H�[�}�b�g�F576p�A�t���[�����g���F50p
	DRV_VOU_PROF_DWCNV_480P_480I_5994P,				//!< �t�H�[�}�b�g�F480i�A�t���[�����g���F59.94i/60i
	DRV_VOU_PROF_480I_THR_5994I,					//!< �t�H�[�}�b�g�F480i�A�t���[�����g���F59.94i/60i
	DRV_VOU_PROF_DWCNV_576P_576I_50I,				//!< �t�H�[�}�b�g�F576i�A�t���[�����g���F50i
	DRV_VOU_PROF_576I_THR_50I,						//!< �t�H�[�}�b�g�F576i�A�t���[�����g���F50i
	DRV_VOU_PROF_NTSC_5994I,						//!< �t�H�[�}�b�g�FNTSC�A�t���[�����g���F59.94i/60i
	DRV_VOU_PROF_PAL_50I,							//!< �t�H�[�}�b�g�FPAL�A�t���[�����g���F50i
	DRV_VOU_PROF_MANUAL,							//!< �t�H�[�}�b�g�F�蓮�ݒ�A�t���[�����g���F�C�� 

	DRV_VOU_PROF_2160P_2997P_PRO,					//!< �t�H�[�}�b�g�F2160p�A�t���[�����g���F30p/29.97p
	DRV_VOU_PROF_2160P_25P_PRO,						//!< �t�H�[�}�b�g�F2160p�A�t���[�����g���F25p
	DRV_VOU_PROF_2160P_2398P_PRO,					//!< �t�H�[�}�b�g�F2160p�A�t���[�����g���F24p/23.98p
	DRV_VOU_PROF_2160P_24P_SMPTE_PRO,				//!< �t�H�[�}�b�g�F2160p(SMPTE)�A�t���[�����g���F24p
	DRV_VOU_PROF_1080P_5994P_PRO,					//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F50p
	DRV_VOU_PROF_1080P_50P_PRO,						//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F50p
	DRV_VOU_PROF_1080P_2398P_PRO,					//!< �t�H�[�}�b�g�F1080p�A�t���[�����g���F24p/23.98p
	DRV_VOU_PROF_1080I_5994I_PRO,					//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F59.94i/60i
	DRV_VOU_PROF_1080I_50I_PRO,						//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F50i
	DRV_VOU_PROF_1080I_48I_PRO,						//!< �t�H�[�}�b�g�F1080i�A�t���[�����g���F48i
	DRV_VOU_PROF_720P_5994P_PRO,					//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F59.94p/60p 
	DRV_VOU_PROF_720P_50P_PRO,						//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F50p
	DRV_VOU_PROF_720P_30P_PRO,						//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F30p
	DRV_VOU_PROF_720P_25P_PRO,						//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F25p
	DRV_VOU_PROF_720P_24P_PRO,						//!< �t�H�[�}�b�g�F720p�A�t���[�����g���F24p
	DRV_VOU_PROF_480P_5994P_PRO,					//!< �t�H�[�}�b�g�F480p�A�t���[�����g���F59.94p/60p
	DRV_VOU_PROF_576P_50P_PRO,						//!< �t�H�[�}�b�g�F576p�A�t���[�����g���F50p
	DRV_VOU_PROF_480I_5994I_PRO,					//!< �t�H�[�}�b�g�F480i�A�t���[�����g���F59.94i/60i
	DRV_VOU_PROF_576I_50I_PRO,						//!< �t�H�[�}�b�g�F576i�A�t���[�����g���F50i
	DRV_VOU_PROF_MANUAL_PRO,						//!< �t�H�[�}�b�g�F�蓮�ݒ�A�t���[�����g���F�C�� 
	                                                                              
	DRV_VOU_PROF_RESERVED
} eDRV_VOU_PROFILE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PPU_CNT_RST_EDGE
 * @brief	���C���J�E���^�����Z�b�g����^�C�~���O�i�����C���^�[���[�X�p�j
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_PPU_RST_AT_NEGEDGE = 0,		//!< VD������ŃJ�E���^���Z�b�g
	DRV_PPU_RST_AT_POSEDGE = 1,		//!< VD���オ��ŃJ�E���^���Z�b�g

	DRV_PPU_RST_AT_RESERVED
} eDRV_PPU_CNT_RST_EDGE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PPU_HI21_WADR_INCMODE
 * @brief	2:1�����C���^�[���[�X���̃A�h���X���Z���[�h
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_PPU_HI21_WADR_INC1_3 = 0,		//!< 1or3���Z
	DRV_PPU_HI21_WADR_INC2   = 1,		//!< 2���Z

	DRV_PPU_HI21_WADR_INC2_RESERVED
} eDRV_PPU_HI21_WADR_INCMODE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_PPU_FAST_LINE_SEL
 * @brief	CCD�nQMIX �������[�h���̏o�̓��C���I��
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_PPU_ODD = 0,				//!< �����f�[�^���o��
	DRV_PPU_EVEN					//!< ��f�[�^���o��
} eDRV_PPU_FAST_LINE_SEL;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_READ_START_FIELD
 * @brief	��荞�݊J�nfield
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_READ_FIRST_RAW  	= 1,						/*!<  1Field�ڂ����荞��	*/
	DRV_READ_SECOND_RAW 	= 2,						/*!<  2Field�ڂ����荞��	*/
	DRV_READ_THIRD_RAW  	= 3,						/*!<  3Field�ڂ����荞��	*/
	DRV_READ_FOURTH_RAW 	= 4,						/*!<  4Field�ڂ����荞��	*/
	DRV_READ_FIFTH_RAW  	= 5,						/*!<  5Field�ڂ����荞��	*/
	DRV_READ_SIXTH_RAW  	= 6,						/*!<  6Field�ڂ����荞��	*/
	DRV_READ_SEVENTH_RAW  	= 7,						/*!<  7Field�ڂ����荞��	*/
	DRV_READ_EIGHTH_RAW  	= 8,						/*!<  8Field�ڂ����荞��	*/
	DRV_READ_NINTH_RAW  	= 9,						/*!<  9Field�ڂ����荞��	*/
	DRV_READ_TENTH_RAW  	= 10,						/*!<  10Field�ڂ����荞��	*/
	DRV_READ_ELEVENTH_RAW  	= 11,						/*!<  11Field�ڂ����荞��	*/
	DRV_READ_TWELFTH_RAW  	= 12						/*!<  12Field�ڂ����荞��	*/

} eDRV_READ_START_FIELD;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SSG_CCDVD_RESET_SEL
 * @brief	CCD�n VDHEAD�̎������Z�b�g�̑I��
 */
/* -----------------------------------------------------------------------------*/
typedef	enum {
	DRV_SSG_CCD_RST = 0,			//!<  CCDVD ���Z�b�g�ݒ�	*/
	DRV_SSG_NRST_VDH_EXT			//!<  CCDVD ���Z�b�g���Ȃ�	*/
} eDRV_SSG_CCDVD_RESET_SEL;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SSG_DIV_VD_SUB
 * @brief	CCD�n �ėp�Z���T���[�h���̊O��VD�����ݒ�
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_SSG_CLKDIV_NON = 0,				//!< �����Ȃ�
	DRV_SSG_CLKDIV_4,					//!< 4����
	DRV_SSG_CLKDIV_8,					//!< 8����
	DRV_SSG_CLKDIV_16					//!< 16����
} eDRV_SSG_DIV_VD_SUB;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_RESOURCE_ID
 * @brief	���\�[�XID�ԍ�
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
 * @brief	���\�[�X�g�p��
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_CMN_RESOURCE_EMPTY = 0,
	DRV_CMN_RESOURCE_USED
} eDRV_CMN_RESOURCE_STATE;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_CMN_EXCLUSION
 * @brief	�r������Ǘ��p
 */
/* -----------------------------------------------------------------------------*/
typedef enum {
	DRV_CMN_EXCLUSION_RSRC = 0,			/* ���\�[�X�Ǘ��pSRAM�i�h���C�o�����Ŏg�p�j */
	DRV_CMN_EXCLUSION_TLB,				/* TLB�i�h���C�o�����Ŏg�p�j */
	DRV_CMN_EXCLUSION_CKGEN,			/* CKG */
	DRV_CMN_EXCLUSION_GPIOU,			/* GPIO */
	DRV_CMN_EXCLUSION_OTHER,			/* �ėp */
	DRV_CMN_EXCLUSION_RESERVED
} eDRV_CMN_EXCLUSION;

/*------------------------------------------------------------------------------*/
/*!
 * @enum	eDRV_SELECT_MEMCON
 * @brief	�����R���̃`���l���I���iCDU/SUBYCU�j
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
 * @brief	DMA�u���b�N�I��
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
 * @brief	DMA�`���l���I��
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
	�\���̐錾
*********************************************************************************/
/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_IMG_SIZE
 * @brief	H/V�����T�C�Y
 */
/* -----------------------------------------------------------------------------*/
typedef struct {
	ULONG ulHsize;			//!< H�����T�C�Y
	ULONG ulVsize;			//!< V�����T�C�Y
} sDRV_IMG_SIZE;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_IMG_POS
 * @brief	H/V�����ʒu
 */
/* -----------------------------------------------------------------------------*/
typedef struct {
	ULONG ulHpos;			//!< H�����ʒu
	ULONG ulVpos;			//!< V�����ʒu
} sDRV_IMG_POS;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_DISP_IMAGE
 * @brief	�\���T�C�Y�E�\���J�n�ʒu�ݒ�
 */
/*------------------------------------------------------------------------------*/
typedef struct {
	sDRV_IMG_SIZE  	sAreaSize;			//!< �\���G���A�T�C�Y
	ULONG			sStartPosH;			//!< �����\���J�n�ʒu
	ULONG			sStartPosV;			//!< �����\���J�n�ʒu
	ULONG			sStartPosVEven;		//!< �����\���J�n�ʒu(EVEN)
} sDRV_DISP_IMAGE;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_CMN_RESOURCE
 * @brief	���\�[�X�ΏۑI��p�\����
 */
/* -----------------------------------------------------------------------------*/
typedef	struct	{
	eDRV_RESOURCE_ID	eResourceId;				/*!< ���\�[�XID�ԍ�	*/
	UCHAR				ucResourceCh;				/*!< ���\�[�XCH�ԍ�	*/
}sDRV_CMN_RESOURCE;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_CMN_INIT_AGENT_SOCKET_DMAC
 * @brief	DMAC�pTLB�������\����
 */
/* -----------------------------------------------------------------------------*/
typedef	struct	{
	eDRV_DMAC_DMA_BLOCK	eSelectBlock;					//!< �u���b�N�I���iMIU0�AMIU1��STU�j
	eDRV_DMAC_DMA_CH	eDmaCh;							//!< DMA�`���l���I��
	UCHAR				*pucInstructionStartAddress;	//!< �C���X�g���N�V�����A�N�Z�X�̃X�^�[�g�A�h���X
}sDRV_CMN_INIT_AGENT_SOCKET_DMAC;

/*------------------------------------------------------------------------------*/
/*!
 * @struct	sDRV_DMAC_USE_BURST_TRANS	
 * @brief	DMAC�Ń��W�X�^�̃o�[�X�g���[�h�ƃ��C�g�p
 */
/* -----------------------------------------------------------------------------*/
typedef struct{
	eDRV_SWITCH			eDmaTransSw;					//!< DMAC�Ń��W�X�^���[�hSW
	eDRV_DMAC_DMA_BLOCK	eSelectBlock;					//!< �u���b�N�I���iMIU0�AMIU1��STU�j
	eDRV_DMAC_DMA_CH	eDmaCh;							//!< DMA�`���l���I��
	UCHAR				ucMmuidNum;						//!< ARM����DMA�ւ̃A�h���X�ϊ��p���ID�i0�`7�j
	UCHAR				*pucInstructionStartAddress;	//!< �C���X�g���N�V�����A�N�Z�X�̃X�^�[�g�A�h���X
}sDRV_DMAC_USE_BURST_TRANS;


/*********************************************************************************
	�v���g�^�C�v�錾
*********************************************************************************/
eDRV_ERR	eLdCMN_GetEmptyResource(sDRV_CMN_RESOURCE *psResource);
eDRV_ERR	eLdCMN_ReleaseResource(sDRV_CMN_RESOURCE *psResource);
eDRV_ERR	eLdCMN_ReferenceResource(eDRV_RESOURCE_ID eResourceId,void *psRefResource);
eDRV_ERR	eLdCMN_InitializeResource(void);
void DRV_CMN_INIT_AGENT_SOCKET(eDRV_CMN_AGENT_SOCKET AGENT);
void DRV_CMN_INIT_AGENT_SOCKET_DMAC(sDRV_CMN_INIT_AGENT_SOCKET_DMAC *);
void DRV_CMN_CHANGE_AGENT_DRAM(eDRV_CMN_AGENT_GROUP, ULONG, ULONG);

#endif	/* __EXT_DRV_CMN_H__ */
