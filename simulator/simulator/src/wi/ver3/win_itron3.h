/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron3.h
 *
 *	@brief	Windows版 iTRON(Ver3.0)サービスコール.
 *
 *	@author	金澤 宣明
 */
#ifndef	__WIN_ITRON3_H__
#define	__WIN_ITRON3_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * データ･タイプ.
 *
 ****************************************************************************/
typedef int				INT;			//!< 符号付き整数.
typedef unsigned int	UINT;			//!< 符号無し整数.
typedef	void			*VP;			//!< ポインタ変数.
typedef void			(*FP)();		//!< 関数アドレス.
typedef	VP				VP_INT;			//!< VP または INT.
typedef	INT				ER;				//!< エラーコード.
typedef	INT				HNO;			//!< ハンドラ番号.
typedef	INT				RNO;			//!< ランデブ番号.
typedef	INT				ID;				//!< ID番号.
typedef	UINT			ATR;			//!< 属性.
typedef	INT				PRI;			//!< タスク優先度.
typedef	INT				BOOL_ID;		//!< BOOL または ID.
typedef	INT				ER_UINT;		//!< エラーコード または UINT.

/*!
 *
 * @brief タイマ構造体.
 *
 */
typedef struct {
	short				utime;			//!< 上位16ビット.
	unsigned long		ltime;			//!< 下位32ビット.
} SYSTIME;

typedef	SYSTIME			CYCTIME;		//!< 周期ハンドラの時間.
typedef	SYSTIME			ALMTIME;		//!< アラームハンドラの時間.
typedef	long			DLYTIME;		//!< タスクディレイ時間.
typedef	long			TMO;			//!< タイムアウト設定値.

#define	TASK			void			//!< タスクの関数タイプ.
#define TMRHDR			void			//!< タイマ･ハンドラの関数タイプ.
#define INTHDR			void			//!< 割り込みハンドラの関数タイプ.

/****************************************************************************
 *
 * シンボル定義.
 *
 ****************************************************************************/
//! オブジェクトの属性.
#define TA_ASM	 	0x0000				//!< アセンブラによるプログラム.
#define TA_HLNG 	0x0001				//!< 高級言語によるプログラム.
#define TA_TFIFO	0x0000				//!< 待ちタスクはFIFO.
#define TA_TPRI 	0x0001				//!< 待ちタスクは優先度順.

//! タイムアウト設定.
#define TMO_POL 	0					//!< ポーリング.
#define TMO_FEVR	(-1)				//!< 永久待ち.

/****************************************************************************
 *
 * エラーコード.
 *
 ****************************************************************************/
#define E_OK		0					//!< 正常終了.
#define E_SYS		(-5)				//!< システムエラー.
#define E_NOMEM 	(-10)				//!< メモリ不足.
#define E_NOSPT 	(-17)				//!< 未サポート機能.
#define E_INOSPT	(-18)				//!< ITRON/FILEでの未サポート機能.
#define E_RSFN		(-20)				//!< 予約機能コード番号.
#define E_RSATR 	(-24)				//!< 予約属性.
#define E_PAR		(-33)				//!< パラメータエラー.
#define E_ID		(-35)				//!< 不正ID番号.
#define E_NOEXS 	(-52)				//!< オブジェクトが存在しない.
#define E_OBJ		(-63)				//!< オブジェクトの状態が不正.
#define E_MACV		(-65)				//!< メモリアクセス不能、メモリアクセス権違反.
#define E_OACV		(-66)				//!< オブジェクトアクセス権違反.
#define E_CTX		(-69)				//!< コンテキストエラー.
#define E_QOVR		(-73)				//!< キューイングまたはネストのオーバーフロー.
#define E_DLT		(-81)				//!< 待ちオブジェクトが削除された.
#define E_TMOUT 	(-85)				//!< ポーリング失敗またはタイムアウト.
#define E_RLWAI 	(-86)				//!< 待ち状態強制解除.
#define E_ILUSE		E_OBJ				//!< サービスコール不正使用.

