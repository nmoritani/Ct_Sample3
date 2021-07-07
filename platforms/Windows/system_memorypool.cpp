#include "system_common.h"
#include <stdlib.h>

typedef struct {
	BOOL 			use;
	THREAD_ATTR		thread_attribute;
	thread_info_t	*thread_queue;

	void			*top;
	unsigned int	size;
	unsigned int	alignment;
} mempool_info_t;

mempool_info_t		info_list[NUM_OF_MEMORYPOOL];

SYSWRAP_ERROR syswrap_memorypool_initial()
{
	ZERO_CLEAR(info_list);

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
	*dst = malloc(size);
	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_free_memory(syswrap_memorypool_t *mempool, void* dst)
{
	free(dst);
	return SYSWRAP_ERR_OK;
}


