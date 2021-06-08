#include "DcwLangModule.h"

#ifdef DIGITYPE_STD

#include "DcwShaperVG.h"
#include "Digitype_std.h"
#include "DcwLayout.h"
#include "DcwCache.h"
#include "DTmanager.h"
#include "DTdigitype.h"
#include "DigiTypeApi.h"

#ifdef THAI_thai
#include "DcwThai.h"
#endif

#ifdef ARABIC_arabic
#include "DcwArabic.h"
#endif

DT8_uchar rasSetBitinBmp( DT8_uchar val, DT8_uchar byteval, DT32_int j, DT32_int op )
{
	DT8_uchar bitmask=0,bb=0;

DBG_MSG_SHOW_FUNC_NAME();

	switch(op){
	case DCW_COPYIFBKZERO:
		if(val>0){	
		  bitmask = val<<(7-(j&7));
		  bb = bitmask | byteval;
		}else bb = byteval;
		
		break;
	case DCW_SETBKZERO:
		bitmask=0x01<<(7-(j&7));
		bb = (~bitmask)&byteval;		
		break;
	default:
		if(val>0){	
		  bitmask = val<<(7-(j&7));
		  bb = bitmask | byteval;
		}else bb = byteval;
	}
	return bb;
}

DT8_uchar rasSetByteinBmp( DT8_uchar val, DT8_uchar byteval, DT32_int op )
{
	DT8_uchar bb=0;

DBG_MSG_SHOW_FUNC_NAME();

	switch(op){
	case DCW_COPYIFBKZERO:
		if(val>0){	bb = val;
		}else bb = byteval;		
		break;
	case DCW_SETBKZERO:
		bb = 0;		
		break;
	default:
		if(val>0){	
		  bb = val;
		}else bb = byteval;
	}
	return bb;
}


DT16_ushort MakeCacheStyleValue(DT16_ushort fid, DT16_ushort grade, DT16_ushort grade_values, DT16_ushort vert)
{
	DT16_ushort style;

DBG_MSG_SHOW_FUNC_NAME();

	/* fid */
	style = fid<<8;

	/* grade values */
	if(grade==DCW_MODE_GRAY16){
		if(grade_values==DLO_GRADE_INDEX_0X00_0X0F){
			style |= DT_CACHE_GRADEVALUES_INDEX;
		}
	}

	/* vert */
	if(vert)
		style |= DT_CACHE_VERT_FONT;

	return style;
}

DT16_ushort MakeCacheOthersValue(/* Defined by yourself in the future, not used now. */)
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;
}

/* Calculate the max font rect for the font style. */
DT_void CalculateFontRect(DT_void *pattr, DT32_int *FXByte, DT32_int *nHeight, DT32_int *nWidth, DT32_int *orgX, DT32_int *orgY, DT32_int *Xext )
{
    DT32_int FXOrg=0, FYOrg=0;
    DT32_int FXExtend=0, FYExtend=0;
	DCW_AttrData *Attr=(DCW_AttrData *)pattr;
    DT32_int w_edge = Attr->w_edge;
    DT32_int ext=0;
 
DBG_MSG_SHOW_FUNC_NAME();
	
    switch (Attr->f_edge)
    {
    case DCW_EDGE_NORMAL:
        FXOrg = FYOrg = 0;
        FXExtend = Attr->xsize;
        FYExtend = Attr->ysize;
        break;
        
    case DCW_EDGE_OUTLINE:
    case DCW_EDGE_BOLD:
        FXOrg = FYOrg = w_edge;
        FXExtend = Attr->xsize + w_edge * 2;
        FYExtend = Attr->ysize + w_edge * 2;
        break;
        
    case DCW_EDGE_BOLD_RIGHT:
        FXOrg = FYOrg = 0;
        FXExtend = Attr->xsize + w_edge;
        FYExtend = Attr->ysize;
        break;
        
    case DCW_EDGE_BOLD_DOWN:
        FXOrg = FYOrg = 0;
        FXExtend = Attr->xsize;
        FYExtend = Attr->ysize + w_edge;
        break;
        
    case DCW_EDGE_BOLD_RIGHT_DOWN:
        FXOrg = FYOrg = 0;
        FXExtend = Attr->xsize + w_edge;
        FYExtend = Attr->ysize + w_edge;
        break;
    }
    
    if (Attr->italic > 0 || Attr->w_underline > 0)
    {
        ext = max(Attr->italic, (Attr->w_underline > 0) ? Attr->e_underline: 0);
        if (!Attr->vert)
            FXExtend += ext;
        else
            FYExtend += ext;
    }
    
    /* Calculate Bitmap size */
	if(FXByte){
		switch (Attr->grade)
		{
			case DCW_MODE_MONOCHROME:
				/* *FXByte = (FXExtend + 31) / 32 * 4;*/
				*FXByte = (FXExtend + 7) / 8;
				break;
        
			case DCW_MODE_GRAY16:
			case DCW_MODE_GRAY256:
				/* *FXByte = (FXExtend + 3) / 4 * 4;*/
				*FXByte = FXExtend;
				break;
		}
	}
	if(nHeight)	*nHeight = FYExtend;
	if(nWidth)	*nWidth  = FXExtend;
	if(orgX)	*orgX = FXOrg;
	if(orgY)	*orgY = FYOrg;	
	if(Xext)	*Xext = ext;

}

