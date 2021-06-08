#include "DcwShaperVG.h"
#include "DcwLangModule.h"
#include "DcwHebrew.h"
#include "DcwLayout.h"
#include "DcwBiDi.h"

#include "DTmanager.h"

/* Check if it's a Mark or Point of Hebrew */
/* 0x25CC won't be a Marks or Points of Hebrew. */
/* Return: 0: It's not a Mark or Point; 1: a Mark or Point */
DT8_uchar isHebrewMarksOrPoints(DT16_ushort ucs)
{
DBG_MSG_SHOW_FUNC_NAME();
	if( ucs>=0x0591 && ucs<=0x05C7 && 
		ucs!=0x05BE && ucs!=0x05C0 && ucs!=0x05C6){
		return 1;
	}
	return 0;
}

/* make the gseq1 and fill the data to the gseq. */
/* Return: current idx of gseq.					 */
DT16_ushort ModifygseqElem(pLayWrk pwrk, DT16_ushort g1idx, DT16_ushort g2idx, DT16_ushort idx, DT16_ushort glyf, DT16_ushort cnt)
{
	DT16_ushort i;
	DT16_ushort nextNcodes = cnt;

DBG_MSG_SHOW_FUNC_NAME();

	pwrk->gseq1[g1idx] = glyf;
	pwrk->gseq2[g2idx] = glyf;
	for(i=idx;i<idx+cnt;i++){
	  pwrk->gseq[i].idx	= i;
	  pwrk->gseq[i].code= pwrk->attr->ucs_str[i];
	  pwrk->gseq[i].glyf1 = glyf;
	  pwrk->gseq[i].idx_gseq1 = g1idx;
	  pwrk->gseq[i].n_per_glyf1 = Make_n_per_glyf(nextNcodes,1);

	  pwrk->gseq[i].glyf2 = glyf;
	  pwrk->gseq[i].idx_gseq2 = g2idx;
	  pwrk->gseq[i].n_per_glyf2 = Make_n_per_glyf(nextNcodes,1);	nextNcodes--;
	}
	pwrk->cur_g1idx = g1idx+1;
	pwrk->cur_g2idx = g2idx+1;
	return i;
}

