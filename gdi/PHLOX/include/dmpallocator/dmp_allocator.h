/*------------------------------------------------------------------------------*/
/*	dmp_allocator.h																*/
/*																				*/
/*	Copyright (c) 2011, Digital Media Professionals Inc. All rights reserved.	*/
/*																				*/
/*------------------------------------------------------------------------------*/
#ifndef	DMP_ALLOCATOR_H
#define	DMP_ALLOCATOR_H

#include "dmpallocator/envdep.h"

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------*/
/*  For exporting                           */
/*------------------------------------------*/

#define EXPORT	extern
//.#define EXPORT

/*------------------------------------------*/
/*  For type definition                     */
/*------------------------------------------*/

typedef unsigned int			SIZE_T;

/*------------------------------------------*/
/*  Definitions                             */
/*------------------------------------------*/
#ifdef PANA_ORG_FUNC
EXPORT	void dmp_allocator_addr_size_set(uint32 pmem_addr , uint32 logical_addr , uint32 pmem_size);  /* should be called before using lib to set env. */
#endif /* PANA_ORG_FUNC */

EXPORT	void dmp_allocator_destroy(void); 
EXPORT	void dmp_allocator_mmap_init(void); /* should be called before using lib. */
EXPORT	void* dmp_allocator_malloc(SIZE_T size, const uint32 align); /* get physical address */
EXPORT	void dmp_allocator_free(void* addr); /* make physcial address free */
EXPORT	uint32 dmp_allocator_get_physical_base(void); /* get physical address base */
EXPORT	uint32 dmp_allocator_get_logical_base(void); /* get logical address base */
EXPORT	void* dmp_allocator_convert_into_logical(const void* const addr); /* get logical address */
EXPORT	void* dmp_allocator_convert_into_physical(const void* const addr); /* get logical address */
EXPORT	uint32 dmp_allocator_get_size(void); /* get maximum size */
EXPORT  unsigned int dmp_allocator_is_valid_address(const void* const addr); /* determine parameter logical address is vaild on this allocator  */
EXPORT	int dmp_allocator_malloc_array(int type, SIZE_T size, const uint32 align, void* addr[], const uint32 arraysize); /* special multiple allocator */
EXPORT	void dmp_allocator_free_array(const void* const addr[], const uint32 arraysize); /* special multiple allocator */

int dmp_allocator_read_logical_memory(void* vram_addr, void* dst_addr, SIZE_T size);
int dmp_allocator_write_logical_memory(void* vram_addr, void* src_addr, SIZE_T size);
int dmp_allocator_read_physical_memory(uint32 vram_addr, void* dst_addr, SIZE_T size);
int dmp_allocator_write_physical_memory(uint32 vram_addr, void* dst_addr, SIZE_T size);

#ifdef __cplusplus
}
#endif


#endif	/* DMP_ALLOCATOR_H */
