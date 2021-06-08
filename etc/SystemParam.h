/***************************************************************************/
/*　ファイル名  ：SystemParam.h                                            */
/*　概要        ：OS資源情報ヘッダファイル                                 */
/* Copyright(c)2005-2006 by Matsushita Electric Industrial Co., Ltd.       */
/***************************************************************************/
/***************************************************************************/

#ifndef __OS_H__
#define __OS_H__



#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
/* 変更履歴 */
/* バージョン 	更新内容 	変更者 	更新日	*/
/****************************************************************************/
/****************************************************************************/

/****************************************************************************/

/* Macro定義 */

/****************************************************************************/

/****************************************************************************/
/*  PF差分吸収								                                */
/****************************************************************************/

/**
 * @brief		ソフトブレークを発生させる
 */
#define SOFT_BREAK() __breakpoint(0)

/**
 * @brief		割り込みハンドラ静的登録用マクロ
 * @details		登録する割り込みハンドラの形式
 *				
 *				void handler(INT_PARAM)
 *				{
 *					// 割り込み処理
 *				}
 *				
 * @param[in]	intno	割り込み番号
 * @param[in]	handler	登録するハンドラ
 */
#define CRE_INT(intno, handler)  DEF_INH(intno, {TA_HLNG, handler})

/**
 * @brief		割り込みハンドラの引数
 */
#define INT_PARAM void

/**
 * @brief		システム時刻取得
 * @param[out]	time	システム時刻の格納先(UW型)
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
#define	FREERUN_TMR_CH			TMR_CH10	// TMR_Wait()用
#define	KAO_TMR_CH				TMR_CH11

#define	CAM_1MS_TMR_CH			TMR_CH12
#define	CAM_AF1_TMR_CH			TMR_CH13
#define	CAM_AF2_TMR_CH			TMR_CH14
#define	CAM_SUB_TMR_CH			TMR_CH15
//#define						TMR_CH16
//#define						TMR_CH17
//#define						TMR_CH18
//#define						TMR_CH19

//#define						TMR_CH20	// Linux用
//#define						TMR_CH21	// Linux用
//#define						TMR_CH22	// Linux用
//#define						TMR_CH23	// Linux用

//#define						TMR_CH24	// ThreadX用
//#define						TMR_CH25	// ThreadX用

/****************************************************************************/
/* チップ間シリアル通信ID */
/****************************************************************************/
/*==== CH0（Main←Sub） ======*/
#define M2S_ID_SM_TOP				0
#define M2S_ID_SYS_NFC_SMS			0		// SYSブロック NFC通信用
#define M2S_ID_SYS_NFC_SMM			1		// SYSブロック NFC通信用
#define M2S_ID_SYS_NFC_SML			2		// SYSブロック NFC通信用
#define M2S_ID_VOU_SM				3		// VOUレジスタ設定
#define M2S_ID_VCL_SM_S				4		// VCLチップ間通信
#define M2S_ID_VCL_SM_L				5		// VCLチップ間通信
#define M2S_ID_AVFW_VEN2_CORE_SM	6		// core間情報（VEN0←VEN2）
#define M2S_ID_AVFW_VEN2_BACD_SM	7		// bacd間情報（VEN0←VEN2）
#define M2S_ID_AVFW_VEN3_CORE_SM	8		// core間情報（VEN0←VEN3）
#define M2S_ID_AVFW_VEN3_BACD_SM	9		// bacd間情報（VEN0←VEN3）
#define M2S_ID_AVFW_VSI_READY_OUTPUT_SM	10		// 画像準備完了（main←sub）
#define M2S_ID_AVFW_VSI_READY_RESIZE_SM	11		// リサイズ準備完了（main←sub）
#define M2S_ID_SM_BOTTOM				11

