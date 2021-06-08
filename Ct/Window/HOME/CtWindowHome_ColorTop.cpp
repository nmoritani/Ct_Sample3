/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowHome_ColorTop
 */


#include "CtWindowHome_ColorTop.h"

CtColor CtWindowHome_ColorTop::LabelColor(71,72,74,0xff);
CtColor CtWindowHome_ColorTop::ImagColor(240,240,240,0xff);
CtColor CtWindowHome_ColorTop::LineColor(40, 41, 44, 0xff);

CtWindowHome_ColorTop::CtWindowHome_ColorTop() :
    m_pLabelMainColor(NULL),
    m_pLabelSubColor(NULL),
    m_pLabelSdi(NULL),
    m_pLabelHdmi(NULL),
    m_pLabelLcd(NULL),
    m_pButtonSub(NULL),
    m_pButtonSdi(NULL),
    m_pButtonHdmi(NULL),
    m_pButtonLcd(NULL),
    m_pButtonMain(NULL),
    m_pButtonExit(NULL),
    m_Vector(NULL),
    m_FocusButton(ButtonIdMain),
    m_PressButton(false),
    m_ManualFunction(true)
{
}

CtWindow* CtWindowHome_ColorTop::createWindow()
{
    m_pWin = new CtWindow(CtColor::Black);
    CtVLayout* pAll = new CtVLayout();

    /* ================================================================================== */
    /* TopLayout描画 =============================================================== */
    /* ================================================================================== */
    CtLayout *pLayout2 = new CtLayout(); // 60
    CtLayout *pLayoutLayoutTop = createWindowLayoutTop(); 
    pLayout2->addWidget(pLayoutLayoutTop);
    CtLayout *pLayout3 = new CtLayout();//50
    CtLayout *pLayoutTop = createWindowTop(); 
    pLayout3->addWidget(pLayoutTop);
    CtVLayout *pTop1 = new CtVLayout(LabelColor);
    pTop1->addStretch( 3 );
    pTop1->addWidget(pLayout2,AlignCenter,60);
    pTop1->addWidget(pLayout3,AlignCenter,50);

    /* ================================================================================== */
    /* BottomLayout描画 =============================================================== */
    /* ================================================================================== */
    CtLayout *pLayout12 = new CtLayout(); // 60
    CtLayout *pLayoutLayoutBottom = createWindowLayoutBottom(); 
    pLayout12->addWidget(pLayoutLayoutBottom);
    CtLayout *pLayout13 = new CtLayout();//50
    CtLayout *pLayoutBottom = createWindowBottom(); 
    pLayout13->addWidget(pLayoutBottom);
    CtVLayout *pTop2 = new CtVLayout(LabelColor);
    pTop2->addWidget(pLayout13,AlignCenter,50);
    pTop2->addWidget(pLayout12,AlignCenter,60);
    pTop2->addStretch( 3 );

    /* ================================================================================== */
    /* WindowLayout描画 =============================================================== */
    /* ================================================================================== */
    pAll->addWidget(pTop1,CtMargin(0,0),113);
    pAll->addStretch( 314 );
    pAll->addWidget(pTop2,CtMargin(0,0),113);

    m_pWin->addWidget(pAll);
    m_pWin->setRegion(CtRegion(0, 0, 960, 540));
    m_pWin->setVisible(true);
    m_pWin->setLayout();

    /* 初期化 */
    InitDisplay();
    updateFocus();
    return m_pWin;
}

