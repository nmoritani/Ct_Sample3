#include "freetype_api.h"
#include "freetype_wrapper.h"

#include "fontapi.h"

typedef enum {
	FT_FONTTYPE_NONE = 0,
	FT_FONTTYPE_MEIRYO_UI,
	FT_FONTTYPE_MS_GOTHIC,
	FT_FONTTYPE_SIMHEI,
	FT_FONTTYPE_MINGLIU,
	FT_FONTTYPE_BATANG,
	FT_FONTTYPE_MSUIGHUR,
	FT_FONTTYPE_LEELAWAD,
	FT_FONTTYPE_APARAJ,
	FT_FONTTYPE_BROWA,
	FT_FONTTYPE_ARIAL,
	FT_FONTTYPE_ITCBLKAD,
	FT_FONTTYPE_VLADIMIR,
	FT_FONTTYPE_LHANDW,
	FT_FONTTYPE_KUNSTLER,
	FT_FONTTYPE_JOKERMAN,
	FT_FONTTYPE_PARCHM,
	FT_FONTTYPE_cambriaz,
	FT_FONTTYPE_BOD_R,
	FT_FONTTYPE_times,
	FT_FONTTYPE_CORBEL,
	FT_FONTTYPE_calibri,	//標準
	FT_FONTTYPE_calibril,	//細字	←Digitypeに近い
	FT_FONTTYPE_calibrib,	//太字
	FT_FONTTYPE_MAX,
} FT_FONT_TYPE;

typedef struct _FONTMNG_TABLE {
	FT_FONT_TYPE	type;
	char*			FontName;
} FONTMNG_TABLE;

static const FONTMNG_TABLE font_tabel[] = {
	{ FT_FONTTYPE_NONE, "" },
	{ FT_FONTTYPE_MEIRYO_UI, "C:\\WINDOWS\\Fonts\\meiryo.ttc" },	
	{ FT_FONTTYPE_MS_GOTHIC, "C:\\WINDOWS\\Fonts\\msgothic.ttc" },	
	{ FT_FONTTYPE_SIMHEI,	 "C:\\WINDOWS\\Fonts\\simhei.ttf" },
	{ FT_FONTTYPE_MINGLIU,	 "C:\\WINDOWS\\Fonts\\mingliu.ttc" },
	{ FT_FONTTYPE_BATANG,	 "C:\\WINDOWS\\Fonts\\batang.ttc" },
	{ FT_FONTTYPE_MSUIGHUR,	 "C:\\WINDOWS\\Fonts\\msuighur.ttf" },
	{ FT_FONTTYPE_LEELAWAD,	 "C:\\WINDOWS\\Fonts\\leelawad.ttf" },
	{ FT_FONTTYPE_APARAJ,	 "C:\\WINDOWS\\Fonts\\aparaj.ttf" },
	{ FT_FONTTYPE_BROWA,	 "C:\\WINDOWS\\Fonts\\browa.ttf" },
	{ FT_FONTTYPE_ARIAL,	 "C:\\WINDOWS\\Fonts\\arial.ttf" },
	{ FT_FONTTYPE_ITCBLKAD,	 "C:\\WINDOWS\\Fonts\\ITCBLKAD.TTF" },
	{ FT_FONTTYPE_VLADIMIR,	"C:\\WINDOWS\\Fonts\\VLADIMIR.TTF" },
	{ FT_FONTTYPE_LHANDW,	"C:\\WINDOWS\\Fonts\\LHANDW.TTF" },
	{ FT_FONTTYPE_KUNSTLER,	"C:\\WINDOWS\\Fonts\\KUNSTLER.TTF" },
	{ FT_FONTTYPE_JOKERMAN,	"C:\\WINDOWS\\Fonts\\JOKERMAN.TTF" },
	{ FT_FONTTYPE_PARCHM,	"C:\\WINDOWS\\Fonts\\PARCHM.TTF" },
	{ FT_FONTTYPE_cambriaz,	"C:\\WINDOWS\\Fonts\\cambriaz.ttf" },
	{ FT_FONTTYPE_BOD_R,	"C:\\WINDOWS\\Fonts\\BOD_R.TTF" },
	{ FT_FONTTYPE_times,	"C:\\WINDOWS\\Fonts\\times.ttf" },
	{ FT_FONTTYPE_CORBEL,	"C:\\WINDOWS\\Fonts\\CORBEL.TTF" },

	{ FT_FONTTYPE_calibri,	"C:\\WINDOWS\\Fonts\\calibri.TTF" },
	{ FT_FONTTYPE_calibril,	"C:\\WINDOWS\\Fonts\\calibril.TTF" },
	{ FT_FONTTYPE_calibrib,	"C:\\WINDOWS\\Fonts\\calibrib.TTF" },
};

