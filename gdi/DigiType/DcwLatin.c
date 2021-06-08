#include "DcwLangModule.h"
#include "DcwLatin.h"
#include "DcwLayout.h"
#include "DcwBiDi.h"


/* Make the awseq. */
DT_void Fillawseg_LAT(pLayWrk pwrk)
{
	DT32_int i, aw=0, ht=0, segw=0, segh=0;
	DT16_ushort ch, gidx=0;
	DLO_Point p;

DBG_MSG_SHOW_FUNC_NAME();

	p.x = 0;	p.y = 0;
	for(i=pwrk->seg_start;i<pwrk->seg_end;i++)
	{
		ch = pwrk->gseq[i].glyf2;
		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,ch,pwrk->gseq[i].idx_gseq2);
		ht = pwrk->fengfuncs.getAheight(pwrk->ras_attr,ch,pwrk->gseq[i].idx_gseq2);
		pwrk->awseq[i].codeidx	= i;
		pwrk->awseq[i].glyfidx = pwrk->gseq[i].idx_gseq2;
		pwrk->awseq[i].aw.vx	= aw;
		pwrk->awseq[i].aw.vy	= 0;
//		pwrk->awseq[i].direct	= DLO_LEFTTORIGHT;
		p.x = segw;		p.y = 0;
		pwrk->awseq[i].leftup = p;

		/* It's useless here, because only 1code=1glyph situation in Latin. */
		if(i==pwrk->seg_start) gidx = pwrk->awseq[i].glyfidx;
		else if(pwrk->awseq[i].glyfidx == gidx) continue;
		else gidx = pwrk->awseq[i].glyfidx;

		segw += aw;
		if(ht > segh){
			segh = ht;
		}
	}
	pwrk->segw = segw;
	pwrk->segh = segh;
}

/* fill the segment info to the segment array, segarr. */
DT_void Fillsegarr_LAT(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();

	pwrk->segarr[pwrk->seg_cnt].ustart	= pwrk->seg_start;
	pwrk->segarr[pwrk->seg_cnt].uend	= pwrk->seg_end;
	pwrk->segarr[pwrk->seg_cnt].script	= pwrk->seg_script;
	pwrk->segarr[pwrk->seg_cnt].lang	= pwrk->seg_lang;
	pwrk->segarr[pwrk->seg_cnt].sw		= pwrk->segw;
	pwrk->segarr[pwrk->seg_cnt].sh		= pwrk->segh;	
}

/* Return: use to distinguish if it need DT_DECENT_PIXS() or DT_FORCE_MOVE_DOWN_PIXS()	*/
/* 0: No DT_DESCENT_PIXS(), No DT_FORCE_MOVE_DOWN_PIXS(), like Chinese, Japanese...		*/
/* 1: DT_FORCE_MOVE_DOWN_PIXS(), but no DT_DESCENT_PIXS(), basic Latin area(0x20-0x7E)	*/
/* 2: DT_FORCE_MOVE_DOWN_PIXS() and DT_DESCENT_PIXS(), like g, j, p, q, y				*/
DT32_int is_LatinChars_Descent(pLayWrk pwrk, DT16_ushort ch)
{
	return 0;
//	switch(ch){
//	case 0x0067:	// g
//	case 0x006A:	// j
//	case 0x0070:	// p
//	case 0x0071:	// q
//	case 0x0079:	// y
//		return 2;
//	default:
//		if(ch>0x001F && ch<0x007F){
//			return 1;
//		}else{
//			return 0;
//		}
//	}
//	return 0;
}

/*---------------------------------------------------------------------------------------------*/

