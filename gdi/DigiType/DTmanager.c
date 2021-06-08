/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#include "DTmanager.h"
#include "DcwCache.h"

/*--------------------------------------------------------------*/
/* decide the font type by file extension. */
/* Return Value: DT_FontType enum value, DTTypeEnd: error */
DT_FontType getfonttype(DT8_char *file)
{
	DT8_char	*pext;
	DT32_int	nLen=0;

DBG_MSG_SHOW_FUNC_NAME();

	nLen = DT_strlen(file);
	if(nLen<4)
		return DTTypeEnd;

	pext = file + (nLen-4);	// Assuming a fontfile has extension like ".BDF", ".FDL"...
	if(!DT_strncmp(pext,".FDL",4) || !DT_strncmp(pext,".fdl",4)){
		return DTDigiType_FDL;
	}else if(!DT_strncmp(pext,".BDF",4) || !DT_strncmp(pext,".bdf",4)){
		return DTBitmap_BDF;
	}else if(!DT_strncmp(pext,".DIF",4) || !DT_strncmp(pext,".dif",4)){
		return DTIconFont_DIF;
	}else if(!DT_strncmp(pext,".TTF",4) || !DT_strncmp(pext,".ttf",4) ||
			 !DT_strncmp(pext,".OTF",4) || !DT_strncmp(pext,".otf",4) ||
			 !DT_strncmp(pext,".TTC",4) || !DT_strncmp(pext,".ttc",4)){
		return DTTrueType_TTF;
	}

	return DTTypeEnd;
}

/*--------------------------------------------------------------*/
/* decide the font type by fontdata. */
/* Return Value: DT_FontType enum value, DTTypeEnd: error */
DT_FontType getfonttypebydata(DT_FontData *fdata)
{

	if(fdata->nfsize>8 && !DT_strncmp(fdata->fontdata,"FDL Font",8)){	
		return DTDigiType_FDL;
	}else if(fdata->nfsize>8 && !DT_strncmp(fdata->fontdata,"DCW ICON",8)){
		return DTIconFont_DIF;
	}else if(fdata->nfsize>9 && !DT_strncmp(fdata->fontdata,"STARTFONT",9)){
		return DTBitmap_BDF;
	}else{
		/* Other font type, now treat it as unknown. */
		return DTTypeEnd;
	}

	return DTTypeEnd;
}

/*--------------------------------------------------------------*/
DT32_int makeatoi(DT8_char *a, DT32_int nlen)
{
	DT32_int i=0, ret=0, neg=0;

DBG_MSG_SHOW_FUNC_NAME();

	if(a[0] == '-')
	{
		i++;
		neg = 1;
	}// end if

	for(; i < nlen; i++)
	{
		ret *= 10;
		ret += a[i] - '0';
	}// end for

	if(neg)
		ret = 0-ret;
	return ret;
}

/*--------------------------------------------------------------*/
/* the line (from -> (from + (*len)) ) contains carriage-return symbol */
DT8_char *getNextLine( DT8_char *from, DT32_int *len, DT8_char *end )
{
	DT8_char *p=from;

DBG_MSG_SHOW_FUNC_NAME();

		while(p<end)
		{
			if(*p == 0x0D)
			{
				p+=2;
				//if(*p == 0x0A) p++;
				break;
			}/*else if(*p == 0x0A)
			{
				p++;
				break;
			}else if(*p == 0x1A)
				break;*/
			else
			{
				p++;
			}// end if
		}// end while
	*len = (DT32_int) (p - from);
	if(*len>0)
		return from;
	else
		return NULL;
}

/*--------------------------------------------------------------*/
DT32_int getBDFfontsize(DT_FontMgr mgr, DT_Font *font)
{
	DT32_int lnlength=0, idx=0, len=0, sz=0;

#ifdef DT_ENABLE_STDIO
	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)mgr;
	const DT8_char *file = font->fontname;
	DT_FILE *fs;
	//DT8_char ln[256];	/* a temporary buffer to store a line, it might be too small for some case. */
						/* deal this issue if mis-parse occurs.										*/
	DT8_char *ln = pmgrwrk->tempbuf;

