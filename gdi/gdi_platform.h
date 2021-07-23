/*************************************************************************/
/**
 * @file      gdi_platform.h
 * @copyright Persol AVC Technorogy
 * @author    
 *************************************************************************/
#ifndef __GDI_PLATFORM_H__
#define __GDI_PLATFORM_H__

#include <CtPlatforms.h>

#define GDI_HOSTMEM_SIZE	(500*1024)
#define GDI_HOSTMEM_ADDR	(0)

#define GDI_DEVICEMEM_SIZE	(30*1024*1024)
#define GDI_DEVICEMEM_ADDR	(0)

#define GDI_FONTMEM_SIZE	(4*1024*1024)
#define GDI_FONTMEM_ADDR	(0)

extern syswrap_memorypool_t gdi_host_memory;
extern syswrap_memorypool_t gdi_device_memory;
extern syswrap_memorypool_t gdi_font_memory;
extern syswrap_semaphore_t gdi_semaphore_draw;
extern syswrap_semaphore_t gdi_semaphore_font;

extern void gdi_platform_init();
extern void gdi_platform_term();

extern void *gdi_alloc(int size);
extern void gdi_free(void *ptr);
extern void *gdi_realloc(void*ptr, int new_size, int cur_size);

extern void *gdi_bmp_alloc(int size);
extern void gdi_bmp_free(void *ptr);
extern void *gdi_bmp_realloc(void* ptr, int new_size, int cur_size);

#endif /* __GDI_PLATFORM_H__ */