/********* Notice: Please refer to DcwUnicodeRange.c to know what codes had been filtered. *********/
/* convert Hebrew unicodes to glyphs, only 1codes=1glyph, 2codes=1glyph, or 3codes=1glyph will happen.			*/
/* TODO: In Hebrew Presentation Form, 0xFB1E, 0xFB20-0xFB29 are not used here. Need to check if it is right.	*/
DT_void convHebrewUcs2gseq(pLayWrk pwrk)
{
	DT16_ushort i, j, k, cnt, isvalid=1;
	DT16_ushort n_per_glyph, last_n_per_glyph, g1idx_start, g2idx_start;	//gidx_start
	DT16_ushort *ucs, *pgseq1;
	DT16_ushort base, shaped;

DBG_MSG_SHOW_FUNC_NAME();

	cnt = pwrk->seg_end - pwrk->seg_start;
	g1idx_start = pwrk->cur_g1idx;	/* keep the current (beginning) gseq1 idx */
	g2idx_start = pwrk->cur_g2idx;	/* keep the current (beginning) gseq2 idx */
	//gidx_start  = pwrk->seg_start;	/* keep the current (beginning) gseq idx  */
	if(cnt <= 0){
		return;
	}else{
	  ucs = pwrk->attr->ucs_str + pwrk->seg_start;
	  pgseq1 = pwrk->gseq1 + pwrk->cur_g1idx;
	  //pgseq1[0]= ucs[0]; pwrk->cur_g1idx++;
	  //ModifygseqElem(pwrk, g1idx_start, g2idx_start, g2idx_start, ucs[0], 1);	// Put the first glyph(as ucs) into gseq1, gseq2, gseq
	  k = ModifygseqElem(pwrk, g1idx_start, g2idx_start, pwrk->seg_start, ucs[0], 1);	// Put the first glyph(as ucs) into gseq1, gseq2, gseq
	  j = 1;	//k = 1;
	  last_n_per_glyph = 1;
	  for(i=1;i<cnt;i++)
	  {
            base = pgseq1[j-1];	/* Set base as the last glyph of gseq1 */
            shaped = 0;
			n_per_glyph = 1;
            if(ucs[i] == Dagesh) {
                if(base >= 0x05D0 && base <= 0x05EA
                    && base != 0x05D7 && base != 0x05DD && base != 0x05DF && base != 0x05E2 && base != 0x05E5) {
                    shaped = (base - 0x05D0) + 0xFB30;
					n_per_glyph = 2;
                }else if(base == 0xFB2A || base == 0xFB2B ){	/* (Shin + Shin dot) or (Shin + Sin dot) with Degesh */
                    shaped = base + 2;	/* 0xFB2C, 0xFB2D */
					if(2==last_n_per_glyph)
						n_per_glyph = 3;
					else
						n_per_glyph = 2;	/* To avoid the ucs string contains 0xFB2A, 0xFB2B originally. */
                }else{
                    isvalid = 0;
                }
            }else if(ucs[i] == ShinDot){
                if(base == 0x05E9){
                    shaped = 0xFB2A;
					n_per_glyph = 2;
                }else if(base == 0xFB49){
                    shaped = 0xFB2C;
					if(2==last_n_per_glyph)
						n_per_glyph = 3;
					else
						n_per_glyph = 2;	/* To avoid the ucs string contains 0xFB2A, 0xFB2B originally. */
                }else{
                    isvalid = 0;
				}
            }else if(ucs[i] == SinDot){
                if(base == 0x05E9){
                    shaped = 0xFB2B;
					n_per_glyph = 2;
                }else if(base == 0xFB49){
                    shaped = 0xFB2D;
					if(2==last_n_per_glyph)
						n_per_glyph = 3;
					else
						n_per_glyph = 2;	/* To avoid the ucs string contains 0xFB2A, 0xFB2B originally. */
                }else{
                    isvalid = 0;
				}
            }else if(ucs[i] == Patah){
                if(base == 0x05D0){
                    shaped = 0xFB2E;
					n_per_glyph = 2;
				}else if(base == 0x05F2){
					shaped = 0xFB1F;
					n_per_glyph = 2;
				}
            }else if(ucs[i] == Qamats){
                if(base == 0x05D0){
                    shaped = 0xFB2F;
					n_per_glyph = 2;
				}
            }else if(ucs[i] == Holam){
                if(base == 0x05D5){
                    shaped = 0xFB4B;
					n_per_glyph = 2;
				}
            }else if(ucs[i] == Rafe){
                if(base == 0x05D1){
                    shaped = 0xFB4C;
					n_per_glyph = 2;
                }else if(base == 0x05DB){
                    shaped = 0xFB4D;
					n_per_glyph = 2;
                }else if(base == 0x05E4){
                    shaped = 0xFB4E;
					n_per_glyph = 2;
				}
            }else if(ucs[i] == Hiriq){
				if(base == 0x05D9){
					shaped = 0xFB1D;
					n_per_glyph = 2;
				}
            }else if(ucs[i] == 0x05DC){		/* Alef-Lamed */
				if(base == 0x05D0){
					shaped = 0xFB4F;
					n_per_glyph = 2;
				}
            }

            if(isvalid==0){
                //pgseq1[j] = 0x25CC;	/* Null dot circle */
				/* n_per_glyph should be 1 */
				k = ModifygseqElem(pwrk, (DT16_ushort)(g1idx_start+j), (DT16_ushort)(g2idx_start+j), k, 0x25CC, n_per_glyph);
                j++;
				//k = i;	//k += n_per_glyph;
				last_n_per_glyph = n_per_glyph;
            }
            if(shaped){
//                if(pwrk->fengfuncs.getAwidth(pwrk->ras_attr,shaped)<=0){
//                    shaped = 0;
				if(!pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr,shaped,-1)){
                    shaped = 0;
                }else{
                    //pgseq1[j-1] = shaped;	/* Modify previous glyph */
					/* Re-Calculate k, n_per_glyph should be 2 or 3 */
					if(n_per_glyph==2){
						k = k-1;
					}else if(n_per_glyph==3){
						k = k-2;
					}
					//ModifygseqElem(pwrk, g1idx_start+j-1, g2idx_start+j-1, gidx_start+k, shaped, n_per_glyph);
					k = ModifygseqElem(pwrk, (DT16_ushort)(g1idx_start+j-1), (DT16_ushort)(g2idx_start+j-1), k, shaped, n_per_glyph);
					//k = i;	//k += n_per_glyph;
					last_n_per_glyph = n_per_glyph;
				}
            }
            if(!shaped){
                //pgseq1[j] = ucs[i];
				/* n_per_glyph should be 1 */
				//ModifygseqElem(pwrk, g1idx_start+j, g2idx_start+j, gidx_start+k, ucs[i], n_per_glyph);
				k = ModifygseqElem(pwrk, (DT16_ushort)(g1idx_start+j), (DT16_ushort)(g2idx_start+j), k, ucs[i], n_per_glyph);
                j++;
				//k = i;	//k += n_per_glyph;
				last_n_per_glyph = n_per_glyph;
            }
	  }	
	}
}

