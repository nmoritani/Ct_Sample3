/**
*  Copyright (c) 2018 Panasonic Corporation
*/

/*******************************************************************************
�C���N���[�h�t�@�C��
*******************************************************************************/
#include <stdbool.h>
#include "freetype_wrapper.h"
#include "gdi.h"

//TODO:���������̊K�w�ɂ́AFT_*���o�Ă����Ȃ��悤�ɂ���(Freetype���g�p���Ă��邱�Ƃ��ӎ������Ȃ�����ɂ���

//#define USE_FT_CACHE	//Freetype�̃L���b�V�����g���ꍇ�͂���define��L����
#define USE_FONT_FILES	//Windows��Font�t�H���_����t�H���g��ǂݍ��ޏꍇ�͂�����L����
//#define USE_FT_MODULE

///////////////////////////////////////////////////
FT_Library  m_library = NULL;
FT_Face		m_face = NULL;
FT_Memory m_memory = NULL;

//�L���b�V���֘A
FTC_Manager    m_cache_man = NULL;		// �L���b�V���}�l�[�W��
FTC_CMapCache  m_cmap_cache = NULL;		// CharMap�̃L���b�V��
FTC_ImageCache m_image_cache = NULL;	// �O���t�C���[�W�̃L���b�V��
FTC_ImageTypeRec m_font_type;
FTC_ScalerRec m_scaler;
FT_Glyph m_cache_glyph = NULL;

#ifdef USE_FT_MODULE
void *freetype_alloc(FT_Memory memory, long size)
{
  return font_lib_alloc(size);
}

void freetype_free(FT_Memory memory, void *ptr)
{
    font_lib_free(ptr);
}

void *freetype_realloc(FT_Memory memory, long cur_size, long new_size,	void* ptr)
{
    return font_lib_realloc(ptr, new_size, cur_size);
}
#endif

/******************************************************************************/
/**
* �L���b�V�����̃R�[���o�b�N
*/
/******************************************************************************/
FT_Error face_requester(FTC_FaceID face_id, FT_Library library, FT_Pointer request_data, FT_Face* aface)
{
	// request_data��freetype_face��n���Ă�����Ă���̂�
	// ���̂܂ܕԂ��Ă�邪������FT_New_Face���Ă��悢�B
	*aface = (FT_Face)request_data;

	return 0;
}

/******************************************************************************/
/**
* �L���b�V�����̏�����
*/
/******************************************************************************/
static void InitCache(unsigned int faceID)
{
	if (m_library == NULL) {
		return;
	}

	if (m_face == NULL) {
		return;
	}

	FTC_Manager_New(m_library, 0, 0, 0, face_requester, m_face, &m_cache_man);
	FTC_CMapCache_New(m_cache_man, &m_cmap_cache);
	FTC_ImageCache_New(m_cache_man, &m_image_cache);

	m_font_type.face_id = (FTC_FaceID)faceID;
}


/******************************************************************************/
/**
* ���C�u�������̔j��
*/
/******************************************************************************/
static bool InitLibrary()
{
#ifdef USE_FT_MODULE
    m_memory = (FT_Memory)font_lib_alloc(sizeof(*m_memory));
    if (m_memory) {
        m_memory->user = NULL;
        m_memory->alloc = freetype_alloc;
        m_memory->realloc = freetype_realloc;
        m_memory->free = freetype_free;
    }
    
    if (FT_Err_Ok != FT_New_Library(m_memory, &m_library)) {
        if (m_memory != NULL) {
            font_lib_free(m_memory);
            m_memory = NULL;
        }
        return false;
    }
    
    FT_Add_Default_Modules(m_library);
    
    return true;
#else
	return (FT_Err_Ok == FT_Init_FreeType(&m_library));
#endif    
}

/******************************************************************************/
/**
* ���C�u�������̔j��
*/
/******************************************************************************/
static void DestroyLibrary()
{
#ifdef USE_FT_MODULE
    if (NULL != m_library) {
        FT_Done_Library(m_library );
        m_library = NULL;
    }
    
    if (NULL != m_memory) {
        font_lib_free(m_memory );
        m_memory = NULL;
    }
    
#else
	if (NULL != m_library) {
		FT_Done_FreeType(m_library);
		m_library = NULL;
	}
#endif
}

