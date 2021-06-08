/**
 *  Copyright (c) 2017 Panasonic Corporation
 *  Element:           control module of line block
 */
#include "line_ctrl.h"
#include "line_layer.h"
#include "line_color.h"
#include "line_task.h"
#include "line_dd.h"
#include "line_debug.h"
#include "gui_config.h"

/* �A�v������擾����ʒu���̊��p */
#define BASE_SCREEN_LCD_WIDTH	320	/* K519 */
#define BASE_SCREEN_LCD_HEIGHT	180	/* K519 */ // �㉺���ѕ������������l
#define BASE_SCREEN_LOUT_WIDTH	320	/* K519 */
#define BASE_SCREEN_LOUT_HEIGHT	180/* K519 */

#define LINE_ROUND(x)		((x) + 0.5f)
#define CALC_SCREEN_LCD_X_RATIO(base, width)	(((UW)(base) * (width) * 1000) / (BASE_SCREEN_LCD_WIDTH * 1000))	/* K519 */
#define CALC_SCREEN_LCD_Y_RATIO(base, height)	(((UW)(base) * (height) * 1000) / (BASE_SCREEN_LCD_HEIGHT * 1000))	/* K519 */
#define CALC_SCREEN_LOUT_X_RATIO(base, width)	(((UW)(base) * (width) * 1000) / (BASE_SCREEN_LOUT_WIDTH * 1000))	/* K519 */
#define CALC_SCREEN_LOUT_Y_RATIO(base, height)	(((UW)(base) * (height) * 1000) / (BASE_SCREEN_LOUT_HEIGHT * 1000))	/* K519 */

typedef struct {
	GUI_VIDEO_FORMAT signal;
	GUI_VIDEO_FORMAT image;
} LINE_RESOLUTION;

typedef struct _LINE_OSD_RESOLUTION_ {
	LINE_RESOLUTION global; /* �f����p */
	LINE_RESOLUTION local;  /* OSD ��p */
} LINE_OSD_RESOLUTION;

typedef struct _LINE_GUIDELINE_POS_ {
	GUI_VIDEO_FORMAT image;		/* OSD ��p */
	struct {
		UH bold;				/* ���� */
		UH start;				/* �J�n�ʒu */
		UH interval;			/* ���̐��܂ł̊Ԋu */
	} horizontal;
	struct {
		UH bold;				/* ���� */
		struct {
			UH start;			/* �J�n�ʒu */
			UH interval;		/* ���̐��܂ł̊Ԋu */
		} x, y;
	} lattice1, lattice2;
} LINE_GUIDELINE_POS;

typedef struct _LINE_FRAME_MARKER_POS_ {
	GUI_VIDEO_FORMAT image;	 /* OSD ��p */
	UH bold;				 /* ���� (���̂Ƃ���S�g�ݍ��킹�ŋ���) */
	struct {
		LINE_POS start;
		LINE_AREA area;
	} angle[GUI_FRAME_MARKER_NUM];
} LINE_FRAME_MARKER_POS;

typedef struct LINE_CENTER_MARKER_POS {
	GUI_VIDEO_FORMAT image;
	UH bold;
	struct {
		struct {
			LINE_POS start;
			UH length;
			UH blank;
		} vertical, horizon;
	} param[GUI_CENTER_MARKER_NUM];
} LINE_CENTER_MARKER_POS;

typedef struct LINE_SPOT_METER_MARKER_POS {
	GUI_VIDEO_FORMAT image;
	UH bold;
	struct {
		LINE_POS start;
		LINE_AREA area;
	} param[GUI_SPOT_METER_MARKER_NUM];
} LINE_SPOT_METER_MARKER_POS;
/*
typedef struct LINE_AF_RANGE_POS {
	UH bold;
	LINE_POS start;
	LINE_AREA area;
} LINE_AF_RANGE_POS;
*/
/* �Ǘ���� */
typedef struct _LINE_CONTROL_ {
	LINE_MEMORY memory;
	GUI_VIDEO_FORMAT signal; /* �M����p */
	GUI_VIDEO_FORMAT image;	 /* �f����p */
	struct {
		BOOL isDisp;
		GUI_FACE_FRAME_INFO layoutInfo;
		GUI_COLOR_ID color;
	} faceFrame[GUI_FACE_FRAME_NUM];
	struct {
		BOOL isDisp;
		GUI_FACE_FRAME_INFO layoutInfo;
		GUI_COLOR_ID color;
	} followFrame;
	struct {
		BOOL isDisp;
		GUI_FACE_FRAME_INFO layoutInfo;
		GUI_COLOR_ID color;
	} areaFrame;
	struct {
		GUI_GUIDELINE_TYPE type;
		GUI_COLOR_ID faColor;	/* Focus Assist �̐F (�K�C�h���C���͌Œ�Ȃ̂ŋL�����Ȃ�) */
	} guideLine;
	struct {
		GUI_SAFETY_ZONE_TYPE type;
		GUI_COLOR_ID color;
		float size;
	} safetyZone;
	struct {
		GUI_FRAME_MARKER_ANGLE angle;
		GUI_COLOR_ID color;
	} frameMarker;
	struct {
		GUI_CENTER_MARKER_TYPE type;
		GUI_COLOR_ID color;
	} centerMarker;
	struct {
		GUI_SPOT_METER_MARKER_TYPE type;
		GUI_COLOR_ID color;
	} spotMeterMarker;
    struct {
        BOOL isDisp;
		GUI_AF_RANGE_INFO layoutInfo;
		GUI_COLOR_ID color;
	} afRange;
} LINE_SCREEN;


#ifdef WIN32_GUI_SIM
UB gui_line_plane_lcd0[LINE_MEM_WIDTH_LCD*LINE_MEM_HEIGHT_LCD];
UB gui_line_plane_lcd1[LINE_MEM_WIDTH_LCD*LINE_MEM_HEIGHT_LCD];
UB gui_line_plane_hdmi0[LINE_MEM_WIDTH_HDMI*LINE_MEM_HEIGHT_HDMI];
UB gui_line_plane_hdmi1[LINE_MEM_WIDTH_HDMI*LINE_MEM_HEIGHT_HDMI];
UB gui_line_plane_sdi0[LINE_MEM_WIDTH_SDI*LINE_MEM_HEIGHT_SDI];
UB gui_line_plane_sdi1[LINE_MEM_WIDTH_SDI*LINE_MEM_HEIGHT_SDI];
#endif

/* �Ǘ���� */
static LINE_SCREEN Lcd;
static LINE_SCREEN Hdmi;
static LINE_SCREEN Sdi;

/* �����̖��M����` */
static const LINE_RESOLUTION NoSignal = {
	{0, 0}, {0, 0}
};

/* �M����p/�f����p�ɑ΂��� OSD �̐M����p�Ɖf����p */
static const LINE_OSD_RESOLUTION OsdResolution[] = {
	/* �M����p      �f����p        OSD �M��     OSD �f�� */
	{{{1920, 1080}, {1024,  576}}, {{1024, 576}, {1024, 576}}}, /* LCD 16:9 */
	{{{1920, 1080}, {1912, 1008}}, {{960,  540}, {956,  504}}}, /* LCD 17:9 */
	{{{1920, 1080}, {1792, 1008}}, {{960,  540}, {896,  504}}}, /* LCD 16:9 */
	{{{1920, 1080}, {1892, 1008}}, {{960,  540}, {946,  504}}}, /* LCD S35 5.7K(5760*3072)1.875:1 */
	{{{4096, 2160}, {4096, 2160}}, {{1024, 540}, {1024, 540}}},
	{{{2048, 1080}, {2048, 1080}}, {{1024, 540}, {1024, 540}}},
	{{{3840, 2160}, {3840, 2160}}, {{960,  540}, {960,  540}}},
	{{{1920, 1080}, {1920, 1080}}, {{960,  540}, {960,  540}}},
	{{{1920, 1080}, {1920, 1012}}, {{960,  540}, {960,  506}}}, /* 16:9 �M���� 17:9 �o�� */
	{{{1920, 1080}, {1900, 1012}}, {{960,  540}, {950,  506}}}, /* HDMI S35 5.7K(5760*3072)1.875:1 */
	{{{1280,  720}, {1280,  720}}, {{640,  360}, {640,  360}}},
	{{{1024,  768}, {768,   480}}, {{1024, 576}, {768,  480}}}, /* STD NTSC 4:3 */
	{{{1024,  768}, {768,   576}}, {{1024, 576}, {768,  576}}}, /* STD PAL 4:3 */
};

/* �K�C�h���C���ʒu */
static const LINE_GUIDELINE_POS GuideLinePos[] = {
	/* ������     ����           �i�q1                         �i�q2 */
	/* �f����p   ��  �J�n �Ԋu  ��  �J�nx �J�ny �Ԋux �Ԋuy  ��  �J�nx �J�ny �Ԋux �Ԋuy */
	{{960,  540}, {2, 89,  180}, {2, {318, 322}, {178, 182}}, {2, {4,   95},  {79,  95}}}, /* HDMI/SDI FHD, UHD */
	{{956,  504}, {2, 83,  168}, {2, {317, 320}, {166, 170}}, {2, {37,  88},  {75,  88}}}, /* LCD (17:9) */
	{{896,  504}, {2, 83,  168}, {2, {297, 300}, {166, 170}}, {2, {7,   88},  {75,  88}}}, /* LCD (16:9) */
	{{1024, 540}, {2, 89,  180}, {2, {340, 342}, {178, 182}}, {2, {36,  95},  {79,  95}}}, /* HDMI/SDI 2K, 4K */
	{{960,  506}, {2, 84,  168}, {2, {318, 322}, {167, 170}}, {2, {34,  89},  {74,  89}}}, /* HDMI/SDI 2K on FHD */
	{{640,  360}, {2, 59,  120}, {2, {212, 214}, {118, 122}}, {2, {4,   63},  {53,  63}}}, /* HDMI/SDI 720p */
	{{720,  480}, {2, 79,  160}, {2, {238, 242}, {158, 162}}, {2, {9,   70},  {71,  84}}}, /* HDMI 480p */
	{{720,  576}, {2, 95,  192}, {2, {238, 242}, {190, 194}}, {2, {4,   71},  {85,  101}}}, /* HDMI 576p */
    {{1024, 576}, {2, 83,  168}, {2, {317, 320}, {166, 170}}, {2, {37,  88},  {75,  88}}}, /* LCD (17:9) */
};

