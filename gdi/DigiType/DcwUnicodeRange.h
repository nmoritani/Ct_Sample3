#ifndef __DCWUNICODERANGE_H
#define __DCWUNICODERANGE_H

#include "DcwShaperVG.h"
#include "DcwLayout.h"

/* Combining Diacritical Marks area: Vietnamese use 5 codes in the area... */
#define IS_CDMs(ch) (((ch)>=0x0300 && (ch)<=0x036F) ? 1 : 0)	/* CDMs are also NSMs */

/* The representations of Arabic code range area. */
#define DL_Arabic_Basic_Key		0x0627
#define DL_Arabic_FormA_Key		0xFB50
#define DL_Arabic_FormB_Key		0xFE70
#define DL_Arabic_DcwPUA_Key	0xE000

typedef enum 
{
    DL_NoCategory,

    DL_Mark_NonSpacing,          /*   Mn */
    DL_Mark_Enclosing,           /*   Me */
	DL_Mark_SpacingCombining,    /*   Mc */

    DL_Separator_Space,          /*   Zs */
	
    DL_Other_Control,            /*   Cc */
    DL_Other_Format,             /*   Cf */
	DL_Bidi_Control,
	DL_ZeroWidth_Format,

    DL_Number_DecimalDigit,      /*   Nd */

    DL_Letter_Uppercase,         /*   Lu */
    DL_Letter_Lowercase,         /*   Ll */
    DL_Letter_Modifier,          /*   Lm */
    DL_Letter_Other,             /*   Lo */

    DL_Punctuation_Open,         /*   Ps */
    DL_Punctuation_Close,        /*   Pe */
    DL_Punctuation_Other,        /*   Po */

	DL_Symbol_Currency,          /*   Sc */

    DL_Symbol_Other              /*   So */

} DL_CodeCategory;



typedef enum 
{
	DL_Not_In_Range,
	DL_Range_INHERIT,
	DL_Range_Special,
	DL_Range_Latin,
	DL_Range_Greek=DL_Range_Latin,		/* temporary	*/
	DL_Range_Cyrillic=DL_Range_Latin,	/* temporary	*/
	DL_Range_Armenian=DL_Range_Latin,	/* temporary	*/
	DL_Range_Thai,						
	DL_Range_Georgian,					/* not support	*/
	DL_Range_Runic,						/* not support	*/
	DL_Range_Ogham,						/* not support	*/
	DL_Range_Arabic,
	DL_Range_Hebrew,					
	DL_Range_Syriac,					/* not support	*/
	DL_Range_Thaana,					/* not support	*/
	DL_Range_Han,						/* not support	*/
	DL_Range_Bopomofo,					/* not support	*/
	DL_Range_Devanagari,
	DL_Range_Tamil
} DL_CodeRange;


/* Code attribute*/
typedef struct  {
	DL_CodeRange range;
	DL_CodeCategory cate;
} DL_CodeAttr;



/************ Functions ******************************************************************************************/
DL_CodeRange DL_DivideStrByScript(pLayWrk pwrk, DT16_ushort *str, DT16_ushort cnt, DT16_ushort idxb, DT16_ushort *idxe);
DT32_int DL_DivideStrByScript_New(pLayWrk pwrk, DT16_ushort *str, DT16_ushort cnt, DT16_ushort idxb, DT16_ushort *idxe, 
								  DT32_int writedir, DLO_Script *sc, DLO_Language *la, DT16_ushort *dir);
DL_CodeAttr	 DL_GetCodeCategory(pLayWrk pwrk, DT16_ushort ch);
DT16_ushort	 DL_GetWriteDirByFirstCode(pLayWrk pwrk, DT16_ushort *str, DT32_int cnt, DLO_Script *sc, DLO_Language *la);
DT16_ushort	 DL_convOpen2Close(pLayWrk pwrk, DT16_ushort ch);

DT_void		 DL_GetScriptLang(DL_CodeRange ra, DLO_Script *sc, DLO_Language *la);
DT32_int	 DL_CheckIfCodeDirective(DL_CodeAttr at);

#endif
