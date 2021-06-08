/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoSwitchesMiddle
 */
#include "CtInfoSwitchesMiddle.h"
#include "CtLabel.h"
#include "apl_sys_param_enum.h"
#include "AplParamService.h"
#include "stdio.h"
CtInfoSwitchesMiddle::CtInfoSwitchesMiddle() :
    m_pBox(NULL),
    m_pSLabelToggle(NULL),
    m_pSLabelUser1(NULL),
    m_pSLabelUser2(NULL),
    m_pSLabelUser3(NULL),
    m_pSLabelUser4(NULL),
    m_pSLabelUser5(NULL),
    m_pSLabelUser6(NULL),
    m_pSLabelUser7(NULL),
    m_pSLabelUser8(NULL),
    m_pSLabelUser9(NULL)
{
    setClassType(CtClassType_LayoutMain);
}

bool CtInfoSwitchesMiddle::inputMsgToStackLabel(CtStackLabel *m_pSLabel)
{
    if (NULL == m_pSLabel) {
        return false;
    }
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);

    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10803, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10804, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10805, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10806, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10762, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10763, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10089, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10807, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10808, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10809, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10810, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10811, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10812, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10813, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10814, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10815, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10816, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10817, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10818, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10819, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10820, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10821, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10822, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10823, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10824, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10825, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10826, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10827, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10828, fSet, CtMargin(4)));
    m_pSLabel->addLabel(new CtLabel(STR_ID_NO_10829, fSet, CtMargin(4)));


    return true;
}