/* �t���[���}�[�J�[�ʒu */
static const LINE_FRAME_MARKER_POS FrameMarkerPos[] = {
		/*{OSD ��p},��, {{ �I�t         }, { 1.33:1              }, { 1.44:1              }, { 1.56:1             }, { 1.78:1             }, { 1.85:1              }, { 2.00:1              }, { 2.201:1             }, { 2.35:1              }, { 2.39:1              }} */
		/*       	    ,{{{�ʒu}, {�̈�}}, {{ �ʒu  }, { �̈�   }}, {{ �ʒu  }, { �̈�   }}, {{ �ʒu }, {�̈�    }}, {{ �ʒu }, { �̈�   }}, {{ �ʒu }, { �̈�    }}, {{ �ʒu }, { �̈�    }}, {{ �ʒu }, { �̈�    }}, {{ �ʒu }, { �̈�    }}, {{ �ʒu }, { �̈�    }}} */
/*��*/  {{1024, 576}, 4, {{{0, 0}, {0, 0}}, {{126,  0}, {772, 576}}, {{ 94,  0}, {834, 576}}, {{62,  0}, {900, 576}}, {{ 0,  0}, {1024,576}}, {{ 0,  9}, {1024, 558}}, {{0,  30}, {1024, 516}}, {{0,  53}, {1024, 470}}, {{0,  68}, {1024, 440}}, {{0,  72}, {1024, 432}}}},
		{{1024, 540}, 2, {{{0, 0}, {0, 0}}, {{151,  0}, {722, 540}}, {{121,  0}, {782, 540}}, {{91,  0}, {842, 540}}, {{31,  0}, {962, 540}}, {{11,  0}, {1002, 540}}, {{0,  13}, {1024, 514}}, {{0,  36}, {1024, 468}}, {{0,  51}, {1024, 438}}, {{0,  55}, {1024, 430}}}},
        {{ 956, 504}, 2, {{{0, 0}, {0, 0}}, {{141,  0}, {674, 504}}, {{113,  0}, {730, 504}}, {{85,  0}, {786, 504}}, {{29,  0}, {898, 504}}, {{11,  0}, { 934, 504}}, {{0,  12}, { 956, 480}}, {{0,  34}, { 956, 436}}, {{0,  48}, { 956, 408}}, {{0,  51}, { 956, 402}}}},
        {{ 946, 504}, 2, {{{0, 0}, {0, 0}}, {{136,  0}, {674, 504}}, {{108,  0}, {730, 504}}, {{80,  0}, {786, 504}}, {{24,  0}, {898, 504}}, {{ 6,  0}, { 934, 504}}, {{0,  14}, { 946, 476}}, {{0,  36}, { 946, 432}}, {{0,  50}, { 946, 404}}, {{0,  53}, { 946, 398}}}},
		{{ 896, 504}, 2, {{{0, 0}, {0, 0}}, {{111,  0}, {674, 504}}, {{ 83,  0}, {730, 504}}, {{55,  0}, {786, 504}}, {{ 0,  0}, {896, 504}}, {{ 0,  9}, { 896, 486}}, {{0,  27}, { 896, 450}}, {{0,  47}, { 896, 410}}, {{0,  60}, { 896, 384}}, {{0,  64}, { 896, 376}}}},
		{{ 960, 506}, 2, {{{0, 0}, {0, 0}}, {{142,  0}, {676, 506}}, {{114,  0}, {732, 506}}, {{86,  0}, {788, 506}}, {{29,  0}, {902, 506}}, {{11,  0}, { 938, 506}}, {{0,  12}, { 960, 482}}, {{0,  34}, { 960, 438}}, {{0,  48}, { 960, 410}}, {{0,  51}, { 960, 404}}}},
		{{ 960, 540}, 2, {{{0, 0}, {0, 0}}, {{119,  0}, {722, 540}}, {{ 89,  0}, {782, 540}}, {{59,  0}, {842, 540}}, {{ 0,  0}, {960, 540}}, {{ 0, 10}, { 960, 520}}, {{0,  29}, { 960, 482}}, {{0,  51}, { 960, 438}}, {{0,  65}, { 960, 410}}, {{0,  68}, { 960, 404}}}},
		{{ 640, 360}, 2, {{{0, 0}, {0, 0}}, {{ 79,  0}, {482, 360}}, {{ 59,  0}, {522, 360}}, {{39,  0}, {562, 360}}, {{ 0,  0}, {640, 360}}, {{ 0,  6}, { 640, 348}}, {{0,  19}, { 640, 322}}, {{0,  34}, { 640, 292}}, {{0,  43}, { 640, 274}}, {{0,  45}, { 640, 270}}}},
		{{ 720, 480}, 2, {{{0, 0}, {0, 0}}, {{ 39,  0}, {642, 480}}, {{ 12,  0}, {696, 480}}, {{ 0,  7}, {720, 466}}, {{ 0, 36}, {720, 408}}, {{ 0, 44}, { 720, 392}}, {{0,  59}, { 720, 362}}, {{0,  75}, { 720, 330}}, {{0,  86}, { 720, 308}}, {{0,  88}, { 720, 304}}}},
		{{ 720, 576}, 2, {{{0, 0}, {0, 0}}, {{  0, 17}, {720, 542}}, {{  0, 38}, {720, 500}}, {{ 0, 55}, {720, 466}}, {{ 0, 84}, {720, 408}}, {{ 0, 92}, { 720, 392}}, {{0, 107}, { 720, 362}}, {{0, 123}, { 720, 330}}, {{0, 134}, { 720, 308}}, {{0, 136}, { 720, 304}}}}
};

/* �Z���^�[�}�[�J�[�ʒu */
static const LINE_CENTER_MARKER_POS CenterMarkerPos[] = {
	/*  {OSD��p   }, ��,{{ �I�t                        },{ �� (+)                                      },{ �� (����)                                   },{ �� (+)                                      },{ �� (����)                                 }} */
	/*  {          },  , {{{{x, y},��,��},{{x, y},��,��}},{{��x,   ��y},  ��, ��},{{��x,  ��y},  ��, ��}},{{{��x,  ��y},  ��,  ��},{{��x,  ��y},  ��,  ��}},{{{��x,  ��y},  ��, ��},{{��x,  ��y},  ��, ��}},{{{��x,  ��y},  ��, ��} {{��x,  ��y},  ��, ��}}} */
 /*��*/ {{1024, 576}, 4, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{510,  268},  40,  0},{{486,  286},  52,  0}},{{{510,  268},  40,  14},{{486,  286},  52,  14}},{{{510,  278},  20,  0},{{499,  286},  26,  0}},{{{510,  278},  20,  8},{{499,  286},  26,  8}}}},
 /*��*/ {{768,  576}, 4, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{382,  268},  40,  0},{{358,  286},  52,  0}},{{{382,  268},  40,  14},{{358,  286},  52,  14}},{{{283,  278},  20,  0},{{371,  286},  26,  0}},{{{382,  278},  20,  8},{{371,  286},  26,  8}}}},
 ///*��*/ {{768,  480}, 2, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{383,  220},  40,  0},{{358,  239},  52,  0}},{{{383,  220},  40,  14},{{358,  239},  52,  14}},{{{383,  230},  20,  0},{{371,  239},  26,  0}},{{{383,  230},  20,  8},{{371,  239},  26,  8}}}},
		{{956,  504}, 2, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{477,  234},  36,  0},{{454,  251},  48,  0}},{{{477,  234},  36,  12},{{454,  251},  48,  12}},{{{477,  243},  18,  0},{{466,  251},  24,  0}},{{{477,  243},  18,  6},{{466,  251},  24,  6}}}},
		{{946,  504}, 2, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{472,  234},  36,  0},{{449,  251},  48,  0}},{{{472,  234},  36,  12},{{449,  251},  48,  12}},{{{472,  243},  18,  0},{{461,  251},  24,  0}},{{{472,  243},  18,  6},{{461,  251},  24,  6}}}},
		{{896,  504}, 2, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{447,  234},  36,  0},{{424,  251},  48,  0}},{{{447,  234},  36,  12},{{424,  251},  48,  12}},{{{447,  243},  18,  0},{{436,  251},  24,  0}},{{{447,  243},  18,  6},{{436,  251},  24,  6}}}},
		{{1024, 540}, 2, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{511,  252},  36,  0},{{488,  269},  48,  0}},{{{511,  252},  36,  12},{{488,  269},  48,  12}},{{{511,  261},  18,  0},{{500,  269},  24,  0}},{{{511,  261},  18,  6},{{500,  269},  24,  6}}}},
		{{960,  506}, 2, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{479,  235},  36,  0},{{456,  252},  48,  0}},{{{479,  235},  36,  12},{{456,  252},  48,  12}},{{{479,  244},  18,  0},{{468,  252},  24,  0}},{{{479,  244},  18,  6},{{468,  252},  24,  6}}}},
		{{960,  540}, 2, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{479,  252},  36,  0},{{456,  269},  48,  0}},{{{479,  252},  36,  12},{{456,  269},  48,  12}},{{{479,  261},  18,  0},{{468,  269},  24,  0}},{{{479,  261},  18,  6},{{468,  269},  24,  6}}}},
		{{640,  360}, 2, {{{{0, 0}, 0, 0},{{0, 0}, 0, 0}},{{{319,  168},  24,  0},{{304,  179},  32,  0}},{{{319,  168},  24,   8},{{304,  179},  32,   8}},{{{319,  174},  12,  0},{{312,  179},  16,  0}},{{{319,  174},  12,  4},{{312,  179},  16,  4}}}},
 };

