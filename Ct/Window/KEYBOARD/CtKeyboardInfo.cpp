/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/*******************************************************************************
    インクルードファイル
*******************************************************************************/
#include "CtKeyboardInfo.h"
#include "CtLanguage.h"

/*******************************************************************************
  定数の定義
*******************************************************************************/

CtKeyboardInfo::CtKeyboardInfoItem CtKeyboardInfo::Info[] = {
#include "KeyboardInfo.def"
};

CtKeyboardInfo::CtKeyboardInfoItem* CtKeyboardInfo::getKeyboardInfo(CtWindowID id)
{
	for (unsigned int i = 0; i < sizeof(Info) / sizeof(CtKeyboardInfoItem); i++) {
		if (id == Info[i].WindowId) {
			return &Info[i];
		}
	}
	return NULL;
}

/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
