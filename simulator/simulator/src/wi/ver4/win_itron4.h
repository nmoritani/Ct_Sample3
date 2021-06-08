/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	win_itron4.h
 *
 *	@brief	Windows版 iTRON(Ver4.0)サービスコール.
 *
 *	@author	金澤 宣明
 */
#ifndef	__WIN_ITRON4_H__
#define	__WIN_ITRON4_H__

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
typedef void			(*FP)();		//!< 関数エントリ･アドレス.
typedef	VP				VP_INT;			//!< VP または INT.
typedef	INT				ER;				//!< エラーコード.
typedef	INT				HNO;			//!< ハンドラ番号.
typedef	INT				RDVNO;			//!< ランデブ番号.
typedef	INT				ID;				//!< ID番号.
typedef	UINT			ATR;			//!< 属性.
typedef	INT				PRI;			//!< タスク優先度.
typedef	INT				FN;				//!< ファンクション･コード.
typedef	INT				ER_UINT;		//!< エラーコード または UINT.
typedef	INT				ER_ID;			//!< エラーコード または ID.
typedef UINT			STAT;			//!< 符号無し整数.
typedef UINT			INTNO;			//!< 割り込み番号.
typedef	UINT			TEXPTN;			//!< タスク例外要因.
typedef	UINT			FLGPTN;			//!< イベントフラグ･パターン.
typedef	UINT			RDVPTN;			//!< ランデブ条件.
typedef	UINT			MODE;			//!< 待ちモード.
typedef INT				BOOL;
typedef unsigned short	USHORT;
typedef short			SHORT;

typedef unsigned long long	UD;
typedef unsigned long		UW;
typedef unsigned short		UH;
typedef unsigned char		UB;
typedef signed long long	D;
typedef signed int			W;
typedef signed short		H;
typedef signed char			B;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/*!
 *
 * @brief タイマ構造体.
 *
 */
typedef struct
{
	short				utime;			//!< 上位16ビット.
    unsigned long		ltime;			//!< 下位32ビット.
} SYSTIME;

typedef SYSTIME			SYSTIM;

typedef	SYSTIME			RELTIM;			//!< 周期ハンドラの時間.
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
#define	TA_ACT		0x0002				//!< タスク生成後すぐに起動.
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
#define E_NOSPT 	(-9)				//!< 未サポート機能.
#define E_RSFN		(-10)				//!< 予約機能コード番号.
#define E_RSATR 	(-11)				//!< 予約属性.
#define E_PAR		(-17)				//!< パラメータエラー.
#define E_ID		(-18)				//!< 不正ID番号.
#define E_CTX		(-25)				//!< コンテキストエラー.
#define E_MACV		(-26)				//!< メモリアクセス不能、メモリアクセス権違反.
#define E_OACV		(-27)				//!< オブジェクトアクセス権違反.
#define E_ILUSE		(-28)				//!< サービスコール不正使用.
#define E_NOMEM 	(-33)				//!< メモリ不足.
#define E_NOID	 	(-34)				//!< ID番号不足.
#define E_OBJ		(-41)				//!< オブジェクトの状態が不正.
#define E_NOEXS 	(-42)				//!< オブジェクトが存在しない.
#define E_QOVR		(-43)				//!< キューイングまたはネストのオーバーフロー.
#define E_RLWAI 	(-49)				//!< 待ち状態強制解除.
#define E_TMOUT 	(-50)				//!< ポーリング失敗またはタイムアウト.
#define E_DLT		(-51)				//!< 待ちオブジェクトが削除された.
#define E_CLS		(-52)				//!< 待ちオブジェクトの状態が変化した.
#define E_WBLK		(-57)				//!< ノンブロッキング受付け.
#define E_BOVR		(-58)				//!< バッファオーバーフロー.

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
	ATR			tskatr;				//!< タスクの属性.
	VP_INT		exinf;				//!< 拡張情報.
	FP			task;				//!< スタート･アドレス.
	PRI			itskpri;			//!< 初期のタスク優先度.
	INT			stksz;				//!< スタック･サイズ.
	VP			stk;				//!< スタック領域の先頭アドレス.
} T_CTSK;

/*!
 *
 * @brief タスク状態の参照用構造体.
 *
 */