/* �X�|�b�g���[�^�[�}�[�J�[�ʒu */
static const LINE_SPOT_METER_MARKER_POS SpotMeterPos[] = {
		/* {OSD��p},��, {{ �I�t        },{ S                   },{ M                    },{ L                    }} */
		/* {       }     {{{x, y},{w, h}},{{x,    y  },  {w,  h}},{{x,    y  },  {w,  h }},{{x,    y  }   {w,  h }}} */
 /*��*/ {{1024, 576}, 4, {{{0, 0},{0, 0}},{{508,  284},  {8,  8}},{{506,  282},  {12, 12}},{{492,  268},  {40,  40}}}},
 /*��*/ {{768,  576}, 4, {{{0, 0},{0, 0}},{{380,  284},  {8,  8}},{{378,  282},  {12, 12}},{{369,  268},  {30,  40}}}},
 ///*��*/ {{768,  480}, 4, {{{0, 0},{0, 0}},{{381,  237},  {6,  6}},{{379,  235},  {10, 10}},{{370,  221},  {28,  38}}}},
        {{956,  504}, 2, {{{0, 0},{0, 0}},{{475,  249},  {6,  6}},{{473,  247},  {10, 10}},{{462,  236},  {32,  32}}}},
		{{946,  504}, 2, {{{0, 0},{0, 0}},{{470,  249},  {6,  6}},{{468,  247},  {10, 10}},{{457,  236},  {32,  32}}}},
		{{896,  504}, 2, {{{0, 0},{0, 0}},{{445,  249},  {6,  6}},{{443,  247},  {10, 10}},{{432,  236},  {32,  32}}}},
		{{1024, 540}, 2, {{{0, 0},{0, 0}},{{509,  267},  {6,  6}},{{507,  265},  {10, 10}},{{495,  253},  {34,  34}}}},
		{{960,  506}, 2, {{{0, 0},{0, 0}},{{477,  250},  {6,  6}},{{475,  248},  {10, 10}},{{464,  237},  {32,  32}}}},
		{{960,  540}, 2, {{{0, 0},{0, 0}},{{477,  267},  {6,  6}},{{475,  265},  {10, 10}},{{463,  253},  {34,  34}}}},
		{{640,  360}, 2, {{{0, 0},{0, 0}},{{317,  177},  {6,  6}},{{316,  176},  { 8,  8}},{{308,  168},  {24,  24}}}},
		{{768,  576}, 2, {{{0, 0},{0, 0}},{{381,  285},  {6,  6}},{{379,  283},  {10, 10}},{{368,  272},  {32,  32}}}},
		{{768,  480}, 2, {{{0, 0},{0, 0}},{{381,  237},  {6,  6}},{{379,  235},  {10, 10}},{{368,  224},  {32,  32}}}}
};

/* ���[�J���֐� */
static LINE_SCREEN* line_GetScreen(GUI_OUTPUT_DEV output);
static LINE_ERR line_SetMemory(GUI_OUTPUT_DEV output, const LINE_MEMORY *memory);
static LINE_ERR line_ClearMemory(GUI_OUTPUT_DEV output);
static LINE_ERR line_SetResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image);
static void line_GetResolution(LINE_RESOLUTION *resolution, const GUI_VIDEO_FORMAT *globalSignal, const GUI_VIDEO_FORMAT *globalImage);
static BOOL line_IsChangeResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image);
static LINE_ERR line_SetDrawOffset(GUI_OUTPUT_DEV output);
static BOOL line_SetParamFaceFrame(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, UW faceFrameId, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color);
static BOOL line_SetParamAfRangeMarker(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_AF_RANGE_INFO* layoutInfo, BOOL isDisp, GUI_COLOR_ID color);
static BOOL line_SetParamFollowFrame(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color);
static BOOL line_SetParamAreaFrame(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color);
static BOOL line_SetParamGuideLine(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_GUIDELINE_TYPE guideType);
static BOOL line_SetParamFocusAssist(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, BOOL isDisp);
static BOOL line_SetParamSafetyzone(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_SAFETY_ZONE_TYPE type, float size, GUI_COLOR_ID color);
static BOOL line_SetParamFrameMarker(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_FRAME_MARKER_ANGLE angle, GUI_COLOR_ID color);
static BOOL line_SetParamCenterMarker(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_CENTER_MARKER_TYPE type, GUI_COLOR_ID color);
static BOOL line_SetParamSpotMeterMarker(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_SPOT_METER_MARKER_TYPE type, GUI_COLOR_ID color);
static void line_CreateBracketParam(LINE_DRAW_BRACKET *bracket, LINE_SCREEN *screen, GUI_FACE_FRAME_INFO *layoutInfo, GUI_COLOR_ID mainColor, GUI_COLOR_ID edgeColor);
static void line_CreateCrossParam(LINE_DRAW_CROSS *cross, LINE_SCREEN *screen, GUI_FACE_FRAME_INFO *layoutInfo, GUI_COLOR_ID mainColor, GUI_COLOR_ID edgeColor);
static void line_Redraw(GUI_OUTPUT_DEV output);

/**
   @brief   LINE �u���b�N�̏�����
   @param[in] �Ȃ�
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_InitCtrl(void)
{
	LINE_SCREEN *screenTab[] = {&Lcd, &Hdmi, &Sdi};
	UB ii;

	/* �������ݒ�l */
	static const LINE_MEMORY memory_lcd = {
		LINE_MEM_WIDTH_LCD,		/* lineOffset */
		LINE_MEM_HEIGHT_LCD,	/* height */
		LINE_PLANE_LCD0,		/* addr */
		{0, 0}					/* DrawOffset */
	};
	static const LINE_MEMORY memory_hdmi = {
		LINE_MEM_WIDTH_HDMI,	/* lineOffset */
		LINE_MEM_HEIGHT_HDMI,	/* height */
		LINE_PLANE_HDMI0,		/* addr */
		{0, 0}					/* DrawOffset */
	};
	static const LINE_MEMORY memory_sdi = {
		LINE_MEM_WIDTH_SDI,		/* lineOffset */
		LINE_MEM_HEIGHT_SDI,	/* height */
		LINE_PLANE_SDI0,		/* addr */
		{0, 0}					/* DrawOffset */
	};

	/* �Ǘ��ϐ��̏����� (static �̈悾���� ALL 0 �ɂȂ��Ă���͂��Ȃ̂ŁA�����I�ȏ��������K�v�ȃ����o�����L�q����) */
	for (ii = 0; ii < sizeof screenTab / sizeof(LINE_SCREEN *); ii++) {
		screenTab[ii]->guideLine.type = GUI_GUIDELINE_TYPE_NONE;
		screenTab[ii]->safetyZone.type = GUI_SAFETY_ZONE_TYPE_OFF;
		screenTab[ii]->frameMarker.angle = GUI_FRAME_MARKER_OFF;
	}

	/* �������ݒ� */
	line_SetMemory(GUI_OUTPUT_LCD, &memory_lcd);
	line_SetMemory(GUI_OUTPUT_HDMI, &memory_hdmi);
	line_SetMemory(GUI_OUTPUT_SDI, &memory_sdi);

	/* �𑜓x�̏����� (���M��) */
	line_SetResolution(GUI_OUTPUT_LCD, NULL, NULL);
	line_SetResolution(GUI_OUTPUT_HDMI, NULL, NULL);
	line_SetResolution(GUI_OUTPUT_SDI, NULL, NULL);

	/* �\�� OFF (�n�[�h�ݒ�) */
	Line_DD_Display(GUI_OUTPUT_LCD, FALSE);
	Line_DD_Display(GUI_OUTPUT_HDMI, FALSE);
	Line_DD_Display(GUI_OUTPUT_SDI, FALSE);

	return LINE_OK;
}

/**
   @brief   �o�͉�p�ύX�v��
   @param[in] output  : �o�͐�
   @param[in] *format : �r�f�I�t�H�[�}�b�g
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_RequestChangeResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *globalSignal, const GUI_VIDEO_FORMAT *globalImage)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	LINE_RESOLUTION newResolution;
	BOOL isChange;

	if (screen == NULL) {
		return LINE_ERR_BADARG;
	}

	line_GetResolution(&newResolution, globalSignal, globalImage);

	isChange = line_IsChangeResolution(output, &(newResolution.signal), &(newResolution.image));
	if (isChange == TRUE) {
		LineDebugPrint("dev=%d signal(%d,%d) image(%d,%d)\n", output, globalSignal->width, globalSignal->height, globalImage->width, globalImage->height);
		/* OSD �����v�����o���Ă���𑜓x�ύX���� */
		Line_DD_Display(output, FALSE);
		Line_SendMessageChangeResolution(output, &(newResolution.signal), &(newResolution.image));
	}
	return LINE_OK;
}

