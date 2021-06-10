/************************************************************************/
/*  Copyright 2010 by DynaComware Inc.									*/
/*  http://www.dynacw.com/												*/
/*  DigiTypeApi -- a font & text out solution for embedded systems.		*/
/************************************************************************/

#include "DigiTypeApi.h"

/****************************************************************************************************/
/* You can adjust the following values according to your needs:										*/
/* The qulifier "const" was removed from the following global variables declaration for the ability */
/* that users can decide these values in programs just before DT_InitDigiType() have been called.	*/
/* PLEASE DO NOT MODIFY THESE GLOBAL VARIABLES after DT_FontMgr has initialized (DT_InitDigiType()).*/
/****************************************************************************************************/

/****************************************************************************/
/****************** Memory Related Constant Value Settings ******************/
/****************************************************************************/

/*===== Memory Values Setting =====*/
#if (1==DT_OPENVG_ENABLED)
#define DT_MAXMEMORY_SIZE						(100*1024 + 0x20000)  /* Panasonic changed to use both DT_STYLE_NORMAL and DT_STYLE_OUTLINE */
#else
#define DT_MAXMEMORY_SIZE						0x20000		/* force the memory size that DigiTypeAPI can use when gDT_Set_Fix_Memory_Size==1 */
#endif
/*const*/ DT32_int  gDT_MAXMEMORY_SIZE			= DT_MAXMEMORY_SIZE;/* If you want to modify this value, please modify DT_MAXMEMORY_SIZE instead of this.				*/
															/* Or, you can modify this value according to conditions below: (This variable is used in DTplatform.c only)*/
															/* a. DT_ENABLE_MEMORY_H disabled and gDT_Set_Fix_Memory_Size=0: An invalid condition.						*/
															/* b. DT_ENABLE_MEMORY_H disabled and gDT_Set_Fix_Memory_Size=1: Re-map the source of wkmem is required.	*/
															/* c. DT_ENABLE_MEMORY_H enabled  and gDT_Set_Fix_Memory_Size=0: This value aren't used.					*/
															/* d. DT_ENABLE_MEMORY_H enabled  and gDT_Set_Fix_Memory_Size=1: This value can be modified directly.		*/
															/* In conditions b, d, if DT_CreateFontFromFile() will be called, and DT_LoadFontData() also uses			*/
															/* DT_loadfilecontent() to load fontfile, this value should count to include the file size of the fonts.	*/
															/* If you want to create 2 or more font handles(DT_Handle), this value needs to be double or more.			*/
															/* See details in DTplatform.h.																				*/

/**** Optimize memory usage of DigiTypeAPI for specified GrayBMP mode ****/
/*const*/ DT32_int gDT_Optimize_Mem_for_Gray16BMP= 1;	/* Please set this value in DTplatform.c			*/
											/* 0: default. gDT_MAXMEMORY_SIZE must larger than 256K.		*/
											/* 1: Optimize for DT_Gray16BMP_MODE. gDT_MAXMEMORY_SIZE>=128K	*/

#if (1==DT_OPENVG_ENABLED)
/*const*/ DT32_long gDT_TEMP_BUFFER_SIZE		= (5600);
#else
/*const*/ DT32_long gDT_TEMP_BUFFER_SIZE		= (0x9400);	/* memory size for temp use. See details in DTplatform.h												*/
															/* It must be larger than the square of (gDT_FONT_MAXSIZE+gDT_FONT_MAXITALIC+DT_STYLE_MAX_EDGE_WIDTH*2) in	*/
															/* DT_GRAYXXBMP_MODE.When DT_OUTLINE_MODE mode, this value won't be smaller than gDT_MAX_OUL_SIZE_PER_GLYPH.*/
															/* If you want to draw Hindi font, the size of (square)*4 is required. This value must be times of 4.		*/
#endif
/*const*/ DT32_int  gDT_Set_Fix_Memory_Size		= 1;		/* 0 or 1. See details in DTplatform.h										*/
															/* gDT_Set_Fix_Memory_Size must be 1, if DT_ENABLE_MEMORY_H isn't enabled.	*/
															/* If this is set to 1 and DT_ENABLE_STDIO is enabled, gDT_MAXMEMORY_SIZE	*/
															/* may need to include the font file size.									*/

/*===== The buffer for font bmp or outline data also affects memory usage =====*/
#if (1==DT_OPENVG_ENABLED)
/*const*/ DT32_int  gDT_Dont_Alloc_BmpBuf_When_CreateFont = 0;
/*const*/ DT32_int  gDT_MAX_BMPRECT_CNT_PER_STR = 1;
#else
/*const*/ DT32_int  gDT_Dont_Alloc_BmpBuf_When_CreateFont = 1;	/* 0 or 1. See details in DTplatform.h */
															/* 0: reserved the required memory; 1: don't reserved.		*/
/*const*/ DT32_int  gDT_MAX_BMPRECT_CNT_PER_STR = 50;		/* maximum count of font bmp rect. suggestion: same as DT_MAX_GLYPHS_PER_STR in DTplatform.h*/
															/* If gDT_Dont_Alloc_BmpBuf_When_CreateFont=0, enough memory for bmp rect will be reserved. */
															/* See details in DTplatform.h */
#endif
/*const*/ DT32_int  gDT_MAX_OUL_SIZE_PER_GLYPH	= (3000);	/* The size of the outline data buffer when DT_OUTLINE_MODE.*/
															/* This value is related to the FDL fontfile that you use,	*/
															/* please consult DynaComware before you modify this value.	*/
															/* See details in DTplatform.h */

/*===== Maximum font size and related values also affects memory usage =====*/
/*const*/ DT32_int	gDT_FONT_EMSIZE				= 1000;		/* EM size while DT_OUTLINE_MODE, avoid overflow by set this value.	*/
															/* It should be samller in the following case:						*/
															/* gDT_FONT_EMSIZE*DT_MAX_GLYPHS_PER_STR > limitation of DT_VGtype	*/
															/* Ex: if DT_SET_DATATYPE_FOR_VGPATH = 16, the limitation is 32768	*/
															/* if the DT_MAX_GLYPHS_PER_STR=100 and gDT_FONT_EMSIZE=512, might	*/
															/* cause the overflow issue (100*512>32768), so set this as 256 is	*/
															/* recommended.														*/
/*const*/ DT32_int	gSet_DT_FONT_SIZE_LIMIT		= 128;		/* The font size limit. If you enlarge this value, please	*/
															/* check if gDT_TEMP_BUFFER_SIZE is enough.					*/

/*===== Font Scaling & Moving's values also affects memory usage =====*/
/*const*/ DT32_int	gDT_FORCE_SCALE_RATIO		= 0;		/* Scale the chars in specified code range.		*/
															/* See details in DTplatform.h	*/
/*const*/ DT32_int	gDT_MoveArabicY				= 0;		/* Moving Arabic chars.			*/
															/* See details in DTplatform.h	*/
/*const*/ DT32_int	gDT_MoveThaiY				= 0;		/* Moving Thai char.			*/
															/* See details in DTplatform.h	*/

/*===== Maximum fonts count (Number of font files) also affects memory usage =====*/
/*const*/ DT32_int  gDT_FONTSLIST_MAXCNT		= 10;		/* Maximum fonts that DigiTypeAPI can handle. See details in DTplatform.h */ /* Panasonic changed this according to the current number of FDLs */

/*===== Font glyphs' maximum ratio may also affects memory usage  =====*/
/*const*/ DT32_int  gDT_MAX_SIZEXY_ASPECT_RATIO	= 1;		/* 1 as default. Do not modify it if you don't know what this stands for. */
															/* See details in DTplatform.h */

