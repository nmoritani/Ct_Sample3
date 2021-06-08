/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoDiagnosticsMiddle
 */

#include "CtInfoDiagnosticsMiddle.h"
#include "CtLabel.h"
#include "apl_sys_param_enum.h"
#include "AplParamService.h"
#include "stdio.h"
#include "str_id.h"
#include "string_api.h"
#include "CtLanguage.h"

CtInfoDiagnosticsMiddle::CtInfoDiagnosticsMiddle() :
    m_pBox(NULL),
    m_pInfoError(NULL),
    m_pInfoError2nd(NULL),
    m_pWarningValue(NULL),
    m_pWarning2ndValue(NULL),
    m_pAlertValue(NULL),
    m_pWarning_AlertValue_Non(NULL),
    m_pTotalOperationValue(NULL),
    m_pWarning_Alert2nd(NULL),
    m_pIrisDialValue(NULL)
{
    setClassType(CtClassType_LayoutMain);
}

CtLayout* CtInfoDiagnosticsMiddle::createContainer()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fCenterSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);

    m_pWarningValue = new CtStackLabel();
    m_pWarning2ndValue = new CtStackLabel();
    m_pAlertValue = new CtStackLabel();
    m_pInfoError = new CtStackLabel();
    m_pInfoError2nd = new CtStackLabel();
    m_pWarning_AlertValue_Non = new CtLabel(STR_ID_NO_10768, fSet); //StringID "Non"
    m_pTotalOperationValue = new CtLabel("", fSet);
    m_pIrisDialValue = new CtLabel("", fSet);

    /*  set stacklabel's value*/
    setWarningLabel(m_pWarningValue);
	setWarning2ndLabel(m_pWarning2ndValue);
    setAlertLabel(m_pAlertValue);
    setInfoErrorLabel(m_pInfoError);
    setInfoErrorLabel(m_pInfoError2nd);

    m_pBox = new CtVLayout();
    const char string[] = ":";

    /*InfoDiagnostics画面の情報部品を作成する*/
    CtHLayout *pWarning_Alert = new CtHLayout();
	m_pWarning_Alert2nd = new CtHLayout();
    CtLayout *pWarning_AlertValue = new CtLayout();
    CtHLayout *pInfo_Error = new CtHLayout();
    CtHLayout *pInfo_Error2nd = new CtHLayout();
    CtHLayout *pTotalOperation = new CtHLayout();
    CtHLayout *pIrisDial = new CtHLayout();

    pWarning_Alert->addStretch(16);
    pWarning_Alert->addWidget(new CtLabel(STR_ID_NO_10692, fSet), 216);
    pWarning_Alert->addWidget(new CtLabel(string, fCenterSet), 16);
    pWarning_AlertValue->addWidget(m_pWarning_AlertValue_Non);
    pWarning_AlertValue->addWidget(m_pWarningValue);
    pWarning_AlertValue->addWidget(m_pAlertValue);
    pWarning_Alert->addWidget(pWarning_AlertValue, 712);

	m_pWarning_Alert2nd->addStretch(16);
	m_pWarning_Alert2nd->addStretch(216);
	m_pWarning_Alert2nd->addStretch(16);
	m_pWarning_Alert2nd->addWidget(m_pWarning2ndValue,712);

    pInfo_Error->addStretch(16);
    pInfo_Error->addWidget(new CtLabel(STR_ID_NO_10693, fSet), 216);
    pInfo_Error->addWidget(new CtLabel(string, fCenterSet), 16);
    pInfo_Error->addWidget(m_pInfoError, 712);

    pInfo_Error2nd->addStretch(16);
    pInfo_Error2nd->addStretch(216);
    pInfo_Error2nd->addStretch(16);
    pInfo_Error2nd->addWidget(m_pInfoError2nd, 712);

    pTotalOperation->addStretch(16);
    pTotalOperation->addWidget(new CtLabel(STR_ID_NO_10801, fSet),240);
    pTotalOperation->addWidget(new CtLabel(string, fCenterSet),16);
    pTotalOperation->addWidget(m_pTotalOperationValue,688);

    pIrisDial->addStretch(16);
    pIrisDial->addWidget(new CtLabel(STR_ID_NO_10802, fSet),240);
    pIrisDial->addWidget(new CtLabel(string, fCenterSet), 16);
    pIrisDial->addWidget(m_pIrisDialValue, 688);

	m_pBox->setElementsMargin(CtMargin(0,6,0,0));
    m_pBox->addStretch(11);					    // (0)
    m_pBox->addWidget(pWarning_Alert,48);	    // (1)
    m_pBox->addWidget(m_pWarning_Alert2nd,48);  // (2)
    m_pBox->addWidget(pInfo_Error,48);		    // (3)
    m_pBox->addWidget(pInfo_Error2nd,48);		// (4)
    m_pBox->addWidget(pTotalOperation,48);	    // (5)
    m_pBox->addWidget(pIrisDial,48);		    // (6)
    m_pBox->addStretch(13);					    // (7)

    m_pBox->setName("@@@CtInfoDiagnosticsMiddle@@@");

    /*AplParamの設定値により画面の表示情報を更新する*/
    updateWarning_Alert();
    updateInfo_Error();
    updateTotalOperation();
    updateIrisDial();

    return m_pBox;
}

