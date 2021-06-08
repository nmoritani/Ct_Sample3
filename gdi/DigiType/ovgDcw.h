#ifndef __OVG_DCW_H
#define __OVG_DCW_H

#include "ovgDcwApi.h"

#define _DCW_OVG_DEC_STROKE		DT_USE_SIMPLIFIED_STROKE

#define DCWOUL_CALC_AW_AH(aw)	(((DT32_long)(aw) * DCWOUL_FDL_FONT_EM + 999) / 1000)	//changed from 999 to 500. //Jacky_20101210

// 20111214: Jack add this macro to scale the FDL path value to DCWOUL_FDL_FONT_EM which might not be 2048.
#define DCWOUL_SCALE2EM(x)		(((x) * DCWOUL_FDL_FONT_EM) >> 8)		//((x) * DCWOUL_FDL_FONT_EM / 256)

typedef struct
{
  DT32_long x;
  DT32_long y;
} OTPoint;

typedef struct
{
  DT32_long left;
  DT32_long top;
  DT32_long right;
  DT32_long bottom;
} OTRect;

#ifndef	NULL
#define	NULL	0
/*#define	NULL	((DT_void*)0)*/
#endif


/*----------------------------------------------------------------------*/
/* Font Data                                                            */
/*----------------------------------------------------------------------*/

/* Header */
#define OFD_DEFVAL       8     /*  Default value of stroke           */
#define OFD_STRCNT       24    /*  Stroke count                      */
#define OFD_RADCNT       26    /*  Radical count                     */
#define OFD_FONCNT       28    /*  Font count                        */
#define OFD_STRTAB       30    /*  Start position of stroke table    */
#define OFD_STROFS       34    /*  Start position of stroke          */
#define OFD_RADTAB       38    /*  Start position of radical table   */
#define OFD_RADOFS       42    /*  Start position of radical         */
#define OFD_FONTAB       46    /*  Start position of font table      */
#define OFD_FONOFS       50    /*  Start position of font            */
#define OFD_CTMODE       54    /*  Coding mode (0-Jis  1-Big5)       */
#define OFD_VERSION      56    /*  Version                           */
#define OFD_LANGTAB		 58	   /*  Extent Area, Language Table.		 */

#define OFD_DECSTR		 76	  /* (0x4C) for Ds -- Decrease Stroke	*/
#define OFD_DSTR_IDENT	0x72747364	/* "dstr" (DT32_long)( ((DT32_ulong)'r'<<24) | ((DT32_ulong)'t'<<16) | ((DT32_ulong)'s'<<8) | ((DT32_ulong)'d') )*/

// The temp identification of Decrease Stroke is abandoned.
//#define	OFD_DECSTR		  4	   /*  for Ds -- Decrease Stroke		 */
//#define OFD_ORIGIN_IDENT 0x746e6f46	/* "Font" (DT32_long)( ((DT32_ulong)'t'<<24) | ((DT32_ulong)'n'<<16) | ((DT32_ulong)'o'<<8) | ((DT32_ulong)'F') )*/

/* Font data flag */
#define OFD_FLAG_HMTX    0x01
#define OFD_FLAG_VMTX    0x02
#define OFD_FLAG_VERT    0x04

/* Radical parameter flag */
#define OFD_RAD_SCALEX   0x01
#define OFD_RAD_SCALEY   0x02
#define OFD_RAD_WID      0x04

/* Radical parameter */
typedef struct FDLRadParam
{
  DT16_short Id;       /* Radical ID                               */
  DT8_BYTE   flag;     /* Radical flag                             */

  DT16_short destx;    /* Radical actual position / size           */
  DT16_short desty;
  DT16_short destw;
  DT16_short desth;

  DT16_short srcx;     /* Radical original position / size         */
  DT16_short srcy;
  DT16_short srcw;
  DT16_short srch;

  DT16_short wid;      /* Scaling width of each stroke in radical  */
} OTFDLRadParam;

/*----------------------------------------------------------------------*/
/* Fdl Data/Rasterizer data                                             */
/*----------------------------------------------------------------------*/
#define OFDL_END_OF_CHR          0x8000
#define OFDL_END_OF_STR          0x8003
#define OFDL_END_OF_SUB          0x8004
#define OFDL_UNKNOW_OP           0xFFFF

#define OFDL_MAX_SEGMENT         (64 * 6)


