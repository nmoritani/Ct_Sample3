/**
*  Copyright (c) 2018 Panasonic Corporation
*/

/*******************************************************************************
インクルードファイル
*******************************************************************************/
#include "freetype_mono_ovg.h"
#include "freetype_api.h"
#include "freetype_wrapper.h"

#include "egl.h"
#include "openvg.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {
	FT_DRAW_ONECHAR_NOERROR,
	FT_DRAW_ONECHAR_FAULT,
	FT_DRAW_ONECHAR_NEWLINE,
	FT_DRAW_ONECHAR_SPACE,
} FT_DRAW_ONECHAR_RESULT;

typedef struct _FONT_DRAW_POS {
	int CurrentWidth;
	int MaxWidth;
	int NextStartPosX;

	int NowHeight;
	int MaxHeight;
	int NextStartPosY;
	int MaxAdvanceY;
} FONT_DRAW_POS;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/**
* X方向に調整したフォントサイズを取得する
*
* [in/out]
*  @param gdi_font_style	: フォントスタイル
* [out]
*  @retrun X方向のフォントサイズ
*
*/
/******************************************************************************/
static unsigned char GetAjustFontSizeX(GDI_FONT_STYLE *gdi_font_style)
{
	FONT_STYLE f_style = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned char size_x = 0;

	gdi_cnv_font_style(&f_style, gdi_font_style, (gdi_font_style->attr == FONT_ATTRIBUTE_MONO));
	if ((AUTO_ADJUST_ENABLE == gdi_font_style->auto_adjust) && (1.0f != gdi_font_style->font_ajust_width)) {
		size_x = (unsigned char)((float)f_style.size_x * gdi_font_style->font_ajust_width);
	} else {
		size_x = f_style.size_x;
	}
	return size_x;
}


