
#include "DcwApi.h"
#include "Dcw.h"

/*

2007-12-12:

  1. FD_DoDraw - Correct for radical
	 A. Check wrk->rdatacnt <= 0 inside radical.
	 B. radid is 2 byte.
	 C. Symbol - Get Data from rdataof/rdatacnt
	 D. Symbol - Shift (fdl.shiftx/shifty)
  2. DCW_FdlRaster.PreCur - Shift Coordinate for Symbol in Radical
  3. FD_LoadRadData - Table Size 3 Bytes

*/

//#define FDLWRK_BASE_MEMSIZE		((sizeof(DcwWrk) + FDL_MAX_SIZE_BOLD * sizeof(DT16_short) * 2 + FDL_MAX_SIZE_BOLD * sizeof(DT16_short)) * 2)
// Jacky_20110411: FDL_MAX_SIZE_BOLD_ITALIC replaces FDL_MAX_SIZE_BOLD 
#define FDLWRK_BASE_MEMSIZE		(sizeof(DcwWrk) + FDL_MAX_SIZE_BOLD_ITALIC * sizeof(DT16_short) * 2 + FDL_MAX_SIZE_BOLD_ITALIC * sizeof(DT16_short) * 2)
												  /* LeftBuf, RightBuf*/								/* LBuf,	RBuf	*/
//		DcwRaster working memory usage:
//		-------------------------
//		|		DcwWrk			|
//		-------------------------
//		|	LeftBuf, RightBuf	|
//		-------------------------
//		|	LBuf,	RBuf		|
//		-------------------------
//		|	GradMem				|
//		-------------------------

DT32_int stroke_weight[] = {
	// 000, 001, 002, 003, 004, 005, 006, 007, 008, 009, 010, 011, 012, 013, 014, 015, 016, 017, 018, 019, 020, 021, 022, 023, 024, 025, 
//		10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  20,  20,
		10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  20-9,  20-8,  20-7,  20-4,  20-3,  20-2,  20-1,  20,  20,

	// 026, 027, 028, 029, 030, 031, 032, 033, 034, 035, 036, 037, 038, 039, 040, 041, 042, 043, 044, 045, 046, 047, 048, 049, 050
	    20,  20,  20,  20,  20,  20,  25,  25,  25,  25,  25,  25,  25,  25,  25,  25,  25,  25,  26,  27,  28,  29,  30,  30,  30,
//		20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  20,  30,  30,  30,
};


#define HINT_LIST(n, s, h)	DT8_char font_##n##_stroke[]={s};\FDL_StrokeHint font_##n##_hint[]= {h}
#define HIST_NUM(n) SIZEOF_ARRAY(font_##n##_hint), font_##n##_stroke, font_##n##_hint

DT8_uchar font_0000_stroke[]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
FDL_StrokeHint font_0000_hint[]= { {0, 0} };
FONT_GROUP fdl_font_group[] = {
	{0x0000, 0, 0, font_0000_stroke, font_0000_hint},								// Must reserve this for default use.
};

// ============================================================================
/* Gradation */
static DT_void GradationLine(pDcwWrk wrk, DT32_int y, DT32_int xl, DT32_int xr, DT32_int dots, DT32_int dots2, DT32_int maxval, DT32_int count, DT32_int redots, DT8_BYTE *p, DT8_BYTE *p0);
static DT_void GradationLineVert(pDcwWrk wrk, DT32_int x, DT32_int yt, DT32_int yb, DT32_int dots, DT32_int dots2, DT32_int maxval);
static DT_void DrawGradation(pDcwWrk wrk);
static DT_void CalculateFontBoxforGray(pDcwWrk wrk);
static DT_void DrawGradationNoFontBox(pDcwWrk wrk);

/* Font Data */
#ifndef FD_READINTBYDATA1
#define FD_READINTBYDATA1(fontdata, ofs)		( (fontdata)[(ofs)] )		// Not used
#endif
#ifndef FD_READINTBYDATA2
#define FD_READINTBYDATA2(fontdata,ofs)	( (DT32_long)(((DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8) | (DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)])) )
#endif
#ifndef FD_READINTBYDATA4
#define FD_READINTBYDATA4(fontdata,ofs) ( (DT32_long)(((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+3]) << 24) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+2]) << 16) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8)  | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)]))) )
#endif
DT32_long FD_ReadIntByData2(DT8_char *fontdata, DT32_long ofs);
DT32_long FD_ReadIntByData4(DT8_char *fontdata, DT32_long ofs);
DT32_long FD_ReadIntByData(DT8_char *fontdata, DT32_long ofs, DT32_int size);

#define FD_ReadInt1(wrk, ofs)		( wrk->fd[(ofs)] )
static DT32_long FD_ReadInt2(pDcwWrk wrk, DT32_long ofs);
static DT32_long FD_ReadInt4(pDcwWrk wrk, DT32_long ofs);
static DT32_long FD_ReadInt(pDcwWrk wrk, DT32_long ofs, DT32_int size);
static DT32_long FD_ReadFontData(pDcwWrk wrk, DT32_int size);

static DT32_int  FD_LoadStrokeData(pDcwWrk wrk, DT32_int strid, DT32_int *flag);
static DT32_int  FD_LoadRadData(pDcwWrk wrk, DT32_int radid, TFDLRadParam *rad);
static DT_void FD_SetPlane(pDcwWrk wrk, DT32_int plane);
static DT32_int  FD_SearchCMap(pDcwWrk wrk, DT32_int fontidx, DT32_int *gidx);
static DT32_int  FD_SearchPage(pDcwWrk wrk, DT32_int fontidx, DT32_int *gidx);
static DT32_int  FD_LoadFontData(pDcwWrk wrk, DT32_long fontidx, DT16_short *x0, DT16_short *aw, DT16_short *y0, DT16_short *ah);

static DT_void FD_ModifyRadData(pDcwWrk wrk, TFDLRadParam *rad);
static DT32_int GetPairTableValueByData(DT8_char *fontdata, DT32_long ofs, DT16_ushort gidx, DT_void *value, DT16_ushort datalen);


/* Drawing */
static DT32_int  FD_DoDraw(pDcwWrk wrk, TFDLRadParam *rad, DT32_int inrad, DT32_int mode);
static DT_void DrawUnderline(pDcwWrk wrk, DT32_int aw);
static DT_void DrawUnderlineVert(pDcwWrk wrk, DT32_int ah);
static DT_void DrawUnderlineVertRot(pDcwWrk wrk, DT32_int aw);

static const DT32_int GrayDots[DCW_MODE_MAX+1] = { 1, 4, 16};
DT32_int Do_DrawBitmap(DT_void *vwrk, pFdlRasterData fdl);

#if _DCW_DEC_STROKE
	static DT32_int  Ds_SetDsData(pDcwWrk wrk, DT8_char *dsdata);
	static DT32_int  Ds_LoadData(pDcwWrk wrk, DT32_int fidx, DT32_int decstr);
	static DT32_int  Ds_Find(pDcwWrk wrk);
#endif

/*---------------------------------------------------------------------------*/
static DT32_int GetFontIdxScaleRatio(pDcwWrk wrk, DT32_long fontidx, DT32_int *brtochar)
{
	DT32_long ofs;

	*brtochar = 0;
	if(wrk->ctmode!=DCW_Code_Ucs)
	{
		return DCW_BASE_RATIO;
	}
	
	if(wrk->langtab <= 0 || 0 == wrk->langtabcnt)
	{
		return DCW_BASE_RATIO;
	}

	if(fontidx < wrk->RtoTable.StartCode || fontidx > wrk->RtoTable.EndCode)
	{
		return DCW_BASE_RATIO;
	}else
	{
		//return (DT32_int)Icon_Scale_Table[fontidx - DCW_ICON_FIDX_START];
		*brtochar = 1;
		ofs = wrk->RtoTable.ofsRtoData + 2*(fontidx - wrk->RtoTable.StartCode);
		return (DT32_int)(DT16_ushort)FD_READINTBYDATA2(wrk->fd, ofs);
	}

	return DCW_BASE_RATIO;
}

/*---------------------------------------------------------------------------*/
DT32_long FD_ReadIntByData2(DT8_char *fontdata, DT32_long ofs)
{
	DT8_BYTE *p;
	DT32_long val;

DBG_MSG_SHOW_FUNC_NAME();

	p = (DT8_BYTE*)fontdata + ofs;
	
	if(0==gDT_Endianness)	
		if(((DT32_ulong)p & 0x01) == 0)
			return (DT32_long)*((DT16_ushort*)((DT8_BYTE*)fontdata + ofs));

	
	p += 1;	//2-1;

	val = *p--;

	val <<= 8;
	val |= *p;

	return val;
}

/*---------------------------------------------------------------------------*/
DT32_long FD_ReadIntByData4(DT8_char *fontdata, DT32_long ofs)
{
	DT8_BYTE *p;
	DT32_long val;

DBG_MSG_SHOW_FUNC_NAME();

	p = (DT8_BYTE*)fontdata + ofs;
	if(0 == gDT_Endianness)
		if(((DT32_ulong)p & 0x03) == 0)
			return *((DT32_long*)((DT8_BYTE*)fontdata + ofs));

	p += 3;	//4-1;

	val = *p--;

	val <<= 8;
	val |= *p;
	p--;
	
	val <<= 8;
	val |= *p;
	p--;

	val <<= 8;
	val |= *p;

	return val;
}

/*---------------------------------------------------------------------------*/
DT32_long FD_ReadIntByData(DT8_char *fontdata, DT32_long ofs, DT32_int size)
{
	DT8_BYTE *p;
	DT32_long val;
	DT32_int i;

DBG_MSG_SHOW_FUNC_NAME();

	p = (DT8_BYTE*)fontdata + ofs + size-1;

	val = *p--;
	for(i=1; i < size; i++, p--)
	{
		val <<= 8;
		val |= *p;
	}

	return val;
}
/*---------------------------------------------------------------------------*/
DT32_long FD_GetLangTableByData(DT8_char *fontdata, DT32_int LangID, DT32_long langtab, DT16_ushort langtabcnt)
{
#if (0)
	DT16_ushort i;
	DT32_long	ofs, sz;

DBG_MSG_SHOW_FUNC_NAME();

	if(langtab<=0 || 0==langtabcnt || langtabcnt>DCW_MAX_LANGTABCNT_LIMIT)
	{
		return 0;
	}
	
	ofs = langtab + 2;
	for(i=0;i<langtabcnt;i++)
	{
		//DT16_ushort langid	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);
		DT8_uchar	langid = fontdata[ofs], ver = fontdata[ofs+1];			// 2012-02-22: LangID supports id and version.
		sz		= FD_READINTBYDATA4(fontdata, ofs+2);		// Jacky_20110608
		if(langid == LangID){
			return ofs;
		}else{
			ofs += sz;
		}
	}
	
	return 0;
#else
	DT16_ushort i;
	DT32_long	ofs;

DBG_MSG_SHOW_FUNC_NAME();

	if(0==langtabcnt || langtabcnt>DCW_MAX_LANGTABCNT_LIMIT)
	{
		return 0;
	}
	
	ofs = langtab + 2;
	for(i=0;i<langtabcnt;i++)
	{
		DT8_uchar	langid = fontdata[ofs], ver = fontdata[ofs+1];			// 2012-02-22: LangID supports id and version.
		if(langid == LangID){
			return ofs;
		}else{
			ofs += FD_READINTBYDATA4(fontdata, ofs+2);
		}
	}
	
	return 0;
#endif
}
/*---------------------------------------------------------------------------*/
DT32_int GetFontIdxScaleRatioByFontData_Bin(DT8_char *fontdata, DT32_long fontidx, DT32_int opt, DT32_int *brtochar)
{
	DT32_long	langtab, ofs;
	DT16_ushort	langtabcnt;
	DT16_short  ratio;

	ofs = 0;
	ratio = DCW_BASE_RATIO;
	langtabcnt = 0;
	langtab= FD_READINTBYDATA4(fontdata, FD_LANGTAB);
	if(langtab > 0)
	{
		langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab);
		if(langtabcnt > 0){
			ofs = FD_GetLangTableByData(fontdata, opt, langtab, langtabcnt);
			if(ofs > 0){
				GetPairTableValueByData(fontdata, ofs, (DT16_ushort)fontidx, &ratio, sizeof(ratio));
			}
		}
	}

	if(brtochar)
		*brtochar = (DCW_BASE_RATIO==ratio)?0:1;

	return (DT32_int)ratio;	
}
/*---------------------------------------------------------------------------*/
DT32_int GetFontIdxScaleRatioByFontData(DT8_char *fontdata, DT32_long fontidx, DT32_int opt, DT32_int *brtochar)
{
	DT32_long	ofs;
	DT32_long	ctmode, langtab;
	DT16_ushort	langtabcnt;
	Font_Ratio_Icon fri;

DBG_MSG_SHOW_FUNC_NAME();

	if(brtochar)
		*brtochar = 0;
	
	ctmode = FD_READINTBYDATA2(fontdata, FD_CTMODE);
	if(ctmode!=DCW_Code_Ucs)
	{
		return DCW_BASE_RATIO;
	}

	// searched by binary-search
	if(DCW_LANGTAB_BIN_SCALE==opt){		//DCWOUL_LANGTAB_BIN_SCALE should be the same.
		return GetFontIdxScaleRatioByFontData_Bin(fontdata, fontidx, opt, brtochar);
	}

	langtabcnt = 0;
	langtab= FD_READINTBYDATA4(fontdata, FD_LANGTAB);
	if(langtab > 0)
	{
		ofs = langtab;
		langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);
		ofs = FD_GetLangTableByData(fontdata, /*DCW_LANGTAB_ICN*/opt, langtab, langtabcnt);
		if(ofs > 0){
			ofs = ofs + 2/*LangID*/ + 4/*sz*/;
			fri.StartCode	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);		ofs += 2;
			fri.EndCode		= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);		ofs += 2;
			fri.MinRatio	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);		ofs += 2;
			fri.MaxRatio	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);		ofs += 2;
			fri.ofsRtoData= ofs;
		}else{
			return DCW_BASE_RATIO;
		}
	}
	
	if(langtab <= 0 || 0 == langtabcnt)
	{
		return DCW_BASE_RATIO;
	}

	if(fontidx < fri.StartCode || fontidx > fri.EndCode)
	{
		return DCW_BASE_RATIO;
	}else
	{
		//return (DT32_int)Icon_Scale_Table[fontidx - DCW_ICON_FIDX_START];
		if(brtochar)
			*brtochar = 1;
		ofs = fri.ofsRtoData + 2*(fontidx - fri.StartCode);
		return (DT32_int)(DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);
	}

	return DCW_BASE_RATIO;
}

//#define PAIRTABLE_GETIDX(pdata,mid)	( (DT16_ushort) FD_ReadIntByData2((pdata), (mid)*4) )
#define PAIRTABLE_GETIDX(pdata,mid,plen) ( ((DT16_ushort)(((DT8_uchar*)pdata)[(mid)*(plen)+1]) << 8) | (DT16_ushort)(((DT8_uchar*)pdata)[(mid)*(plen)]) )
DT16_ushort pairtable_getIdx(DT8_char *pdata, DT32_long idx, DT16_ushort pairlen)
{
DBG_MSG_SHOW_FUNC_NAME();

	return (DT16_ushort) FD_ReadIntByData2(pdata, idx*pairlen);
}

/* 2012-02-22: don't return value directly, pval is the address of pointer to the data found.				*/
/* used to search the table that data format of each element is (code, value), code & value are all 2 bytes.*/
/* Each pair must be consist of (2bytes, datalen-bytes), use the first 2 byste as unicodes for idx.			*/
DT32_int pairtable_bsearch(DT8_char *pdata, DT16_ushort gidx, DT32_long n, DT8_char **pval, DT16_ushort datalen)
{
    //DT16_ushort mid, low = 0, high = n - 1;
	DT32_long mid, low = 0, high = n - 1;
	DT16_ushort	pairlen = /*sizeof(gidx)*/2 + datalen; 

DBG_MSG_SHOW_FUNC_NAME();
	
    while (low <= high)
    {
        mid = (low + high) / 2;

        if (PAIRTABLE_GETIDX(pdata, mid, pairlen) == gidx)
        {
			*pval = pdata + (mid*pairlen + 2);
            return mid;
        }
        else if (PAIRTABLE_GETIDX(pdata, mid, pairlen) > gidx)
        {
            high = mid - 1;
        }
        else if (PAIRTABLE_GETIDX(pdata, mid, pairlen) < gidx)
        {
            low = mid + 1;
        }
    }

	*pval = NULL;

    return -1;
}

