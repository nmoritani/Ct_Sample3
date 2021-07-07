#include "system_common.h"
#include <stdlib.h>

typedef struct {
	int 			use;
	pthread_mutex_t	wait_mutex;
	pthread_cond_t	wait_cond;
} mempool_info_t;

pthread_mutex_t 	mutex;
mempool_info_t		info_list[NUM_OF_MEMORYPOOL];

SYSWRAP_ERROR syswrap_memorypool_initial()
{
	mutex_init(&mutex);
	
	ZERO_CLEAR(info_list);

	for (int i = 0; i < NUM_OF_MEMORYPOOL; i++) {
		info_list[i].use = false;
	}

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_create_memorypool(syswrap_memorypool_t *mempool, size_t size, size_t align_size)
{
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_delete_memorypool(syswrap_memorypool_t *mempool)
{
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_alloc_memory(syswrap_memorypool_t *mempool, size_t size, void** dst)
{
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_free_memory(syswrap_memorypool_t *mempool, void* dst)
{
	return SYSWRAP_ERR_OK;
}


