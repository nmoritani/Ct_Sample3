#ifndef __FREETYPE_WRAPPER_H_
#define __FREETYPE_WRAPPER_H_

#include <ft2build.h>
#include FT_FREETYPE_H			/* <freetype/freetype.h> */
#include FT_CACHE_H				/* <freetype/ftcache.h> */
#include FT_TRUETYPE_TAGS_H		/* <freetype/tttags.h> */
#include FT_TRUETYPE_TABLES_H	/* <freetype/tttables.h> */

typedef struct _FT_FONT_INFO {
	long			width;		//�������̃s�N�Z����
	long			height;		//�c�����̃s�N�Z����
	long			stride;		//1�s���̃r�b�g�}�b�v�f�[�^�̃o�C�g��

	long			accent;				//�A�Z���g
	long			descent;			//�f�B�Z���g
	long			bitmapwidth;		//�r�b�g�}�b�v�̉���
	long			bitmapheight;		//�r�b�g�}�b�v�̍���
	int				lineUnderflow;

	long			drawStartPosX;		//�`��J�n�ʒu
	long			drawStartPosY;		//�`��J�n�ʒu
	long			advanceX;
	long			advanceY;
	unsigned char	*buf;		//�r�b�g�}�b�v�f�[�^�ւ̃|�C���^
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