typedef struct _LANG_TO_FONTTYPE_TABLE {
	enum LOCALE		locale;
	FT_FONT_TYPE	type;
} LANG_TO_FONTTYPE_TABLE;

static const LANG_TO_FONTTYPE_TABLE lang_to_font_table[] = {
    //	{ LOCALE_EN,		FT_FONTTYPE_calibril },		/* 英語および欧州言語 */
	{ LOCALE_EN,		FT_FONTTYPE_MS_GOTHIC },		/* 英語および欧州言語 */
	{ LOCALE_JP,		FT_FONTTYPE_MS_GOTHIC },	/* 日本語 */
	{ LOCALE_SC,		FT_FONTTYPE_VLADIMIR },	/* 中国語（簡体字） */
	{ LOCALE_TC,		FT_FONTTYPE_LHANDW },		/* 中国語（繁体字） */
	{ LOCALE_KR,		FT_FONTTYPE_KUNSTLER },		/* 韓国語 */
	{ LOCALE_AR,		FT_FONTTYPE_JOKERMAN },		/* アラビア語 */
	{ LOCALE_TH,		FT_FONTTYPE_PARCHM },		/* タイ語 */
	{ LOCALE_HI,		FT_FONTTYPE_cambriaz },		/* ヒンディー語 */
	{ LOCALE_EN2,		FT_FONTTYPE_times },		/* イワタ書体切り替え用 */
	{ LOCALE_IC,		FT_FONTTYPE_ARIAL },		/* アイコン（外字、内部動作用） */
	{ LOCALE_FX,		FT_FONTTYPE_MS_GOTHIC },	/* FIXED FONT */
};


//////////////////////////////////////////////////////////////////////////
// 変数定義
//////////////////////////////////////////////////////////////////////////
FT_FONT_TYPE		m_current_type;

/******************************************************************************/
/**
* フォントタイプの設定
* [in/out]
*  @param type	: フォントタイプ
*
*/
/******************************************************************************/
static void ft_service_set_current_font_type(FT_FONT_TYPE type)
{
	m_current_type = type;
}

/******************************************************************************/
/**
* 使用中フォントタイプの取得
* [out]
*  @retrun フォントタイプ
*
*/
/******************************************************************************/
static FT_FONT_TYPE ft_service_get_current_fonttype()
{
	return m_current_type;
}


/******************************************************************************/
/**
* FreeType用フォントAPIの初期化
* [out]
*  @retrun 成功 / 失敗
*
*/
/******************************************************************************/
bool ft_service_init()
{
	ft_service_set_current_font_type(FT_FONTTYPE_NONE);
	freetype_wrapper_init();
	return true;
}

/******************************************************************************/
/**
* FreeType用フォントAPIの終了処理
*/
/******************************************************************************/
void ft_service_terminate()
{
	freetype_wrapper_terminate();
	m_current_type = FT_FONTTYPE_NONE;
}

/******************************************************************************/
/**
* FreeTypeのフォントデータのロード(Faceの作成)
* [out]
*  @retrun 成功 / 失敗
*
*/
/******************************************************************************/
static bool ft_service_load_font_data(const char* fontName, FT_FONT_TYPE fonttype)
{
	if (fontName == NULL) {
		return false;
	}

	return freetype_wrapper_load_newface(fontName, (unsigned int)fonttype);
}

