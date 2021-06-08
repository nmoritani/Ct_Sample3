#include "DcwShaperVG.h"
#include "DcwLayout.h"
#include "DcwUnicodeRange.h"
#include "DcwLangModule.h"
#include "DcwBiDi.h"

#include "DigiTypeApi.h"
#include "DTmanager.h"
#include "DTdigitype.h"

DT_void decideCopyMethod(pLayWrk pwrk)
{
	// nothing to do for OVG mode.
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
		return;

	// bmp (gray, mono) mode
	pwrk->copyMethod = DLO_CPY_NOT_SPECIFY;
	if(pwrk->lastfedge == DLO_STYLE_BOLD || pwrk->lastfedge == DLO_STYLE_OUTLINE){
		if(pwrk->f_edge==DCW_EDGE_NORMAL && pwrk->bMinusLRsb)
			pwrk->copyMethod = DLO_CPY_NEEDS_ORCPY;
	}
}

DT_void clearg2info(pLayWrk pwrk, DT32_int ucs_cnt)
{
	DT32_int i, sz;
	sz = ucs_cnt * 2;	// *2 is enough for all the language now (Hindi) -- 201101031
	if(sz > sizeof(pwrk->g2info)/sizeof(pwrk->g2info[0]))
		sz = sizeof(pwrk->g2info)/sizeof(pwrk->g2info[0]);
	for(i=0; i<sz; i++){
		pwrk->g2info[i].checkedFlag = 0;
	}
}
DT_BOOL isAllEasyLatin(pLayWrk pwrk, DT16_ushort *ucs_str, DT32_int ucs_cnt)
{
	DT32_int i;
	DT16_ushort *pch = ucs_str;

	for(i=0; i<ucs_cnt; i++, pch++){
		if(*pch<0x007F){						// ASCII
			continue;
		}else if(*pch>=0x3040 && *pch<=0x30FF){	// kana
			continue;
		}else if(*pch>=0x4E00 && *pch<=0x9FFF){	// Chinese
			continue;
		}else{
			return DT_FALSE;
		}
	}
	return DT_TRUE;
}
DT_BOOL isAllCharsLatin(pLayWrk pwrk, DT16_ushort *ucs_str, DT32_int ucs_cnt)
{
	DT32_int i;
	DL_CodeAttr cattr;
	DLO_Script	 sc;
	DLO_Language la;
	for(i=0; i<ucs_cnt; i++){
		cattr = DL_GetCodeCategory(pwrk, ucs_str[i]);
		DL_GetScriptLang(cattr.range, &sc, &la);
		if(DLO_SCRIPT_latn!=sc || DLO_LANG_LAT!=la){
			return DT_FALSE;
		}else{
			if(DL_Mark_SpacingCombining == cattr.cate){	// maybe Vietnamese
				return DT_FALSE;
			}
		}
	}
	return DT_TRUE;
}
DT_BOOL isUseDcwArabicPUA(pLayWrk pwrk)
{
	return pwrk->bUseArabicPUA;
}
// Swap the value of x, y once pwrk->vert is set.
DT_void swapXY(DT32_int* x, DT32_int* y)
{
	DT32_int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}

// return DT_TRUE: ch is an Non-Spacing Mark; else return DT_FALSE
DT_BOOL isCodeNSM(DT16_ushort ch)
{
	if(IS_CDMs(ch))			// including IS_Vietnamese_NSMs()
		return DT_TRUE;
	if(IS_Hebrew_NSMs(ch))
		return DT_TRUE;
	if(IS_Arabic_NSMs(ch))
		return DT_TRUE;
	if(IS_IndicsDevanagari_NSMs(ch))
		return DT_TRUE;
	if(IS_Thai_NSMs(ch))
		return DT_TRUE;

	return DT_FALSE;
}

DT_BOOL isNSM(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx)
{
	if(DLO_BIDI_DCWRULE == pwrk->bidirule)
		return (NSM==bidi_getBidiClass(ch));
	else
		return isCodeNSM(ch);

}

DT_void DcwShaperVGGetVersion(DcwShaperVG_Version *ver)
{
DBG_MSG_SHOW_FUNC_NAME();

	ver->major = (DCWSHAPERVG_VERSION & 0xFFFF0000)>>4;
	ver->minor = (DCWSHAPERVG_VERSION & 0x0000FFFF);
	ver->date  = DCWSHAPERVG_REL_DATE;
}

/* Make the value of codes and glyphs to n_per_glyf in GlyphSeq. */
/* n_per_glyf: the HiByte stands for glyfs, the LowByte stands for codes. */
DT16_ushort Make_n_per_glyf(DT16_ushort codes, DT16_ushort glyfs)
{
DBG_MSG_SHOW_FUNC_NAME();

	/* For easy-understanding and being compatible with previous concept,		*/
	/* only the glyfs>1 will be treat as "multi-glyphs stand for multi-codes,	*/
	/* else it will be considered according codes only.							*/
	if(glyfs>1){ 
		return (glyfs<<8)+codes;
	}else{
		return codes;
	}
}

/* Parse the n_per_glyf in GlyphSeq to codes and glyphs. */
/* n_per_glyf: the HiByte stands for glyfs, the LowByte stands for codes. */
DT_void Parse_n_per_glyf(DT16_ushort n_per_glyf, DT16_ushort *codes, DT16_ushort *glyfs)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(n_per_glyf>0x0100){
		*codes = (n_per_glyf&0x00FF);
		*glyfs = (n_per_glyf&0xFF00)>>8;
	}else{
		*codes = n_per_glyf;
		*glyfs = 1;
	}
}

/* Binary Search */
DT32_int	BinSearchinFile(DT32_int count, DT8_uchar *data, DT16_ushort key)
{
	DT32_int l=1, r=count;/*count is DT16_ushort count, not DT8_uchar count*/
	DT32_int m, ok=0;
	DT16_ushort us;
	DT32_long ofs;

DBG_MSG_SHOW_FUNC_NAME();

	m = (l+r)/2;
	while(l<=r && ok==0)
	{
		ofs = m*2;
		us = ReadUShort(data,ofs);
		if(us>key)		r=m-1;
		else if(us<key) l=m+1;
		else{			ok=1; break;	}
		m = (l+r)/2;
	}
	if(ok)	return m;
	else	return -1;
}


DT16_ushort ReadUShort(DT8_uchar *dlo, DT32_long ofs)
{  
	DT8_uchar *p;
	DT16_ushort val, b1, b2;

DBG_MSG_SHOW_FUNC_NAME();

	p = dlo + ofs;
	b1 = *p++;
	b2 = *p;
	val = (b2<<8) + b1;

  return val;
}

DT32_ulong ReadULong(DT8_uchar *dlo, DT32_long ofs, DT32_int size)
{
	DT8_uchar *p;
	DT32_ulong val, b;
	DT32_int scnt, i;

DBG_MSG_SHOW_FUNC_NAME();

	p = dlo + ofs;
	val = *p++;

	for (i=1,scnt=8; i<size; i++,p++,scnt+=8)
	{
      b = *p << scnt;
      val += b;
	}

  return val;
}

DT16_ushort ReadUShortfromCurpos(pLayWrk pwrk)
{
	DT16_ushort val;

DBG_MSG_SHOW_FUNC_NAME();

	val = ReadUShort(pwrk->dlo, pwrk->curpos);
	pwrk->curpos += 2;
	return val;
}

DT32_ulong ReadULongfromCurpos(pLayWrk pwrk)
{
	DT32_ulong val;

DBG_MSG_SHOW_FUNC_NAME();

	val = ReadULong(pwrk->dlo, pwrk->curpos, 4);
	pwrk->curpos += 4;
	return val;
}

/* Get dlo file header: shaperheader */
DT32_int DFS_GetdloHeader(pLayWrk pwrk)
{
	shaperheader *header = &pwrk->header;
	DT8_char identifier[] = "DFShaper";
	DT32_int i;

DBG_MSG_SHOW_FUNC_NAME();
	
	pwrk->curpos = 0;
	for(i=0;i<8;i++)
	{
	  header->ident[i] = *(pwrk->dlo + i);	pwrk->curpos++;
	  if(header->ident[i] != identifier[i]) return DLO_BAD_LAYDATA;
	}
	header->version		= ReadUShortfromCurpos(pwrk);
	header->dlotabcnt	= ReadUShortfromCurpos(pwrk);
	for(i=0;i<header->dlotabcnt;i++)
	{
	  pwrk->dlotaboff[i] = ReadULongfromCurpos(pwrk);
	}
	header->offsetdlotab = pwrk->dlotaboff;
	
	return DLO_SUCCESS;
}

/* Get DLO_Data_Table header */
DT32_int DFS_GetdlotabHeader(pLayWrk pwrk, DLO_Script scr, DLO_Language lan, DT16_ushort *idx)
{
	dlotabheader *head = &pwrk->dloheader;
	DT32_int tmp = -1;
	DT16_ushort i;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk->dlo)	return DLO_TAB_NOT_EXIST;

	for(i=0;i<pwrk->header.dlotabcnt;i++)
	{
		pwrk->curpos = pwrk->header.offsetdlotab[i];
		if(ReadUShortfromCurpos(pwrk) == scr){
			if(ReadUShortfromCurpos(pwrk) == lan){
				tmp = i; break;
			}
		}
	}
	
	if(-1 == tmp) return DLO_TAB_NOT_EXIST;
	else *idx = (DT16_ushort) tmp;

	pwrk->curpos = pwrk->header.offsetdlotab[*idx];
	head->script = ReadUShortfromCurpos(pwrk);
	head->lang	 = ReadUShortfromCurpos(pwrk);
	head->subtabcnt = ReadUShortfromCurpos(pwrk);
	for(i=0;i<head->subtabcnt;i++)
	{
		pwrk->subtaboff[i] = ReadULongfromCurpos(pwrk);
	}
	head->offsetsubtab = pwrk->subtaboff;

	return DLO_SUCCESS;
}

/* Get segment's direction by script. */
DT16_ushort GetSegDirectByScript(DLO_Script script)
{
DBG_MSG_SHOW_FUNC_NAME();

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

/* language processor										*/
/* scr & lan: please refer to DcwShaperVG.h.				*/
/* func: can be FUNC_RENDERTOBUF or FUNC_GETSEGINFO.		*/
/* para: a pointer to some data required. Now it's Str_Seg*.*/
/* When DLO_DATA_PREPARE_POS, Str_Seg* is not needed. It can be 0.	*/
DT32_int FunctionByLang(pLayWrk pwrk, DLO_Script scr, DLO_Language lan, DT32_int func, DT_void *para)
{
	/* Add another language here. Refer to DcwLangModule.h & DcwShaperVG.h	*/
	/* Every language have to prepare to functions: RenderToBuf & GetSeginfo*/
	const LangFunc LangFuncTab[] = {
#ifdef LATIN_latin
		{DLO_SCRIPT_latn, DLO_LANG_LAT, RenderToBuf_Latin, GetSeginfo_Latin, CalcPosition_Latin, RenderByPos_Latin},
#endif
#ifdef ARABIC_arabic
		{DLO_SCRIPT_arab, DLO_LANG_ARA, RenderToBuf_Arabic, GetSeginfo_Arabic, CalcPosition_Arabic, RenderByPos_Arabic},
#endif
#ifdef THAI_thai
		{DLO_SCRIPT_thai, DLO_LANG_THA, RenderToBuf_Thai, GetSeginfo_Thai, CalcPosition_Thai, RenderByPos_Thai},
#endif
#ifdef INDICS_devanagari
		{DLO_SCRIPT_deva, DLO_LANG_HIN, RenderToBuf_Devanagari, GetSeginfo_Devanagari, CalcPosition_Devanagari, RenderByPos_Devanagari},
#endif
#ifdef INDICS_tamil
		{DLO_SCRIPT_taml, DLO_LANG_TAM, RenderToBuf_Tamil, GetSeginfo_Tamil, CalcPosition_Tamil, RenderByPos_Tamil},
#endif
#ifdef HEBREW_hebrew
		{DLO_SCRIPT_hebr, DLO_LANG_IWR, RenderToBuf_Hebrew, GetSeginfo_Hebrew, CalcPosition_Hebrew, RenderByPos_Hebrew},
#endif
	};

	/* Search for the match LangFunc, laidx is the index in LangFuncTab. */
	DT32_uint i,  laidx=0;
	DT32_int ret=DLO_SUCCESS;

DBG_MSG_SHOW_FUNC_NAME();

	for(i=0; i<(DT32_int)sizeof(LangFuncTab)/sizeof(LangFunc); i++){
	  if( scr==LangFuncTab[i].sc && lan==LangFuncTab[i].ln ){laidx=i; break;}
	}

	switch(func){
	case FUNC_RENDERTOBUF:
		ret = LangFuncTab[laidx].RenderToBuf(pwrk,para);
		break;
	case FUNC_GETSEGINFO:
		ret = LangFuncTab[laidx].GetSeginfo(pwrk,para);
		break;
	case FUNC_CALCPOSITION:
		ret = LangFuncTab[laidx].CalcPosition(pwrk,para);
		break;
	case FUNC_RENDERBYPOS:
		ret = LangFuncTab[laidx].RenderByPos(pwrk,para);
		break;
	default:
		break;
	}
	
	return ret;
}

DT32_int EstimateFontEngineGradMem(DLO_EngineType type, DT32_int szx, DT32_int szy, DT32_int grade)
{
	DT32_int option=0;

DBG_MSG_SHOW_FUNC_NAME();

	switch(type){

#ifdef DIGITYPE_OUL
	case DLO_ENG_DCWOPENVG:
		return 0;
#endif

#ifdef DIGITYPE_STD
	case DLO_ENG_DCWRASTER_MONO:
		return 0;
	case DLO_ENG_DCWRASTER_GRAY16:
	case DLO_ENG_DCWRASTER_GRAY256:
		if(gDT_Set_Fix_Memory_Size==1){
			return ras_EstimateWkMem(szx, szy, grade, RAS_ESTIMATE_GRAD_WKMEM);
		}else{
			return 0;
		}
#endif

#ifdef BDF_RASTER
	case DLO_ENG_BDFRASTER:
		return 0;
#endif

#ifdef DIF_RASTER
	case DLO_ENG_DIFRASTER_BIT:
	case DLO_ENG_DIFRASTER_BYTE:
		return 0;
#endif
		
	default:
		return DLO_FONTENGINE_NOT_SUPPORT;
	}
	return DLO_FONTENGINE_NOT_SUPPORT;
}

DT32_int EstimateFontEngineWkMem(DLO_EngineType type, DT32_int szx, DT32_int szy, DT32_int grade)
{
	DT32_int option=0;

DBG_MSG_SHOW_FUNC_NAME();

	switch(type){

#ifdef DIGITYPE_OUL
	case DLO_ENG_DCWOPENVG:
		return oul_EstimateWkMem();
#endif

#ifdef DIGITYPE_STD
	case DLO_ENG_DCWRASTER_MONO:
	case DLO_ENG_DCWRASTER_GRAY16:
	case DLO_ENG_DCWRASTER_GRAY256:
		if(gDT_Set_Fix_Memory_Size==1)
			option = RAS_ESTIMATE_BASE_WKMEM;
		else
			option = RAS_ESTIMATE_DEFT_WKMEM;
		return ras_EstimateWkMem(szx, szy, grade, option);
#endif

#ifdef BDF_RASTER
	case DLO_ENG_BDFRASTER:
		return bdf_EstimateWkMem();
#endif

#ifdef DIF_RASTER
	case DLO_ENG_DIFRASTER_BIT:
	case DLO_ENG_DIFRASTER_BYTE:
		return dif_EstimateWkMem();
#endif
		
	default:
		return DLO_FONTENGINE_NOT_SUPPORT;
	}
	return DLO_FONTENGINE_NOT_SUPPORT;
}

/* Load font engine functions to pwrk->fengfuncs */
DT32_int LoadFontEngineFuncs(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();

	switch(pwrk->fengtype){

#ifdef DIGITYPE_OUL
	case DLO_ENG_DCWOPENVG:
		pwrk->fengfuncs.initFont	= oul_initFont;
		pwrk->fengfuncs.uninitFont	= oul_uninitFont;
		pwrk->fengfuncs.getAwidth	= oul_getAwidth;
		pwrk->fengfuncs.getAwidth2	= oul_getAwidth2;
		pwrk->fengfuncs.getExten	= oul_getExten;
		pwrk->fengfuncs.getAheight	= oul_getAheight;
		pwrk->fengfuncs.getLogh		= oul_getLogh;
		pwrk->fengfuncs.getLogt		= oul_getLogt;
		pwrk->fengfuncs.getHeight	= oul_getHeight;
		pwrk->fengfuncs.getWidth	= oul_getWidth;
		pwrk->fengfuncs.getAexten	= oul_getAexten;
		pwrk->fengfuncs.getVexten	= oul_getVexten;
		pwrk->fengfuncs.getEdge		= oul_getEdge;
		pwrk->fengfuncs.getOutline	= oul_getOutline;
		pwrk->fengfuncs.getDesignInfo=oul_getDesignInfo;
		pwrk->fengfuncs.chkGlyphExist=oul_chkGlyphExist; 

		/* Special functions only available in DLO_ENG_DCWOPENVG */
		pwrk->fengfuncs.getCharOul	= oul_getCharOul;
		pwrk->fengfuncs.fastCharOul	= oul_fastCharOul;
		pwrk->fengfuncs.getDesignGlobalInfo = oul_getDesignGlobalInfo;
		pwrk->fengfuncs.FDL_ReadInt = oulFDL_ReadInt;
		pwrk->fengfuncs.getAwidth_pix = oul_getAwidth_pix;
		break;
#endif

#ifdef DIGITYPE_STD
	case DLO_ENG_DCWRASTER_MONO:
	case DLO_ENG_DCWRASTER_GRAY16:
	case DLO_ENG_DCWRASTER_GRAY256:
		pwrk->fengfuncs.initFont	= ras_initFont;
		pwrk->fengfuncs.uninitFont	= ras_uninitFont;
		pwrk->fengfuncs.getAwidth	= ras_getAwidth;
		pwrk->fengfuncs.getAwidth2	= ras_getAwidth2;
		pwrk->fengfuncs.getExten	= ras_getExten;
		pwrk->fengfuncs.getAheight	= ras_getAheight;
		pwrk->fengfuncs.getLogh		= ras_getLogh;
		pwrk->fengfuncs.getLogt		= ras_getLogt;
		pwrk->fengfuncs.getHeight	= ras_getHeight;
		pwrk->fengfuncs.getWidth	= ras_getWidth;
		pwrk->fengfuncs.getAexten	= ras_getAexten;
		pwrk->fengfuncs.getVexten	= ras_getVexten;
		pwrk->fengfuncs.getEdge		= ras_getEdge;
		pwrk->fengfuncs.getCharbmp	= ras_getCharbmp;
		pwrk->fengfuncs.getDesignInfo = ras_getDesignInfo;
		pwrk->fengfuncs.chkGlyphExist=ras_chkGlyphExist; 

		/* Special functions only available in DLO_ENG_DCWRASTER_XXXX */
		pwrk->fengfuncs.getDesignGlobalInfo = ras_getDesignGlobalInfo;
		pwrk->fengfuncs.FDL_ReadInt = rasFDL_ReadInt;
		break;
#endif

#ifdef BDF_RASTER
	case DLO_ENG_BDFRASTER:
		pwrk->fengfuncs.initFont	= bdf_initFont;
		pwrk->fengfuncs.uninitFont	= bdf_uninitFont;
		pwrk->fengfuncs.getAwidth	= bdf_getAwidth;
		pwrk->fengfuncs.getAwidth2	= bdf_getAwidth2;
		pwrk->fengfuncs.getExten	= bdf_getExten;
		pwrk->fengfuncs.getAheight	= bdf_getAheight;
		pwrk->fengfuncs.getLogh		= bdf_getLogh;
		pwrk->fengfuncs.getLogt		= bdf_getLogt;
		pwrk->fengfuncs.getHeight	= bdf_getHeight;
		pwrk->fengfuncs.getWidth	= bdf_getWidth;
		pwrk->fengfuncs.getAexten	= bdf_getAexten;
		pwrk->fengfuncs.getVexten	= bdf_getVexten;
		pwrk->fengfuncs.getEdge		= bdf_getEdge;
		pwrk->fengfuncs.getCharbmp	= bdf_getCharbmp;
		pwrk->fengfuncs.getDesignInfo=bdf_getDesignInfo;
		pwrk->fengfuncs.chkGlyphExist=bdf_chkGlyphExist; 
		break;
#endif

#ifdef DIF_RASTER
	case DLO_ENG_DIFRASTER_BIT:
	case DLO_ENG_DIFRASTER_BYTE:
		pwrk->fengfuncs.initFont	= dif_initFont;
		pwrk->fengfuncs.uninitFont	= dif_uninitFont;
		pwrk->fengfuncs.getAwidth	= dif_getAwidth;
		pwrk->fengfuncs.getAwidth2	= dif_getAwidth2;
		pwrk->fengfuncs.getExten	= dif_getExten;
		pwrk->fengfuncs.getAheight	= dif_getAheight;
		pwrk->fengfuncs.getLogh		= dif_getLogh;
		pwrk->fengfuncs.getLogt		= dif_getLogt;
		pwrk->fengfuncs.getHeight	= dif_getHeight;
		pwrk->fengfuncs.getWidth	= dif_getWidth;
		pwrk->fengfuncs.getAexten	= dif_getAexten;
		pwrk->fengfuncs.getVexten	= dif_getVexten;
		pwrk->fengfuncs.getEdge		= dif_getEdge;
		pwrk->fengfuncs.getCharbmp	= dif_getCharbmp;
		pwrk->fengfuncs.getDesignInfo=dif_getDesignInfo;
		pwrk->fengfuncs.chkGlyphExist=dif_chkGlyphExist; 
		break;
#endif	
	default:
		return DLO_FONTENGINE_NOT_SUPPORT;
	}
	return DLO_SUCCESS;
}

/* Load font engine functions to pwrk->fengfuncs */
DT_void LoadIconFontEngineFuncs(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();

#ifdef DIF_RASTER
	if(pwrk->iconfontcnt>0 && pwrk->icon_DT_Font){
		pwrk->iconfuncs.initFont	= dif_initFont;
		pwrk->iconfuncs.uninitFont	= dif_uninitFont;
		pwrk->iconfuncs.getAwidth	= dif_getAwidth;
		pwrk->iconfuncs.getAwidth2	= dif_getAwidth2;
		pwrk->iconfuncs.getExten	= dif_getExten;
		pwrk->iconfuncs.getAheight	= dif_getAheight;
		pwrk->iconfuncs.getHeight	= dif_getHeight;
		pwrk->iconfuncs.getWidth	= dif_getWidth;
		pwrk->iconfuncs.getAexten	= dif_getAexten;
		pwrk->iconfuncs.getVexten	= dif_getVexten;
		pwrk->iconfuncs.getEdge		= dif_getEdge;
		pwrk->iconfuncs.getCharbmp	= dif_getCharbmp;
		pwrk->iconfuncs.getDesignInfo=dif_getDesignInfo;
		pwrk->iconfuncs.chkGlyphExist=dif_chkGlyphExist;
	}
#endif	
}

DT32_int AllocEngWorkMem(pLayWrk pwrk, DT32_int estmsz)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(estmsz==0){
		return DLO_SUCCESS;	/* Not required. pwrk->fengtype==DLO_ENG_DIFRASTER_BIT or BYTE */
	}
	pwrk->engWkMem = (DT8_char*)DT_malloc(DT_ALLOC_SIZE(estmsz));
	if(!pwrk->engWkMem){
		return DLO_NOT_ENOUGH_ENGINEWKMEM;
	}else{
		pwrk->engWkMemsz= DT_ALLOC_SIZE(estmsz);	//estmsz;
		DT_memset(pwrk->engWkMem,0,pwrk->engWkMemsz);
	}
	return DLO_SUCCESS;
}