/****************************************************************************
 *
 * タスク管理機能.
 *
 ****************************************************************************/
/*!
 *
 * @brief タスク生成情報構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			tskatr;				//!< タスクの属性.
	FP			task;				//!< スタート･アドレス.
	PRI			itskpri;			//!< 初期のタスク優先度.
	INT			stksz;				//!< スタック･サイズ.
} T_CTSK;

/*!
 *
 * @brief タスク状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	PRI			tskpri; 			//!< 現在の優先度.
	UINT		tskstat;			//!< タスク状態.
	UINT		tskwait;			//!< 待ち要因.
	ID			wid; 				//!< 待ちオブジェクトID.
	INT			wupcnt;				//!< 起床要求カウント.
	INT			suscnt;				//!< サスペンド要求カウント.
	ATR			tskatr; 			//!< タスク属性.
	FP			task;				//!< タスクの起動アドレス.
	PRI			itskpri;			//!< タスク起動時優先度.
	INT			stksz;				//!< スタックサイズ.
} T_RTSK;

/*!
 *
 * @brief タスクID設定値.
 *
 */
#define TSK_SELF	0				//!< 自タスク指定.
 
/*!
 *
 * @brief タスク優先度(tskpri).
 *
 */
#define TPRI_INI	0				//!< タスク起動時の初期優先度を指定 (chg_pri).
#define TPRI_RUN	0				//!< その時実行中の最高優先度を指定 (rot_rdq).

/*!
 *
 * @brief タスク実行状態(tskstat).
 *
 */
#define	TTS_RUN 	0x0001			//!< タスク実行状態.
#define	TTS_RDY 	0x0002			//!< タスク実行可能状態.
#define	TTS_WAI 	0x0004			//!< タスク待ち状態.
#define	TTS_SUS 	0x0008			//!< 強制待ち状態.
#define	TTS_WAS 	0x000C			//!< 二重待ち状態.
#define	TTS_DMT 	0x0010			//!< タスク休止中.
 
/*!
 *
 * @brief タスク待ち要因(tskwait).
 *
 */
#define TTW_SLP 	0x0001			//!< 起床待ち.
#define TTW_DLY 	0x0002			//!< 時間経過待ち.
#define TTW_FLG 	0x0010			//!< イベントフラグ待ち.
#define TTW_SEM 	0x0020			//!< セマフォ資源獲得待ち.
#define TTW_MBX 	0x0040			//!< メールボックスからの受信待ち.
#define TTW_SMBF	0x0080			//!< メッセージバッファへの送信待ち.
#define TTW_RMBF 	0x0100			//!< メッセージバッファからの受信待ち.
#define TTW_CAL 	0x0200			//!< ランデブ呼出待ち.
#define TTW_ACP 	0x0400			//!< ランデブ受付待ち.
#define TTW_RDV 	0x0800			//!< ランデブ終了待ち.
#define TTW_MPL 	0x1000			//!< 可変長メモリブロックの獲得待ち.
#define TTW_MPF 	0x2000			//!< 固定長メモリブロックの獲得待ち.
#define TTW_SDTQ 	0x0000			//!< データキューへの送信待ち   (Ver3.0では使用しない).
#define TTW_RDTQ 	0x0000			//!< データキューからの受信待ち (Ver3.0では使用しない).
#define TTW_MTX 	0x0000			//!< ミューテックスのロック待ち (Ver3.0では使用しない).

