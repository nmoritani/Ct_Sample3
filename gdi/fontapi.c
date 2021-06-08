#include "CtDebugPrint.h"
#include "gdi.h"

#include "fontapi_common.h"
#include <openvg_wrapper.h>

#ifdef WIN32_GUI_SIM
#include <windows.h>
#endif

#include <kernel.h>
#include <kernel_id.h>
#define ID_FONTAPI_SEM		(GDI_SEMID_FONTAPI)


/*------------------------------------------------------------------------------
    定数
------------------------------------------------------------------------------*/
/* DigiType API用のデフォルトフォントスタイルデータ */
const DT32_int styleval[]={
  0,				/*DT_FSTYLE_VERT=0,*/		/* Now, horizontal only.	*/
  24,				/*DT_FSTYLE_SIZEX,*/		/* desired x size			*/
  24,				/*DT_FSTYLE_SIZEY,*/		/* desired y size			*/
  0,				/*DT_FSTYLE_IS_BOLD,*/		/* Bold font(1) or not(0)	*/
  0,				/*DT_FSTYLE_IS_ITALIC,*/	/* Italic font(1) or not(0)	*/
  0					/*DT_FSTYLE_IS_UNDERLINE,*/	/* Underline(1) or not(0)	*/
};

/*------------------------------------------------------------------------------
    変数
------------------------------------------------------------------------------*/
/* DigiTypeのハンドラー等 */
DT_FontMgr dt_fontmgr = NULL;
DT_TextInfo dt_txtinfo;  /* スタック領域に置くにはサイズが大きいので、staticに変更 */
DT_Handle hGray = NULL;  /* DigiTypeのハンドラー（グレースケール用） */

#ifndef ONLY_ONE_DT_HANDLE
/* DigiType 2.5.12ではCreateFontすると多量のメモリを必要とするため、ハンドラーは1つとする */
DT_Handle hMono = NULL;  /* DigiTypeのハンドラー（モノクロ用） */
#endif

DT_Handle hOvg = NULL;  /* DigiTypeのハンドラー（OpenVG用） */  /* TODO: fontapi_ovg.cに移動 */

/* フォントデータ情報整理用 */
static DT_FontData  fonts[LOCALE_NUM];  /* DigiType 2.5.29で参照できなくなったため、fontapi.hで定義される値に変更 */
                                        /* 配列の添字はenum FONT_LOCALEで定義される値(LOCALE_XX) */

/* 現在ロードされている言語フォントデータの識別用 */
static enum FONT_LOCALE current_locale = LOCALE_NONE;

/*------------------------------------------------------------------------------
    プロトタイプ宣言
------------------------------------------------------------------------------*/


/***********************************************************************************************************************
 * FUNCTION		: fontapiエラーメッセージ関数
 ************************************************************************************************************************/
static void gdi_fontapi_errMsg(DT32_int err)
{
	switch (err) {
	case DT_BAD_FONTMGR_HANDLE:
		CtDebugPrint(CtDbg, "fontapi error!! DT_BAD_FONTMGR_HANDLE\n");
		break;
	case DT_BAD_FONT_HANDLE:
		CtDebugPrint(CtDbg, "fontapi error!! DT_BAD_FONT_HANDLE\n");
		break;
	case DT_ERROR_DESTROYFONT:
		CtDebugPrint(CtDbg, "fontapi error!! DT_ERROR_DESTROYFONT\n");
		break;
	case DT_STYLE_NOT_SUPPORT:
		CtDebugPrint(CtDbg, "fontapi error!! DT_STYLE_NOT_SUPPORT\n");
		break;
	case DT_SCRIPT_NOT_SUPPORT:
		CtDebugPrint(CtDbg, "fontapi error!! DT_SCRIPT_NOT_SUPPORT\n");
		break;
	case DT_LANG_NOT_SUPPORT:
		CtDebugPrint(CtDbg, "fontapi error!! DT_LANG_NOT_SUPPORT\n");
		break;
	case DT_ENGINEWKMEM_ERR:
		CtDebugPrint(CtDbg, "fontapi error!! DT_ENGINEWKMEM_ERR\n");
		break;
	case DT_UCS_STR_TOO_LONG:
		CtDebugPrint(CtDbg, "fontapi error!! DT_UCS_STR_TOO_LONG\n");
		break;
	case DT_UCS_ERR:
		CtDebugPrint(CtDbg, "fontapi error!! DT_UCS_ERR\n");
		break;
	case DT_NOT_ENOUGH_BUFFER:
		CtDebugPrint(CtDbg, "fontapi error!! DT_NOT_ENOUGH_BUFFER\n");
		break;
	case DT_FONTSTYLE_ERROR:
		CtDebugPrint(CtDbg, "fontapi error!! DT_FONTSTYLE_ERROR\n");
		break;
	case DT_CREATEFONT_MODE_ERR:
		CtDebugPrint(CtDbg, "fontapi error!! DT_CREATEFONT_MODE_ERR\n");
		break;
	case DT_LAYBUF_ERR:
		CtDebugPrint(CtDbg, "fontapi error!! DT_LAYBUF_ERR\n");
		break;
	case DT_BITBLT_ERR:
		CtDebugPrint(CtDbg, "fontapi error!! DT_BITBLT_ERR\n");
		break;
	case DT_TEMP_BUFFER_ERR:
		CtDebugPrint(CtDbg, "fontapi error!! DT_TEMP_BUFFER_ERR\n");
		break;
	case DT_CACHESET_ADD_ERR:
		CtDebugPrint(CtDbg, "fontapi error!! DT_CACHESET_ADD_ERR\n");
		break;
	case DT_WARNING_EMPTY_FONT:
		CtDebugPrint(CtDbg, "fontapi error!! DT_WARNING_EMPTY_FONT.\n The text string contains one or more characters that don't exist in the font handle.\n");
		break;
	case DT_WARNING_BREAKLINE:
		CtDebugPrint(CtDbg, "fontapi error!! DT_WARNING_BREAKLINE\n The text string contains breakline symbol inside, like 0x0A, 0x0D, 0x2028, 0x2029...\n");
		break;
	case DT_WARNING_BMP_CUTTED:
		CtDebugPrint(CtDbg, "fontapi error!! DT_WARNING_BMP_CUTTED\n Return by DT_RasterGrayBMP(), the grayBMPbuf might not be enough for all the string.\n");
		break;
	default:
		break;
	}
}

/*------------------------------------------------------------------------------
    共通関数定義
------------------------------------------------------------------------------*/
/*------------------------------------
    self VG object leak checker
--------------------------------------*/
static VGPath undestroyed_path[100];
static int num_created_path = 0;

VGPath *font_service_undestroyed_path(void)
{
	return undestroyed_path;
}

int font_service_num_undestroyed_path(void)
{
	return num_created_path;
}

static void record_path(VGPath p)
{
	if (p == VG_INVALID_HANDLE) {
		return;
	}

	if (num_created_path < 100) {
		undestroyed_path[num_created_path++] = p;
	}
}


static void unrecord_path(VGPath p)
{
	int i;
	for(i = 0; i < num_created_path; i++) {
		if (undestroyed_path[i] == p) {
			undestroyed_path[i] = undestroyed_path[--num_created_path];
			return;
		}
	}
}



static VGPath vgCreatePathMockObject(VGint pathFormat,
									 VGPathDatatype datatype,
									 VGfloat scale, VGfloat bias,
									 VGint segmentCapacityHint,
									 VGint coordCapacityHint,
									 VGbitfield capabilities)
{
	VGPath ret = vgCreatePath(pathFormat, datatype, scale, bias, segmentCapacityHint, coordCapacityHint, capabilities);
	record_path(ret);
	return ret;
}


static void vgDestroyPathMockObject(VGPath path)
{
	unrecord_path(path);
	vgDestroyPath(path);
}
#define vgCreatePath vgCreatePathMockObject
#define vgDestroyPath vgDestroyPathMockObject



