/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#ifndef __DIGITYPEAPI_H
#define __DIGITYPEAPI_H

#include "DTplatform.h"
#include "DTbasedef.h"
#include "DTversion.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (1==DT_OPENVG_ENABLED)
 /* The return of the function DT_RasterOVG() */
 #define DT_VG_CREATEFONT_ERR	-101
 #define DT_VG_BAD_OULBUF		-102
 #define DT_VG_MALLOC_ERR		-103
 #define DT_VG_CREATEPATH_ERR	-104

 /* Temporary code used to set the path to a glyph in OpenVG */
 #define DT_VG_FONTCODE		0x0E3B	/* used for myvgfont */
#endif


/**** Return Values ****/
#define DT_SUCCESS 0

/**** Return value of DT_InitDigiType() ****/
/* Return NULL if something error, else a handle of DT_FontMgr */

/**** Return value of DT_unInitDigiType() ****/
#define DT_BAD_FONTMGR_HANDLE	-1

/**** Return value of DT_CreateFontXXX() ****/
/* Return NULL if something error, else a handle of DT_Handle */

/**** Return value of DT_DestroyFont() ****/
#define DT_BAD_FONT_HANDLE		-2
#define DT_ERROR_DESTROYFONT	-3

/**** Return value of DT_SetFontStyle() ****/
#define DT_STYLE_NOT_SUPPORT	-4

/**** Return value of DT_GetAw(), DT_GetTextRect(), DT_RasterXXX() ****/
#define DT_SCRIPT_NOT_SUPPORT	-5
#define DT_LANG_NOT_SUPPORT		-6
#define DT_ENGINEWKMEM_ERR		-7
#define	DT_UCS_STR_TOO_LONG		-8
#define DT_UCS_ERR				-9
#define DT_NOT_ENOUGH_BUFFER	-10
#define DT_FONTSTYLE_ERROR		-11
#define DT_CREATEFONT_MODE_ERR	-12
#define DT_LAYBUF_ERR			-13
#define DT_BITBLT_ERR			-14
#define DT_TEMP_BUFFER_ERR		-15	/* error of DT_TEMP_BUFFER_SIZE in DTplatform.h */
#define	DT_CACHESET_ADD_ERR		-16

/**** Other warnings of DT_RasterXXX() ****/
#define DT_WARNING_EMPTY_FONT	0x01/* The text string contains one or more characters that don't exist in the font handle. */
#define DT_WARNING_BREAKLINE	0x02/* The text string contains breakline symbol inside, like 0x0A, 0x0D, 0x2028, 0x2029... */
									/* DigiTypeAPI now handles 1 line only, so some chars will disappear when DT_BIDI_UNIRULE*/
