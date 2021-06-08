#include "DcwLangModule.h"

#ifdef DIGITYPE_OUL

#include "DcwShaperVG.h"
#include "Digitype_oul.h"
#include "DcwLayout.h"
#include "DTmanager.h"
#include "DTdigitype.h"
#include "DigiTypeApi.h"



/* Suppose: if you call this function, it means that you can get the attribute of option from curfontdata or altfont either.*/
/* Might be something error: Is it right for bReQuery value? Should it be decided by something like DCW_GetAw()?			*/
/* Becare of the situation: curfont contain fontidx, but not langtab info, and altfont has fontidx and langtab both.		*/
DT32_int DCWOUL_QueryCharAttr_1(DT_void *pattr, DCWOUL_Handle oulhandle, DT32_long fontidx, DT32_int gseq2idx, DCW_CharAttr_Option option)
{
	DT32_int val, bReQuery;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	DT_Font *altfont = pwrk->alt_DT_Font;
	DT8_char *curfontdata = ovgattr->fontdata;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	val = DCWOUL_QueryCharAttr(ovgattr,ovgattr->fontdata, fontidx, option);
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
#if(0)		
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
#endif
	case DCW_CHARATTR_ISOFFSETY_CHAR:
		/* Don't know how to decide the value of bReQuery? by aw? or by return value? */
		/* Need to do in the future. */
		if(val==0){
			bReQuery = 1;
		}
		break;
	case DCW_CHARATTR_GET_OFFSETY:
	case DCWOUL_CHARATTR_GET_LOGHEIGHT:
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
	
//	if(DCWOUL_GetAw(ovgattr->hDcwOVG, fontidx, ovgattr->vert, ovgattr->fontdata, NULL, NULL)!=DCW_CODE_NOT_EXIST){
//		// curfont contains fontidx, no need to check altfont.
//		return val;
//	}
	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){ 
		}else{
			oul_chkGlyphExist(pwrk->ras_attr,(DT16_ushort)fontidx,gseq2idx);
		}
		if(0==pfc->codeExist || (pfc->codeExist && pfc->existFont!=DLO_ALT_DT_FONT))
			return val;
	}else{
		if(DCWOUL_GetAw(ovgattr->hDcwOVG, fontidx, ovgattr->vert, ovgattr->fontdata, NULL, NULL)!=DCW_CODE_NOT_EXIST)
			return val;
	}	
	if(bReQuery && pwrk->altfontcnt>0){
		val = DCWOUL_QueryCharAttr(ovgattr->hDcwOVG, altfont->fontdata, fontidx, option);
	}
	return val;
}

/* gseq2idx<0 means it required to search in FDL fontdata; else it can get directly from g2info that had been qureied before. */
DT32_int oulScaleMethod(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DT32_int *rto)
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
		return OUL_SCALE_BY_BINSCALERATIO;
	}
	
	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,ch,gseq2idx,DLO_CHARATTR_XYSCALERATIO,&ratio);
	if(DCW_BASE_RATIO != ratio)
	{
		if(rto)
			*rto = ratio;
		if(gseq2idx >= 0){
			pfc->scaleRatio = (DT16_ushort) ratio;
			pfc->scaleMethod= (DT16_ushort) DLO_SCALE_BY_XYSCALERATIO;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
		}
		return OUL_SCALE_BY_XYSCALERATIO;
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
		return OUL_SCALE_BY_RASSCALERATIO;
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
			return OUL_SCALE_BY_CODERANGE;
		}else if(isThaiChars(ch))
		{
			if(rto)
				*rto = gDT_FORCE_SCALE_RATIO + 1000;	//DCW_BASE_RATIO
			if(pfc){
				pfc->scaleRatio = (DT16_ushort) gDT_FORCE_SCALE_RATIO + 1000;
				pfc->scaleMethod= (DT16_ushort) DLO_SCALE_BY_CODERANGE;
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
			}
			return OUL_SCALE_BY_CODERANGE;
		}
	}
	
	if(pfc){
		pfc->scaleRatio = (DT16_ushort) DLO_BASE_RATIO;
		pfc->scaleMethod= (DT16_ushort) DLO_NOT_SCALE;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
	}
	return OUL_NOT_SCALE;
}

//DT32_int oul_getRatio(pLayWrk pwrk, DT16_ushort ch, DT32_int *rto)
//{
//	DT32_int ratio;
//	*rto = DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE, DCWOUL_BASE_RATIO);
//	/*check if there is an advanced ratio by character.*/
//	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,ch, DLO_CHARATTR_XYSCALERATIO, &ratio);
//	if(DCWOUL_BASE_RATIO != ratio)
//	{
//		*rto = DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE, ratio);
//	}
//	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,ch,DLO_CHARATTR_RASSCALERATIO,&ratio);
//	if(DCWOUL_BASE_RATIO != ratio)
//	{
//		*rto= DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE, ratio);
//	} 
//	/*decide the ratio by code range.*/
//	if(isArabicCodeRange(pwrk,ch))
//	{
//		*rto = DT_ScaleArabicSize(gDT_FONT_EMSIZE);
//	}
//	else if(isThaiChars(ch))
//	{
//		*rto = DT_ScaleThaiSize(gDT_FONT_EMSIZE);
//	}
//	return 0;
//}

DT32_int oul_getRatio(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DT32_int *rtox, DT32_int *rtoy)
{
	DT32_int ratio, ratiox, ratioy;
	DT32_int method, szY;

	method = oulScaleMethod(pwrk, ch, gseq2idx, &ratio);
	switch(method)
	{
	case OUL_SCALE_BY_XYSCALERATIO:
		if(pwrk->vert){
			szY = DCW_SCALED_SIZEXY(pwrk->xsize,ratio);	// force scaling by ysize.
		}else{
			szY = DCW_SCALED_SIZEXY(pwrk->ysize,ratio);	// force scaling by ysize.
		}
		ratiox = szY*gDT_FONT_EMSIZE/pwrk->xsize;
		ratioy = szY*gDT_FONT_EMSIZE/pwrk->ysize;; 
		pwrk->bScaled  = DT_TRUE;
		break;
	case OUL_SCALE_BY_RASSCALERATIO:
	case OUL_SCALE_BY_BINSCALERATIO:
			ratiox = ratioy = DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE,ratio);
			pwrk->bScaled  = DT_TRUE; 
		break;
	case OUL_SCALE_BY_RATIO_FILEWIDE:
		ratiox = ratioy = DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE,ratio);
		pwrk->bScaled  = DT_TRUE;
		break;
	case OUL_SCALE_BY_CODERANGE:
		if(isArabicCodeRange(pwrk,ch))
		{
			ratiox = ratioy = DT_ScaleArabicSize(gDT_FONT_EMSIZE);
			pwrk->bScaled  = DT_TRUE; 
		}else if(isThaiChars(ch))
		{
			ratiox = ratioy = DT_ScaleThaiSize(gDT_FONT_EMSIZE);
			pwrk->bScaled  = DT_TRUE;
		}
		break;
	case OUL_NOT_SCALE:
	default:
		ratio = DCWOUL_BASE_RATIO;
		ratiox = ratioy = DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE,DCWOUL_BASE_RATIO);
		break;
	}

	if(rtox)
		*rtox = ratiox;
	if(rtoy)
		*rtoy = ratioy;

	return method;
}

/* scalexy is OUL_SCALE_X or OUL_SCALE_Y, used to indicate how to scale val to *newval			*/
/* val: the original value before scaling. ignored if newval is NULL.							*/
/* *newval: the new value of val after scaling when func returned. can be NULL.					*/
/* rtox: the scaling ratio of x axis when func returned. can be NULL if you don't need it.		*/
/* rtoy: the scaling ratio of y axis when func returned. can be NULL if you don't need it.		*/
/* Return: the scale method: OUL_SCALE_BY_XXX													*/
DT32_int oul_getRatioScaleValue(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DT32_int scalexy, DT32_int val, DT32_int *newval, DT32_int *rtox, DT32_int *rtoy)
{
	DT32_int ratiox, ratioy;
	DT32_int method, scale_val;
	
	method = oul_getRatio(pwrk, ch, gseq2idx, &ratiox, &ratioy);

	if(newval){
		if(method != OUL_NOT_SCALE){
			switch(scalexy)
			{
			case OUL_SCALE_X:
				if(ratiox != DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE, DCWOUL_BASE_RATIO))
					scale_val = (val*ratiox/gDT_FONT_EMSIZE);
				else
					scale_val = val;
				break;
			case OUL_SCALE_Y:
				if(ratioy != DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE, DCWOUL_BASE_RATIO))
					scale_val = (val*ratioy/gDT_FONT_EMSIZE);
				else
					scale_val = val;
				break;
			default:
				scale_val = val;
			}
		}else{
			scale_val = val;
		}
		*newval = scale_val;
	}

	if(rtox)
		*rtox = ratiox;
	if(rtoy)
		*rtoy = ratioy;

	return method;
}

