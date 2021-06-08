#ifndef __DIGITYPE_OVG_H
#define __DIGITYPE_OVG_H

#include "ovgDcwApi.h"

typedef struct _DcwOpenVG_Attr
{
	DT_void				*pwrk;
	DCWOUL_Handle		hDcwOVG;
	DT8_char			*fontdata;
	DT32_int			vert;
	DT_BOOL				bPix;				// get Logh on pixel based (DT_TRUE) or EM based (DT_FALSE), might not requird.
}DcwOpenVG_Attr, *pDcwOpenVG_Attr;

#define OUL_NOT_SCALE				0
#define OUL_SCALE_BY_XYSCALERATIO	0x0001	// scale by sizey when hori; by sizex when vert.
#define OUL_SCALE_BY_RATIO_FILEWIDE	0x0002
#define OUL_SCALE_BY_CODERANGE		0x0004
#define OUL_SCALE_BY_RASSCALERATIO	0x0008	// scale by sizex & sizey no matter hori or vert.
#define OUL_SCALE_BY_BINSCALERATIO	0x0010	// scale by sizex & sizey no matter hori or vert.

/* scalexy for oul_getRatioScaleValue() */
#define OUL_SCALE_X	0x0
#define OUL_SCALE_Y	0x1

// option for DCWOUL_GetAw_1
#define OUL_OPTION_EXIST			1
#define OUL_OPTION_GETAW			2

/* Functions for get glyph's info. */
DT32_int oul_EstimateWkMem();
DT32_int oul_initFont ( DT_void *pattr, DT8_char *fontdata, DT32_long wkmsz, DT8_char *wkm, DT_void *pwrk);
DT32_int oul_getOutline(DT_void *pattr, DT16_ushort ch, DT_void *op, DT32_long *bufsz, DT8_char **olbuf, DT32_long *pathsz);
DT32_int oul_getCharOul(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_long bufsz, DT_void *olbuf, DT32_long *pathsz);
DT32_int oul_chkGlyphExist( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int oul_getAwidth( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int oul_getAwidth_pix(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int oul_getAwidth2(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy);
DT32_int oul_getAheight(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int oul_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int oul_getLogt( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int oul_getHeight( DT_void *pattr );
DT32_int oul_getWidth( DT_void *pattr );
DT32_int oul_getExten ( DT_void *pattr );
DT32_int oul_getAexten( DT_void *pattr, DT16_ushort ch );	/* Added by Jacky_20090821 */
DT32_int oul_getVexten( DT_void *pattr, DT16_ushort ch );
DT32_int oul_getEdge( DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r );
DT32_int oul_getDesignInfo(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo);
DT32_int oul_getDesignGlobalInfo(DT_void *pattr, DT16_ushort gidx, DT32_int option, DT_void **pdsninfo);

DT32_int oul_fastCharOul(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_long bufsz, DT_void *olbuf, DT32_long *pathsz);

DT32_int oul_uninitFont ( DT_void *pattr );

#ifndef FD_READINTBYDATA1
#define FD_READINTBYDATA1(fontdata, ofs)		( (fontdata[(ofs)] )		// Not used
#endif
#ifndef FD_READINTBYDATA2
#define FD_READINTBYDATA2(fontdata,ofs)	( (DT32_long)(((DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8) | (DT16_ushort)(((DT8_uchar*)fontdata)[(ofs)])) )
#endif
#ifndef FD_READINTBYDATA4
#define FD_READINTBYDATA4(fontdata,ofs) ( (DT32_long)(((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+3]) << 24) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+2]) << 16) | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)+1]) << 8)  | ((DT32_ulong)(((DT8_uchar*)fontdata)[(ofs)]))) )
#endif
DT32_long oulFDL_ReadInt(DT8_char *fdl, DT32_long ofs, DT32_int size);

#endif