bool CtInfoDiagnosticsMiddle::destroyContainer() {
	return true;
}

CtInfoDiagnosticsMiddle::~CtInfoDiagnosticsMiddle()
{
}

void CtInfoDiagnosticsMiddle::setWarningLabel(CtStackLabel *pWarningValue)
{
    if (NULL == pWarningValue) {
        return;
    }
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10768, fSet, CtMargin(4)));       //StringID             "None"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10736, fSet, CtMargin(4)));       //StringID             "LOW_BATTERY"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10737, fSet, CtMargin(4)));       //StringID             "FAN_STOPPED"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10768, fSet, CtMargin(4)));       //StringID             "HIGH_TEMP"->"Non"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10738, fSet, CtMargin(4)));       //StringID             "REC_WARNING"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10739, fSet, CtMargin(4)));       //StringID             "CARD_ERROR"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10768, fSet, CtMargin(4)));       //StringID             "NO_REMAIN -> Non"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10768, fSet, CtMargin(4)));       //StringID             "BATTERY_NEAR_END"->"Non"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10768, fSet, CtMargin(4)));       //StringID             "REMAIN_LESS_2MIN"->"Non"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10739, fSet, CtMargin(4)));       //StringID             "CARD ERROR"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10739, fSet, CtMargin(4)));       //StringID             "CARD ERROR"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10739, fSet, CtMargin(4)));       //StringID             "CARD ERROR"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10739, fSet, CtMargin(4)));       //StringID             "CARD ERROR"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10739, fSet, CtMargin(4)));       //StringID             "CARD ERROR"
	
}

