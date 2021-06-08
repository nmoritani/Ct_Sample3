/******************************************************************************
 Copyright (C) 2011 Panasonic Corporation.

 Filename:
     mem_mng.c

 Description:
     Declaration of memory pool

 Authors:
     YO - Yoshinori OKAZAKI@AVC

 File History:
 Date        Sign    Description
 ----------  ----    -------------------------------------------------------
 2011/10/04   YO     新規作成(AVFW流用)
 ******************************************************************************/

// ----------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------
#include <kernel.h>
#include "SysIf.h"

#include "mem_mng.h"

#ifdef WIN32_GUI_SIM
#include <smDebugSerial.h>
#include "kernel_id.h"
#include "win_itron.h"
#else
#include <dbgserial/smDebugSerial.h>
#endif

// ----------------------------------------------------------------------
// 定数定義
// ----------------------------------------------------------------------
#define	DBG_MEM_POOL_VARIABLE	(0)


// ----------------------------------------------------------------------
// 変数宣言
// ----------------------------------------------------------------------
// メモリプール管理テーブル
SMemMngPoolMng g_tMemMngPoolTable[GEVG_MEM_CONF_MAX_ID + 1];

// 初期化済みフラグ
static unsigned int g_uiMemMngInitFlg = 0;


// ----------------------------------------------------------------------
// 関数定義
// ----------------------------------------------------------------------
static void* MemMngAlloc(size_t uiSize);
static void MemMngFree(void *pAddr);
static size_t MemMngGetSize(void *pAddr);

static MEM_ER mem_mng_lock(void);
static MEM_ER mem_mng_unlock(void);

/***********************************************************************
   API 関数
************************************************************************/
static int max_memory_syze = 0;

static BOOL get_memory_size(ID mplid, int *mem_size)
{
	T_RMPL rmpl;

	if (mem_size == NULL)
		return FALSE;
	
	if (ref_mpl(mplid, &rmpl) != E_OK) {
		return FALSE;
	}
	*mem_size = rmpl.fmplsz;

	return TRUE;
}

static int get_remain_mem_percent(ID mplid)
{
	int remain;

	if (0 == max_memory_syze) {
		return (get_memory_size(mplid, &max_memory_syze)) ? 100 : 0;
	}

	if (!get_memory_size(mplid, &remain)) {
		return 0;
	}

	//smDebugPrintf(1, "ID:[%d]  メモリ残量: %d%%(%d / %d)\n", mplid, (remain * 100 / max_memory_syze), remain, max_memory_syze);

	//残りメモリサイズを％で返す
	return remain * 100 / max_memory_syze;
}

void *gdi_alloc(int size)
{
	void *mem;

	if (tget_mpl(GFX_RESMPL_ID, size, &mem,  500) != E_OK) {
		return NULL;
	}
	return mem;
}

void gdi_free(void *ptr)
{
	rel_mpl(GFX_RESMPL_ID, ptr);
}

int gdi_remain_mem_percent()
{
	return get_remain_mem_percent(GFX_RESMPL_ID);
}

void *gdi_bmp_alloc(int size, int align)
{
	void *p = NULL;
	unsigned long temp = 0;

	size += align+4;
	if (tget_mpl(GUI_WORKMPL_ID, size, &p,  500) != E_OK) {
		return NULL;
	}
	temp = (unsigned long)p + 4;
	if (temp & (align-1)) {
		p = (void *)((temp & (0xFFFFFFFF-(align-1))) +align);
	} else {
		p = (void *)temp;
	}
	((unsigned long *)p)[-1] = temp - 4;

	return p;
}

void gdi_bmp_free(void *ptr)
{
	unsigned long temp = 0;
	
	if (ptr != NULL) {
		temp = ((unsigned long *)ptr)[-1];
	}
	rel_mpl(GUI_WORKMPL_ID, (void *)temp);
}

int gdi_bmp_remain_mem_percent()
{
	return get_remain_mem_percent(GUI_WORKMPL_ID);
}


