/**
 * Copyright(c) 2018 Persol AVC Technology.
 *
 * @file   utf_convert.c
 * @brief  文字列の文字コード変換
 * 
 * UTF-16 <=> UTF-8の変換処理を行う。
 *
 */
#include <stdio.h>
#include "utf_convert.h"
#include "utf16_char.h"

#define CURRENTCHAR(p)  ((p)[0])
#define NEXTCHAR(p)     ((p)[1])
#define NEXTNEXTCHAR(p)     ((p)[2])

/* UTF-8(1byte)のビットパターンかを判別 */
#define UTF8_1BYTE_BITPATTERN(p) ( ((p)[0]&0x80)==0x00 )
/* UTF-8(2byte)のビットパターンかを判別 */
#define UTF8_2BYTE_BITPATTERN(p) ( ( ((p)[0]&0xe0)==0xc0 ) && ( ((p)[1]&0xc0)==0x80 ) )
/* UTF-8(3byte)のビットパターンかを判別 */
#define UTF8_3BYTE_BITPATTERN(p) ( ( ((p)[0]&0xf0)==0xe0 ) && ( ((p)[1]&0xc0)==0x80 ) && ( ((p)[2]&0xc0)==0x80 ) )


/* UTF-8からUNCODEを取り出す */
#define GET_1BYTE_UTF8_BITS(p)           ( (p)[0]&0x007f )
#define GET_2BYTE_UTF8_HIGH_BITS(p)      ( ((p)[0]&0x001f)<<6 )
#define GET_2BYTE_UTF8_LOW_BITS(p)       ( (p)[1]&0x003f )
#define GET_3BYTE_UTF8_HIGH_BITS(p)      ( ((p)[0]&0x000f)<<12 )
#define GET_3BYTE_UTF8_MID_BITS(p)       ( ((p)[1]&0x003f)<<6 )
#define GET_3BYTE_UTF8_LOW_BITS(p)       ( (p)[2]&0x003f )


/* UNCODEをUTF-8形式にセット */
#define SET_1BYTE_UTF8(code)             ((unsigned char)( code&0x007f ))
#define SET_2BYTE_UTF8_HIGH(code)        ((unsigned char)(0xc0|((code&0x07c0)>>6)))
#define SET_2BYTE_UTF8_LOW(code)         ((unsigned char)(0x80|(code&0x003f)))
#define SET_3BYTE_UTF8_HIGH(code)        ((unsigned char)(0xe0|((code&0xf000)>>12)))
#define SET_3BYTE_UTF8_MID(code)         ((unsigned char)(0x80|((code&0x0fc0)>>6)))
#define SET_3BYTE_UTF8_LOW(code)         ((unsigned char)(0x80|(code&0x003f)))


/* UTF-8の1byteパッケージに収まるか判別 */
#define CHECK_UTF8_1BYTE_PACKAGE(code)   ((code&0xff80)==0)
/* UTF-8の2byteパッケージに収まるか判別 */
#define CHECK_UTF8_2BYTE_PACKAGE(code)   ((code&0xf800)==0)


/* UTF-8(3byte)のBOMコードかを判別 */
#define UTF8_BOM_BITPATTERN(p) ( ((p)[0]==0xef ) && ( (p)[1]==0xbb ) && ( (p)[2]==0xbf ) )

/* UNICODEのNULL文字 */
#define UNICODE_NULL_CHAR 0x0000