/* Suppose: if you call this function, it means that you can get the attribute of option from curfontdata or altfont either.*/
/* Might be something error: Is it right for bReQuery value? Should it be decided by something like DCW_GetAw()?			*/
/* Becare of the situation: curfont contain fontidx, but not langtab info, and altfont has fontidx and langtab both.		*/
DT32_int DCW_QueryCharAttr_1(DT_void *pattr, DCW_AttrData *attr, DT32_long fontidx, DT32_int gseq2idx, DCW_CharAttr_Option option)
{
	DT32_int val, bReQuery;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DT_Font *altfont = pwrk->alt_DT_Font;
	DT8_char *curfontdata = attr->fontdata;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

//	if(fontidx!=0){
//		aw = DCW_GetAw(attr, fontidx);
//	}else{
//		aw = 0;
//	}
	val = DCW_QueryCharAttr(attr, fontidx, option);
	bReQuery = 0;
	switch(option){
	case DCW_CHARATTR_LANGTAB_THAI:
		if(0>=val){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_LANGTAB_ICON:
		if(0>=val){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_LANGTAB_RAS_SCALE:
		if(0>=val){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_LANGTAB_BIN_SCALE:
		if(0>=val){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_XYSCALERATIO:
		if(val==0 || val==DCW_BASE_RATIO){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_ISXYSCALE_CHAR:
		if(0==val){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_RASSCALERATIO:
		if(val==0 || val==DCW_BASE_RATIO){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_ISRASSCALE_CHAR:
		if(0==val){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_BINSCALERATIO:
		if(val==0 || val==DCW_BASE_RATIO){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_ISBINSCALE_CHAR:
		if(0==val){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_HEIGHT_SHIFT:
		/* Now it will always return 0, do nothing here. */
		break;
	case DCW_CHARATTR_NORMAL_WIDTH:
		if(val==attr->xsize){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_NORMAL_HEIGHT:
		if(val==attr->ysize){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_ISOFFSETY_CHAR:
		/* Don't know how to decide the value of bReQuery? by aw? or by return value? */
		/* Need to do in the future. */
		if(val==0){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_GET_OFFSETY:
	case DCW_CHARATTR_GET_LOGHEIGHT:
	case DCW_CHARATTR_GET_3IN1_VALUE:
		/* Don't know how to decide the value of bReQuery? by aw? or by return value? */
		/* Need to do in the future. */
		if(val==0){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_END:
	default:
		break;
	}
	
//		if(DCW_GetAw(attr,fontidx)!=DCW_CODE_NOT_EXIST){
//			// current font contains fontidx, no need to check altfont.
//			return val;
//		}
		if(pfc){
			if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){ 
			}else{
				ras_chkGlyphExist(pwrk->ras_attr,(DT16_ushort)fontidx,gseq2idx);
			}
			if(0==pfc->codeExist || (pfc->codeExist && pfc->existFont!=DLO_ALT_DT_FONT))
				return val;
		}else{
			if(DCW_GetAw(attr,fontidx)!=DCW_CODE_NOT_EXIST)
				return val;
		}
	
	if(bReQuery && pwrk->altfontcnt>0){
		attr->fontdata = altfont->fontdata;
		val = DCW_QueryCharAttr(attr, fontidx, option);
		attr->fontdata = curfontdata;
	}
	return val;
}

/* This function's return value CAN stand for if fontidx exists.	*/
/* Return: 0 means fontidx do not exist, >0 advanced width			*/
DT32_int DCW_GetAw_1(DT_void *pattr, DCW_AttrData *attr, DT32_long fontidx, DT32_int gseq2idx, DT32_int option)
{
	DT32_int aw;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DT_Font *altfont = pwrk->alt_DT_Font;
	DT8_char *curfontdata = attr->fontdata;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(RAS_OPTION_GETAW==option && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW)
			return pfc->aw;
		if(RAS_OPTION_EXIST==option && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){
			if(pfc->existFont==DLO_ICON_DT_FONT)
				return DCW_CODE_NOT_EXIST;			// for the char that exists in dif
			// no need to check aw or ah, because that will be set once this func had been called.
			return pfc->codeExist ? 1/*pfc->aw*/ : DCW_CODE_NOT_EXIST;	// 1(other than DCW_CODE_NOT_EXIST) means it exists
		}
	}
	
	aw = DCW_GetAw(attr,fontidx);
	if(aw==DCW_CODE_NOT_EXIST){
		if(pwrk->altfontcnt>0){
			attr->fontdata = altfont->fontdata;
			DCW_Create(attr);
			aw = DCW_GetAw(attr,fontidx);
			if(aw==DCW_CODE_NOT_EXIST){
				if(pfc && !(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)){// avoid to modify the result by dif
					// these value might be modified at dif when this situation.
					pfc->codeExist = 0;
					pfc->existFont = 0;
					pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
					// code don't exist, icon font won't scale and move, so set followings also.
					setDefault_Scale_LRsb_MoveY(pfc);
				}
			}else{
				if(pfc){
					pfc->codeExist = 1;
					pfc->existFont = DLO_ALT_DT_FONT;
					pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;	// force it as been checked.
				}
			}
			attr->fontdata = curfontdata;
			DCW_Create(attr);
		}else{
			if(pfc && !(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)){
				// these value might be modified at dif when this situation.
				pfc->codeExist = 0;
				pfc->existFont = 0;
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
				// code don't exist, icon font won't scale and move, so set followings also.
				setDefault_Scale_LRsb_MoveY(pfc);
			}
		}
	}else{
		if(pfc){
			pfc->codeExist = 1;
			pfc->existFont = DLO_CUR_DT_FONT;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;	// force it as been checked.
		}
	}
	if(option==RAS_OPTION_GETAW){		// set aw only when this option
		if(pfc){
			pfc->aw = aw;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AW;
		}
	}

	return aw;
}

DT32_int DCW_Raster_1(DT_void *pattr, DT32_int *aw, DCW_AttrData *attr, DCW_RasterData *raster)
{
	DT32_int ret=DCW_SUCCESS;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DT_Font *altfont = pwrk->alt_DT_Font;
	DT_Font *curfont = pwrk->cur_DT_Font;
	DT8_char *curfontdata = attr->fontdata;
// 	pDT_FontMgr_wrk	pmgrwrk = curfont->fontmgr;
	DT32_int bGetFromaltfont=0;
	CacheUnit cu;
	DT16_ushort style, others;
	pDT_Fontwrk pdtfwrk = (pDT_Fontwrk)(pwrk->pdtfwrk);
	DT32_int fxbyte = raster->xbyte;

DBG_MSG_SHOW_FUNC_NAME();

	*aw = DCW_GetAw(attr,raster->fontidx);
	if((*aw)==DCW_CODE_NOT_EXIST && pwrk->altfontcnt>0){
		attr->fontdata = altfont->fontdata;
		DCW_Create(attr);
		*aw = DCW_GetAw(attr,raster->fontidx);
		if((*aw)!=DCW_CODE_NOT_EXIST){
			bGetFromaltfont = 1;
			ret = DCW_Raster(attr,raster);
		}/* Treat aw==0 as DLO_SUCCESS */
		attr->fontdata = curfontdata;
		DCW_Create(attr);
	}else{
		ret = DCW_Raster(attr,raster);
	}


	if( pdtfwrk->usedcachearr && pdtfwrk->usedcachearr->CacheSet && pdtfwrk->usedcachearr->Init_FontCache &&
		attr->xsize <= pdtfwrk->usedcachearr->CacheSet->condition.max_fontsize &&
		attr->ysize <= pdtfwrk->usedcachearr->CacheSet->condition.max_fontsize &&
		ret==DCW_SUCCESS && (*aw)!=DCW_CODE_NOT_EXIST){
		if( 0==attr->italic && attr->f_edge==DCW_EDGE_NORMAL &&
			0==attr->w_underline && attr->grade!=DCW_MODE_MONOCHROME
			&& fxbyte==raster->xbyte	// 20110804: Jacky added for xbyte might be modified in DcwRaster.
			&& raster->y0>=0	// Jacky_20110620: Not allowed now, but it might be required in the future.
			){
			style = MakeCacheStyleValue((DT16_ushort)((bGetFromaltfont)?altfont->fid:curfont->fid),
										(DT16_ushort)attr->grade, (DT16_ushort)pwrk->grade_values, (DT16_ushort)pwrk->vert);
			others = MakeCacheOthersValue();
			cu.width	= (DT16_ushort)attr->xsize;
			cu.height	= (DT16_ushort)attr->ysize;
			cu.extra.body[0]	= (DT8_char)raster->x0;
			cu.extra.body[1]	= (DT8_char)raster->y0;
			cu.extra.body[2]	= (DT8_char)raster->xs;
			cu.extra.body[3]	= (DT8_char)raster->ys;
			cu.style	= style;
			cu.others	= others;
			cu.data		= (DT8_uchar*)raster->bitmap;
			AddToCache(pdtfwrk->usedcachearr, (DT16_ushort)raster->fontidx, (DT16_short)attr->xsize, (DT16_short)attr->ysize, &cu);
		}
	}

	return ret;
}

DT_void *DT_bmpcpy( DT_void *dest, const DT_void *src, DT_size_t count )
{
	DT32_ulong	*d, *s;
	DT16_ushort	*ds, *ss;
	DT8_uchar	*dc, *sc;
	DT_size_t	i, cnt;

DBG_MSG_SHOW_FUNC_NAME();
DBGTRACE_STR("dest = ");	DBGTRACE_INT((DT32_int)dest);
DBGTRACE_STR("src = ");		DBGTRACE_INT((DT32_int)src);
DBGTRACE_STR("count = ");		DBGTRACE_INT(count);


	if(!dest || !src || count<=0)
		return dest;

	if( !(((DT_size_t)dest)&3) && !(((DT_size_t)src)&3) && !(count&3) ){	
		cnt = count>>2;
		d = (DT32_ulong*)dest;
		s = (DT32_ulong*)src;
		for(i=0;i<cnt;i++){
//			*d++ |= *s++;
			*d++ = *s++;
		}
	}else if(!(((DT_size_t)dest)&1) && !(((DT_size_t)src)&1) && !(count&1) ){
		cnt = count>>1;
		ds = (DT16_ushort*)dest;
		ss = (DT16_ushort*)src;
		for(i=0;i<cnt;i++){
//			*ds++ |= *ss++;
			*ds++ = *ss++;
		}
	}else{
		dc = (DT8_uchar*) dest;
		sc = (DT8_uchar*) src;
		for(i=0;i<count;i++){
//			*dc++ |= *sc++;
			*dc++ = *sc++;
		}
	}
	return dest;
}

DT_void *DT_bmpORcpy( DT_void *dest, const DT_void *src, DT_size_t count )
{
	DT32_ulong	*d, *s;
	DT16_ushort	*ds, *ss;
	DT8_uchar	*dc, *sc;
	DT_size_t	i, cnt;

	DBG_MSG_SHOW_FUNC_NAME();
	DBGTRACE_STR("dest = ");	DBGTRACE_INT((DT32_int)dest);
	DBGTRACE_STR("src = ");		DBGTRACE_INT((DT32_int)src);
	DBGTRACE_STR("count = ");		DBGTRACE_INT(count);


	if(!dest || !src || count<=0)
		return dest;

	if( !(((DT_size_t)dest)&3) && !(((DT_size_t)src)&3) && !(count&3) ){	
		cnt = count>>2;
		d = (DT32_ulong*)dest;
		s = (DT32_ulong*)src;
		for(i=0;i<cnt;i++){
			*d++ |= *s++;
		}
	}else if(!(((DT_size_t)dest)&1) && !(((DT_size_t)src)&1) && !(count&1) ){
		cnt = count>>1;
		ds = (DT16_ushort*)dest;
		ss = (DT16_ushort*)src;
		for(i=0;i<cnt;i++){
			*ds++ |= *ss++;
		}
	}else{
		dc = (DT8_uchar*) dest;
		sc = (DT8_uchar*) src;
		for(i=0;i<count;i++){
			*dc++ |= *sc++;
		}
	}
	return dest;
}

DT_void *DT_bmpHIcpy( DT_void *dest, const DT_void *src, DT_size_t count )
{
	DT8_uchar	*dc, *sc;
	DT_size_t	i;

	DBG_MSG_SHOW_FUNC_NAME();
	DBGTRACE_STR("dest = ");	DBGTRACE_INT((DT32_int)dest);
	DBGTRACE_STR("src = ");		DBGTRACE_INT((DT32_int)src);
	DBGTRACE_STR("count = ");		DBGTRACE_INT(count);


	if(!dest || !src || count<=0)
		return dest;

	dc = (DT8_uchar*) dest;
	sc = (DT8_uchar*) src;
	for(i=0;i<count;i++){
		*dc = ((*sc) > (*dc)) ? (*sc) : (*dc);
		*dc++;
		*sc++;
	}
	return dest;
}

DT8_uchar isUseDT_bmpcpy(pLayWrk pwrk, DCW_AttrData *attr, DT16_ushort ch)
{
DBG_MSG_SHOW_FUNC_NAME();

	if( pwrk->italic == 0 && pwrk->spacing >= 0 && pwrk->copyMethod==DLO_CPY_NOT_SPECIFY
#ifdef THAI_thai
		&& (!isThaiChars(ch))
#endif
#ifdef INDICS_devanagari
		&& (!isIndicsDevanagariChars(ch))
#endif
		){
		return 1;
	}
	return 0;
}

// To avoid pixel value error when the connection overlapping in Arabic letters.
//DT_BOOL isConnectChars(pLayWrk pwrk, DT16_ushort ch)
//{
//DBG_MSG_SHOW_FUNC_NAME();
//
//	return isArabicChars(pwrk, ch)/* || isIndicsDevanagariChars(ch)*/;
//}

/* gseq2idx<0 means it required to search in FDL fontdata; else it can get directly from g2info that had been qureied before. */
DT32_int rasScaleMethod(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DT32_int *rto)
{
	DT32_int ratio;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

	if(pfc){
		// if checked before, return directly.
		if((pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_SCALE)/* && ch==pwrk->g2info[gseq2idx].code*/){
			if(rto)
				*rto = (DT32_int)pfc->scaleRatio;
			return (DT32_int)pfc->scaleMethod;
		}
	}
	
	if(rto)
		*rto = DLO_BASE_RATIO;
	if(0x0000==ch){
		if(pfc){
			pfc->scaleRatio = (DT16_ushort) DLO_BASE_RATIO;
			pfc->scaleMethod= (DT16_ushort) DLO_NOT_SCALE;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
		}
		return DLO_NOT_SCALE;
	}

	/*check if there is an advanced ratio by character.*/
	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,ch,gseq2idx,DLO_CHARATTR_BINSCALERATIO,&ratio);
	if(DCW_BASE_RATIO != ratio)
	{
		if(rto)
			*rto = ratio;
		if(pfc){
			pfc->scaleRatio = (DT16_ushort) ratio;
			pfc->scaleMethod= (DT16_ushort) DLO_SCALE_BY_BINSCALERATIO;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
		}
		return RAS_SCALE_BY_BINSCALERATIO;
	}
	
	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,ch,gseq2idx,DLO_CHARATTR_XYSCALERATIO,&ratio);
	if(DCW_BASE_RATIO != ratio)
	{
		if(rto)
			*rto = ratio;
		if(pfc){
			pfc->scaleRatio = (DT16_ushort) ratio;
			pfc->scaleMethod= (DT16_ushort) DLO_SCALE_BY_XYSCALERATIO;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
		}
		return RAS_SCALE_BY_XYSCALERATIO;
	}

	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,ch,gseq2idx,DLO_CHARATTR_RASSCALERATIO,&ratio);
	if(DCW_BASE_RATIO != ratio)
	{
		if(rto)
			*rto = ratio;
		if(pfc){
			pfc->scaleRatio = (DT16_ushort) ratio;
			pfc->scaleMethod= (DT16_ushort) DLO_SCALE_BY_RASSCALERATIO;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
		}
		return RAS_SCALE_BY_RASSCALERATIO;
	}

#ifdef DIGITYPE_STD_ENABLE_RATIO_FROM_FDL_GLOBAL_INFO
	/*read ratio table to get font ratio.*/
//	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_RATIO_FILEWIDE, &ratio);
//	if(DCW_BASE_RATIO != ratio)
//	{
//		if(rto)
//			*rto = ratio;
//		if(pfc){
//			pfc->scaleRatio = (DT16_ushort) ratio;
//			pfc->scaleMethod= (DT16_ushort) DLO_SCALE_BY_RATIO_FILEWIDE;
//			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
//		}
//		return RAS_SCALE_BY_RATIO_FILEWIDE;
//	}
#endif
	
	/*decide the ratio by code range.*/
	if(gDT_FORCE_SCALE_RATIO != 0){
		if(isArabicCodeRange(pwrk,ch))
		{
			if(rto)
				*rto = gDT_FORCE_SCALE_RATIO + 1000;	//DCW_BASE_RATIO
			if(pfc){
				pfc->scaleRatio = (DT16_ushort) gDT_FORCE_SCALE_RATIO + 1000;
				pfc->scaleMethod= (DT16_ushort) DLO_SCALE_BY_CODERANGE;
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
			}
			return RAS_SCALE_BY_CODERANGE;
		}else if(isThaiChars(ch))
		{
			if(rto)
				*rto = gDT_FORCE_SCALE_RATIO + 1000;	//DCW_BASE_RATIO
			if(pfc){
				pfc->scaleRatio = (DT16_ushort) gDT_FORCE_SCALE_RATIO + 1000;
				pfc->scaleMethod= (DT16_ushort) DLO_SCALE_BY_CODERANGE;
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
			}
			return RAS_SCALE_BY_CODERANGE;
		}
	}

	if(pfc){
		pfc->scaleRatio = (DT16_ushort) DLO_BASE_RATIO;
		pfc->scaleMethod= (DT16_ushort) DLO_NOT_SCALE;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
	}
	return RAS_NOT_SCALE;
}

// This function is used to modify the DCW_AttrData temporarily.
// Return: Scaled by What?
// After function returned, the normalw & normalh will be the width and height.
// This function needs to consider vert.
DT32_int rasScaledAttr(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DCW_AttrData *oriattr, DCW_AttrData *newattr, DT32_int *normalw, DT32_int *normalh)
{
	DT32_int ratio;
	DT32_int  scalemethod, szY;

DBG_MSG_SHOW_FUNC_NAME();

	scalemethod = rasScaleMethod(pwrk, ch, gseq2idx, &ratio);

	switch(scalemethod)
	{
	case RAS_SCALE_BY_XYSCALERATIO:
		if(oriattr->vert){
			szY = DCW_SCALED_SIZEXY(oriattr->xsize,ratio);	// force scaling by ysize.
		}else{
			szY = DCW_SCALED_SIZEXY(oriattr->ysize,ratio);	// force scaling by ysize.
		}
		newattr->xsize = szY;
		newattr->ysize = szY; 
		pwrk->bScaled  = DT_TRUE; 
		if(normalw)
			*normalw = szY;
		if(normalh)
			*normalh = szY;
		break;
	case RAS_SCALE_BY_RASSCALERATIO:
	case RAS_SCALE_BY_BINSCALERATIO:
			newattr->xsize = DCW_SCALED_SIZEXY(oriattr->xsize,ratio);
			newattr->ysize = DCW_SCALED_SIZEXY(oriattr->ysize,ratio);
			pwrk->bScaled  = DT_TRUE; 
			if(normalw)
				*normalw = newattr->xsize;
			if(normalh)
				*normalh = newattr->ysize;
		break;
	case RAS_SCALE_BY_RATIO_FILEWIDE:
		/* 20110915: Not used now, modify its ratio value to be scaled by the same way with others. */
		newattr->xsize = DCW_SCALED_SIZEXY(oriattr->xsize,ratio);/*oriattr->xsize*ratio;*/		newattr->xsize >>= 6;
		newattr->ysize = DCW_SCALED_SIZEXY(oriattr->xsize,ratio);/*oriattr->ysize*ratio;*/		newattr->ysize >>= 6; 
		pwrk->bScaled  = DT_TRUE; 
		if(normalw)
			*normalw = newattr->xsize;
		if(normalh)
			*normalh = newattr->ysize;
		break;
	case RAS_SCALE_BY_CODERANGE:
		if(isArabicCodeRange(pwrk,ch))
		{
			newattr->xsize = DT_ScaleArabicSize(oriattr->xsize);
			newattr->ysize = DT_ScaleArabicSize(oriattr->ysize);
			pwrk->bScaled  = DT_TRUE; 
			if(normalw)
				*normalw = newattr->xsize;
			if(normalh)
				*normalh = newattr->ysize;
		}else if(isThaiChars(ch))
		{
			newattr->xsize = DT_ScaleThaiSize(oriattr->xsize);
			newattr->ysize = DT_ScaleThaiSize(oriattr->ysize);
			pwrk->bScaled  = DT_TRUE;
			if(normalw)
				*normalw = newattr->xsize;
			if(normalh)
				*normalh = newattr->ysize;
		}
		break;
	case RAS_NOT_SCALE:
	default:
		newattr->xsize = oriattr->xsize;
		newattr->ysize = oriattr->ysize;
		if(normalw)
			*normalw = oriattr->xsize;
		if(normalh)
			*normalh = oriattr->ysize;
		break;
	}

	return scalemethod;

//	/*check if there is an advanced ratio by character.*/
//	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,ch,DLO_CHARATTR_XYSCALERATIO,&ratio);
//	if(DCW_BASE_RATIO != ratio)
//	{
////		if(pwrk->vert)
////			szY = DCW_SCALED_SIZEXY(oriattr->xsize,ratio);	// force scaling by xsize.
////		else
////			szY = DCW_SCALED_SIZEXY(oriattr->ysize,ratio);	// force scaling by ysize.
//		szY = DCW_SCALED_SIZEXY(oriattr->ysize,ratio);	// force scaling by ysize.
//		newattr->xsize = szY;
//		newattr->ysize = szY; 
//		pwrk->bScaled  = DT_TRUE; 
//		if(normalw)
//			*normalw = szY;
//		if(normalh)
//			*normalh = szY;
//		return RAS_SCALE_BY_XYSCALERATIO;
//	}
//
//	/*read ratio table to get font ratio.*/
//	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, DLO_CHARATTR_RATIO_FILEWIDE, &ratio);
//	if(64 != ratio)
//	{
//		newattr->xsize = oriattr->xsize * ratio;		newattr->xsize >>= 6;
//		newattr->ysize = oriattr->ysize * ratio;		newattr->ysize >>= 6; 
//		pwrk->bScaled  = DT_TRUE; 
//		if(normalw)
//			*normalw = newattr->xsize;
//		if(normalh)
//			*normalh = newattr->ysize;
//		return RAS_SCALE_BY_RATIO_FILEWIDE;
//	}
//
//	/*decide the ratio by code range.*/
//	if(isArabicChars(pwrk,ch))
//	{
//		newattr->xsize = DT_ScaleArabicSize(oriattr->xsize);
//		newattr->ysize = DT_ScaleArabicSize(oriattr->ysize);
//		pwrk->bScaled  = DT_TRUE; 
//		if(normalw)
//			*normalw = newattr->xsize;
//		if(normalh)
//			*normalh = newattr->ysize;
//		return RAS_SCALE_BY_CODERANGE;
//	}else if(isThaiChars(ch))
//	{
//		newattr->xsize = DT_ScaleThaiSize(oriattr->xsize);
//		newattr->ysize = DT_ScaleThaiSize(oriattr->ysize);
//		pwrk->bScaled  = DT_TRUE;
//		if(normalw)
//			*normalw = newattr->xsize;
//		if(normalh)
//			*normalh = newattr->ysize;
//		return RAS_SCALE_BY_CODERANGE;
//	}
//	
//	return RAS_NOT_SCALE;
}


// Return: the pointer to the new attr.
DT_void* rasMakeNewAttr(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DCW_AttrData *oriattr, DCW_AttrData *newattr)
{
DBG_MSG_SHOW_FUNC_NAME();

#ifdef RAS_DISABLE_SCALEFONT_FOR_DEBUG
	return (DT_void*)newattr;
#endif	

	rasScaledAttr(pwrk, ch, gseq2idx, oriattr, newattr, NULL, NULL);

	return (DT_void*)newattr;
}

DT32_int rasReGetAttrSizeY(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DCW_AttrData *oriattr, DCW_AttrData *newattr)
{
	DT32_int scalemethod, ratio;

DBG_MSG_SHOW_FUNC_NAME();
	
	scalemethod = rasScaleMethod(pwrk, ch, gseq2idx, &ratio);

	switch(scalemethod)
	{
	case RAS_SCALE_BY_XYSCALERATIO:	
		return oriattr->ysize;	// it's always the same with oriattr->ysize when scale by this method, no matter vert or not.
	case RAS_SCALE_BY_RATIO_FILEWIDE:
		return oriattr->ysize;
	case RAS_SCALE_BY_CODERANGE:
		return newattr->ysize;
	case RAS_SCALE_BY_RASSCALERATIO:
	case RAS_SCALE_BY_BINSCALERATIO:
		return newattr->ysize;
	case RAS_NOT_SCALE:
	default:
		break;
	}

	return newattr->ysize;

}

DT32_int rasMoveYbyCodeRange(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DCW_AttrData *oriattr)
{
	DT32_int moveY = 0;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

	//if(	DCW_CODE_NOT_EXIST == DCW_GetAw_1(pwrk->ras_attr,oriattr,(DT32_long)ch))		// use this to check if ch exists in FDL.
	//	return 0;
	if(pfc && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){
		if(!pfc->codeExist)
			return 0;
	}

	if(gDT_MoveArabicY!=0 && isArabicCodeRange(pwrk,ch))
	{
		moveY = gDT_MoveArabicY;
	}else if(gDT_MoveThaiY!=0 && isThaiChars(ch))
	{
		moveY = gDT_MoveThaiY;
	}

	return moveY;
}

// This function will switch between FDL file to check if it needs to be scaled.
// The ratio returned is fdl file wide, and it's based on 64.
DT32_int rasRatiobyFDLFile_1(pLayWrk pwrk, DT16_ushort gidx)
{
	DT32_int ratio;
	DT8_char *ptable;
	ratio = 64;
	ptable= NULL;
	if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, gidx, DLO_LANGTAB_GLOBAL, (DT_void**)&ptable))
	{
		if(ptable)
			ratio = pwrk->fengfuncs.FDL_ReadInt(ptable, 4, 4);
	}

	return ratio;
}

/*************************************************************************************************/
/* Estimate the required working memory */
/* If DcwRaster doesn't support DCW_ASSIGN_GRADATION_MEM, it will use DCW_WKMEM_DEFAULT. */
DT32_int ras_EstimateWkMem(DT32_int sizex, DT32_int sizey, DT32_int grade, DT32_int option)
{
	DT32_int bUseGradMem = 0;

DBG_MSG_SHOW_FUNC_NAME();

#ifdef DCW_ASSIGN_GRADATION_MEM
		if(gDT_Set_Fix_Memory_Size==1){
			bUseGradMem = 1;
		}
#endif

	if(bUseGradMem){
		switch(option){
		case RAS_ESTIMATE_BASE_WKMEM:
			return DCW_EstimateWkMem(sizex, sizey, grade, DCW_WKMEM_BASE);
		case RAS_ESTIMATE_GRAD_WKMEM:
			return DCW_EstimateWkMem(sizex, sizey, grade, DCW_WKMEM_GRAD);
		case RAS_ESTIMATE_DEFT_WKMEM:
		default:
			return DCW_EstimateWkMem(sizex, sizey, grade, DCW_WKMEM_DEFAULT);
		}	
	}else{
		switch(option){
		case RAS_ESTIMATE_GRAD_WKMEM:
			return 0;
		case RAS_ESTIMATE_BASE_WKMEM:
		case RAS_ESTIMATE_DEFT_WKMEM:
		default:
			return DCW_EstimateWkMem(sizex, sizey, grade, DCW_WKMEM_DEFAULT);
		}
	}
}

/* Set the initial data to create a Digitype FDL font data. */
DT32_int ras_initFont(DT_void *pattr, DT8_char *fontdata, DT32_long fWkMemsize, DT8_char *fWkMem, DT_void *pwrk)
{
  /* Example of gray table. 6 kinds of gray color value sequence. */
  const DT8_uchar GrayTab[7][16] =
  {
	{0, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
	{0, 1, 26, 51, 76, 100, 123, 144, 165, 184, 202, 217, 229, 241, 247, 249},
	{0, 1, 22, 42, 63, 83,  102, 121, 139, 157, 174, 189, 203, 217, 228, 237},
	{0, 1, 17, 33, 49, 65,  81,   97, 113, 129, 145, 161, 177, 193, 209, 225},
	{0, 1, 13, 24, 35, 48,  60,   74,  87, 102, 116, 133, 151, 169, 190, 213},
	{0, 1,  8, 15, 22, 30,  39,   50,  61,  74,  88, 105, 125, 145, 171, 201},
	{0, 1,  2,  3,  4,  5,   6,    7,   8,   9,  10,  11,  12,  13,  14,  15}
  };

	DT32_int ret, grayflags=0;
	DCW_FontInfo fdlinfo;
	DT32_int i, tmpval;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	DCW_AttrData *attr=(DCW_AttrData *)&rasattr->attr;
	pLayWrk playwrk = (pLayWrk)pwrk;

DBG_MSG_SHOW_FUNC_NAME();

	rasattr->pwrk = (pLayWrk)pwrk;

	/* Check if the font data is valid or not. */
	ret = DCW_GetFontInfo(fontdata,&fdlinfo);
	if(!ret) return DLO_BAD_FONTDATA;
	if(fdlinfo.ctmode != DCW_Code_Ucs ) return DLO_INVALID_FDL_CODEMODE;

	/* Prepare the DCW_AttrData */
	if(playwrk->grade == DLO_GRAY_16){
		grayflags = DCW_MODE_GRAY16;
	}else if(playwrk->grade == DLO_GRAY_256){
		grayflags = DCW_MODE_GRAY256;
	}else if(playwrk->grade == DLO_GRAY_MONO){
		grayflags = DCW_MODE_MONOCHROME;
	}

	attr->vert        = playwrk->vert;
	attr->xsize       = playwrk->xsize;
	attr->ysize       = playwrk->ysize;
	attr->grade       = grayflags;//playwrk->grade;
	attr->f_edge      = playwrk->f_edge;
	attr->w_edge      = playwrk->w_edge;
	attr->italic      = (playwrk->italic > playwrk->xsize)?playwrk->xsize:playwrk->italic;
	attr->p_underline = playwrk->p_underline;
	attr->w_underline = playwrk->w_underline;	// Be careful of ras.xbyte if w_underline isn't 0
	attr->e_underline = playwrk->e_underline;
	attr->fontdata    = (DT8_char*)fontdata;
	attr->WkMem       = fWkMem;
	attr->WkMemSize   = fWkMemsize;
	tmpval = DLO_FONT_MAXSIZE+DLO_STYLE_MAX_EDGE_WIDTH-attr->xsize-ras_getExten(pattr);
	if(attr->e_underline > tmpval)
		attr->e_underline = tmpval;

	attr->w_edge266	  = playwrk->w_edge266;

	/* If the GRAY_16 used, fill the gcolor with the first color sequence (a linear one) in GrayTab. */
	/* You can choose another color sequence, such as GrayTab[1][i], or GrayTab[2][i]....			 */
	if(attr->grade&DCW_MODE_GRAY16){
	  if(!playwrk->gcolor || playwrk->gcolor[0]!=17){
	    attr->gcolor[0] = 16;
		switch(playwrk->grade_values){
		case DLO_GRADE_LINEAR_0X00_0XFF:
			for(i=0;i<16;i++){
	  			attr->gcolor[i+1] =  GrayTab[0][i];
			}
			break;
		case DLO_GRADE_INDEX_0X00_0X0F:
		default:
			for(i=0;i<16;i++){
	  		  attr->gcolor[i+1] =  GrayTab[6][i];
			}
		}
	  }else{
		DT_memcpy(attr->gcolor,playwrk->gcolor,playwrk->gcolor[0]+1);
	  }
	}

	ret = DCW_Create(attr);
	if(ret==DCW_NOT_ENOUGH_WKMEM){
		return DLO_NOT_ENOUGH_ENGINEWKMEM;
	}else if(ret!=DCW_SUCCESS){
		return DLO_FONTSTYLE_ERROR;
	}
	return ret;
}

DT32_int ras_uninitFont( DT_void *pattr )
{
DBG_MSG_SHOW_FUNC_NAME();

	return DLO_SUCCESS;
}

/* This function doesn't deal with font-style, such as: bold, outline, italic, underline... */
/* pattr:	a pointer to DCW_AttrData.														*/
/* ch:		the character to be draw.														*/
/* bmpw:	the width (pixels) of bmp.														*/
/* bmph:	the height (pixels) of bmp.														*/
/* (x0,y0):	To draw the glyph from this position(left-top) in the bmp.						*/
/* xbytes:  bytes in each line of the bmp buffer. 4-bytes aligned for gray bmp mode.		*/
/* bmp:		the buffer to be draw on. bmp's address must be times of 4. ((int)bmp&3)==0.	*/
/* flagxs:	reserved for use in the future.													*/
/*			2008.05.27: The reserved 9th parameter changed from (int flagxs) to (void *op).	*/
/* mode:	DLO_LAYOUT_BYTE or DLO_LAYOUT_BIT												*/
/*------------------------------------------------------------------------------------------*/
/* 2008.05.27: The reserved 9th parameter changed from (int flagxs) to (void *op).			*/
/* It can be used for overwriting a specified part in a glyph.								*/
extern DT_void *DT_malloc_remained(DT_size_t *size);
extern DT_void DT_free_remained(DT_void *memblock);
extern DT_void DT_bitset(DT_void *bmp, DT_size_t offset, DT8_uchar num, DT_size_t bitscnt);
DT32_int ras_getCharbmp(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int bmpw, DT32_int bmph, DT32_int x0, DT32_int y0, DT32_int xbytes, DT8_uchar *bmp, DT_void *op, DT32_int mode)
{
	DT32_int i, j, awFDL, start, ret=0;
	DT32_int fxbyte=0, nH=0, nW=0, orgx=0, orgy=0, ext=0; 
	DCW_RasterData ras;
	DT8_uchar val=0, bRemainGradMem;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData tmpattr = rasattr->attr;	// copy the origin attr to the new(temp) one
	DCW_AttrData *attr =  (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, -1, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
	bmpGlyfOperate *go=NULL;
	DT32_int WkMemsz = pwrk->engWkMemsz;
	DT8_char *WkMem = NULL;
	DT8_uchar *prect, *pbmp, *orect, *obmp;
	DT32_int start1, copyh=0, copyw=0, copybytes=0;	// copybytes is used when Monochrome, means the real bytes have to be copied.
	pDT_FontMgr_wrk	pmgrwrk=((DT_Font*)(pwrk->cur_DT_Font))->fontmgr;
	DT32_ulong *rect=NULL;	// for speed up cache
	pDT_Fontwrk pdtfwrk = (pDT_Fontwrk)(pwrk->pdtfwrk);
	CacheUnit *cachebmp=NULL;
	DT16_ushort style, others;
//	DT32_int offdownX, offdownY, offRatio;
	DT32_int leading, bottomh, normalh, realh;	/* the real height of the bmp for the text. while bmph means the bmp buffer's height.	*/
	DT32_int edge_l, edge_r, edge_t, edge_b;
	DT32_long	gmemsz;
	DT_size_t	xstart;
	DT_BOOL	bHicpy = DT_FALSE;
	DT_void* (*DT_bmpcpyfunc)( DT_void *dest, const DT_void *src, DT_size_t count );
//	Font_LRSB	fsb;

DBG_MSG_SHOW_FUNC_NAME();

	if(op){	
		go = (bmpGlyfOperate *) op; 
	}

	//aw = DCW_GetAw_1(pattr,attr,ch); //aw = DCW_GetAw(attr,ch); /* Do this in DCW_Raster_1() */

	/* check cache */
	if( pdtfwrk->usedcachearr && pdtfwrk->usedcachearr->CacheSet && pdtfwrk->usedcachearr->Init_FontCache &&
		attr->xsize <= pdtfwrk->usedcachearr->CacheSet->condition.max_fontsize &&
		attr->ysize <= pdtfwrk->usedcachearr->CacheSet->condition.max_fontsize){
	  if( 0==attr->italic && attr->f_edge==DCW_EDGE_NORMAL &&  
	  	  0==attr->w_underline && attr->grade!=DCW_MODE_MONOCHROME)
	  {
		style = MakeCacheStyleValue((DT16_ushort)((DT_Font*)(pwrk->cur_DT_Font))->fid,
										(DT16_ushort)attr->grade, (DT16_ushort)pwrk->grade_values, (DT16_ushort)pwrk->vert);
		others= MakeCacheOthersValue();
		cachebmp = GetFromCache(pdtfwrk->usedcachearr, ch, (DT16_short)attr->xsize, (DT16_short)attr->ysize, style, others);
		if(!cachebmp && pwrk->altfontcnt>0){
			style = MakeCacheStyleValue((DT16_ushort)((DT_Font*)(pwrk->alt_DT_Font))->fid,
										(DT16_ushort)attr->grade, (DT16_ushort)pwrk->grade_values, (DT16_ushort)pwrk->vert);
			cachebmp = GetFromCache(pdtfwrk->usedcachearr, ch, (DT16_short)attr->xsize, (DT16_short)attr->ysize, style, others);
		}
		if(cachebmp){
				ras.fontidx = ch;
				CalculateFontRect(attr,&fxbyte,&nH,&nW,&orgx,&orgy,&ext);
				fxbyte = (DT32_int)cachebmp->width;
				nH     = (DT32_int)cachebmp->height;
				ras.x0 = (DT32_int)cachebmp->extra.body[0];
				ras.y0 = (DT32_int)cachebmp->extra.body[1];
				ras.xs = (DT32_int)cachebmp->extra.body[2];
				ras.ys = (DT32_int)cachebmp->extra.body[3];
				rect   = (DT32_ulong*)cachebmp->data;
				awFDL  = DCW_GetAw_1(pattr,attr,ch,gseq2idx,RAS_OPTION_EXIST);
		}
	  }
	}

  if(!cachebmp){
	CalculateFontRect(attr,&fxbyte,&nH,&nW,&orgx,&orgy,&ext);

//	if(pmgrwrk->tmpbufsize<fxbyte*nH){
//			return DLO_TEMPBUF_NOT_ENOUGH;
//	}
	rect = (DT32_ulong*)pmgrwrk->tempbuf;	/* This address should be times of 4. */

	{
		// FIXME: It's decided by code range now, but it should be decided by the scale ratio and scale method.
		DT32_int bufsz, extrah;
		Font_LRSB lrsb;
// 		DT32_int max_bold, max_bold_italic;
//		max_bold = gDT_FONT_MAXSIZE+DT_STYLE_MAX_EDGE_WIDTH*2;
//		max_bold_italic = gDT_FONT_MAXSIZE+gDT_FONT_MAXITALIC+DT_STYLE_MAX_EDGE_WIDTH*2;
		extrah = 0;
		if(pwrk->vert){
			// FIXME: Calculate this according to LSB and RSB
			if(isIndicsDevanagariChars(ch)){		// Hindi has chars which x0<0 or y0<0, in order to not crash it needs to
													// move the pointer downer to reserve 1/2-height spaces for DcwRaster. 
													// rect buffer (pmgrwrk->tempbuf) must be large enough.
				//extrah = nH/2;
				pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,ch,gseq2idx,DLO_CHARATTR_FONT_LRSB,&lrsb);
				if(lrsb.nsLsb < 0){
					extrah = (attr->ysize*DTAbs(lrsb.nsLsb)+999)/1000;
				}
				//else									// 20110804: marked by Jacky: not required (lrsb include this value) to reudce memory
				//	extrah = (attr->ysize*50+999)/1000;	// connection issue
			}else{ //if(isArabicCodeRange(pwrk,ch)){
				extrah = (attr->ysize*50+999)/1000;		// Arabic's Final & Medial shape have minus y0.
														// They will have LSB of about -50.
			}
//			if(nH > max_bold_italic){
//				nH = max_bold_italic;
//			}
//			if(fxbyte > max_bold){
//				fxbyte = max_bold;
//			}
		}else{
			if(isArabicCodeRange(pwrk,ch) || isIndicsDevanagariChars(ch)){
				extrah = 1;		// might be minus lsb, reserve a line to avoid memory error.
			}

//			if(nH > max_bold){
//				nH = max_bold;
//			}
//			if(fxbyte > max_bold_italic){
//				fxbyte = max_bold_italic;
//			}
		}

		bufsz = (fxbyte*(nH+extrah)+3)/4*4 + 1;	// 20110928: +1 to ensure that all required area will be set to 0, 
												// especially for the case 0!=fxbyte&3 && extrah!=0.
		if(pmgrwrk->tmpbufsize<bufsz){
//			return DLO_TEMPBUF_NOT_ENOUGH;
			bufsz = pmgrwrk->tmpbufsize;
		}
		DT_memset(rect,0,bufsz);
		//rect += fxbyte*extrah / sizeof(DT32_ulong);
		rect += (fxbyte*extrah+3) / sizeof(DT32_ulong);	// 20110928: ensure it's 4 bytes aligned and the offset won't be 0, 
														// so there won't be garbage pixels.
	}

	ras.fontidx = ch;
	ras.x0 = orgx;
	ras.y0 = orgy;
	ras.xs = 0;
	ras.ys = 0;
	ras.xbyte = fxbyte;
	ras.bitmap = (DT8_char*)rect;
	ras.MemSize = 0;
	ras.hint = (attr->grade==DCW_MODE_GRAY256)? 1 : pwrk->hinting;	//Force no hinting for Gray256, Jacky_20101104

	bRemainGradMem = 0;
#ifdef DCW_ASSIGN_GRADATION_MEM
	if(gDT_Set_Fix_Memory_Size==1){
		bRemainGradMem = 1;
	}
#endif
	
	ras.GradMemUsed = 0;
	if(bRemainGradMem){
		if(pwrk->engGradMemsz <= 0){
			gmemsz = DCW_EstimateWkMem(attr->xsize, attr->ysize, attr->grade, DCW_WKMEM_GRAD);
			gmemsz = DT_ALLOC_SIZE(gmemsz);
			ras.GradMemSize = gmemsz;			// force ras.GradMemSize not too large for performance concern.
		}else{	// use previous
			ras.GradMemSize = pwrk->engGradMemsz;
			gmemsz = pwrk->engGradMemsz;	//gmemsz = DT_ALLOC_SIZE(pwrk->engGradMemsz);
		}
		ras.GradMem	 = DT_malloc_remained((DT_size_t*)&gmemsz);		// gmemsz will be changed in this function call.
		if(!ras.GradMem){
			return DLO_ENGINEWKMEM_ERR;
		}
		if(gmemsz < ras.GradMemSize){
			ras.GradMemSize = gmemsz;
		}

		do{
		  /* Please ensure DCW_Raster_1() will be called here only, or might be something wrong of Cache.  */
		  ret = DCW_Raster_1(pattr,&awFDL,attr,&ras);	//ret = DCW_Raster(attr,&ras);
		  if(DCW_NOT_ENOUGH_WKMEM==ret){
			ras.GradMemSize += DT_ALLOC_SIZE(DLO_WKMSIZE_STEP*4);	//DLO_WKMSIZE_STEP;
			if(gmemsz < ras.GradMemSize){
			  return DLO_ENGINEWKMEM_ERR;
			}
			
			// Note_By_Jacky_20101213: Maybe we can resize rtdata to enlarge GradMem to finish the draw.
		  }else if(ret < DCW_SUCCESS){
			  //return 0;		// Modified_By_Jacky_20101213:
			  if(ret == DCW_NOT_ENOUGH_FONTBOXMEM)
				  return DLO_TEMPBUF_NOT_ENOUGH;
			  return DLO_FONTSTYLE_ERROR;	// Other errors. Should not get into here. All other errors should be intercepted before.
		  }
		}while(DCW_NOT_ENOUGH_WKMEM==ret);

		// Raster succeed. Record the GradMem info.
		pwrk->engGradMem = ras.GradMem;
		pwrk->engGradMemsz = ras.GradMemSize;
		if(pwrk->engGradMaxUsed < ras.GradMemUsed){
			pwrk->engGradMaxUsed = ras.GradMemUsed;
		}

		DT_free_remained(ras.GradMem);
		pwrk->engGradMem = NULL;
		pwrk->engGradMemsz = 0;
	}else{
		ras.GradMemSize = 0;
		ras.GradMem		= NULL;
		do{
		  /* Please ensure DCW_Raster_1() will be called here only, or might be something wrong of Cache.  */
		  ret = DCW_Raster_1(pattr,&awFDL,attr,&ras);	//ret = DCW_Raster(attr,&ras);
		  if(DCW_NOT_ENOUGH_WKMEM==ret){
			WkMemsz += DLO_WKMSIZE_STEP*4;		//DLO_WKMSIZE_STEP;
			//WkMem = (DT8_char*) DT_realloc(pwrk->engWkMem,DT_ALLOC_SIZE(WkMemsz));	//Jacky_20101025_for_Performance
			if(pwrk->engWkMem){
				DT_free(pwrk->engWkMem);
			}
			WkMemsz = DT_ALLOC_SIZE(WkMemsz);
			WkMem = (DT8_char*) DT_malloc(WkMemsz);
			if(!WkMem){
			  //return 0;		// Modified_By_Jacky_20101213:
			  return DLO_ENGINEWKMEM_ERR;		
			}
			DT_memset(WkMem,0,WkMemsz);				//Considering to clear the structure area only. (no gradation memory area.)
			pwrk->TotalWkmsize = pwrk->TotalWkmsize - pwrk->engWkMemsz + WkMemsz;
			pwrk->engWkMem = WkMem;
			pwrk->engWkMemsz = WkMemsz;
			//pwrk->TotalWkmsize += DLO_WKMSIZE_STEP;
			attr->WkMem       = pwrk->engWkMem;
			attr->WkMemSize   = pwrk->engWkMemsz;
			ret = DCW_Create(attr);
		  }else if(ret < DCW_SUCCESS){
			  //return 0;		// Modified_By_Jacky_20101213:
			  if(ret == DCW_NOT_ENOUGH_FONTBOXMEM)
				  return DLO_TEMPBUF_NOT_ENOUGH;
			  return DLO_FONTSTYLE_ERROR;	// Other errors. Should not get into here. All other errors should be intercepted before.
		  }
		}while(DCW_NOT_ENOUGH_WKMEM==ret);

		pwrk->engGradMem = NULL;
		pwrk->engGradMemsz = 0;
		pwrk->engGradMaxUsed = 0;
	}
	fxbyte = ras.xbyte;	// 20110804: Jacky added for ras.xbyte might be modified to fit the memory limitation of rect.
  }

	if(awFDL==DCW_CODE_NOT_EXIST){
		if(pwrk->iconfontcnt>0 && pdtfwrk->bRasterOulBold==0){
			return pwrk->iconfuncs.getCharbmp(pwrk->icon_attr,ch,gseq2idx,bmpw,bmph,x0,y0,xbytes,bmp,op,mode);
		}
		//return 0;		// Modified_By_Jacky_20101213:
		return DLO_EMPTY_FONT;
	}

	edge_l = edge_r = edge_t = edge_b = 0;
	pwrk->fengfuncs.getEdge(pwrk->ras_attr, &edge_t, &edge_b, &edge_l, &edge_r);
	leading	= (pwrk->linemoveYup<0)?DTAbs(pwrk->linemoveYup):0;
	bottomh	= pwrk->linemoveYdn;

	x0 += pwrk->lobuf->ltpos.x;
	y0 += pwrk->lobuf->ltpos.y;
	if(pwrk->vert){
		realh	= pwrk->lobuf->bmpwidth;
		normalh = realh - leading - edge_l - edge_r - bottomh;
		if(pwrk->maxdifH>/*normalh*/pwrk->xsize+edge_l+edge_r)
			x0 -= CalcOffsetY_forbmph(pwrk, pwrk->xsize+edge_l+edge_r, 0, pwrk->maxdifH);

	}else{
		realh	= pwrk->lobuf->bufsize/Calxbytes(pwrk, pwrk->lobuf->bmpwidth);
		normalh = realh - leading - edge_t - edge_b - bottomh;
		if(pwrk->maxdifH>/*normalh*/pwrk->ysize+edge_t+edge_b)
			y0 += CalcOffsetY_forbmph(pwrk, pwrk->ysize+edge_t+edge_b, 0, pwrk->maxdifH);
	}
	
	if(pwrk->bidirule==DLO_BIDI_DCWRULE && pwrk->lobuf->writedir==DLO_RIGHTTOLEFT){	//Added_By_Jacky_20101201: for R2L && italic
		if(pwrk->vert){
			y0 -= ext;
			if(y0<0)
				y0 = 0;
		}else{
			x0 -= ext;			//pwrk->fengfuncs.getAexten(pattr, ch);
			if(x0<0) 
				x0 = 0;	//for safety concern
		}
	}

	// RAS_SCALE_BY_XYSCALERATIO copies the upper part of rect when vert==0, but not works when vert==1.
	// It needs to copy the right part when vert==1. This adjustment will compensate for that! 
	// Note that x0 might be minus after this! But the following calculation or ras.x0 must cover it.
	// If x0+ras.x0 is still <0, please check the FDL font data. 
	if(pwrk->vert){
		DT32_int rto;
		if(RAS_SCALE_BY_XYSCALERATIO==rasScaleMethod(pwrk,ch,gseq2idx,&rto)){
			x0 -= attr->xsize - rasReGetAttrSizeY(pwrk,ch,gseq2idx,&rasattr->attr,attr);
		}
	}


	  /* Clear the pixels in rect if needed, Ex: 0x0E10+0x0E39						*/
	  /* Do not clear the pixels in the return buffer to avoid problems when italic.*/
	  if(go){
		/* Only DCW_SETBKZERO of go->operate will happen now. Do not copy the pixels. */
		  if(DCW_SETBKZERO==go->operate){
			  if(pwrk->vert){
				ras.x0 = go->lenth;
				if(ras.x0+ras.xs>nW){
					ras.xs = nW - ras.x0;
				}
			  }else{
				nH = go->gpoff.y;
				if(ras.y0+ras.ys>nH){
					ras.ys = nH - ras.y0;
				}
			  }
		  }
	  }

	if( mode & DLO_LAYOUT_BYTE){
	  if(attr->grade==DCW_MODE_GRAY16 || attr->grade==DCW_MODE_GRAY256){
		/* calculate by all the scaled EM square */
		copyh = (bmph-y0)<nH?(bmph-y0):nH;
		copyw = (xbytes-x0)<(fxbyte)?(xbytes-x0):(fxbyte);

		/* calculate by the font body */
		copyh = (ras.y0+ras.ys)>copyh ? (copyh-ras.y0)/*(ras.ys-(copyh-ras.y0))*/ : ras.ys;	/* Jacky_20100817 */
		copyw = (ras.x0+ras.xs)>copyw ? (copyw-ras.x0)/*(ras.xs-(copyw-ras.x0))*/ : ras.xs; /* Jacky_20100817 */
		if(isArabicCodeRange(pwrk,ch) || isIndicsDevanagariChars(ch))
		{
			bHicpy = DT_TRUE;
		}
		if(copyw<=0 || copyh<=0){	/* copyw<ras.x0 or copyh<ras.y0, no need to copy. */
			return DLO_SUCCESS;
		}
		/* Point to the ras.x0 & ras.y0 to draw */
		if(0 > x0+ras.x0 )
		{
			ras.x0 += 0 - (x0+ras.x0);
			copyw  -= 0 - (x0+ras.x0);
		}
		if(0 > y0+ras.y0)				// do not copy the pixels which y pos are <0 to avoid crash. // Jacky_20110607
		{
			ras.y0 += 0 - (y0+ras.y0);
			copyh  -= 0 - (y0+ras.y0);
		}
		start = (y0+ras.y0)*xbytes + (x0+ras.x0);	/* for bmp, pbmp use	*/
		start1= (ras.y0)*fxbyte + ras.x0;			/* for rect, prect use	*/
		pbmp  = bmp + start;
		prect = ((DT8_uchar*)rect) + start1;
		
		//if(pwrk->italic == 0 && pwrk->spacing >= 0 && attr->f_edge==DCW_EDGE_NORMAL)
		if(bHicpy)
		{
			DT_bmpcpyfunc = DT_bmpHIcpy;
		}
		else if(isUseDT_bmpcpy(pwrk,attr,ch))
		{
			DT_bmpcpyfunc = DT_bmpcpy;
		}else
		{
			DT_bmpcpyfunc = DT_bmpORcpy;
		}

		i = 0;
		// This for loop is used to avoid coping illegally. skip the pixels which are before the pointer bmp.
//		{
//			DT32_int bw, bh;	// the pixels(bw), lines(bh) before bmp. 
//			bw = x0+ras.x0;
//			bh = y0+ras.y0;
//			if(bw<0 || bh<0)	// skip pixels
//			{
//				for(; i < copyh; i++)
//				{
//					if(pbmp > bmp)
//						break;			// jump to copy the pixels
//
//					if(bh < 0)
//					{
//						start  += xbytes;
//						start1 += fxbyte;
//						prect  = ((DT8_uchar*)rect) + start1;
//						pbmp   = bmp  + start;
//						bh++;
//						continue;
//					}
//					if(bw < 0)
//					{
//						DT32_int cpw;
//						cpw = copyw - DTAbs(bw);
//						if(cpw > 0)
//						{
//							DT_bmpcpyfunc(pbmp+DTAbs(bw),prect+DTAbs(bw),cpw);
//						}
//						start  += xbytes;
//						start1 += fxbyte;
//						prect  = ((DT8_uchar*)rect) + start1;
//						pbmp   = bmp  + start;
//					}
//
//				}
//			}
//		}
		for(; i < copyh; i++)
		{
				DT_bmpcpyfunc(pbmp,prect,copyw);
				start  += xbytes;
				start1 += fxbyte;
				prect  = ((DT8_uchar*)rect) + start1;
				pbmp   = bmp  + start;
		}
	  }
	}else if(mode & DLO_LAYOUT_BIT){	/* It can speedup if needed. */
		// Following are re-implemented by Jacky_20110322 from v2.7.0
		DT32_int rectoffbytes, rectoffbits;	// now endure ras.x0 is minus, but ras.y0<0 isn't allowed.
		DT32_int negpart, pospart;			// when ras.x0 < 0, its the negative part(ras.x0) and positive part(ras.xs-DTAbs(ras.x0))
		if(op && pwrk->vert){	// Set the bits to zero, because following algorithm will copy the bits from x=0 when vert.
								// If vert=0, the copyh won't copy the bits, so no need to set the bits.
			DT_size_t leftbits=0;
			leftbits = go->gpoff.x & 7;		// go->gpoff.x should always be 0, so leftbits is also 0.
			for(i=go->gpoff.y;i<go->gpoff.y+go->height;i++){
				prect = ((DT8_uchar*)rect) + i*fxbyte + (go->gpoff.x>>3);
				DT_bitset(prect,leftbits,0,go->lenth);
			}
		}

	  	/* calculate by all the scaled EM square */
		copyh = (bmph-y0)<nH?(bmph-y0):nH;
		copyw = (xbytes*8-x0)<(fxbyte*8)?(xbytes*8-x0):(fxbyte*8);					// the space left for copyw

		/* calculate by the font body */
		if(ras.x0 < 0){
			negpart = DTAbs(ras.x0);
			pospart = ras.xs - DTAbs(ras.x0);
		}else{
			negpart = 0;
			pospart = ras.x0 + ras.xs;
		}
		copyh = (ras.y0+ras.ys)>copyh ? (copyh-ras.y0) : ras.ys;
		//copyw = (DTAbs(ras.x0)+ras.xs)>copyw ? copyw : (DTAbs(ras.x0)+ras.xs);	// always copy from each lines' start pos of rect.
		copyw = (pospart>copyw) ? copyw : pospart;
		if(x0>0){
			if(x0<negpart){
				copyw += x0;
			}else{
				copyw += negpart;
			}
		}	// the situation when x0 < 0 should be compensated before.

		/* Bit Mode won't have the gray-connection issue. */
		if(copyw<=0 || copyh<=0){	/* copyw<ras.x0 or copyh<ras.y0, no need to copy. */
			return DLO_SUCCESS;
		}
		/* Point to the ras.x0 & ras.y0 to draw */
#define DT_FLOOR_BYTES(x)	( (x) < 0 ? (((x)-7)/8) : ((x)>>3) )
		rectoffbytes = 0;	rectoffbits = 0;	
		if(ras.x0 < 0){
			x0 += ras.x0;
			rectoffbytes = DT_FLOOR_BYTES(ras.x0);
			rectoffbits  = (DTAbs(rectoffbytes)*8) - DTAbs(ras.x0);
			x0 -= rectoffbits;
			copyw += rectoffbits;
		}

		start = (y0+ras.y0)*xbytes + DT_FLOOR_BYTES(x0);	/* for bmp, pbmp use	*/
		start1= (ras.y0)*fxbyte + rectoffbytes;	/* for rect, prect use	*/
		obmp = pbmp  = bmp + start;
		orect= prect = ((DT8_uchar*)rect) + start1;

		// This for loop is used to avoid coping illegally. skip the pixels which are before the pointer bmp.
		i = 0;
		{
			DT32_int bw, bh;	// the pixels(bw), lines(bh) before bmp. 
			bw = x0+ras.x0;
			bh = y0+ras.y0;
			if(bw<0 || bh<0)	// skip pixels
			{
				for(; i < copyh; i++)
				{
					if(pbmp > bmp)
						break;			// jump to copy the pixels

					if(bh < 0)
					{
						obmp  += xbytes;	pbmp = obmp;
						orect += fxbyte;	prect= orect;
						bh++;
						continue;
					}
					// FIXME: Needs to deal with the bits & bytes, comment it here now. some garbage pixels might appear.
//					if(bw < 0)
//					{
//						DT32_int cpw;
//						cpw = copyw - DTAbs(bw);
//						if(cpw > 0)
//						{
//							//DT_bmpcpyfunc(pbmp+DTAbs(bw),prect+DTAbs(bw),cpw);
//						}
//						obmp  += xbytes;	pbmp = obmp;
//						orect += fxbyte;	prect= orect;
//					}
				}
				// 2012-05-04: Jacky added to avoid crashes.	// 2012-12-17: TODO: is it required here?
				//if(bw < 0 && pbmp < bmp){
				//	DT32_int diffbytes	= ((DT32_ulong)bmp - (DT32_ulong)pbmp);
				//	DT32_int diffbits	= diffbytes * 8;
				//	obmp	+= diffbytes;		pbmp = obmp;
				//	orect	+= diffbytes;		prect= orect;
				//}
			}
		}

		// Check if there are pixels after the pointer bmp.		// 2012-12-17: TODO: is it required here?
		//{
		//	DT8_uchar	*bmplast = bmp + bmph*xbytes;
		//	DT8_uchar	*pbmplast= obmp + (copyh-1)*xbytes + x0/8 + copyw;
		//	DT32_long	diffs = (DT32_long)bmplast - (DT32_long)pbmplast;
		//	if(diffs < 0)
		//		copyh += diffs/xbytes;
		//}

		xstart = x0&7;	/* xbytealign=0: x0 is at byte start position */
		if(!xstart){
			copybytes = (copyw+7)>>3;
			for(j=0;j<copyh;j++){
				for(i=0;i<copybytes;i++){
					*pbmp++ |= *prect++;
				}
				obmp  += xbytes;	pbmp = obmp;
				orect += fxbyte;	prect= orect;
			}
		}else{
			for(j=0;j<copyh;j++){
				for(i=0;i+7<copyw;i+=8){
					val = *prect++;
					*pbmp++ |= (val>>xstart);
					*pbmp |= (val<<(8-xstart));
				}
				if( i<copyw){			// The last bytes need to check the boundary.
					val = *prect;
					if(val){
						*pbmp++ |= (val>>xstart);
						if(((DT_size_t)copyw&7) > (8-xstart)){
							*pbmp |= (val<<(8-xstart));
						}
					}
				}
				obmp  += xbytes;	pbmp = obmp;
				orect += fxbyte;	prect= orect;
			}			
		}
	}

	return DLO_SUCCESS;				// Modified_By_Jacky_20101213:
}

// Return 0 if ch does NOT exist.
// Return 1 if ch DOES exist.
DT32_int ras_chkGlyphExist( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DT32_int aw=0;
	DT32_long gidx;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	DCW_AttrData *attr=(DCW_AttrData *)&rasattr->attr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)
			return pfc->codeExist;
	}
	
	gidx = ch;
	aw = DCW_GetAw_1(pattr,attr,gidx,gseq2idx,RAS_OPTION_EXIST);	// will check if code exists.
	if(aw==DCW_CODE_NOT_EXIST){
		if(pwrk->iconfontcnt>0){
			return pwrk->iconfuncs.chkGlyphExist(pwrk->icon_attr,ch,gseq2idx);
		}
		return 0;
	}else{
		return 1;
	}

	return 0;
}

/* DO NOT use this function's return value to distinguish if ch exists.	*/
/* Get advanced width of the glyph.										*/
DT32_int ras_getAwidth(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx)
{
	DT32_int aw=0,t=0,d=0,l=0,r=0;
	DT32_long gidx;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData tmpattr;	// set it later for performance	// copy the origin attr to the new(temp) one
	DCW_AttrData *attr;// =  (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, gseq2idx, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW)
			return (pfc->aw==DCW_CODE_NOT_EXIST)?0:pfc->aw+pwrk->spacing;
	}

	tmpattr = rasattr->attr;
	attr = (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, gseq2idx, &rasattr->attr, &tmpattr);

	gidx = ch;
	aw = DCW_GetAw_1(pattr,attr,gidx,gseq2idx,RAS_OPTION_GETAW);
	if(aw==DCW_CODE_NOT_EXIST){
		if(pwrk->iconfontcnt>0){
//			ras_getEdge( pattr, &t, &d, &l, &r );
//			aw = pwrk->iconfuncs.getAwidth(pwrk->icon_attr,ch);
//			if(aw > 0){
//				aw += (l+r);
//				return aw;	/* spacing is added in dif_getAwidth() */
//			}
			return pwrk->iconfuncs.getAwidth(pwrk->icon_attr,ch,gseq2idx);
		}
	}else if(aw <= 0){
		aw = DCW_CODE_NOT_EXIST;	// treat fail as no aw.
	}

	if(pfc){
		pfc->aw = aw;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AW;
	}

	return (aw==DCW_CODE_NOT_EXIST)?0:aw+pwrk->spacing;	/* Jacky_20100824 */
}

DT32_int ras_getAwidth2(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy)
{
DBG_MSG_SHOW_FUNC_NAME();

	/* Not implement yet. Maybe required when supporting vertical writedir. */
	return 0;
}

/* Get height of the specific glyph.*/
/* Return 0: glyph doesn't exist.	*/
DT32_int ras_getAheight( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DT32_int aw=0, height=0, ext=0;
	DT32_long gidx;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData tmpattr;	// set it later for performance	// copy the origin attr to the new(temp) one
	DCW_AttrData *attr;	// =  (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, -1, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
	DT32_int fxbyte=0, nH=0, nW=0;
	DT_Font *altfont = pwrk->alt_DT_Font;
	DT8_char *curfontdata;	// = attr->fontdata;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AH){
			if( pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST 
				&& pfc->codeExist && pfc->existFont==DLO_ICON_DT_FONT 
				&& pfc->ah > pwrk->maxdifH){
				pwrk->maxdifH = pfc->ah;
			}
			return pfc->ah;
		}
	}
	tmpattr = rasattr->attr;
	attr = (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, gseq2idx, &rasattr->attr, &tmpattr);
	curfontdata = attr->fontdata;

	gidx = ch;
	aw = DCW_GetAw_1(pattr,attr,gidx,gseq2idx,RAS_OPTION_EXIST/*RAS_OPTION_GETAW*/);	//use aw to distinguish if ch exists?
	if(aw==DCW_CODE_NOT_EXIST){
		if(pwrk->iconfontcnt>0){
			return pwrk->iconfuncs.getAheight(pwrk->icon_attr,ch,gseq2idx);	// 20111031: Jacky
		}
	}else{
		attr->ysize = rasReGetAttrSizeY(pwrk,ch,gseq2idx,&rasattr->attr,attr);
		CalculateFontRect(attr,&fxbyte,&nH,&nW,0,0,&ext);
		if(pwrk->vert){
			DT32_int rto;
			if(RAS_SCALE_BY_XYSCALERATIO==rasScaleMethod(pwrk,ch,gseq2idx,&rto)){
				height = nH;
				height -= ext;
			}else
				height = nW;
		}else{
			height = nH;
		}
		//if(gDT_Baseline_Descent_Height != 0 || gDT_Baseline_Compensation_Height != 0){
		//	nH += DT_FORCE_MOVE_DOWN_PIXS(attr->ysize) + DT_DESCENT_PIXS(attr->ysize);
		//}
//		pwrk->fengfuncs.getDesignInfo(pattr, ch, DLO_CHARATTR_GET_OFFSETY, &offY);
//		if(pwrk->vert){
//			nW += DT_FORCE_MOVE_DOWN_PIXS(attr->xsize,offY);
//			return nW;
//		}else{
//			nH += DT_FORCE_MOVE_DOWN_PIXS(attr->ysize,offY);
//			return nH;
//		}
	}

	if(pfc){
		pfc->ah = height;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AH;
	}

	return height;
}

DT32_int ras_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DT32_int logh=0, boldw=0, scaleMethod = DLO_NOT_SCALE;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData tmpattr;
	DCW_AttrData *attr;	// =  (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, -1, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk->ratio)		// ratio is assigned only when Prerender_Devanagari() had been called.
		return 0;			// Now, logh is used to adjust Hindi only.

	if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_LOGH){
		return (DT32_int)pfc->logHeight;
	}

	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_LOGHEIGHT, &logh);
	if(logh<=0){
		logh = DLO_BASE_RATIO;	//1000;
	}

	if(logh){
		tmpattr = rasattr->attr;
		attr = (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, gseq2idx, &rasattr->attr, &tmpattr);
		//attr->ysize = rasReGetAttrSizeY(pwrk,ch,gseq2idx,&rasattr->attr,attr);
		//CalculateFontRect(attr,&fxbyte,&nH,&nW,0,0,&ext);
		switch(attr->f_edge){        
		case DCW_EDGE_OUTLINE:
		case DCW_EDGE_BOLD:
			boldw = pwrk->w_edge * 2;
			break;            
		case DCW_EDGE_BOLD_DOWN:
		case DCW_EDGE_BOLD_RIGHT_DOWN:
			boldw = pwrk->w_edge;
			break;
		case DCW_EDGE_NORMAL:
		case DCW_EDGE_BOLD_RIGHT:
		default:
			boldw = 0;
			break;
		}
		if(pwrk->vert){
			DT32_int rto;
			if(pfc && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_SCALE){
				scaleMethod = pfc->scaleMethod;
			}else{
				scaleMethod = rasScaleMethod(pwrk,ch,gseq2idx,&rto);
			}
			if(RAS_SCALE_BY_XYSCALERATIO==scaleMethod){
				logh = DLO_SCALE_LOGHEIGHT2PIX(logh,attr->ysize) + boldw;	// attr->ysize had been scaled.
			}else
				logh = DLO_SCALE_LOGHEIGHT2PIX(logh,attr->ysize) + boldw;	// attr->xsize had been scaled.
		}else{
			logh = DLO_SCALE_LOGHEIGHT2PIX(logh,attr->ysize) + boldw;		// attr->ysize had been scaled.
		}
	}

	if(pfc){
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_LOGH;
		pfc->logHeight = logh;
	}
	return logh;
}