/*==== CH1（Main→Sub） ======*/
#define M2S_ID_MS_TOP				64
#define M2S_ID_SYS_NFC_MSS			64		// SYSブロック NFC通信用
#define M2S_ID_SYS_NFC_MSM			65		// SYSブロック NFC通信用
#define M2S_ID_SYS_NFC_MSL			66		// SYSブロック NFC通信用
#define M2S_ID_SUB_PORT				67		// SUBブロック 端子情報通信用
#define M2S_ID_VOU_MS				68		// VOUレジスタ設定
#define M2S_ID_VCL_MS_S				69		// VCLチップ間通信
#define M2S_ID_VCL_MS_L				70		// VCLチップ間通信
#define M2S_ID_AVFW_VEN2_CORE_MS	71		// core間情報（VEN0→VEN2）
#define M2S_ID_AVFW_VEN2_BACD_MS	72		// bacd間情報（VEN0→VEN2）
#define M2S_ID_AVFW_VEN3_CORE_MS	73		// core間情報（VEN0→VEN3）
#define M2S_ID_AVFW_VEN3_BACD_MS	74		// bacd間情報（VEN0→VEN3）
#define M2S_ID_AVFW_VSI_READY_OUTPUT_MS	75		// 画像準備完了（main→sub）
#define M2S_ID_AVFW_VSI_OUTPUT_MS		76		// 時刻補正（main→sub）
#define M2S_ID_AVFW_VSI_READY_RESIZE_MS	77		// リサイズ準備完了（main←sub）
#define M2S_ID_MS_BOTTOM				77


/****************************************************************************/
/*  AVIO */
/****************************************************************************/
/*==== タスク優先度 ======*/
#define 	AVDCAM_TSKPRI				29
#define 	AVD_THREAD_TSKPRI			31
#define 	AVDF_TSKPRI					32
#define 	AVDA_TSKPRI					35
#define 	AVC_DRAW_TSKPRI				126

/*==== 割り込み番号 ======*/
#define	AVC_INTNO_SSG_IVD				396		//	VideoVD前エッジ_2
#define	AVC_INTNO_SSG_IVD_inv			197		//	VideoVD後エッジ

#define	AVC_INTNO_VOU_HDMIVD_IRQ0		224		//	HDMI_VD割込み0_1
#define	AVC_INTNO_VOU_HDMI_REG_IRQ		226		//	HDMI_PRO_VD割込み_1
#define	AVC_INTNO_VOU_LCDVD_0			230		//	LCD_VD割込み0
#define	AVC_INTNO_VOU_LCDVD_1			231		//	LCD_VD割込み1
#define	AVC_INTNO_VOU_MONW_IRQ0			254		//	MONW完了割り込み
#define	AVC_INTNO_VOU_MONW_IRQ1			255		//	MONWエラー割り込み
#define	AVC_INTNO_VOU_LCD_OVFLG_IRQ		228		//	MONT_PROバッファアンダー
#define	AVC_INTNO_VOU_MONL_IRQ			252		//	MONLバッファアンダー
#define	AVC_INTNO_VOU_MONT_IRQ			253		//	MONTバッファアンダー

#define	AVC_INTNO_YCU_YCM_IRQ_F			240		//	FG処理終了
#define	AVC_INTNO_YCU_YCM_IRQ_B			242		//	BG処理終了
#define	AVC_INTNO_YCU_AM_IRQ			244		//	YCU(AM)処理終了

#define	AVC_INTNO_FRU_PD14_IRQ			246		//	FRU終了割り込み(PD14)
#define	AVC_INTNO_FRU_PD15_IRQ			247		//	FRU終了割り込み(PD15)
#define	AVC_INTNO_FRU_PD16_IRQ			248		//	FRU終了割り込み(PD16)

#define	AVC_INTNO_PPU_PPU_IRQ			211		//	PPU終了割り込み

#define	AVC_INTNO_ADU_1					176		//	ADU制御用割り込み1（DRam書込終了通知）
#define	AVC_INTNO_ADU_2					177		//	ADU制御用割り込み2（DRam読出終了通知(MON)）
#define	AVC_INTNO_ADU_3					178		//	ADU制御用割り込み3（DRam読出終了通知）
#define	AVC_INTNO_APU_IRQOUT_1			183		//	オーディオバッファ書込完了割込１
#define	AVC_INTNO_APU0_AUX				184		//	APP0補助割込フラグ
#define	AVC_INTNO_APU1_AUX				185		//	APP1補助割込フラグ

#define AVC_INTNO_CAM_YC_START_IRQ		9		//	CAM YC開始通知(CAM→BE)


/****************************************************************************/
/*  DDD */
/****************************************************************************/
/*==== タスク優先度 ======*/
#define 	DDD_TSKPRI_ASYNC	46
#define 	DDD_TSKPRI_BG		45

