
#include "DcwShaperVG.h"
#include "Digitype_std.h"
#include "DcwLayout.h"
#include "DcwCache.h"
#include "DTmanager.h"
#include "DTdigitype.h"
#include "DigiTypeApi.h"


#if (1==DT_OPENVG_ENABLED)
DT32_int getOVGL1SegsCnt(DT32_int segscnt)
{
DBG_MSG_SHOW_FUNC_NAME();

	return segscnt;
}

DT32_int getOVGL1DataCnt(DT32_int segscnt)
{
DBG_MSG_SHOW_FUNC_NAME();

	return 2/*points*/ * 2/*(x,y)*/ * segscnt;
}

DT32_int getOVGL1datasize(DT32_int segscnt)
{
DBG_MSG_SHOW_FUNC_NAME();

	return sizeof(VGubyte)*getOVGL1SegsCnt(segscnt) + sizeof(DT_VGtype)*getOVGL1DataCnt(segscnt);	
}

DT32_int getOVGL2datasize()
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;	
}

DT32_int getOVGL3datasize(DT32_int max_strlen)
{
DBG_MSG_SHOW_FUNC_NAME();

			
	return sizeof(DT16_ushort)*max_strlen;	
}

// this func is used for DTC_TYPE_OVGL1 only
DT32_int CalculateCacheMemOVG(DT_CacheSet *cache)
{
	DT32_long	bytespercache=0, datasize=0;

DBG_MSG_SHOW_FUNC_NAME();

	if( !cache->cachemem || cache->cachesize<=0 ){
		return -1;
	}
	
	switch(cache->type){
	case DTC_TYPE_OVGL1:
		if(cache->condition.max_segs<=0){
			return -1;
		}
		if(cache->condition.max_segs&3){	/* force to times of 4 */
			cache->condition.max_segs = (cache->condition.max_segs+3)/4*4;
		}
		datasize = getOVGL1datasize(cache->condition.max_segs);
		break;
	case DTC_TYPE_OVGL2:
		datasize = getOVGL2datasize();
		break;
	case DTC_TYPE_OVGL3:
		if(cache->condition.max_strlen<=0){
			return -1;
		}
		if(cache->condition.max_strlen&1){	/* force to times of 2 */
			cache->condition.max_strlen = cache->condition.max_strlen+1;	//(cache->condition.max_strlen+1)/2*2;
		}
		datasize = getOVGL3datasize(cache->condition.max_strlen);
		break;
	default:
		return -5;
	}
	
		bytespercache = sizeof(B_CacheUnit)*2 + /* BIndex size, another for temp use when copy.	*/
						sizeof(B_RingUnit) +	/* RingIndex size								*/
						sizeof(CacheUnit) +		/* FontCache size								*/
						datasize;				/* cache data size(bytes)						*/
		if(cache->max_num>0){
			/* Check if cache size is enough. */
			if( cache->cachesize < (DT32_uint)bytespercache*cache->max_num ){
				return -2;
			}
		}else if(0==cache->max_num){
			cache->max_num = cache->cachesize/bytespercache;
			if(cache->max_num<=0){
				return -3;
			}
		}else{
			return -4;
		}
		if(cache->max_num>0xFFFF){
			cache->max_num = 0xFFFF;	/* BIndex pointer boundary check, 2 bytes for this value.	*/
		}

		return 0;
}
#endif	// (1==DT_OPENVG_ENABLED)

/*==========================Start of Cache Functions=============================*/

DT_void InitCache(DT_CacheArray *attr)
{
	DT32_int i;

DBG_MSG_SHOW_FUNC_NAME();

	if(attr->Init_FontCache == 0)
	{
		//direct_log_printf(NULL, "InitCache =================\n");
		attr->Init_FontCache = 1;

		attr->CacheHead = 0;
		attr->CacheNum = 0;

		for(i=0; i < attr->CacheSet->max_num; i++)
			attr->BIndex[i].pointer = i;
	}// end if
}// end InitCache

/* compare key first, then style.				*/
/* return 1, 0, -1: */
DT32_int BCompare(B_CacheUnit* array, DT32_uint key1, DT32_uint style_others1, DT32_uint key2, DT32_uint style_others2)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(key2==key1){
		if(style_others2==style_others1){
			return 0;
		}

		if(style_others2 < style_others1){
			return -1;
		}else{
			return 1;
		}
	}

	if(key2 < key1){
		return -1;
	}else{
		return 1;
	}
}

