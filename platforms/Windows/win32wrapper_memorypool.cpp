#include <windows.h>
#include <windowsX.h>
#include <stdio.h>

#include "win_itron.h"
#include "win32wrapper_common.h"
#include <stdlib.h>

#ifdef SYSTEM_WINDOWS

typedef struct {
	BOOL 			use;

	void			*top;
	unsigned int	size;
	unsigned int	alignment;
} mempool_info_t;

mempool_info_t	mempool_info_list[NUM_OF_MEMORYPOOL] = {0};

typedef struct {
	int size;
	BOOL used;
} memlink_t;

static void *get_block(int size, unsigned char *buf, int max_size)
{
	memlink_t	*mem = NULL;
	int	i, req_size, remain;

	req_size = size + sizeof(memlink_t);

	for (i = 0; i < max_size;) {
		mem = (memlink_t *)(&buf[i]);
		
		if (mem->used == FALSE) {
			if (mem->size >= req_size) {
				remain = mem->size - req_size;
				mem->size = req_size;
				mem->used = TRUE;

				if (remain > sizeof(memlink_t)) {
					mem = (memlink_t *)(&buf[i + req_size]);
					mem->size = remain;
					mem->used = FALSE;
					
				} else {
					mem->size += remain;
				}
				return &buf[i + sizeof(memlink_t)];
			}
		}
		i += mem->size;
	}
	
	return NULL;
}

static BOOL	release_block(void* adr, unsigned char *buf, int max_size)
{
	memlink_t	*mem, *prev, *next;
	int	i, j, pos;
	
	pos = ((int)adr - (int)buf) - (int)sizeof(memlink_t);

	if ((pos < 0) || (pos >= (max_size - (int)sizeof(memlink_t)))) {
		return FALSE;
	}
	
	prev = NULL;
	for (i = 0; i < max_size && i <= pos;) {

		mem = (memlink_t *)(&buf[i]);
		if (mem->size == 0)
			break;

		if (i == pos) {
			if (mem->used == FALSE)
				break;

			mem->used = FALSE;
			j = i + mem->size;
			if (j < (max_size - (int)sizeof(memlink_t))) {
				next = (memlink_t *)(&buf[j]);
				if (next->used == FALSE) {
					mem->size += next->size;
				}
			}
			if ((prev != NULL) && (prev->used == FALSE)) {
				prev->size += mem->size;
			}
			return TRUE;
		}
		i += mem->size;
		prev = mem;
	}
	
	return FALSE;
}

static int get_maxsize(int *max_free, unsigned char *buf, int max_size)
{
	memlink_t *mem = NULL;
	int	i, total_free;

	*max_free  = 0;
	total_free = 0;

	for (i = 0; i < max_size; ) {
		mem = (memlink_t *)(&buf[i]);
		if (mem->used == FALSE) {
			if (*max_free < mem->size) {
				*max_free = mem->size;
			}
			total_free += (mem->size - sizeof(memlink_t));
		}
		i += mem->size;
	}
	
	if (*max_free != 0) {
		*max_free -= sizeof(memlink_t);
	}
	return total_free;
}

SYSWRAP_ERROR syswrap_memorypool_init()
{
	ZERO_CLEAR(mempool_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_memorypool_term()
{
	ZERO_CLEAR(mempool_info_list);

	return SYSWRAP_ERR_OK;
}

SYSWRAP_ERROR syswrap_create_memorypool(syswrap_memorypool_t *mempool, int size, int align_size, void *addr)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_NOEXS;
	mempool_info_t * mempool_info = NULL;
	memlink_t	*link;

	if (mempool == NULL)
		return SYSWRAP_ERR_PAR;
	
	lock_common_mutex(61);
	
	for (int i = 0; i < NUM_OF_MEMORYPOOL; i++) {
		if (mempool_info_list[i].use == TRUE)
			continue;

		mempool_info = &mempool_info_list[i];
		
		mempool_info->use = TRUE;
		mempool_info->size = size;
		mempool_info->alignment = align_size;

		if (addr == NULL) {
			if ((mempool_info->top = malloc(size)) == NULL) {
				return SYSWRAP_ERR_NOMEM;
			}
		} else {
			mempool_info->top = addr;
		}
		memset(mempool_info->top, 0, mempool_info->size);


		link = (memlink_t *)mempool_info->top;
		link->size = mempool_info->size;
		link->used = FALSE;
		
		mempool->sysinfo = mempool_info;
		errcode = SYSWRAP_ERR_OK;
		break;
	}

	unlock_common_mutex();
	
	return errcode;
}

SYSWRAP_ERROR syswrap_destroy_memorypool(syswrap_memorypool_t *mempool)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	mempool_info_t *mempool_info = NULL;

	if ((mempool == NULL) || (mempool->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	lock_common_mutex(62);
	
	mempool_info = (mempool_info_t *)mempool->sysinfo;

	if (mempool_info->top) 
		free(mempool_info->top);

	ZERO_CLEAR(*mempool_info);
	mempool->sysinfo = NULL;

	unlock_common_mutex();

	return errcode;
}

SYSWRAP_ERROR syswrap_alloc_memory(syswrap_memorypool_t *mempool, void **dst, int size)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	mempool_info_t *mempool_info = NULL;
	void *blk;
	
	if ((mempool == NULL) || (mempool->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	if ((dst == NULL) || (size < 0))
		return SYSWRAP_ERR_PAR;
	
	lock_common_mutex(63);
	
	mempool_info = (mempool_info_t *)mempool->sysinfo;

	if ((blk = get_block(size, (unsigned char *)mempool_info->top, mempool_info->size)) == NULL) {
		errcode = SYSWRAP_ERR_NOMEM;
	}
	*dst = blk;

	unlock_common_mutex();

	return errcode;
}

SYSWRAP_ERROR syswrap_free_memory(syswrap_memorypool_t *mempool, void* dst)
{
	SYSWRAP_ERROR errcode = SYSWRAP_ERR_OK;
	mempool_info_t *mempool_info = NULL;

	if ((mempool == NULL) || (mempool->sysinfo == NULL))
		return SYSWRAP_ERR_PAR;

	if (dst == NULL)
		return SYSWRAP_ERR_PAR;
	
	lock_common_mutex(64);
	
	mempool_info = (mempool_info_t *)mempool->sysinfo;

	if (release_block(dst, (unsigned char *)mempool_info->top, mempool_info->size) != TRUE)
		errcode = SYSWRAP_ERR_SYS;
		
	unlock_common_mutex();

	return errcode;
}

#endif

