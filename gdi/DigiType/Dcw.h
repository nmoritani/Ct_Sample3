#ifndef __DCW_H
#define __DCW_H

#include "DcwApi.h"

#define _DCW_DEC_STROKE		DT_USE_SIMPLIFIED_STROKE

//#define OPTIMIZE_CHECK									// If some platforms has problem, such as RISC platform.
#define MAX_REF_DATA										12000 //(12000*(100+15)/100)	// Add extra 15%.

#define DCW_OPT_RESETWRK_FOR_GETAW		0x00000001
#define DCW_OPT_RESETWRK_FOR_RASTER		0x00000002

//#define DT_DEBUG
//#define DT_SVG_DEBUG										// Output SVG outline.
#define FDL_OUTLINE_MODE									// Generate outline then draw bitmap.
#define FDL_WEIGHT											// Enable fdl engine to adjust the font's stroke weight.
															// If not define FDL_CACHE_WEIGHT, the weight must asigned before generate outline.
#define FDL_CACHE_WEIGHT									// Enable to adjust the font's stroke weight from outline, Alan.
//#define FDL_OUTLINE_CACHE									// Enable to cache font outline.
#define ENABLE_ADV_HINTING									// For new hinting algorithm.
//#define FDL_EXTEND

//#define FORCE_HINTING_0_TO_3
#define FDL_HINTING_AREA_START 0x4E00
#define FDL_HINTING_AREA_END   0x9FA5

#define MAIN_GROUP_BIT					3					// The main group use how many bits.

#define FDL_MAIN_GROUP(x)				(((x) & (((1<<(MAIN_GROUP_BIT))-1) << (8-MAIN_GROUP_BIT))))	// Stroke Main Group Mask
#define FDL_SUB_GROUP(x)				((x) & ((1<<(8-MAIN_GROUP_BIT))-1))							// Stroke Sub Group Mask
#define FDL_SET_MAIN_GROUP(x)			((x) << (8-MAIN_GROUP_BIT))									// Set Stroke Main Group
#define FDL_GROUP(x1, x2)				(FDL_SET_MAIN_GROUP(x1) | FDL_SUB_GROUP(x2))				// Set Stroke Group

//#define FDL_ONLY_REMOVE_STROKE_NOHINTING	// For test mode.

#define FDL_NEW_HINTLISTDATA_WITH_NEW_DEFINE	// use new hintlist data + new define

#ifdef FDL_OLD_HINTLISTDATA_WITH_NEW_DEFINE
#define FDL_CONV_OLD_V_TO_NEW_HINTLIST		//Convert old hintlist data to new define
#define FDL_ITS_NEW_HINTLIST_DATA			//After Convert, it new hintlist data
//#define FDL_USE_OLD_HINTLIST_H			//use new functions
#endif

#ifdef FDL_OLD_HINTLISTDATA_WITH_OLD_DEFINE
//#define FDL_CONV_OLD_V_TO_NEW_HINTLIST	//No need to convert hintlist data
#define FDL_USE_OLD_HINTLIST_H				//use old functions (horizontal only).
#endif

#ifdef FDL_NEW_HINTLISTDATA_WITH_NEW_DEFINE
//#define FDL_CONV_OLD_V_TO_NEW_HINTLIST	//No need to convert hintlist data
//#define FDL_USE_OLD_HINTLIST_H			//use new functions
#define FDL_ITS_NEW_HINTLIST_DATA			//It's new hintlist data.
#endif

#define FDL_STROKE_LINE_MAX				10					// The maximum horizontal line in a stroke.
#define FDL_STROKE_HINT_DISABLE			(-1)				// -1 is that don't use hintlist table.
#define FDL_ALIGN_MODE					(0x03 << 6)			// The stroke hinting mode. (VSTROKE and PACK)
#define FDL_ALIGN_PACK					(0x01 << 6)			// This bit represents that the stroke need to be pack to below stroke.
#define FDL_ALIGN_VSTROKE				(0x01 << 7)			// This bit represents that it's a vertical stroke to be hint.
															// In the new difinition, it's replaced by FDL_REMOVE_STROKE_MIX_MODE

#define FDL_REMOVE_STROKE_MIX_MODE		(0x01 << 7)			// Re-define this bit to indicate if mix-mode.
															// This stroke will be removed and the lower stroke will be moved 1/2.
#define FDL_MAX_REMOVE_STROKE_NUM		(20)				// Max number of remove-strokes. //20101115

