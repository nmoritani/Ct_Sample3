#include "CtContainerWifi.h"
#include "CtWindow.h"
#include "CtHLayout.h"

const Wifi_Res_Table CtContainerWifi::m_ImageRes[APL_SYS_PARAM_WLAN_DISABLE] = {
	{IC_OSD_WIFI_OFF,		IC_WIFI_OFF},
	{IC_OSD_WIFI_ROP_LV0,	IC_WIFI_ROP_LV0},
	{IC_OSD_WIFI_ROP_LV1,	IC_WIFI_ROP_LV1},
	{IC_OSD_WIFI_ROP_LV2,	IC_WIFI_ROP_LV2},
	{IC_OSD_WIFI_ROP_LV3,	IC_WIFI_ROP_LV3},
	{IC_OSD_WIFI_ROP_LV4,	IC_WIFI_ROP_LV4},
	{IC_OSD_WIFI_LV0,		IC_WIFI_LV0},
	{IC_OSD_WIFI_LV1,		IC_WIFI_LV1},
	{IC_OSD_WIFI_LV2,		IC_WIFI_LV2},
	{IC_OSD_WIFI_LV3,		IC_WIFI_LV3},
	{IC_OSD_WIFI_LV4,		IC_WIFI_LV4},
	{IC_OSD_LAN_OFF,		IC_LAN_OFF},
	{IC_OSD_LAN_ON,			IC_LAN_ON},
	{IC_OSD_LAN_ON_ROP,		IC_LAN_ON_ROP},
};

CtContainerWifi::CtContainerWifi(CtWindowCommonType Type) :
    m_Type(Type),
    m_pWifi(NULL)
{
}

CtContainerWifi::~CtContainerWifi(){

}

CtLayout* CtContainerWifi::createContainer(){
    CtLabel *pLabel = NULL;
    CtHLayout *pLayoutWifi = new CtHLayout();

    m_pWifi = new CtStackLabel();
    for(int i = 0;i < APL_SYS_PARAM_WLAN_DISABLE;i++){
        if(CT_COMMON_TYPE_REC == m_Type || CT_COMMON_TYPE_PLAY == m_Type ){
           pLabel = new CtLabel(m_ImageRes[i].RecResID);
        }else{
           pLabel = new CtLabel(m_ImageRes[i].HomeResID);
        }
        m_pWifi->addLabel(pLabel);
    }

    pLayoutWifi->addWidget(m_pWifi);

    initDisplay();

    return pLayoutWifi;
}

bool CtContainerWifi::destroyContainer(){
    return true;
}

bool CtContainerWifi::handleParamEvent(const CtEventParam& Param){
    bool isRedraw = true;
    int t_Id = Param.getParamId();
    int int_Data = Param.getParamVal();

    switch(t_Id){
		case AplParamLcdIndicatorWlan:
        case AplParamWLanStatus:
			updateWifiDisp();
        	updateWifiIcon(int_Data);
            break;
        default:
            isRedraw = false;
            break;
    }

    return isRedraw;
}

void CtContainerWifi::updateWifiIcon(int int_Data){
    m_pWifi->index(int_Data);
}

void CtContainerWifi::updateWifiDisp(){
    bool isDisp = false;

	int int_Data = APL_PARAM_GET_DATA(AplParamWLanStatus);
	
    if(APL_SYS_PARAM_WLAN_DISABLE != int_Data){
        isDisp = true;
    }else{
        isDisp = false;
    }

	// Ä¶Žž‚Ì‚Ý
	if( CT_COMMON_TYPE_PLAY == m_Type ){
		bool bIcDisp = APL_PARAM_GET_DATA(AplParamLcdIndicatorWlan) == APL_SYS_PARAM_SWITCH_ON;
    	m_pWifi->setScreenSel(bIcDisp? ScreenAll:ScreenLOUT);
	}

    m_pWifi->setVisible(isDisp);
}

void CtContainerWifi::initDisplay(){

    updateWifiDisp();

    updateWifiIcon(APL_PARAM_GET_DATA(AplParamWLanStatus));

}
