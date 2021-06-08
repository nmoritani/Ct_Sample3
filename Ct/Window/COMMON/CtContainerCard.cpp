#include "CtContainerCard.h"
#include "CtHLayout.h"
#include "CtVLayout.h"

CtContainerCard::CtContainerCard(CtWindowCommonType Type) :
	m_pState(NULL),
	m_pSlotNum(NULL),
	m_pSlotTime(NULL),
	m_pLabel_Min(NULL),
	m_pSlotRemain(NULL),
	m_pSlotRemainMin(NULL),
	m_CardStateFlash(false),
	m_StateFlash(false),
	m_Type(Type),
	m_pAll(NULL)
{

}

CtContainerCard::~CtContainerCard() {

}

CtLayout* CtContainerCard::createContainer() {
	if (CT_COMMON_TYPE_REC == m_Type || CT_COMMON_TYPE_PLAY == m_Type) {
		m_pAll = createRecMode();
	}
	else {
		m_pAll = createHomeMode();
	}
	return m_pAll;
}

CtLayout* CtContainerCard::createRecMode() {
	CtLabel *pLabel = NULL;

	CtRecViewFontSet fSet_Left = CtRecViewFontSet();

	CtHLayout *pLayoutCard = new CtHLayout();
	{
		m_pRecCardStatus = new CtHLayout();
		////////// ○● //////////
		m_pState = new CtStackLabel();
		{
			pLabel = new CtLabel(IC_OSD_PRESET);
			m_pState->addLabel(pLabel);
			pLabel = new CtLabel(IC_OSD_REC);
			m_pState->addLabel(pLabel);
			pLabel = new CtLabel(IC_OSD_TARRY_G);
			m_pState->addLabel(pLabel);
			pLabel = new CtLabel("");
			m_pState->addLabel(pLabel);
		}
		m_pRecCardStatus->addWidget(m_pState, 2);

		////////// □■ //////////
		m_pSlotNum = new CtStackLabel();
		{
			pLabel = new CtLabel(getIcon(IconType_OSD_SD_OFF));
			m_pSlotNum->addLabel(pLabel);
			pLabel = new CtLabel(getIcon(IconType_OSD_SD_ON));
			m_pSlotNum->addLabel(pLabel);
		}
		m_pRecCardStatus->addWidget(m_pSlotNum, 2);
		
		pLayoutCard->addWidget(m_pRecCardStatus, 4);
		////////// 000min/WP,End,ERR,!SDXC //////////
		m_pRemainStatus = new CtLayout();
		{
			m_pSlotRemain = new CtStackLabel();
			{
				m_pSlotRemain->addLabel(new CtLabel(""));
				pLabel = new CtLabel(STR_ID_NO_10647, fSet_Left);	//WP
				m_pSlotRemain->addLabel(pLabel);
				pLabel = new CtLabel(STR_ID_NO_10648, fSet_Left);	//End
				m_pSlotRemain->addLabel(pLabel);
				pLabel = new CtLabel(STR_ID_NO_10649, fSet_Left);	//ERR
				m_pSlotRemain->addLabel(pLabel);
				pLabel = new CtLabel(STR_ID_NO_10650, fSet_Left);	//!SDXC
				m_pSlotRemain->addLabel(pLabel);
			}
			m_pRemainStatus->addWidget(m_pSlotRemain);

			m_pSlotRemainMin = new CtHLayout();
			{
				m_pSlotTime = new CtLabel("", fSet_Left);
				m_pSlotRemainMin->addWidget(m_pSlotTime, 3);

				m_pLabel_Min = new CtLabel(IC_OSD_MIN);
				m_pSlotRemainMin->addWidget(m_pLabel_Min, 2);
			}
			m_pRemainStatus->addWidget(m_pSlotRemainMin, AlignRight);
		}
		pLayoutCard->addWidget(m_pRemainStatus, 5);
	}
	return pLayoutCard;
}

