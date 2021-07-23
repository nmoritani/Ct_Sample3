#include <string.h>
#include "gdi_platform.h"

#define PANA_ORG_FUNC
#define _DMPNATIVE_

/***************************************************************
				マクロ定義
***************************************************************/

/***************************************************************
				ｅｎｕｍ
***************************************************************/

/***************************************************************
				構造体
***************************************************************/

/***************************************************************
				プロトタイプ
***************************************************************/
	
/***************************************************************
				変数宣言
***************************************************************/

//------------------------------------------------------------
//! Graphic Manager Task
/*!
 * \param[] 
 * \param[] 
 * \return  
 * \note    
 * @date       12.02.09 API層の処理をタスクに移植
 */

// セミホスティング対応
int $Sub$$_sys_open(const char *name, int openmode)
{
	/* Dummy */
	return (0);
}

void $Sub$$_sys_exit(int retcode)
{
	/* Dummy */
}

void $Sub$$_ttywrch(int ch)
{
	/* Dummy */
}

void __assert_fail(void)
{
	/* Dummy */
}


// 物理アドレスを論理アドレスに変換
void *GE_CnvLogicAddr(unsigned int addr)
{
	return (void *)addr;
}

// 論理アドレスを物理アドレスに変換
void *GE_CnvPhysicalAddr(unsigned int addr)
{
	return (void *)addr;
}

void GE_suspend(void)
{
	/* Dummy */
}

void GE_resume(void)
{
	/* Dummy */
}

void GE_Irq_gp_signal()
{
	/* Dummy */
}

void GE_Irq_psc_signal()
{
	/* Dummy */
}

void GE_Irq_ppf_signal()
{
	/* Dummy */
}



// DMP内部から参照されてるため消すとコンパイルエラーになる
////////////////////////////
void utl_armcom_cachePurgeALL(void){}
void snprintf(){}
////////////////////////////

#include <CtPlatforms.h>

syswrap_memorypool_t gdi_host_memory = {0};
syswrap_memorypool_t gdi_device_memory = {0};
syswrap_memorypool_t gdi_font_memory = {0};
syswrap_semaphore_t gdi_semaphore_draw = {0};
syswrap_semaphore_t gdi_semaphore_font = {0};


void gdi_platform_init()
{
	syswrap_create_memorypool(&gdi_host_memory, GDI_HOSTMEM_SIZE, 0, GDI_HOSTMEM_ADDR);
	syswrap_create_memorypool(&gdi_device_memory, GDI_DEVICEMEM_SIZE, 64, GDI_DEVICEMEM_ADDR);
	syswrap_create_memorypool(&gdi_font_memory, GDI_FONTMEM_SIZE, 64, GDI_FONTMEM_ADDR);

	syswrap_create_semaphore(&gdi_semaphore_font, 1, THREAD_ATTR_FIFO);
	syswrap_create_semaphore(&gdi_semaphore_draw, 1, THREAD_ATTR_FIFO);
}

void gdi_platform_term()
{
	syswrap_destroy_memorypool(&gdi_host_memory);
	syswrap_destroy_memorypool(&gdi_device_memory);
	
	syswrap_destroy_semaphore(&gdi_semaphore_font);
	syswrap_destroy_semaphore(&gdi_semaphore_draw);
}

void *gdi_alloc(int size)
{
	void *mem;

	if (syswrap_alloc_memory(&gdi_host_memory, &mem, size) != SYSWRAP_ERR_OK) {
		return NULL;
	}
	return mem;
}

void gdi_free(void *ptr)
{
	syswrap_free_memory(&gdi_host_memory, ptr);
}

void *gdi_realloc(void* ptr, int new_size, int cur_size)
{
  void *p;

  if (ptr == NULL)
      return gdi_alloc(new_size);
  
  if (cur_size < new_size) {
      if ((p = gdi_alloc(new_size)) == NULL) {
          gdi_free(ptr);
          return NULL;
      }
      memcpy(p, ptr, new_size);
      gdi_free(ptr);
  } else {
      p = ptr;
  }
  
  return p;
}

void *gdi_bmp_alloc(int size)
{
	void *mem;

	if (syswrap_alloc_memory(&gdi_device_memory, &mem, size) != SYSWRAP_ERR_OK) {
		return NULL;
	}
	return mem;
}

void gdi_bmp_free(void *ptr)
{
	syswrap_free_memory(&gdi_device_memory, ptr);
}

void *gdi_bmp_realloc(void* ptr, int new_size, int cur_size)
{
  void *p;

  if (ptr == NULL)
      return gdi_bmp_alloc(new_size);
  
  if (cur_size < new_size) {
      if ((p = gdi_bmp_alloc(new_size)) == NULL) {
          gdi_bmp_free(ptr);
          return NULL;
      }
      memcpy(p, ptr, new_size);
      gdi_bmp_free(ptr);
  } else {
      p = ptr;
  }
  
  return p;
}
