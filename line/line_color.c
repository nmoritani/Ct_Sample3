/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           color palette of line block
 */

#include "line_color.h"
#include "line_dd.h"

#define COLOR_ID_START		GUI_COLOR_ID_DELETE
#define COLOR_ID_END		(GUI_COLOR_ID_MAX - 1)
#define COLOR_ID_NUM		GUI_COLOR_ID_MAX

#define MARKER_COLOR_START	GUI_COLOR_ID_MARKER_WHITE
#define MARKER_COLOR_END	GUI_COLOR_ID_MARKER_YELLOW
#define MARKER_COLOR_NUM	(MARKER_COLOR_END - MARKER_COLOR_START + 1)

/* �J���[�p���b�g�f�[�^�����p���p�� (�����g���G���f�B�A���O��) */
typedef union {
	UW all;
	struct {
		UW cb:8;				/* bit0-7  : Cb */
		UW cr:8;				/* bit8-15 : Cr */
		UW y:8;					/* bit16-23: Y */
		UW alpha:7;				/* bit24-30: ���ߗ� */
		UW blink:1;				/* bit31   : Blink */
	};
} COLOR_PALETTE_DATA;

static UB line_marker_luminance[] = {
	100,						/* GUI_OUTPUT_LCD */
	100,						/* GUI_OUTPUT_HDMI */
	100							/* GUI_OUTPUT_SDI */
};

static const UW initial_color_palette[COLOR_ID_NUM] = {
	0x00000000,					/* GUI_COLOR_ID_DELETE */
	0x40EB0000,					/* GUI_COLOR_ID_WHITE */
	0x40EB0000,					/* GUI_COLOR_ID_BLACK */
	0x40EB0000,					/* GUI_COLOR_ID_GRAY */
	0x40EB0000,					/* GUI_COLOR_ID_BLUE */
	0x40EB0000,					/* GUI_COLOR_ID_CYAN */
	0x40EB0000,					/* GUI_COLOR_ID_GREEN */
	0x40EB0000,					/* GUI_COLOR_ID_YELLOW */
	0x40EB0000,					/* GUI_COLOR_ID_ORANGE */
	0x40EB0000,					/* GUI_COLOR_ID_RED */
	0x40EB0000,					/* GUI_COLOR_ID_PINK */
	0x40EB0000,					/* GUI_COLOR_ID_PURPLE */
	0x40EB0000,					/* GUI_COLOR_ID_MARKER_WHITE */
	0x40100000,					/* GUI_COLOR_ID_MARKER_BLACK */
	0x403F70E6,					/* GUI_COLOR_ID_MARKER_RED */
	0x40AD9AAA,					/* GUI_COLOR_ID_MARKER_GREEN */
	0x4020F670,					/* GUI_COLOR_ID_MARKER_BLUE */
	0x40DB0A90,					/* GUI_COLOR_ID_MARKER_YELLOW */
};

static void line_SetColorPaletteLcd(UW *source, GUI_COLOR_ID start, UB num);
static void line_SetColorPaletteHdmi(UW *source, GUI_COLOR_ID start, UB num);
static void line_SetColorPaletteSdi(UW *source, GUI_COLOR_ID start, UB num);

/**
   @brief   �J���[�p���b�g������
   @param[in] �Ȃ�
   @retval �Ȃ�
*/
void Line_InitColor(void)
{
	/**
	 * Marker �͋P�x�ݒ�ɂ��p���b�g�l���ς�邪 init �̒i�K�ł͂Ƃ肠���������l�ݒ�ɂ��Ă����B
	 * (���������p�e�[�u���y�ыP�x�ݒ�̏����l�� 100)
	 * ��� APL ���� Marker �P�x�ݒ肪�����^�C�~���O�ŉ��߂ă��[�U�[�l�����f�����
	 */
	Line_DD_SetColorPalette(GUI_OUTPUT_LCD, initial_color_palette, COLOR_ID_START, COLOR_ID_NUM);
	Line_DD_SetColorPalette(GUI_OUTPUT_HDMI, initial_color_palette, COLOR_ID_START, COLOR_ID_NUM);
	Line_DD_SetColorPalette(GUI_OUTPUT_SDI, initial_color_palette, COLOR_ID_START, COLOR_ID_NUM);
}

/**
   @brief   Marker �P�x�ݒ�
   @param[in] output    : �o�͐�w��
   @param[in] luminance : �P�x% (0�`100)
   @retval �Ȃ�
*/
void Line_SetMarkerLuminance(GUI_OUTPUT_DEV output, UB luminance)
{
	UW marker_palette[MARKER_COLOR_NUM];
	UB color;

	if (line_marker_luminance[output] == luminance) {
		return;
	}

	line_marker_luminance[output] = luminance;

	/* �J���[�p���b�g�̍Đݒ� */
	for (color = 0; color < MARKER_COLOR_NUM; color++) {
		COLOR_PALETTE_DATA palette = {0};
		palette.all = initial_color_palette[color + MARKER_COLOR_START];
		palette.y = (UB)(palette.y * luminance / 100); /* luminance �� 100 �Ȃ̂� y ������ꂷ�邱�Ƃ͂Ȃ� */
		marker_palette[color] = palette.all;
	}

	Line_DD_SetColorPalette(output, marker_palette, MARKER_COLOR_START, MARKER_COLOR_NUM);
}
