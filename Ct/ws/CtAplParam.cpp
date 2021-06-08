#include "CtAplParam.h"

int CtAplParam::getData(int id)
{
	return APL_PARAM_GET_DATA(id);
}

int CtAplParam::getLanguage()
{
	return APL_PARAM_GET_DATA(AplParamLanguage);
}

int CtAplParam::getCharLuminance()
{
	return APL_PARAM_GET_DATA(AplParamLcdIndicatorCharLuminance);
}

int CtAplParam::getSdiIndicatorDisp()
{
	return APL_PARAM_GET_DATA(AplParamSdiOutIndicatorDisp);
}

int CtAplParam::getHdmiIndicatorDisp()
{
	return APL_PARAM_GET_DATA(AplParamHdmiOutIndicatorDisp);
}

CtParamState CtAplParam::getState(int id, int val)
{
	AplParamService::AplParamMainItem* pMain = NULL;
	AplParamService::AplParamSubItem* pSub = NULL;

	if (0 > id || id >= AplParamIdMax)
		return CtParamState_End;

	if ((pMain = APL_PARAM()->getParamState(id)) == NULL)
		return CtParamState_End;

	switch (pMain->mState) {
	case AplParamState_VisibleValid:
		break;
	case AplParamState_VisibleInvalid:
		return CtParamState_Invalid;
	case AplParamState_Invisible:
		return CtParamState_Invisible;
	default:
		break;
	}

	if ((pSub = pMain->sub_item) == NULL) {
		return CtParamState_End;
	}

	while (pSub->state != AplParamState_End) {
		if (pSub->value != val) {
			pSub++;
			continue;
		}
		switch (pSub->state) {
		case AplParamState_VisibleValid:
			return CtParamState_Visible;
		case AplParamState_VisibleInvalid:
			return CtParamState_Invalid;
		case AplParamState_Invisible:
			return CtParamState_Invisible;
		default:
			break;
		}
	}
	return CtParamState_End;
}
