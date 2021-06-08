/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#ifndef __GDI_H__
#define __GDI_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef WIN32_GUI_SIM
#include "win_itron.h"
#include "egl.h"
#include "openvg.h"
    
#else
    
#define PANA_ORG_FUNC
#define _DMPNATIVE_
#include "EGL/egl.h"
#include "DMP/eglNative.h"
#include "DMP/eglNativePhlox.h"
#include "DMP/eglDMP.h"
#include "DMP/vgDMPX.h"
#endif
    
#include "fontapi.h"
#include "gdi_image.h"
#include "gdi_string.h"
/*****************************************************************************
 * �^��`
 *****************************************************************************/
//typedef unsigned long GDI_SCREEN_ID;
typedef unsigned long GDI_HANDLER;
#define GDI_INVALID_ID	(0)

typedef enum {
	GDI_COLOR_FORMAT_RGBA4444,
	GDI_COLOR_FORMAT_RGBA8888,
	GDI_COLOR_FORMAT_INDEX,
	GDI_COLOR_FORMAT_YUV422SP,
	GDI_COLOR_FORMAT_YUV420SP,
	GDI_COLOR_FORMAT_DEFAULT,
	GDI_COLOR_FORMAT_NONE
} GDI_COLOR_FORMAT;

typedef enum {
	GDI_NO_ERROR,
	GDI_ILLEGAL_ARGUMENT_ERROR,
	GDI_OUT_OF_MEMORY_ERROR,
	GDI_HW_BUSY_ERROR,
	GDI_CONTEXT_ERROR,
	GDI_EGL_ERROR
	
} GDI_ERRCODE;

typedef enum
{
	GDI_BLEND_MODE_SRC,
	GDI_BLEND_MODE_SRC_OVER
	
} GDI_BLEND_MODE;

typedef enum
{
	GFX_PLANE_LCD,
	GFX_PLANE_LOUT,
	GFX_PLANE_SDI,
	GFX_PLANE_MAX,
	
} GFX_PLANE_ID;

typedef enum
{
	OSD_PLANE_LCD1,
	OSD_PLANE_LCD2,
	OSD_PLANE_LOUT1,
	OSD_PLANE_LOUT2,
	OSD_PLANE_MAX,
	
} OSD_PLANE_ID;
	

typedef enum {
	GDI_DIR_READ,
	GDI_DIR_DRAW
	
} GDI_DIR;

typedef enum _GDI_DRAW_TYPES {
	GDI_DRAW_TYPE_FILL,
	GDI_DRAW_TYPE_SVG,
	GDI_DRAW_TYPE_BITMAP,
	GDI_DRAW_TYPE_YUV,
	GDI_DRAW_TYPE_FONT,
	GDI_DRAW_TYPE_LINE,
	GDI_DRAW_TYPE_RECT,
	GDI_DRAW_TYPE_ROUNDRECT,
	GDI_DRAW_TYPE_ELLIPSE,
	GDI_DRAW_TYPE_DRAWABLE,

	GDI_DRAW_TYPE_NONE,
	GDI_DRAW_MAX = GDI_DRAW_TYPE_NONE
	
} GDI_DRAW_TYPES;
	
typedef enum _GDI_CACHE_TYPES {
	GDI_CACHE_TYPE_SVG,
	GDI_CACHE_TYPE_BITMAP,
	GDI_CACHE_TYPE_FONT,
	GDI_CACHE_TYPE_BITMAP_FONT,
	GDI_CACHE_TYPE_MAX,
	
} GDI_CACHE_TYPES;
	