/****************************************************************************/
/*  DBT */
/****************************************************************************/

/*  セマフォ初期値 */
#define 	DBT_SEMINIT_IF	1	/* 共通デバッグ用コールバック関数登録排他アクセス用 */

/*  セマフォ最大値 */
#define 	DBT_SEMMAX_IF	1	/* 共通デバッグ用コールバック関数登録排他アクセス用 */

/*  タスクスタック */
#define 	DBT_TSKSTK_DBT_MAIN	0x2000 	/* デバッグ入力受信タスク用 */

/*  タスクプライオリティ */
#define 	DBT_TSKPRI_DBT_MAIN	125	/* Bug:4404 */

/****************************************************************************/
/*  MML */
/****************************************************************************/

/*  セマフォ初期値 */
#define 	MML_SEMINIT_PROPLOCK	1	/*  */

/*  セマフォ最大値 */
#define 	MML_SEMMAX_PROPLOCK	1	/*  */

/****************************************************************************/
/*  KAOLIB */
/****************************************************************************/
#define		KAO_TSKPRI				97

/****************************************************************************/
/*  SYS */
/****************************************************************************/
// タスク優先度
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

// 周期ハンドラの周期[ms]
#define		SYS_EVENT_CYCTIM		10
#define		SYS_POVCAM_CYCTIM		20
#define	SYS_ALIVE_MONITOR_CYCTIM	2500

// メモリプール
#define		SYS_MPF_BLKSZ			80
#define		SYS_MPF_BLKCNT			100
#define		RMR_SREQ_MPLSZ			4096

// CPU例外ハンドラ番号
#define SYS_EXCNO_UNDEFINED			0							//!< 未定義命令
#define SYS_EXCNO_PREFETCH_ABORT	1							//!< プリフェッチアボート
#define SYS_EXCNO_DATA_ABORT		2							//!< データアボート

