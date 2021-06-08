/**
@file     fontapi_config.h
@brief    フォントI/F（通称「フォントサービス」）のconfiguration
@author   Yuji Nomura @DSC BU, Panasonic Corp.
@date     2013.3.14 コード整理に伴い新規作成
@par      更新履歴: Subversionのログ参照
*/

#ifndef ___FONTAPI_CONFIG_H
#define ___FONTAPI_CONFIG_H

#include "fontapi.h"

/* フォントサービスのconfiguration */
#undef FONT_DEBUG  /* フォントサービスのログ出力を有効にするなら#define */
#undef FONTAPI_LOGGER  /* フォントサービスのログ出力ルーチンを有効にするなら#define */
#define STRPATH_DUMPER 0  /* OpenVGの文字列パス出力モジュール 0:無効 1:有効 */
#undef GPI_DEBUG  /* GPIのテスト用の動作にするなら#define */
#define USE_IOIF_KERNEL_TIMER  /* 1us単位のタイマーを使用するかどうか */
#undef ONLY_ONE_DT_HANDLE  /* DigiTypeのハンドルを1つのみにするかどうか */
#undef USE_FONT_SPECIFIC_ALNUM  /* 追加言語フォントの英数字を使用するかどうか */
#undef REPLACE_AW0_CHAR_WITH_FILLED_SQUARE  /* DT_WARNING_EMPTY_FONTが発生しなくてもAW=0の文字を■に置換するかどうか */
#define REPLACE_AW0_CHAR_AFTER_EMPTY_FONT_WARNING  /* DT_WARNING_EMPTY_FONTが発生したらAW=0の文字を■に置換するかどうか */
#undef DT_CACHE_CLEAR_EX /* DigiTypeのフォントキャッシュのクリアを強力な方法にするか（縁取り描画でゴミが出る対策） */
#define ENABLE_WIDTH_CONTROL_CODE /* 文字列中の幅調整の制御コードを有効にするかどうか */
#undef GRAY_EDGE_GRAY  /* 灰色文字の縁を灰色にするなら有効（VL30専用）*/
#undef USE_SDCARD_FDL  /* SDカードの"test.fdl"を使うかどうか（set_lang(LOCALE_IC)でロードされる）*/
#define DT_HINDI_BMPHEIGHT_IS_ALMOST_DOUBLE  /* DigiTypeが返すHindiのbmpheightが倍くらいの場合の暫定対応 */ /* 10/8 */
#define DT_HINDI_MAX_ASCENT 2  /* Hindiの最大ascent(== -rct.xy.y)、共通フォントFDLとHindi FDLの組み合わせによって変わる（20ドット基準） */
#define DT_HINDI_MAX_DESCENT 4  /* Hindiの最大descent（20ドット基準） */
#define HINDI_ASCENT_CUT_BY_NDOTS 2  /* Hindiのascentを一律何ドットカットするか（get_*_rectのheightも減る）（20ドット基準） */
#define IGNORE_DT_WARNING_EMPTY_FONT  /* Hindiでret == DT_WARNING_EMPTY_FONT（U+200Dがあると発生する）を無視するかどうか */ /* ArabicでU+200Fがあっても発生するようだ */
#define IGNORE_ALL_DT_WARNING  /* ret > 0 のエラーコード(DT_WARNING_*)を無視するかどうか */
#define GET_RECT_ERROR_IF_ZERO_RECT  /* get_rect系のI/Fで描画領域が0ならエラーを返すかどうか */
#define EDGED_HINDI_AJUST_H 0  /* 縁取りHindi文字を下にずらす量(dot) */
#undef USE_OVGL3CACHE  /* DigiTypeのOVGL3 Cacheを使用するかどうか */
#define USE_LOCAL_OVG_CACHE  /* fontapiでのVGPathキャッシュを有効にするかどうか */
#undef USE_MOCK_OBJECTS_FOR_OVG_CACHE /* fontapiでのVGPathキャッシュのテスト用のmock objectsを使用するかどうか */
#define STATIC_VGPATH  /* fontapi_get_path()が返すVGPathが呼び出し側でvgDestroyPathされないかどうか */
#undef OPENVG_PATH_LEAK_CHECKER  /* vgCreatePath/vgDeletePathの対応が正しいかどうかを検査するかどうか */
#undef ALWAYS_CENTER_UTF8_STRING_PATH   /* font_service_get_exact_rect_from_utf8は原点中心のVGPathを返す */
#define RTOL_PATH_ON_LEFT_OF_ORIGIN  /* Right-to-leftの文字列パスを原点より左に作るかどうか */
#define ASCII_OR_HEX_HEX_WIDTH_FACTOR 0.8  /* font_service_get_ascii_or_hex_path()のHEXの横倍率 */

