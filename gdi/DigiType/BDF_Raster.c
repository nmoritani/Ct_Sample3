#include "DcwLangModule.h"
#include "DcwLayout.h"


#ifdef BDF_RASTER

#include "DcwShaperVG.h"
#include "BDF_Raster.h"
#include "DTmanager.h"
#include "DigiTypeApi.h"


DT32_int my_atoi(DT8_char *a, DT32_int nlen)
{
	DT32_int i=0, ret=0, neg=0;

DBG_MSG_SHOW_FUNC_NAME();

	if(a[0] == '-')
	{
		i++;
		neg = 1;
	}// end if

	for(; i < nlen; i++)
	{
		ret *= 10;
		ret += a[i] - '0';
	}// end for

	if(neg)
		ret = 0-ret;
	return ret;
}

DT_void ClearBuf(DT_void *p, DT32_int n)
{
/*	DT32_int i,cnt;
	DT32_long *cp = (DT32_long*)p;

	// Clear by 4 bytes
	cnt = (n>>2);		// (n+3)/sizeof(DT32_long); assume DT32_long is 4 bytes.
	for(i=0;i<cnt;i++)
		*(cp+i) = 0;

	// Clear the remained bytes.
	for(i<<=2;i < n;i++){
		*((DT8_char*)p+i) = 0;
	}
*/
DBG_MSG_SHOW_FUNC_NAME();

	DT_memset(p,0,n);
}

DT_void ClearBBX(BBX *bb)
{
/*	bb->bbx = 0;
	bb->bby = 0;
	bb->bbxoff = 0;
	bb->bbyoff = 0;
*/
DBG_MSG_SHOW_FUNC_NAME();

	DT_memset((DT_void*)bb,0,sizeof(BBX));
}

DT_void ClearMtx(METRICS *mtx)
{
/*	mtx->sw0.x = 0;		mtx->sw0.y = 0;
	mtx->sw1.x = 0;		mtx->sw1.y = 0;
	mtx->dw0.x = 0;		mtx->dw0.y = 0;
	mtx->dw1.x = 0;		mtx->dw1.y = 0;
	mtx->vv.xoff = 0;	mtx->vv.yoff = 0;
*/
DBG_MSG_SHOW_FUNC_NAME();

	DT_memset((DT_void*)mtx,0,sizeof(METRICS));
}

static DT_void ClearGlyph(Glyphinfo *glyphinfo)
{
/*	ClearBuf( glyphinfo->name, sizeof(glyphinfo->name) );
	glyphinfo->code = 0;
	ClearMtx(&glyphinfo->mtrx);
	ClearBBX(&glyphinfo->bbx);
	glyphinfo->fileshift = 0;
	glyphinfo->bmp = 0;
*/
DBG_MSG_SHOW_FUNC_NAME();

	DT_memset((DT_void*)glyphinfo,0,sizeof(Glyphinfo));
}

/*
parameters:
fromp:	start position in "fontdata" in bytes.
*top:	the start position of next line.
(*top-fromp: total bytes read, including CR, LF, and EOF)
*nlen:	the length (bytes) of this line, CR, LF, and EOF codes are not included.
line:	buffer to contain the line data.
cp2buf: 1: copy the data to "line" buf, 0: don't copy the data to "line" buf.
return value:
1: end of file
0: success
-1: error
*/
DT32_int GetaLine(DT8_char *fontdata, DT32_long fromp, DT32_long *top, DT32_long *nlen, DT8_char *line, DT32_int cp2buf)
{
	DT8_char *p;
	DT32_int retval=0;
	DT32_long j=0;

DBG_MSG_SHOW_FUNC_NAME();

	if(cp2buf && !line)	return -1;
	if(cp2buf)
	{
		if(!line) return -1;
		p = fontdata+fromp;
		while(1)
		{
			if(*p == 0x0D)
			{
				p+=2;
				//if(*p == 0x0A) p++;
				break;
			}/*else if(*p == 0x0A)
			{
				p++;
				break;
			}else if(*p == 0x1A)
				break;*/
			else
			{
				line[j++] = *p;
				p++;
			}// end if
		}// end while

		line[j] = '\0';
	}else
	{
		p = fontdata+fromp;
		while(1)
		{
			if(*p == 0x0D)
			{
				p+=2;
				//if(*p == 0x0A) p++;
				break;
			}/*else if(*p == 0x0A)
			{
				p++;
				break;
			}else if(*p == 0x1A)
				break;*/
			else
			{
				//line[j++] = *p;
				p++;
			}// end if
		}// end while

	}// end if

	*top = p - fontdata;
	*nlen = j;

	return retval;

}

/* return value: the bytes of read char. (nLen) */
DT32_int GetaItem(DT8_char *line, DT32_int ln, DT32_int startp, DT8_char *buf, DT32_int *nread)
{
	DT8_char *p;
	DT32_int i, j=0;

DBG_MSG_SHOW_FUNC_NAME();

	//if(startp > ln)	return 0;
	p = line+startp;
	for(i=startp; i < ln; i++)
	{
		if(*p == ' ')// || *p == 0)
		{
			p++;
			break;
		}else
		{
			buf[j++] = *p;
		}// end if

		p++;
	}// end for

	*nread = p-(line+startp);
	buf[j] = '\0';
	return j;
}

typedef struct TOKEN {
	DT8_char *token;
	DT32_ulong tokenkey;
	DT32_int token_len;
	BDFITEMNAME token_id;	//int token_id;
}TOKEN;

#define TOKEN_KEY(x, y, z, v)				( ((x) << 24) | ((y) << 16 ) | ((z) << 8) | v )

