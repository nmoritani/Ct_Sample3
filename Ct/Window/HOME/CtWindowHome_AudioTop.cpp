/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindowHome_AudioTop.h"
#include "CtDebugPrint.h"
#include "CtWindowCommon.h"
#include "CtEventInterface.h"
#include "string_api.h"
#include "str_id.h"

CtColor CtWindowHome_AudioTop::LabelColor(71,72,74,0xff);
CtColor CtWindowHome_AudioTop::ImagColor(240,240,240,0xff);
CtColor CtWindowHome_AudioTop::CommonBaseColor(0,0,0,0xff);
CtColor CtWindowHome_AudioTop::CommonSelectStrokeColor(255,216,0,0xff);
CtColor CtWindowHome_AudioTop::LineColor(40, 41, 44, 0xff);


CtWindowHome_AudioTop::CtWindowHome_AudioTop() :
    m_pWin(NULL),
    m_pLabelCh1In(NULL),
    m_pLabelCh2In(NULL),
    m_pLabelInput1(NULL),
    m_pLabelInput2(NULL),
    m_pButtonCh1(NULL),
    m_pButtonCh2(NULL),
    m_pButtonSel1(NULL),
    m_pButtonSel2(NULL),
    m_pButtonExit(NULL),
    m_bFocused(CH1_INDEX),
    m_bFocusedCanMove(true),
    m_bTouchButton(true)
    
{
    setClassType(CtClassType_LayoutMain);

}


CtWindow* CtWindowHome_AudioTop::createWindow()
{
    m_pWin = new CtWindow();
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, ImagColor);
	/* m_PWin構築                                                                         */
	/*                                                                                    */
	/*  |<---------(319)----------|6|---------(314)-------|6|-----------(319)----------->|  */
	/*  | 3 (addStretch )         | |                     | |                            |  */
	/*  |-------------------------|-|---------------------| |--------------------------- |  */
	/*  | 60                      | |                     | |                            |  */
	/*  |-------------------------|-|---------------------| |----------------------------|  */
	/*  | 50                      | |                     | |                            |  */
	/*  |_________________________|_|_____LayoutUpper_____| |____________________________|  */
	/*  |314 ( addStretch  )                                                             |  */
	/*  |_______________________________LayoutButtom_____________________________________|  */
	/*  |                         | |                      | |                           |  */
	/*  |50                       |6|                      |6|                           |  */
	/*  |-------------------------| |----------------------| |---------------------------|  */
	/*  |60                       | |                      | |                           |  */
	/*  |-------------------------| |----------------------| |-------------------------- |  */
	/*  |3(addStretch )           | |                      | |                           |  */
	/*  |<---------(319)----------| |----------(314)-------| |-----------(319)---------->|  */

	/* LayoutUpper表示領域 */
    CtLayout *pLayout3BtnUpper = create3BtnLayoutTop(); 
    CtLayout *pLayout3TextUpper = create3BtnNameLayoutTop();
    CtVLayout *pLayoutUpper = new CtVLayout( LabelColor );
    
    pLayoutUpper->addStretch( 3 );
    pLayoutUpper->addWidget(pLayout3BtnUpper, AlignCenter, 60);
    pLayoutUpper->addWidget(pLayout3TextUpper, AlignCenter, 50);


	/* LayoutBottom表示領域 */
    CtLayout* pLayout3BtnDown = create3BtnLayoutBottom();
    CtLayout *pLayout3TextDown = create3BtnNameLayoutBottom();  
    CtVLayout *pLayoutDown = new CtVLayout( LabelColor );
    
    pLayoutDown->addWidget(pLayout3TextDown, AlignCenter, 50);
    pLayoutDown->addWidget(pLayout3BtnDown, AlignCenter, 60);
    pLayoutDown->addStretch( 3 );


    CtVLayout *pLayoutAll = new CtVLayout();
    
	pLayoutAll->addWidget(pLayoutUpper, 113);
	pLayoutAll->addStretch(314);
	pLayoutAll->addWidget(pLayoutDown, 113);
    m_pWin->addWidget(pLayoutAll);

    m_pWin->setRegion( CtRegion(0,0,960,540) );
    m_pWin->setColor( CommonBaseColor );
    m_pWin->setVisible(true);
    m_pWin->setLayout();
    //m_pWin->setName("CtWindowHome_AudioTop");
    
    //この画面に遷移してきたときはカーソルを表示する。
    m_pButtonCh1->setFocus();

    InitDisplay();

    return m_pWin;
}