//create  TopLayout   (下段）ボタン名="MAIN COLOR" と　(下段）ボタン名="SUB COLOR"
CtLayout* CtWindowHome_ColorTop::createWindowTop()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
    CtHLayout *pLayout = new CtHLayout(LabelColor); 

    CtLabel *pLabel_L1 = new CtLabel(CtSize(4,18));
    CtLabel *pLabel_L2 = new CtLabel(CtSize(4,18));
    CtLabel *pLabel_Ch1 = new CtLabel(STR_ID_NO_10793, fSet);

	pLabel_L1->setColor(LineColor);
	pLabel_L2->setColor(LineColor);

    pLayout->addWidget(pLabel_Ch1, CtMargin(0,0), 319);
    pLayout->addWidget(pLabel_L1,4);
    
    
    if( checkSubRec() ){
		CtLabel *pLabel_Ch2 = new CtLabel(STR_ID_NO_10683, fSet);
        pLayout->addWidget(pLabel_Ch2, CtMargin(0,0),314);
    }else{
		CtLabel *pLabel_Ch3 = new CtLabel("", fSet);
        pLayout->addWidget(pLabel_Ch3, CtMargin(0,0),314);// 無しラベルを表示
    }
    pLayout->addWidget(pLabel_L2,4);
    pLayout->addWidget(new CtHLayout(), CtMargin(0,0),319);

    return pLayout;
}

//create  BottomLayout   (下段）ボタン名="SDI OUT" ,(下段）ボタン名="HDMI OUT" と　(下段）ボタン名="LCD OUT"
CtLayout* CtWindowHome_ColorTop::createWindowBottom()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
    CtHLayout *pLayout = new CtHLayout(LabelColor); 

    CtLabel *pLabel_L1 = new CtLabel(CtSize(4,18));
    CtLabel *pLabel_L2 = new CtLabel(CtSize(4,18));
    CtLabel *pLabel_Ch1 = new CtLabel(STR_ID_NO_10795, fSet);

	pLabel_L1->setColor(LineColor);
	pLabel_L2->setColor(LineColor);

    pLayout->addWidget(pLabel_Ch1, CtMargin(0,0), 319);
    pLayout->addWidget(pLabel_L1,4);
    CtLabel *pLabel_Ch2 = new CtLabel(STR_ID_NO_10796, fSet);
    pLayout->addWidget(pLabel_Ch2, CtMargin(0,0),314);
    pLayout->addWidget(pLabel_L2,4);
    CtLabel *pLabel_Ch3 = new CtLabel(STR_ID_NO_10797, fSet);
    pLayout->addWidget(pLabel_Ch3, CtMargin(0,0),319);

    return pLayout;
}

//(上段）MAIN COLORステータス と (上段）SUB COLORステータス
CtLayout* CtWindowHome_ColorTop::createWindowLayoutTop()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::Black);
    //MAIN COLOR
    m_pLabelMainColor = new CtStackLabel();
    m_pLabelMainColor->addLabel(new CtLabel(STR_ID_NO_10062, fSet));
    m_pLabelMainColor->addLabel(new CtLabel(STR_ID_NO_10756, fSet));
    m_pLabelMainColor->addLabel(new CtLabel(STR_ID_NO_10757, fSet));
    m_pLabelMainColor->addLabel(new CtLabel(STR_ID_NO_10758, fSet));
    m_pLabelMainColor->addLabel(new CtLabel(STR_ID_NO_10759, fSet));
    m_pLabelMainColor->addLabel(new CtLabel(STR_ID_NO_10760, fSet));
    //SUB COLOR
    m_pLabelSubColor = new CtStackLabel();
    m_pLabelSubColor->addLabel(new CtLabel(STR_ID_NO_10062, fSet));
    m_pLabelSubColor->addLabel(new CtLabel(STR_ID_NO_10072, fSet));
    m_pLabelSubColor->addLabel(new CtLabel(STR_ID_NO_10756, fSet));
    m_pLabelSubColor->addLabel(new CtLabel(STR_ID_NO_10757, fSet));
    m_pLabelSubColor->addLabel(new CtLabel(STR_ID_NO_10758, fSet));
    m_pLabelSubColor->addLabel(new CtLabel(STR_ID_NO_10759, fSet));
    m_pLabelSubColor->addLabel(new CtLabel(STR_ID_NO_10760, fSet));
    if( !checkSubRec() ){
        m_pLabelSubColor->setVisible( false );// 無しラベルを表示
    }else{
        /* No Operation */
    }
    
    CtLayout *pLayout1 = new CtLayout(); 
    pLayout1->addWidget(m_pLabelMainColor);
    CtLayout *pLayout2 = new CtLayout(); 
    pLayout2->addWidget(m_pLabelSubColor);
    CtLayout *pLayout3 = new CtLayout(); 
    pLayout3->addWidget(new CtLabel(STR_ID_NO_10794, fSet));

    /* MainColor表示領域 */
    m_pButtonMain = new CtButton(CtSize(312,60), pLayout1, CtButton::None);
    m_pButtonMain->setImage(IC_AUDIO_TOP_LEFT);
    m_pButtonMain->setColor(ImagColor);
    m_pButtonMain->setFocusable(false);
   
    /* SubColor表示領域 */
    m_pButtonSub = new CtButton(CtSize(312,60),pLayout2, CtButton::None);
    m_pButtonSub->setImage(IC_AUDIO_TOP_CENTER);
    m_pButtonSub->setColor(ImagColor);
    m_pButtonSub->setFocusable(false);
    
    /* Exit表示領域 */
    m_pButtonExit = new CtButton(CtSize(312,60),pLayout3, CtButton::None);
    m_pButtonExit->setImage(IC_AUDIO_TOP_RIGHT);
    //m_pButtonExit->setColor(ImagColor);
    m_pButtonExit->setFocusable(false);


    CtHLayout *pLayout = new CtHLayout(LabelColor);
    pLayout->addStretch(6);
    pLayout->addWidget(m_pButtonMain,312);
    pLayout->addStretch(6);
    pLayout->addWidget(m_pButtonSub,312);
    pLayout->addStretch(6);
    pLayout->addWidget(m_pButtonExit,312);
    pLayout->addStretch(6);

    m_Vector.push_back(m_pButtonMain);
    m_Vector.push_back(m_pButtonSub);
    m_Vector.push_back(m_pButtonExit);

    return pLayout;
}