// 割り込み番号
#define CPU_INTNO_KAO_START			12							//!< ＫＡＯ通信開始割込み(BE→KAO)
#define CPU_INTNO_KAO_END			12							//!< ＫＡＯ通信終了割込み(KAO→BE)
#define CPU_INTNO_BE_START			13							//!< ＢＥ通信開始割込み(CAM→BE)
#define CPU_INTNO_BE_END			13							//!< ＢＥ通信終了割込み(BE→CAM)
#define CPU_INTNO_VFR				14							//!< ＶＦＲ通知割込み(CAM→BE)
#define CPU_INTNO_CPU1_START		CPU_INTNO_BE_END			//!< CPU1起動割り込み(BE→CAM)
#define CPU_INTNO_CPU2_START		CPU_INTNO_KAO_START			//!< CPU2起動割り込み(BE→KAO)
#define CPU_INTNO_CPU3_START		CPU_INTNO_KAO_START			//!< CPU3起動割り込み(BE<primary>→BE<secondary>)
#define GPIO_INTNO_IRQ0				400							//!< 外部端子0割り込み
#define GPIO_INTNO_IRQ1				401							//!< 外部端子1割り込み
#define GPIO_INTNO_IRQ2				402							//!< 外部端子2割り込み
#define GPIO_INTNO_IRQ3				403							//!< 外部端子3割り込み
#define GPIO_INTNO_IRQ4				404							//!< 外部端子4割り込み
#define GPIO_INTNO_IRQ5				405							//!< 外部端子5割り込み
#define GPIO_INTNO_IRQ6				406							//!< 外部端子6割り込み
#define GPIO_INTNO_IRQ7				407							//!< 外部端子7割り込み
#define GPIO_INTNO_IRQ8				408							//!< 外部端子8割り込み
#define GPIO_INTNO_IRQ9				409							//!< 外部端子9割り込み
#define GPIO_INTNO_IRQ10			410							//!< 外部端子10割り込み
#define GPIO_INTNO_IRQ11			411							//!< 外部端子11割り込み
#define GPIO_INTNO_IRQ12			412							//!< 外部端子12割り込み
#define GPIO_INTNO_IRQ13			413							//!< 外部端子13割り込み
#define GPIO_INTNO_IRQ14			414							//!< 外部端子14割り込み
#define GPIO_INTNO_IRQ15			415							//!< 外部端子15割り込み
#define GPIO_INTNO_IRQ16			416							//!< 外部端子16割り込み
#define GPIO_INTNO_IRQ17			417							//!< 外部端子17割り込み
#define GPIO_INTNO_IRQ18			418							//!< 外部端子18割り込み
#define GPIO_INTNO_IRQ19			419							//!< 外部端子19割り込み
#define GPIO_INTNO_IRQ20			420							//!< 外部端子20割り込み
#define GPIO_INTNO_IRQ21			421							//!< 外部端子21割り込み
#define GPIO_INTNO_IRQ22			422							//!< 外部端子22割り込み
#define GPIO_INTNO_IRQ23			423							//!< 外部端子23割り込み
#define I2C_INTNO_CH0				282							//!< I2C割り込み(ch0)
#define I2C_INTNO_CH1				283							//!< I2C割り込み(ch1)
#define I2C_INTNO_CH2				284							//!< I2C割り込み(ch2)
#define I2C_INTNO_CH3				285							//!< I2C割り込み(ch3)
#define I2C_INTNO_CH4				286							//!< I2C割り込み(ch4)
#define MDMAC_INTNO_CH0				96	// MIU DMAC0 通常転送用	//!< MDMAC割り込み(ch0) 
#define MDMAC_INTNO_CH1				97							//!< MDMAC割り込み(ch1)
#define MDMAC_INTNO_CH2				98							//!< MDMAC割り込み(ch2)
#define MDMAC_INTNO_CH3				99							//!< MDMAC割り込み(ch3)
#define MDMAC_INTNO_CH4				100							//!< MDMAC割り込み(ch4)
#define MDMAC_INTNO_CH5				101							//!< MDMAC割り込み(ch5)
#define MDMAC_INTNO_CH5_2			109	          // 矩形転送用 //!< MDMAC割り込み(ch5)
#define MDMAC_INTNO_RECT			MDMAC_INTNO_CH5_2			//!< MDMAC割り込み(矩形転送用)
#define MDMAC_INTNO_CH6				102							//!< MDMAC割り込み(ch6)
#define MDMAC_INTNO_CH7				103							//!< MDMAC割り込み(ch7)
#define MDMAC_INTNO_CH8				112	// MIU DMAC1 通常転送用 //!< MDMAC割り込み(ch8)
#define MDMAC_INTNO_CH9				113							//!< MDMAC割り込み(ch9)
#define MDMAC_INTNO_CH10			114							//!< MDMAC割り込み(ch10)
#define MDMAC_INTNO_CH11			115							//!< MDMAC割り込み(ch11)
#define MDMAC_INTNO_CH12			116							//!< MDMAC割り込み(ch12)
#define MDMAC_INTNO_CH13			117							//!< MDMAC割り込み(ch13)
#define MDMAC_INTNO_CH14			118							//!< MDMAC割り込み(ch14)
#define MDMAC_INTNO_CH15			119							//!< MDMAC割り込み(ch15)
#define MDMAC_INTNO_CH16			128	// MIU DMAC2 通常転送用	//!< MDMAC割り込み(ch16)
#define MDMAC_INTNO_CH17			129							//!< MDMAC割り込み(ch17)
#define MDMAC_INTNO_CH18			130							//!< MDMAC割り込み(ch18)
#define MDMAC_INTNO_CH19			131							//!< MDMAC割り込み(ch19)
#define MDMAC_INTNO_CH20			132							//!< MDMAC割り込み(ch20)
#define MDMAC_INTNO_CH21			133							//!< MDMAC割り込み(ch21)
#define MDMAC_INTNO_CH22			134							//!< MDMAC割り込み(ch22)
#define MDMAC_INTNO_CH23			135							//!< MDMAC割り込み(ch23)
#define MDMAC_INTNO_ERR0			157							//!< MIU DMAC0 エラー割り込み
#define MDMAC_INTNO_ERR1			158							//!< MIU DMAC1 エラー割り込み
#define MDMAC_INTNO_ERR2			159							//!< MIU DMAC2  エラー割り込み
#define SSP_INTNO_CH0				70							//!< SSP送受信完了割り込み(ch0)
#define SSP_INTNO_CH1				73							//!< SSP送受信完了割り込み(ch1)
#define SSP_INTNO_CH2				76							//!< SSP送受信完了割り込み(ch2)
#define SSP_INTNO_CH3				79							//!< SSP送受信完了割り込み(ch3)
#define SSP_INTNO_CH4				82							//!< SSP送受信完了割り込み(ch4)
#define SSP_INTNO_CH5				288							//!< SSP送受信完了割り込み(ch5)
#define SSP_INTNO_CH6				291							//!< SSP送受信完了割り込み(ch6)
#define SSP_RXCOMP_INTNO_CH0		72							//!< SSP受信完了割り込み(ch0)
#define SSP_RXCOMP_INTNO_CH1		75							//!< SSP受信完了割り込み(ch1)
#define SSP_RXCOMP_INTNO_CH2		78							//!< SSP受信完了割り込み(ch2)
#define SSP_RXCOMP_INTNO_CH3		81							//!< SSP受信完了割り込み(ch3)
#define SSP_RXCOMP_INTNO_CH4		84							//!< SSP受信完了割り込み(ch4)
#define SSP_RXCOMP_INTNO_CH5		290							//!< SSP受信完了割り込み(ch5)
#define SSP_RXCOMP_INTNO_CH6		293							//!< SSP受信完了割り込み(ch6)
#define TMR_INTNO_CH0				36							//!< タイマ割り込み(ch0)
#define TMR_INTNO_CH1				37							//!< タイマ割り込み(ch1)
#define TMR_INTNO_CH2				38							//!< タイマ割り込み(ch2)
#define TMR_INTNO_CH3				39							//!< タイマ割り込み(ch3)
#define TMR_INTNO_CH4				40							//!< タイマ割り込み(ch4)
#define TMR_INTNO_CH5				41							//!< タイマ割り込み(ch5)
#define TMR_INTNO_CH6				42							//!< タイマ割り込み(ch6)
#define TMR_INTNO_CH7				43							//!< タイマ割り込み(ch7)
#define TMR_INTNO_CH8				44							//!< タイマ割り込み(ch8)
#define TMR_INTNO_CH9				45							//!< タイマ割り込み(ch9)
#define TMR_INTNO_CH10				46							//!< タイマ割り込み(ch10)
#define TMR_INTNO_CH11				47							//!< タイマ割り込み(ch11)
#define TMR_INTNO_CH12				48							//!< タイマ割り込み(ch12)
#define TMR_INTNO_CH13				49							//!< タイマ割り込み(ch13)
#define TMR_INTNO_CH14				50							//!< タイマ割り込み(ch14)
#define TMR_INTNO_CH15				51							//!< タイマ割り込み(ch15)
#define TMR_INTNO_CH16				52							//!< タイマ割り込み(ch16)
#define TMR_INTNO_CH17				53							//!< タイマ割り込み(ch17)
#define TMR_INTNO_CH18				54							//!< タイマ割り込み(ch18)
#define TMR_INTNO_CH19				55							//!< タイマ割り込み(ch19)
#define TMR_INTNO_CH20				56							//!< タイマ割り込み(ch20)
#define TMR_INTNO_CH21				57							//!< タイマ割り込み(ch21)
#define TMR_INTNO_CH22				58							//!< タイマ割り込み(ch22)
#define TMR_INTNO_CH23				59							//!< タイマ割り込み(ch23)
#define TMR_INTNO_CH24				60							//!< タイマ割り込み(ch24)
#define TMR_INTNO_CH25				61							//!< タイマ割り込み(ch25)
#define UART_INTNO_CH0				85							//!< UART割り込み(ch0)
#define UART_INTNO_CH1				86							//!< UART割り込み(ch1)
#define UART_INTNO_CH2				294							//!< UART割り込み(ch2)
#define UART_INTNO_CH3				295							//!< UART割り込み(ch3)
#define UART_INTNO_CH4				296							//!< UART割り込み(ch4)
#define ICR_INTNO_CH0				64							//!< キャプチャ割り込み(ch0)
#define ICR_INTNO_CH1				65							//!< キャプチャ割り込み(ch1)
#define ICR_INTNO_CH2				66							//!< キャプチャ割り込み(ch2)
#define ICR_INTNO_CH3				67							//!< キャプチャ割り込み(ch3)
#define ICR_INTNO_CH4				68							//!< キャプチャ割り込み(ch4)
#define ICR_INTNO_CH5				69							//!< キャプチャ割り込み(ch5)
#define SDIP_INTNO_CH0				87							//!< SDIP割り込み(ch0)
#define SDIP_INTNO_CH1				89							//!< SDIP割り込み(ch1)
#define SDIP_INTNO_CH2				91							//!< SDIP割り込み(ch2)
#define SDIO_INTNO_CH0				88							//!< SD-IO割り込み(ch0)
#define SDIO_INTNO_CH1				90							//!< SD-IO割り込み(ch1)
#define SDIO_INTNO_CH2				92							//!< SD-IO割り込み(ch2)