DBG_MSG_SHOW_FUNC_NAME();

	if(pmgrwrk->tmpbufsize<256)
		return 0;
	
	fs = DT_fopen(file,"r");

	if(!fs)
		return -1;

	//DT_fseek(fs,0,DT_SEEK_SET);
	while(DT_fgets(ln,256,fs)){
		if(!DT_strncmp(ln,"SIZE ",5)){
		  idx=5;
		  while(ln[idx]!=' ' && idx<256){
			idx++;
		  }
		  len = idx - 5;
		  sz=makeatoi(ln+5,len);
		  break;
		}
	}

	DT_fclose(fs);
	return sz;
#else /*DT_ENABLE_STDIO*/
	DT8_char *from, *end;

DBG_MSG_SHOW_FUNC_NAME();

	if(1==DT_LoadFontData(font,-1)){
		from = font->fontdata;
		end  = from + font->nfsize;
		while(getNextLine(from, &lnlength, end)){
			if(lnlength>=5 && !DT_strncmp(from,"SIZE ",5)){
			  idx=5;
			  while(from[idx]!=' ' && from[idx]!=0x0D){
				idx++;
			  }
			  len = idx - 5;
			  sz=makeatoi(from+5,len);
			  break;
			}

			from += lnlength;
		}
		DT_unLoadFontData(font,-1);
	}else{
		return 0;
	}
	return sz;
#endif/*DT_ENABLE_STDIO*/


}

/*--------------------------------------------------------------*/
DT32_int getDIFfontsize(DT_FontMgr mgr, DT_Font *font)
{
	DT32_int sz=0;

#ifdef DT_ENABLE_STDIO
	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)mgr;
	DT32_int ret=0;
	const DT8_char *file = font->fontname;
	DT_FILE *fs;
	DT8_char *ln = (DT8_char*)pmgrwrk->tempbuf;

DBG_MSG_SHOW_FUNC_NAME();

	if(pmgrwrk->tmpbufsize<32)	/* header is 32 bytes. */
		return 0;

	fs = DT_fopen(file,"rb");

	if(!fs)
		return -1;

	ret = DT_fread( ln, 32, 1, fs );
	sz = (DT32_int)(DT8_uchar)ln[9];	/* Use its Max_H as font size */


	DT_fclose(fs);
	return sz;
#else /*DT_ENABLE_STDIO*/

DBG_MSG_SHOW_FUNC_NAME();

	if(1==DT_LoadFontData(font,-1)){
		sz = font->fontdata[9];
		DT_unLoadFontData(font,-1);
	}else{
		return 0;
	}
	return sz;
#endif/*DT_ENABLE_STDIO*/


}


DT_Font *FMgr_getDTFontByfid(DT_FontMgr_wrk *mgr, DT32_int fid)
{
	pDT_FontMgr_wrk pmgrwrk=mgr;

DBG_MSG_SHOW_FUNC_NAME();

	return &pmgrwrk->dtflist[fid];
}

