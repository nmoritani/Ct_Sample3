#include "ovgDcwApi.h"
#include "ovgDcw.h"

#if _DCW_OVG_DEC_STROKE
	static DT32_int  OULDs_SetDsData(pODcwWrk wrk, DT8_char *dsdata);
	static DT32_int  OULDs_LoadData(pODcwWrk wrk, DT32_int fidx, DT32_int decstr);
	static DT32_int  OULDs_Find(pODcwWrk wrk);
#endif

/* Font Data */
#ifndef OULFD_READINTBYDATA1
#define OULFD_READINTBYDATA1(fontdata, ofs)		( (fontdata)[(ofs)] )		// Not used
#endif
#ifndef OULFD_READINTBYDATA2
#define OULFD_READINTBYDATA2(fontdata,ofs)	( (DT32_long)(((DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8) | (DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)])) )
#endif
#ifndef OULFD_READINTBYDATA4
#define OULFD_READINTBYDATA4(fontdata,ofs) ( (DT32_long)(((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+3]) << 24) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+2]) << 16) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8)  | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)]))) )
#endif
static DT32_long OULFD_ReadInt(pODcwWrk wrk, DT32_long ofs, DT32_int size);
static DT32_long OULFD_ReadFontData(pODcwWrk wrk, DT32_int size);

static DT32_int  OULFD_LoadStrokeData(pODcwWrk wrk, DT32_int strid, DT32_int *flag);
static DT32_int  OULFD_LoadRadData(pODcwWrk wrk, DT32_int radid, OTFDLRadParam *rad);
static DT_void	 OULFD_SetPlane(pODcwWrk wrk, DT32_int plane);
static DT32_int  OULFD_SearchCMap(pODcwWrk wrk, DT32_int fontidx, DT32_int *gidx);
static DT32_int  OULFD_SearchPage(pODcwWrk wrk, DT32_int fontidx, DT32_int *gidx);
static DT32_int  OULFD_LoadFontData(pODcwWrk wrk, DT32_long fontidx, DT16_short *x0, DT16_short *aw, DT16_short *y0, DT16_short *ah);

static DT_void	 OULFD_ModifyRadData(pODcwWrk wrk, OTFDLRadParam *rad);

/* Drawing */
static DT32_int  OULFD_DoDraw(pODcwWrk wrk, OTFDLRadParam *rad, DT32_int inrad);

DT_void SetDcwOulwrk(pODcwWrk wrk, DT8_char *fontdata)
{
  DT32_long ofs;
  DT32_int i;

  /* Setup Font Data */
  wrk->fd = (DT8_BYTE*)fontdata;

  for (i=0; i<8; i++)
    wrk->fdl.defval[i] = (DT16_WORD)OULFD_READINTBYDATA2(wrk->fd, OFD_DEFVAL+i*2/*, 2*/);

  wrk->strcnt = OULFD_READINTBYDATA2(wrk->fd, OFD_STRCNT/*, 2*/);
  wrk->radcnt = OULFD_READINTBYDATA2(wrk->fd, OFD_RADCNT/*, 2*/);
  wrk->foncnt = OULFD_READINTBYDATA2(wrk->fd, OFD_FONCNT/*, 2*/);
  wrk->strtab = OULFD_READINTBYDATA4(wrk->fd, OFD_STRTAB/*, 4*/);
  wrk->strofs = OULFD_READINTBYDATA4(wrk->fd, OFD_STROFS/*, 4*/);
  wrk->radtab = OULFD_READINTBYDATA4(wrk->fd, OFD_RADTAB/*, 4*/);
  wrk->radofs = OULFD_READINTBYDATA4(wrk->fd, OFD_RADOFS/*, 4*/);
  wrk->fontab = OULFD_READINTBYDATA4(wrk->fd, OFD_FONTAB/*, 4*/);
  wrk->fonofs = OULFD_READINTBYDATA4(wrk->fd, OFD_FONOFS/*, 4*/);
  wrk->ctmode = OULFD_READINTBYDATA2(wrk->fd, OFD_CTMODE/*, 2*/);
  wrk->version= OULFD_READINTBYDATA2(wrk->fd, OFD_VERSION/*, 2*/);

#if _DCW_OVG_DEC_STROKE
	if(OULFD_READINTBYDATA4(wrk->fd, OFD_DECSTR/*, 4*/) == OFD_DSTR_IDENT){
		wrk->decstr = OULFD_READINTBYDATA4(wrk->fd, OFD_DECSTR+4/*, 4*/);	// OFD_DECSTR
		OULDs_SetDsData(wrk, wrk->fd + wrk->decstr);
	}else{
		wrk->decstr = 0;
		OULDs_SetDsData(wrk, NULL);
	}
#endif

  ofs = wrk->fontab;
  if (wrk->version == 0x101)
  {
  	wrk->foncnt  = OULFD_READINTBYDATA4(wrk->fd, ofs/*, 4*/);
  	wrk->fonloc  = OULFD_READINTBYDATA4(wrk->fd, ofs+4/*, 4*/) + wrk->fontab;
  	wrk->fonmap  = (DT16_WORD)OULFD_READINTBYDATA2(wrk->fd, ofs+8/*, 2*/);
  	wrk->planeno = (DT16_WORD)OULFD_READINTBYDATA2(wrk->fd, ofs+10/*, 2*/);
    wrk->planes  = ofs + 12;
    wrk->plane   = -1;
  }
  else
  {
  	wrk->fonmap  = 0xffff;

  	if (wrk->foncnt == 0)
	  {
  		wrk->foncnt = OULFD_READINTBYDATA4(wrk->fd, ofs/*, 4*/);
    	wrk->fonloc = ofs + 4;
	  }
    else
    	wrk->fonloc = ofs;
  }
}