DT32_int oul_getVertMoveDown(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx) 
{
	DT32_int offsety; 
	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_OFFSETY, &offsety);
	offsety = DT_FORCE_MOVE_DOWN_PIXS(gDT_FONT_EMSIZE, offsety);
	return offsety;
}

DT_void oul_getRatioScalePath(pLayWrk pwrk, DCWOUL_OutlineData * pOutlineData, DT32_int ratiox, DT32_int ratioy, DT32_int offsety)
{
	DT16_short *path, *last, op, offx, offy;
	DT32_long pathsize;
	DT32_int opCnt, xyCnt,opIdx;
	
DBG_MSG_SHOW_FUNC_NAME();

	if(pOutlineData->vert){
		offx = -offsety;
		offy = 0;
	}else{
		offx = 0;
		offy = offsety;
	}

    path = (short*)pOutlineData->path;
	pathsize = pOutlineData->pathsize;
    last = path + pathsize;
    while (path < last)
	 {
		opCnt = *path++;
		xyCnt = *path++;
        //Get Contour Path 
		for (opIdx=0; opIdx<opCnt; opIdx++)
		{
			op = *path++;
			switch (op)
			{
			   case DLO_BEZIERTO:
         				*path = (*path)*ratiox/gDT_FONT_EMSIZE;
						*path += offx;
						path++;
						*path = (*path)*ratioy/gDT_FONT_EMSIZE; 
						*path +=  offy;
						path++;
						// break; // no break here, because BEZIERTO needs 2 points: end point & control point.
				case DLO_MOVETO:
				case DLO_LINETO:
          				*path = (*path)*ratiox/gDT_FONT_EMSIZE;
						*path += offx;
						path++;
						*path = (*path)*ratioy/gDT_FONT_EMSIZE;
						*path +=  offy;
						path++;
						break;
				case DLO_CLOSEPATH:	
						break;
			}	  
		}
	}
}

// This func doesn't care about vert!!
DT_void oulGetBoldEdgeXY(pLayWrk pwrk, DT32_int *wedgeX, DT32_int *wedgeY)
{
	pDT_Fontwrk pdtfwrk = (pDT_Fontwrk)(pwrk->pdtfwrk);
	DT32_int f_edge, w_edge;
	DT32_int x,y;
	f_edge = pdtfwrk->style.f_edge;
	w_edge = pdtfwrk->style.w_edge;
	switch(f_edge)
	{
	case DLO_STYLE_BOLD:
	case DLO_STYLE_OUTLINE:
		x = y = w_edge * 2;
		break;
//	case DLO_STYLE_BOLD_RIGHT:		// The 3 style aren't support in OUL mode.
//		x = w_edge;
//		y = 0;
//		break;
//	case DLO_STYLE_BOLD_DOWN:
//		x = 0;
//		y = w_edge;
//		break;
//	case DLO_STYLE_BOLD_RIGHT_DOWN:
//		x = y = w_edge;
//		break;
	default:
		x = y = 0;
	}

	if(wedgeX)
		*wedgeX = x;
	if(wedgeY)
		*wedgeY = y;
}

DT32_int DCWOUL_GetAw_1(DcwOpenVG_Attr *ovgattr, DT32_long fontidx, DT32_int gseq2idx, DT32_int option, DT32_int vert, DT16_short *ltx, DT16_short *paw1000)
{
	DT32_int aw;
	DT16_short x0 = 0, aw1000 = 0;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	DT_Font *altfont = pwrk->alt_DT_Font;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(OUL_OPTION_GETAW==option && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW){
			if(ltx)
				*ltx = pfc->x0;
			if(paw1000)
				*paw1000 = pfc->aw1000;
			return pfc->aw;
		}
		if(OUL_OPTION_EXIST==option && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){
			// dif fonts are not supported in DT_OUTLINE_MODE, comment it
//			if(pfc->existFont==DLO_ICON_DT_FONT)
//				return DCWOUL_EMPTY_FONT;			// for the char that exists in dif
			return pfc->codeExist ? 1 : DCWOUL_EMPTY_FONT;	// 1(other than DCWOUL_EMPTY_FONT) means it exists
		}
	}

	aw = DCWOUL_GetAw(ovgattr->hDcwOVG,fontidx,vert,ovgattr->fontdata,&x0,&aw1000);
	if((DCWOUL_BAD_HANDLE==aw || DCWOUL_EMPTY_FONT==aw)){
		//aw = 0;
		if(pwrk->altfontcnt>0){	/* if you want speed up , you can store two DCWOUL_Handle */
			//ovgattr->hDcwOVG = DCWOUL_Create(altfont->fontdata,pwrk->engWkMemsz,pwrk->engWkMem);
			aw = DCWOUL_GetAw(ovgattr->hDcwOVG,fontidx,vert,altfont->fontdata,&x0,&aw1000);
			if((DCWOUL_BAD_HANDLE==aw || DCWOUL_EMPTY_FONT==aw)){
				if(pfc /*&& !(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)*/){// avoid to modify the result by dif (not required)
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
					pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
				}
			}
			//ovgattr->hDcwOVG = DCWOUL_Create(ovgattr->fontdata,pwrk->engWkMemsz,pwrk->engWkMem);
		}else{
			if(pfc /*&& !(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)*/){
				pfc->codeExist = 0;
				pfc->existFont = 0;
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
				// code don't exist, icon font won't scale and move, so set followings also.
				setDefault_Scale_LRsb_MoveY(pfc);
			}
		}
	}else{
		if(pfc){
			pwrk->g2info[gseq2idx].codeExist = 1;
			pwrk->g2info[gseq2idx].existFont = DLO_CUR_DT_FONT;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
		}
	}
	if(option==OUL_OPTION_GETAW){
		if(pfc){
			pfc->aw = (aw==DCWOUL_BAD_HANDLE)?DCWOUL_EMPTY_FONT:aw;
			pfc->x0 = x0;
			pfc->aw1000 = aw1000;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AW;
		}
	}
	if(ltx)
		*ltx = x0;
	if(paw1000)
		*paw1000 = aw1000;
	return aw;
}

DT32_int DCWOUL_Outline_1(DcwOpenVG_Attr *ovgattr, DT32_int gseq2idx, DT32_int *aw, DCWOUL_OutlineData *outline)
{
	DT32_int ret, aw1;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	DT_Font *altfont = pwrk->alt_DT_Font;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){
			outline->pathsize = 0;
			if(pfc->codeExist){
				if(DLO_CUR_DT_FONT == pfc->existFont){
					if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW){
						aw1 = pfc->aw;
					}else{
						aw1 = DCWOUL_GetAw(ovgattr->hDcwOVG,outline->fontidx,outline->vert,ovgattr->fontdata,NULL,NULL);
					}
					ret = DCWOUL_Outline(ovgattr->hDcwOVG,outline,ovgattr->fontdata);
				}else if(DLO_ALT_DT_FONT == pfc->existFont){
					if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW){
						aw1 = pfc->aw;
					}else{
						aw1 = DCWOUL_GetAw(ovgattr->hDcwOVG,outline->fontidx,outline->vert,altfont->fontdata,NULL,NULL);
					}
					ret = DCWOUL_Outline(ovgattr->hDcwOVG,outline,altfont->fontdata);
				}else{	// error situation: treat as empty font
					aw1 = DCWOUL_EMPTY_FONT;
					ret = DCWOUL_EMPTY_FONT;
				}
			}else{
				aw1 = DCWOUL_EMPTY_FONT;
				ret = DCWOUL_EMPTY_FONT;
			}
			if(aw)
				*aw = aw1;
			return ret;
		}
	}


	aw1 = DCWOUL_GetAw(ovgattr->hDcwOVG,outline->fontidx,outline->vert,ovgattr->fontdata,NULL,NULL);
	if((DCWOUL_BAD_HANDLE==(aw1) || DCWOUL_EMPTY_FONT==(aw1))){
		aw1 = 0;
		if(pwrk->altfontcnt>0){	/* if you want speed up , you can store two DCWOUL_Handle */
			//ovgattr->hDcwOVG = DCWOUL_Create(altfont->fontdata,pwrk->engWkMemsz,pwrk->engWkMem);	
			aw1 = DCWOUL_GetAw(ovgattr->hDcwOVG,outline->fontidx,outline->vert,altfont->fontdata,NULL,NULL);
			ret = DCWOUL_Outline(ovgattr->hDcwOVG,outline,altfont->fontdata);
			//ovgattr->hDcwOVG = DCWOUL_Create(ovgattr->fontdata,pwrk->engWkMemsz,pwrk->engWkMem);
		}else{
			ret = DCWOUL_Outline(ovgattr->hDcwOVG,outline,NULL);
		}
	}else{
		ret = DCWOUL_Outline(ovgattr->hDcwOVG,outline,ovgattr->fontdata);
	}

	if(aw)
		*aw = aw1;
	return ret;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Estimate the required working memory */
