/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           line block device driver
 */
#include "line_dd.h"
#include "line_task.h"
#include "AvcGuiIf.h"
#include "guiif_avc.h"
#include "Mml.h"

/* V10 �ł̓n�[�h���F������A�h���X (�����A�h���X) �� CPU �����F������A�h���X(�_���A�h���X) ���قȂ�
 * Line �����͘_���ň����Ă��邪 AVIO �Ƃ͕����ł��Ƃ肷�邽�߁A�ϊ����K�v */
#define LINE_GET_PHYSICAL_ADDR(logicalAddr)	MML_PhysicalMemAddr((UW)logicalAddr)

/* ���̕ӂ̏��͕ω����邱�Ƃ��Ȃ��̂ŌŒ�l�Ŏ����Ă��� */
static const AVC_ST_OSD_LCD info_lcd = {
	(AVC_OUTPUT_LCDEVF_LCD | AVC_OUTPUT_LCDEVF_EVF),		/* mLcdEvf *//* [K519] */
	AVC_OSD_LAYER_3				/* mLayer */
};

static const AVC_ST_OSD_LOUT info_hdmi = {
	AVC_OUTPUT_TERMINAL_HDMI,	/* mTerminal */
	AVC_OSD_LAYER_3				/* mLayer */
};

static const AVC_ST_OSD_LOUT info_sdi = {
	(AVC_OUTPUT_TERMINAL_SDI | AVC_OUTPUT_TERMINAL_RCA),	/* mTerminal *//* [K519] */
	AVC_OSD_LAYER_3				/* mLayer */
};

static LINE_DD_CALLBACK_FUNC handler = NULL;

/* ���[�J���֐� */
static void line_DD_RequestApply(GUI_OUTPUT_DEV output);
extern void line_DD_SetColorPaletteLcd(const UW *source, GUI_COLOR_ID start, UB num);
extern void line_DD_SetColorPaletteHdmi(const UW *source, GUI_COLOR_ID start, UB num);
extern void line_DD_SetColorPaletteSdi(const UW *source, GUI_COLOR_ID start, UB num);
static void line_DD_SetMemoryLcd(UB *address);
static void line_DD_SetMemoryHdmi(UB *address);
static void line_DD_SetMemorySdi(UB *address);
static void line_DD_DisplayLcd(BOOL isOn);
static void line_DD_DisplayHdmi(BOOL isOn);
static void line_DD_DisplaySdi(BOOL isOn);
static void line_DD_SetResolutionLcd(UH lineOffset, const GUI_VIDEO_FORMAT *signal);
static void line_DD_SetResolutionHdmi(UH lineOffset, const GUI_VIDEO_FORMAT *signal);
static void line_DD_SetResolutionSdi(UH lineOffset, const GUI_VIDEO_FORMAT *signal);
static AVC_ER line_DD_HandlerVsync(void);


/**
   @brief   �p���b�g�ݒ� (LCD)
   @param[in] output    : �o�͐�
   @param[in] *source   : �ݒ�f�[�^�̐擪
   @param[in] start     : �ݒ肷��p���b�g ID (�J�n���� ID)
   @param[in] num       : �ݒ肷��f�[�^��
   @retval �Ȃ�
*/
void Line_DD_SetColorPalette(GUI_OUTPUT_DEV output, const UW *source, GUI_COLOR_ID start, UB num)
{
	switch (output) {
	case GUI_OUTPUT_LCD:
		line_DD_SetColorPaletteLcd(source, start, num);
		line_DD_RequestApply(output);
		break;
	case GUI_OUTPUT_HDMI:
		line_DD_SetColorPaletteHdmi(source, start, num);
		line_DD_RequestApply(output);
		break;
	case GUI_OUTPUT_SDI:
		line_DD_SetColorPaletteSdi(source, start, num);
		line_DD_RequestApply(output);
		break;
	default:
		break;
	}
}

