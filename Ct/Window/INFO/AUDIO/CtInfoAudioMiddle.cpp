/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element: CtInfoAudioMiddle
 */
#include "CtInfoAudioMiddle.h"
#include "CtLabel.h"
#include "apl_sys_param_enum.h"
#include "AplParamService.h"
#include "stdio.h"

CtInfoAudioMiddle::CtInfoAudioMiddle() :
    m_pBox(NULL),
    m_pSLabelSelectCH1(NULL),
    m_pSLabelInput1(NULL),
    m_pSLabelMicPower1(NULL),
    m_pSLabelMicGain1(NULL),
    m_pSLabelLowCut1(NULL),
    m_pSLabelInputCH1(NULL),
    m_pSLabelSelectCH2(NULL),
    m_pSLabelInput2(NULL),
    m_pSLabelMicPower2(NULL),
    m_pSLabelMicGain2(NULL),
    m_pSLabelLowCut2(NULL),
    m_pSLabelInputCH2(NULL),
    m_pSLabelCh1Adjust(NULL),
    m_pSLabelLimiterCH1(NULL),
    m_pSLabelCh2Adjust(NULL),
    m_pSLabelLimiterCH2(NULL),
    m_pSLabelHeadRoom(NULL),
    m_pSLabelHpOut(NULL),
    m_pSLabelHpMode(NULL),
    m_pSLabelVolume(NULL),
    m_pCH1Selet(NULL),
    m_pCH1SeletMicOrLine(NULL),
    m_pCH1SeletMic(NULL),
    m_pCH1SeletLowCut(NULL),
    m_pCH2Selet(NULL),
    m_pCH2SeletMicOrLine(NULL),
    m_pCH2SeletMic(NULL),
    m_pCH2SeletLowCut(NULL),
    m_pCH1Level(NULL),
    m_pCH1LevelManual(NULL),
    m_pCH2Level(NULL),
    m_pCH2LevelManual(NULL),
    m_pHeadRoom(NULL),
    m_pVolume(NULL)
{
    setClassType(CtClassType_LayoutMain);
}


