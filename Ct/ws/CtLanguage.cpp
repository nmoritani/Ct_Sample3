#include "CtLanguage.h"
#include "CtAplParam.h"

/*
    AplParamの言語設定に応じたLANGUAGE_ID取得
*/
LANGUAGE_ID CtLanguage::getLanguageID()
{
	int lang = CtAplParam::getLanguage();

	return getLanguageID(lang);
}

/*
    引数のAplParamの言語設定に応じたLANGUAGE_ID取得
*/
LANGUAGE_ID CtLanguage::getLanguageID(int lang)
{
	// AplParam -> LANGUAGE_IDに変換して値を返す
	switch (lang) {
	case APL_SYS_PARAM_LANGUAGE_ENGLISH:	return LANGUAGE_ID_UE;
	case APL_SYS_PARAM_LANGUAGE_SCHINESE:	return LANGUAGE_ID_SC;
	case APL_SYS_PARAM_LANGUAGE_SPAIN:		return LANGUAGE_ID_SP;
	case APL_SYS_PARAM_LANGUAGE_FRENCH:		return LANGUAGE_ID_FR;
	case APL_SYS_PARAM_LANGUAGE_GERMAN:		return LANGUAGE_ID_GE;
	case APL_SYS_PARAM_LANGUAGE_ITALIA:		return LANGUAGE_ID_IT;
	case APL_SYS_PARAM_LANGUAGE_RUSSIA:		return LANGUAGE_ID_RU;
	case APL_SYS_PARAM_LANGUAGE_DUTCH:		return LANGUAGE_ID_DU;
	case APL_SYS_PARAM_LANGUAGE_TURKISH:	return LANGUAGE_ID_TU;
	case APL_SYS_PARAM_LANGUAGE_SWEDEN:		return LANGUAGE_ID_SW;
	case APL_SYS_PARAM_LANGUAGE_POLAND:		return LANGUAGE_ID_PO;
	case APL_SYS_PARAM_LANGUAGE_CZECH:		return LANGUAGE_ID_CZ;
	case APL_SYS_PARAM_LANGUAGE_HUNGARIAN:	return LANGUAGE_ID_HU;
	case APL_SYS_PARAM_LANGUAGE_JAPANESE:	return LANGUAGE_ID_JA;
	default:								break;
	}

	return LANGUAGE_ID_UE;
}

/*
引数のStringIDの言語設定に応じたLANGUAGE_ID取得
*/
LANGUAGE_ID CtLanguage::getLanguageID(GDI_STRING_ID STR_ID)
{
	switch (STR_ID) {
	case STR_ID_ENGLISH:		return LANGUAGE_ID_UE;
	case STR_ID_JAPANESE:		return LANGUAGE_ID_JA;
	case STR_ID_CHINESE:		return LANGUAGE_ID_SC;
	case STR_ID_SPANISH:		return LANGUAGE_ID_SP;
	case STR_ID_FRENCH:		    return LANGUAGE_ID_FR;
	case STR_ID_GERMAN:			return LANGUAGE_ID_GE;
	case STR_ID_ITALIAN:		return LANGUAGE_ID_IT;
	case STR_ID_RUSSIAN:		return LANGUAGE_ID_RU;
	case STR_ID_DUTCH:		    return LANGUAGE_ID_DU;
	case STR_ID_TURKISH:		return LANGUAGE_ID_TU;
	case STR_ID_SWEDISH:		return LANGUAGE_ID_SW;
	case STR_ID_POLISH:			return LANGUAGE_ID_PO;
	case STR_ID_CZECH:			return LANGUAGE_ID_CZ;
	case STR_ID_HUNGARIAN:		return LANGUAGE_ID_HU;
	default:					break;
	}
	return getLanguageID();
}

/*
    引数langに応じたFONT_LOCALE取得
*/
FONT_LOCALE CtLanguage::getLocale(LANGUAGE_ID lang)
{
	switch(lang){
	case LANGUAGE_ID_JA:	return LOCALE_JP;	/* 日本語 */
	case LANGUAGE_ID_SC:	return LOCALE_SC;	/* 中国語（簡体字） */
	case LANGUAGE_ID_TC:	return LOCALE_TC;	/* 中国語（繁体字） */
	case LANGUAGE_ID_TW:	return LOCALE_TC;	/* 中国語（繁体字） */
	//case LANGUAGE_ID_KO:	return LOCALE_KR;	/* 韓国語 */
	//case LANGUAGE_ID_AR:	return LOCALE_AR;	/* アラビア語 */
	//case LANGUAGE_ID_TH:	return LOCALE_TH;	/* タイ語 */
	//case LANGUAGE_ID_HI:	return LOCALE_HI	/* ヒンディー語 */
	default:				break;
	}

	return LOCALE_EN;
}

