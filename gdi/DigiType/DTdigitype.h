/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#ifndef __DTDIGITYPE_H
#define __DTDIGITYPE_H

#include "DigiTypeApi.h"
#include "DcwCache.h"


#define DT_MAX_GLYPH_COUNT_PER_FDL	35000		/* Remember to lower this value to avoid memory waste		*/
												/* if you disabled gEnbale_DT_Charmap.						*/
#define DT_DEFAULT_P_UNDERLINE(szY)	0			/* default underline's position. No matter with szY			*/
#define DT_DEFAULT_P_STRIKE(szY)	((szY)*2/5)	/* default strike line's position. Smaller than szY.		*/

#define DT_DEFAULT_LASTRETURN		(-9999)		/* default value(<0) for lastreturn							*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _DT_LayBuf	/* the returned info & buffer after DT_RasterGBMP() */
{
	DT32_int	gcnt;		/* Returned glyphs count, limit: DT_MAX_GLYPHS_PER_STR		*/
	DT16_ushort	*glyphs;	/* The returned sequence of glyphs					*/
	DT_PosInfo	*carets;	/* Caret position for each glyph cell				*/
	DT16_ushort	writedir;	/* write direction, DT_LEFTTORIGHT, DT_RIGHTTOLEFT	*/
	DT32_int	bmpwidth;	/* the width of bmpbuf								*/
	DT32_int	bmpheight;	/* the height of bmpbuf								*/
	DT32_int	xbytes;		/* how many bytes per line in bmpbuf				*/
	DT32_int	bitcount;	/* bits count per pixel in the bmp buffer			*/
	DT32_int 	bufsize;	/* Size of bmpbuf									*/
	DT8_uchar	*bmpbuf;	/* the layout bmp buffer							*/
}DT_LayBuf, *pDT_LayBuf;

typedef struct _DT_OulBuf	/* the returned info & buffer after DT_RasterOUL()				*/
{
	DT32_int	gcnt;		/* Returned glyphs count										*/
	DT16_ushort	*glyphs;	/* The returned sequence of glyphs								*/
	DT_OulPos	*carets/*[DT_MAX_GLYPHS_PER_STR]*/;	/* Caret position for each glyph cell	*/
	DT16_ushort	writedir;	/* write direction, DT_LEFTTORIGHT, DT_RIGHTTOLEFT				*/
	DT32_int	eswidth;	/* the estimate width of the string, sum of the advanced width	*/
	DT32_int	esheight;	/* the estimate height of string								*/
	DT32_int	pixwidth;	/* the pixel width of the string								*/
	DT32_int	pixheight;	/* the pixel height of string									*/
	DT32_long	*olsizes;	/* each glyph's outline data path count							*/
	DT32_long	olbufsize;	/* the size (bytes) of olbuf									*/
	DT8_char	*olbuf;		/* a buf pool to store the outline data of each glyph in glyphs	*/
}DT_OulBuf, *pDT_OulBuf;