DT32_uint MakeCacheStyle_others(DT16_ushort style, DT16_ushort others)
{
DBG_MSG_SHOW_FUNC_NAME();

	return (DT32_uint)style + ((DT32_uint)others<<16);
}

DT_void   ParseCacheStyle_others(DT32_uint style_others, DT16_ushort *style, DT16_ushort *others)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(style)
		*style = (DT16_ushort)( style_others & 0xFFFF );
	if(others)
		*others= (DT16_ushort)( style_others >> 16 );
}

DT32_uint MakeCacheKey(DT16_ushort code, DT16_ushort width, DT16_ushort height)
{
	DT32_uint MyKey;

DBG_MSG_SHOW_FUNC_NAME();

	MyKey = code + (((DT8_BYTE)height + ((DT8_BYTE)width << sizeof(DT16_short)*8/2)) << sizeof(DT32_int)*8/2);
	return MyKey;
}

DT_void   ParseCacheKey(DT32_uint key, DT16_ushort *code, DT16_ushort *width, DT16_ushort *height)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(code)
		*code = (DT16_ushort)(key & 0xFFFF);
	if(width)
		*width= (DT16_ushort)((key >> (sizeof(DT32_int)*8/2)) >> (sizeof(DT16_short)*8/2));
	if(height)
		*height= (DT16_ushort)((key >> (sizeof(DT32_int)*8/2)) & 0xFF);
}

DT32_uint GetCacheStyle_others(DT_CacheArray *attr, DT32_int idx)
{
	CacheUnit	*cu;

DBG_MSG_SHOW_FUNC_NAME();

	cu = (attr->FontCache) + attr->BIndex[idx].pointer;
	return MakeCacheStyle_others(cu->style, cu->others);
}

CacheUnit* GetCacheUnit(DT_CacheArray *attr, DT32_int idx)
{
	CacheUnit	*cu;

DBG_MSG_SHOW_FUNC_NAME();

	cu = (attr->FontCache) + attr->BIndex[idx].pointer;
	return cu;
}