/*===== Default BiDirection Rule =====*/
/*const*/ DT32_int	gDT_DEFAULT_BIDI_RULE		= DT_BIDI_UNIRULE;/* Set the default BiDirection rule for parsing the string if DT_FSTYLE_BIDI_RULE isn't set.	*/
															/* v2.5.29: Hindi does not support DT_BIDI_UNIRULE yet. If you want to draw Hindi chars,			*/
															/* please call DT_SetFontStyle(hnd, DT_FSTYLE_BIDI_RULE, DT_BIDI_DCWRULE);							*/

/*===== Endianness, Run on Big-Endian or Little Endian =====*/
/*const*/ DT32_int	gDT_Endianness				= 0;		/* 0: little endian, 1: big endian 								*/
															/* This value will be auto-detected after DT_InitDigiType().	*/

/*===== Some special cases =====*/
/*const*/ DT32_int gDT_ENABLE_FAST_MODE			= 0;		/* 0: disable;	1:enable.		*/

#if (1==DT_OPENVG_ENABLED)
/*const*/ DT32_int gDT_MAX_SEGS_PER_GLYPH		= 400;		/* Used when OpenVG enabled (DT_OUTLINE_MODE) only.			*/
															/* This value is estimated from all the FDLs v2.5.29 used.	*/
/*const*/ DT32_int gDT_EachGlyphWidth_on_Pixels	= 0;		/* Used when OpenVG enabled (DT_OUTLINE_MODE) only.			*/
															/* 0: whole input string based on pixels,					*/
															/* 1: each glyph of the string is based on pixels.			*/
															/* If you want the bmpwidth same with GRAYxxBMP mode,		*/
															/* please set 1 and set gDT_FONT_EMSIZE=1000.				*/
/*const*/ DT32_int gDT_OVGWidth_Based_on_GBMPWidth=0;		/* Used when OpenVG enabled (DT_OUTLINE_MODE) only.					*/
															/* If you want to adjust the OVG's bmpwidth to be same as GrayBMP's,*/
															/* please set this =1, and gDT_EachGlyphWidth_on_Pixels=1, and		*/
															/* gDT_FONT_EMSIZE=1000, and DISABLE(don't use) L3 CACHE!!!			*/
#endif

/****************************************************************************/
/***************** Memory Related Functions Implementation ******************/
/****************************************************************************/

#ifdef DT_ENABLE_MEMORY_H
/****** stdlib header files *****/
#include <stdlib.h>
#include <memory.h>
#include <string.h>
  DT_void *g_mem=NULL;			/* Keep the memory allocated by system's malloc(), need to be free() when exit DigiTypeAPI	*/
#else
#ifndef WIN32
  #pragma _section B=noclr
#endif
  static DT8_uchar wkmem[DT_MAXMEMORY_SIZE];	/* The size must be same as gDT_MAXMEMORY_SIZE */
#endif

/****** Dcw SubMemory files *****/
#include "DTallocator.h"
struct allocator * submem=NULL; /* DigiTypeAPI internal used, don't modify it.	*/
DT_void *g_first_alloc=NULL;	/* Keep the first allocated address by DT_malloc(), which means DigiTypeAPI starts, use this*/
								/* address as a flag to know when to exit DigiTypeAPI and need to be free().				*/

/* a. DT_ENABLE_MEMORY_H disabled and gDT_Set_Fix_Memory_Size=0: An invalid condition.						*/
/* b. DT_ENABLE_MEMORY_H disabled and gDT_Set_Fix_Memory_Size=1: gDT_MAXMEMORY_SIZE (wkmem) will be used.	*/
/* c. DT_ENABLE_MEMORY_H enabled  and gDT_Set_Fix_Memory_Size=0: use system's memory functions directly.	*/
/* d. DT_ENABLE_MEMORY_H enabled  and gDT_Set_Fix_Memory_Size=1: gDT_MAXMEMORY_SIZE (g_mem) will be used.	*/
DT_void *DT_malloc(DT_size_t size )
{

DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_ENABLE_MEMORY_H
  if(1==gDT_Set_Fix_Memory_Size){
	if(submem){
		return DT_memory_alloc(submem,size,0/*not memset()*/);
	}else{
		/* The first time to alloc a block of memory, should be called from DT_InitDigiType() */
		g_mem = malloc(gDT_MAXMEMORY_SIZE);
		submem = DT_memory_init(g_mem, gDT_MAXMEMORY_SIZE, 1, DT_BLOCKSIZE);
		g_first_alloc = DT_memory_alloc(submem,size,0/*not memset()*/);
		return g_first_alloc;		
	}
  }else{
	return malloc(size);
  }
#else
  if(1==gDT_Set_Fix_Memory_Size){
	if(submem){
		return DT_memory_alloc(submem,size,0/*not memset()*/);
	}else{
		/* The first time to alloc a block of memory, should be called from DT_InitDigiType() */
		/* Use wkmem as the total memory that DigiTypeAPI can use.								 */
		submem = DT_memory_init(wkmem, gDT_MAXMEMORY_SIZE, 1, DT_BLOCKSIZE);
		g_first_alloc = DT_memory_alloc(submem,size,0/*not memset()*/);
		return g_first_alloc;
	}
  }else{
	return NULL;	/* Should be an error situation: no memory can be used. */
  }

#endif
}



DT_void *DT_realloc(DT_void *memblock, DT_size_t size )
{
DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_ENABLE_MEMORY_H
  if(1==gDT_Set_Fix_Memory_Size){
	if(submem){
		return DT_memory_realloc(submem,memblock,size);
	}else{
		/* The first time to alloc a block of memory, should be called from DT_InitDigiType()*/
		/* This won't happen, because DT_InitDigiType() will call DT_malloc() for first time.*/
		g_mem = malloc(gDT_MAXMEMORY_SIZE);
		submem = DT_memory_init(g_mem, gDT_MAXMEMORY_SIZE, 1, DT_BLOCKSIZE);
		g_first_alloc = DT_memory_alloc(submem,size,0);
		return g_first_alloc;
	}
  }else{
	return realloc(memblock,size);
  }
#else
  if(1==gDT_Set_Fix_Memory_Size){
	if(submem){
		return DT_memory_realloc(submem,memblock,size);
	}else{
		/* The first time to alloc a block of memory, should be called from DT_InitDigiType()*/
		/* This won't happen, because DT_InitDigiType() will call DT_malloc() for first time.*/
		submem = DT_memory_init(wkmem, gDT_MAXMEMORY_SIZE, 1, DT_BLOCKSIZE);
		g_first_alloc = DT_memory_alloc(submem,size,0);
		return g_first_alloc;
	}
  }else{
	return NULL;	/* Should be an error situation */
  }
#endif
}



