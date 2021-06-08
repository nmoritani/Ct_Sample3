#ifndef __DCWLAYOUT_H
#define __DCWLAYOUT_H

#include "DcwShaperVG.h"

//#define _SPEEDTEST		/* Default: disabled. */	/* Enable this to output the Elapsed CPU clocks by printf(). */

#define DLO_TAB_NOT_EXIST -1

typedef struct _DcwShaperVG_Version
{
	DT32_int major;
	DT32_int minor;
	DT32_int date;
}DcwShaperVG_Version;

/* DcwShaperVG's working memory */
typedef struct _DLO_LayData
{
	DT8_char *laydata;		/* A pointer to a .dlo file data */
	DT32_long lWkMemsize;	/* Working memory size for layout */
	DT8_char *lWkMem;		/* A pointer to the working memory */
}DLO_LayData, *pDLO_LayData;

/* File Header */
typedef struct  {
	DT8_char	ident[8];		/* "DFShaper" */
	DT16_ushort version;		/* Version	  */
	DT16_ushort dlotabcnt;		/* DLO_Data_Table count */
	DT32_ulong  *offsetdlotab;	/* offset array[dlotabcnt] from file start */
}shaperheader;

/* DLO_Data_Table header */
typedef struct {
	DT16_ushort script;			/* The script this table used for */
	DT16_ushort lang;			/* The language this table used for */
	DT16_ushort subtabcnt;		/* SubLookupTab count */
	DT32_ulong  *offsetsubtab;	/* offset array[subtabcnt] from DLO_Data_Table */
}dlotabheader;

/* Coverage table */
typedef struct {
	DT16_ushort format;		/* Coverage Table format */
	DT16_ushort glyfcnt;		/* Glyph count */
	/*DT16_ushort *covarr;*/	/* Modified by Jacky_20090901 for big endian compatible */	
	DT8_uchar *covarr;		/* Coverage Array buf, 2 bytes, little endian DT16_ushort */
}CoverTab1;						/* Coverage table format 1 */

/* Used for Glyph Substitution */
typedef struct{
	DT16_ushort	idx;		/* The index of code in ucs_str */
	DT16_ushort	code;		/* the unicode					*/
	DT16_ushort	idx_gseq1;	/* The index of glyf1 in gseq1	*/
	DT16_ushort	glyf1;		/* The glyph to replace code after process1: such as ReplaceLetter() in Arabic	*/
	DT16_ushort	n_per_glyf1;/* How many codes in ucs_str were presented as this glyf1. 1: 1code=1glyf, 2: 2codes=1glyf */
								/* If n_per_glyf1>0x0100, means 1 code will be divided into 2 or more glyfs.	*/
								/* Decompose the code to several codes(glyf1). (2<<8)+1: 1code=2glyf, (3<<8)+2: 2code=3glyf */
	DT16_ushort	idx_gseq2;	/* The index of glyf2 in gseq2	*/
	DT16_ushort	glyf2;		/* The glyph to replace code after process2: such as ligature match	in Arabic	*/
	DT16_ushort	n_per_glyf2;/* How many codes in ucs_str were presented as this glyf2. 1: 1code=1glyf, 2: 2codes=1glyf */
								/* If n_per_glyf2>0x0100, means 1 code will be divided into 2 or more glyfs.	*/
								/* Decompose the code to several codes(glyf2). (2<<8)+1: 1code=2glyf, (3<<8)+2: 2code=3glyf */
}GlyphSeq;

/* Used for glyph render */
typedef struct
{
//	DT32_int 	codeidx;		/*The index of ucs_str								*/
	DT16_ushort codeidx;		/*The index of ucs_str								*//*20110729: Modified by Jacky to reduce memory usage.	*/
	DT16_ushort	glyfidx;		/*The glyph's index of the glyf_seq	in DLO_LayBuf	*/
//	DT16_ushort	direct;			/*The direction of the glyph according to its script*//*20110729: Marked by Jacky to reduce memory usage.	*/
	DLO_Vector2	aw;				/*Advanced Width									*/
	DLO_Point	leftup;			/*The start point of the glyph in the seg			*/
}CodeAw;