DT32_int ReAllocEngWorkMem(pLayWrk pwrk)
{
	DT32_int memstep, wkmsz;
	DLO_EngineType engtype;
	DT8_char *ptr;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

	/* Set the step when adding font engine working memory */
	if(pwrk){
		engtype = pwrk->fengtype;
		switch(engtype){
		case DLO_ENG_BDFRASTER:
			memstep = 0x100*sizeof(DT32_long);
			break;
		case DLO_ENG_DCWRASTER_MONO:
			memstep = DLO_WKMSIZE_STEP;
			if(pwrk->grade==DLO_GRAY_16||pwrk->grade==DLO_GRAY_256){
				/* continue to next case */
			}else{
				break;
			}
		case DLO_ENG_DCWRASTER_GRAY16:
			memstep = 0x2000;
			if(pwrk->grade==DLO_GRAY_256){
				/* continue to next case */
			}else{
				break;
			}
		case DLO_ENG_DCWRASTER_GRAY256:
			memstep = 0x10000;
			break;
		case DLO_ENG_DCWOPENVG:
			memstep = DLO_WKMSIZE_STEP;
			break;
		case DLO_ENG_DIFRASTER_BIT:
		case DLO_ENG_DIFRASTER_BYTE:
			memstep = 0;	/* DIF_Raster don't need wrk mem. */
			break;
		default:
			memstep = DLO_WKMSIZE_STEP;
		}
	}else{
		memstep = DLO_WKMSIZE_STEP;
	}

	wkmsz = pwrk->engWkMemsz + memstep;
//	ptr = (DT8_char*)DT_realloc(pwrk->engWkMem,DT_ALLOC_SIZE(wkmsz));		//Jacky_20101025_for_Performance
	if(pwrk->engWkMem){
		DT_free(pwrk->engWkMem);
	}
	ptr = (DT8_char*)DT_malloc(DT_ALLOC_SIZE(wkmsz));
	if(!ptr){
		return DLO_NOT_ENOUGH_ENGINEWKMEM;
	}else{
		pwrk->engWkMem  = ptr;
		pwrk->engWkMemsz= DT_ALLOC_SIZE(wkmsz);		//wkmsz;
		DT_memset(pwrk->engWkMem,0,pwrk->engWkMemsz);
	}
	
	return DLO_SUCCESS;
}

DT32_long AllocWorkMem(pLayWrk *ppwrk)
{
	//DT_void *lpwrk=NULL;
	pLayWrk pwrk=NULL;
	DT32_int msz;

DBG_MSG_SHOW_FUNC_NAME();

	/* Allocate & set the main working memory. */
	msz = sizeof(LayWrk);
	msz += sizeof(DifRaster_Attr);

	/* The required attribute data. */
	msz += DLO_RAS_ATTR_SIZE;

	if(!(*ppwrk)){	/* The working Memory for DcwShaper isn't create. */
		pwrk = (pLayWrk)DT_malloc( DT_ALLOC_SIZE(msz) );
		if(!pwrk)
			return DLO_NOT_ENOUGH_LAYWKMEM;
		else{
			//Jacky_20101025_for_Performance. 
			//This line isn't be commented, because DT_memory_init() in DTplatform.c wasn't clear to 0.
			DT_memset(pwrk, 0, DT_ALLOC_SIZE(msz));		/* the working memory are cleared. some openvg handle, like myvgfont, myglyphpath.., are cleared, too. */
			pwrk->dlowkm.lWkMem	 = (DT8_char*)pwrk;
			pwrk->dlowkm.lWkMemsize = sizeof(LayWrk);//msz;
			/* Set the pointer to attribute data. */
			pwrk->icon_attr= (DT8_char*)pwrk + pwrk->dlowkm.lWkMemsize;
			pwrk->ras_attr = (DT8_char*)pwrk->icon_attr + sizeof(DifRaster_Attr);//(DT8_char*)pwrk + pwrk->dlowkm.lWkMemsize;
			*ppwrk = pwrk;
		}
	}

	return DT_ALLOC_SIZE(msz);		//msz;
}

/* Clear the working memory */
DT_void Clearwrk(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();
	//Jacky_20101025_for_Performance

//	DT_memset(pwrk->gseq1,0,DLO_MAXCODES_PER_STR_SEG*sizeof(DT16_ushort));
//	DT_memset(pwrk->gseq2,0,DLO_MAXCODES_PER_STR_SEG*sizeof(DT16_ushort));
//	DT_memset(pwrk->gseq,0,DLO_MAXCODES_PER_STR_SEG*sizeof(GlyphSeq));
//	DT_memset(pwrk->awseq,0,DLO_MAXCODES_PER_STR_SEG*sizeof(CodeAw));
//	DT_memset(pwrk->segarr,0,DLO_SEG_LIMIT*sizeof(Str_Seg));

}

/* Clear the value in GlyfOperate*/
DT_void ClearGlyfOperate(bmpGlyfOperate *go)
{
DBG_MSG_SHOW_FUNC_NAME();

	go->gpoff.x = 0;
	go->gpoff.y = 0;
	go->lenth  = 0;
	go->height = 0;
	go->operate = 0;
}

/* Clear the array of dlotable & subtable */
//DT_void Clean(pLayWrk pwrk)
//{
//DBG_MSG_SHOW_FUNC_NAME();
//
//	DT_memset(pwrk->dlotaboff,0,256);
//	DT_memset(pwrk->subtaboff,0,32);
//}

DT32_int Calxbytes(pLayWrk pwrk, DT32_int w)
{
	DT32_int xbytes=0;
	DT32_int align;
	DT32_int diff = 0;

DBG_MSG_SHOW_FUNC_NAME();

	if(pwrk->xbytes_align==0){
		pwrk->xbytes_align = 4;
	}
	align = pwrk->xbytes_align;
	if(pwrk->mode&DLO_LAYOUT_BIT){
		diff = align*8 - 1;
		xbytes = (w+diff)/(align*8)*align;	/*(w+31)/32*4;*/
	}else if(pwrk->mode&DLO_LAYOUT_BYTE){
		diff = align - 1;
		xbytes = (w+diff)/align*align;		/*(w+3)/4*4;*/
	}
	return xbytes;
}

DT32_int SetCurrentBidiCtrl(pLayWrk pwrk, DT16_ushort bidictrl)
{
	switch(bidictrl){
	case chLRE:
	case chRLE:
	case chLRO:
	case chRLO:
		pwrk->curbidi++;
		pwrk->bidictrls[pwrk->curbidi] = bidictrl;
		break;
	case chPDF:
		if(pwrk->curbidi>=0){
			pwrk->bidictrls[pwrk->curbidi] = 0;
			pwrk->curbidi--;
			//No need to remove the code in pwrk->bidictrls[];
		}	//pwrk->curbidi will be -1 or >=0.
		break;
	case chLRM:
	case chRLM:
	default:
		// do nothing.
		break;
	}
	return pwrk->curbidi;
}

DT16_ushort GetCurrentBidiCtrl(pLayWrk pwrk)
{
	if(pwrk->curbidi<0 || pwrk->curbidi>=sizeof(pwrk->bidictrls)/sizeof(pwrk->bidictrls[0])){
		return 0;
	}

	return pwrk->bidictrls[pwrk->curbidi];
}

DT_BOOL isNeedReverse(pLayWrk pwrk)
{
	DT_BOOL ret = DT_FALSE;
	DT16_ushort ctrl;
	ctrl = GetCurrentBidiCtrl(pwrk);
	if(chRLO==ctrl)
	{
		switch(pwrk->seg_script){
		case	DLO_SCRIPT_arab:
		case	DLO_SCRIPT_hebr:
		case	DLO_SCRIPT_deva:
			break;
		case	DLO_SCRIPT_DFLT:
		case	DLO_SCRIPT_latn:
		case	DLO_SCRIPT_thai:
		case	DLO_SCRIPT_taml:
		default:
			ret = DT_TRUE;
		}
	}else if(chLRO==ctrl)
	{
		switch(pwrk->seg_script){
		case	DLO_SCRIPT_arab:
		case	DLO_SCRIPT_hebr:
			ret = DT_TRUE;
			break;
		case	DLO_SCRIPT_DFLT:
		case	DLO_SCRIPT_latn:
		case	DLO_SCRIPT_thai:
		case	DLO_SCRIPT_deva:
		case	DLO_SCRIPT_taml:
		default:
			break;
		}		
	}

	return ret;
}


DT_BOOL isGlyphNeedReverseNsm(pLayWrk pwrk)
{
	DT_BOOL ret = DT_FALSE;
	switch(pwrk->seg_script){
		case DLO_SCRIPT_deva:
			break;
		default:
		ret = DT_TRUE;
	}
	return ret;
}

DT_void ReAdjustPosY(pLayWrk pwrk, DT32_int *bmph)
{
	// iter all the glyphs, get the max negative moveY
	DT32_int i, ht, dn, oy, sz, moveYup, moveYdn, moveYup_pix;
	//DT32_int maxht, hd;
	pDT_FontMgr_wrk	pmgrwrk=((DT_Font*)(pwrk->cur_DT_Font))->fontmgr;
	DT32_int offsety, offsety_pix;
	DT16_ushort nowglyph;

	moveYup = 0; moveYdn = 0;	moveYup_pix = 0;

	if(pwrk->vert)
		sz = pwrk->xsize;
	else
		sz = pwrk->ysize;

	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
		for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
		{
			nowglyph = pwrk->lobuf->glyf_seq[i];
			pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, i, DLO_CHARATTR_GET_OFFSETY, &offsety);
			offsety = DT_FORCE_MOVE_DOWN_PIXS(gDT_FONT_EMSIZE, offsety);
			offsety_pix = DT_FORCE_MOVE_DOWN_PIXS(sz, offsety);

			offsety += pwrk->lobuf->caret_seq[i].oripos.y;
			//if(pwrk->lobuf->caret_seq[i].oripos.y + offsety < moveYup)
			//	moveYup = pwrk->lobuf->caret_seq[i].oripos.y + offsety;
			if(offsety < moveYup)
				moveYup = offsety;

			offsety_pix += DT_FORCE_MOVE_DOWN_PIXS(sz, pwrk->lobuf->caret_seq[i].oripos.y);
			if(offsety_pix < moveYup_pix)
				moveYup_pix = offsety_pix;

			dn = need_Move_Down_Pixs(pwrk, nowglyph, i);
			if(dn > moveYdn)	// don't use oripos.y because Thai will move some glyph down.
				moveYdn = dn;
		}
	}else{
		for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
		{
			if(pwrk->lobuf->caret_seq[i].oripos.y < moveYup)
				moveYup = pwrk->lobuf->caret_seq[i].oripos.y;

			dn = need_Move_Down_Pixs(pwrk, pwrk->lobuf->glyf_seq[i], i);
			if(dn > moveYdn)	// don't use oripos.y because Thai will move some glyph down.
				moveYdn = dn;
		}
	}

	if(moveYup < 0)
		*bmph += DTAbs(moveYup);
	if(moveYdn > 0)
		*bmph += DTAbs(moveYdn);

#if (1==DT_OPENVG_ENABLED)
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
		// re-adjust oripos.y of all the glyphs
//		if(0 > moveYup)
//		{
//			if(pwrk->vert){
//				for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
//				{
//					oy = pwrk->lobuf->caret_seq[i].oripos.y;
//					oy += *bmph;
//					oy -= gDT_FONT_EMSIZE;
//					pwrk->lobuf->caret_seq[i].oripos.y = -oy;
//				}
//			}else{
//				for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
//				{
//					pwrk->lobuf->caret_seq[i].oripos.y += DTAbs(moveYup);
//				}
//			}
//		}
		DT32_int mvYupAbs;// = (moveYup < 0) ? DTAbs(moveYup) : 0;
		DT32_int logh = 0, logt = 0;
		DT_BOOL  bNeedloop;
		pDcwOpenVG_Attr	ovgattr = (pDcwOpenVG_Attr)pwrk->ras_attr;
		//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, 0x0915, -1, DLO_CHARATTR_GET_LOGHEIGHT, &logh);
		//bNeedloop = !(mvYupAbs==0) || pwrk->ratio/*logh*/;	// pwrk->ratio is assigned only when it had been to Prerender_Devanagari().
		bNeedloop = (moveYup<0) || pwrk->ratio;
		if(bNeedloop){
			DT_BOOL bModified = DT_FALSE;
			DT32_int /*pixoy,*/ pixlogh, pixlogt;
			if(pwrk->vert){
				// TODO:			//2012-10-17(Jacky):
				// Because DT_VERT_BY_OVG is enabled always, pwrk->vert won't be enabled here!
				// Not implement logt & pixlogt, keeplogt, keeplogt_pix. (vert is not required now)
				if(pwrk->ratio){
					sz = pwrk->xsize;
					mvYupAbs	= (moveYup < 0) ? DTAbs(moveYup) : 0;
					moveYup_pix = (moveYup_pix<0) ? DTAbs(moveYup_pix) : 0;
					for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
					{
						ovgattr->bPix = DT_FALSE;
						nowglyph = pwrk->lobuf->glyf_seq[i];
						logh = pwrk->fengfuncs.getLogh(pwrk->ras_attr, nowglyph, i);
						if(logh > 0){
							DT32_int oriy = 0;
							pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, i, DLO_CHARATTR_GET_OFFSETY, &offsety);
							offsety = DT_FORCE_MOVE_DOWN_PIXS(gDT_FONT_EMSIZE, offsety);
							oriy = pwrk->lobuf->caret_seq[i].oripos.y + offsety;
							logh += oriy;
							if(logh > pwrk->linebufh){
								pwrk->linebufh = logh;
								bModified = DT_TRUE;
							}
							if(gDT_EachGlyphWidth_on_Pixels){
								ovgattr->bPix = DT_TRUE;
								pixlogh = pwrk->fengfuncs.getLogh(pwrk->ras_attr, nowglyph, i);
								//pixoy	= oriy * pwrk->ratio / DLO_BASE_RATIO;
								//pixlogh	+= DLO_ADJUST_W_H(pixoy,sz);
								pixlogh	+= DT_FORCE_MOVE_DOWN_PIXS(sz, offsety) + DT_FORCE_MOVE_DOWN_PIXS(sz, pwrk->lobuf->caret_seq[i].oripos.y) + moveYup_pix;
								if(pixlogh > pwrk->linebufh_pixel){
									pwrk->linebufh_pixel = pixlogh;
								}
							}
						}
					}
				}
				if(mvYupAbs > 0){
					for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
					{
						oy = pwrk->lobuf->caret_seq[i].oripos.y;
						oy += *bmph;
						oy -= gDT_FONT_EMSIZE;
						pwrk->lobuf->caret_seq[i].oripos.y = -oy;
					}
				}
			}else{
				DT32_int keeplogt = 0x7FFF, keeplogt_pix=0x7FFF;	// logt should be between 0-gDT_FONT_EMSIZE originally, might be double or triple after scale. 
				sz = pwrk->ysize;	//DLO_SCALED_SIZEXY(pwrk->ysize,pwrk->ratio);
//				if(pwrk->ratio){
//					bModified	= DT_FALSE;
//					for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
//					{
//						ovgattr->bPix = DT_FALSE;
//						nowglyph = pwrk->lobuf->glyf_seq[i];
//						logt = pwrk->fengfuncs.getLogt(pwrk->ras_attr, nowglyph, i);
//						if(logt > 0){
//							if(logt < keeplogt){
//								keeplogt = logt;
//								bModified = DT_TRUE;
//							}
//							ovgattr->bPix = DT_TRUE;
//							pixlogt = pwrk->fengfuncs.getLogt(pwrk->ras_attr, nowglyph, i);
//							if(pixlogt < keeplogt_pix){
//								keeplogt_pix = pixlogt;
//								bModified = DT_TRUE;
//							}
//						}
//					}
//				}
//				if(moveYup < 0 && bModified /*&& keeplogt > 0*/){
//					moveYup += keeplogt;
//					moveYup_pix += keeplogt_pix;
//				}
//				if(moveYup > 0){
//					moveYup = 0;
//					moveYup_pix = 0;
//				}

				mvYupAbs	= (moveYup < 0) ? DTAbs(moveYup) : 0;
				moveYup_pix = (moveYup_pix<0) ? DTAbs(moveYup_pix) : 0;
				bModified	= DT_FALSE;

//				for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
//				{
//					//pwrk->lobuf->caret_seq[i].oripos.y += mvYupAbs;	// do it later
//					
//					if(pwrk->ratio){
//						ovgattr->bPix = DT_FALSE;
//						nowglyph = pwrk->lobuf->glyf_seq[i];
//						logh = pwrk->fengfuncs.getLogh(pwrk->ras_attr, nowglyph, i);
//						if(logh > 0){
//							DT32_int oriy = 0;
//							pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, i, DLO_CHARATTR_GET_OFFSETY, &offsety);
//							offsety = DT_FORCE_MOVE_DOWN_PIXS(gDT_FONT_EMSIZE, offsety);
//							oriy = pwrk->lobuf->caret_seq[i].oripos.y + mvYupAbs + offsety;
//							logh += oriy;				//pwrk->lobuf->caret_seq[i].oripos.y;
//							if(logh > pwrk->linebufh){
//								pwrk->linebufh = logh;
//								bModified = DT_TRUE;
//							}
//							if(gDT_EachGlyphWidth_on_Pixels){
//								ovgattr->bPix = DT_TRUE;
//								pixlogh = pwrk->fengfuncs.getLogh(pwrk->ras_attr, nowglyph, i);
//								pixlogh	+= DT_FORCE_MOVE_DOWN_PIXS(sz, offsety) + DT_FORCE_MOVE_DOWN_PIXS(sz, pwrk->lobuf->caret_seq[i].oripos.y) + moveYup_pix;
//								if(pixlogh > pwrk->linebufh_pixel){
//									pwrk->linebufh_pixel = pixlogh;
//								}
//							}
//						}
//					}
//					pwrk->lobuf->caret_seq[i].oripos.y += mvYupAbs;
// 				}
				if(pwrk->ratio){
					// use a for loop to calc keeplogt, linebufh...
					for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
					{					
						ovgattr->bPix = DT_FALSE;
						nowglyph = pwrk->lobuf->glyf_seq[i];
						logh = pwrk->fengfuncs.getLogh(pwrk->ras_attr, nowglyph, i);
						if(logh > 0){
							DT32_int oriy = 0;
							pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, i, DLO_CHARATTR_GET_OFFSETY, &offsety);
							offsety = DT_FORCE_MOVE_DOWN_PIXS(gDT_FONT_EMSIZE, offsety);
							logt = pwrk->fengfuncs.getLogt(pwrk->ras_attr, nowglyph, i);
							oriy = pwrk->lobuf->caret_seq[i].oripos.y + mvYupAbs + offsety;
							logh += oriy;				//pwrk->lobuf->caret_seq[i].oripos.y;
							if(logh > pwrk->linebufh){
								pwrk->linebufh = logh;
								bModified = DT_TRUE;
							}
							logt += oriy;
							if(logt < keeplogt){
								keeplogt = logt;
							}
							if(gDT_EachGlyphWidth_on_Pixels){
								DT32_int oriy_pix;
								ovgattr->bPix = DT_TRUE;
								pixlogh = pwrk->fengfuncs.getLogh(pwrk->ras_attr, nowglyph, i);
								pixlogt = pwrk->fengfuncs.getLogt(pwrk->ras_attr, nowglyph, i);
								oriy_pix= DT_FORCE_MOVE_DOWN_PIXS(sz, offsety) + DT_FORCE_MOVE_DOWN_PIXS(sz, pwrk->lobuf->caret_seq[i].oripos.y) + moveYup_pix;
								pixlogh	+= oriy_pix;
								if(pixlogh > pwrk->linebufh_pixel){
									pwrk->linebufh_pixel = pixlogh;
								}
								pixlogt += oriy_pix;
								if(pixlogt < keeplogt_pix){
									keeplogt_pix = pixlogt;
								}
							}
						}
					}
					// update moveYup according to keeplogt.
					if(moveYup < 0 && bModified ){
						moveYup += keeplogt;
						if(gDT_EachGlyphWidth_on_Pixels){
							moveYup_pix += keeplogt_pix;
						}
						if(moveYup > 0){
							moveYup = 0;
							if(gDT_EachGlyphWidth_on_Pixels){
								moveYup_pix = 0;
							}
						}
						// renew linebufh as moveYup had been changed.
						pwrk->linebufh -= mvYupAbs;
						if(gDT_EachGlyphWidth_on_Pixels){
							pwrk->linebufh_pixel -= moveYup_pix;
						}
						mvYupAbs	= (moveYup < 0) ? DTAbs(moveYup) : 0;
						moveYup_pix = (moveYup_pix<0) ? DTAbs(moveYup_pix) : 0;
						pwrk->linebufh += mvYupAbs;
						if(gDT_EachGlyphWidth_on_Pixels){
							pwrk->linebufh_pixel += moveYup_pix;
						}
					}

					if(0 != mvYupAbs){
						for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
						{
							pwrk->lobuf->caret_seq[i].oripos.y += mvYupAbs;
						}
					}
				}
			}
			if(bModified && pwrk->linebufh>0 && pwrk->linebufh<*bmph){
				//*bmph = (pwrk->linebufh>gDT_FONT_EMSIZE) ? pwrk->linebufh : gDT_FONT_EMSIZE;
				*bmph = pwrk->linebufh;
			}
		}
	}else
#endif	
	{
		// re-adjust oripos.y of all the glyphs
//		if(0 > moveYup)
//		{
//			for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
//			{
//				pwrk->lobuf->caret_seq[i].oripos.y += DTAbs(moveYup);
//			}
//		}
		DT32_int mvYupAbs;// = (moveYup < 0) ? DTAbs(moveYup) : 0;
		DT32_int logh = 0, logt = 0, szy = pwrk->vert ? pwrk->xsize : pwrk->ysize;
		DT_BOOL  bNeedloop;
		//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, 0x0915, -1, DLO_CHARATTR_GET_LOGHEIGHT, &logh);
		//bNeedloop = !(mvYupAbs==0) || pwrk->ratio/*logh*/;	// pwrk->ratio is assigned only when it had been to Prerender_Devanagari().
		bNeedloop = (moveYup < 0) || pwrk->ratio;
		if(bNeedloop){
			DT_BOOL bModified = DT_FALSE;
			DT32_int keeplogt = 0x7FFF;		// logt should be between 0-1000 originally, might be double or triple after scale.
			for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
			{
				logt = pwrk->fengfuncs.getLogt(pwrk->ras_attr, pwrk->lobuf->glyf_seq[i], i);
				if(logt > 0){
					logt += pwrk->lobuf->caret_seq[i].oripos.y;		// logt in FDL GrayBmp needs to care about its origin y.
					if(logt < keeplogt){
						keeplogt = logt;
						bModified = DT_TRUE;
					}
				}
			}
			
			if(moveYup < 0 && bModified /*&& keeplogt > 0*/){
				moveYup = keeplogt; 
				if(moveYup > 0)
					moveYup = 0;
			}
			bModified = DT_FALSE;
			mvYupAbs = (moveYup < 0) ? DTAbs(moveYup) : 0;
			for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
			{
				pwrk->lobuf->caret_seq[i].oripos.y += mvYupAbs;
				logh = pwrk->fengfuncs.getLogh(pwrk->ras_attr, pwrk->lobuf->glyf_seq[i], i);
				if(logh > 0){
					logh += pwrk->lobuf->caret_seq[i].oripos.y;			// oripos.y must be positive now.
					if(logh > pwrk->linebufh){
						pwrk->linebufh = logh;
						bModified = DT_TRUE;
					}
				}
			}
			if(bModified && pwrk->linebufh>0 && pwrk->linebufh<*bmph){
				//*bmph = (pwrk->linebufh>pwrk->ysize) ? pwrk->linebufh : pwrk->ysize;
				*bmph = pwrk->linebufh;
			}
			//moveYup += keeplogt;
		}

		if(pwrk->vert){
			for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
			{
				oy = pwrk->lobuf->caret_seq[i].oripos.y;
				ht = pwrk->fengfuncs.getAheight(pwrk->ras_attr,pwrk->lobuf->glyf_seq[i],i);
	//			dn = need_Move_Down_Pixs(pwrk, pwrk->lobuf->glyf_seq[i]);
	//			hd = maxht - ht;	// height diff after enlarging fonts.
				if(ht)
					pwrk->lobuf->caret_seq[i].oripos.y = *bmph - oy - ht;
				
			}
		}
	}
	pwrk->linemoveYup = moveYup;
	pwrk->linemoveYdn = moveYdn;
}

DT_void ReAdjustPosX(pLayWrk pwrk/*, DT32_int *bmpw*/)
{
	// iter all the glyphs, get the max negative moveY
	//DT32_int i, ht, dn, oy, moveYup, moveYdn;
	DT32_int i, mvLf;
	//pDT_FontMgr_wrk	pmgrwrk=((DT_Font*)(pwrk->cur_DT_Font))->fontmgr;

	mvLf = (pwrk->linemoveXlf < 0) ? DTAbs(pwrk->linemoveXlf) : 0;
	if(mvLf){
		if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
			// nothing to do.
		}else{
			for(i=0; i<pwrk->lobuf->glyf_cnt; i++)
			{
				pwrk->lobuf->caret_seq[i].oripos.x += mvLf;
				pwrk->lobuf->caret_seq[i].caretpos.x += mvLf;
			}
		}
	}
}