#define FDL_ALIGNPACK_X_LEFT_NEAREST		0				//group doesn't have a center stroke, nor mirrored
#define FDL_ALIGNPACK_X_CENTER_TWO_LINES	1				//group doesn't have a center stroke, but mirrored
#define FDL_ALIGNPACK_X_CENTER_STROKE		2				//group has a center stroke, so it's mirrored of course.


//#define DT_SUB_MEMORY										// Enable use sub memory.
#define	DT_SUBMEMORY_SIZE				(512*20)			// The sub memory size.

#define FDL_OUTLINE_CACHE_SIZE			((1024*20)/4*4)		// Set the outline cache size bytes.
#define FDL_OUTLINE_UNIT_MINI_SIZE		(20)
#define FDL_OUTLINE_UNIT_MAX_SIZE		(60)

#define SEARCH_MODE						-1					// for BSearch() in search mode.
#define INSERT_MODE						 1					// for BSearch() in insert new element when don't find key.

#ifndef FDL_WEIGHT
#undef FDL_CACHE_WEIGHT										// If want to enable FDL_CACHE_WEIGHT, also must enable FDL_WEIGHT, Alan.
#endif // FDL_WEIGHT

#ifndef ENABLE_ADV_HINTING
#undef DT_SVG_DEBUG
#endif // ENABLE_ADV_HINTING

#ifndef DT_SUB_MEMORY
#undef DT_SUBMEMORY_SIZE
#define DT_SUBMEMORY_SIZE				(0)
#endif

typedef struct
{
	DT8_uchar size;											// Need how many pixels to display this word with hinting, after use this weight.
	DT8_uchar stroke;										// The stroke index in word which need to remove/pack for hinting.
															// The max stroke index is 64, the bit 7~6 resrver for FDL_ALIGN_MODE flag.
} FDL_StrokeHint;

typedef struct
{
  DT32_long x;
  DT32_long y;
} TPoint;

typedef struct
{
  DT32_long x;
  DT32_long y;
  DT32_long w;
} TData;

typedef enum
{
	FDL_NO_HINT=0,
	FDL_OLD_HINT,
	FDL_AUTO_HINT,
}FDL_HINT;

typedef enum
{
	FDL_PATH_NONE=0,
	FDL_PATH_HORZ,
	FDL_PATH_VERT,
}FDL_PATH_DIR;

typedef struct
{
  DT32_long left;
  DT32_long top;
  DT32_long right;
  DT32_long bottom;
} TRect;

typedef struct
{
  DT8_char x;
  DT8_char y;
  DT8_char w;
  DT8_char h;
} TSRect;

#ifndef	NULL
#define	NULL	0
//#define	NULL	((void*)0)
#endif


/*----------------------------------------------------------------------*/
/* Font Data                                                            */
/*----------------------------------------------------------------------*/

/* Header */
#define FD_DEFVAL       8     /*  Default value of stroke           */
#define FD_STRCNT       24    /*  Stroke count                      */
#define FD_RADCNT       26    /*  Radical count                     */
#define FD_FONCNT       28    /*  Font count                        */
#define FD_STRTAB       30    /*  Start position of stroke table    */
#define FD_STROFS       34    /*  Start position of stroke          */
#define FD_RADTAB       38    /*  Start position of radical table   */
#define FD_RADOFS       42    /*  Start position of radical         */
#define FD_FONTAB       46    /*  Start position of font table      */
#define FD_FONOFS       50    /*  Start position of font            */
#define FD_CTMODE       54    /*  Coding mode (0-Jis  1-Big5)       */
#define FD_VERSION      56    /*  Version                           */
#define FD_LANGTAB		58	  /*  Extent Area, Language Table.		*/

#ifdef FDL_EXTEND
#define FD_EXTEND       58    /*  Version                           */		// Alan.
#endif

#define FD_DECSTR		76	  /* (0x4C) for Ds -- Decrease Stroke	*/
#define FD_DSTR_IDENT	0x72747364	/* "dstr" (DT32_long)( ((DT32_ulong)'r'<<24) | ((DT32_ulong)'t'<<16) | ((DT32_ulong)'s'<<8) | ((DT32_ulong)'d') )*/

// The temp identification of Decrease Stroke is abandoned.
//#define	FD_DECSTR		 4	  /*  for Ds -- Decrease Stroke			*/
//#define FD_ORIGIN_IDENT	0x746e6f46	/* "Font" (DT32_long)( ((DT32_ulong)'t'<<24) | ((DT32_ulong)'n'<<16) | ((DT32_ulong)'o'<<8) | ((DT32_ulong)'F') )*/


