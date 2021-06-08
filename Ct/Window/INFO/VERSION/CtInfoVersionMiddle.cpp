/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoVersionMiddle
 */
#include "CtInfoVersionMiddle.h"
#include "CtLabel.h"
#include "apl_sys_param_enum.h"
#include "AplParamService.h"
#include "stdio.h"

CtInfoVersionMiddle::CtInfoVersionMiddle() :
    m_pBox(NULL),
    m_pModelValue(NULL),
    m_pSerialNoValue(NULL),
    m_pVersionValue(NULL),
    m_pBeSoftValue(NULL),
    m_pCamSoftValue(NULL),
    m_pActSoftValue(NULL),
    m_pFpgaValue(NULL)
{
    setClassType(CtClassType_LayoutMain);
}

CtLayout* CtInfoVersionMiddle::createContainer()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fSet1 = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    m_pBox = new CtVLayout();

    m_pModelValue = new CtLabel("",fSet);
    m_pSerialNoValue = new CtLabel("",fSet);
    m_pVersionValue = new CtLabel("",fSet);
    m_pBeSoftValue = new CtLabel("",fSet);
    m_pCamSoftValue = new CtLabel("",fSet);
    m_pActSoftValue = new CtLabel("",fSet);
    m_pFpgaValue = new CtLabel("",fSet);

    const char string[] = ":";

    /*InfoVersion画面の情報部品を作成する*/
    CtHLayout *pModel = new CtHLayout();
    CtHLayout *pSerialNo = new CtHLayout();
    CtHLayout *pVersion = new CtHLayout();
    CtHLayout *pBeSoftAndCamSoft = new CtHLayout();
    CtHLayout *pActSoftAndFpga = new CtHLayout();

    pModel->addStretch(16);
    pModel->addWidget(new CtLabel(STR_ID_NO_10831,fSet),136);
    pModel->addWidget(new CtLabel(string,fSet1),16);
    pModel->addWidget(m_pModelValue,792);

    pSerialNo->addStretch(16);
    pSerialNo->addWidget(new CtLabel(STR_ID_NO_10832,fSet),136);
    pSerialNo->addWidget(new CtLabel(string,fSet1),16);
    pSerialNo->addWidget(m_pSerialNoValue,792);

    pVersion->addStretch(16);
    pVersion->addWidget(new CtLabel(STR_ID_NO_10800,fSet),136);
    pVersion->addWidget(new CtLabel(string,fSet1),16);
    pVersion->addWidget(m_pVersionValue,792);

    pBeSoftAndCamSoft->addStretch(36);
    pBeSoftAndCamSoft->addWidget(new CtLabel(STR_ID_NO_10707,fSet),116);
    pBeSoftAndCamSoft->addWidget(new CtLabel(string,fSet1),16);
    pBeSoftAndCamSoft->addWidget(m_pBeSoftValue,150);
    pBeSoftAndCamSoft->addWidget(new CtLabel(STR_ID_NO_10708,fSet),116);
    pBeSoftAndCamSoft->addWidget(new CtLabel(string,fSet1),16);
    pBeSoftAndCamSoft->addWidget(m_pCamSoftValue,510);

    pActSoftAndFpga->addStretch(36);
    pActSoftAndFpga->addWidget(new CtLabel(STR_ID_NO_10709,fSet),116);
    pActSoftAndFpga->addWidget(new CtLabel(string,fSet1),16);
    pActSoftAndFpga->addWidget(m_pActSoftValue,150);
    pActSoftAndFpga->addWidget(new CtLabel(STR_ID_NO_10710,fSet),116);
    pActSoftAndFpga->addWidget(new CtLabel(string,fSet1),16);
    pActSoftAndFpga->addWidget(m_pFpgaValue,510);
    
    m_pBox->addStretch(12);
    m_pBox->addWidget(pModel,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pSerialNo,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pVersion,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pBeSoftAndCamSoft,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pActSoftAndFpga,48);
    m_pBox->addStretch(72);

    m_pBox->setName("@@@CtInfoVersionMiddle@@@");

    /*AplParamの設定値により画面の表示情報を更新する*/
    updateModelValue();
    updateSerialNoValue();
    updateVersionValue();
    updateBeSoftValue();
    updateCamSoftValue();
    updateActSoftValue();
    updateFpgaValue();

    return m_pBox;
}