TOKEN token_list[] = {
//	{"BBX ",						sizeof("BBX "),							fBBX},
	{"FONT", 				TOKEN_KEY('F', 'O', 'N', 'T'),		sizeof("FONT")-1, 						gFONT},
	{"SIZE", 				TOKEN_KEY('S', 'I', 'Z', 'E'),		sizeof("SIZE")-1, 						gSIZE},
	{"CHARS",				TOKEN_KEY('C', 'H', 'A', 'R'),		sizeof("CHARS")-1,						gCHARS},
	{"BITMAP",				TOKEN_KEY('B', 'I', 'T', 'M'),		sizeof("BITMAP")-1,						fBITMAP},
	{"DWIDTH",				TOKEN_KEY('D', 'W', 'I', 'D'),		sizeof("DWIDTH")-1,						gfDWIDTH},
	{"SWIDTH",				TOKEN_KEY('S', 'W', 'I', 'D'),		sizeof("SWIDTH")-1,						gfSWIDTH},
	{"COMMENT", 			TOKEN_KEY('C', 'O', 'M', 'M'),		sizeof("COMMENT")-1, 					gCOMMENT},
	{"DWIDTH1",				TOKEN_KEY('D', 'W', 'I', 'D'),		sizeof("DWIDTH1")-1,					gfDWIDTH1},
	{"ENDCHAR",				TOKEN_KEY('E', 'N', 'D', 'C'),		sizeof("ENDCHAR")-1,					fENDCHAR},
	{"ENDFONT",				TOKEN_KEY('E', 'N', 'D', 'F'),		sizeof("ENDFONT")-1,					gENDFONT},
	{"SWIDTH1",				TOKEN_KEY('S', 'W', 'I', 'D'),		sizeof("SWIDTH1")-1,					gfSWIDTH1},
	{"VVECTOR",				TOKEN_KEY('V', 'V', 'E', 'C'),		sizeof("VVECTOR")-1,					gfVVECTOR},
	{"ENCODING",			TOKEN_KEY('E', 'N', 'C', 'O'),		sizeof("ENCODING")-1,					fENCODING},
//	{"STARTCHAR",			TOKEN_KEY('S', 'T', 'A', 'R'),		sizeof("STARTCHAR")-1,					fSTARTCHAR},
//	{"STARTFONT", 			TOKEN_KEY('S', 'T', 'A', 'R'),		sizeof("STARTFONT")-1, 					gSTARTFONT},
	{"METRICSSET",			TOKEN_KEY('M', 'E', 'T', 'R'),		sizeof("METRICSSET")-1,					gMETRICSSET},
	{"ENDPROPERTIES",		TOKEN_KEY('E', 'N', 'D', 'P'),		sizeof("ENDPROPERTIES")-1,				gENDPROPERTIES},
	{"CONTENTVERSION",		TOKEN_KEY('C', 'O', 'N', 'T'),		sizeof("CONTENTVERSION")-1,	 			gCONTENTVERSION},
	{"FONTBOUNDINGBOX",		TOKEN_KEY('F', 'O', 'N', 'T'),		sizeof("FONTBOUNDINGBOX")-1,			gFONTBOUNDINGBOX},
	{"STARTPROPERTIES",		TOKEN_KEY('S', 'T', 'A', 'R'),		sizeof("STARTPROPERTIES")-1,			gSTARTPROPERTIES},
};

DT32_int itemcmp(DT8_char *item, DT32_int nLen, DT8_char *constitem, DT32_int constnlen)
{
	int i;

DBG_MSG_SHOW_FUNC_NAME();

	if(nLen != constnlen)
		return -1;

	for(i=0; i<nLen; i++){
		if(item[i]!=constitem[i])
			return -1;
	}
	return 0;

/*	DT32_int i=0,cnt=0;
	DT32_long *im;
	DT32_long *cim;

DBG_MSG_SHOW_FUNC_NAME();

	if(nLen != constnlen)
		return -1;

	im  = (DT32_long*)item;
	cim = (DT32_long*)constitem;
	cnt = (nLen+3)>>2;		// (n+3)/sizeof(DT32_long); assume DT32_long is 4 bytes.
	for(i=0;i<cnt;i++){
		if(im[i]!=cim[i])
			return -1;
	}

//	DumpDebugString("%s\n", item);
	return 0;
*/
}

BDFITEMNAME MatchItem(DT8_char *item, DT32_int nLen)
{
	DT32_ulong tokenkey;
	DT32_int start, now, end, value;

DBG_MSG_SHOW_FUNC_NAME();

	if(nLen < 3 || item[0] < 'A')
	{
		return fBITMAP_DATA;
	}else if(nLen == 3)		// ignore error check.
	{
		return fBBX;
	}else if(nLen == 9)
	{
		if(item[5] == 'C')
		{
			return fSTARTCHAR;
		}else
		{
			return gSTARTFONT;
		}
	}// end if

	tokenkey = TOKEN_KEY(item[0], item[1], item[2], item[3]);
	start = 0;
	end = sizeof(token_list)/sizeof(token_list[0]) - 1;

	while(start <= end)
	{
		now = (end+start)/2;

		// =====================================================================
		if(nLen == token_list[now].token_len)
			value = tokenkey - token_list[now].tokenkey;
		else value = nLen - token_list[now].token_len;
		// =====================================================================

		if(value == 0)
		{
			return token_list[now].token_id;
		}

		if(value < 0)
			end = now-1;
		else
		{
			start = now+1;
			now++;
		}// end if
	}// end while

//	DumpDebugString("%s\n", item);
	return fBITMAP_DATA;
}// end MatchItem

