#include "pthread_semaphore.h"
#include "pthread_common.h"

pthread_mutex_t g_semaphore_mutex;	//mutexリストの生成・破棄用
pthread_mtx		g_thread_mutexList[NUM_OF_SEMAPHORE];

static int get_mutex_index(unsigned int id)
{
	int i;
	for (i = 0; i < ARRAY_NUM(g_thread_mutexList); i++) {
		if (!g_thread_mutexList[i].use) {
			continue;
		}

		if (g_thread_mutexList[i].id == id) {
			return i;
		}
	}
	return -1;
}

static pthread_mtx * find_object(int id)
{
	int index = get_mutex_index(id);
	if ((index < 0) || (NUM_OF_SEMAPHORE <= index)) {
		return NULL;
	}
	return &g_thread_mutexList[index];
}

static void create_object(int index, int id)
{
	g_thread_mutexList[index].use = true;
	g_thread_mutexList[index].id = id;

	init_mutex(&(g_thread_mutexList[index].mutex));
	pthread_cond_init(&(g_thread_mutexList[index].cond), NULL);
}

int init_mutex_table()
{
	unsigned int i;

	init_mutex(&g_semaphore_mutex);
	for (i = 0; i < ARRAY_NUM(g_thread_mutexList); i++) {
		g_thread_mutexList[i].use = false;
		g_thread_mutexList[i].id = 0;
	}

	return ERR_OK;
}

void init_mutex(pthread_mutex_t *mutex)
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(mutex, &attr);
}

// idをg_thread_mutexListに登録し、mutexを初期化
int create_semaphore(int id)
{
	unsigned int i;
	int   errcode = ERR_PAR;

	pthread_mtx *obj = find_object(id);
	if (NULL != obj) {
		//既に作成されている場合
		return ERR_OBJ;
	}

	pthread_mutex_lock(&g_semaphore_mutex);

	for (i = 0; i < ARRAY_NUM(g_thread_mutexList); i++) {
		if (g_thread_mutexList[i].use) {
			/*使用済みのIDは飛ばす*/
			continue;
		}

		/*新規ミューテックス作成*/
		create_object(i, id);

		errcode = ERR_OK;
		break;
	}

	pthread_mutex_unlock(&g_semaphore_mutex);
	return errcode;
}

int delete_semaphore(int id)
{
	int ercd;

	pthread_mtx *obj = find_object(id);
	if (NULL == obj) {
		return ERR_OBJ;
	}

	pthread_mutex_lock(&g_semaphore_mutex);

	if (false == obj->use) {
		ercd = ERR_PAR;
	} else if (pthread_mutex_destroy(&(obj->mutex)) != 0) {
		ercd = ERR_SYS;
	} else if (pthread_cond_destroy(&(obj->cond)) != 0) {
		ercd = ERR_SYS;
	} else {
		ZERO_CLEAR(*obj);
		ercd = ERR_OK;
	}

	pthread_mutex_unlock(&g_semaphore_mutex);
	return ercd;
}

int wait_semaphore(int id)
{
	pthread_mtx *obj = find_object(id);
	if (NULL == obj) {
		return ERR_OBJ;
	}
	int result = pthread_mutex_lock(&(obj->mutex));
	return	(0 == result) ? ERR_OK : ERR_PAR;
}

int signal_semaphore(int id)
{
	pthread_mtx *obj = find_object(id);
	if (NULL == obj) {
		return ERR_OBJ;
	}
	int result = pthread_mutex_unlock(&(obj->mutex));
	return	(0 == result) ? ERR_OK : ERR_PAR;
}
