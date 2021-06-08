/******************************************************************************
 Copyright (C) 2011 Panasonic Corporation.

 Filename:
     mem_config.h

 Description:
     Declaration of memory pool

 Authors:
     YO - Yoshinori OKAZAKI@AVC

 File History:
 Date        Sign    Description
 ----------  ----    -------------------------------------------------------
 2011/10/04   YO     新規作成
 ******************************************************************************/

#ifndef _TKMEM_CONFIG_H_
#define _TKMEM_CONFIG_H_

#include "gdi_config.h"

// ----------------------------------------------------------------------
// 定義値 (必要なメモリ量を割りあててください)
// ----------------------------------------------------------------------
// メモリ開始アドレス
#define	MEM_MNG_STATIC_MEMADDR		(char *)(GFX_TK_START)

// メモリブロックサイズ
#define	GEVG_MEM_CONF_ID00_SIZE		(0x20)		// 32
#define	GEVG_MEM_CONF_ID01_SIZE		(0x40)		// 64
#define	GEVG_MEM_CONF_ID02_SIZE		(0x80)		// 128
#define	GEVG_MEM_CONF_ID03_SIZE		(0x100)		// 256
#define	GEVG_MEM_CONF_ID04_SIZE		(0x200)		// 512
#define	GEVG_MEM_CONF_ID05_SIZE		(0x400)		// 1024
#define	GEVG_MEM_CONF_ID06_SIZE		(0x800)		// 2048
#define	GEVG_MEM_CONF_ID07_SIZE		(0x1000)	// 4096
#define	GEVG_MEM_CONF_ID08_SIZE		(0x2000)	// 8192
#define	GEVG_MEM_CONF_ID09_SIZE		(0x4000)	// 16384
#define	GEVG_MEM_CONF_ID10_SIZE		(0x8000)	// 32768
#define	GEVG_MEM_CONF_ID11_SIZE		(0x10000)	// 65535
#define	GEVG_MEM_CONF_ID12_SIZE		(0x20000)	// 131072
#define	GEVG_MEM_CONF_ID13_SIZE		(0x40000)	// 262144
#define	GEVG_MEM_CONF_ID14_SIZE		(0x80000)	// 524288

// メモリブロック数
#define	GEVG_MEM_CONF_ID00_NUM		(1024*2)	// 32    
#define	GEVG_MEM_CONF_ID01_NUM		(1024)		// 64    
#define	GEVG_MEM_CONF_ID02_NUM		(1024*2)	// 128   
#define	GEVG_MEM_CONF_ID03_NUM		(1024)		// 256   
#define	GEVG_MEM_CONF_ID04_NUM		(512)		// 512   
#define	GEVG_MEM_CONF_ID05_NUM		(1024+512)	// 1024  
#define	GEVG_MEM_CONF_ID06_NUM		(256)		// 2048  
#define	GEVG_MEM_CONF_ID07_NUM		(16)		// 4096  
#define	GEVG_MEM_CONF_ID08_NUM		(16)		// 8192  
#define	GEVG_MEM_CONF_ID09_NUM		(8)		// 16384 
#define	GEVG_MEM_CONF_ID10_NUM		(8)		// 32768 
#define	GEVG_MEM_CONF_ID11_NUM		(8)		// 65535 
#define	GEVG_MEM_CONF_ID12_NUM		(8)			// 131072
#define	GEVG_MEM_CONF_ID13_NUM		(0)			// 262144
#define	GEVG_MEM_CONF_ID14_NUM		(0)			// 524288

#endif /* _MEM_CONFIG_H_ */

/*****************************************************************************/
/* Copyright (C) 2011 Panasonic Corporation.                                 */
/*****************************************************************************/

