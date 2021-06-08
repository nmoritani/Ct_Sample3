#include "DcwLangModule.h"
#include "DcwLayout.h"


#ifdef DIF_RASTER

#include "DcwShaperVG.h"
#include "DIF_Raster.h"
#include "DTmanager.h"
#include "DigiTypeApi.h"

DT16_ushort DIF_read2(DT8_uchar *from)
{
	DT16_ushort hi=0, lo=0;
	DT8_uchar	*p=from;

DBG_MSG_SHOW_FUNC_NAME();

	lo = *p++;
	hi = *p;
	return (hi<<8) | lo;
}

DT32_uint	DIF_read4(DT8_uchar *from)
{
	DT32_uint a, b, c, d;
	DT8_uchar	*p=from;

DBG_MSG_SHOW_FUNC_NAME();

	a = *p++;	/* lo	  */
	b = *p++;	/* mid-lo */
	c = *p++;	/* mid-hi */
	d = *p;		/* hi	  */

	return (d<<24) | (c<<16) | (b<<8) | a; 
}

/* 0: not DIF font; 1:DIF font. */
DT32_int	isDifFont(DT8_uchar *fontdata)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(!DT_strncmp((DT8_char*)fontdata,"DCW ICON",8))
		return 1;
	else
		return 0;
}

DT8_uchar	getDifMaxW(DT8_uchar *fontdata)
{
DBG_MSG_SHOW_FUNC_NAME();

	return *(fontdata+DIF_MAX_W);
}

DT8_uchar	getDifMaxH(DT8_uchar *fontdata)
{
DBG_MSG_SHOW_FUNC_NAME();

	return *(fontdata+DIF_MAX_H);
}

DT16_ushort	getDifFontcnt(DT8_uchar *fontdata)
{
DBG_MSG_SHOW_FUNC_NAME();

	return DIF_read2(fontdata+DIF_FCNT);
}

DT16_ushort	getDifSecCnt(DT8_uchar *fontdata)
{
DBG_MSG_SHOW_FUNC_NAME();

	return DIF_read2(fontdata+DIF_SECCNT);
}

DT32_uint	getDifAddrTabStart(DT8_uchar *fontdata)
{
	DT32_uint ofs;

DBG_MSG_SHOW_FUNC_NAME();

	ofs = DIF_SECLIST;
	ofs += getDifSecCnt(fontdata)*2;
	return ofs;
}

/* return: >=0:idx of the section; <0:not found. */
DT32_int	getDifSecIdx(DT8_uchar *fontdata, DT16_ushort ch)
{
	DifSec ds;
	DT16_ushort i,seccnt=0,sec=(ch&0xFF00)>>8;
	DT8_uchar *psec;

DBG_MSG_SHOW_FUNC_NAME();

	seccnt = getDifSecCnt(fontdata);
	psec = fontdata + DIF_SECLIST;
	for(i=0;i<seccnt;i++){
		ds.sec = *psec++;
		ds.idx = *psec++;
		if(ds.sec==sec){
			return (DT32_int)ds.idx;
		}
	}
	return -1;
}

/* return: ==0:not found; >0: offset value from the start of AddrTab. */
DT32_uint	getDifCharOffset(DT8_uchar *fontdata, DT16_ushort ch)
{
	DT8_uchar *p2AddrTab;
	DT32_int  idx;

DBG_MSG_SHOW_FUNC_NAME();

	idx = getDifSecIdx(fontdata,ch);
	if(idx<0){
		return 0;
	}

	p2AddrTab = fontdata + getDifAddrTabStart(fontdata);
	p2AddrTab += idx*256*sizeof(DT32_uint);

	return DIF_read4(p2AddrTab+((ch&0x00FF)*sizeof(DT32_uint)));
}

DT8_uchar	*jump2DifCharStart(DT8_uchar *fontdata, DT16_ushort ch)
{
	DT32_uint ofs;

DBG_MSG_SHOW_FUNC_NAME();

	ofs = getDifCharOffset(fontdata,ch);
	if(0==ofs){
		return NULL;
	}
	return fontdata+DIF_SECCNT+ofs;
}

