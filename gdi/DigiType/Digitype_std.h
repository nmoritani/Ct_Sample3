#ifndef __DIGITYPE_STD_H
#define __DIGITYPE_STD_H

#include "DcwApi.h"

typedef struct _DcwRaster_Attr
{
	DT_void			*pwrk;
	DCW_AttrData	attr;
}DcwRaster_Attr, *pDcwRaster_Attr;

#define RAS_ESTIMATE_DEFT_WKMEM		(0x00)
#define RAS_ESTIMATE_BASE_WKMEM		(0x01)
#define RAS_ESTIMATE_GRAD_WKMEM		(0x02)

//#define RAS_DISABLE_SCALEFONT_FOR_DEBUG		// comment this line when you don't need to scale font.

#define RAS_NOT_SCALE				0
#define RAS_SCALE_BY_XYSCALERATIO	0x0001	// scale by sizey when hori; by sizex when vert.
#define RAS_SCALE_BY_RATIO_FILEWIDE	0x0002
#define RAS_SCALE_BY_CODERANGE		0x0004
#define RAS_SCALE_BY_RASSCALERATIO	0x0008	// scale by sizex & sizey no matter hori or vert.
#define RAS_SCALE_BY_BINSCALERATIO	0x0010	// scale by sizex & sizey no matter hori or vert.

// option for DCW_GetAw_1
#define RAS_OPTION_EXIST			1
#define RAS_OPTION_GETAW			2

/* Functions for get glyph's info. */
DT32_int ras_EstimateWkMem(DT32_int sizex, DT32_int sizey, DT32_int grade, DT32_int option);
DT32_int ras_initFont ( DT_void *pattr,DT8_char *fontdata, DT32_long fWkMemsize, DT8_char *fWkMem, DT_void *pwrk/*, DT32_int sizeX, DT32_int sizeY, DT32_int mode*/);
DT32_int ras_getCharbmp(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int bmpw, DT32_int bmph, DT32_int x0, DT32_int y0, DT32_int xbytes, DT8_uchar *bmp, DT_void *op, DT32_int mode);
DT32_int ras_chkGlyphExist( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int ras_getAwidth( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int ras_getAwidth2(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy);
DT32_int ras_getAheight( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int ras_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int ras_getLogt( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int ras_getHeight( DT_void *pattr );
DT32_int ras_getWidth( DT_void *pattr );
DT32_int ras_getExten ( DT_void *pattr );
DT32_int ras_getAexten( DT_void *pattr, DT16_ushort ch );
DT32_int ras_getVexten( DT_void *pattr, DT16_ushort ch );
DT32_int ras_getEdge( DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r );
DT32_int ras_getDesignInfo(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo);
DT32_int ras_getDesignGlobalInfo(DT_void *pattr, DT16_ushort gidx, DT32_int option, DT_void **dsninfo);

DT32_int ras_uninitFont( DT_void *pattr );

#ifndef FD_READINTBYDATA1
#define FD_READINTBYDATA1(fontdata, ofs)		( (fontdata[(ofs)] )		// Not used
#endif
#ifndef FD_READINTBYDATA2
#define FD_READINTBYDATA2(fontdata,ofs)	( (DT32_long)(((DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8) | (DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)])) )
#endif
#ifndef FD_READINTBYDATA4
#define FD_READINTBYDATA4(fontdata,ofs) ( (DT32_long)(((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+3]) << 24) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+2]) << 16) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8)  | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)]))) )
#endif
DT32_long rasFDL_ReadInt(DT8_char *fdl, DT32_long ofs, DT32_int size);


#endif
