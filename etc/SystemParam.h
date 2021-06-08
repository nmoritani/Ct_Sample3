/***************************************************************************/
/*�@�t�@�C����  �FSystemParam.h                                            */
/*�@�T�v        �FOS�������w�b�_�t�@�C��                                 */
/* Copyright(c)2005-2006 by Matsushita Electric Industrial Co., Ltd.       */
/***************************************************************************/
/***************************************************************************/

#ifndef __OS_H__
#define __OS_H__



#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/* �ύX���� */
/* �o�[�W���� 	�X�V���e 	�ύX�� 	�X�V��	*/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/

/* Macro��` */

/****************************************************************************/

/****************************************************************************/
/*  PF�����z��								                                */
/****************************************************************************/

/**
 * @brief		�\�t�g�u���[�N�𔭐�������
 */
#define SOFT_BREAK() __breakpoint(0)

/**
 * @brief		���荞�݃n���h���ÓI�o�^�p�}�N��
 * @details		�o�^���銄�荞�݃n���h���̌`��
 *				
 *				void handler(INT_PARAM)
 *				{
 *					// ���荞�ݏ���
 *				}
 *				
 * @param[in]	intno	���荞�ݔԍ�
 * @param[in]	handler	�o�^����n���h��
 */
#define CRE_INT(intno, handler)  DEF_INH(intno, {TA_HLNG, handler})

/**
 * @brief		���荞�݃n���h���̈���
 */
#define INT_PARAM void

/**
 * @brief		�V�X�e�������擾
 * @param[out]	time	�V�X�e�������̊i�[��(UW�^)
 */
#define GET_TIM(time)	time = tx_time_get()

/****************************************************************************/
/* DMAC CH */
/****************************************************************************/
#define SYS_REMO_DMAC_CH		MDMAC_CH_0	// MIU DMAC0 CH0
#define ADC_DMAC_CH				MDMAC_CH_1	// MIU DMAC0 CH1
#define	SYS_ROM_DMAC_CH			MDMAC_CH_2	// MIU DMAC0 CH2
#define	SYS_ROM_DMAC_CH2		MDMAC_CH_3	// MIU DMAC0 CH3
#define	AVC_ADU_DMAC_CH			MDMAC_CH_4	// MIU DMAC0 CH4
#define	GUI_DMAC_CH				MDMAC_CH_5	// MIU DMAC0 CH5
#define	SYS_RECT_DMAC_CH		MDMAC_CH_6	// MIU DMAC0 CH6
//#define						MDMAC_CH_7	// MIU DMAC0 CH7

#define CAM_SSPRX_DMAC_CH		MDMAC_CH_8	// MIU DMAC1 CH0
#define	CAM_SSPTX_DMAC_CH		MDMAC_CH_9	// MIU DMAC1 CH1
//#define ADC_DMAC_CH			MDMAC_CH_10	// MIU DMAC1 CH2
//#define						MDMAC_CH_11	// MIU DMAC1 CH3
//#define						MDMAC_CH_12	// MIU DMAC1 CH4
//#define						MDMAC_CH_13	// MIU DMAC1 CH5
//#define						MDMAC_CH_14	// MIU DMAC1 CH6
//#define						MDMAC_CH_15	// MIU DMAC1 CH7

#define CFS_MOVIE_DMAC_CH		MDMAC_CH_16	// MIU DMAC2  CH0
#define	CFS_PICTURE_DMAC_CH		MDMAC_CH_17	// MIU DMAC2  CH1
#define	MDC_DMAC_CH1			MDMAC_CH_18	// MIU DMAC2  CH2
#define	MDC_DMAC_CH2			MDMAC_CH_19	// MIU DMAC2  CH3
#define	AVC_AUDIO_DMAC_CH		MDMAC_CH_20	// MIU DMAC2  CH4
//#define						MDMAC_CH_21	// MIU DMAC2  CH5
//#define						MDMAC_CH_22	// MIU DMAC2  CH6
#define	STC_AUDIO_DMAC_CH		MDMAC_CH_23	// MIU DMAC2  CH7

/****************************************************************************/
/* TMR CH */
/****************************************************************************/
#define SYS_BATT_TMR_CH			TMR_CH0
#define SYS_RTC_TMR_CH			TMR_CH1
#define SYS_AD_TMR_CH			TMR_CH2
#define SYS_FAN_TMR_CH			TMR_CH3
#define SSP2_TMR_CH				TMR_CH4
#define SYS_RTC_MS_TMR_CH		TMR_CH5
#define	AVC_TMR_PLY_LPCM		TMR_CH6
#define	AVC_TMR_PLY_SPDIF		TMR_CH7
#define AVC_TMR_AUDIO_CYCLE		TMR_CH8	
#define	AVC_TMR_AVDF			TMR_CH9	
#define	FREERUN_TMR_CH			TMR_CH10	// TMR_Wait()�p
#define	KAO_TMR_CH				TMR_CH11

#define	CAM_1MS_TMR_CH			TMR_CH12
#define	CAM_AF1_TMR_CH			TMR_CH13
#define	CAM_AF2_TMR_CH			TMR_CH14
#define	CAM_SUB_TMR_CH			TMR_CH15
//#define						TMR_CH16
//#define						TMR_CH17
//#define						TMR_CH18
//#define						TMR_CH19

//#define						TMR_CH20	// Linux�p
//#define						TMR_CH21	// Linux�p
//#define						TMR_CH22	// Linux�p
//#define						TMR_CH23	// Linux�p

//#define						TMR_CH24	// ThreadX�p
//#define						TMR_CH25	// ThreadX�p