/* search for (2bytes, 2bytes) pair.*/
static DT32_int GetPairTableValueByData(DT8_char *fontdata, DT32_long ofs, DT16_ushort gidx, DT_void *value, DT16_ushort datalen)
{
	DT32_long cnt;
	DT8_char  *pdata, *pval=NULL;
	DT32_long tabsz;
	DT8_char	*pval1 = (DT8_char*)value;
	DT16_short	*pval2 = (DT16_short*)value;
	DT32_long	*pval4 = (DT32_long*)value;

DBG_MSG_SHOW_FUNC_NAME();

	tabsz = FD_READINTBYDATA4(fontdata, (ofs + 2));
	pdata = fontdata + (ofs + 2 + 4);
	cnt = (tabsz-6)/(/*sizeof(gidx)*/2+datalen);	//(tabsz-6)>>2;	//(tabsz-2-4)/4;
	if(cnt>0 && pairtable_bsearch(pdata, gidx, cnt, &pval, datalen) >= 0 )
	{
		if(pval){
			switch(datalen){
			case 2:
				*pval2 = (DT16_short) FD_READINTBYDATA2(pval, 0);
				break;
			case 4:
				*pval4 = (DT32_long) FD_READINTBYDATA4(pval, 0);
				break;
			case 1:
				*pval1 = *pval;
				break;
			default:
				value  = pval;		// pointer to the data directly
			}
		}
		return 0;
	}else{
		if(value){
			switch(datalen){
			case 2:
				*pval2 = 0;
				break;
			case 4:
				*pval4 = 0;
				break;
			case 1:
				*pval1 = 0;
			default:
				value  = NULL;
			}
		}
	}

	return -1;
}

/* 20110922: offsetY might be a negative value, so change the type from DT16_ushort to DT16_short.							*/
/* 2012-02-22: in the new format (version 1) DCW_LANGTAB_DESCENT table, offsetY are combined by 2 values: offsetY and logh.	*/
DT32_int FD_GetYoffsetByData(DT8_char *fontdata, DT32_long ofs, DT16_ushort gidx, DT_void *offsetY, DT16_ushort datalen)
{
	return GetPairTableValueByData(fontdata, ofs, gidx, offsetY, datalen);
}

DT32_int GetFontRatio(DCW_AttrData *attr)
{
	DT32_int ratio;
	DT16_ushort langtabcnt;
	DT32_long ofs, langtab;
	ratio = 64;
	ofs = 0;
	langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
	if(langtab > 0)
	{
		ofs = langtab;
		langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, ofs);
		ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_GLOBAL, langtab, langtabcnt);
		if(ofs==0)
		{
			ratio = 64;
		}else{
			ratio = FD_READINTBYDATA4(attr->fontdata, ofs+6); /*sizeof(sz)=2*/
		}
	}
	return (DT32_int) ratio;
}

DT32_int EnlargeFontByRatio(DCW_AttrData *attr, DT32_long fontidx, DT32_int *bRtoChar)
{
	DT32_int rto;

	rto = GetFontRatio(attr);
	attr->xsize = (attr->xsize*rto)>>6;	//attr->xsize*rto/64;
	attr->ysize = (attr->ysize*rto)>>6;	//attr->ysize*rto/64;
	if(bRtoChar)
		*bRtoChar = rto;
	
	return DCW_SUCCESS;
}

DT32_int NeedMoreActions(DCW_AttrData *attr, DT32_long fontidx)
{
	// Enlarge font will be done at DcwShaperVG, won't be done here.
	//EnlargeFontByRatio(attr, fontidx, NULL);

	return DCW_SUCCESS;
}

#define OPT_BASIC_CHECK	0x00000001
#define OPT_RASTER_ATTR	0x00000002
#define OPT_GRAY_LEVELS	0x00000004
DT32_int ReSetDcwWrk(pDcwWrk wrk, DCW_AttrData *attr, DT32_long fontidx, DT32_int option)
{
	DT32_int	ret, /*i,*/ dots;
	DT32_uint	action;

#ifdef DCW_ENABLE_MODIFYATTR_WHEN_RASTER
	action  = OPT_BASIC_CHECK;	// always need.
	switch(option)
	{
	case DCW_OPT_RESETWRK_FOR_GETAW:
		// basic check is enough
		break;
	case DCW_OPT_RESETWRK_FOR_RASTER:
		action |= OPT_RASTER_ATTR;
		break;
	default:
		action |= OPT_RASTER_ATTR | OPT_GRAY_LEVELS;	// unknown option: reset all.
	}

	//------ Do Actions ------//
	if(action & OPT_BASIC_CHECK)
	{
	////// Now fontsize and some attributes can be decided after DCW_Create(), but not fontdata changed. //////
	////// Callers need to guarantee the correctness of the attribute values, ex: xsize, ysize, f_edge.. //////
		//if(wrk->attr.fontdata != wrk->fd)
		//	return DCW_BAD_FONTDATA;
		//if(wrk->fdl.grade != wrk->attr.grade)
		//	return DCW_INVALID_GRADE;
		if(!((DT8_uchar*)(wrk->attr.fontdata) == wrk->fd) || wrk->fdl.grade != wrk->attr.grade)
		{
			ret = DCW_Create(attr);
			if(ret < 0){
				return ret;
			}
		}

		/* Copy Attribute */
		wrk->attr = *attr;

		// get ratio to enlarge char, or other actions.
		NeedMoreActions(&wrk->attr, fontidx);
	}

	if(action & OPT_RASTER_ATTR)
	{
		/* Rasterizer Attribute */
		dots = GrayDots[wrk->attr.grade];
		wrk->fdl.xsize  = wrk->attr.xsize * dots;
		wrk->fdl.ysize  = wrk->attr.ysize * dots;
		wrk->fdl.w_edge = (wrk->attr.f_edge!=DCW_EDGE_NORMAL) ? wrk->attr.w_edge * dots : 0;
		wrk->fdl.italic = wrk->attr.italic * dots;
		wrk->fdl.shiftx = 0;
		wrk->fdl.shifty = 0;
	}

	// 20110804: Marked by Jacky for reduce memory, gcolor isn't used in DigiTypeAPI even for Gray16
//	if(action & OPT_GRAY_LEVELS)
//	{
//	// Once gcolor is changed, DcwShaperVG will guarantee re-call DCW_Create() first, 
//	// so no need to reset the gcolor, comment it here.
//		if(wrk->attr.grade == DCW_MODE_GRAY16)
//		{
//			for(i=0; i<DCW_MAXGRAD+1; i++)
//				wrk->fdl.gcolor[i] = attr->gcolor[i];
//		}
//	}
	////// End of the re-modifing attributes.															 //////
#endif
	
	return DCW_SUCCESS;
}

/*---------------------------------------------------------------------------*/
DT32_int DCW_EstimateWkMem(DT32_int sizex, DT32_int sizey, DT32_int grade, DT32_int option)
{
  DT32_int MinMem=0, BaseMem=0, GradMem=0;
  DT32_int ratio_szX=sizex, ratio_szY=sizey;

DBG_MSG_SHOW_FUNC_NAME();

//#if (1 != DCW_MAX_SIZEXY_ASPECT)
//	if(1 < DCW_MAX_SIZEXY_ASPECT)
//	{
//		ratio_szX = sizex * DCW_MAX_SIZEXY_ASPECT + 2*DCW_MAX_EDGE_WIDTH;
//		/*ratio_szY = sizey * DCW_MAX_SIZEXY_ASPECT;*/	/* ICON will be put at the upper part of font rect.		*/
//														/* The height of real font body won't larger than sizey	*/
//		ratio_szY = sizey + 2*DCW_MAX_EDGE_WIDTH;
//	}else{
//		ratio_szX = sizex + 2*DCW_MAX_EDGE_WIDTH;
//		ratio_szY = sizey + 2*DCW_MAX_EDGE_WIDTH;
//	}
//
//	if(ratio_szX > DCW_MAXSIZE)
//	{
//		ratio_szX = DCW_MAXSIZE;
//	}
//	if(ratio_szY > DCW_MAXSIZE)
//	{
//		ratio_szY = DCW_MAXSIZE;
//	}
//#endif

	ratio_szX = sizex + 2*DCW_MAX_EDGE_WIDTH;
	ratio_szY = sizey + 2*DCW_MAX_EDGE_WIDTH + DCW_MAXITALICAMOUNT;

//  BaseMem = sizeof(DcwWrk) + 
//			FDL_MAX_SIZE * sizeof(DT16_short) +		/* LeftBuf, RightBuf*/
//			FDL_MAX_SIZE_BOLD * sizeof(DT16_short);	/* LBuf,	RBuf	*/
	BaseMem = FDLWRK_BASE_MEMSIZE;

  switch (grade)
  {
    case DCW_MODE_MONOCHROME:
      //MinMem = sizeof(DcwWrk);
	  GradMem = 0;
      break;

    case DCW_MODE_GRAY16:
      //MinMem = sizeof(DcwWrk) + sizeof(DT16_ushort) * ratio_szY * 4 + sizeof(TFGXPair) * ratio_szY * 4 * 4;
	  //MinMem += 0x2000;	/* For safety concern */
	  
	  //MinMem = sizeof(DcwWrk) + sizeof(DT16_ushort) * ratio_szY * 4 + sizeof(TFGXPair) * (ratio_szY*MAX_REF_DATA/(128*2));
      GradMem = sizeof(DT16_ushort) * ratio_szY * 4 + sizeof(TFGXPair) * (ratio_szY*MAX_REF_DATA/(128*2));
	  break;

    case DCW_MODE_GRAY256:
	default:
      //MinMem = sizeof(DcwWrk) + sizeof(DT16_ushort) * ratio_szY * 16 + sizeof(TFGXPair) * ratio_szY * 8 * 4;
	  //MinMem += 0xA000;	/* For safety concern */
	  
	  //MinMem = sizeof(DcwWrk) + sizeof(DT16_ushort) * ratio_szY * 16 + sizeof(TFGXPair) * (ratio_szY*MAX_REF_DATA/128);
	  GradMem = sizeof(DT16_ushort) * ratio_szY * 16 + sizeof(TFGXPair) * (ratio_szY*MAX_REF_DATA/128);
      break;
  }

  if(option==0){
	  option = DCW_WKMEM_DEFAULT;
  }

  if(option & DCW_WKMEM_BASE){
	  MinMem += BaseMem;
  }
  if(option & DCW_WKMEM_GRAD){
	  MinMem += GradMem;
  }


  if(MinMem == 0){	// If option specified isn't found, use DCW_WKMEM_DEFAULT instead.
	  MinMem = BaseMem + GradMem;
  }

#ifdef FDL_OUTLINE_CACHE
  MinMem += FDL_OUTLINE_CACHE_SIZE;
#endif

#ifdef DT_SUB_MEMORY
  MinMem += DT_SUBMEMORY_SIZE;	
#endif

  return MinMem;
}

/*---------------------------------------------------------------------------*/
DT32_int DCW_QueryCharAttr(DCW_AttrData *attr, DT32_long fontidx, DCW_CharAttr_Option option)
{
	DT32_int	szY, ratio, bRtoChar;
	DT16_ushort langtabcnt;
	DT32_long	ofs, langtab;
//	DT32_long	offsetY;
	DT32_int	ret=-1;

//	langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
//	if(langtab > 0)
//		langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab);
//	else
//		langtabcnt = 0;
		
	switch(option){


	case DCW_CHARATTR_LANGTAB_GLOBAL:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_GLOBAL, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
		return (DT32_int)ofs;

	case DCW_CHARATTR_LANGTAB_HINDI_SUB:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_HINDI_SUB, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;

	case DCW_CHARATTR_LANGTAB_HINDI_POS1:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_HINDI_POS1, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;

	case DCW_CHARATTR_LANGTAB_HINDI_POS2:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_HINDI_POS2, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;

	case DCW_CHARATTR_LANGTAB_HINDI_POS3:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_HINDI_POS3, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;

	case DCW_CHARATTR_LANGTAB_RSB:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_RSB, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;


	case DCW_CHARATTR_LANGTAB_THAI:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_THA, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;

		return (DT32_int)ofs;
	case DCW_CHARATTR_LANGTAB_ICON:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_ICN, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;
	case DCW_CHARATTR_LANGTAB_RAS_SCALE:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_RAS_SCALE, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;
	case DCW_CHARATTR_LANGTAB_BIN_SCALE:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_BIN_SCALE, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;
	case DCW_CHARATTR_LANGTAB_DESCENT:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_DESCENT, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;	
	case DCW_CHARATTR_XYSCALERATIO:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(attr->fontdata, fontidx, DCW_LANGTAB_ICN, &bRtoChar);
		return ratio;
	case DCW_CHARATTR_ISXYSCALE_CHAR:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(attr->fontdata, fontidx, DCW_LANGTAB_ICN, &bRtoChar);
		return bRtoChar;
	case DCW_CHARATTR_RASSCALERATIO:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(attr->fontdata, fontidx, DCW_LANGTAB_RAS_SCALE, &bRtoChar);
		return ratio;
	case DCW_CHARATTR_ISRASSCALE_CHAR:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(attr->fontdata, fontidx, DCW_LANGTAB_RAS_SCALE, &bRtoChar);
		return bRtoChar;	
	case DCW_CHARATTR_BINSCALERATIO:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(attr->fontdata, fontidx, DCW_LANGTAB_BIN_SCALE, &bRtoChar);
		return ratio;
	case DCW_CHARATTR_ISBINSCALE_CHAR:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(attr->fontdata, fontidx, DCW_LANGTAB_BIN_SCALE, &bRtoChar);
		return bRtoChar;
	case DCW_CHARATTR_HEIGHT_SHIFT:
		return 0;
	case DCW_CHARATTR_NORMAL_WIDTH:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(attr->fontdata, fontidx, DCW_LANGTAB_ICN, &bRtoChar);
		szY = DCW_SCALED_SIZEXY(attr->ysize,ratio);		//attr->ysize*1000/ratio;
		if(DCW_BASE_RATIO==ratio){
			return attr->xsize;
		}else{
			return szY;// force scaling by ysize.
		}
		break;
	case DCW_CHARATTR_NORMAL_HEIGHT:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(attr->fontdata, fontidx, DCW_LANGTAB_ICN, &bRtoChar);
		szY = DCW_SCALED_SIZEXY(attr->ysize,ratio);		//attr->ysize*1000/ratio;
		if(DCW_BASE_RATIO==ratio){
			return attr->ysize;
		}else{
			return szY;
		}
		break;
	case DCW_CHARATTR_ISOFFSETY_CHAR:
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_DESCENT, langtab, langtabcnt);
			if(ofs > 0){
				DT8_uchar ver = (DT8_uchar) attr->fontdata[ofs + 1];
				if(1==ver){
					DT32_long offsetY = 0;
					ret = FD_GetYoffsetByData(attr->fontdata, ofs, (DT16_ushort)fontidx, &offsetY, 4);					
				}else{
					DT16_short offsetY = 0;
					ret = FD_GetYoffsetByData(attr->fontdata, ofs, (DT16_ushort)fontidx, &offsetY, 2);
				}
				if(ret>=0){
					return 1;
				}
			}
		}
		return 0;
	case DCW_CHARATTR_GET_OFFSETY:		// return a DT32_long in 16.16 format, represents for logh.offsety 
	case DCW_CHARATTR_GET_LOGHEIGHT:	// return a DT32_long in 16.16 format, represents for logh.offsety
	case DCW_CHARATTR_GET_3IN1_VALUE:	// return a DT32_long in 10.10.12 format, represents for logt.logh.offsety
		ofs = 0;
		langtab= FD_READINTBYDATA4(attr->fontdata, FD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(attr->fontdata, langtab);
			ofs = FD_GetLangTableByData(attr->fontdata, DCW_LANGTAB_DESCENT, langtab, langtabcnt);
			if(ofs > 0){
				DT8_uchar ver = (DT8_uchar) attr->fontdata[ofs + 1];
				DT_BOOL   b3in1 = (DCW_CHARATTR_GET_3IN1_VALUE==option)?DT_TRUE:DT_FALSE;
				DT32_long offy, logh, logt;
				if(1==ver){
					DT32_long offsetY = 0;
					ret = FD_GetYoffsetByData(attr->fontdata, ofs, (DT16_ushort)fontidx, &offsetY, 4);
					if(b3in1){
						offy = DCW_OFFY_FROM_LOGHOFFY(offsetY);
						logh = DCW_LOGH_FROM_LOGHOFFY(offsetY);
						logt = 0;
						return (DT32_int) DCW_MAKE_3IN1_VALUE(offy,logh,logt);
					}else
						return (DT32_int) offsetY;
				}else if(2==ver){
					DT32_long val3in1 = 0;
					ret = FD_GetYoffsetByData(attr->fontdata, ofs, (DT16_ushort)fontidx, &val3in1, 4);
					if(b3in1){
						return (DT32_int) val3in1;
					}else /*if(DCW_CHARATTR_GET_OFFSETY==option || DCW_CHARATTR_GET_LOGHEIGHT==option)*/{
						offy = DCW_OFFY_FROM_3IN1_VALUE(val3in1);
						logh = DCW_LOGH_FROM_3IN1_VALUE(val3in1);
						return (DT32_int) DCW_MAKE_LOGH_OFFY(offy,logh);
					}
				}else{
					DT16_short offsetY = 0;
					ret = FD_GetYoffsetByData(attr->fontdata, ofs, (DT16_ushort)fontidx, &offsetY, 2);
					if(b3in1){
						offy = (DT32_long) offsetY;
						logh = 0;
						logt = 0;
						return (DT32_int) DCW_MAKE_3IN1_VALUE(offy,logh,logt);
					}else
						return (DT32_int) offsetY;
				}
			}
		}
		return 0;
	case DCW_CHARATTR_END:
	default:
		return 0;
	}

	return 0;
}