/*	part: 0: means global part of bdf file. 1: means char(glyph) part of bdf file.  */
/*	return value: 
	-1: parse error.
	 0: parse successfully.
	 1: parse successfully and it's the end of the part(global or glyph).
	 2: it's the end of file.
*/
DT32_int ParseLine(BdfRaster_Attr *bdfrasattr, DT8_char *line, DT32_int ln, Bdfginfo *ginfo, Glyphinfo *finfo, DT32_int part, BDFITEMNAME *iname)
{
	METRICS	*mtx;
	DT32_int nLen=0, i=0, j=0, ncnt=0, nread=0, tmp=0;
	DT8_char *item = bdfrasattr->item;

DBG_MSG_SHOW_FUNC_NAME();

	//ClearBuf(item,BDF_ITEMBUF_SIZE);	//ClearBuf(item,sizeof(item));

	if(part==BDF_GLOBAL_PART){
		if(!ginfo)	
			return -1;
		mtx = &ginfo->gMtrx;
	}else if(part==BDF_GLYPH_PART){
		if(!finfo)	
			return -1;
		mtx = &finfo->mtrx;
	}else{
		return -1;
	}

	if(ln > 0)
	{
		nLen=GetaItem(line,ln,i,item,&nread);
		*iname=MatchItem(item,nLen);							//ClearBuf(item,nLen);

		switch(*iname)
		{
		case gSTARTFONT:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			if(!itemcmp(item,nLen,"2.2",3)) ginfo->ver=0x22;
			else if(!itemcmp(item,nLen,"2.1",3)) ginfo->ver=0x21;
																//ClearBuf(item,nLen);
			break;
/*		case gCOMMENT:
			break;
		case gCONTENTVERSION:
			break;
		case gFONT:
			break;*/
		case gSIZE:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->gPSize.Psize = (DT16_short)my_atoi(item,nLen);	//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->gPSize.xres = (DT16_short)my_atoi(item,nLen);		//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->gPSize.yres = (DT16_short)my_atoi(item,nLen);		//ClearBuf(item,nLen);
			break;
		case gFONTBOUNDINGBOX:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->gFbbx.bbx = (DT16_short)my_atoi(item,nLen);		//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->gFbbx.bby = (DT16_short)my_atoi(item,nLen);		//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->gFbbx.bbxoff = (DT16_short)my_atoi(item,nLen);	//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->gFbbx.bbyoff = (DT16_short)my_atoi(item,nLen);	//ClearBuf(item,nLen);
			break;
		case gMETRICSSET:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->gMtrxset = (DT16_short)my_atoi(item,nLen);		//ClearBuf(item,nLen);
			break;
		case gfSWIDTH:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->sw0.x = (DT16_short)my_atoi(item,nLen);				//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->sw0.y = (DT16_short)my_atoi(item,nLen);				//ClearBuf(item,nLen);
			break;
		case gfDWIDTH:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->dw0.x = (DT16_short)my_atoi(item,nLen);				//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->dw0.y = (DT16_short)my_atoi(item,nLen);				//ClearBuf(item,nLen);
			break;
		case gfSWIDTH1:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->sw1.x = (DT16_short)my_atoi(item,nLen);				//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->sw1.y = (DT16_short)my_atoi(item,nLen);				//ClearBuf(item,nLen);
			break;
		case gfDWIDTH1:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->dw1.x = (DT16_short)my_atoi(item,nLen);				//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->dw1.y = (DT16_short)my_atoi(item,nLen);				//ClearBuf(item,nLen);
			break;
		case gfVVECTOR:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->vv.xoff = (DT16_short)my_atoi(item,nLen);			//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			mtx->vv.yoff = (DT16_short)my_atoi(item,nLen);			//ClearBuf(item,nLen);
			break;
		case gSTARTPROPERTIES:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->proplines = (DT16_short)my_atoi(item,nLen);		//ClearBuf(item,nLen);
			break;
//		case gENDPROPERTIES:
//			break;
		case gCHARS:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			ginfo->nglyphs = my_atoi(item,nLen);				//ClearBuf(item,nLen);
			if(part==BDF_GLOBAL_PART)	return 1;
			else break;
		case gENDFONT:
			return 2;
		case fSTARTCHAR:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			tmp = (DT32_int)sizeof(finfo->name);	ncnt = tmp<nLen?tmp:nLen;
			for(j=0;j<ncnt;j++)	finfo->name[j] = item[j];
																ClearBuf(item,nLen);
			break;
		case fENCODING:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			finfo->code = (DT16_ushort)my_atoi(item,nLen);	//ClearBuf(item,nLen);
			break;
/*		case fSWIDTH:
			break;
		case fDWIDTH:
			break;
		case fSWIDTH1:
			break;
		case fDWIDTH1:
			break;
		case fVVECTOR:
			break;		*/
		case fBBX:
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			finfo->bbx.bbx = (DT16_short)my_atoi(item,nLen);			//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			finfo->bbx.bby = (DT16_short)my_atoi(item,nLen);			//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			finfo->bbx.bbxoff = (DT16_short)my_atoi(item,nLen);		//ClearBuf(item,nLen);
			i += nread;	nLen=GetaItem(line,ln,i,item,&nread);
			finfo->bbx.bbyoff = (DT16_short)my_atoi(item,nLen);		//ClearBuf(item,nLen);
			break;
/*		case fBITMAP:
			break;
		case fBITMAP_DATA:
			break;*/
		case fENDCHAR:
			if(part==BDF_GLYPH_PART) return 1;
			else break;
		default:
			//return -1;
			break;
		}	
	}
	return 0;		
}

DT_void SkipnLines(DT8_char *data, DT32_long start, DT32_int n, DT32_long *nend, DT32_long *nread)
{
	DT32_int ret, i=0;
	DT32_long nlen=0, nfrom=0, lr=0;

DBG_MSG_SHOW_FUNC_NAME();

	nfrom = start;
	for(i=0;i<n;i++)
	{
		ret=GetaLine(data,nfrom,nend,&nlen,0,0);
		if(!ret)
		{
			lr += (*nend-nfrom);
			nfrom = *nend;
		}else	break;
	}
	*nread = lr;
}

DT_void MakeDesignValue(DT_void *info, DT8_char *line, DT32_int lineLen, DT8_char *item, DT32_int itemLen, DT32_int nRead)
{
	Font_Design_Thai *fd = (Font_Design_Thai *)info;
	DT8_char val[8];
	DT32_int nread=0, valLen=0;

DBG_MSG_SHOW_FUNC_NAME();

#ifdef THAI_thai
	ClearBuf(val,sizeof(val));
	if(!itemcmp(item,itemLen,"THAI_TOP",8)){
		valLen=GetaItem(line,lineLen,nRead,val,&nread);
		fd->Thai_Top = (DT16_ushort) my_atoi(val,valLen);
	}else if(!itemcmp(item,itemLen,"THAI_ABOVE",10)){
		valLen=GetaItem(line,lineLen,nRead,val,&nread);
		fd->Thai_Above = (DT16_ushort) my_atoi(val,valLen);
	}else if(!itemcmp(item,itemLen,"THAI_BASE",9)){
		valLen=GetaItem(line,lineLen,nRead,val,&nread);
		fd->Thai_Base = (DT16_ushort) my_atoi(val,valLen);
	}else if(!itemcmp(item,itemLen,"THAI_BELOW",10)){
		valLen=GetaItem(line,lineLen,nRead,val,&nread);
		fd->Thai_Below = (DT16_ushort) my_atoi(val,valLen);
	}else if(!itemcmp(item,itemLen,"THAI_SHIFT",10)){
		valLen=GetaItem(line,lineLen,nRead,val,&nread);
		fd->Thai_Shift = (DT16_ushort) my_atoi(val,valLen);
	}
	ClearBuf(val,valLen);
#endif
	
}


/* ParseProperties for Font_Design info. */
DT_void ParseProperties(BdfRaster_Attr *bdfrasattr, DT_void *info, DT8_char *data, DT32_long start, DT32_int n, DT32_long *nend, DT32_long *nread, DT8_char *buf)
{
	/*Font_Design *fd = (Font_Design *)info;*/
	DT32_int ret, i, nLen,nRead;
	DT32_long nlen=0, nfrom=0, lr=0;
	DT8_char *line = bdfrasattr->line;
	DT8_char *item = bdfrasattr->item;

DBG_MSG_SHOW_FUNC_NAME();

	//ClearBuf(line,BDF_LINEBUF_SIZE);	//ClearBuf(line,sizeof(line));
	//ClearBuf(item,BDF_ITEMBUF_SIZE);
	nfrom = start;
	for(i=0;i<n;i++){
		ret=GetaLine(data,nfrom,nend,&nlen,line,1);
		if(!ret){
			nLen=GetaItem(line,nlen,0,item,&nRead);
			MakeDesignValue(info,line,nlen,item,nLen,nRead);
			//ClearBuf(item,nLen);

			lr += (*nend-nfrom);
			nfrom = *nend;
		}else	break;	
			//ClearBuf(line,nlen);
	}
	*nread = lr;
}

