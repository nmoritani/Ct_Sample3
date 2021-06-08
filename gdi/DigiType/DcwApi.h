#ifndef __DCWAPI_H
#define __DCWAPI_H

//#ifdef _WINDLL
//#define DllExport   __declspec( dllexport )
//#endif

#include "DTplatform.h"
#include "DTbasedef.h"


//#ifdef DT_WIN32
//# ifdef _DEBUG
//#  define DT_DEBUG
//# endif
//# ifdef DT_DEBUG
//#  include <dbg.h>
//# endif
//#endif

#ifdef __cplusplus
extern "C" {
#endif

// DLO_CALC_AW_AH(aw,size)	(((DT32_long)(aw) * (size) + (gDT_FONT_EMSIZE-1)) / gDT_FONT_EMSIZE)
#define DCW_CALC_AW_AH(aw,size)	(((DT32_long)(aw) * (size) + 999) / 1000);	// 2012-02-10; Jacky moved here

#define DCW_INTERANL_CALC_LSB_RSB	// Do not enable this when release to customer. It's used only for  FontTool to calculate lsb, rsb.

#define DCW_ENABLE_MODIFYATTR_WHEN_RASTER	/* Enable this to modify attributes after DCW_Create(),	*/
											/* fontdata is still not supported.						*/

#define DCW_ASSIGN_GRADATION_MEM	// Comment this line to disable it. Or it will be enabled.
									// When it is enabled, please assign GradMem and GradMemSize to
									// use another block of memory for gradation (scan line).
									// And get the memory requirement used for gradation (check GradMemUsed).
									// The required gradation memory was included in WkMem before, but it can separate now.
									// Added_By_Jacky_20101210: To use the memory more flexibly.

#define DCW_MAX_SIZEXY_ASPECT	  gDT_MAX_SIZEXY_ASPECT_RATIO /*(1)*/ /* Set it as 1 when normal ratio FDL only. */
//extern const DT32_int gDCW_MAX_SIZEXY_ASPECT;				 /* Set it as 1 when normal ratio FDL only. */
#define DCW_BASE_RATIO			  1000					 /* If you modified this, please check Icon_Scale_Table[] */
#define DCW_SCALED_SIZEXY(sz,rto) (((sz) * (DCW_BASE_RATIO) + ((rto)-1)) / (rto))

#define DCW_CODE_NOT_EXIST		 -10000

#define DCW_MAXSIZE               (gSet_DT_FONT_SIZE_LIMIT*2)	// For the ability to draw Hindi.	//gDT_FONT_MAXSIZE
#define DCW_MAXGRAD               16
#define DCW_MAXITALICAMOUNT		  gDT_FONT_MAXITALIC

/* API Error Code */
#define DCW_SUCCESS               0

#define DCW_EMPTY_FONT            1

#define DCW_SIZE_TOO_LARGE        -1
#define DCW_INVALID_EDGE_FLAG     -2
#define DCW_INVALID_EDGE_WIDTH    -3
#define DCW_NOT_ENOUGH_WKMEM      -4
#define DCW_INVALID_GRADE         -5
#define DCW_INVALID_GRADE_COLOR   -6
#define DCW_BAD_FONTDATA          -7
#define DCW_INVALID_ITALIC        -8
#define DCW_INVALID_UNDERLINE     -9
#define DCW_NOT_ENOUGH_FONTBOXMEM -10

/* Bitmap Mode */
#define DCW_MODE_MONOCHROME       0
#define DCW_MODE_GRAY16           1
#define DCW_MODE_GRAY256          2
#define DCW_MODE_MAX              2

/* Edge Style Flag */
#define DCW_EDGE_NORMAL           0
#define DCW_EDGE_OUTLINE          1
#define DCW_EDGE_BOLD             2
#define DCW_EDGE_BOLD_RIGHT       3
#define DCW_EDGE_BOLD_DOWN        4
#define DCW_EDGE_BOLD_RIGHT_DOWN  5
#define DCW_MAX_EDGE_FLAG         5
#define DCW_MAX_EDGE_WIDTH        DT_STYLE_MAX_EDGE_WIDTH	//5	//10

/* Codes mode */
#define DCW_Code_Jis              0
#define DCW_Code_Big5             1
#define DCW_Code_Gb2312           2
#define DCW_Code_Gb18030          3
#define DCW_Code_Ucs              4
#define DCW_Code_Ksc5601          5
#define DCW_Code_Hkscs            6
#define DCW_Code_Ascii            100
#define DCW_Code_Ascii500         101

/* Option for DCW_EstimateWkMem() */
#define DCW_WKMEM_BASE			(0x01)
#define DCW_WKMEM_GRAD			(0x02)
#define DCW_WKMEM_DEFAULT		(DCW_WKMEM_BASE | DCW_WKMEM_GRAD)


/* Font Attribute */
typedef struct
{
  DT32_int     vert;               /* Vertical Writing           */
  DT32_int     xsize;              /* Horizontal font size       */
  DT32_int     ysize;              /* Vertical font size         */
  DT32_int     f_edge;             /* Font Edge style            */
  DT32_int     w_edge;             /* Font Edge width            */
  DT32_int     italic;             /* Italic amount in pixels    */
  DT32_int     p_underline;        /* Underline position         */
  DT32_int     w_underline;        /* Underline width            */
  DT32_int     e_underline;        /* Underline extend           */
  DT32_int     grade;              /* Bitmap Mode                */
  DT8_uchar gcolor[DCW_MAXGRAD+1]; /* Gradation color table		 */

  DT8_char    *fontdata;           /* Font Data address          */
  DT8_char    *WkMem;              /* Working memory             */
  DT32_long    WkMemSize;          /* Working memory size        */

  DT_f26dot6	w_edge266;
} DCW_AttrData;

/* Font Raster Parameter */
typedef struct
{
  DT32_long    fontidx;            /* Font Index                 */
  DT32_int     x0, y0;             /* Origin of font in bitmap   */
  DT32_int     xs, ys;             /* Size of font in bitmap     */
  DT32_int     xbyte;              /* Horizontal bytes of bitmap */
  DT8_char    *bitmap;             /* Bitmap buffer address      */
  DT32_long    MemSize;

  DT32_int		hint;			   /* Hinting mode				 */

  DT_void     *GradMem;            /* Gradation memory			 */	/* Used when DCW_ASSIGN_GRADATION_MEM defined. */
  DT32_long    GradMemSize;        /* Gradation memory size      */
  DT32_long	   GradMemUsed;		   /* The Gradation memory used for this fontidx. */
								   /* Check this value when function returned.	  */
//  DT32_int	   OutBoundflag;	   /* Is outside of font rect valid? DCW_OUT_BOUND_LEFT... etc.  */

} DCW_RasterData;

/* Font Data Informaton */
typedef struct
{
  DT32_long    ctmode;             /* Codes mode   */
  DT32_long    fontcnt;            /* Font number  */
  DT32_long    version;            /* Version      */
  DT32_long    strcnt;			   /* Stroke number 	*/
} DCW_FontInfo;

/* Language Table (Extent Area)*/
#define DCW_MAX_LANGTABCNT_LIMIT 64/* Max count of LANGTAB, avoiding accessing eror by the wrong FDL file format. */

/* Check DLO_LANGTAB_ID for the values. It's better to set the value the same.			*/
/* 2012-02-22: langid consists of 2 bytes (an DT16_ushort value).						*/
/* the lower-byte stands for DCW_LANGTAB_ID, and the higher-byte stands for its version.*/
/* use the following macro to get the DCW_LANGTAB_ID or the version of the LANGTAB.		*/
#define DCW_GET_REAL_LANGTAB_ID(val)		((((DT16_ushort)(val))<<8)>>8)
#define DCW_GET_REAL_LANGTAB_VER(val)		(((DT16_ushort)(val))>>8)
#define DCW_MAKE_LANGTAB_ID_VAL(tid,ver)	(DT16_ushort)((((DT16_ushort)(ver))<<8) | ((DT16_ushort)(tid)))
typedef enum
{
	DCW_LANGTAB_THA			= 6,
	DCW_LANGTAB_HINDI		= 7,
	DCW_LANGTAB_ICN			= 10,
	DCW_LANGTAB_DESCENT		= 11,
	DCW_LANGTAB_RAS_SCALE	= 12,
	DCW_LANGTAB_BIN_SCALE	= 13,
	DCW_LANGTAB_GLOBAL		= 24,
	DCW_LANGTAB_RSB			= 25,
	DCW_LANGTAB_HINDI_SUB	= 26,
	DCW_LANGTAB_HINDI_POS1	= 27,
	DCW_LANGTAB_HINDI_POS2	= 28,
	DCW_LANGTAB_HINDI_POS3	= 29,
	DCW_LANGTAB_EMPTY = 0xFFFF
}DCW_LANGTAB_ID;

/* Check DLO_CharAttr_Option for the values. It's better to set the value the same. */
typedef enum {
	DCW_CHARATTR_LANGTAB_THAI		= DCW_LANGTAB_THA,
	DCW_CHARATTR_LANGTAB_HINDI		= DCW_LANGTAB_HINDI,
	DCW_CHARATTR_LANGTAB_ICON		= DCW_LANGTAB_ICN,
	DCW_CHARATTR_LANGTAB_DESCENT	= DCW_LANGTAB_DESCENT,
	DCW_CHARATTR_LANGTAB_RAS_SCALE	= DCW_LANGTAB_RAS_SCALE,
	DCW_CHARATTR_LANGTAB_BIN_SCALE	= DCW_LANGTAB_BIN_SCALE,
	DCW_CHARATTR_LANGTAB_GLOBAL		= DCW_LANGTAB_GLOBAL,
	DCW_CHARATTR_LANGTAB_HINDI_SUB	= DCW_LANGTAB_HINDI_SUB,
	DCW_CHARATTR_LANGTAB_HINDI_POS1	= DCW_LANGTAB_HINDI_POS1,
	DCW_CHARATTR_LANGTAB_HINDI_POS2	= DCW_LANGTAB_HINDI_POS2,
	DCW_CHARATTR_LANGTAB_HINDI_POS3	= DCW_LANGTAB_HINDI_POS3,

	DCW_CHARATTR_XYSCALERATIO=1001,
	DCW_CHARATTR_ISXYSCALE_CHAR=1002,
	DCW_CHARATTR_HEIGHT_SHIFT=1003,
	DCW_CHARATTR_NORMAL_WIDTH=1004,
	DCW_CHARATTR_NORMAL_HEIGHT=1005,
	DCW_CHARATTR_ISOFFSETY_CHAR=1006,
	DCW_CHARATTR_GET_OFFSETY=1007,			// return a DT32_long in 16.16 format, represents for logh.offsety
	DCW_CHARATTR_LANGTAB_LSB =1008,
	DCW_CHARATTR_LANGTAB_RSB =1009,
	DCW_CHARATTR_RASSCALERATIO=1010,
	DCW_CHARATTR_ISRASSCALE_CHAR=1011,
	DCW_CHARATTR_BINSCALERATIO=1012,
	DCW_CHARATTR_ISBINSCALE_CHAR=1013,
	DCW_CHARATTR_GET_LOGHEIGHT=1014,		// return a DT32_long in 16.16 format, represents for logh.offsety
//	DCW_CHARATTR_GET_LOGTOP=1015,			// not supplied, force to use 3in1 value istead.
	DCW_CHARATTR_GET_3IN1_VALUE=1016,		// return a DT32_long in 10.10.12 format, represents for logt.logh.offsety

	DCW_CHARATTR_END
} DCW_CharAttr_Option;

#define DCW_10BITS	(DT32_long)(1024-1)
#define DCW_12BITS	(DT32_long)(4096-1)
#define DCW_MAKE_3IN1_VALUE(offy, logh, logt)	(DT32_long)(((DT32_long)(offy) & (DCW_12BITS)) | ((DT32_long)(logh) << 12) | ((DT32_long)(logt) << 22))
#define DCW_OFFY_FROM_3IN1_VALUE(val)			((DT32_long)(val) << 20 >> 20)
#define DCW_LOGH_FROM_3IN1_VALUE(val)			((DT32_ulong)(val) << 10 >> 22)	//(((DT32_long)(val) & (DCW_10BITS << 12)) >> 12)
#define DCW_LOGT_FROM_3IN1_VALUE(val)			((DT32_ulong)(val) >> 22)		//(((DT32_long)(val) & (DCW_10BITS << 22)) >> 22)

#define DCW_16BITS	(DT32_long)0xFFFF	
#define DCW_MAKE_LOGH_OFFY(offy, logh)			(DT32_long)(((DT32_long)(offy) << 16 >> 16) | ((DT32_long)(offy) << 16))
#define DCW_OFFY_FROM_LOGHOFFY(val)				((DT32_long)(val) << 16 >> 16)
#define DCW_LOGH_FROM_LOGHOFFY(val)				((DT32_ulong)(val) >> 16)

DT32_int DCW_Create(DCW_AttrData *attr);
DT32_int DCW_Raster(DCW_AttrData *attr, DCW_RasterData *raster);
DT32_int DCW_GetAw(DCW_AttrData *attr, DT32_long fontidx);
DT32_int DCW_GetFontInfo(DT8_char *fontdata, DCW_FontInfo *info);
DT32_int DCW_EstimateWkMem(DT32_int sizex, DT32_int sizey, DT32_int grade, DT32_int option);
DT32_int DCW_QueryCharAttr(DCW_AttrData *attr, DT32_long fontidx, DCW_CharAttr_Option option);

#ifdef __cplusplus
}
#endif

#endif