/* For Language Table in Extent Area */
typedef struct{
	DT16_ushort	StartCode;		/* the start code of this icon table*/
	DT16_ushort	EndCode;		/* the end code of this icon table.	*/
	DT16_ushort	MinRatio;		/* the minimum Ratio value of this icon table. (to calculate the maximum font size)	*/
	DT16_ushort	MaxRatio;		/* the maximum Ratio value of this icon table. (to calculate the minimum font size)	*/
	DT32_long	ofsRtoData;		/* offset to the icon ratio data.	*/
}Font_Ratio_Icon;

/* Font data flag */
#define FD_FLAG_HMTX    0x01
#define FD_FLAG_VMTX    0x02
#define FD_FLAG_VERT    0x04
#define FD_FLAG_GROUP   0x08    // DLHsieh

/* Radical parameter flag */
#define FD_RAD_SCALEX   0x01
#define FD_RAD_SCALEY   0x02
#define FD_RAD_WID      0x04

/* Radical parameter */
typedef struct FDLRadParam
{
  DT16_short Id;       /* Radical ID                               */
  DT8_BYTE  flag;     /* Radical flag                             */

  DT16_short destx;    /* Radical actual position / size           */
  DT16_short desty;
  DT16_short destw;
  DT16_short desth;

  DT16_short srcx;     /* Radical original position / size         */
  DT16_short srcy;
  DT16_short srcw;
  DT16_short srch;

  DT16_short wid;      /* Scaling width of each stroke in radical  */
} TFDLRadParam;

/*----------------------------------------------------------------------*/
/* Fdl Data/Rasterizer data                                             */
/*----------------------------------------------------------------------*/
//#define ENABLE_FDL_MODE_RASTER	// 20110929: FDL_MODE_RASTER isn't used now, disable this mode to reduce memory requirement.
#define FDL_MODE_RASTER         0	// 20110929: This mode won't be used! fdl->Stack is disabled.
#define FDL_MODE_OUTLINE        1
#define FDL_MODE_RASTER2        2

#define FDL_END_OF_CHR          0x8000
#define FDL_END_OF_STR          0x8003
#define FDL_END_OF_SUB          0x8004
#define FDL_UNKNOW_OP           0xFFFF

#define FDL_GRAYLEVE			((gDT_Optimize_Mem_for_Gray16BMP)?(4):(16))
#define FDL_MAX_SIZE            (DCW_MAXSIZE * FDL_GRAYLEVE)	// Gray 16 ONLY!	//(DCW_MAXSIZE * 16)
#define FDL_MAX_SIZE_BOLD		(FDL_MAX_SIZE + 2*DCW_MAX_EDGE_WIDTH*FDL_GRAYLEVE)	// 4 means the max dots in Gray16
#define FDL_MAX_SIZE_BOLD_ITALIC	(FDL_MAX_SIZE_BOLD + DCW_MAXITALICAMOUNT*FDL_GRAYLEVE)	// Jacky_20110630, check garbage pixels if it had been modified.
#define FDL_MAX_STACK           (276) //(300)	// 20110804: for memory, check 0x9F98 if you modified this
#define FDL_MAX_STROKE			(72)			// 20110929: to reduce memory size.
#define FDL_LIMIT_PATH_NUM_BY_MAX_STACK		// Jacky_20110509: enable this to secure the memory use according to FDL_MAX_STACK

#define FDL_RASTER_DRAW         0
#define FDL_RASTER_CLEAR        1
#define FDL_RASTER_BOLD         2
#define FDL_RASTER_RIGHT        3
#define FDL_RASTER_DOWN         4
#define FDL_RASTER_UP         	5
#define FDL_RASTER_RIGHT_DOWN   6
#define FDL_RASTER_RIGHT_UP     7

