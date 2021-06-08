/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */

#include "CtWindowHome_ShutterTop.h"

CtWindow* CtWindowHome_ShutterTop::createWindow()
{
	m_pWin = new CtWindow();
	m_LabelColor = CtColor(71,72,74,0xff);// Gray
	m_ImageColor = CtColor(240,240,240,0xff);// White
	m_LineColor = CtColor(40, 41, 44, 0xff);// BoundaryColor 紺色

	////////////////////////////////// UPPER //////////////////////////////////
	/*                                                                                      */
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
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	//////////////////////////////// VALUE COMMON RESOURCE ///////////////////////////////////////
	CtFontSet fBtnSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);

	//Upper

	//////////////////////////////// VALUE LEFT ///////////////////////////////////////////////
	m_pUpperLeftValue = new CtStackLabel();
	m_pUpperLeftValue->addLabel(new CtLabel(STR_ID_NO_10009, fBtnSet));
	m_pLeftValue = new CtLabel("", fBtnSet);
	m_pUpperLeftValue->addLabel(m_pLeftValue);
	
	CtLayout* pLayoutUpperLeft = new CtLayout();
	pLayoutUpperLeft->addWidget(m_pUpperLeftValue, AlignCenter);

	m_pBtnUpperLeft = new CtLinkButton( WindowNone, OpenPopup, CtSize(312, 60), pLayoutUpperLeft, CtButton::None);
	m_pBtnUpperLeft->setImage(IC_TOP_LEFT);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//m	m_pBtnUpperLeft->setLabelColorStyle(CtColor::Black);
