#include "ovgDcw.h"
#include "ovgDcwFdlRaster.h"

#ifndef min
  #define min(n1,n2)  (((n1) < (n2)) ? (n1) : (n2))
  #define max(n1,n2)  (((n1) > (n2)) ? (n1) : (n2))
#endif

#define OulReadStrByte(fdl)    OULFD_ReadStrByte((pODcwWrk)fdl->wrk)
#define OulReadStrShort(fdl)   OULFD_ReadStrShort((pODcwWrk)fdl->wrk)

/* Uses Macro to Speed Up */
#define OulScaling(val, scale)           (val * scale / 256)


static DT_void oulSetValue(pOTFdlRasterData fdl, DT32_int index, DT32_int val);
static DT32_int  oulInterpreter(pOTFdlRasterData fdl);
static DT_void oulGet_WW_Point(pOTFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval);
static DT_void oulGet_MN_Point(pOTFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval);
static DT_void oulGet_WW_XY(pOTFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval);
static DT_void oulGet_MN_XY(pOTFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval);
static DT_void oulAddCurve(pOTFdlRasterData fdl);
static DT32_int  oulCheckPath(pOTFdlRasterData fdl, DT32_int size);
static DT_void oulUpdatePath(pOTFdlRasterData fdl, DT32_int size);
static DT_void oulMakePath(pOTFdlRasterData fdl);

/* FDL Instruction Process Routine */
static DT32_int oulOpENDSTR(pOTFdlRasterData fdl);
static DT32_int oulOpENDSUB(pOTFdlRasterData fdl);
static DT32_int oulOpMOVX(pOTFdlRasterData fdl);
static DT32_int oulOpMOVY(pOTFdlRasterData fdl);
static DT32_int oulOpSx(pOTFdlRasterData fdl);
static DT32_int oulOpLOAD(pOTFdlRasterData fdl);
static DT32_int oulOpXLOAD(pOTFdlRasterData fdl);
static DT32_int oulOpXVnADD(pOTFdlRasterData fdl);
static DT32_int oulOpXVnSUB(pOTFdlRasterData fdl);
static DT32_int oulOpYVnADD(pOTFdlRasterData fdl);
static DT32_int oulOpYVnSUB(pOTFdlRasterData fdl);
static DT32_int oulOpXVnA(pOTFdlRasterData fdl);
static DT32_int oulOpXVnS(pOTFdlRasterData fdl);
static DT32_int oulOpYVnA(pOTFdlRasterData fdl);
static DT32_int oulOpYVnS(pOTFdlRasterData fdl);
static DT32_int oulOpXWnADD(pOTFdlRasterData fdl);
static DT32_int oulOpXWnSUB(pOTFdlRasterData fdl);
static DT32_int oulOpYWnADD(pOTFdlRasterData fdl);
static DT32_int oulOpYWnSUB(pOTFdlRasterData fdl);
static DT32_int oulOpXWnA(pOTFdlRasterData fdl);
static DT32_int oulOpXWnS(pOTFdlRasterData fdl);
static DT32_int oulOpYWnA(pOTFdlRasterData fdl);
static DT32_int oulOpYWnS(pOTFdlRasterData fdl);
static DT32_int oulOpWWSTOR(pOTFdlRasterData fdl);
static DT32_int oulOpMNSTOR(pOTFdlRasterData fdl);
static DT32_int oulOpMNSx00(pOTFdlRasterData fdl);
static DT32_int oulOpMNSx10(pOTFdlRasterData fdl);
static DT32_int oulOpMNCx00(pOTFdlRasterData fdl);
static DT32_int oulOpMNCx10(pOTFdlRasterData fdl);
static DT32_int oulOpMNCx11(pOTFdlRasterData fdl);
static DT32_int oulOpWWSx00(pOTFdlRasterData fdl);
static DT32_int oulOpWWSx10(pOTFdlRasterData fdl);
static DT32_int oulOpWWCx00(pOTFdlRasterData fdl);
static DT32_int oulOpWWCx10(pOTFdlRasterData fdl);
static DT32_int oulOpWWCx11(pOTFdlRasterData fdl);
static DT32_int oulOpWWSTORb(pOTFdlRasterData fdl);
static DT32_int oulOpMNSTORb(pOTFdlRasterData fdl);
static DT32_int oulOpMNSx00b(pOTFdlRasterData fdl);
static DT32_int oulOpMNSx10b(pOTFdlRasterData fdl);
static DT32_int oulOpMNCx00b(pOTFdlRasterData fdl);
static DT32_int oulOpMNCx10b(pOTFdlRasterData fdl);
static DT32_int oulOpMNCx11b(pOTFdlRasterData fdl);
static DT32_int oulOpLMCx11b(pOTFdlRasterData fdl);
static DT32_int oulOpXMCx11b(pOTFdlRasterData fdl);
static DT32_int oulOpWWSx00b(pOTFdlRasterData fdl);
static DT32_int oulOpWWSx10b(pOTFdlRasterData fdl);
static DT32_int oulOpWWCx00b(pOTFdlRasterData fdl);
static DT32_int oulOpWWCx10b(pOTFdlRasterData fdl);
static DT32_int oulOpWWCx11b(pOTFdlRasterData fdl);
static DT32_int oulOpLWCx11b(pOTFdlRasterData fdl);
static DT32_int oulOpXWCx11b(pOTFdlRasterData fdl);
static DT32_int oulOpENDSUBb(pOTFdlRasterData fdl);
static DT32_int oulOpSWFX(pOTFdlRasterData fdl);
static DT32_int oulOpSWFY(pOTFdlRasterData fdl);

