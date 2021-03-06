#include "CtContainerCard2.h"

CtContainerCard2::CtContainerCard2(CtWindowCommonType Type) :
	CtContainerCard(Type)
{

}

CtContainerCard2::~CtContainerCard2() {

}

GDI_IMAGE_ID CtContainerCard2::getIcon(IconType type)
{
	switch (type)
	{
	case IconType_OSD_SD_OFF:	return IC_OSD_SLOT2_SD_OFF;
	case IconType_OSD_SD_ON:	return IC_OSD_SLOT2_SD_ON;
	case IconType_SD_OFF:		return IC_SLOT2_SD_OFF;
	case IconType_SD_ON:		return IC_SLOT2_SD_ON;
	default:
		break;
	}

	return IMAGE_ID_MAX;
}

bool CtContainerCard2::startupContainer() {
	if (CT_COMMON_TYPE_REC == m_Type || CT_COMMON_TYPE_PLAY == m_Type) {
		// ??
		updateRecState(APL_PARAM_GET_DATA(AplParamSlot2RecStatus));
		// ??
		updateCardState(APL_PARAM_GET_DATA(AplParamSlot2CardStatus));
		updateSlotRemain(APL_PARAM_GET_DATA(AplParamSlot2ErrStatus));
	}
	else {
		updateSlotRemain(APL_PARAM_GET_DATA(AplParamSlot2ErrStatus));
	}
	CtICManager::getInstance()->registInstance(m_pRecCardStatus, this, IC_SEL_CARD_STATUS2);
	CtICManager::getInstance()->registInstance(m_pRemainStatus, this, IC_SEL_REMAIN2);
	return true;
}

void CtContainerCard2::updateRecState(int int_Data) {
	bool isDisp = false;

	switch (int_Data) {
	case APL_SYS_PARAM_SLOT1_REC_STATUS_RECORDING:
	case APL_SYS_PARAM_SLOT1_REC_STATUS_REC_STOP:
		isDisp = true;
		m_pState->index(1);
		if (APL_SYS_PARAM_SLOT1_REC_STATUS_REC_STOP == int_Data) {
			m_pState->startFlash(CtEventFlash::Freq_1Hz);
		}
		break;
	case APL_SYS_PARAM_SLOT1_REC_STATUS_PRE_REC_STOP:
		isDisp = true;
		m_pState->index(0);
		break;
	case APL_SYS_PARAM_SLOT1_REC_STATUS_OFF:
	default:
		m_pState->index(3);
		isDisp = false;
		break;
	}

	if (APL_SYS_PARAM_SLOT1_REC_STATUS_REC_STOP != int_Data) {
		if (m_pState->isFlashing() == true) {
			m_pState->stopFlash();
		}
	}

	// NDI|HX???͔r??
	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		isDisp = false;
	}

	m_pState->setVisible(isDisp);
}

void CtContainerCard2::updateCardState(int int_Data)
{
	bool isDisp = false;

	switch (int_Data) {
	case APL_SYS_PARAM_SLOT2_CARD_STATUS_INVALID:
	case APL_SYS_PARAM_SLOT2_CARD_STATUS_INVALID_ACCESS:
		isDisp = true;
		m_pSlotNum->index(0);
		if (APL_SYS_PARAM_SLOT2_CARD_STATUS_INVALID_ACCESS == int_Data) {
			m_pSlotNum->startFlash(CtEventFlash::Freq_1Hz);
		}
		break;
	case APL_SYS_PARAM_SLOT2_CARD_STATUS_VALID:
		isDisp = true;
		m_pSlotNum->index(1);
		break;
	case APL_SYS_PARAM_SLOT2_CARD_STATUS_NO_CARD:
	default:
		isDisp = false;
		break;
	}

	if (APL_SYS_PARAM_SLOT2_CARD_STATUS_INVALID_ACCESS != int_Data) {
		if (m_pSlotNum->isFlashing()) {
			m_pSlotNum->stopFlash();
		}
	}

	// NDI|HX???͔r??
	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		isDisp = false;
	}

	m_pSlotNum->setVisible(isDisp);
}