typedef struct
{
  /* For font data reading */
  DT_void    *wrk;
  DT32_int     rot;

  /* Stroke / Symbol data */
  DT16_WORD    defval[8];
  DT32_long    relno;
  DT8_BYTE     rel[16];
  DT32_long    valno;
  DT8_BYTE     val[8];
  DT32_long    sdatacnt;
  DT32_long    sdataofs;

  /* Font parameter */
  DT32_long    x0, y0;					/* Font Original */
  DT32_long    xsize, ysize;

  /* Path Data */
  DT16_short   *path;
  DT32_long    pathmax;
  DT32_long    pathsize;

  DT32_long    shiftx;         /* 2007-12-07 Radical (Shift for Symbol) */
  DT32_long    shifty;

  /* Outline buffer */
  DT16_short   OulBuf[2][OFDL_MAX_SEGMENT];
  DT16_short   *OulPtr[2];

  /* Interpreter Parameter */
  DT8_BYTE     op;
  DT32_long    Xpoint[16], Ypoint[16];
  DT32_long    Value[8], HVal[8], WVal[8];
  DT32_long    Frac, Frac2;

  DT32_int     xhead, xtail, yhead, ytail;
  DT32_long    MNx1, MNy1, MNx2, MNy2, Diffx, Diffy;
  DT32_long    sx1, sy1, sx2, sy2, sx3, sy3;

  DT32_int     isCurve, isLeft;
} OTFdlRasterData, *pOTFdlRasterData;

DT32_int  OFDL_GetFont(pOTFdlRasterData fdl);

/*----------------------------------------------------------------------*/
/* Working Memory                                                       */
/*----------------------------------------------------------------------*/
typedef struct
{
  DT32_long            magic;

  DT32_int             vert;

  /* Font Data Header */
  DT8_BYTE            *fd;
  DT32_long            strcnt;
  DT32_long            radcnt;
  DT32_long            foncnt;
  DT32_long            strtab;
  DT32_long            strofs;
  DT32_long            radtab;
  DT32_long            radofs;
  DT32_long            fontab;
  DT32_long            fonofs;
  DT32_long            ctmode;
  DT32_long            version;

  DT32_long						fonloc;			/* Font Location Table */
  DT16_WORD						fonmap;

  /* Plane */
  DT16_WORD						planeno;
  DT32_long						planes;
  DT32_int							plane;
  DT32_long						gstart;			/* Start Glyph Number of Plane */

  /* Page */
  DT16_WORD						pagebits;		/* Page Count Bits for Page Compress */
  DT16_WORD						pagemask;
  DT16_WORD						pageno;			/* Number of Page */
  DT32_long						pages;

  /* CMap */
  DT16_WORD						segno;			/* Number of Segment for CMap Compress */
  DT32_long						segs;

  /* Character Data */
  DT32_long            datacnt;
  DT32_long            dataofs;

  /* Radical data */
  OTFDLRadParam   *rad;
  DT32_int             inrad;
  DT32_long            rdatacnt;
  DT32_long            rdataofs;

  /* FDL Data/Rasterizer */
  OTFdlRasterData fdl;

#if _DCW_OVG_DEC_STROKE
  DT32_long       decstr;
  DT32_int		  sizexy;
  /* Decrease Stroke Font Data */
  DT32_int        DsFontCnt;      /* Font Count                           */
  //DT16_WORD       *DsIdxs;        /* Indexs: fidx(2) + offset(2)          */
  DT8_BYTE		  *DsIdxs;		  /* Indexs: fidx(2) + offset(2)          */
  DT8_BYTE        *DsDatas;       /* Data: size(1) + pidx(1) + modeval(1) */

  /* Decrease Stroke Data of Current Font */
  DT32_int        DsCnt;          /* Count of Data      */
  DT8_BYTE        *DsData;        /* Pointer to Data    */
  DT32_int        DsMode;         /* Mode               */
  DT32_int        DsVal;          /* Value              */
  DT32_int        DsPartIdx;      /* Current Part Index */
#endif

} ODcwWrk, *pODcwWrk;

//DT8_BYTE  OULFD_ReadStrByte(pODcwWrk wrk);
#define OULFD_ReadStrByte(wrk)	(DT8_BYTE)(*((DT8_BYTE*)(((pODcwWrk)wrk)->fd + ((pODcwWrk)wrk)->fdl.sdataofs++))); ((pODcwWrk)wrk)->fdl.sdatacnt --;
DT16_short OULFD_ReadStrShort(pODcwWrk wrk);

#endif