/*---------------------------------------------------------------------------*/
DT32_int OFDL_GetFont(pOTFdlRasterData fdl)
{
  DT16_WORD  status;
  DT32_int   i;
  DT32_int   ret = DCWOUL_SUCCESS;

  fdl->Frac  = 1 << 3;
  fdl->Frac2  = 3;

  /* Initial Rel/Val */
  if (fdl->relno == 0)     /* Symbol */
  {
    fdl->Xpoint[0] = fdl->Ypoint[0] = 0;

    //fdl->Xpoint[1] = (256 << fdl->Frac2) - 1;
    //fdl->Ypoint[1] = (256 << fdl->Frac2) - 1;
	fdl->Xpoint[1] = DCWOUL_SCALE2EM(256) - 1;	// 256 * DCWOUL_FDL_FONT_EM / 256 - 1;
    fdl->Ypoint[1] = DCWOUL_SCALE2EM(256) - 1;


    /*  load 01  */
    fdl->MNx1 = fdl->Xpoint[0];
    fdl->MNy1 = fdl->Ypoint[0];
    fdl->MNx2 = fdl->Xpoint[1];
    fdl->MNy2 = fdl->Ypoint[1];
    fdl->Diffx = fdl->MNx2 - fdl->MNx1;
    fdl->Diffy = fdl->MNy2 - fdl->MNy1;

    for ( i=0; i<fdl->valno; i++ )
      oulSetValue(fdl, i, fdl->val[i]);
  }
  else  /* Stroke */
  {
    for ( i=7; i>=0; i-- )
      if (fdl->defval[i] != 0)
        oulSetValue(fdl, i, fdl->defval[i]);

    for ( i=0; i<fdl->relno; i++ )
    {
      //fdl->Xpoint[i] = fdl->rel[i*2]   << fdl->Frac2;
      //fdl->Ypoint[i] = fdl->rel[i*2+1] << fdl->Frac2;
	  fdl->Xpoint[i] = DCWOUL_SCALE2EM(fdl->rel[i*2]);		//fdl->rel[i*2] * DCWOUL_FDL_FONT_EM / 256
      fdl->Ypoint[i] = DCWOUL_SCALE2EM(fdl->rel[i*2+1]);	//fdl->rel[i*2+1] * DCWOUL_FDL_FONT_EM / 256
    }

    for ( i=0; i<fdl->valno; i++ )
      oulSetValue(fdl, i, fdl->val[i]);
  }

  /* Setup Outline buffer */
  fdl->OulPtr[0]  = fdl->OulBuf[0];
  fdl->OulPtr[1]  = fdl->OulBuf[1];

  /* Process FDL data */
  while (fdl->sdatacnt > 0)
  {
    status = (DT16_WORD)oulInterpreter(fdl);
    if (status == OFDL_UNKNOW_OP)
    {
      ret = DCWOUL_BAD_FONTDATA;
      break;
    }

    /* Setup Outline buffer */
    fdl->OulPtr[0]  = fdl->OulBuf[0];
    fdl->OulPtr[1]  = fdl->OulBuf[1];

    if (status == OFDL_END_OF_STR) break;
  }

  return ret;
}
/*---------------------------------------------------------------------------*/
DT_void oulSetValue(pOTFdlRasterData fdl, DT32_int index, DT32_int val)
{
  fdl->Value[index] = val;

  //val = val << fdl->Frac2;
  val = DCWOUL_SCALE2EM(val);
  fdl->HVal[index] = val;
  fdl->WVal[index] = val;
}
/*---------------------------------------------------------------------------*/
/* FDL Instruction Process Routine                                           */
/*---------------------------------------------------------------------------*/
#define  MAX_OP   256

typedef DT32_int (*FdlInst)(pOTFdlRasterData fdl);