/* return value 1:part end; 0: success; <0: error. */
DT32_int GetGlobalPart(BdfRaster_Attr *bdfrasattr,/*Bdfginfo *info,*/ DT8_char *fontdata, DT32_long *gend)
{
	Bdfginfo *info = &bdfrasattr->info;
	DT32_long nfrom, nend, nlen=0, nread=0;
	DT32_int rval, ret=0;
	BDFITEMNAME itemname;
	DT8_char *line = bdfrasattr->line;

DBG_MSG_SHOW_FUNC_NAME();

	//ClearBuf(line,BDF_LINEBUF_SIZE);	//ClearBuf(line,sizeof(line));

	nfrom=0;
	while(1)
	{
		ret=GetaLine(fontdata, nfrom, &nend, &nlen, line, 1);
		nread = nend - nfrom;	*gend = nend;
		if(ret==0){
			rval=ParseLine(bdfrasattr, line, nlen, info, 0, BDF_GLOBAL_PART, &itemname);
			if(rval==1) break;
			else if(rval<0) return -2;

			if(itemname==gSTARTPROPERTIES)
			{
				nfrom = nend;
				SkipnLines(fontdata, nfrom, info->proplines, &nend, &nread);
			}
		}else if(ret==1) return 1;
		else if(ret<0) return -1;

		nfrom = nend;
//		ClearBuf(line,nlen);
	}
	return 0;
}

/* return value 1:part end; 0: success; <0: error. */
DT32_int GetCharpart(BdfRaster_Attr *bdfrasattr, DT8_char *fontdata, DT32_long start, Glyphinfo *glyphinfo, DT32_long *gend)
{
// 	Bdfginfo *info = &bdfrasattr->info;
	DT8_char *line = bdfrasattr->line;
	DT32_long nfrom, nend, nlen=0, nread=0;
	DT32_int rval, ret=0, datalines=0; /* use datalines to ensure the data is correct. */
	BDFITEMNAME itemname;

DBG_MSG_SHOW_FUNC_NAME();

	//ClearBuf(line,BDF_LINEBUF_SIZE);	//ClearBuf(line,sizeof(line));

	nfrom=start;
	while(1){
		ret=GetaLine(fontdata, nfrom, &nend, &nlen, line, 1);
		nread = nend - nfrom;	*gend = nend;
		if(ret==0){
			rval=ParseLine(bdfrasattr, line, nlen, 0, glyphinfo, BDF_GLYPH_PART, &itemname);
			if(rval<0) 
				return -2;
			//else if(rval==2)	// the end of file.
			//	return -3;

			if(itemname==fBITMAP){ 
				glyphinfo->fileshift=nend; datalines = glyphinfo->bbx.bby; 
			}else if(itemname==fBITMAP_DATA){ 
				//datalines--; 
				nend = nfrom+nread*datalines;	// jump to the end of char part
				datalines = 0;
			}else if(itemname==fENDCHAR && rval==1){
				//if(datalines!=0) return -2; /*might be error*/
				//else break;
				/* Do not check if the data is correct, leave directly */
				break;
			}else if(itemname==gENDFONT) 
				return -3;
		}else if(ret==1) 
			return 1;
		else if(ret<0) 
			return -1;

		nfrom = nend;
		//ClearBuf(line,nlen);		/* Jacky_20100721 */
	}

	return 0;
}


#if CMAP_MODE==BDF_CMAP_GENERAL_MODE
DT16_ushort GetSecPointer(DT32_long *cmap, DT16_ushort ch, DT8_uchar *nSec)
{
	DT16_ushort ret;
	DT16_ushort hi, lo;
	DT16_ushort filterH=0xff00, filterL=0x00ff;
	DT8_uchar n = *nSec;

DBG_MSG_SHOW_FUNC_NAME();

	hi = ch & filterH;
	lo = ch & filterL;
	if(cmap[hi>>8]){
		ret = (DT16_ushort)cmap[hi>>8];
	}else{
		/*ret = cmap + sizeof(DT32_long)*0xff + sizeof(DT32_long)*0xff*n;*/
		/* Sec Table size is 256 (sizeof(DT32_long)). */
		ret = 256 + 256*n;
		cmap[hi>>8] = ret;
		n++;
	}
	*nSec = n;
	return ret+lo;
}
#endif
/*  This CMapTab is an array which elements are in "DT32_long" type. 
	The value (of DT32_long) is used to point out where the char starts in fontdata.*/
/* BDF_CMAP_SPEED_MODE: You can shift "code" to find the char's start position in file. */
/* BDF_CMAP_GENERAL_MODE: You can shift "code-hi-byte" to refer to the section start in the memory,
   then use "code-lo-byte" to find the start position in file. */
DT32_int MakeCMapTab(BdfRaster_Attr *bdfrasattr, DT8_char *fontdata, DT32_long start, DT32_long *cmap, DT32_long msize)
{
	Glyphinfo gf;
	DT32_long nend, nfrom=start,nsize=msize/sizeof(DT32_long);
	DT32_int i=0, ret=0;
	DT8_uchar nSec=0;
	DT16_ushort pos;

DBG_MSG_SHOW_FUNC_NAME();

#if CMAP_MODE==BDF_CMAP_SPEED_MODE
	while(ret>=0){
		ClearGlyph(&gf);
		ret=GetCharpart(bdfrasattr, fontdata, nfrom, &gf, &nend);
		if(ret>=0){ 
		  i++;
		  pos = gf.code;
		  cmap[pos] = nfrom;
		  nfrom = nend;
		}
	}
#elif CMAP_MODE==BDF_CMAP_GENERAL_MODE
	while(ret>=0){
		ClearGlyph(&gf);
		ret=GetCharpart(bdfrasattr, fontdata, nfrom, &gf, &nend);
		if(ret>=0){ 
		  i++;
		  pos=GetSecPointer(cmap, gf.code, &nSec);
		  if(pos<nsize){	/* ensure the memory is valid */
			cmap[pos] = nfrom;
			nfrom = nend;
		  }else{
			break;	/* do not continue in order to avoid memory overflow. */
		  }
		}else
			break;
	}
	if( (nSec+1)*0x100*sizeof(DT32_long) > (DT32_ulong)msize )
		return DLO_NOT_ENOUGH_ENGINEWKMEM;
#endif
	return i;
}
/* return: 0: Success, <0: error. (-1: file position error; -2: bits data mismatch) */
//static DT8_uchar tmpline[DLO_FONT_MAXSIZE*2+2];	/* line buffer: xsize*2(2 char represent 8bits)+2(CR-LF) */
DT32_int GetGlyfBMP(BdfRaster_Attr *bdfrasattr, Glyphinfo *finfo, DT8_uchar *buf, DT32_int xbytes, DT32_int ypos)
{
	DT32_int i,j,height,rval=0,bufiter=0;
	DT32_long nfrom=0,nend=0,nlen=0;
	DT8_uchar hi,lo,c;
	DT32_int xbytespos=0;
	//DT8_uchar tmpline[DLO_FONT_MAXSIZE*2+2];	/* line buffer: xsize*2(2 char represent 8bits)+2(CR-LF) */
	
	Bdfginfo *ginfo = (Bdfginfo*)&bdfrasattr->info;
	DT8_uchar *tmpline = (DT8_uchar*)bdfrasattr->line;

DBG_MSG_SHOW_FUNC_NAME();

	//ClearBuf(tmpline,sizeof(tmpline));
	height	= /*(finfo->bbx.bby==0)?ginfo->gFbbx.bby:*/finfo->bbx.bby;	/* Marked by Jacky_20100820 */
	nfrom	= finfo->fileshift;		if(!nfrom)	return -1;

	xbytespos = xbytes * ypos;
	for(i=0;i<height;i++)
	{
		rval=GetaLine(ginfo->fontdata, nfrom, &nend, &nlen, (DT8_char*)tmpline, 1);	/* Jacky_20090901 */
		if(!rval)
		{
		  j=0;
		  bufiter = xbytespos;
		  while(j < nlen)
		  {
			c = tmpline[j++];
			hi = (c<0x40) ? (c-0x30) : ((c&0x0F) + 0x09);
			if(j < nlen)
			{ c=tmpline[j];	lo= (c<0x40) ? (c-0x30) : ((c&0x0F) + 0x09);
			}else lo=0;
			c = (hi<<4)+lo;
			*(buf+bufiter) = c;
			bufiter++;
			j++;
			hi=0; lo=0;
		  }
		  //ClearBuf(tmpline,nlen);
		  nfrom = nend;
		}else{
			return -1;
		}// end if

		xbytespos += xbytes;
	}// end for

	if(i==height){
		rval=GetaLine(ginfo->fontdata, nfrom, &nend, &nlen, (DT8_char*)tmpline, 1);	/* Jacky_20090901 */
		if(!rval){
			if(nlen!=7 || fENDCHAR!=MatchItem((char*)tmpline, nlen) /*itemcmp((DT8_char*)tmpline, nlen, "ENDCHAR", 7)!=0*/) 
				return -2;	/* Jacky_20090901 */
			else
				return 0;
		}else
			return -1;
	}

	return 0;
}