#define DT_WARNING_BMP_CUTTED	0x04/* Return by DT_RasterGrayBMP(), the grayBMPbuf might not be enough for all the string.	*/
									/* The bmp might be drawn incompletely. Please check the parameters of xbytes & height.	*/
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/* Call this function to initial DigiTypeAPI. It's the entry point of DigiTypeAPI.							*/
/* cache: Prepare a cache memory for caching fonts. cache->cachemem must be 4 bytes-align and cleared as 0.	*/
/*		  After returned, you can check cache->max_num to know how many chars will be cached.				*/
/* reserved: it is not used now.																			*/
/* DigiTypeAPI will keep a font list of font info that had been created. Maximum: gDT_FONTSLIST_MAXCNT fonts.*/
/* If you want to limit the memory use of DigiTypeAPI, set gDT_Set_Fix_Memory_Size=1 in DTplatform.h,		*/
/* set gDT_MAXMEMORY_SIZE, and then pass the allocated memory as wkmem in DTplatform.c.						*/
/* Return: a handle if success, NULL if error occurs.														*/
DT_FontMgr DT_InitDigiType(DT_CacheSet *cache, DT_void *reserved);
/* A balanced function of DT_InitDigiType(), release allocated memories...etc								*/
/* It should be the last call of DigiTypeAPI.																*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_unInitDigiType(DT_FontMgr mgr);

/* Create Font from a block of memory which fontdata had been loaded. Please assign fontdata to DT_FontData,*/
/* then pass it to this function. Call DT_DestroyFont() when you don't need the font.						*/
/* When you create font by this way, DT_LoadFontData() & DT_unLoadFontData() won't be called.				*/
/* "mgr"  is the handle return from DT_InitDigiType(), can't be NULL.										*/
/* "font" is the font you want to create, can't be NULL. It can be a FDL or BDF(if bkfont is NULL) file.	*/
/* "mode" will be the flag switching among DT_MONOCHROME_MODE, DT_GRAYxxBMP_MODE, DT_OUTLINE_MODE.			*/
/* "bkfont" is a fallback font. If a character can't be found in "font", bkfont will be used. Can be NULL.	*/
/*			If "bkfont" isn't NULL, then "font" and "bkfont" should both be FDL fonts.						*/
/* "iconfont" is a special formatted bmp font for icon. Its type should be DTIconFont_DIF (*.dif).			*/
/*			Can be NULL. "iconfont" is not supported when mode=DT_OUTLINE_MODE.								*/
/* Return: a handle if success, NULL if error occurs.														*/
DT_Handle DT_CreateFontFromMem(DT_FontMgr mgr, DT_FontData *font, DT32_int mode, DT_FontData *bkfont, DT_FontData *iconfont);
/* Almost same as DT_CreateFontFromMem(), but fontdata doesn't come from a block of memory.					*/
/* Create Font from font file path or font fontname. By this way, DT_LoadFontData() & DT_unLoadFontData()	*/
/* in DTplatform.c will be called. You have to implement DT_LoadFontData() to load fontdata.				*/
/* When you DT_DestroyFont(), DT_unLoadFontData() will be called to let you free the fontdata.				*/
/* Return: a handle if success, NULL if error occurs.														*/
DT_Handle DT_CreateFontFromFile(DT_FontMgr mgr, DT_FontFile *font, DT32_int mode, DT_FontFile *bkfont, DT_FontFile *iconfont);
/* A balanced function of DT_CreateFontXXX(), release allocated memories, calling DT_unLoadFontData()...etc	*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_DestroyFont(DT_Handle hnd);

/* Call this function repeatedly to set font styles with their values, or it will use the defaults.			*/
/* Please finish these function calls before you  call DT_GetAw() or DT_RasterXXXX()						*/
/* FontStyle is useless for DT_MONOCHROME_MODE with BDF font.												*/
/* Only some FontStyles are supported by DT_OUTLINE_MODE with FDL. Please check return value.				*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_SetFontStyle(DT_Handle hnd, DT_FontStyle_Option option, DT32_int value);
/* Return: the value you want to get of the specific option.												*/
DT32_int  DT_GetFontStyle(DT_Handle hnd, DT_FontStyle_Option option);

/* Call this function to get the advanced width of the string(ucs_str).							*/
/* Return: >=0: advanced width; <0: error														*/
DT32_int DT_GetAw(	DT_Handle hnd,
					DT16_ushort* ucs_str,		/* the string to be drawn	*/
					DT32_int	 ucs_cnt		/* count of ucs_str			*/
);

/* Call this function to get the width & height of the string(ucs_str).							*/
/* After this function, you can get the text rect (width, height) of ucs_str.					*/
/* rect, xbytes, info can be NULL if you don't want that										*/
/* xbytes & some members in DT_GrayBmpInfo aren't supported by DT_OUTLINE_MODE when DT_CreateFontXXX()*/
/* Notice: The values of "rect" will be roughly estimated while DT_OUTLINE_MODE.				*/
/* Return: 0:DT_SUCCESS; <0:error 																*/
DT32_int DT_GetTextRect(DT_Handle hnd,
						DT16_ushort* ucs_str,		/* the string to be drawn	*/
						DT32_int	 ucs_cnt,		/* count of ucs_str			*/
						DT_RECT		*rect,			/* the text rect to receive, can be NULL	*/
						DT32_int	*xbytes,		/* the xbytes of the rect, can be NULL		*/
						DT_TextInfo	*info			/* the info of glyphs & grayBMP when return. can be NULL*/
);

/* Render the text to the specified buffer(grayBMPbuf).	available for DT_MONOCHROME_MODE, DT_GRAYxxBMP_MODE	*/
/* DT_MONOCHROME_MODE in DT_CreateFontXXX(): get a 1-bit-per-pixel bmp after this function.					*/
/* DT_GRAYxxBMP_MODE in DT_CreateFontXXX(): get a 1-byte-per-pixel bmp after this function.					*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_RasterGrayBMP(DT_Handle hnd, 
			  DT16_ushort* ucs_str,		/* the string to be drawn											*/
			  DT32_int	ucs_cnt,		/* count of ucs_str													*/
			  DT_void	*grayBMPbuf,	/* user allocated buffer to get grayBMP, typecast to DT8_char*, 	*/
			  DT32_int	x0,				/* specify the x of start(left-top) position in grayBMPbuf			*/
			  DT32_int	y0,				/* specify the y of start(left-top) position in grayBMPbuf			*/
			  DT32_int	xbytes,			/* specify how many bytes per line of the allocated grayBMPbuf		*/
			  DT32_int	height			/* specify the height of grayBMPbuf									*/
			  );

