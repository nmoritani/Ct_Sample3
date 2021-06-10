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
	FT_FONTTYPE_calibri,	//�W��
	FT_FONTTYPE_calibril,	//�׎�	��Digitype�ɋ߂�
	FT_FONTTYPE_calibrib,	//����
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
    //	{ LOCALE_EN,		FT_FONTTYPE_calibril },		/* �p�ꂨ��щ��B���� */
	{ LOCALE_EN,		FT_FONTTYPE_MS_GOTHIC },		/* �p�ꂨ��щ��B���� */
	{ LOCALE_JP,		FT_FONTTYPE_MS_GOTHIC },	/* ���{�� */
	{ LOCALE_SC,		FT_FONTTYPE_VLADIMIR },	/* ������i�ȑ̎��j */
	{ LOCALE_TC,		FT_FONTTYPE_LHANDW },		/* ������i�ɑ̎��j */
	{ LOCALE_KR,		FT_FONTTYPE_KUNSTLER },		/* �؍��� */
	{ LOCALE_AR,		FT_FONTTYPE_JOKERMAN },		/* �A���r�A�� */
	{ LOCALE_TH,		FT_FONTTYPE_PARCHM },		/* �^�C�� */
	{ LOCALE_HI,		FT_FONTTYPE_cambriaz },		/* �q���f�B�[�� */
	{ LOCALE_EN2,		FT_FONTTYPE_times },		/* �C���^���̐؂�ւ��p */
	{ LOCALE_IC,		FT_FONTTYPE_ARIAL },		/* �A�C�R���i�O���A��������p�j */
	{ LOCALE_FX,		FT_FONTTYPE_MS_GOTHIC },	/* FIXED FONT */
};


//////////////////////////////////////////////////////////////////////////
// �ϐ���`
//////////////////////////////////////////////////////////////////////////
FT_FONT_TYPE		m_current_type;

/******************************************************************************/
/**
* �t�H���g�^�C�v�̐ݒ�
* [in/out]
*  @param type	: �t�H���g�^�C�v
*
*/
/******************************************************************************/
static void ft_service_set_current_font_type(FT_FONT_TYPE type)
{
	m_current_type = type;
}

/******************************************************************************/
/**
* �g�p���t�H���g�^�C�v�̎擾
* [out]
*  @retrun �t�H���g�^�C�v
*
*/
/******************************************************************************/
static FT_FONT_TYPE ft_service_get_current_fonttype()
{
	return m_current_type;
}


/******************************************************************************/
/**
* FreeType�p�t�H���gAPI�̏�����
* [out]
*  @retrun ���� / ���s
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
* FreeType�p�t�H���gAPI�̏I������
*/
/******************************************************************************/
void ft_service_terminate()
{
	freetype_wrapper_terminate();
	m_current_type = FT_FONTTYPE_NONE;
}