//(下段）SDI OUTステータス,(下段）HDMI OUTステータス と (下段）LCD OUTステータス
CtLayout* CtWindowHome_ColorTop::createWindowLayoutBottom()
{
    CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::Black);
    //SDI OUT
    m_pLabelSdi = new CtStackLabel();
    m_pLabelSdi->addLabel(new CtLabel(STR_ID_NO_10062, fSet));
    m_pLabelSdi->addLabel(new CtLabel(STR_ID_NO_10072, fSet));
    m_pLabelSdi->addLabel(new CtLabel(STR_ID_NO_10756, fSet));
    m_pLabelSdi->addLabel(new CtLabel(STR_ID_NO_10757, fSet));
    m_pLabelSdi->addLabel(new CtLabel(STR_ID_NO_10758, fSet));
    m_pLabelSdi->addLabel(new CtLabel(STR_ID_NO_10759, fSet));
    m_pLabelSdi->addLabel(new CtLabel(STR_ID_NO_10760, fSet));
	m_pLabelSdi->addLabel(new CtLabel(STR_ID_NO_10960, fSet));
    //HDMI OUT
    m_pLabelHdmi = new CtStackLabel();
    m_pLabelHdmi->addLabel(new CtLabel(STR_ID_NO_10062, fSet));
    m_pLabelHdmi->addLabel(new CtLabel(STR_ID_NO_10072, fSet));
    m_pLabelHdmi->addLabel(new CtLabel(STR_ID_NO_10756, fSet));
    m_pLabelHdmi->addLabel(new CtLabel(STR_ID_NO_10757, fSet));
    m_pLabelHdmi->addLabel(new CtLabel(STR_ID_NO_10758, fSet));
    m_pLabelHdmi->addLabel(new CtLabel(STR_ID_NO_10759, fSet));
    m_pLabelHdmi->addLabel(new CtLabel(STR_ID_NO_10760, fSet));
    //LCD OUT
    m_pLabelLcd = new CtStackLabel();
    m_pLabelLcd->addLabel(new CtLabel(STR_ID_NO_10062, fSet));
    m_pLabelLcd->addLabel(new CtLabel(STR_ID_NO_10072, fSet));
    m_pLabelLcd->addLabel(new CtLabel(STR_ID_NO_10756, fSet));
    m_pLabelLcd->addLabel(new CtLabel(STR_ID_NO_10757, fSet));
    m_pLabelLcd->addLabel(new CtLabel(STR_ID_NO_10758, fSet));
    m_pLabelLcd->addLabel(new CtLabel(STR_ID_NO_10759, fSet));
    m_pLabelLcd->addLabel(new CtLabel(STR_ID_NO_10760, fSet));
    
    CtLayout *pLayout1 = new CtLayout(); 
    pLayout1->addWidget(m_pLabelSdi);
    CtLayout *pLayout2 = new CtLayout(); 
    pLayout2->addWidget(m_pLabelHdmi);
    CtLayout *pLayout3 = new CtLayout(); 
    pLayout3->addWidget(m_pLabelLcd);
    /* SdiOut表示領域 */
    m_pButtonSdi = new CtButton(CtSize(312,60), pLayout1, CtButton::None);
    m_pButtonSdi->setImage(IC_AUDIO_BOTTOM_LEFT);
    m_pButtonSdi->setColor(ImagColor);
    m_pButtonSdi->setFocusable(false);
    //m_pButtonSdi->setOwnColor(false);
    /* HdmiOut表示領域 */
    m_pButtonHdmi = new CtButton(CtSize(312,60),pLayout2, CtButton::None);
    m_pButtonHdmi->setImage(IC_AUDIO_BOTTOM_CENTER);
    m_pButtonHdmi->setColor(ImagColor);
    m_pButtonHdmi->setFocusable(false);
    //m_pButtonHdmi->setOwnColor(false);
    /* LcdOut表示領域 */
    m_pButtonLcd = new CtButton(CtSize(312,60),pLayout3, CtButton::None);
    m_pButtonLcd->setImage(IC_AUDIO_BOTTOM_RIGHT);
    m_pButtonLcd->setColor(ImagColor);
    m_pButtonLcd->setFocusable(false);
    //m_pButtonLcd->setOwnColor(false);

    CtHLayout *pLayout = new CtHLayout(LabelColor);
    pLayout->addStretch(6);
    pLayout->addWidget(m_pButtonSdi, CtMargin(0,0),312);
    pLayout->addStretch(6);
    pLayout->addWidget(m_pButtonHdmi, CtMargin(0,0),312);
    pLayout->addStretch(6);
    pLayout->addWidget(m_pButtonLcd, CtMargin(0,0),312);
    pLayout->addStretch(6);

    m_Vector.push_back(m_pButtonSdi);
    m_Vector.push_back(m_pButtonHdmi);
    m_Vector.push_back(m_pButtonLcd);

    return pLayout;
}

