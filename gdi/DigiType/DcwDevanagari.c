#include "DcwDevanagari.h"
#include "DcwLangModule.h"
#include "Devanagari_render.h"
#include "DTmanager.h"
#include "DcwLayout.h"
#include "DcwBiDi.h"


#define DEVA_RATIO		DCW_SCALED_SIZEXY(pwrk->xsize,pwrk->ratio)/512	
#define DEVA_RATIO_VG	DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE,pwrk->ratio)/512
#define RSB_RATIO(szX)	DCW_SCALED_SIZEXY((szX),pwrk->ratio)/1000	
//#define RSB_RATIO_VG	DCW_SCALED_SIZEXY(gDT_FONT_EMSIZE,pwrk->ratio)/1000
#define EMPTY_OFFSET	0x7FFF


DT32_int IsDevanagari(DT16_ushort ch)
{
	if (ch>=0x0900 && ch<=0x097F)
		return 1;
	else
	if ((ch>=0xE300 && ch<=0xE308)||
		(ch>=0xEf00 && ch<=0xEfff)|| 
		(ch>=0xf200 && ch<=0xf3ff)||
		(ch>=0x200c && ch<=0x200d))
		return 2;
	else if(ch == 0x25cc)
		return 3;
	else
		return 0;
}

static DT32_int getAnchorPairClass1Adjustment(pLayWrk pwrk, ALL_TBL * p_all_table ,UNI_CHAR base, UNI_CHAR sign,  DT16_short *poffsetx, DT16_short *poffsety)
{
	DT32_int ret;
	DT16_short ofsx, ofsy;

	ret = -1;
	*poffsetx = 0;
	*poffsety = 0;

	if(p_all_table->p_gup_pos_table)
	{	
		ret = getPosAdjustment_st(p_all_table->p_gup_pos_table, base, sign, &ofsx, &ofsy,0,7);

		if(ret>=0)
		{
			*poffsetx = ofsx;
			*poffsety = ofsy;
		}else
		{
			if(p_all_table->p_gup_pos_table2)
			{
				ret = getPosAdjustment_st(p_all_table->p_gup_pos_table2, base, sign, &ofsx, &ofsy,0,7);
			}
			if(ret>=0)
			{
				*poffsetx = ofsx;
				*poffsety = ofsy;
			}else;
		}
	}
	return ret;
}

static DT32_int getAnchorPairClass2Adjustment(pLayWrk pwrk, ALL_TBL * p_all_table, UNI_CHAR base, UNI_CHAR sign, DT16_short *poffsetx, DT16_short *poffsety)
{
	DT32_int ret;
	DT16_short ofsx, ofsy;
	ret = -1;
	*poffsetx = 0;
	*poffsety = 0;

	if(p_all_table->p_gup_pos_table2)
	{
		ret = getPosAdjustment_st(p_all_table->p_gup_pos_table2, base, sign, &ofsx, &ofsy,8,12);
	}
	if(ret>=0)
	{
		*poffsetx = ofsx;
		*poffsety = ofsy;
	}else;

	return ret;
}

static DT32_int getAnchorPairClass3Adjustment(pLayWrk pwrk, ALL_TBL * p_all_table, UNI_CHAR base, UNI_CHAR sign, DT16_short *poffsetx, DT16_short *poffsety)
{
	DT32_int ret;
	DT16_short ofsx, ofsy;

	ret = -1;
	*poffsetx = 0;
	*poffsety = 0;

	if(p_all_table->p_gup_pos_table3)
	{	/*PV*/
		ret = getPosAdjustment_st(p_all_table->p_gup_pos_table3, base, sign, &ofsx, &ofsy,0,0);

		if(ret>=0)
		{
			*poffsetx = ofsx;
			*poffsety = ofsy;
		}else;
	}
	return ret;
}

static DT32_int getAnchorPairClassAdjustment_16to17(pLayWrk pwrk, ALL_TBL * p_all_table, UNI_CHAR base, UNI_CHAR sign, DT16_short *poffsetx, DT16_short *poffsety)
{
	DT32_int ret;
	DT16_short ofsx, ofsy;
	ret = -1;
	*poffsetx = 0;
	*poffsety = 0;

	if(p_all_table->p_gup_pos_table2)
	{
		ret = getPosAdjustment_st(p_all_table->p_gup_pos_table2, base, sign, &ofsx, &ofsy, 8, 9);
	}
	if(ret>=0)
	{
		*poffsetx = ofsx;
		*poffsety = ofsy;
	}else;

	return ret;
}

static DT32_int getAnchorPairClassAdjustment_18to19(pLayWrk pwrk, ALL_TBL * p_all_table, UNI_CHAR base, UNI_CHAR sign, DT16_short *poffsetx, DT16_short *poffsety)
{
	DT32_int ret;
	DT16_short ofsx =0, ofsy =0;

	ret = -1;
	*poffsetx = 0;
	*poffsety = 0;
	if(p_all_table->p_gup_pos_table2)
	{
		ret = getPosAdjustment_st(p_all_table->p_gup_pos_table2, base, sign, &ofsx, &ofsy, 10, 11);
	}
	if(ret>=0)
	{
		*poffsetx = ofsx;
		*poffsety = ofsy;
	}else;
	return ret;
}

static DT32_int getAnchorPairClassAdjustment_21to21(pLayWrk pwrk, ALL_TBL * p_all_table, UNI_CHAR base, UNI_CHAR sign, DT16_short *poffsetx, DT16_short *poffsety)
{
	DT32_int ret;
	DT16_short ofsx=0, ofsy=0;

	ret = -1;
	*poffsetx = 0;
	*poffsety = 0;

	if(p_all_table->p_gup_pos_table2)
	{
		ret = getPosAdjustment_st(p_all_table->p_gup_pos_table2, base, sign, &ofsx, &ofsy,12,12);
	}
	if(ret>=0)
	{
		*poffsetx = ofsx;
		*poffsety = ofsy;
	}else;
	return ret;
}


void getIndicTable(pLayWrk pwrk, ALL_TBL * p_all_table)
{

	DT8_char *ptable;
	p_all_table->process_switch = 0;
	p_all_table->p_gup_pos_table = 0;
	p_all_table->p_gup_pos_table2 =0 ;
	p_all_table->p_gup_pos_table3 = 0;
	p_all_table->p_gup_vowel_sub_table = 0;

	if(NULL!=pwrk->fengfuncs.getDesignGlobalInfo)
	{
		/*read position table.*/
		if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, 0x0915, DLO_LANGTAB_HINDI_SUB, (DT_void**)&ptable))
		{
			p_all_table->p_gup_vowel_sub_table = ptable+6;
		}
		if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, 0x0915, DLO_LANGTAB_HINDI_POS1,(DT_void**) &ptable))
		{
			p_all_table->p_gup_pos_table = ptable+6;
		}
		if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, 0x0915, DLO_LANGTAB_HINDI_POS2,(DT_void**) &ptable))
		{
			p_all_table->p_gup_pos_table2 = ptable+6;
		}
		if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, 0x0915, DLO_LANGTAB_HINDI_POS3, (DT_void**)&ptable))
		{
			p_all_table->p_gup_pos_table3 = ptable+6;
		}
	}
}