void CtInfoDiagnosticsMiddle::setWarning2ndLabel(CtStackLabel *pWarningValue)
{
	int len = 0;
	int len12 = 0;
	char str[50];
	unsigned short *gdistr = NULL;
	unsigned short slot1[50];
	unsigned short slot2[50];
	unsigned short slot12[50];
	memset(str,0,sizeof(str));
	memset(slot1,0,sizeof(slot1));
	memset(slot2,0,sizeof(slot2));
	memset(slot12,0,sizeof(slot12));

    if (NULL == pWarningValue) {
        return;
    }

	/* Build String [ <SLOT1> ] [ <SLOT2> ] */
	sprintf(str,"<");
	for( int i = 0 ; str[i] ; i++){
		slot1[len+i] = (unsigned short)str[i];
		slot2[len+i] = (unsigned short)str[i];
	}
	len = get_ushort_string_length( slot1 );
	gdistr = GDI_GetString( CtLanguage::getLanguageID(), STR_ID_NO_10892 );	// "SLOT1" [S:10892]SLOT 
	for (int i = 0; gdistr[i]; i++){
		slot1[len] = gdistr[i];
		slot2[len] = gdistr[i];
		len++;
    }
	sprintf(str,"1>");
	for( int i = 0 ; str[i] ; i++){
		slot1[len+i] = (unsigned short)str[i];
	}
	sprintf(str,"2>");
	for( int i = 0 ; str[i] ; i++){
		slot2[len+i] = (unsigned short)str[i];
	}
	len = get_ushort_string_length( slot1 );
	
	/* Build String [ <SLOT1> ] [ <SLOT2> ] */
	sprintf(str,"<");
	for( int i = 0 ; str[i] ; i++){
		slot12[len12+i] = (unsigned short)str[i];
	}
	len12 = get_ushort_string_length( slot12 );
	gdistr = GDI_GetString( CtLanguage::getLanguageID(), STR_ID_NO_10892 );	// "SLOT1" [S:10892]SLOT 
	for (int i = 0; gdistr[i]; i++){
		slot12[len12++] = gdistr[i];
    }
	sprintf(str,"1,2>");
	for( int i = 0 ; str[i] ; i++){
		slot12[len12++] = (unsigned short)str[i];
	}

    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    pWarningValue->addLabel(new CtLabel( ""            , fSet, CtMargin(4)));       //StringID         表示無し
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10884, fSet, CtMargin(4)));       //StringID         [S:10884]<OVER MAX NUM. OF CLIPS>
    pWarningValue->addLabel(new CtLabel( slot1         , fSet, CtMargin(4)));       //StringID         <[S:10892]SLOT1>
    pWarningValue->addLabel(new CtLabel( slot2         , fSet, CtMargin(4)));       //StringID         <[S:10892]SLOT2>
    pWarningValue->addLabel(new CtLabel( slot12        , fSet, CtMargin(4)));       //StringID         <[S:10892]SLOT1><[S:10892]SLOT2>

	/* Connect String */
	gdistr = GDI_GetString( CtLanguage::getLanguageID(), STR_ID_NO_10884 );	// [S:10884]<OVER MAX NUM. OF CLIPS>
	for( int i = 0 ; gdistr[i] ; i++ ){
		slot1[len+i] = gdistr[i];
		slot2[len+i] = gdistr[i];
		slot12[len12++] = gdistr[i];
	}

    pWarningValue->addLabel(new CtLabel( slot1         , fSet, CtMargin(4)));       //StringID         "<[S:10892]SLOT 1>[S:10884]<OVER MAX NUM. OF CLIPS>"
    pWarningValue->addLabel(new CtLabel( slot2         , fSet, CtMargin(4)));       //StringID         "<[S:10892]SLOT 2>[S:10884]<OVER MAX NUM. OF CLIPS>"
    pWarningValue->addLabel(new CtLabel( slot12        , fSet, CtMargin(4)));       //StringID         "<[S:10892]SLOT 1><[S:10892]SLOT 2>[S:10884]<OVER MAX NUM. OF CLIPS>"
    pWarningValue->addLabel(new CtLabel(STR_ID_NO_10886, fSet, CtMargin(4)));       //StringID         "<PLEASE SET TO CORRECT TIME>"
}

void CtInfoDiagnosticsMiddle::setAlertLabel(CtStackLabel *pAlertValue)
{
    if (NULL == pAlertValue) {
        return;
    }
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White); 
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10768, fSet, CtMargin(4)));      //StringID            "ALERT_NONE"->"Non" 
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10740, fSet, CtMargin(4)));      //StringID            "SUB_REC_WARNING"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10741, fSet, CtMargin(4)));      //StringID            "SIMUL_REC_WARNING"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10742, fSet, CtMargin(4)));      //StringID            "NOT_SDXC_CARD"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10743, fSet, CtMargin(4)));      //StringID            "NOT_SUPPORT_CARD"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10744, fSet, CtMargin(4)));      //StringID            "REC_IMPOSSIBLE_CARD"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10745, fSet, CtMargin(4)));      //StringID            "FORMAT_ERROR_CARD"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10746, fSet, CtMargin(4)));      //StringID            "INCOMPATIBLE_CARD"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10747, fSet, CtMargin(4)));      //StringID            "BACKUP_BATT_EMPTY"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10894, fSet, CtMargin(4)));      //StringID            "BACKGROUND REC WARNING"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10737, fSet, CtMargin(4)));      //StringID            "FAN STOPPED"
    pAlertValue->addLabel(new CtLabel(STR_ID_NO_10885, fSet, CtMargin(4)));      //StringID            "INTERNAL CLOCK HAS RESET"
}