DT32_int ras_getLogt( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DT32_int logt=0, scaleMethod = DLO_NOT_SCALE;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData tmpattr;
	DCW_AttrData *attr;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk->ratio)		// ratio is assigned only when Prerender_Devanagari() had been called.
		return 0;			// Now, logh is used to adjust Hindi only.

	if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_LOGT){
		return (DT32_int)pfc->logTop;
	}

	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_LOGTOP, &logt);
	if(logt<=0){
		logt = 0;
	}

	if(logt){
		tmpattr = rasattr->attr;
		attr = (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, gseq2idx, &rasattr->attr, &tmpattr);

		if(pwrk->vert){
			DT32_int rto;
			if(pfc && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_SCALE){
				scaleMethod = pfc->scaleMethod;
			}else{
				scaleMethod = rasScaleMethod(pwrk,ch,gseq2idx,&rto);
			}
			if(RAS_SCALE_BY_XYSCALERATIO==scaleMethod){
				logt = DLO_SCALE_LOGHEIGHT2PIX(logt,attr->ysize);	// attr->ysize had been scaled.
			}else
				logt = DLO_SCALE_LOGHEIGHT2PIX(logt,attr->ysize);	// attr->xsize had been scaled.
		}else{
			logt = DLO_SCALE_LOGHEIGHT2PIX(logt,attr->ysize);		// attr->ysize had been scaled.
		}
	}

	if(pfc){
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_LOGT;
		pfc->logTop = logt;
	}
	return logt;
}