typedef enum
{
	FDL_PATH_IsRightOrButtom=1,
	FDL_PATH_LOCK_sx1 = 1 << 1,
	FDL_PATH_LOCK_sx3 = 1 << 2,
	FDL_PATH_LOCK_sy1 = 1 << 3,
	FDL_PATH_LOCK_sy3 = 1 << 4,
	FDL_PATH_IsCurve  = 1 << 5,
	FDL_PATH_IsLeft   = 1 << 6,
	FDL_PATH_MIRROR_CENTER = 1 << 7,
	FDL_PATH_IsJoint = 1 << 8,
	FDL_PATH_IsHide = 1 << 9,
	FDL_PATH_IsLNear = 1 << 10,
	FDL_PATH_IsLFar = 1 << 11,
	FDL_PATH_MIRROR_PATH = 1 << 12,
	FDL_PATH_TMPLOCK_s1 = 1 << 13,
	FDL_PATH_TMPLOCK_s3 = 1 << 14,
	FDL_PATH_MustHide = 1 << 15,
	FDL_PATH_MustHide2 = 1 << 16,
	FDL_PATH_PRIVATE_MIRROR_PATH = 1 << 17,
	FDL_PATH_PRIVATE_PATH_RATE = 1 << 18,
	FDL_PATH_PRIVATE_MIRROR_H_PATH = 1 << 19,
	FDL_PATH_PRIVATE_MIRROR_LINE_PATH = 1 << 20,
}FDL_PATH_HINT;

typedef enum
{
//	FDL_STROKE_HINT_NO=0,
	FDL_STROKE_MIRROR=1<<1,
	FDL_STROKE_MIRROR_TWO_LINES=1<<2,
	FDL_STROKE_PartHide=1<<3,
	FDL_STROKE_LEFT_LEAN=1<<4,
	FDL_STROKE_EN_REF_POINT=1<<5,
	FDL_STROKE_CANNOT_BE_A_LINE=1<<6,	/* 0x8CDE */
	FDL_STROKE_PartHide2=1<<7,			/* For adjust x value. */
}FDL_STROKE_HINT;

typedef enum
{
	FDL_STROKE_MIDDLE=0,
	FDL_STROKE_FIRST,
	FDL_STROKE_LAST,
}FDL_STROKE_ORDER;

typedef enum
{
	FDL_STROKE_TYPE_UNKNOW=0,
	FDL_STROKE_TYPE_HORZ,
	FDL_STROKE_TYPE_VERT,
}FDL_STROKE_TYPE;

union WEIGHT_MODE_UNIT {
	DT16_short mode;
	struct xy {
		DT8_char x;
		DT8_char y;
	}xy;
};

typedef struct {
	DT32_long XpointDiff;
	DT32_long YpointDiff;
}FDL_WEIGHT_MODE_UNIT;

/* The font outline struct
                                           +------> PATH_UNIT
                  +-----> STROKE_UNIT -----+------> ...
				  |                        +------> PATH_UNIT
    FONT_GROUP -->+-----> STROKE_UNIT ---->
    			  |                        +------> PATH_UNIT
    			  +-----> STROKE_UNIT -----+------> ...
    			                           +------> PATH_UNIT
*/

typedef struct {
	DT32_ulong lock;						// Combine with FDL_PATH_HINT enum struct.
	DT8_char  idx_interline;                // pointing to fdl->interlines respect the closed line path whether around other line path. 
	DT8_char strorder;						// The stroke order in this word. equal to the index of path's STROKE_UNIT in stroke_buf.
	DT8_char subidx;						// The path order in this path_buf.
	DT8_char dir;							// This path direct, FDL_PATH_NONE / FDL_PATH_HORZ / FDL_PATH_VERT.
	DT16_short relation;					// This path's left/right side path index.
	DT16_short mirror_relation;				// This path's mirror path index at another stroke.
	DT16_short stick_relation_path;			// If this path is horizontal and stick to special horizontal path index at another stroke.
	DT16_short stick_stroke;				// If lock enable FDL_PATH_MustHide flag, stick_stroke is point to stroke id.
	DT32_int stick_rate;

	DT32_long sx1x,		sy1y;				// The delta value for scale outline
	DT32_long sx2x,		sy2y;				// The delta value for scale outline
	DT32_long sx3x,		sy3y;				// The delta value for scale outline

	DT32_long sx1;		DT32_long sy1;		// This path's point 1 (sx1, sy1)
	DT32_long sx2;		DT32_long sy2;		// This path's point 2 (sx2, sy2)
	DT32_long sx3;		DT32_long sy3;		// This path's point 3 (sx3, sy3)

	DT32_long *sx01;	DT32_long *sy01;	// This path's point 1 and 3's x value which sx01 < sx03.
	DT32_long *sx03;	DT32_long *sy03;	// This path's point 1 and 3's y value which sy01 < sy03.

//	DT32_long sx1a,		sx3a;				// This path's origin point 1 (sx1, sx3)
	DT32_long sy1a,		sy3a;				// This path's origin point 3 (sy1, sy3)
	
}PATH_UNIT;

