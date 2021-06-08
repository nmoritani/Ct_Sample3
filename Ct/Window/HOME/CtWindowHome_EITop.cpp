/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */

#include "CtWindowHome_EITop.h"

CtWindow* CtWindowHome_EITop::createWindow()
{
	m_LabelColor = CtColor(71,72,74,0xff);		// Gray
	m_ImageColor = CtColor(240,240,240,0xff);	// White
	m_LineColor = CtColor(40, 41, 44, 0xff);	// BoundaryColor 紺色
	m_pWin = new CtWindow();
#if 0
	//////////// UPPER ////////////
	/*                                                                                    */
	/*  |<---------(319)----------|6|---------(314)-------|6|-----------(319)----------->|  */
	/*  | 3 (addStretch )         | |                     | |                            |  */
	/*  |-------------------------|-|---------------------| |--------------------------- |  */
	/*  | 60                      | |                     | |                            |  BtnLayout*/
	/*  |-------------------------|-|---------------------| |----------------------------|  */
	/*  | 50                      | |                     | |                            |  BtnNameLayout*/
	/*  |_________________________|_|_____LayoutUpper_____| |____________________________|  */
	/*  |314 ( addStretch  )                                                             |  */
	/*  |_______________________________LayoutLower______________________________________|  */
	/*  |                         | |                      | |                           |  */
	/*  |50                       |6|                      |6|                           |  BtnNameLayout*/
	/*  |-------------------------| |----------------------| |---------------------------|  */
	/*  |60                       | |                      | |                           |  BtnLayout*/
	/*  |-------------------------| |----------------------| |-------------------------- |  */
	/*  |3(addStretch )           | |                      | |                           |  */
	/*  |<---------(319)----------| |----------(314)-------| |-----------(319)---------->|  */

	//////////////////////////////// NAME COMMON RESOURCE ///////////////////////////////////////
	CtFontSet fNameSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	//////////////////////////////// VALUE COMMON RESOURCE ///////////////////////////////////////
	CtFontSet fBtnSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);
	
	//Upper
	//////////// VALUE LEFT ////////////
	createNativeIsoValue();
	create800IsoValue();
	create2500IsoValue();
	createGainValue();
	
	CtLayout* pLayoutValueLeft = new CtLayout();
	pLayoutValueLeft->addWidget(m_pStackLeftValueNativeISO, AlignRight);
	pLayoutValueLeft->addWidget(m_pStackLeftValue800BaseISO, AlignRight);
	pLayoutValueLeft->addWidget(m_pStackLeftValue2500BaseISO, AlignRight);
	pLayoutValueLeft->addWidget(m_pStackLeftValueGAIN);
	