/**
   @brief   �o�͉�p�ύX
   @param[in] output  : �o�͐�
   @param[in] *format : �r�f�I�t�H�[�}�b�g
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_ChangeResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	if (screen == NULL) {
		return LINE_ERR_BADARG;
	}

	/* �{���Ȃ�A OSD �����v�������f����Ă���𑜓x�ύX���ׂ������A
	   ���̏p���Ȃ��̂łƂ肠�������u�B�S�~��������Ƃ���������l���� */

	/* (AVIO �̃^�X�N�D��x�������̂�) �����𑜓x�̗v��������ꍇ������̂ŁA�����ł�����x�`�F�b�N */
	if (line_IsChangeResolution(output, signal, image) != TRUE) {
		return LINE_OK;
	}

	line_SetResolution(output, signal, image);
	if (((signal == NULL) || (image == NULL))
		|| ((signal->width == NoSignal.signal.width) && (signal->height == NoSignal.signal.height))
		|| ((image->width == NoSignal.image.width) && (image->height == NoSignal.image.height))) { /* �M���Ȃ��̏ꍇ */
		return LINE_OK;			/* �ȍ~�̏����͕K�v�Ȃ� */
	}
	LineDebugPrint("dev=%d signal(%d,%d) image(%d,%d)\n", output, signal->width, signal->height, image->width, image->height);
	line_ClearMemory(output); /* ��p���ς��̂ŁA�`�惁��������x�S�N���A */
	line_SetDrawOffset(output);	/* �`�掞�̃I�t�Z�b�g���X�V */
	Line_DD_SetResolution(output, &(screen->memory), signal);
	line_Redraw(output);		   /* OSD �ĕ`�� */
	Line_DD_Display(output, TRUE); /* OSD �\�� ON */
	return LINE_OK;
}

/**
   @brief   �t�H�[�J�X�A�V�X�g�g�̐F�ݒ�
   @param[in] output      : �\����̑I��
   @param[in] color       : �J���[�p���b�gID
   @retval �Ȃ�
*/
LINE_ERR Line_SetColorFocusAssist(GUI_OUTPUT_DEV output, GUI_COLOR_ID color)
{
	LINE_SCREEN *screen = line_GetScreen(output);

	if (screen == NULL) {
		return LINE_ERR_BADARG;
	}

	/* �\�����Ȃ�ĕ`�� */
	if (screen->guideLine.faColor != color) {
		screen->guideLine.faColor = color;
		if (screen->guideLine.type == GUI_GUIDELINE_TYPE_FA) {
			Line_DrawFocusAssist(output, TRUE);
		}
	}
	return LINE_OK;
}

LINE_ERR Line_DrawAfRange(GUI_OUTPUT_DEV output, GUI_AF_RANGE_INFO *layoutInfo, BOOL isDisp){
	// LineDebugPrint("dev=%d startX=%d startY=%d areaX=%d areaY=%d bold=%d Disp=%d color=%d\n", 
	//    output, startPos.x, startPos.y, areaPos.x, areaPos.y, isDisp);

	LINE_DRAW_OBJECT *object;

	object = Line_CreateDrawObj(LINE_OBJ_AF_RANGE);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (TRUE != line_SetParamAfRangeMarker(object, output, layoutInfo, isDisp, GUI_COLOR_ID_MARKER_RED)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	return Line_RequestLayer(output, LINE_LAYER_AF_RANGE, isDisp, object);
}

/**
   @brief   ��g�̕`��
   @param[in] output      : �\����̑I��
   @param[in] faceFrameId : ��gID
   @param[in] *layoutInfo : �z�u���
   @param[in] isDisp      : �\���� ON/OFF �w��
   @param[in] color       : �F
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_DrawFaceFrame(GUI_OUTPUT_DEV output, UW faceFrameId, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color)
{
	LINE_DRAW_OBJECT *object;
	LINE_OBJECT_ID obj_id = LINE_OBJ_FACE_FRAME_MIN;
	obj_id += faceFrameId;		/* ��s�ŏ����� Warning (�قȂ�^�C�v�̉��Z) ���o��̂ŕ����s�ɕ����� */

	if ((layoutInfo == NULL) || (obj_id > LINE_OBJ_FACE_FRAME_MAX)) {
		return LINE_ERR_BADARG;
	}

	object = Line_CreateDrawObj(obj_id);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (TRUE != line_SetParamFaceFrame(object, output, faceFrameId, layoutInfo, isDisp, color)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	return Line_RequestLayer(output, LINE_LAYER_FACE, isDisp, object);
}

/**
   @brief   �ǂ������g (�ǔ����蒆/�ǔ�NG) �̕`��
   @param[in] output        : �\����̑I��
   @param[in] *layoutInfo   : �z�u���
   @param[in] isDisp        : �\���� ON/OFF �w��
   @param[in] color         : �F
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_DrawFollowFrame(GUI_OUTPUT_DEV output, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color)
{
	LINE_DRAW_OBJECT *object;

	if (layoutInfo == NULL) {
		return LINE_ERR_BADARG;
	}

	object = Line_CreateDrawObj(LINE_OBJ_FOLLOW_FRAME);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	/* �p�����[�^�쐬 */
	if (TRUE != line_SetParamFollowFrame(object, output, layoutInfo, isDisp, color)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	return Line_RequestLayer(output, LINE_LAYER_FOLLOW, isDisp, object);
}

/**
   @brief   �G���A�g�A�ǂ������ǔ����g�̕`��
   @param[in] output      : �\����̑I��
   @param[in] layoutInfo  : �z�u���
   @param[in] isDisp      : �\���� ON/OFF �w��
   @param[in] color       : �F
   @retval LINE_ERR (@ref line_ctrl.h)
*/
/*
	UH hpos;					// ���������̕\���J�n 
	UH vpos;					/ ���������̕\���J�n�ʒu 
	UH width;					/ ���������̑傫�� 
	UH height;					/ ���������̑傫�� 
	UH vsize;					/ �c���̑��� 
	UH hsize;					/ �����̑��� 
	UH waku_size;				/ ���̑��� 
	UH kagi_hsize; / �ꊇ�ʂ̐��������̑傫���A�\���̐����������� 1/2 
	UH kagi_vsize; / �ꊇ�ʂ̐��������̑傫���A�\���̐����������� 1/2 

*/
LINE_ERR Line_DrawAreaFrame(GUI_OUTPUT_DEV output, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color)
{
	LINE_DRAW_OBJECT *object;

	if (layoutInfo == NULL) {
		return LINE_ERR_BADARG;
	}
	LineDebugPrint("dev=%d hpos=%d vpos=%d width=%d height=%d\n", output, layoutInfo->hpos, layoutInfo->vpos, layoutInfo->width, layoutInfo->height);
    LineDebugPrint("vsize=%d hsize=%d waku_size=%d kagi_hsize=%d kagi_vsize=%d\n", layoutInfo->vsize, layoutInfo->hsize, layoutInfo->waku_size, layoutInfo->kagi_hsize, layoutInfo->kagi_vsize);
    
	object = Line_CreateDrawObj(LINE_OBJ_AREA_FRAME);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	/* �p�����[�^���� */
	if (TRUE != line_SetParamAreaFrame(object, output, layoutInfo, isDisp, color)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	return Line_RequestLayer(output, LINE_LAYER_FOLLOW, isDisp, object);
}

/**
   @brief   �K�C�h���C���̕`��
   @param[in] output      : �\����̑I��
   @param[in] guideType   : �K�C�h���C�����
   @param[in] resolution  : �\����ʉ𑜓x (�K�C�h���C���p)
   @param[in] color       : �F
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_DrawGuideLine(GUI_OUTPUT_DEV output, GUI_GUIDELINE_TYPE guideType)
{
	BOOL isDisp = TRUE;
	LINE_DRAW_OBJECT *object;

	object = Line_CreateDrawObj(LINE_OBJ_GUIDELINE);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	/* �p�����[�^���� */
	if (TRUE != line_SetParamGuideLine(object, output, guideType)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	if (guideType == GUI_GUIDELINE_TYPE_NONE) {
		isDisp = FALSE;
	}

	return Line_RequestLayer(output, LINE_LAYER_GUIDELINE, isDisp, object);
}

/**
   @brief   FA �g�̕`��
   @param[in] output      : �\����̑I��
   @param[in] isDisp      : �\���� ON/OFF �w��
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_DrawFocusAssist(GUI_OUTPUT_DEV output, BOOL isDisp)
{
	LINE_DRAW_OBJECT *object;

	if(output != GUI_OUTPUT_LCD){ /* LOUT �� FA ���� */
		return LINE_ERR_NOT_SUPPORTED;
	}

	object = Line_CreateDrawObj(LINE_OBJ_GUIDELINE); /* ID �̓K�C�h���C������ */
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (TRUE != line_SetParamFocusAssist(object, output, isDisp)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	return Line_RequestLayer(output, LINE_LAYER_GUIDELINE, isDisp, object);
}

/**
   @brief   �Z�[�t�e�B�]�[���g�̕`��
   @param[in] output      : �\����̑I��
   @param[in] type        : �}�[�J�[��� (TYPE_OFF �ŕ\�� OFF)
   @param[in] size        : �}�[�J�[�T�C�Y
   @param[in] color       : �}�[�J�[�F
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_DrawSafetyzone(GUI_OUTPUT_DEV output, GUI_SAFETY_ZONE_TYPE type, float size, GUI_COLOR_ID color)
{
	LINE_DRAW_OBJECT *object;
	BOOL isDisp = TRUE;

	LineDebugPrint("dev=%d type=%d size=%f color=%d\n", output, type, size, color);

	object = Line_CreateDrawObj(LINE_OBJ_SAFETY_ZONE);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (TRUE != line_SetParamSafetyzone(object, output, type, size, color)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	if (type == GUI_SAFETY_ZONE_TYPE_OFF) {
		isDisp = FALSE;
	}

	return Line_RequestLayer(output, LINE_LAYER_SAFETY_ZONE, isDisp, object);
}

/**
   @brief   �t���[���}�[�J�[�̕`��
   @param[in] output      : �\����̑I��
   @param[in] angle       : �}�[�J�[��� (TYPE_OFF �ŕ\�� OFF)
   @param[in] color       : �}�[�J�[�F
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_DrawFrameMarker(GUI_OUTPUT_DEV output, GUI_FRAME_MARKER_ANGLE angle, GUI_COLOR_ID color)
{
	LINE_DRAW_OBJECT *object;
	BOOL isDisp = TRUE;

	LineDebugPrint("dev=%d angle=%d color=%d\n", output, angle, color);

	object = Line_CreateDrawObj(LINE_OBJ_FRAME_MARKER);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (TRUE != line_SetParamFrameMarker(object, output, angle, color)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	if (angle == GUI_FRAME_MARKER_OFF) {
		isDisp = FALSE;
	}

	return Line_RequestLayer(output, LINE_LAYER_SAFETY_ZONE, isDisp, object);
}

/**
   @brief   �Z���^�[�}�[�J�[�̕`��
   @param[in] output      : �\����̑I��
   @param[in] type        : �}�[�J�[��� (TYPE_OFF �ŕ\�� OFF)
   @param[in] color       : �}�[�J�[�F
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_DrawCenterMarker(GUI_OUTPUT_DEV output, GUI_CENTER_MARKER_TYPE type, GUI_COLOR_ID color)
{
	LINE_DRAW_OBJECT *object;
	BOOL isDisp = TRUE;

	LineDebugPrint("dev=%d type=%d color=%d\n", output, type, color);

	object = Line_CreateDrawObj(LINE_OBJ_CENTER_MARKER);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (TRUE != line_SetParamCenterMarker(object, output, type, color)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	if (type == GUI_CENTER_MARKER_OFF) {
		isDisp = FALSE;
	}

	return Line_RequestLayer(output, LINE_LAYER_FOLLOW, isDisp, object);
}

/**
   @brief   �X�|�b�g���[�^�[�}�[�J�[�̕`��
   @param[in] output      : �\����̑I��
   @param[in] type        : �}�[�J�[��� (TYPE_OFF �ŕ\�� OFF)
   @param[in] color       : �}�[�J�[�F
   @retval LINE_ERR (@ref line_ctrl.h)
*/
LINE_ERR Line_DrawSpotMeterMarker(GUI_OUTPUT_DEV output, GUI_SPOT_METER_MARKER_TYPE type, GUI_COLOR_ID color)
{
	LINE_DRAW_OBJECT *object;
	BOOL isDisp = TRUE;

	LineDebugPrint("dev=%d type=%d color=%d\n", output, type, color);

	object = Line_CreateDrawObj(LINE_OBJ_SPOT_METER_MARKER);
	if (object == NULL) {
		return LINE_ERR_NOMEM;
	}

	if (TRUE != line_SetParamSpotMeterMarker(object, output, type, color)) {
		Line_DeleteDrawObj(object);
		return LINE_ERR_BADARG;
	}

	if (type == GUI_SPOT_METER_MARKER_OFF) {
		isDisp = FALSE;
	}

	return Line_RequestLayer(output, LINE_LAYER_SPOT_METER, isDisp, object);
}

/* ���[�J���֐� */
/**
   @brief   �\���Ǘ����̎擾
   @param[in] output  : �o�͐�
   @retval LINE_SCREEN (�G���[���� NULL)
*/
LINE_SCREEN* line_GetScreen(GUI_OUTPUT_DEV output)
{
	LINE_SCREEN *screen = NULL;

	switch (output) {
	case GUI_OUTPUT_LCD:
		screen = &Lcd;
		break;
	case GUI_OUTPUT_HDMI:
		screen = &Hdmi;
		break;
	case GUI_OUTPUT_SDI:
		screen = &Sdi;
		break;
	default:
		break;
	}
	return screen;
}

/**
   @brief   ���������o�^
   @param[in] output   : �o�͐�
   @param[in] *memory  : ���������
   @retval LINE_ERR (@ref line_ctrl)
*/
LINE_ERR line_SetMemory(GUI_OUTPUT_DEV output, const LINE_MEMORY *memory)
{
	LINE_SCREEN *screen = line_GetScreen(output);

	if ((screen == NULL) || (memory == NULL)) {
		return LINE_ERR_BADARG;
	}
	screen->memory = *memory;

	Line_DD_SetMemory(output, memory->addr);
	return LINE_OK;
}

/**
   @brief   �`�惁�����N���A
   @param[in] output   : �o�͐�
   @param[in] *memory  : ���������
   @retval LINE_ERR (@ref line_ctrl)
*/
LINE_ERR line_ClearMemory(GUI_OUTPUT_DEV output)
{
	LINE_SCREEN *screen = line_GetScreen(output);

	if (screen == NULL) {
		return LINE_ERR_BADARG;
	}

	/* Draw ���g���ƁA�I�t�Z�b�g�����Ă��܂��̂Œ��œh��ׂ� */
	memset(screen->memory.addr, GUI_COLOR_ID_DELETE, screen->memory.lineOffset * screen->memory.height);
	return LINE_OK;
}

/**
   @brief   OSD �̐M����p�E�f����p��ݒ�
   @param[in] output  : �o�͐�
   @param[in] *signal : OSD �M����p
   @param[in] *image  : OSD �f����p
   @retval TRUE �X�V���� / FALSE �X�V�Ȃ�
*/
LINE_ERR line_SetResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image)
{

	LINE_SCREEN *screen = line_GetScreen(output);

	if (screen == NULL) {
		return LINE_ERR_BADARG;
	}

	if ((signal == NULL) || (image == NULL)) {
		screen->signal = NoSignal.signal;
		screen->image = NoSignal.image;
	} else {
		screen->signal = *signal;
		screen->image = *image;
	}
	return LINE_OK;
}

