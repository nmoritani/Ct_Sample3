#ifndef __FREETYPE_API_H__
#define __FREETYPE_API_H__

#include <stdbool.h>
#include "gdi.h"

typedef struct _FT_FONT_POS {
	long x;
	long y;
} FT_FONT_POS;

typedef struct _FT_SERVICE_INFO {
	long			width;			//�������̃s�N�Z����
	long			height;			//�c�����̃s�N�Z����
	long			xbytes;			//1�s���̃r�b�g�}�b�v�f�[�^�̃o�C�g��
	int				lineUnderflow;
	long			advanceX;		//�������`�掞�ɐi�߂�X���W�̋���
	long			advanceY;		//�������`�掞�ɐi�߂�Y���W�̋���
	long			MaxAdvanceY;	//�������`�掞�ɐi�߂�Y���W�̋���
	FT_FONT_POS		pos;			//�`��J�n�ʒu
} FT_SERVICE_INFO;


extern bool ft_service_init(void);
extern void ft_service_terminate(void);
extern bool ft_service_set_lang(enum FONT_LOCALE loc);
extern bool ft_service_get_rect_char(const FONT_STYLE * style, const unsigned short ucs_str, FT_SERVICE_INFO *pinfo);
extern bool ft_service_draw_bitmap_font_image(
	unsigned short			*dstImage,		//�o�͐�C���[�W�o�b�t�@
	int						x, 				//�o�͐�o�b�t�@�̒��̊J�nX���W
	int						y, 				//�o�͐�o�b�t�@�̒��̊J�nY���W
	int						bufsize_width, 	//�o�͐�o�b�t�@�̕�
	int						bufsize_height, //�o�͐�o�b�t�@�̍���
	const unsigned short	ucs_str, 		//�`�悷�镶����
	const FONT_STYLE		*style,			//�t�H���g�X�^�C��
	unsigned short			color);			//�t�H���g�J���[


#endif //__FREETYPE_API_H__
