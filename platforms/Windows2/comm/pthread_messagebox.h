#ifndef _MBOX_H_
#define _MBOX_H_

#define _GNU_SOURCE

#include "pthread.h"

//MBOXÇÃÉTÉCÉY
#define NUM_OF_MBOX 10
#define NUM_OF_MSG  4096

typedef struct Msg {
	void  *data;
	unsigned int len;
} Msg;

/* ring buffer to store msg. this buffer wastes extra 1 msg */
typedef struct MsgRingBuf {
	int read_pos;
	int write_pos;
	Msg msg[NUM_OF_MSG + 1];
} MsgRingBuf;

typedef struct Mbox {
	int             use;
	int             id;
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
	MsgRingBuf      rbuf;
} Mbox;

int init_mbox_table();
int create_mbox(unsigned int mbox_id);
int delete_mbox(unsigned int mbox_id);
int send_message(unsigned int mbox_id, void const *msg);
int p_receive_message(unsigned int mbox_id, void **msg);
int receive_message(unsigned int mbox_id, void **msg);
int t_receive_message(unsigned int mbox_id, void **msg, int timeout);

#endif /* _MBOX_H_ */

