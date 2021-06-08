/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#ifndef __DTBASE_H
#define __DTBASE_H

#include "DTplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

/**** Handles ****/
typedef DT_void* DT_FontMgr;	/* Returned by DT_InitDigiType() */
typedef DT_void* DT_Handle;		/* Returned by DT_CreateFontXXX()		*/


/**** Max Gray Levels, Depends on DcwRaster ****/
#define DT_MAXGRAD			16	

/**** Max Rotate Degrees, 1/10 degree ****/
#define DT_MAX_DEGREES		3600

/* typeface in DT_FontDemandAttr */
#define DT_DEFAULT_TYPEFACE		0

/* ocassion in DT_FontDemandAttr */
#define DT_DEFAULT_OCASSION_ALL	0

/* mode in DT_CreateFontXXX()					*/
/* Now it's not allowed to combined (by or| ). */
#define DT_OUTLINE_MODE		0x0001
#define DT_MONOCHROME_MODE	0x0002
#define	DT_GRAY256BMP_MODE	0x0004
#define DT_GRAY16BMP_MODE	0x0008

/**** Glyph Bitmap Mode ****/
#define DT_GRAY_MONO		0
#define DT_GRAY_16			1
#define DT_GRAY_256			2
/**** More Glyph Bitmap Mode of DcwRaster-V1.10 ****/
/*#define DT_GRAY_4			0x0100*/
/*#define DT_GRAY_16_2		0x0200*/
/*#define DT_GRAY_64			0x0400*/
#define DT_GRAY_DEF			DT_GRAY_16	/* (DT_GRAY_16) */
#define DT_GRAY_MAX			2

/**** Glyph Bitmap Grade Values Mode ****/
#define DT_GRADE_INDEX_0X00_0X0F	0	/* When GRAY16, graytab is 0-15 */
/*#define DT_GRADE_LINEAR_0X00_0XFF	1*/	/* When GRAY16, graytab is 0x00, 0x11, 0x22...0xEE, 0xFF */
										/* This mode isn't support now. Jacky_20101109			 */
#define DT_GRADE_MAX_FLAG			0	/* 1 */
#define DT_GRADE_DEFAULT			DT_GRADE_INDEX_0X00_0X0F	/* DT_GRADE_LINEAR_0X00_0XFF	 */

/**** Glyph Style: edge: bold, outline ****/
/* Edge Style Flag */
#define DT_STYLE_NORMAL           0
#define DT_STYLE_OUTLINE          1
#define DT_STYLE_BOLD             2
#define DT_STYLE_BOLD_RIGHT       3
#define DT_STYLE_BOLD_DOWN        4
#define DT_STYLE_BOLD_RIGHT_DOWN  5
#define DT_STYLE_MAX_EDGE_FLAG    5
#define DT_STYLE_MAX_EDGE_WIDTH   5
#define DT_STYLE_INNER_NORMAL	 254	/* It's used for drawing the inner of other style, like OUTLINE, BOLD...	*/
										/* Almost same as DT_STYLE_NORMAL, but differs when glyph had been moved.	*/
										/* Ex: THAI_thai, AV, AD, and TONE after UCONS have to shift to left.		*/
										/* When use this flag, please keep w_edge being the same as previous.		*/
#define DT_AUTOGET_F_EDGE(sz)		((sz)<=24 ? DT_STYLE_BOLD_RIGHT : ((sz)<=48 ? DT_STYLE_BOLD_RIGHT_DOWN : DT_STYLE_BOLD))
#ifdef DT_ANDROID
 #define DT_AUTOGET_W_EDGE(sz)		1
#else
 #define DT_AUTOGET_W_EDGE(sz)		((sz)<=48 ? 1 : ((sz)<96 ? 2 : ((sz)/48 + 1)))
#endif
/**** Glyph Style: italic ****/
#define DT_AUTOGET_ITALICMOUNT(sz)	(((sz)/4) > gDT_FONT_MAXITALIC ? gDT_FONT_MAXITALIC : ((sz)/4))	

/**** write direction ****/
/* when using  DLO_SCRIPT_DFLT, DLO_LANG_DFLT */
#define DT_DECIDE_BY_STR	0x0000		/* decide by first encountered code which implies direction. */

