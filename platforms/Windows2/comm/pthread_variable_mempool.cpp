#include "pthread_variable_mempool.h"
#include "pthread_common.h"

int get_variable_mempool(unsigned int id, unsigned int size, void** dst)
{
	*dst = malloc(size);
	return ERR_OK;
}

int free_variable_mempool(unsigned int id, void* dst)
{
	free(dst);
	return ERR_OK;
}