typedef struct{					/* Font style info			*/
	DT32_int	vert;			/* Vertical Writing, range: now, 0 only							*/
	DT32_int	xsize;			/* Horizontal font size, range: 0~gDT_FONT_MAXSIZE				*/
	DT32_int	ysize;			/* Vertical font size, range: 0~gDT_FONT_MAXSIZE				*/
	DT32_int	f_edge;			/* Font Edge style, range: 0~DT_STYLE_MAX_EDGE_FLAG				*/
	DT32_int	w_edge;			/* Font Edge width, range: 0~DT_STYLE_MAX_EDGE_WIDTH			*/
	DT32_int	italic;			/* Italic amount in pixels, range: 0~xsize						*/
	DT32_int	p_underline;	/* Underline position, range: 0~ysize							*/
	DT32_int	w_underline;	/* Underline width, range: 0~ysize								*/
	DT32_int	e_underline;	/* Underline extend, range: 0~xsize, usually the same as italic */
	DT32_int	p_strike;		/* Strike position, range: 0~ysize								*/
	DT32_int	w_strike;		/* Strike width, range: 0~ysize									*/
	DT32_int	e_strike;		/* Strike extend, range: 0~xsize, usually the same as italic	*/

	DT_f26dot6	w_edge266;		/* Font Edge width, range: 0~DT_STYLE_MAX_EDGE_WIDTH			*/

	DT32_int	grade;			/* Bitmap Mode, DT_GRAY_16...etc								*/
	DT8_uchar	gcolor[DT_MAXGRAD+1];   /* Gradation color table, according to grade			*/
	DT32_int	degree;			/* Rotate, degree=10 means 1 degree, range: 0~3600				*/
	DT32_int	writedir;		/* write direction when a string is bi-directional				*/
	DT32_int	oulcoord;		/* coordinate, DT_COORD_LEFT_TOP or DT_COORD_LEFT_BOT			*/
	DT32_int	gen_empath;		/* generate VGPath based on EM?	0: no(based on size); 1: yes.	*/
	DT32_int	grade_values;	/* an easy way to set gcolor when gray16, see DT_FSTYLE_GRAD_VALUES*/
	DT32_int	xbytes_align;	/* horizontal bytes alignment of GBMP, default:4 bytes alignment*/
	DT32_int	spacing;		/* spaces between 2 chars.										*/
	DT32_int	hinting;		/* hinting, 1 or 2 only											*/
	DT32_int	forcedown;		/* force some chars moving down, -1: FDL default; 0-1000: ratio	*/
	DT32_int	bidirule;		/* DLO_BIDI_UNIRULE or DLO_BIDI_DCWRULE.						*/

	DT32_int	is_bold;		/* 0 or 1, DT_FSTYLE_IS_BOLD									*/
	DT32_int	is_italic;		/* 0 or 1, DT_FSTYLE_IS_ITALIC									*/
	DT32_int	is_underline;	/* 0 or 1, DT_FSTYLE_IS_UNDERLINE								*/
	DT32_int	is_strike;		/* 0 or 1, DT_FSTYLE_IS_STRIKE									*/

	DT_void		*cacheset;		/* address of DT_CacheSet.										*/
	DT_void		*ovgL1cache;	/* address of DT_OVGL1_CacheSet.								*/
	DT_void		*ovgL2cache;	/* address of DT_OVGL2_CacheSet.								*/
	DT_void		*ovgL3cache;	/* address of DT_OVGL3_CacheSet.								*/
} DT_StyleAttr, *pDT_StyleAttr;