#define DT_LEFTTORIGHT		0x200E
#define DT_RIGHTTOLEFT		0x200F

/**** BiDirection Rule ****/
#define DT_BIDI_UNIRULE		0		/* implement according to UAX #9: Unicode Bidirectional Algorithm	*/
#define DT_BIDI_DCWRULE		1		/* Dcw private implement rule.										*/


/**** OpenVG Coordinate System ****/
#define DT_COORD_LEFT_TOP		1
#define DT_COORD_LEFT_BOT		2	/* the original OpenVG coordinate system */

/**** Drawing Method of an glyph, the drawmethod of DT_OulPos. ****/
#define DT_DRAW_NORMAL		0
#define DT_AREA_NOT_DRAW	1

/**** Structures ****/
/* Please assign values to the members in this struct, then pass it to DT_CreateFontFromFile().	*/
typedef struct{
	DT8_char *fontfile;		/* the font file, path with name, NULL terminated.	*/
}DT_FontFile;

/* Please assign values to the members in this struct, then pass it to DT_CreateFontFromMem().	*/
typedef struct{
	DT8_char		*fontdata;	/* the pointer to the address of fontdata		*/
	DT32_long		nfsize;		/* the size of fontdata, in bytes				*/
} DT_FontData;

/* Cache Type */
typedef enum {
	DTC_TYPE_GRAYBMP= 300,	/* stands for DT_CacheSet, DT_FCACHE_CACHESET_ADD			*/
	DTC_TYPE_OVGL1	= 301,	/* stands for DT_OVGL1_CacheSet, DT_FCACHE_OVGL1CACHESET_ADD*/
	DTC_TYPE_OVGL2	= 302,	/* stands for DT_OVGL2_CacheSet, DT_FCACHE_OVGL2CACHESET_ADD*/
	DTC_TYPE_OVGL3	= 303,	/* stands for DT_OVGL3_CacheSet, DT_FCACHE_OVGL3CACHESET_ADD*/
}DTC_CacheType;

/* Gray bmp cache set (DT_CacheSet) - can be set by DT_InitDigiType() or DT_SetFontStyle()	*/ /* only FDL, DT_GRAYXXXBMP_MODE, Normal font */
/* OpenVG string VGpath cache set (DT_OVGL3_CacheSet) - can only be set by DT_SetFontStyle()*/ /* only FDL, DT_OUTLINE_MODE, VRAM used		*/
/* OpenVG glyph VGpath cache set (DT_OVGL2_CacheSet) - can only be set by DT_SetFontStyle()	*/ /* only FDL, DT_OUTLINE_MODE, VRAM used		*/
/* OpenVG glyph data cache set (DT_OVGL1_CacheSet) - can only be set by DT_SetFontStyle()	*/ /* only FDL, DT_OUTLINE_MODE					*/
typedef struct{
	DT32_long *cachemem;	/* point to a block of allocated memory for cache, 4 bytes aligned.	*/
							/* Please memset as 0 before passing to DigiTypeAPI.				*/
	DT32_uint cachesize;	/* size of cachemem, in bytes.	times of 4.							*/
	DTC_CacheType type;		/* Please specify which type of cache when set to DT_InitDigiType() */
							/* If you call DT_SetFontStyle() to set cache, it will be ignored,	*/
							/* and it will be modified to the correspond type when return.		*/
	DT32_int max_num;		/* How many chars (strings) will be cached?							*/
							/* 0 is valid, if you want DigiTypeAPI to calculate it for you.		*/
							/* If max_num is still 0 after DT_InitDigiType(), means cachesize	*/
							/* isn't enough to cache one char(string). Please enlarge it.		*/
							/* This value will be affected by cachesize, condition, style.		*/
							/* You can check this value after setting.							*/
	union{
	DT32_int  max_fontsize;	/* used for DT_CacheSet, gray bmp cache.							*/
							/* font size(x & y) smaller than this value will be cached.			*/
							/* please set a value which >0 and times of 4, else will be an error*/
	DT32_int  max_strlen;	/* used for DT_OVGL3_CacheSet, string VGpath cache.					*/
							/* string length smaller than this value will be cached.			*/
							/* please set a value which >0 and times of 2, else will be an error*/
	DT32_int  max_segs;		/* used for DT_OVGL1_CacheSet, glyphs' path data cache.				*/
							/* the segment count smaller than this value will be cached.		*/
							/* please set a value which >0 and times of 4, else will be an error*/
							/* gDT_MAX_SEGS_PER_GLYPH is recommended for all glyphs drawable.	*/
	}condition;
	DT32_int  style;		/* What kind of font style will be used now. Not used now, set 0.	*/
	DT_void	  *Reserved;	/* Reserved. Useless now.											*/
}DT_CacheSet, DT_OVGL3_CacheSet, DT_OVGL2_CacheSet, DT_OVGL1_CacheSet;