DT32_int BSearch(DT_CacheArray *attr, DT32_uint key, DT32_uint style_others, B_CacheUnit* array, DT32_int* len, DT32_int DelKey, DT32_int MaxNum)
{
	DT32_int j, start, now=0, end, ret;
	B_CacheUnit *TmpIndex = attr->tmpBIndex;
	DT16_short OldPointer;
	CacheUnit *unit;

DBG_MSG_SHOW_FUNC_NAME();

	start = 0;
	end = *len-1;
	if(attr->CacheSet->type==DTC_TYPE_OVGL3 && attr->hHandle!=NULL){
		pDT_Fontwrk pdtfwrk = (pDT_Fontwrk)attr->hHandle; 
		DLO_LayAttr *layattr = (DLO_LayAttr*)pdtfwrk->dlolayattr;
		DT16_ushort *p1, *p2;
		DT16_ushort	code1, code2, i, length;
		// don't use binary search for the string
		for(j=start; j<=end; j++){
			// Don't compare style_others here for L3 cache 
			//ret = BCompare(array, (DT32_uint)array[j].key, GetCacheStyle_others(attr,j), key, style_others);
			ret = ((DT32_uint)array[j].key == key) ? 0 : -1;	// only the same key or not.
			if(0==ret){		// length is the same.
				now = j;	// the start of the strings which length and leading code is the same.
				if(SEARCH_MODE == DelKey){	// SEARCH_MODE
					unit = GetCacheUnit(attr, now);
					length= unit->width;
					p1 = (DT16_ushort*)unit->data;
					p2 = layattr->ucs_str;
					// compare string data
					//if(length == layattr->ucs_cnt){	// not required, because BCompare() should quarentee this.
						for(i=0; i<length; i++){
							if(*p1++ != *p2++){
								ret = *(p1-1) - *(p2-1);
								break;
							}
						}
						if(0==ret)
							return now;		// found
					//}
				}else{						//	REPLACE_SEARCH_MODE, DelKey
					if( GetCacheStyle_others(attr,j) == style_others) // only compare style_others when replace search mode.
						return now;
				}
			}else{
				ParseCacheKey((DT32_uint)array[j].key, &code1, NULL, NULL);
				ParseCacheKey((DT32_uint)key, &code2, NULL, NULL);
				if(code2<code1){
					break;
				}				
			}
		}
		now = j;
		//if(REPLACE_SEARCH_MODE == DelKey)
		//	return now;
		//now = 0;	// not found, set now as 0 to be the same with other cache type (DTC_TYPE_XXX)
	}else{	
		while(start <= end)
		{
			now = (end+start)/2;
			
			ret = BCompare(array, (DT32_uint)array[now].key, GetCacheStyle_others(attr,now), key, style_others);
			if(0==ret){
				return now;
			}
			if(ret<0){
				end = now-1;
				if(end<0){
					break;
				}
			}else{
				start = now+1;
				now++;
			}
		}// end while
	}

	if(DelKey >= 0)
	{
		if(*len < MaxNum)			// insert key
		{
			OldPointer = *len;
			DT_memcpy((DT_void*)TmpIndex, (DT_void*)(array+now), (*len-now)*sizeof(B_CacheUnit));
			DT_memcpy((DT_void*)(array+now+1), (DT_void*)TmpIndex, (*len-now)*sizeof(B_CacheUnit));
			(*len)++;
		}else						// replace DelKey
		{
			OldPointer = array[DelKey].pointer;
#if (1==DT_OPENVG_ENABLED)
			if(attr->CacheSet->type==DTC_TYPE_OVGL2){
				unit = GetCacheUnit(attr, DelKey);
				vgDestroyPath((VGPath)unit->extra.infoL2.hVGPath);
				unit->extra.infoL2.hVGPath = VG_INVALID_HANDLE;
			}else if(attr->CacheSet->type==DTC_TYPE_OVGL3){
				unit = GetCacheUnit(attr, DelKey);
				vgDestroyPath((VGPath)unit->extra.infoL3.hVGPath);
				unit->extra.infoL3.hVGPath = VG_INVALID_HANDLE;
			}
#endif

			if(DelKey > now)
			{
				DT_memcpy((DT_void*)TmpIndex, (DT_void*)(array+now), (DelKey-now)*sizeof(B_CacheUnit));
				DT_memcpy((DT_void*)(TmpIndex+DelKey-now), (DT_void*)(array+DelKey+1), (*len-DelKey-1)*sizeof(B_CacheUnit));
				DT_memcpy((DT_void*)(array+now+1), (DT_void*)TmpIndex, (*len-now-1)*sizeof(B_CacheUnit));
			}else if(DelKey < now)
			{
				now--;
				DT_memcpy((DT_void*)(array+DelKey), (DT_void*)(array+DelKey+1), (now-DelKey)*sizeof(B_CacheUnit));
			}// end if
		}// end if

		array[now].key = key;
		array[now].pointer = OldPointer;

		return now;
	}// end if

	return -1;
}// end BSearch

DT32_int TouchCache(DT_CacheArray *attr, DT16_short code, DT16_short width, DT16_short height, DT16_ushort style, DT16_ushort others)
{
	DT32_uint MyKey, ItKey;
	DT32_uint MyStyle_others, ItStyle_others;
	DT32_int MyHead, ItHead;
	DT32_int MyPt, ItPt;

DBG_MSG_SHOW_FUNC_NAME();

	if(attr->CacheNum == 0)
		return 0;

	//MyKey = code + (((DT8_BYTE)height + ((DT8_BYTE)width << sizeof(DT16_short)*8/2)) << sizeof(DT32_int)*8/2);
	MyKey = MakeCacheKey(code, (DT16_ushort)width, (DT16_ushort)height);
	MyStyle_others = MakeCacheStyle_others(style, others);

	if((MyPt = BSearch(attr, MyKey, MyStyle_others, attr->BIndex, &(attr->CacheNum), SEARCH_MODE, attr->CacheSet->max_num)) < 0)
		return -1;

	if(attr->BIndex[MyPt].RingIndex == attr->CacheHead)				// already in top
		return 1;

	MyHead = attr->BIndex[MyPt].RingIndex;
	// MyKey  = 	attr->RingIndex[MyHead].key;
	MyStyle_others = attr->RingIndex[MyHead].style_others;			// re-assign this value for OVG L3 Cache
																	// for other cache the value should be the same, re-assignment isn't required.
	ItHead = (MyHead+1) % (attr->CacheSet->max_num);				// new position
	ItKey = attr->RingIndex[ItHead].key;
	ItStyle_others = attr->RingIndex[ItHead].style_others;

	if((ItPt = BSearch(attr, ItKey, ItStyle_others, attr->BIndex, &(attr->CacheNum), REPLACE_SEARCH_MODE/*SEARCH_MODE*/, attr->CacheSet->max_num)) < 0)
	{
		//HTRACER(TG_DebugSpyBrief, _T("MidPT error %d, %d, %d !!!\n"), ItKey, ItHead, MyPt);
		return -1;
	}// end if

	attr->BIndex[MyPt].RingIndex = ItHead;
	attr->RingIndex[MyHead].key = ItKey;
	attr->RingIndex[MyHead].style_others = ItStyle_others;
	attr->BIndex[ItPt].RingIndex = MyHead;
	attr->RingIndex[ItHead].key = MyKey;
	attr->RingIndex[ItHead].style_others = MyStyle_others;

	return 1;
}// end TouchCache