int GetSeginfo_Devanagari(pLayWrk pwrk, Str_Seg *seginfo)
{
/*
	The memory buffers to do record something.
	They represent that
	1.pwrk->gseq->n_per_glyf1;     --Bytes of per syllable in the ucs_str.
	2.pwrk->gseq->n_per_glyf2;     --Bytes of per syllable in the gseq2.
	3.pwrk->gseq[seginfo->ustart].code;     --The count of gseq.
	4.pwrk->gseq[seginfo->ustart].idx;      --pre-section, pwrk->cur_g2idx.
*/
	DT32_int i,j,q,caret=0;
	DT32_int offset_ucs_str = seginfo->ustart;
	DT32_int offset_aw = seginfo->ustart;
	DT16_ushort offset_gseq2 = pwrk->gseq[seginfo->ustart].idx;
	DT32_int count_glyph;
	DLO_CodePositioning * p_odl_code_positioning;
	DT32_int oriposx,aw;

	

	if(pwrk->lobuf->writedir == DLO_LEFTTORIGHT)
	{
		caret = seginfo->cpstart.x;
	}
	else if(pwrk->lobuf->writedir == DLO_RIGHTTOLEFT)
	{
		caret = seginfo->cpstart.x - seginfo->sw;
	}

	oriposx = caret;
	
	for(i=seginfo->ustart; i< pwrk->gseq[seginfo->ustart].code + seginfo->ustart; i++)
	{
		/*fill the cseq of syllable.*/
		p_odl_code_positioning = &(pwrk->lobuf->caret_seq[offset_gseq2]);

		for(j=0; j< pwrk->gseq[i].n_per_glyf2; j++)
		{
			q = j+offset_gseq2;
			aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, pwrk->gseq2[offset_gseq2+j],offset_gseq2+j);
			p_odl_code_positioning->codeidx = offset_ucs_str;
			p_odl_code_positioning->glyfidx = offset_gseq2;
			p_odl_code_positioning->caretpos.x = caret;
			p_odl_code_positioning->caretpos.y = 0;
			p_odl_code_positioning->n_per_glyf = (DT16_ushort) ((pwrk->gseq[i].n_per_glyf2 << 8) | (pwrk->gseq[i].n_per_glyf1));
			p_odl_code_positioning->oripos.x = oriposx + pwrk->fnt_pos[q].leftup.x + pwrk->fnt_pos[q].offx;
			p_odl_code_positioning->oripos.y = pwrk->fnt_pos[q].leftup.y;
// 2011-11-08: Jacky marked it. MoveY should be contained in FDL data.
//			if(pwrk->vert)
//			{
//				if(IsDevanagari(pwrk->gseq2[offset_gseq2+j]) >0){
//					//p_odl_code_positioning->oripos.x += 29*pwrk->xsize/256;//240-211=29
//					p_odl_code_positioning->oripos.y -= 29*pwrk->xsize/256;//240-211=29
//				}
//			}
//			else
//			{
//				if(IsDevanagari(pwrk->gseq2[offset_gseq2+j]) >0){
//					p_odl_code_positioning->oripos.y -= 29*pwrk->ysize/256;
//				}
//			}
			p_odl_code_positioning->awvec.vx = aw;
			p_odl_code_positioning->awvec.vy = 0;
			p_odl_code_positioning->adjvec.vx = 0;
			p_odl_code_positioning->adjvec.vy = 0;
			p_odl_code_positioning->drawmethod= DLO_DRAW_NORMAL;
			p_odl_code_positioning->dmrect.hw.vx =0;
			p_odl_code_positioning->dmrect.hw.vy =0;
			p_odl_code_positioning->dmrect.xy.x =0;
			p_odl_code_positioning->dmrect.xy.y =0;
			p_odl_code_positioning++;
		}
		/*count syllable's caret.*/
		for(j=0; j<pwrk->gseq[i].n_per_glyf2; j++)
		{
			caret = caret+ (pwrk->fnt_pos[offset_aw+j].aw.vx);
		}
		offset_ucs_str += pwrk->gseq[i].n_per_glyf1;
		offset_gseq2 += pwrk->gseq[i].n_per_glyf2;
		offset_aw += pwrk->gseq[i].n_per_glyf2;
	}

	/*copy the glyph idx to pwrk->lobuf->glyf_seq*/
	count_glyph = 0;
	for(i=seginfo->ustart; i< pwrk->gseq[seginfo->ustart].code + seginfo->ustart; i++)
	{
		count_glyph += pwrk->gseq[i].n_per_glyf2;
	}

	
	offset_gseq2 = pwrk->gseq[seginfo->ustart].idx;
	count_glyph+=offset_gseq2;
	for(i=offset_gseq2;i<count_glyph;i++)
	{
		pwrk->lobuf->glyf_seq[i] = pwrk->gseq2[i];
	}

	seginfo->cpend.x = caret;
	seginfo->cpend.y = 0;
	return 0;
}