typedef struct {
	STAT		tskstat;			//!< タスク状態.
	PRI			tskpri; 			//!< 現在の優先度.
	PRI			tskbpri; 			//!< ベース優先度.
	STAT		tskwait;			//!< 待ち要因.
	ID			wobjid; 			//!< 待ちオブジェクトID.
	TMO			lefttmo;			//!< タイムアウトまでの時間.
	UINT		actcnt;				//!< 起動要求カウント.
	UINT		wupcnt;				//!< 起床要求カウント.
	UINT		suscnt;				//!< サスペンド要求カウント.
} T_RTSK;

/*!
 *
 * @brief タスク状態の参照用構造体 (簡易版).
 *
 */
typedef struct {
	STAT		tskstat;			//!< タスク状態.
	STAT		tskwait;			//!< 待ち要因.
} T_RTST;

/*!
 *
 * @brief タスク例外処理の定義用構造体.
 *
 */
typedef struct {
	ATR			texatr;				//!< タスク例外処理ルーチンの属性.
	FP			texrtn;				//!< タスク例外処理ルーチンのスタート･アドレス.
} T_DTEX;

/*!
 *
 * @brief タスク例外処理状態の参照用構造体.
 *
 */
typedef struct {
	STAT		texstat;			//!< タスク例外処理の状態.
	TEXPTN		pndptn; 			//!< 保留例外要因.
} T_RTEX;

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
#define TTW_SEM 	0x0004			//!< セマフォ資源獲得待ち.
#define TTW_FLG 	0x0008			//!< イベントフラグ待ち.
#define TTW_SDTQ 	0x0010			//!< データキューへの送信待ち.
#define TTW_RDTQ 	0x0020			//!< データキューからの受信待ち.
#define TTW_MBX 	0x0040			//!< メールボックスからの受信待ち.
#define TTW_MTX 	0x0080			//!< ミューテックスのロック待ち.
#define TTW_SMBF	0x0100			//!< メッセージバッファへの送信待ち.
#define TTW_RMBF	0x0200			//!< メッセージバッファからの受信待ち.
#define TTW_CAL 	0x0400			//!< ランデブ呼出待ち.
#define TTW_ACP 	0x0800			//!< ランデブ受付待ち.
#define TTW_RDV 	0x1000			//!< ランデブ終了待ち.
#define TTW_MPF 	0x2000			//!< 固定長メモリブロックの獲得待ち.
#define TTW_MPL 	0x4000			//!< 可変長メモリブロックの獲得待ち.

// サービスコールの定義.
ER		cre_tsk( ID tskid, const T_CTSK *pk_ctsk );
ER_ID	acre_tsk( const T_CTSK *pk_ctsk );
ER		del_tsk( ID tskid );
ER		act_tsk( ID tskid );
ER		iact_tsk( ID tskid );
ER_UINT	can_act( ID tskid );
ER		sta_tsk( ID tskid, VP_INT stacd );
void	ext_tsk( void );
void	exd_tsk( void );
ER		ter_tsk( ID tskid );
ER		chg_pri( ID tskid, PRI tskpri );
ER		get_pri( ID tskid, PRI *p_tskpri );
ER		ref_tsk( ID tskid, T_RTSK *pk_rtsk );
ER		ref_tst( ID tskid, T_RTST *pk_rtst );
ER		slp_tsk( void );
ER		tslp_tsk( TMO tmout );
ER		wup_tsk( ID tskid );
ER		iwup_tsk( ID tskid );
ER_UINT	can_wup( ID tskid );
ER		rel_wai( ID tskid );
ER		irel_wai( ID tskid );
ER		sus_tsk( ID tskid );
ER		rsm_tsk( ID tskid );
ER		frsm_tsk( ID tskid );
ER		dly_tsk( DLYTIME dlytim );
ER		def_tex( ID tskid, T_DTEX *pk_dtex );
ER		ras_tex( ID tskid, TEXPTN rasptn );
ER		iras_tex( ID tskid, TEXPTN rasptn );
ER		dis_tex( void );
ER		ena_tex( void );
INT		sns_tex( void );
ER		ref_tex( ID tskid, T_RTEX *pk_rtex );

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
	ATR			sematr;				//!< セマフォの属性.
	UINT		isemcnt;			//!< セマフォの初期値.
	UINT		maxsem; 			//!< セマフォの最大値.
} T_CSEM;

