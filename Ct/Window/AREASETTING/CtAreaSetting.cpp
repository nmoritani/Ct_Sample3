/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtAreaSetting
 */

#include "CtAreaSetting.h"
#include "CtDebugPrint.h"
#include "CtWindowCommon.h"

#define FACTORY_SETTING 0   // 「Enter」と「Cancel」ボタンがない
#define MENU_SETTING    1   // 「Enter」と「Cancel」ボタンがある

CtAreaSetting::CtAreaSetting(CtWindowContents *pContents) : 
    m_pWin(NULL),
    m_pAREA1(NULL),
    m_pAREA2(NULL),
	m_pAREA3(NULL),
	m_pAREA4(NULL),
	m_pConfirm(NULL),
    m_pCancel(NULL),
	m_Area(ContentsAreaSetting_AREA3)
{
	setClassType(CtClassType_WindowAreaSetting);
}

CtWindow* CtAreaSetting::createWindow()
{
    CtFontSet fSet_Center = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    CtFontSet fSet_Left = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fSet_Right = CtFontSet(FontTypeNormal_alignRight,CtColor::White);
	CtFontSet fSet_Size = CtFontSet(FontTypeNormal_alignRight, CtColor::White);
	

	fSet_Size.setSize(35);
	fSet_Size.setLanguageId(LANGUAGE_ID_UE);
	CtSize Size[4];
	memset(Size, 0, sizeof(Size));
	fSet_Size.getStringSize(Size[0], STR_ID_NO_11632);
	fSet_Size.getStringSize(Size[1], STR_ID_NO_11633);
	fSet_Size.getStringSize(Size[2], STR_ID_NO_11634);
	fSet_Size.getStringSize(Size[3], STR_ID_NO_11635);

	short Max_Size = 0;

	for (int i = 0; i < 4; i++) {
		if (Max_Size < Size[i].width) {
			Max_Size = Size[i].width;
		}
	}

    CtVLayout *pAreaSetting = new CtVLayout(CtColor(ColorRGBA, 0x021527ff, NULL));      // スポイトでRGBの値を取得した
    // "AREA SETTINGS"
    pAreaSetting->addWidget(new CtLabel(STR_ID_NO_10599, fSet_Left), AlignLeft, 80);

    // 空白
    pAreaSetting->addStretch(10);

    // "Please select the region of use."
    pAreaSetting->addWidget(new CtLabel(STR_ID_NO_10895, fSet_Center), AlignCenter, 70);

    // 空白
    pAreaSetting->addStretch(20);

	//m_pAREA1 = new CtToggleButton(CtSize(200, 50), STR_ID_NO_10600, fSet_Center);
	//m_pAREA2 = new CtToggleButton(CtSize(200, 50), STR_ID_NO_10601, fSet_Center);
	//m_pAREA3 = new CtToggleButton(CtSize(200, 50), STR_ID_NO_10602, fSet_Center);
	//m_pAREA4 = new CtToggleButton(CtSize(200, 50), "AREA 4", fSet_Center);

	CtLayout* pLayout_1 = new CtLayout();
	CtLayout* pLayout_2 = new CtLayout();
	CtLayout* pLayout_3 = new CtLayout();
	CtLayout* pLayout_4 = new CtLayout();

	pLayout_1->addWidget(new CtLabel(STR_ID_NO_11632, fSet_Left), CtMargin(0, 10));
	pLayout_2->addWidget(new CtLabel(STR_ID_NO_11633, fSet_Left), CtMargin(0, 10));
	pLayout_3->addWidget(new CtLabel(STR_ID_NO_11634, fSet_Center), CtMargin(0, 10));
	pLayout_4->addWidget(new CtLabel(STR_ID_NO_11635, fSet_Left), CtMargin(0, 10));
	
	m_pAREA1 = new CtToggleButton(CtSize(Max_Size + 20, 50), pLayout_1);
	m_pAREA2 = new CtToggleButton(CtSize(Max_Size + 20, 50), pLayout_2);
	m_pAREA3 = new CtToggleButton(CtSize(Max_Size + 20, 50), pLayout_3);
	m_pAREA4 = new CtToggleButton(CtSize(Max_Size + 20, 50), pLayout_4);
	
	m_pAREA1->setHold(true);
	m_pAREA2->setHold(true);
	m_pAREA3->setHold(true);
	m_pAREA4->setHold(true);
	
    pAreaSetting->addWidget(m_pAREA1, 50);
	pAreaSetting->addStretch(20);
    pAreaSetting->addWidget(m_pAREA2, 50);
    pAreaSetting->addStretch(20);
    pAreaSetting->addWidget(m_pAREA3, 50);
	pAreaSetting->addStretch(20);
	pAreaSetting->addWidget(m_pAREA4, 50);


	if(getWindowID() == Window_Area_Setting){
        // 出荷設定直後
        m_bFlagForTwoBtn = false;
    }else if(getWindowID() == WindowID_Menu_AREA_SETTING){
        // Menuから
        m_bFlagForTwoBtn = true;
    }else{
        // デフォルトは、「Menuから」にする
        m_bFlagForTwoBtn = true;
    }

    if(m_bFlagForTwoBtn){
        // 「決定」と「戻る」ボタンがある
        // 空白
        pAreaSetting->addStretch(40);

        m_pConfirm = new CtButton(CtSize(200, 50), STR_ID_GUIDE_ENTER, fSet_Center);
        m_pCancel = new CtButton(CtSize(200, 50), STR_ID_GUIDE_RETURN, fSet_Center);
		CtHLayout *pTwoBtn = new CtHLayout(CtColor(ColorRGBA, 0x021527ff, NULL));
        pTwoBtn->addWidget(m_pCancel);
        pTwoBtn->addWidget(m_pConfirm);
        pAreaSetting->addWidget(pTwoBtn, 50);

        // 空白
        pAreaSetting->addStretch(10);
    } else {
        // 空白、「決定」と「戻る」ボタンがない
        pAreaSetting->addStretch(100);
    }

    // Window
    m_pWin = new CtWindow();
    m_pWin->addWidget(pAreaSetting);
	//m_pWin->setInitialFocusType(FocusNormal);
	m_pWin->setRoundFocus(true);

    // 「Enter」と「Cancel」ボタンがなければ、
    // フォーカスは「NTSC1」、「NTSC2」又は「PAL」のどちらに設置する
    // AplParamによって、デフォルトフォーカスを決める、
    // フォーカスを移動したら、デフォルトの様子を変わる。
    switch(APL_PARAM_GET_DATA(AplParamUSeAreaSettings)){
    case APL_SYS_PARAM_USE_AREA_1:
//		m_pAREA1->setPressed();
		m_pWin->setDefaultFocus(m_pAREA1);
        break;
    case APL_SYS_PARAM_USE_AREA_2:
//		m_pAREA2->setPressed();
		m_pWin->setDefaultFocus(m_pAREA2);
        break;
	case APL_SYS_PARAM_USE_AREA_3:
//		m_pAREA3->setPressed();
		m_pWin->setDefaultFocus(m_pAREA3);
		break;
	case APL_SYS_PARAM_USE_AREA_4:
//		m_pAREA4->setPressed();
		m_pWin->setDefaultFocus(m_pAREA4);
		break;
	default:
//		m_pAREA3->setPressed();
		m_pWin->setDefaultFocus(m_pAREA3);
        break;
    }

    return m_pWin;
}

