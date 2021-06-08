#include "CtContainerBattery.h"

const Battery_Res_Table CtContainerBattery::m_ImageRes[Bat_Res_Max_Num] = {
    {IC_OSD_BATT_LV5,IC_BATT_LV5},
    {IC_OSD_BATT_LV4,IC_BATT_LV4},
    {IC_OSD_BATT_LV3,IC_BATT_LV3},
    {IC_OSD_BATT_LV2,IC_BATT_LV2},
    {IC_OSD_BATT_LV1,IC_BATT_LV1},
    {IC_OSD_BATT_LV0_RED,IC_BATT_LV0_RED},
    {IC_OSD_BATT_LV0_RED,IC_BATT_LV0_RED},
    {IC_OSD_AC,IC_AC}
};

CtContainerBattery::CtContainerBattery(CtWindowCommonType Type) :
    m_Type(Type),
    m_Flash(false),
    m_pBattery(NULL)
{
}

CtContainerBattery::~CtContainerBattery(){

}

CtLayout* CtContainerBattery::createContainer(){
    CtLabel *pLabel = NULL;
    CtHLayout *pLayoutBattery = new CtHLayout();
	m_pBattery = new CtStackLabel();
    for(int i = 0;i <= APL_SYS_PARAM_BATTERY_REMAIN_DC_IN;i++){
        if(CT_COMMON_TYPE_REC == m_Type || CT_COMMON_TYPE_PLAY == m_Type ){
           pLabel = new CtLabel(m_ImageRes[i].RecResID);
        }else{
           pLabel = new CtLabel(m_ImageRes[i].HomeResID);
        }
        m_pBattery->addLabel(pLabel);
    }
 	if(CT_COMMON_TYPE_REC == m_Type || CT_COMMON_TYPE_PLAY == m_Type ){
	    pLayoutBattery->addWidget(m_pBattery,AlignTop);
	} else {
	    pLayoutBattery->addWidget(m_pBattery);
	}
    updateBattery();
    return pLayoutBattery;
}

bool CtContainerBattery::destroyContainer(){
    return true;
}

bool CtContainerBattery::handleParamEvent(const CtEventParam& Param){
    bool bRet = true;
    int t_Id = Param.getParamId();
    int int_Data = Param.getParamVal();

	switch(t_Id){
	case AplParamBatteryRemainStatus:
	case AplParamLcdIndicatorBatteryRemain: // Ä¶—p
		updateBattery();
		CtICManager::getInstance()->updateIC(IC_SEL_BAT_REMAIN);
		return true;
	}
    return bRet;
}

void CtContainerBattery::updateBattery(){
    int int_Data = APL_PARAM_GET_DATA(AplParamBatteryRemainStatus);

    m_pBattery->index(int_Data);
		
	// “_–Å§Œä
    if((APL_SYS_PARAM_BATTERY_REMAIN_NEAREND == int_Data) ||
       (APL_SYS_PARAM_BATTERY_REMAIN_UNDERCUT == int_Data)){
        if(m_pBattery->isVisible()){
            m_pBattery->startFlash(CtEventFlash::Freq_1Hz);
            m_Flash = true;
        }
    }else{
        if(m_Flash){
            m_pBattery->stopFlash();
            m_Flash = false;
        }
    }

	m_pBattery->setVisible(true);

	// Ä¶•\Ž¦§Œä
    if(  CT_COMMON_TYPE_PLAY == m_Type ){
		bool bDisp = APL_PARAM_GET_DATA(AplParamLcdIndicatorBatteryRemain) == APL_SYS_PARAM_SWITCH_ON;
        m_pBattery->setScreenSel(bDisp? ScreenAll: ScreenNone);
    }
}

CtScreenSel CtContainerBattery::getDispIcModeSel() {
	int int_Data = APL_PARAM_GET_DATA(AplParamBatteryRemainStatus);

	if ((APL_SYS_PARAM_BATTERY_REMAIN_NEAREND == int_Data) ||
		(APL_SYS_PARAM_BATTERY_REMAIN_UNDERCUT == int_Data)) {
		return ScreenAll;
	}

	return ScreenNone;
}