typedef struct {
	DT8_char status;						// This stroke status. Use FDL_STROKE_HINT.
	DT8_char line_type;						// Is this stroke could hinting, use enum FDL_STROKE_TYPE.
	DT8_char strorder;						// The stroke order in this word.
	DT8_char line_num;						// The path number in array line[].
	DT16_short stridmap;					// The stroke abstract ID.
	DT16_short strid;						// The stroke ID.
	DT16_short start;						// Point to path_buf
	DT16_short len;							// This stroke path number.
	DT16_short line[FDL_STROKE_LINE_MAX];	// This only store horizontal/vertical line in this stroke, and sort order.
	TRect	rect;							// This stroke rectangle.
//	DT32_long *ref_x;						// 20110804: Jacky marked for memory
//	DT32_long *ref_y;						// 20110804: Jacky marked for memory
}STROKE_UNIT;

#ifndef SIZEOF_ARRAY
    #define SIZEOF_ARRAY(ar)        (sizeof(ar)/sizeof((ar)[0]))
#endif // !defined(SIZEOF_ARRAY)

#ifdef FDL_OUTLINE_MODE
typedef struct {
	DT16_ushort			fontid;				// This font's unicode.
	DT8_uchar			groupnum;			// The group number.
	DT8_uchar			hintnum;			// THe hintlist[] array len.
	DT8_uchar			*grouplist;			// Pointer to group list.
	FDL_StrokeHint		*hintlist;			// Pointer to FDL_StrokeHint list, the max stroke id is 64, the bit 7~6 resrver for FDL_ALIGN_MODE flag.
}FONT_GROUP;

#endif // FDL_OUTLINE_MODE

// ============================================================================
#ifdef FDL_OUTLINE_CACHE
typedef struct
{
  PATH_UNIT		data;
  DT16_WORD		next;         					// Next Data Index
} OUTLINE_CACHE_UNIT, *pOUTLINE_CACHE_UNIT;

typedef struct {
	DT32_long key;
	DT16_WORD RingIndex;
	DT16_WORD idx;
}B_OutlineCacheUnit;

#define MAX_OUTLINE_CACHE_NUM		(FDL_OUTLINE_CACHE_SIZE / (sizeof(OUTLINE_CACHE_UNIT)*FDL_OUTLINE_UNIT_MINI_SIZE))

typedef struct
{
  DT_void        *wrk;    	 				// Pointer to Working memory
  pOUTLINE_CACHE_UNIT  pool; 				// OUTLINE_CACHE_UNIT pool
  DT32_long      memsize;   				// Memory size can be used

  DT16_WORD      freemax;					// Maximum OUTLINE_CACHE_UNIT number
  DT16_WORD      freelist;					// First free OUTLINE_CACHE_UNIT list
  DT16_WORD      recycle;					// Recycle OUTLINE_CACHE_UNIT list
  DT16_WORD      freenum;					// The total free OUTLINE_CACHE_UNIT number
} FdlOutlineCacheData, *pFdlOutlineCacheData;

DT_void FG_OutlineCache_Initial(pFdlOutlineCacheData fgdata, DT8_char *mem, DT32_long memsize, DT_void *wrk);
DT32_int FG_OutlineCache_Add(pFdlOutlineCacheData fgdata, PATH_UNIT *data, DT32_int num);
DT_void FG_OutlineCache_Delete(pFdlOutlineCacheData fgdata, DT16_WORD idx);
DT32_int FG_OutlineCache_GetPathData(pFdlOutlineCacheData fgdata, DT16_WORD idx, PATH_UNIT *data);
//pOUTLINE_CACHE_UNIT FG_OutlineCache_GetNext(pFdlOutlineCacheData fgdata, pOUTLINE_CACHE_UNIT pair);

