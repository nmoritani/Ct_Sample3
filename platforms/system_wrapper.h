/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: system_wrapper.h
 */

#ifndef __SYSTEM_WRAPPER_H__
#define __SYSTEM_WRAPPER_H__

#include <string.h>
#include <errno.h>

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
#define NUM_OF_MESSAGEQUEUE		20
#define NUM_OF_CYCLICHANDLER	10
#define NUM_OF_THREAD			10
#define	NUM_OF_MEMORYPOOL		 4

	

// macro
#define ARRAY_NUM(array) (sizeof(array) / sizeof(array[0]))
#define	ZERO_CLEAR(var)	 (memset(&(var), 0, sizeof(var)))

extern SYSWRAP_ERROR system_wrapper_init();
extern SYSWRAP_ERROR system_wrapper_term();

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


// Mutex
typedef struct {
	int					id;
	void				*sysinfo;
} syswrap_mutex_t;

extern SYSWRAP_ERROR syswrap_mutex_initial();
extern SYSWRAP_ERROR syswrap_create_mutex(syswrap_mutex_t *mutex);
extern SYSWRAP_ERROR syswrap_destroy_mutex(syswrap_mutex_t *mutex);
extern SYSWRAP_ERROR syswrap_lock_mutex(syswrap_mutex_t *mutex);
extern SYSWRAP_ERROR syswrap_unlock_mutex(syswrap_mutex_t *mutex);

// Semaphore
typedef struct {
	int					id;
	unsigned int		cnt;
    void 				*sysinfo;
} syswrap_semaphore_t;

extern SYSWRAP_ERROR syswrap_semaphore_initial();
extern SYSWRAP_ERROR syswrap_create_semaphore(syswrap_semaphore_t *semaphore, unsigned int count);
extern SYSWRAP_ERROR syswrap_destroy_semaphore(syswrap_semaphore_t *semaphore);
extern SYSWRAP_ERROR syswrap_wait_semaphore(syswrap_semaphore_t *semaphore);
extern SYSWRAP_ERROR syswrap_post_semaphore(syswrap_semaphore_t *semaphore);

#define SYSWRAP_WAITATTR_THREAD_FIFO	0x01
#define SYSWRAP_WAITATTR_THREAD_PRI		0x02
#define SYSWRAP_WAITATTR_FLAGCLEAR		0x04

#define SYSWRAP_WAITFMODE_ANDW       0x00
#define SYSWRAP_WAITFMODE_ORW        0x01
#define SYSWRAP_WAITFMODE_CLEAR      0x10
#define SYSWRAP_WAITFMODE_BITCLR     0x20
#define SYSWRAP_TIMEOUT_POLLING	(unsigned int)0
#define SYSWRAP_TIMEOUT_FOREVER	(unsigned int)-1

// Event
typedef struct {
	int 			id;
	void 			*sysinfo;
} syswrap_event_t;

extern SYSWRAP_ERROR syswrap_event_initial();
extern SYSWRAP_ERROR syswrap_create_event(syswrap_event_t *pevent, unsigned int attr, unsigned int init_val);
extern SYSWRAP_ERROR syswrap_destroy_event(syswrap_event_t *pevent);
extern SYSWRAP_ERROR syswrap_set_event(syswrap_event_t *pevent, unsigned int pattern);
extern SYSWRAP_ERROR syswrap_wait_event(syswrap_event_t *pevent, unsigned int waiptn, unsigned int wfmode, unsigned int *pflgptn, long tmout);
extern SYSWRAP_ERROR syswrap_clear_event(syswrap_event_t *pevent, unsigned int clrptn);


// Message
typedef struct _message {
	struct _message *next;
	int priority;
	
} message_t;

typedef struct {
	int				id;
	void 			*sysinfo;
} syswrap_message_queue_t;

extern SYSWRAP_ERROR syswrap_message_initial();
extern SYSWRAP_ERROR syswrap_create_message_queue(syswrap_message_queue_t *message_queue);
extern SYSWRAP_ERROR syswrap_destroy_message_queue(syswrap_message_queue_t *message_queue);

extern SYSWRAP_ERROR syswrap_send_message(syswrap_message_queue_t *message_queue, message_t *msg);
extern SYSWRAP_ERROR syswrap_receive_message(syswrap_message_queue_t *message_queue, message_t **msg, long tmout);


// Thread
typedef enum {
	THREAD_ATTR_FIFO,
	THREAD_ATTR_PRI,
} THREAD_ATTR;

typedef void *(THREAD_FUNC)(void *);
typedef struct {
	int				id;
	void			*sysinfo;
} syswrap_thread_t;

extern SYSWRAP_ERROR syswrap_thread_initial();
extern SYSWRAP_ERROR syswrap_create_thread(syswrap_thread_t *pthread, THREAD_FUNC pfunc, unsigned int stack_size, int pri);
extern SYSWRAP_ERROR syswrap_destroy_thread(syswrap_thread_t *pthread);
extern SYSWRAP_ERROR syswrap_start_thread(syswrap_thread_t *pthread);
extern SYSWRAP_ERROR syswrap_stop_thread(syswrap_thread_t *pthread, long timeout);
extern SYSWRAP_ERROR syswrap_get_threadid(int *tid);
extern SYSWRAP_ERROR syswrap_delay_thread(long timeout);


// Cyclic Handler
typedef void (HANDLER_FUNC)();

typedef struct {
	int				id;
	void			*sysinfo;
} syswrap_cyclic_handler_t;


extern SYSWRAP_ERROR syswrap_cyclic_handler_initial();
extern SYSWRAP_ERROR syswrap_create_cyclic_handler(syswrap_cyclic_handler_t *cyclic_handler, HANDLER_FUNC pfunc, int cycle_time);
extern SYSWRAP_ERROR syswrap_destroy_cyclic_handler(syswrap_cyclic_handler_t *pCyclic);
extern SYSWRAP_ERROR syswrap_start_cyclic_handler(syswrap_cyclic_handler_t *pCyclic);
extern SYSWRAP_ERROR syswrap_stop_cyclic_handler(syswrap_cyclic_handler_t *pCyclic);
extern SYSWRAP_ERROR syswrap_thread_cyclic_timer();


// Memory Pool
typedef struct {
	int				id;
	unsigned int	size;
	unsigned int	align_size;
	void			*sysinfo;
} syswrap_memorypool_t;

extern SYSWRAP_ERROR syswrap_memorypool_initial();
extern SYSWRAP_ERROR syswrap_create_memorypool(syswrap_memorypool_t *pMem, size_t size, size_t align_size);
extern SYSWRAP_ERROR syswrap_destroy_memorypool(syswrap_memorypool_t *pMem);
extern SYSWRAP_ERROR syswrap_alloc_memory(syswrap_memorypool_t *pMem, size_t size, void** dst);
extern SYSWRAP_ERROR syswrap_free_memory(syswrap_memorypool_t *pMem, void* dst);


#endif	/* __CTPLATFORMS_WRAPPER_H__ */