// サービスコールの定義.
ER		cre_tsk( ID tskid, const T_CTSK *pk_ctsk );
ER		del_tsk( ID tskid );
ER		sta_tsk( ID tskid, VP_INT stacd );
void	ext_tsk( void );
void	exd_tsk( void );
ER		ter_tsk( ID tskid );
ER		chg_pri( ID tskid, PRI tskpri );
ER		ref_tsk( T_RTSK *pk_rtsk, ID tskid );
ER		slp_tsk( void );
ER		tslp_tsk( TMO tmout );
ER		wup_tsk( ID tskid );
ER		can_wup( INT *p_wupcnt, ID tskid );
ER		rel_wai( ID tskid );
ER		sus_tsk( ID tskid );
ER		rsm_tsk( ID tskid );
ER		frsm_tsk( ID tskid );
ER		dly_tsk( DLYTIME dlytim );
 
/****************************************************************************
 *
 * 同期･通信機能 (セマフォ).
 *
 ****************************************************************************/
/*!
 *
 * @brief セマフォ生成情報構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			sematr;				//!< セマフォの属性.
	INT			isemcnt;			//!< セマフォの初期値.
	INT			maxsem; 			//!< セマフォの最大値.
} T_CSEM;

/*!
 *
 * @brief セマフォ状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	BOOL_ID 	wtsk;				//!< 待ちタスクの有無.
	INT			semcnt;				//!< 現在のセマフォカウント値.
} T_RSEM;

// サービスコールの定義.
ER		cre_sem( ID semid, const T_CSEM *pk_csem );
ER		del_sem( ID semid );
ER		sig_sem( ID semid );
ER		wai_sem( ID semid );
ER		pol_sem( ID semid );
ER		twai_sem( ID semid, TMO tmout );
ER		ref_sem( T_RSEM *pk_rsem, ID semid );

/****************************************************************************
 *
 * 同期･通信機能 (イベントフラグ).
 *
 ****************************************************************************/
/*!
 *
 * @brief イベントフラグ生成情報構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			flgatr;				//!< イベントフラグの属性.
	UINT		iflgptn;			//!< イベントフラグの初期値.
} T_CFLG;

/*!
 *
 * @brief イベントフラグ状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	BOOL_ID		wtsk;				//!< 待ちタスクの有無.
	UINT		flgptn;				//!< イベントフラグのビットパターン.
} T_RFLG;

/*!
 *
 * @brief イベントフラグ属性(flgatr).
 *
 */
#define TA_WSGL 	0x0000			//!< 複数タスクの待ちを許さない.
#define TA_WMUL 	0x0008			//!< 複数タスクの待ちを許す.
#define	TA_CLR		0x0004			//!< フラグパターンのクリア (Ver3.0では使わない).

/*!
 *
 * @brief イベントフラグの待ち条件(wfmode).
 *
 */
#define	TWF_ANDW	0x0000			//!< AND待ち.
#define	TWF_ORW 	0x0002			//!< OR待ち.
#define	TWF_CLR 	0x0001			//!< クリア指定.

// サービスコールの定義.
ER		cre_flg( ID flgid, const T_CFLG *pk_cflg );
ER		del_flg( ID flgid );
ER		set_flg( ID flgid, UINT setptn );
ER		clr_flg( ID flgid, UINT clrptn );
ER		wai_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode );
ER		pol_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode );
ER		twai_flg( UINT *p_flgptn, ID flgid, UINT waiptn, UINT wfmode, TMO tmout );
ER		ref_flg( T_RFLG *pk_rflg, ID flgid );

/****************************************************************************
 *
 * 同期･通信機能 (メールボックス).
 *
 ****************************************************************************/
/*!
 *
 * @brief メッセージ･パケット構造体.
 *
 */
typedef struct _T_MSG {
	struct _T_MSG	*nextmsg;		//!< 次のメッセージ･パケット構造体のポインタ.
	PRI				msgpri;			//!< メッセージの優先度.
} T_MSG;

/*!
 *
 * @brief メールボックス生成情報構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			mbxatr;				//!< メールボックスの属性.
} T_CMBX;

/*!
 *
 * @brief メールボックス状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	BOOL_ID		wtsk;				//!< 待ちタスクの有無.
	T_MSG		*pk_msg;			//!< 次に受信されるメッセージ.
} T_RMBX;

/*!
 *
 * @brief メールボックス属性(mbxatr).
 *
 */