//DT32_int AddToCache(DT_CacheArray *attr, DT16_ushort code, DT16_short width, DT16_short height, DT16_ushort style, DT_void* data, DT32_int size, DT16_short actw, DT16_short acth)
DT32_int AddToCache(DT_CacheArray *attr, DT16_ushort code, DT16_short width, DT16_short height, CacheUnit *cu)
{
	DT32_uint key, style_others, pt;
	DT32_int Delidx = 0;
	DT16_short index;
	DT8_uchar *tmpdata;
	DT32_int size;		// the accurate value for the cache data needs to be copied.
	DT32_int space;		// reserved space for each cache data. 
#if (1==DT_OPENVG_ENABLED)
	DT32_int size1, size2, space1;
	DT_void *pL1Segs, *pL1Data;
#endif

DBG_MSG_SHOW_FUNC_NAME();

	switch(attr->CacheSet->type){
	case DTC_TYPE_GRAYBMP:
		if(width > attr->CacheSet->condition.max_fontsize || height > attr->CacheSet->condition.max_fontsize)
			return 0;	// too big size
		size = cu->width * cu->height;
		space= attr->CacheSet->condition.max_fontsize * attr->CacheSet->condition.max_fontsize;
		break;
#if (1==DT_OPENVG_ENABLED)
	case DTC_TYPE_OVGL1:
		if(	cu->extra.infoL1.nSegs > getOVGL1SegsCnt(attr->CacheSet->condition.max_segs)
			|| cu->extra.infoL1.nData > getOVGL1DataCnt(attr->CacheSet->condition.max_segs)){
			return 0;
		}
		size1= cu->extra.infoL1.nSegs*sizeof(VGubyte);
		size2= cu->extra.infoL1.nData*sizeof(DT_VGtype);
		//size = size1 + size2;
		space= getOVGL1datasize(attr->CacheSet->condition.max_segs);
		space1 = getOVGL1SegsCnt(attr->CacheSet->condition.max_segs)*sizeof(VGubyte);
		break;
	case DTC_TYPE_OVGL2:
		size = 0;
		space= getOVGL2datasize();
		break;
	case DTC_TYPE_OVGL3:
		// width stands for the length of the string
		if(width > attr->CacheSet->condition.max_strlen)
			return 0;	// too long string
		size = width*sizeof(DT16_ushort);
		space= getOVGL3datasize(attr->CacheSet->condition.max_strlen);
		break;
#endif
	default:
		return 0;
	}

	//key = code + (((DT8_BYTE)height + ((DT8_BYTE)width << sizeof(DT16_short)*8/2)) << sizeof(DT32_int)*8/2);
	key = MakeCacheKey(code, (DT16_ushort)width, (DT16_ushort)height);
	style_others = MakeCacheStyle_others(cu->style, cu->others);

	attr->CacheHead = (attr->CacheHead+1) % (attr->CacheSet->max_num);

	if(attr->CacheNum < attr->CacheSet->max_num)								// append new element
	{
		if(attr->CacheNum > 0)
			pt = BSearch(attr, key, style_others, attr->BIndex, &(attr->CacheNum), attr->CacheHead, attr->CacheSet->max_num);
		else
		{
			pt = 0;
			attr->BIndex[pt].key = key;
			attr->CacheNum++;
		}// end if
	}else														// replace oldest element
	{
		Delidx = BSearch(attr, attr->RingIndex[attr->CacheHead].key, attr->RingIndex[attr->CacheHead].style_others, attr->BIndex, &(attr->CacheNum), /*SEARCH_MODE*/REPLACE_SEARCH_MODE, attr->CacheSet->max_num);
		pt = BSearch(attr, key, style_others, attr->BIndex, &(attr->CacheNum), Delidx, attr->CacheSet->max_num);
	}// end if

	attr->BIndex[pt].RingIndex = attr->CacheHead;
	attr->RingIndex[attr->CacheHead].key = key;
	attr->RingIndex[attr->CacheHead].style_others = style_others;	// it will be overwrited later for L3 cache

	index = attr->BIndex[pt].pointer;
	tmpdata = attr->FontCache[index].data;
	DT_memcpy(&attr->FontCache[index], cu, sizeof(CacheUnit));
	if(tmpdata){
		attr->FontCache[ index ].data	= tmpdata;	/* Delidx exists, replace the oldest, do not use additional memory */
	}else{
		attr->FontCache[ index ].data	= attr->datastart;
		attr->datastart = (DT8_uchar*)attr->datastart + space;	//attr->CacheSet->max_fontsize*attr->CacheSet->max_fontsize;
		attr->datasize -= space;								//attr->CacheSet->max_fontsize*attr->CacheSet->max_fontsize;
	}

	// copy data
	switch(attr->CacheSet->type){
#if (1==DT_OPENVG_ENABLED)
	case DTC_TYPE_OVGL1:
		pL1Segs = cu->data;
		pL1Data = cu->data + gDT_MAX_SEGS_PER_GLYPH;	// FIXME: force this way.
		DT_memcpy((DT8_uchar*)(attr->FontCache[ index ].data), pL1Segs, size1);
		DT_memcpy((DT8_uchar*)(attr->FontCache[ index ].data)+space1, pL1Data, size2);
		break;
	case DTC_TYPE_OVGL2:
		DT_memcpy((DT8_uchar*)(attr->FontCache[ index ].data), cu->data, size);
		break;
	case DTC_TYPE_OVGL3:
		DT_memcpy((DT8_uchar*)(attr->FontCache[ index ].data), cu->data, size);
		style_others = (DT32_uint)attr->FontCache[ index ].data;
		// re-fill the address of the string data to  FontCache.
		ParseCacheStyle_others(style_others, &attr->FontCache[ index ].style, &attr->FontCache[ index ].others);
		attr->RingIndex[attr->CacheHead].style_others = style_others;
		break;
#endif
	case DTC_TYPE_GRAYBMP:
	default:
		DT_memcpy((DT8_uchar*)(attr->FontCache[ index ].data), cu->data, size);
	}
	return 1;
}// end AddToCache