/*---------------------------------------------------------------------------*/
DT32_int DCW_Create(DCW_AttrData *attr)
{
	pDcwWrk wrk = (pDcwWrk)attr->WkMem;
	DT32_long MinMem, ofs, basememsz;
	DT32_int dots, i, bRemainGradMem = 0;

DBG_MSG_SHOW_FUNC_NAME();

	/* Check Font Size */
	if(attr->xsize > DCW_MAXSIZE || attr->ysize > DCW_MAXSIZE)
		return DCW_SIZE_TOO_LARGE;

	/* Check Edge Flag / Width */
	if(attr->f_edge < 0 || attr->f_edge > DCW_MAX_EDGE_FLAG)
		return DCW_INVALID_EDGE_FLAG;

	if(attr->f_edge !=0 &&
	   (attr->w_edge < 0 || attr->w_edge > DCW_MAX_EDGE_WIDTH))
		return DCW_INVALID_EDGE_WIDTH;

	/* The integer part must be the same as w_edge */
	if(attr->f_edge !=0 && (DT32_int)DTF266ToInt(attr->w_edge266)!=attr->w_edge )
		return DCW_INVALID_EDGE_WIDTH;

	/* Check Italic */
	if(attr->italic < 0 || attr->italic > attr->xsize)
		return DCW_INVALID_ITALIC;

	/* Check Underline */
	if(attr->w_underline > 0)
	{
		if(attr->p_underline < 0 ||
		   attr->p_underline >= attr->ysize ||
		   attr->p_underline + attr->w_underline > attr->ysize ||
		   attr->e_underline < 0)
			return DCW_INVALID_UNDERLINE;
	} else if(attr->w_underline < 0)
		return DCW_INVALID_UNDERLINE;

	/* Check Bitmap Mode */
	if(attr->grade < 0 || attr->grade > DCW_MODE_MAX)
		return DCW_INVALID_GRADE;

	/* Check Gray16 Palette Table */
	if(attr->grade == DCW_MODE_GRAY16 && attr->gcolor[0] != 16)
		return DCW_INVALID_GRADE_COLOR;

	/* Check font data */
	if(!attr->fontdata)
		return DCW_BAD_FONTDATA;

	/* Estimate Working Memory Used */
//	switch(attr->grade)
//	{
//		case DCW_MODE_MONOCHROME:
//			MinMem = sizeof(DcwWrk);
//			break;
//
//		case DCW_MODE_GRAY16:
//			MinMem = sizeof(DcwWrk) + sizeof(DT16_ushort) * attr->ysize * 4 +
//					 sizeof(TFGXPair) * attr->ysize * 4 * 4;
//			break;
//
//		case DCW_MODE_GRAY256:
//			MinMem = sizeof(DcwWrk) + sizeof(DT16_ushort) * attr->ysize * 16 +
//					 sizeof(TFGXPair) * attr->ysize * 8 * 4;
//			break;
//		default:
//			return DCW_INVALID_GRADE;
//	}

#ifdef DCW_ASSIGN_GRADATION_MEM
	if(gDT_Set_Fix_Memory_Size==1){
		bRemainGradMem = 1;
	}
#endif

	if(bRemainGradMem)
		MinMem = (DT32_long) DCW_EstimateWkMem(attr->xsize, attr->ysize, attr->grade, DCW_WKMEM_BASE);
	else
		MinMem = (DT32_long) DCW_EstimateWkMem(attr->xsize, attr->ysize, attr->grade, DCW_WKMEM_DEFAULT);
	
	if(attr->WkMemSize < MinMem)
		return DCW_NOT_ENOUGH_WKMEM;

	//if((attr->WkMemSize) < (sizeof(DcwWrk) + FDL_OUTLINE_CACHE_SIZE + DT_SUBMEMORY_SIZE))
	//	return DCW_NOT_ENOUGH_WKMEM;

	/* Copy Attribute */
	wrk->attr = *attr;

	/* Rasterizer Attribute */
	wrk->fdl.grade = wrk->attr.grade;

	dots = GrayDots[wrk->attr.grade];
	wrk->fdl.xsize  = wrk->attr.xsize * dots;
	wrk->fdl.ysize  = wrk->attr.ysize * dots;
	wrk->fdl.w_edge = (wrk->attr.f_edge!=DCW_EDGE_NORMAL) ? wrk->attr.w_edge * dots : 0;
	wrk->fdl.italic = wrk->attr.italic * dots;
	wrk->fdl.shiftx = 0;
	wrk->fdl.shifty = 0;

	// 20110804: Marked by Jacky for reduce memory, gcolor isn't used in DigiTypeAPI even for Gray16
//	if(wrk->attr.grade == DCW_MODE_GRAY16)
//	{
//		for(i=0; i<DCW_MAXGRAD+1; i++)
//			wrk->fdl.gcolor[i] = attr->gcolor[i];
//	}

	/* Setup Font Data */
	wrk->fd = (DT8_BYTE*)wrk->attr.fontdata;

	for(i=0; i<8; i++)
		wrk->fdl.defval[i] = (DT16_WORD)FD_READINTBYDATA2(wrk->fd, FD_DEFVAL+i*2);

	wrk->strcnt = FD_READINTBYDATA2(wrk->fd, FD_STRCNT);
	wrk->radcnt = FD_READINTBYDATA2(wrk->fd, FD_RADCNT);
	wrk->foncnt = FD_READINTBYDATA2(wrk->fd, FD_FONCNT);
	wrk->strtab = FD_READINTBYDATA4(wrk->fd, FD_STRTAB);
	wrk->strofs = FD_READINTBYDATA4(wrk->fd, FD_STROFS);
	wrk->radtab = FD_READINTBYDATA4(wrk->fd, FD_RADTAB);
	wrk->radofs = FD_READINTBYDATA4(wrk->fd, FD_RADOFS);
	wrk->fontab = FD_READINTBYDATA4(wrk->fd, FD_FONTAB);
	wrk->fonofs = FD_READINTBYDATA4(wrk->fd, FD_FONOFS);
	wrk->ctmode = FD_READINTBYDATA2(wrk->fd, FD_CTMODE);
	wrk->version= FD_READINTBYDATA2(wrk->fd, FD_VERSION);

#if _DCW_DEC_STROKE
	
	if(FD_ReadInt(wrk, FD_DECSTR, 4) == FD_DSTR_IDENT){
		wrk->decstr = FD_ReadInt(wrk, FD_DECSTR+4, 4);	// FD_DECSTR
		Ds_SetDsData(wrk, wrk->fd + wrk->decstr);
	}else{
		wrk->decstr = 0;
		Ds_SetDsData(wrk, NULL);
	}
#endif

#ifdef FDL_EXTEND
	wrk->extend = FD_READINTBYDATA4(wrk->fd, FD_EXTEND);
	wrk->sizecount = 0;
	if(wrk->extend != 0)
	{
		//wrk->sizecount = FD_ReadInt(wrk, wrk->extend, 4);
		//wrk->extend += sizeof(DT32_long);
		wrk->subcnt[0] = FD_READINTBYDATA4(wrk->fd, wrk->extend);
	}else wrk->subcnt[0] = 0;
#endif
	ofs = wrk->fontab;
	if(wrk->version == 0x101)
	{
		wrk->foncnt  = FD_READINTBYDATA4(wrk->fd, ofs);
		wrk->fonloc  = FD_READINTBYDATA4(wrk->fd, ofs+4) + wrk->fontab;
		wrk->fonmap  = (DT16_ushort)FD_READINTBYDATA2(wrk->fd, ofs+8);
		wrk->planeno = (DT16_ushort)FD_READINTBYDATA2(wrk->fd, ofs+10);
		wrk->planes  = ofs + 12;
		wrk->plane   = -1;
	} else
	{
		wrk->fonmap  = 0xffff;

		if(wrk->foncnt == 0)
		{
			wrk->foncnt = FD_READINTBYDATA4(wrk->fd, ofs);
			wrk->fonloc = ofs + 4;
		} else
			wrk->fonloc	= ofs;
	}

	/* assign the required memory for render. Please ensure basememsz=FDLWRK_BASE_MEMSIZE when return. */
	basememsz = sizeof(DcwWrk);
	wrk->fdl.LeftBuf = (DT16_short*) ((DT8_char*)wrk + basememsz);
	basememsz += FDL_MAX_SIZE_BOLD_ITALIC * sizeof(DT16_short);	//FDL_MAX_SIZE * sizeof(DT16_short);	// Jacky_20110411
	wrk->fdl.RightBuf= (DT16_short*) ((DT8_char*)wrk + basememsz);
	basememsz += FDL_MAX_SIZE_BOLD_ITALIC * sizeof(DT16_short);	//FDL_MAX_SIZE * sizeof(DT16_short);
	wrk->fdl.LBuf	 = (DT16_short*) ((DT8_char*)wrk + basememsz);
	basememsz += FDL_MAX_SIZE_BOLD_ITALIC * sizeof(DT16_short);	//FDL_MAX_SIZE_BOLD * sizeof(DT16_short);
	wrk->fdl.RBuf	 = (DT16_short*) ((DT8_char*)wrk + basememsz);
	basememsz += FDL_MAX_SIZE_BOLD_ITALIC * sizeof(DT16_short);	//FDL_MAX_SIZE_BOLD * sizeof(DT16_short);

	if(attr->WkMemSize < basememsz)
		return DCW_NOT_ENOUGH_WKMEM;


	return DCW_SUCCESS;
}
/*---------------------------------------------------------------------------*/
DT32_int DCW_Raster(DCW_AttrData *attr, DCW_RasterData *raster)
{
	pDcwWrk wrk = (pDcwWrk)attr->WkMem;
	DT16_short x0, aw, y0, ah;
	DT32_int savecnt, saveofs;
	DT32_int dots, yt, yb, ext, ret, temp;
	DT32_long gmemsize;
	DT8_char *gmem;


DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_DEBUG
//  wrk->fp = fopen("D:\\Debug.txt", "w+t");
#endif

	wrk->fdl.wrk  = wrk;

//#ifdef DCW_ENABLE_MODIFYATTR_WHEN_RASTER
//	////// Now fontsize and some attributes can be decided after DCW_Create(), but not fontdata changed. //////
//	////// Callers need to guarantee the correctness of the attribute values, ex: xsize, ysize, f_edge.. //////
//	if(wrk->attr.fontdata != wrk->fd)
//		return DCW_BAD_FONTDATA;
//	if(	wrk->fdl.grade != wrk->attr.grade)
//		return DCW_INVALID_GRADE;
//
//	/* Copy Attribute */
//	wrk->attr = *attr;
//
//	/* Rasterizer Attribute */
//	dots = GrayDots[wrk->attr.grade];
//	wrk->fdl.xsize  = wrk->attr.xsize * dots;
//	wrk->fdl.ysize  = wrk->attr.ysize * dots;
//	wrk->fdl.w_edge = (wrk->attr.f_edge!=DCW_EDGE_NORMAL) ? wrk->attr.w_edge * dots : 0;
//	wrk->fdl.italic = wrk->attr.italic * dots;
//	wrk->fdl.shiftx = 0;
//	wrk->fdl.shifty = 0;
//
//	// Once gcolor is changed, DcwShaperVG will guarantee re-call DCW_Create() first, 
//	// so no need to reset the gcolor, comment it here.
////	if(wrk->attr.grade == DCW_MODE_GRAY16)
////	{
////		for(i=0; i<DCW_MAXGRAD+1; i++)
////			wrk->fdl.gcolor[i] = attr->gcolor[i];
////	}
//	////// End of the re-modifing attributes.															 //////
//#endif

	ret = ReSetDcwWrk(wrk, attr, raster->fontidx, DCW_OPT_RESETWRK_FOR_RASTER);
	if(DCW_SUCCESS != ret)
		return ret;

#ifdef FORCE_HINTING_0_TO_3
	if(attr->grade){
		wrk->fdl.hint = (FDL_NO_HINT==raster->hint) ? 3 : raster->hint;
	}else{
		wrk->fdl.hint = FDL_NO_HINT;
	}
#else
	wrk->fdl.hint = attr->grade ? raster->hint : FDL_OLD_HINT;	//0; //Modified_by_Jacky_20101103_FOR_MONOCHROME
#endif

	if( wrk->ctmode==DCW_Code_Ucs && 
		!(raster->fontidx>=FDL_HINTING_AREA_START && raster->fontidx<=FDL_HINTING_AREA_END))
	{
		wrk->fdl.hint = FDL_OLD_HINT;
	}

	wrk->fdl.grade = attr->grade;					// Alan.

	/* Setup Bitmap */
	wrk->fdl.bmp  = raster->bitmap;
	wrk->fdl.bmpw = raster->xbyte;

	/* Load font data */

	if(!FD_LoadFontData(wrk, raster->fontidx, &x0, &aw, &y0, &ah))
		return DCW_EMPTY_FONT;

#if _DCW_DEC_STROKE
	/* Load Decrease Stroke Data of Font */
	Ds_LoadData(wrk, raster->fontidx, wrk->decstr);
#endif

	wrk->fdl.fontidx = raster->fontidx;

	dots = GrayDots[wrk->attr.grade];
#if 1
	wrk->fdl.x0 = (DT16_short)(((DT32_long)x0 * wrk->attr.xsize * dots) / 1000);
	wrk->fdl.y0 = (DT16_short)(((DT32_long)y0 * wrk->attr.ysize * dots) / 1000);
#else
	if(x0 != 0)	x0 = (DT16_short)(((DT32_long)x0 * wrk->attr.xsize) / 1000);
	if(y0 != 0)	y0 = (DT16_short)(((DT32_long)y0 * wrk->attr.ysize) / 1000);
	wrk->fdl.x0   = x0 * dots;
	wrk->fdl.y0   = y0 * dots;
#endif

//	if(x0 != 0)	x0 = (DT16_short)(((DT32_long)x0 * attr->xsize) / 1000);
//	if(y0 != 0)	y0 = (DT16_short)(((DT32_long)y0 * attr->ysize) / 1000);

	/* Swap Rotate Font Size */
	if(wrk->fdl.rot)
	{
		temp = wrk->fdl.xsize;
		wrk->fdl.xsize = wrk->fdl.ysize;
		wrk->fdl.ysize = temp;
	}

	/* Setup font/bitmap origin */
//	dots = GrayDots[wrk->attr.grade];
//	wrk->fdl.x0   = x0 * dots;
//	wrk->fdl.y0   = y0 * dots;
	wrk->fdl.xorg = raster->x0 * dots;
	wrk->fdl.yorg = raster->y0 * dots;

	switch(wrk->attr.grade)
	{
		case DCW_MODE_MONOCHROME:
			/* Initial font rect */
			wrk->fdl.fontbox.left   = 32767;
			wrk->fdl.fontbox.top    = 32767;
			wrk->fdl.fontbox.right  = 0;
			wrk->fdl.fontbox.bottom = 0;
			break;

		case DCW_MODE_GRAY16:
		case DCW_MODE_GRAY256:
			/* Setup gradation data */
			yt = -wrk->fdl.w_edge;
			yb = wrk->fdl.ysize + wrk->fdl.w_edge - 1;
			if(wrk->fdl.vert && (wrk->attr.italic>0 || wrk->attr.w_underline>0))
			{
				ext = (wrk->attr.w_underline>0) ? wrk->attr.e_underline : 0;
				if(wrk->attr.italic > ext) 
					ext = wrk->attr.italic;
				yb += ext * dots;
			}

#ifdef FDL_OUTLINE_CACHE
			//gmem = (DT8_char*)wrk + sizeof(DcwWrk);
			//gmemsize = wrk->attr.WkMemSize - sizeof(DcwWrk) - FDL_OUTLINE_CACHE_SIZE - DT_SUBMEMORY_SIZE;
			gmem = (DT8_char*)wrk + FDLWRK_BASE_MEMSIZE;
			gmemsize = wrk->attr.WkMemSize - FDLWRK_BASE_MEMSIZE;

#ifdef DCW_ASSIGN_GRADATION_MEM
			// Re-assign the block of gradation memory.
			// Use raster->GradMem to distinguish if gradation memory will be assigned.
			if(raster->GradMem && raster->GradMemSize>0)
			{
				gmem = (DT8_char*)raster->GradMem;
				gmemsize = raster->GradMemSize;
			}
#endif
			FG_Initial(&wrk->gdata, yt, yb, gmem, gmemsize, wrk);
			FG_OutlineCache_Initial(&wrk->goutlinecache, gmem+gmemsize, FDL_OUTLINE_CACHE_SIZE, wrk);
			gmem += gmemsize;
#else
			//gmem = (DT8_char*)wrk + sizeof(DcwWrk);
			//gmemsize = wrk->attr.WkMemSize - sizeof(DcwWrk) - DT_SUBMEMORY_SIZE;

			gmem = (DT8_char*)wrk + FDLWRK_BASE_MEMSIZE;
			gmemsize = wrk->attr.WkMemSize - FDLWRK_BASE_MEMSIZE;

#ifdef DCW_ASSIGN_GRADATION_MEM
			// Re-assign the block of gradation memory.
			// Use raster->GradMem to distinguish if gradation memory will be assigned.
			if(raster->GradMem && raster->GradMemSize>0)
			{
				gmem = (DT8_char*)raster->GradMem;
				gmemsize = raster->GradMemSize;
			}
#endif
			FG_Initial(&wrk->gdata, yt, yb, gmem, gmemsize, wrk);
			gmem += gmemsize;
#endif

#ifdef DT_SUB_MEMORY
			wrk->fdl.submem = DT_memory_init(gmem, DT_SUBMEMORY_SIZE, 1, DT_BLOCKSIZE);		// Init sub memory system.
#endif
			break;
	}

	/* Draw underline */
	if(wrk->attr.w_underline > 0)
	{
		// It must not get into here, because w_underline won't >0 in DigiTypeAPI. (underline will be drawn in DigiTypeAPI, not here.)
		if(!wrk->attr.vert)
			DrawUnderline(wrk, aw);
		else if(!wrk->fdl.rot)
			DrawUnderlineVert(wrk, ah);
		else
			DrawUnderlineVertRot(wrk, aw);
	}

	wrk->fdl.path_num = 0;								// Alan.
	wrk->fdl.stridcnt = 0;
	wrk->fdl.Symbolcnt= 0;								//Jacky
	wrk->fdl.Strokecnt= 0;
#ifdef ENABLE_ADV_HINTING
#ifdef FDL_ITS_NEW_HINTLIST_DATA	// Jacky_20101115_for_TestNewRemoveStroke
{// block
	// Now no hintlistV.
	DT32_int i;
	FDL_StrokeHint *Hhintlist;
	wrk->fdl.weight_modeH = FDL_STROKE_HINT_DISABLE;
	wrk->fdl.hintlistH_num = wrk->fdl.hintlistV_num = 0;
	if(wrk->fdl.groupinfo.hintnum > 0){
	  wrk->fdl.hintlistH_num = wrk->fdl.groupinfo.hintnum;
	  if(wrk->fdl.hintlistH_num > 0){
		Hhintlist = wrk->fdl.groupinfo.hintlist;
        if(attr->ysize <= Hhintlist[0].size || Hhintlist[0].size == 0)
		{
#if 0	/* old rule: i:size20 ==> i+1:size16, then weight_modeH=i+1 if size19,18,17*/
          for(i=0; i < wrk->fdl.hintlistH_num; i++)
		  {
            if(attr->ysize >= Hhintlist[i].size)
			{
              wrk->fdl.weight_modeH = i;
			  i++;	// for the next loop
              break;
			}
		  }
		  // Added_by_Jacky: for multi removed strokes of the same size
		  for(;i<wrk->fdl.hintlistH_num;i++){
			if(i>0 && (Hhintlist[i-1].size == Hhintlist[i].size)){
				wrk->fdl.weight_modeH++;
			}else{
				break;
			}
		  }

#else	/* new rule: i:size20 ==> i+1:size16, then weight_modeH=i if size19,18,17*/
          for(i=0; i < wrk->fdl.hintlistH_num; i++)
		  {
			if(attr->ysize <= Hhintlist[i].size)
			{
              wrk->fdl.weight_modeH = i;	/* */
			}else{
			  break;
			}
		  }
#endif

		}
	    // Use all removed strokes.
	    if((FDL_STROKE_HINT_DISABLE==wrk->fdl.weight_modeH) &&
		  attr->ysize<=Hhintlist[wrk->fdl.hintlistH_num-1].size){
			wrk->fdl.weight_modeH = wrk->fdl.hintlistH_num-1;
		}
	  }	
	}
}// end block	
#else
{// block

	DT32_int i, j;
	FDL_StrokeHint *Hhintlist, *Vhintlist;
	wrk->fdl.weight_modeH = FDL_STROKE_HINT_DISABLE;
	wrk->fdl.weight_modeV = FDL_STROKE_HINT_DISABLE;
	wrk->fdl.hintlistH_num = wrk->fdl.hintlistV_num = 0;
    if(wrk->fdl.groupinfo.hintnum > 0)
    {
	  //Get the number of remove strokes.
	  for(i=0; i < wrk->fdl.groupinfo.hintnum; i++)
	  {
		if(wrk->fdl.groupinfo.hintlist[i].stroke & FDL_ALIGN_VSTROKE){
		  break;
		}else{
		  wrk->fdl.hintlistH_num++;
		}
	  }
	  wrk->fdl.hintlistV_num = wrk->fdl.groupinfo.hintnum - wrk->fdl.hintlistH_num;

	  //How many weight_modeH?
	  if(wrk->fdl.hintlistH_num > 0){
		Hhintlist = wrk->fdl.groupinfo.hintlist;
        if(attr->ysize <= Hhintlist[0].size || Hhintlist[0].size == 0)
		{
          for(i=0; i < wrk->fdl.hintlistH_num; i++)
		  {
            if(attr->ysize >= Hhintlist[i].size)
			{
              wrk->fdl.weight_modeH = i;
			  i++;	// for the next loop
              break;
			}
		  }
		  // Added_by_Jacky: for multi removed strokes of the same size
		  for(;i<wrk->fdl.hintlistH_num;i++){
			if(attr->ysize == Hhintlist[i].size){
				wrk->fdl.weight_modeH++;
			}else{
				break;
			}
		  }
		}
	    // Use all removed strokes.
	    if((FDL_STROKE_HINT_DISABLE==wrk->fdl.weight_modeH) &&
		  attr->ysize<=Hhintlist[wrk->fdl.hintlistH_num-1].size){
			wrk->fdl.weight_modeH = wrk->fdl.hintlistH_num-1;
		}
	  }
	  
	  //How many weight_modeV?
	  if(wrk->fdl.hintlistV_num > 0){
		Vhintlist = wrk->fdl.groupinfo.hintlist + wrk->fdl.hintlistH_num;
        if( attr->xsize <= Vhintlist[0].size || Vhintlist[0].size == 0)
		{
          for(i=0; i < wrk->fdl.hintlistV_num; i++)
		  {
            if(attr->xsize >= Vhintlist[i].size)
			{
              wrk->fdl.weight_modeV = i;
			  i++;	// for the next loop
              break;
			}
		  }
		  // Added_by_Jacky: for multi removed strokes of the same size
		  for(;i<wrk->fdl.hintlistV_num;i++){
			if(attr->xsize == Vhintlist[i].size){
				wrk->fdl.weight_modeV++;
			}else{
				break;
			}
		  }
		}
	    // Use all removed strokes.
	    if((FDL_STROKE_HINT_DISABLE==wrk->fdl.weight_modeV) &&
		  attr->xsize<=Vhintlist[wrk->fdl.hintlistV_num-1].size){
			wrk->fdl.weight_modeV = wrk->fdl.hintlistV_num-1;
		}
	  }
    }

}// end block
#endif
#endif	// ENABLE_ADV_HINTING

	/* Draw font */
	if(wrk->datacnt> 0)
	{
		if(wrk->attr.f_edge == DCW_EDGE_OUTLINE)   /* Outline Style */
		{
			/* Draw Bold */
			savecnt = wrk->datacnt;
			saveofs = wrk->dataofs;
			wrk->fdl.f_edge = FDL_RASTER_BOLD;
			ret = FD_DoDraw(wrk, NULL, 0, FDL_MODE_RASTER2);
			if(ret == DCW_SUCCESS)
				ret = Do_DrawBitmap(wrk, &wrk->fdl);				// Jacky_20110509
			
			/* Clear Normal */
			if(ret == DCW_SUCCESS)
			{
				wrk->fdl.path_num = 0;					// Jacky_20110509
				wrk->datacnt = savecnt;
				wrk->dataofs = saveofs;
				wrk->fdl.f_edge = FDL_RASTER_CLEAR;
				ret = FD_DoDraw(wrk, NULL, 0, FDL_MODE_RASTER2);
				if(ret == DCW_SUCCESS)
					ret = Do_DrawBitmap(wrk, &wrk->fdl);			// Jacky_20110509
			}
		} else /* Other Style (Normal, Bold ... ) */
		{
			switch(wrk->attr.f_edge)
			{
				case DCW_EDGE_NORMAL:
					wrk->fdl.f_edge = FDL_RASTER_DRAW;
					break;

				case DCW_EDGE_BOLD:
					wrk->fdl.f_edge = FDL_RASTER_BOLD;
					break;

				case DCW_EDGE_BOLD_RIGHT:
					if(!wrk->fdl.rot)
						wrk->fdl.f_edge = FDL_RASTER_RIGHT;
					else
						wrk->fdl.f_edge	= FDL_RASTER_UP;
					break;

				case DCW_EDGE_BOLD_DOWN:
					if(!wrk->fdl.rot)
						wrk->fdl.f_edge = FDL_RASTER_DOWN;
					else
						wrk->fdl.f_edge	= FDL_RASTER_RIGHT;
					break;

				case DCW_EDGE_BOLD_RIGHT_DOWN:
					if(!wrk->fdl.rot)
						wrk->fdl.f_edge = FDL_RASTER_RIGHT_DOWN;
					else
						wrk->fdl.f_edge	= FDL_RASTER_RIGHT_UP;
					break;
			}
			ret = FD_DoDraw(wrk, NULL, 0, FDL_MODE_RASTER2);
			if(ret == DCW_SUCCESS)
				ret = Do_DrawBitmap(wrk, &wrk->fdl);
		}
	} else
		ret	= DCW_SUCCESS;

	/* Draw gradation font */
	if(wrk->attr.grade != DCW_MODE_MONOCHROME && ret == DCW_SUCCESS)
	{
		// 20110804: Jacky modified for using the font rect efficiently.
		DT32_int w, h;		// the originally required width & height.
		// get fontbox first.
		CalculateFontBoxforGray(wrk);
		w = raster->xbyte;
		if(wrk->fdl.fontbox.top <= wrk->fdl.fontbox.bottom){
			if(wrk->fdl.fontbox.top >= 0){	// so that wrk->fdl.fontbox.bottom > 0
				h = wrk->fdl.fontbox.bottom + 1;
			}else{							// wrk->fdl.fontbox.top < 0, no matter wrk->fdl.fontbox.bottom >=< 0... 
				h = wrk->fdl.fontbox.bottom - wrk->fdl.fontbox.top + 1;
			}
		}else{
			h = 0;
		}
		if(wrk->fdl.fontbox.left < 0){
			h += 1;		// the extrah needs in Digitype_std.c ras_getCharbmp()
		}
		// check if it needs to modify bmpw & xbyte
		if( w*h > gDT_TEMP_BUFFER_SIZE){
			if(wrk->fdl.fontbox.left <= wrk->fdl.fontbox.right){
				if(wrk->fdl.fontbox.left >= 0){
					wrk->fdl.bmpw = raster->xbyte = wrk->fdl.fontbox.right + 1;
				}else{
					wrk->fdl.bmpw = raster->xbyte = wrk->fdl.fontbox.right - wrk->fdl.fontbox.left + 1;
				}
			}
		}
	
		// check if memory is enough for fontbox
		if(raster->xbyte * h > gDT_TEMP_BUFFER_SIZE){
			ret = DCW_NOT_ENOUGH_FONTBOXMEM;
		}else{
			// gradation each line
			DrawGradationNoFontBox(wrk);
		}
		
//		DrawGradation(wrk);
	}

	/* Restore Rotate Font Size */
	if(wrk->fdl.rot)
	{
		temp = wrk->fdl.xsize;
		wrk->fdl.xsize = wrk->fdl.ysize;
		wrk->fdl.ysize = temp;
	}

	/* Return Font Body Rect */
	if(wrk->fdl.fontbox.left <= wrk->fdl.fontbox.right)
	{
		raster->x0 = wrk->fdl.fontbox.left;
		raster->y0 = wrk->fdl.fontbox.top;
		raster->xs = wrk->fdl.fontbox.right - wrk->fdl.fontbox.left + 1;
		raster->ys = wrk->fdl.fontbox.bottom - wrk->fdl.fontbox.top + 1;
	} else
	{
		raster->x0 = 0;
		raster->y0 = 0;
		raster->xs = 0;
		raster->ys = 0;
	}

	/* Return used memory size */
	switch(wrk->attr.grade)
	{
		case DCW_MODE_MONOCHROME:
			raster->MemSize = sizeof(DcwWrk);
			raster->GradMemUsed = 0;
			break;

		case DCW_MODE_GRAY16:
		case DCW_MODE_GRAY256:
			raster->MemSize = sizeof(DcwWrk) + FG_UsedMemSize(&wrk->gdata);
#ifdef DCW_ASSIGN_GRADATION_MEM
			raster->GradMemUsed = FG_UsedMemSize(&wrk->gdata);
#endif
			break;
	}

#ifdef DT_DEBUG
//  fclose(wrk->fp);
//  wrk->fp = NULL;
#endif

	return ret;
}
/*---------------------------------------------------------------------------*/
DT32_int DCW_GetAw(DCW_AttrData *attr, DT32_long fontidx)
{
	pDcwWrk wrk = (pDcwWrk)attr->WkMem;
	DT16_short x0, aw, y0, ah, wid;
	DT32_int ret, errx0;

DBG_MSG_SHOW_FUNC_NAME();

//#ifdef DCW_ENABLE_MODIFYATTR_WHEN_RASTER
//	////// Now fontsize and some attributes can be decided after DCW_Create(), but not fontdata changed. //////
//	////// Callers need to guarantee the correctness of the attribute values, ex: xsize, ysize, f_edge.. //////
//	if(wrk->attr.fontdata != wrk->fd)
//		return DCW_BAD_FONTDATA;
//	if(	wrk->fdl.grade != wrk->attr.grade)
//		return DCW_INVALID_GRADE;
//
//	/* Copy Attribute */
//	wrk->attr = *attr;
//
//	/* Rasterizer Attribute *//* Not Required. */
////	dots = GrayDots[wrk->attr.grade];
////	wrk->fdl.xsize  = wrk->attr.xsize * dots;
////	wrk->fdl.ysize  = wrk->attr.ysize * dots;
////	wrk->fdl.w_edge = (wrk->attr.f_edge!=DCW_EDGE_NORMAL) ? wrk->attr.w_edge * dots : 0;
////	wrk->fdl.italic = wrk->attr.italic * dots;
////	wrk->fdl.shiftx = 0;
////	wrk->fdl.shifty = 0;
//
//	// Once gcolor is changed, DcwShaperVG will guarantee re-call DCW_Create() first, 
//	// so no need to reset the gcolor, comment it here.
////	if(wrk->attr.grade == DCW_MODE_GRAY16)
////	{
////		for(i=0; i<DCW_MAXGRAD+1; i++)
////			wrk->fdl.gcolor[i] = attr->gcolor[i];
////	}
//	////// End of the re-modifing attributes.															 //////
//#endif

	wrk->fdl.wrk = wrk;

	ret = ReSetDcwWrk(wrk, attr, fontidx, DCW_OPT_RESETWRK_FOR_RASTER);
	if(DCW_SUCCESS != ret)
		return ret;

	/* Load font data */
	if(FD_LoadFontData(wrk, fontidx, &x0, &aw, &y0, &ah))
	{
		if(!wrk->attr.vert)
		{	/* Horz. Writing */
			if(x0 < 0){
				errx0 = (((DT32_long)x0 * wrk->attr.xsize) / 1000);
				aw += (x0 - errx0*1000 / wrk->attr.xsize);
			}

			wid = (DT16_short) DCW_CALC_AW_AH(aw,wrk->attr.xsize);

//			wid = (DT16_short)(((DT32_long)aw * attr->xsize + 999) / 1000);   // DLHsieh 2011-03-28
//			if(aw == 0)
//				wid = (DT16_short)attr->xsize;
//			else{
//				//wid	= (DT16_short)(((DT32_long)aw * attr->xsize + /*999*/ 500) / 1000);	//Modified_By_Jacky_20101210: 999=>500
//				wid	= (DT16_short) DCW_CALC_AW_AH(aw,attr->xsize);
//			}

			if(wid > 0){
				switch(wrk->attr.f_edge)
				{
					case DCW_EDGE_BOLD:
					case DCW_EDGE_OUTLINE:
						wid += (DT16_short)(wrk->attr.w_edge * 2);
						break;

					case DCW_EDGE_BOLD_RIGHT:
					case DCW_EDGE_BOLD_RIGHT_DOWN:
						wid += (DT16_short)wrk->attr.w_edge;
						break;
				}
			}
		} else
		{ /* Vert. Writing */
			if(!wrk->fdl.rot)
			{  /* Normal */
				wid = (DT16_short) DCW_CALC_AW_AH(ah,wrk->attr.ysize);
				//wid = (DT16_short)(((DT32_long)ah * attr->ysize + 999) / 1000);   // DLHsieh 2011-03-28
//				if(ah == 0)
//					wid = (DT16_short)attr->ysize;
//				else
//					wid	= (DT16_short)(((DT32_long)ah * attr->ysize + 999) / 1000);
			} else
			{ /* Rotate */
				wid = (DT16_short) DCW_CALC_AW_AH(aw,wrk->attr.ysize);
				//wid = (DT16_short)(((DT32_long)aw * attr->ysize + 999) / 1000);   // DLHsieh 2011-03-28
//				if(aw == 0)
//					wid = (DT16_short)attr->ysize;
//				else
//					wid	= (DT16_short)(((DT32_long)aw * attr->ysize + 999) / 1000);
			}

			if(wid > 0){
				switch(wrk->attr.f_edge)
				{
					case DCW_EDGE_BOLD:
					case DCW_EDGE_OUTLINE:
						wid += (DT16_short)(wrk->attr.w_edge * 2);
						break;

					case DCW_EDGE_BOLD_DOWN:
					case DCW_EDGE_BOLD_RIGHT_DOWN:
						wid += (DT16_short)wrk->attr.w_edge;
						break;
				}
			}
		}
	} else{
		//ret = Back_ReCreate(attr, ori_szx, ori_szy, ori_feg, ori_itl, bRtoChar);	//Not check the return value
		return DCW_CODE_NOT_EXIST;	//wid	= 0;
	}

	return wid;
}
/*---------------------------------------------------------------------------*/
DT32_int DCW_GetFontInfo(DT8_char *fontdata, DCW_FontInfo *info)
{
	DT8_BYTE *p;
	DT16_WORD b1, b2;
	DT32_long l1, l2, l3, l4, pos;

DBG_MSG_SHOW_FUNC_NAME();

	p = (DT8_BYTE*)(fontdata + FD_FONCNT);
	b1 = *p++;
	b2 = *p;
	info->fontcnt = b1 + (b2 << 8);

	if(info->fontcnt == 0)
	{
		p = (DT8_BYTE*)(fontdata + FD_FONTAB);
		l1 = *p++;
		l2 = *p++;
		l3 = *p++;
		l4 = *p;
		pos = l1 + (l2 << 8) + (l3 << 16) + (l4 << 24);

		p = (DT8_BYTE*)(fontdata + pos);
		l1 = *p++;
		l2 = *p++;
		l3 = *p++;
		l4 = *p;
		info->fontcnt = l1 + (l2 << 8) + (l3 << 16) + (l4 << 24);
	}

	/* stroke number */
	p = (DT8_BYTE*)(fontdata + FD_STRCNT);
	b1 = *p++;
	b2 = *p;
	info->strcnt = b1 + (b2 << 8);

	/* Codes */
	p = (DT8_BYTE*)(fontdata + FD_CTMODE);
	b1 = *p++;
	b2 = *p;
	info->ctmode = b1 + (b2 << 8);

	p = (DT8_BYTE*)(fontdata + FD_VERSION);
	b1 = *p++;
	b2 = *p;
	info->version = b1 + (b2 << 8);

	return 1;
}
/*---------------------------------------------------------------------------*/
DT_void DrawUnderline(pDcwWrk wrk, DT32_int aw)
{
	DT32_int dots, xl, xr, yt, yb, y;

DBG_MSG_SHOW_FUNC_NAME();

	/* Calculate Advance Width */
	aw = (DT16_short) DCW_CALC_AW_AH(aw,wrk->attr.xsize);
//	aw = (DT16_short)(((DT32_long)aw * wrk->attr.xsize + 999) / 1000);  // DLHsieh 2011-03-28
//	if(aw == 0){
//		aw = (DT16_short)wrk->attr.xsize;
//	}else{
//		//aw = (DT16_short)(((DT32_long)aw * wrk->attr.xsize + 999) / 1000);	//Marked_By_Jacky_20101210: 999=>500
//		aw	= (DT16_short) DCW_CALC_AW_AH(aw,wrk->attr.xsize);
//	}
	dots = GrayDots[wrk->attr.grade];

	/* Calculate Underline Length */
	xl = 0;
	xr = xl + (aw + wrk->attr.e_underline);
	switch(wrk->attr.f_edge)
	{
		case DCW_EDGE_BOLD:
		case DCW_EDGE_OUTLINE:
			xl -= wrk->attr.w_edge;
			xr += wrk->attr.w_edge;
			break;

		case DCW_EDGE_BOLD_RIGHT:
		case DCW_EDGE_BOLD_RIGHT_DOWN:
			xr += wrk->attr.w_edge;
			break;
	}
	xl = xl * dots;
	xr = xr * dots - 1;

	/* Calculate Underline Position / Width */
	yb = wrk->attr.ysize - wrk->attr.p_underline - 1;
	yt = yb - wrk->attr.w_underline + 1;
	yt = yt * dots;
	yb = (yb + 1) * dots - 1;

	/* Draw Underline */
	if(wrk->attr.grade)
	{
		for(y = yt; y <= yb; y++)
			if(!FG_Add(&wrk->gdata, y, xl, xr))
				return;
	} else
	{
		for(y = yt; y <= yb; y++)
			DoDrawLine(&wrk->fdl, y, xl, xr);
	}
}
/*---------------------------------------------------------------------------*/
DT_void DrawUnderlineVertRot(pDcwWrk wrk, DT32_int aw)
{
	DT32_int dots, xl, xr, yt, yb, y;

DBG_MSG_SHOW_FUNC_NAME();

	/* Calculate Advance Width */
	aw = (DT16_short) DCW_CALC_AW_AH(aw,wrk->attr.ysize);
//	aw = (DT16_short)(((DT32_long)aw * wrk->attr.ysize + 999) / 1000);  // DLHsieh 2011-03-28
//	if(aw == 0)
//		aw = (DT16_short)wrk->attr.ysize;
//	else
//		aw = (DT16_short)(((DT32_long)aw * wrk->attr.ysize + 999) / 1000);
	dots = GrayDots[wrk->attr.grade];

	/* Calculate Underline Length */
	xl = 0;
	xr = xl + (aw + wrk->attr.e_underline);
	switch(wrk->attr.f_edge)
	{
		case DCW_EDGE_BOLD:
		case DCW_EDGE_OUTLINE:
			xl -= wrk->attr.w_edge;
			xr += wrk->attr.w_edge;
			break;

		case DCW_EDGE_BOLD_DOWN:
		case DCW_EDGE_BOLD_RIGHT_DOWN:
			xr += wrk->attr.w_edge;
			break;
	}
	xl = xl * dots;
	xr = xr * dots - 1;

	/* Calculate Underline Position / Width */
	yt = wrk->attr.p_underline;
	yb = yt + wrk->attr.w_underline - 1;
	yt = yt * dots;
	yb = (yb + 1) * dots - 1;

	/* Draw Underline */
	if(wrk->attr.grade)
	{
		for(y = yt; y <= yb; y++)
			if(!FG_Add(&wrk->gdata, y, xl, xr))
				return;
	} else
	{
		for(y = yt; y <= yb; y++)
			DoDrawLine(&wrk->fdl, y, xl, xr);
	}
}
/*---------------------------------------------------------------------------*/
DT_void DrawUnderlineVert(pDcwWrk wrk, DT32_int ah)
{
	DT32_int dots, xl, xr, yt, yb, y;

DBG_MSG_SHOW_FUNC_NAME();

	/* Calculate Advance Width */
	ah = (DT16_short) DCW_CALC_AW_AH(ah,wrk->attr.ysize);
//	ah = (DT16_short)(((DT32_long)ah * wrk->attr.ysize + 999) / 1000);  // DLHsieh 2011-03-28
//	if(ah == 0)
//		ah = (DT16_short)wrk->attr.ysize;
//	else
//		ah = (DT16_short)(((DT32_long)ah * wrk->attr.ysize + 999) / 1000);
	dots = GrayDots[wrk->attr.grade];

	/* Calculate Underline Length */
	yt = 0;
	yb = yt + (ah + wrk->attr.e_underline);
	switch(wrk->attr.f_edge)
	{
		case DCW_EDGE_BOLD:
		case DCW_EDGE_OUTLINE:
			yt -= wrk->attr.w_edge;
			yb += wrk->attr.w_edge;
			break;

		case DCW_EDGE_BOLD_DOWN:
		case DCW_EDGE_BOLD_RIGHT_DOWN:
			yb += wrk->attr.w_edge;
			break;
	}
	yt = yt * dots;
	yb = yb * dots - 1;

	/* Calculate Underline Position / Width */
	xr = wrk->attr.xsize - wrk->attr.p_underline - 1;
	xl = xr - wrk->attr.w_underline + 1;
	xl = xl * dots;
	xr = (xr + 1) * dots - 1;

	/* Draw Underline */
	if(wrk->attr.grade)
	{
		for(y = yt; y <= yb; y++)
			if(!FG_Add(&wrk->gdata, y, xl, xr))
				return;
	} else
	{
		for(y = yt; y <= yb; y++)
			DoDrawLine(&wrk->fdl, y, xl, xr);
	}
}
/*---------------------------------------------------------------------------*/
DT_void GradationLine(pDcwWrk wrk, DT32_int y, DT32_int xl, DT32_int xr, DT32_int dots, DT32_int dots2, DT32_int maxval, DT32_int count, DT32_int redots, DT8_BYTE *p, DT8_BYTE *p0)
{
	DT32_int xl2, xr2, lcnt, rcnt, cnt, val, i;
//	DT8_BYTE *p0;

DBG_MSG_SHOW_FUNC_NAME();

//	y >>= dots2;
	xl2 = xl >> dots2;     lcnt = dots - (xl & redots);
	xr2 = xr >> dots2;     rcnt = ((xr & redots)==0) ? 0 : (xr & redots) + 1;		// Jacky_20110509
	cnt = xr2 - xl2;

//	p = (DT8_BYTE*)(wrk->fdl.bmp + y * wrk->fdl.bmpw + xl2);
//	p = (DT8_BYTE*)(wrk->fdl.bmp + (wrk->fdl.bmpw << dots2) + xl2);
	p = p + xl2;
#if 1
	if(cnt == 0)
	{
		val = (DT32_int)*p + (xr - xl + 1);
		*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
	}else
	{
		val = (DT32_int)*p + lcnt;
		*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
		p++;

//		if(count >= 1)
		{
			for(i=0; i < cnt-1; i++,p++)
			{
				val = (DT32_int)*p + dots;
				*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
			}// end for
		}//else
		{
//			DT_memset(p, dots, cnt-1);
		}// end if

		val = (DT32_int)*p + rcnt;
		if(p - p0 < wrk->fdl.bmpw)						// Jacky_20110509
			*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
	}// end if
#endif
}// end GradationLine