void CtInfoDiagnosticsMiddle::setInfoErrorLabel(CtStackLabel *pInfoError)
{
    if (NULL == pInfoError) {
        return;
    }
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    pInfoError->addLabel(new CtLabel("", fSet, CtMargin(4)));                    //Nodisp
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10768, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_NONE                      "ERROR_NONE"->"Non"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10663, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_ABB_NG                    "ABB NG"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10694, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_ABB_NG_TIME_OVER          "ABB NG <TIME OVER>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10695, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_ABB_NG_SELECT_TEST_SIG    "ABB NG <SELECT TEST SIG>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10696, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_ABB_NG_LENS_NOT_CLOSE     "ABB NG <LENS NOT CLOSE>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10697, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_AWB_NG_TIME_OVER          "AWB NG <TIME OVER>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10698, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_AWB_NG_SELECT_TEST_SIG    "AWB NG <SELECT TEST SIG>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10699, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_AWB_NG_COL_TEMP_LOW       "AWB NG <COLOR TEMP LOW>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10700, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_AWB_NG_COL_TEMP_HIGH      "AWB NG <COLOR TEMP HIGH>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10921, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_AWB_NG_GMG_OVER           "AWB NG <GMg OVER>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10701, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_AWB_NG_LEVEL_OVER         "AWB NG <LEVEL OVER>"
    pInfoError->addLabel(new CtLabel(STR_ID_NO_10702, fSet, CtMargin(4)));       //StringID            APL_SYS_PARAM_INFOERR_AWB_NG_LOW_LIGHT          "AWB NG <LOW LIGHT>"
}

void CtInfoDiagnosticsMiddle::updateWarning_Alert(){
    signed int nTempWarning = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamWarning));
    signed int nTempAlert = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamAlert));
    m_pWarningValue->index(nTempWarning);
    m_pAlertValue->index(nTempAlert);

	/* BOX更新 */
	if( get2ndWarningAlert() == CtInfoDiagnosticsMiddle::Warning2nd_None ){
		m_pWarning2ndValue->setVisible(false);
	} else {
		m_pWarning2ndValue->index(get2ndWarningAlert());
		m_pWarning2ndValue->setVisible(true);
	}
    if(true == isDispWarning()){
        m_pWarningValue->setVisible(true);
        m_pAlertValue->setVisible(false);
        m_pWarning_AlertValue_Non->setVisible(false);
    }else if(true == isDispAlert()){
        m_pWarningValue->setVisible(false);
        m_pAlertValue->setVisible(true);
        m_pWarning_AlertValue_Non->setVisible(false);
    }else{
        m_pWarningValue->setVisible(false);
        m_pAlertValue->setVisible(false);
        m_pWarning_AlertValue_Non->setVisible(true);
    }
	
}

void CtInfoDiagnosticsMiddle::updateInfo_Error(){
    m_pInfoError ->index(get1stInfoErr());
    m_pInfoError2nd ->index(get2ndInfoErr());
}

void CtInfoDiagnosticsMiddle::updateTotalOperation(){
    char string[10];
    memset(string,0,sizeof(string));
    signed int nTempTotalOperationValue = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamInfoTotalOperation));
	if( nTempTotalOperationValue > 999999 ){
		nTempTotalOperationValue = 999999;
	}
    sprintf(string,"%dh",nTempTotalOperationValue);
    m_pTotalOperationValue->setText(string);
}

