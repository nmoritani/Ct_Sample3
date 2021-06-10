/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

/********************************************************************************************/
/*  You can adjust the defines in this file to meet your needs.								*/
/*  And, you can re-implement the functions declared here (implement in DTplatform.c)		*/
/********************************************************************************************/


#ifndef __DTPLATFORM_H
#define __DTPLATFORM_H



#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/****************************************************************************/
/****  Basic type definitions: DigiTypeAPI is workable on 32-bit system  ****/
/****************************************************************************/
typedef char			DT8_char;
typedef unsigned char	DT8_uchar;
typedef short			DT16_short;
typedef unsigned short	DT16_ushort;
typedef int				DT32_int;
typedef unsigned int	DT32_uint;
typedef long			DT32_long;
typedef unsigned long	DT32_ulong;
typedef void			DT_void;

typedef DT8_uchar		DT8_BYTE;
typedef DT16_ushort		DT16_WORD;

typedef DT32_uint		DT_size_t;

typedef DT8_char		DT_BOOL;
#define DT_FALSE		0
#define DT_TRUE			1

typedef DT32_long		DT_f26dot6;

/* These macros are used for positive values only. *//* 32bit system */
#define DTF266_1		64	/*(1 << 6)*/
#define DTF266_Half		32
#define DTFixToF266(integer,frac)	( ((DT_f26dot6)(integer)<<6) | ((DT_f26dot6)(frac) & 0x3F) )
#define DTF266ToCeiling(fval)			( (DT_f26dot6)(fval+DTF266_1-1)>>6 )
#define DTF266ToFloor(fval)				( (DT_f26dot6)(fval)>>6 )
#define DTF266ToRoundOff(fval)			( (DT_f26dot6)(fval+DTF266_Half)>>6 )
#define DTF266ToInt(fval)				DTF266ToCeiling(fval) /*( (DT_f26dot6)(fval+DTF266_Half)>>6 )*/	/*( (DT_f26dot6)(fval)>>6 )*/
#define DTF266ToFrac(fval)				( (DT_f26dot6)(fval) & 0x3F )	/*( ((DT_f26dot6)fval<<26)>>26 )*/
/* Converting 0.00-0.99 to fraction of DT_f26dot6.	*/
#define DTDecimal_1		100				/* 0 - 99, means 0.00 - 0.99 *//* (Note: 1/100 => 1/64 will lose precision) */
#define DTDecTo266Frac(decimal)			( (DT_f26dot6)((decimal)>DTDecimal_1?(DTDecimal_1-1):(decimal))*DTF266_1/DTDecimal_1 )
#define DT266FracToDec(frac)			( (DT_f26dot6)(frac)*DTDecimal_1/DTF266_1 )

/* Absolute Value */
#define DTAbs(x)						( (x)<0 ? -(x) : (x) )

/****************************************************************************/
/************** If you want to enable OpenVG related functions... ***********/
/****************************************************************************/
/* Set DT_OPENVG_ENABLED as 1: it will enable the function DT_RasterOVG().				*/
/* At the same time, it will need the header files and the library that OpenVG needed.	*/
#define DT_OPENVG_ENABLED	(1)	/* 0: not support OpenVG; 1: support OpenVG */

