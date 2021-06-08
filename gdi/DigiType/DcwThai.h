#ifndef __DCWTHAI_H
#define __DCWTHAI_H

#include "DcwLayout.h"

#define isThaiChars(ch)	(((ch)>=0x0E00 && (ch)<=0x0E7F)?1:0)
#define IS_Thai_NSMs(ch)	((ch)==0x0E31 || ((ch)>=0x0E34 && (ch)<=0x0E3A) || ((ch)>=0x0E48 && (ch)<=0x0E4E)?1:0)

#define ThaiCode_NoDesc_0E0D	0x0E60
#define ThaiCode_NoDesc_0E10	0x0E63

#define ThaiClass DT16_ushort

#define CTRL	0x0000			/* Control Characters-Not display*/
#define NON		0x0001			/* Non classfied-Show directly	*/
#define CONS	0x0002			/* Consonants					*/
#define LV		0x0004			/* Leading Vowels				*/
#define FV1		0x0008			/* Following Vowels				*/
#define FV2		0x0010			/* Following Vowels-Below level	*/
#define FV3		0x0020			/* Following Vowels-Special		*/
#define BV1		0x0040			/* Below Vowels-Composed with TONE, AD1	*/
#define BV2		0x0080			/* Below Vowels-Composed with TONE		*/
#define AV1		0x0100			/* Above Vowels-Composed with TONE, AD1	*/
#define AV2		0x0200			/* Above Vowels-Composed with TONE		*/
#define AV3		0x0400			/* Above Vowels-Composed with TONE, AD2	*/
#define AD1		0x0800			/* Above Diacritics-After CONS, BV1, AV1*/
#define AD2		0x1000			/* Above Diacritics-After CONS, AV3		*/
#define AD3		0x2000			/* Above Diacritics-After CONS only		*/
#define BD		0x4000			/* Below Diacritics				*/
#define TONE	0x8000			/* TONE marks-After CONS, BV, AV*/

#define FV  (FV1|FV2|FV3)
#define BV  (BV1|BV2)
#define AV  (AV1|AV2|AV3)
#define VOW (LV|BV|AV)
#define AD  (AD1|AD2|AD3)
#define DCT (AD|BD)

#define isFORWARD(ch)	(ch&CONS||ch&LV||ch&FV)
#define isDEAD(ch)		(ch&BV||ch&BD||ch&AV||ch&AD||ch&TONE)

typedef enum {
    NCONS=0,		/* Normal Consonants, Base level		*/
    UCONS,			/* Upper-tail Consonants, Above level	*/
    SCONS,			/* Split-tail Consonants, Below level	*/
    BCONS,			/* Below-tail Consonants, Below level	*/
} Thai_CONS;

#define isUCONS(usch)	(usch==0x0E1B||usch==0x0E1D||usch==0x0E1F/*||usch==0x0E2C*/)	/* Jacky_20080818 */
#define isSCONS(usch)	(usch==0x0E0D||usch==0x0E10)
#define isBCONS(usch)	(usch==0x0E0E||usch==0x0E0F)

#define isBDEAD(usch)	(usch==0x0E38||usch==0x0E39||usch==0x0E3A)

#define	AM	FV1		/* Traditional Thai Principles, Composed from 0x0E32+0x0E4D	*/
#define AD4	AD1		/* Traditional Thai Principles, Use 0x0E4D as a vowel		*/

extern const DT16_ushort Thai_class[128];
//static const DT16_ushort Thai_class[128] = {
///*0E00*/   NON,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,
///*0E10*/  CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS,
///*0E20*/  CONS,CONS,CONS,CONS, FV3,CONS, FV3,CONS,CONS,CONS,CONS,CONS,CONS,CONS,CONS, NON,
///*0E30*/   FV1, AV2, FV1,  AM, AV1, AV3, AV2, AV3, BV1, BV2,  BD, NON, NON, NON, NON, NON,
///*0E40*/    LV,  LV,  LV,  LV,  LV, FV2, NON, AD2,TONE,TONE,TONE,TONE, AD1, AD4, AD3, NON,
///*0E50*/   NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON,
///*0E60*/  CONS, NON, NON,CONS, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON,
///*0E70*/   NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON, NON
//};

/* Top Level:	TONE, AD1, AD2				*/
/* Above Level:	AV, AD3						*/
/* Base Level:	CONS, LV, FV				*/
/* Below Level:	BV, BD						*/

