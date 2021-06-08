#include "CtLanguage.h"
#include "CtAplParam.h"

/*
    AplParam�̌���ݒ�ɉ�����LANGUAGE_ID�擾
*/
LANGUAGE_ID CtLanguage::getLanguageID()
{
	int lang = CtAplParam::getLanguage();

	return getLanguageID(lang);
}

/*
    ������AplParam�̌���ݒ�ɉ�����LANGUAGE_ID�擾
*/
LANGUAGE_ID CtLanguage::getLanguageID(int lang)
{
	// AplParam -> LANGUAGE_ID�ɕϊ����Ēl��Ԃ�
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
������StringID�̌���ݒ�ɉ�����LANGUAGE_ID�擾
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
    ����lang�ɉ�����FONT_LOCALE�擾
*/
FONT_LOCALE CtLanguage::getLocale(LANGUAGE_ID lang)
{
	switch(lang){
	case LANGUAGE_ID_JA:	return LOCALE_JP;	/* ���{�� */
	case LANGUAGE_ID_SC:	return LOCALE_SC;	/* ������i�ȑ̎��j */
	case LANGUAGE_ID_TC:	return LOCALE_TC;	/* ������i�ɑ̎��j */
	case LANGUAGE_ID_TW:	return LOCALE_TC;	/* ������i�ɑ̎��j */
	//case LANGUAGE_ID_KO:	return LOCALE_KR;	/* �؍��� */
	//case LANGUAGE_ID_AR:	return LOCALE_AR;	/* �A���r�A�� */
	//case LANGUAGE_ID_TH:	return LOCALE_TH;	/* �^�C�� */
	//case LANGUAGE_ID_HI:	return LOCALE_HI	/* �q���f�B�[�� */
	default:				break;
	}

	return LOCALE_EN;
}