/* Get height of the glyph.	*/
/* Now, this function is used only when indicating Font Matrix. It's not used actually. */
//DT32_int ras_getHeight( DT_void *pattr )
//{
//	DT32_int fxbyte=0, nH=0, nW=0, offY=0;
//	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
//	DCW_AttrData tmpattr = rasattr->attr;	// copy the origin attr to the new(temp) one
//	DCW_AttrData *attr =  (DCW_AttrData*)rasMakeNewAttr(pwrk, 0x0000, -1, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	attr->ysize = rasReGetAttrSizeY(pwrk,0x0000,-1,&rasattr->attr,attr);
//	CalculateFontRect(attr,&fxbyte,&nH,&nW,0,0,0);
//	//if(gDT_Baseline_Descent_Height != 0 || gDT_Baseline_Compensation_Height != 0){
//	//	nH += DT_FORCE_MOVE_DOWN_PIXS(attr->ysize) + DT_DESCENT_PIXS(attr->ysize);
//	//}
//
//	//nH += DT_FORCE_MOVE_DOWN_PIXS(attr->ysize,offY);
//	return nH;
//}

/* Get height of the glyph.	*/
/* Now, this function is used only when indicating Font Matrix. It's not used actually. */
/* 2012-02-29 by Jacky: The value is independent by font size (no scale ratio applied). */
DT32_int ras_getHeight( DT_void *pattr )
{
	DT32_int nH=0;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData *attr = (DCW_AttrData *)&rasattr->attr;

DBG_MSG_SHOW_FUNC_NAME();

	CalculateFontRect(attr,NULL,&nH,NULL,NULL,NULL,NULL);

	return nH;
}

