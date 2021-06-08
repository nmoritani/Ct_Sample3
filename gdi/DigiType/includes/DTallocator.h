#ifndef MBA_ALLOCATOR_H
#define MBA_ALLOCATOR_H

/* allocator - allocate and free memory
 */

#include "DTplatform.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
#include <stddef.h>
*/
#ifndef EINVAL
#define EPERM           1
#define ENOENT          2
#define ESRCH           3
#define EDT32_intR           4
#define EIO             5
#define ENXIO           6
#define E2BIG           7
#define ENOEXEC         8
#define EBADF           9
#define ECHILD          10
#define EAGAIN          11
#define ENOMEM          12
#define EACCES          13
#define EFAULT          14
#define EBUSY           16
#define EEXIST          17
#define EXDEV           18
#define ENODEV          19
#define ENOTDIR         20
#define EISDIR          21
#define EINVAL          22
#define ENFILE          23
#define EMFILE          24
#define ENOTTY          25
#define EFBIG           27
#define ENOSPC          28
#define ESPIPE          29
#define EROFS           30
#define EMLINK          31
#define EPIPE           32
#define EDOM            33
#define ERANGE          34
#define EDEADLK         36
#endif

#define ALAL(a) ((a) && (a) != stdlib_allocator ? (a) : (global_allocator ? global_allocator : 0))
#define ALREF(a,p) ((ref_t)((p) ? (DT8_char *)(p) - (DT8_char *)ALAL(a) : 0))
#define ALADR(a,r) ((DT_void *)((r) ? (DT8_char *)ALAL(a) + (r) : NULL))

#define SUBA_PTR_SIZE(ptr) ((ptr) ? (*((DT32_uint *)(ptr) - 1)) : 0)

typedef DT32_uint ref_t;  /* suba offset from start of memory to object */

struct allocator;

typedef DT_void *(*alloc_fn)(struct allocator *al, DT32_uint size, DT32_int flags);
typedef DT_void *(*realloc_fn)(struct allocator *al, DT_void *obj, DT32_uint size);
typedef DT32_int (*free_fn)(DT_void *al, DT_void *obj);
typedef DT32_int (*reclaim_fn)(struct allocator *al, DT_void *arg, DT32_int attempt);
typedef DT_void *(*new_fn)(DT_void *context, DT32_uint size, DT32_int flags);
typedef DT32_int (*del_fn)(DT_void *context, DT_void *object);

struct allocator {
	DT8_uchar magic[8];                /* suba header identifier */
	ref_t tail;                 /* offset to first cell in free list */
	DT32_uint mincell;    /* min cell size must be at least sizeof cell */
	DT32_uint size;                        /* total size of memory area */
	DT32_uint alloc_total;  /* total bytes utilized from this allocator */
	DT32_uint free_total;   /* total bytes released from this allocator */
	DT32_uint DT32_uintotal;  /* total bytes requested from this allocator */
					/* utilization = DT32_uintotal / alloc_total * 100
					 * e.g. 50000.0 / 50911.0 * 100.0 = 98.2%
					 */
	DT32_uint max_free;   /* for debugging - any cell larger throws err */
/*	alloc_fn alloc;
	realloc_fn realloc;
	free_fn free;*/
						/* for reaping memory from pool, varray, etc */
	reclaim_fn reclaim;
	DT_void *reclaim_arg;
	DT32_int reclaim_depth;
	ref_t userref;
};

struct allocator *DT_memory_init(DT_void *mem, DT32_uint size, DT32_int rst, DT32_uint mincell);
DT_void *DT_memory_alloc(struct allocator *suba, DT32_uint size, DT32_int zero);
DT_void *DT_memory_realloc(struct allocator *suba, DT_void *ptr, DT32_uint size);
DT32_int DT_memory_free(DT_void *suba, DT_void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* MBA_ALLOCATOR_H */