/* return: <0:error; >=0:fid												*/
/* max gDT_FONTSLIST_MAXCNT fonts in FontManager if DT_CreateFontFromMem().	*/
/* This function should be called by DT_CreateFontFromMem().				*/
DT32_int FMgr_addDTFontData(DT_FontMgr_wrk *mgr, DT_FontData *font)
{
	pDT_FontMgr_wrk pmgrwrk=mgr;
	DT_FontType		type=DTTypeEnd;
	DT32_int		idx;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pmgrwrk){
		return -1;
	}

	// 20111213: Moved here to check filetype first
	type = getfonttypebydata(font);
	if(DTTypeEnd==type){
		return -3;
	}

	/* Check if font had been added?	*//* fontdata address, nfsize, and fonttype need to be match. */
	for(idx=0;idx<pmgrwrk->fcnt;idx++){
		if( pmgrwrk->dtflist[idx].fontdata==font->fontdata && 
			pmgrwrk->dtflist[idx].nfsize==font->nfsize &&
			pmgrwrk->dtflist[idx].type==type){
			return pmgrwrk->dtflist[idx].fid;
		}
	}

	if(pmgrwrk->fcnt>=gDT_FONTSLIST_MAXCNT){
		return -2;	/* because flist has maximum gDT_FONTSLIST_MAXCNT fonts */
					/* Maybe we need to walk through all dtflist to find a room (which refcnt=0?) for the new font. */
	}

	idx = pmgrwrk->fcnt;
	pmgrwrk->dtflist[idx].fid = idx;
	pmgrwrk->dtflist[idx].type= type;
	pmgrwrk->dtflist[idx].ocassion = DT_DEFAULT_OCASSION_ALL;
	pmgrwrk->dtflist[idx].typeface = DT_DEFAULT_TYPEFACE;
	/*DT_memset(pmgrwrk->dtflist[idx].fontname,0,DT_MAX_FILE_PATH);*/
	pmgrwrk->dtflist[idx].fontname[0] = 0;		/* Make sure the first one is NULL. */
	pmgrwrk->dtflist[idx].nlen		= 0;

	pmgrwrk->dtflist[idx].fontdata = font->fontdata;/* font had been loaded, no need to load font data, assign it directly.	*/
	pmgrwrk->dtflist[idx].nfsize   = font->nfsize;	/* font had been loaded, no need to load font data, assign it directly.	*/
	pmgrwrk->dtflist[idx].refcnt   = 0;
	pmgrwrk->dtflist[idx].fontmgr  = (DT_FontMgr)pmgrwrk;	

	pmgrwrk->fcnt += 1;

	return idx;
}

/* return: <0:error; >=0:fid															*/
/* max gDT_FONTSLIST_MAXCNT fonts in FontManager if called DT_InitFontManager() twice.	*/
/* This function should be called by DT_CreateFontFromMem().							*/
DT32_int FMgr_addDTFontFile(DT_FontMgr_wrk *mgr, DT_FontFile *font)
{
	pDT_FontMgr_wrk pmgrwrk=mgr;
	DT_FontType		type=DTTypeEnd;
	DT32_int		idx, nlen;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pmgrwrk){
		return -1;
	}

	nlen = DT_strlen(font->fontfile);
	if(nlen<=0 || nlen>=DT_MAX_FILE_PATH){
		return -4;
	}

	/* Check if font had been added?	*/
	for(idx=0;idx<pmgrwrk->fcnt;idx++){
		if( (pmgrwrk->dtflist[idx].nlen == nlen) &&
			(!DT_strncmp(pmgrwrk->dtflist[idx].fontname,font->fontfile,nlen)) ){
			return pmgrwrk->dtflist[idx].fid;
		}
	}

	if(pmgrwrk->fcnt>=gDT_FONTSLIST_MAXCNT){
		return -2;	/* because flist has maximum gDT_FONTSLIST_MAXCNT fonts */
					/* Maybe we need to walk through all dtflist to find a room (which refcnt=0?) for the new font. */
	}

	type = getfonttype(font->fontfile);
	if(DTTypeEnd==type|| type==DTTrueType_TTF){
		return -3;
	}

	idx = pmgrwrk->fcnt;
	pmgrwrk->dtflist[idx].fid = idx;
	pmgrwrk->dtflist[idx].type= type;
	pmgrwrk->dtflist[idx].ocassion = DT_DEFAULT_OCASSION_ALL;
	pmgrwrk->dtflist[idx].typeface = DT_DEFAULT_TYPEFACE;
	DT_memcpy(pmgrwrk->dtflist[idx].fontname,font->fontfile,nlen);
	pmgrwrk->dtflist[idx].nlen= nlen;

	pmgrwrk->dtflist[idx].fontdata = NULL;	/* not load yet, load while DT_CreateFont()		*/
	pmgrwrk->dtflist[idx].nfsize   = 0;		/* not set yet, set while fontdata is loaded.	*/
	pmgrwrk->dtflist[idx].refcnt   = 0;
	pmgrwrk->dtflist[idx].fontmgr  = (DT_FontMgr)pmgrwrk;	

	pmgrwrk->fcnt += 1;

	return idx;
	
}