#define TA_MFIFO	0x0000			//!< メッセージはFIFO.
#define TA_MPRI 	0x0002			//!< メッセージは優先度順.
 
// サービスコールの定義.
ER		cre_mbx( ID mbxid, const T_CMBX *pk_cmbx );
ER		del_mbx( ID mbxid );
ER		snd_msg( ID mbxid, T_MSG *pk_msg );
ER		rcv_msg( T_MSG **ppk_msg, ID mbxid );
ER		prcv_msg( T_MSG **ppk_msg, ID mbxid );
ER		trcv_msg( T_MSG **ppk_msg, ID mbxid, TMO tmout );
ER		ref_mbx( T_RMBX *pk_rmbx, ID mbxid );
 
/****************************************************************************
 *
 * 拡張同期･通信機能 (メッセージバッファ).
 *
 ****************************************************************************/
/*!
 *
 * @brief メッセージバッファ生成情報構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			mbfatr; 			//!< メッセージバッファの属性.
	INT			bufsz;				//!< メッセージバッファのサイズ.
	INT			maxmsz; 			//!< メッセージの最大長.
} T_CMBF;

/*!
 *
 * @brief メッセージバッファ状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	BOOL_ID		wtsk;				//!< 受信待ちタスクの有無.
	BOOL_ID		stsk;				//!< 送信待ちタスクの有無.
	INT			msgsz;				//!< 次に受信されるメッセージのサイズ.
	INT			frbufsz;			//!< 空きバッファのサイズ.
} T_RMBF;

// サービスコールの定義.
ER		cre_mbf( ID mbfid, const T_CMBF *pk_cmbf );
ER		del_mbf( ID mbfid );
ER		snd_mbf( ID mbfid, VP msg, INT msgsz );
ER		psnd_mbf( ID mbfid, VP msg, INT msgsz );
ER		tsnd_mbf( ID mbfid, VP msg, INT msgsz, TMO tmout );
ER		rcv_mbf( VP msg, INT *p_msgsz, ID mbfid );
ER		prcv_mbf( VP msg, INT *p_msgsz, ID mbfid );
ER		trcv_mbf( VP msg, INT *p_msgsz, ID mbfid, TMO tmout );
ER		ref_mbf( T_RMBF *pk_rmbf, ID mbfid );

/****************************************************************************
 *
 * 拡張同期･通信機能 (ランデブ).
 *
 ****************************************************************************/
/*!
 *
 * @brief ランデブポート生成情報構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			poratr; 			//!< ポート属性.
	INT			maxcmsz;			//!< 呼出時のメッセージの最大長.
	INT			maxrmsz;			//!< 返答時のメッセージの最大長.
} T_CPOR;

/*!
 *
 * @brief ランデブポート状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	BOOL_ID		wtsk;				//!< 呼出待ちタスクの有無.
	BOOL_ID		atsk;				//!< 受付待ちタスクの有無.
} T_RPOR;

// サービスコールの定義.
ER		cre_por( ID porid, const T_CPOR *pk_cpor );
ER		del_por( ID porid );
ER		cal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz );
ER		pcal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz );
ER		tcal_por( VP msg, INT *p_rmsgsz, ID porid, UINT calptn, INT cmsgsz, TMO tmout );
ER		acp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn );
ER		pacp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn );
ER		tacp_por( RNO *p_rdvno, VP msg, INT *p_cmsgsz, ID porid, UINT acpptn, TMO tmout );
ER		fwd_por( ID porid, UINT calptn, RNO rdvno , VP msg, INT cmsgsz );
ER		rpl_rdv( RNO rdvno, VP msg, INT cmsgsz );
ER		ref_por( T_RPOR *pk_rpor, ID porid );

/****************************************************************************
 *
 * メモリプール管理機能 (固定長メモリプール).
 *
 ****************************************************************************/