/**
   @brief   �v���[���������ݒ�
   @param[in] output    : �o�͐�
   @param[in] address   : ���蓖�ă������A�h���X
   @retval �Ȃ�
*/
void Line_DD_SetMemory(GUI_OUTPUT_DEV output, UB *address)
{
	switch (output) {
	case GUI_OUTPUT_LCD:
		line_DD_SetMemoryLcd(address);
		line_DD_RequestApply(output);
		break;
	case GUI_OUTPUT_HDMI:
		line_DD_SetMemoryHdmi(address);
		line_DD_RequestApply(output);
		break;
	case GUI_OUTPUT_SDI:
		line_DD_SetMemorySdi(address);
		line_DD_RequestApply(output);
		break;
	default:
		break;
	}
}

/**
   @brief   �\���� ON/OFF
   @param[in] output    : �o�͐�
   @param[in] isOn      : �\�� ON/OFF
   @retval �Ȃ�
*/
void Line_DD_Display(GUI_OUTPUT_DEV output, BOOL isOn)
{
	switch (output) {
	case GUI_OUTPUT_LCD:
		line_DD_DisplayLcd(isOn);
		line_DD_RequestApply(output);
		break;
	case GUI_OUTPUT_HDMI:
		line_DD_DisplayHdmi(isOn);
		line_DD_RequestApply(output);
		break;
	case GUI_OUTPUT_SDI:
		line_DD_DisplaySdi(isOn);
		line_DD_RequestApply(output);
		break;
	default:
		break;
	}
}

/**
   @brief   �𑜓x�ݒ�
   @param[in] output    : �o�͐�
   @param[in] format    : �𑜓x
   @retval �Ȃ�
*/
void Line_DD_SetResolution(GUI_OUTPUT_DEV output, const LINE_MEMORY *memory, const GUI_VIDEO_FORMAT *signal)
{
	if ((memory == NULL) || (signal == NULL)) {
		return;
	}

	switch (output) {
	case GUI_OUTPUT_LCD:
		line_DD_SetResolutionLcd(memory->lineOffset, signal);
		line_DD_RequestApply(output);
		break;
	case GUI_OUTPUT_HDMI:
		line_DD_SetResolutionHdmi(memory->lineOffset, signal);
		line_DD_RequestApply(output);
		break;
	case GUI_OUTPUT_SDI:
		line_DD_SetResolutionSdi(memory->lineOffset, signal);
		line_DD_RequestApply(output);
		break;
	default:
		break;
	}
}

/**
   @brief   Vsync �����n���h���o�^
   @param[in] func    : �o�^����n���h�� (NULL �Ȃ�o�^���̃n���h�����폜)
   @retval �Ȃ�
*/
void Line_DD_SetHandlerVsync(LINE_DD_CALLBACK_FUNC func)
{
	if (handler == NULL) {
		handler = func;			/* �R�[���o�b�N�o�^�O�ɍX�V */
		/* HDMI/SDI ���荞�݂͐M���o�͂��ĂȂ��Ɗ��荞�ݓ���Ȃ��̂ŁA LCD ���荞�݂��g�� */
		AVDIrq_setCallbackLcd(line_DD_HandlerVsync);
	} else {
		handler = func;
	}
}

/**
   @brief   �n�[�h�ݒ�l�̔��f�v��
   @param[in] output  : �o�͐�
   @retval �Ȃ�
*/
void line_DD_RequestApply(GUI_OUTPUT_DEV output)
{
	switch (output) {
	case GUI_OUTPUT_LCD:
		GUIAVC_updateOsd(GUIAVC_DISP_LCD, GUIAVC_UPDATE_NORMAL);
		break;
	case GUI_OUTPUT_HDMI:
	case GUI_OUTPUT_SDI:
		GUIAVC_updateOsd(GUIAVC_DISP_LOUT, GUIAVC_UPDATE_NORMAL);
		break;
	default:
		break;
	}
}