/*---------------------------------------------------------------------------*/
DT_void GradationLineVert(pDcwWrk wrk, DT32_int x, DT32_int yt, DT32_int yb, DT32_int dots, DT32_int dots2, DT32_int maxval)
{
	DT32_int yt2, yb2, tcnt, bcnt, cnt, val, i;
	DT8_BYTE *p;

DBG_MSG_SHOW_FUNC_NAME();

	x >>= dots2;
	yt2 = yt >> dots2;     tcnt = dots - (yt - ((yt >> dots2) << dots2));
	yb2 = yb >> dots2;     bcnt = (yb - ((yb >> dots2) << dots2)) + 1;
	cnt = yb2 - yt2;

	p = (DT8_BYTE*)(wrk->fdl.bmp + yt2 * wrk->fdl.bmpw + x);

	if(cnt == 0)
	{
		val = (DT32_int)*p + (yb - yt + 1);
		*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
	} else
	{
		val = (DT32_int)*p + tcnt;
		*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
		p += wrk->fdl.bmpw;

		for(i=0; i<cnt-1; i++,p+=wrk->fdl.bmpw)
		{
			val = (DT32_int)*p + dots;
			*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
		}

		val = (DT32_int)*p + bcnt;
		*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
	}
}
/*---------------------------------------------------------------------------*/
DT_void QuickGradationLineEnd(pDcwWrk wrk, DT32_int y, DT32_int xl, DT32_int xr, DT32_int dots, DT32_int dots2, DT32_int maxval)
{

}// end QuickGradationLineEnd