#define getbboxRight(font_lrsb, xsize, aw, ratio)	((aw) - ((font_lrsb)->nsRsb * DCW_SCALED_SIZEXY(xsize,ratio)/1000))
//DT32_int getbboxRight(Font_LRSB *font_lrsb, DT32_int xsize, DT32_int aw, DT32_int ratio)
//{
//	DT32_int rsb;
//	DT32_int bboxRight;
//	rsb  = font_lrsb->nsRsb * DCW_SCALED_SIZEXY(xsize,ratio)/1000;
//	bboxRight= aw - rsb;
//	return bboxRight;
//}

#define getbboxLeft(font_lrsb, xsize, ratio)	((font_lrsb)->nsLsb * DCW_SCALED_SIZEXY(xsize,ratio)/1000)
//DT32_int getbboxLeft(Font_LRSB *font_lrsb, DT32_int xsize, /*DT32_int aw,*/ DT32_int ratio)
//{
//	DT32_int lsb;
//	DT32_int bboxLeft;
//	lsb = font_lrsb->nsLsb * DCW_SCALED_SIZEXY(xsize,ratio)/1000;
//	bboxLeft = lsb;	// assume all glyphs' advance start from 0 to aw.
//	return bboxLeft;
//}

DT32_int  AdjustEndPosX(pLayWrk pwrk, DT32_int bmpw1);
DT32_int  AdjustBeginPosX(pLayWrk pwrk);
//DT32_int  Adjustbmp1(pLayWrk pwrk, DT32_int bmpw1)
//{
//	DT32_int syll_org_x;
//	DT32_int idx_focus, idx_end = pwrk->cur_g2idx-1;
//	DT32_int fsize, aw, endposx = bmpw1;
//	DT16_ushort nowglyph;
//	Font_LRSB font_lrsb;
//	DT32_int ratio, bboxRight;
//
//	if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
//		fsize = gDT_FONT_EMSIZE;
//	else
//		fsize = pwrk->vert ? pwrk->ysize : pwrk->xsize;
//	
//	font_lrsb.nsLsb = font_lrsb.nsRsb = 0;
//	/*
//	adjust caret to display last character .
//	*/
//	idx_focus = idx_end;
//	if(idx_focus >= 0)
//	{
//		nowglyph = pwrk->gseq2[idx_focus];
//		//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_CHARATTR_RASSCALERATIO, &ratio);
//		ratio = getScaleRatio(pwrk, nowglyph, idx_focus);		// FIXME: if nowglyph is a DLO_CHARATTR_XYSCALERATIO, it won't be compensated.
//
//		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, nowglyph, idx_focus);
//		syll_org_x = pwrk->fnt_pos[idx_focus].leftup.x + pwrk->fnt_pos[idx_focus].offx;
//
//		if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb))
//		{
//			if(font_lrsb.nsRsb > 0)
//				return endposx;
//
//			bboxRight = getbboxRight(&font_lrsb, fsize, aw, ratio);
//		}else{
//			bboxRight = aw;
//		}
//		if(endposx < syll_org_x+bboxRight)
//			endposx = syll_org_x+bboxRight;
//
//		idx_focus = idx_end-1;
//		while(idx_focus >= 0)
//		{
//			nowglyph = pwrk->gseq2[idx_focus];
//			aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, nowglyph, idx_focus);
//			syll_org_x= pwrk->fnt_pos[idx_focus].leftup.x + pwrk->fnt_pos[idx_focus].offx;
//			//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_CHARATTR_RASSCALERATIO, &ratio);
//			ratio = getScaleRatio(pwrk, nowglyph, idx_focus);		// FIXME: if nowglyph is a DLO_CHARATTR_XYSCALERATIO, it won't be compensated.
//			if(IS_ARABIC_ZEROWIDTH(nowglyph) /*arabic*/ || 0==aw /*hindi*/)
//			{
//				if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb))
//				{
//					if(font_lrsb.nsRsb > 0)
//						return endposx;
//					bboxRight = getbboxRight(&font_lrsb, fsize, aw, ratio);
//				}else{
//					bboxRight = aw;
//				}
//				if(endposx < syll_org_x+bboxRight)
//					endposx = syll_org_x+bboxRight;
//
//			}
//			else{
//				/// for the case 0940 in the string: 0930 094d 0915 0940 000d 000a
//				if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb)){
//					if(font_lrsb.nsRsb > 0)
//						return endposx;
//					bboxRight = getbboxRight(&font_lrsb, fsize, aw, ratio);
//					if(endposx < syll_org_x+bboxRight)
//						endposx = syll_org_x+bboxRight;
//				}					
//				break;
//			}
//			idx_focus--;
//		}
//	}
//	return  endposx;
//}

#if (1==DT_OPENVG_ENABLED)
/* This function is used to adjust linewidth in OpenVG mode to be the same as bmpw in GRAYxxBMP mode*/
/* Please call this func when linewidth, linemoveXlf, linemoveXrt is decided.						*/
/* This func also related to spacing. Note that italic should be added at DT_GetTextRect()			*/
/* To essure the accuracy, please set gDT_FONT_EMSIZE=1000, the same with DCW_CALC_AW_AH()			*/
/* Bold issue should be checked!!!																	*/
DT32_int Calc_linewidth_pixel(pLayWrk pwrk, DT32_int oriw)
{
	DT32_int	lwp/*linewidth_pixel*/, aw, i, szx;
	DT16_ushort	nowglyph;
	DLO_LayBuf	*lobuf = pwrk->lobuf;

	lwp = 0;				// oriw isn't useful, set to 0 to re-calculate.
	if(pwrk->vert)
		szx = pwrk->ysize;
	else
		szx = pwrk->xsize;
	
	for(i=0; i<lobuf->glyf_cnt; i++){
		nowglyph = lobuf->glyf_seq[i];
		if(isNSM(pwrk, nowglyph, i)){
			continue;
		}else{
			aw = pwrk->fengfuncs.getAwidth_pix(pwrk->ras_attr, nowglyph, i);	// considering to get from g2info directly! (conv empty font to 0)
			lwp += aw;
		}
	}
	
	if(pwrk->linemoveXrt > 0)
		lwp += DLO_ADJUST_W_H(pwrk->linemoveXrt, szx);
	if(pwrk->linemoveXlf < 0)
		lwp += DLO_ADJUST_W_H(DTAbs(pwrk->linemoveXlf), szx);
	// italic will be added later.
	if(pwrk->spacing < 0)
		lwp += DTAbs(pwrk->spacing);		// pwrk->spacing are in pixels orginally.

	return lwp;
}

DT32_int Calc_lineheight_pixel(pLayWrk pwrk, DT32_int orih)
{
	DT32_int lhp/*lineheight_pixel*/, szy;

	if(pwrk->vert)
		szy = pwrk->xsize;
	else
		szy = pwrk->ysize;

	lhp = DLO_ADJUST_W_H(orih, szy);
	if(pwrk->linemoveYup < 0)
		lhp += DLO_ADJUST_W_H(DTAbs(pwrk->linemoveYup), szy);
	if(pwrk->linemoveYdn > 0)
		lhp += DLO_ADJUST_W_H(pwrk->linemoveYdn, szy);

	if(pwrk->linebufh_pixel>0 && pwrk->linebufh_pixel<lhp){
		lhp = pwrk->linebufh_pixel;					// lineheight_pixel is modified here!
	}

	return lhp;
}
#endif

DT_void ReAdjustWidthHeight(pLayWrk pwrk)
{
	DT_BOOL	isFDL = pwrk->fengtype!=DLO_ENG_BDFRASTER && pwrk->fengtype!=DLO_ENG_DIFRASTER_BIT && pwrk->fengtype!=DLO_ENG_DIFRASTER_BYTE;
	pwrk->linemoveXlf = 0;
	pwrk->linemoveXrt = 0;
	pwrk->linewidth_pixel = 0;
	if(pwrk->linewidth>0){
		if(isFDL){
			DT32_int oriw, diff;
			oriw = pwrk->linewidth;

			/*calculation last character rsb.*/
			pwrk->linewidth = AdjustEndPosX(pwrk,pwrk->linewidth);
			pwrk->linemoveXrt = pwrk->linewidth - oriw;
			
			// Considering italic font. OVG doesn't support italic here, always 0!
			pwrk->linewidth += pwrk->fengfuncs.getAexten(pwrk->ras_attr, pwrk->lobuf->glyf_seq[pwrk->lobuf->glyf_cnt-1]);

			// the difference of the last(rightest) glyph, will compensate later if DCWRULE & R2L
			// 2012-04-16: diff moved here to be related by italic only, because ReAdjustPosX() will cover others, ex: w_edge, spacing, lsb, rsb...
			diff = pwrk->linewidth - oriw;

			// Compensate the last minus spacing.
			if(pwrk->spacing<0){	/* Jacky_20100824 */
				if(pwrk->fengtype == DLO_ENG_DCWOPENVG){
					if(pwrk->vert)
						pwrk->linewidth += DLO_OUL_ROOF_SCALED_PIX2EM(DTAbs(pwrk->spacing),pwrk->ysize);
					else
						pwrk->linewidth += DLO_OUL_ROOF_SCALED_PIX2EM(DTAbs(pwrk->spacing),pwrk->xsize);
				}else{
					pwrk->linewidth += (-pwrk->spacing);
				}
			}

			/*calculation first character lsb.*/
			pwrk->linemoveXlf = AdjustBeginPosX(pwrk);
			if(pwrk->linemoveXlf < 0){
				pwrk->linewidth += DTAbs(pwrk->linemoveXlf);
			}

			// for DCWRULE & R2L, it needs to adjust the right side differences.
			if(pwrk->bidirule==DLO_BIDI_DCWRULE && pwrk->lobuf->writedir==DLO_RIGHTTOLEFT && diff!=0){
				DT32_int i;
				// shift the oripos and caretpos by the difference of bmpw and bmp1.
				for(i=0; i<pwrk->lobuf->glyf_cnt; i++){
					pwrk->lobuf->caret_seq[i].caretpos.x += diff;
					pwrk->lobuf->caret_seq[i].oripos.x += diff;
				}
			}

			// for the leading glyph has minus lsb, re-adjust the oripos of all glyphs.
			if(pwrk->linemoveXlf < 0 )
				ReAdjustPosX(pwrk);

		#if (1==DT_OPENVG_ENABLED)
			// calc linewidth_pixel
			if(pwrk->fengtype == DLO_ENG_DCWOPENVG){
				if(gDT_EachGlyphWidth_on_Pixels){
					DT32_int i;
					DT_VGtype sRatio;
					DLO_CodePositioning	*pc;
					pwrk->linewidth_pixel = Calc_linewidth_pixel(pwrk, oriw);
					
					// 2012-05-24: offset each glyph's origin to fill out the width of the rect.
					sRatio = (DT_VGtype)pwrk->linewidth*pwrk->xsize/gDT_FONT_EMSIZE;
					pc = pwrk->lobuf->caret_seq;
					for(i=0; i<pwrk->lobuf->glyf_cnt; i++, pc++){
						pc->caretpos.x = (DT32_int)(pc->caretpos.x * pwrk->linewidth_pixel / sRatio);
						pc->oripos.x = (DT32_int)(pc->oripos.x * pwrk->linewidth_pixel / sRatio);
					}
				}
			}
		#endif
			
		}else{
			// bdf, dif supports spacing only, no lrsb, no italic.
			if(pwrk->spacing<0){
				pwrk->linewidth += (-pwrk->spacing);
			}
// 			pwrk->linewidth_pixel = pwrk->linewidth;
		}
	}

	pwrk->linemoveYup = 0;
	pwrk->linemoveYdn = 0;
	pwrk->lineheight_pixel = 0;
	pwrk->linebufh = 0;
	pwrk->linebufh_pixel = 0;
//	if(pwrk->lineheight>0 && (DT_FORCE_SCALE_RATIO!=0 || DT_MoveArabicY!=0 || DT_MoveThaiY!=0)){
	if( pwrk->lineheight>0 && pwrk->linewidth>0)
	{
		if(isFDL){
			DT32_int orih;
			orih = pwrk->lineheight;
			ReAdjustPosY(pwrk,&pwrk->lineheight);		// lineheight might be modified inside this func.

		#if (1==DT_OPENVG_ENABLED)
			// calc lineheight_pixel
			if(pwrk->fengtype == DLO_ENG_DCWOPENVG){
				if(gDT_EachGlyphWidth_on_Pixels)
					pwrk->lineheight_pixel = Calc_lineheight_pixel(pwrk, orih);
			}
		#endif
		}
//		else{
//			pwrk->lineheight_pixel = pwrk->lineheight;
//		}
	}

	if(pwrk->vert){
		DT32_int j;
		DLO_CodePositioning *p = pwrk->lobuf->caret_seq;
		for(j=0;j<pwrk->lobuf->glyf_cnt;j++,p++){
			swapXY(&p->caretpos.x, &p->caretpos.y);
			swapXY(&p->oripos.x, &p->oripos.y);
			swapXY(&p->awvec.vx, &p->awvec.vy);
			swapXY(&p->adjvec.vx, &p->adjvec.vy);
			// dmrect should be dealed inside each GetSegInfo_xxx().
		}
	}

	if( pwrk->fengtype!=DLO_ENG_DCWOPENVG){
		pwrk->lobuf->bitcount = (pwrk->mode==DLO_LAYOUT_BIT)?1:8;
		pwrk->lobuf->bmpwidth = (pwrk->vert) ? pwrk->lineheight : pwrk->linewidth;	//pwrk->linewidth
		pwrk->lobuf->bmpheight= (pwrk->vert) ? pwrk->linewidth : pwrk->lineheight;	//pwrk->lineheight;
		pwrk->lobuf->xbytes	  = Calxbytes(pwrk,pwrk->lobuf->bmpwidth);
		pwrk->lobuf->bufsize  = pwrk->lobuf->xbytes * pwrk->lobuf->bmpheight;
	}else{
		pwrk->lobuf->eswidth  = (pwrk->vert) ? pwrk->lineheight : pwrk->linewidth;	//pwrk->linewidth;
		pwrk->lobuf->esheight = (pwrk->vert) ? pwrk->linewidth : pwrk->lineheight;	//pwrk->lineheight;
	#if (1==DT_OPENVG_ENABLED)
		if(gDT_EachGlyphWidth_on_Pixels){			// overwrite the value!
			pwrk->lobuf->bmpwidth  = (pwrk->vert) ? pwrk->lineheight_pixel : pwrk->linewidth_pixel;
			pwrk->lobuf->bmpheight = (pwrk->vert) ? pwrk->linewidth_pixel : pwrk->lineheight_pixel;
		}
	#endif
	}
}

/* Fill the DLO_LayBuf in working memory for temporary use. */
DT32_int Fillwkbuf(pLayWrk pwrk)
{
	//DT32_int nRet;
	DT32_int i, j, bmpw=0, bmph=0, bmpw1=0, bmph1=0;	/* Jacky_20100209 */
	DLO_Point		pos;
	Str_Seg			*ss;
//	DLO_CodePositioning *p;

DBG_MSG_SHOW_FUNC_NAME();

	pwrk->lobuf->glyf_cnt = pwrk->cur_g2idx;
	pwrk->curidxglyf_seq = 0;

	/* Complete the lobuf for return. */
	pwrk->lobuf->writedir  = pwrk->writedir;
	for(i=0;i<pwrk->seg_cnt;i++){
	  bmpw1 += pwrk->segarr[i].sw;
	  bmph1 = pwrk->segarr[i].sh;
	  if(bmph1 > bmph){
		  bmph = bmph1;
	  }
	}
//	if(bmpw1>0){
//		//bmpw1 = Adjustbmp1(pwrk, bmpw1);				// 2011-12-22: doing this by AdjustEndPosX() later (after lobuf finished)!
//		bmpw = pwrk->fengfuncs.getAexten(pwrk->ras_attr, pwrk->gseq2[pwrk->cur_g2idx-1])+bmpw1;
//		if(pwrk->spacing<0){	/* Jacky_20100824 */	// 2011-12-22: do this later
//			bmpw += (-pwrk->spacing);
//		}
//	}else{
//		bmpw = bmpw1;
//	}

	pos.x=0;	pos.y=0;	
	  for(j=0;j<pwrk->seg_cnt;j++){
		ss = &pwrk->segarr[j];
		if(0==j){
		  if(pwrk->lobuf->writedir == DLO_RIGHTTOLEFT){
			  pos.x = bmpw1;	pos.y = 0; 
//			  if(pwrk->spacing<0)
//				  pos.x = bmpw + pwrk->spacing;		//Jacky_20110107_NegativeSpacing when RTL
		  }
		  else if(pwrk->lobuf->writedir == DLO_LEFTTORIGHT){ pos.x = 0;	pos.y = 0; }
		  else{ pos.x = 0;	pos.y = 0; }					/* Jacky_20100209 */
		}else{
		  if(pwrk->lobuf->writedir == DLO_RIGHTTOLEFT){ pos.x -= pwrk->segarr[j-1].sw;	pos.y = 0; }
		  else if(pwrk->lobuf->writedir == DLO_LEFTTORIGHT){ pos.x += pwrk->segarr[j-1].sw;	pos.y = 0; }
		  else{ pos.x += pwrk->segarr[j-1].sw;	pos.y = 0; }/* Jacky_20100209 */
		}
		ss->cpstart = pos;
		/*nRet = */FunctionByLang(pwrk,ss->script,ss->lang,FUNC_GETSEGINFO,ss);	//Jacky_20101213
		//pwrk->segarr[j] = ss;
	  }
#if (1)
	  pwrk->linewidth = bmpw = bmpw1;
	  pwrk->lineheight= bmph;
	  ReAdjustWidthHeight(pwrk);
#else
//	bmpw = bmpw1;
//	pwrk->linemoveXlf = 0;
//	/*pwrk->linemoveXrt = 0;*/
//	if(bmpw1 > 0){
//		DT32_int diff, aext = pwrk->fengfuncs.getAexten(pwrk->ras_attr, pwrk->lobuf->glyf_seq[pwrk->lobuf->glyf_cnt-1]);
//		bmpw1 = AdjustEndPosX(pwrk, bmpw);
//		if(bmpw1 != bmpw){
//			if(pwrk->spacing<0){	/* Jacky_20100824 */
//				bmpw1 += (-pwrk->spacing);
//			}
//			bmpw1 += aext;
//			diff = bmpw1 - bmpw;
//			bmpw = bmpw1;
//		}else{
//			if(pwrk->spacing<0){
//				bmpw += (-pwrk->spacing);
//			}
//			bmpw += aext;
//			diff = aext;			// 2012-02-16: might be an error!? It should be diff = bmpw - bmpw1;!?
//		}
//		if(pwrk->lobuf->writedir == DLO_RIGHTTOLEFT && diff != 0){
//			// shift the oripos and caretpos by the difference of bmpw and bmp1.
//			for(i=0; i<pwrk->lobuf->glyf_cnt; i++){
//				pwrk->lobuf->caret_seq[i].caretpos.x += diff;
//				pwrk->lobuf->caret_seq[i].oripos.x += diff;
//			}
//		}
//		pwrk->linemoveXlf = AdjustBeginPosX(pwrk);
//		if(pwrk->linemoveXlf < 0)
//			bmpw += DTAbs(pwrk->linemoveXlf);
//	}
//
//
//	pwrk->linemoveYup = 0;
//	pwrk->linemoveYdn = 0;
//	//if(bmph>0 && && (DT_FORCE_SCALE_RATIO!=0 || DT_MoveArabicY!=0 || DT_MoveThaiY!=0)){
//	if( bmph>0 && bmpw>0 
//		&& pwrk->fengtype!=DLO_ENG_BDFRASTER && pwrk->fengtype!=DLO_ENG_DIFRASTER_BIT && pwrk->fengtype!=DLO_ENG_DIFRASTER_BYTE)
//	{
//		ReAdjustPosY(pwrk,&bmph);		// bmp might be modified inside this func.
//		if(pwrk->linemoveXlf < 0)
//			ReAdjustPosX(pwrk);
//	}
//	
//	  if(pwrk->vert){
//		  p = pwrk->lobuf->caret_seq;
//		  for(j=0;j<pwrk->lobuf->glyf_cnt;j++,p++){
//			swapXY(&p->caretpos.x, &p->caretpos.y);
//			swapXY(&p->oripos.x, &p->oripos.y);
//			swapXY(&p->awvec.vx, &p->awvec.vy);
//			swapXY(&p->adjvec.vx, &p->adjvec.vy);
//			// dmrect should be dealed inside each GetSegInfo_xxx().
//		  }
//	  }
//
//	if( pwrk->fengtype!=DLO_ENG_DCWOPENVG){
//		pwrk->lobuf->bitcount = (pwrk->mode==DLO_LAYOUT_BIT)?1:8;
//		pwrk->lobuf->bmpwidth = (pwrk->vert) ? bmph : bmpw;	//bmpw;
//		pwrk->lobuf->bmpheight= (pwrk->vert) ? bmpw : bmph;	//bmph;
//		pwrk->lobuf->xbytes	  = Calxbytes(pwrk,pwrk->lobuf->bmpwidth);
//		pwrk->lobuf->bufsize  = pwrk->lobuf->xbytes * pwrk->lobuf->bmpheight;
//	}else{
//		//pwrk->lobuf->eswidth  = (pwrk->vert) ? bmph : bmpw1;	//bmpw1;
//		//pwrk->lobuf->esheight = (pwrk->vert) ? bmpw1 : bmph;	//bmph;
//		pwrk->lobuf->eswidth  = (pwrk->vert) ? bmph : bmpw;
//		pwrk->lobuf->esheight = (pwrk->vert) ? bmpw : bmph;
//	}
#endif

	return DLO_SUCCESS;
}

DT32_int Fill_lobuf1(pLayWrk pwrk)
{
	DT16_ushort i;

	pwrk->lobuf->glyf_cnt = pwrk->cur_g2idx;
	pwrk->curidxglyf_seq = 0;
	pwrk->lobuf->writedir  = pwrk->writedir;
	
	for(i=0;i<pwrk->cur_g2idx;i++)
	{
		pwrk->lobuf->glyf_seq[i] = pwrk->gseq2[i];
		pwrk->lobuf->caret_seq[i].glyfidx = i;
	}

	return i;
}

DT_BOOL isZeroWidth(DT16_ushort nowglyph)
{
	if(NSM==bidi_getBidiClass(nowglyph))
		return DT_TRUE;
	if(IS_ARABIC_ZEROWIDTH(nowglyph))
		return DT_TRUE;

	return DT_FALSE;
}

// return the most right posX (= the new bmp width).
DT32_int  AdjustEndPosX(pLayWrk pwrk, DT32_int bmpw1)
{
	DT32_int idx_focus, idx_end = pwrk->lobuf->glyf_cnt-1;
	DT32_int fsize, aw, endposx = bmpw1;		//pwrk->linewidth;
	DT16_ushort nowglyph;
	Font_LRSB font_lrsb;
	DT32_int ratio,bboxRight;
	DT_BOOL	bZeroW;				//DT_Bidi_Class cls;
	
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
		fsize = gDT_FONT_EMSIZE;
	else
		fsize = pwrk->vert ? pwrk->ysize : pwrk->xsize;
	
	font_lrsb.nsLsb = font_lrsb.nsRsb = 0;
	/*
	adjust caret to display last character .
	*/
	idx_focus = idx_end;
	if(idx_focus >= 0)
	{
		nowglyph = pwrk->lobuf->glyf_seq[idx_focus];
		bZeroW = isZeroWidth(nowglyph);
		//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, DLO_CHARATTR_RASSCALERATIO, &ratio);
		ratio = getScaleRatio(pwrk, nowglyph, idx_focus);		// FIXME: if nowglyph is a DLO_CHARATTR_XYSCALERATIO, it won't be compensated.

		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, nowglyph, idx_focus);
		if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb))
		{	
			if(font_lrsb.nsRsb > 0 && aw != 0 && !bZeroW)
				return endposx;
			bboxRight = getbboxRight(&font_lrsb, fsize, aw, ratio);
		}else{
			bboxRight = aw;
		}
		if(endposx < pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxRight)
			endposx = pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxRight;

		// check if there is an mark(zero width or non-zero width) which width > linewidth 
		idx_focus = idx_end-1;
		while(idx_focus >= 0)
		{
			nowglyph = pwrk->lobuf->glyf_seq[idx_focus];
			//cls = bidi_getBidiClass(nowglyph);
			bZeroW = isZeroWidth(nowglyph);
			aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, nowglyph, idx_focus);
			//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_CHARATTR_RASSCALERATIO, &ratio);
			ratio = getScaleRatio(pwrk, nowglyph, idx_focus);		// FIXME: if nowglyph is a DLO_CHARATTR_XYSCALERATIO, it won't be compensated.
			if(/*NSM == cls*/ bZeroW /*for arabic*/ || 0==aw /*for hindi*/)
			{
				if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb))
				{
					//if(font_lrsb.nsRsb > 0)		// 2011-12-20: Jacky marked it for 0x0915, 0x0902 out of rect.
					//	return endposx;
					bboxRight = getbboxRight(&font_lrsb, fsize, aw, ratio);
				}else{
					bboxRight = aw;
				}
				if(endposx < pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxRight)
					endposx = pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxRight;
			}
			else{
				if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb))
				{
					if(font_lrsb.nsRsb > 0)
						return endposx;
					bboxRight = getbboxRight(&font_lrsb, fsize, aw, ratio);
					if(endposx < pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxRight)
						endposx = pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxRight;
				}
				break;
			}
			idx_focus--;
		}
		//pwrk->linewidth = endposx;
	}
	return endposx;
}

