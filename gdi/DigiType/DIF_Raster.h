#ifndef __DIF_RASTER_H
#define __DIF_RASTER_H

typedef struct _DifRaster_Attr
{
	DT_void				*pwrk;		/* pLayWrk	*/
	DT_void				*dtfont;	/* DT_Font* of iconfont */
	DT8_uchar			*fontdata;
}DifRaster_Attr, *pDifRaster_Attr;

typedef struct _DifSec
{
	DT8_uchar	sec;	/* code=0xE0xx, sec=0xE0; code=0xE2xx, sec=0xE2;*/
	DT8_uchar	idx;	/* section index in the SecList. idx is useless, packing inside just for 2-bytes align. */
}DifSec, *pDifSec;


#define DIF_IDENT	0	/* 8 bytes	*//*DT8_char[8]	*/
#define DIF_MAX_W	8	/* 1 byte	*//*DT8_uchar	*/
#define DIF_MAX_H	9	/* 1 byte	*//*DT8_uchar	*/
#define DIF_FCNT	10	/* 2 byte	*//*DT16_ushort	*/
#define DIF_SECCNT	32	/* Section count, 2 bytes	*//*DT16_ushort	*//* hi-byte reserved. */
#define DIF_SECLIST	34	/* SecList, 2*SecCnt bytes	*//*DT16_ushort	*//* hi-byte:idx, low-byte:Sec	*/

#define DIF_CODE_NOT_EXIST	(-10000)

DT16_ushort DIF_read2(DT8_uchar *from);
DT32_uint	DIF_read4(DT8_uchar *from);

DT32_int	isDifFont(DT8_uchar *fontdata);
DT8_uchar	getDifMaxW(DT8_uchar *fontdata);
DT8_uchar	getDifMaxH(DT8_uchar *fontdata);
DT16_ushort	getDifFontcnt(DT8_uchar *fontdata);
DT16_ushort	getDifSecCnt(DT8_uchar *fontdata);
DT32_uint	getDifAddrTabStart(DT8_uchar *fontdata);
DT32_int	getDifSecIdx(DT8_uchar *fontdata, DT16_ushort ch);
DT32_uint	getDifCharOffset(DT8_uchar *fontdata, DT16_ushort ch);
DT8_uchar	*jump2DifCharStart(DT8_uchar *fontdata, DT16_ushort ch);



DT32_int dif_EstimateWkMem();
DT32_int dif_initFont( DT_void *pattr,DT8_char *fontdata, DT32_long fWkMemsize, DT8_char *fWkMem, DT_void *pwrk);
DT32_int dif_getCharbmp(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int bmpw, DT32_int bmph, DT32_int x0, DT32_int y0, DT32_int xbytes, DT8_uchar *bmp, DT_void *op, DT32_int mode);
DT32_int dif_chkGlyphExist( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int dif_getAwidth( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int dif_getAwidth2(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy);
DT32_int dif_getAheight(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int dif_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int dif_getLogt( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int dif_getHeight( DT_void *pattr );
DT32_int dif_getWidth( DT_void *pattr );
DT32_int dif_getExten( DT_void *pattr );
DT32_int dif_getAexten( DT_void *pattr, DT16_ushort ch );	/* Added by Jacky_20090821 */
DT32_int dif_getVexten( DT_void *pattr, DT16_ushort ch );	/* Added by Jacky_20091023 */
DT32_int dif_getEdge( DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r );
DT32_int dif_getDesignInfo(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo);
DT32_int dif_uninitFont( DT_void *pattr );

#endif