typedef enum {
    DTDigiType_FDL=0,		/* DigiType FDL font file	*//* supports: DT_OUTLINE_MODE, DT_MONOCHROME_MODE, DT_GRAYxxBMP_MODE */
    DTBitmap_BDF=1,			/* Bitmap BDF font file		*//* supports: DT_MONOCHROME_MODE */
    DTTrueType_TTF=2,		/* TrueType font file		*//* Not support yet */
	DTIconFont_DIF=3,		/* Custom-icon DIF font file*//* Can be passed as "iconfont" to DT_CreateFontXXX() */
	DTTypeEnd
} DT_FontType;

typedef struct{			/* The attributes of demanded font	*/
	DT_FontType type;	/* demanded font file type			*//* DTTypeEnd means not specified. */
	DT32_int sizex;		/* demanded x size of font			*//* 0 means not specified.			*/
	DT32_int sizey;		/* demanded y size of font			*//* 0 means not specified.			*/
	DT32_int mode;		/* DT_MONOCHROME_MODE, DT_GRAYxxBMP_MODE, DT_OUTLINE_MODE...	*//* 0 means not specified. */
	DT32_int typeface;	/* demanded typeface				*//* not checked now.				*/
	DT32_int ocassion;	/* demanded ocassion for use		*//* not checked now.				*/
	DT32_int language;	/* DLO_Language, reserved for future*/
	DT32_int codemode;	/* unicode or locale encoded mapping is available in this file. Now, unicode only. *//* not checked now.*/
}DT_FontDemandAttr;

/* This structure will passed in and out to DT_LoadFontData() when you call DT_CreateFontFromFile().		*/
typedef struct{
	DT32_int		fid;		/* the FONT_ID in DT_FontManager				*/
	DT_FontType		type;		/* the type of the fontfile						*/
	DT32_int		ocassion;	/* the ocassion to use, DT_DEFAULT_OCASSION_ALL	*/
	DT32_int		typeface;	/* the typeface of the fontfile, DT_DEFAULT_TYPEFACE*/
	DT8_char		fontname[DT_MAX_FILE_PATH];	/* you can put what you want here, it will be passed to DT_LoadFontData(), font file name, now.	*/
												/* same as "fontfile" in DT_FontFile, DT_CreateFontFromFile() only by-pass it.					*/
												/* DT_LoadFontData() won't be called and fontname[0] will be NULL, when DT_CreateFontFromMem().	*/
	DT32_int		nlen;		/* the length of the fontname					*/
	DT8_char		*fontdata;	/* the pointer to the loaded font file			*/
	DT32_long		nfsize;		/* the size of fontdata							*/
	DT32_int		refcnt;		/* reference counter for DT_LoadFontData()		*/
	DT_FontMgr		fontmgr;	/* handle to font manager						*/
} DT_Font;