/**
   @brief   �p���b�g�ݒ� (LCD)
   @param[in] *source   : �ݒ�f�[�^�̐擪
   @param[in] start     : �ݒ肷��p���b�g ID (�J�n���� ID)
   @param[in] num       : �ݒ肷��f�[�^��
   @retval �Ȃ�
*/
void line_DD_SetColorPaletteLcd(const UW *source, GUI_COLOR_ID start, UB num)
{
	AVC_ST_LUT_LCD lcd;
	lcd.mIndex = start;
	lcd.mNum = num;
	lcd.mpLut = (UW *)source;	/* const ����� */
	lcd.mOsd = info_lcd;
	AVD_setLutLcd(&lcd);
}

/**
   @brief   �p���b�g�ݒ� (HDMI)
   @param[in] *source   : �ݒ�f�[�^�̐擪
   @param[in] start     : �ݒ肷��p���b�g ID (�J�n���� ID)
   @param[in] num       : �ݒ肷��f�[�^��
   @retval �Ȃ�
*/
void line_DD_SetColorPaletteHdmi(const UW *source, GUI_COLOR_ID start, UB num)
{
	AVC_ST_LUT_LOUT hdmi;
	hdmi.mIndex = start;
	hdmi.mNum = num;
	hdmi.mpLut = (UW *)source;	/* const ����� */
	hdmi.mOsd = info_hdmi;
	AVD_setLutLout(&hdmi);
}

/**
   @brief   �p���b�g�ݒ� (SDI)
   @param[in] *source   : �ݒ�f�[�^�̐擪
   @param[in] start     : �ݒ肷��p���b�g ID (�J�n���� ID)
   @param[in] num       : �ݒ肷��f�[�^��
   @retval �Ȃ�
*/
void line_DD_SetColorPaletteSdi(const UW *source, GUI_COLOR_ID start, UB num)
{
	AVC_ST_LUT_LOUT sdi;
	sdi.mIndex = start;
	sdi.mNum = num;
	sdi.mpLut = (UW *)source;	/* const ����� */
	sdi.mOsd = info_sdi;
	AVD_setLutLout(&sdi);
}

/**
   @brief   �v���[���������ݒ� (LCD)
   @param[in] address : ���蓖�ăA�h���X
   @retval �Ȃ�
*/
void line_DD_SetMemoryLcd(UB *address)
{
	AVC_ST_OSD_LCD_INFO dev_lcd;
	dev_lcd.mColor = AVC_VIDEO_COLOR_OSD_RGBA4444;		// GFX�v���[���p�p�����[�^�ׁ̈A�Œ�l�Ƃ��Ă����B
	dev_lcd.mTopAddr = LINE_GET_PHYSICAL_ADDR(address);
	dev_lcd.mOsd = info_lcd;
	AVD_setDisplayOsdLcdInfo(&dev_lcd);
}

/**
   @brief   �v���[���������ݒ� (HDMI)
   @param[in] address : ���蓖�ăA�h���X
   @retval �Ȃ�
*/
void line_DD_SetMemoryHdmi(UB *address)
{
	AVC_ST_OSD_LOUT_INFO dev_hdmi;
	dev_hdmi.mColor = AVC_VIDEO_COLOR_OSD_RGBA4444;		// GFX�v���[���p�p�����[�^�ׁ̈A�Œ�l�Ƃ��Ă����B
	dev_hdmi.mTopAddr = LINE_GET_PHYSICAL_ADDR(address);
	dev_hdmi.mOsd = info_hdmi;
	AVD_setDisplayOsdLoutInfo(&dev_hdmi);
}

/**
   @brief   �v���[���������ݒ� (SDI)
   @param[in] address : ���蓖�ăA�h���X
   @retval �Ȃ�
*/
void line_DD_SetMemorySdi(UB *address)
{
	AVC_ST_OSD_LOUT_INFO dev_sdi;
	dev_sdi.mColor = AVC_VIDEO_COLOR_OSD_RGBA4444;		// GFX�v���[���p�p�����[�^�ׁ̈A�Œ�l�Ƃ��Ă����B
	dev_sdi.mTopAddr = LINE_GET_PHYSICAL_ADDR(address);
	dev_sdi.mOsd = info_sdi;
	AVD_setDisplayOsdLoutInfo(&dev_sdi);
}

