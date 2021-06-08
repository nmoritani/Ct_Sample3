/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/*******************************************************************************
    インクルードファイル
*******************************************************************************/
#include "CtMenuInfo.h"
#include "CtLanguage.h"
#include "CtWindowDecorate.h"

/*******************************************************************************
  定数の定義
*******************************************************************************/

CtMenuInfo::CtMenuButtonInfo CtMenuInfo::ButtonInfo[] = {
#include "MenuButtonInfo.def"
};
CtMenuInfo::CtMenuWindowInfo CtMenuInfo::WindowInfo[] = {
#include "MenuWindowInfo.def"
};


CtMenuInfo::CtMenuButtonInfo* CtMenuInfo::getButtonInfoAll()
{
	return ButtonInfo;
}
CtMenuInfo::CtMenuButtonInfo* CtMenuInfo::getButtonInfo(int ButtonId)
{
	if (0 >= ButtonId || ButtonId >= MenuButtonId_Max) {
		return NULL;
	}
	return &ButtonInfo[ButtonId - 1];
}
CtMenuInfo::CtMenuExclution* CtMenuInfo::getButtonExclution(int ButtonId)
{
	CtMenuButtonInfo* Info = getButtonInfo(ButtonId);
	if (Info == NULL) {
		return NULL;
	}
	return &Info->exclution;
}
CtMenuInfo::CtMenuActionInfo* CtMenuInfo::getButtonAction(int ButtonId)
{
	CtMenuButtonInfo* Info = getButtonInfo(ButtonId);
	if (Info == NULL) {
		return NULL;
	}
	return &Info->action;
}

CtMenuInfo::CtMenuWindowInfo* CtMenuInfo::getWindowInfo(CtWindowID id)
{
	for (int i = 0; i < sizeof(WindowInfo) / sizeof(CtMenuWindowInfo); i++) {  /*pgr0360*/
		if (id == WindowInfo[i].id) {
			return &WindowInfo[i];
		}
	}
	return NULL;
}
CtMenuInfo::CtMenuWindowTitle* CtMenuInfo::getWindowTitle(CtWindowID id)
{
	CtMenuWindowInfo* Info = getWindowInfo(id);
	if (Info == NULL) {
		return NULL;
	}
	return &Info->title;
}
CtMenuInfo::CtMenuWindowChild* CtMenuInfo::getWindowChild(CtWindowID id)
{
	CtMenuWindowInfo* Info = getWindowInfo(id);
	if (Info == NULL) {
		return NULL;
	}
	return &Info->child;
}
CtMenuInfo::CtMenuWindowType CtMenuInfo::getWindowType(CtWindowID id)
{
	CtMenuWindowInfo* Info = getWindowInfo(id);
	if (Info == NULL) {
		return WINDOW_TYPE_MAX;
	}

	return Info->type;
}



void CtMenuInfo::getMenuSize(CtWindowID id, short& label, short& value ,bool& bArrow)
{
	short width;
	CtFontSet fSetL = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	fSetL.setSize(MENU_LABEL_SIZE);
	CtFontSet fSetV = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);
	fSetV.setSize(MENU_LABEL_SIZE);

	CtMenuWindowChild* pChildLabel = getWindowChild(id);
	if (pChildLabel == NULL)return;
	
	for (unsigned int i = 0; i < pChildLabel->num; i++) {
		CtMenuButtonInfo* pInfoLabel = getButtonInfo(pChildLabel->id[i]);

		if (MENU_LABEL_MIN_SIZA > label) {
			label = MENU_LABEL_MIN_SIZA;
		}
		width = getStringSize(getButtonString(pInfoLabel), fSetL);

		if (width > label) {
			label = width;
		}
		CtMenuWindowInfo* pWindowInfo = getWindowInfo(pInfoLabel->action.WindowID);

		if (pWindowInfo != NULL) {
			switch (pWindowInfo->type) {
			case WINDOW_TYPE_LIST:
			case WINDOW_TYPE_CHECKLIST:
			//case WINDOW_TYPE_POPLIST:
				bArrow = true;
				break;
			default:
				break;
			}
		}

		if (pInfoLabel->type & MenuButton_Value) {
			/* 最小値設定 */
			if (MENU_VALUE_MIN_SIZA > value) {
				value = MENU_VALUE_MIN_SIZA;
			}
			/* すでに最大値だった場合は確認行わない */
			if (MENU_VALUE_MAX_SIZA <= value) {
				continue;
			}
			/* サイズ指定がある場合はそれに従う */
			switch (pInfoLabel->value.type & ValueType_SizeMask){
			case ValueType_SizeMAX:
				value = MENU_VALUE_MAX_SIZA;
				continue;
			case ValueType_Size150:
				if (150 > value) {
					value = 150;
				}
				continue;
			case ValueType_Size200:
				if (200 > value) {
					value = 200;
				}
				continue;
			default:
				break;
			}
			if (pWindowInfo != NULL) {
				for (unsigned int i = 0; i < pWindowInfo->child.num; i++) {
					CtMenuButtonInfo* pInfoValue = getButtonInfo(pWindowInfo->child.id[i]);

					width = getStringSize(getButtonString(pInfoValue), fSetV);

					if ((pInfoLabel->value.type & ValueType_SizeMask) == ValueType_SizePlus) {
						width += getStringSize(", ...", fSetV);
					}

					if (width > value) {
						value = width;
						if (MENU_VALUE_MAX_SIZA < value) {
							break;
						}
					}
				}
			}
			if (MENU_VALUE_MAX_SIZA < value) {
				value = MENU_VALUE_MAX_SIZA;
			}
		}
	}
}