/*  UpperLayout(下段）ボタン名 表示領域 */
CtLayout* CtWindowHome_AudioTop::create3BtnNameLayoutTop(){

	/* Layout構築                                                                         */
	/*  |-----------319-----------|-----------314---------|------------------319-------|  */
	/*  | 50                      4                       4                            |  */
	/*  |           CH1 IN        |          CH2 IN       |             addStretch     |  */
	/*  |_________________________|_______________________|____________________________|  */

    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, ImagColor);
    CtHLayout *pLayout = new CtHLayout(LabelColor ); 

    CtLabel *pLabel_Ch1 = new CtLabel(STR_ID_NO_10684, fSet);//CH1 IN
    CtLabel *pLabel_L1 = new CtLabel(CtSize(4, 18));
    CtLabel *pLabel_Ch2 = new CtLabel(STR_ID_NO_10685, fSet);//CH2 IN
    CtLabel *pLabel_L2 = new CtLabel(CtSize(4, 18));

	pLabel_L1->setColor(LineColor);
	pLabel_L2->setColor(LineColor);

    pLayout->addWidget(pLabel_Ch1, 319);
    pLayout->addWidget(pLabel_L1, 4);
    pLayout->addWidget(pLabel_Ch2, 314);
    pLayout->addWidget(pLabel_L2, 4);
    pLayout->addStretch( 319 );

    return pLayout;
}


/*  BottomLayout(上段）ボタン名 表示領域 */
CtLayout* CtWindowHome_AudioTop::create3BtnNameLayoutBottom(){

	/* Layout構築                                                                         */
	/*  |-----------319-----------|-----------314---------|------------------319-------|  */
	/*  | 50                      4                       4                            |  */
	/*  |       INPUT1 SEL        |       INPUT2 SEL      |           addStretch       |  */
	/*  |_________________________|_______________________|____________________________|  */

    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, ImagColor);
    CtHLayout *pLayout = new CtHLayout( LabelColor ); 

    CtLabel *pLabelInput1 = new CtLabel(STR_ID_NO_10686, fSet);//INPUT1 SEL
    CtLabel *pLabel_L1 = new CtLabel(CtSize(4, 18));
    CtLabel *pLabelInput2 = new CtLabel(STR_ID_NO_10687, fSet);//INPUT2 SEL
    CtLabel *pLabel_L2 = new CtLabel(CtSize(4, 18));

	pLabel_L1->setColor(LineColor);
	pLabel_L2->setColor(LineColor);

    pLayout->addWidget(pLabelInput1, 319);
    pLayout->addWidget(pLabel_L1, 4);
    pLayout->addWidget(pLabelInput2, 314);
    pLayout->addWidget(pLabel_L2, 4);
    pLayout->addStretch( 319 );

    return pLayout;
}


