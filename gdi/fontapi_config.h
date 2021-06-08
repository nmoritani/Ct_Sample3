/**
@file     fontapi_config.h
@brief    �t�H���gI/F�i�ʏ́u�t�H���g�T�[�r�X�v�j��configuration
@author   Yuji Nomura @DSC BU, Panasonic Corp.
@date     2013.3.14 �R�[�h�����ɔ����V�K�쐬
@par      �X�V����: Subversion�̃��O�Q��
*/

#ifndef ___FONTAPI_CONFIG_H
#define ___FONTAPI_CONFIG_H

#include "fontapi.h"

/* �t�H���g�T�[�r�X��configuration */
#undef FONT_DEBUG  /* �t�H���g�T�[�r�X�̃��O�o�͂�L���ɂ���Ȃ�#define */
#undef FONTAPI_LOGGER  /* �t�H���g�T�[�r�X�̃��O�o�̓��[�`����L���ɂ���Ȃ�#define */
#define STRPATH_DUMPER 0  /* OpenVG�̕�����p�X�o�̓��W���[�� 0:���� 1:�L�� */
#undef GPI_DEBUG  /* GPI�̃e�X�g�p�̓���ɂ���Ȃ�#define */
#define USE_IOIF_KERNEL_TIMER  /* 1us�P�ʂ̃^�C�}�[���g�p���邩�ǂ��� */
#undef ONLY_ONE_DT_HANDLE  /* DigiType�̃n���h����1�݂̂ɂ��邩�ǂ��� */
#undef USE_FONT_SPECIFIC_ALNUM  /* �ǉ�����t�H���g�̉p�������g�p���邩�ǂ��� */
#undef REPLACE_AW0_CHAR_WITH_FILLED_SQUARE  /* DT_WARNING_EMPTY_FONT���������Ȃ��Ă�AW=0�̕��������ɒu�����邩�ǂ��� */
#define REPLACE_AW0_CHAR_AFTER_EMPTY_FONT_WARNING  /* DT_WARNING_EMPTY_FONT������������AW=0�̕��������ɒu�����邩�ǂ��� */
#undef DT_CACHE_CLEAR_EX /* DigiType�̃t�H���g�L���b�V���̃N���A�����͂ȕ��@�ɂ��邩�i�����`��ŃS�~���o��΍�j */
#define ENABLE_WIDTH_CONTROL_CODE /* �����񒆂̕������̐���R�[�h��L���ɂ��邩�ǂ��� */
#undef GRAY_EDGE_GRAY  /* �D�F�����̉����D�F�ɂ���Ȃ�L���iVL30��p�j*/
#undef USE_SDCARD_FDL  /* SD�J�[�h��"test.fdl"���g�����ǂ����iset_lang(LOCALE_IC)�Ń��[�h�����j*/
#define DT_HINDI_BMPHEIGHT_IS_ALMOST_DOUBLE  /* DigiType���Ԃ�Hindi��bmpheight���{���炢�̏ꍇ�̎b��Ή� */ /* 10/8 */
#define DT_HINDI_MAX_ASCENT 2  /* Hindi�̍ő�ascent(== -rct.xy.y)�A���ʃt�H���gFDL��Hindi FDL�̑g�ݍ��킹�ɂ���ĕς��i20�h�b�g��j */
#define DT_HINDI_MAX_DESCENT 4  /* Hindi�̍ő�descent�i20�h�b�g��j */
#define HINDI_ASCENT_CUT_BY_NDOTS 2  /* Hindi��ascent���ꗥ���h�b�g�J�b�g���邩�iget_*_rect��height������j�i20�h�b�g��j */
#define IGNORE_DT_WARNING_EMPTY_FONT  /* Hindi��ret == DT_WARNING_EMPTY_FONT�iU+200D������Ɣ�������j�𖳎����邩�ǂ��� */ /* Arabic��U+200F�������Ă���������悤�� */
#define IGNORE_ALL_DT_WARNING  /* ret > 0 �̃G���[�R�[�h(DT_WARNING_*)�𖳎����邩�ǂ��� */
#define GET_RECT_ERROR_IF_ZERO_RECT  /* get_rect�n��I/F�ŕ`��̈悪0�Ȃ�G���[��Ԃ����ǂ��� */
#define EDGED_HINDI_AJUST_H 0  /* �����Hindi���������ɂ��炷��(dot) */
#undef USE_OVGL3CACHE  /* DigiType��OVGL3 Cache���g�p���邩�ǂ��� */
#define USE_LOCAL_OVG_CACHE  /* fontapi�ł�VGPath�L���b�V����L���ɂ��邩�ǂ��� */
#undef USE_MOCK_OBJECTS_FOR_OVG_CACHE /* fontapi�ł�VGPath�L���b�V���̃e�X�g�p��mock objects���g�p���邩�ǂ��� */
#define STATIC_VGPATH  /* fontapi_get_path()���Ԃ�VGPath���Ăяo������vgDestroyPath����Ȃ����ǂ��� */
#undef OPENVG_PATH_LEAK_CHECKER  /* vgCreatePath/vgDeletePath�̑Ή������������ǂ������������邩�ǂ��� */
#undef ALWAYS_CENTER_UTF8_STRING_PATH   /* font_service_get_exact_rect_from_utf8�͌��_���S��VGPath��Ԃ� */
#define RTOL_PATH_ON_LEFT_OF_ORIGIN  /* Right-to-left�̕�����p�X�����_��荶�ɍ�邩�ǂ��� */
#define ASCII_OR_HEX_HEX_WIDTH_FACTOR 0.8  /* font_service_get_ascii_or_hex_path()��HEX�̉��{�� */