short CtMenuInfo::getStringSize(GDI_STRING_ID id)
{
	CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor::White);
	fSet.setSize(MENU_LABEL_SIZE);

	return getStringSize(id, fSet);
}
short CtMenuInfo::getStringSize(GDI_STRING_ID id, CtFontSet fSet)
{
	CtSize Size;

	if (fSet.getLanguageId() == LANGUAGE_ID_NONE)
		fSet.setLanguageId(CtLanguage::getLanguageID(id));
	fSet.getStringSize(Size, id);

	return Size.width;
}

short CtMenuInfo::getStringSize(const char* str)
{
	CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor::White);
	fSet.setSize(MENU_LABEL_SIZE);

	return getStringSize(str, fSet);
}
short CtMenuInfo::getStringSize(const char* str, CtFontSet fSet)
{
	CtSize Size;

	if (fSet.getLanguageId() == LANGUAGE_ID_NONE)
		fSet.setLanguageId(CtLanguage::getLanguageID());
	fSet.getStringSize(Size, str);

	return Size.width;
}

short CtMenuInfo::getStringSize(const unsigned short* str)
{
	CtFontSet fSet = CtFontSet(FontTypeNormal, CtColor::White);
	fSet.setSize(MENU_LABEL_SIZE);

	return getStringSize(str, fSet);
}
short CtMenuInfo::getStringSize(const unsigned short* str, CtFontSet fSet)
{
	CtSize Size;

	if (fSet.getLanguageId() == LANGUAGE_ID_NONE)
		fSet.setLanguageId(CtLanguage::getLanguageID());
	fSet.getStringSize(Size, str);

	return Size.width;
}