/*!
 *
 * @brief セマフォ状態の参照用構造体.
 *
 */
typedef struct {
	ID 			wtskid;				//!< セマフォ待ち行列の先頭のタスクのID番号.
	UINT		semcnt;				//!< 現在のセマフォカウント値.
} T_RSEM;

// サービスコールの定義.
ER		cre_sem( ID semid, const T_CSEM *pk_csem );
ER_ID	acre_sem( const T_CSEM *pk_csem );
ER		del_sem( ID semid );
ER		sig_sem( ID semid );
ER		isig_sem( ID semid );
ER		wai_sem( ID semid );
ER		pol_sem( ID semid );
ER		twai_sem( ID semid, TMO tmout );
ER		ref_sem( ID semid, T_RSEM *pk_rsem );

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
	ATR			flgatr;				//!< イベントフラグの属性.
	FLGPTN		iflgptn;			//!< イベントフラグの初期値.
} T_CFLG;

/*!
 *
 * @brief イベントフラグ状態の参照用構造体.
 *
 */
typedef struct {
	ID 			wtskid;				//!< イベントフラグ待ち行列の先頭のタスクのID番号.
	FLGPTN		flgptn;				//!< イベントフラグのビットパターン.
} T_RFLG;

/*!
 *
 * @brief イベントフラグ属性(flgatr).
 *
 */
#define TA_WSGL 	0x0000			//!< 複数タスクの待ちを許さない.
#define TA_WMUL 	0x0002			//!< 複数タスクの待ちを許す.
#define	TA_CLR		0x0004			//!< フラグパターンのクリア.

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
ER_ID	acre_flg( const T_CFLG *pk_cflg );
ER		del_flg( ID flgid );
ER		set_flg( ID flgid, FLGPTN setptn );
ER		iset_flg( ID flgid, FLGPTN setptn );
ER		clr_flg( ID flgid, FLGPTN clrptn );
ER		wai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn );
ER		pol_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn );
ER		twai_flg( ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout );
ER		ref_flg( ID flgid, T_RFLG *pk_rflg );

/****************************************************************************
 *
 * 同期･通信機能 (データキュー).
 *
 ****************************************************************************/
/*!
 *
 * @brief データキュー生成情報構造体.
 *
 */
typedef struct {
	ATR			dtqatr;				//!< データキューの属性.
	UINT		dtqcnt;				//!< データキュー領域の個数.
	VP			dtq;				//!< データキュー領域の先頭アドレス.
} T_CDTQ;

/*!
 *
 * @brief データキュー状態の参照用構造体.
 *
 */
typedef struct {
	ID 			stskid;				//!< データキューの送信待ち行列の先頭のタスクのID番号.
	ID 			rtskid;				//!< データキューの受信待ち行列の先頭のタスクのID番号.
	UINT		sdtqcnt;			//!< データキューに入っているデータ数.
} T_RDTQ;

// サービスコールの定義.
ER		cre_dtq( ID dtqid, const T_CDTQ *pk_cdtq );
ER_ID	acre_dtq( const T_CDTQ *pk_cdtq );
ER		del_dtq( ID dtqid );
ER		snd_dtq( ID dtqid, VP_INT data );
ER		psnd_dtq( ID dtqid, VP_INT data );
ER		ipsnd_dtq( ID dtqid, VP_INT data );
ER		tsnd_dtq( ID dtqid, VP_INT data, TMO tmout );
ER		fsnd_dtq( ID dtqid, VP_INT data );
ER		ifsnd_dtq( ID dtqid, VP_INT data );
ER		rcv_dtq( ID dtqid, VP_INT *p_data );
ER		prcv_dtq( ID dtqid, VP_INT *p_data );
ER		trcv_dtq( ID dtqid, VP_INT *p_data, TMO tmout );
ER		ref_dtq( ID dtqid, T_RDTQ *pk_rdtq );

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

typedef struct
{
	T_MSG   nextmsg;     /* message header */
	PRI     msgpri;     /* message priority */
} T_MSG_PRI;
	
/*!
 *
 * @brief メールボックス生成情報構造体.
 *
 */