/****************************************************************************/
/* �`�b�v�ԃV���A���ʐMID */
/****************************************************************************/
/*==== CH0�iMain��Sub�j ======*/
#define M2S_ID_SM_TOP				0
#define M2S_ID_SYS_NFC_SMS			0		// SYS�u���b�N NFC�ʐM�p
#define M2S_ID_SYS_NFC_SMM			1		// SYS�u���b�N NFC�ʐM�p
#define M2S_ID_SYS_NFC_SML			2		// SYS�u���b�N NFC�ʐM�p
#define M2S_ID_VOU_SM				3		// VOU���W�X�^�ݒ�
#define M2S_ID_VCL_SM_S				4		// VCL�`�b�v�ԒʐM
#define M2S_ID_VCL_SM_L				5		// VCL�`�b�v�ԒʐM
#define M2S_ID_AVFW_VEN2_CORE_SM	6		// core�ԏ��iVEN0��VEN2�j
#define M2S_ID_AVFW_VEN2_BACD_SM	7		// bacd�ԏ��iVEN0��VEN2�j
#define M2S_ID_AVFW_VEN3_CORE_SM	8		// core�ԏ��iVEN0��VEN3�j
#define M2S_ID_AVFW_VEN3_BACD_SM	9		// bacd�ԏ��iVEN0��VEN3�j
#define M2S_ID_AVFW_VSI_READY_OUTPUT_SM	10		// �摜���������imain��sub�j
#define M2S_ID_AVFW_VSI_READY_RESIZE_SM	11		// ���T�C�Y���������imain��sub�j
#define M2S_ID_SM_BOTTOM				11

/*==== CH1�iMain��Sub�j ======*/
#define M2S_ID_MS_TOP				64
#define M2S_ID_SYS_NFC_MSS			64		// SYS�u���b�N NFC�ʐM�p
#define M2S_ID_SYS_NFC_MSM			65		// SYS�u���b�N NFC�ʐM�p
#define M2S_ID_SYS_NFC_MSL			66		// SYS�u���b�N NFC�ʐM�p
#define M2S_ID_SUB_PORT				67		// SUB�u���b�N �[�q���ʐM�p
#define M2S_ID_VOU_MS				68		// VOU���W�X�^�ݒ�
#define M2S_ID_VCL_MS_S				69		// VCL�`�b�v�ԒʐM
#define M2S_ID_VCL_MS_L				70		// VCL�`�b�v�ԒʐM
#define M2S_ID_AVFW_VEN2_CORE_MS	71		// core�ԏ��iVEN0��VEN2�j
#define M2S_ID_AVFW_VEN2_BACD_MS	72		// bacd�ԏ��iVEN0��VEN2�j
#define M2S_ID_AVFW_VEN3_CORE_MS	73		// core�ԏ��iVEN0��VEN3�j
#define M2S_ID_AVFW_VEN3_BACD_MS	74		// bacd�ԏ��iVEN0��VEN3�j
#define M2S_ID_AVFW_VSI_READY_OUTPUT_MS	75		// �摜���������imain��sub�j
#define M2S_ID_AVFW_VSI_OUTPUT_MS		76		// �����␳�imain��sub�j
#define M2S_ID_AVFW_VSI_READY_RESIZE_MS	77		// ���T�C�Y���������imain��sub�j
#define M2S_ID_MS_BOTTOM				77


/****************************************************************************/
/*  AVIO */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define 	AVDCAM_TSKPRI				29
#define 	AVD_THREAD_TSKPRI			31
#define 	AVDF_TSKPRI					32
#define 	AVDA_TSKPRI					35
#define 	AVC_DRAW_TSKPRI				126

/*==== ���荞�ݔԍ� ======*/
#define	AVC_INTNO_SSG_IVD				396		//	VideoVD�O�G�b�W_2
#define	AVC_INTNO_SSG_IVD_inv			197		//	VideoVD��G�b�W

#define	AVC_INTNO_VOU_HDMIVD_IRQ0		224		//	HDMI_VD������0_1
#define	AVC_INTNO_VOU_HDMI_REG_IRQ		226		//	HDMI_PRO_VD������_1
#define	AVC_INTNO_VOU_LCDVD_0			230		//	LCD_VD������0
#define	AVC_INTNO_VOU_LCDVD_1			231		//	LCD_VD������1
#define	AVC_INTNO_VOU_MONW_IRQ0			254		//	MONW�������荞��
#define	AVC_INTNO_VOU_MONW_IRQ1			255		//	MONW�G���[���荞��
#define	AVC_INTNO_VOU_LCD_OVFLG_IRQ		228		//	MONT_PRO�o�b�t�@�A���_�[
#define	AVC_INTNO_VOU_MONL_IRQ			252		//	MONL�o�b�t�@�A���_�[
#define	AVC_INTNO_VOU_MONT_IRQ			253		//	MONT�o�b�t�@�A���_�[

#define	AVC_INTNO_YCU_YCM_IRQ_F			240		//	FG�����I��
#define	AVC_INTNO_YCU_YCM_IRQ_B			242		//	BG�����I��
#define	AVC_INTNO_YCU_AM_IRQ			244		//	YCU(AM)�����I��

#define	AVC_INTNO_FRU_PD14_IRQ			246		//	FRU�I�����荞��(PD14)
#define	AVC_INTNO_FRU_PD15_IRQ			247		//	FRU�I�����荞��(PD15)
#define	AVC_INTNO_FRU_PD16_IRQ			248		//	FRU�I�����荞��(PD16)

#define	AVC_INTNO_PPU_PPU_IRQ			211		//	PPU�I�����荞��

#define	AVC_INTNO_ADU_1					176		//	ADU����p���荞��1�iDRam�����I���ʒm�j
#define	AVC_INTNO_ADU_2					177		//	ADU����p���荞��2�iDRam�Ǐo�I���ʒm(MON)�j
#define	AVC_INTNO_ADU_3					178		//	ADU����p���荞��3�iDRam�Ǐo�I���ʒm�j
#define	AVC_INTNO_APU_IRQOUT_1			183		//	�I�[�f�B�I�o�b�t�@�������������P
#define	AVC_INTNO_APU0_AUX				184		//	APP0�⏕�����t���O
#define	AVC_INTNO_APU1_AUX				185		//	APP1�⏕�����t���O

#define AVC_INTNO_CAM_YC_START_IRQ		9		//	CAM YC�J�n�ʒm(CAM��BE)