/* segment information before render */
typedef struct{
	DT16_ushort		ustart;		/* seg's start position in ucs_str */
	DT16_ushort		uend;		/* seg's end   position in ucs_str */
	DLO_Script		script;		/* seg's script*/	
	DLO_Language	lang;		/* seg's lang  */
	DT32_int		sw;			/* seg's width */
	DT32_int		sh;			/* seg's height*/
	DLO_Point		cpstart;	/* seg's start point. (where the previous seg ends. Use writedir, seg_dir & sw to get the real start point.) */
	DLO_Point		cpend;		/* seg's end point. (where this seg ends. "cpend" may equal to "cpstart".)*/
}Str_Seg;

/* font design information */
typedef struct{
	DT16_ushort	Thai_Top;		/* the pixels or proportion of the top part of a Thai glyph.	*/
	DT16_ushort	Thai_Above;		/* the pixels or proportion of the above part of a Thai glyph.	*/
	DT16_ushort	Thai_Base;		/* the pixels or proportion of the base part of a Thai glyph.	*/
	DT16_ushort	Thai_Below;		/* the pixels or proportion of the below part of a Thai glyph.	*/
	DT16_ushort	Thai_Shift;		/* the pixels or proportion that should be moved while UCONS+(AV,AD,TONE)	*/
}Font_Design_Thai;

typedef struct{
	DT32_long	nSize;			/* Table Size.										*/
	DT32_long	nOffset;		/* Offset to the table start position from fontdata	*/
	DT8_char	*fontdata;		/* Pointer to fontdata which contain this table.	*/
}Font_Design_Descent;


typedef struct {
	DT16_short nsLsb;
	DT16_short nsRsb;
}Font_LRSB;

/* Used for speeding up <= keep the fontcode info */
// The values of these defines are for scaleMethod & will be the same as RAS_SCALE_XXXX, OUL_SCALE_XXXX....
#define DLO_BASE_RATIO				1000	// base ratio for DLO_NOT_SCALE
#define DLO_NOT_SCALE				0
#define DLO_SCALE_BY_XYSCALERATIO	0x0001	// scale by sizey when hori; by sizex when vert.
#define DLO_SCALE_BY_RATIO_FILEWIDE	0x0002
#define DLO_SCALE_BY_CODERANGE		0x0004
#define DLO_SCALE_BY_RASSCALERATIO	0x0008	// scale by sizex & sizey no matter hori or vert.
#define DLO_SCALE_BY_BINSCALERATIO	0x0010	// scale by sizex & sizey no matter hori or vert.

// scale pixel based value to EM based value
#define DLO_ROOFDIFF(val,den)	((val)>0?((den)-1):-((den)-1))
#define DLO_ROUNDDIFF(val,den)	((val)>0?((den)/2):(-(den)/2))
#define DLO_OUL_ROOF_SCALED_PIX2EM(pix,sz) (((pix)*(gDT_FONT_EMSIZE) + DLO_ROOFDIFF(pix,sz)) / (sz))
#define DLO_OUL_FLOOR_SCALED_PIX2EM(pix,sz) ((pix)*(gDT_FONT_EMSIZE) / (sz))
#define DLO_OUL_ROUND_SCALED_PIX2EM(pix,sz) (((pix)*(gDT_FONT_EMSIZE) + DLO_ROUNDDIFF(pix,sz)) / (sz))

// scale EM based value to pixel based value
#define DLO_OUL_ROOF_EM2PIX(val,sz)		(((DT32_long)(val) * (sz) + DLO_ROOFDIFF(val,gDT_FONT_EMSIZE)) / (gDT_FONT_EMSIZE))
#define DLO_OUL_FLOOR_EM2PIX(val,sz)	(((DT32_long)(val) * (sz)) / (gDT_FONT_EMSIZE))
#define DLO_OUL_ROUND_EM2PIX(val,sz)	(((DT32_long)(val) * (sz) + DLO_ROUNDDIFF(val,gDT_FONT_EMSIZE)) / (gDT_FONT_EMSIZE))

// same as DCW_CALC_AW_AH() when gDT_FONT_EMSIZE=1000
#define DLO_CALC_AW_AH(aw,size)			DLO_OUL_ROOF_EM2PIX(aw,size)
#define DLO_ADJUST_W_H(wh,size)			DLO_OUL_FLOOR_EM2PIX(wh,size)