static int utf8_to_utf16(unsigned char *utf8_chr, unsigned short *utf16_chr, int *nbyte)
{
	if ((NULL == utf8_chr) || (NULL == utf16_chr) || (NULL == nbyte)) {
		return UTF_ERR_BAD_ARG;
	}

	if (UTF8_1BYTE_BITPATTERN(utf8_chr)) {
		// 1byte文字
		*utf16_chr = (unsigned short)GET_1BYTE_UTF8_BITS(utf8_chr);	/* pgr0247 意図通りのキャスト */
		*nbyte = 1;
		return UTF_OK;
	}
	if (UTF8_2BYTE_BITPATTERN(utf8_chr)) {
		// 2byte文字
		*utf16_chr = (unsigned short)( GET_2BYTE_UTF8_HIGH_BITS(utf8_chr) 	/* pgr0247 意図通りのキャスト */
															| GET_2BYTE_UTF8_LOW_BITS(utf8_chr) );
		*nbyte = 2;
		return UTF_OK;
	}
	if (NEXTCHAR(utf8_chr) != '\0') {
		if (UTF8_3BYTE_BITPATTERN(utf8_chr)) {
			// 3byte文字
			*utf16_chr = (unsigned short)(GET_3BYTE_UTF8_HIGH_BITS(utf8_chr)	/* pgr0247 意図通りのキャスト */
										| GET_3BYTE_UTF8_MID_BITS(utf8_chr)
										| GET_3BYTE_UTF8_LOW_BITS(utf8_chr));
			*nbyte = 3;
			return UTF_OK;
		}
	}

	/* UTF8のフォーマット違反もしくは4byte以上の文字で非対応 */
	{
		*utf16_chr = UNICODE_NULL_CHAR; /* NULL文字を返す */
		*nbyte=1;
	}
	return UTF_ERR_DECODE;
}


static int utf16_to_utf8(unsigned short code, unsigned char *str, int *num)
{
	if ((NULL == str) || (NULL == num)) {
		return UTF_ERR_BAD_ARG;
	}

	if (CHECK_UTF8_1BYTE_PACKAGE(code)) {
		// 1byte
		str[0] = (unsigned char)SET_1BYTE_UTF8(code);		/* pgr0247 意図通りのキャスト */
		*num = 1;
	} else if (CHECK_UTF8_2BYTE_PACKAGE(code)) {
		// 2byte
		str[0] = (unsigned char)SET_2BYTE_UTF8_HIGH(code);	/* pgr0247 意図通りのキャスト */
		str[1] = (unsigned char)SET_2BYTE_UTF8_LOW(code);	/* pgr0247 意図通りのキャスト */
		*num = 2;
	} else {
		// 3byte
		str[0] = (unsigned char)SET_3BYTE_UTF8_HIGH(code);	/* pgr0247 意図通りのキャスト */
		str[1] = (unsigned char)SET_3BYTE_UTF8_MID(code);	/* pgr0247 意図通りのキャスト */
		str[2] = (unsigned char)SET_3BYTE_UTF8_LOW(code);	/* pgr0247 意図通りのキャスト */
		*num = 3;
	}
	return UTF_OK;
}

/** @addtogroup utf_convert
 *  @{
 */

/** 
 * utf8文字をUTF16文字に変換
 *
 * @param utf8 [IN] 入力UTF8文字の先頭アドレス
 * @param utf16 [OUT] 出力UTF16文字列を収めるためのアドレス
 * @param nbyte [OUT] UTF8のバイト数を収めるためのアドレス
 *
 * @return  @ref utf_err_id "エラーコード"
 *
 * @attention nbyteは終端文字(NULL文字)を含む
 *
 */