#if (1==DT_OPENVG_ENABLED)
#ifndef VG_API_CALL
#define VG_API_CALL extern
#endif
 #include <openvg_wrapper.h>
 typedef VGfloat			DT_float;	/* This type is required only when supporting OpenVG. */

 /*#define DT_DESTROY_VGPATH_EVERYTIME*/	/* You can enable this to destroy the VGPath instead of clean it. */
										/* Some OpenVG chips have this kind of problem. default: disabled.*/
 /* The data type of VGPath for DT_RasterOVGPath().	*/
 #define DT_SET_DATATYPE_FOR_VGPATH	0	/* 0(default):VGfloat, 16:VGshort, 32:VGint					*/
										/* Be careful of value range, if the string is longer, the value of path data might exceed 32767 */
 #if (16==DT_SET_DATATYPE_FOR_VGPATH)
  typedef VGshort			DT_VGtype;
  #define DT_GLYPH_CACHE_PATH_DATATYPE	VG_PATH_DATATYPE_S_16
  #define DT_PARSEOVGPATHDATA_BY_ABS
 #else 
  #if (32==DT_SET_DATATYPE_FOR_VGPATH)
   typedef VGint			DT_VGtype;
   #define DT_GLYPH_CACHE_PATH_DATATYPE	VG_PATH_DATATYPE_S_32
   #define DT_PARSEOVGPATHDATA_BY_ABS
  #else	/* 0 is also included here */
   typedef VGfloat			DT_VGtype;
   #define DT_GLYPH_CACHE_PATH_DATATYPE	VG_PATH_DATATYPE_F
   #define DT_PARSEOVGPATHDATA_BY_ABS
  #endif
 #endif
 
 #define DT_VERT_BY_OVG		/* define this to do vert drawing by OpenVG lib */

 extern /*const*/ DT32_int gDT_MAX_SEGS_PER_GLYPH;	/* Please set this value in DTplatform.c				*/
													/* The limitation of segments(operations) in a glyph.	*/
													/* Note: this value must be the times of 4.				*/

 extern /*const*/ DT32_int gDT_EachGlyphWidth_on_Pixels;/* Please set this value in DTplatform.c				*/
														/* 0: whole input string based on pixels,				*/
														/* 1: each glyph of the string is based on pixels.		*/
														/* If you want the bmpwidth same with GRAYxxBMP mode,	*/
														/* please set 1 and set gDT_FONT_EMSIZE=1000.			*/

 extern /*const*/ DT32_int gDT_OVGWidth_Based_on_GBMPWidth;/* Please set this value in DTplatform.c				*/
														/* If you want to adjust the OVG's bmpwidth to be same as GrayBMP's,*/
														/* please set this =1, and gDT_EachGlyphWidth_on_Pixels=1, and		*/
														/* gDT_FONT_EMSIZE=1000, and DISABLE(don't use) L3 CACHE!!!			*/
#endif

/****************************************************************************/
/*********** If you want to enable the default implement on Win32... ********/
/****************************************************************************/
#undef DT_WIN32			/* Enable this if you want to use DigiTypeAPI on Win32, else disable it.*/
							/* You have to implement your own DT_BitBlt() in you system.			*/
/*#define DT_ANDROID*/

/****************************************************************************/
/*********** If you want to disable the use of filesystem(stdio.h)... *******/
/****************************************************************************/
/*#define DT_ENABLE_STDIO*/		/* Enable this if your system supports stdio.h, else disable it.		*/
							/* Please implement DT_LoadFontData() & DT_unLoadFontData() to load font*/
							/* Check gDT_Set_Fix_Memory_Size, gDT_MAXMEMORY_SIZE before enable this	*/

/****************************************************************************/
/*********** If you want to disable the use of memory.h... ******************/
/****************************************************************************/
/*#define DT_ENABLE_MEMORY_H*/	/* If your system support memory.h or string.h, you can enable it.			*/
							/* If you disable it, DigiTypeAPI will use its own implement of these funcs.*/

/****************************************************************************************************/
/* You can adjust the following values according to your needs:										*/
/* The qulifier "const" was removed from the following global variables declaration for the ability */
/* that users can decide these values in programs just before DT_InitDigiType() have been called.	*/
/* PLEASE DO NOT MODIFY THESE GLOBAL VARIABLES after DT_FontMgr has initialized (DT_InitDigiType()).*/
/****************************************************************************************************/

/****************************************************************************/
/************** If you want to reduce the memory requirement... *************/
/****************************************************************************/

/**** Max Memory Can Be Use ****/
extern /*const*/ DT32_int gDT_Set_Fix_Memory_Size;	/* Please set this value in DTplatform.c		*/
									/* 0:disable; 1:enable.											*/
									/* Enable this to set how many memory that DigiTypeAPI can use.	*/
									/* Set the value of gDT_MAXMEMORY_SIZE, if you enable this.		*/

extern /*const*/ DT32_int gDT_MAXMEMORY_SIZE;/* Equal to DT_MAXMEMORY_SIZE, please set it in DTplatform.c	*/
									/* The limitation of memory that DigiTypeAPI can use.					*/
									/* If gDT_MAXMEMORY_SIZE isn't enough, some function will return error,	*/
									/* or display abnormally, please be careful of this and following values.*/
									/* If DT_CreateFontFromFile() had been called, and DT_LoadFontData() also*/
									/* been called to use DT_loadfilecontent() to load fontfile, this value */
									/* need to include the file size of the font.							*/