/*------------------------------------------------------------------------------
    公開関数定義
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/
/**
@fn           font_service_init
@brief        Font Serviceの初期化
@param[in]    なし
@retval       <0 異常終了
@par          同期
@sa           [in] なし [out] current_locale
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
int  font_service_init(void)
{
	DT_FontMgr init_mgr = NULL;
	DT32_int ret = DT_SUCCESS;
	USHORT i;

	wai_sem(ID_FONTAPI_SEM);
	if (dt_fontmgr) goto finally;  /* 初期化済 */

	/* 全言語共通フォントデータの存在確認 */
#ifdef WIN32_GUI_SIM
	if (
#ifdef USE_IWATA_PUD_LATIN
		*(unsigned long *)UCS_CNS_PUD_W4_SYMBOL_MIX_FDL != 0x204C4446 || /* "FDL Font" */
		*(unsigned long *)UCS_CNS_PUD_W4_SYMBOL_MIX_FDL_last_bytes != 0x204C4446
#else
		*(unsigned long *)UCS_CNS_IWADA_SYMBOL_FDL != 0x204C4446 || /* "FDL Font" */
		*(unsigned long *)UCS_CNS_IWADA_SYMBOL_FDL_last_bytes != 0x204C4446
#endif
	){

#else	/* WIN32_GUI_SIM */
	int start_sig,end_sig;

#ifdef USE_IWATA_PUD_LATIN
	memcpy(&start_sig,UCS_CNS_PUD_W4_SYMBOL_MIX_FDL,sizeof(int));
	memcpy(&end_sig,UCS_CNS_PUD_W4_SYMBOL_MIX_FDL_last_bytes,sizeof(int));
#else
	memcpy(&start_sig,UCS_CNS_IWADA_SYMBOL_FDL,sizeof(int));
	memcpy(&end_sig,UCS_CNS_IWADA_SYMBOL_FDL_last_bytes,sizeof(int));
#endif

	if (
		start_sig != 0x204C4446 || /* "FDL Font" */
		end_sig != 0x204C4446
	){
#endif	/* WIN32_GUI_SIM */
		ret = -1;
		goto finally;
	}

	/* フォントデータの設定 */

//	fonts[LOCALE_EN].fontdata = (DT8_char*)UCS_CNS_PUD_W4_SYMBOL_MIX_FDL;
//	fonts[LOCALE_EN].nfsize = sizeof(UCS_CNS_PUD_W4_SYMBOL_MIX_FDL);
//	fonts[LOCALE_FX].fontdata = (DT8_char*)UCS_CNS_Ascii500_sample_FDL;
//	fonts[LOCALE_FX].nfsize = sizeof(UCS_CNS_Ascii500_sample_FDL);

#ifdef USE_IWATA_PUD_LATIN
	fonts[LOCALE_EN].fontdata = (DT8_char*)UCS_CNS_IWADA_SYMBOL_FDL;
	fonts[LOCALE_EN].nfsize = sizeof(UCS_CNS_IWADA_SYMBOL_FDL);
#endif

	fonts[LOCALE_IC].fontdata = (DT8_char*)iconfontdata;
	fonts[LOCALE_IC].nfsize = sizeof(iconfontdata);

	fonts[LOCALE_JP].fontdata = (DT8_char*)UCS_JIS_HEI_W4_FDL;
	fonts[LOCALE_JP].nfsize = sizeof(UCS_JIS_HEI_W4_FDL);
	fonts[LOCALE_SC].fontdata = (DT8_char*)Ucs_GB_Hei_W4_Part_FDL;
	fonts[LOCALE_SC].nfsize = sizeof(Ucs_GB_Hei_W4_Part_FDL);
	fonts[LOCALE_TC].fontdata = (DT8_char*)Ucs_Big5_Hei_W4_Part_FDL;
	fonts[LOCALE_TC].nfsize = sizeof(Ucs_Big5_Hei_W4_Part_FDL);
	fonts[LOCALE_KR].fontdata = (DT8_char*)Ucs_Hangul_Hei_W4_Part_FDL;
	fonts[LOCALE_KR].nfsize = sizeof(Ucs_Hangul_Hei_W4_Part_FDL);
	fonts[LOCALE_AR].fontdata = (DT8_char*)UCS_CNS_ARABIC_FDL;
	fonts[LOCALE_AR].nfsize = sizeof(UCS_CNS_ARABIC_FDL);
	fonts[LOCALE_TH].fontdata = (DT8_char*)UCS_CNS_THAI_FDL;
	fonts[LOCALE_TH].nfsize = sizeof(UCS_CNS_THAI_FDL);
	fonts[LOCALE_HI].fontdata = (DT8_char*)UCS_CNS_HINDI_FDL;
	fonts[LOCALE_HI].nfsize = sizeof(UCS_CNS_HINDI_FDL);
	fonts[LOCALE_FX].fontdata = (DT8_char*)UCS_CNS_Ascii500_sample_FDL;
	fonts[LOCALE_FX].nfsize = sizeof(UCS_CNS_Ascii500_sample_FDL);

	/* フォントエンジン初期化 */
	init_mgr = DT_InitDigiType(NULL, NULL);

	if(!init_mgr){
		//font engine error.
		ret = -1;
		goto finally;
	}

	/* 全言語共通フォントのみで起動 */
	hGray = DT_CreateFontFromMem(init_mgr, &fonts[LOCALE_EN], DT_GRAY16BMP_MODE, NULL, NULL); /* common font only */

	if (!hGray) {
		DT_unInitDigiType(init_mgr);
		ret = -1;
		goto finally;
	}

	/* 全言語共通フォントのみで起動(OpenVG) */
	hOvg = DT_CreateFontFromMem(init_mgr, &fonts[LOCALE_EN], DT_OUTLINE_MODE, NULL, NULL);

	if (!hOvg || (ret != DT_SUCCESS)) {
		DT_DestroyFont(hGray);
		DT_unInitDigiType(init_mgr);
		gdi_fontapi_errMsg(ret);
		ret = -1;
		goto finally;
	}

#ifndef ONLY_ONE_DT_HANDLE
	hMono = DT_CreateFontFromMem(init_mgr, &fonts[LOCALE_EN], DT_MONOCHROME_MODE, NULL, &fonts[LOCALE_IC]);
	if(!hMono){
		DT_unInitDigiType(init_mgr);
		ret = -1;
		goto finally;
	}
#endif

	for (i = 0; i < 6; i++) {
	  ret |= DT_SetFontStyle(hGray, (DT_FontStyle_Option)i, styleval[i]);
#ifndef ONLY_ONE_DT_HANDLE
	  ret |= DT_SetFontStyle(hMono, (DT_FontStyle_Option)i, styleval[i]);
#endif

	  if ((DT_FontStyle_Option)i != DT_FSTYLE_IS_BOLD)  /* DT_OUTLINE_MODEではDT_FSTYLE_IS_BOLDは不対応 */
		  ret |= DT_SetFontStyle(hOvg, (DT_FontStyle_Option)i, styleval[i]);
	}

	/* for DigiType v2.5.29 and later */
	ret |= DT_SetFontStyle(hGray, DT_FSTYLE_BIDI_RULE, DT_BIDI_UNIRULE);
	ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_BIDI_RULE, DT_BIDI_UNIRULE);

	ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_VG_GEN_EMPATH, 0);
	ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_VG_COORD, DT_COORD_LEFT_BOT);

	current_locale = LOCALE_EN;
	dt_fontmgr = init_mgr;

 finally:
	sig_sem(ID_FONTAPI_SEM);
	return ret;
}

