/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/*******************************************************************************
    インクルードファイル
*******************************************************************************/
#include "CtMenuInfoToggleDialog.h"

/*******************************************************************************
  定数の定義
*******************************************************************************/

CtMenuInfoToggleDialog::CtMenuToggleDialogInfo CtMenuInfoToggleDialog::Info[] = {
	/*{ Target WindowID             , Title STR_ID    } */
	{ WindowID_Menu_CLOCK_SETTING   , STR_ID_NO_10145 },
	{ WindowID_Menu_TC              , STR_ID_NO_10356 },
	{ WindowID_Menu_UB              , STR_ID_NO_10357 },
	{ WindowID_Menu_TIME_ZONESETTING, STR_ID_NO_10151 },
};

CtMenuInfoToggleDialog::CtMenuToggleDialogInfo* CtMenuInfoToggleDialog::getToggleDialogInfo(CtWindowID id)
{
	for (unsigned int i = 0; i < sizeof(Info) / sizeof(CtMenuToggleDialogInfo); i++) {
		if (id == Info[i].WindowId) {
			return &Info[i];
		}
	}
	return NULL;
}

GDI_STRING_ID CtMenuInfoToggleDialog::getTitle(CtWindowID id)
{
	CtMenuToggleDialogInfo* pInfo = getToggleDialogInfo(id);
	if (pInfo != NULL) {
		return pInfo->str_id;
	}
	return STR_ID_MAX_SIZE;
}


/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
