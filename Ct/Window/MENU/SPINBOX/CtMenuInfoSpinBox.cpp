/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/*******************************************************************************
    �C���N���[�h�t�@�C��
*******************************************************************************/
#include "CtMenuInfoSpinBox.h"
#include "CtLanguage.h"

/*******************************************************************************
  �萔�̒�`
*******************************************************************************/

CtMenuInfoSpinBox::CtMenuSpinBoxInfo CtMenuInfoSpinBox::Info[] = {
#include "SpinBoxInfo.def"
};

CtMenuInfoSpinBox::CtMenuSpinBoxTable CtMenuInfoSpinBox::Table[] = {
#include "SpinBoxTable.def"
};

CtMenuInfoSpinBox::CtMenuSpinBoxInfo* CtMenuInfoSpinBox::getSpinBoxInfo(CtWindowID id)
{
	for (unsigned int i = 0; i < sizeof(Info) / sizeof(CtMenuSpinBoxInfo); i++) {
		if (id == Info[i].WindowId) {
			return &Info[i];
		}
	}
	return NULL;
}

CtMenuInfoSpinBox::CtMenuSpinBoxTable* CtMenuInfoSpinBox::getSpinBoxTable(CtWindowID id)
{
	for (unsigned int i = 0; i < sizeof(Table) / sizeof(CtMenuSpinBoxTable); i++) {
		if (id == Table[i].WindowId) {
			return &Table[i];
		}
	}
	return NULL;
}

int CtMenuInfoSpinBox::getIntervalTime(CtWindowID id)
{
	CtMenuSpinBoxInfo* info = getSpinBoxInfo(id);
	if (info == NULL) return FastInterval_Max;

	int validItemnum = 0;
	int interval = FastInterval_Max;

	switch (info->action) {
	case SpinBoxActionType_CallFunc:
		/* CallFunc�n�͍��ڐ����s���Ȃ̂ŕW����Ԃ� */
		return FastInterval_Max;
	default:
	{
		int min = info->disp.min;
		int max = info->disp.max;
		int value = min;

		while (value <= max) {
			value = value + info->disp.step;
			validItemnum++;
		}
	}
	break;
	}

	/* X�b�����đS���ڂ�I���ł���悤�� */
	/* ��������̌v�Z�͍s�� */
	if (validItemnum != 0) {
		interval = FastInterval_SelectionTIme / validItemnum;
		if (interval < FastInterval_Max) {
			interval = FastInterval_Max;
		}
		else if (interval > FastInterval_Min) {
			interval = FastInterval_Min;
		}
	}
	else {
		interval = FastInterval_Min;
	}

	return interval;
}
int CtMenuInfoSpinBox::getNumericMax(CtMenuSpinBoxInfo* pInfo)
{
	if (pInfo == NULL) { return 0; }
	int Max = pInfo->disp.max;

	return Max;
}
int CtMenuInfoSpinBox::getNumericMin(CtMenuSpinBoxInfo* pInfo)
{
	if (pInfo == NULL) { return 0; }
	int Min = pInfo->disp.min;

	return Min;
}

/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