void CtWindowHome_ColorTop::InitDisplay()
{
	//m_pButtonMain->setColorStyle(ImagColor);
	//m_pButtonSub->setColorStyle(ImagColor);
	//m_pButtonExit->setColorStyle(ImagColor);
	//m_pButtonSdi->setColorStyle(ImagColor);
	//m_pButtonHdmi->setColorStyle(ImagColor);
	//m_pButtonLcd->setColorStyle(ImagColor);
#if 0
	m_pButtonMain->setSelectStrokeColorStyle(ImagColor);
	m_pButtonSub->setSelectStrokeColorStyle(ImagColor);
	m_pButtonExit->setSelectStrokeColorStyle(ImagColor);
	m_pButtonSdi->setSelectStrokeColorStyle(ImagColor);
	m_pButtonHdmi->setSelectStrokeColorStyle(ImagColor);
	m_pButtonLcd->setSelectStrokeColorStyle(ImagColor);
#endif
    updateColorMain(APL_PARAM_GET_DATA(AplParamColorMain));

    updateColorSub(APL_PARAM_GET_DATA(AplParamColorSub));

    updateColorSdiOut(APL_PARAM_GET_DATA(AplParamColorSdiOut));

    updateColorHdmiOut(APL_PARAM_GET_DATA(AplParamColorHdmiOut));

    updateColorLcdOut(APL_PARAM_GET_DATA(AplParamColorLcdOut));
 
}