#if KCSPEC_ARM_OPENVG
/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_font_data_table
@brief        別CPUのfontapi初期化のためのfonts情報を取得する
@param[in]    なし
@retval       DT_FontData*
@par          同期
@sa           [in] なし [out] current_locale
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
FONT_DATATABLE *font_service_get_font_data_table(void){
	return (FONT_DATATABLE*)fonts;
}
#endif /* KCSPEC_ARM_OPENVG */

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_quit
@brief        Font Serviceの終了処理
@param[in]    なし
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2011/11/1 新規作成
*/
/*------------------------------------------------------------------------------*/
int  font_service_quit(void)
{
	DT32_int ret = DT_SUCCESS;

	wai_sem(ID_FONTAPI_SEM);
	if (dt_fontmgr == NULL) goto finally;  /* 未初期化 */

	/* フォントエンジンのワークメモリの初期化 */
	if (hGray != NULL){
		ret |= DT_DestroyFont(hGray);
		hGray = NULL;
	}
#ifndef ONLY_ONE_DT_HANDLE
	if (hMono != NULL){
		ret |= DT_DestroyFont(hMono);
		hMono = NULL;
	}
#endif

	if (hOvg != NULL){
		ret |= DT_DestroyFont(hOvg);
		hOvg = NULL;
	}

	ret |= DT_unInitDigiType(dt_fontmgr);
	dt_fontmgr = NULL;

 finally:
	sig_sem(ID_FONTAPI_SEM);
	return ret;
}

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_lang
@brief        現在のフォントロケールの取得
@param[in]    なし
@retval       ロケール種別
@par          同期
@sa           [in] current_locale [out] なし
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
enum FONT_LOCALE font_service_get_lang(void)
{
  return current_locale;
}

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_set_lang
@brief        フォントロケールの切替
@param[in]    loc: ロケール種別
@retval       <0 異常終了
@par          同期
@sa           [in][out] current_locale
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
int font_service_set_lang(enum FONT_LOCALE loc)
{
	DT32_int ret = DT_SUCCESS;
	int i;

	if (!dt_fontmgr){	/* 未初期化なら */
		ret = font_service_init();
		if (ret < 0) return ret;
	}

	wai_sem(ID_FONTAPI_SEM);

	/* 現在のロケールから変更が無ければ何もしない */
	if (loc == current_locale) goto finally;

	/* 再度CreateFontする前にDestroyFontが必要 */
	if (hGray)
		ret |= DT_DestroyFont(hGray);
#ifndef ONLY_ONE_DT_HANDLE
	if (hMono)
		ret |= DT_DestroyFont(hMono);
#endif

	if (hOvg)
		ret |= DT_DestroyFont(hOvg);

	if (ret < 0) {
		ret = -1;
		goto finally;
	}
	current_locale = LOCALE_NONE;

	/* CreateFontの処理 */
	switch(loc){
	case LOCALE_JP:
	case LOCALE_SC:
	case LOCALE_TC:
	case LOCALE_KR:
	case LOCALE_AR:
	case LOCALE_TH:
	case LOCALE_HI:
		hGray = DT_CreateFontFromMem(dt_fontmgr, &fonts[LOCALE_EN], DT_GRAY16BMP_MODE, &fonts[loc], &fonts[LOCALE_IC]); /* common, locale font, bitmap font */
#ifndef ONLY_ONE_DT_HANDLE
		hMono = DT_CreateFontFromMem(dt_fontmgr, &fonts[LOCALE_EN], DT_MONOCHROME_MODE, &fonts[loc], &fonts[LOCALE_IC]);
#endif
		hOvg = DT_CreateFontFromMem(dt_fontmgr, &fonts[LOCALE_EN], DT_OUTLINE_MODE, &fonts[loc], NULL);
		break;

	case LOCALE_FX:
		hGray = DT_CreateFontFromMem(dt_fontmgr, &fonts[loc], DT_GRAY16BMP_MODE, &fonts[LOCALE_EN], &fonts[LOCALE_IC]); /* common, locale font, bitmap font */
#ifndef ONLY_ONE_DT_HANDLE
		hMono = DT_CreateFontFromMem(dt_fontmgr, &fonts[loc], DT_MONOCHROME_MODE, &fonts[LOCALE_EN], &fonts[LOCALE_IC]);
#endif
		hOvg = DT_CreateFontFromMem(dt_fontmgr, &fonts[loc], DT_OUTLINE_MODE, &fonts[LOCALE_EN], NULL);
		break;

	default:
		hGray = DT_CreateFontFromMem(dt_fontmgr, &fonts[LOCALE_EN], DT_GRAY16BMP_MODE, &fonts[LOCALE_JP], &fonts[LOCALE_IC]); /* common, bitmap font */
#ifndef ONLY_ONE_DT_HANDLE
		hMono = DT_CreateFontFromMem(dt_fontmgr, &fonts[LOCALE_EN], DT_MONOCHROME_MODE, &fonts[LOCALE_JP], &fonts[LOCALE_IC]);
#endif
		hOvg = DT_CreateFontFromMem(dt_fontmgr, &fonts[LOCALE_EN], DT_OUTLINE_MODE, &fonts[LOCALE_JP], NULL);
	}

#ifdef ONLY_ONE_DT_HANDLE
	if(!hGray){
#else
	if(!hGray || !hMono){
#endif
//		ASSERT(0);  /* DT_Handle作成失敗 */
		ret = -1;
		goto finally;
	}

	for(i = 0; i < 6; i++) {
		ret |= DT_SetFontStyle(hGray, (DT_FontStyle_Option)i, styleval[i]);
#ifndef ONLY_ONE_DT_HANDLE
		ret |= DT_SetFontStyle(hMono, (DT_FontStyle_Option)i, styleval[i]);
#endif
		if ((DT_FontStyle_Option)i != DT_FSTYLE_IS_BOLD)  /* DT_OUTLINE_MODEではDT_FSTYLE_IS_BOLDは不対応 */
			ret |= DT_SetFontStyle(hOvg, (DT_FontStyle_Option)i, styleval[i]);
	}

	/* for DigiType v2.5.29 and later */
	ret |= DT_SetFontStyle(hGray, DT_FSTYLE_BIDI_RULE, DT_BIDI_UNIRULE);
	ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_BIDI_RULE, DT_BIDI_UNIRULE);

	ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_VG_GEN_EMPATH, 0);
	ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_VG_COORD, DT_COORD_LEFT_BOT);

	current_locale = loc;

 finally:
	sig_sem(ID_FONTAPI_SEM);
	return ret;
}


#if 0
/***********************************************************************************************************************
 * FUNCTION		: フォントスタイルの設定関数
 ************************************************************************************************************************/
static DT32_int font_set_fontstyle(DT_Handle h, const FONT_STYLE *style, DT32_int isNormalStyle)
{
	DT16_ushort	writedir = 0;
	DT32_int	ret = 0;

	if (NULL == style) {
		return DT_STYLE_NOT_SUPPORT;
	}

	writedir = (DT16_ushort)((style->righttoleft) ? DT_RIGHTTOLEFT : DT_LEFTTORIGHT);	/* pgr0247	*/

	ret |= DT_SetFontStyle(h, DT_FSTYLE_SIZEX, style->size_x);
	ret |= DT_SetFontStyle(h, DT_FSTYLE_SIZEY, style->size_y);
	ret |= DT_SetFontStyle(h, DT_FSTYLE_IS_BOLD, style->bold);
	ret |= DT_SetFontStyle(h, DT_FSTYLE_IS_ITALIC, style->italic);
	ret |= DT_SetFontStyle(h, DT_FSTYLE_IS_UNDERLINE, style->underline);
	ret |= DT_SetFontStyle(h, DT_FSTYLE_IS_STRIKE, style->strike);
	ret |= DT_SetFontStyle(h, DT_FSTYLE_SPACING, style->spacing);
	ret |= DT_SetFontStyle(h, DT_FSTYLE_WRITEDIR, writedir);

	if (0 == style->mono) {
		ret |= DT_SetFontStyle(h, DT_FSTYLE_GRAD, DT_GRAY_16);
		ret |= DT_SetFontStyle(h, DT_FSTYLE_GRAD_VALUES, DT_GRADE_INDEX_0X00_0X0F);
	}

	//ノーマルスタイルの場合、太字・アウトラインの設定は行わずに設定を完了する
	if (isNormalStyle) {
		ret |= DT_SetFontStyle(h, DT_FSTYLE_F_EDGE, DT_STYLE_NORMAL);
		return ret;
	}

	//太字の場合
	if (style->bold) {
		ret |= DT_SetFontStyle(h, DT_FSTYLE_F_EDGE, DT_STYLE_BOLD);
	}

	//アウトライン（太字とアウトラインが被った場合は、アウトラインを優先する）
	if (style->edge) {
		DT32_int w_edge266 = (DT32_int)DTFixToF266(style->edge, DTDecTo266Frac(50));	/* 縁太さ=edge+0.5に対応する固定小数点での値 */
		DT32_int w_edge = (DT32_int)DTF266ToInt(w_edge266);								/* 整数への切り上げ値 */

		ret |= DT_SetFontStyle(h, DT_FSTYLE_F_EDGE, DT_STYLE_OUTLINE);
		ret |= DT_SetFontStyle(h, DT_FSTYLE_SPACING, style->spacing - 2 * w_edge);		/* 参考: TestDigiTypeのサンプルコード */
		ret |= DT_SetFontStyle(h, DT_FSTYLE_W_EDGE, 0);
		ret |= DT_SetFontStyle(h, DT_FSTYLE_W_EDGE_26_6, w_edge266);
	}

	return ret;
}