DT32_int oul_EstimateWkMem()
{
DBG_MSG_SHOW_FUNC_NAME();

	return DCWOUL_EstimateWkMem();
}

/* Set the initial data to create a Digitype FDL font data. */
//DT32_int initFont(DT8_char *fontdata, DCWOUL_Handle *hDcwVG )
DT32_int oul_initFont(DT_void *pattr, DT8_char *fontdata, DT32_long wkmsz, DT8_char *wkm, DT_void *pwrk)
{
	DT32_int ret;
	DCWOUL_FontInfo fdlinfo;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;

DBG_MSG_SHOW_FUNC_NAME();

	ovgattr->pwrk	  = (pLayWrk)pwrk;
	ovgattr->fontdata = fontdata;
	ovgattr->hDcwOVG  = 0;
	ovgattr->vert	  = ((pLayWrk)pwrk)->vert;

	/* Check if the font data is valid or not. */
	ret = DCWOUL_GetFontInfo(ovgattr->fontdata,&fdlinfo);
	if(!ret) 
		return DLO_BAD_FONTDATA;
	if(fdlinfo.ctmode != DCWOUL_Code_Ucs ) 
		return DLO_INVALID_FDL_CODEMODE;

	ovgattr->hDcwOVG = DCWOUL_Create(ovgattr->fontdata, wkmsz, wkm);

	if(ovgattr->hDcwOVG)
		ret = DLO_SUCCESS;
	else
		ret = DLO_NOT_ENOUGH_ENGINEWKMEM;
	
	return ret;
}

DT32_int oul_uninitFont ( DT_void *pattr )
{
	DT32_int ret;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;

DBG_MSG_SHOW_FUNC_NAME();

	ret = DCWOUL_Destroy(ovgattr->hDcwOVG);
	if(ret!=DCWOUL_SUCCESS)
		return DLO_BAD_ENGINE_HANDLE;

	return DLO_SUCCESS;

}

/* bufsz: size of olbuf in bytes. olbuf: a pointer to an allocated buffer to receive oul. pathsz: pathsize when returned. */
DT32_int oul_getCharOul(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_long bufsz, DT_void *olbuf, DT32_long *pathsz)
{
	DT32_int ret,ratiox,ratioy,offsety;
//	DT32_int oriaw=0,aw=0;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
 	pLayWrk	pwrk = (pLayWrk)ovgattr->pwrk;
	DCWOUL_OutlineData OutlineData;

DBG_MSG_SHOW_FUNC_NAME();

//	DT_memset(olbuf, 0, bufsz);
	// Get Font Outline
	OutlineData.fontidx  = ch;
	OutlineData.vert     = ovgattr->vert;
	OutlineData.sizexy	 = pwrk->ysize;
	OutlineData.path     = (DT8_char*)olbuf;
	OutlineData.pathmax  = bufsz/sizeof(DT16_short);
	//ret = DCWOUL_Outline(ovgattr->hDcwOVG, &OutlineData);
	ret = DCWOUL_Outline_1(ovgattr, gseq2idx, /*&aw*/NULL, &OutlineData);
	
	if(DCWOUL_SUCCESS==ret){
		*pathsz= OutlineData.pathsize;
		/*read table and adjust path.*/
		//oul_getRatio(pwrk, ch, &ratiox);
//		oriaw = (aw==DCWOUL_EMPTY_FONT) ? 0 : aw;
//		oul_getRatioScaleValue(pwrk, ch, gseq2idx, OUL_SCALE_X, oriaw, &aw, &ratiox, &ratioy);
		oul_getRatioScaleValue(pwrk, ch, gseq2idx, OUL_SCALE_X, 0, NULL, &ratiox, &ratioy);

		offsety = oul_getVertMoveDown(pwrk, ch, gseq2idx);
		if( offsety !=0 
			|| ratiox !=DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE, DCWOUL_BASE_RATIO)
			|| ratioy !=DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE, DCWOUL_BASE_RATIO))
		{
			oul_getRatioScalePath(pwrk, &OutlineData, ratiox, ratioy, offsety);
		}
	}else if(DCWOUL_EMPTY_FONT==ret){
		ret = DLO_SUCCESS;
		*pathsz = 0;
	}

	return ret;
}

/* bufsz: size of olbuf in bytes. olbuf: a pointer to an allocated buffer to receive oul. pathsz: pathsize when returned. */
DT32_int oul_fastCharOul(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_long bufsz, DT_void *olbuf, DT32_long *pathsz)
{
	DT32_int ret/*,awFDL=0*/;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
 	pLayWrk	pwrk = (pLayWrk)ovgattr->pwrk;
	DCWOUL_OutlineData OutlineData;

DBG_MSG_SHOW_FUNC_NAME();

//	DT_memset(olbuf, 0, bufsz);
	// Get Font Outline
	OutlineData.fontidx  = ch;
	OutlineData.vert     = ovgattr->vert;
	OutlineData.sizexy	 = pwrk->ysize;
	OutlineData.path     = (DT8_char*)olbuf;
	OutlineData.pathmax  = bufsz/sizeof(DT16_short);
	ret = DCWOUL_Outline_1(ovgattr, gseq2idx, /*&awFDL*/NULL, &OutlineData);
	
	if(DCWOUL_SUCCESS==ret){
		*pathsz= OutlineData.pathsize;
	}else if(DCWOUL_EMPTY_FONT==ret){
		ret = DLO_SUCCESS;
		*pathsz = 0;
	}

	return ret;
}

/* Get Outline Data. */
DT32_int oul_getOutline(DT_void *pattr, DT16_ushort ch, DT_void *op, DT32_long *bufsz, DT8_char **olbuf, DT32_long *pathsz)
{
	DT32_int ret, /*aw=0,*/ gseq2idx=-1;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	pLayWrk	pwrk = (pLayWrk)ovgattr->pwrk;
	GlyfOperate *go=NULL;
	DCWOUL_OutlineData OutlineData;
	DT32_long msz, nPathBufsize=DLO_MAX_OUL_SIZE_PER_GLYPH;
	//DT8_char PathBuf[DLO_MAX_OUL_SIZE_PER_GLYPH];//DT8_char *PathBuf=NULL;
	DT8_char *ptr=NULL;
	pDT_FontMgr_wrk	pmgrwrk=((DT_Font*)(pwrk->cur_DT_Font))->fontmgr;
	DT8_char *PathBuf=NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(op){
	  go = (GlyfOperate *) op; 
	}

	if(pmgrwrk->tmpbufsize < nPathBufsize){
		return DLO_NOT_ENOUGH_PATHMEM;
	}

	PathBuf = (DT8_char*)pmgrwrk->tempbuf;
	//DT_memset(PathBuf,0,nPathBufsize);
	
	// Get Font Outline
	OutlineData.fontidx  = ch;
	OutlineData.vert     = ovgattr->vert;
	OutlineData.sizexy	 = pwrk->ysize;
	OutlineData.path     = (DT8_char*)PathBuf;
	OutlineData.pathmax  = nPathBufsize/sizeof(DT16_short);
	//ret = DCWOUL_Outline(ovgattr->hDcwOVG, &OutlineData);
	ret = DCWOUL_Outline_1(ovgattr, gseq2idx, /*&aw*/NULL, &OutlineData);
	
	if(DCWOUL_SUCCESS==ret){
		msz = (*bufsz);
		msz += OutlineData.pathsize*sizeof(DT16_short);
		if( pwrk->oldatasz<msz ){
			return DLO_NOT_ENOUGH_PATHMEM;	// return directly, because all the memory remained are used, can't allocate more.

//			ptr = (DT8_char*) DT_realloc(*olbuf,DT_ALLOC_SIZE(msz));
//			if(!ptr){
//			  return DLO_NOT_ENOUGH_PATHMEM;
//			}else{
//			  *olbuf = ptr;
//			  pwrk->oldatasz = msz;
//			}
		}
		  DT_memcpy((*olbuf)+(*bufsz),PathBuf,OutlineData.pathsize*sizeof(DT16_short));
		  *bufsz = msz;
		  *pathsz= OutlineData.pathsize; 
	}else if(DCWOUL_EMPTY_FONT==ret){
		// Modified_By_Jacky_20101213:
		if(DCWOUL_GetAw_1(ovgattr,ch,gseq2idx,OUL_OPTION_GETAW,0,NULL,NULL)==DCWOUL_EMPTY_FONT){ //Check if ch==0x0020 or something like that.
			ret = DLO_EMPTY_FONT;
		}else{
			ret = DLO_SUCCESS;		//some char like 0x0020.
		}
		*pathsz = 0;
	}
	
	return ret;
}