/* Get Latin segment info. */
DT32_int GetSeginfo_Latin(pLayWrk pwrk, Str_Seg *seginfo)
{
	DT32_int i, j, st, en, aw, caret=0, under=0;
	DT16_ushort c,g,gidx=0;
	DLO_CodePositioning p;
	DLO_RECT rect;

DBG_MSG_SHOW_FUNC_NAME();

	st = seginfo->ustart;
	en = seginfo->uend;
	if(pwrk->lobuf->writedir == DLO_LEFTTORIGHT)	caret = seginfo->cpstart.x;
	else if(pwrk->lobuf->writedir == DLO_RIGHTTOLEFT)caret = seginfo->cpstart.x - seginfo->sw;
	else caret = seginfo->cpstart.x;


	rect.xy.x =rect.xy.y =0;
	rect.hw.vx=rect.hw.vy=0;
	c=1; g=1;
	for(i=st;i<en;i+=c){
	  Parse_n_per_glyf(pwrk->gseq[i].n_per_glyf2,&c,&g);
	  gidx = pwrk->gseq[i].idx_gseq2;
	  aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,pwrk->gseq2[gidx],gidx);
	  caret += aw;
	  /* Make DLO_CodePositioning for every glyf */
	  for(j=0; j<g; j++,gidx++){
		pwrk->lobuf->glyf_seq[gidx] = pwrk->gseq2[gidx];
		p.codeidx = i;
		p.glyfidx = gidx;

		if(0==j)	// The first one glyf set to n_per_glyf2
		  p.n_per_glyf = Make_n_per_glyf(c,g);	// pwrk->gseq[i].n_per_glyf2;
		else		// Others are set as 0, this won't happen because only 1code=1glyph in Latin.
		  p.n_per_glyf = 0;

		p.caretpos.x= caret;
		p.caretpos.y= 0;
		p.oripos.x	= caret-aw;
		p.oripos.y	= 0 + need_Move_Down_Pixs(pwrk, pwrk->gseq2[gidx], gidx);	//0;
		p.awvec.vx	= aw;
		p.awvec.vy	= 0;
		p.adjvec.vx	= 0;
		p.adjvec.vy = 0;
		p.drawmethod= DLO_DRAW_NORMAL;
		p.dmrect	= rect;
		pwrk->lobuf->caret_seq[gidx] = p;
	  }
	}

	seginfo->cpend.x = caret;
	seginfo->cpend.y = 0;

	return DLO_SUCCESS;
}

DT32_int CalcPosition_Latin(pLayWrk pwrk, DT_void *para)
{
	DT16_ushort nowglyph;
	DT32_int j, aw, ht, caret, lastcaret, lastpoint_aw=0;
	DLO_RECT rect;

DBG_MSG_SHOW_FUNC_NAME();

//	if(pwrk->vert){
//		return CalcPosition_Latin_vert(pwrk,para);
//	}

	/* calculate the position information. */
	lastcaret = caret = pwrk->linewidth;
	pwrk->segw = caret;			// keep the start caret pos.

	rect.xy.x =rect.xy.y =0;
	rect.hw.vx=rect.hw.vy=0;
	ht = 0;
	for(j=pwrk->seg_start;j<pwrk->seg_end;j++){
	  nowglyph = pwrk->lobuf->glyf_seq[j];
	  aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph,j);
	  ht = pwrk->fengfuncs.getAheight(pwrk->ras_attr,nowglyph,j);

	  if(NSM!=bidi_getBidiClass(nowglyph)){
		  lastcaret = caret;
	  }
	  pwrk->lobuf->caret_seq[j].oripos.x	= lastcaret;
	  pwrk->lobuf->caret_seq[j].oripos.y	= 0 + need_Move_Down_Pixs(pwrk, nowglyph, j);	//0;
	  pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
	  pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
	  pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
	  pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
	  pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
	  pwrk->lobuf->caret_seq[j].dmrect	= rect;//rect
	  
	  if(NSM!=bidi_getBidiClass(nowglyph)){
		caret += aw;
		if(aw!=0)
		{
			lastpoint_aw = 0;
		}
	  }else
	  {
		if(aw > lastpoint_aw)
			lastpoint_aw = aw;
	  }

	  if(ht > pwrk->segh){
		  pwrk->segh = ht;
	  }
	  // caret is decided here.
	  pwrk->lobuf->caret_seq[j].caretpos.x	= caret;
	  pwrk->lobuf->caret_seq[j].caretpos.y	= 0;
	}

	pwrk->linewidth = caret; //+ lastpoint_aw;
	if(0 == pwrk->linewidth - pwrk->segw)	// only one ZEROWIDTH char
		pwrk->linewidth += lastpoint_aw;

	pwrk->segw = pwrk->linewidth - pwrk->segw;	// now caret - start caret = segw.
	if(pwrk->segh > pwrk->lineheight)
		pwrk->lineheight= pwrk->segh;

	return DLO_SUCCESS;		
}