/****************************************************************************/
// GUI管理
/****************************************************************************/
#define GEVG_INTNO_IRQ1				256							//!< GraphicEngine完了割り込み1
#define GEVG_INTNO_IRQ2				257							//!< GraphicEngine完了割り込み2
#define GEVG_INTNO_IRQ3				258							//!< GraphicEngine完了割り込み3

/****************************************************************************/
/*  AVS */
/****************************************************************************/
/* タスク優先度 */
#define NCS_TSKPRI_SEQ					94			/* AVSより高い */
#define	AVS_TSKPRI_MAIN					95
#define	AVS_TSKPRI_DBG_APL				96
#define	AVS_TSKPRI_TEST					97

/* タスクスタック */
#define	AVS_TSKSTK_MAIN					0x1000
#define	AVS_TSKSTK_DBG_APL				0x4000
#define	AVS_TSKSTK_TEST					0x4000

/* セマフォ初期値 */
#define AVS_SEMINIT_APILOCK	1
#define AVS_SEMINIT_FLGLOCK	1

/* セマフォ最大値 */
#define AVS_SEMMAX_APILOCK 	1
#define AVS_SEMMAX_FLGLOCK 	1

/* イベントフラグ初期値 */
#define AVS_FLGINIT_COMTASK			0x00000000	/* メッセージセレクタ用 */