LANGUAGE_ID CtMenuInfo::getLanguage(int value)
{
	if (value == -1) {
		return CtLanguage::getLanguageID();
	}
	else {
		return CtLanguage::getLanguageID(value);
	}

	return LANGUAGE_ID_UE;
}
LANGUAGE_ID CtMenuInfo::getLanguage(GDI_STRING_ID STR_ID)
{
	switch (STR_ID) {
	case STR_ID_LANGUAGE:
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

	return LANGUAGE_ID_NONE;
}

short CtMenuInfo::getHierarchy(CtWindowID id)
{
	switch (id & 0xFFFF0000) {
	case WindowCategory_MenuListTop:
		return 1;
	case WindowCategory_MenuList1st:
		return 2;
	case WindowCategory_MenuList2nd:
		return 3;
	case WindowCategory_MenuList3rd:
		return 4;
	case WindowCategory_MenuList4th:
		return 5;
	case WindowCategory_MenuList5rh:
		return 6;
	case WindowCategory_MenuListPop:
	case WindowCategory_MenuListCheck:
		return 0;
	default:
		break;
	}
	return 1;
}

bool CtMenuInfo::checkArrow(CtMenuButtonInfo* pButtonInfo)
{
	if (pButtonInfo == NULL)return false;

	CtMenuWindowInfo* pWindowInfo = getWindowInfo(pButtonInfo->action.WindowID);
	if (pWindowInfo == NULL)return false;

	switch (pWindowInfo->type){
	case WINDOW_TYPE_LIST:
	case WINDOW_TYPE_CHECKLIST:
	//case WINDOW_TYPE_POPLIST:
		return true;
	default:
		break;
	}

	return false;
}

int CtMenuInfo::getParamValue(int ParamID)
{
	int value = APL_PARAM_GET_DATA(ParamID);
	AplParamService::AplParamMainItem* pMainItem = APL_PARAM()->getParamState(ParamID);
	int size = 0;

	if (pMainItem != NULL) {
		size = pMainItem->size;
	}
	int mask = (1 << (size * 8 - 1));

	// Value 更新の場合はマイナス値が保存されているのでマイナス値に変換
	if (size != 4) {
		if (value & mask) {
			for (int i = 4; i > size; i--) {
				value = value | (0xFF << ((8 * (i - 1))));
			}
		}
	}
	return value;
}

const unsigned short* CtMenuInfo::getButtonString(CtMenuButtonInfo* pInfo)
{
	static unsigned short str[300];
	memset(str, 0, sizeof(str));

	if (pInfo == NULL) {
		convert_char_str_to_ushort_str(str, "None");
		return str;
	}

	GDI_STRING_ID str_id = pInfo->StringId;

	switch (str_id) {
	case STR_ID_JAPANESE:
		return GDI_GetString(LANGUAGE_ID_JA, str_id);
	case STR_ID_LANGUAGE:       // [S:00006]LANGUAGE
	case STR_ID_ENGLISH:        // [S:00045]ENGLISH
		return GDI_GetString(LANGUAGE_ID_UE, str_id);
	case STR_ID_CHINESE:        // [S:00048]中文
		return GDI_GetString(LANGUAGE_ID_SC, str_id);
	case STR_ID_SPANISH:        // [S:00047]SPANISH
		return GDI_GetString(LANGUAGE_ID_SP, str_id);
	case STR_ID_FRENCH:         // [S:00046]FRENCH
		return GDI_GetString(LANGUAGE_ID_FR, str_id);
	case STR_ID_GERMAN:         // [S:00051]GERMAN
		return GDI_GetString(LANGUAGE_ID_GE, str_id);
	case STR_ID_ITALIAN:        // [S:00052]ITALIAN
		return GDI_GetString(LANGUAGE_ID_IT, str_id);
	case STR_ID_RUSSIAN:        // [S:00059]RUSSIAN
		return GDI_GetString(LANGUAGE_ID_RU, str_id);
	case STR_ID_DUTCH:          // [S:00053]DUTCH
		return GDI_GetString(LANGUAGE_ID_DU, str_id);
	case STR_ID_TURKISH:        // [S:00057]TURKISH
		return GDI_GetString(LANGUAGE_ID_TU, str_id);
	case STR_ID_SWEDISH:        // [S:00054]SWEDISH
		return GDI_GetString(LANGUAGE_ID_SW, str_id);
	case STR_ID_POLISH:         // [S:00055]POLISH
		return GDI_GetString(LANGUAGE_ID_PO, str_id);
	case STR_ID_CZECH:          // [S:00056]CZECH
		return GDI_GetString(LANGUAGE_ID_CZ, str_id);
	case STR_ID_HUNGARIAN:      // [S:01196]HUNGARIAN
		return GDI_GetString(LANGUAGE_ID_HU, str_id);
	case STR_ID_MAX_SIZE:       // 文字列無し
	{
		if (pInfo->type & MenuButton_ParamLabel) {
			char dat[100] = { NULL };
			char str2[120] = { NULL };
			AplParamService::AplParamMainItem* AplParamItem = NULL;
			if ((AplParamItem = APL_PARAM()->getParamState(pInfo->value.id)) != NULL) {
				APL_PARAM_GET_DATA_AREA(pInfo->value.id, (unsigned char*)dat, AplParamItem->size);
				sprintf(str2, pInfo->str, dat);
			}
			convert_char_str_to_ushort_str(str, str2);
			return str;
		}
		convert_char_str_to_ushort_str(str, pInfo->str);
		return str;
	}
	default:
		return GDI_GetString(CtLanguage::getLanguageID(), str_id);
	}

	return str;
}
CtFontSet CtMenuInfo::getLabelFont(CtMenuButtonInfo* pInfo)
{
	CtFontSet fSet = CtFontSet(FontTypeBold_alignAuto, CtColor::White);
	fSet.setStrokeWidth(MENU_BOLD_SIZE);

	if (pInfo == NULL) { return fSet; }

	LANGUAGE_ID language = getLanguage(pInfo->StringId);

	if (language != LANGUAGE_ID_NONE)
		fSet.setLanguageId(language);

	return fSet;
}
CtFontSet CtMenuInfo::getValueFont(CtMenuButtonInfo* pInfo)
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);

	if (pInfo == NULL) { return fSet; }

	LANGUAGE_ID language = getLanguage(pInfo->StringId);

	if (language != LANGUAGE_ID_NONE)
		fSet.setLanguageId(language);

	return fSet;
}

bool CtMenuInfo::checkExit(CtWindowID id)
{
	CtMenuWindowInfo* pWindowInfo = getWindowInfo(id);
	if (pWindowInfo == NULL)return false;

	switch (pWindowInfo->type){
	case WINDOW_TYPE_CHECKLIST:
	case WINDOW_TYPE_POPLIST:
		return true;
	default:
		break;
	}
	return false;
}

CtColor CtMenuInfo::getMenuBackColor()
{
	bool bThumb = CtWindowDecorate::isThumbnail();
	unsigned char Transmittance = bThumb ? 235 : 178;
	CtColor color = CtColor(0, 0, 0, Transmittance);
	return color;
}

void CtMenuInfo::getParentId(CtWindowID Windowid, int& param, int& value)
{
	CtMenuWindowInfo* pWindowInfo = NULL;
	CtMenuButtonInfo* pButtonInfo = NULL;

	param = AplParamIdMax;
	value = 0;

	if ((pWindowInfo = getWindowInfo(Windowid)) == NULL)
		return;

	int ButtonId = pWindowInfo->title.id[pWindowInfo->title.num - 1];

	if ((pButtonInfo = getButtonInfo(ButtonId)) == NULL)
		return;

	param = pButtonInfo->exclution.id;
	value = pButtonInfo->exclution.value;
}


/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