// Return 0 if ch does NOT exist.
// Return 1 if ch DOES exist.
DT32_int oul_chkGlyphExist( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DT32_int aw=0;
	DT32_long gidx;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)
			return pfc->codeExist;
	}

	gidx = ch;
	aw = DCWOUL_GetAw_1(ovgattr,gidx,gseq2idx,OUL_OPTION_EXIST,0,NULL,NULL);	// No DLO_FONTCODEINFO_CHECKFLAG_SCALE, No DLO_FONTCODEINFO_CHECKFLAG_AW
	if(DCWOUL_BAD_HANDLE==aw || DCWOUL_EMPTY_FONT==aw ){
		return 0;
	}else{
		return 1;
	}
	return 0;
}

/* Get advanced width of the glyph.	*/
/* Do not deal with vertical layout yet. Assume horizontal layout only. */
DT32_int oul_getAwidth(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx)
{
	DT32_int oriaw, aw, spacing, wedge, wedgeX, wedgeY;
	DT16_short x0 = 0, aw1000 = 0;
	DT32_long gidx;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
	if(ovgattr->vert){
		spacing = DLO_OUL_ROOF_SCALED_PIX2EM(pwrk->spacing,pwrk->ysize);	//(pwrk->spacing*gDT_FONT_EMSIZE)/pwrk->ysize;
		wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeY,pwrk->ysize);			//(wedgeY*gDT_FONT_EMSIZE)/pwrk->ysize;
	}else{
		spacing = DLO_OUL_ROOF_SCALED_PIX2EM(pwrk->spacing,pwrk->xsize);	//(pwrk->spacing*gDT_FONT_EMSIZE)/pwrk->xsize;
		wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeX,pwrk->xsize);			//(wedgeX*gDT_FONT_EMSIZE)/pwrk->xsize;
	}

	
	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW)
			return (pfc->aw==DCWOUL_EMPTY_FONT || pfc->aw==0)?0:pfc->aw+spacing+wedge;
	}

	gidx = ch;
	//aw = DCWOUL_GetAw(ovgattr->hDcwOVG,gidx,0/*ovgattr->vert*/);
	aw = DCWOUL_GetAw_1(ovgattr,gidx,gseq2idx,OUL_OPTION_GETAW,ovgattr->vert,&x0,&aw1000);
	if(DCWOUL_BAD_HANDLE==aw || DCWOUL_EMPTY_FONT==aw){
		//aw = 0;
		if(pfc){
			// because oul_getRatioScaleValue() sets SCALE, so we set it here.
			pfc->scaleMethod = DLO_NOT_SCALE;
			pfc->scaleRatio  = DCWOUL_BASE_RATIO; 
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
		}
	}else{
		oriaw = aw;
		oul_getRatioScaleValue(pwrk, ch, gseq2idx, OUL_SCALE_X, oriaw, &aw, NULL, NULL);
	}

	if(pfc){
		pfc->aw = (DCWOUL_BAD_HANDLE==aw)?DCWOUL_EMPTY_FONT:aw;
		pfc->x0 = x0;
		pfc->aw1000 = aw1000;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AW;
	}

	return (0==aw || DCWOUL_EMPTY_FONT==aw || DCWOUL_BAD_HANDLE==aw)?0:aw+spacing+wedge;//aw+pwrk->spacing;	/* Jacky_20100824 */
}

/* Get advanced width of the glyph.	*/
/* Do not deal with vertical layout yet. Assume horizontal layout only. */
DT32_int oul_getAwidth_pix(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx)
{
	DT32_int szx, spacing, wedge, wedgeX, wedgeY, retaw = 0;
	DT16_short x0 = 0, aw1000 = 0;
	DT32_long gidx;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();
	
	if(pfc && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW){
		if(pfc->aw==DCWOUL_EMPTY_FONT || pfc->aw==0){
			return 0;
		}
		x0 = pfc->x0;
		aw1000 = pfc->aw1000;
	}else{
		DT32_int aw;
		gidx = ch;
		aw = DCWOUL_GetAw_1(ovgattr,gidx,gseq2idx,OUL_OPTION_GETAW,ovgattr->vert,&x0,&aw1000);
		if(DCWOUL_BAD_HANDLE==aw || DCWOUL_EMPTY_FONT==aw){
			return 0;
		}
	}

	oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
	if(ovgattr->vert){
		oul_getRatioScaleValue(pwrk, ch, gseq2idx, OUL_SCALE_X, pwrk->ysize, &szx, NULL, NULL);
		//szx		= pwrk->ysize;
		wedge	= wedgeY;
	}else{
		oul_getRatioScaleValue(pwrk, ch, gseq2idx, OUL_SCALE_X, pwrk->xsize, &szx, NULL, NULL);
		//szx		= pwrk->xsize;
		wedge	= wedgeX;
	}
	spacing = pwrk->spacing;
	
	if(x0 < 0){
		DT32_int errx0 = (((DT32_long)x0 * szx) / 1000);
		aw1000 += (x0 - errx0*1000 / szx);
	}
	retaw = (DT32_int)DLO_CALC_AW_AH(aw1000, szx);
	return retaw+spacing+wedge;
}

/* Get advanced width (vector type) of the glyph.	*/
DT32_int oul_getAwidth2(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy)
{
	DT32_int aw, spacing, wedge, wedgeX, wedgeY;
	DT32_long gidx;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
	if(ovgattr->vert){
		spacing = DLO_OUL_ROOF_SCALED_PIX2EM(pwrk->spacing,pwrk->ysize);	//(pwrk->spacing*gDT_FONT_EMSIZE)/pwrk->ysize;
		wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeY,pwrk->ysize);			//(wedgeY*gDT_FONT_EMSIZE)/pwrk->ysize;
	}else{
		spacing = DLO_OUL_ROOF_SCALED_PIX2EM(pwrk->spacing,pwrk->xsize);	//(pwrk->spacing*gDT_FONT_EMSIZE)/pwrk->xsize;
		wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeX,pwrk->xsize);			//(wedgeX*gDT_FONT_EMSIZE)/pwrk->xsize;
	}

	if(pfc && pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW){
		aw = (pfc->aw==DCWOUL_EMPTY_FONT || pfc->aw==0)?0:pfc->aw+spacing+wedge;
	}else{
		gidx = ch;
		//aw = DCWOUL_GetAw(ovgattr->hDcwOVG,gidx,ovgattr->vert);
		aw = DCWOUL_GetAw_1(ovgattr,gidx,gseq2idx,OUL_OPTION_GETAW,ovgattr->vert,NULL,NULL);

		aw = (aw==DCWOUL_EMPTY_FONT)?0:aw+spacing+wedge;
	}

	if(!ovgattr->vert){	// Horizontal
		*vx = aw;	//(aw==DCWOUL_EMPTY_FONT)?0:aw+spacing;//aw+pwrk->spacing;
		*vy = 0;
	}else{				// Vertical
		*vx = 0;
		*vy = aw;	//(aw==DCWOUL_EMPTY_FONT)?0:aw+spacing;
	}
	return aw;
}

