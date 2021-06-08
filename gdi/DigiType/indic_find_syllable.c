#include "indic_find_syllable.h"

#define EN_DEVA_SYALLABLE

#define _no (C_RESERVED)
#define _se (C_SIGN_NESAL)
#define _vi (C_INDEPENDENT_VOWEL)
#define _cn (C_CONSONANT_NUKTA)
#define _co (C_CONSONANT) 
#define _sn (C_SIGN_NUKTA)
#define _ys (C_SOLE_SYLLABLE)
#define _sv (C_SIGN_VIRAMA)
#define _vd (C_DEPENDENT_VOWEL)
#define _ss (C_SIGN_STRESS)
#define _sc (C_SIGN_ACCENT)
#define _zw (C_ZERO_WIDTH)
/*Tamil*/
#define _lm  (C_LENGTH_MARK)      /*as tamil code 0x0bd7*/ 
#define _bl  (C_BOTH_VOWEL_LEFT)  /*as tamil code 0x0bc6,0x0bc7*/ 
#define _br  (C_BOTH_VOWEL_RIGHT) /*as tamil code 0x0bbe*/
/*Bengali*/
#define _vdp (_vd | P_PREVIOUS)
#define _blp (_bl | P_PREVIOUS)
#define _vdb (_vd | P_BOTH)


#define NON_INCLUDE 0x00ff

#define DEVANAGARI_START 0x0900U
#define DEVANAGARI_END   0x097fU
#define DEVANAGARI_END_P  0x0963U

#define TAMIL_START   0x0B80U
#define TAMIL_END     0x0BFFU
#define TAMIL_END_P   0x0BD7U /*The end of property array*/

/*
  group the language and property. 
*/
typedef struct  
{
	DT16_ushort start;
	DT16_ushort end;
	DT16_ushort end_p;
	CHAR_LOCATION location;
	CHAR_PROPERTY * property;
}E_LANG_PROP;



#define BENGALI_START   0x0980U
#define BENGALI_END     0x09FFU
#define BENGALI_END_P   0x09FAU /*The end of property array*/

#ifdef  EN_TAMIL_SYALLABLE
static CHAR_PROPERTY tamil_property[]={
	/*0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  a,  b,  c,  d,  e,  f,  */
	_no,_no,_se,_se,_no,_vi,_vi,_vi,_vi,_vi,_vi,_no,_no,_no,_vi,_vi, /*0x0B80~0x0B8F*/
	_vi,_no,_vi,_vi,_vi,_co,_no,_no,_no,_co,_co,_no,_co,_no,_co,_co, /*0x0B90~0x0B9F*/
	_no,_no,_no,_co,_co,_no,_no,_no,_co,_co,_co,_no,_no,_no,_co,_co, /*0x0BA0~0x0BAF*/
	_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,_no,_no,_no,_no,_br,_vd, /*0x0BB0~0x0BBF*/
	_vd,_vd,_vd,_no,_no,_no,_bl,_bl,_vd,_no,_vd,_vd,_vd,_sv,_no,_no, /*0x0BC0~0x0BCF*/
	_no,_no,_no,_no,_no,_no,_no,_lm, /*0x0BD0~0x0BD7*/
};
#endif 

#ifdef EN_BENGALI_SYALLABLE
static CHAR_PROPERTY bengali_property[]=
{
	/*0,  1,  2,  3, 4,  5,  6,  7,  8,  9,  a,  b,  c,  d,  e,  f,  */
	_no,_se,_se,_se,_no,_vi,_vi,_vi,_vi,_vi,_vi,_vi,_vi,_no,_no,_vi,/*0x0980~0x098f*/
	_vi,_no,_no,_vi,_vi,_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,/*0x0990~0x099f*/
	_co,_co,_co,_co,_co,_co,_co,_co,_co,_no,_co,_co,_co,_co,_co,_co,/*0x09a0~0x09af*/
	_co,_no,_co,_no,_no,_no,_co,_co,_co,_co,_no,_no,_sn,_ys,_br,_vdp,/*0x09b0~0x09bf*/
	_vd,_vd,_vd,_vd,_vd,_no,_no,_blp,_vdp,_no,_no,_vdb,_vdb,_sv,_ys/**/,_no,/*0x09c0~0x09cf*/
	_no,_no,_no,_no,_no,_no,_no,_lm,_no,_no,_no,_no,_cn,_cn,_no,_cn,/*0x09d0~0x09df*/
	_co,_co,_vd,_vd,_no,_no,_ys,_ys,_ys,_ys,_ys,_ys,_ys,_ys,_ys,_ys,/*0x09e0~0x09e3*/
	_co,_co,_ys,_ys,_ys,_ys,_ys,_ys,_ys,_ys,_ys,	/*0x09f0~0x09fa*/
};
#endif

