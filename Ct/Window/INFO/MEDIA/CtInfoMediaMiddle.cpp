/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoMediaMiddle
 */
#include "CtInfoMediaMiddle.h"
#include "CtLabel.h"
#include "apl_sys_param_enum.h"
#include "AplParamService.h"
#include "stdio.h"

CtInfoMediaMiddle::CtInfoMediaMiddle() :
    m_pBox(NULL),
    m_pSlot1Error(NULL),
    m_pSlot2Error(NULL),
    m_pSlot1Value(NULL),
    m_pSlot2Value(NULL),
    m_pSlot1Remain(NULL),
    m_pSlot2Remain(NULL)
{
    setClassType(CtClassType_LayoutMain);
}

    void CtInfoMediaMiddle::setStackLabel(CtStackLabel *m_pSLabel)
{
    if (NULL == m_pSLabel) {
        return;
    }
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    m_pSLabel->addLabel(new CtLabel("", fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10730, fSet, CtMargin(4)));   //StringID    "PROTECTED"
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10732, fSet, CtMargin(4)));   //StringID    "NOT SDXC"
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10727, fSet, CtMargin(4)));   //StringID    "NO CARD"
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10728, fSet, CtMargin(4)));   //StringID    "NOT SUPPORTED"
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10729, fSet, CtMargin(4)));   //StringID    "FORMAT ERROR"
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10731, fSet, CtMargin(4)));   //StringID    "NO REMAIN"

    /*          連番:16, バージョン:1.06, 変更日:2017/6/1 目的、内容:・INFO-MEDIA画面のスロット状態表示のREC IMPOSSIBLEを削除           */
    /*m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10733, fSet, CtMargin(4)));                 //StringID	                "REC IMPOSSIBLE"*/
}

CtLayout* CtInfoMediaMiddle::createContainer()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    m_pBox = new CtVLayout();
    m_pSlot1Value = new CtLabel("", fSet);
    m_pSlot2Value = new CtLabel("", fSet);
    m_pSlot1Remain = new CtLabel("", fSet);
    m_pSlot2Remain = new CtLabel("", fSet);

    m_pSlot1Error = new CtStackLabel();
    m_pSlot2Error = new CtStackLabel();

    setStackLabel(m_pSlot1Error);
    setStackLabel(m_pSlot2Error);

    /*InfoMedia画面の情報部品を作成する*/
    CtHLayout *pSlotTitle = new CtHLayout();
    CtHLayout *pSlot1 = new CtHLayout();
    CtLayout *pSlot1ValueLayout = new CtLayout();
    CtHLayout *pSlot2 = new CtHLayout();
    CtLayout *pSlot2ValueLayout = new CtLayout();

    pSlotTitle->addStretch(16);
    pSlotTitle->addWidget(new CtLabel(STR_ID_NO_10726,fSet), 366);
    pSlotTitle->addWidget(new CtLabel(STR_ID_NO_10787,fSet), 578);

    pSlot1->addStretch(16);
    pSlot1->addWidget(new CtLabel("1  :",fSet), 40);
    pSlot1->addStretch(16);
    pSlot1ValueLayout->addWidget(m_pSlot1Error);
    pSlot1ValueLayout->addWidget(m_pSlot1Value);
    pSlot1->addWidget(pSlot1ValueLayout, 310);
    pSlot1->addWidget(m_pSlot1Remain,578);

    pSlot2->addStretch(16);
    pSlot2->addWidget(new CtLabel("2  :",fSet), 40);
    pSlot2->addStretch(16);
    pSlot2ValueLayout->addWidget(m_pSlot2Error);
    pSlot2ValueLayout->addWidget(m_pSlot2Value);
    pSlot2->addWidget(pSlot2ValueLayout, 310);
    pSlot2->addWidget(m_pSlot2Remain,578);

    m_pBox->addStretch(12);
    m_pBox->addWidget(pSlotTitle,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pSlot1,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pSlot2,48);
    m_pBox->addStretch(180);

    m_pBox->setName("@@@CtInfoMediaMiddle@@@");

    /*AplParamの設定値により画面の表示情報を更新する*/
    updateSlot();

    return m_pBox;
}

bool CtInfoMediaMiddle::destroyContainer() {
	return true;
}

CtInfoMediaMiddle::~CtInfoMediaMiddle()
{
}