void CtInfoDiagnosticsMiddle::updateIrisDial(){
    char string[10];
    memset(string,0,sizeof(string));
    signed int nTempIrisDialValue = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamInfoIrisDial));
	nTempIrisDialValue = (nTempIrisDialValue / 100) * 100;
	if( nTempIrisDialValue > 99900 ){
		nTempIrisDialValue = 99900;
	}
    sprintf(string,"%dT",nTempIrisDialValue);
    m_pIrisDialValue->setText(string);
}

bool CtInfoDiagnosticsMiddle::handleParamEvent(const CtEventParam& Param){
    bool bRet = false;
    int t_Id = Param.getParamId();
    
    switch(t_Id){
        case AplParamWarning:
        case AplParamAlert:
        case AplParamSlot2ErrStatus:
        case AplParamSlot1ErrStatus:
        case AplParamAlertIncompatibleCardSd1:
        case AplParamAlertIncompatibleCardSd2:
            updateWarning_Alert();
            bRet = true;
            break;
        case AplParamInfoErr:
	    case AplParamABBErrInfo:
	    case AplParamAWBErrInfo:
            updateInfo_Error(); 
            bRet = true;
            break;
        case AplParamInfoTotalOperation:     
            updateTotalOperation();
            bRet = true;
            break;
        case AplParamInfoIrisDial:
            updateIrisDial();
            bRet = true;
            break;

        default:
            break;
    }

    return bRet;
}

bool CtInfoDiagnosticsMiddle::isDispWarning(){

	int warning = APL_PARAM_GET_DATA( AplParamWarning );
	
	switch( warning ){
	case APL_SYS_PARAM_WARNING_NONE:
		break;
	case APL_SYS_PARAM_WARNING_LOW_BATTERY:
		return true;
	case APL_SYS_PARAM_WARNING_FAN_STOPPED:
		return true;
	case APL_SYS_PARAM_WARNING_HIGH_TEMP:
		break;
	case APL_SYS_PARAM_WARNING_REC_WARNING:
		return true;
	case APL_SYS_PARAM_WARNING_CARD_ERROR:
		return true;
	case APL_SYS_PARAM_WARNING_NO_REMAIN:
		break;
	case APL_SYS_PARAM_WARNING_BATTERY_NEAR_END:
		break;
	case APL_SYS_PARAM_WARNING_REMAIN_LESS_2MIN:
		break;
	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING:
		return true;
	case APL_SYS_PARAM_WARNING_CARD_ERROR_SLOT1:
		return true;
	case APL_SYS_PARAM_WARNING_CARD_ERROR_SLOT2:
		return true;
	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING_SLOT1:
		return true;
	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING_SLOT2:
		return true;
	default:
		break;
	}

	return false;

}

bool CtInfoDiagnosticsMiddle::isDispAlert(){

	int alert = APL_PARAM_GET_DATA( AplParamAlert );

	switch( alert ){
	case APL_SYS_PARAM_ALERT_NONE:
		break;
	case APL_SYS_PARAM_ALERT_SUB_REC_WARNING:
		return true;
	case APL_SYS_PARAM_ALERT_SIMUL_REC_WARNING:
		return true;
	case APL_SYS_PARAM_ALERT_NOT_SDXC_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_REC_IMPOSSIBLE_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD:
		return true;
	case APL_SYS_PARAM_ALERT_BACKUP_BATT_EMPTY:
		return true;
	case APL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING:
		return true;
	case APL_SYS_PARAM_ALERT_FAN_STOPPED:
		return true;
	case APL_SYS_PARAM_ALERT_CLOCK_RESET:
		return true;
	default:
		break;
	}

	return false;
}