DT32_int RenderToBuf_Latin(pLayWrk pwrk, DT_void *para)
{
	DT32_int i, mode, ret, rtv, bEmpty;
	DT16_ushort ch, last_ch, compos_ch;
	GlyphSeq	gs;
	Str_Seg		*pss;
	DT16_ushort gidx_st=0, gidx_en=0;
	DT32_long pathsz=0;
	DLO_Point	lt;	/* Left-Top point */

DBG_MSG_SHOW_FUNC_NAME();

	mode = pwrk->rendermode;
	if( (mode&DLO_DATA_RENDER) && !(mode&DLO_DATA_PREPARE_POS) ) goto DATA_RENDER;
	else goto DATA_PREPARE_POS;

DATA_PREPARE_POS:
	/* Get SubLookup Table */
	
	/* Fill the codeidx in gseq, gseq1, gseq2*/
	/*
	for(i=pwrk->seg_start;i<pwrk->seg_end;i++)
	{
		ch = pwrk->attr->ucs_str[i];
		pwrk->gseq1[pwrk->cur_g1idx] = ch;
		pwrk->gseq2[pwrk->cur_g2idx] = ch;

		gs.idx			= i;
		gs.code			= ch;

		gs.glyf1 = ch;
		gs.idx_gseq1 = pwrk->cur_g1idx;
		gs.n_per_glyf1 = Make_n_per_glyf(1,1);

		gs.glyf2 = ch;
		gs.idx_gseq2 = pwrk->cur_g2idx;
		gs.n_per_glyf2 = Make_n_per_glyf(1,1);

		pwrk->gseq[i] = gs;

		pwrk->cur_g1idx++;
		pwrk->cur_g2idx++;
	}
	*/
	
	last_ch = 0;
	for(i=pwrk->seg_start;i<pwrk->seg_end;i++)
	{
		ch = pwrk->attr->ucs_str[i];
		gs.idx			= i;
		gs.code			= ch;
		/**/
		gs.glyf1 = ch;
		gs.idx_gseq1 = pwrk->cur_g1idx;
		gs.n_per_glyf1 = Make_n_per_glyf(1,1);
		pwrk->gseq1[pwrk->cur_g1idx] = ch;
		pwrk->cur_g1idx++;

		/**/
		gs.glyf2 = ch;
		gs.idx_gseq2 = pwrk->cur_g2idx;
	

#ifdef LATIN_vietnamese
		compos_ch  =0;
		if (ch >= 0x0300 && ch < 0x0340)				     
	    {								
		   switch (ch)							      
		   {								     
			  case 0x0300:						      
				compos_ch = Latin_Vietnamese(0, last_ch);	     
				break;							      
			  case 0x0301:						     
				compos_ch =	Latin_Vietnamese(1, last_ch); 
				break;							      
			  case 0x0303:						      
				compos_ch =	Latin_Vietnamese(2, last_ch);	     
				break;							     
			  case 0x0309:						      
				compos_ch = Latin_Vietnamese(3, last_ch);	      
				break;							      
			  case 0x0323:						      
				compos_ch =	Latin_Vietnamese(4, last_ch);      
				break;							      
			  default:	
				compos_ch = 0;
				break;			      
		   }
		   if(compos_ch!=0)
		   {   
			    /*get pre-xx*/
			    pwrk->cur_g2idx--;
				gs.idx_gseq2 = pwrk->cur_g2idx;
				gs.glyf2 = compos_ch;
				/*fill combined condition value*/
			    gs.n_per_glyf2 = Make_n_per_glyf(2,1);
				pwrk->gseq2[pwrk->cur_g2idx] = compos_ch;
				pwrk->gseq[i-1] = gs;
				pwrk->cur_g2idx++;
				pwrk->gseq[i] = gs;//must be filled, becasue call getCharbmp(), parameter use it to get glyph.
		   }
		   else{
			   	gs.n_per_glyf2 = Make_n_per_glyf(1,1);
				pwrk->gseq2[pwrk->cur_g2idx] = ch;
				pwrk->cur_g2idx++;
				pwrk->gseq[i] = gs;
		   }
		}
		else{
#endif /*LATIN_vietnamese*/
			gs.n_per_glyf2 = Make_n_per_glyf(1,1);
			pwrk->gseq2[pwrk->cur_g2idx] = ch;
			pwrk->cur_g2idx++;
			pwrk->gseq[i] = gs;
#ifdef LATIN_vietnamese
		}
		/*keep per-character*/
		last_ch = ch;
#endif /*LATIN_vietnamese*/

	}

	/* Fill the DLO_Laybuf, including cseq */
	Fillawseg_LAT(pwrk);
	Fillsegarr_LAT(pwrk);

	if(!(mode&DLO_DATA_RENDER)) return DLO_SUCCESS;

	
	/* Render to DLO_Laybuf */	
DATA_RENDER:

	//Modified_By_Jacky_20101213: 
	bEmpty = 0;			//Use this value to indicate if there is any empty font inside.
	rtv = DLO_SUCCESS;	//Use this value to know if something error happened.


#ifdef DIGITYPE_OUL
  if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
	pss = (Str_Seg*) para;
	gidx_st = pwrk->gseq[pss->ustart].idx_gseq2;
	gidx_en = pwrk->gseq[pss->uend-1].idx_gseq2;
	for(i=gidx_st;i<=gidx_en;i++){
	  pwrk->pBuf = pwrk->lobuf->olDatabuf;
	  ret = pwrk->fengfuncs.getOutline( 
						pwrk->ras_attr,
						pwrk->lobuf->glyf_seq[i],
						NULL,
						&pwrk->lobuf->olDatabufSize,
						&(pwrk->pBuf),
						&pathsz);
	  pwrk->lobuf->olDatabuf = pwrk->pBuf;
	  if(ret==DLO_SUCCESS){	//Modified_By_Jacky_20101213: 
		  pwrk->lobuf->olSizebuf[i] = pathsz;
		  pathsz = 0;
	  }else if(ret==DLO_EMPTY_FONT){
		  pwrk->lobuf->olSizebuf[i] = pathsz = 0;
		  bEmpty = 1;
	  }else{
		  pwrk->lobuf->olSizebuf[i] = pathsz = 0;
		  rtv = ret;	//Something error, but we continue to draw the next character.
	  }
	}
  }