/*!
 *
 * @brief 固定長メモリプール生成情報構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			mpfatr; 			//!< 固定長メモリプールの属性.
	INT			mpfcnt; 			//!< 固定長メモリプール全体のブロック数.
	INT			blfsz;				//!< 固定長メモリ･ブロックのサイズ.
} T_CMPF;

/*!
 *
 * @brief 固定長メモリプール状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	BOOL_ID		wtsk;				//!< 待ちタスクの有無.
	INT			frbcnt; 			//!< 空きブロックの個数.
} T_RMPF;

// サービスコールの定義.
ER		cre_mpf( ID mpfid, const T_CMPF *pk_cmpf );
ER		del_mpf( ID mpfid );
ER		get_blf( VP *p_blf, ID mpfid );
ER		pget_blf( VP *p_blf, ID mpfid );
ER		tget_blf( VP *p_blf, ID mpfid, TMO tmout );
ER		rel_blf( ID mpfid, VP blk );
ER		ref_mpf( T_RMPF *pk_rmpf, ID mpfid );

/****************************************************************************
 *
 * メモリプール管理機能 (可変長メモリプール).
 *
 ****************************************************************************/
/*!
 *
 * @brief 可変長メモリプール生成情報構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			mplatr; 			//!< 可変長メモリプール属性.
	INT			mplsz;				//!< 可変長メモリプールのサイズ.
} T_CMPL; 

/*!
 *
 * @brief 可変長メモリプール状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	BOOL_ID		wtsk;				//!< 待ちタスクの有無.
	INT			frsz;				//!< 空き領域の合計サイズ.
	INT			maxsz;				//!< 最大の連続空き領域のサイズ.
} T_RMPL; 

// サービスコールの定義.
ER		cre_mpl( ID mplid, const T_CMPL *pk_cmpl );
ER		del_mpl( ID mplid );
ER		get_blk( VP p_blk, ID mplid, INT blksz );
ER		pget_blk( VP p_blk, ID mplid, INT blksz );
ER		tget_blk( VP p_blk, ID mplid, INT blksz, TMO tmout );
ER		rel_blk( ID mplid, VP blk );
ER		ref_mpl(T_RMPL *pk_rmpl, ID mplid );

/****************************************************************************
 *
 * 時間管理機能.
 *
 ****************************************************************************/

// サービスコールの定義.
ER		set_tim( const SYSTIME *pk_tim );
ER		get_tim( SYSTIME *pk_tim );

#define	ret_tmr()	return

/****************************************************************************
 *
 * 時間管理機能 (周期ハンドラ).
 *
 ****************************************************************************/
/*!
 *
 * @brief 周期ハンドラ定義情報用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			cycatr; 			//!< 周期ハンドラ属性.
	FP			cychdr;				//!< 周期ハンドラのアドレス.
	UINT		cycact;				//!< 周期ハンドラの活性状態.
	CYCTIME		cyctim; 			//!< 周期起動時間間隔.
} T_DCYC;

/*!
 *
 * @brief 周期ハンドラ状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	CYCTIME		lfttim; 			//!< 次の起動周期までの時間.
	UINT		cycact;				//!< 周期ハンドラの活性状態.
} T_RCYC;

/*!
 *
 * @brief 周期ハンドラ活性状態(cycact).
 *
 */
#define	TCY_OFF 	0x0000			//!< 周期ハンドラの停止.
#define	TCY_ON		0x0001			//!< 周期ハンドラの起動.
#define	TCY_INI 	0x0002			//!< 周期カウンタの初期化.

// サービスコールの定義.
ER		def_cyc( HNO cycno, const T_DCYC *pk_dcyc );
ER		act_cyc( HNO cycno, UINT cycact );
ER		ref_cyc( T_RCYC *pk_rcyc, HNO cycno );