/****************************************************************************/
/*  DDD */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define 	DDD_TSKPRI_ASYNC	46
#define 	DDD_TSKPRI_BG		45

/****************************************************************************/
/*  DBT */
/****************************************************************************/

/*  �Z�}�t�H�����l */
#define 	DBT_SEMINIT_IF	1	/* ���ʃf�o�b�O�p�R�[���o�b�N�֐��o�^�r���A�N�Z�X�p */

/*  �Z�}�t�H�ő�l */
#define 	DBT_SEMMAX_IF	1	/* ���ʃf�o�b�O�p�R�[���o�b�N�֐��o�^�r���A�N�Z�X�p */

/*  �^�X�N�X�^�b�N */
#define 	DBT_TSKSTK_DBT_MAIN	0x2000 	/* �f�o�b�O���͎�M�^�X�N�p */

/*  �^�X�N�v���C�I���e�B */
#define 	DBT_TSKPRI_DBT_MAIN	125	/* Bug:4404 */

/****************************************************************************/
/*  MML */
/****************************************************************************/

/*  �Z�}�t�H�����l */
#define 	MML_SEMINIT_PROPLOCK	1	/*  */

/*  �Z�}�t�H�ő�l */
#define 	MML_SEMMAX_PROPLOCK	1	/*  */

/****************************************************************************/
/*  KAOLIB */
/****************************************************************************/
#define		KAO_TSKPRI				97

/****************************************************************************/
/*  SYS */
/****************************************************************************/
// �^�X�N�D��x
#define		M2S_TSKPRI				31
#define		S2M_TSKPRI				31
#define		SYS_CAMDEV_TSKPRI		31
#define		SYS_COM_TSKPRI			33
#define		SYS_CAM_TSKPRI			34
#define		SYS_POWER_TSKPRI		50
#define		SYS_NFC_TSKPRI			51
#define		SYS_EVENT_TSKPRI		63
#define		SYS_EYE_SENSOR_TSKPRI	63
#define		SYS_TPANEL_TSKPRI		63
#define		RMR_TSKPRI				64
#define		DIO_USB_TSKPRI			96
#define		SYS_EVR_TSKPRI			96
#define		SYS_RAM_TSKPRI			97
#define		SYS_CAMHEAD_TSKPRI		97
#define		SYS_ROM_TSKPRI			125
#define		SYS_POWER_SUB_TSKPRI	126
#define 	SYS_UPDATE_TSKPRI		127
#define		DIO_UART_TSKPRI			127

// �����n���h���̎���[ms]
#define		SYS_EVENT_CYCTIM		10
#define		SYS_POVCAM_CYCTIM		20
#define	SYS_ALIVE_MONITOR_CYCTIM	2500

// �������v�[��
#define		SYS_MPF_BLKSZ			80
#define		SYS_MPF_BLKCNT			100
#define		RMR_SREQ_MPLSZ			4096

// CPU��O�n���h���ԍ�
#define SYS_EXCNO_UNDEFINED			0							//!< ����`����
#define SYS_EXCNO_PREFETCH_ABORT	1							//!< �v���t�F�b�`�A�{�[�g
#define SYS_EXCNO_DATA_ABORT		2							//!< �f�[�^�A�{�[�g