/*************************************************************************************************/
/* Estimate the required working memory */
DT32_int dif_EstimateWkMem()
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;
}

/* Get bdf global information and complete CMap. */
DT32_int dif_initFont( DT_void *pattr, DT8_char *fontdata, DT32_long fWkMemsize, DT8_char *fWkMem, DT_void *pwrk)
{
	DifRaster_Attr *difrasattr = (DifRaster_Attr*)pattr;

DBG_MSG_SHOW_FUNC_NAME();

	difrasattr->pwrk = (pLayWrk)pwrk;
	difrasattr->fontdata = (DT8_uchar*)fontdata;

	return DLO_SUCCESS;
}

DT32_int dif_uninitFont( DT_void *pattr )
{
DBG_MSG_SHOW_FUNC_NAME();

	return DLO_SUCCESS;
}

extern DT_void DT_bitset(DT_void *bmp, DT_size_t offset, DT8_uchar num, DT_size_t bitscnt);
DT32_int dif_getCharbmp(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int bmpw, DT32_int bmph, DT32_int x0, DT32_int y0, DT32_int xbytes, DT8_uchar *bmp, DT_void *op, DT32_int mode)
{
	DifRaster_Attr *difrasattr = (DifRaster_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)difrasattr->pwrk;
	DT32_int i,j,k,m,w=0,h=0,fxbyte=0,copyw=0,copybytes=0,copyh=0,xstart=0;
	DT8_uchar *rect=NULL;
	DT8_uchar *pbmp, *prect, *obmp, *orect;
	DT8_uchar tmpval, topgrade=0xFF, bmask=0x80;
	bmpGlyfOperate *go=NULL;
	//DT32_int offdownX, offdownY, realh;	/* the real height of the bmp for the text. while bmph means the bmp buffer's height.	*/
	DT32_int leading,bottomh,normalh,realh;	/* the real height of the bmp for the text. while bmph means the bmp buffer's height.	*/
	DT32_int edge_l, edge_r, edge_t, edge_b;

DBG_MSG_SHOW_FUNC_NAME();

	rect = jump2DifCharStart(difrasattr->fontdata, ch);
	if(!rect){	/* ch not found. */
		//return 0;				// Modified_By_Jacky_20101213:
		return DLO_EMPTY_FONT;
	}
	w = (DT32_int) *rect++;
	h = (DT32_int) *rect++;
	fxbyte = (w + 7)>>3;

	edge_l = edge_r = edge_t = edge_b = 0;
	pwrk->fengfuncs.getEdge(pwrk->ras_attr, &edge_t, &edge_b, &edge_l, &edge_r);
	leading = (pwrk->linemoveYup<0)?DTAbs(pwrk->linemoveYup):0;
	bottomh	= pwrk->linemoveYdn;

	x0 += pwrk->lobuf->ltpos.x + edge_l;
	y0 += pwrk->lobuf->ltpos.y + edge_t;
	if(pwrk->vert){
		realh   = pwrk->lobuf->bmpwidth;
		normalh = realh - leading - edge_t - edge_b - bottomh;
		if(w<normalh)
			x0 -= CalcOffsetY_forbmph(pwrk, 0, w, /*normalh*/pwrk->xsize);
	}else{
		realh   = pwrk->lobuf->bufsize/Calxbytes(pwrk, pwrk->lobuf->bmpwidth);
		normalh = realh - leading - edge_t - edge_b - bottomh;
		if(h<normalh)
			y0 += CalcOffsetY_forbmph(pwrk, 0, h, /*normalh*/pwrk->ysize);
	}
//	if(pwrk->vert){
//		//offdownX = offdownY = 0;
//		realh = pwrk->lobuf->bmpwidth;
//		offdownX = /*edge_l + */CalcOffsetY_forbmph(pwrk, 0, w, realh);
//		offdownY = edge_t;
//	}else{
//		realh = pwrk->lobuf->bufsize/Calxbytes(pwrk, pwrk->lobuf->bmpwidth);
//		offdownX = edge_l;
//		offdownY = CalcOffsetY_forbmph(pwrk, 0, h, realh);
//	}
//	//realh = pwrk->lobuf->bufsize/Calxbytes(pwrk, pwrk->lobuf->bmpwidth);
//
//	x0 += pwrk->lobuf->ltpos.x + offdownX;		// + edge_l
//	y0 += pwrk->lobuf->ltpos.y + offdownY;		//+ CalcOffsetY_forbmph(pwrk, 0, h, realh);
	if(pwrk->bidirule==DLO_BIDI_DCWRULE && pwrk->lobuf->writedir==DLO_RIGHTTOLEFT){	//Added_By_Jacky_20101201: for R2L && italic
		if(pwrk->vert){
			y0 -= pwrk->fengfuncs.getAexten(pwrk->ras_attr, ch)/2;
			if(y0<0) 
				y0 = 0;	//for safety concern
		}else{
			x0 -= pwrk->fengfuncs.getAexten(pwrk->ras_attr, ch)/2;
			if(x0<0) 
				x0 = 0;	//for safety concern
		}
	}

	// Jacky_20110322 move here to ensure the h is correct when CalcOffsetY_forbmph() above.
//	if(op){
//		/* It should not run into here, dif should not have an op rect. */
//		go = (bmpGlyfOperate *) op;
//		/* Only DCW_SETBKZERO of go->operate will happen now. Do not copy the pixels. */
//		  if(DCW_SETBKZERO==go->operate){
//			h = go->gpoff.y;
//		  }
//	}

	  /* Clear the pixels in rect if needed, Ex: 0x0E10+0x0E39						*/
	  /* Do not clear the pixels in the return buffer to avoid problems when italic.*/
	  if(op){
		/* Only DCW_SETBKZERO of go->operate will happen now. Do not copy the pixels. */
		  if(DCW_SETBKZERO==go->operate){
			  if(pwrk->vert){
				/* Clear the pixels(bits) to 0. */
				DT_size_t leftbits=0;
				leftbits = go->gpoff.x & 7;		// go->gpoff.x should always be 0, so leftbits is also 0.
				for(i=go->gpoff.y;i<go->gpoff.y+go->height;i++){
					prect = ((DT8_uchar*)rect) + i*fxbyte + (go->gpoff.x>>3);
					DT_bitset(prect,leftbits,0,go->lenth);
				}
			  }else{
				/* Do not copy the pixels. */
				h = go->gpoff.y;
			  }
		  }
	  }
	copyw = (bmpw-x0)>w?w:(bmpw-x0);
	copyh = (bmph-y0)>h?h:(bmph-y0);

	if(mode & DLO_LAYOUT_BIT){
		xstart = x0&7;	/* xbytealign=0: x0 is at byte start position */
		if(!xstart){
			copybytes = (copyw+7)>>3;
			pbmp = obmp = bmp + y0*xbytes + (x0>>3);
			prect= orect= rect;
			for(j=0;j<copyh;j++){
				for(i=0;i<copybytes;i++){
					*pbmp++ |= *prect++;
				}
				obmp  += xbytes;	pbmp = obmp;
				orect += fxbyte;	prect= orect;
			}
		}else{
			pbmp = obmp = bmp + y0*xbytes + (x0>>3);
			prect= orect= rect;
			for(j=0;j<copyh;j++){
				for(i=0;i<copyw;i+=8){
					tmpval = *prect++;
					*pbmp++ |= (tmpval>>xstart);
					*pbmp |= (tmpval<<(8-xstart));
				}
				obmp  += xbytes;	pbmp = obmp;
				orect += fxbyte;	prect= orect;
			}			
		}

	}else if(mode & DLO_LAYOUT_BYTE){
		if(pwrk->grade==DLO_GRAY_16 && pwrk->grade_values==DLO_GRADE_INDEX_0X00_0X0F){
			topgrade = 0x0F;
		}
		pbmp = obmp = bmp + y0*xbytes + x0;
		prect= orect= rect;
		for(j=0;j<copyh;j++){
			for(i=0;i<copyw;i+=8){
				tmpval = *prect++;
				m = (copyw-i)>=8?8:(copyw-i);
				bmask = 0x80;
				for(k=0;k<m;k++){
					*pbmp++ |= ((tmpval&bmask)?topgrade:0);
					bmask >>= 1;
				}
			}
			obmp  += xbytes;	pbmp = obmp;
			orect += fxbyte;	prect= orect;
		}	
	}

	//return w+pwrk->spacing;	// Modified_By_Jacky_20101213:
	return DLO_SUCCESS;
}

