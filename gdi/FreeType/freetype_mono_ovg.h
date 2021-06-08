#ifndef __FREETYPE_MONO_OVG_H__
#define __FREETYPE_MONO_OVG_H__

#include "gdi.h"

extern GDI_ERRCODE Freetype_GetDrawRect(GDI_FONT_STYLE *gdi_font_style, unsigned short *str, unsigned int *pWidth, unsigned int *pHeight);
extern GDI_ERRCODE FreetypeCreateMonoFontImage(GDI_CACHE_BITMAP_FONT *pCache_font, GDI_FONT_STYLE *gdi_font_style, unsigned short ucs_str, GDI_COLOR *fill_color, GDI_COLOR *stroke_color);
extern GDI_ERRCODE FreeType_DrawFont(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font, GDI_CACHE_FONT *cache);

#endif //__FREETYPE_MONO_OVG_H__
