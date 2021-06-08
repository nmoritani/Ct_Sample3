/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#ifndef __DCWSHAPERVG_H
#define __DCWSHAPERVG_H

#include "DTplatform.h"
#include "DTbasedef.h"

#ifndef __cplusplus
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define DCWSHAPERVG_VERSION		0x00020002	/* major minor*/
#define DCWSHAPERVG_REL_DATE	201007220	/* date + 0~9 */

/**** Some Enabling Flags ****/
/* The flags & defines for OpenVG*/
#define DLO_OPENVG_ENABLED 0
//#if (1==DLO_OPENVG_ENABLED)
// #include <openvg.h>
//
// /* The return of the func DLO_ShapeStringVG() */
// #define DLO_VG_CREATEFONT_ERR	-1
// #define DLO_VG_BAD_LAYBUF		-2
// #define DLO_VG_MALLOC_ERR		-3
// #define DLO_VG_CREATEPATH_ERR	-4
//
// /* Temporary code used to set the path to a glyph in OpenVG */
// #define DLO_VG_FONTCODE		0x0E3B	/* used for myvgfont */
// #define DLO_STROKE_BY_MASK		1
//#endif

#define DLO_CODE_NOT_EXIST			-10000
// The values of these defines are for scaleMethod & will be the same as RAS_SCALE_XXXX, OUL_SCALE_XXXX....
#define DLO_BASE_RATIO				1000	// base ratio for DLO_NOT_SCALE
#define DLO_NOT_SCALE				0
#define DLO_SCALE_BY_XYSCALERATIO	0x0001	// scale by sizey when hori; by sizex when vert.
#define DLO_SCALE_BY_RATIO_FILEWIDE	0x0002
#define DLO_SCALE_BY_CODERANGE		0x0004
#define DLO_SCALE_BY_RASSCALERATIO	0x0008	// scale by sizex & sizey no matter hori or vert.
#define DLO_SCALE_BY_BINSCALERATIO	0x0010	// scale by sizex & sizey no matter hori or vert.
#define DLO_SCALED_SIZEXY(sz,rto) (((sz) * (DLO_BASE_RATIO) + ((rto)-1)) / (rto))


/* Outline Opcode */
#define DLO_MOVETO                1
#define DLO_LINETO                2
#define DLO_BEZIERTO              3
#define DLO_CLOSEPATH             4

/**** Maximum Definition ****/
//#ifndef DT_MAX_CODES_PER_STR
// #define DLO_MAXCODES_PER_STR_SEG	80
//#else 
// #define DLO_MAXCODES_PER_STR_SEG DT_MAX_CODES_PER_STR
//#endif
//
//#ifndef DT_MAX_GLYPHS_PER_STR
// #define DLO_MAXGLYPHS_PER_STR		80
//#else 
// #define DLO_MAXGLYPHS_PER_STR	DT_MAX_GLYPHS_PER_STR
//#endif

#define DLO_MAXCODES_PER_STR_SEG	((DT_MAX_CODES_PER_STR>DT_MAX_GLYPHS_PER_STR)?DT_MAX_CODES_PER_STR:DT_MAX_GLYPHS_PER_STR)	//20
//#define DLO_MAXGLYPHS_PER_STR		80
#define DLO_FONT_MAXSIZE			gDT_FONT_MAXSIZE			//48
#define DLO_FONT_EMSIZE				gDT_FONT_EMSIZE				//2048
#define DLO_MAX_OUL_SIZE_PER_GLYPH	gDT_MAX_OUL_SIZE_PER_GLYPH	//0x2000
//#define DLO_PRE_ALLOC_FONTS_CNT		30

/**** API Err_Succ Code ****/
#define DLO_SUCCESS               0

/* DLO_InitShaper(), DLO_unInitShaper() Error Code */
#define DLO_SUCCESS_BUT_BADLAYDATA	0x0001
#define DLO_BAD_HANDLE				-1
#define DLO_BAD_LAYDATA				-2
#define DLO_BAD_FONTDATA			-3
#define DLO_INVALID_FDL_CODEMODE	-4 /*Support Unicode Only*/
#define DLO_NOT_ENOUGH_LAYWKMEM		-5
#define DLO_NOT_ENOUGH_ENGINEWKMEM	-6
#define DLO_BAD_ENGINE_HANDLE		-7
#define DLO_FONTENGINE_NOT_SUPPORT	-8