DT32_int checkEndianness()
{
	DT32_int val = 1;
	DT8_char *chk = (DT8_char*)&val;

	if (chk[0] == 1)
		return 0;		// little-endian	
	else
		return 1;		// big-endian

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT_FontMgr DT_InitFontManager(DT_FontFile *flist, DT32_int fcnt, DT_CacheSet *cache, DT_void *reserved)
{
	pDT_FontMgr_wrk pmgrwrk=NULL;
	DT32_long		mgrwrksz=0, mgrsz=0;
	DT32_int		i, idx;

DBG_MSG_SHOW_FUNC_NAME();

	/*if(!flist)	
		return NULL;
	*/	/* Marked by Jacky_20100906 to accept DT_InitFontManager(NULL, 0, NULL, NULL);	*/

	if(cache){
		if(cache->type == DTC_TYPE_OVGL3){
			return NULL;	// not accept, because cache can't get current ucs_str from this hManager.
		}
		if(CalculateCacheMem(cache)<0){
			return NULL;
		}
	}

	/* dtflist can contain gDT_FONTSLIST_MAXCNT fonts.	*/
	if(fcnt<gDT_FONTSLIST_MAXCNT){
		mgrsz = (sizeof(DT_FontMgr_wrk) + gDT_FONTSLIST_MAXCNT*sizeof(DT_Font) + 3)/4*4;
	}else{
		mgrsz = (sizeof(DT_FontMgr_wrk) + fcnt*sizeof(DT_Font) + 3)/4*4;
	}
	mgrwrksz = mgrsz + gDT_TEMP_BUFFER_SIZE;
	pmgrwrk = (pDT_FontMgr_wrk) DT_malloc(DT_ALLOC_SIZE(mgrwrksz));
	if(!pmgrwrk){
		return NULL;
	}

	DT_memset(pmgrwrk,0,DT_ALLOC_SIZE(mgrwrksz));		//DT_memset(pmgrwrk,0,mgrwrksz);

	pmgrwrk->dtflist = (DT_Font*) ((DT8_char*)pmgrwrk + sizeof(DT_FontMgr_wrk));
	pmgrwrk->totalsize = (DT32_int)DT_ALLOC_SIZE(mgrwrksz);		//mgrwrksz;
	pmgrwrk->tempbuf = (DT8_char*) pmgrwrk + mgrsz;
	pmgrwrk->tmpbufsize=gDT_TEMP_BUFFER_SIZE;

	/* InitCache and prepare its requirements */
	if(cache){
		DT_memcpy(&pmgrwrk->cacheset,cache,sizeof(DT_CacheSet));
		CoordinateCacheMem(pmgrwrk, NULL, &pmgrwrk->cacheset, &pmgrwrk->cachearr);
	}else{
		pmgrwrk->cacheset.cachemem = NULL;
		pmgrwrk->cacheset.cachesize= 0;
		pmgrwrk->cachearr.CacheSet = NULL;
		pmgrwrk->cachearr.Init_FontCache = 0;
	}

	/* Parse each font file. */
	pmgrwrk->fcnt = idx = 0;
	for(i=0;i<fcnt;i++){				
		idx = FMgr_addDTFontFile(pmgrwrk,&flist[i]);
		if(idx<0){
			continue;
		}else{
			/* Nothing to do. */
		}
	}

	return (DT_FontMgr)pmgrwrk;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT_FontMgr DT_InitDigiType(DT_CacheSet *cache, DT_void *reserved)
{
DBG_MSG_SHOW_FUNC_NAME();
	
	gDT_Endianness = checkEndianness();
	return DT_InitFontManager(NULL, 0, cache, reserved);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT32_int DT_unInitFontManager(DT_FontMgr mgr)
{
	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)mgr;

DBG_MSG_SHOW_FUNC_NAME();

	if(!pmgrwrk)
		return DT_BAD_FONTMGR_HANDLE;

	if(pmgrwrk){
		DT_free(pmgrwrk);
		pmgrwrk = NULL;
	}

// 	FMgr_set_gFontManager(NULL);
	return DT_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
DT32_int DT_unInitDigiType(DT_FontMgr mgr)
{
DBG_MSG_SHOW_FUNC_NAME();
STACK_SHOW_ESTIMATE_VALUE();

	return DT_unInitFontManager(mgr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DT32_int DT_QueryFont(DT_FontMgr mgr, DT_FontDemandAttr *demand, DT_Font fontslist[DT_FONTSLIST_MAXCNT], DT32_int *ncnt)
//{
//	pDT_FontMgr_wrk pmgrwrk = (pDT_FontMgr_wrk)mgr;
//	DT32_int i, idx, sz;
//
//DBG_MSG_SHOW_FUNC_NAME();
//	
//	if(!pmgrwrk)
//		return DT_BAD_FONTMGR_HANDLE;
//
//	/* Use a for loop to decide which fonts is suitable. */
//	idx = 0;
//	for(i=0;i<pmgrwrk->fcnt;i++){
//		/* Now only support BDF, FDL, DIF fonts.					*/
//		/* If you want to support TrueType font, please modify it	*/
//		if( demand->type!=DTDigiType_FDL && demand->type!=DTBitmap_BDF && demand->type!=DTIconFont_DIF &&
//			demand->type!=DTTypeEnd)	/* DTTypeEnd means don't care type */
//			continue;
//
//		/* Check Font file type, such as BDF, FDL, TTF...	*/
//		/* DTTypeEnd stands for every type, not specified	*/
//		if(demand->type!=DTTypeEnd){
//		  if( pmgrwrk->dtflist[i].type!=demand->type){
//			continue;
//		  }
//		}
//
//		/* BDF isn't a scalable font.				*/
//		/* 0: means sizex or sizey not specified.	*/
//		if(pmgrwrk->dtflist[i].type==DTBitmap_BDF){
//			sz = getBDFfontsize(mgr, &pmgrwrk->dtflist[i]);
//			if(demand->sizex!=sz && demand->sizex!=0)
//				continue;
//			if(demand->sizey!=sz && demand->sizey!=0)
//				continue;
//		}else if((pmgrwrk->dtflist[i].type==DTIconFont_DIF)){
//			sz = getDIFfontsize(mgr, &pmgrwrk->dtflist[i]);
//			if(demand->sizex!=sz && demand->sizex!=0)
//				continue;
//			if(demand->sizey!=sz && demand->sizey!=0)
//				continue;
//		}else{	/* others: check if it's valid */
//			if( demand->sizex>gDT_FONT_MAXSIZE || demand->sizey>gDT_FONT_MAXSIZE ||
//				demand->sizex<0 || demand->sizey<0){
//				continue;
//			}
//		}
//
//		/* BDF supports monochrome only.*/
//		/* 0: means every mode is OK.	*/
//		if(pmgrwrk->dtflist[i].type==DTBitmap_BDF){
//			if(demand->mode!=DT_MONOCHROME_MODE && demand->mode!=0)
//				continue;
//		}
//	
//		if(idx<DT_FONTSLIST_MAXCNT){
//			DT_memcpy(&fontslist[idx],&pmgrwrk->dtflist[i],sizeof(DT_Font));
//			idx++;
//		}
//	}
//
//	/* Maybe it should return the default font (FONT_ID=0) if idx=0. */	
//	*ncnt = idx;
//	return idx;
//}
