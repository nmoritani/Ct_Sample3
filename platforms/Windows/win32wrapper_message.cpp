#include <stdio.h>
#include <stdlib.h>
#include "win32wrapper_common.h"

#ifdef SYSTEM_WINDOWS

#define NUM_OF_MESSAGEDATA	64

#define NUM_OF_MESSAGE	100

typedef struct _message {
	struct _message *next;
	int priority;
	void *dat;
	BOOL use;
	
} message_t;

typedef struct  {
	BOOL           		use;
	THREAD_ATTR			thread_attribute;
	thread_info_t		*thread_queue;
	
	int					message_count;
	message_t			*message_queue;
} mailbox_info_t;

/* global */
mailbox_info_t	mailbox_info_list[NUM_OF_MAILBOX] = {0};

message_t message_list[NUM_OF_MESSAGE] = {0};

SYSWRAP_ERROR syswrap_message_init()
{
	ZERO_CLEAR(mailbox_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_message_term()
{
	ZERO_CLEAR(mailbox_info_list);

	return SYSWRAP_ERR_OK;
}


SYSWRAP_ERROR syswrap_create_mailbox(syswrap_mailbox_t *mailbox, THREAD_ATTR thread_attribute)
{
	int i;
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;

	if (mailbox == NULL)
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(31);
	
	for (i = 0; i < NUM_OF_MAILBOX; i++) {
		if (mailbox_info_list[i].use)
			continue;

		mailbox_info_list[i].use = TRUE;
		mailbox_info_list[i].thread_attribute = thread_attribute;
		mailbox_info_list[i].thread_queue = NULL;
		mailbox_info_list[i].message_count = 0;
		
		mailbox->sysinfo = &mailbox_info_list[i];
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	unlock_common_mutex();
	
	return errcode;
}

SYSWRAP_ERROR syswrap_destroy_mailbox(syswrap_mailbox_t *mailbox)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;

	if ((mailbox == NULL) || (mailbox->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;
	
	lock_common_mutex(32);

	mailbox_info_t *mailbox_info = (mailbox_info_t *)mailbox->sysinfo;
	
	if (FALSE == mailbox_info->use) 
		errcode = SYSWRAP_ERR_PAR;
	
	ZERO_CLEAR(*mailbox_info);
	mailbox->sysinfo = NULL;

	unlock_common_mutex();
	
	return errcode;
}

SYSWRAP_ERROR syswrap_send_message(syswrap_mailbox_t *mailbox, void *dat, int priority)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	message_t *message = NULL;
	message_t *tmp = NULL;

	if ((mailbox == NULL) || (mailbox->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;

	lock_common_mutex(33);
	
	mailbox_info_t *mailbox_info = (mailbox_info_t *)mailbox->sysinfo;

	for (int i = 0; i < NUM_OF_MESSAGE; i++) {
		if (message_list[i].use == FALSE) {
			message = &message_list[i];
			break;
		}
	}
	if (message == NULL) {
		errcode = SYSWRAP_ERR_RESOVER;
		goto exit;
	}

	message->use = TRUE;
	message->dat = dat;
	message->priority = priority;
	message->next = NULL;
	
	if (mailbox_info->thread_attribute & THREAD_ATTR_PRI) {
		if (mailbox_info->message_queue) {
			mailbox_info->message_queue = message;
			
		} else if (mailbox_info->message_queue->priority > message->priority) {
			message->next = mailbox_info->message_queue;
			mailbox_info->message_queue = message;
			
		} else {
			tmp = mailbox_info->message_queue;
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
		tmp = mailbox_info->message_queue;
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
			mailbox_info->message_queue = message;
		}
	}
		
	if (mailbox_info->thread_queue) {
		wakeup_thread(mailbox_info->thread_queue, WAIT_TYPE_MESSAGE, &mailbox_info->thread_queue);
	}

  exit:
	unlock_common_mutex();
	return errcode;
}

int receive_err = 0;

SYSWRAP_ERROR syswrap_receive_message(syswrap_mailbox_t *mailbox, void **dat, long timeout)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	message_t * message = NULL;
	
	if ((mailbox == NULL) || (mailbox->sysinfo == NULL))
		return SYSWRAP_ERR_RESOVER;
	
	if (dat == NULL)
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(34);
	
	mailbox_info_t *mailbox_info = (mailbox_info_t *)mailbox->sysinfo;
	
	if (mailbox_info->message_queue) {
		message = mailbox_info->message_queue;
		mailbox_info->message_queue = mailbox_info->message_queue->next;

		*dat = message->dat;
		ZERO_CLEAR(*message);
		errcode = SYSWRAP_ERR_OK;
		goto exit;
	}
	
	thread_info_t *thread_info = NULL;

	if ((thread_info = get_current_thread_info()) == NULL)
		return SYSWRAP_ERR_CTX;
	
	errcode = wait_thread(thread_info, WAIT_TYPE_MESSAGE, mailbox_info->thread_attribute, timeout, &mailbox_info->thread_queue);

	if (errcode == SYSWRAP_ERR_OK) {
		if (mailbox_info->message_queue) {
			message = mailbox_info->message_queue;
			mailbox_info->message_queue = mailbox_info->message_queue->next;
			
			*dat = message->dat;
			ZERO_CLEAR(*message);
			errcode = SYSWRAP_ERR_OK;
			goto exit;
		}
	} else {
		receive_err++;
	}

  exit:
	unlock_common_mutex();
	return errcode;
}

int syswrap_get_remain_message(syswrap_mailbox_t *mailbox)
{
	if ((mailbox == NULL) || (mailbox->sysinfo == NULL))
		return -1;

	lock_common_mutex(35);
	mailbox_info_t *mailbox_info = (mailbox_info_t *)mailbox->sysinfo;
	
	if (mailbox_info->message_queue) {
		unlock_common_mutex();
		return 1;
	}
	
	unlock_common_mutex();
	return 0;
}
#endif