// scale logHeight to EM, then the macros above can be used
#define DLO_SCALE_LOGHEIGHT2EM(lh)		DLO_OUL_ROOF_SCALED_PIX2EM((DT32_long)lh, DLO_BASE_RATIO)
#define DLO_SCALE_LOGHEIGHT2PIX(lh,sz)	(((DT32_long)(lh) * (sz) + DLO_ROOFDIFF(lh,DLO_BASE_RATIO)) / (DLO_BASE_RATIO))

// for existFont (which font contains the code?)
#define DLO_CUR_DT_FONT			(1u)
#define DLO_ALT_DT_FONT			(2u)
#define DLO_ICON_DT_FONT		(3u)		// dif font
// The values are for checkedFlag
#define DLO_FONTCODEINFO_CHECKFLAG_EXIST	(0x0001u)	// including codeExist & existFont.
#define DLO_FONTCODEINFO_CHECKFLAG_SCALE	(0x0002u)	// including scaleMethod & scaleRatio
#define DLO_FONTCODEINFO_CHECKFLAG_AW		(0x0004u)
#define DLO_FONTCODEINFO_CHECKFLAG_AH		(0x0008u)
#define DLO_FONTCODEINFO_CHECKFLAG_LRSB		(0x0010u)	// including LSB & RSB
#define DLO_FONTCODEINFO_CHECKFLAG_MOVEY	(0x0020u)	// the original logHeight, logTop in FDL is also checked here. no scaled, no bolden
#define DLO_FONTCODEINFO_CHECKFLAG_LOGH		(0x0040u)	// the logHeight used for current string, scale and bold considered.
#define DLO_FONTCODEINFO_CHECKFLAG_LOGT		(0x0080u)	// the logTop used for current string, scale and bold considered.
typedef struct 
{
//	DT16_ushort	reserved;		// unicode	(can be comment)
	DT16_ushort	checkedFlag;	// 0: this code haven't been checked.(other values aren't correct.) 1: this code had been checked 
								// (can be represented as DT8_char) 

	DT8_uchar	codeExist;		// code exists in the fonts? 0: not exist, 1: exists.
	DT8_uchar	existFont;		// exists in which font? DLO_CUR_DT_FONT:cur_DT_Font; DLO_ALT_DT_FONT:alt_DT_Font; DLO_ICON_DT_FONT:icon_DT_Font
								// It can also act as codeExist do. 0 means not exist, else exists, then codeExist can be used for other purpose. 
	DT16_ushort	scaleRatio;		// scale ratio. default:1000
	DT16_ushort	scaleMethod;	// scale method. ex: DLO_NOT_SCALE, DLO_SCALE_BY_BINSCALERATIO...
	DT16_short	aw;				// the return value from getAwidth()
	DT16_short	ah;				// the return value from getAheight()
	DT16_short	x0;				// used for OVG to compensate the aw as DcwRaster do!	// dependent on CHECKFLAG_AW
	DT16_short	aw1000;			// used for OVG to compensate the aw as DcwRaster do!	// dependent on CHECKFLAG_AW
	Font_LRSB	lrsb;			// left(right)-side-bearing in the DLO_LANGTAB_RSB of fonts
	DT16_short	moveY;			// move up or down in the DLO_LANGTAB_DESCENT of fonts
	DT16_short	logHeight;		// the estimate un-scaled height log in FDL, 0~255, 0 means no info.
								// simply *4 to 1000 when BMP_MODE, scale to size by DLO_SCALE_LOGHEIGHT2PIX().
								// use DLO_SCALE_LOGHEIGHT2EM() to get the height based on EM, then scaleRatio can be applied.
	DT16_short	logTop;			
}FontCodeInfo, *pFontCodeInfo;

/* render a part of glyph to bmp buffer */
#define DCW_COPYIFBKZERO	0	/* SRCCOPY if destination is zero		*/
#define DCW_SETBKZERO		1	/* Set the bmp buffer zero from bpoff	*/
#define DCW_SETVALUE		2	/* Set the bmp buffer to the value		*/
typedef struct{
	DLO_Point	bpoff;		/* The offset from start point of the bmp buffer		*/
	DLO_Point	gpoff;		/* The offset from start point of the glyph				*/
	DT32_int	lenth;		/* how many pixels should be operated in width.			*/
	DT32_int	height;		/* how many lines should be operated in height.			*/
	DT32_int	operate;	/* The method of operation.	such as DCW_COPYIFBKZERO..	*/
}bmpGlyfOperate;
	