/***********************************************************************************************************************
 * FUNCTION		: ビットマップフォントのビットマップ生成関数
 ************************************************************************************************************************/
static int font_create_bitmap_font_image(DT_Handle h, UCHAR *dst, const USHORT *ucs_str, int bufsize_size, DT_RECT *pRct)
{
	DT32_int	len;
	DT32_int	ret = 0;

	if ((NULL == dst) || (NULL == ucs_str) || (NULL == pRct)) {
		return DT_TEMP_BUFFER_ERR;
	}

	/* 文字数カウント */
	for (len = 0; ucs_str[len]; len++);

	/* 描画範囲取得 */
	ret = DT_GetTextRect(h, (DT16_ushort *)ucs_str, len, pRct, NULL, &dt_txtinfo);
	if (ret != DT_SUCCESS) {
		return ret;
	}

	//描画予定バッファサイズチェック
	if (bufsize_size < (dt_txtinfo.xbytes * dt_txtinfo.bmpheight)) {
		return DT_TEMP_BUFFER_ERR;
	}

	//DT_GetTextRect()で取得するrct.hwにはFONT_STYLEでセットしたフォントサイズが入るが、フォント画像の高さはフォントサイズより大きくなることがある。
	//フォント画像の実際のサイズはdt_txtinfo.xbytes、dt_txtinfo.bmpheightにセットされる。
	//出力で返すDT_RECTには実際の画像の高さを渡したいので、dt_txtinfoの情報をセットしておく
	pRct->hw.vx	= dt_txtinfo.xbytes;
	pRct->hw.vy	= dt_txtinfo.bmpheight;

	/* フォントのビットマップ生成 */
	memset(dst, 0, dt_txtinfo.xbytes * dt_txtinfo.bmpheight);

	return DT_RasterGrayBMP(h, (DT16_ushort *)ucs_str, len, dst, 0, 0, pRct->hw.vx, pRct->hw.vy);
}

/***********************************************************************************************************************
 * FUNCTION		: グレイビットマップ(8bit分)→カラーコード変換関数
 ************************************************************************************************************************/
static USHORT convert_gray_to_color_code(UCHAR color)
{
	int r = (0 == (color & 0x0004)) ? 0 : 0xF000;
	int g = (0 == (color & 0x0002)) ? 0 : 0x0F00;
	int b = (0 == (color & 0x0001)) ? 0 : 0x00F0;
	int a = 0x000F;
	return r | g | b | a;
}

/***********************************************************************************************************************
 * FUNCTION		: グレイビットマップ→カラーコード変換関数
 ************************************************************************************************************************/
static int convert_gray_bitmap_to_color(USHORT *bufTop, UCHAR value, USHORT color, int buf_size)
{
	USHORT *bufCurrent = bufTop;

	if (NULL == bufTop) {
		return 0;
	}

	if (value != 0x00) {
		*bufCurrent = (USHORT)((0 == color) ? convert_gray_to_color_code(value) : color);	/* pgr0247 意図通りのキャスト */
	}
	return 1;
}

/***********************************************************************************************************************
 * FUNCTION		: モノクロビットマップ(8bit分)→カラーコード変換関数
 ************************************************************************************************************************/
static int convert_mono_bitmap_to_color(USHORT *bufTop, UCHAR value, USHORT color, int buf_size)
{
	int iBitShift;
	USHORT *bufCurrent = bufTop;

	//・R(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ra
	//・G(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ga
	//・B(X) = (Cmax - RGBmax + RGBmin) * X / 100 + Ba


	if (NULL == bufTop) {
		return 0;
	}

	for (iBitShift = 7; 0 <= iBitShift; iBitShift--) {
		//バッファサイズを超えていたら終了
		if (buf_size < (bufCurrent - bufTop)) {
			break;
		}

		//該当ビットがONしていたらカラーをセットする
		if (value & (0x01 << iBitShift)) {
			*bufCurrent = color;
		} else {
			*bufCurrent = 0x0000;
		}

		bufCurrent++;
	}
	return (bufCurrent - bufTop);
}

/***********************************************************************************************************************
 * FUNCTION		: ビットマップ→カラーコード変換関数
 ************************************************************************************************************************/

static void convert_bitmap_to_color(USHORT *dst, UCHAR *src, int start_x, int start_y, int bufsize_width, int bufsize_height, const FONT_STYLE *style, int width, int height, USHORT color)
{
	typedef int (*FUNC_CONV_BITMAP_TO_COLOR)(USHORT *, UCHAR, USHORT, int);
	static FUNC_CONV_BITMAP_TO_COLOR func_convertBitmapToColor[] = {
		convert_gray_bitmap_to_color,	//Gray
		convert_mono_bitmap_to_color,	//Mono
	};
	int isMonoBitmap;
	int x, y;
//	int x_size = isMonoBitmap ? (width / 8 + ((width % 8 != 0) ? 1 : 0)) : width;
	int x_size = width;
	int y_size = height;
	USHORT *bufTopY;
	USHORT *bufCurrent;

	if ((NULL == dst) || (NULL == src) || (NULL == style)) {
		return;
	}

	bufTopY = (USHORT *)(dst + ((start_y * bufsize_width) + start_x));
	isMonoBitmap = (style->mono) ? 1 : 0;


	for (y = 0; (y < y_size) && ((start_y + y) < bufsize_height); y++) {
		bufCurrent = bufTopY;

		for (x = 0; (x < x_size) && ((start_x + x) < bufsize_width); x++) {
			bufCurrent += (*func_convertBitmapToColor[isMonoBitmap])(bufCurrent, src[(y * width) + x], color, (bufsize_width - (start_x + x)));
		}
		bufTopY += bufsize_width;
	}
}

/***********************************************************************************************************************
 * FUNCTION		: ビットマップフォントイメージ描画関数
 ************************************************************************************************************************/