/* 可変長メモリプールマクロ */
#define	AVS_MPLSZ_MAIN					(1024*64)
		
/* 固定長メモリプールマクロ */
#define	CMS_MPF_BLKCNT_MAIN   100   /* 獲得できるメモリブロック数（個数） */
#define	CMS_MPF_BLKSZ_MAIN    96    /* メモリブロックのサイズ（バイト数） */

/****************************************************************************/
/*  HDC */
/****************************************************************************/
/*==== タスク優先度 ======*/
#define	HDC_TSKPRI_MAIN					72		/* HDC Main Task */
#define	HDC_TSKPRI_FLASHACCESS			69		/* Flash Access Task */
#define	HDC_TSKPRI_MEDIAACCESS			66		/* FileSystem Access Task */

/****************************************************************************/
/*  SDP */
/****************************************************************************/
/*==== タスク優先度 ======*/
/*====System Core用====*/
#define	SDC_TSKPRI_SDCS					68
/*====Picture Core用====*/
#define	SDC_TSKPRI_SDCPC				70
#define	SDC_TSKPRI_SDCPM				75
#define	SDC_TSKPRI_SDCPE				76
/*====Exif Controller用====*/
#define	SDC_TSKPRI_SDCE					78

/****************************************************************************/
/*  CMR */
/****************************************************************************/

/* タスクプライオリティ */
#define	CMR_TSKPRI						40

/* タスクスタック */
#define	CMR_TSKSTK						1024

/****************************************************************************/

/****************************************************************************/
/*  STC */
/****************************************************************************/
/*==== タスク優先度 ======*/
#define	STC_TSKPRI_SCE					80
#define	STC_TSKPRI_HIGH					56
#define SPC_TSKPRI_MAIN					81

/****************************************************************************/

/****************************************************************************/
/*  SCL */
/****************************************************************************/
/*==== タスク優先度 ======*/
#define	SCL_TSKPRI						24			/* HD1st MetisLibと同じ */

#define	SCL_TSKSTK						(10*1024)