typedef struct {
	ATR			mbxatr;				//!< メールボックスの属性.
	PRI			maxmpri;			//!< 送信されるメッセージ優先度の最大値.
	VP			mprihd;				//!< 優先度別のメッセージキューヘッダ領域のアドレス.
} T_CMBX;

/*!
 *
 * @brief メールボックス状態の参照用構造体.
 *
 */
typedef struct {
	ID 			wtskid;				//!< メールボックス待ち行列の先頭のタスクのID番号.
	T_MSG		*pk_msg;			//!< メッセージキューの先頭のメッセージパケットのアドレス.
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
ER_ID	acre_mbx( const T_CMBX *pk_cmbx );
ER		del_mbx( ID mbxid );
ER		snd_msg( ID mbxid, T_MSG *pk_msg );
ER		rcv_msg( ID mbxid, T_MSG **ppk_msg );
ER		prcv_msg( ID mbxid, T_MSG **ppk_msg );
ER		trcv_msg( ID mbxid, T_MSG **ppk_msg, TMO tmout );
ER		ref_mbx( ID mbxid, T_RMBX *pk_rmbx );
#define prcv_mbx	prcv_msg

/****************************************************************************
 *
 * 拡張同期･通信機能 (ミューテックス).
 *
 ****************************************************************************/
/*!
 *
 * @brief ミューテックス生成情報構造体.
 *
 */
typedef struct {
	ATR			mtxatr; 			//!< ミューテックスの属性.
	PRI			ceilpri;			//!< ミューテックスの上限優先度.
} T_CMTX;

/*!
 *
 * @brief ミューテックス状態の参照用構造体.
 *
 */
typedef struct {
	ID			htskid;				//!< ミューテックスをロックしているタスクのID番号.
	ID			wtskid;				//!< ミューテックス待ち行列の先頭のタスクID番号.
} T_RMTX;

#define	TA_INHERIT		0x02		//!< 優先度継承プロトコル.
#define	TA_CEILING		0x03		//!< 上限優先度プロトコル.

// サービスコールの定義.
ER		cre_mtx( ID mtxid, const T_CMTX *pk_cmtx );
ER_ID	acre_mtx( const T_CMTX *pk_cmtx );
ER		del_mtx( ID mtxid );
ER		loc_mtx( ID mtxid );
ER		ploc_mtx( ID mtxid );
ER		tloc_mtx( ID mtxid, TMO tmout );
ER		unl_mtx( ID mtxid );
ER		ref_mtx( ID mtxid, T_RMTX *pk_rmtx );

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
	ATR				mbfatr; 		//!< メッセージバッファの属性.
	UINT			maxmsz; 		//!< メッセージの最大サイズ.
	/*SIZE*/ UINT	mbfsz;			//!< メッセージバッファ領域のサイズ.
	VP				mbf;			//!< メッセージバッファ領域のアドレス.
} T_CMBF;

/*!
 *
 * @brief メッセージバッファ状態の参照用構造体.
 *
 */
typedef struct {
	ID 			stskid;				//!< メッセージバッファの送信待ち行列の先頭のタスクのID番号.
	ID 			rtskid;				//!< メッセージバッファの受信待ち行列の先頭のタスクのID番号.
	INT			smsgcnt;			//!< メッセージバッファに入っているメッセージの数.
	INT			fmbfsz;				//!< メッセージバッファの空き領域のサイズ.
} T_RMBF;

// サービスコールの定義.
ER		cre_mbf( ID mbfid, const T_CMBF *pk_cmbf );
ER_ID	acre_mbf( const T_CMBF *pk_cmbf );
ER		del_mbf( ID mbfid );
ER		snd_mbf( ID mbfid, VP msg, UINT msgsz );
ER		psnd_mbf( ID mbfid, VP msg, UINT msgsz );
ER		tsnd_mbf( ID mbfid, VP msg, UINT msgsz, TMO tmout );
ER_UINT	rcv_mbf( ID mbfid, VP msg );
ER_UINT	prcv_mbf( ID mbfid, VP msg );
ER_UINT	trcv_mbf( ID mbfid, VP msg, TMO tmout );
ER		ref_mbf( ID mbfid, T_RMBF *pk_rmbf );

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
	ATR			poratr; 			//!< ランデブポートの属性.
	UINT		maxcmsz;			//!< 呼出時のメッセージの最大長.
	UINT		maxrmsz;			//!< 返答時のメッセージの最大長.
} T_CPOR;