DT32_int oul_getAheight( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DT32_int aw, height, oriheight, method, ratiox, ratioy;
	DT32_int wedge, wedgeX, wedgeY;
	DT32_long gidx;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
	if(!ovgattr->vert){
		wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeY,pwrk->ysize);		//(wedgeY*gDT_FONT_EMSIZE)/pwrk->ysize;
	}else{
		wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeX,pwrk->xsize);		//(wedgeX*gDT_FONT_EMSIZE)/pwrk->xsize;
	}

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AH){
			// DT_OUTLINE_MODE don't support dif fonts.
//			if( pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST 
//				&& pfc->codeExist && pfc->existFont==DLO_ICON_DT_FONT 
//				&& pfc->ah > pwrk->maxdifH){
//				pwrk->maxdifH = pfc->ah;
//			}
			//return pfc->ah;
			return (pfc->ah==0) ? 0 : (pfc->ah+wedge);
		}
	}

	gidx = ch;
	aw = DCWOUL_GetAw_1(ovgattr,gidx,gseq2idx,OUL_OPTION_EXIST/*OUL_OPTION_GETAW*/,ovgattr->vert,NULL,NULL);

	if(DCWOUL_BAD_HANDLE==aw || DCWOUL_EMPTY_FONT==aw){
		height = 0;
	}else{
		// scale is NOT required.
		oriheight = DLO_FONT_EMSIZE;
		method = oul_getRatio(pwrk, ch, gseq2idx, &ratiox, &ratioy);
		switch(method)
		{
		case RAS_SCALE_BY_XYSCALERATIO:	
			break;	// it's always the same with oriattr->ysize when scale by this method, no matter vert or not.
		case RAS_SCALE_BY_RATIO_FILEWIDE:
			break;	// do nothing.
		case RAS_SCALE_BY_CODERANGE:
		case RAS_SCALE_BY_RASSCALERATIO:
		case RAS_SCALE_BY_BINSCALERATIO:
			oriheight = DLO_FONT_EMSIZE*ratioy/gDT_FONT_EMSIZE;	// scale by sizey.
			break;
		case RAS_NOT_SCALE:
		default:
			break;
		}
		if(ovgattr->vert){
			if(RAS_SCALE_BY_XYSCALERATIO==method){
				height = oriheight;			// FIXME: x, y should not be the same sacle ratio.	
			}else{
				// should be the x width.
				height = oriheight;			//DLO_FONT_EMSIZE;
			}
		}else{
			height = oriheight;
		}
	}

	if(pfc){
		pfc->ah = height;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AH;
	}
	//return height;
	return (0==height) ? 0 : (height+wedge);
}

//DT32_int oul_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
//{
//	DT32_int logh = 0, ratio = gDT_FONT_EMSIZE;
//	DT32_int wedge, wedgeX, wedgeY;
//	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
//	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
////	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	if(!pwrk->ratio)		// ratio is assigned only when Prerender_Devanagari() had been called.
//		return 0;			// Now, logh is used to adjust Hindi only.
//
//	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_LOGHEIGHT, &logh);
//
//	if(logh){
//		DT32_int method, ratiox, ratioy;
//		logh = DLO_SCALE_LOGHEIGHT2EM(logh);	// convert the 1000 based to EM based
//		method = oul_getRatio(pwrk, ch, gseq2idx, &ratiox, &ratioy);
//		oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
//		if(!ovgattr->vert){
//			ratio	= ratioy;
//			wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeY,pwrk->ysize);		//(wedgeY*gDT_FONT_EMSIZE)/pwrk->ysize;
//		}else{
//			ratio	= ratiox;
//			wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeX,pwrk->xsize);		//(wedgeX*gDT_FONT_EMSIZE)/pwrk->xsize;
//		}
//
//		switch(method)
//		{
//		case OUL_SCALE_BY_XYSCALERATIO:				
//			break;
//		case OUL_SCALE_BY_RATIO_FILEWIDE:
//			logh = logh*ratio/gDT_FONT_EMSIZE;	// scale by sizey.
//			break;	// do nothing.
//		case OUL_SCALE_BY_CODERANGE:
//		case OUL_SCALE_BY_RASSCALERATIO:
//		case OUL_SCALE_BY_BINSCALERATIO:
//			logh = logh*ratio/gDT_FONT_EMSIZE;	// scale by sizey.
//			break;
//		case OUL_NOT_SCALE:
//		default:
//			break;
//		}
//		logh += wedge;
//	}
//	return logh;
//}

DT32_int oul_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DT32_int logh = 0, ratio = gDT_FONT_EMSIZE;
	DT32_int wedge, wedgeX, wedgeY;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
//	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk->ratio)		// ratio is assigned only when Prerender_Devanagari() had been called.
		return 0;			// Now, logh is used to adjust Hindi only.

	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_LOGHEIGHT, &logh);
	if(logh<=0){
		logh = DLO_BASE_RATIO;	//1000;
	}

	if(logh){
		if(ovgattr->bPix){
			DT32_int method, sz, szx, szy;
			method = oulScaleMethod(pwrk, ch, gseq2idx, &ratio);
			oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
			szx = DLO_SCALED_SIZEXY(pwrk->xsize,ratio);
			szy = DLO_SCALED_SIZEXY(pwrk->ysize,ratio);
			if(!ovgattr->vert){
				sz = szy;
				wedge = wedgeY;
			}else{
				sz = szx;
				wedge = wedgeX;
			}

			switch(method)
			{
			case OUL_SCALE_BY_XYSCALERATIO:	
				logh = DLO_SCALE_LOGHEIGHT2PIX(logh,szy);
				break;
			case OUL_SCALE_BY_RATIO_FILEWIDE:
				logh = DLO_SCALE_LOGHEIGHT2PIX(logh,sz);
				break;	// do nothing.
			case OUL_SCALE_BY_CODERANGE:
			case OUL_SCALE_BY_RASSCALERATIO:
			case OUL_SCALE_BY_BINSCALERATIO:
				logh = DLO_SCALE_LOGHEIGHT2PIX(logh,sz);
				break;
			case OUL_NOT_SCALE:
			default:
				sz = ovgattr->vert ? pwrk->xsize : pwrk->ysize;
				logh = DLO_SCALE_LOGHEIGHT2PIX(logh,sz);
				break;
			}
			logh += wedge;
		}else
		{
			DT32_int method, ratiox, ratioy;
			logh = DLO_SCALE_LOGHEIGHT2EM(logh);	// convert the 1000 based to EM based
			method = oul_getRatio(pwrk, ch, gseq2idx, &ratiox, &ratioy);
			oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
			if(!ovgattr->vert){
				ratio	= ratioy;
				wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeY,pwrk->ysize);		//(wedgeY*gDT_FONT_EMSIZE)/pwrk->ysize;
			}else{
				ratio	= ratiox;
				wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeX,pwrk->xsize);		//(wedgeX*gDT_FONT_EMSIZE)/pwrk->xsize;
			}

			switch(method)
			{
			case OUL_SCALE_BY_XYSCALERATIO:				
				break;
			case OUL_SCALE_BY_RATIO_FILEWIDE:
				logh = logh*ratio/gDT_FONT_EMSIZE;	// scale by sizey.
				break;	// do nothing.
			case OUL_SCALE_BY_CODERANGE:
			case OUL_SCALE_BY_RASSCALERATIO:
			case OUL_SCALE_BY_BINSCALERATIO:
				logh = logh*ratio/gDT_FONT_EMSIZE;	// scale by sizey.
				break;
			case OUL_NOT_SCALE:
			default:
				break;
			}
			logh += wedge;
		}
	}
	return logh;
}