CtInfoDiagnosticsMiddle::Warning2nd CtInfoDiagnosticsMiddle::get2ndWarningAlert(){

	int warning = APL_PARAM_GET_DATA( AplParamWarning );
	int alert = APL_PARAM_GET_DATA( AplParamAlert );
	
	int slot1_state = APL_PARAM_GET_DATA(AplParamSlot1ErrStatus);
	int slot2_state = APL_PARAM_GET_DATA(AplParamSlot2ErrStatus);

	switch( warning ){
	case APL_SYS_PARAM_WARNING_NONE:
		break;

	case APL_SYS_PARAM_WARNING_LOW_BATTERY:
		break;

	case APL_SYS_PARAM_WARNING_FAN_STOPPED:
		break;

	case APL_SYS_PARAM_WARNING_HIGH_TEMP:
		break;

	case APL_SYS_PARAM_WARNING_REC_WARNING:
		if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_OVER_CLIPS ){
			return CtInfoDiagnosticsMiddle::Warning2nd_OverMaxNum;
		} else if( slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_OVER_CLIPS ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_OverMaxNum;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_WARNING_CARD_ERROR:	//かつカード状態を判断
	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING:
		if( slot1_state != APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR && slot2_state != APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1_Slot2;
		} else if( slot1_state != APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;
		} else if( slot2_state != APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_WARNING_NO_REMAIN:
		break;

	case APL_SYS_PARAM_WARNING_BATTERY_NEAR_END:
		break;

	case APL_SYS_PARAM_WARNING_REMAIN_LESS_2MIN:
		break;

	case APL_SYS_PARAM_WARNING_CARD_ERROR_SLOT1:
		return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;

	case APL_SYS_PARAM_WARNING_CARD_ERROR_SLOT2:
		return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;

	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING_SLOT1:
		return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;

	case APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING_SLOT2:
		return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;

	default:
		break;
	}

	switch( alert ){
	case APL_SYS_PARAM_ALERT_NONE:
		break;

	case APL_SYS_PARAM_ALERT_SUB_REC_WARNING:	// かつ上限エラーか判断
		if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_OVER_CLIPS ){
			return CtInfoDiagnosticsMiddle::Warning2nd_OverMaxNum;
		} else if( slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_OVER_CLIPS ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_OverMaxNum;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_ALERT_SIMUL_REC_WARNING:	// かつどちらのカードか判断 // かつ上限も判断
		if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_OVER_CLIPS && slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_OVER_CLIPS ){
			return Warning2nd_Slot1_Slot2_OverMaxNum;
		} else if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_OVER_CLIPS ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1_OverMaxNum;
		} else if( slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_OVER_CLIPS ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot2_OverMaxNum;
		} else if(slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_SIMUL_ERROR && slot2_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_SIMUL_ERROR ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1_Slot2;
		} else if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_SIMUL_ERROR ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;
		} else if( slot2_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_SIMUL_ERROR ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_ALERT_NOT_SDXC_CARD:	// かつどちらのカードか判断
		if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SDXC && slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1_Slot2;
		} else if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SDXC ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;
		} else if( slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD:	// かつどちらのカードか判断
		if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SUPPORTED && slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1_Slot2;
		} else if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SUPPORTED ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;
		} else if( slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_ALERT_REC_IMPOSSIBLE_CARD:	// かつどちらのカードか判断
		if( slot1_state != APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR && slot2_state != APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1_Slot2;
		} else if( slot1_state != APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;
		} else if( slot2_state != APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_ERR ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD:	// かつどちらのカードか判断
		if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_FORMAT_ERROR && slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1_Slot2;
		} else if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_FORMAT_ERROR ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;
		} else if( slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD:	// かつどちらのカードか判断
		if( APL_PARAM_GET_DATA(AplParamAlertIncompatibleCardSd1) == APL_SYS_PARAM_SWITCH_ON && APL_PARAM_GET_DATA(AplParamAlertIncompatibleCardSd2) == APL_SYS_PARAM_SWITCH_ON ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1_Slot2;
		} else if( APL_PARAM_GET_DATA(AplParamAlertIncompatibleCardSd1) == APL_SYS_PARAM_SWITCH_ON ){
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot1;
		} else if( APL_PARAM_GET_DATA(AplParamAlertIncompatibleCardSd2) == APL_SYS_PARAM_SWITCH_ON ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_Slot2;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_ALERT_BACKUP_BATT_EMPTY:
		break;

	case APL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING:	// かつ上限判断
		if( slot1_state == APL_SYS_PARAM_SLOT1_ERR_STATUS_OVER_CLIPS ){
			return CtInfoDiagnosticsMiddle::Warning2nd_OverMaxNum;
		} else if( slot2_state == APL_SYS_PARAM_SLOT2_ERR_STATUS_OVER_CLIPS ) {
			return CtInfoDiagnosticsMiddle::Warning2nd_OverMaxNum;
		}
		return CtInfoDiagnosticsMiddle::Warning2nd_None;

	case APL_SYS_PARAM_ALERT_FAN_STOPPED:
		break;

	case APL_SYS_PARAM_ALERT_CLOCK_RESET:	// 必ず
		return CtInfoDiagnosticsMiddle::Warning2nd_ClockReset;
	default:
		break;
	}

	return CtInfoDiagnosticsMiddle::Warning2nd_None;

}