CacheUnit* GetFromCache(DT_CacheArray *attr, DT16_short code, DT16_short width, DT16_short height, DT16_ushort style, DT16_ushort others)
{
	DT32_uint key, style_others;
	DT32_int index;
	
DBG_MSG_SHOW_FUNC_NAME();

	switch(attr->CacheSet->type){
	case DTC_TYPE_GRAYBMP:
		if(width > attr->CacheSet->condition.max_fontsize || height > attr->CacheSet->condition.max_fontsize)
			return NULL;	// too big size
		break;
#if (1==DT_OPENVG_ENABLED)
	case DTC_TYPE_OVGL1:
		break;
	case DTC_TYPE_OVGL2:
		break;
	case DTC_TYPE_OVGL3:
		if(width > attr->CacheSet->condition.max_strlen)
			return 0;	// too long string
		break;
#endif
	default:
		return 0;
	}

	//key = code + (((DT8_BYTE)height + ((DT8_BYTE)width << sizeof(DT16_short)*8/2)) << sizeof(DT32_int)*8/2);
	key = MakeCacheKey(code, (DT16_ushort)width, (DT16_ushort)height);
	style_others = MakeCacheStyle_others(style, others);

	if(attr->CacheNum == 0)
		return NULL;

	index = BSearch(attr, key, style_others, attr->BIndex, &(attr->CacheNum), SEARCH_MODE, attr->CacheSet->max_num);
	if(index >= 0)
	{
		TouchCache(attr, code, width, height, style, others);
		return (attr->FontCache) + attr->BIndex[index].pointer;// pointer to FontCache
	}// end if

	return NULL;
}// end GetFromCache

