#include <stdio.h>
#include <stdlib.h>
#include "system_common.h"

#define NUM_OF_MESSAGEDATA	64

#define NUM_OF_MESSAGE	100

typedef struct  {
	BOOL           		use;
	THREAD_ATTR			thread_attribute;
	thread_info_t		*thread_queue;
	
	int					message_count;
	int					message_priority;
	message_t			*message_queue;
} message_queue_info_t;

/* global */
message_queue_info_t	info_list[NUM_OF_MESSAGEQUEUE];


SYSWRAP_ERROR syswrap_message_initial()
{
	ZERO_CLEAR(info_list);

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_message(syswrap_message_queue_t *message_queue, THREAD_ATTR thread_attribute, int message_priority)
{
	int i;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;

	if (message_queue == NULL)
		return SYSWRAP_ERR_PAR;

	for (i = 0; i < NUM_OF_MESSAGEQUEUE; i++) {
		if (info_list[i].use)
			continue;

		info_list[i].use = TRUE;
		info_list[i].thread_attribute = thread_attribute;
		info_list[i].thread_queue = NULL;
		info_list[i].message_priority = message_priority;
		info_list[i].message_count = 0;
		
		message_queue->sysinfo = &info_list[i];
		errcode = SYSWRAP_ERR_OK;
		break;
	}
	return errcode;
}

SYSWRAP_ERROR syswrap_delete_message(syswrap_message_queue_t *message_queue)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((message_queue == NULL) || (message_queue->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	message_queue_info_t *mailbox = (message_queue_info_t *)message_queue->sysinfo;
	
	if (FALSE == mailbox->use) 
		errcode = SYSWRAP_ERR_PAR;
	
	ZERO_CLEAR(*mailbox);
	message_queue->sysinfo = NULL;

	return errcode;
}

SYSWRAP_ERROR syswrap_send_message(syswrap_message_queue_t *message_queue, message_t *message)
{
	message_t *tmp = NULL;

	if ((message_queue == NULL) || (message_queue->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	message_queue_info_t *mailbox = (message_queue_info_t *)message_queue->sysinfo;

	message->next = NULL;
	if (mailbox->thread_attribute & THREAD_ATTR_PRI) {
		
		if (mailbox->message_queue == NULL) {
			mailbox->message_queue = message;
			
		} else if (mailbox->message_queue->priority > message->priority) {
			message->next = mailbox->message_queue;
			mailbox->message_queue = message;
			
		} else {
			tmp = mailbox->message_queue;
			while (tmp) {
				if (tmp->next == NULL) {
					tmp->next = message;
					break;
				}
				if (tmp->next->priority > message->priority) {
					message->next = tmp->next;
					tmp->next = message->next;
					break;
				}
				tmp = tmp->next;
			}
		}
	} else {
		tmp = mailbox->message_queue;
		while (tmp) {
			if (tmp->next == NULL) {
				tmp->next = message;
				break;
			}
			tmp = tmp->next;
		}
		if (tmp) {
			tmp->next = message;
		} else {
			mailbox->message_queue = message;
		}
	}
		
	if (mailbox->thread_queue) {
		wakeup_thread(mailbox->thread_queue, WAIT_TYPE_MESSAGE, &mailbox->thread_queue);
	}

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_receive_message(syswrap_message_queue_t *message_queue, message_t **message, long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	
	if ((message_queue == NULL) || (message_queue->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;
	
	if (message == NULL)
		return SYSWRAP_ERR_PAR;

	message_queue_info_t *mailbox = (message_queue_info_t *)message_queue->sysinfo;
	
	if (mailbox->message_queue) {
		*message = mailbox->message_queue;
		mailbox->message_queue = mailbox->message_queue->next;
		return SYSWRAP_ERR_OK;
	}
	
	thread_info_t *thread_info = NULL;

	if ((thread_info = get_current_thread()) == NULL)
		return SYSWRAP_ERR_CTX;
	
	errcode = wait_thread(thread_info, WAIT_TYPE_MESSAGE, mailbox->thread_attribute, timeout, &mailbox->thread_queue);

	if (errcode == SYSWRAP_ERR_OK) {
		if (mailbox->message_queue) {
			*message = mailbox->message_queue;
			mailbox->message_queue = mailbox->message_queue->next;
		}
	}

	return errcode;
}

SYSWRAP_ERROR syswrap_is_remain_message(syswrap_message_queue_t *message_queue, int *exist)
{
	if ((message_queue == NULL) || (message_queue->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	message_queue_info_t *mailbox = (message_queue_info_t *)message_queue->sysinfo;
	
	if (mailbox->message_queue) {
		*exist = TRUE;
	} else {
		*exist = FALSE;
	}
	
	return SYSWRAP_ERR_OK;
}