/**
   @brief   �M����p�E�f����p���� OSD �M����p�E�f����p�𓾂�
   @param[out] *resolution  : OSD �𑜓x�i�[��
   @param[in] *globalSignal : �M����p
   @param[in] *globalImage  : �f����p
   @retval �Ȃ�
*/
void line_GetResolution(LINE_RESOLUTION *resolution, const GUI_VIDEO_FORMAT *globalSignal, const GUI_VIDEO_FORMAT *globalImage)
{
	const LINE_RESOLUTION *find = NULL; /* �e�[�u�������l */

	if (resolution == NULL) {
		return;
	}

	if ((globalSignal == NULL) || (globalImage == NULL)) {		/* NULL �w�� = �M�� OFF */
		find = NULL;
	} else {
		UB ii;
		for (ii = 0; ii < sizeof(OsdResolution)/sizeof(LINE_OSD_RESOLUTION); ii++) {
			/**
			 * �{���͐M����p�Ɖf����p�̑g�ݍ��킹�� OSD �M����p�� OSD �f����p�����܂�̂���
			 * ����A�f����p������ OSD �M����p�� OSD ��������p�̑g�ݍ��킹�����܂�̂ŁA���������蔲�����Ă���
			 */
			if ((OsdResolution[ii].global.image.width == globalImage->width) && (OsdResolution[ii].global.image.height == globalImage->height)) {
				find = &OsdResolution[ii].local;
				break;
			}
		}
	}

	if (find == NULL) {	/* �M�� OFF �w�� (�e�[�u���������s���܂�) */
		find = &NoSignal;
	}

	*resolution = *find;
}

/**
   @brief   OSD �M����p�E�f����p���ω����Ă��邩�`�F�b�N
   @param[in] output  : �o�͐�
   @param[in] *signal : OSD �M����p
   @param[in] *image  : OSD �f����p
   @retval TRUE �X�V���� / FALSE �X�V�Ȃ�
*/
BOOL line_IsChangeResolution(GUI_OUTPUT_DEV output, const GUI_VIDEO_FORMAT *signal, const GUI_VIDEO_FORMAT *image)
{
	BOOL isChange = FALSE;
	LINE_SCREEN *screen = line_GetScreen(output);

	if (screen == NULL) {
		return FALSE;
	}

	if ((screen->signal.width != signal->width) || (screen->signal.height != signal->height) /* pgr0541 */
		|| (screen->image.width != image->width) || (screen->image.height != image->height)) { /* pgr0541 */
		isChange = TRUE;
	}
	return isChange;
}

/**
   @brief   �`��G���A�ƃ������G���A�Ƃ̃I�t�Z�b�g��ݒ�
   @param[in] memory : OSD ��������p
   @param[in] signal : OSD �M����p
   @param[in] image  : OSD �f����p
   @retval LINE_ERR (@ref line_ctrl)
*/
LINE_ERR line_SetDrawOffset(GUI_OUTPUT_DEV output)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	if (screen == NULL) {
		return LINE_ERR_BADARG;
	}
	/**
	 * �������ɑ΂��A�M���͍���ɋl�߂Ĕz�u (= �I�t�Z�b�g�Ȃ�)
	 * �M���ɑ΂��A�f���͐^�񒆂ɔz�u
	 * ��Draw �u���b�N�̍��W�n�� OSD �M����p����Ƃ���
	 */
	screen->memory.drawOffset.x = (screen->signal.width -  screen->image.width) / 2; /* pgr0351 */
	screen->memory.drawOffset.y = (screen->signal.height - screen->image.height) / 2; /* pgr0351 */
	return LINE_OK;
}