DT32_long GetCharStartinFile(DT16_ushort ch, DT32_long *cmap)
{
	DT32_long from, pos, shift;

DBG_MSG_SHOW_FUNC_NAME();

#if CMAP_MODE==BDF_CMAP_SPEED_MODE
	from = cmap[ch];
#elif CMAP_MODE==BDF_CMAP_GENERAL_MODE
	pos = cmap[(ch&0xff00)>>8];
	if(pos==0){
		return 0;
	}

	shift =  ch&0xff;
	pos = pos + shift;
	from = cmap[ pos ];
#endif

	return from;
}

DT8_uchar bdfSetBitinBmp( DT8_uchar val, DT8_uchar byteval, DT32_int j, DT32_int op )
{
	DT8_uchar bitmask=0,bb=0;

DBG_MSG_SHOW_FUNC_NAME();

	switch(op){
	case DCW_COPYIFBKZERO:
		if(val>0){	
		  bitmask = val<<(7 - (j&7));
		  bb = bitmask | byteval;
		}else bb = byteval;
		
		break;
	case DCW_SETBKZERO:
		bitmask=0x01<<(7 - (j&7));
		bb = (~bitmask)&byteval;		
		break;
	default:
		if(val>0){	
		  bitmask = val<<(7 - (j&7));
		  bb = bitmask | byteval;
		}else bb = byteval;
	}
	return bb;
}

/*************************************************************************************************/
/* Estimate the required working memory */
DT32_int bdf_EstimateWkMem()
{
	DT32_int nSec=2;
	DT32_int nlinesz=BDF_LINEBUF_SIZE;	/* for DT8_char line[512];	at previous version	*/
	DT32_int nitemsz=BDF_ITEMBUF_SIZE;	/* for DT8_char item[256];	at previous version	*/
	DT32_int WkmSize;

DBG_MSG_SHOW_FUNC_NAME();

	WkmSize = nlinesz + nitemsz;
#if CMAP_MODE==BDF_CMAP_SPEED_MODE
	return WkmSize + sizeof(DT32_long)*0x10000*nSec;
#elif CMAP_MODE==BDF_CMAP_GENERAL_MODE
	return WkmSize + sizeof(DT32_long)*0x100*nSec;
#endif
}

/* Get bdf global information and complete CMap. */
DT32_int bdf_initFont( DT_void *pattr, DT8_char *fontdata, DT32_long fWkMemsize, DT8_char *fWkMem, DT_void *pwrk)
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *ginfo = (Bdfginfo*)&bdfrasattr->info;
	DT32_long	 gsize;
	DT32_int	 ret, total;

DBG_MSG_SHOW_FUNC_NAME();

#if CMAP_MODE==BDF_CMAP_SPEED_MODE
	if(fWkMemsize<(DT32_long)sizeof(DT32_long)*0x10000)	return DLO_NOT_ENOUGH_ENGINEWKMEM;
#elif CMAP_MODE==BDF_CMAP_GENERAL_MODE
	if(fWkMemsize<(DT32_long)sizeof(DT32_long)*0x200)	return DLO_NOT_ENOUGH_ENGINEWKMEM;
#endif


	bdfrasattr->pwrk = (pLayWrk)pwrk;
	bdfrasattr->line = fWkMem;
	bdfrasattr->item = fWkMem + BDF_LINEBUF_SIZE;


	ret=GetGlobalPart(bdfrasattr,/*ginfo,*/fontdata,&gsize);	
	if(ret<0)	return DLO_BAD_FONTDATA;
	
	ginfo->cmaptab = (DT32_long*) (DT8_char*)(fWkMem + BDF_LINEBUF_SIZE + BDF_ITEMBUF_SIZE);
	ginfo->cmapmemsz= fWkMemsize-BDF_LINEBUF_SIZE-BDF_ITEMBUF_SIZE;
	ginfo->fontdata = fontdata;
	total=MakeCMapTab(bdfrasattr,fontdata,gsize,ginfo->cmaptab,ginfo->cmapmemsz);
	if(total<0) { 
		// Maybe we can calculate the total section need for this bdf, then record it in pwrk.
		return total; 
	}else if(total!=ginfo->nglyphs)	
		return DLO_BAD_FONTDATA;

	return DLO_SUCCESS;
}

DT32_int bdf_uninitFont( DT_void *pattr )
{
DBG_MSG_SHOW_FUNC_NAME();

	return DLO_SUCCESS;
}


/* 2008.05.27: The reserved 9th parameter changed from (DT32_int flagxs) to (DT_void *op).	*/
/* It can be used for overwriting a specified part in a glyph.						*/
DT32_int bdf_getCharbmp(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int bmpw, DT32_int bmph, DT32_int x0, DT32_int y0, DT32_int xbytes, DT8_uchar *bmp, DT_void *op, DT32_int mode)
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *info = (Bdfginfo*)&bdfrasattr->info;
	pLayWrk pwrk = (pLayWrk)bdfrasattr->pwrk;
	Glyphinfo gf;
	bmpGlyfOperate *go=NULL;
	DT32_long from=0,gend;
	DT32_int ret,xpos,ypos,i, i1, j, start, start1, fxbyte=0, fxbits=0, xbits=0;
	DT8_uchar byteval, /*bitmask,*/ val=0, bb;
	//DT8_uchar rect[DLO_FONT_MAXSIZE*DLO_FONT_MAXSIZE/8];
	pDT_FontMgr_wrk	pmgrwrk=((DT_Font*)(pwrk->cur_DT_Font))->fontmgr;
	DT8_uchar *rect=NULL;
	DT32_int realh;	/* the real height of the bmp for the text. while bmph means the bmp buffer's height.	*/

