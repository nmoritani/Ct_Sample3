/**
 * Copyright(c) 2018 Persol AVC Technology.
 *
 * @file   utf_convert.h
 * 
 * @brief  UTF処理 外部公開用ヘッダファイル
 *
 */

#ifndef __UTF_CONVERT_H__
#define __UTF_CONVERT_H__

#ifdef __cplusplus
extern "C" {
#endif


/* UTF変換処理する最大文字数 */
#define UTF_NUM_MAX_CHAR  130



/**
 * @defgroup utf_err_id エラー定義
 * @ingroup utf_err
 */
/** @addtogroup utf_err_id
 *  @{ */  
#define UTF_OK                       0x00 /**< 正常 */
#define	UTF_ERR_BAD_ARG             -0x01 /**< 引数が不正 */  
#define	UTF_ERR_DECODE              -0x02 /**< 文字列デコードエラー */  
#define	UTF_ERR_UNDEF               -0x03 /**< その他エラー */  
/** @} */

/** @addtogroup utf_add_mark
 *  @{ */  
/** かな・カナの濁点・半濁点タイプ */
typedef enum
  {
	UTF_DEFAULT,        /**< 標準文字 */
	UTF_VOICED,         /**< 濁音文字 */
	UTF_SEMIVOICED,     /**< 半濁音文字 */
  } UTF_MARK_TYPE;
/** @} */


/* API関数宣言 */
extern int UTF_ConvertString8to16(char *utf8, unsigned short *utf16, int *nbyte, int *nchar);

extern int UTF_ConvertString16to8(unsigned short *utf16, char *utf8, int *nbyte, int *nchar);

extern int UTF_ConvertChar8to16(char *utf8, unsigned short *utf16, int *nbyte);

extern int UTF_ConvertChar16to8(unsigned short utf16, char *utf8, int *nbyte);

extern void convert_sjis_to_utf8(const char* sjis, char *utf8);

extern void convert_sjis_to_utf16(const char* sjis, unsigned short *utf16);
    
extern void UTF_AddMark (unsigned short in, unsigned short *out, UTF_MARK_TYPE type);

extern void UTF_AddNextMark (unsigned short in, unsigned short *out);

extern int UTF_InsertString(unsigned short *in, unsigned short *out, unsigned short chr, int pos);

extern int UTF_DeleteString(unsigned short *in, unsigned short *out, int pos);

extern int UTF_StrLen (char *utf8);

extern int UTF_NumBytes16to8 (unsigned short *utf16);

extern int get_char_string_length(const char *str);
extern int get_ushort_string_length(const unsigned short *str);
extern int convert_char_str_to_ushort_str(unsigned short *dst, const char *src);
extern int convert_ushort_str_to_char_str(char *dst, const unsigned short *src);


#ifdef __cplusplus
}
#endif

#endif /* __UTF_CONVERT_H__ */