CtLayout* CtInfoAudioMiddle::createContainer()
{   
    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fSet1 = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);

    createInfoAudioStackLabel();

    m_pBox = new CtVLayout();

    const char string[] = ":";

    /*InfoAudio画面の情報部品を作成する*/
    m_pCH1Selet = new CtHLayout();
    m_pCH1SeletMicOrLine = new CtLayout();
    m_pCH1SeletMic = new CtHLayout();
    m_pCH1SeletLowCut = new CtHLayout();

    m_pCH2Selet = new CtHLayout();
    m_pCH2SeletMicOrLine = new CtLayout();
    m_pCH2SeletMic = new CtHLayout();
    m_pCH2SeletLowCut = new CtHLayout();

    m_pCH1Level = new CtHLayout();
    m_pCH1LevelManual = new CtHLayout();

    m_pCH2Level = new CtHLayout();
    m_pCH2LevelManual = new CtHLayout();

    m_pHeadRoom = new CtHLayout();

    /*      CH1 SELECT          */
    m_pCH1Selet->addStretch(15);
    m_pCH1Selet->addWidget(new CtLabel(STR_ID_NO_10716, fSet), 170);
    m_pCH1Selet->addWidget(new CtLabel(string, fSet), 15);
    m_pCH1Selet->addWidget(m_pSLabelSelectCH1, 120);
    m_pCH1Selet->addWidget(m_pSLabelInput1, 70);
    m_pCH1SeletMic->addWidget(m_pSLabelMicPower1, 90);
    m_pCH1SeletMic->addWidget(m_pSLabelMicGain1, 100);
    m_pCH1SeletMicOrLine->addWidget(m_pCH1SeletMic);
    m_pCH1SeletMicOrLine->addWidget(m_pSLabelInputCH1);
    m_pCH1Selet->addWidget(m_pCH1SeletMicOrLine, 190);
    m_pCH1SeletLowCut->addWidget(new CtLabel(STR_ID_NO_10719, fSet), 105);
    m_pCH1SeletLowCut->addWidget(new CtLabel(string, fSet), 10);
    m_pCH1SeletLowCut->addWidget(m_pSLabelLowCut1, 265);
    m_pCH1Selet->addWidget(m_pCH1SeletLowCut, 380);

    /*      CH2 SELECT          */
    m_pCH2Selet->addStretch(15);
    m_pCH2Selet->addWidget(new CtLabel(STR_ID_NO_10717, fSet), 170);
    m_pCH2Selet->addWidget(new CtLabel(string, fSet), 15);
    m_pCH2Selet->addWidget(m_pSLabelSelectCH2, 120);
    m_pCH2Selet->addWidget(m_pSLabelInput2, 70);
    m_pCH2SeletMic->addWidget(m_pSLabelMicPower2, 90);
    m_pCH2SeletMic->addWidget(m_pSLabelMicGain2, 100);
    m_pCH2SeletMicOrLine->addWidget(m_pCH2SeletMic);
    m_pCH2SeletMicOrLine->addWidget(m_pSLabelInputCH2);
    m_pCH2Selet->addWidget(m_pCH2SeletMicOrLine, 190);
    m_pCH2SeletLowCut->addWidget(new CtLabel(STR_ID_NO_10719, fSet), 105);
    m_pCH2SeletLowCut->addWidget(new CtLabel(string, fSet), 10);
    m_pCH2SeletLowCut->addWidget(m_pSLabelLowCut2, 265);
    m_pCH2Selet->addWidget(m_pCH2SeletLowCut, 380);

    /*   CH1 LEVEL   */
    m_pCH1Level->addStretch(15);
    m_pCH1Level->addWidget(new CtLabel(STR_ID_NO_10720, fSet), 170);
    m_pCH1Level->addWidget(new CtLabel(string, fSet), 15);
    m_pCH1Level->addWidget(m_pSLabelCh1Adjust, 140);
    m_pCH1LevelManual->addWidget(new CtLabel(STR_ID_NO_10722, fSet), 100);
    m_pCH1LevelManual->addWidget(new CtLabel(string, fSet), 10);
    m_pCH1LevelManual->addWidget(m_pSLabelLimiterCH1, 510);
    m_pCH1Level->addWidget(m_pCH1LevelManual, 620);

    /*   CH2 LEVEL   */
    m_pCH2Level->addStretch(15);
    m_pCH2Level->addWidget(new CtLabel(STR_ID_NO_10721, fSet), 170);
    m_pCH2Level->addWidget(new CtLabel(string, fSet), 15);
    m_pCH2Level->addWidget(m_pSLabelCh2Adjust, 140);
    m_pCH2LevelManual->addWidget(new CtLabel(STR_ID_NO_10722, fSet), 100);
    m_pCH2LevelManual->addWidget(new CtLabel(string, fSet), 10);
    m_pCH2LevelManual->addWidget(m_pSLabelLimiterCH2, 510);
    m_pCH2Level->addWidget(m_pCH2LevelManual, 620);
    
    /* HEAD ROOM */
    m_pHeadRoom->addStretch(15);
    m_pHeadRoom->addWidget(new CtLabel(STR_ID_NO_10839, fSet), 170);
    m_pHeadRoom->addWidget(new CtLabel(string, fSet), 15);
    m_pHeadRoom->addWidget(m_pSLabelHeadRoom, 760);

    /* MONITOR */
    CtHLayout *pMonitor = new CtHLayout();
    pMonitor->addStretch(15);
    pMonitor->addWidget(new CtLabel(STR_ID_NO_10723, fSet), 170);
    pMonitor->addWidget(new CtLabel(string, fSet), 15);
    pMonitor->addWidget(m_pSLabelHpOut, 110);
    pMonitor->addWidget(new CtLabel(STR_ID_NO_10724, fSet), 85);
    pMonitor->addWidget(new CtLabel(string, fSet), 10);
    pMonitor->addWidget(m_pSLabelHpMode, 170);
    pMonitor->addWidget(new CtLabel(STR_ID_NO_10725, fSet), 55);
    pMonitor->addWidget(new CtLabel(string, fSet), 10);
    char strVolume[10];
    memset(strVolume,0,sizeof(strVolume));
    signed int nTempVolume = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamVolume));
    sprintf(strVolume,"%d",nTempVolume);
    m_pVolume = new CtLabel(strVolume, fSet);
    pMonitor->addWidget(m_pVolume, 320);

    m_pBox->addStretch(12);
    m_pBox->addWidget(m_pCH1Selet,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(m_pCH2Selet,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(m_pCH1Level,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(m_pCH2Level,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(m_pHeadRoom,48);
    m_pBox->addStretch(6);
    m_pBox->addWidget(pMonitor,48);
    m_pBox->addStretch(12);

    m_pBox->setName("@@@CtInfoAudioMiddle@@@");

    /*AplParamの設定値により画面の表示情報を更新する*/
    updateCH1Selet();
    updateCH2Selet();
    updateCH1Level();
    updateCH2Level();
    updateHeadRoom();
    updateMonitor();

    return m_pBox;
}

bool CtInfoAudioMiddle::destroyContainer() {
	return true;
}

CtInfoAudioMiddle::~CtInfoAudioMiddle()
{
}

    /*  SET STACKLABEL FOR INFOAUDIO  */
void CtInfoAudioMiddle::createInfoAudioStackLabel(){

    CtFontSet fSet = CtFontSet(FontTypeNormal,CtColor::White);    
    m_pSLabelSelectCH1 = new CtStackLabel();
    m_pSLabelSelectCH1->addLabel(new CtLabel(STR_ID_NO_10764, fSet, CtMargin(4)));     //StringID            "INT(L)"
    m_pSLabelSelectCH1->addLabel(new CtLabel(STR_ID_NO_10798, fSet, CtMargin(4)));     //StringID            "INPUT1"

    m_pSLabelInput1 = new CtStackLabel();
    m_pSLabelInput1->addLabel(new CtLabel(STR_ID_NO_10767, fSet, CtMargin(4)));          //StringID            "LINE"
    m_pSLabelInput1->addLabel(new CtLabel(STR_ID_NO_10766, fSet, CtMargin(4)));           //StringID            "MIC"

    m_pSLabelMicPower1 = new CtStackLabel();
    m_pSLabelMicPower1->addLabel(new CtLabel("", fSet, CtMargin(4)));            //StringID            Non
    m_pSLabelMicPower1->addLabel(new CtLabel(STR_ID_NO_10718, fSet, CtMargin(4)));        //StringID            "+48V"

    m_pSLabelMicGain1 = new CtStackLabel();
    m_pSLabelMicGain1->addLabel(new CtLabel(STR_ID_NO_10402, fSet, CtMargin(4)));        //StringID            "-40dB"
    m_pSLabelMicGain1->addLabel(new CtLabel(STR_ID_NO_10403, fSet, CtMargin(4)));        //StringID            "-50dB"
    m_pSLabelMicGain1->addLabel(new CtLabel(STR_ID_NO_10404, fSet, CtMargin(4)));        //StringID            "-60dB"

    m_pSLabelLowCut1 = new CtStackLabel();
    m_pSLabelLowCut1->addLabel(new CtLabel(STR_ID_NO_10792, fSet, CtMargin(4)));            //StringID            "OFF"
    m_pSLabelLowCut1->addLabel(new CtLabel(STR_ID_NO_10836, fSet, CtMargin(4)));             //StringID            "ON"

    m_pSLabelInputCH1 = new CtStackLabel();
    m_pSLabelInputCH1->addLabel(new CtLabel(STR_ID_NO_10408, fSet, CtMargin(4)));          //StringID            "0dB"
    m_pSLabelInputCH1->addLabel(new CtLabel(STR_ID_NO_10407, fSet, CtMargin(4)));          //StringID            "4dB"

    m_pSLabelSelectCH2 = new CtStackLabel();
    m_pSLabelSelectCH2->addLabel(new CtLabel(STR_ID_NO_10765, fSet, CtMargin(4)));      //StringID            "INT(R)"
    m_pSLabelSelectCH2->addLabel(new CtLabel(STR_ID_NO_10798, fSet, CtMargin(4)));      //StringID            "INPUT1"
    m_pSLabelSelectCH2->addLabel(new CtLabel(STR_ID_NO_10799, fSet, CtMargin(4)));      //StringID            "INPUT2"

    m_pSLabelInput2 = new CtStackLabel();
    m_pSLabelInput2->addLabel(new CtLabel(STR_ID_NO_10767, fSet, CtMargin(4)));           //StringID            "LINE"
    m_pSLabelInput2->addLabel(new CtLabel(STR_ID_NO_10766, fSet, CtMargin(4)));            //StringID            "MIC"

    m_pSLabelMicPower2 = new CtStackLabel();
    m_pSLabelMicPower2->addLabel(new CtLabel("", fSet, CtMargin(4)));            //StringID            Non
    m_pSLabelMicPower2->addLabel(new CtLabel(STR_ID_NO_10718, fSet, CtMargin(4)));        //StringID            "+48V"

    m_pSLabelMicGain2 = new CtStackLabel();
    m_pSLabelMicGain2->addLabel(new CtLabel(STR_ID_NO_10402, fSet, CtMargin(4)));        //StringID            "-40dB"
    m_pSLabelMicGain2->addLabel(new CtLabel(STR_ID_NO_10403, fSet, CtMargin(4)));        //StringID            "-50dB"
    m_pSLabelMicGain2->addLabel(new CtLabel(STR_ID_NO_10404, fSet, CtMargin(4)));        //StringID            "-60dB"

    m_pSLabelLowCut2 = new CtStackLabel();
    m_pSLabelLowCut2->addLabel(new CtLabel(STR_ID_NO_10792, fSet, CtMargin(4)));           //StringID            "OFF"
    m_pSLabelLowCut2->addLabel(new CtLabel(STR_ID_NO_10836, fSet, CtMargin(4)));            //StringID            "ON"

    m_pSLabelInputCH2 = new CtStackLabel();
    m_pSLabelInputCH2->addLabel(new CtLabel(STR_ID_NO_10408, fSet, CtMargin(4)));          //StringID            "0dB"
    m_pSLabelInputCH2->addLabel(new CtLabel(STR_ID_NO_10407, fSet, CtMargin(4)));          //StringID            "4dB"
    
    m_pSLabelCh1Adjust = new CtStackLabel();
    m_pSLabelCh1Adjust->addLabel(new CtLabel(STR_ID_NO_10837, fSet, CtMargin(4)));        //StringID            "AUTO"
    m_pSLabelCh1Adjust->addLabel(new CtLabel(STR_ID_NO_10838, fSet, CtMargin(4)));      //StringID            "MANUAL"

    m_pSLabelLimiterCH1 = new CtStackLabel();
    m_pSLabelLimiterCH1->addLabel(new CtLabel(STR_ID_NO_10792, fSet, CtMargin(4)));        //StringID            "OFF"
    m_pSLabelLimiterCH1->addLabel(new CtLabel(STR_ID_NO_10836, fSet, CtMargin(4)));         //StringID            "ON"
    
    m_pSLabelCh2Adjust = new CtStackLabel();
    m_pSLabelCh2Adjust->addLabel(new CtLabel(STR_ID_NO_10837, fSet, CtMargin(4)));        //StringID            "AUTO"
    m_pSLabelCh2Adjust->addLabel(new CtLabel(STR_ID_NO_10838, fSet, CtMargin(4)));      //StringID            "MANUAL"

    m_pSLabelLimiterCH2 = new CtStackLabel();
    m_pSLabelLimiterCH2->addLabel(new CtLabel(STR_ID_NO_10792, fSet, CtMargin(4)));        //StringID            "OFF"
    m_pSLabelLimiterCH2->addLabel(new CtLabel(STR_ID_NO_10836, fSet, CtMargin(4)));         //StringID            "ON"

    m_pSLabelHeadRoom = new CtStackLabel();
    m_pSLabelHeadRoom->addLabel(new CtLabel(STR_ID_NO_10391, fSet, CtMargin(4)));         //StringID            "18dB"
    m_pSLabelHeadRoom->addLabel(new CtLabel(STR_ID_NO_10392, fSet, CtMargin(4)));         //StringID            "20dB"

    m_pSLabelHpOut = new CtStackLabel();
    m_pSLabelHpOut->addLabel(new CtLabel(STR_ID_NO_10840, fSet, CtMargin(4)));             //StringID            "CH1"
    m_pSLabelHpOut->addLabel(new CtLabel(STR_ID_NO_10841, fSet, CtMargin(4)));             //StringID            "CH2"
    m_pSLabelHpOut->addLabel(new CtLabel(STR_ID_NO_10842, fSet, CtMargin(4)));          //StringID            "STEREO"
    m_pSLabelHpOut->addLabel(new CtLabel(STR_ID_NO_10843, fSet, CtMargin(4)));             //StringID            "MIX"

    m_pSLabelHpMode = new CtStackLabel();
    m_pSLabelHpMode->addLabel(new CtLabel( STR_ID_NO_10844, fSet, CtMargin(4)));      //StringID            "LIVE"
    m_pSLabelHpMode->addLabel(new CtLabel( STR_ID_NO_10845, fSet, CtMargin(4)));      //StringID            "RECORDING"
    
}

bool CtInfoAudioMiddle::handleParamEvent(const CtEventParam& Param){
    bool bRet = false;
    int t_Id = Param.getParamId();
    
    switch(t_Id){
        case AplParamSelInput1:     //CH1 SELECTのAplParamID
        case AplParamInSelectCH1:   //CH1 SELECTのAplParamID
        case AplParamMicPower1:     //CH1 SELECTのAplParamID
        case AplParamMicGain1:      //CH1 SELECTのAplParamID
        case AplParamLowCut:        //CH1 SELECTのAplParamID
        case AplParamLineInputCH1:  //CH1 SELECTのAplParamID
            updateCH1Selet();
            bRet = true;
            break;
        case AplParamSelInput2:     //CH2 SELECTのAplParamID
        case AplParamInSelectCH2:   //CH2 SELECTのAplParamID
        case AplParamMicPower2:     //CH2 SELECTのAplParamID
        case AplParamMicGain2:      //CH2 SELECTのAplParamID
        case AplParamLowCut2:       //CH2 SELECTのAplParamID
        case AplParamLineInputCH2:  //CH2 SELECTのAplParamID
            updateCH2Selet(); 
            bRet = true;
            break;
        case AplParamCh1Adjust:     //CH1 LEVELのAplParamID
        case AplParamLimiterCH1:    //CH1 LEVELのAplParamID
            updateCH1Level();
            bRet = true;
            break;
        case AplParamCh2Adjust:     //CH2 LEVELのAplParamID
        case AplParamLimiterCH2:    //CH2 LEVELのAplParamID
            updateCH2Level();
            bRet = true;
            break;
        case AplParamHeadRoom:      //HEAD ROOMのAplParamID
            updateHeadRoom();
            bRet = true;
            break;
        case AplParamHpOut:         //MONITORのAplParamID
        case AplParamHpMode:        //MONITORのAplParamID
        case AplParamVolume:        //MONITORのAplParamID
            updateMonitor();
            bRet = true;
            break;
        default:
            break;
    }

    return bRet;
}

void CtInfoAudioMiddle::updateCH1Selet(){

    signed int nTempSelectCH1 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamInSelectCH1));
    signed int nTempSelInput1 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSelInput1));
    signed int nTempMicPower1 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamMicPower1));
    signed int nTempMicGain1 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamMicGain1));
    signed int nTempLowCut1 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamLowCut));
    signed int nTempLineInputCH1 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamLineInputCH1));

    m_pSLabelSelectCH1->index(nTempSelectCH1);
    m_pSLabelInput1->index(nTempSelInput1);
    m_pSLabelMicPower1->index(nTempMicPower1);
    m_pSLabelMicGain1->index(nTempMicGain1);
    m_pSLabelLowCut1->index(nTempLowCut1);
    m_pSLabelInputCH1->index(nTempLineInputCH1);

    if(APL_SYS_PARAM_CH_IN_SELECT_INT == nTempSelectCH1){
        m_pSLabelInput1->setVisible(false);
        m_pCH1SeletMicOrLine->setVisible(false);
        m_pCH1SeletLowCut->setVisible(false);
    }else{

        if(APL_SYS_PARAM_SELECT_INPUT_LINE == nTempSelInput1){
            m_pSLabelInput1->setVisible(true);
            m_pCH1SeletMicOrLine->setVisible(true);
            m_pCH1SeletMic->setVisible(false);
            m_pSLabelInputCH1->setVisible(true);
            m_pCH1SeletLowCut->setVisible(false);
        }else{
            m_pSLabelInput1->setVisible(true);
            m_pCH1SeletMicOrLine->setVisible(true);
            m_pCH1SeletMic->setVisible(true);
            m_pSLabelInputCH1->setVisible(false);
            m_pCH1SeletLowCut->setVisible(true);
        }

    }

}