DT_void DT_free( DT_void *memblock )
{
  DT32_int ret;

DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_ENABLE_MEMORY_H
  if(1==gDT_Set_Fix_Memory_Size){
	if(submem){
		if(memblock==g_first_alloc){
			/* Release all the submemory */
			free(g_mem);
			g_mem = NULL;
			g_first_alloc = NULL;
			submem = NULL;
		}else if((DT_size_t)memblock>(DT_size_t)submem && (DT_size_t)memblock<(DT_size_t)submem+gDT_MAXMEMORY_SIZE){	
			/* Release sub memory */
			ret = DT_memory_free(submem,memblock);
		}else{	
			/* The address isn't inside DCW SubMemory, redirect it to system's free(). */	
			free(memblock);
		}
	}
	return;
  }else{
	free(memblock);
  }
#else
  if(1==gDT_Set_Fix_Memory_Size){
	if(submem){
		if(memblock==g_first_alloc){
			/* Release all the submemory */
			/* Do Nothing, wkmem do not need to free. */
			g_first_alloc = NULL;
			submem = NULL;
		}else if((DT_size_t)memblock>(DT_size_t)submem && (DT_size_t)memblock<(DT_size_t)submem+gDT_MAXMEMORY_SIZE){	
			/* Release sub memory */
			ret = DT_memory_free(submem,memblock);
		}else{	
			/* The address isn't inside DCW SubMemory, redirect it to system's free(). */	
			/* Do Nothing, wkmem do not need to free. */
		}
	}
	return;
  }else{
	/* Do nothing */
  }	
#endif
}



/* value is not more than 0xFF in DigiTypeAPI.  */
DT_void *DT_memset( DT_void *ptr, DT32_int value, DT_size_t num )
{

#ifdef DT_ENABLE_MEMORY_H
DBG_MSG_SHOW_FUNC_NAME();

	return memset(ptr, value, num);

#else
	DT32_ulong val, bval;
	DT32_ulong *p;
	DT8_uchar  *pc=(DT8_uchar*)ptr;
	DT_size_t j, prebytes;

DBG_MSG_SHOW_FUNC_NAME();
	
	bval=(value&0xFF);
	val = bval<<24 | bval<<16 | bval<<8 | bval;
	
		  prebytes = (4-(((DT_size_t)ptr)&3))&3;
		  for(j=0;j<prebytes && j<num;j++){
			*pc++ = (DT8_uchar)bval;
		  }
		  p = (DT32_ulong *)pc;
		  for(;j+4<=num;j+=4){
			   *p++ = val; 
		  }
		  pc = (DT8_uchar*)p;
		  for(;j<num;j++){
			  *pc++ = (DT8_uchar)bval;
		  }
	return ptr;
#endif
}



/* It can be improved. Re-implement by detecting memory alignment.					*/
/* Now only 4 bytes aligned and count=multi-4bytes will be copied by 4bytes-based.	*/
DT_void *DT_memcpy( DT_void *dest, const DT_void *src, DT_size_t count )
{

#ifdef DT_ENABLE_MEMORY_H
	
DBG_MSG_SHOW_FUNC_NAME();

	return memcpy(dest, src, count);

#else
	DT32_ulong	*d, *s;
	DT16_ushort	*ds, *ss;
	DT8_uchar	*dc, *sc;
	DT_size_t	i, cnt;

DBG_MSG_SHOW_FUNC_NAME();

	if(!dest || !src || count<=0)
		return dest;

	if( !(((DT_size_t)dest)&3) && !(((DT_size_t)src)&3) && !(count&3) ){	
		cnt = count>>2;
		d = (DT32_ulong*)dest;
		s = (DT32_ulong*)src;
		for(i=0;i<cnt;i++){
			*d++ = *s++;
		}
	}else if(!(((DT_size_t)dest)&1) && !(((DT_size_t)src)&1) && !(count&1) ){
		cnt = count>>1;
		ds = (DT16_ushort*)dest;
		ss = (DT16_ushort*)src;
		for(i=0;i<cnt;i++){
			*ds++ = *ss++;
		}
	}else{
		dc = (DT8_uchar*) dest;
		sc = (DT8_uchar*) src;
		for(i=0;i<count;i++){
			*dc++ = *sc++;
		}
	}
	return dest;
#endif
}



/* string operate functions */
DT_size_t DT_strlen( const DT8_char *str )
{

#ifdef DT_ENABLE_MEMORY_H

DBG_MSG_SHOW_FUNC_NAME();

	return strlen(str);

#else
	DT8_char *p = (DT8_char*)str;
	DT_size_t len;

DBG_MSG_SHOW_FUNC_NAME();

	if(!p)
		return (0);

	while(1){
		if(!(*p++))
			break;
	}
	len = (DT_size_t)(p-str-1);
	return len<0?0:len;
#endif
}



/* DigiTypeAPI only use this func to know if it's the same string, so do not deal with >0 or <0 now. */
DT32_int DT_strncmp( const DT8_char *string1, const DT8_char *string2, DT_size_t count )
{

#ifdef DT_ENABLE_MEMORY_H

DBG_MSG_SHOW_FUNC_NAME();
	
	return strncmp(string1, string2, count);

#else
	DT_size_t cnt1, cnt2, i;
	DT8_char *p1, *p2;

DBG_MSG_SHOW_FUNC_NAME();

	p1 = (DT8_char*)string1;	cnt1 = DT_strlen(string1);
	p2 = (DT8_char*)string2;	cnt2 = DT_strlen(string2);

	if(cnt1<=0 || cnt2<=0){
		return p1 - p2;
	}
	if(count>cnt1 || count>cnt2){
		return p1 - p2;
	}

	for(i=0;i<count;i++){
		if(*p1++ != *p2++)
			return p1 - p2;
	}

	return 0;
#endif
}

/****************************************************************************/
/**************** File I/O Related Functions Implementation *****************/
/****************************************************************************/

#ifdef DT_ENABLE_STDIO
#include <stdio.h>

/* FILE operate functions */
DT_FILE *DT_fopen( const DT8_char *filename, const DT8_char *mode )
{
DBG_MSG_SHOW_FUNC_NAME();

	return fopen(filename, mode);
}

DT_size_t DT_fread ( DT_void *ptr, DT_size_t size, DT_size_t count, DT_FILE *stream )
{
DBG_MSG_SHOW_FUNC_NAME();

	return fread(ptr, size, count, stream);
}

DT8_char *DT_fgets( DT8_char *str, DT32_int n, DT_FILE *stream )
{
DBG_MSG_SHOW_FUNC_NAME();

	return fgets(str, n, stream);
}

DT32_int DT_fclose ( DT_FILE *stream )
{
DBG_MSG_SHOW_FUNC_NAME();

	return fclose(stream);
}

DT32_int DT_feof ( DT_FILE *stream )
{
DBG_MSG_SHOW_FUNC_NAME();

	return feof(stream);
}

DT32_int DT_ferror ( DT_FILE *stream )
{
DBG_MSG_SHOW_FUNC_NAME();

	return ferror(stream);
}

DT32_int DT_fseek ( DT_FILE *stream, DT32_long offset, DT32_int origin )
{
DBG_MSG_SHOW_FUNC_NAME();

	return fseek(stream, offset, origin);
}

DT_void DT_rewind( DT_FILE *stream )
{
DBG_MSG_SHOW_FUNC_NAME();

	rewind(stream);
}

DT32_long DT_ftell( DT_FILE *stream )
{
DBG_MSG_SHOW_FUNC_NAME();

	return ftell(stream);
}

/*#define DT_MY_ASSIGNED_ICONFONT*/
#ifdef DT_MY_ASSIGNED_ICONFONT
/* Now we have only the DcwIconFont.h but not a really DcwIconFont.dif file.			*/
/* So use these to distinguish if the filename should be load from .dif file or by .h	*/
#include "DcwIconFont.h"
static const	DT8_uchar fontDIF[]="DcwIconFont.dif";

