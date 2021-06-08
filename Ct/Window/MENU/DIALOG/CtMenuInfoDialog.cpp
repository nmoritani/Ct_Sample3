/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/*******************************************************************************
    インクルードファイル
*******************************************************************************/
#include "CtMenuInfoDialog.h"
#include "CtLanguage.h"

/*******************************************************************************
  定数の定義
*******************************************************************************/

CtMenuInfoDialog::CtMenuDialogInfo CtMenuInfoDialog::Info[] = {
#include "DialogInfo.def"
};

CtMenuInfoDialog::CtMenuDialogInfo* CtMenuInfoDialog::getDialogInfo(CtWindowID id)
{
	for (unsigned int i = 0; i < sizeof(Info) / sizeof(CtMenuDialogInfo); i++) {
		if (id == Info[i].WindowId) {
			return &Info[i];
		}
	}
	return NULL;
}



/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
