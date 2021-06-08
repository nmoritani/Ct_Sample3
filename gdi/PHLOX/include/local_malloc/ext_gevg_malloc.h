/******************************************************************************
 Copyright (C) 2011 Panasonic Corporation.

 Filename:
     ext_gevg_malloc.h

 Description:
     Declaration of memory pool

 Authors:
     YO - Yoshinori OKAZAKI@AVC

 File History:
 Date        Sign    Description
 ----------  ----    -------------------------------------------------------
 2011/10/04   YO     新規作成
 ******************************************************************************/

#ifndef _EXT_GEVG_MALLOC_H_
#define _EXT_GEVG_MALLOC_H_

/* ----------------------------------------------------------------------*/
/* インクルードファイル                                                  */
/* ----------------------------------------------------------------------*/
#include "string.h"

// ----------------------------------------------------------------------
// 設定値(必要に応じて変更してください)
// ----------------------------------------------------------------------
// メモリブロック管理数
#define	GEVG_MEM_CONF_MAX_ID		(15)		// 15種類管理

// デバッグ機能有無(1:有効, 0:無効)
#define	GEVG_MEM_CONF_DEBUG			(1)


// ----------------------------------------------------------------------
// マクロ定義
// ----------------------------------------------------------------------
#define MEM_TSZ_MPF_INFO(num) ( ((sizeof(SMemMngMpfInfo) + num) + (32-1)) / 32 * 32 )
#define MEM_TSZ_MPF(size, num) ( ((num) * ((size + (32-1)) / 32 * 32)) + MEM_TSZ_MPF_INFO(num) )


/* ----------------------------------------------------------------------*/
/* 型定義                                                                */
/* ----------------------------------------------------------------------*/
// メモリプール管理情報
typedef struct _SMemMngMpfInfo {
    unsigned long	size;       // メモリブロックのサイズ
    unsigned long	num;        // メモリブロックの数
    char*			addr;       // メモリブロック先頭アドレス
    unsigned long	use_num;    // メモリブロックの使用数
    unsigned long	next;       // 次空きブロックindex
    char*			flag;       // ブロック使用フラグ先頭アドレス
} SMemMngMpfInfo;

// メモリ初期化情報
typedef struct _SMemMngInit {
	char*			mem_adr;	// 先頭アドレス
	unsigned long	mem_size;	// メモリサイズ
	struct {
		unsigned long	size;	// メモリブロックサイズ
		unsigned long	num;	// メモリブロック数
	} mem_pool_info[GEVG_MEM_CONF_MAX_ID];
} SMemMngInit;


/* ----------------------------------------------------------------------*/
/* 関数プロトタイプ宣言                                                  */
/* ----------------------------------------------------------------------*/
void *tkmalloc(size_t size);
void tkfree(void *ptr);
void *tkrealloc(void *ptr, size_t size);

int tkMemMngInitialize(SMemMngInit *ptInit);
int tkMemMngTerminate(void);


#endif /* _EXT_GEVG_MALLOC_H_ */

/*****************************************************************************/
/* Copyright (C) 2011 Panasonic Corporation.                                 */
/*****************************************************************************/