/********* In modern IT displays of Hebrew, the points and marks aren't used.			   *********/
DT_void convHebrewUcs2gseq_MarksPointsFiltered(pLayWrk pwrk)
{
	DT16_ushort i, k, cnt;
	DT16_ushort g1idx_start, g2idx_start;	//gidx_start
	DT16_ushort *ucs;

DBG_MSG_SHOW_FUNC_NAME();

	cnt = pwrk->seg_end - pwrk->seg_start;
	g1idx_start = pwrk->cur_g1idx;	/* keep the current (beginning) gseq1 idx */
	g2idx_start = pwrk->cur_g2idx;	/* keep the current (beginning) gseq2 idx */
	//gidx_start  = pwrk->seg_start;	/* keep the current (beginning) gseq idx  */
	if(cnt <= 0){
		return;
	}else{
		k = pwrk->seg_start;
		ucs = pwrk->attr->ucs_str + pwrk->seg_start;
		for(i=0; i<cnt; i++){
			if(isHebrewMarksOrPoints(ucs[i])){
				k = ModifygseqElem(pwrk, (DT16_ushort)(g1idx_start+i), (DT16_ushort)(g2idx_start+i), k, 0x25CC, 1);	
			}else{
				k = ModifygseqElem(pwrk, (DT16_ushort)(g1idx_start+i), (DT16_ushort)(g2idx_start+i), k, ucs[i], 1);
			}
		}
	}
}

/* Make the awseq. */
DT_void Fillawseg_IWR(pLayWrk pwrk)
{
	DT32_int i, aw=0, ht=0, segw=0, segh=0;
	DT16_ushort ch, gidx=0;		/* Jacky_20100209 */
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
//		pwrk->awseq[i].direct	= DLO_RIGHTTOLEFT;
		p.x = segw;		p.y = 0;
		pwrk->awseq[i].leftup = p;

		/* Only multi-codes=1glyph supported, so use gidx to distinguish this situation. */
		if(i==pwrk->seg_start) gidx = pwrk->awseq[i].glyfidx;
		else if(pwrk->awseq[i].glyfidx == gidx) continue;
		else gidx = pwrk->awseq[i].glyfidx;
		
		if(!isHebrewMarksOrPoints(ch)){
			segw += aw;
			if(ht > segh){
				segh = ht;
			}
		}
	}

	pwrk->segw = segw;
	pwrk->segh = segh;
}

/* fill the segment info to the segment array, segarr. */
DT_void Fillsegarr_IWR(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();

	Fillsegarr_R2L(pwrk);
}



/*---------------------------------------------------------------------------------------------*/

/* Get Latin segment info. */
DT32_int GetSeginfo_Hebrew(pLayWrk pwrk, Str_Seg *seginfo)
{
	DT32_int i, j, st, en, g2st, g2en, gcnt, aw, caret;
	DT16_ushort c, g, gidx=0;		/* Jacky_20100209 */
	DLO_CodePositioning p;
	DLO_RECT rect;
	DT8_uchar issamecell=0;			/* 0: next cell; 1: same cell. */
	pDT_FontMgr_wrk	pmgrwrk=((DT_Font*)(pwrk->cur_DT_Font))->fontmgr;
	FontCodeInfo *pfc;

DBG_MSG_SHOW_FUNC_NAME();

	DT_memset(&p,0,sizeof(DLO_CodePositioning));	/* To avoid warnings when compile with GCC */
	DT_memset(&rect, 0, sizeof(DLO_RECT));

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
	
	c=1; g=1; gidx = g2en; j = g2st;
	for(i=st;i<en;i+=c,gidx--,j++){
	  pwrk->lobuf->glyf_seq[j] = pwrk->gseq2[gidx];
	  Parse_n_per_glyf(pwrk->gseq[i].n_per_glyf2,&c,&g);
	  p.codeidx = i;
	  p.glyfidx = j;
	  p.n_per_glyf = Make_n_per_glyf(c,g);	// only multi-codes=1Glyph situation supported. Don't deal with g>1.
	  //pwrk->lobuf->caret_seq[gidx] = p;	/* Jacky_20100622 */
	  pwrk->lobuf->caret_seq[j] = p;		// 20111104: Jacky
	  if(pfc)
		pfc[j-g2st] = pwrk->g2info[gidx];		// copy the element to the tempbuf.
	  else
		pwrk->g2info[j].checkedFlag = 0;	// set the element in g2info to 0 directly.
	}

	// reset g2info (copy from the tempbuf) due to the gseq2 is reordered.
	if(pfc)
		DT_memcpy(&pwrk->g2info[g2st], pfc, gcnt*sizeof(FontCodeInfo));


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
	  pwrk->lobuf->caret_seq[j].oripos.y	= 0 + need_Move_Down_Pixs(pwrk, pwrk->lobuf->glyf_seq[j], j);	//0;;
	  pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
	  pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
	  pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
	  pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
	  pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
	  pwrk->lobuf->caret_seq[j].dmrect	= rect;
	  issamecell = isHebrewMarksOrPoints(pwrk->lobuf->glyf_seq[j]);
	  if(!issamecell){
		caret += aw;
	  }
	}

	seginfo->cpend.x = caret;
	seginfo->cpend.y = 0;

	return DLO_SUCCESS;
}