void *gui_alloc(int size, int align)
{
	void *p = NULL;
	unsigned long temp = 0;

	size += align+4;
	if (tget_mpl(GUI_WORKMPL_ID, size, &p,  500) != E_OK) {
		return NULL;
	}
	temp = (unsigned long)p + 4;
	if (temp & (align-1)) {
		p = (void *)((temp & (0xFFFFFFFF-(align-1))) +align);
	} else {
		p = (void *)temp;
	}
	((unsigned long *)p)[-1] = temp - 4;

	return p;
}

void gui_free(void *ptr)
{
	unsigned long temp = 0;
	
	if (ptr != NULL) {
		temp = ((unsigned long *)ptr)[-1];
	}
	rel_mpl(GUI_WORKMPL_ID, (void *)temp);
}

int gui_remain_mem_percent()
{
	return get_remain_mem_percent(GUI_WORKMPL_ID);
}

int largesize = 0;
void *tkmalloc(size_t size)
{
	void * p;

	if (size <= 32*1024) {		// 32KBより大きければTkMallocを使用しない(mem_config.hを参照)
		p = MemMngAlloc(size);
	} else {
		p = gui_alloc(size, 0x10);
	}
	return p;
}

void tkfree(void *ptr)
{
	if ((g_tMemMngPoolTable[0].m_pStartAddr <= ptr) &&
		(ptr <= g_tMemMngPoolTable[10].m_pEndAddr)) {
		MemMngFree(ptr);
	} else {
		gui_free(ptr);
	}
}

void *tkrealloc(void *ptr, size_t size)
{
	void* p;
	size_t	blsz;

	if (ptr == NULL) {
		return (tkmalloc(size));
	}

	blsz = MemMngGetSize(ptr);
	if (blsz < size) {
		p = tkmalloc(size);
		if (p == NULL) {
			tkfree(ptr);
			return (NULL);
		}
		memcpy(p, ptr, blsz);
		tkfree(ptr);
	} else {
		p = ptr;
	}

	return p;
}

/***********************************************************************
 Function : メモリブロック獲得
 Calling  : void* MemMngAlloc(size_t uiSize)
 Input    : size_t uiSize : サイズ
 OutPut   : なし
 Return   : メモリブロックの先頭アドレス
 Comment  : 
 Update   : 2007.11.02 : AW : 新規作成
            2007.11.26 : AW : 非タスクコンテキスト呼び出し対応
            2008.08.20 : AW : 再探索開始プールの初期値をNULLから
                             管理テーブルの先頭に変更
************************************************************************/
static void* MemMngAlloc(size_t uiSize)
{
    MEM_ER ercd;
    MEM_VP pMemBlk = NULL;
    MEM_ER eRet;
    SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;

    // 引数チェック
    if (uiSize <= 0) {
        return NULL;
    }

    eRet = mem_mng_lock();
    if (eRet != MEM_E_OK) {
        return NULL;
    }

    // 初期済みチェック
    if (g_uiMemMngInitFlg != 1) {
        (void)mem_mng_unlock();
        return NULL;
    }

    // 引数uiSizeに対応する固定長メモリプールが存在する場合は、
    // 該当するプールのメモリブロックを獲得する

    // 対応する固定長メモリプールを線形探索する
    while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
        if ((pMemPoolMng->m_tPoolData.m_uiMinSize <= (unsigned long)uiSize) &&
            ((unsigned long)uiSize <= pMemPoolMng->m_tPoolData.m_uiMaxSize) &&
            (pMemBlk == NULL)) {
            //  固定長メモリブロックを獲得する
            ercd = tkmem_mng_pget_mpf(pMemPoolMng->m_Id, &pMemBlk);
            if (ercd != MEM_E_OK) {
                // 獲得エラーのときは明示的にNULLにする
                 pMemBlk = NULL;

				// 取得失敗
				pMemPoolMng->m_tPoolData.m_ulFail ++;
				
                // メモリブロックの獲得に失敗した場合は、上位プールの
                // ブロックでの取得を試みるために 1つプールを進める
                pMemPoolMng ++;
            }
			else
			{
				// 取得成功(統計情報更新)
				if (pMemPoolMng->m_tPoolData.m_ulPeakSize < (unsigned long)uiSize) {
					pMemPoolMng->m_tPoolData.m_ulPeakSize = (unsigned long)uiSize;
				}
				pMemPoolMng->m_tPoolData.m_ulUseNum ++;
				if (pMemPoolMng->m_tPoolData.m_ulPeakNum < pMemPoolMng->m_tPoolData.m_ulUseNum) {
					pMemPoolMng->m_tPoolData.m_ulPeakNum = pMemPoolMng->m_tPoolData.m_ulUseNum;
				}
			}
            break;   /* pgr0701 */
        }
        pMemPoolMng++;
    }

    // 引数uiSizeに対応する固定長メモリプールが存在しない場合は、
    // 獲得可能なプールのブロックを獲得する

    if (pMemBlk == NULL) {
        // 対応する固定長メモリプールを線形探索する
        while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
            //  固定長メモリブロックを獲得する
            ercd = tkmem_mng_pget_mpf(pMemPoolMng->m_Id, &pMemBlk);
            if (ercd != MEM_E_OK) {
                // 獲得エラーのときは明示的にNULLにする
                pMemBlk = NULL;
				// 取得失敗
				pMemPoolMng->m_tPoolData.m_ulFail ++;
            } else {
				// 取得成功(統計情報更新)
				if (pMemPoolMng->m_tPoolData.m_ulPeakSize < (unsigned long)uiSize) {
					pMemPoolMng->m_tPoolData.m_ulPeakSize = (unsigned long)uiSize;
				}
				pMemPoolMng->m_tPoolData.m_ulUseNum ++;
				if (pMemPoolMng->m_tPoolData.m_ulPeakNum < pMemPoolMng->m_tPoolData.m_ulUseNum) {
					pMemPoolMng->m_tPoolData.m_ulPeakNum = pMemPoolMng->m_tPoolData.m_ulUseNum;
				}
				pMemPoolMng->m_tPoolData.m_ulOtherSize ++;
                break;  /* pgr0701 */
            }

            pMemPoolMng++;
        }
    }
	
    (void)mem_mng_unlock();
    return (void*)pMemBlk;
}