/******************************************************************************/
/**
* �t�F�C�X���̔j��
*/
/******************************************************************************/
static void DestroyFace()
{
#ifdef USE_FT_CACHE
	if (NULL != m_cache_man) {
		FTC_Manager_Done(m_cache_man);
		m_face = NULL;
		m_cache_man = NULL;
	}
#else
	if (NULL != m_face) {
		FT_Done_Face(m_face);
		m_face = NULL;
	}
#endif
}

/******************************************************************************/
/**
* FreeTYpe�t�H���g�̏���������
*/
/******************************************************************************/
void freetype_wrapper_init()
{
    printf("FreeType Library Initialize\n");
	m_library = NULL;
	m_face = NULL;
	InitLibrary();
}


/******************************************************************************/
/**
* FreeTYpe�t�H���g�̏I������
*/
/******************************************************************************/
void freetype_wrapper_terminate()
{
    printf("FreeType Library Destroyed\n");
	DestroyFace();
    //	DestroyLibrary();
}

/******************************************************************************/
/**
* �t�F�C�X�̃��[�h
*
* [in/out]
*  @param fileName	: �t�H���g�t�@�C����
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
#ifndef USE_FONT_FILES
static char s_font_table[] = {
#include "fontdata/n019004t.tbl",
	0x00
};
#endif

bool freetype_wrapper_load_newface(const char* fileName, unsigned int faceID)
{
#ifdef USE_FONT_FILES
#ifdef USE_FT_CACHE
	if (NULL != m_face) {
		//�L���b�V����face�̍폜
	}
#else
	if (NULL != m_face) {
		DestroyFace();
	}
#endif
	FT_Error err = FT_New_Face(m_library, fileName, 0, &m_face);
    
#else // !USE_FONT_FILES
	if (NULL != m_face) {
		return true;
	}
	FT_Error err = FT_New_Memory_Face(m_library, (FT_Byte*)s_font_table, (FT_Long)sizeof(s_font_table), 0, &m_face);
#endif

#ifdef USE_FT_CACHE
	InitCache(faceID);
#endif

	return err == FT_Err_Ok;
}

/******************************************************************************/
/**
* �O���t�̃C���f�b�N�X�擾
*
* [in/out]
*  @param char_code	: �L�����R�[�h
* [out]
*  @retrun �O���t�̃C���f�b�N�X
*
*/
/******************************************************************************/
static unsigned int GetGlyphIndex(unsigned long char_code)
{
	if (m_face == NULL) {
		return false;
	}

	return FT_Get_Char_Index(m_face, char_code);
}