#ifdef EN_DEVA_SYALLABLE
static CHAR_PROPERTY devanagari_property[]={
	/*0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  a,  b,  c,  d,  e,  f,  */
	_no,_se,_se,_se,_vi,_vi,_vi,_vi,_vi,_vi,_vi,_vi,_vi,_vi,_vi,_vi, /*0x0900~0x090f*/
	_vi,_vi,_vi,_vi,_vi,_co,_co,_co,_co,_cn,_co,_co,_co,_co,_co,_co, /*0x0910~0x091f*/
	_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,_co,_co, /*0x0920~0x092f*/
	_co,_cn,_co,_co,_cn,_co,_co,_co,_co,_co,_no,_no,_sn,_ys,_vd,_vd, /*0x0930~0x093f*/
	_vd,_vd,_vd,_vd,_vd,_vd,_vd,_vd,_vd,_vd,_vd,_vd,_vd,_sv,_no,_no, /*0x0940~0x094f*/
	_ys,_ss,_ss,_sc,_sc,_cn,_cn,_cn,_cn,_cn,_cn,_cn,_cn,_cn,_cn,_cn, /*0x0950~0x095f*/ 
	_ys,_ys,_vd,_vd, /*0x0960~0x0963*/    
};
#endif

/*
 A table is to represent the association between property and language.
*/
static E_LANG_PROP tbl_lan_prop[]={
#ifdef EN_DEVA_SYALLABLE
	{DEVANAGARI_START, DEVANAGARI_END, DEVANAGARI_END_P, L_DEVENAGARI, devanagari_property},
#endif
#ifdef  EN_TAMIL_SYALLABLE
	{TAMIL_START, TAMIL_END, TAMIL_END_P, L_TAMIL, tamil_property},
#endif

#ifdef EN_BENGALI_SYALLABLE
	{BENGALI_START, BENGALI_END, BENGALI_END_P, L_BENGALI, bengali_property},
#endif
};


#define GET_CLASS(prop) (MASK_CLASS & char_property)
#define GET_LOCATION(prop) (MASK_LOCATION & char_property)

static SYLLABLE_STATE states[][14]=
{
	           /*_no, _se, _vi, _cn,  _co,  _sn, _ys,  _sv, _vd, _ss, _sc, _lm, _bl, _br*/
	/*start_0*/	     { 1,    1,   2,   6,   10,    1,   1,    1,   1,   1,   1,   1,   1,   1},
	/*end_1*/        {-1,   -1,  -1,  -1,   -1,   -1,  -1,   -1,  -1,  -1,  -1,  -1,  -1,  -1}, 
	/*vi_2*/         {-1,    3,  -1,  -1,   -1,    4,  -1,   -1,  -1,   5,   1,  -1,  -1,  -1},  
	/*_vi+_se_3*/ 	 {-1,   -1,  -1,  -1,   -1,   -1,  -1,   -1,  -1,   5,   1,  -1,  -1,  -1},  
	/*_vi+_sn_4*/ 	 {-1,    3,  -1,  -1,   -1,   -1,  -1,   -1,  -1,   5,   1,  -1,  -1,  -1},
	/*_vi+_ss_5*/    {-1,   -1,  -1,  -1,   -1,   -1,  -1,   -1,  -1,  -1,   1,  -1,  -1,  -1}, 

	/*_cn_6*/ 		 {-1,    3,  -1,  -1,   -1,   -1,  -1,    7,   9,   5,   1,  -1,  12,   9},  

	/*_cn+_sv_7*/	 {-1,   -1,  -1,   6,    8,   -1,  -1,   -1,  -1,  -1,  -1,  -1,  -1,  -1}, 
	/*_cn+_sv+_co_8*/{-1,    3,  -1,  -1,   -1,    6,  -1,    7,   9,   5,   1,  -1,  12,   9},     
	/*_cn+_vd_9*/	 {-1,    3,  -1,  -1,   -1,    1,  -1,    1,  -1,   5,   1,  -1,  -1,  -1},   

	/*_co_10*/		 {-1,    3,  -1,  -1,   -1,    6,  -1,   11,   9,   5,   1,  -1,  12,   9}, 
	/*_co+_sv_11*/   {-1,   -1,  -1,   6,   10,   -1,  -1,   -1,  -1,  -1,   1,  -1,  -1,  -1},
	
	/*_cn+bl_12*/	 {-1,    3,  -1,  -1,   -1,   -1,  -1,    1,  -1,   5,   1,   9,  -1,   9},
};