/**** Optimize memory usage of DigiTypeAPI for specified GrayBMP mode ****/
extern /*const*/ DT32_int gDT_Optimize_Mem_for_Gray16BMP;	/* Please set this value in DTplatform.c		*/
											/* 0: default. gDT_MAXMEMORY_SIZE must larger than 256K.		*/
											/* 1: Optimize for DT_Gray16BMP_MODE. gDT_MAXMEMORY_SIZE>=128K	*/

/**** Prepare font bmp buffer by yourself ****/
extern /*const*/ DT32_int gDT_Dont_Alloc_BmpBuf_When_CreateFont;	/* Please set this value in DTplatform.c*/
												/*0: DigiTypeAPI will allocate a bmp buf for its temp use.	*/
												/*1: DigiTypeAPI won't alloc the bmp buf when DT_CreateFont */
												/*	 Please make sure that DT_RasterBitBlt(), DT_RasterOVG()*/
												/*	 will NOT be used during all the function calls. Only	*/
												/*	 DT_RasterGrayBmp() will be used, and the parameter of	*/
												/*	 grayBMPbuf won't be NULL. If this value is 1 and 		*/
												/*	 DT_RasterBitBlt(), DT_RasterOVG() had been called, it  */
												/*	 will try to realloc memory to use.						*/
												/* Suggestion: If you need to DT_CreateFontXXX() twice or	*/
												/*   more simultaneously, please set it as 0.				*/
												/* This value affects the memory requirement very much.		*/

/**** Max Code Count ****/	/* If you want to enlarge these values, please contact DynaComware. */
#define DT_MAX_STRING_LENGTH	 (50)	/* the limitation of the code points of the input string:		*/
										/* the "ucs_cnt" of "ucs_str" in DT_GetXXX() or DT_RasterXXX()	*/
#define DT_MAX_CODES_PER_STR	 DT_MAX_STRING_LENGTH
									/* the limitation of the "ucs_cnt" or "ucs_str" in DT_GetXXX() or DT_RasterXXX()*/
#define DT_MAX_GLYPHS_PER_STR	(DT_MAX_STRING_LENGTH * 2)
									/* the limitation of the counts of "glyphs" of DT_TextInfo in DT_GetTextRect()	*/
									/* or DT_TextInfo in DT_RasterXXX().											*/
									/* Set it a little larger than or equal to  DT_MAX_CODES_PER_STR is recommended.*/

/**** Glyph font bmp rectangles count ****/
extern /*const*/ DT32_int gDT_MAX_BMPRECT_CNT_PER_STR;	/* Please set this value in DTplatform.c									*/
										/* Specify this value to tell DigiTypeAPI how much memory for bmp buffer will be reserved	*/
										/* according to the value of gDT_FONT_MAXSIZE, when gDT_Dont_Alloc_BmpBuf_When_CreateFont=0.*/
										/* It means how many font rectangles will be reserved, usually same as DT_MAX_GLYPHS_PER_STR*/
										/* The difference between this and DT_MAX_GLYPHS_PER_STR is the glyphs that will overlap.	*/
										/* This value can be smaller than DT_MAX_GLYPHS_PER_STR in some languages (like: Thai).		*/
										/* This value is useless when DT_OUTLINE_MODE in DT_CreateFontXXX().						*/

/**** Max Font Size ****/
extern /*const*/ DT32_int gDT_FONT_EMSIZE;/* EM size while DT_OUTLINE_MODE	*/
extern /*const*/ DT32_int gSet_DT_FONT_SIZE_LIMIT; /* See details in DTplatform.c							*/
										/* This will help you to set the limit of font size.				*/
										/* This value is the max size DT_FSTYLE_SIZEX(Y) that could be set	*/
										/* in DT_SetFontStyle(). No need to care about buffer size.			*/