/* Get width of the glyph.	*/
//DT32_int ras_getWidth( DT_void *pattr )
//{
//	DT32_int fxbyte=0, nH=0, nW=0;
//	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
//	DCW_AttrData tmpattr = rasattr->attr;	// copy the origin attr to the new(temp) one
//	DCW_AttrData *attr =  (DCW_AttrData*)rasMakeNewAttr(pwrk, 0x0000, -1, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	CalculateFontRect(attr,&fxbyte,&nH,&nW,0,0,0);
//	return nW;
//}

/* Get width of the glyph.	*/
/* 2012-02-29 by Jacky: The value is independent by font size (no scale ratio applied). */
DT32_int ras_getWidth( DT_void *pattr )
{
	DT32_int nW=0;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData *attr = (DCW_AttrData *)&rasattr->attr;

DBG_MSG_SHOW_FUNC_NAME();

	CalculateFontRect(attr,NULL,NULL,&nW,NULL,NULL,NULL);
	return nW;
}

/* Get how many bytes should be extend of the glyph for special font styles. */
//DT32_int ras_getExten( DT_void *pattr )
//{
//	DT32_int fxbyte=0, nH=0, ext=0;
//	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
//	DCW_AttrData tmpattr = rasattr->attr;	// copy the origin attr to the new(temp) one
//	DCW_AttrData *attr = (DCW_AttrData*)rasMakeNewAttr(pwrk, 0x0000, -1, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	CalculateFontRect(attr,&fxbyte,&nH,0,0,0,&ext);
//	return ext;
//
//}

