#include "pthread_common.h"
#include "pthread_event_flag.h"
#include "pthread_variable_mempool.h"
#include "pthread_messagebox.h"
#include "pthread_semaphore.h"
#include "pthread_thread.h"
#include "pthread_cycle_handler.h"

void init_pthread_lib()
{
	init_eventflag_table();
	init_mbox_table();
	init_mutex_table();
	init_thread_table();
	init_cyclehandler_table();
}


#define THREAD_CYCLE_TIME 1
void cycle_thread()
{
	struct timespec ts;
	int			 ret;

	pthread_mutex_t mutex;
	pthread_cond_t  cond;

	init_mutex(&mutex);
	pthread_cond_init(&cond, NULL);

	pthread_mutex_lock(&mutex);

	get_passage_time(&ts, THREAD_CYCLE_TIME);	//3ms�P�ʂŋN��������

	do {
		ret = pthread_cond_timedwait(&cond, &mutex, &ts);
		if (ETIMEDOUT == ret) {
			thread_cycletimer();	//���Ԃ��o�߂����珈������
			get_passage_time(&ts, THREAD_CYCLE_TIME);	//1ms�P�ʂŋN��������
		}
		else if (ERR_OK != ret) {
			break;					//�ُ픭����
		}
	} while (1);

	pthread_mutex_unlock(&mutex);
}
