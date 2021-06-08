#ifndef __DCWARABIC_H
#define __DCWARABIC_H

#include "DcwLayout.h"

#define MAX_LIG_COMPONENTS 19

#define IS_ARABIC_HONORIFICS(x)		(((x)>=0x0610 && (x)<=0x0615) ? 1 : 0)
#define IS_ARABIC_POINTS(x)			((((x)>=0x064B && (x)<=0x0652) || (x)==0x0670) ? 1 : 0)	
#define IS_ARABIC_HAMZA(x)			((((x)>=0x0653 && (x)<=0x0655) || (x)==0x0674) ? 1 : 0)
#define IS_ARABIC_KORANIC_ANNO(x)	((((x)>=0x06D6 && (x)<=0x06DC) || ((x)>=0x06DF && (x)<=0x06E8) || ((x)>=0x06EA && (x)<=0x06ED)) ? 1 : 0)

#define IS_ARABIC_ZEROWIDTH(x)	( (IS_ARABIC_HONORIFICS(x) || IS_ARABIC_POINTS(x) || IS_ARABIC_HAMZA(x) || IS_ARABIC_KORANIC_ANNO(x)) ? 1 : 0 )


#define IS_OTHER_COMBINING_MARKS(x)	(((x)>=0x0656 && (x)<=0x065E) ? 1 : 0)
#define IS_ARABIC_TRANS_GLYPHS(x)	(((x)>=0xFC5E && (x)<=0xFC63) ? 1 : 0)

#define IS_Arabic_NSMs(x)	( (IS_ARABIC_TRANS_GLYPHS(x) || IS_ARABIC_POINTS(x) || IS_ARABIC_HAMZA(x) || IS_ARABIC_KORANIC_ANNO(x) || IS_OTHER_COMBINING_MARKS(x) || IS_ARABIC_HONORIFICS(x)) ? 1 : 0 )

//#define IS_ARABIC_POINTS(x)	(((x)>=0x064B && (x)<=0x0652)?1:0)

/* Arabic Shape. The value will be matched with the shape of an ArabicLigature. */
/* So please do not change the order of this enumeration.						*/
typedef enum {
    XIsolated=0,
    XFinal,
    XInitial,
    XMedial,
    XCausing,
	XTransparent,
	XShapeEnd
} ArabicShape;

/* Join type: JType_U, D, R are very usually in Arabic. */
typedef enum {
	JType_U=0,	/*Non-Joining*/
	JType_C,	/*Join-Causing*/
	JType_D,	/*Dual-Joining*/
    JType_R,	/*Right-Joining*/
	JType_T,	/*Transparent*/
	JType_L		/*Left-Joining*/	/*Never Occurs in Unicode Standard*/
} JoinType;

/* Arabic letter group: Each group has one or some letters. */
typedef enum {
    /* NonJoining */
    ArabicNone=0,
	ArabicSpace,

    /* Transparent */
    Transparent,

    /* Causing */
    Center,
    Tatweel,/*Kashida*/

    /* Arabic */
    /* Dual */
    Beh,
    Noon,
    Meem,
    Heh,
    KnottedHeh,
    HehGoal,
    SwashKaf,
    Yeh,
    Hah,
    Seen,
    Sad,
    Tah,
    Kaf,
    Gaf,
    Lam,
    Ain,
    Feh,
    Qaf,

    /* Right */
    Alef,
    Waw,
    Dal,
    TehMarbuta,
    Reh,
    HamzaOnHehGoal,
    YehWithTail,
    YehBarree,
	ArabicGroupsEnd
} ArabicGroup;