DT32_int oul_getLogt( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DT32_int logt = 0, ratio = gDT_FONT_EMSIZE;
//	DT32_int wedge, wedgeX, wedgeY;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
//	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk->ratio)		// ratio is assigned only when Prerender_Devanagari() had been called.
		return 0;			// Now, logt is used to adjust Hindi only.

	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_LOGTOP, &logt);
	if(logt<=0){
		logt = 0;
	}

	if(logt){
		if(ovgattr->bPix){
			DT32_int method, sz, szx, szy;
			method = oulScaleMethod(pwrk, ch, gseq2idx, &ratio);
			//oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
			szx = DLO_SCALED_SIZEXY(pwrk->xsize,ratio);
			szy = DLO_SCALED_SIZEXY(pwrk->ysize,ratio);
			if(!ovgattr->vert){
				sz = szy;
				//wedge = wedgeY;
			}else{
				sz = szx;
				//wedge = wedgeX;
			}

			switch(method)
			{
			case OUL_SCALE_BY_XYSCALERATIO:	
				logt = DLO_SCALE_LOGHEIGHT2PIX(logt,szy);
				break;
			case OUL_SCALE_BY_RATIO_FILEWIDE:
				logt = DLO_SCALE_LOGHEIGHT2PIX(logt,sz);
				break;	// do nothing.
			case OUL_SCALE_BY_CODERANGE:
			case OUL_SCALE_BY_RASSCALERATIO:
			case OUL_SCALE_BY_BINSCALERATIO:
				logt = DLO_SCALE_LOGHEIGHT2PIX(logt,sz);
				break;
			case OUL_NOT_SCALE:
			default:
				sz = ovgattr->vert ? pwrk->xsize : pwrk->ysize;
				logt = DLO_SCALE_LOGHEIGHT2PIX(logt,sz);
				break;
			}
			//logt += wedge;
		}else
		{
			DT32_int method, ratiox, ratioy;
			logt = DLO_SCALE_LOGHEIGHT2EM(logt);	// convert the 1000 based to EM based
			method = oul_getRatio(pwrk, ch, gseq2idx, &ratiox, &ratioy);
			//oulGetBoldEdgeXY(pwrk,&wedgeX,&wedgeY);
			if(!ovgattr->vert){
				ratio	= ratioy;
				//wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeY,pwrk->ysize);		//(wedgeY*gDT_FONT_EMSIZE)/pwrk->ysize;
			}else{
				ratio	= ratiox;
				//wedge	= DLO_OUL_ROOF_SCALED_PIX2EM(wedgeX,pwrk->xsize);		//(wedgeX*gDT_FONT_EMSIZE)/pwrk->xsize;
			}

			switch(method)
			{
			case OUL_SCALE_BY_XYSCALERATIO:				
				break;
			case OUL_SCALE_BY_RATIO_FILEWIDE:
				logt = logt*ratio/gDT_FONT_EMSIZE;	// scale by sizey.
				break;	// do nothing.
			case OUL_SCALE_BY_CODERANGE:
			case OUL_SCALE_BY_RASSCALERATIO:
			case OUL_SCALE_BY_BINSCALERATIO:
				logt = logt*ratio/gDT_FONT_EMSIZE;	// scale by sizey.
				break;
			case OUL_NOT_SCALE:
			default:
				break;
			}
			//logt += wedge;
		}
	}
	return logt;
}

/* Get height of the glyph.	*/
DT32_int oul_getHeight( DT_void *pattr )
{
DBG_MSG_SHOW_FUNC_NAME();

	return DLO_FONT_EMSIZE;
}

/* Get width of the glyph.	*/
DT32_int oul_getWidth( DT_void *pattr )
{
DBG_MSG_SHOW_FUNC_NAME();

	return DLO_FONT_EMSIZE;
}

DT32_int oul_getExten( DT_void *pattr )
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;
}

DT32_int oul_getAexten( DT_void *pattr, DT16_ushort ch )
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;
}

DT32_int oul_getVexten( DT_void *pattr, DT16_ushort ch )
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;
}

/* The edge width (difference between Bold and Normal font).*/
/* t:top-edge; d:down-edge; l:left-edge; r:right-edge		*/
/* return: 0:DLO_SUCCESS; <0:Error							*/
DT32_int oul_getEdge( DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r )
{
DBG_MSG_SHOW_FUNC_NAME();

	if(t)	*t=0;
	if(d)	*d=0;
	if(l)	*l=0;
	if(r)	*r=0;
	return DLO_SUCCESS;
}

/* Get data */
DT32_long oulFDL_ReadInt(DT8_char *fdl, DT32_long ofs, DT32_int size)
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



DT32_long oul_ReadIntByData(DT8_char *fontdata, DT32_long ofs, DT32_int size)
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

//DT32_int oul_getTable(DT8_char * fontdata, DCW_CharAttr_Option op)
//{ 
//#define OULFD_LANGDATA 58 /* offset in FDL header to language data. */
//
//	DT16_ushort i, langid, langtabcnt;
//	DT32_long ofs, langtab, sz;
//	DT32_int ret_ofs;
//	ofs = 0;
//	ret_ofs = 0;
//	langtab = FD_READINTBYDATA4(fontdata, OULFD_LANGDATA/*, 4*/);
//	if(langtab > 0)
//	{
//		ofs = langtab;
//		langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs/*, 2*/);
//		ofs+=2;
//		if(0<langtabcnt && langtabcnt <= DCW_MAX_LANGTABCNT_LIMIT)
//		{
//			for(i=0;i<langtabcnt;i++)
//			{
//				langid	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs/*, 2*/);
//				sz		= FD_READINTBYDATA4(fontdata, ofs+2/*, 4*/);
//				if(langid == op){
//					ret_ofs = (DT32_int)ofs;
//					break;
//				}else{
//					ofs += sz;
//				}
//			}
//		}	
//	}
//	return (DT32_int)ret_ofs;
//}