CtLayout* CtInfoSwitchesMiddle::createContainer()
{


    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fCenterSet = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    m_pBox = new CtVLayout();

    m_pSLabelToggle = new CtStackLabel();
    m_pSLabelUser1 = new CtStackLabel();
    m_pSLabelUser2 = new CtStackLabel();
    m_pSLabelUser3 = new CtStackLabel();
    m_pSLabelUser4 = new CtStackLabel();
    m_pSLabelUser5 = new CtStackLabel();
    m_pSLabelUser6 = new CtStackLabel();
    m_pSLabelUser7 = new CtStackLabel();
    m_pSLabelUser8 = new CtStackLabel();
    m_pSLabelUser9 = new CtStackLabel();

    inputMsgToStackLabel(m_pSLabelUser1);
    inputMsgToStackLabel(m_pSLabelUser2);
    inputMsgToStackLabel(m_pSLabelUser3);
    inputMsgToStackLabel(m_pSLabelUser4);
    inputMsgToStackLabel(m_pSLabelUser5);
    inputMsgToStackLabel(m_pSLabelUser6);
    inputMsgToStackLabel(m_pSLabelUser7);
    inputMsgToStackLabel(m_pSLabelUser8);
    inputMsgToStackLabel(m_pSLabelUser9);

    m_pSLabelToggle->addLabel(new CtLabel(STR_ID_NO_10803, fSet, CtMargin(4)));	/* 10083: 「INHIBIT」: ユーザースイッチに機能を割り当てない */
    m_pSLabelToggle->addLabel(new CtLabel(STR_ID_NO_10790, fSet, CtMargin(4)));	/* 10114: 「SHUTTER」: シャッター */
    m_pSLabelToggle->addLabel(new CtLabel(STR_ID_NO_10789, fSet, CtMargin(4)));	/* 10115: 「FPS」: バリアブルフレームレート */
    m_pSLabelToggle->addLabel(new CtLabel(STR_ID_NO_10830, fSet, CtMargin(4)));	/* 10116: 「MONITOR VOL」: PHONES端子から出力する音声のレベル */

    const char string[] = ":";

    /*InfoSwitches画面の情報部品を作成する*/
    CtHLayout *pUser1AndUser4 = new CtHLayout();
    CtHLayout *pUser2AndUser5 = new CtHLayout();
    CtHLayout *pUser3AndUser6 = new CtHLayout();
    CtHLayout *pUserToggleAndUser7 = new CtHLayout();
    CtHLayout *pUser8 = new CtHLayout();
    CtHLayout *pUser9 = new CtHLayout();

    pUser1AndUser4->addStretch(16);
    pUser1AndUser4->addWidget(new CtLabel(STR_ID_1,fSet),16);
    pUser1AndUser4->addWidget(new CtLabel(string,fCenterSet),16);
    pUser1AndUser4->addWidget(m_pSLabelUser1,432);
    pUser1AndUser4->addStretch(16);
    pUser1AndUser4->addWidget(new CtLabel(STR_ID_4,fSet),16);
    pUser1AndUser4->addWidget(new CtLabel(string,fCenterSet),16);
    pUser1AndUser4->addWidget(m_pSLabelUser4,432);

    pUser2AndUser5->addStretch(16);
    pUser2AndUser5->addWidget(new CtLabel(STR_ID_2,fSet),16);
    pUser2AndUser5->addWidget(new CtLabel(string,fCenterSet),16);
    pUser2AndUser5->addWidget(m_pSLabelUser2,432);
    pUser2AndUser5->addStretch(16);
    pUser2AndUser5->addWidget(new CtLabel(STR_ID_5,fSet),16);
    pUser2AndUser5->addWidget(new CtLabel(string,fCenterSet),16);
    pUser2AndUser5->addWidget(m_pSLabelUser5,432);

    pUser3AndUser6->addStretch(16);
    pUser3AndUser6->addWidget(new CtLabel(STR_ID_3,fSet),16);
    pUser3AndUser6->addWidget(new CtLabel(string,fCenterSet),16);
    pUser3AndUser6->addWidget(m_pSLabelUser3,432);
    pUser3AndUser6->addStretch(16);
    pUser3AndUser6->addWidget(new CtLabel(STR_ID_6,fSet),16);
    pUser3AndUser6->addWidget(new CtLabel(string,fCenterSet),16);
    pUser3AndUser6->addWidget(m_pSLabelUser6,432);

    pUserToggleAndUser7->addStretch(16);
    pUserToggleAndUser7->addWidget(new CtLabel(STR_ID_NO_10704,fSet),116);
    pUserToggleAndUser7->addWidget(new CtLabel(string,fCenterSet),16);
    pUserToggleAndUser7->addWidget(m_pSLabelToggle,332);
    pUserToggleAndUser7->addStretch(16);
    pUserToggleAndUser7->addWidget(new CtLabel(STR_ID_7,fSet),16);
    pUserToggleAndUser7->addWidget(new CtLabel(string,fCenterSet),16);
    pUserToggleAndUser7->addWidget(m_pSLabelUser7,432);

    pUser8->addStretch(16);
    pUser8->addWidget(new CtLabel(STR_ID_8,fSet),16);
    pUser8->addWidget(new CtLabel(string,fCenterSet),16);
    pUser8->addWidget(m_pSLabelUser8,912); 

    pUser9->addStretch(16);
    pUser9->addWidget(new CtLabel(STR_ID_9,fSet),16);
    pUser9->addWidget(new CtLabel(string,fCenterSet),16);
    pUser9->addWidget(m_pSLabelUser9,912); 

    m_pBox->addStretch(12);
    m_pBox->addWidget(pUser1AndUser4,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pUser2AndUser5,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pUser3AndUser6,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pUserToggleAndUser7,48);
    m_pBox->addStretch(5);
    m_pBox->addWidget(new CtLabel(CtRect(CtColor::lightGray,0,CtColor::NoColor)),2);
    m_pBox->addStretch(5);
    m_pBox->addWidget(pUser8,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pUser9,48);
    m_pBox->addStretch(12);

    m_pBox->setName("@@@CtInfoSwitchesMiddle@@@");

    /*AplParamの設定値により画面の表示情報を更新する*/
    updateUser();

    return m_pBox;
}

bool CtInfoSwitchesMiddle::destroyContainer() {
	return true;
}

CtInfoSwitchesMiddle::~CtInfoSwitchesMiddle()
{
}