#endif


#ifdef DIGITYPE_STD
  if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
	  pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256){
	pss = (Str_Seg*) para;
	gidx_st = pwrk->gseq[pss->ustart].idx_gseq2;
	gidx_en = pwrk->gseq[pss->uend-1].idx_gseq2;

	for(i=gidx_st;i<=gidx_en;i++){
	  lt.x = pwrk->lobuf->caret_seq[i].oripos.x;
	  lt.y = pwrk->lobuf->caret_seq[i].oripos.y;
	  ret = pwrk->fengfuncs.getCharbmp(
					pwrk->ras_attr, 
					pwrk->lobuf->glyf_seq[i],i,
					pwrk->lobuf->bmpwidth, 
					pwrk->lobuf->bmpheight,
					lt.x, lt.y,
					pwrk->lobuf->xbytes, 
					(DT8_uchar*)pwrk->lobuf->bmpbuf,			/* Jacky_20090901 */
					0, 
					pwrk->mode);
	  if(ret==DLO_SUCCESS){	//Modified_By_Jacky_20101213:
	  }else if(ret == DLO_EMPTY_FONT){
		  bEmpty = 1;
	  }else{
		  rtv = ret;		//Something error, but we continue to draw the next character.
	  }
	}
  }
#endif

#ifdef BDF_RASTER
  if(pwrk->fengtype==DLO_ENG_BDFRASTER){
	pss = (Str_Seg*) para;
	gidx_st = pwrk->gseq[pss->ustart].idx_gseq2;
	gidx_en = pwrk->gseq[pss->uend-1].idx_gseq2;
	for(i=gidx_st;i<=gidx_en;i++){
	  lt.x = pwrk->lobuf->caret_seq[i].oripos.x;
	  lt.y = pwrk->lobuf->caret_seq[i].oripos.y;
	  ret = pwrk->fengfuncs.getCharbmp(
					pwrk->ras_attr, 
					pwrk->lobuf->glyf_seq[i],i,
					pwrk->lobuf->bmpwidth, 
					pwrk->lobuf->bmpheight,
					lt.x, lt.y,
					pwrk->lobuf->xbytes, 
					(DT8_uchar*)pwrk->lobuf->bmpbuf,			/* Jacky_20090901 */
					0, 
					pwrk->mode);
	  if(ret==DLO_SUCCESS){	//Modified_By_Jacky_20101213:
	  }else if(ret == DLO_EMPTY_FONT){
		  bEmpty = 1;
	  }else{
		  rtv = ret;		//Something error, but we continue to draw the next character.
	  }
	}
  }
#endif

#ifdef DIF_RASTER
  if( pwrk->fengtype==DLO_ENG_DIFRASTER_BIT ||
	  pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE){
	pss = (Str_Seg*) para;
	gidx_st = pwrk->gseq[pss->ustart].idx_gseq2;
	gidx_en = pwrk->gseq[pss->uend-1].idx_gseq2;
	for(i=gidx_st;i<=gidx_en;i++){
	  lt.x = pwrk->lobuf->caret_seq[i].oripos.x;
	  lt.y = pwrk->lobuf->caret_seq[i].oripos.y;
	  ret = pwrk->fengfuncs.getCharbmp(
					pwrk->ras_attr, 
					pwrk->lobuf->glyf_seq[i],i,
					pwrk->lobuf->bmpwidth, 
					pwrk->lobuf->bmpheight,
					lt.x, lt.y,
					pwrk->lobuf->xbytes, 
					(DT8_uchar*)pwrk->lobuf->bmpbuf,			/* Jacky_20090901 */
					0, 
					pwrk->mode);
	  if(ret==DLO_SUCCESS){	//Modified_By_Jacky_20101213:
	  }else if(ret == DLO_EMPTY_FONT){
		  bEmpty = 1;
	  }else{
		  rtv = ret;		//Something error, but we continue to draw the next character.
	  }
	}
  }