/******************************************************************************/
/**
* フォントファイル名の検索
* [in/out]
*  @param type	: フォントタイプ
* [out]
*  @retrun フォントファイル名
*
*/
/******************************************************************************/
static char* ft_service_find_fonttabel(FT_FONT_TYPE type)
{
	for (int i = 0; i < (sizeof(font_tabel) / sizeof(font_tabel[0])); i++) {
		if (font_tabel[i].type == type) {
			return font_tabel[i].FontName;
		}
	}
	return NULL;
}

/******************************************************************************/
/**
* フォントファイルのロード
* [in/out]
*  @param type	: フォントタイプ
* [out]
*  @retrun 成功 / 失敗
*
*/
/******************************************************************************/
bool ft_service_find_load(FT_FONT_TYPE type)
{
	bool ret = false;

	//現在読み込んでいるフォントと一致していたら読み込まない
	if (ft_service_get_current_fonttype() == type) {
		return true;
	}

	//フォントタイプを基に、フォント名を検索する
	char* fontName = ft_service_find_fonttabel(type);
	if (!fontName) {
		return false;
	}

	//指定したフォント名からフォントをロードする
	if (ft_service_load_font_data(fontName, type)) {
		ft_service_set_current_font_type(type);
		ret = true;
	}

	return ret;
}


/******************************************************************************/
/**
* フォントタイプの検索
* [in/out]
*  @param loc	: ロケール
* [out]
*  @retrun フォントタイプ
*
*/
/******************************************************************************/
static FT_FONT_TYPE ft_service_find_fonttype(enum FONT_LOCALE loc)
{
	for (int i = 0; i < (sizeof(lang_to_font_table) / sizeof(lang_to_font_table[0])); i++) {
		if (lang_to_font_table[i].locale == loc) {
			return lang_to_font_table[i].type;
		}
	}
	return FT_FONTTYPE_NONE;
}

/******************************************************************************/
/**
* ロケールの設定
* [in/out]
*  @param loc	: ロケール
* [out]
*  @retrun 成功 / 失敗
*
*/
/******************************************************************************/
bool ft_service_set_lang(enum FONT_LOCALE loc)
{
	FT_FONT_TYPE type = ft_service_find_fonttype(loc);
	return ft_service_find_load(type);
}

/******************************************************************************/
/**
* フォントスタイルの設定
* [in/out]
*  @param style	: フォントスタイル
* [out]
*  @retrun 成功 / 失敗
*
*/
/******************************************************************************/
static bool ft_service_set_style(const FONT_STYLE * style)
{
	long width = style->size_x;
	long height = style->size_y;

	//フォントサイズの設定
	if (!freetype_wrapper_set_char_size(width, height)) {
		return false;
	}

	return true;
}


/******************************************************************************/
/**
* フォントスタイルのフラグ設定
* [in/out]
*  @param ft_style	: FreeType用フォントスタイル
*  @param style		: FontApi用フォントスタイル
* [out]
*  @retrun 成功 / 失敗
*
*/
/******************************************************************************/
static void Set_FT_Style_Flag(FT_FONT_STYLE *ft_style, const FONT_STYLE *style)
{
	ft_style->flag = 0;

	if (0 != style->bold) {
		SET_FONTSTYLE_BOLD(ft_style->flag);
	}

	if (0 != style->italic) {
		SET_FONTSTYLE_ITALIC(ft_style->flag);
	}

	if (0 != style->edge) {
		SET_FONTSTYLE_OUTLINE(ft_style->flag);
	}
	
	if (0 != style->mono) {
		SET_FONTSTYLE_MONO(ft_style->flag);
	}
}