DT_void QuickGradationLine(pDcwWrk wrk, DT32_int y, DT32_int xl, DT32_int xr, DT32_int dots, DT32_int dots2, DT32_int maxval)
{
	DT32_int xl2, xr2, lcnt, rcnt, cnt, val, i;
	DT8_BYTE *p;

DBG_MSG_SHOW_FUNC_NAME();

	y >>= dots2;
	xl2 = xl >> dots2;     lcnt = dots - (xl - ((xl >> dots2) << dots2));
	xr2 = xr >> dots2;     rcnt = (xr - ((xr >> dots2) << dots2)) + 1;
	cnt = xr2 - xl2;

	p = (DT8_BYTE*)(wrk->fdl.bmp + y * wrk->fdl.bmpw + xl2);

	if(cnt == 0)
	{
		val = (DT32_int)*p + (xr - xl + 1);
		*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
	}else
	{
		val = (DT32_int)*p + lcnt;
		*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
		p++;

		for(i=0; i < cnt-1; i++,p++)
		{
			val = (DT32_int)*p + dots;
			*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
		}// end for

		val = (DT32_int)*p + rcnt;
		*p = (DT8_BYTE)((val <= maxval) ? val : maxval);
	}// end if

}// end QuickGradationLine


DT_void DrawGradation(pDcwWrk wrk)
{
	DT32_int gray16, dots, dots2, redots, maxval;
	DT32_int yt, yb, y, xorg, yorg, xl, xr, x;//, idx;
	DT32_int yt2, yb2;
	pFdlGradeData gdata = &wrk->gdata;
	pFGXPair pair;
	//DT8_BYTE *p;
	//TFdlGradeData gdata2;
	//DT8_char *mygmem;

DBG_MSG_SHOW_FUNC_NAME();

	/* Get line range */
	FG_GetLineRange(gdata, &yt, &yb);

	//mygmem = DT_malloc(0x8000);
	//FG_Initial(&gdata2, 0, 511, mygmem, 0x8000, wrk);

	/* No Scan Line => return */
	if(yt > yb)
	{
		wrk->fdl.fontbox.left   = 32767;
		wrk->fdl.fontbox.top    = 32767;
		wrk->fdl.fontbox.right  = 0;
		wrk->fdl.fontbox.bottom = 0;
		return;
	}// end if

	/* Bitmap origin */
	xorg = wrk->fdl.xorg;
	yorg = wrk->fdl.yorg;

	/* Get Gray flag */
	gray16 = wrk->attr.grade==DCW_MODE_GRAY16;
	if(gray16)
	{
		dots = 4;
		dots2 = 2;
		redots = 4-1;
		maxval = 15;
	}else
	{
		dots = 16;
		dots2 = 4;
		redots = 16-1;
		maxval = 255;
	}// end if

	/* Intital font body */
	if(!wrk->fdl.rot)
	{
		wrk->fdl.fontbox.left   = 32767;
		wrk->fdl.fontbox.right  = 0;
		wrk->fdl.fontbox.top    = (yt + yorg) >> dots2;
		wrk->fdl.fontbox.bottom = (yb + yorg) >> dots2;
	} else
	{
		wrk->fdl.fontbox.top    = 32767;
		wrk->fdl.fontbox.bottom = 0;
		wrk->fdl.fontbox.left   = (wrk->fdl.ysize - yb + xorg) >> dots2;
		wrk->fdl.fontbox.right  = (wrk->fdl.ysize - yt + xorg) >> dots2;
	}// end if

	// Calculate Gradation level
	if(!wrk->fdl.rot)
	{
		DT8_BYTE *p = (DT8_BYTE*)wrk->fdl.bmp + (yt+yorg) * wrk->fdl.bmpw;
		for(y = yt; y <= yb; y++)
		{
			DT32_int targety;
			DT32_int k;
			DT32_int count;
			pair = FG_GetLine(gdata, y);
			if(pair != NULL)
			{
				DT8_BYTE *p0;
				targety = (y+yorg) >> dots2;
				p0 = p = (DT8_BYTE*)(wrk->fdl.bmp + targety * wrk->fdl.bmpw);
				k = 0;
				count = FG_GetLineNum(gdata, pair);
				while(1)
				{	// Normal
					xl = xorg + pair->xl;
					xr = xorg + pair->xr;
					GradationLine(wrk, targety, xl, xr, dots, dots2, maxval, count, redots, p, p0);	// Jacky_20110509, p will be changed, p0 won't.

					if(xl < wrk->fdl.fontbox.left)
						wrk->fdl.fontbox.left = xl;
					if(xr > wrk->fdl.fontbox.right)
						wrk->fdl.fontbox.right = xr;

					if( ++k < count )
						pair = FG_GetNext(gdata, pair);
					else break;
				}// end for
			}// end if

		}// end for
		wrk->fdl.fontbox.left  >>= dots2;
		wrk->fdl.fontbox.right >>= dots2;
	}else
	{
		for(y = yt; y <= yb; y++)
		{
			pair = FG_GetLine(gdata, y);
			while(pair != NULL)
			{	// Rotate Font for Vertical Writing
				x = xorg + (wrk->fdl.ysize - y - 1);
				yt2 = yorg + pair->xl;
				yb2 = yorg + pair->xr;
				GradationLineVert(wrk, x, yt2, yb2, dots, dots2, maxval);

				if(yt2 < wrk->fdl.fontbox.top)
					wrk->fdl.fontbox.top = yt2;
				if(yb2 > wrk->fdl.fontbox.bottom)
					wrk->fdl.fontbox.bottom = yb2;
	
				pair = FG_GetNext(gdata, pair);
			}// end while
		}// end for

		wrk->fdl.fontbox.top 	>>= dots2;
		wrk->fdl.fontbox.bottom >>= dots2;
	}// end if

	/* Lookup Gray16 Palette  */
	// 20110803: Marked by Jacky because the palette is always the same(0x0-0xF), mapping palette is not required.
	// There is also a bug in the palette mapping, because it might access out of the range of wrk->fdl.bmp.
//	if(gray16)
//	{
//		DT8_BYTE *p;
//		DT32_int idx;
//		for(y = wrk->fdl.fontbox.top; y <= wrk->fdl.fontbox.bottom; y++)
//		{
//			p = (DT8_BYTE*)(wrk->fdl.bmp + y * wrk->fdl.bmpw);
//			for(x=0; x<wrk->fdl.bmpw; x++,p++)
//			{
//				idx = *p;
//				*p = wrk->fdl.gcolor[idx+1];
//			}
//		}
//	}
}

