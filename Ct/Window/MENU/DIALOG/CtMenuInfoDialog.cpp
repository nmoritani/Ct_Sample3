/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/*******************************************************************************
    �C���N���[�h�t�@�C��
*******************************************************************************/
#include "CtMenuInfoDialog.h"
#include "CtLanguage.h"

/*******************************************************************************
  �萔�̒�`
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