DT32_int isDcwIconFont(DT8_char	*filename, DT32_int nlen)
{
	DT32_int ret=0;
	DT32_int fnamestart = nlen - (sizeof(fontDIF)-1);	/* only compare the file name, path isn't include. */
	DT8_char *fname = filename+fnamestart;

DBG_MSG_SHOW_FUNC_NAME();

	if(fnamestart>=0){
		if(!DT_strncmp(fname,fontDIF,(sizeof(fontDIF)-1))){
			ret = 1;
		}
	}
	return ret;
}
#endif
/*--------------------------------------------------------------*/
/* Load file content function: you can modify this function to load font from a file.							*/
/* This function will be called inside DT_CreateFontFromFile() through DT_LoadFontData().						*/
/* "fontdata" & "nfsize" of 1st param "font" (DT_Font) will be set as "buf" and "bufsize" after this function.	*/
/* Please return 1 as success; others as error.																	*/
/* fontname	: [in]font file path, it will point to the "fontfile" of DT_FontFile in DT_CreateFontFromFile().	*/
/*			  You can use this as an identifier.																*/
/* nlen		: [in]the length of "fontname".																		*/
/* buf		: [out]	please set it as the address of the pointer that point to font data.						*/
/*			  "fontdata" of DT_Font will point to this font data if this function return success.				*/
/* bufsize	: [out]the size of buf(font data). "nfsize" of DT_Font will be set to this value.				 	*/
/* used to load font file content.											*/
/* Return value: -1:Open file error; 0:Load file content Error; 1:Success.	*/
DT32_int DT_loadfilecontent(DT_void *fontname, DT32_int nlen, DT8_char **buf, DT32_long *bufsize)
{
	DT_FILE		*stream=NULL;
	DT32_ulong	datasize = 0;
	DT8_char	*databuf=NULL;
	DT8_char	*tmpptr=NULL;
	DT32_int	i,nread,ret;
	DT8_char	*filename = (DT8_char*)fontname;

DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_MY_ASSIGNED_ICONFONT
	if(isDcwIconFont(filename,nlen)){
		*buf = (DT8_char*)iconfontdata;	/* char array inside DcwIconFont.h */
		*bufsize = sizeof(iconfontdata);
		return 1;
	}
#endif
	stream = DT_fopen(filename,"rb");
	if(stream){	
		if(DT_fseek(stream, 0, DT_SEEK_END))
		{
			DT_fclose(stream);
			return -1;
		}
		datasize = DT_ftell(stream);	
		if(datasize < 0)
		{
			DT_fclose(stream);
			return -1;
		}

		DT_rewind(stream);

		databuf = DT_malloc(DT_ALLOC_SIZE(datasize));
		if(!databuf)
		{
			/* If it runs into here, and gDT_Set_Fix_Memory_Size=1, please check the value of gDT_MAXMEMORY_SIZE.		*/
			/* Make sure it's enough for DT_FMEMORY_FONTMANAGER + DT_FMEMORY_CREATEFONT + the fontfile going to be load.*/
			DT_fclose(stream);
			return -1;
		}

		i=0; nread=0; ret=0;
		while( !DT_feof(stream) ){
			tmpptr = databuf + i*BUFSIZ;
			/*DT_memset(tmpptr,0,BUFSIZ);*/
			nread = DT_fread(tmpptr,sizeof(DT8_char),BUFSIZ,stream);
			if( DT_ferror(stream) ){
				ret = -1;
				break;
			}else{
				i++;
			}
		}

		if( ret>=0 ){
			ret = 1;
		}else{
			if(databuf)	DT_free(databuf);
			databuf = NULL;
			datasize= 0;
			ret = 0;
		}
	}else 
		return -1;

	DT_fclose(stream);

	*buf = databuf;
	*bufsize = datasize;

	return ret;
	
}
/*
DT32_int DT_loadfilecontent(DT_void *fontname, DT32_int nlen, DT8_char **buf, DT32_long *bufsize)
{
	DT_FILE		*stream=NULL;
	DT32_ulong	allocsize;
	DT32_ulong	datasize = 0;
	DT8_char	*databuf=NULL;
	DT8_char	*tmpptr=NULL;
	DT32_int	i,nread,ret;
	DT8_char	*filename = (DT8_char*)fontname;

DBG_MSG_SHOW_FUNC_NAME();

	if(isDcwIconFont(filename,nlen)){
		*buf = (DT8_char*)iconfontdata;
		*bufsize = sizeof(iconfontdata);
		return 1;
	}

	stream = DT_fopen(filename,"rb");
	if(stream){
		i=0; nread=0; ret=0;
		tmpptr = databuf;				
		
		while( !DT_feof(stream) ){
			allocsize = BUFSIZ*(i+1);
			databuf = (DT8_char*) DT_realloc( databuf, DT_ALLOC_SIZE(sizeof(DT8_char)*allocsize) );		
			if( !databuf ){
				ret = -1;
				break;
			}

			tmpptr = databuf + i*BUFSIZ;
			DT_memset(tmpptr,0,BUFSIZ);
			nread = DT_fread(tmpptr,sizeof(DT8_char),BUFSIZ,stream);
			if( DT_ferror(stream) ){
				ret = -1;
				break;
			}else{
				datasize += nread;	
				i++;
			}
		}

		if( databuf!=NULL && datasize>0 && ret>=0){
			ret = 1;
		}else{
			if(databuf)	DT_free(databuf);
			databuf = NULL;
			datasize= 0;
			ret = 0;
		}
	}else 
		return -1;

	DT_fclose(stream);

	*buf = databuf;
	*bufsize = datasize;

	return ret;
	
}
*/

/*--------------------------------------------------------------*/
/* Release content function: a balance function of DT_loadfilecontent()		*/
/* This function will be called inside DT_DestroyFont().					*/
/* Please refer to DT_loadfilecontent()	for details of the parameters		*/
/* unload file content */
DT_void DT_unloadfilecontent(DT_void *fontname, DT32_int nlen, DT8_char *buf, DT32_long bufsize)
{
DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_MY_ASSIGNED_ICONFONT
	if(isDcwIconFont((DT8_char*)fontname,nlen)){
		/* No need to free */
		buf=NULL;
		return;
	}
#endif

	if(buf)	DT_free(buf);
	buf=NULL;
}

#else /*DT_ENABLE_STDIO*/

#include "DTfontdata.h"  /* Panasonic changed this */

typedef struct _DT_FontFileInfo
{								/* Reference to DT_Font to get the members' meaning.				*/
	const DT8_char	*fontname;	/* font file name or something to distinguish font, max 256 bytes.	*/
	DT32_int	nlen;			/* length of fontname, do not contain terminated NULL				*/
	DT8_char	*fontdata;		/* point to font data												*/
	DT32_long	nfsize;			/* fontdata size in bytes											*/
	DT32_int	sizex;			/* font sizex of the font file if you know.							*/
	DT32_int	sizey;			/* font sizey of the font file if you know.							*/
}DT_FontFileInfo, *pDT_FontFileInfo;

static const	DT8_char fontFDL0[]="UCS-CNS-PUD_W4_SYMBOL_MIX.FDL";  /* Panasonic changed this block */
static const	DT8_char fontFDL1[]="UcsJIS0208-UD-Hei-W4.FDL";
static const	DT8_char fontFDL2[]="UcsGB18030-Hei-W4.FDL";
static const	DT8_char fontFDL3[]="UcsBIG5-Hei-W4.FDL";
static const	DT8_char fontFDL4[]="UcsKSC5601-Hei-W4.FDL";
static const	DT8_char fontFDL5[]="UCS-CNS-ARABIC.FDL";
static const	DT8_char fontFDL6[]="UCS-CNS-THAI_HEI.FDL";
static const	DT8_char fontFDL7[]="UCS_CNS_HINDI_HEI.FDL";
static const	DT8_char fontFDL8[]="UCS-CNS-Ascii500_sample.FDL";
static const	DT8_char fontDIF[]="DcwIconFont.dif";