DT_void CalculateFontBoxforGray(pDcwWrk wrk)
{
	DT32_int gray16, dots, dots2;
	DT32_int yt, yb, y, xorg, yorg, xl, xr;
	DT32_int yt2, yb2;
	pFdlGradeData gdata = &wrk->gdata;
	pFGXPair pair;

DBG_MSG_SHOW_FUNC_NAME();

	/* Get line range */
	FG_GetLineRange(gdata, &yt, &yb);

	/* No Scan Line => return */
	if(yt > yb)
	{
		wrk->fdl.fontbox.left   = 32767;
		wrk->fdl.fontbox.top    = 32767;
		wrk->fdl.fontbox.right  = 0;
		wrk->fdl.fontbox.bottom = 0;
		return;
	}// end if

	/* Bitmap origin */
	xorg = wrk->fdl.xorg;
	yorg = wrk->fdl.yorg;

	/* Get Gray flag */
	gray16 = wrk->attr.grade==DCW_MODE_GRAY16;
	if(gray16)
	{
		dots = 4;
		dots2 = 2;
	}else
	{
		dots = 16;
		dots2 = 4;
	}// end if

	/* Intital font body */
	if(!wrk->fdl.rot)
	{
		wrk->fdl.fontbox.left   = 32767;
		wrk->fdl.fontbox.right  = 0;
		wrk->fdl.fontbox.top    = (yt + yorg) >> dots2;
		wrk->fdl.fontbox.bottom = (yb + yorg) >> dots2;
	} else
	{
		wrk->fdl.fontbox.top    = 32767;
		wrk->fdl.fontbox.bottom = 0;
		wrk->fdl.fontbox.left   = (wrk->fdl.ysize - yb + xorg) >> dots2;
		wrk->fdl.fontbox.right  = (wrk->fdl.ysize - yt + xorg) >> dots2;
	}// end if

	// Calculate Gradation level
	if(!wrk->fdl.rot)
	{
		for(y = yt; y <= yb; y++)
		{
			DT32_int k;
			DT32_int count;
			pair = FG_GetLine(gdata, y);
			if(pair != NULL)
			{
				k = 0;
				count = FG_GetLineNum(gdata, pair);
				while(1)
				{	// Normal
					xl = xorg + pair->xl;
					xr = xorg + pair->xr;

					if(xl < wrk->fdl.fontbox.left)
						wrk->fdl.fontbox.left = xl;
					if(xr > wrk->fdl.fontbox.right)
						wrk->fdl.fontbox.right = xr;

					if( ++k < count )
						pair = FG_GetNext(gdata, pair);
					else break;
				}// end for
			}// end if

		}// end for
		wrk->fdl.fontbox.left  >>= dots2;
		wrk->fdl.fontbox.right >>= dots2;
	}else
	{
		for(y = yt; y <= yb; y++)
		{
			pair = FG_GetLine(gdata, y);
			while(pair != NULL)
			{	// Rotate Font for Vertical Writing
				yt2 = yorg + pair->xl;
				yb2 = yorg + pair->xr;

				if(yt2 < wrk->fdl.fontbox.top)
					wrk->fdl.fontbox.top = yt2;
				if(yb2 > wrk->fdl.fontbox.bottom)
					wrk->fdl.fontbox.bottom = yb2;
	
				pair = FG_GetNext(gdata, pair);
			}// end while
		}// end for

		wrk->fdl.fontbox.top 	>>= dots2;
		wrk->fdl.fontbox.bottom >>= dots2;
	}// end if
}

DT_void DrawGradationNoFontBox(pDcwWrk wrk)
{
	DT32_int gray16, dots, dots2, redots, maxval;
	DT32_int yt, yb, y, xorg, yorg, xl, xr, x;//, idx;
	DT32_int yt2, yb2;
	pFdlGradeData gdata = &wrk->gdata;
	pFGXPair pair;
	//DT8_BYTE *p;
	//TFdlGradeData gdata2;
	//DT8_char *mygmem;

DBG_MSG_SHOW_FUNC_NAME();

	/* Get line range */
	FG_GetLineRange(gdata, &yt, &yb);

	//mygmem = DT_malloc(0x8000);
	//FG_Initial(&gdata2, 0, 511, mygmem, 0x8000, wrk);

	/* No Scan Line => return */
	if(yt > yb)
	{
//		wrk->fdl.fontbox.left   = 32767;
//		wrk->fdl.fontbox.top    = 32767;
//		wrk->fdl.fontbox.right  = 0;
//		wrk->fdl.fontbox.bottom = 0;
		return;
	}// end if

	/* Bitmap origin */
	xorg = wrk->fdl.xorg;
	yorg = wrk->fdl.yorg;

	/* Get Gray flag */
	gray16 = wrk->attr.grade==DCW_MODE_GRAY16;
	if(gray16)
	{
		dots = 4;
		dots2 = 2;
		redots = 4-1;
		maxval = 15;
	}else
	{
		dots = 16;
		dots2 = 4;
		redots = 16-1;
		maxval = 255;
	}// end if

	/* Intital font body */
//	if(!wrk->fdl.rot)
//	{
//		wrk->fdl.fontbox.left   = 32767;
//		wrk->fdl.fontbox.right  = 0;
//		wrk->fdl.fontbox.top    = (yt + yorg) >> dots2;
//		wrk->fdl.fontbox.bottom = (yb + yorg) >> dots2;
//	} else
//	{
//		wrk->fdl.fontbox.top    = 32767;
//		wrk->fdl.fontbox.bottom = 0;
//		wrk->fdl.fontbox.left   = (wrk->fdl.ysize - yb + xorg) >> dots2;
//		wrk->fdl.fontbox.right  = (wrk->fdl.ysize - yt + xorg) >> dots2;
//	}// end if

	// Calculate Gradation level
	if(!wrk->fdl.rot)
	{
		DT8_BYTE *p = (DT8_BYTE*)wrk->fdl.bmp + (yt+yorg) * wrk->fdl.bmpw;
		for(y = yt; y <= yb; y++)
		{
			DT32_int targety;
			DT32_int k;
			DT32_int count;
			pair = FG_GetLine(gdata, y);
			if(pair != NULL)
			{
				DT8_BYTE *p0;
				targety = (y+yorg) >> dots2;
				p0 = p = (DT8_BYTE*)(wrk->fdl.bmp + targety * wrk->fdl.bmpw);
				k = 0;
				count = FG_GetLineNum(gdata, pair);
				while(1)
				{	// Normal
					xl = xorg + pair->xl;
					xr = xorg + pair->xr;
					GradationLine(wrk, targety, xl, xr, dots, dots2, maxval, count, redots, p, p0);	// Jacky_20110509, p will be changed, p0 won't.

//					if(xl < wrk->fdl.fontbox.left)
//						wrk->fdl.fontbox.left = xl;
//					if(xr > wrk->fdl.fontbox.right)
//						wrk->fdl.fontbox.right = xr;

					if( ++k < count )
						pair = FG_GetNext(gdata, pair);
					else break;
				}// end for
			}// end if

		}// end for
//		wrk->fdl.fontbox.left  >>= dots2;
//		wrk->fdl.fontbox.right >>= dots2;
	}else
	{
		for(y = yt; y <= yb; y++)
		{
			pair = FG_GetLine(gdata, y);
			while(pair != NULL)
			{	// Rotate Font for Vertical Writing
				x = xorg + (wrk->fdl.ysize - y - 1);
				yt2 = yorg + pair->xl;
				yb2 = yorg + pair->xr;
				GradationLineVert(wrk, x, yt2, yb2, dots, dots2, maxval);

//				if(yt2 < wrk->fdl.fontbox.top)
//					wrk->fdl.fontbox.top = yt2;
//				if(yb2 > wrk->fdl.fontbox.bottom)
//					wrk->fdl.fontbox.bottom = yb2;
	
				pair = FG_GetNext(gdata, pair);
			}// end while
		}// end for

//		wrk->fdl.fontbox.top 	>>= dots2;
//		wrk->fdl.fontbox.bottom >>= dots2;
	}// end if

	/* Lookup Gray16 Palette  */
	// 20110803: Marked by Jacky because the palette is always the same(0x0-0xF), mapping palette is not required.
	// There is also a bug in the palette mapping, because it might access out of the range of wrk->fdl.bmp.
//	if(gray16)
//	{
//		DT8_BYTE *p;
//		DT32_int idx;
//		for(y = wrk->fdl.fontbox.top; y <= wrk->fdl.fontbox.bottom; y++)
//		{
//			p = (DT8_BYTE*)(wrk->fdl.bmp + y * wrk->fdl.bmpw);
//			for(x=0; x<wrk->fdl.bmpw; x++,p++)
//			{
//				idx = *p;
//				*p = wrk->fdl.gcolor[idx+1];
//			}
//		}
//	}
}

/*---------------------------------------------------------------------------*/
DT32_long FD_ReadInt2(pDcwWrk wrk, DT32_long ofs)
{
	DT8_BYTE *p;
	DT32_long val;

DBG_MSG_SHOW_FUNC_NAME();

	p = wrk->fd + ofs;
	
	if(0==gDT_Endianness)	
		if(((DT32_ulong)p & 0x01) == 0)
			return (DT32_long)*((DT16_ushort*)(wrk->fd + ofs));

	
	p += 1;	//2-1;

	val = *p--;

	val <<= 8;
	val |= *p;

	return val;
}