CtInfoDiagnosticsMiddle::InfoErr CtInfoDiagnosticsMiddle::get1stInfoErr()
{
	if( getAwbErr() != InfoErr_NONE ){
		return getAwbErr();
	} else if( getAbbErr() != InfoErr_NONE ){
		return getAbbErr();
	}
	return InfoErr_NONE;
}

CtInfoDiagnosticsMiddle::InfoErr CtInfoDiagnosticsMiddle::get2ndInfoErr()
{
	CtInfoDiagnosticsMiddle::InfoErr Err1st = get1stInfoErr();
	
	if( getAbbErr() != InfoErr_NONE && getAwbErr() != InfoErr_NONE ){
		return getAbbErr();
	}
	return InfoErr_NODISP;
}

CtInfoDiagnosticsMiddle::InfoErr CtInfoDiagnosticsMiddle::getAbbErr()
{
	switch( APL_PARAM_GET_DATA(AplParamABBErrInfo) ){
	case APL_SYS_PARAM_ABB_ERR_INFO_NONE:
		break;
	case APL_SYS_PARAM_ABB_ERR_INFO_ABB_NG:
		return InfoErr_ABB_NG;
	case APL_SYS_PARAM_ABB_ERR_INFO_ABB_NG_TIME_OVER:
		return InfoErr_ABB_NG_TIME_OVER;
	case APL_SYS_PARAM_ABB_ERR_INFO_ABB_NG_SELECT_TEST_SIG:
		return InfoErr_ABB_NG_SELECT_TEST_SIG;
	case APL_SYS_PARAM_ABB_ERR_INFO_ABB_NG_LENS_NOT_CLOSE:
		return InfoErr_ABB_NG_LENS_NOT_CLOSE;
	default:
		break;
	}
	return InfoErr_NONE;
}


CtInfoDiagnosticsMiddle::InfoErr CtInfoDiagnosticsMiddle::getAwbErr()
{
	switch( APL_PARAM_GET_DATA(AplParamAWBErrInfo) ){
	case APL_SYS_PARAM_AWB_ERR_INFO_NONE:
		break;
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_TIME_OVER:
		return InfoErr_AWB_NG_TIME_OVER;
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_SELECT_TEST_SIG:
		return InfoErr_AWB_NG_SELECT_TEST_SIG;
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_COL_TEMP_LOW:
		return InfoErr_AWB_NG_COL_TEMP_LOW;
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_COL_TEMP_HIGH:
		return InfoErr_AWB_NG_COL_TEMP_HIGH;
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_GMG_OVER:
		return InfoErr_AWB_NG_GMG_OVER;
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_LEVEL_OVER:
		return InfoErr_AWB_NG_LEVEL_OVER;
	case APL_SYS_PARAM_AWB_ERR_INFO_AWB_NG_LOW_LIGHT:
		return InfoErr_AWB_NG_LOW_LIGHT;
	}
	return InfoErr_NONE;
}