void CtContainerCard2::updateSlotRemain(int int_Data) {
	int Index = 0;
	bool isDisp = true;
	int Value = 999;

	if (APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_CARD == int_Data) {
		isDisp = false;
	}
	else if (APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED == int_Data
		|| APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR == int_Data) {
		isDisp = true;
		Index = 3;
	}
	else if (APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC == int_Data) {
		isDisp = true;
		Index = 4;
	}
	else if (APL_SYS_PARAM_SLOT2_ERR_STATUS_WP == int_Data) {
		isDisp = true;
		Index = 1;
	}
	else if (APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_REMAIN == int_Data) {
		isDisp = true;
		Index = 2;
	}
	else if (APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR == int_Data ||
		APL_SYS_PARAM_SLOT2_ERR_STATUS_INCOMPATIBLE_CARD == int_Data) {
		Index = 0;
		isDisp = true;

		char Str[7];
		memset(Str, 0, sizeof(Str));
		Value = APL_PARAM_GET_DATA(AplParamSlot2Remain);

		if (CT_COMMON_TYPE_HOME == m_Type) {
			sprintf(Str, "%d", Value);
		}
		else {
			sprintf(Str, "%3d", Value);
		}

		m_pSlotTime->setText(Str);
	}
	else {
		isDisp = false;
	}
	m_pSlotRemain->index(Index);

	if (CT_COMMON_TYPE_REC == m_Type || CT_COMMON_TYPE_PLAY == m_Type) {
		if (APL_PARAM_GET_DATA(AplParamBlinkSd2) == APL_SYS_PARAM_SWITCH_ON) {
			m_pSlotRemainMin->startFlash(CtEventFlash::Freq_1Hz);
		}
		else {
			if (m_pSlotRemainMin->isFlashing()) {
				m_pSlotRemainMin->stopFlash();
			}
		}
	}

	// NDI|HX???͔r??
	if (APL_PARAM_GET_DATA(AplParamNetworkFunc) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX) {
		isDisp = false;
	}

	if (CT_COMMON_TYPE_REC == m_Type || CT_COMMON_TYPE_PLAY == m_Type) {
		if (isDisp == false) {
			// Card ??
			m_pSlotRemainMin->setVisible(false);
			m_pSlotRemain->setVisible(false);
		}
		else if (Index == 0) {
			// ?c?ʕ\??
			m_pSlotRemainMin->setVisible(isDisp);
			m_pSlotRemain->setVisible(false);
		}
		else {
			// Err?\??
			m_pSlotRemainMin->setVisible(false);
			m_pSlotRemain->setVisible(isDisp);
		}
	}
	//updateDisp();
}
bool CtContainerCard2::handleParamEvent(const CtEventParam& Param) {
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
		// ??
	case AplParamSlot2RecStatus:
		updateRecState(int_Data);
		CtICManager::getInstance()->updateIC(IC_SEL_CARD_STATUS2);
		break;
		// ??
	case AplParamSlot2CardStatus:
		updateCardState(int_Data);
		break;
		// ***min
	case AplParamBlinkSd2:
	case AplParamSlot2Remain:
	case AplParamSlot2ErrStatus:
		updateSlotRemain(APL_PARAM_GET_DATA(AplParamSlot2ErrStatus));
		CtICManager::getInstance()->updateIC(IC_SEL_CARD_STATUS2);
		CtICManager::getInstance()->updateIC(IC_SEL_REMAIN2);
		break;
		// NDI|HX
	case AplParamNetworkFunc:
		updateRecState(APL_PARAM_GET_DATA(AplParamSlot2RecStatus));
		updateCardState(APL_PARAM_GET_DATA(AplParamSlot2CardStatus));
		updateSlotRemain(APL_PARAM_GET_DATA(AplParamSlot2ErrStatus));
		CtICManager::getInstance()->updateIC(IC_SEL_CARD_STATUS2);
		CtICManager::getInstance()->updateIC(IC_SEL_REMAIN2);
		break;
	default:
		return false;
	}

	return true;
}