#define gDT_FONT_MAXSIZE		(gSet_DT_FONT_SIZE_LIMIT*5/4)
										/* Max limitation of SIZEX, SIZEY by buffer size			*/
										/* The max font size that can be drawn.						*/
										/* Some FDL fonts will be enlarged indicated by font data,	*/
										/* use this value to guarantee the buffer is sufficient.	*/

#define gDT_FONTSIZE_FOR_MALLOC (gSet_DT_FONT_SIZE_LIMIT)
										/* This will tell DigiTypeAPI how much memory should be prepared.	*/
										/* Set this equal to gSet_DT_FONT_SIZE_LIMIT is recommended.		*/
										/* The size hint for memory allocate while DT_CreateFontXXX()		*/
										/* DT_CreateFontXXx() will create a block of buffer for internal use*/
										/* This will affect the working memory buffer size for Rasterizer,	*/
										/* and the returned text bmp buffer size.							*/
										/* Set this value same as gSet_DT_FONT_SIZE_LIMIT is recommended,	*/
										/* or it may require to re-allocate a new block of memory.			*/


/**** Default Font Size ****/
#define gDT_FONT_DEFSIZE		(gSet_DT_FONT_SIZE_LIMIT)
										/* The default font size after DT_CreateFontFromXXX(). smaller than gSet_DT_FONT_SIZE_LIMIT.*/
										/* Set this value according to your needs. This value won't affect the usage of memory.		*/
										/* SIZEX, SIZEY will be set as this value after DT_Handle created from DT_CreateFontXXX().	*/

/**** Max Italic Size ****/
#define DT_DECIDE_MAX_ITALIC(x)	( ((x)/4) > 24 ? 24 : ((x)/4) )	
#define gDT_FONT_MAXITALIC			DT_DECIDE_MAX_ITALIC(gSet_DT_FONT_SIZE_LIMIT)	/*(gSet_DT_FONT_SIZE_LIMIT/4)*/
									/* Max italic amount in pixels.													*/
									/* The italic amount will also affect the memory required.(for bmp rect)		*/
									/* limitation of italic amount: DT_FSTYLE_ITALICAMOUNT when DT_SetFontStyle()	*/
									/* suggestion: gSet_DT_FONT_SIZE_LIMIT/4										*/

/**** Temp Buffer Size ****/
extern /*const*/ DT32_long gDT_TEMP_BUFFER_SIZE;	/* Please set this value in DTplatform.c			*/
									/* For DigiTypeAPI temporary use. Before modifying this value,		*/
									/* please make sure you know what this value stands for exactly.	*/
									/* 4-bytes aligned is required.										*/

/**** Font Outline Size Per Glyph ****/
extern /*const*/ DT32_int gDT_MAX_OUL_SIZE_PER_GLYPH;	/* Please set this value in DTplatform.c		*/
									/* A buffer to keep the outline data of a glyph when DT_OUTLINE_MODE*/
									/* When gDT_Dont_Alloc_BmpBuf_When_CreateFont=0, DT_CreateFontXXX() */
									/* will prepared the memory enough for DT_MAX_GLYPHS_PER_STR glyphs.*/
									/* That is gDT_MAX_OUL_SIZE_PER_GLYPH*gDT_MAX_BMPRECT_CNT_PER_STR.	*/

/**** Default BiDirection Rule ****/
extern /*const*/ DT32_int	gDT_DEFAULT_BIDI_RULE;	/* Please set this value in DTplatform.c			*/
									/* If you don't call DT_SetFontStyle() to set DT_FSTYLE_BIDI_RULE,  */
									/* this rule will be used as default.								*/

/**** Endianness, Run on Big-Endian or Little Endian ****/
extern /*const*/ DT32_int	gDT_Endianness;	/* You don't need to set this value in DTplatform.c		*/
									/* 0: little endian, 1: big endian 								*/
									/* This value will be auto-detected after DT_InitDigiType().	*/
															
															
/****************************************************************************/
/************** Something about font file path length...  *******************/
/****************************************************************************/
/**** Max FilePath Length ****/ /* If you want to enlarge these values, please contact DynaComware. */
#ifdef DT_ENABLE_STDIO
 #define DT_MAX_FILE_PATH		260	/* _MAX_PATH, limitation of file path	*/
#else
 #define DT_MAX_FILE_PATH		32	/* usually only fontname are required	*/