DT32_int  AdjustBeginPosX(pLayWrk pwrk)
{
	DT32_int idx_focus, idx_end = pwrk->lobuf->glyf_cnt-1, basecnt = 0;
	DT32_int fsize, aw, beginposx = 0;
	DT16_ushort nowglyph;
	Font_LRSB font_lrsb;
	DT32_int ratio,bboxLeft;
	DT_BOOL	bZeroW;				//DT_Bidi_Class cls;
	
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
		fsize = gDT_FONT_EMSIZE;
	else
		fsize = pwrk->vert ? pwrk->ysize : pwrk->xsize;
	
	font_lrsb.nsLsb = font_lrsb.nsRsb = 0;
	/*
	adjust caret to display last character .
	*/
	idx_focus = 0;
	if(idx_focus <= idx_end)
	{
		nowglyph = pwrk->lobuf->glyf_seq[idx_focus];
		bZeroW = isZeroWidth(nowglyph);
		//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, DLO_CHARATTR_RASSCALERATIO, &ratio);
		ratio = getScaleRatio(pwrk, nowglyph, idx_focus);		// FIXME: if nowglyph is a DLO_CHARATTR_XYSCALERATIO, it won't be compensated.

		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, nowglyph, idx_focus);
		if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb))
		{	
			//if(font_lrsb.nsLsb > 0 && aw != 0 && !bZeroW && basecnt > 0)	// nerver return here, because NSM hasn't checked.
			//	return beginposx;
			bboxLeft = getbboxLeft(&font_lrsb, fsize, /*aw,*/ ratio);
		}else{
			bboxLeft = 0;
		}
		if(pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxLeft < beginposx)
			beginposx = pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxLeft;

		if(aw != 0 && !bZeroW)
			basecnt++;
		// check if there is an mark(zero width or non-zero width) which width > linewidth 
		idx_focus++;
		while(idx_focus <= idx_end)
		{
			nowglyph = pwrk->lobuf->glyf_seq[idx_focus];
			bZeroW = isZeroWidth(nowglyph);
			aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, nowglyph, idx_focus);
			//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_CHARATTR_RASSCALERATIO, &ratio);
			ratio = getScaleRatio(pwrk, nowglyph, idx_focus);		// FIXME: if nowglyph is a DLO_CHARATTR_XYSCALERATIO, it won't be compensated.
			if(/*NSM == cls*/ bZeroW /*for arabic*/ || 0==aw /*for hindi*/)
			{
				if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb))
				{
					//if(font_lrsb.nsRsb > 0)
					//	return ;
					bboxLeft = getbboxLeft(&font_lrsb, fsize, /*aw,*/ ratio);
				}else{
					bboxLeft = 0;
				}
				if(pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxLeft < beginposx)
					beginposx = pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxLeft;

			}
			else{
				if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, idx_focus, DLO_LANGTAB_RSB, &font_lrsb))
				{
					if(font_lrsb.nsLsb > 0 && basecnt > 0)
						return beginposx;
					bboxLeft = getbboxLeft(&font_lrsb, fsize, /*aw,*/ ratio);
					if(pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxLeft < beginposx)
						beginposx = pwrk->lobuf->caret_seq[idx_focus].oripos.x+bboxLeft;
				}
				if(basecnt > 0)
					break;
				basecnt++;
			}
			idx_focus++;
		}
	}
	return beginposx;
}

/* for UNIRULE only: This step will fill the lobuf*/
DT32_int Fill_lobuf2(pLayWrk pwrk)
{
	DT32_int	/*ret,*/ size, rtv;
	DL_CodeAttr	castart, caend;
	DLO_Script	scend;
	DLO_Language laend;
//	DLO_CodePositioning *p;

	pwrk->maxdifH = 0;	 pwrk->bScaled = DT_FALSE;
	pwrk->seg_start = 0; pwrk->seg_end	=0; size = 0; pwrk->seg_cnt = 0; pwrk->segw = 0; pwrk->segh = 0;
	pwrk->cur_g1idx = 0; pwrk->cur_g2idx=0; 
	pwrk->seg_script= DLO_SCRIPT_DFLT; pwrk->seg_lang = DLO_LANG_DFLT;
	pwrk->linewidth = 0; pwrk->lineheight = 0;
	while(pwrk->seg_start < pwrk->lobuf->glyf_cnt)
	{
		//devide segments according to its script
		castart = DL_GetCodeCategory(pwrk,pwrk->lobuf->glyf_seq[pwrk->seg_start]);
		DL_GetScriptLang(castart.range,&pwrk->seg_script,&pwrk->seg_lang);
		//pwrk->seg_dir = GetSegDirectByScript(pwrk->seg_script);
		pwrk->seg_end = pwrk->seg_start+1;
		while(pwrk->seg_end < pwrk->lobuf->glyf_cnt)
		{
			caend = DL_GetCodeCategory(pwrk,pwrk->lobuf->glyf_seq[pwrk->seg_end]);
			DL_GetScriptLang(caend.range,&scend,&laend);
			if( scend==pwrk->seg_script
				|| (caend.range==DL_Range_Special && (caend.cate==DL_ZeroWidth_Format || caend.cate==DL_Symbol_Other))	// for 0x200B, 0x200C, 0x200D or0x25CC
			)
			{
				pwrk->seg_end++;
			}else
			{
				break;
			}
		}

		size = pwrk->seg_end - pwrk->seg_start;
		if(size<=0)	
			break;
		
		/* Get the DLO_Data_Table in dlo file data by script and lang. */
		rtv = DFS_GetdlotabHeader(pwrk, pwrk->seg_script, pwrk->seg_lang, &pwrk->cur_dlotab_idx);
		if(rtv == DLO_TAB_NOT_EXIST)
		{ 
			pwrk->dlo_tab_exist = 0; 
			//ret |= DLO_TABLE_NOT_FOUND;		// 2012-02-17: don't return 
		}
		else 
			pwrk->dlo_tab_exist = 1;

		/* Every segment is dispatched to its language processor. */
		FunctionByLang( pwrk, pwrk->seg_script, pwrk->seg_lang, FUNC_CALCPOSITION, 0);	

		pwrk->seg_start += size; size=0; pwrk->segw=0; pwrk->segh = 0;			
	}

	// Re-Adjust Bmp width & height
	ReAdjustWidthHeight(pwrk);
	
	return DLO_SUCCESS;
}


// /* Now supports only the situation of multi-codes=1glyph.	*/
// /* You have to implement N-codes=N-glyphs if you need.		*/
// /* This function will calculate the segment width (segw).	*/
//DT_void Fillawseg_R2L_OLD(pLayWrk pwrk)
//{
//	DT32_int i, aw=0, ht=0, segw=0, segh=0;
//	DT16_ushort ch, gidx=0;		/* Jacky_20100209 */
//	DLO_Point p;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	p.x = 0;	p.y = 0;
//	for(i=pwrk->seg_start;i<pwrk->seg_end;i++)
//	{
//		ch = pwrk->gseq[i].glyf2;
//		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,ch);
//		ht = pwrk->fengfuncs.getAheight(pwrk->ras_attr,ch);
//		pwrk->awseq[i].codeidx	= i;
//		pwrk->awseq[i].glyfidx	= pwrk->gseq[i].idx_gseq2;
//		pwrk->awseq[i].aw.vx	= aw;
//		pwrk->awseq[i].aw.vy	= 0;
//		pwrk->awseq[i].direct	= DLO_RIGHTTOLEFT;
//		p.x = segw;		p.y = 0;
//		pwrk->awseq[i].leftup = p;
//
//		/* Only multi-codes=1glyph supported, so use gidx to distinguish this situation. */
//		if(i==pwrk->seg_start) gidx = pwrk->awseq[i].glyfidx;
//		else if(pwrk->awseq[i].glyfidx == gidx) continue;
//		else gidx = pwrk->awseq[i].glyfidx;
//
//		segw += aw;
//		if(ht > segh){
//			segh = ht;
//		}
//	}
//
//	pwrk->segw = segw;
//	pwrk->segh = segh;
//}

/* Now supports only the situation of multi-codes=1glyph.	*/
/* You have to implement N-codes=N-glyphs if you need.		*/
/* This function will calculate the segment width (segw).	*/
DT_void Fillawseg_R2L(pLayWrk pwrk)
{
	DT32_int i, j, aw=0, ht=0, ht1=0, segw=0, segh=0;
	DT16_ushort g2, gidx, g=0, c=0;		/* Jacky_20100209 */
	DLO_Point p;

DBG_MSG_SHOW_FUNC_NAME();

	p.x = 0;	p.y = 0;
	i=pwrk->seg_start;
	//for(i=pwrk->seg_start;i<pwrk->seg_end;i++)
	while(i<pwrk->seg_end)
	{
		Parse_n_per_glyf(pwrk->gseq[i].n_per_glyf2,&c,&g);
		aw = 0;
		ht = 0;
		if(pwrk->gseq[i].n_per_glyf2!=0){	// N-codes=N-glyphs
			gidx = pwrk->gseq[i].idx_gseq2;
			for(j=0; j<g; j++){
				g2 =  pwrk->gseq2[gidx+j];
				if(!IS_ARABIC_ZEROWIDTH(g2)){
					aw += pwrk->fengfuncs.getAwidth(pwrk->ras_attr,g2,gidx+j);
				}else{
					if(1==pwrk->seg_end-pwrk->seg_start || (0==segw && 0==aw)){
						aw += pwrk->fengfuncs.getAwidth(pwrk->ras_attr,g2,gidx+j);	//Special case: the seg contains only 1 point
					}
				}
				ht1 = pwrk->fengfuncs.getAheight(pwrk->ras_attr,g2,gidx+j);
				if(ht1>ht){
					ht = ht1;
				}
			}

			for(j=0;j<c;j++){
				pwrk->awseq[i].codeidx	= i;
				pwrk->awseq[i].glyfidx	= gidx;
				pwrk->awseq[i].aw.vx	= aw;
				pwrk->awseq[i].aw.vy	= 0;
//				pwrk->awseq[i].direct	= DLO_RIGHTTOLEFT;
				p.x = segw;		p.y = 0;
				pwrk->awseq[i].leftup = p;
				i++;
			}
		}
		segw += aw;
		if(ht > segh){
			segh = ht;
		}
	}

	pwrk->segw = segw;
	pwrk->segh = segh;
}

DT_void Fillsegarr_R2L(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();

	pwrk->segarr[pwrk->seg_cnt].ustart	= pwrk->seg_start;
	pwrk->segarr[pwrk->seg_cnt].uend	= pwrk->seg_end;
	pwrk->segarr[pwrk->seg_cnt].script	= pwrk->seg_script;
	pwrk->segarr[pwrk->seg_cnt].lang	= pwrk->seg_lang;
	pwrk->segarr[pwrk->seg_cnt].sw		= pwrk->segw;
	pwrk->segarr[pwrk->seg_cnt].sh		= pwrk->segh;
}

// /* Now supports only the situation of multi-codes=1glyph.	*/
// /* You have to implement N-codes=N-glyphs if you need.		*/
// /* Reversed glyphs.											*/
//DT32_int GetSeginfo_R2L_OLD(pLayWrk pwrk, Str_Seg *seginfo)
//{
//	DT32_int i, j, st, en, g2st, g2en, gcnt, aw, caret;
//	DT16_ushort c, g, gidx=0;		/* Jacky_20100209 */
//	DLO_CodePositioning p;
//	DLO_RECT rect;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	//Jacky_20101025_for_Performance
////	DT_memset(&p,0,sizeof(DLO_CodePositioning));	/* To avoid warnings when compile with GCC */
//	//DT_memset(&rect, 0, sizeof(DLO_RECT));
//
//	st = seginfo->ustart;
//	en = seginfo->uend;
//
//	/* Re-sequences R2L glyf_seq (Reverse-ordered) */
//	g2st  = pwrk->gseq[st].idx_gseq2;
//	g2en  = pwrk->gseq[en-1].idx_gseq2;
//	gcnt  = g2en - g2st + 1;
//	
//	c=1; g=1; gidx = g2en; j = g2st;
//	for(i=st;i<en;i+=c,gidx--,j++){
//	  pwrk->lobuf->glyf_seq[j] = pwrk->gseq2[gidx];
//	  Parse_n_per_glyf(pwrk->gseq[i].n_per_glyf2,&c,&g);
//	  p.codeidx = i;
//	  p.glyfidx = j;
//	  p.n_per_glyf = Make_n_per_glyf(c,g);	// only multi-codes=1Glyph situation supported. Don't deal with g>1.
//	  pwrk->lobuf->caret_seq[gidx] = p;	/* Jacky_20100622 */
//	}
//
//	/* calculate the position information. */
//	if(pwrk->lobuf->writedir == DLO_LEFTTORIGHT)	caret = seginfo->cpstart.x;
//	else if(pwrk->lobuf->writedir == DLO_RIGHTTOLEFT)caret = seginfo->cpstart.x - seginfo->sw;
//	else caret = seginfo->cpstart.x;
//
//	rect.xy.x =rect.xy.y =0;
//	rect.hw.vx=rect.hw.vy=0;
//	for(j=g2st;j<g2st+gcnt;j++){
//	  aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,pwrk->lobuf->glyf_seq[j]);
//	  pwrk->lobuf->caret_seq[j].caretpos.x	= caret;
//	  pwrk->lobuf->caret_seq[j].caretpos.y	= 0;
//	  pwrk->lobuf->caret_seq[j].oripos.x	= caret;
//	  pwrk->lobuf->caret_seq[j].oripos.y	= 0 + need_Move_Down_Pixs(pwrk, pwrk->lobuf->glyf_seq[j]);	//0;
//	  pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
//	  pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
//	  pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
//	  pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
//	  pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
//	  pwrk->lobuf->caret_seq[j].dmrect	= rect;//rect
//	  caret += aw;
//	}
//
//	seginfo->cpend.x = caret;
//	seginfo->cpend.y = 0;
//
//	return DLO_SUCCESS;
//}

/* Now supports only the situation of multi-codes=1glyph.	*/
/* You have to implement N-codes=N-glyphs if you need.		*/
/* Reversed glyphs.											*/
DT32_int GetSeginfo_R2L(pLayWrk pwrk, Str_Seg *seginfo)
{
	DT32_int i, j, k, st, en, g2st, g2en, gcnt, aw, caret, lastpoint_aw=0;
	DT16_ushort c, g, gidx=0;		/* Jacky_20100209 */
	DLO_CodePositioning p;
	DLO_RECT rect;
	pDT_FontMgr_wrk	pmgrwrk=((DT_Font*)(pwrk->cur_DT_Font))->fontmgr;
	FontCodeInfo *pfc;

DBG_MSG_SHOW_FUNC_NAME();

	//Jacky_20101025_for_Performance
	//DT_memset(&p,0,sizeof(DLO_CodePositioning));	/* To avoid warnings when compile with GCC */
	//DT_memset(&rect, 0, sizeof(DLO_RECT));

	st = seginfo->ustart;
	en = seginfo->uend;

	/* Re-sequences R2L glyf_seq (Reverse-ordered) */
	g2st  = pwrk->gseq[st].idx_gseq2;
	g2en  = pwrk->gseq[en-1].idx_gseq2;
	gcnt  = g2en - g2st + 1;
	
	if(gcnt*sizeof(FontCodeInfo) > (DT32_ulong)pmgrwrk->tmpbufsize){
		pfc = NULL;
	}else{
		pfc = (FontCodeInfo*) pmgrwrk->tempbuf;
	}

	c=1; g=1; i=st; j=g2en; gidx=g2st;
	while(i<en){
		if(pwrk->gseq[i].n_per_glyf2!=0){
			Parse_n_per_glyf(pwrk->gseq[i].n_per_glyf2,&c,&g);
			for(k=0; k<g; k++){
				pwrk->lobuf->glyf_seq[j] = pwrk->gseq2[gidx];
				p.codeidx = i;
				p.glyfidx = j;
				p.n_per_glyf = (k==g-1)?Make_n_per_glyf(c,g):0;
				pwrk->lobuf->caret_seq[j] = p;
				if(pfc)
					pfc[j-g2st] = pwrk->g2info[gidx];		// copy the element to the tempbuf.
				else
					pwrk->g2info[j].checkedFlag = 0;	// set the element in g2info to 0 directly.
				j--; gidx++;
			} 
			i += c;
		}
		
	}
	// reset g2info (copy from the tempbuf) due to the gseq2 is reordered.
	if(pfc)
		DT_memcpy(pwrk->g2info+g2st, pfc, gcnt*sizeof(FontCodeInfo));

	/* calculate the position information. */
	if(pwrk->lobuf->writedir == DLO_LEFTTORIGHT)	caret = seginfo->cpstart.x;
	else if(pwrk->lobuf->writedir == DLO_RIGHTTOLEFT)caret = seginfo->cpstart.x - seginfo->sw;
	else caret = seginfo->cpstart.x;

	rect.xy.x =rect.xy.y =0;
	rect.hw.vx=rect.hw.vy=0;
	for(j=g2st;j<g2st+gcnt;j++){
	  aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,pwrk->lobuf->glyf_seq[j],j);
	  pwrk->lobuf->caret_seq[j].caretpos.x	= caret;
	  pwrk->lobuf->caret_seq[j].caretpos.y	= 0;
	  pwrk->lobuf->caret_seq[j].oripos.x	= caret;
	  pwrk->lobuf->caret_seq[j].oripos.y	= 0 + need_Move_Down_Pixs(pwrk, pwrk->lobuf->glyf_seq[j],j);	//0;
	  pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
	  pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
	  pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
	  pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
	  pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
	  pwrk->lobuf->caret_seq[j].dmrect	= rect;//rect

	  if(!IS_ARABIC_ZEROWIDTH(pwrk->lobuf->glyf_seq[j])){
		caret += aw;
		if(pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr,pwrk->lobuf->glyf_seq[j],j))
		{
			lastpoint_aw = 0;
		}
	  }else
	  {
		  lastpoint_aw = aw;
	  }
	}

	seginfo->cpend.x = caret + lastpoint_aw;
	seginfo->cpend.y = 0;

	return DLO_SUCCESS;
}

/* Convert DL_Punctuation_Open to DL_Punctuation_Close and versas. Only gseq2 will be modified. */
/* Please call this function in the R2L script, like DLO_SCRIPT_arab, DLO_SCRIPT_hebr...etc.	*/
DT_void ConvPunctuation_Open2Close(pLayWrk pwrk, DT16_ushort seg_start, DT16_ushort seg_end)
{
	DT16_ushort i, glyph, glyph2;
	DL_CodeAttr at;
	for(i=seg_start;i<seg_end;i++){
		glyph = pwrk->gseq[i].glyf2;
		at = DL_GetCodeCategory(pwrk, glyph);
		if(at.cate==DL_Punctuation_Open || at.cate==DL_Punctuation_Close){
			glyph2 = DL_convOpen2Close(pwrk, glyph);
			pwrk->gseq[i].glyf2 = glyph2;
			pwrk->gseq2[pwrk->gseq[i].idx_gseq2] = glyph2;
		}
	}
}

/* Get the DLO_CHARATTR_RASSCALERATIO or DLO_CHARATTR_BINSCALERATIO scale ratio value for specific code, */
DT32_int getScaleRatio(pLayWrk pwrk, DT16_ushort gidx, DT32_int gseq2idx)
{
	DT32_int ratio = DCW_BASE_RATIO;
	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, gidx, gseq2idx, DLO_CHARATTR_RASSCALERATIO, &ratio);
	if(ratio==0 || ratio==DCW_BASE_RATIO){	// check another scale table.
		pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, gidx, gseq2idx, DLO_CHARATTR_BINSCALERATIO, &ratio);
	}
	return ratio;
}

extern DT32_int rasScaleMethod(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DT32_int *rto);
#ifdef DIGITYPE_OUL  /* Panasonic added this #ifdef */
extern DT32_int oulScaleMethod(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DT32_int *rto);
#endif

DT16_ushort dloScaleMethod(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx, DT16_ushort *rto)
{
	DT32_int method, ratio;
	ratio = DCW_BASE_RATIO;
	method= DLO_NOT_SCALE;

	if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
	{
#ifdef DIGITYPE_OUL  /* Panasonic added this #ifdef */
		method = oulScaleMethod(pwrk, ch, gseq2idx, &ratio);
#endif
	}else if(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO || pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 || pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256)
	{
		method = rasScaleMethod(pwrk, ch, gseq2idx, &ratio);
	}else	// if(pwrk->fengtype==DLO_ENG_BDFRASTER || pwrk->fengtype==DLO_ENG_DIFRASTER_BIT || pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE)
	{
		// do nothing. remain DLO_NOT_SCALE & DCW_BASE_RATIO.
	}

	if(rto)
		*rto = (DT16_ushort) ratio;

	return (DT16_ushort)method;
}

// set some default FontCodeInfo when code doesn't exist.
DT_void  setDefault_Scale_LRsb_MoveY(FontCodeInfo *pfc)
{
	// code don't exist, icon font won't scale and move, so set followings also.
	pfc->moveY = 0;
	pfc->logHeight = 0;
	pfc->logTop= 0;
	pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;

	pfc->scaleMethod = DLO_NOT_SCALE;
	pfc->scaleRatio  = DCW_BASE_RATIO;
	pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;

	pfc->lrsb.nsLsb  = pfc->lrsb.nsRsb = 0;
	pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_LRSB;
}

//DT32_int queryFontCodeInfo(pLayWrk pwrk, DT32_int gseq2idx)
//{
//	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;
//	DT32_int moveY;
//	DT16_ushort code;
//
//	if(!pfc)
//		return DT_SUCCESS;
//
//	if(NULL!=pwrk->fengfuncs.getFontCodeInfo){
//	}else{
//		code = pwrk->gseq2[gseq2idx];
//		pfc->checkedFlag = 0;
//		// calling these 2 funcs should finish the 4 CHECKFLAGs: EXIST, SCALE, AW, AH
//		pwrk->fengfuncs.getAwidth(pwrk->ras_attr, code, gseq2idx);
//		pwrk->fengfuncs.getAheight(pwrk->ras_attr, code, gseq2idx);
//
////		pfc->scaleMethod = dloScaleMethod(pwrk, pfc->code, gseq2idx, &pfc->scaleRatio);
////		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_SCALE;
////		pfc->aw = (DT16_short)pwrk->fengfuncs.getAwidth(pwrk->ras_attr, pfc->code, gseq2idx);
////		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AW;
////		pfc->ah = (DT16_short)pwrk->fengfuncs.getAheight(pwrk->ras_attr, pfc->code, gseq2idx);
////		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AH;
////		pfc->codeExist = (DT8_uchar)pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr, pfc->code, gseq2idx);	// also pfc->existFont
////		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
//		// moveY
//		moveY = 0;
//		pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, code, gseq2idx, DLO_CHARATTR_GET_OFFSETY, &moveY);
//		pfc->moveY = (DT16_short) moveY;
//		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;
//		// LRSB
//		pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, code, gseq2idx, DLO_CHARATTR_FONT_LRSB, &pfc->lrsb);
//		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_MOVEY;
//	}
//
//	return DT_SUCCESS;
//}
/* Because DigiTypeAPI can render two or more fonts in a line of text, some fonts height won't match others.*/
/* This function is used to calculate if the char should be move downer (offset) to match other fonts.		*/
/* Now, it will put all chars in the middle of bmph. bmpH is calculated in advanced to contain the text.	*/
/* fontH: fonts' height. If 0, means this function is called by DIF_Raster.									*/
/*  difH: icons' height. If 0, means this function is called by BDF_Raster or Digitype_std.					*/
/* One of fontH or difH should be 0, and bmpH won't be 0 always.											*/
DT32_int CalcOffsetY_forbmph(pLayWrk pwrk, DT32_int fontH, DT32_int difH, DT32_int bmpH)
{
	DT32_int fontmid, difmid, bmpmid = bmpH/2;

	if(bmpH <= 0){
		return 0;
	}

	if(fontH > 0){
	  if(fontH > bmpH){
		/* This should not happen. */
		return 0;
	  }else if(fontH < bmpH){
		fontmid = fontH/2;
		return bmpmid - fontmid;	//(bmpH - fontH + 1)/2;	/* move to the middle of the height. */
	  }else{
		return 0;
	  }
	}else if(difH > 0){
	  if(difH > bmpH){
		/* This should not happen. */
		return 0;
	  }else if(difH < bmpH){
		/* It must make sure dif matches exactly. */
		difmid = difH/2;
		return bmpmid - difmid;		//(bmpH - difH + 1)/2;	/* move to the middle of the height. */
	  }else{
		return 0;
	  }
	}
	return 0;
}