void CtInfoAudioMiddle::updateCH2Selet(){

    signed int nTempSelectCH2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamInSelectCH2));
    signed int nTempSelInput2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSelInput2));
    signed int nTempMicPower2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamMicPower2));
    signed int nTempMicGain2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamMicGain2));
    signed int nTempLowCut2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamLowCut2));
    signed int nTempLineInputCH2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamLineInputCH2));

	// INPUT1が選択されている場合はINPUT1の情報で上書きする
	if( APL_SYS_PARAM_CH_IN_SELECT_INPUT1 == nTempSelectCH2 ){
		nTempSelInput2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamSelInput1));
		nTempMicPower2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamMicPower1));
		nTempMicGain2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamMicGain1));
		nTempLineInputCH2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamLineInputCH1));
	}
	
    m_pSLabelSelectCH2->index(nTempSelectCH2);
    m_pSLabelInput2->index(nTempSelInput2);
    m_pSLabelMicPower2->index(nTempMicPower2);
    m_pSLabelMicGain2->index(nTempMicGain2);
    m_pSLabelLowCut2->index(nTempLowCut2);
    m_pSLabelInputCH2->index(nTempLineInputCH2);

    if(APL_SYS_PARAM_CH_IN_SELECT_INT == nTempSelectCH2){
        m_pSLabelInput2->setVisible(false);
        m_pCH2SeletMicOrLine->setVisible(false);
        m_pCH2SeletLowCut->setVisible(false);
    }else{

        if(APL_SYS_PARAM_SELECT_INPUT_LINE == nTempSelInput2){
            m_pSLabelInput2->setVisible(true);
            m_pCH2SeletMicOrLine->setVisible(true);
            m_pCH2SeletMic->setVisible(false);
            m_pSLabelInputCH2->setVisible(true);
            m_pCH2SeletLowCut->setVisible(false);
        }else{
            m_pSLabelInput2->setVisible(true);
            m_pCH2SeletMicOrLine->setVisible(true);
            m_pCH2SeletMic->setVisible(true);
            m_pSLabelInputCH2->setVisible(false);
            m_pCH2SeletLowCut->setVisible(true);
        }

    }

}

