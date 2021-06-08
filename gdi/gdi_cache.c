/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#include <string.h>

#ifdef WIN32_GUI_SIM
#include <windows.h>
#include "win_itron.h"
#include "wi_resource.h"
#include "egl.h"
#include "openvg.h"
#else
#define PANA_ORG_FUNC
#define _DMPNATIVE_
#include "EGL/egl.h"

#include "DMP/eglNative.h"
#include "DMP/eglNativePhlox.h"
#include "DMP/eglDMP.h"
#include "DMP/vgDMPX.h"
#endif

#include "gdi.h"
#include "gdi_local.h"

GDI_CACHE_SVG *gdi_alloc_cache_svg(void)
{
	GDI_CACHE_SVG *cache_svg;
	
	cache_svg = gdi_alloc(sizeof(*cache_svg));
	if (cache_svg == NULL)
		return NULL;

	cache_svg->type = GDI_CACHE_TYPE_SVG;
	cache_svg->path = NULL;

	return cache_svg;
}

void gdi_free_cache_svg(GDI_CACHE_SVG *cache_svg)
{
	GDI_CACHE_PATH *cache = NULL;
	GDI_CACHE_PATH *next = NULL;

	if (cache_svg == NULL)
		return;

	cache = cache_svg->path;
	
	while (cache != NULL) {
		next = cache->next;
		gdi_free_cache_path(cache);
		cache = next;
	}
	gdi_free(cache_svg);
}

GDI_CACHE_BITMAP *gdi_alloc_cache_bitmap(void)
{
	GDI_CACHE_BITMAP *cache_bitmap;
	
	cache_bitmap = gdi_alloc(sizeof(*cache_bitmap));
	if (cache_bitmap == NULL)
		return NULL;
	
	cache_bitmap->type = GDI_CACHE_TYPE_BITMAP;
	cache_bitmap->vg_image = VG_INVALID_HANDLE;
	cache_bitmap->raw_data = NULL;
	
	return cache_bitmap;
}

void gdi_free_cache_bitmap(GDI_CACHE_BITMAP *cache_bitmap)
{
	if (cache_bitmap == NULL)
		return;
	
	if (cache_bitmap->vg_image != VG_INVALID_HANDLE) {
		vgDestroyImage(cache_bitmap->vg_image);
	}
	
	if (cache_bitmap->raw_data != NULL) {
		gdi_free(cache_bitmap->raw_data);
	}
	gdi_free(cache_bitmap);
}

extern USHORT *gdi_dummy_str;

GDI_CACHE_FONT *gdi_alloc_cache_font(void)
{
	GDI_CACHE_FONT *cache_font;
	
	cache_font = (GDI_CACHE_FONT *)gdi_alloc(sizeof(*cache_font));
	if (cache_font == NULL)
		return NULL;

	cache_font->type    = GDI_CACHE_TYPE_FONT;
	cache_font->path    = VG_INVALID_HANDLE;
	cache_font->width   = 0;
	cache_font->height  = 0;

	return cache_font;
}

void gdi_free_cache_font(GDI_CACHE_FONT *cache_font)
{
	if (cache_font == NULL)
		return;
	
	if (cache_font->path != VG_INVALID_HANDLE) {
		vgDestroyPath(cache_font->path);
	}

	gdi_free(cache_font);
}


GDI_CACHE_BITMAP_FONT *gdi_alloc_cache_bitmap_font(void)
{
	GDI_CACHE_BITMAP_FONT *cache_font;

	cache_font = (GDI_CACHE_BITMAP_FONT *)gdi_alloc(sizeof(*cache_font));
	if (cache_font == NULL)
		return NULL;

	cache_font->type = GDI_CACHE_TYPE_BITMAP_FONT;
	cache_font->vg_image = VG_INVALID_HANDLE;
	cache_font->raw_data = NULL;
	cache_font->ucs_str = NULL;
	cache_font->length = 0;
	cache_font->width = 0;
	cache_font->height = 0;

	cache_font->lineUnderflow = 0;
	cache_font->x_pos = 0;
	cache_font->y_pos = 0;
	cache_font->advanceX = 0;
    
	return cache_font;
}

void gdi_free_cache_bitmap_font(GDI_CACHE_BITMAP_FONT *cache_font)
{
	if (cache_font == NULL)
		return;
	
	if (cache_font->vg_image != VG_INVALID_HANDLE) {
		vgDestroyImage(cache_font->vg_image);
	}

	if (cache_font->raw_data != NULL) {
		gdi_bmp_free(cache_font->raw_data);
	}

	gdi_free(cache_font);
}


GDI_CACHE_PATH *gdi_alloc_cache_path(void)
{
	GDI_CACHE_PATH *cache_path;
	
	cache_path = gdi_alloc(sizeof(*cache_path));
	if (cache_path == NULL)
		return NULL;
	
	cache_path->parts = NULL;
	cache_path->path = VG_INVALID_HANDLE;
	cache_path->stroke = VG_INVALID_HANDLE;
	cache_path->fill = VG_INVALID_HANDLE;
	cache_path->mode = 0;
	cache_path->next = NULL;
	
	return cache_path;
}


void gdi_free_cache_path(GDI_CACHE_PATH *cache_path)
{
	if (cache_path == NULL)
		return;
	
	if (cache_path->stroke != VG_INVALID_HANDLE) {
		vgDestroyPaint(cache_path->stroke);
	}
	
	if (cache_path->fill != VG_INVALID_HANDLE) {
		vgDestroyPaint(cache_path->fill);
	}
	
	if (cache_path->path != VG_INVALID_HANDLE) {
		vgDestroyPath(cache_path->path);
	}
	
	gdi_free(cache_path);
}



static unsigned long gdi_crc_table[256];
static int gdi_crc_table_computed = 0;

static void gdi_make_crc_table(void)
{
	unsigned long c;
	int n, k;
	for (n = 0; n < 256; n++) {
		c = (unsigned long)n;
		for (k = 0; k < 8; k++) {
			if (c & 1) {
				c = 0xedb88320L ^ (c >> 1);
			} else {
				c = c >> 1;
			}
		}
		gdi_crc_table[n] = c;
	}
	gdi_crc_table_computed = 1;
}


unsigned long gdi_update_crc(unsigned long crc, unsigned char *buf, int len)
{
	unsigned long c = crc;
	int n;

	if (buf == NULL)
		return 0;
	
	if (!gdi_crc_table_computed) {
		gdi_make_crc_table();
	}
	for (n = 0; n < len; n++) {
		c = gdi_crc_table[(c ^ buf[n]) & 0xFF] ^ (c >> 8);
	}
	return c ^ 0xffffffffL;
}