/*  UpperLayout(上段）ボタンのステータス 表示領域 */
CtLayout* CtWindowHome_AudioTop::create3BtnLayoutTop(){
    
	/* Layout構築                                                                           */
	/*  |-----------319-----------|-|----------314---------|-|-----------------319-------|  */
	/*  | 60                      |6|                      |6|                           |  */
	/*  |       CH1 IN            | |      CH2 IN          | |          addStretch       |  */
	/*  |_________________________|_|______________________|_|___________________________|  */

    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);
      
    m_pLabelCh1In= new CtStackLabel();
    m_pLabelCh1In->addLabel(new CtLabel(STR_ID_NO_10764, fSet));
    m_pLabelCh1In->addLabel(new CtLabel(STR_ID_NO_10798, fSet));

    m_pLabelCh2In= new CtStackLabel();
    m_pLabelCh2In->addLabel(new CtLabel(STR_ID_NO_10765, fSet));
    m_pLabelCh2In->addLabel(new CtLabel(STR_ID_NO_10798, fSet));
    m_pLabelCh2In->addLabel(new CtLabel(STR_ID_NO_10799, fSet));
    //CH1 IN
    CtVLayout *pLayoutCh1 = new CtVLayout();
    pLayoutCh1->addWidget(m_pLabelCh1In);
    
    m_pButtonCh1 = new CtButton(CtSize(312, 60), pLayoutCh1, CtButton::None);
    m_pButtonCh1->setImage(IC_TOP_LEFT);
	m_pButtonCh1->setColor(CommonSelectStrokeColor);

    //CH2 IN
    CtVLayout *pLayoutCh2 = new CtVLayout();
    pLayoutCh2->addWidget(m_pLabelCh2In);

    m_pButtonCh2 = new CtButton(CtSize(312, 60), pLayoutCh2, CtButton::None);
    m_pButtonCh2->setImage(IC_TOP_CENTER);
    m_pButtonCh2->setColor( ImagColor);
    //NULL
    CtVLayout *pLayoutNull = new CtVLayout();

    CtLabel *pLabelNull = new CtLabel(IC_TOP_RIGHT);
    pLabelNull->setColor(ImagColor);
    pLayoutNull->addWidget(pLabelNull);

    CtHLayout *pLayout = new CtHLayout( LabelColor ); 

    pLayout->addStretch( 6 );
    pLayout->addWidget(m_pButtonCh1, 312);
    pLayout->addStretch( 6 );
    pLayout->addWidget(m_pButtonCh2, 312);
    pLayout->addStretch( 6 );
    pLayout->addWidget(pLayoutNull, 312);
    pLayout->addStretch( 6 );

    m_Vector.push_back(m_pButtonCh1);
    m_Vector.push_back(m_pButtonCh2);
    
    return pLayout;
}


/*  BottomLayout(下段）ボタンのステータス 表示領域 */
CtLayout* CtWindowHome_AudioTop::create3BtnLayoutBottom(){
	
	/* Layout構築                                                                           */
	/*  |-----------319-----------|-|----------314---------|-|-----------------319-------|  */
	/*  | 60                      |6|                      |6|                           |  */
	/*  |       INPUT1 SEL        | |      INPUT2 SEL      | |              EXIT         |  */
	/*  |_________________________|_|______________________|_|___________________________|  */


    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);
    
    m_pLabelInput1 = new CtStackLabel();
    m_pLabelInput1->addLabel(new CtLabel(STR_ID_NO_10767, fSet));
    m_pLabelInput1->addLabel(new CtLabel(STR_ID_NO_10766, fSet));

    m_pLabelInput2 = new CtStackLabel();
    m_pLabelInput2->addLabel(new CtLabel(STR_ID_NO_10767, fSet));
    m_pLabelInput2->addLabel(new CtLabel(STR_ID_NO_10766, fSet));
    //INPUT1 SEL
    CtVLayout *pLayoutSel1 = new CtVLayout();
    pLayoutSel1->addWidget( m_pLabelInput1 );

    m_pButtonSel1 = new CtButton(CtSize(312, 60), pLayoutSel1, CtButton::None );
    m_pButtonSel1->setImage(IC_AUDIO_BOTTOM_LEFT);
    m_pButtonSel1->setColor( ImagColor);

    //  INPUT2 SEL  
    CtVLayout *pLayoutSel2 = new CtVLayout();
    pLayoutSel2->addWidget(m_pLabelInput2);

    m_pButtonSel2 = new CtButton(CtSize(312, 60), pLayoutSel2, CtButton::None);
    m_pButtonSel2->setImage(IC_AUDIO_BOTTOM_CENTER);
    m_pButtonSel2->setColor( ImagColor);

    //EXIT
    CtVLayout *pLayoutExit = new CtVLayout();
    CtLabel* p_LabelExit = new CtLabel(STR_ID_NO_10794, fSet);
    pLayoutExit->addWidget(p_LabelExit);

    m_pButtonExit = new CtButton(CtSize(312,60), pLayoutExit, CtButton::None);
    m_pButtonExit->setImage(IC_AUDIO_BOTTOM_RIGHT);
    m_pButtonExit->setColor( ImagColor);

    CtHLayout *pLayout = new CtHLayout( LabelColor ); 
    pLayout->addStretch( 6 );
    pLayout->addWidget(m_pButtonSel1, 312);
    pLayout->addStretch( 6 );
    pLayout->addWidget(m_pButtonSel2, 312);
    pLayout->addStretch( 6 );
    pLayout->addWidget(m_pButtonExit, 312);
    pLayout->addStretch( 6 );
    
    m_Vector.push_back(m_pButtonSel1);
    m_Vector.push_back(m_pButtonSel2);
    m_Vector.push_back(m_pButtonExit);

    return pLayout;
}