DT32_int need_Move_Down_Pixs(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx)
{
	DT32_int Ratio=0;
#ifdef DT_VERT_BY_OVG
	// do nothing
#else
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
		if(pwrk->vert){
			pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_OFFSETY, &Ratio);
			return DT_FORCE_MOVE_DOWN_PIXS(gDT_FONT_EMSIZE, Ratio);
		}
	}
#endif

//	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
//		pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_OFFSETY, &Ratio);
//		return DT_FORCE_MOVE_DOWN_PIXS(gDT_FONT_EMSIZE, Ratio);
//	}

	if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
		pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
		pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256 ){
		pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, ch, gseq2idx, DLO_CHARATTR_GET_OFFSETY,&Ratio);
	}

	if(pwrk->vert){
		return DT_FORCE_MOVE_DOWN_PIXS(pwrk->xsize, Ratio);
	}

	return DT_FORCE_MOVE_DOWN_PIXS(pwrk->ysize, Ratio);

//	DT32_int under=0, underpixs=0;
//	if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//		pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//		pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256 ){
//		under = is_LatinChars_Descent(pwrk, ch);
//	}else{
//		under = 0;
//	}
//	switch(under){
//	case 1:	/* some chars in some FDL needs to move down. */
//		underpixs	= DT_FORCE_MOVE_DOWN_PIXS(pwrk->ysize);
//		break;
//	case 2: /* some chars in some FDL needs to move down, and g,j,y... needs decent pixels */
//		underpixs	= DT_FORCE_MOVE_DOWN_PIXS(pwrk->ysize) + DT_DESCENT_PIXS(pwrk->ysize);
//		break;
//	case 0:
//	default:
//		underpixs	= 0;
//	}
//
//	return underpixs;
}

/* FDL is always little endian. */
//DT32_long leReadInt(DT8_char *fdl, DT32_long ofs, DT32_int size)
//{
//  DT8_uchar *p;
//  DT32_long val, b;
//  DT32_int scnt, i;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//  p = (DT8_uchar*)fdl + ofs;	/* Jacky_20090901 */
//  val = *p++;
//
//  for (i=1,scnt=8; i<size; i++,p++,scnt+=8)
//  {
//    b = *p << scnt;
//    val += b;
//  }
//
//  return val;
//}

/* If any one code exists, it returns 1, else it returns 0. */
DT_BOOL chkCodeRange(pLayWrk pwrk, DT16_ushort first, DT16_ushort last)
{
	DT16_ushort code;
	for(code=first; code<=last; code++){
		if(pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr, code, -1))
			return DT_TRUE;
	}
	return DT_FALSE;
}

/* check the key chars(not all chars) to see if they were contained in the font?				*/
/* Return: 1(DLO_LANG_LAT): Latin Only, shaper isn't required. others: need to go into shaper.	*/
DT32_int checkFontsLatinOnly(pLayWrk pwrk)
{
#define OFFTO_FDLLANGTAB	(58)
	DT_Font	 *curfont, *altfont = NULL;
	DT8_char *curfontdata, *altfontdata = NULL;

DBG_MSG_SHOW_FUNC_NAME();

	curfont = (DT_Font*)pwrk->cur_DT_Font;
	curfontdata = curfont->fontdata;
	if(pwrk->altfontcnt > 0){
		altfont = (DT_Font*)pwrk->alt_DT_Font;
		altfontdata = altfont->fontdata;
	}

	// any table inside? contains Thai-level, scale, moveY, gpos, or gsub table...
	if( pwrk->fengtype == DLO_ENG_DCWRASTER_MONO ||
		pwrk->fengtype == DLO_ENG_DCWRASTER_GRAY16 ||
		pwrk->fengtype == DLO_ENG_DCWRASTER_GRAY256 ||
		pwrk->fengtype == DLO_ENG_DCWOPENVG)
	{
		if( 0 != pwrk->fengfuncs.FDL_ReadInt(curfontdata, OFFTO_FDLLANGTAB, 4) )
			return (DT32_int)DLO_LANG_DFLT;
		if(altfontdata){
			if(0 != pwrk->fengfuncs.FDL_ReadInt(altfontdata, OFFTO_FDLLANGTAB, 4))
				return (DT32_int)DLO_LANG_DFLT;
		}
	}

	// Hindi, Hindi requires LANGTAB, so it should be returned during the previous process.
	if( chkCodeRange(pwrk, 0x0910, 0x0940) )
		return (DT32_int)DLO_LANG_HIN;
	// Thai
	if( chkCodeRange(pwrk, 0x0E01, 0x0E2F) )
		return (DT32_int)DLO_LANG_THA;
	// Vietnamese
	if( chkCodeRange(pwrk, 0x0300, 0x0303) )
		return (DT32_int)DLO_LANG_DFLT;		// return default instead.
	if( chkCodeRange(pwrk, 0x0309, 0x0309) )
		return (DT32_int)DLO_LANG_DFLT;		// return default instead.
	if( chkCodeRange(pwrk, 0x0323, 0x0323) )
		return (DT32_int)DLO_LANG_DFLT;		// return default instead.
	
	// Arabic
	if( chkCodeRange(pwrk, 0x0621, 0x064A) )
		return (DT32_int)DLO_LANG_ARA;

	// Hebrew
	if( chkCodeRange(pwrk, 0x05D0, 0x05EA) )
		return (DT32_int)DLO_LANG_IWR;
	
	// Bidi Control Code
	if(chkCodeRange(pwrk, chLS, chRLO) || chkCodeRange(pwrk, chLRM, chRLM))
		return (DT32_int)DLO_LANG_DFLT;		// return default instead.

	return (DT32_int)DLO_LANG_LAT;
}

DT32_int ReInitFont(pLayWrk pwrk)
{
	DT32_int ret, rtval;
	ret = DLO_SUCCESS;
	/* Font style has been changed, re-initFont() */
	if( pwrk->isReinitFont && 
		(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256) ){
		do{	
		  ret = pwrk->fengfuncs.initFont(pwrk->ras_attr,pwrk->fondata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
		  if(ret==DLO_NOT_ENOUGH_ENGINEWKMEM){
			rtval = ReAllocEngWorkMem(pwrk);
			if(DLO_SUCCESS!=rtval){
				return rtval;
			}else{
				pwrk->TotalWkmsize = pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;				
			}
		  }		
		}while(ret==DLO_NOT_ENOUGH_ENGINEWKMEM);
		if(ret != DLO_SUCCESS)
			return ret;
	}
	return ret;
}

#ifdef _SPEEDTEST
#include <time.h>
#define	USING_CLOCK_OR_GETTIMEOFDAY	0	/* 0: clock(), 1: gettimeofday()*/

/* For reporting Clock & Time*/
clock_t bc, ec, dc;
time_t btime, etime;
double tdiff, tdc;
DT32_int	nline=0;

#if(1==USING_CLOCK_OR_GETTIMEOFDAY)
struct timeval tv, tv2;
DT32_ulong start_utime, end_utime;
#endif

DT_void SpeedTestStart(DT8_char *str)
{
#if(0==USING_CLOCK_OR_GETTIMEOFDAY)
	//printf("%s Speed Testing.....\n\n", str);
	time(&btime);
	bc = clock();
#else //if(1==USING_CLOCK_OR_GETTIMEOFDAY)
	gettimeofday(&tv,NULL);
	start_utime = tv.tv_sec * 1000000 + tv.tv_usec;
#endif
}

DT_void SpeedTestEnd()
{
#if(0==USING_CLOCK_OR_GETTIMEOFDAY)
	ec = clock();
	time(&etime);
	tdiff = difftime(etime,btime);	
	dc = ec - bc;
	tdc = (double)dc/CLOCKS_PER_SEC;
	printf("%ld\t",dc);
#else //if(1==USING_CLOCK_OR_GETTIMEOFDAY)
	gettimeofday(&tv2,NULL);
	end_utime = tv2.tv_sec * 1000000 + tv2.tv_usec;
	dc = (double)end_utime-start_utime;
	printf("%ld\t",dc);
#endif
}
#endif

/*---------------------------------------------------------------------------*/
DT32_int DLO_InitShaper(DT8_char *laydata, DT_void *font, DLO_EngineType type, DT32_int fontsizehint, DLO_Handle *hShaper,
						DT_void *altfont, DT32_int altfontcnt, DT_void *iconfont, DT32_int iconfontcnt)
{
	pLayWrk pwrk=NULL;
	DT32_int rtval, estmsz=0, totalmem=0;
	DT32_int memstep=0x100*sizeof(DT32_long);	/* Now only BDF_Raster engine may need to reallocate engine memory here. */
	DT8_char *fontdata = ((DT_Font*)font)->fontdata;

DBG_MSG_SHOW_FUNC_NAME();

	/* Check the pointer of fdl file data. */
	if( !fontdata )	
		return DLO_BAD_FONTDATA;

	//*hShaper = NULL;
	pwrk = *hShaper;

	/* Allocate required DcwShaper working memory */
	rtval = AllocWorkMem(&pwrk);
	if(rtval<=0){
		return rtval;
	}else{
		totalmem = rtval;
	}

	/* Load font engine functions */
	pwrk->fengtype = type;
	rtval = LoadFontEngineFuncs(pwrk);
	if(rtval!=DLO_SUCCESS)	
		goto ReleaseWrkMem;

	/* Estimate required working memory for font engine. */
	pwrk->xsize = pwrk->ysize = fontsizehint;
	if(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO){
		pwrk->grade = DLO_GRAY_MONO;
		pwrk->mode	= DLO_LAYOUT_BIT;
	}else if(pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16){
		pwrk->grade = DLO_GRAY_16;
		pwrk->mode  = DLO_LAYOUT_BYTE;
	}else if(pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256){
		pwrk->grade = DLO_GRAY_256;
		pwrk->mode  = DLO_LAYOUT_BYTE;
	}else if(pwrk->fengtype==DLO_ENG_BDFRASTER){
		pwrk->mode  = DLO_LAYOUT_BIT;
	}else if(pwrk->fengtype==DLO_ENG_DIFRASTER_BIT){
		pwrk->mode  = DLO_LAYOUT_BIT;
	}else if(pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE){
		pwrk->mode  = DLO_LAYOUT_BYTE;
	}

	estmsz = EstimateFontEngineWkMem(type,fontsizehint,fontsizehint,pwrk->grade);
	if(estmsz<0){
		rtval = DLO_FONTENGINE_NOT_SUPPORT;
		goto ReleaseWrkMem;
	}

	/* Allocate the required font engine working memory, used for BDF_RASTER now  */
	do{
		rtval = AllocEngWorkMem(pwrk, estmsz);
		if(rtval!=DLO_SUCCESS){
			goto ReleaseWrkMem;
		}
	
		rtval = pwrk->fengfuncs.initFont(pwrk->ras_attr,fontdata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
		if(rtval==DLO_NOT_ENOUGH_ENGINEWKMEM){
			if(pwrk->engWkMem){
				DT_free(pwrk->engWkMem);
				pwrk->engWkMem = NULL;
				pwrk->engWkMemsz = 0;
				//pwrk->TotalWkmsize = totalmem;	//pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE;
			}
			estmsz += memstep;
		}
		
	}while(rtval==DLO_NOT_ENOUGH_ENGINEWKMEM);

	pwrk->fnt_userdata = NULL;
	if(rtval==DLO_SUCCESS){
		/* keep some info related to engine working memory */
		pwrk->TotalWkmsize = totalmem + pwrk->engWkMemsz;	//pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;
		pwrk->engGradMem   = NULL;
		pwrk->engGradMemsz = 0;
		pwrk->engGradMaxUsed = 0;
		pwrk->engGradSuggest = EstimateFontEngineGradMem(type,fontsizehint,fontsizehint,pwrk->grade);

		/* Pointer to laydata */
		//if( !laydata )	return DLO_BAD_LAYDATA;
		pwrk->dlowkm.laydata = laydata;
		pwrk->dlo = (DT8_uchar*)laydata;

		/* Pointer to fontdata */
		pwrk->cur_DT_Font = font;
		pwrk->fondata = fontdata;

		/* altfont & iconfont */
		pwrk->alt_DT_Font = altfont;
		pwrk->altfontcnt  = altfontcnt;
		pwrk->icon_DT_Font= iconfont;
		pwrk->iconfontcnt = iconfontcnt;
		LoadIconFontEngineFuncs(pwrk);
		if(pwrk->iconfontcnt>0 && iconfont){
			/* No need font engine working memory, and it should always init successfully.	*/
			pwrk->iconfuncs.initFont(pwrk->icon_attr,((DT_Font*)iconfont)->fontdata,0,NULL,pwrk);
		}

		
	  if(pwrk->dlo){
		/* Get and check the dlo file header. */
		rtval = DFS_GetdloHeader(pwrk);
		if(rtval==DLO_BAD_LAYDATA)	/* DLO_BAD_LAYDATA is acceptable for some languages. Let user decide is it valid. */
		  rtval = DLO_SUCCESS_BUT_BADLAYDATA;
	  }else{
		rtval = DLO_SUCCESS_BUT_BADLAYDATA;
	  }

	  pwrk->bUseArabicPUA = DT_FALSE;
	  if( pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr, DL_Arabic_Basic_Key, -1) &&
		  pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr, DL_Arabic_FormA_Key, -1) &&
		  pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr, DL_Arabic_FormB_Key, -1) &&
		  pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr, DL_Arabic_DcwPUA_Key, -1) )
	  {
			pwrk->bUseArabicPUA = DT_TRUE;		// 0xE000-0xE08F will be treat as Arabic PUA only when these 4 chars exist.
	  }

//	  if(gDT_ENABLE_FAST_MODE)			// 2011-11-09: force to do this, it helps the performance for the FDL without extra table.
		pwrk->fdlLatinOnly = checkFontsLatinOnly(pwrk);		// 1: latin only && no extra table like scale, moveY...
															// others: other languages inside, need shaper.
		pwrk->fdlLatinOnly = (pwrk->fdlLatinOnly==1)?1:0;	// fdlLatinOnly will be 0 or 1 only (easier to use).

	  make_gBidiClass_ArrayPlaneIdx();					// to speed BidiClass bsearch.
	  
	  // Can't get fds here, because the value need to be changed when DT_SetFontStyle() had been called.
//#ifdef THAI_thai
//		if(DLO_SUCCESS==ret){
//			Font_Design_Thai *fds = (Font_Design_Thai*)&pwrk->fds;
//			pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr,fds);
//		}
//#endif
	}

ReleaseWrkMem:
	if(rtval==DLO_SUCCESS || rtval==DLO_SUCCESS_BUT_BADLAYDATA){
		*hShaper = pwrk;		
	}else{
		if(pwrk->engWkMem)	DT_free(pwrk->engWkMem);
		if(pwrk)	DT_free(pwrk);
	}
	
	return rtval;
	
}

/*---------------------------------------------------------------------------*/
DT32_int DLO_unInitShaper(DLO_Handle hShaper)
{
	DT32_int ret;
	pLayWrk pwrk = (pLayWrk) hShaper;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

	if(pwrk->ras_attr){
	  ret = pwrk->fengfuncs.uninitFont(pwrk->ras_attr);
	  if(ret!=DLO_SUCCESS)
		return DLO_BAD_ENGINE_HANDLE;
	}else
		return DLO_BAD_HANDLE;

//#if (1==DLO_OPENVG_ENABLED)
//	if(pwrk->myvgfont)
//		vgDestroyFont(pwrk->myvgfont);
//	if(pwrk->myglyphpath)
//		vgDestroyPath(pwrk->myglyphpath);
//	if(pwrk->mytranspath)
//		vgDestroyPath(pwrk->mytranspath);
//	if(pwrk->mymaskpath)
//		vgDestroyPath(pwrk->mymaskpath);
//#endif
	
	//if(pwrk->ras_attr) DT_free(pwrk->ras_attr);	// It's not required now, because it's inside pwrk now.
	if(pwrk->engWkMem)	DT_free(pwrk->engWkMem);
	if(pwrk) DT_free(pwrk);

	return DLO_SUCCESS;
}

/*---------------------------------------------------------------------------*/
DT_void  DLO_SetFontStyle(DLO_Handle hShaper, DLO_FontStyle_Option option, DT32_int value)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int tmp, tmp266;

DBG_MSG_SHOW_FUNC_NAME();

	/* engine independent option */
	if(option==FSTYLE_SPACING){
		pwrk->spacing = value;
		return;
	}

	if(value<0 && option!=FSTYLE_FORCE_MOVE_DOWN)	
		return;

	/* engine dependent option */
#ifdef BDF_RASTER
	if(pwrk->fengtype==DLO_ENG_BDFRASTER){
		pwrk->mode = DLO_LAYOUT_BIT;
		/* writedir will be set when DLO_ShapeString(), layattr */
		switch(option){
		case FSTYLE_XBYTE_ALIGN:
		  tmp = pwrk->xbytes_align;
		  if(value<=0){
			pwrk->xbytes_align = 4;
		  }else{
			pwrk->xbytes_align = value;
		  }
		  break;
		default:
			break;
		}
	}
#endif

#ifdef DIF_RASTER
	if(pwrk->fengtype==DLO_ENG_DIFRASTER_BIT){
		pwrk->mode = DLO_LAYOUT_BIT;
		/* writedir will be set when DLO_ShapeString(), layattr */
		switch(option){
		case FSTYLE_XBYTE_ALIGN:
		  tmp = pwrk->xbytes_align;
		  if(value<=0){
			pwrk->xbytes_align = 4;
		  }else{
			pwrk->xbytes_align = value;
		  }
		  break;
		default:
			break;
		}
	}
	if(pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE){
		pwrk->mode = DLO_LAYOUT_BYTE;
		/* writedir will be set when DLO_ShapeString(), layattr */
		switch(option){
		case FSTYLE_XBYTE_ALIGN:
		  tmp = pwrk->xbytes_align;
		  if(value<=0){
			pwrk->xbytes_align = 4;
		  }else{
			pwrk->xbytes_align = value;
		  }
		  break;
		default:
			break;
		}
	}
#endif

#ifdef DIGITYPE_STD
	if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
		pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
		pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256){
	  switch(option){
	  case FSTYLE_VERT:
		tmp = pwrk->vert;
		if(!value)
			pwrk->vert = 0;
		else
			pwrk->vert = 1;
		if(tmp!=pwrk->vert)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_SIZEX:
		tmp = pwrk->xsize;
		if(value>DLO_FONT_MAXSIZE)
			pwrk->xsize = DLO_FONT_MAXSIZE;
		else
			pwrk->xsize = value;
		if(tmp!=pwrk->xsize)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_SIZEY:
		tmp = pwrk->ysize;
		if(value>DLO_FONT_MAXSIZE)
			pwrk->ysize = DLO_FONT_MAXSIZE;
		else
			pwrk->ysize = value;
		if(tmp!=pwrk->ysize)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_F_EDGE:
		tmp = pwrk->f_edge;
		//pwrk->f_edge	= value;	/* Now the values are all the same as DcwRaster's define. */
		switch(value){
		case DLO_STYLE_NORMAL:
			pwrk->f_edge = DCW_EDGE_NORMAL;
			break;
		case DLO_STYLE_OUTLINE:
			pwrk->f_edge = DCW_EDGE_OUTLINE;
			break;
		case DLO_STYLE_BOLD:
			pwrk->f_edge = DCW_EDGE_BOLD;
			break;
		case DLO_STYLE_BOLD_RIGHT:
			pwrk->f_edge = DCW_EDGE_BOLD_RIGHT;
			break;
		case DLO_STYLE_BOLD_DOWN:
			pwrk->f_edge = DCW_EDGE_BOLD_DOWN;
			break;
		case DLO_STYLE_BOLD_RIGHT_DOWN:
			pwrk->f_edge = DCW_EDGE_BOLD_RIGHT_DOWN;
			break;
		default:
			pwrk->f_edge = DCW_EDGE_NORMAL;
		}
		if(tmp!=pwrk->f_edge)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_W_EDGE:
		tmp = pwrk->w_edge;
		if(value>DLO_STYLE_MAX_EDGE_WIDTH)
			pwrk->w_edge = DLO_STYLE_MAX_EDGE_WIDTH;
		else
			pwrk->w_edge= value;
		if(tmp!=pwrk->w_edge)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_W_EDGE_26_6:
		//tmp = pwrk->w_edge;
		tmp266 = pwrk->w_edge266;
		if(DTF266ToInt(value)>DLO_STYLE_MAX_EDGE_WIDTH){
			pwrk->w_edge266 = (DT_f26dot6)DTFixToF266(DLO_STYLE_MAX_EDGE_WIDTH,0);
			//pwrk->w_edge = DLO_STYLE_MAX_EDGE_WIDTH;
		}else{
			pwrk->w_edge266 = (DT_f26dot6)value;
			//pwrk->w_edge = (DT32_int)DT_F26DOT6_INTEGER(value);
		}
		// No need to check this because FSTYLE_W_EDGE must also be called.
		//if(tmp266!=pwrk->w_edge266 || tmp!=pwrk->w_edge)
		//	pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_ITALIC:
		tmp = pwrk->italic;
		pwrk->italic= value;
		if(tmp!=pwrk->italic)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_P_UNDERLINE:
		tmp = pwrk->p_underline;
		pwrk->p_underline= value;
		if(tmp!=pwrk->p_underline)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_W_UNDERLINE:
		tmp = pwrk->w_underline;
		pwrk->w_underline= value;
		if(tmp!=pwrk->w_underline)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_E_UNDERLINE:
		tmp = pwrk->e_underline;
		pwrk->e_underline= value;
		if(tmp!=pwrk->e_underline)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_GRAD:
		tmp = pwrk->grade;
		switch(value){
		case DLO_GRAY_256:
			pwrk->grade = DCW_MODE_GRAY256;
			pwrk->mode = DLO_LAYOUT_BYTE;
			pwrk->fengtype = DLO_ENG_DCWRASTER_GRAY256;
			break;
		case DLO_GRAY_MONO:
			pwrk->grade = DCW_MODE_MONOCHROME;
			pwrk->mode = DLO_LAYOUT_BIT;
			pwrk->fengtype = DLO_ENG_DCWRASTER_MONO;
			break;
		case DLO_GRAY_16:
		default:
			pwrk->grade = DCW_MODE_GRAY16;
			pwrk->mode = DLO_LAYOUT_BYTE;
			pwrk->fengtype = DLO_ENG_DCWRASTER_GRAY16;
			break;
		}
		if(tmp!=pwrk->grade)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_GRAD_VALUES:
		tmp = pwrk->grade_values;
		if(value<0 || value>DLO_GRADE_MAX_FLAG){
			pwrk->grade_values = DLO_GRADE_INDEX_0X00_0X0F;	/* Or, do nothing here. */
		}else{
			pwrk->grade_values = value;
		}
		if(tmp!=pwrk->grade_values)
			pwrk->isReinitFont = 1;
		break;
	  case FSTYLE_XBYTE_ALIGN:
		tmp = pwrk->xbytes_align;
		if(value<=0){
			pwrk->xbytes_align = 4;
		}else{
			pwrk->xbytes_align = value;
		}
		/*No need to re-initFont.*/
		/*if(tmp!=pwrk->xbytes_align)
			pwrk->isReinitFont = 1;	
		*/
		break;
	  case FSTYLE_HINTING:
		  tmp = pwrk->hinting;
		  if(value!=1 && value!=2){
			  pwrk->hinting = 1;
		  }else{
			  pwrk->hinting = value;
		  }
		  break;
	  case FSTYLE_FORCE_MOVE_DOWN:
		  tmp = pwrk->forcedown;
		  if(value!=-1 && (value>1000 || value<-1)){
			  pwrk->forcedown = 0;
		  }else{
			  pwrk->forcedown = value;
		  }
		  break;		  
	  default:
		  break;
	  }
	}