// ���荞�ݔԍ�
#define CPU_INTNO_KAO_START			12							//!< �j�`�n�ʐM�J�n������(BE��KAO)
#define CPU_INTNO_KAO_END			12							//!< �j�`�n�ʐM�I��������(KAO��BE)
#define CPU_INTNO_BE_START			13							//!< �a�d�ʐM�J�n������(CAM��BE)
#define CPU_INTNO_BE_END			13							//!< �a�d�ʐM�I��������(BE��CAM)
#define CPU_INTNO_VFR				14							//!< �u�e�q�ʒm������(CAM��BE)
#define CPU_INTNO_CPU1_START		CPU_INTNO_BE_END			//!< CPU1�N�����荞��(BE��CAM)
#define CPU_INTNO_CPU2_START		CPU_INTNO_KAO_START			//!< CPU2�N�����荞��(BE��KAO)
#define CPU_INTNO_CPU3_START		CPU_INTNO_KAO_START			//!< CPU3�N�����荞��(BE<primary>��BE<secondary>)
#define GPIO_INTNO_IRQ0				400							//!< �O���[�q0���荞��
#define GPIO_INTNO_IRQ1				401							//!< �O���[�q1���荞��
#define GPIO_INTNO_IRQ2				402							//!< �O���[�q2���荞��
#define GPIO_INTNO_IRQ3				403							//!< �O���[�q3���荞��
#define GPIO_INTNO_IRQ4				404							//!< �O���[�q4���荞��
#define GPIO_INTNO_IRQ5				405							//!< �O���[�q5���荞��
#define GPIO_INTNO_IRQ6				406							//!< �O���[�q6���荞��
#define GPIO_INTNO_IRQ7				407							//!< �O���[�q7���荞��
#define GPIO_INTNO_IRQ8				408							//!< �O���[�q8���荞��
#define GPIO_INTNO_IRQ9				409							//!< �O���[�q9���荞��
#define GPIO_INTNO_IRQ10			410							//!< �O���[�q10���荞��
#define GPIO_INTNO_IRQ11			411							//!< �O���[�q11���荞��
#define GPIO_INTNO_IRQ12			412							//!< �O���[�q12���荞��
#define GPIO_INTNO_IRQ13			413							//!< �O���[�q13���荞��
#define GPIO_INTNO_IRQ14			414							//!< �O���[�q14���荞��
#define GPIO_INTNO_IRQ15			415							//!< �O���[�q15���荞��
#define GPIO_INTNO_IRQ16			416							//!< �O���[�q16���荞��
#define GPIO_INTNO_IRQ17			417							//!< �O���[�q17���荞��
#define GPIO_INTNO_IRQ18			418							//!< �O���[�q18���荞��
#define GPIO_INTNO_IRQ19			419							//!< �O���[�q19���荞��
#define GPIO_INTNO_IRQ20			420							//!< �O���[�q20���荞��
#define GPIO_INTNO_IRQ21			421							//!< �O���[�q21���荞��
#define GPIO_INTNO_IRQ22			422							//!< �O���[�q22���荞��
#define GPIO_INTNO_IRQ23			423							//!< �O���[�q23���荞��
#define I2C_INTNO_CH0				282							//!< I2C���荞��(ch0)
#define I2C_INTNO_CH1				283							//!< I2C���荞��(ch1)
#define I2C_INTNO_CH2				284							//!< I2C���荞��(ch2)
#define I2C_INTNO_CH3				285							//!< I2C���荞��(ch3)
#define I2C_INTNO_CH4				286							//!< I2C���荞��(ch4)
#define MDMAC_INTNO_CH0				96	// MIU DMAC0 �ʏ�]���p	//!< MDMAC���荞��(ch0) 
#define MDMAC_INTNO_CH1				97							//!< MDMAC���荞��(ch1)
#define MDMAC_INTNO_CH2				98							//!< MDMAC���荞��(ch2)
#define MDMAC_INTNO_CH3				99							//!< MDMAC���荞��(ch3)
#define MDMAC_INTNO_CH4				100							//!< MDMAC���荞��(ch4)
#define MDMAC_INTNO_CH5				101							//!< MDMAC���荞��(ch5)
#define MDMAC_INTNO_CH5_2			109	          // ��`�]���p //!< MDMAC���荞��(ch5)
#define MDMAC_INTNO_RECT			MDMAC_INTNO_CH5_2			//!< MDMAC���荞��(��`�]���p)
#define MDMAC_INTNO_CH6				102							//!< MDMAC���荞��(ch6)
#define MDMAC_INTNO_CH7				103							//!< MDMAC���荞��(ch7)
#define MDMAC_INTNO_CH8				112	// MIU DMAC1 �ʏ�]���p //!< MDMAC���荞��(ch8)
#define MDMAC_INTNO_CH9				113							//!< MDMAC���荞��(ch9)
#define MDMAC_INTNO_CH10			114							//!< MDMAC���荞��(ch10)
#define MDMAC_INTNO_CH11			115							//!< MDMAC���荞��(ch11)
#define MDMAC_INTNO_CH12			116							//!< MDMAC���荞��(ch12)
#define MDMAC_INTNO_CH13			117							//!< MDMAC���荞��(ch13)
#define MDMAC_INTNO_CH14			118							//!< MDMAC���荞��(ch14)
#define MDMAC_INTNO_CH15			119							//!< MDMAC���荞��(ch15)
#define MDMAC_INTNO_CH16			128	// MIU DMAC2 �ʏ�]���p	//!< MDMAC���荞��(ch16)
#define MDMAC_INTNO_CH17			129							//!< MDMAC���荞��(ch17)
#define MDMAC_INTNO_CH18			130							//!< MDMAC���荞��(ch18)
#define MDMAC_INTNO_CH19			131							//!< MDMAC���荞��(ch19)
#define MDMAC_INTNO_CH20			132							//!< MDMAC���荞��(ch20)
#define MDMAC_INTNO_CH21			133							//!< MDMAC���荞��(ch21)
#define MDMAC_INTNO_CH22			134							//!< MDMAC���荞��(ch22)
#define MDMAC_INTNO_CH23			135							//!< MDMAC���荞��(ch23)
#define MDMAC_INTNO_ERR0			157							//!< MIU DMAC0 �G���[���荞��
#define MDMAC_INTNO_ERR1			158							//!< MIU DMAC1 �G���[���荞��
#define MDMAC_INTNO_ERR2			159							//!< MIU DMAC2  �G���[���荞��
#define SSP_INTNO_CH0				70							//!< SSP����M�������荞��(ch0)
#define SSP_INTNO_CH1				73							//!< SSP����M�������荞��(ch1)
#define SSP_INTNO_CH2				76							//!< SSP����M�������荞��(ch2)
#define SSP_INTNO_CH3				79							//!< SSP����M�������荞��(ch3)
#define SSP_INTNO_CH4				82							//!< SSP����M�������荞��(ch4)
#define SSP_INTNO_CH5				288							//!< SSP����M�������荞��(ch5)
#define SSP_INTNO_CH6				291							//!< SSP����M�������荞��(ch6)
#define SSP_RXCOMP_INTNO_CH0		72							//!< SSP��M�������荞��(ch0)
#define SSP_RXCOMP_INTNO_CH1		75							//!< SSP��M�������荞��(ch1)
#define SSP_RXCOMP_INTNO_CH2		78							//!< SSP��M�������荞��(ch2)
#define SSP_RXCOMP_INTNO_CH3		81							//!< SSP��M�������荞��(ch3)
#define SSP_RXCOMP_INTNO_CH4		84							//!< SSP��M�������荞��(ch4)
#define SSP_RXCOMP_INTNO_CH5		290							//!< SSP��M�������荞��(ch5)
#define SSP_RXCOMP_INTNO_CH6		293							//!< SSP��M�������荞��(ch6)
#define TMR_INTNO_CH0				36							//!< �^�C�}���荞��(ch0)
#define TMR_INTNO_CH1				37							//!< �^�C�}���荞��(ch1)
#define TMR_INTNO_CH2				38							//!< �^�C�}���荞��(ch2)
#define TMR_INTNO_CH3				39							//!< �^�C�}���荞��(ch3)
#define TMR_INTNO_CH4				40							//!< �^�C�}���荞��(ch4)
#define TMR_INTNO_CH5				41							//!< �^�C�}���荞��(ch5)
#define TMR_INTNO_CH6				42							//!< �^�C�}���荞��(ch6)
#define TMR_INTNO_CH7				43							//!< �^�C�}���荞��(ch7)
#define TMR_INTNO_CH8				44							//!< �^�C�}���荞��(ch8)
#define TMR_INTNO_CH9				45							//!< �^�C�}���荞��(ch9)
#define TMR_INTNO_CH10				46							//!< �^�C�}���荞��(ch10)
#define TMR_INTNO_CH11				47							//!< �^�C�}���荞��(ch11)
#define TMR_INTNO_CH12				48							//!< �^�C�}���荞��(ch12)
#define TMR_INTNO_CH13				49							//!< �^�C�}���荞��(ch13)
#define TMR_INTNO_CH14				50							//!< �^�C�}���荞��(ch14)
#define TMR_INTNO_CH15				51							//!< �^�C�}���荞��(ch15)
#define TMR_INTNO_CH16				52							//!< �^�C�}���荞��(ch16)
#define TMR_INTNO_CH17				53							//!< �^�C�}���荞��(ch17)
#define TMR_INTNO_CH18				54							//!< �^�C�}���荞��(ch18)
#define TMR_INTNO_CH19				55							//!< �^�C�}���荞��(ch19)
#define TMR_INTNO_CH20				56							//!< �^�C�}���荞��(ch20)
#define TMR_INTNO_CH21				57							//!< �^�C�}���荞��(ch21)
#define TMR_INTNO_CH22				58							//!< �^�C�}���荞��(ch22)
#define TMR_INTNO_CH23				59							//!< �^�C�}���荞��(ch23)
#define TMR_INTNO_CH24				60							//!< �^�C�}���荞��(ch24)
#define TMR_INTNO_CH25				61							//!< �^�C�}���荞��(ch25)
#define UART_INTNO_CH0				85							//!< UART���荞��(ch0)
#define UART_INTNO_CH1				86							//!< UART���荞��(ch1)
#define UART_INTNO_CH2				294							//!< UART���荞��(ch2)
#define UART_INTNO_CH3				295							//!< UART���荞��(ch3)
#define UART_INTNO_CH4				296							//!< UART���荞��(ch4)
#define ICR_INTNO_CH0				64							//!< �L���v�`�����荞��(ch0)
#define ICR_INTNO_CH1				65							//!< �L���v�`�����荞��(ch1)
#define ICR_INTNO_CH2				66							//!< �L���v�`�����荞��(ch2)
#define ICR_INTNO_CH3				67							//!< �L���v�`�����荞��(ch3)
#define ICR_INTNO_CH4				68							//!< �L���v�`�����荞��(ch4)
#define ICR_INTNO_CH5				69							//!< �L���v�`�����荞��(ch5)
#define SDIP_INTNO_CH0				87							//!< SDIP���荞��(ch0)
#define SDIP_INTNO_CH1				89							//!< SDIP���荞��(ch1)
#define SDIP_INTNO_CH2				91							//!< SDIP���荞��(ch2)
#define SDIO_INTNO_CH0				88							//!< SD-IO���荞��(ch0)
#define SDIO_INTNO_CH1				90							//!< SD-IO���荞��(ch1)
#define SDIO_INTNO_CH2				92							//!< SD-IO���荞��(ch2)







