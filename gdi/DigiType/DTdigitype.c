/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#include "DTdigitype.h"
#include "DTmanager.h"
#include "DcwShaperDLO.h"
#include "DcwShaperVG.h"
#include "DcwLayout.h"

//#define MOVEORI_TO_FILL_OVGWIDTH		// 2012-05-24: enable this to fill out the rect's width when 1==gDT_BmpWidth_Based_on_Pixels.
										// If this is enabled here, it can cover the same problem when it gets into FastMode,
										// but this can't cover the problem of each glyph's origin. (origin position x can't reflect the offset.)

const DT32_int gEnbale_DT_Charmap = 1;	/* Enable this to convert unicode to glyph id. */

DT_BOOL isStrTheSame(DT16_ushort *str1, DT32_int len1, DT16_ushort *str2, DT32_int len2)
{
	DT32_int i;

	if(len1 != len2)
		return DT_FALSE;
	for(i=0; i<len1; i++){
		if(*str1++ != *str2++){
			return DT_FALSE;
		}
	}
	return DT_TRUE;
}

DT_BOOL isFastMode(pDT_Fontwrk pdtfwrk, DT16_ushort *ucs_str, DT32_int ucs_cnt)
{
	pLayWrk		pwrk = (pLayWrk) pdtfwrk->hShaper;
	
	if(0==gDT_ENABLE_FAST_MODE)
		return DT_FALSE;

	if( /*DLO_ENG_DCWOPENVG==pdtfwrk->engtype &&*/ !pdtfwrk->style.vert && pwrk->fdlLatinOnly && 
		(1==ucs_cnt || /*isAllCharsLatin*/isAllEasyLatin(pwrk, ucs_str, ucs_cnt)) ){
		return DT_TRUE;
	}else
		return DT_FALSE;
}

/*--------------------------------------------------------------*/
/* choose an engine by mode specified. */
DLO_EngineType ChooseEngine(DT_FontType ftype, DT32_int mode)
{
DBG_MSG_SHOW_FUNC_NAME();

	switch(mode){
	case DT_OUTLINE_MODE:
		if(ftype==DTDigiType_FDL)
			return DLO_ENG_DCWOPENVG;
		break;

	case DT_MONOCHROME_MODE:
		if(ftype==DTBitmap_BDF)
			return DLO_ENG_BDFRASTER;
		else if(ftype==DTDigiType_FDL)
			return DLO_ENG_DCWRASTER_MONO;
		break;
	case DT_GRAY256BMP_MODE:
		if(ftype==DTDigiType_FDL){
			return DLO_ENG_DCWRASTER_GRAY256;
		}
		break;
	case DT_GRAY16BMP_MODE:
		if(ftype==DTDigiType_FDL){
			return DLO_ENG_DCWRASTER_GRAY16; /* use gray16 as default, user can change it by DT_SetFontStyle() */
		}
		break;
	default:
		return DLO_ENG_END;
	}
	return DLO_ENG_END;
}

/*--------------------------------------------------------------*/
/* estimate the size of buffer required for return. */
DT32_int Estimate_rtbuffer_Size(DLO_EngineType eng)
{
DBG_MSG_SHOW_FUNC_NAME();

	switch(eng){
	case DLO_ENG_DCWOPENVG:
		return sizeof(DT_OulBuf);
	case DLO_ENG_BDFRASTER:
	case DLO_ENG_DCWRASTER_MONO:
	case DLO_ENG_DCWRASTER_GRAY16:
	case DLO_ENG_DCWRASTER_GRAY256:
		return sizeof(DT_LayBuf);
	default:
		return 0;
	}
}

/*--------------------------------------------------------------*/
/* estimate the required data buffer size for return.					*/
/* DLO_ENG_DCWOPENVG engine: the buffer to contain outline paths & segs */
/* other engine: the buffer to contain bmp data, 1 byte or bit per pixel*/
/* isSuggest=0: estimate according to current settings;					*/
/* isSuggest=1: suggestion values according to current settings;		*/
DT32_int Estimate_rtdata_Size(DLO_EngineType eng, DT32_int isSuggest)
{
	DT32_int maxw;	//=(gDT_FONTSIZE_FOR_MALLOC+2*DT_STYLE_MAX_EDGE_WIDTH);
	DT32_int cnt;

DBG_MSG_SHOW_FUNC_NAME();

	if(isSuggest==0){
		maxw=(gDT_FONTSIZE_FOR_MALLOC+2*DT_STYLE_MAX_EDGE_WIDTH);
		cnt = gDT_MAX_BMPRECT_CNT_PER_STR;
	}else{
		maxw=(gDT_FONT_MAXSIZE+2*DT_STYLE_MAX_EDGE_WIDTH);
		if(DT_MAX_GLYPHS_PER_STR > gDT_MAX_BMPRECT_CNT_PER_STR){
			cnt = DT_MAX_GLYPHS_PER_STR;
		}else{
			cnt = gDT_MAX_BMPRECT_CNT_PER_STR;
		}
	}

	if(0==isSuggest && 1==gDT_Dont_Alloc_BmpBuf_When_CreateFont && eng!=DLO_ENG_DCWOPENVG){
		return 0;//DT_BLOCKSIZE;
	}

	switch(eng){
	case DLO_ENG_DCWOPENVG:
#if (1==DT_OPENVG_ENABLED)
		{	// 2012-01-19: ensure it's enough for the data size of OVGformat for each glyph.
			DT32_int n1, n2;
			n1 = DLO_MAX_OUL_SIZE_PER_GLYPH*cnt;
			n2 = gDT_MAX_SEGS_PER_GLYPH + gDT_MAX_SEGS_PER_GLYPH*2*2*4;	// 2 (points), 2 (x,y), 4 sizeof(VGfloat)
			return (n1 > n2) ? n1 : n2;
		}
#else
	return DLO_MAX_OUL_SIZE_PER_GLYPH*cnt;
#endif
	case DLO_ENG_BDFRASTER:
	case DLO_ENG_DCWRASTER_MONO:
		/* force 4 bytes alignment */
		//return (DT_MAX_GLYPHS_PER_STR*maxw+DT_FONT_MAXITALIC+31)/32*4*maxw;
		//return (gDT_MAX_BMPRECT_CNT_PER_STR*maxw+gDT_FONT_MAXITALIC+31)/32*4*maxw;
		return (cnt*maxw+gDT_FONT_MAXITALIC+31)/32*4*maxw;
	case DLO_ENG_DCWRASTER_GRAY16:
	case DLO_ENG_DCWRASTER_GRAY256:
		/* force 4 bytes alignment */
		//return (DT_MAX_GLYPHS_PER_STR*maxw+DT_FONT_MAXITALIC+3)/4*4*maxw;
		//return (gDT_MAX_BMPRECT_CNT_PER_STR*maxw+gDT_FONT_MAXITALIC+3)/4*4*maxw;
		return (cnt*maxw+gDT_FONT_MAXITALIC+3)/4*4*maxw;
	default:
		return 0;
	}
}

/*--------------------------------------------------------------*/
/* decide the grade value according to the mode while DT_CreateFont() */
DT32_int getGradeValue(DT32_int mode)
{
DBG_MSG_SHOW_FUNC_NAME();

	switch(mode){
	case DT_MONOCHROME_MODE:
		return DT_GRAY_MONO;
	case DT_GRAY256BMP_MODE:
		return DT_GRAY_256;
	case DT_GRAY16BMP_MODE:
		return DT_GRAY_16;
	case DT_OUTLINE_MODE:
	default:
		return -1;
	}
}

/*--------------------------------------------------------------*/
/* Get grade value by engine type. */
DT32_int getGradebyEngine(DLO_EngineType eng)
{
DBG_MSG_SHOW_FUNC_NAME();

	switch(eng){
	case DLO_ENG_DCWRASTER_MONO:
		return DT_GRAY_MONO;
	case DLO_ENG_DCWRASTER_GRAY256:
		return DT_GRAY_256;
	case DLO_ENG_DCWRASTER_GRAY16:
		return DT_GRAY_16;
	case DLO_ENG_DCWOPENVG:
	case DLO_ENG_BDFRASTER:
	default:
		return -1;
	}
}

/*--------------------------------------------------------------*/
/* Convert the DigiTypeAPI's DT_FSTYLE_GRAD to the value in DcwShaper. */
DT32_int conv2DcwShaperGrade(DT32_int grade)
{
DBG_MSG_SHOW_FUNC_NAME();

	switch(grade){
	case DT_GRAY_MONO:
		return DLO_GRAY_MONO;
	case DT_GRAY_256:
		return DLO_GRAY_256;
	case DT_GRAY_16:
		return DLO_GRAY_16;
	default:
		return DLO_GRAY_16;
	}
}

/*--------------------------------------------------------------*/
/* Set Default Font Style while DT_CreateFont() */
DT_void setDefaultStyle(pDT_Fontwrk pdtfwrk)
{
	DT32_int ret;

DBG_MSG_SHOW_FUNC_NAME();

	if(pdtfwrk->engtype==DLO_ENG_BDFRASTER){
		ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_WRITEDIR,DT_LEFTTORIGHT);
		ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_XBYTE_ALIGN,4);
		ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_GRAD,DT_GRAY_MONO);
		ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_BIDI_RULE,gDT_DEFAULT_BIDI_RULE);
		return;
	}

	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_SIZEX,gDT_FONT_DEFSIZE);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_SIZEY,gDT_FONT_DEFSIZE);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_GRAD,getGradebyEngine(pdtfwrk->engtype));
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_GRAD_VALUES,DT_GRADE_DEFAULT/*DT_GRADE_INDEX_0X00_0X0F*/);
	/* gcolor isn't set here, use DcwShaper's default */
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_F_EDGE,DT_STYLE_NORMAL);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_W_EDGE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_VERT,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_ITALICAMOUNT,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_W_UNDERLINE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_P_UNDERLINE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_E_UNDERLINE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_W_STRIKE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_P_STRIKE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_E_STRIKE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_DEGREE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_WRITEDIR,DT_LEFTTORIGHT);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_VG_COORD,DT_COORD_LEFT_BOT);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_XBYTE_ALIGN,4);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_HINTING,1);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_FORCE_MOVE_DOWN,-1);	// default by fontdata forcedown table.
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_BIDI_RULE,gDT_DEFAULT_BIDI_RULE);

	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_IS_BOLD,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_IS_ITALIC,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_IS_UNDERLINE,0);
	ret = DT_SetFontStyle(pdtfwrk,DT_FSTYLE_IS_STRIKE,0);

}

/*--------------------------------------------------------------*/
/* get glyphs count in the FDL font. Assume unicode ctmode.		 */
DT_void getGlyphsCount(pDT_Fontwrk pdtfwrk)
{
	DT16_ushort fontidx=0;

DBG_MSG_SHOW_FUNC_NAME();

	pdtfwrk->charmap_num = 0;
	pdtfwrk->charmap[ pdtfwrk->charmap_num++ ] = 0;
	for(fontidx=32; fontidx < 0xFFFF; fontidx++){
		if(DLO_GetCharAw(pdtfwrk->hShaper,fontidx) > 0){
			pdtfwrk->charmap[ pdtfwrk->charmap_num++ ] = fontidx;
		}
	}
}

/*--------------------------------------------------------------*/
/* Convert the DCWShaper's return values (DLO_XXXX) to DigiTypeAPI's */
DT32_int convReturnValue(DT32_int ret)
{
	DT32_int rtval = DT_SUCCESS;

DBG_MSG_SHOW_FUNC_NAME();

	switch(ret){
	case DLO_BAD_HANDLE:
		rtval = DT_BAD_FONT_HANDLE;
		break;
	case DLO_MEM_NOT_ENF_GLYFSQ:
	case DLO_MEM_NOT_ENF_CARETSQ:
	case DLO_UCS_STR_TOO_LONG:
	case DLO_SEG_ERROR:
		rtval = DT_UCS_STR_TOO_LONG;
		break;
	case DLO_UCS_ERR:
		rtval = DT_UCS_ERR;
		break;
	case DLO_SCRIPT_NOT_SUPPORT:
		rtval = DT_SCRIPT_NOT_SUPPORT;
		break;
	case DLO_LANG_NOT_SUPPORT:
		rtval = DT_LANG_NOT_SUPPORT;
		break;
	case DLO_ENGINEWKMEM_ERR:
		rtval = DT_ENGINEWKMEM_ERR;
		break;
	case DLO_FONTSTYLE_ERROR:
	case DLO_INVALID_FONTSIZE:
	case DLO_SPACING_ERR:
		rtval = DT_FONTSTYLE_ERROR;
		break;
	case DLO_NOT_ENOUGH_PATHMEM:
		rtval = DT_NOT_ENOUGH_BUFFER;
		break;
	case DLO_FONTENGINE_NOT_SUPPORT:
		rtval = DT_CREATEFONT_MODE_ERR;
		break;
	case DLO_TEMPBUF_NOT_ENOUGH:
		rtval = DT_TEMP_BUFFER_ERR;
		break;
	default:
		rtval = DT_SUCCESS;
	}
	
	/* Followings are some kind of success. */
	if(ret>DLO_SUCCESS && rtval==DT_SUCCESS){
		if(ret & DLO_EMPTY_FONT){
			rtval |= DT_WARNING_EMPTY_FONT;
		}
		if(ret & DLO_BREAKLINE){
			rtval |= DT_WARNING_BREAKLINE;
		}
	}
	return rtval;
}



/*--------------------------------------------------------------*/
DT_void setBoldStyle(pDT_Fontwrk pdtfwrk, DT32_int bBold)
{	
	DT32_int fsize = pdtfwrk->style.ysize;	//(pdtfwrk->style.xsize + pdtfwrk->style.ysize)/2;

DBG_MSG_SHOW_FUNC_NAME();

	if(bBold){
//	  if(fsize<=24/*16*/){
//		pdtfwrk->style.f_edge = DT_STYLE_BOLD_RIGHT;
//		pdtfwrk->style.w_edge = 1;	//fsize/12;
//	  }else if(fsize<=48/*24*/){
//		pdtfwrk->style.f_edge = DT_STYLE_BOLD_RIGHT_DOWN;
//		pdtfwrk->style.w_edge = 1;
//	  }else if(fsize<72){
//		pdtfwrk->style.f_edge = DT_STYLE_BOLD;
//		pdtfwrk->style.w_edge = fsize/36 + 1;
//	  }else{
//		pdtfwrk->style.f_edge = DT_STYLE_BOLD;
//		pdtfwrk->style.w_edge = fsize/72 + 2;
//	  }
//#ifdef DT_ANDROID
//		pdtfwrk->style.w_edge = 1;		/* force to 1 only */
//#endif
		pdtfwrk->style.f_edge = DT_AUTOGET_F_EDGE(fsize);
		pdtfwrk->style.w_edge = DT_AUTOGET_W_EDGE(fsize);
	}else{
		pdtfwrk->style.f_edge = DT_STYLE_NORMAL;
		pdtfwrk->style.w_edge = 0;
	}
	DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_F_EDGE,pdtfwrk->style.f_edge);
	DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_W_EDGE,pdtfwrk->style.w_edge);
	// sync!
	pdtfwrk->style.w_edge266 = (DT_f26dot6)DTFixToF266(pdtfwrk->style.w_edge,0);
	DLO_SetFontStyle(pdtfwrk->hShaper, FSTYLE_W_EDGE_26_6, (DT32_int) (pdtfwrk->style.w_edge266) );

}

/*--------------------------------------------------------------*/
DT_void setItalicStyle(pDT_Fontwrk pdtfwrk, DT32_int bItalic)
{	
	DT32_int fsize = pdtfwrk->style.ysize;

DBG_MSG_SHOW_FUNC_NAME();

	if(bItalic){
		pdtfwrk->style.italic = DT_AUTOGET_ITALICMOUNT(fsize);//fsize/2;
	}else{
		pdtfwrk->style.italic = 0;
	}
//	if( (pdtfwrk->style.xsize+pdtfwrk->style.italic)*pdtfwrk->style.ysize > 
//		((pDT_FontMgr_wrk)pdtfwrk->font->fontmgr)->tmpbufsize){
//		return;
//	}	// Marked_By_Jacky_20101122: Check it later.
	DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_ITALIC,pdtfwrk->style.italic);
	pdtfwrk->style.e_underline = pdtfwrk->style.italic;
	//DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_E_UNDERLINE,pdtfwrk->style.italic);		// Jacky_20100727_underline
}

/*--------------------------------------------------------------*/
DT_void setUnderlineStyle(pDT_Fontwrk pdtfwrk, DT32_int bUnderline)
{	
	DT32_int fsize = pdtfwrk->style.ysize;

DBG_MSG_SHOW_FUNC_NAME();

	if(bUnderline){
		pdtfwrk->style.w_underline = DT_AUTOGET_W_EDGE(fsize);	//(fsize/16)<1?1:fsize/16;
	}else{
		pdtfwrk->style.w_underline = 0;
	}
	pdtfwrk->style.p_underline = DT_DEFAULT_P_UNDERLINE(fsize);
	pdtfwrk->style.e_underline = pdtfwrk->style.italic;
	//DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_P_UNDERLINE,pdtfwrk->style.p_underline);	// Jacky_20100727_underline
	//DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_W_UNDERLINE,pdtfwrk->style.w_underline);	// Jacky_20100727_underline
	//DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_E_UNDERLINE,pdtfwrk->style.italic);		// Jacky_20100727_underline
}

/*--------------------------------------------------------------*/
DT_void setStrikeStyle(pDT_Fontwrk pdtfwrk, DT32_int bStrike)
{	
	DT32_int fsize = pdtfwrk->style.ysize;

DBG_MSG_SHOW_FUNC_NAME();

	if(bStrike){
		pdtfwrk->style.w_strike = DT_AUTOGET_W_EDGE(fsize);		//(fsize/16)<1?1:fsize/16;
	}else{
		pdtfwrk->style.w_strike = 0;
	}
	pdtfwrk->style.p_strike = DT_DEFAULT_P_STRIKE(fsize);	//2*fsize/5;
	pdtfwrk->style.e_strike = pdtfwrk->style.italic;
}

/*--------------------------------------------------------------*/
/* Parse the n_per_glyf in GlyphSeq to codes and glyphs. */
/* n_per_glyf: the HiByte stands for glyfs, the LowByte stands for codes. */
DT_void parse_n_per_glyf(DT16_ushort n_per_glyf, DT16_ushort *codes, DT16_ushort *glyfs)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(n_per_glyf>0x0100){
		*codes =(DT16_ushort) (n_per_glyf&0x00FF);
		*glyfs =(DT16_ushort) (n_per_glyf&0xFF00)>>8;
	}else{
		*codes = n_per_glyf;
		*glyfs = 1;
	}
}

#define GETCODES_N_PER_GLYF(npg) ((npg)>0x0100)?((npg)&0x00FF):(npg)
#define GETGLYFS_N_PER_GLYF(npg) ((npg)>0x0100)?(((npg)&0x00FF)>>8):(1)
/*--------------------------------------------------------------*/
/* Make DT_LayBuf for return */
DT32_int makeRTlaybuf(pDT_Fontwrk pdtfwrk)
{
	DT_LayBuf	*dtlay = pdtfwrk->laybuf;
	DLO_LayBuf	*dlolay= pdtfwrk->dlolaybuf;
	DT_PosInfo  *pi;						// 2012-02-07: use pointer for performance
	DT16_ushort i, g=0, c=0;
	DLO_CodePositioning *pos;

DBG_MSG_SHOW_FUNC_NAME();

	dtlay->gcnt = dlolay->glyf_cnt;
	dtlay->glyphs = (DT16_ushort*) dlolay->glyf_seq;
	dtlay->writedir = dlolay->writedir;
	dtlay->bmpwidth = dlolay->bmpwidth;
	dtlay->bmpheight= dlolay->bmpheight;
	dtlay->xbytes   = dlolay->xbytes;
	dtlay->bitcount = dlolay->bitcount;
	dtlay->bufsize  = dlolay->bufsize;
	dtlay->bmpbuf   = NULL;

//	DT_memset(pdtfwrk->laycarets,0,DT_MAX_GLYPHS_PER_STR*sizeof(DT_PosInfo));

	//DT_memset(&pi,0,sizeof(DT_PosInfo));		// 2012-02-07: not required
	pos = dlolay->caret_seq;
	pi = &pdtfwrk->laycarets[0];
	for(i=0;(i < dtlay->gcnt && i < DT_MAX_GLYPHS_PER_STR); i++, pos++, pi++)
	{
		//pi.gidx = dlolay->caret_seq[i].glyfidx;
		pi->gidx = pos->glyfidx;
		/* Because only the glyph that starts a cell has a non-zero value of n_per_glyf,	*/
		/* we calculate the position only when it's non-zero. Cell info will be the same.	*/
		if(pos->n_per_glyf)
		{
			//g = GETGLYFS_N_PER_GLYF(dlolay->caret_seq[i].n_per_glyf);	/* Notice: be aware of the type. MACRO doen't check type */
			//c = GETCODES_N_PER_GLYF(dlolay->caret_seq[i].n_per_glyf);	/* Notice: be aware of the type. MACRO doen't check type */
			parse_n_per_glyf(pos->n_per_glyf,&c,&g);
			// Marked by Jacky 20110316, since UAX#9:Bidi
			//pi.sgidx= pos->glyfidx;
			//pi.gextn= g;
			//pi.scidx=  pos->codeidx;
			//pi.cextn= c;
		}

		pi->caretpos.x = pos->caretpos.x;
		pi->caretpos.y = pos->caretpos.y;
		//pdtfwrk->laycarets[i] = pi;
	}

	dtlay->carets = pdtfwrk->laycarets;

	return DT_SUCCESS;
}

/*--------------------------------------------------------------*/
/* Make DT_OulBuf for return */
DT32_int makeRToulbuf(pDT_Fontwrk pdtfwrk)
{
	DT_OulBuf	*dtoul = pdtfwrk->oulbuf;
	DLO_LayBuf	*dlolay= pdtfwrk->dlolaybuf;
	DT_OulPos   *pi;						// 2012-02-07: use pointer for performance
	DT16_ushort i, g=0, c=0;

DBG_MSG_SHOW_FUNC_NAME();

	dtoul->gcnt = dlolay->glyf_cnt;
	dtoul->glyphs = (DT16_ushort*) dlolay->glyf_seq;
	dtoul->writedir = dlolay->writedir;
	dtoul->eswidth  = dlolay->eswidth;
	dtoul->esheight = dlolay->esheight;
	dtoul->pixwidth	= dlolay->bmpwidth;
	dtoul->pixheight= dlolay->bmpheight;
	dtoul->olbuf    = NULL;
	dtoul->olbufsize= 0;
	dtoul->olsizes  = NULL;

//	DT_memset(pdtfwrk->oulcarets,0,DT_MAX_GLYPHS_PER_STR*sizeof(DT_OulPos));

	//DT_memset(&pi,0,sizeof(DT_OulPos));		// 2012-02-07: not required
	pi = &pdtfwrk->oulcarets[0];
	for(i=0;(i<dtoul->gcnt && i<DT_MAX_GLYPHS_PER_STR);i++, pi++){
		pi->gidx = dlolay->caret_seq[i].glyfidx;
		/* Because only the glyph that starts a cell has a non-zero value of n_per_glyf,	*/
		/* we calculate the position only when it's non-zero. Cell info will be the same.	*/
		if(dlolay->caret_seq[i].n_per_glyf){
			//g = GETGLYFS_N_PER_GLYF(dlolay->caret_seq[i].n_per_glyf);	/* Notice: be aware of the type. MACRO doen't check type */
			//c = GETCODES_N_PER_GLYF(dlolay->caret_seq[i].n_per_glyf);	/* Notice: be aware of the type. MACRO doen't check type */
			parse_n_per_glyf(dlolay->caret_seq[i].n_per_glyf,&c,&g);
			// Marked by Jacky 20110316, since UAX#9:Bidi
			//pi->sgidx= dlolay->caret_seq[i].glyfidx;
			//pi->gextn= g;
			//pi->scidx= dlolay->caret_seq[i].codeidx;
			//pi->cextn= c;
		}
		pi->caretpos.x = dlolay->caret_seq[i].caretpos.x;
		pi->caretpos.y = dlolay->caret_seq[i].caretpos.y;
		pi->oripos.x   = dlolay->caret_seq[i].oripos.x;
		pi->oripos.y   = dlolay->caret_seq[i].oripos.y;
		pi->awvec.vx   = dlolay->caret_seq[i].awvec.vx;
		pi->awvec.vy   = dlolay->caret_seq[i].awvec.vy;
		pi->adjvec.vx  = dlolay->caret_seq[i].adjvec.vx;
		pi->adjvec.vy  = dlolay->caret_seq[i].adjvec.vy;
		pi->drawmethod = dlolay->caret_seq[i].drawmethod;
		pi->dmrect.xy.x= dlolay->caret_seq[i].dmrect.xy.x;
		pi->dmrect.xy.y= dlolay->caret_seq[i].dmrect.xy.y;
		pi->dmrect.hw.vx= dlolay->caret_seq[i].dmrect.hw.vx;
		pi->dmrect.hw.vy= dlolay->caret_seq[i].dmrect.hw.vy;
		//pdtfwrk->oulcarets[i] = pi;
	}

	dtoul->carets = pdtfwrk->oulcarets;

	return DT_SUCCESS;
}

/*--------------------------------------------------------------*/
/* make DT_DrawData to pass to DT_RasterBitBlt()				*/
DT_void makeDrawData(pDT_Fontwrk pdtfwrk, pDT_LayBuf dtlaybuf, DT_RGBA *fclr, DT_RGBA *bclr, DT_DrawData *drawdata)
{
DBG_MSG_SHOW_FUNC_NAME();

		drawdata->bitcount = dtlaybuf->bitcount;
		drawdata->bmpsize  = dtlaybuf->bufsize;
		drawdata->nWidth   = dtlaybuf->bmpwidth;
		drawdata->nHeight  = dtlaybuf->bmpheight;
		drawdata->xbytes   = dtlaybuf->xbytes;
		drawdata->grade    = pdtfwrk->style.grade;
		drawdata->grade_values = pdtfwrk->style.grade_values;
		drawdata->fontcolor= *fclr;
		drawdata->backcolor= *bclr;
		drawdata->bmpbuf   = dtlaybuf->bmpbuf;
}

/* offset must be 0~7, num is 0 or 1 */
DT_void DT_bitset(DT_void *bmp, DT_size_t offset, DT8_uchar num, DT_size_t bitscnt)
{
	DT_size_t i, diff, rbits;
	DT8_uchar *p, val;

	i = 0;
	p = bmp;

	if(num){
		rbits = 8 - offset;
		val = 0xFF >> offset;	// keep right bits.
		if(bitscnt<rbits){
			diff = rbits-bitscnt;
			val &= (val>>diff)<<diff;
		}
		for(;i<rbits;i+=rbits){
			*p++ |= val;
		}
		
		val = 0xFF;
		if(!num)
			val = ~val;
		for(;i+8<bitscnt;i+=8){
			*p++ |= val;
		}

		val = 0xFF >> (bitscnt-i);
		val = ~val;	// keep left bits.
		for(;i<bitscnt;i+=(bitscnt-i)){
			*p++ |= val;
		}
	}else{
		rbits = 8 - offset;
		val = 0xFF >> offset;	// keep right bits.
		if(bitscnt<rbits){
			diff = rbits-bitscnt;
			val &= (val>>diff)<<diff;
		}
		val = ~val;

		for(;i<rbits;i+=rbits){
			*p++ &= val;
		}
		
		val = 0xFF;
		if(!num)
			val = ~val;
		for(;i+8<bitscnt;i+=8){
			*p++ &= val;
		}

		val = 0xFF >> (bitscnt-i);
		for(;i<bitscnt;i+=(bitscnt-i)){
			*p++ &= val;
		}		
	}
}

/*--------------------------------------------------------------*/
DT_void drawBMPUnderline_vert(pDT_Fontwrk pdtfwrk, DLO_LayBuf* buf)
{
	DT_StyleAttr *sattr = &pdtfwrk->style;
	DT32_int i, j, height=0, thick=0, /*exten=0, aw=0, linebytes=0,*/ leftbits=0, gval=-1, pos=0;
	DT_Point start;
	DT8_uchar *p;
	DT32_int basepos, def_p, edge_l=0, edge_r=0, leading=0, bottomh=0; 
	pLayWrk	 pwrk = (pLayWrk)pdtfwrk->hShaper;

DBG_MSG_SHOW_FUNC_NAME();

	if(!buf->bmpbuf || buf->bmpwidth<=0 || buf->bmpheight<=0)
		return;

	height  = buf->bmpheight;
	leading = DTAbs(pwrk->linemoveYup);
	bottomh = pwrk->linemoveYdn;
	pwrk->fengfuncs.getEdge(pwrk->ras_attr,NULL,NULL,&edge_l,&edge_r);
	if(pwrk->maxdifH>edge_r + sattr->xsize + edge_l)
		basepos = 0;
	else
		basepos = buf->bmpwidth - leading - edge_r - sattr->xsize - edge_l;

	if(basepos < 0)
		basepos = 0;
	if(basepos > buf->bmpwidth)
		basepos = buf->bmpwidth;

	if(sattr->xsize > buf->bmpwidth)
		def_p = DT_DEFAULT_P_UNDERLINE(buf->bmpwidth);
	else def_p = DT_DEFAULT_P_UNDERLINE(sattr->xsize);

	pos = basepos + sattr->p_underline;
	if( pos<0 || pos > buf->bmpwidth){
		pos = basepos + def_p;			// Set it as default normal size.
	}
	thick = sattr->w_underline;
	if(pos - thick < 0){
		pos = basepos;
		thick = 1;
	}

	if(buf->bitcount==8){
		if( sattr->grade==DT_GRAY_16 &&
			sattr->grade_values==DT_GRADE_INDEX_0X00_0X0F){
			gval = 0xF;
		}
		start.x = buf->ltpos.x + pos;	//+ (buf->bmpwidth - pos - thick);
		start.y = buf->ltpos.y;
		p = (DT8_uchar*)buf->bmpbuf + (start.x + start.y*buf->xbytes);
		for(i=0;i<height;i++){
			DT_memset((DT_void*)p,gval,thick);
			p += buf->xbytes;
		}
	}else if(buf->bitcount==1){
		start.x = buf->ltpos.x + pos;	//+ (buf->bmpwidth - pos - thick);
		start.y = buf->ltpos.y;
		leftbits = start.x & 7;
		p = (DT8_uchar*)buf->bmpbuf + (start.y*buf->xbytes + (start.x>>3));
		for(j=0;j<height;j++){
			DT_bitset(p,leftbits,1,thick);
			p  += buf->xbytes;
		}
	}
}

/* draw underline by ourselves to avoid the problem of italic+underline with area cleared, Ex: 0x0E10+0x0E39	*/
/* The original draw method in DLO_xxxxxx was disabled while DT_SetFontStyle().									*/
DT_void drawBMPUnderline(pDT_Fontwrk pdtfwrk, DLO_LayBuf* buf)
{
	DT_StyleAttr *sattr = &pdtfwrk->style;
	DT32_int i, width=0, thick=0,/* exten=0, aw=0, linebytes=0,*/ leftbits=0, gval=-1, pos=0;
	DT_Point start;
	DT8_uchar *p;
	DT32_int basepos, def_p, edge_t=0, edge_b=0, leading=0, bottomh=0; 
	pLayWrk	 pwrk = (pLayWrk)pdtfwrk->hShaper;

DBG_MSG_SHOW_FUNC_NAME();

	if(sattr->vert){
		drawBMPUnderline_vert(pdtfwrk,buf);
		return;
	}

	if(!buf->bmpbuf || buf->bmpwidth<=0 || buf->bmpheight<=0)
		return;

	width = buf->bmpwidth;
	leading = DTAbs(pwrk->linemoveYup);
	bottomh = pwrk->linemoveYdn;
	pwrk->fengfuncs.getEdge(pwrk->ras_attr,&edge_t,&edge_b,NULL,NULL);
	if(pwrk->maxdifH>edge_t + sattr->ysize + edge_b)
		basepos = buf->bmpheight;
	else
		basepos= leading + edge_t + sattr->ysize + edge_b;

	if(basepos < 0)
		basepos = 0;
	if(basepos > buf->bmpheight)
		basepos = buf->bmpheight;
	
	if(sattr->ysize > buf->bmpheight)
		def_p = DT_DEFAULT_P_UNDERLINE(buf->bmpheight);
	else def_p = DT_DEFAULT_P_UNDERLINE(sattr->ysize);

	pos = basepos - sattr->p_underline;
	if( pos<0 || pos > buf->bmpheight){
		pos = basepos - def_p;			// Set it as default normal size.
	}
	thick = sattr->w_underline;
	if(pos - thick < 0){
		pos = basepos;
		thick = 1;	//pos;
	}

	if(buf->bitcount==8){
		if( sattr->grade==DT_GRAY_16 &&
			sattr->grade_values==DT_GRADE_INDEX_0X00_0X0F){
			gval = 0xF;
		}
		start.x = buf->ltpos.x;
		start.y = buf->ltpos.y + pos - thick;
		p = (DT8_uchar*)buf->bmpbuf + (start.x + start.y*buf->xbytes);
		for(i=0;i<thick;i++){
			DT_memset((DT_void*)p,gval,width);
			p += buf->xbytes;
		}
	}else if(buf->bitcount==1){
		start.x = buf->ltpos.x;
		start.y = buf->ltpos.y + pos - thick;
		leftbits = start.x & 7;
		p = (DT8_uchar*)buf->bmpbuf + (start.y*buf->xbytes + (start.x>>3));
		for(i=0;i<thick;i++){
			DT_bitset(p,leftbits,1,width);
			p  += buf->xbytes;
		}
	}
}

/*--------------------------------------------------------------*/
DT_void drawBMPStrike_vert(pDT_Fontwrk pdtfwrk, DLO_LayBuf* buf)
{
	DT_StyleAttr *sattr = &pdtfwrk->style;
	DT32_int i, j, height=0, thick=0, /*exten=0, aw=0, linebytes=0,*/ leftbits=0, gval=-1, pos=0;
	DT_Point start;
	DT8_uchar *p;
	DT32_int basepos, def_p, edge_l=0, edge_r=0, leading=0, bottomh=0; 
	pLayWrk	 pwrk = (pLayWrk)pdtfwrk->hShaper;

DBG_MSG_SHOW_FUNC_NAME();

	if(!buf->bmpbuf || buf->bmpwidth<=0 || buf->bmpheight<=0)
		return;

	height  = buf->bmpheight;
	leading = DTAbs(pwrk->linemoveYup);
	bottomh = pwrk->linemoveYdn;
	pwrk->fengfuncs.getEdge(pwrk->ras_attr,NULL,NULL,&edge_l,&edge_r);
	if(pwrk->maxdifH>edge_r + sattr->xsize + edge_l)
		basepos = 0;
	else
		basepos = buf->bmpwidth - leading - edge_r - sattr->xsize - edge_l;

	if(basepos < 0)
		basepos = 0;
	if(basepos > buf->bmpwidth)
		basepos = buf->bmpwidth;
	
	if(sattr->xsize > buf->bmpwidth)
		def_p = DT_DEFAULT_P_STRIKE(buf->bmpwidth);
	else def_p = DT_DEFAULT_P_STRIKE(sattr->xsize);

	pos = basepos + sattr->p_strike;
	if( pos<0 || pos > buf->bmpwidth){
		pos = basepos + def_p;			// Set it as default normal size.
	}
	thick = sattr->w_strike;
	if(pos - thick < 0){
		pos = basepos + def_p;
		thick = 1;
	}

	if(buf->bitcount==8){
		if( sattr->grade==DT_GRAY_16 &&
			sattr->grade_values==DT_GRADE_INDEX_0X00_0X0F){
			gval = 0xF;
		}
		start.x = buf->ltpos.x + pos;	//+ (buf->bmpwidth - pos - thick);
		start.y = buf->ltpos.y;
		p = (DT8_uchar*)buf->bmpbuf + (start.x + start.y*buf->xbytes);
		for(i=0;i<height;i++){
			DT_memset((DT_void*)p,gval,thick);
			p += buf->xbytes;
		}
	}else if(buf->bitcount==1){
		start.x = buf->ltpos.x + pos;	//+ (buf->bmpwidth - pos - thick);
		start.y = buf->ltpos.y;
		leftbits = start.x & 7;
		p = (DT8_uchar*)buf->bmpbuf + (start.y*buf->xbytes + (start.x>>3));
		for(j=0;j<height;j++){
			DT_bitset(p,leftbits,1,thick);
			p  += buf->xbytes;
		}
	}
}

/* draw strike by ourselves to avoid the problem of italic+strike with area cleared, Ex: 0x0E10+0x0E39	*/
/* It's a new ability which DLO_xxxxxx lacks.															*/
DT_void drawBMPStrike(pDT_Fontwrk pdtfwrk, DLO_LayBuf* buf)
{
	DT_StyleAttr *sattr = &pdtfwrk->style;
	DT32_int i, width=0, thick=0, /*exten=0, aw=0, linebytes=0,*/ leftbits=0, gval=-1, pos=0;
	DT_Point start;
	DT8_uchar *p;
	DT32_int basepos, def_p, edge_t=0, edge_b=0, leading=0, bottomh=0; 
	pLayWrk	 pwrk = (pLayWrk)pdtfwrk->hShaper;

DBG_MSG_SHOW_FUNC_NAME();

	if(sattr->vert){
		drawBMPStrike_vert(pdtfwrk,buf);
		return;
	}

	if(!buf->bmpbuf || buf->bmpwidth<=0 || buf->bmpheight<=0)
		return;

	width = buf->bmpwidth;
	leading = DTAbs(pwrk->linemoveYup);
	bottomh = pwrk->linemoveYdn;
	pwrk->fengfuncs.getEdge(pwrk->ras_attr,&edge_t,&edge_b,NULL,NULL);
	if(pwrk->maxdifH>edge_t + sattr->ysize + edge_b)
		basepos = buf->bmpheight;
	else
		basepos = leading + edge_t + sattr->ysize + edge_b;

	if(basepos < 0)
		basepos = 0;
	if(basepos > buf->bmpheight)
		basepos = buf->bmpheight;
	
	if(sattr->ysize > buf->bmpheight)
		def_p = DT_DEFAULT_P_STRIKE(buf->bmpheight);
	else def_p = DT_DEFAULT_P_STRIKE(sattr->ysize);

	pos = basepos - sattr->p_strike;
	if( pos<0 || pos > buf->bmpheight){
		pos = basepos - def_p;			// Set it as default normal size.
	}
	thick = sattr->w_strike;
	if(pos - thick < 0){
		//thick = pos;
		pos = basepos + def_p;
		thick = 1;
	}

	if(buf->bitcount==8){
		if( sattr->grade==DT_GRAY_16 &&
			sattr->grade_values==DT_GRADE_INDEX_0X00_0X0F){
			gval = 0xF;
		}
		start.x = buf->ltpos.x;
		start.y = buf->ltpos.y + pos - thick;
		p = (DT8_uchar*)buf->bmpbuf + (start.x + start.y*buf->xbytes);
		for(i=0;i<thick;i++){
			DT_memset((DT_void*)p,gval,width);
			p += buf->xbytes;
		}
	}else if(buf->bitcount==1){
		start.x = buf->ltpos.x;
		start.y = buf->ltpos.y + pos - thick;
		leftbits = start.x & 7;
		p = (DT8_uchar*)buf->bmpbuf + (start.y*buf->xbytes + (start.x>>3));
		for(i=0;i<thick;i++){
			DT_bitset(p,leftbits,1,width);
			p  += buf->xbytes;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* DT_OUTLINE_MODE while DT_CreateFont() isn't support this function.	*/
/* DT_MONOCHROME_MODE: Get a 1-bit-per-pixel bmp						*/
/* DT_GRAY16BMP_MODE, DT_GRAY256BMP_MODE: Get a 1-byte-per-pixel bmp.	*/
DT32_int DT_RasterGBMP(DT_Handle hnd, DT16_ushort* ucs_str, DT32_int ucs_cnt, DT32_int flag, pDT_LayBuf *laybuf, 
					   DT_void *myownGBMP, DT32_int xbytesOfmyGBMP, DT32_int hOfmyGBMP, DT_Point lt)
{
	DT32_int		ret, rtval, maxw, maxh, bCut=0;
	pDT_Fontwrk		pdtfwrk = (pDT_Fontwrk) hnd;
	DLO_LayAttr		*lay;
	DLO_LayBuf		*buf;
//	DT8_char		*ptr=NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG){
		return DT_CREATEFONT_MODE_ERR;
	}

	/* force to release the buffer if the flag combined with DT_RELEASE */
	if(flag&DT_RELEASE){
		goto dt_release;
	}

	/* get info */
	if(flag&DT_GET_INFO){
		goto dt_get_info;
	}

	if(flag&DT_DRAW){
		if(!(*laybuf))
			goto dt_get_info;
		else
			goto dt_draw;
	}

dt_get_info:

	if(ucs_cnt<=0 || !ucs_str || ucs_cnt>DT_MAX_CODES_PER_STR)
		return DT_UCS_ERR;

	// FIXME: ysize=xsize is a must when vert
	if( pdtfwrk->engtype == DLO_ENG_DCWRASTER_MONO ||
		pdtfwrk->engtype == DLO_ENG_DCWRASTER_GRAY16 ||
		pdtfwrk->engtype == DLO_ENG_DCWRASTER_GRAY256)
	{
		if(pdtfwrk->style.vert && pdtfwrk->style.xsize!=pdtfwrk->style.ysize){
			pdtfwrk->style.ysize = pdtfwrk->style.xsize;
			DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_SIZEY,pdtfwrk->style.xsize);
		}
	}

	/* Prepare the layattr data */
//	DT_memset(pdtfwrk->dlolayattr,0,pdtfwrk->dlolayattrsz);
	lay = (DLO_LayAttr*)pdtfwrk->dlolayattr;
	lay->mainScript	= DLO_SCRIPT_DFLT;
	lay->mainLang	= DLO_LANG_DFLT;
	lay->ucs_cnt	= ucs_cnt;
	lay->ucs_str	= ucs_str;
	lay->writedir	= pdtfwrk->style.writedir;

	/* Prepare the buffer to receive info from DcwShaper. */
//	DT_memset(pdtfwrk->dlolaybuf,0,pdtfwrk->dlolaybufsz);
	buf	  = (DLO_LayBuf*)pdtfwrk->dlolaybuf;

	ret = DLO_ShapeString(pdtfwrk->hShaper,lay,buf,DLO_DATA_PREPARE_POS);
	rtval = convReturnValue(ret);

	if(rtval<DT_SUCCESS)
		return rtval;

	/* Prepare and clear the buffer for laybuf to return. */
//	DT_memset(pdtfwrk->rtbuffer,0,pdtfwrk->rtbuffersz);
	pdtfwrk->laybuf = (DT_LayBuf *)pdtfwrk->rtbuffer;
	ret = makeRTlaybuf(pdtfwrk);
	*laybuf = pdtfwrk->laybuf;

	if(flag&DT_DRAW){
		goto dt_draw;
	}

	return rtval;

dt_draw:
	/* return as an error if laybuf is empty. */
	if(!(*laybuf))
		return DT_LAYBUF_ERR;

	/* check glyphs count to avoid index over it (maybe modified outside by user). */
	if((*laybuf)->gcnt>DT_MAX_GLYPHS_PER_STR)
		(*laybuf)->gcnt = DT_MAX_GLYPHS_PER_STR;

	/* Check if there is sufficient buffer for return data. */
	if(!myownGBMP){	/* myownGBMP will guarantee it's sufficient */
	  if(pdtfwrk->rtdatasz<(*laybuf)->bufsize){
		// Should not get into here when gDT_Dont_Alloc_BmpBuf_When_CreateFont==0
		  if(0==gDT_Dont_Alloc_BmpBuf_When_CreateFont){
			  return DT_NOT_ENOUGH_BUFFER;
		  }

//		ptr = DT_realloc( pdtfwrk->rtdata, DT_ALLOC_SIZE((*laybuf)->bufsize) );
//		if(!ptr){
//			return DT_NOT_ENOUGH_BUFFER;
//		}else{
//			pdtfwrk->rtdata = ptr;
//			pdtfwrk->rtdatasz = (*laybuf)->bufsize;
//		}
		// Modified_By_Jacky_20101213:
		if(pdtfwrk->rtdata)
			DT_free(pdtfwrk->rtdata);
		pdtfwrk->rtdatasz = DT_ALLOC_SIZE((*laybuf)->bufsize);
		pdtfwrk->rtdata	  = DT_malloc(pdtfwrk->rtdatasz);
		if(!pdtfwrk->rtdata){
			pdtfwrk->rtdatasz = 0;
			return DT_NOT_ENOUGH_BUFFER;
		}else{
			if(pdtfwrk->rtdatasz > pdtfwrk->rtdataszused){
				pdtfwrk->rtdataszused = pdtfwrk->rtdatasz;
			}
		}
	  }
	 }

	lay = (DLO_LayAttr*)pdtfwrk->dlolayattr;
	buf	= (DLO_LayBuf*)pdtfwrk->dlolaybuf;
	
	// Check Temp Buffer Size	// Added_By_Jacky_20101122: Check it here.
	if(pdtfwrk->engtype == DLO_ENG_BDFRASTER){
		/* Need to be checked in the future.*/
	}else if(pdtfwrk->engtype == DLO_ENG_DCWRASTER_MONO ||
			 pdtfwrk->engtype == DLO_ENG_DCWRASTER_GRAY16 ||
			 pdtfwrk->engtype == DLO_ENG_DCWRASTER_GRAY256){
			
		maxw = pdtfwrk->style.xsize;
		maxh = pdtfwrk->style.ysize;
		if( pdtfwrk->style.italic>0){
			maxw += pdtfwrk->style.italic;
		}
		switch(pdtfwrk->style.f_edge){
		case DT_STYLE_OUTLINE:
		case DT_STYLE_BOLD:
			maxw += 2 * pdtfwrk->style.w_edge;
			maxh += 2 * pdtfwrk->style.w_edge;
			break;
		case DT_STYLE_BOLD_RIGHT:
			maxw += pdtfwrk->style.w_edge;
			break;
		case DT_STYLE_BOLD_DOWN:
			maxh += pdtfwrk->style.w_edge;
			break;
		case DT_STYLE_BOLD_RIGHT_DOWN:
			maxw += pdtfwrk->style.w_edge;
			maxh += pdtfwrk->style.w_edge;
			break;
		case DT_STYLE_NORMAL:
		default:
			/* Do Nothing. */ 
			break;
		}

		switch(pdtfwrk->style.grade){
		case DT_GRAY_MONO:
			if(((maxw+7)>>3)*maxh > ((pDT_FontMgr_wrk)pdtfwrk->font->fontmgr)->tmpbufsize){
				return DT_TEMP_BUFFER_ERR;
			}
			break;
		case DT_GRAY_16:
		case DT_GRAY_256:
		default:
			if(maxw*maxh > ((pDT_FontMgr_wrk)pdtfwrk->font->fontmgr)->tmpbufsize){
				return DT_TEMP_BUFFER_ERR;
			}
		}
	 }else if(pdtfwrk->engtype == DLO_ENG_DIFRASTER_BIT ||
			  pdtfwrk->engtype == DLO_ENG_DIFRASTER_BYTE){
		 /* No need to check */
	 }

	if(!myownGBMP){	/* use the rtdata in DigiTypeAPI for GBMP. */
//		DT_memset(pdtfwrk->rtdata,0,pdtfwrk->rtdatasz);
		DT_memset(pdtfwrk->rtdata,0,(*laybuf)->bufsize);	// 20101111_for_Performance
		(*laybuf)->bmpbuf = (DT8_uchar*) pdtfwrk->rtdata;
		buf->bmpbuf	= (DT8_char*) (*laybuf)->bmpbuf;
		buf->ltpos.x= 0;
		buf->ltpos.y= 0;
	}else{			/* caller allocated memory for GBMP. */
		if(	lt.x<0 || lt.y<0 || xbytesOfmyGBMP<=0 || hOfmyGBMP<=0 )	
			return DT_NOT_ENOUGH_BUFFER;
		if( xbytesOfmyGBMP*hOfmyGBMP<(*laybuf)->bufsize ||			// 2012-02-17: Let it be drawn incompletely!
			(lt.y+(*laybuf)->bmpheight)>hOfmyGBMP){
				bCut = 1;
			}

		buf->bmpbuf	= (DT8_char*) myownGBMP;
		buf->xbytes = (xbytesOfmyGBMP<=0)?(*laybuf)->xbytes:xbytesOfmyGBMP;
		buf->bmpheight = hOfmyGBMP;	// Notice: Is this required? or should let it bmpheight as originally.
		buf->ltpos.x= lt.x;
		buf->ltpos.y= lt.y;
	}
	ret = DLO_ShapeString(pdtfwrk->hShaper,lay,buf,DLO_DATA_RENDER);
	rtval = convReturnValue(ret);

	if(ret>=0 && pdtfwrk->style.w_underline>0)	// Jacky_20100727_underline
		drawBMPUnderline(pdtfwrk, buf);

	if(ret>=0 && pdtfwrk->style.w_strike>0)		// Jacky_20100727_underline
		drawBMPStrike(pdtfwrk, buf);

	if(bCut && rtval >= DT_SUCCESS)
		rtval |= DT_WARNING_BMP_CUTTED;

	return rtval;
	
	
dt_release:
	pdtfwrk->laybuf->gcnt	  = 0;
//	if(pdtfwrk->laybuf->glyphs)
//		DT_memset(pdtfwrk->laybuf->glyphs,0,DT_MAX_GLYPHS_PER_STR*sizeof(DT16_ushort));	

//	if(pdtfwrk->laybuf->carets)
//		DT_memset(pdtfwrk->laybuf->carets,0,DT_MAX_GLYPHS_PER_STR*sizeof(DT_PosInfo));

	pdtfwrk->laybuf->writedir = 0;

	pdtfwrk->laybuf->bitcount = 0;
	pdtfwrk->laybuf->bmpwidth = 0;
	pdtfwrk->laybuf->bmpheight= 0;
	pdtfwrk->laybuf->xbytes   = 0;
//	if(pdtfwrk->laybuf->bmpbuf && !myownGBMP)
//		DT_memset(pdtfwrk->laybuf->bmpbuf,0,pdtfwrk->laybuf->bufsize);
	pdtfwrk->laybuf->bmpbuf   = NULL;
	pdtfwrk->laybuf->bufsize  = 0;

	buf	  = (DLO_LayBuf*)pdtfwrk->dlolaybuf;
	if(myownGBMP){
		buf->bmpbuf = NULL;		/* avoid DLO_DeShapeString() to clear the GBMP. */
	}else{
		if(1==gDT_Dont_Alloc_BmpBuf_When_CreateFont){
			if(pdtfwrk->rtdata){
				DT_free(pdtfwrk->rtdata);
			}
			pdtfwrk->rtdata = NULL;
			pdtfwrk->rtdatasz = 0;
			buf->bmpbuf = NULL;
		}
	}
	DLO_DeShapeString(pdtfwrk->hShaper,buf);
	/* Set the laybuf to NULL. No more operations will be allowed. */
	*laybuf = NULL;
	return DT_SUCCESS;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------*/
/* Return the outline data of the string. Only DT_OUTLINE_MODE is valid for this function.					*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
extern DT_size_t DT_query_memory_remained();
DT32_int DT_RasterOUL(DT_Handle hnd, 
			  DT16_ushort* ucs_str,		/* the string to be drawn					*/
			  DT32_int	ucs_cnt,		/* count of ucs_str							*/
			  DT32_int	flag,			/* DT_GET_INFO | DT_DRAW, DT_RELEASE		*/
			  pDT_OulBuf *oulbuf		/* outline info when return.				*/
			  )
{
	DT32_int		ret, rtval, tmpsz;
	pDT_Fontwrk		pdtfwrk = (pDT_Fontwrk) hnd;
	DLO_LayAttr		*lay;
	DLO_LayBuf		*buf;
// 	DT8_char		*ptr=NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	if(pdtfwrk->engtype!=DLO_ENG_DCWOPENVG){
		return DT_CREATEFONT_MODE_ERR;
	}

	/* force to release the buffer if the flag combined with DT_RELEASE */
	if(flag&DT_RELEASE){
		goto dt_release;
	}

	/* get info */
	if(flag&DT_GET_INFO){
		goto dt_get_info;
	}

	if(flag&DT_DRAW){
		if(!(*oulbuf))
			goto dt_get_info;
		else
			goto dt_draw;
	}

dt_get_info:

	if(ucs_cnt<=0 || !ucs_str || ucs_cnt>DT_MAX_CODES_PER_STR)
		return DT_UCS_ERR;

	/* Prepare the layattr data */
//	DT_memset(pdtfwrk->dlolayattr,0,pdtfwrk->dlolayattrsz);
	lay = (DLO_LayAttr*)pdtfwrk->dlolayattr;
	lay->mainScript	= DLO_SCRIPT_DFLT;
	lay->mainLang	= DLO_LANG_DFLT;
	lay->ucs_cnt	= ucs_cnt;
	lay->ucs_str	= ucs_str;
	lay->writedir	= pdtfwrk->style.writedir;

	/* Prepare the buffer to receive info from DcwShaper. */
//	DT_memset(pdtfwrk->dlolaybuf,0,pdtfwrk->dlolaybufsz);
	buf	  = (DLO_LayBuf*)pdtfwrk->dlolaybuf;

	ret = DLO_ShapeString(pdtfwrk->hShaper,lay,buf,DLO_DATA_PREPARE_POS);
	rtval = convReturnValue(ret);

	if(rtval<DT_SUCCESS)
		return rtval;

	/* Prepare and clear the buffer for laybuf to return. */
//	DT_memset(pdtfwrk->rtbuffer,0,pdtfwrk->rtbuffersz);
	pdtfwrk->oulbuf = (DT_OulBuf *)pdtfwrk->rtbuffer;
	ret = makeRToulbuf(pdtfwrk);
	*oulbuf = pdtfwrk->oulbuf;

	if(flag&DT_DRAW){
		goto dt_draw;
	}

	return /*DT_SUCCESS*/rtval;

dt_draw:
	/* return as an error if oulbuf is empty. */
	if(!(*oulbuf))
		return DT_LAYBUF_ERR;

	/* check glyphs count to avoid index over it (maybe modified outside by user). */
	if((*oulbuf)->gcnt>DT_MAX_GLYPHS_PER_STR)
		(*oulbuf)->gcnt = DT_MAX_GLYPHS_PER_STR;

	if(((pDT_FontMgr_wrk)pdtfwrk->font->fontmgr)->tmpbufsize < DLO_MAX_OUL_SIZE_PER_GLYPH){
		return DT_TEMP_BUFFER_ERR;
	}

	/* set the pointer to the buffer prepared in working memory, DT_Fontwrk */
	lay = (DLO_LayAttr*)pdtfwrk->dlolayattr;
	buf	  = (DLO_LayBuf*)pdtfwrk->dlolaybuf;

//	DT_memset(pdtfwrk->rtdata,0,pdtfwrk->rtdatasz);
//	DT_memset(pdtfwrk->rtdata,0,buf->bufsize);	// 20101111_for_Performance
	if(pdtfwrk->rtdatasz < buf->glyf_cnt*DLO_MAX_OUL_SIZE_PER_GLYPH){
		// It should not get into here when gDT_Dont_Alloc_BmpBuf_When_CreateFont==0!
		if(0==gDT_Dont_Alloc_BmpBuf_When_CreateFont){
			return DT_NOT_ENOUGH_BUFFER;
		}

		tmpsz = pdtfwrk->rtdatasz;
		if(pdtfwrk->rtdata)
			DT_free(pdtfwrk->rtdata);
		pdtfwrk->rtdatasz = DT_ALLOC_SIZE(buf->glyf_cnt*DLO_MAX_OUL_SIZE_PER_GLYPH);
		pdtfwrk->rtdata	  = DT_malloc(pdtfwrk->rtdatasz);
		if(!pdtfwrk->rtdata){
//			// Try to allocate a smaller size for rtdata. Maybe it will render normally.
//			// Note_By_Jacky_20101213: Maybe we can use DT_malloc_remained() to use all the memory left.
//			pdtfwrk->rtdatasz = DT_ALLOC_SIZE(buf->glyf_cnt*DLO_MAX_OUL_SIZE_PER_GLYPH/3);
//			if(tmpsz > pdtfwrk->rtdatasz){	// Ensure new memory won't be smaller than original.
//				pdtfwrk->rtdatasz = DT_ALLOC_SIZE(tmpsz);
//			}
//			pdtfwrk->rtdata	  = DT_malloc(pdtfwrk->rtdatasz);
//			if(!pdtfwrk->rtdata){
//				pdtfwrk->rtdatasz = 0;
//				pdtfwrk->rtdata	  = NULL;
//				return DT_NOT_ENOUGH_BUFFER;
//			}else{
//				if(pdtfwrk->rtdatasz > pdtfwrk->rtdataszused){
//					pdtfwrk->rtdataszused = pdtfwrk->rtdatasz;
//				}
//			}

			// Try to allocate all the memory remained.
			if(1==gDT_Set_Fix_Memory_Size){
				pdtfwrk->rtdatasz = (DT32_int) DT_query_memory_remained();	// Because it's remained, no DT_ALLOC_SIZE().
				if(tmpsz > pdtfwrk->rtdatasz){
					pdtfwrk->rtdatasz = tmpsz;		// Ensure new memory won't be smaller than origin.
				}
				pdtfwrk->rtdata = DT_malloc(pdtfwrk->rtdatasz);
				if(!pdtfwrk->rtdata){
					// Should not get into here!
					pdtfwrk->rtdatasz = 0;
					pdtfwrk->rtdata	  = NULL;
					return DT_NOT_ENOUGH_BUFFER;
				}else{
					if(pdtfwrk->rtdatasz > pdtfwrk->rtdataszused){
						pdtfwrk->rtdataszused = pdtfwrk->rtdatasz;
					}
				}
			}else{
				pdtfwrk->rtdatasz = 0;
				pdtfwrk->rtdata	  = NULL;
				return DT_NOT_ENOUGH_BUFFER;
			}
		}else{
			if(pdtfwrk->rtdatasz > pdtfwrk->rtdataszused){
				pdtfwrk->rtdataszused = pdtfwrk->rtdatasz;
			}
		}
	}
	buf->olDatabuf	= (DT8_char*) pdtfwrk->rtdata;
	buf->olDatabufSize = pdtfwrk->rtdatasz;	/* tell DcwShaper how many olDatabuf is allocated. */
	ret = DLO_ShapeString(pdtfwrk->hShaper,lay,buf,DLO_DATA_RENDER);
	rtval = convReturnValue(ret);

	/* fill the returned outline info to oulbuf */
	(*oulbuf)->olbuf = buf->olDatabuf;
	(*oulbuf)->olsizes = buf->olSizebuf;
	(*oulbuf)->olbufsize=buf->olDatabufSize;
	/* reset the pointer of rtdata, it might be realloc in DcwShaper. */
	if(buf->olDatabufSize > pdtfwrk->rtdatasz){
		pdtfwrk->rtdata = buf->olDatabuf;
		pdtfwrk->rtdatasz=buf->olDatabufSize;
	}
	return rtval;
	
dt_release:
	pdtfwrk->oulbuf->gcnt	  = 0;
//	if(pdtfwrk->oulbuf->glyphs)
//		DT_memset(pdtfwrk->oulbuf->glyphs,0,DT_MAX_GLYPHS_PER_STR*sizeof(DT16_ushort));	
//	if(pdtfwrk->oulbuf->carets)
//		DT_memset(pdtfwrk->oulbuf->carets,0,DT_MAX_GLYPHS_PER_STR*sizeof(DT_OulPos));
	pdtfwrk->oulbuf->writedir = 0;

	pdtfwrk->oulbuf->eswidth  = 0;
	pdtfwrk->oulbuf->esheight = 0;

//	if(pdtfwrk->oulbuf->olbuf)
//		DT_memset(pdtfwrk->oulbuf->olbuf,0,pdtfwrk->oulbuf->olbufsize);
	pdtfwrk->oulbuf->olbuf   = NULL;
	pdtfwrk->oulbuf->olbufsize = 0;

	buf	  = (DLO_LayBuf*)pdtfwrk->dlolaybuf;
	if(1==gDT_Dont_Alloc_BmpBuf_When_CreateFont){
		if(pdtfwrk->rtdata){
			DT_free(pdtfwrk->rtdata);
		}
		pdtfwrk->rtdata = NULL;
		pdtfwrk->rtdatasz = 0;
	}
	DLO_DeShapeString(pdtfwrk->hShaper,buf);
	/* Set the laybuf to NULL. No more operations will be allowed. */
	*oulbuf = NULL;
	return DT_SUCCESS;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT_Handle DT_CreateFontEx(DT_Font *font, DT32_int mode, DT_Font *bkfont, DT_Font *iconfont)
{
	pDT_Fontwrk pdtfwrk = NULL;
	DT32_int	wrksz = sizeof(DT_Fontwrk);
	DT32_int	ret, rtbufsz=0, rtdatasz=0, dlolayattrsz=0, dlolaybufsz=0;
	DLO_EngineType eng;
	DLO_Handle	hShaper=NULL;
	DT32_int	bfontload=0, bbkfontload=0, biconfontload=0;
	pLayWrk		pwrk;

DBG_MSG_SHOW_FUNC_NAME();

	if(font){
		if(!font->fontmgr || font->type==DTIconFont_DIF){
			return NULL;
		}
		font = FMgr_getDTFontByfid(font->fontmgr,font->fid);	/* use the DT_Font stored in FontManager */
	}else{
		return NULL;
	}

	if(iconfont){
		if(font->fontmgr!=iconfont->fontmgr || iconfont->type!=DTIconFont_DIF || mode==DT_OUTLINE_MODE){
			goto Error_Release;
		}
		iconfont = FMgr_getDTFontByfid(iconfont->fontmgr,iconfont->fid);/* use the DT_Font stored in FontManager */
	}

	if(bkfont){
		if(font->fontmgr!=bkfont->fontmgr || font->type!=bkfont->type || bkfont->type!=DTDigiType_FDL){
			goto Error_Release;
		}
		bkfont = FMgr_getDTFontByfid(bkfont->fontmgr,bkfont->fid);/* use the DT_Font stored in FontManager */
	}

	eng = ChooseEngine(font->type,mode);
	if(eng==DLO_ENG_END)
		return NULL;

	/* Allocate the required memory */
	dlolayattrsz= sizeof(DLO_LayAttr);		wrksz += dlolayattrsz;
	dlolaybufsz = sizeof(DLO_LayBuf);		wrksz += dlolaybufsz;
	rtbufsz = Estimate_rtbuffer_Size(eng);	wrksz += rtbufsz;

	/* main working memory of DT_Fontwrk */
	pdtfwrk = (pDT_Fontwrk) DT_malloc(DT_ALLOC_SIZE(wrksz));
	if(!pdtfwrk)
		return NULL;

	DT_memset(pdtfwrk,0,DT_ALLOC_SIZE(wrksz));	//DT_memset(pdtfwrk,0,wrksz); 
												// some OVG handle, ex: mytmppath_str, mytmppath_glyph... will be set as 0 (VG_INVALID_HANDLE)	
	pdtfwrk->charmap = NULL;		// If not set these, it will crash when DT_ENABLE_MEMORY_H enabled.
	pdtfwrk->charmap_num = 0;
	pdtfwrk->altfontcnt = 0;
	pdtfwrk->iconfontcnt = 0;

	/* estimate the required data size for return by engine. */
//	rtdatasz= Estimate_rtdata_Size(eng);
//	if(rtdatasz>0)
//		pdtfwrk->rtdata	  = (DT8_char*) DT_malloc(DT_ALLOC_SIZE(rtdatasz));
//	
//	if(!pdtfwrk->rtdata){
//		DT_free(pdtfwrk);
//		return NULL;
//	}
//
//	pdtfwrk->rtdatasz = rtdatasz;
	//DT_memset(pdtfwrk->rtdata,0,rtdatasz);	// 20101111_for_Performance

	/* Load font file content, memory is allocated in DT_loadfilecontent(). */
	//ret = DT_loadfilecontent(font->fontname, font->nlen, &font->fontdata, &font->nfsize);
	if(font->nlen>0 && font->fontname[0]){	/* load from file or fontname.	*/
	  ret = DT_LoadFontData(font,-1);
	  if(ret!=1){
		goto Error_Release;
	  }else{
		bfontload = 1;
	  }
	}else{	/* load from font data. */
	  font->refcnt++;	
	}
	if(iconfont){
	  if(iconfont->nlen>0 && iconfont->fontname[0]){
		ret = DT_LoadFontData(iconfont,-1);
		if(ret!=1){
			goto Error_Release;
		}else{
			biconfontload = 1;
			pdtfwrk->iconfont = iconfont;
			pdtfwrk->iconfontcnt = 1;
		}
	  }else{
		iconfont->refcnt++;
		pdtfwrk->iconfont = iconfont;
		pdtfwrk->iconfontcnt = 1;
	  }
	}

	if(bkfont){
	  if(bkfont->nlen>0 && bkfont->fontname[0]){
		ret = DT_LoadFontData(bkfont,-1);
		if(ret!=1){
			goto Error_Release;
		}else{
			bbkfontload = 1;
			pdtfwrk->altfont = bkfont;
			pdtfwrk->altfontcnt = 1;
		}
	  }else{
		bkfont->refcnt++;
		pdtfwrk->altfont = bkfont;
		pdtfwrk->altfontcnt = 1;
	  }
	}

	/* Set the buffer for results out. */
	pdtfwrk->fontmgr = font->fontmgr;
	pdtfwrk->totalmemsz = DT_ALLOC_SIZE(wrksz);		//wrksz;
	pdtfwrk->dlolayattr=(DT8_char*)pdtfwrk + sizeof(DT_Fontwrk);
	pdtfwrk->dlolaybuf= (DT8_char*)pdtfwrk->dlolayattr + dlolayattrsz;

	pdtfwrk->rtbuffer = (DT8_char*)pdtfwrk->dlolaybuf + dlolaybufsz;
	
	pdtfwrk->dlolayattrsz=dlolayattrsz;
	pdtfwrk->dlolaybufsz= dlolaybufsz;
	pdtfwrk->rtbuffersz = rtbufsz;

	if(DLO_ENG_DCWOPENVG==eng){
		pdtfwrk->oulbuf = (DT_OulBuf*) pdtfwrk->rtbuffer;
	}else{
		pdtfwrk->laybuf = (DT_LayBuf*) pdtfwrk->rtbuffer;
	}

	pdtfwrk->font = font;
	pdtfwrk->engtype = eng;		/* keep engine type */

	/* Initial DcwShaper as the size hint and set default font style. */
	pdtfwrk->hShaper = NULL;
	ret = DLO_InitShaper((DT8_char*)dlodata,pdtfwrk->font,eng,gDT_FONTSIZE_FOR_MALLOC,&hShaper,
						 pdtfwrk->altfont,pdtfwrk->altfontcnt,pdtfwrk->iconfont,pdtfwrk->iconfontcnt);
	if(ret<0 || !hShaper){
		goto Error_Release;
	}
	((pLayWrk)hShaper)->pdtfwrk = pdtfwrk;
	pdtfwrk->hShaper = hShaper;

	/* estimate the required data size for return by engine. */	/* 20101213: Move here to ensure rtdata is the last allocated. */
	rtdatasz= Estimate_rtdata_Size(eng,0);
	pdtfwrk->rtdatasz = rtdatasz>0 ? DT_ALLOC_SIZE(rtdatasz) : 0;
	if(pdtfwrk->rtdatasz>0)
		pdtfwrk->rtdata	  = (DT8_char*) DT_malloc(pdtfwrk->rtdatasz);
	
	if(!pdtfwrk->rtdata){
		pdtfwrk->rtdatasz = 0;
		if(gDT_Dont_Alloc_BmpBuf_When_CreateFont==0)
			goto Error_Release;
	}else{
		pdtfwrk->rtdataszused = pdtfwrk->rtdatasz;
	}
	//DT_memset(pdtfwrk->rtdata,0,rtdatasz);	// Do it before going to use it. Only the required will be set.

	pdtfwrk->rtdatasuggest = DT_ALLOC_SIZE(Estimate_rtdata_Size(eng,1));


	/* Set Default font style	*/
	setDefaultStyle(pdtfwrk);

	/* Set Cache */
	pdtfwrk->usedcachearr = NULL;
	if( ((DT_FontMgr_wrk*)pdtfwrk->fontmgr)->cachearr.CacheSet && 
		((DT_FontMgr_wrk*)pdtfwrk->fontmgr)->cachearr.Init_FontCache){
		pdtfwrk->usedcachearr = (DT_CacheArray*) &((DT_FontMgr_wrk*)pdtfwrk->fontmgr)->cachearr;
	}

	/* Set Last return code. */
	if(DLO_ENG_DCWOPENVG==eng)
		pdtfwrk->lastreturn = DT_DEFAULT_LASTRETURN;	// laststrlen will be 0 here.
	return pdtfwrk;

Error_Release:
	if(font->nlen>0 && font->fontname[0]){
	  if(bfontload){
		DT_unLoadFontData(font,-1);
		//font->fontdata = NULL;	/* refcnt is used, can't set it as NULL now.*/
		//font->nfsize = 0;			/* refcnt is used, can't set it as 0 now.	*/
	  }
	}else{
	  font->refcnt--;
	}
	if(bkfont){
	  if(bkfont->nlen>0 && bkfont->fontname[0]){
		if(bbkfontload){
		  if(bkfont->fontdata){
			DT_unLoadFontData(bkfont,-1);
		  }
		}
	  }else{
		bkfont->refcnt--;
	  }
	}
	if(iconfont){
	  if(iconfont->nlen>0 && iconfont->fontname[0]){
		if(biconfontload){
		  if(iconfont->fontdata){
			DT_unLoadFontData(iconfont,-1);
		  }
		}
	  }else{
		iconfont->refcnt--;
	  }
	}

	if(pdtfwrk && pdtfwrk->hShaper){
		pwrk = (pLayWrk)pdtfwrk->hShaper;
		if(pwrk->engWkMem){
			DT_free(pwrk->engWkMem);
			pwrk->engWkMem = NULL;
			pwrk->engWkMemsz = 0;
		}
		DT_free(pwrk);
		pdtfwrk->hShaper = NULL;
	}

	if(pdtfwrk && pdtfwrk->rtdata){
		DT_free(pdtfwrk->rtdata);
		pdtfwrk->rtdata = NULL;
		pdtfwrk->rtdatasz = 0;
	}

	if(pdtfwrk){
		DT_free(pdtfwrk);
		pdtfwrk = NULL;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT_Handle DT_CreateFont(DT_Font *font, DT32_int mode)
{
DBG_MSG_SHOW_FUNC_NAME();

	return DT_CreateFontEx(font,mode,NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT_Handle DT_CreateFontFromMem(DT_FontMgr mgr, DT_FontData *font, DT32_int mode, DT_FontData *bkfont, DT_FontData *iconfont)
{
	DT32_int fontid=-1, bkfontid=-1, iconfontid=-1;
	DT_Font  *mainf=NULL;
	DT_Font  *bkf=NULL;
	DT_Font  *iconf=NULL;
	DT_FontMgr_wrk* h_gFontManager = (DT_FontMgr_wrk*)mgr;
	DT_Handle  hFont=NULL;

DBG_MSG_SHOW_FUNC_NAME();
	
	if(!h_gFontManager){
		return NULL;
	}

	// Check fonts' identifier & add font to FontManager
	if(!font){
		return NULL;
	}else{
		fontid = FMgr_addDTFontData(h_gFontManager, font);
		if(fontid<0){
			return NULL;
		}
	}
	if(bkfont){
		bkfontid = FMgr_addDTFontData(h_gFontManager, bkfont);
		if(bkfontid<0){
			return NULL;
		}
	}
	if(iconfont){
		iconfontid = FMgr_addDTFontData(h_gFontManager, iconfont);
		if(iconfontid<0){
			return NULL;
		}
	}

	mainf = FMgr_getDTFontByfid(h_gFontManager, fontid);
	if(mainf->fontmgr != h_gFontManager){
		return NULL;
	}
	if(bkfont && bkfontid>=0){
		bkf = FMgr_getDTFontByfid(h_gFontManager, bkfontid);
		if(bkf->fontmgr != h_gFontManager){
			return NULL;
		}
	}
	if(iconfont && iconfontid>=0){
		iconf = FMgr_getDTFontByfid(h_gFontManager, iconfontid);
		if(iconf->fontmgr != h_gFontManager){
			return NULL;
		}
	}

	hFont = DT_CreateFontEx(mainf, mode, bkf, iconf);

	return hFont;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT_Handle DT_CreateFontFromFile(DT_FontMgr mgr, DT_FontFile *font, DT32_int mode, DT_FontFile *bkfont, DT_FontFile *iconfont)
{
	DT32_int fontid=-1, bkfontid=-1, iconfontid=-1;
	DT_Font  *mainf=NULL;
	DT_Font  *bkf=NULL;
	DT_Font  *iconf=NULL;
	DT_FontMgr_wrk* h_gFontManager = (DT_FontMgr_wrk*)mgr;
	DT_Handle  hFont=NULL;

DBG_MSG_SHOW_FUNC_NAME();
	
	if(!h_gFontManager){
		return NULL;
	}

	// Check fonts' identifier & add font to FontManager
	if(!font){
		return NULL;
	}else{
		fontid = FMgr_addDTFontFile(h_gFontManager, font);
		if(fontid<0){
			return NULL;
		}
	}
	if(bkfont){
		bkfontid = FMgr_addDTFontFile(h_gFontManager, bkfont);
		if(bkfontid<0){
			return NULL;
		}
	}
	if(iconfont){
		iconfontid = FMgr_addDTFontFile(h_gFontManager, iconfont);
		if(iconfontid<0){
			return NULL;
		}
	}

	mainf = FMgr_getDTFontByfid(h_gFontManager, fontid);
	if(mainf->fontmgr != h_gFontManager){
		return NULL;
	}
	if(bkfont && bkfontid>=0){
		bkf = FMgr_getDTFontByfid(h_gFontManager, bkfontid);
		if(bkf->fontmgr != h_gFontManager){
			return NULL;
		}
	}
	if(iconfont && iconfontid>=0){
		iconf = FMgr_getDTFontByfid(h_gFontManager, iconfontid);
		if(iconf->fontmgr != h_gFontManager){
			return NULL;
		}
	}

	hFont = DT_CreateFontEx(mainf, mode, bkf, iconf);

	return hFont;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT32_int DT_DestroyFont(DT_Handle hnd)
{
	DT32_int ret;
	pDT_Fontwrk pdtfwrk = (pDT_Fontwrk) hnd;
#if (1==DT_OPENVG_ENABLED) 
	DT32_int i;
	CacheUnit *unit;
#endif

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	/* Release Charmap */
	if(pdtfwrk->charmap){
		DT_free(pdtfwrk->charmap);
		pdtfwrk->charmap = NULL;
		pdtfwrk->charmap_num = 0;
	}

	/* unInitShaper */
	ret = DLO_unInitShaper(pdtfwrk->hShaper);
	if(ret<0)
		return DT_ERROR_DESTROYFONT;

	/* Release the file content */
	if(pdtfwrk->font->nlen>0 && pdtfwrk->font->fontname[0] && pdtfwrk->font->fontdata!=NULL){
		DT_unLoadFontData(pdtfwrk->font,-1);
		//pdtfwrk->font->fontdata	= NULL;	//	RefCnt used. Can't set NULL here.
		//pdtfwrk->font->nfsize	= 0;
	}
	if(pdtfwrk->altfontcnt){
		if(pdtfwrk->altfont->nlen>0 && pdtfwrk->altfont->fontname[0] && pdtfwrk->altfont->fontdata!=NULL){
			DT_unLoadFontData(pdtfwrk->altfont,-1);
		}
		pdtfwrk->altfontcnt = 0;
	}
	if(pdtfwrk->iconfontcnt){
		if(pdtfwrk->iconfont->nlen>0 && pdtfwrk->iconfont->fontname[0] && pdtfwrk->iconfont->fontdata!=NULL){
			DT_unLoadFontData(pdtfwrk->iconfont,-1);
		}
		pdtfwrk->iconfontcnt = 0;
	}

	/* Release return data */
	if(pdtfwrk->rtdata){
		DT_free(pdtfwrk->rtdata);
		pdtfwrk->rtdata = NULL;
		pdtfwrk->rtdatasz = 0;
	}

#if (1==DT_OPENVG_ENABLED)
	if(pdtfwrk->myvgfont)
		vgDestroyFont((VGPath)pdtfwrk->myvgfont);
	if(pdtfwrk->myglyphpath)
		vgDestroyPath((VGPath)pdtfwrk->myglyphpath);
	if(pdtfwrk->mytranspath)
		vgDestroyPath((VGPath)pdtfwrk->mytranspath);
	if(pdtfwrk->mymaskpath)
		vgDestroyPath((VGPath)pdtfwrk->mymaskpath);

	if(pdtfwrk->mytmppath_str){
		vgDestroyPath((VGPath)pdtfwrk->mytmppath_str);
	}
	if(pdtfwrk->mytmppath_strEM){
		vgDestroyPath((VGPath)pdtfwrk->mytmppath_strEM);
	}	
	if(pdtfwrk->mytmppath_glyph){
		vgDestroyPath((VGPath)pdtfwrk->mytmppath_glyph);
	}
	if(pdtfwrk->mytmppath_glyph00){
		vgDestroyPath((VGPath)pdtfwrk->mytmppath_glyph00);
	}
	unit = NULL;
	if(pdtfwrk->usedcacheL1){
		// no OpenVG handle created, so it's not required.
		pdtfwrk->usedcacheL1 = NULL;
	}
	if(pdtfwrk->usedcacheL2){
		for(i=0; i<pdtfwrk->usedcacheL2->CacheNum; i++){
			unit = GetCacheUnit(pdtfwrk->usedcacheL2, i);
			vgDestroyPath((VGPath)unit->extra.infoL2.hVGPath);
		}
		pdtfwrk->usedcacheL2 = NULL;
	}
	if(pdtfwrk->usedcacheL3){
		for(i=0; i<pdtfwrk->usedcacheL3->CacheNum; i++){
			unit = GetCacheUnit(pdtfwrk->usedcacheL3, i);
			vgDestroyPath((VGPath)unit->extra.infoL3.hVGPath);
		}
		pdtfwrk->usedcacheL3 = NULL;	
	}
#endif

	/* Release DT_Fontwrk working memory */
	if(pdtfwrk){
		DT_free(pdtfwrk);
		pdtfwrk = NULL;
	}

	return DT_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* BDF font, DLO_ENG_BDFRASTER: only support DT_FSTYLE_WRITEDIR.								*/
/* FDL font with DcwRaster (DT_RasterGBMP(), DT_RasterBitBlt()): all styles should be supported,
	but some aren't implement: DT_FSTYLE_VERT, DT_FSTYLE_DEGREE. DT_FSTYLE_VG_COORD is useless.	*/
/* FDL font with DcwOpenVG (DT_RasterOVG()), DLO_ENG_DCWOPENVG: some styles aren't implement,	
	DT_FSTYLE_VERT, DT_FSTYLE_ITALICAMOUNT, DT_FSTYLE_E_UNDERLINE, DT_FSTYLE_GRAD, DT_FSTYLE_DEGREE.	*/
DT32_int DT_SetFontStyle(DT_Handle hnd, DT_FontStyle_Option option, DT32_int value)
{
	pDT_Fontwrk		pdtfwrk = (pDT_Fontwrk) hnd;
	pDT_StyleAttr	sattr;
	DT32_int		bOUL=0, bGrayValid=0;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	sattr = &pdtfwrk->style;

	/* BDF font doesn't support font style */
	if(pdtfwrk->engtype==DLO_ENG_BDFRASTER){
		if( option!=DT_FSTYLE_WRITEDIR && 
			option!=DT_FSTYLE_XBYTE_ALIGN && 
			option!=DT_FSTYLE_SPACING && 
			option!=DT_FSTYLE_BIDI_RULE)
			return DT_STYLE_NOT_SUPPORT;
	}

	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG)
		bOUL = 1;

	switch(option){
	case DT_FSTYLE_VERT:		/* Now, horizontal only.	*//* Enabled after v2.5.29 */
		if(value /*&& !bOUL*/)
			value = 1;	//return DT_STYLE_NOT_SUPPORT;	// Jacky_20110318: Vertical output. Ensuring it's 0 or 1.
		sattr->vert = value;
		
	#ifdef DT_VERT_BY_OVG
		if(!bOUL)		// vert will be done in DT_RasterOVGPath(), don't set it to DcwShaperVG.
	#endif
			DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_VERT,value);
		break;
	case DT_FSTYLE_SIZEX:		/* desired x size			*/
		if(value<0 || (value>gSet_DT_FONT_SIZE_LIMIT && !bOUL))
			return DT_STYLE_NOT_SUPPORT;
//		if( (value+DT_FONT_MAXITALIC)*sattr->ysize > ((pDT_FontMgr_wrk)pdtfwrk->font->fontmgr)->tmpbufsize){
//			return DT_TEMP_BUFFER_ERR;	/* Estimate if temp buffer enough */
//		}	// Marked_By_Jacky_20101122: Check it later.
		sattr->xsize = value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_SIZEX,value);
		if(!bOUL){
			/* Bold was affected by sizex */
		  if(sattr->is_bold)	//Notes_Jacky_20101201: It might needs to be enabled to not reset the value.
			setBoldStyle(pdtfwrk, sattr->is_bold);
		}
		break;
	case DT_FSTYLE_SIZEY:		/* desired y size			*/
		if(value<0 || (value>gSet_DT_FONT_SIZE_LIMIT && !bOUL))
			return DT_STYLE_NOT_SUPPORT;
//		if( (sattr->xsize+DT_FONT_MAXITALIC)*value > ((pDT_FontMgr_wrk)pdtfwrk->font->fontmgr)->tmpbufsize){
//			return DT_TEMP_BUFFER_ERR;
//		}	// Marked_By_Jacky_20101122: Check it later.

		sattr->ysize = value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_SIZEY,value);
		if(!bOUL){
			/* Bold, Italic, Underline, Strike was affected by sizey */
		  if(sattr->is_bold)	//Notes_Jacky_20101201: It might needs to be enabled to not reset the value.
			setBoldStyle(pdtfwrk, sattr->is_bold);
		  if(sattr->is_italic)
			setItalicStyle(pdtfwrk, sattr->is_italic);
		  if(sattr->is_underline)
			setUnderlineStyle(pdtfwrk, sattr->is_underline);
		  if(sattr->is_strike)
			setStrikeStyle(pdtfwrk, sattr->is_strike);
		}
		break;
	case DT_FSTYLE_IS_BOLD:		/* Bold font(1) or not(0)	*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		sattr->is_bold = value?1:0;
		setBoldStyle(pdtfwrk, sattr->is_bold);
		break;
	case DT_FSTYLE_IS_ITALIC:	/* Italic font(1) or not(0)	*/
		// 20110810: Jacky marked this to enable it.
		//if(bOUL)
		//	return DT_STYLE_NOT_SUPPORT;
		sattr->is_italic = value?1:0;
		setItalicStyle(pdtfwrk, sattr->is_italic);
		break;
	case DT_FSTYLE_IS_UNDERLINE:/* Underline(1) or not(0)	*/
		// 20110810: Jacky marked this to enable it.
		//if(bOUL)
		//	return DT_STYLE_NOT_SUPPORT;
		sattr->is_underline = value?1:0;
		setUnderlineStyle(pdtfwrk, sattr->is_underline);
		break;
	case DT_FSTYLE_IS_STRIKE:	/* Strike(1) or not(0)		*/
		// 20110810: Jacky marked this to enable it.
		//if(bOUL)
		//	return DT_STYLE_NOT_SUPPORT;
		sattr->is_strike = value?1:0;
		setStrikeStyle(pdtfwrk, sattr->is_strike);
		break;
	case DT_FSTYLE_F_EDGE:		/* font edge, such as bold, outline...*/
		if(value<0 || value>DT_STYLE_MAX_EDGE_FLAG)
			return DT_STYLE_NOT_SUPPORT;
		if(bOUL){
			if( value==DT_STYLE_BOLD_RIGHT || 
				value==DT_STYLE_BOLD_DOWN || 
				value==DT_STYLE_BOLD_RIGHT_DOWN){
				return DT_STYLE_NOT_SUPPORT;
			}
		}
		sattr->f_edge = value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_F_EDGE,value);
		break;
	case DT_FSTYLE_W_EDGE:		/* the width of the edge	*/
		if(value<0 || value>DT_STYLE_MAX_EDGE_WIDTH)
			return DT_STYLE_NOT_SUPPORT;
		sattr->w_edge = value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_W_EDGE,value);
		// sync!
		sattr->w_edge266 = (DT_f26dot6)DTFixToF266(sattr->w_edge,0);
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_W_EDGE_26_6,sattr->w_edge266);
		break;
	case DT_FSTYLE_W_EDGE_26_6:		/* the width of the edge	*/
		if(DTF266ToInt(value)<0 || DTF266ToInt(value)>DT_STYLE_MAX_EDGE_WIDTH)
			return DT_STYLE_NOT_SUPPORT;
		sattr->w_edge266 = (DT_f26dot6)value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_W_EDGE_26_6,value);
		// overwrites! following must be set.
		sattr->w_edge = (DT32_int)DTF266ToInt(value);	
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_W_EDGE,sattr->w_edge);
		break;
	case DT_FSTYLE_ITALICAMOUNT:/* italic amount in pixels	*/
		// 20110810: Jacky marked this to enable it.
		//if(bOUL)
		//	return DT_STYLE_NOT_SUPPORT;
		if(value<0 || (!bOUL && value>gDT_FONT_MAXITALIC) || value>sattr->xsize)
			return DT_STYLE_NOT_SUPPORT;
//		if( (sattr->xsize+value)*sattr->ysize > ((pDT_FontMgr_wrk)pdtfwrk->font->fontmgr)->tmpbufsize){
//			return DT_TEMP_BUFFER_ERR;
//		}	// Marked_By_Jacky_20101122: Check it later.

		sattr->italic = value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_ITALIC,value);
		break;
	case DT_FSTYLE_P_UNDERLINE:	/* the position of underline*/
		// Marked_by_Jacky_20110429 for some chars will be larger than ysize while DT_FORCE_SCALE_RATIO!=0
		//if(value<0 || value>=(sattr->ysize - sattr->w_underline) )
		//	return DT_STYLE_NOT_SUPPORT;
		sattr->p_underline = value;
		//DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_P_UNDERLINE,value);		// Jacky_20100727_underline
		break;
	case DT_FSTYLE_W_UNDERLINE:	/* the width of underline	*/
		if(value<0 /*|| value>=(sattr->ysize - DTAbs(sattr->p_underline))*/ )
			return DT_STYLE_NOT_SUPPORT;
		sattr->w_underline = value;
		//DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_W_UNDERLINE,value);		// Jacky_20100727_underline
		break;
	case DT_FSTYLE_E_UNDERLINE:	/* the extend of underline	*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		if(value<0 /*|| value>sattr->italic*/)
			return DT_STYLE_NOT_SUPPORT;
		sattr->e_underline = value;
		//DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_E_UNDERLINE,value);		// Jacky_20100727_underline
		break;
	case DT_FSTYLE_P_STRIKE:	/* the position of strike*/
		// Marked_by_Jacky_20110429 for some chars will be larger than ysize while DT_FORCE_SCALE_RATIO!=0
		//if(value<0 || value>=(sattr->ysize - sattr->w_strike) )
		//	return DT_STYLE_NOT_SUPPORT;
		sattr->p_strike = value;
		break;
	case DT_FSTYLE_W_STRIKE:	/* the width of strike	*/
		if(value<0 /*|| value>=(sattr->ysize - DTAbs(sattr->p_strike))*/ )
			return DT_STYLE_NOT_SUPPORT;
		sattr->w_strike = value;
		break;
	case DT_FSTYLE_E_STRIKE:	/* the extend of strike	*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		if(value<0 /*|| value>sattr->italic*/)
			return DT_STYLE_NOT_SUPPORT;
		sattr->e_strike = value;
		break;
	case DT_FSTYLE_GRAD:		/* GRAY16, GRAY256...etc.	*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		if(value<0 || value>DT_GRAY_MAX)
			return DT_STYLE_NOT_SUPPORT;
		
		if(pdtfwrk->engtype==DLO_ENG_DCWRASTER_GRAY256)	/* all grade is valid. */
			bGrayValid = 1;
		else if(pdtfwrk->engtype==DLO_ENG_DCWRASTER_GRAY16 && 
				(value==DT_GRAY_16 || value==DT_GRAY_MONO) ) /* under gray16 is valid */
			bGrayValid = 1;
		else if(pdtfwrk->engtype==DLO_ENG_DCWRASTER_MONO &&
				value==DT_GRAY_MONO )					/* only mono is valid */
			bGrayValid = 1;
		if(bGrayValid){
			sattr->grade = value;
			DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_GRAD,conv2DcwShaperGrade(value));
		}else{
			return DT_STYLE_NOT_SUPPORT;
		}
		break;
	case DT_FSTYLE_DEGREE:		/* 1/10 degree rotated, not support yet	*/
		if(value<0 || value>DT_MAX_DEGREES)
			return DT_STYLE_NOT_SUPPORT;
		sattr->degree = value;
		//DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_DEGREE,value);
		break;
	case DT_FSTYLE_WRITEDIR:	/* write direction: DT_LEFTTORIGHT or DT_RIGHTTOLEFT	*/
		if(value!=DT_LEFTTORIGHT && value!=DT_RIGHTTOLEFT && value!=DT_DECIDE_BY_STR)
			return DT_STYLE_NOT_SUPPORT;
		sattr->writedir = value;
		//Write direction will be set while calling DLO_ShapeString().
		break;
	case DT_FSTYLE_VG_COORD:	/* coordinate, DT_COORD_LEFT_TOP or DT_COORD_LEFT_BOT	*/
		if(!bOUL)
			return DT_STYLE_NOT_SUPPORT;
		if(value!=DT_COORD_LEFT_TOP && value!=DT_COORD_LEFT_BOT)
			return DT_STYLE_NOT_SUPPORT;
		sattr->oulcoord = value;
		//Coordinate will be used while DT_RasterOVG()
		break;
	case DT_FSTYLE_VG_GEN_EMPATH:
		if(!bOUL)
			return DT_STYLE_NOT_SUPPORT;
		sattr->gen_empath = value ? 1 : 0;
		break;
	case DT_FSTYLE_GRAD_VALUES:			/* an easy way to set gcolor when gray16, see DT_FSTYLE_GRAD_VALUES*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		if(value<0 || value>DT_GRADE_MAX_FLAG)
			return DT_STYLE_NOT_SUPPORT;
		sattr->grade_values = value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_GRAD_VALUES,value);	
		// Now, the values are the same between DigiTypeAPI(DT_) & DcwShaper(DLO_), set directly.
		break;
	case DT_FSTYLE_XBYTE_ALIGN:	/* horizontal bytes alignment for GBMP, default:4*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		if(value<0){
			sattr->xbytes_align = 4;	
		}else{
			sattr->xbytes_align = value;
		}
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_XBYTE_ALIGN,value);
		break;

	case DT_FSTYLE_SPACING:
		// do some check if needed.
		sattr->spacing = value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_SPACING,value);
		break;
	case DT_FSTYLE_HINTING:
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		if(value!=1 /*&& value!=2*/){
			return DT_STYLE_NOT_SUPPORT;
		}else{
			sattr->hinting = value;
		}
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_HINTING,value);
		break;
	case DT_FSTYLE_FORCE_MOVE_DOWN:
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		if(value!=-1 && (value>1000 || value<-1)){
			return DT_STYLE_NOT_SUPPORT;
		}else{
			sattr->forcedown = value;
		}
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_FORCE_MOVE_DOWN,value);
		break;
	case DT_FSTYLE_BIDI_RULE:
		if(value!=DT_BIDI_UNIRULE && value!=DT_BIDI_DCWRULE)
			return DT_STYLE_NOT_SUPPORT;
		else
			sattr->bidirule = value;
		DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_BIDI_RULE,value);
		break;
	case DT_FCACHE_CACHESET_ADD:
		if(bOUL || !value){
			return DT_STYLE_NOT_SUPPORT;
		}
		sattr->cacheset = (DT_void*)value;
		((DT_CacheSet*)sattr->cacheset)->type = DTC_TYPE_GRAYBMP;
		if(CalculateCacheMem((DT_CacheSet*)sattr->cacheset)<0){
			return DT_CACHESET_ADD_ERR;
		}
		DT_memcpy(&pdtfwrk->cacheset,sattr->cacheset,sizeof(DT_CacheSet));
		CoordinateCacheMem(NULL, pdtfwrk, &pdtfwrk->cacheset, &pdtfwrk->cachearr);
		pdtfwrk->usedcachearr = &pdtfwrk->cachearr;
		break;
#if (1==DT_OPENVG_ENABLED)
	case DT_FCACHE_OVGL1CACHESET_ADD:
		if(!bOUL || !value){
			return DT_STYLE_NOT_SUPPORT;
		}
		sattr->ovgL1cache = (DT_void*)value;
		((DT_OVGL1_CacheSet*)sattr->ovgL1cache)->type = DTC_TYPE_OVGL1;
		if(CalculateCacheMem((DT_OVGL1_CacheSet*)sattr->ovgL1cache)<0){
			return DT_CACHESET_ADD_ERR;
		}
		DT_memcpy(&pdtfwrk->cachesetL1,sattr->ovgL1cache,sizeof(DT_OVGL1_CacheSet));
		CoordinateCacheMem(NULL, pdtfwrk, &pdtfwrk->cachesetL1, &pdtfwrk->cachearrL1);
		pdtfwrk->usedcacheL1 = &pdtfwrk->cachearrL1;
		break;
	case DT_FCACHE_OVGL2CACHESET_ADD:
		if(!bOUL || !value){
			return DT_STYLE_NOT_SUPPORT;
		}
		sattr->ovgL2cache = (DT_void*)value;
		((DT_OVGL2_CacheSet*)sattr->ovgL2cache)->type = DTC_TYPE_OVGL2;
		if(CalculateCacheMem((DT_OVGL2_CacheSet*)sattr->ovgL2cache)<0){
			return DT_CACHESET_ADD_ERR;
		}
		DT_memcpy(&pdtfwrk->cachesetL2,sattr->ovgL2cache,sizeof(DT_OVGL2_CacheSet));
		CoordinateCacheMem(NULL, pdtfwrk, &pdtfwrk->cachesetL2, &pdtfwrk->cachearrL2);
		pdtfwrk->usedcacheL2 = &pdtfwrk->cachearrL2;
		break;
	case DT_FCACHE_OVGL3CACHESET_ADD:
		if(!bOUL || !value){
			return DT_STYLE_NOT_SUPPORT;
		}
		sattr->ovgL3cache = (DT_void*)value;
		((DT_OVGL3_CacheSet*)sattr->ovgL3cache)->type = DTC_TYPE_OVGL3;
		if(CalculateCacheMem((DT_OVGL3_CacheSet*)sattr->ovgL3cache)<0){
			return DT_CACHESET_ADD_ERR;
		}
		DT_memcpy(&pdtfwrk->cachesetL3,sattr->ovgL3cache,sizeof(DT_OVGL3_CacheSet));
		CoordinateCacheMem(NULL, pdtfwrk, &pdtfwrk->cachesetL3, &pdtfwrk->cachearrL3);
		pdtfwrk->usedcacheL3 = &pdtfwrk->cachearrL3;
		break;
#endif
	default:
		return DT_STYLE_NOT_SUPPORT;
	}

	return DT_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT32_int  DT_GetFontStyle(DT_Handle hnd, DT_FontStyle_Option option)
{
	pDT_Fontwrk		pdtfwrk = (pDT_Fontwrk) hnd;
	pDT_StyleAttr	sattr;
	DT32_int		ret, bOUL=0;
	DLO_Font_Metrix mtx;
	pDT_FontMgr_wrk	pmgr=NULL;
	pLayWrk			pshaper=NULL;
	DT32_int		charmapsz=0;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	/* check the option to avoid to get into here <= more efficient. */
	if(option >= 100 && option < 200){	/*DT_FMETRIX_HEIGHT(100) - DT_FMEMORY_FONTMANAGER(200)*/
		ret = DLO_GetFontMetrix(pdtfwrk->hShaper, &mtx);
		if(ret<0){
			return convReturnValue(ret);
		}
		switch(option){
		case DT_FMETRIX_HEIGHT:
			return mtx.height;
		case DT_FMETRIX_ASCENT:
			return mtx.ascent;
		case DT_FMETRIX_DESCENT:
			return mtx.descent;
		case DT_FMETRIX_INTERNALLEADING:
			return mtx.inleading;
		case DT_FMETRIX_EXTERNALLEADING:
			return mtx.exleading;
		case DT_FMETRIX_WIDTH:
			return mtx.width;
		case DT_FMETRIX_OVERHANG:
			return mtx.overhang;
		case DT_FMETRIX_FONTWEIGHT:
			return mtx.fontweight;
		default:
			//do nothing here. let it goes through.
			break;
		}
	}

	pshaper = (pLayWrk)pdtfwrk->hShaper;
	if(pdtfwrk->charmap){
		charmapsz = DT_MAX_GLYPH_COUNT_PER_FDL*sizeof(DT16_ushort);
		charmapsz = DT_ALLOC_SIZE(charmapsz);
	}else{
		charmapsz = 0;
	}		

	switch(option){
	case DT_FMEMORY_FONTMANAGER:
		pmgr = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;
		return DT_ALLOC_SIZE(pmgr->totalsize);
	case DT_FMEMORY_CREATEFONT:
//		return	DT_ALLOC_SIZE(pdtfwrk->totalmemsz) + 
//				DT_ALLOC_SIZE(pdtfwrk->rtdataszused) + 
//				DT_ALLOC_SIZE(pshaper->TotalWkmsize) + 
//				DT_ALLOC_SIZE(charmapsz);
		return	pdtfwrk->totalmemsz + 
				pdtfwrk->rtdataszused + 
				pshaper->TotalWkmsize + 
				charmapsz;
	case DT_FMEMORY_CREATE_MINI_SGST:
//		return	DT_ALLOC_SIZE(pdtfwrk->totalmemsz) + 
//				DT_ALLOC_SIZE(pdtfwrk->rtdataszused) + 
//				DT_ALLOC_SIZE(pshaper->TotalWkmsize) + 
//				DT_ALLOC_SIZE(pshaper->engGradSuggest) + 
//				DT_ALLOC_SIZE(charmapsz); 
		return	pdtfwrk->totalmemsz + 
				pdtfwrk->rtdatasuggest + 
				pshaper->TotalWkmsize + 
				pshaper->engGradSuggest + 
				charmapsz; 
	case DT_FMEMORY_FONTHANDLE_USED:
//		return	DT_ALLOC_SIZE(pdtfwrk->totalmemsz) + 
//				DT_ALLOC_SIZE(pdtfwrk->rtdataszused) + 
//				DT_ALLOC_SIZE(pshaper->TotalWkmsize) + 
//				(pshaper->engGradMaxUsed>0?DT_ALLOC_SIZE(pshaper->engGradMaxUsed):0) + 
//				DT_ALLOC_SIZE(charmapsz);
		return	pdtfwrk->totalmemsz + 
				pdtfwrk->rtdataszused + 
				pshaper->TotalWkmsize + 
				(pshaper->engGradMaxUsed>0?pshaper->engGradMaxUsed:0) + 
				charmapsz;
	default:
		//do nothing here. let it goes through.
		break;
	}

	sattr = &pdtfwrk->style;

	/* BDF font doesn't support font style */
	if(pdtfwrk->engtype==DLO_ENG_BDFRASTER){
		if( option!=DT_FSTYLE_WRITEDIR && 
			option!=DT_FSTYLE_XBYTE_ALIGN && 
			option!=DT_FSTYLE_SPACING &&
			option!=DT_FSTYLE_BIDI_RULE)
			return DT_STYLE_NOT_SUPPORT;
	}

	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG)
		bOUL = 1;

	switch(option){
	case DT_FSTYLE_VERT:		/* Now, horizontal only.	*/
		return sattr->vert;
	case DT_FSTYLE_SIZEX:		/* desired x size			*/
		return sattr->xsize;
	case DT_FSTYLE_SIZEY:		/* desired y size			*/
		return sattr->ysize;
	case DT_FSTYLE_IS_BOLD:		/* Bold font(1) or not(0)	*/
		return sattr->is_bold;
	case DT_FSTYLE_IS_ITALIC:	/* Italic font(1) or not(0)	*/
		return sattr->is_italic;
	case DT_FSTYLE_IS_UNDERLINE:/* Underline(1) or not(1)	*/
		return sattr->is_underline;
	case DT_FSTYLE_IS_STRIKE:	/* Strike(1) or not(1)		*/
		return sattr->is_strike;
	case DT_FSTYLE_F_EDGE:		/* font edge, such as bold, outline...*/
		return sattr->f_edge;
	case DT_FSTYLE_W_EDGE:		/* the width of the edge	*/
		return sattr->w_edge;
	case DT_FSTYLE_W_EDGE_26_6:	/* the width of the edge	*/
		return sattr->w_edge266;
	case DT_FSTYLE_ITALICAMOUNT:/* italic amount in pixels	*/
		return sattr->italic;
	case DT_FSTYLE_P_UNDERLINE:	/* the position of underline*/
		return sattr->p_underline;
	case DT_FSTYLE_W_UNDERLINE:	/* the width of underline	*/
		return sattr->w_underline;
	case DT_FSTYLE_E_UNDERLINE:	/* the extend of underline	*/
		return sattr->e_underline;
	case DT_FSTYLE_P_STRIKE:	/* the position of strike	*/
		return sattr->p_strike;
	case DT_FSTYLE_W_STRIKE:	/* the width of strike		*/
		return sattr->w_strike;
	case DT_FSTYLE_E_STRIKE:	/* the extend of strike		*/
		return sattr->e_strike;
	case DT_FSTYLE_GRAD:		/* GRAY16, GRAY256...etc.	*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		return sattr->grade;
	case DT_FSTYLE_DEGREE:		/* 1/1000 degree rotated, not support yet	*/
		return sattr->degree;
	case DT_FSTYLE_WRITEDIR:	/* write direction: DT_LEFTTORIGHT or DT_RIGHTTOLEFT	*/
		return sattr->writedir;
	case DT_FSTYLE_VG_COORD:	/* coordinate, DT_COORD_LEFT_TOP or DT_COORD_LEFT_BOT	*/
		if(!bOUL)
			return DT_STYLE_NOT_SUPPORT;
		return sattr->oulcoord;
	case DT_FSTYLE_VG_GEN_EMPATH:
		if(!bOUL)
			return DT_STYLE_NOT_SUPPORT;
		return sattr->gen_empath;
	case DT_FSTYLE_GRAD_VALUES:	/* an easy way to set gcolor when gray16, see DT_FSTYLE_GRAD_VALUES*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		return sattr->grade_values;
	case DT_FSTYLE_XBYTE_ALIGN:	/* 1 or 4 are valid, horizontal bytes alignment for GBMP, default:4*/
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		return sattr->xbytes_align;

	case DT_FSTYLE_SPACING:
		// do some check if needed.
		return sattr->spacing;
	case DT_FSTYLE_HINTING:
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		return sattr->hinting;
	case DT_FSTYLE_FORCE_MOVE_DOWN:
		if(bOUL)
			return DT_STYLE_NOT_SUPPORT;
		return sattr->forcedown;
	case DT_FSTYLE_BIDI_RULE:
		return sattr->bidirule;
	case DT_FCACHE_CACHESET_ADD:
		return (DT32_int)sattr->cacheset;
#if (1==DT_OPENVG_ENABLED)
	case DT_FCACHE_OVGL1CACHESET_ADD:
		return (DT32_int)sattr->ovgL1cache;
	case DT_FCACHE_OVGL2CACHESET_ADD:
		return (DT32_int)sattr->ovgL2cache;
	case DT_FCACHE_OVGL3CACHESET_ADD:
		return (DT32_int)sattr->ovgL3cache;
#endif
	default:
		return DT_STYLE_NOT_SUPPORT;
	}

	return DT_STYLE_NOT_SUPPORT;
}

DT32_int fastAw(pDT_Fontwrk	pdtfwrk, DT16_ushort* ucs_str, DT32_int ucs_cnt)
{
	DT32_int i, ret, aw, pixw, width, bOVG;
	pLayWrk	 pwrk = (pLayWrk)pdtfwrk->hShaper;

	bOVG = (pdtfwrk->engtype==DLO_ENG_DCWOPENVG) ? 1 : 0;
	if(!bOVG){
		ret = ReInitFont(pwrk);
		ret = convReturnValue(ret);
		if(DT_SUCCESS != ret)
			return ret;
	}else{
		ret = DT_SUCCESS;
	}

	width = 0;	pixw = 0;
	for(i=0; i<ucs_cnt; i++){
		if(bOVG){
			aw	= pwrk->fengfuncs.getAwidth(pwrk->ras_attr, ucs_str[i], -1);		// g2info not used
			width += aw;
			pixw += DLO_CALC_AW_AH(aw,pdtfwrk->style.xsize);
		}else{
			width += pwrk->fengfuncs.getAwidth(pwrk->ras_attr, ucs_str[i], -1);		// g2info not used
		}
	}
#if (1==DT_OPENVG_ENABLED)
	if(bOVG){
		if(gDT_EachGlyphWidth_on_Pixels){
			width = pixw;
		}else{
			width = DLO_OUL_ROOF_EM2PIX(width, pdtfwrk->style.xsize);
		}
	}
#endif
	return width;	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Get the advanced width of the string (ucs_str)						*/
/* Return value: >=0:advanced width; <0:error.							*/
DT32_int DT_GetAw(DT_Handle hnd, DT16_ushort* ucs_str, DT32_int ucs_cnt)
{
	DT32_int		ret, rtval=DT_SUCCESS, width=0, height=0, diff=gDT_FONT_EMSIZE-1,exten;
	pDT_Fontwrk		pdtfwrk = (pDT_Fontwrk) hnd;
	DLO_LayAttr		*lay;
	DLO_LayBuf		*buf;
	pLayWrk			pwrk;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	if(ucs_cnt<=0 || !ucs_str || ucs_cnt>DT_MAX_CODES_PER_STR)
		return DT_UCS_ERR;
	
	pwrk = (pLayWrk) pdtfwrk->hShaper;
	if(!pwrk)
		return DT_BAD_FONT_HANDLE;

	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG){
		pdtfwrk->lastreturn = DT_DEFAULT_LASTRETURN;
		pdtfwrk->laststrlen = 0;
	}

	// returned directly in some situations.
	pdtfwrk->bFastMode = isFastMode(pdtfwrk, ucs_str, ucs_cnt);
	if( pdtfwrk->bFastMode ){
		return fastAw(pdtfwrk, ucs_str, ucs_cnt);
	}
	
	buf	  = (DLO_LayBuf*)pdtfwrk->dlolaybuf;
	//DT_memset(buf,0,pdtfwrk->dlolaybufsz);	// 20101111_for_Performance

	lay = (DLO_LayAttr*)pdtfwrk->dlolayattr;
	//DT_memset(lay,0,pdtfwrk->dlolayattrsz);	// 20101111_for_Performance
	lay->mainScript	= DLO_SCRIPT_DFLT;
	lay->mainLang	= DLO_LANG_DFLT;
	lay->ucs_cnt	= ucs_cnt;
	lay->ucs_str	= ucs_str;
	lay->writedir	= pdtfwrk->style.writedir;

	ret = DLO_ShapeString(pdtfwrk->hShaper,lay,buf,DLO_DATA_PREPARE_POS);
	rtval = convReturnValue(ret);

#if (1==DT_OPENVG_ENABLED)
	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG){
		if(gDT_EachGlyphWidth_on_Pixels){
			width = buf->bmpwidth;
			height= buf->bmpheight;
		}else{
			//width = buf->eswidth;
			//height= buf->esheight;
			width = DLO_OUL_ROOF_EM2PIX(buf->eswidth,pdtfwrk->style.xsize);
			height= DLO_OUL_ROOF_EM2PIX(buf->esheight,pdtfwrk->style.ysize);
		}
		#ifdef DT_VERT_BY_OVG
		if(pdtfwrk->style.vert){
			DT32_int tmp;
			tmp = width;
			width = height;
			height= tmp;
		}	
		#endif

//#ifdef DT_VERT_BY_OVG
//		if(pdtfwrk->style.vert){
//			DT32_int tmp;
//			tmp = buf->eswidth;
//			buf->eswidth = buf->esheight;
//			buf->esheight= tmp;
//		}	
//#endif
//
//		if(buf->eswidth==0){
//			width = 0;
//		}else{
//			width = (buf->eswidth*pdtfwrk->style.xsize+diff)/gDT_FONT_EMSIZE;
//		}
//		if(buf->esheight==0){
//			height = 0;
//		}else{
//			height = (buf->esheight*pdtfwrk->style.ysize+diff)/gDT_FONT_EMSIZE;
//		}
	}else
#endif
	{
		//Marked_by_Jacky_20101201: for DT_RIGHTTOLEFT and the last char's aw=0
		//width = buf->caret_seq[buf->glyf_cnt-1].caretpos.x;
		//if(width==buf->caret_seq[buf->glyf_cnt-1].oripos.x){ //last char is Arabic(DT_RIGHTTOLEFT)
		//	width += buf->caret_seq[buf->glyf_cnt-1].awvec.vx;
		//}
		width = buf->bmpwidth;
		height= buf->bmpheight;
		//pwrk  = (pLayWrk)pdtfwrk->hShaper;
		exten = pwrk->fengfuncs.getAexten(pwrk->ras_attr, buf->glyf_seq[buf->glyf_cnt-1]);
		if(exten>0){
			if(pdtfwrk->style.vert)
				height -=exten;
			else
				width -= exten;
		}
		// comment by Jacky_20110617: to endure minus aw
//		if(width<0){
//			width = 0;		// Avoid aw to be minus. Is it correct?
//		}
//		if(height<0){
//			height = 0;
//		}
	}

	DLO_DeShapeString(pdtfwrk->hShaper,buf);

	if(rtval<DT_SUCCESS)
		return rtval;
	else{
		if(pdtfwrk->style.vert)
			return height;
		else
			return width;
	}
}

DT_void fastFillingDT_OulPos(DT16_ushort idx, DT32_int width, DT32_int aw, DT_OulPos *opos)
{
	opos->gidx = idx;
	opos->oripos.x = width;
	opos->oripos.y = 0;
	opos->caretpos.x = width + aw;
	opos->caretpos.y = 0;
	opos->awvec.vx = aw;
	opos->awvec.vy = 0;
	opos->adjvec.vx = opos->adjvec.vy = 0;
	opos->drawmethod = DLO_DRAW_NORMAL;
	opos->dmrect.xy.x = opos->dmrect.xy.y = opos->dmrect.hw.vx = opos->dmrect.hw.vy = 0;
}

DT_void fastFillingDT_PosInfo(DT16_ushort idx, DT32_int width, DT32_int aw, DT_PosInfo *pinfo)
{
	pinfo->gidx = idx;
	pinfo->caretpos.x = width + aw;
	pinfo->caretpos.y = 0;
}

DT_void fastFillingDT_CodePositioning(DT16_ushort idx, DT32_int width, DT32_int aw, DLO_CodePositioning *p)
{
	p->codeidx = idx;
	p->glyfidx = idx;	// the same
	p->n_per_glyf = 1;	//Make_n_per_glyf(1,1);
	p->caretpos.x= width + aw;
	p->caretpos.y= 0;
	p->oripos.x	= width;
	p->oripos.y	= 0;
	p->awvec.vx	= aw;
	p->awvec.vy	= 0;
	p->adjvec.vx	= 0;
	p->adjvec.vy = 0;
	p->drawmethod= DLO_DRAW_NORMAL;
	p->dmrect.xy.x = p->dmrect.xy.y = p->dmrect.hw.vx = p->dmrect.hw.vy = 0;
}

DT32_int fastTextRect(pDT_Fontwrk pdtfwrk, DT16_ushort* ucs_str, DT32_int ucs_cnt, DT_RECT *rect, 
						DT32_int *xbytes, DT_TextInfo *info)
{
	DT32_int		i, ret, aw=0, width=0, height=0, xbts=0, diff=gDT_FONT_EMSIZE-1, spacing=0, italic=0;
	pLayWrk			pwrk = (pLayWrk) pdtfwrk->hShaper;
	DT_BOOL			bOVGmode = DT_FALSE;
	DT32_int		pixwidth, pixheight, emwidth;
	DT32_int		gcnt, /*bEmpty=0,*/ bBreak=0;

	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG){
		bOVGmode = DT_TRUE;
	}
	if(!bOVGmode){
		ret = ReInitFont(pwrk);
		ret = convReturnValue(ret);
		if(DT_SUCCESS > ret)
			return ret;
	}else{
		ret = DT_SUCCESS;
	}

	width = 0;	pixwidth = 0; emwidth = 0;
	height = pwrk->fengfuncs.getHeight(pwrk->ras_attr);		// No scale FDL, can use this func.
	pixheight = DLO_CALC_AW_AH(height,pdtfwrk->style.ysize);
	//if(info){
	//	DT_memset(info,0,sizeof(DT_TextInfo));				// 2012-02-15: not required.
	//}
	for(i=0; i<ucs_cnt; i++){
		pwrk->g2info[i].checkedFlag = 0;
		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, ucs_str[i], i);		// g2info not used.
		if(info){
			if(bOVGmode/*pdtfwrk->engtype==DLO_ENG_DCWOPENVG*/){
				fastFillingDT_OulPos((DT16_ushort)i, width, aw, &info->oulcarets[i]);
				pixwidth += DLO_CALC_AW_AH(aw,pdtfwrk->style.xsize);
			}else{
				fastFillingDT_PosInfo((DT16_ushort)i, width, aw, &info->carets[i]);
			}	
		}
		width += aw;
		//if(0==aw){														// DT_GetTextRect() doesn't return EMPTY_FONT.
		//	//ret |= DT_WARNING_EMPTY_FONT;
		//	bEmpty = 1;
		//}
		if(ucs_str[i]==0x0A || ucs_str[i]==0x0D){							// only these 2 codes will get into FastMode.
			if(pdtfwrk->style.bidirule==DT_BIDI_UNIRULE){
				bBreak = 1;
				i++;
				break;
			}
		}
		if(!pwrk->g2info[i].codeExist){
			if(!DT_isCode_NoEmptyFontWarning(ucs_str[i],NULL)){
				ret |= DT_WARNING_EMPTY_FONT;
			}
		}
	}
	gcnt = i;
	emwidth = width;

#if (1==DT_OPENVG_ENABLED)
	if(bOVGmode/*pdtfwrk->engtype==DLO_ENG_DCWOPENVG*/){
		DT32_int hwedge, vwedge;
		// The two func in OpenVG isn't implemented, calc bold and italic by ourselves.
		//vext = pwrk->fengfuncs.getVexten(pwrk->ras_attr, 0x0000);
		//hext = pwrk->fengfuncs.getAexten(pwrk->ras_attr, 0x0000);	// DcwOpenVG don't support italic! added it later!
		hwedge = vwedge = 0;
		if(pdtfwrk->style.w_edge > 0){
			if(pdtfwrk->style.f_edge==DT_STYLE_BOLD || pdtfwrk->style.f_edge==DT_STYLE_OUTLINE){	// OpenVG mode supports these 2 style only.
				hwedge = vwedge = pdtfwrk->style.w_edge * 2;
			}//else hwedge = vwedge = 0;
		}
		if(gDT_EachGlyphWidth_on_Pixels){
			spacing = pwrk->spacing;
			italic  = pdtfwrk->style.italic;
			width = pixwidth;
			height= pixheight + vwedge;
		}else{
//			spacing = DLO_OUL_ROOF_SCALED_PIX2EM(pdtfwrk->style.spacing,pdtfwrk->style.xsize);	//(pwrk->spacing*gDT_FONT_EMSIZE)/pwrk->xsize;
//			italic  = DLO_OUL_ROOF_SCALED_PIX2EM(pdtfwrk->style.italic,pdtfwrk->style.xsize);	//(pdtfwrk->style.italic*gDT_FONT_EMSIZE)/pdtfwrk->style.xsize;
//			hwedge	= DLO_OUL_ROOF_SCALED_PIX2EM(hwedge,pdtfwrk->style.xsize);					//(hwedge*gDT_FONT_EMSIZE)/pdtfwrk->style.xsize;
//			vwedge	= DLO_OUL_ROOF_SCALED_PIX2EM(vwedge,pdtfwrk->style.ysize);					//(vwedge*gDT_FONT_EMSIZE)/pdtfwrk->style.ysize;
//			height	+= vwedge;
			spacing = pdtfwrk->style.spacing;
			italic  = pdtfwrk->style.italic;
			hwedge	= hwedge;
			vwedge	= vwedge;
			height	= DLO_OUL_ROOF_EM2PIX(height,pdtfwrk->style.ysize);
			height	+= vwedge;
			width	= DLO_OUL_ROOF_EM2PIX(width,pdtfwrk->style.xsize);
		}
		
		if(width > 0){
			if(spacing < 0)
				width += -spacing;
			width += italic;
		}
	}else
#endif
	{
		DT32_int vext=0, hext=0;
		vext = pwrk->fengfuncs.getVexten(pwrk->ras_attr, 0x0000);	// w_edge inside here for BMP mode!
		hext = pwrk->fengfuncs.getAexten(pwrk->ras_attr, 0x0000);	// italic inside here for BMP mode!
		spacing = pwrk->spacing;
		if(width > 0){
			width += hext;
			height += vext;
			if(spacing < 0)
				width += -spacing;
		}
	}
	
	if(rect){
		rect->xy.x = 0;
		rect->xy.y = 0;
		rect->hw.vx= width;
		rect->hw.vy= height;
	}
	xbts = Calxbytes(pwrk, width);
	if(xbytes){
		*xbytes = xbts;
	}
	if(info){
		info->gcnt = gcnt;
		info->writedir = DT_LEFTTORIGHT; /* Only Latin here! */
		DT_memcpy(info->glyphs,ucs_str,info->gcnt*sizeof(ucs_str[0]));
		info->bmpwidth = width;
		info->bmpheight= height;
	  if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG){
#if (1==DT_OPENVG_ENABLED)
		  if(gDT_OVGWidth_Based_on_GBMPWidth && gDT_EachGlyphWidth_on_Pixels){
			  // 2012-05-24: offset the origin position x to fill out the rect.
			  DT_OulPos *po;
			  DT_VGtype sRatio;
			  po = info->oulcarets;
			  sRatio = (DT_VGtype)emwidth * pdtfwrk->style.xsize / gDT_FONT_EMSIZE;
			  for(i=0; i<gcnt; i++, po++){
				  po->oripos.x = (DT32_int)(po->oripos.x * pixwidth / sRatio);
				  po->caretpos.x = (DT32_int)(po->caretpos.x * pixwidth / sRatio);
			  }
		  }
#endif
	  }else{
		info->xbytes   = xbts;
		info->bitcount = (pwrk->mode==DLO_LAYOUT_BIT)?1:8;
		info->bufsize  = info->xbytes * info->bmpheight;
	  }
	}

	//if(bEmpty)						// DT_GetTextRect() doesn't return EMPTY_FONT.
	//	ret |= DT_WARNING_EMPTY_FONT;
	if(bBreak && gcnt!=ucs_cnt)
		ret |= DT_WARNING_BREAKLINE;

	if(bOVGmode){
		pdtfwrk->lastreturn = ret;		//convReturnValue(ret);
		pdtfwrk->laststrlen	= ucs_cnt;
		DT_memcpy(pdtfwrk->laststr, ucs_str, ucs_cnt*sizeof(ucs_str[0]));
	}
	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Get the text rectangle of the string (ucs_str)						*/
/* Return value: 0:DT_SUCCESS; <0:error.								*/
/* Notice: DLO_ENG_DCWOPENVG engine will be the sum of each glyphs' aw	*/
/* other engine will be the width of the returned bmp					*/
DT32_int DT_GetTextRect(DT_Handle hnd, DT16_ushort* ucs_str, DT32_int ucs_cnt, DT_RECT *rect, 
						DT32_int *xbytes, DT_TextInfo *info)
{
	DT32_int		ret, width=0, height=0, xbts=0, diff=gDT_FONT_EMSIZE-1, vext=0;
	pDT_Fontwrk		pdtfwrk = (pDT_Fontwrk) hnd;
	pDT_LayBuf		playbuf = NULL;
	pDT_OulBuf		poulbuf = NULL;
	DT_Point		xy={0,0};
	pLayWrk			pwrk;
	DT_BOOL			bOVGmode = DT_FALSE;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	if(ucs_cnt<=0 || !ucs_str || ucs_cnt>DT_MAX_CODES_PER_STR)
		return DT_UCS_ERR;

	pwrk = (pLayWrk) pdtfwrk->hShaper;
	if(!pwrk)
		return DT_BAD_FONT_HANDLE;

	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG){
		bOVGmode = DT_TRUE;
		pdtfwrk->lastreturn = DT_DEFAULT_LASTRETURN;
		pdtfwrk->laststrlen = 0;
	}
	
	// returned directly in some situations.
	pdtfwrk->bFastMode = isFastMode(pdtfwrk, ucs_str, ucs_cnt);
	if( pdtfwrk->bFastMode ){
		return fastTextRect(pdtfwrk, ucs_str, ucs_cnt, rect, xbytes, info);
	}

	if(bOVGmode/*pdtfwrk->engtype==DLO_ENG_DCWOPENVG*/){
		ret = DT_RasterOUL(hnd, ucs_str, ucs_cnt, DT_GET_INFO, &poulbuf);
	}else{
		ret = DT_RasterGBMP(hnd, ucs_str, ucs_cnt, DT_GET_INFO, &playbuf, NULL, 0, 0, xy);
	}
	if(ret<0){
		return ret;
	}

#if (1==DT_OPENVG_ENABLED)
	if(bOVGmode/*pdtfwrk->engtype==DLO_ENG_DCWOPENVG*/){
		if(gDT_EachGlyphWidth_on_Pixels){
		 #ifdef DT_VERT_BY_OVG
			if(pdtfwrk->style.vert){
				height= poulbuf->pixwidth;
				width = poulbuf->pixheight;
			}
			else{
				width = poulbuf->pixwidth;
				height= poulbuf->pixheight;
			}
		 #else
			width = poulbuf->pixwidth;
			height= poulbuf->pixheight;
		 #endif

//			if(width!=0){								// 2012-02-10: not required
//				width = (width*pdtfwrk->style.xsize+diff)/gDT_FONT_EMSIZE;
//			}
//			if(height!=0){
//				height= (height*pdtfwrk->style.ysize+diff)/gDT_FONT_EMSIZE;
//			}

			if(pdtfwrk->style.vert){
				if(height!=0)
					height+= pdtfwrk->style.italic;		// 2011-12-20: italic add here, because DcwOpenVG don't support italic! not the same with DcwRaster!
			}else{
				if(width!=0)
					width += pdtfwrk->style.italic;		// 2011-12-20: italic add here, because DcwOpenVG don't support italic! not the same with DcwRaster!
			}
			xbts = 0;
			if(rect){
				DT32_int wedge;
				vext = pwrk->fengfuncs.getVexten(pwrk->ras_attr, 0x0000);
				wedge = 0;
				if(pdtfwrk->style.w_edge > 0){
					if(pdtfwrk->style.f_edge==DT_STYLE_BOLD || pdtfwrk->style.f_edge==DT_STYLE_OUTLINE) // OVG supports the 2 style only!
						wedge = pdtfwrk->style.w_edge * 2;
					//else
					//	wedge = 0;
				}
				
				if(pdtfwrk->style.vert){
					rect->xy.x = DLO_OUL_FLOOR_EM2PIX(pwrk->linemoveYup,pdtfwrk->style.xsize);// 2012-02-14: for the same as STD
					rect->xy.y = DLO_OUL_FLOOR_EM2PIX(pwrk->linemoveXlf,pdtfwrk->style.ysize);
					rect->hw.vx= pdtfwrk->style.xsize+vext+wedge;
					rect->hw.vy= height;
				}else{
					rect->xy.x = DLO_OUL_FLOOR_EM2PIX(pwrk->linemoveXlf,pdtfwrk->style.xsize);
					rect->xy.y = DLO_OUL_FLOOR_EM2PIX(pwrk->linemoveYup,pdtfwrk->style.ysize);
					rect->hw.vx= width;
					rect->hw.vy= pdtfwrk->style.ysize+vext+wedge;
				}
			}
		}else{
		 #ifdef DT_VERT_BY_OVG
			if(pdtfwrk->style.vert){
				height= poulbuf->eswidth;
				width = poulbuf->esheight;
			}
			else{
				width = poulbuf->eswidth;
				height= poulbuf->esheight;
			}
		 #else
			width = poulbuf->eswidth;
			height= poulbuf->esheight;
		 #endif
			
			if(pdtfwrk->style.vert){
				//if(height!=0)
				//	height+= DLO_OUL_ROOF_SCALED_PIX2EM(pdtfwrk->style.italic,pdtfwrk->style.ysize);	// 2012-02-10: italic in EM
				width = DLO_OUL_ROOF_EM2PIX(width, pdtfwrk->style.ysize);
				height= DLO_OUL_ROOF_EM2PIX(height, pdtfwrk->style.xsize);
				if(height > 0)
					height += pdtfwrk->style.italic;
			}else{
				//if(width!=0)
				//	width += DLO_OUL_ROOF_SCALED_PIX2EM(pdtfwrk->style.italic,pdtfwrk->style.xsize);	// 2012-02-10: italic in EM
				width = DLO_OUL_ROOF_EM2PIX(width, pdtfwrk->style.xsize);
				height= DLO_OUL_ROOF_EM2PIX(height, pdtfwrk->style.ysize);
				if(width > 0)
					width += pdtfwrk->style.italic;
			}
			xbts = 0;
			if(rect){
				DT32_int wedge;
				vext = pwrk->fengfuncs.getVexten(pwrk->ras_attr, 0x0000);
				wedge = 0;
				if(pdtfwrk->style.w_edge > 0){
					if(pdtfwrk->style.f_edge==DT_STYLE_BOLD || pdtfwrk->style.f_edge==DT_STYLE_OUTLINE) // OVG supports the 2 style only!
						wedge = pdtfwrk->style.w_edge * 2;
					//else
					//	wedge = 0;
				}
				
				if(pdtfwrk->style.vert){
					//wedge = DLO_OUL_ROOF_SCALED_PIX2EM(wedge,pdtfwrk->style.xsize);
					rect->xy.x = DLO_OUL_ROOF_EM2PIX(pwrk->linemoveYup, pdtfwrk->style.ysize);
					rect->xy.y = DLO_OUL_ROOF_EM2PIX(pwrk->linemoveXlf, pdtfwrk->style.xsize);
					rect->hw.vx= pdtfwrk->style.xsize+vext+wedge;		//gDT_FONT_EMSIZE+vext+wedge;
					rect->hw.vy= height;
				}else{
					//wedge = DLO_OUL_ROOF_SCALED_PIX2EM(wedge,pdtfwrk->style.ysize);
					rect->xy.x = DLO_OUL_ROOF_EM2PIX(pwrk->linemoveXlf, pdtfwrk->style.xsize);
					rect->xy.y = DLO_OUL_ROOF_EM2PIX(pwrk->linemoveYup, pdtfwrk->style.ysize);
					rect->hw.vx= width;
					rect->hw.vy= pdtfwrk->style.ysize+vext+wedge;		//gDT_FONT_EMSIZE+vext+wedge;
				}
			}
		}
	}else
#endif	
	{
		width = playbuf->bmpwidth;
		height= playbuf->bmpheight;
		xbts = playbuf->xbytes;
		if(rect){
			pwrk = (pLayWrk) pdtfwrk->hShaper;
			vext = pwrk->fengfuncs.getVexten(pwrk->ras_attr, 0x0000);
			if(pdtfwrk->style.vert){
				rect->xy.x = pwrk->linemoveYup;
				rect->xy.y = pwrk->linemoveXlf;
				rect->hw.vx= pdtfwrk->style.xsize+vext;	//width - DTAbs(pwrk->linemoveYup) - DTAbs(pwrk->linemoveYdn);
				rect->hw.vy= height;
			}else{
				rect->xy.x = pwrk->linemoveXlf;
				rect->xy.y = pwrk->linemoveYup;
				rect->hw.vx= width;
				rect->hw.vy= pdtfwrk->style.ysize+vext;	//height -  DTAbs(pwrk->linemoveYup) - DTAbs(pwrk->linemoveYdn);
			}
		}
	}

	if(xbytes){
		*xbytes = xbts;
	}

	if(info){
	  //DT_memset(info,0,sizeof(DT_TextInfo));		// not required to speed up
#if (1==DT_OPENVG_ENABLED)
	  if(bOVGmode/*pdtfwrk->engtype==DLO_ENG_DCWOPENVG*/){
		  info->gcnt = poulbuf->gcnt;
		  DT_memcpy(info->glyphs,poulbuf->glyphs,poulbuf->gcnt*sizeof(DT16_ushort));
		  info->writedir = poulbuf->writedir; /* The values and meanings are the same in DigiTypeAPI & DcwShaper. */
		  DT_memcpy(info->oulcarets,poulbuf->carets,poulbuf->gcnt*sizeof(DT_OulPos));
		  info->bmpwidth = width;
		  info->bmpheight= height;
		  info->xbytes   = 0;
		  info->bitcount = 0;
		  info->bufsize  = 0;
	  }else
#endif	  
	  {
		info->gcnt = playbuf->gcnt;
		DT_memcpy(info->glyphs,playbuf->glyphs,playbuf->gcnt*sizeof(DT16_ushort));
		info->writedir = playbuf->writedir;	/* The values and meanings are the same in DigiTypeAPI & DcwShaper. */
		DT_memcpy(info->carets,playbuf->carets,playbuf->gcnt*sizeof(DT_PosInfo));
		info->bmpwidth = width;
		info->bmpheight= height;
		info->xbytes   = playbuf->xbytes;
		info->bitcount = playbuf->bitcount;
		info->bufsize  = playbuf->bufsize;
	  }
	}

	// 2011-11-11: don't release the data.
//	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG){
//		ret = DT_RasterOUL(hnd, ucs_str, ucs_cnt, DT_RELEASE, &poulbuf);
//	}else{
//		//ret = DT_RasterGBMP(hnd, ucs_str, ucs_cnt, DT_RELEASE, &playbuf, NULL, 0, 0, xy);	// 20101111_for_Performance
//	}
	ret = convReturnValue(ret);
	if(ret<0){
		return ret;
	}
	
	// 2011-11-11: Success, set lastreturn
	if(bOVGmode){
		pdtfwrk->lastreturn = ret;		//DT_SUCCESS;
		pdtfwrk->laststrlen	= ucs_cnt;
		DT_memcpy(pdtfwrk->laststr, ucs_str, ucs_cnt*sizeof(ucs_str[0]));
	}

	return ret;
}

DT32_int fastInfoforGrayBMP(pDT_Fontwrk pdtfwrk, DT16_ushort* ucs_str, DT32_int ucs_cnt, pDT_LayBuf *pbuf)
{
	DT32_int		i, ret, bEmpty, bBreak, aw, vext, hext;
	pDT_LayBuf		dtlay = (pDT_LayBuf) pdtfwrk->rtbuffer;
	pLayWrk			pwrk = (pLayWrk) pdtfwrk->hShaper;
	DLO_LayAttr		*layattr = (DLO_LayAttr*)pdtfwrk->dlolayattr;
	DLO_LayBuf		*dlolay= pdtfwrk->dlolaybuf;
	DT_PosInfo		*carets = pdtfwrk->laycarets;
	DLO_CodePositioning *cp = dlolay->caret_seq;

	/* OVG don't require re-initFont. */
	ret = ReInitFont(pwrk);
	ret = convReturnValue(ret);
	if(DT_SUCCESS != ret)
		return ret;

	pwrk->attr	= layattr;
	pwrk->lobuf = dlolay;

	// layattr is used for L3 cache
	layattr->mainScript	= DLO_SCRIPT_DFLT;
	layattr->mainLang	= DLO_LANG_DFLT;
	layattr->ucs_cnt	= ucs_cnt;
	layattr->ucs_str	= ucs_str;
	layattr->writedir	= pdtfwrk->style.writedir;
	
	aw = 0; bEmpty = 0;	bBreak = 0;
	dlolay->bmpwidth  = 0;
	dlolay->bmpheight = pwrk->fengfuncs.getHeight(pwrk->ras_attr);

	for(i=0; i<ucs_cnt; i++){
		pwrk->g2info[i].checkedFlag = 0;									// be sure it's the first call.
		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, ucs_str[i], i);
		fastFillingDT_PosInfo((DT16_ushort)i, dlolay->bmpwidth, aw, &carets[i]);
		fastFillingDT_CodePositioning((DT16_ushort)i, dlolay->bmpwidth, aw, &cp[i]);
		dlolay->bmpwidth += aw;
		if(0==aw){
			//ret |= DT_WARNING_EMPTY_FONT;
			if(!DT_isCode_NoEmptyFontWarning(ucs_str[i],NULL)){
				bEmpty = 1;
			}
		}
		if(ucs_str[i]==0x0A || ucs_str[i]==0x0D){							// only these 2 codes will get into FastMode.
			if(pdtfwrk->style.bidirule==DT_BIDI_UNIRULE){
				bBreak = 1;
				i++;
				break;
			}
		}
	}
	dlolay->glyf_cnt = i;
	DT_memcpy(dlolay->glyf_seq, ucs_str, dlolay->glyf_cnt*sizeof(ucs_str[0]));

	vext = pwrk->fengfuncs.getVexten(pwrk->ras_attr, 0x0000);
	hext = pwrk->fengfuncs.getAexten(pwrk->ras_attr, 0x0000);
	if(dlolay->bmpwidth >= 0){
		dlolay->bmpwidth  += hext;
		dlolay->bmpheight += vext;
		if(pwrk->spacing<0){	/* Jacky_20100824 */
			dlolay->bmpwidth += (-pwrk->spacing);
		}
	}
	dtlay->gcnt		= dlolay->glyf_cnt;
	dtlay->glyphs	= (DT16_ushort*) dlolay->glyf_seq;
	dtlay->writedir = DT_LEFTTORIGHT;
	dtlay->carets	= carets;
	dtlay->bmpwidth	= dlolay->bmpwidth;
	dtlay->bmpheight= dlolay->bmpheight;
	dtlay->bmpbuf	= dlolay->bmpbuf = (DT8_uchar*)NULL;
	dtlay->xbytes	= dlolay->xbytes = Calxbytes(pwrk, dlolay->bmpwidth);
	dtlay->bufsize	= dlolay->bufsize= dtlay->xbytes * dtlay->bmpheight;
	dtlay->bitcount	= dlolay->bitcount = (pwrk->mode==DLO_LAYOUT_BIT)?1:8;

	pwrk->linemoveYup = pwrk->linemoveYdn = 0;
	pwrk->linemoveXlf = pwrk->linemoveXrt = 0;
	pwrk->linewidth	= dlolay->bmpwidth;
	pwrk->lineheight= dlolay->bmpheight;

	if(pbuf)
		*pbuf = dtlay;

	ret = DT_SUCCESS;
	if(bEmpty)
		ret |= DT_WARNING_EMPTY_FONT;
	if(bBreak && dlolay->glyf_cnt!=ucs_cnt)
		ret |= DT_WARNING_BREAKLINE;
	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_RasterGrayBMP(DT_Handle hnd, 
			  DT16_ushort* ucs_str,		/* the string to be drawn											*/
			  DT32_int	ucs_cnt,		/* count of ucs_str													*/
			  DT_void	*grayBMPbuf,	/* user allocated buffer to get grayBMP, typecast to DT8_char*, 	*/
			  DT32_int	x0,				/* x of start(left-top) position in grayBMPbuf						*/
			  DT32_int	y0,				/* y of start(left-top) position in grayBMPbuf						*/
			  DT32_int	xbytes,			/* How many bytes per line of the allocated grayBMPbuf				*/
			  DT32_int	height			/* height of grayBMPbuf												*/
			  )
{
	DT32_int		ret, rtval=DT_SUCCESS;//bEmpty=0, bBreak=0, bCut=0;
	pDT_Fontwrk		pdtfwrk = (pDT_Fontwrk) hnd;
	pDT_LayBuf		playbuf = NULL;
	DT_Point		xy={0,0};

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	if(ucs_cnt<=0 || !ucs_str)
		return DT_UCS_ERR;

	if(!grayBMPbuf){
		return DT_NOT_ENOUGH_BUFFER;
	}

	pdtfwrk->bFastMode = isFastMode(pdtfwrk, ucs_str, ucs_cnt);
	if( pdtfwrk->bFastMode ){
		DT32_int i, ltx, lty;
		pLayWrk	 pwrk = (pLayWrk) pdtfwrk->hShaper;
		
		// get info
		ret = fastInfoforGrayBMP(pdtfwrk, ucs_str, ucs_cnt, &playbuf);
		if(ret<0){
			return ret;
		}else
			rtval = ret;
//		if(ret&DT_WARNING_EMPTY_FONT){
//			bEmpty = 1;
//		}
//		if(ret&DT_WARNING_BREAKLINE){
//			bBreak = 1;
//		}

		// raster graybmp
		pwrk->lobuf->bmpbuf = (DT8_char*)grayBMPbuf;
		if(xbytes <= 0 || height <= 0)
			return DT_NOT_ENOUGH_BUFFER;
		if(xbytes < playbuf->xbytes || height < playbuf->bmpheight){		// 2012-02-17: Let it can be drawn incompletely.
		//	bCut = 1;
			rtval |= DT_WARNING_BMP_CUTTED;
		}

		for(i=0; i<ucs_cnt; i++){
			ltx = x0 + pwrk->lobuf->caret_seq[i].oripos.x;	// filled in fastInfoforGrayBMP().
			lty = y0 + pwrk->lobuf->caret_seq[i].oripos.y;
			pwrk->fengfuncs.getCharbmp(pwrk->ras_attr, ucs_str[i], i, xbytes, height, ltx, lty, xbytes, grayBMPbuf, NULL, pwrk->mode );
		}
		if(ret>=0 && pdtfwrk->style.w_underline>0)	// Jacky_20100727_underline
			drawBMPUnderline(pdtfwrk, pwrk->lobuf);

		if(ret>=0 && pdtfwrk->style.w_strike>0)		// Jacky_20100727_underline
			drawBMPStrike(pdtfwrk, pwrk->lobuf);

	}else{
		ret = DT_RasterGBMP(hnd, ucs_str, ucs_cnt, DT_GET_INFO, &playbuf, NULL, 0, 0, xy);
		if(ret<0)
			return ret;
		else rtval = ret;
//		if(ret&DT_WARNING_BREAKLINE){
//			bBreak = 1;
//		}

		xy.x=x0;	xy.y=y0;	//bEmpty = 0;
		ret = DT_RasterGBMP(hnd, ucs_str, ucs_cnt, DT_DRAW, &playbuf, grayBMPbuf, xbytes, height, xy);
		if(ret<0){
			return ret;
		}else rtval |= ret;
//		if(ret&DT_WARNING_EMPTY_FONT){
//			bEmpty = 1;
//		}
//		if(ret&DT_WARNING_BMP_CUTTED){
//			bCut = 1;
//		}
	}
	
	//xy.x=0;		xy.y=0;	// 20101111_for_Performance
	 /* grayBMPbuf use as a flag, so we have to pass it to tell DcwShaper not to clear the data. */
	//ret = DT_RasterGBMP(hnd, ucs_str, ucs_cnt, DT_RELEASE, &playbuf, grayBMPbuf, 0, 0, xy);	// 20101111_for_Performance
	//ret = DT_RasterGBMP(hnd, ucs_str, ucs_cnt, DT_RELEASE, &playbuf, grayBMPbuf, xbytes, height, xy);

//	if(ret>=DT_SUCCESS){
//		if(bEmpty){
//			ret |= DT_WARNING_EMPTY_FONT;
//		}
//		if(bBreak){
//			ret |= DT_WARNING_BREAKLINE;
//		}
//		if(bCut){
//			ret |= DT_WARNING_BMP_CUTTED;
//		}
//	}
//	return ret;
	return rtval;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Get a bmp and draw by DT_BitBlt()								*/
/* Return Value: 0:DT_SUCCESS; <0:error								*/
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
			  DT_RGBA	*incolor,		/* inner color			*/
			  DT_StrInfo *info,			/* the string info when return.	*/
			  DT_void	**userdata		/* user's data when DT_BitBlt()	*/
			  //DT_RECT		*rtClipping,	/* set the clipping rect  	*/
			  //VGPaint 		fillpaint,		/* fill paint 				*/
			  //DT32_int	flag,			/* clipping rect align flag		*/
			  )
{
	DT32_int		ret, bEmpty, bBreak, binner=0, w_edge=0, tmpf_edge=0, tmpgrade=0, tmpw_ul=0, tmpw_sk=0, tmpsp=0;
	pDT_Fontwrk		pdtfwrk = (pDT_Fontwrk) hnd;
	pDT_LayBuf		dtlaybuf=NULL;
	DT_DrawData		drawdata;
	DT_Point		xy={0,0};
	DT32_int		offsetX, offsetY;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	if(pdtfwrk->engtype==DLO_ENG_DCWOPENVG){
		return DT_CREATEFONT_MODE_ERR;
	}

	w_edge = pdtfwrk->style.w_edge;
	/* set outline style if needed. draw outline as DT_GRAY_MONO */
	if( pdtfwrk->style.f_edge==DT_STYLE_OUTLINE && w_edge>0
		&& pdtfwrk->engtype!=DLO_ENG_BDFRASTER){
		if(incolor){
			binner = 1;
			tmpf_edge = pdtfwrk->style.f_edge;
			tmpgrade = pdtfwrk->style.grade;
			tmpw_ul = DT_GetFontStyle(hnd,DT_FSTYLE_W_UNDERLINE);
			tmpw_sk = DT_GetFontStyle(hnd,DT_FSTYLE_W_STRIKE);			// Jacky_20100727_underline
			tmpsp	= DT_GetFontStyle(hnd,DT_FSTYLE_SPACING);
			/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_W_STRIKE,0);			// Jacky_20100727_underline
			/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_F_EDGE,DT_STYLE_BOLD);
			/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_SPACING,tmpsp - w_edge*2);	//Jacky_20110107
			pdtfwrk->bRasterOulBold = 1; /* This time, not draw bold if iconfont exist. */
			//ret = DT_SetFontStyle(hnd,DT_FSTYLE_GRAD,DT_GRAY_MONO);	// Marked by Jacky_20100727
		}
	}
	
	ret = DT_RasterGBMP(hnd,ucs_str,ucs_cnt,DT_GET_INFO,&dtlaybuf,NULL,0,0,xy);
	if(ret<0){
		goto error_return;
	}else{
		if(info){
			info->width = dtlaybuf->bmpwidth;
			info->height= dtlaybuf->bmpheight;
			info->gcnt  = dtlaybuf->gcnt;
			DT_memcpy(info->glyphs,dtlaybuf->glyphs,dtlaybuf->gcnt*sizeof(DT16_ushort));
		}
	}
	/* Get bmp */
	bEmpty = 0;	bBreak = 0;
	ret = DT_RasterGBMP(hnd,ucs_str,ucs_cnt,DT_DRAW,&dtlaybuf,NULL,0,0,xy);
	if(ret>=0){
		if(ret&DT_WARNING_EMPTY_FONT){
			bEmpty = 1;
		}
		if(ret&DT_WARNING_BREAKLINE){
			bBreak = 1;
		}
		/* Draw bmp by DT_BitBlt() */
		makeDrawData(pdtfwrk, dtlaybuf, fcolor, bkcolor, &drawdata);
		ret = DT_BitBlt(destdc,originx,originy,nwidth,nheight,&drawdata,userdata);
		if(ret<0){
			goto error_return;
		}
	}else{
		goto error_return;
	}
	/* set the buffer used back to 0. */
	ret = DT_RasterGBMP(hnd,ucs_str,ucs_cnt,DT_RELEASE,&dtlaybuf,NULL,0,0,xy);

	
	/* Draw inner side and set the style back if needed.	*/
	if(binner){
		pdtfwrk->bRasterOulBold = 0;	/* This time, draw normal if iconfont exist. */
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_W_UNDERLINE,0);
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_W_STRIKE,tmpw_sk);		// Jacky_20100727_underline, draw strike when normal
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_F_EDGE,DT_STYLE_NORMAL);
		//ret = DT_SetFontStyle(hnd,DT_FSTYLE_GRAD,tmpgrade);		// Marked by Jacky_20100727
		/* Set spacing to put the normal font in the right position. */
		/* Because of the implementation of underline issue, DigiType doesn't enable spacing setting.*/
		/* Call DcwShaper's function directly.														 */
		//Now DigiTypeAPI supports spacing
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_SPACING,tmpsp+w_edge*2);
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_SPACING,tmpsp);
		ret = DT_RasterGBMP(hnd,ucs_str,ucs_cnt,DT_GET_INFO,&dtlaybuf,NULL,0,0,xy);
		if(ret<0){
			goto error_return;
		}
		
		bEmpty = 0;
		ret = DT_RasterGBMP(hnd,ucs_str,ucs_cnt,DT_DRAW,&dtlaybuf,NULL,0,0,xy);
		if(ret>=0){
			if(ret&DT_WARNING_EMPTY_FONT){
				bEmpty = 1;
			}
			if(ret&DT_WARNING_BREAKLINE){
				bBreak = 1;
			}

			/* be care of start position & color. */
			makeDrawData(pdtfwrk, dtlaybuf, incolor, fcolor, &drawdata);
			/* Modified_by_Jacky_20101119: for put chars in the middle with iconfont. */
			/* Modified_by_Jacky_20110323: for vertical writing.					  */
//			if((dtlaybuf->bmpwidth+2*w_edge)!=info->width){
//				offsetX = originx+(info->width/2 - dtlaybuf->bmpwidth/2);
//			}else{
//				offsetX = originx+w_edge;
//			}
//			if((dtlaybuf->bmpheight+2*w_edge)!=info->height){
//				offsetX = originx+w_edge;
//				offsetY = originy+(info->height/2 - dtlaybuf->bmpheight/2);
//			}else{
//				offsetX = originx+w_edge;
//				offsetY = originy+w_edge;
//			}
			/* Modified_by_Jacky_20110429: force to put the normal bmp in the right place of the bold bmp. */
			offsetX = originx+w_edge;
			offsetY = originy+w_edge;
			//ret = DT_BitBlt(destdc,originx+w_edge,originy+w_edge,nwidth,nheight,&drawdata,userdata);
			ret = DT_BitBlt(destdc,offsetX,offsetY,nwidth,nheight,&drawdata,userdata);
			if(ret<0){
				goto error_return;
			}
		}else{
			goto error_return;	
		}
		ret = DT_RasterGBMP(hnd,ucs_str,ucs_cnt,DT_RELEASE,&dtlaybuf,NULL,0,0,xy);
		/* set the font style back. */
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_W_UNDERLINE,tmpw_ul);
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_F_EDGE,tmpf_edge);
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_SPACING,tmpsp);
	}

	if(ret==DT_SUCCESS){				//Modified_By_Jacky_20101213: 
		if(bEmpty){
			ret |= DT_WARNING_EMPTY_FONT;
		}
		if(bBreak){
			ret |= DT_WARNING_BREAKLINE;
		}
	}
	return ret;
	//return DT_SUCCESS;
	
error_return:
	pdtfwrk->bRasterOulBold = 0;
	if(binner){
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_W_UNDERLINE,tmpw_ul);
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_F_EDGE,tmpf_edge);
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_GRAD,tmpgrade);
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_W_STRIKE,tmpw_sk);
		/*ret = */DT_SetFontStyle(hnd,DT_FSTYLE_SPACING,tmpsp);
	}
//	DT_SetFontStyle(hnd,DT_FSTYLE_GRAD,tmpgrade);
//	DT_SetFontStyle(hnd,DT_FSTYLE_F_EDGE,tmpf_edge);
//	DLO_SetFontStyle(pdtfwrk->hShaper,FSTYLE_SPACING,tmpsp);
	DT_RasterGBMP(hnd,ucs_str,ucs_cnt,DT_RELEASE,&dtlaybuf,NULL,0,0,xy);	// 20101111_for_Performance
	return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* These functions are used to operate FontEngine directly, no need to distinguish its script or language. */
/* Different from the above functions, it's caller's responsibility to allocate the required memory for 'bmp' or 'path'*/
DT32_int DT_GetCharAw(DT_Handle hnd, DT16_ushort ucs)
{
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;
	DT32_int ret, rtval;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	ret = DLO_GetCharAw(pdtfwrk->hShaper, ucs);
	if(ret<0)
		rtval = convReturnValue(ret);
	else
		rtval = ret;

	return rtval;
}

DT32_int DT_GetFontRect(DT_Handle hnd, DT_RECT *rt)
{
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;
	DT32_int ret, rtval;
	DLO_RECT rect={{0,0},{0,0}};

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	ret = DLO_GetFontRect(pdtfwrk->hShaper, &rect);
	rtval = convReturnValue(ret);
	if(rt){
		rt->xy.x  = rect.xy.x;
		rt->xy.y  = rect.xy.y;
		rt->hw.vx = rect.hw.vx;
		rt->hw.vy = rect.hw.vy;
	}
	return rtval;
}

DT32_int DT_GetCharGBMP(DT_Handle hnd, DT16_ushort ucs, DT_void *bmp, DT32_int xbytes, DT_RECT clip)
{
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;
	DT32_int ret, rtval;
	DLO_RECT rect={{0,0},{0,0}};

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	rect.xy.x = clip.xy.x;
	rect.xy.y = clip.xy.y;
	rect.hw.vx= clip.hw.vx;
	rect.hw.vy= clip.hw.vy;

	ret = DLO_GetCharGBMP(pdtfwrk->hShaper,ucs,bmp,xbytes,rect);
	rtval = convReturnValue(ret);

	return rtval;
}

DT32_int DT_GetCharOUL(DT_Handle hnd, DT16_ushort ucs, DT_void *path, DT32_long pathbytes, DT32_long *pathsize)
{
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;
	DT32_int ret, rtval;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	ret = DLO_GetCharOUL(pdtfwrk->hShaper,ucs,-1,path,pathbytes,pathsize);
	rtval = convReturnValue(ret);

	return rtval;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT32_int makeCharmap(pDT_Fontwrk pdtfwrk)
{
	DT32_uint charmapsz=0;
	DT8_char  *charmap=NULL;
	DT32_int  keeprtdatasz=0;	// Ensure rtdata is allocated after charmap. // Jacky_20101213

DBG_MSG_SHOW_FUNC_NAME();

	if(pdtfwrk->rtdatasz>0){
		keeprtdatasz = pdtfwrk->rtdatasz;
		if(pdtfwrk->rtdata){
			DT_free(pdtfwrk->rtdata);
		}
		pdtfwrk->rtdata = NULL;
		pdtfwrk->rtdatasz = 0;
	}


	charmapsz = DT_MAX_GLYPH_COUNT_PER_FDL*sizeof(DT16_ushort);
	charmap = (DT8_char*) DT_malloc(DT_ALLOC_SIZE(charmapsz));
	if(!charmap){
		if(keeprtdatasz>0){
			pdtfwrk->rtdatasz = keeprtdatasz;
			pdtfwrk->rtdata = DT_malloc(pdtfwrk->rtdatasz);		// It should always be successful, because it just had been free.
		}
		return -1;
	}else{
		if(keeprtdatasz>0){			// try to allocate rtdata back.
			pdtfwrk->rtdatasz = keeprtdatasz;
			pdtfwrk->rtdata = DT_malloc(pdtfwrk->rtdatasz);
			if(!pdtfwrk->rtdata){	// Memory left isn't enough for both charmap and rtdata, reserve rtdata first.
				if(pdtfwrk->charmap){
					DT_free(pdtfwrk->charmap);
					pdtfwrk->charmap = NULL;
				}
				pdtfwrk->rtdatasz = keeprtdatasz;
				pdtfwrk->rtdata = DT_malloc(pdtfwrk->rtdatasz);	// It should always be successful, because it just had been free.
				return -1;
			}
		}

	}

	pdtfwrk->charmap = (DT16_ushort*) charmap;
	pdtfwrk->charmap_num = 0;

	getGlyphsCount(pdtfwrk);
	return 0;

}

DT32_uint DT_GlyphsCount(DT_Handle hnd)
{
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return 0;

	if(pdtfwrk->charmap_num>0)
		return pdtfwrk->charmap_num;

	if( gEnbale_DT_Charmap ){
	  if(!pdtfwrk->charmap){
		if(makeCharmap(pdtfwrk)<0){
			return 0;
		}
	  }
	}else{
	  return 0;
	}

	return pdtfwrk->charmap_num;
}

DT16_ushort DT_Glyphidx2Unicode(DT_Handle hnd, DT16_ushort idx)
{
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return 0;

	if( gEnbale_DT_Charmap ){
	  if(!pdtfwrk->charmap){
		if(makeCharmap(pdtfwrk)<0){
			return 0;
		}
	  }
	}else{
	  return 0;
	}

	if(idx < pdtfwrk->charmap_num){
		return pdtfwrk->charmap[ idx ];
	} else 
		return 0;
}

DT16_ushort DT_Unicode2Glyphidx(DT_Handle hnd, DT16_ushort ucs)
{
	DT32_int start, now, end;
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return 0;

	if( gEnbale_DT_Charmap ){
	  if(!pdtfwrk->charmap){
		if(makeCharmap(pdtfwrk)<0){
			return 0;
		}
	  }
	}else{
	  return 0;
	}

	start = 0;
	end = pdtfwrk->charmap_num - 1;

	while(start <= end)
	{
		now = (end+start)/2;

		if(pdtfwrk->charmap[now] == ucs)
			return now;

		if(ucs < pdtfwrk->charmap[now]){
			end = now-1;
		}else{
			start = now+1;
			now++;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------*/
#if (1==DT_OPENVG_ENABLED)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// functions for DT_RasterOVG()

/*---------------------------------------------------------------------------*/
/* Distinguish if the (xpos, ypos) inside the specified rect(rt). Its origin(0,0) is left-top. */
/* 0: not inside; 1: inside */
DT32_int isInsideRect(DT16_short xpos, DT16_short ypos, DT_RECT *rt)
{
	DT32_int xin=0, yin=0;
	DT32_int x0, y0, w, h;

DBG_MSG_SHOW_FUNC_NAME();

	x0 = rt->xy.x;
	y0 = rt->xy.y;
	w  = rt->hw.vx;
	h  = rt->hw.vy;
	if(xpos>x0 && xpos<x0+w)
		xin = 1;
	if(ypos>y0 && ypos<y0+h)
		yin = 1;
	return (xin&yin);
}

/*---------------------------------------------------------------------------*/
/* append outline path data to VGPath of glyphs -- left-top origin coordinate*/
/* Return Value: <0:error; >=0:DT_SUCCESS									 */
DT32_int AppendPathDataLT(pDT_Fontwrk pdtfwrk, VGPath vgpath, VGfloat szX, VGfloat szY, DT16_short *olbuf, DT32_long olsize, DT32_int method, DT_RECT *rt, VGfloat ori[2])
{
	VGubyte *pathSegs=NULL;
	VGfloat *pathData=NULL;
//	DT_void  *ptr=NULL;

	DT8_uchar  *p;
	DT32_ulong tmp;
	DT16_short *path, *last, op;
	DT32_int opCnt, xyCnt, opIdx, xyIdx;
	DT32_int nodraw=0;
//	DT32_uint nSegsz=0, nDatasz=0;

	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pmgrwrk || !pmgrwrk->tempbuf){
		return DT_TEMP_BUFFER_ERR;
	}

//	nSegsz = DLO_MAX_OUL_SIZE_PER_GLYPH/sizeof(DT16_short)*sizeof(VGubyte);
//	nDatasz = DLO_MAX_OUL_SIZE_PER_GLYPH/sizeof(DT16_short)*sizeof(VGfloat);
	pathSegs = (VGubyte*) pmgrwrk->tempbuf;
	//p = (DT8_uchar*)pmgrwrk->tempbuf + pmgrwrk->tmpbufsize/4;	// Assume 1/4 for op, 3/4 for xy data.
																// Jacky_20110615: Don't change the portion of 1/4, issue of 4 bytes(VGfloat) alignment
																// FIXME: don't know if this works on a 2bytes aligned system (ex:RISC, MIPS cpu)
	p = (DT8_uchar*)pmgrwrk->tempbuf + gDT_MAX_SEGS_PER_GLYPH;
	tmp = ((DT32_ulong)p) & (sizeof(VGfloat)-1);
	if( tmp )													// try to compensate for bytes aligned.
	{
		p += sizeof(VGfloat) - tmp;
	}
	pathData = (VGfloat*)p;


//	Modified_By_Jacky_20101213: use tempbuf of font manager. No need to allocate a new one.
//	nSegsz = DLO_MAX_OUL_SIZE_PER_GLYPH/sizeof(DT16_short)*sizeof(VGubyte); //olsize*sizeof(VGubyte)/4;	/* Assume there are olsize/4 segs. */
//	pathSegs = (VGubyte*)DT_malloc(DT_ALLOC_SIZE(nSegsz));
//	if(!pathSegs)
//		return DT_NOT_ENOUGH_BUFFER;
//	
//	nDatasz = DLO_MAX_OUL_SIZE_PER_GLYPH/sizeof(DT16_short)*sizeof(VGfloat);//olsize*sizeof(VGfloat)/2;	/* Assume there are olsize/2 points. */
//	pathData = (VGfloat*)DT_malloc(DT_ALLOC_SIZE(nDatasz));
//	if(!pathData)
//		return DT_NOT_ENOUGH_BUFFER;

    path = olbuf;
    last = path + olsize;

     while (path < last)
	 {
      // Get Contour Path 
      opCnt = *path++;
      xyCnt = *path++;

#if 0   // What you have to do is enlarging the tempbuf of pmgrwrk, not re-allocating here.         
//	  if(opCnt*sizeof(VGubyte) > nSegsz){
//		ptr = DT_realloc(pathSegs, DT_ALLOC_SIZE(opCnt*sizeof(VGubyte)));
//		if(!ptr){
//			if(pathSegs)	DT_free(pathSegs);
//			return DT_NOT_ENOUGH_BUFFER;
//		}else{
//			pathSegs = (VGubyte*)ptr;
//			nSegsz = opCnt*sizeof(VGubyte);
//			ptr = NULL;
//		}
//	  }
//	  if(xyCnt*sizeof(VGfloat)*2 > nDatasz){
//		ptr = DT_realloc(pathData, DT_ALLOC_SIZE(xyCnt*sizeof(VGfloat)*2));
//		if(!ptr){
//			if(pathData)	DT_free(pathData);
//			return DT_NOT_ENOUGH_BUFFER;
//		}else{
//			pathData = (VGfloat*)ptr;
//			nDatasz  = xyCnt*sizeof(VGfloat)*2;
//			ptr = NULL;
//		}
//	  }
#endif
      // Convert each segment
      for (opIdx=xyIdx=0; opIdx<opCnt; opIdx++)
      {
        op = *path++;
        switch (op)
        {
        case DLO_MOVETO:
		  if(DLO_AREA_NOT_DRAW==method){
			nodraw = isInsideRect(*path,*(path+1),rt);
		  }
		  if(!nodraw){
            pathSegs[opIdx] = VG_MOVE_TO_ABS;
            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[1] + /*szY - */(VGfloat)(*path++) * szY / gDT_FONT_EMSIZE;
		  }else{
			//skip the value, not recorded.
			*path++;
			*path++;
		  }
          break;

        case DLO_LINETO:
		  if(!nodraw){
            pathSegs[opIdx] = VG_LINE_TO_ABS;
            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[1] + /*szY - */(VGfloat)(*path++) * szY / gDT_FONT_EMSIZE;
		  }else{
			*path++;
			*path++;
		  }
          break;

        case DLO_BEZIERTO:
		  if(!nodraw){
            pathSegs[opIdx] = VG_QUAD_TO_ABS;
            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[1] + /*szY - */(VGfloat)(*path++) * szY / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[1] + /*szY - */(VGfloat)(*path++) * szY / gDT_FONT_EMSIZE;
		  }else{
			  *path++;
			  *path++;
			  *path++;
			  *path++;
		  }
          break;

        case DLO_CLOSEPATH:
		  if(!nodraw){
            pathSegs[opIdx] = VG_CLOSE_PATH;
            vgAppendPathData(vgpath, opCnt, pathSegs, pathData);
		  }else{
			nodraw = 0;
		  }
          break;
        }
      }
	}
	 
//	if (pathSegs) DT_free(pathSegs);
//	if (pathData) DT_free(pathData);
	return DT_SUCCESS;
}

/*---------------------------------------------------------------------------*/
/* append outline path data to VGPath of glyphs -- left-bottom origin coordinate*/
/* Return Value: <0:error; >=0:DT_SUCCESS										*/
DT32_int AppendPathDataLB(pDT_Fontwrk pdtfwrk, VGPath vgpath, VGfloat szX, VGfloat szY, DT16_short *olbuf, DT32_long olsize, DT32_int method, DT_RECT *rt, VGfloat ori[2])
{
	VGubyte *pathSegs=NULL;
	VGfloat *pathData=NULL;
//	DT_void *ptr=NULL;

	DT8_uchar  *p;
	DT32_ulong tmp;
	DT16_short *path, *last, op;
	DT32_int opCnt, xyCnt, opIdx, xyIdx;
	DT32_int nodraw=0;
//	DT32_uint nSegsz=0, nDatasz=0;

	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pmgrwrk || !pmgrwrk->tempbuf){
		return DT_TEMP_BUFFER_ERR;
	}

//	nSegsz = DLO_MAX_OUL_SIZE_PER_GLYPH/sizeof(DT16_short)*sizeof(VGubyte);
//	nDatasz = DLO_MAX_OUL_SIZE_PER_GLYPH/sizeof(DT16_short)*sizeof(VGfloat);
	pathSegs = (VGubyte*) pmgrwrk->tempbuf;
	//p = (DT8_uchar*)pmgrwrk->tempbuf + pmgrwrk->tmpbufsize/4;	// Assume 1/4 for op, 3/4 for xy data.
																// Jacky_20110615: Don't change the portion of 1/4, issue of 4 bytes(VGfloat) alignment
																// FIXME: don't know if this works on a 2bytes aligned system (ex:RISC, MIPS cpu)
	p = (DT8_uchar*)pmgrwrk->tempbuf + gDT_MAX_SEGS_PER_GLYPH;
	tmp = ((DT32_ulong)p) & (sizeof(VGfloat)-1);
	if( tmp )													// try to compensate for bytes aligned.
	{
		p += sizeof(VGfloat) - tmp;
	}
	pathData = (VGfloat*)p;

//	Modified_By_Jacky_20101213: use tempbuf of font manager. No need to allocate a new one.
//	nSegsz = DLO_MAX_OUL_SIZE_PER_GLYPH/sizeof(DT16_short)*sizeof(VGubyte);//olsize*sizeof(VGubyte)/4;	/* Assume there are olsize/4 segs. */
//	pathSegs = (VGubyte*)DT_malloc(DT_ALLOC_SIZE(nSegsz));	
//	if(!pathSegs)
//		return DT_NOT_ENOUGH_BUFFER;
//	
//	nDatasz = DLO_MAX_OUL_SIZE_PER_GLYPH/sizeof(DT16_short)*sizeof(VGfloat);//olsize*sizeof(VGfloat)/2;	/* Assum there are olsize/2 points. */
//	pathData = (VGfloat*)DT_malloc(DT_ALLOC_SIZE(nDatasz));

	if(!pathData)
		return DT_NOT_ENOUGH_BUFFER;
	
    path = olbuf;
    last = path + olsize;

     while (path < last)
	 {
      // Get Contour Path 
      opCnt = *path++;
      xyCnt = *path++;

#if 0   // What you have to do is enlarging the tempbuf of pmgrwrk, not re-allocating here.   
//	  if(opCnt*sizeof(VGubyte) > nSegsz){
//		ptr = DT_realloc(pathSegs, DT_ALLOC_SIZE(opCnt*sizeof(VGubyte)));
//		if(!ptr){
//			if(pathSegs)	DT_free(pathSegs);
//			return DT_NOT_ENOUGH_BUFFER;
//		}else{
//			pathSegs = (VGubyte*)ptr;
//			nSegsz = opCnt*sizeof(VGubyte);
//			ptr = NULL;
//		}
//	  }
//	  if(xyCnt*sizeof(VGfloat)*2 > nDatasz){
//		ptr = DT_realloc(pathData, DT_ALLOC_SIZE(xyCnt*sizeof(VGfloat)*2));
//		if(!ptr){
//			if(pathData)	DT_free(pathData);
//			return DT_NOT_ENOUGH_BUFFER;
//		}else{
//			pathData = (VGfloat*)ptr;
//			nDatasz  = xyCnt*sizeof(VGfloat)*2;
//			ptr = NULL;
//		}
//	  }
#endif
      // Convert each segment
      for (opIdx=xyIdx=0; opIdx<opCnt; opIdx++)
      {
        op = *path++;
        switch (op)
        {
        case DLO_MOVETO:
		  if(DLO_AREA_NOT_DRAW==method){
			nodraw = isInsideRect(*path,*(path+1),rt);
		  }
		  if(!nodraw){
            pathSegs[opIdx] = VG_MOVE_TO_ABS;
            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[1] + szY - (VGfloat)(*path++) * szY / gDT_FONT_EMSIZE;
		  }else{
			//skip the value, not recorded.
			*path++;
			*path++;
		  }
          break;

        case DLO_LINETO:
		  if(!nodraw){
            pathSegs[opIdx] = VG_LINE_TO_ABS;
            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[1] + szY - (VGfloat)(*path++) * szY / gDT_FONT_EMSIZE;
		  }else{
			*path++;
			*path++;
		  }
          break;

        case DLO_BEZIERTO:
		  if(!nodraw){
            pathSegs[opIdx] = VG_QUAD_TO_ABS;
            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[1] + szY - (VGfloat)(*path++) * szY / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / gDT_FONT_EMSIZE;
            pathData[xyIdx++] = ori[1] + szY - (VGfloat)(*path++) * szY / gDT_FONT_EMSIZE;
		  }else{
			  *path++;
			  *path++;
			  *path++;
			  *path++;
		  }
          break;

        case DLO_CLOSEPATH:
		  if(!nodraw){
            pathSegs[opIdx] = VG_CLOSE_PATH;
            vgAppendPathData(vgpath, opCnt, pathSegs, pathData);
		  }else{
			nodraw = 0;
		  }
          break;
        }
      }
	}
	 
//	if (pathSegs) DT_free(pathSegs);
//	if (pathData) DT_free(pathData);
	return DT_SUCCESS;
}

/*---------------------------------------------------------------------------*/
/* use a rectangle to set(fill) the mask. it's not used now.	*/
DT_void MakeClearMaskPath(VGPath maskpath, DT_float origin[2], DT32_int width, DT32_int height, VGbitfield paintModes)
{
	DT32_int strw=0;	/* stroke width */
//	VGPath maskpath;	/* use a rect path to cover the region glyphs will be drawn. */
	VGubyte Segs[6]={VG_MOVE_TO_ABS,
					 VG_LINE_TO_ABS,
					 VG_LINE_TO_ABS,
					 VG_LINE_TO_ABS,
					 VG_LINE_TO_ABS,
					 VG_CLOSE_PATH};
	VGfloat Coords_F[10];
	VGfloat w, h;

DBG_MSG_SHOW_FUNC_NAME();

	w = (VGfloat)width;
	h = (VGfloat)height;

	if(paintModes & VG_STROKE_PATH){
		strw = vgGeti(VG_STROKE_LINE_WIDTH);
		w += (VGfloat)strw;
		h += (VGfloat)strw;
	}

		Coords_F[0] = origin[0];	/* left-bottom (origin) */
		Coords_F[1] = origin[1];
		Coords_F[2] = origin[0];	/* left-top */
		Coords_F[3] = origin[1]+h;
		Coords_F[4] = origin[0]+w;	/* right-top */
		Coords_F[5] = origin[1]+h;
		Coords_F[6] = origin[0]+w;	/* right-bottom */
		Coords_F[7] = origin[1];
		Coords_F[8] = origin[0];	/* left-bottom (origin) */
		Coords_F[9] = origin[1];
		vgAppendPathData(maskpath, 6, Segs, (VGfloat*)Coords_F);		
	vgRemovePathCapabilities(maskpath, VG_PATH_CAPABILITY_APPEND_TO);
}

/*---------------------------------------------------------------------------*/
/* Convert color to VGuint */
VGuint convColorOVG(DT_RGBA color)
{
	VGuint r,g,b,a;

DBG_MSG_SHOW_FUNC_NAME();

	r = (VGuint)color.r<<24;
	g = (VGuint)color.g<<16;
	b = (VGuint)color.b<<8;
	a = (VGuint)color.a;
	return  (VGuint) r | g | b | a;
}

VGboolean isAlphaFill(VGPaint fillpaint)
{
	#define CLAMP(x) ((x) < 0.0f ? 0.0f : ((x) > 1.0f ? 1.0f : (x)))
	VGfloat rgba_f[4];
	DT32_uint red, green, blue, alpha;
	vgGetParameterfv(fillpaint, VG_PAINT_COLOR, 4, rgba_f);
	/*
	* Clamp color and alpha values from vgGetParameterfv to the
	* [0, 1] range, scale to 8 bits, and round to integer.
	*/
	red		= (DT32_uint)(CLAMP(rgba_f[0])*255.0f + 0.5f);
	green	= (DT32_uint)(CLAMP(rgba_f[1])*255.0f + 0.5f);
	blue	= (DT32_uint)(CLAMP(rgba_f[2])*255.0f + 0.5f);
	alpha	= (DT32_uint)(CLAMP(rgba_f[3])*255.0f + 0.5f);
	return (VGboolean)(255 != alpha);
}

/*---------------------------------------------------------------------------*/
/* Make the fillpaint & strokepaint			*/
/* Be care of the color within the paints	*/
DT32_int makePaint(	pDT_Fontwrk pdtfwrk, DT_RGBA *fcolor, DT_RGBA *incolor,
					VGPaint *fillp, VGPaint *strokep, VGbitfield *paintmodes, DT32_int *stkw)
{
	DT32_int f_edge, w_edge;
	DT32_int bUseMask=0, bFill=1, bStroke=0;
	VGuint	fillcolor=0x000000FF, stkcolor=0;

DBG_MSG_SHOW_FUNC_NAME();

	f_edge = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_F_EDGE);
	w_edge = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_W_EDGE);

	*stkw = 0;		*paintmodes = 0;
	if( f_edge==DT_STYLE_OUTLINE && w_edge>0){
		if(incolor){
			bFill = 1;	fillcolor = convColorOVG(*incolor);	//(VGuint) DT_convColor(*incolor);
			bStroke=1;	stkcolor  = convColorOVG(*fcolor);	//(VGuint) DT_convColor(*fcolor);
			*stkw = w_edge;
		}else{
			bFill = 0;	fillcolor = convColorOVG(*fcolor);	//(VGuint) DT_convColor(*fcolor);
			bStroke=1;	stkcolor = convColorOVG(*fcolor);	//(VGuint) DT_convColor(*fcolor);
			*stkw = w_edge;
		}
	}else if( f_edge==DT_STYLE_BOLD && w_edge>0){
		bFill = 1;	fillcolor = convColorOVG(*fcolor);	//(VGuint) DT_convColor(*fcolor);
		bStroke=1;	stkcolor  = convColorOVG(*fcolor);	//(VGuint) DT_convColor(*fcolor);
		*stkw = w_edge;
	}else{	/* Normal: DT_STYLE_NORMAL */
		bFill = 1;	fillcolor = convColorOVG(*fcolor);	//(VGuint) DT_convColor(*fcolor);
		bStroke=0;	stkcolor = convColorOVG(*fcolor);	//(VGuint) DT_convColor(*fcolor);
	}

	*fillp = vgCreatePaint();
	vgSetParameteri(*fillp, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetColor(*fillp, fillcolor);
	//vgSetParameterfv(*fillp, VG_PAINT_COLOR, 4, fillColor);
	vgSetPaint(*fillp,VG_FILL_PATH);
	if(bFill)
		*paintmodes |= VG_FILL_PATH;

	*strokep = vgCreatePaint();
	vgSetParameteri(*strokep, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetColor(*strokep, stkcolor);
	//vgSetParameterfv(*strokep, VG_PAINT_COLOR, 4, strokeColor);
	vgSetPaint(*strokep,VG_STROKE_PATH);
	vgSeti(VG_STROKE_LINE_WIDTH,*stkw);
	if(bStroke)
		*paintmodes |= VG_STROKE_PATH;

	if(bStroke && isAlphaFill(*fillp))		//if(bStroke && (fillcolor&0x000000FF)!=0xFF)
		bUseMask = 1;

	return bUseMask;
}

/*---------------------------------------------------------------------------*/
DT_void dePaint(VGPaint *fillp, VGPaint *strokep)
{
DBG_MSG_SHOW_FUNC_NAME();

  if(*fillp)	vgDestroyPaint(*fillp);
  if(*strokep)	vgDestroyPaint(*strokep);
}

/*---------------------------------------------------------------------------*/
/* */
DT32_int makeGlyphsPath(pDT_Fontwrk pdtfwrk, pDT_OulBuf oulbuf, VGfloat szX, VGfloat szY, VGfloat origin[2])
{
	VGfloat ori[2] = {0.0f, 0.0f};
	DT32_int ret, i, bufread, coords=DT_COORD_LEFT_BOT;
	DT16_short *pathbuf;

DBG_MSG_SHOW_FUNC_NAME();

	coords = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_VG_COORD);

	/* Create Path */
	if(!pdtfwrk->myglyphpath){
	  pdtfwrk->myglyphpath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 
							  1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
	  if(pdtfwrk->myglyphpath == VG_INVALID_HANDLE)
		return DT_VG_CREATEPATH_ERR;
	}else{
	  vgClearPath(pdtfwrk->myglyphpath,VG_PATH_CAPABILITY_ALL);
	}
	ori[0] = origin[0];
	ori[1] = origin[1];

	/* Parse each glyph's outline data to the path */
	bufread = 0;
	pathbuf = (DT16_short*) oulbuf->olbuf;
	for(i=0;i<oulbuf->gcnt;i++){
		if(bufread+oulbuf->olsizes[i] > oulbuf->olbufsize)
			break;

		ori[0] = (VGfloat)oulbuf->carets[i].oripos.x * szX / gDT_FONT_EMSIZE;
		if(coords==DT_COORD_LEFT_TOP){
			ori[1] = (VGfloat)oulbuf->carets[i].oripos.y * szY / gDT_FONT_EMSIZE;
		}else{
			ori[1] = 0 - (VGfloat)oulbuf->carets[i].oripos.y * szY / gDT_FONT_EMSIZE;
		}
		if(oulbuf->olsizes[i]){
		  if(coords==DT_COORD_LEFT_TOP){
			ret = AppendPathDataLT(pdtfwrk,pdtfwrk->myglyphpath,(VGfloat)szX,(VGfloat)szY,
								pathbuf+bufread,oulbuf->olsizes[i],
								oulbuf->carets[i].drawmethod, &oulbuf->carets[i].dmrect, ori);
		  }else{
			ret = AppendPathDataLB(pdtfwrk,pdtfwrk->myglyphpath,(VGfloat)szX,(VGfloat)szY,
								pathbuf+bufread,oulbuf->olsizes[i],
								oulbuf->carets[i].drawmethod, &oulbuf->carets[i].dmrect, ori);
		  }
		  if(ret!=DT_SUCCESS){
			return ret;
		  }
		}
		bufread += oulbuf->olsizes[i];
	}

	return bufread;
}

/*---------------------------------------------------------------------------*/
/* Return Value: 0:DT_SUCCESS; <0:error										*/
DT32_int drawUnderline(pDT_Fontwrk pdtfwrk, VGfloat origin[2], DT_StrInfo *info)
{
	DT32_int szX, szY, p_ul, w_ul, e_ul, coordstyle;
	VGfloat ulpos;
	VGint  stkw;
	VGPath underline;
	VGubyte Segs[3];
	VGfloat Coords[3];

DBG_MSG_SHOW_FUNC_NAME();

	szX  = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_SIZEX);
	szY  = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_SIZEY);
	p_ul = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_P_UNDERLINE);
	w_ul = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_W_UNDERLINE);
	e_ul = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_E_UNDERLINE);
	coordstyle = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_VG_COORD);

	if(w_ul<=0)
		return DT_SUCCESS;
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	underline = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 
							  1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
	if(underline == VG_INVALID_HANDLE)
		return DT_VG_CREATEPATH_ERR;

	if(DT_GetFontStyle(pdtfwrk,DT_FSTYLE_VERT)){
		ulpos = (VGfloat)(p_ul+(VGfloat)w_ul/2);	// DT_COORD_LEFT_TOP also the same.
		Segs[0] = VG_MOVE_TO_ABS;
		Coords[0] = origin[0] + ulpos;
		Coords[1] = origin[1] + szY;
		Segs[1] = VG_VLINE_TO_REL;
		Coords[2] = -(VGfloat)info->height;
		Segs[2] = VG_CLOSE_PATH;
	}else{
		if(coordstyle==DT_COORD_LEFT_TOP){
		  ulpos = (VGfloat)szY-(p_ul+(VGfloat)w_ul/2);
		}else{
		  ulpos = (VGfloat)(p_ul+(VGfloat)w_ul/2);
		}
		Segs[0] = VG_MOVE_TO_ABS;
		Coords[0] = origin[0];
		Coords[1] = origin[1] + ulpos;
		Segs[1] = VG_HLINE_TO_REL;
		Coords[2] = (VGfloat)info->width;			// DT_COORD_LEFT_TOP also the same.
		Segs[2] = VG_CLOSE_PATH;
	}


	vgAppendPathData(underline, 3, Segs, (VGfloat*)Coords);		
	vgRemovePathCapabilities(underline, VG_PATH_CAPABILITY_APPEND_TO);

	
	stkw = vgGeti(VG_STROKE_LINE_WIDTH);	/* keep stkw */
	
	vgSeti(VG_STROKE_LINE_WIDTH,w_ul);
	vgDrawPath(underline,VG_STROKE_PATH);
	vgSeti(VG_STROKE_LINE_WIDTH,stkw);

	return DT_SUCCESS;
}

/*---------------------------------------------------------------------------*/
/* Return Value: 0:DT_SUCCESS; <0:error										*/
DT32_int drawStrike(pDT_Fontwrk pdtfwrk, VGfloat origin[2], DT_StrInfo *info)
{
	DT32_int szX, szY, p_sk, w_sk, e_sk, coordstyle;
	VGfloat skpos;
	VGint  stkw;
	VGPath strike;
	VGubyte Segs[3];
	VGfloat Coords[3];

DBG_MSG_SHOW_FUNC_NAME();

	szX  = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_SIZEX);
	szY  = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_SIZEY);
	p_sk = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_P_STRIKE);
	w_sk = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_W_STRIKE);
	e_sk = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_E_STRIKE);
	coordstyle = DT_GetFontStyle(pdtfwrk,DT_FSTYLE_VG_COORD);

	if(w_sk<=0)
		return DT_SUCCESS;
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);

	strike = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 
							  1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
	if(strike == VG_INVALID_HANDLE)
		return DT_VG_CREATEPATH_ERR;

	if(DT_GetFontStyle(pdtfwrk,DT_FSTYLE_VERT)){
		skpos = (VGfloat)(p_sk+(VGfloat)w_sk/2);	// DT_COORD_LEFT_TOP also the same.
		Segs[0] = VG_MOVE_TO_ABS;
		Coords[0] = origin[0] + skpos;
		Coords[1] = origin[1] + szY;
		Segs[1] = VG_VLINE_TO_REL;
		Coords[2] = -(VGfloat)info->height;
		Segs[2] = VG_CLOSE_PATH;
	}else{
		if(coordstyle==DT_COORD_LEFT_TOP){
		  skpos = (VGfloat)szY-(p_sk+(VGfloat)w_sk/2);
		}else{
		  skpos = (VGfloat)(p_sk+(VGfloat)w_sk/2);
		}
		Segs[0] = VG_MOVE_TO_ABS;
		Coords[0] = origin[0];
		Coords[1] = origin[1] + skpos;
		Segs[1] = VG_HLINE_TO_REL;
		Coords[2] = (VGfloat)info->width;			// DT_COORD_LEFT_TOP also the same.
		Segs[2] = VG_CLOSE_PATH;
	}


	vgAppendPathData(strike, 3, Segs, (VGfloat*)Coords);		
	vgRemovePathCapabilities(strike, VG_PATH_CAPABILITY_APPEND_TO);

	
	stkw = vgGeti(VG_STROKE_LINE_WIDTH);	/* keep stkw */
	
	vgSeti(VG_STROKE_LINE_WIDTH,w_sk);
	vgDrawPath(strike,VG_STROKE_PATH);
	vgSeti(VG_STROKE_LINE_WIDTH,stkw);

	return DT_SUCCESS;
}

/*---------------------------------------------------------------------------*/
/* Get the sum of advanced width of each glyphs								*/
DT32_int DT_GetStringWidth(DT_Handle hnd, DT_OulBuf *laybuf, DT32_int sizeX, DT32_int sizeY)
{
	DT32_int dif = gDT_FONT_EMSIZE-1;

DBG_MSG_SHOW_FUNC_NAME();

	return (laybuf->eswidth*sizeX+dif)/gDT_FONT_EMSIZE;
}

/*---------------------------------------------------------------------------*/
/* Get the height of glyphs	(the height of the line)						*/
DT32_int DT_GetStringHeight(DT_Handle hnd, DT_OulBuf *laybuf, DT32_int sizeX, DT32_int sizeY)
{
	DT32_int dif = gDT_FONT_EMSIZE-1;

DBG_MSG_SHOW_FUNC_NAME();

	return (laybuf->esheight*sizeY+dif)/gDT_FONT_EMSIZE;
}

/*---------------------------------------------------------------------------*/
/* Using mask to avoid the un-expected result while the color's alpha channel isn't 1.	*/
/* Return Value: 0:DT_SUCCESS; <0:error													*/
DT32_int DT_VGprepareMask(/*pDT_Fontwrk pdtfwrk*/DT_void *hnd, /*pDT_OulBuf oulbuf*/DT_void *buf,
						  DT32_int w, DT32_int h, DT32_int stkw, VGfloat origin[2])
{
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk)hnd;
	pDT_OulBuf	oulbuf	= (pDT_OulBuf)buf;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;
	if(!oulbuf)
		return DT_VG_BAD_OULBUF;

		/* Create mytranspath for masking. */
		if(!pdtfwrk->mytranspath){
		  pdtfwrk->mytranspath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
		  if(pdtfwrk->mytranspath == VG_INVALID_HANDLE)
			return DT_VG_CREATEPATH_ERR;
		}else{
		  vgClearPath(pdtfwrk->mytranspath,VG_PATH_CAPABILITY_ALL);
		}

		/* Create mymaskpath for masking. */
		if(!pdtfwrk->mymaskpath){
		  pdtfwrk->mymaskpath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
		  if(pdtfwrk->mymaskpath == VG_INVALID_HANDLE)
			return DT_VG_CREATEPATH_ERR;
		}else{
		  vgClearPath(pdtfwrk->mymaskpath,VG_PATH_CAPABILITY_ALL);
		}

		/* Set matrix mode to use the path matrix */
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);			/* Set the matrix mode. */

		/* Fill the drawing area's mask before making the mask */
#if 0 /* Panasonic removed vgMasking for GV200 */
		vgSeti(VG_MASKING, VG_TRUE);
		vgMask(VG_INVALID_HANDLE,VG_FILL_MASK,(VGint)origin[0],(VGint)origin[1],w+stkw,h+stkw);
		vgSeti(VG_MASKING, VG_FALSE);
#endif
		
		/* Render to mask. */	
		vgTranslate(origin[0]/2, origin[1]/2);							/* It have to be so to get the right result. */
		vgTransformPath(pdtfwrk->mytranspath, pdtfwrk->myglyphpath);	/* transform myglyphpath to mytranspath */	
#if 0 /* Panasonic removed vgMasking for GV200 */
		vgRenderToMask(pdtfwrk->mytranspath, VG_FILL_PATH, VG_SUBTRACT_MASK);	/* render to mask. */	
#endif
		vgTranslate(-origin[0]/2, -origin[1]/2);						/* Same as above. because origin had been offseted. */
		return DT_SUCCESS;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* This function is valid only if mode=DT_OUTLINE_MODE when DT_CreateFont() */
/* Return Value: 0:DT_SUCCESS; <0:error										*/
//DT32_int DT_RasterOVG_OLD(DT_Handle hnd,
//			  DT16_ushort*	ucs_str,		/* the string to be drawn	*/
//			  DT32_int		ucs_cnt,		/* count of ucs_str			*/
//			  VGfloat 		originx,		/* origin x					*/
//			  VGfloat		originy,		/* origin y					*/
//			  DT_RGBA		*fcolor,		/* font color, fill color	*/
//			  DT_RGBA		*incolor,		/* inner color when DT_STYLE_OUTLINE, set NULL as no incolor */
//              VGboolean		allowAutoHinting,/* auto hinting by openVG	*/
//  			  DT_StrInfo	*info			/* the string info when return.	*/
//			  //DT32_int		isClipping,		/* 1:clipping; 0:no clipping*/
//			  //DT_RECT		*rtClipping,	/* set the clipping rect  	*/
//			  //DT32_int	flag,			/* clipping rect align flag		*/
//			)
//{
//	VGPaint		fillpaint=0, strokepaint=0;
//	VGbitfield	paintModes;
//	VGint		matrixmode, blendmode, fillrule, joinstyle;
//	VGfloat		origin[2]={0.0f, 0.0f};
//	VGfloat		ori[2]={0.0f, 0.0f};
//	VGfloat		awv[2]={0.0f, 0.0f};
//	VGfloat		szX, szY;
//	DT32_int	bUseMask=0;
//
//	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;
//	pDT_OulBuf	oulbuf=NULL;
//
//	DT32_int ret, rtval=DT_SUCCESS;
//	DT32_int h, w, stkw;	/* drawing width, height, stroke width */
//
//DBG_MSG_SHOW_FUNC_NAME();
//	
//	if(!pdtfwrk)
//		return DT_BAD_FONT_HANDLE;
//
//	if(pdtfwrk->engtype!=DLO_ENG_DCWOPENVG){
//		return DT_CREATEFONT_MODE_ERR;
//	}
//
//	/* Get Outline data here */
//	ret = DT_RasterOUL(hnd, ucs_str, ucs_cnt, DT_GET_INFO | DT_DRAW, &oulbuf);
//	rtval = convReturnValue(ret);
//	if(rtval!=DT_SUCCESS){
//		ret = DT_RasterOUL(hnd, ucs_str, ucs_cnt, DT_RELEASE, &oulbuf);
//		return rtval;
//	}
//
//	/* Set required font style */
//	origin[0]=(VGfloat)originx;	origin[1]=(VGfloat)originy;
//	szX = (VGfloat)DT_GetFontStyle(hnd,DT_FSTYLE_SIZEX);
//	szY = (VGfloat)DT_GetFontStyle(hnd,DT_FSTYLE_SIZEY);
//	// italic
//
//	/* Create VGFont if need */
//	if(!pdtfwrk->myvgfont){
//		pdtfwrk->myvgfont = vgCreateFont(oulbuf->gcnt);
//		if(pdtfwrk->myvgfont == VG_INVALID_HANDLE)
//		  return DT_VG_CREATEFONT_ERR;
//	}
//
//	/* Keep some info */
//	matrixmode = vgGeti(VG_MATRIX_MODE);
//	blendmode  = vgGeti(VG_BLEND_MODE);
//	fillrule = vgGeti(VG_FILL_RULE);
//	joinstyle= vgGeti(VG_STROKE_JOIN_STYLE);
//
//	/* Set some attributes to new value. */
//	vgSeti(VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE);
//	vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
//	vgSeti(VG_FILL_RULE, VG_NON_ZERO);	/* Set non_zero as the fill rule to avoid the problem of intersection. */
//	vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);	/* Set ROUND-JOIN to avoid un-usual protruding problems while stroking. */
//
//	ret = makeGlyphsPath(pdtfwrk,oulbuf,szX,szY,origin);
//	if( ret<=0 ){	/* Nothing in the path, close it. */
//		rtval = ret;
//		goto DT_SET_VG_INFO_BACK;
//	}
//	
//	/* Remove this Capability of path will be faster. */
//	vgRemovePathCapabilities(pdtfwrk->myglyphpath, VG_PATH_CAPABILITY_APPEND_TO);
//
//	/* Get advanced width (escapement) */
//	awv[0] = (VGfloat)oulbuf->eswidth;
//	awv[1] = (VGfloat)oulbuf->esheight;
//
//	ori[0] = 0.0f;
//	ori[1] = 0.0f;
//	/* Set all path to the code DT_VG_FONTCODE <== you can modify this code. */
//	vgSetGlyphToPath(pdtfwrk->myvgfont, (VGuint)DT_VG_FONTCODE/*0x0E3B*/, pdtfwrk->myglyphpath, VG_TRUE, ori, awv);
//
//	vgSetfv(VG_GLYPH_ORIGIN,2,(VGfloat*)origin);
//
//	/* Prepare Paints, get paintModex, stroke width(stkw), and decide if mask is needed. */
//	bUseMask = makePaint(pdtfwrk,fcolor,incolor,&fillpaint,&strokepaint,&paintModes,&stkw);
//	w = DT_GetStringWidth(pdtfwrk,oulbuf,(DT32_int)szX,(DT32_int)szY);
//	h = DT_GetStringHeight(pdtfwrk,oulbuf,(DT32_int)szX,(DT32_int)szY);
//
//	/* Prepare a mask for stroke path drawing -- avoid alpha channel problem. */
//	if(bUseMask){
//	    /* Prepare the mask -- the inner part of each glyphs */
//		ret = DT_VGprepareMask(pdtfwrk, oulbuf, w, h, stkw, origin);
//		if(ret<0){
//			rtval = ret;
//			goto DT_SET_VG_INFO_BACK;
//		}
//		
//		/* ensure the matrix mode is glyph mode. */
//		vgSeti(VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE);
//
//		/* stroking glyph. */
//		vgSeti(VG_MASKING, VG_TRUE);
//		vgDrawGlyph(pdtfwrk->myvgfont,(VGuint)DT_VG_FONTCODE/*0x0E3B*/,VG_STROKE_PATH,allowAutoHinting);
//		vgSeti(VG_MASKING, VG_FALSE);
//
//		/* fill mask back to normal. */
//		vgSeti(VG_MASKING, VG_TRUE);
//		vgMask(VG_INVALID_HANDLE,VG_FILL_MASK,(VGint)origin[0],(VGint)origin[1],w+stkw,h+stkw);
//		vgSeti(VG_MASKING, VG_FALSE);
//
//		/* If need filling glyph... */
//		vgSetfv(VG_GLYPH_ORIGIN, 2, origin);
//		if(paintModes&VG_FILL_PATH)
//			vgDrawGlyph(pdtfwrk->myvgfont,(VGuint)DT_VG_FONTCODE/*0x0E3B*/,VG_FILL_PATH,allowAutoHinting);
//
//	}else{//bUseMask
//		if(paintModes&VG_STROKE_PATH)		/* stroke glyph */
//			vgDrawGlyph(pdtfwrk->myvgfont,(VGuint)DT_VG_FONTCODE/*0x0E3B*/,VG_STROKE_PATH,allowAutoHinting);
//
//		vgSetfv(VG_GLYPH_ORIGIN, 2, origin);
//		if(paintModes&VG_FILL_PATH)			/* fill glyph	*/
//			vgDrawGlyph(pdtfwrk->myvgfont,(VGuint)DT_VG_FONTCODE/*0x0E3B*/,VG_FILL_PATH,allowAutoHinting);
//	}// bUseMask
//		
//	vgClearGlyph(pdtfwrk->myvgfont,(VGuint)DT_VG_FONTCODE/*0x0E3B*/);
//
//	/* make DT_StrInfo for return */
//	if(info){
//		/* vgPathBounds() only return the really boundary of glyphs,				*/
//		/* the height won't be the same even szY is the same.						*/
//		/* vgPathBounds() ignores stroke parameters, and width will not include rsb.*/
//		//VGfloat minX, minY;
//		//VGfloat width, height;
//		//vgPathBounds(pdtfwrk->myglyphpath,&minX,&minY,&width,&height);
//		//vgPathTransformedBounds(pdtfwrk->myglyphpath,&minX,&minY,&width,&height);
//		info->width = w+stkw;
//		info->height= h+stkw;
//		info->gcnt  = oulbuf->gcnt;
//		DT_memcpy(info->glyphs,oulbuf->glyphs,oulbuf->gcnt*sizeof(DT16_ushort));
//	}
//
//	/* Draw Underline */
//	ret = drawUnderline(pdtfwrk,origin,info);
//	if(ret<0){
//		rtval = ret;
//		goto DT_SET_VG_INFO_BACK;
//	}
//	/* Draw Strike */
//	/* strike color is the same with innercolor. */
//	vgSetParameteri(strokepaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
//	if(incolor)
//		vgSetColor(strokepaint, convColorOVG(*incolor));
//	ret = drawStrike(pdtfwrk,origin,info);
//	if(ret<0){
//		rtval = ret;
//		goto DT_SET_VG_INFO_BACK;
//	}
//
//DT_SET_VG_INFO_BACK:
//	/* Release something */
//	dePaint(&fillpaint,&strokepaint);
//	ret = DT_RasterOUL(hnd, ucs_str, ucs_cnt, DT_RELEASE, &oulbuf);
//
//	// Set the info back
//	vgSeti(VG_MATRIX_MODE, matrixmode);
//	vgSeti(VG_BLEND_MODE, blendmode);
//	vgSeti(VG_FILL_RULE, fillrule);
//	vgSeti(VG_STROKE_JOIN_STYLE, joinstyle);
//
//	return rtval;
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* This function is valid only if mode=DT_OUTLINE_MODE when DT_CreateFont() */
/* Return Value: 0:DT_SUCCESS; <0:error										*/
DT32_int DT_RasterOVG(DT_Handle hnd,
			  DT16_ushort*	ucs_str,		/* the string to be drawn	*/
			  DT32_int		ucs_cnt,		/* count of ucs_str			*/
			  VGfloat 		originx,		/* origin x					*/
			  VGfloat		originy,		/* origin y					*/
			  DT_RGBA		*fcolor,		/* font color, fill color	*/
			  DT_RGBA		*incolor,		/* inner color when DT_STYLE_OUTLINE, set NULL as no incolor */
              VGboolean		allowAutoHinting,/* auto hinting by openVG	*//*Not used now*/
  			  DT_StrInfo	*info			/* the string info when return.	*/
			  //DT32_int		isClipping,		/* 1:clipping; 0:no clipping*/
			  //DT_RECT		*rtClipping,	/* set the clipping rect  	*/
			  //DT32_int	flag,			/* clipping rect align flag		*/
			)
{
	VGPaint		fillpaint=VG_INVALID_HANDLE, strokepaint=VG_INVALID_HANDLE;
	VGbitfield	paintModes;
	VGPath		hStrPath;
	VGint		matrixmode, blendmode, fillrule, joinstyle;
	VGfloat		matrix[9];
	DT32_int	stkw, bUseMask=0;
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk) hnd;
	DT32_int ret, rtval=DT_SUCCESS;

DBG_MSG_SHOW_FUNC_NAME();
	
	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	if(pdtfwrk->engtype!=DLO_ENG_DCWOPENVG){
		return DT_CREATEFONT_MODE_ERR;
	}

	hStrPath = VG_INVALID_HANDLE;
	ret = DT_RasterPathforOVG(pdtfwrk, ucs_str, ucs_cnt, &hStrPath, info);
	if(ret < 0){
		return ret;
	}else rtval = ret;
	/* Remove this Capability of path will be faster. */
	vgRemovePathCapabilities(hStrPath, VG_PATH_CAPABILITY_APPEND_TO);

	/* keep & set matrix mode */
	matrixmode = vgGeti(VG_MATRIX_MODE);
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	vgGetMatrix(matrix);
	vgLoadIdentity();

	
	/* Keep some info */
	blendmode  = vgGeti(VG_BLEND_MODE);
	fillrule = vgGeti(VG_FILL_RULE);
	joinstyle= vgGeti(VG_STROKE_JOIN_STYLE);

	/* Set some attributes to new value. */
	vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
	vgSeti(VG_FILL_RULE, VG_NON_ZERO);	/* Set non_zero as the fill rule to avoid the problem of intersection. */
	vgSeti(VG_STROKE_JOIN_STYLE,VG_JOIN_ROUND);	/* Set ROUND-JOIN to avoid un-usual protruding problems while stroking. */

	/* Prepare Paints, get paintModex, stroke width(stkw), and decide if mask is needed. */
	bUseMask = makePaint(pdtfwrk,fcolor,incolor,&fillpaint,&strokepaint,&paintModes,&stkw);

	vgTranslate(originx, originy);

	if(pdtfwrk->style.gen_empath == 1){
		vgScale((VGfloat)pdtfwrk->style.xsize/gDT_FONT_EMSIZE, (VGfloat)pdtfwrk->style.ysize/gDT_FONT_EMSIZE);
		vgSeti(VG_STROKE_LINE_WIDTH, stkw*gDT_FONT_EMSIZE/pdtfwrk->style.ysize);
	}

	/* Prepare a mask for stroke path drawing -- avoid alpha channel problem. */
	if(!bUseMask){
		VGboolean bFill  = paintModes&VG_FILL_PATH;
		VGboolean bStroke= paintModes&VG_STROKE_PATH;
		if(bFill && bStroke){
			vgDrawPath(hStrPath, VG_STROKE_PATH);
			vgDrawPath(hStrPath, VG_FILL_PATH);
			//vgDrawPath(path, VG_FILL_PATH | VG_STROKE_PATH);
		}else if(bFill && !bStroke)
			vgDrawPath(hStrPath, VG_FILL_PATH);
		else
			;	// do nothing ==> (bStroke && !bFill) should do mask.
	}else{
		DT_StrokeOVGPathByMask(hnd,hStrPath);		// draw stroke first.
		if(paintModes&VG_FILL_PATH)
			vgDrawPath(hStrPath,VG_FILL_PATH);
	}

//DT_SET_VG_INFO_BACK:
	/* Release something */
	dePaint(&fillpaint,&strokepaint);

	// Set the info back
	vgLoadMatrix(matrix);
	vgSeti(VG_BLEND_MODE, blendmode);
	vgSeti(VG_FILL_RULE, fillrule);
	vgSeti(VG_STROKE_JOIN_STYLE, joinstyle);
	vgSeti(VG_MATRIX_MODE, matrixmode);

	return rtval;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// functions for DT_RasterOVGPath()

/* OVG Cache */
DT16_ushort MakeOVGCacheStyleValue(DT16_ushort fid, DT16_ushort coords, DT16_ushort bidirule, DT16_ushort vert)
{
	DT16_ushort style;

DBG_MSG_SHOW_FUNC_NAME();

	/* fid */
	style = fid<<8;

	/* grade values */
	if(coords==DT_COORD_LEFT_TOP){
		style |= DT_OVGCACHE_COORDS_LEFTTOP;
	}

	/* vert */
	if(vert)
		style |= DT_OVGCACHE_VERT_FONT;

	/* bidi-rule, used only for OVGL3 cache */
	if(bidirule == DT_BIDI_DCWRULE)
		style |= DT_OVGCACHE_BIDIRULE_DCW;

	return style;
}

DT16_ushort MakeOVGCacheOthersValue(/* Defined by yourself in the future, not used now. */)
{
DBG_MSG_SHOW_FUNC_NAME();

	return 0;
}

/*---------------------------------------------------------------------------*/
/// a glyph's VGPath cache
VGPath chkL2Cache(pDT_Fontwrk pdtfwrk, DT16_ushort code)	
{
	DT16_ushort style, others, vert;
	CacheUnit *unit;	
	pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;
	
DBG_MSG_SHOW_FUNC_NAME();

	vert = (DT16_ushort)pdtfwrk->style.vert;
#ifdef DT_VERT_BY_OVG
	vert = (DT16_ushort)pwrk->vert;	// overwrite it. vert will be done by rotate by OpenVG
#endif

	// FIXME: altfont's fid won't be logged. Don't distinguish fid now.
	style = MakeOVGCacheStyleValue( (DT16_ushort)pdtfwrk->font->fid, (DT16_ushort)pdtfwrk->style.oulcoord, 
									(DT16_ushort)pdtfwrk->style.bidirule, (DT16_ushort)vert);
	others= MakeOVGCacheOthersValue();

	if(pdtfwrk->usedcacheL2){
		unit = GetFromCache(pdtfwrk->usedcacheL2, code, 0, 0, style, others);
		if(unit){
			return (VGPath) unit->extra.infoL2.hVGPath;
		}
	}
	return VG_INVALID_HANDLE;
}

DT32_int addToL2Cache(pDT_Fontwrk pdtfwrk, DT16_ushort code, VGPath glyphPath)
{
	DT16_ushort style, others, vert;
	CacheUnit cu;
	pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;

	vert = (DT16_ushort)pdtfwrk->style.vert;
#ifdef DT_VERT_BY_OVG
	vert = (DT16_ushort)pwrk->vert;	// overwrite it. vert will be done by rotate by OpenVG
#endif

	// FIXME: altfont's fid won't be logged. Don't distinguish fid now.
	style = MakeOVGCacheStyleValue( (DT16_ushort)pdtfwrk->font->fid, (DT16_ushort)pdtfwrk->style.oulcoord, 
									(DT16_ushort)pdtfwrk->style.bidirule, (DT16_ushort)vert);
	others= MakeOVGCacheOthersValue();
	
	cu.width = 0;
	cu.height= 0;
	cu.style = style;
	cu.others= others;
	cu.extra.infoL2.hVGPath = glyphPath;
	cu.data  = NULL;

	return AddToCache(&pdtfwrk->cachearrL2, code, 0, 0, &cu);
}

/*---------------------------------------------------------------------------*/
/// a glyph's pathSegs & pathData cache
DT_BOOL chkL1Cache(pDT_Fontwrk pdtfwrk, DT16_ushort code, VGubyte **Segs, DT32_int *SegsCnt, DT_VGtype **Data, DT32_int *DataCnt)	
{
	DT16_ushort style, others, vert;
	CacheUnit *unit;
	pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;
	
DBG_MSG_SHOW_FUNC_NAME();

	vert = (DT16_ushort)pdtfwrk->style.vert;
#ifdef DT_VERT_BY_OVG
	vert = (DT16_ushort)pwrk->vert;	// overwrite it. vert will be done by rotate by OpenVG
#endif
	
	// FIXME: altfont's fid won't be logged. Don't distinguish fid now.
	style = MakeOVGCacheStyleValue( (DT16_ushort)pdtfwrk->font->fid, (DT16_ushort)pdtfwrk->style.oulcoord, 
									(DT16_ushort)pdtfwrk->style.bidirule, (DT16_ushort)vert);
	others= MakeOVGCacheOthersValue();

	if(pdtfwrk->usedcacheL1){
		unit = GetFromCache(pdtfwrk->usedcacheL1, code, 0, 0, style, others);
		if(unit){
			*Segs = (VGubyte*)unit->data;
			*SegsCnt = unit->extra.infoL1.nSegs;
			// FIXME: if you want to use the memory more efficiently.
			*Data = (DT_VGtype*)(unit->data + pdtfwrk->usedcacheL1->CacheSet->condition.max_segs*sizeof(VGubyte));	// check the space by getOVGL1datasize()
			*DataCnt = unit->extra.infoL1.nData;
			return DT_TRUE;
		}
	}
	return DT_FALSE;
}

/// FIXME: Segs, Data will always be in the tempbuf, 
/// and the first gDT_MAX_SEGS_PER_GLYPH bytes are reserved for Segs, Data will start from tempbuf+gDT_MAX_SEGS_PER_GLYPH.
DT32_int addToL1Cache(pDT_Fontwrk pdtfwrk, DT16_ushort code, /*VGubyte *Segs,*/ DT32_int SegsCnt, /*VGfloat *Data,*/ DT32_int DataCnt)
{
	DT16_ushort style, others, vert;
	CacheUnit cu;
	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;
	pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;

	vert = (DT16_ushort)pdtfwrk->style.vert;
#ifdef DT_VERT_BY_OVG
	vert = (DT16_ushort)pwrk->vert;	// overwrite it. vert will be done by rotate by OpenVG
#endif
	
	// FIXME: altfont's fid won't be logged. Don't distinguish fid now.
	style = MakeOVGCacheStyleValue( (DT16_ushort)pdtfwrk->font->fid, (DT16_ushort)pdtfwrk->style.oulcoord, 
									(DT16_ushort)pdtfwrk->style.bidirule, (DT16_ushort)vert);
	others= MakeOVGCacheOthersValue();
	
	cu.width = 0;
	cu.height= 0;
	cu.style = style;
	cu.others= others;
	cu.extra.infoL1.nSegs = (DT16_ushort) SegsCnt;
	cu.extra.infoL1.nData = (DT16_ushort) DataCnt;
	cu.data  = pmgrwrk->tempbuf;	// FIXME

	return AddToCache(&pdtfwrk->cachearrL1, code, 0, 0, &cu);
}

#ifdef DT_PARSEOVGPATHDATA_BY_ABS
//#define TEST_CONTOUR
/*--------------------------------------------------------------------------*/
/* parse outline path data to OpenVG format -- left-bottom origin coordinate*/
/* Return Value: <0:error; >=0:DT_SUCCESS									*/
DT_void parsePathDataLB_EMABS(pDT_Fontwrk pdtfwrk, DT16_short *olbuf, DT32_long olsize, 
							  //DT32_int method, DT_RECT *rt,	// can't use, because of cache.
							  //DT_VGtype ori[2],				// always (0,0)
							  VGubyte **Segs, DT32_int *SegsCnt, DT_VGtype **Data, DT32_int *DataCnt)
{
	VGubyte *pathSegs,*pSegs;
	DT_VGtype *pathData,*pData;
	DT8_uchar  *p;
	DT16_short *path, *last, op;
	DT32_int opCnt, xyCnt, opIdx, xyIdx;
//	DT32_int nodraw=0;
	DT32_int opTotal, xyTotal;
	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;

DBG_MSG_SHOW_FUNC_NAME();

	pSegs = pathSegs = (VGubyte*) pmgrwrk->tempbuf;
	p = (DT8_uchar*)pmgrwrk->tempbuf + gDT_MAX_SEGS_PER_GLYPH;
	pData = pathData = (DT_VGtype*)p;
	
    path = olbuf;
    last = path + olsize;

	opTotal = xyTotal = 0;
#ifdef TEST_CONTOUR
     while (path < last && nodraw < 3)
#else
     while (path < last)
#endif
	 {
      // Get Contour Path 
      opCnt = *path++;
      xyCnt = *path++;

      // Convert each segment
      for (opIdx=xyIdx=0; opIdx<opCnt; opIdx++)
      {
        op = *path++;
        switch (op)
        {
        case DLO_MOVETO:
//		  if(DLO_AREA_NOT_DRAW==method){
//			nodraw = isInsideRect(*path,*(path+1),rt);
//		  }
//		  if(!nodraw){
            pathSegs[opIdx] = VG_MOVE_TO_ABS;
            pathData[xyIdx++] = (DT_VGtype) (/*ori[0] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[1] +*/ gDT_FONT_EMSIZE - (*path++));
//		  }else{
//			//skip the value, not recorded.
//			*path++;
//			*path++;
//		  }
          break;

        case DLO_LINETO:
// 		  if(!nodraw){
            pathSegs[opIdx] = VG_LINE_TO_ABS;
            pathData[xyIdx++] = (DT_VGtype) (/*ori[0] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[1] +*/ gDT_FONT_EMSIZE - (*path++));
//		  }else{
//			*path++;
//			*path++;
//		  }
          break;

        case DLO_BEZIERTO:
// 		  if(!nodraw){
            pathSegs[opIdx] = VG_QUAD_TO_ABS;
            pathData[xyIdx++] = (DT_VGtype) (/*ori[0] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[1] +*/ gDT_FONT_EMSIZE - (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[0] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[1] +*/ gDT_FONT_EMSIZE - (*path++));
//		  }else{
//			  *path++;
//			  *path++;
//			  *path++;
//			  *path++;
//		  }
          break;

        case DLO_CLOSEPATH:
// 		  if(!nodraw){
            pathSegs[opIdx] = VG_CLOSE_PATH;
            //vgAppendPathData(vgpath, opCnt, pathSegs, pathData);
//		  }else{
//			nodraw = 0;
//		  }
#ifdef TEST_CONTOUR
			nodraw++;
#endif
          break;
        }
      }
	  
	  opTotal += opIdx;
	  xyTotal += xyIdx;
	  pathSegs = pSegs + opTotal;
	  pathData = pData + xyTotal;
	}

	 /// ABS don't require this, vgTranslate will cover it.
	 /// When VGshort datatype, it needs to move back to origin. (Because ori might larger than VG_MAXSHORT) 
//#if (16==DT_SET_DATATYPE_FOR_VGPATH)
//	 pSegs[opTotal++] = VG_MOVE_TO_ABS;
//	 pData[xyTotal++] = /*ori[0] +*/ 0;
//	 pData[xyTotal++] = /*ori[1] +*/ 0;
//#endif

	*Segs = pSegs;
	*SegsCnt = opTotal;
	*Data = pData;
	*DataCnt = xyTotal; 
}

/*--------------------------------------------------------------------------*/
/* parse outline path data to OpenVG format -- left-top origin coordinate	*/
/* Return Value: <0:error; >=0:DT_SUCCESS									*/
DT_void parsePathDataLT_EMABS(pDT_Fontwrk pdtfwrk, DT16_short *olbuf, DT32_long olsize, 
							  //DT32_int method, DT_RECT *rt,	// can't use, because of cache.
							  //DT_VGtype ori[2],				// always (0,0)
							  VGubyte **Segs, DT32_int *SegsCnt, DT_VGtype **Data, DT32_int *DataCnt)
{
	VGubyte *pathSegs,*pSegs;
	DT_VGtype *pathData,*pData;

	DT8_uchar  *p;
	DT16_short *path, *last, op;
	DT32_int opCnt, xyCnt, opIdx, xyIdx;
//	DT32_int nodraw=0;

	DT32_int opTotal, xyTotal;

	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;

DBG_MSG_SHOW_FUNC_NAME();

	pSegs = pathSegs = (VGubyte*) pmgrwrk->tempbuf;
	p = (DT8_uchar*)pmgrwrk->tempbuf + gDT_MAX_SEGS_PER_GLYPH;
	pData = pathData = (DT_VGtype*)p;

    path = olbuf;
    last = path + olsize;

	opTotal = xyTotal = 0;
     while (path < last)
	 {
      // Get Contour Path 
      opCnt = *path++;
      xyCnt = *path++;

      // Convert each segment
      for (opIdx=xyIdx=0; opIdx<opCnt; opIdx++)
      {
        op = *path++;
        switch (op)
        {
        case DLO_MOVETO:
// 		  if(DLO_AREA_NOT_DRAW==method){
// 			nodraw = isInsideRect(*path,*(path+1),rt);
//		  }
// 		  if(!nodraw){
            pathSegs[opIdx] = VG_MOVE_TO_ABS;
            pathData[xyIdx++] = (DT_VGtype) (/*ori[0] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[1] +*/ (*path++));
//		  }else{
//			//skip the value, not recorded.
//			*path++;
//			*path++;
//		  }
          break;

        case DLO_LINETO:
// 		  if(!nodraw){
            pathSegs[opIdx] = VG_LINE_TO_ABS;
            pathData[xyIdx++] = (DT_VGtype) (/*ori[0] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[1] +*/ (*path++));
//		  }else{
//			*path++;
//			*path++;
//		  }
          break;

        case DLO_BEZIERTO:
// 		  if(!nodraw){
            pathSegs[opIdx] = VG_QUAD_TO_ABS;
            pathData[xyIdx++] = (DT_VGtype) (/*ori[0] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[1] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[0] +*/ (*path++));
            pathData[xyIdx++] = (DT_VGtype) (/*ori[1] +*/ (*path++));
//		  }else{
//			  *path++;
//			  *path++;
//			  *path++;
//			  *path++;
//		  }
          break;

        case DLO_CLOSEPATH:
// 		  if(!nodraw){
            pathSegs[opIdx] = VG_CLOSE_PATH;
            //vgAppendPathData(vgpath, opCnt, pathSegs, pathData);
//		  }else{
//			nodraw = 0;
//		  }
          break;
        }
      }

	  opTotal += opIdx;
	  xyTotal += xyIdx;
	  pathSegs = pSegs + opTotal;
	  pathData = pData + xyTotal;
	}

	 /// ABS don't require this, vgTranslate will cover it.
	 /// When VGshort datatype, it needs to move back to origin. (Because ori might larger than VG_MAXSHORT) 
//#if (16==DT_SET_DATATYPE_FOR_VGPATH)
//	 pSegs[opTotal++] = VG_MOVE_TO_ABS;
//	 pData[xyTotal++] = /*ori[0] +*/ 0;
//	 pData[xyTotal++] = /*ori[1] +*/ 0;
//#endif

	*Segs = pSegs;
	*SegsCnt = opTotal;
	*Data = pData;
	*DataCnt = xyTotal; 
}

#else
/*--------------------------------------------------------------------------*/
/* parse outline path data to OpenVG format -- left-bottom origin coordinate*/
/* Return Value: <0:error; >=0:DT_SUCCESS									*/
DT_void parsePathDataLB_EMREL(pDT_Fontwrk pdtfwrk, DT16_short *olbuf, DT32_long olsize, 
							  //DT32_int method, DT_RECT *rt,	// can't use, because of cache.
							  //DT_VGtype ori[2],				// always (0,0)
							  VGubyte **Segs, DT32_int *SegsCnt, DT_VGtype **Data, DT32_int *DataCnt)
{
	VGubyte *pathSegs,*pSegs;
	DT_VGtype *pathData,*pData;
	DT_VGtype prvX, prvY;
	DT8_uchar  *p;
	DT16_short *path, *last, op;
	DT32_int opCnt, xyCnt, opIdx, xyIdx;
	DT32_int opTotal, xyTotal;
	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;
//	DT32_int nodraw=0; 		// DLO_AREA_NOT_DRAW is not required in this func, because it's not compatible with cache.
							// This issue should be done outside this func, ex: 0x0E0D, 0x0E10 was replaced by 0x0E60 & 0x0E63 for Thai

	DBG_MSG_SHOW_FUNC_NAME();

	pSegs = pathSegs = (VGubyte*) pmgrwrk->tempbuf;
	p = (DT8_uchar*)pmgrwrk->tempbuf + gDT_MAX_SEGS_PER_GLYPH;
	pData = pathData = (DT_VGtype*)p;
	
    path = olbuf;
    last = path + olsize;

	opTotal = xyTotal = 0;
	prvX = prvY = 0;
     while (path < last)
	 {
      // Get Contour Path 
      opCnt = *path++;
      xyCnt = *path++;

      // Convert each segment
      for (opIdx=xyIdx=0; opIdx<opCnt; opIdx++)
      {
        op = *path++;
        switch (op)
        {
        case DLO_MOVETO:
            pathSegs[opIdx] = VG_MOVE_TO_REL;
            prvX += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvX;
            prvY += pathData[xyIdx++] = (DT_VGtype) gDT_FONT_EMSIZE - (*path++) - prvY;
          break;

        case DLO_LINETO:
            pathSegs[opIdx] = VG_LINE_TO_REL;
            prvX += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvX;
			prvY += pathData[xyIdx++] = (DT_VGtype) gDT_FONT_EMSIZE - (*path++) - prvY;
          break;

        case DLO_BEZIERTO:
            pathSegs[opIdx] = VG_QUAD_TO_REL;
            pathData[xyIdx++] = (DT_VGtype) (*path++) - prvX;
            pathData[xyIdx++] = (DT_VGtype) gDT_FONT_EMSIZE - (*path++) - prvY;
            prvX += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvX;
            prvY += pathData[xyIdx++] = (DT_VGtype) gDT_FONT_EMSIZE - (*path++) - prvY;
          break;

        case DLO_CLOSEPATH:
            pathSegs[opIdx] = VG_CLOSE_PATH;
          break;
        }
      }
	  
	  opTotal += opIdx;
	  xyTotal += xyIdx;
	  pathSegs = pSegs + opTotal;
	  pathData = pData + xyTotal;
	}
	 
	 /// When VGshort datatype, it needs to move back to origin. (Because ori might larger than VG_MAXSHORT) 
#if (16==DT_SET_DATATYPE_FOR_VGPATH)
	 pSegs[opTotal++] = VG_MOVE_TO_REL;
	 pData[xyTotal++] = /*ori[0] */ - prvX;
	 pData[xyTotal++] = /*ori[1] */ - prvY;
#endif

	*Segs = pSegs;
	*SegsCnt = opTotal;
	*Data = pData;
	*DataCnt = xyTotal; 
}

/*--------------------------------------------------------------------------*/
/* parse outline path data to OpenVG format -- left-top origin coordinate	*/
/* Return Value: <0:error; >=0:DT_SUCCESS									*/
DT_void parsePathDataLT_EMREL(pDT_Fontwrk pdtfwrk, DT16_short *olbuf, DT32_long olsize, 
							  //DT32_int method, DT_RECT *rt,	// can't use, because of cache.
							  //DT_VGtype ori[2],				// always (0,0)
							  VGubyte **Segs, DT32_int *SegsCnt, DT_VGtype **Data, DT32_int *DataCnt)
{
	VGubyte *pathSegs,*pSegs;
	DT_VGtype *pathData,*pData;
	DT_VGtype prvX, prvY;
	DT8_uchar  *p;
	DT16_short *path, *last, op;
	DT32_int opCnt, xyCnt, opIdx, xyIdx;
	DT32_int opTotal, xyTotal;
	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;
//	DT32_int nodraw=0; 		// DLO_AREA_NOT_DRAW is not required in this func, because it's not compatible with cache.
							// This issue should be done outside this func, ex: 0x0E0D, 0x0E10 was replaced by 0x0E60 & 0x0E63 for Thai

DBG_MSG_SHOW_FUNC_NAME();

	pSegs = pathSegs = (VGubyte*) pmgrwrk->tempbuf;
	p = (DT8_uchar*)pmgrwrk->tempbuf + gDT_MAX_SEGS_PER_GLYPH;
	pData = pathData = (DT_VGtype*)p;

    path = olbuf;
    last = path + olsize;

	opTotal = xyTotal = 0;
	prvX = prvY = 0;
     while (path < last)
	 {
      // Get Contour Path 
      opCnt = *path++;
      xyCnt = *path++;

      // Convert each segment
      for (opIdx=xyIdx=0; opIdx<opCnt; opIdx++)
      {
        op = *path++;
        switch (op)
        {
        case DLO_MOVETO:
            pathSegs[opIdx] = VG_MOVE_TO_REL;
            prvX += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvX;
            prvY += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvY;
          break;

        case DLO_LINETO:
            pathSegs[opIdx] = VG_LINE_TO_REL;
            prvX += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvX;
            prvY += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvY;
          break;

        case DLO_BEZIERTO:
            pathSegs[opIdx] = VG_QUAD_TO_REL;
			pathData[xyIdx++] = (DT_VGtype) (*path++) - prvX;
			pathData[xyIdx++] = (DT_VGtype) (*path++) - prvY;
			prvX += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvX;
			prvY += pathData[xyIdx++] = (DT_VGtype) (*path++) - prvY;
          break;

        case DLO_CLOSEPATH:
            pathSegs[opIdx] = VG_CLOSE_PATH;
          break;
        }
      }

	  opTotal += opIdx;
	  xyTotal += xyIdx;
	  pathSegs = pSegs + opTotal;
	  pathData = pData + xyTotal;
	}

	 /// When VGshort datatype, it needs to move back to origin. (Because ori might larger than VG_MAXSHORT) 
#if (16==DT_SET_DATATYPE_FOR_VGPATH)
	 pSegs[opTotal++] = VG_MOVE_TO_REL;
	 pData[xyTotal++] = /*ori[0] */ - prvX;
	 pData[xyTotal++] = /*ori[1] */ - prvY;
#endif

	*Segs = pSegs;
	*SegsCnt = opTotal;
	*Data = pData;
	*DataCnt = xyTotal; 
}
#endif

DT_void parseGlyphPathDataToOVGformat(pDT_Fontwrk pdtfwrk, pDT_OulBuf oulbuf, DT32_int idx, DT_void *data, DT32_long pathsize,
									   VGubyte **Segs, DT32_int *SegsCnt, DT_VGtype **Data, DT32_int *DataCnt)
{
	DT16_short *pathbuf = data;
//	DT_VGtype ori[2];
//	DT32_int method; 
//	DT_RECT *rt;

DBG_MSG_SHOW_FUNC_NAME();

	/* Parse each glyph's outline data to the path */
//	ori[0] = 0;		ori[1] = 0;
//	//method = oulbuf->carets[idx].drawmethod;
//	method = DLO_DRAW_NORMAL;			// force this method to get the normal glyph path
//	rt = &oulbuf->carets[idx].dmrect;

	if(pathsize>0){
#ifdef DT_PARSEOVGPATHDATA_BY_ABS
	  if(pdtfwrk->style.oulcoord == DT_COORD_LEFT_TOP){
		parsePathDataLT_EMABS(pdtfwrk, pathbuf, pathsize, //method, rt, ori, 
							  Segs, SegsCnt, Data, DataCnt);
	  }else{		// DT_COORD_LEFT_BOT
		parsePathDataLB_EMABS(pdtfwrk, pathbuf, pathsize, //method, rt, ori, 
							  Segs, SegsCnt, Data, DataCnt);
	  }
#else
	  if(pdtfwrk->style.oulcoord == DT_COORD_LEFT_TOP){
		parsePathDataLT_EMREL(pdtfwrk, pathbuf, pathsize, //method, rt, ori, 
							  Segs, SegsCnt, Data, DataCnt);
	  }else{		// DT_COORD_LEFT_BOT
		parsePathDataLB_EMREL(pdtfwrk, pathbuf, pathsize, //method, rt, ori, 
							  Segs, SegsCnt, Data, DataCnt);
	  }
#endif
	}
}

/* get glyph's path data from FDL engine and convert it to OpenVG format */
DT32_int GetGlyphPathDataFromEngine(pDT_Fontwrk pdtfwrk, pDT_OulBuf oulbuf, DT32_int idx,
									VGubyte **Segs, DT32_int *SegsCnt, DT_VGtype **Data, DT32_int *DataCnt)
{
	//pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;
	DT32_int ret, rtval;
	DT32_int tmpsz;
	DT32_long pathsize;

	/* Prepare the memory to get FDL path data from engine. */
	if(pdtfwrk->rtdatasz < DLO_MAX_OUL_SIZE_PER_GLYPH){
		// It should not get into here when gDT_Dont_Alloc_BmpBuf_When_CreateFont==0!
		if(0==gDT_Dont_Alloc_BmpBuf_When_CreateFont){
			return DT_NOT_ENOUGH_BUFFER;
		}

		tmpsz = pdtfwrk->rtdatasz;
		if(pdtfwrk->rtdata)
			DT_free(pdtfwrk->rtdata);
		pdtfwrk->rtdatasz = DT_ALLOC_SIZE(DLO_MAX_OUL_SIZE_PER_GLYPH);
		pdtfwrk->rtdata	  = DT_malloc(pdtfwrk->rtdatasz);
		if(!pdtfwrk->rtdata){
			// Try to allocate all the memory remained.
			if(1==gDT_Set_Fix_Memory_Size){
				pdtfwrk->rtdatasz = (DT32_int) DT_query_memory_remained();	// Because it's remained, no DT_ALLOC_SIZE().
				if(tmpsz > pdtfwrk->rtdatasz){
					pdtfwrk->rtdatasz = tmpsz;		// Ensure new memory won't be smaller than origin.
				}
				pdtfwrk->rtdata = DT_malloc(pdtfwrk->rtdatasz);
				if(!pdtfwrk->rtdata){
					// Should not get into here!
					pdtfwrk->rtdatasz = 0;
					pdtfwrk->rtdata	  = NULL;
					return DT_NOT_ENOUGH_BUFFER;
				}else{
					if(pdtfwrk->rtdatasz > pdtfwrk->rtdataszused){
						pdtfwrk->rtdataszused = pdtfwrk->rtdatasz;
					}
				}
			}else{
				pdtfwrk->rtdatasz = 0;
				pdtfwrk->rtdata	  = NULL;
				return DT_NOT_ENOUGH_BUFFER;
			}
		}else{
			if(pdtfwrk->rtdatasz > pdtfwrk->rtdataszused){
				pdtfwrk->rtdataszused = pdtfwrk->rtdatasz;
			}
		}
	}

	pathsize = 0;
	if(pdtfwrk->bFastMode){
		ret = DLO_FastCharOUL(pdtfwrk->hShaper, oulbuf->glyphs[idx], idx, pdtfwrk->rtdata, (DT32_long)pdtfwrk->rtdatasz, &pathsize);	
	}else{
		ret = DLO_GetCharOUL(pdtfwrk->hShaper, oulbuf->glyphs[idx], idx, pdtfwrk->rtdata, (DT32_long)pdtfwrk->rtdatasz, &pathsize);
	}
	rtval = convReturnValue(ret);
	if(rtval < 0){
		goto release_rtdata;
	}

	parseGlyphPathDataToOVGformat(pdtfwrk, oulbuf, idx, pdtfwrk->rtdata, pathsize,
									Segs, SegsCnt, Data, DataCnt);
	
release_rtdata:
	if(1==gDT_Dont_Alloc_BmpBuf_When_CreateFont){
		if(pdtfwrk->rtdata){
			DT_free(pdtfwrk->rtdata);
		}
		pdtfwrk->rtdata = NULL;
		pdtfwrk->rtdatasz = 0;
	}
	return rtval;	
}

DT32_int GetGlyphPathData(pDT_Fontwrk pdtfwrk, pDT_OulBuf oulbuf, DT32_int idx, VGubyte **Segs, DT32_int *SegsCnt, DT_VGtype **Data, DT32_int *DataCnt)
{
	DT32_int ret;
	DT_BOOL bL1Cached;
	DT16_ushort glyph;
//	VGubyte	*pSegs;
//	DT_VGtype	*pData;
//	DT32_int nSegs, nData;

DBG_MSG_SHOW_FUNC_NAME();

	glyph = oulbuf->glyphs[idx];
	bL1Cached = DT_FALSE;
	/* Check L1 cache */
	if(pdtfwrk->usedcacheL1){
		bL1Cached = chkL1Cache(pdtfwrk, glyph, Segs, SegsCnt, Data, DataCnt);
		if(bL1Cached){
			return DT_SUCCESS;
		}
	}

	/* get glyph's PathData of OVG format */
//	pSegs = NULL;	pData = NULL;
//	nSegs = nData = 0;
	ret = GetGlyphPathDataFromEngine(pdtfwrk, oulbuf, idx, Segs, SegsCnt, Data, DataCnt);
	if(ret < 0){
		return ret;
	}

	if(pdtfwrk->usedcacheL1){
		// add to L1 Cache
		addToL1Cache(pdtfwrk, glyph, *SegsCnt, *DataCnt);
	}

	return DT_SUCCESS;
}

DT32_int PrepareGlyphTmpPath(pDT_Fontwrk pdtfwrk)
{
	VGuint		nSegsHint = 0 * gDT_MAX_SEGS_PER_GLYPH;
	VGuint		nDataHint = 0 * gDT_MAX_SEGS_PER_GLYPH*2*2;

DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_DESTROY_VGPATH_EVERYTIME
	if(pdtfwrk->mytmppath_glyph){
		vgDestroyPath(pdtfwrk->mytmppath_glyph);
		pdtfwrk->mytmppath_glyph = VG_INVALID_HANDLE;
	}
	if(!pdtfwrk->mytmppath_glyph){
		pdtfwrk->mytmppath_glyph = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
											1.0f, 0.0f, nSegsHint, nDataHint, VG_PATH_CAPABILITY_ALL);
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_glyph){
			pdtfwrk->mytmppath_glyph = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
									1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		}
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_glyph){
			return  DT_VG_CREATEPATH_ERR;
		}
	}
#else
	// DT_RasterOVGPath() will guarantee the path had created successfully.
	vgClearPath(pdtfwrk->mytmppath_glyph, VG_PATH_CAPABILITY_ALL);
#endif
	return DT_SUCCESS;

}

DT32_int PrepareGlyph00TmpPath(pDT_Fontwrk pdtfwrk)
{
	VGuint		nSegsHint = 0 * gDT_MAX_SEGS_PER_GLYPH;
	VGuint		nDataHint = 0 * gDT_MAX_SEGS_PER_GLYPH*2*2;

DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_DESTROY_VGPATH_EVERYTIME
	if(pdtfwrk->mytmppath_glyph00){
		vgDestroyPath(pdtfwrk->mytmppath_glyph00);
		pdtfwrk->mytmppath_glyph00 = VG_INVALID_HANDLE;
	}
	if(!pdtfwrk->mytmppath_glyph00){
		pdtfwrk->mytmppath_glyph00 = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
											1.0f, 0.0f, nSegsHint, nDataHint, VG_PATH_CAPABILITY_ALL);
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_glyph00){
			pdtfwrk->mytmppath_glyph00 = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
									1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		}
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_glyph00){
			return DT_VG_CREATEPATH_ERR;
		}
	}
#else
	vgClearPath(pdtfwrk->mytmppath_glyph00, VG_PATH_CAPABILITY_ALL);
#endif
	return DT_SUCCESS;
}

/* translate & convert each coordinate point to VGfloat datatype, used for DT_PARSEOVGPATHDATA_BY_ABS only.*/
//DT_void myTranslatePathData_f(VGint nSegs, VGubyte *psrcSegs, DT_VGtype *psrcData, VGint orix, VGint oriy, VGfloat *pdstData)
//{
//	VGint i;
//	for(i=0; i<nSegs; i++){
//		switch(*psrcSegs++){
//		case VG_MOVE_TO_ABS:
//		case VG_LINE_TO_ABS:
//		case VG_SQUAD_TO_ABS:
//			*pdstData++ = (VGfloat)((*psrcData++) + orix);
//			*pdstData++ = (VGfloat)((*psrcData++) + oriy);
//			break;
//		case VG_HLINE_TO_ABS:
//			*pdstData++ = (VGfloat)((*psrcData++) + orix);
//			break;
//		case VG_VLINE_TO_ABS:
//			*pdstData++ = (VGfloat)((*psrcData++) + oriy);
//			break;
//		case VG_QUAD_TO_ABS:
//		case VG_SCUBIC_TO_ABS:
//			*pdstData++ = (VGfloat)((*psrcData++) + orix);
//			*pdstData++ = (VGfloat)((*psrcData++) + oriy);
//			*pdstData++ = (VGfloat)((*psrcData++) + orix);
//			*pdstData++ = (VGfloat)((*psrcData++) + oriy);
//			break;
//		case VG_CUBIC_TO_ABS:
//			*pdstData++ = (VGfloat)((*psrcData++) + orix);
//			*pdstData++ = (VGfloat)((*psrcData++) + oriy);
//			*pdstData++ = (VGfloat)((*psrcData++) + orix);
//			*pdstData++ = (VGfloat)((*psrcData++) + oriy);
//			*pdstData++ = (VGfloat)((*psrcData++) + orix);
//			*pdstData++ = (VGfloat)((*psrcData++) + oriy);
//			break;
//		case VG_SCCWARC_TO_ABS:
//		case VG_SCWARC_TO_ABS:
//		case VG_LCCWARC_TO_ABS:
//		case VG_LCWARC_TO_ABS:
//			*pdstData++ = (VGfloat)((*psrcData++));	// rh
//			*pdstData++ = (VGfloat)((*psrcData++));	// rv
//			*pdstData++ = (VGfloat)((*psrcData++));	// rot
//			*pdstData++ = (VGfloat)((*psrcData++) + orix);
//			*pdstData++ = (VGfloat)((*psrcData++) + oriy);
//		default:
//			break;
//		}
//	}
//}

/* translate & convert each coordinate point to VGfloat datatype, used for DT_PARSEOVGPATHDATA_BY_ABS only.*/
DT_void myTranslatePathData(VGint nSegs, VGubyte *psrcSegs, DT_VGtype *psrcData, DT_VGtype orix, DT_VGtype oriy, DT_VGtype *pdstData)
{
	VGint i;
	for(i=0; i<nSegs; i++){
		switch(*psrcSegs++){
		case VG_MOVE_TO_ABS:
		case VG_LINE_TO_ABS:
		case VG_SQUAD_TO_ABS:
			*pdstData++ = (DT_VGtype)((*psrcData++) + orix);
			*pdstData++ = (DT_VGtype)((*psrcData++) + oriy);
			break;
		case VG_HLINE_TO_ABS:
			*pdstData++ = (DT_VGtype)((*psrcData++) + orix);
			break;
		case VG_VLINE_TO_ABS:
			*pdstData++ = (DT_VGtype)((*psrcData++) + oriy);
			break;
		case VG_QUAD_TO_ABS:
		case VG_SCUBIC_TO_ABS:
			*pdstData++ = (DT_VGtype)((*psrcData++) + orix);
			*pdstData++ = (DT_VGtype)((*psrcData++) + oriy);
			*pdstData++ = (DT_VGtype)((*psrcData++) + orix);
			*pdstData++ = (DT_VGtype)((*psrcData++) + oriy);
			break;
		case VG_CUBIC_TO_ABS:
			*pdstData++ = (DT_VGtype)((*psrcData++) + orix);
			*pdstData++ = (DT_VGtype)((*psrcData++) + oriy);
			*pdstData++ = (DT_VGtype)((*psrcData++) + orix);
			*pdstData++ = (DT_VGtype)((*psrcData++) + oriy);
			*pdstData++ = (DT_VGtype)((*psrcData++) + orix);
			*pdstData++ = (DT_VGtype)((*psrcData++) + oriy);
			break;
		case VG_SCCWARC_TO_ABS:
		case VG_SCWARC_TO_ABS:
		case VG_LCCWARC_TO_ABS:
		case VG_LCWARC_TO_ABS:
			*pdstData++ = (DT_VGtype)((*psrcData++));	// rh
			*pdstData++ = (DT_VGtype)((*psrcData++));	// rv
			*pdstData++ = (DT_VGtype)((*psrcData++));	// rot
			*pdstData++ = (DT_VGtype)((*psrcData++) + orix);
			*pdstData++ = (DT_VGtype)((*psrcData++) + oriy);
		default:
			break;
		}
	}
}
/*---------------------------------------------------------------------------*/
DT32_int makeGlyphsPathByCache(pDT_Fontwrk pdtfwrk, pDT_OulBuf oulbuf, VGPath strpath)
{
	DT32_int ret, i;
	VGPath hGlyphPath;
	VGubyte  *pSegs;
	DT_VGtype *pData;
	DT32_int nSegs, nData;
	VGubyte	mvToOriSeg;
	DT_VGtype ori[2], orival[2];			//VGfloat ori[2], orival[2];	// avoid overflow when VGshort
#if (16==DT_SET_DATATYPE_FOR_VGPATH)
	DT_VGtype prv[2];						//VGfloat prv[2];
#endif
	DT_VGtype sRatio;

DBG_MSG_SHOW_FUNC_NAME();

	if(!oulbuf)
		return DT_LAYBUF_ERR;

	/* check glyphs count to avoid index over it (maybe modified outside by user). */
	if(oulbuf->gcnt>DT_MAX_GLYPHS_PER_STR)
		oulbuf->gcnt = DT_MAX_GLYPHS_PER_STR;
	
	ori[0] = ori[1] = 0;
	orival[0] = orival[1] = 0;
	mvToOriSeg = VG_MOVE_TO_ABS;
	sRatio = (DT_VGtype)pdtfwrk->oulbuf->eswidth*pdtfwrk->style.xsize/gDT_FONT_EMSIZE;


#ifndef DT_PARSEOVGPATHDATA_BY_ABS
#if (16==DT_SET_DATATYPE_FOR_VGPATH)
	prv[0] = ori[0];	 prv[1] = ori[1];
	mvToOriSeg = VG_MOVE_TO_REL;
#endif
#endif
	
	/* Parse each glyph's outline data to the path */
	for(i=0;i<oulbuf->gcnt;i++){
		if(pdtfwrk->style.oulcoord == DT_COORD_LEFT_TOP){
			ori[0] = (DT_VGtype)oulbuf->carets[i].oripos.x;
			ori[1] = (DT_VGtype)oulbuf->carets[i].oripos.y;
		}else{		// DT_COORD_LEFT_BOT
			ori[0] = (DT_VGtype)oulbuf->carets[i].oripos.x;
			ori[1] = (DT_VGtype)(0 - oulbuf->carets[i].oripos.y);
		}
#ifdef MOVEORI_TO_FILL_OVGWIDTH
		if(gDT_BmpWidth_Based_on_Pixels)
			ori[0] = ori[0] * pdtfwrk->oulbuf->pixwidth / sRatio;
#endif		
		hGlyphPath = VG_INVALID_HANDLE;
		pSegs = NULL;	pData = NULL;
		nSegs = nData = 0;
		/* Check L2 Cache: glyph VGPath cache */
		if(pdtfwrk->usedcacheL2){
			hGlyphPath = chkL2Cache(pdtfwrk,oulbuf->glyphs[i]);
		}
		/* if it need to get PathData from L1 cache? */
		if(VG_INVALID_HANDLE==hGlyphPath){
			ret = GetGlyphPathData(pdtfwrk,oulbuf,i,&pSegs,&nSegs,&pData,&nData);
			if(ret < 0){
				return ret;
			}
			/* if it need to add into L2 cache? */
			if(pdtfwrk->usedcacheL2){
				hGlyphPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
											1.0f, 0.0f, gDT_MAX_SEGS_PER_GLYPH, gDT_MAX_SEGS_PER_GLYPH*2*2, VG_PATH_CAPABILITY_ALL);
				if(VG_INVALID_HANDLE!=hGlyphPath){
					if(nSegs > 0)
						vgAppendPathData(hGlyphPath,nSegs,pSegs,pData);
					addToL2Cache(pdtfwrk,oulbuf->glyphs[i],hGlyphPath);
				}
			}
		}

#ifdef DT_PARSEOVGPATHDATA_BY_ABS
 #if (0)	// 2012-01-19: modified for performance on some platform (Takumi) when L2 Cache is off.
		/* transform the path for the origin pos. */
		vgSeti(VG_MATRIX_MODE,VG_MATRIX_PATH_USER_TO_SURFACE);
		vgLoadIdentity();
		vgTranslate((VGfloat)ori[0],(VGfloat)ori[1]);
		//vgClearPath(pdtfwrk->mytmppath_glyph,VG_PATH_CAPABILITY_ALL);
		PrepareGlyphTmpPath(pdtfwrk);		// used to create or clear the mytmppath_glyph
		if(hGlyphPath==VG_INVALID_HANDLE){
			//vgClearPath(pdtfwrk->mytmppath_glyph00,VG_PATH_CAPABILITY_ALL);
			PrepareGlyph00TmpPath(pdtfwrk);	// used to create or clear the mytmppath_glyph00
			if(nSegs > 0)
				vgAppendPathData(pdtfwrk->mytmppath_glyph00,nSegs,pSegs,pData);
			vgTransformPath(pdtfwrk->mytmppath_glyph,pdtfwrk->mytmppath_glyph00);
		}else{
			vgTransformPath(pdtfwrk->mytmppath_glyph,hGlyphPath);
		}
		// append to strpath
		vgAppendPath(strpath, pdtfwrk->mytmppath_glyph);
 #else	// (0)
		if(hGlyphPath==VG_INVALID_HANDLE){	// L2 Cache is off.
			if(nSegs > 0){
				DT_VGtype *p;
				if(0==ori[0] && 0==ori[1]){
					p = (DT_VGtype*)pData;
				}else
				{
					p = (DT_VGtype*)((DT8_char*)pdtfwrk->rtdata + gDT_MAX_SEGS_PER_GLYPH);
					myTranslatePathData(nSegs, pSegs, pData, ori[0], ori[1], p);
				}
				vgAppendPathData(strpath, nSegs, pSegs, p);
			}
		}else{								// L2 Cache is on.
			static VGfloat matrix[] = {1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f};
			matrix[6] = (VGfloat)ori[0];
			matrix[7] = (VGfloat)ori[1];
			vgLoadMatrix(matrix);
			PrepareGlyphTmpPath(pdtfwrk);		// used to create or clear the mytmppath_glyph
			vgTransformPath(pdtfwrk->mytmppath_glyph,hGlyphPath);
			vgAppendPath(strpath, pdtfwrk->mytmppath_glyph);
		}
 #endif	// (0)
#else	/* By Relational coordinate pathdata */
		/* it can append path data directly. */
 #if (16 == DT_SET_DATATYPE_FOR_VGPATH)
		orival[0] = (DT_VGtype)(ori[0] - prv[0]);	// typecast after the substraction finished to avoid overflow
		orival[1] = (DT_VGtype)(ori[1] - prv[1]);
		vgAppendPathData(strpath,1,&mvToOriSeg,orival);	// move to the origin pos.
		prv[0] = ori[0];
		prv[1] = ori[1];
 #else
		orival[0] = (DT_VGtype)ori[0];
		orival[1] = (DT_VGtype)ori[1];
		vgAppendPathData(strpath,1,&mvToOriSeg,orival);	// move to the origin pos.
 #endif
		if(hGlyphPath==VG_INVALID_HANDLE){
			PrepareGlyph00TmpPath(pdtfwrk);			// use mytmppath_glyph00 because the datatype matches.
			if(nSegs > 0)
				vgAppendPathData(pdtfwrk->mytmppath_glyph00,nSegs,pSegs,pData);
			vgAppendPath(strpath,pdtfwrk->mytmppath_glyph00);
			//vgAppendPathData(strpath,nSegs,pSegs,pData);
		}else{
			vgAppendPath(strpath, hGlyphPath);
		}
#endif
	}

	return DT_SUCCESS;
}

//DT32_int makerectlineLT(VGfloat startx, VGfloat starty, VGfloat width, VGfloat height, VGubyte *Segs, VGfloat *Coords)
DT32_int makerectlineLT(DT_VGtype startx, DT_VGtype starty, DT_VGtype width, DT_VGtype height, VGubyte *Segs, DT_VGtype *Coords)
{
	Segs[0] = VG_MOVE_TO_ABS;
	Coords[0] = startx;		//origin[0];
	Coords[1] = starty;		//origin[1] + ulpos - thick/2;
	Segs[1] = VG_HLINE_TO_REL;
	Coords[2] = width;	//(VGfloat)info->width;			// DT_COORD_LEFT_TOP also the same.
	Segs[2] = VG_VLINE_TO_REL;
	Coords[3] = height;
	Segs[3] = VG_HLINE_TO_REL;
	Coords[4] = -width;
	Segs[4] = VG_VLINE_TO_REL;
	Coords[5] = -height;
	Segs[5] = VG_CLOSE_PATH;
	return 6;
}

// NON-ZERO fill with FDL path should complete the path by the same direction (clockwise).
//DT32_int makerectlineLB(VGfloat startx, VGfloat starty, VGfloat width, VGfloat height, VGubyte *Segs, VGfloat *Coords)
DT32_int makerectlineLB(DT_VGtype startx, DT_VGtype starty, DT_VGtype width, DT_VGtype height, VGubyte *Segs, DT_VGtype *Coords)
{
	Segs[0] = VG_MOVE_TO_ABS;
	Coords[0] = startx;					//origin[0];
	Coords[1] = starty + height;		//origin[1] + ulpos - thick/2;
	Segs[1] = VG_HLINE_TO_REL;
	Coords[2] = width;	//(VGfloat)info->width;			// DT_COORD_LEFT_TOP also the same.
	Segs[2] = VG_VLINE_TO_REL;
	Coords[3] = -height;
	Segs[3] = VG_HLINE_TO_REL;
	Coords[4] = -width;
	Segs[4] = VG_VLINE_TO_REL;
	Coords[5] = height;
	Segs[5] = VG_CLOSE_PATH;
	return 6;
}

/*--------------------------------------------------------------------------*/
/* Because addunderline() is called after transformed, so it doesn't deal	*/
/* with the VG_MAXSHORT overflow issue when 16==DT_SET_DATATYPE_FOR_VGPATH.	*/
/* Return Value: 0:DT_SUCCESS; <0:error										*/
DT32_int addUnderline(pDT_Fontwrk pdtfwrk, VGPath strpath, DT_VGtype origin[2], DT_VGtype width, DT_VGtype height)
{
	DT32_int szX, szY, p_ul, w_ul, e_ul, coordstyle, vert;
	VGubyte Segs[6];
	DT_VGtype Coords[6];				//VGfloat Coords[6];
	DT_VGtype mvUp, mvLf, thick, ulpos, boldw;	//VGfloat mvUp, mvLf, thick, ulpos;
	VGint	segsnum;
	DT_BOOL	bEdge;
	pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;

DBG_MSG_SHOW_FUNC_NAME();

	szX  = pdtfwrk->style.xsize;		//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_SIZEX);
	szY  = pdtfwrk->style.ysize;		//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_SIZEY);
	p_ul = pdtfwrk->style.p_underline;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_P_UNDERLINE);
	w_ul = pdtfwrk->style.w_underline;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_W_UNDERLINE);
	e_ul = pdtfwrk->style.e_underline;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_E_UNDERLINE);
	coordstyle = pdtfwrk->style.oulcoord;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_VG_COORD);
	vert = pdtfwrk->style.vert;
	mvUp = (DT_VGtype)pwrk->linemoveYup;
	mvLf = (DT_VGtype)pwrk->linemoveXlf;
	segsnum = 0;

	if(w_ul<=0 || !pdtfwrk->style.is_underline)
		return DT_SUCCESS;

	if(pdtfwrk->style.f_edge==DT_STYLE_BOLD || pdtfwrk->style.f_edge==DT_STYLE_OUTLINE){
		boldw = (DT_VGtype)pdtfwrk->style.w_edge;
		bEdge = DT_TRUE;
	}else{
		boldw = 0;
		bEdge = DT_FALSE;
	}

#ifdef DT_VERT_BY_OVG
	if(vert){
		vert = pwrk->vert;		// should be 0. force this to draw underline correctly.
	}
#endif

	if(vert){
		DT_VGtype starty;		//VGfloat starty;
		ulpos = (DT_VGtype)(-p_ul-(DT_VGtype)w_ul/2)*gDT_FONT_EMSIZE/szX;	// DT_COORD_LEFT_TOP also the same.
		ulpos += mvUp;
		thick = (DT_VGtype)(w_ul * gDT_FONT_EMSIZE / szX);
		if(bEdge){
			height -= (DT_VGtype)(boldw * 2 * gDT_FONT_EMSIZE / szY);
		}
		if(coordstyle==DT_COORD_LEFT_TOP){
			starty = origin[1] + height;
			segsnum = makerectlineLT((DT_VGtype)(origin[0] + ulpos - thick/2), starty, thick, (DT_VGtype)-height, Segs, Coords);
		}else{
			starty = origin[1] + gDT_FONT_EMSIZE;
			segsnum = makerectlineLB((DT_VGtype)(origin[0] + ulpos - thick/2), starty, thick, (DT_VGtype)-height, Segs, Coords);
		}
	}else{
		thick = (DT_VGtype)(w_ul * gDT_FONT_EMSIZE / szY);
		if(bEdge){
			width -= (DT_VGtype)(boldw * 2 * gDT_FONT_EMSIZE / szX);
//  			height -= (DT_VGtype)(boldw * 2 * gDT_FONT_EMSIZE / szY);
		}
		if(coordstyle==DT_COORD_LEFT_TOP){
			ulpos = (DT_VGtype)((szY+(-p_ul+(DT_VGtype)w_ul/2))*gDT_FONT_EMSIZE/szY);
//			if(height > gDT_FONT_EMSIZE)
//				ulpos = (DT_VGtype)(gDT_FONT_EMSIZE + (-p_ul+(DT_VGtype)w_ul/2)*gDT_FONT_EMSIZE/szY);
//			else
//				ulpos = (DT_VGtype)(height + (-p_ul+(DT_VGtype)w_ul/2)*gDT_FONT_EMSIZE/szY);
			ulpos -= mvUp;
			segsnum = makerectlineLT((DT_VGtype)(origin[0]+mvLf), (DT_VGtype)(origin[1] + ulpos - thick/2), width, thick, Segs, Coords);
		}else{
			ulpos = (DT_VGtype)((p_ul-(DT_VGtype)w_ul/2)*gDT_FONT_EMSIZE/szY);
//			if(height < gDT_FONT_EMSIZE)
//				ulpos += gDT_FONT_EMSIZE - height;
			ulpos += mvUp;
			segsnum = makerectlineLB((DT_VGtype)(origin[0]+mvLf), (DT_VGtype)(origin[1] + ulpos - thick/2), width, thick, Segs, Coords);
		}
	}

	//if(segsnum > 0)		// no need to check, because segsnum always = 6.
	vgAppendPathData(strpath, segsnum, Segs, (DT_VGtype*)Coords);
	
	return DT_SUCCESS;
}

/*--------------------------------------------------------------------------*/
/* Because addStrike() is called after transformed, so it doesn't deal		*/
/* with the VG_MAXSHORT overflow issue when 16==DT_SET_DATATYPE_FOR_VGPATH.	*/
/* Return Value: 0:DT_SUCCESS; <0:error										*/
DT32_int addStrike(pDT_Fontwrk pdtfwrk, VGPath strpath, DT_VGtype origin[2], DT_VGtype width, DT_VGtype height)
{
	DT32_int szX, szY, p_sk, w_sk, e_sk, coordstyle, vert;
	VGubyte Segs[6];
	DT_VGtype Coords[6];				//VGfloat Coords[6];
	DT_VGtype mvUp, mvLf, thick, skpos, boldw;	//VGfloat mvUp, mvLf, thick, skpos;
	VGint	segsnum;
	DT_BOOL	bEdge;
	pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;

DBG_MSG_SHOW_FUNC_NAME();

	szX  = pdtfwrk->style.xsize;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_SIZEX);
	szY  = pdtfwrk->style.ysize;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_SIZEY);
	p_sk = pdtfwrk->style.p_strike;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_P_STRIKE);
	w_sk = pdtfwrk->style.w_strike;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_W_STRIKE);
	e_sk = pdtfwrk->style.e_strike;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_E_STRIKE);
	coordstyle = pdtfwrk->style.oulcoord;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_VG_COORD);
	vert = pdtfwrk->style.vert;
	mvUp = (DT_VGtype)pwrk->linemoveYup;
	mvLf = (DT_VGtype)pwrk->linemoveXlf;

	if(w_sk<=0 || !pdtfwrk->style.is_strike)
		return DT_SUCCESS;

	if(pdtfwrk->style.f_edge==DT_STYLE_BOLD || pdtfwrk->style.f_edge==DT_STYLE_OUTLINE){
		boldw = (DT_VGtype)pdtfwrk->style.w_edge;
		bEdge = DT_TRUE;
	}else{
		boldw = 0;
		bEdge = DT_FALSE;
	}
	
#ifdef DT_VERT_BY_OVG
	if(vert){
		vert = pwrk->vert;		// should be 0. force this to draw underline correctly.
	}
#endif
	
	if(vert){
		DT_VGtype starty;		//VGfloat starty;
		skpos = (DT_VGtype)((-p_sk-(DT_VGtype)w_sk/2)*gDT_FONT_EMSIZE/szX);	// DT_COORD_LEFT_TOP also the same.
		skpos -= mvUp;
		thick = (DT_VGtype)(w_sk * gDT_FONT_EMSIZE / szX);
		if(bEdge){
			height -= (DT_VGtype)(boldw * 2 * gDT_FONT_EMSIZE / szY);
		}
		if(coordstyle==DT_COORD_LEFT_TOP){
			starty = origin[1] + height;
			segsnum = makerectlineLT((DT_VGtype)(origin[0] + skpos - thick/2), starty, thick, (DT_VGtype)-height, Segs, Coords);
		}else{
			starty = origin[1] + gDT_FONT_EMSIZE;
			segsnum = makerectlineLB((DT_VGtype)(origin[0] + skpos - thick/2), starty, thick, (DT_VGtype)-height, Segs, Coords);
		}
	}else{
		thick = (DT_VGtype)(w_sk * gDT_FONT_EMSIZE / szY);
		if(bEdge){
			width -= (DT_VGtype)(boldw * 2 * gDT_FONT_EMSIZE / szX);
		}
		if(coordstyle==DT_COORD_LEFT_TOP){
			skpos = (DT_VGtype)((szY+(-p_sk+(DT_VGtype)w_sk/2))*gDT_FONT_EMSIZE/szY);
			skpos -= mvUp;
			segsnum = makerectlineLT((DT_VGtype)(origin[0]+mvLf), (DT_VGtype)(origin[1] + skpos - thick/2), width, thick, Segs, Coords);
		}else{
			skpos = (DT_VGtype)((p_sk-(DT_VGtype)w_sk/2)*gDT_FONT_EMSIZE/szY);
			skpos += mvUp;
			segsnum = makerectlineLB((DT_VGtype)(origin[0]+mvLf), (DT_VGtype)(origin[1] + skpos - thick/2), width, thick, Segs, Coords);
		}
	}

	//if(segsnum > 0)		// no need to check, because segsnum always = 6.
	vgAppendPathData(strpath, segsnum, Segs, (DT_VGtype*)Coords);

	return DT_SUCCESS;
}

/*--------------------------------------------------------------------------*/
/* Check if the ucs_str had been cached?									*/
/* Return Value: !=0:string path; VG_INVALID_HANDLE:error					*/
VGPath chkL3Cache(pDT_Fontwrk pdtfwrk, DT16_ushort* ucs_str, DT32_int ucs_cnt)
{
	DT16_ushort height, style, others, vert;
	CacheUnit *unit;
	pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;
	
DBG_MSG_SHOW_FUNC_NAME();

	vert = (DT16_ushort)pdtfwrk->style.vert;
#ifdef DT_VERT_BY_OVG
	vert = (DT16_ushort)pwrk->vert;	// overwrite it. vert will be done by rotate by OpenVG
#endif

	// FIXME: altfont's fid won't be logged. Don't distinguish fid now.
	// 20110907: Jacky modified for L3 Cache, because style_others is used for the string address inside.
	height= MakeOVGCacheStyleValue( (DT16_ushort)pdtfwrk->font->fid, (DT16_ushort)pdtfwrk->style.oulcoord, 
									(DT16_ushort)pdtfwrk->style.bidirule, (DT16_ushort)vert);
	style = 0;
	others= MakeOVGCacheOthersValue();

	unit = GetFromCache(&pdtfwrk->cachearrL3, ucs_str[0], (DT16_short)ucs_cnt, height, style, others);
	if(unit){
		return (VGPath)unit->extra.infoL3.hVGPath;
	}

	return VG_INVALID_HANDLE;
}

DT32_int addToL3Cache(pDT_Fontwrk pdtfwrk, DT16_ushort* ucs_str, DT32_int ucs_cnt, VGPath hVGPath)
{
	DT16_ushort height, style, others, vert;
	CacheUnit cu;
	pLayWrk pwrk = (pLayWrk)pdtfwrk->hShaper;
	
DBG_MSG_SHOW_FUNC_NAME();

	vert = (DT16_ushort)pdtfwrk->style.vert;
#ifdef DT_VERT_BY_OVG
	vert = (DT16_ushort)pwrk->vert;	// overwrite it. vert will be done by rotate by OpenVG
#endif


	// FIXME: altfont's fid won't be logged. Don't distinguish fid now.
	// 20110907: Jacky modified for L3 Cache, because style_others is used for the string address inside.
	height= MakeOVGCacheStyleValue( (DT16_ushort)pdtfwrk->font->fid, (DT16_ushort)pdtfwrk->style.oulcoord, 
									(DT16_ushort)pdtfwrk->style.bidirule, (DT16_ushort)vert);
	style = 0;
	others= MakeOVGCacheOthersValue();
	
	cu.width = (DT16_ushort)ucs_cnt;
	cu.height= height;
	cu.style = style;
	cu.others= others;
	cu.extra.infoL3.hVGPath = (DT32_uint)hVGPath;
	cu.data  = (DT8_uchar*)ucs_str;

	return AddToCache(&pdtfwrk->cachearrL3, ucs_str[0], (DT16_ushort)ucs_cnt, height, &cu);
}

DT32_int PrepareTmpPath(pDT_Fontwrk pdtfwrk)
{
	DT32_int	ret;
	VGuint		nSegsHint = 0 * gDT_MAX_SEGS_PER_GLYPH;
	VGuint		nDataHint = 0 * gDT_MAX_SEGS_PER_GLYPH*2*2;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pdtfwrk->mytmppath_str){
		pdtfwrk->mytmppath_str = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
				1.0f, 0.0f, nSegsHint*DT_MAX_GLYPHS_PER_STR, nDataHint*DT_MAX_GLYPHS_PER_STR, VG_PATH_CAPABILITY_ALL);
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_str){
			pdtfwrk->mytmppath_str = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
									1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		}
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_str){
			ret = DT_VG_CREATEPATH_ERR;
			goto Release_mytmppath;
		}
	}
//	else{		// clear only when it will be used.
//		vgClearPath(pdtfwrk->mytmppath_str,VG_PATH_CAPABILITY_ALL);
//	}

	if(!pdtfwrk->mytmppath_strEM){
		pdtfwrk->mytmppath_strEM = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
				1.0f, 0.0f, nSegsHint*DT_MAX_GLYPHS_PER_STR, nDataHint*DT_MAX_GLYPHS_PER_STR, VG_PATH_CAPABILITY_ALL);
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_strEM){
			pdtfwrk->mytmppath_strEM = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
									1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		}
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_strEM){
			ret = DT_VG_CREATEPATH_ERR;
			goto Release_mytmppath;
		}
	}
//	else{		// clear only when it will be used.
//		vgClearPath(pdtfwrk->mytmppath_str,VG_PATH_CAPABILITY_ALL);
//	}

	if(!pdtfwrk->mytmppath_glyph){
		pdtfwrk->mytmppath_glyph = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
											1.0f, 0.0f, nSegsHint, nDataHint, VG_PATH_CAPABILITY_ALL);
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_glyph){
			pdtfwrk->mytmppath_glyph = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
									1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		}
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_glyph){
			ret = DT_VG_CREATEPATH_ERR;
			goto Release_mytmppath;
		}
	}
//	else{		// clear only when it will be used.
//		vgClearPath(pdtfwrk->mytmppath_glyph,VG_PATH_CAPABILITY_ALL);
//	}

	if(!pdtfwrk->mytmppath_glyph00){
		pdtfwrk->mytmppath_glyph00 = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
											1.0f, 0.0f, nSegsHint, nDataHint, VG_PATH_CAPABILITY_ALL);
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_glyph00){
			pdtfwrk->mytmppath_glyph00 = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
									1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		}
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_glyph00){
			ret = DT_VG_CREATEPATH_ERR;
			goto Release_mytmppath;
		}
	}
//	else{		// clear only when it will be used.
//		vgClearPath(pdtfwrk->mytmppath_glyph00,VG_PATH_CAPABILITY_ALL);
//	}
	return DT_SUCCESS;

Release_mytmppath:

	if(VG_INVALID_HANDLE != pdtfwrk->mytmppath_str){
		vgDestroyPath(pdtfwrk->mytmppath_str);
		pdtfwrk->mytmppath_str = VG_INVALID_HANDLE;
	}
	if(VG_INVALID_HANDLE != pdtfwrk->mytmppath_strEM){
		vgDestroyPath(pdtfwrk->mytmppath_strEM);
		pdtfwrk->mytmppath_strEM = VG_INVALID_HANDLE;
	}
	if(VG_INVALID_HANDLE != pdtfwrk->mytmppath_glyph){
		vgDestroyPath(pdtfwrk->mytmppath_glyph);
		pdtfwrk->mytmppath_glyph = VG_INVALID_HANDLE;
	}
	if(VG_INVALID_HANDLE != pdtfwrk->mytmppath_glyph00){
		vgDestroyPath(pdtfwrk->mytmppath_glyph00);
		pdtfwrk->mytmppath_glyph00 = VG_INVALID_HANDLE;
	}
	return ret;
}

DT32_int PrepareStrTmpPath(pDT_Fontwrk pdtfwrk)
{
	VGuint		nSegsHint = 0 * gDT_MAX_SEGS_PER_GLYPH;
	VGuint		nDataHint = 0 * gDT_MAX_SEGS_PER_GLYPH*2*2;

DBG_MSG_SHOW_FUNC_NAME();

	if(pdtfwrk->mytmppath_str){
		vgDestroyPath(pdtfwrk->mytmppath_str);
		pdtfwrk->mytmppath_str = VG_INVALID_HANDLE;
	}
	if(!pdtfwrk->mytmppath_str){

		pdtfwrk->mytmppath_str = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
				1.0f, 0.0f, nSegsHint*DT_MAX_GLYPHS_PER_STR, nDataHint*DT_MAX_GLYPHS_PER_STR, VG_PATH_CAPABILITY_ALL);
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_str){
			pdtfwrk->mytmppath_str = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
									1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		}
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_str){
			return DT_VG_CREATEPATH_ERR;
		}
	}
	
	if(pdtfwrk->mytmppath_strEM){
		vgDestroyPath(pdtfwrk->mytmppath_strEM);
		pdtfwrk->mytmppath_strEM = VG_INVALID_HANDLE;
	}
	if(!pdtfwrk->mytmppath_strEM){

		pdtfwrk->mytmppath_strEM = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
				1.0f, 0.0f, nSegsHint*DT_MAX_GLYPHS_PER_STR, nDataHint*DT_MAX_GLYPHS_PER_STR, VG_PATH_CAPABILITY_ALL);
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_strEM){
			pdtfwrk->mytmppath_strEM = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
									1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		}
		if(VG_INVALID_HANDLE == pdtfwrk->mytmppath_strEM){
			return DT_VG_CREATEPATH_ERR;
		}
	}
	return DT_SUCCESS;
}

DT32_int DT_GetOVGPath(pDT_Fontwrk pdtfwrk, DT16_ushort *ucs_str, DT32_int ucs_cnt, pDT_OulBuf oulbuf, VGPath *hstrpath)
{
	DT32_int ret;
	VGPath strpathEM;
	
DBG_MSG_SHOW_FUNC_NAME();

	//*hstrpath = VG_INVALID_HANDLE;
	strpathEM = VG_INVALID_HANDLE;

	/* Check L3 Cache: string VGPath cache */
	if(pdtfwrk->usedcacheL3){
		strpathEM = chkL3Cache(pdtfwrk, ucs_str, ucs_cnt);
	}
	if(VG_INVALID_HANDLE == strpathEM){
		if(pdtfwrk->usedcacheL3){
			VGuint		nSegsHint = 0 * gDT_MAX_SEGS_PER_GLYPH;
			VGuint		nDataHint = 0 * gDT_MAX_SEGS_PER_GLYPH*2*2;
			/* create a paht for srcpath */
			strpathEM = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
								  1.0f, 0.0f, nSegsHint*DT_MAX_GLYPHS_PER_STR, nDataHint*DT_MAX_GLYPHS_PER_STR, VG_PATH_CAPABILITY_ALL);
			if(strpathEM == VG_INVALID_HANDLE){
				strpathEM = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
								  1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
				if(strpathEM == VG_INVALID_HANDLE)
					return DT_VG_CREATEPATH_ERR;
			}
			ret = makeGlyphsPathByCache(pdtfwrk,oulbuf,strpathEM);
			if( ret<0 ){	/* Nothing in the path, close it. */
				return ret;
			}
			//if(pdtfwrk->usedcacheL3 && VG_INVALID_HANDLE!=strpathEM)
				addToL3Cache(pdtfwrk,ucs_str,ucs_cnt,strpathEM);
			if(*hstrpath == VG_INVALID_HANDLE){
				*hstrpath = strpathEM;
			}else{
				vgAppendPath(*hstrpath, strpathEM);
			}
			
		}else{
			if(*hstrpath == VG_INVALID_HANDLE){
				strpathEM = pdtfwrk->mytmppath_strEM;
			}else{
				strpathEM = *hstrpath;				// append path data directly!
			}
			ret = makeGlyphsPathByCache(pdtfwrk,oulbuf,strpathEM);
			if( ret<0 ){	/* Nothing in the path, close it. */
				return ret;
			}
			// No matter if *hstrpath is invalid or not, force set it.
			*hstrpath = strpathEM;
		}
	}else{
		// found by L3 cache.
		if(*hstrpath == VG_INVALID_HANDLE){
			*hstrpath = strpathEM;
		}else{
			vgAppendPath(*hstrpath, strpathEM);		// won't get here!!
		}
	}

	return DT_SUCCESS;
}

DT32_int DT_DelOVGPath(pDT_Fontwrk pdtfwrk, VGPath hstrpath)
{
DBG_MSG_SHOW_FUNC_NAME();

	vgDestroyPath(hstrpath);
	return DT_SUCCESS;
}

DT32_int fastInfoforOVG(pDT_Fontwrk pdtfwrk, DT16_ushort* ucs_str, DT32_int ucs_cnt, pDT_OulBuf *pbuf)
{
	DT32_int		i, aw, spacing, pixwidth, pixheight;
	pDT_OulBuf		dtoul = (pDT_OulBuf) pdtfwrk->rtbuffer;
	pLayWrk			pwrk = (pLayWrk) pdtfwrk->hShaper;
	DLO_LayAttr		*layattr = (DLO_LayAttr*)pdtfwrk->dlolayattr;
	DLO_LayBuf		*dlolay= pdtfwrk->dlolaybuf;
	DT_OulPos		*carets = pdtfwrk->oulcarets;
	DT32_int		ret=DT_SUCCESS, bEmpty=0, bBreak=0;

	/* OVG don't require re-initFont. */
//	ret = ReInitFont(pwrk);
//	ret = convReturnValue(ret);
//	if(DT_SUCCESS != ret)
//		return ret;

	// layattr is used for L3 cache
	layattr->mainScript	= DLO_SCRIPT_DFLT;
	layattr->mainLang	= DLO_LANG_DFLT;
	layattr->ucs_cnt	= ucs_cnt;
	layattr->ucs_str	= ucs_str;
	layattr->writedir	= pdtfwrk->style.writedir;
	
	aw = 0;
	dlolay->eswidth  = 0;
	dlolay->esheight = pwrk->fengfuncs.getHeight(pwrk->ras_attr);	// No scale FDL, can use this func.
	pixwidth  = 0;
	pixheight = DLO_CALC_AW_AH(dlolay->esheight, pdtfwrk->style.ysize);
	for(i=0; i<ucs_cnt; i++){
		if(pdtfwrk->lastreturn < 0)
			pwrk->g2info[i].checkedFlag = 0;									// be sure it's the first call.
		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, ucs_str[i], i);
		fastFillingDT_OulPos((DT16_ushort)i, dlolay->eswidth, aw, &carets[i]);
		dlolay->eswidth += aw;
		pixwidth += DLO_CALC_AW_AH(aw,pdtfwrk->style.xsize);
		//if(0==aw){
		//	//ret |= DT_WARNING_EMPTY_FONT;
		//	bEmpty = 1;
		//}
		if(!pwrk->g2info[i].codeExist){
			if(!DT_isCode_NoEmptyFontWarning(ucs_str[i],NULL)){
				bEmpty = 1;
			}
		}
		if(ucs_str[i]==0x0A || ucs_str[i]==0x0D){							// only these 2 codes will get into FastMode.
			if(pdtfwrk->style.bidirule==DT_BIDI_UNIRULE){
				bBreak = 1;
				i++;
				break;
			}
		}
	}

	dlolay->glyf_cnt = i;
	DT_memcpy(dlolay->glyf_seq, ucs_str, dlolay->glyf_cnt*sizeof(ucs_str[0]));
	if(gDT_OVGWidth_Based_on_GBMPWidth && gDT_EachGlyphWidth_on_Pixels){
		// 2012-05-24: offset the origin position x to fill out the rect.
		DT_VGtype sRatio;
		sRatio = (DT_VGtype)dlolay->eswidth * pdtfwrk->style.xsize / gDT_FONT_EMSIZE;
		for(i=0; i<dlolay->glyf_cnt; i++){
			carets[i].oripos.x = (DT32_int)(carets[i].oripos.x * pixwidth / sRatio);
			carets[i].caretpos.x = (DT32_int)(carets[i].caretpos.x * pixwidth / sRatio);
		}
	}
	//vext = pwrk->fengfuncs.getVexten(pwrk->ras_attr, 0x0000);
	//hext = pwrk->fengfuncs.getAexten(pwrk->ras_attr, 0x0000);
	spacing = (pwrk->spacing*gDT_FONT_EMSIZE)/pwrk->xsize;
	if(dlolay->eswidth > 0){
		if(spacing < 0)
			dlolay->eswidth += -spacing;
	}
	
	dtoul->gcnt		= dlolay->glyf_cnt;
	dtoul->glyphs	= (DT16_ushort*) dlolay->glyf_seq;
	dtoul->writedir = DT_LEFTTORIGHT;
	dtoul->eswidth  = dlolay->eswidth;
	dtoul->esheight = dlolay->esheight;
	dtoul->olbuf    = NULL;
	dtoul->olbufsize= 0;
	dtoul->olsizes  = NULL;
	dtoul->carets	= carets;
	dtoul->pixwidth = pixwidth;
	dtoul->pixheight= pixheight;

	if(pbuf)
		*pbuf = dtoul;

	if(bEmpty)
		ret |= DT_WARNING_EMPTY_FONT;
	if(bBreak && dlolay->glyf_cnt!=ucs_cnt)
		ret |= DT_WARNING_BREAKLINE;
	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* This function is valid only if mode=DT_OUTLINE_MODE when DT_CreateFont() */
/* Return: 0:DT_SUCCESS; <0:error											*/
DT32_int DT_RasterPathforOVG(pDT_Fontwrk pdtfwrk, 
			  DT16_ushort*	ucs_str,		/* the string to be drawn											*/
			  DT32_int		ucs_cnt,		/* count of ucs_str													*/
			  DT32_uint		*hPath,			/* the result VGPath for ucs_str when this func returned.											*/
											/* can NOT be NULL.																					*/
  			  DT_StrInfo	*info			/* the string info when return.	*/
			  )
{
	DT_Handle	hnd = (DT_Handle) pdtfwrk;
	VGPath		*hndstrpath = (VGPath*)hPath;
	pDT_OulBuf	oulbuf=NULL;
	DT32_int	ret, rtval=DT_SUCCESS;
	DT32_int	coords, f_edge, w_edge;
	DT_VGtype	stkw, w, h;					//VGfloat		stkw, w, h;		// VGfloat for accuracy

	VGPath		srcpath,dstpath,newsrc,pempath;	//pempath is used as a pointer.
	VGint		matrixmode;
	VGfloat		matrix[9];
	DT_VGtype	origin[2];					//VGfloat		origin[2];
	pDT_FontMgr_wrk pmgrwrk;
	VGboolean	bTmpUline, bTmpStrike;
	pLayWrk		pwrk;
	DT_BOOL		bReturnEMPath = DT_FALSE;

DBG_MSG_SHOW_FUNC_NAME();
	
	if(!pdtfwrk)
		return DT_BAD_FONT_HANDLE;

	if(pdtfwrk->engtype!=DLO_ENG_DCWOPENVG){
		return DT_CREATEFONT_MODE_ERR;
	}

	if(!ucs_str || ucs_cnt<=0 || ucs_cnt>DT_MAX_STRING_LENGTH){
		return DT_UCS_STR_TOO_LONG;
	}

	pmgrwrk = (pDT_FontMgr_wrk)pdtfwrk->fontmgr;
	if(!pmgrwrk)
		return DT_BAD_FONT_HANDLE;
	
	if(!pmgrwrk->tempbuf || pmgrwrk->tmpbufsize<gDT_MAX_OUL_SIZE_PER_GLYPH || pmgrwrk->tmpbufsize<gDT_MAX_SEGS_PER_GLYPH){
		return DT_TEMP_BUFFER_ERR;
	}

	pwrk = (pLayWrk) pdtfwrk->hShaper;
	if(!pwrk)
		return DT_BAD_FONT_HANDLE;

	// check if it can return VGPath based on EM, take care of Italic, Vert, Underline, Strike, becareful of the L3 Cache.
	if( pdtfwrk->style.gen_empath && !pdtfwrk->style.vert
		&& !pdtfwrk->style.is_italic && pdtfwrk->style.italic==0
		&& !(pdtfwrk->style.is_underline || pdtfwrk->style.w_underline) 
		&& !(pdtfwrk->style.is_strike || pdtfwrk->style.w_strike) 
		)
	{
		bReturnEMPath = DT_TRUE;
	}
	

	/* Keep some info */
	matrixmode = vgGeti(VG_MATRIX_MODE);
	vgGetMatrix(matrix);

	/* Get string position info */
	if(pdtfwrk->lastreturn >= 0/*DT_SUCCESS*/ && isStrTheSame(ucs_str, ucs_cnt, pdtfwrk->laststr, pdtfwrk->laststrlen)){
		if( pdtfwrk->bFastMode ){	// bFastMode should be checked in DT_GetTextRect()
			rtval = fastInfoforOVG(pdtfwrk, ucs_str, ucs_cnt, &oulbuf);	// still need to call this for something like DLO_LayAttr, DLO_LayBuf...
		}else{
			oulbuf = (pDT_OulBuf) pdtfwrk->rtbuffer;
			rtval = pdtfwrk->lastreturn;
		}
	}else{
		pdtfwrk->lastreturn = DT_DEFAULT_LASTRETURN;
		pdtfwrk->bFastMode = isFastMode(pdtfwrk, ucs_str, ucs_cnt);
		if( pdtfwrk->bFastMode ){
			rtval = fastInfoforOVG(pdtfwrk, ucs_str, ucs_cnt, &oulbuf);
		}else{
			ret = DT_RasterOUL(hnd, ucs_str, ucs_cnt, DT_GET_INFO, &oulbuf);
			rtval = convReturnValue(ret);
			if(rtval < 0){
				DT_RasterOUL(hnd, ucs_str, ucs_cnt, DT_RELEASE, &oulbuf);
				return rtval;
			}
		}
		// don't set these values to speed up, because the hit rate will very low.
		//pdtfwrk->lastreturn = rtval;
		//pdtfwrk->laststrlen	= ucs_cnt;
		//DT_memcpy(pdtfwrk->laststr, ucs_str, ucs_cnt*sizeof(ucs_str[0]));
	}

	//*hndstrpath = VG_INVALID_HANDLE;	// 20110907: Jacky Marked for the VGPath user created.

	/* Set the matrix mode to be used, reduce the times of this func call.  */
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	vgLoadIdentity();

#ifdef DT_DESTROY_VGPATH_EVERYTIME
	ret = PrepareStrTmpPath(pdtfwrk);
	if(ret < 0){
		return ret;
	}
	// no need to clear the path, because it's newly created.
#else
	/* Create mytmppath for later use. */
	ret = PrepareTmpPath(pdtfwrk);
	if(ret < 0){
		return ret;
	}
	// clear the VGPath of the string to return.
	vgClearPath(pdtfwrk->mytmppath_str,VG_PATH_CAPABILITY_ALL);
	vgClearPath(pdtfwrk->mytmppath_strEM,VG_PATH_CAPABILITY_ALL);
#endif // DT_DESTROY_VGPATH_EVERYTIME

	/* Get string VGPath: srcpath */
	if(bReturnEMPath)
		srcpath = *hndstrpath;		// might be invalid handle or user own handle!
	else
		srcpath = VG_INVALID_HANDLE;
	ret = DT_GetOVGPath(pdtfwrk, ucs_str, ucs_cnt, oulbuf, &srcpath);
	if(ret < 0){
		rtval = ret;
		goto DT_SET_VG_INFO_BACK;
	}
	/// srcpath here should be ready to do followings.

	// calculate stkw.
	stkw = 0; 
	f_edge = pdtfwrk->style.f_edge;		//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_F_EDGE);
	w_edge = pdtfwrk->style.w_edge;		//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_W_EDGE);
	if(f_edge==DT_STYLE_BOLD || f_edge==DT_STYLE_OUTLINE){
		stkw = (DT_VGtype)w_edge;
	}

	// origin & width, height
	origin[0] = (DT_VGtype)0;	origin[1] = (DT_VGtype)0;	
#ifdef DT_VERT_BY_OVG
	w = (DT_VGtype)oulbuf->eswidth;
	h = (DT_VGtype)oulbuf->esheight;
#else
	w = (DT_VGtype)(pdtfwrk->style.vert?gDT_FONT_EMSIZE:oulbuf->eswidth);
	h = (DT_VGtype)(pdtfwrk->style.vert?oulbuf->esheight:gDT_FONT_EMSIZE);
#endif

	/* make DT_StrInfo for return */
	if(info){
		/* vgPathBounds() only return the really boundary of glyphs,				*/
		/* the height won't be the same even szY is the same.						*/
		/* vgPathBounds() ignores stroke parameters, and width will not include rsb.*/
		//VGfloat minX, minY;
		//VGfloat width, height;
		//vgPathBounds(pdtfwrk->myglyphpath,&minX,&minY,&width,&height);
		//vgPathTransformedBounds(pdtfwrk->myglyphpath,&minX,&minY,&width,&height);

		info->width = (w>0)?(DT32_int)(w+stkw):0;
		info->height= (h>0)?(DT32_int)(h+stkw):0;
		info->gcnt  = oulbuf->gcnt;
		DT_memcpy(info->glyphs,oulbuf->glyphs,oulbuf->gcnt*sizeof(oulbuf->glyphs[0]));
	}

	if(bReturnEMPath){
		*hndstrpath = srcpath;
	}else{
		bTmpUline = pdtfwrk->usedcacheL3 && (pdtfwrk->style.is_underline || pdtfwrk->style.w_underline);
		bTmpStrike= pdtfwrk->usedcacheL3 && (pdtfwrk->style.is_strike || pdtfwrk->style.w_strike);
		/// newsrc is used for L3 cache to avoid cache the underline or strike
		newsrc = VG_INVALID_HANDLE;
		if(bTmpUline || bTmpStrike){
			newsrc = vgCreatePath(VG_PATH_FORMAT_STANDARD, DT_GLYPH_CACHE_PATH_DATATYPE, 
										1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
			if(VG_INVALID_HANDLE == newsrc){
				rtval = DT_VG_CREATEPATH_ERR;
				goto DT_SET_VG_INFO_BACK;
			}
			vgAppendPath(newsrc, srcpath);
			pempath = newsrc;
		}else{
			pempath = srcpath;
		}

#if(1)
		// w & h are used here only, not use any more in the following process.
		if(w>0 && h>0){
			if(gDT_OVGWidth_Based_on_GBMPWidth && gDT_EachGlyphWidth_on_Pixels){
				DT_VGtype sRatio;			// 2012-05-24: scale to fill all the rect (which is the same with the gray bmp's rect)
				sRatio = (DT_VGtype)pdtfwrk->oulbuf->eswidth*pdtfwrk->style.xsize/gDT_FONT_EMSIZE;
				w = w * pdtfwrk->oulbuf->pixwidth / sRatio;
			}
			w += stkw;
			h += stkw;
			addUnderline(pdtfwrk, pempath, origin, (DT_VGtype)w, (DT_VGtype)h);
			addStrike(pdtfwrk, pempath, origin, (DT_VGtype)w, (DT_VGtype)h);
		}
#else
		if(w>0)
			w += stkw;
		if(h>0)
			h += stkw;
		if(w>0 && h>0){
			addUnderline(pdtfwrk, pempath, origin, (DT_VGtype)w, (DT_VGtype)h);
			addStrike(pdtfwrk, pempath, origin, (DT_VGtype)w, (DT_VGtype)h);
		}
#endif
		/* Set some attributes to new value. */
		//vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);	// 2012-01-19: not required, setted above.
		vgLoadIdentity();

		// scale to specified size
		/* Set required font style */
		if(!pdtfwrk->style.gen_empath){
			VGfloat		szX, szY;
			szX = (VGfloat)pdtfwrk->style.xsize/gDT_FONT_EMSIZE;		//DT_GetFontStyle(hnd,DT_FSTYLE_SIZEX)/gDT_FONT_EMSIZE;
			szY = (VGfloat)pdtfwrk->style.ysize/gDT_FONT_EMSIZE;		//DT_GetFontStyle(hnd,DT_FSTYLE_SIZEY)/gDT_FONT_EMSIZE;
			vgScale(szX, szY);
		}
			
		// italic
		coords = pdtfwrk->style.oulcoord;	//DT_GetFontStyle(pdtfwrk,DT_FSTYLE_VG_COORD);
		if(DT_COORD_LEFT_TOP == coords){		
			if(pdtfwrk->style.is_italic || pdtfwrk->style.italic!=0){
				// pdtfwrk->style.italic will also be set at DT_SetFontStyle() when is_italic is true.
				if(pdtfwrk->style.vert){
					vgShear(0.0f,(VGfloat)pdtfwrk->style.italic/pdtfwrk->style.xsize);
				}else{
					vgShear((VGfloat)pdtfwrk->style.italic/pdtfwrk->style.ysize,0.0f);
				}
			}
		}else{	//DT_COORD_LEFT_BOT
			if(pdtfwrk->style.is_italic || pdtfwrk->style.italic!=0){
				// pdtfwrk->style.italic will also be set at DT_SetFontStyle() when is_italic is true.
				if(pdtfwrk->style.vert){
					vgShear(0.0f,-(VGfloat)pdtfwrk->style.italic/pdtfwrk->style.xsize);
				}else{
					vgShear((VGfloat)pdtfwrk->style.italic/pdtfwrk->style.ysize,0.0f);
				}
			}
		}
		
	#ifdef DT_VERT_BY_OVG
		if(pdtfwrk->style.vert){
			if(DT_COORD_LEFT_TOP == coords){
				vgRotate(90);
			}else{		// DT_COORD_LEFT_BOT
				vgRotate(-90);
			}
		}
	#endif

		// prepare the path for return.
		if(VG_INVALID_HANDLE == *hndstrpath)			// 20110907: Jacky modified for the VGPath user created.
			dstpath = pdtfwrk->mytmppath_str;
		else
			dstpath = *hndstrpath;
		vgTransformPath(dstpath,pempath);

		if(newsrc != VG_INVALID_HANDLE){
			vgDestroyPath(newsrc);
			newsrc = VG_INVALID_HANDLE;
		}

		if(VG_INVALID_HANDLE == *hndstrpath)		// 20110907: Jacky modified for the VGPath user created. 
			*hndstrpath = dstpath;
	}
	
DT_SET_VG_INFO_BACK:
	// Set the info back
	vgSeti(VG_MATRIX_MODE, matrixmode);
	vgLoadMatrix(matrix);

	/* Release something */	// 2011-11-11: don't release the data.
//	DT_RasterOUL(hnd, ucs_str, ucs_cnt, DT_RELEASE, &oulbuf);

	// Destroy srcpath isn't required now, because mytmppath_strEM is used and 
	// it will be destroyed when DT_DestroyFont() when L3 cache off,
	// or it will be destroyed when removing out of L3 cache. (L3 Cache on)
//	if(!pdtfwrk->usedcacheL3 && srcpath!=VG_INVALID_HANDLE && !bReturnEMPath)
//		DT_DelOVGPath(pdtfwrk,srcpath);

	return rtval;
}

/* This function is used to get a VGPath(hndstrpath) for ucs_str, valid only when DT_OUTLINE_MODE mode.		*/
/* Return: 0:DT_SUCCESS; <0:error																			*/
DT32_int DT_RasterOVGPath(DT_Handle hnd, 
			  DT16_ushort* ucs_str,		/* the string to be drawn											*/
			  DT32_int	ucs_cnt,		/* count of ucs_str													*/
			  VGPath	*hndstrpath		/* the result VGPath for ucs_str when this func returned.			*/
										/* can NOT be NULL.													*/
/*			  DT_StrInfo	*info*/		/* the string info when return.										*/
			  )
{
	return DT_RasterPathforOVG((pDT_Fontwrk)hnd, ucs_str, ucs_cnt, (DT32_uint*)hndstrpath, NULL);
}

DT32_int DT_StrokeOVGPathByMask(DT_Handle hnd, VGPath hndstrpath)
{
	VGfloat x, y, w, h;
	VGfloat stkw = vgGetf(VG_STROKE_LINE_WIDTH);
	pDT_Fontwrk pdtfwrk = (pDT_Fontwrk)hnd;

	if(pdtfwrk){
		if(pdtfwrk->style.gen_empath){
			stkw = stkw * pdtfwrk->style.ysize / gDT_FONT_EMSIZE;
		}
	}// else ;	// this function still workable. The mask rect will be larger than the real rect if DT_FSTYLE_VG_GEN_EMPATH is set.

	vgPathTransformedBounds(hndstrpath,&x,&y,&w,&h);
#if 0  /* Panasonic removed vgMasking for GV200 */
	vgSeti(VG_MASKING, VG_TRUE);
	vgMask(VG_INVALID_HANDLE,VG_FILL_MASK,(VGint)(x-stkw),(VGint)(y-stkw),(VGint)(w+stkw),(VGint)(h+stkw));	
	vgRenderToMask(hndstrpath, VG_FILL_PATH, VG_SUBTRACT_MASK);
#endif
	vgDrawPath(hndstrpath, VG_STROKE_PATH);
#if 0  /* Panasonic removed vgMasking for GV200 */
	vgSeti(VG_MASKING, VG_FALSE);
#endif

	return DT_SUCCESS;
}

#endif	//(1==DT_OPENVG_ENABLED)

#ifdef DT_ANDROID
// ============================================================================
// ================= (c) Copyright 2010 DynaCW DigiType =======================
// ============================================================================

typedef enum {
	XIsolated=0,
	XFinal,
	XInitial,
	XMedial,
	XCausing,
	XTransparent,
	XShapeEnd
} ArabicShape;

/* Join type: JType_U, D, R are very usually in Arabic. */
typedef enum {
	JType_U=0,	/*Non-Joining*/
	JType_C,	/*Join-Causing*/
	JType_D,	/*Dual-Joining*/
	JType_R,	/*Right-Joining*/
	JType_T,	/*Transparent*/
	JType_L		/*Left-Joining*/	/*Never Occurs in Unicode Standard*/
} JoinType;

/* Arabic letter group: Each group has one or some letters. */
typedef enum {
	/* NonJoining */
	ArabicNone=0,
	ArabicSpace,

	/* Transparent */
	Transparent,

	/* Causing */
	Center,
	Tatweel,/*Kashida*/

	/* Arabic */
	/* Dual */
	Beh,
	Noon,
	Meem,
	Heh,
	KnottedHeh,
	HehGoal,
	SwashKaf,
	Yeh,
	Hah,
	Seen,
	Sad,
	Tah,
	Kaf,
	Gaf,
	Lam,
	Ain,
	Feh,
	Qaf,

	/* Right */
	Alef,
	Waw,
	Dal,
	TehMarbuta,
	Reh,
	HamzaOnHehGoal,
	YehWithTail,
	YehBarree,
	ArabicGroupsEnd
} ArabicGroup;

static const JoinType _ArabicGroupType[ArabicGroupsEnd] =  {
	/* NonJoining */
	JType_U,	/*ArabicNone*/
	JType_U,	/*ArabicSpace*/

	/* Transparent */
	JType_T,	/*Transparent*/

	/* Causing */
	JType_C,	/*Center*/
	JType_C,	/*Tatweel*/

	/* Arabic */
	/* Dual */
	JType_D,	/*Beh*/
	JType_D,	/*Noon*/
	JType_D,	/*Meem*/
	JType_D,	/*Heh*/
	JType_D,	/*KnottedHeh*/
	JType_D,	/*HehGoal*/
	JType_D,	/*SwashKaf*/
	JType_D,	/*Yeh*/
	JType_D,	/*Hah*/
	JType_D,	/*Seen*/
	JType_D,	/*Sad*/
	JType_D,	/*Tah*/
	JType_D,	/*Kaf*/
	JType_D,	/*Gaf*/
	JType_D,	/*Lam*/
	JType_D,	/*Ain*/
	JType_D,	/*Feh*/
	JType_D,	/*Qaf*/

	/* Right */
	JType_R,	/*Alef*/
	JType_R,	/*Waw*/
	JType_R,	/*Dal*/
	JType_R,	/*TehMarbuta*/
	JType_R,	/*Reh*/
	JType_R,	/*HamzaOnHehGoal*/
	JType_R,	/*YehWithTail*/
	JType_R		/*YehBarree*/
};

typedef enum
{
	DL_Not_In_Range,
	DL_Range_INHERIT,
	DL_Range_Special,
	DL_Range_Latin,
	DL_Range_Greek=DL_Range_Latin,		/* temporary	*/
	DL_Range_Cyrillic=DL_Range_Latin,	/* temporary	*/
	DL_Range_Armenian=DL_Range_Latin,	/* temporary	*/
	DL_Range_Thai,						
	DL_Range_Georgian,					/* not support	*/
	DL_Range_Runic,						/* not support	*/
	DL_Range_Ogham,						/* not support	*/
	DL_Range_Arabic,
	DL_Range_Hebrew,					
	DL_Range_Syriac,					/* not support	*/
	DL_Range_Thaana,					/* not support	*/
	DL_Range_Han,						/* not support	*/
	DL_Range_Bopomofo,					/* not support	*/
	DL_Range_Devanagari,
	DL_Range_Tamil
} DL_CodeRange;

#define MAX_LIG_COMPONENTS 19

#define IS_ARABIC_HONORIFICS(x)		(((x)>=0x0610 && (x)<=0x0615) ? 1 : 0)
#define IS_ARABIC_POINTS(x)			((((x)>=0x064B && (x)<=0x0652) || (x)==0x0670) ? 1 : 0)	
#define IS_ARABIC_HAMZA(x)			((((x)>=0x0653 && (x)<=0x0655) || (x)==0x0674) ? 1 : 0)
#define IS_ARABIC_KORANIC_ANNO(x)	((((x)>=0x06D6 && (x)<=0x06DC) || ((x)>=0x06DF && (x)<=0x06E8) || ((x)>=0x06EA && (x)<=0x06ED)) ? 1 : 0)

#define IS_ARABIC_ZEROWIDTH(x)	( (IS_ARABIC_HONORIFICS(x) || IS_ARABIC_POINTS(x) || IS_ARABIC_HAMZA(x) || IS_ARABIC_KORANIC_ANNO(x)) ? 1 : 0 )

/**** Script ****/
#define DT_CODE_DIR_NOT_SPECIFIED	0x00	/* Not specified											*/
#define DT_CODE_ASCII_PUNCT			0x01	/* like the punctuations in ascii							*/
#define DT_CODE_ASCII_PAIR_OPEN		0x02	/* like punct, but something different, Ex: 0x28, 0x5B, 0x7B*/
#define DT_CODE_ASCII_PAIR_CLOSE	0x03	/* like punct, but something different, Ex: 0x29, 0x5D, 0x7D*/
#define DT_CODE_DIR_AS_LATIN		0x04	/* Left to Right */
#define DT_CODE_DIR_AS_ARABIC		0x05	/* Right to Left */

//#include "DcwShaperDLO.h"
//extern unsigned char dlodata[];

typedef enum 
{
	DL_NoCategory,

	DL_Mark_NonSpacing,          /*   Mn */
	DL_Mark_Enclosing,           /*   Me */
	DL_Mark_SpacingCombining,    /*   Mc */

	DL_Separator_Space,          /*   Zs */

	DL_Other_Control,            /*   Cc */
	DL_Other_Format,             /*   Cf */

	DL_Number_DecimalDigit,      /*   Nd */

	DL_Letter_Uppercase,         /*   Lu */
	DL_Letter_Lowercase,         /*   Ll */
	DL_Letter_Modifier,          /*   Lm */
	DL_Letter_Other,             /*   Lo */

	DL_Punctuation_Open,         /*   Ps */
	DL_Punctuation_Close,        /*   Pe */
	DL_Punctuation_Other,        /*   Po */

	DL_Symbol_Currency,          /*   Sc */

	DL_Symbol_Other              /*   So */

} DL_CodeCategory;

#ifndef __DTDIGITYPE_H

#define DLO_MAXCODES_PER_STR_SEG			1024
#define DLO_SEG_LIMIT	  8

#if 1
typedef void		  DT_void;
typedef long		  DT32_long;
typedef unsigned long DT32_ulong;
typedef int			  DT32_int;
typedef char		  DT8_char;
typedef unsigned char DT8_uchar;
typedef unsigned short DT16_ushort;
#else
typedef void		  DT_void;
typedef long		  DT32_long;
typedef unsigned long DT32_ulong;
typedef int32_t		  DT32_int;
typedef int8_t		  DT8_char;
typedef uint8_t       DT8_uchar;
typedef uint16_t      DT16_ushort;
#endif

typedef enum
{
	DLO_SCRIPT_DFLT=0,	/*Default: Decided by characters*/
	DLO_SCRIPT_latn,	/*Latin	*/
	DLO_SCRIPT_arab,	/*Arabic*/
	DLO_SCRIPT_thai,	/*Thai	*/
	DLO_SCRIPT_deva,    /*Devanagari*/
	DLO_SCRIPT_taml,    /*Tamil*/
	DLO_SCRIPT_hebr,	/*Hebrew*/
	DLO_SCRIPT_END		/*DLO_Script's End. Don't use this value.*/
}DLO_Script;

/**** Languages ****/
/* Please refer to the opentype spec "Language System Tags" for the specific names. */
/* Only DLO_LANG_DFLT, DLO_LANG_LAT, DLO_LANG_ARA, DLO_LANG_THA are valid now. */
typedef enum
{
	DLO_LANG_DFLT=0,	/*Default: Not specified*/
	DLO_LANG_LAT,		/*Latin*/
	DLO_LANG_JAN,		/*Japanese*/
	DLO_LANG_ZHT,		/*Chinese Traditional*/
	DLO_LANG_ZHS,		/*Chinese Simplified*/
	DLO_LANG_ARA,		/*Arabic*/
	DLO_LANG_THA=6,		/*Thai*/
	DLO_LANG_HIN,       /*Hindi*/
	DLO_LANG_TAM,       /*TAM*/
	DLO_LANG_IWR,		/*Hebrew*/
	DLO_LANG_ICN=10,	/*Icon*/
	DLO_LANG_end		/*DLO_Language's End. Don't use this value.*/
}DLO_Language;


typedef struct _DLO_Point
{
	DT32_int x;
	DT32_int y;
}DLO_Point;

typedef struct _DLO_Vector2
{
	DT32_int vx;
	DT32_int vy;
}DLO_Vector2;

typedef struct _DLO_RECT
{
	DLO_Point	xy;
	DLO_Vector2 hw;
}DLO_RECT;

typedef struct _DLO_CodePositioning
{
	DT32_int 	codeidx;
	DT16_ushort	glyfidx;
	DT16_ushort	n_per_glyf;
	DLO_Point	caretpos;
	DLO_Point	oripos;
	DLO_Vector2	awvec;
	DLO_Vector2	adjvec;
	DT32_int	drawmethod;
	DLO_RECT	dmrect;
}DLO_CodePositioning;

#endif // __DTDIGITYPE_H
/*
typedef struct  {
	DT8_char	ident[8];
	DT16_ushort version;
	DT16_ushort dlotabcnt;
	DT32_ulong  *offsetdlotab;
}shaperheader;

typedef struct {
	DT16_ushort script;
	DT16_ushort lang;
	DT16_ushort subtabcnt;
	DT32_ulong  *offsetsubtab;
}dlotabheader;
*/
typedef struct {
	DT16_ushort format;
	DT16_ushort offset2Cover;
	DT16_ushort ligasetcnt;
	DT8_uchar	*ligsetoffset;
}SubLookupTab;

typedef struct {
	ArabicShape prevS;
	ArabicShape thisS;
} JoiningPair;

typedef struct{
	DT16_ushort leadcode;
	DT16_ushort replacelem;
	ArabicShape shape;
	DT16_ushort elementcnt;
	DT16_ushort *combelem;
}ArabicLigature;

typedef struct{
	DT16_ushort		glyf1;
	ArabicGroup		group;
	JoinType		jtype;
	ArabicShape		shape;
}ArabicProperties;

#if 0
typedef struct {
	DT16_ushort format;
	DT16_ushort glyfcnt;
	DT8_uchar *covarr;
}CoverTab1;

typedef struct{
	DT16_ushort	idx;
	DT16_ushort	code;
	DT16_ushort	idx_gseq1;
	DT16_ushort	glyf1;
	DT16_ushort	n_per_glyf1;
	DT16_ushort	idx_gseq2;
	DT16_ushort	glyf2;
	DT16_ushort	n_per_glyf2;
}GlyphSeq;
#endif

typedef struct{
	DT16_ushort		ustart;
	DT16_ushort		uend;
	DLO_Script		script;
	DLO_Language	lang;
	DT32_int		gxstart;
	DT32_int		gxend;

//	DT32_int		sw;			/* seg's width */
//	DT32_int		sh;			/* seg's height*/
//	DLO_Point		cpstart;	/* seg's start point. (where the previous seg ends. Use writedir, seg_dir & sw to get the real start point.) */
	DLO_Point		cpend;		/* seg's end point. (where this seg ends. "cpend" may equal to "cpstart".)*/
}Str_Seg2;

typedef struct  {
	DL_CodeRange range;
	DL_CodeCategory cate;
} DL_CodeAttr;

typedef struct DLO_HANDLE
{
	DLO_Script 	mainScript;	/*Default Script*/
	DLO_Language mainLang;	/*Default Language*/
	DT32_int	writedir;							/* keep the writedir for further use. */
	DT32_int	ucs_cnt;	/*Count of text(ucs_str)*/
	DT16_ushort	*ucs_str;	/*Text to layout, a sequence of unicodes*/

	DT8_uchar	*dlo;
	DT32_ulong	curpos;
	DT32_ulong	dlotaboff[256];
	DT32_ulong	subtaboff[32];
	shaperheader header;
	dlotabheader dloheader;
	DT16_ushort	cur_dlotab_idx;
	DT32_ulong	offtosubtab;

	DT32_int	seg_start;
	DT32_int	seg_end;
	/* Code String Control */
//	DT16_ushort	seg_start;		/* start of the segment (Each segment is divided according the language.) */
//	DT16_ushort	seg_end;		/* end of the segment		*/
	DT16_ushort	seg_dir;		/* direction of the segment */
	DT16_ushort	seg_curpos;		/* current position of the segment */
	DLO_Script	seg_script;		/* script of the segment    */
	DLO_Language seg_lang;		/* language of the segment  */
	DT32_int	segw;			/* width of the segment     */
	DT32_int	segh;			/* height of the segment    */

	DT16_ushort	seg_cnt;							/* segment count		*/
	Str_Seg2	segarr[DLO_SEG_LIMIT];				/* segment info array	*/

	DT16_ushort	cur_g1idx;
	DT16_ushort	cur_g2idx;
	DT16_ushort	gseq1[DLO_MAXCODES_PER_STR_SEG];
	GlyphSeq	gseq[DLO_MAXCODES_PER_STR_SEG];
	DT16_ushort	gseq2[DLO_MAXCODES_PER_STR_SEG];
	DT16_ushort	glyf_seq[DLO_MAXCODES_PER_STR_SEG];
}DLO_HANDLE;

DT16_ushort _ReadUShort(DT8_uchar *dlo, DT32_long ofs)
{  
	DT8_uchar *p;
	DT16_ushort val, b1, b2;

	p = dlo + ofs;
	b1 = *p++;
	b2 = *p;
	val = (b2<<8) + b1;

	return val;
}

DT32_ulong _ReadULong(DT8_uchar *dlo, DT32_long ofs, DT32_int size)
{
	DT8_uchar *p;
	DT32_ulong val, b;
	DT32_int scnt, i;

	p = dlo + ofs;
	val = *p++;

	for (i=1,scnt=8; i<size; i++,p++,scnt+=8)
	{
		b = *p << scnt;
		val += b;
	}

	return val;
}

DT16_ushort _ReadUShortfromCurpos(DLO_HANDLE *dlo_handle)
{
	DT16_ushort val;

	val = _ReadUShort(dlo_handle->dlo, dlo_handle->curpos);
	dlo_handle->curpos += 2;
	return val;
}

DT32_ulong _ReadULongfromCurpos(DLO_HANDLE *dlo_handle)
{
	DT32_ulong val;

	val = _ReadULong(dlo_handle->dlo, dlo_handle->curpos, 4);
	dlo_handle->curpos += 4;
	return val;
}

DT32_int _DFS_GetSubLookupTab(DLO_HANDLE *dlo_handle, SubLookupTab *hd)
{
	DT32_int i;

	for(i=0; i < dlo_handle->dloheader.subtabcnt; i++)
	{
		dlo_handle->offtosubtab = dlo_handle->dlotaboff[dlo_handle->cur_dlotab_idx] + dlo_handle->subtaboff[i]; 
	}

	dlo_handle->curpos = dlo_handle->offtosubtab;

	hd->format = _ReadUShortfromCurpos(dlo_handle); 
	if(hd->format != 1)
		return -1;
	hd->offset2Cover = _ReadUShortfromCurpos(dlo_handle);
	hd->ligasetcnt	 = _ReadUShortfromCurpos(dlo_handle);
	hd->ligsetoffset = (DT8_uchar*)dlo_handle->dlo + dlo_handle->curpos;
	return 	1;
}

DT32_int _DFS_GetdloHeader(DLO_HANDLE *dlo_handle)
{
	DT32_int i;

	dlo_handle->curpos = 8;

	dlo_handle->header.version	= _ReadUShortfromCurpos(dlo_handle);
	dlo_handle->header.dlotabcnt	= _ReadUShortfromCurpos(dlo_handle);
	for(i=0; i < dlo_handle->header.dlotabcnt; i++)
	{
		dlo_handle->dlotaboff[i] = _ReadULongfromCurpos(dlo_handle);
	}

	dlo_handle->header.offsetdlotab = dlo_handle->dlotaboff;

	return 1;
}

DT32_int _DFS_GetdlotabHeader(DLO_HANDLE *dlo_handle, dlotabheader *head, DLO_Script scr, DLO_Language lan, DT16_ushort *idx)
{
	DT32_int tmp = -1;
	DT16_ushort i;

	for(i=0; i < dlo_handle->header.dlotabcnt; i++)
	{
		dlo_handle->curpos = dlo_handle->header.offsetdlotab[i];
		if(_ReadUShortfromCurpos(dlo_handle) == scr)
		{
			if(_ReadUShortfromCurpos(dlo_handle) == lan)
			{
				tmp = i;
				break;
			}// end if
		}// end if
	}// end for

	if(-1 == tmp)
		return -1;
	else *idx = (DT16_ushort) tmp;

	dlo_handle->curpos = dlo_handle->header.offsetdlotab[*idx];
	head->script = _ReadUShortfromCurpos(dlo_handle);
	head->lang	 = _ReadUShortfromCurpos(dlo_handle);
	head->subtabcnt = _ReadUShortfromCurpos(dlo_handle);
	for(i=0; i < head->subtabcnt; i++)
	{
		dlo_handle->subtaboff[i] = _ReadULongfromCurpos(dlo_handle);
	}

	head->offsetsubtab = dlo_handle->subtaboff;

	return 1;
}

DT32_int _BinSearchinFile(DT32_int count, DT8_uchar *data, DT16_ushort key)
{
	DT32_int l=1, r=count;
	DT32_int m, ok=0;
	DT16_ushort us;
	DT32_long ofs;

	m = (l+r)/2;
	while(l<=r && ok==0)
	{
		ofs = m*2;
		us = _ReadUShort(data,ofs);
		if(us>key)		r=m-1;
		else if(us<key) l=m+1;
		else{			ok=1; break;	}
		m = (l+r)/2;
	}
	if(ok)	return m;
	else	return -1;
}

DT32_int _DFS_SearchInCoverageTab(DLO_HANDLE *del_handle, SubLookupTab *sub, DT16_ushort ch)
{
	DT32_int rtv;
	CoverTab1 cv;

	del_handle->curpos = del_handle->offtosubtab + sub->offset2Cover;
	cv.format = _ReadUShortfromCurpos(del_handle); 
	if(cv.format != 1){ return -1;}  /* Take unknown format as not found */
	cv.glyfcnt	= _ReadUShortfromCurpos(del_handle);
	cv.covarr	= (DT8_uchar*)del_handle->dlo + del_handle->curpos;
	rtv = _BinSearchinFile(cv.glyfcnt, (DT8_uchar*)cv.covarr, ch);
	return rtv;
}

DT16_ushort _Make_n_per_glyf(DT16_ushort codes, DT16_ushort glyfs)
{
	if(glyfs>1){ 
		return (glyfs<<8)+codes;
	}else{
		return codes;
	}
}

DT_void _Parse_n_per_glyf(DT16_ushort n_per_glyf, DT16_ushort *codes, DT16_ushort *glyfs)
{
	if(n_per_glyf>0x0100){
		*codes = (n_per_glyf&0x00FF);
		*glyfs = (n_per_glyf&0xFF00)>>8;
	}else{
		*codes = n_per_glyf;
		*glyfs = 1;
	}
}

DT32_int _SetgseqElem1(DLO_HANDLE *dlo_handle, DT16_ushort idx, DT16_ushort glyf, DT16_ushort cnt)
{
	DT16_ushort i;
	DT16_ushort nextNcodes = cnt;

	dlo_handle->gseq1[ dlo_handle->cur_g1idx ] = glyf;
	for(i=idx; i < idx+cnt; i++)
	{
		dlo_handle->gseq[i].glyf1 = glyf;
		dlo_handle->gseq[i].idx_gseq1 = dlo_handle->cur_g1idx;
		dlo_handle->gseq[i].n_per_glyf1 = _Make_n_per_glyf(nextNcodes,1);
		nextNcodes--;
	}

	dlo_handle->cur_g1idx++;
	return 1;
}

DT32_int _ReplaceLetter(DLO_HANDLE *dlo_handle, DT16_ushort idx, DT16_ushort *str)
{
	DT16_ushort us, us1, usr;
	DT32_int ret=2;

	us = str[idx];
	us1= str[idx+1];

	switch(us)
	{
	case 0x0627:
		if(us1 == 0x0653)		usr = 0x0622;
		else if(us1 == 0x0654)	usr = 0x0623;
		else if(us1 == 0x0655)	usr = 0x0625;
		else if(us1 == 0x0674)	usr = 0x0675;
		else { usr=us; ret=1; }
		break;
	case 0x0648:
		if(us1 == 0x0654)		usr = 0x0624;
		else if(us1 == 0x0674)	usr = 0x0676;
		else { usr=us; ret=1; }
		break;
	case 0x064A:
		if(us1 == 0x0654)		usr = 0x0626;
		else if(us1 == 0x0674)	usr = 0x0678;
		else { usr=us; ret=1; }
		break;
	case 0x06C1:
		if(us1 == 0x0654)		usr = 0x06C2;
		else { usr=us; ret=1; }
		break;
	case 0x06C7:
		if(us1 == 0x0674)		usr = 0x0677;
		else { usr=us; ret=1; }
		break;
	case 0x06D2:
		if(us1 == 0x0654)		usr = 0x06D3;
		else { usr=us; ret=1; }
		break;
	case 0x06D5:
		if(us1 == 0x0654)		usr = 0x06C0;
		else { usr=us; ret=1; }
		break;
	default:
		usr=us; ret=1;
		break;
	}
	_SetgseqElem1(dlo_handle, idx, usr, (DT16_ushort)ret);
	return ret;
}

static const DT8_uchar arabic_group[256] = {
	ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
	ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,

	Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, ArabicNone,
	ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,

	ArabicNone, ArabicNone, Alef, Alef, Waw, Alef, Yeh, Alef,
	Beh, TehMarbuta, Beh, Beh, Hah, Hah, Hah, Dal,

	Dal, Reh, Reh, Seen, Seen, Sad, Sad, Tah,
	Tah, Ain, Ain, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,

	Tatweel, Feh, Qaf, Kaf, Lam, Meem, Noon, Heh,
	Waw, Yeh, Yeh, Transparent, Transparent, Transparent, Transparent, Transparent,

	Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent,
	Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone,

	ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
	ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, Beh, Qaf,

	Transparent, Alef, Alef, Alef, ArabicNone, Alef, Waw, Waw,
	Yeh, Beh, Beh, Beh, Beh, Beh, Beh, Beh,

	Beh, Hah, Hah, Hah, Hah, Hah, Hah, Hah,
	Dal, Dal, Dal, Dal, Dal, Dal, Dal, Dal,

	Dal, Reh, Reh, Reh, Reh, Reh, Reh, Reh,
	Reh, Reh, Seen, Seen, Seen, Sad, Sad, Tah,

	Ain, Feh, Feh, Feh, Feh, Feh, Feh, Qaf,
	Qaf, Gaf, SwashKaf, Gaf, Kaf, Kaf, Kaf, Gaf,

	Gaf, Gaf, Gaf, Gaf, Gaf, Lam, Lam, Lam,
	Lam, Noon, Noon, Noon, Noon, Noon, KnottedHeh, Hah,

	TehMarbuta, HehGoal, HehGoal, HamzaOnHehGoal, Waw, Waw, Waw, Waw,
	Waw, Waw, Waw, Waw, Yeh, YehWithTail, Yeh, Waw,

	Yeh, Yeh, YehBarree, YehBarree, ArabicNone, TehMarbuta, Transparent, Transparent,
	Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, Transparent, Transparent,

	Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, ArabicNone, Transparent,
	Transparent, ArabicNone, Transparent, Transparent, Transparent, Transparent, Dal, Reh,

	ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
	ArabicNone, ArabicNone, Seen, Sad, Ain, ArabicNone, ArabicNone, KnottedHeh
};

static const JoiningPair ArabicJointab[5][4] =
{
	{ { XIsolated,XIsolated }, { XIsolated,XCausing }, { XIsolated,XInitial }, { XIsolated,XIsolated } }, /* XIsolated, Previous code's shape */
	{ { XFinal,	  XIsolated }, { XFinal,   XCausing }, { XFinal,   XInitial }, { XFinal,   XIsolated } }, /* XFinal */
	{ { XIsolated,XIsolated }, { XInitial, XCausing }, { XInitial, XMedial },  { XInitial, XFinal } }, /* XInitial */
	{ { XFinal,	  XIsolated }, { XMedial,  XCausing }, { XMedial,  XMedial },  { XMedial,  XFinal } }, /* XMedial */
	{ { XIsolated,XIsolated }, { XIsolated,XCausing }, { XIsolated,XMedial },  { XIsolated,XFinal } }, /* XCausing */
};

/*---------------------------------------------------*/

ArabicGroup _ArabicGetGroup(DT16_ushort uc)
{
	if (uc >= 0x0600 && uc < 0x0700)
		return (ArabicGroup) arabic_group[uc-0x0600];
	else if (uc == 0x0020)
		return ArabicSpace;
	else
		return ArabicNone;
}

DT32_int _DecideArabicCodeShape(DLO_HANDLE *dlo_handle, DT16_ushort idx, ArabicProperties *pro)
{
	ArabicShape shape, prevshape=XIsolated;
	ArabicGroup group, pregroup=ArabicNone;
	JoinType	jtype;
	DT16_ushort glyf1, idx1, previdx, sidx1, eidx1;
	DT32_int modprev=0;

	sidx1 = dlo_handle->gseq[dlo_handle->seg_start].idx_gseq1;
	eidx1 = dlo_handle->gseq[dlo_handle->seg_end-1].idx_gseq1;

	glyf1 = dlo_handle->gseq[idx].glyf1;
	idx1 = dlo_handle->gseq[idx].idx_gseq1;
    previdx = idx1;
	if(idx1>sidx1){
		previdx = idx1;
		do{
			previdx--;
			prevshape = pro[previdx].shape;	
			pregroup = pro[previdx].group;
		}while(prevshape==XTransparent && previdx > dlo_handle->gseq[dlo_handle->seg_start].idx_gseq1 && previdx > 0);
		if(prevshape==XTransparent){
			prevshape = XIsolated;
		}
	}

	if(idx1 == sidx1){
		group = _ArabicGetGroup(glyf1);
		jtype = _ArabicGroupType[group];
		if(jtype == JType_T){
			if(IS_ARABIC_ZEROWIDTH(glyf1)){
				shape = XIsolated;
			}else{
				shape = XIsolated;
			}
		}
		else if(idx1 == eidx1) 
			shape = XIsolated;
		else shape = ArabicJointab[prevshape][jtype].thisS;
	}else{
		group = _ArabicGetGroup(glyf1);
		jtype = _ArabicGroupType[group];
		if(jtype == JType_T){
			if(IS_ARABIC_ZEROWIDTH(glyf1)){
				shape = XTransparent;
			}else{
				shape = XIsolated;
			}
		}
		else shape = ArabicJointab[prevshape][jtype].thisS;

		if(shape!=XTransparent && prevshape != ArabicJointab[prevshape][jtype].prevS){
			pro[previdx].shape = ArabicJointab[prevshape][jtype].prevS; 
			modprev=1;
		}else if(idx1==eidx1 && shape==XTransparent){
			if(prevshape==XInitial){
				pro[previdx].shape = XIsolated;
				modprev=1;
			}
			else if(prevshape==XMedial){
				pro[previdx].shape = XFinal;
				modprev=1;
			}
		}

		if(idx1==eidx1  && jtype==JType_D){
			if(shape==XInitial) shape = XIsolated;
			else if(shape==XMedial) shape = XFinal;
		}
	}

	pro[idx1].glyf1 = glyf1;
	pro[idx1].group = group;
	pro[idx1].jtype = jtype;
	pro[idx1].shape = shape;

	return modprev;
}

DT32_int _DFS_GetLigature(DLO_HANDLE *dlo_handle, DT32_ulong pos, DT16_ushort idx, ArabicLigature *al)
{
	DT32_ulong of, of_start;
	DT32_int i;

	of = pos + 2 + idx*2;
	of_start = pos + _ReadUShort(dlo_handle->dlo, of);
	al->replacelem	= _ReadUShort(dlo_handle->dlo,of_start); of_start += 2 ;
	al->shape		= (ArabicShape)_ReadUShort(dlo_handle->dlo,of_start); of_start += 2 ;
	al->elementcnt	= _ReadUShort(dlo_handle->dlo,of_start); of_start += 2 ;
	for(i=0;i<al->elementcnt-1;i++)
	{
		al->combelem[i] = _ReadUShort(dlo_handle->dlo,of_start); of_start += 2 ;
	}
	return 1;
}

DT32_int _IsLigaMatch(DLO_HANDLE *dlo_handle, DT16_ushort idx, ArabicLigature *al, ArabicShape shapes, DT32_int comcnt, DT16_ushort *pcnt)
{
	DT32_int i;
	DT16_ushort index, pointscnt, matchcnt;

	if(al->shape != shapes)	
		return 0;

	if( comcnt!=0 && comcnt!=al->elementcnt ) 
		return 0; 

	i = 0;	pointscnt = 0;	matchcnt = 0;
	index = dlo_handle->gseq[idx].idx_gseq1+1;
	while(i < al->elementcnt-1 && index < dlo_handle->cur_g1idx)
	{
		if(al->combelem[i] != dlo_handle->gseq1[index])
		{
			if( IS_ARABIC_ZEROWIDTH(dlo_handle->gseq1[index]) )
			{
				index++;
				pointscnt++;
				continue;
			}else{
				return 0;
			}
		}else{
			i++;
			index++;
			matchcnt++;
		}
	}

	if(matchcnt != al->elementcnt-1){
		return 0;
	}

#ifdef USE_Android_DroidSansArabic
	switch(al->replacelem)
	{
	case 0x060C:
	case 0x061B:
	case 0x061F:
	case 0x067E:
	case 0x0686:
	case 0x0688:
	case 0x0691:
	case 0x0698:
	case 0x06A4:
	case 0x06A9:
	case 0x06AF:
	case 0x06BA:
	case 0x06BE:
	case 0x06C1:
	case 0x06CC:
	case 0x274A:
	case 0xFB9E:
	case 0xFB9F:
	case 0xFBE8:
	case 0xFBE9:
	case 0xFBFC:
	case 0xFBFD:
	case 0xFC5E:
	case 0xFC60:
	case 0xFC61:
	case 0xFDF2:
		break;
	default:
		if(!(
			(al->replacelem >= 0x0621 && al->replacelem <= 0x063A) ||
			(al->replacelem >= 0x0640 && al->replacelem <= 0x0656) ||
			(al->replacelem >= 0x0660 && al->replacelem <= 0x066D) ||
			(al->replacelem >= 0x0670 && al->replacelem <= 0x0671) ||
			(al->replacelem >= 0x0679 && al->replacelem <= 0x067B) ||
			(al->replacelem >= 0x06F0 && al->replacelem <= 0x06F9) ||
			(al->replacelem >= 0x200C && al->replacelem <= 0x200F) ||	// ?
			(al->replacelem >= 0xFB50 && al->replacelem <= 0xFB59) ||
			(al->replacelem >= 0xFB5E && al->replacelem <= 0xFB61) ||
			(al->replacelem >= 0xFB66 && al->replacelem <= 0xFB6D) ||
			(al->replacelem >= 0xFB7A && al->replacelem <= 0xFB7D) ||
			(al->replacelem >= 0xFB88 && al->replacelem <= 0xFB95) ||
			(al->replacelem >= 0xFBA6 && al->replacelem <= 0xFBAF) ||
			(al->replacelem >= 0xFE70 && al->replacelem <= 0xFEFC)
			) )
			return 0;
		break;
	}// end switch

#else
/*	if(al->replacelem < 0x060C || (al->replacelem > 0x060C && al->replacelem < 0x061B) || (al->replacelem > 0x061B && al->replacelem < 0x061F) ||
		(al->replacelem > 0x061F && al->replacelem < 0x0621) || 
		(al->replacelem > 0x063A && al->replacelem < 0x0640) || al->replacelem == 0x06EF ||
		(al->replacelem > 0xE0BC && al->replacelem < 0xFB50) || 
		(al->replacelem > 0xFBB1 && al->replacelem < 0xFBD4) || 
		al->replacelem == 0xFBD7 || al->replacelem == 0xFBD9 || al->replacelem == 0xFBDB || al->replacelem == 0xFBDD || al->replacelem == 0xFBDE ||
		al->replacelem == 0xFBE0 || al->replacelem == 0xFBE2 || al->replacelem == 0xFBE3 || al->replacelem == 0xFBE4 ||
		(al->replacelem > 0xFBE9 && al->replacelem < 0xFBFC) || 
		(al->replacelem > 0xFBFF && al->replacelem < 0xFE70) || 
		(al->replacelem > 0xFEFC && al->replacelem < 0xFEDC)
		)
		return 0;*/
	switch(al->replacelem)
	{
	case 0x060C:
	case 0x061B:
	case 0x061F:
	case 0x3000:
	case 0xFBD8:
	case 0xFBDA:
 	case 0xFBDC:
	case 0xFBDF:
	case 0xFBE1:
	case 0xFBE3:
		break;
	default:
		if(!(
//			(al->replacelem >= 0x0020 && al->replacelem <= 0x007E) ||
//			(al->replacelem >= 0x00A0 && al->replacelem <= 0x00FF) ||
			(al->replacelem >= 0x0621 && al->replacelem <= 0x063A) ||
			(al->replacelem >= 0x0640 && al->replacelem <= 0x0655) ||
			(al->replacelem >= 0x0660 && al->replacelem <= 0x066D) ||
			(al->replacelem >= 0x0670 && al->replacelem <= 0x06ED) ||
			(al->replacelem >= 0x06F0 && al->replacelem <= 0x06FE) ||

			(al->replacelem >= 0xE000 && al->replacelem <= 0xE08C) ||
			(al->replacelem >= 0xE420 && al->replacelem <= 0xE47E) ||

			(al->replacelem >= 0xFB50 && al->replacelem <= 0xFBB1) ||
			(al->replacelem >= 0xFBD4 && al->replacelem <= 0xFBD6) ||
			(al->replacelem >= 0xFBE5 && al->replacelem <= 0xFBE9) ||
			(al->replacelem >= 0xFBFC && al->replacelem <= 0xFBFF) ||
			(al->replacelem >= 0xFE70 && al->replacelem <= 0xFE74) ||
			(al->replacelem >= 0xFE76 && al->replacelem <= 0xFEFC)
			) )
			return 0;
		break;
	}// end switch
#endif
	*pcnt = pointscnt;
	return al->elementcnt;
}

DT16_ushort _CheckArabicLigature(DLO_HANDLE *dlo_handle, DT16_ushort idx, DT16_ushort ls, ArabicProperties *pro, SubLookupTab *sub, DT16_ushort *g2, DT16_ushort *points)
{
	DT32_int bmatch=0, tidx;
	DT32_int retm=0, comcnt=0, bReMatch=0;
	DT16_ushort i, ligcnt, elems=1, pointscnt;
	DT32_ulong  lsb;
	DT16_ushort comps[MAX_LIG_COMPONENTS];
	ArabicShape starts=XIsolated, ends=XIsolated, matchshape=XIsolated;
	ArabicLigature al;

	al.leadcode = dlo_handle->gseq[idx].glyf1;
	al.combelem = comps;

	dlo_handle->curpos = dlo_handle->offtosubtab + _ReadUShort(sub->ligsetoffset, ls*2);

	lsb = dlo_handle->curpos;
	ligcnt = _ReadUShortfromCurpos(dlo_handle);
	for(i=0; i < ligcnt; i++)
	{
		pointscnt = 0;
		_DFS_GetLigature(dlo_handle, lsb, i, &al);

		if(!bReMatch){
			starts = pro[ dlo_handle->gseq[idx].idx_gseq1 ].shape;
			tidx = idx;
			while(starts==XTransparent && tidx>dlo_handle->seg_start){
				tidx--;
				starts = pro[ dlo_handle->gseq[tidx].idx_gseq1 ].shape;
			}
			matchshape = starts;
		}

		if(_ArabicGetGroup(dlo_handle->gseq[idx].glyf1)==Lam){
			tidx = idx + 1;
			while(tidx < dlo_handle->seg_end){
				if(IS_ARABIC_ZEROWIDTH(dlo_handle->gseq[tidx].glyf1)){
					tidx++;
					continue;
				}
				if(_ArabicGetGroup(dlo_handle->gseq[tidx].glyf1) == Alef){
					if(starts==XInitial)		starts=XIsolated;
					else if(starts==XMedial)	starts=XFinal;
					else{ ;	/* do nothing*/ }
					if(!bReMatch){
						matchshape = starts;
					}
				}
				break;
			}
		}
		retm = _IsLigaMatch(dlo_handle,idx,&al,matchshape,comcnt,&pointscnt);

		if( retm>0 ){
			*g2	= al.replacelem;
			elems = al.elementcnt;
			*points = pointscnt;

			ends = pro[ dlo_handle->gseq[idx].idx_gseq1+retm-1 ].shape;		
			tidx = dlo_handle->gseq[idx].idx_gseq1+retm-1;
			while(ends==XTransparent && tidx>=dlo_handle->gseq[idx].idx_gseq1){
				tidx--;
				ends = pro[ tidx ].shape;
			}

               if( !bReMatch && ( starts==XInitial || starts==XMedial || starts==XCausing ) && ends==XFinal){
				if(starts==XInitial)		matchshape = XIsolated;
				else if(starts==XMedial)	matchshape = XFinal;
				else{ ;	}
				bReMatch=1;
				i=0; comcnt=retm; continue;
			}else{
				bmatch = 1;		break;
			}
		}
	}

	if(!bmatch && !bReMatch){
		*g2 = al.leadcode;
		elems = 1;
		*points = 0;
	}
	return elems;
}

DT16_ushort _SetgseqElem2(DLO_HANDLE *dlo_handle, DT16_ushort idx, DT16_ushort glyf, DT16_ushort cnt, DT16_ushort pointscnt)
{
	DT16_ushort i,j,r,g,c,total,index,tcnt,gcnt;

	tcnt = cnt + pointscnt;
	gcnt = pointscnt + 1;

	total = 0;	index = idx;
	for(i=0; i < tcnt; i++)
	{
		_Parse_n_per_glyf(dlo_handle->gseq[index].n_per_glyf1,&r,&g);
		total += r;
		index += r; 
	}

	index = idx;
	while(index<idx+tcnt){
		_Parse_n_per_glyf(dlo_handle->gseq[index].n_per_glyf1,&c,&g);
		for(j=0;j<c;j++){
			if(index+j==idx){
				dlo_handle->gseq[idx].glyf2	 = glyf;
				dlo_handle->gseq[idx].idx_gseq2 = dlo_handle->cur_g2idx;
				dlo_handle->gseq[idx].n_per_glyf2 = _Make_n_per_glyf(total,gcnt);
			}else if(index+j > idx){
				dlo_handle->gseq[index+j].glyf2	 = dlo_handle->gseq2[dlo_handle->cur_g2idx];
				dlo_handle->gseq[index+j].idx_gseq2 = dlo_handle->cur_g2idx;
				dlo_handle->gseq[index+j].n_per_glyf2 = 0;
			}
		}
		if(index==idx){
			dlo_handle->gseq2[dlo_handle->cur_g2idx] = glyf;
		}else if(IS_ARABIC_ZEROWIDTH(dlo_handle->gseq[index].glyf1)){
			dlo_handle->cur_g2idx++;
			dlo_handle->gseq2[dlo_handle->cur_g2idx] = dlo_handle->gseq[index].glyf1;
		}
		index += c;	
	}
	dlo_handle->cur_g2idx++;
	return total;
}

DT32_int _GetSeginfo_R2L(DLO_HANDLE *dlo_handle, Str_Seg2 *seginfo)
{
	DT32_int i, j, k, st, en, g2st, g2en, gcnt;
	DT16_ushort c, g, gidx=0;
	DLO_CodePositioning p;

	st = seginfo->ustart;
	en = seginfo->uend;

	g2st  = dlo_handle->gseq[st].idx_gseq2;
	g2en  = dlo_handle->gseq[en-1].idx_gseq2;
	gcnt  = g2en - g2st + 1;

	c=1; g=1; i=st; j=g2en; gidx=g2st;
	while(i < en)
	{
		if(dlo_handle->gseq[i].n_per_glyf2 != 0)
		{
			_Parse_n_per_glyf(dlo_handle->gseq[i].n_per_glyf2,&c,&g);
			for(k=0; k < g; k++)
			{
				dlo_handle->glyf_seq[j] = dlo_handle->gseq2[gidx];
				p.codeidx = i;
				p.glyfidx = j;
				p.n_per_glyf = (k==g-1) ? _Make_n_per_glyf(c,g):0;
				j--; gidx++;
			} 
			i += c;
		}

	}

	return 1;
}

DT32_int _GetSeginfo_Latin(DLO_HANDLE *dlo_handle, Str_Seg2 *seginfo)
{
	DT32_int i, j, st, en, caret=0, under=0;
	DT16_ushort c,g,gidx=0;
	DLO_CodePositioning p;
	DLO_RECT rect;

	st = seginfo->ustart;
	en = seginfo->uend;

     rect.xy.x =rect.xy.y =0;
	rect.hw.vx=rect.hw.vy=0;
	c=1; g=1;
	for(i=st; i < en; i+=c)
	{
		_Parse_n_per_glyf(dlo_handle->gseq[i].n_per_glyf2,&c,&g);
		gidx = dlo_handle->gseq[i].idx_gseq2;

		for(j=0; j < g; j++, gidx++)
		{
			dlo_handle->glyf_seq[gidx] = dlo_handle->gseq2[gidx];
			p.codeidx = i;
			p.glyfidx = gidx;

			if(0==j)
				p.n_per_glyf = _Make_n_per_glyf(c,g);
			else
				p.n_per_glyf = 0;
		}// end for
	}// end for

	seginfo->cpend.x = caret;
	seginfo->cpend.y = 0;

	return 1;
}

#if 0
DT32_int DT_CodeDirection(DT16_ushort ch)
{
/* Notice: Reserved Area: Some areas are reserved. It won't be decided here. */
/*
	if(ch>=0xE000 && ch<=0xE08F){}
	if(ch>=0xE900 && ch<=0xE9FF){}
	if(ch>=0xEE00 && ch<=0xEEFF){}
*/

/* For example: treat 0xE420-0xE47F as Basic Latin. */
#ifdef DT_CODE_ASCII_IN_PUA
	DT32_int	dir;
	DT16_ushort	code;
	code = ch - DT_CODE_ASCII_IN_PUA;
	if(code>=0x0020 && code<0x007F){
		dir = DT_CODE_ASCII_PUNCT;
		if(code>=0x41 && code<=0x5A ) dir = DT_CODE_DIR_AS_LATIN;
		else if(code>=0x61 && code<=0x7A ) dir = DT_CODE_DIR_AS_LATIN;
		else if(code>=0x30 && code<=0x39 ) dir = DT_CODE_DIR_AS_LATIN;
		else if(0x28==code || 0x5B==code || 0x7B==code)  dir = DT_CODE_ASCII_PAIR_OPEN;	/* pair in DT_PUAOpenClosePair[][2] */
		else if(0x29==code || 0x5D==code || 0x7D==code)  dir = DT_CODE_ASCII_PAIR_CLOSE;/* pair in DT_PUAOpenClosePair[][2] */
		return dir;
	}
#endif

	return DT_CODE_DIR_NOT_SPECIFIED;
}
#endif

/*---------------------------------------------------------------------------*/
DL_CodeAttr _DL_GetCodeCategoryPUA(DT16_ushort ch)
{
	DL_CodeAttr chattr;
	DT32_int dir;
	dir = DT_CodeDirection(ch);
     switch(dir){
	case DT_CODE_ASCII_PUNCT:
		chattr.range = DL_Range_Latin;
		chattr.cate  = DL_Punctuation_Other;
		break;
	case DT_CODE_ASCII_PAIR_OPEN:
		chattr.range = DL_Range_Latin;
		chattr.cate  = DL_Punctuation_Open;
		break;
	case DT_CODE_ASCII_PAIR_CLOSE:
		chattr.range = DL_Range_Latin;
		chattr.cate  = DL_Punctuation_Close;
		break;
	case DT_CODE_DIR_AS_LATIN:
		chattr.range = DL_Range_Latin;
		chattr.cate  = DL_Letter_Other;
		break;
	case DT_CODE_DIR_AS_ARABIC:
		chattr.range = DL_Range_Arabic;
		chattr.cate  = DL_Letter_Other;
		break;
	case DT_CODE_DIR_NOT_SPECIFIED:
	default:
		chattr.range = DL_Not_In_Range;
		chattr.cate  = DL_NoCategory;
	}

	return chattr;
}

DL_CodeAttr _DL_GetCodeCategory(DT16_ushort ch)
{
	DL_CodeAttr chattr;

	chattr.range = DL_Range_Latin;
	chattr.cate  = DL_Letter_Other;
	if( (ch<=0x001F)				||
		(ch==0x007F)				||
		(ch>=0x0080 && ch<=0x009F)
		){
			chattr.range  = DL_Range_Special;
			chattr.cate	  =	DL_Other_Control;
			return chattr;
	}

	if(ch==0x0020 || ch==0x3000){
		chattr.range = DL_Range_INHERIT;
		chattr.cate  = DL_Separator_Space;
		return chattr;
	}

	if(ch>0x0020 && ch<0x007F){
		chattr.range = DL_Range_Latin;
		chattr.cate	  = DL_Punctuation_Other;
		if(ch>=0x0041 && ch<=0x005A ) chattr.cate = DL_Letter_Uppercase;
		else if(ch>=0x0061 && ch<=0x007A ) chattr.cate = DL_Letter_Lowercase;
		else if(ch>=0x0030 && ch<=0x0039 ) chattr.cate = DL_Number_DecimalDigit;
		else if((ch>=0x0023 && ch<=0x0026) || 0x0040==ch) chattr.cate = DL_Symbol_Other;
		else if(0x28==ch || 0x5B==ch || 0x7B==ch) chattr.cate = DL_Punctuation_Open;
		else if(0x29==ch || 0x5D==ch || 0x7D==ch) chattr.cate = DL_Punctuation_Close;
		return chattr;
	}

	if( (ch>=0x00A0 && ch<=0x02FF) ){			
		chattr.range  = DL_Range_Latin;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
	}

	if( (ch>=0x0300 && ch<=0x036F)  ){		/* Combing Diacritical Marks */
		chattr.range  = DL_Range_Latin;
		chattr.cate	  = DL_Mark_SpacingCombining;
		return chattr;
	}

	if( (ch>=0x0370 && ch<=0x03FF) ){
		chattr.range  = DL_Range_Greek;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
	}

	if( (ch>=0x0400 && ch<=0x04FF) ||
		(ch>=0x0500 && ch<=0x052F)
		){		
			chattr.range  = DL_Range_Cyrillic;
			chattr.cate	  = DL_Letter_Other;
			return chattr;
	}

	if( (ch>=0x0530 && ch<=0x058F) ){
		chattr.range  = DL_Range_Armenian;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
	}

	if( (ch>=0x0590 && ch<=0x05FF) ||
		(ch>=0xFB1D && ch<=0xFB4F) ){
			chattr.range  = DL_Range_Hebrew;
			chattr.cate	  = DL_Letter_Other;
			return chattr;
	}

	if( (ch>=0x0600 && ch<=0x06FF)	||
		(ch>=0xFB50 && ch<=0xFDFF)	||
		(ch>=0xFE70 && ch<0xFEFF)	||
		(ch>=0xE000 && ch<0xE08F)
		){	
			chattr.range  = DL_Range_Arabic;
			chattr.cate   = DL_Letter_Other;
			if( (ch>=0x0610 && ch<=0x0615) || (ch>=0x064B && ch<=0x065E) || (ch>=0x06D6 && ch<=0x06DC) ||
				(ch>=0x06DF && ch<=0x06E4) || (ch>=0x06E7 && ch<=0x06E8) || (ch>=0x06EA && ch<=0x06ED) ||
				0x0670==ch ) chattr.cate = DL_Mark_NonSpacing;
			else if( 0x06DE==ch ) chattr.cate = DL_Mark_Enclosing;
			else if( 0x0640==ch ) chattr.cate = DL_Letter_Modifier;
			else chattr.cate   = DL_Letter_Other;
			return chattr;
	}

	if( (ch>=0x0900 && ch<=0x097F) ||
		(ch>=0xE900 && ch<=0xE9C1)) {
			chattr.range	= DL_Range_Devanagari;
			chattr.cate		= DL_Letter_Other;
			return chattr;
	}

	if( (ch>=0x0b80 && ch<=0x0bff) ||
		(ch>=0xEE00 && ch<=0xEE53)) {
			chattr.range	= DL_Range_Tamil;
			chattr.cate		= DL_Letter_Other;
			return chattr;
	}

	if( (ch>=0x0E00 && ch<=0x0E7F) ){
		chattr.range	= DL_Range_Thai;
		chattr.cate		= DL_Letter_Other;
		return chattr;
	}

	if( (ch>=0x2000 && ch<=0x21FF) ){
		chattr.range  = DL_Range_Special;
		chattr.cate   = DL_Other_Format;
		return chattr;
	}

	if(ch == 0xFEFF){ chattr.range = DL_Not_In_Range; chattr.cate = DL_NoCategory;}	

	if( ch>=0xE000 && ch<=0xF8FF ){
		return _DL_GetCodeCategoryPUA(ch);
	}

	return chattr;
}

/* Set the script and lang according code range. */
DT_void _DL_GetScriptLang(DL_CodeRange ra, DLO_Script *sc, DLO_Language *la)
{
	switch(ra)
	{
	case DL_Range_Arabic:
		*sc = DLO_SCRIPT_arab;
		*la = DLO_LANG_ARA;
		break;
	case DL_Range_Hebrew:
		*sc = DLO_SCRIPT_hebr;
		*la = DLO_LANG_IWR;
		break;
	case DL_Range_Thai:
		*sc = DLO_SCRIPT_thai;
		*la = DLO_LANG_THA;
		break;
	case DL_Range_Devanagari:
		*sc = DLO_SCRIPT_deva;
		*la = DLO_LANG_HIN;
		break;
	case DL_Range_Tamil:
		*sc = DLO_SCRIPT_taml;
		*la = DLO_LANG_TAM;
		break;
	case DL_Not_In_Range:
	case DL_Range_INHERIT:
	case DL_Range_Special:
	default:
		*sc = DLO_SCRIPT_latn;
		*la = DLO_LANG_LAT;
	}
}

/* Return 0:No direction implied. 1:direction implied. */
DT32_int _DL_CheckIfCodeDirective(DL_CodeAttr at)
{
	switch(at.range){
		/* Codes in the following ranges are not directive. */
	case DL_Not_In_Range:
	case DL_Range_INHERIT:
	case DL_Range_Special:
		return 0;
	case DL_Range_Latin:
		if( at.cate==DL_Punctuation_Other ||
			at.cate==DL_Symbol_Other ||
			at.cate==DL_Punctuation_Open ||
			at.cate==DL_Punctuation_Close){
				return 0;
		}/* else let it go to the default case. It should return DLO_LEFTTORIGHT. */
	default:
		return 1;
	}
	return 0;
}

DT16_ushort _GetSegDirectByScript2(DLO_Script script)
{
	switch(script)
	{
	case DLO_SCRIPT_arab:
	case DLO_SCRIPT_hebr:
		return DLO_RIGHTTOLEFT;/*0x200F;*/	/* In unicode, it means RTL (Right To Left). */
	case DLO_SCRIPT_latn:
	case DLO_SCRIPT_thai:
	default:
		return DLO_LEFTTORIGHT;/*0x200E;*/	/* In unicode, it means LTR (Left To Right). */
	}
}

DT16_ushort _DL_GetWriteDirByFirstCode2(DT16_ushort *str, DT32_int cnt, DLO_Script *sc, DLO_Language *la)
{
	//Use the first code's write direction will be used.
	DT32_int i;
	DT16_ushort dir=DLO_DECIDE_BY_STR;
	DLO_Script	tmpScript;
	DLO_Language tmpLang;
	DL_CodeAttr	at;
	tmpScript = DLO_SCRIPT_DFLT;	tmpLang = DLO_LANG_DFLT;
	for(i=0;i<cnt;i++){
		at = _DL_GetCodeCategory(str[i]);
		if(_DL_CheckIfCodeDirective(at)){
			_DL_GetScriptLang(at.range, &tmpScript,&tmpLang);
			dir = _GetSegDirectByScript2(tmpScript);
			break;
		}
	}
	if(sc){
		*sc = tmpScript;
	}
	if(la){
		*la = tmpLang;
	}

	return dir;
}

DT32_int _DL_DivideStrByScript_New2(DT16_ushort *str, DT16_ushort cnt, DT16_ushort idxb, DT32_int *idxe, 
								  DT32_int writedir, DLO_Script *sc, DLO_Language *la, DT16_ushort *dir)
{
	DT16_ushort iter=idxb;
	DL_CodeAttr at;
	DT32_int stop=0;
	DLO_Script next_sc=DLO_SCRIPT_DFLT, now_sc=DLO_SCRIPT_DFLT, ori_sc = *sc;
	DLO_Language next_la=DLO_LANG_DFLT, now_la=DLO_LANG_DFLT, ori_la = *la;
	DT16_ushort next_dir=DLO_DECIDE_BY_STR, now_dir=DLO_DECIDE_BY_STR, ori_dir = *dir;
	DT8_char	isOpenPunct_AtOtherDir=0;

	*sc = DLO_SCRIPT_DFLT;
	*la = DLO_LANG_DFLT;
	*dir= DLO_DECIDE_BY_STR;

//	switch(writedir){
//	case DLO_LEFTTORIGHT:
	while( iter<cnt && iter<DLO_MAXCODES_PER_STR_SEG && !stop )
	{
		//  if(0==str[iter]){
		//	  break;
		//  }
		  at = _DL_GetCodeCategory(str[iter]);
		  if(_DL_CheckIfCodeDirective(at)){
			  if(now_sc == DLO_SCRIPT_DFLT || now_la==DLO_LANG_DFLT){
				  /* Script is not decided yet. */
				  _DL_GetScriptLang(at.range, &now_sc, &now_la);
				  now_dir = _GetSegDirectByScript2(now_sc);
				  *sc = now_sc;
				  *la = now_la;
				  *dir= now_dir;
			  }else{
				/* Is the script the same? */
				_DL_GetScriptLang(at.range, &now_sc, &now_la);
				if(now_sc == *sc){
					/* same script, let loop going on, do nothing here. */
				}else{
					stop = 1;
				}
			  }
		  }else{
			  if(*sc == DLO_SCRIPT_DFLT || *la==DLO_LANG_DFLT){
				/* The leading code is a symbol or punctuation. Let follow the writedir */				
				if(writedir==DLO_RIGHTTOLEFT){
					*sc = now_sc = DLO_SCRIPT_arab;
					*la = now_la = DLO_LANG_ARA;
					*dir= now_dir= DLO_RIGHTTOLEFT;
				}else{
					*sc = now_sc = DLO_SCRIPT_latn;
					*la = now_la = DLO_LANG_LAT;
					*dir= now_dir= DLO_LEFTTORIGHT;
				}  
			  }else{
				next_dir = _DL_GetWriteDirByFirstCode2(str+iter, cnt-iter, &next_sc, &next_la);	/* Get Next Direction */
				if(next_sc==now_sc){
					/* This symbol or punctuation is between the same script, let loop going on. */
				}else{
					/* next_sc is not the same with now_sc, decided will it stop here. */
				  if(next_dir==DLO_DECIDE_BY_STR){ /* next_dir is not decided. */
					  if(now_dir==writedir){
						/* Let the loop complete. It should run to the end. (It should be *idxe==cnt)*/
					  }else{
						stop = 1;
					  }
				  }else if(next_dir==now_dir){	/* something like "+" at: ARABIC Latin + Thai ... */
					  if(now_dir==writedir){
						/* Let the loop stop at next script encountered. */
					  }else{
						stop = 1;
					  }
				  }else/* if(next_dir!=now_dir)*/{/* something like "+" at: ARABIC "Latin + ARABIC" ... */
					  if(now_dir==writedir){
						/* Let the loop stop at next script encountered. */
					  }else{
						stop = 1;
					  }
				  }

				  if(1==stop){
					  if(isOpenPunct_AtOtherDir>0){
						stop = 0;
						if(at.cate==DL_Punctuation_Close){
						  isOpenPunct_AtOtherDir -= 1;
						}
					  }else{
						stop = 1;
					  }
				  }
				}
			  }
			  if(at.cate==DL_Punctuation_Open){
				if(now_dir!=writedir){
					isOpenPunct_AtOtherDir += 1;
				}
			  }
		  }
		  if(!stop){
			iter++;
		  }
		}
//	case DLO_RIGHTTOLEFT:
//		break;
//	}


	if(*dir==DLO_DECIDE_BY_STR){	/* still not decide. Use writedir to assign the value. */
		if(writedir==DLO_RIGHTTOLEFT){
			*sc = DLO_SCRIPT_arab;
			*la = DLO_LANG_ARA;
			*dir= DLO_RIGHTTOLEFT;
		}else{
			*sc = DLO_SCRIPT_latn;
			*la = DLO_LANG_LAT;
			*dir= DLO_LEFTTORIGHT;
		}
	}
	//*idxe = idxb + segidx;
	*idxe = iter;
	
	return (*idxe - idxb);
}

DT16_ushort _DL_convOpen2Close2(DT16_ushort ch)
{
	DL_CodeAttr at;
	DT16_ushort codeout=ch;
	DT32_int	i;

	i = 0;
	at = _DL_GetCodeCategory(ch);
	if(at.cate==DL_Punctuation_Open){
		switch(ch){
		case 0x0028:
			codeout = 0x0029;
			break;
		case 0x005B:
			codeout = 0x005D;
			break;
		case 0x007B:
			codeout = 0x007D;
			break;
		default:
			// find in PUA area.
			while(DT_PUAOpenClosePair[i][0]){
				if(DT_PUAOpenClosePair[i][0]==ch){
					codeout = DT_PUAOpenClosePair[i][1];	//pair found in PUA
					break;
				}
				i++;
			}
		}
	}else if(at.cate==DL_Punctuation_Close){
		switch(ch){
		case 0x0029:
			codeout = 0x0028;
			break;
		case 0x005D:
			codeout = 0x005B;
			break;
		case 0x007D:
			codeout = 0x007B;
			break;
		default:
			// find in PUA area.
			while(DT_PUAOpenClosePair[i][1]){
				if(DT_PUAOpenClosePair[i][1]==ch){
					codeout = DT_PUAOpenClosePair[i][0];	//pair found in PUA
					break;
				}
				i++;
			}
		}
	}

	return codeout;	
}
DT32_int _DT_FunctionByLang(DLO_HANDLE *dlo_handle, DLO_Script scr, DLO_Language lan)
{
	int i;
	unsigned short ch;
	int iter, bexist, index;
	DT32_int rtv, bmod=0;
	DT16_ushort lsidx, points, c;
	ArabicProperties glyf1pro[DLO_MAXCODES_PER_STR_SEG];
	SubLookupTab subhead;
	DT16_ushort g=0, elemcnt, glyf2, total;
	DL_CodeAttr at, at2;
	Str_Seg2 ss;

	if(scr == DLO_SCRIPT_arab && lan == DLO_LANG_ARA)
	{
		_DFS_GetSubLookupTab(dlo_handle, &subhead);

		for(i=dlo_handle->seg_start; i < dlo_handle->seg_end; i++)
		{
			dlo_handle->gseq[i].idx	= i;
			dlo_handle->gseq[i].code = dlo_handle->ucs_str[i];
	}

	for(iter=dlo_handle->seg_start; iter < dlo_handle->seg_end; )
	{
		iter += _ReplaceLetter(dlo_handle, iter, dlo_handle->ucs_str);
	}// end for

	/* Decide the code's shape in gseq1 */
	for(iter=dlo_handle->seg_start; iter < dlo_handle->seg_end; )
	{
		bmod = _DecideArabicCodeShape(dlo_handle, iter, (ArabicProperties*)glyf1pro);
		_Parse_n_per_glyf(dlo_handle->gseq[iter].n_per_glyf1, &c, &g);
		iter += c;
	}

#if 1
	dlo_handle->segarr[dlo_handle->seg_cnt].gxstart	= dlo_handle->cur_g2idx;
	/* Search Sub Tab for glyph substitution (ligature or shape) and generate gseq2. Example: 0628+062D+064A=FDC2 */
	iter = dlo_handle->seg_start;
	while(iter < dlo_handle->seg_end)
	{
		//		ch = str[iter];
		ch = dlo_handle->gseq[iter].glyf1;
		/* Is there any suitable substitutions? */
		bexist = 0;

		rtv = _DFS_SearchInCoverageTab(dlo_handle, &subhead, ch);
		if(rtv >= 0)
		{
			lsidx = rtv;
			bexist=1;
		}// end if
#if 1
			/* Found */
		if(bexist)
		{
			points = 0;	/* ligature contains points */
			elemcnt = _CheckArabicLigature(dlo_handle, iter, lsidx, (ArabicProperties*)glyf1pro, &subhead, &glyf2, &points);
			total = _SetgseqElem2(dlo_handle, iter, glyf2, elemcnt, points);
				/* Not Found */
		}else
		{ 
			total = _SetgseqElem2(dlo_handle, iter, ch, 1, 0);	// alone point will also get into this.
		}
		iter = iter+total;
#endif
	}// end while

		//	ConvPunctuation_Open2Close(pwrk, dlo_handle->seg_start, dlo_handle->seg_end);
		for(i=dlo_handle->seg_start; i < dlo_handle->seg_end; i++)
		{
			DT16_ushort glyph, glyph2;

			glyph = dlo_handle->gseq[i].glyf2;
			at = _DL_GetCodeCategory(glyph);
			if(at.cate == DL_Punctuation_Open || at.cate == DL_Punctuation_Close)
			{
				glyph2 = _DL_convOpen2Close2(glyph);
				dlo_handle->gseq[i].glyf2 = glyph2;
				dlo_handle->gseq2[dlo_handle->gseq[i].idx_gseq2] = glyph2;
			}
		}
#endif

	index = dlo_handle->seg_start;
	at.range = DL_Not_In_Range;
	at2.range = DL_Not_In_Range;
	at = at2 = _DL_GetCodeCategory( dlo_handle->ucs_str[0] );
	for(iter=dlo_handle->seg_start; iter < dlo_handle->seg_end; iter++)
	{
		at = _DL_GetCodeCategory( dlo_handle->ucs_str[iter] );

		if(at.range != at2.range)
		{
			ss.ustart = index;
			ss.uend = iter;
			if(at2.range == DL_Range_Arabic)
				_GetSeginfo_R2L(dlo_handle, &ss);
			else _GetSeginfo_Latin(dlo_handle, &ss);
			at2.range = at.range;
			index = iter;
		}// end if
	}// end while

	if(iter > index)
	{
		ss.ustart = index;
		ss.uend = iter;
		if(at2.range == DL_Range_Arabic)
				_GetSeginfo_R2L(dlo_handle, &ss);
		else _GetSeginfo_Latin(dlo_handle, &ss);
	}// end if


		dlo_handle->segarr[dlo_handle->seg_cnt].gxend	= dlo_handle->cur_g2idx;
		dlo_handle->segarr[dlo_handle->seg_cnt].ustart	= dlo_handle->seg_start;
		dlo_handle->segarr[dlo_handle->seg_cnt].uend	= dlo_handle->seg_end;
		dlo_handle->segarr[dlo_handle->seg_cnt].script	= dlo_handle->seg_script;
		dlo_handle->segarr[dlo_handle->seg_cnt].lang	= dlo_handle->seg_lang;
	}else
	{
		GlyphSeq	gs;

		dlo_handle->segarr[dlo_handle->seg_cnt].gxstart	= dlo_handle->cur_g2idx;
		/* Fill the codeidx in gseq, gseq1, gseq2*/
		for(i=dlo_handle->seg_start; i < dlo_handle->seg_end; i++)
		{
			ch = dlo_handle->ucs_str[i];
			dlo_handle->gseq1[dlo_handle->cur_g1idx] = ch;
			dlo_handle->gseq2[dlo_handle->cur_g2idx] = ch;

			gs.idx			= i;
			gs.code			= ch;

			gs.glyf1 = ch;
			gs.idx_gseq1 = dlo_handle->cur_g1idx;
			gs.n_per_glyf1 = _Make_n_per_glyf(1,1);

			gs.glyf2 = ch;
			gs.idx_gseq2 = dlo_handle->cur_g2idx;
			gs.n_per_glyf2 = _Make_n_per_glyf(1,1);

			dlo_handle->gseq[i] = gs;

			dlo_handle->cur_g1idx++;
			dlo_handle->cur_g2idx++;
		}


		/* Fill the DLO_Laybuf, including cseq */
//		Fillawseg_LAT(pwrk);
//		Fillsegarr_LAT(pwrk);

		dlo_handle->segarr[dlo_handle->seg_cnt].gxend	= dlo_handle->cur_g2idx;
		dlo_handle->segarr[dlo_handle->seg_cnt].ustart	= dlo_handle->seg_start;
		dlo_handle->segarr[dlo_handle->seg_cnt].uend	= dlo_handle->seg_end;
		dlo_handle->segarr[dlo_handle->seg_cnt].script	= dlo_handle->seg_script;
		dlo_handle->segarr[dlo_handle->seg_cnt].lang	= dlo_handle->seg_lang;

		ss.ustart = dlo_handle->seg_start;
		ss.uend = dlo_handle->seg_end;
//		GetSeginfo_Latin(dlo_handle, &ss);
	}// end if

	return 0;
}

int exchangestr(unsigned short *str, int len, unsigned short *str2)
{
	int i, j;
	j=len-1;

	for(i=0; i < j; i++, j--)
	{
		str2[i] = str[j];
		str2[j] = str[i];
	}
	if(len & 0x01)
		str2[i] = str[i];

	return len;
}// end exchangestr


///////////////// Functions used by Thai /////////////////
#include "DcwThai.h"
#define ismyUCONS(usch)		((usch)==0x0E64||(usch)==0x0E65||(usch)==0x0E66)
#define ismySCONS(usch)		((usch)==0x0E60||(usch)==0x0E63)
#define ismylowerTONE(usch)	((usch)==0x0E68||(usch)==0x0E69||(usch)==0x0E6A||(usch)==0x0E6B)
#define ismylowerAD1(usch)	((usch)==0x0E6C)
#define ismyUpperAD2(usch)	((usch)==0x0E67)
#define ismyUpperAD4(usch)	((usch)==0x0E6D)
#define ismyleftBDEAD(usch)	((usch)==0x0E3B||(usch)==0x0E3C||(usch)==0x0E3D)

extern ThaiClass ThaiGetClass(DT16_ushort uc);

int _DL_isThaiChars(unsigned short ch)
{
	return isThaiChars(ch);
}

int _DL_isThaiNSMs(unsigned short ch)
{
	if(ch==0x0E31 || (ch>=0x0E34 && ch<=0x0E3A) || (ch>=0x0E47 && ch<=0x0E4E))
		return 1;

	// my additional Thai chars
	if((ch>=0x0E3B && ch<=0x0E3D) || (ch>=0x0E67 && ch<=0x0E6D))
		return 1;

	return 0;
}

int _DL_isThaiUCons(unsigned short ch)
{
	return isUCONS(ch);
}

int _DL_isThaiSCons(unsigned short ch)
{
	return isSCONS(ch);
}

int _DL_isThaiBDead(unsigned short ch)
{
	return isBDEAD(ch);
}

int _DL_isThaiAV(unsigned short ch)
{
	ThaiClass cls = ThaiGetClass(ch);
	return (cls&AV);
}

int _DL_isHalfWidthTONEAD(unsigned short ch)
{
	if( (0x0E49<=ch && 0x0E4C) || (0x0E69<=ch && 0x0E6C) )
		return 1;
	
	return 0;
}

unsigned short _Thai_getPair(unsigned short uc)
{
	// convert to my defined pair
	switch(uc){
	case 0x0E0D:
		return 0x0E60;
	case 0x0E10:
		return 0x0E63;
	case 0x0E1B:
		return 0x0E64;
	case 0x0E1D:
		return 0x0E65;
	case 0x0E1F:
		return 0x0E66;
	default:
		break;
	}
	if(uc>=0x0E38 && uc<=0x0E3A)
	{
		return uc + 0x03;
	}
	if(uc>=0x0E47 && uc<=0x0E4D)
	{
		return uc + 0x20;
	}

	// convert back to the original one.
	switch(uc){
	case 0x0E60:
		return 0x0E0D;
	case 0x0E63:
		return 0x0E10;
	case 0x0E64:
		return 0x0E1B;
	case 0x0E65:
		return 0x0E1D;
	case 0x0E66:
		return 0x0E1F;
	default:
		break;
	}
	if(uc>=0x0E3B && uc<=0x0E3D)
	{
		return uc - 0x03;
	}
	if(uc>=0x0E67 && uc<=0x0E6D)
	{
		return uc - 0x20;
	}

	// Not paired
	return uc;
}

#define LEVELID_THAI_TOP	0
#define LEVELID_THAI_ABOVE	1
#define LEVELID_THAI_BASE	2
#define LEVELID_THAI_BELOW	3
#define LEVELID_THAI_SHIFT	4
#define LEVELID_THAI_TOTALH	5

#ifndef FD_READINTBYDATA1
#define FD_READINTBYDATA1(fontdata, ofs)		( (fontdata[(ofs)] )		// Not used
#endif
#ifndef FD_READINTBYDATA2
#define FD_READINTBYDATA2(fontdata,ofs)	( (DT32_long)(((DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8) | (DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)])) )
#endif
#ifndef FD_READINTBYDATA4
#define FD_READINTBYDATA4(fontdata,ofs) ( (DT32_long)(((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+3]) << 24) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+2]) << 16) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8)  | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)]))) )
#endif
extern DT32_long FD_ReadIntByData2(DT8_char *fontdata, DT32_long ofs);
extern DT32_long FD_ReadIntByData4(DT8_char *fontdata, DT32_long ofs);
extern DT32_long FD_ReadIntByData(DT8_char *fontdata, DT32_long ofs, DT32_int size);

extern DT32_long FD_GetLangTableByData(DT8_char *fontdata, DT32_int LangID, DT32_long langtab, DT16_ushort langtabcnt);

int _parsingThaiTable(char *fontdata, long nfsize, Font_Design_Thai *pdt)
{
	int  bDonebyData = 0;
	long ofs, langtab;
	unsigned short langtabcnt = 0;
	if(fontdata /*&& nfsize>8 && !DT_strncmp(fontdata,"FDL Font",8)*/ ){	// Assume format is always right.
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, 58/*FD_LANGTAB*/);
		if(langtab > 0)
		{
			ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);
			ofs = FD_GetLangTableByData(fontdata, 6/*DCW_LANGTAB_THA*/, langtab, langtabcnt);
			if(ofs>0 && ofs < nfsize){
				ofs += (2+4);
				pdt->Thai_Top	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);	ofs += 2;
				pdt->Thai_Above	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);	ofs += 2;
				pdt->Thai_Base	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);	ofs += 2;
				pdt->Thai_Below	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);	ofs += 2;
				pdt->Thai_Shift	= (DT16_ushort)FD_READINTBYDATA2(fontdata, ofs);	ofs += 2;
				bDonebyData = 1;
			}
		}
	}
	
	if(!bDonebyData){
		pdt->Thai_Top	= 170;
		pdt->Thai_Above	= 148;
		pdt->Thai_Base	= 543;
		pdt->Thai_Below	= 139;
		pdt->Thai_Shift	= 140;
	}

	return bDonebyData;
}

int _GetThaiLevels(Font_Design_Thai *pdt, int levelid)
{
	switch(levelid)
	{
	case LEVELID_THAI_TOP:
		return pdt->Thai_Top;
	case LEVELID_THAI_ABOVE:
		return pdt->Thai_Above;
	case LEVELID_THAI_BASE:
		return pdt->Thai_Base;
	case LEVELID_THAI_BELOW:
		return pdt->Thai_Below;
	case LEVELID_THAI_SHIFT:
		return pdt->Thai_Shift;
	case LEVELID_THAI_TOTALH:
		return pdt->Thai_Top+pdt->Thai_Above+pdt->Thai_Base+pdt->Thai_Below;
	default:
		return 0;
	}
}

int _ThaiGetmyUconsAwDiff(Font_Design_Thai *pdt, int aw)
{
	int xshift;
	int totalh;

	xshift = _GetThaiLevels(pdt,LEVELID_THAI_SHIFT);
	totalh = _GetThaiLevels(pdt,LEVELID_THAI_TOTALH);
	return -(aw*xshift+totalh-1)/totalh;
}

int _ThaiGetmy0E33AwDiff(int aw)
{
	return (-aw/3);
}

int _ThaiGetmyleftBDEADXdiff(Font_Design_Thai *pdt, int w)
{
	int xshift;
	int totalh;

	xshift = _GetThaiLevels(pdt,LEVELID_THAI_SHIFT);
	totalh = _GetThaiLevels(pdt,LEVELID_THAI_TOTALH);
	return (w*xshift+totalh-1)/totalh;
}

int dynacw_getThaiAwDiff(void *hfont, unsigned short ch, int aw)
{
	pDT_Fontwrk	pdtfwrk = (pDT_Fontwrk)hfont;
	Font_Design_Thai dt;
	int diff;

	diff = 0;
	if( (ch>=0x0E64 && ch<=0x0E66) || ch==0x0E33 || (ch>=0x0E3B && ch<=0x0E3D) ){
		if(pdtfwrk && pdtfwrk->font->fontdata && pdtfwrk->font->type==DTDigiType_FDL){
			_parsingThaiTable(pdtfwrk->font->fontdata, pdtfwrk->font->nfsize, &dt);
		}else{
			_parsingThaiTable(NULL, 0, &dt);	// get a default one.
		}

		if( (ch>=0x0E64 && ch<=0x0E66) )
		{
			diff = _ThaiGetmyUconsAwDiff(&dt, aw);
		}else if(ch==0x0E33)
		{
			diff = _ThaiGetmy0E33AwDiff(aw);
		}else if( (ch>=0x0E3B && ch<=0x0E3D) )
		{
			diff = _ThaiGetmyleftBDEADXdiff(&dt, aw);
		}
	}
	
	return diff;
}

void dynacw_getThaimove(void *hfont, unsigned short ch, int bmpwidth, int *movex, int *movey, int *advance)
{
	int mvX, mvY, aw;
	mvX = mvY = 0;
	aw = *advance;

	if( _DL_isThaiNSMs(ch) )
	{
		aw = 0;
		mvX = -bmpwidth;
		if( (ch>=0x0E3B && ch<=0x0E3D))
		{
			mvX += dynacw_getThaiAwDiff(hfont, ch, bmpwidth);
		}
	}else if( (ch>=0x0E64 && ch<=0x0E66) )
	{
		aw += dynacw_getThaiAwDiff(hfont, ch, aw);
	}else if(ch==0x0E33)
	{
		mvX = dynacw_getThaiAwDiff(hfont, ch, aw);
		aw += mvX;
	}else
	{
		// do nothing
	}

	*movex = mvX;
	*movey = mvY;
	*advance = aw;
}

int dynacw_thai_run(unsigned short *str, int cnt)
{
	int i;
	unsigned short *prv=NULL, *now=NULL, *base=NULL;
	ThaiClass clsnow;

	for(i=0;i<cnt;i++){
		now = str + i;
		if(isThaiChars(*now)){
			if(now>str)
				prv = now - 1;

			clsnow = ThaiGetClass(*now);
			if(CONS==clsnow){
				base = now;
			}else if(0x0E33==*now){
				if(base && isUCONS(*base)){
					*base = _Thai_getPair(*base);				// UCONS + 0x0E33
				}
				if(prv && ismylowerTONE(*prv)){
					*prv  = _Thai_getPair(*prv);				// CONS + TONE + 0x0E33
				}
				base = NULL;	// 0x0E33 is a FV, terminated.
			}else if(clsnow&LV || clsnow&FV || NON==clsnow){
				base = NULL;
			}

			// Check if conversion is required?
			if(base){
				if(isDEAD(clsnow)){
					if(isBDEAD(*now)){
						if(isSCONS(*base)){
							*base = _Thai_getPair(*base);			// SCONS + (BV|BD)
						}
						//else if(isUCONS(*base)){
						//	*now  = _Thai_getPair(*now);			// UCONS + (BV|BD)
						//}
					}else if(!isBDEAD(*now)){
						if(isUCONS(*base)){
							*base = _Thai_getPair(*base);			// UCONS + (AV|AD|TONE)
						}
						//// Dealing TONEs. Is level down required?
						if(TONE==clsnow){
							if(1==now-base){
								*now = _Thai_getPair(*now);			// CONS + TONE
							}else if(2==now-base){
								if(prv && isBDEAD(*prv) ){
									*now = _Thai_getPair(*now);		// CONS + (BV|BD) + TONE
									if(ismyUCONS(*base))
										*prv = _Thai_getPair(*prv);	// UCONS + (BV|BD) + TONE
								}
							}else{
								// TONE stay at top level.
							}
						}
						//// Dealing AVs
						else if(AV==clsnow){
							// AV always stay at above level
						}
						//// Dealing ADs, the level isn't the same as before in the Android FDL font
						else if(0x0E4C==*now){	// AD1, top level originally
							if(1==now-base){
								*now = _Thai_getPair(*now);			// CONS + AD1
							}else if(2==now-base){
								if(prv && (isBDEAD(*prv) || ismyleftBDEAD(*prv))){
									*now = _Thai_getPair(*now);		// CONS + (BV|BD) + AD1
								}
							}
						}else if(0x0E4D==*now){	// AD4, above level originally, no level up required.
						}else if(0x0E47==*now){	// AD2, above level originally, no level up required.
						}else if(0x0E4E==*now){	// AD3, above level originally, no level up required.
						}
					}
				}
			}			
		}else{
			base = NULL;
			now  = NULL;
			prv  = NULL;
		}
	}
	return cnt;
}

#if 0	// Old mode
int dynacw_arabic_reshape(unsigned short *str, int str_len, unsigned short *str2, int *len2, int maxlen, int writedir)
{
	uint32_t i;
	DT16_ushort ch;
	uint32_t iter, bexist, index;
	DT32_int rtv, bmod=0;
	DLO_HANDLE dlo_handle;
	DT16_ushort g=0, elemcnt, glyf2, total;
	DL_CodeAttr at, at2;

	SubLookupTab subhead;
	DT16_ushort lsidx, points, c;
	ArabicProperties glyf1pro[DLO_MAXCODES_PER_STR_SEG];
	Str_Seg	ss;

	memset(&dlo_handle, 0, sizeof(dlo_handle));
	dlo_handle.dlo = (DT8_uchar*)dlodata;
	dlo_handle.seg_start = 0;
	dlo_handle.seg_end = str_len;

	if(_DFS_GetdloHeader(&dlo_handle) < 0)
		return -1;

	rtv = _DFS_GetdlotabHeader(&dlo_handle, &dlo_handle.dloheader, DLO_SCRIPT_arab, DLO_LANG_ARA, &dlo_handle.cur_dlotab_idx);

	if( _DFS_GetSubLookupTab(&dlo_handle, &subhead) < 0)
		return -1;

	for(i=0; i < str_len; i++)
	{
		dlo_handle.gseq[i].idx	= i;
		dlo_handle.gseq[i].code = str[i];
	}

	for(iter=0; iter < str_len; )
	{
		iter += _ReplaceLetter(&dlo_handle, iter, str);
	}// end for

	for(iter=0; iter < str_len; )
	{
		bmod = _DecideArabicCodeShape(&dlo_handle, iter, (ArabicProperties*)glyf1pro);
		_Parse_n_per_glyf(dlo_handle.gseq[iter].n_per_glyf1, &c, &g);
		iter += c;
	}

	iter = 0;
	while(iter < str_len)
	{
		ch = dlo_handle.gseq[iter].glyf1;
		bexist = 0;

		rtv = _DFS_SearchInCoverageTab(&dlo_handle, &subhead, ch);
		if(rtv >= 0)
		{
			lsidx = rtv;
			bexist=1;
		}// end if

		if(bexist)
		{
			points = 0;
			elemcnt = _CheckArabicLigature(&dlo_handle, iter, lsidx, (ArabicProperties*)glyf1pro, &subhead, &glyf2, &points);
			total = _SetgseqElem2(&dlo_handle, iter, glyf2, elemcnt, points);
		}else
		{ 
			total = _SetgseqElem2(&dlo_handle, iter, ch, 1, 0);
		}
		iter = iter+total;
	}// end while

	index = 0;
	iter = 0;
	at.range = DL_Not_In_Range;
	at2.range = DL_Not_In_Range;
	at = at2 = _DL_GetCodeCategory( str[0] );	
	for(iter=1; iter < str_len; iter++)
	{
		at = _DL_GetCodeCategory( str[iter] );

		if(at.range != at2.range)
		{
			ss.ustart = index;
			ss.uend = iter;
			if(at2.range == DL_Range_Arabic)
				_GetSeginfo_R2L(&dlo_handle, &ss);
			else _GetSeginfo_Latin(&dlo_handle, &ss);
			at2.range = at.range;
			index = iter;
		}// end if
	}// end while

	if(iter > index)
	{
		ss.ustart = index;
		ss.uend = iter;
		if(at2.range == DL_Range_Arabic)
			_GetSeginfo_R2L(&dlo_handle, &ss);
		else _GetSeginfo_Latin(&dlo_handle, &ss);
	}// end if

	if(dlo_handle.writedir = DLO_RIGHTTOLEFT)
	{
		int len;
		int pos = dlo_handle.cur_g2idx;
		for(i=0; i < dlo_handle.seg_cnt; i++)
		{
			len = dlo_handle.segarr[i].gxend - dlo_handle.segarr[i].gxstart;
			pos -= len;
			memcpy(str2 + pos, dlo_handle.glyf_seq + dlo_handle.segarr[i].gxstart, len * sizeof(unsigned short));
		}// end for
		str2[dlo_handle.cur_g2idx] = 0;
	}else memcpy(str2, dlo_handle.glyf_seq, dlo_handle.cur_g2idx * sizeof(DT16_ushort));
	*len2 = dlo_handle.cur_g2idx;

	return 0;
}

#else
int dynacw_arabic_reshape(unsigned short *str0, int str_len, unsigned short *str2, int *len2, int maxlen, int writedir)
{
	DT32_int i;
	DT32_int bmod=0;
	DLO_HANDLE dlo_handle;
	DT32_int size;
	unsigned short *str;
	unsigned short str1[1024];
	unsigned short  unicd;
	int isArabic = 0;

	//memcpy(str2, str0, str_len * sizeof(unsigned short));		*len2 = str_len;		return 0;
#define DT_DECIDE_BY_STR	0x0000		/* decide by first encountered code which implies direction. */
#define DT_LEFTTORIGHT		0x200E
#define DT_RIGHTTOLEFT		0x200F

	dynacw_thai_run(str0, str_len);


	for(i=0; i<str_len; i++) {
		unicd = str0[i];
		if((unicd >= 0x600 && unicd <= 0x700)|| (unicd>=0xFB50 && unicd<=0xFDFF)|| (unicd>=0xFE70 &&unicd<=0xFEFF) || (unicd >= 0xE000 && unicd<0xE08F))
		{
			isArabic = 1;
			break;
		}
	}
	if (!isArabic) {
		*len2 = str_len;
		memcpy(str2,str0,sizeof(unsigned short)*str_len);
		return 0;
	}else{
		writedir=0x200E;		// DT_LEFTTORIGHT
	}

	if(writedir != 0x400E)
	{
		str = str0;
	}else
	{
		str = str1;
		writedir = 0x200E;
		for(i=0; i < str_len; )
		{
			if(0x0600 <= str0[i] && str0[i] <= 0x06FF)
			{
				int k;
				for(k=i; k < str_len; k++)
				{
					if(!(0x0600 <= str0[k] && str0[k] <= 0x06FF))
						break;
				}// end for
	
				i += exchangestr(str0+i, k-i, str+i);
			}else
			{
				str[i] = str0[i];
				i++;
			}// end if
		}// end for
	}// end if

	memset(&dlo_handle, 0, sizeof(dlo_handle));
	dlo_handle.dlo = dlodata;
	dlo_handle.seg_start = 0;
	dlo_handle.seg_end = str_len;
	dlo_handle.writedir = writedir;

	if(_DFS_GetdloHeader(&dlo_handle) < 0)
		return -1;

	dlo_handle.mainScript = DLO_SCRIPT_DFLT;
	dlo_handle.mainLang	= DLO_LANG_DFLT;
	dlo_handle.ucs_cnt = str_len;
	dlo_handle.ucs_str = str;

	/* Decide the writedir if needed. */
	if(writedir == DLO_DECIDE_BY_STR)
	{
		if(dlo_handle.mainScript == DLO_SCRIPT_DFLT || dlo_handle.mainLang==DLO_LANG_DFLT)
		{
			dlo_handle.writedir = _DL_GetWriteDirByFirstCode2(dlo_handle.ucs_str, dlo_handle.ucs_cnt, NULL, NULL);
			if(DLO_DECIDE_BY_STR == dlo_handle.writedir)
			{
				/* Can't decide, use L2R as default. */
				dlo_handle.writedir = DLO_LEFTTORIGHT;
			}
		}else
		{
			dlo_handle.writedir = _GetSegDirectByScript2(dlo_handle.mainScript);
		}// end if
	}else
	{
		dlo_handle.writedir = writedir;
	}// end if

	size = 0;
	dlo_handle.seg_start = 0;
	dlo_handle.seg_end=0;
	dlo_handle.seg_cnt = 0;
	dlo_handle.segw = 0;
	dlo_handle.segh = 0;
	dlo_handle.cur_g1idx = 0;
	dlo_handle.cur_g2idx =0; 
	dlo_handle.seg_script = DLO_SCRIPT_DFLT;
	dlo_handle.seg_lang = DLO_LANG_DFLT;
	while(dlo_handle.seg_start < dlo_handle.ucs_cnt)
	{
		if(dlo_handle.mainScript==DLO_SCRIPT_DFLT || dlo_handle.mainLang==DLO_LANG_DFLT)
		{
			size = _DL_DivideStrByScript_New2( dlo_handle.ucs_str, (DT16_ushort)dlo_handle.ucs_cnt, dlo_handle.seg_start, &(dlo_handle.seg_end),
					dlo_handle.writedir, &dlo_handle.seg_script, &dlo_handle.seg_lang, &dlo_handle.seg_dir);
			//DL_GetScriptLang(rang, &pwrk->seg_script,&pwrk->seg_lang);
			//pwrk->seg_dir = GetSegDirectByScript2(pwrk->seg_script);
		}else
		{
			dlo_handle.seg_script = dlo_handle.mainScript;
			dlo_handle.seg_lang	= dlo_handle.mainLang;
			dlo_handle.seg_end = dlo_handle.ucs_cnt;
			dlo_handle.seg_dir = _GetSegDirectByScript2(dlo_handle.seg_script);
		}// end if

		size = dlo_handle.seg_end - dlo_handle.seg_start;
		if(size <= 0)
			break;

		_DFS_GetdlotabHeader(&dlo_handle, &dlo_handle.dloheader, dlo_handle.seg_script, dlo_handle.seg_lang, &dlo_handle.cur_dlotab_idx);

		_DT_FunctionByLang(&dlo_handle, dlo_handle.seg_script, dlo_handle.seg_lang);

		dlo_handle.seg_cnt++;
		if(dlo_handle.seg_cnt >= DLO_SEG_LIMIT)
			break;
		dlo_handle.seg_start += size;
		size=0;
		dlo_handle.segw=0;
		dlo_handle.segh = 0;
	}// end while

	for(i=0; i < dlo_handle.seg_cnt; i++)
	{
		Str_Seg2 ss;
		ss = dlo_handle.segarr[i];

		if(ss.lang == DLO_LANG_ARA && ss.script == DLO_SCRIPT_arab)
			_GetSeginfo_R2L(&dlo_handle, &ss);
		else _GetSeginfo_Latin(&dlo_handle, &ss);
	}// end for

	if(dlo_handle.writedir = DLO_RIGHTTOLEFT)
	{
		int len;
		int pos = dlo_handle.cur_g2idx;
		for(i=0; i < dlo_handle.seg_cnt; i++)
		{
			len = dlo_handle.segarr[i].gxend - dlo_handle.segarr[i].gxstart;
			pos -= len;
			memcpy(str2 + pos, dlo_handle.glyf_seq + dlo_handle.segarr[i].gxstart, len * sizeof(unsigned short));
		}// end for
		str2[dlo_handle.cur_g2idx] = 0;
	}else memcpy(str2, dlo_handle.glyf_seq, dlo_handle.cur_g2idx * sizeof(unsigned short));

	*len2 = dlo_handle.cur_g2idx;

	return 0;
}
#endif

#endif

