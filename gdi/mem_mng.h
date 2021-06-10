#if 0
/******************************************************************************
 Copyright (C) 2011 Panasonic Corporation.

 Filename:
     mem_pool.h

 Description:
     Declaration of memory pool

 Authors:
     YO - Yoshinori OKAZAKI@AVC

 File History:
 Date        Sign    Description
 ----------  ----    -------------------------------------------------------
 2011/10/04   YO     新規作成(AVFW流用)
 ******************************************************************************/

#ifndef _MEM_MNG_H_
#define _MEM_MNG_H_

// ----------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------
#include "ext_gevg_malloc.h"


// ----------------------------------------------------------------------
// 型定義
// ----------------------------------------------------------------------
typedef signed long		MEM_ER;
typedef signed long		MEM_ER_ID;
typedef void 			*MEM_VP;
typedef void			*MEM_ID;
typedef unsigned char	MEM_ATR;

// ----------------------------------------------------------------------
// 定数定義
// ----------------------------------------------------------------------
#define MEM_E_OK		(0)
#define MEM_E_ID		(-1)
#define MEM_E_PAR		(-2)
#define MEM_E_TMOUT		(-3)

#define MEM_TA_TFIFO	(0x01)		// 暫定

#ifndef	NULL
#define	NULL			(0)
#endif

// ----------------------------------------------------------------------
// マクロ定義
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
// 構造体定義
// ----------------------------------------------------------------------
// メモリプール生成情報
typedef struct MEM_T_CMPF {
    MEM_ATR			mpfatr;
    unsigned long	blkcnt;
    unsigned long	blksz;
    MEM_VP			mpf;
} MEM_T_CMPF;

// メモリプール設定用構造体
typedef struct _SMemMngPool { /* pgr1232 */
    unsigned long	m_uiBlkSize;   // メモリブロックのサイズ
    unsigned long	m_uiBlkNum;    // メモリブロックの数
    unsigned long	m_uiMinSize;   // 本プールを使用する下限サイズ
    unsigned long	m_uiMaxSize;   // 本プールを使用する上限サイズ
    unsigned long	m_ulPeakSize;  // 本プールが取得した最大サイズ(for Debug)
    unsigned long	m_ulUseNum;    // 本プールで使用中の数(for Debug)
    unsigned long	m_ulPeakNum;   // 本プールが取得した最大サイズ(for Debug)
    unsigned long	m_ulFail;      // 本プールが取得失敗した数(for Debug)
    unsigned long	m_ulOtherSize; // 本プールが取得失敗した数(for Debug)
} SMemMngPool;

// メモリプール管理用構造体
typedef struct _SMemMngPoolMng { /* pgr1232 */
    SMemMngPool m_tPoolData;  // メモリプールのデータ
    MEM_ID m_Id;              // メモリプールのID番号(現行システムではpStartAddr)
    MEM_VP m_pStartAddr;      // メモリプールの先頭アドレス
    MEM_VP m_pEndAddr;        // メモリプールの終端アドレス
} SMemMngPoolMng;


// ----------------------------------------------------------------------
// 変数宣言(extern)
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
// 関数プロトタイプ宣言
// ----------------------------------------------------------------------
MEM_ER tkmem_mng_acre_mpf(MEM_T_CMPF *pk_cmpf, MEM_ID* id);
MEM_ER tkmem_mng_del_mpf(MEM_ID mpfid);
MEM_ER tkmem_mng_pget_mpf(MEM_ID mpfid, MEM_VP *p_blk);
MEM_ER tkmem_mng_rel_mpf(MEM_ID mpfid, MEM_VP blk);

#endif /* _MEM_POOL_H_ */

/*****************************************************************************/
/* Copyright (C) 2011 Panasonic Corporation.                                 */
/*****************************************************************************/
#endif
