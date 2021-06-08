#ifndef __FONTAPI_H
#define __FONTAPI_H

/* VC++のDigiTypeの受け入れテストアプリ対応 */
#ifdef __cplusplus
extern "C" {
#endif

typedef char	FONT_DATATABLE;

#ifdef WIN32_GUI_SIM
typedef char CHAR;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int UINT;
#else
#include <kernel.h>
#endif

/*------------------------------------------------------------------------------*/
/**
@brief        文字スタイル構造体
*/
/*------------------------------------------------------------------------------*/
typedef struct {
    UCHAR   size_x;    /* 文字サイズ（横）*/
    UCHAR   size_y;    /* 文字サイズ（縦）*/
    UCHAR   bold;      /* 1: 太字 */
    UCHAR   italic;    /* 1: 斜体 */
    UCHAR   underline; /* 1: 下線 */
    UCHAR   strike;    /* 1: 打ち消し線 */
    CHAR    spacing;   /* 文字間隔 */
    UCHAR   righttoleft;  /* 描画方向 0:左から右  1:右から左 */
    UCHAR   edge;      /* 1: 縁取り（縁のみ） */
    UCHAR   edge_color;  /* 縁取り色 縁取りあり時のみ有効 */// [R77S1]フチ色対応
    UCHAR   mono;      /* 0: 16階調  1:モノクロ */
} FONT_STYLE;

typedef struct {
    UCHAR   size_x;    /* 文字サイズ（横）*/
    UCHAR   size_y;    /* 文字サイズ（縦）*/
    UCHAR   bold;      /* 1: 太字 */
    UCHAR   italic;    /* 1: 斜体 */
    UCHAR   underline; /* 1: 下線 */
    UCHAR   strike;    /* 1: 打ち消し線 */
    UCHAR   spacing;   /* 文字間隔 */
    UCHAR   righttoleft;  /* 描画方向 0:左から右  1:右から左 */
    UCHAR   edge;      /* 縁取りの縁太さ（0:縁取りなし） */
    UCHAR   shadow;    /* 0: 影なし 1: 右下に影 */
    UCHAR   fgcolor;   /* 文字色（0-15、OSD1カラーパレットの上位4bit）*/ /* ※現在は7（白）のみ使用可能 */
} FONT_STYLE_OSD1;

typedef struct {
	/* int width; */
	/* int height; */
	int ascent;        /* ほとんどの英数字の、ベースラインから最上点までの距離 */
	int descent;       /* ほとんどの英数字の、ベースラインから最下点までの距離 */
	/* int leading; */
	/* int maxAdvance; */
	int maxAscent;     /* 全ての文字の最大ascent */
	int maxDescent;    /* 全ての文字の最大descent */
} FONT_METRICS;

typedef struct {
	UINT width;			//描画する文字列全体の横幅
	UINT height;		//フォントの縦サイズ
	UINT lineunder;		//描画起点(左下)よりも下に描画されるイメージ部分の高さ
	UINT bmpwidth;		//実際に描画する文字イメージの幅
	UINT bmpheight;		//実際に描画する文字イメージの高さ
} FONT_DRAW_INFO;

/*------------------------------------------------------------------------------*/
/**
@brief        フォントロケールの定義
@par          フォントサービスにおける文字コードの扱い、使用する言語フォント、
              多言語文字列レイアウタの動作を決めるロケール種別を表します。
*/
/*------------------------------------------------------------------------------*/
enum FONT_LOCALE{
	LOCALE_EN = 0,  /* 英語および欧州言語 */
	LOCALE_JP,      /* 日本語 */
	LOCALE_SC,      /* 中国語（簡体字） */
	LOCALE_TC,      /* 中国語（繁体字） */
	LOCALE_KR,      /* 韓国語 */
	LOCALE_AR,      /* アラビア語 */
	LOCALE_TH,      /* タイ語 */
	LOCALE_HI,      /* ヒンディー語 */
	LOCALE_EN2,     /* イワタ書体切り替え用 */
	LOCALE_IC,      /* アイコン（外字、内部動作用） */
	LOCALE_FX,      /* FIXED FONT */
	LOCALE_NUM,     /* 全ロケール数（内部処理用） */
	LOCALE_NONE = 0xffff  /*  */
};

/*------------------------------------------------------------------------------*/
/**
@brief        フォントサービスのエラーコードの定義
*/
/*------------------------------------------------------------------------------*/
#define LANG_NOT_SUPPORT (-6)
#define ENGINEWKMEM_ERR (-7)
#define UCS_STR_TOO_LONG (-8)
#define UCS_ERR (-9)
#define NOT_ENOUGH_BUFFER (-10)
#define FONTSTYLE_ERROR (-11)
#define LAYBUF_ERR (-13)

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_init
@brief        Font Serviceの初期化
@param[in]    なし
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_init(
    void
);

#if KCSPEC_ARM_OPENVG
/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_font_data_table
@brief        別CPUのfontapi初期化のためのfonts情報を取得する
@param[in]    なし
@retval       FONT_DATATABLE*	(font_service_initの引数としてのみ使用可能)
@par          同期
@sa           [in] なし [out] current_locale
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
extern FONT_DATATABLE *font_service_get_font_data_table(
	void
);
#endif

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_quit
@brief        Font Serviceの終了処理
@param[in]    なし
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2011/11/1 新規作成
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_quit(
    void
);

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_lang
@brief        現在のフォントロケールの取得
@param[in]    なし
@retval       ロケール種別
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
extern enum FONT_LOCALE font_service_get_lang(
    void
);

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_set_lang
@brief        フォントロケールの切替
@param[in]    loc: ロケール種別
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_set_lang(
    enum FONT_LOCALE loc
);




/*------------------------------------------------------------------------------*/
/**
@fn           gdi_fontapi_get_rect
@brief        文字列イメージの描画サイズの取得
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@param[out]   width   文字列イメージの横サイズ
@param[out]   height  文字列イメージの縦サイズ
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
*/
/*------------------------------------------------------------------------------*/
extern int gdi_fontapi_get_rect(
	const FONT_STYLE *style, 
	const unsigned short *ucs_str, 
	unsigned short *width, 
	unsigned short *height,
	unsigned short *xbytes,
	unsigned char isBitmapFont
);

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_path
@brief        文字列イメージの取得（OpenVGのパスデータ）
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@retval       VGPathのハンドル（異常終了時はVG_INVALID_HANDLE）
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2011/9/5 新規作成
@par          特記事項: 使用後はfont_service_release_path()による解放が必要です。
*/
/*------------------------------------------------------------------------------*/
extern UINT gdi_fontapi_get_path(
    const FONT_STYLE *style,
    const USHORT *ucs_str,
	int len,
    FONT_DRAW_INFO *draw_info
);

extern UINT gdi_fontapi_CombineCharsToStrPath(
	const FONT_STYLE *style,
	const USHORT *ucs_str,
	FONT_DRAW_INFO *draw_info
);


/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_path
@brief        ビットマップフォント文字列イメージの取得
@par          更新履歴:
              2011/9/5 新規作成
@par          特記事項: 使用後はfont_service_release_path()による解放が必要です。
*/
/*------------------------------------------------------------------------------*/
extern int gdi_fontapi_create_bmp_font_Image(
	USHORT *dstImage,			// 描画用ハンドル
	int bufsize_width, 			// 出力先バッファの幅
	int bufsize_height, 		// 出力先バッファの高さ
	const USHORT *ucs_str, 		// 描画する文字列
	const FONT_STYLE *style, 	// フォントスタイル
	unsigned int fill_color, 	// フォントカラー
	unsigned int stroke_color 	// 縁線カラー
);











/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_rect
@brief        文字列描画に必要なイメージバッファのサイズの取得
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@param[out]   width   文字列イメージの横サイズ（ドット数）
@param[out]   height  文字列イメージの縦サイズ（ドット数）
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_get_rect(
    const  FONT_STYLE  *style,
    const  unsigned short  *ucs_str,
    unsigned short  *width,
    unsigned short  *height
);

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_exact_rect
@brief        文字列イメージの描画サイズの取得
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@param[out]   width   文字列イメージの横サイズ（ドット数）
@param[out]   height  文字列イメージの縦サイズ（ドット数）
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2010/11/13 新規作成
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_get_exact_rect(
    const  FONT_STYLE  *style,
    const  unsigned short  *ucs_str,
    unsigned short  *width,
    unsigned short  *height
);



#if KCSPEC_OPENVG
#ifdef WIN32
#include <VG/openvg.h>
#else
#ifndef VG_API_CALL
#define VG_API_CALL extern
#endif
#include <VG/openvg.h>
#endif
/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_path
@brief        文字列イメージの取得（OpenVGのパスデータ）
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@retval       VGPathのハンドル（異常終了時はVG_INVALID_HANDLE）
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2011/9/5 新規作成
@par          特記事項: 使用後はfont_service_release_path()による解放が必要です。
*/
/*------------------------------------------------------------------------------*/
extern VGPath gdi_fontapi_get_path(
    const FONT_STYLE *style,
    const USHORT *ucs_str,
    FONT_DRAW_INFO *draw_info
);

extern int gdi_fontapi_get_bmp_font_Image(
	USHORT *dstImage,			//出力先バッファ
	int x, 						//出力先バッファの中の開始X座標
	int y, 						//出力先バッファの中の開始Y座標
	int bufsize_width, 			//出力先バッファの幅
	int bufsize_height, 		//出力先バッファの高さ
	const USHORT *ucs_str, 		//描画する文字列
	const FONT_STYLE *style,	//フォントスタイル
	USHORT fcolor, 				//フォントカラー
	USHORT incolor, 			//内塗り(アウトライン描画時に中を塗る場合はセット。0の場合無効)
	VGint *pdrawRct				//描画を行った際の幅と高さの情報
);


#endif /* KCSPEC_OPENVG */

#ifdef __cplusplus
}
#endif

#endif /* __FONTAPI_H */