/*!
 *
 * @brief ランデブポート状態の参照用構造体.
 *
 */
typedef struct {
	ID 			ctskid;				//!< ランデブポートの呼出待ち行列の先頭のタスクのID番号.
	ID 			atskid;				//!< ランデブポートの受付待ち行列の先頭のタスクのID番号.
} T_RPOR;

/*!
 *
 * @brief ランデブ状態の参照用構造体.
 *
 */
typedef struct {
	ID 			wtskid;				//!< ランデブ終了待ち状態のタスクのID番号.
} T_RRDV;

// サービスコールの定義.
ER		cre_por( ID porid, const T_CPOR *pk_cpor );
ER_ID	acre_por( const T_CPOR *pk_cpor );
ER		del_por( ID porid );
ER_UINT	cal_por( ID porid, RDVPTN calptn, VP msg, UINT cmsgsz );
ER_UINT	tcal_por( ID porid, RDVPTN calptn, VP msg, UINT cmsgsz, TMO tmout );
ER_UINT	acp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg );
ER_UINT	pacp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg );
ER_UINT	tacp_por( ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg, TMO tmout );
ER		fwd_por( ID porid, RDVPTN calptn, RDVNO rdvno, VP msg, UINT cmsgsz );
ER		rpl_rdv( RDVNO rdvno, VP msg, UINT cmsgsz );
ER		ref_por( ID porid, T_RPOR *pk_rpor );
ER		ref_rdv( RDVNO rdvno, T_RRDV *pk_rrdv );

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
	ATR			mpfatr; 			//!< 固定長メモリプールの属性.
	UINT		blkcnt; 			//!< 確保できるメモリブロック数.
	UINT		blfsz;				//!< メモリブロックのサイズ.
	VP			mpf;				//!< 固定長メモリプール領域のアドレス.
} T_CMPF;

/*!
 *
 * @brief 固定長メモリプール状態の参照用構造体.
 *
 */
typedef struct {
	ID 			wtskid;				//!< 固定長メモリプールの待ち行列の先頭のタスクのID番号.
	UINT		fblkcnt; 			//!< 空きブロックの個数.
} T_RMPF;

// サービスコールの定義.
ER		cre_mpf( ID mpfid, const T_CMPF *pk_cmpf );
ER_ID	acre_mpf( const T_CMPF *pk_cmpf );
ER		del_mpf( ID mpfid );
ER		get_blf(ID mpfid, VP *p_blf );
ER		pget_blf(ID mpfid, VP *p_blf );
ER		tget_blf(ID mpfid, VP *p_blf, TMO tmout );
ER		rel_blf( ID mpfid, VP blk );
ER		ref_mpf( ID mpfid, T_RMPF *pk_rmpf );

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
	ATR				mplatr; 		//!< 可変長メモリプール属性.
	INT	/*SIZE*/	mplsz;			//!< 可変長メモリプールのサイズ.
	VP				mpl;			//!< 可変長メモリプール領域のアドレス.
} T_CMPL; 

/*!
 *
 * @brief 可変長メモリプール状態の参照用構造体.
 *
 */
typedef struct
{
	ID 				wtskid;			//!< 可変長メモリプールの待ち行列の先頭のタスクのID番号.
	INT	/*SIZE*/	fmplsz;			//!< 可変長メモリプールの空き領域の合計サイズ.
	UINT			fblksz;			//!< 獲得可能な最大の連続空き領域のサイズ.
} T_RMPL; 


// サービスコールの定義.
ER		cre_mpl( ID mplid , const T_CMPL *pk_cmpl );
ER		acre_mpl( const T_CMPL *pk_cmpl );
ER		del_mpl( ID mplid );
ER		get_mpl( ID mplid, UINT blksz, VP *p_blk );
ER		pget_mpl( ID mplid, UINT blksz, VP *p_blk );
ER		tget_mpl( ID mplid, UINT blksz, VP *p_blk, TMO tmout );
ER		rel_mpl( ID mplid, VP blk);
ER		rel_blk( ID mpfid, VP blk );
ER		ref_mpl( ID mplid, T_RMPL *pk_rmpl );