// Return 0 if ch does NOT exist.
// Return 1 if ch DOES exist.
DT32_int dif_chkGlyphExist( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DifRaster_Attr *difrasattr = (DifRaster_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)difrasattr->pwrk;
	DT8_uchar *cp;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	// don't enable this because it shouldn't get into here when DLO_FONTCODEINFO_CHECKFLAG_EXIST.
	// and CANNOT enable this, because DLO_FONTCODEINFO_CHECKFLAG_EXIST might be set for DLO_CUR_DT_FONT, DLO_ALT_DT_FONT
//	if(pfc)
//		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)
//			return pfc->codeExist;
	
	cp = jump2DifCharStart(difrasattr->fontdata, ch);
	
	if(cp){
		if(pfc){
			pfc->codeExist = 1;
			pfc->existFont = DLO_ICON_DT_FONT;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
			// DIF won't scale, moveY, and no lrsb
			setDefault_Scale_LRsb_MoveY(pfc);
		}
		return 1;
	}else{
		if(pfc){	// always set this, because it's the last check.
			pfc->codeExist = 0;
			pfc->existFont = 0;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
			// DIF won't scale, moveY, and no lrsb
			// it's the last check, should not get into here if ch exists in other fonts.
			setDefault_Scale_LRsb_MoveY(pfc);
		}
		return 0;
	}
//	return 0;
}