DT32_int oul_getDesignGlobalInfo(DT_void *pattr, DT16_ushort gidx, DT32_int option, DT_void **pdsninfo)
{
	DT32_long pos;
	DCW_CharAttr_Option op;
	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	DCWOUL_Handle oulhandle = ovgattr->hDcwOVG;
	DT8_char *curfontdata = ovgattr->fontdata;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	DT_Font *altfont = pwrk->alt_DT_Font;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdsninfo){
		return -1;
	}
	switch(option){
		case DLO_LANGTAB_GLOBAL:
				op = DCWOUL_CHARATTR_LANGTAB_GLOBAL;
				/*
				pos = oul_getTable(curfontdata, op);	
				if(pos){
					*pdsninfo =curfontdata+pos;
					return 0;
				}else return -1;*/
				break;
		case DLO_LANGTAB_HINDI_SUB:
				op = DCWOUL_CHARATTR_LANGTAB_HINDI_SUB;
				/*
				pos = oul_getTable(curfontdata, op);	
				if(pos){
					*pdsninfo =curfontdata+pos;
					return 0;
				}else return -1;*/
				break;
		case DLO_LANGTAB_HINDI_POS1:
				op = DCWOUL_CHARATTR_LANGTAB_HINDI_POS1;
				/*
				pos = oul_getTable(curfontdata, op);	
				if(pos){
					*pdsninfo =curfontdata+pos;
					return 0;
				}else return -1;*/
				break;
		case DLO_LANGTAB_HINDI_POS2:
				op = DCWOUL_CHARATTR_LANGTAB_HINDI_POS2;
				/*
				pos = oul_getTable(curfontdata, op);	
				if(pos){
					*pdsninfo =curfontdata+pos;
					return 0;
				}else return -1;*/
				break;

		case DLO_LANGTAB_HINDI_POS3:
				op = DCWOUL_CHARATTR_LANGTAB_HINDI_POS3;
				/*
				pos = oul_getTable(curfontdata, op);	
				if(pos){
					*pdsninfo =curfontdata+pos;
					return 0;
				}else return -1;*/
				break;

		case DLO_LANGTAB_RSB:
				op = DCWOUL_CHARATTR_LANGTAB_RSB;
				/*
				pos = oul_getTable(curfontdata, op);	
				if(pos){
					*pdsninfo =curfontdata+pos;
					return 0;
				}else return -1;*/
				break;
		default:
			break;
	}

    /* Don't call DCW_QueryCharAttr_1(), because we need to know which font contains the table we want. */
	pos = DCWOUL_QueryCharAttr(ovgattr, curfontdata, 0/*don't care*/, op);
	if(pos>0){
		*pdsninfo = curfontdata + pos;
		return 0;
	}else{
		if(DCWOUL_GetAw(oulhandle,gidx,ovgattr->vert,ovgattr->fontdata,NULL,NULL)!=DCW_CODE_NOT_EXIST){
			// current font contains gidx, no need to check altfont.
			return -1;
		}
		if(pwrk->altfontcnt>0){
			pos = DCWOUL_QueryCharAttr(ovgattr, altfont->fontdata, 0/*don't care*/, op);
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
DT32_int oul_getDesignInfo(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo)
{
#define OULFD_LANGDATA 58	/* offset in FDL header to language data. */

	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
	DCWOUL_Handle oulhandle = ovgattr->hDcwOVG;
	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
	DT8_char *curfontdata = ovgattr->fontdata;
	DT_Font *altfont = pwrk->alt_DT_Font;

	Font_Design_Thai *fds = (Font_Design_Thai*)dsninfo;
	Font_Design_Thai fd;
	DT32_long pos;
	DT16_ushort totalh, diffh;
	DT8_char *pdata=NULL;

	DCW_CharAttr_Option op;
	DT32_int /**offY,*/ *bRtoChar, *ratio;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	switch(option){

		case DLO_CHARATTR_LANGTAB_THAI:
			op = DCW_CHARATTR_LANGTAB_THAI;
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
			break;
		case DLO_CHARATTR_XYSCALERATIO:
			ratio = (DT32_int*)dsninfo;
			op = DCW_CHARATTR_XYSCALERATIO;
			*ratio = DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
			if(0 == *ratio)
				*ratio = DCWOUL_BASE_RATIO;
			return 0;
		case DLO_CHARATTR_ISXYSCALE_CHAR:
			bRtoChar = (DT32_int*)dsninfo;
			op = DCW_CHARATTR_ISXYSCALE_CHAR;
			*bRtoChar= DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
			if(DCWOUL_BASE_RATIO == *bRtoChar)
				*bRtoChar = 0;
			if(*bRtoChar)
				*bRtoChar = 1;
			return 0;
		case DLO_CHARATTR_RASSCALERATIO:
			ratio = (DT32_int*)dsninfo;
			op = DCW_CHARATTR_RASSCALERATIO;
			*ratio = DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
			if(0 == *ratio)
				*ratio = DCWOUL_BASE_RATIO;
			return 0;
		case DLO_CHARATTR_ISRASSCALE_CHAR:
			bRtoChar = (DT32_int*)dsninfo;
			op = DCW_CHARATTR_ISRASSCALE_CHAR;
			*bRtoChar= DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
			if(DCWOUL_BASE_RATIO == *bRtoChar)
				*bRtoChar = 0;
			if(*bRtoChar)
				*bRtoChar = 1;
			return 0;
		case DLO_CHARATTR_BINSCALERATIO:
			ratio = (DT32_int*)dsninfo;
			op = DCW_CHARATTR_BINSCALERATIO;
			*ratio = DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
			if(0 == *ratio)
				*ratio = DCWOUL_BASE_RATIO;
			return 0;
		case DLO_CHARATTR_ISBINSCALE_CHAR:
			bRtoChar = (DT32_int*)dsninfo;
			op = DCW_CHARATTR_ISBINSCALE_CHAR;
			*bRtoChar= DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
			if(DCWOUL_BASE_RATIO == *bRtoChar)
				*bRtoChar = 0;
			if(*bRtoChar)
				*bRtoChar = 1;
			return 0;
//		case DLO_CHARATTR_GET_OFFSETY:
//		{
//			DT32_int *offY;
//			offY = (DT32_int*)dsninfo;
//			if(pfc){
//				if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_MOVEY){
//					*offY = (DT32_int)pfc->moveY;
//					return 0;
//				}	
//			}
//			op = DCWOUL_CHARATTR_GET_OFFSETY;
//			*offY = DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
//#if(0)
//			if(*offY){
//				if(pwrk->forcedown!=-1){
//					*offY = pwrk->forcedown;
//				}
//			}
//			else{
//				*offY = rasMoveYbyCodeRange(pwrk, gidx, gseq2idx, attr);
//			}
//#endif
//			if(pfc){
//				pfc->moveY = (DT16_short) *offY;
//				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;
//			}
//			return 0;
//		}
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
//		op = bOffY ? DCWOUL_CHARATTR_GET_OFFSETY : DCWOUL_CHARATTR_GET_LOGHEIGHT;
//		val = DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
//		offy= GET_OFFY_FROM_RETVAL(val);
//		logh= GET_LOGH_FROM_RETVAL(val);
//
//		if(bOffY){
//			*retval = (DT32_int)offy;
//#if (0)
//			if(*retval){
//				if(pwrk->forcedown!=-1){
//					*retval = pwrk->forcedown;
//				}
//			}else{
//				*retval = oulMoveYbyCodeRange(pwrk, gidx, gseq2idx, attr);
//			}
//#endif
//		}else *retval = (DT32_int)logh;
//		if(pfc){
//			pfc->moveY		= offy;
//			pfc->logHeight	= logh;
//			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;
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
		op = DCWOUL_CHARATTR_GET_3IN1_VALUE;
		val = DCWOUL_QueryCharAttr_1(pattr, oulhandle, gidx, gseq2idx, op);
		offy= (DT16_short) DCWOUL_OFFY_FROM_3IN1_VALUE(val);
		logh= (DT16_short) DCWOUL_LOGH_FROM_3IN1_VALUE(val);
		logt= (DT16_short) DCWOUL_LOGT_FROM_3IN1_VALUE(val);

		if(DLO_CHARATTR_GET_OFFSETY==option){
			*retval = (DT32_int)offy;
#if (0)
			if(*retval){
				if(pwrk->forcedown!=-1){
					*retval = pwrk->forcedown;
				}
			}else{
				*retval = oulMoveYbyCodeRange(pwrk, gidx, gseq2idx, attr);
			}
#endif
		}else if(DLO_CHARATTR_GET_LOGHEIGHT==option){
			*retval = (DT32_int)logh;
		}else if(DLO_CHARATTR_GET_LOGTOP==option){
			*retval = (DT32_int)logt;
		}
		if(pfc){
			pfc->moveY		= offy;
			pfc->logHeight	= logh;
			pfc->logTop		= logt;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;
		}
		return 0;
	}		
	
#if(0)
		case DLO_CHARATTR_RATIO_FILEWIDE:
			ratio = (DT32_int*)dsninfo;
			*ratio= rasRatiobyFDLFile_1(pwrk,gidx);
			if(0 == *ratio)
				*ratio = DCWOUL_BASE_RATIO;
			return 0;
			break;
		case DLO_CHARATTR_ISSCALE_FILEWIDE:
			bRtoChar = (DT32_int*)dsninfo;
			*bRtoChar= rasRatiobyFDLFile_1(pwrk,gidx);
			if(0 == *bRtoChar || DCWOUL_BASE_RATIO == *bRtoChar)
				*bRtoChar= 0;
			else
				*bRtoChar= 1;
			return 0;
			break;
#endif

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
				oul_getDesignGlobalInfo(pattr, gidx, DLO_LANGTAB_RSB, (DT_void**)&pdata);
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
	pos = DCWOUL_QueryCharAttr(ovgattr, curfontdata, 0/*don't care*/, op);
	if(pos<=0){
		curfontdata = NULL;
//		if(DCWOUL_GetAw(oulhandle, gidx, ovgattr->vert, ovgattr->fontdata)!=DCW_CODE_NOT_EXIST){
//			// current font contains gidx, no need to check altfont.
//			return -1;
//		}
		if(pfc){
			if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST){ 
			}else{
				oul_chkGlyphExist(pwrk->ras_attr,gidx,gseq2idx);
			}
			if(0==pfc->codeExist || (pfc->codeExist && pfc->existFont!=DLO_ALT_DT_FONT))
				return -1;
		}else{
			if(DCWOUL_GetAw(oulhandle, gidx, ovgattr->vert, ovgattr->fontdata, NULL, NULL)!=DCW_CODE_NOT_EXIST)
				return -1;
		}
		if(pwrk->altfontcnt>0){
			pos = DCWOUL_QueryCharAttr(ovgattr, altfont->fontdata, 0/*don't care*/, op);
			if(pos>0){
				curfontdata = altfont->fontdata;
			}else{
				return -1;
			}
		}
	}

#ifdef THAI_thai
	if(pos>0 && curfontdata && option==DLO_CHARATTR_LANGTAB_THAI){
		  DT32_int scaleh, rx, ry;
		  oul_getRatio(pwrk, gidx, -1, &rx, &ry);
		  if(pwrk->vert)
			  scaleh = rx;
		  else
			  scaleh = ry;	//(DLO_FONT_EMSIZE*ry/DLO_FONT_EMSIZE);
		  if(scaleh<=0)
			  scaleh = DLO_FONT_EMSIZE;

		  pos += (2+4);
		  fd.Thai_Top	= (DT16_ushort)FD_READINTBYDATA2(curfontdata,pos/*,2*/);	pos += 2;
		  fd.Thai_Above	= (DT16_ushort)FD_READINTBYDATA2(curfontdata,pos/*,2*/);	pos += 2;
		  fd.Thai_Base	= (DT16_ushort)FD_READINTBYDATA2(curfontdata,pos/*,2*/);	pos += 2;
		  fd.Thai_Below	= (DT16_ushort)FD_READINTBYDATA2(curfontdata,pos/*,2*/);	pos += 2;
		  fd.Thai_Shift	= (DT16_ushort)FD_READINTBYDATA2(curfontdata,pos/*,2*/);	pos += 2;
		  
		  totalh = fd.Thai_Top + fd.Thai_Above + fd.Thai_Base + fd.Thai_Below;
		  diffh  = totalh - 1;
		  // No matter vert or not, these values are the same.
		  fds->Thai_Top		= (fd.Thai_Top*scaleh+diffh)/totalh;
		  fds->Thai_Above	= ((fd.Thai_Top+fd.Thai_Above)*scaleh+diffh)/totalh - fds->Thai_Top;
		  fds->Thai_Base	= ((fd.Thai_Top+fd.Thai_Above+fd.Thai_Base)*scaleh+diffh)/totalh - fds->Thai_Top - fds->Thai_Above;
		  fds->Thai_Below	= scaleh - (fds->Thai_Top+fds->Thai_Above+fds->Thai_Base);
		  fds->Thai_Shift	= fd.Thai_Shift*scaleh/totalh;
		  return 0;
	}
#endif

	if(pos>0 && curfontdata && option==DLO_CHARATTR_LANGTAB_DESCENT){
		Font_Design_Descent *fdsl = (Font_Design_Descent*)dsninfo;
		pos += 2;
		fdsl->nSize		= FD_READINTBYDATA4(curfontdata,pos/*,4*/);	pos += 4;
		fdsl->nOffset	= pos;
		fdsl->fontdata	= curfontdata;
		return 0;
	}

//	{
//	DT32_int i, bskip;
//	DT32_long langoff, langlen;
//	DT16_ushort langcnt, langid;
//	langoff = oulFDL_ReadInt(curfontdata,OULFD_LANGDATA,4);	
//	if(!langoff)	return -1;
//
//	langcnt = (DT16_ushort)oulFDL_ReadInt(curfontdata,langoff,2);
//	pos = langoff + 2;
//	for(i=0;i<langcnt;i++){
//		bskip=1;	
//		langid = (DT16_ushort)oulFDL_ReadInt(curfontdata,pos,2);
//		langlen= oulFDL_ReadInt(curfontdata,pos+2,4);
//#ifdef THAI_thai
//		if(langid==DLO_LANG_THA){
//		  pos += (2+4);
//		  fd.Thai_Top	= (DT16_ushort)oulFDL_ReadInt(curfontdata,pos,2);	pos += 2;
//		  fd.Thai_Above	= (DT16_ushort)oulFDL_ReadInt(curfontdata,pos,2);	pos += 2;
//		  fd.Thai_Base	= (DT16_ushort)oulFDL_ReadInt(curfontdata,pos,2);	pos += 2;
//		  fd.Thai_Below	= (DT16_ushort)oulFDL_ReadInt(curfontdata,pos,2);	pos += 2;
//		  fd.Thai_Shift	= (DT16_ushort)oulFDL_ReadInt(curfontdata,pos,2);	pos += 2;
//		  
//		  totalh = fd.Thai_Top + fd.Thai_Above + fd.Thai_Base + fd.Thai_Below;
//		  fds->Thai_Top		= fd.Thai_Top*DLO_FONT_EMSIZE/totalh;
//		  fds->Thai_Above	= fd.Thai_Above*DLO_FONT_EMSIZE/totalh;
//		  fds->Thai_Base	= fd.Thai_Base*DLO_FONT_EMSIZE/totalh;
//		  fds->Thai_Below	= DLO_FONT_EMSIZE - (fds->Thai_Top+fds->Thai_Above+fds->Thai_Base);
//		  fds->Thai_Shift	= fd.Thai_Shift*DLO_FONT_EMSIZE/totalh;
//		  bskip=0;
//		  return 0;
//		}
//#endif
//		if(bskip)	pos += langlen;
//	}
//	}

	return -1;
}

/* Get fonts design information							*/
/* return value: 1: use default, 0: success, <0:error	*/
//DT32_int oul_getDesignInfo(DT_void *pattr, DT32_int option, DT_void *dsninfo)
//{
//	Need to implement DCWOUL_QueryCharAttr() in DcwOpenVG;
//	DcwOpenVG_Attr *ovgattr = (DcwOpenVG_Attr*)pattr;
//	Font_Design_Thai *fds;	// = (Font_Design*)dsninfo;
//	Font_Design_Thai fd;
//	Font_Design_Latin *fdsl;
//	DT32_long pos;
//	DT16_ushort totalh;
//
//	pLayWrk pwrk = (pLayWrk)ovgattr->pwrk;
//	DT_Font *altfont = pwrk->alt_DT_Font;
//	DT8_char *curfontdata = ovgattr->fontdata;
//	DT8_char *pdata=NULL;
//	DCW_CharAttr_Option op;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	switch(option){
//	case DLO_LANG_THA:
//		op = DCW_CHARATTR_LANGTAB_THAI;
//		fds = (Font_Design_Thai*)dsninfo;
//		break;
//	case DLO_LANG_ICN:
//		op = DCW_CHARATTR_LANGTAB_ICON;
//		break;
//	case DLO_LANG_LAT:
//		//op = DCW_CHARATTR_LANGTAB_LATN;
//		fdsl = (Font_Design_Latin*)dsninfo;
//		break;
//	default:
//		return -1;
//	}
//
//	/* Don't call DCW_QueryCharAttr_1(), because we need to know which font contains the table we want. */
//	pos = DCW_QueryCharAttr(attr, 0/*don't care*/, option);
//	if(!pos){
//		if(pwrk->altfontcnt>0){
//			attr->fontdata = altfont->fontdata;
//			pos = DCW_QueryCharAttr(attr, 0/*don't care*/, option);
//			attr->fontdata = curfontdata;
//			if(pos){
//				pdata = altfont->fontdata;
//			}else{
//				return -1;
//			}
//		}
//	}else{
//		pdata = curfontdata;
//	}
//
//#ifdef THAI_thai
//	if(pos>0 && pdata){
//		  pos += (2+4);
//		  fd.Thai_Top	= (DT16_ushort)oulFDL_ReadInt(ovgattr->fontdata,pos,2);	pos += 2;
//		  fd.Thai_Above	= (DT16_ushort)oulFDL_ReadInt(ovgattr->fontdata,pos,2);	pos += 2;
//		  fd.Thai_Base	= (DT16_ushort)oulFDL_ReadInt(ovgattr->fontdata,pos,2);	pos += 2;
//		  fd.Thai_Below	= (DT16_ushort)oulFDL_ReadInt(ovgattr->fontdata,pos,2);	pos += 2;
//		  fd.Thai_Shift	= (DT16_ushort)oulFDL_ReadInt(ovgattr->fontdata,pos,2);	pos += 2;
//		  
//		  totalh = fd.Thai_Top + fd.Thai_Above + fd.Thai_Base + fd.Thai_Below;
//		  fds->Thai_Top		= fd.Thai_Top*DLO_FONT_EMSIZE/totalh;
//		  fds->Thai_Above	= fd.Thai_Above*DLO_FONT_EMSIZE/totalh;
//		  fds->Thai_Base	= fd.Thai_Base*DLO_FONT_EMSIZE/totalh;
//		  fds->Thai_Below	= DLO_FONT_EMSIZE - (fds->Thai_Top+fds->Thai_Above+fds->Thai_Base);
//		  fds->Thai_Shift	= fd.Thai_Shift*DLO_FONT_EMSIZE/totalh;
//	  return 0;
//	}
//#endif
//
//#ifdef LATIN_latin
//	if(pos>0 && pdata){
//		return 0;
//	}
//#endif
//
//	return -1;
//}
#endif