DT32_int CalcPosition_Devanagari(pLayWrk pwrk, DT_void *para)
{
	
	DT16_ushort nowglyph, preglyph, pre_pre_glyph, main_glyph;
	DT32_int j, aw, ht, caret, lastcaret, syll_org_x, pre_syll_org_x;
	DT32_int mark_org_x=0, mark_org_y=0;
	DT32_int mark_org_y_non_decent;
	DLO_RECT rect;
	DT16_short offsetx, offsety;
	ALL_TBL all_table, * p_all_table;
	DT32_int ret_adj, ret_adj_spec,is_prev;
	DT32_int rsb, fontszX;
	Font_LRSB font_lrsb;
	DT32_int state =0;
	font_lrsb.nsLsb = 0;
	font_lrsb.nsRsb = 0;
	
#define STATE_POS_MATCH_NON (0)
#define STATE_POS_MATCH_CLASS_CONS (1)
#define STATE_POS_MATCH_CLASS_SUB (2)
#define STATE_POS_MATCH_CLASS_NUKTA (3)
#define STATE_POS_MATCH_CLASS_ANUDATTA (4)
#define STATE_POS_MATCH_CLASS_MARKMARK (5)

DBG_MSG_SHOW_FUNC_NAME();

getIndicTable(pwrk, &all_table);
p_all_table = &all_table; 

	if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
		fontszX = gDT_FONT_EMSIZE;
	else
		fontszX = pwrk->xsize;

	/* calculate the position information. */
	syll_org_x = lastcaret = caret = pwrk->linewidth;
	pwrk->segw = caret;			// keep the start caret pos.

	rect.xy.x =rect.xy.y =0;
	rect.hw.vx=rect.hw.vy=0;
	ht = 0;

	nowglyph = 0; preglyph =0, pre_pre_glyph=0;
	pre_syll_org_x = 0;
	
/*
*/
	/*the character at the first postion do check lsb,rsb to avoid */
 	if(pwrk->seg_start<pwrk->seg_end)
	{
		j = pwrk->seg_start;
		nowglyph = pwrk->lobuf->glyf_seq[j];
		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph,j);
		ht = pwrk->fengfuncs.getAheight(pwrk->ras_attr,nowglyph,j);
		pwrk->lobuf->caret_seq[j].oripos.x = syll_org_x;
		pwrk->lobuf->caret_seq[j].oripos.y = 0 + need_Move_Down_Pixs(pwrk, nowglyph, j);
		pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
		pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
		pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
		pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
		pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
		pwrk->lobuf->caret_seq[j].dmrect	= rect;
		pwrk->lobuf->caret_seq[j].caretpos.x = syll_org_x+aw;
		pwrk->lobuf->caret_seq[j].caretpos.y = 0;	

		if(ht > pwrk->segh){
			 pwrk->segh = ht;
		}

		if(aw!=0){
			caret+=aw;
		}else
		{
			if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, j, DLO_LANGTAB_RSB, &font_lrsb))
			{
				aw = -(font_lrsb.nsLsb+font_lrsb.nsRsb) * RSB_RATIO(fontszX);

			}else{
				aw = 0;
			}
			if(aw>0)
			{
				pwrk->lobuf->caret_seq[j].oripos.x = syll_org_x- (font_lrsb.nsLsb * RSB_RATIO(fontszX));
				pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
				pwrk->lobuf->caret_seq[j].caretpos.x = syll_org_x+aw;
				caret+=aw;
			}
	    }
	
		pre_syll_org_x = pwrk->lobuf->caret_seq[j].oripos.x;
	}

	for(j=pwrk->seg_start+1;j<pwrk->seg_end;j++)
	{
		nowglyph = pwrk->lobuf->glyf_seq[j];
	    preglyph = pwrk->lobuf->glyf_seq[j-1];
		state = STATE_POS_MATCH_NON;
		if( (nowglyph == 0x200d && preglyph == 0x093f) || (nowglyph == 0x200c && preglyph == 0x093f) )
		{
			if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, preglyph, j-1, DLO_LANGTAB_RSB, &font_lrsb))
			{
				aw = -(font_lrsb.nsLsb+font_lrsb.nsRsb) * RSB_RATIO(fontszX);

			}else{
				aw = 0;
			}
			aw -= pwrk->fengfuncs.getAwidth(pwrk->ras_attr, preglyph, j-1);
		}
		else{
			aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph, j);
		}
	    ht = pwrk->fengfuncs.getAheight(pwrk->ras_attr,nowglyph, j);
		pwrk->lobuf->caret_seq[j].oripos.x	= caret;
		pwrk->lobuf->caret_seq[j].oripos.y	= 0 + need_Move_Down_Pixs(pwrk, nowglyph, j); 
		pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
		pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
		pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
		pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
		pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
		pwrk->lobuf->caret_seq[j].dmrect	= rect;
		pwrk->lobuf->caret_seq[j].caretpos.x = syll_org_x+aw;
		pwrk->lobuf->caret_seq[j].caretpos.y = 0;

		caret += aw;
		
		if(ht > pwrk->segh){
			  pwrk->segh = ht;
		}
		//caret is decided here.
		pwrk->lobuf->caret_seq[j].caretpos.x = caret;
		pwrk->lobuf->caret_seq[j].caretpos.y = 0;


		/**/
	    ret_adj = -1;		
		main_glyph = preglyph;
		syll_org_x = pwrk->lobuf->caret_seq[j].oripos.x;

		/*check the syllable whether  has 0x093f  to decide check PV table or not.*/
		if((pre_pre_glyph == 0x093f ) || (0xf37b <= pre_pre_glyph && pre_pre_glyph <= 0xF3A8 ) || (0xf3b2<= pre_pre_glyph && pre_pre_glyph<=0xf3bc))/*normal lookup- 0x093f*//*may be this can lookpu sub-table.*/
		{
			is_prev =1;
		}
		else
		{
			is_prev =0;
		}
		/*
			table 0~15 & PV
		*/
		do{
			ret_adj = -1;
			if(1==is_prev)
			{
				ret_adj = getAnchorPairClass3Adjustment(pwrk, p_all_table, main_glyph, nowglyph, &offsetx, &offsety);	
				if(ret_adj<0){
					ret_adj = getAnchorPairClass1Adjustment(pwrk, p_all_table, main_glyph, nowglyph, &offsetx, &offsety);
				}
			}
			else
			{
				ret_adj = getAnchorPairClass1Adjustment(pwrk, p_all_table, main_glyph, nowglyph, &offsetx, &offsety);
			}
			if(ret_adj>=0){
					
				if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
					mark_org_y_non_decent = offsety*DEVA_RATIO_VG;
					pwrk->lobuf->caret_seq[j].oripos.x = pre_syll_org_x + offsetx * DEVA_RATIO_VG;
				}
				else{
					mark_org_y_non_decent = offsety*DEVA_RATIO;
					pwrk->lobuf->caret_seq[j].oripos.x = pre_syll_org_x + offsetx * DEVA_RATIO;

				}
					pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y_non_decent + need_Move_Down_Pixs(pwrk, nowglyph, j);
					pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
					pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
					pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
					pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
					pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
					pwrk->lobuf->caret_seq[j].dmrect	= rect;
					mark_org_x = pwrk->lobuf->caret_seq[j].oripos.x;
					mark_org_y = mark_org_y_non_decent;
					/*next loop*/
					j++;
					if(j>=pwrk->seg_end)
						break;
					pre_pre_glyph = preglyph;
					preglyph = nowglyph;
					nowglyph = pwrk->lobuf->glyf_seq[j];
					state = STATE_POS_MATCH_CLASS_CONS;
					/*Is it mark to mark or not?*/
					if(nowglyph== 0x0952)
					{							
						ret_adj_spec = getAnchorPairClassAdjustment_21to21(pwrk, p_all_table, preglyph, nowglyph, &offsetx, &offsety);
						if(ret_adj_spec >=0)
						{
							state = STATE_POS_MATCH_CLASS_ANUDATTA;
							break;
						}
					}
					else if(preglyph == 0xef12) 
					{
						ret_adj_spec = getAnchorPairClassAdjustment_16to17(pwrk, p_all_table, preglyph, nowglyph, &offsetx, &offsety);
						if(ret_adj_spec >=0)
						{
							state = STATE_POS_MATCH_CLASS_SUB;
							break;
						}
						
					}else if(preglyph==0x093c)
					{

						ret_adj_spec = getAnchorPairClassAdjustment_18to19(pwrk, p_all_table, preglyph, nowglyph, &offsetx, &offsety);
						if(ret_adj_spec >=0)
						{
							state = STATE_POS_MATCH_CLASS_NUKTA;
							break;
						}
					}

			}
			else;
		}while(ret_adj>=0);

		/*
			table 16~20
		*/
		switch(state)
		{
			case STATE_POS_MATCH_CLASS_CONS:
					j--;
					preglyph = pre_pre_glyph;
					state = STATE_POS_MATCH_CLASS_MARKMARK;
					break;

			case STATE_POS_MATCH_CLASS_NUKTA:
					if(pwrk->fengtype==DLO_ENG_DCWOPENVG){			
						mark_org_y_non_decent = mark_org_y + offsety*DEVA_RATIO_VG;
						pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO_VG;
					}
					else{
						mark_org_y_non_decent = mark_org_y + offsety*DEVA_RATIO;
						pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO;
					}
					pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y_non_decent + need_Move_Down_Pixs(pwrk, nowglyph, j);
					pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
					pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
			        pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
			        pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
			        pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
			        pwrk->lobuf->caret_seq[j].dmrect	= rect;
					mark_org_x = pwrk->lobuf->caret_seq[j].oripos.x;
					mark_org_y = mark_org_y_non_decent;
					j++;
					if(j < pwrk->seg_end)
					{
						pre_pre_glyph = preglyph;
						preglyph = nowglyph;
						nowglyph = pwrk->lobuf->glyf_seq[j];

						ret_adj_spec = getAnchorPairClassAdjustment_16to17(pwrk, p_all_table, preglyph, nowglyph, &offsetx, &offsety);
						if(ret_adj_spec >=0)
						{
							if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
								mark_org_y_non_decent =  mark_org_y + offsety*DEVA_RATIO_VG;
								pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO_VG;

							}else{
								mark_org_y_non_decent =  mark_org_y + offsety*DEVA_RATIO;
								pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO;
							}
							pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y_non_decent + need_Move_Down_Pixs(pwrk, nowglyph, j);
							pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
							pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
							pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
							pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
							pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
							pwrk->lobuf->caret_seq[j].dmrect	= rect;
							mark_org_x = pwrk->lobuf->caret_seq[j].oripos.x;
							mark_org_y = mark_org_y_non_decent;
							j++;
							pre_pre_glyph = preglyph;
							preglyph = nowglyph;
							nowglyph = pwrk->lobuf->glyf_seq[j];
							if(j < pwrk->seg_end)
								break;
						}else;
					
						ret_adj_spec = getAnchorPairClassAdjustment_21to21(pwrk, p_all_table, preglyph, nowglyph, &offsetx, &offsety);
						if(ret_adj_spec >=0){
							if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
								pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO_VG;
								pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y + offsety*DEVA_RATIO_VG + need_Move_Down_Pixs(pwrk, nowglyph, j);
							}else{
								pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO;
								pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y + offsety*DEVA_RATIO + need_Move_Down_Pixs(pwrk, nowglyph, j);
							}
							pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
							pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
							pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
							pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
							pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
							pwrk->lobuf->caret_seq[j].dmrect	= rect;
						}
						else{	
							j--;
							preglyph = pre_pre_glyph;
						}
					}
					state = STATE_POS_MATCH_CLASS_MARKMARK;
					break;

			case STATE_POS_MATCH_CLASS_SUB:

					if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
						mark_org_y_non_decent = mark_org_y + offsety*DEVA_RATIO_VG;
						pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO_VG;
					}else{
						mark_org_y_non_decent = mark_org_y + offsety*DEVA_RATIO;
						pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO;
					}
					pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y_non_decent + need_Move_Down_Pixs(pwrk, nowglyph, j);
					pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
					pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
			        pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
			        pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
			        pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
			        pwrk->lobuf->caret_seq[j].dmrect	= rect;
					mark_org_x = pwrk->lobuf->caret_seq[j].oripos.x;
					mark_org_y = mark_org_y_non_decent;
					j++;
					if(j < pwrk->seg_end)
					{
						pre_pre_glyph = preglyph;
						preglyph = nowglyph;
						nowglyph = pwrk->lobuf->glyf_seq[j];
						ret_adj_spec = getAnchorPairClassAdjustment_21to21(pwrk, p_all_table, preglyph, nowglyph, &offsetx, &offsety);
						if(ret_adj_spec >=0){

							if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
								pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO_VG;
								pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y + offsety*DEVA_RATIO_VG+need_Move_Down_Pixs(pwrk, nowglyph, j);
							}else
							{
								pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO;
								pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y + offsety*DEVA_RATIO +need_Move_Down_Pixs(pwrk, nowglyph, j);
							}
							pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
							pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
							pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
							pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
							pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
							pwrk->lobuf->caret_seq[j].dmrect	= rect;
						}
						else{	
							j--;
							preglyph = pre_pre_glyph;
						}
					}
					state = STATE_POS_MATCH_CLASS_MARKMARK;
					break;
			case STATE_POS_MATCH_CLASS_ANUDATTA:

					if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
						pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO_VG;
						pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y + offsety*DEVA_RATIO_VG +need_Move_Down_Pixs(pwrk, nowglyph, j);
					}else
					{
						pwrk->lobuf->caret_seq[j].oripos.x = mark_org_x + offsetx * DEVA_RATIO;
						pwrk->lobuf->caret_seq[j].oripos.y = mark_org_y + offsety*DEVA_RATIO +need_Move_Down_Pixs(pwrk, nowglyph, j);
		
					}
					pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
					pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
			        pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
			        pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
			        pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
			        pwrk->lobuf->caret_seq[j].dmrect	= rect;
					state = STATE_POS_MATCH_CLASS_MARKMARK;
					break;
			default:
				   break;
		}


		if(STATE_POS_MATCH_CLASS_MARKMARK== state)
		{
			do{
				j++;
				if(j>=pwrk->seg_end)
						break;
				pre_pre_glyph = preglyph;
				preglyph = nowglyph;
				nowglyph = pwrk->lobuf->glyf_seq[j];

				ret_adj = -1;
				if(is_prev == 1)
				{
					ret_adj = getAnchorPairClass3Adjustment(pwrk, p_all_table, main_glyph, nowglyph, &offsetx, &offsety);	
					if(ret_adj<0){
						ret_adj = getAnchorPairClass1Adjustment(pwrk, p_all_table, main_glyph, nowglyph, &offsetx, &offsety);
					}
				}
				else
				{
					ret_adj = getAnchorPairClass1Adjustment(pwrk, p_all_table, main_glyph, nowglyph, &offsetx, &offsety);
				}
				if(ret_adj>=0){

					if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
						pwrk->lobuf->caret_seq[j].oripos.x = pre_syll_org_x + offsetx * DEVA_RATIO_VG;
						pwrk->lobuf->caret_seq[j].oripos.y = offsety*DEVA_RATIO_VG+need_Move_Down_Pixs(pwrk, nowglyph, j);
					}
					else{
						pwrk->lobuf->caret_seq[j].oripos.x = pre_syll_org_x + offsetx * DEVA_RATIO;
						pwrk->lobuf->caret_seq[j].oripos.y = offsety*DEVA_RATIO+need_Move_Down_Pixs(pwrk, nowglyph, j);
					}
						pwrk->lobuf->caret_seq[j].awvec.vx	= aw;
						pwrk->lobuf->caret_seq[j].awvec.vy	= 0;
						pwrk->lobuf->caret_seq[j].adjvec.vx	= 0;
						pwrk->lobuf->caret_seq[j].adjvec.vy = 0;
						pwrk->lobuf->caret_seq[j].drawmethod= DLO_DRAW_NORMAL;
						pwrk->lobuf->caret_seq[j].dmrect	= rect;
				
				}else{
					j--;
					preglyph = pre_pre_glyph;
					break;
				};
			}while(ret_adj>=0);
		}

		pre_pre_glyph = preglyph;
		pre_syll_org_x = syll_org_x;
	}//for

	/*when last character is 0x093f, add the rsb to caret.0x202e,0x0041,0x0915,0x093f,0x0041,0x202c.*/
	nowglyph = pwrk->lobuf->glyf_seq[pwrk->seg_end-1];
	if( (nowglyph>=0xf37a && nowglyph<=0xf3A8) ||(nowglyph>=0xf3b2 && nowglyph<=0xf3be)|| nowglyph == 0x093f) 
	{
		if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, pwrk->seg_end-1, DLO_LANGTAB_RSB, &font_lrsb))
		{
			rsb  = -(font_lrsb.nsRsb) * RSB_RATIO(fontszX);
			if(rsb>0)
				caret+= rsb;
		}
		else{
			rsb = 0;
		}
	}