/*---------------------------------------------------------------------------*/
DCWOUL_Handle DCWOUL_Create(DT8_char *fontdata, DT32_long WkMemsz, DT_void *WkMem)
{
  pODcwWrk wrk;/*pODcwWrk wrk = (pODcwWrk)DT_malloc(sizeof(ODcwWrk));*/

  /* Modified by Jacky_20100325 for not allocate working memory inside library. */
  if(WkMemsz<(DT32_long)sizeof(ODcwWrk))	return NULL;
  wrk = (pODcwWrk)WkMem;
  if (!wrk) return NULL;

  SetDcwOulwrk(wrk, fontdata);

  return (DCWOUL_Handle)wrk;
}
/*---------------------------------------------------------------------------*/
DT32_int DCWOUL_Destroy(DCWOUL_Handle hnd)
{
	/* Modified by Jacky_20100325 for not allocate working memory inside library. */
//  pODcwWrk wrk = hnd;
//  if (wrk) 
//  {
//    DT_free(wrk);
//    return DCWOUL_SUCCESS;
//  }
//  else
//    return DCWOUL_BAD_HANDLE;
	return DCWOUL_SUCCESS;
}
/*---------------------------------------------------------------------------*/
// fontdata can be NULL
DT32_int DCWOUL_Outline(DCWOUL_Handle hnd, DCWOUL_OutlineData *outline, DT8_char *fontdata)
{
  pODcwWrk wrk = (pODcwWrk)hnd;
  DT16_short x0, aw, y0, ah;
  DT32_int ret;

  if (!wrk) return DCWOUL_BAD_HANDLE;

  if(fontdata && !((DT8_uchar*)fontdata == wrk->fd))
	  SetDcwOulwrk(wrk,fontdata);		// Reset wrk when fontdata isn't the same.
										// the pointer of hnd and wrk won't be changed.

  wrk->fdl.wrk  = wrk;

  /* Setup Vertical Writing */
  wrk->vert = 0;
  wrk->fdl.rot  = 0;
  if (outline->vert)
  {
    //if (outline->fontidx < 256)
	if(DT_isCodeRotate90_WhenVert((DT16_ushort)outline->fontidx,NULL))	// Modified by Jacky_20110324
      wrk->fdl.rot = 1;
    else
      wrk->vert = 1;
  }

  /* Setup Path buffer */
  wrk->fdl.path     = (DT16_short*)outline->path;
  wrk->fdl.pathmax  = outline->pathmax;
  wrk->fdl.pathsize = 0;

  /* Load font data */
  if (!OULFD_LoadFontData(wrk, outline->fontidx, &x0, &aw, &y0, &ah))
    return DCWOUL_EMPTY_FONT;

#if _DCW_OVG_DEC_STROKE
	/* Load Decrease Stroke Data of Font */
    wrk->sizexy = outline->sizexy;
	OULDs_LoadData(wrk, outline->fontidx, wrk->decstr);
#endif

  if (x0 != 0) x0 = (DT16_short)(((DT32_long)x0 * DCWOUL_FDL_FONT_EM) / 1000);
  if (y0 != 0) y0 = (DT16_short)(((DT32_long)y0 * DCWOUL_FDL_FONT_EM) / 1000);

  /* Setup font origin */
  wrk->fdl.x0	= x0;
  wrk->fdl.y0	= y0;
  wrk->fdl.shiftx = 0;
  wrk->fdl.shifty = 0;

  /* Draw font */
  if (wrk->datacnt> 0)
  {
    ret = OULFD_DoDraw(wrk, NULL, 0);

    if (ret == DCWOUL_SUCCESS)
    {
      outline->pathsize = wrk->fdl.pathsize;
      if (outline->pathsize > outline->pathmax)
        ret = DCWOUL_NOT_ENOUGH_PATHMEM;
    }
	}
  else
  {
  	ret = DCWOUL_EMPTY_FONT;
  }

  return ret;
}
/*---------------------------------------------------------------------------*/
DT32_int DCWOUL_GetAw(DCWOUL_Handle hnd, DT32_long fontidx, DT32_int vert, DT8_char *fontdata, DT16_short *ltx, DT16_short *paw1000)
{
  pODcwWrk wrk = (pODcwWrk)hnd;
  DT16_short x0, aw, y0, ah, wid;

  if (!wrk) return DCWOUL_BAD_HANDLE;

  if(fontdata && !((DT8_uchar*)fontdata == wrk->fd))
	  SetDcwOulwrk(wrk,fontdata);		// Reset wrk when fontdata isn't the same.
										// the pointer of hnd and wrk won't be changed.

  //wrk->vert = vert && fontidx >= 256;
  wrk->vert = vert && !DT_isCodeRotate90_WhenVert((DT16_ushort)fontidx,NULL);	// Modified by Jacky_20110324

  /* Load font data */
  if(ltx)
	*ltx = 0;
  if(paw1000)
	*paw1000 = 0;
  if (OULFD_LoadFontData(wrk, fontidx, &x0, &aw, &y0, &ah))
  {
    if (!wrk->vert)
    {	/* Horz. Writing */
		if(ltx)
			*ltx = x0;
		if(paw1000)
			*paw1000 = aw;

		// 2012-03-05: check if it required? Attemption: same as DcwRaster does!
		//if(x0 < 0){
		//	aw += x0;
		//}

		wid = (DT16_short) DCWOUL_CALC_AW_AH(aw);
//	  if (aw == 0){
//        wid = DCWOUL_FDL_FONT_EM;
//	  }else{
//        //wid = (DT16_short)(((DT32_long)aw * DCWOUL_FDL_FONT_EM + 999) / 1000);	//Marked_By_Jacky_20101210
//		wid = (DT16_short)DCWOUL_CALC_HORIZ_AW(aw);
//	  }
		// deal ltx, lty when not vert only, because DcwRaster's DCW_GetAw() compensate here only, too.
    }
    else
    { /* Vert. Writing */
		wid = (DT16_short) DCWOUL_CALC_AW_AH(ah);
//      if (ah == 0)
//        wid = DCWOUL_FDL_FONT_EM;
//      else
//        wid = (DT16_short)(((DT32_long)ah * DCWOUL_FDL_FONT_EM + 999) / 1000);
    }

    return wid;
  }
  else
    return DCWOUL_EMPTY_FONT;
}
/*---------------------------------------------------------------------------*/
DT32_int DCWOUL_GetFontInfo(DT8_char *fontdata, DCWOUL_FontInfo *info)
{
  DT8_BYTE *p;
  DT16_WORD b1, b2;
  DT32_long l1, l2, l3, l4, pos;

  p = (DT8_BYTE*)(fontdata + OFD_FONCNT);
  b1 = *p++;
  b2 = *p;
  info->fontcnt = b1 + (b2 << 8);

  if (info->fontcnt == 0)
  {
	  p = (DT8_BYTE*)(fontdata + OFD_FONTAB);
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

  p = (DT8_BYTE*)(fontdata + OFD_CTMODE);
  b1 = *p++;
  b2 = *p;
  info->ctmode = b1 + (b2 << 8);

  p = (DT8_BYTE*)(fontdata + OFD_VERSION);
  b1 = *p++;
  b2 = *p;
  info->version = b1 + (b2 << 8);

  return 1;
}
/*---------------------------------------------------------------------------*/
DT32_int DCWOUL_EstimateWkMem()
{
	return (DT32_int) sizeof(ODcwWrk);
}
/*---------------------------------------------------------------------------*/
DT32_long OULFD_ReadInt(pODcwWrk wrk, DT32_long ofs, DT32_int size)
{
	DT8_BYTE *p;
	DT32_long val;
	DT32_int i;

DBG_MSG_SHOW_FUNC_NAME();

	p = wrk->fd + ofs + size-1;

	val = *p--;
	for(i=1; i < size; i++, p--)
	{
		val <<= 8;
		val |= *p;
	}

  return val;
}
/*---------------------------------------------------------------------------*/
//DT8_BYTE OULFD_ReadStrByte(pODcwWrk wrk)
//{
//  DT8_BYTE val = *((DT8_BYTE*)(wrk->fd + wrk->fdl.sdataofs));
//
//  wrk->fdl.sdataofs ++;
//  wrk->fdl.sdatacnt --;
//
//  return val;
//}
/*---------------------------------------------------------------------------*/
DT16_short OULFD_ReadStrShort(pODcwWrk wrk)
{
  DT8_BYTE *p = wrk->fd + wrk->fdl.sdataofs;
  DT16_WORD b1, b2;

  b1 = *p++;
  b2 = *p;

  wrk->fdl.sdataofs += 2;
  wrk->fdl.sdatacnt -= 2;

  return (DT16_short)(b1 + (b2 << 8));
}
/*---------------------------------------------------------------------------*/
DT32_long OULFD_ReadFontData(pODcwWrk wrk, DT32_int size)
{
  DT32_int val;

  if (wrk->inrad)
  {
    val = OULFD_ReadInt(wrk, wrk->rdataofs, size);

    wrk->rdataofs += size;
    wrk->rdatacnt -= size;
  }
  else
  {
    val = OULFD_ReadInt(wrk, wrk->dataofs, size);

    wrk->dataofs += size;
    wrk->datacnt -= size;
  }

  return val;
}
/*---------------------------------------------------------------------------*/
DT32_int OULFD_LoadStrokeData(pODcwWrk wrk, DT32_int strid, DT32_int *flag)
{
  DT32_long len, ofs, addr1, addr2;
  DT32_int  cnt, param;

  if (strid < wrk->strcnt)
  {
    /* Read stroke position & size */
	len = (wrk->version == 0x102) ? 3 : 2;
	ofs = wrk->strtab + strid*len;
	addr1 = OULFD_ReadInt(wrk, ofs, len);
	addr2 = OULFD_ReadInt(wrk, ofs+len, len);
	cnt = addr2 - addr1;

    if (cnt > 0)
    {
      ofs = wrk->strofs + addr1;

      /* Read stroke parameter */
      param = OULFD_READINTBYDATA1(wrk->fd, ofs/*, 1*/);
      wrk->fdl.relno = (param >> 4) & 0x0f;
      wrk->fdl.valno = param & 0x0f;

      *flag = OULFD_READINTBYDATA1(wrk->fd, ofs+1/*, 1*/);

      /* stroke data */
      wrk->fdl.sdatacnt = cnt - 2;
      wrk->fdl.sdataofs = ofs + 2;

      return 1;
    }
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int OULFD_LoadRadData(pODcwWrk wrk, DT32_int radid, OTFDLRadParam *rad)
{
  DT32_long ofs, addr1, addr2;
  DT32_int  cnt, param;

  if (radid < wrk->radcnt)
  {
    /* Read radical position & size */
    /* 2007-12-12 Radical : 3 Bytes Table */
    ofs = wrk->radtab + radid*3;
    addr1 = OULFD_ReadInt(wrk, ofs,   3);
    addr2 = OULFD_ReadInt(wrk, ofs+3, 3);
    cnt = addr2 - addr1;

    if (cnt > 0)
    {
      /* Read radical parameter */
      ofs = wrk->radofs + addr1;
      param = OULFD_READINTBYDATA4(wrk->fd, ofs/*, 4*/);

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
DT_void OULFD_SetPlane(pODcwWrk wrk, DT32_int plane)
{
	DT32_long start, ofs;

	if (plane != wrk->plane)
  {
  	wrk->plane = plane;

    /* Read Plane Table */
    ofs = wrk->planes + plane * 8;
    start = OULFD_READINTBYDATA4(wrk->fd, ofs/*, 4*/);
    wrk->gstart = OULFD_READINTBYDATA4(wrk->fd, ofs+4/*, 4*/);

  	ofs = wrk->fontab + start;
    if (wrk->fonmap == 0)
	  {	/* Read Segment Table */
			wrk->segno   	= (DT16_WORD)OULFD_READINTBYDATA2(wrk->fd, ofs/*, 2*/);
    	wrk->segs			= ofs + 2;
  	}
  	else if (wrk->fonmap == 1)
    {	/* Read Page Table */
    	wrk->pagebits	= (DT16_WORD)OULFD_READINTBYDATA2(wrk->fd, ofs/*, 2*/);
	    wrk->pageno 	= (DT16_WORD)OULFD_READINTBYDATA2(wrk->fd, ofs+2/*, 2*/);
    	wrk->pages 		= ofs + 4;

	    wrk->pagemask = (1 << wrk->pagebits) - 1;
	  }
  }
}
/*---------------------------------------------------------------------------*/
DT32_int OULFD_SearchCMap(pODcwWrk wrk, DT32_int fontidx, DT32_int *gidx)
{
	DT32_int base = wrk->segs;
	DT32_int cnt  = wrk->segno;
  DT32_int width = 6;
  DT32_int mid, probe, start, last;

  while (cnt > 0)
  {
    mid = cnt >> 1;
    probe = base + mid * width;
		start = OULFD_READINTBYDATA2(wrk->fd, probe/*, 2*/);
		last  = OULFD_READINTBYDATA2(wrk->fd, probe+2/*, 2*/);

    if (fontidx >= start && fontidx <= last)
    {
			*gidx = wrk->gstart + OULFD_READINTBYDATA2(wrk->fd, probe+4/*, 2*/) + (fontidx - start);
    	return 1;
  	}
    else if (fontidx < start)
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
DT32_int OULFD_SearchPage(pODcwWrk wrk, DT32_int fontidx, DT32_int *gidx)
{
  DT32_int pageidx = fontidx >> wrk->pagebits;
  DT32_int ofs = wrk->pages + pageidx * 2;
	DT32_int start = OULFD_READINTBYDATA2(wrk->fd, ofs/*, 2*/);

  if (start != 0xFFFF)
  {
  	*gidx = wrk->gstart + start + (fontidx & wrk->pagemask);
    return 1;
  }
	else
  	return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int OULFD_LoadFontData(pODcwWrk wrk, DT32_long fontidx, DT16_short *x0, DT16_short *aw, DT16_short *y0, DT16_short *ah)
{
  DT32_long ofs, addr1, addr2;
  DT32_int  flag, total, fcnt, fcnt2;
  DT32_int  vert;// = (wrk->vert) && (fontidx>=256);
  DT32_int  plane, fidx2, gidx, cmap;

  if (fontidx >= wrk->foncnt) return 0;

  vert = (wrk->vert) && !DT_isCodeRotate90_WhenVert((DT16_ushort)fontidx,NULL);	// Modified by Jacky_20110324

  /* Read font location & size */
  if (wrk->version == 0)
  {
    ofs = wrk->fonloc + fontidx * 3;
    addr1 = OULFD_ReadInt(wrk, ofs,   3);
    addr2 = OULFD_ReadInt(wrk, ofs+3, 3);
    flag = 0;
    cmap = 0;
  }
  else if ((wrk->version == 0x100) || (wrk->version == 0x102))
  {
    /* Get Location & Flag */
    ofs = wrk->fonloc + fontidx * 4;
    addr1 = OULFD_READINTBYDATA4(wrk->fd, ofs/*,   4*/);
    addr2 = OULFD_READINTBYDATA4(wrk->fd, ofs+4/*, 4*/);

    flag = addr1 >> 24;
    addr1 &= 0x0ffffff;
    addr2 &= 0x0ffffff;
    cmap = 0;
  }
  else if (wrk->version == 0x101)
  {
    /* Get Glyph Index */
    plane = fontidx >> 16;
    fidx2 = fontidx & 0x0FFFF;
    OULFD_SetPlane(wrk, plane);

    if (wrk->fonmap == 0)
    {
      if ( !OULFD_SearchCMap(wrk, fidx2, &gidx) ) return 0;
    }
    else
    {
      if ( !OULFD_SearchPage(wrk, fidx2, &gidx) ) return 0;
    }

    /* Get Location & Flag */
    ofs = wrk->fonloc + gidx * 3;
    addr1 = OULFD_ReadInt(wrk, ofs,   3);
    addr2 = OULFD_ReadInt(wrk, ofs+3, 3);

    cmap = 1;
  }
  else
    return 0;

  total = addr2 - addr1;
  if (total == 0) return 0;

  //*x0 = *aw = *y0 = *ah = 0;
  *x0 = *y0 = 0;
  *aw = *ah = 1000;

  ofs = wrk->fonofs + addr1;

  /* Read Flag */
  if (cmap)
  {
    flag = OULFD_READINTBYDATA1(wrk->fd, ofs/*, 1*/);
    ofs++;
    total--;
    if (total == 0) return 0;
  }

  /* Horz. Metric */
  if (flag & OFD_FLAG_HMTX)
  {
    if (!vert)
    {
      /*ofs = wrk->fonofs + addr1;*/
      *x0 = (DT16_short)OULFD_READINTBYDATA2(wrk->fd, ofs/*, 2*/);
      *aw = (DT16_short)OULFD_READINTBYDATA2(wrk->fd, ofs+2/*, 2*/);
    }
    total -= 4;
    ofs += 4;
  }

  /* Vert. Metric */
  if (flag & OFD_FLAG_VMTX)
  {
    if (vert)
    {
      /*ofs = wrk->fonofs + addr1;*/
      *y0 = (DT16_short)OULFD_READINTBYDATA2(wrk->fd, ofs/*, 2*/);
      *ah = (DT16_short)OULFD_READINTBYDATA2(wrk->fd, ofs+2/*, 2*/);
    }
    total -= 4;
    ofs += 4;
  }

  /* Font Data Count */
  if (flag != 0)
  {
    fcnt = OULFD_READINTBYDATA2(wrk->fd, ofs/*, 2*/);
    total -= fcnt;
    ofs += 2;

    /* Get Vertical Writing Font Data */
    if (vert && (flag & OFD_FLAG_VERT) && total>0)
    {
      fcnt2 = OULFD_READINTBYDATA2(wrk->fd, ofs+fcnt/*, 2*/);
      if (fcnt2 > 0)
      {
        ofs += fcnt + 2;
        fcnt = fcnt2;
      }
    }
  }
  else
    fcnt = total;

  /* Font data */
  wrk->datacnt = fcnt;
  wrk->dataofs = ofs;

  /*wrk->fdl.vert = wrk->attr.vert;*/
  /*wrk->fdl.rot  = wrk->attr.vert && (fontidx<256);*/
  /*wrk->fdl.rot  = wrk->attr.vert && DT_isCodeRotate90_WhenVert((DT16_ushort)fontidx,NULL);*/

  return 1;
}
/*---------------------------------------------------------------------------*/
DT32_int OULFD_DoDraw(pODcwWrk wrk, OTFDLRadParam *rad, DT32_int inrad)
{
  DT32_int strid, radid, relflag;
  OTFDLRadParam r2;
  DT16_WORD mask;
  DT32_int done, cnt, ret, i;
#if _DCW_OVG_DEC_STROKE
	DT32_int doit;
#endif

  wrk->inrad = inrad;
  ret = DCWOUL_SUCCESS;

#if _DCW_OVG_DEC_STROKE
	if(!inrad)
		wrk->DsPartIdx = 0;
#endif

  /* 2007-12-12 Radical :
       Check wrk->rdatacnt <= 0 inside radical
  */
  /*  while (wrk->datacnt > 0 && (ret == DCWOUL_SUCCESS))  */
  while (ret == DCWOUL_SUCCESS)
  {
    done = (inrad) ? wrk->rdatacnt <= 0 : wrk->datacnt <= 0;
    if (done) break;

    strid = OULFD_ReadFontData(wrk, 1);

    if (strid == 0xFA)
    { /* Symbol */
      wrk->fdl.relno = 0;

      wrk->fdl.valno = OULFD_ReadFontData(wrk, 1);
      if ((wrk->fdl.valno % 2)==1) wrk->fdl.valno++;
      for (i=0; i<wrk->fdl.valno; i++)
        wrk->fdl.val[i] = (DT8_BYTE)OULFD_ReadFontData(wrk, 1);

      wrk->fdl.sdatacnt = OULFD_ReadFontData(wrk, 2);

      /* 2007-12-12 Radical :
           1. Get Data from rdataofs/rdatacnt in radical
           2. Shift Symbol (fdl.shiftx/shifty)
      */
      if (!inrad)
      {
        wrk->fdl.sdataofs = wrk->dataofs;

        wrk->datacnt -= wrk->fdl.sdatacnt;
        wrk->dataofs += wrk->fdl.sdatacnt;
      }
      else
      {
        wrk->fdl.sdataofs = wrk->rdataofs;

        wrk->rdatacnt -= wrk->fdl.sdatacnt;
        wrk->rdataofs += wrk->fdl.sdatacnt;

        if (rad)
        {
          wrk->fdl.shiftx = (rad->destx - rad->srcx) * wrk->fdl.xsize / 256;
          wrk->fdl.shifty = (rad->desty - rad->srcy) * wrk->fdl.ysize / 256;
        }
      }

      /* Draw symbol / Get symbol outline */
      ret = OFDL_GetFont(&wrk->fdl);

      /* 2007-12-12 Radical (Reset fdl.shiftx/shifty) */
      if (inrad && rad)
      {
        wrk->fdl.shiftx = 0;
        wrk->fdl.shifty = 0;
      }
    }
    else if (strid == 0xFC)
    { /* Radical */
      /* 2007-12-12 Radical (radid is 2 byte) */
      /* radid = OULFD_ReadFontData(wrk, 1); */
      radid = OULFD_ReadFontData(wrk, 2);

      /* Load radical data */
      OULFD_LoadRadData(wrk, radid, &r2);

      /* Radical parameter */
      r2.flag = (DT8_BYTE)OULFD_ReadFontData(wrk, 1);
      if (r2.flag != 0)
      {
        /* Setup radical parameter */
        if ((r2.flag & OFD_RAD_SCALEX) != 0)
        {
          r2.destx = (DT16_short)OULFD_ReadFontData(wrk, 1);
          r2.destw = (DT16_short)OULFD_ReadFontData(wrk, 1);
        }

        if ((r2.flag & OFD_RAD_SCALEY) != 0)
        {
          r2.desty = (DT16_short)OULFD_ReadFontData(wrk, 1);
          r2.desth = (DT16_short)OULFD_ReadFontData(wrk, 1);
        }

        if ((r2.flag & OFD_RAD_WID) != 0)
        {
          r2.wid = (DT16_short)OULFD_ReadFontData(wrk, 1);
        }

        /* Draw radical */
        ret = OULFD_DoDraw(wrk, &r2, 1);
      }
      else
      {
        /* Draw radical */
        ret = OULFD_DoDraw(wrk, NULL, 1);
      }
#if _DCW_OVG_DEC_STROKE
	  wrk->DsPartIdx--;
#endif
    }
    else if (strid == 0xFD)
    { /* Outline (Skip) */
      cnt = OULFD_ReadFontData(wrk, 2);
      wrk->datacnt -= cnt;
      wrk->dataofs += cnt;
    }
    else
    { /* Stoke */
      if (strid == 0xFF)
      {
        strid = OULFD_ReadFontData(wrk, 2);
      }

      /* Load stroke data */
      OULFD_LoadStrokeData(wrk, strid, &relflag);

      /* Read relative point */
      mask = 1;
      for (i=0; i<wrk->fdl.relno; i++)
      {
        if (i>=1 && i<=4 && relflag!=0)
        {
          if ((relflag & mask)==0)
            wrk->fdl.rel[i*2] = (DT8_BYTE)OULFD_ReadFontData(wrk, 1);
          else
            wrk->fdl.rel[i*2] = wrk->fdl.rel[i*2-2];
          mask = (DT16_WORD)(mask << 1);

          if ((relflag & mask)==0)
            wrk->fdl.rel[i*2+1] = (DT8_BYTE)OULFD_ReadFontData(wrk, 1);
          else
            wrk->fdl.rel[i*2+1] = wrk->fdl.rel[i*2-1];
          mask = (DT16_WORD)(mask << 1);
        }
        else
        {
          wrk->fdl.rel[i*2]   = (DT8_BYTE)OULFD_ReadFontData(wrk, 1);
          wrk->fdl.rel[i*2+1] = (DT8_BYTE)OULFD_ReadFontData(wrk, 1);
        }
      }

      /* Read value */
      for (i=0; i<wrk->fdl.valno; i++)
        wrk->fdl.val[i] = (DT8_BYTE)OULFD_ReadFontData(wrk, 1);

      /* Modify radical data */
      if (rad)
      {
        OULFD_ModifyRadData(wrk, rad);
      }

      /* Draw stroke / Get stroke outline */
#if _DCW_OVG_DEC_STROKE
			doit = 1;
			if(OULDs_Find(wrk))
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
		      ret = OFDL_GetFont(&wrk->fdl);
			else
			  ret = 0;
#else
      ret = OFDL_GetFont(&wrk->fdl);
#endif
	}
#if _DCW_OVG_DEC_STROKE
		wrk->DsPartIdx++;
#endif
  }
  wrk->inrad = 0;

  return ret;
}
/*---------------------------------------------------------------------------*/
DT_void OULFD_ModifyRadData(pODcwWrk wrk, OTFDLRadParam *rad)
{
  DT32_int w2, h2, x, y, i;

  /* Modify value */
  if (rad->wid != 128)
  {
    for (i=0; i<wrk->fdl.valno; i++)
    {
      wrk->fdl.val[i] = (DT8_BYTE)(((DT32_int)wrk->fdl.val[i] * rad->wid + 64) / 128);
    }
  }

  /* Modify relative point */
  w2 = rad->srcw;
  h2 = rad->srch;

  for (i=0; i<wrk->fdl.relno; i++)
  {
    x = wrk->fdl.rel[i*2];
    y = wrk->fdl.rel[i*2+1];

    y = (((y - rad->srcx) * rad->destw + w2) / rad->srcw) + rad->destx;
    x = (((x - rad->srcy) * rad->desth + h2) / rad->srch) + rad->desty;

    wrk->fdl.rel[i*2]   = (DT8_BYTE)x;
    wrk->fdl.rel[i*2+1] = (DT8_BYTE)y;
  }
}
/*---------------------------------------------------------------------------*/

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
extern DT32_int GetFontIdxScaleRatioByFontData(DT8_char *fontdata, DT32_long fontidx, DT32_int opt, DT32_int *brtochar);
extern DT32_int FD_GetYoffsetByData(DT8_char *fontdata, DT32_long ofs, DT16_ushort gidx, DT_void *offsetY, DT16_ushort datalen);


//DT32_int DCWOUL_SetRatio(DCWOUL_Handle hnd, DT32_long ratio)
//{
//		pODcwWrk wrk = (pODcwWrk)hnd;
//		wrk->ratio = ratio;
//		return 0;
//}

DT32_int DCWOUL_QueryCharAttr(DCWOUL_Handle hnd, DT8_char *fontdata, DT32_long fontidx, DCWOUL_CharAttr_Option option)
{

//	pODcwWrk wrk = (pODcwWrk)hnd;	// not required in this function
	DT32_int	ratio, bRtoChar;
	DT16_ushort langtabcnt;
	DT32_long	ofs, langtab;
//	DT32_long	offsetY;
	DT32_int	ret=-1;

//	langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
//	if(langtab > 0)
//		langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab);
//	else
//		langtabcnt = 0;
	
	switch(option){

	case DCWOUL_CHARATTR_LANGTAB_GLOBAL:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_GLOBAL, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;

		return (DT32_int)ofs;

	case DCWOUL_CHARATTR_LANGTAB_HINDI_SUB:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_HINDI_SUB, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;

	case DCWOUL_CHARATTR_LANGTAB_HINDI_POS1:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_HINDI_POS1, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;

	case DCWOUL_CHARATTR_LANGTAB_HINDI_POS2:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_HINDI_POS2, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;

	case DCWOUL_CHARATTR_LANGTAB_HINDI_POS3:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_HINDI_POS3, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;

	case DCWOUL_CHARATTR_LANGTAB_RSB:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_RSB, langtab, langtabcnt);
			if(ofs ==0)
				ofs = -1;
		}else ofs =-1;
	
		return (DT32_int)ofs;


	case DCWOUL_CHARATTR_LANGTAB_THAI:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_THA, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;
	case DCWOUL_CHARATTR_LANGTAB_ICON:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_ICN, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;
	case DCWOUL_CHARATTR_LANGTAB_RAS_SCALE:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_RAS_SCALE, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;
	case DCWOUL_CHARATTR_LANGTAB_BIN_SCALE:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_BIN_SCALE, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;
	case DCWOUL_CHARATTR_LANGTAB_DESCENT:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_DESCENT, langtab, langtabcnt);
		}
		if(ofs <= 0)
			return -1;
		return (DT32_int)ofs;	
	case DCWOUL_CHARATTR_XYSCALERATIO:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(fontdata, fontidx, DCWOUL_LANGTAB_ICN, &bRtoChar);
		return ratio;
	case DCWOUL_CHARATTR_ISXYSCALE_CHAR:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(fontdata, fontidx, DCWOUL_LANGTAB_ICN, &bRtoChar);
		return bRtoChar;
	case DCWOUL_CHARATTR_RASSCALERATIO:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(fontdata, fontidx, DCWOUL_LANGTAB_RAS_SCALE, &bRtoChar);
		return ratio;
	case DCWOUL_CHARATTR_ISRASSCALE_CHAR:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(fontdata, fontidx, DCWOUL_LANGTAB_RAS_SCALE, &bRtoChar);
		return bRtoChar;	
	case DCWOUL_CHARATTR_BINSCALERATIO:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(fontdata, fontidx, DCWOUL_LANGTAB_BIN_SCALE, &bRtoChar);
		return ratio;
	case DCWOUL_CHARATTR_ISBINSCALE_CHAR:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(fontdata, fontidx, DCWOUL_LANGTAB_BIN_SCALE, &bRtoChar);
		return bRtoChar;
	case DCWOUL_CHARATTR_HEIGHT_SHIFT:
		return 0;
	
#if(0)
	case DCWOUL_CHARATTR_NORMAL_WIDTH:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(fontdata, fontidx, DCWOUL_LANGTAB_ICN, &bRtoChar);
		szY = DCWOUL_SCALED_SIZEXY(attr->ysize,ratio);		//attr->ysize*1000/ratio;
		if(DCWOUL_BASE_RATIO==ratio){
			return attr->xsize;
		}else{
			return szY;// force scaling by ysize.
		}
		break;

	case DCWOUL_CHARATTR_NORMAL_HEIGHT:
		bRtoChar = 0;
		ratio = GetFontIdxScaleRatioByFontData(fontdata, fontidx, DCW_LANGTAB_ICN, &bRtoChar);
		szY = DCW_SCALED_SIZEXY(attr->ysize,ratio);		//attr->ysize*1000/ratio;
		if(DCW_BASE_RATIO==ratio){
			return attr->ysize;
		}else{
			return szY;
		}
		break;
#endif

	case DCWOUL_CHARATTR_ISOFFSETY_CHAR:
		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_DESCENT, langtab, langtabcnt);
			if(ofs > 0){
				DT8_uchar ver = (DT8_uchar) fontdata[ofs + 1];
				if(1==ver){
					DT32_long offsetY = 0;
					ret = FD_GetYoffsetByData(fontdata, ofs, (DT16_ushort)fontidx, &offsetY, 4);					
				}else{
					DT16_short offsetY = 0;
					ret = FD_GetYoffsetByData(fontdata, ofs, (DT16_ushort)fontidx, &offsetY, 2);
				}
				if(ret>=0){
					return 1;
				}
			}
		}
		return 0;
	case DCWOUL_CHARATTR_GET_OFFSETY:
	case DCWOUL_CHARATTR_GET_LOGHEIGHT:
	case DCWOUL_CHARATTR_GET_3IN1_VALUE:

		ofs = 0;
		langtab= FD_READINTBYDATA4(fontdata, OFD_LANGTAB);
		if(langtab > 0)
		{
			//ofs = langtab;
			langtabcnt = (DT16_ushort)FD_READINTBYDATA2(fontdata, langtab/*ofs*/);
			ofs = FD_GetLangTableByData(fontdata, DCWOUL_LANGTAB_DESCENT, langtab, langtabcnt);
			if(ofs > 0){
				DT8_uchar ver = (DT8_uchar) fontdata[ofs + 1];
				DT_BOOL   b3in1 = (DCWOUL_CHARATTR_GET_3IN1_VALUE==option)?DT_TRUE:DT_FALSE;
				DT32_long offy, logh, logt;
				if(1==ver){
					DT32_long offsetY = 0;
					ret = FD_GetYoffsetByData(fontdata, ofs, (DT16_ushort)fontidx, &offsetY, 4);
					if(b3in1){
						offy = DCWOUL_OFFY_FROM_LOGHOFFY(offsetY);
						logh = DCWOUL_LOGH_FROM_LOGHOFFY(offsetY);
						logt = 0;
						return (DT32_int) DCWOUL_MAKE_3IN1_VALUE(offy,logh,logt);
					}else
						return (DT32_int) offsetY;
				}else if(2==ver){
					DT32_long val3in1 = 0;
					ret = FD_GetYoffsetByData(fontdata, ofs, (DT16_ushort)fontidx, &val3in1, 4);
					if(b3in1){
						return (DT32_int) val3in1;
					}else /*if(DCW_CHARATTR_GET_OFFSETY==option || DCW_CHARATTR_GET_LOGHEIGHT==option)*/{
						offy = DCWOUL_OFFY_FROM_3IN1_VALUE(val3in1);
						logh = DCWOUL_LOGH_FROM_3IN1_VALUE(val3in1);
						return (DT32_int) DCWOUL_MAKE_LOGH_OFFY(offy,logh);
					}
				}else{
					DT16_short offsetY = 0;
					ret = FD_GetYoffsetByData(fontdata, ofs, (DT16_ushort)fontidx, &offsetY, 2);
					if(b3in1){
						offy = (DT32_long) offsetY;
						logh = 0;
						logt = 0;
						return (DT32_int) DCWOUL_MAKE_3IN1_VALUE(offy,logh,logt);
					}else
						return (DT32_int) offsetY;
				}
			}
		}
		return 0;
	case DCWOUL_CHARATTR_END:

	default:
		return 0;
	}
	return 0;
}

#if _DCW_OVG_DEC_STROKE
/*---------------------------------------------------------------------------*/
DT32_int OULDs_SetDsData(pODcwWrk wrk, DT8_char *dsdata)
{
	if(dsdata)
	{
		wrk->DsFontCnt = (DT16_WORD)OULFD_READINTBYDATA2(dsdata, 0);		//*((DT16_WORD*)dsdata);
		dsdata += 2;

		wrk->DsIdxs = (DT8_BYTE*)dsdata;									//(DT16_WORD*)dsdata;
		dsdata += (wrk->DsFontCnt + 1) * 4;

		wrk->DsDatas = (DT8_BYTE*)dsdata;
	} else
	{
		wrk->DsFontCnt  = 0;
		wrk->DsIdxs     = NULL;
		wrk->DsDatas    = NULL;
	}

	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OULDs_LoadData(pODcwWrk wrk, DT32_int fidx, DT32_int decstr)
{
	DT16_WORD ofs, fidx2, i;
	DT8_BYTE *idxs;																	//DT16_WORD *idxs;

	wrk->DsCnt  = 0;
	wrk->DsData = NULL;

	if(decstr)
	{
		idxs = wrk->DsIdxs;
		for(i = 0; i < wrk->DsFontCnt; i++)
		{
			fidx2 = (DT16_WORD)OULFD_READINTBYDATA2(idxs, 0);						//*idxs;
			if(fidx2 == fidx)
			{
				ofs = (DT16_WORD)OULFD_READINTBYDATA2(idxs, 1*2);					//*(idxs + 1);

				wrk->DsCnt  = (DT16_WORD)OULFD_READINTBYDATA2(idxs, 3*2) - ofs;		//*(idxs + 3) - ofs;
				wrk->DsData = wrk->DsDatas + (ofs * 3);
				return(1);
			} else if(fidx2 > fidx)
				break;

			idxs += 2*2;															//idxs += 2;
		}
	}

	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OULDs_Find(pODcwWrk wrk)
{
	DT32_int fsize, fsize2, pidx, modeval;
	DT8_BYTE *p;
	DT32_int cnt;

	//fsize = wrk->fdl.xsize;
	//if(fsize != wrk->fdl.ysize || fsize > 255)	return(0);

	fsize = wrk->sizexy;

	p = wrk->DsData;
	cnt = wrk->DsCnt;

	while(cnt > 0)
	{
		fsize2 = *p++;
		if(fsize2 > fsize) break;

		if(fsize2 == fsize)
		{
			pidx = *p++;
			if(pidx == wrk->DsPartIdx)
			{
				modeval = *p++;
				wrk->DsMode = modeval >> 4;
				wrk->DsVal  = modeval & 0x0f;
				return(1);
			} else
				p++;
		} else
			p += 2;

		cnt--;
	}

	return(0);
}
/*---------------------------------------------------------------------------*/
#endif  /* _DCW_OVG_DEC_STROKE */