static const DT_FontFileInfo myfontlist[]={
	/* Panasonic changed this array */
	{ fontFDL0,	sizeof(fontFDL0)-1,	(DT8_char*)UCS_CNS_PUD_W4_SYMBOL_MIX_FDL,	sizeof(UCS_CNS_PUD_W4_SYMBOL_MIX_FDL),	 0,  0	},
	{ fontFDL1,	sizeof(fontFDL1)-1,	(DT8_char*)UCS_JIS_HEI_W4_FDL,	sizeof(UCS_JIS_HEI_W4_FDL),	 0,  0	},
	{ fontFDL2,	sizeof(fontFDL2)-1,	(DT8_char*)Ucs_GB_Hei_W4_Part_FDL,	sizeof(Ucs_GB_Hei_W4_Part_FDL),	 0,  0	},
	{ fontFDL3,	sizeof(fontFDL3)-1,	(DT8_char*)Ucs_Big5_Hei_W4_Part_FDL,	sizeof(Ucs_Big5_Hei_W4_Part_FDL),	 0,  0	},
	{ fontFDL4,	sizeof(fontFDL4)-1,	(DT8_char*)Ucs_Hangul_Hei_W4_Part_FDL,	sizeof(Ucs_Hangul_Hei_W4_Part_FDL),	 0,  0	},
	{ fontFDL5,	sizeof(fontFDL5)-1,	(DT8_char*)UCS_CNS_ARABIC_FDL,	sizeof(UCS_CNS_ARABIC_FDL),	 0,  0	},
	{ fontFDL6,	sizeof(fontFDL6)-1,	(DT8_char*)UCS_CNS_THAI_FDL,	sizeof(UCS_CNS_THAI_FDL),	 0,  0	},
	{ fontFDL7,	sizeof(fontFDL7)-1,	(DT8_char*)UCS_CNS_HINDI_FDL,	sizeof(UCS_CNS_HINDI_FDL),	 0,  0	},
	{ fontFDL8,	sizeof(fontFDL8)-1,	(DT8_char*)UCS_CNS_Ascii500_sample_FDL,	sizeof(UCS_CNS_Ascii500_sample_FDL),	 0,  0	},
	{ fontDIF,	sizeof(fontDIF)-1,	(DT8_char*)iconfontdata,		sizeof(iconfontdata),		32, 24	}
};

#endif /*DT_ENABLE_STDIO*/




/****************************************************************************/
/***************** Debug Message Functions Implementation *******************/
/****************************************************************************/

#ifdef DT_MY_DBG_MSG	/* See details in DTplatform.h */
#include <syslog.h>
/* "tail -f /var/log/messages | grep digitype" or "tail -f /var/log/syslog | grep digitype" to view it. */

DT_void my_dbg_msg_int(DT32_int n)
{
	openlog("digitype", LOG_CONS | LOG_PID, 0);
	syslog(LOG_INFO, "=> %d \n", n);
	closelog();
}

DT_void my_dbg_msg_str(const DT8_char *str)
{
	my_estimate_stack(str);
	openlog("digitype", LOG_CONS | LOG_PID, 0);
	syslog(LOG_INFO, "=> %s \n", str);
	closelog();
}

static DT32_ulong stack_at_init=0;
static DT32_ulong max_stack_add=0;

DT_void my_estimate_stack(const DT8_char *str)
{
	DT32_ulong add;
	add = (DT32_ulong)&add;

	if(!stack_at_init){
		max_stack_add = stack_at_init = add;
		openlog("digitype-stack", LOG_CONS | LOG_PID, 0);
		syslog( LOG_INFO, "==>Stack count start at Function:%s() stack_at_init=max_stack_add=add=%u \n", 
			str, add);
		closelog();
	}
	if( add < max_stack_add){
		openlog("digitype-stack", LOG_CONS | LOG_PID, 0);
		syslog( LOG_INFO, "==>Stack increase %u at Function:%s() stack_at_init=%u, max_stack_add=%u, add=%u \n", 
			max_stack_add-add, str, stack_at_init, max_stack_add, add);
		closelog();
		max_stack_add = add;
	}
}

DT_void my_estimate_stack_show()
{
	openlog("digitype-stack", LOG_CONS | LOG_PID, 0);
	syslog( LOG_INFO, "=>stack_at_init=%u, max_stack_add=%u \n", 
			stack_at_init, max_stack_add);
	closelog();
}

#else

static DT32_ulong stack_at_init=0;
static DT32_ulong max_stack_add=0;

DT_void my_estimate_stack()
{
	DT32_ulong add;
	add = (DT32_ulong)&add;

	if(!stack_at_init){
		max_stack_add = stack_at_init = add;
	}
	if( add < max_stack_add){
		max_stack_add = add;
	}
}
#endif

/*
#ifdef DT_WIN32
#include <Windows.h>
DT8_char dbgmsg[512];

DT_void my_dbg_msg_int(DT32_int n)
{
	DT_memset(dbgmsg,0,512);
	sprintf(dbgmsg,"=> %d", n);
	OutputDebugString(dbgmsg);
}

DT_void my_dbg_msg_str(const DT8_char *str)
{
	my_estimate_stack(str);
	DT_memset(dbgmsg,0,512);
	sprintf(dbgmsg,"=> %s", str);
	OutputDebugString(dbgmsg);
}
#else
#endif
*/
/******************************************************************************************************************/


/*==========================================================================================================*/
/*					Something required for implementing the functions defined in DTplatform.h				*/
/*==========================================================================================================*/

#ifdef DT_WIN32

/* Platform Dependent drawing funtions */
DT32_ulong myDT_convColor(DT_RGBA *color)
{
	DT32_ulong r,g,b,a;

DBG_MSG_SHOW_FUNC_NAME();

	a = (DT32_ulong)color->a<<24;
	r = (DT32_ulong)((color->r*color->a)/255)<<16;	/*pre-multiplied, estimated, r*a/255 */
	g = (DT32_ulong)((color->g*color->a)/255)<<8;	/*pre-multiplied, estimated, g*a/255 */
	b = (DT32_ulong)((color->b*color->a)/255);		/*pre-multiplied, estimated, b*a/255 */

	return  (DT32_ulong) r | g | b | a;
}

