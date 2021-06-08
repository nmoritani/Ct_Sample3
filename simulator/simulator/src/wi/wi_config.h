/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_config.h
 *
 *	@brief	Windows版 iTRONサービスコールの環境定義.
 *
 *	@author	金澤 宣明
 */
#ifndef	__WI_CONFIG_H__
#define	__WI_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * シンボル定義.
 *
 ****************************************************************************/
#define		TMAX_MAXTSK		256			//!< タスクIDの最大番号.
#define		TMAX_MAXSEM		256			//!< セマフォIDの最大番号.
#define		TMAX_MAXFLG		256			//!< イベントフラグIDの最大番号.
#define		TMAX_MAXDTQ		256			//!< データキューIDの最大番号.
#define		TMAX_MAXMBX		256			//!< メールボックスIDの最大番号.
#define		TMAX_MAXMBF		256			//!< メッセージバッファIDの最大番号.
#define		TMAX_MAXMTX		256			//!< ミューテックスIDの最大番号.
#define		TMAX_MAXPOR		256			//!< ランデブポートIDの最大番号.
#define		TMAX_MAXMPF		256			//!< 固定長メモリプールIDの最大番号.
#define		TMAX_MAXMPL		256			//!< 可変長メモリプールIDの最大番号.
#define		TMAX_MAXCYC		256			//!< 周期ハンドラ番号の最大番号.
#define		TMAX_MAXALM		256			//!< アラームハンドラ番号の最大番号.
#define		TMAX_MAXINT		256			//!< 割り込みハンドラ番号の最大番号.
#define		TMAX_MAXRDV		0x7FFFFFFF	//!< ランデブ番号の最大番号.

#define		TMAX_ACTCNT		1			//!< タスク起動要求キューイング数の最大数.
#define		TBIT_FLGPTN		32			//!< イベントフラグのビット数.
#define		TMAX_MPRI		256			//!< メッセージ優先度の最大値.

#define		CYCLETIME		10			//!< 周期タイマ間隔.

//#define	__ITRON3__					//!< Ver3.0
#ifndef		__ITRON3__
#ifndef		__ITRON4__
#define		__ITRON4__					//!< Ver4.0
#endif	//	__ITRON4__
#endif	//	__ITRON3__

#ifdef __cplusplus
}
#endif
#endif	// __WI_CONFIG_H__
/* End of file */
