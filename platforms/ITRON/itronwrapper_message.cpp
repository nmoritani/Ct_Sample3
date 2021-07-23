#include <stdio.h>
#include <stdlib.h>
#include "itronwrapper_common.h"

#ifdef SYSTEM_ITRON

typedef struct {
	T_MSG	header;
	BOOL	use;
	void	*message;
} message_t;

#define NUM_OF_MESSAGE 1000
message_t msg_dat[NUM_OF_MESSAGE] = {0};

SYSWRAP_ERROR syswrap_create_mailbox(syswrap_mailbox_t *mailbox, THREAD_ATTR thread_attribute)
{
	T_CMBX cmbx = {0};

	if (mailbox == NULL)
		return SYSWRAP_ERR_PAR;
	
	cmbx.mbxatr = TA_TFIFO|TA_MFIFO;
	cmbx.maxmpri = 0;
	cmbx.mprihd = 0;

	if (mailbox->id == 0) {
		if ((mailbox->id = acre_mbx(&cmbx)) <= 0)
			return SYSWRAP_ERR_SYS;

	} else {
		if (cre_mbx(mailbox->id, &cmbx) != E_OK)
			return SYSWRAP_ERR_SYS;
	}

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_destroy_mailbox(syswrap_mailbox_t *mailbox)
{
	if (mailbox == NULL)
		return SYSWRAP_ERR_PAR;

	if (mailbox->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (del_mbx(mailbox->id) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_send_message(syswrap_mailbox_t *mailbox, void *message, int priority)
{
	int i;
	message_t *msg = NULL;
	
	if (mailbox == NULL)
		return SYSWRAP_ERR_PAR;

	if (mailbox->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	for (i= 0; i < NUM_OF_MESSAGE; i++) {
		if (msg_dat[i].use != TRUE) {
			msg = &msg_dat[i];
			msg->use = TRUE;
			break;
		}
	}

	if (msg == NULL)
		return SYSWRAP_ERR_PAR;

	msg->header = {0};
	msg->message = message;
	
	if (snd_msg(mailbox->id, (T_MSG*)msg) != E_OK)
		return SYSWRAP_ERR_SYS;

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_receive_message(syswrap_mailbox_t *mailbox, void **message, long timeout)
{
	int i;
	message_t *msg = NULL;
	
	if (mailbox == NULL)
		return SYSWRAP_ERR_PAR;

	if (mailbox->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (trcv_msg(mailbox->id, (T_MSG**)&msg, timeout) != E_OK)
		return SYSWRAP_ERR_SYS;

	*message = msg->message;

	msg->header = {0};
	msg->use = FALSE;
	msg->message = NULL;
	
	return SYSWRAP_ERR_OK;
}

int syswrap_get_remain_message(syswrap_mailbox_t *mailbox)
{
	T_RMBX rmbx;
	
	if (mailbox == NULL)
		return -1;

	if (mailbox->id <= 0)
		return SYSWRAP_ERR_SYS;
	
	if (ref_mbx(mailbox->id, &rmbx) != E_OK)
		return SYSWRAP_ERR_SYS;

	if (rmbx.pk_msg != NULL)
		return 1;
	
	return 0;
}

#endif