#if(0)
	/*
	NOTE: The follow part move to function AdjustEndPosX.
	*/
	/*
	adjust caret to display last character .
	*/
	if(pwrk->seg_end-1 > pwrk->seg_start)
	{
		j = pwrk->seg_end-1;
		nowglyph = pwrk->lobuf->glyf_seq[pwrk->seg_end-1];
		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr,nowglyph,pwrk->seg_end-1);
		if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, pwrk->seg_end-1, DLO_LANGTAB_RSB, &font_lrsb))
		{	
			rsb  = -(font_lrsb.nsRsb) * RSB_RATIO(fontszX);
			/*
			if( (nowglyph>=0xf37a && nowglyph<=0xf3be) || nowglyph == 0x093f) 
			{
					aw = -(font_lrsb.nsLsb+font_lrsb.nsRsb) * RSB_RATIO(fontszX);
			}
			*/
		}else{
			rsb = 0;
		}
/*
		if(caret < pwrk->lobuf->caret_seq[j].oripos.x+aw+rsb+1)
		{
			caret = pwrk->lobuf->caret_seq[j].oripos.x+aw+rsb +1 ;
		}
*/
		j = pwrk->seg_end - 2;
		aw = 0;
		while(j> pwrk->seg_start)
		{
			if(0== pwrk->lobuf->caret_seq[j].awvec.vx)/*the vx keep aw value,if it is equal to zero, it is sign.*/
			{
				nowglyph = pwrk->lobuf->glyf_seq[j];
				if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, j, DLO_LANGTAB_RSB, &font_lrsb))
				{
					rsb = -(font_lrsb.nsRsb)* RSB_RATIO(fontszX);
				}else{
					rsb = 0;
				}
				if( caret < pwrk->lobuf->caret_seq[j].oripos.x+aw+1)
				{
					caret= pwrk->lobuf->caret_seq[j].oripos.x + aw +1;
				}

			}else break;
			j--;
		}
	}
#endif

	pwrk->linewidth = caret; 
	pwrk->segw = pwrk->linewidth - pwrk->segw;	// now caret - start caret = segw.
	if(pwrk->segh > pwrk->lineheight)
		pwrk->lineheight = pwrk->segh;
	return DLO_SUCCESS;	
}