/*
	Get the defined property of character.
*/
CHAR_PROPERTY get_property(UNI_CHAR uni_char)
{
	DT32_int i;
	for(i=0; i<TABLE_SIZE(tbl_lan_prop); i++)
	{
		 if( tbl_lan_prop[i].start<= uni_char  && uni_char <= tbl_lan_prop[i].end_p)
		 {
				return (*(tbl_lan_prop[i].property+ (uni_char - tbl_lan_prop[i].start))
						| tbl_lan_prop[i].location); 
		 }
		 else continue;
	}
	return NON_INCLUDE;
}

CHAR_CLASS get_class(UNI_CHAR uni_char)
{
	return  MASK_CLASS & get_property(uni_char);
}

CHAR_LOCATION get_location(UNI_CHAR uni_char)
{
	return  MASK_LOCATION & get_property(uni_char);
}


#define GET_CLASS(prop) (MASK_CLASS & char_property)
#define GET_LOCATION(prop) (MASK_LOCATION & char_property)

DT_BOOL indic_get_syllable(UNI_CHAR* p_unitxt, DT32_int len, DT32_int * p_end)
{
	return indic_get_syllable_ex(p_unitxt, len, p_end, 0);
}

DT_BOOL indic_get_syllable_ex(UNI_CHAR* p_unitxt, DT32_int len, DT32_int * p_end, SYLLABLE_STATE init_state)
{
	DT32_int ret=FALSE;
	CHAR_PROPERTY char_property;
	CHAR_LOCATION  char_location;
	SYLLABLE_STATE state;
	/*
	*/
	*p_end =0;
	char_property = get_property(*p_unitxt);
	char_location = GET_LOCATION(char_property);

	if(NON_INCLUDE ==GET_CLASS(char_property)){
		/*It don't confuse elements of syllable so return 
			a character as each time.*/
		(*p_end)++;
		if(len <= *p_end){
			ret = FALSE;
		}
		else
			ret = TRUE;
	}
	else
	{		
		state = states[init_state][GET_CLASS(char_property)];
		/*if(state=<0){(*p_end)++};*/
		while(state > 0)
		{
			(*p_end)++;
			if(*p_end >=len)
			{
				ret = FALSE;
				break;
			}
			char_property = get_property(* (p_unitxt+ (*p_end) )) ;
			/**/
			if(NON_INCLUDE == GET_CLASS(char_property) ||  char_location != GET_LOCATION(char_property) ){
				if( (*(p_unitxt+(*p_end))) == ZWJ ||  (*(p_unitxt+(*p_end))) == ZWNJ)
				{
					(*p_end)++;
					if(*p_end >=len)
					{
						ret = FALSE;
						break;
					}
				}
				ret = TRUE;
				break;
			}
			else
			{	
				state = states[state][GET_CLASS(char_property)];
				if(state<0){
					ret = TRUE;
					break;
				}
				else if(len <= *p_end){
					ret = FALSE;
					break;
				}
			}
		}
	}
	return ret;
}

