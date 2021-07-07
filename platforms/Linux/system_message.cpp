#include <stdio.h>
#include <stdlib.h>
#include "system_common.h"

typedef struct  {
	int            		use;
	int					msgcnt;
	message_t			msghead;
	pthread_mutex_t 	mutex;
	pthread_cond_t  	cond;
} message_queue_info_t;

/* global */
pthread_mutex_t 		mutex;	//メールボックスの生成・破棄用
message_queue_info_t	info_list[NUM_OF_MESSAGEQUEUE];


SYSWRAP_ERROR syswrap_message_initial()
{
	mutex_init(&mutex);

	ZERO_CLEAR(info_list);
	for (int i = 0; i < NUM_OF_MESSAGEQUEUE; i++) {
		info_list[i].use = false;
	}

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_message(syswrap_message_queue_t *message_queue)
{
	int i, j;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;

	if (message_queue == NULL)
		return SYSWRAP_ERR_PAR;

	pthread_mutex_lock(&mutex);

	for (i = 0; i < NUM_OF_MESSAGEQUEUE; i++) {
		if (info_list[i].use)
			continue;

		info_list[i].use = true;
		
		mutex_init(&info_list[i].mutex);
		pthread_cond_init(&info_list[i].cond, NULL);
		
		message_queue->sysinfo = &info_list[i];
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	pthread_mutex_unlock(&mutex);
	return errcode;
}

SYSWRAP_ERROR syswrap_delete_message(syswrap_message_queue_t *message_queue)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((message_queue == NULL) || (message_queue->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	pthread_mutex_lock(&mutex);

	message_queue_info_t *mbox = (message_queue_info_t *)message_queue->sysinfo;
	
	if (false == mbox->use) 
		errcode = SYSWRAP_ERR_PAR;
	
	if (pthread_mutex_destroy(&mbox->mutex) != 0)
		errcode = SYSWRAP_ERR_SYS;

	if (pthread_cond_destroy(&(mbox->cond)) != 0)
		errcode = SYSWRAP_ERR_SYS;

	ZERO_CLEAR(*mbox);
	message_queue->sysinfo = NULL;

	pthread_mutex_unlock(&mutex);
	
	return errcode;
}

SYSWRAP_ERROR syswrap_send_message(syswrap_message_queue_t *message_queue, message_t *msg)
{
	SYSWRAP_ERROR errcode;
	message_t *msgptr = NULL;

	if ((message_queue == NULL) || (message_queue->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	if (msg == NULL)
		return SYSWRAP_ERR_PAR;
	
	message_queue_info_t *mbox = (message_queue_info_t *)message_queue->sysinfo;

	pthread_mutex_lock(&(mbox->mutex));

	msg->next = NULL;

	msgptr = mbox->msghead;
	if (msgptr == NULL) {
		mbox->msghead = msg;
		
	} else {
		while (msgptr != NULL) {
			if (msgptr->next == NULL)
				break;
			msgptr = msgptr->next;
		}
		msgptr->next = msg;
	}
	pthread_cond_signal(&(mbox->cond));
	pthread_mutex_unlock(&(mbox->mutex));

	return errcode;
}

SYSWRAP_ERROR syswrap_receive_message(syswrap_message_queue_t *message_queue, message_t **msg, long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	int			 ret;
	unsigned int len = 0;

	if ((message_queue == NULL) || (message_queue->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	message_queue_info_t *mbox = (message_queue_info_t *)message_queue->sysinfo;
	
	pthread_mutex_lock(&(mbox->mutex));

	if (timeout == SYSWRAP_TIMEOUT_POLLING) {
		//		errcode = read_msgbuf(&(mbox->msgbuf), msg, &len);
		
	} else if (timeout == SYSWRAP_TIMEOUT_FOREVER) {
#if 0
		while (SYSWRAP_ERR_NOEXS == (errcode = read_msgbuf(&(mbox->msgbuf), msg, &len))) {
			pthread_cond_wait(&(mbox->cond), &(mbox->mutex));
		}
#endif		
	} else {
#if 0
		while (SYSWRAP_ERR_NOEXS == (errcode = read_msgbuf(&(mbox->msgbuf), msg, &len))) {
			syswrap_timeval_t tv;
			struct timespec to;
			syswrap_get_time(&tv);
			syswrap_add_time_ms(&tv, timeout);
			to.tv_sec = tv.tv_sec;
			to.tv_nsec = tv.tv_usec * 1000;
			
			ret = pthread_cond_timedwait(&(mbox->cond), &(mbox->mutex), &to);
			if (ETIMEDOUT == ret) {
				errcode = SYSWRAP_ERR_TMOUT;
				break;
			} else if (EINTR == ret) {
				/* continue (check ring buffer) */
			} else if (0 != ret) {
				errcode = SYSWRAP_ERR_SYS;
				break;
			} else {
				/* continue (check ring buffer) */
			}
		}
#endif
	}

	pthread_mutex_unlock(&(mbox->mutex));
	return errcode;
}

SYSWRAP_ERROR syswrap_is_remain_message(syswrap_message_queue_t *message_queue, int *exist)
{
	if ((message_queue == NULL) || (message_queue->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	message_queue_info_t *mbox = (message_queue_info_t *)message_queue->sysinfo;
#if 0	
	if (mbox->msgbuf.read_pos == mbox->msgbuf.write_pos) {
		*exist = false;
	} else {
		*exist = true;
	}
#endif	
	return SYSWRAP_ERR_OK;
}