/******************************************************************************/
/**
* 1文字分の描画領域の取得
* [in/out]
*  @param style		: フォントスタイル
*  @param ucs_str	: 文字列
*  @param pinfo		: 描画情報
* [out]
*  @retrun 成功 / 失敗
*
*/
/******************************************************************************/
bool ft_service_get_rect_char(const FONT_STYLE * style, const unsigned short ucs_str, FT_SERVICE_INFO *pinfo)
{
	FT_FONT_INFO info;
	FT_FONT_STYLE ft_style;
	long startX = 0;

	//フォントスタイルのセット場合
	if (!ft_service_set_style(style)) {
		return false;
	}

	//1文字生成
	Set_FT_Style_Flag(&ft_style, style);
	if (!freetype_wrapper_load_char(ucs_str, &ft_style)) {
		return false;
	}

	//描画情報取出
	if (!freetype_wrapper_get_font_info(style->size_y, &info)) {
		return false;
	}

	int total_width;
	int xbytes;

	startX = (info.drawStartPosX < 0) ? -info.drawStartPosX : info.drawStartPosX;
	total_width = info.bitmapwidth + startX;
	xbytes = (0 == style->mono) ? total_width : info.stride;

	pinfo->pos.x = info.drawStartPosX;
	pinfo->pos.y = info.drawStartPosY;
	pinfo->width = total_width;
	pinfo->height = info.height;
	pinfo->xbytes = xbytes;
	pinfo->advanceX = info.advanceX;
	pinfo->advanceY = info.advanceY;
	pinfo->lineUnderflow = info.lineUnderflow;
	return true;
}


/***********************************************************************************************************************/
/**
* グレイビットマップ(8bit分)→カラーコード変換関数
* [in/out]
*  @param color		: 元色情報
* [out]
*  @retrun 変換後色情報
*
*/
/************************************************************************************************************************/
static unsigned short convert_gray_to_color_code(unsigned char color)
{
	int r = (0 == (color & 0x0004)) ? 0 : 0xF000;
	int g = (0 == (color & 0x0002)) ? 0 : 0x0F00;
	int b = (0 == (color & 0x0001)) ? 0 : 0x00F0;
	int a = 0x000F;
	return (unsigned short)(r | g | b | a);
}