/* DLO_ShapeString(), DLO_ShapeStringVG() Error Code */	/* 0:success; <0:error; >0:some situation. */
#define DLO_SUBTABLE_UNKNOW		 0x1004	// don't return
#define DLO_TABLE_NOT_FOUND		 0x1002	// don't return
#define DLO_BREAKLINE			 0x0002
#define DLO_EMPTY_FONT           0x0001
#define DLO_BAD_HANDLE			-1		/* re-definition, Same as above section */
#define DLO_MEM_NOT_ENF_GLYFSQ	-2
#define DLO_MEM_NOT_ENF_CARETSQ	-3
#define DLO_SCRIPT_NOT_SUPPORT	-4
#define DLO_LANG_NOT_SUPPORT	-5
#define DLO_ENGINEWKMEM_ERR		-6
#define DLO_UCS_ERR				-7
#define	DLO_FONTENGINE_NOT_SUPPORT	-8	/* re-definition, Same as above section */
#define DLO_INVALID_FONTSIZE	-9
#define DLO_NOT_ENOUGH_PATHMEM	-10
#define DLO_SPACING_ERR			-11
#define DLO_FONTSTYLE_ERROR		-12
#define DLO_UCS_STR_TOO_LONG	-13
#define DLO_TEMPBUF_NOT_ENOUGH	-14
#define DLO_SEG_ERROR			-15


/**** Glyph Bitmap Mode ****/
#define DLO_GRAY_MONO		0x0000
#define DLO_GRAY_16			0x0001
#define DLO_GRAY_256		0x0002
#define DLO_GLYPH_DEF		DLO_GRAY_16

/**** Glyph Bitmap Grade Values Mode ****/
#define DLO_GRADE_INDEX_0X00_0X0F	0	/* When GRAY16, gcolor is 0-15 */
#define DLO_GRADE_LINEAR_0X00_0XFF	1	/* When GRAY16, gcolor is 0x00, 0x11, 0x22...0xEE, 0xFF */
#define DLO_GRADE_MAX_FLAG			1

/**** Glyph Style: edge: bold, outline ****/
/* Edge Style Flag */
#define DLO_STYLE_NORMAL           0
#define DLO_STYLE_OUTLINE          1
#define DLO_STYLE_BOLD             2
#define DLO_STYLE_BOLD_RIGHT       3
#define DLO_STYLE_BOLD_DOWN        4
#define DLO_STYLE_BOLD_RIGHT_DOWN  5
#define DLO_STYLE_MAX_EDGE_FLAG    5
#define DLO_STYLE_MAX_EDGE_WIDTH   DT_STYLE_MAX_EDGE_WIDTH	//5
//#define DLO_STYLE_INNER_NORMAL	 254	/* It's used for drawing the inner of other style, like OUTLINE, BOLD...	*/
										/* Almost same as DT_STYLE_NORMAL, but differs when glyph had been moved.	*/
										/* Ex: THAI_thai, AV, AD, and TONE after UCONS have to shift to left.		*/
										/* When use this flag, please keep w_edge being the same as previous.		*/


/**** Layout buffer is bit base or byte base? ****/
/* These two flags should be combined with above. */
#define DLO_LAYOUT_BIT		0x0100	/* Combined with DLO_GRAY_MONO ONLY! */
#define DLO_LAYOUT_BYTE		0x0200

/**** String Layout Flags ****/
#define DLO_DATA_PREPARE_POS	0x01	/* Get glyph sequence and positioning */
#define DLO_DATA_RENDER			0x02	/* Get outline data, the origin(0,0) of the data is left-top. */
										/* The data are based on DLO_FONT_EMSIZE. */

/* alignment in DLO_LayBuf, when using  DLO_SCRIPT_DFLT, DLO_LANG_DFLT */
#define DLO_DECIDE_BY_STR	0x0000		/* decide by first encountered code which implies direction. */

#define DLO_LEFTTORIGHT		0x200E
#define DLO_RIGHTTOLEFT		0x200F

/* BiDirection Rule */
#define DLO_BIDI_UNIRULE	DT_BIDI_UNIRULE			/* default rule: according UAX #9: Unicode Bidirectional Algorithm	*/
#define DLO_BIDI_DCWRULE	DT_BIDI_DCWRULE			/* Dcw private implement rule.										*/

