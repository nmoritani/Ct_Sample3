/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: system_wrapper.h
 */

#ifndef __SYSTEM_WRAPPER_H__
#define __SYSTEM_WRAPPER_H__

#include "kernel_id.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define SYSTEM_WINDOWS
//#define SYSTEM_ITRON
//#define SYSTEM_LINUX
	
//#include <string.h>

typedef enum {
	SYSWRAP_ERR_OK			= 0,		//!< 正常終了.
	SYSWRAP_ERR_SYS			= -5,		//!< システムエラー.
	SYSWRAP_ERR_RESOVER		= -7,
	SYSWRAP_ERR_NOSPT 		= (-9),		//!< 未サポート機能.
	SYSWRAP_ERR_RSFN		= (-10),	//!< 予約機能コード番号.
	SYSWRAP_ERR_RSATR 		= (-11),	//!< 予約属性.
	SYSWRAP_ERR_PAR			= (-17),	//!< パラメータエラー.
	SYSWRAP_ERR_ID			= (-18),	//!< 不正ID番号.
	SYSWRAP_ERR_CTX			= (-25),	//!< コンテキストエラー.
	SYSWRAP_ERR_MACV		= (-26),	//!< メモリアクセス不能、メモリアクセス権違反.
	SYSWRAP_ERR_OACV		= (-27),	//!< オブジェクトアクセス権違反.
	SYSWRAP_ERR_ILLIGALUSE	= (-28),	//!< サービスコール不正使用.
	SYSWRAP_ERR_NOMEM 		= (-33),	//!< メモリ不足.
	SYSWRAP_ERR_NOID	 	= (-34),	//!< ID番号不足.
	SYSWRAP_ERR_OBJ			= (-41),	//!< オブジェクトの状態が不正.
	SYSWRAP_ERR_NOEXS 		= (-42),	//!< オブジェクトが存在しない.
	SYSWRAP_ERR_QOVR		= (-43),	//!< キューイングまたはネストのオーバーフロー.
	SYSWRAP_ERR_RLWAI 		= (-49),	//!< 待ち状態強制解除.
	SYSWRAP_ERR_TIMEOUT		= (-50),	//!< ポーリング失敗またはタイムアウト.
	SYSWRAP_ERR_DLT			= (-51),	//!< 待ちオブジェクトが削除された.
	SYSWRAP_ERR_CLS			= (-52),	//!< 待ちオブジェクトの状態が変化した.
	SYSWRAP_ERR_WBLK		= (-57),	//!< ノンブロッキング受付け.
	SYSWRAP_ERR_BOVR		= (-58),	//!< バッファオーバーフロー.
} SYSWRAP_ERROR;

#define NUM_OF_SEMAPHORE		50
#define NUM_OF_MUTEX			50
#define NUM_OF_EVENTFLAG		20
#define NUM_OF_MAILBOX			20
#define NUM_OF_CYCLICHANDLER	10
#define NUM_OF_THREAD			10
#define	NUM_OF_MEMORYPOOL		10

// macro
#define ARRAY_NUM(array) (sizeof(array) / sizeof(array[0]))
#define	ZERO_CLEAR(var)	 (memset(&(var), 0, sizeof(var)))

extern void system_wrapper_init();
extern void system_wrapper_term();

typedef struct {
	long tv_sec;
	long tv_usec;
} syswrap_timeval_t;

unsigned long syswrap_get_msec();
unsigned long syswrap_get_usec();
long syswrap_sub_sec(unsigned long sec1, unsigned long sec2);

SYSWRAP_ERROR syswrap_get_time(syswrap_timeval_t *tv);
SYSWRAP_ERROR syswrap_add_time(syswrap_timeval_t *tv, int msec);
long syswrap_sub_time(syswrap_timeval_t *tv1, syswrap_timeval_t *tv2);


// Thread
typedef enum {
	THREAD_ATTR_FIFO,
	THREAD_ATTR_PRI,
} THREAD_ATTR;