bool CtWindowHome_ColorTop::handleButtonEvent(const CtEventButton& Button)
{
    /* Releaseでのみ処理 */
    if( Button.getPressType() != CtEventButton::Release ){
        return false;
    }else{
        /* No Operation */
    }

    int index =0;
    switch(m_FocusButton){
    case ButtonIdMain:
        if(checkSdiRaw()){
            if ( NULL != m_pWin ) {
//                m_pWin->requestWindow(WindowID_Menu_COLOR_SETTING_MAIN,OpenPopup,NULL);
            }
        }else{
            /* No Operation */
        }
        break;
    case ButtonIdSub:
        if(checkSubRec()&&checkMainColor()){
            index =updateColorSub(APL_PARAM_GET_DATA(AplParamColorSub));
            if(index == 1){
                index=0;
            }else{
                index=1;
            }
            updateColorSub(index);
            APL_PARAM_SET_DATA(AplParamColorSub,index);
        }else{
            /* No Operation */
        }
        break;
    case ButtonIdExit:
        if ( NULL != m_pWin ) {
            m_pWin->requestWindow(WindowNone, Close,NULL);
        }
        break;
    case ButtonIdSdi:
        if(checkSdiRaw()&&checkMainColor()){
            index =updateColorSdiOut(APL_PARAM_GET_DATA(AplParamColorSdiOut));
            if(index == 1){
                index=0;
            }else{
                index=1;
            }
            updateColorSdiOut(index);
            APL_PARAM_SET_DATA(AplParamColorSdiOut,index);
        }else{
            /* No Operation */
        }
        break;
    case ButtonIdHdmi:
        if(/*checkSdiRaw()&&*/checkMainColor()){
            index =updateColorHdmiOut(APL_PARAM_GET_DATA(AplParamColorHdmiOut));
            if(index == 1){
                index=0;
            }else{
                index=1;
            }
            updateColorHdmiOut(index);
            APL_PARAM_SET_DATA(AplParamColorHdmiOut,index);
        }else{
            /* No Operation */
        }
        break;
    case ButtonIdLcd:
        if(/*checkSdiRaw()&&*/checkMainColor()){
            index =updateColorLcdOut(APL_PARAM_GET_DATA(AplParamColorLcdOut));
            if(index == 1){
                index=0;
            }else{
                index=1;
            }
            updateColorLcdOut(index);
            APL_PARAM_SET_DATA(AplParamColorLcdOut,index);
        }else{
            /* No Operation */
        }
        break;
    default:
        break;
    }
    return true;
}

bool CtWindowHome_ColorTop::handleParamEvent(const CtEventParam& Param)
{
    int t_Id = Param.getParamId();
    int int_Data = Param.getParamVal();

    switch(t_Id) {
    case AplParamColorMain:  
        updateColorMain(int_Data);
        break;  
    case AplParamColorSub:  
        updateColorSub(int_Data);
        break;
    case AplParamColorSdiOut:
        updateColorSdiOut(int_Data);
        break;      
    case AplParamColorHdmiOut:
        updateColorHdmiOut(int_Data);
        break;
    case AplParamColorLcdOut:
        updateColorLcdOut(int_Data);
        break;
	case AplParamSystemSdiRaw:
		updateColorSdiOut(APL_PARAM_GET_DATA( AplParamColorSdiOut));
		break;
    default:
        return false;
        break;
    }
    return true;
}