#endif // end FDL_OUTLINE_CACHE
// ============================================================================
typedef struct
{
#ifdef DT_SUB_MEMORY
	struct allocator *submem;
#endif
#ifdef FDL_OUTLINE_MODE
	// GridFit Hinting
	DT32_long	fontsizex, fontsizey;
	DT32_long	fontidx;
	DT8_char	*gfstrid;							/* Grid Fitting Mode for each Stroke */
	DT32_int	gfmode;								/* Grid Fitting Mode */
	DT32_int	gfdx;								/* Move x Offset */
	DT32_int	gfdy;								/* Move y Offset */
	DT32_int	strid;
	DT32_int    stridcnt;							// Total stroke number in this word.
	DT32_int	subidx;								// For sub idex counter, Alan.
	DT32_int	path_num;							// The path number which in path_buf.
	PATH_UNIT	path_buf[FDL_MAX_STACK];			// The all path list.							// 20110804: memory		
	DT32_int	path_buf_pt_num;					// The path list number, after remove stroke.
	DT16_short	path_buf_pt[FDL_MAX_STACK];			// The path list which after remove stroke. Could not over 255, Alan.	// 20110804: memory

	STROKE_UNIT	stroke_buf[FDL_MAX_STROKE/*FDL_MAX_STACK/4*/];			// The stroke list.
	TRect		group_rect[FDL_MAX_STROKE/2/*FDL_MAX_STACK/8*/];		// The each group rectangle, this is the original position before hinting.		// 20110804: memory
	TRect		main_group_rect[FDL_MAX_STROKE/2/*FDL_MAX_STACK/8*/];	// The each main group rectangle, this is the original position before hinting.
	DT8_uchar	main_group_xtype[FDL_MAX_STROKE/2/*FDL_MAX_STACK/8*/];	// The X-aligntype in group, FDL_ALIGNPACK_X_LEFT_NEAREST...
	DT8_uchar	stroke_num;												// The stroke number, after remove stroke.
	DT8_uchar	stroke_order[FDL_MAX_STROKE/*FDL_MAX_STACK/4*/];		// The stroke list, after remove stroke.
	DT8_uchar	stroke_line_num;					// The stroke horizontal/vertical line number, after remove stroke.
	DT16_short	stroke_line_order[FDL_MAX_STACK];	// The stroke horizontal/vertical line list with sort, after remove stroke.
	DT32_int	stroke_NormalWeightX;				// Set the normal horizontal line's height is how many pixels, the value is the pixels * 10.
	DT32_int	stroke_NormalWeightY;				// Set the normal vertical line's width is how many pixels, the value is the pixels * 10.
	DT32_int	stroke_weightX;						// Set the horizontal line's height is how many pixels, the value is the pixels * 10.
	DT32_int	stroke_weightY;						// Set the vertical line's width is how many pixels, the value is the pixels * 10.
	DT32_int	stroke_weightXSpace;				// Set the horizontal line's space height is how many pixels, the value is the pixels * 10.
	DT32_int	stroke_weightYSpace;				// Set the vertical line's space width is how many pixels, the value is the pixels * 10.
	DT32_int	weight_modeH;						// -1 is disable mode, set to reduce how many Horizontal stroke of this ysize.
	DT32_int	hintlistH_num;						// How many Horizontal strokes of hintlist in the FDL.
	DT32_int	weight_modeV;						// -1 is disable mode, set to reduce how many Vertical stroke of this xsize.
	DT32_int	hintlistV_num;						// How many Vertical strokes of hintlist in the FDL.
	FDL_StrokeHint	hintlist[FDL_MAX_REMOVE_STROKE_NUM];	// For temp use, keep the info of hintlist. It can be deleted when FontTool is ready for FDL_REMOVE_STROKE_MIX_MODE	//20101115
	FONT_GROUP	groupinfo;
	DT8_uchar	group_wrknum;
	DT8_uchar	group_wrk[FDL_MAX_STROKE/2/*FDL_MAX_STACK/8*/];			// The stroke groups current do hinting. 0xFF: is not in process, include main group info.
	DT8_uchar	group_fin[FDL_MAX_STROKE/2/*FDL_MAX_STACK/8*/];			// The stroke groups status, after do hinting, include main group info.
//	DT8_uchar	group_list[FDL_MAX_STACK/8];		/* Jacky_Modified_20101015, DT8_char => DT8_uchar */	// 20110804: Jacky marked for memory
	DT16_short	HaveCenterStroke;					// Current work group center path, if don't have stroke in center, it value is -1.
	DT16_short	HaveCenterStrokeR;					// The current work group center stroke's relation path.
	DT8_uchar	path_tmp_num;						// The tmp buffer number.
	DT16_short	path_tmp_buf[FDL_MAX_STACK/*1024*/];// The tmp buffer.
	DT32_int	shift;								// The fdl->Frac2 + fdl->recycleshift
	DT32_int	recycle;							// Gray16: 3, Gray256: 15
	DT32_int	recycleshift;						// Shift bits, Gray16: 2, Gray256: 4
	DT32_int	*hint_move_offsetX, *hint_move_offsetY;

	DT8_uchar	interlines[FDL_MAX_STACK];          // Record the interpath information of linepaths.
#endif	// FDL_OUTLINE_MODE

#ifdef FDL_OUTLINE_CACHE
	DT8_char	Init_OutlineCache;					// For check if already init cache buffer.
	DT32_int OutlineCacheHead, OutlineCacheNum;
	B_OutlineCacheUnit OutlineBIndex[MAX_OUTLINE_CACHE_NUM];
	DT16_WORD OutlineRingIndex[MAX_OUTLINE_CACHE_NUM];
//	CacheUnit FontCache[MAX_CACHE_NUM];
#endif // end FDL_OUTLINE_CACHE

  DT_void	  *SetValuePt;		// For SetValue Function, Alan.
  DT_void    *AddPt2ScanPt;		// For AddPt2Scan2 Function, Alan.
  /* For font data reading */
  DT_void    *wrk;

  /* Stroke / Symbol data */
  DT16_WORD    defval[8];
  DT32_long    relno;
  DT8_BYTE    rel[16];
  DT32_long    valno;
  DT8_BYTE    val[8];
  DT32_long    sdatacnt;
  DT32_long    sdataofs;

  /* Font parameter */
  DT32_long    x0, y0;				/* Font Original */
  DT32_long    xorg, yorg;			/* Bitmap Buffer Origin */
  DT32_long    xsize, ysize;
  DT32_long    f_edge;
  DT32_long    w_edge;
  DT32_long    italic;
  DT8_char    *bmp;
  DT32_long    bmpw;
  DT8_BYTE		vert;				/* Vertical Writing */
  DT8_BYTE		rot;				/* Rotate font for Vertical Writing */
  TRect   fontbox;

  DT32_int     grade;
//  DT8_BYTE    gcolor[DCW_MAXGRAD+1];

  DT32_long    shiftx;				/* 2007-12-07 Radical (Shift for Symbol) */
  DT32_long    shifty;

  /* Rasterizer wroking parameter */
  DT32_int			hint;
  DT32_long    xsize2, ysize2;
  DT32_long    zoom;
  
  DT32_long    Mode;
  DT32_long    RasterCnt;
//  DT16_short   LeftBuf[FDL_MAX_SIZE_BOLD_ITALIC];
//  DT16_short   RightBuf[FDL_MAX_SIZE_BOLD_ITALIC];
  DT16_short   *LeftBuf;				/* for normal render, count: FDL_MAX_SIZE */
  DT16_short   *RightBuf;				/* for normal render, count: FDL_MAX_SIZE */


//  DT16_short   LBuf[FDL_MAX_SIZE_BOLD_ITALIC/* *DCW_MAXGRAD */];			/* for bold render */
//  DT16_short   RBuf[FDL_MAX_SIZE_BOLD_ITALIC/* *DCW_MAXGRAD */];			/* for bold render */
  DT16_short   *LBuf;			/* for bold render, count: FDL_MAX_SIZE_BOLD */
  DT16_short   *RBuf;			/* for bold render, count: FDL_MAX_SIZE_BOLD */

  DT8_BYTE     op;
  DT32_long    Xpoint[16], Ypoint[16];
  DT32_long    Value[8], HVal[8], WVal[8];
  DT32_long    Frac, Flat, FracMod;
  DT32_long    Frac2, Flat2;								// For Optimize, Alan.

#ifdef FDL_WEIGHT
  DT32_long    WeightX0, WeightY0, WeightX, WeightY, WeightRX, WeightRY;
  FDL_WEIGHT_MODE_UNIT WeightDiff[16];						// For cache weight, Alan.
  DT32_long	   WeightXDiff, WeightYDiff;

  DT32_long sx1x,		sy1y;
  DT32_long sx2x,		sy2y;
  DT32_long sx3x,		sy3y;
#endif

  DT32_int     xhead, xtail, yhead, ytail;
  DT32_long    MNx1, MNy1, MNx2, MNy2, Diffx, Diffy;
  DT32_long    sx1, sy1, sx2, sy2, sx3, sy3;
  DT32_int     lxwait, lywait, rxwait, rywait;
  DT32_int     LeftWait, RightWait;
#ifdef ENABLE_FDL_MODE_RASTER
    DT32_long    Stack[FDL_MAX_STACK];		// 20110929: 
#endif
  DT32_long    FirstX;

  DT32_int     isCurve, isLeft, S128;

  DT16_short   *Left_Ptr, *Right_Ptr;

  DT32_long    NsTop;                    /* Top coordinate               */
  DT32_long    NsDownL;                  /* Down coordinate of Left      */
  DT32_long    NsDownR;                  /* Down coordinate of Right     */
  DT32_long    NsFrac2;                  /* Half of One                  */
  DT32_long    NsMaxSeg;                 /* Max segment length of Curve  */
  TPoint  NsStack[FDL_MAX_STACK];        /* Stack for curve generator    */

  DT16_ushort	Symbolcnt;				 /* How many symbols in this fontidx */
  DT16_ushort	Strokecnt;				 /* How many strokes in this fontidx */
} TFdlRasterData, *pFdlRasterData;

