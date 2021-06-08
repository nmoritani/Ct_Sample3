
#include "Dcw.h"
#include "DCW_FdlRaster.h"
//#include "Debug.h"

//#define AUTO_OFF
#define LIMIT_SIZE			24

#define ENABLE_STICK_Y
//#define ENABLE_STICK_X

#define		TOLERANCE_X				((1 << fdl->shift)*2/3)							// Need to currect x distance.
#define		TOLERANCE_Y				((1 << fdl->shift)*2/3)							// Need to currect y distance.

//#define		TOLERANCE_X				0						// Need to currect x distance.
//#define		TOLERANCE_Y				0							// Need to currect y distance.

#define FDL_RESORT_BY_HLINES		0
#define FDL_RESORT_BY_VLINES		1

#define FDL_SHORTEN_VALUE(x)		( (x)*2/3 )
#define FDL_FORCE_GROUP_INFO_WHEN_HINTING(x)	(fdl->groupinfo.fontid=(x))

#ifndef DT_DEBUG
#undef SVG_RETURN_STEP
#define SVG_RETURN_STEP(x)
#undef BEGINCODE
#define BEGINCODE()
#undef ENDCODE
#define ENDCODE()
#endif

#ifdef DT_SVG_DEBUG
//#include "svg.h"
#endif // DT_SVG_DEBUG

#ifndef min
	#define min(n1,n2)  (((n1) < (n2)) ? (n1) : (n2))
	#define max(n1,n2)  (((n1) > (n2)) ? (n1) : (n2))
#endif

#define ReadStrByte(fdl)    FD_ReadStrByte((pDcwWrk)fdl->wrk)
#define ReadStrShort(fdl)   FD_ReadStrShort((pDcwWrk)fdl->wrk)

#ifndef FDL_OUTLINE_MODE
/* Uses Macro to Speed Up */
#define ScaleX(fdl, val)              ((val * fdl->ysize + 128) / 256)
#define ScaleY(fdl, val)              ((val * fdl->xsize + 128) / 256)
#define ScaleX2(fdl, val)              ((val * fdl->ysize2 + 128) / 256)
#define ScaleY2(fdl, val)              ((val * fdl->xsize2 + 128) / 256)
#define Scaling(val, scale)           (val * scale / 256)
#define Scaling3(val, scale, scale2)  ((val * scale / 256) * scale2 / 256)
#else
#define ScaleX(fdl, val)              (val)
#define ScaleY(fdl, val)              (val)
#define ScaleX2(fdl, val)              (val)
#define ScaleY2(fdl, val)              (val)
#define Scaling(val, scale)           (val * scale / 256)
#define Scaling3(val, scale, scale2)  ((val * scale / 256) * scale2 / 256)
#endif

#define a2ScaleX(fdl, val)              ((val * fdl->ysize + 128) / 256)
#define a2ScaleY(fdl, val)              ((val * fdl->xsize + 128) / 256)
#define a2ScaleX2(fdl, val, x)          (((val << x) + 128) / 256)
#define a2ScaleY2(fdl, val, y)          (((val << y) + 128) / 256)

//#define CutVal(fdl, val)              ((val / fdl->Frac) * fdl->Frac)
//#define ItVal(fdl, val)               ((val / fdl->Flat) * fdl->Flat)
#ifdef OPTIMIZE_CHECK
	#define CutVal(fdl, val)              ((val >> fdl->Frac2) << fdl->Frac2)
#else
	#define CutVal(fdl, val)              ((val & (~0xFF)))							// I think Frac2 is 8, Alan.
#endif
#define ItVal(fdl, val)               ((val >> fdl->Flat2) << fdl->Flat2)

#define SetValueMacro(x, y, z)				((DT_void (*)(pFdlRasterData fdl, DT32_int index, DT32_int val)) (x)->SetValuePt) ((x), (y), (z))
#define AddPt2ScanPtMacro(x, y, z)				((DT_void (*)(pFdlRasterData fdl, DT32_long x1, DT32_long y2)) (x)->AddPt2ScanPt) ((x), (y), (z))
static DT_void SetValue(pFdlRasterData fdl, DT32_int index, DT32_int val);
static DT_void SetValueS128(pFdlRasterData fdl, DT32_int index, DT32_int val);

static DT32_int  Interpreter(pFdlRasterData fdl);
static DT_void Get_WW_Point(pFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval);
static DT_void Get_MN_Point(pFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval);
static DT_void Get_WW_XY(pFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval);
static DT_void Get_MN_XY(pFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval);
static DT_void PreCur(pFdlRasterData fdl);
static DT_void PreLastSCurve(pFdlRasterData fdl);
#ifdef ENABLE_FDL_MODE_RASTER
static DT_void Scurve(pFdlRasterData fdl);
#endif
static DT_void cutxy(pFdlRasterData fdl, DT32_int x,DT32_int y);
static DT_void Cpoint(pFdlRasterData fdl);
static DT_void Adjust(pFdlRasterData fdl);
static DT32_int  DrawBitmap(pFdlRasterData fdl);
static DT_void DoClearLine(pFdlRasterData fdl, DT32_int y, DT32_int xl, DT32_int xr);
static DT_void DoDrawDot(pFdlRasterData fdl, DT32_int x, DT32_int y, DT32_int clr);

/* New Scaline Generator */
static DT_void deLine(pFdlRasterData fdl, DT32_long x1, DT32_long y1, DT32_long x2, DT32_long y2);
static DT_void DoDeLine(pFdlRasterData fdl, DT32_long x1, DT32_long y1, DT32_long x2, DT32_long y2);
//static DT_void AddPt2Scan(pFdlRasterData fdl, DT32_long x, DT32_long y);
static DT_void AddPt2Scan2(pFdlRasterData fdl, DT32_long x, DT32_long y);		 // This doesn't check bound
static DT_void SCurve2(pFdlRasterData fdl);
static DT_void SCurve3(pFdlRasterData fdl);
static DT32_int Do_SCurve2(pFdlRasterData fdl, DT32_int subidx);
static DT_void Do_AdvHinting(pFdlRasterData fdl);
static DT_void NewScanInit(pFdlRasterData fdl);
static DT_void AssignLeftOrRight(pFdlRasterData fdl, DT32_int start, DT32_int cnt);
static DT32_int Do_SCurve3(pFdlRasterData fdl, DT32_int stridcnt, DT32_int subidx);
static DT_void ShiftStrokeX(pFdlRasterData fdl, DT32_int stridcnt, DT32_int x);
static DT_void ShiftStrokeY(pFdlRasterData fdl, DT32_int stridcnt, DT32_int y);
static DT_void ShiftStrokeW(pFdlRasterData fdl, DT32_int stridcnt, DT32_int w);
static DT_void ShiftStrokeH(pFdlRasterData fdl, DT32_int stridcnt, DT32_int h);
DT_void Do_SortCollectLines(pFdlRasterData fdl);
DT_void Do_SortCollectVLines(pFdlRasterData fdl);
DT32_int IsVLineOverlayX(PATH_UNIT *p1, PATH_UNIT *p2);
DT32_int IsVLineOverlayY(PATH_UNIT *p1, PATH_UNIT *p2);
DT_void Do_MoveStrokeXPath(pFdlRasterData fdl, DT32_int lineorder, DT32_int newpos);
DT_void Do_MoveStrokeYPath(pFdlRasterData fdl, DT32_int lineorder, DT32_int newpos);

DT_void GetCenterPointInGroup(pFdlRasterData fdl, DT32_int *centerpoint);
DT_void CheckStrokeMirrorStatusInGroup(pFdlRasterData fdl, DT32_int grpcenterpoint, DT32_int *centerestidx, DT32_int needsortfirst);
DT32_int GetGroupXAlignType(pFdlRasterData fdl, DT32_int remove_strorder, DT32_int centerestidx, DT32_int *rel_strorder, DT32_int group);

DT_void Do_MoveInterXPoint(pFdlRasterData fdl, DT32_long offset,  DT32_int lineorder, DT32_int/*BOOL*/ str_self);
DT_void Do_MoveInterXPath(pFdlRasterData fdl, DT32_long offset, DT32_int lineorder);
DT_void Do_AvgInterXPath(pFdlRasterData fdl, DT32_int lineorder);
DT32_int IsHLineOverlayX(PATH_UNIT *p01, PATH_UNIT *p02);

DT_void Do_FindInterPath(pFdlRasterData fdl);
DT_void Do_FindHidePath(pFdlRasterData fdl);
DT_void Do_FindJointPath(pFdlRasterData fdl);
DT_void Do_FindHidePath_L(pFdlRasterData fdl);
DT_void Do_FindLPath(pFdlRasterData fdl, DT8_char do_dir);
DT32_int IsLineOverlayX(DT32_int sx01, DT32_int sx03, DT32_int sx11, DT32_int sx13);
DT32_int IsLineOverlayY(DT32_int sy01, DT32_int sy03, DT32_int sy11, DT32_int sy13);
DT_void GetVerStickRelationPath(pFdlRasterData fdl);
DT_void CheckVerStickRelationPath(pFdlRasterData fdl);
DT_void Do_MoveStrokeXPath_LOCK(pFdlRasterData fdl, DT32_int lineorder, DT32_int newpos);
DT_void Do_TOLERANCE_Y(pFdlRasterData fdl);
DT_void Do_SortCollectLinesAllH(pFdlRasterData fdl);

DT_void DT_qsort(pFdlRasterData fdl, DT_void *va, DT32_long n, DT32_long es, DT32_int (*cmp)(pFdlRasterData, DT_void*, DT_void*));

//  00, 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15
static DT32_int move_offsetX016[] = { 0, -1, -2,  1,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,			// Left Line
									  0, -1, -2,  1,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0};		// Right Line
//static DT32_int move_offsetY016[] = { 0, -1, -2,  1,   0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,
static DT32_int move_offsetY016[] = { 0, -1, -2,  1,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,
									  0, -1,  2,  1,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0,  0,  0,};		// Right Line

static DT32_int move_offsetX256[] = { 0, -1, -2, -3, -4, -5, -6, -7, 8,  7,  6,  5,  4,  3,  2,  1,			// Left Line
									  0, -1, -2, -3, -4, -5, -6, -7, 8,  7,  6,  5,  4,  3,  2,  1 };		// Right Line
//static DT32_int move_offsetY256[] = { 0, -1, -2, -3,  -4, -5, -6, -7, 8,  7,  6,  5,  4,  3,  2,  1,		// Left Line
static DT32_int move_offsetY256[] = { 0, -1, -2, -3, -4, -5, -6, -7,-8, -9,-10,-11,-12,-13,-14,-15,			// Left Line
									  0, -1, -2, -3, -4, -5, -6, -7, 8,  7,  6,  5,  4,  3,  2,  1 };		// Right Line

extern DT32_int stroke_weight[];

/* FDL Instruction Process Routine */
static DT32_int OpENDSTR(pFdlRasterData fdl);
static DT32_int OpENDSUB(pFdlRasterData fdl);
static DT32_int OpMOVX(pFdlRasterData fdl);
static DT32_int OpMOVY(pFdlRasterData fdl);
static DT32_int OpSx(pFdlRasterData fdl);
static DT32_int OpLOAD(pFdlRasterData fdl);
static DT32_int OpXLOAD(pFdlRasterData fdl);
static DT32_int OpXVnADD(pFdlRasterData fdl);
static DT32_int OpXVnSUB(pFdlRasterData fdl);
static DT32_int OpYVnADD(pFdlRasterData fdl);
static DT32_int OpYVnSUB(pFdlRasterData fdl);
static DT32_int OpXVnA(pFdlRasterData fdl);
static DT32_int OpXVnS(pFdlRasterData fdl);
static DT32_int OpYVnA(pFdlRasterData fdl);
static DT32_int OpYVnS(pFdlRasterData fdl);
static DT32_int OpXWnADD(pFdlRasterData fdl);
static DT32_int OpXWnSUB(pFdlRasterData fdl);
static DT32_int OpYWnADD(pFdlRasterData fdl);
static DT32_int OpYWnSUB(pFdlRasterData fdl);
static DT32_int OpXWnA(pFdlRasterData fdl);
static DT32_int OpXWnS(pFdlRasterData fdl);
static DT32_int OpYWnA(pFdlRasterData fdl);
static DT32_int OpYWnS(pFdlRasterData fdl);
static DT32_int OpWWSTOR(pFdlRasterData fdl);
static DT32_int OpMNSTOR(pFdlRasterData fdl);
static DT32_int OpMNSx00(pFdlRasterData fdl);
static DT32_int OpMNSx10(pFdlRasterData fdl);
static DT32_int OpMNCx00(pFdlRasterData fdl);
static DT32_int OpMNCx10(pFdlRasterData fdl);
static DT32_int OpMNCx11(pFdlRasterData fdl);
static DT32_int OpWWSx00(pFdlRasterData fdl);
static DT32_int OpWWSx10(pFdlRasterData fdl);
static DT32_int OpWWCx00(pFdlRasterData fdl);
static DT32_int OpWWCx10(pFdlRasterData fdl);
static DT32_int OpWWCx11(pFdlRasterData fdl);
static DT32_int OpWWSTORb(pFdlRasterData fdl);
static DT32_int OpMNSTORb(pFdlRasterData fdl);
static DT32_int OpMNSx00b(pFdlRasterData fdl);
static DT32_int OpMNSx10b(pFdlRasterData fdl);
static DT32_int OpMNCx00b(pFdlRasterData fdl);
static DT32_int OpMNCx10b(pFdlRasterData fdl);
static DT32_int OpMNCx11b(pFdlRasterData fdl);
static DT32_int OpLMCx11b(pFdlRasterData fdl);
static DT32_int OpXMCx11b(pFdlRasterData fdl);
static DT32_int OpWWSx00b(pFdlRasterData fdl);
static DT32_int OpWWSx10b(pFdlRasterData fdl);
static DT32_int OpWWCx00b(pFdlRasterData fdl);
static DT32_int OpWWCx10b(pFdlRasterData fdl);
static DT32_int OpWWCx11b(pFdlRasterData fdl);
static DT32_int OpLWCx11b(pFdlRasterData fdl);
static DT32_int OpXWCx11b(pFdlRasterData fdl);
static DT32_int OpENDSUBb(pFdlRasterData fdl);
static DT32_int OpSWFX(pFdlRasterData fdl);
static DT32_int OpSWFY(pFdlRasterData fdl);

/*---------------------------------------------------------------------------*/
DT32_int DT_abs(DT32_int number )
{
	return( number>=0 ? number : -number );
}

/*---------------------------------------------------------------------------*/
DT_void SetValue(pFdlRasterData fdl, DT32_int index, DT32_int val)		// Don't support S128 mode
{
	fdl->Value[index] = val;

	val = val << fdl->Frac2;
#ifdef OPTIMIZE_CHECK
	if(fdl->S128)
	{
		fdl->HVal[index] = ScaleX2(fdl, val);
		fdl->WVal[index] = ScaleY2(fdl, val);
	} else
#endif
	{
		fdl->HVal[index] = val;
		fdl->WVal[index] = val;
	}
}

DT_void SetValueS128(pFdlRasterData fdl, DT32_int index, DT32_int val)
{
	fdl->Value[index] = val;

	val = val << fdl->Frac2;
	fdl->HVal[index] = ScaleX2(fdl, val);
	fdl->WVal[index] = ScaleY2(fdl, val);
}
/*---------------------------------------------------------------------------*/
/* FDL Instruction Process Routine                                           */
/*---------------------------------------------------------------------------*/
#define  MAX_OP   256

typedef DT32_int (*FdlInst)(pFdlRasterData fdl);

static const FdlInst FdlInsts[MAX_OP] =
{
	OpMNSx00,  NULL,      OpMNSx10,  OpSx,      OpMNSx00,  NULL,      OpMNSx10,  OpSx,
	OpMNCx00,  NULL,      OpMNCx10,  OpMNCx11,  OpMNCx00,  NULL,      OpMNCx10,  OpMNCx11,
	OpWWSx00,  NULL,      OpWWSx10,  NULL,      OpWWSx00,  NULL,      OpWWSx10,  NULL,
	OpWWCx00,  NULL,      OpWWCx10,  OpWWCx11,  OpWWCx00,  NULL,      OpWWCx10,  OpWWCx11,
	OpXWnADD,  OpXWnADD,  OpXWnADD,  OpXWnADD,  OpXWnADD,  OpXWnADD,  OpXWnADD,  OpXWnADD,
	OpXWnSUB,  OpXWnSUB,  OpXWnSUB,  OpXWnSUB,  OpXWnSUB,  OpXWnSUB,  OpXWnSUB,  OpXWnSUB,
	OpLOAD,    OpXLOAD,   OpMOVX,    OpMOVY,    OpMNSTOR,  OpWWSTOR,  OpSWFX,    OpSWFY,
	NULL,      NULL,      NULL,      NULL,      NULL,      NULL,      NULL,      NULL,
	OpYWnADD,  OpYWnADD,  OpYWnADD,  OpYWnADD,  OpYWnADD,  OpYWnADD,  OpYWnADD,  OpYWnADD,
	OpYWnSUB,  OpYWnSUB,  OpYWnSUB,  OpYWnSUB,  OpYWnSUB,  OpYWnSUB,  OpYWnSUB,  OpYWnSUB,
	OpXVnADD,  OpXVnADD,  OpXVnADD,  OpXVnADD,  OpXVnADD,  OpXVnADD,  OpXVnADD,  OpXVnADD,
	OpXVnSUB,  OpXVnSUB,  OpXVnSUB,  OpXVnSUB,  OpXVnSUB,  OpXVnSUB,  OpXVnSUB,  OpXVnSUB,
	OpYVnADD,  OpYVnADD,  OpYVnADD,  OpYVnADD,  OpYVnADD,  OpYVnADD,  OpYVnADD,  OpYVnADD,
	OpYVnSUB,  OpYVnSUB,  OpYVnSUB,  OpYVnSUB,  OpYVnSUB,  OpYVnSUB,  OpYVnSUB,  OpYVnSUB,
	OpENDSUB,  OpENDSTR,  NULL,      NULL,      NULL,      NULL,      NULL,      NULL,
	OpLMCx11b, OpLMCx11b, OpLWCx11b, OpLWCx11b, OpXMCx11b, OpXMCx11b, OpXWCx11b, OpXWCx11b,
	OpMNSx00b, NULL,      OpMNSx10b, NULL,      OpMNSx00b, NULL,      OpMNSx10b, NULL,
	OpMNCx00b, NULL,      OpMNCx10b, OpMNCx11b, OpMNCx00b, NULL,      OpMNCx10b, OpMNCx11b,
	OpWWSx00b, NULL,      OpWWSx10b, NULL,      OpWWSx00b, NULL,      OpWWSx10b, NULL,
	OpWWCx00b, NULL,      OpWWCx10b, OpWWCx11b, OpWWCx00b, NULL,      OpWWCx10b, OpWWCx11b,
	OpXWnA,    OpXWnA,    OpXWnA,    OpXWnA,    OpXWnA,    OpXWnA,    OpXWnA,    OpXWnA,
	OpXWnS,    OpXWnS,    OpXWnS,    OpXWnS,    OpXWnS,    OpXWnS,    OpXWnS,    OpXWnS,
	NULL,      NULL,      NULL,      NULL,      OpMNSTORb, OpWWSTORb, NULL,      NULL,
	NULL,      NULL,      NULL,      NULL,      NULL,     NULL,       NULL,      NULL,
	OpYWnA,    OpYWnA,    OpYWnA,    OpYWnA,    OpYWnA,    OpYWnA,    OpYWnA,    OpYWnA,
	OpYWnS,    OpYWnS,    OpYWnS,    OpYWnS,    OpYWnS,    OpYWnS,    OpYWnS,    OpYWnS,
	OpXVnA,    OpXVnA,    OpXVnA,    OpXVnA,    OpXVnA,    OpXVnA,    OpXVnA,    OpXVnA,
	OpXVnS,    OpXVnS,    OpXVnS,    OpXVnS,    OpXVnS,    OpXVnS,    OpXVnS,    OpXVnS,
	OpYVnA,    OpYVnA,    OpYVnA,    OpYVnA,    OpYVnA,    OpYVnA,    OpYVnA,    OpYVnA,
	OpYVnS,    OpYVnS,    OpYVnS,    OpYVnS,    OpYVnS,    OpYVnS,    OpYVnS,    OpYVnS,
	OpENDSUBb, NULL,      NULL,      NULL,      NULL,      NULL,      NULL,      NULL,
	NULL,      NULL,      NULL,      NULL,      NULL,      NULL,      NULL,      NULL
};

#ifdef DT_DEBUG
#define DT_DEBUG_CMD

#ifdef DT_DEBUG_CMD
	#define	DumpDebugStringCMD			DumpDebugString
#else
	DT_void __cdecl DumpDebugStringCMD(DT8_char* szFormat, ...)
	{
	}// end DumpDebugStringCMD
#endif

static DT8_char *op_strold[MAX_OP] =
{
	"mnsl00", "mnsl01", "mnsl10", "sl    ", "mnsr00", "mnsr01", "mnsr10", "sr    ",
	"mncl00", "mncl01", "mncl10", "mncl11", "mncr00", "mncr01", "mncr10", "mncr11",
	"wwsl00", "wwsl01", "wwsl10", "      ", "wwsr00", "wwsr01", "wwsr10", "      ",
	"wwcl00", "wwcl01", "wwcl10", "wwcl11", "wwcr00", "wwcr01", "wwcr10", "wwcr11",
	"x+w0* ", "x+w1* ", "x+w2* ", "x+w3* ", "x+w4* ", "x+w5* ", "x+w6* ", "x+w7* ",
	"x-w0* ", "x-w1* ", "x-w2* ", "x-w3* ", "x-w4* ", "x-w5* ", "x-w6* ", "x-w7* ",
	"load  ", "xload ", "movx  ", "movy  ", "mnstor", "wwstor", "swfx  ", "swfy  ",
	"      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ",
	"y+w0* ", "y+w1* ", "y+w2* ", "y+w3* ", "y+w4* ", "y+w5* ", "y+w6* ", "y+w7* ",
	"y-w0* ", "y-w1* ", "y-w2* ", "y-w3* ", "y-w4* ", "y-w5* ", "y-w6* ", "y-w7* ",
	"x+v0* ", "x+v1* ", "x+v2* ", "x+v3* ", "x+v4* ", "x+v5* ", "x+v6* ", "x+v7* ",
	"x-v0* ", "x-v1* ", "x-v2* ", "x-v3* ", "x-v4* ", "x-v5* ", "x-v6* ", "x-v7* ",
	"y+v0* ", "y+v1* ", "y+v2* ", "y+v3* ", "y+v4* ", "y+v5* ", "y+v6* ", "y+v7* ",
	"y-v0* ", "y-v1* ", "y-v2* ", "y-v3* ", "y-v4* ", "y-v5* ", "y-v6* ", "y-v7* ",
	"endsub", "endstr", "      ", "      ", "      ", "      ", "      ", "      ",
	"LMcl11", "LMcr11", "LWcl11", "LWcr11", "XMcl11", "XMcr11", "XWcl11", "XWcr11",
	"MNsl00", "MNsl01", "MNsl10", "      ", "MNsr00", "MNsr01", "MNsr10", "      ",
	"MNcl00", "MNcl01", "MNcl10", "MNcl11", "MNcr00", "MNcr01", "MNcr10", "MNcr11",
	"WWsl00", "WWsl01", "WWsl10", "      ", "WWsr00", "WWsr01", "WWsr10", "      ",
	"WWcl00", "WWcl01", "WWcl10", "WWcl11", "WWcr00", "WWcr01", "WWcr10", "WWcr11",
	"x+w0*1", "x+w1*1", "x+w2*1", "x+w3*1", "x+w4*1", "x+w5*1", "x+w6*1", "x+w7*1",
	"x-w0*1", "x-w1*1", "x-w2*1", "x-w3*1", "x-w4*1", "x-w5*1", "x-w6*1", "x-w7*1",
	"      ", "      ", "      ", "      ", "MNstor", "WWstor", "      ", "      ",
	"      ", "      ", "      ", "      ", "      ", "      ", "      ", "      ",
	"y+w0*1", "y+w1*1", "y+w2*1", "y+w3*1", "y+w4*1", "y+w5*1", "y+w6*1", "y+w7*1",
	"y-w0*1", "y-w1*1", "y-w2*1", "y-w3*1", "y-w4*1", "y-w5*1", "y-w6*1", "y-w7*1",
	"x+v0*1", "x+v1*1", "x+v2*1", "x+v3*1", "x+v4*1", "x+v5*1", "x+v6*1", "x+v7*1",
	"x-v0*1", "x-v1*1", "x-v2*1", "x-v3*1", "x-v4*1", "x-v5*1", "x-v6*1", "x-v7*1",
	"y+v0*1", "y+v1*1", "y+v2*1", "y+v3*1", "y+v4*1", "y+v5*1", "y+v6*1", "y+v7*1",
	"y-v0*1", "y-v1*1", "y-v2*1", "y-v3*1", "y-v4*1", "y-v5*1", "y-v6*1", "y-v7*1",
	"ENDSUB", "      ", "      ", "      ", "      ", "      ", "      ", "      ",
	"      ", "      ", "      ", "      ", "      ", "      ", "      ", "      "
};

static DT8_char *op_str[MAX_OP] =
{
	"OpMNSx00 : mnsl00",    "NULL     : mnsl01",    "OpMNSx10 : mnsl10",    "OpSx     : sl    ",    "OpMNSx00 : mnsr00",    "NULL     : mnsr01",    "OpMNSx10 : mnsr10",    "OpSx     : sr    ",
	"OpMNCx00 : mncl00",    "NULL     : mncl01",    "OpMNCx10 : mncl10",    "OpMNCx11 : mncl11",    "OpMNCx00 : mncr00",    "NULL     : mncr01",    "OpMNCx10 : mncr10",    "OpMNCx11 : mncr11",
	"OpWWSx00 : wwsl00",    "NULL     : wwsl01",    "OpWWSx10 : wwsl10",    "NULL     :       ",    "OpWWSx00 : wwsr00",    "NULL     : wwsr01",    "OpWWSx10 : wwsr10",    "NULL     :       ",
	"OpWWCx00 : wwcl00",    "NULL     : wwcl01",    "OpWWCx10 : wwcl10",    "OpWWCx11 : wwcl11",    "OpWWCx00 : wwcr00",    "NULL     : wwcr01",    "OpWWCx10 : wwcr10",    "OpWWCx11 : wwcr11",
	"OpXWnADD : x+w0* ",    "OpXWnADD : x+w1* ",    "OpXWnADD : x+w2* ",    "OpXWnADD : x+w3* ",    "OpXWnADD : x+w4* ",    "OpXWnADD : x+w5* ",    "OpXWnADD : x+w6* ",    "OpXWnADD : x+w7* ",
	"OpXWnSUB : x-w0* ",    "OpXWnSUB : x-w1* ",    "OpXWnSUB : x-w2* ",    "OpXWnSUB : x-w3* ",    "OpXWnSUB : x-w4* ",    "OpXWnSUB : x-w5* ",    "OpXWnSUB : x-w6* ",    "OpXWnSUB : x-w7* ",
	"OpLOAD   : load  ",    "OpXLOAD  : xload ",    "OpMOVX   : movx  ",    "OpMOVY   : movy  ",    "OpMNSTOR : mnstor",    "OpWWSTOR : wwstor",    "OpSWFX   : swfx  ",    "OpSWFY   : swfy  ",
	"NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",
	"OpYWnADD : y+w0* ",    "OpYWnADD : y+w1* ",    "OpYWnADD : y+w2* ",    "OpYWnADD : y+w3* ",    "OpYWnADD : y+w4* ",    "OpYWnADD : y+w5* ",    "OpYWnADD : y+w6* ",    "OpYWnADD : y+w7* ",
	"OpYWnSUB : y-w0* ",    "OpYWnSUB : y-w1* ",    "OpYWnSUB : y-w2* ",    "OpYWnSUB : y-w3* ",    "OpYWnSUB : y-w4* ",    "OpYWnSUB : y-w5* ",    "OpYWnSUB : y-w6* ",    "OpYWnSUB : y-w7* ",
	"OpXVnADD : x+v0* ",    "OpXVnADD : x+v1* ",    "OpXVnADD : x+v2* ",    "OpXVnADD : x+v3* ",    "OpXVnADD : x+v4* ",    "OpXVnADD : x+v5* ",    "OpXVnADD : x+v6* ",    "OpXVnADD : x+v7* ",
	"OpXVnSUB : x-v0* ",    "OpXVnSUB : x-v1* ",    "OpXVnSUB : x-v2* ",    "OpXVnSUB : x-v3* ",    "OpXVnSUB : x-v4* ",    "OpXVnSUB : x-v5* ",    "OpXVnSUB : x-v6* ",    "OpXVnSUB : x-v7* ",
	"OpYVnADD : y+v0* ",    "OpYVnADD : y+v1* ",    "OpYVnADD : y+v2* ",    "OpYVnADD : y+v3* ",    "OpYVnADD : y+v4* ",    "OpYVnADD : y+v5* ",    "OpYVnADD : y+v6* ",    "OpYVnADD : y+v7* ",
	"OpYVnSUB : y-v0* ",    "OpYVnSUB : y-v1* ",    "OpYVnSUB : y-v2* ",    "OpYVnSUB : y-v3* ",    "OpYVnSUB : y-v4* ",    "OpYVnSUB : y-v5* ",    "OpYVnSUB : y-v6* ",    "OpYVnSUB : y-v7* ",
	"OpENDSUB : endsub",    "OpENDSTR : endstr",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",
	"OpLMCx11b: LMcl11",    "OpLMCx11b: LMcr11",    "OpLWCx11b: LWcl11",    "OpLWCx11b: LWcr11",    "OpXMCx11b: XMcl11",    "OpXMCx11b: XMcr11",    "OpXWCx11b: XWcl11",    "OpXWCx11b: XWcr11",
	"OpMNSx00b: MNsl00",    "NULL     : MNsl01",    "OpMNSx10b: MNsl10",    "NULL     :       ",    "OpMNSx00b: MNsr00",    "NULL     : MNsr01",    "OpMNSx10b: MNsr10",    "NULL     :       ",
	"OpMNCx00b: MNcl00",    "NULL     : MNcl01",    "OpMNCx10b: MNcl10",    "OpMNCx11b: MNcl11",    "OpMNCx00b: MNcr00",    "NULL     : MNcr01",    "OpMNCx10b: MNcr10",    "OpMNCx11b: MNcr11",
	"OpWWSx00b: WWsl00",    "NULL     : WWsl01",    "OpWWSx10b: WWsl10",    "NULL     :       ",    "OpWWSx00b: WWsr00",    "NULL     : WWsr01",    "OpWWSx10b: WWsr10",    "NULL     :       ",
	"OpWWCx00b: WWcl00",    "NULL     : WWcl01",    "OpWWCx10b: WWcl10",    "OpWWCx11b: WWcl11",    "OpWWCx00b: WWcr00",    "NULL     : WWcr01",    "OpWWCx10b: WWcr10",    "OpWWCx11b: WWcr11",
	"OpXWnA   : x+w0*1",    "OpXWnA   : x+w1*1",    "OpXWnA   : x+w2*1",    "OpXWnA   : x+w3*1",    "OpXWnA   : x+w4*1",    "OpXWnA   : x+w5*1",    "OpXWnA   : x+w6*1",    "OpXWnA   : x+w7*1",
	"OpXWnS   : x-w0*1",    "OpXWnS   : x-w1*1",    "OpXWnS   : x-w2*1",    "OpXWnS   : x-w3*1",    "OpXWnS   : x-w4*1",    "OpXWnS   : x-w5*1",    "OpXWnS   : x-w6*1",    "OpXWnS   : x-w7*1",
	"NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "OpMNSTORb: MNstor",    "OpWWSTORb: WWstor",    "NULL     :       ",    "NULL     :       ",
	"NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",
	"OpYWnA   : y+w0*1",    "OpYWnA   : y+w1*1",    "OpYWnA   : y+w2*1",    "OpYWnA   : y+w3*1",    "OpYWnA   : y+w4*1",    "OpYWnA   : y+w5*1",    "OpYWnA   : y+w6*1",    "OpYWnA   : y+w7*1",
	"OpYWnS   : y-w0*1",    "OpYWnS   : y-w1*1",    "OpYWnS   : y-w2*1",    "OpYWnS   : y-w3*1",    "OpYWnS   : y-w4*1",    "OpYWnS   : y-w5*1",    "OpYWnS   : y-w6*1",    "OpYWnS   : y-w7*1",
	"OpXVnA   : x+v0*1",    "OpXVnA   : x+v1*1",    "OpXVnA   : x+v2*1",    "OpXVnA   : x+v3*1",    "OpXVnA   : x+v4*1",    "OpXVnA   : x+v5*1",    "OpXVnA   : x+v6*1",    "OpXVnA   : x+v7*1",
	"OpXVnS   : x-v0*1",    "OpXVnS   : x-v1*1",    "OpXVnS   : x-v2*1",    "OpXVnS   : x-v3*1",    "OpXVnS   : x-v4*1",    "OpXVnS   : x-v5*1",    "OpXVnS   : x-v6*1",    "OpXVnS   : x-v7*1",
	"OpYVnA   : y+v0*1",    "OpYVnA   : y+v1*1",    "OpYVnA   : y+v2*1",    "OpYVnA   : y+v3*1",    "OpYVnA   : y+v4*1",    "OpYVnA   : y+v5*1",    "OpYVnA   : y+v6*1",    "OpYVnA   : y+v7*1",
	"OpYVnS   : y-v0*1",    "OpYVnS   : y-v1*1",    "OpYVnS   : y-v2*1",    "OpYVnS   : y-v3*1",    "OpYVnS   : y-v4*1",    "OpYVnS   : y-v5*1",    "OpYVnS   : y-v6*1",    "OpYVnS   : y-v7*1",
	"OpENDSUBb: ENDSUB",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",
	"NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       ",    "NULL     :       "
};

#endif

/*---------------------------------------------------------------------------*/
DT32_int  Interpreter(pFdlRasterData fdl)
{
	DT8_BYTE reg;
	FdlInst Inst;
	DT32_int ret;

	do
	{
		/* Get Instruction Operation Code */
		fdl->op = (DT8_BYTE)ReadStrByte(fdl);

		/* Get Instruction Source/Destination */
		reg = (DT8_BYTE)ReadStrByte(fdl);
		fdl->xhead = fdl->yhead = reg >> 4;
		fdl->xtail = fdl->ytail = reg & 0x0f;

		/* Get Instruction Process Routine */
		Inst = FdlInsts[fdl->op];
		if(Inst != NULL)
		{
			/* Execute Instruction */
			ret = Inst(fdl);
			if(ret != 0) return(ret);
		} else
			return(FDL_UNKNOW_OP);
	} while(fdl->sdatacnt > 0);

	PreLastSCurve(fdl);
//	InfoPath(fdl);
	return(FDL_END_OF_STR);
}


/*---------------------------------------------------------------------------*/
DT32_int OpENDSTR(pFdlRasterData fdl)
{
	//DumpDebugStringCMD("%s\n", op_str[fdl->op]);
	PreLastSCurve(fdl);
	//InfoPath(fdl);
	return(FDL_END_OF_STR);
}
/*---------------------------------------------------------------------------*/
DT32_int OpENDSUB(pFdlRasterData fdl)
{
	//DumpDebugStringCMD("%s\n", op_str[fdl->op]);
	PreLastSCurve(fdl);
//	InfoPath(fdl);
	return(FDL_END_OF_SUB);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMOVX(pFdlRasterData fdl)
{
	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead];
#ifdef FDL_CACHE_WEIGHT
	fdl->WeightDiff[fdl->xtail].XpointDiff = fdl->WeightDiff[fdl->xhead].XpointDiff;
	//DumpDebugStringCMD("%s x[%d, %d] %d, %d\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->Xpoint[fdl->xtail], fdl->WeightDiff[fdl->xtail].XpointDiff);
#else
	//DumpDebugStringCMD("%s x[%d, %d] %d\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->Xpoint[fdl->xtail]);
#endif
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMOVY(pFdlRasterData fdl)
{
	fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead];
#ifdef FDL_CACHE_WEIGHT
	fdl->WeightDiff[fdl->xtail].YpointDiff = fdl->WeightDiff[fdl->xhead].YpointDiff;
	//DumpDebugStringCMD("%s y[%d, %d] %d, %d\n", op_str[fdl->op], fdl->yhead, fdl->ytail, fdl->Ypoint[fdl->ytail], fdl->WeightDiff[fdl->xtail].YpointDiff);
#else
	//DumpDebugStringCMD("%s y[%d, %d] %d\n", op_str[fdl->op], fdl->yhead, fdl->ytail, fdl->Ypoint[fdl->ytail]);
#endif
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpSx(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==SL;
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
	fdl->isCurve = 0;

#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
fdl->sx2x = fdl->WeightDiff[fdl->xhead].XpointDiff;
fdl->sy2y = fdl->WeightDiff[fdl->yhead].YpointDiff;
	fdl->sx3x = fdl->WeightDiff[fdl->xtail].XpointDiff;
	fdl->sy3y = fdl->WeightDiff[fdl->ytail].YpointDiff;
#endif

	//DumpDebugStringCMD("%s: x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	//DumpDebugStringCMD("    (%d, %d), (%d, %d), (%d, %d)\n", fdl->sx1x, fdl->sy1y, fdl->sx2x, fdl->sy2y, fdl->sx3x, fdl->sy3y);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpLOAD(pFdlRasterData fdl)
{
	fdl->MNx1 = fdl->Xpoint[fdl->xhead];
	fdl->MNy1 = fdl->Ypoint[fdl->yhead];
	fdl->MNx2 = fdl->Xpoint[fdl->xtail];
	fdl->MNy2 = fdl->Ypoint[fdl->ytail];
	fdl->Diffx = fdl->MNx2 - fdl->MNx1;
	fdl->Diffy = fdl->MNy2 - fdl->MNy1;

	//DumpDebugStringCMD("%s: x[%d, %d] y[%d, %d] (%d, %d), (%d, %d) => (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->MNx1, fdl->MNy1, fdl->MNx2, fdl->MNy2, fdl->Diffx, fdl->Diffy);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXLOAD(pFdlRasterData fdl)
{
	fdl->MNx1 = fdl->Xpoint[fdl->xhead];
	fdl->MNy1 = fdl->Ypoint[fdl->ytail];
	fdl->MNx2 = fdl->Xpoint[fdl->xtail];
	fdl->MNy2 = fdl->Ypoint[fdl->yhead];
	fdl->Diffx = fdl->MNx2 - fdl->MNx1;
	fdl->Diffy = fdl->MNy2 - fdl->MNy1;

	//DumpDebugStringCMD("%s: x[%d, %d] y[%d, %d] (%d, %d), (%d, %d) => (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->MNx1, fdl->MNy1, fdl->MNx2, fdl->MNy2, fdl->Diffx, fdl->Diffy);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXVnADD(pFdlRasterData fdl)
{
	DT32_int rate, Vn;

	rate = ReadStrShort(fdl);

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		Vn = Scaling(fdl->HVal[fdl->op - XV0ADD], rate);
		fdl->WeightDiff[fdl->xtail].XpointDiff = -(Vn - fdl->WeightDiff[fdl->xhead].XpointDiff);
	#else
		Vn = Scaling3(fdl->HVal[fdl->op - XV0ADD], rate, fdl->WeightX);
	#endif
#else
	Vn = Scaling(fdl->HVal[fdl->op - XV0ADD], rate);
#endif

//	if(rate==256) Vn = CutVal(fdl, Vn);
	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] + Vn;
	//DumpDebugStringCMD("%s x[%d, %d] Vn+: %d, %d <=X*\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Xpoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXVnSUB(pFdlRasterData fdl)	// <==
{
	DT32_int rate, Vn;

	rate = ReadStrShort(fdl);

#ifdef FDL_WEIGHT
	//DumpDebugStringCMD("               org Vn: %d\n", Scaling(fdl->HVal[fdl->op - XV0SUB], rate) );
	#ifdef FDL_CACHE_WEIGHT
		Vn = Scaling(fdl->HVal[fdl->op - XV0SUB], rate);
//		if(rate==256) Vn = CutVal(fdl, Vn);
		fdl->WeightDiff[fdl->xtail].XpointDiff = Vn + fdl->WeightDiff[fdl->xhead].XpointDiff;
	#else
//		Vn = Scaling3(fdl->HVal[fdl->op - XV0SUB], rate, fdl->WeightX);
		Vn = Scaling(fdl->HVal[fdl->op - XV0SUB], rate);
		Vn = Vn * fdl->WeightX / 256;
	#endif
#else
	Vn = Scaling(fdl->HVal[fdl->op - XV0SUB], rate);
#endif

//	if(rate==256) Vn = CutVal(fdl, Vn);
	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] - Vn;
	//DumpDebugStringCMD("%s x[%d, %d] Vn-: %d, %d<=X*\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Xpoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpYVnADD(pFdlRasterData fdl)
{
	DT32_int rate, Vn;

	rate = ReadStrShort(fdl);

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		Vn = Scaling(fdl->WVal[fdl->op - YV0ADD], rate);
		fdl->WeightDiff[fdl->xtail].YpointDiff = -(Vn - fdl->WeightDiff[fdl->xhead].YpointDiff);
	#else
		Vn = Scaling3(fdl->WVal[fdl->op - YV0ADD], rate, fdl->WeightY);
	#endif
#else
	Vn = Scaling(fdl->WVal[fdl->op - YV0ADD], rate);
#endif

//	if(rate==256) Vn = CutVal(fdl, Vn);
	fdl->Ypoint[fdl->xtail] = fdl->Ypoint[fdl->xhead] + Vn;
	//DumpDebugStringCMD("%s y[%d, %d] Vn+: %d, %d <=Y*, %d\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Ypoint[fdl->xtail], fdl->WeightDiff[fdl->xtail].YpointDiff);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpYVnSUB(pFdlRasterData fdl)
{
	DT32_int rate, Vn;

	rate = ReadStrShort(fdl);

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		Vn = Scaling(fdl->WVal[fdl->op - YV0SUB], rate);
		//if(rate==256) Vn = CutVal(fdl, Vn);
		fdl->WeightDiff[fdl->xtail].YpointDiff = Vn + fdl->WeightDiff[fdl->xhead].YpointDiff;
	#else
		Vn = Scaling3(fdl->WVal[fdl->op - YV0SUB], rate, fdl->WeightY);
	#endif
#else
	Vn = Scaling(fdl->WVal[fdl->op - YV0SUB], rate);
#endif

//	if(rate==256) Vn = CutVal(fdl, Vn);
	fdl->Ypoint[fdl->xtail] = fdl->Ypoint[fdl->xhead] - Vn;
	//DumpDebugStringCMD("%s y[%d, %d] Vn-: %d, %d <=Y*\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Ypoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXVnA(pFdlRasterData fdl)		// <==
{
	DT32_int Vn;

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		Vn = fdl->HVal[fdl->op - XV0A];
		Vn = CutVal(fdl, Vn);
		fdl->WeightDiff[fdl->xtail].XpointDiff = -(Vn - fdl->WeightDiff[fdl->xhead].XpointDiff);
	#else
		Vn = Scaling(fdl->HVal[fdl->op - XV0A], fdl->WeightX);
	#endif
#else
	Vn = fdl->HVal[fdl->op - XV0A];
#endif

	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] + CutVal(fdl, Vn);
	//DumpDebugStringCMD("%s x[%d, %d] Vn+: %d, %d<=X*\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Xpoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXVnS(pFdlRasterData fdl)
{
	DT32_int Vn;

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		Vn = fdl->HVal[fdl->op - XV0S];
		fdl->WeightDiff[fdl->xtail].XpointDiff = Vn + fdl->WeightDiff[fdl->xhead].XpointDiff;
	#else
		Vn = Scaling(fdl->HVal[fdl->op - XV0S], fdl->WeightX);
	#endif
#else
	Vn = fdl->HVal[fdl->op - XV0S];
#endif

	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] - CutVal(fdl, Vn);
	//DumpDebugStringCMD("%s x[%d, %d] Vn-: %d, %d<=X*\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Xpoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpYVnA(pFdlRasterData fdl)		// ==>
{
	DT32_int Vn;

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		Vn = fdl->WVal[fdl->op - YV0A];
		Vn = CutVal(fdl, Vn);
		fdl->WeightDiff[fdl->xtail].YpointDiff = -(Vn - fdl->WeightDiff[fdl->xhead].YpointDiff);
	#else
		Vn = Scaling(fdl->WVal[fdl->op - YV0A], fdl->WeightY);
		Vn = CutVal(fdl, Vn);
	#endif
#else
	Vn = fdl->WVal[fdl->op - YV0A];
	Vn = CutVal(fdl, Vn);
#endif

	fdl->Ypoint[fdl->xtail] = fdl->Ypoint[fdl->xhead] + Vn;
	//DumpDebugStringCMD("%s y[%d, %d] Vn+: %d, %d<=Y*\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Ypoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpYVnS(pFdlRasterData fdl)
{
	DT32_int Vn;

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		Vn = fdl->WVal[fdl->op - YV0S];
		fdl->WeightDiff[fdl->xtail].YpointDiff = Vn + fdl->WeightDiff[fdl->xhead].YpointDiff;
	#else
		Vn = Scaling(fdl->WVal[fdl->op - YV0S], fdl->WeightY);
	#endif
#else
	Vn = fdl->WVal[fdl->op - YV0S];
#endif

	fdl->Ypoint[fdl->xtail] = fdl->Ypoint[fdl->xhead] - CutVal(fdl, Vn);
	//DumpDebugStringCMD("%s x[%d, %d] Vn-: %d, %d<=Y*\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Ypoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXWnADD(pFdlRasterData fdl)
{
	DT32_int idx, rate, factor, Vn;

	idx = fdl->op - XW0ADD;
	rate   = ReadStrShort(fdl);
	factor = ReadStrShort(fdl);
	Vn = Scaling(fdl->HVal[idx], rate);

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		fdl->WeightDiff[fdl->xtail].XpointDiff = -(Vn - fdl->WeightDiff[fdl->xhead].XpointDiff);
	#else
		Vn += Scaling3(fdl->HVal[idx], fdl->WeightX-256, factor);
	#endif
#endif

//	if(rate==256) Vn = CutVal(fdl, Vn);
	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] + Vn;
	//DumpDebugStringCMD("%s x[%d, %d] -256Vn+: %d, %d<=X*-256, factor\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Xpoint[fdl->xtail], factor);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXWnSUB(pFdlRasterData fdl)
{
	DT32_int idx, rate, factor, Vn;

	idx = fdl->op - XW0SUB;
	rate   = ReadStrShort(fdl);
	factor = ReadStrShort(fdl);
	Vn = Scaling(fdl->HVal[idx], rate);

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		fdl->WeightDiff[fdl->xtail].XpointDiff = Vn + fdl->WeightDiff[fdl->xhead].XpointDiff;
	#else
		Vn += Scaling3(fdl->HVal[idx], fdl->WeightX-256, factor);
	#endif
#endif

//	if(rate==256) Vn = CutVal(fdl, Vn);
	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] - Vn;
	//DumpDebugStringCMD("%s x[%d, %d] -256Vn-: %d, %d<=X*-256\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Xpoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpYWnADD(pFdlRasterData fdl)
{
	DT32_int idx, rate, factor, Vn;

	idx = fdl->op - YW0ADD;
	rate   = ReadStrShort(fdl);
	factor = ReadStrShort(fdl);
	Vn = Scaling(fdl->WVal[idx], rate);

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		fdl->WeightDiff[fdl->ytail].YpointDiff = -Vn;
	#else
		Vn += Scaling3(fdl->WVal[idx], fdl->WeightY-256, factor);
	#endif
#endif

//	if(rate==256) Vn = CutVal(fdl, Vn);
	fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead] + Vn;
	//DumpDebugStringCMD("%s y[%d, %d] -256Vn+: %d, %d<=Y*-256\n", op_str[fdl->op], fdl->yhead, fdl->ytail, Vn, fdl->Ypoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpYWnSUB(pFdlRasterData fdl)
{
	DT32_int idx, rate, factor, Vn;

	idx = fdl->op - YW0SUB;
	rate   = ReadStrShort(fdl);
	factor = ReadStrShort(fdl);
	Vn = Scaling(fdl->WVal[idx], rate);

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		fdl->WeightDiff[fdl->ytail].YpointDiff = Vn;
	#else
		Vn += Scaling3(fdl->WVal[idx], fdl->WeightY-256, factor);
	#endif
#endif

//	if(rate==256) Vn = CutVal(fdl, Vn);
	fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead] - Vn;
	//DumpDebugStringCMD("%s y[%d, %d] -256Vn-: %d, %d<=Y*-256\n", op_str[fdl->op], fdl->yhead, fdl->ytail, Vn, fdl->Ypoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXWnA(pFdlRasterData fdl)
{
	DT32_int idx, factor, Vn;

	idx = fdl->op - XW0A;
	factor = ReadStrShort(fdl);
	Vn = fdl->WVal[idx];

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		fdl->WeightDiff[fdl->xtail].XpointDiff = -Vn;
	#else
		Vn += Scaling3(fdl->HVal[idx], fdl->WeightX-256, factor);
	#endif
#endif

	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] + CutVal(fdl, Vn);
	//DumpDebugStringCMD("%s x[%d, %d] -256Vn+: %d, %d<=X*-256\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Xpoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXWnS(pFdlRasterData fdl)
{
	DT32_int idx, factor, Vn;

	idx = fdl->op - XW0S;
	factor = ReadStrShort(fdl);
	Vn = fdl->HVal[idx];

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		fdl->WeightDiff[fdl->xtail].XpointDiff = Vn;
	#else
		Vn += Scaling3(fdl->HVal[idx], fdl->WeightX-256, factor);
	#endif
#endif

	fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] - CutVal(fdl, Vn);
	//DumpDebugStringCMD("%s x[%d, %d] -256Vn-: %d, %d<=X*-256\n", op_str[fdl->op], fdl->xhead, fdl->xtail, Vn, fdl->Xpoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpYWnA(pFdlRasterData fdl)
{
	DT32_int idx, factor, Vn;

	idx = fdl->op - YW0A;
	factor = ReadStrShort(fdl);
	Vn = fdl->WVal[idx];

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		fdl->WeightDiff[fdl->ytail].YpointDiff = -Vn;
	#else
		Vn += Scaling3(fdl->WVal[idx], fdl->WeightY-256, factor);
	#endif
#endif

	fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead] + CutVal(fdl, Vn);
	//DumpDebugStringCMD("%s y[%d, %d] -256Vn+: %d, %d<=Y*-256\n", op_str[fdl->op], fdl->yhead, fdl->ytail, Vn, fdl->Ypoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpYWnS(pFdlRasterData fdl)
{
	DT32_int idx, factor, Vn;

	idx = fdl->op - YW0S;
	factor = ReadStrShort(fdl);
	Vn = fdl->WVal[idx];

#ifdef FDL_WEIGHT
	#ifdef FDL_CACHE_WEIGHT
		fdl->WeightDiff[fdl->ytail].YpointDiff = Vn;
	#else
		Vn += Scaling3(fdl->WVal[idx], fdl->WeightY-256, factor);
	#endif
#endif

	fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead] - CutVal(fdl, Vn);
	//DumpDebugStringCMD("%s y[%d, %d] -256Vn-: %d, %d<=T*-256\n", op_str[fdl->op], fdl->yhead, fdl->ytail, Vn, fdl->Ypoint[fdl->xtail]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWSTOR(pFdlRasterData fdl)
{
	Get_WW_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	//DumpDebugStringCMD("%s x[%d, %d] (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->Xpoint[fdl->xhead], fdl->Ypoint[fdl->xhead]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNSTOR(pFdlRasterData fdl)
{
	Get_MN_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	//DumpDebugStringCMD("%s x[%d, %d] (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->Xpoint[fdl->xhead], fdl->Ypoint[fdl->xhead]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNSx00(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==MNSL00;
	Get_MN_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	Get_MN_Point(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
	fdl->isCurve = 0;
	//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNSx10(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==MNSL10;
	Get_MN_Point(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 0;
	//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op],fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail,  fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNCx00(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==MNCL00;
	mncnt = ReadStrShort(fdl) - 1;
	Get_MN_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	do
	{
		Get_MN_Point(fdl, &fdl->sx2, &fdl->sy2);
		Get_MN_Point(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
		mncnt -= 2;
		if(mncnt<=0) break;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->Xpoint[fdl->xtail] = fdl->sx3;
	fdl->Ypoint[fdl->ytail] = fdl->sy3;
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNCx10(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==MNCL10;
	mncnt = ReadStrShort(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	do
	{
		Get_MN_Point(fdl, &fdl->sx2, &fdl->sy2);
		Get_MN_Point(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
		mncnt -= 2;
		if(mncnt<=0) break;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->Xpoint[fdl->xtail] = fdl->sx3;
	fdl->Ypoint[fdl->ytail] = fdl->sy3;
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNCx11(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==MNCL11;
	mncnt = ReadStrShort(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	do
	{
		Get_MN_Point(fdl, &fdl->sx2, &fdl->sy2);
		mncnt -= 2;
		if(mncnt<=0) break;
		Get_MN_Point(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
#ifdef FDL_CACHE_WEIGHT
	fdl->sx3x = fdl->WeightDiff[fdl->xtail].XpointDiff;
	fdl->sy3y = fdl->WeightDiff[fdl->xtail].YpointDiff;
#endif
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWSx00(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==WWSL00;
	Get_WW_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	Get_WW_Point(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
	//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	fdl->isCurve = 0;
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWSx10(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==WWSL10;
	Get_WW_Point(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->xtail];
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 0;
	//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWCx00(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==WWCL00;
	mncnt = ReadStrShort(fdl) - 1;
	Get_WW_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	do
	{
		Get_WW_Point(fdl, &fdl->sx2, &fdl->sy2);
		Get_WW_Point(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
		mncnt -= 2;
		if(mncnt<=0) break;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->Xpoint[fdl->xtail] = fdl->sx3;
	fdl->Ypoint[fdl->ytail] = fdl->sy3;
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWCx10(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==WWCL10;
	mncnt = ReadStrShort(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	do
	{
		Get_WW_Point(fdl, &fdl->sx2, &fdl->sy2);
		Get_WW_Point(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
		mncnt -= 2;
		if(mncnt<=0) break;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->Xpoint[fdl->xtail] = fdl->sx3;
	fdl->Ypoint[fdl->ytail] = fdl->sy3;
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWCx11(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==WWCL11;
	mncnt = ReadStrShort(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;

#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif

	do
	{
		Get_WW_Point(fdl, &fdl->sx2, &fdl->sy2);
		mncnt -= 2;
		if(mncnt<=0) break;
		Get_WW_Point(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;

#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
#ifdef FDL_CACHE_WEIGHT
	fdl->sx3x = fdl->WeightDiff[fdl->xtail].XpointDiff;
	fdl->sy3y = fdl->WeightDiff[fdl->xtail].YpointDiff;
#endif
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWSTORb(pFdlRasterData fdl)
{
	Get_WW_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
#ifdef FDL_CACHE_WEIGHT
	//DumpDebugStringCMD("%s [%d, %d] (%d, %d) (h%d, t%d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->Xpoint[fdl->xhead], fdl->Ypoint[fdl->xhead], fdl->WeightDiff[fdl->xhead].XpointDiff, fdl->WeightDiff[fdl->xtail].XpointDiff);
#else
	//DumpDebugStringCMD("%s [%d, %d] (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->Xpoint[fdl->xhead], fdl->Ypoint[fdl->xhead]);
#endif
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNSTORb(pFdlRasterData fdl)
{
	Get_MN_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	//DumpDebugStringCMD("%s [%d, %d] (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->Xpoint[fdl->xhead], fdl->Ypoint[fdl->xhead]);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNSx00b(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==MNSL00b;
	Get_MN_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	Get_MN_XY(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
	fdl->isCurve = 0;
	//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNSx10b(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==MNSL10b;
	Get_MN_XY(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 0;
	//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNCx00b(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==MNCL00b;
	//mncnt = ReadStrByte(fdl) - 1;
	mncnt = ReadStrByte(fdl);		mncnt -= 1;
	Get_MN_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	do
	{
		Get_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
		Get_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
		mncnt -= 2;
		if(mncnt<=0) break;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->Xpoint[fdl->xtail] = fdl->sx3;
	fdl->Ypoint[fdl->ytail] = fdl->sy3;
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNCx10b(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==MNCL10b;
	mncnt = ReadStrByte(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	do
	{
		Get_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
		Get_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
		mncnt -= 2;
		if(mncnt<=0) break;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->Xpoint[fdl->xtail] = fdl->sx3;
	fdl->Ypoint[fdl->ytail] = fdl->sy3;
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpMNCx11b(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==MNCL11b;
	mncnt = ReadStrByte(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	do
	{
		Get_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
		mncnt -= 2;
		if(mncnt<=0) break;
		Get_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
#ifdef FDL_CACHE_WEIGHT
	fdl->sx3x = fdl->WeightDiff[fdl->xtail].XpointDiff;
	fdl->sy3y = fdl->WeightDiff[fdl->xtail].YpointDiff;
#endif
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpLMCx11b(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;
#ifdef FDL_CACHE_WEIGHT
	DT32_long vnx, vny;
	FDL_WEIGHT_MODE_UNIT *wp_xhead, *wp_yhead, *wp_xtail, *wp_ytail;

	wp_xhead = fdl->WeightDiff + fdl->xhead;
	wp_yhead = fdl->WeightDiff + fdl->yhead;
	wp_xtail = fdl->WeightDiff + fdl->xtail;
	wp_ytail = fdl->WeightDiff + fdl->ytail;
#endif

	fdl->MNx1 = fdl->Xpoint[fdl->xhead];
	fdl->MNy1 = fdl->Ypoint[fdl->yhead];
	fdl->MNx2 = fdl->Xpoint[fdl->xtail];
	fdl->MNy2 = fdl->Ypoint[fdl->ytail];
	fdl->Diffx = fdl->MNx2 - fdl->MNx1;
	fdl->Diffy = fdl->MNy2 - fdl->MNy1;

	fdl->isLeft = fdl->op==LMCL11b;
	mncnt = ReadStrByte(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = wp_xhead->XpointDiff;
	fdl->sy1y = wp_yhead->YpointDiff;

	vnx = wp_xtail->XpointDiff - wp_xhead->XpointDiff;
	vny = wp_ytail->YpointDiff - wp_yhead->YpointDiff;
#endif

	do
	{
		Get_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
#ifdef FDL_CACHE_WEIGHT
		fdl->sx2x = ((fdl->WeightXDiff * vnx - fdl->WeightYDiff * vny) >> 8) + wp_xhead->XpointDiff;
		fdl->sy2y = ((fdl->WeightYDiff * vnx + fdl->WeightXDiff * vny) >> 8) + wp_yhead->YpointDiff;
#endif
		mncnt -= 2;
		if(mncnt<=0) break;
		Get_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
#ifdef FDL_CACHE_WEIGHT
		fdl->sx3x = ((fdl->WeightXDiff * vnx - fdl->WeightYDiff * vny) >> 8) + wp_xhead->XpointDiff;
		fdl->sy3y = ((fdl->WeightYDiff * vnx + fdl->WeightXDiff * vny) >> 8) + wp_yhead->YpointDiff;
#endif
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
	} while(1);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
#ifdef FDL_CACHE_WEIGHT
	fdl->sx3x = wp_xtail->XpointDiff;
	fdl->sy3y = wp_ytail->YpointDiff;
#endif
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXMCx11b(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;
#ifdef FDL_CACHE_WEIGHT
	DT32_long vnx, vny;
	FDL_WEIGHT_MODE_UNIT *wp_xhead, *wp_yhead, *wp_xtail, *wp_ytail;

	wp_xhead = fdl->WeightDiff + fdl->xhead;
	wp_yhead = fdl->WeightDiff + fdl->yhead;
	wp_xtail = fdl->WeightDiff + fdl->xtail;
	wp_ytail = fdl->WeightDiff + fdl->ytail;
#endif

	fdl->MNx1 = fdl->Xpoint[fdl->xhead];
	fdl->MNy1 = fdl->Ypoint[fdl->ytail];
	fdl->MNx2 = fdl->Xpoint[fdl->xtail];
	fdl->MNy2 = fdl->Ypoint[fdl->yhead];
	fdl->Diffx = fdl->MNx2 - fdl->MNx1;
	fdl->Diffy = fdl->MNy2 - fdl->MNy1;

	fdl->isLeft = fdl->op==XMCL11b;
	mncnt = ReadStrByte(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = wp_xhead->XpointDiff;
	fdl->sy1y = wp_yhead->YpointDiff;

	vnx = wp_xtail->XpointDiff - wp_xhead->XpointDiff;
	vny = wp_yhead->YpointDiff - wp_ytail->YpointDiff;
#endif

	do
	{
		Get_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
#ifdef FDL_CACHE_WEIGHT
		fdl->sx2x = ((fdl->WeightXDiff * vnx - fdl->WeightYDiff * vny) >> 8) + wp_xhead->XpointDiff;
		fdl->sy2y = ((fdl->WeightYDiff * vnx + fdl->WeightXDiff * vny) >> 8) + wp_yhead->YpointDiff;
#endif
		mncnt -= 2;
		if(mncnt<=0) break;
		Get_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
#ifdef FDL_CACHE_WEIGHT
		fdl->sx3x = ((fdl->WeightXDiff * vnx - fdl->WeightYDiff * vny) >> 8) + wp_xhead->XpointDiff;
		fdl->sy3y = ((fdl->WeightYDiff * vnx + fdl->WeightXDiff * vny) >> 8) + wp_yhead->YpointDiff;
#endif
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
#ifdef FDL_CACHE_WEIGHT
	fdl->sx3x = wp_xtail->XpointDiff;
	fdl->sy3y = wp_ytail->YpointDiff;
#endif
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWSx00b(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==WWSL00b;
	Get_WW_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	Get_WW_XY(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
	fdl->isCurve = 0;
	//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWSx10b(pFdlRasterData fdl)
{
	fdl->isLeft = fdl->op==WWSL10b;
	Get_WW_XY(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->xtail];
	fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 0;
	//DumpDebugStringCMD("%s x[%d, %d] y[%d, %d] (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail, fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWCx00b(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==WWCL00b;
	//mncnt = ReadStrByte(fdl) - 1;
	mncnt = ReadStrByte(fdl);	mncnt -= 1;
	Get_WW_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	//DumpDebugStringCMD("%s [%d, %d], [%d, %d]\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail);
	do
	{
		Get_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
		Get_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s [%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
		mncnt -= 2;
		if(mncnt<=0) break;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->Xpoint[fdl->xtail] = fdl->sx3;
	fdl->Ypoint[fdl->ytail] = fdl->sy3;
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWCx10b(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==WWCL10b;
	mncnt = ReadStrByte(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	//DumpDebugStringCMD("%s [%d, %d], [%d, %d]\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail);
	do
	{
		Get_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
		Get_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s [%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
		mncnt -= 2;
		if(mncnt<=0) break;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->Xpoint[fdl->xtail] = fdl->sx3;
	fdl->Ypoint[fdl->ytail] = fdl->sy3;
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpWWCx11b(pFdlRasterData fdl)
{
	DT32_int mncnt, x3buf, y3buf;

	fdl->isLeft = fdl->op==WWCL11b;
	mncnt = ReadStrByte(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;
#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = fdl->WeightDiff[fdl->xhead].XpointDiff;
	fdl->sy1y = fdl->WeightDiff[fdl->yhead].YpointDiff;
#endif
	//DumpDebugStringCMD("%s [%d, %d], [%d, %d]\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail);

	do
	{
		Get_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
		mncnt -= 2;
		if(mncnt<=0) break;
		Get_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s [%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
#ifdef FDL_CACHE_WEIGHT
	fdl->sx3x = fdl->WeightDiff[fdl->xtail].XpointDiff;
	fdl->sy3y = fdl->WeightDiff[fdl->xtail].YpointDiff;
#endif
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpLWCx11b(pFdlRasterData fdl)		// <==
{
	DT32_int mncnt, x3buf, y3buf;
#ifdef FDL_CACHE_WEIGHT
	DT32_long vnx, vny;
	FDL_WEIGHT_MODE_UNIT *wp_xhead, *wp_yhead, *wp_xtail, *wp_ytail;

	wp_xhead = fdl->WeightDiff + fdl->xhead;
	wp_yhead = fdl->WeightDiff + fdl->yhead;
	wp_xtail = fdl->WeightDiff + fdl->xtail;
	wp_ytail = fdl->WeightDiff + fdl->ytail;
#endif

	fdl->MNx1 = fdl->Xpoint[fdl->xhead];
	fdl->MNy1 = fdl->Ypoint[fdl->yhead];
	fdl->MNx2 = fdl->Xpoint[fdl->xtail];
	fdl->MNy2 = fdl->Ypoint[fdl->ytail];
	fdl->Diffx = fdl->MNx2 - fdl->MNx1;
	fdl->Diffy = fdl->MNy2 - fdl->MNy1;
	//DumpDebugStringCMD("%s [%d, %d], [%d, %d]\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail);

	fdl->isLeft = fdl->op==LWCL11b;
	mncnt = ReadStrByte(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;

#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = wp_xhead->XpointDiff;
	fdl->sy1y = wp_yhead->YpointDiff;

	vnx = wp_xtail->XpointDiff - wp_xhead->XpointDiff;
	vny = wp_ytail->YpointDiff - wp_yhead->YpointDiff;
#endif
	do
	{
		Get_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
#ifdef FDL_CACHE_WEIGHT
		fdl->sx2x = (fdl->WeightXDiff * vnx >> 8) + wp_yhead->XpointDiff;
		fdl->sy2y = (fdl->WeightYDiff * vny >> 8) + wp_yhead->YpointDiff;
#endif
		mncnt -= 2;
		if(mncnt<=0) break;
		Get_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
#ifdef FDL_CACHE_WEIGHT
		fdl->sx3x = (fdl->WeightXDiff * vnx >> 8) + wp_yhead->XpointDiff;
		fdl->sy3y = (fdl->WeightYDiff * vny >> 8) + wp_yhead->YpointDiff;
#endif
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		//DumpDebugStringCMD("%s [%d, %d] (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);
	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
#ifdef FDL_CACHE_WEIGHT
	fdl->sx3x = wp_xtail->XpointDiff;
	fdl->sy3y = wp_ytail->YpointDiff;
#endif
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpXWCx11b(pFdlRasterData fdl)			// <==
{
	DT32_int mncnt, x3buf, y3buf;
#ifdef FDL_CACHE_WEIGHT
	DT32_long vnx, vny;
	FDL_WEIGHT_MODE_UNIT *wp_xhead, *wp_yhead, *wp_xtail, *wp_ytail;

	wp_xhead = fdl->WeightDiff + fdl->xhead;
	wp_yhead = fdl->WeightDiff + fdl->yhead;
	wp_xtail = fdl->WeightDiff + fdl->xtail;
	wp_ytail = fdl->WeightDiff + fdl->ytail;
#endif

	fdl->MNx1 = fdl->Xpoint[fdl->xhead];
	fdl->MNy1 = fdl->Ypoint[fdl->ytail];
	fdl->MNx2 = fdl->Xpoint[fdl->xtail];
	fdl->MNy2 = fdl->Ypoint[fdl->yhead];
	fdl->Diffx = fdl->MNx2 - fdl->MNx1;
	fdl->Diffy = fdl->MNy2 - fdl->MNy1;
	//DumpDebugStringCMD("%s [%d, %d], [%d, %d]\n", op_str[fdl->op], fdl->xhead, fdl->xtail, fdl->yhead, fdl->ytail);

	fdl->isLeft = fdl->op==XWCL11b;
	mncnt = ReadStrByte(fdl);
	fdl->sx1 = fdl->Xpoint[fdl->xhead];
	fdl->sy1 = fdl->Ypoint[fdl->yhead];
	fdl->isCurve = 1;

#ifdef FDL_CACHE_WEIGHT
	fdl->sx1x = wp_xhead->XpointDiff;
	fdl->sy1y = wp_yhead->YpointDiff;

	vnx = wp_xtail->XpointDiff - wp_xhead->XpointDiff;
	vny = wp_yhead->YpointDiff - wp_ytail->YpointDiff;
#endif
	do
	{
		Get_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
#ifdef FDL_CACHE_WEIGHT
		fdl->sx2x = (fdl->WeightXDiff * vnx >> 8) + wp_xhead->XpointDiff;
		fdl->sy2y = (fdl->WeightYDiff * vny >> 8) + wp_ytail->YpointDiff;
#endif
		mncnt -= 2;
		if(mncnt<=0) break;
		Get_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
#ifdef FDL_CACHE_WEIGHT
		fdl->sx3x = (fdl->WeightXDiff * vnx >> 8) + wp_xhead->XpointDiff;
		fdl->sy3y = (fdl->WeightYDiff * vny >> 8) + wp_ytail->YpointDiff;
#endif
		//DumpDebugStringCMD("%s (%d, %d), (%d, %d), (%d, %d)\n", op_str[fdl->op], fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
		x3buf = fdl->sx3;
		y3buf = fdl->sy3;
		PreCur(fdl);
		fdl->sx3 = fdl->sx1 = x3buf;
		fdl->sy3 = fdl->sy1 = y3buf;
#ifdef FDL_CACHE_WEIGHT
		fdl->sx1x = fdl->sx3x;
		fdl->sy1y = fdl->sy3y;
#endif
	} while(1);

	fdl->sx3 = fdl->Xpoint[fdl->xtail];
	fdl->sy3 = fdl->Ypoint[fdl->ytail];
#ifdef FDL_CACHE_WEIGHT
	fdl->sx3x = wp_xtail->XpointDiff;
	fdl->sy3y = wp_ytail->YpointDiff;
#endif
	//DumpDebugStringCMD("    (%d, %d), (%d, %d), (%d, %d)\n", fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3);
	PreCur(fdl);
	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpENDSUBb(pFdlRasterData fdl)
{
	fdl->sdatacnt++;
	fdl->sdataofs--;
	fdl->sx1 = -1;
	//DumpDebugStringCMD("%s %d\n", op_str[fdl->op], fdl->sx1);
	PreCur(fdl);
	return(FDL_END_OF_SUB);
}
/*---------------------------------------------------------------------------*/
DT32_int OpSWFX(pFdlRasterData fdl)
{
#ifdef FDL_WEIGHT
	if(fdl->WeightX0 != 256)
		fdl->WeightX = (unsigned)(((DT32_long)fdl->WeightX0 * fdl->Value[fdl->xhead]) >> 7);
	//DumpDebugStringCMD("%s [%d, %d] X0: %d, X: %d <=\n", op_str[fdl->op], fdl->WeightX0, fdl->WeightX);
#endif

	return(0);
}
/*---------------------------------------------------------------------------*/
DT32_int OpSWFY(pFdlRasterData fdl)
{
#ifdef FDL_WEIGHT
	if(fdl->WeightY0 != 256)
		fdl->WeightY = (unsigned)(((DT32_long)fdl->WeightY0 * fdl->Value[fdl->xhead]) >> 7);
	//DumpDebugStringCMD("%s [%d, %d] Y0: %d, Y: %d <=\n", op_str[fdl->op], fdl->WeightY0, fdl->WeightY);
#endif

	return(0);
}
/*---------------------------------------------------------------------------*/
DT_void Get_WW_Point(pFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval)
{
	*Xval = fdl->MNx1 + Scaling(ReadStrShort(fdl), fdl->Diffx);
	*Yval = fdl->MNy1 + Scaling(ReadStrShort(fdl), fdl->Diffy);
}
/*---------------------------------------------------------------------------*/
DT_void Get_MN_Point(pFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval)
{
	DT32_int mx = ReadStrShort(fdl);
	DT32_int ny = ReadStrShort(fdl);

	*Xval = fdl->MNx1 + (((DT32_long)mx * fdl->Diffx - (DT32_long)ny * fdl->Diffy) / 256);
	*Yval = fdl->MNy1 + (((DT32_long)ny * fdl->Diffx + (DT32_long)mx * fdl->Diffy) / 256);
}
/*---------------------------------------------------------------------------*/
DT_void Get_WW_XY(pFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval)
{
	DT32_int x, y;

	x = ReadStrByte(fdl);
	y = ReadStrByte(fdl);

	if(x==255) x = 256;
	if(y==255) y = 256;

#ifdef FDL_WEIGHT
	fdl->WeightXDiff = x;
	fdl->WeightYDiff = y;
	*Xval = fdl->MNx1 + Scaling(x, fdl->Diffx);
	*Yval = fdl->MNy1 + Scaling(y, fdl->Diffy);
#else
	*Xval = fdl->MNx1 + Scaling(x, fdl->Diffx);
	*Yval = fdl->MNy1 + Scaling(y, fdl->Diffy);
#endif
}
/*---------------------------------------------------------------------------*/
DT_void Get_MN_XY(pFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval)
{
	DT32_int mx, ny;

	mx = ReadStrByte(fdl);
	ny = ReadStrByte(fdl);

	if(mx==255)	mx = 256;
	if(ny==255)	ny = 256;

#ifdef FDL_WEIGHT
	fdl->WeightXDiff = mx;
	fdl->WeightYDiff = ny;
	*Xval = fdl->MNx1 + (((DT32_long)mx * fdl->Diffx - (DT32_long)ny * fdl->Diffy) / 256);
	*Yval = fdl->MNy1 + (((DT32_long)ny * fdl->Diffx + (DT32_long)mx * fdl->Diffy) / 256);
#else
	*Xval = fdl->MNx1 + (((DT32_long)mx * fdl->Diffx - (DT32_long)ny * fdl->Diffy) / 256);
	*Yval = fdl->MNy1 + (((DT32_long)ny * fdl->Diffx + (DT32_long)mx * fdl->Diffy) / 256);
#endif
}
/*---------------------------------------------------------------------------*/
DT_void PreCur(pFdlRasterData fdl)
{
	DT32_int ofs;

#ifndef FDL_CACHE_WEIGHT
	if(!fdl->S128)
	{
		fdl->sx1 = ScaleX(fdl, fdl->sx1);
		fdl->sx2 = ScaleX(fdl, fdl->sx2);
		fdl->sx3 = ScaleX(fdl, fdl->sx3);

		fdl->sy1 = ScaleY(fdl, fdl->sy1);
		fdl->sy2 = ScaleY(fdl, fdl->sy2);
		fdl->sy3 = ScaleY(fdl, fdl->sy3);
	}
#endif
	/* 2007-12-07 Radical (Shift for Symbol in Radical) */
	if(fdl->shiftx != 0)
	{
		ofs = fdl->shiftx << fdl->Frac2;

		fdl->sy1 += ofs;
		fdl->sy2 += ofs;
		fdl->sy3 += ofs;
	}

	if(fdl->shifty != 0)
	{
		ofs = fdl->shifty << fdl->Frac2;

		fdl->sx1 += ofs;
		fdl->sx2 += ofs;
		fdl->sx3 += ofs;
	}
	/* 2007-12-07 Radical */
#ifdef ENABLE_FDL_MODE_RASTER
	if(fdl->Mode == FDL_MODE_RASTER)
	{
		Scurve(fdl);
	} else 
#endif	
	if(fdl->Mode == FDL_MODE_RASTER2)
	{
		if(fdl->hint > FDL_NO_HINT)
			SCurve3(fdl);
		else SCurve2(fdl);
	} else
	{
		Cpoint(fdl);
	}
}
/*---------------------------------------------------------------------------*/
DT_void PreLastSCurve(pFdlRasterData fdl)
{
	if(fdl->Mode == FDL_MODE_RASTER)
	{
		*fdl->Left_Ptr  = (DT16_short)(fdl->lywait >> fdl->Frac2);
		*fdl->Right_Ptr = (DT16_short)(fdl->rywait >> fdl->Frac2);

		fdl->Left_Ptr++;
		fdl->Right_Ptr++;
	}
}
/*---------------------------------------------------------------------------*/
#ifdef ENABLE_FDL_MODE_RASTER
DT_void Scurve(pFdlRasterData fdl)
{
	DT32_long tmp, nextx, *p;

	p = fdl->Stack;
	nextx = ItVal(fdl, fdl->sx1) + fdl->Flat;
	cutxy(fdl, fdl->sx1, fdl->sy1);

	do
	{
		tmp = ItVal(fdl, fdl->sx3) - nextx;

		if(tmp > 0)
		{
			*p = fdl->sx3;
			p++;

			*p = tmp = (fdl->sx3 + fdl->sx2) / 2;
			p++;

			fdl->sx2 = (fdl->sx2 + fdl->sx1) / 2;
			fdl->sx3 = (tmp + fdl->sx2) / 2;

			*p = fdl->sy3;
			p++;

			*p = tmp = (fdl->sy3 + fdl->sy2) / 2;
			p++;

			fdl->sy2 = (fdl->sy2 + fdl->sy1) / 2;
			fdl->sy3 = (tmp + fdl->sy2) / 2;
		} else
		{
			if(tmp == 0)
			{
				cutxy(fdl, fdl->sx3, fdl->sy3);
				nextx += fdl->Flat;
				fdl->sx1 = fdl->sx3;
				fdl->sy1 = fdl->sy3;
			}
			if(p-fdl->Stack > 0)
			{
				p--, fdl->sy2 = *p;
				p--, fdl->sy3 = *p;
				p--, fdl->sx2 = *p;
				p--, fdl->sx3 = *p;
			} else break;
		}
	} while(1);
}
#endif
/*---------------------------------------------------------------------------*/
DT_void cutxy(pFdlRasterData fdl, DT32_int x, DT32_int y)
{
	DT32_int tmp;

	tmp = CutVal(fdl, x);

	if(fdl->isLeft)
	{
		if(fdl->LeftWait)
		{
			if(CutVal(fdl, fdl->lxwait) >= tmp)
			{
				if(y<fdl->lywait)
				{
					fdl->lxwait = x;
					fdl->lywait = y;
				}
			} else
			{
				*fdl->Left_Ptr = (DT16_short)(fdl->lywait >> fdl->Frac2);
				fdl->Left_Ptr++;
				fdl->lxwait = x;
				fdl->lywait = y;
			}
		} else
		{
			fdl->LeftWait = 1;
			fdl->lxwait = x;
			fdl->lywait = y;
			if(fdl->FirstX < 0)	fdl->FirstX = fdl->lxwait >> fdl->Frac2;
		}
	} else
	{
		if(fdl->RightWait)
		{
			if(CutVal(fdl, fdl->rxwait) >= tmp)
			{
				if(y > fdl->rywait)
				{
					fdl->rxwait = x;
					fdl->rywait = y;
				}
			} else
			{
				*fdl->Right_Ptr = (DT16_short)(fdl->rywait >> fdl->Frac2);
				fdl->Right_Ptr++;
				fdl->rxwait = x;
				fdl->rywait = y;
			}
		} else
		{
			fdl->RightWait = 1;
			fdl->rxwait = x;
			fdl->rywait = y;
			if(fdl->FirstX<0) fdl->FirstX = fdl->rxwait >> fdl->Frac2;
		}
	}
}
/*---------------------------------------------------------------------------*/
DT_void Cpoint(pFdlRasterData fdl)
{
	if(fdl->isLeft)
	{
		*fdl->Left_Ptr = (DT16_short)(fdl->sy1 >> fdl->Frac2), fdl->Left_Ptr++;
		*fdl->Left_Ptr = (DT16_short)(fdl->sx1 >> fdl->Frac2), fdl->Left_Ptr++;
		*fdl->Left_Ptr = (DT16_short)(fdl->sy2 >> fdl->Frac2), fdl->Left_Ptr++;
		*fdl->Left_Ptr = (DT16_short)(fdl->sx2 >> fdl->Frac2), fdl->Left_Ptr++;
		*fdl->Left_Ptr = (DT16_short)(fdl->sy3 >> fdl->Frac2), fdl->Left_Ptr++;
		*fdl->Left_Ptr = (DT16_short)(fdl->sx3 >> fdl->Frac2), fdl->Left_Ptr++;
	} else
	{
		*fdl->Right_Ptr = (DT16_short)(fdl->sy1 >> fdl->Frac2), fdl->Right_Ptr++;
		*fdl->Right_Ptr = (DT16_short)(fdl->sx1 >> fdl->Frac2), fdl->Right_Ptr++;
		*fdl->Right_Ptr = (DT16_short)(fdl->sy2 >> fdl->Frac2), fdl->Right_Ptr++;
		*fdl->Right_Ptr = (DT16_short)(fdl->sx2 >> fdl->Frac2), fdl->Right_Ptr++;
		*fdl->Right_Ptr = (DT16_short)(fdl->sy3 >> fdl->Frac2), fdl->Right_Ptr++;
		*fdl->Right_Ptr = (DT16_short)(fdl->sx3 >> fdl->Frac2), fdl->Right_Ptr++;
	}
}
/*---------------------------------------------------------------------------*/
DT_void Make_Default_Value(pFdlRasterData fdl)
{
	DT32_int  i, val;

	if(fdl->S128)
	{
		for(i=0; i<8; i++)
		{
			val = fdl->Value[i] << fdl->Frac2;
			fdl->HVal[i] = Scaling(val, fdl->ysize2);
			fdl->WVal[i] = Scaling(val, fdl->xsize2);
		}
	} else
	{
		for(i=0; i<8; i++)
		{
			val = fdl->Value[i] << fdl->Frac2;
			fdl->HVal[i] = val;
			fdl->WVal[i] = val;
		}
	}// end if
}
/*---------------------------------------------------------------------------*/
DT_void Adjust(pFdlRasterData fdl)
{
	DT16_short *lp, *rp;
	DT32_int i;

	lp = fdl->LeftBuf;
	rp = fdl->RightBuf;

	// ===================================================== Alan.
	if(fdl->RasterCnt > 0)
	{
#ifdef OPTIMIZE_CHECK
		DT16_short temp;
		if(*lp > *rp)
		{
			//DumpDebugString("OPTIMIZE_CHECK fail 1\n");
			temp = *lp;
			*lp  = *rp;
			*rp  = temp;
		}
#endif
		lp++;
		rp++;

		for(i=1; i < fdl->RasterCnt; i++,lp++,rp++)
		{
#ifdef OPTIMIZE_CHECK
			// exchange left/right point
			if(*lp > *rp)
			{
				//DumpDebugString("OPTIMIZE_CHECK fail 2\n");
				temp = *lp;
				*lp  = *rp;
				*rp  = temp;
			}
#endif
			// connect dropout scan line
			//if(i > 0)
			{

				if(*lp > *(rp-1))
					*lp = *(rp-1);
				else if(*rp < *(lp-1))
					*rp = *(lp-1);
			}
		}// end for
	}// end if
}
/*---------------------------------------------------------------------------*/
static const DT8_BYTE BitMask1[8] = {0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01};
static const DT8_BYTE BitMask2[8] = {0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff};
static const DT8_BYTE BitMask0[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

DT_void DoDrawLine(pFdlRasterData fdl, DT32_int y, DT32_int xl, DT32_int xr)
{
	DT32_int start, last, cnt, x, y2, yt, yb;
	DT8_BYTE *p0, *p, mask, b;
	DT32_int i;

	if(!fdl->rot)
	{  /* Draw Horz Line */
		y  += fdl->yorg;
		xl += fdl->xorg;
		xr += fdl->xorg;

		start = xl >> 3;
		last  = xr >> 3;
		cnt = last - start;

		/* Calculate first byte position */
		p0= (DT8_BYTE*)(fdl->bmp + y * fdl->bmpw);
		p = (DT8_BYTE*)(fdl->bmp + y * fdl->bmpw + start);

		/* Fill line */
		if(cnt == 0)
		{
			mask = (DT8_BYTE)(BitMask1[xl & 0x07] & BitMask2[xr & 0x07]);
			*p = *p | mask;
		} else
		{
			b = *p;
			*p = (DT8_BYTE)(b | BitMask1[xl & 0x07]);
			p++;

			for(i=0; i<cnt-1; i++,p++)
				*p = 0xff;

			b = *p;
			if(p - p0 < fdl->bmpw)							// Jacky_20110509
				*p = (DT8_BYTE)(b | BitMask2[xr & 0x07]);
		}

		/* Calculate font body range */
		if(y < fdl->fontbox.top)	fdl->fontbox.top    = y;
		if(y > fdl->fontbox.bottom)	fdl->fontbox.bottom = y;

		if(xl < fdl->fontbox.left) fdl->fontbox.left   = xl;
		if(xr > fdl->fontbox.right)	fdl->fontbox.right  = xr;
	} else
	{  /* Draw Vert Line */
		x  = fdl->xorg + (fdl->ysize - y - 1);
		yt = fdl->yorg + xl;
		yb = fdl->yorg + xr;

		/* Calculate first byte position */
		p = (DT8_BYTE*)(fdl->bmp + yt * fdl->bmpw + (x >> 3));
		mask = BitMask0[x & 0x07];

		/* Fill line */
		for(y2 = yt; y2 <= yb; y2++)
		{
			*p = *p | mask;
			p += fdl->bmpw;
		}

		/* Calculate font body range */
		if(yt < fdl->fontbox.top)	 fdl->fontbox.top    = yt;
		if(yb > fdl->fontbox.bottom) fdl->fontbox.bottom = yb;

		if(x < fdl->fontbox.left) fdl->fontbox.left   = x;
		if(x > fdl->fontbox.right) fdl->fontbox.right  = x;
	}
}
/*---------------------------------------------------------------------------*/
DT_void DoDrawDot(pFdlRasterData fdl, DT32_int x, DT32_int y, DT32_int clr)
{
	DT32_int x2, y2;
	DT8_BYTE *p, mask;

	/* Calculate Dot Coordinate */
	if(!fdl->rot)
	{
		x2 = fdl->xorg + x;
		y2 = fdl->yorg + y;
	} else
	{
		x2 = fdl->xorg + (fdl->ysize - y - 1);
		y2 = fdl->yorg + x;
	}

	/* Set Dot */
	p = (DT8_BYTE*)(fdl->bmp + y2 * fdl->bmpw + (x2 >> 3));
	if(!clr)
	{
		mask = (DT8_BYTE)BitMask0[x2 & 0x07];
		*p = *p | mask;
	} else
	{
		mask = ~(DT8_BYTE)BitMask0[x2 & 0x07];
		*p = *p & mask;
	}

	/* Calculate font body range */
	if(!clr)
	{
		if(x2 < fdl->fontbox.left) fdl->fontbox.left   = x2;
		if(x2 > fdl->fontbox.right)	fdl->fontbox.right  = x2;

		if(y2 < fdl->fontbox.top)	 fdl->fontbox.top    = y2;
		if(y2 > fdl->fontbox.bottom) fdl->fontbox.bottom = y2;
	}
}
/*---------------------------------------------------------------------------*/
DT_void DoClearLine(pFdlRasterData fdl, DT32_int y, DT32_int xl, DT32_int xr)
{
	DT32_int start, last, cnt, x, yt, yb;
	DT8_BYTE *p, mask, b;
	DT32_int i;

	if(!fdl->rot)
	{  /* Clear Horz Line */
		y  += fdl->yorg;
		xl += fdl->xorg;
		xr += fdl->xorg;

		start = xl >> 3;
		last  = xr >> 3;
		cnt = last - start;

		/* Calculate first byte position */
		p = (DT8_BYTE*)(fdl->bmp + y * fdl->bmpw + start);

		/* Clear line */
		if(cnt == 0)
		{
			mask = (DT8_BYTE)(~(BitMask1[xl & 0x07] & BitMask2[xr & 0x07]));
			*p = *p & mask;
		} else
		{
			b = *p;
			mask = (DT8_BYTE)(~BitMask1[xl & 0x07]);
			*p = (DT8_BYTE)(b & mask);
			p++;

			for(i=0; i<cnt-1; i++,p++)
				*p = 0x00;

			b = *p;
			mask = (DT8_BYTE)(~BitMask2[xr & 0x07]);
			*p = (DT8_BYTE)(b & mask);
		}
	} else
	{  /* Clear Vert Line */
		x  = fdl->xorg + (fdl->ysize - y - 1);
		yt = fdl->yorg + xl;
		yb = fdl->yorg + xr;

		/* Calculate first byte position */
		p = (DT8_BYTE*)(fdl->bmp + yt * fdl->bmpw + x / 8);
		mask = ~BitMask0[x % 8];

		/* Clear line */
		for(y = yt; y <= yb; y++)
		{
			*p = *p & mask;
			p += fdl->bmpw;
		}
	}
}

/*==========================================================================*/
/* New Scaline Generator                                                    */
/*==========================================================================*/
static DT_void AddPt2ScanL(pFdlRasterData fdl, DT32_long x, DT32_long y)
{
//	if(y < fdl->NsTop)					// Do this at AddPt2Scan2()
//		fdl->NsTop  = y;

//	if(y > fdl->NsDownL)				// Do this at DoDeLine
//		fdl->NsDownL = y;

	DT16_short *p = fdl->Left_Ptr  + (y);
	if(x <= *p)
		*p = (DT16_short)x;
}// end AddPt2ScanL

static DT_void AddPt2ScanR(pFdlRasterData fdl, DT32_long x, DT32_long y)
{
//	if(y < fdl->NsTop)					// Do this at AddPt2Scan2()
//		fdl->NsTop  = y;

//	if(y > fdl->NsDownR)				// Do this at DoDeLine
//		fdl->NsDownR = y;

	DT16_short *p = fdl->Right_Ptr + (y);
	if(x >= *p)
		*p = (DT16_short)x;
}// end AddPt2ScanR

static DT_void deLine(pFdlRasterData fdl, DT32_long x1, DT32_long y1, DT32_long x2, DT32_long y2)
{
	if(y1 > y2){
		DoDeLine(fdl, x2, y2, x1, y1);
	}else{
		DoDeLine(fdl, x1, y1, x2, y2);
	}
}
/*---------------------------------------------------------------------------*/
static DT_void DoDeLine(pFdlRasterData fdl, DT32_long x1, DT32_long y1, DT32_long x2, DT32_long y2)
{
	DT32_long x, y, dx, dy;
	DT32_long ddy;
	DT32_long IncInt, IncFrac, OneInt, OneFrac;
	DT32_long startY, endY;
	DT32_long m1, m2;
//DumpDebugString("DoDeLine (%d, %d), (%d, %d)\n", x1, y1, x2, y2);
	dx = x2 - x1;
	dy = y2 - y1;

	/* Horz. line */
	if(dy == 0)
	{
		y = y1 >> fdl->Frac2;
		AddPt2Scan2(fdl, x1 >> fdl->Frac2, y);
		if(dx != 0)	AddPt2Scan2(fdl, x2 >> fdl->Frac2, y);
		return;
	}

	// Scanline Range
//	m1 = y1 % fdl->Frac;
	m1 = y1 & fdl->FracMod;
	startY = (m1 <= fdl->NsFrac2) ? (y1 - m1 + fdl->NsFrac2) : (y1 - m1 + fdl->NsFrac2 + fdl->Frac);

//	m2 = y2 % fdl->Frac;
	m2 = y2 & fdl->FracMod;
	endY = (m2 < fdl->NsFrac2) ? (y2 - m2 - fdl->NsFrac2) : (y2 - m2 + fdl->NsFrac2);
	if(endY == y2) endY -= fdl->Frac;

	// First Scanline X Increment
	ddy = (DT32_long)(startY - y1) * dx;
	IncInt  = ddy / dy;
//	IncFrac = ddy % dy;
	IncFrac = ddy - IncInt*dy;

	// Next Scanline X Increment (=1)
	ddy = (DT32_long)(dx << fdl->Frac2);
	OneInt  = ddy / dy;
//	OneFrac = ddy % dy;
	OneFrac = ddy - OneInt*dy;

	// Scanline Y Coordinate
	y = startY >> fdl->Frac2;
	endY = endY >> fdl->Frac2;

	if(y < 0)
		y = 0;
	if(endY > fdl->ysize)
		endY = fdl->ysize;

	if(fdl->isLeft)
	{
		if(endY > fdl->NsDownL)
			fdl->NsDownL = endY;
	} else
	{
		if(endY > fdl->NsDownR)
			fdl->NsDownR = endY;
	}// end if

	y = y - fdl->NsTop;
	if(fdl->isLeft)
	{// block
		DT32_int k = endY - fdl->NsTop;
		if(IncFrac + OneFrac*(k-y) > 0)
		{
			while(y <= k)
			{	// Output Scanline
				x = (x1 + IncInt) >> fdl->Frac2;
//				AddPt2ScanPtMacro(fdl, x, y);
				if(x <= fdl->Left_Ptr[y])
					fdl->Left_Ptr[y] = (DT16_short)x;
				y++;

				// Next Scanline X Increament
				IncInt  += OneInt;
				IncFrac += OneFrac;
				if(IncFrac >= dy)
				{
					IncInt++;
					IncFrac -= dy;
				}// end if
			}// end while
		} else
		{
			if(OneInt == 0)
			{
				x = (x1) >> fdl->Frac2;
				while(y <= k)
				{	// Output Scanline
					if(x <= fdl->Left_Ptr[y])
						fdl->Left_Ptr[y] = (DT16_short)x;
					y++;
				}// end while
			} else
			{
				while(y <= k)
				{	// Output Scanline
					x = (x1) >> fdl->Frac2;
					//				AddPt2ScanPtMacro(fdl, x, y);
					if(x <= fdl->Left_Ptr[y])
						fdl->Left_Ptr[y] = (DT16_short)x;
					y++;

					// Next Scanline X Increament
					x1  += OneInt;
				}// end while
			}// end if
		}// end if
	} else
	{
		DT32_int k = endY - fdl->NsTop;
		if(IncFrac + OneFrac*(k-y) > 0)
		{
			while(y <= k)
			{	// Output Scanline
				x = (x1 + IncInt) >> fdl->Frac2;
//				AddPt2ScanPtMacro(fdl, x, y);
				if(x >= fdl->Right_Ptr[y])
					fdl->Right_Ptr[y] = (DT16_short)x;
				y++;

				// Next Scanline X Increament
				IncInt  += OneInt;
				IncFrac += OneFrac;
				if(IncFrac >= dy)
				{
					IncInt++;
					IncFrac -= dy;
				}// end if
			}// end while
		} else
		{
			if(OneInt == 0)
			{
				x = (x1) >> fdl->Frac2;
				while(y <= k)
				{	// Output Scanline
					if(x >= fdl->Right_Ptr[y])
						fdl->Right_Ptr[y] = (DT16_short)x;
					y++;
				}// end while
			} else
			{
				while(y <= k)
				{	// Output Scanline
					x = (x1) >> fdl->Frac2;
					//				AddPt2ScanPtMacro(fdl, x, y);
					if(x >= fdl->Right_Ptr[y])
						fdl->Right_Ptr[y] = (DT16_short)x;
					y++;

					// Next Scanline X Increament
					x1  += OneInt;
				}// end while
			}// end if
		}// end if
	}// end if
}
/*---------------------------------------------------------------------------*/
static DT_void AddPt2Scan2(pFdlRasterData fdl, DT32_long x, DT32_long y)		 // This doesn't check bound
{
	DT16_short *p;

	// Check point outside font box
//	if(y < 0 || y >= fdl->ysize)
//		return;

/*	if(x < 0)
	{
		x = 0;
	}else if(x >= fdl->xsize)
	{
		x = fdl->xsize - 1;
	}// end if
*/
	if(y < fdl->NsTop)
		fdl->NsTop  = y;

	if(fdl->isLeft)
	{
		if(y > fdl->NsDownL)
			fdl->NsDownL = y;

		p = fdl->Left_Ptr  + (y - fdl->NsTop);
		if(x < *p)
			*p = (DT16_short)x;
	} else
	{
		if(y > fdl->NsDownR)
			fdl->NsDownR = y;

		p = fdl->Right_Ptr + (y - fdl->NsTop);
		if(x > *p)
			*p = (DT16_short)x;
	}// end if
}// end AddPt2Scan2

/*---------------------------------------------------------------------------*/
#ifdef FDL_OUTLINE_MODE
static DT_void SCurve3(pFdlRasterData fdl)
{
	PATH_UNIT *p = fdl->path_buf + fdl->path_num;

#ifdef FDL_LIMIT_PATH_NUM_BY_MAX_STACK
	if(fdl->path_num >= sizeof(fdl->path_buf)/sizeof(fdl->path_buf[0]))
		return;
#endif

//	/* 2011-08-31: Start *//* for symbol fonts that had no lines but only curves. */
//	if (fdl->isCurve)
//	{
//		if ((fdl->sx2 == fdl->sx1) && (fdl->sy2 == fdl->sy1) ||
//			(fdl->sx2 == fdl->sx3) && (fdl->sy2 == fdl->sy3))      
//			fdl->isCurve = 0;
//		else
//			fdl->isCurve = 1;
//	}
//	else
//		fdl->isCurve = 0;
//	/* 2011-08-31: End */

//	p->strid = fdl->strid;
	p->strorder = fdl->stridcnt;
	p->subidx = fdl->subidx;
	p->relation = -1;
	p->stick_relation_path = -1;
	p->stick_stroke = -1;
	if(fdl->isCurve)
		p->lock = FDL_PATH_IsCurve;
	else p->lock = 0;
	if(fdl->isLeft)
		p->lock |= FDL_PATH_IsLeft;
	p->sx1 = fdl->sy1;
	p->sy1 = fdl->sx1;

	p->sx2 = fdl->sy2;
	p->sy2 = fdl->sx2;

	p->sx3 = fdl->sy3;
	p->sy3 = fdl->sx3;

	// =========================================================
#ifdef FDL_CACHE_WEIGHT
	p->sx1x = fdl->sy1y;
	p->sy1y = fdl->sx1x;

	p->sx2x = fdl->sy2y;
	p->sy2y = fdl->sx2x;

	p->sx3x = fdl->sy3y;
	p->sy3y = fdl->sx3x;
#endif
	// =========================================================

	if(p->sx1 <= p->sx3)
	{
		p->sx01 = &(p->sx1);
		p->sx03 = &(p->sx3);
	} else
	{
		p->sx01 = &(p->sx3);
		p->sx03 = &(p->sx1);
	}// end if


	if(p->sy1 <= p->sy3)
	{
		p->sy01 = &(p->sy1);
		p->sy03 = &(p->sy3);
	} else
	{
		p->sy01 = &(p->sy3);
		p->sy03 = &(p->sy1);
	}// end if

	if((p->lock & FDL_PATH_IsCurve) == 0)
	{
		if(p->sx1 == p->sx3)
			p->dir = FDL_PATH_VERT;
		else if(p->sy1 == p->sy3)
			p->dir = FDL_PATH_HORZ;
		else p->dir	= FDL_PATH_NONE;
	} else p->dir = FDL_PATH_NONE;

#ifdef LIST_POINTS
#ifdef FDL_CACHE_WEIGHT
{
//DT32_int W=		fdl->WeightRX;
//	DumpDebugString("      ==> Point%d %s (%d, %d),(%d, %d),(%d, %d) =>\n          (%d, %d),(%d, %d),(%d, %d)\n", fdl->path_num, (p->lock & FDL_PATH_IsRightOrButtom) ? "E": "S" ,
//					p->sx1, p->sy1, p->sx2, p->sy2, p->sx3, p->sy3,
//					p->sx1x, p->sy1y, p->sx2x, p->sy2y, p->sx3x, p->sy3y
//					p->sx1 + ((p->sx1x * W/256) >> 0), p->sy1 + ((p->sy1y * W/256) >> 0),
//					p->sx2 + ((p->sx2x * W/256) >> 0), p->sy2 + ((p->sy2y * W/256) >> 0),
//					p->sx3 + ((p->sx3x * W/256) >> 0), p->sy3 + ((p->sy3y * W/256) >> 0),
//
//					(p->sx1 + (p->sx1x * W/256)) >> 8, (p->sy1 + (p->sy1y * W/256)) >> 8,
//					(p->sx2 + (p->sx2x * W/256)) >> 8, (p->sy2 + (p->sy2y * W/256)) >> 8,
//					(p->sx3 + (p->sx3x * W/256)) >> 8, (p->sy3 + (p->sy3y * W/256)) >> 8
//					);
}
#else
//	DumpDebugString("  Point%d %s (%d, %d),(%d, %d),(%d, %d) => (%d, %d),(%d, %d),(%d, %d): %d\n", fdl->path_num, (p->lock & FDL_PATH_IsRightOrButtom) ? "E": "S" ,p->sx1, p->sy1, p->sx2, p->sy2, p->sx3, p->sy3, (p->sx1 >> fdl->Frac2),  (p->sy1 >> fdl->Frac2),  (p->sx2 >> fdl->Frac2),  (p->sy2 >> fdl->Frac2), (p->sx3 >> fdl->Frac2),  (p->sy3 >> fdl->Frac2), (p->sx3 >> fdl->Frac2)-(p->sx1 >> fdl->Frac2));
#endif
#endif
	fdl->path_num++;
}// end SCurve3

static DT_void AssignLeftOrRight(pFdlRasterData fdl, DT32_int start, DT32_int cnt)
{
	DT32_int i, j;

	DT32_int near_idx_up, near_idx_down;
	DT32_int near_count_up,near_count_down;
	DT32_long near_mindist_up, near_mindist_down;

    PATH_UNIT *tmp_p;

	PATH_UNIT *p0, *p = fdl->path_buf+start;

	p0 = p;
	for(i=0; i < cnt; i++, p++)
	{
		PATH_UNIT *p1;
		DT32_long mx, my;

		mx = (p->sx1 + p->sx3) / 2;
		my = (p->sy1 + p->sy3) / 2;
		p1 = p0;
		if(p->dir == FDL_PATH_VERT)
		{
			for(j=0; j < cnt; j++, p1++)
			{
				if(j == i) continue;
				if(*p1->sy01 < my && my < *p1->sy03)
				{
					p->relation = j+start;
					if(mx >= *p1->sx03)
						p->lock |= FDL_PATH_IsRightOrButtom;
					break;
				}// end if
			}// end for
		}else if(p->dir == FDL_PATH_HORZ)
		{
#if 1
			near_mindist_up = 0;
			near_mindist_down = 0x7FFFFFFF;
			near_count_up = 0; 
			near_count_down = 0;
			near_idx_down  = -1;
			near_idx_up = -1;
		
			tmp_p = p1;
			for(j=0; j < cnt; j++, tmp_p++)
			{
				if(j == i) continue;
				if(*tmp_p->sx01 < mx && mx < *tmp_p->sx03)
				{
				 
					if( *tmp_p->sy01 <= *p->sy01)
					{
						if( *tmp_p->sy01 > near_mindist_up )
						{
							near_mindist_up = *tmp_p->sy01;
							near_idx_up = j;
						}
						near_count_up++;
					}
					else{
						if( *tmp_p->sy01 < near_mindist_down )
						{
							near_mindist_down = *tmp_p->sy01;
							near_idx_down = j;
						}
						near_count_down++;
					}
				}
			}
			if(near_count_up + near_count_down >0)
			{
				if(near_count_up%2==1)
				{
					p->relation = near_idx_up+start;
					if(my>=*(p1+near_idx_up)->sy03)
							p->lock |= FDL_PATH_IsRightOrButtom;
				}
				else{

					p->relation = near_idx_down+start;
					if(my>=*(p1+near_idx_down)->sy03)
							p->lock |= FDL_PATH_IsRightOrButtom;
				}
			}
#else
			
			for(j=0; j < cnt; j++, p1++)
			{
				if(j == i) continue;
				if(*p1->sx01 < mx && mx < *p1->sx03)
				{
					p->relation = j+start;
					if(my >= *p1->sy03)
						p->lock |= FDL_PATH_IsRightOrButtom;
					break;
				}// end if
			}// end for
#endif
		}else
		{
			DT32_int iFind1=-1, iFind2=-1;
			for(j=0; j < cnt; j++, p1++)
			{
				if(j == i) continue;
				if(*p1->sx01 < mx && mx < *p1->sx03)
				{
//					p->relation = j+start;
//					if(my < *p1->sy03)
//						p->lock |= FDL_PATH_IsRightOrButtom;
					iFind1 = j;
					break;
				}// end if
			}// end for

			p1 = p0;
			for(j=0; j < cnt; j++, p1++)
			{
				if(j == i) continue;
				if(*p1->sy01 < my && my < *p1->sy03)
				{
//					p->relation = j+start;
//					if(mx >= *p1->sx03)
//						p->lock |= FDL_PATH_IsRightOrButtom;
					iFind2 = j;
					break;
				}// end if
			}// end for

			if(iFind1 >= 0 && iFind2 < 0)
			{
				p->relation = iFind1+start;
				if(my < fdl->path_buf[start+iFind1].sy03[0])
					p->lock |= FDL_PATH_IsRightOrButtom;
			}else if(iFind1 < 0 && iFind2 >= 0)
			{
				p->relation = iFind2+start;
				if(mx >= fdl->path_buf[start+iFind2].sx03[0])
					p->lock |= FDL_PATH_IsRightOrButtom;
			}else if(iFind1 >= 0 && iFind2 >= 0)
			{
				if((my > fdl->path_buf[start+iFind1].sy03[0]) && (mx >= fdl->path_buf[start+iFind2].sx03[0]))
					p->lock |= FDL_PATH_IsRightOrButtom;
				else if((my > fdl->path_buf[start+iFind1].sy03[0]) && (mx < fdl->path_buf[start+iFind2].sx03[0]))
					p->lock |= FDL_PATH_IsRightOrButtom;
			}// end if

		}// end if
	}// end for

}// end AssignLeftOrRight

static DT_void ShiftStrokeW(pFdlRasterData fdl, DT32_int strorder, DT32_int w)
{
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(strorder >= 0 && p->strorder != strorder)
			continue;

		if(p->lock & FDL_PATH_IsRightOrButtom)
		{
			p->sx1 += w;
			p->sx2 += w;
			p->sx3 += w;
		}// end if
	}// end for
}// end ShiftStrokeW

static DT_void ShiftStrokeH(pFdlRasterData fdl, DT32_int strorder, DT32_int h)
{
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(strorder >= 0 && p->strorder != strorder)
			continue;

		if(p->lock & FDL_PATH_IsRightOrButtom)
		{
			p->sy1 += h;
			p->sy2 += h;
			p->sy3 += h;
		}// end if
	}// end for
}// end ShiftStrokeH

static DT_void ShiftStrokeX(pFdlRasterData fdl, DT32_int strorder, DT32_int x)
{
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(strorder >= 0 && p->strorder != strorder)
			continue;

		p->sx1 += x;
		p->sx2 += x;
		p->sx3 += x;
		if(x < 0)
		{
			if(p->sx1 < 0) p->sx1 = 0;
			//if(p->sx2 < 0) p->sx2 = 0;
			if(p->sx3 < 0) p->sx3 = 0;
		}// end if
	}// end for
}// end ShiftStrokeX

static DT_void ShiftStrokeY(pFdlRasterData fdl, DT32_int strorder, DT32_int y)
{
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(strorder >= 0 && p->strorder != strorder)
			continue;

		p->sy1 += y;
		p->sy2 += y;
		p->sy3 += y;
	}// end for
}// end ShiftStrokeY

DT_void ShiftXY(pFdlRasterData fdl, DT32_int group, DT32_int x, DT32_int y)
{
#if 1
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(fdl->group_wrk[p->strorder] != group)
			continue;

		p->sx1 += x;
		p->sx2 += x;
		p->sx3 += x;

		p->sy1 += y;
		p->sy2 += y;
		p->sy3 += y;
	}// end for
#endif
}// end ShiftXY

DT_void ShiftX(pFdlRasterData fdl, DT32_int group, DT32_int x)
{
#if 1
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(fdl->group_wrk[p->strorder] != group)
			continue;

		p->sx1 += x;
		p->sx2 += x;
		p->sx3 += x;
	}// end for
#endif
}// end ShiftX

DT_void ShiftY(pFdlRasterData fdl, DT32_int group, DT32_int y)
{
#if 1
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(fdl->group_wrk[p->strorder] != group)
			continue;

		p->sy1 += y;
		p->sy2 += y;
		p->sy3 += y;
	}// end for
#endif
}// end ShiftXY

DT_void CountBoundle(pFdlRasterData fdl, DT32_int group, TRect* rect)
{
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	rect->left = 0x00FFFFFF;
	rect->right = 0;
	rect->top = 0x00FFFFFF;
	rect->bottom = 0;

	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(fdl->group_wrk[p->strorder] != group)
			continue;

		if(rect->left > *p->sx01)
			rect->left = *p->sx01;
		if(rect->right < *p->sx03)
			rect->right = *p->sx03;

		if(rect->top > *p->sy01)
			rect->top = *p->sy01;
		if(rect->bottom < *p->sy03)
			rect->bottom = *p->sy03;
	}// end for
}// end CountBoundle


static DT_void ScaleOutline(pFdlRasterData fdl)
{
	DT32_int i, divvalue;
	PATH_UNIT *p;

	//DumpDebugString("      ScaleOutline path_num %d\n", fdl->path_num);
	// ========================================================================
	divvalue = 0;
	p = fdl->path_buf;
	switch(fdl->ysize)
	{
		case 1<<1:	divvalue = 1; break;	case 1<<2:	divvalue = 2; break;	case 1<<3:	divvalue = 3; break;
		case 1<<4:	divvalue = 4; break;	case 1<<5:	divvalue = 5; break;	case 1<<6:	divvalue = 6; break;
		case 1<<7:	divvalue = 7; break;	case 1<<8:	divvalue = 8; break;	case 1<<9:	divvalue = 9; break;
		case 1<<10:	divvalue = 10; break;	case 1<<11:	divvalue = 11; break;	case 1<<12:	divvalue = 12; break;
		case 1<<13:	divvalue = 13; break;	case 1<<14:	divvalue = 14; break;	case 1<<15:	divvalue = 15; break;
		default:
			break;
	}// end switch

	if(divvalue > 0)
	{
		for(i=0; i < fdl->path_num; i++, p++)
		{
#ifdef FDL_CACHE_WEIGHT
			p->sy1 += ((p->sy1y * fdl->WeightRX) >> 8);
			p->sy2 += ((p->sy2y * fdl->WeightRX) >> 8);
			p->sy3 += ((p->sy3y * fdl->WeightRX) >> 8);
#endif
			p->sy1 = a2ScaleY2(fdl, p->sy1, divvalue);
			p->sy2 = a2ScaleY2(fdl, p->sy2, divvalue);
			p->sy3 = a2ScaleY2(fdl, p->sy3, divvalue);
		}// end for
	}else
	{
		for(i=0; i < fdl->path_num; i++, p++)
		{
#ifdef FDL_CACHE_WEIGHT
#ifdef LIST_POINTS
			//DumpDebugStringCMD(" Point%d (%d, %d), (%d, %d)\n", i, p->sy1, p->sy3, p->sy1y, p->sy3y);
#endif
			p->sy1 = (p->sy1* fdl->ysize + ((p->sy1y*fdl->WeightRX* fdl->ysize)>>8)+128 )>>8;
			p->sy2 = (p->sy2* fdl->ysize + ((p->sy2y*fdl->WeightRX* fdl->ysize)>>8)+128 )>>8;
			p->sy3 = (p->sy3* fdl->ysize + ((p->sy3y*fdl->WeightRX* fdl->ysize)>>8)+128 )>>8;
#else
			p->sy1 = a2ScaleY(fdl, p->sy1);
			p->sy2 = a2ScaleY(fdl, p->sy2);
			p->sy3 = a2ScaleY(fdl, p->sy3);
#endif
		}// end for
	}// end if

	// ========================================================================
	divvalue = 0;
	p = fdl->path_buf;
	switch(fdl->xsize)
	{
		case 1<<1:	divvalue = 1; break;	case 1<<2:	divvalue = 2; break;	case 1<<3:	divvalue = 3; break;
		case 1<<4:	divvalue = 4; break;	case 1<<5:	divvalue = 5; break;	case 1<<6:	divvalue = 6; break;
		case 1<<7:	divvalue = 7; break;	case 1<<8:	divvalue = 8; break;	case 1<<9:	divvalue = 9; break;
		case 1<<10:	divvalue = 10; break;	case 1<<11:	divvalue = 11; break;	case 1<<12:	divvalue = 12; break;
		case 1<<13:	divvalue = 13; break;	case 1<<14:	divvalue = 14; break;	case 1<<15:	divvalue = 15; break;
		default:
			break;
	}// end switch

	if(divvalue > 0)
	{
		for(i=0; i < fdl->path_num; i++, p++)
		{
#ifdef FDL_CACHE_WEIGHT
			p->sx1 += ((p->sx1x * fdl->WeightRY) >> 8);
			p->sx2 += ((p->sx2x * fdl->WeightRY) >> 8);
			p->sx3 += ((p->sx3x * fdl->WeightRY) >> 8);
#endif
			p->sx1 = a2ScaleX2(fdl, p->sx1, divvalue);
			p->sx2 = a2ScaleX2(fdl, p->sx2, divvalue);
			p->sx3 = a2ScaleX2(fdl, p->sx3, divvalue);
		}// end for
	}else
	{
		for(i=0; i < fdl->path_num; i++, p++)
		{
#ifdef FDL_CACHE_WEIGHT
#ifdef LIST_POINTS
			//DumpDebugStringCMD("    PointX%d (%d, %d), (%d, %d)\n", i, p->sx1, p->sx3, p->sx1x, p->sx3x);
#endif
			p->sx1 = (p->sx1* fdl->xsize + ((p->sx1x*fdl->WeightRY* fdl->xsize)>>8)+128 )>>8;
			p->sx2 = (p->sx2* fdl->xsize + ((p->sx2x*fdl->WeightRY* fdl->xsize)>>8)+128 )>>8;
			p->sx3 = (p->sx3* fdl->xsize + ((p->sx3x*fdl->WeightRY* fdl->xsize)>>8)+128 )>>8;

#else
			p->sx1 = a2ScaleY(fdl, p->sx1);
			p->sx2 = a2ScaleY(fdl, p->sx2);
			p->sx3 = a2ScaleY(fdl, p->sx3);
#endif
		}// end for
	}// end if

#ifdef LIST_POINTS
	//p = fdl->path_buf;
	//for(i=0; i < fdl->path_num; i++, p++)
		//DumpDebugString("  Point%d %d:%d %s rel:%d (%d, %d),(%d, %d) => (%d, %d),(%d, %d)\n", i, p->strorder, p->subidx, (p->lock & FDL_PATH_IsRightOrButtom) ? "E": "S", p->relation, p->sx1, p->sy1, p->sx3, p->sy3, (p->sx1 >> fdl->Frac2),  (p->sy1 >> fdl->Frac2),  (p->sx3 >> fdl->Frac2),  (p->sy3 >> fdl->Frac2));
#endif
}// end ScaleOutline

static DT_void GetStrokeRect(pFdlRasterData fdl, DT32_int strorder, TRect* rect)
{
	DT32_int i;
	PATH_UNIT *p;

	rect->right = 0;
	rect->bottom = 0;
	rect->left = 0x00FFFFFF;
	rect->top = 0x00FFFFFF;

	p = fdl->path_buf + fdl->stroke_buf[strorder].start;
	for(i=0; i < fdl->stroke_buf[strorder].len; i++, p++)
	{
		if(rect->left > *p->sx01)
			rect->left = *p->sx01;
		if(rect->right < *p->sx03)
			rect->right = *p->sx03;

		if(rect->top > *p->sy01)
			rect->top = *p->sy01;
		if(rect->bottom < *p->sy03)
			rect->bottom = *p->sy03;
	}// end for

}// GetStrokeRect

static DT_void GetGroupRect(pFdlRasterData fdl)
{
	DT32_int i, groupnum;
	TRect *rect1;
	TRect *rect = fdl->group_rect;

	if(fdl->groupinfo.fontid == 0x0000)
		groupnum = 1;
	else groupnum = fdl->groupinfo.groupnum;

	for(i=0; i < groupnum; i++, rect++)
	{
		rect->right = 0;
		rect->bottom = 0;
		rect->left = 0x00FFFFFF;
		rect->top = 0x00FFFFFF;
	}// end for

	rect = fdl->group_rect;
	for(i=0; i < fdl->stridcnt; i++)
	{
		rect = fdl->group_rect + FDL_SUB_GROUP(fdl->groupinfo.grouplist[i]);
		rect1 = &(fdl->stroke_buf[i].rect);

		if(rect->left > rect1->left)
			rect->left = rect1->left;
		if(rect->right < rect1->right)
			rect->right = rect1->right;

		if(rect->top > rect1->top)
			rect->top = rect1->top;
		if(rect->bottom < rect1->bottom)
			rect->bottom = rect1->bottom;
	}// end for

}// end GetGroupRect

static DT_void GetMainGroupRect(pFdlRasterData fdl)
{
	DT32_int i, group, strorder, curorder;
	TRect *rect1;
	TRect *rect = fdl->main_group_rect;

	for(i=0; i < SIZEOF_ARRAY(fdl->main_group_rect); i++, rect++)
	{
		rect->right = 0;
		rect->bottom = 0;
		rect->left = 0x00FFFFFF;
		rect->top = 0x00FFFFFF;
	}// end for

	curorder = -1;
	for(i=0; i < fdl->stridcnt; i++)
	{
		group = fdl->groupinfo.grouplist[i];
		rect = fdl->main_group_rect + (FDL_MAIN_GROUP(group) >> (8-MAIN_GROUP_BIT));
		strorder = FDL_SUB_GROUP(group);
		rect1 = fdl->group_rect + strorder;

		if(curorder != strorder)
		{
			curorder = strorder;
			if(rect->left > rect1->left)
				rect->left = rect1->left;
			if(rect->right < rect1->right)
				rect->right = rect1->right;

			if(rect->top > rect1->top)
				rect->top = rect1->top;
			if(rect->bottom < rect1->bottom)
				rect->bottom = rect1->bottom;
		}// end if
	}// end for

}// end GetMainGroupRect

static DT32_long GetMainGroupCenter(pFdlRasterData fdl, DT32_int mgrpidx)
{
	DT32_int i, j, groupnum, subcnt, group;
	DT8_uchar sublist[8];		// main group has max 8 sub groups.
	DT32_long mgrpcenter;
	DT32_long subcenterlist[8];	// sub group's center line.
	DT32_int  max_nearcnt;		//
	DT32_int  subgroupidx;		//
	TRect *rect;

	rect = fdl->main_group_rect + mgrpidx;//(FDL_MAIN_GROUP(mgrp) >> (8-MAIN_GROUP_BIT));
	mgrpcenter = (rect->left + rect->right)/2;

	if(fdl->groupinfo.fontid == 0x0000)
		groupnum = 1;
	else groupnum = fdl->groupinfo.groupnum;

	if(groupnum < 3){		//Re-Calculate the center of main group only when groupnum > 3.
		return mgrpcenter;
	}

	// Get how many sub-groups of this maingroup?
	subcnt = 0;
	DT_memset(sublist, 0xFF, sizeof(sublist));
	DT_memset(subcenterlist, 0, sizeof(subcenterlist));
	for(i=0; i < fdl->stridcnt; i++)
	{
		group = fdl->groupinfo.grouplist[i];
		
		if((FDL_MAIN_GROUP(group) >> (8-MAIN_GROUP_BIT)) == mgrpidx)	//FDL_MAIN_GROUP(mgrp))
		{
			if(subcnt==0)
			{
				subcnt++;
				sublist[subcnt-1] = (DT8_uchar)FDL_SUB_GROUP(group);
				rect = fdl->group_rect + FDL_SUB_GROUP(group);
				subcenterlist[subcnt-1] = (rect->left + rect->right)/2;
			}else
			{
				for(j=0; j<subcnt; j++)
				{
					if(sublist[j]==FDL_SUB_GROUP(group))
						break;
				}

				if(j==subcnt)	//New sub-group
				{
					subcnt++;
					sublist[subcnt-1] = (DT8_uchar)FDL_SUB_GROUP(group);
					rect = fdl->group_rect + FDL_SUB_GROUP(group);
					subcenterlist[subcnt-1] = (rect->left + rect->right)/2;
				}
			}
		}
	}

	// loop all the sub-groups to re-calculate the center of maingroup
	if(subcnt<3){
		return mgrpcenter;	// subgroup less 3, use maingroup's center line
	}
	max_nearcnt = 0;
	subgroupidx = -1;
	for(i=0; i<subcnt; i++)
	{
		DT8_uchar cnt=0;
		//mgrpcenter = subcenterlist[i];
		for(j=0; j<subcnt; j++)
		{
			if( i!=j && (DT_abs(subcenterlist[i]-subcenterlist[j]) < (1 << fdl->shift)/2) )
				cnt++;
		}
		if(cnt > max_nearcnt)
		{
			max_nearcnt = cnt;
			subgroupidx= i; 
		}
	}

	if(subgroupidx>=0){
		if( DT_abs(subcenterlist[subgroupidx]-mgrpcenter) <= (1 << fdl->shift)/2){
			return mgrpcenter;
		}
		return subcenterlist[subgroupidx];
	}else{
		return mgrpcenter;
	}

	return mgrpcenter;
}

static DT_void GetGroupRectAfterHint(pFdlRasterData fdl, TRect *rectorg, DT32_int len)
{
	DT32_int i;
	PATH_UNIT *p;
	TRect *rect1;
	TRect *rect = rectorg;

	for(i=0; i < len; i++, rect++)
	{
		rect->right = 0;
		rect->bottom = 0;
		rect->left = 0x00FFFFFF;
		rect->top = 0x00FFFFFF;
	}// end for

	for(i=0; i <  fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		rect = rectorg + (FDL_SUB_GROUP(fdl->groupinfo.grouplist[ p->strorder ]));
		rect1 = &(fdl->stroke_buf[ p->strorder ].rect);

		if(rect->left > rect1->left)
			rect->left = rect1->left;
		if(rect->right < rect1->right)
			rect->right = rect1->right;

		if(rect->top > rect1->top)
			rect->top = rect1->top;
		if(rect->bottom < rect1->bottom)
			rect->bottom = rect1->bottom;
	}// end for

}// end GetGroupRectAfterHint

static DT_void GetMainGroupRectAfterHint(pFdlRasterData fdl, TRect *rectorg, DT32_int len)
{
	DT32_int i;
	PATH_UNIT *p;
	TRect *rect1;
	TRect *rect = rectorg;

	for(i=0; i < len; i++, rect++)
	{
		rect->right = 0;
		rect->bottom = 0;
		rect->left = 0x00FFFFFF;
		rect->top = 0x00FFFFFF;
	}// end for

	for(i=0; i <  fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		rect = rectorg + (FDL_MAIN_GROUP(fdl->groupinfo.grouplist[ p->strorder ]) >> (8-MAIN_GROUP_BIT));
		rect1 = &(fdl->stroke_buf[ p->strorder ].rect);

		if(rect->left > rect1->left)
			rect->left = rect1->left;
		if(rect->right < rect1->right)
			rect->right = rect1->right;

		if(rect->top > rect1->top)
			rect->top = rect1->top;
		if(rect->bottom < rect1->bottom)
			rect->bottom = rect1->bottom;
	}// end for

}// end GetMainGroupRectAfterHint

static DT_void GetFontRectAll(pFdlRasterData fdl, TRect *rect)
{
	DT32_int i;
	PATH_UNIT *p;

	rect->right = 0;
	rect->bottom = 0;
	rect->left = 0x00FFFFFF;
	rect->top = 0x00FFFFFF;

	p = fdl->path_buf;
	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(rect->left > *p->sx01)
			rect->left = *p->sx01;
		if(rect->right < *p->sx03)
			rect->right = *p->sx03;

		if(rect->top > *p->sy01)
			rect->top = *p->sy01;
		if(rect->bottom < *p->sy03)
			rect->bottom = *p->sy03;
	}// end for

}// end GetFontRectAll

static DT_void GetFontRect(pFdlRasterData fdl, TRect *rect)
{
	DT32_int i;
	PATH_UNIT *p;

	rect->right = 0;
	rect->bottom = 0;
	rect->left = 0x00FFFFFF;
	rect->top = 0x00FFFFFF;

	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(rect->left > *p->sx01)
			rect->left = *p->sx01;
		if(rect->right < *p->sx03)
			rect->right = *p->sx03;

		if(rect->top > *p->sy01)
			rect->top = *p->sy01;
		if(rect->bottom < *p->sy03)
			rect->bottom = *p->sy03;
	}// end for

}// end GetFontRect

static DT_void Do_MoveFontMainGroupX(pFdlRasterData fdl, DT32_int maingroup, DT32_int move)
{
	DT32_int i, group;
	PATH_UNIT *p;

	group = maingroup << (8-MAIN_GROUP_BIT);
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[ p->strorder ]) == group)
		{
			p->sx1 += move;
			p->sx2 += move;
			p->sx3 += move;
		}// end if
	}// end for

}// end Do_MoveFontGroupX

static DT_void Do_MoveFontMainGroupY(pFdlRasterData fdl, DT32_int maingroup, DT32_int move)
{
	DT32_int i, group;
	PATH_UNIT *p;

	group = maingroup << (8-MAIN_GROUP_BIT);
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[ p->strorder ]) == group)
		{
			p->sy1 += move;
			p->sy2 += move;
			p->sy3 += move;
		}// end if
	}// end for

}// end Do_MoveFontGroupY

static DT_void Do_MoveFontX(pFdlRasterData fdl, DT32_int move)
{
	DT32_int i;
	PATH_UNIT *p;

	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		p->sx1 += move;
		p->sx2 += move;
		p->sx3 += move;
	}// end for

}// end Do_MoveFontX

static DT_void Do_MoveFontY(pFdlRasterData fdl, DT32_int move)
{
	DT32_int i;
	PATH_UNIT *p;

	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		p->sy1 += move;
		p->sy2 += move;
		p->sy3 += move;
	}// end for

}// end Do_MoveFontY

#if 0
static DT32_int SortCmp(TRect *rect1, TRect *rect2)
{
	if((rect1->left >= rect2->left && rect1->left <= rect2->right) ||
			(rect1->right >= rect2->left && rect1->right <= rect2->right)
	{
		
	}// end if

}// end SortCmp

// 20110804: Jacky marked for memory
//static DT_void SortGroupList(pFdlRasterData fdl)
//{
//	DT32_int i, j, IsOK;
//	TRect *rect = fdl->group_rect;
//
//	for(i=0; i < fdl->groupinfo.groupnum; i++, rect++)
//	{
//		IsOK = 0;
//		for(j=0; j < i; j++)
//		{
////			if(rect->left < fdl->group_rect[ fdl->group_list[j] ].left)
//			if(SortCmp(rect, fdl->group_rect + fdl->group_list[j]) <= 0)
//			{
//				DT8_uchar tmpbuf[FDL_MAX_STACK/8];		// 20110804: the limitation changed in Dcw.h
//				DT_memcpy(tmpbuf, fdl->group_list+j, j);
//				fdl->group_list[j] = i;
//				DT_memcpy(fdl->group_list+j+1, tmpbuf, j);
//				IsOK = 1;
//				break;
//			}// end if
//		}// end for
//
//		if(IsOK == 0)
//		{
//			fdl->group_list[j] = i;
//		}// end if
//	}// end for
//
///*	rect = fdl->group_rect;
//	for(i=0; i < fdl->stridcnt; i++)
//	{
//		rect = fdl->group_rect + fdl->groupinfo.grouplist[i];
//		rect1 = &(fdl->stroke_buf[i].rect);
//
//		if(rect->left > rect1->left)
//			rect->left = rect1->left;
//		if(rect->right < rect1->right)
//			rect->right = rect1->right;
//
//		if(rect->top > rect1->top)
//			rect->top = rect1->top;
//		if(rect->bottom < rect1->bottom)
//			rect->bottom = rect1->bottom;
//	}// end for
//*/
//}// end SortGroupList
#endif

static DT_void Do_KeepAllPathStroke(pFdlRasterData fdl)
{
	DT32_int i;
	PATH_UNIT *p = fdl->path_buf;

	fdl->stroke_num = 0;
	fdl->path_buf_pt_num = 0;
	for(i=0; i < fdl->path_num; i++, p++)
	{
		if(fdl->stroke_num <= 0 || fdl->stroke_order[fdl->stroke_num-1] != p->strorder)
			fdl->stroke_order[ fdl->stroke_num++ ] = p->strorder;
		fdl->path_buf_pt[ fdl->path_buf_pt_num++ ] = i;
	}
}

//static DT_void Do_RemoveStroke(pFdlRasterData fdl)
//{
//	DT32_int i, j, k;
//	PATH_UNIT *p = fdl->path_buf;
//	DT32_int cancel;
//	FDL_StrokeHint *Vhintlist;
//
//	fdl->stroke_num = 0;
//	if(fdl->groupinfo.hintnum <= 0)
//	{
//		for(i=0; i < fdl->path_num; i++, p++)
//		{
//			if(fdl->stroke_num <= 0 || fdl->stroke_order[fdl->stroke_num-1] != p->strorder)
//				fdl->stroke_order[ fdl->stroke_num++ ] = p->strorder;
//			fdl->path_buf_pt[i] = i;
//		}// end for
//		fdl->path_buf_pt_num = i;
//		return;
//	}
//	
//	// make sure weight_modeH and weight_modeV less than index.
//	if(fdl->weight_modeH >= fdl->hintlistH_num){
//		fdl->weight_modeH = fdl->hintlistH_num-1;
//	}else if(fdl->weight_modeV >= fdl->hintlistV_num){
//		fdl->weight_modeV = fdl->hintlistV_num-1;
//	}
//
//	fdl->path_buf_pt_num = 0;
//	Vhintlist = fdl->groupinfo.hintlist + fdl->hintlistH_num;
//	for(i=0; i < fdl->path_num; i++, p++)
//	{
//		cancel = 0;
//		for(j=0; j <= fdl->weight_modeH; j++)	// find the stroke to remove.
//		{
//			if(p->strorder == fdl->groupinfo.hintlist[j].stroke)	// If this weight with FDL_ALIGN_MODE flag, then should never have strorder equal it.
//			{
//				cancel = 1;
//				break;
//			}// end if
//		}// end for
//		
//		if(cancel==0){
//		  for(k=0; k <= fdl->weight_modeV; k++)
//		  {
//			if(p->strorder == (Vhintlist[k].stroke & ~FDL_ALIGN_VSTROKE))	// If this weight with FDL_ALIGN_MODE flag, then should never have strorder equal it.
//			{
//				cancel = 1;
//				break;
//			}// end if
//		  }// end for
//		}
//
//		if(cancel == 0)
//		{
//			if(fdl->stroke_num <= 0 || fdl->stroke_order[fdl->stroke_num-1] != p->strorder)
//				fdl->stroke_order[ fdl->stroke_num++ ] = p->strorder;
//			fdl->path_buf_pt[ fdl->path_buf_pt_num++ ] = i;
//		}// end if
//	}// end for
//
///*	fdl->stroke_pack_num = 0;
//	for(j=0; j <= fdl->weight_mode; j++)
//	{
//		if((fdl->groupinfo.weight[j] & FDL_ALIGN_MODE) != 0)
//		{
//			fdl->stroke_pack[fdl->stroke_pack_num++] = fdl->groupinfo.weight[j] & ~FDL_ALIGN_MODE;
//		}// end if
//	}// end if*/
//}// end Do_RemoveStroke

static DT_void Do_RemoveStroke_When_Adjust(pFdlRasterData fdl, DT32_int strorder, DT32_int resort)
{
	DT16_short i, j, pstart=0xFF;
	STROKE_UNIT *s=NULL;
	PATH_UNIT	*p=NULL;

	s = &fdl->stroke_buf[strorder];
	// Remove stroke
	for(i=0;i<fdl->stroke_num;i++)
	{
		if(fdl->stroke_order[i]==strorder){
			// Remove stroke
			fdl->path_tmp_num = fdl->stroke_num - i - 1;
			DT_memcpy(fdl->path_tmp_buf,fdl->stroke_order+i+1,fdl->path_tmp_num*sizeof(fdl->stroke_order[0]));	// backup
			DT_memcpy(fdl->stroke_order+i,fdl->path_tmp_buf,fdl->path_tmp_num*sizeof(fdl->stroke_order[0]));
			fdl->stroke_order[i+fdl->path_tmp_num]=0;
			fdl->stroke_num--;
			// Remove path of this stroke
			for(j=0;j<fdl->path_buf_pt_num;j++){	// find the start path of this stroke
				if(fdl->stroke_buf[strorder].start==fdl->path_buf_pt[j]){
					pstart = fdl->path_buf_pt[j];
					fdl->path_tmp_num = fdl->path_buf_pt_num - j - s->len;
					DT_memcpy(fdl->path_tmp_buf,fdl->path_buf_pt+j+s->len,fdl->path_tmp_num*sizeof(fdl->path_buf_pt[0]));
					DT_memcpy(fdl->path_buf_pt+j,fdl->path_tmp_buf,fdl->path_tmp_num*sizeof(fdl->path_buf_pt[0]));
					DT_memset(fdl->path_buf_pt+j+fdl->path_tmp_num, 0, s->len*sizeof(fdl->path_buf_pt[0]));
					fdl->path_buf_pt_num -= s->len;
					break;
				}
			}
			// Re-sort 
			fdl->path_tmp_num = fdl->stroke_line_num;
			if(FDL_RESORT_BY_HLINES==resort)
				Do_SortCollectLines(fdl);
			else if(FDL_RESORT_BY_VLINES==resort){
				Do_SortCollectVLines(fdl);
			}
			DT_memset(fdl->stroke_line_order+fdl->stroke_line_num,0,
						(fdl->path_tmp_num-fdl->stroke_line_num)*sizeof(fdl->stroke_line_order[0]));
			break;
		}
	}

	//TODO:Need to Re-Calculate Stroke & Group's rect?

}

static DT32_int StrokeOrder(pFdlRasterData fdl, DT32_int idx)
{
	DT32_int j, curgroup;
	DT32_int mode=FDL_STROKE_MIDDLE;
	DT32_int top=0;

	//fdl->stroke_buf[idx].rect.top;	//Marked_by_Jacky 
	curgroup = fdl->group_wrk[idx];
	for(j=0; j < fdl->stroke_line_num; j++)
	{
		if(fdl->group_wrk[ fdl->path_buf[ fdl->stroke_line_order[j] ].strorder] == curgroup)
		{
		   top = *(fdl->path_buf[ fdl->stroke_line_order[j] ].sy01);
		   break;
		}// end if
	}// end for

	if(top <= fdl->stroke_buf[idx].rect.top)	//Modified_by_Jacky, origin: //if(top >= fdl->stroke_buf[idx].rect.top)
	{
		mode = FDL_STROKE_FIRST;
	}else
	{
		for(j++; j < fdl->stroke_line_num; j++)
		{
			if(fdl->group_wrk[ fdl->path_buf[ fdl->stroke_line_order[j] ].strorder] == curgroup)
			{
				top = *(fdl->path_buf[ fdl->stroke_line_order[j] ].sy01);
			}// end if
		}// end for

		if( fdl->stroke_buf[idx].rect.bottom <= top)	//Modified_by_Jacky, origin: //if( fdl->stroke_buf[idx].rect.bottom >= top)
			mode = FDL_STROKE_LAST;
	}// end if

	return 	mode;
}// end StrokeOrder

static Do_ChangeStrokeGroup(pFdlRasterData fdl, DT8_uchar curgroup, DT8_uchar targetgroup)
{
	DT32_int i;

	for(i=0; i < fdl->stridcnt; i++)
	{
		if(fdl->group_wrk[i] == curgroup)
		{
			fdl->group_wrk[i] = targetgroup;
			fdl->group_fin[i] = targetgroup;
		}// end if
	}// end for

//	if(fdl->group_wrknum < targetgroup && targetgroup != 0xFF)
//		fdl->group_wrknum = targetgroup;

}// end Do_ChangeStrokeGroup

static DT32_long CalNewYPosition(DT32_long y, DT32_long top, DT32_long recth, DT32_long shorten)
{
	if(0==shorten){
		return y;
	}

	return (top + (y-top)*(recth-shorten)/recth);
} 

static DT32_long CalNewXPosition(DT32_long x, DT32_long left, DT32_long rectw, DT32_long shorten)
{
	if(0==shorten){
		return x;
	}

	return (left + (x-left)*(rectw-shorten)/rectw);
} 

static DT_void DuplicatePATH_UNIT(PATH_UNIT *dst, PATH_UNIT *src)
{
	DT_memcpy(dst, src, sizeof(PATH_UNIT));
	dst->sx01 = (dst->sx1<dst->sx3) ? (&dst->sx1):(&dst->sx3);
	dst->sx03 = (dst->sx1>dst->sx3) ? (&dst->sx1):(&dst->sx3);
	dst->sy01 = (dst->sy1<dst->sy3) ? (&dst->sy1):(&dst->sy3);
	dst->sy03 = (dst->sy1>dst->sy3) ? (&dst->sy1):(&dst->sy3);
}

static DT8_char Is_Rect_rt0_Inside_rt1(TRect *rt0, TRect *rt1)
{
	if( rt1->left<=rt0->left &&
		rt1->right>=rt0->right &&
		rt1->top<=rt0->top &&
		rt1->bottom>=rt0->bottom){
		return 1;
	}
	return 0;	
}

static DT_void Do_MoveStroke_AlignPackY( pFdlRasterData fdl, STROKE_UNIT	*s,	STROKE_UNIT	*spp, 
									    PATH_UNIT *p0, DT32_long pp_sy01, DT32_long pp_rel_h/*, PATH_UNIT *pp*/)
{
	DT16_short i, adjsy2/*, end_path = start_path + s->len*/;
	PATH_UNIT *p=NULL;
	DT32_long tmp, p0_relate, recth, high, move, shorten, gap, pixh;
	DT32_int p0_rel_h, threshold;
	STROKE_UNIT *stroke_p0=NULL;

	recth = s->rect.bottom-s->rect.top;	// height of s->rect
	high = pp_sy01/**pp->sy01*/ - *p0->sy01;
	if(s->rect.top < *p0->sy01){
		move = 0;
		tmp = s->rect.bottom - *p0->sy01;
		if(tmp<=0){
			shorten = 0;
			return;
		}else if(tmp>=high){
			shorten = high;
		}else{
			p0_relate= *p0->sy01;
			if(FDL_PATH_HORZ==p0->dir && p0->relation>=0){
				p0_relate = *(fdl->path_buf[p0->relation].sy03);
			}
			if(s->rect.bottom <= p0_relate){
				shorten = 0;
				return;
			}else{
				shorten = tmp;
			}
		}
	}else if(s->rect.top > pp_sy01/**pp->sy01*/){
		move = high;
		shorten = 0;
	}else{
		move = s->rect.top - (*p0->sy01);
		tmp = pp_sy01/**pp->sy01*/ - s->rect.top;
		if( tmp+pp_rel_h >= recth ){
			shorten = recth;
			if(s->strorder!=p0->strorder){
				if( spp && s->rect.left >= spp->rect.left &&
					s->rect.right <= spp->rect.right){
					if(s->strorder == spp->strorder){
						shorten = 0;
					}else{
						//Because all the stroke will be as a line, delete it directly.
						Do_RemoveStroke_When_Adjust(fdl, s->strorder,FDL_RESORT_BY_HLINES);
						return;
					}
				}else{
					shorten = FDL_SHORTEN_VALUE(recth);	//recth*9/10;
				}
			}
		}else{
			shorten = tmp;
		}
	}

	// reset each stroke's path
	if(s->strorder==p0->strorder){
	  stroke_p0 = &fdl->stroke_buf[p0->strorder];
	  p0_rel_h = *p0->sy01;
	  if(FDL_PATH_HORZ==p0->dir && p0->relation>=0){
		p0_rel_h = *(fdl->path_buf[p0->relation].sy03);
	  }
	  p0_rel_h -= *p0->sy01;
	  if(p0_rel_h<=0){
		p0_rel_h = pp_rel_h;
	  }
	  threshold = *p0->sy01 + p0_rel_h;
	  pixh		= (fdl->stroke_weightX<<fdl->shift)/10;
	  
	  if(stroke_p0->status & FDL_STROKE_CANNOT_BE_A_LINE){	/* 0x8DCE, 0x3107 type */
		  for(i=0;i<s->len;i++){
			p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;
			adjsy2 = 0;
			if(p->sy1 > threshold){
				p->sy1 = CalNewYPosition(p->sy1, s->rect.top, recth, shorten);
				gap = p->sy1 - *p0->sy01;
				if( (gap < 2*p0_rel_h) || (p->sy1-threshold<pixh) ){
					p->sy1 = threshold + pixh;	
					adjsy2 = 1;
				}
			}
			if(p->sy3 > threshold){
				p->sy3 = CalNewYPosition(p->sy3, s->rect.top, recth, shorten);
				gap = p->sy3 - *p0->sy01;
				if( (gap < 2*p0_rel_h) || (p->sy3-threshold<pixh)){
					p->sy3 = threshold + pixh;	
					adjsy2 = 1;
				}
			}
			if(p->sy2 > threshold){
				p->sy2 = CalNewYPosition(p->sy2, s->rect.top, recth, shorten);	
				if(adjsy2)
				{
				p->sy2 = (p->sy1 + p->sy3)/2;
			}
			}

			p->sy1 -= move;
			p->sy3 -= move;
			p->sy2 -= move;
					
			p->sy1a = p->sy1;
			p->sy3a = p->sy3;
		  }
	  }else{
		  for(i=0;i<s->len;i++){
			p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

			if(p->sy1 > threshold){
				p->sy1 = CalNewYPosition(p->sy1, s->rect.top, recth, shorten);
			}
			if(p->sy2 > threshold){
				p->sy2 = CalNewYPosition(p->sy2, s->rect.top, recth, shorten);
			}
			if(p->sy3 > threshold){
				p->sy3 = CalNewYPosition(p->sy3, s->rect.top, recth, shorten);
			}
			p->sy1 -= move;
			p->sy3 -= move;
			p->sy2 -= move;
					
			p->sy1a = p->sy1;
			p->sy3a = p->sy3;
		  }
	  }
	}else{

	  for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		p->sy1 = CalNewYPosition(p->sy1, s->rect.top, recth, shorten);
		p->sy2 = CalNewYPosition(p->sy2, s->rect.top, recth, shorten);
		p->sy3 = CalNewYPosition(p->sy3, s->rect.top, recth, shorten);

		p->sy1 -= move;
		p->sy3 -= move;
		p->sy2 -= move;
				
		p->sy1a = p->sy1;
		p->sy3a = p->sy3;
	  }

	}

	GetStrokeRect(fdl, s->strorder, &(fdl->stroke_buf[ s->strorder ].rect));
	//TODO: Group rect?

	Do_SortCollectLines(fdl);
}

// AlignPack to upper
static DT_void Do_StrokeAlignPackY(pFdlRasterData fdl, DT32_int remove_strorder)
{
	DT32_int j, high;
	PATH_UNIT *p;

	for(j=0; j < fdl->stroke_line_num; j++)	//loop to fined which stroke.
	{
		PATH_UNIT *pp;
		pp = fdl->path_buf + fdl->stroke_line_order[j];
		if(pp->strorder == remove_strorder)	//remove_stroke found.
		{
				DT16_short k;
				PATH_UNIT *p0=NULL;
				STROKE_UNIT	*s=NULL;	//current stroke to deal with.
				STROKE_UNIT	spp;		//stroke contains pp; Maybe only TRect is required.
				DT32_long pp_sy01;
				DT32_long pp_rel_h, p0_rel_h;
				//PATH_UNIT pp_copy;	// keep the original pp to get the relationship
				
				//DuplicatePATH_UNIT(&pp_copy,pp);
				DT_memcpy(&spp, fdl->stroke_buf+remove_strorder, sizeof(STROKE_UNIT) ); // keep stroke of pp								

				pp_sy01 = *pp->sy01;
				pp_rel_h = *pp->sy01;
				if(FDL_PATH_HORZ==pp->dir && pp->relation>=0){
					pp_rel_h = *(fdl->path_buf[pp->relation].sy03);
				}
				pp_rel_h -= *pp->sy01;

				for(k=j; k > 0; k--)
				{
					p0 = fdl->path_buf + fdl->stroke_line_order[k-1];	//find the upper hori-line: p0
					if( fdl->group_wrk[ p0->strorder ] != 0xFF &&
						IsLineOverlayX(*p0->sx01, *p0->sx03, *pp->sx01, *pp->sx03) ){
						if(*p0->sy01 == pp_sy01){	//TODO: How about multi-remove-stroke in a same size?
							p0 = NULL;			//Jacky_20101026: avoid wrong p0
							continue;			//Jacky_20101026: multi-remove-stroke to the same p0.
							//break;			//Jacky_20100921: TODO: Is it correct?
						}else{
							if(p0->relation>=0){
								p0_rel_h = *(fdl->path_buf[p0->relation].sy03) - *p0->sy01 ;
								if(pp_rel_h>0 && p0_rel_h>2*pp_rel_h){	// avoid to find the wrong p0
									continue;
								}
								break;
							}else{
								continue;	// p0 must be a horizontal line
							}
						}
					}else p0 = NULL;
				}// end for

				if(p0 == NULL) continue;
				//adjust by stroke
				high = *pp->sy01 - *p0->sy01;	//distance between pp & p0
				Do_ChangeStrokeGroup(fdl, fdl->group_wrk[remove_strorder], fdl->group_wrk[p0->strorder]);
				for(k=0; k < fdl->path_buf_pt_num; k += s->len/*k++*/)
				{
					p = fdl->path_buf + fdl->path_buf_pt[k];
					s = &fdl->stroke_buf[p->strorder];
					if(fdl->group_wrk[ p->strorder ] == 0xFF)
						continue;

					if(p->strorder == remove_strorder){
						continue;		// pp: do it in the final
					}
					
					Do_MoveStroke_AlignPackY(fdl, s, &spp, p0, pp_sy01, pp_rel_h/*, &pp_copy*/);
//					if(0==s->rect.bottom - s->rect.top){
//						if( s->rect.left >= spp.rect.left &&
//							s->rect.right<= spp.rect.right){
//							Do_RemoveStroke_When_Adjust(fdl,s->strorder,FDL_RESORT_BY_HLINES);
//						}
//					}

//					}// end if
				}// end for
				Do_MoveStroke_AlignPackY(fdl, &spp, &spp, p0, pp_sy01, pp_rel_h/*, &pp_copy*/);	//stroke spp
				
			break;	//next remove stroke
		}// end if

	}// end for
}

static DT_void Do_MoveStroke_RemoveAlignY( pFdlRasterData fdl, STROKE_UNIT	*s,	STROKE_UNIT	*spp, 
										  DT32_long pp_sy01, DT32_long pp_rel_h/*, PATH_UNIT *pp*/)
{
	DT16_short i/*, end_path = start_path + s->len*/;
	PATH_UNIT *p=NULL;
	DT32_long recth, move, shorten;	// move: to up; shorten: remove distance;

	recth = s->rect.bottom-s->rect.top;	// height of s->rect
	if(s->rect.top < pp_sy01){						//rect of s is upper than pp
		move = 0;
		shorten = 0;								//no move; no shorten		
		if(s->rect.bottom > (pp_sy01+pp_rel_h) ){	//rect of s is upper than pp, shorten pp_rel_h
			shorten = pp_rel_h;
		}else if(s->rect.bottom <= pp_sy01){
			shorten = 0;
			return;									//all the rect of s is upper than pp, no move; no shorten
		}else{
			shorten = s->rect.bottom-pp_sy01;		//bottom of s is inside pp, shorten the part lower than pp
		}
	}else if(s->rect.top > (pp_sy01+pp_rel_h)){
		move = pp_rel_h;							//all the rect of s is lower than pp, only move upper
		shorten = 0;
	}else{
		move = s->rect.top - pp_sy01;				//rect of s starts inside pp, move upper, move < pp_rel_h
		shorten = pp_rel_h - move;
		if(shorten>=recth){
			shorten = recth;						//TODO: Can s be removed?
			if( spp && s->rect.left >= spp->rect.left &&
				s->rect.right<= spp->rect.right){
				Do_RemoveStroke_When_Adjust(fdl, s->strorder,FDL_RESORT_BY_HLINES);
				return;
			}else{
				shorten = FDL_SHORTEN_VALUE(recth);	//recth*9/10;
			}
		}
	}

	// re-calculate each path in the stroke s
	for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		p->sy1 = CalNewYPosition(p->sy1, s->rect.top, recth, shorten);
		p->sy2 = CalNewYPosition(p->sy2, s->rect.top, recth, shorten);
		p->sy3 = CalNewYPosition(p->sy3, s->rect.top, recth, shorten);

		p->sy1 -= move;
		p->sy3 -= move;
		p->sy2 -= move;
				
		p->sy1a = p->sy1;
		p->sy3a = p->sy3;
	}

	//Re-calculate stroke's rect
	GetStrokeRect(fdl, s->strorder, &(fdl->stroke_buf[ s->strorder ].rect));
	//TODO: Need to re-calculate group's rect?
	Do_SortCollectLines(fdl);
}

static DT_void Do_StrokeAlignRemoveY(pFdlRasterData fdl, DT32_int remove_strorder)
{
	DT32_int i;

//	for(j=0; j < fdl->stroke_line_num; j++)
	for(i=0; i < fdl->stroke_num; i++)
	{
		//PATH_UNIT *pp;
		//pp = fdl->path_buf + fdl->stroke_line_order[j];
		//if(pp->strorder == remove_strorder)
		if(fdl->stroke_order[i] == remove_strorder)
		{
				DT16_short k;
				PATH_UNIT *p=NULL;
				STROKE_UNIT	*s=NULL;
				STROKE_UNIT	spp;
				DT32_long pp_sy01;
				DT32_long pp_rel_h;
				

				DT_memcpy(&spp, fdl->stroke_buf+remove_strorder, sizeof(STROKE_UNIT) );

					pp_sy01 = spp.rect.top;
					//if(fdl->stroke_line_num>0){
					//	p = fdl->path_buf + fdl->stroke_line_order[k];
					//}
//					if(spp.line_num>0){
//						p = fdl->path_buf + spp.line[0];
//					}else{
//						p = NULL;
//					}
//					if(p && p->relation>=0)
//					{
//						pp_rel_h = DT_abs( (*p->sy01) - *(fdl->path_buf[p->relation].sy01) );
//					}else{
//						pp_rel_h = (fdl->stroke_weightX<<fdl->shift)/10;
//					} 
					pp_rel_h = (fdl->stroke_weightX<<fdl->shift)/10;
				
				for(k=0; k < fdl->path_buf_pt_num; k += s->len/*k++*/)
				{
					p = fdl->path_buf + fdl->path_buf_pt[k];
					s = &fdl->stroke_buf[p->strorder];
					if(fdl->group_wrk[ p->strorder ] == 0xFF)
						continue;

					if(p->strorder == remove_strorder){
						continue;
					}
					
					Do_MoveStroke_RemoveAlignY(fdl, s, &spp, pp_sy01, pp_rel_h/*, &pp_copy*/);		
//JACKY_DEBUG_STRORDER_RETURN(16)
//					if(0==s->rect.bottom - s->rect.top){
//						if( s->rect.left >= spp.rect.left &&
//							s->rect.right<= spp.rect.right){
//							Do_RemoveStroke_When_Adjust(fdl,s->strorder,FDL_RESORT_BY_HLINES);
//						}
//					}

				}// end for
				Do_RemoveStroke_When_Adjust(fdl,spp.strorder,FDL_RESORT_BY_HLINES);
				
			break;
		}// end if

	}// end for
}

static DT_void Do_MoveStroke_AlignUpDownY( pFdlRasterData fdl, STROKE_UNIT	*s, DT32_long move_up)
{
	DT32_int i;
	PATH_UNIT *p;

	// re-calculate each path in the stroke s
	for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		p->sy1 -= move_up;
		p->sy3 -= move_up;
		p->sy2 -= move_up;
				
		p->sy1a = p->sy1;
		p->sy3a = p->sy3;
	}

	//Re-calculate stroke's rect
	GetStrokeRect(fdl, s->strorder, &(fdl->stroke_buf[ s->strorder ].rect));
	//TODO: Need to re-calculate group's rect?
	Do_SortCollectLines(fdl);
}

static DT_void Do_StrokeAlignMixY(pFdlRasterData fdl, DT32_int remove_strorder)
{
	DT32_int j, move;

	for(j=0; j < fdl->stroke_line_num; j++)	//loop to fined which stroke.
	{
		PATH_UNIT *pp;
		pp = fdl->path_buf + fdl->stroke_line_order[j];
		if(pp->strorder == remove_strorder)	//remove_stroke found.
		{
			DT16_short k;
			PATH_UNIT *p0;
			STROKE_UNIT	*s;	//current stroke to deal with.
			DT32_long pp_rel_h, p0_rel_h;

			pp_rel_h = 0;
			if(pp->relation >= 0){
				pp_rel_h = *(fdl->path_buf[pp->relation].sy03) - *pp->sy01 ;
			}

			if(pp_rel_h <= 0 || pp_rel_h > 2*(fdl->stroke_weightX<<fdl->shift)/10){
				pp_rel_h = (fdl->stroke_weightX<<fdl->shift)/10;
			}

			p0 = NULL;
			if(j < fdl->stroke_line_num-1){			
				for(k=j+1; k < fdl->stroke_line_num; k++)
				{
					p0 = fdl->path_buf + fdl->stroke_line_order[k];	//find the lower hori-line: p0
					if( fdl->group_wrk[ p0->strorder ] != 0xFF &&
						IsLineOverlayX(*p0->sx01, *p0->sx03, *pp->sx01, *pp->sx03) )
					{
						if(p0->relation>=0){
							p0_rel_h = *(fdl->path_buf[p0->relation].sy03) - *p0->sy01 ;
							if(p0_rel_h > 2*pp_rel_h)
							{
								p0 = NULL;
								continue;
							}
						}
						break;	// p0 found.
					}else p0 = NULL;
				}// end for
			}else{
				p0 = NULL;
			}
			if(p0 == NULL) break;

			//Adjust the stroke of p0 ONLY!! Other stroke won't be adjusted.
			move = (*p0->sy01 - *pp->sy01)/2;	// 1/2 distance between pp & p0
			s = &fdl->stroke_buf[p0->strorder];
			if(move > 0){
				Do_MoveStroke_AlignUpDownY(fdl, s, move);
			}

			//Remove the stroke of pp
			Do_RemoveStroke_When_Adjust(fdl,remove_strorder,FDL_RESORT_BY_HLINES);	//stroke spp
				
			break;	//next remove stroke
		}// end if

	}// end for
}

static DT_void Do_StrokeAlignUpY(pFdlRasterData fdl, DT32_int remove_strorder)
{
	DT32_int j, move;

	for(j=0; j < fdl->stroke_line_num; j++)	//loop to find which stroke.
	{
		PATH_UNIT *pp;
		pp = fdl->path_buf + fdl->stroke_line_order[j];
		if(pp->strorder == remove_strorder)	//remove_stroke found.
		{
			DT16_short k;
			PATH_UNIT *p0;
			STROKE_UNIT	*s;	//current stroke to deal with.
			DT32_long pp_rel_h, p0_rel_h;

			pp_rel_h = 0;
			if(pp->relation >= 0){
				pp_rel_h = *(fdl->path_buf[pp->relation].sy03) - *pp->sy01 ;
			}

			if(pp_rel_h <= 0 || pp_rel_h > 2*(fdl->stroke_weightX<<fdl->shift)/10){
				pp_rel_h = (fdl->stroke_weightX<<fdl->shift)/10;
			}

			p0 = NULL;
			if(j > 0){			
				for(k=j; k > 0; k--)
				{
					p0 = fdl->path_buf + fdl->stroke_line_order[k-1];	//find the lower hori-line: p0
					if( fdl->group_wrk[ p0->strorder ] != 0xFF &&
						IsLineOverlayX(*p0->sx01, *p0->sx03, *pp->sx01, *pp->sx03) )
					{
						if(p0->relation>=0){
							p0_rel_h = *(fdl->path_buf[p0->relation].sy03) - *p0->sy01 ;
							if(p0_rel_h > 2*pp_rel_h)
							{
								p0 = NULL;
								continue;
							}
						}
						break;	// p0 found.
					}else p0 = NULL;
				}// end for
			}else{
				p0 = NULL;
			}
			if(p0 == NULL) break;

			//Adjust the stroke of pp ONLY!! Other stroke won't be adjusted.
			move = (*pp->sy01 - *p0->sy01);	// move pp to p0
			s = &fdl->stroke_buf[pp->strorder];
			if(move > 0){
				Do_MoveStroke_AlignUpDownY(fdl, s, move);
			}
				
			break;	//next remove stroke
		}// end if

	}// end for
}

static DT_void Do_StrokeAlignAllUpY(pFdlRasterData fdl, DT32_int remove_strorder)
{
	DT32_int j, move;

	for(j=0; j < fdl->stroke_line_num; j++)	//loop to find which stroke.
	{
		PATH_UNIT *pp;
		pp = fdl->path_buf + fdl->stroke_line_order[j];
		if(pp->strorder == remove_strorder)	//remove_stroke found.
		{
			DT16_short k, m;
			PATH_UNIT *p0;
			STROKE_UNIT	*spp, *s;	//current stroke to deal with.
			DT32_long pp_rel_h, p0_rel_h;

			pp_rel_h = 0;
			if(pp->relation >= 0){
				pp_rel_h = *(fdl->path_buf[pp->relation].sy03) - *pp->sy01 ;
			}

			if(pp_rel_h <= 0 || pp_rel_h > 2*(fdl->stroke_weightX<<fdl->shift)/10){
				pp_rel_h = (fdl->stroke_weightX<<fdl->shift)/10;
			}

			p0 = NULL;
			if(j > 0){			
				for(k=j; k > 0; k--)
				{
					p0 = fdl->path_buf + fdl->stroke_line_order[k-1];	//find the lower hori-line: p0
					if( fdl->group_wrk[ p0->strorder ] != 0xFF &&
						IsLineOverlayX(*p0->sx01, *p0->sx03, *pp->sx01, *pp->sx03) )
					{
						if(p0->relation>=0){
							p0_rel_h = *(fdl->path_buf[p0->relation].sy03) - *p0->sy01 ;
							if(p0_rel_h > 2*pp_rel_h)
							{
								p0 = NULL;
								continue;
							}
						}
						break;	// p0 found.
					}else p0 = NULL;
				}// end for
			}else{
				p0 = NULL;
			}
			if(p0 == NULL) break;

			move = (*pp->sy01 - *p0->sy01);	// move pp to p0
			if(move <= 0){
				break;
			}

			spp = &fdl->stroke_buf[pp->strorder];
			for(m=0; m < fdl->stroke_num; m++)
			{
				s = &fdl->stroke_buf[m];
				if(fdl->group_wrk[ m ] == 0xFF)
					continue;

				if(s->strorder == spp->strorder){	// do this later.
					continue;
				}
				if(s->rect.top >= spp->rect.top){
					Do_MoveStroke_AlignUpDownY(fdl, s, move);
				}
			}// end for
			Do_MoveStroke_AlignUpDownY(fdl, spp, move);
				
			break;	//next remove stroke
		}// end if

	}// end for
}

static DT_void Do_StrokeAlignDownY(pFdlRasterData fdl, DT32_int remove_strorder)
{
	DT32_int j, move;

	for(j=fdl->stroke_line_num; j > 0; j--)	//loop to fined which stroke.
	{
		PATH_UNIT *pp;
		pp = fdl->path_buf + fdl->stroke_line_order[j-1];
		if(pp->strorder == remove_strorder)	//remove_stroke found.
		{
			DT16_short k;
			PATH_UNIT *p0;
			STROKE_UNIT	*s;	//current stroke to deal with.
			DT32_long pp_rel_h, p0_rel_h;

			pp_rel_h = 0;
			if(pp->relation >= 0){
				pp_rel_h = *(fdl->path_buf[pp->relation].sy03) - *pp->sy01 ;
			}

			if(pp_rel_h <= 0 || pp_rel_h > 2*(fdl->stroke_weightX<<fdl->shift)/10){
				pp_rel_h = (fdl->stroke_weightX<<fdl->shift)/10;
			}

			p0 = NULL;
			if(j < fdl->stroke_line_num-1){			
				for(k=j; k < fdl->stroke_line_num; k++)
				{
					p0 = fdl->path_buf + fdl->stroke_line_order[k];	//find the lower hori-line: p0
					if( fdl->group_wrk[ p0->strorder ] != 0xFF &&
						IsLineOverlayX(*p0->sx01, *p0->sx03, *pp->sx01, *pp->sx03) )
					{
						if(p0->relation>=0){
							p0_rel_h = *(fdl->path_buf[p0->relation].sy03) - *p0->sy01 ;
							if(p0_rel_h > 2*pp_rel_h)
							{
								p0 = NULL;
								continue;
							}
						}
						break;	// p0 found.
					}else p0 = NULL;
				}// end for
			}else{
				p0 = NULL;
			}
			if(p0 == NULL) break;

			//Adjust the stroke of p0 ONLY!! Other stroke won't be adjusted.
			move = (*pp->sy01 - *p0->sy01);
			s = &fdl->stroke_buf[pp->strorder];
			if(move < 0){	// Move down
				Do_MoveStroke_AlignUpDownY(fdl, s, move);
			}
				
			break;	//next remove stroke
		}// end if

	}// end for
}

static DT_void Do_AdjustStrokeY(pFdlRasterData fdl)
{
	DT32_int i, curgroup;
	TRect *rect;
	DT32_int high;
	DT32_int remove_weight/*, last_remove_weight*/;

	if(fdl->weight_modeH >= fdl->hintlistH_num)		//fdl->groupinfo.hintnum)
		fdl->weight_modeH = fdl->hintlistH_num-1;	//fdl->groupinfo.hintnum-1;

	if(fdl->weight_modeH >= 0)
		Do_SortCollectLines(fdl);

	for(i=0; i <= fdl->weight_modeH; i++)	//loop for each stroke that should remove
	{
		remove_weight = fdl->groupinfo.hintlist[i].stroke & ~FDL_ALIGN_MODE;
		if(fdl->group_wrk[remove_weight] == 0xFF){
			continue;
		}
/*		else if(i>0 && fdl->groupinfo.hintlist[i].size==fdl->groupinfo.hintlist[i-1].size){	//multi removed-strokes in one size.
			last_remove_weight = fdl->groupinfo.hintlist[i-1].stroke & ~FDL_ALIGN_MODE;
			//TODO: Following if() is needed only when AlignPack. Is it correct!?
			if( fdl->stroke_buf[ remove_weight ].rect.top == fdl->stroke_buf[ last_remove_weight ].rect.top){
				if(fdl->groupinfo.hintlist[i].stroke & FDL_ALIGN_MODE){
					//continue;
				}else{
					Do_RemoveStroke_When_Adjust(fdl,remove_weight,FDL_RESORT_BY_HLINES);
					continue;
				}
			}
		}
*/
#ifdef FDL_USE_OLD_HINTLIST_H
		else if(i>0 && fdl->groupinfo.hintlist[i].size==fdl->groupinfo.hintlist[i-1].size){	//multi removed-strokes in one size.
			last_remove_weight = fdl->groupinfo.hintlist[i-1].stroke & ~FDL_ALIGN_MODE;
			//TODO: Now, the second AlignPack is skipped, is it right?
			if( (fdl->groupinfo.hintlist[i].stroke & FDL_ALIGN_PACK) &&
				!(fdl->groupinfo.hintlist[i].stroke & FDL_REMOVE_STROKE_MIX_MODE) &&
				fdl->stroke_buf[ remove_weight ].rect.top == fdl->stroke_buf[ last_remove_weight ].rect.top){
				continue;
			}
		}
#endif
		rect = &(fdl->stroke_buf[ remove_weight ].rect);	//remove_weight's stroke rect
		if(rect->bottom > 0)
		{
			high = rect->bottom - rect->top;	//remove_weight stroke rect's height
			curgroup = fdl->group_wrk[ remove_weight ];
			if( (fdl->groupinfo.hintlist[i].stroke & FDL_ALIGN_PACK) && 
				!(fdl->groupinfo.hintlist[i].stroke & FDL_REMOVE_STROKE_MIX_MODE))
			{	// AlignPack
#ifdef FDL_USE_OLD_HINTLIST_H
				Do_StrokeAlignPackY(fdl, remove_weight);	// move & scale the strokes under remove_weight	//20101112
#else
				//Do_StrokeAlignAllUpY(fdl, remove_weight);	// move up all the strokes under remove_weight
				//Do_StrokeAlignUpY(fdl, remove_weight);	// move the lower stroke up
				Do_StrokeAlignPackY(fdl, remove_weight);
#endif
			}else if( !(fdl->groupinfo.hintlist[i].stroke & FDL_ALIGN_PACK) && 
					  !(fdl->groupinfo.hintlist[i].stroke & FDL_REMOVE_STROKE_MIX_MODE))
			{	// Only remove stroke.
#ifdef FDL_USE_OLD_HINTLIST_H
				Do_StrokeAlignRemoveY(fdl, remove_weight);	//20101112
#else
				//Do_RemoveStroke_When_Adjust(fdl,remove_weight,FDL_RESORT_BY_HLINES);
				Do_StrokeAlignRemoveY(fdl, remove_weight);	//20101112
#endif
			}else if( !(fdl->groupinfo.hintlist[i].stroke & FDL_ALIGN_PACK) && 
					  (fdl->groupinfo.hintlist[i].stroke & FDL_REMOVE_STROKE_MIX_MODE))
			{	// Remove and move the lower stroke up (between them)
				Do_StrokeAlignMixY(fdl, remove_weight);
			}else if( (fdl->groupinfo.hintlist[i].stroke & FDL_ALIGN_PACK) && 
					  (fdl->groupinfo.hintlist[i].stroke & FDL_REMOVE_STROKE_MIX_MODE) )
			{
				//Do_StrokeAlignDownY(fdl, remove_weight);	//Reserve the condition
				Do_RemoveStroke_When_Adjust(fdl,remove_weight,FDL_RESORT_BY_HLINES);
			}// end if
			
			//TODO: Re-calculate group's rect?

		}// end if(rect->bottom > 0)
	}// end for(i=0; i <= fdl->weight_modeH; i++)

}// end Do_AdjustStrokeY

// Pre-requirement: All the remove_stroke are vertical path, and relation exists
// Notice: p0 may be a virtual one when center-align.
static DT_void Do_MoveStroke_AlignPackX( pFdlRasterData fdl, STROKE_UNIT	*s,	STROKE_UNIT	*spp, 
									     PATH_UNIT *p0, DT32_long pp_sx01, DT32_long pp_rel_w/*, PATH_UNIT *pp*/)
{
	DT16_short i;
	PATH_UNIT *p=NULL;
	DT32_long tmp, p0_relate, rectw, width, move, shorten;	// move:to left; shorten:;
	DT32_int p0_rel_w, threshold;

	rectw = s->rect.right - s->rect.left;	// width of s->rect
	width = pp_sx01/**pp->sy01*/ - *p0->sx01;
	if(s->rect.left < *p0->sx01){
		move = 0;
		tmp = s->rect.right - *p0->sx01;
		if(tmp<=0){
			shorten = 0;
			return;
		}else if(tmp>width){
			shorten = width;
		}else{
			p0_relate= *p0->sx01;
			if(FDL_PATH_VERT==p0->dir && p0->relation>=0){
				p0_relate = *(fdl->path_buf[p0->relation].sx03);
			}
			if(s->rect.right <= p0_relate){
				shorten = 0;
				return;
			}else{
				shorten = tmp;
			}
		}
	}else if(s->rect.left > pp_sx01/**pp->sy01*/){
		move = width;
		shorten = 0;
	}else{
		move = s->rect.left - (*p0->sx01);
		tmp = pp_sx01/**pp->sy01*/ - s->rect.left;
		if( tmp+pp_rel_w >= rectw ){
			shorten = rectw;
			//if(Is_Rect_rt0_Inside_rt1(&s->rect,&spp->rect)){
			//	Do_RemoveStroke_When_Adjust(fdl, s->strorder, FDL_RESORT_BY_VLINES);
			//	return;
			//}
			if(s->strorder!=p0->strorder){
				if( spp && s->rect.top >= spp->rect.top &&
					s->rect.bottom<= spp->rect.bottom){
					Do_RemoveStroke_When_Adjust(fdl, s->strorder,FDL_RESORT_BY_VLINES);
					return;
				}else{
					shorten = FDL_SHORTEN_VALUE(rectw);	//rectw*9/10;
				}
			}
		}else{
			shorten = tmp;
		}
	}

	if(s->strorder==p0->strorder){
	  p0_rel_w = *p0->sx01;
	  if(FDL_PATH_VERT==p0->dir && p0->relation>=0){
		p0_rel_w = *(fdl->path_buf[p0->relation].sx03);
	  }
	  p0_rel_w -= *p0->sx01;
	  if(p0_rel_w<=0){
		p0_rel_w = pp_rel_w;
	  }
	  threshold = *p0->sx01 + p0_rel_w;
	  
	  for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		if(p->sx1 > threshold){
			p->sx1 = CalNewXPosition(p->sx1, s->rect.left, rectw, shorten);
		}
		if(p->sx2 > threshold){
			p->sx2 = CalNewXPosition(p->sx2, s->rect.left, rectw, shorten);
		}
		if(p->sx3 > threshold){
			p->sx3 = CalNewXPosition(p->sx3, s->rect.left, rectw, shorten);
		}
		p->sx1 -= move;
		p->sx3 -= move;
		p->sx2 -= move;
				
		//p->sy1a = p->sy1;
		//p->sy3a = p->sy3;
	  }
	}else{
	  for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		p->sx1 = CalNewXPosition(p->sx1, s->rect.left, rectw, shorten);
		p->sx2 = CalNewXPosition(p->sx2, s->rect.left, rectw, shorten);
		p->sx3 = CalNewXPosition(p->sx3, s->rect.left, rectw, shorten);

		p->sx1 -= move;
		p->sx3 -= move;
		p->sx2 -= move;
				
		//p->sy1a = p->sy1;			//Not used
		//p->sy3a = p->sy3;			//Not used
	  }
	}

	GetStrokeRect(fdl, s->strorder, &(fdl->stroke_buf[ s->strorder ].rect));
	//TODO: group rect?
	Do_SortCollectVLines(fdl);
}

//Calculate the position at the left side of center stroke
static DT32_long CalNewXPosition_L2C(DT32_long x, DT32_long rcent, DT32_long w, DT32_long shorten)
{
	if(0==shorten){
		return x;
	}
	return (rcent - (rcent-x)*(w-shorten)/w);
} 

static DT_void Do_MoveStroke_AlignPackX_R( pFdlRasterData fdl, STROKE_UNIT	*s,	STROKE_UNIT	*spp_ori,
											PATH_UNIT *p0, /*DT32_long pp_sx01, */DT32_long pp_rel_w,
											DT32_int rel_strorder, DT32_long gap)
{
	DT16_short i;
	PATH_UNIT *p=NULL;
	DT32_long tmp, p0_relate, rectw, width, move, shorten;
	DT32_int p0_rel_w, threshold;
	STROKE_UNIT	*spp=NULL;
	PATH_UNIT *pp=NULL;
	DT32_long pp_sx03;

	rectw = s->rect.right - s->rect.left;	// width of s->rect
	if(rel_strorder>=0){
		spp = &fdl->stroke_buf[rel_strorder];
		if(spp->line_num>0){
		  pp = fdl->path_buf + spp->line[spp->line_num-1];
		  pp_sx03 = *pp->sx03;
		  if(pp->relation>=0){
			pp = fdl->path_buf + pp->relation;
			pp_sx03 = *pp->sx03;
			pp_rel_w = pp_sx03 - *(fdl->path_buf[ spp->line[spp->line_num-1] ].sx01);
		  }
		  width = *p0->sx03 - *pp->sx03;
		}else{
		  width = gap;
		  pp_sx03 = *p0->sx03 - gap;
		}
	}else{
		width = gap;
		pp_sx03 = *p0->sx03 - gap;
	}

	if(s->rect.right > *p0->sx03){
		move = 0;
		tmp = *p0->sx03 - s->rect.left;
		if(tmp<=0){
			shorten = 0;
			return;
		}else if(tmp>width){
			shorten = width;
		}else{
			p0_relate= *p0->sx03;
			if(FDL_PATH_VERT==p0->dir && p0->relation>=0){
				p0_relate = *(fdl->path_buf[p0->relation].sx01);
			}
			if(s->rect.left >= p0_relate){
				shorten = 0;
				return;
			}else{
				shorten = tmp;
			}
		}
	}else if(s->rect.right < pp_sx03/**pp->sy01*/){
		move = width;
		shorten = 0;
	}else{
		move = (*p0->sx03) - s->rect.right;
		tmp = s->rect.right - pp_sx03;
		if( tmp+pp_rel_w >= rectw ){
			shorten = rectw;
			if(s->strorder!=p0->strorder){
				if( spp && spp->rect.top <= s->rect.top &&
					spp->rect.bottom >= s->rect.bottom ){
					Do_RemoveStroke_When_Adjust(fdl, s->strorder, FDL_RESORT_BY_VLINES);
					return;
				}else{
					shorten = FDL_SHORTEN_VALUE(rectw);	//rectw*9/10;
				}
			}
		}else{
			shorten = tmp;
		}
	}

	//////////////////////////-----------------TODO-----------------------/////////////////////////////
	if(s->strorder==p0->strorder){
	  p0_rel_w = pp_rel_w;
	  if(p0->relation>=0){
	    p0_rel_w = *(fdl->path_buf[p0->relation].sx01);	//*p0->sx03;
	    if(FDL_PATH_VERT==p0->dir){
	 	  p0_rel_w = *p0->sx03;		//*(fdl->path_buf[p0->relation].sx01);
		}
	    p0_rel_w -= *(fdl->path_buf[p0->relation].sx01);	//*p0->sx01;
	  }
	  
	  if(p0_rel_w<=0){
		p0_rel_w = pp_rel_w;
	  }
	  threshold = *p0->sx03 - p0_rel_w;
	  
	  for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		if(p->sx1 < threshold){
			p->sx1 = CalNewXPosition_L2C(p->sx1, s->rect.right, rectw, shorten);
		}
		if(p->sx2 < threshold){
			p->sx2 = CalNewXPosition_L2C(p->sx2, s->rect.right, rectw, shorten);
		}
		if(p->sx3 < threshold){
			p->sx3 = CalNewXPosition_L2C(p->sx3, s->rect.right, rectw, shorten);
		}
		p->sx1 += move;
		p->sx3 += move;
		p->sx2 += move;
				
		//p->sy1a = p->sy1;
		//p->sy3a = p->sy3;
	  }
	}else{
	  for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		p->sx1 = CalNewXPosition_L2C(p->sx1, s->rect.right, rectw, shorten);
		p->sx2 = CalNewXPosition_L2C(p->sx2, s->rect.right, rectw, shorten);
		p->sx3 = CalNewXPosition_L2C(p->sx3, s->rect.right, rectw, shorten);

		p->sx1 += move;
		p->sx3 += move;
		p->sx2 += move;
				
		//p->sy1a = p->sy1;			//Not used
		//p->sy3a = p->sy3;			//Not used
	  }
	}

	GetStrokeRect(fdl, s->strorder, &(fdl->stroke_buf[ s->strorder ].rect));
	//TODO:group's rect
	Do_SortCollectVLines(fdl);
}

static DT_void Make_Virtual_p0(PATH_UNIT *p0, DT32_long x, TRect *grprect)
{
	p0->sx1 = p0->sx2 = p0->sx3 = x;
	p0->sy1 = grprect->top;
	p0->sy3 = grprect->bottom;
	p0->sy2 = (p0->sy1 + p0->sy3)/2;
	p0->sx01= &p0->sx1;
	p0->sx03= &p0->sx3;
	p0->sy01= &p0->sy1;
	p0->sy03= &p0->sy3;
	p0->dir = FDL_PATH_VERT;
	p0->relation = -1;
	p0->strorder = -1;
}

static DT_void Do_MoveStroke_AlignPackX_Center( pFdlRasterData fdl, DT32_int aligntype, DT32_int rel_strorder,
											    STROKE_UNIT	*s,	STROKE_UNIT	*spp,
												DT32_long pp_sx01, DT32_long pp_rel_w)
{
	PATH_UNIT	vp0;	// virtual p0;
	PATH_UNIT	*p0, *pc, *pcr;
	DT32_long	grpcenter, center, lcent, rcent, gap, rectw;
	DT32_int curgroup=-1;
	TRect *rect;

	curgroup = FDL_MAIN_GROUP(fdl->group_wrk[s->strorder]) >> (8-MAIN_GROUP_BIT);
	rect = &fdl->main_group_rect[ curgroup ];
	rectw = (rect->right - rect->left);
	if(rectw<=0){
		return;
	}
	grpcenter = rect->left + rectw/2;

	if(aligntype==FDL_ALIGNPACK_X_CENTER_TWO_LINES && rel_strorder<0){
		center = grpcenter;
		lcent = grpcenter - pp_rel_w/2;
		rcent = grpcenter + pp_rel_w/2;
		Make_Virtual_p0(&vp0, lcent, rect);
		p0 = &vp0;
	}else if(aligntype==FDL_ALIGNPACK_X_CENTER_TWO_LINES && rel_strorder>=0){
		center = grpcenter;
		lcent = grpcenter - pp_rel_w/2;
		rcent = grpcenter + pp_rel_w/2;
		Make_Virtual_p0(&vp0, lcent, rect);
		p0 = &vp0;
	}else if(aligntype==FDL_ALIGNPACK_X_CENTER_STROKE){
		if(fdl->HaveCenterStroke<0){
			return;
		}
		pc = &fdl->path_buf[fdl->HaveCenterStroke];
		pcr= &fdl->path_buf[fdl->HaveCenterStrokeR];
		lcent = *pc->sx01;
		rcent = *pcr->sx01;
		center = (lcent + rcent)/2;
		p0 = pc;
	}
	
	gap = DT_abs(pp_sx01  - *p0->sx01);
	if( 0==gap && aligntype==FDL_ALIGNPACK_X_CENTER_STROKE && 
		rel_strorder<0 && p0->strorder==spp->strorder){
		center = grpcenter;
		lcent = grpcenter - pp_rel_w/2;
		rcent = grpcenter + pp_rel_w/2;
		Make_Virtual_p0(&vp0, lcent, rect);
		p0 = &vp0;
		gap = DT_abs(pp_sx01  - *p0->sx01);
	}

	Do_MoveStroke_AlignPackX( fdl, s, spp, p0, pp_sx01, pp_rel_w);
	
	if(p0==&vp0){	//aligntype==FDL_ALIGNPACK_X_CENTER_TWO_LINES
		Make_Virtual_p0(&vp0, rcent, rect);
	}else{			//aligntype==FDL_ALIGNPACK_X_CENTER_STROKE
		p0 = pcr;
	}	
	Do_MoveStroke_AlignPackX_R( fdl, s, spp, p0, /*pp_sx01,*/ pp_rel_w, rel_strorder, gap);
}

DT32_int GetGroupXAlignType(pFdlRasterData fdl, DT32_int remove_strorder, DT32_int centerestidx, DT32_int *rel_strorder, DT32_int group)
{
	DT32_int curgroup=-1, aligntype = FDL_ALIGNPACK_X_LEFT_NEAREST;
	DT32_int k, m, strorder, strorder1, grpcenter, dist_s, dist_s1, xtolerance=0, ytolerance=0;
	STROKE_UNIT *s, *s1;
	PATH_UNIT	*p, *p1, *p_rel;
	TRect *rect;

	if(group>=0){
		curgroup = group >> (8-MAIN_GROUP_BIT);
	}else{
		curgroup = FDL_MAIN_GROUP(fdl->group_wrk[remove_strorder]) >> (8-MAIN_GROUP_BIT);
	}
	rect = &fdl->main_group_rect[ curgroup ];
	grpcenter = rect->left + (rect->right - rect->left)/2;
#ifdef TOLERANCE_X
	xtolerance = TOLERANCE_X;
#endif

#ifdef TOLERANCE_Y
	ytolerance = TOLERANCE_Y;
#endif

	if(centerestidx>=0){
		p = p1 = p_rel = NULL;
		p = &fdl->path_buf[fdl->stroke_line_order[centerestidx]];
		if(*p->sx01 > grpcenter ){
			p1 = p;		p=NULL;
			if(centerestidx>0){
				p  = &fdl->path_buf[fdl->stroke_line_order[centerestidx-1]];
			}
		}else{
			if(centerestidx<fdl->stroke_line_num){
				p1 = &fdl->path_buf[fdl->stroke_line_order[centerestidx+1]];
			}
		}
		if(NULL!=p && NULL!=p1 && p->relation>=0){
			p_rel = &fdl->path_buf[p->relation];
			if( DT_abs( (grpcenter - *p_rel->sx03) - (*p1->sx03 - grpcenter) ) <= xtolerance &&
				DT_abs(*p1->sy01 - *p_rel->sy01) <= ytolerance &&
				DT_abs(*p1->sy03 - *p_rel->sy03) <= ytolerance)
			{
				if(p1->strorder==remove_strorder){
					*rel_strorder = p->strorder;
				}else if(p->strorder==remove_strorder){
					*rel_strorder = p1->strorder;
				}
				aligntype = FDL_ALIGNPACK_X_CENTER_TWO_LINES;
			}
		}

	}

	for(k=0; k < fdl->stroke_num; k++)
	{
		strorder = fdl->stroke_order[k];
		if(fdl->group_wrk[ strorder ] == 0xFF)
			continue;

		s = &fdl->stroke_buf[strorder];

		for(m=k+1; m<fdl->stroke_num; m++){
		  strorder1 = fdl->stroke_order[m];
		  if(fdl->group_wrk[ strorder1 ] == 0xFF)
			continue;

		  s1 = &fdl->stroke_buf[strorder1];
		  if(s->strid == s1->strid){
			if( (s->rect.left<=grpcenter && s1->rect.left<=grpcenter) ||
				(s->rect.left>grpcenter && s1->rect.left>grpcenter)
			  )
			{
				continue;
			}

			if(	DT_abs((s->rect.right-s->rect.left)-(s1->rect.right-s1->rect.left)) <= xtolerance &&
				DT_abs(s->rect.top - s1->rect.top) <= ytolerance &&
				DT_abs(s->rect.bottom - s1->rect.bottom) <= ytolerance)
			{
				if(s1->rect.left<grpcenter){
					dist_s1 = grpcenter - s1->rect.right;
					dist_s	 = s->rect.left - grpcenter;
				}else{
					dist_s1 = s1->rect.left - grpcenter;
					dist_s	 = grpcenter - s->rect.right;
				}
				if(DT_abs(dist_s - dist_s1)<=xtolerance){
					if(s1->strorder==remove_strorder){
						*rel_strorder = s->strorder;
					}else if(s->strorder==remove_strorder){
						*rel_strorder = s->strorder;
					}
					aligntype = FDL_ALIGNPACK_X_CENTER_TWO_LINES;
				}
			}
		  }
		}
	}

	if(fdl->HaveCenterStroke>=0){
		aligntype = FDL_ALIGNPACK_X_CENTER_STROKE;
	}

	*rel_strorder = -1;
	
	return aligntype;
}

static DT_void Do_StrokeAlignPackX(pFdlRasterData fdl, DT32_int remove_strorder, DT32_int centerestidx)
{
	DT32_int j, width, aligntype, rel_strorder=-1;
	PATH_UNIT *p;

	aligntype = GetGroupXAlignType(fdl, remove_strorder, centerestidx, &rel_strorder, -1);

	for(j=0; j < fdl->stroke_line_num; j++)
	{
		PATH_UNIT *pp;
		pp = fdl->path_buf + fdl->stroke_line_order[j];
		if(pp->strorder == remove_strorder)
		{
			DT16_short k;
			PATH_UNIT *p0=NULL;
			STROKE_UNIT	*s=NULL;
			STROKE_UNIT	spp;
			STROKE_UNIT	sppr;
			DT32_long pp_sx01;
			DT32_long pp_rel_w, p0_rel_w;
			//PATH_UNIT pp_copy;	// keep the original pp to get the relationship
			TRect	*grprect;
			DT32_int grpcenter, curgroup=-1;	

			curgroup= FDL_MAIN_GROUP(fdl->group_wrk[remove_strorder]) >> (8-MAIN_GROUP_BIT);
			grprect = &fdl->main_group_rect[ curgroup ];
			grpcenter = grprect->left + (grprect->right - grprect->left)/2;
			
			//DuplicatePATH_UNIT(&pp_copy,pp);
			pp_sx01 = *pp->sx01;
			pp_rel_w = *pp->sx01;
			if(FDL_PATH_VERT==pp->dir && pp->relation>=0){
				pp_rel_w = *(fdl->path_buf[pp->relation].sx03);
			}
			pp_rel_w -= *pp->sx01;

			DT_memcpy(&spp, fdl->stroke_buf+remove_strorder, sizeof(STROKE_UNIT) );

			if(spp.rect.left < (grpcenter-pp_rel_w/2) ){
				aligntype = FDL_ALIGNPACK_X_LEFT_NEAREST;
				rel_strorder = -1;
			}
			
			if(aligntype==FDL_ALIGNPACK_X_LEFT_NEAREST){
				for(k=j; k > 0; k--)
				{
					p0 = fdl->path_buf + fdl->stroke_line_order[k-1];
					if( fdl->group_wrk[ p0->strorder ] != 0xFF && 
						IsVLineOverlayY(p0, pp) ){
						if(*p0->sx01 == pp_sx01){		//TODO:
							p0 = NULL;					//Jacky_20101026:
							continue;					//Jacky_20101026:
							//break;
						}else{
							if(p0->relation>=0){
								p0_rel_w = *(fdl->path_buf[p0->relation].sx03) - *p0->sx01 ;
								if(pp_rel_w>0 && p0_rel_w>2*pp_rel_w){	// avoid to find the wrong p0
									continue;
								}
								break;
							}else{
								continue;	// p0 must be a horizontal line
							}
						}
					}else p0 = NULL;
				}// end for

				if(p0 == NULL) continue;
				width = *pp->sx01 - *p0->sx01;
				Do_ChangeStrokeGroup(fdl, fdl->group_wrk[remove_strorder], fdl->group_wrk[p0->strorder]);
			}
			else if(aligntype==FDL_ALIGNPACK_X_CENTER_TWO_LINES && rel_strorder<0){
				//TODO: Do_ChangeStrokeGroup()
			}else if(aligntype==FDL_ALIGNPACK_X_CENTER_TWO_LINES && rel_strorder>=0){
				DT_memcpy(&sppr, fdl->stroke_buf+rel_strorder, sizeof(STROKE_UNIT) );
				Do_ChangeStrokeGroup(fdl, fdl->group_wrk[remove_strorder], fdl->group_wrk[rel_strorder]);
			}else if(aligntype==FDL_ALIGNPACK_X_CENTER_STROKE){
				if(rel_strorder>=0){
					DT_memcpy(&sppr, fdl->stroke_buf+rel_strorder, sizeof(STROKE_UNIT) );
					Do_ChangeStrokeGroup(fdl, fdl->group_wrk[remove_strorder], fdl->group_wrk[rel_strorder]);
				}
			}

			for(k=0; k < fdl->path_buf_pt_num; k += s->len/*k++*/)
			{
				p = fdl->path_buf + fdl->path_buf_pt[k];
				s = &fdl->stroke_buf[p->strorder];
				if(fdl->group_wrk[ p->strorder ] == 0xFF)
					continue;

				if(p->strorder==remove_strorder || p->strorder==rel_strorder){
					continue;
				}

				if(aligntype==FDL_ALIGNPACK_X_LEFT_NEAREST){
					Do_MoveStroke_AlignPackX(fdl, s, &spp, p0, pp_sx01, pp_rel_w/*, &pp_copy*/);		
				}else{
					Do_MoveStroke_AlignPackX_Center(fdl, aligntype, rel_strorder, s, &spp, pp_sx01, pp_rel_w);
				}
//				if(0==s->rect.right - s->rect.left){
//					if( spp && spp->rect.top <= s->rect.top &&
//						spp->rect.bottom >= s->rect.bottom ){
//						Do_RemoveStroke_When_Adjust(fdl,s->strorder,FDL_RESORT_BY_VLINES);
//					}
//				}
			}// end for

			if(aligntype==FDL_ALIGNPACK_X_LEFT_NEAREST){
				Do_MoveStroke_AlignPackX(fdl, &spp, &spp, p0, pp_sx01, pp_rel_w/*, &pp_copy*/);
			}else{
				Do_MoveStroke_AlignPackX_Center(fdl, aligntype, rel_strorder, &spp, &spp, pp_sx01, pp_rel_w);
				if(rel_strorder>=0){
					Do_MoveStroke_AlignPackX_Center(fdl, aligntype, rel_strorder, &sppr, &spp, pp_sx01, pp_rel_w);
				}
			}
				
			break;
		}// end if

	}// end for
}

static DT_void Do_MoveStroke_RemoveAlignX( pFdlRasterData fdl, STROKE_UNIT	*s,	STROKE_UNIT	*spp, 
										  DT32_long pp_sx01, DT32_long pp_rel_w/*, PATH_UNIT *pp*/)
{
	DT16_short i;
	PATH_UNIT *p=NULL;
	DT32_long rectw, move, shorten;

	rectw = s->rect.right-s->rect.left;	// width of s->rect
	if(s->rect.left <= pp_sx01){
		move = 0;
		shorten = 0;
		if(s->rect.right > (pp_sx01+pp_rel_w) ){
			shorten = pp_rel_w;
		}else if(s->rect.right<=pp_sx01){
			shorten = 0;
			return;
		}else{
			shorten = s->rect.right-pp_sx01;
		}
	}else if(s->rect.left > (pp_sx01+pp_rel_w)){
		move = pp_rel_w;
		shorten = 0;
	}else{
		move = s->rect.left - pp_sx01;
		shorten = pp_rel_w - move;
		if(shorten>=rectw){
			shorten = rectw;
			if( spp && s->rect.top >= spp->rect.top &&
				s->rect.bottom<= spp->rect.bottom){
				Do_RemoveStroke_When_Adjust(fdl, s->strorder,FDL_RESORT_BY_VLINES);
				return;
			}else{
				shorten = FDL_SHORTEN_VALUE(rectw);	//rectw*9/10;
			}
		}
	}

	for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		p->sx1 = CalNewXPosition(p->sx1, s->rect.left, rectw, shorten);
		p->sx2 = CalNewXPosition(p->sx2, s->rect.left, rectw, shorten);
		p->sx3 = CalNewXPosition(p->sx3, s->rect.left, rectw, shorten);

		p->sx1 -= move;
		p->sx3 -= move;
		p->sx2 -= move;
				
		//p->sy1a = p->sy1;			//Not used
		//p->sy3a = p->sy3;			//Not used
	}

	GetStrokeRect(fdl, s->strorder, &(fdl->stroke_buf[ s->strorder ].rect));
	Do_SortCollectVLines(fdl);
}

static DT_void Do_MoveStroke_RemoveAlignX_R(pFdlRasterData fdl, STROKE_UNIT *s, STROKE_UNIT *spp, 
											DT32_long pp_sx01, DT32_long pp_rel_w/*, PATH_UNIT *pp*/)
{
	DT16_short i;
	PATH_UNIT *p=NULL;
	DT32_long rectw, move, shorten;

	rectw = s->rect.right-s->rect.left;	// width of s->rect
	if(s->rect.right >= (pp_sx01+pp_rel_w)){
		move = 0;
		shorten = 0;
		if(s->rect.left < pp_sx01 ){
			shorten = pp_rel_w;
		}else if(s->rect.left >= (pp_sx01+pp_rel_w)){
			shorten = 0;
			return;
		}else{
			shorten = (pp_sx01+pp_rel_w) - s->rect.left;
		}
	}else if(s->rect.right < pp_sx01){
		move = pp_rel_w;
		shorten = 0;
	}else{
		move = pp_sx01+pp_rel_w - s->rect.right;
		shorten = pp_rel_w - move;
		if(shorten>=rectw){
			shorten = rectw;
			if( spp && s->rect.top >= spp->rect.top &&
				s->rect.bottom<= spp->rect.bottom){
				Do_RemoveStroke_When_Adjust(fdl, s->strorder,FDL_RESORT_BY_VLINES);
				return;
			}else{
				shorten = FDL_SHORTEN_VALUE(rectw);	//rectw*9/10;
			}
		}
	}

	for(i=0;i<s->len;i++){
		p = fdl->path_buf + fdl->stroke_buf[s->strorder].start + i;

		p->sx1 = CalNewXPosition_L2C(p->sx1, s->rect.right, rectw, shorten);
		p->sx2 = CalNewXPosition_L2C(p->sx2, s->rect.right, rectw, shorten);
		p->sx3 = CalNewXPosition_L2C(p->sx3, s->rect.right, rectw, shorten);

		p->sx1 += move;
		p->sx3 += move;
		p->sx2 += move;
				
		//p->sy1a = p->sy1;			//Not used
		//p->sy3a = p->sy3;			//Not used
	}

	GetStrokeRect(fdl, s->strorder, &(fdl->stroke_buf[ s->strorder ].rect));
	Do_SortCollectVLines(fdl);
}

static DT_void Do_StrokeAlignRemoveX(pFdlRasterData fdl, DT32_int remove_strorder, DT32_int centerestidx)
{
	DT32_int i, aligntype, rel_strorder=-1;
	DT32_int doRemove=0;	//0:do nothing; 1:L2R; 2:R2L; 3:L2C & R2C

	aligntype = GetGroupXAlignType(fdl, remove_strorder, centerestidx, &rel_strorder, -1);

	for(i=0; i < fdl->stroke_num; i++)
	{
		//pp = fdl->path_buf + fdl->stroke_line_order[j];
		if(fdl->stroke_order[i] == remove_strorder)
		{
				DT16_short k;
				PATH_UNIT *p=NULL;
				STROKE_UNIT	*s=NULL;
				STROKE_UNIT	spp;
				DT32_long pp_sx01;
				DT32_long pp_rel_w;
				TRect	*grprect;
				DT32_int grpcenter, curgroup=-1;
				PATH_UNIT *p_center=NULL;
				//PATH_UNIT pp_copy;	// keep the original pp to get the relationship

				curgroup = FDL_MAIN_GROUP(fdl->group_wrk[remove_strorder]) >> (8-MAIN_GROUP_BIT);
				grprect = &fdl->main_group_rect[ curgroup ];
				grpcenter = grprect->left + (grprect->right - grprect->left)/2;
				
				DT_memcpy(&spp, fdl->stroke_buf+remove_strorder, sizeof(STROKE_UNIT) );

				pp_sx01 = spp.rect.left;
				//if(fdl->stroke_line_num>0){
				//	p = fdl->path_buf + fdl->stroke_line_order[0];
				//}
//				if(spp.line_num>0){
//					p = fdl->path_buf + spp.line[0];
//				}else{
//					p = NULL;
//				}
//				if(p && p->relation>=0)
//				{
//					pp_rel_w = DT_abs( (*p->sx01) - *(fdl->path_buf[p->relation].sx01) );
//				}else{
//					pp_rel_w = (fdl->stroke_weightY<<fdl->shift)/10;
//				} 
				pp_rel_w = (fdl->stroke_weightY<<fdl->shift)/10;

				if(	FDL_ALIGNPACK_X_CENTER_TWO_LINES==aligntype || 
					FDL_ALIGNPACK_X_CENTER_STROKE==aligntype){
					if( FDL_ALIGNPACK_X_CENTER_STROKE==aligntype && fdl->HaveCenterStroke>=0 && 
						fdl->path_buf[fdl->HaveCenterStroke].strorder==remove_strorder){
						doRemove = 3;
						//TODO: pp_sx01 pp_rel_w
						p_center = &fdl->path_buf[fdl->HaveCenterStroke];
						pp_sx01  = *p_center->sx01;
						pp_rel_w = *(fdl->path_buf[fdl->HaveCenterStrokeR].sx01) - pp_sx01;
					}else{
						if(spp.rect.right <= grpcenter){
							doRemove = 1;
						}else if(spp.rect.left > grpcenter){
							doRemove = 2;
						}else{
							doRemove = 3;
						}
					}
				}else{
					doRemove = 2;
				}

				for(k=0; k < fdl->path_buf_pt_num; k += s->len/*k++*/)
				{
					p = fdl->path_buf + fdl->path_buf_pt[k];
					s = &fdl->stroke_buf[p->strorder];
					if(fdl->group_wrk[ p->strorder ] == 0xFF)
						continue;

					if(p->strorder == remove_strorder){
						continue;
					}
					switch(doRemove){
					case 1:
						Do_MoveStroke_RemoveAlignX_R(fdl, s, &spp, pp_sx01, pp_rel_w);
						break;
					case 2:
						Do_MoveStroke_RemoveAlignX(fdl, s, &spp, pp_sx01, pp_rel_w);
						break;
					case 3:
						Do_MoveStroke_RemoveAlignX(fdl, s, &spp, pp_sx01, pp_rel_w);
						Do_MoveStroke_RemoveAlignX_R(fdl, s, &spp, pp_sx01, pp_rel_w);
						break;
					default:
						//do nothing
						break;
					}
//					if(0==s->rect.right - s->rect.left){
//						if( s->rect.top >= spp.rect.top &&
//							s->rect.bottom<= spp.rect.bottom){
//							Do_RemoveStroke_When_Adjust(fdl,s->strorder,FDL_RESORT_BY_VLINES);
//						}
//					}
				}// end for

				Do_RemoveStroke_When_Adjust(fdl,spp.strorder,FDL_RESORT_BY_VLINES);
				if(spp.strorder==fdl->path_buf[fdl->HaveCenterStroke].strorder){
					fdl->HaveCenterStroke = -1;
					fdl->HaveCenterStrokeR= -1;
					fdl->main_group_xtype[ curgroup ] = FDL_ALIGNPACK_X_CENTER_TWO_LINES;
				}
				
				doRemove = 0;
			break;
		}// end if

	}// end for
}

static DT_void Do_AdjustStrokeX(pFdlRasterData fdl)
{
	DT32_int i, curgroup;
	TRect *rect;
	DT32_int width, centerpoint, centerestidx;
	DT32_int remove_weight, last_remove_weight;
	FDL_StrokeHint *Vhintlist;

	if(fdl->weight_modeV >= fdl->hintlistV_num)
		fdl->weight_modeV = fdl->hintlistV_num-1;

	if(fdl->weight_modeV >= 0){
		Do_SortCollectVLines(fdl);
		Vhintlist = fdl->groupinfo.hintlist + fdl->hintlistH_num;
		GetCenterPointInGroup(fdl,&centerpoint);
		CheckStrokeMirrorStatusInGroup(fdl, centerpoint, &centerestidx, 0);
	}

	for(i=0; i <= fdl->weight_modeV; i++)
	{
		remove_weight = Vhintlist[i].stroke & ~FDL_ALIGN_MODE;
		if(fdl->group_wrk[remove_weight] == 0xFF){
			continue;
		}
		else if(i>0 && Vhintlist[i].size==Vhintlist[i-1].size){
			last_remove_weight = Vhintlist[i-1].stroke & ~FDL_ALIGN_MODE;
			if( (fdl->groupinfo.hintlist[i].stroke & FDL_ALIGN_MODE) &&
				fdl->stroke_buf[ remove_weight ].rect.left == fdl->stroke_buf[ last_remove_weight ].rect.left){
				continue;
			}
		}

		rect = &(fdl->stroke_buf[ remove_weight ].rect);
		if(rect->right > 0)
		{
			width = rect->right - rect->left;
			curgroup = fdl->group_wrk[ remove_weight ];
			if((Vhintlist[i].stroke & FDL_ALIGN_PACK)/*FDL_ALIGN_MODE) == FDL_ALIGN_PACK*/)
			{
				Do_StrokeAlignPackX(fdl, remove_weight, centerestidx);
			}else		// Normal remove stroke.
			{
				Do_StrokeAlignRemoveX(fdl, remove_weight, centerestidx);
			}// end if
			//TODO: group's rect
		}// end if(rect->right > 0)
	}// end for(i=0; i <= fdl->weight_modeV; i++)

}// end Do_AdjustStrokeX

DT_void GetStrokeLines(pFdlRasterData fdl, DT32_int strid)
{
	DT32_int i, j;
	DT16_short *line;
	DT8_char IsOK;
	PATH_UNIT *p = fdl->path_buf + fdl->stroke_buf[strid].start;

	line = fdl->stroke_buf[strid].line;
	if(fdl->stroke_buf[strid].stridmap == 2)
	{
		fdl->stroke_buf[strid].line_num = 2;
		line[0] = fdl->stroke_buf[strid].start + 1;
		line[1] = fdl->stroke_buf[strid].start + 8;
	}else
	{
		fdl->stroke_buf[strid].line_num = 0;
		for(i=0; i < fdl->stroke_buf[strid].len; i++, p++)
		{
			if(p->dir == FDL_PATH_HORZ && (p->lock & FDL_PATH_IsRightOrButtom) == 0)
			{
				if(fdl->stroke_buf[strid].line_num <= 0)
				{
					line[ fdl->stroke_buf[strid].line_num++ ] = fdl->stroke_buf[strid].start + i;
				}else
				{
					IsOK=0;
					for(j=0; j < fdl->stroke_buf[strid].line_num; j++)
					{
						if(*p->sy01 < *(fdl->path_buf[ line[j] ].sy01))
						{
							DT_memcpy(fdl->path_tmp_buf, line+j, (fdl->stroke_buf[strid].line_num-j)*sizeof(line[0]));
							line[j] = fdl->stroke_buf[strid].start + i;
							DT_memcpy(line+j+1, fdl->path_tmp_buf, (fdl->stroke_buf[strid].line_num-j)*sizeof(line[0]));
							fdl->stroke_buf[strid].line_num++;
							IsOK = 1;
							break;
						}// end if
					}// end for

					if(IsOK == 0)
						line[ fdl->stroke_buf[strid].line_num++ ] = fdl->stroke_buf[strid].start + i;
				}// end if

			}// end if
		}// end for
	}// end if

}// end GetStrokeLines

DT_void GetStrokeLineType(pFdlRasterData fdl, DT32_int strid)
{
	DT16_short *line;
	PATH_UNIT *p;
	DT32_int w, i, now;

	line = fdl->stroke_buf[strid].line;

	if(fdl->stroke_buf[strid].line_num > 0)
	{
		now = 0;
		w = *fdl->path_buf[line[0]].sx03 - *fdl->path_buf[line[0]].sx01;
		for(i=1; i < fdl->stroke_buf[strid].line_num; i++)
		{
			if(w < (*fdl->path_buf[line[i]].sx03 - *fdl->path_buf[line[i]].sx01))
			{
				w = (*fdl->path_buf[line[i]].sx03 - *fdl->path_buf[line[i]].sx01);
				now = i;
			}// end if
		}// end for
		p = fdl->path_buf + line[now];

		w = (*p->sx03 - *p->sx01);
		if(w > (fdl->recycle << fdl->Frac2))
		{
			if(p->relation >= 0)
			{
				if(fdl->path_buf[ p->relation ].dir == FDL_PATH_HORZ && (*(fdl->path_buf[p->relation].sy03)-*p->sy01 <= w))			// Is it 100% correct ?
				{
					fdl->stroke_buf[strid].line_type = FDL_STROKE_TYPE_HORZ;
				}// end if
			}// end if
		}else fdl->stroke_buf[strid].line_type = FDL_STROKE_TYPE_VERT;
	}// end if

}// end GetStrokeLineType

DT_void GetStrokeVLines(pFdlRasterData fdl, DT32_int strid)
{
	DT32_int i, j, strokew;
	DT16_short *line;
	DT8_char IsOK;
	PATH_UNIT *p = fdl->path_buf + fdl->stroke_buf[strid].start;

	line = fdl->stroke_buf[strid].line;
	if(fdl->stroke_buf[strid].stridmap == 2)
	{
		fdl->stroke_buf[strid].line_num = 2;
		line[0] = fdl->stroke_buf[strid].start + 0;
		line[1] = fdl->stroke_buf[strid].start + 7;
	}else
	{
		fdl->stroke_buf[strid].line_num = 0;
		strokew = (fdl->stroke_weightY << fdl->shift)/10;
		for(i=0; i < fdl->stroke_buf[strid].len; i++, p++)
		{
		
			if(p->dir == FDL_PATH_VERT && (p->lock & FDL_PATH_IsRightOrButtom) == 0 && p->relation >=0)
			//if(p->dir == FDL_PATH_VERT && (p->lock & FDL_PATH_IsRightOrButtom) == 0)
			{
				DT32_int w1, w2;
				w1 = (*p->sy03 - *p->sy01);
				w2 = DT_abs(p->sx1 - *(fdl->path_buf[ p->relation].sx01));
				if((w1 <= strokew && DT_abs(w1 - w2) <= strokew/5) || w1 >= w2)
				//if (p->relation >=0 && ( (*(p->sy03) -(*(p->sy01)) ) > DT_abs(p->sx1 - *(fdl->path_buf[ p->relation].sx01))) )
				{
					if(fdl->stroke_buf[strid].line_num <= 0)
					{
						line[ fdl->stroke_buf[strid].line_num++ ] = fdl->stroke_buf[strid].start + i;
					}else
					{
						IsOK=0;
						for(j=0; j < fdl->stroke_buf[strid].line_num; j++)
						{
							if(*p->sx01 < *(fdl->path_buf[ line[j] ].sx01))
							{
								DT_memcpy(fdl->path_tmp_buf, line+j, (fdl->stroke_buf[strid].line_num-j)*sizeof(line[0]));
								line[j] = fdl->stroke_buf[strid].start + i;
								DT_memcpy(line+j+1, fdl->path_tmp_buf, (fdl->stroke_buf[strid].line_num-j)*sizeof(line[0]));
								fdl->stroke_buf[strid].line_num++;
								IsOK = 1;
								break;
							}// end if
						}// end for

						if(IsOK == 0)
							line[ fdl->stroke_buf[strid].line_num++ ] = fdl->stroke_buf[strid].start + i;
					}// end if
				}
			}// end if
		}// end for
	}// end if

}// end GetStrokeVLines

DT_void GetStrokeVLineType(pFdlRasterData fdl, DT32_int strid)
{
	DT16_short *line;
	PATH_UNIT *p;
	DT32_int w;
	DT32_int i;

	line = fdl->stroke_buf[strid].line;

	for(i=0;i<fdl->stroke_buf[strid].line_num; i++)
	{
		p = fdl->path_buf + line[i];
		w = (*p->sy03 - *p->sy01);
		if(w > (fdl->recycle << fdl->Frac2))
		{
			if(p->relation >= 0)
			{
				if(fdl->path_buf[ p->relation ].dir == FDL_PATH_VERT && (*(fdl->path_buf[p->relation].sx03)-*p->sx01 <= w))			// Is it 100% correct ?
				{
					fdl->stroke_buf[strid].line_type = FDL_STROKE_TYPE_VERT;
					break;
				}// end if
			}// end if
		}else fdl->stroke_buf[strid].line_type = FDL_STROKE_TYPE_HORZ;
	}// end if

}// end GetStrokeVLineType

static DT_void ScaleStroke(pFdlRasterData fdl, DT32_int stroke, DT32_int sizew, DT32_int sizeh)
{
	DT32_int i;
	PATH_UNIT *p;

	if(sizeh > 0)
	{
		p = fdl->path_buf + fdl->stroke_buf[stroke].start;
		for(i=0; i < fdl->stroke_buf[stroke].len; i++, p++)
		{
			p->sy1 = (p->sy1 * sizeh)/100;
			p->sy2 = (p->sy2 * sizeh)/100;
			p->sy3 = (p->sy3 * sizeh)/100;
		}// end for
	}// end if

	// ========================================================================
	if(sizew > 0)
	{
		p = fdl->path_buf + fdl->stroke_buf[stroke].start;
		for(i=0; i < fdl->stroke_buf[stroke].len; i++, p++)
		{
			p->sx1 = (p->sx1 * sizew)/100;
			p->sx2 = (p->sx2 * sizew)/100;
			p->sx3 = (p->sx3 * sizew)/100;
		}// end for
	}// end if

}// end ScaleStroke

DT_void Do_MoveStrokeUpDown(pFdlRasterData fdl, DT32_int stroke, DT32_int move)
{
	DT32_int i;
	PATH_UNIT *p;

	p = fdl->path_buf + fdl->stroke_buf[stroke].start;
	for(i=0; i < fdl->stroke_buf[stroke].len; i++, p++)
	{
		p->sy1 += move;
		p->sy2 += move;
		p->sy3 += move;
	}// end for
}// end Do_MoveStrokeUpDown

static DT_void Do_SCurve2MoveY(pFdlRasterData fdl, DT32_int move, DT32_int lineorder, DT32_long sy, DT32_int n, DT32_int group, DT32_int force , DT32_long left, DT32_long right)
{
	DT32_int i, j, k, domove;
	PATH_UNIT *p = fdl->path_buf;

	PATH_UNIT *p0,*p0_r,*p1,*pk;
	DT32_int org_sx1,org_sy1,org_sx3,org_sy3;
	DT32_int org_top,org_bottom;
	DT32_int idx_clip_path[2];

	TRect rect, rect0;
	DT32_long max;
	DT32_int b_find_line=0, b_upward=0;

	DT32_long half_pixel = (1<< (fdl->shift-1));
	p0= fdl->path_buf+lineorder;
	p0_r = fdl->path_buf+ p0->relation;

	org_top = p0->sy1;
	org_bottom = p0_r->sy1;

	org_sx1 = p0->sx1;
	org_sy1 = p0->sy1;
	org_sx3 = p0->sx3;
	org_sy3 = p0->sy3;

	GetStrokeRect(fdl, p0->strorder, &rect0);
    if (p0->sy1> p0_r->sy1)
	{
		rect0.top = p0_r->sy1;
		rect0.bottom = p0->sy1;
	}
	else{
		rect0.top = p0->sy1;
		rect0.bottom = p0_r->sy1;
	}
	
	//re-connect the divided path.
	//p = fdl->path_buf;
	//for(i=0; i < fdl->path_num; i++, p++)
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		domove = 0;
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if( (p->sx1 == org_sx1 && p->sy1 == org_sy1)
			|| (p->sx1 == org_sx3 && p->sy1 == org_sy3) )
		{
			p->lock |= FDL_PATH_LOCK_sy1;
			p->sy1+=move;
			domove +=move;

		}

		if( (p->sx3 == org_sx1 && p->sy3 == org_sy1)
			|| (p->sx3 == org_sx3 && p->sy3 == org_sy3))
		{
			p->lock |= FDL_PATH_LOCK_sy3;
			p->sy3+=move;
			domove +=move;
		}
		p->sy2+= domove/2;
	}

	/*lock between the path of line as the bottom path is moving.*/
	if(org_top> org_bottom)
	{
		for(i=0; i<fdl->path_buf_pt_num; i++)
		{	
			p = fdl->path_buf + fdl->path_buf_pt[i];
			if((left <= *p->sx01) && (*p->sx03 <= right ))
			{
				domove = 0;
				if( ((p->lock & FDL_PATH_LOCK_sy1) == 0) && (org_bottom<p->sy1) && (org_top> p->sy1))
				{
						domove += (p0_r->sy1 - p->sy1);
						p->sy1 = p0_r->sy1;
						p->lock |= FDL_PATH_LOCK_sy1;
				}
				if( ((p->lock & FDL_PATH_LOCK_sy3) == 0) && (org_bottom< p->sy3) && (org_top > p->sy3))
				{
						domove += (p0_r->sy1 - p->sy3);
						p->sy3 = p0_r->sy1;
						p->lock |= FDL_PATH_LOCK_sy3;
				}
				p->sy2+= domove/2;
			}
		}
	}

	p = fdl->path_buf + fdl->stroke_buf[p0->strorder].start;
	for(i=0; i<fdl->stroke_buf[p0->strorder].len; i++, p++)
	{
		if(p->subidx != p0->subidx)
		{
			domove = 0;
			if( ((p->lock & FDL_PATH_LOCK_sy1) == 0) && (org_top < p->sy1) && (p->sy1 < org_bottom+ half_pixel))
			{
					p->lock |= FDL_PATH_LOCK_sy1;
					p->sy1+=move;
					domove +=move;
			}

			if( ((p->lock & FDL_PATH_LOCK_sy3) == 0) &&(org_top<p->sy3) && (p->sy3 < org_bottom+ half_pixel) )
			{
					p->lock |= FDL_PATH_LOCK_sy3;
					p->sy3+=move;
					domove +=move;
			}
			p->sy2+= domove/2;
		}
	}

	//p = fdl->path_buf;
	//for(i=0; i<fdl->path_num; i++, p++)
	for(i=0; i<fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(p->dir == FDL_PATH_HORZ && ((p->lock & FDL_PATH_LOCK_sy1)==0) & (p->sy1 < sy ))
		{
			b_find_line=0;
			for(j=0; j < fdl->stroke_line_num; j++)
			{
				p0= fdl->path_buf+fdl->stroke_line_order[j];
				if(fdl->path_buf_pt[i] == fdl->stroke_line_order[j] || p0->relation == fdl->path_buf_pt[i])
				{
					b_find_line =1;
					break;
				}
			}
			
			if(b_find_line==1)
				continue;

			org_sx1 = p->sx1;
			org_sy1 = p->sy1;
			org_sx3 = p->sx3;
			org_sy3 = p->sy3;

			//check upward or downward.
			if(fdl->path_buf_pt[i] == fdl->path_num-1)
			{
				idx_clip_path[0] = 0;
				idx_clip_path[1] = fdl->path_num-2;
			}
			else if(fdl->path_buf_pt[i] == 0)
			{
				idx_clip_path[0] = fdl->path_num-1;
				idx_clip_path[1] = 2;
			}
			else{
				idx_clip_path[0] = fdl->path_buf_pt[i]-1;
				idx_clip_path[1] = fdl->path_buf_pt[i]+1;
			}

			b_upward = 0;
			for(j=0; j<2; j++)
			{
				p1 = fdl->path_buf+idx_clip_path[j];
			
				if((p1->sx1 ==  org_sx1 && p1->sy1 ==  org_sy1)
					 || (p1->sx1 ==  org_sx3 && p1->sy1 ==  org_sy3))
				{
					(p1->sy3 > p1->sy1) ? (b_upward = 0) :(b_upward = 1);
					 break;
				}
				if( (p1->sx3 ==  org_sx3 && p1->sy3 ==  org_sy3)
					 || (p1->sx3 ==  org_sx1 && p1->sy3 ==  org_sy1))
				{
					(p1->sy3 > p1->sy1) ? (b_upward = 1) :(b_upward = 0);
					 break;
				}
			}
		    if(b_upward==1)
			{
				b_find_line=0;
				for(j=fdl->stroke_line_num-1; j >=0 ; j--)
				{
					p0 = fdl->path_buf+fdl->stroke_line_order[j];
					p0_r = fdl->path_buf + p0->relation;
					if( (p0_r->sy1 < p->sy1)
						&& (*p0->sx01<= *p->sx01 || *p0_r->sx01<= *p->sx01)
						&& (*p->sx03 <= *p0->sx03 || *p->sx03 <= *p0_r->sx03))
					{
						b_find_line = 1;
						break;
					}

					if( (p0_r->sy1 >= p->sy1) && (p0->sy1 <= p->sy1) 
						&& (*p0->sx01<= *p->sx01 || *p0_r->sx01<= *p->sx01)
						&& (*p->sx03 <= *p0->sx03 || *p->sx03 <= *p0_r->sx03))
					{
						b_find_line = 2;
						break;
					}
				}

				p->sy1+=move;
				if(b_find_line == 1)
				{	
					if( p->sy1 > p0_r->sy1 + (1 <<fdl->shift))
					{
						p->sy1+=half_pixel;
						p->sy1>>= fdl->shift;
						p->sy1<<= fdl->shift;
					}
					else{
						p->sy1 = p0_r->sy1 + (1 <<fdl->shift);
					}
				}
				if(b_find_line == 2)
				{
					    p->sy1 = p0->sy1; 
				}
				else{
					;
				}
			}
			else{
				
				if(sy > p->sy1 + (1 <<fdl->shift) ) 
				{
					p->sy1+=move;
					p->sy1+=half_pixel;
					p->sy1>>= fdl->shift;
					p->sy1<<= fdl->shift;
				}
				else
				{
					p->sy1 = sy + move - (1 << fdl->shift);
					if(p->sy1 <0) p->sy1 = 0;
				}
			}
		
			p->sy3 = p->sy1;
			p->lock |= (FDL_PATH_LOCK_sy1|FDL_PATH_LOCK_sy3);

			//p1 = fdl->path_buf;
			//for(j=0; j<fdl->path_num; j++, p1++)
			for(j=0; j<fdl->path_buf_pt_num; j++)
			{
				p1 = fdl->path_buf + fdl->path_buf_pt[j];
				domove = 0;
				if( (p1->sx1 == org_sx1 && p1->sy1 == org_sy1)
					|| (p1->sx1 == org_sx3 && p1->sy1 == org_sy3) )
				{
					p1->lock |= FDL_PATH_LOCK_sy1;
					domove += (p->sy1-p1->sy1);
					p1->sy1 = p->sy1;
				}

				if( (p1->sx3 == org_sx1 && p1->sy3 == org_sy1)
					|| (p1->sx3 == org_sx3 && p1->sy3 == org_sy3))
				{
					p1->lock |= FDL_PATH_LOCK_sy3;
					domove += (p->sy3 -p1->sy1);
					p1->sy3= p->sy1;
				}
				p1->sy2+= domove/2;
			}
		}
		
		else if(p->dir != FDL_PATH_HORZ
				&& ( (p->lock & FDL_PATH_LOCK_sy1)==0 || (p->lock & FDL_PATH_LOCK_sy3)==0) && (p->sy1 <sy ) )
		{

				b_find_line=1;
				max = 0;
				p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(j=0; j<fdl->stroke_buf[p->strorder].len; j++, p1++)
				{
					if (p->subidx != p1->subidx)
					{
						continue;
					}
					else if(p1->sy1 > sy || p1->sy3 >sy || p1->dir == FDL_PATH_HORZ)
					{
						b_find_line=0;
						break;
					}
					else{
						if(*p1->sx03 > max )
						{
							max = *p1->sx03;
						}
					}
				}
				if(b_find_line > 0)
				{
					p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
					for(j=0; j<fdl->stroke_buf[p->strorder].len; j++, p1++)
					{
						if(p->subidx == p1->subidx)
						{
								pk = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
								for(k=0; k<fdl->stroke_buf[p->strorder].len; k++, pk++)
								{
									if(p1->subidx != pk->subidx)
									{
										if( max >= pk->sy1)
										{
											pk->lock |= FDL_PATH_LOCK_sy1;
										}
										if( max >= pk->sy3)
										{
											pk->lock |= FDL_PATH_LOCK_sy3;
										}
									}
								}
								p1->lock |= FDL_PATH_LOCK_sy1;
								p1->lock |= FDL_PATH_LOCK_sy3;
						}
			}
		}
		}else;
	}


	org_bottom = p0_r->sy1;

//	if(move != 0) // must disable it ,because must enable lock.
	{
		for(j=0; j < fdl->stridcnt; j++)
		{
			DT32_int crossover=0;
//			DT32_int middle;
/*#ifdef CHECK_SUB_GROUP
			if(fdl->group_wrk[j] != group)
				continue;
#else
			if(fdl->group_wrk[j] == 0xFF)
				continue;
#endif*/

			if(fdl->group_wrk[j] != group)
				continue;
			GetStrokeRect(fdl, j, &rect);
//			middle = (rect.right+rect.left)/2;
//			if( !(*p0->sx01 <= middle && middle <= *p0->sx03) )
//				continue;

//			if( !IsLineOverlayX(*p0->sx01, *p0->sx03, rect.left, rect.right) )
//				continue;

			if(rect.bottom < n)
				continue;

			if( (rect.bottom < rect0.top) || (rect.top > rect0.bottom))
			{
				crossover = 0;
			}else
			{
				crossover = 1;
			}

			p = fdl->path_buf + fdl->stroke_buf[j].start;
			if(crossover == 1 && fdl->stroke_buf[j].stridmap == 44)
			{
				DT32_int high1 = rect.bottom - rect.top;
				DT32_int high2 = high1 + move;

				for(i=0; i < fdl->stroke_buf[j].len; i++, p++)
				{
					if(!(i <= 1 || i == 5)) continue;
					if(p->dir == FDL_PATH_HORZ)
					{
						if(p->sy1 >= n || crossover)
						{
							if((p->lock & FDL_PATH_TMPLOCK_s1) == 0)
							{
								if((p->lock & FDL_PATH_LOCK_sy1) == 0)
								{
									if( p->sy1<org_bottom && crossover)
										p->lock |= FDL_PATH_TMPLOCK_s1; 

									if(sy == p->sy1)
										p->lock |= (FDL_PATH_LOCK_sy1 | FDL_PATH_LOCK_sy3);
									p->sy1 += move;
									p->sy3 = p->sy1;
								}// end if
							}
						}// end if
					}else
					{
						domove = 0;
						if(p->sy3 >= n || crossover)									// Have some bug in code 0x6FA4 at 23 pixels.
						{
							if((p->lock & FDL_PATH_TMPLOCK_s3) == 0)
							{
								if((p->lock & FDL_PATH_LOCK_sy3) == 0)
								{
									if( p->sy3<org_bottom && crossover)
										p->lock |= FDL_PATH_TMPLOCK_s3; 

									if(sy == p->sy3)
										p->lock |= FDL_PATH_LOCK_sy3;
									p->sy3 += move;
									domove += move;
								}// end if
							}
						}// end if

						if(p->sy1 >= n || crossover)
						{
							if((p->lock & FDL_PATH_TMPLOCK_s1) == 0)
							{
								if((p->lock & FDL_PATH_LOCK_sy1) == 0)
								{
									if( p->sy1<org_bottom && crossover)
										p->lock |= FDL_PATH_TMPLOCK_s1;  

									if(sy == p->sy1)
										p->lock |= FDL_PATH_LOCK_sy1;
									p->sy1 += move;
									domove += move;
								}// end if
							}
						}// end if

						p->sy2 += domove/2;
					}// end if
				}// end for

				p = fdl->path_buf + fdl->stroke_buf[j].start;
				for(i=3; i < fdl->stroke_buf[j].len; i++)
				{
					if(i == 5 || i == 6)continue;
					p[i].sy1 = rect.top + (p[i].sy1 - rect.top)*high2/high1;
					p[i].sy2 = rect.top + (p[i].sy2 - rect.top)*high2/high1;
					p[i].sy3 = rect.top + (p[i].sy3 - rect.top)*high2/high1;
				}// end for

				*(p[2].sy01) = p[1].sy3;
				*(p[6].sy01) = p[5].sy3;
				p[2].sy3 = p[3].sy1;
				p[6].sy3 = p[7].sy1;

			}else if(crossover == 1 && (fdl->stroke_buf[j].stridmap == 46 || fdl->stroke_buf[j].stridmap == 6
				|| fdl->stroke_buf[j].stridmap == 136 || fdl->stroke_buf[j].stridmap == 131 || fdl->stroke_buf[j].stridmap == 132
				|| fdl->stroke_buf[j].stridmap == 151 || fdl->stroke_buf[j].stridmap == 88 || fdl->stroke_buf[j].stridmap == 139
				|| fdl->stroke_buf[j].stridmap == 29 || fdl->stroke_buf[j].stridmap == 74
				))
			{
				DT32_int high1 = rect.bottom - rect.top;
				DT32_int high2 = high1 + move;
				if(high1 > -move)
				{
					for(i=0; i < fdl->stroke_buf[j].len; i++)
					{
						p[i].sy1 = rect.top + (p[i].sy1 - rect.top)*high2/high1;
						p[i].sy2 = rect.top + (p[i].sy2 - rect.top)*high2/high1;
						p[i].sy3 = rect.top + (p[i].sy3 - rect.top)*high2/high1;
					}// end for
				}// end if
			}else if(fdl->stroke_buf[j].stridmap == 195)
			{
				DT32_int high1 = rect.bottom - rect.top;
				DT32_int high2 = high1 + move;
				if(high1 > -move)
				{
					//DumpDebugString("  move2 %d\n", move);
					if((fdl->path_buf+lineorder) == (p+3)) 
					{
						for(i=6; i < 8; i++)
						{
							p[i].sy1 += move;
							p[i].sy2 += move;
							p[i].sy3 += move;
						}// end for
						for(i=10; i < 11; i++)
						{
							p[i].sy1 += move;
							p[i].sy2 += move;
							p[i].sy3 += move;
						}// end for
						p[4].sy3 = (p[1].sy1 + p[3].sy1)>>1;
						p[8].sy3 += (p[4].sy3-p[5].sy1);

						p[5].sy2 += ((p[4].sy3-p[5].sy1)>>1);
						p[5].sy1 = p[4].sy3;
						p[5].sy3 += move;

						p[9].sy2 += ((p[8].sy3- p[9].sy1)>>1);
						p[9].sy1 = p[9].sy1;
						p[9].sy3 += move;

					}
					else if((fdl->path_buf+lineorder) == (p+1))
					{
						p[0].sy3 += move;
						p[2].sy3 += move;
						p[3].sy1 += move;
						p[3].sy2 += move;
						p[3].sy3 += move;
						p[4].sy3 += move;

						for(i=5; i < 8; i++)
						{
							p[i].sy1 += move;
							p[i].sy2 += move;
							p[i].sy3 += move;
						}// end for

						p[8].sy3 += move;
						for(i=9; i < 11; i++)
						{
							p[i].sy1 += move;
							p[i].sy2 += move;
							p[i].sy3 += move;
						}// end for
					}
					else if(crossover == 1)
					{
						p[4].sy2 = rect.top + (p[4].sy2 - rect.top)*high2/high1;
						p[4].sy3 = rect.top + (p[4].sy3 - rect.top)*high2/high1;
						p[8].sy2 = rect.top + (p[8].sy2 - rect.top)*high2/high1;
						p[8].sy3 = rect.top + (p[8].sy3 - rect.top)*high2/high1;
						for(i=5; i < fdl->stroke_buf[j].len; i++)
						{
							if(i == 8) continue;
							p[i].sy1 = rect.top + (p[i].sy1 - rect.top)*high2/high1;
							p[i].sy2 = rect.top + (p[i].sy2 - rect.top)*high2/high1;
							p[i].sy3 = rect.top + (p[i].sy3 - rect.top)*high2/high1;
						}// end for
					}
					else
					{
						for(i=0; i < fdl->stroke_buf[j].len; i++)
						{
							p[i].sy1 += move;
							p[i].sy2 += move;
							p[i].sy3 += move;
						}// end for
					}// end if
				}// end if
			}else
			{
				for(i=0; i < fdl->stroke_buf[j].len; i++, p++)
				{
					if(p->dir == FDL_PATH_HORZ)
					{
						if(p->sy1 >= n || crossover)
						{
							if((p->lock & FDL_PATH_TMPLOCK_s1) == 0)
							{
								if((p->lock & FDL_PATH_LOCK_sy1) == 0)
								{
									if( p->sy1<org_bottom && crossover)
											p->lock |= FDL_PATH_TMPLOCK_s1; 

									if(sy == p->sy1)
										p->lock |= (FDL_PATH_LOCK_sy1 | FDL_PATH_LOCK_sy3);
									p->sy1 += move;
									p->sy3 = p->sy1;
								}// end if
							}
						}// end if
					}else
					{
						domove = 0;
						if(p->sy3 >= n || crossover)									// Have some bug in code 0x6FA4 at 23 pixels.
						{
							if((p->lock & FDL_PATH_TMPLOCK_s3) == 0)
							{
								if((p->lock & FDL_PATH_LOCK_sy3) == 0)
								{
									if( p->sy3<org_bottom && crossover)
										p->lock |= FDL_PATH_TMPLOCK_s3; 

									if(sy == p->sy3)
										p->lock |= FDL_PATH_LOCK_sy3;

									if((p->lock & FDL_PATH_TMPLOCK_s1) != 0 
										&& org_bottom < org_top
										&&( (p->sy3 > p->sy1 && p->sy3+move <= p->sy1) 
											|| (p->sy1 > p->sy3 && p->sy3+move >= p->sy1))
										)
									{
										pk = fdl->path_buf + fdl->stroke_buf[j].start;
										for(k=0; k<fdl->stroke_buf[j].len; k++, pk++)
										{
											if(pk->sy1a == p->sy3a && pk->sx1 == p->sx3)
											{
												pk->sy1 = p->sy3;
												pk->lock |= FDL_PATH_TMPLOCK_s1;
											}
											if(pk->sy3a == p->sy3a && pk->sx3 == p->sx3)
											{
											    pk->sy3 = p->sy3;
											   	pk->lock |= FDL_PATH_TMPLOCK_s3;
											}
										}
										p->lock |= FDL_PATH_TMPLOCK_s3;
									}
									else{
									p->sy3 += move;
									domove += move;
								}// end if
							}
							}
						}// end if

						if(p->sy1 >= n || crossover)
						{
							if((p->lock & FDL_PATH_TMPLOCK_s1) == 0)
							{
								if((p->lock & FDL_PATH_LOCK_sy1) == 0)
								{
									if( p->sy1<org_bottom && crossover)
											p->lock |= FDL_PATH_TMPLOCK_s1;  

									if(sy == p->sy1)
										p->lock |= FDL_PATH_LOCK_sy1;


									if((p->lock & FDL_PATH_TMPLOCK_s3) != 0 
										&& org_bottom < org_top
										&&( (p->sy1 > p->sy3 && p->sy1+move <= p->sy3) 
											|| (p->sy1 < p->sy3 && p->sy1+move >= p->sy3))
									  )
									{

										if( (p->sy1a > p->sy3a && p->sy1 <=p->sy3)
											|| (p->sy1a <p->sy3a && p->sy1 >=p->sy3)
											)
										{
											p->sy1 += move;
											domove += move;
										}

										pk = fdl->path_buf + fdl->stroke_buf[j].start;
										for(k=0; k<fdl->stroke_buf[j].len; k++, pk++)
										{
											if(pk->sy1a == p->sy1a && pk->sx1 == p->sx1)
											{
												pk->sy1 = p->sy1;
												pk->lock |= FDL_PATH_TMPLOCK_s1;
											}
											if(pk->sy3a == p->sy1a && pk->sx3 == p->sx1)
											{
											    pk->sy3 = p->sy1;
											   	pk->lock |= FDL_PATH_TMPLOCK_s3;
											}
										}
										p->lock |= FDL_PATH_TMPLOCK_s1;
									}
									else
									{
									p->sy1 += move;
									domove += move;
									}
								}// end if
							}
						}// end if

						p->sy2 += domove/2;
					}// end if
				}// end for

			}// end if

		}// end for
	}// end if

}// end Do_SCurve2MoveY


DT_void Do_AlignStrokeLineH(pFdlRasterData fdl, DT32_int lineorder, DT32_int last_line, DT32_int org_line, DT32_int i_1)
{
	DT32_int i;
	DT32_int y1, y2, newy1, offsety;
	PATH_UNIT *p, *p0, *p1, *pi1;
	DT32_long left, right;
	

	//for(i=0; i< fdl->path_num; i++)
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		p->lock &= ~ (FDL_PATH_TMPLOCK_s1| FDL_PATH_TMPLOCK_s3);
	}

	p = fdl->path_buf + lineorder;
	p0 = fdl->path_buf + p->relation; 
	(*p->sx01 < p0->sx1) ? (left = *p->sx01): (left = p0->sx1);
	(*p->sx03 > p0->sx3) ? (right = *p->sx03): (right = p0->sx3);
	
	if(i_1>=0)
	{
		pi1 =  fdl->path_buf + fdl->stroke_line_order[i_1+2];
		p1 = fdl->path_buf+pi1->relation;
		if(pi1->sy1 == p->sy1 && p0->sy1 == p1->sy1)
		{
			if(left > (*pi1->sx01)) {left = *pi1->sx01; }
			if(left > *p1->sx01) {left = *p1->sx01; }
			if(right < *pi1->sx03) {right = *pi1->sx03; }
			if(right < *pi1->sx03) {right = *p1->sx03; }
		}
	}

	if(last_line < 0)
	{
		p->lock |= (FDL_PATH_LOCK_sy1 | FDL_PATH_LOCK_sy3);
		y1 = (p->sy1) >> fdl->Frac2;
		y1 = y1 & ~fdl->recycle;
		newy1 = (y1 << fdl->Frac2);
		
		if(i_1>=0)
		{
			pi1 =  fdl->path_buf + fdl->stroke_line_order[i_1];
			pi1 = fdl->path_buf + pi1->relation; 
			if( (pi1->sy1+ (1<<fdl->Frac2) ) > newy1)
			{
					newy1 = pi1->sy1 + (1<<fdl->Frac2);
					y1 = (newy1 >> fdl->Frac2);
			}
		}
		offsety = newy1 - p->sy1;
		Do_SCurve2MoveY(fdl, offsety, lineorder,p->sy1, p->sy1, fdl->group_wrk[p->strorder], 1 , left, right);
		//p->sy1 += offsety;
		//p->sy3 += offsety;
	}else
	{
		p0 = fdl->path_buf + fdl->stroke_line_order[last_line];

		p->lock |= (FDL_PATH_LOCK_sy1 | FDL_PATH_LOCK_sy3);
		y1 = (p->sy1) >> fdl->Frac2;
		y1 = y1 & ~fdl->recycle;
		y2 = (p0->sy1) >> fdl->Frac2;

		//
		if(y1 - y2 <= (fdl->recycle+1)*(fdl->stroke_weightX + fdl->stroke_weightXSpace)/10)
			y1 = y2 + (fdl->recycle+1)*(fdl->stroke_weightX + fdl->stroke_weightXSpace)/10;
		//else if(y1 - y2 > ((p->sy1 - org_line) >> fdl->Frac2))
		//	y1 = y2 + (((p->sy1 - org_line) >> fdl->shift) << fdl->recycleshift);

		newy1 = (y1 << fdl->Frac2);
		
		if(last_line != i_1)
		{
			pi1 =  fdl->path_buf + fdl->stroke_line_order[i_1];
			if( (( p->sy1 - pi1->sy1) < (1<<fdl->shift)) && ( (p->sy1 - pi1->sy1) > (1<< (fdl->shift-1))) )
			{
				p0 =  fdl->path_buf + p->relation;
				pi1 = fdl->path_buf + pi1->relation;
				
				for(i=0; i < fdl->path_buf_pt_num; i++)
				{
					p1 = fdl->path_buf + fdl->path_buf_pt[i];
					if(pi1->sy1< p1->sy1 && p1->sy1 < p0->sy1 &&  *p1->sx01 > *pi1->sx01 && *pi1->sx03 > *p1->sx03 )
					{
						newy1 += (1 << fdl->shift);
						y1 = (newy1 >> fdl->Frac2);
						break;
					}
				}
			}
			else if(pi1->sy1> newy1)
			{
					newy1 = pi1->sy1;
					y1 = (newy1 >> fdl->Frac2);
			}
		}else
		{
		
			for(i=0; i < fdl->path_buf_pt_num; i++)
			{
				p1 = fdl->path_buf + fdl->path_buf_pt[i];
				if( (*p->sx01 < *p1->sx01) &&  (*p1->sx03 < *p->sx03)  
					&& (p1->dir != FDL_PATH_VERT) && (p1->dir != FDL_PATH_HORZ) )
				{
					if( p1->sy1<p->sy1 
						&& p1->sy3<p->sy1 
						&& ( ((p1->sy1 >>fdl->shift) >= (newy1>>fdl->shift))
							|| ( (p1->sy3 >>fdl->shift) >= (newy1>>fdl->shift))
						  ) 
					  )
					{
						newy1 += (1 << fdl->shift);
						y1 = (newy1 >> fdl->Frac2);
						break;
					}			
				}
			}
		}
	
		offsety = newy1 - p->sy1;
		Do_SCurve2MoveY(fdl, offsety, lineorder,p->sy1, p->sy1, fdl->group_wrk[p->strorder], 0 ,left, right);
		//p->sy1 += offsety;
		//p->sy3 += offsety;
	}// end if

	if(p->relation >= 0)
	{
		p0 = fdl->path_buf + p->relation;
	//	p0->lock |= (FDL_PATH_LOCK_sy1 | FDL_PATH_LOCK_sy3);
		y1 = y1 + (fdl->recycle+1)*(fdl->stroke_weightX)/10 - 1;
		newy1 = (y1 << fdl->Frac2);
		offsety = newy1 - p0->sy1;	
		Do_SCurve2MoveY(fdl, offsety, p->relation, p0->sy1, p0->sy1, fdl->group_wrk[p->strorder], 0, left, right);
		//p0->sy1 += offsety;
		//p0->sy3 += offsety;
	}// end if

}// end Do_AlignStrokeLineH

// ======== collect all horizontal line in all strokes, and sort  =========
DT_void Do_SortCollectLines(pFdlRasterData fdl)
{
	DT32_int i, j, stroke_order;
	PATH_UNIT *p = fdl->path_buf;

	fdl->stroke_line_num = 0;
	for(i=0; i < fdl->stroke_num; i++)
	{
		stroke_order = fdl->stroke_order[i];
		if(fdl->group_wrk[stroke_order] == 0xFF)
			continue;
		if((fdl->stroke_buf[stroke_order].stridmap != 2 && fdl->stroke_buf[ stroke_order ].line_type != FDL_STROKE_TYPE_HORZ))
			continue;
 		for(j=0; j < fdl->stroke_buf[ stroke_order ].line_num; j++)
		{
			DT32_int IsOK, n;

			IsOK=0;
			if((fdl->stroke_buf[i].stridmap == 65 && fdl->stroke_buf[ stroke_order ].line[j] != fdl->stroke_buf[ stroke_order ].start+7) ||
				(fdl->stroke_buf[i].stridmap == 45 && fdl->stroke_buf[ stroke_order ].line[j] != fdl->stroke_buf[ stroke_order ].start+3) )
					continue;

			for(n=0; n < fdl->stroke_line_num; n++)
			{
				if(*(fdl->path_buf[fdl->stroke_line_order[n]].sy01) > *(fdl->path_buf[ fdl->stroke_buf[ stroke_order ].line[j] ].sy01))
				{
					DT_memcpy(fdl->path_tmp_buf, fdl->stroke_line_order+n, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
					fdl->stroke_line_order[n] = fdl->stroke_buf[ stroke_order ].line[j];
					DT_memcpy(fdl->stroke_line_order+n+1, fdl->path_tmp_buf, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
					fdl->stroke_line_num++;
					IsOK = 1;
					break;
				}// end if
				}// end for

			if(IsOK == 0)
				fdl->stroke_line_order[fdl->stroke_line_num++] = fdl->stroke_buf[ stroke_order ].line[j];
		}// end for
	}// end for

}// end Do_SortCollectLines


DT_void Do_SortCollectLinesAllH(pFdlRasterData fdl)
{
	DT32_int i, j, stroke_order;
	PATH_UNIT *p = fdl->path_buf;

	fdl->stroke_line_num = 0;
	for(i=0; i < fdl->stroke_num; i++)
	{
		stroke_order = fdl->stroke_order[i];
		if(fdl->group_wrk[stroke_order] == 0xFF)
			continue;
		for(j=0; j < fdl->stroke_buf[ stroke_order ].line_num; j++)
		{
			DT32_int IsOK, n;

			IsOK=0;

			for(n=0; n < fdl->stroke_line_num; n++)
			{
				if(*(fdl->path_buf[fdl->stroke_line_order[n]].sy01) > *(fdl->path_buf[ fdl->stroke_buf[ stroke_order ].line[j] ].sy01))
				{
					DT_memcpy(fdl->path_tmp_buf, fdl->stroke_line_order+n, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
					fdl->stroke_line_order[n] = fdl->stroke_buf[ stroke_order ].line[j];
					DT_memcpy(fdl->stroke_line_order+n+1, fdl->path_tmp_buf, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
					fdl->stroke_line_num++;
					IsOK = 1;
					break;
				}// end if
				}// end for

			if(IsOK == 0)
				fdl->stroke_line_order[fdl->stroke_line_num++] = fdl->stroke_buf[ stroke_order ].line[j];
		}// end for
	}// end for

}// end Do_SortCollectLinesAllH

DT_void Do_SortCollectLines_Overlay(pFdlRasterData fdl)
{
	DT32_int i,j,k;
	DT32_int m, n, idx_max;
	DT32_int dist, dist_sub;
	PATH_UNIT *p, *p0;

	i= 0;
	while(i<fdl->stroke_line_num)
	{
		p = fdl->path_buf + fdl->stroke_line_order[i];
		for(j=i; j<fdl->stroke_line_num; j++)
		{
			p0 = fdl->path_buf + fdl->stroke_line_order[j];
			if(p->sy1 == p0->sy1)
			{
				continue;
			}else
				break;
		}
		if(i+1<j)
		{
			for(m=i; m<j; m++)
			{
				dist = -1;
				idx_max  = -1;
				for(n=m; n<j; n++)
				{
					p = fdl->path_buf + fdl->stroke_line_order[n];
					dist_sub = -1;
					for(k=i-1; k>=0; k--)
					{
						p0 = fdl->path_buf + fdl->stroke_line_order[k];
						if(!IsHLineOverlayX(p, p0))
						{
							continue;
						}
						else
						{
							if( dist_sub < k)
							{
								dist_sub = k;
							}
							break;
						}
					}
					if(dist_sub > dist)
					{
						dist = dist_sub;
						idx_max = n;
					}
				}
				//
				if(idx_max >=0)
				{
					dist = fdl->stroke_line_order[m];
					fdl->stroke_line_order[m] =  fdl->stroke_line_order[idx_max];
					fdl->stroke_line_order[idx_max] = dist;
				}	
			}
		}
		i=j;
	}
}
// end Do_SortCollectLines_Overlay

// ======== collect all vertical stroke line in all strokes, and sort  =========
DT_void Do_SortCollectVLines(pFdlRasterData fdl)
{
	DT32_int i, j, stroke_order;
	PATH_UNIT *p;

	fdl->stroke_line_num = 0;
	for(i=0; i < fdl->stroke_num; i++)
	{
		stroke_order = fdl->stroke_order[i];
		if(fdl->group_wrk[stroke_order] == 0xFF || (fdl->stroke_buf[stroke_order].stridmap != 2 && fdl->stroke_buf[ stroke_order ].line_type != FDL_STROKE_TYPE_VERT))
			continue;

		for(j=0; j < fdl->stroke_buf[ stroke_order ].line_num; j++)
		{
			DT32_int IsOK, n;

			p = fdl->path_buf + fdl->stroke_buf[ stroke_order ].line[j];
			if(p->relation >= 0 && fdl->path_buf[p->relation].dir != FDL_PATH_VERT)
				continue;
			IsOK=0;
			for(n=0; n < fdl->stroke_line_num; n++)
			{
				if(*(fdl->path_buf[fdl->stroke_line_order[n]].sx01) > *(fdl->path_buf[ fdl->stroke_buf[ stroke_order ].line[j] ].sx01))
				{
					DT_memcpy(fdl->path_tmp_buf, fdl->stroke_line_order+n, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
					fdl->stroke_line_order[n] = fdl->stroke_buf[ stroke_order ].line[j];
					DT_memcpy(fdl->stroke_line_order+n+1, fdl->path_tmp_buf, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
					fdl->stroke_line_num++;
					IsOK = 1;
					break;
				}// end if
			}// end for

			if(IsOK == 0)
				fdl->stroke_line_order[fdl->stroke_line_num++] = fdl->stroke_buf[ stroke_order ].line[j];
		}// end for
	}// end for

}// end Do_SortCollectVLines

// ======== collect all vertical line in all strokes, and sort  =========
DT_void Do_SortCollectAllVLines(pFdlRasterData fdl, DT32_int group)
{
	DT32_int i, j, stroke_order;
	PATH_UNIT *p;

	fdl->stroke_line_num = 0;
	for(i=0; i < fdl->stroke_num; i++)
	{
		stroke_order = fdl->stroke_order[i];
		for(j=0; j < fdl->stroke_buf[ stroke_order ].len; j++)
		{
			DT32_int IsOK, n, poffset;

			poffset = fdl->stroke_buf[ stroke_order ].start + j;
			p = fdl->path_buf + poffset;
			if(FDL_MAIN_GROUP(fdl->group_fin[stroke_order]) != group || p->dir != FDL_PATH_VERT)
				continue;
			IsOK=0;
			for(n=0; n < fdl->stroke_line_num; n++)
			{
				if(*(fdl->path_buf[fdl->stroke_line_order[n]].sx01) > *(p->sx01))
				{
					DT_memcpy(fdl->path_tmp_buf, fdl->stroke_line_order+n, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
					fdl->stroke_line_order[n] = poffset;
					DT_memcpy(fdl->stroke_line_order+n+1, fdl->path_tmp_buf, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
					fdl->stroke_line_num++;
					IsOK = 1;
					break;
				}// end if
			}// end for

			if(IsOK == 0)
				fdl->stroke_line_order[fdl->stroke_line_num++] = poffset;
		}// end for
	}// end for

}// end Do_SortCollectAllVLines

static DT_void Do_SCurve2MoveXCenter(pFdlRasterData fdl, DT32_int move, DT32_long sx, DT32_int group)
{
	DT32_int i;
	DT32_int move_curve;
	PATH_UNIT *p;
	//p= fdl->path_buf;
	//for(i=0; i < fdl->path_num; i++, p++)
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];

		if(FDL_MAIN_GROUP(fdl->group_fin[p->strorder]) != group)
			continue;

		move_curve =0;

		if((p->lock & FDL_PATH_LOCK_sx1) == 0)
		{		
		if(sx == p->sx1)
			p->lock |= FDL_PATH_LOCK_sx1;
		p->sx1 += move;
			move_curve += move;
		}
		
		if((p->lock & FDL_PATH_LOCK_sx3) == 0)
		{

		if(sx == p->sx3)
			p->lock |= FDL_PATH_LOCK_sx3;
		p->sx3 += move;
			move_curve += move;
		}
		p->sx2 += move_curve/2;
	}// end for

}// end Do_SCurve2MoveXCenter

static DT_void Do_SCurve2MoveXBottom(pFdlRasterData fdl, DT32_int move, DT32_long sx, DT32_int n, DT32_int group)
{
	DT32_int i, domove;
	PATH_UNIT *p;
	//p= fdl->path_buf;
	DT32_int sx1;
	//for(i=0; i < fdl->path_num; i++, p++)
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];

		if(fdl->group_fin[p->strorder] != group)
			continue;

		sx1 = p->sx1;
		domove = 0;
//		if(p->sx1 >= n)
		{
			if((p->lock & FDL_PATH_LOCK_sx1) == 0)
			{
				if(sx == p->sx1)
				{
					if( (p->idx_interline >=0) && (p->relation>=0) && (p->dir == FDL_PATH_VERT))
					{
						Do_MoveInterXPoint(fdl, move, i, 1);
					}
					p->lock |= FDL_PATH_LOCK_sx1;
					p->sx1 += move;
					domove += move;
				}
			}// end if
		}// end if

//		if(p->sx3 >= n)
		{
			if((p->lock & FDL_PATH_LOCK_sx3) == 0)
			{
				if(sx == p->sx3)
				{
					p->lock |= FDL_PATH_LOCK_sx3;
					p->sx3 += move;
					domove += move;
				}
			}// end if
		}// end if

		p->sx2 += domove/2;
	}// end for

}// end Do_SCurve2MoveXBottom

static DT_void Do_SCurve2MoveXHead(pFdlRasterData fdl, DT32_int move, DT32_long sx, DT32_int n, DT32_int group)
{
	DT32_int i, domove;
	PATH_UNIT *p;
	//p= fdl->path_buf;
	//for(i=0; i < fdl->path_num; i++, p++)
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		DT32_ulong lock1, lock3;
		p = fdl->path_buf + fdl->path_buf_pt[i];

		if(fdl->group_wrk[p->strorder] != group)
			continue;

		if(*p->sx01 == p->sx1)
		{
			lock1 = FDL_PATH_LOCK_sx1;
			lock3 = FDL_PATH_LOCK_sx3;
		}else
		{
			lock1 = FDL_PATH_LOCK_sx3;
			lock3 = FDL_PATH_LOCK_sx1;
		}// end if

		domove = 0;
		if(sx <= *p->sx01 && *p->sx01 <= n)
		{
			if((p->lock & lock1) == 0)
			{
				if(sx == *p->sx01)
					p->lock |= lock1;
				*p->sx01 += move;
				domove += move;
			//	if((p->lock & lock1) == 0)
				{
					if(*p->sx01 < sx)
					{
						domove += sx - *p->sx01;
						*p->sx01 = sx;
					}else if(*p->sx01 > n)
					{
						domove += n - *p->sx01;
						*p->sx01 = n;
					}// end if
					}
			}// end if
		}else if(n <= *p->sx01 && *p->sx01 <= sx)
		{
			if((p->lock & lock1) == 0)
			{
				if(sx == *p->sx01)
					p->lock |= lock1;

				*p->sx01 += move;
				domove += move;

			//	if((p->lock & lock1) == 0)
				{
				
				if(*p->sx01 < n)
				{
					domove += n - *p->sx01;
					*p->sx01 = n;
				}else if(*p->sx01 > sx)
				{
					domove += sx - *p->sx01;
					*p->sx01 = sx;
				}// end if
				}

			}// end if
		}// end if

		if(sx <= *p->sx03 && *p->sx03 <= n)
		{
			if((p->lock & lock3) == 0)
			{
				if(sx == *p->sx03)
					p->lock |= lock3;
				*p->sx03 += move;
				domove += move;

			//	if((p->lock & FDL_PATH_LOCK_sx3) == 0)
				{
				if(*p->sx03 < sx)
				{
					domove += sx - *p->sx03;
					*p->sx03 = sx;
				}else if(*p->sx03 > n)
				{
					domove += n - *p->sx03;
					*p->sx03 = n;
				}// end if
				}
			}// end if
		}else if(n <= *p->sx03 && *p->sx03 <= sx)
		{
			if((p->lock & lock3) == 0)
			{
				if(sx == *p->sx03)
					p->lock |= lock3;
				*p->sx03 += move;
				domove += move;

			//	if((p->lock & FDL_PATH_LOCK_sx3) == 0)
				{
				if(*p->sx03 < n)
				{
					domove += n - *p->sx03;
					*p->sx03 = n;
				}else if(*p->sx03 > sx)
				{
					domove += sx - *p->sx03;
					*p->sx03 = sx;
				}// end if
				}
			}// end if
		}// end if

		p->sx2 += domove/2;
	}// end for

}// end Do_SCurve2MoveXHead


static DT_void Do_SCurve2MoveXHead_Right(pFdlRasterData fdl, DT32_int move, DT32_long sx, DT32_int n, DT32_int group)
{
	DT32_int i, domove;
	PATH_UNIT *p;
	//p= fdl->path_buf;

	//for(i=0; i < fdl->path_num; i++, p++)
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];

		if(fdl->group_wrk[p->strorder] != group)
			continue;

		domove = 0;
		if(sx <= *p->sx01 && *p->sx01 <= n)
		{
			if((p->lock & FDL_PATH_LOCK_sx1) == 0)
			{
				if(sx == *p->sx01)
					p->lock |= FDL_PATH_LOCK_sx1;
				*p->sx01 += move;
				domove += move;
				if((p->lock & FDL_PATH_LOCK_sx1) == 0)
				{
				if(*p->sx01 < sx)
				{
					domove += sx - *p->sx01;
					*p->sx01 = sx;
				}else if(*p->sx01 > n)
				{
					domove += n - *p->sx01;
					*p->sx01 = n;
				}// end if
			}
			}// end if
		}else if(n <= *p->sx01 && *p->sx01 <= sx)
		{
			if((p->lock & FDL_PATH_LOCK_sx1) == 0)
			{
				if(sx == *p->sx01)
					p->lock |= FDL_PATH_LOCK_sx1;

				*p->sx01 += move;
				domove += move;

				if((p->lock & FDL_PATH_LOCK_sx1) == 0)
				{
				
				if(*p->sx01 < n)
				{
					domove += n - *p->sx01;
					*p->sx01 = n;
				}else if(*p->sx01 > sx)
				{
					domove += sx - *p->sx01;
					*p->sx01 = sx;
				}// end if
				}

			}// end if
		}// end if

		if(sx <= *p->sx03 && *p->sx03 <= n)
		{
			if((p->lock & FDL_PATH_LOCK_sx3) == 0)
			{
				if(sx == *p->sx03)
					p->lock |= FDL_PATH_LOCK_sx3;
				*p->sx03 += move;
				domove += move;

				if((p->lock & FDL_PATH_LOCK_sx3) == 0)
				{
				if(*p->sx03 < sx)
				{
					domove += sx - *p->sx03;
					*p->sx03 = sx;
				}else if(*p->sx03 > n)
				{
					domove += n - *p->sx03;
					*p->sx03 = n;
				}// end if
				}
			}// end if
		}else if(n <= *p->sx03 && *p->sx03 <= sx)
		{
			if((p->lock & FDL_PATH_LOCK_sx3) == 0)
			{
				if(sx == *p->sx03)
					p->lock |= FDL_PATH_LOCK_sx3;
				*p->sx03 += move;
				domove += move;

				if((p->lock & FDL_PATH_LOCK_sx3) == 0)
				{
				if(*p->sx03 < n)
				{
					domove += n - *p->sx03;
					*p->sx03 = n;
				}else if(*p->sx03 > sx)
				{
					domove += sx - *p->sx03;
					*p->sx03 = sx;
				}// end if
				}
			}// end if
		}// end if

		p->sx2 += domove/2;
	}// end for

}// end Do_SCurve2MoveXHead_Right

// ===== move x1 <-> x2
static DT_void Do_SCurve2MoveXScale(pFdlRasterData fdl, DT32_int move, DT32_int lineorder, DT32_int targetx ,DT32_int sx1, DT32_int sx2, DT32_int group, DT32_int stroder)
{	// sx1 must always <= sx2
	DT32_int i, domove, oldlen, x1, newsx, newlen;
	PATH_UNIT *p = fdl->path_buf;
	PATH_UNIT *p0;
	DT32_int org_sx1,org_sy1,org_sx3,org_sy3;

	p0= fdl->path_buf+lineorder;
	org_sx1 = p0->sx1;
	org_sy1 = p0->sy1;
	org_sx3 = p0->sx3;
	org_sy3 = p0->sy3;;

	if(sx1 <= sx2)
	{
		oldlen = sx2 - sx1;
		if(targetx == sx1)
		{
			newsx = sx1 + move;
			newlen = oldlen - move;
		}else
		{
			newsx = sx1;
			newlen = oldlen + move;
		}// end if

		oldlen >>= fdl->Frac2;			// Shift the value to avoid the int overflow.
		newlen >>= fdl->Frac2;			// Shift the value to avoid the int overflow.
	}else
	{
		oldlen = sx1 - sx2;
		if(targetx == sx1)
		{
			newsx = sx1 + move;
			newlen = oldlen - move;
		}else
		{
			newsx = sx1;
			newlen = oldlen + move;
		}// end if

		i = sx2;
		sx2 = sx1;
		sx1 = i;
		oldlen >>= fdl->Frac2;			// Shift the value to avoid the int overflow.
		newlen >>= fdl->Frac2;			// Shift the value to avoid the int overflow.
	}// end if

	if(oldlen <= 0) oldlen = 1;

	fdl->path_tmp_num = 0;
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(fdl->group_fin[p->strorder] != group || (p->strorder == stroder))
			continue;

		if(fdl->stroke_buf[p->strorder].stridmap == 25
			|| fdl->stroke_buf[p->strorder].stridmap == 131
			|| fdl->stroke_buf[p->strorder].stridmap == 74
			|| fdl->stroke_buf[p->strorder].stridmap == 38
			|| fdl->stroke_buf[p->strorder].stridmap == 3
//			|| fdl->stroke_buf[p->strorder].stridmap == 19	/* 0x7DE8 */
			|| fdl->stroke_buf[p->strorder].stridmap == 12	/* 0x5EE0 */
//|| fdl->stroke_buf[p->strorder].stridmap == 128
			|| fdl->stroke_buf[p->strorder].stridmap == 45
			|| fdl->stroke_buf[p->strorder].stridmap == 30
		)
		{
			TRect rect;
			GetStrokeRect(fdl, p->strorder, &rect);
			if(rect.left < sx1 && sx2 < rect.right)
				i += fdl->stroke_buf[p->strorder].len-1;
			else if(sx1 <= rect.left && rect.right <= sx2)
			{
				DT32_int width1;
				DT32_int width2;

				width1 = rect.right - rect.left;
				width2 = width1 + move;
				if(width1 > -move)
				{
					DT32_int j;
					for(j=0; j < fdl->stroke_buf[p->strorder].len; j++)
					{
						p[j].sx1 = rect.left + (p[j].sx1 - rect.left)*width2/width1;
						p[j].sx2 = rect.left + (p[j].sx2 - rect.left)*width2/width1;
						p[j].sx3 = rect.left + (p[j].sx3 - rect.left)*width2/width1;
					}// end for
				}// end if

				i += fdl->stroke_buf[p->strorder].len-1;
			}
			else //if(fdl->stroke_buf[p->strorder].stridmap != 45)
			{
				if((sx1 <= *p->sx01 && *p->sx01 <= sx2 || sx1 <= *p->sx03 && *p->sx03 <= sx2))
					fdl->path_tmp_buf[ fdl->path_tmp_num++ ] = fdl->path_buf_pt[i];
			}// end if
		}else if((sx1 <= *p->sx01 && *p->sx01 <= sx2 || sx1 <= *p->sx03 && *p->sx03 <= sx2))
		{
			fdl->path_tmp_buf[ fdl->path_tmp_num++ ] = fdl->path_buf_pt[i];
		}// end if
	}// end for

	for(i=0; i < fdl->path_tmp_num; i++)
	{
		p = fdl->path_buf + fdl->path_tmp_buf[i];
		if( (fdl->stroke_buf[p->strorder].status & FDL_STROKE_LEFT_LEAN) != 0)
		{/*move the left part to corrent postion.*/
			continue;
		}

		domove = 0;
		if((p->lock & FDL_PATH_LOCK_sx1) == 0)
		{
			if(targetx == p->sx1)
			{
				p->lock |= FDL_PATH_LOCK_sx1;
				p->sx1 += move;
				domove += move;
			}
			else if(sx1 <= p->sx1 && p->sx1 <= sx2)
			{
				x1 = newsx + (p->sx1 - sx1)*newlen/oldlen;
				domove = x1 - p->sx1;
				p->sx1 = x1;
			}// end if
		}// end if

		if((p->lock & FDL_PATH_LOCK_sx3) == 0)
		{
			if(targetx == p->sx3)
			{
				p->lock |= FDL_PATH_LOCK_sx3;
				p->sx3 += move;
				domove += move;
			}else if(sx1 <= (p->sx3) && (p->sx3) <= sx2)
			{
				x1 = newsx + (p->sx3 - sx1)*newlen/oldlen;
				domove += x1 - p->sx3;
				p->sx3 = x1;
			}// end if
		}// end if

		p->sx2 += domove/2;
	}// end for

#if 1
	//re-connect the divided path.
	p = fdl->path_buf + fdl->stroke_buf[stroder].start;
	for(i=0; i<fdl->stroke_buf[stroder].len; i++, p++)
	{
		domove = 0;
		if( (p->sx1 == org_sx1 && p->sy1 == org_sy1)
			|| (p->sx1 == org_sx3 && p->sy1 == org_sy3))
		{
				p->lock |= FDL_PATH_LOCK_sx1;
				p->sx1+=move;
				domove = move;
		}

		if( (p->sx3 == org_sx1 && p->sy3 == org_sy1)
			|| (p->sx3 == org_sx3 && p->sy3 == org_sy3))
		{
				p->lock |= FDL_PATH_LOCK_sx3;
				p->sx3+=move;
				domove += move;
		}
		p->sx2 += domove/2;
	}
#endif

/*
	// ============== adjust stroke's path ================
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(fdl->group_fin[p->strorder] != group)
			continue;

		if(p->strorder != stroder)
			continue;

		domove = 0;
		if((p->lock & FDL_PATH_LOCK_sx1) == 0)
		{
			if(sx1 <= *p->sx01 && *p->sx01 <= sx2)
			{
				if(targetx == *p->sx01)
				{
					p->lock |= FDL_PATH_LOCK_sx1;
					*p->sx01 += move;
					domove += move;
				}else if(p->strorder == stroder)
				{
					x1 = newsx + (*p->sx01 - sx1)*newlen/oldlen;
					domove = x1 - *p->sx01;
					*p->sx01 = x1;
				}// end if
			}// end if
		}// end if

		if((p->lock & FDL_PATH_LOCK_sx3) == 0)
		{
			if(sx1 <= *p->sx03 && *p->sx03 <= sx2)
			{
				if(targetx == *p->sx03)
				{
					p->lock |= FDL_PATH_LOCK_sx3;
					*p->sx03 += move;
					domove += move;
				}else if(p->strorder == stroder)
				{
					x1 = newsx + (*p->sx03 - sx1)*newlen/oldlen;
					domove += x1 - *p->sx03;
					*p->sx03 = x1;
				}// end if
			}// end if
		}// end if

		p->sx2 += domove/2;
	}// end for
*/
}// end Do_SCurve2MoveXScale


DT_void Do_MoveStrokeXPath_LOCK(pFdlRasterData fdl, DT32_int lineorder, DT32_int newpos)
{
	DT32_int i, x1,y1,y3;
	PATH_UNIT *p, *p0;

	p = fdl->path_buf + lineorder;
	x1 = p->sx1;
	y1 = p->sy1;
	y3 = p->sy3;
	p0 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;

	for(i=0; i < fdl->stroke_buf[p->strorder].len; i++, p0++)
	{
		if(p0->sx1 == x1)
		{
			p0->sx1 = newpos;
			if( (y1 ==  p0->sy1) || (y3 ==  p0->sy1))
				p0->lock |= FDL_PATH_LOCK_sx1;
		}
		if(p0->sx3 == x1)
		{
			p0->sx3 = newpos;
			if( (y1 ==  p0->sy3) || (y3 ==  p0->sy3))
				p0->lock |= FDL_PATH_LOCK_sx3;
		}

	}// end for

}// end Do_MoveStrokeXPath

DT_void Do_AlignStrokeLineV(pFdlRasterData fdl, DT32_int lineorder, DT32_int last_line)
{
	DT32_int x1, newx1, offsetx,newx1_r;
	PATH_UNIT *p, *p0, *p01;
	DT32_int i,j;
	DT32_int lock_sx,lock_sy;
	DT32_int domove;

	p = fdl->path_buf + lineorder;
	if((p->lock & (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3)) == 0)
	{
		if(last_line == 0xFFFF)
		{
			p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
			x1 = (p->sx1) >> fdl->Frac2;
			x1 = x1 & ~fdl->recycle;
			newx1 = (x1 << fdl->Frac2);
			offsetx = newx1 - p->sx1;

			Do_MoveStrokeXPath_LOCK(fdl, lineorder, newx1);
		}else if(last_line < 0)
		{
			x1 = (p->sx1) >> fdl->Frac2;
			x1 = x1 & ~fdl->recycle;
			newx1 = (x1 << fdl->Frac2);
			offsetx = newx1 - p->sx1;
			Do_SCurve2MoveXCenter(fdl, offsetx, p->sx1, FDL_MAIN_GROUP(fdl->group_fin[p->strorder]));

			p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
		}else
		{
			DT32_int w;
			p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);

			p0 = fdl->path_buf + fdl->stroke_line_order[last_line];
			if(p->sx1 >= p0->sx1)
			{
				w = p->sx1 - p0->sx1;
				w = (w >> fdl->shift) << fdl->recycleshift;
				if(w < (fdl->recycle+1)*(fdl->stroke_weightY + fdl->stroke_weightYSpace)/10)
					w = (fdl->recycle+1)*(fdl->stroke_weightY + fdl->stroke_weightYSpace)/10;
				newx1 = p0->sx1 + (w << fdl->Frac2);
				x1 = newx1 >> fdl->Frac2;
			}else
			{
				w = p0->sx1 - p->sx1;
				w = (w >> fdl->shift) << fdl->recycleshift;
				if(w < (fdl->recycle+1)*(fdl->stroke_weightY + fdl->stroke_weightYSpace)/10)
					w = (fdl->recycle+1)*(fdl->stroke_weightY + fdl->stroke_weightYSpace)/10;
				newx1 = p0->sx1 - (w << fdl->Frac2);
				x1 = newx1 >> fdl->Frac2;
			}// end if

			offsetx = newx1 - p->sx1;

/*
			Do_SCurve2MoveXHead(fdl, offsetx, p->sx1, p0->sx1, fdl->group_wrk[p->strorder]);

			p->sx1 += offsetx;
			p->sx3 += offsetx;
*/			
			
			if( ((p->sx1>p0->sx1)&&(offsetx<0)) || ((p->sx1<p0->sx1)&&(offsetx>0)) )
			{
			//	p->lock &= ~(FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
					Do_SCurve2MoveXHead(fdl, offsetx, p->sx1, p0->sx1, fdl->group_wrk[p->strorder]);
			//	p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
					p->sx1 += offsetx;
					p->sx3 += offsetx;
				
			}else{
				
				p->lock &= ~(FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);

				p0 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(i=0; i< fdl->stroke_buf[p->strorder].len; i++, p0++)
				{
					if((p0->lock & FDL_PATH_LOCK_sx1) == 0 &&  (p0->lock & FDL_PATH_TMPLOCK_s1) == 0)
					{
							lock_sx = p0->sx1;
							lock_sy = p0->sy1;
							p01 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
							for(j=0; j< fdl->stroke_buf[p->strorder].len; j++, p01++)
							{
								if((p01->lock & FDL_PATH_LOCK_sx1) != 0 )
								{
									if(p01->sx1 == lock_sx && p01->sy1 == lock_sy )
									{
										p0->lock |= FDL_PATH_LOCK_sx1;
									}
								}
								
								if((p01->lock & FDL_PATH_LOCK_sx3) != 0 )
								{
									if(p01->sx3 == lock_sx && p01->sy3 == lock_sy )
									{
										p0->lock |= FDL_PATH_LOCK_sx1;
									}
								}
							}
					}

					if(((p0->lock & FDL_PATH_LOCK_sx3) == 0) && (p0->lock & FDL_PATH_TMPLOCK_s3)==0)
					{
							lock_sx = p0->sx3;
							lock_sy = p0->sy3;
							
							p01 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
							for(j=0; j< fdl->stroke_buf[p->strorder].len; j++, p01++)
							{
								if((p01->lock & FDL_PATH_LOCK_sx1) != 0 )
								{
									if(p01->sx1 == lock_sx && p01->sy1 == lock_sy )
									{
										p0->lock |= FDL_PATH_LOCK_sx3;
									}
								}

								if((p01->lock & FDL_PATH_LOCK_sx3) != 0 )
								{
									if(p01->sx3 == lock_sx && p01->sy3 == lock_sy )
									{
										p0->lock |= FDL_PATH_LOCK_sx3;
									}
								}
							}
					}
	
				}// end for

				p0 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(i=0; i< fdl->stroke_buf[p->strorder].len; i++, p0++)
				{
					domove = 0;
					if((p0->lock & FDL_PATH_LOCK_sx1) == 0 && (p0->lock & FDL_PATH_TMPLOCK_s1)==0)
					{
						((p0->sx1)) += offsetx;
						domove = offsetx;
					}
					if((p0->lock & FDL_PATH_LOCK_sx3) == 0 && (p0->lock & FDL_PATH_TMPLOCK_s3)==0)
					{
						((p0->sx3)) += offsetx;
						domove += offsetx;
					}
					p0->sx2 += domove/2;
				}

				p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
			}
		
		}// end if
	}else
	{
		x1 = p->sx1 >> fdl->Frac2;
		newx1 = (x1 << fdl->Frac2);
	}// end if

	newx1_r = newx1;

	if(p->relation >= 0)
	{
		p0 = fdl->path_buf + p->relation;
		if((p0->lock & (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3)) == 0 && p0->sx1 >= p->sx1)
		{
			p0->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
			x1 = x1 + (fdl->recycle+1)*(fdl->stroke_weightY)/10 - 1;
			newx1 = (x1 << fdl->Frac2) + (1 << fdl->shift)/2 ;
			newx1>>=fdl->shift;
			newx1<<=fdl->shift;

			if( (newx1 - newx1_r) < (1<<fdl->shift) ){
				newx1 = newx1_r + (1<<fdl->shift);
			}
			offsetx = newx1 - p0->sx1;
			Do_SCurve2MoveXBottom(fdl, offsetx, p0->sx1, p->sx1, fdl->group_wrk[p->strorder]);
			p0->sx1 += offsetx;
			p0->sx3 += offsetx;
			p0->sx2 += offsetx;
	
		}// end if
	}// end if

}// end Do_AlignStrokeLineV

DT_void Do_AlignStrokeLineV_Right(pFdlRasterData fdl, DT32_int lineorder, DT32_int last_line)
{
	DT32_int x1, newx1, offsetx;
	PATH_UNIT *p, *p0;
	DT32_int i;

	p = fdl->path_buf + lineorder;
	if((p->lock & (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3)) == 0)
	{
		if(last_line == 0xFFFF)
		{
			p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
			x1 = (p->sx1) >> fdl->Frac2;
			x1 = x1 & ~fdl->recycle;
			newx1 = (x1 << fdl->Frac2);
			offsetx = newx1 - p->sx1;

			//Do_MoveStrokeXPath(fdl, lineorder, newx1);
			Do_MoveStrokeXPath_LOCK(fdl, lineorder, newx1);
		}else if(last_line < 0)
		{
			p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
			x1 = (p->sx1) >> fdl->Frac2;
			x1 = x1 & ~fdl->recycle;
			newx1 = (x1 << fdl->Frac2);
			offsetx = newx1 - p->sx1;
			Do_SCurve2MoveXCenter(fdl, offsetx, p->sx1, FDL_MAIN_GROUP(fdl->group_fin[p->strorder]));
		}else
		{
			DT32_int w;
			p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);

			p0 = fdl->path_buf + fdl->stroke_line_order[last_line];
			if(p->sx1 >= p0->sx1)
			{
				w = p->sx1 - p0->sx1;
				w = (w >> fdl->shift) << fdl->recycleshift;
				if(w < (fdl->recycle+1)*(fdl->stroke_weightY + fdl->stroke_weightYSpace)/10)
					w = (fdl->recycle+1)*(fdl->stroke_weightY + fdl->stroke_weightYSpace)/10;
				newx1 = p0->sx1 + (w << fdl->Frac2);
				x1 = newx1 >> fdl->Frac2;
			}else
			{
				w = p0->sx1 - p->sx1;
				w = (w >> fdl->shift) << fdl->recycleshift;
				if(w < (fdl->recycle+1)*(fdl->stroke_weightY + fdl->stroke_weightYSpace)/10)
					w = (fdl->recycle+1)*(fdl->stroke_weightY + fdl->stroke_weightYSpace)/10;
				newx1 = p0->sx1 - (w << fdl->Frac2);
				x1 = newx1 >> fdl->Frac2;
			}// end if

			offsetx = newx1 - p->sx1;

			if( ((p->sx1>p0->sx1)&&(offsetx<0)) || ((p->sx1<p0->sx1)&&(offsetx>0)) )
			{
				 // p->lock &= ~(FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
					Do_SCurve2MoveXHead(fdl, offsetx, p->sx1, p0->sx1, fdl->group_wrk[p->strorder]);
					//Do_SCurve2MoveXHead_Right(fdl, offsetx, p->sx1, p0->sx1, fdl->group_wrk[p->strorder]);

				  //p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
					p->sx1 += offsetx;
					p->sx3 += offsetx;
		
			}else{
				
				p0 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(i=0; i< fdl->stroke_buf[p->strorder].len; i++, p0++)
				{
					p0->sx1 += offsetx;
					p0->sx3 += offsetx;
				}// end for*/
			}
		}// end if
	}else x1 = p->sx1 >> fdl->Frac2;

	if(p->relation >= 0)
	{
		p0 = fdl->path_buf + p->relation;
		if((p0->lock & (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3)) == 0 && p0->sx1 >= p->sx1)
		{
			p0->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
			x1 = x1 + (fdl->recycle+1)*(fdl->stroke_weightY)/10 - 1;
			newx1 = (x1 << fdl->Frac2);
			offsetx = newx1 - p0->sx1;
			Do_SCurve2MoveXBottom(fdl, offsetx, p0->sx1, p->sx1, fdl->group_wrk[p->strorder]);
			p0->sx1 += offsetx;
			p0->sx3 += offsetx;
	
		}// end if
	}// end if

}// end Do_AlignStrokeLineV_Right

DT_void Do_AlignStrokeLineVLeftRight(pFdlRasterData fdl, DT32_int lineorder, DT32_int targetsx, DT32_int centersx)
{
	DT32_int x1, offsetx;
	PATH_UNIT *p, *p0;

	p = fdl->path_buf + lineorder;

	if(targetsx <= centersx)
	{
		if(fdl->stroke_buf[p->strorder].stridmap == 4 && (lineorder - fdl->stroke_buf[p->strorder].start) == 1)
			p->relation = fdl->stroke_buf[p->strorder].start+4;

		if(fdl->stroke_buf[p->strorder].stridmap == 34 && (lineorder - fdl->stroke_buf[p->strorder].start) == 0)
			p->relation = fdl->stroke_buf[p->strorder].start+2;

	
		p0 = fdl->path_buf + p->relation;
		p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
		offsetx = targetsx - p->sx1;
		Do_SCurve2MoveXScale(fdl, offsetx, lineorder, p->sx1, p->sx1, p0->sx1-1, fdl->group_fin[p->strorder], p->strorder);
	
		// ====================================================================
		// p->relation should must have, so I don't check it.
		x1 = targetsx >> fdl->Frac2;
		p0->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
		x1 = x1 + (fdl->recycle+1)*(fdl->stroke_weightY)/10 - 1;

		offsetx = (x1 << fdl->Frac2) - p0->sx1;
		Do_SCurve2MoveXScale(fdl, offsetx, p->relation, p0->sx1, p0->sx1, centersx-1, fdl->group_fin[p->strorder], p0->strorder);
	}else
	{
		if(fdl->stroke_buf[p->strorder].stridmap == 4 && (lineorder - fdl->stroke_buf[p->strorder].start) == 8)
			p->relation = fdl->stroke_buf[p->strorder].start+7;
		p0 = fdl->path_buf + p->relation;

		// p->relation should must have, so I don't check it.
		x1 = targetsx >> fdl->Frac2;
		p0->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
		x1 = x1 + (fdl->recycle+1)*(fdl->stroke_weightY)/10 - 1;
		offsetx = (x1 << fdl->Frac2) - p0->sx1;
		Do_SCurve2MoveXScale(fdl, offsetx, p->relation, p0->sx1, p->sx1+1, p0->sx1, fdl->group_fin[p->strorder], p0->strorder);

		// ====================================================================
		p->lock |= (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3);
		offsetx = targetsx - p->sx1;
		Do_SCurve2MoveXScale(fdl, offsetx, lineorder, p->sx1, centersx+1, p->sx1, fdl->group_fin[p->strorder], p->strorder);
	}// end if

}// end Do_AlignStrokeLineVLeftRight


DT32_int IsVLineOverlayY2(PATH_UNIT *p1, PATH_UNIT *p2)
{
	if(*p1->sy01 <= *p2->sy01 && *p2->sy01 <= *p1->sy03)
		return *p1->sy03 - *p2->sy01;
	else if(*p1->sy01 < *p2->sy03 && *p2->sy03 < *p1->sy03)
		return *p2->sy03 - *p1->sy01;
	else if(*p1->sy01 <= *p2->sy01 && *p2->sy03 <= *p1->sy03)
		return *p2->sy03 - *p2->sy01;
	else if(*p1->sy01 > *p2->sy01 && *p2->sy03 > *p1->sy03)
		return *p2->sy03 - *p2->sy01;

	return -1;
}// end IsVLineOverlayY2

DT32_int IsVLineOverlayY(PATH_UNIT *p1, PATH_UNIT *p2)
{
/*	if((*p1->sy01 <= p2->sy1 && p2->sy1 <= *p1->sy03) 
		|| (*p1->sy01 < p2->sy3 && p2->sy3 < *p1->sy03) 
		|| (*p1->sy01 <= *p2->sy01 && *p2->sy03 <= *p1->sy03)
		|| (*p1->sy01 > *p2->sy01 && *p2->sy03 > *p1->sy03)
		)
		return 1;*/
	if(*p1->sy01 <= *p2->sy01)
	{
		if( ((*p1->sy03 - *p1->sy01) - (*p2->sy01 - *p1->sy01)) > 0 )
			return 1;
	}else if(*p1->sy01 < *p2->sy03)
	{
		return 1;
	}// end if

	return 0;
}// end IsVLineOverlayY

DT32_int IsVLineOverlayX(PATH_UNIT *p1, PATH_UNIT *p2)
{
	if((*p1->sx01 <= p2->sx1 && p2->sx1 <= *p1->sx03) 
		|| (*p1->sx01 < p2->sx3 && p2->sx3 < *p1->sx03) 
		|| (*p1->sx01 <= *p2->sx01 && *p2->sx03 <= *p1->sx03)
		|| (*p1->sx01 > *p2->sx01 && *p2->sx03 > *p1->sx03)
		)
		return 1;

	return 0;
}// end IsVLineOverlayX

DT32_int IsHLineOverlayX(PATH_UNIT *p01, PATH_UNIT *p02)
{
	PATH_UNIT *p1, *p2;
	p1 = p01;
	p2 = p02;
	if((*p1->sx01 <= p2->sx1 && p2->sx1 <= *p1->sx03) 
		|| (*p1->sx01 <= p2->sx3 && p2->sx3 <= *p1->sx03) 
		|| (*p1->sx01 <= *p2->sx01 && *p2->sx03 <= *p1->sx03)
		|| (*p1->sx01 >= *p2->sx01 && *p2->sx03 >= *p1->sx03)
		)
	return 1;

	p1 = p02;
	p2 = p01;
	if((*p1->sx01 <= p2->sx1 && p2->sx1 <= *p1->sx03) 
		|| (*p1->sx01 <= p2->sx3 && p2->sx3 <= *p1->sx03) 
		|| (*p1->sx01 <= *p2->sx01 && *p2->sx03 <= *p1->sx03)
		|| (*p1->sx01 >= *p2->sx01 && *p2->sx03 >= *p1->sx03)
		)
	return 1;

	return 0;
}// end IsHLineOverlayX

DT_void Do_MoveStrokeX(pFdlRasterData fdl, DT32_int lineorder, DT32_int newpos)
{
	DT32_int i, x1, move;
	PATH_UNIT *p, *p0;

	p = fdl->path_buf + lineorder;
	x1 = p->sx1;
	move = newpos - x1;
	p0 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;

	for(i=0; i < fdl->stroke_buf[p->strorder].len; i++, p0++)
	{
		if(p0->sx1 == x1)
			p0->sx1 = newpos;
		else p0->sx1 += move;

		if(p0->sx3 == x1)
			p0->sx3 = newpos;
		else p0->sx3 += move;

		p0->sx2 += move;
	}// end for

}// end Do_MoveStrokeX

DT_void Do_MoveStrokeXPath(pFdlRasterData fdl, DT32_int lineorder, DT32_int newpos)
{
	DT32_int i, x1;
	PATH_UNIT *p, *p0;

	p = fdl->path_buf + lineorder;
	x1 = p->sx1;
	p0 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;

	for(i=0; i < fdl->stroke_buf[p->strorder].len; i++, p0++)
	{
		if(p0->sx1 == x1)
			p0->sx1 = newpos;
		if(p0->sx3 == x1)
			p0->sx3 = newpos;
	}// end for

}// end Do_MoveStrokeXPath

DT_void Do_MoveStrokeYPath(pFdlRasterData fdl, DT32_int lineorder, DT32_int newpos)
{
	DT32_int i, y1;
	PATH_UNIT *p, *p0;

	p = fdl->path_buf + lineorder;
	y1 = p->sy1;
	p0 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
	for(i=0; i < fdl->stroke_buf[p->strorder].len; i++, p0++)
	{
		if(p0->sy1 == y1)
			p0->sy1 = newpos;
		if(p0->sy3 == y1)
			p0->sy3 = newpos;
	}// end for
}// end Do_MoveStrokeYPath

DT_void Do_AlignThisStrokeLineV(pFdlRasterData fdl, DT32_int lineorder, DT32_int centerpoint)
{
	DT32_int i, newx1, iFind=0;
	PATH_UNIT *p, *p0, *p1;

	p = fdl->path_buf + fdl->stroke_line_order[lineorder];

	if((p->lock & FDL_PATH_IsRightOrButtom) == 0)
	{
		if((fdl->stroke_buf[p->strorder].stridmap == 0) && (fdl->path_buf[fdl->stroke_buf[p->strorder].start+2].lock & FDL_PATH_PRIVATE_MIRROR_PATH))
		{
			p0 = fdl->path_buf + fdl->path_buf[fdl->stroke_buf[p->strorder].start+2].mirror_relation;
			if(p0->relation >= 0)
				newx1 = p0->sx1 - (fdl->path_buf[p->relation].sx1 - p->sx1 - (fdl->path_buf[p0->relation].sx1 - p0->sx1))/2;
			else newx1 = p0->sx1 - (fdl->path_buf[p->relation].sx1 - p->sx1 - (fdl->stroke_weightY << fdl->shift)/10)/2;
			newx1 = (newx1 >> fdl->shift) << fdl->shift;
			Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);

			for(i=lineorder-1; i >= 0; i--)	// 0x775B,17
			{
				if(i == lineorder) continue;
				p1 = fdl->path_buf + fdl->stroke_line_order[i];
				if(!(p->sx1 < p1->sx1 && p1->sx1 < p0->sx1)) continue;
				if(IsVLineOverlayY(p, p1))
				{
					if((p1->lock & FDL_PATH_MustHide2) != 0 && p1->stick_stroke == p->strorder)
						continue;
					if((p1->lock & FDL_PATH_IsRightOrButtom) == 0)
						newx1 = p1->sx1 + (fdl->stroke_weightY/10 << fdl->shift);
					else newx1 = p1->sx1;
					newx1 = (newx1 >> fdl->shift) << fdl->shift;
					Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);
					iFind = 1;
					break;
				}// end if

			}// end for
		}else if((p->sx1 & ((1 << fdl->shift)-1)) != 0)
		{
/*			if( p->relation >= 0 && (fdl->stroke_buf[p->strorder].status & FDL_STROKE_MIRROR) == 0 &&
				(fdl->stroke_buf[p->strorder].status & FDL_STROKE_MIRROR_TWO_LINES) != 0 &&
				fdl->stroke_line_order[lineorder] == fdl->stroke_buf[p->strorder].line[ fdl->stroke_buf[p->strorder].line_num-1 ] )
			{
				newx1 = fdl->path_buf[p->relation].sx1 >> fdl->shift;
				newx1 = newx1 - fdl->stroke_weightY/10;
				newx1 <<= fdl->shift;
			}else*/
//				newx1 = ((p->sx1+(1 << fdl->shift)/2) >> fdl->shift) << fdl->shift;

			newx1 = (p->sx1 >> fdl->shift) << fdl->shift;
			Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);

			for(i=fdl->stroke_line_num-1; i >= 0; i--)
			{
				if(i == lineorder) continue;
				p0 = fdl->path_buf + fdl->stroke_line_order[i];
				if(p->sx1 < p0->sx1) continue;
				if(IsVLineOverlayY(p, p0))
				{
					if((newx1 - (*p0->sx03+1) < (1 << fdl->shift)) && (p0->lock & FDL_PATH_IsRightOrButtom) != 0)
						newx1 = *p0->sx03 + (1 << fdl->Frac2) + (1 << fdl->shift);
					Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);
					iFind = 1;
					break;
				}// end if

			}// end for

		}// end if

		if(iFind == 0)
		{
			if(fdl->stroke_buf[p->strorder].stridmap == 2 || fdl->stroke_buf[p->strorder].stridmap == 30)
			{	// Do nothing, because thie stroke should already align.

			}else if(p->relation >= 0 && fdl->stroke_buf[p->strorder].status & FDL_STROKE_MIRROR && (fdl->stroke_buf[p->strorder].status & FDL_STROKE_MIRROR_TWO_LINES) == 0)
			{
				newx1 = ((p->sx1+(1 << fdl->shift)/2) >> fdl->shift) << fdl->shift;
				p0 = fdl->path_buf + p->relation;
				newx1 = p0->sx1 - p->sx1;
			}else if(p->lock & FDL_PATH_MIRROR_PATH)
			{
				DT32_int middle;
				PATH_UNIT *p1;
				middle = centerpoint >> fdl->shift;
				p1 = fdl->path_buf + p->mirror_relation;
				newx1 = middle - (p1->sx1 >> fdl->shift);
				if(newx1 < 1)
				{
					newx1 = 1;
					Do_MoveStrokeX(fdl, p1->relation, ((middle - (newx1 + fdl->stroke_weightY/10)) << fdl->shift) );
				}// end if
				newx1 = (middle + newx1) << fdl->shift;
				Do_MoveStrokeX(fdl, fdl->stroke_line_order[lineorder], newx1);
			}// end if
		}// end if

	}else
	{
		DT32_int dist, relation;
		if((fdl->stroke_buf[p->strorder].status & (FDL_STROKE_MIRROR | FDL_STROKE_MIRROR_TWO_LINES)) != (FDL_STROKE_MIRROR | FDL_STROKE_MIRROR_TWO_LINES))
		{
			if(p->relation >= 0 && (fdl->stroke_buf[p->strorder].status & FDL_STROKE_MIRROR) && fdl->stroke_line_order[lineorder] != fdl->HaveCenterStrokeR)
			{
				if((fdl->stroke_buf[p->strorder].status & FDL_STROKE_MIRROR_TWO_LINES) == 0 || p->relation != fdl->stroke_buf[p->strorder].line[0])
				{
					DT32_int middle_pos;
					if(fdl->stroke_buf[p->strorder].status & FDL_STROKE_MIRROR_TWO_LINES)
						relation = fdl->stroke_buf[p->strorder].line[0];
					else relation = p->relation;

					if(fdl->HaveCenterStroke >= 0)
						middle_pos = fdl->path_buf[fdl->HaveCenterStroke].sx1;
					else if(p->lock & FDL_PATH_PRIVATE_MIRROR_PATH)
						middle_pos = fdl->path_buf[p->mirror_relation].sx1;
					else middle_pos = centerpoint;

					dist = middle_pos - fdl->path_buf[ relation ].sx1;
					if(p->lock & FDL_PATH_PRIVATE_PATH_RATE)
					{
						dist = (fdl->path_buf[p->mirror_relation].sx1 - fdl->path_buf[p->relation].sx1)*1000/p->stick_rate;
						newx1 = fdl->path_buf[ fdl->path_buf[p->mirror_relation].relation ].sx1 + dist;
					}else if(dist >= 0 && p->sx1 > middle_pos)
					{
						if(fdl->HaveCenterStroke >= 0)
							dist = fdl->path_buf[ fdl->path_buf[fdl->HaveCenterStroke].relation ].sx1 + dist;
						else if(p->lock & FDL_PATH_PRIVATE_MIRROR_PATH)
						{
							dist = fdl->path_buf[ fdl->path_buf[p->mirror_relation].relation ].sx1 + dist;
						}else
						{
							DT32_int middle;
							middle = centerpoint >> fdl->shift;
							newx1 = middle - (fdl->path_buf[ relation ].sx1 >> fdl->shift);
							dist = (middle + newx1) << fdl->shift;
						}// end if
						newx1 = dist;
					}else
					{
						newx1 = ((p->sx1 + (1 << fdl->shift)/2) >> fdl->shift) << fdl->shift;
						newx1 -= (1 << fdl->Frac2);
						dist = newx1 - fdl->path_buf[relation].sx1;
						dist = dist >> fdl->shift;
						newx1 = fdl->path_buf[relation].sx1 - (1 << fdl->Frac2) + ((dist | 0x01) << fdl->shift);
					}// end if
					Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);
					iFind = 1;
				}// end if
			}// end if

			if(iFind == 0)
			{
				if(p->lock & FDL_PATH_PRIVATE_PATH_RATE)
				{
					dist = (fdl->path_buf[p->mirror_relation].sx1 - fdl->path_buf[p->relation].sx1)*1000/p->stick_rate;
					newx1 = fdl->path_buf[ fdl->path_buf[p->mirror_relation].relation ].sx1 + dist;
					Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);
				}else if(p->lock & FDL_PATH_PRIVATE_MIRROR_PATH)
				{
					DT32_int middle_pos;
					middle_pos = fdl->path_buf[p->mirror_relation].sx1;
					dist = middle_pos - fdl->path_buf[ p->relation ].sx1;
					newx1 = fdl->path_buf[ fdl->path_buf[p->mirror_relation].relation ].sx1 + dist;
					Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);
				}else if((((p->sx1 >> fdl->Frac2) + 1) & fdl->recycle) != 0)
				{
					if(p->relation >= 0 && fdl->stroke_buf[p->strorder].line_type == FDL_STROKE_TYPE_VERT)
					{
						if(	(p->lock & (FDL_PATH_IsLFar| FDL_PATH_IsLNear)) !=0  && (fdl->path_buf[p->relation].lock & (FDL_PATH_IsLFar| FDL_PATH_IsLNear)) ==0
							 || (p->lock & (FDL_PATH_IsLFar| FDL_PATH_IsLNear)) ==0  && (fdl->path_buf[p->relation].lock & (FDL_PATH_IsLFar| FDL_PATH_IsLNear)) !=0)
						{
							newx1 = ((p->sx1 + (1 << fdl->shift)/2) >> fdl->shift) << fdl->shift;
							newx1 -= (1 << fdl->Frac2);
						}else
						{
							newx1 = ((fdl->path_buf[p->relation].sx1 >> fdl->Frac2) + (fdl->recycle+1)*(fdl->stroke_weightY)/10 - 1);
							newx1 = (newx1 << fdl->Frac2);
						}
					}else
					{
						newx1 = ((p->sx1 + (1 << fdl->shift)/2) >> fdl->shift) << fdl->shift;
						newx1 -= (1 << fdl->Frac2);
					}// end if

					Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);
					for(i=0; i < fdl->stroke_line_num; i++)
					{
						if(i == lineorder) continue;
						p0 = fdl->path_buf + fdl->stroke_line_order[i];
						if(p0->sx1 < p->sx1) continue;
						if(IsVLineOverlayY(p, p0))
						{
							if((p0->lock & FDL_PATH_MustHide2) != 0 && p0->stick_stroke == p->strorder)
								continue;

							if(((*p0->sx01) - newx1 < (1 << fdl->shift)) && (p0->lock & FDL_PATH_IsRightOrButtom) == 0)
								newx1 = *p0->sx03 - (1 << fdl->Frac2) - (1 << fdl->shift);
							Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);
							iFind = 1;
							break;
						}// end if
	
					}// end for
	
				}else if(p->relation >= 0 && (p->sx1 - fdl->path_buf[p->relation].sx1) >= (2 << fdl->shift))
				{
					for(i=0; i < fdl->stroke_line_num; i++)
					{
						if(i == lineorder) continue;
						p0 = fdl->path_buf + fdl->stroke_line_order[i];
						if(p0->sx1 < p->sx1) continue;
						if(IsVLineOverlayY(p, p0))
						{
							if(( (*p0->sx03+1) - p->sx1 < (1 << fdl->shift)) && (p0->lock & FDL_PATH_IsRightOrButtom) == 0 && (p0->lock & (FDL_PATH_LOCK_sx1 | FDL_PATH_LOCK_sx3)))
							{
								newx1 = *p0->sx03 - (1 << fdl->Frac2) - (1 << fdl->shift);
								Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[lineorder], newx1);
							}// end if
							break;
						}// end if

					}// end for

				}// end if
			}// end if
		}// end if
	}// end if
	
	
}// end Do_AlignThisStrokeLineV

DT_void GetCenterPointInGroup(pFdlRasterData fdl, DT32_int *centerpoint)
{
	DT32_int curgroup=-1;
	DT32_int i, stroke_order;
	TRect *rect;

	*centerpoint = 0;
	for(i=0; i < fdl->stroke_num; i++)
	{
		stroke_order = fdl->stroke_order[i];
		if(fdl->group_wrk[stroke_order] != 0xFF)
		{
			curgroup = FDL_MAIN_GROUP(fdl->group_wrk[stroke_order]) >> (8-MAIN_GROUP_BIT);
			rect = &fdl->main_group_rect[ curgroup ];
			*centerpoint = rect->left + (rect->right - rect->left)/2;
			break;
		}// end if
	}// end for
}

DT_void CheckStrokeMirrorStatusInGroup(pFdlRasterData fdl, DT32_int grpcenterpoint, DT32_int *centerestidx, DT32_int needsortfirst)
{
	DT32_int i, j, dist, centerpoint, xtolerance=0, cp=-1, lastx = 0x00FFFFFF;
	PATH_UNIT *p = fdl->path_buf;
	DT32_int cp2=-1, lastx2=0x00FFFFFF;

#ifdef TOLERANCE_X
	xtolerance = TOLERANCE_X;
#endif

	fdl->HaveCenterStroke = -1;
	fdl->HaveCenterStrokeR = -1;

	if(needsortfirst){
		Do_SortCollectVLines(fdl);
		GetCenterPointInGroup(fdl, &centerpoint);
	}else{
		centerpoint = grpcenterpoint;
	}
	
	//Get which is the central line.
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		p = fdl->path_buf + fdl->stroke_line_order[i];
		if(fdl->stroke_buf[p->strorder].stridmap == 4 || fdl->stroke_buf[p->strorder].stridmap == 2)
			continue;

		dist = p->sx1 - centerpoint;
		dist = DT_abs(dist);
		if(dist < lastx)
		{
			if(p->relation >= 0 && p->sx1 <= centerpoint && fdl->path_buf[p->relation].sx1 >= centerpoint && dist < lastx2)
			{
				lastx2 = dist;
				cp2 = i;
			}
			lastx = dist;
			cp = i;
		}// end if
	}// end for

	//find the strokes which  won two vertical boundary lines, as it is mirror stroke.
	for(i=0; i < fdl->stroke_num; i++)
	{
		DT32_int stroke_order;
		stroke_order = fdl->stroke_order[i];
		if(fdl->group_wrk[stroke_order] != 0xFF)
		{
			if(fdl->stroke_buf[ stroke_order ].line_num >= 2 && fdl->path_buf[fdl->stroke_buf[ stroke_order ].line[0]].sx1 == fdl->stroke_buf[ stroke_order ].rect.left)
			{
				p = fdl->path_buf + fdl->stroke_buf[ stroke_order ].line[fdl->stroke_buf[ stroke_order ].line_num-1];
				if(p->relation >= 0 && fdl->path_buf[p->relation].sx1 == fdl->stroke_buf[ stroke_order ].rect.right)
				{
					fdl->stroke_buf[ stroke_order ].status |= FDL_STROKE_MIRROR_TWO_LINES;
//					DumpDebugString("stroke %d FDL_STROKE_MIRROR_TWO_LINES\n", stroke_order);
				}// end if
			}// end if
		}// end if
	}// end for

#if 0	// For fixed 0x6797 bug, Alan.
	// Try to find the mirror strokes.
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		DT32_int len;
		p = fdl->path_buf + fdl->stroke_line_order[i];
		if(p->sx1 >= centerpoint)
			break;
		dist = centerpoint - p->sx1;
		len = *p->sy03 - *p->sy01;
		for(j=cp; j < fdl->stroke_line_num; j++)
		{
			PATH_UNIT *p1 = fdl->path_buf + fdl->stroke_line_order[j];
			if(p->strorder != p1->strorder && fdl->stroke_buf[p->strorder].strid == fdl->stroke_buf[p1->strorder].strid &&
				p1->sx1 > centerpoint && p1->relation >= 0)
			{
				if(IsVLineOverlayY(p, p1))
				{
					p1 = fdl->path_buf + p1->relation;
					if(DT_abs(dist - (p1->sx1 - centerpoint)) < (1 << fdl->shift)/2 && DT_abs(len - (*p1->sy03 - *p1->sy01)) <= (1 << fdl->shift))
					{
						//DumpDebugString("path %d %d FDL_PATH_MIRROR_PATH\n", fdl->stroke_line_order[i], fdl->stroke_line_order[j]);
						p1 = fdl->path_buf + fdl->stroke_line_order[j];
						p1->lock |= FDL_PATH_MIRROR_PATH;
						p1->mirror_relation = p->relation;
						break;
					}// end if
				}// end if
			}// end if
		}// end for
	}// end for
#endif
	for(i=0; i < fdl->stridcnt; i++)
	{
		if(fdl->stroke_buf[i].stridmap == 0)	// check all `-` stroke
		{
			DT32_int diff=0, newdiff;
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			for(j=0; j < fdl->stroke_line_num; j++)
			{
				PATH_UNIT *p1 = fdl->path_buf + fdl->stroke_line_order[j];
				if(p1->relation >= 0 && (p->sx1 < p1->sx1 && p1->sx1 < p[2].sx1))
				{
					PATH_UNIT *p2 = fdl->path_buf + p1->relation;
					if(DT_abs((p1->sx1 - p->sx1) - (p[2].sx1 - p2->sx1)) < (1 << fdl->shift)/2)
					{
						p[2].lock &= ~FDL_PATH_MustHide2;
						//DumpDebugString("stroke %d mirror -> %d\n", i, fdl->stroke_line_order[j]);
						p[2].lock &= ~FDL_PATH_PRIVATE_PATH_RATE;
						p[2].lock |= FDL_PATH_PRIVATE_MIRROR_PATH;
						p[2].mirror_relation = fdl->stroke_line_order[j];
						break;
					}else if(IsVLineOverlayY(p1, p))
					{
						if(p[2].lock & FDL_PATH_PRIVATE_PATH_RATE)
						{
							newdiff = DT_abs((p1->sx1 - p->sx1) - (p[2].sx1 - p2->sx1));
							if(newdiff < diff)
							{
								if(p[2].sx1 - p2->sx1 == 0)
									continue;
								diff = newdiff;
								p[2].mirror_relation = fdl->stroke_line_order[j];
								p[2].stick_rate = (p1->sx1 - p->sx1)*1000/(p[2].sx1 - p2->sx1);
							}// end if
						}else
						{
							if(p[2].sx1 - p2->sx1 == 0)
								continue;
							diff = DT_abs((p1->sx1 - p->sx1) - (p[2].sx1 - p2->sx1));
							p[2].mirror_relation = fdl->stroke_line_order[j];
							p[2].stick_rate = (p1->sx1 - p->sx1)*1000/(p[2].sx1 - p2->sx1);
							if(p[2].stick_rate < 1000/2) // Don't support over 50%.
								continue;
						}// end if
						p[2].lock &= ~FDL_PATH_MustHide2;
						p[2].lock |= FDL_PATH_PRIVATE_PATH_RATE;
						//DumpDebugString("stroke %d rate -> %d: %d, (%d, %d)\n", i, fdl->stroke_line_order[j], p[2].stick_rate, (p1->sx1 - p->sx1), (p[2].sx1 - p2->sx1));
					}// end if
				}// end if
			}// end for
		}else if(fdl->stroke_buf[i].stridmap == 2 || fdl->stroke_buf[i].stridmap == 4 || fdl->stroke_buf[i].stridmap == 18
			|| fdl->stroke_buf[i].stridmap == 30  || fdl->stroke_buf[i].stridmap == 34)
		{
			DT32_int a, b, ifind=0;
			if(fdl->stroke_buf[i].stridmap == 2)
			{
				a = 0; b = 10;
			}else if(fdl->stroke_buf[i].stridmap == 4)
			{
				a = 1; b = 8;
			}else if(fdl->stroke_buf[i].stridmap == 18)
			{
				a = 1; b = 10;
			}else if(fdl->stroke_buf[i].stridmap == 34)
			{
				a = 0; b = 9;
			}else if(fdl->stroke_buf[i].stridmap == 30)
			{
				a = 1; b = 10;
			}else continue;

			p = fdl->path_buf + fdl->stroke_buf[i].start;
			for(j=0; j < fdl->stroke_line_num; j++)
			{
				PATH_UNIT *p1 = fdl->path_buf + fdl->stroke_line_order[j];
				if(p1->relation >= 0 && (p[a].sx1 < p1->sx1 && p1->sx1 < p[b].sx1))
				{
					PATH_UNIT *p2 = fdl->path_buf + p1->relation;
					if(DT_abs((p1->sx1 - p[a].sx1) - (p[b].sx1 - p2->sx1)) < (1 << fdl->shift))		// (1 << fdl->shift)/2 have problem at 0x5272.
					{
						//DumpDebugString("stroke %d FDL_PATH_PRIVATE_MIRROR_PATH -> %d\n", i, fdl->stroke_line_order[j]);
						ifind = 1;
						p[b].lock |= FDL_PATH_PRIVATE_MIRROR_PATH;
						p[b].mirror_relation = fdl->stroke_line_order[j];
						p[b].stick_rate = (p1->sx1 - p[a].sx1);				// Note.
						break;
					}// end if
				}// end if
			}// end for

			if(ifind == 0)
			{
				for(j=0; j < fdl->stridcnt; j++)
				{
					if(fdl->stroke_buf[j].stridmap == 0)
					{
						DT32_int mid;
						PATH_UNIT *p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						if(*p[a].sy01 > p1[3].sy1 && IsLineOverlayX(p[a].sx1, p[b].sx1, p1[0].sx1, p1[2].sx1))
						{
							int a1, a2, a3;
							mid = (p1[2].sx1 + p1[0].sx1)/2;
							a1 = (mid - p[a].sx1);
							a2 = (p[b].sx1 - mid);
							a3 = (mid - p[a].sx1) - (p[b].sx1 - mid);
							if(DT_abs((mid - p[a].sx1) - (p[b].sx1 - mid)) < (1 << fdl->shift))
							{
								//DumpDebugString("stroke %d FDL_PATH_PRIVATE_MIRROR_LINE_PATH -> %d\n", i, j);
								p[b].lock |= FDL_PATH_PRIVATE_MIRROR_LINE_PATH;
								p[b].mirror_relation = j;
								p[b].stick_rate = (mid - p[a].sx1);				// Note.
								break;
							}// end if
						}// end if
					}// end if
				}// end for
			}// end if

		}// end if
	}// end for

	if(cp >= 0)
	{
		DT32_int cp_order;
		DT32_int p_idx, p_rel_idx;

		for(i=0; i < 2 && cp >= 0; i++)
		{
			p_idx = fdl->stroke_line_order[cp];
			p_rel_idx = fdl->path_buf[p_idx].relation;
			dist = centerpoint - (fdl->path_buf[p_idx].sx1 + fdl->path_buf[p_rel_idx].sx1)/2;

			cp_order = fdl->path_buf[p_idx].strorder;
			if(dist <= (1 << fdl->shift) && fdl->path_buf[p_idx].sx1 <= centerpoint && fdl->path_buf[p_rel_idx].sx1 >= centerpoint)
			{
				if(! ((fdl->stroke_buf[ cp_order ].status & FDL_STROKE_MIRROR_TWO_LINES) != 0 && fdl->stroke_buf[ cp_order ].line_num == 2))
				{
					fdl->HaveCenterStroke = fdl->stroke_line_order[cp];
					fdl->HaveCenterStrokeR = p->relation;

					p = fdl->path_buf + fdl->stroke_line_order[cp];
					p->lock |= FDL_PATH_MIRROR_CENTER;
//					DumpDebugString("stroke %d FDL_PATH_MIRROR_CENTER\n", fdl->stroke_line_order[cp]);
				}// end if
				break;
			}// end if

			if(i >= 1)
				break;
			cp = cp2;
		}// end for

		// ================= check which stroke need to do mirror ================
		//Condition: the line at the center as central line. The error distance is "(fdl->stroke_weightY/10) << fdl->shift"
		for(i=0; i < fdl->stroke_num; i++)
		{
			DT32_int stroke_order;
			stroke_order = fdl->stroke_order[i];
			if(fdl->group_wrk[stroke_order] != 0xFF)
			{
				DT32_int diff;
				diff = DT_abs((centerpoint - fdl->stroke_buf[ stroke_order ].rect.left) - (fdl->stroke_buf[ stroke_order ].rect.right - centerpoint));
				dist = fdl->stroke_buf[ stroke_order ].rect.left + (fdl->stroke_buf[ stroke_order ].rect.right - fdl->stroke_buf[ stroke_order ].rect.left)/2;
				dist = centerpoint - dist;
				if(DT_abs(dist) <= (1 << fdl->shift)			// Check if have center stroke.
					&& diff <= (1 << fdl->shift) && diff*100/((fdl->stroke_buf[ stroke_order ].rect.right-fdl->stroke_buf[ stroke_order ].rect.left)/2) < 50 )
				{
//					DumpDebugString("stroke %d FDL_STROKE_MIRROR\n", stroke_order);
					fdl->stroke_buf[ stroke_order ].status |= FDL_STROKE_MIRROR;
				}else
					fdl->stroke_buf[ stroke_order ].status &= ~FDL_STROKE_MIRROR;
			}// end if
		}// end for

	}// end if

	*centerestidx = cp;
}

DT_void Do_OutlineAlignX(pFdlRasterData fdl)
{
	DT32_int curgroup=-1;
	DT32_int i,j, lastx, lastline;
	DT32_int org_lastx, orgtmp_lastx=0;
	DT32_int doline = 0xFFFF;

	DT32_int m;
	PATH_UNIT *p0,*p0r,*p1;
	PATH_UNIT *p = fdl->path_buf;
	DT32_int needresort=0;
	DT32_int centerpoint=0, dist, cp=-1;

	fdl->HaveCenterStroke = -1;
	fdl->HaveCenterStrokeR = -1;
	Do_SortCollectVLines(fdl);
	Do_FindInterPath(fdl);
/*
	for(i=0; i < fdl->stroke_num; i++)
	{
		DT32_int stroke_order;
		stroke_order = fdl->stroke_order[i];
		if(fdl->group_wrk[stroke_order] != 0xFF)
		{
			TRect *rect;
			curgroup = FDL_MAIN_GROUP(fdl->group_wrk[stroke_order]) >> (8-MAIN_GROUP_BIT);
			rect = &fdl->main_group_rect[ curgroup ];
			centerpoint = rect->left + (rect->right - rect->left)/2;
			break;
		}// end if
	}// end for
*/
	GetCenterPointInGroup(fdl,&centerpoint);

#ifdef TOLERANCE_X
	// For fixed code 0x6FA4, 0x6688 bug. If could verify font data to ensure that never have this case, we could remove those code.
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		DT32_int ji;
		PATH_UNIT *p1;

		p = fdl->path_buf + fdl->stroke_line_order[i];
		for(ji=0; ji < fdl->stroke_line_num; ji++)
		{
			if(ji == i) continue;
			p1 = fdl->path_buf + fdl->stroke_line_order[ji];
			if(fdl->stroke_buf[p1->strorder].stridmap == 44)	// Adjust 0x7AEF:5 would break stroke, actually it doesn't need to adjust.
				continue;
			dist = *p1->sx01 - *p->sx01;
			if(dist !=0)
			{
				if(DT_abs(dist) < TOLERANCE_X)
				{
					needresort = 1;
					
					Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[ji], *p->sx01);

					if(p->relation >= 0 && p1->relation >= 0)			// Why crash in 0x371A.
					{
						dist = *(fdl->path_buf[p1->relation].sx01) - *(fdl->path_buf[p->relation].sx01);
						if(DT_abs(dist) < TOLERANCE_X)
						{
							Do_MoveStrokeXPath(fdl, p1->relation, *(fdl->path_buf[p->relation].sx01));
						}
					}
					
				}// end if
			}
		}// end for
	}// end for

#ifdef ENABLE_STICK_X
	GetVerStickRelationPath(fdl);
#endif

	if(needresort)
	{
		for(i=0; i < fdl->stridcnt; i++)
			GetStrokeRect(fdl, i, &(fdl->stroke_buf[i].rect));
		GetGroupRect(fdl);
		GetMainGroupRect(fdl);

		Do_SortCollectVLines(fdl);
	}// end if
	// =======================================================================================================================
#endif // TOLERANCE_X

	// Modified_By_Jacky_20100927
	CheckStrokeMirrorStatusInGroup(fdl, centerpoint, &cp, 0);
	if(cp >= 0)
	{
		// =============== do vertical line alignment ===========================
		Do_AlignStrokeLineV(fdl, fdl->stroke_line_order[cp], -1);			// Alignment center stroke.
	}// end if

	if(fdl->HaveCenterStroke >= 0)
	{
		PATH_UNIT *p1, *p2;
		PATH_UNIT *p0 = &fdl->path_buf[fdl->stroke_line_order[cp]];

		// Align all vertical lines which have FDL_STROKE_MIRROR_TWO_LINES attrib.
		for(i=0; i < cp; i++)
		{
			p1 = &fdl->path_buf[fdl->stroke_line_order[i]];
			if((fdl->stroke_buf[ p1->strorder ].status & (FDL_STROKE_MIRROR | FDL_STROKE_MIRROR_TWO_LINES)) == (FDL_STROKE_MIRROR | FDL_STROKE_MIRROR_TWO_LINES))
			{
				if(fdl->stroke_buf[p1->strorder].line[0] == fdl->stroke_line_order[i])
				{
					p2 = &fdl->path_buf[ fdl->stroke_buf[p1->strorder].line[ fdl->stroke_buf[p1->strorder].line_num-1 ] ];
					if(p1->relation >= 0 && p0->relation >= 0 && p2->relation >= 0)
					{
						DT32_int w1, w2;
						PATH_UNIT *p0a = &fdl->path_buf[p0->relation];
						p1 = &fdl->path_buf[p1->relation];
						if( ((p1->sx1< p0->sx1 ) && (p0a->sx1 < p2->sx1)) || (( p1->sx1<p2->sx1) && (p0a->sx1 < p0->sx1)))
						{
								w1 = (p0->sx1 - p1->sx1 + (1 << fdl->shift)/2) >> fdl->shift;
								w2 = (p2->sx1 - p0a->sx1 + (1 << fdl->shift)/2) >> fdl->shift;

								Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_line_order[i], p0->sx1 - ((w1 + fdl->stroke_weightY/10) << fdl->shift), p0->sx1);
								Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[p1->strorder].line[ fdl->stroke_buf[p1->strorder].line_num-1 ], ((p0a->sx1+(w1 << fdl->shift)+(1 << fdl->shift)/2) >> fdl->shift) << fdl->shift, p0a->sx1);
						}// end if
					}// end if
				}// end if
			}// end if
		}// end for
#if 0
		for(; i < fdl->stroke_num; i++)
		{
			p1 = &fdl->path_buf[fdl->stroke_line_order[i]];
			if(p1->strorder == p0->strorder)
				continue;
			if(p1->lock & FDL_PATH_MIRROR_PATH)
			{
				DT32_int middle, newx1;
				//DumpDebugString("FDL_PATH_MIRROR_PATH %d, %d\n", fdl->stroke_line_order[i], p1->mirror_relation);
				middle = centerpoint >> fdl->shift;
				p1 = fdl->path_buf + p1->mirror_relation;
				newx1 = middle - (p1->sx1 >> fdl->shift);
				if(newx1 < 1)
				{
					newx1 = 1;
					Do_MoveStrokeX(fdl, p1->relation, ((middle - (newx1 + fdl->stroke_weightY/10)) << fdl->shift) );
				}// end if
				newx1 = (middle + newx1) << fdl->shift;
				Do_MoveStrokeX(fdl, fdl->stroke_line_order[i], newx1);
			}// end if
		}// end for
#endif
	}else
	{
		PATH_UNIT *p1, *p2;

		// Align all vertical lines which have FDL_STROKE_MIRROR_TWO_LINES attrib.
		for(i=0; i < fdl->stroke_num; i++)
		{
			DT32_int stroke_order;
			stroke_order = fdl->stroke_order[i];

			if(fdl->group_wrk[stroke_order] != 0xFF)
			{
				p = fdl->path_buf + fdl->stroke_buf[stroke_order].start;
				if(fdl->stroke_buf[ stroke_order ].stridmap == 2 || fdl->stroke_buf[ stroke_order ].stridmap == 4
					|| fdl->stroke_buf[ stroke_order ].stridmap == 18
					|| fdl->stroke_buf[ stroke_order ].stridmap == 30
					|| fdl->stroke_buf[ stroke_order ].stridmap == 34
				)
				{
					DT32_int w1, w2;
					DT32_int a, b, c;
					if(fdl->stroke_buf[ stroke_order ].stridmap == 2)
					{
						a = 0; b = 10; c = 7;
					}else if(fdl->stroke_buf[ stroke_order ].stridmap == 4)
					{
						a = 1; b = 8; c = 7;
					}else if(fdl->stroke_buf[ stroke_order ].stridmap == 18)
					{
						a = 1; b = 10; c = 7;
					}else if(fdl->stroke_buf[i].stridmap == 34)
					{
						a = 0; b = 9; c = 6;
					}else
					{	// 30
						a = 1; b = 10; c = 7;
					}// end if

					if(p[b].lock & FDL_PATH_PRIVATE_MIRROR_LINE_PATH)
					{
						DT32_int mid;
						p1 = fdl->path_buf + fdl->stroke_buf[p[b].mirror_relation].start;

						mid = (p1[2].sx1 + p1[0].sx1)/2;
						mid = (mid >> fdl->shift) << fdl->shift;

						w1 = (mid - p[a].sx1);
						if(w1 < (1 << fdl->shift))
							w1 = 1 << fdl->shift;

						w2 = ((mid - w1) >> fdl->shift) << fdl->shift;
						Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[stroke_order].start + a, w2, mid);
						w2 = ((mid + w1) >> fdl->shift) << fdl->shift;
						Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[stroke_order].start+c, w2, mid);
					}else if(p[b].lock & FDL_PATH_PRIVATE_MIRROR_PATH)
					{
						DT32_int mid, w3;
						p1 = fdl->path_buf + p[b].mirror_relation;
						p2 = fdl->path_buf + p1->relation;

						if(IsVLineOverlayY(p1, p+a))
						{
							w1 = ((p1->sx1 - p[a].sx1) >> fdl->shift) << fdl->shift;
							if(w1 < (2 << fdl->shift))
								w1 = 2 << fdl->shift;
							mid = p1->sx1;
							w2 = ((mid - w1) >> fdl->shift) << fdl->shift;
							Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[stroke_order].start + a, w2, p1->sx1);

//							w2 = ((mid + w1) >> fdl->shift) << fdl->shift;
//							w2 = (((p2->sx1 + w1) >> fdl->shift) + fdl->stroke_weightY/10) << fdl->shift;

							w3 = (((p2->sx1 + w1) >> fdl->shift) + fdl->stroke_weightY/10) << fdl->shift;
							w3 = w2 + ((((w3-w2) >> fdl->shift)/2*2) << fdl->shift);
							Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[stroke_order].start+c, w3, p2->sx1);
						}else
						{
							w1 = ((p1->sx1 - p[a].sx1) >> fdl->shift) << fdl->shift;
							if(w1 < (1 << fdl->shift))
								w1 = 1 << fdl->shift;
							mid = p1->sx1;
							w2 = ((mid - w1) >> fdl->shift) << fdl->shift;
							Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[stroke_order].start + a, w2, p1->sx1);
							w2 = ((mid + w1) >> fdl->shift) << fdl->shift;
							Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[stroke_order].start+c, w2, p2->sx1);
						}// end if
					}else
					{
						p1 = fdl->path_buf + fdl->stroke_buf[stroke_order].start+c;
						p2 = fdl->path_buf + p1->relation;

						w2 = ((p[a].sx1 + (1 << fdl->shift)/2) >> fdl->shift) << fdl->shift;
						Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[stroke_order].start+a, w2, p1->sx1);
						w2 = ((p[a].sx1 + (p1->sx1 - p[a].sx1) + (1 << fdl->shift)/2) >> fdl->shift) << fdl->shift;
						Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[stroke_order].start+c, w2, p2->sx1);
					}// end if
				}else if((fdl->stroke_buf[ stroke_order ].status & (FDL_STROKE_MIRROR | FDL_STROKE_MIRROR_TWO_LINES)) == (FDL_STROKE_MIRROR | FDL_STROKE_MIRROR_TWO_LINES))
				{
					if(fdl->stroke_buf[stroke_order].line_num > 0)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[stroke_order].line[0];
						p2 = fdl->path_buf + fdl->stroke_buf[stroke_order].line[ fdl->stroke_buf[stroke_order].line_num-1 ];
						if(p1->relation >= 0 && p2->relation >= 0)
						{
							DT32_long diffs_cp;
							DT32_int w1;
							p1 = &fdl->path_buf[p1->relation];
							if( (p1->sx1 < centerpoint ) && (centerpoint < p2->sx1) )
							{
								diffs_cp = (((p1->sx1 + p2->sx1)/2)>>fdl->shift) - (centerpoint >> fdl->shift);
								if(DT_abs(diffs_cp) < (1 << fdl->shift))
								{
//									DT32_int centerpointalign = (centerpoint >> fdl->shift) << fdl->shift;
//									DT32_int centerpointalign2 = centerpointalign + (((fdl->recycle+1)*(fdl->stroke_weightY)/10 - 1) << fdl->Frac2);
//									w1 = (centerpointalign - p1->sx1 + (1 << fdl->shift)/2) >> fdl->shift;
//									Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[p1->strorder].line[0], centerpointalign - ((w1 + fdl->stroke_weightY/10) << fdl->shift), centerpointalign);
//									Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[p1->strorder].line[ fdl->stroke_buf[p1->strorder].line_num-1 ], ((centerpointalign2+(w1 << fdl->shift)) >> fdl->shift) << fdl->shift, centerpointalign2);

									DT32_int centerpointalign = (centerpoint >> fdl->shift) << fdl->shift;
									DT32_int centerpointalign2 = centerpointalign + (1 << fdl->shift) - (1 << fdl->Frac2);
									w1 = (centerpointalign - p1->sx1 + (1 << fdl->shift)/2) >> fdl->shift;

									Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[p1->strorder].line[0], centerpointalign - ((w1 + fdl->stroke_weightY/10) << fdl->shift), centerpointalign);
									Do_AlignStrokeLineVLeftRight(fdl, fdl->stroke_buf[p1->strorder].line[ fdl->stroke_buf[p1->strorder].line_num-1 ], (((centerpointalign2+(w1 << fdl->shift)) >> fdl->shift) << fdl->shift) - (fdl->stroke_weightY/10 << fdl->shift)*0, centerpointalign2);
								}// end if
							}// end if
						}// end if
					}else
					{
						// We will do mirror alignment for stroke which like '-' in Do_AlignThisStrokeLineV().
					}// end if
				}// end if
			}// end if
		}// end for
	}// end if

SVG_RETURN_STEP(526)
	//for(i=0; i< fdl->path_num; i++)
	for(i=0; i< fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		p->lock &= ~ (FDL_PATH_TMPLOCK_s1| FDL_PATH_TMPLOCK_s3);
	}

#if 1
	// =============================== do left side =================================
	if(cp >= 0)
		lastx = *(fdl->path_buf[ fdl->stroke_line_order[cp] ].sx01);
	else lastx = -1;
	lastline = cp;
	org_lastx = 0x00FFFFFF;
	doline = 0xFFFF;
	for(i=cp-1; i >= 0; i--)
	{
		p = fdl->path_buf + fdl->stroke_line_order[i];

		if(fdl->stroke_buf[p->strorder].line_num >=2)
		{
			for(j=0; j<fdl->stroke_buf[p->strorder].line_num; j++)
			{
				if( fdl->stroke_line_order[i] == fdl->stroke_buf[p->strorder].line[j])
					continue;
				else{
						p0 = fdl->path_buf+fdl->stroke_buf[p->strorder].line[j];
						p0r =  fdl->path_buf+p0->relation;
						p1 = fdl->path_buf+fdl->stroke_buf[p->strorder].start;
						for(m=0;m<fdl->stroke_buf[p->strorder].len; m++, p1++)
						{
							if( (p1->sx1 == p0->sx1 && p1->sy1 == p0->sy1)
								|| (p1->sx1 == p0->sx3 && p1->sy1 == p0->sy3)
								||(p1->sx1 == p0r->sx1 && p1->sy1 == p0r->sy1)
								||(p1->sx1 == p0r->sx3 && p1->sy1 == p0r->sy3)
								)
							{
								p1->lock |= FDL_PATH_TMPLOCK_s1;
							}
							if( (p1->sx3 == p0->sx1 && p1->sy3 == p0->sy1)
								|| (p1->sx3 == p0->sx3 && p1->sy3 == p0->sy3)
								||(p1->sx3 == p0r->sx1 && p1->sy3 == p0r->sy1)
								||(p1->sx3 == p0r->sx3 && p1->sy3 == p0r->sy3)
								)
							{
								p1->lock |= FDL_PATH_TMPLOCK_s3;
							}
						}
				}
			}
			
		}

		org_lastx = orgtmp_lastx;
	
		if(lastx != *(p->sx01) )
		{
			DT32_int k;
			if(org_lastx != *(p->sx01)) //The same coordinates do the same thing.
			{
				doline = 0xFFFF;
				if(i >= cp-1)
				{
					if(!IsVLineOverlayY(p, fdl->path_buf + fdl->stroke_line_order[cp]))
						doline = 0xFFFF;
					else
						doline = lastline;
				}else
				{
						
					for(k=i+1; k <= cp-1; k++)
					{
						if(IsVLineOverlayY(p, fdl->path_buf + fdl->stroke_line_order[k]))
						{
							doline = k;
							break;
						}// end if
					}// end for
				}// end if
			}
			orgtmp_lastx = *(p->sx01);
			Do_AlignStrokeLineV(fdl, fdl->stroke_line_order[i], doline);

			if(fdl->stroke_buf[p->strorder].line_num >=2)
			{
				p1 = fdl->path_buf+fdl->stroke_buf[p->strorder].start;
				for(m=0;m<fdl->stroke_buf[p->strorder].len; m++, p1++)
				{
					p1->lock &= ~ (FDL_PATH_TMPLOCK_s1| FDL_PATH_TMPLOCK_s3);
				}
			}
		}// end if

		lastx = *(p->sx01);
		lastline = i;
	}// end for


SVG_RETURN_STEP(530)

	//for(i=0; i< fdl->path_num; i++)
	for(i=0; i< fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		p->lock &= ~ (FDL_PATH_TMPLOCK_s1| FDL_PATH_TMPLOCK_s3);
	}

#if 1
	// =============================== do right side =================================
	if(cp >= 0)
		lastx = *(fdl->path_buf[ fdl->stroke_line_order[cp] ].sx01);
	else lastx = -1;
	lastline = cp;
	org_lastx = 0x00FFFFFF;
	doline = 0xFFFF;
	for(i=cp+1; i < fdl->stroke_line_num; i++)
	{
		p = fdl->path_buf + fdl->stroke_line_order[i];

		if(fdl->stroke_buf[p->strorder].line_num >=2)
		{
			for(j=0; j<fdl->stroke_buf[p->strorder].line_num; j++)
			{
				if( fdl->stroke_line_order[i] == fdl->stroke_buf[p->strorder].line[j])
					continue;
				else{
						p0 = fdl->path_buf+fdl->stroke_buf[p->strorder].line[j];
						p0r =  fdl->path_buf+p0->relation;
						p1 = fdl->path_buf+fdl->stroke_buf[p->strorder].start;
						for(m=0;m<fdl->stroke_buf[p->strorder].len; m++, p1++)
						{
							if( (p1->sx1 == p0->sx1 && p1->sy1 == p0->sy1)
								|| (p1->sx1 == p0->sx3 && p1->sy1 == p0->sy3)
								||(p1->sx1 == p0r->sx1 && p1->sy1 == p0r->sy1)
								||(p1->sx1 == p0r->sx3 && p1->sy1 == p0r->sy3)
								)
							{
								p1->lock |= FDL_PATH_TMPLOCK_s1;
							}
							if( (p1->sx3 == p0->sx1 && p1->sy3 == p0->sy1)
								|| (p1->sx3 == p0->sx3 && p1->sy3 == p0->sy3)
								||(p1->sx3 == p0r->sx1 && p1->sy3 == p0r->sy1)
								||(p1->sx3 == p0r->sx3 && p1->sy3 == p0r->sy3)
								)
							{
								p1->lock |= FDL_PATH_TMPLOCK_s3;
							}
						}
				}
			}
		}// end if

		org_lastx = orgtmp_lastx;
		if(lastx != *(p->sx01) )
		{
			DT32_int k;
			if(org_lastx != *(p->sx01)) //The same coordinates do the same thing.
			{
				DT32_int oversize;
				doline = 0xFFFF;
				if(cp >= 0 && i <= cp+1)		// For fixed fonttool crash.
				{
					oversize = IsVLineOverlayY2(p, fdl->path_buf + fdl->stroke_line_order[cp]);
					if(oversize < 0 || oversize < (1 << fdl->shift))
						doline = 0xFFFF;
					else doline = lastline;
				}else
				{
					for(k=i-1; k >= cp+1; k--)
					{
						if(IsVLineOverlayY2(p, fdl->path_buf + fdl->stroke_line_order[k]) > (1 << fdl->shift))
						{
							p1 = fdl->path_buf + fdl->stroke_line_order[k];
							if(p1->relation >= 0 && IsVLineOverlayY2(p, fdl->path_buf + p1->relation) > (1 << fdl->shift))
							{
								doline = k;
								break;
							}// end if
						}// end if
					}// end for
				}// end if
			}else;// the same doline_rd
			
			orgtmp_lastx = *(p->sx01);
			Do_AlignStrokeLineV(fdl, fdl->stroke_line_order[i], doline);
			
			if(fdl->stroke_buf[p->strorder].line_num >=2)
			{
				p1 = fdl->path_buf+fdl->stroke_buf[p->strorder].start;
				for(m=0;m<fdl->stroke_buf[p->strorder].len; m++, p1++)
				{
					p1->lock &= ~ (FDL_PATH_TMPLOCK_s1| FDL_PATH_TMPLOCK_s3);
				}
			}

		}// end if

		lastx = *(p->sx01);
		lastline = i;
	}// end for
#endif // right side
#endif

	// ========================================================================
	if(fdl->stroke_line_num > 0)
	{
		DT32_int centerstroke=-1;
		if(fdl->HaveCenterStroke >= 0)
			centerstroke = fdl->path_buf[fdl->HaveCenterStroke].strorder;
		Do_SortCollectAllVLines(fdl, FDL_MAIN_GROUP(fdl->group_fin[ fdl->path_buf[fdl->stroke_line_order[0]].strorder ]));
		for(i=0; i < fdl->stroke_line_num; i++)
		{
			p = fdl->path_buf + fdl->stroke_line_order[i];
			if(centerstroke == p->strorder)
				continue;
			if( (p->lock & FDL_PATH_IsHide)==0)
			{	//if it isn't a hidden path.
				if(p->relation >= 0 && fdl->path_buf[p->relation].dir == FDL_PATH_VERT &&
					((p->lock & (FDL_PATH_LOCK_sx1| FDL_PATH_LOCK_sx3)) == 0 || (p->lock & FDL_PATH_MIRROR_PATH && fdl->HaveCenterStroke < 0)) )
				{
					Do_AlignThisStrokeLineV(fdl, i, centerpoint);
				}// end if
			}// end if

		}// end for
	}// end if

//#ifdef ENABLE_STICK_X
	CheckVerStickRelationPath(fdl);
//#endif

	for(i=0; i< fdl->path_buf_pt_num; i++, p++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if( (p->idx_interline >=0) && (p->relation>=0) && (p->dir == FDL_PATH_VERT))
		{
			Do_AvgInterXPath(fdl, fdl->path_buf_pt[i]);
		}
	}
	
}// end Do_OutlineAlignX

DT_void GetHorStickRelationPath(pFdlRasterData fdl)
{
	DT32_int i, j;
	PATH_UNIT *p;

	// For find out which path is sticky.
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		DT32_int dist;
		PATH_UNIT *p1;

		p = fdl->path_buf + fdl->stroke_line_order[i];
		if(p->relation >= 0)
		{
			{	// Only correct vertical line.
				//for(j=0; j < fdl->path_num; j++)
				for(j=0;j <fdl->path_buf_pt_num; j++)
				{
					//p1 = fdl->path_buf + j;
					p1 = fdl->path_buf + fdl->path_buf_pt[j];
					if(p1->strorder == p->strorder || (p1->dir != FDL_PATH_HORZ))
						continue;
					if(p1->relation >= 0 && (p1->lock & FDL_PATH_IsRightOrButtom) != 0)
					{
						if(p1->sy1 > p->sy1 && p1->dir == FDL_PATH_HORZ)
						{
							if(IsVLineOverlayX(fdl->path_buf+p->relation, p1))
							{
								dist = *p1->sy01 - *(fdl->path_buf[p->relation].sy03);
								if(DT_abs(dist) <= (fdl->stroke_NormalWeightX/10 << fdl->shift) &&
										(p->sy1 <= p1->sy1 && p1->sy1 <= fdl->path_buf[p->relation].sy1))
								{
//										p1->stick_relation_path = fdl->stroke_line_order[i];
									p1->stick_relation_path = p->relation;
									//DumpDebugString("  strick relation %d -> %d\n", j, p1->stick_relation_path);
								}// end if
							}// end if
						}// end if
					}else if(p1->sy1 >= p->sy1)
					{
						if(IsVLineOverlayX(p, p1) && p1->dir == FDL_PATH_HORZ)
						{
							if(p->sy1 <= p1->sy1 && p1->sy1 <= (p->sy1 + (fdl->path_buf[p->relation].sy1 - p->sy1)*110/100)	// Add extra 10% tolerance, Alan.
											&& *(p->sx01)<= *(p1->sx01) &&  *(p1->sx03) <= *(p->sx03) )
							{
								if((p1->sy1 - p->sy1) > (fdl->path_buf[p->relation].sy1 - p->sy1))
									p1->stick_relation_path = p->relation;
								else p1->stick_relation_path = fdl->stroke_line_order[i];
								//DumpDebugString("strick %d -> %d\n", j, p1->stick_relation_path);
							}// end if
						}// end if
					}// end if

				}// end for
			}// end if

		}// end if
	}// end for

}// end GetHorStickRelationPath

DT_void GetVerStickRelationPath(pFdlRasterData fdl)
{
	DT32_int i, j;
	PATH_UNIT *p;

	// For find out which path is sticky.
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		PATH_UNIT *p1;
		DT32_int dist;

		p = fdl->path_buf + fdl->stroke_line_order[i];
		if(p->relation >= 0)
		{
			{	// Only correct horizontal line.
				//for(j=0; j < fdl->path_num; j++)
				for(j=0; j < fdl->path_buf_pt_num; j++)
				{
					//p1 = fdl->path_buf + j;
					p1 = fdl->path_buf + fdl->path_buf_pt[j];
					if(p1->strorder == p->strorder || (p1->dir != FDL_PATH_VERT))
						continue;
					if(p1->relation >= 0 && (p1->lock & FDL_PATH_IsRightOrButtom) != 0)
					{
						if(p1->sx1 > p->sx1 && p1->dir == FDL_PATH_VERT)
						{
							if(IsVLineOverlayY(fdl->path_buf+p->relation, p1))
							{
								dist = *p1->sx01 - *(fdl->path_buf[p->relation].sx03);
								if(DT_abs(dist) <= (fdl->stroke_weightY/10 << fdl->shift) &&
										p->sx1 <= p1->sx1 && p1->sx1 <= fdl->path_buf[p->relation].sx1)
								{
//									DumpDebugString("  strickv relation %d -> %d\n", j, p->relation);
									p1->stick_relation_path = p->relation;
								}// end if
							}// end if
						}// end if
					}else if(p1->sx1 >= p->sx1)
					{
						if(IsVLineOverlayY(p, p1) && p1->dir == FDL_PATH_VERT)
						{
							dist = *p1->sx01 - *p->sx01;
							if(DT_abs(dist) <= (fdl->stroke_weightY/10 << fdl->shift) &&
									p->sx1 <= p1->sx1 && p1->sx1 <= fdl->path_buf[p->relation].sx1)
							{
								p1->stick_relation_path = fdl->stroke_line_order[i];
//								DumpDebugString("strickv %d -> %d\n", j, fdl->stroke_line_order[i]);
							}// end if
						}// end if
					}// end if

				}// end for
			}// end if

		}// end if
	}// end for

}// end GetVerStickRelationPath

DT_void CheckHorStickRelationPath(pFdlRasterData fdl)
{
	PATH_UNIT *p, *p1;
	DT32_int i, j;
	TRect rect;

	//p = fdl->path_buf;
	//for(i=0; i < fdl->path_num; i++, p++)
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf+fdl->path_buf_pt[i];
		if(p->stick_relation_path >= 0 && p->dir == FDL_PATH_HORZ)
		{
			if(*p->sy01 != *(fdl->path_buf[p->stick_relation_path].sy01))
			{
				DT32_int targety = *(fdl->path_buf[p->stick_relation_path].sy01);
				DT32_int orgy = p->sy1;
				PATH_UNIT *p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;

				for(j=0; j < fdl->stroke_buf[p->strorder].len; j++, p1++)
				{
					if(p1->sy1 == orgy)
						p1->sy1 = targety;
					if(p1->sy3 == orgy)
						p1->sy3 = targety;
				}// end for
			}// end if
		}// end if
	}// end for

	for(i=0; i < fdl->stridcnt; i++)
	{
		DT32_int k;
		if((fdl->stroke_buf[i].status & FDL_STROKE_PartHide) == 0)
			continue;

		p = fdl->path_buf + fdl->stroke_buf[i].start;
		for(k=0; k < fdl->stroke_buf[i].len; k++, p++)
		{
			if(p->lock & FDL_PATH_PRIVATE_MIRROR_H_PATH)
			{
				DT32_int targety;
				DT32_int orgy;
				p1 = fdl->path_buf + p->stick_rate;
				targety = fdl->path_buf[p1->relation].sy1 + (p1->sy1 - fdl->path_buf[p->relation].sy1);

				orgy = p->sy1;
				p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(j=0; j < fdl->stroke_buf[p->strorder].len; j++, p1++)
				{
					if(p1->sy1 == orgy)
						p1->sy1 = targety;
					if(p1->sy3 == orgy)
						p1->sy3 = targety;
				}// end for
			}// end if

			if(p->lock & FDL_PATH_MustHide && p->stick_stroke >= 0)
			{
				DT32_int newy;
				GetStrokeRect(fdl, p->stick_stroke, &rect);
				newy = p->stick_rate*(rect.bottom - rect.top)/10000 + rect.bottom;

				{
					DT32_int targety = newy;
					DT32_int targety2 = p->sy3 + (newy - p->sy1);
					DT32_int orgy = p->sy1;
					DT32_int orgy2 = p->sy3;
					PATH_UNIT *p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
					p->sy2 += (newy - p->sy1);
					for(j=0; j < fdl->stroke_buf[p->strorder].len; j++, p1++)
					{
						if(p1->sy1 == orgy)
							p1->sy1 = targety;
						else if(p1->sy3 == orgy)
							p1->sy3 = targety;

						if(p1->sy1 == orgy2)
							p1->sy1 = targety2;
						else if(p1->sy3 == orgy2)
							p1->sy3 = targety2;
					}// end for
				}// end if
				break;
			}// end if
		}// end for

	}// end for

}// end CheckHorStickRelationPath

DT_void CheckVerStickRelationPath(pFdlRasterData fdl)
{
	PATH_UNIT *p;
	DT32_int i, j;
	TRect rect;
/*
	//p = fdl->path_buf;
	//for(i=0; i < fdl->path_num; i++, p++)
	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf+fdl->path_buf_pt[i];

		if(p->stick_relation_path >= 0 && p->dir == FDL_PATH_VERT)
		{
			if(*p->sx01 != *(fdl->path_buf[p->stick_relation_path].sx01))
			{
				DT32_int targetx = *(fdl->path_buf[p->stick_relation_path].sx01);
				DT32_int orgx = p->sx1;
				PATH_UNIT *p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(j=0; j < fdl->stroke_buf[p->strorder].len; j++, p1++)
				{
					if(p1->sx1 == orgx)
						p1->sx1 = targetx;
					if(p1->sx3 == orgx)
						p1->sx3 = targetx;
				}// end for
			}// end if

		}// end if
	}// end for
*/
	for(i=0; i < fdl->stridcnt; i++)
	{
		DT32_int k;
		if((fdl->stroke_buf[i].status & FDL_STROKE_PartHide2) == 0)
			continue;

		p = fdl->path_buf + fdl->stroke_buf[i].start;
		for(k=0; k < fdl->stroke_buf[i].len; k++, p++)
		{
			if(p->lock & FDL_PATH_MustHide2 && p->stick_stroke >= 0)
			{
				DT32_int newx;
				GetStrokeRect(fdl, p->stick_stroke, &rect);
				newx = p->stick_rate*(rect.right - rect.left)/10000 + rect.right;

				{
					DT32_int targetx = newx;
					DT32_int targetx2 = p->sx3 + (newx - p->sx1);
					DT32_int orgx = p->sx1;
					DT32_int orgx2 = p->sx3;
					PATH_UNIT *p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
					p->sx2 += (newx - p->sx1);
					for(j=0; j < fdl->stroke_buf[p->strorder].len; j++, p1++)
					{
						if(p1->sx1 == orgx)
							p1->sx1 = targetx;
						else if(p1->sx3 == orgx)
							p1->sx3 = targetx;

						if(p1->sx1 == orgx2)
							p1->sx1 = targetx2;
						else if(p1->sx3 == orgx2)
							p1->sx3 = targetx2;
					}// end for
				}// end if
				break;
			}// end if
		}// end for

	}// end for


	for(i=0; i < fdl->stridcnt; i++)
	{
		DT32_int x;
		switch(fdl->stroke_buf[i].stridmap)
		{
		case 19:
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			x = ((p[6].sx1 - (fdl->stroke_weightY << fdl->shift)/10 + (1 << fdl->Frac2)) >> fdl->shift) << fdl->shift;
			p[2].sx1 = p[2].sx3 = p[1].sx3 = p[3].sx1 = x;
			break;
		default:
			break;
		}// end if
		
	}// end for

}// end CheckVerStickRelationPath

DT_void Do_OutlineAlignY(pFdlRasterData fdl)
{
	DT32_int i, lasty, orgy, w, lastline;
	DT32_int j;
	PATH_UNIT *p = fdl->path_buf;
	PATH_UNIT *p_lastline = NULL;

	Do_SortCollectLinesAllH(fdl);
	Do_TOLERANCE_Y(fdl);

	Do_SortCollectLines(fdl);

#ifdef ENABLE_STICK_Y
	GetHorStickRelationPath(fdl);				// For find out which path is sticky.
#endif

#ifdef TOLERANCE_Y
	// For fixed code 0x53F7, 0x8A2D bug. If could verify font data to ensure that never have this case, we could remove those code.
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		PATH_UNIT *p1;
		DT32_int ji, dist;

		p = fdl->path_buf + fdl->stroke_line_order[i];
		w = (*p->sx03 - *p->sx01);
		if(p->relation >= 0 && (*(fdl->path_buf[p->relation].sy03) - *p->sy01 <= w))			// Only correct horizontal line.
		{
			for(ji=0; ji < fdl->stroke_line_num; ji++)
			{
				if(ji == i) continue;
				p1 = fdl->path_buf + fdl->stroke_line_order[ji];
				if(IsVLineOverlayX(p, p1))
				{
					dist = *p1->sy01 - *p->sy01;
					if(DT_abs(dist) < TOLERANCE_Y)
					{
						if(*p1->sy01 < *p->sy01)
							Do_MoveStrokeYPath(fdl, fdl->stroke_line_order[ji], *p->sy01);
						if(p1->relation >= 0)
						{
							dist = *(fdl->path_buf[p1->relation].sy01) - *(fdl->path_buf[p->relation].sy01);
							if(DT_abs(dist) < TOLERANCE_Y)
							{
								if(*(fdl->path_buf[p1->relation].sy01) < *(fdl->path_buf[p->relation].sy01))
									Do_MoveStrokeYPath(fdl, p1->relation, *(fdl->path_buf[p->relation].sy01));
							}
						}// end if
					}// end if
				}// end if
			}// end for

		}// end if
	}// end for

#endif // TOLERANCE_Y

	Do_SortCollectLines(fdl);  //Doing TOLERANCE_Y adjustment,maybe dis-order something.
	Do_SortCollectLines_Overlay(fdl);

SVG_RETURN_STEP(215)
	// =============== do horizontal line alignment ===========================
	orgy = 0x00FFFFFF;
	lasty = -1;
	lastline = -1;
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		p = fdl->path_buf + fdl->stroke_line_order[i];
		
		//for add X-axis overlay check.
		lastline = -1;
		orgy = 0x00FFFFFF;

		for(j=i-1; j>=0; j--)
		{	
			 p_lastline = fdl->path_buf + fdl->stroke_line_order[j];
			 if(!IsHLineOverlayX(p, p_lastline))
				 continue;
			 else{
					lastline = j;
					orgy = *(fdl->path_buf[ fdl->stroke_line_order[j] ].sy01);
					break;
			 }					 
		}
		
		w = (*p->sx03 - *p->sx01);
		if(p->relation >= 0 && (*(fdl->path_buf[p->relation].sy03) - *p->sy01 <= w))			// Is it 100% correct ?
		{
			if(lasty != *(fdl->path_buf[ fdl->stroke_line_order[i] ].sy01) )
			{
				//if(fdl->stroke_line_order[i] == 11)	//break;
				//DumpDebugString(" move %d, last %d\n", fdl->stroke_line_order[i], (lastline >= 0) ? fdl->stroke_line_order[lastline]:lastline);
				Do_AlignStrokeLineH(fdl, fdl->stroke_line_order[i], lastline, orgy, i-1);
			}// end if
			lasty = *(fdl->path_buf[ fdl->stroke_line_order[i] ].sy01);
		}// end if
	}// end for

}// end Do_OutlineAlignY

static DT_void Do_OutlineAlignSubV(pFdlRasterData fdl)
{
	DT32_int i, j, move, x1;
	PATH_UNIT *p, *p1;

	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(p->dir == FDL_PATH_VERT)
		{
			x1 = p->sx1 >> fdl->Frac2;
			if((p->lock & FDL_PATH_IsRightOrButtom) == 0)
			{
				x1 += fdl->hint_move_offsetX[(x1 & fdl->recycle)];
				if(x1 < 0) x1 = 0;
				move = x1 << fdl->Frac2;
			}else
			{
				x1 += fdl->hint_move_offsetX[(x1 & fdl->recycle) + (1 << 4)];
				if(x1 < 0) x1 = 0;
				move = (x1 << fdl->Frac2) - 1;
			}// end if

			if(move != p->sx1)
			{
				x1 = p->sx1;
				p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(j=0; j < fdl->stroke_buf[p->strorder].len; j++, p1++)
				{
					if(p1->sx1 == x1)
						p1->sx1 = move;
					if(p1->sx3 == x1)
						p1->sx3 = move;
				}// end for
			}// end if
		}// end if
	}// end for

}// end Do_OutlineAlignSubV

static DT_void Do_OutlineAlignSubH(pFdlRasterData fdl)
{
	DT32_int i, j, k, move, y1;
	PATH_UNIT *p, *p1, *p_relation;

	DT32_int max_idx, min_idx;
	DT16_short idx[3];

	DT16_short max_order,tmp_order, mid_order;
	DT32_int ac_idx;
	DT32_int org_width_line = 1<<fdl->shift;
	ac_idx = -1;

	DT_memcpy(fdl->path_tmp_buf, fdl->path_buf_pt, fdl->path_buf_pt_num*sizeof(fdl->path_buf_pt[0]));

	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		p->lock &= ~ (FDL_PATH_TMPLOCK_s1| FDL_PATH_TMPLOCK_s3);
	}


	for(i=0; i < fdl->stroke_num; i++)
	{
		if(fdl->stroke_buf[i].line_num >=1)
		{
			for(j=0; j<fdl->stroke_buf[i].line_num; j++)
			{
				p = fdl->path_buf+fdl->stroke_buf[i].line[j];
				if(p->relation >=0)
				{
					p_relation = fdl->path_buf+ p->relation;
					if((fdl->stroke_buf[i].line[j] > p->relation )
						&& (p->lock & (FDL_PATH_IsLFar| FDL_PATH_IsLNear)) ==0
						&& (p_relation->lock & (FDL_PATH_IsLFar| FDL_PATH_IsLNear)) ==0)
					{
						fdl->path_buf_pt[fdl->stroke_buf[i].line[j]] =  p->relation;
						fdl->path_buf_pt[p->relation] = fdl->stroke_buf[i].line[j];
					}
				}
			}

			p = fdl->path_buf+fdl->stroke_buf[i].line[0];
			if(fdl->stroke_buf[i].line_num == 2 && (p->lock & (FDL_PATH_IsLFar| FDL_PATH_IsLNear)) !=0)  
			{
				p = fdl->path_buf+fdl->stroke_buf[i].line[0];
				p1 = fdl->path_buf+fdl->stroke_buf[i].line[1];
				p_relation = fdl->path_buf+ p->relation;
			
				if( (p->lock & FDL_PATH_IsLFar) !=0  ||  (p_relation->lock & FDL_PATH_IsLFar) !=0 )
				{
					if((p->lock & FDL_PATH_IsLFar) !=0)
					{
						idx[2] = fdl->stroke_buf[i].line[0];
						idx[1] =  p->relation;
					}
					else
					{
						idx[2] = p->relation;
						idx[1] =  fdl->stroke_buf[i].line[0];
					}
					if( (p1->lock & FDL_PATH_IsLNear) !=0)
					{
						idx[0] = fdl->stroke_buf[i].line[1];
					}
					else{
						idx[0] = p1->relation;
					}
				}
				else
				{
					if((p->lock & FDL_PATH_IsLNear) !=0)
					{
						idx[0] = fdl->stroke_buf[i].line[0];
						idx[1] =  p->relation;
					}
					else
					{
						idx[0]= p->relation;
						idx[1] =  fdl->stroke_buf[i].line[0];
					}

					if( (p1->lock & FDL_PATH_IsLFar) !=0)
					{
						idx[2] = fdl->stroke_buf[i].line[1];
					}
					else{
						idx[2] = p1->relation;
					}
				}
				
				max_idx=0;
				min_idx=0;
				max_order = idx[0];
				tmp_order = idx[0];
				for(j=1; j<3; j++)
				{
					if(max_order< idx[j])
					{
						max_order = idx[j];
						max_idx = j;
					}
					if(tmp_order>idx[j])
					{
						tmp_order = idx[j];
						min_idx = j;
					}
				}

				for(j=0; j<3;j++)
				{
					if( max_order!=idx[j] && tmp_order !=idx[j] )
						mid_order = idx[j];
				}

				fdl->path_buf_pt[max_order] =  idx[2];
				if(idx[0] >idx[1])
				{
					fdl->path_buf_pt[tmp_order] =  idx[1];
					fdl->path_buf_pt[mid_order] =  idx[0];
				}
				else{
					fdl->path_buf_pt[tmp_order] =  idx[0];
					fdl->path_buf_pt[mid_order] =  idx[1];
				}

			}

	
			p = fdl->path_buf+fdl->stroke_buf[i].line[0];
			if(fdl->stroke_buf[i].line_num == 2 && (p->lock & (FDL_PATH_IsLFar| FDL_PATH_IsLNear)) ==0)
			{
			
				for(j=0; j<fdl->stroke_buf[i].line_num; j++)
				{
			
					p = fdl->path_buf+fdl->stroke_buf[i].line[j];	
					if(p->relation <0)
						continue;

					if(fdl->stroke_buf[i].line[j] > p->relation)
					{
						max_order = fdl->stroke_buf[i].line[j];
					}
					else
					{
						max_order =  p->relation;
					}
				
					for(k=j+1; k<fdl->stroke_buf[i].line_num; k++)
					{
						p1 = fdl->path_buf+fdl->stroke_buf[i].line[k];
						if(p1->relation >= 0)
						{
							if(max_order > fdl->stroke_buf[i].line[k]
								|| (max_order > p1->relation))
							{
									tmp_order= fdl->path_buf_pt[max_order];
									if(fdl->stroke_buf[i].line[k] > p1->relation)
									{
											fdl->path_buf_pt[max_order] =  fdl->path_buf_pt[p1->relation];
											fdl->path_buf_pt[p1->relation] = tmp_order;
									}
									else{
											fdl->path_buf_pt[max_order] =  fdl->path_buf_pt[fdl->stroke_buf[i].line[k]];
											fdl->path_buf_pt[fdl->stroke_buf[i].line[k]] = tmp_order;
									}
							}
						}// end if
					}
				}
			}	
		}
		
	}

	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];

		if(p->dir == FDL_PATH_HORZ)
		{
			y1 = p->sy1 >> fdl->Frac2;
			if((p->lock & FDL_PATH_IsRightOrButtom) == 0)
			{
				y1 += fdl->hint_move_offsetY[(y1 & fdl->recycle)];
				if(y1 < 0) y1 = 0;
				move = y1 << fdl->Frac2;

				if(p->relation >=0 )
				{
					p_relation = fdl->path_buf + p->relation;
					if(p_relation->dir== FDL_PATH_HORZ)
					{
						org_width_line =  (((p_relation->sy1- p->sy1 +(1<<(fdl->shift-1)) )>>fdl->shift)<<fdl->shift);
						if(org_width_line<=0) org_width_line = 1;
						ac_idx = fdl->path_buf_pt[i];
					}
				}

			}else
			{
				y1 += fdl->hint_move_offsetY[(y1 & fdl->recycle) + (1 << 4)];
				if(y1 < 0) y1 = 0;
				move = (y1 << fdl->Frac2) - 1;
				if(p->relation == ac_idx && (p->lock & FDL_PATH_IsLFar)==0) {
					p_relation = fdl->path_buf + p->relation;
					if(move -  p_relation->sy1 > (1<<fdl->shift) )
					{
						move = p_relation->sy1 + org_width_line-1;
					}
					ac_idx = -1;
				}
			
			}// end if

			if(move != p->sy1)
			{
				y1 = p->sy1;
				p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(j=0; j < fdl->stroke_buf[p->strorder].len; j++, p1++)
				{
					if(*p1->sy01 == y1 && (p1->lock & FDL_PATH_TMPLOCK_s1) == 0 )
					{
						*p1->sy01 = move;
						p1->lock |= FDL_PATH_TMPLOCK_s1;
					}
					if(*p1->sy03 == y1 && (p1->lock & FDL_PATH_TMPLOCK_s3) == 0)
					{
						*p1->sy03 = move;
						p1->lock |= FDL_PATH_TMPLOCK_s3;
					}
				}// end for
			}// end if
		}// end if
	}// end for

	DT_memcpy(fdl->path_buf_pt, fdl->path_tmp_buf, fdl->path_buf_pt_num*sizeof(fdl->path_buf_pt[0]));

}// end Do_OutlineAlignSubH

static DT_void Do_OutlineAlignSubH_OLD(pFdlRasterData fdl)
{
	DT32_int i, j, move, y1;
	PATH_UNIT *p, *p1;

	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(p->dir == FDL_PATH_HORZ)
		{
			y1 = p->sy1 >> fdl->Frac2;
			if((p->lock & FDL_PATH_IsRightOrButtom) == 0)
			{
				y1 += fdl->hint_move_offsetY[(y1 & fdl->recycle)];
				if(y1 < 0) y1 = 0;
				move = y1 << fdl->Frac2;
			}else
			{
				y1 += fdl->hint_move_offsetY[(y1 & fdl->recycle) + (1 << 4)];
				if(y1 < 0) y1 = 0;
				move = (y1 << fdl->Frac2) - 1;
			}// end if

			if(move != p->sy1)
			{
				y1 = p->sy1;
				p1 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
				for(j=0; j < fdl->stroke_buf[p->strorder].len; j++, p1++)
				{
					if(p1->sy1 == y1)
						p1->sy1 = move;
					if(p1->sy3 == y1)
						p1->sy3 = move;
				}// end for
			}// end if
		}// end if
	}// end for

}// end Do_OutlineAlignSubH

static DT_void GetAllStrokeRectAfterHint(pFdlRasterData fdl)
{
	DT32_int i, nowstroke;
	nowstroke = -1;
	for(i=0; i < fdl->path_buf_pt_num; i++)			// Only recount still used strokes rectangle.
	{
		DT32_int newstroke;
		newstroke = fdl->path_buf[fdl->path_buf_pt[i]].strorder;
		if(nowstroke != newstroke)
		{
			nowstroke = newstroke;
			GetStrokeRect(fdl, newstroke, &(fdl->stroke_buf[ newstroke ].rect));
		}// end if
	}// end for
}// end GetAllStrokeRectAfterHint

DT32_int IsLineOverlayX(DT32_int sx01, DT32_int sx03, DT32_int sx11, DT32_int sx13)
{
//	if((sx01 <= sx11 && sx11 <= sx03) || (sx01 <= sx13 && sx13 <= sx03) || (sx01 <= sx11 && sx13 <= sx03) || (sx11 <= sx01 && sx03 <= sx13))
//		return 1;
	if(sx01 <= sx11)
	{
		if( ((sx03 - sx01) - (sx11 - sx01)) > 0 )
			return 1;
	}else if(sx01 < sx13)
	{
		return 1;
	}// end if

	return 0;
}// end IsLineOverlayX

DT32_int IsLineOverlayY(DT32_int sy01, DT32_int sy03, DT32_int sy11, DT32_int sy13)
{
	if((sy01 <= sy11 && sy11 <= sy03) || (sy01 <= sy13 && sy13 <= sy03) || (sy01 <= sy11 && sy13 <= sy03) || (sy11 <= sy01 && sy03 <= sy13))
		return 1;

	return 0;
}// end IsLineOverlayY

static DT32_int Do_MeasureStrokeWeightX(pFdlRasterData fdl)
{
	TRect rect, maxrect[10];
	DT32_int i, maxline[10], lines, maxgroup=0, rectsize;
	DT32_int s, maxnum=0, newwx, newwxspace;

	DT_memset(maxline, 0, sizeof(maxline));
	for(i=0; i < sizeof(maxline)/sizeof(maxline[0]); i++)
	{
		maxrect[i].top = 0;
		maxrect[i].bottom = fdl->fontsizey << fdl->shift;
	}// end for

	fdl->path_tmp_num = 0;
	for(i=0; i < fdl->stridcnt; i++)
		fdl->path_tmp_buf[i] = 0xFF;

	for(s=0; s < fdl->stridcnt; s++)
	{
		if(fdl->path_tmp_buf[s] == 0xFF)
		{
			lines = 0;
			rect.left = fdl->stroke_buf[s].rect.left;
			rect.right = fdl->stroke_buf[s].rect.right;
			rect.top = fdl->stroke_buf[s].rect.top;
			rect.bottom = fdl->stroke_buf[s].rect.bottom;
			//DumpDebugString("\nstart %d (%d, %d)\n", s, rect.left, rect.right);
			for(i=s; i < fdl->stridcnt; i++)
			{
				if(fdl->path_tmp_buf[i] != 0xFF)
					continue;
				if(IsLineOverlayX(rect.left, rect.right, fdl->stroke_buf[i].rect.left, fdl->stroke_buf[i].rect.right) == 0)
					continue;

				fdl->path_tmp_buf[i] = maxnum;
				if(fdl->stroke_buf[i].line_type == FDL_STROKE_TYPE_HORZ)
				{
					DT32_int j, IsCancel=0;
					if(fdl->weight_modeH > 0)
					{
						for(j=0; j <= fdl->weight_modeH; j++)
						{
							if(((fdl->groupinfo.hintlist[j].stroke)&(~FDL_ALIGN_MODE)) == j )	// Bits 6,7 reserved for FDL_ALIGN_PACK
							{
								IsCancel = 1;
								break;
							}// end if
						}// end for
					}// end if

					if(IsCancel)
						continue;

					//DumpDebugString("  sub %d (%d, %d)\n", i, fdl->stroke_buf[i].rect.left, fdl->stroke_buf[i].rect.right);
					if(fdl->stroke_buf[i].line_num > 0)
					{
						lines += fdl->stroke_buf[i].line_num;
						if(*(fdl->path_buf[ fdl->stroke_buf[i].line[0] ].sy01) < rect.top)
							rect.top = *(fdl->path_buf[ fdl->stroke_buf[i].line[0] ].sy01);

						if(*(fdl->path_buf[ fdl->stroke_buf[i].line[fdl->stroke_buf[i].line_num-1] ].sy03) > rect.bottom)
							rect.bottom = *(fdl->path_buf[ fdl->stroke_buf[i].line[fdl->stroke_buf[i].line_num-1] ].sy03);
					}// end if
				}// end if

			}// end for

			if(lines > maxline[maxnum])
			{
				maxline[maxnum] = lines;
				maxrect[maxnum].top = rect.top;
				maxrect[maxnum].bottom = rect.bottom;
			}// end if
			maxnum++;
		}// end if

	}// end for

/*	if(fdl->groupinfo.fontid == 0x0000 && maxnum > 1)
	{
		fdl->groupinfo.groupnum = maxnum;
		fdl->groupinfo.grouplist = fdl->group_list;
		for(i=0; i < fdl->stridcnt; i++)
		{
			fdl->groupinfo.grouplist[i] = FDL_GROUP(fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
			DumpDebugString("group (%d, %d)\n", i, fdl->path_tmp_buf[i]);
		}// end for

		DT_memcpy(fdl->group_fin, fdl->groupinfo.grouplist, fdl->stridcnt * sizeof(DT8_uchar));
		// ======== recount group information, because we resetup group information ===========
		fdl->groupinfo.fontid = 0xFFFF;
		GetGroupRect(fdl);
		GetMainGroupRect(fdl);
	}// end if
*/

#ifdef AUTO_OFF
	for(i=0; i < maxnum; i++)
	{
		rectsize = (maxrect[i].bottom - maxrect[i].top) >> fdl->shift;
		rectsize = fdl->fontsizey - (((fdl->main_group_rect[maxgroup].bottom-fdl->main_group_rect[maxgroup].top)>>fdl->shift) - rectsize);
		if(rectsize < (maxline[i] + (maxline[i]-1))-1)
		{
			//DumpDebugString(" m[%d] %d, %d -> %d\n", fdl->fontsizey, i, rectsize, (maxline[i] + (maxline[i]-1)));
			return 1;
		}// end if
	}// end for
#endif

//#define COUNT_STROKE_WEIGHT

#ifdef COUNT_STROKE_WEIGHT
	if(fdl->stroke_weightX < 20)
		fdl->stroke_weightX = 10;
#else
	fdl->stroke_weightX = 10;
#endif

//	if(fdl->stroke_weightX > 10 && fdl->stroke_weightXSpace > 10)
	if(fdl->stroke_weightXSpace > 10)
	{
		newwx = fdl->stroke_weightX;
		newwxspace = fdl->stroke_weightXSpace;

		for(i=0; i < maxnum; i++)
		{
			rectsize = (maxrect[i].bottom - maxrect[i].top) >> fdl->shift;
			//DumpDebugString("max lines %d, %d, len %d[%d], (%d, %d)\n", maxline[i], (maxline[i]*2-1), rectsize, (fdl->main_group_rect[maxgroup].bottom-fdl->main_group_rect[maxgroup].top)>>fdl->shift);
			rectsize = fdl->fontsizey - (((fdl->main_group_rect[maxgroup].bottom-fdl->main_group_rect[maxgroup].top)>>fdl->shift) - rectsize);
//			if(newwx > 10 && newwxspace > 10)
			if(newwxspace >= 10)
			{
				DT32_int iFind=0, wx, ws, domode=0;
				//DumpDebugString("  ==========rectsize %d, %d, %d\n", rectsize, (maxline*fdl->stroke_weightX + (maxline-1)*fdl->stroke_weightXSpace/2)/10, (maxline*fdl->stroke_weightX/2 + (maxline-1)*fdl->stroke_weightXSpace/2)/10);
				rectsize *= 10;
				wx = newwx;
				ws = newwxspace;
				while(ws > 0)
				{
					if(rectsize >= (maxline[i]*wx + (maxline[i]-1)*ws))
					{
						iFind = 1;
						break;
					}// end if

					if(domode == 0)
					{
						domode = 1;
						if(ws % 10 != 0)
							ws = (ws/10)*10;
						else ws -= 10;
					}else
					{
						domode = 0;
/*						if(wx % 10 != 0)
							wx = (wx/10)*10;
						else wx -= 10;*/
					}// end if
				}// end for

				if(iFind)
				{
					if(wx <= newwx && ws <= newwxspace)
					{
						newwx = wx;
						newwxspace = ws;
						//DumpDebugString("wx %d, ws %d\n", wx, ws);
					}// end if
				}else
				{
					newwx = 10;
					newwxspace = 10;
				}// end if

			}// end if
		}// end for

//		fdl->stroke_weightX = newwx;
		fdl->stroke_weightXSpace = newwxspace;
	}// end if
fdl->stroke_weightXSpace=10;
#ifdef COUNT_STROKE_WEIGHT
		// ====================================================================
	if(fdl->stroke_weightX > 10)
	{
		newwx = fdl->stroke_weightX;
		for(i=0; i < maxnum; i++)
		{
			rectsize = (maxrect[i].bottom - maxrect[i].top) >> fdl->shift;
			rectsize = fdl->fontsizey - (((fdl->main_group_rect[maxgroup].bottom-fdl->main_group_rect[maxgroup].top)>>fdl->shift) - rectsize);
			if(newwx >= 10)
			{
				DT32_int iFind=0, wx, ws, domode=0;
				rectsize *= 10;
				wx = newwx;
				ws = fdl->stroke_weightXSpace;
				while(ws > 0)
				{
					if(rectsize >= (maxline[i]*wx + (maxline[i]-1)*ws))
					{
						iFind = 1;
						break;
					}// end if

					if(domode == 0)
					{
						domode = 1;
//						if(ws % 10 != 0)
//							ws = (ws/10)*10;
//						else ws -= 10;
					}else
					{
						domode = 0;
						if(wx % 10 != 0)
							wx = (wx/10)*10;
						else wx -= 10;
					}// end if
				}// end for

				if(iFind)
				{
					if(wx <= newwx && ws <= newwxspace)
					{
						newwx = wx;
//						newwxspace = ws;
						//DumpDebugString("wx %d, ws %d\n", wx, ws);
					}// end if
				}else
				{
					newwx = 10;
//					newwxspace = 10;
				}// end if

			}// end if

		}// end for

		if(newwx < 10)
			fdl->stroke_weightX = 10;
		else fdl->stroke_weightX = newwx;
	}// end if
#endif

	return 0;
}// end Do_MeasureStrokeWeightX


static DT32_int Do_MeasureStrokeWeightY(pFdlRasterData fdl)
{
	TRect rect, maxrect[10];
	DT32_int i, maxline[10], lines, maxgroup=0, rectsize;
	DT32_int s, maxnum=0, newwx, newwxspace;

	DT_memset(maxline, 0, sizeof(maxline));
	for(i=0; i < sizeof(maxline)/sizeof(maxline[0]); i++)
	{
		maxrect[i].left = 0;
		maxrect[i].right = fdl->fontsizex << fdl->shift;
	}// end for

	fdl->path_tmp_num = 0;
	for(i=0; i < fdl->stridcnt; i++)
		fdl->path_tmp_buf[i] = 0xFF;

	for(s=0; s < fdl->stridcnt; s++)
	{
		if(fdl->path_tmp_buf[s] == 0xFF)
		{
			lines = 0;
			rect.left = fdl->stroke_buf[s].rect.left;
			rect.right = fdl->stroke_buf[s].rect.right;
			rect.top = fdl->stroke_buf[s].rect.top;
			rect.bottom = fdl->stroke_buf[s].rect.bottom;
			//DumpDebugString("\nstart %d (%d, %d)\n", s, rect.left, rect.right);
			for(i=s; i < fdl->stridcnt; i++)
			{
				if(fdl->path_tmp_buf[i] != 0xFF)
					continue;
				if(IsLineOverlayY(rect.top, rect.bottom, fdl->stroke_buf[i].rect.top, fdl->stroke_buf[i].rect.bottom) == 0)
					continue;

				//DumpDebugString("  sub %d (%d, %d)\n", i, fdl->stroke_buf[i].rect.left, fdl->stroke_buf[i].rect.right);
				fdl->path_tmp_buf[i] = maxnum;
				if(fdl->stroke_buf[i].line_type == FDL_STROKE_TYPE_VERT)
				{
					DT32_int j, IsCancel=0;
					if(fdl->weight_modeV > 0)
					{
						for(j=0; j <= fdl->weight_modeV; j++)
						{
							if(((fdl->groupinfo.hintlist[fdl->hintlistH_num+j].stroke)&(~FDL_ALIGN_MODE)) == j )	// Bits 6,7 reserved for FDL_ALIGN_PACK
							{
								IsCancel = 1;
								break;
							}// end if
						}// end for
					}// end if

					if(IsCancel)
						continue;

					if(fdl->stroke_buf[i].line_num > 0)
					{
						lines += fdl->stroke_buf[i].line_num;
						if(*(fdl->path_buf[ fdl->stroke_buf[i].line[0] ].sx01) < rect.left)
							rect.left = *(fdl->path_buf[ fdl->stroke_buf[i].line[0] ].sx01);

						if(*(fdl->path_buf[ fdl->stroke_buf[i].line[fdl->stroke_buf[i].line_num-1] ].sx03) > rect.right)
							rect.right = *(fdl->path_buf[ fdl->stroke_buf[i].line[fdl->stroke_buf[i].line_num-1] ].sx03);
					}// end if
				}// end if

			}// end for

			if(lines > maxline[maxnum])
			{
				maxline[maxnum] = lines;
				maxrect[maxnum].left = rect.left;
				maxrect[maxnum].right = rect.right;
			}// end if
			maxnum++;
		}// end if

	}// end for

/*	if(fdl->groupinfo.fontid == 0x0000 && maxnum > 1)
	{
		fdl->groupinfo.groupnum = maxnum;
		fdl->groupinfo.grouplist = fdl->group_list;
		for(i=0; i < fdl->stridcnt; i++)
		{
			fdl->groupinfo.grouplist[i] = FDL_GROUP(fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
			//DumpDebugString("group (%d, %d)\n", fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
		}// end for

		DT_memcpy(fdl->group_fin, fdl->groupinfo.grouplist, fdl->stridcnt * sizeof(DT8_uchar));
		// ======== recount group information, because we resetup group information ===========
		fdl->groupinfo.fontid = 0xFFFF;
		GetGroupRect(fdl);
		GetMainGroupRect(fdl);
	}// end if
*/
#ifdef AUTO_OFF
	for(i=0; i < maxnum; i++)
	{
		rectsize = (maxrect[i].right - maxrect[i].left) >> fdl->shift;
		rectsize = fdl->fontsizex - (((fdl->main_group_rect[maxgroup].right-fdl->main_group_rect[maxgroup].left)>>fdl->shift) - rectsize);
		if(rectsize < (maxline[i] + (maxline[i]-1))-1)
		{
			//DumpDebugString(" m[%d] %d, %d -> %d\n", fdl->fontsizex, i, rectsize, (maxline[i] + (maxline[i]-1)));
			return 1;
		}// end if
	}// end for
#endif

	if(fdl->stroke_weightY > 10 && fdl->stroke_weightYSpace > 10)
	{
		newwx = fdl->stroke_weightY;
		newwxspace = fdl->stroke_weightYSpace;

		for(i=0; i < maxnum; i++)
		{
			rectsize = (maxrect[i].right - maxrect[i].left) >> fdl->shift;
			//DumpDebugString("max lines %d, %d, len %d[%d], (%d, %d)\n", maxline[i], (maxline[i]*2-1), rectsize, (fdl->main_group_rect[maxgroup].right-fdl->main_group_rect[maxgroup].left)>>fdl->shift);
			rectsize = fdl->fontsizex - (((fdl->main_group_rect[maxgroup].right - fdl->main_group_rect[maxgroup].left) >> fdl->shift) - rectsize);
			if(newwx > 10 && newwxspace > 10)
			{
				DT32_int iFind=0, wx, ws, domode=0;
				//DumpDebugString("  ==========rectsize %d, %d, %d\n", rectsize, (maxline*fdl->stroke_weightY + (maxline-1)*fdl->stroke_weightYSpace/2)/10, (maxline*fdl->stroke_weightY/2 + (maxline-1)*fdl->stroke_weightYSpace/2)/10);
				rectsize *= 10;
				wx = newwx;
				ws = newwxspace;
				while(ws > 0)
				{
					if(rectsize >= (maxline[i]*wx + (maxline[i]-1)*ws))
					{
						iFind = 1;
						break;
					}// end if

					if(domode == 0)
					{
						domode = 1;
						if(ws % 10 != 0)
							ws = (ws/10)*10;
						else ws -= 10;
					}else
					{
						domode = 0;
						if(wx % 10 != 0)
							wx = (wx/10)*10;
						else wx -= 10;
					}// end if
				}// end for

				if(iFind)
				{
					if(wx <= newwx && ws <= newwxspace)
					{
						newwx = wx;
						newwxspace = ws;
						//DumpDebugString("size %d => wx %d, ws %d\n", fdl->fontsizex, wx, ws);
					}// end if
				}else
				{
					newwx = 10;
					newwxspace = 10;
				}// end if

			}// end if
		}// end for

		fdl->stroke_weightY = newwx;
		fdl->stroke_weightYSpace = newwxspace;
	}// end if

	return 0;
}// end Do_MeasureStrokeWeightY

DT32_int GetAllOverlayStroke(pFdlRasterData fdl, TRect rect, DT32_int group, TRect *maxrect)
{
	DT32_int i, update=0;
	maxrect->left = 0x00FFFFFF;
	maxrect->right = 0;
	maxrect->top = 0x00FFFFFF;
	maxrect->bottom = 0x00;

	for(i=0; i < fdl->stridcnt; i++)
	{
		if(IsLineOverlayX(rect.left, rect.right, fdl->stroke_buf[i].rect.left, fdl->stroke_buf[i].rect.right))
		{
			if(fdl->path_tmp_buf[i] != group)
				update = 1;
			fdl->path_tmp_buf[i] = group;
			if(fdl->stroke_buf[i].rect.left < maxrect->left)
				maxrect->left = fdl->stroke_buf[i].rect.left;
			if(fdl->stroke_buf[i].rect.right > maxrect->right)
				maxrect->right = fdl->stroke_buf[i].rect.right;

			if(fdl->stroke_buf[i].rect.top < maxrect->top)
				maxrect->top = fdl->stroke_buf[i].rect.top;
			if(fdl->stroke_buf[i].rect.bottom > maxrect->bottom)
				maxrect->bottom = fdl->stroke_buf[i].rect.bottom;
		}// end if
	}// end for

	return update;
}// end GetAllOverlayStroke


static DT_void Do_AutoGroup(pFdlRasterData fdl)
{
	TRect rect, maxrect;
	DT32_int s, i, maxnum=0;

	fdl->path_tmp_num = 0;
	DT_memset(fdl->path_tmp_buf, 0xFF, fdl->stridcnt*sizeof(fdl->path_tmp_buf[0]));

	for(s=0; s < fdl->stridcnt; s++)
	{
		if(fdl->path_tmp_buf[s] == 0xFF)
		{
			rect.left = fdl->stroke_buf[s].rect.left;
			rect.right = fdl->stroke_buf[s].rect.right;
			rect.top = fdl->stroke_buf[s].rect.top;
			rect.bottom = fdl->stroke_buf[s].rect.bottom;

			while(GetAllOverlayStroke(fdl, rect, maxnum, &maxrect))
			{
				rect.left = maxrect.left;
				rect.right = maxrect.right;
				rect.top = maxrect.top;
				rect.bottom = maxrect.bottom;
			}// end if

			maxnum++;
		}// end if
	}// end for

// for(s=0; s < fdl->stridcnt; s++)
// DumpDebugString("  sub %d (%d)\n", s, fdl->path_tmp_buf[s]);
// DumpDebugString("  max group %d\n", maxnum);

	if(fdl->groupinfo.fontid == 0x0000 && maxnum > 0)
	{
		fdl->groupinfo.groupnum = maxnum;

		// 20110804: Jacky modified for memory
//		fdl->groupinfo.grouplist = fdl->group_list;
//		for(i=0; i < fdl->stridcnt; i++)
//		{
//			fdl->groupinfo.grouplist[i] = (DT8_uchar)FDL_GROUP(fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
//			//DumpDebugString("group (%d, %d)\n", fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
//		}// end for
//
//		DT_memcpy(fdl->group_fin, fdl->groupinfo.grouplist, fdl->stridcnt * sizeof(fdl->groupinfo.grouplist[0]));

		for(i=0; i < fdl->stridcnt; i++)
		{
			fdl->group_fin[i] = (DT8_uchar)FDL_GROUP(fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
		}// end for

		// ======== recount group information, because we resetup group information ===========
		fdl->groupinfo.fontid = 0xFFFF;
		GetGroupRect(fdl);
		GetMainGroupRect(fdl);
	}// end if

}	//Do_AutoGroup()

static DT_void Do_MeasureStrokeWeightW(pFdlRasterData fdl)
{

}

static DT_void Do_MeasureStrokeWeightH(pFdlRasterData fdl)
{
//	TRect *rect;
//	DT32_int s, i, maxline[10], lines, maxgroup=0, rectsize, maxnum=0;
//	DT32_int newwx, newwxspace;
//	
//	for(s=0; s < fdl->stroke_num; s++)
//	{
//		lines = 0;
//		rect = &fdl->stroke_buf[s].rect;
//		for(i=s; i < fdl->stroke_num; i++)
//		{
//			if(fdl->group_wrk[i] == 0xFF)
//				continue;
//			if(0==IsLineOverlayX(rect.left, rect.right, fdl->stroke_buf[i].rect.left, fdl->stroke_buf[i].rect.right))
//				continue;
//
//			if(fdl->stroke_buf[i].line_type == FDL_STROKE_TYPE_HORZ)
//			{
//				if(fdl->stroke_buf[i].line_num > 0)
//				{
//					lines += fdl->stroke_buf[i].line_num;
//				}// end if
//			}// end if
//
//		}// end for
//
//		if(lines > maxline[maxnum])
//		{
//			maxline[maxnum] = lines;
//		}// end if
//		maxnum++;
//	}// end for
	
}

static DT_void Do_MeasureStrokeWeight(pFdlRasterData fdl)
{
	TRect rect, maxrect[10];
	DT32_int s, i, maxline[10], lines, maxgroup=0, rectsize, maxnum=0;
	DT32_int newwx, newwxspace;

	DT_memset(maxline, 0, sizeof(maxline));
	for(i=0; i < 10; i++)
	{
		maxrect[i].top = 0;
		maxrect[i].bottom = fdl->fontsizey << fdl->shift;
	}// end for

	fdl->path_tmp_num = 0;
	//DT_memset(fdl->path_tmp_buf, 0xFF, sizeof(DT32_int)*fdl->stridcnt);
	DT_memset(fdl->path_tmp_buf, 0xFF, fdl->stridcnt*sizeof(fdl->path_tmp_buf[0]));

	for(s=0; s < fdl->stridcnt; s++)
	{
		if(fdl->path_tmp_buf[s] == 0xFF)
		{
			lines = 0;
			rect.left = 0x00FFFFFF;
			rect.right = 0;
			rect.top = 0x00FFFFFF;
			rect.bottom = 0x00;

			rect.left = fdl->stroke_buf[s].rect.left;
			rect.right = fdl->stroke_buf[s].rect.right;
			rect.top = fdl->stroke_buf[s].rect.top;
			rect.bottom = fdl->stroke_buf[s].rect.bottom;
			//DumpDebugString("\nstart %d (%d, %d)\n", s, rect.left, rect.right);
			for(i=s; i < fdl->stridcnt; i++)
			{
				if(fdl->path_tmp_buf[i] != 0xFF)
					continue;
				if(IsLineOverlayX(rect.left, rect.right, fdl->stroke_buf[i].rect.left, fdl->stroke_buf[i].rect.right) == 0)
					continue;

				//DumpDebugString("  sub %d (%d, %d)\n", i, fdl->stroke_buf[i].rect.left, fdl->stroke_buf[i].rect.right);
				fdl->path_tmp_buf[i] = maxnum;
				if(fdl->stroke_buf[i].line_type == FDL_STROKE_TYPE_HORZ)
				{
					DT32_int j, IsCancel=0;
					if(fdl->groupinfo.hintnum > 0)
					{
						for(j=0; j <= fdl->weight_modeH; j++)
						{
							if(fdl->groupinfo.hintlist[j].stroke == j)
							{
								IsCancel = 1;
								break;
							}// end if
						}// end for
					}// end if

					if(fdl->stroke_buf[i].line_num > 0)
					{
						lines += fdl->stroke_buf[i].line_num;
						if(*(fdl->path_buf[ fdl->stroke_buf[i].line[0] ].sy01) < rect.top)
							rect.top = *(fdl->path_buf[ fdl->stroke_buf[i].line[0] ].sy01);
	
						if(*(fdl->path_buf[ fdl->stroke_buf[i].line[fdl->stroke_buf[i].line_num-1] ].sy03) > rect.bottom)
							rect.bottom = *(fdl->path_buf[ fdl->stroke_buf[i].line[fdl->stroke_buf[i].line_num-1] ].sy03);
					}// end if
				}// end if

			}// end for

			if(lines > maxline[maxnum])
			{
				maxline[maxnum] = lines;
				maxrect[maxnum].top = rect.top;
				maxrect[maxnum].bottom = rect.bottom;
			}// end if
			maxnum++;
		}// end if

	}// end for

	if(fdl->groupinfo.fontid == 0x0000 && maxnum > 1)
	{
		fdl->groupinfo.groupnum = maxnum;

		// 20110804: Jacky modified for memory
//		fdl->groupinfo.grouplist = fdl->group_list;
//		for(i=0; i < fdl->stridcnt; i++)
//		{
//			fdl->groupinfo.grouplist[i] = (DT8_uchar)FDL_GROUP(fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
//			//DumpDebugString("group (%d, %d)\n", fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
//		}// end for
//
//		DT_memcpy(fdl->group_fin, fdl->groupinfo.grouplist, fdl->stridcnt * sizeof(fdl->groupinfo.grouplist[0]));

		for(i=0; i < fdl->stridcnt; i++)
		{
			fdl->group_fin[i] = (DT8_uchar)FDL_GROUP(fdl->path_tmp_buf[i], fdl->path_tmp_buf[i]);
		}// end for

		// ======== recount group information, because we resetup group information ===========
		fdl->groupinfo.fontid = 0xFFFF;
		GetGroupRect(fdl);
		GetMainGroupRect(fdl);
	}// end if

	if(fdl->stroke_weightX> 10 && fdl->stroke_weightXSpace > 10)
	{
		newwx = fdl->stroke_weightX;
		newwxspace = fdl->stroke_weightXSpace;

		for(i=0; i < maxnum; i++)
		{
			rectsize = (maxrect[i].bottom - maxrect[i].top) >> fdl->shift;
			//DumpDebugString("max lines %d, %d, len %d[%d], (%d, %d)\n", maxline, (maxline*2-1), rectsize, (fdl->main_group_rect[maxgroup].bottom-fdl->main_group_rect[maxgroup].top)>>fdl->shift);
			rectsize = fdl->fontsizey - (((fdl->main_group_rect[maxgroup].bottom-fdl->main_group_rect[maxgroup].top)>>fdl->shift) - rectsize);
			if(newwx > 10 && newwxspace > 10)
			{
				DT32_int iFind=0, wx, ws, domode=0;
				//DumpDebugString("  ==========rectsize %d, %d, %d\n", rectsize, (maxline*fdl->stroke_weightX + (maxline-1)*fdl->stroke_weightXSpace/2)/10, (maxline*fdl->stroke_weightX/2 + (maxline-1)*fdl->stroke_weightXSpace/2)/10);
				rectsize *= 10;
				wx = newwx;
				ws = newwxspace;
				while(ws > 0)
				{
					if(rectsize >= (maxline[i]*wx + (maxline[i]-1)*ws))
					{
						iFind = 1;
						break;
					}// end if
		
					if(domode == 0)
					{
						domode = 1;
						if(ws % 10 != 0)
							ws = (ws/10)*10;
						else ws -= 10;
					}else
					{
						domode = 0;
						if(wx % 10 != 0)
							wx = (wx/10)*10;
						else wx -= 10;
					}// end if
				}// end for
		
				if(iFind)
				{
					if(wx <= newwx && ws <= newwxspace)
					{
						newwx = wx;
						newwxspace = ws;
						//DumpDebugString("wx %d, ws %d\n", wx, ws);
					}// end if
				}else
				{
					newwx = 10;
					newwxspace = 10;
				}// end if
		
			}// end if
		}// end for

//		fdl->stroke_weightX = newwx;
//		fdl->stroke_weightXSpace = newwxspace;
	}// end if

}// end Do_MeasureStrokeWeight

static DT_void Do_ClipRect(pFdlRasterData fdl)
{
	DT32_int i, w, h;
	PATH_UNIT *p;

	w = (fdl->fontsizex) << fdl->shift;
	h = (fdl->fontsizey) << fdl->shift;

	for(i=0; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(*p->sx03 > w)
		{
			*p->sx03 = w;
			if(*p->sx01 > w)
				*p->sx01 = w;
			if(p->sx2 > w)
				p->sx2 = w;
		}else if(*p->sx01 < 0)
			*p->sx01 = 0;

		if(*p->sy03 > h)
		{
			*p->sy03 = h;
			if(*p->sy01 > h)
				*p->sy01 = h;
			if(p->sy2 > h)
				p->sy2 = h;
		}// end if

		if(*p->sy01 < 0)
		{
			*p->sy01 = 0;
			p->sy2 = 0;
		}// end if
		if(*p->sy03 < 0)
			*p->sy03 = 0;
	}// end for

}// end Do_ClipRect

// ======== collect this main group all stroke's horizontal line in all strokes, and sort  =========
DT_void Do_SortCollectMainGroupLines(pFdlRasterData fdl, DT32_int maingroup, DT8_char *groupcount)
{
	DT32_int i, j, w, stroke_order;
	PATH_UNIT *p;

	fdl->stroke_line_num = 0;
	for(i=0; i < fdl->stroke_num; i++)
	{
		stroke_order = fdl->stroke_order[i];
		for(j=0; j < fdl->stroke_buf[ stroke_order ].line_num; j++)
		{
			DT32_int IsOK, n;

			if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[stroke_order]) != maingroup)
				continue;
			p = fdl->path_buf + fdl->stroke_buf[ stroke_order ].line[j];
			w = (*p->sx03 - *p->sx01);
			if(p->relation >= 0 && (*(fdl->path_buf[p->relation].sy03) - *p->sy01 <= w))			// Is it 100% correct ?
			{
				IsOK=0;
				for(n=0; n < fdl->stroke_line_num; n++)
				{
					if(*(fdl->path_buf[fdl->stroke_line_order[n]].sy01) == *(fdl->path_buf[ fdl->stroke_buf[ stroke_order ].line[j] ].sy01))
					{
						IsOK=2;
						break;
					}else if(*(fdl->path_buf[fdl->stroke_line_order[n]].sy01) > *(fdl->path_buf[ fdl->stroke_buf[ stroke_order ].line[j] ].sy01))
					{
						DT_memcpy(fdl->path_tmp_buf, fdl->stroke_line_order+n, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
						fdl->stroke_line_order[n] = fdl->stroke_buf[ stroke_order ].line[j];
						DT_memcpy(fdl->stroke_line_order+n+1, fdl->path_tmp_buf, (fdl->stroke_line_num-n)*sizeof(fdl->stroke_line_order[0]));
						fdl->stroke_line_num++;
						IsOK = 1;
						break;
					}// end if
				}// end for

				if(IsOK == 2)
					continue;
				if(IsOK == 0)
					fdl->stroke_line_order[fdl->stroke_line_num++] = fdl->stroke_buf[ stroke_order ].line[j];
				groupcount[ FDL_SUB_GROUP(fdl->group_fin[stroke_order])  ]++;
			}// end if
		}// end for
	}// end for

}// end Do_SortCollectMainGroupLines

static DT_void Do_ShiftStrokeYPathDown(pFdlRasterData fdl, DT32_long path, DT32_int move, DT32_int maingroup)
{
	DT32_int i, j, domove, startx;
	PATH_UNIT *p = fdl->path_buf;

	startx = fdl->path_buf[path].sy1;

	for(i=0; i < fdl->stridcnt; i++)
	{
		if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[i]) == maingroup && fdl->group_fin[i] != 0xFF)
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if(fdl->stroke_buf[i].stridmap == 44 && (p[0].sy1 <= startx && startx <= p[4].sy3))
			{
				if(move > 0)
				{
					for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
					{
						if(j <= 1 || j == 5) continue;

						p->sy1 += move;
						p->sy3 += move;
						p->sy2 += move;
					}// end for

					p = fdl->path_buf + fdl->stroke_buf[i].start;
					p[2].sy1 = p[1].sy3;
					p[6].sy1 = p[5].sy3;
					p[2].sy3 = p[3].sy1;
					p[6].sy3 = p[7].sy1;
				}else
				{
					p[0].sy1 += move;
					p[0].sy3 += move;
					p[5].sy1 += move;
					p[5].sy3 += move;
					p[1].sy1 += move;
					p[1].sy3 += move;

					p[2].sy1 = p[1].sy1;
					p[6].sy1 = p[5].sy1;
				}// end if
			}else if(fdl->stroke_buf[i].stridmap == 115 && (p[0].sy1 <= startx && startx <= p[4].sy3))
			{
				if(move > 0)
				{
					for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
					{
						if(j <= 0 || j == 5 || j == 6) continue;

						p->sy1 += move;
						p->sy3 += move;
						p->sy2 += move;
					}// end for

					p = fdl->path_buf + fdl->stroke_buf[i].start;
					p[1].sy1 = p[0].sy3;
					p[7].sy1 = p[6].sy3;
					//p[2].sy3 = p[3].sy1;
					//p[6].sy3 = p[7].sy1;
				}else
				{
					p[0].sy1 += move;
					p[0].sy3 += move;
					p[5].sy1 += move;
					p[5].sy3 += move;
					p[6].sy1 += move;
					p[6].sy3 += move;

					p[7].sy1 = p[6].sy1;
					p[1].sy1 = p[0].sy1;
				}// end if
			}else
			{
				for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
				{
					domove = 0;
					if(p->sy1 > startx)
					{
						p->sy1 += move;
						domove += move;
					}// end if

					if(p->sy3 > startx)
					{
						p->sy3 += move;
						domove += move;
					}// end if

					p->sy2 += domove/2;
				}// end for

			}// end if
		}// end if
	}// end for

}// end Do_ShiftStrokeYPathDown

static DT_void Do_ShiftStrokeYPathDown2(pFdlRasterData fdl, DT32_long path, DT32_int move, DT32_int maingroup)
{
	DT32_int i, j, domove, startx;
	DT32_int inRange;
	PATH_UNIT *p = fdl->path_buf;

	startx = fdl->path_buf[path].sy1;

	for(i=0; i < fdl->stridcnt; i++)
	{
		if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[i]) == maingroup && fdl->group_fin[i] != 0xFF)
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;

			inRange = 0;
			if(fdl->stroke_buf[i].len<=4)
			{
				PATH_UNIT * plongerPath;		
				if( (p[0].sx1-p[0].sx3)*(p[0].sx1-p[0].sx3)+(p[0].sy1-p[0].sy3)*(p[0].sy1-p[0].sy3)
					> (p[1].sx1-p[1].sx3)*(p[1].sx1-p[1].sx3)+(p[1].sy1-p[1].sy3)*(p[1].sy1-p[1].sy3))
				{
					plongerPath = &(p[0]);	
				}
				else {
					plongerPath = &(p[1]);
				}

				if( DT_abs(plongerPath->sy1 - plongerPath->sy3) < DT_abs(plongerPath->sx1 - plongerPath->sx3) )
				{
					for(j=0; j < fdl->stroke_buf[i].len; j++)
					{
						if(p[j].sy1 >= startx || p[j].sy3 >= startx)
						{
							inRange = 1;
							break;
						}
					}
				}
			}
			if(fdl->stroke_buf[i].stridmap == 12 && (p[0].sy1 <= startx && startx <= p[3].sy3))
			{
				DT32_int high1 = p[3].sy3 - p[0].sy1;
				DT32_int high2 = high1 + move;
				if(high1 > -move)
				{
					for(j=0; j < fdl->stroke_buf[i].len; j++)
					{
						p[j].sy1 = p[0].sy1 + (p[j].sy1 - p[0].sy1)*high2/high1;
						p[j].sy2 = p[0].sy1 + (p[j].sy2 - p[0].sy1)*high2/high1;
						p[j].sy3 = p[0].sy1 + (p[j].sy3 - p[0].sy1)*high2/high1;
					}// end for
				}// end if
			}else if(fdl->stroke_buf[i].stridmap == 44 && (p[0].sy1 <= startx && startx <= p[4].sy3))
			{
				if(move > 0)
				{
					if(startx != p[5].sy1)
					{
						for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
						{
							if(j <= 1 || j == 5) continue;

							p->sy1 += move;
							p->sy3 += move;
							p->sy2 += move;
						}// end for

						p = fdl->path_buf + fdl->stroke_buf[i].start;
						p[2].sy1 = p[1].sy3;
						p[6].sy1 = p[5].sy3;
						p[2].sy3 = p[3].sy1;
						p[6].sy3 = p[7].sy1;
					}
					else
					{
						for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
						{
							p->sy1 += move;
							p->sy3 += move;
							p->sy2 += move;
						}// end for
					}
				}else
				{
					p[0].sy1 += move;
					p[0].sy3 += move;
					p[5].sy1 += move;
					p[5].sy3 += move;
					p[1].sy1 += move;
					p[1].sy3 += move;

					p[2].sy1 = p[1].sy1;
					p[6].sy1 = p[5].sy1;
				}// end if
			}
			
			/*else if(fdl->stroke_buf[i].stridmap == 55 && (p[0].sy1 <= startx && startx <= p[5].sy3))
			{
				if(move > 0)
				{
					for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
					{
						if(j <= 3 && j != 1) continue;

						p->sy1 += move;
						p->sy3 += move;
						p->sy2 += move;
					}// end for

					p = fdl->path_buf + fdl->stroke_buf[i].start;
					p[1].sy1 = p[0].sy3;
					p[4].sy1 = p[3].sy3;
				}else
				{
					p[0].sy1 += move;
					p[0].sy3 += move;
					p[3].sy1 += move;
					p[3].sy3 += move;
					p[2].sy1 += move;
					p[2].sy3 += move;

					p[1].sy1 = p[1].sy1;
					p[4].sy1 = p[3].sy1;
				}// end if
			}*/
			else if(fdl->stroke_buf[i].stridmap == 115 && (p[0].sy1 <= startx && startx <= p[4].sy3))
			{
				if(move > 0)
				{
					if(startx != p[5].sy1)
					{
						
						for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
						{
							if(j <= 0 || j == 5 || j == 6) continue;

							p->sy1 += move;
							p->sy3 += move;
							p->sy2 += move;
						}// end for

						p = fdl->path_buf + fdl->stroke_buf[i].start;
						p[1].sy1 = p[0].sy3;
						p[7].sy1 = p[6].sy3;
						//p[2].sy3 = p[3].sy1;
						//p[6].sy3 = p[7].sy1;
					}
					else{
						for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
						{
							p->sy1 += move;
							p->sy3 += move;
							p->sy2 += move;
						}// end for
					}
				}else
				{
					p[0].sy1 += move;
					p[0].sy3 += move;
					p[5].sy1 += move;
					p[5].sy3 += move;
					p[6].sy1 += move;
					p[6].sy3 += move;

					p[7].sy1 = p[6].sy1;
					p[1].sy1 = p[0].sy1;
				}// end if
			}
			else
			if(inRange ==1 && p[0].dir==FDL_STROKE_TYPE_UNKNOW && p[1].dir==FDL_STROKE_TYPE_UNKNOW)
			{
					for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
					{
						p->sy1 += move;
						p->sy3 += move;
						p->sy2 += move;
					}// end for
			}
			else
			if(inRange ==1 && p[0].dir==FDL_PATH_VERT && p[1].dir==FDL_PATH_HORZ && p[2].dir==FDL_PATH_VERT && p[3].dir==FDL_PATH_HORZ)
			{
					for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
					{
						p->sy1 += move;
						p->sy3 += move;
						p->sy2 += move;
					}// end for
			}
			else
			{
				for(j=0; j < fdl->stroke_buf[i].len; j++, p++)
				{
					domove = 0;
					if(p->sy1 >= startx)
					{
						p->sy1 += move;
						domove += move;
					}// end if

					if(p->sy3 >= startx)
					{
						p->sy3 += move;
						domove += move;
					}// end if

					p->sy2 += domove/2;
				}// end for

			}// end if
		}// end if
	}// end for

}// end Do_ShiftStrokeYPathDown2

static DT_void Do_GrowStrokeYPathWeight(pFdlRasterData fdl, DT32_long path, DT32_int add)
{
	PATH_UNIT *p = fdl->path_buf + path;
	if(p->relation >= 0)
	{
		Do_ShiftStrokeYPathDown(fdl, p->relation, add*(1 << fdl->shift), FDL_MAIN_GROUP(fdl->groupinfo.grouplist[p->strorder]) );
	}// end if
}// end Do_GrowStrokeYPathWeight

static DT_void Do_ReadjustGroupStrokeSpace(pFdlRasterData fdl, DT32_int group, DT32_int offset)
{
	DT32_int n;
	PATH_UNIT *p;

	for(n=0; n < fdl->stroke_line_num; n++)
	{
		p = fdl->path_buf + fdl->stroke_line_order[n];
		if(fdl->group_fin[p->strorder] == group)
		{
			Do_ShiftStrokeYPathDown(fdl, fdl->stroke_line_order[n], offset*(1 << fdl->shift), FDL_MAIN_GROUP(fdl->groupinfo.grouplist[p->strorder]));
		}// end if
	}// end for

}// end Do_ReadjustGroupStrokeSpace

static DT_void Do_ReadjustMainGroupStrokeSpace(pFdlRasterData fdl, DT32_int maingroup, DT32_int offset)
{
	DT32_int n;
	PATH_UNIT *p;
//return;					// Alan remove for test.
//DumpDebugString("Do_ReadjustMainGroupStrokeSpace %d, %d\n", maingroup, offset);
	for(n=0; n < fdl->stroke_line_num; n++)
	{
		p = fdl->path_buf + fdl->stroke_line_order[n];
		if(FDL_MAIN_GROUP(fdl->group_fin[p->strorder]) == FDL_SET_MAIN_GROUP(maingroup))
		{
//			DumpDebugString("    Do_ShiftStrokeYPathDown %d, %d\n", fdl->stroke_line_order[n], offset);
			Do_ShiftStrokeYPathDown(fdl, fdl->stroke_line_order[n], offset*(1 << fdl->shift), FDL_MAIN_GROUP(fdl->groupinfo.grouplist[p->strorder]));
		}// end if
	}// end for

}// end Do_ReadjustMainGroupStrokeSpace


#define MAX_GROUP			10
static TData orgarray[30];
static TData tmparray[30];
TRect mainrect[MAX_GROUP];
static DT_void Do_ReadjustStrokeSpace(pFdlRasterData fdl, DT32_int maingroupnum)
{
	DT32_int i, w, diff, lasty, maingroup=0;
	DT8_char groupcount[MAX_GROUP];
	PATH_UNIT *p = fdl->path_buf;

//	GetAllStrokeRectAfterHint(fdl);
//	GetMainGroupRectAfterHint(fdl, mainrect, SIZEOF_ARRAY(mainrect));
	for(maingroup=0; maingroup < maingroupnum; maingroup++)
	{
		DT32_int w1, w2, addw;
	
		addw = 0;
		GetAllStrokeRectAfterHint(fdl);
		GetMainGroupRectAfterHint(fdl, mainrect, SIZEOF_ARRAY(mainrect));

		DT_memset(groupcount, 0, sizeof(groupcount));
		Do_SortCollectMainGroupLines(fdl, FDL_SET_MAIN_GROUP(maingroup), groupcount);
		if(fdl->stroke_line_num > 0)
		{
			w1 = (fdl->main_group_rect[maingroup].bottom- fdl->main_group_rect[maingroup].top);
			w2 = (mainrect[maingroup].bottom - mainrect[maingroup].top);
			if(w1 >= w2)
				diff = ((w1 - w2 + (1 << fdl->shift)-1) >> fdl->shift);
			else continue;	//diff = fdl->fontsizey - ((w2 + (1 << fdl->shift)-1) >> fdl->shift);
//DumpDebugString("\n\ndiff1: %d: %d, %d\n", diff, fdl->stroke_NormalWeightX, fdl->stroke_weightX);
			if(fdl->stroke_NormalWeightX > fdl->stroke_weightX)
			{
				if(fdl->stroke_line_num <= diff)
				{
					w = diff/fdl->stroke_line_num;
					if(w*10 + fdl->stroke_weightX > fdl->stroke_NormalWeightX)
						w = (fdl->stroke_NormalWeightX - fdl->stroke_weightX)/10;

					addw += w;
					lasty = -1;	
					/*JOE-FIX*/
					for(i=0; i < fdl->stroke_line_num; i++)
					{
						p = fdl->path_buf + fdl->stroke_line_order[i];
						if(lasty != *(fdl->path_buf[ fdl->stroke_line_order[i] ].sy01) )
						{
							Do_GrowStrokeYPathWeight(fdl, fdl->stroke_line_order[i], w);
						}
						lasty = *(fdl->path_buf[ fdl->stroke_line_order[i] ].sy01);
					}
					diff = diff - (w*fdl->stroke_line_num);
				}// end if
			}// end if
//DumpDebugString("diff2: %d: stroke_line_num: %d\n", diff, fdl->stroke_line_num);

			if(diff >= (fdl->stroke_line_num-1))
			{
				if(fdl->stroke_line_num > 1)
				{
					w = diff/(fdl->stroke_line_num-1);
					if((addw+w)*10 + fdl->stroke_weightX > fdl->stroke_NormalWeightX)
						w = (fdl->stroke_NormalWeightX - fdl->stroke_weightX)/10;
					diff = diff - (w*(fdl->stroke_line_num-1));
				}else
				{
					w = 1;
					if((addw+w)*10 + fdl->stroke_weightX > fdl->stroke_NormalWeightX)
						w = (fdl->stroke_NormalWeightX - fdl->stroke_weightX)/10;
					diff -= w;
				}// end if

				addw += w;
				Do_ReadjustMainGroupStrokeSpace(fdl, maingroup, w);
			}// end if

//DumpDebugString("diff3: %d\n", diff);
			if(diff > 0)
			{
#if 1
				DT32_int j;
				//TData orgarray[30];
				//TData tmparray[30];

				DT_memset(orgarray, 0, sizeof(orgarray));
				for(i=0; i < fdl->stroke_line_num; i++)
				{
					orgarray[i].x = fdl->stroke_line_order[i];
					if(i > 0)
					{
						orgarray[i].y = fdl->path_buf[orgarray[i].x].sy3a - fdl->path_buf[orgarray[i-1].x].sy1a;
						orgarray[i].w = fdl->path_buf[orgarray[i].x].sy3 - fdl->path_buf[orgarray[i-1].x].sy1;
						orgarray[i].y = DT_abs(orgarray[i].y);
						orgarray[i].w = DT_abs(orgarray[i].w);
					}// end if
				}// end for

				fdl->path_tmp_num = 0;
				for(i=0; i < fdl->stroke_line_num; i++)
				{
					DT32_int IsOK;
					PATH_UNIT *p;

					p = fdl->path_buf + fdl->stroke_line_order[i];
					if(FDL_MAIN_GROUP(fdl->group_fin[p->strorder]) != (maingroup << (8-MAIN_GROUP_BIT)))
						continue;

					if(fdl->path_tmp_num == 0)
					{
						tmparray[fdl->path_tmp_num].x = orgarray[i].x;
						tmparray[fdl->path_tmp_num].w = orgarray[i].w;
						tmparray[fdl->path_tmp_num++].y = orgarray[i].y;
					}else
					{
						IsOK = 0;
						for(j=0; j < fdl->path_tmp_num; j++)
						{
							if(orgarray[i].y > tmparray[j].y)
							{
								DT_memcpy(fdl->path_tmp_buf, tmparray+j, (fdl->path_tmp_num-j)*sizeof(tmparray[0]));
								tmparray[j].x = orgarray[i].x;
								tmparray[j].y = orgarray[i].y;
								tmparray[j].w = orgarray[i].w;
								DT_memcpy(tmparray+j+1, fdl->path_tmp_buf, (fdl->path_tmp_num-j)*sizeof(tmparray[0]));
								fdl->path_tmp_num++;
								IsOK = 1;
								break;
							}// end if
						}// end for
	
						if(IsOK == 0)
						{
							tmparray[fdl->path_tmp_num].x = orgarray[i].x;
							tmparray[fdl->path_tmp_num].w = orgarray[i].w;
							tmparray[fdl->path_tmp_num++].y = orgarray[i].y;
						}// end if
					}// end if
				}// end for

				for(i=0; i < fdl->path_tmp_num && diff > 0; i++)
				{
					w = (tmparray[i].y - tmparray[i].w + (1 << fdl->shift)/2) >> fdl->shift;
					if(w > 0 && diff >= w)
					{
						Do_ShiftStrokeYPathDown2(fdl, tmparray[i].x, w*(1 << fdl->shift), maingroup);
						diff -= w;
					}// end if

				}// end for
#endif
//DumpDebugString("diff4: %d\n", diff);
//continue;
#if 0
				if(diff > 0)
				{
					DT32_int j;
					for(j=fdl->groupinfo.groupnum-1; j >= 0 && diff > 0; j--)
					{
						PATH_UNIT *p;
						for(i=0; i < fdl->path_tmp_num; i++)
						{
							p = fdl->path_buf + tmparray[i].x;
							if(fdl->group_fin[p->strorder] != j)
								continue;
							Do_ShiftStrokeYPathDown(fdl, tmparray[i].x, diff*(1 << fdl->shift), maingroup);
							diff = 0;
							break;
						}// end for
					}// end for
				}// end if
#endif
			}// end if
		}// end if

	}// end for

}// end Do_ReadjustStrokeSpace

static DT_void Do_GroupXAlignType(pFdlRasterData fdl)
{
	DT32_int i, j, grpcenter=0, centerestidx=-1, rel_strorder=-1;
	DT32_int group, n;

	for(group=0; group < ((fdl->groupinfo.groupnum) << (8-MAIN_GROUP_BIT)); group+=(1<<(8-MAIN_GROUP_BIT)))
	{
		n=0;
		fdl->group_wrknum = fdl->groupinfo.groupnum;
		for(i=0; i < fdl->stridcnt; i++)
		{
			if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[i]) == group)
			{
				n = 1;
				fdl->group_wrk[i] = fdl->groupinfo.grouplist[i];		// Note: the group_wrk[] store group id without shift right.
			}else fdl->group_wrk[i] = 0xFF;
		}// end for
		if(n == 0) break;
	
		for(j=0; j < fdl->stridcnt; j++)
		{
			GetStrokeVLines(fdl, j);
			GetStrokeVLineType(fdl, j);
		}// end for
		GetCenterPointInGroup(fdl,&grpcenter);
		CheckStrokeMirrorStatusInGroup(fdl, grpcenter, &centerestidx, 1);

		rel_strorder = -1;
		fdl->main_group_xtype[group] = GetGroupXAlignType(fdl, -1, centerestidx, &rel_strorder, group);
	}// end for
}

DT_void IdentifyStroke(pFdlRasterData fdl)
{
	DT32_int i, j, k;
	PATH_UNIT *p, *p1, *p2;
	DT32_int ifind;

	for(i=0; i < fdl->stridcnt; i++)
	{
		ifind = 0;
		switch(fdl->stroke_buf[i].len)
		{
		case 4:
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if( (p[0].lock & FDL_PATH_IsCurve) == 0 && (p[1].lock & FDL_PATH_IsCurve) == 0 && (p[2].lock & FDL_PATH_IsCurve) == 0
				 && (p[3].lock & FDL_PATH_IsCurve) == 0)
			{
				if(p[0].dir == FDL_PATH_VERT && p[1].dir == FDL_PATH_HORZ && p[2].dir == FDL_PATH_VERT && p[3].dir == FDL_PATH_HORZ)
				{
					if((*p[0].sy03 - *p[0].sy01) <= (*p[1].sx03 - *p[1].sx01))
					{
						DT32_int n;
						fdl->stroke_buf[i].stridmap = 0;		// Stroke ID 0. -

						for(n=0; n < 2; n++)
						{
							ifind = 0;
							for(j=0; j < fdl->stridcnt && ifind == 0; j++)
							{
								if(j == p->strorder) continue;
								if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
									fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy03 < fdl->stroke_buf[j].rect.bottom)
								{
									p1 = fdl->path_buf + fdl->stroke_buf[j].start;
									for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
									{
										if(p1->dir == FDL_PATH_VERT && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_VERT)
										{
											p2 = fdl->path_buf + p1->relation;
	//										if(*p1->sy01 <= *p->sy01 && *p->sy03 <= *p1->sy03 && p1->sx1 - (1<<fdl->shift)/3 < p->sx1 && p->sx1 < p2->sx1)
											if(*p1->sy01 <= *p->sy01 && *p->sy03 <= *p1->sy03)
											{
												ifind = 1;
												p->lock |= FDL_PATH_MustHide2;
												fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide2;
												p->stick_stroke = j;
												p->stick_rate = (p->sx1 - fdl->stroke_buf[j].rect.right)*10000/(fdl->stroke_buf[j].rect.right - fdl->stroke_buf[j].rect.left);
												//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
												break;
											}// end if
										}// end for
									}// end for
								}// end if

							}// end for
							p = p+2;
						}// end for

					}else
					{
						DT32_int n;
						fdl->stroke_buf[i].stridmap = 1;		// Stroke ID 1. |
#if 1
						p += 1;
						for(n=0; n < 2 && ifind == 0; n++)
						{
							ifind = 0;
							for(j=0; j < fdl->stridcnt && ifind == 0; j++)
							{
								if(j == p->strorder) continue;
								if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
									(fdl->stroke_buf[j].rect.top <= p->sy1 && p->sy1 <= fdl->stroke_buf[j].rect.bottom))
								{
									p1 = fdl->path_buf + fdl->stroke_buf[j].start;
									for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
									{
										if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
										{
											p2 = fdl->path_buf + p1->relation;
											if(*p1->sy01 <= p->sy1 && p->sy1 <= p2->sy1)
											{	// Have some bugs in this function, so I only use to be checked for below FDL_PATH_PRIVATE_MIRROR_H_PATH.
												ifind = 1;
//												p->lock |= FDL_PATH_MustHide;
/*												fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
												p->stick_stroke = j;
												p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.top)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
												//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
*/												break;
											}// end if
										}// end for
									}// end for
								}// end if

							}// end for
							p = p+2;
						}// end for
#endif
//						if((fdl->stroke_buf[p->strorder].status & FDL_STROKE_PartHide) == 0)
						if(ifind == 0)
						{
							p = fdl->path_buf + fdl->stroke_buf[i].start;
							for(j=0; j < fdl->stridcnt; j++)
							{
								if(j == p->strorder) continue;
								if((fdl->stroke_buf[j].rect.left <= p[1].sx1 && p[1].sx1 <= fdl->stroke_buf[j].rect.right ||
									fdl->stroke_buf[j].rect.left <= p[1].sx3 && p[1].sx3 <= fdl->stroke_buf[j].rect.right) &&
									(*p->sy01 < fdl->stroke_buf[j].rect.top && *p->sy03 > fdl->stroke_buf[j].rect.bottom))
								{
									ifind++;
									p1 = fdl->path_buf + fdl->stroke_buf[j].start;
									for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
									{
										if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
										{
											p2 = fdl->path_buf + p1->relation;
											if(DT_abs((p1->sy1 - p[1].sy1) - (p[3].sy1 - p2->sy1)) < (1 << fdl->shift)/2)
											{
												fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
												p[3].lock |= FDL_PATH_PRIVATE_MIRROR_H_PATH;
												p[3].stick_stroke = j;
												p[3].stick_rate = fdl->stroke_buf[j].start+k;
												//DumpDebugString(" stick%d[%d] %d FDL_PATH_PRIVATE_MIRROR_H_PATH %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
												break;
											}// end if
										}// end for
									}// end for
								}// end if
							}// end for

							if(ifind >= 4)		// If this | cross too much lines, then it must not the mirror path.
								p[3].lock &= ~FDL_PATH_PRIVATE_MIRROR_H_PATH;
						}// end if

					}// end if
				}else if(p[0].dir == FDL_PATH_NONE && ( (*p[3].sx03 - *p[3].sx01) < (*p[2].sy03 - *p[2].sy01) ))
				{
					if(p[1].dir == FDL_PATH_NONE && p[2].dir == FDL_PATH_NONE && p[3].dir == FDL_PATH_HORZ)
					{	// 0x811A: 11
						fdl->stroke_buf[i].stridmap = 88;
					}else
					{
						if(p[1].dir == FDL_PATH_VERT && p[2].dir == FDL_PATH_VERT && p[3].dir == FDL_PATH_HORZ)
						{	// 0x5F92: 2
							fdl->stroke_buf[i].stridmap = 139;
						}// end if

						for(j=0; j < fdl->stridcnt; j++)
						{
							if(j == p->strorder) continue;
							if(fdl->stroke_buf[j].rect.left <= *p->sx01 && *p->sx03 <= fdl->stroke_buf[j].rect.right &&
								fdl->stroke_buf[j].rect.top <= *p->sy01 && *p->sy03 <= fdl->stroke_buf[j].rect.bottom)
							{
								p[0].lock |= FDL_PATH_MustHide;
								fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;

								p->stick_stroke = j;
								p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
								//DumpDebugString(" stick0 %d:%d -> %d\n", i, 0, j);
								break;
							}// end if
						}// end for
					}// end if

				}else if(p[3].dir == FDL_PATH_NONE && ( (*p[1].sx03 - *p[1].sx01) < (*p[0].sy03 - *p[0].sy01) ))
				{
					p1 = p+3;
					for(j=0; j < fdl->stridcnt; j++)
					{
						if(j == p->strorder) continue;
						if(fdl->stroke_buf[j].rect.left <= *p1->sx01 && *p1->sx03 <= fdl->stroke_buf[j].rect.right &&
							fdl->stroke_buf[j].rect.top <= *p1->sy01 && *p1->sy03 <= fdl->stroke_buf[j].rect.bottom)
						{
							p1->lock |= FDL_PATH_MustHide;
							fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;

							p1->stick_stroke = j;
							p1->stick_rate = (p1->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
							//DumpDebugString(" stick2 %d:%d -> %d\n", i, 3, j);
							break;
						}// end if
					}// end for
				}else if(p[1].dir == FDL_PATH_HORZ && p[2].dir == FDL_PATH_VERT && ( (*p[1].sx03 - *p[1].sx01) < (*p[2].sy03 - *p[2].sy01) ))
				{
					p1 = p+1;
					for(j=0; j < fdl->stridcnt; j++)
					{
						if(j == p->strorder) continue;
						if(fdl->stroke_buf[j].rect.left <= *p1->sx01 && *p1->sx03 <= fdl->stroke_buf[j].rect.right &&
							fdl->stroke_buf[j].rect.top <= *p1->sy01 && *p1->sy03 <= fdl->stroke_buf[j].rect.bottom)
						{
							p1->stick_stroke = j;
							p1->stick_rate = (p1->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);

							p1->lock |= FDL_PATH_MustHide;
							fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
							//DumpDebugString(" stick %d:%d -> %d\n", i, 1, j);
							break;
						}// end if
					}// end for
					
				}// end if
			}else if( (p[0].lock & FDL_PATH_IsCurve) == 0 && (p[1].lock & FDL_PATH_IsCurve) != 0 && (p[2].lock & FDL_PATH_IsCurve) != 0
				&& (p[3].lock & FDL_PATH_IsCurve) == 0)
			{	/* 0x8A00 */
				fdl->stroke_buf[i].stridmap = 3;		// I think the stroke 3 and 7 are the same type, Alan.
//				DumpDebugString("Identidy Stroke %d %d[0x%x]\n", i, fdl->stroke_buf[i].stridmap, fdl->stroke_buf[i].stridmap);
				p = p+3;
				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
						fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy03 < fdl->stroke_buf[j].rect.bottom)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
						{
							if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
							{
								p2 = fdl->path_buf + p1->relation;
								if(p1->sy1 <= *p->sy01 && *p->sy03 <= p2->sy1 && *p1->sx01 < *p->sx01 && *p->sx03 < *p1->sx03)
								{
									ifind = 1;
									p->lock |= FDL_PATH_MustHide;
									fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
									p->stick_stroke = j;
									p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
//									DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
									break;
								}// end if
							}// end for
						}// end for
					}// end if

				}// end for

				ifind = 0;
				p = p = fdl->path_buf + fdl->stroke_buf[i].start;
				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
						fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy03 < fdl->stroke_buf[j].rect.bottom)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
						{
							if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
							{
								p2 = fdl->path_buf + p1->relation;
								if(p1->sy1 <= *p->sy01 && *p->sy03 <= p2->sy1 && *p1->sx01 < *p->sx01 && *p->sx03 < *p1->sx03)
								{
									ifind = 1;
									p->lock |= FDL_PATH_MustHide;
									fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
									p->stick_stroke = j;
									p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
									//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
									break;
								}// end if
							}// end for
						}// end for
					}// end if

				}// end for
			}else if( (p[0].lock & FDL_PATH_IsCurve) != 0 && (p[1].lock & FDL_PATH_IsCurve) == 0 && (p[2].lock & FDL_PATH_IsCurve) == 0
				&& (p[3].lock & FDL_PATH_IsCurve) != 0)
			{	/* 0x7406: 3 */
				fdl->stroke_buf[i].stridmap = 12;

/*				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(*p->sx01 < fdl->stroke_buf[j].rect.left && fdl->stroke_buf[j].rect.right < *p->sx03 &&
						fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy01 <= fdl->stroke_buf[j].rect.bottom)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
						{
							if(*p->sy01 <= *p1->sy01 && *p1->sy03 <= *(p[3].sy03))
							{
								ifind = 1;
								p->lock |= FDL_PATH_MustHide2;
								fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide2;
								p->stick_stroke = j;
								p->stick_rate = (p->sx1 - fdl->stroke_buf[j].rect.right)*10000/(fdl->stroke_buf[j].rect.right - fdl->stroke_buf[j].rect.left);
								DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
								break;
							}// end if
						}// end for
					}// end if

				}// end for
*/
			}else if( (p[0].lock & FDL_PATH_IsCurve) != 0 && (p[1].lock & FDL_PATH_IsCurve) == 0 && (p[2].lock & FDL_PATH_IsCurve) != 0
				&& (p[3].lock & FDL_PATH_IsCurve) == 0)
			{	/* 0x61B6: 4 */
				fdl->stroke_buf[i].stridmap = 38;
				p = p+1;
				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
						fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy03 < fdl->stroke_buf[j].rect.bottom)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
						{
							if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
							{
								p2 = fdl->path_buf + p1->relation;
								if(p1->sy1 <= *p->sy01 && *p->sy03 <= p2->sy1 && *p1->sx01 < *p->sx01 && *p->sx03 < *p1->sx03)
								{
									ifind = 1;
									p->lock |= FDL_PATH_MustHide;
									fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
									p->stick_stroke = j;
									p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
									//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
									break;
								}// end if
							}// end for
						}// end for
					}// end if

				}// end for
			}// end if
		}
		break;
		case 5:
		{	/* 0x596E */
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if( (p[0].lock & FDL_PATH_IsCurve) == 0 && (p[1].lock & FDL_PATH_IsCurve) != 0 && (p[2].lock & FDL_PATH_IsCurve) != 0
				&& (p[3].lock & FDL_PATH_IsCurve) != 0 && (p[4].lock & FDL_PATH_IsCurve) == 0)
			{	/* 0x90E1 */
				DT32_int sy = (p->sy1 + p->sy3)/2;
				fdl->stroke_buf[i].stridmap = 295;
				//DumpDebugString("Identidy Stroke %d %d[0x%x]\n", i, fdl->stroke_buf[i].stridmap, fdl->stroke_buf[i].stridmap);
				ifind = 0;
				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left <= *p->sx01 && *p->sx03 <= fdl->stroke_buf[j].rect.right &&
						fdl->stroke_buf[j].rect.top < sy && sy < fdl->stroke_buf[j].rect.bottom)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
						{
							if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
							{
								p2 = fdl->path_buf + p1->relation;
								if(p1->sy1 < sy && sy < p2->sy1 && *p1->sx01 < *p->sx01 && *p->sx03 < *p1->sx03)
								{
									ifind = 1;
									p->lock |= FDL_PATH_MustHide;
									fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
									p->stick_stroke = j;
									p->stick_rate = (sy - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
									//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
									break;
								}// end if
							}// end for
						}// end for
					}// end if

				}// end for
			}// end if
		}
		break;
		case 6:
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if( p[0].dir == FDL_PATH_HORZ && p[1].dir == FDL_PATH_VERT && p[2].dir == FDL_PATH_VERT && p[3].dir == FDL_PATH_HORZ
				&& p[4].dir == FDL_PATH_VERT && p[5].dir == FDL_PATH_HORZ)
			{	/* 0x523A: 1 */
				fdl->stroke_buf[i].stridmap = 55;
			}else
			if( p[0].dir == FDL_PATH_VERT && p[1].dir == FDL_PATH_HORZ && p[2].dir == FDL_PATH_VERT && p[3].dir == FDL_PATH_HORZ
				&& p[4].dir == FDL_PATH_VERT && p[5].dir == FDL_PATH_HORZ)
			{	/* 0x8B77: 10 */
				
				if(p[0].sx1 == p[5].sx3)
				{
					fdl->stroke_buf[i].stridmap = 45;
				}
				else{
					fdl->stroke_buf[i].stridmap = 35;
				}
				
			}else
			if( (p[0].lock & FDL_PATH_IsCurve) != 0 && (p[1].lock & FDL_PATH_IsCurve) != 0 && (p[2].lock & FDL_PATH_IsCurve) == 0
				&& (p[3].lock & FDL_PATH_IsCurve) == 0 && (p[4].lock & FDL_PATH_IsCurve) != 0 && (p[5].lock & FDL_PATH_IsCurve) != 0)
			{	/* 0x90E1 */ /* 0x5FAA: 9 */
				fdl->stroke_buf[i].stridmap = 131;		// I think the stroke 30, 127 and 131 are the same type, Alan.
				//DumpDebugString("Identidy Stroke %d %d[0x%x]\n", i, fdl->stroke_buf[i].stridmap, fdl->stroke_buf[i].stridmap);
				p = p+3;
				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
						fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy03 < fdl->stroke_buf[j].rect.bottom)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
						{
							if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
							{
								p2 = fdl->path_buf + p1->relation;
								if(p1->sy1 <= *p->sy01 && *p->sy03 <= p2->sy1 && *p1->sx01 < *p->sx01 && *p->sx03 < *p1->sx03)
								{
									ifind = 1;
									p->lock |= FDL_PATH_MustHide;
									fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
									p->stick_stroke = j;
									p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
									//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
									break;
								}// end if
							}// end for
						}// end for
					}// end if

				}// end for
			}else if( (p[0].lock & FDL_PATH_IsCurve) == 0 && (p[1].lock & FDL_PATH_IsCurve) != 0 && (p[2].lock & FDL_PATH_IsCurve) != 0
					&& (p[3].lock & FDL_PATH_IsCurve) != 0 && (p[4].lock & FDL_PATH_IsCurve) != 0 && (p[5].lock & FDL_PATH_IsCurve) == 0)
			{	/* 0x8B93 */
					fdl->stroke_buf[i].stridmap = 132;
					//DumpDebugString("Identidy Stroke %d %d[0x%x]\n", i, fdl->stroke_buf[i].stridmap, fdl->stroke_buf[i].stridmap);
					ifind = 0;
					for(j=0; j < fdl->stridcnt && ifind == 0; j++)
					{
						if(j == p->strorder) continue;
						if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
							fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy03 < fdl->stroke_buf[j].rect.bottom)
						{
							p1 = fdl->path_buf + fdl->stroke_buf[j].start;
							for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
							{
								if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
								{
									p2 = fdl->path_buf + p1->relation;
									if(p1->sy1 <= *p->sy01 && *p->sy03 <= p2->sy1 && *p1->sx01 < *p->sx01 && *p->sx03 < *p1->sx03)
									{
										ifind = 1;
										p->lock |= FDL_PATH_MustHide;
										fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
										p->stick_stroke = j;
										p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
										//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
										break;
									}// end if
								}// end for
							}// end for
						}// end if

					}// end for
			}else if( (p[0].lock & FDL_PATH_IsCurve) != 0 && (p[1].lock & FDL_PATH_IsCurve) != 0 && (p[2].lock & FDL_PATH_IsCurve) == 0
				&& (p[3].lock & FDL_PATH_IsCurve) != 0 && (p[4].lock & FDL_PATH_IsCurve) != 0 && (p[5].lock & FDL_PATH_IsCurve) == 0)
			{	/* 0x8B58: 8 */
				fdl->stroke_buf[i].stridmap = 25;
				//DumpDebugString("Identidy Stroke %d %d[0x%x]\n", i, fdl->stroke_buf[i].stridmap, fdl->stroke_buf[i].stridmap);

				p = p+2;
				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
						fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy03 < fdl->stroke_buf[j].rect.bottom)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
						{
							if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
							{
								p2 = fdl->path_buf + p1->relation;
								if(p1->sy1 <= *p->sy01 && *p->sy03 <= p2->sy1 && *p1->sx01 < *p->sx01 && *p->sx03 < *p1->sx03)
								{
									ifind = 1;
									p->lock |= FDL_PATH_MustHide;
									fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
									p->stick_stroke = j;
									p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
									//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
									break;
								}// end if
							}// end for
						}// end for
					}// end if

				}// end for
			}// end if
		}
		break;
		case 7:
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			/* 0x6728 */
			if( (p[0].lock & FDL_PATH_IsCurve) != 0 && (p[1].lock & FDL_PATH_IsCurve) != 0 && (p[5].lock & FDL_PATH_IsCurve) != 0 && (p[6].lock & FDL_PATH_IsCurve) != 0
				&& p[3].dir == FDL_PATH_HORZ && p[4].dir == FDL_PATH_VERT && fdl->path_buf[fdl->stroke_buf[i].start+6].subidx == 0)
			{
				fdl->stroke_buf[i].stridmap = 46;
			}// end if
		}
		break;
		case 8:
		{	/* 0x8F15 */
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if( p[0].dir == FDL_PATH_VERT && p[1].dir == FDL_PATH_HORZ  && p[2].dir == FDL_PATH_VERT && p[3].dir == FDL_PATH_HORZ && p[4].dir == FDL_PATH_VERT
				 && p[5].dir == FDL_PATH_HORZ && p[7].dir == FDL_PATH_HORZ)
			{
				fdl->stroke_buf[i].stridmap = 19;
			}else if( (p[0].lock & FDL_PATH_IsCurve) != 0 && (p[1].lock & FDL_PATH_IsCurve) == 0 && (p[2].lock & FDL_PATH_IsCurve) == 0 && (p[3].lock & FDL_PATH_IsCurve) != 0
				&& (p[4].lock & FDL_PATH_IsCurve) == 0 && (p[6].lock & FDL_PATH_IsCurve) != 0 && p[4].subidx == 1)
			{
				fdl->stroke_buf[i].stridmap = 136;
			}else if( (p[0].lock & FDL_PATH_IsCurve) != 0 && (p[1].lock & FDL_PATH_IsCurve) != 0 && (p[2].lock & FDL_PATH_IsCurve) != 0 && (p[3].lock & FDL_PATH_IsCurve) == 0
				&& (p[4].lock & FDL_PATH_IsCurve) == 0 && (p[6].lock & FDL_PATH_IsCurve) != 0 && p[7].subidx == 0)
			{
				fdl->stroke_buf[i].stridmap = 43;
				p1 = p+4;
				for(j=0; j < fdl->stridcnt; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left <= *p1->sx01 && *p1->sx03 <= fdl->stroke_buf[j].rect.right &&
						fdl->stroke_buf[j].rect.top <= *p1->sy01 && *p1->sy03 <= fdl->stroke_buf[j].rect.bottom)
					{
						p1->stick_stroke = j;
						p1->stick_rate = (p1->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);

						p1->lock |= FDL_PATH_MustHide;
						fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
						//							DumpDebugString(" stick %d:%d -> %d\n", i, 1, j);
						break;
					}// end if
				}// end for
			}// end if
		}
		break;
		case 10:
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if( p[0].dir == FDL_PATH_HORZ && p[1].dir == FDL_PATH_NONE && p[5].dir == FDL_PATH_VERT
				&& p[6].dir == FDL_PATH_HORZ && (p[2].lock & FDL_PATH_IsCurve) != 0 && (p[8].lock & FDL_PATH_IsCurve) != 0)
			{	/* 0x8D2: 2 */
				fdl->stroke_buf[i].stridmap = 115;
			}else
			if(p[0].dir == FDL_PATH_VERT && p[1].dir == FDL_PATH_HORZ && p[2].dir == FDL_PATH_VERT && p[3].dir == FDL_PATH_HORZ
				&& p[5].dir == FDL_PATH_HORZ && p[6].dir == FDL_PATH_VERT && p[6].subidx == 1 && p[9].dir == FDL_PATH_VERT)
			{
				fdl->stroke_buf[i].stridmap = 34;
			}else
			if( p[0].dir == FDL_PATH_HORZ && p[1].dir == FDL_PATH_VERT && p[8].dir == FDL_PATH_VERT
				&& p[2].dir == FDL_PATH_NONE && p[6].dir == FDL_PATH_NONE && p[6].subidx == 1)
			{	/* remove stroke: 0x8CDE, 0x3107 0x8173:8 type */
				fdl->stroke_buf[i].status |= FDL_STROKE_CANNOT_BE_A_LINE;
				fdl->stroke_buf[i].stridmap = 4;
			}else
			if( (p[0].lock & FDL_PATH_IsCurve) == 0 && (p[3].lock & FDL_PATH_IsCurve) == 0 && (p[4].lock & FDL_PATH_IsCurve) == 0
				&& p[7].dir == FDL_PATH_HORZ && p[9].dir == FDL_PATH_HORZ && p[6].dir == FDL_PATH_NONE && p[6].subidx == 1)
			{	/* 0x4E92:1 */
				fdl->stroke_buf[i].stridmap = 199;
				p = p+3;
				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left < *p->sx01 && *p->sx03 < fdl->stroke_buf[j].rect.right &&
						fdl->stroke_buf[j].rect.top < *p->sy01 && *p->sy03 < fdl->stroke_buf[j].rect.bottom)
					{
						p1 = fdl->path_buf + fdl->stroke_buf[j].start;
						for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
						{
							if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
							{
								p2 = fdl->path_buf + p1->relation;
								if(p1->sy1 <= *p->sy01 && *p->sy03 <= p2->sy1 && *p1->sx01 < *p->sx01 && *p->sx03 < *p1->sx03)
								{
									ifind = 1;
									p->lock |= FDL_PATH_MustHide;
									fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
									p->stick_stroke = j;
									p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
									//DumpDebugString(" stick%d[%d] %d -> %d\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k);
									break;
								}// end if
							}// end for
						}// end for
					}// end if

				}// end for
			}
		}
		break;
		case 11:
			{
				p = fdl->path_buf + fdl->stroke_buf[i].start;
				if( p[0].dir == FDL_PATH_VERT && p[1].dir == FDL_PATH_HORZ && (p[2].lock & FDL_PATH_IsCurve) == 0 && p[3].dir == FDL_PATH_HORZ
					&& (p[4].lock & FDL_PATH_IsCurve) == 0 && (p[5].lock & FDL_PATH_IsCurve) != 0 && fdl->path_buf[fdl->stroke_buf[i].start+4].subidx == 1)
				{	/* 0x8072 */
					fdl->stroke_buf[i].stridmap = 195;
				}else
				if( p[0].dir == FDL_PATH_VERT && p[3].dir == FDL_PATH_HORZ && (p[1].lock & FDL_PATH_IsCurve) != 0 && p[4].dir == FDL_PATH_VERT
					&& (p[5].lock & FDL_PATH_IsCurve) != 0 && fdl->path_buf[fdl->stroke_buf[i].start+7].subidx == 1)
				{	/* 0x6642:7 */
					fdl->stroke_buf[i].stridmap = 29;
/*					for(j=0; j < fdl->stridcnt && ifind == 0; j++)
					{
						if(j == p->strorder) continue;
						if(fdl->stroke_buf[j].rect.left <= *p->sx01 && *p->sx03 <= fdl->stroke_buf[j].rect.right &&
							*p->sy01 <= fdl->stroke_buf[j].rect.top && fdl->stroke_buf[j].rect.bottom <= *p->sy03)
						{
							p1 = fdl->path_buf + fdl->stroke_buf[j].start;
							for(k=0; k < fdl->stroke_buf[j].len; k++, p1++)
							{
								if(fdl->stroke_buf[j].rect.top != p1->sy1) continue;
								if(p1->dir == FDL_PATH_HORZ && (p1->lock & FDL_PATH_IsRightOrButtom) == 0 && p1->relation >= 0 && fdl->path_buf[p1->relation].dir == FDL_PATH_HORZ)
								{
									p2 = fdl->path_buf + p1->relation;
									if(*p->sy01 <= p1->sy1 && p2->sy1 <= *p->sy03 && *p1->sx01 <= *p->sx01 && *p->sx03 <= *p1->sx03)
									{
										ifind = 1;
										p = p+3;
										p->lock |= FDL_PATH_MustHide;
										fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
										p->stick_stroke = j;
										p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
										DumpDebugString(" stick%d[%d] %d -> %d, %d%%\n", i, fdl->stroke_buf[i].stridmap, j, fdl->stroke_buf[j].start+k, p->stick_rate);
										break;
									}// end if
								}// end for
							}// end for
						}// end if
					}// end for
*/
				}// end if
			}
			break;
		case 12:
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if( p[0].dir == FDL_PATH_VERT && p[1].dir == FDL_PATH_HORZ && p[2].dir == FDL_PATH_VERT && (p[3].lock & FDL_PATH_IsCurve) != 0
				&& p[5].dir == FDL_PATH_HORZ && p[6].dir == FDL_PATH_VERT && p[7].subidx == 0 && p[9].subidx == 1)
			{	/* 0x7FFB:0,  8173:4 */
				fdl->stroke_buf[i].stridmap = 44;	// I think the stroke 44 and 54 are the same type, Alan.
			}else
			if(p[6].subidx == 1 && p[11].subidx == 1 && p[0].dir == FDL_PATH_VERT && p[1].dir == FDL_PATH_HORZ && p[3].dir == FDL_PATH_HORZ
				&& p[4].dir == FDL_PATH_VERT && p[7].dir == FDL_PATH_VERT && p[8].dir == FDL_PATH_HORZ && p[10].dir == FDL_PATH_VERT && p[11].dir == FDL_PATH_HORZ)
			{	/* 0x53E3 */
				fdl->stroke_buf[i].stridmap = 2;
			}else
			if(p[4].subidx == 1 && p[11].subidx == 1 && (p[0].lock & FDL_PATH_IsCurve) != 0 && (p[3].lock & FDL_PATH_IsCurve) != 0 && (p[4].lock & FDL_PATH_IsCurve) != 0
				&& (p[5].lock & FDL_PATH_IsCurve) != 0 && (p[10].lock & FDL_PATH_IsCurve) != 0 && (p[7].lock & FDL_PATH_IsCurve) == 0)
			{	/* 0x5FAA: 0 */
				fdl->stroke_buf[i].stridmap = 151;
/*				p1 = p+4;
				p2 = p+9;
				ifind = 0;
				for(j=0; j < fdl->stridcnt && ifind == 0; j++)
				{
					if(j == p->strorder) continue;
					if(fdl->stroke_buf[j].rect.left < p2->sx3 && p2->sx3 < fdl->stroke_buf[j].rect.right &&
						*p2->sy01 < fdl->stroke_buf[j].rect.top && fdl->stroke_buf[j].rect.bottom < *p2->sy03)
					{
						p = p2;
						p->lock |= FDL_PATH_MustHide;
						fdl->stroke_buf[p->strorder].status |= FDL_STROKE_PartHide;
						p->stick_stroke = j;
						p->stick_rate = (p->sy1 - fdl->stroke_buf[j].rect.bottom)*10000/(fdl->stroke_buf[j].rect.bottom - fdl->stroke_buf[j].rect.top);
						//DumpDebugString(" stick%d[%d] %d\n", i, fdl->stroke_buf[i].stridmap, j);
						break;
					}// end if
				}// end for
*/
			}else
			if( p[0].dir == FDL_PATH_HORZ
				&&p[1].dir == FDL_PATH_VERT
				&& p[2].dir == FDL_PATH_NONE
				&& p[3].dir == FDL_PATH_HORZ
				&& p[4].dir == FDL_PATH_VERT
				&& p[7].dir == FDL_PATH_VERT && p[6].subidx == 1)
			{	/* 0x8276: 12 */
				fdl->stroke_buf[i].stridmap = 30;
			}else
			if( p[0].dir == FDL_PATH_VERT 
				&&p[1].dir == FDL_PATH_HORZ
				&& p[2].dir == FDL_PATH_NONE
				&& p[3].dir == FDL_PATH_NONE
				&& p[4].dir == FDL_PATH_NONE && p[8].subidx == 1)
			{	/* 0x53E6 */
				fdl->stroke_buf[i].status |= FDL_STROKE_LEFT_LEAN ;
				fdl->stroke_buf[i].status |= FDL_STROKE_EN_REF_POINT ;
				//fdl->stroke_buf[i].ref_x = &(p[8].sx1);	// 20110804: Jacky marked for memory
				//fdl->stroke_buf[i].ref_y = &(p[8].sy1);
			}else
			if( p[0].dir == FDL_PATH_NONE 
				&&p[1].dir == FDL_PATH_HORZ
				&& p[2].dir == FDL_PATH_NONE
				&& p[3].dir == FDL_PATH_NONE
				&& p[4].dir == FDL_PATH_VERT && p[8].subidx == 1)
			{	/* 0x6613 */
				fdl->stroke_buf[i].status |= FDL_STROKE_LEFT_LEAN ;
				fdl->stroke_buf[i].status |= FDL_STROKE_EN_REF_POINT ;
				//fdl->stroke_buf[i].ref_x = &(p[8].sx1);	// 20110804: Jacky marked for memory
				//fdl->stroke_buf[i].ref_y = &(p[8].sy1);
				//p[4].lock |= FDL_PATH_IsHide;
			}
		}
		break;
		case 14: /* 0x78BC:12 */
			{
				p = fdl->path_buf + fdl->stroke_buf[i].start;
				if(p[9].subidx == 0 && p[10].subidx == 1 && p[13].subidx == 1 && p[0].dir == FDL_PATH_VERT && p[1].dir == FDL_PATH_HORZ
					&& p[6].dir == FDL_PATH_VERT && p[7].dir == FDL_PATH_HORZ && (p[8].lock & FDL_PATH_IsCurve) != 0)
				{
					fdl->stroke_buf[i].stridmap = 65;
					//DumpDebugString("Identidy Stroke %d[0x%x]\n", fdl->stroke_buf[i].stridmap, fdl->stroke_buf[i].stridmap);
				}// end if
			}
			break;
		case 16:
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if(p[5].subidx == 0 && p[6].subidx == 1 && p[9].subidx == 1 && p[12].subidx == 2 && p[2].dir == FDL_PATH_NONE && p[11].dir == FDL_PATH_NONE)
			{	/* 0x5DFE */
				fdl->stroke_buf[i].stridmap = 18;
			}else
			if(p[7].subidx == 0 && p[8].subidx == 1 && p[15].subidx == 1 && p[0].dir == FDL_PATH_VERT && p[3].dir == FDL_PATH_HORZ && p[4].dir == FDL_PATH_VERT)
			{	/* 0x8AAD: 11 */
				fdl->stroke_buf[i].stridmap = 74;
			}// end if
		}
		break;
		case 17:
		{
			p = fdl->path_buf + fdl->stroke_buf[i].start;
			if(p[8].subidx == 0 && p[9].subidx == 1 && p[16].subidx == 1 && p[0].dir == FDL_PATH_VERT && p[5].dir == FDL_PATH_VERT
				 && (p[11].lock & FDL_PATH_IsCurve) != 0 && (p[16].lock & FDL_PATH_IsCurve) != 0)
			{	/* 0x5BF5 */
				fdl->stroke_buf[i].stridmap = 128;
			}// end if
		}
		break;
		case 19:
			{
				p = fdl->path_buf + fdl->stroke_buf[i].start;
				if(p[8].subidx == 0 && p[9].subidx == 1 && p[14].subidx == 1 && p[16].subidx == 2 && p[2].dir == FDL_PATH_VERT && p[15].dir == FDL_PATH_HORZ)
				{	/* 0x9001: 7*/
					fdl->stroke_buf[i].stridmap = 100;
					//DumpDebugString("Identidy Stroke %d[0x%x]\n", fdl->stroke_buf[i].stridmap, fdl->stroke_buf[i].stridmap);
				}// end if
			}
			break;
		default:
			break;
		}// end switch

		//if(fdl->stroke_buf[i].stridmap >= 0) DumpDebugString("Identidy Stroke %d: %d[0x%x]\n", i, fdl->stroke_buf[i].stridmap, fdl->stroke_buf[i].stridmap);
	}// end for

}// end IdentifyStroke

static DT_void Do_StrokeRemoveAlignPackAdjust(pFdlRasterData fdl)
{
	DT32_int i;
	DT32_int group, n;

		if(fdl->groupinfo.fontid == 0x0000)
		{
			for(i=0; i < fdl->stridcnt; i++)
			{
				GetStrokeLines(fdl, i);
				GetStrokeLineType(fdl, i);
			}// end for
			// =================  ===================
			//Do_MeasureStrokeWeightX(fdl);
			Do_AdjustStrokeY(fdl);
#if 0
			// =================  ===================
			for(i=0; i < fdl->stridcnt; i++)
			{
				GetStrokeVLines(fdl, i);
				GetStrokeVLineType(fdl, i);
			}// end for
			
			//Do_MeasureStrokeWeightY(fdl);
			Do_AdjustStrokeX(fdl);
#endif
			group = 1 << (8-MAIN_GROUP_BIT);
		}else{
			// =================  ===================
			for(i=0; i < fdl->stridcnt; i++)
			{
				GetStrokeLines(fdl, i);
				GetStrokeLineType(fdl, i);
			}// end for

			//Do_MeasureStrokeWeightX(fdl);
			for(group=0; group < ((fdl->groupinfo.groupnum) << (8-MAIN_GROUP_BIT)); group+=(1<<(8-MAIN_GROUP_BIT)))
			{
				n=0;
				fdl->group_wrknum = fdl->groupinfo.groupnum;
				for(i=0; i < fdl->stridcnt; i++)
				{
					if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[i]) == group)
					{
						n = 1;
						fdl->group_wrk[i] = fdl->groupinfo.grouplist[i];		// Note: the group_wrk[] store group id without shift right.
					}else fdl->group_wrk[i] = 0xFF;
				}// end for
	
				if(n == 0) break;
	
				Do_AdjustStrokeY(fdl);
			}// end for
		
#if 0
			// =================  ===================
			for(i=0; i < fdl->stridcnt; i++)
			{
				GetStrokeVLines(fdl, i);
				GetStrokeVLineType(fdl, i);
			}// end for

			//Do_MeasureStrokeWeightY(fdl);
			for(group=0; group < ((fdl->groupinfo.groupnum) << (8-MAIN_GROUP_BIT)); group+=(1<<(8-MAIN_GROUP_BIT)))
			{
				n=0;
				fdl->group_wrknum = fdl->groupinfo.groupnum;
				for(i=0; i < fdl->stridcnt; i++)
				{
					if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[i]) == group)
					{
						n = 1;
						fdl->group_wrk[i] = fdl->groupinfo.grouplist[i];		// Note: the group_wrk[] store group id without shift right.
						//DumpDebugString("main group %d, %d\n", group>>5, FDL_SUB_GROUP(fdl->groupinfo.grouplist[i]));
					}else fdl->group_wrk[i] = 0xFF;
				}// end for
				if(n == 0) break;
				
				Do_AdjustStrokeX(fdl);	//TODO: Do_AdjustStrokeY() Do_RemoveStroke_When_Adjust()
			}// end for
#endif
		}// end if
}

static DT_void Do_AdvHinting(pFdlRasterData fdl)
{
	DT32_int i;
	DT32_int w, w0, middle, move;
	TRect rect[6];
	PATH_UNIT *p = fdl->path_buf;
	DT32_int group, n;

	for(i=0; i < fdl->path_num; i++)
	{
//		fdl->path_buf[i].sx1a = fdl->path_buf[i].sx1;
//		fdl->path_buf[i].sx3a = fdl->path_buf[i].sx3;

		fdl->path_buf[i].sy1a = fdl->path_buf[i].sy1;
		fdl->path_buf[i].sy3a = fdl->path_buf[i].sy3;
	}// end for

	DT_memcpy(fdl->group_fin, fdl->groupinfo.grouplist, fdl->stridcnt * sizeof(fdl->groupinfo.grouplist[0]));
	SVG_RETURN_STEP(120)

	Do_FindLPath(fdl, FDL_PATH_HORZ);
	Do_FindLPath(fdl, FDL_PATH_VERT);
//	Do_FindInterPath(fdl);


#ifdef ENABLE_ADV_HINTING

#if 1
	for(i=0; i < fdl->stridcnt; i++)
		GetStrokeRect(fdl, i, &(fdl->stroke_buf[i].rect));
	GetGroupRect(fdl);
	GetMainGroupRect(fdl);

	IdentifyStroke(fdl);

	for(i=0; i < fdl->stridcnt; i++)				// For fixed 0x5E36
	{
		if(fdl->stroke_buf[i].stridmap == 18)
		{
			PATH_UNIT p1, *p = fdl->path_buf+fdl->stroke_buf[i].start;
			DT_memcpy(&p1, p + 13, sizeof(PATH_UNIT));
			DT_memcpy(p + 13, p + 14, sizeof(PATH_UNIT));
			DT_memcpy(p + 14, &p1, sizeof(PATH_UNIT));
		}// end if
	}// end for

	// ================= Enable  FDL_PATH_IsJointflags ===================
	Do_FindJointPath(fdl);

/*	if(fdl->groupinfo.fontid == 0x0000)
	{
		fdl->group_wrknum = 1;
		DT_memset(fdl->group_wrk, 0, fdl->stridcnt*sizeof(fdl->group_wrk[0]));

		Do_AutoGroup(fdl);
		
	}*/

	// ================== Stroke Remove & AlignPck & Adjust ===============
	Do_KeepAllPathStroke(fdl);	//Keep all paths & strokes
	//Do_GroupXAlignType(fdl);	//Is group should be mirror in X direction (y-axis)?
	Do_StrokeRemoveAlignPackAdjust(fdl);
SVG_RETURN_STEP(206)

#ifdef FDL_ONLY_REMOVE_STROKE_NOHINTING
	return;
#endif // FDL_ONLY_REMOVE_STROKE_NOHINTING

// ==============================
#if 1
fdl->groupinfo.fontid = 0x0000;
fdl->group_wrknum = 1;
DT_memset(fdl->group_wrk, 0, fdl->stridcnt*sizeof(fdl->group_wrk[0]));
Do_AutoGroup(fdl);
#endif
// ==============================

#ifdef HINTING_SIZE
	if(fdl->fontsizey > HINTING_SIZE)
	{
		return;
	}
#endif
	// ========================================= Hinting starts =================================
	// ================= Horizontal Alignment ===================
	if(fdl->groupinfo.fontid == 0x0000)
	{
		//fdl->group_wrknum = 1;
		DT_memset(fdl->group_wrk, 0, fdl->stridcnt*sizeof(fdl->group_wrk[0]));

		for(i=0; i < fdl->stridcnt; i++)
		{
			GetStrokeLines(fdl, i);
			GetStrokeLineType(fdl, i);
		}// end for

		if(Do_MeasureStrokeWeightX(fdl) > 0)
		{
//			Do_OutlineAlignSubH(fdl, 1);
//			Do_OutlineAlignSubV(fdl);
	//		return;
		}// end if

		if(fdl->groupinfo.fontid == 0x0000)
		{
			Do_OutlineAlignY(fdl);
			group = 1 << (8-MAIN_GROUP_BIT);
		}else
		{
			for(group=0; group < ((fdl->groupinfo.groupnum) << (8-MAIN_GROUP_BIT)); group+=(1<<(8-MAIN_GROUP_BIT)))
			{
				n=0;
				fdl->group_wrknum = fdl->groupinfo.groupnum;
				for(i=0; i < fdl->stridcnt; i++)
				{
					if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[i]) == group)
					{
						n = 1;
						fdl->group_wrk[i] = fdl->groupinfo.grouplist[i];		// Note: the group_wrk[] store group id without shift right.
					}else fdl->group_wrk[i] = 0xFF;
				}// end for
	
				if(n == 0) break;
	
				Do_OutlineAlignY(fdl);
			}// end for
		}// end if
	}else
	{
		for(i=0; i < fdl->stridcnt; i++)
		{
			GetStrokeLines(fdl, i);
			GetStrokeLineType(fdl, i);
		}// end for

		if(Do_MeasureStrokeWeightX(fdl) > 0)
		{
//			Do_OutlineAlignSubH(fdl);
	//		return;
		}// end if

		for(group=0; group < ((fdl->groupinfo.groupnum) << (8-MAIN_GROUP_BIT)); group+=(1<<(8-MAIN_GROUP_BIT)))
		{
			n=0;
			fdl->group_wrknum = fdl->groupinfo.groupnum;
			for(i=0; i < fdl->stridcnt; i++)
			{
				if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[i]) == group)
				{
					n = 1;
					fdl->group_wrk[i] = fdl->groupinfo.grouplist[i];		// Note: the group_wrk[] store group id without shift right.
				}else fdl->group_wrk[i] = 0xFF;
			}// end for

			if(n == 0) break;

			Do_OutlineAlignY(fdl);
		}// end for

	}// end if
SVG_RETURN_STEP(220)

//Do_FindLPath(fdl, FDL_PATH_HORZ);
//Do_FindLPath(fdl, FDL_PATH_VERT);

	Do_ReadjustStrokeSpace(fdl, (group >> (8-MAIN_GROUP_BIT)) );

//return;//
//	if(fdl->stroke_weightX % 10 == 0)
//		Do_OutlineAlignSubH(fdl);
//return;//

#ifdef ENABLE_STICK_Y
	CheckHorStickRelationPath(fdl);
#endif

#if 0	// Off Vertical Alignment
SVG_RETURN_STEP(260)
	Do_FindHidePath(fdl);
//	Do_FindInterPath(fdl);

// ================= Vertical Alignment ===================
	if(fdl->groupinfo.fontid == 0x0000 || fdl->groupinfo.groupnum <= 1)
	{
		//fdl->group_wrknum = 1;
		DT_memset(fdl->group_wrk, 0, fdl->stridcnt*sizeof(fdl->group_wrk[0]));
		for(i=0; i < fdl->stridcnt; i++)
		{
			GetStrokeVLines(fdl, i);
			GetStrokeVLineType(fdl, i);
		}// end for

		if(Do_MeasureStrokeWeightY(fdl) > 0)
			return;
		Do_OutlineAlignX(fdl);

		//for(i=0; i< fdl->path_num; i++, p++)
		/*for(i=0; i< fdl->path_buf_pt_num; i++, p++)
		{
			p = fdl->path_buf + fdl->path_buf_pt[i];
			if( (p->idx_interline >=0) && (p->relation>=0) && (p->dir == FDL_PATH_VERT))
			{
				Do_AvgInterXPath(fdl, fdl->path_buf_pt[i]);
			}
		}
		*/

SVG_RETURN_STEP(599)
	}else
	{
		for(i=0; i < fdl->stridcnt; i++)
		{
			GetStrokeVLines(fdl, i);
			GetStrokeVLineType(fdl, i);
		}// end for

		if(Do_MeasureStrokeWeightY(fdl) > 0)
			return;

		for(group=0; group < ((fdl->groupinfo.groupnum) << (8-MAIN_GROUP_BIT)); group+=(1<<(8-MAIN_GROUP_BIT)))
		{
			n=0;
			fdl->group_wrknum = fdl->groupinfo.groupnum;
			for(i=0; i < fdl->stridcnt; i++)
			{
				if(FDL_MAIN_GROUP(fdl->groupinfo.grouplist[i]) == group)
				{
					n = 1;
					fdl->group_wrk[i] = fdl->groupinfo.grouplist[i];		// Note: the group_wrk[] store group id without shift right.
					//DumpDebugString("main group %d, %d\n", group>>5, FDL_SUB_GROUP(fdl->groupinfo.grouplist[i]));
				}else fdl->group_wrk[i] = 0xFF;
			}// end for
			if(n == 0) break;
			
		Do_OutlineAlignX(fdl);
SVG_RETURN_STEP(520)
		}// end for
	}// end if
//return;//
SVG_RETURN_STEP(600)
	if(fdl->stroke_weightY % 10 == 0)
		Do_OutlineAlignSubV(fdl);
SVG_RETURN_STEP(700)

#endif // Vertical Alignment

#endif

#if 1		// Alan test.
	// ============ align center by main group ============
	middle = ((1 << fdl->shift)-1)/2;
	GetAllStrokeRectAfterHint(fdl);
	GetMainGroupRectAfterHint(fdl, rect, SIZEOF_ARRAY(rect));

	for(i=0; fdl->main_group_rect[i].right < 0x000FFFFF && i < SIZEOF_ARRAY(fdl->main_group_rect); i++)
//	for(i=0; fdl->main_group_rect[i].right < 0x000FFFFF; i++)
	{
		w0 = fdl->main_group_rect[i].top + (fdl->main_group_rect[i].bottom - fdl->main_group_rect[i].top)/2;
		w = rect[i].top + (rect[i].bottom - rect[i].top)/2;
		if(w != w0)
		{
			if(w0 > w)
			{
				move = w0 - w + middle;
				move = (move >> fdl->shift) << fdl->shift;
			}else
			{
				move = w - w0 + middle;
				move = (move >> fdl->shift) << fdl->shift;
				move = 0 - move;
			}// end if
			Do_MoveFontMainGroupY(fdl, i, move);
		}// end if

		w0 = fdl->main_group_rect[i].left + (fdl->main_group_rect[i].right - fdl->main_group_rect[i].left)/2;
		w = rect[i].left + (rect[i].right - rect[i].left)/2;
		if(w != w0)
		{
			if(w0 > w)
			{
				move = w0 - w + middle;
				move = (move >> fdl->shift) << fdl->shift;
			}else
			{
				move = w - w0 + middle;
				move = (move >> fdl->shift) << fdl->shift;
				move = 0 - move;
			}// end if
			Do_MoveFontMainGroupX(fdl, i, move);
		}// end if

	}// end for
#endif
	// =============== need to improve performance, for case 0x66C7 size=16, weight=2 ====================
#if 1
	GetFontRect(fdl, rect);
	if(rect->bottom > (fdl->fontsizey << fdl->shift) && rect->top >= (1 << fdl->shift))
	{
		DT32_int offset = rect->bottom - (fdl->fontsizey << fdl->shift);
		if(offset <= rect->top)
			move = ((offset + (1 << fdl->shift)-1) >> fdl->shift) << fdl->shift;
		else move = ((rect->top + (1 << fdl->shift)-1) >> fdl->shift) << fdl->shift;
		Do_MoveFontY(fdl, 0-move);
	}// end if
#endif

#endif // ENABLE_ADV_HINTING

}// end Do_AdvHinting

static DT32_int Do_SCurve2(pFdlRasterData fdl, DT32_int subidx)
{
	DT32_int i;
	PATH_UNIT *p;
	DT32_int curidex;

	if(subidx < 0)
	{
		p = fdl->path_buf;
		for(i=0; i < fdl->path_num; i++, p++)
		{
			fdl->isCurve = p->lock & FDL_PATH_IsCurve;
			fdl->isLeft = p->lock & FDL_PATH_IsLeft;
			fdl->sx1 = p->sy1;
			fdl->sy1 = p->sx1;

			fdl->sx2 = p->sy2;
			fdl->sy2 = p->sx2;

			fdl->sx3 = p->sy3;
			fdl->sy3 = p->sx3;

//DumpDebugString("  Point%d %s (%d, %d),(%d, %d) => (%d, %d),(%d, %d)\n", i, (p->lock & FDL_PATH_IsRightOrButtom) ? "E": "S" ,p->sx1, p->sy1, p->sx3, p->sy3, (p->sx1 >> fdl->Frac2),  (p->sy1 >> fdl->Frac2),  (p->sx3 >> fdl->Frac2),  (p->sy3 >> fdl->Frac2));
			SCurve2(fdl);
		}// end for
	} else
	{
		p = fdl->path_buf + subidx;

		curidex = p->subidx;
		for(i=subidx; i < fdl->path_num; i++, p++)
		{
			if(curidex != p->subidx)
				break;

			fdl->isCurve = p->lock & FDL_PATH_IsCurve;
			fdl->isLeft = p->lock & FDL_PATH_IsLeft;
			fdl->sx1 = p->sy1;
			fdl->sy1 = p->sx1;

			fdl->sx2 = p->sy2;
			fdl->sy2 = p->sx2;

			fdl->sx3 = p->sy3;
			fdl->sy3 = p->sx3;

//DumpDebugString("  Point%d %s (%d, %d),(%d, %d) => (%d, %d),(%d, %d)\n", i, (p->lock & FDL_PATH_IsRightOrButtom) ? "E": "S" ,p->sx1, p->sy1, p->sx3, p->sy3, (p->sx1 >> fdl->Frac2),  (p->sy1 >> fdl->Frac2),  (p->sx3 >> fdl->Frac2),  (p->sy3 >> fdl->Frac2));
			SCurve2(fdl);
		}// end for
	}// end if

	return(i);
}// end Do_SCurve2

static DT32_int Do_SCurve3(pFdlRasterData fdl, DT32_int strorder, DT32_int subidx)
{
	DT32_int i;
	PATH_UNIT *p;
	DT32_int curidex;

#ifdef ENABLE_ADV_HINTING
	curidex = fdl->path_buf[fdl->path_buf_pt[subidx]].subidx;
	for(i=subidx; i < fdl->path_buf_pt_num; i++)
	{
		p = fdl->path_buf + fdl->path_buf_pt[i];
		if(curidex != p->subidx || p->strorder != strorder)
			break;

		fdl->isCurve = p->lock & FDL_PATH_IsCurve;
		fdl->isLeft = p->lock & FDL_PATH_IsLeft;
		fdl->sx1 = p->sy1;
		fdl->sy1 = p->sx1;

		fdl->sx2 = p->sy2;
		fdl->sy2 = p->sx2;

		fdl->sx3 = p->sy3;
		fdl->sy3 = p->sx3;

		SCurve2(fdl);
	}// end for
#else
	p = fdl->path_buf + subidx;

	curidex = p->subidx;
	for(i=subidx; i < fdl->path_num; i++, p++)
	{
		if(curidex != p->subidx || p->strorder != strorder)
			break;

		//fdl->lock = p->lock;
		fdl->isLeft = p->lock & FDL_PATH_IsLeft;
		fdl->sx1 = p->sy1;
		fdl->sy1 = p->sx1;

		fdl->sx2 = p->sy2;
		fdl->sy2 = p->sx2;

		fdl->sx3 = p->sy3;
		fdl->sy3 = p->sx3;

//DumpDebugString("  Point%d %s (%d, %d),(%d, %d) => (%d, %d),(%d, %d)\n", i, (p->lock & FDL_PATH_IsRightOrButtom) ? "E": "S" ,p->sx1, p->sy1, p->sx3, p->sy3, (p->sx1 >> fdl->Frac2),  (p->sy1 >> fdl->Frac2),  (p->sx3 >> fdl->Frac2),  (p->sy3 >> fdl->Frac2));
		SCurve2(fdl);
	}// end for
#endif

	return(i);
}// end Do_SCurve3
#endif	// FDL_OUTLINE_MODE

static DT_void SCurve2(pFdlRasterData fdl)
{
	DT32_int stacklen, sp = 0;		/* init stack pointer */
	TPoint cp0, cp1, cp2, tp0, tp1, tp2, mp;
	DT32_long dx, dy;

	if(fdl->isLeft)
		fdl->AddPt2ScanPt = AddPt2ScanL;
	else fdl->AddPt2ScanPt = AddPt2ScanR;
//mytestcount=0;

#if !defined DT_REAL_STRAIGHT_LINE_FDL_USED
	/* 2011-08-31: Start *//* for symbol fonts that had no lines but only curves. */
	if (fdl->isCurve)
	{
		// 20111005: Jacky modified this for Gray256
		if((fdl->sx2 == fdl->sx3) && (fdl->sy2 == fdl->sy3)){
			fdl->isCurve = 0;
		}
		else if((fdl->sx2 == fdl->sx1) && (fdl->sy2 == fdl->sy1)){
			if(fdl->grade == DCW_MODE_GRAY16)
				fdl->isCurve = 0;
			else
				fdl->isCurve = 1;
		}
		else{
			fdl->isCurve = 1;
		}
	}
	else
		fdl->isCurve = 0;
	/* 2011-08-31: End */
#endif

	if(fdl->isCurve)
	{
		// Add head/tail point
		AddPt2Scan2(fdl, fdl->sy1 >> fdl->Frac2, fdl->sx1 >> fdl->Frac2);
		AddPt2Scan2(fdl, fdl->sy3 >> fdl->Frac2, fdl->sx3 >> fdl->Frac2);

		//DumpDebugString("    SCurve2 %s (%d, %d), (%d, %d), (%d)				===> %d, %d\n", (fdl->isLeft ? "L": "R"), fdl->sx1 >>  fdl->Frac2, fdl->sy1 >> fdl->Frac2, fdl->sx2 >>  fdl->Frac2, fdl->sy2 >>  fdl->Frac2, fdl->sx3 >>  fdl->Frac2, fdl->sy3 >> fdl->Frac2, fdl->RasterCnt);
		cp0.x = fdl->sy1;
		cp0.y = fdl->sx1;
		cp1.x = fdl->sy2;
		cp1.y = fdl->sx2;
		cp2.x = fdl->sy3;
		cp2.y = fdl->sx3;

		mp = cp1;       tp2 = cp2;
		tp1.x = (tp2.x + cp1.x) / 2;            tp1.y = (tp2.y + cp1.y) / 2;
		cp1.x = (cp1.x + cp0.x) / 2;            cp1.y = (cp1.y + cp0.y) / 2;
		tp0.x = (cp1.x + tp1.x) / 2;            tp0.y = (cp1.y + tp1.y) / 2;
		dx = mp.x - tp0.x;
		dy = mp.y - tp0.y;
		stacklen = sizeof(fdl->NsStack) / sizeof(fdl->NsStack[0]);
		if(dx >= 0)
		{
			if(dy >= 0)
			{
				while(sp < stacklen/*FDL_MAX_STACK*/)
				{
					if(dx < fdl->NsMaxSeg && dy < fdl->NsMaxSeg)
					{
//						deLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
						DoDeLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
						if(sp > 0)
						{
							sp--, cp0 = fdl->NsStack[sp];
							sp--, cp1 = fdl->NsStack[sp];
							sp--, cp2 = fdl->NsStack[sp];
						} else break;
					} else
					{
						fdl->NsStack[sp] = tp2, sp++;
						fdl->NsStack[sp] = tp1, sp++;
						fdl->NsStack[sp] = tp0, sp++;
						cp2 = tp0;
					}// end if

					mp = cp1;       tp2 = cp2;
					tp1.x = (tp2.x + cp1.x) / 2;            tp1.y = (tp2.y + cp1.y) / 2;
					cp1.x = (cp1.x + cp0.x) / 2;            cp1.y = (cp1.y + cp0.y) / 2;
					tp0.x = (cp1.x + tp1.x) / 2;            tp0.y = (cp1.y + tp1.y) / 2;

					dx = mp.x - tp0.x;
					dy = mp.y - tp0.y;
				}// end while
			} else
			{
				dy = -dy;
				while(sp < stacklen/*FDL_MAX_STACK*/)
				{
					if(dx < fdl->NsMaxSeg && dy < fdl->NsMaxSeg)
					{
//						deLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
						DoDeLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
						if(sp > 0)
						{
							sp--, cp0 = fdl->NsStack[sp];
							sp--, cp1 = fdl->NsStack[sp];
							sp--, cp2 = fdl->NsStack[sp];
						} else break;
					} else
					{
						fdl->NsStack[sp] = tp2, sp++;
						fdl->NsStack[sp] = tp1, sp++;
						fdl->NsStack[sp] = tp0, sp++;
						cp2 = tp0;
					}// end if

					mp = cp1;       tp2 = cp2;
					tp1.x = (tp2.x + cp1.x) / 2;            tp1.y = (tp2.y + cp1.y) / 2;
					cp1.x = (cp1.x + cp0.x) / 2;            cp1.y = (cp1.y + cp0.y) / 2;
					tp0.x = (cp1.x + tp1.x) / 2;            tp0.y = (cp1.y + tp1.y) / 2;

					dx = mp.x - tp0.x;
					dy = tp0.y - mp.y;
				}// end while
			}// end if
		} else
		{
			dx = -dx;
			if(dy >= 0)
			{
				while(sp < stacklen/*FDL_MAX_STACK*/)
				{
					if(dx < fdl->NsMaxSeg && dy < fdl->NsMaxSeg)
					{
//						deLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
						DoDeLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
						if(sp > 0)
						{
							sp--, cp0 = fdl->NsStack[sp];
							sp--, cp1 = fdl->NsStack[sp];
							sp--, cp2 = fdl->NsStack[sp];
						} else break;
					} else
					{
						fdl->NsStack[sp] = tp2, sp++;
						fdl->NsStack[sp] = tp1, sp++;
						fdl->NsStack[sp] = tp0, sp++;
						cp2 = tp0;
					}// end if

					mp = cp1;       tp2 = cp2;
					tp1.x = (tp2.x + cp1.x) / 2;            tp1.y = (tp2.y + cp1.y) / 2;
					cp1.x = (cp1.x + cp0.x) / 2;            cp1.y = (cp1.y + cp0.y) / 2;
					tp0.x = (cp1.x + tp1.x) / 2;            tp0.y = (cp1.y + tp1.y) / 2;

					dx = tp0.x - mp.x;
					dy = mp.y - tp0.y;
				}// end while
			} else
			{
				dy = -dy;
				while(sp < stacklen/*FDL_MAX_STACK*/)
				{
					if(dx < fdl->NsMaxSeg && dy < fdl->NsMaxSeg)
					{
//						deLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
						DoDeLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
						if(sp > 0)
						{
							sp--, cp0 = fdl->NsStack[sp];
							sp--, cp1 = fdl->NsStack[sp];
							sp--, cp2 = fdl->NsStack[sp];
						} else break;
					} else
					{
						fdl->NsStack[sp] = tp2, sp++;
						fdl->NsStack[sp] = tp1, sp++;
						fdl->NsStack[sp] = tp0, sp++;
						cp2 = tp0;
					}// end if

					mp = cp1;       tp2 = cp2;
					tp1.x = (tp2.x + cp1.x) / 2;            tp1.y = (tp2.y + cp1.y) / 2;
					cp1.x = (cp1.x + cp0.x) / 2;            cp1.y = (cp1.y + cp0.y) / 2;
					tp0.x = (cp1.x + tp1.x) / 2;            tp0.y = (cp1.y + tp1.y) / 2;

					dx = tp0.x - mp.x;
					dy = tp0.y - mp.y;
				}// end while
			}// end if
		}// end if

/*		while(sp < FDL_MAX_STACK)
		{
			mp = cp1;		tp2 = cp2;
			tp1.x = (tp2.x + cp1.x) / 2;			tp1.y = (tp2.y + cp1.y) / 2;
			cp1.x = (cp1.x + cp0.x) / 2;			cp1.y = (cp1.y + cp0.y) / 2;
			tp0.x = (cp1.x + tp1.x) / 2;			tp0.y = (cp1.y + tp1.y) / 2;

			dx = mp.x - tp0.x;
			dy = mp.y - tp0.y;
			if(dx < 0)			dx = -dx;
			if(dy < 0)			dy = -dy;

			if(dx < fdl->NsMaxSeg && dy < fdl->NsMaxSeg)
			{
				deLine(fdl, cp0.x, cp0.y, cp2.x, cp2.y);
				if(sp > 0)
				{
					sp--, cp0 = fdl->NsStack[sp];
					sp--, cp1 = fdl->NsStack[sp];
					sp--, cp2 = fdl->NsStack[sp];
				}else break;
			}else
			{
				fdl->NsStack[sp] = tp2, sp++;
				fdl->NsStack[sp] = tp1, sp++;
				fdl->NsStack[sp] = tp0, sp++;
				cp2 = tp0;
			}// end if
		}// end while		*/
//DumpDebugString("SCurve2 (%d, %d), (%d, %d), (%d, %d)						===> %d\n", fdl->sx1, fdl->sy1, fdl->sx2, fdl->sy2, fdl->sx3, fdl->sy3, fdl->RasterCnt);
	} else
	{
		// Add head/tail point
		//DumpDebugString("    Line %s (%d, %d), (%d, %d) => (%d, %d), (%d, %d)\n", (fdl->isLeft ? "L": "R"), fdl->sx1, fdl->sy1, fdl->sx3, fdl->sy3,  fdl->sx1>> fdl->Frac2, fdl->sy1>> fdl->Frac2, fdl->sx3>> fdl->Frac2, fdl->sy3>> fdl->Frac2);
		AddPt2Scan2(fdl, fdl->sy1 >> fdl->Frac2, fdl->sx1 >> fdl->Frac2);
		AddPt2Scan2(fdl, fdl->sy3 >> fdl->Frac2, fdl->sx3 >> fdl->Frac2);

		deLine(fdl, fdl->sy1, fdl->sx1, fdl->sy3, fdl->sx3);
	}// end if
}
/*---------------------------------------------------------------------------*/
DT_void NewScanInit(pFdlRasterData fdl)
{
	DT32_int i,cnt;
	DT32_long value;
	DT32_long *lp2, *rp2;
	lp2 = (DT32_long*)fdl->Left_Ptr;
	rp2 = (DT32_long*)fdl->Right_Ptr;
	value = (fdl->xsize << 16) | fdl->xsize;
	cnt = fdl->ysize + fdl->yorg + fdl->w_edge*2 + fdl->italic;	//Jacky_20110411


	for(i=0; i < /*fdl->ysize/2*/cnt/2; i++)		// Maybe have problem in RISC, Alan.
	{
		*lp2++ = value;
		*rp2++ = 0;
	}// end for

	//if(fdl->ysize & 2)	//Marked_20101123: for some bug of some monochrome characters.
	{
		DT32_int offset = cnt-1;	//fdl->ysize-1;
		fdl->Left_Ptr[offset] = (DT16_short)fdl->xsize;
		fdl->Right_Ptr[offset] = 0;
	}// end if

	fdl->NsTop = fdl->ysize;
	fdl->NsDownL = 0;
	fdl->NsDownR = 0;
}

/*---------------------------------------------------------------------------*/
DT32_int FDL_GetFont(DT_void *vwrk, pFdlRasterData fdl, DT32_int mode, DT32_int strid)
{
	DT16_WORD  status;
	DT32_int   i;
	DT32_int   ret = DCW_SUCCESS, size=0;

	fdl->Mode = mode;
	// ============================================================================================
	//DumpDebugString("Start strid %d (0x%X) ===================================\n", strid, strid);

//	fdl->group_wrknum = fdl->groupinfo.groupnum;
//	DT_memcpy(fdl->group_wrk, fdl->groupinfo.grouplist, fdl->groupinfo.strnum);

	if(fdl->hint > FDL_NO_HINT)
	{
		fdl->zoom = 8;
		fdl->xsize2 = fdl->xsize << 3;	// fdl->xsize * fdl->zoom;
		fdl->ysize2 = fdl->ysize << 3;	// fdl->ysize * fdl->zoom;
	} else
	{
		fdl->zoom = 1;
		fdl->xsize2 = fdl->xsize;
		fdl->ysize2 = fdl->ysize;
	}

	if(fdl->xsize2>32767 || fdl->ysize2>32767)	// avoid overflow of DT16_short
	{
		fdl->zoom = 1;
		fdl->xsize2 = fdl->xsize;
		fdl->ysize2 = fdl->ysize;
	}

#ifdef FDL_OUTLINE_MODE
	fdl->gfdx = 0;
	fdl->gfdy = 0;
	if(fdl->grade == DCW_MODE_GRAY16)
	{
		size = fdl->xsize >> 2;
		fdl->hint_move_offsetX = move_offsetX016;
		fdl->hint_move_offsetY = move_offsetY016;
		fdl->recycle = 4-1;
		fdl->recycleshift = 2;

		fdl->fontsizex = size;
		fdl->fontsizey = fdl->ysize >> 2;
	} else
	{
		size = fdl->xsize >> 4;
		fdl->hint_move_offsetX = move_offsetX256;
		fdl->hint_move_offsetY = move_offsetY256;
		fdl->recycle = 16-1;
		fdl->recycleshift = 4;

		fdl->fontsizex = size;
		fdl->fontsizey = fdl->ysize >> 4;
	}// end if

	fdl->strid = strid;
	fdl->stroke_buf[ fdl->stridcnt ].stridmap = (DT16_ushort)0xFFFF;
	fdl->stroke_buf[ fdl->stridcnt ].strid = strid;
	fdl->stroke_buf[ fdl->stridcnt ].start = fdl->path_num;
	fdl->stroke_buf[ fdl->stridcnt ].status = 0;
	fdl->stroke_buf[ fdl->stridcnt ].line_num = 0;
	fdl->stroke_buf[ fdl->stridcnt ].line_type = FDL_STROKE_TYPE_UNKNOW;
#endif //FDL_OUTLINE_MODE

#ifdef FDL_WEIGHT
#ifdef FDL_OUTLINE_MODE
	if(fdl->weight_modeH >= 0)
	{
		fdl->stroke_weightX = 10;
		fdl->stroke_weightY = 10;
	}else
	{
		if(fdl->fontsizex < 32)
			fdl->stroke_weightY = stroke_weight[fdl->fontsizex];
		if(fdl->fontsizey < 32)
			fdl->stroke_weightX = stroke_weight[fdl->fontsizey];

		if(fdl->fontsizex >= 32 &&  fdl->fontsizex <= 48)
			fdl->stroke_weightY = stroke_weight[fdl->fontsizex];
		if(fdl->fontsizey >= 32 &&  fdl->fontsizey <= 48)
			fdl->stroke_weightX = stroke_weight[fdl->fontsizey];

	}// end if

	fdl->stroke_NormalWeightX = fdl->stroke_weightX;
	fdl->stroke_NormalWeightY = fdl->stroke_weightY;

	fdl->stroke_weightXSpace = fdl->stroke_weightX;
	fdl->stroke_weightYSpace = fdl->stroke_weightY;
	fdl->WeightX0 = fdl->WeightX = 256;
	fdl->WeightY0 = fdl->WeightY = 256;
	fdl->WeightRX = 0;
	fdl->WeightRY = 0;
	if(1)
	{
		DT32_int weightx, weighty;
		DT32_int REDUCE_WEIGHTX, REDUCE_WEIGHTY;
		weightx = weighty = 256;
		REDUCE_WEIGHTX = REDUCE_WEIGHTY = 0;

#ifndef FDL_ONLY_REMOVE_STROKE_NOHINTING
		if(fdl->hint > FDL_OLD_HINT)
		{
			if(fdl->stroke_weightX <= 10)
			{
				if(fdl->grade == DCW_MODE_GRAY16)
				{
	#ifdef LIMIT_SIZE
	//				if(fdl->fontsizey < LIMIT_SIZE && fdl->fontsizey < 24)
					if(fdl->fontsizey <= 24 && fdl->fontsizey <= LIMIT_SIZE && fdl->fontsizex < LIMIT_SIZE)
	#else
					if(fdl->fontsizey < 24)
	#endif // LIMIT_SIZE
					{
						weightx = 120 + (23 - fdl->fontsizey)*6;	// This value need modify by compare to font data.
						if(weightx > 256)
							weightx = 256;
					}else if(fdl->fontsizey < 24)
						weightx = 110;
					else weightx = 90;

				}else if(fdl->grade == DCW_MODE_GRAY256)
				{
					if(fdl->fontsizey < 24)
					{
						weightx = 120 + (23 - fdl->fontsizey)*10;	// This value need modify by compare to font data.
						if(weightx > 256)
							weightx = 256;
					}else weightx = 208;
				}// end if
			}// end if
#if 0
			if(fdl->stroke_weightY <= 10)
			{
				if(fdl->grade == DCW_MODE_GRAY16)
				{
#ifdef LIMIT_SIZE
					//				if(fdl->fontsizey < LIMIT_SIZE && fdl->fontsizey < 24)
					if(fdl->fontsizex <= 24 && fdl->fontsizex <= LIMIT_SIZE && fdl->fontsizey < LIMIT_SIZE)
#else
					if(fdl->fontsizex < 24)
#endif // LIMIT_SIZE
					{
						weighty = 120 + (23 - fdl->fontsizex)*6;	// This value need modify by compare to font data.
						if(weighty > 256)
							weighty = 256;
					}else if(fdl->fontsizex < 24)
						weighty = 110;
					else weighty = 90;

				}else if(fdl->grade == DCW_MODE_GRAY256)
				{
					if(fdl->fontsizex < 24)
					{
						weighty = 120 + (23 - fdl->fontsizex)*10;	// This value need modify by compare to font data.
						if(weighty > 256)
							weighty = 256;
					}else weighty = 208;
				}// end if
			}// end if
#endif // 0
		}// end if
#endif // FDL_ONLY_REMOVE_STROKE_NOHINTING

		REDUCE_WEIGHTX = 256 - weightx;
		REDUCE_WEIGHTY = 256 - weighty;
		fdl->WeightX0 = 256+REDUCE_WEIGHTX/2;
		fdl->WeightY0 = 256-REDUCE_WEIGHTY/2;
		fdl->WeightX = 256 - REDUCE_WEIGHTX;
		fdl->WeightY = 256 - REDUCE_WEIGHTY;
		fdl->WeightRX = REDUCE_WEIGHTX;
		fdl->WeightRY = REDUCE_WEIGHTY;
	}// end if
#endif // FDL_OUTLINE_MODE
#endif // FDL_WEIGHT

	if(fdl->Mode == FDL_MODE_RASTER2)
	{
		fdl->Frac     = 8 - (max(fdl->xsize2, fdl->ysize2) >> 12);
		//fdl->NsMaxSeg = max((1 << (fdl->Frac - 3)), 2);		// 2012-07-04[Alan]: avoid error of large size.
		if(fdl->Frac < 3)
          fdl->NsMaxSeg = 2;
		else fdl->NsMaxSeg = max((1 << (fdl->Frac -3)), 2);

		fdl->NsFrac2  = 1 << (fdl->Frac - 1);

		fdl->Frac2  = fdl->Frac;
		fdl->Flat2  = fdl->Frac2-1;

		fdl->Frac     = 1 << fdl->Frac;
	} else
	{
		if(max(fdl->xsize2,fdl->ysize2) < 128)
		{
			fdl->Frac  = 1 << 8;
			fdl->Flat  = 1 << 7;

			fdl->Frac2  = 8;
			fdl->Flat2  = 7;
		} else
		{
			fdl->Frac  = 1 << 3;
			fdl->Flat  = 1 << 2;

			fdl->Frac2  = 3;
			fdl->Flat2  = 2;
		}
	}

	fdl->FracMod = fdl->Frac - 1;

#ifdef FDL_OUTLINE_MODE
	fdl->shift = fdl->Frac2 + fdl->recycleshift;
#endif // FDL_OUTLINE_MODE
	fdl->S128 = (fdl->xsize2 < 128) && (fdl->ysize2 < 128);
	if(fdl->S128)
		fdl->SetValuePt = SetValueS128;
	else fdl->SetValuePt = SetValue;

	/* Initial Rel/Val */
	if(fdl->relno == 0)		/* Symbol */
	{
		fdl->Symbolcnt++;
		fdl->Xpoint[0] = fdl->Ypoint[0] = 0;
		if(fdl->S128)
		{
			fdl->Xpoint[1] = ((fdl->ysize2) << fdl->Frac2) - 1;
			fdl->Ypoint[1] = ((fdl->xsize2) << fdl->Frac2) - 1;
		} else
		{
			fdl->Xpoint[1] = ((256) << fdl->Frac2) - 1;
			fdl->Ypoint[1] = ((256) << fdl->Frac2) - 1;
		}// end if

		/*  load 01  */
		fdl->MNx1 = fdl->Xpoint[0];
		fdl->MNy1 = fdl->Ypoint[0];
		fdl->MNx2 = fdl->Xpoint[1];
		fdl->MNy2 = fdl->Ypoint[1];
		fdl->Diffx = fdl->MNx2 - fdl->MNx1;
		fdl->Diffy = fdl->MNy2 - fdl->MNy1;

		for(i=0; i< fdl->valno; i++)
			SetValueMacro(fdl, i, fdl->val[i]);
	}else	/* Stroke */
	{
		fdl->Strokecnt++;
		for(i=7; i >= 0; i--)
		{
			if(fdl->defval[i] != 0)
				SetValueMacro(fdl, i, fdl->defval[i]);
		}// end for

		if(fdl->S128)
		{
			for(i=0; i<fdl->relno; i++)
			{
				fdl->Xpoint[i] = fdl->rel[i*2]   << fdl->Frac2;
				fdl->Ypoint[i] = fdl->rel[i*2+1] << fdl->Frac2;
#ifndef FDL_CACHE_WEIGHT
				fdl->Xpoint[i] = ScaleX2(fdl, fdl->Xpoint[i]);
				fdl->Ypoint[i] = ScaleY2(fdl, fdl->Ypoint[i]);
#endif // FDL_CACHE_WEIGHT
			}// end for
		}else
		{
			for(i=0; i<fdl->relno; i++)
			{
				fdl->Xpoint[i] = fdl->rel[i*2]   << fdl->Frac2;
				fdl->Ypoint[i] = fdl->rel[i*2+1] << fdl->Frac2;
			}// end for
		}// end if
		for(i=0; i < fdl->valno; i++)
			SetValueMacro(fdl, i, fdl->val[i]);
	}

#ifdef FDL_WEIGHT
	{// block
/*		FDL_WEIGHT_MODE_UNIT *p = fdl->WeightDiff;			// Move this clear to below.
		for(i=0; i < fdl->relno; i++, p++)
		{
			p->XpointDiff = 0;
			p->YpointDiff = 0;
		}// end if
*/		fdl->WeightXDiff = fdl->WeightYDiff = 0;
		fdl->sx1x = fdl->sy1y = 0;
		fdl->sx2x = fdl->sy2y = 0;
		fdl->sx3x = fdl->sy3y = 0;
	}// end block
#endif // FDL_WEIGHT

	/* Setup raster buffer */
	fdl->Left_Ptr  = fdl->LeftBuf;
	fdl->Right_Ptr = fdl->RightBuf;

	if(fdl->Mode == FDL_MODE_RASTER)
	{
		fdl->FirstX    = -1;
		fdl->LeftWait  = fdl->RightWait = 0;
	} else if(fdl->Mode == FDL_MODE_RASTER2)
	{
//		NewScanInit(fdl);
	}// end if

	fdl->subidx = 0;
	// Process FDL data
	if(fdl->Mode == FDL_MODE_RASTER)
	{
		while(fdl->sdatacnt > 0)
		{
			fdl->path_num = 0;
			status = (DT16_WORD)Interpreter(fdl);
			if(status == FDL_UNKNOW_OP)
			{
				ret = DCW_BAD_FONTDATA;
				break;
			}

			Do_SCurve2(fdl, -1);

			{	// Draw raster
				if(fdl->Left_Ptr > fdl->Right_Ptr)
					fdl->Left_Ptr = fdl->Right_Ptr;
				fdl->RasterCnt = (DT32_long)(fdl->Left_Ptr - fdl->LeftBuf);

				if(fdl->RasterCnt > 0)
				{
					Adjust(fdl);
					if(!DrawBitmap(fdl))
					{
						ret = DCW_NOT_ENOUGH_WKMEM;
						break;
					}
				}

				fdl->FirstX = -1;
				fdl->LeftWait = fdl->RightWait = 0;
				fdl->Left_Ptr  = fdl->LeftBuf;
				fdl->Right_Ptr = fdl->RightBuf;
				if(status == FDL_END_OF_STR) break;
			}// end

			fdl->subidx++;
		}// end while
	}else if(fdl->Mode == FDL_MODE_RASTER2)
	{
		DT32_int curp=0;
//		DTShiftTable *point=NULL;
//		point = FindShiftTable(fdl->fontsizey, fdl->fontidx);
#ifndef FDL_OUTLINE_MODE
		NewScanInit(fdl);
		fdl->path_num = 0;
//		point = FindShiftTable(fdl->fontsizey, fdl->fontidx);
#else
		curp = fdl->path_num;
#endif // FDL_OUTLINE_MODE
		while(fdl->sdatacnt > 0)
		{
#ifdef FDL_WEIGHT
			FDL_WEIGHT_MODE_UNIT *p = fdl->WeightDiff;
			for(i=0; i < sizeof(fdl->WeightDiff)/sizeof(fdl->WeightDiff[0]); i++, p++)
			{
				p->XpointDiff = 0;
				p->YpointDiff = 0;
			}// end if
#endif // FDL_WEIGHT
			//DumpDebugString("  subidx %d\n", fdl->subidx);
			status = (DT16_WORD)Interpreter(fdl);
			if(status == FDL_UNKNOW_OP)
			{
				ret = DCW_BAD_FONTDATA;
				break;
			}// end if

			if(fdl->hint > FDL_OLD_HINT)
				AssignLeftOrRight(fdl, curp, fdl->path_num - curp);
			curp = fdl->path_num;

			{	// Draw raster
#ifdef DT_DEBUG
//				if(fdl->NsDownL != fdl->NsDownR)
//        			Debug((pDcwWrk)fdl->wrk, "  Unbalance(%d,%d)", fdl->NsDownL, fdl->NsDownR);
#endif // DT_DEBUG
					if(status == FDL_END_OF_STR)
						break;
			}// end
			fdl->subidx++;
		}// end while

		fdl->stroke_buf[ fdl->stridcnt ].len = fdl->path_num - fdl->stroke_buf[ fdl->stridcnt ].start;
		fdl->stroke_buf[ fdl->stridcnt ].strorder = fdl->stridcnt;
		fdl->stridcnt++;

#ifndef FDL_OUTLINE_MODE
/*		if(point != NULL && point->enable != 0 && !(fdl->hint == FDL_OLD_HINT && size >= 32))
		{
			DT32_int n;
			for(n=0; n < fdl->stridcnt; n++)
			{
				if(point->table[n].x != 0)
					ShiftStrokeX(fdl, n, (point->table[n].x * (fdl->recycle+1)) << fdl->Frac2);
				if(point->table[n].y != 0)
					ShiftStrokeY(fdl, n, (point->table[n].y * (fdl->recycle+1)) << fdl->Frac2);

				if(point->table[n].w != 0)
					ShiftStrokeW(fdl, n, (point->table[n].w * (fdl->recycle+1)) << fdl->Frac2);
				if(point->table[n].h != 0)
					ShiftStrokeH(fdl, n, (point->table[n].h * (fdl->recycle+1)) << fdl->Frac2);
			}// end for
		}// end if
*/
		i = 0;
		while(1)
		{
			fdl->subidx = fdl->path_buf[i].subidx;
			//DumpDebugString("  do %d subidx %d\n", i, fdl->path_buf[i].subidx);
			i = Do_SCurve2(fdl, i);		// The Do_SCurve2() will do i++, Alan.

			fdl->RasterCnt = min(fdl->NsDownL, fdl->NsDownR) - fdl->NsTop + 1;
			if(fdl->RasterCnt > 0)
			{
				fdl->FirstX = fdl->NsTop;
				Adjust(fdl);
				if(!DrawBitmap(fdl))
				{
					ret = DCW_NOT_ENOUGH_WKMEM;
					break;
				}// end if

				if(!(i < fdl->path_num))
					break;
				else NewScanInit(fdl);
			}// end if

		}// end while
#endif // FDL_OUTLINE_MODE
	}// end if

	return(ret);
}

DT32_int Do_DrawBitmap(DT_void *vwrk, pFdlRasterData fdl)
{
	PATH_UNIT *p = fdl->path_buf;
	DT32_int i;
	DT32_int curstridcnt;
	DT32_int ret = DCW_SUCCESS;
	i = 0;
#ifdef FDL_OUTLINE_MODE

 #ifdef ENABLE_ADV_HINTING
  #ifdef LIMIT_SIZE
	if(fdl->hint > FDL_OLD_HINT && fdl->Symbolcnt == 0
//		&& (fdl->fontsizey < LIMIT_SIZE)
		&& (!(fdl->fontsizex >= 24 && fdl->fontsizey >= 24)
		&& (fdl->fontsizey <= 24 && fdl->fontsizey <= LIMIT_SIZE) || (fdl->fontsizex <= LIMIT_SIZE && fdl->fontsizey < LIMIT_SIZE))
	)
  #else
	if(fdl->hint > FDL_OLD_HINT && 0==fdl->Symbolcnt)
  #endif // LIMIT_SIZE

	{
		
  #ifdef FDL_OUTLINE_MODE
		ScaleOutline(fdl);
  #endif // FDL_OUTLINE_MODE

  #ifdef DT_SVG_DEBUG
		BEGINCODE()
		ShowGrid(512, 512, fdl->fontsizey, 0x00FF00, (512/fdl->fontsizey)/(fdl->recycle+1));
		DrawSVGOutLineBG(fdl);
		ENDCODE()
		SVG_RETURN_STEP(1)
  #endif // DT_SVG_DEBUG

  #ifndef ONLY_REMOVE_STROKE
		Do_AdvHinting(fdl);
  #endif // ONLY_REMOVE_STROKE
		p = fdl->path_buf + fdl->path_buf_pt[0];

  #ifdef ONLY_REMOVE_STROKE
		fdl->path_buf_pt_num = fdl->path_num;
		for(i=0; i < fdl->path_num; i++)
			fdl->path_buf_pt[i] = i;
  #endif // ONLY_REMOVE_STROKE

  #ifdef DT_SVG_DEBUG
		BEGINCODE()
		DrawSVGOutLine(fdl);
		DumpDebugStringFile(NULL);	// For close SVG file.
		ENDCODE()
  #endif // DT_SVG_DEBUG

		Do_ClipRect(fdl);
  #if 0
		for(i=0; i < fdl->path_buf_pt_num; i++)
		{
			PATH_UNIT *p = fdl->path_buf + fdl->path_buf_pt[i];
			//DumpDebugString("  Point%d %d:%d %s rel:%d (%d, %d),(%d, %d) => (%d, %d),(%d, %d)\n", i, p->strorder, p->subidx, (p->lock & FDL_PATH_IsRightOrButtom) ? "E": "S", p->relation, p->sx1, p->sy1, p->sx3, p->sy3, (p->sx1 >> fdl->Frac2),  (p->sy1 >> fdl->Frac2),  (p->sx3 >> fdl->Frac2),  (p->sy3 >> fdl->Frac2));
		}// end if
  #endif // 0

	}else
	{
		ScaleOutline(fdl);

  #ifdef DT_SVG_DEBUG
//		BEGINCODE()
//		ShowGrid(512, 512, fdl->fontsizey, 0x00FF00, (512/fdl->fontsizey)/(fdl->recycle+1));
//		DrawSVGOutLineBG(fdl);
//		ENDCODE()
  #endif // DT_SVG_DEBUG

		fdl->path_buf_pt_num = fdl->path_num;
		for(i=0; i < fdl->path_num; i++)
			fdl->path_buf_pt[i] = i;
		p = fdl->path_buf + fdl->path_buf_pt[0];

  #ifdef DT_SVG_DEBUG
//		DrawSVGOutLine(fdl);
//		DumpDebugStringFile(NULL);	// For close SVG file.
  #endif // DT_SVG_DEBUG
	}// end if
 #else //ENABLE_ADV_HINTING
		p = fdl->path_buf;
 #endif //ENABLE_ADV_HINTING

 #ifdef ENABLE_ADV_HINTING
	for(i=0; i < fdl->path_buf_pt_num;)
 #else
	for(i=0; i < fdl->path_num;)
 #endif // ENABLE_ADV_HINTING
	{
		NewScanInit(fdl);
		fdl->gfdx = 0;
		fdl->gfdy = 0;
		curstridcnt = p->strorder;

		//DumpDebugString("======> strid %d\n", curstridcnt);
		while(1)
		{
			fdl->subidx = p->subidx;
			//DumpDebugString("  do %d subidx %d\n", i, fdl->path_buf[i].subidx);
			i = Do_SCurve3(fdl, curstridcnt, i);		// The Do_SCurve3() will do i++, Alan.

			fdl->RasterCnt = min(fdl->NsDownL, fdl->NsDownR) - fdl->NsTop;
			if(fdl->RasterCnt >= 0){
				if(fdl->grade){				// Jacky_20110509
					fdl->RasterCnt += 1;
				}else{						// Jacky_20110614: for the last line when monochrome
					if(0==fdl->RasterCnt && min(fdl->NsDownL, fdl->NsDownR) == fdl->NsTop)
						fdl->RasterCnt = 1;
					else
						fdl->RasterCnt += 1;
				}
			}

			if(fdl->RasterCnt > 0)
			{
				fdl->FirstX = fdl->NsTop;
				Adjust(fdl);

				if(!DrawBitmap(fdl))
				{
					ret = DCW_NOT_ENOUGH_WKMEM;
					break;
				}// end if

 #ifdef ENABLE_ADV_HINTING
				p = fdl->path_buf + fdl->path_buf_pt[i];
				if(!(i < fdl->path_buf_pt_num) || p->strorder != curstridcnt)
					break;
 #else
				p = fdl->path_buf+i;
				if(!(i < fdl->path_num) || p->strorder != curstridcnt)
					break;
 #endif // ENABLE_ADV_HINTING
				else NewScanInit(fdl);
			}else if(fdl->RasterCnt < 0)
			{
				i++;
				break;
			}// end if

		}// end while
	}// end for
#endif // FDL_OUTLINE_MODE

	return ret;
}// Do_DrawBitmap

// ============================================================================
// ============================================================================
// ============================================================================
#ifdef FDL_OUTLINE_CACHE

DT_void FG_OutlineCache_Initial(pFdlOutlineCacheData fgdata, DT8_char *mem, DT32_long memsize, DT_void *wrk)
{
	DT32_long lsize = 0;//lcnt * sizeof(DT16_WORD)*2;

	fgdata->wrk       = wrk;
	fgdata->memsize   = memsize;
	fgdata->pool      = (pOUTLINE_CACHE_UNIT)(mem + lsize);
	fgdata->freemax   = (DT16_WORD)((memsize - lsize) / sizeof(OUTLINE_CACHE_UNIT));
	fgdata->freelist  = 0;
	fgdata->recycle   = 0xffff;
	fgdata->freenum   = fgdata->freemax;

	//DT_memset(fgdata->pool, 0xff, memsize - lsize);	// I hope that we don't need to clear this pool.
}// end FG_OutlineCache_Initial

static DT32_int FG_OutlineCache_Get(pFdlOutlineCacheData fgdata, DT16_WORD *idx)
{
	if(fgdata->freelist >= fgdata->freemax)						// Alan.
	{
		if(fgdata->recycle != 0xffff)
		{
			*idx = fgdata->recycle;
			fgdata->recycle = fgdata->pool[*idx].next;
			fgdata->freenum--;

			return 1;
		}else
		{
			*idx = 0xffff;
			return 0;
		}// end if
	}else
	{	// Alan.
		*idx = fgdata->freelist++;
		fgdata->freenum--;
		return 1;
	}// end if

}// end FG_OutlineCache_Get

static DT_void FG_OutlineCache_Free(pFdlOutlineCacheData fgdata, DT16_WORD idx)
{
	if(fgdata->recycle != 0xffff)
		fgdata->pool[idx].next = fgdata->recycle;
	else
		fgdata->pool[idx].next = 0xffff;

	fgdata->recycle = idx;
	fgdata->freenum++;
}// end FG_OutlineCache_Free

DT_void FG_OutlineCache_Delete(pFdlOutlineCacheData fgdata, DT16_WORD idx)
{
	DT16_WORD nextidx;

	while(idx != 0xffff)
	{
		nextidx = fgdata->pool[idx].next;
		FG_OutlineCache_Free(fgdata, idx);
		idx = nextidx;
	}// end while

}// end FG_OutlineCache_Delete

DT32_int FG_OutlineCache_Add(pFdlOutlineCacheData fgdata, PATH_UNIT *data, DT32_int num)
{
	DT16_WORD i, startidx, idx;
	if(num <= 0 || fgdata->freenum < num)
		return -1;

	if(FG_OutlineCache_Get(fgdata, &startidx) == 0)
	{
#ifdef DT_DEBUG
		//DumpDebugString("    OutlineCache error !!!!!!\n");
#endif
		return -1;
	}// end if

	DT_memcpy(fgdata->pool+startidx, data, sizeof(PATH_UNIT));

	for(i=1; i < num; i++)
	{
		if(!FG_OutlineCache_Get(fgdata, &idx))
		{
			DT_memcpy(fgdata->pool+idx, data, sizeof(PATH_UNIT));
		}else
		{
			FG_OutlineCache_Delete(fgdata, startidx);
#ifdef DT_DEBUG
			//DumpDebugString("    OutlineCache error2 !!!!!!\n");
#endif
			return -1;
		}// end if
	}// end for

	return startidx;
}// end FG_OutlineCache_Add

pOUTLINE_CACHE_UNIT FG_OutlineCache_GetNext(pFdlOutlineCacheData fgdata, pOUTLINE_CACHE_UNIT pair)
{
	DT32_int idx = pair->next;

	if(idx != 0xffff)
		return &fgdata->pool[idx];
	else
		return NULL;
}// end FG_OutlineCache_GetNext

DT32_int FG_OutlineCache_GetPathData(pFdlOutlineCacheData fgdata, DT16_WORD idx, PATH_UNIT *data)
{
	DT32_int counter=0;
	pOUTLINE_CACHE_UNIT pair;

	while(idx != 0xffff)
	{
		pair = fgdata->pool+idx;
		DT_memcpy(data+counter, pair, sizeof(PATH_UNIT));
		idx = pair->next;
		counter++;
	}// end while

	return counter;
}// end FG_OutlineCache_GetPathData

// ============================================================================
static B_OutlineCacheUnit TmpIndex[MAX_OUTLINE_CACHE_NUM];
DT_void InitOutlineCache(pFdlRasterData fdl)
{
	if(fdl->Init_OutlineCache == 0)
	{
		DT32_int i;
		fdl->Init_OutlineCache = 1;
		fdl->OutlineCacheNum = 0;
		fdl->OutlineCacheHead = 0;

#ifdef PRERENDER_FONT_ON
		PreArray1 = unicodeArray;
		PreArray2 = unicodeArray;
		PreArray3 = unicodeArray;

		InitPreCache(MAX_STATIC_CACHE_NUM1, PreArray1);
//		DT_memcpy((CHAR*)PreArray2, (CHAR*)PreArray1, sizeof(PreArray1));
//		DT_memcpy((CHAR*)PreArray3, (CHAR*)PreArray1, sizeof(PreArray1));
//		InitPreCache(MAX_STATIC_CACHE_NUM2, PreArray2);
//		InitPreCache(MAX_STATIC_CACHE_NUM3, PreArray3);

#ifndef STATIC_PRERENDER_FONT_ON
		FillPreCache(DFL_MEDSMALL_R, PreArray1, MAX_STATIC_CACHE_NUM1, (UCHAR*)StaticCache1, sizeof(StaticCacheUnit1));		// 18
		FillPreCache(DFL_SMALL_R, PreArray2, MAX_STATIC_CACHE_NUM2, (UCHAR*)StaticCache2, sizeof(StaticCacheUnit2));		// 20
		FillPreCache(DFL_MEDLARGE_R, PreArray3, MAX_STATIC_CACHE_NUM3, (UCHAR*)StaticCache3, sizeof(StaticCacheUnit3));		// 24
#endif // STATIC_PRERENDER_FONT_ON
#endif // end PRERENDER_FONT_ON

		for(i=0; i < MAX_OUTLINE_CACHE_NUM; i++)
		{
			fdl->OutlineBIndex[i].RingIndex = i;
			fdl->OutlineBIndex[i].idx = 0xFFFF;
		}// end for
	}// end if
}// end InitCache


DT32_int OutlineBSearch(pFdlRasterData fdl, DT32_long key, B_OutlineCacheUnit* array, DT32_int* len, DT32_int DelKey, DT32_int MaxNum)
{
	DT32_int start, now, end;

	start = 0;
	end = *len-1;

	while(start <= end)
	{
		now = (end+start)/2;

		if(array[now].key == key)
			return now;

		if(key < array[now].key)
			end = now-1;
		else
		{
			start = now+1;
			now++;
		}// end if
	}// end while

	if(DelKey >= 0)
	{
		DT32_int OldPointer;

		if(*len < MaxNum)			// insert key
		{
			OldPointer = FG_OutlineCache_Add( &(((pDcwWrk)(fdl->wrk))->goutlinecache), fdl->path_buf, fdl->path_num);
			if(OldPointer < 0)
				return -1;
			DT_memcpy((DT_void*)TmpIndex, (DT_void*)(array+now), (*len-now)*sizeof(B_OutlineCacheUnit));
			DT_memcpy((DT_void*)(array+now+1), (DT_void*)TmpIndex, (*len-now)*sizeof(B_OutlineCacheUnit));
			(*len)++;
		}else						// replace delkey
		{
			OldPointer = FG_OutlineCache_Add( &(((pDcwWrk)(fdl->wrk))->goutlinecache), fdl->path_buf, fdl->path_num);
			if(OldPointer < 0)
				return -1;

			FG_OutlineCache_Delete( &(((pDcwWrk)(fdl->wrk))->goutlinecache), array[DelKey].idx);
			if(DelKey > now)
			{
				DT_memcpy((DT_void*)TmpIndex, (DT_void*)(array+now), (DelKey-now)*sizeof(B_OutlineCacheUnit));
				DT_memcpy((DT_void*)(TmpIndex+DelKey-now), (DT_void*)(array+DelKey+1), (*len-DelKey-1)*sizeof(B_OutlineCacheUnit));
				DT_memcpy((DT_void*)(array+now+1), (DT_void*)TmpIndex, (*len-now-1)*sizeof(B_OutlineCacheUnit));
			}else if(DelKey < now)
			{
				now--;
				DT_memcpy((DT_void*)(array+DelKey), (DT_void*)(array+DelKey+1), (now-DelKey)*sizeof(B_OutlineCacheUnit));
			}// end if
		}// end if

		array[now].key = key;
		array[now].idx = OldPointer;

		return now;
	}// end if

	return -1;
}// end OutlineBSearchBSearch

DT32_int OutlineTouchCache(pFdlRasterData fdl, DT32_long code, DT32_int MyPt)
{
	DT32_int MyKey, ItKey;
	DT32_int MyHead, ItHead;
	DT32_int ItPt;

	if(fdl->OutlineCacheNum == 0)
		return 0;

	MyKey = code; // + (((BYTE)height + ((BYTE)width << sizeof(SHORT)*8/2)) << sizeof(INT)*8/2);

//	if((MyPt = OutlineBSearch(fdl, MyKey, fdl->OutlineBIndex, &(fdl->OutlineCacheNum), SEARCH_MODE, MAX_OUTLINE_CACHE_NUM)) < 0)
//		return -1;

	if(fdl->OutlineBIndex[MyPt].RingIndex == fdl->OutlineCacheHead)				// already in top
		return 1;

	MyHead = fdl->OutlineBIndex[MyPt].RingIndex;
	ItHead = (MyHead+1) % (MAX_OUTLINE_CACHE_NUM);				// new position
	ItKey = fdl->OutlineRingIndex[ItHead];

	if((ItPt = OutlineBSearch(fdl, ItKey, fdl->OutlineBIndex, &(fdl->OutlineCacheNum), SEARCH_MODE, MAX_OUTLINE_CACHE_NUM)) < 0)
	{
#ifdef DT_DEBUG
		//DumpDebugString("MidPT error %d, %d, %d !!!\n", ItKey, ItHead, MyPt);
#endif
		return -1;
	}// end if

	fdl->OutlineBIndex[MyPt].RingIndex = ItHead;
	fdl->OutlineRingIndex[MyHead] = ItKey;
	fdl->OutlineBIndex[ItPt].RingIndex = MyHead;
	fdl->OutlineRingIndex[ItHead] = MyKey;

	return 1;
}// end OutlineTouchCache

DT32_int OutlineAddToCache(pFdlRasterData fdl, DT32_long code, DT_void* data, DT32_int size)
{
	DT32_int key, pt;
	DT32_int DelCode = 0;

//	if(width > MAX_CACHE_FONT || height > MAX_CACHE_FONT)
//		return 0;	// too big size

	key = code;// + (((BYTE)height + ((BYTE)width << sizeof(SHORT)*8/2)) << sizeof(INT)*8/2);

	fdl->OutlineCacheHead = (fdl->OutlineCacheHead+1) % (MAX_OUTLINE_CACHE_NUM);

	if(fdl->OutlineCacheNum < MAX_OUTLINE_CACHE_NUM)	// append new element
	{
		if(fdl->OutlineCacheNum > 0)
			pt = OutlineBSearch(fdl, key, fdl->OutlineBIndex, &(fdl->OutlineCacheNum), fdl->OutlineCacheHead, MAX_OUTLINE_CACHE_NUM);
		else
		{
			pt = 0;
			fdl->OutlineBIndex[pt].key = key;
			fdl->OutlineCacheNum++;
		}// end if
	}else												// replace oldest element
	{
		DelCode = OutlineBSearch(fdl, fdl->OutlineRingIndex[fdl->OutlineCacheHead], fdl->OutlineBIndex, &(fdl->OutlineCacheNum), SEARCH_MODE, MAX_OUTLINE_CACHE_NUM);
		pt = OutlineBSearch(fdl, key, fdl->OutlineBIndex, &(fdl->OutlineCacheNum), DelCode, MAX_OUTLINE_CACHE_NUM);
	}// end if

	fdl->OutlineBIndex[pt].RingIndex = fdl->OutlineCacheHead;
	fdl->OutlineRingIndex[fdl->OutlineCacheHead] = key;

//	SHORT index = fdl->BIndex[pt].pointer;
//	fdl->FontCache[ index ].width = actw;
//	fdl->FontCache[ index ].height = acth;
//	DT_memcpy((DT8_char*)(fdl->FontCache[ index ].data), data, size);

	return 1;
}// end OutlineAddToCache

DT16_WORD GetOutlineFromCache(pFdlRasterData fdl, DT32_long code)
{
	DT32_long key;
	DT32_int index;

	key = code;		// + (((BYTE)height + ((BYTE)width << sizeof(SHORT)*8/2)) << sizeof(INT)*8/2);

	if(fdl->OutlineCacheNum == 0)
		return -1;

	index = OutlineBSearch(fdl, key, fdl->OutlineBIndex, &(fdl->OutlineCacheNum), SEARCH_MODE, MAX_OUTLINE_CACHE_NUM);
	if(index >= 0)
	{
		OutlineTouchCache(fdl, code, index);
		return fdl->OutlineBIndex[index].idx;// pointer to OutlineCache
//		return (fdl->FontCache) + fdl->OutlineBIndex[index].idx;// pointer to OutlineCache
	}// end if

	return -1;
}// end GetFromCache

#endif

// ============================================================================

typedef struct
{
	DT32_int    (*cmp)(pFdlRasterData fdl, DT_void*, DT_void*);
	DT_void     (*swap)(DT8_char*, DT8_char*, DT32_long);
	DT32_long   es;
}Sort;

static DT_void swapb(DT8_char *i, DT8_char *j, DT32_long es)
{
	DT8_char c;
	do
	{
		c = *i;
		*i++ = *j;
		*j++ = c;
		es--;
	} while(es != 0);
}// end swapb

static DT_void swapi(DT8_char *ii, DT8_char *ij, DT32_long es)
{
	DT32_long *i, *j, c;

	i = (DT32_long*)ii;
	j = (DT32_long*)ij;
	do
	{
		c = *i;
		*i++ = *j;
		*j++ = c;
		es -= sizeof(DT32_long);
	} while(es != 0);
}// end swapi

static DT8_char* pivot(pFdlRasterData fdl, DT8_char *a, DT32_long n, Sort *p)
{
	DT32_long j;
	DT8_char *pi, *pj, *pk;

	j = n/6 * p->es;
	pi = a + j;		/* 1/6 */
	j += j;
	pj = pi + j;	/* 1/2 */
	pk = pj + j;	/* 5/6 */
	if(p->cmp(fdl, pi, pj) < 0)
	{
		if(p->cmp(fdl, pi, pk) < 0)
		{
			if(p->cmp(fdl, pj, pk) < 0)
				return(pj);
			return(pk);
		}
		return(pi);
	}
	if(p->cmp(fdl, pj, pk) < 0)
	{
		if(p->cmp(fdl, pi, pk) < 0)
			return(pi);
		return(pk);
	}
	return(pj);
}

static DT_void qsorts(pFdlRasterData fdl, DT8_char *a, DT32_long n, Sort *p)
{
	DT32_long j, es;
	DT8_char *pi, *pj, *pn;

	es = p->es;
	while(n > 1)
	{
		if(n > 10)
		{
			pi = pivot(fdl, a, n, p);
		} else
			pi = a + (n>>1)*es;

		p->swap(a, pi, es);
		pi = a;
		pn = a + n*es;
		pj = pn;
		for(;;)
		{
			do
				pi += es;
			while(pi < pn && p->cmp(fdl, pi, a) < 0);
			do
				pj -= es;
			while(pj > a && p->cmp(fdl, pj, a) > 0);
			if(pj < pi)
				break;
			p->swap(pi, pj, es);
		}
		p->swap(a, pj, es);
		j = (pj - a) / es;

		n = n-j-1;
		if(j >= n)
		{
			qsorts(fdl, a, j, p);
			a += (j+1)*es;
		} else
		{
			qsorts(fdl, a + (j+1)*es, n, p);
			n = j;
		}
	}
}

DT_void DT_qsort(pFdlRasterData fdl, DT_void *va, DT32_long n, DT32_long es, DT32_int (*cmp)(pFdlRasterData, DT_void*, DT_void*))
{
	Sort s;

	s.cmp = cmp;
	s.es = es;
	s.swap = swapi;
	if(((DT32_long)va | es) % sizeof(DT32_long))
		s.swap = swapb;
	qsorts(fdl, (DT8_char*)va, n, &s);
}// end DT_qsort

DT_void Do_MoveInterXPoint(pFdlRasterData fdl, DT32_long offset,  DT32_int lineorder, DT32_int/*BOOL*/ str_self)
{
		DT32_int i,j, k, x1,xx1, xx1_offset;
		PATH_UNIT *p, *p0, *p1, *p2;
		DT32_long rect_left, rect_top, rect_right, rect_bottom;

		
		p = fdl->path_buf + lineorder;
		p0 = fdl->path_buf + fdl->stroke_buf[p->strorder].start;
		xx1_offset = offset;	
		x1 = p->sx1;
	
		for(i=0; i < fdl->stroke_buf[p->strorder].len; i++, p0++)
		{
			//Conditions: the start of stroke, vertical line.
			if( (p0->sx1 == x1 || p0->sx3 == x1) &&  (p0->relation>=0) && (p0->dir == FDL_PATH_VERT))
			{
				if(p0->sx1< (fdl->path_buf+p0->relation)->sx1 )
				{
					rect_left = p0->sx1;
					rect_right= (fdl->path_buf+p0->relation)->sx1;
				}else
				{
					rect_left = (fdl->path_buf+p0->relation)->sx1;
					rect_right= p0->sx1; 
				}
				rect_top = ( *(p0->sy01) > *(fdl->path_buf+p0->relation)->sy01) ? *(p0->sy01): *((fdl->path_buf+p0->relation)->sy01);
				rect_bottom = ( *(p0->sy03) < *(fdl->path_buf+p0->relation)->sy03) ? *(p0->sy03): *((fdl->path_buf+p0->relation)->sy03);

				//p1 = fdl->path_buf;
				//for(j=0; j<fdl->path_num; j++, p1++)
				for(j=0; j < fdl->path_buf_pt_num; j++)
				{
					p1 = fdl->path_buf+fdl->path_buf_pt[j]; 

					if(j>=fdl->stroke_buf[p->strorder].start
						&&  j <fdl->stroke_buf[p->strorder].start+fdl->stroke_buf[p->strorder].len)
					{
						if(!str_self)
							continue;
						else
						if(p1->dir == FDL_PATH_VERT)
						{
							if( rect_left < p1->sx1 && p1->sx1 < rect_right 
								&& rect_top < *(p1->sy01) && *(p1->sy03) < rect_bottom )
							{
								p2 = fdl->path_buf + fdl->stroke_buf[p1->strorder].start;
								xx1 = p1->sx1;

								for(k=0; k<fdl->stroke_buf[p1->strorder].len; k++, p2++)
								{
										if(p2->sx1 == xx1)
											p2->sx1+=xx1_offset;
										if(p2->sx3 == xx1)
											p2->sx3+=xx1_offset;
								}
							}
						}
					}
					else
					{
						if(p1->dir == FDL_PATH_VERT)
						{
							if( rect_left < p1->sx1 && p1->sx1 < rect_right 
								&& rect_top < *(p1->sy01) && *(p1->sy03) < rect_bottom )
							{
								p2 = fdl->path_buf + fdl->stroke_buf[p1->strorder].start;
								xx1 = p1->sx1;
							
								for(k=0; k<fdl->stroke_buf[p1->strorder].len; k++, p2++)
								{
										if(p2->sx1 == xx1)
											p2->sx1+=xx1_offset;
										if(p2->sx3 == xx1)
											p2->sx3+=xx1_offset;
								}
							}
						}
					}
				}
			}
		}
}

DT_void Do_MoveInterXPath(pFdlRasterData fdl, DT32_long offset, DT32_int lineorder)
{
	DT32_int j;
	PATH_UNIT *p, *p_inpath;
	DT8_uchar num_inpath,i;
	DT8_uchar *pidx_inter;
	DT32_long sx1, sy1, sx3, sy3;

	p = fdl->path_buf + lineorder;
	num_inpath = fdl->interlines[p->idx_interline];
	pidx_inter = fdl->interlines+p->idx_interline+1;
	for(i=0; i<num_inpath; i++, pidx_inter++)
	{
		p_inpath = fdl->path_buf+ (*pidx_inter);
		sx1 = p_inpath->sx1;
		sy1 = p_inpath->sy1;
		sx3 = p_inpath->sx3;
		sy3 = p_inpath->sy3;

		p = fdl->path_buf+fdl->stroke_buf[p_inpath->strorder].start;
		for(j=0; j<fdl->stroke_buf[p_inpath->strorder].len; j++, p++)
		{
			if( (p->sx1 == sx1 && p->sy1 == sy1)
				||(p->sx1 == sx3 && p->sy1 == sy3) )
			{
				p->sx1+=offset;
			}
			if( (p->sx3 == sx1 && p->sy3 == sy1)
				||(p->sx3 == sx3 && p->sy3 == sy3) )
			{
				p->sx3+=offset;
			}
		}		
	}
}

DT_void Do_AvgInterXPath(pFdlRasterData fdl, DT32_int lineorder)
{
	DT32_int j;
	PATH_UNIT *p, *p_r, *p_inpath, *p0;
	DT8_uchar num_inpath,i;
	DT8_uchar *pidx_inter;
	DT32_long sx1, sy1, sx3, sy3;
	DT32_long avg_sx;

	p0 = fdl->path_buf + lineorder;
	p = fdl->path_buf + lineorder;
	p_r = fdl->path_buf + p->relation;

	avg_sx = (p->sx1+p_r->sx1)>>1;

	num_inpath = fdl->interlines[p->idx_interline];
	pidx_inter = fdl->interlines+p->idx_interline+1;
	for(i=0; i<num_inpath; i++, pidx_inter++)
	{
		p_inpath = fdl->path_buf+ (*pidx_inter);
		sx1 = p_inpath->sx1;
		sy1 = p_inpath->sy1;
		sx3 = p_inpath->sx3;
		sy3 = p_inpath->sy3;

		p = fdl->path_buf+fdl->stroke_buf[p_inpath->strorder].start;
		for(j=0; j<fdl->stroke_buf[p_inpath->strorder].len; j++, p++)
		{
			if( (p->sx1 == sx1 && p->sy1 == sy1)
				||(p->sx1 == sx3 && p->sy1 == sy3) )
			{
				p->sx1 = avg_sx;
				if((p0->lock & FDL_PATH_LOCK_sx1) !=0) //FDL_PATH_LOCK_sx3
				{
					p->lock |= FDL_PATH_LOCK_sx1;
			}
			}

			if( (p->sx3 == sx1 && p->sy3 == sy1)
				||(p->sx3 == sx3 && p->sy3 == sy3) )
			{
				p->sx3 = avg_sx;
				if((p0->lock & FDL_PATH_LOCK_sx1) !=0)
				{
					p->lock |= FDL_PATH_LOCK_sx3;
			}
		}		

		
		}		
	}
}

DT_void Do_FindInterPath(pFdlRasterData fdl)
{
	DT32_int i,j;
	PATH_UNIT *p,*p0;
	DT32_long rect_left, rect_top, rect_right, rect_bottom;

	DT8_uchar *p_cnt_interlines;	/* Jacky_Modified_20101015, DT8_char => DT8_uchar */
	DT8_uchar *p_interlines;		/* Jacky_Modified_20101015, DT8_char => DT8_uchar */
	DT8_char idx_interlines;

	p0 = fdl->path_buf;
	p_cnt_interlines = fdl->interlines;
	p_interlines = p_cnt_interlines+1;
	idx_interlines = 0;

	*p_cnt_interlines = 0;

	for(i=0; i<fdl->path_num; i++, p0++)
	{
		*p_cnt_interlines = 0;

		if((p0->relation>=0) && (p0->dir == FDL_PATH_VERT))
		{
				if(p0->sx1< (fdl->path_buf+p0->relation)->sx1 )
				{
					rect_left = p0->sx1;
					rect_right= (fdl->path_buf+p0->relation)->sx1;
				}else
				{
					rect_left = (fdl->path_buf+p0->relation)->sx1;
					rect_right= p0->sx1; 
				}
				rect_top = ( *(p0->sy01) > *(fdl->path_buf+p0->relation)->sy01) ? *(p0->sy01): *((fdl->path_buf+p0->relation)->sy01);
				rect_bottom = ( *(p0->sy03) < *(fdl->path_buf+p0->relation)->sy03) ? *(p0->sy03): *((fdl->path_buf+p0->relation)->sy03);

			
			p = fdl->path_buf;
			for(j=0; j<fdl->path_num; j++, p++)
			{	
				if(i!=j && (p->dir == FDL_PATH_VERT))
				{
						if( rect_left < *p->sx01 && *p->sx03 < rect_right 
								&& rect_top <= *(p->sy01) && *(p->sy03) <= rect_bottom )
						{
								(*p_cnt_interlines)++; 
								*p_interlines = j;
								p_interlines++;
						}

						if(  (rect_left == *p->sx01 || *p->sx03 == rect_right) 
								&& rect_top < *(p->sy01) && *(p->sy03) < rect_bottom )
						{
								(*p_cnt_interlines)++; 
								*p_interlines = j;
								p_interlines++;
						}
				}else continue;
			}
		}
		else continue;
		
		if((*p_cnt_interlines) ==0)
		{
		  p0->idx_interline = -1;
		}
		else{
				
				p0->idx_interline = idx_interlines ;
				idx_interlines+=(p_interlines -  p_cnt_interlines);
				p_cnt_interlines = p_interlines;
				p_interlines++;
		}
	}
	
	*p_cnt_interlines =0;
	*p_interlines = 0;

	//----------------------------------------------------------
	Do_FindHidePath_L(fdl);
}

DT_void Do_FindHidePath_L(pFdlRasterData fdl)
{

	DT32_int i;
	DT8_uchar j,num_inpath;
	DT8_uchar *pidx_inter;
	i=0;
	while(1)
	{	
		num_inpath = fdl->interlines[i];
		if(num_inpath<=0)
			break;
		else
		{
			i++;
			pidx_inter = fdl->interlines+i;
			for(j=0; j<num_inpath; j++,pidx_inter++)
			{
				fdl->path_buf[*pidx_inter].lock|= FDL_PATH_IsHide; 
			}
			i+=num_inpath;
		}
	}
}

DT_void Do_FindJointPath(pFdlRasterData fdl)
{
	DT32_int i,j;
	DT32_int str_idx;
	PATH_UNIT *p, *p_str_start, *p0;
	DT8_char strorder;

	p_str_start = NULL;
	p = fdl->path_buf;
	strorder = -1;
	for(i=0; i<fdl->path_num; i++, p++)
	{
		if(strorder != p->strorder)
		{
			strorder = p->strorder;
			p_str_start = p;
			str_idx = i;
		}

		if(p_str_start != NULL)
		{
			p0 = p_str_start;
			for(j=str_idx; j<fdl->path_num; j++, p0++)
			{
				if(p->strorder==strorder)
				{
					if(i!=j)
					if( *p->sx01 == *p0->sx01 
						|| *p->sx03 == *p0->sx03
						|| *p->sy01 == *p0->sy01
						|| *p->sy03 == *p0->sy03)
					{
						p->lock |= FDL_PATH_IsJoint;
					}else;
				}else break;
			}
		}// end if
	}

}



typedef struct 
{
		DT32_long a;
		DT32_long b;
		DT32_long c;
}CO_LINE;

typedef struct 
{
	CO_LINE left_top;
	CO_LINE	right_top;
	CO_LINE	left_bottom;
	CO_LINE	right_bottom;
}FOUR_LINES_AREA;

typedef struct 
{
	DT32_long sx_t;
	DT32_long sy_t;
	DT32_long sx_l;
	DT32_long sy_l;
	DT32_long sx_r;
	DT32_long sy_r;
	DT32_long sx_b;
	DT32_long sy_b;

}FOUR_POINTS_AREA;

DT_void makeLines(DT32_long sx1, DT32_long sy1,
				  DT32_long sx2, DT32_long sy2, 
				  CO_LINE * coLine)
{
	coLine->a = sy2-sy1;
	coLine->b = sx1-sx2;
	coLine->c = sy1*sx1 + sy1*sx2 - sy2*sx1 - sy1*sx1;
}

DT_void makeLinesArea(FOUR_POINTS_AREA *points_area, FOUR_LINES_AREA * lines_area)
{
	makeLines(points_area->sx_l, points_area->sy_l, points_area->sx_t, points_area->sy_t, 
				  &(lines_area->left_top));

	makeLines(points_area->sx_r, points_area->sy_r, points_area->sx_t, points_area->sy_t, 
				  &(lines_area->right_top));

	makeLines(points_area->sx_l, points_area->sy_l, points_area->sx_b, points_area->sy_b, 
				  &(lines_area->left_bottom));
	
	makeLines(points_area->sx_r, points_area->sy_r, points_area->sx_b, points_area->sy_b, 
				  &(lines_area->right_bottom));
}

DT32_int checkHit(FOUR_LINES_AREA * lines_area, DT32_long sx, DT32_long sy)
{
		if( (lines_area->left_top.a*sx+lines_area->left_top.b+lines_area->left_top.c) <0
			|| (lines_area->right_bottom.a*sx+lines_area->right_bottom.b+lines_area->right_bottom.c) >0
			|| (lines_area->right_top.a*sx+lines_area->right_top.b+lines_area->right_top.c) <0
			|| (lines_area->left_bottom.a*sx+lines_area->left_bottom.b+lines_area->left_bottom.c) >0
		)
		{
			return 1;
		}	
		return 0;
}


#define  MAX_NUM_IPATH (8)

DT_void Do_FindHidePath(pFdlRasterData fdl)
{
	DT32_int i,j,k,l;
	DT8_char subidx;
	PATH_UNIT *p, *p0, *p1;
	
	CO_LINE colines[MAX_NUM_IPATH];  
	CO_LINE * pcoline;

	DT32_int idx_begin, idx_end;
	DT32_int len_path;
	DT32_int leftside;
	DT32_int rightside;
	DT32_int line_sum;
	DT32_int bFind=0;

	for(i=0; i<fdl->stridcnt; i++)
	{
		if(fdl->stroke_buf[i].len <6)
			continue;
		else
		{
			p0 = fdl->path_buf+fdl->stroke_buf[i].start;
			subidx  = p0->subidx;
			idx_begin = 0;
			idx_end = 0;
			pcoline = colines;
			len_path =0;
			bFind =0;
			for(j=0; j<fdl->stroke_buf[i].len; j++, p0++)
			{
				if(p0->subidx == subidx)
				{
					if(len_path<MAX_NUM_IPATH)
					{
						makeLines(p0->sx1, p0->sy1, p0->sx3, p0->sy3, pcoline++);
						len_path++;
					}
					if(j==fdl->stroke_buf[i].len-1)
					{
						bFind= 1;
						idx_begin = idx_end;
						idx_end = j+1;
					}	
				}
				else{
					bFind= 1;
					idx_begin = idx_end;
					idx_end = j;
					subidx = p0->subidx;
				}
				if(bFind)
				{
					p = fdl->path_buf+fdl->stroke_buf[i].start;
					for(k=0; k<fdl->stroke_buf[i].len; k++, p++)
					{
							if((idx_begin<=k && k<idx_end)
							//	|| (p->dir != FDL_PATH_VERT)
							  )
								continue;
							else{	
									leftside = 0;
									rightside= 0;
									pcoline = colines;
									p1 = fdl->path_buf+fdl->stroke_buf[i].start+idx_begin;
									for(l=0;l<len_path; l++, p1++ , pcoline++)
									{
										if( (*p1->sy01) <= p->sy1 && p->sy1 <= (*p1->sy03) )
										{
											line_sum = pcoline->a*p->sx1+pcoline->b*p->sy1+pcoline->c;
											if(line_sum == 0)
											{
												leftside=1;
												rightside=1;
												break;
											}
											if( line_sum<0)
											{
												leftside++;		
											}
											else
											{
												rightside++;
											}
										}
									}
									if(leftside==1 && rightside==1)
									{	
										leftside = 0;
										rightside= 0;
										pcoline = colines;
										p1 = fdl->path_buf+fdl->stroke_buf[i].start+idx_begin;
										for(l=0;l<len_path; l++, p1++ , pcoline++)
										{
											if( (*p1->sy01) <= p->sy3 && p->sy3 <= (*p1->sy03) )
											{
												line_sum = pcoline->a*p->sx3+pcoline->b*p->sy3+pcoline->c;
												if(line_sum == 0)
												{
													leftside=1;
													rightside=1;
													break;
												}
												if( line_sum<0)
												{
													leftside++;		
												}
												else
												{
													rightside++;
												}
											}
										}
										if(leftside==1 && rightside==1)
										{
											p->lock |= FDL_PATH_IsHide;
										}
									}
							}
					}//for
					len_path =0;
					bFind = 0;
					pcoline = colines;
					if(len_path<MAX_NUM_IPATH)
					{
						makeLines(p0->sx1, p0->sy1, p0->sx3, p0->sy3, pcoline++);
						len_path++;
					}
				}//if(bFind)
			}//for
		}
	}//for
}//Do_FindHidePath


DT_void Do_FindnPath(pFdlRasterData fdl, DT8_char do_dir)
{
#define MAX_MID (8)
   	DT32_int i,j,k;
	PATH_UNIT *p, *p0;
	DT16_short order;
	DT32_int ar_mid_idx[MAX_MID];
	DT32_int mid_idx;
	DT8_char dir = FDL_PATH_HORZ ;
	
	if(do_dir == FDL_PATH_VERT)
	{
		dir = do_dir;
	}

  	for(i=0; i<fdl->stridcnt; i++)
	{

			if(fdl->stroke_buf[i].len <6)
				continue;
			else
			{
				p0 = fdl->path_buf+fdl->stroke_buf[i].start;
				for(j=0; j<fdl->stroke_buf[i].len; j++, p0++)
				{
					if(p0->dir == dir)
					{
						order = fdl->stroke_buf[i].start+j;
						p = fdl->path_buf+fdl->stroke_buf[i].start;
						mid_idx =0;
						for(k=0; k<fdl->stroke_buf[i].len; k++, p++)
						{
							if(j==k)
								continue;
							if(p->dir == dir && order == p->relation)
							{
								if(dir == FDL_PATH_HORZ )
								{
									if(mid_idx<MAX_MID) ar_mid_idx[mid_idx++]=k;	
								}
								else{
									if(mid_idx<MAX_MID) ar_mid_idx[mid_idx++]=k;
								}
							}
						}

						if(mid_idx>=2)
						{
							for(k=0; k<mid_idx; k++)
							{
								(fdl->path_buf+ar_mid_idx[k]+fdl->stroke_buf[i].start)->lock |= FDL_PATH_IsLFar;
							}
						}

					}
				}
			
			}
	}
}

DT_void Do_FindLPath(pFdlRasterData fdl, DT8_char do_dir)
{

	DT32_int i,j,k;
	PATH_UNIT *p, *p0;

	DT32_long max_dist;
	DT32_long min_dist;
	DT32_long dist;
	DT32_int max_idx, min_idx;
	DT16_short order;
	DT8_char dir = FDL_PATH_HORZ ;

//	FDL_PATH_IsLNear = 1024,
//	FDL_PATH_IsLFar = 2048,
	
	Do_FindnPath(fdl, do_dir);
	
	if(do_dir == FDL_PATH_VERT)
	{
		dir = do_dir;
	}

  	for(i=0; i<fdl->stridcnt; i++)
	{
		if(fdl->stroke_buf[i].len <6)
			continue;
		else{
				p0 = fdl->path_buf+fdl->stroke_buf[i].start;
				for(j=0; j<fdl->stroke_buf[i].len; j++, p0++)
				{
				
					if(p0->dir == dir)
					{
						order = fdl->stroke_buf[i].start+j;
						min_dist = 0x7FFFFFFF;
						max_dist = 0;
						min_idx = -1;
						max_idx = -1;
						p = fdl->path_buf+fdl->stroke_buf[i].start;
						for(k=0; k<fdl->stroke_buf[i].len; k++, p++)
						{
							if(j==k)
								continue;
							if(p->dir == dir && order == p->relation)
							{

									if(dir == FDL_PATH_HORZ )
							{
										if(p0->sy1 > p->sy1){
									dist = p0->sy1 - p->sy1;
										}
										else{
									dist = p->sy1 - p0->sy1;
										}
									}
									else{
										if(p0->sx1 > p->sx1){
											dist = p0->sx1 - p->sx1;
										}
										else{
											dist = p->sx1 - p0->sx1;
										}
									}
									
									
									if(min_dist > dist)
									{
										min_dist = dist;
										min_idx = k;
									}
									if(max_dist < dist)
									{
										max_dist = dist;
										max_idx = k;	
									}

							}else continue;
							;
						}
						if(min_idx!=-1  && max_idx != -1)
						{
							if(min_dist == max_dist)
								continue;
							else
							{
								(fdl->path_buf+max_idx+fdl->stroke_buf[i].start)->lock |= FDL_PATH_IsLFar;
								(fdl->path_buf+min_idx+fdl->stroke_buf[i].start)->lock |= FDL_PATH_IsLNear;
								p0->relation = min_idx+fdl->stroke_buf[i].start;
							}
						}
					}else continue;
				}//for
		}
	}
}





/*---------------------------------------------------------------------------*/
/**** Move this function to the bottom of this file to reduce the stack usage under 1k	****/
/**** Tested by Renesas High-performance Embedded Workshop for SH-2A CPU.				****/
/**** Please keep this func is the most bottom function, and beware of the 3 variables	****/
#ifdef DT_DCWRASTER_STDBOLD						// The bold method in DcwRaster std v1.0.9 (StdBold)
#else
 #define DCW_EASY_BOLD							// Easy and faster bold. (EasyBold)
 #ifdef DT_DCWRASTER_EASYBOLD_METHOD_THINER
  // Nothing to be defined, it will use the New EasyBold method.
  // New EasyBold method, it will be thiner and smoother than original EasyBold method.
 #else
  #define DCW_ORIGIN_METHOD_IN_EASY_BOLD		// Original EasyBold method.
 #endif
#endif
static DT32_int vitalic;  /* Italic for Vertical Writing */
static DT32_int hitalic;  /* Italic for Horizontal Writing or Rotate Vertical Writing */
static DT32_int italic;
DT32_int DrawBitmap(pFdlRasterData fdl)
{
	pFdlGradeData gdata = &(((pDcwWrk)fdl->wrk)->gdata);
	DT32_int x, y, x0, y0, xl, xr, xl2, xr2, last, dx, dy;
	DT32_int w, dw, yt, yb, y2;
	DT16_short *lp, *rp, *lp2, *rp2;
	DT32_int i;

	x0 = fdl->x0;
	y0 = fdl->y0;
	vitalic = fdl->vert && !fdl->rot && (fdl->italic>0);
	hitalic = !vitalic && (fdl->italic>0);
	italic = fdl->italic;

	lp = fdl->LeftBuf;
	rp = fdl->RightBuf;
	last = fdl->RasterCnt - 1;

	switch(fdl->f_edge)
	{
		case FDL_RASTER_DRAW:
			y = fdl->FirstX - y0;
			for(i=0; i<=last; i++,y++,lp++,rp++)
			{
				/* Get Scan Line Coordinate */
				xl = *lp - x0;
				xr = *rp - x0;

				/* Horz. Italic */
				if(hitalic)
				{
					dx = (fdl->ysize - y) * italic / fdl->ysize;
					xl += dx;
					xr += dx;
				}

				/* Add scan line */
				if(fdl->grade)
				{
					if(!vitalic)
					{
						if(!FG_Add(gdata, y, xl, xr))
							return(0);
					} else
					{
						for(x=xl; x<=xr; x++)
						{
							dy = x * italic / fdl->xsize;
							if(!FG_Add(gdata, y+dy, x, x))
								return(0);
						}
					}
				} else
				{
					if(!vitalic)
						DoDrawLine(fdl, y, xl, xr);
					else
					{
						for(x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
						{
							dy = x * italic / fdl->xsize;
							DoDrawDot(fdl, x, y+dy, 0);
						}
					}
				}
			}
			break;

		case FDL_RASTER_CLEAR:
			y = fdl->FirstX - y0;
			for(i=0; i<=last; i++,y++,lp++,rp++)
			{
				/* Get Scan Line Coordinate */
				xl = *lp - x0;
				xr = *rp - x0;

				/* Horz. Italic */
				if(hitalic)
				{
					dx = (fdl->ysize - y) * italic / fdl->ysize;
					xl += dx;
					xr += dx;
				}

				/* Clear scan line */
				if(fdl->grade)
				{
					if(!vitalic)
					{
						if(!FG_Delete(gdata, y, xl, xr))
							return(0);
					} else
					{
						for(x=xl; x<=xr; x++)
						{
							dy = x * italic / fdl->xsize;
							if(!FG_Delete(gdata, y+dy, x, x))
								return(0);
						}
					}
				} else
				{
					if(!vitalic)
						DoClearLine(fdl, y, xl, xr);
					else
					{
						for(x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
						{
							dy = x * italic / fdl->xsize;
							DoDrawDot(fdl, x, y+dy, 1);
						}
					}
				}
			}
			break;
#ifdef DCW_EASY_BOLD
		case FDL_RASTER_BOLD:
		  if(hitalic || vitalic){	// let italic algorithm goes here to match with the draw of FDL_RASTER_DRAW when f_edge==1
			w = fdl->w_edge;
			y = fdl->FirstX - w - y0;

			for(i=-w; i<=last+w; i++,y++)
			{
				/* Get / Calculate Scan Line Coordinate */
				yt = i - w;
				yb = i + w;
				if(yt<0) yt = 0;
				if(yb>last)	yb = last;

				lp2 = lp + yt;
				rp2 = rp + yt;

				for(y2=yt; y2<=yb; y2++,lp2++,rp2++)
				{
					dw = y2 - i;
					if(dw < 0) dw = -dw;
					xl2 = *lp2 - w + dw - x0;
					xr2 = *rp2 + w - dw - x0;

					if(y2 == yt)
					{
						xl = xl2;
						xr = xr2;
					} else
					{
						if(xl2 < xl) xl = xl2;
						if(xr2 > xr) xr = xr2;
					}
				}

				/* Horz. Italic */
				if(hitalic)
				{
					dx = (fdl->ysize - y) * italic / fdl->ysize;
					xl += dx;
					xr += dx;
				}

				/* Add scan line */
				if(fdl->grade)
				{
					if(!vitalic)
					{
						if(!FG_Add(gdata, y, xl, xr))
							return(0);
					} else
					{
						for(x=xl; x<=xr; x++)
						{
							dy = x * italic / fdl->xsize;
							if(!FG_Add(gdata, y+dy, x, x))
								return(0);
						}
					}
				} else
				{
					if(!vitalic)
						DoDrawLine(fdl, y, xl, xr);
					else
					{
						for(x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
						{
							dy = x * italic / fdl->xsize;
							DoDrawDot(fdl, x, y+dy, 0);
						}
					}
				}
			}
		  }else{	// if(hitalic)
			DT32_int j, yp;
			w = fdl->w_edge;		// Assume w_edge is always the same as the integer part of w_edge266.
			// ================================================================
			if(!fdl->grade)						// Jacky_20110509
				yt = -w;
			else
			{
				DT32_int frac;
				DT_f26dot6 w266;
				yt = gdata->yt;
				// Jacky_20110614: Re-explain w_edge266
				//w += (DT32_int)DTF266ToFrac( ((pDcwWrk)fdl->wrk)->attr.w_edge266 )*(fdl->recycle+1) / DTF266_1;
//				frac = DTF266ToFrac( ((pDcwWrk)fdl->wrk)->attr.w_edge266 );
//				if(frac >= DTF266_Half){
//					w = fdl->w_edge - (fdl->recycle+1);
//					w += frac * (fdl->recycle+1) / DTF266_1;
//				}// else ;	// Clips (cuts off) the gray pixels outside the edge

				w266 = ((pDcwWrk)fdl->wrk)->attr.w_edge266;
				if(DTF266ToInt(w266) > DTF266ToFloor(w266)){
					w = fdl->w_edge - (fdl->recycle+1);
				}
				frac = DTF266ToFrac( w266 );
				w += frac * (fdl->recycle+1) / DTF266_1;
			}

			y = fdl->FirstX - y0;
			dw = y - w;
			if(dw < /*gdata->yt*/yt)			// Jacky_20110509
				dw = y - /*gdata->yt*/yt;		// Jacky_20110509
			else dw = w;

			for(i=0; i < dw; i++, y++)
			{
				fdl->LBuf[y] = (DT16_short)0x7FFF;			//32767	// Jacky_20110629 for Hindi
				fdl->RBuf[y] = (DT16_short)0x8000;	//0;	//-32768
			}// end for

			for(i=0; i <= last; i++, lp++, rp++, y++)
			{
				*lp = *lp - w - x0;
				*rp = *rp + w - x0;

				fdl->LBuf[y] = *lp;	//*lp<-fdl->recycle?-fdl->recycle:*lp;
				fdl->RBuf[y] = *rp;
			}// end for

			for(i=0; i < w; i++, y++)
			{
				fdl->LBuf[y] = (DT16_short)0x7FFF;			//32767	// Jacky_20110629 for Hindi
				fdl->RBuf[y] = (DT16_short)0x8000;	//0;	//-32768
			}// end for

			lp = fdl->LeftBuf;
			rp = fdl->RightBuf;
#ifdef DCW_ORIGIN_METHOD_IN_EASY_BOLD
			y = fdl->FirstX - y0 + dw;
			for(i=0; i <= w && y >= /*gdata->yt*/yt + dw; i++, y--)			// Jacky_20110509
			{
				fdl->LBuf[y] = *lp;	//*lp<-fdl->recycle?-fdl->recycle:*lp;
				fdl->RBuf[y] = *rp;
			}// end for
#endif
			y = fdl->FirstX - y0 + dw;
			for(i=0; i <= last; i++, y++, lp++, rp++)
			{
				if(*lp < *(lp-1) || *rp > *(rp-1))
				{
					//*lp = *lp<-fdl->recycle?-fdl->recycle:*lp;
					yp = y-1;
			#ifdef DCW_ORIGIN_METHOD_IN_EASY_BOLD
					for(j=1; j <= w && yp >= 0; j++, yp--)
					{
						if(*lp < fdl->LBuf[yp])
							fdl->LBuf[yp] = *lp;
						if(*rp > fdl->RBuf[yp])
							fdl->RBuf[yp] = *rp;
					}// end for
			#else
					for(j=0; j < w && yp >= 0; j++, yp--)
					{
						if(*lp < fdl->LBuf[yp])
							fdl->LBuf[yp] = *lp + j/2;
						if(*rp > fdl->RBuf[yp])
							fdl->RBuf[yp] = *rp - j/2;
					}// end for
			#endif
				}// end if

				if(*lp < *(lp+1) || *rp > *(rp+1))
				{
					//*lp = *lp<-fdl->recycle?-fdl->recycle:*lp;
					yp = y+1;
					//					for(j=1; j <= w && y+j < fdl->ysize + dw; j++)
			#ifdef DCW_ORIGIN_METHOD_IN_EASY_BOLD
					for(j=1; j <= w; j++, yp++)
					{
						if(*lp < fdl->LBuf[yp])
							fdl->LBuf[yp] = *lp;
						if(*rp > fdl->RBuf[yp])
							fdl->RBuf[yp] = *rp;
					}// end for
			#else
					for(j=0; j < w; j++, yp++)
					{
						if(*lp < fdl->LBuf[yp])
							fdl->LBuf[yp] = *lp + j/2;
						if(*rp > fdl->RBuf[yp])
							fdl->RBuf[yp] = *rp - j/2;
					}// end for
			#endif
				}// end if
			}// end for
#ifdef DCW_ORIGIN_METHOD_IN_EASY_BOLD
			lp = fdl->LeftBuf+last;
			rp = fdl->RightBuf+last;
			y = fdl->FirstX - y0 + last + dw + 1;
			for(i=1; i <= w; i++, y++)
			{
				if(*lp < fdl->LBuf[y])
					fdl->LBuf[y] = *lp; //*lp<-fdl->recycle?-fdl->recycle:*lp;
				if(*rp > fdl->RBuf[y])
					fdl->RBuf[y] = *rp;
			}// end for
#endif
			/* =========================== upload all path ================================= */
			y = fdl->FirstX - y0;
			if(hitalic)
			{
//				DT32_int xval;	// Jacky_20110509	// Marked_by_Jacky_20110628: for Hindi
				if(!fdl->grade)
				{
					for(i=0; i < dw ; i++, y++)
					{
						if(fdl->LBuf[y] < fdl->RBuf[y])
						{
							dx = (fdl->ysize - y) * italic / fdl->ysize;
//							xval = fdl->LBuf[y]+dx;	// Marked_by_Jacky_20110628: for Hindi
//							if(xval<-fdl->w_edge)
//								xval = -fdl->w_edge;
							DoDrawLine(fdl, y-dw, /*xval*/fdl->LBuf[y]+dx, fdl->RBuf[y]+dx);
						}// end if
					}// end for

					for(i=0; i <= last; i++, y++)
					{
						if(fdl->LBuf[y] < fdl->RBuf[y])
						{
							dx = (fdl->ysize - y) * italic / fdl->ysize;
//							xval = fdl->LBuf[y]+dx;	// Marked_by_Jacky_20110628: for Hindi
//							if(xval<-fdl->w_edge)
//								xval = -fdl->w_edge;
							DoDrawLine(fdl, y-dw, /*xval*/fdl->LBuf[y]+dx, fdl->RBuf[y]+dx);
						}// end if
					}// end for

					for(i=0; i < w && y < fdl->ysize+dw+w; i++, y++)
					{
						if(fdl->LBuf[y] < fdl->RBuf[y])
						{
							dx = (fdl->ysize - y) * italic / fdl->ysize;
//							xval = fdl->LBuf[y]+dx;	// Marked_by_Jacky_20110628: for Hindi
//							if(xval<-fdl->w_edge)
//								xval = -fdl->w_edge;
							DoDrawLine(fdl, y-dw, /*xval*/fdl->LBuf[y]+dx, fdl->RBuf[y]+dx);
						}// end if
					}// end for
				}else
				{
					for(i=0; i < dw ; i++, y++)
					{
						if(fdl->LBuf[y] < fdl->RBuf[y])
						{
							dx = (fdl->ysize - y) * italic / fdl->ysize;
//							xval = fdl->LBuf[y]+dx;	// Marked_by_Jacky_20110628: for Hindi
//							if(xval<-fdl->w_edge)
//								xval = -fdl->w_edge;
							if(!FG_Add(gdata, y-dw, /*xval*/fdl->LBuf[y]+dx, fdl->RBuf[y]+dx))
								return (0);
						}// end if
					}// end for

					for(i=0; i <= last; i++, y++)
					{
						dx = (fdl->ysize - y) * italic / fdl->ysize;
//						xval = fdl->LBuf[y]+dx;		// Marked_by_Jacky_20110628: for Hindi
//						if(xval<-fdl->w_edge)
//							xval = -fdl->w_edge;
						if(!FG_Add(gdata, y-dw, /*xval*/fdl->LBuf[y]+dx, fdl->RBuf[y]+dx))
							return (0);
					}// end for

					for(i=0; i < w && y < fdl->ysize+dw+w; i++, y++)
					{
						if(fdl->LBuf[y] < fdl->RBuf[y])
						{
							dx = (fdl->ysize - y) * italic / fdl->ysize;
//							xval = fdl->LBuf[y]+dx;	// Marked_by_Jacky_20110628: for Hindi
//							if(xval<-fdl->w_edge)
//								xval = -fdl->w_edge;
							if(!FG_Add(gdata, y-dw, /*xval*/fdl->LBuf[y]+dx, fdl->RBuf[y]+dx))
								return (0);
						}// end if
					}// end for
				}
			}else
			{
				// Jacky_20110509: Ensure the left point of a scanline won't too small.
//				y = fdl->FirstX - y0;
//				for(i=0; i < dw + last+1 + w; i++, y++)			// Marked_by_Jacky_20110628: for Hindi
//				{
//					if(fdl->LBuf[y] < (DT16_short)-fdl->w_edge)
//						fdl->LBuf[y] = (DT16_short)-fdl->w_edge;
//				}
				
				y = fdl->FirstX - y0;
				if(!fdl->grade)
				{
					for(i=0; i < dw ; i++, y++)
					{
						//						if(fdl->LBuf[y] < fdl->RBuf[y])		// For speed up
						DoDrawLine(fdl, y-dw, fdl->LBuf[y], fdl->RBuf[y]);
					}// end for

					for(i=0; i <= last; i++, y++)
					{
						DoDrawLine(fdl, y-dw, fdl->LBuf[y], fdl->RBuf[y]);
					}// end for

					for(i=0; i < w && y < fdl->ysize+dw+w; i++, y++)
					{
						//						if(fdl->LBuf[y] < fdl->RBuf[y])		// For speed up
						DoDrawLine(fdl, y-dw, fdl->LBuf[y], fdl->RBuf[y]);
					}// end for
				}else
				{
					for(i=0; i < dw ; i++, y++)
					{
						//if(fdl->LBuf[y] < fdl->RBuf[y])		// For speed up
						if(!FG_Add(gdata, y-dw, fdl->LBuf[y], fdl->RBuf[y]))
							return (0);
					}// end for

					for(i=0; i <= last; i++, y++)
					{
						if(!FG_Add(gdata, y-dw, fdl->LBuf[y], fdl->RBuf[y]))
							return (0);
					}// end for

					for(i=0; i < w && y < fdl->ysize+dw+w; i++, y++)
					{
						if(fdl->LBuf[y] < fdl->RBuf[y]){
							if(!FG_Add(gdata, y-dw, fdl->LBuf[y], fdl->RBuf[y]))
								return (0);
						}else break;
					}// end for
				}// end if
			}// end if
		}	// if(hitalic)

			break;
#else	// DCW_EASY_BOLD
	  case FDL_RASTER_BOLD:
			w = fdl->w_edge;		// Assume w_edge is always the same as the integer part of w_edge266.
			// ================================================================
			if(!fdl->grade)						// Jacky_20110509
				yt = -w;
			else
			{
				DT32_int frac;
				DT_f26dot6 w266;
				yt = gdata->yt;
				// Jacky_20110614: Re-explain w_edge266
				//w += (DT32_int)DTF266ToFrac( ((pDcwWrk)fdl->wrk)->attr.w_edge266 )*(fdl->recycle+1) / DTF266_1;
//				frac = DTF266ToFrac( ((pDcwWrk)fdl->wrk)->attr.w_edge266 );
//				if(frac >= DTF266_Half){
//					w = fdl->w_edge - (fdl->recycle+1);
//					w += frac * (fdl->recycle+1) / DTF266_1;
//				}// else ;	// Clips (cuts off) the gray pixels outside the edge

				w266 = ((pDcwWrk)fdl->wrk)->attr.w_edge266;
				if(DTF266ToInt(w266) > DTF266ToFloor(w266)){
					w = fdl->w_edge - (fdl->recycle+1);
				}
				frac = DTF266ToFrac( w266 );
				w += frac * (fdl->recycle+1) / DTF266_1;
			}
		y = fdl->FirstX - w - y0;

		for (i=-w; i<=last+w; i++,y++)
		{
    		/* Get / Calculate Scan Line Coordinate */
		  yt = i - w;
		  yb = i + w;
		  if (yt<0) yt = 0;
		  if (yb>last) yb = last;

		  lp2 = lp + yt;
		  rp2 = rp + yt;

		  for (y2=yt; y2<=yb; y2++,lp2++,rp2++)
		  {
			dw = y2 - i;
			if (dw < 0) dw = -dw;
			xl2 = *lp2 - w + dw - x0;
			xr2 = *rp2 + w - dw - x0;

			if (y2 == yt)
			{
			  xl = xl2;
			  xr = xr2;
			}
			else
			{
			  if (xl2 < xl) xl = xl2;
			  if (xr2 > xr) xr = xr2;
			}
		  }

		  /* Horz. Italic */
		  if (hitalic)
		  {
			dx = (fdl->ysize - y) * italic / fdl->ysize;
			xl += dx;
			xr += dx;
		  }

		  /* Add scan line */
		  if (fdl->grade)
		  {
      		if (!vitalic)
			{
				if (!FG_Add(gdata, y, xl, xr))
  					return 0;
			}
			else
			{
        		for (x=xl; x<=xr; x++)
			  {
          		dy = x * italic / fdl->xsize;
	        		if (!FG_Add(gdata, y+dy, x, x))
  	        			return 0;
			  }
			}
		  }
		  else
		  {
      		if (!vitalic)
        		DoDrawLine(fdl, y, xl, xr);
			else
			{
        		for (x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
				{
          			dy = x * italic / fdl->xsize;
        			DoDrawDot(fdl, x, y+dy, 0);
				}
			}
		  }
		}
		break;
#endif	// DCW_EASY_BOLD
		case FDL_RASTER_RIGHT:
			w = fdl->w_edge;
			y = fdl->FirstX - y0;

			for(i=0; i<=last; i++,y++,lp++,rp++)
			{
				/* Get / Calculate Scan Line Coordinate */
				xl = *lp - x0;
				xr = *rp + w - x0;

				/* Horz. Italic */
				if(hitalic)
				{
					dx = (fdl->ysize - y) * italic / fdl->ysize;
					xl += dx;
					xr += dx;
				}

				/* Add scan line */
				if(fdl->grade)
				{
					if(!vitalic)
					{
						if(!FG_Add(gdata, y, xl, xr))
							return(0);
					} else
					{
						for(x=xl; x<=xr; x++)
						{
							dy = x * italic / fdl->xsize;
							if(!FG_Add(gdata, y+dy, x, x))
								return(0);
						}
					}
				} else
				{
					if(!vitalic)
						DoDrawLine(fdl, y, xl, xr);
					else
					{
						for(x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
						{
							dy = x * italic / fdl->xsize;
							DoDrawDot(fdl, x, y+dy, 0);
						}
					}
				}
			}
			break;

		case FDL_RASTER_DOWN:
			w = fdl->w_edge;
			y = fdl->FirstX - y0;

			for(i=0; i<=last+w; i++,y++)
			{
				/* Get / Calculate Scan Line Coordinate */
				yt = i - w;
				yb = i;
				if(yt<0) yt = 0;
				if(yb>last)	yb = last;

				lp2 = lp + yt;
				rp2 = rp + yt;

				for(y2=yt; y2<=yb; y2++,lp2++,rp2++)
				{
					xl2 = *lp2 - x0;
					xr2 = *rp2 - x0;

					if(y2 == yt)
					{
						xl = xl2;
						xr = xr2;
					} else
					{
						if(xl2 < xl) xl = xl2;
						if(xr2 > xr) xr = xr2;
					}
				}

				/* Horz. Italic */
				if(hitalic)
				{
					dx = (fdl->ysize - y) * italic / fdl->ysize;
					xl += dx;
					xr += dx;
				}

				/* Add scan line */
				if(fdl->grade)
				{
					if(!vitalic)
					{
						if(!FG_Add(gdata, y, xl, xr))
							return(0);
					} else
					{
						for(x=xl; x<=xr; x++)
						{
							dy = x * italic / fdl->xsize;
							if(!FG_Add(gdata, y+dy, x, x))
								return(0);
						}
					}
				} else
				{
					if(!vitalic)
						DoDrawLine(fdl, y, xl, xr);
					else
					{
						for(x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
						{
							dy = x * italic / fdl->xsize;
							DoDrawDot(fdl, x, y+dy, 0);
						}
					}
				}
			}
			break;

		case FDL_RASTER_UP:
			w = fdl->w_edge;
			y = fdl->FirstX - w - y0;

			for(i=-w; i<=last; i++,y++)
			{
				/* Get / Calculate Scan Line Coordinate */
				yt = i;
				yb = i + w;
				if(yt<0) yt = 0;
				if(yb>last)	yb = last;

				lp2 = lp + yt;
				rp2 = rp + yt;

				for(y2=yt; y2<=yb; y2++,lp2++,rp2++)
				{
					xl2 = *lp2 - x0;
					xr2 = *rp2 - x0;

					if(y2 == yt)
					{
						xl = xl2;
						xr = xr2;
					} else
					{
						if(xl2 < xl) xl = xl2;
						if(xr2 > xr) xr = xr2;
					}
				}

				/* Horz. Italic */
				if(hitalic)
				{
					dx = (fdl->ysize - y) * italic / fdl->ysize;
					xl += dx;
					xr += dx;
				}

				/* Add scan line */
				if(fdl->grade)
				{
					if(!vitalic)
					{
						if(!FG_Add(gdata, y, xl, xr))
							return(0);
					} else
					{
						for(x=xl; x<=xr; x++)
						{
							dy = x * italic / fdl->xsize;
							if(!FG_Add(gdata, y+dy, x, x))
								return(0);
						}
					}
				} else
				{
					if(!vitalic)
						DoDrawLine(fdl, y, xl, xr);
					else
					{
						for(x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
						{
							dy = x * italic / fdl->xsize;
							DoDrawDot(fdl, x, y+dy, 0);
						}
					}
				}
			}
			break;

		case FDL_RASTER_RIGHT_DOWN:
			w = fdl->w_edge;
			y = fdl->FirstX - y0;

			for(i=0; i<=last+w; i++,y++)
			{
				/* Get / Calculate Scan Line Coordinate */
				yt = i - w;
				yb = i;
				if(yt<0) yt = 0;
				if(yb>last)	yb = last;

				lp2 = lp + yt;
				rp2 = rp + yt;

				for(y2=yt; y2<=yb; y2++,lp2++,rp2++)
				{
					xl2 = *lp2 - x0;
					xr2 = *rp2 + w - x0;

					if(y2 == yt)
					{
						xl = xl2;
						xr = xr2;
					} else
					{
						if(xl2 < xl) xl = xl2;
						if(xr2 > xr) xr = xr2;
					}
				}

				/* Horz. Italic */
				if(hitalic)
				{
					dx = (fdl->ysize - y) * italic / fdl->ysize;
					xl += dx;
					xr += dx;
				}

				/* Add scan line */
				if(fdl->grade)
				{
					if(!vitalic)
					{
						if(!FG_Add(gdata, y, xl, xr))
							return(0);
					} else
					{
						for(x=xl; x<=xr; x++)
						{
							dy = x * italic / fdl->xsize;
							if(!FG_Add(gdata, y+dy, x, x))
								return(0);
						}
					}
				} else
				{
					if(!vitalic)
						DoDrawLine(fdl, y, xl, xr);
					else
					{
						for(x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
						{
							dy = x * italic / fdl->xsize;
							DoDrawDot(fdl, x, y+dy, 0);
						}
					}
				}
			}
			break;

		case FDL_RASTER_RIGHT_UP:
			w = fdl->w_edge;
			y = fdl->FirstX - w - y0;

			for(i=-w; i<=last; i++,y++)
			{
				/* Get / Calculate Scan Line Coordinate */
				yt = i;
				yb = i + w;
				if(yt<0) yt = 0;
				if(yb>last)	yb = last;

				lp2 = lp + yt;
				rp2 = rp + yt;

				for(y2=yt; y2<=yb; y2++,lp2++,rp2++)
				{
					xl2 = *lp2 - x0;
					xr2 = *rp2 + w - x0;

					if(y2 == yt)
					{
						xl = xl2;
						xr = xr2;
					} else
					{
						if(xl2 < xl) xl = xl2;
						if(xr2 > xr) xr = xr2;
					}
				}

				/* Horz. Italic */
				if(hitalic)
				{
					dx = (fdl->ysize - y) * italic / fdl->ysize;
					xl += dx;
					xr += dx;
				}

				/* Add scan line */
				if(fdl->grade)
				{
					if(!vitalic)
					{
						if(!FG_Add(gdata, y, xl, xr))
							return(0);
					} else
					{
						for(x=xl; x<=xr; x++)
						{
							dy = x * italic / fdl->xsize;
							if(!FG_Add(gdata, y+dy, x, x))
								return(0);
						}
					}
				} else
				{
					if(!vitalic)
						DoDrawLine(fdl, y, xl, xr);
					else
					{
						for(x=xl; x<xr; x++)	// for(x=xl; x<=xr; x++)	// 20110927: Jacky for vert italic of 0x2592
						{
							dy = x * italic / fdl->xsize;
							DoDrawDot(fdl, x, y+dy, 0);
						}
					}
				}
			}
			break;
	}

	return(1);
}


DT_void Do_TOLERANCE_Y(pFdlRasterData fdl)
{
#ifdef TOLERANCE_Y
	DT32_int i, w;
	PATH_UNIT *p, *p1;
	DT32_int ji, dist;

	// For fixed code 0x53F7, 0x8A2D bug. If could verify font data to ensure that never have this case, we could remove those code.
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		p = fdl->path_buf + fdl->stroke_line_order[i];
		if(fdl->stroke_buf[p->strorder].len <=4)
			continue;

		w = (*p->sx03 - *p->sx01);
		if(p->relation >= 0 && (*(fdl->path_buf[p->relation].sy03) - *p->sy01 <= w))			// Only correct horizontal line.
		{
			for(ji=0; ji < fdl->stroke_line_num; ji++)
			{
				if(ji == i) continue;
				
				p1 = fdl->path_buf + fdl->stroke_line_order[ji];

				if(fdl->stroke_buf[p1->strorder].len <=4)
					continue;

				if(IsVLineOverlayX(p, p1))
				{
					dist = *p1->sy01 - *p->sy01;
					if(DT_abs(dist) < TOLERANCE_Y)
					{
						if(*p1->sy01 < *p->sy01)
							Do_MoveStrokeYPath(fdl, fdl->stroke_line_order[ji], *p->sy01);
						if(p1->relation >= 0)
						{
							dist = *(fdl->path_buf[p1->relation].sy01) - *(fdl->path_buf[p->relation].sy01);
							if(DT_abs(dist) < TOLERANCE_Y)
							{
								if(*(fdl->path_buf[p1->relation].sy01) < *(fdl->path_buf[p->relation].sy01))
									Do_MoveStrokeYPath(fdl, p1->relation, *(fdl->path_buf[p->relation].sy01));
							}
						}// end if
					}// end if
				}// end if
			}// end for

		}// end if
	}// end for

#endif // TOLERANCE_Y

}


DT_void Do_TOLERANCE_X(pFdlRasterData fdl)
{
	DT32_int i;
	PATH_UNIT *p, *p1;
	DT32_int ji, dist;

#ifdef TOLERANCE_X
	// For fixed code 0x6FA4, 0x6688 bug. If could verify font data to ensure that never have this case, we could remove those code.
	for(i=0; i < fdl->stroke_line_num; i++)
	{
		p = fdl->path_buf + fdl->stroke_line_order[i];
		for(ji=0; ji < fdl->stroke_line_num; ji++)
		{
			if(ji == i) continue;
			p1 = fdl->path_buf + fdl->stroke_line_order[ji];
			if(fdl->stroke_buf[p1->strorder].stridmap == 44)	// Adjust 0x7AEF:5 would break stroke, actually it doesn't need to adjust.
				continue;
			dist = *p1->sx01 - *p->sx01;
			if(dist !=0)
			{
				if(DT_abs(dist) < TOLERANCE_X)
				{
					Do_MoveStrokeXPath(fdl, fdl->stroke_line_order[ji], *p->sx01);

					if(p->relation >= 0 && p1->relation >= 0)			// Why crash in 0x371A.
					{
						dist = *(fdl->path_buf[p1->relation].sx01) - *(fdl->path_buf[p->relation].sx01);
						if(DT_abs(dist) < TOLERANCE_X)
						{
							Do_MoveStrokeXPath(fdl, p1->relation, *(fdl->path_buf[p->relation].sx01));
						}
					}
					
				}// end if
			}
		}// end for
	}// end for
#endif
}
