#ifndef __FREETYPE_API_H__
#define __FREETYPE_API_H__

#include <stdbool.h>
#include "gdi.h"

typedef struct _FT_FONT_POS {
	long x;
	long y;
} FT_FONT_POS;

typedef struct _FT_SERVICE_INFO {
	long			width;			//横方向のピクセル数
	long			height;			//縦方向のピクセル数
	long			xbytes;			//1行分のビットマップデータのバイト数
	int				lineUnderflow;
	long			advanceX;		//次文字描画時に進めるX座標の距離
	long			advanceY;		//次文字描画時に進めるY座標の距離
	long			MaxAdvanceY;	//次文字描画時に進めるY座標の距離
	FT_FONT_POS		pos;			//描画開始位置
} FT_SERVICE_INFO;


extern bool ft_service_init(void);
extern void ft_service_terminate(void);
extern bool ft_service_set_lang(enum FONT_LOCALE loc);
extern bool ft_service_get_rect_char(const FONT_STYLE * style, const unsigned short ucs_str, FT_SERVICE_INFO *pinfo);
extern bool ft_service_draw_bitmap_font_image(
	unsigned short			*dstImage,		//出力先イメージバッファ
	int						x, 				//出力先バッファの中の開始X座標
	int						y, 				//出力先バッファの中の開始Y座標
	int						bufsize_width, 	//出力先バッファの幅
	int						bufsize_height, //出力先バッファの高さ
	const unsigned short	ucs_str, 		//描画する文字列
	const FONT_STYLE		*style,			//フォントスタイル
	unsigned short			color);			//フォントカラー


#endif //__FREETYPE_API_H__