CtAreaSetting::~CtAreaSetting()
{
    destroyWindow();
}


bool CtAreaSetting::destroyWindow()
{
    return true;
}

bool CtAreaSetting::handleButtonEvent(const CtEventButton& Button)
{
    bool bFlag = false;

	if( Button.getChangeState() == CtEventButton::Select ) {
		if (Button.getWidget() == m_pAREA1) {
			m_pAREA2->setSelect(false);
			m_pAREA3->setSelect(false);
			m_pAREA4->setSelect(false);
			m_Area = ContentsAreaSetting_AREA1;
			bFlag = true;
		}else if(Button.getWidget() == m_pAREA2){
			m_pAREA1->setSelect(false);
			m_pAREA3->setSelect(false);
			m_pAREA4->setSelect(false);
			m_Area = ContentsAreaSetting_AREA2;
			bFlag = true;
		}else if(Button.getWidget() == m_pAREA3){
			m_pAREA1->setSelect(false);
			m_pAREA2->setSelect(false);
			m_pAREA4->setSelect(false);
			m_Area = ContentsAreaSetting_AREA3;
			bFlag = true;
		}else if (Button.getWidget() == m_pAREA4) {
			m_pAREA1->setSelect(false);
			m_pAREA2->setSelect(false);
			m_pAREA3->setSelect(false);
			m_Area = ContentsAreaSetting_AREA4;
			bFlag = true;
		}
	}

	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}

	if(m_bFlagForTwoBtn){
		if(Button.getWidget() == m_pConfirm){
			requestNextWindow();
			bFlag = true;
        }else if(Button.getWidget() == m_pCancel){
            // 当該WindowをCloseする
            CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
            bFlag = true;
        }
    }else{
		requestNextWindow();
		bFlag = true;
    }

    return bFlag;
}

bool CtAreaSetting::handleKeyEvent(const CtEventKey& Key){
    switch (Key.getKeyAction()) {
        case CtEventKey::Press:
    	    switch ( Key.getKeyCode() ) {
    	        case CtEventKey::KeyCode_Exit:
    	    	case CtEventKey::KeyCode_GripUser1:
	    	    	if( m_bFlagForTwoBtn == true ){
				        if ( NULL != m_pWin ) {
							CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
							return true;
				        }
	    	    	}
	    	        break;
    	        default:
    		        break;
    	    }
            break;
		case CtEventKey::Release:
			switch (Key.getKeyCode()) {
			case CtEventKey::KeyCode_Enter:
			case CtEventKey::KeyCode_ManualFunction:
				if (m_bFlagForTwoBtn == false) {
					requestNextWindow();
					return true;
				}
				break;
			default:
				break;
			}
			break;
		default:
            break;
    }

    return false;
}


void CtAreaSetting::requestNextWindow()
{
	CtWindowID ChangeWindowID;

	ChangeWindowID = (m_bFlagForTwoBtn ? WindowID_Menu_Area_Setting_Confirm : Window_Area_Setting_Confirm);
	CtWindowContentsAreaSettingConfirm* pContents = new CtWindowContentsAreaSettingConfirm(ChangeWindowID);
	pContents->setContentsAreaSetting(static_cast<ContentsAreaSetting>(m_Area));
	pContents->setAreaSetingType(static_cast<AreaSettingType>(FACTORY_SETTING));

	CtEventInterface::requestWindowCmd(CtEventWindow::Change, ChangeWindowID, pContents);
	delete pContents;
}

ContentsAreaSetting CtAreaSetting::chackFocusButton()
{
	ContentsAreaSetting area = ContentsAreaSetting_AREA3;
	if (m_pAREA1->isFocused() == true) {
		area = ContentsAreaSetting_AREA1;
	}
	else if (m_pAREA2->isFocused() == true) {
		area = ContentsAreaSetting_AREA2;
	}
	else if (m_pAREA3->isFocused() == true) {
		area = ContentsAreaSetting_AREA3;
	}
	else if (m_pAREA4->isFocused() == true) {
		area = ContentsAreaSetting_AREA4;
	}
	return area;
}