/* Get how many bytes should be extend of the glyph for special font styles.						*/
/* 2012-02-29 by Jacky: The value is independent by font size (no scale ratio applied).				*/
/* Actually, it is affected by italic only! (w_underline and e_underline should always be 0 here)	*/
DT32_int ras_getExten( DT_void *pattr )
{
	DT32_int ext=0;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData *attr = (DCW_AttrData *)&rasattr->attr;

DBG_MSG_SHOW_FUNC_NAME();

	if (attr->italic>0 || attr->w_underline>0){
      ext = max(attr->italic, (attr->w_underline>0) ? attr->e_underline:0);
	}
	return ext;

}

/* The extents of all glyph in FDL are the same. FDL font glyph is never out of bounding box. */
/* Added by Jacky_20090821 */
//DT32_int ras_getAexten( DT_void *pattr, DT16_ushort ch )
//{
//	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
//	DCW_AttrData tmpattr = rasattr->attr;	// copy the origin attr to the new(temp) one
//	DCW_AttrData *Attr =  (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, -1, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
//	DT32_int ext=0;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	if (Attr->italic>0 || Attr->w_underline>0){
//      ext = max(Attr->italic, (Attr->w_underline>0) ? Attr->e_underline:0);
//	}
//	return ext;
//}

/* The extents of all glyph in FDL are the same. FDL font glyph is never out of bounding box.		*/
/* 2012-02-29 by Jacky: The value is independent by font size (no scale ratio applied).				*/
/* Actually, it is affected by italic only! (w_underline and e_underline should always be 0 here)	*/
DT32_int ras_getAexten( DT_void *pattr, DT16_ushort ch )
{
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData *attr = (DCW_AttrData *)&rasattr->attr;
	DT32_int ext=0;

DBG_MSG_SHOW_FUNC_NAME();

	if (attr->italic>0 || attr->w_underline>0){
      ext = max(attr->italic, (attr->w_underline>0) ? attr->e_underline:0);
	}
	return ext;
}

//DT32_int ras_getVexten( DT_void *pattr, DT16_ushort ch )
//{
//	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
//	DCW_AttrData tmpattr = rasattr->attr;	// copy the origin attr to the new(temp) one
//	DCW_AttrData *Attr =  (DCW_AttrData*)rasMakeNewAttr(pwrk, ch, -1, &rasattr->attr, &tmpattr); //(DCW_AttrData *)&rasattr->attr;
//	DT32_int fxbyte=0, nH_Bold=0, nH_Normal=0, nW_Bold=0, nW_Normal=0, Vext=0;
//	DT32_int edge=Attr->f_edge;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	if(edge!=DCW_EDGE_NORMAL){
//	  CalculateFontRect(Attr,&fxbyte,&nH_Bold,&nW_Bold,0,0,0);
//	  Attr->f_edge = DCW_EDGE_NORMAL;
//	  CalculateFontRect(Attr,&fxbyte,&nH_Normal,&nW_Normal,0,0,0);
//	  Attr->f_edge = edge;
//	  if(pwrk->vert){
//		Vext = nW_Bold - nW_Normal;
//	  }else{
//		Vext = nH_Bold - nH_Normal;
//	  }
//	}
//
//	return Vext;
//}

