/** 同期制御クラス
 *
 * Copyright(c) 2018 Persol AVC Technology.
 * @file
 */

#include "CtSynchro.h"
#include <CtPlatforms.h>

extern "C" {	// @@@
}



/***********************************
static member.
***********************************/
const unsigned int CtSynchro::ms_InvalidFlgPtn = 0;
const unsigned int CtSynchro::ms_MaxBit = 16;
unsigned int CtSynchro::ms_FlgPtnMap = 0;
syswrap_event_t CtSynchro::m_Event = {0};
syswrap_semaphore_t CtSynchro::m_Semaphore = {0};

void CtSynchro::init()
{
	syswrap_create_event(&m_Event, THREAD_ATTR_FIFO, 0);
	syswrap_create_semaphore(&m_Semaphore, 1, THREAD_ATTR_FIFO);	// binary semaphoreでないと描画noize出ます
}

void CtSynchro::term()
{
	syswrap_destroy_semaphore(&m_Semaphore);
	syswrap_destroy_event(&m_Event);
}


/** イベントフラグの状態を初期化
 * 
 * @param [out]	イベントフラグ情報
 */
void	CtSynchro::initFlgInfo( FlgInfo &info )
{
	info.flgptn = ms_InvalidFlgPtn;
	info.flg = NULL;
}

/** イベントフラグ情報を割り当てる
 * 
 * @retval イベントフラグ情報
 */
CtSynchro::FlgInfo	CtSynchro::allocFlgInfo()
{
	SYSWRAP_ERROR ercd;
	FlgInfo	info;
	unsigned int bit;

	/* 初期化する */
	initFlgInfo( info );

	/* 未使用のbitを探す */
	ercd = syswrap_wait_semaphore(&m_Semaphore, SYSWRAP_TIMEOUT_FOREVER);
	for ( bit = 0; bit < ms_MaxBit; ++bit ) {
		if ( ( ms_FlgPtnMap & ( 1 << bit ) ) == 0 ) {
			info.flgptn = ( 1 << bit );
			info.flg = &m_Event;
			ms_FlgPtnMap |= ( 1 << bit );
			break;
		}
	}
	ercd = syswrap_post_semaphore(&m_Semaphore);

	return info;
}

/** イベントフラグ情報を解放する
 *
 * @retval Ct_E_OK		成功
 * @retval Ct_E_OK以外	失敗
 */
bool CtSynchro::freeFlgInfo( const FlgInfo &info )
{
	bool bRet = false;
	SYSWRAP_ERROR ercd;

	/* 有効なFlgInfoかどうか確認 */
	if ( !isValidFlgInfo( info ) ) {
		goto failed0;
	}
	ercd = syswrap_wait_semaphore(&m_Semaphore, SYSWRAP_TIMEOUT_FOREVER);
	ms_FlgPtnMap &= ~info.flgptn;
	ercd = syswrap_post_semaphore(&m_Semaphore);

	bRet = true;

failed0:
	return bRet;
}

/** コンストラクタ */
CtSynchro::CtSynchro() : m_FlgInfo( allocFlgInfo() )
{
	//Ct_SET_CLASSID(Ct_CLS_SYNCHRO);
	//Ct_ASSERT( isValidFlgInfo( m_FlgInfo ) );
}



/** デストラクタ */
CtSynchro::~CtSynchro()
{
	freeFlgInfo( m_FlgInfo );
}


/***********************************
public member.
***********************************/
/** 同期通知を待つ
 * 
 * @param [in]	tout	タイムアウト（単位：ミリ秒）
 * @retval Ct_E_OK		成功
 * @retval Ct_E_OK以外	失敗
 */
bool CtSynchro::wait(long timeout)
{
	bool bRet = false;
	unsigned int retptn;
	SYSWRAP_ERROR ercd;

	/* 有効なFlgInfoかどうか確認 */
	if ( !isValidFlgInfo( m_FlgInfo ) ) {
		goto failed0;
	}

	ercd = syswrap_wait_event(m_FlgInfo.flg, m_FlgInfo.flgptn, SYSWRAP_WAITFMODE_ANDW, &retptn, timeout);
	if ( ercd != SYSWRAP_ERR_OK ) {
		if ( ercd == SYSWRAP_ERR_TIMEOUT ) {
			/* タイムアウト */
			goto failed0;
		}
		goto failed0;
	}

	/* 同時に複数のFSタスクが動く場合 や 上位タスクの方が優先度が
	   高い場合は、flgptn と retptn が異なる事はありうる。 */

	ercd = syswrap_clear_event(m_FlgInfo.flg, ~m_FlgInfo.flgptn);
	if ( ercd != SYSWRAP_ERR_OK ) {
		goto failed0;
	}

	bRet = true;

failed0:
	return bRet;
}



/** 同期通知を行う
 * 
 * @retval Ct_E_OK		成功
 * @retval Ct_E_OK以外	失敗
 */
bool CtSynchro::notify()
{
	bool	bRet = false;
	SYSWRAP_ERROR ercd;

	/* 有効なFlgInfoかどうか確認 */
	if ( !isValidFlgInfo( m_FlgInfo ) ) {
		goto failed0;
	}

	ercd = syswrap_set_event(m_FlgInfo.flg, m_FlgInfo.flgptn);
	if ( ercd != SYSWRAP_ERR_OK ) {
		goto failed0;
	}
	bRet = true;

failed0:
	return bRet;
}