/******************************************************************************/
/**
* �O���t�̃��[�h
*
* [in/out]
*  @param glyph_index	: �O���t�̃C���f�b�N�X
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
static bool LoadGlyph(unsigned int glyph_index)
{
	if (m_face == NULL) {
		return false;
	}

	return FT_Err_Ok == FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
}


/******************************************************************************/
/**
* �O���t�̃����_�����O
*
* [in/out]
*  @param IsMono	: ���m�N���t���O
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
static bool RenderGriph(bool IsMono)
{
	if (m_face == NULL) {
		return false;
	}

	FT_Render_Mode mode = IsMono ? FT_RENDER_MODE_MONO : FT_RENDER_MODE_NORMAL;
	FT_GlyphSlot slot = m_face->glyph;
	return (FT_Err_Ok == FT_Render_Glyph(slot, mode));
}


/******************************************************************************/
/**
* Freetype�̕����`����擾
*
* [in/out]
*  @param fontsize	: �t�H���g�T�C�Y
*  @param info		: �t�H���g�ݒ���
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
static bool freetype_get_font_info(int fontsize, FT_FONT_INFO *info)
{
	FT_GlyphSlot slot = m_face->glyph;

	if (slot->format != FT_GLYPH_FORMAT_BITMAP) {
		return false;
	}

	FT_Bitmap bitmap = slot->bitmap;

	double ratio = (double)m_face->size->metrics.y_ppem / (double)m_face->units_per_EM;

	// ��ʒu�̏������o��
	info->bitmapwidth = bitmap.width;
	info->bitmapheight = bitmap.rows;

	/////////////////////////////////////////////////////////////////
	info->descent = (m_face->descender * ratio) * -1;
	info->accent = (m_face->ascender * ratio);

	info->drawStartPosX = slot->bitmap_left;
	info->drawStartPosY = info->accent - slot->bitmap_top;

	// �r�b�g�}�b�v�̏������o��
	info->stride = bitmap.pitch;
	info->buf = bitmap.buffer;
	info->width = bitmap.width;

	info->height = info->accent + info->descent;
	if (info->height < fontsize) {
		info->height = fontsize;
	}

	info->advanceX = slot->advance.x >> 6;
	info->advanceY = info->drawStartPosY + info->bitmapheight;

	info->lineUnderflow = 0;

	return true;
}

static bool freetype_get_fontcache_info(int fontsize, FT_FONT_INFO *info)
{
	FT_GlyphSlot slot = m_face->glyph;
	FT_BitmapGlyph bitmap_gliph = (FT_BitmapGlyph)m_cache_glyph;

	if (slot->format != FT_GLYPH_FORMAT_BITMAP) {
		return false;
	}
	
	FT_Bitmap bitmap = bitmap_gliph->bitmap;

	double ratio = (double)m_face->size->metrics.y_ppem / (double)m_face->units_per_EM;

	// ��ʒu�̏������o��
	info->bitmapwidth = bitmap.width;
	info->bitmapheight = bitmap.rows;

	/////////////////////////////////////////////////////////////////
	info->descent = (m_face->descender * ratio) * -1;
	info->accent = (m_face->ascender * ratio);

	info->drawStartPosX = bitmap_gliph->left;
	info->drawStartPosY = info->accent - bitmap_gliph->top;

	// �r�b�g�}�b�v�̏������o��
	info->stride = bitmap.pitch;
	info->buf = bitmap.buffer;
	info->width = bitmap.width;

	info->height = info->accent + info->descent;
	if (info->height < fontsize) {
		info->height = fontsize;
	}

	info->advanceX = bitmap_gliph->root.advance.x >> 16;
	info->advanceY = info->drawStartPosY + info->bitmapheight;
	
	info->lineUnderflow = 0;

	return true;
}


bool freetype_wrapper_get_font_info(int fontsize, FT_FONT_INFO *info)
{
#ifdef USE_FT_CACHE
	return freetype_get_fontcache_info(fontsize, info);
#else
	return freetype_get_font_info(fontsize, info);
#endif
}


/******************************************************************************/
/**
* Freetype�̑����`��L����
*/
/******************************************************************************/
void freetype_wrapper_enable_bold()
{
	FT_Outline_EmboldenXY(&m_face->glyph->outline, 50, 50);
}

/******************************************************************************/
/**
* Freetype�̎Α̕`��L����
*/
/******************************************************************************/
void freetype_wrapper_enable_Italic()
{
	FT_Matrix matrix;
	matrix.xx = 1 << 16;
	matrix.xy = 0x5800;
	matrix.yx = 0;
	matrix.yy = 1 << 16;
	FT_Outline_Transform(&m_face->glyph->outline, &matrix);
}

/******************************************************************************/
/**
* Freetype�̉����`��L����
*/
/******************************************************************************/
void freetype_wrapper_enable_Outline()
{
	FT_Outline_EmboldenXY(&m_face->glyph->outline, 150, 150);
}