/**
   @brief   ��g�̃p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] faceFrameId : ��gID
   @param[in] layoutInfo  : �z�u���
   @param[in] isDisp      : �\���� ON/OFF �w��
   @param[in] color       : �F
   @retval �Ȃ�
*/
BOOL line_SetParamFaceFrame(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, UW faceFrameId, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color)
{
	GUI_COLOR_ID main_color = color;
	GUI_COLOR_ID edge_color = GUI_COLOR_ID_GRAY;
	LINE_SCREEN *screen = line_GetScreen(output);

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}

	if (faceFrameId >= GUI_FACE_FRAME_NUM) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
	screen->faceFrame[faceFrameId].isDisp = isDisp;
	screen->faceFrame[faceFrameId].layoutInfo = *layoutInfo; /* pgr0541 */
	screen->faceFrame[faceFrameId].color = color;

	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_BOX;

	/* �p�����[�^���� */	/* K519 */
	if(GUI_OUTPUT_LCD == output){
		object->param.box.start.x = CALC_SCREEN_LCD_X_RATIO(layoutInfo->hpos, screen->image.width);	/* pgr0351 */
		object->param.box.start.y = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->vpos, screen->image.height); /* pgr0351 */
		object->param.box.area.w = CALC_SCREEN_LCD_X_RATIO(layoutInfo->width, screen->image.width);	/* pgr0351 */
		object->param.box.area.h = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->height, screen->image.height); /* pgr0351 */
		object->param.box.bold = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->vsize, screen->image.height); /* �ω��̏��Ȃ����������g�� */ /* pgr0351 */
		object->param.box.edge.width = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->waku_size, screen->image.height); /* pgr0351 */
	}else{
		object->param.box.start.x = CALC_SCREEN_LOUT_X_RATIO(layoutInfo->hpos, screen->image.width);	/* pgr0351 */
		object->param.box.start.y = CALC_SCREEN_LOUT_Y_RATIO(layoutInfo->vpos, screen->image.height); /* pgr0351 */
		object->param.box.area.w = CALC_SCREEN_LOUT_X_RATIO(layoutInfo->width, screen->image.width);	/* pgr0351 */
		object->param.box.area.h = CALC_SCREEN_LOUT_Y_RATIO(layoutInfo->height, screen->image.height); /* pgr0351 */
		object->param.box.bold = CALC_SCREEN_LOUT_Y_RATIO(layoutInfo->vsize, screen->image.height); /* �ω��̏��Ȃ����������g�� */ /* pgr0351 */
		object->param.box.edge.width = CALC_SCREEN_LOUT_Y_RATIO(layoutInfo->waku_size, screen->image.height); /* pgr0351 */
	}
	object->param.box.color = main_color;
	object->param.box.edge.color = edge_color;
	return TRUE;
}

/**
   @brief   �ǂ������g�̃p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] layoutInfo  : �z�u���
   @param[in] isDisp      : �\���� ON/OFF �w��
   @param[in] color       : �F
   @retval �Ȃ�
*/
BOOL line_SetParamFollowFrame(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color)
{
	GUI_COLOR_ID main_color = color;
	GUI_COLOR_ID edge_color = GUI_COLOR_ID_GRAY;
	LINE_SCREEN *screen = line_GetScreen(output);

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
	screen->followFrame.layoutInfo = *layoutInfo; /* pgr0541 */
	screen->followFrame.isDisp = isDisp;
	screen->followFrame.color = color;

	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_BRACKET;

	/* �p�����[�^���� */
	line_CreateBracketParam(&(object->param.bracket), screen, layoutInfo, main_color, edge_color);
	return TRUE;
}

/**
   @brief   �G���A�g�̃p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] layoutInfo  : �z�u���
   @param[in] isDisp      : �\���� ON/OFF �w��
   @param[in] color       : �F
   @retval �Ȃ�
*/
BOOL line_SetParamAreaFrame(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_FACE_FRAME_INFO *layoutInfo, BOOL isDisp, GUI_COLOR_ID color)
{
	GUI_COLOR_ID main_color = color;
	GUI_COLOR_ID edge_color = GUI_COLOR_ID_MARKER_BLACK;
	LINE_SCREEN *screen = line_GetScreen(output);

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}
    
	/* �p�����[�^�ێ� */
	screen->areaFrame.layoutInfo = *layoutInfo;	/* pgr0541 */
	screen->areaFrame.isDisp = isDisp;
	screen->areaFrame.color = color;

	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_SIGHT;

	/* �p�����[�^���� */
	line_CreateBracketParam(&(object->param.sight.bracket), screen, layoutInfo, main_color, edge_color);
	line_CreateCrossParam(&(object->param.sight.cross), screen, layoutInfo, main_color, edge_color);
	return TRUE;
}

/**
   @brief   �K�C�h���C���̃p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] guideType   : �K�C�h���C�����
   @retval �Ȃ�
*/
BOOL line_SetParamGuideLine(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_GUIDELINE_TYPE guideType)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	LINE_DRAW_GRID *grid;
	UB ii;
	const LINE_GUIDELINE_POS *table = NULL;

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
	screen->guideLine.type = guideType;

	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_GRID;

	grid = &(object->param.grid); /* �����̂Œu������ */

	for (ii = 0; ii < sizeof(GuideLinePos)/sizeof(LINE_GUIDELINE_POS); ii++) {
		if ((GuideLinePos[ii].image.width == screen->image.width) && (GuideLinePos[ii].image.height == screen->image.height)) {
			table = &GuideLinePos[ii];
			break;
		}
	}

	if (table == NULL) {			/* �e�[�u���������s */
		return FALSE;
	}

	grid->start.x = 0;
	grid->start.y = 0;
	grid->area.w = screen->image.width;
	grid->area.h = screen->image.height;
	grid->color = GUI_COLOR_ID_WHITE;

	switch (guideType) {
	case GUI_GUIDELINE_TYPE_HORIZONTAL:
		grid->horizon.bold = table->horizontal.bold;
		grid->horizon.start = table->horizontal.start;
		grid->horizon.interval = table->horizontal.interval;
		grid->vertical.bold = 0; /* �������Ȃ� */
		break;
	case GUI_GUIDELINE_TYPE_LATTICE1:
		grid->vertical.bold = table->lattice1.bold;
		grid->vertical.start = table->lattice1.x.start;
		grid->vertical.interval = table->lattice1.x.interval;
		grid->horizon.bold = table->lattice1.bold;
		grid->horizon.start = table->lattice1.y.start;
		grid->horizon.interval = table->lattice1.y.interval;
		break;
	case GUI_GUIDELINE_TYPE_LATTICE2:
		grid->vertical.bold = table->lattice2.bold;
		grid->vertical.start = table->lattice2.x.start;
		grid->vertical.interval = table->lattice2.x.interval;
		grid->horizon.bold = table->lattice2.bold;
		grid->horizon.start = table->lattice2.y.start;
		grid->horizon.interval = table->lattice2.y.interval;
		break;
	case GUI_GUIDELINE_TYPE_NONE:
	default:
		/* �����Ƃ��ɂ̓p�����[�^�K�v�Ȃ� */
		grid->horizon.bold = 0;
		grid->vertical.bold = 0;
		break;
	}
	return TRUE;
}

/**
   @brief   FA �g�̕`��p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] isDisp      : �\�� ON/OFF
   @retval �Ȃ�
*/
BOOL line_SetParamFocusAssist(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, BOOL isDisp)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	LINE_DRAW_LINES *lines;

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
	if (isDisp == TRUE) {
		screen->guideLine.type = GUI_GUIDELINE_TYPE_FA;
	} else {
		screen->guideLine.type = GUI_GUIDELINE_TYPE_NONE;
	}

	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_LINES;

	lines = &(object->param.lines); /* �����̂Œu������ */
	lines->num = 4;

	/* ��� */
	lines->line[0].start.x = 0;
	lines->line[0].start.y = 0;
	lines->line[0].end.x = screen->image.width - 1; /* ���W�Ȃ̂ŕ� -1 */ /* pgr0351 */
	lines->line[0].end.y = screen->image.height - 1; /* ���W�Ȃ̂ō��� -1 */ /* pgr0351 */
	lines->line[0].color = screen->guideLine.faColor;
	lines->line[0].bold = 16;	/* �Œ� */

	/* ���� */
	lines->line[1] = lines->line[0]; /* �������̂������̂ł܂��R�s�[ */
	lines->line[1].start.y += screen->image.height - lines->line[1].bold; /* pgr0351 */
	lines->line[1].end.y = lines->line[1].start.y;

	/* ���� */
	lines->line[2] = lines->line[0];
	lines->line[2].end.x = 0;
	lines->line[2].end.y = screen->image.height - 1; /* pgr0351 */

	/* �E�� */
	lines->line[3] = lines->line[2];
	lines->line[3].start.x += screen->image.width - lines->line[3].bold; /* pgr0351 */
	lines->line[3].end.x = lines->line[3].start.x;
	return TRUE;
}