/* Drawing Method of an glyph, the drawmethod of DLO_CodePositioning. */
#define DLO_DRAW_NORMAL		0
#define DLO_AREA_NOT_DRAW	1

/* Some glyphs have to erase a rect before or after being drawn, not used yet. */
#define DLO_ERASE_BEFORE_DRAW	0x01
#define DLO_ERASE_AFTER_DRAW	0x02

/**** Script ****/
/* Please refer to the opentype spec "Script Tags" for the specific names. */
/* Only DLO_SCRIPT_DFLT, DLO_SCRIPT_latn, DLO_SCRIPT_arab, DLO_SCRIPT_hebr, DLO_SCRIPT_thai are valid now. */
typedef enum
{
	DLO_SCRIPT_DFLT=0,	/*Default: Decided by characters*/
	DLO_SCRIPT_latn,	/*Latin	*/
	DLO_SCRIPT_arab,	/*Arabic*/
	DLO_SCRIPT_thai,	/*Thai	*/
	DLO_SCRIPT_deva,    /*Devanagari*/
	DLO_SCRIPT_taml,    /*Tamil*/
	DLO_SCRIPT_hebr,	/*Hebrew*/
	DLO_SCRIPT_END		/*DLO_Script's End. Don't use this value.*/
}DLO_Script;

/**** Languages ****/
/* Please refer to the opentype spec "Language System Tags" for the specific names. */
/* Only DLO_LANG_DFLT, DLO_LANG_LAT, DLO_LANG_ARA, DLO_LANG_THA are valid now. */
typedef enum
{
	DLO_LANG_DFLT=0,	/*Default: Not specified*/
	DLO_LANG_LAT,		/*Latin*/
	DLO_LANG_JAN,		/*Japanese*/
	DLO_LANG_ZHT,		/*Chinese Traditional*/
	DLO_LANG_ZHS,		/*Chinese Simplified*/
	DLO_LANG_ARA,		/*Arabic*/
	DLO_LANG_THA=6,		/*Thai*/
	DLO_LANG_HIN=7,      /*Hindi*/
	DLO_LANG_TAM,       /*TAM*/
	DLO_LANG_IWR,		/*Hebrew*/
	DLO_LANG_ICN=10,	/*Icon*/
	DLO_LANG_end		/*DLO_Language's End. Don't use this value.*/
}DLO_Language;


/* 2012-02-22: langid consists of 2 bytes (an DT16_ushort value).						*/
/* the lower-byte stands for DLO_LANGTAB_ID, and the higher-byte stands for its version.*/
/* use the following macro to get the DLO_LANGTAB_ID or the version of the LANGTAB.		*/
#define DLO_GET_REAL_LANGTAB_ID(val)		((((DT16_ushort)(val))<<8)>>8)
#define DLO_GET_REAL_LANGTAB_VER(val)		(((DT16_ushort)(val))>>8)
#define DLO_MAKE_LANGTAB_ID_VAL(tid,ver)	(DT16_ushort)((((DT16_ushort)(ver))<<8) | ((DT16_ushort)(tid)))
typedef enum
{
	DLO_LANGTAB_THA			= 6,
	DLO_LANGTAB_HINDI		= 7,
	DLO_LANGTAB_ICN			= 10,
	DLO_LANGTAB_DESCENT		= 11,
	DLO_LANGTAB_RAS_SCALE	= 12,
	DLO_LANGTAB_BIN_SCALE	= 13,
	DLO_LANGTAB_GLOBAL		= 24,
	DLO_LANGTAB_RSB			= 25,
	DLO_LANGTAB_HINDI_SUB	= 26,
	DLO_LANGTAB_HINDI_POS1	= 27,
	DLO_LANGTAB_HINDI_POS2	= 28,
	DLO_LANGTAB_HINDI_POS3	= 29,
	DLO_LANGTAB_EMPTY = 0xFFFF
}DLO_LANGTAB_ID;