/****************************************************************************
 *
 * 時間管理機能 (アラーム･ハンドラ).
 *
 ****************************************************************************/
/*!
 *
 * @brief アラーム･ハンドラ定義情報用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ATR			almatr; 			//!< アラーム･ハンドラ属性.
	FP			almhdr;				//!< アラーム･ハンドラのアドレス.
	UINT		tmmode;				//!< 起動時刻指定モード.
	ALMTIME		almtim; 			//!< 起動時刻.
} T_DALM;

/*!
 *
 * @brief アラーム･ハンドラ状態の参照用構造体.
 *
 */
typedef struct {
	VP			exinf;				//!< 拡張情報.
	ALMTIME		lfttim; 			//!< 起動時刻までの時間.
} T_RALM;

/*!
 *
 * @brief 起動時刻指定モード(tmmode).
 *
 */
#define TTM_ABS 	0x0000			//!< 絶対時刻での指定.
#define TTM_REL 	0x0001			//!< 相対時刻での指定.

// サービスコールの定義.
ER		def_alm( HNO almno, const T_DALM *pk_dalm );
ER		ref_alm( T_RALM *pk_ralm, HNO almno );

/****************************************************************************
 *
 * 割り込み管理機能.
 *
 ****************************************************************************/
/*!
 *
 * @brief 割込みハンドラ定義情報用構造体.
 *
 */
typedef struct {
	ATR			intatr; 			//!< 割込みハンドラ属性.
	FP			inthdr;				//!< 割込みハンドラアドレス.
} T_DINT; 

// サービスコールの定義.
ER		def_int( UINT dintno, const T_DINT *pk_dint );
ER		dis_int( UINT eintno );
ER		ena_int( UINT eintno );
ER		loc_cpu( void );
ER		unl_cpu( void );
#define	ret_int()		return
#define	ret_wup( _a )	return

/****************************************************************************
 *
 * システム管理機能.
 *
 ****************************************************************************/
/*!
 *
 * @brief バージョン情報構造体.
 *
 */
typedef struct {
	unsigned short		maker;		//!< メーカー.
	unsigned short		id;			//!< 形式番号.
	unsigned short		spver;		//!< 仕様書バージョン.
	unsigned short		prver;		//!< 製品バージョン.
	unsigned short		prno[4];	//!< 製品管理情報.
	unsigned short		cpu;		//!< CPU情報.
	unsigned short		var;		//!< バリエーション記述子.
} T_VER;

/*!
 *
 * @brief システム情報構造体.
 *
 */
typedef struct {
	INT			sysstat;			//!< システム状態.
} T_RSYS;
 
/*!
 *
 * @brief コンフィグレーション構造体.
 *
 */
typedef struct {
	VP			dummy;				//!< 実装定義のみのためダミーのメンバ変数を定義.
} T_RCFG; 

/*!
 *
 * @brief システム状態(sysstat).
 *
 */
#define TSS_TSK 	0				//!< タスク部実行中でディスパッチを許可した通常の状態.
#define TSS_DDSP	1				//!< タスク部実行中でdis_dspを実行した後の状態(ディスパッチ禁止中).
#define TSS_LOC 	3				//!< タスク部実行中でloc_cpuを実行した後の状態(割込みおよびディスパッチ禁止中).
#define TSS_INDP	4				//!< タスク独立部(割り込みハンドラ、タイマハンドラ)実行中.

// サービスコールの定義.
ER		rot_rdq( PRI tskpri );
ER		get_tid( ID *p_tskid );
ER		dis_dsp( void );
ER		ena_dsp( void );
ER		ref_sys( T_RSYS *pk_rsys );
ER		get_ver( T_VER *pk_ver );
ER		ref_cfg( T_RCFG *pk_rcfg );

#ifdef __cplusplus
}
#endif
#endif	// __WIN_ITRON3_H__
/* End of file */
