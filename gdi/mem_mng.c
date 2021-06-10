/******************************************************************************
 Copyright (C) 2011 Panasonic Corporation.

 Filename:
     mem_mng.c

 Description:
     Declaration of memory pool

 Authors:
     YO - Yoshinori OKAZAKI@AVC

 File History:
 Date        Sign    Description
 ----------  ----    -------------------------------------------------------
 2011/10/04   YO     新規作成(AVFW流用)
 ******************************************************************************/

// ----------------------------------------------------------------------
// インクルードファイル
// ----------------------------------------------------------------------
#include <kernel.h>

#include "mem_mng.h"

#ifdef WIN32_GUI_SIM
#include "kernel_id.h"
#include "win_itron.h"
#endif

// ----------------------------------------------------------------------
// 定数定義
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// 変数宣言
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------
// 関数定義
// ----------------------------------------------------------------------

/***********************************************************************
   API 関数
************************************************************************/
static int max_memory_syze = 0;

static BOOL get_memory_size(ID mplid, int *mem_size)
{
	T_RMPL rmpl;

	if (mem_size == NULL)
		return FALSE;
	
	if (ref_mpl(mplid, &rmpl) != E_OK) {
		return FALSE;
	}
	*mem_size = rmpl.fmplsz;

	return TRUE;
}

static int get_remain_mem_percent(ID mplid)
{
	int remain;

	if (0 == max_memory_syze) {
		return (get_memory_size(mplid, &max_memory_syze)) ? 100 : 0;
	}

	if (!get_memory_size(mplid, &remain)) {
		return 0;
	}

	//smDebugPrintf(1, "ID:[%d]  メモリ残量: %d%%(%d / %d)\n", mplid, (remain * 100 / max_memory_syze), remain, max_memory_syze);

	//残りメモリサイズを％で返す
	return remain * 100 / max_memory_syze;
}

void *gdi_alloc(int size)
{
	void *mem;

	if (tget_mpl(GFX_RESMPL_ID, size, &mem,  500) != E_OK) {
		return NULL;
	}
	return mem;
}

void gdi_free(void *ptr)
{
	rel_mpl(GFX_RESMPL_ID, ptr);
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

#if 0
// FONT_LIBMPL_ID
void *font_lib_alloc(long size)
{
  void *mem;

	if (tget_mpl(FONT_LIBMPL_ID, size, &mem,  500) != E_OK) {
    return NULL;
	}
	return mem;
}

void font_lib_free(void *ptr)
{
	rel_mpl(FONT_LIBMPL_ID, ptr);
}

void *font_lib_realloc(void *ptr, long new_size, long cur_size)
{
  void *p;

  if (ptr == NULL)
      return font_lib_alloc(new_size);

  if (cur_size < new_size)
  {
      p = font_lib_alloc(new_size);
      if (p == NULL)
      {
          font_lib_free(ptr);
          return NULL;
      }
      memcpy(p, ptr, new_size);
      font_lib_free(ptr);
  }
  else
  {
      p = ptr;
  }
  return p;
}
#endif

int gdi_remain_mem_percent()
{
	return get_remain_mem_percent(GFX_RESMPL_ID);
}

void *gdi_bmp_alloc(int size, int align)
{
	void *p = NULL;
	unsigned long temp = 0;

	size += align+4;
	if (tget_mpl(GUI_WORKMPL_ID, size, &p,  500) != E_OK) {
		return NULL;
	}
	temp = (unsigned long)p + 4;
	if (temp & (align-1)) {
		p = (void *)((temp & (0xFFFFFFFF-(align-1))) +align);
	} else {
		p = (void *)temp;
	}
	((unsigned long *)p)[-1] = temp - 4;

	return p;
}

void gdi_bmp_free(void *ptr)
{
	unsigned long temp = 0;
	
	if (ptr != NULL) {
		temp = ((unsigned long *)ptr)[-1];
	}
	rel_mpl(GUI_WORKMPL_ID, (void *)temp);
}

void *gdi_bmp_realloc(void* ptr, int new_size, int cur_size)
{
  void *p;

  if (ptr == NULL)
      return gdi_bmp_alloc(new_size, 128);
  
  if (cur_size < new_size) {
      if ((p = gdi_bmp_alloc(new_size, 128)) == NULL) {
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

int gdi_bmp_remain_mem_percent()
{
	return get_remain_mem_percent(GUI_WORKMPL_ID);
}


void *gui_alloc(int size, int align)
{
	void *p = NULL;
	unsigned long temp = 0;

	size += align+4;
	if (tget_mpl(GUI_WORKMPL_ID, size, &p,  500) != E_OK) {
		return NULL;
	}
	temp = (unsigned long)p + 4;
	if (temp & (align-1)) {
		p = (void *)((temp & (0xFFFFFFFF-(align-1))) +align);
	} else {
		p = (void *)temp;
	}
	((unsigned long *)p)[-1] = temp - 4;

	return p;
}

void gui_free(void *ptr)
{
	unsigned long temp = 0;
	
	if (ptr != NULL) {
		temp = ((unsigned long *)ptr)[-1];
	}
	rel_mpl(GUI_WORKMPL_ID, (void *)temp);
}

int gui_remain_mem_percent()
{
	return get_remain_mem_percent(GUI_WORKMPL_ID);
}