void CtWindowHome_AudioTop::InitDisplay()
{
    //m_pButtonCh1->setColorStyle( ImagColor );
	//m_pButtonCh2->setColorStyle( ImagColor );
	//m_pButtonSel1->setColorStyle( ImagColor );
	//m_pButtonSel2->setColorStyle( ImagColor );
	//m_pButtonExit->setColorStyle( ImagColor );
#if 0
    m_pButtonCh1->setLabelColorStyle( CommonBaseColor );
	m_pButtonCh2->setLabelColorStyle( CommonBaseColor );
	m_pButtonSel1->setLabelColorStyle( CommonBaseColor );
	m_pButtonSel2->setLabelColorStyle( CommonBaseColor );
	m_pButtonExit->setLabelColorStyle( CommonBaseColor );
#endif
    //[AUDIO INPUT]-[INPUT1 LINE/MIC SEL]
    updateSelInput1(APL_PARAM_GET_DATA(AplParamSelInput1));

    //[AUDIO INPUT]-[INPUT2 LINE/MIC SEL]
    updateSelInput2(APL_PARAM_GET_DATA(AplParamSelInput2));

    //[AUDIO CH SETTINGS]-[CH1 IN SELECT]
    updateCh1In(APL_PARAM_GET_DATA(AplParamInSelectCH1));

    //[AUDIO CH SETTINGS]-[CH2 IN SELECT]
    updateCh2In(APL_PARAM_GET_DATA(AplParamInSelectCH2));
 
}  


bool CtWindowHome_AudioTop::handleParamEvent(const CtEventParam& Param){
    int t_Id = Param.getParamId();
    int int_Data = Param.getParamVal();

    switch(t_Id)
    {
    //[AUDIO INPUT]-[INPUT1 LINE/MIC SEL]
    case AplParamSelInput1:  
        updateSelInput1(int_Data);
        break;  
    //[AUDIO INPUT]-[INPUT2 LINE/MIC SEL]
    case AplParamSelInput2:  
        updateSelInput2(int_Data);
        break;
    //[AUDIO CH SETTINGS]-[CH1 IN SELECT]
    case AplParamInSelectCH1:
        updateCh1In(int_Data);
        break;      
    //[AUDIO CH SETTINGS]-[CH2 IN SELECT]
    case AplParamInSelectCH2:
        updateCh2In(int_Data);
        break;
    default:
        return false;
        break;

    }
	return true;
}


int CtWindowHome_AudioTop::updateSelInput1(int int_Data){
    int index = 0;
    
    switch(int_Data){
        case APL_SYS_PARAM_SELECT_INPUT_LINE:
            index = 0;
            break;
        case APL_SYS_PARAM_SELECT_INPUT_MIC:
            index = 1;
            break;
       default:
            break;
        
    }
    m_pLabelInput1->index(index);
    
    return index;
}


int CtWindowHome_AudioTop::updateSelInput2(int int_Data){
    int index = 0;
    
    switch(int_Data){
        case APL_SYS_PARAM_SELECT_INPUT_LINE:
            index = 0;
            break;
        case APL_SYS_PARAM_SELECT_INPUT_MIC:
            index = 1;
            break;
       default:
            break;
        
    }
    m_pLabelInput2->index(index);
    
    return index;
}


int CtWindowHome_AudioTop::updateCh1In(int int_Data){
    
    int index = 0;
    
    switch(int_Data){
        case APL_SYS_PARAM_CH_IN_SELECT_INT:
            index = 0;
            break;
        case APL_SYS_PARAM_CH_IN_SELECT_INPUT1:
            index = 1;
            break;
       default:
            break;
    }
    m_pLabelCh1In->index(index);
    
    return index;
    
}


