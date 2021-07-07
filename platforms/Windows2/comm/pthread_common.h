#pragma once
#include "pthread.h"
#include "winlib/system_time_spec.h"


#define ERR_OK			0					//!< 正常終了.
#define ERR_SYS			(-5)				//!< システムエラー.
#define ERR_NOSPT 		(-9)				//!< 未サポート機能.
#define ERR_RSFN		(-10)				//!< 予約機能コード番号.
#define ERR_RSATR 		(-11)				//!< 予約属性.
#define ERR_PAR			(-17)				//!< パラメータエラー.
#define ERR_ID			(-18)				//!< 不正ID番号.
#define ERR_CTX			(-25)				//!< コンテキストエラー.
#define ERR_MACV		(-26)				//!< メモリアクセス不能、メモリアクセス権違反.
#define ERR_OACV		(-27)				//!< オブジェクトアクセス権違反.
#define ERR_ILUSE		(-28)				//!< サービスコール不正使用.
#define ERR_NOMEM 		(-33)				//!< メモリ不足.
#define ERR_NOID	 	(-34)				//!< ID番号不足.
#define ERR_OBJ			(-41)				//!< オブジェクトの状態が不正.
#define ERR_NOEXS 		(-42)				//!< オブジェクトが存在しない.
#define ERR_QOVR		(-43)				//!< キューイングまたはネストのオーバーフロー.
#define ERR_RLWAI 		(-49)				//!< 待ち状態強制解除.
#define ERR_TMOUT 		(-50)				//!< ポーリング失敗またはタイムアウト.
#define ERR_DLT			(-51)				//!< 待ちオブジェクトが削除された.
#define ERR_CLS			(-52)				//!< 待ちオブジェクトの状態が変化した.
#define ERR_WBLK		(-57)				//!< ノンブロッキング受付け.
#define ERR_BOVR		(-58)				//!< バッファオーバーフロー.


/* macro */
#define ARRAY_NUM(array) (sizeof(array) / sizeof(array[0]))
#define	ZERO_CLEAR(var)	 (memset(&(var), 0, sizeof(var)))

///////////////////////////////////////////////////////////////////////
//スレッド起動用引数定義
typedef void *(PTHREAD_START_FUNC)(void *);
#define PTHREAD_START_FUNC_CAST(f)	(void*(*)(void*))((f))
typedef struct _thread_arg {
	unsigned int		tskatr;				//!< タスクの属性.
	void				*exinf;				//!< 拡張情報.
	PTHREAD_START_FUNC	*task;				//!< スタート・アドレス.
	int					itskpri;			//!< 初期のタスク優先度.
	int					stksz;				//!< スタック・サイズ.
	void				*stk;				//!< スタック領域の先頭アドレス.
} thread_arg;


///////////////////////////////////////////////////////////////////////
//サイクリックハンドラ用引数定義
typedef void (CYCLETIMER__FUNC)();
#define CYCLETIMER_FUNC_CAST(f)		(void (*)())((f))
typedef struct _cycle_time_arg {
	unsigned int		attr; 				//!< 周期ハンドラ属性.
	CYCLETIMER__FUNC	*func;				//!< 周期ハンドラのアドレス.
	long				cycle_time;			//!< 周期起動時間間隔(ms単位)
} cycle_time_arg;

typedef struct _cycle_handler_state {
	bool	active;					// 周期ハンドラ動作状態
	long	remain_time; 			// 次起動周期までの時間
} cycle_handler_state;


///////////////////////////////////////////////////////////////////////
extern int create_cycle_timer_thread(unsigned int id, thread_arg *parg);