/*�摜�^�C�v*/
typedef enum {
	GDI_IMAGE_TYPE_NONE,
	GDI_IMAGE_TYPE_1BPP,		/*1bpp�C���[�W*/
	GDI_IMAGE_TYPE_8BPP,		/*8bpp�C���[�W*/
	GDI_IMAGE_TYPE_16BPP,		/*16bpp�C���[�W*/
	GDI_IMAGE_TYPE_32BPP,		/*32bpp�C���[�W*/
	GDI_IMAGE_TYPE_SVG,			/*SVG�J���[�C���[�W*/
	GDI_IMAGE_TYPE_YCbCr,		/*YCbCr�`���摜*/
	GDI_IMAGE_TYPE_YUV420S,		/*YUV420 SEMIPLANAR�`���摜*/
	GDI_IMAGE_TYPE_MAX,
	
} GDI_IMAGE_TYPE;
	
/*�}�`�^�C�v*/
typedef enum {
	GDI_SHAPE_TYPE_PATH = 1,	/*SVG Path*/
	GDI_SHAPE_TYPE_LINE,		/*����*/
	GDI_SHAPE_TYPE_RECT,		/*��`*/
	GDI_SHAPE_TYPE_RRECT	,	/*�p�ۋ�`*/
	GDI_SHAPE_TYPE_ELLIPSE,		/*�ȉ~*/
	GDI_SHAPE_TYPE_POLYLINE,	/*�ܐ�*/
	GDI_SHAPE_TYPE_POLYGON,		/*�|���S��*/
	GDI_SHAPE_TYPE_MAX,
	
} GDI_SHAPE_TYPE;


typedef struct _GDI_REGION
{
	short				x;
	short				y;
	short				width;
	short				height;
	
} GDI_REGION;
	
typedef struct _GDI_IMAGE {
	GDI_IMAGE_TYPE		type;			/* �摜�`��*/
	short				width;			/* �摜�̕�*/
	short				height;			/* �摜�̍���*/
	const unsigned char	*data;			/* �摜�f�[�^*/
} GDI_IMAGE;


/*��������*/
typedef struct _GDI_FONT_ATTRIB {
	short				width;			/* �����̕� */
	short				height;			/* �����̍��� */
	short				weight;			/* �����̑��� */
	unsigned short		italic;			/* �����̎Α� */
	unsigned short		outline;		/* �����̉���� */
	unsigned short		exstyle;		/* �g���X�^�C�� */
	unsigned short		direction;		/* �����̓ǂݕ��� */
	char				interval;		/* �����Ԋu */
} GDI_FONT_ATTRIB;

/*�����n���h��*/
typedef struct _GDI_FONT_HANDLE {
	short			id;				/*�t�H���g�n���h����ID*/
	GDI_FONT_ATTRIB	attribute;		/*�t�H���g����*/
} GDI_FONT_HANDLE;
	
/*�C���[�W�w�b�h���*/
typedef struct _GDI_BITMAP {
	GDI_IMAGE_TYPE		type;			/* �摜�`��*/
	short				width;			/* �摜�̕�*/
	short				height;			/* �摜�̍���*/
	
	const unsigned char	*data;			/* �摜�f�[�^*/
} GDI_BITMAP;

/*�j�����\����*/
typedef struct _GDI_DASH {
	short				count;
	const float			*dash_pattern;
} GDI_DASH;

/*�O���f�[�V�������\����*/
typedef struct _GDI_GRADIENT {
	short				paint_type;
	float				x1;
	float				y1;
	float				x2;
	float				y2;
	float				r;
	long				num_stops;
	const float			*stops;					/*[5*lNumStops]*/
} GDI_GRADIENT;
	
/*�J���[�g����*/
typedef struct _GDI_COLOR {
	VGPaintType			type;
	unsigned long		color;
	const GDI_GRADIENT	*gradient;
} GDI_COLOR;