#endif

#ifdef DIGITYPE_OUL
	if( pwrk->fengtype==DLO_ENG_DCWOPENVG){
	  switch(option){
	  case FSTYLE_VERT:
		if(value)
			pwrk->vert = 1;
		else
			pwrk->vert = 0;
		((DcwOpenVG_Attr*)pwrk->ras_attr)->vert = pwrk->vert;	// no need to ReInitFont().
		break;
	  case FSTYLE_SIZEX:
		pwrk->xsize = value;
		break;
	  case FSTYLE_SIZEY:
		pwrk->ysize = value;
		break;

	  default:
		  /* Others will be dealed outside. */
		  break;
	  }
	}
#endif

	switch(option){
	case FSTYLE_BIDI_RULE:
		tmp = pwrk->bidirule;
		if(value!=DLO_BIDI_UNIRULE && value!=DLO_BIDI_DCWRULE){
			if(pwrk->bidirule==DLO_BIDI_UNIRULE || pwrk->bidirule==DLO_BIDI_DCWRULE){
				// do nothing.
			}else
				pwrk->bidirule = DLO_BIDI_UNIRULE;
		}else{
			pwrk->bidirule = value;
		}
		  break;
	default:
		break;
	}
}

/*---------------------------------------------------------------------------*/
#if 0	//Comment for test BiDirection
//DT32_int DLO_ShapeString(DLO_Handle hShaper, DLO_LayAttr *layattr,/* DT32_int sizeX, DT32_int sizeY, */DLO_LayBuf *laybuf, DT32_int flag)
//{
//	pLayWrk pwrk = (pLayWrk) hShaper;
//	DT32_int i, size, rtv, rtval, ret=DLO_SUCCESS;	/* Jacky_20100209 */
//	DL_CodeRange rang;
//	DL_CodeAttr	 lcatt;
//	Str_Seg	ss;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	if(!pwrk)
//		return DLO_BAD_HANDLE;
//
//	/* Check parameters */
//	if(/*layattr->mainScript<0 ||*/ layattr->mainScript>=DLO_SCRIPT_END)return DLO_SCRIPT_NOT_SUPPORT;
//	if(/*layattr->mainLang<0 ||*/ layattr->mainLang>=DLO_LANG_end)		return DLO_LANG_NOT_SUPPORT;
//	if(layattr->ucs_cnt<=0 || !layattr->ucs_str)					return DLO_UCS_ERR;
//	if(layattr->ucs_cnt>DLO_MAXCODES_PER_STR_SEG)					return DLO_UCS_STR_TOO_LONG;
//	
//	/* switch to DLO_DATA_PREPARE_POS or DLO_DATA_RENDER */
//	if(flag&DLO_DATA_PREPARE_POS)	Clearwrk(pwrk);
//	pwrk->attr	= layattr;
//	pwrk->lobuf = laybuf;	
//
//	if( (flag&DLO_DATA_RENDER) && !(flag&DLO_DATA_PREPARE_POS) ) goto DATA_RENDER;
//	else goto DATA_PREPARE_POS;
//
//	/* DATA_PREPARE_POS:											*/
//	/* Deal with the code string(ucs_str),							*/
//	/* Divided ucs_str to several segments by code range.			*/
//	/* Decide write direction if DLO_DECIDE_BY_STR					*/
//	/* Make the returned DLO_LayBuf, except olDatabuf,olDatabufSize,olSizebuf...	*/
//DATA_PREPARE_POS:
//	
// #ifdef _SPEEDTEST
//	//printf("DcwShaperVG benchmark by CPU clocks\n");
//	if(!nline){
//	  printf("line\tPOS\tOUL\tParse\tMask\tStroke\tFill\n");
//	  nline++;
//	}
//	printf("%d\t", nline); nline++;
//	SpeedTestStart("POS");
// #endif
//
//	/* Font style has been changed, re-initFont() */
//	if( pwrk->isReinitFont && 
//		(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256) ){
//		do{	
//		  ret = pwrk->fengfuncs.initFont(pwrk->ras_attr,pwrk->fondata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
//		  if(ret==DLO_NOT_ENOUGH_ENGINEWKMEM){
//			rtval = ReAllocEngWorkMem(pwrk);
//			if(DLO_SUCCESS!=rtval){
//				return rtval;
//			}else{
//				pwrk->TotalWkmsize = pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;				
//			}
//		  }		
//		}while(ret==DLO_NOT_ENOUGH_ENGINEWKMEM);
//		if(ret != DLO_SUCCESS)
//			return ret;
//	}
//
//	pwrk->seg_start = 0; pwrk->seg_end	=0; size = 0; pwrk->seg_cnt = 0; pwrk->segw = 0;
//	pwrk->cur_g1idx = 0; pwrk->cur_g2idx=0; 
//	while(pwrk->seg_start < layattr->ucs_cnt){
//	  /* Divided ucs_str to segments, get its script, lang */
//	  if(layattr->mainScript==DLO_SCRIPT_DFLT || layattr->mainLang==DLO_LANG_DFLT){
//	   rang = DL_DivideStrByScript(layattr->ucs_str,(DT16_ushort)layattr->ucs_cnt, pwrk->seg_start,&pwrk->seg_end);
//	   DL_GetScriptLang(rang, &pwrk->seg_script,&pwrk->seg_lang);
//	   pwrk->seg_dir = GetSegDirectByScript(pwrk->seg_script);
//	  }else{
//	   pwrk->seg_script = layattr->mainScript;
//	   pwrk->seg_lang	= layattr->mainLang;
//	   pwrk->seg_end = layattr->ucs_cnt;
//	   pwrk->seg_dir = GetSegDirectByScript(pwrk->seg_script);
//	  }
//
//	  /* If DLO_DECIDE_BY_STR, the first segment's write direction will be used. */
//      if(pwrk->seg_start==0){
//		if(layattr->writedir == DLO_DECIDE_BY_STR) 
//		  pwrk->writedir = pwrk->seg_dir;
//	    else
//		  pwrk->writedir = layattr->writedir;
//	  }
//
//	  /* To avoid the wrong position of "space" char while seg_dir is not the same with writedir. */
//	  lcatt = DL_GetCodeCategory(layattr->ucs_str[pwrk->seg_end-1]);
//	  if(lcatt.range==DL_Range_INHERIT){ 
//		if( pwrk->seg_dir!=pwrk->writedir 
//			&& pwrk->seg_end<layattr->ucs_cnt)	/* Avoid the last "space" being skipped. Jacky_20101019 */
//		  pwrk->seg_end = pwrk->seg_end-1;
//	  }
//
//	  size = pwrk->seg_end - pwrk->seg_start;
//	  if(size<=0)	break;
//
//	  /* Get the DLO_Data_Table in dlo file data by script and lang. */
//	  rtv = DFS_GetdlotabHeader(pwrk, pwrk->seg_script, pwrk->seg_lang, &pwrk->cur_dlotab_idx);
//	  if(rtv == DLO_TAB_NOT_EXIST){ pwrk->dlo_tab_exist = 0; ret |= DLO_TABLE_NOT_FOUND;}
//	  else pwrk->dlo_tab_exist = 1;
//	
//	  /* Every segment is dispatched to its language processor. */
//	  pwrk->rendermode = DLO_DATA_PREPARE_POS;
//	  rtv = FunctionByLang( pwrk, pwrk->seg_script, pwrk->seg_lang, FUNC_RENDERTOBUF, 0); ret |= rtv;
//	  
//	  pwrk->seg_cnt++;
//	  pwrk->seg_start += size; size=0; pwrk->segw=0;
//	}
//	
//	/* Calculate the caret-positioning. */
//	rtv = Fillwkbuf(pwrk);
//	if(rtv!=DLO_SUCCESS)
//		return rtv;
//
// #ifdef _SPEEDTEST
//	SpeedTestEnd();
// #endif
//
//	if(!(flag&DLO_DATA_RENDER)) return ret;
//	
//DATA_RENDER:
//
// #ifdef _SPEEDTEST
//	SpeedTestStart("OUL");
// #endif
//
//	pwrk->rendermode = DLO_DATA_RENDER;
//#ifdef DIGITYPE_OUL
//  if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
//	  DT_memset(pwrk->lobuf->olDatabuf,0,pwrk->lobuf->olDatabufSize);
//	  DT_memset(pwrk->lobuf->olSizebuf,0,DLO_MAXCODES_PER_STR_SEG*sizeof(DT32_long));
//	  pwrk->oldatasz = pwrk->lobuf->olDatabufSize;	/* keep the size of olDatabuf had been allocated.			*/
//	  pwrk->lobuf->olDatabufSize = 0;				/* It has to set to 0, because the data will be appended.	*/
//
//	pwrk->seg_start = 0; pwrk->seg_end = 0; size = 0;
//	for(i=0;i<pwrk->seg_cnt;i++){
//	  ss = pwrk->segarr[i];
//	  rtv = FunctionByLang( pwrk, ss.script, ss.lang, FUNC_RENDERTOBUF, &ss); ret |= rtv;
//	}
//  }
//#endif
//
//#ifdef DIGITYPE_STD
//  if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256){
//	/*DT_memset(pwrk->lobuf->bmpbuf,0,pwrk->lobuf->bufsize);*//*Marked by Jacky_20100527, should be done by caller */
//	pwrk->seg_start = 0; pwrk->seg_end = 0; size = 0;
//	for(i=0;i<pwrk->seg_cnt;i++){
//	  ss = pwrk->segarr[i];
//	  rtv = FunctionByLang( pwrk, ss.script, ss.lang, FUNC_RENDERTOBUF, &ss); ret |= rtv;
//	}
//  }
//#endif
//
//#ifdef BDF_RASTER
//  if(pwrk->fengtype==DLO_ENG_BDFRASTER){
//	/*DT_memset(pwrk->lobuf->bmpbuf,0,pwrk->lobuf->bufsize);*//*Marked by Jacky_20100527, should be done by caller */
//	pwrk->seg_start = 0; pwrk->seg_end = 0; size = 0;
//	for(i=0;i<pwrk->seg_cnt;i++){
//	  ss = pwrk->segarr[i];
//	  rtv = FunctionByLang( pwrk, ss.script, ss.lang, FUNC_RENDERTOBUF, &ss); ret |= rtv;
//	}
//  }
//#endif
//
//#ifdef DIF_RASTER
//  if( pwrk->fengtype==DLO_ENG_DIFRASTER_BIT ||
//	  pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE){
//	/*DT_memset(pwrk->lobuf->bmpbuf,0,pwrk->lobuf->bufsize);*//*Marked by Jacky_20100527, should be done by caller */
//	pwrk->seg_start = 0; pwrk->seg_end = 0; size = 0;
//	for(i=0;i<pwrk->seg_cnt;i++){
//	  ss = pwrk->segarr[i];
//	  rtv = FunctionByLang( pwrk, ss.script, ss.lang, FUNC_RENDERTOBUF, &ss); ret |= rtv;
//	}
//  }
//#endif
//
// #ifdef _SPEEDTEST
//	SpeedTestEnd();
// #endif
//
//	return ret;
}
#endif	// #if 0 //Comment for test BiDirection

DT32_int DLO_ShapeString_DcwRule(DLO_Handle hShaper, DLO_LayAttr *layattr,/* DT32_int sizeX, DT32_int sizeY, */DLO_LayBuf *laybuf, DT32_int flag)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int i, size, rtv, /*rtval,*/ ret=DLO_SUCCESS, bEmpty;	/* Jacky_20100209 */
	//DL_CodeRange rang;
	//DL_CodeAttr	 lcatt;
	Str_Seg	ss;
//#ifdef INDICS_devanagari
//	FontPosition * p_fnt_pos;
//#endif

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

	/* Check parameters */
	if(/*layattr->mainScript<0 ||*/ layattr->mainScript>=DLO_SCRIPT_END)return DLO_SCRIPT_NOT_SUPPORT;
	if(/*layattr->mainLang<0 ||*/ layattr->mainLang>=DLO_LANG_end)		return DLO_LANG_NOT_SUPPORT;
	if(layattr->ucs_cnt<=0 || !layattr->ucs_str)					return DLO_UCS_ERR;
	if(layattr->ucs_cnt>DLO_MAXCODES_PER_STR_SEG)					return DLO_UCS_STR_TOO_LONG;
	
	/* switch to DLO_DATA_PREPARE_POS or DLO_DATA_RENDER */
	if(flag&DLO_DATA_PREPARE_POS)	Clearwrk(pwrk);
	pwrk->attr	= layattr;
	pwrk->lobuf = laybuf;	

#ifdef INDICS_devanagari
//	p_fnt_pos = &(pwrk->fnt_pos[0]);
//	size = DT_MAX_CODES_PER_STR*2;
//	for(i=0;i<size; i++){
//		p_fnt_pos->aw = 0;
//		p_fnt_pos->flags = 0;
//		p_fnt_pos->leftup = 0;
//		p_fnt_pos->offx = 0;
//		p_fnt_pos++;
//	}
	DT_memset(pwrk->fnt_pos,0,sizeof(pwrk->fnt_pos));
#endif

	if( (flag&DLO_DATA_RENDER) && !(flag&DLO_DATA_PREPARE_POS) ) goto DATA_RENDER;
	else goto DATA_PREPARE_POS;

	/* DATA_PREPARE_POS:											*/
	/* Deal with the code string(ucs_str),							*/
	/* Divided ucs_str to several segments by code range.			*/
	/* Decide write direction if DLO_DECIDE_BY_STR					*/
	/* Make the returned DLO_LayBuf, except olDatabuf,olDatabufSize,olSizebuf...	*/
DATA_PREPARE_POS:
	
 #ifdef _SPEEDTEST
	//printf("DcwShaperVG benchmark by CPU clocks\n");
	if(!nline){
	  //printf("line\tPOS\tOUL\tParse\tMask\tStroke\tFill\n");
	  nline++;
	}
	//printf("%d\t", nline); nline++;
	SpeedTestStart("POS");
 #endif

	/* Font style has been changed, re-initFont() */
//	if( pwrk->isReinitFont && 
//		(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256) ){
//		do{	
//		  ret = pwrk->fengfuncs.initFont(pwrk->ras_attr,pwrk->fondata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
//		  if(ret==DLO_NOT_ENOUGH_ENGINEWKMEM){
//			rtval = ReAllocEngWorkMem(pwrk);
//			if(DLO_SUCCESS!=rtval){
//				return rtval;
//			}else{
//				pwrk->TotalWkmsize = pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;				
//			}
//		  }		
//		}while(ret==DLO_NOT_ENOUGH_ENGINEWKMEM);
//		if(ret != DLO_SUCCESS)
//			return ret;
//	}

	clearg2info(pwrk,layattr->ucs_cnt);	// clear g2info

	ret = ReInitFont(pwrk);
	if(DLO_SUCCESS != ret)
		return ret;


	/* Decide the writedir if needed. */
	if(layattr->writedir == DLO_DECIDE_BY_STR){
		if(layattr->mainScript==DLO_SCRIPT_DFLT || layattr->mainLang==DLO_LANG_DFLT){
			pwrk->writedir = DL_GetWriteDirByFirstCode(pwrk, layattr->ucs_str, layattr->ucs_cnt, NULL, NULL);
			if(DLO_DECIDE_BY_STR==pwrk->writedir){
				/* Can't decide, use L2R as default. */
				pwrk->writedir = DLO_LEFTTORIGHT;
			}
		}else{
			pwrk->writedir = GetSegDirectByScript(layattr->mainScript);
		}
	}else{
		pwrk->writedir = layattr->writedir;
	}

	pwrk->maxdifH = 0;	 pwrk->bScaled = DT_FALSE;
	pwrk->seg_start = 0; pwrk->seg_end	=0; size = 0; pwrk->seg_cnt = 0; pwrk->segw = 0; pwrk->segh = 0;
	pwrk->cur_g1idx = 0; pwrk->cur_g2idx=0; 
	pwrk->seg_script= DLO_SCRIPT_DFLT; pwrk->seg_lang = DLO_LANG_DFLT;
	pwrk->curbidi   =-1;	// avoid the affections of DLO_BIDI_UNIRULE.
	pwrk->bMinusLRsb = 0;
	pwrk->bHindi	 = 0;
	pwrk->ratio		 = DLO_BASE_RATIO;	//0;	// 2012-09-12[Jacky]: not 0: force to check logh for every language.
	while(pwrk->seg_start < layattr->ucs_cnt){
	  /* Divided ucs_str to segments, get its script, lang */
	  if(layattr->mainScript==DLO_SCRIPT_DFLT || layattr->mainLang==DLO_LANG_DFLT){
	   size = DL_DivideStrByScript_New( pwrk, layattr->ucs_str,(DT16_ushort)layattr->ucs_cnt, pwrk->seg_start,&pwrk->seg_end, 
										pwrk->writedir, &pwrk->seg_script, &pwrk->seg_lang, &pwrk->seg_dir);
	   //DL_GetScriptLang(rang, &pwrk->seg_script,&pwrk->seg_lang);
	   //pwrk->seg_dir = GetSegDirectByScript(pwrk->seg_script);
	  }else{
	   pwrk->seg_script = layattr->mainScript;
	   pwrk->seg_lang	= layattr->mainLang;
	   pwrk->seg_end = layattr->ucs_cnt;
	   pwrk->seg_dir = GetSegDirectByScript(pwrk->seg_script);
	  }

//	  /* If DLO_DECIDE_BY_STR, the first segment's write direction will be used. */
//      if(pwrk->seg_start==0){
//		if(layattr->writedir == DLO_DECIDE_BY_STR) 
//		  pwrk->writedir = pwrk->seg_dir;
//	    else
//		  pwrk->writedir = layattr->writedir;
//	  }

//	  /* To avoid the wrong position of "space" char while seg_dir is not the same with writedir. */
//	  lcatt = DL_GetCodeCategory(layattr->ucs_str[pwrk->seg_end-1]);
//	  if(lcatt.range==DL_Range_INHERIT){ 
//		if( pwrk->seg_dir!=pwrk->writedir 
//			&& pwrk->seg_end<layattr->ucs_cnt)	/* Avoid the last "space" being skipped. Jacky_20101019 */
//		  pwrk->seg_end = pwrk->seg_end-1;
//	  }

	  size = pwrk->seg_end - pwrk->seg_start;
	  if(size<=0)	break;

	  /* Get the DLO_Data_Table in dlo file data by script and lang. */
	  rtv = DFS_GetdlotabHeader(pwrk, pwrk->seg_script, pwrk->seg_lang, &pwrk->cur_dlotab_idx);
	  if(rtv == DLO_TAB_NOT_EXIST){
		  pwrk->dlo_tab_exist = 0; 
		  //ret |= DLO_TABLE_NOT_FOUND;		// 2012-02-17: don't return 
	  }else pwrk->dlo_tab_exist = 1;
	
	  /* Every segment is dispatched to its language processor. */
	  pwrk->rendermode = DLO_DATA_PREPARE_POS;
	  //rtv = FunctionByLang( pwrk, pwrk->seg_script, pwrk->seg_lang, FUNC_RENDERTOBUF, 0);	ret |= rtv;	
	  //Modified_By_Jacky_20101213: rtv will always be DLO_SUCCESS, won't be a value other than DLO_SUCCESS.
	  FunctionByLang( pwrk, pwrk->seg_script, pwrk->seg_lang, FUNC_RENDERTOBUF, 0);
	  
	  pwrk->seg_cnt++;
	  if(pwrk->seg_cnt >= DLO_SEG_LIMIT){
		  ret = DLO_SEG_ERROR;
		  break;
	  }
	  pwrk->seg_start += size; size=0; pwrk->segw=0; pwrk->segh = 0;
	}
	
	/* Calculate the caret-positioning. */
	rtv = Fillwkbuf(pwrk);
	if(rtv!=DLO_SUCCESS)
		return rtv;
	else{
		if(pwrk->lobuf->glyf_cnt>0){
			DT32_int k;
			FontCodeInfo *pfc = pwrk->g2info;
			for(k=0; k<pwrk->lobuf->glyf_cnt; k++, pfc++){
				if(!pfc->codeExist){
					if(!DT_isCode_NoEmptyFontWarning(pwrk->lobuf->glyf_seq[k],NULL)){
						ret |= DLO_EMPTY_FONT;
						break;
					}
				}
			}
		}
	}

 #ifdef _SPEEDTEST
	SpeedTestEnd();
 #endif

	if(!(flag&DLO_DATA_RENDER)) return ret;
	
DATA_RENDER:

 #ifdef _SPEEDTEST
	SpeedTestStart("OUL");
 #endif

	pwrk->rendermode = DLO_DATA_RENDER;

	bEmpty = 0;				//Modified_By_Jacky_20101213:
	ret = DLO_SUCCESS;

	if(pwrk->fengtype!=DLO_ENG_DCWOPENVG){
		if( pwrk->lobuf->bmpwidth<=0 || pwrk->lobuf->bmpheight<=0 ||
			pwrk->lobuf->bufsize<=0 || pwrk->lobuf->xbytes<=0)
		{
			if(pwrk->lobuf->glyf_cnt>0){
				DT32_int k;
				FontCodeInfo *pfc = pwrk->g2info;
				for(k=0; k<pwrk->lobuf->glyf_cnt; k++, pfc++){
					if(!pfc->codeExist){
						if(!DT_isCode_NoEmptyFontWarning(pwrk->lobuf->glyf_seq[k],NULL)){
							return DLO_EMPTY_FONT;
						}
					}
				}
				return DLO_SUCCESS;
			}else{
				return DLO_SUCCESS;
			}
		}
	}

#ifdef DIGITYPE_OUL
  if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
//	  DT_memset(pwrk->lobuf->olDatabuf,0,pwrk->lobuf->olDatabufSize);
//	  DT_memset(pwrk->lobuf->olSizebuf,0,DLO_MAXCODES_PER_STR_SEG*sizeof(DT32_long));
	  pwrk->oldatasz = pwrk->lobuf->olDatabufSize;	/* keep the size of olDatabuf had been allocated.			*/
	  pwrk->lobuf->olDatabufSize = 0;				/* It has to set to 0, because the data will be appended.	*/

	pwrk->seg_start = 0; pwrk->seg_end = 0; size = 0;
	for(i=0;i<pwrk->seg_cnt;i++){
	  ss = pwrk->segarr[i];
	  rtv = FunctionByLang( pwrk, ss.script, ss.lang, FUNC_RENDERTOBUF, &ss); 
	  //ret |= rtv;	//Modified_By_Jacky_20101213: 
	  if(rtv < DLO_SUCCESS){
		  ret = rtv;	// Error Code can't be added by '|', use the last error as a representation.
	  }else if(rtv==DLO_EMPTY_FONT){
		  bEmpty = 1;
	  }
	}
  }
#endif

#ifdef DIGITYPE_STD
  if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256){
	/*DT_memset(pwrk->lobuf->bmpbuf,0,pwrk->lobuf->bufsize);*//*Marked by Jacky_20100527, should be done by caller */
	decideCopyMethod(pwrk);
	pwrk->seg_start = 0; pwrk->seg_end = 0; size = 0;
	for(i=0;i<pwrk->seg_cnt;i++){
	  ss = pwrk->segarr[i];
	  rtv = FunctionByLang( pwrk, ss.script, ss.lang, FUNC_RENDERTOBUF, &ss);
	  //ret |= rtv;	//Modified_By_Jacky_20101213: 
	  if(rtv < DLO_SUCCESS){
		  ret = rtv;	// Error Code can't be added by '|', use the last error as a representation.
	  }else if(rtv==DLO_EMPTY_FONT){
		  bEmpty = 1;
	  }
	}
	pwrk->lastfedge = (DT8_uchar)pwrk->f_edge;
  }
#endif