typedef enum {
	DLO_CHARATTR_LANGTAB_THAI		= DLO_LANGTAB_THA,
	DLO_CHARATTR_LANGTAB_ICON		= DLO_LANGTAB_ICN,
	DLO_CHARATTR_LANGTAB_DESCENT	= DLO_LANGTAB_DESCENT,
	DLO_CHARATTR_LANGTAB_RAS_SCALE	= DLO_LANGTAB_RAS_SCALE,
	DLO_CHARATTR_LANGTAB_BIN_SCALE	= DLO_LANGTAB_BIN_SCALE,
	DLO_CHARATTR_FONT_LRSB			= DLO_LANGTAB_RSB,

	DLO_CHARATTR_XYSCALERATIO=1001,	/* scale ratio by the ratio table */
	DLO_CHARATTR_ISXYSCALE_CHAR=1002, /* scale ratio by the ratio table */
	DLO_CHARATTR_HEIGHT_SHIFT=1003,
	DLO_CHARATTR_NORMAL_WIDTH=1004,
	DLO_CHARATTR_NORMAL_HEIGHT=1005,
	DLO_CHARATTR_ISOFFSETY_CHAR=1006,
	DLO_CHARATTR_GET_OFFSETY=1007,
	DLO_CHARATTR_RATIO_FILEWIDE=1008,	/* globalinfo, file-wide ratio*/
	DLO_CHARATTR_ISSCALE_FILEWIDE=1009,	/* globalinfo, file-wide ratio*/
	DLO_CHARATTR_RASSCALERATIO=1010,	/* scale ratio by the ratio table */
	DLO_CHARATTR_ISRASSCALE_CHAR=1011,	/* scale ratio by the ratio table */
	DLO_CHARATTR_BINSCALERATIO=1012,	/* scale ratio by the ratio table */
	DLO_CHARATTR_ISBINSCALE_CHAR=1013,	/* scale ratio by the ratio table */
	DLO_CHARATTR_GET_LOGHEIGHT=1014,	/* the estimate height log in FDL */
	DLO_CHARATTR_GET_LOGTOP=1015,
//	DLO_CHARATTR_GET_3IN1_VALUE=1016,	/* not support here, use OFFSETY, LOGHEIGHT, or LOGTOP instead. */


	DLO_CHARATTR_END
} DLO_CharAttr_Option;

/**** Font Engines ****/
typedef enum
{
	DLO_ENG_DCWOPENVG=1,			/* get outline from FDL font file				*/
	DLO_ENG_BDFRASTER,				/* get 1bit-bmp from BDF font file				*/
	DLO_ENG_DCWRASTER_MONO,			/* get a bit per pixel bmp from FDL font file	*/
	DLO_ENG_DCWRASTER_GRAY16,		/* get a byte per pixel bmp from FDL font file	*/
	DLO_ENG_DCWRASTER_GRAY256,		/* get a byte per pixel bmp from FDL font file	*/
	DLO_ENG_DIFRASTER_BIT,			/* get a bit per pixel bmp from DIF font file	*/
	DLO_ENG_DIFRASTER_BYTE,			/* get a byte per pixel bmp from DIF font file	*/
	DLO_ENG_END
}DLO_EngineType;

typedef enum {
	FSTYLE_VERT=0,		/* Now, horizontal only.	*/
	FSTYLE_SIZEX,		/* desired x size			*/
	FSTYLE_SIZEY,		/* desired y size			*/
	FSTYLE_F_EDGE,		/* font edge, such as bold, outline...*/
	FSTYLE_W_EDGE,		/* the width of the edge	*/
	FSTYLE_ITALIC,		/* italic amount in pixels	*/
	FSTYLE_P_UNDERLINE,	/* the position of underline*/
	FSTYLE_W_UNDERLINE,	/* the width of underline	*/
	FSTYLE_E_UNDERLINE, /* the extend of underline	*/
	FSTYLE_GRAD,		/* GRAY16, GRAY256...etc.	*/
//	FSTYLE_DEGREE,		/* 1/1000 degree rotated, not support yet	*/
	FSTYLE_SPACING,		/* spacing between 2 characters, now it's used for OUTLINE 		*/
						/* draw a bold font first then use this to draw a normal font.	*/
						/* don't used it generally, especially when underline is enabled*/
//	FSTYLE_WRITEDIR,	/* write direction: DT_LEFTTORIGHT or DT_RIGHTTOLEFT*//*Marked, because it's in DLO_LayAttr */
	FSTYLE_GRAD_VALUES,	/* grade values when GRAY16, DLO_GRADE_INDEX_0X00_0X0F or DLO_GRADE_LINEAR_0X00_0XFF*/
	FSTYLE_XBYTE_ALIGN,	/* xbytes alignment to calculate "xbytes" of DLO_LayBuf, default:4 bytes aligned	*/
	FSTYLE_HINTING,		/* hinting mode, 1 or 2 only*/
	FSTYLE_FORCE_MOVE_DOWN,	/* force to move some chars down. -1 or 0-1000 only */
	FSTYLE_BIDI_RULE,	/* DLO_BIDI_UNIRULE or DLO_BIDI_DCWRULE	*/

	FSTYLE_W_EDGE_26_6,	/* the width of the edge, 26.6	*/
	
	FSTYLE_End
} DLO_FontStyle_Option;