#endif

/**** Max Count in Fontlist ****/
extern /*const*/ DT32_int gDT_FONTSLIST_MAXCNT;/* Please set this value in DTplatform.c					*/
										/* DigiTypeAPI can handle up to DT_FONTSLIST_MAXCNT fonts.	*/

extern /*const*/ DT32_int gDT_MAX_SIZEXY_ASPECT_RATIO;/* Please set this value in DTplatform.c	*/
										/* The max ratio of sizeX:SizeY. Used for DcwRaster.*/
										/* May affect the buffer size. set 1 as default.	*/

/****************************************************************************/
/****************                 Others                 ********************/
/****************************************************************************/
/* Font Moving: Please make sure the gDT_FONT_MAXSIZE is enough after moving. */
/* A Macro used to move some glyphs downer */
#define DT_FORCE_MOVE_DOWN_PIXS(szY,Ratio) ((szY)*(Ratio)/1000)
extern /*const*/ DT32_int gDT_MoveArabicY;	/* Please set this value in DTplatform.c							*/
											/* After scaling, how much do you want to move up or down when szY.	*/
											/* This is used as "Ratio" passing to DT_FORCE_MOVE_DOWN_PIXS()	to	*/
											/* calculate the real pixels.										*/
											/* 1000 based;	>0: moving down;	<0: moving up; 0: don't move	*/
extern /*const*/ DT32_int gDT_MoveThaiY;	/* Please set this value in DTplatform.c							*/
											/* After scaling, how much do you want to move up or down when szY.	*/
											/* This is used as "Ratio" passing to DT_FORCE_MOVE_DOWN_PIXS()	to	*/
											/* calculate the real pixels.										*/
											/* 1000 based;	>0: moving down;	<0: moving up; 0: don't move	*/

/* Font Scaling: Please make sure the gDT_FONT_MAXSIZE is enough after scaling. */
extern /*const*/ DT32_int gDT_FORCE_SCALE_RATIO;/* Please set this value in DTplatform.c	*/
												/* This value forces scaling font size up for some chars. If you set it as 1000, double size is used.	*/
												/* If you don't need to force scaling font size, set it as 0.											*/
												/* 1000 based;	0: don't enlarge;	0~300: enlarge														*/
												/* It will be useless if the fonts contains the scale info for every chars.								*/
#define DT_ScaleArabicSize(szY)	( (szY) + (((szY)*gDT_FORCE_SCALE_RATIO)/1000) )	/* The really size you want for Arabic chars after scaling when szY.*/
#define DT_ScaleThaiSize(szY)	( (szY) + (((szY)*gDT_FORCE_SCALE_RATIO)/1000) )	/* The really size you want for Thai chars after scaling when szY.	*/

/* The defines of bold method for GrayBMP mode */
#define DT_DCWRASTER_EASYBOLD_METHOD_THINER	/* You can enable this or not to choose the bold method. */

/* The defines for some special cases */
extern /*const*/ DT32_int gDT_ENABLE_FAST_MODE;	/* Please set this value in DTplatform.c					*/
												/* for DT_OUTLINE_MODE only (now), and the FDLs are limited.*/
												/* 0: disabled; 1:enabled									*/

/* The defines for FDL data */
/*#define DT_REAL_STRAIGHT_LINE_FDL_USED*/
#define DT_USE_SIMPLIFIED_STROKE	(1)			/* Some FDLs embedded with simplified stroke glyphs when specified font size*/
												/* 0: don't use simplified(decreased) stroke glyphs even if FDL supports;	*/
												/* 1: use simplified stroke glyphs if FDL supports at specified font size.	*/


#define DT_CODE_ASCII_IN_PUA		0xE400	/* Treat this area(0xE400~0xE47F) as ascii, comment this line if you don't need.*/


/* Enable this to output dbg message when compile with GCC (C99 & stdio required)	*/
/* Make sure it's disabled when compiler is other than GCC.							*/
/*#define __GCC_DEBUG_POINT__*/
#ifdef __GCC_DEBUG_POINT__
 #if __STDC_VERSION__ < 199901L  
  # if __GNUC__ >= 2  
  #  define __func__ __FUNCTION__  
  # else  
  #  define __func__ "<unknown>"  
  # endif  
 #endif

 #define DT_MY_DBG_MSG