DT32_int CalcPosition_Hebrew(pLayWrk pwrk, DT_void *para)
{
	DT16_ushort nowglyph;
	DT32_int j, aw, ht, caret, lastcaret, lastpoint_aw=0;
	DLO_RECT rect;

DBG_MSG_SHOW_FUNC_NAME();

//	if(pwrk->vert)
//		return CalcPosition_Hebrew_vert(pwrk,para);
	
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

	  //if( NSM!=bidi_getBidiClass(pwrk->lobuf->glyf_seq[j]))	// Not Sure if it's right, distinguish by ourselves.
	  if(!IS_ARABIC_ZEROWIDTH(nowglyph) && !isHebrewMarksOrPoints(nowglyph)){
		  lastcaret = caret;
	  }

	  pwrk->lobuf->caret_seq[j].caretpos.x	= lastcaret;
	  pwrk->lobuf->caret_seq[j].caretpos.y	= 0;
	  pwrk->lobuf->caret_seq[j].oripos.x	= lastcaret;
	  pwrk->lobuf->caret_seq[j].oripos.y	= 0 + need_Move_Down_Pixs(pwrk, nowglyph, j);	//0;
	  pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
	  pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
	  pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
	  pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
	  pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
	  pwrk->lobuf->caret_seq[j].dmrect	= rect;//rect

	  //if( NSM!=bidi_getBidiClass(pwrk->lobuf->glyf_seq[j]))	// Not Sure if it's right, distinguish by ourselves.
	  if(!IS_ARABIC_ZEROWIDTH(nowglyph) && !isHebrewMarksOrPoints(nowglyph)){
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
	}

	pwrk->linewidth = caret;	// + lastpoint_aw;
	if(0 == pwrk->linewidth - pwrk->segw)	// only one ZEROWIDTH char
		pwrk->linewidth += lastpoint_aw;

	pwrk->segw = pwrk->linewidth - pwrk->segw;	// now caret - start caret = segw.
	if(pwrk->segh > pwrk->lineheight)
		pwrk->lineheight= pwrk->segh;

	return DLO_SUCCESS;	
}

DT32_int RenderToBuf_Hebrew(pLayWrk pwrk, DT_void *para)
{
	DT32_int i, mode, ret, rtv, bEmpty;
	Str_Seg		*pss;
	DT16_ushort gidx_st=0, gidx_en=0;
	DT32_long pathsz=0;
	DLO_Point	lt;	/* Left-Top point */

DBG_MSG_SHOW_FUNC_NAME();

	mode = pwrk->rendermode;
	if( (mode&DLO_DATA_RENDER) && !(mode&DLO_DATA_PREPARE_POS) ) goto DATA_RENDER;
	else goto DATA_PREPARE_POS;

DATA_PREPARE_POS:	/* Get Ligatures & Reverse the glyphs */
	/* Get SubLookup Table */
	

	/* Fill the codeidx in gseq, gseq1, gseq2*/
	if(0==isFilter_MarksPoints_of_Hebrew){
		convHebrewUcs2gseq(pwrk);
	}else /*if(1==isFilter_MarksPoints_of_Hebrew)*/{
		convHebrewUcs2gseq_MarksPointsFiltered(pwrk);
	}

	if(pwrk->bidirule==DLO_BIDI_DCWRULE)
		ConvPunctuation_Open2Close(pwrk, pwrk->seg_start, pwrk->seg_end);

	/* Fill the DLO_Laybuf, including cseq */
	Fillawseg_IWR(pwrk);
	Fillsegarr_IWR(pwrk);

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
	  pwrk->fengtype==DLO_ENG_DIFRASTER_BYTE ){
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
}

DT32_int RenderByPos_Hebrew(pLayWrk pwrk, DT_void *para)
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