/* ThaiGroup is used for mapping into the Thai_input_tab easily.	*/
typedef enum{
	iCTRL = 0,
	iNON,
	iCONS,
	iLV,
	iFV1,
	iFV2,
	iFV3,
	iBV1,
	iBV2,
	iAV1,
	iAV2,
	iAV3,
	iAD1,
	iAD2,
	iAD3,
	iBD,
	iTONE
} ThaiGroup;


/****************************************************************************************/
/* Basic Rules: 1. Every display cell begins with base level. (NON|LV|FV|CONS)			*/
/*				2. CONS + (AV1|AV2|AV3|BV1|BV2) + (TONE|BD|AD1|AD2)						*/
/*				3. CONS + (AD3)															*/
/* StrictCheck:	__|--------------Display Cell-----------------------|__					*/
/*				__|-----forward-----|----------dead-----------------|__					*/
/*				  | (NON|LV|FV|CON)									|					*/
/*				  |	(CONS)			+ (BV1|AV1)]	+ (TONE|AD1)	|					*/
/*				  | (CONS)			+ (AD2|AD3|BD)					|					*/
/*				  | (CONS)			+ (BV2|AV2)		+ (TONE)		|					*/
/*				  |	(CONS)			+ (AV3)			+ (TONE|AD2)	|					*/
/* PS: FV=(FV1|FV2|FV3)																	*/
/****************************************************************************************/

/* Mode0: pass through, Mode1: basic rules, Mode2:strict check.	*/
/* a-a-r: means Mode0 accept, Mode1 accept, Mode2 reject		*/
/* A: accept,		a-a-a, next display cell					*/
/* C: compose,		a-a-a, same display cell					*/
/* S: strict reject,a-a-r, next display cell					*/
/* R: reject,		a-r-r, next display cell					*/
/* X: non-display,	a-a-a, non-display							*/

/***************Thai Showing_Value table*************************/
/* For display, only Mode1:Basic Rules are required.			*/
/* For input method, both Mode1 and Mode2 are required.			*/
/* The Thai_input_tab contains the meaning of Mode0,1,2.		*/
/* use Thai_input_tab[Cn-1's ThaiGroup][Cn's ThaiGroup]			*/
extern const DT8_char Thai_input_tab[17][17];
//static const DT8_char Thai_input_tab[17][17] = {
//		 /*CTRL, NON,CONS,  LV, FV1, FV2, FV3, BV1, BV2, AV1, AV2, AV3, AD1, AD2, AD3,  BD,TONE*/ /* Cn */
///*CTRL*/	'X', 'A', 'A', 'A', 'A', 'A', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///* NON*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///*CONS*/	'X', 'A', 'A', 'A', 'A', 'S', 'A', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C',
///*  LV*/	'X', 'S', 'A', 'S', 'S', 'S', 'S', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///* FV1*/	'X', 'S', 'A', 'S', 'A', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///* FV2*/	'X', 'A', 'A', 'A', 'A', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///* FV3*/	'X', 'A', 'A', 'A', 'S', 'A', 'S', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///* BV1*/	'X', 'A', 'A', 'A', 'A', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'C', 'R', 'R', 'R', 'C',
///* BV2*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'C',
///* AV1*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'C', 'R', 'R', 'R', 'C',
///* AV2*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'C',
///* AV3*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'C', 'R', 'R', 'C',
///* AD1*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///* AD2*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///* AD3*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',
///*  BD*/	'X', 'A', 'A', 'A', 'S', 'S', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 
///*TONE*/	'X', 'A', 'A', 'A', 'A', 'A', 'A', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R'
///*Cn-1*/
//};

#define isSameCell(ch)	(ch=='C')
#define isNextCell(ch)	(ch=='A'||ch=='S'||ch=='R')
#define isNonDisp (ch)	(ch=='X')


/* Thai language processor functions. */
DT32_int RenderToBuf_Thai(pLayWrk pwrk, DT_void *para);
DT32_int GetSeginfo_Thai(pLayWrk pwrk, Str_Seg *seginfo);
DT32_int CalcPosition_Thai(pLayWrk pwrk, DT_void *para);
DT32_int RenderByPos_Thai(pLayWrk pwrk, DT_void *para);

#endif