/*SVG �}�`�\����*/
typedef struct _GDI_PARTS {
	GDI_SHAPE_TYPE		type;				/*�}�`�^�C�v*/
	const void			*data;				/*�}�`�f�[�^GDI_SHAPE_LINE,GDI_SHAPE_RECT�Ȃ�*/
	
	VGPaintMode			paint_mode;			/*�y�C���g���[�h*/
	VGFillRule 			fill_rule;			/*�h��Ԃ��K��*/
	VGCapStyle			cap_style;			/*�L���b�v�X�^�C��*/
	VGJoinStyle			join_style;			/*�ڍ��X�^�C��*/
	float				miter_limit;
	float				stroke_width;		/*����*/
	const GDI_DASH		*dash_info;			/*�_�b�V��ID*/

	const GDI_COLOR		*stroke_color;
	const GDI_COLOR		*fill_color;
	
} GDI_PARTS;


typedef struct _GDI_IMAGE_BASE {
	GDI_IMAGE_TYPE		type;			/*�摜�`��*/
	short				width;			/*�摜�̕�*/
	short				height;			/*�摜�̍���*/
	
} GDI_IMAGE_BASE;
	
/*BMP�摜�̃w�b�h���*/
typedef struct _GDI_IMAGE_BITMAP {
	GDI_IMAGE_TYPE		type;			/*�摜�`��*/
	short				width;			/*�摜�̕�*/
	short				height;			/*�摜�̍���*/
	
	short				buf_width;
	short				buf_height;
	unsigned short		status;			/*�摜���*/
	const unsigned char	*data;			/*�摜�f�[�^*/
} GDI_IMAGE_BITMAP;

/*SVG�摜�̃w�b�h���*/
typedef struct _GDI_IMAGE_SVG {
	GDI_IMAGE_TYPE			type;			/*�摜�`��*/
	short					width;			/*�摜�̕�*/
	short					height;			/*�摜�̍���*/
	
	unsigned short			status;			/*�摜���*/
	long					shape_num;		/*�}�`���i�̐�*/
	const GDI_PARTS* const	*data;			/*�}�`�f�[�^�|�C���^�̔z��*/
} GDI_IMAGE_SVG;

/*YUV�摜�̃w�b�h���*/
typedef struct _GDI_IMAGE_YUV {
	GDI_IMAGE_TYPE			type;			/*�摜�`��*/
	short					width;			/*�摜�̕�*/
	short					height;			/*�摜�̍���*/

	short					y_plane_size;	/*Y�v���[���̃T�C�Y*/
	short					c_plane_size;	/*C�v���[���̃T�C�Y(y�v���[���̔���)*/
	short					plane_stride;	/*�v���[���̐܂�Ԃ�(64�̔{��)*/
	short					plane_height;	/*�v���[���̍���(8�̔{��)*/
	const unsigned char		*y_plane;		/*�摜�f�[�^(Y�v���[��)(128byte�A���C���̃o�b�t�@�ɂ��邱��)*/
	const unsigned char		*c_plane;		/*�摜�f�[�^(C�v���[��)(128byte�A���C���̃o�b�t�@�ɂ��邱��)*/
} GDI_IMAGE_YUV;

/*�}�`�i���j���\����*/
typedef struct _GDI_SHAPE_LINE {
	float	x0;
	float 	y0;
	float	x1;
	float	y1;
} GDI_SHAPE_LINE;

/*�}�`�i��`�j���\����*/
typedef struct _GDI_SHAPE_RECT {
	float	x;
	float	y;
	float	width;
	float	height;
	
} GDI_SHAPE_RECT;

/*�}�`�i�p�ۋ�`�j���\����*/
typedef struct _GDI_SHAPE_RRECT {
	float	x;
	float	y;
	float	width;
	float	height;
	float	arc_width;
	float	arc_height;
	
} GDI_SHAPE_RRECT;

/*�}�`�i�ȉ~�`�j���\����*/
typedef struct _GDI_SHAPE_ELLIPSE{
	float	x;
	float	y;
	float	width;
	float	height;
	
} GDI_SHAPE_ELLIPSE;

/*�}�`�i�ܐ�/�}�`�j���\����*/
typedef struct _GDI_SHAPE_POLYLINE {
	unsigned short		num_points;
	const float			*points;
	
} GDI_SHAPE_POLYLINE;
	