bool CtInfoVersionMiddle::destroyContainer() {
	return true;
}

CtInfoVersionMiddle::~CtInfoVersionMiddle()
{
}

void CtInfoVersionMiddle::updateModelValue(){
    char modelValue[AplParamInfoModel_Size];
	APL_PARAM_GET_DATA_AREA(AplParamInfoModel, (unsigned char*)modelValue, AplParamInfoModel_Size );
    m_pModelValue->setText(modelValue);
}

void CtInfoVersionMiddle::updateSerialNoValue(){
    char serialNoValue[AplParamInfoSerialNo_Size];
    APL_PARAM_GET_DATA_AREA(AplParamInfoSerialNo, (unsigned char*)serialNoValue, AplParamInfoSerialNo_Size );
    m_pSerialNoValue->setText(serialNoValue);
}

void CtInfoVersionMiddle::updateVersionValue(){
    int versionValue = APL_PARAM_GET_DATA( AplParamInfoVersion );
    char strVersionValue[30];
    memset(strVersionValue,0,sizeof(strVersionValue));
	sprintf( strVersionValue, "%01d.%02d-%02d-%01d.%02d", ((versionValue & 0xFF000000) >> 24),
                                                          ((versionValue & 0x00FF0000) >> 16),
                                                          ((versionValue & 0x0000F000) >> 12),
                                                          ((versionValue & 0x00000F00) >> 8),
                                                          ((versionValue & 0x000000FF) >> 0));
    m_pVersionValue->setText(strVersionValue);
}

void CtInfoVersionMiddle::updateBeSoftValue(){
    int beSoftValue = APL_PARAM_GET_DATA(AplParamBeSoftVer);
    char strBeSoftValue[30];
    memset(strBeSoftValue,0,sizeof(strBeSoftValue));
	sprintf( strBeSoftValue, "v%03d", beSoftValue );
    m_pBeSoftValue->setText(strBeSoftValue);
}

void CtInfoVersionMiddle::updateCamSoftValue(){
    int camSoftValue = APL_PARAM_GET_DATA(AplParamCamSoftVer);
    char strCamSoftValue[5];
    memset(strCamSoftValue,0,sizeof(strCamSoftValue));
	sprintf( strCamSoftValue, "v%03d", camSoftValue );
    m_pCamSoftValue->setText(strCamSoftValue);
}

void CtInfoVersionMiddle::updateActSoftValue(){
    int actSoftValue = APL_PARAM_GET_DATA(AplParamActSoftVer);
    char strActSoftValue[5];
    memset(strActSoftValue,0,sizeof(strActSoftValue));
	sprintf( strActSoftValue, "v%03d", actSoftValue );
    m_pActSoftValue->setText(strActSoftValue);
}

void CtInfoVersionMiddle::updateFpgaValue(){
    int fpgaValue = APL_PARAM_GET_DATA(AplParamFpgaVer);
    char strFpgaValue[5];
    memset(strFpgaValue,0,sizeof(strFpgaValue));
	sprintf( strFpgaValue, "v%03d", fpgaValue);
    m_pFpgaValue->setText(strFpgaValue);
}

bool CtInfoVersionMiddle::handleParamEvent(const CtEventParam& Param){
    bool bRet = false;
    int t_Id = Param.getParamId();
    
    switch(t_Id){
        case AplParamInfoModel:
            updateModelValue();
            bRet = true;
            break;
        case AplParamInfoSerialNo:
            updateSerialNoValue(); 
            bRet = true;
            break;
        case AplParamInfoVersion:     
            updateVersionValue();
            bRet = true;
            break;
        case AplParamBeSoftVer:
            updateBeSoftValue();
            bRet = true;
            break;
        case AplParamCamSoftVer:
            updateCamSoftValue();
            bRet = true;
            break;
        case AplParamActSoftVer:
            updateActSoftValue();
            bRet = true;
            break;
        case AplParamFpgaVer:
            updateFpgaValue();
            bRet = true;
            break;

        default:
            break;
    }

    return bRet;
}