DT32_int ras_getVexten( DT_void *pattr, DT16_ushort ch )
{
	DT32_int t=0, d=0, l=0, r=0;
	DT32_int wext=0, hext=0;
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DCW_AttrData *attr = (DCW_AttrData *)&rasattr->attr;
	
	ras_getEdge(pattr, &t, &d, &l, &r);
	if(attr->vert){
		return l+r;
	}else{
		return t+d;
	}
}

/* The edge width (difference between Bold and Normal font).*/
/* t:top-edge; d:down-edge; l:left-edge; r:right-edge		*/
/* return: 0:DLO_SUCCESS; <0:Error							*/
DT32_int ras_getEdge( DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r )
{
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	DCW_AttrData *Attr=(DCW_AttrData *)&rasattr->attr;

DBG_MSG_SHOW_FUNC_NAME();

	if(t)	*t=0;
	if(d)	*d=0;
	if(l)	*l=0;
	if(r)	*r=0;
    switch (Attr->f_edge)
    {
    case DCW_EDGE_NORMAL:
        break;
        
    case DCW_EDGE_OUTLINE:
    case DCW_EDGE_BOLD:
		if(t)	*t=Attr->w_edge;
		if(d)	*d=Attr->w_edge;
		if(l)	*l=Attr->w_edge;
		if(r)	*r=Attr->w_edge;
        break;
        
    case DCW_EDGE_BOLD_RIGHT:
		if(r)	*r=Attr->w_edge;
        break;
        
    case DCW_EDGE_BOLD_DOWN:
		if(d)	*d=Attr->w_edge;
        break;
        
    case DCW_EDGE_BOLD_RIGHT_DOWN:
		if(r)	*r=Attr->w_edge;
		if(d)	*d=Attr->w_edge;
		break;
	default:
		break;
	}

	return DLO_SUCCESS;
}

/* Get data */
DT32_long rasFDL_ReadInt(DT8_char *fdl, DT32_long ofs, DT32_int size)
{
	DT8_BYTE *p;
	DT32_long val;
	DT32_int i;

DBG_MSG_SHOW_FUNC_NAME();

	p = (DT8_BYTE*)fdl + ofs + size-1;

	val = *p--;
	for(i=1; i < size; i++, p--)
	{
		val <<= 8;
		val |= *p;
	}

	return val;
}

///* Get fonts design information							*/
//DT32_int ras_getDesignInfo(DT_void *pattr, DT_void *dsninfo)
//{
//#define RASFD_LANGDATA 58
//
//	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
//	DCW_AttrData *attr=(DCW_AttrData *)&rasattr->attr;
//	Font_Design *fds = (Font_Design*)dsninfo;
//	Font_Design fd;
//	DT32_long langoff, langlen, pos;
//	DT16_ushort langcnt, langid;
//	DT32_int i, bskip;
//	DT16_ushort totalh;
//
//	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
//	DT_Font *altfont = pwrk->alt_DT_Font;
//	DT8_char *curfontdata = attr->fontdata;
//	DT8_char *pdata=NULL;
//
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	langoff = rasFDL_ReadInt(curfontdata,RASFD_LANGDATA,4);	
//	if(!langoff){
//		if(pwrk->altfontcnt>0){
//			langoff = rasFDL_ReadInt(altfont->fontdata,RASFD_LANGDATA,4);
//		}
//		if(!langoff){
//			return 0;
//		}else{
//			pdata = altfont->fontdata;
//		}
//	}else{
//		pdata = curfontdata;
//	}
//
//	langcnt = (DT16_ushort)rasFDL_ReadInt(pdata,langoff,2);
//	pos = langoff + 2;
//	for(i=0;i<langcnt;i++){
//		bskip=1;	
//		langid = (DT16_ushort)rasFDL_ReadInt(pdata,pos,2);
//		langlen= rasFDL_ReadInt(pdata,pos+2,4);
//#ifdef THAI_thai
//		if(langid==DLO_LANG_THA){
//		  pos += (2+4);
//		  fd.Thai_Top	= (DT16_ushort)rasFDL_ReadInt(pdata,pos,2);	pos += 2;
//		  fd.Thai_Above	= (DT16_ushort)rasFDL_ReadInt(pdata,pos,2);	pos += 2;
//		  fd.Thai_Base	= (DT16_ushort)rasFDL_ReadInt(pdata,pos,2);	pos += 2;
//		  fd.Thai_Below	= (DT16_ushort)rasFDL_ReadInt(pdata,pos,2);	pos += 2;
//		  fd.Thai_Shift	= (DT16_ushort)rasFDL_ReadInt(pdata,pos,2);	pos += 2;
//		  
//		  totalh = fd.Thai_Top + fd.Thai_Above + fd.Thai_Base + fd.Thai_Below;
//		  fds->Thai_Top		= fd.Thai_Top*attr->ysize/totalh;
//		  fds->Thai_Above	= fd.Thai_Above*attr->ysize/totalh;
//		  fds->Thai_Base	= fd.Thai_Base*attr->ysize/totalh;
//		  fds->Thai_Below	= attr->ysize - (fds->Thai_Top+fds->Thai_Above+fds->Thai_Base);
//		  fds->Thai_Shift	= fd.Thai_Shift*attr->xsize/totalh;
//		  bskip=0;
//		}
//#endif
//		if(bskip)	pos += langlen;
//	}
//
//	return 0;
//}

/* option is the type of DLO_LANGTAB_ID */
/* gidx is used only to distinguish if it's the right FDL file. */
DT32_int ras_getDesignGlobalInfo(DT_void *pattr, DT16_ushort gidx, DT32_int option, DT_void **pdsninfo)
{
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	DCW_AttrData *attr=(DCW_AttrData *)&rasattr->attr;
	DT32_long pos;

	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	DT_Font *altfont = pwrk->alt_DT_Font;
	DT8_char *curfontdata = attr->fontdata;
	//DT8_char *pdata=NULL;
	DCW_CharAttr_Option op;
	DT32_int gseq2idx = -1;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdsninfo){
		return -1;
	}

	*pdsninfo = NULL;
	switch(option){
	case DLO_LANGTAB_GLOBAL:
			op = DCW_CHARATTR_LANGTAB_GLOBAL;
//			pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
//			if(pos >=0){
//				*pdsninfo = (rasattr->attr.fontdata +pos);
//				return 0;
//			}else return -1;
			break;
	case DLO_LANGTAB_HINDI_SUB:
			op = DCW_CHARATTR_LANGTAB_HINDI_SUB;
//			pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
//			if(pos >=0){
//				*pdsninfo = (rasattr->attr.fontdata+pos);
//				return 0;
//			}else return -1;
			break;
	case DLO_LANGTAB_HINDI_POS1:
			op = DCW_CHARATTR_LANGTAB_HINDI_POS1;
//			pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
//			if(pos >=0){
//				*pdsninfo = (rasattr->attr.fontdata+pos);
//				return 0;
//			}else return -1;
			break;
	case DLO_LANGTAB_HINDI_POS2:
			op = DCW_CHARATTR_LANGTAB_HINDI_POS2;
//			pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
//			if(pos >=0){
//				*pdsninfo = (rasattr->attr.fontdata+pos);
//				return 0;
//			}else return -1;
			break;

	case DLO_LANGTAB_HINDI_POS3:
			op = DCW_CHARATTR_LANGTAB_HINDI_POS3;
			break;

	case DLO_LANGTAB_RSB:
			op = DCW_CHARATTR_LANGTAB_RSB;
//			pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
//			if(pos >=0){
//				*pdsninfo = (rasattr->attr.fontdata+pos);
//				return 0;
//			}else return -1;
			break;
	default:
		return -1;
		break;
	}

	/* Don't call DCW_QueryCharAttr_1(), because we need to know which font contains the table we want. */
	pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
	if(pos>0){
		*pdsninfo = curfontdata + pos;
		return 0;
	}else{
//		if(DCW_GetAw(attr,gidx)!=DCW_CODE_NOT_EXIST){
//			// current font contains gidx, no need to check altfont.
//			return -1;
//		}
		if(pfc){
			if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){ 
			}else{
				ras_chkGlyphExist(pwrk->ras_attr,gidx,gseq2idx);
			}
			if(0==pfc->codeExist || (pfc->codeExist && pfc->existFont!=DLO_ALT_DT_FONT))
				return -1;
		}else{
			if(DCW_GetAw(attr,gidx)!=DCW_CODE_NOT_EXIST)
				return -1;
		}
		if(pwrk->altfontcnt>0){
			attr->fontdata = altfont->fontdata;
			pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
			attr->fontdata = curfontdata;
			if(pos > 0){
				*pdsninfo = altfont->fontdata + pos;
				return 0;
			}else{
				return -1;
			}
		}
	}

	return -1;
}