/*==== タスク拡張情報 =====*/
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
/*==== タスク優先度 ======*/
#define	AVFW_TSKPRI_TIMER				24
#define	VCI_TSKPRI						25
#define	AVFW_TSKPRI_VSO_VEN				31			/* Bug4485,Bug4697対策 */
#define	AVFW_TSKPRI_BACD_DEC			34
#define AVFW_TSKPRI_AVFW_ALIB			40
#define AVFW_TSKPRI_ALIB				40
#define AVFW_TSKPRI_GAIA				30			/* AVFW VENの1つ上 */
#define AVFW_TSKPRI_THREAD				42
#define	AVFW_TSKPRI_BACD_ENC			43
#define	VCL_TSKPRI_MAIN					44			/* AVDFタスクより下に */
#define	VCL_TSKPRI_SUB					45
#define VCL_TSKPRI_CHIPCOMMUNICATE		39
	
/* SMP関連 */
#if defined( ALLOPT_OS_SMP ) && defined( ALLOPT_MAINCHIP )
#define AVFW_RUN_CPU	3	/* AVFW動作CPU */
#endif

/****************************************************************************/

/****************************************************************************/
/*  CFS */
/****************************************************************************/

/*==== タスク優先度 ======*/
#define	CFS_TSKPRI_FAT			57
#define	CFS_TSKPRI_UDF			56

// 20070703 TU FATタスクを追加
#define	CFS_TSKPRI_FAT2			57

#define	CFS_TSKPRI_FROM			56
#define	CFS_TSKPRI_INT			121

/* HDD制御用 */
#define	CFS_TSKPRI_HIGH			55		/* FAT用タスクより上であること */
#define	CFS_TSKPRI_HDD_IDLIMM	115		/* ミドルで一番低くしておく */

/* 分割残量計算用タスク */
#define CFS_TSKPRI_GETFS		58

/****************************************************************************/
/*  USB */
/****************************************************************************/
/*  タスクプライオリティ */
#define USB_TSKPRI_MAIN 				  54
#define USB_TSKPRI_UOH  				  114
#define USB_TSKPRI_MASS_S  				  84
#define USB_TSKPRI_MASS_H  				  84			/* 2007/07/31 追加 */
#define USB_TSKPRI_VD_STREAM			  84			/* STC, CFSよりひくく設定 AKBのとき */
#define USB_TSKPRI_AD_STREAM			  30			/* AVIOより高く */

#define USBHD_TSKPRI_EVENT				  53 /* USB_TSKPRI_MAIN より高く */
#define USBHD_CONFIG_MPLSZ				1024

/* 割込み番号 */
#define USBIP_INTNO						 151	/* USBIP(USB_IRQ2) */
#define USBIP_INTNO_PERI	USBIP_INTNO			/* ペリフェラル用 */
#define USBIP_INTNO_HOST	USBIP_INTNO			/* ホスト用 */

/****************************************************************************/
/* GUI */
/****************************************************************************/

	/* GDIタスク優先度 */
	#define GUI_TSKPRI						  70

	/* タイムスタンプデータ更新タスク優先度 */
    #define GUI_TS_TSKPRI				      71	/* 跨ぎ対策でMDCよりひとつ上 */
	
	/* 画面描画タスク優先度 */
	#define CT_MAIN_TSKPRI					118	/* 旧APL描画タスクと同程度 */
	
	/* 毎フレーム描画タスク優先度 */
	#define CT_DRAW_TSKPRI                 46 /* 40から変更 STCより下へ */

	/* 線描画タスク優先度 */
	#define	GUI_TSKPRI_LINE			  119	/* APL_MAIN_TSKPRI(120)より1つだけ高い */

	/* DMPライブラリタスク優先度 */
	#define DMP_MAIN_TSKPRI                   39

	/* DMA完了待ちタスク優先度 */
    #define GUI_DMA_TSKPRI				123	/* TSタスクより高い */
	
/* 割込みレベル */
#define 	GIH_INTLVL	GRP108INTLVL

/* 割込み番号 */
#define 	GIH_INTNO	GRP108INTNO

/* HTK可変長メモリプールサイズ */
#define HTK_MPLSIZE 0x20000

/****************************************************************************/

/****************************************************************************/
/* HDMI */
/****************************************************************************/
/*==== タスク優先度 ======*/
#define	HDM_TSKPRI_BASE				40		/* HDMI Task */

#define CEC_TSKPRI_SYS				62		/* CECSYS Task */
#define CEC_TSKPRI_IF				58		/* CECIF Task */
#define CEC_TSKPRI_DD				35		/* CECDD Task */


/****************************************************************************/

/****************************************************************************/
/* KAO */
/****************************************************************************/
/*
 *	タスク優先度
 */