DT32_int dif_getAwidth( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DifRaster_Attr *difrasattr = (DifRaster_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)difrasattr->pwrk;
	DT32_int aw, width=0, height=0;
	DT8_uchar *cp;
	DT32_int edge_l, edge_r, edge_t, edge_d;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();
	
	// don't enable this because it shouldn't get into here when DLO_FONTCODEINFO_CHECKFLAG_AW.
//	if(pfc)
//		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW)
//			return (pfc->aw==DIF_CODE_NOT_EXIST || aw==0)?0:pfc->aw+pwrk->spacing;


	cp = jump2DifCharStart(difrasattr->fontdata, ch);
	
	if(cp){
		width = (DT32_int) (*cp++);
		height = (DT32_int) (*cp);
	}

	edge_l=0; edge_r=0; edge_t=0; edge_d=0;
	pwrk->fengfuncs.getEdge( pwrk->ras_attr, &edge_t, &edge_d, &edge_l, &edge_r );

	if(width > 0){
		width += (edge_l+edge_r);
	}
	if(height > 0){
		height += (edge_t+edge_d);
	}

	if(pwrk->vert)
		aw = (height==0)?0:height;	//+pwrk->spacing;
	else
		aw = (width==0)?0:width;	//+pwrk->spacing;	/* Jacky_20100824 */

	if(pfc){
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AW;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
		if(cp){
			pfc->aw = aw;
			pfc->codeExist = 1;
			pfc->existFont = DLO_ICON_DT_FONT;
		}else{
			// always set this, because it's the last check.
			pfc->aw = DIF_CODE_NOT_EXIST;
			pfc->codeExist = 0;
			pfc->existFont = 0;
		}
		// DIF won't scale, moveY, and no lrsb 
		// it's the last check, should not get into here if ch exists in other fonts.
		setDefault_Scale_LRsb_MoveY(pfc);
	}
	return (aw==0)?0:aw+pwrk->spacing;
}

DT32_int dif_getAwidth2(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy)
{
DBG_MSG_SHOW_FUNC_NAME();

	/* Not implement yet. Maybe required when supporting vertical writedir. */
	return 0;
}

