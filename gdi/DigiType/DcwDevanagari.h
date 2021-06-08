#ifndef __DCWDEVANAGARI_H
#define __DCWDEVANAGARI_H

#include "indic_common.h"

typedef LayWrk * P_LAYWRK;
typedef LayWrk LAYWRK;
typedef Str_Seg * P_STR_SEG;
typedef Str_Seg STR_SEG;

#define isIndicsDevanagariChars(ch) (( ((ch)>=0x0900 && (ch)<=0x097f)\
									|| ((ch)>=0xE300 && (ch)<=0xE308)\
									|| ((ch)>=0xEF00 && (ch)<=0xEFFF)\
									|| ((ch)>=0xF200 && (ch)<=0xF3FF)\
									|| (ch)==0x25CC)?1:0)
#define IS_IndicsDevanagari_NSMs(ch)	((	((ch)>=0x0900 && (ch)<=0x0902)\
									|| 	(ch)==0x093A || (ch)==0x093C\
									|| 	((ch)>=0x0941 && (ch)<=0x0948)\
									|| 	((ch)==0x094D)\
									|| 	((ch)>=0xEF10 && (ch)<=0xEF13)\
									|| 	((ch)>=0xEF28 && (ch)<=0xEF2D)\
									|| 	((ch)>=0xEF32 && (ch)<=0xEF33)\
									) ? 1 : 0)

DT32_int RenderToBuf_Devanagari(P_LAYWRK pwrk, DT_void *para);
DT32_int Prerender_Devanagari(pLayWrk pwrk);
DT32_int GetSeginfo_Devanagari(P_LAYWRK pwrk, P_STR_SEG seginfo);
DT32_int Render_Devanagari(pLayWrk pwrk, DT_void *para);
DT32_int CalcPosition_Devanagari(pLayWrk pwrk, DT_void *para);
DT32_int RenderByPos_Devanagari(pLayWrk pwrk, DT_void *para);


#endif /*__DCWDEVANAGARI_H*/