DT32_int  FDL_GetFont(DT_void *wrk, pFdlRasterData fdl, DT32_int mode, DT32_int strid);
DT_void DoDrawLine(pFdlRasterData fdl, DT32_int y, DT32_int xl, DT32_int xr);

/*----------------------------------------------------------------------*/
/* Gradation Data                                                       */
/*----------------------------------------------------------------------*/
typedef struct
{
  DT16_short   xl;           /* Left X Coordinate    */
  DT16_short   xr;           /* Right X Coordinate   */
  DT16_WORD    next;         /* Next Scanline Index  */
} TFGXPair, *pFGXPair;

typedef struct
{
  DT_void		 *wrk;       /* Pointer to Working memory                */

  pFGXPair		 pool;       /* Scanline pool                            */
  DT32_long      memsize;    /* Memory size can be used                  */

  DT16_short     yt;         /* First scan line y coordinate             */
  DT16_short     yb;         /* Last scan line y coordinate              */
  DT16_WORD      linecnt;
  DT16_WORD      *line;      /* Pointer to first scanline of each line   */
  DT16_WORD      *linelast;  /* Pointer to first scanline of each line last, Alan.  */

  DT16_WORD      freemax;    /* Maximum scanline                         */
  DT16_WORD      freelist;   /* First free scanline                      */
  DT16_WORD      recycle;    /* Recycle scanline list                    */
} TFdlGradeData, *pFdlGradeData;

