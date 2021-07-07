#include "pthread.h"
#include "pthread_common.h"

typedef struct _pthread_mutex {
	int             use;
	int             id;
	pthread_mutex_t mutex;
	pthread_cond_t  cond;
} pthread_mtx;


/* macro */
#define ARRAY_NUM(array) (sizeof(array) / sizeof(array[0]))

#define NUM_OF_SEMAPHORE	10

extern int init_mutex_table();
extern void init_mutex(pthread_mutex_t *mutex);
extern int create_semaphore(int id);
extern int delete_semaphore(int id);
extern int wait_semaphore(int id);
extern int signal_semaphore(int id);