typedef enum {
	THREAD_STATE_ERROR = -1,
	THREAD_STATE_DORMANT = 0,	// 休止中
	THREAD_STATE_SUSPEND,		// 強制待ち状態
	THREAD_STATE_WAIT,			// 待ち状態
	THREAD_STATE_READY,			// 実行可能状態
	THREAD_STATE_RUN,			// 実行状態
	THREAD_STATE_MAX
} THREAD_STATE;

typedef enum {
	THREAD_PRI_LOWEST,
	THREAD_PRI_NORMAL_LOW,
	THREAD_PRI_NORMAL,
	THREAD_PRI_NORMAL_HIGH,
	THREAD_PRI_HIGHEST,
	THREAD_PRI_MAX
} THREAD_PRIORITY;

typedef void (*THREAD_FUNC)(void *);
typedef void (*FUNC)();
typedef struct {
	int				id;
	void			*sysinfo;
} syswrap_thread_t;

extern SYSWRAP_ERROR syswrap_thread_init();
extern SYSWRAP_ERROR syswrap_thread_term();
extern SYSWRAP_ERROR syswrap_create_thread(syswrap_thread_t *pthread, FUNC func, unsigned int stack_size, THREAD_PRIORITY pri);
extern SYSWRAP_ERROR syswrap_destroy_thread(syswrap_thread_t *pthread);
extern SYSWRAP_ERROR syswrap_start_thread(syswrap_thread_t *pthread);
extern SYSWRAP_ERROR syswrap_term_thread(syswrap_thread_t *pthread);
extern SYSWRAP_ERROR syswrap_delay_thread(long timeout);
extern SYSWRAP_ERROR syswrap_wait_term_thread(syswrap_thread_t *pthread, long timeout);

extern int syswrap_get_threadid(syswrap_thread_t *pthread);
extern THREAD_STATE syswrap_get_thread_state(syswrap_thread_t *pthread);


// Cyclic Handler
typedef void (*HANDLER_FUNC)(void *);
typedef void (*FUNC)();

typedef struct {
	int				id;
	void			*sysinfo;
} syswrap_cyclic_handler_t;


extern SYSWRAP_ERROR syswrap_cyclic_handler_init();
extern SYSWRAP_ERROR syswrap_cyclic_handler_term();
extern SYSWRAP_ERROR syswrap_create_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, FUNC func, int cycle_time);
extern SYSWRAP_ERROR syswrap_destroy_cyclic_handler(syswrap_cyclic_handler_t *pCyclic);
extern SYSWRAP_ERROR syswrap_start_cyclic_handler(syswrap_cyclic_handler_t *pCyclic);
extern SYSWRAP_ERROR syswrap_stop_cyclic_handler(syswrap_cyclic_handler_t *pCyclic);
extern SYSWRAP_ERROR syswrap_thread_cyclic_timer();
extern THREAD_STATE syswrap_get_cyclic_state(syswrap_cyclic_handler_t *pcyclic);


// Mutex
typedef struct {
	int					id;
	void				*sysinfo;
} syswrap_mutex_t;

extern SYSWRAP_ERROR syswrap_mutex_init();
extern SYSWRAP_ERROR syswrap_mutex_term();
extern SYSWRAP_ERROR syswrap_create_mutex(syswrap_mutex_t *mutex);
extern SYSWRAP_ERROR syswrap_destroy_mutex(syswrap_mutex_t *mutex);
extern SYSWRAP_ERROR syswrap_lock_mutex(syswrap_mutex_t *mutex, long timeout);
extern SYSWRAP_ERROR syswrap_unlock_mutex(syswrap_mutex_t *mutex);

// Semaphore
typedef struct {
	int					id;
	unsigned int		cnt;
    void 				*sysinfo;
} syswrap_semaphore_t;