/* Get fonts design information							*/
/* return value: 1: use default, 0: success, <0:error	*/
DT32_int ras_getDesignInfo(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo)
{
	DcwRaster_Attr *rasattr = (pDcwRaster_Attr)pattr;
	pLayWrk pwrk = (pLayWrk)rasattr->pwrk;
	//DCW_AttrData tmpattr = rasattr->attr;	// copy the origin attr to the new(temp) one
	//DCW_AttrData *attr =  (DCW_AttrData*)rasMakeNewAttr(pwrk, gidx, -1, &rasattr->attr, &tmpattr); 
	DCW_AttrData *attr = (DCW_AttrData *)&rasattr->attr;
	DT32_long pos;
	DT16_ushort totalh, diffh;

	DT_Font *altfont = pwrk->alt_DT_Font;
	DT8_char *curfontdata = attr->fontdata;
	DT8_char *pdata=NULL;
	DCW_CharAttr_Option op;
	DT32_int *bRtoChar, *ratio;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(!dsninfo){
		return -1;
	}

	switch(option){		// if the option is gidx related, it will return directly in this switch. others will go through.
	case DLO_CHARATTR_LANGTAB_THAI:
		op = DCW_CHARATTR_LANGTAB_THAI;
		//fds = (Font_Design_Thai*)dsninfo;
		break;
	case DLO_CHARATTR_LANGTAB_ICON:
		op = DCW_CHARATTR_LANGTAB_ICON;
		break;
	case DLO_CHARATTR_LANGTAB_RAS_SCALE:
		op = DCW_CHARATTR_LANGTAB_RAS_SCALE;
		break;
	case DLO_CHARATTR_LANGTAB_BIN_SCALE:
		op = DCW_CHARATTR_LANGTAB_BIN_SCALE;
		break;
	case DLO_CHARATTR_LANGTAB_DESCENT:
		op = DCW_CHARATTR_LANGTAB_DESCENT;
		//fdsl = (Font_Design_Descent*)dsninfo;
		break;
	case DLO_CHARATTR_XYSCALERATIO:
		ratio = (DT32_int*)dsninfo;
		op = DCW_CHARATTR_XYSCALERATIO;
		*ratio = DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
		if(0 == *ratio)
			*ratio = DCW_BASE_RATIO;
		return 0;
	case DLO_CHARATTR_ISXYSCALE_CHAR:
		bRtoChar = (DT32_int*)dsninfo;
		op = DCW_CHARATTR_ISXYSCALE_CHAR;
		*bRtoChar= DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
		if(DCW_BASE_RATIO == *bRtoChar)
			*bRtoChar = 0;
		if(*bRtoChar)
			*bRtoChar = 1;
		return 0;
	case DLO_CHARATTR_RASSCALERATIO:
		ratio = (DT32_int*)dsninfo;
		op = DCW_CHARATTR_RASSCALERATIO;
		*ratio = DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
		if(0 == *ratio)
			*ratio = DCW_BASE_RATIO;
		return 0;
	case DLO_CHARATTR_ISRASSCALE_CHAR:
		bRtoChar = (DT32_int*)dsninfo;
		op = DCW_CHARATTR_ISRASSCALE_CHAR;
		*bRtoChar= DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
		if(DCW_BASE_RATIO == *bRtoChar)
			*bRtoChar = 0;
		if(*bRtoChar)
			*bRtoChar = 1;
		return 0;
	case DLO_CHARATTR_BINSCALERATIO:
		ratio = (DT32_int*)dsninfo;
		op = DCW_CHARATTR_BINSCALERATIO;
		*ratio = DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
		if(0 == *ratio)
			*ratio = DCW_BASE_RATIO;
		return 0;
	case DLO_CHARATTR_ISBINSCALE_CHAR:
		bRtoChar = (DT32_int*)dsninfo;
		op = DCW_CHARATTR_ISBINSCALE_CHAR;
		*bRtoChar= DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
		if(DCW_BASE_RATIO == *bRtoChar)
			*bRtoChar = 0;
		if(*bRtoChar)
			*bRtoChar = 1;
		return 0;
//	case DLO_CHARATTR_HEIGHT_SHIFT:
//		op = DCW_CHARATTR_HEIGHT_SHIFT;
//		break;
//	case DLO_CHARATTR_NORMAL_WIDTH:
//		op = DCW_CHARATTR_NORMAL_WIDTH;
//		break;
//	case DLO_CHARATTR_NORMAL_HEIGHT:
//		op = DCW_CHARATTR_NORMAL_HEIGHT;
//		break;
//	case DLO_CHARATTR_ISOFFSETY_CHAR:
//		op = DCW_CHARATTR_ISOFFSETY_CHAR;
//		break;
//	case DLO_CHARATTR_GET_OFFSETY:
//	{
//		DT32_int *offY;
//		offY = (DT32_int*)dsninfo;
//		if(pfc){
//			if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_MOVEY){
//				*offY = (DT32_int)pfc->moveY;
//				return 0;
//			}	
//		}
//		op = DCW_CHARATTR_GET_OFFSETY;
//		*offY = DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
//		if(*offY){
//			if(pwrk->forcedown!=-1){
//				*offY = pwrk->forcedown;
//			}
//		}else{
//			*offY = rasMoveYbyCodeRange(pwrk, gidx, gseq2idx, attr);
//		}
//		if(pfc){
//			pfc->moveY = (DT16_short) *offY;
//			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;
//		}
//		return 0;
//	}
//	case DLO_CHARATTR_GET_LOGHEIGHT:
//	{
//		DT32_int *logh;
//		logh = (DT32_int*)dsninfo;
//		if(pfc){
//			if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_LOGH){
//				*logh = (DT32_int)pfc->logHeight;
//				return 0;
//			}
//		}
//		op = DCW_CHARATTR_GET_LOGHEIGHT;
//		*logh = DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
//		if(pfc){
//			pfc->logHeight = (DT8_uchar) *logh;
//			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_LOGH;
//		}
//		return 0;
//	}
	case DLO_CHARATTR_GET_OFFSETY:
	case DLO_CHARATTR_GET_LOGHEIGHT:
	case DLO_CHARATTR_GET_LOGTOP:
/*	case DLO_CHARATTR_GET_3IN1_VALUE:*/
//	{
//#define GET_OFFY_FROM_RETVAL(rtv)	(DT16_short)( (((DT32_ulong)rtv) << 16) >> 16 )
//#define GET_LOGH_FROM_RETVAL(rtv)	(DT16_short)( ((DT32_ulong)rtv) >> 16 )
//		DT32_int	*retval = (DT32_int*)dsninfo;
//		DT32_long	val;		/* offy and logh combined value */
//		DT16_short	offy, logh;
//		DT_BOOL bOffY = (option==DLO_CHARATTR_GET_OFFSETY) ? DT_TRUE : DT_FALSE; // true: offY, else logh
//		if(pfc){
//			if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_MOVEY){
//				*retval = bOffY ? (DT32_int)pfc->moveY : (DT32_int)pfc->logHeight;
//				return 0;
//			}	
//		}
//		op = bOffY ? DCW_CHARATTR_GET_OFFSETY : DCW_CHARATTR_GET_LOGHEIGHT;
//		val = DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
//		offy= GET_OFFY_FROM_RETVAL(val);
//		logh= GET_LOGH_FROM_RETVAL(val);
//		if(bOffY){
//			*retval = (DT32_int)offy;
//			if(*retval){
//				if(pwrk->forcedown!=-1){
//					*retval = pwrk->forcedown;
//				}
//			}else{
//				*retval = rasMoveYbyCodeRange(pwrk, gidx, gseq2idx, attr);
//			}
//		}else *retval = (DT32_int)logh;
//		if(pfc){
//			pfc->moveY		= offy;
//			pfc->logHeight	= logh;									// log for temp, not search again.
//			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;	// No CHECKFLAG_LOGH
//		}
//		return 0;
//	}
	{
		DT32_int	*retval = (DT32_int*)dsninfo;
		DT32_long	val;		/* offy and logh combined value */
		DT16_short	offy, logh, logt;
		if(pfc){
			if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_MOVEY){
				switch(option){
				case DLO_CHARATTR_GET_OFFSETY:
					*retval = (DT32_int)pfc->moveY;
					break;
				case DLO_CHARATTR_GET_LOGHEIGHT:
					*retval = (DT32_int)pfc->logHeight;
					break;
				case DLO_CHARATTR_GET_LOGTOP:
					*retval = (DT32_int)pfc->logTop;
					break;
				}
				return 0;
			}	
		}
		op = DCW_CHARATTR_GET_3IN1_VALUE;
		val = DCW_QueryCharAttr_1(pattr, attr, gidx, gseq2idx, op);
		offy= (DT16_short) DCW_OFFY_FROM_3IN1_VALUE(val);
		logh= (DT16_short) DCW_LOGH_FROM_3IN1_VALUE(val);
		logt= (DT16_short) DCW_LOGT_FROM_3IN1_VALUE(val);
		if(DLO_CHARATTR_GET_OFFSETY == option){
			*retval = (DT32_int)offy;
			if(*retval){
				if(pwrk->forcedown!=-1){
					*retval = pwrk->forcedown;
				}
			}else{
				*retval = rasMoveYbyCodeRange(pwrk, gidx, gseq2idx, attr);
			}
		}else if(DLO_CHARATTR_GET_LOGHEIGHT == option){
			*retval = (DT32_int)logh;
		}else if(DLO_CHARATTR_GET_LOGTOP == option){
			*retval = (DT32_int)logt;
		}
		if(pfc){
			pfc->moveY		= offy;
			pfc->logHeight	= logh;									// log for temp, not search again.
			pfc->logTop		= logt;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;	// No CHECKFLAG_LOGH, CHECKFLAG_LOGT
		}
		return 0;
	}
	case DLO_CHARATTR_RATIO_FILEWIDE:
		ratio = (DT32_int*)dsninfo;
		*ratio= rasRatiobyFDLFile_1(pwrk,gidx);
		if(0 == *ratio)
			*ratio = DCW_BASE_RATIO;
		return 0;
		break;
	case DLO_CHARATTR_ISSCALE_FILEWIDE:
		bRtoChar = (DT32_int*)dsninfo;
		*bRtoChar= rasRatiobyFDLFile_1(pwrk,gidx);
		if(0 == *bRtoChar || DCW_BASE_RATIO == *bRtoChar)
			*bRtoChar = 0;
		else
			*bRtoChar = 1;
		return 0;
		break;
	case DLO_CHARATTR_FONT_LRSB:
		{
			DT16_ushort usLowerBound, usUpperBound;
			DT32_uint uiCntOfDir;
			DT32_int offset;
			DT32_uint idir;
			Font_LRSB *fdsl;

			fdsl = (Font_LRSB*)dsninfo;
			if(pfc){
				if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_LRSB){
					fdsl->nsLsb = pfc->lrsb.nsLsb;
					fdsl->nsRsb = pfc->lrsb.nsRsb;
					return 0;
				}
			}
			pos = 6;
			ras_getDesignGlobalInfo(pattr, gidx, DLO_LANGTAB_RSB, (DT_void**)&pdata);
			fdsl->nsLsb = 0;
			fdsl->nsRsb = 0;
			if(pdata)
			{
				uiCntOfDir = FD_READINTBYDATA4(pdata, pos/*, 4*/);
				pos+=4;	
				for(idir =0; idir<uiCntOfDir; idir++)
				{
					usLowerBound = (DT16_ushort)FD_READINTBYDATA2(pdata, pos/*, 2*/);
					pos+=2;
					usUpperBound = (DT16_ushort)FD_READINTBYDATA2(pdata, pos/*, 2*/);
					pos+=2;
					offset = FD_READINTBYDATA4(pdata, pos/*, 4*/);
					pos+=4;
					if(usLowerBound <= gidx && gidx<=usUpperBound)
					{
						pos =  offset+(gidx-usLowerBound)*4+6;
						fdsl->nsLsb = (DT16_short)FD_READINTBYDATA2(pdata, pos/*, 2*/);
						pos+=2;
						fdsl->nsRsb = (DT16_short)FD_READINTBYDATA2(pdata, pos/*, 2*/);
						if(pfc){
							pfc->lrsb.nsLsb = fdsl->nsLsb;
							pfc->lrsb.nsRsb = fdsl->nsRsb;
							pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_LRSB;
						}
						return 0;
					}else;
				}
			}else;
			if(pfc){	// no lrsb info
				pfc->lrsb.nsLsb = fdsl->nsLsb;	// should be 0
				pfc->lrsb.nsRsb = fdsl->nsRsb;	// should be 0
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_LRSB;
			}
			return -1;
		}
		break;
	default:
		return -1;
	}

	/* Don't call DCW_QueryCharAttr_1(), because we need to know which font contains the table we want. */
	pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
	if(pos<=0){
//		if(DCW_GetAw(attr,gidx)!=DCW_CODE_NOT_EXIST){
//			// current font contains gidx, no need to check altfont.
//			return -1;
//		}
		if(pfc){
			if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){ 
			}else{
				ras_chkGlyphExist(pwrk->ras_attr,gidx,gseq2idx);
			}
			if(0==pfc->codeExist || (pfc->codeExist && pfc->existFont!=DLO_ALT_DT_FONT))
				return -1;
		}else{
			if(DCW_GetAw(attr,gidx)!=DCW_CODE_NOT_EXIST)
				return -1;
		}
		if(pwrk->altfontcnt>0){
			attr->fontdata = altfont->fontdata;
			pos = DCW_QueryCharAttr(attr, 0/*don't care*/, op);
			attr->fontdata = curfontdata;
			if(pos>0){
				pdata = altfont->fontdata;
			}else{
				return -1;
			}
		}
	}else{
		pdata = curfontdata;
	}

#ifdef THAI_thai
	if(pos>0 && pdata && option==DLO_CHARATTR_LANGTAB_THAI){
	  Font_Design_Thai fd;
	  Font_Design_Thai *fds = (Font_Design_Thai*)dsninfo;
	  DCW_AttrData tmpattr = rasattr->attr;	// copy the origin attr to the new(temp) one
	  DCW_AttrData *newattr =  (DCW_AttrData*)rasMakeNewAttr(pwrk, gidx, -1, &rasattr->attr, &tmpattr); 
	  
	  pos += (2+4);
	  fd.Thai_Top	= (DT16_ushort)FD_READINTBYDATA2(pdata,pos/*,2*/);	pos += 2;
	  fd.Thai_Above	= (DT16_ushort)FD_READINTBYDATA2(pdata,pos/*,2*/);	pos += 2;
	  fd.Thai_Base	= (DT16_ushort)FD_READINTBYDATA2(pdata,pos/*,2*/);	pos += 2;
	  fd.Thai_Below	= (DT16_ushort)FD_READINTBYDATA2(pdata,pos/*,2*/);	pos += 2;
	  fd.Thai_Shift	= (DT16_ushort)FD_READINTBYDATA2(pdata,pos/*,2*/);	pos += 2;
	  
	  totalh = fd.Thai_Top + fd.Thai_Above + fd.Thai_Base + fd.Thai_Below;
  	  diffh  = totalh - 1;
	  if(pwrk->vert){
//		fds->Thai_Top	= fd.Thai_Top*newattr->xsize/totalh;
//		fds->Thai_Above	= fd.Thai_Above*newattr->xsize/totalh;
//		fds->Thai_Base	= fd.Thai_Base*newattr->xsize/totalh;
//		fds->Thai_Below	= newattr->xsize - (fds->Thai_Top+fds->Thai_Above+fds->Thai_Base);
//		fds->Thai_Shift	= fd.Thai_Shift*newattr->ysize/totalh;		  
	    fds->Thai_Top	= (fd.Thai_Top*newattr->xsize+diffh)/totalh;
	    fds->Thai_Above	= ((fd.Thai_Top+fd.Thai_Above)*newattr->xsize+diffh)/totalh - fds->Thai_Top;
	    fds->Thai_Base	= ((fd.Thai_Top+fd.Thai_Above+fd.Thai_Base)*newattr->xsize+diffh)/totalh - fds->Thai_Top - fds->Thai_Above;
	    fds->Thai_Below	= newattr->xsize - (fds->Thai_Top+fds->Thai_Above+fds->Thai_Base);
	    fds->Thai_Shift	= fd.Thai_Shift*newattr->ysize/totalh;
	  }else{
//		fds->Thai_Top	= fd.Thai_Top*attr->ysize/totalh;
//		fds->Thai_Above	= fd.Thai_Above*attr->ysize/totalh;
//		fds->Thai_Base	= fd.Thai_Base*attr->ysize/totalh;
//		fds->Thai_Below	= attr->ysize - (fds->Thai_Top+fds->Thai_Above+fds->Thai_Base);
//		fds->Thai_Shift	= fd.Thai_Shift*attr->xsize/totalh;

	    fds->Thai_Top	= (fd.Thai_Top*newattr->ysize+diffh)/totalh;
	    fds->Thai_Above	= ((fd.Thai_Top+fd.Thai_Above)*newattr->ysize+diffh)/totalh - fds->Thai_Top;
	    fds->Thai_Base	= ((fd.Thai_Top+fd.Thai_Above+fd.Thai_Base)*newattr->ysize+diffh)/totalh - fds->Thai_Top - fds->Thai_Above;
	    fds->Thai_Below	= newattr->ysize - (fds->Thai_Top+fds->Thai_Above+fds->Thai_Base);
	    fds->Thai_Shift	= fd.Thai_Shift*newattr->xsize/totalh;
	  }
	  return 0;
	}
#endif

	if(pos>0 && pdata && option==DLO_CHARATTR_LANGTAB_DESCENT){
		Font_Design_Descent *fdsl = (Font_Design_Descent*)dsninfo;
		pos += 2;
		fdsl->nSize		= FD_READINTBYDATA4(pdata,pos/*,4*/);	pos += 4;
		fdsl->nOffset	= pos;
		fdsl->fontdata	= pdata;
		return 0;
	}

	return -1;
}


#endif