//	m_pButtonUpperLeft = new CtLinkButton(WindowID_Menu_NATIVE_ISO, OpenPopup, CtSize(312, 60), pLayoutValueLeft, None);
	m_pButtonUpperLeft->setImage(IC_TOP_LEFT);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//	m_pButtonUpperLeft->setLabelColorStyle(CtColor::Black);
	//m_pButtonUpperLeft->setColorStyle(m_ImageColor);

	//////////// VALUE CENTER ////////////
	m_pStackCenterValueISO = new CtStackLabel();
	m_pStackCenterValueISO->addLabel(new CtLabel( STR_ID_NO_10970, fBtnSet));	//「NATIVE ONLY」
	m_pStackCenterValueISO->addLabel(new CtLabel( STR_ID_NO_10971, fBtnSet));	//「800BASE」
	m_pStackCenterValueISO->addLabel(new CtLabel( STR_ID_NO_10197, fNameSet));	//ダミー [3200BaseのEnum値、未使用のため]
	m_pStackCenterValueISO->addLabel(new CtLabel( STR_ID_NO_10194, fBtnSet));	//STR_ID_NO_10972
	m_pStackCenterValueISO->setVisible(false);

	m_pStackCenterValueGAIN = new CtStackLabel();
	m_pStackCenterValueGAIN->addLabel(new CtLabel( STR_ID_NO_10973, fBtnSet));	// 「NORMAL」
	m_pStackCenterValueGAIN->addLabel(new CtLabel( STR_ID_NO_10974, fBtnSet));	// 「HIGH」
	m_pStackCenterValueGAIN->setVisible(false);

	CtLayout* pLayoutCenter = new CtLayout();
	pLayoutCenter->addWidget(m_pStackCenterValueISO);
	pLayoutCenter->addWidget(m_pStackCenterValueGAIN);

	m_pButtonUpperCenter = new CtLinkButton(WindowID_Menu_ISO_SELECT, OpenPopup,CtSize(312, 60), pLayoutCenter, None);
	m_pButtonUpperCenter->setImage(IC_TOP_CENTER);
	//m_pButtonUpperCenter->setColorStyle(m_ImageColor);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//	m_pButtonUpperCenter->setLabelColorStyle(CtColor::Black);

	//////////// VALUE RIGHT ////////////
	CtLabel* plabelUpperRight = new CtLabel(CtSize(312, 60), IC_TOP_RIGHT);

	//////////// VALUE LINE UP ////////////
	CtHLayout* pLayoutUpperValue = new CtHLayout(m_LabelColor);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget( m_pButtonUpperLeft, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget( m_pButtonUpperCenter, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget( plabelUpperRight, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);

	//////////// NAME LEFT ////////////
	m_pStackLeftNameISO = new CtStackLabel();
	m_pStackLeftNameISO->addLabel( new CtLabel( STR_ID_NO_10966, fNameSet));//STR_ID_NO_10195 [NATIVE ISO]
	m_pStackLeftNameISO->addLabel( new CtLabel( STR_ID_NO_10967, fNameSet));//STR_ID_NO_10198 [800BASE ISO]
	m_pStackLeftNameISO->addLabel( new CtLabel( STR_ID_MAX_SIZE, fNameSet));//ダミー [3200BaseのEnum値、未使用ため]
	m_pStackLeftNameISO->addLabel( new CtLabel( STR_ID_NO_10968, fNameSet));//STR_ID_NO_10204 [2500BASE ISO]
	m_pStackLeftNameISO->setVisible(false);
	m_pLabelLeftNameGAIN = new CtLabel(STR_ID_NO_10969, fNameSet);//STR_ID_NO_10214 [GAIN SELECT]
	m_pLabelLeftNameGAIN->setVisible(false);

	CtLayout* pLayoutLeftName = new CtLayout();
	pLayoutLeftName->addWidget(m_pStackLeftNameISO);
	pLayoutLeftName->addWidget(m_pLabelLeftNameGAIN);

	CtStackLabel* pLabelUpperBoundaryLeft = new CtStackLabel(CtSize(4, 18));
	pLabelUpperBoundaryLeft->setColor(m_LineColor);

	//////////// NAME CENTER ////////////
	m_pStackCenterNameISO_GAIN = new CtStackLabel();
	m_pStackCenterNameISO_GAIN->addLabel(new CtLabel( STR_ID_NO_10976, fNameSet));// GAIN MODE
	m_pStackCenterNameISO_GAIN->addLabel(new CtLabel( STR_ID_NO_10975, fNameSet));// ISO SELECT

	CtLabel* pLabelUpperBoundaryCenter = new CtLabel(CtSize(4, 18));

	pLabelUpperBoundaryCenter->setColor(m_LineColor);
	//////////// NAME RIGHT ////////////
	// none

	//////////// NAME LINE UP ////////////
	CtHLayout* pLayoutUpperName = new CtHLayout();
	pLayoutUpperName->addWidget( pLayoutLeftName, CtMargin( 0, 0), 319);
	pLayoutUpperName->addWidget( pLabelUpperBoundaryLeft, 4);
	pLayoutUpperName->addWidget( m_pStackCenterNameISO_GAIN, CtMargin( 0, 0), 314);
	pLayoutUpperName->addWidget( pLabelUpperBoundaryCenter, 4);
	pLayoutUpperName->addStretch(319);
	
	//////////// LOWER LAYOUT INTEG ////////////
	// Name用レイアウトとValue用レイアウトの統合
	CtVLayout* pLayoutUpper = new CtVLayout( m_LabelColor);
	pLayoutUpper->addStretch(3);
	pLayoutUpper->addWidget(pLayoutUpperValue, AlignCenter, 60);
	pLayoutUpper->addWidget(pLayoutUpperName, AlignCenter, 50);

	// LOWER
	//////////// VALUE LEFT ////////////
	CtLabel* plabelLowerLeft = new CtLabel(CtSize(312, 60), IC_TOP_RIGHT);

	//////////// VALUE CENTER ////////////
	CtLabel* plabelLowerCenter = new CtLabel(CtSize(312, 60), IC_AUDIO_BOTTOM_CENTER);
	
	//////////// VALUE RIGHT ////////////
	CtLinkButton* pButtonLowerRight = new CtLinkButton(WindowNone, Close, CtSize(312, 60), STR_ID_NO_10794, fBtnSet, None);
	pButtonLowerRight->setImage(IC_TOP_LEFT);
	//pButtonLowerRight->setColorStyle(m_ImageColor);
	//	pButtonLowerRight->setLabelColorStyle(CtColor::Black);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//	pButtonLowerRight->setLabelColorStyle(CtColor::Black);

	//////////// VALUE LINE UP ////////////
	CtHLayout* pLayoutLowerValue = new CtHLayout(m_LabelColor );
	
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(plabelLowerLeft, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(plabelLowerCenter, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(pButtonLowerRight, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	
	//////////// NAME LEFT ////////////
	CtLabel* pLabelLowerLeftBoundary = new CtLabel(CtSize(4, 18));
	CtLabel* pLabelLowerLeftName = new CtLabel("", fNameSet);
	pLabelLowerLeftBoundary->setColor(m_LineColor);

	//////////// NAME CENTER ////////////
	CtLabel* pLabelLowerCenterBoundary = new CtLabel(CtSize(4, 18));
	CtLabel* pLabelLowerCenterName = new CtLabel("", fNameSet);
	pLabelLowerCenterBoundary->setColor(m_LineColor);

	//////////// NAME RIGHT ////////////
	CtLabel* pLabelLowerRightName = new CtLabel("", fNameSet);
	
	//////////// NAME LINE UP ////////////
	CtHLayout *pLayoutLowerName = new CtHLayout(m_LabelColor); 
	pLayoutLowerName->addStretch(319);
	pLayoutLowerName->addWidget(pLabelLowerLeftBoundary, 4);
	pLayoutLowerName->addStretch(314);
	pLayoutLowerName->addWidget(pLabelLowerCenterBoundary, 4);
	pLayoutLowerName->addStretch(319);
	
	//////////// LOWER LAYOUT INTEG ////////////
	// Name用レイアウトとValue用レイアウトの統合
	CtVLayout* pLayoutLower = new CtVLayout(m_LabelColor);
	pLayoutLower->addWidget( pLayoutLowerName, AlignCenter, 50);
	pLayoutLower->addWidget( pLayoutLowerValue, AlignCenter, 60);
	pLayoutLower->addStretch(3);

	CtVLayout *pLayoutAll = new CtVLayout();
	pLayoutAll->addWidget( pLayoutUpper, 113);
	pLayoutAll->addStretch( 314);
	pLayoutAll->addWidget( pLayoutLower, 113);

	// init
	setGainIsoDisp( APL_PARAM_GET_DATA(AplParamGainIsoDispChg));

	m_pWin->addWidget(pLayoutAll);
	m_pWin->setRegion(CtRegion(0,0,960,540));
	m_pWin->setColor(CtColor::Black);
	m_pWin->setVisible(true);
	m_pWin->setLayout();
	//m_pWin->setName("CtWindowHome_EITop");
	m_pWin->setRoundFocus(true);
#endif
//	m_pWin->setInitialFocusType(FocusNormal);
	m_pWin->setDefaultFocus(m_pButtonUpperLeft);
	return m_pWin;
}

CtWindowHome_EITop::CtWindowHome_EITop()
{
	m_pWin = NULL;
	setClassType(CtClassType_LayoutMain);
}

bool CtWindowHome_EITop::handleParamEvent(const CtEventParam& Param){
	int t_Id = Param.getParamId();
    int int_Data = Param.getParamVal();

    switch(t_Id)
    {
	case AplParamGainIsoDispChg:
		setGainIsoDisp(int_Data);
		break;
	case AplParamISOSelect:  
		setIsoSelect(int_Data);
        break;
    case AplParamGainSwitch: 
		setGainSwitch(int_Data);
        break;
	case AplParamNativeISO:
		setNativeIso(int_Data);
		break;
	case AplParam800BaseISO:
		set800BaseIso(int_Data);
		break;
	case AplParam2500BaseISO:
		set2500BaseIso(int_Data);
		break;
	case AplParamGainSelect:
		setGainSelect(int_Data);
		break;
    default:
        return false;
        break;

    }
	return true;
}
bool CtWindowHome_EITop::handleButtonEvent(const CtEventButton& Button){
	return false;
}
bool CtWindowHome_EITop::handleKeyEvent(const CtEventKey& Key){
	bool result = false;
	if( CtEventKey::Press == Key.getKeyAction() ){
    	switch ( Key.getKeyCode() ) {
    	case CtEventKey::KeyCode_Exit:
        case CtEventKey::KeyCode_GripUser1:
			if ( NULL != m_pWin ) {
				m_pWin->requestWindow(WindowNone, Close,NULL);
				result = true;
			}
	    	break;
		default:
			break;
		}
	}
	return result;
}

bool CtWindowHome_EITop::handleTouchEvent(const CtEventTouch& Touch){
	return false;
}

void CtWindowHome_EITop::createGainValue(){
	m_pStackLeftValueGAIN = new CtStackLabel();
	m_pStackLeftValueGAIN->setVisible(false);
	CtFontSet fBtnSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);
    m_pStackLeftValueGAIN->addLabel(new CtLabel( "-12 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "-10 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "-8 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "-6 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "-4 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "-2 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "0 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "2 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "4 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "6 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "8 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "10 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "12 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "14 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "16 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "18 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "20 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "22 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "24 dB", fBtnSet));
	m_pStackLeftValueGAIN->addLabel(new CtLabel( "26 dB", fBtnSet));
}

void CtWindowHome_EITop::createNativeIsoValue(){
	m_pStackLeftValueNativeISO = new CtStackLabel();
	m_pStackLeftValueNativeISO->setVisible(false);
	CtFontSet fBtnSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);
	m_pStackLeftValueNativeISO->addLabel( new CtLabel( "800 ISO", fBtnSet));
	m_pStackLeftValueNativeISO->addLabel( new CtLabel( "3200 ISO", fBtnSet));
	m_pStackLeftValueNativeISO->addLabel( new CtLabel( "2500 ISO", fBtnSet));
	m_pStackLeftValueNativeISO->addLabel( new CtLabel( "400 ISO", fBtnSet));
	m_pStackLeftValueNativeISO->addLabel( new CtLabel( "1250 ISO", fBtnSet));
}
void CtWindowHome_EITop::create800IsoValue(){
	m_pStackLeftValue800BaseISO = new CtStackLabel();
	m_pStackLeftValue800BaseISO->setVisible(false);
	CtFontSet fBtnSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "200 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "250 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "320 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "400 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "500 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "640 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "800 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "1000 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "1250 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "1600 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "2000 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "2500 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "3200 ISO", fBtnSet));
	m_pStackLeftValue800BaseISO->addLabel( new CtLabel( "4000 ISO", fBtnSet));
}
void CtWindowHome_EITop::create2500IsoValue(){
	m_pStackLeftValue2500BaseISO = new CtStackLabel();
	m_pStackLeftValue2500BaseISO->setVisible(false);
	CtFontSet fBtnSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "640 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "800 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "1000 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "1250 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "1600 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "2000 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "2500 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "3200 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "4000 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "5000 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "6400 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "8000 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "10000 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "12800 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "16000 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "20000 ISO", fBtnSet));
	m_pStackLeftValue2500BaseISO->addLabel( new CtLabel( "25600 ISO", fBtnSet));
}
void CtWindowHome_EITop::setGainIsoDisp(int int_Data){
	switch( int_Data){
		case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN:
			setIsoDisp(false);
			setGainDisp(true);
			break;
		case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO:
			setGainDisp(false);
			setIsoDisp(true);
			break;
		default:
			break;
	}
	m_pStackCenterNameISO_GAIN->index(int_Data);
}
void CtWindowHome_EITop::setGainDisp(bool bDisp){
		m_pStackLeftValueGAIN->setVisible(bDisp);
		m_pLabelLeftNameGAIN->setVisible(bDisp);
		m_pStackCenterValueGAIN->setVisible(bDisp);
	if( bDisp){
		setGainSwitch(APL_PARAM_GET_DATA(AplParamGainSwitch));
		setGainSelect(APL_PARAM_GET_DATA(AplParamGainSelect));
//		m_pButtonUpperLeft->setOpenWindow( WindowID_Menu_GAIN_SELECT, OpenPopup, NULL);
////		m_pButtonUpperCenter->setOpenWindow( WindowID_Menu_GAIN_MODE, OpenPopup, NULL);
	}
}
void CtWindowHome_EITop::setIsoDisp(bool bDisp){
	m_pStackLeftNameISO->setVisible(bDisp);
	m_pStackCenterValueISO->setVisible(bDisp);
	if( bDisp){
		setIsoSelect(APL_PARAM_GET_DATA(AplParamISOSelect));
//		m_pButtonUpperCenter->setOpenWindow( WindowID_Menu_ISO_SELECT, OpenPopup, NULL);
	}else{
		m_pStackLeftValueNativeISO->setVisible(false);
		m_pStackLeftValue800BaseISO->setVisible(false);
		m_pStackLeftValue2500BaseISO->setVisible(false);
	}
}
		