bool CtWindowHome_ColorTop::handleKeyEvent(const CtEventKey& Key)
{
    bool bRet = false;
    
    switch (Key.getKeyAction()) {
    case CtEventKey::Press:
        switch ( Key.getKeyCode() ) {
    	case CtEventKey::KeyCode_Exit:
        case CtEventKey::KeyCode_GripUser1:
            if ( NULL != m_pWin ) {
                m_pWin->requestWindow(WindowNone, Close,NULL);
                bRet = true;
            }
            break;
        case CtEventKey::KeyCode_Enter:
        case CtEventKey::KeyCode_ManualFunction:
            /* DIAL_ENTER」を押下して 、「DIAL_UP/DIAL_DOWN」が応答できなくて、フォーカス遷移できません */
            m_ManualFunction = false;
            break;
        default:
            break;
        }
        break;
    case CtEventKey::Release:
        switch (Key.getKeyCode()) {
        case CtEventKey::KeyCode_MmrPlus:
            if(checkSubRec()){
                dialFocus(false,true);
            }else{
                dialFocus(false,false);
            }
            bRet = true;
            break;
        case CtEventKey::KeyCode_MmrMinus:
            if(checkSubRec()){
                dialFocus(true,true);
            }else{
                dialFocus(true,false);
            }
            bRet = true;
            break;
        case CtEventKey::KeyCode_Up:
            moveFocus(DirUp);
            bRet = true;
            break;
        case CtEventKey::KeyCode_Down:
            moveFocus(DirDown);
            bRet = true;
            break;
        case CtEventKey::KeyCode_Left:
            moveFocus(DirLeft);
            bRet = true;
            break;
        case CtEventKey::KeyCode_Right:
            moveFocus(DirRight);
            bRet = true;
            break;
        case CtEventKey::KeyCode_ManualFunction:
        case CtEventKey::KeyCode_Enter:
            {
            m_ManualFunction = true;
            CtButton* pButton = NULL;
            switch( m_FocusButton ){
            case ButtonIdMain:      pButton = m_pButtonMain;        break;
            case ButtonIdSub:       pButton = m_pButtonSub;         break;
            case ButtonIdExit:       pButton = m_pButtonExit;         break;
            case ButtonIdSdi:       pButton = m_pButtonSdi;         break;
            case ButtonIdHdmi:      pButton = m_pButtonHdmi;        break;
            case ButtonIdLcd:       pButton = m_pButtonLcd;         break;
            default:    break;
            }
            if( pButton != NULL ){
#if 0 /*@salvage*/
                CtEventInterface::requestButtonCmd(pButton, this, CtEventButton::Release);
#endif
            }else{
                /* No Operation */
            }
        }
        bRet = true;
        break;
        default:
            break;
        }
    break;
    default:
        break;
    }
    return bRet;
}

bool CtWindowHome_ColorTop::handleTouchEvent(const CtEventTouch& Touch)
{   
    int i = 0;
    int FocusButton = ButtonIdMax+1;
    bool bRet = true;
    CtEventTouch::TouchPosition pos = Touch.getPosition();
    CtPosition Pos;
    
    Pos.x = pos.m_X;
    Pos.y = pos.m_Y;

    for( ; i< m_Vector.size(); i++ ){
        if ( m_Vector[i]->isContains(Pos) ){
            FocusButton = i;
            break;
        }else{
            // No Operation
        }
    }
    //[SUB REC]がOFFの場合は無効。
    if(!checkSubRec()){
        if(ButtonIdSub == (ButtonId)FocusButton){
            return bRet;
        }
    }
    switch (Touch.getAction()) {
    case CtEventTouch::Press:
        if( m_Vector.size()== i ){
            m_PressButton = false;
            return bRet;
        }else{
            m_PressButton = true;
            // No Operation
        }
        m_FocusButton = (ButtonId)FocusButton;
        updateFocus();
        break;
    case CtEventTouch::Release:
        if( ( m_FocusButton == FocusButton )&&(m_PressButton == true) ) {
            m_PressButton = false;
            if( m_Vector[FocusButton] != NULL ){
#if 0 /*@salvage*/
                CtEventInterface::requestButtonCmd(m_Vector[FocusButton], this, CtEventButton::Release);
#endif
            }else{
                // No Operation
            }
        }else{
            m_PressButton = false;
            return bRet;
        }
        break;
    default:
        break;
    }
    return bRet;
}