void CtInfoAudioMiddle::updateCH1Level(){

    signed int nTempCh1Adjust = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamCh1Adjust));
    signed int nTempLimiterCH1 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamLimiterCH1));

    m_pSLabelCh1Adjust->index(nTempCh1Adjust);
    m_pSLabelLimiterCH1->index(nTempLimiterCH1);

    if(APL_SYS_PARAM_CH_ADJUST_AUTO == nTempCh1Adjust){
        m_pCH1LevelManual->setVisible(false);
    }else{
        m_pCH1LevelManual->setVisible(true);
    }

}

void CtInfoAudioMiddle::updateCH2Level(){

    signed int nTempCh2Adjust = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamCh2Adjust));
    signed int nTempLimiterCH2 = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamLimiterCH2));

    m_pSLabelCh2Adjust->index(nTempCh2Adjust);
    m_pSLabelLimiterCH2->index(nTempLimiterCH2);

    if(APL_SYS_PARAM_CH_ADJUST_AUTO == nTempCh2Adjust){
        m_pCH2LevelManual->setVisible(false);
    }else{
        m_pCH2LevelManual->setVisible(true);
    }

}

void CtInfoAudioMiddle::updateHeadRoom(){

    signed int nTemm_pHeadRoom = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamHeadRoom));
    
    m_pSLabelHeadRoom->index(nTemm_pHeadRoom);

}

void CtInfoAudioMiddle::updateMonitor(){

    signed int nTempHpOut = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamHpOut));
    signed int nTempHpMode = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamHpMode));

    m_pSLabelHpOut->index(nTempHpOut);
    m_pSLabelHpMode->index(nTempHpMode);

    char strVolume[10];
    memset(strVolume,0,sizeof(strVolume));
    signed int nTempVolume = static_cast<signed int>(APL_PARAM_GET_DATA(AplParamVolume));
    sprintf(strVolume,"%d",nTempVolume);
    m_pVolume->setText(strVolume);

}