DT_void FG_Initial(pFdlGradeData fgdata, DT32_int yt, DT32_int yb, DT8_char *mem, DT32_long memsize, DT_void *wrk);
DT32_int  FG_Add(pFdlGradeData fgdata, DT32_int y, DT32_int xl, DT32_int xr);
DT32_int  FG_Delete(pFdlGradeData fgdata, DT32_int y, DT32_int xl, DT32_int xr);
DT_void FG_GetLineRange(pFdlGradeData fgdata, DT32_int *yt, DT32_int *yb);
pFGXPair FG_GetLine(pFdlGradeData fgdata, DT32_int y);
pFGXPair FG_GetNext(pFdlGradeData fgdata, pFGXPair pair);
DT32_int FG_GetLineNum(pFdlGradeData fgdata, pFGXPair pair);
DT32_long FG_UsedMemSize(pFdlGradeData fgdata);

/*----------------------------------------------------------------------*/
/* Working Memory                                                       */
/*----------------------------------------------------------------------*/
typedef struct
{
  /* Attribute */
  DCW_AttrData    attr;

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
#ifdef FDL_EXTEND
  DT32_long			  extend;
  DT32_long			  sizecount;
  DT32_long			  subcnt[5];
#endif

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
  TFDLRadParam    *rad;
  DT32_int             inrad;
  DT32_long            rdatacnt;
  DT32_long            rdataofs;

  /* FDL Data/Rasterizer */
  TFdlRasterData  fdl;

  /* Gradation Data */
  TFdlGradeData   gdata;

  FONT_GROUP	        groupinfo;    // DLHsieh

#ifdef FDL_OUTLINE_CACHE
  FdlOutlineCacheData goutlinecache;
#endif

  DT32_long				langtab;
  DT16_ushort			langtabcnt;
  
#if (1 != DCW_MAX_SIZEXY_ASPECT)
  DT32_long				ofs2RtoTab;
  Font_Ratio_Icon		RtoTable;
#endif

  #ifdef DT_DEBUG
//  FILE            *fp;
  #endif

#if _DCW_DEC_STROKE
  DT32_long       decstr;
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

} DcwWrk, *pDcwWrk;

//DT8_BYTE  FD_ReadStrByte(pDcwWrk wrk);
#define FD_ReadStrByte(wrk)	(DT8_BYTE)(*((DT8_BYTE*)(((pDcwWrk)wrk)->fd + ((pDcwWrk)wrk)->fdl.sdataofs++))); ((pDcwWrk)wrk)->fdl.sdatacnt --;

DT16_short FD_ReadStrShort(pDcwWrk wrk);

#endif