int CtWindowHome_ColorTop::updateColorMain(int int_Data)
{
    int index = 0;

    switch(int_Data){
    case APL_SYS_PARAM_COLOR_MAIN_VLOG:
        index = 0;
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
        index = 1;
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
        index = 2;
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
        index = 3;
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
        index = 4;
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
        index = 5;
        break;
    default:
        break;  
    }
    m_pLabelMainColor->index(index);
    return index;
}

int CtWindowHome_ColorTop::updateColorSub(int int_Data)
{
    int index = 0;

    switch(int_Data){
    case APL_SYS_PARAM_COLOR_SUB_VLOG:
        index = 0;
        break;
    case APL_SYS_PARAM_COLOR_SUB_V709:
        index = 1;
        break;
    case APL_SYS_PARAM_COLOR_SUB_SCENE1:
        index = 2;
        break;
    case APL_SYS_PARAM_COLOR_SUB_SCENE2:
        index = 3;
        break;
    case APL_SYS_PARAM_COLOR_SUB_SCENE3:
        index = 4;
        break;
    case APL_SYS_PARAM_COLOR_SUB_SCENE4:
        index = 5;
        break;
    case APL_SYS_PARAM_COLOR_SUB_SCENE5:
        index = 6;
        break;
    default:
        break; 
    }
    m_pLabelSubColor->index(index);
    return index;
}

int CtWindowHome_ColorTop::updateColorSdiOut(int int_Data)
{
    int index = 0;
	if( checkSdiRaw()){
		switch(int_Data){
		case APL_SYS_PARAM_COLOR_SDI_OUT_VLOG:
			index = 0;
			break;
		case APL_SYS_PARAM_COLOR_SDI_OUT_V709:
			index = 1;
			break;
		case APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1:
			index = 2;
			break;
		case APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2:
			index = 3;
			break;
		case APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3:
			index = 4;
			break;
		case APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4:
			index = 5;
			break;
		case APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5:
			index = 6;
			break;
		default:
			break;
		}
	}else{
		index = 7;
	}
    m_pLabelSdi->index(index);
    return index;
}

int CtWindowHome_ColorTop::updateColorHdmiOut(int int_Data)
{
    int index = 0;

    switch(int_Data){
    case APL_SYS_PARAM_COLOR_HDMI_OUT_VLOG:
        index = 0;
        break;
    case APL_SYS_PARAM_COLOR_HDMI_OUT_V709:
        index = 1;
        break;
    case APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1:
        index = 2;
        break;
    case APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2:
        index = 3;
        break;
    case APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3:
        index = 4;
        break;
    case APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4:
        index = 5;
        break;
    case APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5:
        index = 6;
        break;
    default:
        break; 
    }
    m_pLabelHdmi->index(index);
    return index;
}

int CtWindowHome_ColorTop::updateColorLcdOut(int int_Data)
{
    int index = 0;

    switch(int_Data){
    case APL_SYS_PARAM_COLOR_LCD_OUT_VLOG:
        index = 0;
        break;
    case APL_SYS_PARAM_COLOR_LCD_OUT_V709:
        index = 1;
        break;
    case APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1:
        index = 2;
        break;
    case APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2:
        index = 3;
        break;
    case APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3:
        index = 4;
        break;
    case APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4:
        index = 5;
        break;
    case APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5:
        index = 6;
        break;
    default:
        break;
    }
    m_pLabelLcd->index(index);
    return index;
}

