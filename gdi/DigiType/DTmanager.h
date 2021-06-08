/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#ifndef __DTMANAGER_H
#define __DTMANAGER_H

#include "DigiTypeApi.h"
#include "DcwCache.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	DT_Font		*dtflist;	/* An array contains a list of all supported fonts. */
	DT32_int	fcnt;		/* the count of dtflist.							*/
	//DT32_long	cachesize;	/* The size of memory can be used as cache memory	*/
	//DT8_char	*cachemem;	/* The allocated cache memory						*/
	DT32_int	totalsize;	/* The required working memory size for FontManager	*/
	DT32_long	tmpbufsize;	/* The size of memory can be used as temp memory	*/
	DT_void		*tempbuf;	/* memory for temp use, don't store data inside when you exit the function.	*/
	DT_CacheSet cacheset;	/* used for cache. memory, size, and settings.		*/
	DT_CacheArray cachearr;	/* used for cache: BIndex, RingIndex, FontCache..etc*/
	//DT32_int	createtimes;/* times of DT_CreateFontFromMem(), knowing when to DT_unInitFontManager().		*/
							/* 0:means user called DT_InitFontManager() & DT_unInitFontManager() by themself.	*/
							/* >0:means user called DT_CreateFontFromMem(), increases 1 once the func be called*/
							/* DT_unInitFontManager() should be called at DT_DestroyFont() when createtimes=1.	*/
}DT_FontMgr_wrk, *pDT_FontMgr_wrk;

/* Get DT_Font by fid after DT_InitFontManager() succeed. */
DT_Font *FMgr_getDTFontByfid(DT_FontMgr_wrk *mgr, DT32_int fid);
/* Add a font to FontManager after DT_InitFontManager() succeed. Return: <0:error; >=0:fid */
DT32_int FMgr_addDTFontData(DT_FontMgr_wrk *mgr, DT_FontData *font);
/* Add a font to FontManager after DT_InitFontManager() succeed. Return: <0:error; >=0:fid */
DT32_int FMgr_addDTFontFile(DT_FontMgr_wrk *mgr, DT_FontFile *font);


// DT_FontMgr FMgr_get_gFontManager();
// DT_void FMgr_set_gFontManager(DT_FontMgr mgr);


/* Input a list of fontfile, and get a DT_FontMgr															*/
/* flist: it is a list of font file path.																	*/
/* fcnt : it is the count of flist.																			*/
/* cache: Prepare a cache memory for caching fonts. cache->cachemem must be 4 bytes-align and cleared as 0.	*/
/*		  After returned, you can check cache->max_num to know how many chars will be cached.				*/
/* reserved: it is not used now.																			*/
/* If you want to limit the memory use of DigiTypeAPI, set gDT_Set_Fix_Memory_Size=1 in DTplatform.h,		*/
/* set gDT_MAXMEMORY_SIZE, and then pass the allocated memory as wkmem in DTplatform.c.						*/
/* Return: a handle if success, NULL if error occurs.														*/
DT_FontMgr DT_InitFontManager(DT_FontFile *flist, DT32_int fcnt, DT_CacheSet *cache, DT_void *reserved);

/* A balanced function of DT_InitFontManager(), release allocated memories...etc							*/
/* Notice: you have to release the userdata in DT_RasterBitBlt() by yourself.								*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_unInitFontManager(DT_FontMgr mgr);

/* Set the conditions of demand to query one or more fonts that meet your needs.							*/
/* "fontslist" is a list of suitable fonts, "ncnt" is the count of fonts inside "fontslist".				*/
/* Return: If successful queried, the return value is the same as ncnt, else return a value <0 as an error. */
//DT32_int DT_QueryFont(DT_FontMgr mgr, DT_FontDemandAttr *demand, DT_Font fontslist[DT_FONTSLIST_MAXCNT], DT32_int *ncnt);


#ifdef __cplusplus
}
#endif

#endif