/****************************************************************************/
// GUI�Ǘ�
/****************************************************************************/
#define GEVG_INTNO_IRQ1				256							//!< GraphicEngine�������荞��1
#define GEVG_INTNO_IRQ2				257							//!< GraphicEngine�������荞��2
#define GEVG_INTNO_IRQ3				258							//!< GraphicEngine�������荞��3

/****************************************************************************/
/*  AVS */
/****************************************************************************/
/* �^�X�N�D��x */
#define NCS_TSKPRI_SEQ					94			/* AVS��荂�� */
#define	AVS_TSKPRI_MAIN					95
#define	AVS_TSKPRI_DBG_APL				96
#define	AVS_TSKPRI_TEST					97

/* �^�X�N�X�^�b�N */
#define	AVS_TSKSTK_MAIN					0x1000
#define	AVS_TSKSTK_DBG_APL				0x4000
#define	AVS_TSKSTK_TEST					0x4000

/* �Z�}�t�H�����l */
#define AVS_SEMINIT_APILOCK	1
#define AVS_SEMINIT_FLGLOCK	1

/* �Z�}�t�H�ő�l */
#define AVS_SEMMAX_APILOCK 	1
#define AVS_SEMMAX_FLGLOCK 	1

/* �C�x���g�t���O�����l */
#define AVS_FLGINIT_COMTASK			0x00000000	/* ���b�Z�[�W�Z���N�^�p */

/* �ϒ��������v�[���}�N�� */
#define	AVS_MPLSZ_MAIN					(1024*64)
		
/* �Œ蒷�������v�[���}�N�� */
#define	CMS_MPF_BLKCNT_MAIN   100   /* �l���ł��郁�����u���b�N���i���j */
#define	CMS_MPF_BLKSZ_MAIN    96    /* �������u���b�N�̃T�C�Y�i�o�C�g���j */

/****************************************************************************/
/*  HDC */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define	HDC_TSKPRI_MAIN					72		/* HDC Main Task */
#define	HDC_TSKPRI_FLASHACCESS			69		/* Flash Access Task */
#define	HDC_TSKPRI_MEDIAACCESS			66		/* FileSystem Access Task */

/****************************************************************************/
/*  SDP */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
/*====System Core�p====*/
#define	SDC_TSKPRI_SDCS					68
/*====Picture Core�p====*/
#define	SDC_TSKPRI_SDCPC				70
#define	SDC_TSKPRI_SDCPM				75
#define	SDC_TSKPRI_SDCPE				76
/*====Exif Controller�p====*/
#define	SDC_TSKPRI_SDCE					78

/****************************************************************************/
/*  CMR */
/****************************************************************************/

/* �^�X�N�v���C�I���e�B */
#define	CMR_TSKPRI						40

/* �^�X�N�X�^�b�N */
#define	CMR_TSKSTK						1024

/****************************************************************************/

/****************************************************************************/
/*  STC */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define	STC_TSKPRI_SCE					80
#define	STC_TSKPRI_HIGH					56
#define SPC_TSKPRI_MAIN					81

/****************************************************************************/

/****************************************************************************/
/*  SCL */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define	SCL_TSKPRI						24			/* HD1st MetisLib�Ɠ��� */