/***********************************************************************
 Function : メモリブロック返却
 Calling  : void MemMngFree(void *pAddr)
 Input    : void *pAddr : メモリブロックの先頭アドレス
 OutPut   : なし
 Return   : なし
 Comment  : 
 Update   : 2007.11.02 : AW : 新規作成
            2007.11.26 : AW : 非タスクコンテキスト呼び出し対応
************************************************************************/
static void MemMngFree(void *pAddr)
{
    MEM_ER ercd;
    MEM_ER eRet;
    SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;

    // 引数チェック
    if (pAddr == NULL) {
        return ;
    }

    eRet = mem_mng_lock();
    if(eRet != MEM_E_OK) {
        return ;
    }

    // 初期化チェック
    if (g_uiMemMngInitFlg != 1) {
        eRet = mem_mng_unlock();
        if (eRet != MEM_E_OK) {
            return ;
        }
        return ;
    }

	// 引数addrが固定長メモリプールのアドレスの場合は、
    // 固定長メモリブロックを返却する
    while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
        if ((pMemPoolMng->m_pStartAddr <= pAddr) &&
            (pAddr <= pMemPoolMng->m_pEndAddr)) {
            // 固定長メモリブロックを返却する
            ercd = tkmem_mng_rel_mpf(pMemPoolMng->m_Id, pAddr);
            if (ercd == MEM_E_OK) {
            	if(pMemPoolMng->m_tPoolData.m_ulUseNum > 0){
					pMemPoolMng->m_tPoolData.m_ulUseNum --;
            	}
                break;    /*    pgr0701 */ /* 意図したbreak */
            } else {
                // 何もしない(致命的な状態)
            }
            break;
        }

        pMemPoolMng++;
    }

    (void)mem_mng_unlock();
    return ;
}

/***********************************************************************
 Function : メモリブロック返却
 Calling  : size_t MemMngGetSize(void *pAddr)
 Input    : void *pAddr : メモリブロックの先頭アドレス
 OutPut   : size_t メモリブロックサイズ
 Return   : なし
 Comment  : 
 Update   : 2011.10.04 : AW : 新規作成
************************************************************************/
static size_t MemMngGetSize(void *pAddr)
{
    SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;
    MEM_ER eRet;

    // 引数チェック
    if (pAddr == NULL) {
        return (0);
    }

    eRet = mem_mng_lock();
    if(eRet != MEM_E_OK) {
        return (0);
    }

    // 初期化チェック
    if (g_uiMemMngInitFlg != 1) {
        (void)mem_mng_unlock();
        return (0);
    }

    // 引数addrの固定長ブロックを検索する
    while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
        if ((pMemPoolMng->m_pStartAddr <= pAddr) &&
            (pAddr <= pMemPoolMng->m_pEndAddr)) {
            (void)mem_mng_unlock();
            return (pMemPoolMng->m_tPoolData.m_uiMaxSize);
        }
        pMemPoolMng++;
    }

    (void)mem_mng_unlock();
    return (0);
}

