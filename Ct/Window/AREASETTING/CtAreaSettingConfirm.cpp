/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtAreaSettingConfirm
 */

#include "CtAreaSettingConfirm.h"
#include "CtDebugPrint.h"
#include "CtWindowCommon.h"
#include "CtWindowContentsAreaSettingConfirm.h"

#define FACTORY_SETTING 0   // 「Enter」と「Cancel」ボタンがない
#define MENU_SETTING    1   // 「Enter」と「Cancel」ボタンがある

CtAreaSettingConfirm::CtAreaSettingConfirm(CtWindowContents *pContents) : 
    m_pWin(NULL),
    m_pConfirm(NULL),
    m_pCancel(NULL)
{
    CtWindowContentsAreaSettingConfirm* pContentsTemp = static_cast<CtWindowContentsAreaSettingConfirm*>(pContents);
    if(pContentsTemp != NULL){
        m_nUseArea = pContentsTemp->getContentsAreaSetting();
        m_nAreaSettingType = pContentsTemp->getAreaSettingType();
    }else{
        // To Be Delete
        // 一時ContentsAreaSetting_NTSC2にして、「Enter」と「Cancel」ボタンがあるようにする
        m_nUseArea = ContentsAreaSetting_AREA3;
        m_nAreaSettingType = MENU_SETTING;
    }
	setClassType(CtClassType_WindowAreaSetting);
}


CtWindow* CtAreaSettingConfirm::createWindow()
{
    CtFontSet fSet_Center = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    CtFontSet fSet_Left = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fSet_Right = CtFontSet(FontTypeNormal_alignRight,CtColor::White);

    CtVLayout *pAreaSettingConfirm = new CtVLayout(CtColor(ColorRGBA, 0x021527ff, NULL));      // スポイトでRGBの値を取得した
    // "AREA SETTINGS"
    pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_10599, fSet_Left), AlignLeft, 80);
    // 空白
    pAreaSettingConfirm->addStretch(100);

    switch(m_nUseArea){
        case ContentsAreaSetting_AREA1:
            // "This device is set with NTSC1.\nAre you sure?"
            pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_10896, fSet_Center), AlignCenter, 140);
            break;
        case ContentsAreaSetting_AREA2:
            // "This device is set with NTSC2.\nAre you sure?"
            pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_10897, fSet_Center), AlignCenter, 140);
            break;
		case ContentsAreaSetting_AREA3:
			// "This device is set with PAL.\nAre you sure?"
			pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_10898, fSet_Center), AlignCenter, 140);
			break;
		case ContentsAreaSetting_AREA4:
			// "This device is set with AREA 4.\nAre you sure?"
			pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_11564, fSet_Center), AlignCenter, 140);
			break;
		default:
            // 空白
            pAreaSettingConfirm->addStretch(140);
            break;
    }

    // 空白
    pAreaSettingConfirm->addStretch(160);

    CtHLayout *pTwoBtn = new CtHLayout(CtColor(ColorRGBA, 0x021527ff, NULL));
    m_pConfirm = new CtButton(CtSize(200, 50), STR_ID_MSG_YES, fSet_Center);
    m_pCancel = new CtButton(CtSize(200, 50), STR_ID_MSG_NO, fSet_Center);
    pTwoBtn->addWidget(m_pConfirm);
    pTwoBtn->addWidget(m_pCancel);
    pAreaSettingConfirm->addWidget(pTwoBtn, 50);

    // 空白
    pAreaSettingConfirm->addStretch(10);

    // Window
    m_pWin = new CtWindow();
    m_pWin->addWidget(pAreaSettingConfirm);
    /*m_pWin->setRegion(CtRegion(0,0,960,540));*/
    m_pWin->setVisible(true);
    m_pWin->setLayout();
    /* 初期フォーカスはCancel */
	// TODO m_pWin->setInitialFocusType(FocusNormal);
    m_pWin->setDefaultFocus(m_pCancel);
    
    return m_pWin;
}

CtAreaSettingConfirm::~CtAreaSettingConfirm()
{
    destroyWindow();
}


bool CtAreaSettingConfirm::destroyWindow()
{
    return true;
}

bool CtAreaSettingConfirm::handleButtonEvent(const CtEventButton& Button)
{
    bool bFlag = false;

    /* Releaseでのみ処理 */
    if( Button.getPressType() != CtEventButton::Release ){
        return false;
    }

	int value;
	switch (m_nUseArea){
	case ContentsAreaSetting_AREA1:
		value = APL_SYS_PARAM_USE_AREA_1;
		break;
	case ContentsAreaSetting_AREA2:
	default:
		value = APL_SYS_PARAM_USE_AREA_2;
		break;
	case ContentsAreaSetting_AREA3:
		value = APL_SYS_PARAM_USE_AREA_3;
		break;
	case ContentsAreaSetting_AREA4:
		value = APL_SYS_PARAM_USE_AREA_4;
		break;
	}

    if(m_nAreaSettingType == FACTORY_SETTING){
        if(Button.getWidget() == m_pConfirm){
            // 選択したデータをAplParamに保存して、「時間設定」画面に遷移する
        	if( APL_PARAM_GET_DATA(AplParamUSeAreaSettings) != value) {
            	APL_PARAM_SET_DATA(AplParamUSeAreaSettings, value);
        	} else {
        		APL_PARAM_EXEC_FAKE_UPDATE(AplParamUSeAreaSettings);
        	}
            bFlag = true;
        }else if(Button.getWidget() == m_pCancel){
            // 選択したデータをAplParamに保存しなくて、元のAreaSetting画面に戻る
            // 「Enter」と「Cancel」ボタンがなし
			CtEventInterface::requestWindowCmd(CtEventWindow::Return, WindowNone);
            bFlag = true;
        }else{
            // No Operation
        }
    }else if(m_nAreaSettingType == MENU_SETTING){
        if(Button.getWidget() == m_pConfirm){
            // 選択したデータをAplParamに保存して、MenuのOption画面に遷移する
        	if( APL_PARAM_GET_DATA(AplParamUSeAreaSettings) != value) {
            	APL_PARAM_SET_DATA(AplParamUSeAreaSettings, value);
        	} else {
        		APL_PARAM_EXEC_FAKE_UPDATE(AplParamUSeAreaSettings);
        	}
            // MenuのOption画面に戻る（開いたAreaSetting画面を閉じたら、十分）
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
            bFlag = true;
        }else if(Button.getWidget() == m_pCancel){
            // 選択したデータをAplParamに保存しなくて、元のAreaSetting画面に戻る
            // 「Enter」と「Cancel」ボタンがある（MenuからのAreaSetting画面）
			CtEventInterface::requestWindowCmd(CtEventWindow::Return, WindowNone);
            bFlag = true;
        }
    }

    return bFlag;
}

bool CtAreaSettingConfirm::handleKeyEvent(const CtEventKey& Key){
    bool bRet = false;

    switch (Key.getKeyAction()) {
        case CtEventKey::Press:
            switch ( Key.getKeyCode() ) {
                case CtEventKey::KeyCode_Exit:
                case CtEventKey::KeyCode_GripUser1:
                    if(m_nAreaSettingType != FACTORY_SETTING){
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
        default:
            break;
    }

    return bRet;
}