#define	SCL_TSKSTK						(10*1024)

/*==== �^�X�N�g����� =====*/
#define	RPY_TSK01_IDX		0x00000000
#define	RPY_TSK02_IDX		0x00000001
#define	RPY_TSK03_IDX		0x00000002
#define	RPY_TSK04_IDX		0x00000003
#define	RPY_TSK05_IDX		0x00000004
#define	RPY_TSKLAST_IDX		0x00000005
#define	RPY_TIMERTSK01_IDX	0x00000006

/****************************************************************************/

/****************************************************************************/
/*  VCL */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define	AVFW_TSKPRI_TIMER				24
#define	VCI_TSKPRI						25
#define	AVFW_TSKPRI_VSO_VEN				31			/* Bug4485,Bug4697�΍� */
#define	AVFW_TSKPRI_BACD_DEC			34
#define AVFW_TSKPRI_AVFW_ALIB			40
#define AVFW_TSKPRI_ALIB				40
#define AVFW_TSKPRI_GAIA				30			/* AVFW VEN��1�� */
#define AVFW_TSKPRI_THREAD				42
#define	AVFW_TSKPRI_BACD_ENC			43
#define	VCL_TSKPRI_MAIN					44			/* AVDF�^�X�N��艺�� */
#define	VCL_TSKPRI_SUB					45
#define VCL_TSKPRI_CHIPCOMMUNICATE		39
	
/* SMP�֘A */
#if defined( ALLOPT_OS_SMP ) && defined( ALLOPT_MAINCHIP )
#define AVFW_RUN_CPU	3	/* AVFW����CPU */
#endif

/****************************************************************************/

/****************************************************************************/
/*  CFS */
/****************************************************************************/

/*==== �^�X�N�D��x ======*/
#define	CFS_TSKPRI_FAT			57
#define	CFS_TSKPRI_UDF			56

// 20070703 TU FAT�^�X�N��ǉ�
#define	CFS_TSKPRI_FAT2			57

#define	CFS_TSKPRI_FROM			56
#define	CFS_TSKPRI_INT			121

/* HDD����p */
#define	CFS_TSKPRI_HIGH			55		/* FAT�p�^�X�N����ł��邱�� */
#define	CFS_TSKPRI_HDD_IDLIMM	115		/* �~�h���ň�ԒႭ���Ă��� */

/* �����c�ʌv�Z�p�^�X�N */
#define CFS_TSKPRI_GETFS		58

/****************************************************************************/
/*  USB */
/****************************************************************************/
/*  �^�X�N�v���C�I���e�B */
#define USB_TSKPRI_MAIN 				  54
#define USB_TSKPRI_UOH  				  114
#define USB_TSKPRI_MASS_S  				  84
#define USB_TSKPRI_MASS_H  				  84			/* 2007/07/31 �ǉ� */
#define USB_TSKPRI_VD_STREAM			  84			/* STC, CFS���Ђ����ݒ� AKB�̂Ƃ� */
#define USB_TSKPRI_AD_STREAM			  30			/* AVIO��荂�� */

#define USBHD_TSKPRI_EVENT				  53 /* USB_TSKPRI_MAIN ��荂�� */
#define USBHD_CONFIG_MPLSZ				1024

/* �����ݔԍ� */
#define USBIP_INTNO						 151	/* USBIP(USB_IRQ2) */
#define USBIP_INTNO_PERI	USBIP_INTNO			/* �y���t�F�����p */
#define USBIP_INTNO_HOST	USBIP_INTNO			/* �z�X�g�p */

/****************************************************************************/
/* GUI */
/****************************************************************************/

	/* GDI�^�X�N�D��x */
	#define GUI_TSKPRI						  70

	/* �^�C���X�^���v�f�[�^�X�V�^�X�N�D��x */
    #define GUI_TS_TSKPRI				      71	/* �ׂ��΍��MDC���ЂƂ� */
	
	/* ��ʕ`��^�X�N�D��x */
	#define CT_MAIN_TSKPRI					118	/* ��APL�`��^�X�N�Ɠ����x */
	
	/* ���t���[���`��^�X�N�D��x */
	#define CT_DRAW_TSKPRI                 46 /* 40����ύX STC��艺�� */

	/* ���`��^�X�N�D��x */
	#define	GUI_TSKPRI_LINE			  119	/* APL_MAIN_TSKPRI(120)���1�������� */

	/* DMP���C�u�����^�X�N�D��x */
	#define DMP_MAIN_TSKPRI                   39

	/* DMA�����҂��^�X�N�D��x */
    #define GUI_DMA_TSKPRI				123	/* TS�^�X�N��荂�� */
	
/* �����݃��x�� */
#define 	GIH_INTLVL	GRP108INTLVL

/* �����ݔԍ� */
#define 	GIH_INTNO	GRP108INTNO

/* HTK�ϒ��������v�[���T�C�Y */
#define HTK_MPLSIZE 0x20000

/****************************************************************************/

/****************************************************************************/
/* HDMI */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define	HDM_TSKPRI_BASE				40		/* HDMI Task */

#define CEC_TSKPRI_SYS				62		/* CECSYS Task */
#define CEC_TSKPRI_IF				58		/* CECIF Task */
#define CEC_TSKPRI_DD				35		/* CECDD Task */


/****************************************************************************/

/****************************************************************************/
/* KAO */
/****************************************************************************/
/*
 *	�^�X�N�D��x
 */
#define	KAO_IMAGE_TSKPRI			36
#define	KAO_KDET_TSKPRI				37
#define	KAO_TRCK_TSKPRI				38

/*
 *	�^�X�N�X�^�b�N�T�C�Y
 */
#define	KAO_IMAGE_TSKSTK			0x1000
#define	KAO_KDET_TSKSTK				0x4000
#define	KAO_TRCK_TSKSTK				0x1000

/*
 *	���荞��NO
 */
#define	KAO_IRQ_NO_ODU				298

/****************************************************************************/