int CtWindowHome_AudioTop::updateCh2In(int int_Data){
    int index = 0;
    
    switch(int_Data){
        case APL_SYS_PARAM_CH_IN_SELECT_INT:
            index = 0;
            break;
        case APL_SYS_PARAM_CH_IN_SELECT_INPUT1:
            index = 1;
            break;
        case APL_SYS_PARAM_CH_IN_SELECT_INPUT2:
            index = 2;
            break;
       default:
            break;
    }
    m_pLabelCh2In->index(index);
    
    return index;
    
}

	
bool CtWindowHome_AudioTop::handleButtonEvent(const CtEventButton& Button)
{
	/* Releaseでのみ処理 */
	if( Button.getPressType() != CtEventButton::Release ){
		return false;
	}else{

        if ( m_pButtonExit == Button.getWidget() ) {
            if ( NULL != m_pWin ) {
                m_pWin->requestWindow(WindowNone, Close,NULL);
            }
        }else{
            keyActionEvent();
        }
   }
	return true;
}


bool CtWindowHome_AudioTop::isFocused(){
    int i =0;
    bool flag = false;
    for( i = 0; i < m_Vector.size(); i++) {
        if( true == m_Vector[i]->CtButton::isFocused() ){
            m_bFocused = i;
            flag = true;
           break;
        }else{
        }
    }
    return flag;
}


/* Touch動作状態で、press動作とrelease動作の応答が同じbuttonであることを保証する */
/* press動作とrelase動作は同じbuttonではない時、応答しない  */	
bool CtWindowHome_AudioTop::handleTouchEvent(const CtEventTouch& Touch){
    bool bRet = false;
    CtEventTouch::TouchPosition pos = Touch.getPosition();
	CtPosition Pos;
	
	Pos.x = pos.m_X;
	Pos.y = pos.m_Y;
    int FocusedTmp =0;
    int i = 0;
    for( i=0; i < m_Vector.size(); i++ ){
        if( m_Vector[i]->isContains(Pos) ){
            FocusedTmp = i;
            break;
        }else{
            // No Operation
        }
    }
    switch (Touch.getAction()) {
        case CtEventTouch::Press:
            if( EXIT_INDEX + 1 == i){
                m_bTouchButton = false;  /*touch対応はbuttonではない */
                bRet = true;
            }else {
                m_bFocusedCanMove = false;
                m_bFocused = FocusedTmp;
                m_bTouchButton = true;   /* m_bTouchButton = true 時、touch対象はbuttonである */
                focusedColorChange();
            }
            break;
        case CtEventTouch::Release:
            m_bFocusedCanMove = true;
            if( m_bFocused != FocusedTmp ){
                bRet = true;
            }else if(( m_bFocused == FocusedTmp) && (true == m_bTouchButton )){
                CtEventInterface::requestButtonCmd(m_Vector[m_bFocused], this, CtEventButton::Release);
            }else{
                bRet = true;
            }
             break;
        default:
            break;
    }
    return true;
}

bool CtWindowHome_AudioTop::handleKeyEvent(const CtEventKey& Key){
    bool result = true;
    
    if( CtEventKey::Release == Key.getKeyAction() ){
        if( true ==  isFocused() ){
            switch ( Key.getKeyCode() ) {
            case CtEventKey::KeyCode_Enter:
            case CtEventKey::KeyCode_ManualFunction:
                keyActionEvent();
                m_bFocusedCanMove = true;
                break;  
            case CtEventKey::KeyCode_MmrPlus:
                if( true == m_bFocusedCanMove ){
                    keyCodeEvent(CtEventKey::KeyCode_MmrPlus,m_bFocused);
                }else{
                }
                break;
            case CtEventKey::KeyCode_MmrMinus:
                if( true == m_bFocusedCanMove ){
                    keyCodeEvent(CtEventKey::KeyCode_MmrMinus,m_bFocused);
                }else{
                }
                break;
            default:
                result = false;
                break;
            }
       }
    } else if( CtEventKey::Press == Key.getKeyAction() ){
    	switch ( Key.getKeyCode() ) {
    	case CtEventKey::KeyCode_Exit:
        case CtEventKey::KeyCode_GripUser1:
			if ( NULL != m_pWin ) {
				m_pWin->requestWindow(WindowNone, Close,NULL);
				result = true;
			}
	    	break;
        case CtEventKey::KeyCode_Enter:
        case CtEventKey::KeyCode_ManualFunction:
		/* DIAL_ENTER」を押下して 、「DIAL_UP/DIAL_DOWN」が応答できなくて、フォーカス遷移できません */   		
            m_bFocusedCanMove = false; 
            break;
    	default:
    		break;
    	}
	}else{
        result = false;
    }
    return result;
}


