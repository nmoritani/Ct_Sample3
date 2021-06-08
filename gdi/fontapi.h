#ifndef __FONTAPI_H
#define __FONTAPI_H

/* VC++��DigiType�̎󂯓���e�X�g�A�v���Ή� */
#ifdef __cplusplus
extern "C" {
#endif

typedef char	FONT_DATATABLE;

#ifdef WIN32_GUI_SIM
typedef char CHAR;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int UINT;
#else
#include <kernel.h>
#endif

/*------------------------------------------------------------------------------*/
/**
@brief        �����X�^�C���\����
*/
/*------------------------------------------------------------------------------*/
typedef struct {
    UCHAR   size_x;    /* �����T�C�Y�i���j*/
    UCHAR   size_y;    /* �����T�C�Y�i�c�j*/
    UCHAR   bold;      /* 1: ���� */
    UCHAR   italic;    /* 1: �Α� */
    UCHAR   underline; /* 1: ���� */
    UCHAR   strike;    /* 1: �ł������� */
    CHAR    spacing;   /* �����Ԋu */
    UCHAR   righttoleft;  /* �`����� 0:������E  1:�E���獶 */
    UCHAR   edge;      /* 1: �����i���̂݁j */
    UCHAR   edge_color;  /* �����F ����肠�莞�̂ݗL�� */// [R77S1]�t�`�F�Ή�
    UCHAR   mono;      /* 0: 16�K��  1:���m�N�� */
} FONT_STYLE;

typedef struct {
    UCHAR   size_x;    /* �����T�C�Y�i���j*/
    UCHAR   size_y;    /* �����T�C�Y�i�c�j*/
    UCHAR   bold;      /* 1: ���� */
    UCHAR   italic;    /* 1: �Α� */
    UCHAR   underline; /* 1: ���� */
    UCHAR   strike;    /* 1: �ł������� */
    UCHAR   spacing;   /* �����Ԋu */
    UCHAR   righttoleft;  /* �`����� 0:������E  1:�E���獶 */
    UCHAR   edge;      /* �����̉������i0:�����Ȃ��j */
    UCHAR   shadow;    /* 0: �e�Ȃ� 1: �E���ɉe */
    UCHAR   fgcolor;   /* �����F�i0-15�AOSD1�J���[�p���b�g�̏��4bit�j*/ /* �����݂�7�i���j�̂ݎg�p�\ */
} FONT_STYLE_OSD1;

typedef struct {
	/* int width; */
	/* int height; */
	int ascent;        /* �قƂ�ǂ̉p�����́A�x�[�X���C������ŏ�_�܂ł̋��� */
	int descent;       /* �قƂ�ǂ̉p�����́A�x�[�X���C������ŉ��_�܂ł̋��� */
	/* int leading; */
	/* int maxAdvance; */
	int maxAscent;     /* �S�Ă̕����̍ő�ascent */
	int maxDescent;    /* �S�Ă̕����̍ő�descent */
} FONT_METRICS;

typedef struct {
	UINT width;			//�`�悷�镶����S�̂̉���
	UINT height;		//�t�H���g�̏c�T�C�Y
	UINT lineunder;		//�`��N�_(����)�������ɕ`�悳���C���[�W�����̍���
	UINT bmpwidth;		//���ۂɕ`�悷�镶���C���[�W�̕�
	UINT bmpheight;		//���ۂɕ`�悷�镶���C���[�W�̍���
} FONT_DRAW_INFO;

/*------------------------------------------------------------------------------*/
/**
@brief        �t�H���g���P�[���̒�`
@par          �t�H���g�T�[�r�X�ɂ����镶���R�[�h�̈����A�g�p���錾��t�H���g�A
              �����ꕶ���񃌃C�A�E�^�̓�������߂郍�P�[����ʂ�\���܂��B
*/
/*------------------------------------------------------------------------------*/
enum FONT_LOCALE{
	LOCALE_EN = 0,  /* �p�ꂨ��щ��B���� */
	LOCALE_JP,      /* ���{�� */
	LOCALE_SC,      /* ������i�ȑ̎��j */
	LOCALE_TC,      /* ������i�ɑ̎��j */
	LOCALE_KR,      /* �؍��� */
	LOCALE_AR,      /* �A���r�A�� */
	LOCALE_TH,      /* �^�C�� */
	LOCALE_HI,      /* �q���f�B�[�� */
	LOCALE_EN2,     /* �C���^���̐؂�ւ��p */
	LOCALE_IC,      /* �A�C�R���i�O���A��������p�j */
	LOCALE_FX,      /* FIXED FONT */
	LOCALE_NUM,     /* �S���P�[�����i���������p�j */
	LOCALE_NONE = 0xffff  /*  */
};

/*------------------------------------------------------------------------------*/
/**
@brief        �t�H���g�T�[�r�X�̃G���[�R�[�h�̒�`
*/
/*------------------------------------------------------------------------------*/
#define LANG_NOT_SUPPORT (-6)
#define ENGINEWKMEM_ERR (-7)
#define UCS_STR_TOO_LONG (-8)
#define UCS_ERR (-9)
#define NOT_ENOUGH_BUFFER (-10)
#define FONTSTYLE_ERROR (-11)
#define LAYBUF_ERR (-13)

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_init
@brief        Font Service�̏�����
@param[in]    �Ȃ�
@retval       <0 �ُ�I��
@par          ����
@sa           [in][out] �Ȃ�
@par          �X�V����:
              2010/10/21 �V�K�쐬
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_init(
    void
);

#if KCSPEC_ARM_OPENVG
/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_font_data_table
@brief        ��CPU��fontapi�������̂��߂�fonts�����擾����
@param[in]    �Ȃ�
@retval       FONT_DATATABLE*	(font_service_init�̈����Ƃ��Ă̂ݎg�p�\)
@par          ����
@sa           [in] �Ȃ� [out] current_locale
@par          �X�V����:
              2010/10/21 �V�K�쐬
*/
/*------------------------------------------------------------------------------*/
extern FONT_DATATABLE *font_service_get_font_data_table(
	void
);
#endif

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_quit
@brief        Font Service�̏I������
@param[in]    �Ȃ�
@retval       <0 �ُ�I��
@par          ����
@sa           [in][out] �Ȃ�
@par          �X�V����:
              2011/11/1 �V�K�쐬
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_quit(
    void
);

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_lang
@brief        ���݂̃t�H���g���P�[���̎擾
@param[in]    �Ȃ�
@retval       ���P�[�����
@par          ����
@sa           [in][out] �Ȃ�
@par          �X�V����:
              2010/10/21 �V�K�쐬
*/
/*------------------------------------------------------------------------------*/
extern enum FONT_LOCALE font_service_get_lang(
    void
);

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_set_lang
@brief        �t�H���g���P�[���̐ؑ�
@param[in]    loc: ���P�[�����
@retval       <0 �ُ�I��
@par          ����
@sa           [in][out] �Ȃ�
@par          �X�V����:
              2010/10/21 �V�K�쐬
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_set_lang(
    enum FONT_LOCALE loc
);




/*------------------------------------------------------------------------------*/
/**
@fn           gdi_fontapi_get_rect
@brief        ������C���[�W�̕`��T�C�Y�̎擾
@param[in]    style   �����X�^�C��
@param[in]    ucs_str UCS-2������i0�I�[�j
@param[out]   width   ������C���[�W�̉��T�C�Y
@param[out]   height  ������C���[�W�̏c�T�C�Y
@retval       <0 �ُ�I��
@par          ����
@sa           [in][out] �Ȃ�
*/
/*------------------------------------------------------------------------------*/
extern int gdi_fontapi_get_rect(
	const FONT_STYLE *style, 
	const unsigned short *ucs_str, 
	unsigned short *width, 
	unsigned short *height,
	unsigned short *xbytes,
	unsigned char isBitmapFont
);

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_path
@brief        ������C���[�W�̎擾�iOpenVG�̃p�X�f�[�^�j
@param[in]    style   �����X�^�C��
@param[in]    ucs_str UCS-2������i0�I�[�j
@retval       VGPath�̃n���h���i�ُ�I������VG_INVALID_HANDLE�j
@par          ����
@sa           [in][out] �Ȃ�
@par          �X�V����:
              2011/9/5 �V�K�쐬
@par          ���L����: �g�p���font_service_release_path()�ɂ�������K�v�ł��B
*/
/*------------------------------------------------------------------------------*/
extern UINT gdi_fontapi_get_path(
    const FONT_STYLE *style,
    const USHORT *ucs_str,
	int len,
    FONT_DRAW_INFO *draw_info
);

extern UINT gdi_fontapi_CombineCharsToStrPath(
	const FONT_STYLE *style,
	const USHORT *ucs_str,
	FONT_DRAW_INFO *draw_info
);


/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_path
@brief        �r�b�g�}�b�v�t�H���g������C���[�W�̎擾
@par          �X�V����:
              2011/9/5 �V�K�쐬
@par          ���L����: �g�p���font_service_release_path()�ɂ�������K�v�ł��B
*/
/*------------------------------------------------------------------------------*/
extern int gdi_fontapi_create_bmp_font_Image(
	USHORT *dstImage,			// �`��p�n���h��
	int bufsize_width, 			// �o�͐�o�b�t�@�̕�
	int bufsize_height, 		// �o�͐�o�b�t�@�̍���
	const USHORT *ucs_str, 		// �`�悷�镶����
	const FONT_STYLE *style, 	// �t�H���g�X�^�C��
	unsigned int fill_color, 	// �t�H���g�J���[
	unsigned int stroke_color 	// �����J���[
);











/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_rect
@brief        ������`��ɕK�v�ȃC���[�W�o�b�t�@�̃T�C�Y�̎擾
@param[in]    style   �����X�^�C��
@param[in]    ucs_str UCS-2������i0�I�[�j
@param[out]   width   ������C���[�W�̉��T�C�Y�i�h�b�g���j
@param[out]   height  ������C���[�W�̏c�T�C�Y�i�h�b�g���j
@retval       <0 �ُ�I��
@par          ����
@sa           [in][out] �Ȃ�
@par          �X�V����:
              2010/10/21 �V�K�쐬
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_get_rect(
    const  FONT_STYLE  *style,
    const  unsigned short  *ucs_str,
    unsigned short  *width,
    unsigned short  *height
);

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_exact_rect
@brief        ������C���[�W�̕`��T�C�Y�̎擾
@param[in]    style   �����X�^�C��
@param[in]    ucs_str UCS-2������i0�I�[�j
@param[out]   width   ������C���[�W�̉��T�C�Y�i�h�b�g���j
@param[out]   height  ������C���[�W�̏c�T�C�Y�i�h�b�g���j
@retval       <0 �ُ�I��
@par          ����
@sa           [in][out] �Ȃ�
@par          �X�V����:
              2010/11/13 �V�K�쐬
*/
/*------------------------------------------------------------------------------*/
extern int  font_service_get_exact_rect(
    const  FONT_STYLE  *style,
    const  unsigned short  *ucs_str,
    unsigned short  *width,
    unsigned short  *height
);



#if KCSPEC_OPENVG
#ifdef WIN32
#include <VG/openvg.h>
#else
#ifndef VG_API_CALL
#define VG_API_CALL extern
#endif
#include <VG/openvg.h>
#endif
/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_path
@brief        ������C���[�W�̎擾�iOpenVG�̃p�X�f�[�^�j
@param[in]    style   �����X�^�C��
@param[in]    ucs_str UCS-2������i0�I�[�j
@retval       VGPath�̃n���h���i�ُ�I������VG_INVALID_HANDLE�j
@par          ����
@sa           [in][out] �Ȃ�
@par          �X�V����:
              2011/9/5 �V�K�쐬
@par          ���L����: �g�p���font_service_release_path()�ɂ�������K�v�ł��B
*/
/*------------------------------------------------------------------------------*/
extern VGPath gdi_fontapi_get_path(
    const FONT_STYLE *style,
    const USHORT *ucs_str,
    FONT_DRAW_INFO *draw_info
);

extern int gdi_fontapi_get_bmp_font_Image(
	USHORT *dstImage,			//�o�͐�o�b�t�@
	int x, 						//�o�͐�o�b�t�@�̒��̊J�nX���W
	int y, 						//�o�͐�o�b�t�@�̒��̊J�nY���W
	int bufsize_width, 			//�o�͐�o�b�t�@�̕�
	int bufsize_height, 		//�o�͐�o�b�t�@�̍���
	const USHORT *ucs_str, 		//�`�悷�镶����
	const FONT_STYLE *style,	//�t�H���g�X�^�C��
	USHORT fcolor, 				//�t�H���g�J���[
	USHORT incolor, 			//���h��(�A�E�g���C���`�掞�ɒ���h��ꍇ�̓Z�b�g�B0�̏ꍇ����)
	VGint *pdrawRct				//�`����s�����ۂ̕��ƍ����̏��
);


#endif /* KCSPEC_OPENVG */

#ifdef __cplusplus
}
#endif

#endif /* __FONTAPI_H */