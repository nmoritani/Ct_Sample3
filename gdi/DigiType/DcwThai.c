#include "DcwLangModule.h"
#include "DcwThai.h"
#include "DcwLayout.h"
#include "DcwBiDi.h"

/*----------------- Language Arrays -----------------*/

const DT16_ushort Thai_class[128] = {
/*0E00*/   NON,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,
/*0E10*/  CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,
/*0E20*/  CONS,CONS,CONS,CONS, FV3,CONS, FV3,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS, NON,
/*0E30*/   FV1, AV2, FV1,  AM, AV1, AV3, AV2, AV3, BV1, BV2,  BD, NON, NON, NON, NON, NON,
/*0E40*/    LV,  LV,  LV,  LV,  LV, FV2, NON, AD2,TONE,TONE,TONE,TONE, AD1, AD4, AD3, NON,
/*0E50*/   NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON,
/*0E60*/  CONS, NON, NON,CONS, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON,
/*0E70*/   NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON
};

const DT8_char Thai_input_tab[17][17] = {
		 /*CTRL, NON,CONS,  LV, FV1, FV2, FV3, BV1, BV2, AV1, AV2, AV3, AD1, AD2, AD3,  BD,TONE*/ /* Cn */
/*CTRL*/	{'X', 'A', 'A', 'A', 'A', 'A', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/* NON*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/*CONS*/	{'X', 'A', 'A', 'A', 'A', 'S', 'A', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C'},
/*  LV*/	{'X', 'S', 'A', 'S', 'S', 'S', 'S', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/* FV1*/	{'X', 'S', 'A', 'S', 'A', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/* FV2*/	{'X', 'A', 'A', 'A', 'A', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/* FV3*/	{'X', 'A', 'A', 'A', 'S', 'A', 'S', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/* BV1*/	{'X', 'A', 'A', 'A', 'A', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'C', 'R', 'R', 'R', 'C'},
/* BV2*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'C'},
/* AV1*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'C', 'R', 'R', 'R', 'C'},
/* AV2*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'C'},
/* AV3*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'C', 'R', 'R', 'C'},
/* AD1*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/* AD2*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/* AD3*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'},
/*  BD*/	{'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}, 
/*TONE*/	{'X', 'A', 'A', 'A', 'A', 'A', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'}
/*Cn-1*/
};

/*----------------------------------------------------*/


ThaiClass ThaiGetClass(DT16_ushort uc)
{
DBG_MSG_SHOW_FUNC_NAME();

    if (uc >= 0x0E00 && uc < 0x0E70)
        return (ThaiClass) Thai_class[uc-0x0E00];
    else
        return NON;
}


ThaiGroup ThaiGetGroup(DT16_ushort uc)
{
	ThaiClass tc;
	ThaiGroup rtg;

DBG_MSG_SHOW_FUNC_NAME();

	tc = ThaiGetClass(uc);
	switch(tc){
	case CTRL:
		rtg = iCTRL;	break;
	case NON:
		rtg = iNON;		break;
	case CONS:
		rtg = iCONS;	break;
	case LV:
		rtg = iLV;		break;
	case FV1:
		rtg = iFV1;		break;
	case FV2:
		rtg = iFV2;		break;
	case FV3:
		rtg = iFV3;		break;
	case BV1:
		rtg = iBV1;		break;
	case BV2:
		rtg = iBV2;		break;
	case AV1:
		rtg = iAV1;		break;
	case AV2:
		rtg = iAV2;		break;
	case AV3:
		rtg = iAV3;		break;
	case AD1:
		rtg = iAD1;		break;
	case AD2:
		rtg = iAD2;		break;
	case AD3:
		rtg = iAD3;		break;
	case BD:
		rtg = iBD;		break;
	case TONE:
		rtg = iTONE;	break;
	default:
		rtg = iNON;
	} 

	return rtg;
}

DT8_char ThaiGetShowing_Value(DT16_ushort *gs, DT32_int start, DT32_int idx)
{
	ThaiGroup cn, cn_1;

DBG_MSG_SHOW_FUNC_NAME();

	if(idx-1<start)	return 'A';
	else{
		cn_1 = ThaiGetGroup(gs[idx-1]);
		cn	 = ThaiGetGroup(gs[idx]);
		return Thai_input_tab[cn_1][cn];
	}
}

/* Should SaraAM(0x0E33) be decomposed?	*/
/* Return Value							*/
/* 0: still 0E33.						*/
/* 1: decompose to 0E4D+0E32			*/
DT32_int ThaiDecomposeSaraAM(DT16_ushort *ucs_str, DT32_int st, DT32_int i)
{
	DT32_int isDecompose=0;
	ThaiClass tcn_1=NON,tcn_2=NON;

DBG_MSG_SHOW_FUNC_NAME();

	if(i<=st)	return 0;
	
	tcn_1 = ThaiGetClass(ucs_str[i-1]);

	if(CONS==tcn_1)	isDecompose=1;
	else if( TONE==tcn_1 ){
		if(i-2>=st){	
			tcn_2 = ThaiGetClass(ucs_str[i-2]);
			if(CONS==tcn_2) isDecompose=1;
		}
	}

	return isDecompose;	/* return 1; */		/* Modified by Jacky_20100225, maybe a bug. */
}

/* make a GlyphSeq, considering the case of Sara-AM(0x0E33).									*/
DT_void ThaiMakegs(pLayWrk pwrk, DT32_int i, GlyphSeq *gs)
{
	DT16_ushort ch;
	DT32_int isDecompose=0;

DBG_MSG_SHOW_FUNC_NAME();

	ch = pwrk->attr->ucs_str[i];
	gs->idx	= i;
	gs->code= ch;
	
	switch(ch){
	case 0x0E33:
		isDecompose = ThaiDecomposeSaraAM(pwrk->attr->ucs_str,pwrk->seg_start,i);
		if( isDecompose ){
			/* make gseq1 */
			pwrk->gseq1[pwrk->cur_g1idx] = 0x0E4D;	
			pwrk->cur_g1idx++;
			pwrk->gseq1[pwrk->cur_g1idx] = 0x0E32;

			/* make gseq2*/
			pwrk->gseq2[pwrk->cur_g2idx] = 0x0E4D;	
			pwrk->cur_g2idx++;
			pwrk->gseq2[pwrk->cur_g2idx] = 0x0E32;			

			/* Prepare the gs of Glyphseq */
			/* use 0x0E32 instead of 0x0E33 */
			gs->glyf1	= 0x0E32;
			gs->n_per_glyf1 = Make_n_per_glyf(1,2);
			gs->idx_gseq1 = pwrk->cur_g1idx;

			gs->glyf2	= 0x0E32;
			gs->n_per_glyf2 = Make_n_per_glyf(1,2);
			gs->idx_gseq2 = pwrk->cur_g2idx;
			break;	/* Don't process to default. */
		}	/* if 0E33 isn't decomposed, process into default. */
	case 0x0E0D:
	case 0x0E10:
		if(i+1<pwrk->seg_end){
			DT16_ushort tmpch;
			if( isBDEAD(pwrk->attr->ucs_str[i+1]) ){
				if(0x0E0D==ch){
					tmpch = ThaiCode_NoDesc_0E0D;	/* 0x0E0D => 0x0E60 (ThaiCode_NoDesc_0E0D) */
				}else if(0x0E10==ch){
					tmpch = ThaiCode_NoDesc_0E10;	/* 0x0E10 => 0x0E63 (ThaiCode_NoDesc_0E10) */
				}
				if( pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr,tmpch,-1)!=0 ) /* chkGlyphExist() */
				{
					gs->code = ch = tmpch;									
				}
			}
		}
	default:
		pwrk->gseq1[pwrk->cur_g1idx] = ch;
		pwrk->gseq2[pwrk->cur_g2idx] = ch;

		gs->glyf1 = ch;
		gs->n_per_glyf1 = Make_n_per_glyf(1,1);
		gs->idx_gseq1 = pwrk->cur_g1idx;

		gs->glyf2 = ch;
		gs->n_per_glyf2 = Make_n_per_glyf(1,1);
		gs->idx_gseq2 = pwrk->cur_g2idx;
		break;
	}

}

/* cell1, cell2 are unicodes for a thai word cell.	*/
/* if cell2 is not exist, set it as 0.				*/
DT32_int ThaiIsDeadValid(DT16_ushort cell1, DT16_ushort cell2)
{
	ThaiClass c1, c2;

DBG_MSG_SHOW_FUNC_NAME();
	
	if( cell1==0)	return 0;
	else c1=ThaiGetClass(cell1);
	
	if(cell2==0){
	  if( (c1&AV || c1&TONE|| c1&AD || c1&BV || c1&BD) )	return 1;
	}else{
	  c2=ThaiGetClass(cell2);	/* 2008.12.16 -- added for removing warnings. */
	  if( (c1&BV1||c1&AV1) &&  (c2&TONE||c2&AD1) )	return 1;
	  if( (c1&BV2||c1&AV2) &&  (c2&TONE) )			return 1;
	  if( (c1&AV3) && (c2&TONE||c2&AD2) )			return 1;
	}
	return 0;
}

/* Check is gs[i] is in the same cell? gs is the glyph sequence. */
DT32_int ThaiIsSameCell(DT16_ushort *gs, DT32_int st, DT32_int i)
{
	DT32_int ret=0, CONSidx=-1;

DBG_MSG_SHOW_FUNC_NAME();

	if( i-1>=st ){
		if( CONS==ThaiGetClass(gs[i-1]) )
		  return 1;
		else if(i-2>=st){
		  if( CONS==ThaiGetClass(gs[i-2]) )	CONSidx = i-2;
		}
	}

	if( CONSidx>=0 ){
		ret = ThaiIsDeadValid(gs[i-1],gs[i]);
	}

	return ret;
}

/* Get Dead Code Position, seq is the glyph sequence. */
/* bdecomp means if this 0x0E4D decomposed from 0x0E33? */
/* isnextdecomp: it means that if the next glyph is 0x0E4D, does it come from Decompose(0x0E33=>0x0E4D+0x0E32). */
/* isnextdecomp will be helpful to decide the previous glyph's (TONE's) position, especially CONS+TONE+0x0E33.  */
DLO_Point ThaiGetDeadCodePos(Font_Design_Thai *fds, DT16_ushort *seq, DT32_int st, DT32_int en, DT32_int i, DT32_int bdecomp, DT32_int isnextdecomp)
{
	DLO_Point xy;		/* shift value. x is positive when moving to right, y is positive when moving down.*/
	DT32_int CONSidx=-1;		/* the index of the leading CONS*/
	DT16_ushort lc;	/* leading CONS */
	DT16_ushort dc;	/* this dead code (idx=i) */
	ThaiClass /*lcc=NON,*/ dcc=NON, tmp=NON;	/* lcc:ThaiClass of lc, dcc:ThaiClass of dc */

DBG_MSG_SHOW_FUNC_NAME();

	xy.x=0;	xy.y=0;

	dc = seq[i];
	
	dcc = ThaiGetClass(dc);

	/* Find the leading CONS */
	if( i-1<st )
		return xy;									
	else if( CONS==ThaiGetClass(seq[i-1]) )		
		CONSidx = i-1;
	else if( i-2<st )
		return xy;
	else if( CONS==ThaiGetClass(seq[i-2]) )	
		CONSidx = i-2;
	else
		return xy;

	/* a valid cell: CONS + (BV, BD, AV, AD) + (TONE,0E4C) */
	if(CONSidx>=0){
		lc = seq[CONSidx];
		//lcc = ThaiGetClass(lc);
		if(isUCONS(lc) && (dcc&AV || dcc&AD || dcc&TONE) ) xy.x = fds->Thai_Shift*(-1);

		if( i-1==CONSidx ){
		  /* After CONS (not AV or AD), TONE, AD1, AD2 have to move to Above level. */
		  if( dcc&TONE || dcc&AD1 || dcc&AD2 )	xy.y = fds->Thai_Top;
		  
		  /* If next code is 0x0E33 and need to be decomposed, TONE remain in Top level. */
		  if( dcc&TONE && i+1<=en ){
			if(isnextdecomp)
				xy.y = 0;
		  }
		}else if(i-2==CONSidx){
		  /* After CONS+(BV,BD), TONE, AD1, AD2 have to move to Above level.		*/
		  tmp = ThaiGetClass(seq[i-1]);
		  if( tmp&BV || tmp&BD )	xy.y = fds->Thai_Top;

		  /* Special case: CONS+(TONE,AD1,AD2)+0x0E33, and 0x0E33 is decomposed as 0x0E4D+0x0E32. */
		  /* The (TONE,AD1,AD2) should still be in the Top level, and 0x0E4D in Above level. */	/* Jacky_20080813 */
		  if( seq[i]==0x0E4D && bdecomp ){
			if( tmp&TONE || tmp&AD1 || tmp&AD2 )	xy.y = fds->Thai_Top;
		  }
		}
	}

	return xy;
}

/* Make the awseq. */
DT_void Fillawseg_THA(pLayWrk pwrk)
{
	DT32_int i, aw=0, ht=0, segw=0, segh=0;
	DT16_ushort ch;
	DT16_ushort c, g, idxg2=0, idxg2start=0;
	DT8_char showing;
	DT32_int samecell;
	DLO_Point p;

DBG_MSG_SHOW_FUNC_NAME();

	p.x = 0;	p.y = 0;

	idxg2start = pwrk->gseq[pwrk->seg_start].idx_gseq2;
	idxg2 = idxg2start;
	for(i=pwrk->seg_start;i<pwrk->seg_end;i++,idxg2++)
	{
		ch = pwrk->gseq[i].glyf2;
		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,ch,pwrk->gseq[i].idx_gseq2);
		ht = pwrk->fengfuncs.getAheight(pwrk->ras_attr,ch,pwrk->gseq[i].idx_gseq2);

		pwrk->awseq[i].codeidx	= i;
		pwrk->awseq[i].glyfidx = pwrk->gseq[i].idx_gseq2;
		pwrk->awseq[i].aw.vx	= aw;
		pwrk->awseq[i].aw.vy	= 0;
//		pwrk->awseq[i].direct	= DLO_LEFTTORIGHT;
		p.x = segw;		
		p.y = 0;
		pwrk->awseq[i].leftup = p;

		/* Check if it's in the same cell, and aw will be increased? */
		samecell=0;
		Parse_n_per_glyf(pwrk->gseq[i].n_per_glyf2,&c,&g);
		if(g==2){		/* 0x0E33 => 0x0E4D + 0x0E32; Only this situation in Thai */
		  if(0x0E4D==pwrk->gseq2[idxg2] && 0x0E32==pwrk->gseq2[idxg2+1])
			idxg2++;	/* Index to 0x0E32, because now it is calculating segw only. */
		}
	    showing = ThaiGetShowing_Value(pwrk->gseq2,idxg2start,idxg2);
	    if( isSameCell(showing) ){
		  samecell = ThaiIsSameCell(pwrk->gseq2,idxg2start,idxg2);
		}
		if(!samecell){
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
DT_void Fillsegarr_THA(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();

	pwrk->segarr[pwrk->seg_cnt].ustart	= pwrk->seg_start;
	pwrk->segarr[pwrk->seg_cnt].uend	= pwrk->seg_end;
	pwrk->segarr[pwrk->seg_cnt].script	= pwrk->seg_script;
	pwrk->segarr[pwrk->seg_cnt].lang	= pwrk->seg_lang;
	pwrk->segarr[pwrk->seg_cnt].sw		= pwrk->segw;
	pwrk->segarr[pwrk->seg_cnt].sh		= pwrk->segh;	
}

/* Convert from GlyfOperate to bmpGlyfOperate */
//DT_void convGlyfOperate(GlyfOperate op, bmpGlyfOperate *bop, DLO_CodePositioning codepos, Font_Design_Thai *fds)
//{
//DBG_MSG_SHOW_FUNC_NAME();
//
//	bop->bpoff.x = codepos.oripos.x;
//	bop->bpoff.y = op.rect.xy.y;	//fds->Thai_Top + fds->Thai_Above + fds->Thai_Base;
//	bop->gpoff.x = 0;
//	bop->gpoff.y = op.rect.xy.y;
//	bop->lenth = codepos.awvec.vx;
//	bop->height = op.rect.hw.vy;	//fds->Thai_Below;
//	bop->operate = DCW_SETBKZERO;
//}

/* Convert from GlyfOperate to bmpGlyfOperate *//* supports vert*/
DT_void convGlyfOperate(GlyfOperate op, bmpGlyfOperate *bop, DLO_CodePositioning codepos, Font_Design_Thai *fds)
{
DBG_MSG_SHOW_FUNC_NAME();

	bop->bpoff.x = codepos.oripos.x + op.rect.xy.x;
	bop->bpoff.y = codepos.oripos.y + op.rect.xy.y;
	bop->gpoff.x = op.rect.xy.x;
	bop->gpoff.y = op.rect.xy.y;
	bop->lenth	 = op.rect.hw.vx; //codepos.awvec.vx;
	bop->height	 = op.rect.hw.vy;
	bop->operate = DCW_SETBKZERO;
}

/*---------------------------------------------------------------------------------------------*/
DT32_int RenderToBuf_Thai(pLayWrk pwrk, DT_void *para)
{
	DT32_int ret, i, mode, rtv, bEmpty;
	GlyphSeq	gs;
	Str_Seg		*pss;
	GlyfOperate op;
	//GlyfOperate *pop;
	Font_Design_Thai *fds = (Font_Design_Thai*)&pwrk->fds;
	DT16_ushort gidx_st=0, gidx_en=0;
	DT32_long pathsz=0;
	DLO_Point	lt;	/* Left-Top point */
	bmpGlyfOperate bop;
	bmpGlyfOperate *pbop;

DBG_MSG_SHOW_FUNC_NAME();

	mode = pwrk->rendermode;
	if( (mode&DLO_DATA_RENDER) && !(mode&DLO_DATA_PREPARE_POS) ) goto DATA_RENDER;
	else goto DATA_PREPARE_POS;

DATA_PREPARE_POS:
	/* Get Font_Design_Thai Value *//* Consider to separete fd & fds, keep fd when InitShaper(), and scale to fds here. */
	pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, 0x0E01, -1, DLO_CHARATTR_LANGTAB_THAI ,fds);	//use 0x0E01 as an representation
																					//avoid to get the table from wrong FDL.

	/* Fill the codeidx in gseq, gseq1, gseq2*/
	for(i=pwrk->seg_start;i<pwrk->seg_end;i++)
	{
		ThaiMakegs(pwrk, i, &gs);	/* Make a GlyphSeq */
		pwrk->gseq[i] = gs;

		pwrk->cur_g1idx++;
		pwrk->cur_g2idx++;
	}


	/* Fill the DLO_Laybuf, including cseq */
	Fillawseg_THA(pwrk);
	Fillsegarr_THA(pwrk);

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
	for(i=gidx_st;i<=gidx_en;i++)
	{
	  pwrk->pBuf = pwrk->lobuf->olDatabuf;
	  if(pwrk->lobuf->caret_seq[i].drawmethod!=DLO_DRAW_NORMAL)
	  {
		  op.operate = pwrk->lobuf->caret_seq[i].drawmethod;
		  op.rect	 = pwrk->lobuf->caret_seq[i].dmrect;
		  /*pop		 = &op;*/
		  ret = pwrk->fengfuncs.getOutline( 
						pwrk->ras_attr,
						pwrk->lobuf->glyf_seq[i],
						&op,
						&pwrk->lobuf->olDatabufSize,
						&(pwrk->pBuf),
						&pathsz);
	  }else
	  {
		  /*pop = NULL;*/
		  ret = pwrk->fengfuncs.getOutline( 
						pwrk->ras_attr,
						pwrk->lobuf->glyf_seq[i],
						NULL,
						&pwrk->lobuf->olDatabufSize,
						&(pwrk->pBuf),
						&pathsz);
	  }
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
	  if(pwrk->lobuf->caret_seq[i].drawmethod!=DLO_DRAW_NORMAL){
		  op.operate = pwrk->lobuf->caret_seq[i].drawmethod;
		  op.rect	 = pwrk->lobuf->caret_seq[i].dmrect;
		  convGlyfOperate(op, &bop, pwrk->lobuf->caret_seq[i],fds);
		  pbop		 = &bop;
	  }else
		  pbop = NULL;

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
					pbop, 
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
	  if(pwrk->lobuf->caret_seq[i].drawmethod!=DLO_DRAW_NORMAL){
		  op.operate = pwrk->lobuf->caret_seq[i].drawmethod;
		  op.rect	 = pwrk->lobuf->caret_seq[i].dmrect;
		  convGlyfOperate(op, &bop, pwrk->lobuf->caret_seq[i],fds);
		  pbop		 = &bop;
	  }else
		  pbop = NULL;
	  
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
					pbop, 
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
	  if(pwrk->lobuf->caret_seq[i].drawmethod!=DLO_DRAW_NORMAL){
		  op.operate = pwrk->lobuf->caret_seq[i].drawmethod;
		  op.rect	 = pwrk->lobuf->caret_seq[i].dmrect;
		  convGlyfOperate(op, &bop, pwrk->lobuf->caret_seq[i],fds);
		  pbop		 = &bop;
	  }else
		  pbop = NULL;
	  
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
					pbop, 
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

DT32_int GetSeginfo_Thai(pLayWrk pwrk, Str_Seg *seginfo)
{
	DT32_int i, j, st, en, aw, aw1=0, law=0, caret=0, edget=0, edged=0, offY=0;
	DT16_ushort c, g, idxg2start, idxg2end, gidx=0;
	DLO_CodePositioning p;
	DLO_RECT rect;
	DT8_char showing;
	DT32_int samecell, bDecomp=0, bIsNextDecomp=0;
	DLO_Point lt;
	Font_Design_Thai *fds = (Font_Design_Thai*)&pwrk->fds;

DBG_MSG_SHOW_FUNC_NAME();

	st = seginfo->ustart;
	en = seginfo->uend;
	if(pwrk->lobuf->writedir == DLO_LEFTTORIGHT)	caret = seginfo->cpstart.x;
	else if(pwrk->lobuf->writedir == DLO_RIGHTTOLEFT)caret = seginfo->cpstart.x - seginfo->sw;
	else caret = seginfo->cpstart.x;

	idxg2start=pwrk->gseq[st].idx_gseq2;	gidx = idxg2start;
	idxg2end  =pwrk->gseq[en-1].idx_gseq2;
	rect.xy.x =rect.xy.y =0;
	rect.hw.vx=rect.hw.vy=0;
	c=1; g=1;
	for(i=st;i<en;i+=c){
	  aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,pwrk->gseq[i].glyf2,pwrk->gseq[i].idx_gseq2);
	  offY = need_Move_Down_Pixs(pwrk, pwrk->gseq[i].glyf2,pwrk->gseq[i].idx_gseq2);
		
	  /* Check if next is decomposed. */
	  if(i+1<en){
		Parse_n_per_glyf(pwrk->gseq[i+1].n_per_glyf2,&c,&g);
		if(2==g)
		  bIsNextDecomp = 1;
		else
		  bIsNextDecomp = 0;
	  }
	  /* Get the count of codes and glyphs. */
	  Parse_n_per_glyf(pwrk->gseq[i].n_per_glyf2,&c,&g);

	  /* Make DLO_CodePositioning for every glyf */
	  for(j=0;j<g;j++,gidx++){
		lt.x = lt.y = 0;
		pwrk->lobuf->glyf_seq[gidx] = pwrk->gseq2[gidx];
		samecell=0;
		showing = ThaiGetShowing_Value(pwrk->gseq2,idxg2start,gidx);
		if( isSameCell(showing) ){
		  samecell = ThaiIsSameCell(pwrk->gseq2,idxg2start,gidx);
		}
		
		if(2==g && 0==j){	/* 0x0E33 => 0x0E4D + 0x0E32: 0x0E4D will be in the same cell. */
		  samecell = 1;	/* force to show 0x0E4D in the same cell. */
		  bDecomp  = 1;		  
		}else{
		  bDecomp  = 0;
		}
		
		p.codeidx = i;
		p.glyfidx = gidx;
		p.n_per_glyf = (0==j)?pwrk->gseq[i].n_per_glyf2:0;//Set the first glyf to n_per_glyf2, others are 0
		if( samecell ){
			aw1 = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,pwrk->gseq2[gidx],gidx);
			lt = ThaiGetDeadCodePos(fds,pwrk->gseq2,idxg2start,idxg2end,gidx,bDecomp,bIsNextDecomp);
			caret += 0;
			p.oripos.x = caret-aw1+lt.x;//(bDecomp)?(caret-aw1+lt.x):(caret-aw1+lt.x);
			p.oripos.y = 0 + lt.y + offY;	//0 + lt.y;
			p.adjvec.vx	= lt.x;
			p.adjvec.vy = lt.y;
		}else{
			law = aw;
			caret += aw;
			p.oripos.x = caret - aw;
			p.oripos.y = 0  + offY;	//0;
			p.adjvec.vx	= 0;
			p.adjvec.vy = 0;
		}
		p.caretpos.x= caret;
		p.caretpos.y= 0;
		p.awvec.vx	= aw;
		p.awvec.vy	= 0;

		p.drawmethod= DLO_DRAW_NORMAL;
		p.dmrect	= rect;
		/* For SCONS+(BV,BD), don't draw the below area. */
		if(gidx<idxg2end){
		  if( isSCONS(pwrk->gseq2[gidx]) ){
		    if(isBDEAD(pwrk->gseq2[gidx+1])){
			  DT32_int halfedged;	// Jacky_20110803 for edged
			  pwrk->fengfuncs.getEdge(pwrk->ras_attr,&edget,&edged,NULL,NULL);
			  p.drawmethod = DLO_AREA_NOT_DRAW;
			  if(pwrk->vert){
				halfedged = edged/2;
				p.dmrect.xy.x =0;	
				p.dmrect.xy.y =0;
				p.dmrect.hw.vx=fds->Thai_Below + halfedged /*edged*/;
				p.dmrect.hw.vy=pwrk->fengfuncs.getAwidth(pwrk->ras_attr,pwrk->gseq2[gidx],gidx)+pwrk->fengfuncs.getAexten(pwrk->ras_attr,pwrk->gseq2[gidx]);
			  }else{
				halfedged = (edged+1)/2;
				p.dmrect.xy.x =0;	
				p.dmrect.xy.y =edget + fds->Thai_Top + fds->Thai_Above + fds->Thai_Base + halfedged /*edged*/; // Jacky_20101102_for_Baseline
				p.dmrect.hw.vx=pwrk->fengfuncs.getAwidth(pwrk->ras_attr,pwrk->gseq2[gidx],gidx)+pwrk->fengfuncs.getAexten(pwrk->ras_attr,pwrk->gseq2[gidx]);
				p.dmrect.hw.vy=fds->Thai_Below + (edged-halfedged) /*edged*/;
			  }
			}
		  }
		}

		pwrk->lobuf->caret_seq[gidx] = p;
	  }
	}

	seginfo->cpend.x = caret;
	seginfo->cpend.y = 0;

	return DLO_SUCCESS;
}

DT32_int CalcPosition_Thai(pLayWrk pwrk, DT_void *para)
{
	DT32_int aw1=0, law=0, edget=0, edged=0, offY=0;
	DT8_char showing;
	DT32_int samecell, bDecomp=0, bIsNextDecomp=0;
	DLO_Point lt;
	Font_Design_Thai *fds = (Font_Design_Thai*)&pwrk->fds;
	
	DT16_ushort nowglyph, nextglyph, nextnextglyph;
	DT32_int j, aw, ht, caret, lastpoint_aw=0;
	DLO_CodePositioning *nowp = NULL;
	DLO_RECT rect;

DBG_MSG_SHOW_FUNC_NAME();

//	if(pwrk->vert)
//		return CalcPosition_Thai_vert(pwrk,para);

	/* calculate the position information. */
	caret = pwrk->linewidth;
	pwrk->segw = caret;		// keep the start caret pos.

	rect.xy.x =rect.xy.y =0;
	rect.hw.vx=rect.hw.vy=0;
	for(j=pwrk->seg_start;j<pwrk->seg_end;j++){
	  nowglyph = pwrk->lobuf->glyf_seq[j];
	  if(j+1<pwrk->seg_end){
		  nextglyph = pwrk->lobuf->glyf_seq[j+1];
		  if(nextglyph==0x0E4D && j+2<pwrk->seg_end)
		  {
			  nextnextglyph = pwrk->lobuf->glyf_seq[j+2];
		  }else
			  nextnextglyph = 0;
	  }
	  else
	  {
		  nextglyph = 0;
		  nextnextglyph = 0;
	  }

	  nowp = &pwrk->lobuf->caret_seq[j];
	  
	  aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph,j);
	  ht = pwrk->fengfuncs.getAheight(pwrk->ras_attr,nowglyph,j);
	  offY = need_Move_Down_Pixs(pwrk, nowglyph,j);
	  /* Check if next is decomposed. */
	  if(nextnextglyph==0x0E32 && nextglyph==0x0E4D){
		  bIsNextDecomp = 1;
	  }else
		  bIsNextDecomp = 0;

	  samecell=0;
	  showing = ThaiGetShowing_Value(pwrk->lobuf->glyf_seq,pwrk->seg_start,j);
	  if( isSameCell(showing) ){
		  samecell = ThaiIsSameCell(pwrk->lobuf->glyf_seq,pwrk->seg_start,j);
	  }
	  if(nowglyph==0x0E4D && nextglyph==0x0E32){	/* 0x0E33 => 0x0E4D + 0x0E32: 0x0E4D will be in the same cell. */
		  samecell = 1;	/* force to show 0x0E4D in the same cell. */
		  bDecomp  = 1;		  
	  }else{
		  bDecomp  = 0;
	  }

		lt.x = lt.y = 0;
	  	if( samecell ){
			aw1 = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph,j);
			lt = ThaiGetDeadCodePos(fds,pwrk->lobuf->glyf_seq,pwrk->seg_start,pwrk->seg_end,j,bDecomp,bIsNextDecomp);
			caret += 0;
			nowp->oripos.x = caret-aw1+lt.x;//(bDecomp)?(caret-aw1+lt.x):(caret-aw1+lt.x);
			nowp->oripos.y = pwrk->vert?(0-lt.y+offY):(0+lt.y+offY);	//0 + lt.y + offY;	//0 + lt.y;
			nowp->adjvec.vx	= lt.x;
			nowp->adjvec.vy = lt.y;
		}else{
			law = aw;
			caret += aw;
			nowp->oripos.x = caret - aw;
			nowp->oripos.y = 0  + offY;	//0;
			nowp->adjvec.vx	= 0;
			nowp->adjvec.vy = 0;
		}
		nowp->caretpos.x= caret;
		nowp->caretpos.y= 0;
		nowp->awvec.vx	= aw;
		nowp->awvec.vy	= 0;

		nowp->drawmethod= DLO_DRAW_NORMAL;
		nowp->dmrect	= rect;
		/* For SCONS+(BV,BD), don't draw the below area. */
		if(j<pwrk->seg_end){
		  if( isSCONS(nowglyph) ){
		    if( j+1<pwrk->seg_end && isBDEAD(nextglyph)){
			  DT32_int halfedged;	// Jacky_20110803 for edged
			  pwrk->fengfuncs.getEdge(pwrk->ras_attr,&edget,&edged,NULL,NULL);
			  nowp->drawmethod = DLO_AREA_NOT_DRAW;
			  if(pwrk->vert){
				halfedged = edged/2;
				nowp->dmrect.xy.x =0;	
				nowp->dmrect.xy.y =0;	//fds->Thai_Top + fds->Thai_Above + fds->Thai_Base + edged;
				nowp->dmrect.hw.vx=fds->Thai_Below + halfedged /*edged*/; //pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph)+pwrk->fengfuncs.getAexten(pwrk->ras_attr,nowglyph);
				nowp->dmrect.hw.vy=pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph,j)+pwrk->fengfuncs.getAexten(pwrk->ras_attr,nowglyph); //fds->Thai_Below+edged;
			  }else{
				halfedged = (edged+1)/2;
				nowp->dmrect.xy.x =0;	
				nowp->dmrect.xy.y =fds->Thai_Top + fds->Thai_Above + fds->Thai_Base + halfedged /*edged*/; // Jacky_20101102_for_Baseline
				nowp->dmrect.hw.vx=pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph,j)+pwrk->fengfuncs.getAexten(pwrk->ras_attr,nowglyph);
				nowp->dmrect.hw.vy=fds->Thai_Below + (edged-halfedged) /*edged*/;
			  }
			}
		  }
		}
		if(ht > pwrk->segh){
		  pwrk->segh = ht;
		}
	} // end for
	

	pwrk->linewidth = caret;
	if(0 == pwrk->linewidth - pwrk->segw)	// only one ZEROWIDTH char
		pwrk->linewidth += lastpoint_aw;

	pwrk->segw = pwrk->linewidth - pwrk->segw;	// now caret - start caret = segw.
	if(pwrk->segh > pwrk->lineheight)
		pwrk->lineheight= pwrk->segh;

	return DLO_SUCCESS;	
}

DT32_int RenderByPos_Thai(pLayWrk pwrk, DT_void *para)
{
	DT32_int	ret, rtv = DLO_SUCCESS, bEmpty = 0, opengine;
	DT16_ushort i, gidx_st, gidx_en;
	DLO_Point	lt;
	DT32_long	pathsz=0;
	GlyfOperate	op;
	bmpGlyfOperate bop;
	bmpGlyfOperate *pbop;
	Font_Design_Thai *fds = (Font_Design_Thai*)&pwrk->fds;

DBG_MSG_SHOW_FUNC_NAME();

#ifdef DIGITYPE_OUL
  if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
	gidx_st = pwrk->seg_start;
	gidx_en = pwrk->seg_end;
	for(i=gidx_st;i<gidx_en;i++){
	  pwrk->pBuf = pwrk->lobuf->olDatabuf;
	  if(pwrk->lobuf->caret_seq[i].drawmethod!=DLO_DRAW_NORMAL)
	  {
		  op.operate = pwrk->lobuf->caret_seq[i].drawmethod;
		  op.rect	 = pwrk->lobuf->caret_seq[i].dmrect;
		  /*pop		 = &op;*/
		  ret = pwrk->fengfuncs.getOutline( 
						pwrk->ras_attr,
						pwrk->lobuf->glyf_seq[i],
						&op,
						&pwrk->lobuf->olDatabufSize,
						&(pwrk->pBuf),
						&pathsz);
	  }else
	  {
		  /*pop = NULL;*/
		  ret = pwrk->fengfuncs.getOutline( 
						pwrk->ras_attr,
						pwrk->lobuf->glyf_seq[i],
						NULL,
						&pwrk->lobuf->olDatabufSize,
						&(pwrk->pBuf),
						&pathsz);
	  }
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
	  if(pwrk->lobuf->caret_seq[i].drawmethod!=DLO_DRAW_NORMAL){
		  op.operate = pwrk->lobuf->caret_seq[i].drawmethod;
		  op.rect	 = pwrk->lobuf->caret_seq[i].dmrect;
		  convGlyfOperate(op, &bop, pwrk->lobuf->caret_seq[i],fds);
		  pbop		 = &bop;
	  }else
		  pbop = NULL;
	  
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
					pbop, 
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