/***********************************************************************
 Function : 初期化関数
 Calling  : int tkMemMngInitialize(SMemMngInit *ptInit)
 Input    : なし
 OutPut   : なし
 Return   :  0 : 正常終了
            -1 : エラー
 Comment  : 
 Update   : 2007.10.18 : AW : 新規作成
            2007.11.26 : AW : 非タスクコンテキスト呼び出し対応
            2011.10.07 : YO : GE用に作り直し
            2011.10.18 : YO : CACHE-IFのPURGEコード追加
************************************************************************/
int tkMemMngInitialize(SMemMngInit *ptInit)
{
	MEM_ER ercd;
	MEM_T_CMPF pk_cmpf;
	MEM_ID mpfid;
	SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;
	char*			pStartAddr;
	unsigned long	ulMemSize;
	int	i;

	// 初期化チェック
	if (g_uiMemMngInitFlg == 1) {
		return -1;
	}

	// パラメータチェック
	if (ptInit == NULL) {
		return -1;
	}

	// メモリアドレスチェック
	if (ptInit->mem_adr == NULL) {
		return -1;
	}

	// メモリプール先頭情報確認
	if (ptInit->mem_pool_info[0].size == 0) {
		// 先頭が 0 はおかしい
		return -1;
	}
	
	// メモリ開始アドレス、全体サイズ取得
	pStartAddr	= ptInit->mem_adr;
	ulMemSize	= ptInit->mem_size;

	// メモリ管理情報初期化
	memset(pMemPoolMng, 0, sizeof(SMemMngPoolMng)*(GEVG_MEM_CONF_MAX_ID + 1));

	// メモリプールの生成
	for (i = 0; i < GEVG_MEM_CONF_MAX_ID; i ++) {
		// メモリプール生成終了
		if ((ptInit->mem_pool_info[i].num == 0) ||
			(ptInit->mem_pool_info[i].size == 0)) {
			break;
		}

		// 非終端プール(id < MAX_ID -1)
		if (i < (GEVG_MEM_CONF_MAX_ID - 1)) {
			// サイズは昇順で無ければならない
			if (ptInit->mem_pool_info[i+1].size < ptInit->mem_pool_info[i].size) {
				return -1;
			}
		}

		// プール管理情報の設定
		pMemPoolMng->m_tPoolData.m_uiBlkSize	= ptInit->mem_pool_info[i].size;
		pMemPoolMng->m_tPoolData.m_uiBlkNum		= ptInit->mem_pool_info[i].num;
		if (i == 0) {
			// 先頭は 1 から
			pMemPoolMng->m_tPoolData.m_uiMinSize	= 1;
		} else {
			// 2番目以降は、1つ前 + 1
			pMemPoolMng->m_tPoolData.m_uiMinSize	= ptInit->mem_pool_info[i-1].size + 1;
		}
		pMemPoolMng->m_tPoolData.m_uiMaxSize	= ptInit->mem_pool_info[i].size;
		pMemPoolMng->m_tPoolData.m_ulPeakSize	= pMemPoolMng->m_tPoolData.m_uiMinSize;
		pMemPoolMng->m_tPoolData.m_ulUseNum		= 0;
		pMemPoolMng->m_tPoolData.m_ulPeakNum	= 0;
		pMemPoolMng->m_tPoolData.m_ulFail		= 0;
		pMemPoolMng->m_tPoolData.m_ulOtherSize	= 0;
		pMemPoolMng->m_pStartAddr = pStartAddr;
		pMemPoolMng->m_pEndAddr   = (char*)pMemPoolMng->m_pStartAddr
			+ MEM_TSZ_MPF(ptInit->mem_pool_info[i].size , ptInit->mem_pool_info[i].num) - 1;

		// 終端がメモリサイズを超えた
		if (((unsigned long)(ptInit->mem_adr) + ptInit->mem_size) < (unsigned long)(pMemPoolMng->m_pEndAddr)) {
			return -1;
		}
		
		// メモリプール作成
		pk_cmpf.mpfatr	= MEM_TA_TFIFO;
		pk_cmpf.blkcnt	= pMemPoolMng->m_tPoolData.m_uiBlkNum;
		pk_cmpf.blksz	= pMemPoolMng->m_tPoolData.m_uiBlkSize;
		pk_cmpf.mpf		= pMemPoolMng->m_pStartAddr;

		// 固定長メモリプールを生成する
		ercd = tkmem_mng_acre_mpf(&pk_cmpf, &mpfid);
		if (ercd != MEM_E_OK) {
			return -1;
		} else {
			pMemPoolMng->m_Id = mpfid;
		}

		pStartAddr = (char*)pMemPoolMng->m_pEndAddr + 1;
		pMemPoolMng++;
	}

	ercd = mem_mng_lock();
	if(ercd != MEM_E_OK) {
		return -1;
	}
	// 初期化済みフラグを立てる
	g_uiMemMngInitFlg = 1;
	(void)mem_mng_unlock();

	return 0;
}