/**** Structures in the APIs ****/
typedef struct _DLO_LayAttr
{
	DLO_Script 	mainScript;	/*Default Script*/
	DLO_Language mainLang;	/*Default Language*/
	DT16_ushort	writedir;	/*Write direction, use DLO_DECIDE_BY_STR to be decide by the first code. */
	DT32_int	ucs_cnt;	/*Count of text(ucs_str)*/
	DT16_ushort	*ucs_str;	/*Text to layout, a sequence of unicodes*/
}DLO_LayAttr;

typedef struct _DLO_Font_Metrix
{
	DT32_int height;
	DT32_int ascent;
	DT32_int descent;
	DT32_int inleading;
	DT32_int exleading;
	DT32_int width;
	DT32_int overhang;
	DT32_int fontweight;
}DLO_Font_Metrix;

typedef struct _DLO_Point
{
	DT32_int x;
	DT32_int y;
}DLO_Point;

typedef struct _DLO_Vector2
{
	DT32_int vx;
	DT32_int vy;
}DLO_Vector2;

typedef struct _DLO_RECT
{
	DLO_Point	xy;		/* The start position of the rect, according to the coordinate system. */
	DLO_Vector2 hw;		/* The width & height of the rect, it can be positive or negative. */
}DLO_RECT;

typedef struct _DLO_CodePositioning
{
	DT32_int 	codeidx;	/*The start index of ucs_str, consider the n_per_glyf*/
	DT16_ushort	glyfidx;	/*The start index of glyf_seq*/
	DT16_ushort	n_per_glyf;	/*How many codes in ucs_str were presented as the glyfs. */
							/*0x0001: 1code=1glyf, 0x0002: 2codes=1glyf... */
							/*If n_per_glyf2>0x0100, means 1 code will be divided into 2 or more glyfs.	*/
							/*Decompose the code to several codes(glyf). (2<<8)+1: 1code=2glyf, (3<<8)+2: 2code=3glyf */
	DLO_Point	caretpos;	/*Caret position of the code, glyf_seq[glyfidx], ucs_str[codeidx]*/
	DLO_Point	oripos;		/*The origin position of the glyph, glyf_seq[glyfidx]. */
	DLO_Vector2	awvec;		/*advanced width vector of the glyph, glyf_seq[glyfidx]. */
	DLO_Vector2	adjvec;		/*adjustment vector of the glyph, glyf_seq[gplyfidx]. */
	DT32_int	drawmethod;	/*DLO_DRAW_NORMAL or DLO_AREA_NOT_DRAW */
	DLO_RECT	dmrect;		/*the area that drawmethod==DLO_AREA_NOT_DRAW applied. */
							/*DcwShapeStringVG() doesn't draw the path segments start(MOVE_TO) inside this area. */
}DLO_CodePositioning;