/* The Font Style option for DT_SetFontStyle() and DT_GetFontStyle()	*/
/* BDF font doesn't support font styles, except DT_FSTYLE_WRITEDIR.		*/
typedef enum {
	/* Basic options. The SIZEX & SIZEY will be set as gDT_FONT_DEFSIZE after DT_CreateFontXXX()	*/
	DT_FSTYLE_VERT=0,		/* Now, horizontal only.	*/
	DT_FSTYLE_SIZEX=1,		/* desired x size			*/
	DT_FSTYLE_SIZEY=2,		/* desired y size			*/

	/* Followings are used independently, do not use with advanced settings.					*/
	/* When you set DT_FSTYLE_IS_XXXX, the font will be affected by different SIZEX or SIZEY.	*/
	/* This group of DT_FSTYLE_IS_XXXX are not supported by DT_RasterOVG()						*/
	DT_FSTYLE_IS_BOLD=3,		/* Bold font(1) or not(0)	*//* affect F_EDGE, W_EDGE	*/
	DT_FSTYLE_IS_ITALIC=4,		/* Italic font(1) or not(0)	*/
	DT_FSTYLE_IS_UNDERLINE=5,	/* Underline(1) or not(0)	*/
	DT_FSTYLE_IS_STRIKE=6,		/* Strike(1) or not(0)		*//* Not support yet	*/

	/* Followings are used for advanced settings.		*/
	DT_FSTYLE_F_EDGE=20,		/* font edge, such as bold, outline...*/
	DT_FSTYLE_W_EDGE=21,		/* the width of the edge	*//* NOT supported by DT_RasterOVG() */
	DT_FSTYLE_ITALICAMOUNT=22,	/* italic amount in pixels	*//* NOT supported by DT_RasterOVG() */
	DT_FSTYLE_P_UNDERLINE=23,	/* the position of underline*//* NOT supported by DT_RasterOVG() */
	DT_FSTYLE_W_UNDERLINE=24,	/* the width of underline	*//* NOT supported by DT_RasterOVG() */
	DT_FSTYLE_E_UNDERLINE=25,	/* the extend of underline	*//* NOT supported by DT_RasterOVG() */
	DT_FSTYLE_P_STRIKE=26,		/* the position of strike	*//* NOT supported by DT_RasterOVG() */
	DT_FSTYLE_W_STRIKE=27,		/* the width of strike		*//* NOT supported by DT_RasterOVG() */
	DT_FSTYLE_E_STRIKE=28,		/* the extend of strike		*//* NOT supported by DT_RasterOVG() */

	/* Other settings, some restriction may applied. Set these values according to your needs.	*/
	DT_FSTYLE_GRAD=40,			/* GRAY16, GRAY256...etc.	*//* NOT supported by DT_RasterOVG() */
	DT_FSTYLE_DEGREE=41,		/* 1/1000 degree rotated, not support yet				*/	
	DT_FSTYLE_WRITEDIR=42,		/* write direction: DT_LEFTTORIGHT or DT_RIGHTTOLEFT	*/
	DT_FSTYLE_VG_COORD=43,		/* coordinate, DT_COORD_LEFT_TOP or DT_COORD_LEFT_BOT	*/
	DT_FSTYLE_VG_GEN_EMPATH=44,	/* used for DT_OUTLINE_MODE(OpenVG mode) only: */
								/* 0: the path generated by DT_RasterOVGPath() will be based on SIZEX,SIZEY.	*/
								/* 1: the path generated by DT_RasterOVGPath() will be based on gDT_FONT_EMSIZE.*/
	DT_FSTYLE_GRAD_VALUES=45,	/* grade values when GRAY16, now DT_GRADE_INDEX_0X00_0X0F ONLY!		*/
	DT_FSTYLE_XBYTE_ALIGN=46,	/* horizontal bytes alignment for GBMP, default: 4 bytes alignment.	*/
	DT_FSTYLE_SPACING=47,		/* spaces width between 2 chars. */
	DT_FSTYLE_HINTING=48,		/* Hinting mode. 1(no hint) or 2(grid fit), only available for DT_GRAY16BMP_MODE*/
	DT_FSTYLE_FORCE_MOVE_DOWN=49,	/* Force some chars defined in FDL to move down when DT_GRAYXXBMP_MODE.		*/
									/* The value -1: use default. 0-1000: move down ratio, DT_FORCE_MOVE_DOWN_PIXS(szY,Ratio)	*/

	DT_FSTYLE_BIDI_RULE=50,		/* BiDirection Rule: DT_BIDI_UNIRULE or DT_BIDI_DCWRULE	*/

	/* Followings are same as advanced settings above, but decimal enabled(DT_f26dot6). */
	DT_FSTYLE_W_EDGE_26_6=81,	/* the width of the edge	*//* NOT supported by DT_RasterOVG() */

	/* Followings that started with DT_FMETRIX are used for DT_GetFontStyle() only. (No DT_SetFontStyle)*/
	DT_FMETRIX_HEIGHT=100,			/* current font's height*/
	DT_FMETRIX_ASCENT=101,			/* ascent.				*/
	DT_FMETRIX_DESCENT=102,			/* decent.				*/
	DT_FMETRIX_INTERNALLEADING=103,	/* internal leading		*/
	DT_FMETRIX_EXTERNALLEADING=104,	/* external leading		*/
	DT_FMETRIX_WIDTH=105,			/* current font's width.*/
	DT_FMETRIX_OVERHANG=106,		/* the overhang part when italic.	*/
	DT_FMETRIX_FONTWEIGHT=107,		/* font weight, thin(1)-thick(9)	*/
/*	DT_FMETRIX_AVECHARWIDTH=108,*/
/*	DT_FMETRIX_MAXCHARWIDTH=109,*/
/*	DT_FMETRIX_LSB=110,*/
/*	DT_FMETRIX_RSB=111,*/
	
	/* Followings that started with DT_FMEMORY are used for DT_GetFontStyle() only. (No DT_SetFontStyle)*/
	/* All the memory required for fontfile (loaded by DT_loadfilecontent() ) isn't inclusive here.		*/
	/* All the memory usage are handle based, if you create a second font, you have to check the total	*/
	/* memory required or used by yourself.	something like: mem_fmgr + mem_fmini1 + mem_fmini2...		*/
	DT_FMEMORY_FONTMANAGER=200,		/* working memory used for DT_FontMgr, in bytes	*/
	DT_FMEMORY_CREATEFONT=201,		/* working memory needed for DT_Handle to pass DT_CreeateFontXX(), bytes*/
									/* This value might be different when SIZEX(Y)>gDT_FONTSIZE_FOR_MALLOC.	*/
									/* Different mode of DT_CreateFontXX() affects the memory size been used*/
									/* The buffer used for VGPath when DT_OULINE_MODE doesn't be included. 	*/
	DT_FMEMORY_CREATE_MINI_SGST=202,/* The minimum suggestion to create a font according to create mode.	*/
									/* It's almost same as above, but it's the minimum suggestion, not only */
									/* the value required to pass the function call of DT_CreeateFontXX().	*/
									/* The buffer used for VGPath when DT_OULINE_MODE doesn't be included. 	*/
	DT_FMEMORY_FONTHANDLE_USED=203,	/* Use this to know how many bytes were actually used by the font handle*/
									/* This value is recorded from font handle created till you query it.	*/
									/* If you draw a new text, please query again. The value might differs.	*/
									/* DT_FMEMORY_FONTMANAGER + DT_FMEMORY_FONTHANDLE_USED is the value that*/
									/* the total memory had been used till now.								*/
									/* The buffer used for VGPath when DT_OULINE_MODE doesn't be included. 	*/

	/* Used to set cache address. *//* Please typecast the address of DT_XX_CacheSet to DT_void* to pass in.*/
									/* DigiTypeAPI won't free the cache memory. Free it by yourself.		*/
									/* If you set this multi-times, the last one will be used.				*/
	/*DT_CacheSet(Gray bmp cache)*/
	DT_FCACHE_CACHESET_ADD=300,		/* Not recommend to use this. You can set cache in DT_InitDigiType().	*/
									/* If cache is enabled in DT_InitDigiType() and this is set successfully*/
									/* this cache will be used instead of the one in DT_InitDigiType().		*/
	/*DT_OVGL1_CacheSet*/							
	DT_FCACHE_OVGL1CACHESET_ADD=301,/* Following 3 cache are used when DT_OPENVG_ENABLED=1 & DT_OUTLINE_MODE*/
	/*DT_OVGL2_CacheSet*/			/* You can set it by DT_SetFontStyle() ONLY upon your needs.			*/
	DT_FCACHE_OVGL2CACHESET_ADD=302,
	/*DT_OVGL3_CacheSet*/
	DT_FCACHE_OVGL3CACHESET_ADD=303,

	DT_FSTYLE_End=1000000
} DT_FontStyle_Option;

