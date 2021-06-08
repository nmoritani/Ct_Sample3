#ifndef __DCWHEBREW_H
#define __DCWHEBREW_H

#include "DcwLayout.h"

#define IS_Hebrew_NSMs(ch)	(((ch)>=0x0591 && (ch)<=0x05C7 && (ch)!=0x05BE && (ch)!=0x05C0 && (ch)!=0x05C6)?1:0)

/* This value is used to define how to deal with Marks & Point in Hebrew.	*/
/* 0: Don't filter Marks & Points, Hebrew Presentation Form will be used.	*/
/* 1: Marks & Points will be replaced by 0x25CC.							*/
/*    If 0x25CC doesn't exist, it seems Marks & Points are filtered.		*/
/*    If 0x25CC exists, Marks & Points are shown as 0x25CC (dotted circle).	*/
/* You can #define it instead of a const value to avoid the if-else operate.*/
/* Or, you can move this value to DTplatform.h or other *.h to be decided by user.*/
static const DT32_int isFilter_MarksPoints_of_Hebrew = 1;

typedef enum{
	Hiriq	= 0x05B4,
	Patah	= 0x05B7,
	Qamats	= 0x05B8,
	Holam	= 0x05B9,
	Rafe	= 0x05BF,
	Dagesh	= 0x05BC,
	ShinDot = 0x05C1,
	SinDot	= 0x05C2
}Hebrew_Spec_Codes;

typedef enum{
	Hebr_Cantil_Marks	= 0,
	Hebr_Points			= 1,
	Hebr_Punctuation	= 2,
	Hebr_Letters		= 3,
	Hebr_Yiddish		= 4,
	Hebr_END
}Hebrew_CodesType;

DT16_ushort ModifygseqElem(pLayWrk pwrk, DT16_ushort g1idx, DT16_ushort g2idx, DT16_ushort idx, DT16_ushort glyf, DT16_ushort cnt);

DT8_uchar isHebrewMarksOrPoints(DT16_ushort ucs);
DT_void	  convHebrewUcs2gseq(pLayWrk pwrk);
DT_void	  convHebrewUcs2gseq_MarksPointsFiltered(pLayWrk pwrk);


DT32_int RenderToBuf_Hebrew(pLayWrk pwrk, DT_void *para);
DT32_int GetSeginfo_Hebrew(pLayWrk pwrk, Str_Seg *seginfo);
DT32_int CalcPosition_Hebrew(pLayWrk pwrk, DT_void *para);
DT32_int RenderByPos_Hebrew(pLayWrk pwrk, DT_void *para);

#endif