/***********************************************************************
 Function : 終了関数
 Calling  : int tkMemMngTerminate(void)
 Input    : なし
 OutPut   : なし
 Return   : 0 : 正常終了
            -1 : エラー
 Comment  : 
 Update   : 2007.10.18 : AW : 新規作成
            2007.11.26 : AW : 非タスクコンテキスト呼び出し対応
************************************************************************/
int tkMemMngTerminate(void)
{
	int iRet = 0;
	MEM_ER ercd;
	SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;

	ercd = mem_mng_lock();
	if(ercd != MEM_E_OK) {
		return -1;
	}

	// 初期化チェックはしない
	// 初期化処理中のエラー発生により初期化処理を完了しなかった場合も、
	// 途中までに獲得したリソースを解放するため

	while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
		// 固定長メモリプールを削除する
		ercd = tkmem_mng_del_mpf(pMemPoolMng->m_Id);
		if ((ercd != MEM_E_OK) && (ercd != MEM_E_ID)) {
			// 終了処理中のエラー発生は、可能な限り処理を続行する
			iRet = -1;
		} else {
			// 削除した固定長メモリプールのID番号をクリアする
			pMemPoolMng->m_Id = 0;
		}
		pMemPoolMng++;
	}

	// 初期化済みフラグを下げる
	g_uiMemMngInitFlg = 0;
	(void)mem_mng_unlock();

	return iRet;
}

/***********************************************************************
 Function : アトミックなロック開始
 Calling  : ER mem_mng_lock()
 Input    : なし
 OutPut   : なし
 Return   : 正常終了(E_OK)またはエラーコード
 Comment  : 
 Update   : 2007.11.26 : AW : 新規作成
            2008.04.14 : AW : vent_cim/ivent_cimを使用しないように修正
************************************************************************/
static MEM_ER mem_mng_lock(void)
{
    ER eRet = E_OK;

    eRet = loc_cpu();
    if (eRet == E_CTX) {
        eRet = iloc_cpu();
    }
    if (eRet == E_OK)
		return (MEM_E_OK);
	
    return (MEM_E_PAR);
}

/***********************************************************************
 Function : アトミックなロック解除
 Calling  : ER mem_mng_unlock(void)
 Input    : なし
 OutPut   : なし
 Return   : 正常終了(E_OK)またはエラーコード
 Comment  : 
 Update   : 2007.11.26 : AW : 新規作成
            2008.04.14 : AW : vlea_cim/ivlea_cimを使用しないように修正
************************************************************************/
static MEM_ER mem_mng_unlock(void)
{
    ER eRet = E_OK;

    eRet = unl_cpu();
    if (eRet == E_CTX) {
        eRet = iunl_cpu();
    }
    if (eRet == E_OK)
		return (MEM_E_OK);
	
    return (MEM_E_PAR);
}

