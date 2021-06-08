#ifndef __BDF_RASTER_H
#define __BDF_RASTER_H

typedef struct _BDF_CMapRec
{
	DT16_ushort	ucode;
	DT16_ushort	deviceaw;
	DT32_long	offset;
}BDF_CMap, *pBDF_CMap;

#define BDF_CODE_NOT_EXIST	(-10000)

/****************Functions to get information in a BDF File***************************************/
/* CMap mode */
#define BDF_CMAP_SPEED_MODE		1		/* Need [sizeof(DT32_long)=4]*0x10000=0x40000=256k bytes of working memory */
#define BDF_CMAP_GENERAL_MODE	2		/* According to the fontdata (code section) */
#define CMAP_MODE (BDF_CMAP_GENERAL_MODE)

#define	BDF_GLOBAL_PART	0
#define BDF_GLYPH_PART	1

typedef enum {
	gSTARTFONT=0,
	gCOMMENT,
	gCONTENTVERSION,
	gFONT,
	gSIZE,
	gFONTBOUNDINGBOX,
	gMETRICSSET,
	gfSWIDTH,
	gfDWIDTH,
	gfSWIDTH1,
	gfDWIDTH1,
	gfVVECTOR,
	gSTARTPROPERTIES,
	gENDPROPERTIES,
	gCHARS,
	gENDFONT,
	fSTARTCHAR,
	fENCODING,
/*	fSWIDTH,
	fDWIDTH,
	fSWIDTH1,
	fDWIDTH1,
	fVVECTOR,*/
	fBBX,
	fBITMAP,
	fBITMAP_DATA,
	fENDCHAR,
	BDFITEMNAME_END
} BDFITEMNAME;

typedef struct _PXYSIZE {
	DT16_short Psize;	/* PointSize */
	DT16_short xres;		/* Xres */
	DT16_short yres;		/* Yres */
} PXYSIZE, *pPXYSIZE;

typedef struct _BBX {
	DT16_short bbx;
	DT16_short bby;
	DT16_short bbxoff;
	DT16_short bbyoff;
} BBX, *pBBX;

typedef struct _VVECTOR {
	DT16_short	xoff;
	DT16_short	yoff;
} VVECTOR, *pVVECTOR;

typedef struct _WIDTH {
	DT16_short	x;
	DT16_short	y;
} SWIDTH, DWIDTH, SWIDTH1, DWIDTH1;

typedef struct _METRICS {
	SWIDTH	sw0;
	DWIDTH	dw0;
	SWIDTH1	sw1;
	DWIDTH1	dw1;
	VVECTOR	vv;
} METRICS, *pMETRICS;

typedef struct _Bdfginfo {
	DT8_uchar	ver;		/* STARTFONT 2.1--upper 4bits is the major value(2), lower is the minor(1). ver=0x21 */
	/*DT8_char	*comment;*/	/* COMMENT */
	/*DT16_short conver;*/	/* CONTENTVERSION */
	/*DT8_char	*fontname;*//* FONT */
	PXYSIZE		gPSize;		/* SIZE */
	BBX			gFbbx;		/* FONTBOUNDINGBOX */
	DT16_short	gMtrxset;	/* METRICSSET, 0,1,2; only 0 is valid now. We don't deal with vertical rendering. */
	METRICS		gMtrx;		/* METRICSSET */
	DT16_short	proplines;	/* STARTPROPERTIES */	
	/*DT8_char	*prop;*/	/* STARTPROPERTIES-ENDPROPERTIES */
	DT32_int	nglyphs;	/* CHARS */
	DT32_long	*cmaptab;	/* 0x0000-0xffff shift array to get the start position for every glyph(char) */
	DT32_long	cmapmemsz;	/* the allocated size (in bytes) for cmap table.							 */
	DT8_char	*fontdata;	/* BDF font data */
} Bdfginfo, *pBdfginfo;

typedef struct _Glyphinfo {
	DT8_char	name[14];	/* STARTCHAR 14 chars for ver-2.1, unlimited for ver-2.2 */
	DT16_ushort	code;		/* ENCODING */
	METRICS		mtrx;		/* SWIDTH, DWIDTH, SWIDTH1, DWIDTH1, VVECTOR */
	BBX			bbx;		/* BBX */
	DT8_uchar	*bmp;		/* BITMAP */
	DT32_long	fileshift;	/* Shift from bdf file (Bdfginfo.fontdata) start.  */
} Glyphinfo, *pGlyphinfo;

#define BDF_LINEBUF_SIZE	512
#define BDF_ITEMBUF_SIZE	256

typedef struct _BdfRaster_Attr
{
	DT_void		*pwrk;
	Bdfginfo	info;
	DT8_char	*line;		/* pointer to DT8_char line[512]; BDF_LINEBUF_SIZE	*/
	DT8_char	*item;		/* pointer to DT8_char item[256]; BDF_ITEMBUF_SIZE	*/
}BdfRaster_Attr, *pBdfRaster_Attr;


DT32_int bdf_EstimateWkMem();
DT32_int bdf_initFont( DT_void *pattr,DT8_char *fontdata, DT32_long fWkMemsize, DT8_char *fWkMem, DT_void *pwrk);
DT32_int bdf_getCharbmp(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int bmpw, DT32_int bmph, DT32_int x0, DT32_int y0, DT32_int xbytes, DT8_uchar *bmp, DT_void *op, DT32_int mode);
DT32_int bdf_chkGlyphExist( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int bdf_getAwidth( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int bdf_getAwidth2(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy);
DT32_int bdf_getAheight(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx );
DT32_int bdf_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int bdf_getLogt( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx);
DT32_int bdf_getHeight( DT_void *pattr );
DT32_int bdf_getWidth( DT_void *pattr );
DT32_int bdf_getExten( DT_void *pattr );
DT32_int bdf_getAexten( DT_void *pattr, DT16_ushort ch );	/* Added by Jacky_20090821 */
DT32_int bdf_getVexten( DT_void *pattr, DT16_ushort ch );	/* Added by Jacky_20091023 */
DT32_int bdf_getEdge( DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r );
DT32_int bdf_getDesignInfo(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo);
DT32_int bdf_uninitFont( DT_void *pattr );

#endif