#if KCSPEC_SLR
#define USE_FSTYLE_VG_GEN_EMPATH  /* OpenVG�̏ꍇ�͏��DigiType��"VG_GEN_EMPATH"���[�h���g�p���邩�ǂ��� */
#else
#undef USE_FSTYLE_VG_GEN_EMPATH  /* OpenVG�̏ꍇ�͏��DigiType��"VG_GEN_EMPATH"���[�h���g�p���邩�ǂ��� */
#endif

#ifdef USE_FSTYLE_VG_GEN_EMPATH
#define LOCAL_VGPATH_DATATYPE DT_GLYPH_CACHE_PATH_DATATYPE
#define SET_EMPATH_VALUE_ON_VGPATH(path, x) vgRemovePathCapabilities((path), (x) * VG_PATH_CAPABILITY_PATH_LENGTH)
#define GET_EMPATH_VALUE_ON_VGPATH(path) ((vgGetPathCapabilities(path) ^ VG_PATH_CAPABILITY_ALL) / VG_PATH_CAPABILITY_PATH_LENGTH)
#else
#define LOCAL_VGPATH_DATATYPE VG_PATH_DATATYPE_F
#endif

#ifdef KCSPEC_MAP_VIEW
#if KCSPEC_MAP_VIEW == 1  /* KCSPEC_OPENVG == 0��OpenVG���g�����f���̂��߂̎b��Ή� */
#undef	KCSPEC_OPENVG
#define	KCSPEC_OPENVG	1
#endif
#endif

#if KCSPEC_OPENVG
#define USE_IWATA_PUD_LATIN  /* OpenVG�g�p�@��ł́AOVG/�O���[�X�P�[����킸�A�C���^PUD���e���t�H���g���g�p���� */
//#if KCSPEC_SLR || !CFG_USE_GENWARE
//#define COMPRESS_ASCENT_DESCENT_VERTICALLY  /* ���y�є�GENWARE�@���ascent/descent�`������Ȃ��̂ŏc�ɏk�߂�K�v���� */
//#undef COMPRESS_ASCENT_DESCENT_VERTICALLY_EXCEPT_5_PERCENT  /* �㉺5%�͂ݏo���k�����[�h�iGF6/G6�����������ʑ����j */
//#undef USE_DT_COORD_LEFT_TOP  /* DT_COORD_LEFT_BOT����DigiType�̓���d�l���킩���̂ŁAV9�ȍ~��DT_COORD_LEFT_TOP���g�p���� */
//#endif
#else
#undef USE_IWATA_PUD_LATIN   /* OpenVG�s�g�p�@��i�O���[�X�P�[���̂݁j�ł́A�C���^PUD���e���t�H���g���g�p���Ȃ� */
#define USE_FONT_SPECIFIC_ALNUM  /* �ǉ�����t�H���g�̉p�������g�p���邩�ǂ��� */
#endif

#define USE_OPENVG		KCSPEC_OPENVG

#if KCSPEC_SLR
#define USE_OPENVG_COLOR_EDGE_IF  /* G5�̃g�b�v���j���[��ʂŎg�p */ /* �����Ӂ� PIC�ʂ𓧉߂�����̂͋֎~�ipremultiplied alpha���Ή��̂��߁j */
#else
#undef USE_OPENVG_COLOR_EDGE_IF
#endif

#if CFG_USE_SLR_OSD_OVG
#undef RTOL_PATH_ON_LEFT_OF_ORIGIN  /* OSD task+OVG�̍\���ł̓A���r�A��^�y���V��������_���E�ɍ�� */
#endif

#endif  /* ___FONTAPI_CONFIG_H */