/****************************************************************************/
/* IIS/IUC */
/****************************************************************************/
/* �^�X�N�D��x */
#define	IUC_TSKPRI		98	
/* �^�X�N�X�^�b�N�T�C�Y */
#define IUC_TSK_STK		0x2000

/****************************************************************************/

/****************************************************************************/
/* UIO */
/****************************************************************************/
#define		UIO_TASKPRI				96
#define		UIO_EVENT_TASKPRI		65
#define		UIOF_DRV_TASKPRI		123

/****************************************************************************/

/****************************************************************************/
/* FACT */
/****************************************************************************/
#define		FACT_TSKPRI				123

#define		FACT_MPF_BLKSZ			64
#define		FACT_MPF_BLKCNT			30

/****************************************************************************/

/****************************************************************************/
/* APL */
/****************************************************************************/
#define		APL_EVENT_TSKPRI		110
#define		APL_HIGH_TSKPRI			112
#define		APL_MIDDLE_TSKPRI		113
#define		APL_MIDDLE_SUB_TSKPRI	114
#define		APL_CLOCK_TSKPRI		115
#define		APL_LOW1_TSKPRI			116
#define		APL_LOW2_TSKPRI			117
#define		APL_LOW3_TSKPRI			118
#define		APL_MAIN_TSKPRI			120
#define		APL_ANIMATION_TSKPRI	74		/* = AMS_TSKPRI */

#define		APL_MOUNT_TSKPRI			CFS_TSKPRI_FAT2

/****************************************************************************/

/****************************************************************************/
/* NWA */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define NWA_TSKPRI_RECV		59
#define NWA_TSKPRI_SEND		59
#define NWA_TSKPRI_BOOT		59
	
/*==== �����ݔԍ� ======*/
#define NWA_INTNO_COMM		SPICA_INTNO_IRC2_DINT1

/****************************************************************************/
/* NWB */
/****************************************************************************/
/*==== �^�X�N�D��x ======*/
#define		NWB_EVENTTSK_PRI		65


/****************************************************************************/
/*									TCC ID									*/
/****************************************************************************/