DBG_MSG_SHOW_FUNC_NAME();

	ClearGlyph(&gf);

	if(op){	go = (bmpGlyfOperate *) op; }

	/*from = *(info->cmaptab+ch);*/
	from = GetCharStartinFile(ch,info->cmaptab);
	if(from!=0){
		ret=GetCharpart(bdfrasattr, info->fontdata, from, &gf, &gend);
		if(ret<0){
			if(pwrk->iconfontcnt>0){
				return pwrk->iconfuncs.getCharbmp(pwrk->icon_attr,ch,gseq2idx,bmpw,bmph,x0,y0,xbytes,bmp,op,mode);
			}
			//return 0;		// Modified_By_Jacky_20101213:
			return DLO_FONTSTYLE_ERROR;		// It should be bad format of fontdata. But we return this error instead.
		}
	}else{
		if(pwrk->iconfontcnt>0){
			return pwrk->iconfuncs.getCharbmp(pwrk->icon_attr,ch,gseq2idx,bmpw,bmph,x0,y0,xbytes,bmp,op,mode);
		}
		//return 0;		// Modified_By_Jacky_20101213:
		return DLO_EMPTY_FONT;
	}

	//ret = GetGlyfBMP(info, &gf, rect);	if(ret<0) return 0;
	realh = pwrk->lobuf->bufsize/Calxbytes(pwrk, pwrk->lobuf->bmpwidth);

	x0 += pwrk->lobuf->ltpos.x;
	//y0 += pwrk->lobuf->ltpos.y + CalcOffsetY_forbmph(pwrk, info->gFbbx.bby, 0, realh);
	//y0 += pwrk->lobuf->ltpos.y + CalcOffsetY_forbmph(pwrk, pwrk->fengfuncs.getAheight(pattr,ch), 0, realh);
	y0 += pwrk->lobuf->ltpos.y;
	if(pwrk->vert){
		// Should not get into here, because BDF doesn't support vert.
		if(pwrk->maxdifH>pwrk->xsize)	// bdf doesn't have edges.
			x0 -= CalcOffsetY_forbmph(pwrk, pwrk->xsize, 0, pwrk->maxdifH);
	}else{
		if(pwrk->maxdifH>pwrk->ysize)	// bdf doesn't have edges.
			y0 += CalcOffsetY_forbmph(pwrk, pwrk->ysize, 0, pwrk->maxdifH);
	}


	fxbyte = (gf.bbx.bbx + 7)/8;
	xpos = x0 + gf.bbx.bbxoff;
	ypos = (info->gFbbx.bby + info->gFbbx.bbyoff) - (gf.bbx.bbyoff + gf.bbx.bby);

	if(pwrk->attr->ucs_cnt==1 && xpos==0){
		ret = GetGlyfBMP(bdfrasattr, &gf, bmp, xbytes, y0+ypos);
		if(ret<0){
			//return 0;		// Modified_By_Jacky_20101213:
			return DLO_FONTSTYLE_ERROR;		// It should be bad format of fontdata. But we return this error instead.
		}else{
			return gf.mtrx.dw0.x;
		}
	}else{
		if(pmgrwrk->tmpbufsize < fxbyte*(info->gFbbx.bby+info->gFbbx.bbyoff)){
			//return 0;		// Modified_By_Jacky_20101213:
			return DLO_TEMPBUF_NOT_ENOUGH;
		}
		rect = (DT8_uchar*)pmgrwrk->tempbuf;
		//ClearBuf(rect,sizeof(rect));
		DT_memset(rect,0,fxbyte*(info->gFbbx.bby+info->gFbbx.bbyoff));

		ret = GetGlyfBMP(bdfrasattr, &gf, rect, fxbyte, 0);
		if(ret<0){ 
			//return 0;		// Modified_By_Jacky_20101213:
			return DLO_FONTSTYLE_ERROR;		// It should be bad format of fontdata. But we return this error instead.
		}
	}
	if(mode & DLO_LAYOUT_BIT){
	  xbits = xbytes*8;
	  fxbits= fxbyte*8;
	  start = (y0+ypos)*xbits + xpos;
	  start1= 0;
	  for(i=y0+ypos,i1=0;(i<bmph && i1<gf.bbx.bby);i++,i1++){
		  for(j=0;j<gf.bbx.bbx;j++){
		    if( (xpos+j) >= xbits )	break;
			val = (rect[(start1+j)>>3]>>(7-(j&7)))&0x01;
		    //bitmask = val<<(7-((xpos+j)&7));
		    byteval = *(bmp+((start+j)>>3));
			*(bmp+((start+j)>>3)) = bdfSetBitinBmp(val,byteval,xpos+j,DCW_COPYIFBKZERO);
		  }
		  start += xbits;
		  start1 += fxbits;
	  }
	  /* Deal with the rect specified, such as clear(DCW_SETBKZERO) */
	  /* Another way, you can check the first and end byte per line,*/
	  /* then set the bytes between first and end byte to zero.		*/
	  if(op){
		  go->bpoff.x += pwrk->lobuf->ltpos.x;	go->bpoff.y += pwrk->lobuf->ltpos.y;
		  for(i=go->bpoff.y;(i<bmph && i<go->bpoff.y+go->height);i++){
			for(j=go->bpoff.x;(j<xbytes*8 && j<go->bpoff.x+go->lenth);j++){
			  start = i*xbytes*8;
			  val = 0;	//bitmask = 0;
			  byteval = *(bmp+(start+j)/8);
			  bb = bdfSetBitinBmp(val,byteval,j,go->operate);
			  *(bmp+(start+j)/8) = bb;
			}
		  }
	  }
	}

	//return gf.mtrx.dw0.x;			// Modified_By_Jacky_20101213:
	return DLO_SUCCESS;