#if CFG_ENABLE_HJ_SHELL
void ge_mpl_info(void)
{
	int id;
	
	smDebugPrintf(1, "ID,StAdd,EndAdd,BlkSize,BlkNum,MinSize,MaxSize,PeakSize,UseNum,PeakNum,FailNum,OthSize\r\n");
	for(id=0;id<GEVG_MEM_CONF_MAX_ID;id++){
		smDebugPrintf(1, "%x,%x,%x,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",
			g_tMemMngPoolTable[id].m_Id,
			g_tMemMngPoolTable[id].m_pStartAddr,
			g_tMemMngPoolTable[id].m_pEndAddr,
			g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkSize,
		    g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum,
			g_tMemMngPoolTable[id].m_tPoolData.m_uiMinSize,
			g_tMemMngPoolTable[id].m_tPoolData.m_uiMaxSize,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulPeakSize,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulPeakNum,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulFail,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulOtherSize );
		}
	smDebugPrintf(1, "---------------------\r\n\r\n\r\n");
}
#endif /* CFG_ENABLE_HJ_SHELL */


void geman_mpl_info(void)
{
	unsigned long id, use_total = 0, total = 0;
	
	smDebugPrintf(1, "|Block Size X Block Num  |UsedSize(Peak Num)  | Percent\n");
	for (id=0;id<GEVG_MEM_CONF_MAX_ID;id++) {
		smDebugPrintf(1, " %12d X %4d , %12d(%4d), (%3d) \n",
					  g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkSize,
					  g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum,
					  g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum,
					  g_tMemMngPoolTable[id].m_tPoolData.m_ulPeakNum,
					  (g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum*100)/(g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum));
		use_total += (g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkSize)*(g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum);
		total += (g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkSize)*(g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum);
		}
	smDebugPrintf(1, "-------- %12d / %12d ---------------------\n", use_total, total);
}


BOOL GDI_checkRemainMpl(unsigned int percent)
{
#ifdef WIN32_GUI_SIM
	return FALSE;
#else
	unsigned int id, per;
	
	for (id = 0; id < GEVG_MEM_CONF_MAX_ID; id++) {
		if (g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum == 0 ||
			g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum == 0) {
			continue;
		}

		per = (g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum * 100)/g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum;
		if (per > percent) {	// percent以上使用していれば、trueを返す
			return TRUE;
		}
	}
	return FALSE;
#endif
}

/***********************************************************************
 Function : 固定長メモリプールの生成
 Calling  : MEM_ER_ID tkmem_mng_acre_mpf(MEM_T_CMPF *pk_cmpf)
 Input    : MEM_T_CMPF *pk_cmpf : 固定長メモリプール生成情報を入れたパケットへのポインタ
 OutPut   : MEM_ID *id : 生成した固定長メモリプールのID番号(正の値)
 Return   : 正常終了(MEM_E_OK)またはエラーコード
 Comment  : 
 Update   : 2007.11.26 : AW : 新規作成
            2007.11.26 : YO : 修正
            2007.12.07 : AW : ITRONの型を独自の型に変更
************************************************************************/
MEM_ER tkmem_mng_acre_mpf(MEM_T_CMPF* pk_cmpf, MEM_ID* id)
{
    SMemMngMpfInfo* info = NULL;
    unsigned long i;

    // 引数チェック
    if ((pk_cmpf == NULL) || (id == NULL)) {
        return MEM_E_PAR;
    }

    if ((pk_cmpf->blkcnt <= 0) || (pk_cmpf->blksz <= 0) || (pk_cmpf->mpf == NULL)) {
        return MEM_E_PAR;
    }

    // 固定長メモリプール領域の先頭部分は管理情報を格納するとし、
    // その初期化を行う
    info            = (SMemMngMpfInfo*)(pk_cmpf->mpf);
    info->num       = pk_cmpf->blkcnt;
    info->size      = pk_cmpf->blksz;
    info->use_num   = 0;
    info->next      = 0;
    info->addr      = (char*)(pk_cmpf->mpf) + MEM_TSZ_MPF_INFO(pk_cmpf->blkcnt);
    info->flag      = (char*)(pk_cmpf->mpf) + sizeof(SMemMngMpfInfo);

    // 使用フラグクリア
    for (i = 0; i < info->num; i++) {
        info->flag[i] = 0;
    }

    // IDにはアドレスを返す
    *id = (MEM_ID)(pk_cmpf->mpf);
    return MEM_E_OK;
}