ER		iloc_cpu(void);
ER		iunl_cpu(void);

/****************************************************************************
 *
 * 時間管理機能.
 *
 ****************************************************************************/

// サービスコールの定義.
ER		set_tim( const SYSTIME *pk_tim );
ER		get_tim( SYSTIME *pk_tim );
ER		isig_tim( void );

#define	ret_tmr()	return;

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
	ATR			cycatr; 			//!< 周期ハンドラ属性.
	VP_INT		exinf;				//!< 拡張情報.
	FP			cychdr;				//!< 周期ハンドラのアドレス.
	RELTIM		cyctim; 			//!< 周期起動時間間隔.
	RELTIM		cycphs; 			//!< 周期起動位相.
} T_CCYC;

/*!
 *
 * @brief 周期ハンドラ状態の参照用構造体.
 *
 */
typedef struct {
	STAT		cycstat;			//!< 周期ハンドラの動作状態.
	RELTIM		lefttim; 			//!< 次の起動周期までの時間.
} T_RCYC;

/*!
 *
 * @brief 周期ハンドラの動作状態(cycstat).
 *
 */
#define	TCYC_STP		0x00		//!< 周期ハンドラが動作していない.
#define	TCYC_STA		0x01		//!< 周期ハンドラが動作している.

#define	TA_STA			0x02		//!< 周期ハンドラを起動.
#define	TA_PHS			0x04		//!< 周期ハンドラの起動位相あり.

// サービスコールの定義.
ER		cre_cyc( ID cycid, const T_CCYC *pk_ccyc );
ER		acre_cyc( const T_CCYC *pk_ccyc );
ER		del_cyc( ID cycid );
ER		sta_cyc( ID cycid );
ER		stp_cyc( ID cycid );
ER		ref_cyc( ID cycid, T_RCYC *pk_rcyc );

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
	ATR			almatr; 			//!< アラーム･ハンドラ属性.
	VP_INT		exinf;				//!< 拡張情報.
	FP			almhdr;				//!< アラーム･ハンドラのアドレス.
} T_CALM;

/*!
 *
 * @brief アラーム･ハンドラ状態の参照用構造体.
 *
 */
typedef struct {
	STAT		almstat;			//!< アラーム･ハンドラの動作状態.
	RELTIM		lefttim; 			//!< アラーム･ハンドラの起動時刻までの時間.
} T_RALM;

/*!
 *
 * @brief 起動時刻指定モード(tmmode).
 *
 */
#define TTM_ABS 	0x0000			//!< 絶対時刻での指定.
#define TTM_REL 	0x0001			//!< 相対時刻での指定.

/*!
 *
 * @brief アラーム･ハンドラの動作状態(almstat).
 *
 */
#define	TALM_STP		0x00		//!< アラーム･ハンドラが動作していない.
#define	TALM_STA		0x01		//!< アラーム･ハンドラが動作している.

// サービスコールの定義.
ER		cre_alm( ID almid, const T_CALM *pk_calm );
ER_ID	acre_alm( const T_CALM *pk_calm );
ER		del_alm( ID almid );
ER		sta_alm( ID almid, RELTIM almtim );
ER		stp_alm( ID almid );
ER		ref_alm( ID almid, T_RALM *pk_ralm );

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
	ATR			inhatr; 			//!< 割込みハンドラ属性.
	FP			inthdr;				//!< 割込みハンドラアドレス.
} T_DINH;

// サービスコールの定義.
ER		def_inh( INTNO intno, const T_DINH *pk_dinh );
ER		dis_int( INTNO intno );
ER		ena_int( INTNO intno );
ER		loc_cpu( void );
ER		unl_cpu( void );

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
	unsigned short	maker;			//!< メーカー.
	unsigned short	prid;			//!< カーネルの識別番号.
	unsigned short	spver;			//!< 仕様書バージョン.
	unsigned short	prver;			//!< カーネルのバージョン番号.
	unsigned short	prno[4];		//!< 製品管理情報.
} T_RVER;

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
ER		get_ver( T_RVER *pk_rver );
ER		ref_cfg( T_RCFG *pk_rcfg );

#ifdef __cplusplus
}
#endif
#endif	// __WIN_ITRON4_H__
/* End of file */
