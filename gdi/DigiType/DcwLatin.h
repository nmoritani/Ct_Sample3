#ifndef __DCWLATIN_H
#define __DCWLATIN_H

#include "DcwLayout.h"

DT32_int RenderToBuf_Latin(pLayWrk pwrk, DT_void *para);
DT32_int GetSeginfo_Latin(pLayWrk pwrk, Str_Seg *seginfo);
DT32_int CalcPosition_Latin(pLayWrk pwrk, DT_void *para);
DT32_int RenderByPos_Latin(pLayWrk pwrk, DT_void *para);

#endif