typedef struct _DT_Point{
	DT32_int x;
	DT32_int y;
}DT_Point;

typedef struct _DT_Vector2{
	DT32_int vx;
	DT32_int vy;
}DT_Vector2;

typedef struct _DT_RECT{
	DT_Point	xy;		/* The start position of the rect, according to the coordinate system.	*/
	DT_Vector2	hw;		/* The width & height of the rect, it can be positive or negative.		*/
}DT_RECT;

typedef struct {		/* the returned info & buffer after DT_RasterBitBlt()	*/
	DT32_int	width;	/* the estimate width of the string */
	DT32_int	height;	/* the estimate height of the string*/
	DT32_int	gcnt;	/* the count of glyphs				*/
	DT16_ushort	glyphs[DT_MAX_GLYPHS_PER_STR];	/* the returned glyphs sequence		*/
}DT_StrInfo;

typedef struct _DT_PosInfo{
	/* The following 4 members are not supported since v2.5.29											*/
	/*DT16_ushort sgidx;*/		/* the start index of the cell in glyphs sequence, glyphs					*/
	/*DT16_ushort gextn;*/		/* how many glyphs should be considered together with sgidx as the same cell*/
	/*DT16_ushort scidx;*/		/* the start index of the cell in ucs_str, corresponding to sgidx			*/
	/*DT16_ushort cextn;*/		/* how many codex should be considered together with scidx as the same cell	*/
							/* (glyphs from sgidx to sgidx+gextn) = (ucs_str from scidx to scidx+gextn) */
	DT_Point	caretpos;	/* the caret position of this cell											*/
	DT16_ushort gidx;		/* the index of this glyph in glyphs										*/
							/* "cell" means a group of glyphs replaced several codes in ucs_str			*/
							/* following values represent a cell position information.					*/
}DT_PosInfo;