#define	BITMAP_CANVAS_WIDTH			(512)	//横：512
#define	BITMAP_CANVAS_HEIGHT		(256)	//縦：256pt
static UCHAR s_drawBmpFont_tmpbuf[BITMAP_CANVAS_WIDTH * BITMAP_CANVAS_HEIGHT];	//TODO:サイズは後で考える
static int font_draw_bitmap_font_image(
	DT_Handle h, 				//描画用ハンドル
	USHORT *dstImage, 			//出力先イメージバッファ
	int x, 						//出力先バッファの中の開始X座標
	int y, 						//出力先バッファの中の開始Y座標
	int bufsize_width, 			//出力先バッファの幅
	int bufsize_height, 		//出力先バッファの高さ
	const USHORT *ucs_str, 		//描画する文字列
	const FONT_STYLE *style, 	//フォントスタイル
	USHORT color, 				//フォントカラー
	DT32_int isNormalStyle)			//
{
	DT_RECT		rct = {{0,0}, {0,0}};
	DT32_int	ret = DT_SUCCESS;

	//フォントスタイルの設定
	ret = font_set_fontstyle(h, style, isNormalStyle);
	if (ret != DT_SUCCESS) {
		gdi_fontapi_errMsg(ret);
		goto EXIT;
	}

	//フォントイメージの生成
	ret = font_create_bitmap_font_image(h, s_drawBmpFont_tmpbuf, ucs_str, sizeof(s_drawBmpFont_tmpbuf), &rct);
	if (ret != DT_SUCCESS) {
		gdi_fontapi_errMsg(ret);
		goto EXIT;
	}

	//生成したビットマップをカラーコードに変換して出力
	convert_bitmap_to_color(dstImage, s_drawBmpFont_tmpbuf, x, y, bufsize_width, bufsize_height, style, rct.hw.vx, rct.hw.vy, color);

 EXIT:
	return ret;
}

/*------------------------------------------------------------------------------*/
/**
@fn           convert_truecolor_to_highcolor
*/
/*------------------------------------------------------------------------------*/

