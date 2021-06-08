#include "DcwUnicodeRange.h"
#include "DcwLayout.h"
#include "DcwBiDi.h"

/*---------------------------------------------------------------------------*/
DL_CodeAttr DL_GetCodeCategoryPUA(DT16_ushort ch)
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
	case DT_CODE_DIR_NOT_SPECIFIED:	//0x00	/* Not specified, like punctuation in ASCII */
	default:
		chattr.range = DL_Not_In_Range;
		chattr.cate  = DL_NoCategory;
	}

	return chattr;
}
/* Classified characters */
DL_CodeAttr DL_GetCodeCategory(pLayWrk pwrk, DT16_ushort ch)
{
	DL_CodeAttr chattr;

DBG_MSG_SHOW_FUNC_NAME();

	chattr.range = DL_Range_Latin;	//DL_Not_In_Range;
	chattr.cate  = DL_Letter_Other;	//DL_NoCategory;
	if( (ch<=0x001F)				||	/* C0 Controls	*/
		(ch==0x007F)				||	/* DEL			*/
		(ch>=0x0080 && ch<=0x009F)		/* C1 Controls	*/
	  ){
		chattr.range  = DL_Range_Special;
		chattr.cate	  =	DL_Other_Control;
		return chattr;
	}
	
	if(ch==0x0020 || ch==0x3000){			/* Spaces */
		chattr.range = DL_Range_INHERIT;
		chattr.cate  = DL_Separator_Space;
		return chattr;
	}

	if(ch>0x0020 && ch<0x007F){				/* Basic Latin */
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

//	if(ch==0xE420){
//		chattr.range = DL_Range_INHERIT;
//		chattr.cate  = DL_Separator_Space;
//		return chattr;
//	}
//	if(ch>0xE420 && ch<0xE47F){				/* Latin at PUA */
//		chattr.range = DL_Range_Latin;
//		chattr.cate	  = DL_Punctuation_Other;
//		if(ch>=0xE441 && ch<=0xE45A ) chattr.cate = DL_Letter_Uppercase;
//		else if(ch>=0xE461 && ch<=0xE47A ) chattr.cate = DL_Letter_Lowercase;
//		else if(ch>=0xE430 && ch<=0xE439 ) chattr.cate = DL_Number_DecimalDigit;
//		else if((ch>=0xE423 && ch<=0xE426) || 0xE440==ch) chattr.cate = DL_Symbol_Other;
//		else if(0xE428==ch || 0xE45B==ch || 0xE47B==ch) chattr.cate = DL_Punctuation_Open;
//		else if(0xE429==ch || 0xE45D==ch || 0xE47D==ch) chattr.cate = DL_Punctuation_Close;
//		return chattr;
//	}


	if( (ch>=0x00A0 && ch<=0x02FF) ){			
		chattr.range  = DL_Range_Latin;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
		/* Do something in the future*/	/* Marked by Jacky_20100209 */
		/*if		(ch>=0x00A0 && ch<=0x00FF);*/		/* Latin-1 Supplement */
		/*else if	(ch>=0x0100 && ch<=0x017F);*/		/* Latin Extension A  */
		/*else if	(ch>=0x0180 && ch<=0x024F);*/		/* Latin Extension B  */
		/*else if	(ch>=0x0250 && ch<=0x02AF);*/		/* IPA Extension	  */
		/*else if	(ch>=0x02B0 && ch<=0x02FF);*/		/* Spacing Modifier Letters */
		/*else ;							   */
	}

	if( (ch>=0x0300 && ch<=0x036F)  ){		/* Combing Diacritical Marks */
		chattr.range  = DL_Range_Latin;
		chattr.cate	  = DL_Mark_SpacingCombining;
		return chattr;
	}

	if( (ch>=0x0370 && ch<=0x03FF) ){		/* Greek & Coptic */
		chattr.range  = DL_Range_Greek;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
	}

	if( (ch>=0x0400 && ch<=0x04FF) ||		/* Cyrillic		*/
		(ch>=0x0500 && ch<=0x052F)			/* Cyrillic Supplement */
	  ){		
		chattr.range  = DL_Range_Cyrillic;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
	}

	if( (ch>=0x0530 && ch<=0x058F) ){		/* Armenian, not support */
		chattr.range  = DL_Range_Armenian;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
	}

	if( (ch>=0x0590 && ch<=0x05FF) ||
		(ch>=0xFB1D && ch<=0xFB4F) ){		/* Hebrew, not support	 */
		chattr.range  = DL_Range_Hebrew;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
	}

	if( (ch>=0x0600 && ch<=0x06FF)	||		/* Arabic Basic */
		(ch>=0xFB50 && ch<=0xFDFF)	||		/* Arabic-Form A*/
		(ch>=0xFE70 && ch<0xFEFF)	||		/* Arabic-Form B*/
		(pwrk->bUseArabicPUA && ch>=0xE000 && ch<0xE08F)	/* Arabic-PUA	*/
	  ){	
		chattr.range  = DL_Range_Arabic;
		chattr.cate   = DL_Letter_Other;
		if( (ch>=0x0610 && ch<=0x0615) || (ch>=0x064B && ch<=0x065E) || (ch>=0x06D6 && ch<=0x06DC) ||
			(ch>=0x06DF && ch<=0x06E4) || (ch>=0x06E7 && ch<=0x06E8) || (ch>=0x06EA && ch<=0x06ED) ||
			0x0670==ch ) chattr.cate = DL_Mark_NonSpacing;
		else if( 0x06DE==ch ) chattr.cate = DL_Mark_Enclosing;
		else if( 0x0640==ch ) chattr.cate = DL_Letter_Modifier;
		else chattr.cate   = DL_Letter_Other;	/* Jacky_20100209 */
		return chattr;
	}

/*-------0x0900---------------------------------------------------------------------------------------------*/
	if( (ch>=0x0900 && ch<=0x097F) ||
		(ch>=0xE300 && ch<=0xE308) ||
		(ch>=0xEf00 && ch<=0xEfff) ||
		(ch>=0xf200 && ch<=0xf3ff)) {
		chattr.range	= DL_Range_Devanagari;
		chattr.cate		= DL_Letter_Other;
		return chattr;
	}

/*-------0x0B80---------------------------------------------------------------------------------------------*/

	if( (ch>=0x0b80 && ch<=0x0bff) ||
		(ch>=0xEE00 && ch<=0xEE53)) {
		chattr.range	= DL_Range_Tamil;
		chattr.cate		= DL_Letter_Other;
		return chattr;
	}
/*-------0x0E00---------------------------------------------------------------------------------------------*/

	if( (ch>=0x0E00 && ch<=0x0E7F) ){
		chattr.range	= DL_Range_Thai;
		chattr.cate		= DL_Letter_Other;
		return chattr;
	}
	


/*-------0x1FFF---------------------------------------------------------------------------------------------*/

	if( (ch>=0x2000 && ch<=0x21FF) ){
		chattr.range  = DL_Range_Special;
		chattr.cate   = DL_Other_Format;
		if(ch==chLRM || ch==chRLM || ch==chLRE || ch==chRLE || ch==chLRO || ch==chRLO || ch==chPDF){
			chattr.cate = DL_Bidi_Control;
		}
		if(ch>=0x200B && ch<=0x200D){
			chattr.cate = DL_ZeroWidth_Format;
		}
		return chattr;
		/* Do something in the future*/		/* Marked by Jacky_20100209 */
		/*if		(ch>=0x2000 && ch<=0x206F);*/		/* General Punctuation						*/
		/*else if	(ch>=0x2070 && ch<=0x209F);*/		/* Superscripts & Subscripts				*/
		/*else if	(ch>=0x20A0 && ch<=0x20CF);*/		/* Currency Symbols							*/
		/*else if	(ch>=0x20D0 && ch<=0x20FF);*/		/* Combining Diacritical Marks for Symbols	*/
		/*else if	(ch>=0x2100 && ch<=0x214F);*/		/* Letterlike Symbols						*/
		/*else if	(ch>=0x2150 && ch<=0x218F);*/		/* Number Forms								*/
		/*else if	(ch>=0x2190 && ch<=0x21FF);*/		/* Arrows									*/
		/*else ;							   */
	}

/*-------0x25cc---------------------------------------------------------------------------------------------*/

	if( (ch==0x25CC) ){			
		chattr.range  = DL_Range_Special;	//DL_Range_Latin;	// 20110808: Jacky modified for Hindi-Bidi.
		chattr.cate	  = DL_Symbol_Other;
	}
/*-------0x4E00---------------------------------------------------------------------------------------------*/
	if(ch>=0x4E00 && ch<=0x9FFF /*0x9FA5*/){	//CJK, Han
		chattr.range  = DL_Range_Latin;		//DL_Range_Han;
		chattr.cate	  = DL_Letter_Other;
		return chattr;
	}


	/*if(ch == 0xFEFF){ chattr.script = DL_Not_In_Range; chattr.cate = DL_Separator_Space;}*/
	//set this as before to avoid some problems.
	if(ch == 0xFEFF){ chattr.range = DL_Not_In_Range; chattr.cate = DL_NoCategory;}	

/*-------0xE000 ~ 0xF8FF-------------------------------------------------------------------------------------*/
	// Please be sure this if-else is at the bottom of this function.  
	if( ch>=0xE000 && ch<=0xF8FF ){	//PUA: Private Use Area
		//((ch>=0xE000 && ch<0xE08F)) => this area had been reserved for Arabic, should return in previous if-else.
		//((ch>=0xE900 && ch<0xE9FF))
		//((ch>=0xEE00 && ch<0xEEFF))
		return DL_GetCodeCategoryPUA(ch);
	}

	return chattr;
}

/* Set the script and lang according code range. */
DT_void DL_GetScriptLang(DL_CodeRange ra, DLO_Script *sc, DLO_Language *la)
{
DBG_MSG_SHOW_FUNC_NAME();

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

/* Get next segment. */
DL_CodeRange DL_DivideStrByScript(pLayWrk pwrk, DT16_ushort *str, DT16_ushort cnt, DT16_ushort idxb, DT16_ushort *idxe)
{
	DT16_ushort ch;
	DT16_ushort segidx=0, iter=idxb;
	DL_CodeAttr at;
	DT32_int stop=0, fstop=0, dcr=DL_Not_In_Range;

DBG_MSG_SHOW_FUNC_NAME();

	while( iter<cnt && segidx<DLO_MAXCODES_PER_STR_SEG && !stop )
	{
	  /* If the leading code is a code which has no direction implied, get next code instead. */
	  if( iter==idxb ){
		/* Get first segment & its script */
		while( iter<cnt && segidx<DLO_MAXCODES_PER_STR_SEG && !fstop){
		  ch = str[iter];
		  at = DL_GetCodeCategory(pwrk, ch);
		  segidx++; iter++;

		  switch(at.range)
		  {
		  /* Codes in the following ranges are not directive. */
		  case DL_Not_In_Range:
		  case DL_Range_INHERIT:
		  case DL_Range_Special:
			break;
		  default:
			dcr = at.range;
			fstop=1;
		  }
		}
		if(iter==cnt || segidx==DLO_MAXCODES_PER_STR_SEG) break;
	  }

	  /* Is the script the same? */
	  ch = str[iter];
	  at = DL_GetCodeCategory(pwrk, ch);
	  switch(at.range)
	  {
	  case DL_Not_In_Range:
	  case DL_Range_INHERIT:
	  case DL_Range_Special:
		break;
	  default:
		/* If the code's script is not the same, the segment is ended. */
		if( at.range!=(DL_CodeRange)dcr ) stop = 1;
		break;
	  }
	  if(!stop){
		segidx++; iter++;
	  }
	}

	*idxe = idxb + segidx;
	
	return dcr;
}

/* Get next segment. */
DT32_int DL_DivideStrByScript_New(pLayWrk pwrk, DT16_ushort *str, DT16_ushort cnt, DT16_ushort idxb, DT16_ushort *idxe, 
								  DT32_int writedir, DLO_Script *sc, DLO_Language *la, DT16_ushort *dir)
{
	DT16_ushort iter=idxb;
	DL_CodeAttr at;
	DT32_int stop=0;
	DLO_Script next_sc=DLO_SCRIPT_DFLT, now_sc=DLO_SCRIPT_DFLT/*, ori_sc = *sc*/;
	DLO_Language next_la=DLO_LANG_DFLT, now_la=DLO_LANG_DFLT/*, ori_la = *la*/;
	DT16_ushort next_dir=DLO_DECIDE_BY_STR, now_dir=DLO_DECIDE_BY_STR/*, ori_dir = *dir*/;
	DT8_char	isOpenPunct_AtOtherDir=0;

DBG_MSG_SHOW_FUNC_NAME();

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
		  at = DL_GetCodeCategory(pwrk, str[iter]);
		  if(DL_CheckIfCodeDirective(at)){
			  if(now_sc == DLO_SCRIPT_DFLT || now_la==DLO_LANG_DFLT){
				  /* Script is not decided yet. */
				  DL_GetScriptLang(at.range, &now_sc, &now_la);
				  now_dir = GetSegDirectByScript(now_sc);
				  *sc = now_sc;
				  *la = now_la;
				  *dir= now_dir;
			  }else{
				/* Is the script the same? */
				DL_GetScriptLang(at.range, &now_sc, &now_la);
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
				next_dir = DL_GetWriteDirByFirstCode(pwrk, str+iter, cnt-iter, &next_sc, &next_la);	/* Get Next Direction */
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

/* Return 0:No direction implied. 1:direction implied. */
DT32_int DL_CheckIfCodeDirective(DL_CodeAttr at)
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
	//return 0;
}

/* Decide the write direction. If no direction implied of all string, return DLO_DECIDE_BY_STR. */
/* Also return its script and language if sc or la isn't NULL.									*/
DT16_ushort DL_GetWriteDirByFirstCode(pLayWrk pwrk, DT16_ushort *str, DT32_int cnt, DLO_Script *sc, DLO_Language *la)
{
	//Use the first code's write direction will be used.
	DT32_int i;
	DT16_ushort dir=DLO_DECIDE_BY_STR;
	DLO_Script	tmpScript;
	DLO_Language tmpLang;
	DL_CodeAttr	at;
	tmpScript = DLO_SCRIPT_DFLT;	tmpLang = DLO_LANG_DFLT;
	for(i=0;i<cnt;i++){
		at = DL_GetCodeCategory(pwrk, str[i]);
		if(DL_CheckIfCodeDirective(at)){
			DL_GetScriptLang(at.range, &tmpScript,&tmpLang);
			dir = GetSegDirectByScript(tmpScript);
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

//DT16_ushort DL_convOpen2Close_OLD(DT16_ushort ch)
//{
//	DL_CodeAttr at;
//	at = DL_GetCodeCategory(ch);
//	if(at.cate==DL_Punctuation_Open){
//		switch(ch){
//		case 0x0028:
//			return 0x0029;
//		case 0x005B:
//			return 0x005D;
//		case 0x007B:
//			return 0x007D;
//		}
//	}else if(at.cate==DL_Punctuation_Close){
//		switch(ch){
//		case 0x0029:
//			return 0x0028;
//		case 0x005D:
//			return 0x005B;
//		case 0x007D:
//			return 0x007B;
//		}
//	}else{
//		return ch;
//	}
//
//	return ch;	
//}

DT16_ushort DL_convOpen2Close(pLayWrk pwrk, DT16_ushort ch)
{
	DL_CodeAttr at;
	DT16_ushort codeout=ch;
	DT32_int	i;

	i = 0;
	at = DL_GetCodeCategory(pwrk, ch);
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