/*
	// These code moved from DIF_Raster.c, which still have some bugs. Need to deal with bbxoff, bbyoff
	DT32_int ret,xpos,ypos;
	DT32_int i,j,k,m,w=0,h=0,fxbyte=0,copyw=0,copybytes=0,copyh=0,xstart=0;
	DT8_uchar *rect=NULL;
	DT8_uchar *pbmp, *prect, *obmp, *orect;
	DT8_uchar tmpval, topgrade=0xFF, lmask=0xFF, rmask=0xFF, bmask=0x80;


	w = gf.bbx.bbx;
	h = gf.bbx.bby;

	if(op){
		go = (bmpGlyfOperate *) op;
		// Only DCW_SETBKZERO of go->operate will happen now. Do not copy the pixels.
		  if(DCW_SETBKZERO==go->operate){
			h = go->gpoff.y;
		  }
	}

	//x0 += pwrk->lobuf->ltpos.x;
	//y0 += pwrk->lobuf->ltpos.y;

	copyw = (bmpw-x0)>w?w:(bmpw-x0);
	copyh = (bmph-y0)>h?h:(bmph-y0);

	if(mode & DLO_LAYOUT_BIT){
		xstart = x0&7;	// xbytealign=0: x0 is at byte start position 
		if(!xstart){
			copybytes = (copyw+7)>>3;
			pbmp = obmp = bmp + y0*xbytes + x0;
			prect= orect= rect;
			for(j=0;j<copyh;j++){
				for(i=0;i<copybytes;i++){
					*pbmp++ |= *prect++;
				}
				obmp  += xbytes;	pbmp = obmp;
				orect += fxbyte;	prect= orect;
			}
		}else{
			pbmp = obmp = bmp + y0*xbytes + (x0>>3);
			prect= orect= rect;
			for(j=0;j<copyh;j++){
				for(i=0;i<copyw;i+=8){
					tmpval = *prect++;
					*pbmp++ |= (tmpval>>xstart);
					*pbmp |= (tmpval<<(8-xstart));
				}
				obmp  += xbytes;	pbmp = obmp;
				orect += fxbyte;	prect= orect;
			}			
		}

	}else if(mode & DLO_LAYOUT_BYTE){
		if(pwrk->grade==DLO_GRAY_16 && pwrk->grade_values==DLO_GRADE_INDEX_0X00_0X0F){
			topgrade = 0x0F;
		}
		pbmp = obmp = bmp + y0*xbytes + x0;
		prect= orect= rect;
		for(j=0;j<copyh;j++){
			for(i=0;i<copyw;i+=8){
				tmpval = *prect++;
				m = (copyw-i)>=8?8:(copyw-i);
				bmask = 0x80;
				for(k=0;k<m;k++){
					*pbmp++ |= ((tmpval&bmask)?topgrade:0);
					bmask >>= 1;
				}
			}
			obmp  += xbytes;	pbmp = obmp;
			orect += fxbyte;	prect= orect;
		}	
	}

	return w+pwrk->spacing;
*/
}

// Return 0 if ch does NOT exist.
// Return 1 if ch DOES exist.
DT32_int bdf_chkGlyphExist( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *info = (Bdfginfo*)&bdfrasattr->info;
	pLayWrk	 pwrk = (pLayWrk)bdfrasattr->pwrk;
	DT32_int aw=0;/*info->gMtrx.dw0.x;*/
	Glyphinfo gf;
	DT32_long start=0,gend;
	DT32_int ret;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)
			return pfc->codeExist;
	}
	
	ClearGlyph(&gf);
	start = GetCharStartinFile(ch,info->cmaptab);
	if(start!=0){
		ret=GetCharpart(bdfrasattr, info->fontdata, start, &gf, &gend);
		if(ret>=0){
			if(pfc){
				pfc->codeExist = 1;
				pfc->existFont = DLO_CUR_DT_FONT;	// don't support second bdf now, so it's always 1;
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
				// BDF won't scale, moveY, and no lrsb
				setDefault_Scale_LRsb_MoveY(pfc);
			}
			return 1;
		}else{
			if(pwrk->iconfontcnt>0){
				return pwrk->iconfuncs.chkGlyphExist(pwrk->icon_attr,ch,gseq2idx);
			}
			//return 0;
		}
	}else{
		if(pwrk->iconfontcnt>0){
			return pwrk->iconfuncs.chkGlyphExist(pwrk->icon_attr,ch,gseq2idx);
		}
		//return 0;
	}
	
	if(pfc /*&& !(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)*/){// not required, checked at func's beginning 
		pfc->codeExist = 0;
		pfc->existFont = 0;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;
		// BDF won't scale, moveY, and no lrsb
		setDefault_Scale_LRsb_MoveY(pfc);
	}
	return 0;
}

DT32_int bdf_getAwidth( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *info = (Bdfginfo*)&bdfrasattr->info;
	pLayWrk	 pwrk = (pLayWrk)bdfrasattr->pwrk;
	DT32_int aw=0;/*info->gMtrx.dw0.x;*/
	Glyphinfo gf;
	DT32_long start=0,gend;
	DT32_int ret=-1;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	/* For the font that don't contain space char (0x0020). */
//	switch(ch){
//	case 0x0020:
//		aw = info->gFbbx.bbx/2;
//		break;
//	default:
//		break;
//	}

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AW)
			return (pfc->aw==0 || pfc->aw==BDF_CODE_NOT_EXIST)?0:pfc->aw+pwrk->spacing;
	}

	ClearGlyph(&gf);
	start = GetCharStartinFile(ch,info->cmaptab);
	if(start!=0){
		ret=GetCharpart(bdfrasattr, info->fontdata, start, &gf, &gend);
		if(ret>=0){
			aw=gf.mtrx.dw0.x;
		}else{
			if(pwrk->iconfontcnt>0){
				/* bdf_getEdge() always return t, d, l, r edge=0, don't need to deal with. */
				return pwrk->iconfuncs.getAwidth(pwrk->icon_attr,ch,gseq2idx);
			}
		}
	}else{
		if(pwrk->iconfontcnt>0){
			/* bdf_getEdge() always return t, d, l, r edge=0, don't need to deal with. */
			return pwrk->iconfuncs.getAwidth(pwrk->icon_attr,ch,gseq2idx);
		}
		//return 0 /* + pwrk->spacing*/;	/* Jacky_20100824 */	// 20111031: Marked by Jacky, not required.
	}

	if(pfc){
		if(ret>=0){
			pfc->aw = aw;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AW;
			pfc->codeExist = 1;
			pfc->existFont = DLO_CUR_DT_FONT;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;	// also had been checked.
		}else{
			pfc->aw = BDF_CODE_NOT_EXIST;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AW;
			if(!(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)){
				pfc->codeExist = 0;
				pfc->existFont = 0;
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;	// also had been checked.
			}
		}
		// BDF won't scale, moveY, and no lrsb
		setDefault_Scale_LRsb_MoveY(pfc);
	}
	return (aw==0)?0:aw+pwrk->spacing;	/* Jacky_20100824 */
}

DT32_int bdf_getAwidth2(DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx, DT32_int *vx, DT32_int *vy)
{

DBG_MSG_SHOW_FUNC_NAME();

	/* Not implement yet. Maybe required when supporting vertical writedir. */
	return 0;
}

DT32_int bdf_getAheight( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx )
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *info = (Bdfginfo*)&bdfrasattr->info;
	pLayWrk	 pwrk = (pLayWrk)bdfrasattr->pwrk;
	Glyphinfo gf;
	DT32_long start=0,gend;
	DT32_int ret, height=0;
	FontCodeInfo *pfc = (gseq2idx>=0) ? &pwrk->g2info[gseq2idx] : NULL;