int UTF_ConvertChar8to16(char *utf8, unsigned short *utf16, int *nbyte)
{
	if (utf8 == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (utf16 == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (nbyte == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	return utf8_to_utf16(utf8, utf16, nbyte);
}

/** 
 * utf16文字をUTF8文字に変換
 *
 * @param utf16 [IN] 入力UTF16文字
 * @param utf8 [OUT] 出力UTF8文字を収めるためのアドレス
 * @param nbyte [OUT] UTF8のバイト数を収めるためのアドレス
 *
 * @return  @ref utf_err_id "エラーコード"
 *
 * @attention nbyteは終端文字(NULL文字)を含む
 *
 */
int UTF_ConvertChar16to8(unsigned short utf16, char *utf8, int *nbyte)
{
	if (utf8 == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	if (nbyte == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	return utf16_to_utf8(utf16, utf8, nbyte);
}

/** 
 * utf8文字列をUTF16文字列に変換
 *
 * @param utf8 [IN] 入力UTF8文字列の先頭アドレス
 * @param utf16 [OUT] 出力UTF16文字列の先頭アドレス
 * @param nbyte [OUT] UTF8のバイト数を収めるためのアドレス
 * @param nchar [OUT] 変換文字数を収めるためのアドレス
 *
 * @return  @ref utf_err_id "エラーコード"
 *
 * @attention NULL文字を検出するか、100文字に達するまで処理を続ける
 * @attention nbyte、ncharは終端文字(NULL文字)を含む
 *
 */
int UTF_ConvertString8to16(char *utf8, unsigned short *utf16, int *nbyte, int *nchar)
{
	int sum_byte, byte;
	int cnt;
	int ret = UTF_OK;

	if (utf8 == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (utf16 == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (nbyte == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (nchar == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	for (cnt = 0, sum_byte = 0; cnt < UTF_NUM_MAX_CHAR; cnt++, sum_byte += byte) {
		ret = utf8_to_utf16(&utf8[sum_byte], &utf16[cnt], &byte);
		if(utf16[cnt] == UNICODE_NULL_CHAR) {
			cnt++;
			sum_byte+=byte;
			break;
		}
	}

	*nbyte = sum_byte;
	*nchar = cnt;

	return ret;
}

/** 
 * utf16文字列をUTF8文字列に変換
 *
 * @param utf16 [IN] 入力UTF16文字列の先頭アドレス
 * @param utf8 [OUT] 出力UTF8文字列の先頭アドレス
 * @param nbyte [OUT] UTF8のバイト数を収めるためのアドレス
 * @param nchar [OUT] 変換文字数を収めるためのアドレス
 *
 * @return  @ref utf_err_id "エラーコード"
 *
 * @attention NULL文字を検出するか、100文字に達するまで処理を続ける
 * @attention nbyte、ncharは終端文字(NULL文字)を含む
 *
 */
int UTF_ConvertString16to8(unsigned short *utf16, char *utf8, int *nbyte, int *nchar)
{
	int sum_byte, byte;
	int cnt;
	int ret = UTF_OK;

	if (utf16 == NULL) {
	  return UTF_ERR_BAD_ARG;
	}

	if (utf8 == NULL) {
	  return UTF_ERR_BAD_ARG;
	}

	if (nbyte == NULL) {
	  return UTF_ERR_BAD_ARG;
	}

	if (nchar == NULL) {
	  return UTF_ERR_BAD_ARG;
	}


	for (cnt = 0, sum_byte = 0; cnt < UTF_NUM_MAX_CHAR; cnt++, sum_byte += byte) {
		ret = utf16_to_utf8(utf16[cnt], &utf8[sum_byte], &byte);
		if(utf8[sum_byte] == '\0') {
			cnt++;
			sum_byte+=byte;
			break;
		}
	}

	*nbyte = sum_byte;
	*nchar = cnt;

	return ret;
}


/** 
 * utf16文字列をUTF8に変更した際のUTF8バイト数取得
 *
 * @param utf16 [IN] UTF16文字列の先頭アドレス
 *
 * @return  UTF8文字列のバイト数
 *
 * @attention 終端文字(NULL文字)を含む
 *
 */
int UTF_NumBytes16to8(unsigned short *utf16)
{
	int sum_byte, byte;
	int cnt;
	unsigned char utf8[3];

	if (utf16 == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	for (cnt = 0, sum_byte = 0; cnt < UTF_NUM_MAX_CHAR; cnt++, sum_byte += byte) {
		utf16_to_utf8(utf16[cnt], utf8, &byte);
		if (utf16[cnt] == UNICODE_NULL_CHAR) {
			sum_byte+=byte;
			break;
		}
	}

	return sum_byte;
}

/** 
 * utf8文字数取得
 *
 * @param utf8 [IN] UTF8文字列の先頭アドレス
 *
 * @return  文字数
 *
 * @attention 終端文字(NULL文字)を含む
 *
 */
int UTF_StrLen(char *utf8)
{
	int sum_byte, byte;
	int cnt;
	unsigned short utf16;

	if(utf8 == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	for (cnt = 0, sum_byte = 0; cnt < UTF_NUM_MAX_CHAR; cnt++, sum_byte += byte) {
		utf8_to_utf16(&utf8[sum_byte], &utf16, &byte);
		if (utf8[sum_byte] == '\0') {
			cnt++;
			sum_byte += byte;
			break;
		}
	}
	return cnt;
}

/** 
 * 8bit文字列の文字数取得関数
 *
 * @param in  [IN]  char型の文字列の先頭アドレス
 *
 * @return  @ref 文字数(NULL含む)
 *
 * @note IN側文字列は必ずNULL終端すること
 */
int get_char_string_length(const char *str)
{
	int len = 0;
	if (str == NULL)
		return 0;
		
	for (len = 0; str[len]; len++) {	/* parasoft-suppress BD-PB-NOTINIT */
		if (str[len] == 0) break;
	}
	return len;
}


/** 
 * 16bit文字列の文字数取得関数
 *
 * @param in  [IN]  unsigned short型の文字列の先頭アドレス
 *
 * @return  @ref 文字数(NULL含む)
 *
 * @note IN側文字列は必ずNULL終端すること
 */
int get_ushort_string_length(const unsigned short *str)
{
	int len = 0;
	
	if (str == NULL)
		return 0;
		
	for (len = 0; str[len]; len++) {
		if (str[len] == 0) break;
	}
	return len;
}

/** 
 * 8bit文字列→16bit文字列変換関数
 *
 * @param in  [IN]  char型の文字列の先頭アドレス
 * @param out [OUT] unsigned short型の文字列の先頭アドレス
 *
 * @return  @ref 格納した文字数(NULL含む)
 *
 * @note IN側文字列は必ずNULL終端すること
 */
int convert_char_str_to_ushort_str(unsigned short *dst, const char *src)
{
	int len = 0;

	if (dst == NULL || src == NULL)
		return 0;
	
	for (len = 0; src[len]; len++) {
		if (src[len] == 0) break;
		dst[len] = (unsigned short)src[len];
	}
	dst[len] = 0x0000;
	
	return len;
}

/** 
 * 16bit文字列→8bit文字列変換関数
 *
 * @param in  [IN]  unsigned short型の文字列の先頭アドレス
 * @param out [OUT] char型の文字列の先頭アドレス
 *
 * @return  @ref 格納した文字数(NULL含む)
 *
 * @note IN側文字列は必ずNULL終端すること
 */
int convert_ushort_str_to_char_str(char *dst, const unsigned short *src)
{
	int len = 0;

	if (dst == NULL || src == NULL)
		return 0;
	
	for (len = 0; src[len]; len++) {
		if (src[len] == 0) break;
		dst[len] = (unsigned char)(src[len] & 0x00FF);	/* pgr0247 意図通りのキャスト */
	}
	dst[len] = 0x00;
	return len;
}


/** @addtogroup utf_string
 *  @{
 */
/** 
 * UTF16文字列の挿入
 *
 * @param in [IN] 挿入前の入力文字列の先頭アドレス
 * @param out [OUT] 挿入後の出力文字列の先頭アドレス
 * @param chr [IN] 挿入文字(UTF16形式)
 * @param pos [IN] 挿入位置
 *
 * @return  @ref utf_err_id "エラーコード"
 *
 * @note 挿入位置について、先頭に挿入する場合は0を指定する。
 * @note 挿入位置より前にNULL文字が検出された場合は、文字列の最後に追加する。
 *
 */
int UTF_InsertString(unsigned short *in, unsigned short *out, unsigned short chr, int pos)
{
	int idx;

	if(in == NULL)
	{
		return UTF_ERR_BAD_ARG;
	}
	if(out == NULL)
	{
		return UTF_ERR_BAD_ARG;
	}
	if( (pos<0)||(pos>=(UTF_NUM_MAX_CHAR-1)) )
	{
		return UTF_ERR_BAD_ARG;
	}

	for(idx=0;idx<pos;idx++)
	{
		out[idx] = in[idx];
		if(out[idx] == UNICODE_NULL_CHAR)
		{
			/* posにたどり着く途中にNULL文字が来た場合、NULL文字の場所に文字を追加 */
			out[idx++] = chr;
			out[idx] = UNICODE_NULL_CHAR;
			return UTF_OK;
		}
	}

	out[idx] = chr;

	for(;idx<(UTF_NUM_MAX_CHAR-1);idx++)
	{
		out[idx+1] = in[idx];

		if(in[idx] == UNICODE_NULL_CHAR)
		{
			/* NULL文字にたどり着いた場合、削除完了 */
			return UTF_OK;
		}
	}
	out[idx] = UNICODE_NULL_CHAR;
	return UTF_OK;
}



/** 
 * UTF16文字列の削除
 *
 * @param in [IN] 削除前の入力文字列の先頭アドレス
 * @param out [OUT] 削除後の出力文字列の先頭アドレス
 * @param pos [IN] 削除位置
 *
 * @return  @ref utf_err_id "エラーコード"
 *
 * @note 削除位置について、先頭文字を削除する場合は0を指定する。
 * @note 削除位置より前にNULL文字が検出された場合は、削除は行われない。
 *
 */
int UTF_DeleteString(unsigned short *in, unsigned short *out, int pos)
{
	int idx;

	if (in == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	if (out == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	if ((pos < 0) || (pos >= UTF_NUM_MAX_CHAR)) {
		return UTF_ERR_BAD_ARG;
	}

	for (idx = 0; idx < pos; idx++) {
		out[idx] = in[idx];
		if (in[idx] == UNICODE_NULL_CHAR) {
			/* posにたどり着く途中にNULL文字が来た場合、削除出来ないため終了する */
			return UTF_OK;
		}
	}

	if (in[idx] == UNICODE_NULL_CHAR) {
		/* posがNULL文字の場合、削除しても意味無いのでNULLを書いて終了 */
		out[idx] = UNICODE_NULL_CHAR;
		return UTF_OK;
	}

	for (; idx < (UTF_NUM_MAX_CHAR - 1); idx++) {
		out[idx] = in[idx + 1];

		if (out[idx] == UNICODE_NULL_CHAR) {
			/* NULL文字にたどり着いた場合、１文字削除完了 */
			return UTF_OK;
		}
	}
	out[idx] = UNICODE_NULL_CHAR;
	return UTF_OK;
}




static unsigned short add_mark_a_to_o(unsigned short in, UTF_MARK_TYPE type)
{
	/*
	あいうう"えお
	*/
	unsigned short output = in;

	//う⇔う"のみ変換
	/* 標準文字から濁音文字に変換 */
	if (in == UTF_H_LETTER_U) {
		if (type == UTF_VOICED) {
			return UTF_H_LETTER_VU;
		}
	}

	/* 濁音文字から標準文字に変換 */
	if (in == UTF_H_LETTER_VU) {
		if (type == UTF_DEFAULT) {
			return UTF_H_LETTER_U;
		}
	}
	return output;
}

static unsigned short add_mark_ka_to_ti(unsigned short in, UTF_MARK_TYPE type)
{
	/*
		かがきぎくぐけげこご 
		さざしじすずせぜそぞ 
		ただちぢ
		奇数：標準文字
		偶数：濁音文字
	*/
	unsigned short output = in;

	if (in & 0x0001) {
		/* 奇数は標準文字 */
		if (type == UTF_VOICED) {
			/* 標準文字から濁音文字に変換 */
			output = (unsigned short)(in + 1);	/* pgr0247 意図通りのキャスト */
		}
	} else {
		/* 遇数は濁音文字 */
		if (type == UTF_DEFAULT) {
			/* 濁音文字から標準文字に変換 */
			output = (unsigned short)(in - 1);	/* pgr0247 意図通りのキャスト */
		}
	}
	return output;
}

static unsigned short add_mark_tu_to_to(unsigned short in, UTF_MARK_TYPE type)
{
	/*
		っつづてでとど
	*/
	unsigned short output = in;
	unsigned short offset;

	//「っ」だけはそのまま返す
	if (in == UTF_H_LETTER_SMALL_TU) {
		return output;
	}

	if (type == UTF_DEFAULT) {
		offset = 0;
	} else if (type == UTF_VOICED) {
		offset = 1;
	} else {
		return output;
	}

	if (in <= UTF_H_LETTER_DU) {
		output = (unsigned short)(UTF_H_LETTER_TU + offset);	/* pgr0247 意図通りのキャスト */
	} else if(in <= UTF_H_LETTER_DE) {
		output = (unsigned short)(UTF_H_LETTER_TE + offset);	/* pgr0247 意図通りのキャスト */
	} else if(in <= UTF_H_LETTER_DO) {
		output = (unsigned short)(UTF_H_LETTER_TO + offset);	/* pgr0247 意図通りのキャスト */
	}

	return output;
}

static unsigned short add_mark_ha_to_ho(unsigned short in, UTF_MARK_TYPE type)
{
	/*
		はばぱひびぴふぶぷへべぺほぼぽ
	*/
	unsigned short output = in;
	unsigned short offset;

	if (type == UTF_DEFAULT) {
		offset = 0;
	} else if (type == UTF_VOICED) {
		offset = 1;
	} else if (type == UTF_SEMIVOICED) {
		offset = 2;
	} else {
		return in;
	}

	if (in <= UTF_H_LETTER_PA) {
		output = (unsigned short)(UTF_H_LETTER_HA + offset);	/* pgr0247 意図通りのキャスト */
	} else if (in <= UTF_H_LETTER_PI) {
		output = (unsigned short)(UTF_H_LETTER_HI + offset);	/* pgr0247 意図通りのキャスト */
	} else if (in <= UTF_H_LETTER_PU) {
		output = (unsigned short)(UTF_H_LETTER_HU + offset);	/* pgr0247 意図通りのキャスト */
	} else if (in <= UTF_H_LETTER_PE) {
		output = (unsigned short)(UTF_H_LETTER_HE + offset);	/* pgr0247 意図通りのキャスト */
	} else if (in <= UTF_H_LETTER_PO) {
		output = (unsigned short)(UTF_H_LETTER_HO + offset);	/* pgr0247 意図通りのキャスト */
	}

	return output;
}

static unsigned short add_mark(unsigned short in, UTF_MARK_TYPE type)
{
	if(in <= UTF_H_LETTER_O) {
		/* あ行 */
		return add_mark_a_to_o(in, type);
	}

	if(in <= UTF_H_LETTER_DI) {
		/* か～ち */
		return add_mark_ka_to_ti(in, type);
	}

	if(in <= UTF_H_LETTER_DO) {
		/* つてと */
		return add_mark_tu_to_to(in, type);
	}

	if(in <= UTF_H_LETTER_NO) {
		/* な行はなにもしない */
		return in;
	}

	if(in <= UTF_H_LETTER_PO) {
		/* は～ほ */
		return add_mark_ha_to_ho(in, type);
	}

	if(in == UTF_H_LETTER_VU) {
		/* う" */
		return add_mark_a_to_o(in, type);
	}

	/* 「ま～ん」は何もしない */
	return in;
}



static unsigned short add_mark_hiragana(unsigned short in, unsigned short *out, UTF_MARK_TYPE type)
{
	unsigned short chr;

	chr = add_mark(in, type);

	return chr;
}

static unsigned short add_mark_katakana(unsigned short in, unsigned short *out, UTF_MARK_TYPE type)
{
	unsigned short chr;

	/* ひらがなと処理を共通にするため、一旦ひらがなに変換 */
	chr = (unsigned short)(in - UTF_K_LETTER_SMALL_A + UTF_H_LETTER_SMALL_A);	/* pgr0247 意図通りのキャスト */

	chr = add_mark(chr, type);

	/* カタカナに戻す */
	chr = (unsigned short)(chr - UTF_H_LETTER_SMALL_A + UTF_K_LETTER_SMALL_A);	/* pgr0247 意図通りのキャスト */

	return chr;
}



/** @addtogroup utf_add_mark
 *  @{
 */
/** 
 * かな・カナの濁音・半濁音変換
 *
 * @param in [IN] 変換前の文字
 * @param out [OUT] 変換後の文字を格納するアドレス
 * @param type [IN] 変換タイプ
 *
 * @return  なし
 *
 * @attention 無効な変更を指定した場合、入力文字を返す。\n
 *            (たとえば「な」に濁音を指定した場合「な」を、「だ」に半濁音を指定した場合は「だ」を返す)
 *
 */
void UTF_AddMark(unsigned short in, unsigned short *out, UTF_MARK_TYPE type)
{
	if (NULL == out) {
		return;
	}

	if ((UTF_H_LETTER_SMALL_A <= in) && (in <= UTF_H_LETTER_VU)) {
		//ひらがなコードの範囲
		*out = add_mark_hiragana(in, out, type);
	} else if ((UTF_K_LETTER_SMALL_A <= in) && (in <= UTF_K_LETTER_VU)) {
		//カタカナコードの範囲
		*out = add_mark_katakana(in, out, type);
	} else {
		/* ひらがな・カタカナ以外の場合は変換せずに終了する */
		*out = in;
	}

	return;
}



static unsigned short add_nextmark_a_to_o(unsigned short in)
{
	/*
	あいうう"えお
	*/
	unsigned short output = in;

	//ウ⇔ヴのみ変換
	// 標準文字から濁音文字に変換
	if (in == UTF_K_LETTER_U) {
		return UTF_K_LETTER_VU;
	}

	// 濁音文字から標準文字に変換
	if(in == UTF_K_LETTER_VU) {
		return UTF_K_LETTER_U;
	}

	return output;
}

static unsigned short add_nextmark_ka_to_ti(unsigned short in)
{
	/*
		かがきぎくぐけげこご 
		さざしじすずせぜそぞ 
		ただちぢ
		奇数：標準文字
		偶数：濁音文字
	*/
	unsigned short output = in;

	if (in & 0x0001) {
		/* 奇数は標準文字 */
		/* 標準文字から濁音文字に変換 */
		output = (unsigned short)(in + 1);	/* pgr0247 意図通りのキャスト */
	} else {
		/* 偶数は濁音文字 */
		/* 濁音文字から標準文字に変換 */
		output = (unsigned short)(in - 1);	/* pgr0247 意図通りのキャスト */
	}
	return output;
}

static unsigned short add_nextmark_tu_to_to(unsigned short in)
{
	/*
		っつづてでとど
	*/
	unsigned short output = in;

	//「っ」だけはそのまま返す
	if (in == UTF_H_LETTER_SMALL_TU) {
		return output;
	}

	/* 先頭から２で割って余りで現在のtypeを求める
		余り	0:濁点，半濁点なし,1：濁点
	*/
	switch ((in - UTF_H_LETTER_TU) % 2) {
	case 0:	//濁点，半濁点なし
		//NEXT
		output = (unsigned short)(in + 1);	/* pgr0247 意図通りのキャスト */
		break;
	case 1:	//濁点
	default:
		//濁点，半濁点なしに戻す
		output = (unsigned short)(in - 1);	/* pgr0247 意図通りのキャスト */
		break;
	}
	return output;
}

static unsigned short add_nextmark_ha_to_ho(unsigned short in)
{
	/*
		はばぱひびぴふぶぷへべぺほぼぽ
	*/
	unsigned short output = in;

	/* 先頭から３で割って余りで現在のtypeを求める
		余り	0:濁点，半濁点なし,1：濁点，2：半濁点
	*/
	switch ((in - UTF_H_LETTER_HA) % 3) {
	case 0:	//濁点，半濁点なし
	case 1:	//濁点
		//NEXT
		output = (unsigned short)(in + 1);	/* pgr0247 意図通りのキャスト */
		break;
	case 2:	//半濁点
	default:
		//濁点，半濁点なしに戻す
		output = (unsigned short)(in - 2);	/* pgr0247 意図通りのキャスト */
		break;
	}
	return output;
}


static unsigned short add_nextmark(unsigned short in)
{

	if(in <= UTF_H_LETTER_O) {
		/* あ行*/
		return add_nextmark_a_to_o(in);
	}

	if (in <= UTF_H_LETTER_DI) {
		/* か～ぢ */
		return add_nextmark_ka_to_ti(in);
	}

	if (in <= UTF_H_LETTER_DO) {
		/* つ～ど */
		return add_nextmark_tu_to_to(in);
	}

	if (in <= UTF_H_LETTER_NO) {
		/* な行はなにもしない */
		return in;
	}

	if (in <= UTF_H_LETTER_PO) {
		/* は～ぽ */
		return add_nextmark_ha_to_ho(in);
	}

	if (in == UTF_K_LETTER_VU) {
		/* ヴ */
		return add_nextmark_a_to_o(in);
	}

	if (in == UTF_K_LETTER_U) {
		/* ウ */
		return add_nextmark_a_to_o(in);
	}

	/* 「ま～ん」は何もしない */
	return in;
}


static unsigned short add_nextmark_hiragana(unsigned short in, unsigned short *out)
{
	unsigned short chr;

	chr = add_nextmark(in);

	return chr;
}

static unsigned short add_nextmark_katakana(unsigned short in, unsigned short *out)
{
	unsigned short chr;

	if ((in == UTF_K_LETTER_U) || (in == UTF_K_LETTER_VU)) {
		/* 「ウ」はひらがなに変換せずに処理を行う (「う」の扱いはカタカナ、ひらがなで処理が異なるため)*/
		chr = add_nextmark(in);
	} else {
		/* ひらがなと処理を共通にするため、一旦ひらがなに変換 */
		chr = (unsigned short)(in - UTF_K_LETTER_SMALL_A + UTF_H_LETTER_SMALL_A );	/* pgr0247 意図通りのキャスト */
		chr = add_nextmark(chr);

		/* カタカナに戻す */
		chr = (unsigned short)(chr - UTF_H_LETTER_SMALL_A + UTF_K_LETTER_SMALL_A );	/* pgr0247 意図通りのキャスト */
	}
	return chr;
}

/*
in : 現在入力されている値
out：変換後の値（標準→濁音→半濁音→標準の順に切り替える）
*/
void UTF_AddNextMark(unsigned short in, unsigned short *out)
{
	if (NULL == out) {
		return;
	}

	//従来の変換と同じ流れ
	if ((in >= UTF_H_LETTER_SMALL_A) && (in <= UTF_H_LETTER_VU)) {
		//ひらがなコードの範囲
		*out = add_nextmark_hiragana(in, out);
	} else if ((in >= UTF_K_LETTER_SMALL_A) && (in <= UTF_K_LETTER_VU)) {
		//カタカナコードの範囲
		*out = add_nextmark_katakana(in, out);
	} else {
		/* ひらがな・カタカナ以外の場合は変換せずに終了する */
		*out = in;
	}

	return;
}





/** @} */ //end of utf_convert
