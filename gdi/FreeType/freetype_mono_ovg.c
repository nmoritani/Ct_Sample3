/**
*  Copyright (c) 2018 Panasonic Corporation
*/

/*******************************************************************************
�C���N���[�h�t�@�C��
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
* X�����ɒ��������t�H���g�T�C�Y���擾����
*
* [in/out]
*  @param gdi_font_style	: �t�H���g�X�^�C��
* [out]
*  @retrun X�����̃t�H���g�T�C�Y
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
* TRUE�J���[��High�J���[�ϊ��֐�
* [in/out]
*  @param color				: ���F���
* [out]
*  @retrun �ϊ���F���
*
*/
/************************************************************************************************************************/
static unsigned short convert_truecolor_to_highcolor(unsigned int color)
{
	unsigned char color_tbl[4];
	color_tbl[0] = (unsigned char)((color >> 24) & 0xff);					/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	color_tbl[1] = (unsigned char)((color >> 16) & 0xff);					/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	color_tbl[2] = (unsigned char)((color >> 8) & 0xff);					/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	color_tbl[3] = (unsigned char)((color) & 0xff);							/* pgr0247 �Ӑ}�ʂ�̃L���X�g */

	color_tbl[0] = (unsigned char)(((color_tbl[0] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	color_tbl[1] = (unsigned char)(((color_tbl[1] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	color_tbl[2] = (unsigned char)(((color_tbl[2] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	color_tbl[3] = (unsigned char)(((color_tbl[3] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */

	return ((color_tbl[0] << (3 * 4))
		| (color_tbl[1] << (2 * 4))
		| (color_tbl[2] << (1 * 4))
		| (color_tbl[3] << (0 * 4)));
}

/***********************************************************************************************************************/
/**
* �r�b�g�}�b�v���J���[�R�[�h�ϊ��֐�
* [in/out]
*  @param dstImage			: �o�͐�o�b�t�@
*  @param bufsize_width		: �o�͐�o�b�t�@�̕�
*  @param bufsize_height	: �o�͐�o�b�t�@�̍���
*  @param ucs_str			: �`�悷�镶����
*  @param style				: �t�H���g�X�^�C��
*  @param fill_color		: �F���
*  @param stroke_color		: �F���
* [out]
*  @retrun ���� / ���s
*
*/
/************************************************************************************************************************/
static bool CreateBitmapFontImage(
	unsigned short *dstImage,			// �`��p�n���h��
	int bufsize_width, 					// �o�͐�o�b�t�@�̕�
	int bufsize_height, 				// �o�͐�o�b�t�@�̍���
	const unsigned short ucs_str, 		// �`�悷�镶����
	const FONT_STYLE *style, 			// �t�H���g�X�^�C��
	unsigned int fill_color, 			// �t�H���g�J���[
	unsigned int stroke_color) 			// �����J���[
{
	unsigned short fcolor, incolor;

	if ((NULL == dstImage) || (NULL == style)) {
		return false;
	}

	//###mada 32�r�b�g�J���[��16�r�b�g�J���[�ɕύX�B���ۂɎg���Ƃ��̓J���[�p���b�g�H
	fcolor = convert_truecolor_to_highcolor((style->edge) ? stroke_color : fill_color);
	incolor = 0;

	//�`��
	if (!ft_service_draw_bitmap_font_image(dstImage, 0, 0, bufsize_width, bufsize_height, ucs_str, style, fcolor)) {
		return false;
	}

	return true;
}

/******************************************************************************/
/**
* �r�b�g�}�b�v�t�H���g�̕`��C���[�W�̐���
*
* [in/out]
*  @param gdi_font_style	: �t�H���g�X�^�C��
*  @param str				: ����
*  @param draw_info			: �`����
*  @param fill_color		: �h��Ԃ��J���[
*  @param stroke_color		: �����J���[
* [out]
*  @retrun �`����̃|�C���^
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

	/* �`��͈͎擾 */
	if (!ft_service_get_rect_char(&f_style, str, &info)) {
		return NULL;
	}

	height = info.height;
	xbytes = info.xbytes;	//�i�[���̃o�C�g��

	buf_width = (0 == f_style.mono) ? xbytes : ((xbytes + 2) * 8);	//���m�N���F1bit = 8px / �O���[�X�P�[���F1byte = 1px
	buf_height = height + 1;

	//DMP�Ή��B�c=8�̔{���A����16�̔{���ł��邱�ƁB
	buf_width = ((buf_width + 16) / 16) * 16;
	buf_height = ((buf_height + 8) / 8) * 8;
	buf_size = buf_width * buf_height * sizeof(unsigned short);

	//malloc�ŕ`��̈�m��
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
* �`��̈�̐���
*
* [in/out]
*  @param gdi_font_style	: �t�H���g�X�^�C��
*  @param str				: ������
*  @param draw_info			: �`����
*  @param fill_color		: �h��Ԃ��J���[
*  @param stroke_color		: �����J���[
* [out]
*  @retrun �`����̃|�C���^
*
*/
/******************************************************************************/
static bool FreetypeCreateCache(GDI_CACHE_BITMAP_FONT *cache_font, GDI_FONT_STYLE *gdi_font_style, unsigned short str, FONT_DRAW_INFO *draw_info, GDI_COLOR *fill_color, GDI_COLOR *stroke_color)
{
	//������
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

	//�r�b�g�}�b�v�t�H���g�̕`��C���[�W����
	cache_font->raw_data = gdi_create_bitmapfont_image(gdi_font_style, str, draw_info, fill_color, stroke_color);
	if (NULL == cache_font->raw_data) {
		return false;
	}

	return true;
}

/******************************************************************************/
/**
* �t�H���g�̕`�摮������(VGImage�̐���)
*
* [in/out]
*  @param gdi_font_style	: �t�H���g�X�^�C��
*  @param str				: ������
*  @param fill_color		: �h��Ԃ��J���[
*  @param stroke_color		: �����J���[
* [out]
*  @retrun �`����̃|�C���^
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

	VGErrorCode err = vgGetError();	//���s�O�ɃG���[�������Ă���
	image_width = ((draw_info.bmpwidth + 16) / 16) * 16;
	image_height = ((draw_info.height + 8) / 8) * 8;

	//vgImage�̐���
#ifdef WIN32_GUI_SIM
	bufStride = draw_info.width * sizeof(unsigned short);

	cache_font->vg_image = vgCreateImage(format,
		image_width,
		image_height,
		VG_IMAGE_QUALITY_FASTER);

	err = vgGetError();	//�G���[���擾
	if (err != VG_NO_ERROR) {
		GDI_FreeCache_BitmapFont(cache_font);
		return GDI_OUT_OF_MEMORY_ERROR;
	}

	vgImageSubData(cache_font->vg_image, cache_font->raw_data, bufStride, format, 0, 0, image_width, image_height);

	err = vgGetError();	//�G���[���擾
	if (err != VG_NO_ERROR) {
		GDI_FreeCache_BitmapFont(cache_font);
		return GDI_OUT_OF_MEMORY_ERROR;
	}

#else
	bufStride = draw_info.width;
	void *buf_addr = (void *)((unsigned long)cache_font->raw_data & 0x3FFFFF80);	// DMP�Ή��B�A�h���X�w��̏��2bit���O�Œ�Ƃ���
	cache_font->vg_image = vgCreateImageStandardDataDMP(format,
		bufStride,					//�o�b�t�@�̐܂�Ԃ���(px)
		image_height,				//�o�b�t�@�̍���(px)
		(bufStride * image_height * sizeof(unsigned short)),	//�o�b�t�@�̃o�C�g��
		buf_addr,					//�o�b�t�@�̃A�h���X
		VG_IMAGE_QUALITY_FASTER);

	err = vgGetError();	//�G���[���擾
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
* �t�H���g�̕`�摮���̎擾
*
* [in/out]
*  @param info:         �`����@
* [out]
*  @retrun �t�H���g�̕`�摮��(���m�N��/����/�A�E�g���C��)
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
* ���p�X�y�[�X�̕��擾
*
* [in/out]
*  @param gdi_font_style	: �t�H���g�X�^�C��
* [out]
*  @retrun �X�y�[�X�̕�
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
* ���p�X�y�[�X����
*
* [in/out]
*  @param str	: �����R�[�h
* [out]
*  @retrun �X�y�[�X�̕�
*
*/
/******************************************************************************/
static int IsCharCode_Space(unsigned short str)
{
	return (0x0020 == str);
}


/******************************************************************************/
/**
* ���m�N���t�H���g��1�����`��(���t)
*
* [in/out]
*  @param hdr:
*  @param ucs_str	: �`�悷�镶��
*  @param info		: �`����@
*  @param charWidth	: �`��J�n�ʒu���玟�������`��J�n����ʒu�܂ł̋���
* [out]
*  @retrun �G���[�R�[�h
*
*/
/******************************************************************************/
static GDI_ERRCODE FreetypeDrawMono_OneChar(GDI_DRAW_BASE *info, GDI_CACHE_FONT *cache, unsigned short ucs_str, GDI_DRAW_FONT *info_font, int space_width, int *charWidth)
{
	return GDI_DrawBitmapFont_OneChar(info, cache, ucs_str, info_font, charWidth);
}

/******************************************************************************/
/**
* ���m�N���t�H���g��1�����`��(���t)
*
* [in/out]
*  @param hdr		:
*  @param ucs_str	: �`�悷�镶��
*  @param info		: �`����
*  @param charWidth	: �`��J�n�ʒu���玟�������`��J�n����ʒu�܂ł̋���
* [out]
*  @retrun �G���[�R�[�h
*/
/******************************************************************************/
static GDI_ERRCODE FreetypeDrawMono_Outline(GDI_DRAW_BASE *info, GDI_CACHE_FONT *cache, unsigned short ucs_str, GDI_DRAW_FONT *info_font, int space_width, int *charWidth)
{
	GDI_ERRCODE err = GDI_NO_ERROR;

	//����������`��
	info_font->font_style.attr = FONT_ATTRIBUTE_OUTLINE;
	err = FreetypeDrawMono_OneChar(info, cache, ucs_str, info_font, space_width, charWidth);
	if (GDI_NO_ERROR != err) return err;

	//���h��p�ɕ`��J�n���W���ړ�
	info->draw_area.x += 1;
	info->draw_area.y -= 1;

	//���m�N���ɂ��Ē��h��`��
	info_font->font_style.attr = FONT_ATTRIBUTE_NORMAL;
	err = FreetypeDrawMono_OneChar(info, cache, ucs_str, info_font, space_width, charWidth);
	if (GDI_NO_ERROR != err) return err;

	//�`��J�n���W��߂�
	info->draw_area.x -= 1;
	info->draw_area.y += 1;

	return err;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�`��J�nX���W�̎擾
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
//���s�R�[�h����
static int IsNewLine(const USHORT *ucs_str)
{
	if (ucs_str == NULL)
		return 0;

	if ((0x0D == *ucs_str) && (0x0A == *(ucs_str + 1))) {
		return 2; //CR + LF(���s�R�[�h��2char)
	}

	if (0x0D == *ucs_str) {
		return 1; //CR�̂�
	}

	if (0x0A == *ucs_str) {
		return 1; //LF�̂�
	}

	return 0;	//���s�R�[�h�Ȃ�
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�`����̎擾
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

	//���������̍��v�T�C�Y�����߂�
	for (len = 0; ucs_str[len]; len++) {

		if (IsCharCode_Space(ucs_str[len])) {
			MaxWidth = NextStartPosX + space;
			NextStartPosX += space;

			MaxHeight = (MaxHeight < f_style.size_y) ? f_style.size_y : MaxHeight;
		} else if ((newLineCharNum = IsNewLine(&ucs_str[len])) > 0) {
			//���s�R�[�h���������ꍇ�A�������͍��W0�����蒼��(MAX�l�͕ێ�)
			NowWidth = 0;
			NextStartPosX = 0;

			//�c�����̊J�n�ʒu���X�V
			NextStartPosY += MaxHeight;

			len += (newLineCharNum - 1);
		} else {
			if (!ft_service_get_rect_char(&f_style, ucs_str[len], &info)) {
				return false;
			}
			// �������̏��X�V
			NowWidth = NextStartPosX + info.width + 1;
			MaxWidth = (MaxWidth < NowWidth) ? NowWidth : MaxWidth;
			NextStartPosX += info.advanceX;

			// �c�����̏��X�V
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
//1�����`�掞�̕`������Z�b�g����
static bool UpdateDrawInfo_OneChar(FONT_DRAW_POS *pos_info, FONT_STYLE *f_style, const unsigned short ucs_str)
{
	FT_SERVICE_INFO info;

	if (!ft_service_get_rect_char(f_style, ucs_str, &info)) {
		return false;
	}

	// �������̏��X�V
	pos_info->CurrentWidth = pos_info->NextStartPosX + info.width + 1;
	if (pos_info->MaxWidth < pos_info->CurrentWidth) pos_info->MaxWidth = pos_info->CurrentWidth;
	pos_info->NextStartPosX += info.advanceX;

	// �c�����̏��X�V
	pos_info->NowHeight = pos_info->NextStartPosY + info.advanceY;
	if (pos_info->MaxHeight < pos_info->NowHeight) pos_info->MaxHeight = pos_info->NowHeight;
	if (pos_info->MaxAdvanceY < info.advanceY) pos_info->MaxAdvanceY = info.advanceY;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�X�y�[�X���̕`������Z�b�g����
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
//1�������̕`������擾����
static FT_DRAW_ONECHAR_RESULT GetDrawInfo_OneChar(FONT_DRAW_POS *pos_info, FONT_STYLE *f_style, const unsigned short *ucs_str, int space_width)
{
	if (0 < IsNewLine(ucs_str)) {
		//���s�R�[�h���������ꍇ�͏I��
		return FT_DRAW_ONECHAR_NEWLINE;
	}

	//���p�X�y�[�X�̏ꍇ�̓X�y�[�X�����`����W�����炵�Ď���
	if (UpdateDrawInfo_Space(pos_info, f_style, *ucs_str, space_width)) {
		return FT_DRAW_ONECHAR_SPACE;
	}

	//1�������̕`��������o���Ď���
	if (!UpdateDrawInfo_OneChar(pos_info, f_style, *ucs_str)) {
		return FT_DRAW_ONECHAR_FAULT;
	}

	return FT_DRAW_ONECHAR_NOERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1�s���̕`������擾����
static GDI_ERRCODE GetDrawInfo_OneLine(FONT_STYLE *f_style, const unsigned short *ucs_str, int space_width, FT_SERVICE_INFO *pinfo, int *OneLineChars)
{
	FT_DRAW_ONECHAR_RESULT result;
	FONT_DRAW_POS pos_info;
	int length = 0;
	int crlf_len;
	const unsigned short *str_top = ucs_str;
	const unsigned short *str = ucs_str;

	memset(&pos_info, 0, sizeof(pos_info));

	//1�s���̃T�C�Y�����߂�
	while (0x0000 != *str) {
		//1�������̕`����擾
		result = GetDrawInfo_OneChar(&pos_info, f_style, str, space_width);

		if (FT_DRAW_ONECHAR_FAULT == result) {
			return GDI_ILLEGAL_ARGUMENT_ERROR;
		}

		if (FT_DRAW_ONECHAR_NEWLINE == result) {
			break;
		}
		str++;
	}

	//�擾�����`�����Ԃ�
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

	// 1�s���̕`������擾
	err = GetDrawInfo_OneLine(f_style, ucs_str, space_width, &drawinfo, &OneLineChars);
	if (GDI_NO_ERROR != err) {
		return err;
	}

	//�`��J�nX���W��ύX(ALIGN�̑Ή�)
	int drawStartX = (int)get_drawfont_start_x(work_info_font.font_style.halign, drawinfo.width,
																						 work_info.draw_area.x, work_info.draw_area.width);
	work_info.draw_area.x = drawStartX;

	//1�s���`�悷��
	for (int len = 0; len < OneLineChars; len++) {
		if (0 != IsNewLine(&ucs_str[len])) {
			break;			//���s�R�[�h������������I��
		}

		//Freetype�͔��p�X�y�[�X�������ł��Ȃ��̂ŁA�X�y�[�X�������̂܂ܕԂ�
		if (IsCharCode_Space(ucs_str[len])) {
			work_info.draw_area.x += space_width;
			work_info.draw_area.width -= space_width;
			continue;
		}

		//1�s���`��
		oneCharWidth = 0;
		err = (isOutLine)
			? FreetypeDrawMono_Outline(&work_info, cache, ucs_str[len], &work_info_font, space_width, &oneCharWidth)
			: FreetypeDrawMono_OneChar(&work_info, cache, ucs_str[len], &work_info_font, space_width, &oneCharWidth);
		if (GDI_NO_ERROR != err) break;

		//�`��͈͊O�܂ŕ`���Ă�����I��
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

		//1�s���`��
		err = DrawOneLine(info, info_font, cache, &f_style, &info_font->str[CurrentIndex], space_width, &drawCount);
		if (GDI_NO_ERROR != err) {
			return err;
		}
		CurrentIndex += drawCount;
	}
#ifndef WIN32_GUI_SIM
	//gdi_alloc���Ԏ؂肵�����ł̓�����������Ȃ��Ȃ�̂ŁA
	//������`���Ƀt�H���g�f�[�^��j������B
	//Freetype�p�̃������̈�����炦���炱�̑Ή��͗v��Ȃ�
    //mori	ft_service_terminate();
#endif
	return GDI_NO_ERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
static unsigned char GetAdjustFontSize(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font)
{
	unsigned char fontsize;

	//���������t���O��OFF�������ꍇ�͒������Ȃ�
	if (info_font->font_style.auto_adjust == AUTO_ADJUST_DISABLE) {
		return info_font->font_style.font_size;
	}

	//�t�H���g�T�C�Y���`��̈�ȉ��������ꍇ�͒������Ȃ�
	//�t�H���g�T�C�Y���w�肳��Ă����ꍇ�͒������Ȃ�
	if ((0 != info_font->font_style.font_size)
		&& (info_font->font_style.font_size <= info->draw_area.height)) {
		return info_font->font_style.font_size;
	}

	//�t�H���g�T�C�Y�𒲐�
	fontsize = (unsigned char)(info->draw_area.height * 0.75f);	/* pgr0247	*/
	if (fontsize < 16) {	//�������Ȃ肷����Ɗ��S�ɂԂ�Ă��܂����߁A16�ȉ��ɂ͂��Ȃ�
		fontsize = 16;
	}

	return fontsize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�̈�ɍ��킹���t�H���g�T�C�Y�̒���
static GDI_ERRCODE SetAdjustFontSize(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font)
{
	float ajust_width = 1.0f;
	FT_SERVICE_INFO drawinfo;

	memset(&drawinfo, 0, sizeof(drawinfo));

	info_font->font_style.font_size = GetAdjustFontSize(info, info_font);	//�c�̈撲���̓t�H���g�T�C�Y�ōs��
	info_font->font_style.font_ajust_height = 1.0f;
	info_font->font_style.font_ajust_width = 1.0f;

	//�������`�掞�̕��E�������擾����
	if (!GetDrawInfo(&info_font->font_style, info_font->str, &drawinfo)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	//�����`��̈�𒴂��Ă�����k������
	if (info->draw_area.width < drawinfo.width) {			//���̈撲���͉��Z�ōs��
		ajust_width = (float)info->draw_area.width / (drawinfo.width);
	} else {
		ajust_width = 1.0f;
	}
	info_font->font_style.font_ajust_width = ajust_width;

	//�����̑��������Z�b�g����(�����A�����Ȃ�)
	info_font->font_style.attr = getFontStyleAttr(info_font);

	return GDI_NO_ERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����`�F�b�N
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
* FreeType���g�p�����r�b�g�}�b�v�t�H���g�̕�����`��
*
* [in/out]
*  @param hdr:
*  @param info:
*    -member blend         �`����@
*    -member clip_area     �N���b�v�͈�
*    -member field
*    -member draw_area     �`��͈�
*    -member len           ������
*    -member str           ������
*    -member font_style    �t�H���g�`��
*    -member auto_adjust   0�F�T�C�Y���������Ȃ� / 1�Fdraw_area�Ɏ��܂�悤�ɃT�C�Y�̎����������s��
*    -member stroke_width  ������
*    -member stroke_color  �����F
*    -member fill_color    �h��Ԃ��F
* [out]
*  @retrun �G���[�R�[�h
*/
/******************************************************************************/
GDI_ERRCODE FreeType_DrawFont(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font, GDI_CACHE_FONT *cache)
{
	GDI_ERRCODE err = GDI_NO_ERROR;
	GDI_DRAW_BASE work_info;
	GDI_DRAW_FONT work_info_font;
	int len;
	int space_width;

	//�����`�F�b�N
	if (!IsCheckArgument(info_font)) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	//�������J�E���g
	for (len = 0; info_font->str[len]; len++);
	if (0 == len) {
		return GDI_ILLEGAL_ARGUMENT_ERROR;
	}

	//������
	work_info = *info;
    work_info_font.font_style.attr = FONT_ATTRIBUTE_NORMAL;	//TODO:�O���[�X�P�[�����g���ꍇ�͂��̃R�����g�A�E�g���O��
	work_info_font = *info_font;	//�`�掞��info_font�̒l���X�V���邽�߁A�R�s�[���Ďg�p����

	//�`��̈�ɍ��킹�������T�C�Y����
	err = SetAdjustFontSize(&work_info, &work_info_font);
	if (GDI_NO_ERROR != err) {
		return err;
	}

	//���p�X�y�[�X�̕���ݒ�
	space_width = GetSpaceWidth(&work_info_font.font_style);

	//������`��
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