/*�}�`�i�|���S���j���\����*/
typedef struct _GDI_SHAPE_POLYGON {
	unsigned short		num_points;
	const float			*points;
	
	short				stroke_width;
	GDI_COLOR			stroke_color;
	GDI_COLOR			fill_color;
	
} GDI_SHAPE_POLYGON;

/*�}�`�i�p�X�j���\����*/
typedef struct _GDI_SHAPE_PATH {
	unsigned  short		num_segments;
	const VGubyte		*path_segments;
	const float			*path_data;
} GDI_SHAPE_PATH;

typedef struct _GDI_DRAW_BASE {
	GDI_BLEND_MODE		blend;
	GDI_REGION			clip_area;
	GDI_REGION			draw_area;
	//	float				alpha_factor;	//���W��
} GDI_DRAW_BASE;


typedef struct _gdi_cache_path {
	GDI_PARTS			*parts;
	VGPath				path;
	VGPaint				stroke;
	VGPaint				fill;
	unsigned short		mode;
	struct _gdi_cache_path	*next;
	
} GDI_CACHE_PATH;


typedef struct _gdi_cache_base {
	GDI_CACHE_TYPES		type;
	
} GDI_CACHE_BASE;

typedef struct _gdi_cache_svg {
	GDI_CACHE_TYPES		type;
	
	GDI_CACHE_PATH		*path;
} GDI_CACHE_SVG;


typedef struct _gdi_cache_bitmap {
	GDI_CACHE_TYPES		type;
	
	VGImage				vg_image;
	unsigned char		*raw_data;
	
} GDI_CACHE_BITMAP;


typedef struct _gdi_cache_font {
	GDI_CACHE_TYPES		type;

	VGPath				path;

	//�`����
	short				width;			//�`�悷�镶����S�̂̉���
	short				height;			//�t�H���g�̏c�T�C�Y
	short				lineUnderflow;	//�`��N�_(����)�������ɕ`�悳���C���[�W�����̍���
	short				bmpheight;		//���ۂɕ`�悷�镶���C���[�W�̍����B
} GDI_CACHE_FONT;


typedef enum {
	ASPECT_RATIO_DEFAULT = 0,	//�S�p������ŉ�:�c= 8:10(���p���Ɖ�:�c= 4:10)
	ASPECT_RATIO_SAME,			//�S�p������ŉ�:�c=10:10(���p���Ɖ�:�c= 5:10)
	ASPECT_RATIO_WIDE,			//�S�p������ŉ�:�c=20:10(���p���Ɖ�:�c=10:10)
	ASPECT_RATIO_NARROW,
	ASPECT_RATIO_RECVIEW,		//���p������ŉ�:�c=12:20(RecView��ʂ̏㉺���ѐ�p)
} ASPECT_RATIO;

typedef enum {
	AUTO_ADJUST_DISABLE = 0,	//�`��G���A�ɑ΂��ẴT�C�Y����������
	AUTO_ADJUST_ENABLE,			//�`��G���A�ɑ΂��ẴT�C�Y���������L
} AUTO_ADJUST;


typedef enum {
	FONT_ATTRIBUTE_NORMAL = 0,		//�C���Ȃ�
	FONT_ATTRIBUTE_BOLD,			//����
	FONT_ATTRIBUTE_OUTLINE,			//�O�g�t
	FONT_ATTRIBUTE_MONO,			//���m�N��(�r�b�g�}�b�v�t�H���g)
} FONT_ATTRIBUTE;

typedef enum {
	HALIGN_LEFT = 0,	//����
	HALIGN_CENTER,		//��������
	HALIGN_RIGHT		//�E��
} HALIGN;

typedef enum {
	VALIGN_DEFAULT = 0,	//��≺��
	VALIGN_TOP,			//���
	VALIGN_MIDDLE,		//��������
	VALIGN_BOTTOM		//����
} VALIGN;

