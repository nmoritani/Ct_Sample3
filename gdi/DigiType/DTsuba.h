#ifndef MBA_SUBA_H
#define MBA_SUBA_H

/* suba - sub-allocate memory from larger chunk of memory
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "DTallocator.h"

extern DT_void *DT_memory_addr(const struct allocator *suba, const ref_t ref);
extern ref_t DT_memory_ref(const struct allocator *suba, const DT_void *ptr);

#ifdef __cplusplus
}
#endif

#endif /* MBA_SUBA_H */