DT32_int dif_getAheight(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	DifRaster_Attr *difrasattr = (DifRaster_Attr*)pattr;
	pLayWrk pwrk = (pLayWrk)difrasattr->pwrk;
	DT32_int reth=0, width=0, height=0;
	DT8_uchar *cp;
	DT32_int edge_t, edge_b, edge_l, edge_r;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	// don't enable this because it shouldn't get into here when DLO_FONTCODEINFO_CHECKFLAG_AH.
//	if(pfc)
//		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AH)
//			return pfc->ah;

	
	cp = jump2DifCharStart(difrasattr->fontdata, ch);
	
	if(cp){
		width = (DT32_int) (*cp++);
		height = (DT32_int) (*cp);
		edge_t = edge_b = edge_l = edge_r = 0;
		pwrk->fengfuncs.getEdge( pwrk->ras_attr, &edge_t, &edge_b, &edge_l, &edge_r );
		if(height>0){
			height += edge_t + edge_b;
		}
		if(width>0){
			width += edge_l + edge_r;
		}
		if(pwrk->vert){
			if(width > pwrk->maxdifH)
				pwrk->maxdifH = width;
		}else{
			if(height > pwrk->maxdifH)
				pwrk->maxdifH = height;
		}
	}

	if(pwrk->vert){
		reth = width;
	}else
		reth = height;

	if(pfc){
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AH;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;	
		pfc->ah = reth;
		if(cp){
			pfc->codeExist = 1;
			pfc->existFont = DLO_ICON_DT_FONT;
		}else{
			// always set this, because it's the last check.
			pfc->codeExist = 0;
			pfc->existFont = 0;
		}
		// DIF won't scale, moveY, and no lrsb
		// it's the last check, should not get into here if ch exists in other fonts.
		setDefault_Scale_LRsb_MoveY(pfc);
	}
	return reth;
}

DT32_int dif_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx)
{
	return 0;
}

DT32_int dif_getLogt( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx)
{
	return 0;
}

DT32_int dif_getHeight( DT_void *pattr )
{
	DifRaster_Attr *difrasattr = (DifRaster_Attr*)pattr;
 	pLayWrk pwrk = (pLayWrk)difrasattr->pwrk;

DBG_MSG_SHOW_FUNC_NAME();

	if(pwrk->vert)
		return (DT32_int)getDifMaxW(difrasattr->fontdata);
	else
		return (DT32_int)getDifMaxH(difrasattr->fontdata);
}

DT32_int dif_getWidth( DT_void *pattr )
{
	DifRaster_Attr *difrasattr = (DifRaster_Attr*)pattr;
 	pLayWrk pwrk = (pLayWrk)difrasattr->pwrk;

DBG_MSG_SHOW_FUNC_NAME();

	if(pwrk->vert)
		return (DT32_int)getDifMaxH(difrasattr->fontdata);
	else
		return (DT32_int)getDifMaxW(difrasattr->fontdata);
}

/* The difference between advanced width and width in global part. Just for estimation. */
DT32_int dif_getExten( DT_void *pattr )
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;	
}

/* The difference between advanced width and glyph width. */
DT32_int dif_getAexten( DT_void *pattr, DT16_ushort ch )
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;
}

/* The difference of the vertical extent between a normal font and a bold (Attr->f_edge!=0) font*/
DT32_int dif_getVexten( DT_void *pattr, DT16_ushort ch )
{
DBG_MSG_SHOW_FUNC_NAME();
	
	return 0;
}

/* The edge width (difference between Bold and Normal font).*/
/* t:top-edge; d:down-edge; l:left-edge; r:right-edge		*/
/* return: 0:DLO_SUCCESS; <0:Error							*/
DT32_int dif_getEdge( DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r )
{
DBG_MSG_SHOW_FUNC_NAME();

	if(t)	*t = 0;
	if(d)	*d = 0;
	if(l)	*l = 0;
	if(r)	*r = 0;
	return DLO_SUCCESS;
}

/* Get fonts design information							*/
/* return value: 1: use default, 0: success, <0:error	*/
DT32_int dif_getDesignInfo(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo)
{
DBG_MSG_SHOW_FUNC_NAME();

	/* Now icon font won't contain these info. Do nothing now. */
	return -1;
}

#endif	/* DIF_RASTER */