typedef struct _DT_OulPos{	
	/* The following 4 members are not supported since v2.5.29											*/
	/*DT16_ushort sgidx;*/		/* the start index of the cell in glyphs sequence							*/
	/*DT16_ushort gextn;*/		/* how many glyphs should be considered together with sgidx as the same cell*/
	/*DT16_ushort scidx;*/		/* the start index of the cell in ucs_str, corresponding to sgidx			*/
	/*DT16_ushort cextn;*/		/* how many codex should be considered together with scidx as the same cell	*/
							/* (glyphs from sgidx to sgidx+gextn) = (ucs_str from scidx to scidx+gextn) */
	DT_Point	caretpos;	/* the caret position of this cell											*/
	DT_Point	oripos;		/* The origin position of this glyph, glyphs[gidx].							*/
	DT_Vector2	awvec;		/* advanced width vector of this glyph, glyphs[gidx].						*/
	DT_Vector2	adjvec;		/* adjustment vector of this glyph, glyphs[gidx].							*/
	DT32_int	drawmethod;	/* DT_DRAW_NORMAL or DT_AREA_NOT_DRAW										*/
	DT_RECT		dmrect;		/* the area that drawmethod==DLO_AREA_NOT_DRAW applied.						*/
							/* you shouldn't draw the path segments start(MOVE_TO) inside this area.	*/
	DT16_ushort gidx;		/* the index of this glyph in glyphs										*/
							/* "cell" means a group of glyphs replaced several codes in ucs_str			*/
}DT_OulPos;

typedef struct _DT_TextInfo	/* the returned gray bmp info after DT_GetTextRect() */
{
	DT32_int	gcnt;		/* Returned glyphs count, limit: DT_MAX_GLYPHS_PER_STR		*/
	DT16_ushort	glyphs[DT_MAX_GLYPHS_PER_STR];	/* The returned sequence of glyphs		*/
	DT16_ushort	writedir;	/* write direction, DT_LEFTTORIGHT, DT_RIGHTTOLEFT	*/

	DT_OulPos	oulcarets[DT_MAX_GLYPHS_PER_STR];	/* the info for each glyph, DT_OUTLINE_MODE only	*/
	
	/* Following are not supported by DT_OUTLINE_MODE when DT_CreateFontXXX()	*/
	DT_PosInfo	carets[DT_MAX_GLYPHS_PER_STR];		/* Caret position for each glyph cell*/
	DT32_int	bmpwidth;	/* the width of bmpbuf								*/
	DT32_int	bmpheight;	/* the height of bmpbuf								*/
	DT32_int	xbytes;		/* how many bytes per line in bmpbuf				*/
	DT32_int	bitcount;	/* bits count per pixel in the bmp buffer			*/
	DT32_int 	bufsize;	/* Size of bmpbuf									*/
}DT_TextInfo, *pDT_TextInfo;

#ifdef __cplusplus
}
#endif

#endif