int RenderToBuf_Devanagari(pLayWrk pwrk, void *para)
{

	DT32_int mode;
	mode = pwrk->rendermode;
	//if(pwrk->bidirule==DLO_BIDI_UNIRULE)
	//	return DLO_SUCCESS;				// FIXME: force to do nothing temporarily

	pwrk->bHindi = 1;
	pwrk->bMinusLRsb = 1;
	if( (mode&DLO_DATA_RENDER) && !(mode&DLO_DATA_PREPARE_POS) )
		return Render_Devanagari(pwrk, para);
	else 
		return Prerender_Devanagari(pwrk);	
}


int deva_copy_render(pLayWrk pwrk, UNI_CHAR* p_unitxt, int len, UNI_CHAR* p_heap_memory, 
			 UNI_CHAR* p_out , unsigned short * out_len , GlyphSeq * p_trace, 
			 unsigned short * count_syllable, ALL_TBL * p_all_table)
{
	 UNI_CHAR swap_uc;
	 if(p_unitxt[1]==0x25cc && len==2)
	{			
			swap_uc = p_unitxt[0];
			p_unitxt[0] = p_unitxt[1];
			p_unitxt[1] = swap_uc;
	}

	if(len>=2)
	{
		if(p_unitxt[0]==0xef12
			|| p_unitxt[0]==0x093c
			|| ( p_unitxt[0]>=0x0941 && p_unitxt[0]<=0x0944)
			|| p_unitxt[0]==0x0962
			|| p_unitxt[0]==0x0963
			)
		{

			p_out[0] = 0x0915;
			if(p_unitxt[0] == 0x093c)
				p_out[0] = 0x0920;

			p_out[1] = p_unitxt[0];
			p_out[2] = p_unitxt[1];
			p_trace[0].n_per_glyf1 = 2;
			p_trace[0].n_per_glyf2 = 3;
			p_trace[0].idx_gseq2 = 0;
			p_trace[1].n_per_glyf1 = 0;
			p_trace[1].n_per_glyf2 = 0;
			p_trace[1].idx_gseq2 = 0;
			*out_len = 3;
			*count_syllable=1;
		}
		else{			
			p_out[0] = p_unitxt[0];
			p_out[1] = p_unitxt[1];
			p_trace[0].n_per_glyf1 = 2;
			p_trace[0].n_per_glyf2 = 2;
			p_trace[0].idx_gseq2 = 0;
			p_trace[1].n_per_glyf1 = 0;
			p_trace[1].n_per_glyf2 = 0;
			p_trace[1].idx_gseq2 = 0;
			*out_len = 2;
			*count_syllable=1;
		}

	}else
	{
			p_out[1] = p_unitxt[1];
			p_trace[0].n_per_glyf1 = 1;
			p_trace[0].n_per_glyf2 = 1;
			p_trace[0].idx_gseq2 = 0;
			p_trace[1].n_per_glyf1 = 0;
			p_trace[1].n_per_glyf2 = 0;
			p_trace[1].idx_gseq2 = 0;
			*out_len = 1;
			*count_syllable=1;
	}
	return 0;
}


/*
*/
//void  AdjustSegW(pLayWrk pwrk, DT32_int countofglyph)
//{
//	DT32_int syll_org_x;
//	DT32_int idx_focus, idx_end = pwrk->cur_g2idx+countofglyph-1;
//	DT32_int aw, endposx = pwrk->segw;
//	DT16_ushort nowglyph;
//	Font_LRSB font_lrsb;
//	DT32_int rsb;
//	DT32_int ratio;
//	
//	/*
//	adjust caret to display last character .
//	*/
//	idx_focus = idx_end;
//	if(idx_focus >= 0)
//	{
//		nowglyph = pwrk->gseq2[idx_focus];
//		pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, DLO_CHARATTR_RASSCALERATIO, &ratio);
//
//		aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, nowglyph);
//		syll_org_x = pwrk->fnt_pos[idx_focus].leftup.x + pwrk->fnt_pos[idx_focus].offx;
//
//		if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, DLO_LANGTAB_RSB, &font_lrsb))
//		{	
//			rsb  = -(font_lrsb.nsRsb) * DCW_SCALED_SIZEXY(pwrk->xsize,ratio)/1000;
//			if(font_lrsb.nsRsb > 0)
//				return ;
//
//		}else{
//			rsb = 0;
//		}
//
//		if(endposx < syll_org_x+aw+rsb+1)
//		{
//			endposx = syll_org_x+aw+rsb+1;
//		}
//
//		idx_focus = idx_end-1;
//		while(idx_focus >= 0)
//		{
//			nowglyph = pwrk->gseq2[idx_focus];
//			aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, nowglyph);
//			syll_org_x= pwrk->fnt_pos[idx_focus].leftup.x + pwrk->fnt_pos[idx_focus].offx;
//			pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, DLO_CHARATTR_RASSCALERATIO, &ratio);
//			if(0==aw)
//			{
//				if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, nowglyph, DLO_LANGTAB_RSB, &font_lrsb))
//				{
//					rsb = -(font_lrsb.nsRsb)*DCW_SCALED_SIZEXY(pwrk->xsize,ratio)/1000;
//					if(font_lrsb.nsRsb > 0)
//						return ;
//				}else{
//					rsb = 0;
//				}
//				if( endposx < syll_org_x+aw+1)
//				{
//					endposx= syll_org_x+aw+1;
//				}
//			}
//			else
//				break;
//			idx_focus--;
//		}
//		pwrk->segw = endposx;
//	}
//}

/*
	@Function:Prerender

*/
int Prerender_Devanagari(pLayWrk pwrk)
{
	DT32_int i,j,k,aw=0;
	DT32_int segw =0;
	DT16_ushort g2idx_data_len =0;
	DT16_ushort gseq_valid_count =0;
	DT16_short offsetx, offsety;
	DT32_long  loffsetx, loffsety;
//	Font_LRSB font_lrsb;
//	DT32_int rsb;
	DT32_int ret_adj;
	/**/
	ALL_TBL *p_all_table;
	ALL_TBL all_table;
	DT8_char *ptable;
		

	all_table.process_switch = 0;
	all_table.p_gup_pos_table = 0;
	all_table.p_gup_vowel_sub_table = 0;
	all_table.p_gup_pos_table2 = 0;
	all_table.p_gup_pos_table3 = 0;

//#ifdef TABLE_FROM_USERDATA
//	p_all_table = (ALL_TBL *) pwrk->fnt_userdata;
//	if(p_all_table)
//	{
//		all_table.process_switch = p_all_table->process_switch;
//	}
//#endif	

	
	//pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, 0x0915, DLO_CHARATTR_RASSCALERATIO, &pwrk->ratio);
	pwrk->ratio = getScaleRatio(pwrk, 0x0915, -1);

	if(NULL!=pwrk->fengfuncs.getDesignGlobalInfo)
	{
		/*read position table.*/
		if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, 0x0915, DLO_LANGTAB_HINDI_SUB, (DT_void**)&ptable))
		{
			all_table.p_gup_vowel_sub_table = ptable+6;
		}
		if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, 0x0915, DLO_LANGTAB_HINDI_POS1, (DT_void**)&ptable))
		{
			all_table.p_gup_pos_table = ptable+6;
		}
		if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, 0x0915, DLO_LANGTAB_HINDI_POS2, (DT_void**)&ptable))
		{
			all_table.p_gup_pos_table2 = ptable+6;
		}
		if(0<=pwrk->fengfuncs.getDesignGlobalInfo(pwrk->ras_attr, 0x0915, DLO_LANGTAB_HINDI_POS3, (DT_void**)&ptable))
		{
			all_table.p_gup_pos_table3 = ptable+6;
		}
	}