static const FdlInst FdlInsts[MAX_OP] =
{
  oulOpMNSx00,  NULL,		  oulOpMNSx10,  oulOpSx,      oulOpMNSx00,  NULL,		  oulOpMNSx10,  oulOpSx,
  oulOpMNCx00,  NULL,		  oulOpMNCx10,  oulOpMNCx11,  oulOpMNCx00,  NULL,		  oulOpMNCx10,  oulOpMNCx11,
  oulOpWWSx00,  NULL,		  oulOpWWSx10,  NULL,		  oulOpWWSx00,  NULL,		  oulOpWWSx10,  NULL,
  oulOpWWCx00,  NULL,		  oulOpWWCx10,  oulOpWWCx11,  oulOpWWCx00,  NULL,		  oulOpWWCx10,  oulOpWWCx11,
  oulOpXWnADD,  oulOpXWnADD,  oulOpXWnADD,  oulOpXWnADD,  oulOpXWnADD,  oulOpXWnADD,  oulOpXWnADD,  oulOpXWnADD,
  oulOpXWnSUB,  oulOpXWnSUB,  oulOpXWnSUB,  oulOpXWnSUB,  oulOpXWnSUB,  oulOpXWnSUB,  oulOpXWnSUB,  oulOpXWnSUB,
  oulOpLOAD,    oulOpXLOAD,   oulOpMOVX,    oulOpMOVY,    oulOpMNSTOR,  oulOpWWSTOR,  oulOpSWFX,    oulOpSWFY,
  NULL,			NULL,		  NULL,			NULL,		  NULL,			NULL,		  NULL,			NULL,
  oulOpYWnADD,  oulOpYWnADD,  oulOpYWnADD,  oulOpYWnADD,  oulOpYWnADD,  oulOpYWnADD,  oulOpYWnADD,  oulOpYWnADD,
  oulOpYWnSUB,  oulOpYWnSUB,  oulOpYWnSUB,  oulOpYWnSUB,  oulOpYWnSUB,  oulOpYWnSUB,  oulOpYWnSUB,  oulOpYWnSUB,
  oulOpXVnADD,  oulOpXVnADD,  oulOpXVnADD,  oulOpXVnADD,  oulOpXVnADD,  oulOpXVnADD,  oulOpXVnADD,  oulOpXVnADD,
  oulOpXVnSUB,  oulOpXVnSUB,  oulOpXVnSUB,  oulOpXVnSUB,  oulOpXVnSUB,  oulOpXVnSUB,  oulOpXVnSUB,  oulOpXVnSUB,
  oulOpYVnADD,  oulOpYVnADD,  oulOpYVnADD,  oulOpYVnADD,  oulOpYVnADD,  oulOpYVnADD,  oulOpYVnADD,  oulOpYVnADD,
  oulOpYVnSUB,  oulOpYVnSUB,  oulOpYVnSUB,  oulOpYVnSUB,  oulOpYVnSUB,  oulOpYVnSUB,  oulOpYVnSUB,  oulOpYVnSUB,
  oulOpENDSUB,  oulOpENDSTR,  NULL,			NULL,		  NULL,			NULL,		  NULL,			NULL,
  oulOpLMCx11b, oulOpLMCx11b, oulOpLWCx11b, oulOpLWCx11b, oulOpXMCx11b, oulOpXMCx11b, oulOpXWCx11b, oulOpXWCx11b,
  oulOpMNSx00b, NULL,		  oulOpMNSx10b, NULL,		  oulOpMNSx00b, NULL,		  oulOpMNSx10b, NULL,
  oulOpMNCx00b, NULL,		  oulOpMNCx10b, oulOpMNCx11b, oulOpMNCx00b, NULL,		  oulOpMNCx10b, oulOpMNCx11b,
  oulOpWWSx00b, NULL,		  oulOpWWSx10b, NULL,		  oulOpWWSx00b, NULL,		  oulOpWWSx10b, NULL,
  oulOpWWCx00b, NULL,		  oulOpWWCx10b, oulOpWWCx11b, oulOpWWCx00b, NULL,		  oulOpWWCx10b, oulOpWWCx11b,
  oulOpXWnA,    oulOpXWnA,    oulOpXWnA,    oulOpXWnA,    oulOpXWnA,    oulOpXWnA,    oulOpXWnA,    oulOpXWnA,
  oulOpXWnS,    oulOpXWnS,    oulOpXWnS,    oulOpXWnS,    oulOpXWnS,    oulOpXWnS,    oulOpXWnS,    oulOpXWnS,
  NULL,			NULL,		  NULL,			NULL,		  oulOpMNSTORb, oulOpWWSTORb, NULL,			NULL,
  NULL,			NULL,		  NULL,			NULL,		  NULL,			NULL,		  NULL,			NULL,
  oulOpYWnA,    oulOpYWnA,    oulOpYWnA,    oulOpYWnA,    oulOpYWnA,    oulOpYWnA,    oulOpYWnA,    oulOpYWnA,
  oulOpYWnS,    oulOpYWnS,    oulOpYWnS,    oulOpYWnS,    oulOpYWnS,    oulOpYWnS,    oulOpYWnS,    oulOpYWnS,
  oulOpXVnA,    oulOpXVnA,    oulOpXVnA,    oulOpXVnA,    oulOpXVnA,    oulOpXVnA,    oulOpXVnA,    oulOpXVnA,
  oulOpXVnS,    oulOpXVnS,    oulOpXVnS,    oulOpXVnS,    oulOpXVnS,    oulOpXVnS,    oulOpXVnS,    oulOpXVnS,
  oulOpYVnA,    oulOpYVnA,    oulOpYVnA,    oulOpYVnA,    oulOpYVnA,    oulOpYVnA,    oulOpYVnA,    oulOpYVnA,
  oulOpYVnS,    oulOpYVnS,    oulOpYVnS,    oulOpYVnS,    oulOpYVnS,    oulOpYVnS,    oulOpYVnS,    oulOpYVnS,
  oulOpENDSUBb, NULL,		  NULL,			NULL,		  NULL,			NULL,		  NULL,			NULL,
  NULL,			NULL,		  NULL,			NULL,		  NULL,			NULL,		  NULL,			NULL
};