/**
   @brief   �Z�[�t�e�B�]�[���g�̕`��p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] type        : �}�[�J�[��� (TYPE_OFF �ŕ\�� OFF)
   @param[in] size        : �}�[�J�[�T�C�Y (%)
   @retval �Ȃ�
*/
BOOL line_SetParamSafetyzone(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_SAFETY_ZONE_TYPE type, float size, GUI_COLOR_ID color)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	LINE_DRAW_BOX *box;
	LINE_DRAW_BRACKET *bracket;
	UW mw, mh, bw, bh;

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
	screen->safetyZone.type = type;
	screen->safetyZone.size = size;
	screen->safetyZone.color = color;

	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);

	/* �}�[�J�[�T�C�Y�v�Z */
	mw = (UW)LINE_ROUND(screen->image.width * size / 100 / 2) * 2; /* pgr0247 */
	mh = (UW)LINE_ROUND(screen->image.height * size / 100 / 2) * 2; /* pgr0247 */
    if(size == 100){
        // Size 100%�̎���Bold�l�ɂ��Area�̕��A�������T�C�Y�I�[�o�[����̂ŁABold�������Ă���
        mw -= 4;
        mh -= 4;
    }
    
	switch (type) {
	case GUI_SAFETY_ZONE_TYPE_OFF: /* �\�� OFF ���͂����̍폜�v���Ȃ̂Ńp�����[�^�͕K�v�Ȃ� */
	default:
		break;
	case GUI_SAFETY_ZONE_TYPE_BOX:
		object->drawType = LINE_DRAW_TYPE_BOX;
		box = &(object->param.box); /* �����̂Œu������ */
		box->bold = 4;//2				/* �����͌Œ� */
		box->area.w = mw + box->bold / 2 * 2; /* ���̔����� 2 �� */ /* pgr0351 */
		box->area.h = mh + box->bold / 2 * 2; /* pgr0351 */
		box->start.x = (screen->image.width - box->area.w) / 2;	/* pgr0351 */
		box->start.y = (screen->image.height - box->area.h) / 2; /* pgr0351 */
		box->color = screen->safetyZone.color;
		box->edge.width = 0;	/* ���Ȃ� */
		break;
	case GUI_SAFETY_ZONE_TYPE_CORNER:
		object->drawType = LINE_DRAW_TYPE_BRACKET;
		bracket = &(object->param.bracket); /* �����̂Œu������ */
		/* �������T�C�Y�v�Z ��bw �� bh �͉f���ł͂Ȃ��M���T�C�Y�����Ɍv�Z����d�l */
		bw = mw - (UW)LINE_ROUND(screen->signal.width * 0.2 / 2) * 2; /* pgr0247 */
		bh = mh - (UW)LINE_ROUND(screen->signal.height * 0.2 / 2) * 2; /* pgr0247 */
		bracket->bold = 4;//2				/* �����͌Œ� */
		bracket->area.w = mw + bracket->bold / 2 * 2; /* ���̔����� 2 �� */ /* pgr0351 */
		bracket->area.h = mh + bracket->bold / 2 * 2; /* pgr0351 */
		bracket->start.x = (screen->image.width - bracket->area.w) / 2;	/* pgr0351 */
		bracket->start.y = (screen->image.height - bracket->area.h) / 2; /* pgr0351 */
		bracket->hook.w = (bracket->area.w - bw) / 2; /* pgr0351 */
		bracket->hook.h = (bracket->area.h - bh) / 2; /* pgr0351 */
		bracket->color = screen->safetyZone.color;
		bracket->edge.width = 0;	/* ���Ȃ� */
		break;
	}
	return TRUE;
}

/**
   @brief   �t���[���}�[�J�[�̕`��p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] angle       : �}�[�J�[��� (TYPE_OFF �ŕ\�� OFF)
   @param[in] size        : �}�[�J�[�T�C�Y (%)
   @retval �Ȃ�
*/
BOOL line_SetParamFrameMarker(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_FRAME_MARKER_ANGLE angle, GUI_COLOR_ID color)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	const LINE_FRAME_MARKER_POS *pos;
	UB ii;
	LINE_DRAW_BOX *box;

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
	screen->frameMarker.angle = angle;
	screen->frameMarker.color = color;

	/* �e�[�u�����ʒu�E�T�C�Y���擾 */
	pos = NULL;
	for (ii = 0; ii < sizeof FrameMarkerPos / sizeof (LINE_FRAME_MARKER_POS); ii++) {
		if ((FrameMarkerPos[ii].image.width == screen->image.width) && (FrameMarkerPos[ii].image.height == screen->image.height)) {
			pos = &FrameMarkerPos[ii];
			break;
		}
	}
	if (pos == NULL) {			/* �e�[�u���������s (���M�� or �K��O�� OSD ��p) */
		LineDebugPrint("table error!! not has w=%d h=%d\n", screen->image.width, screen->image.height);
		return FALSE;
	}

	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_BOX;
	box = &(object->param.box);	/* �����̂Œu������ */

	box->start = pos->angle[angle].start;
	box->area = pos->angle[angle].area;
	box->bold = pos->bold;
	box->color = color;
	box->edge.width = 0;
	box->edge.color = GUI_COLOR_ID_DELETE;
	LineDebugPrint("Frame x=%d y=%d w=%d h =%d \n", box->start.x, box->start.y, box->area.w, box->area.h);
	return TRUE;
}

/**
   @brief   �Z���^�[�}�[�J�[�̕`��p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] type        : �}�[�J�[��� (TYPE_OFF �ŕ\�� OFF)
   @param[in] color       : �}�[�J�[�F
   @retval �Ȃ�
*/
BOOL line_SetParamCenterMarker(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_CENTER_MARKER_TYPE type, GUI_COLOR_ID color)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	const LINE_CENTER_MARKER_POS *pos;
	UB ii;
	LINE_DRAW_CROSS *cross;

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
	screen->centerMarker.type = type;
	screen->centerMarker.color = color;

	/* �e�[�u�����ʒu�����擾 */
	pos = NULL;
	for (ii = 0; ii < sizeof CenterMarkerPos / sizeof (LINE_CENTER_MARKER_POS); ii++) {
		if ((CenterMarkerPos[ii].image.width == screen->image.width) && (CenterMarkerPos[ii].image.height == screen->image.height)) {
			pos = &CenterMarkerPos[ii];
			break;
		}
	}
	if (pos == NULL) {			/* �e�[�u���������s (���M�� or �K��O�� OSD ��p) */
		LineDebugPrint("table error!! not has w=%d h=%d\n", screen->image.width, screen->image.height);
		return FALSE;
	}

	/* --- �`��p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_CROSS;
	cross = &(object->param.cross); /* ���O�̒u������ (�����̂�) */
	cross->horizon.start.x = pos->param[type].horizon.start.x;
	cross->horizon.start.y = pos->param[type].horizon.start.y;
	cross->horizon.area.w = pos->param[type].horizon.length;
	cross->horizon.area.h = pos->bold;
	cross->horizon.blank = pos->param[type].horizon.blank;
	cross->vertical.start.x = pos->param[type].vertical.start.x;
	cross->vertical.start.y = pos->param[type].vertical.start.y;
	cross->vertical.area.w = pos->bold;
	cross->vertical.area.h = pos->param[type].vertical.length;
	cross->vertical.blank = pos->param[type].vertical.blank;
	cross->color = color;
	cross->edge.width = 0;
	cross->edge.color = GUI_COLOR_ID_DELETE;
	return TRUE;
}

/**
   @brief   �X�|�b�g���[�^�[�}�[�J�[�̕`��p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
   @param[out] *object    : �p�����[�^��������I�u�W�F�N�g
   @param[in] output      : �\����̑I��
   @param[in] type        : �}�[�J�[��� (TYPE_OFF �ŕ\�� OFF)
   @param[in] color       : �}�[�J�[�F
   @retval �Ȃ�
*/
BOOL line_SetParamSpotMeterMarker(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_SPOT_METER_MARKER_TYPE type, GUI_COLOR_ID color)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	const LINE_SPOT_METER_MARKER_POS *pos;
	UB ii;
	LINE_DRAW_BOX *box;

	if ((object == NULL) || (screen == NULL)) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
	screen->spotMeterMarker.type = type;
	screen->spotMeterMarker.color = color;

	/* �e�[�u�����ʒu�E�T�C�Y���擾 */
	pos = NULL;
	for (ii = 0; ii < sizeof SpotMeterPos / sizeof (LINE_SPOT_METER_MARKER_POS); ii++) {
		if ((SpotMeterPos[ii].image.width == screen->image.width) && (SpotMeterPos[ii].image.height == screen->image.height)) {
			pos = &SpotMeterPos[ii];
			break;
		}
	}
	if (pos == NULL) {			/* �e�[�u���������s (���M�� or �K��O�� OSD ��p) */
		LineDebugPrint("table error!! not has w=%d h=%d\n", screen->image.width, screen->image.height);
		return FALSE;
	}

	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_BOX;
	box = &(object->param.box);	/* �����̂Œu������ */

	box->start = pos->param[type].start;
	box->area = pos->param[type].area;
	box->bold = pos->bold;
	box->color = color;
	box->edge.width = 0;
	box->edge.color = GUI_COLOR_ID_DELETE;
	return TRUE;
}

/**
   @brief   AfRange�}�[�J�[�̕`��p�����[�^�������ĕ`��̂��߂̃p�����[�^�ێ�
*/
BOOL line_SetParamAfRangeMarker(LINE_DRAW_OBJECT *object, GUI_OUTPUT_DEV output, GUI_AF_RANGE_INFO* layoutInfo, BOOL isDisp, GUI_COLOR_ID color)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	//const LINE_SPOT_METER_MARKER_POS *pos;
	UB ii;
	LINE_DRAW_BOX *box;

	if ((object == NULL) || (screen == NULL) || (layoutInfo == NULL)) {
		return FALSE;
	}

	/* �p�����[�^�ێ� */
    
    screen->afRange.isDisp = isDisp;
    screen->afRange.color = color;
    screen->afRange.layoutInfo.bold = 3;
    screen->afRange.layoutInfo.x = layoutInfo->x;
    screen->afRange.layoutInfo.y = layoutInfo->y;
    screen->afRange.layoutInfo.w = layoutInfo->w;
    screen->afRange.layoutInfo.h = layoutInfo->h;
	
	/* --- �p�����[�^�ݒ� �������� --- */
	object->memory = &(screen->memory);
	object->drawType = LINE_DRAW_TYPE_BOX;
	box = &(object->param.box);	/* �����̂Œu������ */

    // APL����ʒm���ꂽ����CAM�T�C�Y(x,y) = (1920,1080) �� OSD �f����p�Ȃ̂ŁA�L����p�l�ɕ␳
    // ��CAM�T�C�Y��AplCam�����̃f�[�^��`
    box->start.x = screen->afRange.layoutInfo.x * 1024/1920;	/* pgr0351 */
    box->start.y = screen->afRange.layoutInfo.y * 576/1080;	/* pgr0351 */
    box->area.w = screen->afRange.layoutInfo.w * 1024/1920;	/* pgr0351 */
	box->area.h = screen->afRange.layoutInfo.h * 576/1080; // �Œ�l	/* pgr0351 */
    box->bold = screen->afRange.layoutInfo.bold;
	box->color = screen->afRange.color;
	box->edge.width = 0;
	box->edge.color = GUI_COLOR_ID_DELETE;
	return TRUE;
}