//#ifdef TABLE_FROM_USERDATA
//	p_all_table = (ALL_TBL *) pwrk->fnt_userdata;
//	if(p_all_table)
//	{
//		p_all_table->p_gup_pos_table2 = NULL;
//	}
//#else
	p_all_table = 0;
// #endif 
	if(!p_all_table || !p_all_table->p_gup_vowel_sub_table || !p_all_table->p_gup_pos_table)
	{
		p_all_table = &all_table;
		if(p_all_table->p_gup_pos_table){
			HINDI_ASSERT(p_all_table->p_gup_pos_table[0]>=22);
		}
	}else
	{
		;
	}
//#ifdef TABLE_FROM_USERDATA
//	if(p_all_table->process_switch & DISENABLE_SUB) //JOE_DEBUG
//	{
//		deva_copy_render(pwrk,pwrk->attr->ucs_str + pwrk->seg_start,
//					 pwrk->seg_end - pwrk->seg_start, 
//					 pwrk->gseq1+pwrk->cur_g1idx,
//					 pwrk->gseq2+pwrk->cur_g2idx,
//					 &g2idx_data_len,                
//					 pwrk->gseq + pwrk->seg_start,
//					 &gseq_valid_count,
//					 p_all_table
//					 );
//		pwrk->gseq[pwrk->seg_start].idx = pwrk->cur_g2idx; 
//		pwrk->gseq[pwrk->seg_start].code = gseq_valid_count;
//
//	}else
//#endif
	{
		deva_render(pwrk,pwrk->attr->ucs_str + pwrk->seg_start,
					 pwrk->seg_end - pwrk->seg_start, 
					 pwrk->gseq1+pwrk->cur_g1idx,
					 pwrk->gseq2+pwrk->cur_g2idx,
					 &g2idx_data_len,                 /* now, g2idx valid data len.*/
					 pwrk->gseq + pwrk->seg_start,    /* now, reserved gseg[0].idx and ,gseg[0].code for pass data 
														to other fucntion.
														this function only uses the member n_per_glyf1 and n_per_glyf2
														the n_per_glyf is the syllable has the count of characters.
														the n_per_glyf2 is the syllable has the count of glyphs.
													   */
					 &gseq_valid_count,          /* now,It represent the count of gseq,  it is count of syllable*/
					 p_all_table
					 );


		/*Mark where have valid data*/
		pwrk->gseq[pwrk->seg_start].idx = pwrk->cur_g2idx; 
		pwrk->gseq[pwrk->seg_start].code = gseq_valid_count;
	}