typedef struct _GDI_IMAGE_STYLE {
	ASPECT_RATIO	aspect_ratio;
	AUTO_ADJUST		auto_adjust;
	HALIGN			halign;
	VALIGN			valign;
} GDI_IMAGE_STYLE;

typedef struct _GDI_DRAW_SVG {
	GDI_IMAGE_SVG		*svg;
	GDI_IMAGE_STYLE		image_style;
	
	// CACHE�f�[�^
	GDI_COLOR			stroke;
	GDI_COLOR			fill;
} GDI_DRAW_SVG;

typedef struct _GDI_DRAW_BITMAP {
	GDI_IMAGE_BITMAP	*bitmap;
	GDI_IMAGE_STYLE		image_style;
} GDI_DRAW_BITMAP;

typedef struct _GDI_DRAW_YUV {
	GDI_IMAGE_YUV		*yuv;
	GDI_IMAGE_STYLE		image_style;
} GDI_DRAW_YUV;

typedef struct _GDI_DRAW_DRAWABLE {
	GDI_HANDLER			drawable;
	GDI_IMAGE_STYLE		image_style;
} GDI_DRAW_DRAWABLE;

	
GDI_IMAGE_BASE* 	GDI_GetImage(GDI_IMAGE_ID id);
GDI_IMAGE_SVG*	 	GDI_GetImageSVG(GDI_IMAGE_ID id);
GDI_IMAGE_BITMAP* 	GDI_GetImageBitmap(GDI_IMAGE_ID id);


typedef struct _GDI_FONT_STYLE {
	unsigned char		font_size;			// �t�H���g�̃T�C�Y
	enum FONT_LOCALE	locale;
	ASPECT_RATIO		aspect_ratio;		// 1�������̏c����(�S�p�����)
	AUTO_ADJUST			auto_adjust;
	FONT_ATTRIBUTE		attr;				// �����C��(0:���� / 1:���� / 2:�O�g�t)
	HALIGN				halign;
	VALIGN				valign;
	BOOL				isWriteOneChar;		// 1�����`��(������w��ł��擪1�����̂ݕ`��)
	float				font_ajust_width;	// �t�H���g������(Freetype�Ŏ��������@�\�ŃT�C�Y�ύX����ۂɎg�p)
	float				font_ajust_height;	// �t�H���g��������(Freetype�Ŏ��������@�\�ŃT�C�Y�ύX����ۂɎg�p)
} GDI_FONT_STYLE;

typedef struct _GDI_DRAW_FONT {
	//	unsigned short		len;
	unsigned short		*str;
	GDI_FONT_STYLE		font_style;

	GDI_COLOR			stroke_color;
	GDI_COLOR			fill_color;
	short				stroke_width;

} GDI_DRAW_FONT;

//�r�b�g�}�b�v�t�H���g
typedef struct _gdi_cache_bitmap_font {
	GDI_CACHE_TYPES		type;

	VGImage				vg_image;
	unsigned char		*raw_data;		//�r�b�g�}�b�v�t�H���g�̃C���[�W�f�[�^

	unsigned short		*ucs_str;
	unsigned short 		length;

	//�`����
	short		 		width;			//�r�b�g�}�b�v�摜�̉���
	short 				height;			//�r�b�g�}�b�v�摜�̏c��
	signed int		lineUnderflow;	//�`��N�_(����)�������ɕ`�悳���C���[�W�����̍���
	signed int		x_pos;			//���ʒu�����p
	signed int		y_pos;			//�c�ʒu�����p
	signed int		advanceX;		//�������`�掞�ɐi�߂�X���W�̋���
} GDI_CACHE_BITMAP_FONT;

typedef struct _GDI_DRAW_SHAPE {
	GDI_SHAPE_TYPE		shape_type;
	void				*shape;

	unsigned short		stroke_width;
	GDI_COLOR			stroke_color;
	GDI_COLOR			fill_color;
	
} GDI_DRAW_SHAPE;