/***********************************************************************************************************************/
/**
* TRUEカラー→Highカラー変換関数
* [in/out]
*  @param color				: 元色情報
* [out]
*  @retrun 変換後色情報
*
*/
/************************************************************************************************************************/
static unsigned short convert_truecolor_to_highcolor(unsigned int color)
{
	unsigned char color_tbl[4];
	color_tbl[0] = (unsigned char)((color >> 24) & 0xff);					/* pgr0247 意図通りのキャスト */
	color_tbl[1] = (unsigned char)((color >> 16) & 0xff);					/* pgr0247 意図通りのキャスト */
	color_tbl[2] = (unsigned char)((color >> 8) & 0xff);					/* pgr0247 意図通りのキャスト */
	color_tbl[3] = (unsigned char)((color) & 0xff);							/* pgr0247 意図通りのキャスト */

	color_tbl[0] = (unsigned char)(((color_tbl[0] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */
	color_tbl[1] = (unsigned char)(((color_tbl[1] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */
	color_tbl[2] = (unsigned char)(((color_tbl[2] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */
	color_tbl[3] = (unsigned char)(((color_tbl[3] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */

	return ((color_tbl[0] << (3 * 4))
		| (color_tbl[1] << (2 * 4))
		| (color_tbl[2] << (1 * 4))
		| (color_tbl[3] << (0 * 4)));
}

/***********************************************************************************************************************/
/**
* ビットマップ→カラーコード変換関数
* [in/out]
*  @param dstImage			: 出力先バッファ
*  @param bufsize_width		: 出力先バッファの幅
*  @param bufsize_height	: 出力先バッファの高さ
*  @param ucs_str			: 描画する文字列
*  @param style				: フォントスタイル
*  @param fill_color		: 色情報
*  @param stroke_color		: 色情報
* [out]
*  @retrun 成功 / 失敗
*
*/
/************************************************************************************************************************/
static bool CreateBitmapFontImage(
	unsigned short *dstImage,			// 描画用ハンドル
	int bufsize_width, 					// 出力先バッファの幅
	int bufsize_height, 				// 出力先バッファの高さ
	const unsigned short ucs_str, 		// 描画する文字列
	const FONT_STYLE *style, 			// フォントスタイル
	unsigned int fill_color, 			// フォントカラー
	unsigned int stroke_color) 			// 縁線カラー
{
	unsigned short fcolor, incolor;

	if ((NULL == dstImage) || (NULL == style)) {
		return false;
	}

	//###mada 32ビットカラーを16ビットカラーに変更。実際に使うときはカラーパレット？
	fcolor = convert_truecolor_to_highcolor((style->edge) ? stroke_color : fill_color);
	incolor = 0;

	//描画
	if (!ft_service_draw_bitmap_font_image(dstImage, 0, 0, bufsize_width, bufsize_height, ucs_str, style, fcolor)) {
		return false;
	}

	return true;
}

/******************************************************************************/
/**
* ビットマップフォントの描画イメージの生成
*
* [in/out]
*  @param gdi_font_style	: フォントスタイル
*  @param str				: 文字
*  @param draw_info			: 描画情報
*  @param fill_color		: 塗りつぶしカラー
*  @param stroke_color		: 縁線カラー
* [out]
*  @retrun 描画情報のポインタ
*
*/
/******************************************************************************/
static BOOL IsUseDescentArea(USHORT _str)
{
	int cmpStr = (int)_str;

	return (('Q' == cmpStr)
		|| ('g' == cmpStr)
		|| ('j' == cmpStr)
		|| ('p' == cmpStr)
		|| ('q' == cmpStr)
		|| ('y' == cmpStr));
}

static unsigned char* gdi_create_bitmapfont_image(GDI_FONT_STYLE *gdi_font_style, unsigned short str, FONT_DRAW_INFO *draw_info, GDI_COLOR *fill_color, GDI_COLOR *stroke_color)
{
	int xbytes = 0;
	int height = 0;
	int buf_width = 0, buf_height = 0;
	int buf_size;
	unsigned char* image;
	unsigned int fillColor = 0;
	unsigned int strokeColor = 0;
	FT_SERVICE_INFO info;

	FONT_STYLE f_style = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if ((NULL == draw_info) || (NULL == gdi_font_style)) {
		return NULL;
	}

	if (!ft_service_set_lang(gdi_font_style->locale)) {
		return NULL;
	}

	gdi_cnv_font_style(&f_style, gdi_font_style, (gdi_font_style->attr == FONT_ATTRIBUTE_MONO));
	f_style.size_x = GetAjustFontSizeX(gdi_font_style);

	if (gdi_font_style->isWriteOneChar) {
		if (IsUseDescentArea(str)) {
			f_style.size_y -= 2;
		}
	}

	/* 描画範囲取得 */
	if (!ft_service_get_rect_char(&f_style, str, &info)) {
		return NULL;
	}

	height = info.height;
	xbytes = info.xbytes;	//格納元のバイト数

	buf_width = (0 == f_style.mono) ? xbytes : ((xbytes + 2) * 8);	//モノクロ：1bit = 8px / グレースケール：1byte = 1px
	buf_height = height + 1;

	//DMP対応。縦=8の倍数、横は16の倍数であること。
	buf_width = ((buf_width + 16) / 16) * 16;
	buf_height = ((buf_height + 8) / 8) * 8;
	buf_size = buf_width * buf_height * sizeof(unsigned short);

	//mallocで描画領域確保
	image = (unsigned char*)GDI_Alloc_Memory(buf_size);

	if (NULL == image) {
		return NULL;
	}

	memset(image, 0, buf_size);

	if (NULL != fill_color && fill_color->type != 0)
		fillColor = fill_color->color;
	if (NULL != stroke_color && stroke_color->type != 0)
		strokeColor = stroke_color->color;

	bool ret = CreateBitmapFontImage((USHORT*)image, buf_width, buf_height, str, &f_style, fillColor, strokeColor);

	if (!ret) {
		return NULL;
	}

	draw_info->pos_x = info.pos.x;
	draw_info->pos_y = info.pos.y;
	draw_info->width = buf_width;
	draw_info->height = height;
	draw_info->bmpwidth = info.width;
	draw_info->lineUnderflow = info.lineUnderflow;
	draw_info->advanceX = info.advanceX;

	return image;
}


/******************************************************************************/
/**
* 描画領域の生成
*
* [in/out]
*  @param gdi_font_style	: フォントスタイル
*  @param str				: 文字列
*  @param draw_info			: 描画情報
*  @param fill_color		: 塗りつぶしカラー
*  @param stroke_color		: 縁線カラー
* [out]
*  @retrun 描画情報のポインタ
*
*/
/******************************************************************************/
static bool FreetypeCreateCache(GDI_CACHE_BITMAP_FONT *cache_font, GDI_FONT_STYLE *gdi_font_style, unsigned short str, FONT_DRAW_INFO *draw_info, GDI_COLOR *fill_color, GDI_COLOR *stroke_color)
{
	//初期化
	cache_font->type = GDI_CACHE_TYPE_BITMAP_FONT;
	cache_font->vg_image = VG_INVALID_HANDLE;
	cache_font->raw_data = NULL;
	cache_font->ucs_str = NULL;
	cache_font->length = 0;
	cache_font->width = 0;
	cache_font->height = 0;
	cache_font->lineUnderflow = 0;
	cache_font->x_pos = 0;
	cache_font->y_pos = 0;
	cache_font->advanceX = 0;

	//ビットマップフォントの描画イメージ生成
	cache_font->raw_data = gdi_create_bitmapfont_image(gdi_font_style, str, draw_info, fill_color, stroke_color);
	if (NULL == cache_font->raw_data) {
		return false;
	}

	return true;
}

/******************************************************************************/
/**
* フォントの描画属性生成(VGImageの生成)
*
* [in/out]
*  @param gdi_font_style	: フォントスタイル
*  @param str				: 文字列
*  @param fill_color		: 塗りつぶしカラー
*  @param stroke_color		: 縁線カラー
* [out]
*  @retrun 描画情報のポインタ
*
*/
/******************************************************************************/
GDI_ERRCODE FreetypeCreateMonoFontImage(GDI_CACHE_BITMAP_FONT *pCache_font, GDI_FONT_STYLE *gdi_font_style, unsigned short str, GDI_COLOR *fill_color, GDI_COLOR *stroke_color)
{
	GDI_CACHE_BITMAP_FONT cache;
	GDI_CACHE_BITMAP_FONT *cache_font = &cache;
	FONT_DRAW_INFO draw_info = { 0, 0, 0, 0, 0 };
	VGImageFormat format = VG_sRGBA_4444;
	unsigned int bufStride, image_width, image_height;

	memset(&cache, 0, sizeof(cache));

	if (gdi_font_style == NULL) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	if (!FreetypeCreateCache(cache_font, gdi_font_style, str, &draw_info, fill_color, stroke_color)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	VGErrorCode err = vgGetError();	//実行前にエラーを除いておく
	image_width = ((draw_info.bmpwidth + 16) / 16) * 16;
	image_height = ((draw_info.height + 8) / 8) * 8;

	//vgImageの生成
#ifdef WIN32_GUI_SIM
	bufStride = draw_info.width * sizeof(unsigned short);

	cache_font->vg_image = vgCreateImage(format,
		image_width,
		image_height,
		VG_IMAGE_QUALITY_FASTER);

	err = vgGetError();	//エラー情報取得
	if (err != VG_NO_ERROR) {
		GDI_FreeCache_BitmapFont(cache_font);
		return GDI_OUT_OF_MEMORY_ERROR;
	}

	vgImageSubData(cache_font->vg_image, cache_font->raw_data, bufStride, format, 0, 0, image_width, image_height);

	err = vgGetError();	//エラー情報取得
	if (err != VG_NO_ERROR) {
		GDI_FreeCache_BitmapFont(cache_font);
		return GDI_OUT_OF_MEMORY_ERROR;
	}

#else
	bufStride = draw_info.width;
	void *buf_addr = (void *)((unsigned long)cache_font->raw_data & 0x3FFFFF80);	// DMP対応。アドレス指定の上位2bitを０固定とする
	cache_font->vg_image = vgCreateImageStandardDataDMP(format,
		bufStride,					//バッファの折り返し幅(px)
		image_height,				//バッファの高さ(px)
		(bufStride * image_height * sizeof(unsigned short)),	//バッファのバイト数
		buf_addr,					//バッファのアドレス
		VG_IMAGE_QUALITY_FASTER);

	err = vgGetError();	//エラー情報取得
	if (err != VG_NO_ERROR) {
		return GDI_OUT_OF_MEMORY_ERROR;
	}
#endif

	if (VG_INVALID_HANDLE == cache_font->vg_image) {
		GDI_FreeCache_BitmapFont(cache_font);
		return GDI_OUT_OF_MEMORY_ERROR;
	}

	cache_font->type = GDI_CACHE_TYPE_BITMAP_FONT;
	cache_font->width = image_width;
	cache_font->height = draw_info.height;
	cache_font->x_pos = draw_info.pos_x;
	cache_font->y_pos = draw_info.pos_y;
//	cache_font->ucs_str = str;
//	cache_font->length = len;
	cache_font->advanceX = draw_info.advanceX;
	cache_font->lineUnderflow = draw_info.lineUnderflow;

	*pCache_font = cache;

	return GDI_NO_ERROR;
}


/******************************************************************************/
/**
* フォントの描画属性の取得
*
* [in/out]
*  @param info:         描画方法
* [out]
*  @retrun フォントの描画属性(モノクロ/太字/アウトライン)
*
*/
/******************************************************************************/
static FONT_ATTRIBUTE getFontStyleAttr(GDI_DRAW_FONT *info)
{
    GDI_DRAW_FONT * pInfo = info;
    
	if (&pInfo->stroke_color == NULL) {
		return (info->font_style.attr == FONT_ATTRIBUTE_NORMAL) ? FONT_ATTRIBUTE_NORMAL : FONT_ATTRIBUTE_MONO;
	}

	if ((info->fill_color.type == info->stroke_color.type)
		&& (info->fill_color.color == info->stroke_color.color)) {
		return FONT_ATTRIBUTE_BOLD;
	}

	if ((info->fill_color.type == info->stroke_color.type)
		|| (info->fill_color.color != info->stroke_color.color)) {
		return FONT_ATTRIBUTE_OUTLINE;
	}
	return FONT_ATTRIBUTE_NORMAL;
}

/******************************************************************************/
/**
* 半角スペースの幅取得
*
* [in/out]
*  @param gdi_font_style	: フォントスタイル
* [out]
*  @retrun スペースの幅
*
*/
/******************************************************************************/
static int GetSpaceWidth(GDI_FONT_STYLE * gdi_font_style)
{
	unsigned char size_x = GetAjustFontSizeX(gdi_font_style);
	return size_x / 4;
}

/******************************************************************************/
/**
* 半角スペース判定
*
* [in/out]
*  @param str	: 文字コード
* [out]
*  @retrun スペースの幅
*
*/
/******************************************************************************/
static int IsCharCode_Space(unsigned short str)
{
	return (0x0020 == str);
}


/******************************************************************************/
/**
* モノクロフォントの1文字描画(縁付)
*
* [in/out]
*  @param hdr:
*  @param ucs_str	: 描画する文字
*  @param info		: 描画方法
*  @param charWidth	: 描画開始位置から次文字が描画開始する位置までの距離
* [out]
*  @retrun エラーコード
*
*/
/******************************************************************************/
static GDI_ERRCODE FreetypeDrawMono_OneChar(GDI_DRAW_BASE *info, GDI_CACHE_FONT *cache, unsigned short ucs_str, GDI_DRAW_FONT *info_font, int space_width, int *charWidth)
{
	return GDI_DrawBitmapFont_OneChar(info, cache, ucs_str, info_font, charWidth);
}

/******************************************************************************/
/**
* モノクロフォントの1文字描画(縁付)
*
* [in/out]
*  @param hdr		:
*  @param ucs_str	: 描画する文字
*  @param info		: 描画情報
*  @param charWidth	: 描画開始位置から次文字が描画開始する位置までの距離
* [out]
*  @retrun エラーコード
*/
/******************************************************************************/
static GDI_ERRCODE FreetypeDrawMono_Outline(GDI_DRAW_BASE *info, GDI_CACHE_FONT *cache, unsigned short ucs_str, GDI_DRAW_FONT *info_font, int space_width, int *charWidth)
{
	GDI_ERRCODE err = GDI_NO_ERROR;

	//縁線部分を描画
	info_font->font_style.attr = FONT_ATTRIBUTE_OUTLINE;
	err = FreetypeDrawMono_OneChar(info, cache, ucs_str, info_font, space_width, charWidth);
	if (GDI_NO_ERROR != err) return err;

	//中塗り用に描画開始座標を移動
	info->draw_area.x += 1;
	info->draw_area.y -= 1;

	//モノクロにして中塗り描画
	info_font->font_style.attr = FONT_ATTRIBUTE_NORMAL;
	err = FreetypeDrawMono_OneChar(info, cache, ucs_str, info_font, space_width, charWidth);
	if (GDI_NO_ERROR != err) return err;

	//描画開始座標を戻す
	info->draw_area.x -= 1;
	info->draw_area.y += 1;

	return err;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//描画開始X座標の取得
static VGfloat get_drawfont_start_x(HALIGN align, VGfloat src_width, VGint x, VGint width)
{
	switch (align) {
	case HALIGN_CENTER:
		return x + (width * 0.5f) - (src_width * 0.5f);

	case HALIGN_RIGHT:
		return x + (width - src_width);

	case HALIGN_LEFT:
	default:
		return (VGfloat)x;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//改行コード判定
static int IsNewLine(const USHORT *ucs_str)
{
	if (ucs_str == NULL)
		return 0;

	if ((0x0D == *ucs_str) && (0x0A == *(ucs_str + 1))) {
		return 2; //CR + LF(改行コードが2char)
	}

	if (0x0D == *ucs_str) {
		return 1; //CRのみ
	}

	if (0x0A == *ucs_str) {
		return 1; //LFのみ
	}

	return 0;	//改行コードなし
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//描画情報の取得
static bool GetDrawInfo(GDI_FONT_STYLE * gdi_font_style, const unsigned short *ucs_str, FT_SERVICE_INFO *pinfo)
{
	int len;
	FT_SERVICE_INFO info;
	int MaxWidth = 0;
	int NowWidth = 0;
	int NowHeight = 0;
	int MaxHeight = 0;
	int NextStartPosX = 0;
	int NextStartPosY = 0;
	int MaxAdvanceY = 0;
	int totalWidth = 0;
	int newLineCharNum = 0;


	FONT_STYLE f_style = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int space = GetSpaceWidth(gdi_font_style);

	gdi_cnv_font_style(&f_style, gdi_font_style, (gdi_font_style->attr == FONT_ATTRIBUTE_MONO));

	//文字数分の合計サイズを求める
	for (len = 0; ucs_str[len]; len++) {

		if (IsCharCode_Space(ucs_str[len])) {
			MaxWidth = NextStartPosX + space;
			NextStartPosX += space;

			MaxHeight = (MaxHeight < f_style.size_y) ? f_style.size_y : MaxHeight;
		} else if ((newLineCharNum = IsNewLine(&ucs_str[len])) > 0) {
			//改行コードがあった場合、横方向は座標0からやり直す(MAX値は保持)
			NowWidth = 0;
			NextStartPosX = 0;

			//縦方向の開始位置を更新
			NextStartPosY += MaxHeight;

			len += (newLineCharNum - 1);
		} else {
			if (!ft_service_get_rect_char(&f_style, ucs_str[len], &info)) {
				return false;
			}
			// 横方向の情報更新
			NowWidth = NextStartPosX + info.width + 1;
			MaxWidth = (MaxWidth < NowWidth) ? NowWidth : MaxWidth;
			NextStartPosX += info.advanceX;

			// 縦方向の情報更新
			NowHeight = NextStartPosY + info.advanceY;
			MaxHeight = (MaxHeight < NowHeight) ? NowHeight : MaxHeight;
			MaxAdvanceY = (MaxAdvanceY < info.advanceY) ? info.advanceY : MaxAdvanceY;
		}
	}

	pinfo->width = MaxWidth;
	pinfo->height = MaxHeight;
	pinfo->MaxAdvanceY = MaxAdvanceY;
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1文字描画時の描画情報をセットする
static bool UpdateDrawInfo_OneChar(FONT_DRAW_POS *pos_info, FONT_STYLE *f_style, const unsigned short ucs_str)
{
	FT_SERVICE_INFO info;

	if (!ft_service_get_rect_char(f_style, ucs_str, &info)) {
		return false;
	}

	// 横方向の情報更新
	pos_info->CurrentWidth = pos_info->NextStartPosX + info.width + 1;
	if (pos_info->MaxWidth < pos_info->CurrentWidth) pos_info->MaxWidth = pos_info->CurrentWidth;
	pos_info->NextStartPosX += info.advanceX;

	// 縦方向の情報更新
	pos_info->NowHeight = pos_info->NextStartPosY + info.advanceY;
	if (pos_info->MaxHeight < pos_info->NowHeight) pos_info->MaxHeight = pos_info->NowHeight;
	if (pos_info->MaxAdvanceY < info.advanceY) pos_info->MaxAdvanceY = info.advanceY;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//スペース時の描画情報をセットする
static bool UpdateDrawInfo_Space(FONT_DRAW_POS *pos_info, FONT_STYLE *f_style, const unsigned short ucs_str, int space_width)
{
	if (!IsCharCode_Space(ucs_str)) {
		return false;
	}

	pos_info->MaxWidth = pos_info->NextStartPosX + space_width;
	pos_info->NextStartPosX += space_width;

	if (pos_info->MaxHeight < f_style->size_y) pos_info->MaxHeight = f_style->size_y;

	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1文字分の描画情報を取得する
static FT_DRAW_ONECHAR_RESULT GetDrawInfo_OneChar(FONT_DRAW_POS *pos_info, FONT_STYLE *f_style, const unsigned short *ucs_str, int space_width)
{
	if (0 < IsNewLine(ucs_str)) {
		//改行コードがあった場合は終了
		return FT_DRAW_ONECHAR_NEWLINE;
	}

	//半角スペースの場合はスペース幅分描画座標をずらして次へ
	if (UpdateDrawInfo_Space(pos_info, f_style, *ucs_str, space_width)) {
		return FT_DRAW_ONECHAR_SPACE;
	}

	//1文字分の描画情報を取り出して次へ
	if (!UpdateDrawInfo_OneChar(pos_info, f_style, *ucs_str)) {
		return FT_DRAW_ONECHAR_FAULT;
	}

	return FT_DRAW_ONECHAR_NOERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1行分の描画情報を取得する
static GDI_ERRCODE GetDrawInfo_OneLine(FONT_STYLE *f_style, const unsigned short *ucs_str, int space_width, FT_SERVICE_INFO *pinfo, int *OneLineChars)
{
	FT_DRAW_ONECHAR_RESULT result;
	FONT_DRAW_POS pos_info;
	int length = 0;
	int crlf_len;
	const unsigned short *str_top = ucs_str;
	const unsigned short *str = ucs_str;

	memset(&pos_info, 0, sizeof(pos_info));

	//1行分のサイズを求める
	while (0x0000 != *str) {
		//1文字分の描画情報取得
		result = GetDrawInfo_OneChar(&pos_info, f_style, str, space_width);

		if (FT_DRAW_ONECHAR_FAULT == result) {
			return GDI_ILLEGAL_ARGUMENT_ERROR;
		}

		if (FT_DRAW_ONECHAR_NEWLINE == result) {
			break;
		}
		str++;
	}

	//取得した描画情報を返す
	pinfo->width = pos_info.MaxWidth;
	pinfo->height = pos_info.MaxHeight;
	pinfo->MaxAdvanceY = pos_info.MaxAdvanceY;

	length = str - str_top;
	crlf_len = IsNewLine(str);
	*OneLineChars = length + crlf_len;

	return GDI_NO_ERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
static GDI_ERRCODE DrawOneLine(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font, GDI_CACHE_FONT *cache, FONT_STYLE *f_style, const unsigned short *ucs_str, int space_width, int *DrawCharCount)
{
	FT_SERVICE_INFO drawinfo;
	int OneLineChars = 0;
	int oneCharWidth = 0;
	GDI_ERRCODE err;
	GDI_DRAW_BASE work_info = *info;
	GDI_DRAW_FONT work_info_font = *info_font;

	bool isOutLine = (0 != f_style->edge);

	memset(&drawinfo, 0, sizeof(drawinfo));

	// 1行分の描画情報を取得
	err = GetDrawInfo_OneLine(f_style, ucs_str, space_width, &drawinfo, &OneLineChars);
	if (GDI_NO_ERROR != err) {
		return err;
	}

	//描画開始X座標を変更(ALIGNの対応)
	int drawStartX = (int)get_drawfont_start_x(work_info_font.font_style.halign, drawinfo.width,
																						 work_info.draw_area.x, work_info.draw_area.width);
	work_info.draw_area.x = drawStartX;

	//1行分描画する
	for (int len = 0; len < OneLineChars; len++) {
		if (0 != IsNewLine(&ucs_str[len])) {
			break;			//改行コードが見つかったら終了
		}

		//Freetypeは半角スペースを処理できないので、スペース幅をそのまま返す
		if (IsCharCode_Space(ucs_str[len])) {
			work_info.draw_area.x += space_width;
			work_info.draw_area.width -= space_width;
			continue;
		}

		//1行分描画
		oneCharWidth = 0;
		err = (isOutLine)
			? FreetypeDrawMono_Outline(&work_info, cache, ucs_str[len], &work_info_font, space_width, &oneCharWidth)
			: FreetypeDrawMono_OneChar(&work_info, cache, ucs_str[len], &work_info_font, space_width, &oneCharWidth);
		if (GDI_NO_ERROR != err) break;

		//描画範囲外まで描いていたら終了
		if (work_info.draw_area.width < oneCharWidth) {
			break;
		}

		work_info.draw_area.x += oneCharWidth;
		work_info.draw_area.width -= oneCharWidth;
	}

	info->draw_area.y += drawinfo.MaxAdvanceY;
	*DrawCharCount = OneLineChars;

	return err;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
static GDI_ERRCODE DrawString(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font, GDI_CACHE_FONT *cache, int strLen, int space_width)
{
	GDI_ERRCODE err;
	int drawCount = 0;
	int CurrentIndex = 0;

	FONT_STYLE f_style;
	memset(&f_style, 0, sizeof(f_style));
	gdi_cnv_font_style(&f_style, &info_font->font_style, (info_font->font_style.attr == FONT_ATTRIBUTE_MONO));

	while (CurrentIndex < strLen) {
		drawCount = 0;

		//1行分描画
		err = DrawOneLine(info, info_font, cache, &f_style, &info_font->str[CurrentIndex], space_width, &drawCount);
		if (GDI_NO_ERROR != err) {
			return err;
		}
		CurrentIndex += drawCount;
	}
#ifndef WIN32_GUI_SIM
	//gdi_allocを間借りした環境ではメモリが足りなくなるので、
	//文字列描画後にフォントデータを破棄する。
	//Freetype用のメモリ領域をもらえたらこの対応は要らない
    //mori	ft_service_terminate();
#endif
	return GDI_NO_ERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
static unsigned char GetAdjustFontSize(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font)
{
	unsigned char fontsize;

	//自動調整フラグがOFFだった場合は調整しない
	if (info_font->font_style.auto_adjust == AUTO_ADJUST_DISABLE) {
		return info_font->font_style.font_size;
	}

	//フォントサイズが描画領域以下だった場合は調整しない
	//フォントサイズが指定されていた場合は調整しない
	if ((0 != info_font->font_style.font_size)
		&& (info_font->font_style.font_size <= info->draw_area.height)) {
		return info_font->font_style.font_size;
	}

	//フォントサイズを調整
	fontsize = (unsigned char)(info->draw_area.height * 0.75f);	/* pgr0247	*/
	if (fontsize < 16) {	//小さくなりすぎると完全につぶれてしまうため、16以下にはしない
		fontsize = 16;
	}

	return fontsize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//領域に合わせたフォントサイズの調整
static GDI_ERRCODE SetAdjustFontSize(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font)
{
	float ajust_width = 1.0f;
	FT_SERVICE_INFO drawinfo;

	memset(&drawinfo, 0, sizeof(drawinfo));

	info_font->font_style.font_size = GetAdjustFontSize(info, info_font);	//縦領域調整はフォントサイズで行う
	info_font->font_style.font_ajust_height = 1.0f;
	info_font->font_style.font_ajust_width = 1.0f;

	//文字列を描画時の幅・高さを取得する
	if (!GetDrawInfo(&info_font->font_style, info_font->str, &drawinfo)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	//幅が描画領域を超えていたら縮小する
	if (info->draw_area.width < drawinfo.width) {			//横領域調整は演算で行う
		ajust_width = (float)info->draw_area.width / (drawinfo.width);
	} else {
		ajust_width = 1.0f;
	}
	info_font->font_style.font_ajust_width = ajust_width;

	//文字の属性情報をセットする(太字、縁線など)
	info_font->font_style.attr = getFontStyleAttr(info_font);

	return GDI_NO_ERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//引数チェック
static bool IsCheckArgument(GDI_DRAW_FONT *info)
{
	if (NULL == info) {
		return false;
	}

	if (NULL == info->str) {
		return false;
	}

	if (!ft_service_set_lang(info->font_style.locale)) {
		return false;
	}

	return true;
}

/******************************************************************************/
/**
* FreeTypeを使用したビットマップフォントの文字列描画
*
* [in/out]
*  @param hdr:
*  @param info:
*    -member blend         描画方法
*    -member clip_area     クリップ範囲
*    -member field
*    -member draw_area     描画範囲
*    -member len           文字列長
*    -member str           文字列
*    -member font_style    フォント形式
*    -member auto_adjust   0：サイズ自動調整なし / 1：draw_areaに収まるようにサイズの自動調整を行う
*    -member stroke_width  縁線幅
*    -member stroke_color  縁線色
*    -member fill_color    塗りつぶし色
* [out]
*  @retrun エラーコード
*/
/******************************************************************************/
GDI_ERRCODE FreeType_DrawFont(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font, GDI_CACHE_FONT *cache)
{
	GDI_ERRCODE err = GDI_NO_ERROR;
	GDI_DRAW_BASE work_info;
	GDI_DRAW_FONT work_info_font;
	int len;
	int space_width;

	//引数チェック
	if (!IsCheckArgument(info_font)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	//文字数カウント
	for (len = 0; info_font->str[len]; len++);
	if (0 == len) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	//初期化
	work_info = *info;
    work_info_font.font_style.attr = FONT_ATTRIBUTE_NORMAL;	//TODO:グレースケールを使う場合はこのコメントアウトを外す
	work_info_font = *info_font;	//描画時にinfo_fontの値を更新するため、コピーして使用する

	//描画領域に合わせた文字サイズ調整
	err = SetAdjustFontSize(&work_info, &work_info_font);
	if (GDI_NO_ERROR != err) {
		return err;
	}

	//半角スペースの幅を設定
	space_width = GetSpaceWidth(&work_info_font.font_style);

	//文字列描画
	return DrawString(&work_info, &work_info_font, cache, len, space_width);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
GDI_ERRCODE Freetype_GetDrawRect(GDI_FONT_STYLE * gdi_font_style, unsigned short * str, unsigned int * pWidth, unsigned int * pHeight)
{
	GDI_FONT_STYLE work = *gdi_font_style;
	FT_SERVICE_INFO drawinfo;
	memset(&drawinfo, 0, sizeof(drawinfo));


	work.font_ajust_height = 1.0f;
	work.font_ajust_width = 1.0f;
	if (!GetDrawInfo(&work, str, &drawinfo)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	*pWidth = drawinfo.width;
	*pHeight = drawinfo.height;
	return GDI_NO_ERROR;
}



/**********************************************************************************
* Copyright(C) by 2018 Panasonic Corporation.
**********************************************************************************/