/* 本体MULTI DIALボタンのフォーカスは更新処理 */
void CtWindowHome_ColorTop::dialFocus(bool bPlus,bool silent)
{
    if((m_ManualFunction == true )&&(m_PressButton == false)){
        if( bPlus ){
            switch( m_FocusButton ){
            case ButtonIdMain:       silent?(m_FocusButton = ButtonIdSub):(m_FocusButton = ButtonIdExit);       break;
            case ButtonIdSub:        m_FocusButton = ButtonIdExit;      break;
            case ButtonIdExit:       m_FocusButton = ButtonIdSdi;       break;
            case ButtonIdSdi:        m_FocusButton = ButtonIdHdmi;      break;
            case ButtonIdHdmi:       m_FocusButton = ButtonIdLcd;       break;
            case ButtonIdLcd:        m_FocusButton = ButtonIdMain;      break;
            default:    break;
            }
        } else {
            switch( m_FocusButton ){
            case ButtonIdMain:       m_FocusButton = ButtonIdLcd;       break;
            case ButtonIdSub:        m_FocusButton = ButtonIdMain;      break;
            case ButtonIdExit:       silent?(m_FocusButton = ButtonIdSub):(m_FocusButton = ButtonIdMain);       break;
            case ButtonIdSdi:	     m_FocusButton = ButtonIdExit;      break;
            case ButtonIdHdmi:       m_FocusButton = ButtonIdSdi;       break;
            case ButtonIdLcd:        m_FocusButton = ButtonIdHdmi;      break;
            default:    break;
            }
        }
    }
    updateFocus();
}

/* 本体DIALボタンのフォーカスは更新処理 */
void CtWindowHome_ColorTop::moveFocus(CtDirection Dir)
{
    switch( Dir ){
    case DirUp:
        switch( m_FocusButton ){
        case ButtonIdSdi:        m_FocusButton = ButtonIdMain;      break;
        case ButtonIdHdmi:       m_FocusButton = ButtonIdSub;       break;
        case ButtonIdLcd:        m_FocusButton = ButtonIdExit;      break;
        default:    break;
        }
        break;
    case DirDown:
        switch( m_FocusButton ){
        case ButtonIdMain:       m_FocusButton = ButtonIdSdi;       break;
        case ButtonIdSub:        m_FocusButton = ButtonIdHdmi;      break;
        case ButtonIdExit:       m_FocusButton = ButtonIdLcd;       break;
        default:    break;
        }
        break;
    case DirLeft:
        switch( m_FocusButton ){
        case ButtonIdSub:        m_FocusButton = ButtonIdMain;      break;
        case ButtonIdExit:       m_FocusButton = ButtonIdSub;       break;
        case ButtonIdHdmi:       m_FocusButton = ButtonIdSdi;       break;
        case ButtonIdLcd:        m_FocusButton = ButtonIdHdmi;      break;
        default:    break;
        }
        break;
    case DirRight:
        switch( m_FocusButton ){
        case ButtonIdMain:       m_FocusButton = ButtonIdSub;       break;
        case ButtonIdSub:        m_FocusButton = ButtonIdExit;      break;
        case ButtonIdSdi:        m_FocusButton = ButtonIdHdmi;      break;
        case ButtonIdHdmi:       m_FocusButton = ButtonIdLcd;       break;
        default:    break;
        }
    break;
    default:    break;
    }
    updateFocus();
}

/* BaseColorは更新処理必要 */
void CtWindowHome_ColorTop::updateFocus()
{
	const CtStyle::CtProperty& prop =  CtStyle::getProperty();
    for (int i = 0; i < m_Vector.size(); i++) {
        if( i == m_FocusButton){
            m_Vector[i]->setColor( prop.Button.Selected.Base );
        }else{
            m_Vector[i]->setColor( ImagColor );
        }
    }
}

bool CtWindowHome_ColorTop::checkMainColor()
{
    if( APL_PARAM_GET_DATA( AplParamColorMain ) == APL_SYS_PARAM_COLOR_MAIN_VLOG ){
        return true;
    }else{
        return false;
    }
}

bool CtWindowHome_ColorTop::checkSdiRaw()
{
    if( APL_PARAM_GET_DATA( AplParamSystemSdiRaw  ) == APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF  ){
        return true;
    }else{
        return false;
    }
}

bool CtWindowHome_ColorTop::checkSubRec()
{
    if( APL_PARAM_GET_DATA( AplParamSystemSubRec  ) == APL_SYS_PARAM_SYSTEM_SUB_REC_OFF   ){
        return false;
    }else{
        return true;
    }
}

CtWindowHome_ColorTop::~CtWindowHome_ColorTop()
{
    destroyWindow();
}

bool CtWindowHome_ColorTop::destroyWindow()
{
    return true;
}