if(pwrk->fengtype != DLO_ENG_BDFRASTER)
{
	DT_BOOL  b_continue_end;
	DT32_int m,n;
	DT32_int idx_ref =0, pre_idx_ref =0;
	DT32_int ad_aw_vx =0;
	DT16_short aw_offset =0;
	DT32_int pos_x =0;
	DT32_int bprevowel_adj=0;
//	DT32_int fontszX;
//	if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
//		fontszX = gDT_FONT_EMSIZE;
//	else
//		fontszX = pwrk->xsize;

	i=pwrk->cur_g2idx;
	j=pwrk->cur_g2idx;
	k=0;

	for(m=pwrk->seg_start; m<gseq_valid_count+pwrk->seg_start;m++)
	{
		idx_ref = pwrk->gseq[m].idx_gseq2+i;//idx_qseq2 id
		/*As the last consonant isn't at the end of position.*/
		if(pwrk->gseq[m].idx_gseq2 < pwrk->gseq[m].n_per_glyf2-1)
		{
			bprevowel_adj = PREVOWEL(pwrk->gseq[m].idx_gseq1) ;
//#if (0)
//			/*for 0x093f*/
//			if(pwrk->gseq2[i]>=0xF37A && pwrk->gseq2[i]<=0xF390){
//
//				bprevowel_adj = 1;
//			}
//			else if(pwrk->gseq2[i]>=0xF391 && pwrk->gseq2[i]<=0xF3A8){
//
//				bprevowel_adj = 2;
//			}
//			else{
//				bprevowel_adj = 0;
//			}
//#endif
			/*
				TODO: process the characters before the consonant.
			*/
			for(n=0; n<=pwrk->gseq[m].idx_gseq2; n++)
			{
				pwrk->fnt_pos[j].aw.vy = 0;
				aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, pwrk->gseq2[i], i);
				pwrk->fnt_pos[j].aw.vx = aw;
				pwrk->fnt_pos[j].leftup.x = pos_x;
				pwrk->fnt_pos[j].leftup.y = 0 + need_Move_Down_Pixs(pwrk, pwrk->gseq2[i], i);
				pwrk->fnt_pos[j].offx = 0;
				pwrk->fnt_pos[j].flags = ID_DEVA;
				pos_x +=aw; 
				i++;j++;k++;
			}

			ad_aw_vx = pwrk->fnt_pos[j-1].aw.vx; 
			aw_offset = 0;
			loffsetx = 0;
			loffsety = 0;
			b_continue_end = FALSE;
			/*
				TODO: process the characters after the consonant.
			*/
			for(n=pwrk->gseq[m].idx_gseq2+1; n<pwrk->gseq[m].n_per_glyf2; n++)
			{

				offsetx = 0;
				offsety = 0;	
				ret_adj = -1;

				pwrk->fnt_pos[j].aw.vy = 0;

				if( (pwrk->gseq2[i]==0x093e) || 
					(pwrk->gseq2[i]==0x0940) ||
					((pwrk->gseq2[i]>= 0xf3a9) && (pwrk->gseq2[i]<= 0xf3b1))||
					((pwrk->gseq2[i]>= 0x0949) && (pwrk->gseq2[i]<= 0x094c))||
					(pwrk->gseq2[i]== 0xef22)||
					(pwrk->gseq2[i]== 0xef25)||
					((pwrk->gseq2[i]>= 0xef2e) && (pwrk->gseq2[i]<= 0xef31))||
					(pwrk->gseq2[i]<= 0x0903)
					)
				{
					loffsetx = 0;
					loffsety = 0;
				}

				/*
				if(b_continue_end)
				{
					aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, pwrk->gseq2[i]);
					offsetx =0;

				}else
				{
				*/

					/*
						Table 20, vowel+0x0952 so do this.
					*/
					if( pwrk->gseq2[i] == 0x0952)
					{
						ret_adj = getAnchorPairClass2Adjustment(pwrk, p_all_table, pwrk->gseq2[i-1], pwrk->gseq2[i], &offsetx, &offsety);
						
					}
					if(ret_adj>=0)
					{
							loffsetx += offsetx;
							loffsety = offsety;
							offsetx+=aw_offset;

							if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
							{
								pwrk->fnt_pos[j-1].aw.vx = (offsetx - aw_offset)*DEVA_RATIO_VG;
								aw = ad_aw_vx - pwrk->fnt_pos[j-1].aw.vx;
								pwrk->fnt_pos[j].aw.vy = offsety*DEVA_RATIO_VG;
							}
							else{
								pwrk->fnt_pos[j-1].aw.vx = (offsetx - aw_offset)*DEVA_RATIO; 
								aw = ad_aw_vx - pwrk->fnt_pos[j-1].aw.vx;
								pwrk->fnt_pos[j].aw.vy = offsety*DEVA_RATIO;
							}
					}
					else
					{
						/*
							Table 16,18 0xef12,0x093c + vowel, so do this.
						*/
						if( pwrk->gseq2[i-1] == 0xef12 || pwrk->gseq2[i-1] == 0x093c)
						{
							ret_adj = getAnchorPairClass2Adjustment(pwrk, p_all_table, pwrk->gseq2[i-1], pwrk->gseq2[i], &offsetx, &offsety);
						}

						if(ret_adj>=0)
						{
							loffsetx += offsetx;
							loffsety = offsety;
							offsetx+=aw_offset;

							if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
							{
								pwrk->fnt_pos[j-1].aw.vx = (offsetx - aw_offset)*DEVA_RATIO_VG;
								aw =   ad_aw_vx - pwrk->fnt_pos[j-1].aw.vx;
								pwrk->fnt_pos[j].aw.vy = offsety*DEVA_RATIO_VG;
							}
							else
							{
								pwrk->fnt_pos[j-1].aw.vx = (offsetx - aw_offset)*DEVA_RATIO;
								aw =   ad_aw_vx - pwrk->fnt_pos[j-1].aw.vx;
								pwrk->fnt_pos[j].aw.vy = offsety*DEVA_RATIO;
							}
						}
						else{

							/**/
							if(bprevowel_adj)
							{
								ret_adj= getAnchorPairClass3Adjustment(pwrk, p_all_table, pwrk->gseq2[idx_ref], pwrk->gseq2[i], &offsetx, &offsety);	
							}

							if(ret_adj<0)
							{
								ret_adj= getAnchorPairClass1Adjustment(pwrk, p_all_table, pwrk->gseq2[idx_ref], pwrk->gseq2[i], &offsetx, &offsety);
							}

							if(ret_adj<0)
							{
								aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, pwrk->gseq2[i], i);
								offsetx =0;
								/*do this because right vowel.*/
								idx_ref = i;
								//b_continue_end = TRUE;
							}
							else
							{
								loffsetx = offsetx;
								loffsety = offsety;
								if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
								{
									pwrk->fnt_pos[j-1].aw.vx = (offsetx - aw_offset)*DEVA_RATIO_VG;
									aw =   ad_aw_vx - pwrk->fnt_pos[j-1].aw.vx;
									pwrk->fnt_pos[j].aw.vy = offsety*DEVA_RATIO_VG;
								}else
								{
									
									pwrk->fnt_pos[j-1].aw.vx = (offsetx - aw_offset)*DEVA_RATIO;
									aw =   ad_aw_vx - pwrk->fnt_pos[j-1].aw.vx;
									pwrk->fnt_pos[j].aw.vy = offsety*DEVA_RATIO;

								}
							}
						}
					//}
				}
				/**/
				if(ret_adj<0){
					pwrk->fnt_pos[j].leftup.x = pos_x;
					pos_x +=aw; 
				}
				else{
					pwrk->fnt_pos[j].leftup.x = pwrk->fnt_pos[j-1].leftup.x; 

				}
				if(pwrk->fengtype==DLO_ENG_DCWOPENVG)
				{
					pwrk->fnt_pos[j].leftup.y =  loffsety*DEVA_RATIO_VG + need_Move_Down_Pixs(pwrk, pwrk->gseq2[i], i);//pwrk->awseq[j].aw.vy;
					pwrk->fnt_pos[j].offx = loffsetx*DEVA_RATIO_VG;

				}
				else{
					pwrk->fnt_pos[j].leftup.y = loffsety*DEVA_RATIO + need_Move_Down_Pixs(pwrk, pwrk->gseq2[i], i);//pwrk->awseq[j].aw.vy;
					pwrk->fnt_pos[j].offx = loffsetx*DEVA_RATIO;

				}
				pwrk->fnt_pos[j].flags = ID_DEVA;
				pwrk->fnt_pos[j].aw.vx = aw;
				aw_offset = offsetx;
				ad_aw_vx = aw;
				i++;j++;k++;
			}
		}
		else
		{
			for(n=0; n<pwrk->gseq[m].n_per_glyf2; n++)
			{
				pwrk->fnt_pos[j].aw.vy = 0;
				aw = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, pwrk->gseq2[i], i);
				pwrk->fnt_pos[j].aw.vx = aw;
				pwrk->fnt_pos[j].leftup.x = pos_x;
				pwrk->fnt_pos[j].leftup.y = 0 + need_Move_Down_Pixs(pwrk, pwrk->gseq2[i], i);
				pwrk->fnt_pos[j].offx = 0;
				pwrk->fnt_pos[j].flags = ID_DEVA;
				pos_x +=aw;
//#if (0)
//				if(IsDevanagari(pwrk->gseq2[i])<=0 && IsDevanagari(pwrk->gseq2[pre_idx_ref])>0)
//				{
//					DT32_int rsb, fontszX = pwrk->xsize;
//					/*
//					pwrk->fnt_pos[j].aw.vx += 40*pwrk->xsize/256;;
//					pwrk->fnt_pos[j].leftup.x +=40*pwrk->xsize/256;;
//					pos_x+= 40*pwrk->xsize/256;*/
//					font_lrsb.nsLsb = 0;
//					font_lrsb.nsRsb = 0;
//					if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, pwrk->gseq2[pre_idx_ref], pre_idx_ref, DLO_LANGTAB_RSB, &font_lrsb))
//					{
//						if(0==pwrk->fengfuncs.getAwidth(pwrk->ras_attr, pwrk->gseq2[pre_idx_ref], pre_idx_ref))
//						{
//							rsb = (font_lrsb.nsLsb+font_lrsb.nsRsb)* RSB_RATIO(fontszX);
//								
//						}else{
//							rsb = font_lrsb.nsRsb* RSB_RATIO(fontszX);
//						}
//					}else rsb = 0;	
//					
//					if(rsb<0)
//					{/*
//						move non-hindi 
//					 */
//						pwrk->fnt_pos[j].aw.vx -= rsb;
//						pwrk->fnt_pos[j].leftup.x -=rsb;
//						pos_x-= rsb;
//					}
//				}
//#endif
				i++;j++;k++;
			}
		}

		pre_idx_ref = idx_ref;
		if(k>=g2idx_data_len)
			break;
	}
}

	segw =0;
//#ifdef TABLE_FROM_USERDATA
//if(p_all_table->process_switch & DISENABLE_SUB)
//{
//	segw += pwrk->fengfuncs.getAwidth(pwrk->ras_attr, 0x0915, -1);
//	//check table exist or not.
//	if(0 > pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, 0x0915, -1, DLO_LANGTAB_RSB, &font_lrsb))
//	{
//		segw += pwrk->fengfuncs.getAwidth(pwrk->ras_attr, 0x0915, -1);
//	}else;
//}
//
//if(p_all_table->process_switch & ENABLE_COPY_SUB) 
//{
//	//check table exist or not.
//	if(0 > pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, 0x0915, -1, DLO_LANGTAB_RSB, &font_lrsb))
//	{
//		segw += pwrk->fengfuncs.getAwidth(pwrk->ras_attr, 0x0915, -1);
//	}else;
//}
//#endif

	for(j=pwrk->cur_g2idx, k=0; k<g2idx_data_len; j++, k++)
	{
		segw += pwrk->fnt_pos[j].aw.vx;
	}

//#if(0)
//	font_lrsb.nsLsb = 0;
//	font_lrsb.nsRsb = 0;
//	if(0 <= pwrk->fengfuncs.getDesignInfo(pwrk->ras_attr, pwrk->gseq2[pwrk->cur_g2idx+g2idx_data_len-1], pwrk->cur_g2idx+g2idx_data_len-1, DLO_LANGTAB_RSB, &font_lrsb))
//	{
//	 
//		if(0==pwrk->fengfuncs.getAwidth(pwrk->ras_attr, pwrk->gseq2[pwrk->cur_g2idx+g2idx_data_len-1], pwrk->cur_g2idx+g2idx_data_len-1))
//		{
//			rsb = (font_lrsb.nsLsb+font_lrsb.nsRsb) * RSB_RATIO(fontszX);
//				
//		}else{
//			rsb = font_lrsb.nsRsb * RSB_RATIO(fontszX);
//		}
//	}
//	else rsb = 0;	
//
//	if(rsb <0)
//	{
//		pwrk->segw = segw - rsb;
//	}
//	else{
//		//pwrk->segw = segw+1;
//		pwrk->segw = segw;
//		//pwrk->segw+=40*pwrk->xsize/256;
//	}
//#endif

	pwrk->segw = segw;
