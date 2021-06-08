#include "DcwLangModule.h"
#include "DcwArabic.h"
#include "DcwLayout.h"

#include "DTmanager.h"
#include "DcwUnicodeRange.h"
#include "DcwBiDi.h"

/*----------------- Language Arrays -----------------*/

const JoinType ArabicGroupType[ArabicGroupsEnd] =  {
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

const DT8_uchar arabic_group[256] = {
	/*0x0600-0x0607*/
    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
	/*0x0608-0x060F*/
    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,

	/*0x0610*/
    Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, ArabicNone,
    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,

	/*0x0620*/
    ArabicNone, ArabicNone, Alef, Alef, Waw, Alef, Yeh, Alef,
    Beh, TehMarbuta, Beh, Beh, Hah, Hah, Hah, Dal,

	/*0x0630*/
    Dal, Reh, Reh, Seen, Seen, Sad, Sad, Tah,
    Tah, Ain, Ain, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,

    /*0x0640 */
    Tatweel, Feh, Qaf, Kaf, Lam, Meem, Noon, Heh,
    Waw, Yeh, Yeh, Transparent, Transparent, Transparent, Transparent, Transparent,

	/*0x0650*/
    Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent,
    Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone,

	/*0x0660*/
    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, Beh, Qaf,

	/*0x0670*/
    Transparent, Alef, Alef, Alef, ArabicNone, Alef, Waw, Waw,
    Yeh, Beh, Beh, Beh, Beh, Beh, Beh, Beh,

    /* 0x680 */
    Beh, Hah, Hah, Hah, Hah, Hah, Hah, Hah,
    Dal, Dal, Dal, Dal, Dal, Dal, Dal, Dal,

	/*0x0690*/
    Dal, Reh, Reh, Reh, Reh, Reh, Reh, Reh,
    Reh, Reh, Seen, Seen, Seen, Sad, Sad, Tah,

	/*0x06A0*/
    Ain, Feh, Feh, Feh, Feh, Feh, Feh, Qaf,
    Qaf, Gaf, SwashKaf, Gaf, Kaf, Kaf, Kaf, Gaf,

	/*0x06B0*/
    Gaf, Gaf, Gaf, Gaf, Gaf, Lam, Lam, Lam,
    Lam, Noon, Noon, Noon, Noon, Noon, KnottedHeh, Hah,

    /* 0x6C0 */
    TehMarbuta, HehGoal, HehGoal, HamzaOnHehGoal, Waw, Waw, Waw, Waw,
    Waw, Waw, Waw, Waw, Yeh, YehWithTail, Yeh, Waw,

	/*0x06D0*/
    Yeh, Yeh, YehBarree, YehBarree, ArabicNone, TehMarbuta, Transparent, Transparent,
    Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, Transparent, Transparent,

	/*0x06E0*/
    Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, ArabicNone, Transparent,
    Transparent, ArabicNone, Transparent, Transparent, Transparent, Transparent, Dal, Reh,

	/*0x06F0*/
    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
    ArabicNone, ArabicNone, Seen, Sad, Ain, ArabicNone, ArabicNone, KnottedHeh
};

const JoiningPair ArabicJointab[5][4] =
{
	/* Coming code's JoinType: */
	/*			JType_U,				 JType_C,				JType_D,				JType_R				*/
    { { XIsolated,XIsolated }, { XIsolated,XCausing }, { XIsolated,XInitial }, { XIsolated,XIsolated } }, /* XIsolated, Previous code's shape */
    { { XFinal,	  XIsolated }, { XFinal,   XCausing }, { XFinal,   XInitial }, { XFinal,   XIsolated } }, /* XFinal */
    { { XIsolated,XIsolated }, { XInitial, XCausing }, { XInitial, XMedial },  { XInitial, XFinal } }, /* XInitial */
    { { XFinal,	  XIsolated }, { XMedial,  XCausing }, { XMedial,  XMedial },  { XMedial,  XFinal } }, /* XMedial */
    { { XIsolated,XIsolated }, { XIsolated,XCausing }, { XIsolated,XMedial },  { XIsolated,XFinal } }, /* XCausing */
};

/*---------------------------------------------------*/
DT32_int isArabicChars(pLayWrk pwrk, DT16_ushort ch)
{
	DL_CodeAttr	 ca;
	ca = DL_GetCodeCategory(pwrk, ch);

	if(ca.range==DL_Range_Arabic){
		return 1;
	}

	return 0;
}

DT_BOOL  isArabicLetters(DT16_ushort ch)
{
	return (AL==bidi_getBidiClass(ch));
}

DT_BOOL isArabicCodeRange(pLayWrk pwrk, DT16_ushort ch)
{
DBG_MSG_SHOW_FUNC_NAME();

	if(pwrk->bidirule==DLO_BIDI_DCWRULE)
	{
		return isArabicChars(pwrk,ch);
	}
	else if(pwrk->bidirule==DLO_BIDI_UNIRULE)
	{
		return isArabicLetters(ch);
	}
	return DT_FALSE;
}

ArabicGroup ArabicGetGroup(DT16_ushort uc)
{
DBG_MSG_SHOW_FUNC_NAME();

    if (uc >= 0x0600 && uc < 0x0700)
        return (ArabicGroup) arabic_group[uc-0x0600];
	else if (uc == 0x0020)
		return ArabicSpace;
    else
        return ArabicNone;
}

/* Get Sub Lookup Table in the dlo file data. */
DT32_int DFS_GetSubLookupTab(pLayWrk pwrk, SubLookupTab *hd)
{
	DT32_int i;

DBG_MSG_SHOW_FUNC_NAME();

	/* Because there is only one SubLookup Table in the Arabic DLO_Data_Table, it assigned directly.  */
	/* If you have more than one SubLookup Table in the Arabic DLO_Data_Table,	*/
	/* you should implement this to compatible with multi-SubLookupTab.			*/
	for(i=0;i<pwrk->dloheader.subtabcnt;i++)
	{
		pwrk->offtosubtab = pwrk->dlotaboff[pwrk->cur_dlotab_idx] + pwrk->subtaboff[i]; 
	}

	pwrk->curpos = pwrk->offtosubtab;
	
	hd->format = ReadUShortfromCurpos(pwrk); 
	if(hd->format != 1){ pwrk->sub_tab_exist=0; return DLO_SUBTABLE_UNKNOW;}	/* Only format 1 is supported now. */
	hd->offset2Cover = ReadUShortfromCurpos(pwrk);
	hd->ligasetcnt	 = ReadUShortfromCurpos(pwrk);
	hd->ligsetoffset = (DT8_uchar*)pwrk->dlowkm.laydata + pwrk->curpos;	/* Modified by Jacky_20090901 for big endian compatible */
	pwrk->sub_tab_exist = 1;
	return 	DLO_SUCCESS;
}

/* find out the pointer for the leading code. */
DT32_int DFS_SearchInCoverageTab(pLayWrk pwrk, SubLookupTab *sub, DT16_ushort ch)
{
	DT32_int rtv;
	CoverTab1 cv;

DBG_MSG_SHOW_FUNC_NAME();

	pwrk->curpos = pwrk->offtosubtab + sub->offset2Cover;
	cv.format = ReadUShortfromCurpos(pwrk); 
	if(cv.format != 1){ return -1;}  /* Take unknown format as not found */
	cv.glyfcnt	= ReadUShortfromCurpos(pwrk);
	cv.covarr	= (DT8_uchar*)pwrk->dlowkm.laydata + pwrk->curpos;	/* Modified by Jacky_20090901 for big endian compatible */
	rtv = BinSearchinFile(cv.glyfcnt,(DT8_uchar*)cv.covarr,ch);
	return rtv;
}

/* make the gseq1 and fill the data to the gseq. */
DT32_int SetgseqElem1(pLayWrk pwrk, DT16_ushort idx, DT16_ushort glyf, DT16_ushort cnt)
{
	DT16_ushort i;
	DT16_ushort nextNcodes = cnt;

DBG_MSG_SHOW_FUNC_NAME();

	pwrk->gseq1[pwrk->cur_g1idx] = glyf;
	for(i=idx;i<idx+cnt;i++){
	  pwrk->gseq[i].glyf1 = glyf;
	  pwrk->gseq[i].idx_gseq1 = pwrk->cur_g1idx;
	  pwrk->gseq[i].n_per_glyf1 = Make_n_per_glyf(nextNcodes,1);	nextNcodes--;
	}
	pwrk->cur_g1idx++;
	return DLO_SUCCESS;
}

/* Replace letters in the 0x06xx area and make the gseq1. */
DT32_int ReplaceLetter(pLayWrk pwrk, DT16_ushort idx)
{
	DT16_ushort us, us1, usr;
	DT32_int ret=2;

DBG_MSG_SHOW_FUNC_NAME();

	us = pwrk->attr->ucs_str[idx];
	us1= pwrk->attr->ucs_str[idx+1];

	switch(us){
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
	SetgseqElem1(pwrk, idx, usr, (DT16_ushort)ret);
	return ret;
}

// /* Make the gseq2 and fill the data to gseq. */
//DT16_ushort SetgseqElem2_OLD(pLayWrk pwrk, DT16_ushort idx, DT16_ushort glyf, DT16_ushort cnt)
//{
//	DT16_ushort i,j,r,g,c,total,index;
//	DT16_ushort nextNcodes;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	pwrk->gseq2[pwrk->cur_g2idx] = glyf;
//	total = 0; index = idx;
//	for(i=0;i<cnt;i++)
//	{
//	  Parse_n_per_glyf(pwrk->gseq[index].n_per_glyf1,&r,&g); //g isn't used, because 1 code=N glyphs won't happened in arabic.
//	  total += r;
//	  index += r; 
//	}
//
//	index = idx; nextNcodes = total;
//	for(i=0;i<cnt;i++){
//		Parse_n_per_glyf(pwrk->gseq[index].n_per_glyf1,&c,&g);
//		for(j=0;j<c;j++){
//		  pwrk->gseq[index+j].glyf2	 = glyf;
//		  pwrk->gseq[index+j].idx_gseq2 = pwrk->cur_g2idx;
//		  pwrk->gseq[index+j].n_per_glyf2 = Make_n_per_glyf(nextNcodes,1);	nextNcodes--;
//		}
//		index += c;
//	}
//	pwrk->cur_g2idx++;
//	return total;
//}

/* Make the gseq2 and fill the data to gseq. */
DT16_ushort SetgseqElem2(pLayWrk pwrk, DT16_ushort idx, DT16_ushort glyf, DT16_ushort cnt, DT16_ushort pointscnt)
{
	DT16_ushort i,j,r,g,c,total,index,tcnt,gcnt;

DBG_MSG_SHOW_FUNC_NAME();

	tcnt = cnt + pointscnt;
	gcnt = pointscnt + 1;

	total = 0;	index = idx;
	for(i=0;i<tcnt/*cnt*/;i++)
	{
	  Parse_n_per_glyf(pwrk->gseq[index].n_per_glyf1,&r,&g); //g isn't used, because 1 code=N glyphs won't happened in n_per_glyf1.
	  total += r;
	  index += r; 
	}

	index = idx;
	while(index<idx+tcnt){
		Parse_n_per_glyf(pwrk->gseq[index].n_per_glyf1,&c,&g);		// n_per_glyf1 will only be Ncodes=1glyf.
		for(j=0;j<c;j++){
			if(index+j==idx){	//if(index+j==idx+tcnt-1){			// Note: Consider to put glyf in the last.
				pwrk->gseq[idx].glyf2	 = glyf;
				pwrk->gseq[idx].idx_gseq2 = pwrk->cur_g2idx;
				pwrk->gseq[idx].n_per_glyf2 = Make_n_per_glyf(total,gcnt);	// total codes = 1 (glyf) + pointscnt (points)
			}else if(index+j > idx){
			  pwrk->gseq[index+j].glyf2	 = pwrk->gseq2[pwrk->cur_g2idx];	// except the first one, others will point to the last glyf2
			  pwrk->gseq[index+j].idx_gseq2 = pwrk->cur_g2idx;				// the last one.
			  pwrk->gseq[index+j].n_per_glyf2 = 0;							// use 0 to represent the same cell.
			}
		}
		if(index==idx){			//if(index+j==idx+tcnt-1){			// Note: Consider to put glyf in the last.
			pwrk->gseq2[pwrk->cur_g2idx] = glyf;
		}else if(IS_ARABIC_ZEROWIDTH(pwrk->gseq[index].glyf1)){
			pwrk->cur_g2idx++;
			pwrk->gseq2[pwrk->cur_g2idx] = pwrk->gseq[index].glyf1;
		}
		index += c;	
	}
	pwrk->cur_g2idx++;
	return total;
}

DT16_ushort GetNextglyf1(pLayWrk pwrk, DT16_ushort idx, DT16_ushort *rc)
{
	DT16_ushort cnt=0,g=0;

DBG_MSG_SHOW_FUNC_NAME();

	*rc = pwrk->gseq[idx].glyf1;
	Parse_n_per_glyf(pwrk->gseq[idx].glyf1,&cnt,&g);

	return cnt;
}

// /* Use the previous and current codes' group to decide its shape. */
//DT32_int DecideArabicCodeShape_OLD(pLayWrk pwrk, DT16_ushort idx, ArabicProperties *pro)
//{
//	ArabicShape shape, prevshape=XIsolated;
//	ArabicGroup group, pregroup=ArabicNone;
//	JoinType	jtype;
//	DT16_ushort glyf1, idx1;
//	DT32_int modprev=0;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	glyf1 = pwrk->gseq[idx].glyf1;
//	idx1 = pwrk->gseq[idx].idx_gseq1;
//	if(idx1>pwrk->gseq[pwrk->seg_start].idx_gseq1){		/* Modified by Jacky_20100209, a bug when drawing with Thai. */
//		prevshape = pro[idx1-1].shape;	pregroup = pro[idx1-1].group;
//	}
//	if(idx == pwrk->seg_start){
//	  group = ArabicGetGroup(glyf1);
//	  jtype = ArabicGroupType[group];
//	  if(jtype == JType_T) shape = XIsolated;
//	  else if(idx == pwrk->seg_end-1) shape = XIsolated; /*XFinal;*/ /* 2008.07.08 */
//	  else shape = ArabicJointab[prevshape][jtype].thisS;
//	}else{
//	  group = ArabicGetGroup(glyf1);
//	  jtype = ArabicGroupType[group];
//	  if(jtype == JType_T) shape = XIsolated;
//	  else shape = ArabicJointab[prevshape][jtype].thisS;
//
//	  if(prevshape != ArabicJointab[prevshape][jtype].prevS){
//		pro[idx1-1].shape = ArabicJointab[prevshape][jtype].prevS; modprev=1;
//	  }
//	  if(idx == pwrk->seg_end-1  && jtype==JType_D){	/*  2008.07.08 */
//		  if(shape==XInitial) shape = XIsolated;
//		  else if(shape==XMedial) shape = XFinal;
//	  }
//	}
//	pro[idx1].glyf1 = glyf1;
//	pro[idx1].group = group;
//	pro[idx1].jtype = jtype;
//	pro[idx1].shape = shape;
//	return modprev;
//}

/* Use the previous and current codes' group to decide its shape. */
DT32_int DecideArabicCodeShape(pLayWrk pwrk, DT16_ushort idx, ArabicProperties *pro)
{
	ArabicShape shape, prevshape=XIsolated, keepshape;
	ArabicGroup group/*, pregroup=ArabicNone*/;
	JoinType	jtype;
	DT16_ushort glyf1, idx1, previdx, sidx1, eidx1;
	DT32_int modprev=0;

DBG_MSG_SHOW_FUNC_NAME();

	sidx1 = pwrk->gseq[pwrk->seg_start].idx_gseq1;
	eidx1 = pwrk->gseq[pwrk->seg_end-1].idx_gseq1;

	glyf1 = pwrk->gseq[idx].glyf1;
	idx1 = pwrk->gseq[idx].idx_gseq1;
	if(idx1>sidx1){
		//prevshape = pro[idx1-1].shape;	pregroup = pro[idx1-1].group;
		previdx = idx1;
		do{
			previdx--;
			prevshape = pro[previdx].shape;	
			//pregroup = pro[previdx].group;
		}while(prevshape==XTransparent && previdx>pwrk->gseq[pwrk->seg_start].idx_gseq1 && previdx>0);
		if(prevshape==XTransparent){	// Still XTransparent, won't happen at all.
			prevshape = XIsolated;		// Shouldn't get into here. 
		}
	}

	if(idx1 == sidx1){			//if(idx == pwrk->seg_start){
	  group = ArabicGetGroup(glyf1);
	  jtype = ArabicGroupType[group];
	  if(jtype == JType_T){
		  if(IS_ARABIC_ZEROWIDTH(glyf1)){
			shape = XIsolated;			// Assume it shouldn't get into here. Points shouldn't be a leading char.
										// If you modified this, please check the preshape to index correctly.
		  }else{
			shape = XIsolated;
		  }
	  }
	  else if(idx1 == eidx1)	//else if(idx == pwrk->seg_end-1) 
		  shape = XIsolated;// only one char
	  else shape = ArabicJointab[prevshape][jtype].thisS;
	}else{
	  group = ArabicGetGroup(glyf1);
	  jtype = ArabicGroupType[group];
	  if(jtype == JType_T){
		  if(IS_ARABIC_ZEROWIDTH(glyf1)){
			  shape = XTransparent;		// Keep 0x064B-0x0652 as an transparent glyph.
		  }else{
			  shape = XIsolated;		// treat others as isolated <== might be wrong when using in other languages.
		  }
	  }
	  else shape = ArabicJointab[prevshape][jtype].thisS;

	  // Modified previous shape
	  if(shape!=XTransparent && prevshape != ArabicJointab[prevshape][jtype].prevS){
		  //pro[previdx].shape = ArabicJointab[prevshape][jtype].prevS; 
		  keepshape = ArabicJointab[prevshape][jtype].prevS;
		  modprev=1;
	  }else if(idx1==eidx1 && shape==XTransparent){	//the shape of last char is XTransparent, the previous shape should be modified.
		  if(prevshape==XInitial){
			//pro[previdx].shape = XIsolated;
			keepshape = XIsolated;
			modprev=1;
		  }
		  else if(prevshape==XMedial){
			//pro[previdx].shape = XFinal;
			keepshape = XFinal;
			modprev=1;
		  }
	  }
	  // If idx1 is the last, check if the shape needs to be modified?
	  if(idx1==eidx1  && jtype==JType_D){	//if(idx == pwrk->seg_end-1  && jtype==JType_D){
		  if(shape==XInitial) shape = XIsolated;
		  else if(shape==XMedial) shape = XFinal;
	  }
	}
	pro[idx1].glyf1 = glyf1;
	pro[idx1].group = group;
	pro[idx1].jtype = jtype;
	pro[idx1].shape = shape;
	if(1==modprev && idx1>sidx1){
		pro[previdx].shape = keepshape;
	}
	return modprev;
}

ArabicShape convToArabicShape(unsigned short n)
{
	switch(n){
	case 0:
		return XIsolated;
    case 1:
		return XFinal;
    case 2:
		return XInitial;
    case 3:
		return XMedial;
    case 4:
		return XCausing;
	case 5:
		return XTransparent;
	default:
		return XShapeEnd;
	}
}

/* Get a ligature from pos in dlo file and idx. */
DT32_int DFS_GetLigature(pLayWrk pwrk, DT32_ulong pos, DT16_ushort idx, ArabicLigature *al)
{
	DT32_ulong of, of_start;
	DT32_int i;

DBG_MSG_SHOW_FUNC_NAME();

	of = pos + 2 + idx*2;	/* Move to LigaSet's offset table to get offset to the start of the ligature */
	of_start = pos + ReadUShort(pwrk->dlo,of);
	al->replacelem	= ReadUShort(pwrk->dlo,of_start); of_start += 2 ;
	al->shape		= convToArabicShape(ReadUShort(pwrk->dlo,of_start)); of_start += 2 ;
	al->elementcnt	= ReadUShort(pwrk->dlo,of_start); of_start += 2 ;
	for(i=0;i<al->elementcnt-1;i++)
	{
		al->combelem[i] = ReadUShort(pwrk->dlo,of_start); of_start += 2 ;
	}
	return DLO_SUCCESS;
}

// /* Check if the ligature is matched to the gseq1. If matched, return the ligature, else return 0. */
//DT32_int IsLigaMatch_OLD(pLayWrk pwrk, DT16_ushort idx, ArabicLigature *al, ArabicShape shapes, DT32_int comcnt)
//{
//	DT32_int i;
//	DT16_ushort index;
//
//DBG_MSG_SHOW_FUNC_NAME();
//	
//	/* Check shape */
//	if(al->shape != shapes)	return 0;
//	
//	/* If comcnt!=0, it means re-match. while re-matching, the components count should be the same. */
//	if( comcnt!=0 && comcnt!=al->elementcnt ) return 0; 
//
//	index = pwrk->gseq[idx].idx_gseq1+1;
//	for(i=0;i<al->elementcnt-1;i++,index++){	/* check Ligature components */
//	  if(al->combelem[i] != pwrk->gseq1[index])	return 0;
//	}
//	
//	/* If the advanced width of replace code is 0, take it as not matched. */
//	if(pwrk->fengfuncs.getAwidth(pwrk->ras_attr,al->replacelem)==0)	return 0;
//
//	return al->elementcnt; /* 0: none matched, >0: element count. */
//}

/* Check if the ligature is matched to the gseq1. If matched, return the ligature, else return 0. */
DT32_int IsLigaMatch(pLayWrk pwrk, DT16_ushort idx, ArabicLigature *al, ArabicShape shapes, DT32_int comcnt, DT16_ushort *pcnt)
{
	DT32_int i;
	DT16_ushort index, pointscnt, matchcnt;

DBG_MSG_SHOW_FUNC_NAME();
	
	/* Check shape */
	if(al->shape != shapes)	
		return 0;
	
	/* If comcnt!=0, it means re-match. while re-matching, the components count should be the same. */
	if( comcnt!=0 && comcnt!=al->elementcnt ) 
		return 0; 

	i = 0;	pointscnt = 0;	matchcnt = 0;	// when processing here, it means leadcode is the same, so matchcnt=0 is a valid matched case. 
	index = pwrk->gseq[idx].idx_gseq1+1;	// leadcode is the same, compare the others.
	while(i<al->elementcnt-1 && index<pwrk->cur_g1idx)
	{
		if(al->combelem[i] != pwrk->gseq1[index]){
			if( IS_ARABIC_ZEROWIDTH(pwrk->gseq1[index]) ){
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

	/* If the advanced width of replace code is 0, take it as not matched. */
//	if(pwrk->fengfuncs.getAwidth(pwrk->ras_attr,al->replacelem)==0)	
//		return 0;
	if(!pwrk->fengfuncs.chkGlyphExist(pwrk->ras_attr,al->replacelem, -1))	
		return 0;

	*pcnt = pointscnt;
	return al->elementcnt; /* 0: none matched, >0: element count. */
}

// /* Search for the replace code in Ligature Set by leading code and shape. */
//DT16_ushort CheckArabicLigature_OLD(pLayWrk pwrk, DT16_ushort idx, DT16_ushort ls, ArabicProperties *pro, SubLookupTab *sub, DT16_ushort *g2)
//{
//	DT32_int bmatch=0;
//	DT32_int retm=0, comcnt=0, bReMatch=0;
//	DT16_ushort i, ligcnt, elems=1;
//	DT32_ulong  lsb;
//	DT16_ushort comps[MAX_LIG_COMPONENTS];
//	ArabicShape starts=XIsolated, ends=XIsolated, matchshape=XIsolated;	/* Jacky_20100209 */
//	ArabicLigature al;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	al.leadcode = pwrk->gseq[idx].glyf1;
//	al.combelem = comps;
//
//	pwrk->curpos = pwrk->offtosubtab + ReadUShort(sub->ligsetoffset, ls*2);	/* Move to Ligature Set */
//
//	lsb = pwrk->curpos;
//	ligcnt = ReadUShortfromCurpos(pwrk);
//	for(i=0;i<ligcnt;i++){
//	  /* Get a ligature from the Ligature Set. */
//	  DFS_GetLigature(pwrk, lsb, i, &al);
//
//	  if(!bReMatch){
//	    starts = pro[ pwrk->gseq[idx].idx_gseq1 ].shape;
//		matchshape = starts;
//	  }
//	  /* For ALEF.LAM ligature */
//	  if(ArabicGetGroup(pwrk->gseq[idx].glyf1)==Lam && ArabicGetGroup(pwrk->gseq[idx+1].glyf1)==Alef){
//		if(starts==XInitial)		matchshape=starts=XIsolated;
//		else if(starts==XMedial)	matchshape=starts=XFinal;
//		else{ ;	/* do nothing for avoid warnings. Jacky_20100209 */}
//	  }
//
//	  /* Check the ligature is match or not. */
//	  retm = IsLigaMatch_OLD(pwrk,idx,&al,matchshape,comcnt);
//
//	  /* If ligature exist, then									*/
//	  /* A. starts==XIsolated, shapes may only be XIsolated			*/
//	  /* B. starts==XInitial , shapes may be XInitial or XIsolated	*/
//	  /* C. starts==XMedial  , shapes may be XMedial  or XFinal		*/
//	  /* D. starts==XFinal   , shapes may only be XFinal			*/
//	  if( retm>0 ){
//		ends = pro[ pwrk->gseq[idx].idx_gseq1+retm-1 ].shape;
//
//		/* Check if there is an advanced shape for this ligature.		*/
//		/* B. If starts=XInitial && ends=XFinal, use XIsolated instead.	*/
//		/* C. If starts=XMedial  && ends=XFinal, use XFinal instead.	*/
//		if( !bReMatch && ( starts==XInitial || starts==XMedial || starts==XCausing ) && ends==XFinal){
//		  if(starts==XInitial)		matchshape = XIsolated;		/* B. */
//		  else if(starts==XMedial)	matchshape = XFinal;		/* C. */
//		  else{ ;	/* do nothing for avoid warnings. Jacky_20100209 */}
//		  bReMatch=1;
//		  i=0; comcnt=retm; continue;
//		}else{
//		  bmatch = 1;		break;
//		}
//	  }
//	}
//
//	if(bmatch == 1){
//		*g2	= al.replacelem;
//		elems = al.elementcnt;
//	}else {
//		*g2 = al.leadcode;
//		elems = 1;
//	}
//	return elems;
//}

/* Search for the replace code in Ligature Set by leading code and shape. */
DT16_ushort CheckArabicLigature(pLayWrk pwrk, DT16_ushort idx, DT16_ushort ls, ArabicProperties *pro, SubLookupTab *sub, DT16_ushort *g2, DT16_ushort *points)
{
	DT32_int bmatch=0, tidx;
	DT32_int retm=0, comcnt=0, bReMatch=0;
	DT16_ushort i, ligcnt, elems=1, pointscnt;
	DT32_ulong  lsb;
	DT16_ushort comps[MAX_LIG_COMPONENTS];
	ArabicShape starts=XIsolated, ends=XIsolated, matchshape=XIsolated;	/* Jacky_20100209 */
	ArabicLigature al;

DBG_MSG_SHOW_FUNC_NAME();

	al.leadcode = pwrk->gseq[idx].glyf1;
	al.combelem = comps;

	pwrk->curpos = pwrk->offtosubtab + ReadUShort(sub->ligsetoffset, ls*2);	/* Move to Ligature Set */

	lsb = pwrk->curpos;
	ligcnt = ReadUShortfromCurpos(pwrk);
	for(i=0;i<ligcnt;i++){
	  
	  pointscnt = 0;
	  /* Get a ligature from the Ligature Set. */
	  DFS_GetLigature(pwrk, lsb, i, &al);

	  if(!bReMatch){
	    starts = pro[ pwrk->gseq[idx].idx_gseq1 ].shape;
		tidx = idx;
		while(starts==XTransparent && tidx>pwrk->seg_start){
			tidx--;
			starts = pro[ pwrk->gseq[tidx].idx_gseq1 ].shape;	// get previous shape as starts.
		}
		matchshape = starts;
	  }
	  
	  /* For ALEF.LAM ligature */
	  if(ArabicGetGroup(pwrk->gseq[idx].glyf1)==Lam && al.elementcnt>1){
		tidx = idx + 1;
		while(tidx < pwrk->seg_end){
			if(IS_ARABIC_ZEROWIDTH(pwrk->gseq[tidx].glyf1)){
				tidx++;
				continue;
			}
			if(ArabicGetGroup(pwrk->gseq[tidx].glyf1) == Alef){
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
	  /* Check the ligature is match or not. */
	  retm = IsLigaMatch(pwrk,idx,&al,matchshape,comcnt,&pointscnt);

	  /* If ligature exist, then									*/
	  /* A. starts==XIsolated, shapes may only be XIsolated			*/
	  /* B. starts==XInitial , shapes may be XInitial or XIsolated	*/
	  /* C. starts==XMedial  , shapes may be XMedial  or XFinal		*/
	  /* D. starts==XFinal   , shapes may only be XFinal			*/
	  if( retm>0 ){
		*g2	= al.replacelem;
		elems = al.elementcnt;
		*points = pointscnt;

		ends = pro[ pwrk->gseq[idx].idx_gseq1+retm-1 ].shape;		
		// ends can't be XTransparent
		tidx = pwrk->gseq[idx].idx_gseq1+retm-1;
		while(ends==XTransparent && tidx>=pwrk->gseq[idx].idx_gseq1){
			tidx--;
			ends = pro[ tidx ].shape;	// get previous shape as ends.
		}
		/* Check if there is an advanced shape for this ligature.		*/
		/* B. If starts=XInitial && ends=XFinal, use XIsolated instead.	*/
		/* C. If starts=XMedial  && ends=XFinal, use XFinal instead.	*/
		if( !bReMatch && ( starts==XInitial || starts==XMedial || starts==XCausing ) && ends==XFinal){
		  if(starts==XInitial)		matchshape = XIsolated;		/* B. */
		  else if(starts==XMedial)	matchshape = XFinal;		/* C. */
		  else{ ;	/* do nothing for avoid warnings. Jacky_20100209 */}
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

/* Make the awseq. */
DT_void Fillawseg_ARA(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();
	Fillawseg_R2L(pwrk);
}
//DT_void Fillawseg_ARA_OLD(pLayWrk pwrk)
//{
//	DT32_int i, aw=0, segw=0;
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
//		pwrk->awseq[i].codeidx	= i;
//		pwrk->awseq[i].glyfidx = pwrk->gseq[i].idx_gseq2;
//		pwrk->awseq[i].aw.vx	= aw;
//		pwrk->awseq[i].aw.vy	= 0;
//		pwrk->awseq[i].direct	= DLO_RIGHTTOLEFT;
//		p.x = segw;		p.y = 0;
//		pwrk->awseq[i].leftup = p;
//
//		/* Only multi-codes=1glyph in Arabic, so use gidx to distinguish this situation. */
//		if(i==pwrk->seg_start) gidx = pwrk->awseq[i].glyfidx;
//		else if(pwrk->awseq[i].glyfidx == gidx) continue;
//		else gidx = pwrk->awseq[i].glyfidx;
//
//		segw += aw;
//	}
//
//	pwrk->segw = segw;
//}

/* fill the segment info to the segment array, segarr. */
//DT_void Fillsegarr_ARA_OLD(pLayWrk pwrk)
//{
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	pwrk->segarr[pwrk->seg_cnt].ustart	= pwrk->seg_start;
//	pwrk->segarr[pwrk->seg_cnt].uend	= pwrk->seg_end;
//	pwrk->segarr[pwrk->seg_cnt].script	= pwrk->seg_script;
//	pwrk->segarr[pwrk->seg_cnt].lang	= pwrk->seg_lang;
//	pwrk->segarr[pwrk->seg_cnt].sw		= pwrk->segw;
//	pwrk->segarr[pwrk->seg_cnt].sh		= pwrk->segh;	
//}

/* fill the segment info to the segment array, segarr. */
DT_void Fillsegarr_ARA(pLayWrk pwrk)
{
DBG_MSG_SHOW_FUNC_NAME();

	Fillsegarr_R2L(pwrk);
}


/*---------------------------------------------------------------------------------------------*/

/* Get Arabic segment info. */
/* Complete the info of DLO_CodePositioning array in DLO_LayBuf. */
DT32_int GetSeginfo_Arabic(pLayWrk pwrk, Str_Seg *seginfo)
{
DBG_MSG_SHOW_FUNC_NAME();

	return GetSeginfo_R2L(pwrk, seginfo);
}
DT32_int CalcPosition_Arabic(pLayWrk pwrk, DT_void *para)
{
	DT16_ushort nowglyph;
	DT32_int j, aw, ht, caret, lastcaret, lastpoint_aw=0;
	DLO_RECT rect;

DBG_MSG_SHOW_FUNC_NAME();

//	if(pwrk->vert)
//		return CalcPosition_Arabic_vert(pwrk,para);

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
	  if(!IS_ARABIC_ZEROWIDTH(nowglyph)){
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
	  if(!IS_ARABIC_ZEROWIDTH(nowglyph)){
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
//DT32_int GetSeginfo_Arabic_OLD(pLayWrk pwrk, Str_Seg *seginfo)
//{
//	DT32_int i, j, st, en, g2st, g2en, gcnt, aw, caret;
//	DT16_ushort c, g, gidx=0;		/* Jacky_20100209 */
//	DLO_CodePositioning p;
//	DLO_RECT rect;
//
//DBG_MSG_SHOW_FUNC_NAME();
//
//	DT_memset(&p,0,sizeof(DLO_CodePositioning));	/* To avoid warnings when compile with GCC */
//
//	st = seginfo->ustart;
//	en = seginfo->uend;
//
//	/* Re-sequences Arabic glyf_seq (Reverse-ordered) */
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
//	  p.n_per_glyf = Make_n_per_glyf(c,g);	// only multi-codes=1Glyph situation in Arabic. Don't deal with g>1.
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
//	  pwrk->lobuf->caret_seq[j].oripos.y	= 0;
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

DT32_int RenderToBuf_Arabic(pLayWrk pwrk, DT_void *para)
{
	DT32_int i, rtv, /*bmod=0,*/ bexist=0, ret=DLO_SUCCESS, bEmpty;
	SubLookupTab subhead;
	DT16_ushort iter, lsidx, ch, elemcnt, glyf2, total, c, g, points;
	//ArabicProperties glyf1pro[DLO_MAXCODES_PER_STR_SEG];
	DT32_int mode;
	Str_Seg *pss;
	DT16_ushort gidx_st=0, gidx_en=0;
	DT32_long pathsz=0;
	DLO_Point	lt;	/* Left-Top point */
	pDT_FontMgr_wrk	pmgrwrk=((DT_Font*)(pwrk->cur_DT_Font))->fontmgr;
	ArabicProperties *glyf1pro;

DBG_MSG_SHOW_FUNC_NAME();

	if(pmgrwrk->tmpbufsize<(DT32_long)((pwrk->seg_end-pwrk->seg_start)*sizeof(ArabicProperties))){
		//return 0;		// Modified_By_Jacky_20101213:
		return DLO_TEMPBUF_NOT_ENOUGH;
	}
	glyf1pro = (ArabicProperties *)pmgrwrk->tempbuf;

	mode = pwrk->rendermode;

	if( (mode&DLO_DATA_RENDER) && !(mode&DLO_DATA_PREPARE_POS) ) goto DATA_RENDER;
	else goto DATA_PREPARE_POS;

DATA_PREPARE_POS:
	/* Get SubLookup Table */
	if(pwrk->dlo_tab_exist){
		/* If there are more than one subtab, you should get it by a loop.	*/
		/* Now in Arabic, there is only one SubLookup Table.				*/
		/* for(i=0;i<pwrk->dloheader.subtabcnt;i++)							*/
		//rtv = DFS_GetSubLookupTab(pwrk,&subhead);	if(rtv)	ret |= rtv;		//Marked_By_Jacky_20101213

		//Modified_By_Jacky_20101213
		// SubLookupTab is a part of source codes in DigiTypeAPI, so it should exist always. No need to check it.
		DFS_GetSubLookupTab(pwrk,&subhead);
	}

	/* Fill the codeidx in gseq */
	for(i=pwrk->seg_start;i<pwrk->seg_end;i++)
	{
		pwrk->gseq[i].idx	= i;
		pwrk->gseq[i].code = pwrk->attr->ucs_str[i];
	}

	/* Letter Replacement, and generate gseq1. Example: 0627+0653=0622		*/
	/* Some combined letters are defined in 0x06xx area, replace them here. */
	iter = pwrk->seg_start;
	while(iter<pwrk->seg_end){
	  iter += ReplaceLetter(pwrk, iter);
	}

	/* Decide the code's shape in gseq1 */
	iter = pwrk->seg_start;
	while(iter<pwrk->seg_end){
	  /*bmod =*/ DecideArabicCodeShape(pwrk, iter, (ArabicProperties*)glyf1pro/*(ArabicProperties*)&glyf1pro*/);
	  Parse_n_per_glyf(pwrk->gseq[iter].n_per_glyf1,&c,&g);
	  iter += c;
	}


	/* Search Sub Tab for glyph substitution (ligature or shape) and generate gseq2. Example: 0628+062D+064A=FDC2 */
	iter = pwrk->seg_start;
	while(iter<pwrk->seg_end){
	  ch = pwrk->gseq[iter].glyf1;
	  /* Is there any suitable substitutions? */
	  bexist = 0;
	  if( pwrk->sub_tab_exist && pwrk->dlo_tab_exist){
		rtv = DFS_SearchInCoverageTab(pwrk,&subhead,ch);
		if(rtv >= 0){ lsidx = rtv; bexist=1; }
	  }

	  /* Found */
	  if(bexist){ 
		points = 0;	/* ligature contains points */
		elemcnt = CheckArabicLigature(pwrk,iter,lsidx,(ArabicProperties*)glyf1pro,&subhead,&glyf2,&points);
		total = SetgseqElem2(pwrk, iter, glyf2, elemcnt, points);
	  /* Not Found */
	  }else{ 
		total = SetgseqElem2(pwrk, iter, ch, 1, 0);	// alone point will also get into this.
	  }
	  iter = iter+total;
	}
	if(pwrk->bidirule==DLO_BIDI_DCWRULE)
		ConvPunctuation_Open2Close(pwrk, pwrk->seg_start, pwrk->seg_end);

	/* Fill some info to the array for later rendering. */
	Fillawseg_ARA(pwrk);
	Fillsegarr_ARA(pwrk);

	if(!(mode&DLO_DATA_RENDER)) return ret;
	
	
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

DT32_int RenderByPos_Arabic(pLayWrk pwrk, DT_void *para)
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