/**
   @brief   OSD �\�� ON/OFF (LCD)
   @param[in] isOn   : �\�� ON/OFF
   @retval �Ȃ�
*/
void line_DD_DisplayLcd(BOOL isOn)
{
	AVC_ST_DISPLAY_LCD disp_lcd;
	disp_lcd.mIsOn = isOn;
	disp_lcd.mOsd = info_lcd;
	AVD_setDisplayOsdLcd(&disp_lcd);
}

/**
   @brief   OSD �\�� ON/OFF (HDMI)
   @param[in] isOn   : �\�� ON/OFF
   @retval �Ȃ�
*/
void line_DD_DisplayHdmi(BOOL isOn)
{
	AVC_ST_DISPLAY_LOUT disp_hdmi;
	disp_hdmi.mIsOn = isOn;
	disp_hdmi.mOsd = info_hdmi;
	AVD_setDisplayOsdLout(&disp_hdmi);
}

/**
   @brief   OSD �\�� ON/OFF (SDI)
   @param[in] isOn   : �\�� ON/OFF
   @retval �Ȃ�
*/
void line_DD_DisplaySdi(BOOL isOn)
{
	AVC_ST_DISPLAY_LOUT disp_sdi;
	disp_sdi.mIsOn = isOn;
	disp_sdi.mOsd = info_sdi;
	AVD_setDisplayOsdLout(&disp_sdi);
}

/**
   @brief   �𑜓x�ݒ� (LCD)
   @param[in] format    : �𑜓x
   @retval �Ȃ�
*/
void line_DD_SetResolutionLcd(UH lineOffset, const GUI_VIDEO_FORMAT *signal)
{
	AVC_ST_OSD_PLANE_LCD lcd;
	lcd.mWidth = signal->width;	  /* pgr0541 */
	lcd.mHeight = signal->height; /* pgr0541 */
	lcd.mMemW = lineOffset;
	lcd.mOsd = info_lcd;
	AVD_setOsdPlaneSizeLcd(&lcd);
}

/**
   @brief   �𑜓x�ݒ� (HDMI)
   @param[in] format    : �𑜓x
   @retval �Ȃ�
*/
void line_DD_SetResolutionHdmi(UH lineOffset, const GUI_VIDEO_FORMAT *signal)
{
	AVC_ST_OSD_PLANE_LOUT hdmi;
	hdmi.mWidth = signal->width;   /* pgr0541 */
	hdmi.mHeight = signal->height; /* pgr0541 */
	hdmi.mMemW = lineOffset;
	hdmi.mOsd = info_hdmi;
	AVD_setOsdPlaneSizeLout(&hdmi);
}

/**
   @brief   �𑜓x�ݒ� (SDI)
   @param[in] format    : �𑜓x
   @retval �Ȃ�
*/
void line_DD_SetResolutionSdi(UH lineOffset, const GUI_VIDEO_FORMAT *signal)
{
	AVC_ST_OSD_PLANE_LOUT sdi;
	sdi.mWidth = signal->width;	  /* pgr0541 */
	sdi.mHeight = signal->height; /* pgr0541 */
	sdi.mMemW = lineOffset;
	sdi.mOsd = info_sdi;
	AVD_setOsdPlaneSizeLout(&sdi);
}

/**
   @brief   Vsync �����n���h��
   @param[in] �Ȃ�
   @retval �Ȃ�
*/
AVC_ER line_DD_HandlerVsync(void)
{
	if (handler) {
		handler();
		return AVC_ER_CALL_NEXT_FIELD;
	}
	return AVC_ER_OK;
}