#endif

 #ifdef DT_MY_DBG_MSG
  extern DT_void my_dbg_msg_int(DT32_int n);
  extern DT_void my_dbg_msg_str(const DT8_char *str);
  extern DT_void my_estimate_stack(const DT8_char *str);
  extern DT_void my_estimate_stack_show();

  #define DBGTRACE_STR(x)	my_dbg_msg_str(x)
  #define DBGTRACE_INT(x)	my_dbg_msg_int(x)

  /* This Macro will be called at DT_unInitDigiType() */
  #define STACK_SHOW_ESTIMATE_VALUE()	my_estimate_stack_show()

  /* This Macro will be called at the beginning in each function. */
  #define DBG_MSG_SHOW_FUNC_NAME()	DBGTRACE_STR((__func__))
 #else
  extern DT_void my_estimate_stack();
  
  #define DBGTRACE_STR(x)
  #define DBGTRACE_INT(x)

  #define STACK_SHOW_ESTIMATE_VALUE()

  #define DBG_MSG_SHOW_FUNC_NAME()	/*my_estimate_stack()*/
 #endif
  
typedef struct _DT_RGBA {
  DT8_uchar	r;
  DT8_uchar	g;
  DT8_uchar	b;
  DT8_uchar	a;
}DT_RGBA;

typedef struct _DT_DrawData{
	DT32_int	nWidth;
	DT32_int	nHeight;
	DT32_int	xbytes;
	DT32_int	bitcount;	/* Now it's 1(1-bit-per-pixel) or 8(1-byte-per-pixel)	*/
	DT32_int	grade;		/* DT_GRAY_MONO, DT_GRAY_16, DT_GRAY_256				*/
	DT32_int	grade_values;/* gray values mode(0-0xF, or 0-0xFF) when DT_GRAY_16	*/
	DT_RGBA		fontcolor;
	DT_RGBA		backcolor;
	DT32_int	bmpsize;
	DT8_uchar	*bmpbuf;
}DT_DrawData;


#ifdef DT_WIN32
/***** The platform dependent include header files *****/
#include <windows.h>	/* platform dependent */
#include <windowsx.h>	/* platform dependent */
#include <wingdi.h>

/* bitmap header and palette */
	typedef struct tagBITMAPINFOGRAY {
		BITMAPINFOHEADER    bmiHeader;
		RGBQUAD             bmiColors[256];
	} BITMAPINFOGRAY;

/* "flag" of myDT_32BITBMP_img */
#define myDT_DRAW_32BITBMP	0x01
#define myDT_GET_32BITBMP	0x02
typedef struct _myDT_32BITBMP_img{
	DT32_int		flag;		/* myDT_DRAW_32BITBMP or myDT_GET_32BITBMP		*/
	BITMAPINFOGRAY	bmpinfo;	/* your own BITMAPINFO if myDT_GET_32BITBMP		*/
	DT32_ulong		*pvbits;	/* a buffer to contain data bits, allocated by yourself. */
	DT32_int		bufw;		/* the width (bufw*4 bytes) of the buffer.		*/
	DT32_int		bufh;		/* the height of the buffer.					*/
}myDT_32BITBMP_img;
#endif	/*DT_WIN32*/

#ifdef DT_ENABLE_STDIO
#include <stdio.h>
/* FILE operate functions */
typedef FILE			DT_FILE;

extern DT_FILE *DT_fopen( const DT8_char *filename, const DT8_char *mode );
extern DT_size_t DT_fread ( DT_void *ptr, DT_size_t size, DT_size_t count, DT_FILE *stream );
extern DT8_char *DT_fgets( DT8_char *str, DT32_int n, DT_FILE *stream );
extern DT32_int DT_fclose ( DT_FILE *stream );
extern DT32_int DT_feof ( DT_FILE *stream );
extern DT32_int DT_ferror ( DT_FILE *stream );