DT_void myDT_CopyBits(DT_DrawData *drawdata, DT32_ulong *bits, DT32_int x0, DT32_int y0, DT32_int bufw, DT32_int bufh)
{
	DT_RGBA fc=drawdata->fontcolor;
	DT32_int i,j,k;
	DT32_int	copyw, copyh;
	DT8_uchar	*pbmp, *pbmp_start;
	DT32_ulong	*pvbits, *pvbits_start;
	DT8_uchar	bidx;

	DT32_ulong	pix1;
	DT32_ulong	pixcolortab[256];
	DT32_ulong	*pixcolor;

DBG_MSG_SHOW_FUNC_NAME();

	if(drawdata->grade==DT_GRAY_MONO){
		fc.a = 0xFF;
		pix1 = myDT_convColor(&fc);

		pbmp = pbmp_start = drawdata->bmpbuf;
		pvbits = pvbits_start = bits + bufw*y0 + x0;

		copyw = drawdata->xbytes;
		if((copyw<<3)>(bufw-x0))
			copyw = (bufw-x0+7)>>3;

		copyh = drawdata->nHeight;
		if(copyh>bufh-y0)
			copyh = bufh-y0;

		for(j=0;j<copyh;j++){
			for(i=0;i<copyw;i++){
				bidx = 0x80;
				for(k=0;k<8;k++){
					*pvbits++ = ((*pbmp)&(bidx>>k))?pix1:0;
				}
				*pbmp++;
			}
			pbmp_start += drawdata->xbytes;
			pbmp = pbmp_start;
			pvbits_start += bufw;
			pvbits = pvbits_start;
		}
	}else if(drawdata->grade==DT_GRAY_16 && drawdata->grade_values==DT_GRADE_INDEX_0X00_0X0F){
		pixcolor = (DT32_ulong*) pixcolortab;
		for(k=0;k<16;k++){
			fc.a = k*0x11;
			*pixcolor++ = myDT_convColor(&fc);
		}
		pixcolor = (DT32_ulong*) pixcolortab;
		pbmp = pbmp_start = drawdata->bmpbuf;
		pvbits = pvbits_start = bits + bufw*y0 + x0;

		copyw = drawdata->nWidth;
		if(copyw>bufw-x0)
			copyw = bufw-x0;

		copyh = drawdata->nHeight;
		if(copyh>bufh-y0)
			copyh = bufh-y0;

		for(j=0;j<copyh;j++){
			for(i=0;i<copyw;i++){
				*pvbits++ = *(pixcolor + (*pbmp++));
			}
			pbmp_start += drawdata->xbytes;
			pbmp = pbmp_start;
			pvbits_start += bufw;
			pvbits = pvbits_start;
		}
	}else{
		pixcolor = (DT32_ulong*) pixcolortab;
		for(k=0;k<256;k++){
			fc.a = k;
			*pixcolor++ = myDT_convColor(&fc);
		}
		pixcolor = (DT32_ulong*) pixcolortab;
		pbmp = pbmp_start = drawdata->bmpbuf;
		pvbits = pvbits_start = bits + bufw*y0 + x0;

		copyw = drawdata->nWidth;
		if(copyw>bufw-x0)
			copyw = bufw-x0;

		copyh = drawdata->nHeight;
		if(copyh>bufh-y0)
			copyh = bufh-y0;
		
		for(j=0;j<copyh;j++){
			for(i=0;i<copyw;i++){
				*pvbits++ = *(pixcolor + (*pbmp++));
			}
			pbmp_start += drawdata->xbytes;
			pbmp = pbmp_start;
			pvbits_start += bufw;
			pvbits = pvbits_start;
		}
	}
}

/* Make the bmp's info header. */
DT_void MakeBitmapInfo32(BITMAPINFOGRAY *bmpgrayinfo, RGBQUAD *palette, DT_DrawData *drawdata)
{
/*	DT32_int i;
	DT_RGBA fc=drawdata->fontcolor;
	DT_RGBA bc=drawdata->backcolor;
*/
DBG_MSG_SHOW_FUNC_NAME();

	DT_memset(bmpgrayinfo, 0, sizeof(BITMAPINFO));
   /* Bitmap info header */
	bmpgrayinfo->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmpgrayinfo->bmiHeader.biWidth       = drawdata->nWidth;
	bmpgrayinfo->bmiHeader.biHeight      = -drawdata->nHeight;
	bmpgrayinfo->bmiHeader.biPlanes      = 1;
	bmpgrayinfo->bmiHeader.biBitCount    = 32;/*drawdata->bitcount;*/
	bmpgrayinfo->bmiHeader.biCompression = BI_RGB;
	bmpgrayinfo->bmiHeader.biSizeImage   = drawdata->nWidth*drawdata->nHeight*sizeof(DT32_ulong);/*drawdata->bmpsize;*/
}

/* Draw a bmp (gray or none) to screen. Please implement this function according to your target platform.	*/
/* Return Value: 0:DT_SUCCESS; <0:error																		*/
DT32_int myDT_BitBlt32(DT_void *hdcDest,		/* handle to destination DC					*/
					DT32_int nXDest,		/* x-coord of destination upper-left corner */
					DT32_int nYDest,		/* y-coord of destination upper-left corner */
					DT32_int nWidthDest,	/* width of destination rectangle			*/
					DT32_int nHeightDest,	/* height of destination rectangle			*/
					DT_DrawData *bmpdata,	/* the data to be drawn						*/
					DT_void **userdata		/* typecast to your own type struct, by pass from DT_RasterBitBlt()*/
)
{
	DT32_int ret=DT_SUCCESS;
	HDC mdc;
	BITMAPINFOGRAY bmpinfo;
	HBITMAP bmp, poldbmp;
	DT32_ulong *FBmpBuf=NULL;
	RGBQUAD pal[256];
	COLORREF bc;

	BLENDFUNCTION bf;
	myDT_32BITBMP_img *img = (myDT_32BITBMP_img *)*userdata;

DBG_MSG_SHOW_FUNC_NAME();
	
	if(!bmpdata->bmpbuf)
		return DT_SUCCESS;

	/* Create a compatible memory DC */
	bc = RGB(bmpdata->backcolor.r, bmpdata->backcolor.g, bmpdata->backcolor.b);

	if(myDT_DRAW_32BITBMP & img->flag){
		mdc = CreateCompatibleDC(NULL);
		SetBkColor(mdc,bc/*WHITENESS*/);
	 
		/* Create bitmap */
		MakeBitmapInfo32(&bmpinfo,pal,bmpdata);
		bmp = CreateDIBSection(mdc, (BITMAPINFO*)&bmpinfo, DIB_RGB_COLORS,	(DT_void**)&FBmpBuf, NULL, 0);
		if(!bmp){
			DeleteDC(mdc);
			return DT_BITBLT_ERR;
		}

		/* Select the bitmap into the DC */
		poldbmp = (HBITMAP)SelectObject(mdc,bmp);

		/* Copy (BitBlt) bitmap from memory DC to virtual screen DC. */
		myDT_CopyBits(bmpdata, FBmpBuf, 0, 0, bmpdata->nWidth, bmpdata->nHeight);

		if(nWidthDest==0)
			nWidthDest = bmpdata->nWidth;
		if(nHeightDest==0)
			nHeightDest= bmpdata->nHeight;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0x01;/*AC_SRC_ALPHA;*/
		bf.SourceConstantAlpha = 0xff;
			
		ret = AlphaBlend(hdcDest,nXDest,nYDest,nWidthDest,nHeightDest,
						 mdc,0,0,bmpdata->nWidth,bmpdata->nHeight,bf);
		
		SelectObject( mdc,poldbmp );
		DeleteObject(bmp);
		DeleteObject(poldbmp);
		DeleteDC(mdc);	
	}
	
	if(myDT_GET_32BITBMP & img->flag){
			MakeBitmapInfo32(&img->bmpinfo,bmpinfo.bmiColors,bmpdata);
			myDT_CopyBits(bmpdata, img->pvbits, nXDest, nYDest, img->bufw, img->bufh);
	}

	return ret;
}

