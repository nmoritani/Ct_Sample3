/** 同期制御クラス
 *
 * Copyright(c) 2018 Persol AVC Technology.
 * @file
 */

//#include "CtClassID.h"
#include "CtSynchro.h"
//#include "CtConvertErrorItron.h"

extern "C" {	// @@@
#include <kernel_id.h>
//#include "CtDebug.h"
}



/***********************************
static member.
***********************************/
const FLGPTN	CtSynchro::ms_InvalidFlgPtn = 0;
const UW 		CtSynchro::ms_MaxBit = TBIT_FLGPTN;/* ITRON仕様上16以上が保障されているが、
													   32未満の場合はコンパイルエラーさせる。 */
const ID		CtSynchro::ms_Flg = CT_FLGID_SYNCHRO;		/* 1つのイベントフラグで同期できるのは16タスクまで。
													   16以上のタスクが同期待ちする必要があれば、この
													   メンバーを配列にして、複数のイベントフラグで
													   実現できる。 */
FLGPTN			CtSynchro::ms_FlgPtnMap = 0;

/** イベントフラグの状態を初期化
 * 
 * @param [out]	イベントフラグ情報
 */
void	CtSynchro::initFlgInfo( FlgInfo &info )
{
	info.flgptn = ms_InvalidFlgPtn;
	info.flg = -1;	/* 無効な場合はflgptnしか参照されないので
					   適当な値を入れておく */
}

/** イベントフラグ情報を割り当てる
 * 
 * @retval イベントフラグ情報
 */
CtSynchro::FlgInfo	CtSynchro::allocFlgInfo()
{
	ER		ercd;
	FlgInfo	info;
	UW		bit;

	/* 初期化する */
	initFlgInfo( info );

	/* 未使用のbitを探す */
	ercd = wai_sem( CT_SEMID_SYNCHRO );
	//Ct_ASSERT( ercd == E_OK );
	for ( bit = 0; bit < ms_MaxBit; ++bit ) {
		if ( ( ms_FlgPtnMap & ( 1 << bit ) ) == 0 ) {
			info.flgptn = ( 1 << bit );
			info.flg = ms_Flg;
			ms_FlgPtnMap |= ( 1 << bit );
			break;
		}
	}
	ercd = sig_sem( CT_SEMID_SYNCHRO );
	//Ct_ASSERT( ercd == E_OK );

	//Ct_ASSERT( isValidFlgInfo( info ) );

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
	ER	ercd;

	/* 有効なFlgInfoかどうか確認 */
	if ( !isValidFlgInfo( info ) ) {
		goto failed0;
	}
	ercd = wai_sem( CT_SEMID_SYNCHRO );
	//Ct_ASSERT( ercd == E_OK );
	ms_FlgPtnMap &= ~info.flgptn;
	ercd = sig_sem( CT_SEMID_SYNCHRO );
	//Ct_ASSERT( ercd == E_OK );

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
bool CtSynchro::wait(W tout)
{
	bool bRet = false;
	FLGPTN	retptn;
	ER		ercd;

	/* 有効なFlgInfoかどうか確認 */
	if ( !isValidFlgInfo( m_FlgInfo ) ) {
		//Ct_ASSERT( 0 );
		goto failed0;
	}

	ercd = twai_flg( m_FlgInfo.flg, m_FlgInfo.flgptn, TWF_ANDW, &retptn, tout );
	if ( ercd != E_OK ) {
		if ( ercd == E_TMOUT ) {
			/* タイムアウト */
			goto failed0;
		}
		//Ct_ASSERT( 0 );
		goto failed0;
	}

	/* 同時に複数のFSタスクが動く場合 や 上位タスクの方が優先度が
	   高い場合は、flgptn と retptn が異なる事はありうる。 */
//	Ct_ASSERT( flgptn == retptn );

	ercd = clr_flg( m_FlgInfo.flg, ~m_FlgInfo.flgptn );
	if ( ercd != E_OK ) {
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
	ER		ercd;

	/* 有効なFlgInfoかどうか確認 */
	if ( !isValidFlgInfo( m_FlgInfo ) ) {
		goto failed0;
	}

#ifdef WIN32_GUI_SIM
	ercd = set_flg( m_FlgInfo.flg, m_FlgInfo.flgptn );
#else
	if ( sns_ctx() ) {
		ercd = iset_flg( m_FlgInfo.flg, m_FlgInfo.flgptn );
	}
	else {
		ercd = set_flg( m_FlgInfo.flg, m_FlgInfo.flgptn );
	}
#endif
	if ( ercd != E_OK ) {
		goto failed0;
	}

	bRet = true;

failed0:
	return bRet;
}