#ifdef BDF_RASTER
  if(pwrk->fengtype==DLO_ENG_BDFRASTER){
	/*DT_memset(pwrk->lobuf->bmpbuf,0,pwrk->lobuf->bufsize);*//*Marked by Jacky_20100527, should be done by caller */
	pwrk->seg_start = 0; pwrk->seg_end = 0; size = 0;
	for(i=0;i<pwrk->seg_cnt;i++){
	  ss = pwrk->segarr[i];
	  rtv = FunctionByLang( pwrk, ss.script, ss.lang, FUNC_RENDERTOBUF, &ss);
	  //ret |= rtv;	//Modified_By_Jacky_20101213: 
	  if(rtv < DLO_SUCCESS){
		  ret = rtv;	// Error Code can't be added by '|', use the last error as a representation.
	  }else if(rtv==DLO_EMPTY_FONT){
		  bEmpty = 1;
	  }
	}
  }
#endif

#ifdef DIF_RASTER
  if( pwrk->fengtype==DLO_ENG_DIFRASTER_BIT ||
	  pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE){
	/*DT_memset(pwrk->lobuf->bmpbuf,0,pwrk->lobuf->bufsize);*//*Marked by Jacky_20100527, should be done by caller */
	pwrk->seg_start = 0; pwrk->seg_end = 0; size = 0;
	for(i=0;i<pwrk->seg_cnt;i++){
	  ss = pwrk->segarr[i];
	  rtv = FunctionByLang( pwrk, ss.script, ss.lang, FUNC_RENDERTOBUF, &ss);
	  //ret |= rtv;	//Modified_By_Jacky_20101213: 
	  if(rtv < DLO_SUCCESS){
		  ret = rtv;	// Error Code can't be added by '|', use the last error as a representation.
	  }else if(rtv==DLO_EMPTY_FONT){
		  bEmpty = 1;
	  }
	}
  }
#endif

 #ifdef _SPEEDTEST
	SpeedTestEnd();
 #endif

	if(ret==DLO_SUCCESS){			//Modified_By_Jacky_20101213:
		if(bEmpty){
			if(pwrk->lobuf->glyf_cnt>0){
				DT32_int k;
				FontCodeInfo *pfc = pwrk->g2info;
				for(k=0; k<pwrk->lobuf->glyf_cnt; k++, pfc++){
					if(!pfc->codeExist){
						if(!DT_isCode_NoEmptyFontWarning(pwrk->lobuf->glyf_seq[k],NULL)){
							return DLO_EMPTY_FONT;
						}
					}
				}
				return DLO_SUCCESS;
			}else{
				return DLO_SUCCESS;
			}
		}
	}

	return ret;
}

// These functions are in DcwBidi.c used for parsing lines.
/*---------------------------------------------------------------------------*/
DT32_int DLO_ShapeString/*_BidiShapeFirst*/(DLO_Handle hShaper, DLO_LayAttr *layattr,/* DT32_int sizeX, DT32_int sizeY, */DLO_LayBuf *laybuf, DT32_int flag)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int i, size, rtv, /*rtval,*/ ret=DLO_SUCCESS, bEmpty, bBreak;	/* Jacky_20100209 */
	DT16_ushort	idx, j, c, g;
	DT32_int baselevel, ich, tmpg2idx;
	DT32_int ncnt_prgf = 0;	// characters count in the first paragraph.
	DT32_int ncnt_line = 0;	// characters count in the first line of the first paragraph.
	DL_CodeAttr castart, caend;
	DLO_Script  scend; 
	DLO_Language laend;
//	DT16_ushort	*oriText = NULL;
//	DT32_int	oriTextcnt = 0;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

	/* Use the original DcwRule. */
	if(pwrk->bidirule==DLO_BIDI_DCWRULE)
		return DLO_ShapeString_DcwRule(hShaper, layattr, laybuf, flag);

	/* Check parameters */
	if(layattr->mainScript>=DLO_SCRIPT_END)	return DLO_SCRIPT_NOT_SUPPORT;
	if(layattr->mainLang>=DLO_LANG_end)		return DLO_LANG_NOT_SUPPORT;
	if(layattr->ucs_cnt<=0 || !layattr->ucs_str)	return DLO_UCS_ERR;
	if(layattr->ucs_cnt>DLO_MAXCODES_PER_STR_SEG)	return DLO_UCS_STR_TOO_LONG;
	
	/* switch to DLO_DATA_PREPARE_POS or DLO_DATA_RENDER */
	if(flag&DLO_DATA_PREPARE_POS)	Clearwrk(pwrk);
	pwrk->attr	= layattr;
	pwrk->lobuf = laybuf;
	
	// keep the string in a temp buffer.
	DT_memcpy(pwrk->tmptext, layattr->ucs_str, layattr->ucs_cnt*sizeof(layattr->ucs_str[0]));
	// re-point the text string to avoid modifing. (BiDi will modify the string directly.)
	pwrk->attr->ucs_str = pwrk->tmptext;

	if( (flag&DLO_DATA_RENDER) && !(flag&DLO_DATA_PREPARE_POS) ) goto DATA_RENDER;
	else goto DATA_PREPARE_POS;

	/* DATA_PREPARE_POS:											*/
	/* Deal with the code string(ucs_str),							*/
	/* Divided ucs_str to several segments by code range.			*/
	/* Decide write direction if DLO_DECIDE_BY_STR					*/
	/* Make the returned DLO_LayBuf, except olDatabuf,olDatabufSize,olSizebuf...	*/
DATA_PREPARE_POS:
	
 #ifdef _SPEEDTEST
	//printf("DcwShaperVG benchmark by CPU clocks\n");
	if(!nline){
	  printf("line\tPOS\tOUL\tParse\tMask\tStroke\tFill\n");
	  nline++;
	}
	printf("%d\t", nline); nline++;
	SpeedTestStart("POS");
 #endif

	/* Font style has been changed, re-initFont() */
//	if( pwrk->isReinitFont && 
//		(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256) ){
//		do{	
//		  ret = pwrk->fengfuncs.initFont(pwrk->ras_attr,pwrk->fondata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
//		  if(ret==DLO_NOT_ENOUGH_ENGINEWKMEM){
//			rtval = ReAllocEngWorkMem(pwrk);
//			if(DLO_SUCCESS!=rtval){
//				return rtval;
//			}else{
//				pwrk->TotalWkmsize = pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;				
//			}
//		  }		
//		}while(ret==DLO_NOT_ENOUGH_ENGINEWKMEM);
//		if(ret != DLO_SUCCESS)
//			return ret;
//	}

	clearg2info(pwrk,layattr->ucs_cnt);	// clear g2info

	ret = ReInitFont(pwrk);
	if(DLO_SUCCESS != ret)
		return ret;

	// Implementing UAX9: The Unicode BiDi Rule.
	// NOTICE: we don't use pwrk->segarr to restore the segments info.
	// We parse and devide the string into individual segments everytime, because:
	// 1. the original string will be modified and reversed if need.
	// 2. if we keep every segment, it may need too many segments <= a problem of memory. (DLO_SEG_LIMIT issue)
	// Every individual segment(word) will be processed by the response language function, only the pwrk->seg_xxx is used.
	// Ex: in each language function, pwrk->seg_start represents the start index of the string, while pwrk->seg_end represents the end.
	// pwrk->seg_xxx isn't reliable when next segment encountered.
	if(pwrk->bidirule==DLO_BIDI_UNIRULE)
	{
		switch(pwrk->attr->writedir)
		{
		case DLO_DECIDE_BY_STR:
			baselevel = -1;		// decide by first character that have strong types.
			break;
		case DLO_RIGHTTOLEFT:
			baselevel = 1;
			break;
		case DLO_LEFTTORIGHT:
		default:
			baselevel = 0;
			break;
		}

		ich = bidi_classify(pwrk->attr->ucs_str,pwrk->biditypes,pwrk->attr->ucs_cnt,DT_FALSE);
		DT_memset(pwrk->bidilevel, 0, sizeof(pwrk->bidilevel));
		// Devide paragraph here! Now, we support ONE PARAGRAPH ONLY!
		ncnt_prgf = bidi_BidiParagraph(&baselevel,pwrk->biditypes,pwrk->bidilevel,pwrk->attr->ucs_cnt);
		pwrk->writedir = (baselevel==1)?DLO_RIGHTTOLEFT:DLO_LEFTTORIGHT;

		// assign directional types again, but for WS, S this time
		ich = bidi_classify(pwrk->attr->ucs_str,pwrk->biditypes,pwrk->attr->ucs_cnt,DT_TRUE);
		// You can refer to bidi_BidiLines() to implement multi-lines paragraph.
		// Now we deal with one line only, so we don't call this function. 
		// PS: bidi_BidiLines() lacks Rule L3 in (UAX #9: Unicode Bidirectional Algorithm)
		//bidi_BidiLines(baselevel,pwrk->attr->ucs_str,pwrk->biditypes,pwrk->bidilevel,pwrk->attr->ucs_cnt,1,NULL);
		
		// If you want to support multi-lines, shape the string to glyphs here first.
		// Then calculate the sum of advanced widths to break line. (make pbrk for bidi_BidiLines())
		// Finally you can call bidi_BidiLines().

		// **************Now, we support ONE LINE ONLY!**************
		ncnt_line = bidi_resolveLines(pwrk->attr->ucs_str, NULL, ncnt_prgf);
		bBreak = pwrk->attr->ucs_cnt - ncnt_line;

		// Replace codes with glyphs
		pwrk->maxdifH = 0;	 pwrk->bScaled = DT_FALSE;
		pwrk->seg_start = 0; pwrk->seg_end	=0; size = 0; pwrk->seg_cnt = 0; pwrk->segw = 0; pwrk->segh = 0;
		pwrk->cur_g1idx = 0; pwrk->cur_g2idx=0; 
		pwrk->seg_script= DLO_SCRIPT_DFLT; pwrk->seg_lang = DLO_LANG_DFLT;
		pwrk->curbidi   =-1; 
		pwrk->bMinusLRsb = 0;
		pwrk->bHindi	 = 0;
		pwrk->ratio		 = DLO_BASE_RATIO;	//0;	// 2012-09-12[Jacky]: not 0: force to check logh for every language.
		while(pwrk->seg_start < ncnt_line)
		{
			//devide segments according to its script
			castart = DL_GetCodeCategory(pwrk,pwrk->attr->ucs_str[pwrk->seg_start]);
			if(castart.range==DL_Range_Special && castart.cate==DL_Bidi_Control){
				SetCurrentBidiCtrl(pwrk,pwrk->attr->ucs_str[pwrk->seg_start]);
			}
			DL_GetScriptLang(castart.range,&pwrk->seg_script,&pwrk->seg_lang);
			pwrk->seg_dir = GetSegDirectByScript(pwrk->seg_script);
			pwrk->seg_end = pwrk->seg_start+1;
			while(pwrk->seg_end < ncnt_line)
			{
				caend = DL_GetCodeCategory(pwrk,pwrk->attr->ucs_str[pwrk->seg_end]);
				DL_GetScriptLang(caend.range,&scend,&laend);
				if( scend==pwrk->seg_script 
					|| (caend.range==DL_Range_Special && (caend.cate==DL_ZeroWidth_Format || caend.cate==DL_Symbol_Other))	// for 0x200B, 0x200C, 0x200D or0x25CC
					)
				{
					pwrk->seg_end++;
				}else
				{
					break;
				}
			}

			size = pwrk->seg_end - pwrk->seg_start;
			if(size<=0)	
				break;

			/* Get the DLO_Data_Table in dlo file data by script and lang. */
			rtv = DFS_GetdlotabHeader(pwrk, pwrk->seg_script, pwrk->seg_lang, &pwrk->cur_dlotab_idx);
			if(rtv == DLO_TAB_NOT_EXIST)
			{ 
				pwrk->dlo_tab_exist = 0; 
				//ret |= DLO_TABLE_NOT_FOUND;		// 2012-02-17: don't return 
			}
			else 
				pwrk->dlo_tab_exist = 1;
	
			tmpg2idx = pwrk->cur_g2idx;
			// check if the seg needs to be reversed to get the right results(affects arabic shape)?
			if(isNeedReverse(pwrk))
			{
				bidi_reverse_nsm(pwrk->attr->ucs_str+pwrk->seg_start,size);
			}
			/* Every segment is dispatched to its language processor. */
			pwrk->rendermode = DLO_DATA_PREPARE_POS;
			//Modified_By_Jacky_20101213: rtv will always be DLO_SUCCESS, won't be a value other than DLO_SUCCESS.
			FunctionByLang( pwrk, pwrk->seg_script, pwrk->seg_lang, FUNC_RENDERTOBUF, 0);
	  
			// reverse the seg back.
			if(isNeedReverse(pwrk))
			{
				bidi_reverse_nsm(pwrk->attr->ucs_str+pwrk->seg_start,size);
				//bidi_reverse_nsm(pwrk->gseq2+tmpg2idx, pwrk->cur_g2idx-tmpg2idx);
				bidi_reverse_nsm_withg2info(pwrk->gseq2+tmpg2idx, pwrk->g2info+tmpg2idx, pwrk->cur_g2idx-tmpg2idx);
			}
			// Mark the following lines, because seg_cnt isn't required when using DLO_BIDI_UNIRULE.
			
			// make a new level array for reorder ==> glyflevel[], glyftypes[]
			for(i=pwrk->seg_start;i<pwrk->seg_end;i++){
				Parse_n_per_glyf(pwrk->gseq[i].n_per_glyf2,&c,&g);

				for(j=0;j<g;j++){
					if(0==j){			// first glyf
						idx = i;
					}else if(j+1==g){	// last glyf
						idx = i+c-1;
					}else{
						idx = i+j;
						if(idx>i+c-1)
							idx = i+c-1;// fill the last code's info to the glyf
					}
					pwrk->glyftypes[tmpg2idx] = pwrk->biditypes[idx];
					pwrk->glyflevel[tmpg2idx] = pwrk->bidilevel[idx];
					tmpg2idx++;
				}
			}
			pwrk->seg_start += size; size=0; pwrk->segw=0; pwrk->segh = 0;			
		}
		//if(pwrk->cur_g2idx != Fill_lobuf1(pwrk,0,0+ncnt_line))	// deal ONE LINE ONLY.
		//{
		//	// something error here.
		//}
		Fill_lobuf1(pwrk);	// deal ONE LINE ONLY (from the first glyph).

		// Above is used to generate a new string. Now reparsing the first line.
		
		// Following processes are applied in the line. (ncnt_line chars)
		//bidi_resolveWhitespace(baselevel, pwrk->biditypes, pwrk->bidilevel, ncnt_line); // 1 line only  
		bidi_resolveWhitespace(baselevel, pwrk->glyftypes, pwrk->glyflevel, pwrk->lobuf->glyf_cnt); // 1 line only
		//if (1)	// mirror means (), <>, {}... please refer to http://www.unicode.org/Public/UNIDATA/BidiMirroring.txt
		{
			//bidi_mirror(pwrk->attr->ucs_str, pwrk->bidilevel, ncnt_line);
			bidi_mirror(pwrk->lobuf->glyf_seq, pwrk->glyflevel, pwrk->lobuf->glyf_cnt);
		}

		// this will reorder pwrk->lobuf->glyf_seq and pwrk->lobuf->caret_seq.
		//bidi_reorder_caret_seq(baselevel, pwrk->lobuf->caret_seq, pwrk->glyflevel, pwrk->lobuf->glyf_cnt, pwrk->lobuf->glyf_seq, DT_TRUE/*isGlyphNeedReverseNsm(pwrk)*/);
		bidi_reorder_caret_seq_g2info(baselevel, pwrk->lobuf->caret_seq, pwrk->g2info, pwrk->glyflevel, pwrk->lobuf->glyf_cnt, pwrk->lobuf->glyf_seq, DT_TRUE/*isGlyphNeedReverseNsm(pwrk)*/);

		// because the lobuf->glyf_seq is reordered, it needs to refresh g2info
//		for(j=0; j<pwrk->lobuf->glyf_cnt; j++){
//			queryFontCodeInfo(pwrk, j);
//		}

		// Calculate the other information of caret_seq
		Fill_lobuf2(pwrk);
		// ************** ONE LINE Ends here!!!**************
	}

 #ifdef _SPEEDTEST
	SpeedTestEnd();
 #endif

	if(ret >= DLO_SUCCESS){
		// use g2info to check if empty fonts.
		if(pwrk->lobuf->glyf_cnt>0){
			DT32_int k;
			FontCodeInfo *pfc = pwrk->g2info;
			for(k=0; k<pwrk->lobuf->glyf_cnt; k++, pfc++){
				if(!pfc->codeExist){
					if(!DT_isCode_NoEmptyFontWarning(pwrk->lobuf->glyf_seq[k],NULL)){
						ret |= DLO_EMPTY_FONT;
						break;
					}
				}
			}
		}

		if(bBreak){
			ret |= DLO_BREAKLINE;
		}
	}

	if(!(flag&DLO_DATA_RENDER)) 
		return ret;
	
DATA_RENDER:

 #ifdef _SPEEDTEST
	SpeedTestStart("OUL");
 #endif

//	pwrk->rendermode = DLO_DATA_RENDER;

	bEmpty = 0;				//Modified_By_Jacky_20101213:
	ret = DLO_SUCCESS;

#ifdef DIGITYPE_OUL
  if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
//	  DT_memset(pwrk->lobuf->olDatabuf,0,pwrk->lobuf->olDatabufSize);
//	  DT_memset(pwrk->lobuf->olSizebuf,0,DLO_MAXCODES_PER_STR_SEG*sizeof(DT32_long));
	  pwrk->oldatasz = pwrk->lobuf->olDatabufSize;	/* keep the size of olDatabuf had been allocated.			*/
	  pwrk->lobuf->olDatabufSize = 0;				/* It has to set to 0, because the data will be appended.	*/
  }
#endif

    decideCopyMethod(pwrk);
	pwrk->seg_start = 0; pwrk->seg_end	=0; size = 0;
	while(pwrk->seg_start < pwrk->lobuf->glyf_cnt)
	{
		//devide segments according to its script
		castart = DL_GetCodeCategory(pwrk,pwrk->lobuf->glyf_seq[pwrk->seg_start]);
		DL_GetScriptLang(castart.range,&pwrk->seg_script,&pwrk->seg_lang);
		//pwrk->seg_dir = GetSegDirectByScript(pwrk->seg_script);
		pwrk->seg_end = pwrk->seg_start+1;
		while(pwrk->seg_end < pwrk->lobuf->glyf_cnt)
		{
			caend = DL_GetCodeCategory(pwrk,pwrk->lobuf->glyf_seq[pwrk->seg_end]);
			DL_GetScriptLang(caend.range,&scend,&laend);
			
			if( scend==pwrk->seg_script 
			|| (caend.range==DL_Range_Special && (caend.cate==DL_ZeroWidth_Format || caend.cate==DL_Symbol_Other))	// for 0x200B, 0x200C, 0x200D or0x25CC
			){
				pwrk->seg_end++;
			}else
			{
				break;
			}
		}

		size = pwrk->seg_end - pwrk->seg_start;
		if(size<=0)	
			break;
  
		rtv = FunctionByLang( pwrk, pwrk->seg_script, pwrk->seg_lang, FUNC_RENDERBYPOS, 0);	
		if(rtv < DLO_SUCCESS){
			ret = rtv;	// Error Code can't be added by '|', use the last error as a representation.
		}else if(rtv==DLO_EMPTY_FONT){
			bEmpty = 1;
		}
		pwrk->seg_start += size; size=0; pwrk->segw=0; pwrk->segh = 0;	
	}
	pwrk->lastfedge = (DT8_uchar)pwrk->f_edge;

 #ifdef _SPEEDTEST
	SpeedTestEnd();
 #endif

	if(ret==DLO_SUCCESS){			//Modified_By_Jacky_20101213:
		if(bEmpty){
			if(pwrk->lobuf->glyf_cnt>0){
				DT32_int k;
				FontCodeInfo *pfc = pwrk->g2info;
				for(k=0; k<pwrk->lobuf->glyf_cnt; k++, pfc++){
					if(!pfc->codeExist){
						if(!DT_isCode_NoEmptyFontWarning(pwrk->lobuf->glyf_seq[k],NULL)){
							return DLO_EMPTY_FONT;
						}
					}
				}
			}
		}
	}

	return ret;
}

/*---------------------------------------------------------------------------*/
DT32_int DLO_DeShapeString(DLO_Handle hShaper, DLO_LayBuf *laybuf)
{
	pLayWrk pwrk = (pLayWrk) hShaper;

DBG_MSG_SHOW_FUNC_NAME();

	laybuf->glyf_cnt = 0;
	laybuf->writedir = 0;

	//Jacky_20101025_for_Performance
//	if(laybuf->glyf_seq){
//		DT_memset(laybuf->glyf_seq,0,DLO_MAXCODES_PER_STR_SEG*sizeof(DT16_ushort));
//	}

	//Jacky_20101025_for_Performance
//	if(laybuf->caret_seq){
//		DT_memset(laybuf->caret_seq,0,DLO_MAXCODES_PER_STR_SEG*sizeof(DLO_CodePositioning));
//	}

	if(!pwrk)
		return DLO_BAD_HANDLE;

	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
//		if(laybuf->olDatabuf){
//			DT_memset(laybuf->olDatabuf,0,laybuf->olDatabufSize);
//		}

//		if(laybuf->olSizebuf){
//			DT_memset(laybuf->olSizebuf,0,DLO_MAXCODES_PER_STR_SEG*sizeof(DT32_long));
//		}
		laybuf->eswidth	 = 0;
		laybuf->esheight = 0;
		laybuf->olDatabufSize = 0;
	}

	if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
		pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
		pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256 ||
		pwrk->fengtype==DLO_ENG_BDFRASTER ||
		pwrk->fengtype==DLO_ENG_DIFRASTER_BIT ||
		pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE){
//		if(laybuf->bmpbuf){							//Jacky_20101025_for_Performance
//			DT_memset(laybuf->bmpbuf,0,laybuf->bufsize);
//		}
		laybuf->bitcount = 0;
		laybuf->bmpwidth = 0;
		laybuf->bmpheight= 0;
		laybuf->xbytes	 = 0;
		laybuf->bufsize	 = 0;
		laybuf->ltpos.x	 = 0;
		laybuf->ltpos.y  = 0;
	}
	return DLO_SUCCESS;
}

/*---------------------------------------------------------------------------*/
DT32_int DLO_GetCharAw(DLO_Handle hShaper, DT16_ushort ucs)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int  /*rtval,*/ ret=DLO_SUCCESS;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

	/* Font style has been changed, re-initFont() */
//	if( pwrk->isReinitFont && 
//		(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256) ){
//		do{	
//		  ret = pwrk->fengfuncs.initFont(pwrk->ras_attr,pwrk->fondata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
//		  if(ret==DLO_NOT_ENOUGH_ENGINEWKMEM){
//			rtval = ReAllocEngWorkMem(pwrk);
//			if(DLO_SUCCESS!=rtval){
//				return rtval;
//			}else{
//				pwrk->TotalWkmsize = pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;				
//			}
//		  }		
//		}while(ret==DLO_NOT_ENOUGH_ENGINEWKMEM);
//		if(ret != DLO_SUCCESS)
//			return ret;
//	}
	ret = ReInitFont(pwrk);
	if(DLO_SUCCESS != ret)
		return ret;

	if(!pwrk->ras_attr){
		return DLO_ENGINEWKMEM_ERR;
	}
	
	return pwrk->fengfuncs.getAwidth(pwrk->ras_attr, ucs, -1);

}

/*---------------------------------------------------------------------------*/
DT32_int DLO_GetFontRect(DLO_Handle hShaper, DLO_RECT *rt)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int  /*rtval,*/ ret=DLO_SUCCESS;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

	/* Font style has been changed, re-initFont() */
//	if( pwrk->isReinitFont && 
//		(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256) ){
//		do{	
//		  ret = pwrk->fengfuncs.initFont(pwrk->ras_attr,pwrk->fondata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
//		  if(ret==DLO_NOT_ENOUGH_ENGINEWKMEM){
//			rtval = ReAllocEngWorkMem(pwrk);
//			if(DLO_SUCCESS!=rtval){
//				return rtval;
//			}else{
//				pwrk->TotalWkmsize = pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;				
//			}
//		  }		
//		}while(ret==DLO_NOT_ENOUGH_ENGINEWKMEM);
//		if(ret != DLO_SUCCESS)
//			return ret;
//	}
	ret = ReInitFont(pwrk);
	if(DLO_SUCCESS != ret)
		return ret;

	if(!pwrk->ras_attr){
		return DLO_ENGINEWKMEM_ERR;
	}
	
	rt->xy.x = 0;
	rt->xy.y = 0;
	rt->hw.vx = pwrk->fengfuncs.getWidth(pwrk->ras_attr);
	rt->hw.vy = pwrk->fengfuncs.getHeight(pwrk->ras_attr);
	return DLO_SUCCESS;
	