/* Make the bmp's info header. */
DT_void MakeBitmapInfo(BITMAPINFOGRAY *bmpgrayinfo, RGBQUAD *palette, DT_DrawData *drawdata)
{
	DT32_int i;
	DT_RGBA fc=drawdata->fontcolor;
	DT_RGBA bc=drawdata->backcolor;

DBG_MSG_SHOW_FUNC_NAME();

	DT_memset(bmpgrayinfo, 0, sizeof(BITMAPINFO));
   /* Bitmap info header */
	bmpgrayinfo->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bmpgrayinfo->bmiHeader.biWidth       = drawdata->nWidth;
	bmpgrayinfo->bmiHeader.biHeight      = -drawdata->nHeight;
	bmpgrayinfo->bmiHeader.biPlanes      = 1;
	bmpgrayinfo->bmiHeader.biBitCount    = drawdata->bitcount;
	bmpgrayinfo->bmiHeader.biCompression = 0;
	bmpgrayinfo->bmiHeader.biSizeImage   = drawdata->bmpsize;

	/* Color palette */
	DT_memset(palette,0,sizeof(RGBQUAD)*256);
	if(drawdata->grade==DT_GRAY_MONO){
	  for(i=0; i<2; i++){
		palette[i].rgbBlue     = (i==0)?bc.b:fc.b;
        palette[i].rgbGreen    = (i==0)?bc.g:fc.g;
        palette[i].rgbRed      = (i==0)?bc.r:fc.r;
        palette[i].rgbReserved = fc.a;		
	  }
	  DT_memcpy(&bmpgrayinfo->bmiColors,palette,sizeof(RGBQUAD)*2);
	}else if(drawdata->grade==DT_GRAY_16 && drawdata->grade_values==DT_GRADE_INDEX_0X00_0X0F){
	  for(i=0; i<16; i++){
		palette[i].rgbBlue     = bc.b + (fc.b-bc.b)*i*0x11/255;
        palette[i].rgbGreen    = bc.g + (fc.g-bc.g)*i*0x11/255;
        palette[i].rgbRed      = bc.r + (fc.r-bc.r)*i*0x11/255;
        palette[i].rgbReserved = fc.a;		
	  }
	  DT_memcpy(&bmpgrayinfo->bmiColors,palette,sizeof(RGBQUAD)*16);
	}else/* if(drawdata->grade==DT_GRAY_256)*/{
	  for(i=0; i<256; i++){
		palette[i].rgbBlue     = bc.b + (fc.b-bc.b)*i/255;
        palette[i].rgbGreen    = bc.g + (fc.g-bc.g)*i/255;
        palette[i].rgbRed      = bc.r + (fc.r-bc.r)*i/255;
        palette[i].rgbReserved = fc.a;		
	  }
	  DT_memcpy(&bmpgrayinfo->bmiColors,palette,sizeof(RGBQUAD)*256);
	}
	
}

/* Draw a bmp (gray or none) to screen. Please implement this function according to your target platform.	*/
/* Return Value: 0:DT_SUCCESS; <0:error																		*/
DT32_int myDT_BitBlt(DT_void *hdcDest,		/* handle to destination DC					*/
					DT32_int nXDest,		/* x-coord of destination upper-left corner */
					DT32_int nYDest,		/* y-coord of destination upper-left corner */
					DT32_int nWidthDest,	/* width of destination rectangle			*/
					DT32_int nHeightDest,	/* height of destination rectangle			*/
					DT_DrawData *bmpdata,	/* the data to be drawn						*/
					DT_void **userdata		/* typecast to your own type struct, by pass from DT_RasterBitBlt()*/
)
{
	HDC mdc;
	BITMAPINFOGRAY bmpinfo;
	HBITMAP bmp, poldbmp;
	DT8_uchar *FBmpBuf=NULL;
	RGBQUAD pal[256];
	COLORREF bc;

DBG_MSG_SHOW_FUNC_NAME();

	/* If userdata exists, assume it will be drawn by 32 bit bmp. You can define your own userdata to check it. */
	if(userdata){	
		return myDT_BitBlt32(hdcDest,nXDest,nYDest,nWidthDest,nHeightDest,bmpdata,userdata);
	}

	if(!hdcDest)
		return DT_BITBLT_ERR;

	if(!bmpdata->bmpbuf)
		return DT_SUCCESS;
	
	
	/* Create a compatible memory DC */
	bc = RGB(bmpdata->backcolor.r, bmpdata->backcolor.g, bmpdata->backcolor.b);
	mdc = CreateCompatibleDC(NULL);
	SetBkColor(mdc,bc/*WHITENESS*/);
	 
	/* Create bitmap */
	MakeBitmapInfo(&bmpinfo,pal,bmpdata);
	bmp = CreateDIBSection(mdc, (BITMAPINFO*)&bmpinfo, DIB_RGB_COLORS,	(DT_void**)&FBmpBuf, NULL, 0);

	/* Select the bitmap into the DC */
	poldbmp = (HBITMAP)SelectObject(mdc,bmp);

	/* Copy (BitBlt) bitmap from memory DC to virtual screen DC. */
	DT_memcpy(FBmpBuf,bmpdata->bmpbuf,bmpdata->bmpsize);

	if(nWidthDest==0)
		nWidthDest = bmpdata->nWidth;
	if(nHeightDest==0)
		nHeightDest= bmpdata->nHeight;
	TransparentBlt(hdcDest, nXDest, nYDest, nWidthDest, nHeightDest,mdc, 0, 0, bmpdata->nWidth, bmpdata->nHeight, bc);
	
	SelectObject( mdc,poldbmp );
	DeleteObject(bmp);
	DeleteObject(poldbmp);
	DeleteDC(mdc);	
	
	return DT_SUCCESS;
}

#endif	/*DT_WIN32*/












/*==========================================================================================================*/
/*                 Implementation of the functions defined in DTplatform.h									*/
/*==========================================================================================================*/


/* Platform Dependent Color conversion funtion */
DT32_ulong DT_convColor(DT_RGBA color)
{
	DT32_ulong r,g,b,a;

DBG_MSG_SHOW_FUNC_NAME();

	r = (DT32_ulong)color.r<<24;
	g = (DT32_ulong)color.g<<16;
	b = (DT32_ulong)color.b<<8;
	a = (DT32_ulong)color.a;
	return  (DT32_ulong) r | g | b | a;
}


/* Draw a bmp (gray or none) to screen. Please implement this function according to your target platform.	*/
/* Return Value: 0:DT_SUCCESS; <0:error																		*/
DT32_int DT_BitBlt(	DT_void *hdcDest,		/* handle to destination DC					*/
					DT32_int nXDest,		/* x-coord of destination upper-left corner */
					DT32_int nYDest,		/* y-coord of destination upper-left corner */
					DT32_int nWidthDest,	/* width of destination rectangle			*/
					DT32_int nHeightDest,	/* height of destination rectangle			*/
					DT_DrawData *bmpdata,	/* the data to be drawn						*/
					DT_void **userdata		/* typecast to your own type struct, by pass from DT_RasterBitBlt()*/
)
{
DBG_MSG_SHOW_FUNC_NAME();

#ifdef DT_WIN32
	return myDT_BitBlt(hdcDest,nXDest,nYDest,nWidthDest,nHeightDest,bmpdata,userdata);
#endif
	
	return DT_SUCCESS;
}