typedef struct{
	DT_void			*hShaper;		/* DcwShaper's working memory										*/
	DT32_int		totalmemsz;		/* total working memory, DT_Fontwrk, rtbuffer, rtdata are inclusive.*/
	DT_Font			*font;			/* Keep the input font info											*/
	DT32_int		engtype;		/* DLO_EngineType													*/
	DT_StyleAttr	style;			/* keep fontstyle													*/
	DT_void			*dlolayattr;	/* a temp buffer for DLO_LayAttr, used for DT_GetAw(), DT_RasterXXX()*/
	DT32_int		dlolayattrsz;	/* the size (in bytes) of dlolayattr, usually sizeof(DLO_LayAttr)	*/
	DT_void			*dlolaybuf;		/* a temp buffer for DLO_LayBuf, used for DT_GetAw(), DT_RasterXXX()*/
	DT32_int		dlolaybufsz;	/* the size (in byte) of dlolaybuf									*/
	DT_PosInfo		laycarets[DT_MAX_GLYPHS_PER_STR];/* temp buffer for caret position for each glyph cell*/
	DT_OulPos		oulcarets[DT_MAX_GLYPHS_PER_STR];/* temp buffer for outline caret position			*/		
	DT_StrInfo		outinfo;		/* returned glyphs' position info									*/
	DT_LayBuf		*laybuf;		/* for DT_MONOCHROME_MODE or DT_GRAYxxBMP_MODE, pointer to rtbuffer	*/
	DT_OulBuf		*oulbuf;		/* for DT_OUTLINE_MODE, pointer to rtbuffer							*/
	DT8_char		*rtbuffer;		/* a buffer to keep the data of laybuf or oulbuf, type cast before use*/
	DT32_int		rtbuffersz;		/* the size (in byte) of rtbuffer									*/
	DT8_char		*rtdata;		/* a pointer to a bmp or oul data for return 						*/
	DT32_int		rtdatasz;		/* the size (in byte) of rtdata										*/
	DT32_int		rtdataszused;	/* the max size (in byte) of rtdata	ever used.						*/
	DT32_int		rtdatasuggest;	/* the suggest size of rtdata.										*/
/*	DT8_uchar		*tmpseg;*/		/* temp path segs array while parsing each glyph (VGubyte)			*/
/*	DT32_uint		tmpsegsz;*/		/* the size of tmpseg												*/
/*	DT8_char		*tmppath;*/		/* temp path data array while parsing each glyph (VGfloat)			*/
/*	DT32_uint		tmppathsz;*/		/* the size of tmppath												*/
/*	DT8_uchar		*tmpbmp;*/		/* a temp bmp for DT_BitBlt()										*/
/*	DT32_int		tmpbmpsz;*/		/* the size (in byte) of tmpbmp										*/
	DT32_uint		myvgfont;		/* For VGFont, used in DT_RasterOVG()								*/
	DT32_uint		myglyphpath;	/* VGPath for glyphs, used in DLO_ShapeStringVG()					*/
	DT32_uint		mytranspath;	/* VGPath for transparent, used in DLO_ShapeStringVG()				*/
	DT32_uint		mymaskpath;		/* Use a rectangle to fill the mask where fonts been drawn			*/
	DT16_ushort		*charmap;		/* the mapping table of character code & glyph id					*/
	DT32_uint		charmap_num;	/* counts of glyphs in charmap										*/
	DT_Font			*altfont;		/* Alternated font that can be used in the same handle.				*/
	DT32_int		altfontcnt;		/* the count of altfont. now 0 or 1 only.							*/
	DT_Font			*iconfont;		/* Icon font, DIF font file, can be used in the same handle.		*/
	DT32_int		iconfontcnt;	/* the count of iconfont. now 0 or 1 only.							*/
	DT32_int		bRasterOulBold;	/* 1:This time is drawing Bold when DT_STYLE_OUTLINE of DT_RasterBitBlt() */
									/* Only draw normal font when iconfont exist.						*/
	DT_FontMgr		fontmgr;		/* handle of font manager.											*/
	DT_CacheSet		cacheset;		/* used for cache. memory, size, and settings.						*/
	DT_CacheArray	cachearr;		/* used for cache: BIndex, RingIndex, FontCache..etc				*/
	DT_CacheArray	*usedcachearr;	/* NULL: no cache. else point to the cache that should be used.		*/
									/* Cache can passed when DT_InitDigiType(), or set by DT_FCACHE_CACHESET_ADD */
	DT_BOOL			bFastMode;		/* default:DT_FALSE, check isFastMode() to know when will be DT_TRUE*/
#if (1==DT_OPENVG_ENABLED)
	DT32_uint		mytmppath_glyph;/* tmp VGPath for each glyph. DATATYPE is VGfloat for accuracy.					*/
	DT32_uint		mytmppath_glyph00;/* tmp VGPath for each glyph, origin is always (0,0),  DATATYPE is DT_VGtype.	*/
	DT32_uint		mytmppath_strEM;/* tmp VGPath for the ucs_str. EM based.										*/
	DT32_uint		mytmppath_str;	/* tmp VGPath for the ucs_str. DATATYPE is VGfloat for accuracy.				*/
	DT_CacheSet		cachesetL1;		/* used for L1 cache. memory, size, and settings.								*/
	DT_CacheArray	cachearrL1;		/* used for L1 cache: BIndex, RingIndex, FontCache..etc							*/
	DT_CacheArray	*usedcacheL1;	/* NULL: no L1 cache. else point to the cache that should be used.				*/
									/* Cache can passed when DT_InitDigiType(), or set by DT_FCACHE_OVGL1CACHESET_ADD */
	DT_CacheSet		cachesetL2;		/* used for L2 cache. memory, size, and settings.								*/
	DT_CacheArray	cachearrL2;		/* used for L2 cache: BIndex, RingIndex, FontCache..etc							*/
	DT_CacheArray	*usedcacheL2;	/* NULL: no L2 cache. else point to the cache that should be used.				*/
									/* Cache can passed when DT_InitDigiType(), or set by DT_FCACHE_OVGL2CACHESET_ADD */
	DT_CacheSet		cachesetL3;		/* used for L3 cache. memory, size, and settings.								*/
	DT_CacheArray	cachearrL3;		/* used for L3 cache: BIndex, RingIndex, FontCache..etc							*/
	DT_CacheArray	*usedcacheL3;	/* NULL: no L3 cache. else point to the cache that should be used.				*/
									/* Cache can set by DT_FCACHE_OVGL3CACHESET_ADD only							*/
#endif
	/* the lastxxx is used to enhance the performance for DT_GetTextRect() then DT_RasterOVGPath() only!			*/
	DT16_ushort		laststr[DT_MAX_CODES_PER_STR];	/* keep the last str for DT_GetTextRect, DT_RasterPathforOVG	*/
	DT32_int		laststrlen;		/* length of laststr.															*/
	DT32_int		lastreturn;		/* The last return value for laststr, used to check if it's success.			*/
									/* >=0: success, <0: error. it will be -9999 after DT_CreateFontEx()			*/
}DT_Fontwrk, *pDT_Fontwrk;