static USHORT convert_truecolor_to_highcolor(unsigned int color)
{
	unsigned char color_tbl[4];
	color_tbl[0] = (unsigned char)((color >> 24) & 0xff);					/* pgr0247 意図通りのキャスト */
	color_tbl[1] = (unsigned char)((color >> 16) & 0xff);					/* pgr0247 意図通りのキャスト */
	color_tbl[2] = (unsigned char)((color >> 8) & 0xff);					/* pgr0247 意図通りのキャスト */
	color_tbl[3] = (unsigned char)((color) & 0xff);							/* pgr0247 意図通りのキャスト */

	color_tbl[0] = (unsigned char)(((color_tbl[0] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */
	color_tbl[1] = (unsigned char)(((color_tbl[1] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */
	color_tbl[2] = (unsigned char)(((color_tbl[2] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */
	color_tbl[3] = (unsigned char)(((color_tbl[3] * 0x0F) / 0xFF) & 0x0F);	/* pgr0247 意図通りのキャスト */

	return ((color_tbl[0] << (3 * 4))
		|   (color_tbl[1] << (2 * 4))
		|   (color_tbl[2] << (1 * 4))
		|   (color_tbl[3] << (0 * 4)));
}

/*------------------------------------------------------------------------------*/
/**
@fn           gdi_fontapi_create_bmp_font_Image
@brief        ビットマップフォントイメージの取得
@retval       <0 異常終了
@par          同期
*/
/*------------------------------------------------------------------------------*/
int gdi_fontapi_create_bmp_font_Image(
	USHORT *dstImage,			// 描画用ハンドル
	int bufsize_width, 			// 出力先バッファの幅
	int bufsize_height, 		// 出力先バッファの高さ
	const USHORT *ucs_str, 		// 描画する文字列
	const FONT_STYLE *style, 	// フォントスタイル
	unsigned int fill_color, 	// フォントカラー
	unsigned int stroke_color) 	// 縁線カラー
{
	DT_Handle	h;
	DT32_int	ret = 0;
	USHORT fcolor, incolor;

	if ((NULL == dstImage) || (NULL == ucs_str) || (NULL == style)) {
		return DT_STYLE_NOT_SUPPORT;
	}

	h = (0 == style->mono) ? hGray : hMono;

	wai_sem(ID_FONTAPI_SEM);

	//###mada 32ビットカラーを16ビットカラーに変更。実際に使うときはカラーパレット？
	if (style->edge && (0 != stroke_color)) {
		fcolor = convert_truecolor_to_highcolor(stroke_color);
		incolor = convert_truecolor_to_highcolor(fill_color);
	} else {
		((FONT_STYLE *)style)->edge = 0;
		fcolor = convert_truecolor_to_highcolor(fill_color);
		incolor = 0;
	}

	//描画
	ret = font_draw_bitmap_font_image(h, dstImage, 0, 0, bufsize_width, bufsize_height, ucs_str, style, fcolor, 0);
	if (ret != DT_SUCCESS) {
		gdi_fontapi_errMsg(ret);
		goto EXIT;
	}

	//中塗りのアウトライン描画の場合はスタイルをノーマルにして再描画
	if (style->edge && (0 != incolor)) {
		int adjust = (int)(11.0f * (float)(style->size_y) / 100.0f);	/* pgr0247 意図通りのキャスト */
		ret = font_draw_bitmap_font_image(h, dstImage, adjust, adjust, bufsize_width, bufsize_height, ucs_str, style, incolor, 1);
	}

 EXIT:
	sig_sem(ID_FONTAPI_SEM);

	return ret;
}
#endif

/*------------------------------------------------------------------------------*/
/**
@fn           gdi_fontapi_get_rect
@brief        文字列イメージの描画サイズの取得
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@param[out]   width   文字列イメージの横サイズ
@param[out]   height  文字列イメージの縦サイズ
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
*/
/*------------------------------------------------------------------------------*/
int gdi_fontapi_get_rect(const FONT_STYLE *style,
						 const unsigned short *ucs_str,
						 unsigned short *width,
						 unsigned short *height,
						 unsigned short *xbytes,
						 unsigned char isBitmapFont)
{
	DT_RECT		rct = {{0,0}, {0,0}};
	DT32_int	ret = 0;
	DT16_ushort	writedir = 0;
	unsigned short	len = 0;
	DT_Handle	h;
	unsigned short	work_str[DT_MAX_STRING_LENGTH] = { 0 };

	if ((NULL == style) || (NULL == ucs_str) || (NULL == width) || (NULL == height) || (NULL == xbytes)) {
		return 0;
	}

	wai_sem(ID_FONTAPI_SEM);

	h = (isBitmapFont) ? ((0 == style->mono) ? hGray : hMono) : hOvg;

	//フォントスタイルの設定
	writedir = (DT16_ushort)((style->righttoleft) ? DT_RIGHTTOLEFT : DT_LEFTTORIGHT);	/* pgr0247	*/
	{
		ret |= DT_SetFontStyle(h, DT_FSTYLE_SIZEX, style->size_x);
		ret |= DT_SetFontStyle(h, DT_FSTYLE_SIZEY, style->size_y);
//		ret |= DT_SetFontStyle(h, DT_FSTYLE_IS_BOLD, style->bold);			/* DigiTypeのDT_OUTLINE_MODEでは不対応 */
//		ret |= DT_SetFontStyle(h, DT_FSTYLE_IS_ITALIC, style->italic);		/* 同上（DigiType API仕様確認必要） */
//		ret |= DT_SetFontStyle(h, DT_FSTYLE_IS_UNDERLINE, style->underline);	/* 同上（DigiType API仕様確認必要） */
//		ret |= DT_SetFontStyle(h, DT_FSTYLE_IS_STRIKE, style->strike);		/* 同上（DigiType API仕様確認必要） */
		ret |= DT_SetFontStyle(h, DT_FSTYLE_SPACING, style->spacing);
		ret |= DT_SetFontStyle(h, DT_FSTYLE_WRITEDIR, writedir);
		ret |= DT_SetFontStyle(h, DT_FSTYLE_F_EDGE, DT_STYLE_OUTLINE);

		if (ret != DT_SUCCESS) {
			gdi_fontapi_errMsg(ret);
			goto DESTROY_AND_EXIT;
		}
	}

	/* 文字数カウント */
	for (len = 0; ucs_str[len]; len++);
	if (len <= 0) goto DESTROY_AND_EXIT;

	if (DT_MAX_STRING_LENGTH <= len || CountLineFeedCode(ucs_str) > 0) {
		//DigiTypeの最大文字数(50文字)を超えていた場合
		//または改行コードがある場合

		BOOL bLineFeedCode_backup = FALSE;
		unsigned short total_copylen = 0;
		unsigned short total_width = 0;
		unsigned short total_height = 0;
		unsigned short total_xbytes = 0;

		do {
			unsigned short LineFeedCode = 0;
			unsigned short max_str = DT_MAX_STRING_LENGTH - 1;		//NULL含み50文字なので-1しておく
			unsigned short remain_str = len - total_copylen;		//残り文字数
			unsigned short copylen = (max_str < remain_str) ? max_str : remain_str;

			//文字列をワークにコピーする
			unsigned short index;
			for (index = 0; index < copylen; index++) {
				if (ucs_str[total_copylen + index] == '\n' || ucs_str[total_copylen + index] == '\r') {
					if (ucs_str[total_copylen + index] == '\r' && ucs_str[total_copylen + index + 1] == '\n') {
						LineFeedCode += 1;
					}
					LineFeedCode += 1;
					break;
				}
				work_str[index] = ucs_str[total_copylen + index];
			}
			work_str[index] = 0x00;	//NULL終端

			//描画情報の取得
			ret = DT_GetTextRect(h, (DT16_ushort *)work_str, index, &rct, NULL, &dt_txtinfo);
			if (ret != DT_SUCCESS) {
				gdi_fontapi_errMsg(ret);
				goto DESTROY_AND_EXIT;
			}

			//サイズ更新 (前回の結果で更新を行う)
			if (bLineFeedCode_backup == TRUE) {
				total_width = (total_width < dt_txtinfo.bmpwidth) ? dt_txtinfo.bmpwidth : total_width;	/* pgr0351 */ /* pgr0247 */ /* pgr0360 */
				total_height += dt_txtinfo.bmpheight;	/* pgr0351 */ /* pgr0360 */
				total_xbytes += (isBitmapFont) ? (dt_txtinfo.xbytes * 8) * sizeof(unsigned short) : 0;	/* pgr0351 */
			}
			else {
				total_width += (unsigned short)dt_txtinfo.bmpwidth;	/* pgr0351 */ /* pgr0247 */
				total_height = (total_height < dt_txtinfo.bmpheight) ? dt_txtinfo.bmpheight : total_height;	/* pgr0351 */ /* pgr0360 */
				total_xbytes += (isBitmapFont) ? (dt_txtinfo.xbytes * 8) * sizeof(unsigned short) : 0;	/* pgr0351 */
			}

			//更新後処理
			if (LineFeedCode >= 1)	index += LineFeedCode;	//改行コード分
			bLineFeedCode_backup = LineFeedCode >= 1 ? TRUE : FALSE;
			total_copylen += index;

		} while (total_copylen < len);	//文字数分の描画が終わったら終了

		*width = total_width;
		*height = total_height;
		*xbytes = total_xbytes;
	} else {
		//描画情報の取得
		ret = DT_GetTextRect(h, (DT16_ushort *)ucs_str, len, &rct, NULL, &dt_txtinfo);
		if (ret != DT_SUCCESS) {
			gdi_fontapi_errMsg(ret);
			goto DESTROY_AND_EXIT;
		}

		*width = dt_txtinfo.bmpwidth;	/* pgr0351 */
		*height = dt_txtinfo.bmpheight;	/* pgr0351 */
		*xbytes = (isBitmapFont) ? (dt_txtinfo.xbytes * 8) * sizeof(unsigned short) : 0;	/* pgr0351 */
	}

FINALLY:
	sig_sem(ID_FONTAPI_SEM);
	return ret;

DESTROY_AND_EXIT:  /* 異常終了 */
	goto FINALLY;
}


VGPath gdi_fontapi_createFontPath(const FONT_STYLE *style, const USHORT *ucs_str, int len, FONT_DRAW_INFO *draw_info)
{
	VGPath		return_handle = VG_INVALID_HANDLE;
	DT_RECT		rct = { { 0,0 },{ 0,0 } };
	DT32_int	ret = 0;
	VGfloat		adjustX = 0.0f;
	VGfloat		adjustY = 0.0f;
	int			size_Y;
	int			draw_height = 0;
	int			rct_y = 0;
	int			lineUnderflow = 0;
	int			bmpheight = 0;
	int			rct_hw_vy = 0;
	GDI_ERRCODE err = GDI_NO_ERROR;

	if ((NULL == style) || (NULL == ucs_str) || (NULL == draw_info)) {
		return VG_INVALID_HANDLE;
	}

	/* 文字数チェック */
	if (len <= 0) goto DESTROY_AND_EXIT;

	//フォントパスの初期化
	return_handle = vgCreatePath(VG_PATH_FORMAT_STANDARD, LOCAL_VGPATH_DATATYPE, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

	if ((return_handle == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
		goto DESTROY_AND_EXIT;
	}

	//フォントパス生成
	{
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
		vgLoadIdentity();

		ret = DT_RasterOVGPath(hOvg, (DT16_ushort *)ucs_str, len, &return_handle);
		if (ret != DT_SUCCESS) {
			gdi_fontapi_errMsg(ret);
			if (ret < 0) {
				goto DESTROY_AND_EXIT;
			}
		}
	}

	//描画情報の取得
	ret = DT_GetTextRect(hOvg, (DT16_ushort *)ucs_str, len, &rct, NULL, &dt_txtinfo);
	if (ret != DT_SUCCESS) {
		gdi_fontapi_errMsg(ret);
		if (ret < 0) {
			goto DESTROY_AND_EXIT;
		}
	}

	//位置の調整
	adjustX = (VGfloat)((style->righttoleft) ? -rct.hw.vx : 0);
	adjustY = (VGfloat)(-rct.xy.y);

	bmpheight = dt_txtinfo.bmpheight;
	rct_y = -rct.xy.y;
	draw_height = rct.hw.vy + rct_y;
	lineUnderflow = (draw_height < bmpheight) ? (bmpheight - draw_height) : 0;
	rct_hw_vy = rct.hw.vy;

	//全角文字(フォントサイズ：デフォルト)の場合
	size_Y = (int)style->size_y;
	if ((size_Y == bmpheight) && (24 == bmpheight)) {
		bmpheight += 10;
		rct_hw_vy += 10;
		adjustY += 3;
	}


	//仮想基点への移動
	if ((0 != adjustX) || (0 != adjustY)) {
		VGPath tmppath = vgCreatePath(VG_PATH_FORMAT_STANDARD, LOCAL_VGPATH_DATATYPE, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
		if ((tmppath == VG_INVALID_HANDLE) || (vgGetError() != GDI_NO_ERROR)) {
			goto DESTROY_AND_EXIT;
		}
		vgAppendPath(tmppath, return_handle);
		if (vgGetError() != GDI_NO_ERROR) {
			return_handle = VG_INVALID_HANDLE;
			goto DESTROY_AND_EXIT;
		}
		vgLoadIdentity();
		vgTranslate(adjustX, adjustY);
		vgClearPath(return_handle, VG_PATH_CAPABILITY_ALL);
		vgTransformPath(return_handle, tmppath);
		vgDestroyPath(tmppath);
	}


	draw_info->width = dt_txtinfo.bmpwidth;
	draw_info->height = rct_hw_vy;
	draw_info->lineUnderflow = lineUnderflow;
	draw_info->bmpwidth = dt_txtinfo.bmpwidth;
	draw_info->bmpheight = bmpheight;


FINALLY:
	return return_handle;

DESTROY_AND_EXIT:  /* 異常終了 */
	return_handle = VG_INVALID_HANDLE;
	goto FINALLY;
}


/*------------------------------------------------------------------------------*/
/**
@fn           gdi_fontapi_get_path
@brief        文字列イメージの取得（OpenVGのパスデータ）
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@retval       VGPathのハンドル（異常終了時はVG_INVALID_HANDLE）
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2011/9/5 新規作成
              2012/2/13 RTOL_PATH_ON_LEFT_OF_ORIGINの定義追加と共に全体的に整理
*/
/*------------------------------------------------------------------------------*/
VGPath gdi_fontapi_get_path(const FONT_STYLE *style, const USHORT *ucs_str, int len, FONT_DRAW_INFO *pdraw_info)
{
	VGPath		return_handle = VG_INVALID_HANDLE;
	VGPath		work_handle = VG_INVALID_HANDLE;
	VGPath		tmppath = VG_INVALID_HANDLE;
	DT_RECT		rct = {{0,0}, {0,0}};
	DT32_int	ret = 0;
	DT16_ushort	writedir = 0;
	USHORT		work_str[DT_MAX_STRING_LENGTH] = { 0 };

	int			draw_height = 0;
	int			rct_y = 0;
	GDI_ERRCODE err = GDI_NO_ERROR;

	if ((NULL == style) || (NULL == ucs_str) || (NULL == pdraw_info)) {
		return VG_INVALID_HANDLE;
	}

	wai_sem(ID_FONTAPI_SEM);

	//フォントスタイルの設定
	writedir = (DT16_ushort)((style->righttoleft) ? DT_RIGHTTOLEFT : DT_LEFTTORIGHT);	/* pgr0247	*/
	{
		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_SIZEX, style->size_x);
		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_SIZEY, style->size_y);
//		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_IS_BOLD, style->bold);			/* DigiTypeのDT_OUTLINE_MODEでは不対応 */
//		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_IS_ITALIC, style->italic);		/* 同上（DigiType API仕様確認必要） */
//		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_IS_UNDERLINE, style->underline);	/* 同上（DigiType API仕様確認必要） */
//		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_IS_STRIKE, style->strike);		/* 同上（DigiType API仕様確認必要） */
		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_SPACING, style->spacing);
		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_WRITEDIR, writedir);
		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_F_EDGE, DT_STYLE_OUTLINE);

		if (ret != DT_SUCCESS) {
			gdi_fontapi_errMsg(ret);
			goto DESTROY_AND_EXIT;
		}
	}

	if (DT_MAX_STRING_LENGTH <= len) {
		//DigiTypeの最大文字数(50文字)を超えていた場合
		int total_copylen = 0;
		FONT_DRAW_INFO draw_info;
		pdraw_info->width = 0;
		pdraw_info->height = 0;
		pdraw_info->lineUnderflow = 0;
		pdraw_info->bmpwidth = 0;
		pdraw_info->bmpheight = 0;
		//フォントパスの初期化
		return_handle = vgCreatePath(VG_PATH_FORMAT_STANDARD, LOCAL_VGPATH_DATATYPE, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

		if ((return_handle == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
			goto DESTROY_AND_EXIT;
		}

		//複数回gdi_fontapi_createFontPathを呼び出し、パスを結合する
		do {
			int max_str = DT_MAX_STRING_LENGTH - 1;		//NULL含み50文字なので-1しておく
			int remain_str = len - total_copylen;		//残り文字数
			int copylen = (max_str < remain_str) ? max_str : remain_str;

			//文字列をワークにコピーする
			int index;
			for (index = 0; index < copylen; index++) {
				work_str[index] = ucs_str[total_copylen + index];
			}

			work_str[copylen] = 0x00;	//NULL終端

			work_handle = gdi_fontapi_createFontPath(style, work_str, copylen, &draw_info);	//パスの生成
			if (work_handle == VG_INVALID_HANDLE) {
				goto DESTROY_AND_EXIT;
			}

			//パスの結合
			if (0 < pdraw_info->width) {
				//2回目以降はX方向の描画開始位置をずらし、vgAppendPathする
				tmppath = vgCreatePath(VG_PATH_FORMAT_STANDARD, LOCAL_VGPATH_DATATYPE, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
				if ((tmppath == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
					goto DESTROY_AND_EXIT;
				}
				vgAppendPath(tmppath, work_handle);
				if (vgGetError() != VG_NO_ERROR) {
					goto DESTROY_AND_EXIT;
				}
				vgLoadIdentity();
				vgTranslate((VGfloat)pdraw_info->width, 0.0f);
				vgClearPath(work_handle, VG_PATH_CAPABILITY_ALL);
				vgTransformPath(work_handle, tmppath);
				vgDestroyPath(tmppath);
			}
			vgAppendPath(return_handle, work_handle);
			if (vgGetError() != VG_NO_ERROR) {
				goto DESTROY_AND_EXIT;
			}
			vgDestroyPath(work_handle);

			pdraw_info->width += draw_info.width;
			pdraw_info->height = draw_info.height = (pdraw_info->height < draw_info.height) ? draw_info.height : pdraw_info->height;
			pdraw_info->lineUnderflow = (pdraw_info->lineUnderflow < draw_info.lineUnderflow) ? draw_info.lineUnderflow : pdraw_info->lineUnderflow;
			pdraw_info->bmpwidth += draw_info.bmpwidth;
			pdraw_info->bmpheight = (pdraw_info->bmpheight < draw_info.bmpheight) ? draw_info.bmpheight : pdraw_info->bmpheight;

			//処理した文字数を更新
			total_copylen += copylen;
		} while (total_copylen < len);	//文字数分の描画が終わったら終了
	} else {
		return_handle = gdi_fontapi_createFontPath(style, ucs_str, len, pdraw_info);
	}

FINALLY:
	sig_sem(ID_FONTAPI_SEM);

	return return_handle;

DESTROY_AND_EXIT:  /* 異常終了 */
	if (return_handle != VG_INVALID_HANDLE) {
		vgDestroyPath(return_handle);
		return_handle = VG_INVALID_HANDLE;
	}
	if (work_handle != VG_INVALID_HANDLE) {
		vgDestroyPath(work_handle);
		work_handle = VG_INVALID_HANDLE;
	}
	if (tmppath != VG_INVALID_HANDLE) {
		vgDestroyPath(tmppath);
		tmppath = VG_INVALID_HANDLE;
	}

	goto FINALLY;
}


/*------------------------------------------------------------------------------*/
/**
@fn           gdi_fontapi_CombineCharsToStrPath
@brief        文字列イメージの取得（OpenVGのパスデータ）(1文字ずつパスに追加していく)
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@retval       VGPathのハンドル（異常終了時はVG_INVALID_HANDLE）
@par          同期
@sa           [in][out] なし
@par          更新履歴:
2011/9/5 新規作成
2012/2/13 RTOL_PATH_ON_LEFT_OF_ORIGINの定義追加と共に全体的に整理
*/
/*------------------------------------------------------------------------------*/
static BOOL IsUseDescentArea(USHORT _str)
{
	int cmpStr = (int)_str;

	return (('Q' == cmpStr)
		||  ('g' == cmpStr)
		||  ('j' == cmpStr)
		||  ('p' == cmpStr)
		||  ('q' == cmpStr)
		||  ('y' == cmpStr));
}


VGPath gdi_fontapi_CombineCharsToStrPath(const FONT_STYLE *style, const USHORT *ucs_str, FONT_DRAW_INFO *draw_info)
{
	VGPath		return_handle = VG_INVALID_HANDLE;
	DT_RECT		rct = { { 0,0 },{ 0,0 } };
	DT32_int	ret = 0;
	DT16_ushort	writedir = 0;
	DT32_int	len = 0;
	VGfloat		adjustX = 0.0f;
	VGfloat		adjustY = 0.0f;
	VGfloat		totalWidth = 0.0f;
	USHORT		work_str[2] = { 0,0 };
	int			draw_height = 0;
	int			rct_y = 0;
	int			lineUnderflow;
	int			bmpheight;
	BOOL		bIsUseDescent = FALSE;
	VGPath		work_handle = VG_INVALID_HANDLE;
	VGPath		tmppath = VG_INVALID_HANDLE;

	if ((NULL == style) || (NULL == ucs_str)) {
		return VG_INVALID_HANDLE;
	}

	wai_sem(ID_FONTAPI_SEM);

	//フォントパスの初期化
	return_handle = vgCreatePath(VG_PATH_FORMAT_STANDARD, LOCAL_VGPATH_DATATYPE, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);

	if ((return_handle == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
		goto DESTROY_AND_EXIT;
	}

	writedir = (DT16_ushort)((style->righttoleft) ? DT_RIGHTTOLEFT : DT_LEFTTORIGHT);	/* pgr0247	*/

	/* 文字数カウント */
	for (len = 0; ucs_str[len]; len++) {

		//1文字取り出し
		work_str[0] = ucs_str[len];

		bIsUseDescent = IsUseDescentArea(work_str[0]);

		//フォントスタイルの設定
		{
			ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_SIZEX, (bIsUseDescent) ? (style->size_x - 2) : style->size_x);
			ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_SIZEY, (bIsUseDescent) ? (style->size_y - 2) : style->size_y);
			//		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_IS_BOLD, style->bold);			/* DigiTypeのDT_OUTLINE_MODEでは不対応 */
			//		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_IS_ITALIC, style->italic);		/* 同上（DigiType API仕様確認必要） */
			//		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_IS_UNDERLINE, style->underline);	/* 同上（DigiType API仕様確認必要） */
			//		ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_IS_STRIKE, style->strike);		/* 同上（DigiType API仕様確認必要） */
			ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_SPACING, style->spacing);
			ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_WRITEDIR, writedir);
			ret |= DT_SetFontStyle(hOvg, DT_FSTYLE_F_EDGE, DT_STYLE_OUTLINE);

			if (ret != DT_SUCCESS) {
				gdi_fontapi_errMsg(ret);
				goto DESTROY_AND_EXIT;
			}
		}

		//パスを生成
		work_handle = vgCreatePath(VG_PATH_FORMAT_STANDARD, LOCAL_VGPATH_DATATYPE, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
		if ((work_handle == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
			goto DESTROY_AND_EXIT;
		}

		//フォントパス生成
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
		vgLoadIdentity();
		ret = DT_RasterOVGPath(hOvg, (DT16_ushort *)work_str, 1, &work_handle);
		if (ret != DT_SUCCESS) {
			gdi_fontapi_errMsg(ret);
			goto DESTROY_AND_EXIT;
		}

		//描画情報の取得
		ret = DT_GetTextRect(hOvg, (DT16_ushort *)work_str, 1, &rct, NULL, &dt_txtinfo);
		if (ret != DT_SUCCESS) {
			gdi_fontapi_errMsg(ret);
			goto DESTROY_AND_EXIT;
		}

		//位置の調整
		adjustX = (VGfloat)totalWidth;
		adjustY = (VGfloat)(-rct.xy.y);

		//縦位置の微調整
		if (bIsUseDescent) {
			int org_width = (int)(style->size_x * 0.5f);	/* pgr0247 意図通りのキャスト */
			adjustX += (dt_txtinfo.bmpwidth < org_width) ? (org_width - dt_txtinfo.bmpwidth) * 0.5f : 0;
			adjustY += 3.0f;	//下に突き出る文字は位置を上に2pt程度ずらす
		}

		//仮想基点への移動
		if ((0 != adjustX) || (0 != adjustY)) {
			tmppath = vgCreatePath(VG_PATH_FORMAT_STANDARD, LOCAL_VGPATH_DATATYPE, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
			if ((tmppath == VG_INVALID_HANDLE) || (vgGetError() != VG_NO_ERROR)) {
				goto DESTROY_AND_EXIT;
			}
			vgAppendPath(tmppath, work_handle);
			if (vgGetError() != VG_NO_ERROR) {
				goto DESTROY_AND_EXIT;
			}
			vgLoadIdentity();
			vgTranslate(adjustX , adjustY);
			vgClearPath(work_handle, VG_PATH_CAPABILITY_ALL);
			vgTransformPath(work_handle, tmppath);
			vgDestroyPath(tmppath);
		}
		vgAppendPath(return_handle, work_handle);
		vgDestroyPath(work_handle);
		//totalWidth += rct.hw.vx;
		//totalWidth += dt_txtinfo.bmpwidth;
		totalWidth += (style->size_x * 0.5f);
	}

	//元々のサイズを返す
	ret = DT_GetTextRect(hOvg, (DT16_ushort *)ucs_str, len, &rct, NULL, &dt_txtinfo);

	rct_y = -rct.xy.y;
	draw_height = rct.hw.vy + rct_y;
	bmpheight = dt_txtinfo.bmpheight;
	lineUnderflow = (draw_height < bmpheight) ? (bmpheight - draw_height) : 0;

	if (NULL != draw_info) {
		draw_info->width = (UINT)(style->size_x * 0.5f * len);	/* pgr0247 意図通りのキャスト */
		draw_info->height = style->size_y;
		draw_info->lineUnderflow = lineUnderflow;
		draw_info->bmpwidth = dt_txtinfo.bmpwidth;
		draw_info->bmpheight = bmpheight;
	}

FINALLY:
	sig_sem(ID_FONTAPI_SEM);

	return return_handle;

DESTROY_AND_EXIT:  /* 異常終了 */
	if (VG_INVALID_HANDLE != return_handle) {
		vgDestroyPath(return_handle);
		return_handle = VG_INVALID_HANDLE;
	}

	if (VG_INVALID_HANDLE != work_handle) {
		vgDestroyPath(work_handle);
		work_handle = VG_INVALID_HANDLE;
	}

	if (VG_INVALID_HANDLE != tmppath) {
		vgDestroyPath(tmppath);
		tmppath = VG_INVALID_HANDLE;
	}
	
	goto FINALLY;
}

/*------------------------------------------------------------------------------*/
/**
@fn           CountLineFeedCode
@brief        文字列内の改行コードをチェック
@param[in]    ucs_str UCS-2文字列（0終端）
@retval       
@par          同期
@sa           [in][out] なし
@par          更新履歴:
2018/1/11 新規作成
*/
/*------------------------------------------------------------------------------*/
int CountLineFeedCode(USHORT* _str)
{
    unsigned short    ret = 0;
	DT32_int len = 0;
	
	if (_str == NULL) return 0;

	for (len = 0; _str[len]; len++) {
        if (_str[len] == '\n' || _str[len] == '\r') {
			if (_str[len] == '\r' && _str[len + 1] == '\n') {
				len++;
			}
            ret++;
        }
    }

    return ret;
}



///////////////////////////////////////////////////////////////////////////////////////////////
//以下、削除予定(HWIN_***で使用されているため、一旦削除保留。あとで消す)

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_rect
@brief        文字列描画に必要なイメージバッファのサイズの取得
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@param[out]   width   文字列イメージの横サイズ（ドット数）
@param[out]   height  文字列イメージの縦サイズ（ドット数）
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2010/10/21 新規作成
*/
/*------------------------------------------------------------------------------*/
int  font_service_get_rect(
    const  FONT_STYLE  *style,
    const  unsigned short  *ucs_str,
    unsigned short  *width,
    unsigned short  *height
){
	return -1;
}

/*------------------------------------------------------------------------------*/
/**
@fn           font_service_get_exact_rect
@brief        文字列イメージの描画サイズの取得
@param[in]    style   文字スタイル
@param[in]    ucs_str UCS-2文字列（0終端）
@param[out]   width   文字列イメージの横サイズ（ドット数）
@param[out]   height  文字列イメージの縦サイズ（ドット数）
@retval       <0 異常終了
@par          同期
@sa           [in][out] なし
@par          更新履歴:
              2010/11/13 新規作成
*/
/*------------------------------------------------------------------------------*/
int  font_service_get_exact_rect(
    const  FONT_STYLE  *style,
    const  unsigned short  *ucs_str,
    unsigned short  *width,
    unsigned short  *height
){
	return -1;

}