/**
   @brief   �ꊇ�ʂ̃p�����[�^�쐬
   @param[out] *bracket   : ��������p�����[�^
   @param[in] screen      : �X�N���[�����
   @param[in] *layoutInfo : �z�u���
   @param[in] mainColor   : �F
   @param[in] edgeColor   : ���F
   @retval �Ȃ�
*/
void line_CreateBracketParam(LINE_DRAW_BRACKET *bracket, LINE_SCREEN *screen, GUI_FACE_FRAME_INFO *layoutInfo, GUI_COLOR_ID mainColor, GUI_COLOR_ID edgeColor)
{
	if ((bracket == NULL) || (screen == NULL) || (layoutInfo == NULL)) {
		return;
	}
    /*
    #define BASE_SCREEN_LCD_WIDTH	424
    #define BASE_SCREEN_LCD_HEIGHT	240	// �㉺���ѕ������������l
    #define BASE_SCREEN_LOUT_WIDTH	424	
    #define BASE_SCREEN_LOUT_HEIGHT	240
    #define LINE_ROUND(x)		((x) + 0.5f)
    #define CALC_SCREEN_LCD_X_RATIO(base, width)	(((UW)(base) * (width) * 1000) / (BASE_SCREEN_LCD_WIDTH * 1000))
    #define CALC_SCREEN_LCD_Y_RATIO(base, height)	(((UW)(base) * (height) * 1000) / (BASE_SCREEN_LCD_HEIGHT * 1000))
    #define CALC_SCREEN_LOUT_X_RATIO(base, width)	(((UW)(base) * (width) * 1000) / (BASE_SCREEN_LOUT_WIDTH * 1000))
    #define CALC_SCREEN_LOUT_Y_RATIO(base, height)	(((UW)(base) * (height) * 1000) / (BASE_SCREEN_LOUT_HEIGHT * 1000))
    */

    bracket->start.x = CALC_SCREEN_LCD_X_RATIO(layoutInfo->hpos, 1024); /* pgr0351 */	/* K519 */
	bracket->start.y = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->vpos,576);	/* pgr0351 */	/* K519 */
	bracket->area.w = CALC_SCREEN_LCD_X_RATIO(layoutInfo->width, 1024); /* pgr0351 */	/* K519 */
	bracket->area.h = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->height, 576); /* pgr0351 */	/* K519 */
	bracket->hook.w = CALC_SCREEN_LCD_X_RATIO(layoutInfo->kagi_hsize, 1024);	/* pgr0351 */	/* K519 */
	bracket->hook.h = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->kagi_vsize,576); /* pgr0351 */	/* K519 */
	bracket->bold = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->vsize, 576); /* �ω������Ȃ������������g�� */ /* pgr0351 */	/* K519 */
	bracket->color = mainColor;
	bracket->edge.width = 1;//CALC_SCREEN_LCD_Y_RATIO(layoutInfo->waku_size, screen->image.width); /* pgr0351 */	/* K519 */
	bracket->edge.color = edgeColor;
}
/**
   @brief   �\���˂̃p�����[�^�쐬
   @param[out] *bracket   : ��������p�����[�^
   @param[in] screen      : �X�N���[�����
   @param[in] *layoutInfo : �z�u���
   @param[in] mainColor   : �F
   @param[in] edgeColor   : ���F
   @retval �Ȃ�
*/
void line_CreateCrossParam(LINE_DRAW_CROSS *cross, LINE_SCREEN *screen, GUI_FACE_FRAME_INFO *layoutInfo, GUI_COLOR_ID mainColor, GUI_COLOR_ID edgeColor)
{
	if ((cross == NULL) || (screen == NULL) || (layoutInfo == NULL)) {
		return;
	}

	cross->horizon.start.x = CALC_SCREEN_LCD_X_RATIO(layoutInfo->hpos - layoutInfo->kagi_hsize, 1024); /* pgr0351 */	/* K519 */
	cross->horizon.start.y = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->vpos + layoutInfo->height/2 - layoutInfo->vsize/2, 576); /* pgr0351 */	/* K519 */
	cross->vertical.start.x = CALC_SCREEN_LCD_X_RATIO(layoutInfo->hpos + layoutInfo->width/2 - layoutInfo->hsize/2, 1024); /* pgr0351 */	/* K519 */
	cross->vertical.start.y = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->vpos - layoutInfo->kagi_vsize, 576);	/* pgr0351 */	/* K519 */
	cross->horizon.area.w = CALC_SCREEN_LCD_X_RATIO(layoutInfo->width + layoutInfo->kagi_hsize*2,1024);	/* pgr0351 */	/* K519 */
	cross->horizon.area.h = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->vsize, 576); /* pgr0351 */	/* K519 */
	cross->vertical.area.w = CALC_SCREEN_LCD_X_RATIO(layoutInfo->hsize, 1024); /* pgr0351 */	/* K519 */
	cross->vertical.area.h = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->height + layoutInfo->kagi_vsize*2, 576); /* pgr0351 */	/* K519 */
	cross->horizon.blank = CALC_SCREEN_LCD_X_RATIO(layoutInfo->width - layoutInfo->kagi_hsize*2, 1024); /* pgr0351 */	/* K519 */
	cross->vertical.blank = CALC_SCREEN_LCD_Y_RATIO(layoutInfo->height - layoutInfo->kagi_vsize*2, 576); /* pgr0351 */	/* K519 */
	cross->color = mainColor;
    cross->edge.width = 1;//CALC_SCREEN_LCD_Y_RATIO(layoutInfo->waku_size, 576); /* pgr0351 */	/* K519 */
	cross->edge.color = edgeColor;
}

/**
   @brief   �ĕ`�揈��
   @param[in] output  : �o�͐�
   @param[in] *format : �r�f�I�t�H�[�}�b�g
   @retval �Ȃ�
*/
void line_Redraw(GUI_OUTPUT_DEV output)
{
	LINE_SCREEN *screen = line_GetScreen(output);
	UW faceFrameId;

	if (screen == NULL) {
		return;
	}

	/* ��g */
	for (faceFrameId = 0; faceFrameId < GUI_FACE_FRAME_NUM; faceFrameId++) {
		if (screen->faceFrame[faceFrameId].isDisp == TRUE) {
			Line_DrawFaceFrame(output, faceFrameId, &(screen->faceFrame[faceFrameId].layoutInfo), TRUE, screen->faceFrame[faceFrameId].color);
		}
	}

	/* �ǂ������g */
	if (screen->followFrame.isDisp == TRUE) {
		Line_DrawFollowFrame(output, &(screen->followFrame.layoutInfo), TRUE, screen->followFrame.color);
	}

	/* �G���A�g */
	if (screen->areaFrame.isDisp == TRUE) {
		Line_DrawAreaFrame(output, &(screen->areaFrame.layoutInfo), TRUE, screen->areaFrame.color);
	}

    	/* �G���A�g */
	if (screen->afRange.isDisp == TRUE) {
	    Line_DrawAfRange(output, &(screen->afRange.layoutInfo), TRUE);
	}

	/* �K�C�h���C��/�t�H�[�J�X�A�V�X�g */
	switch (screen->guideLine.type) {
	case GUI_GUIDELINE_TYPE_FA:
		Line_DrawFocusAssist(output, TRUE);
		break;
	case GUI_GUIDELINE_TYPE_HORIZONTAL:
	case GUI_GUIDELINE_TYPE_LATTICE1:
	case GUI_GUIDELINE_TYPE_LATTICE2:
		Line_DrawGuideLine(output, screen->guideLine.type);
		break;
	case GUI_GUIDELINE_TYPE_NONE:
	default:
		break;
	}

	/* �Z�[�t�e�B�]�[���ĕ`�� */
	if (screen->safetyZone.type != GUI_SAFETY_ZONE_TYPE_OFF) {
		Line_DrawSafetyzone(output, screen->safetyZone.type, screen->safetyZone.size, screen->safetyZone.color);
	}

	/* �t���[���}�[�J�[�ĕ`�� */
	if (screen->frameMarker.angle != GUI_FRAME_MARKER_OFF) {
		Line_DrawFrameMarker(output, screen->frameMarker.angle, screen->frameMarker.color);
	}

	/* �Z���^�[�}�[�J�[ */
	if (screen->centerMarker.type != GUI_CENTER_MARKER_OFF) {
		Line_DrawCenterMarker(output, screen->centerMarker.type, screen->centerMarker.color);
	}

	/* �X�|�b�g���[�^�[�}�[�J�[ */
	if (screen->spotMeterMarker.type != GUI_SPOT_METER_MARKER_OFF) {
		Line_DrawSpotMeterMarker(output, screen->spotMeterMarker.type, screen->spotMeterMarker.color);
	}
}