/* MULTI DIAL-UP番号CH1 IN→EXIT→INPUT2 SEL→INPUT1 SEL→CH2 IN→CH1 INの順でカーソルを移動する */
/* DIAL-DOWN:  DIAL-UPの逆順でカーソルを移動する */
void CtWindowHome_AudioTop::keyCodeEvent(CtEventKey::KeyCode KeyCode,int i){
   
	int index =0;

	switch(KeyCode){
        //MULTI DIAL-UP
		case CtEventKey::KeyCode_MmrPlus:
			if( CH1_INDEX == i){
				m_bFocused = EXIT_INDEX;
			}else{
				m_bFocused = i-1;
			}
			break;
       
       //MULTI DIAL-DOWN
		case CtEventKey::KeyCode_MmrMinus:
			if( EXIT_INDEX == i){
				m_bFocused = CH1_INDEX;
			}else{
				m_bFocused = i+1;
			}
			break;
		default:
			break;
	}
    
   focusedColorChange();/* 現在foucusと前回のfocus色の設定  */
   
}


/* 現在foucusと前回のfocus色の設定  */
void CtWindowHome_AudioTop::focusedColorChange(){
    
    for(int j=0; j <m_Vector.size(); j++){
      if( m_bFocused == j){
          m_Vector[m_bFocused]->setFocus();
          m_Vector[m_bFocused]->setColor( CommonSelectStrokeColor );
      }else{
          m_Vector[j]->setColor( ImagColor );
      }
    }
}


/* DIAL-SET 設定値と表示を切り替える */
void CtWindowHome_AudioTop::keyActionEvent(){
    CtDebugPrint(CtDbg, "keyActionEvent m_bFocused= %d)\n",m_bFocused);
    
    int index =0;
    switch(m_bFocused){
        case CH1_INDEX:
            index = updateCh1In( APL_PARAM_GET_DATA(AplParamInSelectCH1));
            if( 0 == index){ 
                index =1;
            }else {
                index = 0;
            }
            updateCh1In(index);
            APL_PARAM_SET_DATA(AplParamInSelectCH1,index);
            break;
        case CH2_INDEX:
            index = updateCh2In(APL_PARAM_GET_DATA(AplParamInSelectCH2)); 
            if( 0 == index){ 
                index = 1;
            }else if( 1 == index){ 
                index = 2;
            }else {
                index = 0;
            }
            updateCh2In(index);
            APL_PARAM_SET_DATA(AplParamInSelectCH2,index);
            break;
        case SEL1_INDEX:
            index = updateSelInput1(APL_PARAM_GET_DATA(AplParamSelInput1)); 
            if( 0 == index){ 
                index = 1;
            }else {
                index = 0;
            }
            updateSelInput1(index);
            APL_PARAM_SET_DATA(AplParamSelInput1,index);
            break;
        case SEL2_INDEX:
            index = updateSelInput2(APL_PARAM_GET_DATA(AplParamSelInput2)); 
            if( 0 == index ) { 
                index = 1;
            }else {
                index = 0;
            }
            updateSelInput2(index);
            APL_PARAM_SET_DATA(AplParamSelInput2,index);
            break;
        case EXIT_INDEX:
            CtInterface::getInstance()->closeWindow(ScreenLCD);
           break; 
        default:
            break;

    }
    
         focusedColorChange();/* 現在foucusと前回のfocus色の設定  */

}


CtWindowHome_AudioTop::~CtWindowHome_AudioTop()
{
    destroyWindow();
}


bool CtWindowHome_AudioTop::destroyWindow()
{
	return true;
}