typedef struct _GDI_DRAW_LINE {
	short				x0;
	short				y0;
	short				x1;
	short				y1;
	
	short				line_width;
	GDI_COLOR			line_color;

} GDI_DRAW_LINE;


typedef struct _GDI_DRAW_RECT {
	unsigned short		stroke_width;
	GDI_COLOR			stroke_color;
	GDI_COLOR			fill_color;
	
} GDI_DRAW_RECT;

typedef struct _GDI_DRAW_ROUNDRECT {
	short				arc_width;
	short				arc_height;
		
	unsigned short		stroke_width;
	GDI_COLOR			stroke_color;
	GDI_COLOR			fill_color;
	
} GDI_DRAW_ROUNDRECT;

typedef struct _GDI_DRAW_ELLIPSE {
	unsigned short		stroke_width;
	GDI_COLOR			stroke_color;
	GDI_COLOR			fill_color;
	
} GDI_DRAW_ELLIPSE;

typedef void (*GDI_DRAW_CALLBACK)(unsigned short request, int error);

typedef struct {
	short				width;
	short				height;
	GDI_COLOR_FORMAT 	format;
	unsigned char		*color_buffer0;
	unsigned char		*color_buffer1;
	GDI_DRAW_CALLBACK 	callback;
	
} GDI_DRAW_BUFFER;


/* RGBA */
#define	GDI_RGBA(r, g, b, a)	((unsigned long)((((unsigned long)(r)) << 24) + (((unsigned long)(g)) << 16) + (((unsigned long)(b)) << 8) + ((unsigned long)(a))))
/* RGB+A(A��0�`100) */
#define	GDI_RGB_A(r, g, b, a)	((unsigned long)((((unsigned long)(r)) << 24) + (((unsigned long)(g)) << 16) + (((unsigned long)(b)) << 8) + ((unsigned long)(a))))
/* ARGB */
#define	GDI_ARGB(a, r, g, b)	((unsigned long)((((unsigned long)(a)) << 24) + (((unsigned long)(r)) << 16) + (((unsigned long)(g)) << 8) + ((unsigned long)(b))))
/* RGB */
#define	GDI_RGB(r, g, b)	((unsigned long)((((unsigned long)(r)) << 16) + (((unsigned long)(g)) << 8) + ((unsigned long)(b))))

extern GDI_ERRCODE GDI_DrawSVG(GDI_DRAW_BASE* info, GDI_DRAW_SVG *info_svg, GDI_CACHE_SVG *cache);
extern GDI_ERRCODE GDI_DrawBitmap(GDI_DRAW_BASE* info, GDI_DRAW_BITMAP *bitmap, GDI_CACHE_BITMAP *cache);
extern GDI_ERRCODE GDI_DrawYUV(GDI_DRAW_BASE* info, GDI_DRAW_YUV *yuv);
extern GDI_ERRCODE GDI_DrawImage(GDI_DRAW_BASE* info, GDI_HANDLER hdr);

extern GDI_ERRCODE GDI_DrawDrawable(GDI_DRAW_BASE *info, GDI_DRAW_DRAWABLE *info_drawable);
extern GDI_ERRCODE GDI_DrawLine(GDI_DRAW_BASE *info, GDI_DRAW_LINE *shape);
extern GDI_ERRCODE GDI_DrawFill(GDI_DRAW_BASE *info, GDI_COLOR color);
extern GDI_ERRCODE GDI_DrawRectangle(GDI_DRAW_BASE *info, GDI_DRAW_RECT *shape);
extern GDI_ERRCODE GDI_DrawRoundRect(GDI_DRAW_BASE *info, GDI_DRAW_ROUNDRECT *shape);
extern GDI_ERRCODE GDI_DrawEllipse(GDI_DRAW_BASE* info, GDI_DRAW_ELLIPSE *shape);
extern GDI_ERRCODE GDI_DrawFont(GDI_DRAW_BASE* info, GDI_DRAW_FONT *info_font, GDI_CACHE_FONT *cache);
extern GDI_ERRCODE GDI_DrawBitmapFont(GDI_DRAW_BASE *info, GDI_DRAW_FONT *info_font, GDI_CACHE_BITMAP_FONT *cache);
extern GDI_ERRCODE GDI_GetDrawRect(GDI_FONT_STYLE *gdi_font_style, unsigned short *str, unsigned short *pWidth, unsigned short *pHeight);
extern void GDI_CopyRectYUV422(unsigned short src_width, unsigned short src_height,
							   void* src_Y, void* src_UV,
							   unsigned short dst_width, unsigned short dst_height,
							   void* dst_Y, void* dst_UV);

	