/* Load font file data.	fsize is not required now (always -1), so ignore it.	*/
/* This function will be called from DT_CreateFontFromFile() only.				*/
/* DT_CreateFontFromMem() won't call this function.								*/
/* Modify "fontdata", "nfsize", and "refcnt" only. Let others stay the same.	*/
/* return 1 as success; others as error.										*/
DT32_int DT_LoadFontData(DT_void *dtfont, DT32_int fsize)
{
	DT_Font *font = (DT_Font*)dtfont;
	DT32_int i, ret=0, fcnt=0, fnamestart=0;
	DT8_char *fname;

DBG_MSG_SHOW_FUNC_NAME();

	if(font->refcnt==0){
#ifdef DT_ENABLE_STDIO
		/* DT_loadfilecontent() ignores fsize, always load all file. you can re-implement it.	*/
		/* You can implement a reference counter here to avoid to load font file many times.	*/
		ret = DT_loadfilecontent(font->fontname, font->nlen, &font->fontdata, &font->nfsize);
#else
		/* Because the data had been load, set it directly. */
		fcnt = sizeof(myfontlist)/sizeof(DT_FontFileInfo);
		for(i=0;i<fcnt;i++){
		  fnamestart = font->nlen - myfontlist[i].nlen;	/* only compare the file name, path isn't include. */
		  fname = font->fontname+fnamestart;
		  if(fnamestart>=0){
			if(!DT_strncmp(fname,myfontlist[i].fontname,myfontlist[i].nlen)){
				font->fontdata = myfontlist[i].fontdata;
				font->nfsize   = myfontlist[i].nfsize;
				ret = 1;
				break;
			}
		  }
		}
#endif
		if(1==ret){
			font->refcnt++;
			return 1;
		}else{
			return ret;
		}
	}else{	/*if(!font->fontdata || font->nfsize<=0 || font->refcnt==0)*/
		font->refcnt++;	
	}
	return 1;
}

/* Unload font file data.														*/
/* This function will be called from DT_CreateFontFromFile() only.				*/
/* DT_CreateFontFromMem() won't call this function.								*/
/* Modify "fontdata", "nfsize", and "refcnt" only. Let others stay the same.	*/
DT_void DT_unLoadFontData(DT_void *dtfont, DT32_int fsize)
{
	DT_Font *font = (DT_Font*)dtfont;
	
DBG_MSG_SHOW_FUNC_NAME();

	font->refcnt--;

	if(0==font->refcnt){
#ifdef DT_ENABLE_STDIO
	DT_unloadfilecontent(font->fontname, font->nlen, font->fontdata, font->nfsize);	
#else
	/*Do nothing*/
#endif
		font->fontdata = NULL;
		font->nfsize = 0;
	}
}



/*-----------------------------------------------------------------------------------------*/

const DT16_ushort DT_PUAOpenClosePair[][2] = {
#ifdef DT_CODE_ASCII_IN_PUA
	{0xE428, 0xE429},
	{0xE45B, 0xE45D},
	{0xE47B, 0xE47D},
#endif
	{0x0000, 0x0000}	/* Please reserve this line. */
};
/* Decide the direction of the codes in PUA.		*/
/* Please Return:									*/
/* DT_CODE_DIR_AS_LATIN (will be treated as Latin)	*/
/* DT_CODE_DIR_AS_ARABIC (will be treated as Arabic)*/
/* DT_CODE_DIR_NOT_SPECIFIED (Not specified, affected by DT_FSTYLE_WRITEDIR, like punctuation in ASCII)	*/
DT32_int DT_CodeDirection(DT16_ushort ch)
{
	DT32_int	dir;
	DT16_ushort	code;

/* Notice: Reserved Area: Some areas are reserved. It won't be decided here. */
/*
	if(ch>=0xE000 && ch<=0xE08F){}
	if(ch>=0xE900 && ch<=0xE9FF){}
	if(ch>=0xEE00 && ch<=0xEEFF){}
*/

/* For example: treat 0xE420-0xE47F as Basic Latin. */
#ifdef DT_CODE_ASCII_IN_PUA
	code = ch - (DT16_ushort)DT_CODE_ASCII_IN_PUA;
	if(code>=0x0020 && code<0x007F){
		dir = DT_CODE_ASCII_PUNCT;
		if(code>=0x41 && code<=0x5A ) dir = DT_CODE_DIR_AS_LATIN;
		else if(code>=0x61 && code<=0x7A ) dir = DT_CODE_DIR_AS_LATIN;
		else if(code>=0x30 && code<=0x39 ) dir = DT_CODE_DIR_AS_LATIN;
		else if(0x28==code || 0x5B==code || 0x7B==code)  dir = DT_CODE_ASCII_PAIR_OPEN;	/* pair in DT_PUAOpenClosePair[][2] */
		else if(0x29==code || 0x5D==code || 0x7D==code)  dir = DT_CODE_ASCII_PAIR_CLOSE;/* pair in DT_PUAOpenClosePair[][2] */
		return dir;
	}
#endif
	if (ch>0xE0FDu && ch<=0xE0FFu)
		return DT_CODE_DIR_AS_LATIN;  /* Panasonic added this */

	return DT_CODE_DIR_NOT_SPECIFIED;
}



/*-----------------------------------------------------------------------------------------*/
/* Rotate 90 degree code range table when DT_FSTYLE_VERT==1.	*/
/* The default table. */
DT_CodeFromTo DT_DefaultRotate90Table[] = {
	{0x0020, 0x007E},		/* Base Latin		*/
	{0x0600, 0x06FF},		/* Arabic Letters	*/
	{0x0900, 0x097F},		/* Devanagari Letter*/
	{0x0E00, 0x0E7F},		/* Thai Letters		*/
	{0x25CC, 0x25CC},
	{0xE000, 0xE07F},		/* Arabic Dcw PUA	*/
	{0xE080, 0xE08F},		/* Arabic Dcw PUA or ARIB STD_B24 *//* Comment this if ARIB STD_B24 */
	{0xEF00, 0xEFFF},		/* Devanagari PUA	*/
	{0xF200, 0xF3FF},		/* Devanagari		*/
	{0xFB50, 0xFDFF},		/* Arabic Form-A	*/
	{0xFE70, 0xFEFE},		/* Arabic Form-B	*/
	{0xFF61, 0xFF9F},		/* Half-Width Hana	*/
	{0,0}					/* Please reserve this line. */
};
/* You can reimplement this function to load the table by tableid.						*/
/* DT_isCodeRotate90_WhenVert() will call this function to get the table should be used.*/
DT_CodeFromTo* DT_GetRotate90CodesTable_WhenVert(DT32_int tableid)
{
	switch(tableid){
	case 0:
	default:
		return DT_DefaultRotate90Table;
	}
	return NULL;
}

/* You can modify this variable to tell DigiTypeAPI which table should be used.				*/
DT32_int gDT_Rotate90Table_ID = 0;
/* This function will be called inside DigiTypeAPI to decide which code should be rotated.	*/
/* ch: the code or glyph.											*/
/* Rversed: not used now. only NULL will be passed in.				*/
/* Return: 0: ch don't need to be rotate; 1: ch should be rotate.	*/
DT32_int DT_isCodeRotate90_WhenVert(DT16_ushort ch, DT32_int *Reserved)
{
	DT_CodeFromTo *range=NULL;

	range = DT_GetRotate90CodesTable_WhenVert(gDT_Rotate90Table_ID);

	if(!range)
		return 0;
	
	while(range->start){
		if(ch>=range->start && ch<=range->end){
			return 1;
		}
		range++;
	}

	return 0;
}

/* This function will be called inside DigiTypeAPI to decide which code should not return DT_WARNING_EMPTY_FONT.	*/
/* Parameters:																										*/
/*				ch: the code or glyph.																				*/
/*				Reserved: not used now. only NULL will be passed in.												*/
/* Returns 1: if you don't want DT_WARNING_EMPTY_FONT warning for 'ch'; else returns 0 for 'ch'.					*/
DT32_int DT_isCode_NoEmptyFontWarning(DT16_ushort ch, DT32_int *Reserved)
{
	if( (0x200B <= ch && 0x200F >= ch) || (0x2028 <= ch && 0x202F >= ch) ){
		return 1;
	}

	return 0;
}