int CtInfoSwitchesMiddle::getUserParamView(const int paramId){
    int userParamView[] = {
        APL_SYS_PARAM_USER_BUTTON_INH,
        APL_SYS_PARAM_USER_BUTTON_AWB,
        APL_SYS_PARAM_USER_BUTTON_PUSH_AF,
        APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS,
        APL_SYS_PARAM_USER_BUTTON_ATW,
        APL_SYS_PARAM_USER_BUTTON_ATW_LOCK,
        APL_SYS_PARAM_USER_BUTTON_EIS,
        APL_SYS_PARAM_USER_BUTTON_D_ZOOM,
        APL_SYS_PARAM_USER_BUTTON_IR_MODE,
        APL_SYS_PARAM_USER_BUTTON_REC_SW,
        APL_SYS_PARAM_USER_BUTTON_PREREC,
        APL_SYS_PARAM_USER_BUTTON_REC_CHECK,
        APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE,
        APL_SYS_PARAM_USER_BUTTON_LAST_CLIP,
        APL_SYS_PARAM_USER_BUTTON_SLOT_SEL,
        APL_SYS_PARAM_USER_BUTTON_FA,
        APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA,
        APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA,
        APL_SYS_PARAM_USER_BUTTON_WFM,
        APL_SYS_PARAM_USER_BUTTON_SPOT_METER,
        APL_SYS_PARAM_USER_BUTTON_ZEBRA,
        APL_SYS_PARAM_USER_BUTTON_LEVEL,
        APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET,
        APL_SYS_PARAM_USER_BUTTON_SDI_COLOR,
        APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR,
        APL_SYS_PARAM_USER_BUTTON_LCD_COLOR,
        APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW,
        APL_SYS_PARAM_USER_BUTTON_LCD_MARKER,
        APL_SYS_PARAM_USER_BUTTON_COLOR_BARS,
        APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    };

    int nTemp = (APL_PARAM_GET_DATA(paramId));
    for(int view = 0; view < sizeof(userParamView)/sizeof(int); view++){        /* pgr0360 */
        if( nTemp == userParamView[view]){
            return view;
        }
    }
    return -1;
}

int CtInfoSwitchesMiddle::getToggleView(const int paramId){
    int userParamView[] = {
        APL_SYS_PARAM_USER_TOGGLE_INH,
        APL_SYS_PARAM_USER_TOGGLE_SHUTTER,
        APL_SYS_PARAM_USER_TOGGLE_FPS,
        APL_SYS_PARAM_USER_TOGGLE_MONITOR_VOL,
    };
    
    int nTemp = (APL_PARAM_GET_DATA(paramId));
    for(int view = 0; view < sizeof(userParamView)/sizeof(int); view++){        /* pgr0360 */
        if( nTemp == userParamView[view]){
            return view;
        }
    }
    return -1;
}

void CtInfoSwitchesMiddle::updateUser(){
    m_pSLabelToggle->index(getToggleView(AplParamUserToggle));
    m_pSLabelUser1->index(getUserParamView(AplParamUserButton1));
    m_pSLabelUser2->index(getUserParamView(AplParamUserButton2));
    m_pSLabelUser3->index(getUserParamView(AplParamUserButton3));
    m_pSLabelUser4->index(getUserParamView(AplParamUserButton4));
    m_pSLabelUser5->index(getUserParamView(AplParamUserButton5));
    m_pSLabelUser6->index(getUserParamView(AplParamUserButton6));
    m_pSLabelUser7->index(getUserParamView(AplParamUserButton7));
    m_pSLabelUser8->index(getUserParamView(AplParamUserButton8));
    m_pSLabelUser9->index(getUserParamView(AplParamUserButton9));
}

bool CtInfoSwitchesMiddle::handleParamEvent(const CtEventParam& Param){
    bool bRet = false;
    int t_Id = Param.getParamId();
    
    switch(t_Id){
        case AplParamUserToggle:
            m_pSLabelToggle->index(getToggleView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton1:
            m_pSLabelUser1->index(getUserParamView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton2:
            m_pSLabelUser2->index(getUserParamView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton3:
            m_pSLabelUser3->index(getUserParamView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton4:
            m_pSLabelUser4->index(getUserParamView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton5:
            m_pSLabelUser5->index(getUserParamView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton6:
            m_pSLabelUser6->index(getUserParamView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton7:
            m_pSLabelUser7->index(getUserParamView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton8:
            m_pSLabelUser8->index(getUserParamView(t_Id));
            bRet = true;
            break;
        case AplParamUserButton9:
            m_pSLabelUser9->index(getUserParamView(t_Id));
            bRet = true;
            break;
        default:
            break;
    }

    return bRet;
}
