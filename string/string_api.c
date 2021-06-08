

#ifdef WIN32_GUI_SIM
#else
# include "SysIf.h"
#endif

#include "language_id.h"	/*多言語ID（共通）*/
//#include "str_id.h"	/*文言ID（共通）*/
#include "gdi_string.h"	/*文言ID（共通）*/
#include "string_sub.h"	/*文言ID（共通）*/
#include "string_api.h"	/*文言ID（共通）*/
#include "fontapi.h"

static LANG_INFO lang_info_list [] =
  {
	{ false, ".ja_string", str_table_ja },  /* [0]	日本語					*/
	{ false, ".en_string", str_table_en }, 	/* [1]	英語			PAL		*/
	{ false, ".ue_string", str_table_ue }, 	/* [2]	英語			NTSC	*/
	{ false, ".ge_string", str_table_ge }, 	/* [3]	独語					*/
	{ false, ".fr_string", str_table_fr }, 	/* [4]	仏語			PAL		*/
//	{ false, ".ca_string", str_table_ca }, 	/* [5]	仏語			NTSC	*/
	{ false, ".it_string", str_table_it }, 	/* [6]	伊語					*/
	{ false, ".sp_string", str_table_sp }, 	/* [7]	西語			PAL		*/
//	{ false, ".us_string", str_table_us }, 	/* [8]	西語			NTSC	*/
	{ false, ".du_string", str_table_du }, 	/* [9]	蘭語					*/
	{ false, ".sw_string", str_table_sw }, 	/* [10]	スウェーデン語			*/
	{ false, ".po_string", str_table_po }, 	/* [11]	ポーランド語			*/
	{ false, ".ru_string", str_table_ru }, 	/* [12]	露語					*/
//	{ false, ".ar_string", str_table_ar }, 	/* [13]	アラビア語				*/
//	{ false, ".pe_string", str_table_pe }, 	/* [14]	ペルシャ語				*/
//	{ false, ".ko_string", str_table_ko }, 	/* [15]	韓国語					*/
	{ false, ".sc_string", str_table_sc }, 	/* [16]	簡体語					*/
	{ false, ".tc_string", str_table_tc }, 	/* [17]	繁体語			PAL		*/
	{ false, ".tw_string", str_table_tw }, 	/* [18]	繁体語			NTSC	*/
	{ false, ".cz_string", str_table_cz }, 	/* [19]	チェコ語				*/
//	{ false, ".th_string", str_table_th }, 	/* [20]	タイ語					*/
//	{ false, ".hi_string", str_table_hi }, 	/* [21]	ヒンディ語 				*/
	{ false, ".je_string", str_table_je }, 	/* [22]	英語(日本向け)	NTSC	*/
	{ false, ".tu_string", str_table_tu }, 	/* [23]	トルコ語                */
	{ false, ".hu_string", str_table_hu },	/* [24]	ハンガリー語            */
//	{ false, ".pt_string", str_table_pt }	/* [25]	ポルトガル語            */
  };

// 言語情報取得マクロ
#define GET_LANG_INFO(lang_id) (&(lang_info_list[(lang_id)]))

#ifdef WIN32_GUI_SIM
#else
/**
 * @brief  文字列データのロード
 * @param  language_id   言語ＩＤ
 * @return なし
 */
static void SLIB_load_string (LANGUAGE_ID language_id)
{
  LANG_INFO *langInfo;

  // 引数チェック
  if(language_id >= LANGUAGE_ID_MAX)
	{
	  return;
	}

  langInfo = GET_LANG_INFO(language_id);
  if(langInfo->is_load == TRUE)
	{
	  return;   // 既にロード済み
	}

  // 全ロードフラグをFALSEにする
  {
	INT i;

	for(i = 0; i < LANGUAGE_ID_MAX; i++)
	  {
		GET_LANG_INFO(i)->is_load = false;
	  }
  }
  
  if(SYS_Section_Load(langInfo->section_name) == SYS_OK)
	{
	  // ロードに成功したらフラグを立てる
	  langInfo->is_load = true;
	}
}
#endif

unsigned short* GDI_GetString ( LANGUAGE_ID language_id, unsigned short string_id )
{
  unsigned short* str;
  LANG_INFO *langInfo;

  // 引数チェック
  if( (language_id >= LANGUAGE_ID_MAX) || (string_id >= (GDI_STRING_ID)STR_ID_MAX_SIZE) )
	{
	  return 0;
	}

#ifdef WIN32_GUI_SIM
#else
	// 文字列のロードチェック＆ロード
	SLIB_load_string(language_id);
#endif

  langInfo = &lang_info_list[language_id];
//  if(langInfo->is_load == false){
//	  return null;  // 未ロードデータ
//  }

  str = (unsigned short*)(langInfo->string_table[string_id]);

  return str;
}