/* ArabicGroup's join type: the order should be match with ArabicGroup above. */
extern const JoinType ArabicGroupType[ArabicGroupsEnd];
//static const JoinType ArabicGroupType[ArabicGroupsEnd] =  {
//    /* NonJoining */
//    JType_U,	/*ArabicNone*/
//	JType_U,	/*ArabicSpace*/
//
//    /* Transparent */
//    JType_T,	/*Transparent*/
//
//    /* Causing */
//    JType_C,	/*Center*/
//    JType_C,	/*Tatweel*/
//
//    /* Arabic */
//    /* Dual */
//    JType_D,	/*Beh*/
//    JType_D,	/*Noon*/
//    JType_D,	/*Meem*/
//    JType_D,	/*Heh*/
//    JType_D,	/*KnottedHeh*/
//    JType_D,	/*HehGoal*/
//    JType_D,	/*SwashKaf*/
//    JType_D,	/*Yeh*/
//    JType_D,	/*Hah*/
//    JType_D,	/*Seen*/
//    JType_D,	/*Sad*/
//    JType_D,	/*Tah*/
//    JType_D,	/*Kaf*/
//    JType_D,	/*Gaf*/
//    JType_D,	/*Lam*/
//    JType_D,	/*Ain*/
//    JType_D,	/*Feh*/
//    JType_D,	/*Qaf*/
//
//    /* Right */
//    JType_R,	/*Alef*/
//    JType_R,	/*Waw*/
//    JType_R,	/*Dal*/
//    JType_R,	/*TehMarbuta*/
//    JType_R,	/*Reh*/
//    JType_R,	/*HamzaOnHehGoal*/
//    JType_R,	/*YehWithTail*/
//    JType_R		/*YehBarree*/
//};


/* Classified each code to an ArabicGroup. */
extern const DT8_uchar arabic_group[256];
//static const DT8_uchar arabic_group[256] = {
//	/*0x0600-0x0607*/
//    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
//	/*0x0608-0x060F*/
//    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
//
//	/*0x0610*/
//    Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, ArabicNone,
//    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
//
//	/*0x0620*/
//    ArabicNone, ArabicNone, Alef, Alef, Waw, Alef, Yeh, Alef,
//    Beh, TehMarbuta, Beh, Beh, Hah, Hah, Hah, Dal,
//
//	/*0x0630*/
//    Dal, Reh, Reh, Seen, Seen, Sad, Sad, Tah,
//    Tah, Ain, Ain, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
//
//    /*0x0640 */
//    Tatweel, Feh, Qaf, Kaf, Lam, Meem, Noon, Heh,
//    Waw, Yeh, Yeh, Transparent, Transparent, Transparent, Transparent, Transparent,
//
//	/*0x0650*/
//    Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent,
//    Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone,
//
//	/*0x0660*/
//    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
//    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, Beh, Qaf,
//
//	/*0x0670*/
//    Transparent, Alef, Alef, Alef, ArabicNone, Alef, Waw, Waw,
//    Yeh, Beh, Beh, Beh, Beh, Beh, Beh, Beh,
//
//    /* 0x680 */
//    Beh, Hah, Hah, Hah, Hah, Hah, Hah, Hah,
//    Dal, Dal, Dal, Dal, Dal, Dal, Dal, Dal,
//
//	/*0x0690*/
//    Dal, Reh, Reh, Reh, Reh, Reh, Reh, Reh,
//    Reh, Reh, Seen, Seen, Seen, Sad, Sad, Tah,
//
//	/*0x06A0*/
//    Ain, Feh, Feh, Feh, Feh, Feh, Feh, Qaf,
//    Qaf, Gaf, SwashKaf, Gaf, Kaf, Kaf, Kaf, Gaf,
//
//	/*0x06B0*/
//    Gaf, Gaf, Gaf, Gaf, Gaf, Lam, Lam, Lam,
//    Lam, Noon, Noon, Noon, Noon, Noon, KnottedHeh, Hah,
//
//    /* 0x6C0 */
//    TehMarbuta, HehGoal, HehGoal, HamzaOnHehGoal, Waw, Waw, Waw, Waw,
//    Waw, Waw, Waw, Waw, Yeh, YehWithTail, Yeh, Waw,
//
//	/*0x06D0*/
//    Yeh, Yeh, YehBarree, YehBarree, ArabicNone, TehMarbuta, Transparent, Transparent,
//    Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, Transparent, Transparent,
//
//	/*0x06E0*/
//    Transparent, Transparent, Transparent, Transparent, Transparent, ArabicNone, ArabicNone, Transparent,
//    Transparent, ArabicNone, Transparent, Transparent, Transparent, Transparent, Dal, Reh,
//
//	/*0x06F0*/
//    ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone, ArabicNone,
//    ArabicNone, ArabicNone, Seen, Sad, Ain, ArabicNone, ArabicNone, KnottedHeh
//};