/******************************************************************************/
/**
* �t�H���g�X�^�C���̐ݒ�
*
* [in/out]
*  @param style		: �t�H���g�X�^�C��
*
*/
/******************************************************************************/
#define	IS_ON_FONTSTYLE_MONO(f)		(((FT_FONTSTYLE_MONO) & (f)) != 0)
#define	IS_ON_FONTSTYLE_BOLD(f)		(((FT_FONTSTYLE_BOLD) & (f)) != 0)
#define	IS_ON_FONTSTYLE_ITALIC(f)	(((FT_FONTSTYLE_ITALIC) & (f)) != 0)
#define	IS_ON_FONTSTYLE_OUTLINE(f)	(((FT_FONTSTYLE_OUTLINE) & (f)) != 0)
static void set_font_style(FT_FONT_STYLE *style)
{
	if (IS_ON_FONTSTYLE_BOLD(style->flag)) {
		//����
		freetype_wrapper_enable_bold();
	}
	else if (IS_ON_FONTSTYLE_OUTLINE(style->flag)) {
		//�g��
		freetype_wrapper_enable_Outline();
	}

	if (IS_ON_FONTSTYLE_ITALIC(style->flag)) {
		//�Α�
		freetype_wrapper_enable_Italic();
	}
}

/******************************************************************************/
/**
* Freetype�̕����̃O���t���[�h�A���������_�����O
*
* [in/out]
*  @param char_code		: �L�����R�[�h
*  @param style			: �t�H���g�X�^�C��
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
bool freetype_wrapper_load_char(unsigned long char_code, FT_FONT_STYLE *style)
{
	if (NULL == style) {
		return false;
	}
#ifdef USE_FT_CACHE
	///////////////////////////////////////////////////////////////
	//�O���t�̃C���f�b�N�X���擾����
	FT_Face freetype_face;
	FTC_FaceID faceID = m_font_type.face_id;
	FTC_Manager_LookupFace(m_cache_man, faceID, &freetype_face);

	m_font_type.flags = ((bool)style->flag) ? (FT_LOAD_MONOCHROME | FT_LOAD_RENDER) : FT_LOAD_RENDER;
	m_scaler.face_id = faceID;
	FT_Size font_size;
	FTC_Manager_LookupSize(m_cache_man, &m_scaler, &font_size);

	FT_Int cmap_index = FT_Get_Charmap_Index(freetype_face->charmap);
	FT_UInt glyph_index = FTC_CMapCache_Lookup(
		m_cmap_cache,
		faceID,
		cmap_index,
		char_code);
	///////////////////////////////////////////////////////////////
	//�擾�����C���f�b�N�X�ʒu�̃O���t�����[�h����
	FT_Error err;

	err = FTC_ImageCache_Lookup(m_image_cache, &m_font_type, glyph_index, &m_cache_glyph, NULL);

	return FT_Err_Ok == err;

#else
#if 0
	//�O���t�̃C���f�b�N�X���擾����
	FT_UInt glyph_index = GetGlyphIndex(char_code);

	//�擾�����C���f�b�N�X�ʒu�̃O���t�����[�h����
	if (!LoadGlyph(glyph_index)) return false;
#else
    if (m_face == NULL) {
        return false;
    }
    if (FT_Err_Ok != FT_Load_Char(m_face, char_code, FT_LOAD_DEFAULT))
        return false;
#endif

	//�t�H���g�X�^�C���̐ݒ�
	set_font_style(style);

	//���[�h�����O���t�������_�����O
	return RenderGriph(IS_ON_FONTSTYLE_MONO(style->flag));
#endif
}


/******************************************************************************/
/**
* Freetype�̕����T�C�Y�ݒ�
*
* [in/out]
*  @param width		: �c�T�C�Y
*  @param height	: ���T�C�Y
* [out]
*  @retrun ���� / ���s
*
*/
/******************************************************************************/
bool freetype_wrapper_set_char_size(long width, long height)
{
	if (m_face == NULL) {
		return false;
	}

#ifdef USE_FT_CACHE
	m_font_type.width = width;
	m_font_type.height = height;
	m_font_type.flags = 0;
	m_scaler.width = width;
	m_scaler.height = height;
	m_scaler.pixel = 1;
	m_scaler.x_res = 0;
	m_scaler.y_res = 0;
	return true;
#else
	return FT_Err_Ok == FT_Set_Pixel_Sizes(m_face, width, height);
#endif
}


/**********************************************************************************
* Copyright(C) by 2018 Panasonic Corporation.
**********************************************************************************/