/***********************************************************************************************************************/
/**
* グレイビットマップ→カラーコード変換関数
* [in/out]
*  @param bufTop	: バッファの先頭
*  @param value		: FreeTypeでラスタライズして得た値
*  @param color		: 色情報
*  @param buf_size	: バッファサイズ
* [out]
*  @retrun 変換して格納したpx数(1バイトにつき1px)
*
*/
/************************************************************************************************************************/
static int convert_gray_bitmap_to_color(unsigned short *bufTop, unsigned char value, unsigned short color, int buf_size)
{
	unsigned short *bufCurrent = bufTop;

	if (NULL == bufTop) {
		return 0;
	}

	if (value != 0x00) {
		unsigned short alpha = (((value * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */
		*bufCurrent = (color & 0xFFF0) | alpha;
	}
	return 1;
}

/***********************************************************************************************************************/
/**
* モノクロビットマップ→カラーコード変換関数
* [in/out]
*  @param bufTop	: バッファの先頭
*  @param value		: FreeTypeでラスタライズして得た値
*  @param color		: 色情報
*  @param buf_size	: バッファサイズ
* [out]
*  @retrun 変換して格納したpx数(1バイトにつき8px)
*
*/
/************************************************************************************************************************/
static int convert_mono_bitmap_to_color(unsigned short *bufTop, unsigned char value, unsigned short color, int buf_size)
{
	int iBitShift;
	unsigned short *bufCurrent = bufTop;

	//・R(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ra
	//・G(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ga
	//・B(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ba


	if (NULL == bufTop) {
		return 0;
	}

	//1バイト分(8bit)変換する
	for (iBitShift = 7; 0 <= iBitShift; iBitShift--) {
		//バッファサイズを超えていたら終了
		if (buf_size < (bufCurrent - bufTop)) {
			break;
		}

		//該当ビットがONしていたらカラーをセットする
		if (value & (0x01 << iBitShift)) {
			*bufCurrent = color;
		}
		else {
			*bufCurrent = 0x0000;
		}

		bufCurrent++;
	}
	return (bufCurrent - bufTop);
}

/***********************************************************************************************************************/
/**
* ビットマップ→カラーコード変換関数
* [in/out]
*  @param dst				: 出力先バッファ
*  @param src				: 入力元バッファ
*  @param start_x			: 出力先バッファの開始位置(X)
*  @param start_y			: 出力先バッファの開始位置(Y)
*  @param bufsize_width		: 出力先バッファの幅
*  @param bufsize_height	: 出力先バッファの高さ
*  @param style				: フォントスタイル
*  @param width				: 入力元バッファの幅
*  @param height			: 入力元バッファの高さ
*  @param color				: 色情報
* [out]
*  @retrun 成功 / 失敗
*
*/
/************************************************************************************************************************/
static bool convert_bitmap_to_color(
	unsigned short *dst, 
	unsigned char *src, 
	int start_x, 
	int start_y, 
	int bufsize_width, 
	int bufsize_height, 
	const FONT_STYLE *style, 
	int width, 
	int height, 
	unsigned short color)
{
	typedef int(*FUNC_CONV_BITMAP_TO_COLOR)(unsigned short *, unsigned char, unsigned short, int);
	static FUNC_CONV_BITMAP_TO_COLOR func_convertBitmapToColor[] = {
		convert_gray_bitmap_to_color,	//Gray
		convert_mono_bitmap_to_color,	//Mono
	};
	int isMonoBitmap;
	int x, y;
	int x_size = width;
	int y_size = height;
	unsigned short *bufTopY;
	unsigned short *bufCurrent;

	if ((NULL == dst) || (NULL == src) || (NULL == style)) {
		return false;
	}

	bufTopY = (unsigned short *)(dst + ((start_y * bufsize_width) + start_x));
	isMonoBitmap = (style->mono) ? 1 : 0;


	for (y = 0; (y < y_size) && ((start_y + y) < bufsize_height); y++) {
		bufCurrent = bufTopY;

		for (x = 0; (x < x_size) && ((start_x + x) < bufsize_width); x++) {
			bufCurrent += (*func_convertBitmapToColor[isMonoBitmap])(bufCurrent, src[(y * width) + x], color, (bufsize_width - (start_x + x)));
		}
		bufTopY += bufsize_width;
	}

	return true;
}

/***********************************************************************************************************************/
/**
* FreeTypeが生成した文字ビットマップをカラーコードに変換して出力先バッファ格納
* [in/out]
*  @param dstImage			: 出力先バッファ
*  @param x					: 出力先バッファの開始位置(X)
*  @param y					: 出力先バッファの開始位置(Y)
*  @param bufsize_width		: 出力先バッファの幅
*  @param bufsize_height	: 出力先バッファの高さ
*  @param ucs_str			: 描画する文字列
*  @param style				: フォントスタイル
*  @param color				: 色情報
* [out]
*  @retrun 成功 / 失敗
*
*/
/************************************************************************************************************************/
bool ft_service_draw_bitmap_font_image(
	unsigned short			*dstImage,		//出力先イメージバッファ
	int						x, 				//出力先バッファの中の開始X座標
	int						y, 				//出力先バッファの中の開始Y座標
	int						bufsize_width, 	//出力先バッファの幅
	int						bufsize_height, //出力先バッファの高さ
	const unsigned short	ucs_str, 		//描画する文字列
	const FONT_STYLE		*style,			//フォントスタイル
	unsigned short			color) 			//フォントカラー
{
	unsigned char* ftbuf = NULL;
	long width = 0;
	long height = 0;
	FT_FONT_STYLE ft_style;
	FT_FONT_INFO info;

	//フォントスタイルのセット場合
	if (!ft_service_set_style(style)) {
		return false;
	}

	//1文字生成
	Set_FT_Style_Flag(&ft_style, style);
	if (!freetype_wrapper_load_char(ucs_str, &ft_style)) {
		return false;
	}

	//描画情報取出
	if (!freetype_wrapper_get_font_info(style->size_y, &info)) {
		return false;
	}

	ftbuf = info.buf;
	width = info.stride;
	height = info.bitmapheight;

	if (!convert_bitmap_to_color(dstImage, ftbuf, x, y, bufsize_width, bufsize_height, style, width, height, color)) {
		return false;
	}

	return true;
}