/*---------------------------------------------------------------------------*/
DT32_int  oulInterpreter(pOTFdlRasterData fdl)
{
  DT8_BYTE reg;
  FdlInst Inst;
  DT32_int ret;

  do
  {
    /* Get Instruction Operation Code */
    fdl->op = (DT8_BYTE)OulReadStrByte(fdl);

    /* Get Instruction Source/Destination */
    reg = (DT8_BYTE)OulReadStrByte(fdl);
    fdl->xhead = fdl->yhead = reg >> 4;
    fdl->xtail = fdl->ytail = reg & 0x0f;

    /* Get Instruction Process Routine */
    Inst = FdlInsts[fdl->op];
    if (Inst != NULL)
    {
      /* Execute Instruction */
      ret = Inst(fdl);
      if (ret != 0) return ret;
    }
    else
      return OFDL_UNKNOW_OP;
  } while (fdl->sdatacnt > 0);

  oulMakePath(fdl);
  return OFDL_END_OF_STR;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpENDSTR(pOTFdlRasterData fdl)
{
  oulMakePath(fdl);
  return OFDL_END_OF_STR;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpENDSUB(pOTFdlRasterData fdl)
{
  oulMakePath(fdl);
  return OFDL_END_OF_SUB;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMOVX(pOTFdlRasterData fdl)
{
  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead];
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMOVY(pOTFdlRasterData fdl)
{
  fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead];
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpSx(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oSL;
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpLOAD(pOTFdlRasterData fdl)
{
  fdl->MNx1 = fdl->Xpoint[fdl->xhead];
  fdl->MNy1 = fdl->Ypoint[fdl->yhead];
  fdl->MNx2 = fdl->Xpoint[fdl->xtail];
  fdl->MNy2 = fdl->Ypoint[fdl->ytail];
  fdl->Diffx = fdl->MNx2 - fdl->MNx1;
  fdl->Diffy = fdl->MNy2 - fdl->MNy1;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXLOAD(pOTFdlRasterData fdl)
{
  fdl->MNx1 = fdl->Xpoint[fdl->xhead];
  fdl->MNy1 = fdl->Ypoint[fdl->ytail];
  fdl->MNx2 = fdl->Xpoint[fdl->xtail];
  fdl->MNy2 = fdl->Ypoint[fdl->yhead];
  fdl->Diffx = fdl->MNx2 - fdl->MNx1;
  fdl->Diffy = fdl->MNy2 - fdl->MNy1;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXVnADD(pOTFdlRasterData fdl)
{
  DT32_int rate, Vn;

  rate = OulReadStrShort(fdl);

  Vn = OulScaling(fdl->HVal[fdl->op - oXV0ADD], rate);
  
  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] + Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXVnSUB(pOTFdlRasterData fdl)
{
  DT32_int rate, Vn;

  rate = OulReadStrShort(fdl);

  Vn = OulScaling(fdl->HVal[fdl->op - oXV0SUB], rate);
  
  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] - Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpYVnADD(pOTFdlRasterData fdl)
{
  DT32_int rate, Vn;

  rate = OulReadStrShort(fdl);

  Vn = OulScaling(fdl->WVal[fdl->op - oYV0ADD], rate);
  
  fdl->Ypoint[fdl->xtail] = fdl->Ypoint[fdl->xhead] + Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpYVnSUB(pOTFdlRasterData fdl)
{
  DT32_int rate, Vn;

  rate = OulReadStrShort(fdl);

  Vn = OulScaling(fdl->WVal[fdl->op - oYV0SUB], rate);
  
  fdl->Ypoint[fdl->xtail] = fdl->Ypoint[fdl->xhead] - Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXVnA(pOTFdlRasterData fdl)
{
  DT32_int Vn;

  #ifdef FDL_WEIGHT
  Vn = OulScaling(fdl->HVal[fdl->op - oXV0A], fdl->WeightX);
  #else
  Vn = fdl->HVal[fdl->op - oXV0A];
  #endif

  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] + Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXVnS(pOTFdlRasterData fdl)
{
  DT32_int Vn;

  #ifdef FDL_WEIGHT
  Vn = OulScaling(fdl->HVal[fdl->op - oXV0S], fdl->WeightX);
  #else
  Vn = fdl->HVal[fdl->op - oXV0S];
  #endif

  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] - Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpYVnA(pOTFdlRasterData fdl)
{
  DT32_int Vn;

  #ifdef FDL_WEIGHT
  Vn = OulScaling(fdl->WVal[fdl->op - oYV0A], fdl->WeightY);
  #else
  Vn = fdl->WVal[fdl->op - oYV0A];
  #endif

  fdl->Ypoint[fdl->xtail] = fdl->Ypoint[fdl->xhead] + Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpYVnS(pOTFdlRasterData fdl)
{
  DT32_int Vn;

  #ifdef FDL_WEIGHT
  Vn = OulScaling(fdl->WVal[fdl->op - oYV0S], fdl->WeightY);
  #else
  Vn = fdl->WVal[fdl->op - oYV0S];
  #endif

  fdl->Ypoint[fdl->xtail] = fdl->Ypoint[fdl->xhead] - Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXWnADD(pOTFdlRasterData fdl)
{
  DT32_int idx, rate, factor, Vn;

  idx = fdl->op - oXW0ADD;
  rate   = OulReadStrShort(fdl);
  factor = OulReadStrShort(fdl);
  Vn = OulScaling(fdl->HVal[idx], rate);

  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] + Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXWnSUB(pOTFdlRasterData fdl)
{
  DT32_int idx, rate, factor, Vn;

  idx = fdl->op - oXW0SUB;
  rate   = OulReadStrShort(fdl);
  factor = OulReadStrShort(fdl);
  Vn = OulScaling(fdl->HVal[idx], rate);

  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] - Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpYWnADD(pOTFdlRasterData fdl)
{
  DT32_int idx, rate, factor, Vn;

  idx = fdl->op - oYW0ADD;
  rate   = OulReadStrShort(fdl);
  factor = OulReadStrShort(fdl);
  Vn = OulScaling(fdl->WVal[idx], rate);

  fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead] + Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpYWnSUB(pOTFdlRasterData fdl)
{
  DT32_int idx, rate, factor, Vn;

  idx = fdl->op - oYW0SUB;
  rate   = OulReadStrShort(fdl);
  factor = OulReadStrShort(fdl);
  Vn = OulScaling(fdl->WVal[idx], rate);

  fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead] - Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXWnA(pOTFdlRasterData fdl)
{
  DT32_int idx, factor, Vn;

  idx = fdl->op - oXW0A;
  factor = OulReadStrShort(fdl);
  Vn = fdl->WVal[idx];

  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] + Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXWnS(pOTFdlRasterData fdl)
{
  DT32_int idx, factor, Vn;

  idx = fdl->op - oXW0S;
  factor = OulReadStrShort(fdl);
  Vn = fdl->HVal[idx];

  fdl->Xpoint[fdl->xtail] = fdl->Xpoint[fdl->xhead] - Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpYWnA(pOTFdlRasterData fdl)
{
  DT32_int idx, factor, Vn;

  idx = fdl->op - oYW0A;
  factor = OulReadStrShort(fdl);
  Vn = fdl->WVal[idx];

  fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead] + Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpYWnS(pOTFdlRasterData fdl)
{
  DT32_int idx, factor, Vn;

  idx = fdl->op - oYW0S;
  factor = OulReadStrShort(fdl);
  Vn = fdl->WVal[idx];

  fdl->Ypoint[fdl->ytail] = fdl->Ypoint[fdl->yhead] - Vn;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWSTOR(pOTFdlRasterData fdl)
{
  oulGet_WW_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNSTOR(pOTFdlRasterData fdl)
{
  oulGet_MN_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNSx00(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oMNSL00;
  oulGet_MN_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  oulGet_MN_Point(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNSx10(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oMNSL10;
  oulGet_MN_Point(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNCx00(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oMNCL00;
  mncnt = OulReadStrShort(fdl) - 1;
  oulGet_MN_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_MN_Point(fdl, &fdl->sx2, &fdl->sy2);
    oulGet_MN_Point(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
    mncnt -= 2;
    if (mncnt<=0) break;
  } while(1);
  fdl->Xpoint[fdl->xtail] = fdl->sx3;
  fdl->Ypoint[fdl->ytail] = fdl->sy3;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNCx10(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oMNCL10;
  mncnt = OulReadStrShort(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_MN_Point(fdl, &fdl->sx2, &fdl->sy2);
    oulGet_MN_Point(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
    mncnt -= 2;
    if (mncnt<=0) break;
  } while(1);
  fdl->Xpoint[fdl->xtail] = fdl->sx3;
  fdl->Ypoint[fdl->ytail] = fdl->sy3;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNCx11(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oMNCL11;
  mncnt = OulReadStrShort(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_MN_Point(fdl, &fdl->sx2, &fdl->sy2);
    mncnt -= 2;
    if (mncnt<=0) break;
    oulGet_MN_Point(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
  } while(1);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWSx00(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oWWSL00;
  oulGet_WW_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  oulGet_WW_Point(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWSx10(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oWWSL10;
  oulGet_WW_Point(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->xtail];
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWCx00(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oWWCL00;
  mncnt = OulReadStrShort(fdl) - 1;
  oulGet_WW_Point(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_WW_Point(fdl, &fdl->sx2, &fdl->sy2);
    oulGet_WW_Point(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
    mncnt -= 2;
    if (mncnt<=0) break;
  } while(1);
  fdl->Xpoint[fdl->xtail] = fdl->sx3;
  fdl->Ypoint[fdl->ytail] = fdl->sy3;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWCx10(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oWWCL10;
  mncnt = OulReadStrShort(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
     oulGet_WW_Point(fdl, &fdl->sx2, &fdl->sy2);
     oulGet_WW_Point(fdl, &fdl->sx3, &fdl->sy3);
     x3buf = fdl->sx3;
     y3buf = fdl->sy3;
     oulAddCurve(fdl);
     fdl->sx3 = fdl->sx1 = x3buf;
     fdl->sy3 = fdl->sy1 = y3buf;
     mncnt -= 2;
     if (mncnt<=0) break;
  } while(1);
  fdl->Xpoint[fdl->xtail] = fdl->sx3;
  fdl->Ypoint[fdl->ytail] = fdl->sy3;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWCx11(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oWWCL11;
  mncnt = OulReadStrShort(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_WW_Point(fdl, &fdl->sx2, &fdl->sy2);
    mncnt -= 2;
    if (mncnt<=0) break;
    oulGet_WW_Point(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
  } while(1);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWSTORb(pOTFdlRasterData fdl)
{
  oulGet_WW_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNSTORb(pOTFdlRasterData fdl)
{
  oulGet_MN_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNSx00b(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oMNSL00b;
  oulGet_MN_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  oulGet_MN_XY(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNSx10b(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oMNSL10b;
  oulGet_MN_XY(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNCx00b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oMNCL00b;
  //mncnt = OulReadStrByte(fdl) - 1;
  mncnt = OulReadStrByte(fdl);	mncnt -= 1;
  oulGet_MN_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
    oulGet_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
    mncnt -= 2;
    if (mncnt<=0) break;
  } while(1);
  fdl->Xpoint[fdl->xtail] = fdl->sx3;
  fdl->Ypoint[fdl->ytail] = fdl->sy3;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNCx10b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oMNCL10b;
  mncnt = OulReadStrByte(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
    oulGet_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
    mncnt -= 2;
    if (mncnt<=0) break;
  } while(1);
  fdl->Xpoint[fdl->xtail] = fdl->sx3;
  fdl->Ypoint[fdl->ytail] = fdl->sy3;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpMNCx11b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oMNCL11b;
  mncnt = OulReadStrByte(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
    mncnt -= 2;
    if (mncnt<=0) break;
    oulGet_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
  } while(1);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpLMCx11b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->MNx1 = fdl->Xpoint[fdl->xhead];
  fdl->MNy1 = fdl->Ypoint[fdl->yhead];
  fdl->MNx2 = fdl->Xpoint[fdl->xtail];
  fdl->MNy2 = fdl->Ypoint[fdl->ytail];
  fdl->Diffx = fdl->MNx2 - fdl->MNx1;
  fdl->Diffy = fdl->MNy2 - fdl->MNy1;

  fdl->isLeft = fdl->op==oLMCL11b;
  mncnt = OulReadStrByte(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
    mncnt -= 2;
    if (mncnt<=0) break;
    oulGet_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
  } while(1);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXMCx11b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->MNx1 = fdl->Xpoint[fdl->xhead];
  fdl->MNy1 = fdl->Ypoint[fdl->ytail];
  fdl->MNx2 = fdl->Xpoint[fdl->xtail];
  fdl->MNy2 = fdl->Ypoint[fdl->yhead];
  fdl->Diffx = fdl->MNx2 - fdl->MNx1;
  fdl->Diffy = fdl->MNy2 - fdl->MNy1;

  fdl->isLeft = fdl->op==oXMCL11b;
  mncnt = OulReadStrByte(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_MN_XY(fdl, &fdl->sx2, &fdl->sy2);
    mncnt -= 2;
    if (mncnt<=0) break;
    oulGet_MN_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
  } while(1);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWSx00b(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oWWSL00b;
  oulGet_WW_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  oulGet_WW_XY(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWSx10b(pOTFdlRasterData fdl)
{
  fdl->isLeft = fdl->op==oWWSL10b;
  oulGet_WW_XY(fdl, &fdl->Xpoint[fdl->xtail], &fdl->Ypoint[fdl->xtail]);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->xtail];
  fdl->sx1 = fdl->sx2 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->sy2 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 0;
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWCx00b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oWWCL00b;
  //mncnt = OulReadStrByte(fdl) - 1;
  mncnt = OulReadStrByte(fdl);	mncnt -= 1;
  oulGet_WW_XY(fdl, &fdl->Xpoint[fdl->xhead], &fdl->Ypoint[fdl->xhead]);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
    oulGet_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
    mncnt -= 2;
    if (mncnt<=0) break;
  } while(1);
  fdl->Xpoint[fdl->xtail] = fdl->sx3;
  fdl->Ypoint[fdl->ytail] = fdl->sy3;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWCx10b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oWWCL10b;
  mncnt = OulReadStrByte(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
    oulGet_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
    mncnt -= 2;
    if (mncnt<=0) break;
  } while(1);
  fdl->Xpoint[fdl->xtail] = fdl->sx3;
  fdl->Ypoint[fdl->ytail] = fdl->sy3;
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpWWCx11b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->isLeft = fdl->op==oWWCL11b;
  mncnt = OulReadStrByte(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
    mncnt -= 2;
    if (mncnt<=0) break;
    oulGet_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
  } while(1);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpLWCx11b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->MNx1 = fdl->Xpoint[fdl->xhead];
  fdl->MNy1 = fdl->Ypoint[fdl->yhead];
  fdl->MNx2 = fdl->Xpoint[fdl->xtail];
  fdl->MNy2 = fdl->Ypoint[fdl->ytail];
  fdl->Diffx = fdl->MNx2 - fdl->MNx1;
  fdl->Diffy = fdl->MNy2 - fdl->MNy1;

  fdl->isLeft = fdl->op==oLWCL11b;
  mncnt = OulReadStrByte(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
    mncnt -= 2;
    if (mncnt<=0) break;
    oulGet_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
  } while(1);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpXWCx11b(pOTFdlRasterData fdl)
{
  DT32_int mncnt, x3buf, y3buf;

  fdl->MNx1 = fdl->Xpoint[fdl->xhead];
  fdl->MNy1 = fdl->Ypoint[fdl->ytail];
  fdl->MNx2 = fdl->Xpoint[fdl->xtail];
  fdl->MNy2 = fdl->Ypoint[fdl->yhead];
  fdl->Diffx = fdl->MNx2 - fdl->MNx1;
  fdl->Diffy = fdl->MNy2 - fdl->MNy1;

  fdl->isLeft = fdl->op==oXWCL11b;
  mncnt = OulReadStrByte(fdl);
  fdl->sx1 = fdl->Xpoint[fdl->xhead];
  fdl->sy1 = fdl->Ypoint[fdl->yhead];
  fdl->isCurve = 1;
  do
  {
    oulGet_WW_XY(fdl, &fdl->sx2, &fdl->sy2);
    mncnt -= 2;
    if (mncnt<=0) break;
    oulGet_WW_XY(fdl, &fdl->sx3, &fdl->sy3);
    x3buf = fdl->sx3;
    y3buf = fdl->sy3;
    oulAddCurve(fdl);
    fdl->sx3 = fdl->sx1 = x3buf;
    fdl->sy3 = fdl->sy1 = y3buf;
  } while(1);
  fdl->sx3 = fdl->Xpoint[fdl->xtail];
  fdl->sy3 = fdl->Ypoint[fdl->ytail];
  oulAddCurve(fdl);
  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpENDSUBb(pOTFdlRasterData fdl)
{
  fdl->sdatacnt++;
  fdl->sdataofs--;
  fdl->sx1 = -1;
  oulAddCurve(fdl);
  return OFDL_END_OF_SUB;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpSWFX(pOTFdlRasterData fdl)
{
  #ifdef FDL_WEIGHT
  if (fdl->WeightX0 != 256)
    fdl->WeightX = (unsigned)(((DT32_long)fdl->WeightX0 * fdl->Value[fdl->xhead]) >> 7);
  #endif

  return 0;
}
/*---------------------------------------------------------------------------*/
DT32_int oulOpSWFY(pOTFdlRasterData fdl)
{
  #ifdef FDL_WEIGHT
  if (fdl->WeightY0 != 256)
    fdl->WeightY = (unsigned)(((DT32_long)fdl->WeightY0 * fdl->Value[fdl->xhead]) >> 7);
  #endif

  return 0;
}
/*---------------------------------------------------------------------------*/
DT_void oulGet_WW_Point(pOTFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval)
{
  *Xval = fdl->MNx1 + OulScaling(OulReadStrShort(fdl), fdl->Diffx);
  *Yval = fdl->MNy1 + OulScaling(OulReadStrShort(fdl), fdl->Diffy);
}
/*---------------------------------------------------------------------------*/
DT_void oulGet_MN_Point(pOTFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval)
{
   DT32_int mx = OulReadStrShort(fdl);
   DT32_int ny = OulReadStrShort(fdl);

   *Xval = fdl->MNx1 + (((DT32_long)mx * fdl->Diffx - (DT32_long)ny * fdl->Diffy) / 256);
   *Yval = fdl->MNy1 + (((DT32_long)ny * fdl->Diffx + (DT32_long)mx * fdl->Diffy) / 256);
}
/*---------------------------------------------------------------------------*/
DT_void oulGet_WW_XY(pOTFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval)
{
   DT32_int x, y;

   x = OulReadStrByte(fdl);
   y = OulReadStrByte(fdl);

   if (x==255) x = 256;
   if (y==255) y = 256;

   *Xval = fdl->MNx1 + OulScaling(x, fdl->Diffx);
   *Yval = fdl->MNy1 + OulScaling(y, fdl->Diffy);
}
/*---------------------------------------------------------------------------*/
DT_void oulGet_MN_XY(pOTFdlRasterData fdl, DT32_long *Xval, DT32_long *Yval)
{
   DT32_int mx, ny;

   mx = OulReadStrByte(fdl);
   ny = OulReadStrByte(fdl);

   if (mx==255) mx = 256;
   if (ny==255) ny = 256;

   *Xval = fdl->MNx1 + (((DT32_long)mx * fdl->Diffx - (DT32_long)ny * fdl->Diffy) / 256);
   *Yval = fdl->MNy1 + (((DT32_long)ny * fdl->Diffx + (DT32_long)mx * fdl->Diffy) / 256);
}
#ifdef DT_REAL_STRAIGHT_LINE_FDL_USED
/*---------------------------------------------------------------------------*/
/* according to FDL data, no need to convert curve back to line. */
DT_void oulAddCurve(pOTFdlRasterData fdl)
{
  DT32_int ofs, dx, dy;
  DT16_short *ptr;

  /* 2007-12-07 Radical (Shift for Symbol in Radical) */
  if (fdl->shiftx != 0)
  {
    //ofs = fdl->shiftx << fdl->Frac2;
	ofs = DCWOUL_SCALE2EM(fdl->shiftx);  

    fdl->sy1 += ofs;
    fdl->sy2 += ofs;
    fdl->sy3 += ofs;
  }

  if (fdl->shifty != 0)
  {
    //ofs = fdl->shifty << fdl->Frac2;
	ofs = DCWOUL_SCALE2EM(fdl->shifty);

    fdl->sx1 += ofs;
    fdl->sx2 += ofs;
    fdl->sx3 += ofs;
  }
  /* 2007-12-07 Radical */

  /* Add Curve/Line to Outline buffer */
  ptr = fdl->OulPtr[fdl->isLeft];
  dx = fdl->x0;
  dy = fdl->y0;
  
  *ptr++ = (DT16_short)(fdl->sy1 - dx);
  *ptr++ = (DT16_short)(fdl->sx1 - dy);
  if (fdl->isCurve)
  {
    *ptr++ = (DT16_short)(fdl->sy2 - dx);
    *ptr++ = (DT16_short)(fdl->sx2 - dy);
  }
  else
  {
    *ptr++ = -1;
    *ptr++ = -1;
  }
  *ptr++ = (DT16_short)(fdl->sy3 - dx);
  *ptr++ = (DT16_short)(fdl->sx3 - dy);

  fdl->OulPtr[fdl->isLeft] = ptr;
}
#else
/* check FDL data if it needs to convert curve back to line. */
DT_void oulAddCurve(pOTFdlRasterData fdl)
{
  DT32_int ofs, dx, dy, isCurve;
  DT16_short *ptr;

  /* 2007-12-07 Radical (Shift for Symbol in Radical) */
  if (fdl->shiftx != 0)
  {
    //ofs = fdl->shiftx << fdl->Frac2;
	ofs = DCWOUL_SCALE2EM(fdl->shiftx);

    fdl->sy1 += ofs;
    fdl->sy2 += ofs;
    fdl->sy3 += ofs;
  }

  if (fdl->shifty != 0)
  {
    //ofs = fdl->shifty << fdl->Frac2;
	ofs = DCWOUL_SCALE2EM(fdl->shifty);

    fdl->sx1 += ofs;
    fdl->sx2 += ofs;
    fdl->sx3 += ofs;
  }
  /* 2007-12-07 Radical */

  /* Add Curve/Line to Outline buffer */
  ptr = fdl->OulPtr[fdl->isLeft];
  dx = fdl->x0;
  dy = fdl->y0;

 /* 2011-08-31: Start *//* for symbol fonts that had no lines but only curves. */
 if (fdl->isCurve)
 {
   if ((fdl->sx2 == fdl->sx1) && (fdl->sy2 == fdl->sy1) ||
       (fdl->sx2 == fdl->sx3) && (fdl->sy2 == fdl->sy3))      
     isCurve = 0;
   else
     isCurve = 1;
 }
 else
   isCurve = 0;
 /* 2011-08-31: End */

  *ptr++ = (DT16_short)(fdl->sy1 - dx);
  *ptr++ = (DT16_short)(fdl->sx1 - dy);

  if (isCurve)   /* 2011-08-31 */
 //  if (fdl->isCurve)
  {
    *ptr++ = (DT16_short)(fdl->sy2 - dx);
    *ptr++ = (DT16_short)(fdl->sx2 - dy);
  }
  else
  {
    *ptr++ = -1;
    *ptr++ = -1;
  }
  *ptr++ = (DT16_short)(fdl->sy3 - dx);
  *ptr++ = (DT16_short)(fdl->sx3 - dy);

  fdl->OulPtr[fdl->isLeft] = ptr;
}
#endif
/*---------------------------------------------------------------------------*/
DT32_int oulCheckPath(pOTFdlRasterData fdl, DT32_int size)
{
  return (fdl->pathsize+size) <= fdl->pathmax;
}
/*---------------------------------------------------------------------------*/
DT_void oulUpdatePath(pOTFdlRasterData fdl, DT32_int size)
{
  fdl->pathsize += size;
}
/*---------------------------------------------------------------------------*/
DT_void oulMakePath(pOTFdlRasterData fdl)
{
  DT32_int oulCnt[2];
  DT16_short *ptr;
  DT16_short x1, y1, x2, y2, x3, y3;
  DT32_int isLeft, isCurve, i;
  DT32_int opCnt, xyCnt;
  DT16_short *startPath;

  oulCnt[0] = (fdl->OulPtr[0] - fdl->OulBuf[0]) / 6;
  oulCnt[1] = (fdl->OulPtr[1] - fdl->OulBuf[1]) / 6;
  if ((oulCnt[0]==0) || (oulCnt[1]==0)) return;

  /* Save Op/XY Count */
  opCnt = xyCnt = 0;
  if (oulCheckPath(fdl, 2))
  {
    startPath = fdl->path;
    *fdl->path++ = opCnt;   
    *fdl->path++ = xyCnt;   
  }
  else
    startPath = NULL;
  oulUpdatePath(fdl, 2);  

  /* Process Right/Left segment */
  for (isLeft=0; isLeft<=1; isLeft++)
  {
    if (isLeft)
      ptr = fdl->OulBuf[isLeft] + oulCnt[isLeft] * 6 - 1;
    else
      ptr = fdl->OulBuf[isLeft];

    for (i=0; i<oulCnt[isLeft]; i++)
    {
      /* Get Curve/Line Coordinate */
      if (isLeft)
      {
        y1 = *ptr--;
        x1 = *ptr--;
        y2 = *ptr--;
        x2 = *ptr--;
        y3 = *ptr--;
        x3 = *ptr--;
      }
      else
      {
        x1 = *ptr++;
        y1 = *ptr++;
        x2 = *ptr++;
        y2 = *ptr++;
        x3 = *ptr++;
        y3 = *ptr++;
      }
      isCurve = (x2!=-1) && (y2!=-1);

      /* MoveTo */
      if (i==0 && !isLeft)  
      { 
        if (oulCheckPath(fdl, 3))
        {
          *fdl->path++ = DCWOUL_MOVETO;   
          if (!fdl->rot)
          {
            *fdl->path++ = x1;   
            *fdl->path++ = y1;   
          }
          else
          {
            *fdl->path++ = DCWOUL_FDL_FONT_EM - y1;   
            *fdl->path++ = x1;   
          }
        }
        oulUpdatePath(fdl, 3);
        opCnt++;
        xyCnt++;
      }

      if (isCurve)
      { /* BezierTo */
        if (oulCheckPath(fdl, 5))
        {
          *fdl->path++ = DCWOUL_BEZIERTO;   
          if (!fdl->rot)
          {
            *fdl->path++ = x2;   
            *fdl->path++ = y2;   
            *fdl->path++ = x3;   
            *fdl->path++ = y3;   
          }
          else
          {
            *fdl->path++ = DCWOUL_FDL_FONT_EM - y2;   
            *fdl->path++ = x2;   
            *fdl->path++ = DCWOUL_FDL_FONT_EM - y3;   
            *fdl->path++ = x3;   
          }
        }
        oulUpdatePath(fdl, 5);  
        opCnt++;
        xyCnt += 2;
      }
      else
      { /* LineTo */
        if (oulCheckPath(fdl, 3))
        {
          *fdl->path++ = DCWOUL_LINETO;   
          if (!fdl->rot)
          {
            *fdl->path++ = x3;   
            *fdl->path++ = y3;   
          }
          else
          {
            *fdl->path++ = DCWOUL_FDL_FONT_EM - y3;   
            *fdl->path++ = x3;   
          }
        }
        oulUpdatePath(fdl, 3);  
        opCnt++;
        xyCnt++;
      }
    }
  }

  /* ClosePath */
  if (oulCheckPath(fdl, 1))
  {
    *fdl->path++ = DCWOUL_CLOSEPATH;   
  }
  oulUpdatePath(fdl, 1);  
  opCnt++;

  /* Update Op/XY Count */
  if (startPath)
  {
    *startPath++ = opCnt;
    *startPath   = xyCnt;
  }
}
/*---------------------------------------------------------------------------*/