void CtInfoMediaMiddle::updateSlot(){
    signed int nTempSlot1Error = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSlot1ErrStatus));
    signed int nTempSlot1Remain = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSlot1Remain));
    signed int nTempSlot1RemainAll = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSlot1RemainAll));
    signed int nTempSlot2Error = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSlot2ErrStatus));
    signed int nTempSlot2Remain = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSlot2Remain));
    signed int nTempSlot2RemainAll = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSlot2RemainAll));
    char SlotValue[30];
    memset(SlotValue,0,sizeof(SlotValue));
    char RemainValue[30];
    memset(RemainValue,0,sizeof(RemainValue));

	/* Slot1 Value */
    m_pSlot1Error->index(nTempSlot1Error);
    if(0 == nTempSlot1Remain){
        sprintf(SlotValue,"%d%%",nTempSlot1Remain);
    }else{
        sprintf(SlotValue,"%d%%",((nTempSlot1Remain * 100) / nTempSlot1RemainAll));
    }
    m_pSlot1Value->setText(SlotValue);

	if( APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF != APL_PARAM_GET_DATA(AplParamSystemSdiRaw)){
		m_pSlot1Error->setVisible(false);
        m_pSlot1Value->setVisible(false);
	}else if( isErrorDispSlot1() == false ){
        m_pSlot1Error->setVisible(false);
        m_pSlot1Value->setVisible(true);
    }else{
        m_pSlot1Error->setVisible(true);
        m_pSlot1Value->setVisible(false);
    }
	
	/* Slot2 Value */
    m_pSlot2Error->index(nTempSlot2Error);
    if(0 == nTempSlot2Remain){
        sprintf(SlotValue,"%d%%",nTempSlot2Remain);
    }else{
        sprintf(SlotValue,"%d%%",((nTempSlot2Remain * 100) / nTempSlot2RemainAll));
    }
    m_pSlot2Value->setText(SlotValue);

	if( APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF != APL_PARAM_GET_DATA(AplParamSystemSdiRaw)){
		m_pSlot2Error->setVisible(false);
        m_pSlot2Value->setVisible(false);
	}else if( isErrorDispSlot2() == false ){
        m_pSlot2Error->setVisible(false);
        m_pSlot2Value->setVisible(true);
    }else{
        m_pSlot2Error->setVisible(true);
        m_pSlot2Value->setVisible(false);
    }
    
	/* Slot1 Slot2 Remain */
    if(APL_PARAM_GET_DATA(AplParamSystemSdiRaw) != APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF){
        m_pSlot1Remain->setStringID(STR_ID_NO_10792);	//OFF
        m_pSlot2Remain->setStringID(STR_ID_NO_10792);	//OFF
    } else {
        /* (2017.07.21) */
        /* Slot残量の少ない方に合わせる仕様動作はAPL側で実施している */
        /* GUIはそのまま表示すれば良い */
        if( isDispSlot1Remain() == false ){
            m_pSlot1Remain->setText("");
        } else {
	        sprintf(RemainValue,"%d/%dmin",nTempSlot1Remain, nTempSlot1RemainAll);
	        m_pSlot1Remain->setText(RemainValue);
        }
        if( isDispSlot2Remain() == false ){
            m_pSlot2Remain->setText("");
        } else {
	        sprintf(RemainValue,"%d/%dmin",nTempSlot2Remain, nTempSlot2RemainAll);
	        m_pSlot2Remain->setText(RemainValue);
        }
    }
}

bool CtInfoMediaMiddle::handleParamEvent(const CtEventParam& Param){
    bool bRet = false;
    int t_Id = Param.getParamId();
    
    switch(t_Id){
        case AplParamSlot1ErrStatus:
        case AplParamSlot1Remain:
        case AplParamSlot1RemainAll:
        case AplParamSlot2ErrStatus:
        case AplParamSlot2Remain:
        case AplParamSlot2RemainAll:
        case AplParamSystemSdiRaw:
        case AplParamSystemSubRec:
        case AplParamRelayBackup:
        case AplParamMediaSelect:
            updateSlot(); 
            bRet = true;
            break;
        default:
            break;
    }

    return bRet;
}

bool CtInfoMediaMiddle::isErrorDispSlot1()
{
	switch( APL_PARAM_GET_DATA(AplParamSlot1ErrStatus))
	{
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_WP:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SDXC:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_CARD:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SUPPORTED:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_FORMAT_ERROR:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_REMAIN:
		return true;
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_REC_IMPOSSIBLE:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_OVER_CLIPS:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_INCOMPATIBLE_CARD:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR:
	default:
		return false;
	}
}


bool CtInfoMediaMiddle::isErrorDispSlot2()
{
	switch( APL_PARAM_GET_DATA(AplParamSlot2ErrStatus))
	{
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_WP:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_CARD:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_REMAIN:
		return true;
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_REC_IMPOSSIBLE:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_OVER_CLIPS:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_INCOMPATIBLE_CARD:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR:
	default:
		return false;
	}
}



bool CtInfoMediaMiddle::isDispSlot1Remain()
{
	switch( APL_PARAM_GET_DATA(AplParamSlot1ErrStatus))
	{
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_CARD:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SUPPORTED:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_FORMAT_ERROR:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SDXC:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_WP:
		return false;
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_REMAIN:
	//case APL_SYS_PARAM_SLOT1_ERR_STATUS_REC_IMPOSSIBLE:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_OVER_CLIPS:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_INCOMPATIBLE_CARD:
	case APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR:
	default:
		return true;
	}
}


bool CtInfoMediaMiddle::isDispSlot2Remain()
{
	switch( APL_PARAM_GET_DATA(AplParamSlot2ErrStatus))
	{
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_CARD:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_WP:
		return false;
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_REMAIN:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_REC_IMPOSSIBLE:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_OVER_CLIPS:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_INCOMPATIBLE_CARD:
	case APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR:
	default:
		return true;
	}
}