void CtWindowHome_EITop::setIsoSelect(int int_Data){
	if( APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY == int_Data){
		m_pStackLeftValueNativeISO->index(APL_PARAM_GET_DATA( AplParamNativeISO ));
		m_pStackLeftValueNativeISO->setVisible(true);
		m_pStackLeftValue800BaseISO->setVisible(false);
		m_pStackLeftValue2500BaseISO->setVisible(false);
//		m_pButtonUpperLeft->setOpenWindow( WindowID_Menu_NATIVE_ISO, OpenPopup, NULL);
	}else if( APL_SYS_PARAM_ISO_SELECT_800BASE == int_Data){
		m_pStackLeftValueNativeISO->setVisible(false);
		m_pStackLeftValue800BaseISO->index(APL_PARAM_GET_DATA( AplParam800BaseISO ));
		m_pStackLeftValue800BaseISO->setVisible(true);
		m_pStackLeftValue2500BaseISO->setVisible(false);
//		m_pButtonUpperLeft->setOpenWindow( WindowID_Menu_800BASE_ISO, OpenPopup, NULL);
	}else if( APL_SYS_PARAM_ISO_SELECT_2500BASE == int_Data){
		m_pStackLeftValueNativeISO->setVisible(false);
		m_pStackLeftValue800BaseISO->setVisible(false);
		m_pStackLeftValue2500BaseISO->index(APL_PARAM_GET_DATA( AplParam2500BaseISO ));
		m_pStackLeftValue2500BaseISO->setVisible(true);
//		m_pButtonUpperLeft->setOpenWindow( WindowID_Menu_3200BASE_ISO, OpenPopup, NULL);
	}else{
		m_pStackLeftValueNativeISO->setVisible(false);
		m_pStackLeftValue800BaseISO->setVisible(false);
		m_pStackLeftValue2500BaseISO->setVisible(false);
		m_pButtonUpperLeft->setOpenWindow( WindowNone, Close, NULL);
	}
	m_pStackCenterValueISO->index(int_Data);
	m_pStackLeftNameISO->index(int_Data);
	
}

void CtWindowHome_EITop::setGainSwitch(int int_Data){
	m_pStackCenterValueGAIN->index(int_Data);
	setGainSelect(APL_PARAM_GET_DATA(AplParamGainSelect));
}

void CtWindowHome_EITop::setNativeIso(int int_Data){
	m_pStackLeftValueNativeISO->index(int_Data);
}
void CtWindowHome_EITop::set800BaseIso(int int_Data){
	m_pStackLeftValue800BaseISO->index(int_Data);
}
void CtWindowHome_EITop::set2500BaseIso(int int_Data){
	m_pStackLeftValue2500BaseISO->index(int_Data);
}
void CtWindowHome_EITop::setGainSelect(int int_Data){
	m_pStackLeftValueGAIN->index(int_Data);
}
