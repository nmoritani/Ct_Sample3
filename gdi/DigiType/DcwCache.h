#ifndef __DCWCACHE_H
#define __DCWCACHE_H

#include "DigiTypeApi.h"

#define SEARCH_MODE				-1		// for BSearch() in search mode.
#define REPLACE_SEARCH_MODE		-2		// for BSearch() in replace search mode. used for OVG L3 Cache (don't compare string contains).
										// because it's <0, it should behave the same as SEARCH_MODE in other Caches (Ex: L1, L2, GBMP)
										// this mode can be used only when you are sure that the unit is in the cache array.
#define INSERT_MODE				1		// for BSearch() in insert new element when don't find key.

/* style_tag: 8-bits can be used */
#define DT_CACHE_GRADEVALUES_INDEX	0x01	/* grade values are 0x00-0x0F */
#define DT_CACHE_VERT_FONT			0x02	/* Vertical Font			  */

/* style_tag for OVG: 8-bits can be used */
#define DT_OVGCACHE_COORDS_LEFTTOP	0x01	/* DT_COORD_LEFT_TOP are set */
#define DT_OVGCACHE_VERT_FONT		0x02	/* Vertical Font			 */
#define DT_OVGCACHE_BIDIRULE_DCW	0x04	/* DT_BIDI_DCWRULE			 */


typedef struct {
	DT16_ushort nSegs;		// count of Segs for OVGL1 cache
	DT16_ushort nData;		// count of Data for OVGL1 cache
	//DT16_ushort Reserved1;		// count of Segs for OVGL1 cache
	//DT16_ushort Reserved2;		// count of Data for OVGL1 cache
}cntinfo_ovgL1;

typedef struct {
	DT32_uint	hVGPath;	// stands for the VGPath
}cntinfo_ovgL2;

typedef struct {
	DT32_uint	hVGPath;	// stands for the VGPath
}cntinfo_ovgL3;

typedef struct {
	DT32_uint key;
	DT16_short RingIndex;
	DT16_short pointer;
}B_CacheUnit;

typedef struct {
	DT16_ushort width;	/* same as fxbyte when DTC_TYPE_GRAYBMP		*/
						/* the string length when DTC_TYPE_OVGL3	*/
	DT16_ushort height;
	DT16_ushort	style;	/* (style>>8):fid; style&0x00FF:style_tag. */
	DT16_ushort	others;	/* Reserved for further use. Implement in BSearch() by yourself if needed.	*/
	union{
		DT8_char		body[4];/* x0, y0, xs, ys	*/	// Jacky_20110610: type redefined from DT8_uchar to DT8_char to endure minus value.
		cntinfo_ovgL1	infoL1;/* nSegs, nData for OVGL1 cache */
		cntinfo_ovgL2	infoL2;/* for OVGL1 cache */
		cntinfo_ovgL3	infoL3;/* nLeng for OVGL3 cache */
	}extra;
	DT8_uchar  *data;
}CacheUnit;

typedef struct {
	DT32_uint	key;
	DT32_uint	style_others;	// in OVG L3 cache, it stands for the pointer to the data.
								// don't compare this element in L3 cache if you just want to check whether a string is inside L3 cache.
}B_RingUnit;

typedef struct {
	//DT_FontMgr  Fontmgr;
	//DTC_CacheType	type;
	DT_void		*hManager, *hHandle;	/* Maybe DT_FontMgr or DT_Handle. Used to know cache is set by which handle. */
	DT32_int	Init_FontCache;
	DT32_int	CacheHead, CacheNum;
	DT32_uint	datasize;
	DT8_uchar	*datastart;
	DT_CacheSet *CacheSet;	/* Used to know if cache enabled. */
	B_CacheUnit *BIndex;
	B_CacheUnit *tmpBIndex;	/* for temp use. */
	B_RingUnit	*RingIndex;	/* DT32_uint	*RingIndex; */
	CacheUnit	*FontCache;
}DT_CacheArray;


DT32_uint MakeCacheStyle_others(DT16_ushort style, DT16_ushort others);
DT32_uint MakeCacheKey(DT16_ushort code, DT16_ushort width, DT16_ushort height);
DT_void   ParseCacheStyle_others(DT32_uint style_others, DT16_ushort *style, DT16_ushort *others);
DT_void   ParseCacheKey(DT32_uint key, DT16_ushort *code, DT16_ushort *width, DT16_ushort *height);
DT32_uint GetCacheStyle_others(DT_CacheArray *attr, DT32_int idx);
CacheUnit* GetCacheUnit(DT_CacheArray *attr, DT32_int idx);


DT32_int TouchCache(DT_CacheArray *attr, DT16_short code, DT16_short width, DT16_short height,DT16_ushort style, DT16_ushort others);
DT32_int BSearch(DT_CacheArray *attr, DT32_uint key, DT32_uint style_others, B_CacheUnit* array, DT32_int* len, DT32_int DelKey, DT32_int MaxNum);


DT_void InitCache(DT_CacheArray *attr);
DT32_int AddToCache(DT_CacheArray *attr, DT16_ushort code, DT16_short width, DT16_short height, CacheUnit *cu);
CacheUnit* GetFromCache(DT_CacheArray *attr, DT16_short code, DT16_short width, DT16_short height, DT16_ushort style, DT16_ushort others);

/* Return <0: error; 0: success.	*/
DT32_int CalculateCacheMem(DT_CacheSet *cache);
DT_void  CoordinateCacheMem(DT_void* hManager, DT_void* hHandle, DT_CacheSet *cacheset, DT_CacheArray *cachearr);
// ================================================================================================

#endif /*__DCWCACHE_H*/