/******************************************************************************/
/**
* FreeType�̃t�H���g�f�[�^�̃��[�h(Face�̍쐬)
* [out]
*  @retrun ���� / ���s
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
* �t�H���g�t�@�C�����̌���
* [in/out]
*  @param type	: �t�H���g�^�C�v
* [out]
*  @retrun �t�H���g�t�@�C����
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
* �t�H���g�t�@�C���̃��[�h
* [in/out]
*  @param type	: �t�H���g�^�C�v
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
bool ft_service_find_load(FT_FONT_TYPE type)
{
	bool ret = false;

	//���ݓǂݍ���ł���t�H���g�ƈ�v���Ă�����ǂݍ��܂Ȃ�
	if (ft_service_get_current_fonttype() == type) {
		return true;
	}

	//�t�H���g�^�C�v����ɁA�t�H���g������������
	char* fontName = ft_service_find_fonttabel(type);
	if (!fontName) {
		return false;
	}

	//�w�肵���t�H���g������t�H���g�����[�h����
	if (ft_service_load_font_data(fontName, type)) {
		ft_service_set_current_font_type(type);
		ret = true;
	}

	return ret;
}


/******************************************************************************/
/**
* �t�H���g�^�C�v�̌���
* [in/out]
*  @param loc	: ���P�[��
* [out]
*  @retrun �t�H���g�^�C�v
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
* ���P�[���̐ݒ�
* [in/out]
*  @param loc	: ���P�[��
* [out]
*  @retrun ���� / ���s
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
* �t�H���g�X�^�C���̐ݒ�
* [in/out]
*  @param style	: �t�H���g�X�^�C��
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
static bool ft_service_set_style(const FONT_STYLE * style)
{
	long width = style->size_x;
	long height = style->size_y;

	//�t�H���g�T�C�Y�̐ݒ�
	if (!freetype_wrapper_set_char_size(width, height)) {
		return false;
	}

	return true;
}


/******************************************************************************/
/**
* �t�H���g�X�^�C���̃t���O�ݒ�
* [in/out]
*  @param ft_style	: FreeType�p�t�H���g�X�^�C��
*  @param style		: FontApi�p�t�H���g�X�^�C��
* [out]
*  @retrun ���� / ���s
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
* 1�������̕`��̈�̎擾
* [in/out]
*  @param style		: �t�H���g�X�^�C��
*  @param ucs_str	: ������
*  @param pinfo		: �`����
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
bool ft_service_get_rect_char(const FONT_STYLE * style, const unsigned short ucs_str, FT_SERVICE_INFO *pinfo)
{
	FT_FONT_INFO info;
	FT_FONT_STYLE ft_style;
	long startX = 0;

	//�t�H���g�X�^�C���̃Z�b�g�ꍇ
	if (!ft_service_set_style(style)) {
		return false;
	}

	//1��������
	Set_FT_Style_Flag(&ft_style, style);
	if (!freetype_wrapper_load_char(ucs_str, &ft_style)) {
		return false;
	}

	//�`�����o
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
* �O���C�r�b�g�}�b�v(8bit��)���J���[�R�[�h�ϊ��֐�
* [in/out]
*  @param color		: ���F���
* [out]
*  @retrun �ϊ���F���
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
* �O���C�r�b�g�}�b�v���J���[�R�[�h�ϊ��֐�
* [in/out]
*  @param bufTop	: �o�b�t�@�̐擪
*  @param value		: FreeType�Ń��X�^���C�Y���ē����l
*  @param color		: �F���
*  @param buf_size	: �o�b�t�@�T�C�Y
* [out]
*  @retrun �ϊ����Ċi�[����px��(1�o�C�g�ɂ�1px)
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
		unsigned short alpha = (((value * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		*bufCurrent = (color & 0xFFF0) | alpha;
	}
	return 1;
}

/***********************************************************************************************************************/
/**
* ���m�N���r�b�g�}�b�v���J���[�R�[�h�ϊ��֐�
* [in/out]
*  @param bufTop	: �o�b�t�@�̐擪
*  @param value		: FreeType�Ń��X�^���C�Y���ē����l
*  @param color		: �F���
*  @param buf_size	: �o�b�t�@�T�C�Y
* [out]
*  @retrun �ϊ����Ċi�[����px��(1�o�C�g�ɂ�8px)
*
*/
/************************************************************************************************************************/
static int convert_mono_bitmap_to_color(unsigned short *bufTop, unsigned char value, unsigned short color, int buf_size)
{
	int iBitShift;
	unsigned short *bufCurrent = bufTop;

	//�ER(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ra
	//�EG(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ga
	//�EB(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ba


	if (NULL == bufTop) {
		return 0;
	}

	//1�o�C�g��(8bit)�ϊ�����
	for (iBitShift = 7; 0 <= iBitShift; iBitShift--) {
		//�o�b�t�@�T�C�Y�𒴂��Ă�����I��
		if (buf_size < (bufCurrent - bufTop)) {
			break;
		}

		//�Y���r�b�g��ON���Ă�����J���[���Z�b�g����
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
* �r�b�g�}�b�v���J���[�R�[�h�ϊ��֐�
* [in/out]
*  @param dst				: �o�͐�o�b�t�@
*  @param src				: ���͌��o�b�t�@
*  @param start_x			: �o�͐�o�b�t�@�̊J�n�ʒu(X)
*  @param start_y			: �o�͐�o�b�t�@�̊J�n�ʒu(Y)
*  @param bufsize_width		: �o�͐�o�b�t�@�̕�
*  @param bufsize_height	: �o�͐�o�b�t�@�̍���
*  @param style				: �t�H���g�X�^�C��
*  @param width				: ���͌��o�b�t�@�̕�
*  @param height			: ���͌��o�b�t�@�̍���
*  @param color				: �F���
* [out]
*  @retrun ���� / ���s
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
* FreeType���������������r�b�g�}�b�v���J���[�R�[�h�ɕϊ����ďo�͐�o�b�t�@�i�[
* [in/out]
*  @param dstImage			: �o�͐�o�b�t�@
*  @param x					: �o�͐�o�b�t�@�̊J�n�ʒu(X)
*  @param y					: �o�͐�o�b�t�@�̊J�n�ʒu(Y)
*  @param bufsize_width		: �o�͐�o�b�t�@�̕�
*  @param bufsize_height	: �o�͐�o�b�t�@�̍���
*  @param ucs_str			: �`�悷�镶����
*  @param style				: �t�H���g�X�^�C��
*  @param color				: �F���
* [out]
*  @retrun ���� / ���s
*
*/
/************************************************************************************************************************/
bool ft_service_draw_bitmap_font_image(
	unsigned short			*dstImage,		//�o�͐�C���[�W�o�b�t�@
	int						x, 				//�o�͐�o�b�t�@�̒��̊J�nX���W
	int						y, 				//�o�͐�o�b�t�@�̒��̊J�nY���W
	int						bufsize_width, 	//�o�͐�o�b�t�@�̕�
	int						bufsize_height, //�o�͐�o�b�t�@�̍���
	const unsigned short	ucs_str, 		//�`�悷�镶����
	const FONT_STYLE		*style,			//�t�H���g�X�^�C��
	unsigned short			color) 			//�t�H���g�J���[
{
	unsigned char* ftbuf = NULL;
	long width = 0;
	long height = 0;
	FT_FONT_STYLE ft_style;
	FT_FONT_INFO info;

	//�t�H���g�X�^�C���̃Z�b�g�ꍇ
	if (!ft_service_set_style(style)) {
		return false;
	}

	//1��������
	Set_FT_Style_Flag(&ft_style, style);
	if (!freetype_wrapper_load_char(ucs_str, &ft_style)) {
		return false;
	}

	//�`�����o
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