/* Followings are only needed in DTplatform.c */
#define DT_SEEK_SET		SEEK_SET
#define DT_SEEK_CUR		SEEK_CUR
#define DT_SEEK_END		SEEK_END
extern DT32_int DT_fseek ( DT_FILE *stream, DT32_long offset, DT32_int origin );
extern DT_void DT_rewind( DT_FILE *stream );
extern DT32_long DT_ftell( DT_FILE *stream );	
#endif	/*DT_ENABLE_STDIO*/

/****************************************************************************/
/************** If you want to load font file from somewhere... *************/
/****************************************************************************/

/* This function will be called in DigiTypeAPI to load font data, please implement this function.			*/
/* You can open file, memory map, or read from a .h font file. And you can implement a reference count here.*/
/* dtfont:[in,out] please typecast to DT_Font*, it tells you which font is going to be load by "fontname".	*/
/*        "fontname" is the same as "fontfile" in DT_FontFile which passed in DT_CreateFontFromFile().		*/
/*        You can use "fontname" as a font file path or an identifier.										*/
/*        After this function, "fontdata" & "nfsize" in dtfont should be filled, "refcnt" should increase.	*/
/* fsize :[in] how many bytes will be load? -1 means load all file.											*/
/* Please return 1 as success; others as error.																*/
extern DT32_int DT_LoadFontData(DT_void *dtfont, DT32_int fsize);

/* This function will be called in DigiTypeAPI to unload font data, please implement this function.			*/
/* This is the balanced function of DT_LoadFontData(). DigiTypeAPI will guarantee the balanced call.		*/
/* dtfont:[in,out] please typecast to DT_Font*, it tells you which font is going to be unload by "fontname".*/
/*        "refcnt" should decrease. If "refcnt" is 0, it's time to release the fontdata that loaded.		*/
/* fsize :[in] how many bytes will be load? -1 means load all file.											*/
extern DT_void DT_unLoadFontData(DT_void *dtfont, DT32_int fsize);

/****************************************************************************/
/************** If you want to do BitBlt() by your system funcs... **********/
/****************************************************************************/
/* Platform Dependent drawing function: this func will be called by DT_RasterBitBlt().	*/
/* Please re-implement this function to meet your requirement.							*/
/* Please return DT_SUCCESS as success; DT_BITBLT_ERR as fail.							*/
/* hdcDest	: "destdc" param in DT_RasterBitBlt(), it can be the handle to your DC, Canvas, or something else.	*/
/* nXDest, nYDest, nWidthDest, nHeightDest: the rectangle to be drawn.											*/
/* bmpdata	: the text gray bmp	to be drawn.																	*/
/* userdata	: an address of a pointer that point to your own userdata. Same as the "userdata" in DT_RasterBitBlt()*/
/*			  If you need some info to be passed into and after DT_BitBlt(), you can put it here				*/
/* return: 0:DT_SUCCESS; <0:error; >0:some situation															*/
extern DT32_int DT_BitBlt(	DT_void *hdcDest,		/* handle to destination DC, by pass from DT_RasterBitBlt()	*/
							DT32_int nXDest,		/* x-coord of destination upper-left corner					*/
							DT32_int nYDest,		/* y-coord of destination upper-left corner					*/
							DT32_int nWidthDest,	/* width of destination rectangle							*/
							DT32_int nHeightDest,	/* height of destination rectangle							*/
							DT_DrawData *bmpdata,	/* the data to be drawn										*/
							DT_void **userdata		/* typecast to your own type struct, by pass from DT_RasterBitBlt()*/
);

/****************************************************************************/
/************** If you want to convert gray bmp to 32-bit bmp... ************/
/****************************************************************************/
#define DT_GetRValue(rgb)      ((BYTE)((rgb) >>24))
#define DT_GetGValue(rgb)      ((BYTE)((rgb) >>16))
#define DT_GetBValue(rgb)      ((BYTE)((rgb) >> 8))
#define DT_GetAValue(rgb)      ((BYTE)(rgb))
extern DT32_ulong DT_convColor(DT_RGBA color);		/* convert color from DT_RGBA to a value */

