#ifndef __OVG_DCWAPI_H
#define __OVG_DCWAPI_H

#include "DTplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DCWOUL_FDL_FONT_EM			gDT_FONT_EMSIZE

#define DCWOUL_RATIO_SHIFT          4

#define DCWOUL_BASE_RATIO			  1000	
#define DCWOUL_SCALED_SIZEXY(sz,rto) (((sz) * (DCWOUL_BASE_RATIO) + ((rto)-1)) / (rto))

/* API Error Code */
#define DCWOUL_SUCCESS               0

#define DCWOUL_BAD_HANDLE            -1
#define DCWOUL_EMPTY_FONT            -10000		//-2
#define DCWOUL_BAD_FONTDATA          -3
#define DCWOUL_NOT_ENOUGH_PATHMEM    -4

/* Codes mode */
#define DCWOUL_Code_Jis              0
#define DCWOUL_Code_Big5             1
#define DCWOUL_Code_Gb2312           2
#define DCWOUL_Code_Gb18030          3
#define DCWOUL_Code_Ucs              4
#define DCWOUL_Code_Ksc5601          5
#define DCWOUL_Code_Hkscs            6
#define DCWOUL_Code_Ascii            100
#define DCWOUL_Code_Ascii500         101

/* Outline Opcode */
#define DCWOUL_MOVETO                1
#define DCWOUL_LINETO                2
#define DCWOUL_BEZIERTO              3
#define DCWOUL_CLOSEPATH             4

typedef DT_void* DCWOUL_Handle;

/* Font Outline Parameter */
typedef struct
{
  DT32_long    fontidx;            /* Font Index                 */
  DT32_int     vert;               /* Vertical Writing           */
  DT32_int		sizexy;

  DT8_char    *path;              /* Path buffer address        */
  DT32_long    pathmax;            /* Path buffer size           */
  DT32_long    pathsize;
} DCWOUL_OutlineData;

/* Font Data Informaton */
typedef struct
{
  DT32_long    ctmode;             /* Codes mode   */
  DT32_long    fontcnt;            /* Font number  */
  DT32_long    version;            /* Version      */
} DCWOUL_FontInfo;

/* 2012-02-22: langid consists of 2 bytes (an DT16_ushort value).							*/
/* the lower-byte stands for DCWOUL_LANGTAB_ID, and the higher-byte stands for its version.	*/
/* use the following macro to get the DCWOUL_LANGTAB_ID or the version of the LANGTAB.		*/
#define DCWOUL_GET_REAL_LANGTAB_ID(val)		((((DT16_ushort)(val))<<8)>>8)
#define DCWOUL_GET_REAL_LANGTAB_VER(val)	(((DT16_ushort)(val))>>8)
#define DCWOUL_MAKE_LANGTAB_ID_VAL(tid,ver)	(DT16_ushort)((((DT16_ushort)(ver))<<8) | ((DT16_ushort)(tid)))
typedef enum
{
	DCWOUL_LANGTAB_THA			= 6,
	DCWOUL_LANGTAB_HINDI		= 7,
	DCWOUL_LANGTAB_ICN			= 10,
	DCWOUL_LANGTAB_DESCENT		= 11,
	DCWOUL_LANGTAB_RAS_SCALE	= 12,
	DCWOUL_LANGTAB_BIN_SCALE	= 13,
	DCWOUL_LANGTAB_GLOBAL		= 24,
	DCWOUL_LANGTAB_RSB			= 25,
	DCWOUL_LANGTAB_HINDI_SUB	= 26,
	DCWOUL_LANGTAB_HINDI_POS1	= 27,
	DCWOUL_LANGTAB_HINDI_POS2	= 28,
	DCWOUL_LANGTAB_HINDI_POS3	= 29,
	DCWOUL_LANGTAB_EMPTY = 0xFFFF
}DCWOUL_LANGTAB_ID;


