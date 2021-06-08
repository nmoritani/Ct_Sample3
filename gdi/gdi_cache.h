/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#ifndef __GDI_CACHE_H__
#define __GDI_CACHE_H__

#include "gdi.h"

typedef int bool;
#define false 0
#define true  1

typedef void object;

typedef struct _list_node {
	unsigned int key;
	object	*obj;
	struct _list_node *next;
	struct _list_node *prev;
	struct _list *list;
} list_node;

typedef struct _list {
	struct _list_node *head;
	unsigned int length;
} list;

extern list *create_list(void);
extern void free_list(list *list, void (*freeobj)(object *obj));
extern list_node *search_list(list *list, unsigned int key);

extern list_node *create_node(unsigned int key, object *obj);
extern void free_node(list_node *nd);
extern bool insert_node(list_node *nd, list_node *tnd);
extern bool remove_node(list_node *nd);
extern bool move_node(list_node *nd, list_node *tnd, int div);

typedef enum _GDI_CACHE_TYPES {
	GDI_CACHE_SVG,
	GDI_CACHE_BITMAP,
	GDI_CACHE_FONT,
	GDI_CACHE_MAX,
	
} GDI_CACHE_TYPES;


typedef struct _gdi_cache_path {
	GDI_PARTS	*parts;
	VGPath		path;
	VGPaint		stroke;
	VGPaint		fill;
	VGbitfield	mode;
	struct _gdi_cache_path	*next;
	
} gdi_cache_path;


typedef struct _gdi_cache_svg {
	GDI_CACHE_TYPES	type;
	
	gdi_cache_path	*path;
	GDI_COLOR		*stroke;
	GDI_COLOR		*fill;
} GDI_CACHE_SVG;


typedef struct _gdi_cache_bitmap {
	GDI_CACHE_TYPES	type;
	
	VGImage			vg_image;
	unsigned char	*raw_data;
	
} GDI_CACHE_BITMAP;


typedef struct _gdi_cache_font {
	GDI_CACHE_TYPES	type;
	
	VGPath			path;
	VGint			width;
	VGint			height;
	USHORT			*ucs_str;
	unsigned int	length;
	
} GDI_CACHE_FONT;

#endif