typedef struct _DLO_LayBuf
{
	/* Use the DLO_DATA_PREPARE_POS flag in DLO_ShapeString() to get the following info. */
	DT32_int		glyf_cnt;	/*Returned glyph count, the count of glyf_seq */
	DT16_ushort		glyf_seq[DLO_MAXCODES_PER_STR_SEG];	/*The returned sequence of glyphs, Arabic glyphs will be reversed. */
	DLO_CodePositioning	caret_seq[DLO_MAXCODES_PER_STR_SEG];	/*Positioning info for each glyph */
	DT16_ushort		writedir;	/*returned write direction while DLO_DECIDE_BY_STR being passed in DLO_LayAttr. */
	/* Use the DLO_DATA_PREPARE_POS flag in DLO_ShapeString() and DLO_EngineType==DLO_ENG_DCWOPENVG to get the following info. */
	DT32_int		eswidth;	/*the estimate width, the sum of advanced width */
	DT32_int		esheight;	/*the estimate height, the height of the line */
	/* Use the DLO_DATA_RENDER flag in DLO_ShapeString() and DLO_EngineType==DLO_ENG_DCWOPENVG to get the following info. */
	DT32_long		olDatabufSize; /*the size of olDatabuf in byte */
	DT8_char		*olDatabuf;	/*a buf pool to store the outline data of each glyph in glyf_seq */
	DT32_long		olSizebuf[DLO_MAXCODES_PER_STR_SEG]; /*an array of each glyph's outline data path count, the count of this array is glyf_cnt */
	/* Use the DLO_DATA_PREPARE_POS flag in DLO_ShapeString() and DLO_EngineType!=DLO_ENG_DCWOPENVG to get the following info. */
	DT32_int		bitcount;	/*bit count per pixel, now only 1 & 8 are supported */
	DT32_int		bmpwidth;	/*bmp width */
	DT32_int		bmpheight;	/*bmp height */
	DT32_int		xbytes;		/*how many bytes stand for a line in bmpbuf.*/
	DT32_int		bufsize;	/*the bmp buffer size of bmpbuf*/
	/* Use the DLO_DATA_RENDER flag in DLO_ShapeString() and DLO_EngineType!=DLO_ENG_DCWOPENVG to get the following info. */
	DT8_char		*bmpbuf;	/*the buffer to store bmp bit data*/
	DLO_Point		ltpos;		/*the start(left-top) of bmpbuf*/
}DLO_LayBuf, *pDLO_LayBuf;


typedef DT_void* DLO_Handle;

DT32_int DLO_InitShaper(DT8_char *laydata, DT_void *font, DLO_EngineType type, DT32_int fontsizehint, DLO_Handle *hShaper, 
						DT_void *altfont, DT32_int altfontcnt, DT_void *iconfont, DT32_int iconfontcnt);
DT_void  DLO_SetFontStyle(DLO_Handle hShaper, DLO_FontStyle_Option option, DT32_int value);
DT32_int DLO_ShapeString(DLO_Handle hShaper, DLO_LayAttr *layattr, DLO_LayBuf *laybuf, DT32_int flag);
// #if (1==DLO_OPENVG_ENABLED)
//  DT32_int DLO_ShapeStringVG(DLO_Handle hShaper,
//						DLO_LayBuf *laybuf, 
//                        DT32_int sizeX, DT32_int sizeY, DT_float origin[2],
//                        DT32_uint /*VGbitfield*/ paintModes,
//                        DT32_int /*VGboolean*/ allowAutoHinting);
//  DT32_int DLO_GetStringWidth(DLO_Handle hShaper,DLO_LayBuf *laybuf, DT32_int sizeX, DT32_int sizeY);
//  DT32_int DLO_GetStringHeight(DLO_Handle hShaper,DLO_LayBuf *laybuf,DT32_int sizeX, DT32_int sizeY);
// #endif
DT32_int DLO_DeShapeString(DLO_Handle hShaper, DLO_LayBuf *laybuf);

DT32_int DLO_GetCharAw(DLO_Handle hShaper, DT16_ushort ucs);
DT32_int DLO_GetFontRect(DLO_Handle hShaper, DLO_RECT *rt);
DT32_int DLO_GetFontMetrix(DLO_Handle hShaper, DLO_Font_Metrix *mtx);
DT32_int DLO_GetCharGBMP(DLO_Handle hShaper, DT16_ushort ucs, DT_void *bmp, DT32_int xbytes, DLO_RECT clip);
DT32_int DLO_GetCharOUL(DLO_Handle hShaper, DT16_ushort ucs, DT32_int gseq2idx, DT_void *path, DT32_long pathbytes, DT32_long *pathsize);
DT32_int DLO_FastCharOUL(DLO_Handle hShaper, DT16_ushort ucs, DT32_int gseq2idx, DT_void *path, DT32_long pathbytes, DT32_long *pathsize);

DT32_int DLO_unInitShaper(DLO_Handle hShaper);

#ifdef __cplusplus
}
#endif

#endif