/**** flag in DT_RasterXXXX() function ****/
#define DT_GET_INFO	0x01	/* use this flag to get position info of ucs_str											*/
#define DT_DRAW		0x02	/* combine this flag to draw all glyphs, get bmps or outlines								*/
							/* DT_RasterBitBlt(): draw to the dc, available when DT_MONOCHROME_MODE or DT_GRAYxxBMP_MODE*/
							/* DT_RasterGBMP(): get a 1-bit-per-pixel bmp (DT_MONOCHROME_MODE), or 1-bit-per-pixel (DT_GRAYxxBMP_MODE)	*/
							/* DT_RasterOVG(): get all glyphs' outlines, DT_OUTLINE_MODE												*/
#define DT_RELEASE	0x04	/* valid for DT_RasterGBMP() only. use this flag to release data while you don't need						*/
							/* you can combine DT_GET_INFO|DT_DRAW to get position info and bmp, then use DT_RELEASE to  release data	*/
							/* Please do not use this flag in other functions like DT_RasterBitBlt(), or DT_RasterOVG()...				*/

/* Return a buffer which contains the gray level of each pixel.	available for DT_MONOCHROME_MODE, DT_GRAYxxBMP_MODE	*/
/* DT_MONOCHROME_MODE in DT_CreateFont(): get a 1-bit-per-pixel bmp after this function.							*/
/* DT_GRAYxxBMP_MODE in DT_CreateFont(): get a 1-byte-per-pixel bmp after this function.							*/
/* If you want to keep the GBMP, you can allocate the required memory((*laybuf)->bufsize) for myownGBMP.			*/
/* myownGBMP also uses as a flag (myownGBMP!=NULL) to tell DigiTypeAPI not to clear the GBMP when DT_RELEASE		*/
/* The usual procedure:  set myownGBMP=NULL and call with DT_GET_INFO|DT_DRAW flag, then call with DT_RELEASE		*/
/* Ex: 
	pDT_LayBuf out;
	DT_Point   xy={0,0};
	DT_RasterGBMP(hnd, str, cnt, DT_GET_INFO | DT_DRAW, &out, NULL, 0, 0, xy);
	... do something you want. ... 
	DT_RasterGBMP(hnd, str, cnt, DT_RELEASE, &out, NULL, 0, 0, xy);
*/
/* If you want to draw to your buffer(myownGBMP) directly:															*/
/*	1. call with DT_GET_INFO flag (myownGBMP is useless now): you can get the buffer size required for myownGBMP,	*/
/*	2. Allocate the required memory of myownGBMP, then call with DT_DRAW flag, the GBMP will be drawn to myownGBMP,	*/
/*  3. call with DT_RELEASE again to release the other members of DT_LayBuf, myownGBMP won't be changed but used as a flag.*/
/* Ex1: 
	pDT_LayBuf out;
	DT_Point   xy={0,0};
	DT_RasterGBMP(hnd, str, cnt, DT_GET_INFO, &out, NULL, 0, 0, xy);
	DT8_uchar *mybmp;
	mybmp = (DT8_uchar*) DT_malloc(out->bufsize); 
	DT_memset(mybmp, out->bufsize);
	DT_RasterGBMP(hnd, str, cnt, DT_DRAW, &out, mybmp, out->xbytes, out->bmpHeight, xy);
	... do something you want. ...
	DT_RasterGBMP(hnd, str, cnt, DT_RELEASE, &out, NULL, 0, 0, xy);
	==> The values in "out" will be cleared, but mybmp will be unchanged. 
*/
/* Ex2:
    ==>Use a buffer to represent a line or a screen.
	mybmp = (DT8_uchar*) DT_malloc(800*600); ==>assume a line won't larger than this,  BOLD style should be considered.
	DT_memset(mybmp, 800*600);
	DT_RasterGBMP(hnd, str, cnt, DT_GET_INFO, &out, NULL, 0, 0, xy);
	xy.x=20; xy.y=30;
	DT_RasterGBMP(hnd, str, cnt, DT_GET_INFO|DT_DRAW, &out, mybmp, 800, 600, xy);
	... do something you want if it need the info in "out". ...
	DT_RasterGBMP(hnd, str, cnt, DT_RELEASE, &out, NULL, 0, 0, xy);	 
*/
/* Return: 0:DT_SUCCESS; <0:error												*/
DT32_int DT_RasterGBMP(DT_Handle hnd, 
			  DT16_ushort* ucs_str,		/* the string to be drawn				*/
			  DT32_int	ucs_cnt,		/* count of ucs_str						*/
			  DT32_int	flag,			/* DT_GET_INFO | DT_DRAW, DT_RELEASE	*/
			  pDT_LayBuf *laybuf,		/* the string info when return.			*/
			  DT_void	*myownGBMP,		/* If it's not NULL, the GBMP will draw to here directly while DT_DRAW	*/
										/* Also used as a flag to enable the following parameters.				*/
			  DT32_int	xbytesOfmyGBMP,	/* How many bytes in a line of myownGBMP.								*/
										/* It will be ignored if myownGBMP=NULL									*/
			  							/* It's caller's responsibility to guarantee this buffer is sufficient.	*/
			  DT32_int	hOfmyGBMP,		/* height of myownGBMP, valid only when	myownGBMP isn't NULL			*/
			  DT_Point	lt				/* left-top point in myownGBMP, valid only when	myownGBMP isn't NULL	*/
			  );