/****************************************************************************/
/************** If you want to decide the PUA codes' direction... ***********/
/****************************************************************************/
/* This function is used to decide the direction of the codes in PUA(Private Used area: 0xE000-0xF8FF)	*/
/* When DigiTypeAPI encountered a code in PUA, this function will be called to decide it direction.		*/
/* Note: 0xE000~0xE08F is reserved for Arabic, so the codes inside this area won't be decided here.		*/
/* Note: 0xE900~0xE9FF and 0xEE00~0xEEFF are also reserved.												*/
#define DT_CODE_DIR_NOT_SPECIFIED	0x00	/* Not specified											*/
#define DT_CODE_ASCII_PUNCT			0x01	/* like the punctuations in ascii							*/
#define DT_CODE_ASCII_PAIR_OPEN		0x02	/* like punct, but something different, Ex: 0x28, 0x5B, 0x7B*/
#define DT_CODE_ASCII_PAIR_CLOSE	0x03	/* like punct, but something different, Ex: 0x29, 0x5D, 0x7D*/
#define DT_CODE_DIR_AS_LATIN		0x04	/* Left to Right */
#define DT_CODE_DIR_AS_ARABIC		0x05	/* Right to Left */

extern const DT16_ushort DT_PUAOpenClosePair[][2];/* The list of DT_CODE_ASCII_PAIR_OPEN & DT_CODE_ASCII_PAIR_CLOSE.	*/
extern DT32_int DT_CodeDirection(DT16_ushort ch);/* It's used only when DT_BIDI_DCWRULE, useless when DT_BIDI_UNIRULE.	*/


/****************************************************************************/
/** If you want to set which code should be rotated 90 degree clockwise... **/
/****************************************************************************/
/* When DT_FSTYLE_VERT is set as 1, you can decide which code should be rotated 90 degrees clockwise.	*/
/* This function is used only when FDL font. Please implement this function in DTplatform.c if you want.*/
typedef struct{			/* codes>=start && codes<=end will be rotated.	*/
	DT16_ushort start;	/* code from*/
	DT16_ushort end;	/* code to	*/
}DT_CodeFromTo;
extern DT32_int gDT_Rotate90Table_ID;	/* a global variable indicating which table should be used.		*/
extern DT32_int DT_isCodeRotate90_WhenVert(DT16_ushort ch, DT32_int *Reserved);

/******************************************************************************/
/** If you want to set which code should not return DT_WARNING_EMPTY_FONT... **/
/******************************************************************************/
/* You can decide if DT_GetTextRect(), DT_RasterXXX() return DT_WARNING_EMPTY_FONT by implementing this func in DTplatform.c.	*/
extern DT32_int DT_isCode_NoEmptyFontWarning(DT16_ushort ch, DT32_int *Reserved);

/****************************************************************************/
/********************* DigiTypeAPI's Sub-Memory Functions *******************/
/****************************************************************************/
/* DigiTypeAPI have its own memory functions, and you can implement them in DTplatform.c*/
/* DigiTypeAPI will use these functions to allocate and free memory only.				*/
/* You can redirect it to your system's memory functions in DTplatform.c.				*/
/* If gDT_Set_Fix_Memory_Size=1, the default implementation of these					*/
/* functions will guarantee only the gDT_MAXMEMORY_SIZE memory will be used.			*/

#define	DT_BLOCKSIZE		(0x200)		/* The sub memory alloc base unit. Should be >=0	*/
#define DT_POFF				(8)			/* Please DO NOT modify this value.					*/
										/* Redefine POFF in DTmemory.c. It's every memory cell's offset value. */
#define DT_ALLOC_SIZE(x)	(((gDT_Set_Fix_Memory_Size)==1)?((x+DT_POFF+DT_BLOCKSIZE-1)/DT_BLOCKSIZE*DT_BLOCKSIZE-DT_POFF):(x))

/* Memory allocate & operation functions */
extern DT_void *DT_malloc(DT_size_t size );
extern DT_void *DT_realloc(DT_void *memblock, DT_size_t size );
extern DT_void DT_free( DT_void *memblock );

extern DT_void *DT_memset( DT_void *ptr, DT32_int value, DT_size_t num );
extern DT_void *DT_memcpy( DT_void *dest, const DT_void *src, DT_size_t count );

/* string operate functions */
extern DT_size_t DT_strlen( const DT8_char *str );
extern DT32_int DT_strncmp( const DT8_char *string1, const DT8_char *string2, DT_size_t count );


#ifdef __cplusplus
}
#endif

#endif