extern SYSWRAP_ERROR syswrap_semaphore_init();
extern SYSWRAP_ERROR syswrap_semaphore_term();
extern SYSWRAP_ERROR syswrap_create_semaphore(syswrap_semaphore_t *semaphore, unsigned int count, THREAD_ATTR attr);
extern SYSWRAP_ERROR syswrap_destroy_semaphore(syswrap_semaphore_t *semaphore);
extern SYSWRAP_ERROR syswrap_wait_semaphore(syswrap_semaphore_t *semaphore, long timeout);
extern SYSWRAP_ERROR syswrap_post_semaphore(syswrap_semaphore_t *semaphore);
extern SYSWRAP_ERROR syswrap_get_semaphore_count(syswrap_semaphore_t *semaphore, int *count);

#define SYSWRAP_WAITATTR_THREAD_FIFO	0x01
#define SYSWRAP_WAITATTR_THREAD_PRI		0x02
#define SYSWRAP_WAITATTR_FLAGCLEAR		0x04

#define SYSWRAP_WAITFMODE_ANDW       	0x00
#define SYSWRAP_WAITFMODE_ORW        	0x02
#define SYSWRAP_WAITFMODE_CLEAR      	0x01
	
#define SYSWRAP_TIMEOUT_POLLING	(unsigned int)0
#define SYSWRAP_TIMEOUT_FOREVER	(unsigned int)-1

// Event
typedef struct {
	int 			id;
	void 			*sysinfo;
} syswrap_event_t;

extern SYSWRAP_ERROR syswrap_event_init();
extern SYSWRAP_ERROR syswrap_event_term();
extern SYSWRAP_ERROR syswrap_create_event(syswrap_event_t *pevent, THREAD_ATTR thread_att, unsigned int init_val);
extern SYSWRAP_ERROR syswrap_destroy_event(syswrap_event_t *pevent);
extern SYSWRAP_ERROR syswrap_set_event(syswrap_event_t *pevent, unsigned int pattern);
extern SYSWRAP_ERROR syswrap_wait_event(syswrap_event_t *pevent, unsigned int waiptn, unsigned int wfmode, unsigned int *pflgptn, long tmout);
extern SYSWRAP_ERROR syswrap_clear_event(syswrap_event_t *pevent, unsigned int clrptn);


// Message
typedef struct {
	int				id;
	void 			*sysinfo;
} syswrap_mailbox_t;

extern SYSWRAP_ERROR syswrap_message_init();
extern SYSWRAP_ERROR syswrap_message_term();
extern SYSWRAP_ERROR syswrap_create_mailbox(syswrap_mailbox_t *mailbox, THREAD_ATTR attr);
extern SYSWRAP_ERROR syswrap_destroy_mailbox(syswrap_mailbox_t *mailbox);

extern SYSWRAP_ERROR syswrap_send_message(syswrap_mailbox_t *mailbox, void *msg, int priority);
extern SYSWRAP_ERROR syswrap_receive_message(syswrap_mailbox_t *mailbox_queue, void **msg, long tmout);
extern int syswrap_get_remain_message(syswrap_mailbox_t *mailbox);


// Memory Pool
typedef struct {
	int				id;
	unsigned int	size;
	unsigned int	align_size;
	void			*sysinfo;
} syswrap_memorypool_t;

extern SYSWRAP_ERROR syswrap_memorypool_init();
extern SYSWRAP_ERROR syswrap_memorypool_term();
extern SYSWRAP_ERROR syswrap_create_memorypool(syswrap_memorypool_t *memorypool, int size, int align_size, void *addr);
extern SYSWRAP_ERROR syswrap_destroy_memorypool(syswrap_memorypool_t *memorypool);
extern SYSWRAP_ERROR syswrap_alloc_memory(syswrap_memorypool_t *memorypool, void **dst, int size);
extern SYSWRAP_ERROR syswrap_free_memory(syswrap_memorypool_t *memorypool, void *dst);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* __CTPLATFORMS_WRAPPER_H__ */