/* Return the outline data of the string. Only DT_OUTLINE_MODE is valid for this function.					*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_RasterOUL(DT_Handle hnd, 
			  DT16_ushort* ucs_str,		/* the string to be drawn					*/
			  DT32_int	ucs_cnt,		/* count of ucs_str							*/
			  DT32_int	flag,			/* DT_GET_INFO | DT_DRAW, DT_RELEASE		*/
			  pDT_OulBuf *oulbuf		/* outline info when return.				*/
			  );

/* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */
/* These functions are used to operate FontEngine directly, no need to distinguish its script or language. */
/* Different from the above functions, it's caller's responsiblity to allocate the required memory for 'bmp' or 'path'*/
/*DT32_int DT_GetCharAw(DT_Handle hnd, DT16_ushort ucs);*/
/*DT32_int DT_GetFontRect(DT_Handle hnd, DT_RECT *rt);*/
/*DT32_int DT_GetCharGBMP(DT_Handle hnd, DT16_ushort ucs, DT_void *bmp, DT32_int xbytes, DT_RECT clip);*/
/*DT32_int DT_GetCharOUL(DT_Handle hnd, DT16_ushort ucs, DT_void *path, DT32_long pathbytes, DT32_long *pathsize);*/
/* ////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

/* Use a font you queried from DT_QueryFont() to create a handle and operate the font.						*/
/* "mode" will be the flag to switch among DT_MONOCHROME_MODE, DT_GRAYxxBMP_MODE, DT_OUTLINE_MODE.			*/
/* It will allocate a memory which contains:																*/
/* fontdata, working memory for DcwShaper & (DcwOpenVG or DcwRaster),										*/
/* and estimate the required memory when a string output according to the input font.						*/
/* It will set the default font styles for raster.															*/
/* Return: a handle if success, NULL if error occurs.														*/
DT_Handle DT_CreateFont(DT_Font *font, DT32_int mode);
/* This function is almost the same as DT_CreateFont(), but you can set a fallback font (bkfont).			*/
/* If a character can't be found in font, bkfont will be used to display the character.						*/
/* font and bkfont should be queried from the same DT_FontMgr, and had the same DT_FontType=DTDigiType_FDL.	*/
/* iconfont is a special formatted bmp font for icon. Its type should be DTIconFont_DIF (*.dif).			*/
/* iconfont is not supported when mode=DT_OUTLINE_MODE.														*/
/* If bkfont=NULL && iconfont=NULL, it's same as DT_CreateFont().											*/
DT_Handle DT_CreateFontEx(DT_Font *font, DT32_int mode, DT_Font *bkfont, DT_Font *iconfont);

/* Set an alternated font list. If some code can't be found in the original font of DT_CreateFont(),		*/
/* DigiTypeAPI will try to find it in the fontlist. Only the fonts with the same ability (DT_FontType type) */
/* will be used. Fonts with other type won't be used.														*/
/* DT_LoadFontData() will be called in this function if the font type matched.								*/
/* And DT_unLoadFontData() will be called in DT_DestroyFont() to release*/
/* Return: the number of fonts in fontlist can be used. 0: no alternated font. <0: something error.			*/
/*DT32_int DT_SetAlternatedFontList(DT_Handle hnd, DT_Font *fontlist, DT32_int cnt);*/

/* *hPath is a VGPath */
DT32_int DT_RasterPathforOVG(pDT_Fontwrk pdtfwrk, DT16_ushort* ucs_str, DT32_int ucs_cnt, DT32_uint* hPath, DT_StrInfo *info);


#ifdef __cplusplus
}
#endif

#endif
