#include "pthread_common.h"
#include "pthread_messagebox.h"
#include "pthread_semaphore.h"

/* global */
pthread_mutex_t g_mbox_mutex;	//メールボックスの生成・破棄用
Mbox			g_mbox[NUM_OF_MBOX];

static int get_mbox_index(unsigned int id)
{
	int i;
	for (i = 0; i < ARRAY_NUM(g_mbox); i++) {
		if (!g_mbox[i].use) {
			continue;
		}

		if (g_mbox[i].id == id) {
			return i;
		}
	}
	return -1;
}

static Mbox * find_object(int id)
{
	int index = get_mbox_index(id);
	if ((index < 0) || (NUM_OF_MBOX <= index)) {
		return NULL;
	}
	return &g_mbox[index];
}

static void create_object(int index, int id)
{
	unsigned int j;
	g_mbox[index].use = true;
	g_mbox[index].id = id;

	init_mutex(&(g_mbox[index].mutex));
	pthread_cond_init(&(g_mbox[index].cond), NULL);

	g_mbox[index].rbuf.read_pos = 0;
	g_mbox[index].rbuf.write_pos = 0;
	for (j = 0; j < ARRAY_NUM(g_mbox[0].rbuf.msg); j++) {
		g_mbox[index].rbuf.msg[j].data = NULL;
		g_mbox[index].rbuf.msg[j].len = 0;
	}
}

/* write data to ring buffer */
static int write_rbuf(MsgRingBuf *rbuf, void const *data, unsigned int len)
{
	int next;

	next = (rbuf->write_pos + 1) % (NUM_OF_MSG + 1);
	if (next == rbuf->read_pos) {
		return ERR_QOVR;
	}

#if 0
	//データをコピーするならこっち
	rbuf->msg[rbuf->write_pos].data = malloc(len);
	if (NULL == rbuf->msg[rbuf->write_pos].data) {
		return ERR_SYS;
	}
	memcpy(rbuf->msg[rbuf->write_pos].data, data, len);
#else
	//メッセージ送信元でdataをmallocしているので、ポインタのアドレスだけ渡す
	unsigned int dataAdr = (unsigned int)data;
	unsigned int length = sizeof(dataAdr);
	rbuf->msg[rbuf->write_pos].data = malloc(length);
	if (NULL == rbuf->msg[rbuf->write_pos].data) {
		return ERR_SYS;
	}
	memcpy(rbuf->msg[rbuf->write_pos].data, &dataAdr, length);
#endif
	rbuf->msg[rbuf->write_pos].len = length;

	rbuf->write_pos = next;

	return ERR_OK;
}

/* read data from ring buffer */
static int read_rbuf(MsgRingBuf *rbuf, void **data, unsigned int *len)
{
	if (rbuf->write_pos == rbuf->read_pos) {
		return ERR_NOEXS;
	}

	int* adr = (int*)rbuf->msg[rbuf->read_pos].data;

	*len = rbuf->msg[rbuf->read_pos].len;
	*data = (void*)*adr;
	free(rbuf->msg[rbuf->read_pos].data);

	rbuf->msg[rbuf->read_pos].data = NULL;
	rbuf->msg[rbuf->read_pos].len = 0;

	rbuf->read_pos = (rbuf->read_pos + 1) % (NUM_OF_MSG + 1);

	return ERR_OK;
}

int init_mbox_table()
{
	unsigned int i;

	init_mutex(&g_mbox_mutex);
	for (i = 0; i < ARRAY_NUM(g_mbox); i++) {
		g_mbox[i].use = false;
		g_mbox[i].id = 0;
	}

	return ERR_OK;
}


int create_mbox(unsigned int id)
{
	unsigned int i;
	int   errcode = ERR_NOEXS;

	pthread_mutex_lock(&g_mbox_mutex);

	Mbox *obj = find_object(id);
	if (NULL != obj) {
		//既に作成されている場合
		return ERR_OBJ;
	}

	for (i = 0; i < ARRAY_NUM(g_mbox); i++) {
		if (g_mbox[i].use) {
			/*使用済みのIDは飛ばす*/
			continue;
		}

		/*新規メッセージボックス作成*/
		create_object(i, id);
		errcode = ERR_OK;
		break;
	}

	pthread_mutex_unlock(&g_mbox_mutex);
	return errcode;
}

int delete_mbox(unsigned int id)
{
	unsigned int i;
	int ercd;

	Mbox *obj = find_object(id);
	if (NULL == obj) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&g_mbox_mutex);

	if (false == obj->use) {
		ercd = ERR_PAR;
	} else if (pthread_mutex_destroy(&(obj->mutex)) != 0) {
		ercd = ERR_SYS;
	} else if (pthread_cond_destroy(&(obj->cond)) != 0) {
		ercd = ERR_SYS;
	} else {
		for (i = 0; i < ARRAY_NUM(g_mbox[0].rbuf.msg); i++) {
			if (obj->rbuf.msg[i].data != NULL) {
				free(obj->rbuf.msg[i].data);
			}
			obj->rbuf.msg[i].len = 0;
		}
		ZERO_CLEAR(*obj);
		ercd = ERR_OK;
	}

	pthread_mutex_unlock(&g_mbox_mutex);
	return ercd;
}

int send_message(unsigned int id, void const *msg)
{
	int ercd;
	unsigned int len = sizeof(msg);

	Mbox *mbox = find_object(id);
	if (NULL == mbox) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&(mbox->mutex));
	ercd = write_rbuf(&(mbox->rbuf), msg, len);
	pthread_cond_signal(&(mbox->cond));
	pthread_mutex_unlock(&(mbox->mutex));

	return ercd;
}

int p_receive_message(unsigned int id, void **msg)
{
	int ercd;
	unsigned int len = 0;

	Mbox *mbox = find_object(id);
	if (NULL == mbox) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&(mbox->mutex));
	ercd = read_rbuf(&(mbox->rbuf), msg, &len);
	pthread_mutex_unlock(&(mbox->mutex));

	return ercd;
}

int receive_message(unsigned int id, void **msg)
{
	int ercd;
	unsigned int len = 0;

	Mbox *mbox = find_object(id);
	if (NULL == mbox) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&(mbox->mutex));
	while (ERR_NOEXS == (ercd = read_rbuf(&(mbox->rbuf), msg, &len))) {
		pthread_cond_wait(&(mbox->cond), &(mbox->mutex));
	}
	pthread_mutex_unlock(&(mbox->mutex));

	return ercd;
}

/* milli second timeout */
int t_receive_message(unsigned int id, void **msg, int timeout)
{
	int			 ercd;
	int			 ret;
	unsigned int len = 0;

	struct timespec ts;

	Mbox *mbox = find_object(id);
	if (NULL == mbox) {
		return ERR_PAR;
	}

	pthread_mutex_lock(&(mbox->mutex));

	get_passage_time(&ts, timeout);
	while (ERR_NOEXS == (ercd = read_rbuf(&(mbox->rbuf), msg, &len))) {
		ret = pthread_cond_timedwait(&(mbox->cond), &(mbox->mutex), &ts);
		if (ETIMEDOUT == ret) {
			ercd = ERR_TMOUT;
			break;
		} else if (EINTR == ret) {
			/* continue (check ring buffer) */
		} else if (0 != ret) {
			ercd = ERR_SYS;
			break;
		} else {
			/* continue (check ring buffer) */
		}
	}

	pthread_mutex_unlock(&(mbox->mutex));
	return ercd;
}