#endif


  if(rtv==DLO_SUCCESS){
	  if(bEmpty){	//no error, but some glyphs don't exist.
		  rtv = DLO_EMPTY_FONT;
	  }
  }

	return rtv;		//Modified_By_Jacky_20101213:
	//return DLO_SUCCESS;
}

DT32_int RenderByPos_Latin(pLayWrk pwrk, DT_void *para)
{
	DT32_int	ret, rtv = DLO_SUCCESS, bEmpty = 0, opengine;
	DT16_ushort i, gidx_st, gidx_en;
	DLO_Point	lt;
	DT32_long pathsz=0;

DBG_MSG_SHOW_FUNC_NAME();

#ifdef DIGITYPE_OUL
  if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
	gidx_st = pwrk->seg_start;
	gidx_en = pwrk->seg_end;
	for(i=gidx_st;i<gidx_en;i++){
	  pwrk->pBuf = pwrk->lobuf->olDatabuf;
	  ret = pwrk->fengfuncs.getOutline( 
						pwrk->ras_attr,
						pwrk->lobuf->glyf_seq[i],
						NULL,
						&pwrk->lobuf->olDatabufSize,
						&(pwrk->pBuf),
						&pathsz);
	  pwrk->lobuf->olDatabuf = pwrk->pBuf;
	  if(ret==DLO_SUCCESS){	//Modified_By_Jacky_20101213: 
		  pwrk->lobuf->olSizebuf[i] = pathsz;
		  pathsz = 0;
	  }else if(ret==DLO_EMPTY_FONT){
		  pwrk->lobuf->olSizebuf[i] = pathsz = 0;
		  bEmpty = 1;
	  }else{
		  pwrk->lobuf->olSizebuf[i] = pathsz = 0;
		  rtv = ret;	//Something error, but we continue to draw the next character.
	  }
	}
  }
#endif

    // opengine=1: bmp mode, includes Digitype_std, BDF_Raster, and DIF_Raster.
	switch(pwrk->fengtype)
	{
#ifdef DIGITYPE_STD
	case DLO_ENG_DCWRASTER_MONO:
	case DLO_ENG_DCWRASTER_GRAY16:
	case DLO_ENG_DCWRASTER_GRAY256:
		opengine = 1;
		break;
#endif
#ifdef BDF_RASTER
	case DLO_ENG_BDFRASTER:
		opengine = 1;
		break;
#endif
#ifdef DIF_RASTER
	case DLO_ENG_DIFRASTER_BIT:
	case DLO_ENG_DIFRASTER_BYTE:
		opengine = 1;
		break;
#endif
	default:
		opengine = 0;	// default: do nothing.
	}

  if( 1==opengine ){
	gidx_st = pwrk->seg_start;
	gidx_en = pwrk->seg_end;

	for(i=gidx_st;i<gidx_en;i++){
	  lt.x = pwrk->lobuf->caret_seq[i].oripos.x;
	  lt.y = pwrk->lobuf->caret_seq[i].oripos.y;
	  ret = pwrk->fengfuncs.getCharbmp(
					pwrk->ras_attr, 
					pwrk->lobuf->glyf_seq[i],i,
					pwrk->lobuf->bmpwidth, 
					pwrk->lobuf->bmpheight,
					lt.x, lt.y,
					pwrk->lobuf->xbytes, 
					(DT8_uchar*)pwrk->lobuf->bmpbuf,			/* Jacky_20090901 */
					0, 
					pwrk->mode);
	  if(ret==DLO_SUCCESS){	//Modified_By_Jacky_20101213:
	  }else if(ret == DLO_EMPTY_FONT){
		  bEmpty = 1;
	  }else{
		  rtv = ret;		//Something error, but we continue to draw the next character.
	  }
	}
  }

  if(rtv==DLO_SUCCESS){
	if(bEmpty){	//no error, but some glyphs don't exist.
		rtv = DLO_EMPTY_FONT;
	}
  }

  return rtv;
}