/*---------------------------------------------------------------------------*/
DT32_long FD_ReadInt4(pDcwWrk wrk, DT32_long ofs)
{
	DT8_BYTE *p;
	DT32_long val;

DBG_MSG_SHOW_FUNC_NAME();

	p = wrk->fd + ofs;
	if(0 == gDT_Endianness)
		if(((DT32_ulong)p & 0x03) == 0)
			return *((DT32_long*)(wrk->fd + ofs));

	p += 3;	//4-1;

	val = *p--;

	val <<= 8;
	val |= *p;
	p--;
	
	val <<= 8;
	val |= *p;
	p--;

	val <<= 8;
	val |= *p;

	return val;
}

/*---------------------------------------------------------------------------*/
DT32_long FD_ReadInt(pDcwWrk wrk, DT32_long ofs, DT32_int size)
{
	DT8_BYTE *p;
	DT32_long val, b;
	DT32_int scnt, i;

DBG_MSG_SHOW_FUNC_NAME();

	p = wrk->fd + ofs;
	val = *p++;

	for(i=1,scnt=8; i<size; i++,p++,scnt+=8)
	{
		b = *p << scnt;
		val += b;
	}

	return val;
}

/*DT32_long FD_ReadInt(pDcwWrk wrk, DT32_long ofs, DT32_int size)
{
DBG_MSG_SHOW_FUNC_NAME();

	switch(size){
	case 1:
		return (DT32_long)(DT8_BYTE)wrk->fd[ofs];
	case 2:
		return FD_ReadIntByData2((DT8_char*)wrk->fd, ofs);
	case 4:
		return FD_ReadIntByData4((DT8_char*)wrk->fd, ofs);
	default:
		return FD_ReadIntByData((DT8_char*)wrk->fd, ofs, size);
	}
}
*/
/*---------------------------------------------------------------------------*/
//DT8_BYTE FD_ReadStrByte(pDcwWrk wrk)
//{
//	DT8_BYTE val = *((DT8_BYTE*)(wrk->fd + wrk->fdl.sdataofs));
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	wrk->fdl.sdataofs ++;
//	wrk->fdl.sdatacnt --;
//
//	return val;
//}
/*---------------------------------------------------------------------------*/
DT16_short FD_ReadStrShort(pDcwWrk wrk)
{
	DT8_BYTE *p = wrk->fd + wrk->fdl.sdataofs;
	DT16_WORD b1, b2;

DBG_MSG_SHOW_FUNC_NAME();

	b1 = *p++;
	b2 = *p;

	wrk->fdl.sdataofs += 2;
	wrk->fdl.sdatacnt -= 2;

	return(DT16_short)(b1 + (b2 << 8));
}
/*---------------------------------------------------------------------------*/
DT32_long FD_ReadFontData(pDcwWrk wrk, DT32_int size)
{
	DT32_int val;

DBG_MSG_SHOW_FUNC_NAME();

	if(wrk->inrad)
	{
		val = FD_ReadInt(wrk, wrk->rdataofs, size);

		wrk->rdataofs += size;
		wrk->rdatacnt -= size;
	} else
	{
		val = FD_ReadInt(wrk, wrk->dataofs, size);

		wrk->dataofs += size;
		wrk->datacnt -= size;
	}

	return val;
}
/*---------------------------------------------------------------------------*/
DT32_int FD_LoadStrokeData(pDcwWrk wrk, DT32_int strid, DT32_int *flag)
{
	DT32_long len, ofs, addr1, addr2;
	DT32_int  cnt, param;

DBG_MSG_SHOW_FUNC_NAME();

	if(strid < wrk->strcnt)
	{
		/* Read stroke position & size */
		len = (wrk->version == 0x102) ? 3 : 2;
		ofs = wrk->strtab + strid*len;
		addr1 = FD_ReadInt(wrk, ofs, len);
		addr2 = FD_ReadInt(wrk, ofs+len, len);
		cnt = addr2 - addr1;

		if(cnt > 0)
		{
			ofs = wrk->strofs + addr1;

			/* Read stroke parameter */
			param = FD_ReadInt1(wrk, ofs);
			wrk->fdl.relno = (param >> 4) & 0x0f;
			wrk->fdl.valno = param & 0x0f;

			*flag = FD_ReadInt1(wrk, ofs+1);

			/* stroke data */
			wrk->fdl.sdatacnt = cnt - 2;
			wrk->fdl.sdataofs = ofs + 2;

			return 1;
		}
	}

	return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int FD_LoadRadData(pDcwWrk wrk, DT32_int radid, TFDLRadParam *rad)
{
	DT32_long ofs, addr1, addr2;
	DT32_int  cnt, param;

DBG_MSG_SHOW_FUNC_NAME();

	if(radid < wrk->radcnt)
	{
		/* Read radical position & size */
		/* 2007-12-12 Radical : 3 Bytes Table */
		ofs = wrk->radtab + radid*3;
		addr1 = FD_ReadInt(wrk, ofs,   3);
		addr2 = FD_ReadInt(wrk, ofs+3, 3);
		cnt = addr2 - addr1;

		if(cnt > 0)
		{
			/* Read radical parameter */
			ofs = wrk->radofs + addr1;
			param = FD_READINTBYDATA4(wrk->fd, ofs);

			/* Setup radical parameter */
			rad->Id    = (DT16_short)radid;
			rad->srcx  = (DT16_short)(param & 0x0ff);
			rad->srcy  = (DT16_short)((param >> 8) & 0x0ff);
			rad->srcw  = (DT16_short)((param >> 16) & 0x0ff);
			rad->srch  = (DT16_short)((param >> 24) & 0x0ff);
			rad->destx = rad->srcx;
			rad->desty = rad->srcy;
			rad->destw = rad->srcw;
			rad->desth = rad->srch;
			rad->wid   = 128;

			/* Radical data */
			wrk->rdatacnt = cnt - 4;
			wrk->rdataofs = ofs + 4;

			return 1;
		}
	}

	return 0;
}
/*---------------------------------------------------------------------------*/
DT_void FD_SetPlane(pDcwWrk wrk, DT32_int plane)
{
	DT32_long start, ofs;

DBG_MSG_SHOW_FUNC_NAME();

	if(plane != wrk->plane)
	{
		wrk->plane = plane;

		/* Read Plane Table */
		ofs = wrk->planes + plane * 8;
		start = FD_READINTBYDATA4(wrk->fd, ofs);
		wrk->gstart = FD_READINTBYDATA4(wrk->fd, ofs+4);

		ofs = wrk->fontab + start;
		if(wrk->fonmap == 0)
		{ /* Read Segment Table */
			wrk->segno      = (DT16_ushort)FD_READINTBYDATA2(wrk->fd, ofs);
			wrk->segs       = ofs + 2;
		} else if(wrk->fonmap == 1)
		{	/* Read Page Table */
			wrk->pagebits   = (DT16_ushort)FD_READINTBYDATA2(wrk->fd, ofs);
			wrk->pageno     = (DT16_ushort)FD_READINTBYDATA2(wrk->fd, ofs+2);
			wrk->pages      = ofs + 4;

			wrk->pagemask = (1 << wrk->pagebits) - 1;
		}
	}
}
/*---------------------------------------------------------------------------*/
DT32_int FD_SearchCMap(pDcwWrk wrk, DT32_int fontidx, DT32_int *gidx)
{
	DT32_int base = wrk->segs;
	DT32_int cnt  = wrk->segno;
	DT32_int width = 6;
	DT32_int mid, probe, start, last;

DBG_MSG_SHOW_FUNC_NAME();

	while(cnt > 0)
	{
		mid = cnt >> 1;
		probe = base + mid * width;
		start = FD_READINTBYDATA2(wrk->fd, probe);
		last  = FD_READINTBYDATA2(wrk->fd, probe+2);

		if(fontidx >= start && fontidx <= last)
		{
			*gidx = wrk->gstart + FD_READINTBYDATA2(wrk->fd, probe+4) + (fontidx - start);
			return 1;
		} else if(fontidx < start)
			cnt = mid;
		else
		{
			base = probe + width;
			cnt -= mid + 1;
		}
	}

	return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int FD_SearchPage(pDcwWrk wrk, DT32_int fontidx, DT32_int *gidx)
{
	DT32_int pageidx = fontidx >> wrk->pagebits;
	DT32_int ofs = wrk->pages + pageidx * 2;
	DT32_int start = FD_READINTBYDATA2(wrk->fd, ofs);

DBG_MSG_SHOW_FUNC_NAME();

	if(start != 0xFFFF)
	{
		*gidx = wrk->gstart + start + (fontidx & wrk->pagemask);
		return 1;
	} else
		return 0;
}
/*---------------------------------------------------------------------------*/
#ifdef FDL_CONV_OLD_V_TO_NEW_HINTLIST
DT_void convhintlist(pDcwWrk wrk)
{
	DT32_int i, j, numh, numv;
	FDL_StrokeHint *Hhintlist, *Vhintlist;

	if(wrk->fdl.groupinfo.hintnum<=0){
		return;
	}
	//Get the number of remove strokes.
	numh = 0;	numv = 0;
	for(i=0; i < wrk->fdl.groupinfo.hintnum; i++)
	{
		if(wrk->fdl.groupinfo.hintlist[i].stroke & FDL_ALIGN_VSTROKE){
		  break;
		}else{
		  numh++;
		}
	}
	numv = wrk->fdl.groupinfo.hintnum - numh;

	// Because the bit FDL_REMOVE_STROKE_MIX_MODE is redefined, mixed the bit to hintlistH.
	// This loop can be removed if FontTool is ready for this definition.
	Hhintlist = wrk->fdl.groupinfo.hintlist;
	Vhintlist = wrk->fdl.groupinfo.hintlist + numh;
	if(numh > 0){
	  DT_memcpy(wrk->fdl.hintlist, wrk->fdl.groupinfo.hintlist, numh*sizeof(wrk->fdl.groupinfo.hintlist[0]));
	  wrk->fdl.groupinfo.hintnum = numh;
	  if(numv > 0){
		// convert the FDL_ALIGN_VSTROKE to FDL_REMOVE_STROKE_MIX_MODE.
		for(i=0;i<numv;i++){
			for(j=0;j<numh;j++){
				if( (Hhintlist[j].size == Vhintlist[i].size) &&
					((Hhintlist[j].stroke & ~FDL_ALIGN_MODE) == (Vhintlist[i].stroke & ~FDL_ALIGN_MODE)) ){
					wrk->fdl.hintlist[j].stroke |= FDL_REMOVE_STROKE_MIX_MODE;
				}
			}
		}
	  }
	  wrk->fdl.groupinfo.hintlist = wrk->fdl.hintlist;
	}
}
#endif
/*---------------------------------------------------------------------------*/
DT32_int FD_LoadFontData(pDcwWrk wrk, DT32_long fontidx, DT16_short *x0, DT16_short *aw, DT16_short *y0, DT16_short *ah)
{
	DT32_long ofs, addr1, addr2;
	DT32_int  flag, total, fcnt, fcnt2;
	DT32_int  vert = (wrk->attr.vert) && (fontidx>=256);
	DT32_int  plane, fidx2, gidx, cmap;
#ifndef FDL_ONLY_REMOVE_STROKE_NOHINTING
	DT32_long ofs2;               // DLHsieh
	DT32_int  pcnt, gcnt, scnt;   // DLHsieh
#endif // #ifdef FDL_ONLY_REMOVE_STROKE_NOHINTING

#ifdef FDL_EXTEND
	DT32_int subdata=0;
#endif

DBG_MSG_SHOW_FUNC_NAME();

	if(fontidx >= wrk->foncnt) return 0;

	// Decide if it need to be rotated by DTplatform.c
	vert = (wrk->attr.vert) && !DT_isCodeRotate90_WhenVert((DT16_ushort)fontidx,NULL);

	/* Read font location & size */
	if(wrk->version == 0)
	{
		ofs = wrk->fonloc + fontidx * 3;
		addr1 = FD_ReadInt(wrk, ofs,   3);
		addr2 = FD_ReadInt(wrk, ofs+3, 3);
		flag = 0;
		cmap = 0;
	} else if((wrk->version == 0x100) || (wrk->version == 0x102))
	{
		/* Get Location & Flag */
#ifdef FDL_EXTEND
		const DT32_int startid = 0x5920;
		if(wrk->attr.ysize <= 21 && fontidx < wrk->subcnt[0] && fontidx > startid)
		{
			if(wrk->attr.ysize <= 11)
				ofs = wrk->extend + (fontidx-startid) * 4;
			else if(wrk->attr.ysize >= 20)
				ofs = wrk->extend + (fontidx-startid + (wrk->subcnt[0]-startid)*(20-11)) * 4;
			else ofs = wrk->extend + (fontidx-startid + (wrk->subcnt[0]-startid)*(wrk->attr.ysize-11)) * 4;

			addr1 = FD_READINTBYDATA4(wrk->fd, ofs);
			addr2 = FD_READINTBYDATA4(wrk->fd, ofs+4);
			addr1 &= 0x0ffffff;
			addr2 &= 0x0ffffff;
			if(addr2 - addr1 == 0)
			{
		ofs = wrk->fonloc + fontidx * 4;
		addr1 = FD_READINTBYDATA4(wrk->fd, ofs);
		addr2 = FD_READINTBYDATA4(wrk->fd, ofs+4);
			}else subdata = 1;
		}else
		{
			ofs = wrk->fonloc + fontidx * 4;
			addr1 = FD_READINTBYDATA4(wrk->fd, ofs);
			addr2 = FD_READINTBYDATA4(wrk->fd, ofs+4);
		}// end if
#else
		ofs = wrk->fonloc + fontidx * 4;
		addr1 = FD_READINTBYDATA4(wrk->fd, ofs);
		addr2 = FD_READINTBYDATA4(wrk->fd, ofs+4);
#endif

		flag = addr1 >> 24;
		addr1 &= 0x0ffffff;
		addr2 &= 0x0ffffff;
		cmap = 0;
	} else if(wrk->version == 0x101)
	{
		/* Get Glyph Index */
		plane = fontidx >> 16;
		fidx2 = fontidx & 0x0FFFF;
		FD_SetPlane(wrk, plane);

		if(wrk->fonmap == 0)
		{
			if(!FD_SearchCMap(wrk, fidx2, &gidx)) return 0;
		} else
		{
			if(!FD_SearchPage(wrk, fidx2, &gidx)) return 0;
		}

		/* Get Location & Flag */
		ofs = wrk->fonloc + gidx * 3;
		addr1 = FD_ReadInt(wrk, ofs,   3);
		addr2 = FD_ReadInt(wrk, ofs+3, 3);

		cmap = 1;
	} else
		return 0;

	total = addr2 - addr1;
	if(total == 0) return 0;

	*x0 = *y0 = 0;
	*aw = *ah = 1000;

#ifdef FDL_EXTEND
	if(subdata)
		ofs = addr1;
	else ofs = wrk->fonofs + addr1;
#else
	ofs = wrk->fonofs + addr1;
#endif

	/* Read Flag */
	if(cmap)
	{
		flag = FD_ReadInt1(wrk, ofs);
		ofs++;
		total--;
		if(total == 0) return 0;
	}

	/* Horz. Metric */
	if(flag & FD_FLAG_HMTX)
	{
		if(!vert)
		{
			//ofs = wrk->fonofs + addr1;
			*x0 = (DT16_short)FD_READINTBYDATA2(wrk->fd, ofs);
			*aw = (DT16_short)FD_READINTBYDATA2(wrk->fd, ofs+2);
		}
		total -= 4;
		ofs += 4;
	}

	/* Vert. Metric */
	if(flag & FD_FLAG_VMTX)
	{
		if(vert)
		{
			//ofs = wrk->fonofs + addr1;
			*y0 = (DT16_short)FD_READINTBYDATA2(wrk->fd, ofs);
			*ah = (DT16_short)FD_READINTBYDATA2(wrk->fd, ofs+2);
		}
		total -= 4;
		ofs += 4;
	}

	/* Font Data Count */
	fcnt2 = 0;    // DLHsieh
	if(flag != 0)
	{
		fcnt = FD_READINTBYDATA2(wrk->fd, ofs);
		total -= fcnt;
		ofs += 2;

    	// DLHsieh
		/* Get Vertical Writing Font Data */
		if(flag & FD_FLAG_VERT)
		{
			fcnt2 = FD_READINTBYDATA2(wrk->fd, ofs+fcnt);
			if(fcnt2 > 0 && vert)
			{
				ofs += fcnt + 2;
				fcnt = fcnt2;
			}
		}
    /*
		if(vert && (flag & FD_FLAG_VERT) && total>0)
		{
			fcnt2 = FD_READINTBYDATA2(wrk->fd, ofs+fcnt);
			if(fcnt2 > 0)
			{
				ofs += fcnt + 2;
				fcnt = fcnt2;
			}
		}
	*/
    // DLHsieh

	} else
		fcnt = total;

  	// DLHsieh
  	// Read Hinting Infomation

#define FDL_GROUP(x1, x2)				(FDL_SET_MAIN_GROUP(x1) | FDL_SUB_GROUP(x2))

#ifndef FDL_ONLY_REMOVE_STROKE_NOHINTING
	if(flag & FD_FLAG_GROUP)
  	{
		ofs2 = (flag & FD_FLAG_VERT) ? (ofs + fcnt) : (ofs + fcnt + 2 + fcnt2);
	  	pcnt = FD_ReadInt1(wrk, ofs2);
	  	gcnt = FD_ReadInt1(wrk, ofs2+1);
	  	scnt = FD_ReadInt1(wrk, ofs2+2);

      	wrk->groupinfo.fontid   = (DT16_ushort)fontidx;
	  	wrk->groupinfo.groupnum = gcnt;
	  	wrk->groupinfo.hintnum  = scnt;
	  	wrk->groupinfo.grouplist= wrk->fd + ofs2 + 3;
	  	wrk->groupinfo.hintlist = (FDL_StrokeHint*)(wrk->fd + ofs2 + 3 + pcnt);
		DT_memcpy(&(wrk->fdl.groupinfo), &wrk->groupinfo, sizeof(wrk->fdl.groupinfo));
	}else
#endif // FDL_ONLY_REMOVE_STROKE_NOHINTING
	{
	////////// 20111027: Jacky Marked the copy for speed up. No hinted-FDLs are used now and wrk->fdl.groupinfo will always be 0.
	#if (0)	
		DT32_int i, ifond=0;
		for(i=0; i < SIZEOF_ARRAY(fdl_font_group); i++)					// For Alan test.
		{
			if(fdl_font_group[i].fontid == fontidx)
			{
				ifond = 1;
				DT_memcpy(&(wrk->fdl.groupinfo), fdl_font_group + i, sizeof(wrk->fdl.groupinfo));
				break;
			}// end if
		}// end for

		if(ifond == 0){
			DT_memcpy(&(wrk->fdl.groupinfo), fdl_font_group + SIZEOF_ARRAY(fdl_font_group) - 1, sizeof(wrk->fdl.groupinfo));	
		}
	#endif
	}// end if

#ifdef FDL_CONV_OLD_V_TO_NEW_HINTLIST
		// For temp use of FDL_REMOVE_STROKE_MIX_MODE, doesn't consider the situation when wrk->groupinfo.hintnum > FDL_MAX_REMOVE_STROKE_NUM
		if(wrk->fdl.groupinfo.hintnum>0){							//20101115
			convhintlist(wrk);
		}
#endif

	//wrk->fdl.groupinfo = fdl_font_group;
  	// DLHsieh

	/* Font data */
	wrk->datacnt = fcnt;
	wrk->dataofs = ofs;

	wrk->fdl.vert = wrk->attr.vert;
	//wrk->fdl.rot  = wrk->attr.vert && (fontidx<256);
	// Modified by Jacky_20110324. Assumption: Unicode CMap only.
	wrk->fdl.rot  = wrk->attr.vert && DT_isCodeRotate90_WhenVert((DT16_ushort)fontidx,NULL);

	return 1;
}
/*---------------------------------------------------------------------------*/
DT32_int FD_DoDraw(pDcwWrk wrk, TFDLRadParam *rad, DT32_int inrad, DT32_int mode)
{
	DT32_int strid, radid, relflag;
	TFDLRadParam r2;
	DT16_WORD mask;
	DT32_int done, cnt, ret, i;
#if _DCW_DEC_STROKE
	DT32_int doit;
#endif

DBG_MSG_SHOW_FUNC_NAME();

	wrk->inrad = inrad;
	ret = DCW_SUCCESS;

#if _DCW_DEC_STROKE
	if(!inrad)
		wrk->DsPartIdx = 0;
#endif

	/* 2007-12-12 Radical :
		 Check wrk->rdatacnt <= 0 inside radical
	*/
	/*  while (wrk->datacnt > 0 && (ret == DCW_SUCCESS))  */
	while(ret == DCW_SUCCESS)
	{
		done = (inrad) ? wrk->rdatacnt <= 0 : wrk->datacnt <= 0;
		if(done) break;

		strid = FD_ReadFontData(wrk, 1);

		if(strid == 0xFA)
		{ /* Symbol */
			wrk->fdl.relno = 0;

			wrk->fdl.valno = FD_ReadFontData(wrk, 1);
			if((wrk->fdl.valno % 2)==1)	wrk->fdl.valno++;
			for(i=0; i<wrk->fdl.valno; i++)
				wrk->fdl.val[i] = (DT8_BYTE)FD_ReadFontData(wrk, 1);

			wrk->fdl.sdatacnt = FD_ReadFontData(wrk, 2);

			/* 2007-12-12 Radical :
				 1. Get Data from rdataofs/rdatacnt in radical
				 2. Shift Symbol (fdl.shiftx/shifty)
			*/
			if(!inrad)
			{
				wrk->fdl.sdataofs = wrk->dataofs;

				wrk->datacnt -= wrk->fdl.sdatacnt;
				wrk->dataofs += wrk->fdl.sdatacnt;
			} else
			{
				wrk->fdl.sdataofs = wrk->rdataofs;

				wrk->rdatacnt -= wrk->fdl.sdatacnt;
				wrk->rdataofs += wrk->fdl.sdatacnt;

				if(rad)
				{
					wrk->fdl.shiftx = (rad->destx - rad->srcx) * wrk->fdl.xsize / 256;
					wrk->fdl.shifty = (rad->desty - rad->srcy) * wrk->fdl.ysize / 256;
				}
			}

			// Draw symbol / Get symbol outline
			ret = FDL_GetFont(wrk, &wrk->fdl, mode, -1);

			/* 2007-12-12 Radical (Reset fdl.shiftx/shifty) */
			if(inrad && rad)
			{
				wrk->fdl.shiftx = 0;
				wrk->fdl.shifty = 0;
			}
		} else if(strid == 0xFC)
		{ /* Radical */
		  /* 2007-12-12 Radical (radid is 2 byte) */
		  /* radid = FD_ReadFontData(wrk, 1); */
			radid = FD_ReadFontData(wrk, 2);

			/* Load radical data */
			FD_LoadRadData(wrk, radid, &r2);

			/* Radical parameter */
			r2.flag = (DT8_BYTE)FD_ReadFontData(wrk, 1);
			if(r2.flag != 0)
			{
				/* Setup radical parameter */
				if((r2.flag & FD_RAD_SCALEX) != 0)
				{
					r2.destx = (DT16_short)FD_ReadFontData(wrk, 1);
					r2.destw = (DT16_short)FD_ReadFontData(wrk, 1);
				}

				if((r2.flag & FD_RAD_SCALEY) != 0)
				{
					r2.desty = (DT16_short)FD_ReadFontData(wrk, 1);
					r2.desth = (DT16_short)FD_ReadFontData(wrk, 1);
				}

				if((r2.flag & FD_RAD_WID) != 0)
				{
					r2.wid = (DT16_short)FD_ReadFontData(wrk, 1);
				}

				/* Draw radical */
				ret = FD_DoDraw(wrk, &r2, 1, mode);
			} else
			{
				/* Draw radical */
				ret = FD_DoDraw(wrk, NULL, 1, mode);
			}
#if _DCW_DEC_STROKE
			wrk->DsPartIdx--;
#endif
		} else if(strid == 0xFD)
		{ /* Outline (Skip) */
			cnt = FD_ReadFontData(wrk, 2);
			wrk->datacnt -= cnt;
			wrk->dataofs += cnt;
		} else
		{ /* Stoke */
			if(strid == 0xFF)
			{
				strid = FD_ReadFontData(wrk, 2);
			}

			/* Load stroke data */
			FD_LoadStrokeData(wrk, strid, &relflag);

			/* Read relative point */
			mask = 1;
			for(i=0; i<wrk->fdl.relno; i++)
			{
				if(i>=1 && i<=4 && relflag!=0)
				{
					if((relflag & mask)==0)
						wrk->fdl.rel[i*2] = (DT8_BYTE)FD_ReadFontData(wrk, 1);
					else
						wrk->fdl.rel[i*2] = wrk->fdl.rel[i*2-2];
					mask = (DT16_WORD)(mask << 1);

					if((relflag & mask)==0)
						wrk->fdl.rel[i*2+1] = (DT8_BYTE)FD_ReadFontData(wrk, 1);
					else
						wrk->fdl.rel[i*2+1]	= wrk->fdl.rel[i*2-1];
					mask = (DT16_WORD)(mask << 1);
				} else
				{
					wrk->fdl.rel[i*2]   = (DT8_BYTE)FD_ReadFontData(wrk, 1);
					wrk->fdl.rel[i*2+1] = (DT8_BYTE)FD_ReadFontData(wrk, 1);
				}
			}

			/* Read value */
			for(i=0; i<wrk->fdl.valno; i++)
				wrk->fdl.val[i] = (DT8_BYTE)FD_ReadFontData(wrk, 1);

			/* Modify radical data */
			if(rad)
			{
				FD_ModifyRadData(wrk, rad);
			}

			// Draw stroke / Get stroke outline
#if _DCW_DEC_STROKE
			doit = 1;
			if(Ds_Find(wrk))
			{
				/* Action for Decrease Stroke */
				switch(wrk->DsMode)
				{
					case 0:	/* Remove */
						doit = 0;
						break;
					case 1:	/* Move up */
						for(i=0; i<wrk->fdl.relno; i++)
							wrk->fdl.rel[i*2] -= wrk->DsVal;
						break;
					case 2:	/* Move Down */
						for(i=0; i<wrk->fdl.relno; i++)
							wrk->fdl.rel[i*2] += wrk->DsVal;
						break;
					case 3:	/* Move Left */
						for(i=0; i<wrk->fdl.relno; i++)
							wrk->fdl.rel[i*2+1] -= wrk->DsVal;
						break;
					case 4:	/* Move Right */
						for(i=0; i<wrk->fdl.relno; i++)
							wrk->fdl.rel[i*2+1] += wrk->DsVal;
						break;
				}
			}

			if(doit)
				ret = FDL_GetFont(wrk, &wrk->fdl, mode, strid);
			else
				ret	= 0;
#else
			ret = FDL_GetFont(wrk, &wrk->fdl, mode, strid);
#endif
		}// end if
#if _DCW_DEC_STROKE
		wrk->DsPartIdx++;
#endif
	}// end while

	wrk->inrad = 0;

	return ret;
}
/*---------------------------------------------------------------------------*/
DT_void FD_ModifyRadData(pDcwWrk wrk, TFDLRadParam *rad)
{
	DT32_int w2, h2, x, y, i;

DBG_MSG_SHOW_FUNC_NAME();

	/* Modify value */
	if(rad->wid != 128)
	{
		for(i=0; i<wrk->fdl.valno; i++)
		{
			wrk->fdl.val[i] = (DT8_BYTE)(((DT32_int)wrk->fdl.val[i] * rad->wid + 64) / 128);
		}
	}

	/* Modify relative point */
	w2 = rad->srcw;
	h2 = rad->srch;

	for(i=0; i<wrk->fdl.relno; i++)
	{
		x = wrk->fdl.rel[i*2];
		y = wrk->fdl.rel[i*2+1];

		y = (((y - rad->srcx) * rad->destw + w2) / rad->srcw) + rad->destx;
		x = (((x - rad->srcy) * rad->desth + h2) / rad->srch) + rad->desty;

		wrk->fdl.rel[i*2]   = (DT8_BYTE)x;
		wrk->fdl.rel[i*2+1] = (DT8_BYTE)y;
	}
}

#if _DCW_DEC_STROKE
/*---------------------------------------------------------------------------*/
DT32_int Ds_SetDsData(pDcwWrk wrk, DT8_char *dsdata)
{
	if(dsdata)
	{
		wrk->DsFontCnt = (DT16_WORD)FD_READINTBYDATA2(dsdata,0);	//*((DT16_WORD*)dsdata);
		dsdata += 2;

		wrk->DsIdxs = (DT8_BYTE*)dsdata;							//(DT16_WORD*)dsdata;
		dsdata += (wrk->DsFontCnt + 1) * 4;

		wrk->DsDatas = dsdata;
	} else
	{
		wrk->DsFontCnt  = 0;
		wrk->DsIdxs     = NULL;
		wrk->DsDatas    = NULL;
	}

	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int Ds_LoadData(pDcwWrk wrk, DT32_int fidx, DT32_int decstr)
{
	DT16_WORD ofs, fidx2, i;
	DT8_BYTE *idxs;																//DT16_WORD *idxs;

	wrk->DsCnt  = 0;
	wrk->DsData = NULL;

	if(decstr)
	{
		idxs = wrk->DsIdxs;
		for(i = 0; i < wrk->DsFontCnt; i++)
		{
			fidx2 = (DT16_WORD)FD_READINTBYDATA2(idxs,0);						//*idxs;
			if(fidx2 == fidx)
			{
				ofs = (DT16_WORD)FD_READINTBYDATA2(idxs, 1*2);					//*(idxs + 1);

				wrk->DsCnt  = (DT16_WORD)FD_READINTBYDATA2(idxs, 3*2) - ofs;	//*(idxs + 3) - ofs;
				wrk->DsData = wrk->DsDatas + (ofs * 3);
				return(1);
			} else if(fidx2 > fidx)
				break;

			idxs += 2*2;														//idxs += 2;
		}
	}

	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int Ds_Find(pDcwWrk wrk)
{
	DT32_int fsize, fsize2, pidx, modeval;
	DT8_BYTE *p, *lastp=NULL;
	DT32_int cnt;

//	fsize = wrk->attr.xsize;
//	if(fsize != wrk->attr.ysize || fsize > 255)	return(0);

	fsize = wrk->attr.ysize;
	if(fsize != 18 && fsize != 20)
		return(0);
/*	switch(fsize)
	{
	case 18:
	case 19:
		fsize = 18;
		break;
	case 21:
	case 20:
		fsize = 20;
		break;
	default:
		return 0;
	}
*/
	p = wrk->DsData;
	cnt = wrk->DsCnt;

	while(cnt > 0)
	{
		fsize2 = *p++;
		if(fsize2 > fsize)
			break;

		if(fsize2 == fsize)
		{
			pidx = *p++;
			if(pidx == wrk->DsPartIdx)
			{
				modeval = *p++;
				wrk->DsMode = modeval >> 4;
				wrk->DsVal  = modeval & 0x0f;
				return(1);
			}else
				p++;
		}else
			p += 2;

		cnt--;
	}// end while

	return(0);
}
/*---------------------------------------------------------------------------*/
#endif  /* _DCW_DEC_STROKE */

/*---------------------------------------------------------------------------*/
/*
GROUP_UNIT group_table[] = {
			{0x0000, 1,  0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
			{0x65E5, 1,  2, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
			{0x672C, 1,  5, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
			{0x6674, 3,  9, {0, 1, 1, 1, 1, 2, 2, 2, 0} },
			{0x5929, 1,  4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
			{0x66C7, 3, 14, {0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0} },
			{0x96E8, 1,  7, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} },
*/

