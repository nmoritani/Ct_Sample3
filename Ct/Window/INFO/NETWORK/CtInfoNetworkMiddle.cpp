/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoNetworkMiddle
 */
#include "CtInfoNetworkMiddle.h"
#include "CtLabel.h"
#include "apl_sys_param_enum.h"
#include "AplParamService.h"
#include "stdio.h"
CtInfoNetworkMiddle::CtInfoNetworkMiddle() :
    m_pBox(NULL),
    m_pLabelWlan(NULL),
    m_pLabelLink(NULL),
    m_pNetworkSelLink(NULL),
    m_pIdAddressValue(NULL),
    m_pNetMaskValue(NULL),
    m_pGatewayValue(NULL)
{
    setClassType(CtClassType_LayoutMain);
}

CtLayout* CtInfoNetworkMiddle::createContainer()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fCenterSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    m_pLabelWlan = new CtStackLabel();
    m_pLabelLink = new CtStackLabel();
    m_pBox = new CtVLayout();

    m_pNetworkSelLink = new CtHLayout();
    m_pIdAddressValue = new CtLabel("", fSet);
    m_pNetMaskValue = new CtLabel("", fSet);
    m_pGatewayValue = new CtLabel("", fSet);
    
    m_pLabelWlan->addLabel(new CtLabel(STR_ID_NO_10792, fSet, CtMargin(4)));      //StringID   "OFF"
    m_pLabelWlan->addLabel(new CtLabel(STR_ID_NO_10834, fSet, CtMargin(4)));      //StringID   "WLAN"
    m_pLabelLink->addLabel(new CtLabel(STR_ID_NO_10712, fSet, CtMargin(4)));      //StringID   "NO LINK"
    m_pLabelLink->addLabel(new CtLabel(STR_ID_NO_10711, fSet, CtMargin(4)));      //StringID   "LINK"
    m_pLabelLink->addLabel(new CtLabel(STR_ID_NO_10713, fSet, CtMargin(4)));      //StringID   "ERROR"

    const char string[] = ":";
    /*InfoNetwork画面の情報部品を作成する*/
    CtHLayout *pNetworkSel = new CtHLayout();
    CtHLayout *pIdAddress = new CtHLayout();
    CtHLayout *pNetMask = new CtHLayout();
    CtHLayout *pGateway = new CtHLayout();

    pNetworkSel->addStretch(16);
    pNetworkSel->addWidget(new CtLabel(STR_ID_NO_10833, fSet), 200);
    pNetworkSel->addWidget(new CtLabel(string, fCenterSet), 16);
    pNetworkSel->addWidget(m_pLabelWlan, 112);
    m_pNetworkSelLink->addWidget(new CtLabel(string, fCenterSet), 16);
    m_pNetworkSelLink->addWidget(m_pLabelLink, 600);
    pNetworkSel->addWidget(m_pNetworkSelLink, 616);

    pIdAddress->addStretch(232);
    pIdAddress->addWidget(new CtLabel(STR_ID_NO_10835,fSet),134);
    pIdAddress->addWidget(new CtLabel(string,fCenterSet),16);
    pIdAddress->addWidget(m_pIdAddressValue,578);

    pNetMask->addStretch(232);
    pNetMask->addWidget(new CtLabel(STR_ID_NO_10714,fSet),134);
    pNetMask->addWidget(new CtLabel(string,fCenterSet),16);
    pNetMask->addWidget(m_pNetMaskValue,578);

    pGateway->addStretch(232);
    pGateway->addWidget(new CtLabel(STR_ID_NO_10715,fSet),134);
    pGateway->addWidget(new CtLabel(string,fCenterSet),16);
    pGateway->addWidget(m_pGatewayValue,578);

    m_pBox->addStretch(12);
    m_pBox->addWidget(pNetworkSel,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pIdAddress,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pNetMask,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pGateway,48);
    m_pBox->addStretch(126);

    m_pBox->setName("@@@CtInfoNetworkMiddle@@@");

    /*AplParamの設定値により画面の表示情報を更新する*/
    updateNetworkSel();
    updateIdAddress();
    updateNetMask();
    updateGateway();

    return m_pBox;
}

bool CtInfoNetworkMiddle::destroyContainer() {
	return true;
}

CtInfoNetworkMiddle::~CtInfoNetworkMiddle(){
}

void CtInfoNetworkMiddle::updateNetworkSel(){
    signed int nTempWlan = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamWirelessLanMode));
    signed int nTempLink = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamWlanLinkState));
    m_pLabelWlan->index(nTempWlan);
    m_pLabelLink->index(nTempLink);

    if(0 == nTempWlan){
        m_pNetworkSelLink->setVisible(false);
        m_pIdAddressValue->setVisible(false);
        m_pNetMaskValue->setVisible(false);
        m_pGatewayValue->setVisible(false);
    }else{
        m_pNetworkSelLink->setVisible(true);
        m_pIdAddressValue->setVisible(true);
        m_pNetMaskValue->setVisible(true);
        m_pGatewayValue->setVisible(true);
    }
}

void CtInfoNetworkMiddle::updateIdAddress(){
    unsigned char Data[AplParamIpAddress_Size];
    char str[16];
    memset(str,0,sizeof(str));
    APL_PARAM_GET_DATA_AREA( AplParamIpAddress, Data, AplParamIpAddress_Size);
    sprintf( str,"%d.%d.%d.%d", Data[0], Data[1], Data[2], Data[3]);
    m_pIdAddressValue->setText(str);
}

void CtInfoNetworkMiddle::updateNetMask(){
    unsigned char Data[AplParamSubnet_Size];
    char str[16];
    memset(str,0,sizeof(str));
    APL_PARAM_GET_DATA_AREA( AplParamSubnet, Data, AplParamSubnet_Size);
    sprintf( str,"%d.%d.%d.%d", Data[0], Data[1], Data[2], Data[3]);
    m_pNetMaskValue->setText(str);
}

void CtInfoNetworkMiddle::updateGateway(){
    unsigned char Data[AplParamGateway_Size];
    char str[16];
    memset(str,0,sizeof(str));
    APL_PARAM_GET_DATA_AREA( AplParamGateway, Data, AplParamGateway_Size);
    sprintf( str,"%d.%d.%d.%d", Data[0], Data[1], Data[2], Data[3]);
    m_pGatewayValue->setText(str);
}

bool CtInfoNetworkMiddle::handleParamEvent(const CtEventParam& Param){
    bool bRet = false;
    int t_Id = Param.getParamId();
    
    switch(t_Id){
        case AplParamWirelessLanMode:
        case AplParamWLanStatus:
        case AplParamWlanLinkState:
            updateNetworkSel();
            bRet = true;
            break;
        case AplParamIpAddress:
            updateIdAddress(); 
            bRet = true;
            break;
        case AplParamSubnet:     
            updateNetMask();
            bRet = true;
            break;
        case AplParamGateway:
            updateGateway();
            bRet = true;
            break;

        default:
            break;
    }

    return bRet;
}