#define	KAO_IMAGE_TSKPRI			36
#define	KAO_KDET_TSKPRI				37
#define	KAO_TRCK_TSKPRI				38

/*
 *	タスクスタックサイズ
 */
#define	KAO_IMAGE_TSKSTK			0x1000
#define	KAO_KDET_TSKSTK				0x4000
#define	KAO_TRCK_TSKSTK				0x1000

/*
 *	割り込みNO
 */
#define	KAO_IRQ_NO_ODU				298

/****************************************************************************/

/****************************************************************************/
/* IIS/IUC */
/****************************************************************************/
/* タスク優先度 */
#define	IUC_TSKPRI		98	
/* タスクスタックサイズ */
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
/*==== タスク優先度 ======*/
#define NWA_TSKPRI_RECV		59
#define NWA_TSKPRI_SEND		59
#define NWA_TSKPRI_BOOT		59
	
/*==== 割込み番号 ======*/
#define NWA_INTNO_COMM		SPICA_INTNO_IRC2_DINT1

/****************************************************************************/
/* NWB */
/****************************************************************************/
/*==== タスク優先度 ======*/
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
#define	TCC_USER_ENTRY_ID_092	92	/* 未使用 */
#define	TCC_USER_ENTRY_ID_093	93	/* 未使用 */
#define	TCC_USER_ENTRY_ID_094	94	/* 未使用 */
#define	TCC_USER_ENTRY_ID_095	95	/* 未使用 */
#define	TCC_USER_ENTRY_ID_096	96	/* 未使用 */
#define	TCC_USER_ENTRY_ID_097	97	/* 未使用 */
#define	TCC_USER_ENTRY_ID_098	98	/* 未使用 */
#define	TCC_USER_ENTRY_ID_099	99	/* 未使用 */
#define	TCC_USER_ENTRY_ID_100	100	/* 未使用 */
#define	TCC_USER_ENTRY_ID_101	101	/* 未使用 */
#define	TCC_USER_ENTRY_ID_102	102	/* 未使用 */
#define	TCC_USER_ENTRY_ID_103	103	/* 未使用 */
#define	TCC_USER_ENTRY_ID_104	104	/* 未使用 */
#define	TCC_USER_ENTRY_ID_105	105	/* 未使用 */
#define	TCC_USER_ENTRY_ID_106	106	/* 未使用 */
#define	TCC_USER_ENTRY_ID_107	107	/* 未使用 */
#define	TCC_USER_ENTRY_ID_108	108	/* 未使用 */
#define	TCC_USER_ENTRY_ID_109	109	/* 未使用 */
#define	TCC_USER_ENTRY_ID_110	110	/* 未使用 */
#define	TCC_USER_ENTRY_ID_111	111	/* 未使用 */
#define	TCC_USER_ENTRY_ID_112	112	/* 未使用 */
#define	TCC_USER_ENTRY_ID_113	113	/* 未使用 */
#define	TCC_USER_ENTRY_ID_114	114	/* 未使用 */
#define	TCC_USER_ENTRY_ID_115	115	/* 未使用 */
#define	TCC_USER_ENTRY_ID_116	116	/* 未使用 */
#define	TCC_USER_ENTRY_ID_117	117	/* 未使用 */
#define	TCC_USER_ENTRY_ID_118	118	/* 未使用 */
#define	TCC_USER_ENTRY_ID_119	119	/* 未使用 */
#define	TCC_USER_ENTRY_ID_120	120	/* 未使用 */
#define	TCC_USER_ENTRY_ID_121	121	/* 未使用 */
#define	TCC_USER_ENTRY_ID_122	122	/* 未使用 */
#define	TCC_USER_ENTRY_ID_123	123	/* 未使用 */
#define	TCC_USER_ENTRY_ID_124	124	/* 未使用 */
#define	TCC_USER_ENTRY_ID_125	125	/* 未使用 */
#define	TCC_USER_ENTRY_ID_126	126	/* 未使用 */
#define	TCC_USER_ENTRY_ID_127	127	/* 未使用 */

#define	TCC_USER_ENTRY_ID_NM	( TCC_ID_VCL_OB + 1 )	/* 使用ID数 */

#ifdef __cplusplus
}
#endif

#endif /*  __OS_H__ */