DBG_MSG_SHOW_FUNC_NAME();

	if(pfc){
		if(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_AH)
			return pfc->ah;
	}

	ClearGlyph(&gf);
	start = GetCharStartinFile(ch,info->cmaptab);
	if(start!=0){
		ret=GetCharpart(bdfrasattr, info->fontdata, start, &gf, &gend);
		if(ret>=0){
			//aw=gf.mtrx.dw0.x;
			height = info->gFbbx.bby;	//gf.bbx.bby;	// 2011-12-12: Jacky modified for not display completely.
		}
	}

	if(0==height){
		if(pwrk->iconfontcnt>0){
			return pwrk->iconfuncs.getAheight(pwrk->icon_attr,ch,gseq2idx);
		}
	}

	if(pfc){
		pfc->ah = height;
		pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_AH;
		if(ret >= 0){
			pfc->codeExist = 1;
			pfc->existFont = DLO_CUR_DT_FONT;
			pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;	// also had been checked here.
		}else{
			if(!(pfc->checkedFlag&DLO_FONTCODEINFO_CHECKFLAG_EXIST)){
				pfc->codeExist = 0;
				pfc->existFont = 0;
				pfc->checkedFlag |= DLO_FONTCODEINFO_CHECKFLAG_EXIST;	// also had been checked here.
			}
		}
		// BDF won't scale, moveY, and no lrsb
		setDefault_Scale_LRsb_MoveY(pfc);
	}

	return height;
}

DT32_int bdf_getLogh( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx)
{
	return 0;
}

DT32_int bdf_getLogt( DT_void *pattr, DT16_ushort ch, DT32_int gseq2idx)
{
	return 0;
}

DT32_int bdf_getHeight( DT_void *pattr )
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *info = (Bdfginfo*)&bdfrasattr->info;

DBG_MSG_SHOW_FUNC_NAME();

/*	DT32_int h=info->gFbbx.bby;
	Glyphinfo gf;
	DT32_long gend;
	DT32_int ret;
	ClearGlyph(&gf);
	ret=GetCharpart(bdfrasattr, info->fontdata, info->cmaptab[ch], &gf, &gend);
	if(ret>=0)	h=gf.bbx.bby;
*/
	return info->gFbbx.bby;
}

DT32_int bdf_getWidth( DT_void *pattr )
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *info = (Bdfginfo*)&bdfrasattr->info;

DBG_MSG_SHOW_FUNC_NAME();


	return info->gFbbx.bbx;
}

/* The difference between advanced width and width in global part. Just for estimation. */
DT32_int bdf_getExten( DT_void *pattr )
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *info = (Bdfginfo*)&bdfrasattr->info;
	DT32_int maxaw=0, maxwid=0, diff=0;	/* Jacky_20100621 */

DBG_MSG_SHOW_FUNC_NAME();

	maxwid = info->gFbbx.bbx + info->gFbbx.bbxoff;
	maxaw  = info->gMtrx.dw0.x;
	diff = (maxwid-maxaw)>0 ? (maxwid-maxaw) : 0;
	return diff;
	/*return info->gFbbx.bbx - info->gMtrx.dw0.x;*/
}

/* The difference between advanced width and glyph width. */
/* Added by Jacky_20090821 */
DT32_int bdf_getAexten( DT_void *pattr, DT16_ushort ch )
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo *info = (Bdfginfo*)&bdfrasattr->info;
	DT32_int wid=0,aw=0;
	Glyphinfo gf;
	DT32_long start=0,gend;
	DT32_int ret;

DBG_MSG_SHOW_FUNC_NAME();

	ClearGlyph(&gf);
	start = GetCharStartinFile(ch,info->cmaptab);
	if(start!=0){
		ret=GetCharpart(bdfrasattr, info->fontdata, start, &gf, &gend);
		if(ret>=0){
			wid=gf.bbx.bbx + gf.bbx.bbxoff;
			aw =gf.mtrx.dw0.x;
		}
	}
	return (wid>aw)?(wid-aw):0;	/* Modified by Jacky_20090925 */
}

/* The difference of the vertical extent between a normal font and a bold (Attr->f_edge!=0) font*/
/* Added by Jacky_20091023																		*/
/* It's not support in BDF font, so return 0 always.											*/
DT32_int bdf_getVexten( DT_void *pattr, DT16_ushort ch )
{	
DBG_MSG_SHOW_FUNC_NAME();

	return 0;
}

/* The edge width (difference between Bold and Normal font).*/
/* t:top-edge; d:down-edge; l:left-edge; r:right-edge		*/
/* return: 0:DLO_SUCCESS; <0:Error							*/
DT32_int bdf_getEdge( DT_void *pattr, DT32_int *t, DT32_int *d, DT32_int *l, DT32_int *r )
{
DBG_MSG_SHOW_FUNC_NAME();

	if(t)	*t=0;
	if(d)	*d=0;
	if(l)	*l=0;
	if(r)	*r=0;
	return DLO_SUCCESS;
}

/* Get fonts design information							*/
/* return value: 1: use default, 0: success, <0:error	*/
DT32_int bdf_getDesignInfo(DT_void *pattr, DT16_ushort gidx, DT32_int gseq2idx, DT32_int option, DT_void *dsninfo)
{
	BdfRaster_Attr *bdfrasattr = (BdfRaster_Attr*)pattr;
	Bdfginfo info, *bdfi;
	DT32_long nfrom, nend, nlen=0, nread=0;
	DT32_int rval, ret=0;
	BDFITEMNAME itemname;
	/*DT8_char line[512];*/
	DT8_char *line = bdfrasattr->line;
	DT8_char *fontdata;

DBG_MSG_SHOW_FUNC_NAME();

	bdfi = (Bdfginfo*) &bdfrasattr->info;
	fontdata = bdfi->fontdata;
	//ClearBuf(line,BDF_LINEBUF_SIZE);	//ClearBuf(line,sizeof(line));

	nfrom=0;
	while(1){
		ret=GetaLine(fontdata, nfrom, &nend, &nlen, line, 1);
		nread = nend - nfrom;
		if(ret==0){
			rval=ParseLine(bdfrasattr, line, nlen, &info, 0, BDF_GLOBAL_PART, &itemname);
			if(rval==1) break;
			else if(rval<0) return -2;

			if(itemname==gSTARTPROPERTIES){
				nfrom = nend;
				ParseProperties(bdfrasattr, dsninfo, fontdata, nfrom, info.proplines, &nend, &nread, line);
			}else if(itemname==gENDPROPERTIES){
				break;
			}
		}else if(ret==1) break;
		else if(ret<0) return -1;

		nfrom = nend;
		//ClearBuf(line,nlen);
	}
	return 0;
}

#endif	/* BDF_RASTER */