typedef struct{
	DT32_int	operate;	/* The method of operation. DLO_DRAW_NORMAL or DLO_AREA_NOT_DRAW */
	DLO_RECT	rect;		/* The rect that method applied. */
}GlyfOperate;

typedef struct{/**/
	DT32_int flags;
	DLO_Vector2	aw;				/*Advanced Width									*/
	DLO_Point	leftup;			/*The start point of the glyph in the seg			*/
	DT32_int offx;
}FontPosition;

/* Font Engine Functions */
typedef struct{
	DT32_int (*initFont)	(DT_void *pattr, DT8_char *fontdata, DT32_long wkmsz, DT8_char *wkm, DT_void *pwrk);
	DT32_int (*getOutline)	(DT_void *pattr, DT16_ushort ch, DT_void *op, DT32_long *bufsz, DT8_char **olbuf, DT32_long *pathsz);
	DT32_int (*getCharbmp)	(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int bmpw, DT32_int bmph, DT32_int x0, DT32_int y0, DT32_int xbytes, DT8_uchar *bmp, DT_void *op, DT32_int mode);
	DT32_int (*getDesignInfo)(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo);
	DT32_int (*chkGlyphExist)( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
	DT32_int (*getAwidth)	(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
	DT32_int (*getAheight)	(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
	DT32_int (*getLogh)		(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
	DT32_int (*getLogt)		(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
	DT32_int (*getHeight)	(DT_void *pattr );	// Used for estimate font matrics only. No ch required. // Don't use for other purpose.
	DT32_int (*getWidth)	(DT_void *pattr );	// Used for estimate font matrics only. No ch required. // Don't use for other purpose.
	DT32_int (*getExten)	(DT_void *pattr );	// Used for estimate font matrics only. No ch required. // Don't use for other purpose.
	DT32_int (*getAexten)	(DT_void *pattr, DT16_ushort ch );
	DT32_int (*getVexten)	(DT_void *pattr, DT16_ushort ch );
	DT32_int (*getEdge)		(DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r );
	DT32_int (*getAwidth2)	(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy);
	DT32_int (*uninitFont)	(DT_void *pattr );
	DT32_int (*getFontCodeInfo)(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT_void **pfcinfo);

	DT32_int (*getDesignGlobalInfo)(DT_void *pattr, DT16_ushort gidx, DT32_int option, DT_void **pdsninfo);
	DT32_long (*FDL_ReadInt)(DT8_char *fdl, DT32_long ofs, DT32_int size);
	/* Some Special functions */
	DT32_int (*getCharOul)(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_long bufsz, DT_void *olbuf, DT32_long *pathsz);
	DT32_int (*fastCharOul)(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_long bufsz, DT_void *olbuf, DT32_long *pathsz);
	DT32_int (*getAwidth_pix)(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
}FontEngine_Funcs;

typedef struct {
	DT32_int 	codeidx;	/*The index of ucs_str		*/
	DT16_ushort	glyfidx;	/*The index of reordertext	*/
}CodevsGlyph;

/*----------------------------------------------------------------------*/
/* Working Memory                                                       */
/*----------------------------------------------------------------------*/
#define DLO_SEG_LIMIT	  (DT_MAX_CODES_PER_STR) //DLO_MAXCODES_PER_STR_SEG	//64
#define DLO_RAS_ATTR_SIZE 128	/* the size for ras_attr */
#define DLO_WKMSIZE_STEP  DT_BLOCKSIZE	/* the increasing step for working memory */

//Values for copyMethod
#define DLO_CPY_NOT_SPECIFY		(0x00)
#define DLO_CPY_NEEDS_ORCPY		(0x01)

typedef struct
{
	/* Total working Memory, including DcwShaper & Font Engine */
	DT32_long	TotalWkmsize;

	/* Specified Data */
	DLO_LayData dlowkm;
	DLO_LayAttr *attr;

	/* Point to DigiTypeAPI's working memory: DT_Fontwrk. *//* Added by Jacky_20100811 */
	DT_void		*pdtfwrk;		/* typecast to pDT_Fontwrk */
	DT_void		*cur_DT_Font;	/* typecast to DT_Font*, point to the DT_Font that are used now.*/
	DT_void		*alt_DT_Font;	/* typecast to DT_Font*, point to the DT_Font of altfont(bkfont)*/
	DT32_int	altfontcnt;		/* counts of bk_DT_Font, now 0 or 1 only.						*/
	DT_void		*icon_DT_Font;	/* typecast to DT_Font*, point to the DT_Font of iconfont.		*/
	DT32_int	iconfontcnt;	/* count of icon_DT_Font, now 0 or 1 only.						*/
	FontEngine_Funcs iconfuncs;	/* Icon Font engine(DIF_Raster) functions' pointer.				*/
	DT_void		*icon_attr;		/* similar as ras_attr, but for DifRaster_Attr use.				*/

	/* Some info for Font & DigiType_ovg */
	DT_void *ras_attr;	/* A pointer to a dynamic allocated buf(rattrbuf), typecast (to DcwOpenVG_Attr) while you need. */
						/* A buffer to store something for DigiType_ovg */
	DT8_char	*fondata;		/* A pointer to font file data, such as FDL or BDF... */
	DT_BOOL		bUseArabicPUA;	/* If cur_DT_Font, alt_DT_Font or icon_DT_Font contains 0x0627, 0xFB50, 0xFE70, and 0xE000, it will be DT_TRUE, else DT_FALSE */
								/* DT_FALSE: fonts don't contain arabic PUA, 0xE000-0xE07F won't be treat as Arabic Letters.	*/
								/* DT_TRUE: fonts contain arabic PUA, 0xE000-0xE07F will be treat as Arabic Letters.			*/

	/* .dlo data */
	DT8_uchar	*dlo;			/* A pointer to dlo file data */
	DT32_ulong	curpos;			/* Current position in dlo file data */
	DT32_ulong	dlotaboff[/*256*/8];	/* DLO_Data_Table offset in dlo. Maximum 256 tables. *//*20110804: 256->8 Jacky for reduce memory. Only Arabic use this.*/
	DT32_ulong	subtaboff[/*32*/8];	/* SubLookupTab offset array per DLO_Data_Table. Maximum 32 *//*20110804: 256->8 Jacky for reduce memory. Only Arabic use this.*/
	shaperheader header;		/* dlo file header */
	dlotabheader dloheader;		/* dlo table header */
	DT16_ushort	cur_dlotab_idx;	/* The index of current used DLO_Data_Table */
	DT32_int	dlo_tab_exist;	/* Is there any specified DLO_Data_table? */
	DT32_ulong	offtosubtab;	/* offset to SubLookup Table from file start */
	DT32_int	sub_tab_exist;	

	/* Code String Control */
	DT16_ushort	seg_start;		/* start of the segment (Each segment is divided according the language.) */
	DT16_ushort	seg_end;		/* end of the segment		*/
	DT16_ushort	seg_dir;		/* direction of the segment */
	DT16_ushort	seg_curpos;		/* current position of the segment */	/* Useless now */
	DLO_Script	seg_script;		/* script of the segment    */
	DLO_Language seg_lang;		/* language of the segment  */
	DT32_int	segw;			/* width of the segment     */
	DT32_int	segh;			/* height of the segment    */

	/* Layout buffer */
	DT32_int	rendermode;							/* DLO_DATA_PREPARE_POS or DLO_DATA_RENDER */
	DT8_uchar	copyMethod;							/* the bmp copy method (bmpcpy, bmpHIcpy, bmpORcpy)			*/
													/* DLO_CPY_NOT_SPECIFY, DLO_CPY_NEEDS_ORCPY					*/
	DT8_uchar	bHindi;								/* if the string contains Hindi chars (deal by Hindi Module)*/
	DT8_uchar	bMinusLRsb;							/* if the string might contains minus lsb, Rsb.				*/
	DT8_uchar	lastfedge;							/* for distinguish last raster mode for DT_GRAYxxBMP_MODE	*/
													/* use this to decide the bmp copy method(copyMethod).		*/
													/* if lastfedge is Bold and now is normal, use bmpORcpy()	*/
													/* for the case of 0x0915+0x0041 (rsb issue of draw outline)*/
	DLO_LayBuf	*lobuf;								/* A pointer to the input DLO_LayBuf*/
	DT16_ushort	gseq1[DLO_MAXCODES_PER_STR_SEG];	/* temporary use, first combination	*/	/* Letter Replace */
	DT16_ushort	cur_g1idx;
	DT16_ushort	gseq2[DLO_MAXCODES_PER_STR_SEG];	/* temporary use, 2nd combinataion	*/	/* Ligature */
	DT16_ushort	cur_g2idx;
	GlyphSeq	gseq[DLO_MAXCODES_PER_STR_SEG];		/* glyph info array, its index based on codes */
	CodeAw		awseq[DLO_MAXCODES_PER_STR_SEG];	/* advanced width array for render, its index based on codes */
	DT16_ushort	seg_cnt;							/* segment count		*/
	Str_Seg		segarr[DLO_SEG_LIMIT];				/* segment info array	*/
	FontCodeInfo g2info[DLO_MAXCODES_PER_STR_SEG];	/* the glyph's fontcode info of gseq2 (1 by 1 according its index)	*/
													/* the values inside this array will be filled before calculating	*/
													/* its position, check the checkedFlag before use.					*/
													/* @@ This array can be intergrate into caret_seq in DLO_LayBuf.	*/
													/* Consider to add a FontCodeInfo member of DLO_CodePositioning.	*/
	/* Buffers used for Bidi. */
	DT16_ushort tmptext[/*DT_MAX_CODES_PER_STR*/DLO_MAXCODES_PER_STR_SEG];	/* temp buffer for bidi.*/
	DT32_int	biditypes[DLO_MAXCODES_PER_STR_SEG];/* DT_Bidi_Class array for the input ucs_str.	*/
	DT32_int	bidilevel[DLO_MAXCODES_PER_STR_SEG];/* embedded level array for the input ucs_str.	*/
	DT32_int	glyftypes[DLO_MAXCODES_PER_STR_SEG];/* DT_Bidi_Class array for the ouput glyf_seq.	*/
	DT32_int	glyflevel[DLO_MAXCODES_PER_STR_SEG];/* embedded level array for the output glyf_seq.*/
//	DT16_ushort	reordertext[DLO_MAXCODES_PER_STR_SEG];/* the codes that will be reordered.			*/
//	CodevsGlyph map2ucs_str[DLO_MAXCODES_PER_STR_SEG];/* use this to index back to origin ucs_str.	*/
	DT16_ushort bidictrls[DLO_MAXCODES_PER_STR_SEG];/* an array to keep the Bidi_Control codes.		*/
	DT32_int	curbidi;							/* idx to bidictrls, current seg's bidictrl code*/
													/* it can be -1 as no bidictrl codes exist.		*/

	DT32_int	linewidth;							/* the width of the first line (input string)	*/
	DT32_int	lineheight;							/* the height of the first line (input string)	*/
	DT32_int	linebufh;							/* for Devanagari to get the real buf height.	*/

	/// the following 2 members are used in OpenVG mode only. Convert the value based on EM to pixels based on current sizeX,Y
	DT32_int	linewidth_pixel;					/* the pixels of the first line (input string)	*/	/* at current sizeXY*/
	DT32_int	lineheight_pixel;					/* the pixels of the first line (input string)	*/	/* at current sizeXY*/

	DT32_int	linebufh_pixel;						/* for Devanagari to get the real buf pixels.	*/	/* at current sizeXY*/

	DT32_int	linemoveYup;						/* the most negative moveY, only used when glyphs need to be move upper */
													/* Some glyphs like(Arabic, Thai) need to be drawn larger, other glyphs */
													/* might need to be move down.											*/
	DT32_int	linemoveYdn;						/* the most positive moveY, only used when glyphs need to be move downer*/
	DT32_int	linemoveXlf;						/* the most negative moveX*/
	DT32_int	linemoveXrt;						/* the diff of bmpw at right side, cause by RSB...etc */
	DT32_int	maxdifH;							/* 0: the bmpheight isn't determined by the glyph inside iconfont.		*/
													/* !=0: the bmpheight is determined by iconfont. ucs_str contains icons.*/
	DT_BOOL		bScaled;							/* TRUE: the string (ucs_str) has at least one char which needs scaled. */

	/* Font_Design info for some languages */
	Font_Design_Thai	fds;						/* DLO_LANGTAB_THAI *//* Font designed information, now used in Thai language.	*/
	Font_Design_Descent	fdsdes;						/* DLO_LANGTAB_DESCENT *//* Font design info for Latin, indicating offsetY.		*/
	DT32_int	fdlLatinOnly;						/* FDLs' code ranges, 1: non-scale, non-MoveY, and Latin only! no need shaper.	*/
													/* others: shaper required languages included in FDLs, or scale, moveY enabled.	*/
													/* Check if it's Latin only. Not check other languages.	DLO_LANG_LAT(1)			*/
													/* use this value by if(1==fdlLatinOnly);										*/
	/* Some Additional cases. Reserved area. */
//	DT32_uint	myvgfont;							/* For VGFont, used in DLO_ShapeStringVG() */
//	DT32_uint	myglyphpath;						/* VGPath for glyphs, used in DLO_ShapeStringVG() */
//	DT32_uint	mytranspath;						/* VGPath for transparent, used in DLO_ShapeStringVG() */
//	DT32_uint	mymaskpath;							/* Use a rectangle to fill the mask where fonts been drawn. */
	DT32_long	oldatasz;							/* allocated outline data size */
	DT8_char	*pBuf;								/* current pointer to LayBuf.olDatabuf */
	DT32_long	curidxglyf_seq;						/* current idx to pwrk->lobuf->glyf_seq*/
	DT32_int	writedir;							/* keep the writedir for further use. */

	/* Font Engine Functions */
	DLO_EngineType	 fengtype;	/* Font engine type, indicates which engine will be loaded.*/
	FontEngine_Funcs fengfuncs;	/* Font engine functions' pointer. */
	DT32_int	engWkMemsz;
	DT8_char	*engWkMem;
	DT32_long	engGradMemsz;	/* DcwRaster's Gradation Memory size.		*/
	DT_void		*engGradMem;	/* point to DcwRaster's Gradation Memory	*/
	DT32_long	engGradMaxUsed;	/* The max value of GradMem that ever used	*/
	DT32_long	engGradSuggest;	/* The minimum suggestion value of GradMem	*/

	/* Font Styles */
	DT32_int	vert;			/* Vertical Writing, range: now, 0 only							*/
	DT32_int	xsize;			/* Horizontal font size, range: 0~DLO_FONT_MAXSIZE				*/
	DT32_int	ysize;			/* Vertical font size, range: 0~DLO_FONT_MAXSIZE				*/
	DT32_int	f_edge;			/* Font Edge style, range: 0~DLO_STYLE_MAX_EDGE_FLAG			*/
	DT32_int	w_edge;			/* Font Edge width, range: 0~DLO_STYLE_MAX_EDGE_WIDTH			*/
	DT32_int	italic;			/* Italic amount in pixels, range: 0~xsize						*/
	DT32_int	p_underline;	/* Underline position, range: 0~ysize							*/
	DT32_int	w_underline;	/* Underline width, range: 0~ysize								*/
	DT32_int	e_underline;	/* Underline extend, range: 0~xsize, usually the same as italic */
	DT32_int	grade;			/* Bitmap Mode, DT_MODE_GRAY16...etc							*/
	DT8_uchar	*gcolor;		/* Gradation color table, according to grade					*/
	DT32_int	degree;			/* Rotate, degree=10 means 1 degree, range: 0~3600				*/
	DT32_int	spacing;		/* spacing between 2 characters, now it's used for OUTLINE 		*/
								/* draw a bold font first then use this to draw a normal font.	*/
								/* don't used it generally, especially when underline is enabled*/
	DT32_int	hinting;		/* hinting mode for DcwRaster, 1 or 2 only.						*/
	DT32_int	forcedown;		/* force move down flag, -1 or 0-1000 only						*/
	DT32_int	mode;			/* Layout mode, DLO_LAYOUT_BIT or DLO_LAYOUT_BYTE				*/
	DT32_int	isReinitFont;	/* is it required to re-initFont()								*/
	DT32_int	grade_values;	/* an easy way to set gcolor when gray16, see FSTYLE_GRAD_VALUES*/
	DT32_int	xbytes_align;	/* set xbyte alignment for bitmap, see FSTYLE_XBYTE_ALIGN		*/
	/**/
	DT32_int	ratio;			/* used for Hindi Only! if 0 means the string had no Hindi chars*/
	DT_void *   tmpdata;		/*easy pass data to other funtion, not modify function parameter.*/
	DT_void *   fnt_userdata;   /*easy pass data from out size.*/
	FontPosition fnt_pos[DT_MAX_CODES_PER_STR*2];

	DT32_int	bidirule;		/* DLO_BIDI_UNIRULE: unicode bidi algorithm;					*/
								/* DLO_BIDI_DCWRULE: old private implement rule.				*/
	DT_f26dot6	w_edge266;		/* Font Edge width, range: 0~DLO_STYLE_MAX_EDGE_WIDTH			*/

}LayWrk, *pLayWrk;

/* Language Functions */
#define FUNC_RENDERTOBUF	0x0000
#define FUNC_GETSEGINFO		0x0001
#define FUNC_CALCPOSITION	0x0002
#define FUNC_RENDERBYPOS	0x0004
typedef struct _LangFunc {
	DLO_Script	sc;
	DLO_Language ln; 
	DT32_int			(*RenderToBuf)(pLayWrk pwrk, DT_void *para);
	DT32_int			(*GetSeginfo)(pLayWrk pwrk, Str_Seg *para);
	DT32_int			(*CalcPosition)(pLayWrk pwrk, DT_void *para);	// Calc Position for DLO_BIDI_UNIRULE
	DT32_int			(*RenderByPos)(pLayWrk pwrk, DT_void *para);
}LangFunc;	/* Used for FunctionByLang() */

DT16_ushort	ReadUShort(DT8_uchar *dlo, DT32_long ofs);
DT32_ulong	ReadULong(DT8_uchar *dlo, DT32_long ofs, DT32_int size);
DT16_ushort	ReadUShortfromCurpos(pLayWrk pwrk);
DT32_ulong	ReadULongfromCurpos(pLayWrk pwrk);
DT16_ushort	GetSegDirectByScript(DLO_Script script);
DT32_int	BinSearchinFile(DT32_int count, DT8_uchar *data, DT16_ushort key);
DT_void		ClearGlyfOperate(bmpGlyfOperate *go);
DT16_ushort	Make_n_per_glyf(DT16_ushort codes, DT16_ushort glyfs);
DT_void		Parse_n_per_glyf(DT16_ushort n_per_glyf, DT16_ushort *codes, DT16_ushort *glyfs);
DT_void		DcwShaperVGGetVersion(DcwShaperVG_Version *ver);

DT_void ConvPunctuation_Open2Close(pLayWrk pwrk, DT16_ushort seg_start, DT16_ushort seg_end);
DT_void Fillawseg_R2L(pLayWrk pwrk);
DT_void Fillsegarr_R2L(pLayWrk pwrk);
DT32_int GetSeginfo_R2L(pLayWrk pwrk, Str_Seg *seginfo);

DT32_int getScaleRatio(pLayWrk pwrk, DT16_ushort gidx, DT32_int gseq2idx);
DT32_int CalcOffsetY_forbmph(pLayWrk pwrk, DT32_int fontH, DT32_int difH, DT32_int bmpH);
DT32_int need_Move_Down_Pixs(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx);
DT32_int Calxbytes(pLayWrk pwrk, DT32_int w);

DT_BOOL isCodeNSM(DT16_ushort ch);								// Used for DCWRULE
DT_BOOL isNSM(pLayWrk pwrk, DT16_ushort ch, DT32_int gseq2idx);	// check according to BIDI_RULE, 
DT_void swapXY(DT32_int* x, DT32_int* y);
DT_BOOL isUseDcwArabicPUA(pLayWrk pwrk);
DT_BOOL isAllCharsLatin(pLayWrk pwrk, DT16_ushort *ucs_str, DT32_int ucs_cnt);
DT_BOOL isAllEasyLatin(pLayWrk pwrk, DT16_ushort *ucs_str, DT32_int ucs_cnt);	// ASCII, Chinese, Hiragana, Katakana 
DT32_int ReInitFont(pLayWrk pwrk);

//DT32_int queryFontCodeInfo(pLayWrk pwrk, DT32_int gseq2idx);
DT_void  setDefault_Scale_LRsb_MoveY(FontCodeInfo *pfc);	// set some default FontCodeInfo when code doesn't exist.

#endif