/*
#ifdef DIGITYPE_OUL
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){

	}
#endif

#ifdef DIGITYPE_STD
	  if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256){
	  
	  }
#endif

#ifdef BDF_RASTER
  if(pwrk->fengtype==DLO_ENG_BDFRASTER){
  }
#endif
*/
}

/*---------------------------------------------------------------------------*/
DT32_int DLO_GetFontMetrix(DLO_Handle hShaper, DLO_Font_Metrix *mtx)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int  /*rtval,*/ ret=DLO_SUCCESS;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

	/* Font style has been changed, re-initFont() */
//	if( pwrk->isReinitFont && 
//		(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256) ){
//		do{	
//		  ret = pwrk->fengfuncs.initFont(pwrk->ras_attr,pwrk->fondata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
//		  if(ret==DLO_NOT_ENOUGH_ENGINEWKMEM){
//			rtval = ReAllocEngWorkMem(pwrk);
//			if(DLO_SUCCESS!=rtval){
//				return rtval;
//			}else{
//				pwrk->TotalWkmsize = pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;				
//			}
//		  }		
//		}while(ret==DLO_NOT_ENOUGH_ENGINEWKMEM);
//		if(ret != DLO_SUCCESS)
//			return ret;
//	}
	ret = ReInitFont(pwrk);
	if(DLO_SUCCESS != ret)
		return ret;

	if(!pwrk->ras_attr){
		return DLO_ENGINEWKMEM_ERR;
	}
	
	mtx->height	= pwrk->fengfuncs.getHeight(pwrk->ras_attr);
	switch(pwrk->f_edge){
	case DLO_STYLE_OUTLINE:
	case DLO_STYLE_BOLD:
		mtx->ascent	= (860*pwrk->ysize+999)/1000 + pwrk->w_edge;
		break;
	case DLO_STYLE_BOLD_DOWN:
	case DLO_STYLE_BOLD_RIGHT_DOWN:
		mtx->ascent	= (860*pwrk->ysize+999)/1000;
		break;
	case DLO_STYLE_BOLD_RIGHT:
	case DLO_STYLE_NORMAL:
	default:
		mtx->ascent	= (860*pwrk->ysize+999)/1000;
	}
	mtx->descent= mtx->height - mtx->ascent;

	mtx->inleading	= 0;
	mtx->exleading	= 0;
	mtx->width		= pwrk->fengfuncs.getWidth(pwrk->ras_attr);
	mtx->overhang	= pwrk->fengfuncs.getExten(pwrk->ras_attr);
	mtx->fontweight = 4;	/* force it now! Maybe we can parse the font file name to get this info. */
	return DLO_SUCCESS;
	
}

/*---------------------------------------------------------------------------*/
DT32_int DLO_GetCharGBMP(DLO_Handle hShaper, DT16_ushort ucs, DT_void *bmp, DT32_int xbytes, DLO_RECT clip)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int  /*rtval,*/ ret=DLO_SUCCESS, bBit=0;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

#ifdef DIGITYPE_OUL
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
		return DLO_FONTENGINE_NOT_SUPPORT;
	}
#endif

	/* Font style has been changed, re-initFont() */
//	if( pwrk->isReinitFont && 
//		(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
//		 pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256) ){
//		do{	
//		  ret = pwrk->fengfuncs.initFont(pwrk->ras_attr,pwrk->fondata,pwrk->engWkMemsz,pwrk->engWkMem,pwrk);
//		  if(ret==DLO_NOT_ENOUGH_ENGINEWKMEM){
//			rtval = ReAllocEngWorkMem(pwrk);
//			if(DLO_SUCCESS!=rtval){
//				return rtval;
//			}else{
//				pwrk->TotalWkmsize = pwrk->dlowkm.lWkMemsize + DLO_RAS_ATTR_SIZE + pwrk->engWkMemsz;				
//			}
//		  }		
//		}while(ret==DLO_NOT_ENOUGH_ENGINEWKMEM);
//		if(ret != DLO_SUCCESS)
//			return ret;
//	}
	ret = ReInitFont(pwrk);
	if(DLO_SUCCESS != ret)
		return ret;

	if(!pwrk->ras_attr){
		return DLO_ENGINEWKMEM_ERR;
	}
	
#ifdef DIGITYPE_STD
	  if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256){
		if(pwrk->fengtype==DLO_ENG_DCWRASTER_MONO)
			bBit = 1;

		ret = pwrk->fengfuncs.getCharbmp( pwrk->ras_attr, ucs, -1, clip.hw.vx, clip.hw.vy, clip.xy.x, clip.xy.y, xbytes, 
									(DT8_uchar*)bmp, NULL, bBit?DLO_LAYOUT_BIT:DLO_LAYOUT_BYTE);
	  }
#endif

#ifdef BDF_RASTER
  if(pwrk->fengtype==DLO_ENG_BDFRASTER){
	  ret = pwrk->fengfuncs.getCharbmp( pwrk->ras_attr, ucs, -1, clip.hw.vx, clip.hw.vy, clip.xy.x, clip.xy.y, xbytes, 
								  (DT8_uchar*)bmp, NULL, DLO_LAYOUT_BIT);
  }
#endif
  
#ifdef DIF_RASTER
  if( pwrk->fengtype==DLO_ENG_DIFRASTER_BIT ||
	  pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE){
	  if(pwrk->fengtype==DLO_ENG_DIFRASTER_BIT)
			bBit = 1;

	  ret = pwrk->fengfuncs.getCharbmp( pwrk->ras_attr, ucs, -1, clip.hw.vx, clip.hw.vy, clip.xy.x, clip.xy.y, xbytes, 
								  (DT8_uchar*)bmp, NULL, bBit?DLO_LAYOUT_BIT:DLO_LAYOUT_BYTE);
  }
#endif

  return ret;
}

/*---------------------------------------------------------------------------*/
DT32_int DLO_GetCharOUL(DLO_Handle hShaper, DT16_ushort ucs, DT32_int gseq2idx, DT_void *path, DT32_long pathbytes, DT32_long *pathsize)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int ret=DLO_SUCCESS;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pwrk)
		return DLO_BAD_HANDLE;

	if(!pwrk->ras_attr){
		return DLO_ENGINEWKMEM_ERR;
	}

#ifdef DIGITYPE_OUL
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
		ret = pwrk->fengfuncs.getCharOul(pwrk->ras_attr, ucs, gseq2idx, pathbytes, path, pathsize);
	}else{
		return DLO_FONTENGINE_NOT_SUPPORT;
	}
#else
	return DLO_FONTENGINE_NOT_SUPPORT;
#endif

  return ret;
}

/*---------------------------------------------------------------------------*/
DT32_int DLO_FastCharOUL(DLO_Handle hShaper, DT16_ushort ucs, DT32_int gseq2idx, DT_void *path, DT32_long pathbytes, DT32_long *pathsize)
{
	pLayWrk pwrk = (pLayWrk) hShaper;
	DT32_int ret=DLO_SUCCESS;

DBG_MSG_SHOW_FUNC_NAME();

//	if(!pwrk)
//		return DLO_BAD_HANDLE;

//	if(!pwrk->ras_attr){
//		return DLO_ENGINEWKMEM_ERR;
//	}

#ifdef DIGITYPE_OUL
	if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
		ret = pwrk->fengfuncs.fastCharOul(pwrk->ras_attr, ucs, gseq2idx, pathbytes, path, pathsize);
	}else{
		return DLO_FONTENGINE_NOT_SUPPORT;
	}
#else
	return DLO_FONTENGINE_NOT_SUPPORT;
#endif

  return ret;
}

/*---------------------------------------------------------------------------*/
//Marked_By_Jacky_20101213: These codes are not used in DigiTypeAPI, marked it.
//#if (1==DLO_OPENVG_ENABLED)
//
///* Distinguish if the (xpos, ypos) inside the specified rect(rt). Its origin(0,0) is left-top. */
//DT32_int isInsideRect(DT16_short xpos, DT16_short ypos, DLO_RECT *rt)
//{
//	DT32_int xin=0, yin=0;
//	DT32_int x0, y0, w, h;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	x0 = rt->xy.x;
//	y0 = rt->xy.y;
//	w  = rt->hw.vx;
//	h  = rt->hw.vy;
//	if(xpos>x0 && xpos<x0+w)
//		xin = 1;
//	if(ypos>y0 && ypos<y0+h)
//		yin = 1;
//	return (xin&yin);
//}
//
//DT32_int AppendPathData(VGPath vgpath, VGfloat szX, VGfloat szY, DT16_short *olbuf, DT32_long olsize, DT32_int method, DLO_RECT *rt, VGfloat ori[2])
//{
//	VGubyte *pathSegs=NULL;
//	VGfloat *pathData=NULL;
//
//	DT16_short *path, *last, op;
//	DT32_int opCnt, xyCnt, opIdx, xyIdx;
//	DT32_int nodraw=0;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	pathSegs = (VGubyte*)DT_malloc(DT_ALLOC_SIZE(olsize*sizeof(VGubyte)/4));	/* Assume there are olsize/4 segs. */
//	if(!pathSegs)
//		return DLO_NOT_ENOUGH_PATHMEM;
//	
//	pathData = (VGfloat*)DT_malloc(DT_ALLOC_SIZE(olsize*sizeof(VGfloat)/2));
//	if(!pathData)
//		return DLO_NOT_ENOUGH_PATHMEM;
//
//    path = olbuf;
//    last = path + olsize;
//
//     while (path < last)
//	 {
//      // Get Contour Path 
//      opCnt = *path++;
//      xyCnt = *path++;
//      
//      pathSegs = (VGubyte*)DT_realloc(pathSegs, DT_ALLOC_SIZE(opCnt*sizeof(VGubyte)));
//      pathData = (VGfloat*)DT_realloc(pathData, DT_ALLOC_SIZE(xyCnt*sizeof(VGfloat)*2));
//
//      // Convert each segment
//      for (opIdx=xyIdx=0; opIdx<opCnt; opIdx++)
//      {
//        op = *path++;
//        switch (op)
//        {
//        case DCWOUL_MOVETO:
//		  if(DLO_AREA_NOT_DRAW==method){
//			nodraw = isInsideRect(*path,*(path+1),rt);
//		  }
//		  if(!nodraw){
//            pathSegs[opIdx] = VG_MOVE_TO_ABS;
//            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / DLO_FONT_EMSIZE;
//            pathData[xyIdx++] = ori[1] + szY - (VGfloat)(*path++) * szY / DLO_FONT_EMSIZE;
//		  }else{
//			//skip the value, not recorded.
//			*path++;
//			*path++;
//		  }
//          break;
//
//        case DCWOUL_LINETO:
//		  if(!nodraw){
//            pathSegs[opIdx] = VG_LINE_TO_ABS;
//            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / DLO_FONT_EMSIZE;
//            pathData[xyIdx++] = ori[1] + szY - (VGfloat)(*path++) * szY / DLO_FONT_EMSIZE;
//		  }else{
//			*path++;
//			*path++;
//		  }
//          break;
//
//        case DCWOUL_BEZIERTO:
//		  if(!nodraw){
//            pathSegs[opIdx] = VG_QUAD_TO_ABS;
//            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / DLO_FONT_EMSIZE;
//            pathData[xyIdx++] = ori[1] + szY - (VGfloat)(*path++) * szY / DLO_FONT_EMSIZE;
//            pathData[xyIdx++] = ori[0] + (VGfloat)(*path++) * szX / DLO_FONT_EMSIZE;
//            pathData[xyIdx++] = ori[1] + szY - (VGfloat)(*path++) * szY / DLO_FONT_EMSIZE;
//		  }else{
//			  *path++;
//			  *path++;
//			  *path++;
//			  *path++;
//		  }
//          break;
//
//        case DCWOUL_CLOSEPATH:
//		  if(!nodraw){
//            pathSegs[opIdx] = VG_CLOSE_PATH;
//            vgAppendPathData(vgpath, opCnt, pathSegs, pathData);
//		  }else{
//			nodraw = 0;
//		  }
//          break;
//        }
//      }
//	}
//	 
//	if (pathSegs) DT_free(pathSegs);
//    if (pathData) DT_free(pathData);
//	return DLO_SUCCESS;
//}
//
//DT_void MakeClearMaskPath(VGPath maskpath, DT_float origin[2], DT32_int width, DT32_int height, VGbitfield paintModes)
//{
//	DT32_int strw=0;			/* stroke width */
////	VGPath maskpath;	/* use a rect path to cover the region glyphs will be drawn. */
//	VGubyte Segs[6]={VG_MOVE_TO_ABS,
//					 VG_LINE_TO_ABS,
//					 VG_LINE_TO_ABS,
//					 VG_LINE_TO_ABS,
//					 VG_LINE_TO_ABS,
//					 VG_CLOSE_PATH};
//	VGfloat Coords_F[10];
//	VGfloat w, h;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	w = (VGfloat)width;
//	h = (VGfloat)height;
//
//	if(paintModes & VG_STROKE_PATH){
//		strw = vgGeti(VG_STROKE_LINE_WIDTH);
//		w += (VGfloat)strw;
//		h += (VGfloat)strw;
//	}
//
//		Coords_F[0] = origin[0];	/* left-bottom (origin) */
//		Coords_F[1] = origin[1];
//		Coords_F[2] = origin[0];	/* left-top */
//		Coords_F[3] = origin[1]+h;
//		Coords_F[4] = origin[0]+w;	/* right-top */
//		Coords_F[5] = origin[1]+h;
//		Coords_F[6] = origin[0]+w;	/* right-bottom */
//		Coords_F[7] = origin[1];
//		Coords_F[8] = origin[0];	/* left-bottom (origin) */
//		Coords_F[9] = origin[1];
//		vgAppendPathData(maskpath, 6, Segs, (VGfloat*)Coords_F);		
//	vgRemovePathCapabilities(maskpath, VG_PATH_CAPABILITY_APPEND_TO);
//}
//

//  DT32_int DLO_ShapeStringVG(DLO_Handle hShaper,
//						DLO_LayBuf *laybuf, 
//                        DT32_int sizeX, DT32_int sizeY, DT_float origin[2],
//                        DT32_uint /*VGbitfield*/ paintModes,
//                        DT32_int /*VGboolean*/ allowAutoHinting)
//{
//	pLayWrk		pwrk = (pLayWrk) hShaper;
//	VGbitfield	paint = paintModes;
//	VGboolean	autohint = (allowAutoHinting)?VG_TRUE:VG_FALSE;
//	VGint		matrixmode, blendmode, fillrule, joinstyle;
//	VGfloat		ori[2]={0.0f, 0.0f};
//	VGfloat		awv[2]={0.0f, 0.0f};
//	VGfloat		szX = (VGfloat)sizeX;
//	VGfloat		szY = (VGfloat)sizeY;
//	
//	VGubyte		*pathSegs=NULL;
//	VGfloat		*pathData=NULL;
//
//	DT32_int rtv, ret=DLO_SUCCESS;
//	DT32_int i, bufread;
//	DT16_short *pathbuf = (DT16_short*) laybuf->olDatabuf;
//	//VGfloat x, y, h, w;
//	DT32_int h, w, stkw;
//	
//DBG_MSG_SHOW_FUNC_NAME();
//
//	if(!pwrk->myvgfont){
//		pwrk->myvgfont = vgCreateFont(laybuf->glyf_cnt);
//		if(pwrk->myvgfont == VG_INVALID_HANDLE)
//		  return DLO_VG_CREATEFONT_ERR;
//	}
//
//	if(!laybuf)
//		return DLO_VG_BAD_LAYBUF;
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
// #ifdef _SPEEDTEST
//	SpeedTestStart("Parse");
// #endif
//	/* Create Path */
//	if(!pwrk->myglyphpath){
//	  pwrk->myglyphpath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 
//							  1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
//	  if(pwrk->myglyphpath == VG_INVALID_HANDLE)
//		return DLO_VG_CREATEPATH_ERR;
//	}else{
//	  vgClearPath(pwrk->myglyphpath,VG_PATH_CAPABILITY_ALL);
//	}
//	ori[0] = origin[0];
//	ori[1] = origin[1];
//	bufread = 0;
//	for(i=0;i<laybuf->glyf_cnt;i++){
//		if(bufread+laybuf->olSizebuf[i] > laybuf->olDatabufSize)
//			break;
//
//		ori[0] = (VGfloat)laybuf->caret_seq[i].oripos.x * szX / DLO_FONT_EMSIZE;
//		ori[1] = 0 - (VGfloat)laybuf->caret_seq[i].oripos.y * szY / DLO_FONT_EMSIZE;
//		if(laybuf->olSizebuf[i]){
//			rtv = AppendPathData(pwrk->myglyphpath,(VGfloat)sizeX,(VGfloat)sizeY,
//								pathbuf+bufread,laybuf->olSizebuf[i],
//								laybuf->caret_seq[i].drawmethod, &laybuf->caret_seq[i].dmrect, ori);
//		}
//		if(rtv!=DLO_SUCCESS) ret = rtv;			
//		bufread += laybuf->olSizebuf[i];
//	}
// #ifdef _SPEEDTEST
//	SpeedTestEnd();
// #endif	
//	
//	if(0==bufread){	/* Nothing in the path, close it. */
// #ifdef _SPEEDTEST
//	printf("No\tNo\tNo");
// #endif
//
//		goto SET_VG_INFO_BACK;
//	}
//	
//	/* Remove this Capability of path will be faster. */
//	vgRemovePathCapabilities(pwrk->myglyphpath, VG_PATH_CAPABILITY_APPEND_TO);
//
//	/* Get advanced width (escapement) */
//	awv[0] = (VGfloat)laybuf->eswidth;
//	awv[1] = (VGfloat)laybuf->esheight;
//
//	ori[0] = 0.0f;
//	ori[1] = 0.0f;
//	/* Set Path */
//	vgSetGlyphToPath(pwrk->myvgfont, (VGuint)DLO_VG_FONTCODE/*0x0E3B*/, pwrk->myglyphpath, VG_TRUE, ori, awv);
//
//	/* Prepare a make for stroke path drawing -- avoid alpha channel problem. */
//	vgSetfv(VG_GLYPH_ORIGIN,2,(VGfloat*)origin);
//#if (DLO_STROKE_BY_MASK==1)
//	if(paint & VG_STROKE_PATH){	/* stroke glyph */
//
// #ifdef _SPEEDTEST
//	SpeedTestStart("Mask");
// #endif
//
//		/* Using mask to avoid the un-expected result while the color's alpha channel isn't 1. */
//		/* Create mytranspath for masking. */
//		if(!pwrk->mytranspath){
//		  pwrk->mytranspath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
//		  if(pwrk->mytranspath == VG_INVALID_HANDLE)
//			return DLO_VG_CREATEPATH_ERR;
//		}else{
//		  vgClearPath(pwrk->mytranspath,VG_PATH_CAPABILITY_ALL);
//		}
//
//		/* Render to mask. */
//		if(!pwrk->mymaskpath){
//		  pwrk->mymaskpath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1, 0, 0, 0, VG_PATH_CAPABILITY_ALL);
//		  if(pwrk->mymaskpath == VG_INVALID_HANDLE)
//			return DLO_VG_CREATEPATH_ERR;
//		}else{
//		  vgClearPath(pwrk->mymaskpath,VG_PATH_CAPABILITY_ALL);
//		}
//		
//		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);			/* Set the matrix mode. */
//		w = DLO_GetStringWidth(hShaper,laybuf,sizeX,sizeY);
//		h = DLO_GetStringHeight(hShaper,laybuf,sizeX,sizeY);
//
//		stkw = vgGeti(VG_STROKE_LINE_WIDTH);							/* Jacky_20100312, new method to set a mask. */
//		vgSeti(VG_MASKING, VG_TRUE);
//		vgMask(VG_INVALID_HANDLE,VG_FILL_MASK,origin[0],origin[1],w+stkw,h+stkw);
//		vgSeti(VG_MASKING, VG_FALSE);
//	
//		vgTranslate(origin[0]/2, origin[1]/2);							/* It have to be so to get the right result. */
//		vgTransformPath(pwrk->mytranspath, pwrk->myglyphpath);			/* transform myglyphpath to mytranspath */
//	
//		vgRenderToMask(pwrk->mytranspath, VG_FILL_PATH, VG_SUBTRACT_MASK);	/* render to mask. */	
//		vgTranslate(-origin[0]/2, -origin[1]/2);						/* Same as above. because origin had been offseted. */
//		//vgDestroyPath(pwrk->mytranspath);									
//		vgSeti(VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE);		/* Set the matrix mode back. */
//
// #ifdef _SPEEDTEST
//	SpeedTestEnd();
//	SpeedTestStart("Stroke");
// #endif
//		/* stroking glyph. */
//		vgSeti(VG_MASKING, VG_TRUE);
//		vgDrawGlyph(pwrk->myvgfont,(VGuint)DLO_VG_FONTCODE/*0x0E3B*/,VG_STROKE_PATH,autohint);
//		vgSeti(VG_MASKING, VG_FALSE);
//
//		/* Clear Mask. */	/* Marked by Jack_20100310 */
//		vgSeti(VG_MASKING, VG_TRUE);									/* Jacky_20100312, fill mask back. */
//		vgMask(VG_INVALID_HANDLE,VG_FILL_MASK,origin[0],origin[1],w+stkw,h+stkw);
//		vgSeti(VG_MASKING, VG_FALSE);
// #ifdef _SPEEDTEST
//	SpeedTestEnd();
//	SpeedTestStart("Fill");
// #endif
//		/* If it need filling... */
//		vgSetfv(VG_GLYPH_ORIGIN, 2, origin);
//		if(paint&VG_FILL_PATH)
//			vgDrawGlyph(pwrk->myvgfont,(VGuint)DLO_VG_FONTCODE/*0x0E3B*/,VG_FILL_PATH,autohint);
// #ifdef _SPEEDTEST
//	SpeedTestEnd();
// #endif
//
//	}else{	/* Fill glyph only. */
// #ifdef _SPEEDTEST
//	printf("No\tNo\t");
//	SpeedTestStart("Fill");
// #endif
//		vgSetfv(VG_GLYPH_ORIGIN, 2, origin);
//		if(paint&VG_FILL_PATH)
//			vgDrawGlyph(pwrk->myvgfont,(VGuint)DLO_VG_FONTCODE/*0x0E3B*/,VG_FILL_PATH,autohint);
//		
// #ifdef _SPEEDTEST
//	SpeedTestEnd();
// #endif
//	}
//
//#else
//	/* stroke */
//	if(paint&VG_STROKE_PATH)
//		vgDrawGlyph(pwrk->myvgfont,(VGuint)DLO_VG_FONTCODE/*0x0E3B*/,VG_STROKE_PATH,autohint);
//
//	/* fill */
//	vgSetfv(VG_GLYPH_ORIGIN, 2, origin);
//	if(paint&VG_FILL_PATH)
//		vgDrawGlyph(pwrk->myvgfont,(VGuint)DLO_VG_FONTCODE/*0x0E3B*/,VG_FILL_PATH,autohint);
//#endif
//	
//	vgClearGlyph(pwrk->myvgfont,(VGuint)DLO_VG_FONTCODE/*0x0E3B*/);
//
//SET_VG_INFO_BACK:
//	// Set the info back
//	vgSeti(VG_MATRIX_MODE, matrixmode);
//	vgSeti(VG_BLEND_MODE, blendmode);
//	vgSeti(VG_FILL_RULE, fillrule);
//	vgSeti(VG_STROKE_JOIN_STYLE, joinstyle);
//
// #ifdef _SPEEDTEST
//	printf("\n");
// #endif
//
//	
//	return ret;
//}
//
//  DT32_int DLO_GetStringWidth(DLO_Handle hShaper,DLO_LayBuf *laybuf, DT32_int sizeX, DT32_int sizeY)
//  {
//	DT32_int dif = DLO_FONT_EMSIZE-1;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	return (laybuf->eswidth*sizeX+dif)/DLO_FONT_EMSIZE;
//
//  }
//
//  DT32_int DLO_GetStringHeight(DLO_Handle hShaper,DLO_LayBuf *laybuf,DT32_int sizeX, DT32_int sizeY)
//  {
//	DT32_int dif = DLO_FONT_EMSIZE-1;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	return (laybuf->esheight*sizeY+dif)/DLO_FONT_EMSIZE;
//  }
//#endif