/***********************************************************************
 Function : 固定長メモリプールの削除
 Calling  : MEM_ER tkmem_mng_del_mpf(MEM_ID mpfid)
 Input    : MEM_ID mpfid : 削除対象の固定長メモリプールのID
 OutPut   : なし
 Return   : 正常終了(MEM_E_OK)またはエラーコード
 Comment  : 
 Update   : 2007.11.26 : YO : 新規作成
            2007.12.07 : AW : ITRONの型を独自の型に変更
************************************************************************/
MEM_ER tkmem_mng_del_mpf(MEM_ID mpfid)
{
    // IDチェック
    if ((MEM_VP)mpfid == NULL) {
        return MEM_E_ID;
    }

    // 破棄処理は不要
    return MEM_E_OK;
}


/***********************************************************************
 Function : 固定長メモリプールの獲得
 Calling  : MEM_ER tkmem_mng_pget_mpf(MEM_ID mpfid, MEM_VP *p_blk)
 Input    : MEM_ID mpfid : メモリブロック獲得対象の固定長メモリプールのID番号
 OutPut   : MEM_VP blk : 獲得したメモリブロックの先頭番地
 Return   : 正常終了(MEM_E_OK)またはエラーコード
 Comment  : 
 Update   : 2007.11.26 : YO : 新規作成
            2007.12.07 : AW : ITRONの型を独自の型に変更
************************************************************************/
MEM_ER tkmem_mng_pget_mpf(MEM_ID mpfid, MEM_VP *p_blk)
{
    SMemMngMpfInfo* info = NULL;
    unsigned long i;

    // IDチェック
    if ((MEM_VP)mpfid == NULL) {
        return MEM_E_ID;
    }

    // パラメータチェック
    if (p_blk == NULL) {
        return MEM_E_PAR;
    }

    info = (SMemMngMpfInfo*)mpfid;
    for (i = info->next; i < info->num; i++) {
        if (info->flag[i] == 0) {
            *p_blk = info->addr + (info->size * i); /* pgr0244 */
            info->flag[i] = 1;
            (info->next)++;
            (info->use_num)++;
            return MEM_E_OK;
        }
    }

    // 獲得失敗(空きブロックなし)
    return MEM_E_TMOUT;
}


/***********************************************************************
 Function : 固定長メモリプールの返却
 Calling  : MEM_ER tkmem_mng_rel_mpf(MEM_ID mpfid, MEM_VP blk)
 Input    : MEM_ID mpfid : メモリブロック返却対象の固定長メモリプールのID番号
 OutPut   : MEM_VP blk : 返却するメモリブロックの先頭番地
 Return   : 正常終了(MEM_E_OK)またはエラーコード
 Comment  : 
 Update   : 2007.11.26 : YO : 新規作成
            2007.12.07 : AW : ITRONの型を独自の型に変更
************************************************************************/
MEM_ER tkmem_mng_rel_mpf(MEM_ID mpfid, MEM_VP blk)
{
    SMemMngMpfInfo* info = NULL;
    long            index;

    // IDチェック
    if (mpfid == 0) {
        return MEM_E_ID;
    }

    // 引数チェック
    if (blk == NULL) {
        return MEM_E_PAR;
    }

    info = (SMemMngMpfInfo*)mpfid;

    // 返却ブロックチェック(アライメント)
    index = (long)blk - (long)(info->addr);
    if (((unsigned long)index % info->size) != 0) {
        // アドレスがブロック先頭ではない
        return MEM_E_PAR;
    }

    // 返却ブロックチェック(範囲)
    index /= info->size;
    if (((long)index < 0) || ((unsigned long)index >= info->num)) {
        // アドレスがプールデータ範囲外
        return MEM_E_PAR;
    }

    // 返却ブロックチェック(使用状態)
    if (info->flag[index] == 0) {
        // 未割り当てブロック
        return MEM_E_PAR;
    }

    // 管理情報更新
    (info->use_num)--;
    info->flag[index] = 0;
    if ((unsigned long)index < info->next)
    {
        // 空きブロック位置更新
        info->next = index;
    }

    return MEM_E_OK;
}
