#ifndef __FREETYPE_WRAPPER_H_
#define __FREETYPE_WRAPPER_H_

#include <ft2build.h>
#include FT_FREETYPE_H			/* <freetype/freetype.h> */
#include FT_CACHE_H				/* <freetype/ftcache.h> */
#include FT_TRUETYPE_TAGS_H		/* <freetype/tttags.h> */
#include FT_TRUETYPE_TABLES_H	/* <freetype/tttables.h> */

typedef struct _FT_FONT_INFO {
	long			width;		//横方向のピクセル数
	long			height;		//縦方向のピクセル数
	long			stride;		//1行分のビットマップデータのバイト数

	long			accent;				//アセント
	long			descent;			//ディセント
	long			bitmapwidth;		//ビットマップの横幅
	long			bitmapheight;		//ビットマップの高さ
	int				lineUnderflow;

	long			drawStartPosX;		//描画開始位置
	long			drawStartPosY;		//描画開始位置
	long			advanceX;
	long			advanceY;
	unsigned char	*buf;		//ビットマップデータへのポインタ
} FT_FONT_INFO;

typedef struct _FT_FONT_STYLE {
#define	FT_FONTSTYLE_MONO		(0x0001)
#define	FT_FONTSTYLE_BOLD		(0x0002)
#define	FT_FONTSTYLE_ITALIC		(0x0004)
#define	FT_FONTSTYLE_OUTLINE	(0x0008)
	unsigned short flag;
} FT_FONT_STYLE;

#define	SET_FONTSTYLE_MONO(f)		((f) |= (FT_FONTSTYLE_MONO))
#define	SET_FONTSTYLE_BOLD(f)		((f) |= (FT_FONTSTYLE_BOLD))
#define	SET_FONTSTYLE_ITALIC(f)		((f) |= (FT_FONTSTYLE_ITALIC))
#define	SET_FONTSTYLE_OUTLINE(f)	((f) |= (FT_FONTSTYLE_OUTLINE))

extern void freetype_wrapper_init();
extern void freetype_wrapper_terminate();
extern bool freetype_wrapper_load_newface(const char* fileName, unsigned int faceID);
extern bool freetype_wrapper_get_font_info(int fontsize, FT_FONT_INFO *info);
extern bool freetype_wrapper_load_char(unsigned long char_code, FT_FONT_STYLE *style);
extern bool freetype_wrapper_set_char_size(long width, long height);

#endif //__FREETYPE_WRAPPER_H_