/* Substitution Lookup Table */
typedef struct {
	DT16_ushort format;			/* Substitution Lookup Table format */
	DT16_ushort offset2Cover;	/* offset to Coverage Table from the start of Substitution Lookup Table*/
	DT16_ushort ligasetcnt;		/* LigatureSet count */
	/*DT16_ushort *ligsetoffset;*//* Modified by Jacky_20090901 for big endian compatible */	
	DT8_uchar	*ligsetoffset;	/* LigatureSet offset from the start of Substitution Lookup Table */
									/* It's a buf contains 2-bytes, little endian DT16_ushort */
}SubLookupTab;

/* Arabic Ligature, Arabic Shape mapping table. */
/* Mapping the code in 0x06xx area to Arabic Presentation Form A, B by it's shape or ligature. */
typedef struct{
	DT16_ushort leadcode;	/* leading code in 0x06xx area */
	DT16_ushort replacelem;	/* replaced code in Form A, B (including extension area)*/
	ArabicShape	shape;		/* replacelem's shape */
	DT16_ushort elementcnt;	/* elements count, if 0628+062E=FC07, then elementcnt=2. */
	DT16_ushort *combelem;/* A pointer to the sequence of the codes which will be combined to the leadcode. */
}ArabicLigature;

/* Properties of an Arabic glyph */
typedef struct{
	DT16_ushort		glyf1;
	ArabicGroup		group;
	JoinType		jtype;
	ArabicShape		shape;
}ArabicProperties;


/* Code shape's joining pair */
typedef struct {
    ArabicShape prevS;
    ArabicShape thisS;
} JoiningPair;

/* If the coming code's Jtype is JType_R and previous code's shape is XIntial,		*/
/* You can refer to ArabicJointab[2][3], so that the shape of coming code is XFinal.*/
extern const JoiningPair ArabicJointab[5][4];
//static const JoiningPair ArabicJointab[5][4] =
//{
//	/* Coming code's JoinType: */
//	/*			JType_U,				 JType_C,				JType_D,				JType_R				*/
//    { { XIsolated,XIsolated }, { XIsolated,XCausing }, { XIsolated,XInitial }, { XIsolated,XIsolated } }, /* XIsolated, Previous code's shape */
//    { { XFinal,	  XIsolated }, { XFinal,   XCausing }, { XFinal,   XInitial }, { XFinal,   XIsolated } }, /* XFinal */
//    { { XIsolated,XIsolated }, { XInitial, XCausing }, { XInitial, XMedial },  { XInitial, XFinal } }, /* XInitial */
//    { { XFinal,	  XIsolated }, { XMedial,  XCausing }, { XMedial,  XMedial },  { XMedial,  XFinal } }, /* XMedial */
//    { { XIsolated,XIsolated }, { XIsolated,XCausing }, { XIsolated,XMedial },  { XIsolated,XFinal } }, /* XCausing */
//};

/* Functions to get info in the dlo file. */
DT32_int DFS_GetSubLookupTab(pLayWrk pwrk, SubLookupTab *hd);
DT32_int DFS_SearchInCoverageTab(pLayWrk pwrk, SubLookupTab *sub, DT16_ushort ch);
DT32_int DFS_GetLigature(pLayWrk pwrk, DT32_ulong pos, DT16_ushort idx, ArabicLigature *al);

/* Arabic language processor functions. */
DT32_int RenderToBuf_Arabic(pLayWrk pwrk, DT_void *para);
DT32_int GetSeginfo_Arabic(pLayWrk pwrk, Str_Seg *seginfo);
DT32_int CalcPosition_Arabic(pLayWrk pwrk, DT_void *para);
DT32_int RenderByPos_Arabic(pLayWrk pwrk, DT_void *para);

DT32_int isArabicChars(pLayWrk pwrk, DT16_ushort ch);		// Dcw private defined. (from DcwUnicodeRange.h)
DT_BOOL  isArabicLetters(DT16_ushort ch);					// Defined by Unicode Data (from DcwBiDi.h)
DT_BOOL  isArabicCodeRange(pLayWrk pwrk, DT16_ushort ch);	// for other funcs use, no need to distinguish the 2 funcs above.

#endif