CtLayout* CtContainerCard::createHomeMode() {
	// NoMaintenance
	CtLabel *pLabel = NULL;

	CtFontSet fSet_Right = CtFontSet(FontTypeNormal_alignRight, CtColor::White);
	CtFontSet fSet_Left = CtFontSet(FontTypeNormal, CtColor::White);
	CtFontSet fSet_Center = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	CtFontSet fSet_Center_Red = CtFontSet(FontTypeNormal_alignCenter, CtColor::Red);
	CtHLayout* pLayout1 = new CtHLayout();  // 11

	CtVLayout* pLayout21 = new CtVLayout();  // 10
	m_pState = new CtStackLabel();
	pLabel = new CtLabel(IC_PRESET);
	m_pState->addLabel(pLabel);
	pLabel = new CtLabel();
	m_pState->addLabel(pLabel);
	CtVLayout* pLayout22 = new CtVLayout();  // 10
	CtVLayout* pLayout2 = new CtVLayout();  // 22
	pLayout2->addWidget(pLayout21, 10);
	pLayout2->addWidget(m_pState, 30);
	pLayout2->addWidget(pLayout22, 10);

	CtVLayout* pLayout3 = new CtVLayout();  // 12

	m_pSlotNum = new CtStackLabel(); //  Slot 40x50
	pLabel = new CtLabel(getIcon(IconType_SD_OFF));
	m_pSlotNum->addLabel(pLabel);
	pLabel = new CtLabel(getIcon(IconType_SD_ON));
	m_pSlotNum->addLabel(pLabel);

	m_pSlotRemain = new CtStackLabel();
	pLabel = new CtLabel();
	m_pSlotRemain->addLabel(pLabel);
	pLabel = new CtLabel(STR_ID_NO_10647, fSet_Center);
	m_pSlotRemain->addLabel(pLabel);
	pLabel = new CtLabel(STR_ID_NO_10648, fSet_Center);
	m_pSlotRemain->addLabel(pLabel);
	pLabel = new CtLabel(STR_ID_NO_10649, fSet_Center_Red);
	m_pSlotRemain->addLabel(pLabel);
	pLabel = new CtLabel(STR_ID_NO_10650, fSet_Center_Red);
	m_pSlotRemain->addLabel(pLabel);

	m_pSlotTime = new CtLabel("", fSet_Right);// 80     Slot1残量
	m_pLabel_Min = new CtLabel(IC_MIN); // 75

	CtHLayout* pLayoutCard1 = new CtHLayout();
	pLayoutCard1->addWidget(pLayout1, 11);
	pLayoutCard1->addWidget(pLayout2, 22);
	pLayoutCard1->addWidget(pLayout3, 12);
	pLayoutCard1->addWidget(m_pSlotNum, 40);
	pLayoutCard1->addWidget(m_pSlotRemain, 155);

	CtVLayout* pMinVLayout = new CtVLayout();
	CtHLayout* pMinHLayout = new CtHLayout();
	pMinHLayout->addWidget(m_pLabel_Min, 50);
	pMinHLayout->addStretch(10);
	pMinVLayout->addStretch(16);
	pMinVLayout->addWidget(pMinHLayout, 32);
	pMinVLayout->addStretch(2);

	CtHLayout *pHLayout = new CtHLayout();
	pHLayout->addWidget(new CtLabel(), 85);
	pHLayout->addWidget(m_pSlotTime, 80);
	pHLayout->addWidget(pMinVLayout, AlignLeft, 60);
	pHLayout->addWidget(new CtLabel(), 15);

	CtLayout *pLayoutMain = new CtLayout();
	pLayoutMain->addWidget(pLayoutCard1);
	pLayoutMain->addWidget(pHLayout);

	return pLayoutMain;
}

bool CtContainerCard::destroyContainer() {
	return false;
}

CtScreenSel CtContainerCard::getDispIcModeSel(int _IcId){
	CtMenuOutputId IcId = (CtMenuOutputId)_IcId;
	if (IcId == IC_SEL_CARD_STATUS || IcId == IC_SEL_CARD_STATUS2) {
		return checkRecCardStatusScrnSel();
	}
	else if (IcId == IC_SEL_REMAIN1 || IcId == IC_SEL_REMAIN2) {
		return checkRemainStatusScrnSel();
	}
	return ScreenNone;
}

CtScreenSel CtContainerCard::checkRecCardStatusScrnSel() {
	CtScreenSel ScreenSel = ScreenAll;

	if (APL_PARAM_GET_DATA(AplParamLcdIndicatorSlotStatus) == APL_SYS_PARAM_SWITCH_OFF) {
		if (isRemainUnder2min()) {
			// (2分以下)点滅中はすべて表示
			ScreenSel = ScreenAll;
		} else {
			ScreenSel = ScreenNone;
		}
	}else if (APL_PARAM_GET_DATA(AplParamDispModeCheck) == APL_SYS_PARAM_SWITCH_ON) {
		if (m_pState->getIndex() == 1 || m_pState->getIndex() == 2) {
			ScreenSel = ScreenAll;
		} else {
			ScreenSel = ScreenNone;
		}
	}
	return ScreenSel;
}

CtScreenSel CtContainerCard::checkRemainStatusScrnSel() {
	CtScreenSel ScreenSel = ScreenAll;

	if (APL_PARAM_GET_DATA(AplParamLcdIndicatorSlotStatus) == APL_SYS_PARAM_SWITCH_OFF) {
		ScreenSel = ScreenNone;
	}
	if (APL_PARAM_GET_DATA(AplParamDispModeCheck) == APL_SYS_PARAM_SWITCH_ON) {
		ScreenSel = ScreenNone;
	}
	if (isRemainUnder2min()) {
		// (2分以下)点滅中はすべて表示
		ScreenSel = ScreenAll;
	}
	return ScreenSel;
}

bool CtContainerCard::isRemainUnder2min() {
	if (m_pSlotRemainMin->isFlashing() == true && m_pSlotRemain->getIndex() == 0 /*残量表示中*/) {
		// (2分以下)点滅中はすべて表示
		return true;
	}
	return false;
}