//	m_pBtnUpperLeft->setColorStyle(m_ImageColor);

	//////////////////////////////// VALUE CENTER ///////////////////////////////////////////////
	m_pStackUpperCenterValue = new CtStackLabel();
	m_pStackUpperCenterValue->addLabel(new CtLabel( STR_ID_NO_10009, fBtnSet));// OFF
	m_pStackUpperCenterValue->addLabel(new CtLabel( STR_ID_NO_10008, fBtnSet));// ON
	
	CtLayout* pLayoutUpperCenter = new CtLayout();
	pLayoutUpperCenter->addWidget( m_pStackUpperCenterValue);

	m_pBtnUpperCenter = new CtButton(CtSize(312, 60), pLayoutUpperCenter, CtButton::None);
	m_pBtnUpperCenter->setImage(IC_TOP_CENTER);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//m	m_pBtnUpperCenter->setLabelColorStyle(CtColor::Black);
	m_pBtnUpperCenter->setColor(m_ImageColor);

	//////////////////////////////// VALUE RIGHT ///////////////////////////////////////////////
	CtLabel* plabelUpperRight = new CtLabel(CtSize(312, 60), IC_TOP_RIGHT);

	//////////////////////////////// VALUE LINE UP ///////////////////////////////////////////////
	CtHLayout* pLayoutUpperValue = new CtHLayout(m_LabelColor);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget(m_pBtnUpperLeft, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget(m_pBtnUpperCenter, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget(plabelUpperRight, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);

	//////////////////////////////// NAME LEFT //////////////////////////////////////////////////
	CtLabel* pLabelUpperBoundaryLeft = new CtLabel(CtSize(4, 18));
	CtLabel* pLabelUpperLeftName = new CtLabel(STR_ID_NO_10963, fSet);// "VALUE"
	pLabelUpperBoundaryLeft->setColor(m_LineColor);
	
	//////////////////////////////// NAME CENTER ////////////////////////////////////////////////
	CtLabel* pLabelUpperCenterName = new CtLabel(STR_ID_NO_10965, fSet);// "ON/OFF"
	CtLabel* pLabelUpperBoundaryCenter = new CtLabel(CtSize(4, 18));
	pLabelUpperCenterName->setColor(m_LineColor);

	//////////////////////////////// NAME RIGHT /////////////////////////////////////////////////
	
	//////////////////////////////// NAME LINE UP ////////////////////////////////////////////////
	CtHLayout* pLayoutUpperName = new CtHLayout(); 
	pLayoutUpperName->addWidget( pLabelUpperLeftName, CtMargin( 0, 0), 319);
	pLayoutUpperName->addWidget( pLabelUpperBoundaryLeft, 4);
	pLayoutUpperName->addWidget( pLabelUpperCenterName, CtMargin( 0, 0), 314);
	pLayoutUpperName->addWidget( pLabelUpperBoundaryCenter, 4);
	pLayoutUpperName->addStretch(319);
	
	//////////////////////////////// UPPER LAYOUT INTEG ///////////////////////////////////////////
	// Name用レイアウトとValue用レイアウトの統合
	CtVLayout* pLayoutUpper = new CtVLayout( m_LabelColor);
	pLayoutUpper->addStretch(3);
	pLayoutUpper->addWidget(pLayoutUpperValue, AlignCenter, 60);
	pLayoutUpper->addWidget(pLayoutUpperName, AlignCenter, 50);

	// LOWER
	//////////////////////////////// VALUE LEFT ///////////////////////////////////////////////
	CtLabel* plabelLowerLeft = new CtLabel(CtSize(312, 60), IC_TOP_RIGHT);

	//////////// VALUE CENTER ////////////
	CtLabel* plabelLowerCenter = new CtLabel(CtSize(312, 60), IC_AUDIO_BOTTOM_CENTER);

	//////////////////////////////// VALUE RIGHT ///////////////////////////////////////////////
	CtLinkButton* pButtonLowerRight = new CtLinkButton(WindowNone, Close, CtSize(312, 60), STR_ID_NO_10794, fBtnSet, CtButton::None);
	pButtonLowerRight->setImage(IC_TOP_LEFT);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//pButtonLowerRight->setColorStyle(m_ImageColor);
	//m	pButtonLowerRight->setLabelColorStyle(CtColor::Black);

	//////////////////////////////// VALUE LINE UP ///////////////////////////////////////////////
	CtHLayout* pLayoutLowerValue = new CtHLayout(m_LabelColor );
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(plabelLowerLeft, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(plabelLowerCenter, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(pButtonLowerRight, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	
	//////////////////////////////// NAME LEFT //////////////////////////////////////////////////
	CtLabel* pLabelLowerLeftBoundary = new CtLabel(CtSize(4, 18));
	pLabelLowerLeftBoundary->setColor(m_LineColor);

	//////////////////////////////// NAME RIGHT /////////////////////////////////////////////////
	
	//////////////////////////////// NAME CENTER ////////////////////////////////////////////////
	CtLabel* pLabelLowerCenterBoundary = new CtLabel(CtSize(4, 18));
	pLabelLowerCenterBoundary->setColor(m_LineColor);

	//////////////////////////////// NAME LINE UP ////////////////////////////////////////////////
	CtHLayout *pLayoutLowerName = new CtHLayout(m_LabelColor); 
	pLayoutLowerName->addStretch(319);
	pLayoutLowerName->addWidget(pLabelLowerLeftBoundary, 4);
	pLayoutLowerName->addStretch(314);
	pLayoutLowerName->addWidget(pLabelLowerCenterBoundary, 4);
	pLayoutLowerName->addStretch(319);
	
	//////////////////////////////// LOWER LAYOUT INTEG ///////////////////////////////////////////
	// Name用レイアウトとValue用レイアウトの統合
	CtVLayout* pLayoutLower = new CtVLayout(m_LabelColor);
	pLayoutLower->addWidget( pLayoutLowerName, AlignCenter, 50);
	pLayoutLower->addWidget( pLayoutLowerValue, AlignCenter, 60);
	pLayoutLower->addStretch(3);
	
	CtVLayout *pLayoutAll = new CtVLayout();
	pLayoutAll->addWidget( pLayoutUpper, 113);
	pLayoutAll->addStretch( 314);
	pLayoutAll->addWidget( pLayoutLower, 113);
	
	setShutterSwitch(APL_PARAM_GET_DATA(AplParamShutterSwitch));
	
	m_pWin->addWidget(pLayoutAll);
	m_pWin->setRegion(CtRegion(0,0,960,540));
	m_pWin->setColor(CtColor::Black);
	m_pWin->setVisible(true);
	m_pWin->setLayout();
	//m_pWin->setName("CtWindowHome_ShutterTop");
	m_pWin->setRoundFocus(true);

//	m_pWin->setInitialFocusType(FocusNormal);
	m_pWin->setDefaultFocus(m_pBtnUpperLeft);

	return m_pWin;
}

CtWindowHome_ShutterTop::CtWindowHome_ShutterTop()
{
	m_pWin = NULL;
	setClassType(CtClassType_LayoutMain);
}

bool CtWindowHome_ShutterTop::handleButtonEvent(const CtEventButton& Button){
	/* Releaseでのみ処理 */
	if( Button.getPressType() != CtEventButton::Release ){
		return false;
	}

	if( Button.getWidget() == m_pBtnUpperCenter){
		if(APL_PARAM_GET_DATA(AplParamShutterSwitch) == APL_SYS_PARAM_SWITCH_ON ){
			//ON⇒OFF
			APL_PARAM_SET_DATA(AplParamShutterSwitch, APL_SYS_PARAM_SWITCH_OFF );
		}else{
			//OFF⇒ON
			APL_PARAM_SET_DATA(AplParamShutterSwitch, APL_SYS_PARAM_SWITCH_ON );
		}
		return true;
	}
	return false;
}

bool CtWindowHome_ShutterTop::handleParamEvent(const CtEventParam& Param){
	int t_Id = Param.getParamId();
    int int_Data = Param.getParamVal();

    switch(t_Id){
		case AplParamShutterSwitch:
			setShutterSwitch( int_Data);
			break;
		case AplParamShutterDispChg:
			setShutterDisp(int_Data);
			break;
		case AplParamShutterDegValue:
		case AplParamShutterSecValue:
			setShutterValue();
		default:
			return false;
			break;
	}
	return true;
}

bool CtWindowHome_ShutterTop::handleKeyEvent(const CtEventKey& Key){
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
bool CtWindowHome_ShutterTop::handleTouchEvent(const CtEventTouch& Touch){
	return false;
}

void CtWindowHome_ShutterTop::setShutterSwitch(int int_Data){
	if( int_Data == APL_SYS_PARAM_SWITCH_ON){
		setShutterDisp(APL_PARAM_GET_DATA( AplParamShutterDispChg ));
	}else{
		m_pUpperLeftValue->index(0);
		m_pBtnUpperLeft->setOpenWindow( WindowNone, OpenPopup, NULL);
	}
	m_pStackUpperCenterValue->index( int_Data);
}

void CtWindowHome_ShutterTop::setShutterDisp(int int_Data){
	if( APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND == int_Data){
//		m_pBtnUpperLeft->setOpenWindow( WindowID_Menu_SHUTTER_SEC_VALUE, OpenPopup, NULL);
	}else{
//		m_pBtnUpperLeft->setOpenWindow( WindowID_Menu_SHUTTER_DEG_VALUE, OpenPopup, NULL);
	}
	setShutterValue();
}

void CtWindowHome_ShutterTop::setShutterValue(){
	
	char str[16] = {0};
    if( APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND == APL_PARAM_GET_DATA( AplParamShutterDispChg )){
        int temp_Int = (int)( APL_PARAM_GET_DATA( AplParamShutterSecValue ) / 10 );
        int temp_Sec = APL_PARAM_GET_DATA( AplParamShutterSecValue ) % 10;
		char* temp_UnitSec = "sec";
    	if( temp_Int >= 180 ){
            sprintf( str, "1/%d%s", temp_Int, temp_UnitSec);
    	} else {
            sprintf( str, "1/%d.%d%s", temp_Int, temp_Sec, temp_UnitSec);
    	}
	}else{
		int temp_Int = (int)( APL_PARAM_GET_DATA( AplParamShutterDegValue ) / 10 );
		int temp_Dec = APL_PARAM_GET_DATA( AplParamShutterDegValue ) % 10;
		char* temp_deg = "deg";
		sprintf( str, "%d.%d%s", temp_Int, temp_Dec, temp_deg );
	}
	m_pLeftValue->setText(str);
	m_pUpperLeftValue->index(1);
}