#define	TCC_USER_ENTRY_ID_000	0	/* CAM */
#define	TCC_USER_ENTRY_ID_001	1	/* CAM */
#define	TCC_USER_ENTRY_ID_002	2	/* CAM */
#define	TCC_USER_ENTRY_ID_003	3	/* CAM */
#define	TCC_USER_ENTRY_ID_004	4	/* CAM */
#define	TCC_USER_ENTRY_ID_005	5	/* CAM */
#define	TCC_USER_ENTRY_ID_006	6	/* CAM */
#define	TCC_USER_ENTRY_ID_007	7	/* CAM */
#define	TCC_USER_ENTRY_ID_008	8	/* CAM */
#define	TCC_USER_ENTRY_ID_009	9	/* CAM */
#define	TCC_USER_ENTRY_ID_010	10	/* CAM */
#define	TCC_USER_ENTRY_ID_011	11	/* CAM */
#define	TCC_USER_ENTRY_ID_012	12	/* CAM */
#define	TCC_USER_ENTRY_ID_013	13	/* CAM */
#define	TCC_USER_ENTRY_ID_014	14	/* CAM */
#define	TCC_USER_ENTRY_ID_015	15	/* CAM */
#define	TCC_USER_ENTRY_ID_016	16	/* CAM */
#define	TCC_USER_ENTRY_ID_017	17	/* CAM */
#define	TCC_USER_ENTRY_ID_018	18	/* CAM */
#define	TCC_USER_ENTRY_ID_019	19	/* CAM */
#define	TCC_USER_ENTRY_ID_020	20	/* CAM */
#define	TCC_USER_ENTRY_ID_021	21	/* CAM */
#define	TCC_USER_ENTRY_ID_022	22	/* CAM */
#define	TCC_USER_ENTRY_ID_023	23	/* CAM */
#define	TCC_ID_VCL_MS			24	/* STC */
#define	TCC_ID_VCL_SM			25	/* STC */
#define	TCC_ID_AVFW_ES0_SM		26	/* AVFW */
#define	TCC_ID_AVFW_ES1_SM		27	/* AVFW */
#define	TCC_ID_AVFW_ES_MS		28	/* AVFW */
#define	TCC_USER_ENTRY_ID_029	29	/* GUI */
#define	TCC_USER_ENTRY_ID_030	30	/* GUI */
#define	TCC_USER_ENTRY_ID_031	31	/* GUI */
#define	TCC_USER_ENTRY_ID_032	32	/* AVC */
#define	TCC_USER_ENTRY_ID_033	33	/* AVC */
#define	TCC_USER_ENTRY_ID_034	34	/* AVC */
#define	TCC_USER_ENTRY_ID_035	35	/* AVC */
#define	TCC_USER_ENTRY_ID_036	36	/* AVC */
#define	TCC_USER_ENTRY_ID_037	37	/* AVC */
#define	TCC_USER_ENTRY_ID_038	38	/* AVC */
#define	TCC_USER_ENTRY_ID_039	39	/* AVC */
#define	TCC_USER_ENTRY_ID_040	40	/* AVC */
#define	TCC_USER_ENTRY_ID_041	41	/* AVC */
#define	TCC_USER_ENTRY_ID_042	42	/* AVC */
#define	TCC_USER_ENTRY_ID_043	43	/* AVC */
#define	TCC_USER_ENTRY_ID_044	44	/* AVC */
#define	TCC_USER_ENTRY_ID_045	45	/* AVC */
#define	TCC_USER_ENTRY_ID_046	46	/* AVC */
#define	TCC_USER_ENTRY_ID_047	47	/* AVC */
#define	TCC_USER_ENTRY_ID_048	48	/* AVC */
#define	TCC_USER_ENTRY_ID_049	49	/* AVC */
#define	TCC_USER_ENTRY_ID_050	50	/* AVC */
#define	TCC_USER_ENTRY_ID_051	51	/* AVC */
#define	TCC_USER_ENTRY_ID_052	52	/* AVC */
#define	TCC_USER_ENTRY_ID_053	53	/* AVC */
#define	TCC_USER_ENTRY_ID_054	54	/* AVC */
#define	TCC_USER_ENTRY_ID_055	55	/* AVC */
#define	TCC_USER_ENTRY_ID_056	56	/* AVC */
#define	TCC_USER_ENTRY_ID_057	57	/* AVC */
#define	TCC_USER_ENTRY_ID_058	58	/* AVC */
#define	TCC_USER_ENTRY_ID_059	59	/* AVC */
#define	TCC_USER_ENTRY_ID_060	60	/* AVC */
#define	TCC_USER_ENTRY_ID_061	61	/* AVC */
#define	TCC_USER_ENTRY_ID_062	62	/* AVC */
#define	TCC_USER_ENTRY_ID_063	63	/* AVC */
#define	TCC_USER_ENTRY_ID_064	64	/* AVC */
#define	TCC_USER_ENTRY_ID_065	65	/* AVC */
#define	TCC_USER_ENTRY_ID_066	66	/* AVC */
#define	TCC_USER_ENTRY_ID_067	67	/* AVC */
#define	TCC_USER_ENTRY_ID_068	68	/* AVC */
#define	TCC_USER_ENTRY_ID_069	69	/* AVC */
#define	TCC_USER_ENTRY_ID_070	70	/* AVC */
#define	TCC_USER_ENTRY_ID_071	71	/* AVC */
#define	TCC_USER_ENTRY_ID_072	72	/* AVC */
#define	TCC_USER_ENTRY_ID_073	73	/* AVC */
#define	TCC_USER_ENTRY_ID_074	74	/* AVC */
#define	TCC_USER_ENTRY_ID_075	75	/* AVC */
#define	TCC_USER_ENTRY_ID_076	76	/* AVC */
#define	TCC_USER_ENTRY_ID_077	77	/* AVC */
#define	TCC_USER_ENTRY_ID_078	78	/* AVC */
#define	TCC_USER_ENTRY_ID_079	79	/* AVC */
#define	TCC_USER_ENTRY_ID_080	80	/* HDMI */
#define	TCC_USER_ENTRY_ID_081	81	/* HDMI */
#define	TCC_USER_ENTRY_ID_082	82	/* HDMI */
#define	TCC_USER_ENTRY_ID_083	83	/* HDMI */
#define	TCC_USER_ENTRY_ID_084	84	/* GUI */
#define	TCC_USER_ENTRY_ID_085	85	/* GUI */
#define	TCC_USER_ENTRY_ID_086	86	/* GUI */
#define	TCC_USER_ENTRY_ID_087	87	/* GUI */
#define	TCC_USER_ENTRY_ID_088	88	/* GUI */
#define	TCC_ID_VCL_AUDIO		89	/* VCL */
#define	TCC_ID_VCL_STREAM		90	/* VCL */
#define	TCC_ID_VCL_OB			91	/* VCL */
#define	TCC_USER_ENTRY_ID_092	92	/* ���g�p */
#define	TCC_USER_ENTRY_ID_093	93	/* ���g�p */
#define	TCC_USER_ENTRY_ID_094	94	/* ���g�p */
#define	TCC_USER_ENTRY_ID_095	95	/* ���g�p */
#define	TCC_USER_ENTRY_ID_096	96	/* ���g�p */
#define	TCC_USER_ENTRY_ID_097	97	/* ���g�p */
#define	TCC_USER_ENTRY_ID_098	98	/* ���g�p */
#define	TCC_USER_ENTRY_ID_099	99	/* ���g�p */
#define	TCC_USER_ENTRY_ID_100	100	/* ���g�p */
#define	TCC_USER_ENTRY_ID_101	101	/* ���g�p */
#define	TCC_USER_ENTRY_ID_102	102	/* ���g�p */
#define	TCC_USER_ENTRY_ID_103	103	/* ���g�p */
#define	TCC_USER_ENTRY_ID_104	104	/* ���g�p */
#define	TCC_USER_ENTRY_ID_105	105	/* ���g�p */
#define	TCC_USER_ENTRY_ID_106	106	/* ���g�p */
#define	TCC_USER_ENTRY_ID_107	107	/* ���g�p */
#define	TCC_USER_ENTRY_ID_108	108	/* ���g�p */
#define	TCC_USER_ENTRY_ID_109	109	/* ���g�p */
#define	TCC_USER_ENTRY_ID_110	110	/* ���g�p */
#define	TCC_USER_ENTRY_ID_111	111	/* ���g�p */
#define	TCC_USER_ENTRY_ID_112	112	/* ���g�p */
#define	TCC_USER_ENTRY_ID_113	113	/* ���g�p */
#define	TCC_USER_ENTRY_ID_114	114	/* ���g�p */
#define	TCC_USER_ENTRY_ID_115	115	/* ���g�p */
#define	TCC_USER_ENTRY_ID_116	116	/* ���g�p */
#define	TCC_USER_ENTRY_ID_117	117	/* ���g�p */
#define	TCC_USER_ENTRY_ID_118	118	/* ���g�p */
#define	TCC_USER_ENTRY_ID_119	119	/* ���g�p */
#define	TCC_USER_ENTRY_ID_120	120	/* ���g�p */
#define	TCC_USER_ENTRY_ID_121	121	/* ���g�p */
#define	TCC_USER_ENTRY_ID_122	122	/* ���g�p */
#define	TCC_USER_ENTRY_ID_123	123	/* ���g�p */
#define	TCC_USER_ENTRY_ID_124	124	/* ���g�p */
#define	TCC_USER_ENTRY_ID_125	125	/* ���g�p */
#define	TCC_USER_ENTRY_ID_126	126	/* ���g�p */
#define	TCC_USER_ENTRY_ID_127	127	/* ���g�p */

#define	TCC_USER_ENTRY_ID_NM	( TCC_ID_VCL_OB + 1 )	/* �g�pID�� */

#ifdef __cplusplus
}
#endif

#endif /*  __OS_H__ */