// this func is used for DTC_TYPE_GRAYBMP only
DT32_int CalculateCacheMemGBMP(DT_CacheSet *cache)
{
	DT32_long	bytespercache=0;

DBG_MSG_SHOW_FUNC_NAME();

		if( !cache->cachemem || cache->cachesize<=0 || cache->condition.max_fontsize<=0){
			return -1;
		}
		if(cache->condition.max_fontsize&3){	/* force to times of 4 */
			cache->condition.max_fontsize = (cache->condition.max_fontsize+3)/4*4;
		}
		if(cache->condition.max_fontsize>gDT_FONT_MAXSIZE){
			cache->condition.max_fontsize = gDT_FONT_MAXSIZE;
		}
		if(cache->condition.max_fontsize>0xFF){
			cache->condition.max_fontsize = 0xFF;	/* BIndex key's boundary check, 1 byte stand for this value. */
		}
		bytespercache = sizeof(B_CacheUnit)*2 + /* BIndex size, another for temp use when copy.	*/
						sizeof(B_RingUnit) +	/* RingIndex size								*/
						sizeof(CacheUnit) +		/* FontCache size								*/
						cache->condition.max_fontsize*cache->condition.max_fontsize;	/* bmp bytes size			*/
		if(cache->max_num>0){
			/* Check if cache size is enough. */
			if( cache->cachesize < (DT32_uint)bytespercache*cache->max_num ){
				return -2;
			}
		}else if(0==cache->max_num){
			cache->max_num = cache->cachesize/bytespercache;
			if(cache->max_num<=0){
				return -3;
			}
		}else{
			return -4;
		}
		if(cache->max_num>0xFFFF){
			cache->max_num = 0xFFFF;	/* BIndex pointer boundary check, 2 bytes for this value.	*/
		}

		return 0;
}

DT_void  CoordinateCacheMem(DT_void* hManager, DT_void* hHandle, DT_CacheSet *cacheset, DT_CacheArray *cachearr)
{
DBG_MSG_SHOW_FUNC_NAME();

		cachearr->hManager	= hManager;
		cachearr->hHandle   = hHandle;
		cachearr->CacheSet  = cacheset;
		cachearr->BIndex    = (B_CacheUnit*)cacheset->cachemem;
		cachearr->tmpBIndex = (B_CacheUnit*)((DT8_uchar*)cachearr->BIndex 
								+ cacheset->max_num*sizeof(B_CacheUnit));
		cachearr->RingIndex = (B_RingUnit*)((DT8_uchar*)cachearr->tmpBIndex 
								+ cacheset->max_num*sizeof(B_CacheUnit));
		cachearr->FontCache = (CacheUnit*)((DT8_uchar*)cachearr->RingIndex 
								+ cacheset->max_num*sizeof(B_RingUnit));
		cachearr->datastart = (DT8_uchar*)((DT8_uchar*)cachearr->FontCache
								+ cacheset->max_num*sizeof(CacheUnit));
		cachearr->datasize  = cachearr->CacheSet->cachesize - ((DT32_uint)cachearr->datastart
								- (DT32_uint)cachearr->CacheSet->cachemem);

		InitCache(cachearr);
}

// Before you call this function, please check if the cache->type is set?
DT32_int CalculateCacheMem(DT_CacheSet *cache)
{
	switch(cache->type){
#if (1==DT_OPENVG_ENABLED)
	case DTC_TYPE_OVGL1:
	case DTC_TYPE_OVGL2:
	case DTC_TYPE_OVGL3:
		return CalculateCacheMemOVG(cache);
#endif
	case DTC_TYPE_GRAYBMP:
	default:
		cache->type = DTC_TYPE_GRAYBMP;		// force to set this (again) for DT_InitDigiType() if the type can't be recognized
		return CalculateCacheMemGBMP(cache);
	}
}
/*==========================End of Cache Functions=============================*/