typedef enum {
	DCWOUL_CHARATTR_LANGTAB_THAI		= DCWOUL_LANGTAB_THA,		/* DLO_LANGTAB_THA */
	DCWOUL_CHARATTR_LANGTAB_HINDI		= DCWOUL_LANGTAB_HINDI,
	DCWOUL_CHARATTR_LANGTAB_ICON		= DCWOUL_LANGTAB_ICN,		/* DLO_LANGTAB_ICN */
	DCWOUL_CHARATTR_LANGTAB_DESCENT		= DCWOUL_LANGTAB_DESCENT,	/* DLO_LANGTAB_DECENT */
	DCWOUL_CHARATTR_LANGTAB_RAS_SCALE	= DCWOUL_LANGTAB_RAS_SCALE,
	DCWOUL_CHARATTR_LANGTAB_BIN_SCALE	= DCWOUL_LANGTAB_BIN_SCALE,
	DCWOUL_CHARATTR_LANGTAB_GLOBAL		= DCWOUL_LANGTAB_GLOBAL,
	DCWOUL_CHARATTR_LANGTAB_HINDI_SUB	= DCWOUL_LANGTAB_HINDI_SUB,
	DCWOUL_CHARATTR_LANGTAB_HINDI_POS1	= DCWOUL_LANGTAB_HINDI_POS1,
	DCWOUL_CHARATTR_LANGTAB_HINDI_POS2	= DCWOUL_LANGTAB_HINDI_POS2,
	DCWOUL_CHARATTR_LANGTAB_HINDI_POS3	= DCWOUL_LANGTAB_HINDI_POS3,

	DCWOUL_CHARATTR_XYSCALERATIO=1001,
	DCWOUL_CHARATTR_ISXYSCALE_CHAR=1002,
	DCWOUL_CHARATTR_HEIGHT_SHIFT=1003,
	DCWOUL_CHARATTR_NORMAL_WIDTH=1004,
	DCWOUL_CHARATTR_NORMAL_HEIGHT=1005,
	DCWOUL_CHARATTR_ISOFFSETY_CHAR=1006,
	DCWOUL_CHARATTR_GET_OFFSETY=1007,		// return a DT32_long in 16.16 format, represents for logh.offsety
	DCWOUL_CHARATTR_LANGTAB_LSB =1008,
	DCWOUL_CHARATTR_LANGTAB_RSB =1009,
	DCWOUL_CHARATTR_RASSCALERATIO=1010,
	DCWOUL_CHARATTR_ISRASSCALE_CHAR=1011,
	DCWOUL_CHARATTR_BINSCALERATIO=1012,
	DCWOUL_CHARATTR_ISBINSCALE_CHAR=1013,
	DCWOUL_CHARATTR_GET_LOGHEIGHT=1014,		// return a DT32_long in 16.16 format, represents for logh.offsety
//	DCWOUL_CHARATTR_GET_LOGTOP=1015,		// not supplied, force to use 3in1 value istead.
	DCWOUL_CHARATTR_GET_3IN1_VALUE=1016,	// return a DT32_long in 10.10.12 format, represents for logt.logh.offsety

	DCWOUL_CHARATTR_END
} DCWOUL_CharAttr_Option;

#define DCWOUL_10BITS	(DT32_long)(1024-1)
#define DCWOUL_12BITS	(DT32_long)(4096-1)
#define DCWOUL_MAKE_3IN1_VALUE(offy, logh, logt)	(DT32_long)(((DT32_long)(offy) & (DCWOUL_12BITS)) | ((DT32_long)(logh) << 12) | ((DT32_long)(logt) << 22))
#define DCWOUL_OFFY_FROM_3IN1_VALUE(val)			((DT32_long)(val) << 20 >> 20)
#define DCWOUL_LOGH_FROM_3IN1_VALUE(val)			((DT32_ulong)(val) << 10 >> 22)	//(((DT32_long)(val) & (DCWOUL_10BITS << 12)) >> 12)
#define DCWOUL_LOGT_FROM_3IN1_VALUE(val)			((DT32_ulong)(val) >> 22)		//(((DT32_long)(val) & (DCWOUL_10BITS << 22)) >> 22)

#define DCWOUL_16BITS	(DT32_long)0xFFFF	
#define DCWOUL_MAKE_LOGH_OFFY(offy, logh)			(DT32_long)(((DT32_long)(offy) << 16 >> 16) | ((DT32_long)(offy) << 16))
#define DCWOUL_OFFY_FROM_LOGHOFFY(val)				((DT32_long)(val) << 16 >> 16)
#define DCWOUL_LOGH_FROM_LOGHOFFY(val)				((DT32_ulong)(val) >> 16)

DCWOUL_Handle DCWOUL_Create(DT8_char *fontdata, DT32_long WkMemsz, DT_void *WkMem);
DT32_int DCWOUL_Destroy(DCWOUL_Handle hnd);
DT32_int DCWOUL_Outline(DCWOUL_Handle hnd, DCWOUL_OutlineData *outline, DT8_char *fontdata);
DT32_int DCWOUL_GetAw(DCWOUL_Handle hnd, DT32_long fontidx, DT32_int vert, DT8_char *fontdata, DT16_short *ltx, DT16_short *lty);
DT32_int DCWOUL_GetFontInfo(DT8_char *fontdata, DCWOUL_FontInfo *info);
DT32_int DCWOUL_EstimateWkMem();
DT32_int DCWOUL_QueryCharAttr(DCWOUL_Handle hnd, DT8_char *fontdata, DT32_long fontidx, DCWOUL_CharAttr_Option option);

#ifdef __cplusplus
}
#endif

#endif