extern void GDI_DisplayOn(void);
extern GDI_ERRCODE GDI_Clear(short x, short y, short width, short height, unsigned long rgba);

extern GDI_ERRCODE GDI_Update(GDI_HANDLER hdr);
extern GDI_CACHE_SVG *GDI_CreateCacheSVG(GDI_IMAGE_SVG *svg);
extern GDI_CACHE_BITMAP *GDI_CreateCacheBitmap(GDI_IMAGE_BITMAP *bitmap);
extern GDI_CACHE_FONT *GDI_CreateCacheFont(GDI_FONT_STYLE *gdi_font_style, unsigned short *str);


extern GDI_ERRCODE GDI_DeleteCache(GDI_CACHE_BASE *cache);

extern GDI_ERRCODE GDI_CreateContext(GDI_COLOR_FORMAT format);
extern void GDI_DeleteContext(void);
	
extern GDI_HANDLER GDI_CreateScreen(int width, int height, GDI_COLOR_FORMAT format, GFX_PLANE_ID plane);
extern GDI_ERRCODE GDI_DeleteScreen(GDI_HANDLER hdr);
extern GDI_ERRCODE GDI_SwitchScreen(GDI_HANDLER hdr);

extern GDI_HANDLER GDI_CreateDrawable(int width, int height, GDI_COLOR_FORMAT format);
extern GDI_ERRCODE GDI_DeleteDrawable(GDI_HANDLER hdr);
extern GDI_ERRCODE GDI_SwitchDrawable(GDI_HANDLER hdr, GDI_DIR dir);

extern GDI_HANDLER GDI_GetCurrentHandler(void);

extern BOOL GDI_checkRemainMpl(unsigned int percent);
	
//�r�b�g�}�b�v�t�H���g�֘A
extern GDI_ERRCODE GDI_DrawBitmapFont_OneChar(GDI_DRAW_BASE *info, GDI_CACHE_FONT *cache, unsigned short ucs_str, GDI_DRAW_FONT *info_font, int *draw_width);
extern void gdi_cnv_font_style(FONT_STYLE *f_style, GDI_FONT_STYLE *gdi_f_style, BOOL bIsMono);
extern GDI_CACHE_BITMAP_FONT *GDI_AllocCache_BitmapFont(void);
extern void GDI_FreeCache_BitmapFont(GDI_CACHE_BITMAP_FONT *cache_font);
extern void *GDI_Alloc_Memory(int size);

void GDI_Init();
	
#ifdef WIN32_GUI_SIM
void GDI_Terminate();
void GDI_SetNativeWindow(GFX_PLANE_ID plane, NativeWindowType window);
# define __rodata_font
# define __rodata_imagedata
#else
	#include "gui_section.h"
#endif

typedef unsigned long GDI_DRAWABLE_ID;

extern void *gdi_alloc(int size);
extern void gdi_free(void *ptr);
extern void *gdi_realloc(void* ptr, int new_size, int cur_size);

extern void *gdi_bmp_alloc(int size, int align);
extern void gdi_bmp_free(void *ptr);
extern void *gdi_bmp_realloc(void* ptr, int new_size, int cur_size);

extern void *font_lib_alloc(int size);
extern void font_lib_free(void *ptr);
extern void *font_lib_realloc(void* ptr, int new_size, int cur_size);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