#if KCSPEC_SLR
#define USE_FSTYLE_VG_GEN_EMPATH  /* OpenVGの場合は常にDigiTypeの"VG_GEN_EMPATH"モードを使用するかどうか */
#else
#undef USE_FSTYLE_VG_GEN_EMPATH  /* OpenVGの場合は常にDigiTypeの"VG_GEN_EMPATH"モードを使用するかどうか */
#endif

#ifdef USE_FSTYLE_VG_GEN_EMPATH
#define LOCAL_VGPATH_DATATYPE DT_GLYPH_CACHE_PATH_DATATYPE
#define SET_EMPATH_VALUE_ON_VGPATH(path, x) vgRemovePathCapabilities((path), (x) * VG_PATH_CAPABILITY_PATH_LENGTH)
#define GET_EMPATH_VALUE_ON_VGPATH(path) ((vgGetPathCapabilities(path) ^ VG_PATH_CAPABILITY_ALL) / VG_PATH_CAPABILITY_PATH_LENGTH)
#else
#define LOCAL_VGPATH_DATATYPE VG_PATH_DATATYPE_F
#endif

#ifdef KCSPEC_MAP_VIEW
#if KCSPEC_MAP_VIEW == 1  /* KCSPEC_OPENVG == 0でOpenVGを使うモデルのための暫定対応 */
#undef	KCSPEC_OPENVG
#define	KCSPEC_OPENVG	1
#endif
#endif

#if KCSPEC_OPENVG
#define USE_IWATA_PUD_LATIN  /* OpenVG使用機種では、OVG/グレースケール問わず、イワタPUDラテンフォントを使用する */
//#if KCSPEC_SLR || !CFG_USE_GENWARE
//#define COMPRESS_ASCENT_DESCENT_VERTICALLY  /* 一眼及び非GENWARE機種はascent/descent描画をしないので縦に縮める必要あり */
//#undef COMPRESS_ASCENT_DESCENT_VERTICALLY_EXCEPT_5_PERCENT  /* 上下5%はみ出し縮小モード（GF6/G6向け調整結果相当） */
//#undef USE_DT_COORD_LEFT_TOP  /* DT_COORD_LEFT_BOTだとDigiTypeの動作仕様がわかり難いので、V9以降はDT_COORD_LEFT_TOPを使用する */
//#endif
#else
#undef USE_IWATA_PUD_LATIN   /* OpenVG不使用機種（グレースケールのみ）では、イワタPUDラテンフォントを使用しない */
#define USE_FONT_SPECIFIC_ALNUM  /* 追加言語フォントの英数字を使用するかどうか */
#endif

#define USE_OPENVG		KCSPEC_OPENVG

#if KCSPEC_SLR
#define USE_OPENVG_COLOR_EDGE_IF  /* G5のトップメニュー画面で使用 */ /* ★注意★ PIC面を透過させるのは禁止（premultiplied alpha未対応のため） */
#else
#undef USE_OPENVG_COLOR_EDGE_IF
#endif

#if CFG_USE_SLR_OSD_OVG
#undef RTOL_PATH_ON_LEFT_OF_ORIGIN  /* OSD task+OVGの構成ではアラビア語／ペルシャ語も原点より右に作る */
#endif

#endif  /* ___FONTAPI_CONFIG_H */