/* Draw a string by DT_BitBlt(), valid only when DT_MONOCHROME_MODE or DT_GRAYxxBMP_MODE in DT_CreateFontXXX()*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_RasterBitBlt(DT_Handle hnd, 
			  DT16_ushort* ucs_str,		/* the string to be drawn	*/
			  DT32_int	ucs_cnt,		/* count of ucs_str			*/
			  DT_void	*destdc,		/* destination DC			*/
			  DT32_int	originx,		/* the string start point x of destdc */
			  DT32_int	originy,		/* the string start point y of destdc */
			  DT32_int	nwidth,			/* the width of destination DC	*/
			  DT32_int	nheight,		/* the height of destination DC	*/
			  DT_RGBA	*fcolor,		/* font color				*/
			  DT_RGBA	*bkcolor,		/* background color			*/
			  DT_RGBA	*incolor,		/* inner color when DT_STYLE_OUTLINE, set NULL as no incolor */
			  DT_StrInfo *info,			/* the string info when return.	*/
			  DT_void	**userdata		/* user's data when DT_BitBlt()	*/
			  );

#if(DT_OPENVG_ENABLED==1)
/* Render the font outline data by OpenVG. Only DT_OUTLINE_MODE is valid for this function.					*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_RasterOVG(DT_Handle hnd,
			  DT16_ushort*	ucs_str,		/* the string to be drawn	*/
			  DT32_int		ucs_cnt,		/* count of ucs_str			*/
			  VGfloat 		originx,		/* origin x					*/
			  VGfloat		originy,		/* origin y					*/
			  DT_RGBA		*fcolor,		/* font color				*/
			  DT_RGBA		*incolor,		/* inner color when DT_STYLE_OUTLINE, set NULL as no incolor */
              VGboolean		allowAutoHinting,/* auto hinting by openVG	*/
			  DT_StrInfo	*info			/* the string info when return.	*/
			  );

/* This function is used to get a VGPath(hndstrpath) for ucs_str, valid only when DT_OUTLINE_MODE mode.		*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_RasterOVGPath(DT_Handle hnd, 
			  DT16_ushort* ucs_str,		/* the string to be drawn											*/
			  DT32_int	ucs_cnt,		/* count of ucs_str													*/
			  VGPath	*hndstrpath		/* the result VGPath for ucs_str when this func returned.			*/
										/* can NOT be NULL.													*/
/*			  DT_StrInfo	*info*/		/* the string info when return.										*/
			  );

/* This function will help you to stroke the hndstrpath when masking is required, so before you call this	*/
/* function you have to setup fill & stroke paint ready, and switch to VG_MATRIX_PATH_USER_TO_SURFACE mode.	*/
/* Masking is required in the following 2 situations, other situations won't need masking:					*/
/* 1. stroke the hndstrpath but not fill the hndstrpath														*/
/* 2. stroke the hndstrpath, and fill the hndstrpath with the color which alpha channel isn't 1 (or 0xFF).	*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_StrokeOVGPathByMask(DT_Handle hnd, VGPath hndstrpath);
#endif

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/* These 3 functions are not need in most cases.						*/
/* If these had been called, please re-check the DT_FMEMORY_CREATEFONT.	*/
/* Get the glyphs count of the font file that specified in hnd.			*/
/* Return: the glyphs count of the font file							*/
DT32_uint	DT_GlyphsCount(DT_Handle hnd);
/* Convert the glyph index to unicode									*/
/* Return: 0: not found, else: unicode									*/
DT16_ushort DT_Glyphidx2Unicode(DT_Handle hnd, DT16_ushort idx);
/* Convert unicode to glyph index										*/
/* Return: 0: not found, else: glyph index								*/
DT16_ushort DT_Unicode2Glyphidx(DT_Handle hnd, DT16_ushort ucs);
/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#ifdef DT_ANDROID
DT32_int DT_GetCharOUL(DT_Handle hnd, DT16_ushort ucs, DT_void *path, DT32_long pathbytes, DT32_long *pathsize);
#endif

#ifdef __cplusplus
}
#endif

#endif