//	AdjustSegW(pwrk, g2idx_data_len);

	HINDI_ASSERT(pwrk->segw<2);
	/*out*/
	pwrk->segarr[pwrk->seg_cnt].ustart	= pwrk->seg_start;
	pwrk->segarr[pwrk->seg_cnt].uend	= pwrk->seg_end;
	pwrk->segarr[pwrk->seg_cnt].script	= pwrk->seg_script;
	pwrk->segarr[pwrk->seg_cnt].lang	= pwrk->seg_lang;
	pwrk->segarr[pwrk->seg_cnt].sw		= pwrk->segw;
	pwrk->segarr[pwrk->seg_cnt].sh		= pwrk->fengfuncs.getAheight(pwrk->ras_attr,0x0915,-1);

	/*use the gseq pass the data to GetSeginfo function.*/
	pwrk->cur_g2idx += g2idx_data_len;
	
	/*next loop*/
	return 0;
}


DT32_int Render_Devanagari_Std(pLayWrk pwrk, DT_void *para)
{
	DT32_int i,j,uend;
	DT32_int ret, rtv = DLO_SUCCESS, bEmpty =0 ;
	DT16_ushort syllable_idx =0 , offset_awseq =0;
	DT16_ushort gidx;
	DLO_Point	lt;
	Str_Seg		*pss;


#ifdef TABLE_FROM_USERDATA
ALL_TBL *p_all_table;
DT32_int debug_offset =0;
p_all_table = (ALL_TBL *) pwrk->fnt_userdata;
if(p_all_table)
debug_offset = pwrk->fengfuncs.getAwidth(pwrk->ras_attr, 0x0915, -1);
#endif
if(pwrk->bidirule==DLO_BIDI_DCWRULE){
	pss = (Str_Seg*) para;
	i=pss->ustart;
	offset_awseq = pss->ustart;
	syllable_idx  = pss->ustart; 
	gidx = pwrk->gseq[pss->ustart].idx;
	uend = pss->uend;
}else{
	i=pwrk->seg_start;
	offset_awseq = pwrk->seg_start;
	syllable_idx  = pwrk->seg_start; 
	gidx =  pwrk->gseq[pwrk->seg_start].idx;
	uend = pwrk->seg_end;
}
	//while( i< pss->uend)
	while(i < uend)
	{

#ifdef TABLE_FROM_USERDATA
if(p_all_table){
if(p_all_table->process_switch & DISENABLE_SUB)
{
	lt.x+=debug_offset;
}
}
#endif		
		bEmpty = 0;
		rtv = DLO_SUCCESS;
		for(j=0; j< pwrk->gseq[syllable_idx].n_per_glyf2; j++)
		{
			lt.x = pwrk->lobuf->caret_seq[gidx+j].oripos.x;
			lt.y = pwrk->lobuf->caret_seq[gidx+j].oripos.y;
//	20110705: Move to GetSeginfo().
//			if(pwrk->vert)
//			{
//				if(IsDevanagari(pwrk->lobuf->glyf_seq[gidx+j]) >0){
//				lt.x+= 29*pwrk->xsize/256;//240-211=29
//				}
//			}
//			else
//			{
//				if(IsDevanagari(pwrk->lobuf->glyf_seq[gidx+j]) >0){
//				lt.y-= 29*pwrk->ysize/256;
//				}
//			}
	
			ret  = pwrk->fengfuncs.getCharbmp(pwrk->ras_attr,
					 pwrk->lobuf->glyf_seq[gidx+j],gidx+j,
					 pwrk->lobuf->bmpwidth,
					 pwrk->lobuf->bmpheight,
					 lt.x, 
					 lt.y,
					 pwrk->lobuf->xbytes,
					 (DT8_uchar*)pwrk->lobuf->bmpbuf,
					 0,
					 pwrk->mode);
			
			 if(ret != DLO_SUCCESS)
			 {
				 if(ret == DLO_EMPTY_FONT){
					bEmpty = 1;
				 }
				 else{
					rtv = ret;		
				}
			 }else;
		}
		/*next loop*/
		i+= pwrk->gseq[syllable_idx].n_per_glyf1;
		offset_awseq += pwrk->gseq[syllable_idx].n_per_glyf2;
		gidx +=  pwrk->gseq[syllable_idx].n_per_glyf2;
		syllable_idx++;
	}

	if(rtv==DLO_SUCCESS){
	  if(bEmpty){	//no error, but some glyphs don't exist.
		  rtv = DLO_EMPTY_FONT;
	  }
    }
	return rtv;		
}

DT32_int Render_Devanagari_Oul(pLayWrk pwrk, DT_void *para)
{
	DT32_int i,j,uend;
	DT16_ushort syllable_idx =0 , offset_awseq =0;
	DT16_ushort gidx;
	DT32_int ret, rtv =DLO_SUCCESS, bEmpty = DT_FALSE;

	DT32_long pathsz=0;
	Str_Seg		*pss;
	if(pwrk->bidirule==DLO_BIDI_DCWRULE){
		pss = (Str_Seg*) para;
		i=pss->ustart;
		offset_awseq = pss->ustart;
		syllable_idx  = pss->ustart; 
		gidx = pwrk->gseq[pss->ustart].idx;
		uend = pss->uend;
	}else{
		i=pwrk->seg_start;
		offset_awseq = pwrk->seg_start;
		syllable_idx  = pwrk->seg_start; 
		gidx = pwrk->gseq[pwrk->seg_start].idx;
		uend = pwrk->seg_end;
	}
	//while( i< pss->uend)
	while(i < uend)
	{
		for(j =0; j<pwrk->gseq[syllable_idx].n_per_glyf2; j++)
		{
			pwrk->pBuf = pwrk->lobuf->olDatabuf;
			ret = pwrk->fengfuncs.getOutline( 
						pwrk->ras_attr,
						pwrk->lobuf->glyf_seq[gidx+j],
						NULL,
						&pwrk->lobuf->olDatabufSize,
						&(pwrk->pBuf),
						&pathsz);
			pwrk->lobuf->olDatabuf = pwrk->pBuf;
			pwrk->lobuf->olSizebuf[gidx+j] = pathsz;

			if(ret != DLO_SUCCESS)
			{
				 if(ret == DLO_EMPTY_FONT){
					bEmpty = 1;
				 }
				 else{
					rtv = ret;		
				}
			}else;
		}
		/*next loop*/
		i+= pwrk->gseq[syllable_idx].n_per_glyf1;
		offset_awseq += pwrk->gseq[syllable_idx].n_per_glyf2;
		gidx +=  pwrk->gseq[syllable_idx].n_per_glyf2;
		syllable_idx++;
	}

	if(rtv==DLO_SUCCESS){
	  if(bEmpty){	//no error, but some glyphs don't exist.
		  rtv = DLO_EMPTY_FONT;
	  }
    }
	return rtv;
}

int Render_Devanagari(pLayWrk pwrk, void *para)
{
	 if( pwrk->fengtype==DLO_ENG_DCWRASTER_MONO ||
			pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY16 ||
			pwrk->fengtype==DLO_ENG_DCWRASTER_GRAY256){
			return Render_Devanagari_Std(pwrk, para);
	 }
	 if(pwrk->fengtype==DLO_ENG_DCWOPENVG){
			return Render_Devanagari_Oul(pwrk, para);
	 }
	 else /*This condition doesn't exist, upon-level will avoid it.*/
		 return DLO_SUCCESS;
}

DT32_int RenderByPos_Devanagari(pLayWrk pwrk, DT_void *para)
{
	DT32_int	ret, rtv = DLO_SUCCESS, bEmpty = 0, opengine;
	DT16_ushort i, gidx_st, gidx_en;
	DLO_Point	lt;
	DT32_long pathsz=0;

DBG_MSG_SHOW_FUNC_NAME();

	//return DLO_SUCCESS;		// FIXME: force to do nothing temporarily

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
