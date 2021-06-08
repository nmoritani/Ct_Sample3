/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */


#include "CtWindowHome.h"
#include "string_api.h"
#include "str_id.h"

CtColor CtWindowHome::LabelColor(71,71,74,0xff);
CtColor CtWindowHome:: RectColor(40,41,44,0xff);
CtColor CtWindowHome::ImagColor(240,240,240,0xff);
CtColor CtWindowHome::LineColor(96,96,96,0xff);

CtWindowHome::CtWindowHome():
m_pWin(NULL),
m_pClip(NULL),
m_pClipNull(NULL),
m_pClipName(NULL),
m_pClipNo(NULL),
m_pFpsName(NULL),
m_pVRFOn(NULL),
m_pVRFOff(NULL),
m_pFpsIntLayout(NULL),
m_pFpsDecLayout(NULL),
m_pLabelIntPart(NULL),
m_pLabelDecPart(NULL),
m_pLabelInterlace(NULL),
m_pLabelFpsOnInt(NULL),
m_pDecFpsIcon(NULL),

m_pLabelMainColor(NULL),
m_pLabelSubColor(NULL),
m_pMainVLog(NULL),
m_pSubOff(NULL),
m_pMainScene(NULL),
m_pLabelSceneName(NULL),

m_pLabelSec(NULL),
m_pLabelDeg(NULL),
m_pShutterOff(NULL),
m_pShutterSec(NULL),
m_pShutterDeg(NULL),
m_pLabelIsoSel(NULL),
m_pLabelGainSel(NULL),
m_pLabelGain(NULL),

m_pISONative(NULL),
m_pISO800Base(NULL),
m_pISO2500Base(NULL),
m_pEiIso(NULL),
m_pEiGain(NULL),
m_pLabelCH1(NULL),
m_pLabelCH2(NULL),
m_pLabelSelCH1(NULL),
m_pLabelSelCH2(NULL),
m_pLabelSelInput(NULL),

m_pLabelWb(NULL),
m_pLabelWbNum(NULL),
m_pWbNum(NULL),
m_pATW(NULL),

m_pLabel2SlotOrSub(NULL),
m_pLabelBothCenter2Slot(NULL),
m_pLabelBothCenterRec(NULL),
m_pLabelCenter2Slot(NULL),
m_pLabelSubRec(NULL),
m_pLabelUpperRight(NULL),
m_pLabelLowerRight(NULL),
m_pLowerLeft(NULL),
m_pLowerRight(NULL),
m_pUpperRight(NULL),
m_pLowerLeftAndCenter(NULL),
m_pCenter(NULL),
m_pBothCenter(NULL),
m_p2SlotFuncNull(NULL),

m_pLabelSdiOutColor(NULL),
m_pLabelHdmiOutColor(NULL),
m_pLabelLcdOutColor(NULL),
m_pLabelMainOutColor(NULL),
m_pOutColorX3(NULL),
m_pOutColorX1(NULL),

m_pLabelSysSta(NULL),
m_pLabelMainCodec(NULL),

m_pButtonFps(NULL),
m_pButtonColor(NULL),
m_pButtonShutter(NULL),
m_pButtonEi(NULL),
m_pButtonAudio(NULL),
m_pButtonWb(NULL),

m_FocusButton(ButtonIdFps),
m_bTouchButton(true),
m_bManualFunction(false),

m_bHighLight(false),
m_bCanMmr(true)

{
    memset( m_SceneFileName, 0, sizeof( m_SceneFileName ) );
    
}

CtWindow* CtWindowHome::createWindow()
{
    CtDebugPrint(CtDbg, "******* CtWindowHome::createWindow*******\n");
	m_pWin = new CtWindow();
	
 // **************************pLayoutUpper begin   ***********************************************
    CtLayout *pLayoutUpperBtn = create3BtnLayout( LayoutIdentifyUpper ); // 110
    CtLayout *pLayoutUpperBtnName = create3BtnNameUpperLayout();
    
    CtVLayout *pLayoutUpper = new CtVLayout( CtWindowHome::LabelColor );
    pLayoutUpper->addStretch( 3 );
    pLayoutUpper->addWidget( pLayoutUpperBtn, 110 );
    pLayoutUpper->addWidget( pLayoutUpperBtnName, 45 );
// *****************************pLayoutUpper end *************************************************   
// *****************************pLayoutCenter begin***********************************************
    CtLayout* pLayoutCenterLeft = createCenterLeftLayout();
    CtLayout* pLayoutCenterRight = createCenterRightLayout();
    CtHLayout* pLayoutCenter = new CtHLayout( CtColor::Black ); //  224
    pLayoutCenter->addWidget( pLayoutCenterLeft, 308 );
    pLayoutCenter->addStretch( 16 );
    pLayoutCenter->addWidget( pLayoutCenterRight, 636 );
// *****************************pLayoutCenter end ************************************************
// *****************************pLayoutLower begin************************************************
    CtLayout* pLayoutLowerBtnName = create3BtnNameLowerLayout();
    CtLayout *pLayoutLowerBtn = create3BtnLayout( LayoutIdentifyLower );  // 110
    
    CtVLayout *pLayoutLower = new CtVLayout( CtWindowHome::LabelColor ); //  158
    pLayoutLower->addWidget( pLayoutLowerBtnName, 45 );
    pLayoutLower->addWidget( pLayoutLowerBtn, 110 );
    pLayoutLower->addStretch( 3 );
// *****************************pLayoutLower end *************************************************
	CtVLayout *pLayoutAll = new CtVLayout();
	pLayoutAll->addWidget( pLayoutUpper, 158 );
	pLayoutAll->addWidget( pLayoutCenter, 224 );
	pLayoutAll->addWidget( pLayoutLower, 158 );
	m_pWin->addWidget( pLayoutAll );

	//pWin->setWindowID(id);
	//	m_pWin->setColor(CtColor::darkGreen);
	//	m_pWin->setRegion(CtRegion(0, 0, 960, 640), 0);
	//	m_pWin->setLayout(0);
	//	m_pWin->setRegion(CtRegion(0, 0, 960, 540), 1);
	//	m_pWin->setLayout(1);
	//m_pWin->setVisible(true);
	//m_pWin->setDialIndex();
	
	return m_pWin;
}

CtLayout* CtWindowHome::create3BtnNameUpperLayout(){
    CtLabel *pLabelLeftLine = new CtLabel( CtRect( CtWindowHome::RectColor, 1, CtWindowHome::RectColor ) ); // 18
    CtVLayout *pLayoutLeftLine = new CtVLayout();
    pLayoutLeftLine->addStretch( 15 );
    pLayoutLeftLine->addWidget( pLabelLeftLine, 18 );
    pLayoutLeftLine->addStretch( 12 );

    CtLabel *pLabelRightLine = new CtLabel( CtRect( CtWindowHome::RectColor, 1, CtWindowHome::RectColor ) ); // 18
    CtVLayout *pLayoutRightLine = new CtVLayout();
    pLayoutRightLine->addStretch( 15 );
    pLayoutRightLine->addWidget( pLabelRightLine, 18 );
    pLayoutRightLine->addStretch( 12 );

    CtFontSet fSet = CtFontSet( FontTypeNormal_alignCenter, CtColor::White );

    m_pFpsName = new CtStackLabel();
    CtLabel* pLabel = NULL;
    pLabel = new CtLabel();
    m_pFpsName->addLabel( pLabel);
    pLabel = new CtLabel( STR_ID_NO_10789, fSet );
    m_pFpsName->addLabel( pLabel);

    updateBtnFpsNameLabel();
    
    CtLabel *pLabelColor = new CtLabel( STR_ID_NO_10668, fSet );  // 「COLOR」
    CtLabel *pLabelShutter = new CtLabel( STR_ID_NO_10790, fSet );   // 「SHUTTER」

    CtHLayout *pLayout = new CtHLayout(); //  45
    pLayout->addWidget( m_pFpsName, 319 );
    pLayout->addWidget( pLayoutLeftLine, 4 );
    pLayout->addWidget( pLabelColor, 314 );
    pLayout->addWidget( pLayoutRightLine, 4 );
    pLayout->addWidget( pLabelShutter, 319 );

    return pLayout;
    
}

CtLayout* CtWindowHome::create3BtnNameLowerLayout(){
    CtLabel *pLabelLeftLine = new CtLabel(CtRect(CtWindowHome:: RectColor,1,CtWindowHome:: RectColor)); // 18
    
    CtVLayout *pLayoutLeftLine = new CtVLayout();
    pLayoutLeftLine->addStretch( 12 );
    pLayoutLeftLine->addWidget( pLabelLeftLine, 18 );
    pLayoutLeftLine->addStretch( 15 );

    CtLabel *pLabelRightLine = new CtLabel(CtRect(CtWindowHome:: RectColor,1,CtWindowHome:: RectColor)); // 18
    
    CtVLayout *pLayoutRightLine = new CtVLayout();
    pLayoutRightLine->addStretch( 12 );
    pLayoutRightLine->addWidget( pLabelRightLine, 18 );
    pLayoutRightLine->addStretch( 15 );


    CtFontSet fSet = CtFontSet( FontTypeNormal_alignCenter, CtColor::White );

    CtLabel *pLabelEi = new CtLabel( STR_ID_NO_10791, fSet );      // "EI"
    CtLabel *pLabelAudio = new CtLabel( STR_ID_NO_10669, fSet );    // "AUDIO"
    CtLabel *pLabelWb = new CtLabel( STR_ID_NO_10673, fSet );     // "WB"

    CtHLayout *pLayout = new CtHLayout(); //  45
    pLayout->addWidget( pLabelEi, 319 );
    pLayout->addWidget( pLayoutLeftLine, 4 );
    pLayout->addWidget( pLabelAudio, 314 );
    pLayout->addWidget( pLayoutRightLine, 4 );
    pLayout->addWidget( pLabelWb, 319 );

    return pLayout;
}

CtLayout* CtWindowHome::create3BtnLayout(LayoutIdentifyId id){
    CtButton* pButton_Left = NULL;
    CtButton* pButton_Center = NULL;
    CtButton* pButton_Right = NULL;
    CtHLayout* pLayout = new CtHLayout(); // 110
    switch(id){
    case LayoutIdentifyUpper:
        pButton_Left = createBtnFps();
        pButton_Center = createBtnColor();
        pButton_Right = createBtnShutter();
        break;
    case LayoutIdentifyLower:
        pButton_Left = createBtnEi();
        pButton_Center = createBtnAudio();
        pButton_Right = createBtnWb();
        break;
    default:
        return pLayout;
    }

    pLayout->addStretch( 6 );
    pLayout->addWidget( pButton_Left, 312 );
    pLayout->addStretch( 6 );
    pLayout->addWidget( pButton_Center, 312 );
    pLayout->addStretch( 6 );
    pLayout->addWidget( pButton_Right, 312 );
    pLayout->addStretch( 6 );

    return pLayout;
}

void CtWindowHome::createVFRONLayout(){
    m_pVRFOn = new CtHLayout(); // 312
    
    CtLabel *pLabelVFR = new CtLabel( IC_VFR ); // 32  「VFR」のマークを左上に表示する
   
    CtVLayout *pLayoutVFRMark = new CtVLayout(); // 68
    pLayoutVFRMark->addStretch( 20 );
    pLayoutVFRMark->addWidget( pLabelVFR, 32 );
    pLayoutVFRMark->addStretch( 58 );
    
    CtHLayout *pLayoutVFR = new CtHLayout(); // 80
    pLayoutVFR->addStretch( 4 );
    pLayoutVFR->addWidget( pLayoutVFRMark, 68 );
    pLayoutVFR->addStretch( 8 );
    
    m_pFpsDecLayout = createFpsNumericLayout();
    m_pFpsIntLayout = createFpsOnIntLayout();
        
    CtLayout* pVFROnNumLayout = new CtLayout();
    pVFROnNumLayout->addWidget( m_pFpsIntLayout );
    pVFROnNumLayout->addWidget( m_pFpsDecLayout );
    
//    updateVFROnLayout();
   
    m_pVRFOn->addWidget( pLayoutVFR, 80 );
    m_pVRFOn->addWidget( pVFROnNumLayout, 224 );
    m_pVRFOn->addStretch( 8 );
    return;
}

void CtWindowHome::createVFROffLayout(){
    m_pVRFOff = new CtHLayout(); // 312
    
 //   updateVFROffLabel();
    
    CtLayout* pLayoutFpsNumeric = createFpsNumericLayout();
    
    m_pVRFOff->addStretch( 80 );
    m_pVRFOff->addWidget( pLayoutFpsNumeric, 224 );
    m_pVRFOff->addStretch( 8 );

    return;
}

CtButton* CtWindowHome::createBtnFps(){
    CtFontSet fSet_Left = CtFontSet( FontTypeNormal, CtColor::black );
    fSet_Left.setSize(60);

    m_pLabelIntPart = new CtLabel();
    m_pLabelDecPart = new CtLabel();
    m_pLabelInterlace = new CtLabel("i",fSet_Left);
    m_pLabelFpsOnInt = new CtLabel();
    
    createVFRONLayout();
    createVFROffLayout();
    
    CtLayout* pLayout = new CtLayout(); // 312
    pLayout->addWidget( m_pVRFOn );
    pLayout->addWidget( m_pVRFOff );
    
    updateBtnFps();

    m_pButtonFps = new CtButton( CtSize(312,110), pLayout, CtButton::None );
#if 1 /*@salvage*/
    m_pButtonFps->setImage( IC_TOP_LEFT );
#endif
	//m	m_pButtonFps->setFocusable( false );
	//m_pButtonFps->setOwnColor( false );
	//m    m_pButtonFps->setColor( CtWindowHome::ImagColor );
    return m_pButtonFps;
}

void CtWindowHome::createMainVlogLayout(){
    CtFontSet fSet = CtFontSet( FontTypeNormal, CtColor::black );

    CtLabel *pLabel_Main = new CtLabel( STR_ID_NO_10846, fSet ); // 136 "MAIN"
    CtLabel *pLabel_Main_Value = new CtLabel( STR_ID_NO_10062, fSet ); // 136   "V-log"
    CtHLayout *pLayoutMain = new CtHLayout(); // 36
    pLayoutMain->addStretch( 75 );
    pLayoutMain->addWidget( pLabel_Main, 75 );
    pLayoutMain->addStretch( 12 );
    pLayoutMain->addWidget( pLabel_Main_Value, 75 );
    pLayoutMain->addStretch( 75 );

    CtLabel *pLabel_Sub = new CtLabel( STR_ID_NO_10847, fSet ); // "SUB"
    m_pLabelSubColor = getLabelColor( LayoutColorIdentifyColorBtn );
    CtHLayout *pLayoutSub = new CtHLayout();
    pLayoutSub->addStretch( 75 );
    pLayoutSub->addWidget( pLabel_Sub, 75 );
    pLayoutSub->addStretch( 12 );
    pLayoutSub->addWidget( m_pLabelSubColor, 75 );
    pLayoutSub->addStretch( 75 );

    m_pMainVLog = new CtVLayout(); // 312
    // COLORステータス枠内の上段
    m_pMainVLog->addWidget( pLayoutMain, 55 );
    // COLORステータス枠内の下段
    m_pMainVLog->addWidget( pLayoutSub, 55 );
    return;
}

void CtWindowHome::createSubOffLayout(){
    CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter_Middle, CtColor::black );
    // MAIN COLOR設定値がV-Log、かつ[SUB REC]がOFFの場合 
    // 上段下段を分けずに中央に大きいフォント（FPSなどの数値と同じ）で"V-Log"文字列を表示（センタリングで表示）
    CtLabel *pLabel_Vlog = new CtLabel( STR_ID_NO_10062, fSet_Center ); // "V-Log"
    m_pSubOff = new CtLayout(); // 312
    m_pSubOff->addWidget( pLabel_Vlog );
    return;
}

void CtWindowHome::createMainSceneLayout(){
    CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter_Middle, CtColor::black );
    // MAIN COLOR設定値がV-Log以外（SCENE*）の場合
    // - COLORステータス枠内の上段
    // MAIN COLOR設定値
    // （センタリングで表示）
    //  - COLORステータス枠内の下段
    //  SCENEのNAME（最大8文字）        
    m_pLabelMainColor = getLabelColor( LayoutColorIdentifyColorBtn );
 //   updateSceneFileName();
    m_pLabelSceneName = new CtLabel( m_SceneFileName, fSet_Center );
    m_pMainScene = new CtVLayout(); // 11
    m_pMainScene->addWidget( m_pLabelMainColor, 1 );
    m_pMainScene->addWidget( m_pLabelSceneName, 1 );
    return;

}

CtButton* CtWindowHome::createBtnColor(){
    createMainVlogLayout();
    createSubOffLayout();
    createMainSceneLayout();
    
    CtLayout *pLayout = new CtLayout();
    pLayout->addWidget( m_pMainVLog );
    pLayout->addWidget( m_pSubOff );
    pLayout->addWidget( m_pMainScene );

    updateBtnColor();
    
    m_pButtonColor = new CtButton( CtSize(312,110), pLayout, CtButton::None);
#if 1 /*@salvage*/
    m_pButtonColor->setImage( IC_TOP_CENTER );
#endif
	//m_pButtonColor->setOwnColor(false);
	//m	m_pButtonColor->setFocusable(false);
	//m    m_pButtonColor->setColor( CtWindowHome::ImagColor );
    return m_pButtonColor;
}

void CtWindowHome::createShutterOff(){
    CtFontSet fSet = CtFontSet( FontTypeNormal_alignCenter, CtColor::black );
    CtLabel *pLabel_Shutter = new CtLabel( STR_ID_NO_10792, fSet ); // "OFF"
    m_pShutterOff = new CtLayout();
    m_pShutterOff->addWidget( pLabel_Shutter );
    return;
}

void CtWindowHome::createShutterSec(){

	CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter, CtColor::black );
    CtLabel *pLabel = new CtLabel( IC_1 ); // 62
    CtVLayout *pLayoutIC1 = new CtVLayout(); // 296
    pLayoutIC1->addStretch( 52 );
    pLayoutIC1->addWidget( pLabel, 48 );
    pLayoutIC1->addStretch( 10 );
    
    m_pLabelSec = new CtLabel("",fSet_Center);
    CtLayout* pLayoutNum = createShutterNumericLayout( m_pLabelSec, IC_SEC );

    m_pShutterSec = new CtHLayout();
    m_pShutterSec->addStretch( 25 );
    m_pShutterSec->addWidget( pLayoutIC1, 62 );
    m_pShutterSec->addWidget( pLayoutNum, 215 );
    m_pShutterSec->addStretch( 10 );    
    return;
}

void CtWindowHome::createShutterDeg(){
	CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter, CtColor::black );
    m_pLabelDeg = new CtLabel("",fSet_Center);
    CtLayout* pLayoutNum = createShutterNumericLayout( m_pLabelDeg, IC_DEG );
    m_pShutterDeg = new CtHLayout();
    m_pShutterDeg->addStretch( 87 );
    m_pShutterDeg->addWidget( pLayoutNum, 215 );
    m_pShutterDeg->addStretch( 10 );    
    return;
}

CtButton* CtWindowHome::createBtnShutter(){
    createShutterOff();
    createShutterSec();
    createShutterDeg();

    CtLayout* pLayout =new CtLayout();
    pLayout->addWidget( m_pShutterOff );
    pLayout->addWidget( m_pShutterSec );
    pLayout->addWidget( m_pShutterDeg );
    
    updateBtnShutter();
    
    m_pButtonShutter = new CtButton( CtSize(312,110), pLayout, CtButton::None);
#if 1 /*@salvage*/ // ボタン背景設定機能待ち
    m_pButtonShutter->setImage( IC_TOP_RIGHT );
#endif
	//m_pButtonShutter->setOwnColor(false);
	//m	m_pButtonShutter->setFocusable(false);
	//m    m_pButtonShutter->setColor( CtWindowHome::ImagColor );
    return m_pButtonShutter;
}

void CtWindowHome::createEiGainLayout(){
    m_pLabelGainSel = new CtLabel();

    CtVLayout *pLayoutGainSel = new CtVLayout(); // 68
    pLayoutGainSel->addStretch( 20 );
    pLayoutGainSel->addWidget( m_pLabelGainSel, 32 );
    pLayoutGainSel->addStretch( 58 );

    m_pLabelGain = getLabelGain();   // get Gain select value     
    
    CtLabel *pLabel = new CtLabel( IC_DB ); // 62
    
    CtVLayout *pLayoutImag = new CtVLayout(); // 62
    pLayoutImag->addStretch( 54 );
    pLayoutImag->addWidget( pLabel, 48 );
    pLayoutImag->addStretch( 8 );
    
    CtHLayout *pLayoutNum = new CtHLayout(); // 8
    pLayoutNum->addWidget( m_pLabelGain, 143 );
    pLayoutNum->addWidget( pLayoutImag, 62 );

    m_pEiGain = new CtHLayout();
    m_pEiGain->addStretch( 4 );
    m_pEiGain->addWidget( pLayoutGainSel, 88 );
    m_pEiGain->addStretch( 8 );
    m_pEiGain->addWidget( pLayoutNum, 205 );
    m_pEiGain->addStretch( 7 );
    return;
}

void CtWindowHome::createEiIsoLayout(){

    m_pLabelIsoSel = new CtStackLabel();
    CtLabel* pLabelIsoSel = NULL;
    pLabelIsoSel = new CtLabel( IC_NATIVE );
    m_pLabelIsoSel->addLabel( pLabelIsoSel );  // NATIVE
    pLabelIsoSel = new CtLabel( IC_800B );
    m_pLabelIsoSel->addLabel( pLabelIsoSel );  // 800BASE
    pLabelIsoSel = new CtLabel( IC_3200B );
    m_pLabelIsoSel->addLabel( pLabelIsoSel );   // 3200BASE
    pLabelIsoSel = new CtLabel( IC_2500B );
    m_pLabelIsoSel->addLabel( pLabelIsoSel );   // 2500BASE

    CtLabel* pLabel_ISO = new CtLabel( IC_ISO ); // ISO  68
    CtVLayout *pLayoutISO = new CtVLayout(); // 8
    pLayoutISO->addStretch( 20 );
    pLayoutISO->addWidget( m_pLabelIsoSel, 32 );
    pLayoutISO->addStretch( 9 );
    pLayoutISO->addWidget( pLabel_ISO, 32 );
    pLayoutISO->addStretch( 17 );
   
    m_pISONative = getISONative();
    m_pISO800Base = getISO800Base();
    m_pISO2500Base = getISO2500Base();

    CtLayout *pLayoutIsoSet = new CtLayout(); // 8
    pLayoutIsoSet->addWidget( m_pISONative );
    pLayoutIsoSet->addWidget( m_pISO800Base );
    pLayoutIsoSet->addWidget( m_pISO2500Base );
    
    CtHLayout *pLayoutNum = new CtHLayout(); // 8
    pLayoutNum->addWidget( pLayoutIsoSet, 143 );
    pLayoutNum->addStretch( 62 );

    m_pEiIso = new CtHLayout();
    m_pEiIso->addStretch( 4 );
    m_pEiIso->addWidget( pLayoutISO, 68 );
    m_pEiIso->addStretch( 8 );
    m_pEiIso->addWidget( pLayoutNum, 224 );
    m_pEiIso->addStretch( 8 );
    return;
}

CtButton* CtWindowHome::createBtnEi(){
    createEiGainLayout();
    createEiIsoLayout();
    
    CtLayout *pLayout = new CtLayout(); // 312
    pLayout->addWidget( m_pEiIso );
    pLayout->addWidget( m_pEiGain);

    updateBtnEi();
    
    m_pButtonEi = new CtButton( CtSize(312,110), pLayout, CtButton::None);
#if 1 /*@salvage*/
    m_pButtonEi->setImage( IC_BOTTOM_LEFT );
#endif
	//m_pButtonEi->setOwnColor(false);
	//m	m_pButtonEi->setFocusable(false);
	//m    m_pButtonEi->setColor( CtWindowHome::ImagColor );
    return m_pButtonEi;
}

CtButton* CtWindowHome::createBtnAudio(){
    CtLabel *pLabel_CH1 = new CtLabel( IC_CH1_BTN );
    m_pLabelCH1 = new CtLabel( CtSize( 213, 50 ) );
    updateBtnAudioCH1();
    
    CtHLayout *pLayoutCH1 = new CtHLayout();  // 34
    pLayoutCH1->addStretch( 21 );
    pLayoutCH1->addWidget( pLabel_CH1, 72 );
    pLayoutCH1->addStretch( 6 );
    pLayoutCH1->addWidget( m_pLabelCH1, 213 );
    
    CtLabel *pLabel_CH2 = new CtLabel( IC_CH2_BTN );  // 72
    m_pLabelCH2 = new CtLabel( CtSize( 213, 50 ) );
    updateBtnAudioCH2();
    
    CtHLayout *pLayoutCH2 = new CtHLayout();  // 34
    pLayoutCH2->addStretch( 21 );
    pLayoutCH2->addWidget( pLabel_CH2, 72 );
    pLayoutCH2->addStretch( 6 );
    pLayoutCH2->addWidget( m_pLabelCH2, 213 );

    CtVLayout *pLayout = new CtVLayout();  
    pLayout->addStretch( 14 );
    pLayout->addWidget( pLayoutCH1, 34 );
    pLayout->addStretch( 16 );
    pLayout->addWidget( pLayoutCH2, 34 );
    pLayout->addStretch( 12 );
    
    m_pButtonAudio = new CtButton( CtSize(312,110), pLayout, CtButton::None);
#if 1 /*@salvage*/
    m_pButtonAudio->setImage( IC_BOTTOM_CENTER );
#endif
	//m_pButtonAudio->setOwnColor(false);
	//m	m_pButtonAudio->setFocusable(false);
	//m    m_pButtonAudio->setColor( CtWindowHome::ImagColor );
    return m_pButtonAudio;
}

void CtWindowHome::createWbNumLayout(){
    m_pLabelWbNum = new CtLabel();
    
    CtLabel *pLabel = new CtLabel( IC_K ); // 62
    CtVLayout *pLayoutImag = new CtVLayout(); // 62
    pLayoutImag->addStretch( 51 );
    pLayoutImag->addWidget( pLabel, 48 );
    pLayoutImag->addStretch( 11 );
    
    CtHLayout *pLayoutNum = new CtHLayout(); // 8
    pLayoutNum->addWidget( m_pLabelWbNum, 234 );
    pLayoutNum->addWidget( pLayoutImag, 62 );

    m_pWbNum = new CtHLayout();
    m_pWbNum->addStretch( 8 );
    m_pWbNum->addWidget( pLayoutNum, 296);
    m_pWbNum->addStretch( 8 );

    return;
}

void CtWindowHome::createAtwLayout(){
    CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter_Middle, CtColor::black );
    m_pLabelWb = new CtStackLabel();
    CtLabel* pLabel = NULL;

    pLabel = new CtLabel( STR_ID_NO_10762, fSet_Center);    // "ATW"
    m_pLabelWb->addLabel( pLabel );
    pLabel = new CtLabel( STR_ID_NO_10763, fSet_Center);    // "ATW LOCK"
    m_pLabelWb->addLabel( pLabel );
    m_pATW = new CtLayout();
    m_pATW->addWidget( m_pLabelWb ); 
    return;
}

CtButton* CtWindowHome::createBtnWb(){
    CtLayout* pLayout = new CtLayout();
    createWbNumLayout();
    createAtwLayout();
    pLayout->addWidget( m_pWbNum );
    pLayout->addWidget( m_pATW );

    updateBtnWb();
    m_pButtonWb = new CtButton( CtSize(312,110), pLayout, CtButton::None);
#if 1 /*@salvage*/
    m_pButtonWb->setImage( IC_BOTTOM_RIGHT );
#endif
	//m	m_pButtonWb->setFocusable(false);
	//m_pButtonWb->setOwnColor(false);
	//m    m_pButtonWb->setColor( CtWindowHome::ImagColor );
    return m_pButtonWb;
}

CtLayout* CtWindowHome::createFpsNumericLayout(){
    CtVLayout *pLayoutDecPart = new CtVLayout(); // 81
    pLayoutDecPart->addStretch( 38 ); // 50
    pLayoutDecPart->addWidget( m_pLabelDecPart, 60 ); // 32
    pLayoutDecPart->addStretch( 12 ); // 28
    
    CtVLayout *pLayoutInterlace = new CtVLayout(); // 81
    pLayoutInterlace->addStretch( 38 ); // 50
    pLayoutInterlace->addWidget( m_pLabelInterlace, 60 ); // 32
    pLayoutInterlace->addStretch( 12 ); // 28

    CtHLayout *pLayoutNum = new CtHLayout(); // 8
    pLayoutNum->addWidget( m_pLabelIntPart, 107 );
    pLayoutNum->addWidget( pLayoutDecPart, 55 );
    
    m_pDecFpsIcon = new CtLabel( IC_FPS ); // 62
    
    CtVLayout *pLayoutImag = new CtVLayout(); // 62
    pLayoutImag->addStretch( 51 );
    pLayoutImag->addWidget( m_pDecFpsIcon, 48 );
    pLayoutImag->addStretch( 11 );

	CtLayout *pLayoutUnit = new CtLayout();
	pLayoutUnit->addWidget(pLayoutImag);
	pLayoutUnit->addWidget(pLayoutInterlace);
	
    CtHLayout *pLayout = new CtHLayout(); // 8
    pLayout->addWidget( pLayoutNum, 162 );
    pLayout->addWidget( pLayoutUnit, 62 );

    return pLayout;
}

CtLayout* CtWindowHome::createFpsOnIntLayout(){
    CtLabel *pLabel = new CtLabel( IC_FPS ); // 62
    CtVLayout *pLayoutImag = new CtVLayout(); // 62
    pLayoutImag->addStretch( 51 );
    pLayoutImag->addWidget( pLabel, 48 );
    pLayoutImag->addStretch( 11 );

    CtHLayout *pLayout = new CtHLayout(); // 8
    pLayout->addWidget( m_pLabelFpsOnInt, 162 );
    pLayout->addWidget( pLayoutImag, 62 );

    return pLayout;
}

// 215
CtLayout* CtWindowHome::createShutterNumericLayout(CtLabel* pLabel, const GDI_IMAGE_ID imgID){
    CtHLayout *pLayout = new CtHLayout(); // 8

    if( NULL == pLabel ){ 
        return pLayout; 
    }
    
    CtLabel *pLabel_img = new CtLabel( imgID ); // 62
    
    CtVLayout *pLayoutImag = new CtVLayout(); // 62
    pLayoutImag->addStretch( 51 );
    pLayoutImag->addWidget( pLabel_img, 48 );
    pLayoutImag->addStretch( 11 );

    pLayout->addWidget( pLabel, 153 );
    pLayout->addWidget( pLayoutImag, 62 );

    return pLayout;
}

CtLayout* CtWindowHome::createCenterLeftLayout(){
    CtDebugPrint(CtDbg, " ******CtWindowHome::createCenterLeftLayout******\n");
    m_pLabelSysSta = new CtLabel();
    m_pLabelMainCodec = getLabelMainCodec();
    CtVLayout* pLayoutVSsMc = new CtVLayout(); // 306
    pLayoutVSsMc->addWidget( m_pLabelSysSta, 1 );      //  SYSTEMステータスを表示する。
    pLayoutVSsMc->addWidget( m_pLabelMainCodec, 1 );   // MAIN CODEC設定値を表示する。
    CtLabel* pLabel_Line = new CtLabel( CtRect( CtWindowHome::LineColor, 0, CtWindowHome::LineColor )); // 2
    CtHLayout* pLayoutHSsMc = new CtHLayout();  // 116
    pLayoutHSsMc->addStretch( 16 );
    pLayoutHSsMc->addWidget( pLayoutVSsMc, 274 );
    pLayoutHSsMc->addStretch( 15 );
    pLayoutHSsMc->addWidget( pLabel_Line, 2 );

	CtLabel *pTempLabel = new CtLabel();
	//m	pTempLabel->setColor(CtColor::Black);
    pLayoutHSsMc->addWidget(pTempLabel, 1 );

    updateSysStatusLayout();
    updateMainCodecLayout();
    
    // タイムコード
    CtLayout* pLayoutTCGWarning = createTCGOrWarningLayout();
    
    CtVLayout* pLayout = new CtVLayout();
    pLayout->addStretch( 13 );
    pLayout->addWidget( pLayoutHSsMc, 116 );
    pLayout->addWidget( pLayoutTCGWarning, 95 );
    
    return pLayout;
}

CtLayout* CtWindowHome::createCenterRightLayout(){
    CtDebugPrint(CtDbg, " ******CtWindowHome::createCenterRightLayout******\n");
    CtLayout* pLayoutSlot = createSlotLayout();  // 240
    
    CtLayout* pLayout2SlotFunc = create2SlotFuncAndRecModeLayout(); //  224
    
    CtLayout* pLayoutLanBattClip = createLanAndBatteryAndClipLayout(); // 172
    CtHLayout* pLayoutUpper = new CtHLayout();
    pLayoutUpper->addWidget( pLayoutSlot, 240 );
    pLayoutUpper->addWidget( pLayout2SlotFunc, 224 );
    pLayoutUpper->addWidget( pLayoutLanBattClip, 172 );

    CtFastContainerAudioLevel* pAudioLevel = new CtFastContainerAudioLevel_Home(); // 68
    CtVLayout* pLayoutAudioLevel = new CtVLayout(); // 298
    pLayoutAudioLevel->addStretch( 17 );
    pLayoutAudioLevel->addContainer( pAudioLevel, 68 );
    pLayoutAudioLevel->addStretch( 8 );
        
    CtLayout* pLayoutOutColor = createOutColorLayout(); // 70
    CtVLayout* pLayoutVOutColor = new CtVLayout(); // 278
    pLayoutVOutColor->addStretch( 16 );
    pLayoutVOutColor->addWidget( pLayoutOutColor, 70 );
    pLayoutVOutColor->addStretch( 7 );
    
    CtHLayout* pLayoutLower = new CtHLayout();
    pLayoutLower->addStretch( 7 );
    pLayoutLower->addWidget( pLayoutAudioLevel, 298 );
    pLayoutLower->addStretch( 41 );
    pLayoutLower->addWidget( pLayoutVOutColor, 278 );
    pLayoutLower->addStretch( 12 );
    
    CtVLayout* pLayout = new CtVLayout();
    pLayout->addWidget( pLayoutUpper, 131 );
    pLayout->addWidget( pLayoutLower, 93 );

    return pLayout;
}

CtLayout* CtWindowHome::createTCGOrWarningLayout(){

    CtHLayout* pLayoutTcgWarning = new CtHLayout();

	CtFastDrawContainerTcgWarning* pTcgWarning = new CtFastDrawContainerTcgWarning();
    
    pLayoutTcgWarning->addStretch( 6 );
	pLayoutTcgWarning->addContainer( pTcgWarning, 64 );

    CtFastContainerTimeCode* pTimeCode = new CtFastContainerTimeCode( true);
    CtVLayout* pLayoutTimeCode = new CtVLayout();
    pLayoutTimeCode->addStretch( 14 );
	pLayoutTimeCode->addContainer( pTimeCode, 72 );
    pLayoutTimeCode->addStretch( 9 );

    CtHLayout* pLayout = new CtHLayout();
    pLayout->addWidget( pLayoutTcgWarning, 70 );
    pLayout->addStretch( 9 );
    pLayout->addWidget( pLayoutTimeCode, 219 );
    pLayout->addStretch( 8 );
    
	return pLayout;
}

CtLayout* CtWindowHome::createSlotLayout(){
    CtContainerCard1* pSlot1 = new CtContainerCard1( CT_COMMON_TYPE_HOME );
    CtLabel* pLabel_Line = new CtLabel( CtRect( CtWindowHome::LineColor, 0, CtWindowHome::LineColor ) ); // 2
    CtContainerCard2* pSlot2 = new CtContainerCard2( CT_COMMON_TYPE_HOME );
    CtVLayout* pLayout = new CtVLayout();
    pLayout->addStretch( 13 );
    pLayout->addContainer( pSlot1, 50 );
    pLayout->addStretch( 7 );
    pLayout->addWidget( pLabel_Line, 2 );
    pLayout->addStretch( 7 );
    pLayout->addContainer( pSlot2, 50 );
    pLayout->addStretch( 2 );
    return pLayout;
}

void CtWindowHome::createOutColor3XLayout(){
    
    CtLabel* pLabel_OutColor = new CtLabel( IC_OUTPUTX3 );    //  SDI/HDMI/LCD OUT Color
    
    m_pLabelSdiOutColor = getLabelColor( LayoutColordentifyOutColor );
    m_pLabelHdmiOutColor = getLabelColor( LayoutColordentifyOutColor );
    m_pLabelLcdOutColor = getLabelColor( LayoutColordentifyOutColor );
    
    CtLayout* pLayoutLine1 = new CtLayout(); // 1
    CtLayout* pLayoutLine2 = new CtLayout(); // 1
    CtHLayout* pLayoutOutColor3X = new CtHLayout(); // 30
    pLayoutOutColor3X->addWidget( m_pLabelSdiOutColor, 92 );
    pLayoutOutColor3X->addWidget( pLayoutLine1, 1 );
    pLayoutOutColor3X->addWidget( m_pLabelHdmiOutColor, 92 );
    pLayoutOutColor3X->addWidget( pLayoutLine2, 1 );
    pLayoutOutColor3X->addWidget( m_pLabelLcdOutColor, 92 );

    CtVLayout* pLayout = new CtVLayout(); // 70
    pLayout->addStretch( 22 );
    pLayout->addWidget( pLayoutOutColor3X, 45 );
    pLayout->addStretch( 3 );

    m_pOutColorX3 = new CtLayout();
    m_pOutColorX3->addWidget( pLabel_OutColor );
    m_pOutColorX3->addWidget( pLayout );

    return;
}

void CtWindowHome::createOutColor1XLayout(){    
    
    CtLabel* pLabel_OutColor = new CtLabel( IC_OUTPUTX1 );    //  SDI/HDMI/LCD OUT Color

    m_pLabelMainOutColor = getLabelColor( LayoutColordentifyOutColor );
    CtVLayout* pLayout = new CtVLayout(); // 70
    pLayout->addStretch( 22 );
    pLayout->addWidget( m_pLabelMainOutColor, 45 );
    pLayout->addStretch( 3 );

    m_pOutColorX1 = new CtLayout();
    m_pOutColorX1->addWidget( pLabel_OutColor );
    m_pOutColorX1->addWidget( pLayout );

    return;
}

CtLayout* CtWindowHome::createOutColorLayout(){
    createOutColor3XLayout();
    createOutColor1XLayout();
        
    CtLayout* pLayout = new CtLayout();
    pLayout->addWidget( m_pOutColorX1 );
    pLayout->addWidget( m_pOutColorX3 );

    updateOutColorLayout();
    
    return pLayout;
}

CtLayout* CtWindowHome::create2SlotFuncAndRecModeLayout(){
    m_pLowerLeft = create2SlotFuncOrSubRecLayoutLowerLeft();
    m_pLowerRight = createRecModLayoutLowerRight();
    m_pUpperRight = createRecModLayoutUpperRight();
    m_pLowerLeftAndCenter = createSubRecAndRecModLayoutLowerLeftAndCenter();
    m_pCenter = create2SlotFuncLayoutCenter();
    m_pBothCenter = create2SlotFuncAndRecModLayoutCenter();
    m_p2SlotFuncNull = new CtLayout();
    
    CtLayout* pLayout = new CtLayout();
    pLayout->addWidget( m_pLowerLeft );
    pLayout->addWidget( m_pLowerRight );
    pLayout->addWidget( m_pUpperRight );
    pLayout->addWidget( m_pLowerLeftAndCenter );
    pLayout->addWidget( m_pCenter );
    pLayout->addWidget( m_pBothCenter );
    pLayout->addWidget( m_p2SlotFuncNull );

    update2SlotFuncAndRecModeLayout();
    
    return pLayout;
}


CtLayout* CtWindowHome::create2SlotFuncOrSubRecLayoutLowerLeft(){
    CtLabel* pLabel_extendLine = new CtLabel( CtRect( CtWindowHome::LineColor, 0,CtWindowHome::LineColor ) );    // 2
    CtVLayout* pLayoutExtendLine = new CtVLayout();    // 12
    pLayoutExtendLine->addStretch( 70 );
    pLayoutExtendLine->addWidget( pLabel_extendLine, 2 );
    pLayoutExtendLine->addStretch( 59 );
    
    CtLabel* pLabel_Line = new CtLabel( CtRect( CtWindowHome::LineColor, 0, CtWindowHome::LineColor ) );    // 2
    m_pLabel2SlotOrSub = new CtLabel();    // 36
    
    CtVLayout* pLayout2SlotOrSub = new CtVLayout();
    pLayout2SlotOrSub->addStretch( 70 );
    pLayout2SlotOrSub->addWidget( pLabel_Line, 2 );
    pLayout2SlotOrSub->addStretch( 14 );
    pLayout2SlotOrSub->addWidget( m_pLabel2SlotOrSub, 36 );
    pLayout2SlotOrSub->addStretch( 9 );

    CtHLayout* pLayout = new CtHLayout();
    pLayout->addWidget( pLayoutExtendLine, 12 );
    pLayout->addWidget( pLayout2SlotOrSub, 100 );
    pLayout->addStretch( 112 );
    return pLayout;
}

CtLayout* CtWindowHome::createRecModLayoutLowerRight(){
    CtLabel* pLabel_Line = new CtLabel( CtRect( CtWindowHome::LineColor, 0, CtWindowHome::LineColor ) );    // 2

	m_pLabelLowerRight = new CtLabel();
    CtHLayout* pLayoutLowerRight = new CtHLayout();  // 36
    pLayoutLowerRight->addStretch( 124 );
    pLayoutLowerRight->addWidget( m_pLabelLowerRight, 100 );

    CtVLayout* pLayout = new CtVLayout();
    pLayout->addStretch( 70 );
    pLayout->addWidget( pLabel_Line, 2 );
    pLayout->addStretch( 14 );
    pLayout->addWidget( pLayoutLowerRight, 36 );
    pLayout->addStretch( 9 );
    return pLayout;
}

CtLayout* CtWindowHome::createRecModLayoutUpperRight(){

    m_pLabelUpperRight = new CtLabel();
    CtHLayout* pLayoutUpperRight = new CtHLayout(); // 36
    pLayoutUpperRight->addStretch( 124 );
    pLayoutUpperRight->addWidget( m_pLabelUpperRight, 100 );
    
    CtLabel* pLabel_Line = new CtLabel( CtRect( CtWindowHome::LineColor, 0, CtWindowHome::LineColor ) );    // 2

    CtVLayout* pLayout = new CtVLayout();
    pLayout->addStretch( 20 );
    pLayout->addWidget( pLayoutUpperRight, 36 );
    pLayout->addStretch( 14 );
    pLayout->addWidget( pLabel_Line, 2 );
    pLayout->addStretch( 59 );
    return pLayout;
}

CtLayout* CtWindowHome::createSubRecAndRecModLayoutLowerLeftAndCenter(){
    CtLabel* pLabel_extendLine = new CtLabel( CtRect( CtWindowHome::LineColor, 0, CtWindowHome::LineColor ) );    // 2
    CtVLayout* pLayoutExtendLine = new CtVLayout();    // 12
    pLayoutExtendLine->addStretch( 70 );
    pLayoutExtendLine->addWidget( pLabel_extendLine, 2 );
    pLayoutExtendLine->addStretch( 59 );
    
    CtLabel* pLabel_Line = new CtLabel( CtRect( CtWindowHome::LineColor, 0, CtWindowHome::LineColor ) );    // 2

    m_pLabelSubRec = new CtLabel();
    CtVLayout* pLayoutSubRec = new CtVLayout();
    pLayoutSubRec->addStretch( 70 );
    pLayoutSubRec->addWidget( pLabel_Line, 2 );
    pLayoutSubRec->addStretch( 14 );
    pLayoutSubRec->addWidget( m_pLabelSubRec, 36 );
    pLayoutSubRec->addStretch( 9 );

    CtLabel* pLabel_RecMod = new CtLabel( IC_INTRVL ); //  36
    CtVLayout* pLayoutRecMod = new CtVLayout();
    pLayoutRecMod->addStretch( 53 );
    pLayoutRecMod->addWidget( pLabel_RecMod, 36 );
    pLayoutRecMod->addStretch( 42 );
    
    CtHLayout* pLayout = new CtHLayout();
    pLayout->addWidget( pLayoutExtendLine, 12 );
    pLayout->addWidget( pLayoutSubRec, 100 );
    pLayout->addStretch( 12 );
    pLayout->addWidget( pLayoutRecMod, 100 );
    return pLayout;
}

CtLayout* CtWindowHome::create2SlotFuncLayoutCenter(){
    CtLabel* pLabel_imgLine1 = new CtLabel( IC_SLOT1 );
    CtLabel* pLabel_imgLine2 = new CtLabel( IC_SLOT2 );
    m_pLabelCenter2Slot = new CtLabel();
    CtVLayout* pLayout2Slot = new CtVLayout();
    pLayout2Slot->addStretch( 32 );
    pLayout2Slot->addWidget( pLabel_imgLine1, 21 );
    pLayout2Slot->addWidget( m_pLabelCenter2Slot, 36 );
    pLayout2Slot->addWidget( pLabel_imgLine2, 21 );
    pLayout2Slot->addStretch( 21 );

    CtHLayout* pLayout = new CtHLayout();
    pLayout->addStretch( 12 );
    pLayout->addWidget( pLayout2Slot, 100 );
    pLayout->addStretch( 112 );
    return pLayout;
}

CtLayout* CtWindowHome::create2SlotFuncAndRecModLayoutCenter(){
    CtLabel* pLabel_imgLine1 = new CtLabel( IC_SLOT1 );
    CtLabel* pLabel_imgLine2 = new CtLabel( IC_SLOT2 );
    m_pLabelBothCenter2Slot = new CtLabel();
    CtVLayout* pLayout2Slot = new CtVLayout();
    pLayout2Slot->addStretch( 32 );
    pLayout2Slot->addWidget( pLabel_imgLine1, 21 );
    pLayout2Slot->addWidget( m_pLabelBothCenter2Slot, 36 );
    pLayout2Slot->addWidget( pLabel_imgLine2, 21 );
    pLayout2Slot->addStretch( 21 );

    m_pLabelBothCenterRec = new CtLabel();
    CtVLayout* pLayoutRec = new CtVLayout();
    pLayoutRec->addStretch( 53 );
    pLayoutRec->addWidget( m_pLabelBothCenterRec, 36 );
    pLayoutRec->addStretch( 42 );
    
    CtHLayout* pLayout = new CtHLayout();
    pLayout->addStretch( 12 );
    pLayout->addWidget( pLayout2Slot, 100 );
    pLayout->addStretch( 12 );
    pLayout->addWidget( pLayoutRec, 100 );
    return pLayout;
}

CtLayout* CtWindowHome::createLanAndBatteryAndClipLayout(){
    
    CtFontSet fSet_Left = CtFontSet( FontTypeNormal, CtColor::White );

    CtContainerWifi* pWifi = new CtContainerWifi(); // 無線LANステータス
    
    CtContainerBattery* pBatt = new CtContainerBattery();   // バッテリー残量表示
    CtVLayout* pLayoutBatt = new CtVLayout();   // 57

    pLayoutBatt->addStretch( 5 );
    pLayoutBatt->addContainer( pBatt, 57 );
    pLayoutBatt->addStretch( 3 );

    CtHLayout* pLayoutWifiBatt = new CtHLayout();   // 36
    pLayoutWifiBatt->addStretch( 35 );
    pLayoutWifiBatt->addContainer( pWifi, 44 );
    pLayoutWifiBatt->addStretch( 19 );
    pLayoutWifiBatt->addWidget( pLayoutBatt, 57 );
    pLayoutWifiBatt->addStretch( 17 );

    CtLayout* pLayoutClip = createClipLayout();    // CLIP NAME

    CtVLayout* pLayout = new CtVLayout();
    pLayout->addStretch( 13 );
    pLayout->addWidget( pLayoutWifiBatt, 36 );
    pLayout->addStretch( 16 );
    pLayout->addWidget( pLayoutClip, 66 );

    return pLayout;
}

CtLayout* CtWindowHome::createClipLayout(){
    m_pClipNull = new CtHLayout();   // 66
    
    CtLabel* pLabel_ReelImg = new CtLabel( IC_REEL ); //  32
    m_pClipNo = new CtLabel( CtSize( 80, 45 ) );
    CtHLayout* pLayoutClipNo = new CtHLayout();   // 30
    pLayoutClipNo->addWidget( pLabel_ReelImg, 32 );
    pLayoutClipNo->addWidget( m_pClipNo, 80 );
    pLayoutClipNo->addStretch( 19 );
    
    CtLabel* pLabel_ClipImg = new CtLabel( IC_CUT ); //  32
    m_pClipName = new CtLabel( CtSize( 80, 45 ) );    // C000～C999
    CtHLayout* pLayoutClipName = new CtHLayout();   // 30
    pLayoutClipName->addWidget( pLabel_ClipImg, 32 );
    pLayoutClipName->addWidget( m_pClipName, 80 );
    pLayoutClipName->addStretch( 19 );

    CtVLayout* pLayoutClip = new CtVLayout();   // 131
    pLayoutClip->addWidget( pLayoutClipNo, 30 );
    pLayoutClip->addStretch( 6 );
    pLayoutClip->addWidget( pLayoutClipName, 30 );

    m_pClip = new CtHLayout();   // 66
    m_pClip->addStretch( 41 );
    m_pClip->addWidget( pLayoutClip, 131 ); 

    CtLayout* pLayout = new CtLayout();
    pLayout->addWidget( m_pClipNull );
    pLayout->addWidget( m_pClip );

    updateClipLayout();
    
    return pLayout;
}

void CtWindowHome::updateClipNo(){
   CtFontSet fSet_Left = CtFontSet( FontTypeNormal, CtColor::White );
   char ClipFileName[AplParamHomeClipFileName_Size+10] = {0};
   char str[AplParamHomeClipFileName_Size+10] = {0};
   APL_PARAM_GET_DATA_AREA( AplParamHomeClipFileName, (unsigned char*)ClipFileName, AplParamHomeClipFileName_Size );
   if( ClipFileName[4] == 'C' && ClipFileName[5] == '0' &&  ClipFileName[6] == '0' && ClipFileName[7] == '0' ){
       sprintf( str, "");
   } else {
       sprintf( str, "%s", ClipFileName );
   }
   str[4] = '\0';		/* A000C000の前半 */
   m_pClipNo->setText( str );
   m_pClipNo->setFontSet( fSet_Left );
   return;
}

void CtWindowHome::updateClipName(){
    CtFontSet fSet_Left = CtFontSet( FontTypeNormal, CtColor::White );
    char ClipFileName[AplParamHomeClipFileName_Size+10];
    memset( ClipFileName, 0, sizeof( ClipFileName ) );
    char str[AplParamHomeClipFileName_Size+10] = {0};
    memset( str, 0, sizeof( str ) );
    APL_PARAM_GET_DATA_AREA( AplParamHomeClipFileName, (unsigned char*)ClipFileName, AplParamHomeClipFileName_Size );
    if( (ClipFileName[4] == 'C' && ClipFileName[5] == '0' &&  ClipFileName[6] == '0' && ClipFileName[7] == '0') || (ClipFileName[4] != 'C') ){
        // 電源ONして最初のRECを行うまでは非表示
        m_pClipNull->setVisible( true );
        m_pClip->setVisible( false );
    } else {
    	str[0] = ClipFileName[4];
    	str[1] = ClipFileName[5];
    	str[2] = ClipFileName[6];
    	str[3] = ClipFileName[7];
    	str[4] = '\0';
        m_pClipName->setText( str );
        m_pClipName->setFontSet( fSet_Left );
        m_pClipNull->setVisible( false );
        m_pClip->setVisible( true );
    }
    return;
}

bool CtWindowHome::handleParamEvent(const CtEventParam& Param){
    AplParamEepromId t_Id = Param.getParamId();
    switch( t_Id ){
    case AplParamCameraNumber:  // 同じ処理とAplParamReelCountがあります
    case AplParamReelCount:
    case AplParamRecClipName:
    case AplParamHomeClipFileName:
		updateClipLayout();
        break;
    case AplParamSystemSubRec:
        if( APL_SYS_PARAM_COLOR_MAIN_VLOG == APL_PARAM_GET_DATA( AplParamColorMain ) ){
            updateBtnColor();
        }
        update2SlotFuncAndRecModeLayout();
        break;
    case AplParamRelayBackupErrStatus:  // 同じ処理とAplParamMediaSelectがあります
    case AplParamRecFunctionMode:       // 同じ処理とAplParamMediaSelectがあります
    case AplParamRelayBackup:           // 同じ処理とAplParamMediaSelectがあります
    case AplParamMediaSelect:
        update2SlotFuncAndRecModeLayout();
        break;
    case AplParamVFRValue:
        updateBtnFps();
//        updateBtnFpsNameLabel();
        if( APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA( AplParamShutterSwitch )
            && APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND == APL_PARAM_GET_DATA( AplParamShutterDispChg ) ){
            // secで動作しているとき、FPSの動作値が変化しすると、
            // ＳＨＵＴＴＥＲの動作上限値が変わり、現在の設定値が、動作範囲外になることがある。
            // このときは、SHUTTERのsecの値は範囲内の値に変更されるので、その値を表示する。
            updateBtnShutter();
        }
        break;
    case AplParamVFRMode:
        updateBtnFps();
        updateBtnFpsNameLabel();
        break;
    case AplParamSystemModeFrequency:
        updateBtnFps();
        updateSysStatusLayout();
        break;
    case AplParamColorMain:
        updateBtnColor();
        updateOutColorLayout();
        break;
    case AplParamColorSub:
        if( APL_SYS_PARAM_COLOR_MAIN_VLOG == APL_PARAM_GET_DATA( AplParamColorMain )
            && APL_PARAM_GET_DATA( AplParamSystemSubRec ) != APL_SYS_PARAM_SYSTEM_SUB_REC_OFF ){
            updateBtnColor();
        }
        break;
    case AplParamShutterSwitch:
        updateBtnShutter();
        break;
    case AplParamShutterDispChg:
        if(  APL_PARAM_GET_DATA(AplParamShutterSwitch) != APL_SYS_PARAM_SWITCH_OFF ){
            updateBtnShutter();
        }       
        break;
    case AplParamShutterSecValue:
        if( APL_PARAM_GET_DATA( AplParamShutterSwitch ) != APL_SYS_PARAM_SWITCH_OFF
            && APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND == APL_PARAM_GET_DATA(AplParamShutterDispChg) ){
            updateBtnShutter();
        }   
        break;
    case AplParamShutterDegValue:
        if( APL_PARAM_GET_DATA( AplParamShutterSwitch ) != APL_SYS_PARAM_SWITCH_OFF
            && APL_SYS_PARAM_SHUTTER_DISP_CHG_DEGREE == APL_PARAM_GET_DATA(AplParamShutterDispChg) ){
            updateBtnShutter();
        }   
        break;
    case AplParamGainIsoDispChg:
        updateBtnEi();
        break;
    case AplParamGainSwitch:    // 同じ処理とAplParamGainSelectがあります
    case AplParamGainSelect:
        if( APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN == APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
            updateBtnEi();
        }
        break;
    case AplParamISOSelect:
        if( APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO == APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
            updateBtnEi();
        }
        break;
	case AplParamNativeISO:
        if( APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO == APL_PARAM_GET_DATA( AplParamGainIsoDispChg )
            || APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY == APL_PARAM_GET_DATA( AplParamISOSelect ) ){
            updateBtnEi();
        }
        break;
    case AplParam800BaseISO:
        if( APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO == APL_PARAM_GET_DATA( AplParamGainIsoDispChg )
            || APL_SYS_PARAM_ISO_SELECT_800BASE == APL_PARAM_GET_DATA( AplParamISOSelect ) ){
            updateBtnEi();
        }
        break;
    case AplParam2500BaseISO:
        if( APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO == APL_PARAM_GET_DATA( AplParamGainIsoDispChg )
            || APL_SYS_PARAM_ISO_SELECT_2500BASE == APL_PARAM_GET_DATA( AplParamISOSelect ) ){
            updateBtnEi();
        }
        break;
    case AplParamInSelectCH1:
        updateBtnAudioCH1();
        break;
    case AplParamInSelectCH2:
        updateBtnAudioCH2();
        break;
    case AplParamSelInput1:
        if( APL_SYS_PARAM_CH_IN_SELECT_INPUT1 == APL_PARAM_GET_DATA(AplParamInSelectCH1) ){
            updateBtnAudioCH1();
        }
        if( APL_SYS_PARAM_CH_IN_SELECT_INPUT1 == APL_PARAM_GET_DATA( AplParamInSelectCH2 ) ){
            updateBtnAudioCH2();
        }
        break;
    case AplParamSelInput2:
        if( APL_SYS_PARAM_CH_IN_SELECT_INPUT2 == APL_PARAM_GET_DATA( AplParamInSelectCH2 ) ){
            updateBtnAudioCH2();
        }
        break;
    case AplParamMicPower1:
        if( APL_SYS_PARAM_CH_IN_SELECT_INPUT1 == APL_PARAM_GET_DATA( AplParamInSelectCH1 )
            && APL_SYS_PARAM_SELECT_INPUT_MIC == APL_PARAM_GET_DATA( AplParamSelInput1 ) ){
            updateBtnAudioCH1();
        }
        if( APL_SYS_PARAM_CH_IN_SELECT_INPUT1 == APL_PARAM_GET_DATA( AplParamInSelectCH2 )
            && APL_SYS_PARAM_SELECT_INPUT_MIC == APL_PARAM_GET_DATA( AplParamSelInput1 ) ){
            updateBtnAudioCH2();
        }
        break;
    case AplParamMicPower2:
        if( APL_SYS_PARAM_CH_IN_SELECT_INPUT2 == APL_PARAM_GET_DATA( AplParamInSelectCH2 )
            && APL_SYS_PARAM_SELECT_INPUT_MIC == APL_PARAM_GET_DATA( AplParamSelInput2 ) ){
            updateBtnAudioCH2();
        }
        break;
    case AplParamAutoTrackingWhiteLock:
        if( 0 == APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) ){
            updateBtnWb();
        }
        break;
    case AplParamWhiteValueIndex:
        updateBtnWb();
        break;
    case AplParamWhiteValueTemp:
        if( APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) != 0 ){
            updateBtnWb();
        }
        break;
    case AplParamColorSdiOut:   // 同じ処理とAplParamColorLcdOutがあります
    case AplParamColorHdmiOut:  // 同じ処理とAplParamColorLcdOutがあります
    case AplParamColorLcdOut:
        if( APL_SYS_PARAM_COLOR_MAIN_VLOG == APL_PARAM_GET_DATA( AplParamColorMain )){
            updateOutColorLayout();
        }
        break;
    case AplParamSystemSdiRaw:
        update2SlotFuncAndRecModeLayout();
        updateSysStatusLayout();
        updateMainCodecLayout();
        updateClipLayout();
        break;
    case AplParamSystemSensorMode:  // 同じ処理とAplParamSystemMainPixelがあります
    case AplParamSystemMainPixel:
        if( APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF == APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
            updateSysStatusLayout();
        }
        break;
    case AplParamSystemMainCodec:
        if( APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF == APL_PARAM_GET_DATA(AplParamSystemSdiRaw) ){
            updateMainCodecLayout();
        }
        updateClipLayout();
        break;
    default:
        break;
    }

    return true;    
}


bool CtWindowHome::handleButtonEvent(const CtEventButton& Button){
    bool Flag = true;

	/* Releaseでのみ処理 */
	if( Button.getPressType() != CtEventButton::Release ){
		return false;
	}

    if( Button.getWidget() == m_pButtonFps ){
		// 20171117 [K460][是正]HOME画面改善により、FPS_TOP画面へ遷移に変更
		// タッチまたはDIAL-SETとFPS画面へ遷移する。
        // HOME画面の番号1（FPS）でVFRがOFFのときはFPS画面へ遷移しない
		if( AplParamState_VisibleValid == APL_PARAM()->getParamState( AplParamVFRMode )->mState){
            if( m_pWin != NULL ){
                //m_pWin->requestWindow( WindowID_Menu_FPS_VALUE, OpenPopup, NULL );
				m_pWin->requestWindow( Window_Home_Fps_Top, OpenPopup, NULL );
            }
        }
		if( m_pWin != NULL ){
			//m_pWin->requestWindow( Window_Home_Fps_Top, OpenPopup, NULL );
        }
    }else if( Button.getWidget() == m_pButtonColor ){
        //  タッチまたはDIAL-SETするとCOLOR-TOP画面へ遷移する
        if( m_pWin != NULL ){
            m_pWin->requestWindow( Window_Home_ColorTop, OpenPopup, NULL );
        }
    }else if( Button.getWidget() == m_pButtonShutter ){
		// 20171117 [K460][是正]HOME画面改善により、Shutter_TOP画面へ遷移に変更
		/*
		// タッチまたはDIAL-SETするとSHUTTER画面へ遷移する。
        // HOME画面の番号3（SHUTTER）でSHUTTERがOFFのときはSHUTTER画面へ遷移しない
		if( APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA( AplParamShutterSwitch ) ){
			if( APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND == APL_PARAM_GET_DATA( AplParamShutterDispChg )){
				if( m_pWin != NULL ){
					m_pWin->requestWindow( WindowID_Menu_SHUTTER_SEC_VALUE, OpenPopup, NULL );
				}
			}else if( APL_SYS_PARAM_SHUTTER_DISP_CHG_DEGREE == APL_PARAM_GET_DATA( AplParamShutterDispChg )){
				if( m_pWin != NULL ){
					m_pWin->requestWindow( WindowID_Menu_SHUTTER_DEG_VALUE, OpenPopup, NULL );
				}
			}
		}
		*/
		if( m_pWin != NULL ){
			m_pWin->requestWindow( Window_Home_Shutter_Top, OpenPopup, NULL );
		}
    }else if( Button.getWidget() == m_pButtonEi ){
		// 20171117 [K460][是正]HOME画面改善により、EI_TOP画面へ遷移に変更
		/*
		// タッチまたはDIAL-SETするとEI画面へ遷移する。
        if( m_pEiGain->isVisible() ){
            if( m_pWin != NULL ){
                m_pWin->requestWindow( WindowID_Menu_GAIN_SELECT, OpenPopup, NULL );
            }
        }else if( m_pEiIso->isVisible() ){
            if( m_pISONative->isVisible() ){
                if( m_pWin != NULL ){
                    m_pWin->requestWindow( 
					, OpenPopup, NULL );
                }
            }else if( m_pISO800Base->isVisible() ){
                if( m_pWin != NULL ){
                    m_pWin->requestWindow( WindowID_Menu_800BASE_ISO, OpenPopup, NULL );
                }
            }else if( m_pISO2500Base->isVisible() ){
                if( m_pWin != NULL ){
                    m_pWin->requestWindow( WindowID_Menu_3200BASE_ISO, OpenPopup, NULL );
                }
            }
        }
		*/
		if( m_pWin != NULL ){
			m_pWin->requestWindow( Window_Home_EI_TOP, OpenPopup, NULL );
		}
    }else if( Button.getWidget() == m_pButtonAudio ){
        // タッチまたはDIAL-SETするとAUDIO-TOP画面へ遷移する。
        if( m_pWin != NULL ){
            m_pWin->requestWindow( Window_Home_Audio_Top, OpenPopup, NULL );
        }
    }else if( Button.getWidget() == m_pButtonWb ){
		if( m_pWin != NULL ){
//            m_pWin->requestWindow( WindowID_Menu_WHITE_VALUE, OpenPopup, NULL );
        }
		// 20171117 [K460][是正]HOME画面改善により、WB_TOP画面へ遷移に変更
		// タッチまたはDIAL-SETするとWB画面へ遷移する。
		// WBの要件Drop
		/*
		if( m_pWin != NULL ){
            m_pWin->requestWindow( Window_Home_WB_Top, OpenPopup, NULL );
        }
		*/
    }
    
    return Flag;
}

bool CtWindowHome::handleTimerEvent(const CtEventTimer& Timer){
	CtButton*	ButtonList[ ButtonIdMax + 1 ] =
	{m_pButtonFps,m_pButtonColor,m_pButtonShutter,m_pButtonEi,m_pButtonAudio,m_pButtonWb};

	//m    ButtonList[m_FocusButton]->setColor( CtWindowHome::ImagColor );
	m_bHighLight = false;
	
    return true;
}

bool CtWindowHome::handleKeyEvent(const CtEventKey& Key){
    bool bRet = false;
    const CtStyle::CtProperty& prop =  CtStyle::getProperty();

    switch (Key.getKeyAction()) {
    case CtEventKey::Press:
        switch (Key.getKeyCode()) {
        case CtEventKey::KeyCode_Enter:     // 同じ処理とKeyCode_ManualFunctionがあります
        case CtEventKey::KeyCode_ManualFunction:
            {   
        		CtButton* pButton = NULL;
				switch( m_FocusButton ){
				case ButtonIdFps:		pButton = m_pButtonFps;		break;
				case ButtonIdColor:		pButton = m_pButtonColor;	break;
				case ButtonIdShutter:	pButton = m_pButtonShutter;	break;
				case ButtonIdEi:		pButton = m_pButtonEi;		break;
				case ButtonIdAudio:		pButton = m_pButtonAudio;	break;
				case ButtonIdWb:		pButton = m_pButtonWb;		break;
				default:	break;
				}
                if (pButton == NULL) return false; 
				//m                pButton->setColor( prop.Button.Selected.Base );
                m_bManualFunction = true;
            }
            return true;
        case CtEventKey::KeyCode_GripUser1: // 同じ処理とKeyCode_Exitがあります
        case CtEventKey::KeyCode_Exit:
            {
                CtButton*   ButtonList[ ButtonIdMax + 1 ] =
                {m_pButtonFps,m_pButtonColor,m_pButtonShutter,m_pButtonEi,m_pButtonAudio,m_pButtonWb};

				//m                ButtonList[m_FocusButton]->setColor( CtWindowHome::ImagColor );
                m_bHighLight = false;
                CtTimer::getInstance()->cancelAlarm(CT_HOME_TIMER_ID, this );
            }
            return true;
        default:
            break;
        }
        break;
    case CtEventKey::Release:
        switch (Key.getKeyCode()) {
        case CtEventKey::KeyCode_Up:
			moveFocus( DirUp );
			return true;
		case CtEventKey::KeyCode_Down:
			moveFocus( DirDown );
			return true;
		case CtEventKey::KeyCode_Left:
			moveFocus( DirLeft );
			return true;
		case CtEventKey::KeyCode_Right:
			moveFocus( DirRight );
			return true;
        case CtEventKey::KeyCode_MmrPlus:
            if( m_bCanMmr ){
        		moveFocus(false);
            }
            return true;
        case CtEventKey::KeyCode_MmrMinus:
            if( m_bCanMmr ){
        		moveFocus(true);
            }
            return true;
        case CtEventKey::KeyCode_Enter:
        case CtEventKey::KeyCode_ManualFunction:
        	{
                m_bManualFunction = false;
                CtTimer::getInstance()->cancelAlarm(CT_HOME_TIMER_ID, this );
        		CtButton* pButton = NULL;
				switch( m_FocusButton ){
				case ButtonIdFps:		pButton = m_pButtonFps;		break;
				case ButtonIdColor:		pButton = m_pButtonColor;	break;
				case ButtonIdShutter:	pButton = m_pButtonShutter;	break;
				case ButtonIdEi:		pButton = m_pButtonEi;		break;
				case ButtonIdAudio:		pButton = m_pButtonAudio;	break;
				case ButtonIdWb:		pButton = m_pButtonWb;		break;
				default:	break;
				}
        		m_bHighLight = false;
        		if( pButton != NULL ){
					//m					pButton->setColor( CtWindowHome::ImagColor );
					CtEventInterface::requestButtonCmd(pButton, this, CtEventButton::Release);
        		}
        	}
        	return true;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return bRet;
}

bool CtWindowHome::handleTouchEvent(const CtEventTouch& Touch){
	return false;
    CtEventTouch::TouchPosition pos = Touch.getPosition();
	CtPosition Pos;
	
	Pos.x = pos.m_X;
	Pos.y = pos.m_Y;
    
	CtButton*	ButtonList[ ButtonIdMax + 1 ] =
	{m_pButtonFps,m_pButtonColor,m_pButtonShutter,m_pButtonEi,m_pButtonAudio,m_pButtonWb};

    int FocusButton = ButtonIdMax + 1;
    int i = 0;
    for(; i < ButtonIdMax + 1; i++ ){
        if( ButtonList[i]->isContains(Pos) ){
            FocusButton = i;
            break;
        }
    }
    switch (Touch.getAction()) {
	case CtEventTouch::Press:
        if( ButtonIdMax + 1 == i ){
            m_bTouchButton = false;
            m_bCanMmr = true;
            return true;
        }else{
            m_bCanMmr = false;
            m_bTouchButton = true;
            m_FocusButton = (ButtonId)FocusButton;
            updateFocus( false );
        }
        break;
	case CtEventTouch::Release:
        m_bCanMmr = true;
        if( m_bTouchButton != false  ){
			//m            ButtonList[m_FocusButton]->setColor( CtWindowHome::ImagColor );
        	m_bHighLight = false;
        }
        if( FocusButton != m_FocusButton ){
            return true;
        }else if( ( FocusButton == m_FocusButton ) && ( true == m_bTouchButton ) ){
            if( ButtonList[m_FocusButton] != NULL ){
                CtEventInterface::requestButtonCmd(ButtonList[i], this, CtEventButton::Release);
            }
        }
        break;
    default:
        break;
    }
    return true;
}

CtStackLabel* CtWindowHome::createStackLabelByList(const char** c, const CtFontSet &fset, int count)
{
	CtStackLabel *sl = new CtStackLabel();
	for (int i = 0; i < count; i++) sl->addLabel(new CtLabel(c[i], fset));
	return sl;
}

CtStackLabel* CtWindowHome::createStackLabelByList(const GDI_STRING_ID* str_id, const CtFontSet &fset, int count)
{
	CtStackLabel *sl = new CtStackLabel();
	for (int i = 0; i < count; i++) sl->addLabel(new CtLabel(str_id[i], fset));
	return sl;
}

CtStackLabel* CtWindowHome::getISONative(){
    CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter_Middle, CtColor::black );

	const char* list[] = {
		"800",
		"3200",
		"2500",
		"400",
		"1250",
	};

	return createStackLabelByList(list, fSet_Center, sizeof(list) / sizeof(char*));
}

CtStackLabel* CtWindowHome::getISO800Base(){
    CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter_Middle, CtColor::black );

	const char* list[] = {
		"200",
		"250",
		"320",
		"400",
		"500",
		"640",
		"800",
		"1000",
		"1250",
		"1600",
		"2000",
		"2500",
		"3200",
		"4000",
	};

	return createStackLabelByList(list, fSet_Center, sizeof(list) / sizeof(char*));
}

CtStackLabel* CtWindowHome::getISO2500Base()
{
    CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter_Middle, CtColor::black );
    
	const char* list[] = {
		"640",
		"800",
		"1000",
		"1250",
		"1600",
		"2000",
		"2500",
		"3200",
		"4000",
		"5000",
		"6400",
		"8000",
		"10000",
		"12800",
		"16000",
		"20000",
		"25600",
	};

	return createStackLabelByList(list, fSet_Center, sizeof(list) / sizeof(char*));
}

CtStackLabel* CtWindowHome::getLabelGain()
{
    CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter_Middle, CtColor::Black );

	const char* list[] = {
		"-12",
		"-10",
		"-8",
		"-6",
		"-4",
		"-2",
		"0",
		"2",
		"4",
		"6",
		"8",
		"10",
		"12",
		"14",
		"16",
		"18",
		"20",
		"22",
		"24",
		"26",
	};

	return createStackLabelByList(list, fSet_Center, sizeof(list) / sizeof(char*));
}

CtStackLabel* CtWindowHome::getLabelColor(LayoutColorIdentifyId ColorId)
{
    CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter, (LayoutColorIdentifyColorBtn == ColorId) ? CtColor::Black : CtColor::White );

	const GDI_STRING_ID list[] = {
		STR_ID_NO_10062,	// "V-LOG"
		STR_ID_NO_10072,	// "V-709"
		STR_ID_NO_10756,	// "SCENE1"
		STR_ID_NO_10757,	// "SCENE2"
		STR_ID_NO_10758,	// SCENE3"
		STR_ID_NO_10759,	// SCENE4"
		STR_ID_NO_10760,	// SCENE5"
		STR_ID_NO_10960,	// RAW"
	};
    
    return createStackLabelByList(list, fSet_Center, sizeof(list) / sizeof(GDI_STRING_ID));
}

CtStackLabel* CtWindowHome::getLabelMainCodec(){
    
    CtFontSet fSet_Left = CtFontSet(FontTypeNormal, CtColor::White);
	fSet_Left.setSize( 0 );

	const GDI_STRING_ID list[] = {
		STR_ID_NO_10674,   // "420LongG 150M"
		STR_ID_NO_10675,   // "420LongG 100M"
		STR_ID_NO_10676,  // "420LongG 50M"
		STR_ID_NO_10677,  // "422LongG 150M"
		STR_ID_NO_10678,  // "422LongG 100M"
		STR_ID_NO_10679,  // "422LongG 50M"
		STR_ID_NO_10048,  // "422Intra 400M"
		STR_ID_NO_10049,  // "422Intra 200M"
		STR_ID_NO_10050,  // "422Intra 100M"
		STR_ID_NO_10622,  // "AVCHD PS"
		STR_ID_NO_10623,  // "AVCHD PH"
		STR_ID_NO_10624,  // "AVCHD HA"
		STR_ID_NO_10625,  // "AVCHD PM"
		STR_ID_NO_10891,  // "ONLY SDI RAW"
	};

	return createStackLabelByList(list, fSet_Left, sizeof(list) / sizeof(GDI_STRING_ID));
}

void CtWindowHome::updateBtnFpsNameLabel(){
    if( APL_PARAM()->getParamState(AplParamVFRMode)->mState != AplParamState_VisibleValid ){
        // VFRが無効のときは、下段のボタン名は非表示とする。
        m_pFpsName->index( 0 );
    }else{
        m_pFpsName->index( 1 );
    }
    return;
}

void CtWindowHome::updateVFROffLabel(){
    // VFRがOFFまたはVFR無効なときFREQUENCYの値を表示
    CtFontSet fSet_Left = CtFontSet( FontTypeNormal, CtColor::black );
	fSet_Left.setSize(60);
    CtFontSet fSet_Right = CtFontSet( FontTypeNormal_alignRight, CtColor::black );
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
        m_pLabelIntPart->setText( "23." );
        m_pLabelDecPart->setText( "98" );
    	m_pLabelInterlace->setVisible( false );
    	m_pDecFpsIcon->setVisible( true );
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
        m_pLabelIntPart->setText( "24." );
        m_pLabelDecPart->setText( "00" );
    	m_pLabelInterlace->setVisible( false );
    	m_pDecFpsIcon->setVisible( true );
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
        m_pLabelIntPart->setText( "25." );
        m_pLabelDecPart->setText( "00" );
    	m_pLabelInterlace->setVisible( false );
    	m_pDecFpsIcon->setVisible( true );
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
        m_pLabelIntPart->setText( "29." );
        m_pLabelDecPart->setText( "97" );
    	m_pLabelInterlace->setVisible( false );
    	m_pDecFpsIcon->setVisible( true );
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
        m_pLabelIntPart->setText( "50." );
        m_pLabelDecPart->setText( "00" );
    	m_pLabelInterlace->setVisible( false );
    	m_pDecFpsIcon->setVisible( true );
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
        m_pLabelIntPart->setText( "59." );
        m_pLabelDecPart->setText( "94" );
    	m_pLabelInterlace->setVisible( false );
    	m_pDecFpsIcon->setVisible( true );
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
        m_pLabelIntPart->setText( "50." );
        m_pLabelDecPart->setText( "00" );
    	m_pLabelInterlace->setVisible( true );
    	m_pDecFpsIcon->setVisible( false );
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
        m_pLabelIntPart->setText( "59." );
        m_pLabelDecPart->setText( "94" );
    	m_pLabelInterlace->setVisible( true );
    	m_pDecFpsIcon->setVisible( false );
        break;
    default:
        break;
    }
    m_pLabelIntPart->setFontSet( fSet_Right );
    m_pLabelDecPart->setFontSet( fSet_Left );
    return;
}

void CtWindowHome::updateVFROnLayout(){
    CtFontSet fSet_Left = CtFontSet( FontTypeNormal, CtColor::black );
	fSet_Left.setSize(60);
    CtFontSet fSet_Right = CtFontSet( FontTypeNormal_alignRight, CtColor::black );
    m_pLabelInterlace->setVisible( false );
	m_pDecFpsIcon->setVisible( true );
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
        if( 24 == APL_PARAM_GET_DATA( AplParamVFRValue ) ){
            m_pLabelIntPart->setText( "23." );
            m_pLabelDecPart->setText( "98" );
            m_pLabelIntPart->setFontSet( fSet_Right );
            m_pLabelDecPart->setFontSet( fSet_Left );
            m_pFpsDecLayout->setVisible( true );
            m_pFpsIntLayout->setVisible( false );
            return;
        }
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
        if( 24 == APL_PARAM_GET_DATA( AplParamVFRValue ) ){
            m_pLabelIntPart->setText( "24." );
            m_pLabelDecPart->setText( "00" );
            m_pLabelIntPart->setFontSet( fSet_Right );
            m_pLabelDecPart->setFontSet( fSet_Left );
            m_pFpsDecLayout->setVisible( true );
            m_pFpsIntLayout->setVisible( false );
            return;
        }
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
        if( 25 == APL_PARAM_GET_DATA( AplParamVFRValue ) ){
            m_pLabelIntPart->setText( "25." );
            m_pLabelDecPart->setText( "00" );
            m_pLabelIntPart->setFontSet( fSet_Right );
            m_pLabelDecPart->setFontSet( fSet_Left );
            m_pFpsDecLayout->setVisible( true );
            m_pFpsIntLayout->setVisible( false );
            return;
        }
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
        if( 30 == APL_PARAM_GET_DATA( AplParamVFRValue ) ){
            m_pLabelIntPart->setText( "29." );
            m_pLabelDecPart->setText( "97" );
            m_pLabelIntPart->setFontSet( fSet_Right );
            m_pLabelDecPart->setFontSet( fSet_Left );
            m_pFpsDecLayout->setVisible( true );
            m_pFpsIntLayout->setVisible( false );
            return;
        }
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
        if( 50 == APL_PARAM_GET_DATA( AplParamVFRValue ) ){
            m_pLabelIntPart->setText( "50." );
            m_pLabelDecPart->setText( "00" );
            m_pLabelIntPart->setFontSet( fSet_Right );
            m_pLabelDecPart->setFontSet( fSet_Left );
            m_pFpsDecLayout->setVisible( true );
            m_pFpsIntLayout->setVisible( false );
            return;
        }
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
        if( 60 == APL_PARAM_GET_DATA( AplParamVFRValue ) ){
            m_pLabelIntPart->setText( "59." );
            m_pLabelDecPart->setText( "94" );
            m_pLabelIntPart->setFontSet( fSet_Right );
            m_pLabelDecPart->setFontSet( fSet_Left );
            m_pFpsDecLayout->setVisible( true );
            m_pFpsIntLayout->setVisible( false );
            return;
        }
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
        if( 50 == APL_PARAM_GET_DATA( AplParamVFRValue ) ){
            m_pLabelIntPart->setText( "50." );
            m_pLabelDecPart->setText( "00" );
            m_pLabelIntPart->setFontSet( fSet_Right );
            m_pLabelDecPart->setFontSet( fSet_Left );
            m_pFpsDecLayout->setVisible( true );
            m_pFpsIntLayout->setVisible( false );
            return;
        }
        break;
    case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
        if( 60 == APL_PARAM_GET_DATA( AplParamVFRValue ) ){
            m_pLabelIntPart->setText( "59." );
            m_pLabelDecPart->setText( "94" );
            m_pLabelIntPart->setFontSet( fSet_Right );
            m_pLabelDecPart->setFontSet( fSet_Left );
            m_pFpsDecLayout->setVisible( true );
            m_pFpsIntLayout->setVisible( false );
            return;
        }
        break;
    default:
        break;
    }
    CtFontSet fSet = CtFontSet( FontTypeNormal_alignCenter, CtColor::black );
    char str_Int[10] = {0};
    sprintf( str_Int, "%d", APL_PARAM_GET_DATA( AplParamVFRValue ) );
    m_pLabelFpsOnInt->setText( str_Int );
    m_pLabelFpsOnInt->setFontSet( fSet );
    m_pFpsIntLayout->setVisible( true );
    m_pFpsDecLayout->setVisible( false );
    return;
}

void CtWindowHome::updateBtnFps(){
    if( APL_PARAM()->getParamState( AplParamVFRMode )->mState != AplParamState_VisibleValid ){
         // VFR無効
        updateVFROffLabel();
        m_pVRFOff->setLayout();
        m_pVRFOff->setVisible( true );
        m_pVRFOn->setVisible( false );
    }else if( APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA( AplParamVFRMode ) ){
        // VFRがONのとき現在の動作フレームレートを表示する 「VFR」のマークを左上に表示する
        updateVFROnLayout();
        m_pVRFOn->setLayout();
        m_pVRFOff->setVisible( false );
        m_pVRFOn->setVisible( true );
    }else{
        // VFRがOFF
        updateVFROffLabel();
        m_pVRFOff->setLayout();
        m_pVRFOn->setVisible( false );
        m_pVRFOff->setVisible( true );
    }
    return;
}

void CtWindowHome::updateBtnColor(){
    if( APL_SYS_PARAM_COLOR_MAIN_VLOG == APL_PARAM_GET_DATA( AplParamColorMain ) ){
        if( APL_PARAM_GET_DATA( AplParamSystemSubRec ) != APL_SYS_PARAM_SYSTEM_SUB_REC_OFF ){
            // MAIN COLOR設定値がV-Log、かつ[SUB REC]がOFF以外の場合
            m_pLabelSubColor->index( APL_PARAM_GET_DATA( AplParamColorSub ) );
            m_pMainVLog->setLayout();
            m_pMainVLog->setVisible( true );
            m_pSubOff->setVisible( false );
            m_pMainScene->setVisible( false );
        }else{
            // MAIN COLOR設定値がV-Log、かつ[SUB REC]がOFFの場合
            m_pSubOff->setVisible( true );
            m_pMainVLog->setVisible( false );
            m_pMainScene->setVisible( false );
        }
    }else if( APL_PARAM_GET_DATA( AplParamColorMain ) != APL_SYS_PARAM_COLOR_MAIN_DUMMY ){
        // MAIN COLOR設定値がV-Log以外（SCENE*）の場合
        m_pLabelMainColor->index( APL_PARAM_GET_DATA( AplParamColorMain ) );
        updateSceneFileName();
        m_pLabelSceneName->setText( m_SceneFileName );
        m_pMainScene->setLayout();
        m_pMainScene->setVisible( true );
        m_pSubOff->setVisible( false );
        m_pMainVLog->setVisible( false );
        
    }
    return;
}

void CtWindowHome::updateBtnShutter(){
	CtFontSet fSet_Center = CtFontSet( FontTypeNormal_alignCenter, CtColor::black );
    CtFontSet fSet_Right = CtFontSet( FontTypeNormal_alignRight, CtColor::black );
    if( APL_SYS_PARAM_SWITCH_OFF == APL_PARAM_GET_DATA( AplParamShutterSwitch ) ){
        m_pShutterOff->setVisible( true );
        m_pShutterSec->setVisible( false );
        m_pShutterDeg->setVisible( false );
    }else if( APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA( AplParamShutterSwitch ) ){
        if( APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND == APL_PARAM_GET_DATA( AplParamShutterDispChg )){
            int temp_Int = (int)( APL_PARAM_GET_DATA( AplParamShutterSecValue ) / 10 );
            int temp_Sec = APL_PARAM_GET_DATA( AplParamShutterSecValue ) % 10;
            char str[10] = {0};
	    	if( temp_Int >= 180 ){
	            sprintf( str, "%d", temp_Int);
	    	} else {
	            sprintf( str, "%d.%d", temp_Int, temp_Sec );
	    	}
            m_pLabelSec->setText( str );
            m_pLabelSec->setFontSet( fSet_Center );
            m_pShutterSec->setVisible( true );
            m_pShutterOff->setVisible( false );
            m_pShutterDeg->setVisible( false );
        }else if( APL_SYS_PARAM_SHUTTER_DISP_CHG_DEGREE == APL_PARAM_GET_DATA( AplParamShutterDispChg )){
            int temp_Int = (int)( APL_PARAM_GET_DATA( AplParamShutterDegValue ) / 10 );
            int temp_Dec = APL_PARAM_GET_DATA( AplParamShutterDegValue ) % 10;
            char str[10] = {0};
            sprintf( str, "%d.%d", temp_Int, temp_Dec );
            m_pLabelDeg->setText( str );
            m_pLabelDeg->setFontSet( fSet_Center );
            m_pShutterDeg->setVisible( true );
            m_pShutterOff->setVisible( false );
            m_pShutterSec->setVisible( false );
        }
    }
    return;
}

void CtWindowHome::updateBtnEi(){
    if( APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN == APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
        if(  APL_SYS_PARAM_GAIN_SWITCH_NORMAL == APL_PARAM_GET_DATA( AplParamGainSwitch ) ){
            m_pLabelGainSel->setImage( IC_NORMAL );   // NORMAL
        }else if( APL_SYS_PARAM_GAIN_SWITCH_HIGH == APL_PARAM_GET_DATA( AplParamGainSwitch ) ){
            m_pLabelGainSel->setImage( IC_HIGH );    // HIGH
        }
        m_pLabelGain->index( APL_PARAM_GET_DATA( AplParamGainSelect ) );
        m_pEiGain->setVisible( true );
        m_pEiIso->setVisible( false ); 
       
    }else if( APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO == APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){  
        m_pLabelIsoSel->index( APL_PARAM_GET_DATA( AplParamISOSelect ) );
        
        switch( APL_PARAM_GET_DATA( AplParamISOSelect ) ){
        case APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY:
            m_pISONative->index( APL_PARAM_GET_DATA( AplParamNativeISO ) );
            m_pISONative->setVisible( true );
            m_pISO800Base->setVisible( false );
            m_pISO2500Base->setVisible( false );
            break;
        case APL_SYS_PARAM_ISO_SELECT_800BASE:
            m_pISO800Base->index( APL_PARAM_GET_DATA( AplParam800BaseISO ) );
            m_pISO800Base->setVisible( true );
            m_pISONative->setVisible( false );
            m_pISO2500Base->setVisible( false );
            break;
        case APL_SYS_PARAM_ISO_SELECT_2500BASE:
            m_pISO2500Base->index( APL_PARAM_GET_DATA( AplParam2500BaseISO ) );
            m_pISO2500Base->setVisible( true );
            m_pISO800Base->setVisible( false );
            m_pISONative->setVisible( false );
            break;
        default:
            break;
        }

        m_pEiIso->setVisible( true );
        m_pEiGain->setVisible( false ); 
    }
    return;
}

void CtWindowHome::updateBtnAudioCH1(){
    CtFontSet fSet = CtFontSet(FontTypeNormal_Middle, CtColor::black);
    char str_CH1[30] = {0};
    if(  APL_SYS_PARAM_CH_IN_SELECT_INT == APL_PARAM_GET_DATA(AplParamInSelectCH1) ){
        strcpy( str_CH1, "INT(L)" );    // STR_ID_NO_10764
    }else if( APL_SYS_PARAM_SELECT_INPUT_MIC == APL_PARAM_GET_DATA(AplParamSelInput1)
        && APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamMicPower1)){
        // マイクパワー設定 ＊入力経路がMIC、かつMIC POWERがONの場合のみ表示
        sprintf(str_CH1,"IN1  MIC  48V" );
    }else{
        char* SEL_INPUT_idlist[APL_SYS_PARAM_SELECT_INPUT_MAX + 1]={
            "LINE", // STR_ID_NO_10767
            "MIC" // STR_ID_NO_10766
        };
        sprintf(str_CH1,"IN1  %s", SEL_INPUT_idlist[APL_PARAM_GET_DATA(AplParamSelInput1)] );
    }
    m_pLabelCH1->setText( str_CH1 ); // 216
    m_pLabelCH1->setFontSet( fSet );
    return;
}

void CtWindowHome::updateBtnAudioCH2(){
    CtFontSet fSet = CtFontSet(FontTypeNormal_Middle, CtColor::black);
    char str_CH2[30] = {0};
    if(  APL_SYS_PARAM_CH_IN_SELECT_INT == APL_PARAM_GET_DATA(AplParamInSelectCH2) ){
        strcpy( str_CH2, "INT(R)");
    }else if( APL_SYS_PARAM_CH_IN_SELECT_INPUT2 == APL_PARAM_GET_DATA(AplParamInSelectCH2) ){
        if( APL_SYS_PARAM_SELECT_INPUT_MIC == APL_PARAM_GET_DATA(AplParamSelInput2)
        && APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamMicPower2) ){
            sprintf( str_CH2,"IN2  MIC  48V" );
        }else{
            char* SEL_INPUT_idlist[APL_SYS_PARAM_SELECT_INPUT_MAX + 1]={
                "LINE", // STR_ID_NO_10767
                "MIC" // STR_ID_NO_10766
            };
            sprintf( str_CH2,"IN2  %s", SEL_INPUT_idlist[APL_PARAM_GET_DATA(AplParamSelInput2)] );
        }
    }else if(  APL_SYS_PARAM_CH_IN_SELECT_INPUT1 == APL_PARAM_GET_DATA(AplParamInSelectCH2) ){
        if( APL_SYS_PARAM_SELECT_INPUT_MIC == APL_PARAM_GET_DATA(AplParamSelInput1)
        && APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA(AplParamMicPower1) ){
            sprintf( str_CH2,"IN1  MIC  48V" );
        }else{
            char* SEL_INPUT_idlist[APL_SYS_PARAM_SELECT_INPUT_MAX + 1]={
                "LINE", // STR_ID_NO_10767
                "MIC" // STR_ID_NO_10766
            };
            sprintf( str_CH2,"IN1  %s", SEL_INPUT_idlist[APL_PARAM_GET_DATA(AplParamSelInput1)] );
        }
    }
    
    m_pLabelCH2->setText( str_CH2 ); // 216
    m_pLabelCH2->setFontSet( fSet );
    return;
}

void CtWindowHome::updateBtnWb(){
    CtFontSet fSet_Right = CtFontSet( FontTypeNormal_alignRight, CtColor::black );
    switch( APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) ){
    case 0:
        {   
            if( APL_SYS_PARAM_SWITCH_ON == APL_PARAM_GET_DATA( AplParamAutoTrackingWhiteLock ) ){
                // ATW LOCK動作中
                m_pLabelWb->index( 1 );
            }else{
                // ATW動作中
                m_pLabelWb->index( 0 );
            }
            m_pATW->setVisible( true );
            m_pWbNum->setVisible( false );
        }
        break;
    case 1:     //  AWB MEMORY
        {
            char str[10] = {0};
            // AWB MEMORYなら色温度の前にAを付けて表示する。
            sprintf( str, "A%d", APL_PARAM_GET_DATA( AplParamWhiteValueTemp ) );
            m_pLabelWbNum->setText( str );
            m_pLabelWbNum->setFontSet( fSet_Right );
            m_pWbNum->setVisible( true );
            m_pATW->setVisible( false );

        }
        break;
    default:
        {   
            char str[10] = {0};
            sprintf( str, "%d", APL_PARAM_GET_DATA( AplParamWhiteValueTemp ) );
            m_pLabelWbNum->setText( str );
            m_pLabelWbNum->setFontSet( fSet_Right );
            m_pWbNum->setVisible( true );
            m_pATW->setVisible( false );
        }
        break;
    }

    return;
}

void CtWindowHome::updateOutColorLayout(){
    if( APL_SYS_PARAM_COLOR_MAIN_VLOG == APL_PARAM_GET_DATA( AplParamColorMain ) ){
		if( APL_PARAM_GET_DATA(AplParamSystemSdiRaw) != APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF){
			m_pLabelSdiOutColor->index( 7);
		}else{
			m_pLabelSdiOutColor->index( APL_PARAM_GET_DATA( AplParamColorSdiOut));
		}
        m_pLabelHdmiOutColor->index( APL_PARAM_GET_DATA( AplParamColorHdmiOut));
        m_pLabelLcdOutColor->index( APL_PARAM_GET_DATA( AplParamColorLcdOut));
        
        m_pOutColorX3->setVisible( true );
        m_pOutColorX1->setVisible( false );
    }else{
        m_pLabelMainOutColor->index( APL_PARAM_GET_DATA( AplParamColorMain ) );
        m_pOutColorX1->setVisible( true );
        m_pOutColorX3->setVisible( false );
    }
    return;
}

void CtWindowHome::updateSysStatusLayout(){
    CtFontSet fSet_Left = CtFontSet(FontTypeNormal, CtColor::White);
	fSet_Left.setSize( 0 );
    char* SEL_Freq_idlist[APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_MAX + 1]={
        "23.98p",   // STR_ID_NO_10021
        "24.00p",   // STR_ID_NO_10022
        "25.00p",   // STR_ID_NO_10023
        "29.97p",   // STR_ID_NO_10024
        "50.00p",   // STR_ID_NO_10025
        "59.94p",   // STR_ID_NO_10026
        "50.00i",   // STR_ID_NO_10027
        "59.94i"    // STR_ID_NO_10028
    };

    char str_SysSta[30] = {0};
    if( APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF == APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
        char* Main_Pix_IdList[9] = {
            "4096x2160",    // STR_ID_NO_10627
            "3840x2160",    // STR_ID_NO_10628
            "2048x1080",    // STR_ID_NO_10629
            "1920x1080",    // STR_ID_NO_10630
            "1280x720",     // STR_ID_NO_10631
            "2048 MIX",     // STR_ID_NO_10632
            "1920 MIX",    // STR_ID_NO_10633
            "2048 CROP",   // STR_ID_NO_10634
            "1920 CROP"    // STR_ID_NO_10635
        };
   //     sprintf( str_SysSta, "%s / %s", Main_Pix_IdList[APL_PARAM_GET_DATA( AplParamSystemMainPixel )], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
        int int_Data = APL_PARAM_GET_DATA( AplParamSystemMainPixel );
        switch( int_Data ){
        case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
            if( APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K == APL_PARAM_GET_DATA(AplParamSystemSensorMode) ){
                sprintf( str_SysSta, "%s / %s", Main_Pix_IdList[5], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
            }else if( APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K == APL_PARAM_GET_DATA(AplParamSystemSensorMode) ){
                sprintf( str_SysSta, "%s / %s", Main_Pix_IdList[7], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
            }else{
                sprintf( str_SysSta, "%s / %s", Main_Pix_IdList[2], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
            }
            break;
        case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
            if( APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K == APL_PARAM_GET_DATA(AplParamSystemSensorMode) ){
                sprintf( str_SysSta, "%s / %s", Main_Pix_IdList[6], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
            }else if( APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K == APL_PARAM_GET_DATA(AplParamSystemSensorMode) ){
                sprintf( str_SysSta, "%s / %s", Main_Pix_IdList[8], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
            }else{
                sprintf( str_SysSta, "%s / %s", Main_Pix_IdList[3], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
            }
            break;
        default:
            sprintf( str_SysSta, "%s / %s", Main_Pix_IdList[APL_PARAM_GET_DATA( AplParamSystemMainPixel )], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
            break;
        }

    }else{
        char* Sdi_Raw_idList[APL_SYS_PARAM_SYSTEM_SDI_RAW_MAX + 1] = {
            "OFF",
            "S35 5.7K",		// STR_ID_NO_10030
            "CROP 4K",		// STR_ID_NO_10755
			"CROP&MIX 2K"   // STR_ID_NO_10959
        };
		sprintf( str_SysSta, "%s / %s", Sdi_Raw_idList[APL_PARAM_GET_DATA( AplParamSystemSdiRaw )], SEL_Freq_idlist[APL_PARAM_GET_DATA( AplParamSystemModeFrequency )] );
    }
    
    m_pLabelSysSta->setText( str_SysSta );
    m_pLabelSysSta->setFontSet( fSet_Left );

    return;
}

void CtWindowHome::updateMainCodecLayout(){
   if( APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF == APL_PARAM_GET_DATA(AplParamSystemSdiRaw) ){
        m_pLabelMainCodec->index( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) );
   }else{
        m_pLabelMainCodec->index( APL_SYS_PARAM_SYSTEM_MAIN_CODEC_MAX + 1 );
   }
   return;
}

void CtWindowHome::update2SlotFuncAndRecModeLayout(){
    if( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) != APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF ){
        m_p2SlotFuncNull->setVisible( true );
        m_pLowerLeft->setVisible( false );
        m_pLowerRight->setVisible( false );
        m_pUpperRight->setVisible( false );
        m_pLowerLeftAndCenter->setVisible( false );
        m_pCenter->setVisible( false );
        m_pBothCenter->setVisible( false );
        return;
    }else{
        m_p2SlotFuncNull->setVisible( false );
        if( APL_PARAM_GET_DATA( AplParamSystemSubRec ) != APL_SYS_PARAM_SYSTEM_SUB_REC_OFF ){
            
            if( ( APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL == APL_PARAM_GET_DATA(AplParamRecFunctionMode) )
                || ( APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT == APL_PARAM_GET_DATA(AplParamRecFunctionMode) ) ){
                if( APL_SYS_PARAM_RELAY_BACKUP_ERR_SUB == APL_PARAM_GET_DATA( AplParamRelayBackupErrStatus )){
                // サブ記録設定時に機能が無効な場合は斜線表示
                    m_pLabelSubRec->setImage( IC_SUB_OFF );
                }else{
                    m_pLabelSubRec->setImage( IC_SUB_ON );
                }
                m_pLowerLeft->setVisible( false );
                m_pLowerRight->setVisible( false );
                m_pUpperRight->setVisible( false );
                m_pLowerLeftAndCenter->setVisible( true );
                m_pCenter->setVisible( false );
                m_pBothCenter->setVisible( false );
                return;
            }else{
                if( APL_SYS_PARAM_RELAY_BACKUP_ERR_SUB == APL_PARAM_GET_DATA( AplParamRelayBackupErrStatus )){
                // サブ記録設定時に機能が無効な場合は斜線表示
                    m_pLabel2SlotOrSub->setImage( IC_SUB_OFF );
                }else{
                    m_pLabel2SlotOrSub->setImage( IC_SUB_ON );
                }
                m_pLowerLeft->setVisible( true );
                m_pLowerRight->setVisible( false );
                m_pUpperRight->setVisible( false );
                m_pLowerLeftAndCenter->setVisible( false );
                m_pCenter->setVisible( false );
                m_pBothCenter->setVisible( false );
                return;
            }
        }
        switch( APL_PARAM_GET_DATA( AplParamRelayBackup ) ){
        case APL_SYS_PARAM_RELAY_BACKUP_RELAY:
            {   
                if( APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL == APL_PARAM_GET_DATA( AplParamRecFunctionMode )
                    || APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT == APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
                    if( APL_SYS_PARAM_RELAY_BACKUP_ERR_RELAY == APL_PARAM_GET_DATA( AplParamRelayBackupErrStatus )){
                    // リレー記録設定時に機能が無効な場合は斜線表示
                        m_pLabelBothCenter2Slot->setImage( IC_RELAY_OFF );
                    }else{
                        m_pLabelBothCenter2Slot->setImage( IC_RELAY_ON );    
                    }
                    m_pLabelBothCenterRec->setImage( IC_INTRVL );
                    m_pLowerLeft->setVisible( false );
                    m_pLowerRight->setVisible( false );
                    m_pUpperRight->setVisible( false );
                    m_pLowerLeftAndCenter->setVisible( false );
                    m_pCenter->setVisible( false );
                    m_pBothCenter->setVisible( true );
                    return;
                }else if( APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP == APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
                    if( APL_SYS_PARAM_RELAY_BACKUP_ERR_RELAY == APL_PARAM_GET_DATA( AplParamRelayBackupErrStatus )){
                    // リレー記録設定時に機能が無効な場合は斜線表示
                        m_pLabelBothCenter2Slot->setImage( IC_RELAY_OFF );
                    }else{
                        m_pLabelBothCenter2Slot->setImage( IC_RELAY_ON );    
                    }
                    m_pLabelBothCenterRec->setImage( IC_LOOP );
                    m_pLowerLeft->setVisible( false );
                    m_pLowerRight->setVisible( false );
                    m_pUpperRight->setVisible( false );
                    m_pLowerLeftAndCenter->setVisible( false );
                    m_pCenter->setVisible( false );
                    m_pBothCenter->setVisible( true );
                    return;
                }else{
                    if( APL_SYS_PARAM_RELAY_BACKUP_ERR_RELAY == APL_PARAM_GET_DATA( AplParamRelayBackupErrStatus ) ){
                    // リレー記録設定時に機能が無効な場合は斜線表示 
                        m_pLabelCenter2Slot->setImage( IC_RELAY_OFF );
                    }else{
                        m_pLabelCenter2Slot->setImage( IC_RELAY_ON );    
                    }
                    m_pLowerLeft->setVisible( false );
                    m_pLowerRight->setVisible( false );
                    m_pUpperRight->setVisible( false );
                    m_pLowerLeftAndCenter->setVisible( false );
                    m_pCenter->setVisible( true );
                    m_pBothCenter->setVisible( false );
                    return;
                }
            }
            break;
        case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:
            {
                if( APL_SYS_PARAM_RELAY_BACKUP_ERR_BACKUP == APL_PARAM_GET_DATA( AplParamRelayBackupErrStatus )){
                    m_pLabel2SlotOrSub->setImage( IC_BACKGR_OFF );
                }else{
                    m_pLabel2SlotOrSub->setImage( IC_BACKGR_ON );
                }
                m_pLowerLeft->setVisible( true );
                m_pLowerRight->setVisible( false );
                m_pUpperRight->setVisible( false );
                m_pLowerLeftAndCenter->setVisible( false );
                m_pCenter->setVisible( false );
                m_pBothCenter->setVisible( false );
                return;
            }
            break;
        case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:
            {
                if( APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL == APL_PARAM_GET_DATA( AplParamRecFunctionMode ) 
                    || APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT == APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
                    if( APL_SYS_PARAM_RELAY_BACKUP_ERR_SIMUL == APL_PARAM_GET_DATA( AplParamRelayBackupErrStatus )){
                        m_pLabelBothCenter2Slot->setImage( IC_SIMUL_OFF );
                    }else{
                        m_pLabelBothCenter2Slot->setImage( IC_SIMUL__ON );
                    }
                    m_pLabelBothCenterRec->setImage( IC_INTRVL );
                    m_pLowerLeft->setVisible( false );
                    m_pLowerRight->setVisible( false );
                    m_pUpperRight->setVisible( false );
                    m_pLowerLeftAndCenter->setVisible( false );
                    m_pCenter->setVisible( false );
                    m_pBothCenter->setVisible( true );
                    return;
                }else{
                    if( APL_SYS_PARAM_RELAY_BACKUP_ERR_SIMUL == APL_PARAM_GET_DATA( AplParamRelayBackupErrStatus )){
                        m_pLabelCenter2Slot->setImage( IC_SIMUL_OFF );
                    }else{
                        m_pLabelCenter2Slot->setImage( IC_SIMUL__ON );
                    }    
                    m_pLowerLeft->setVisible( false );
                    m_pLowerRight->setVisible( false );
                    m_pUpperRight->setVisible( false );
                    m_pLowerLeftAndCenter->setVisible( false );
                    m_pCenter->setVisible( true );
                    m_pBothCenter->setVisible( false );
                    return;
                }
            }
            break;
        default:
            break;
        }

        if(  APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL == APL_PARAM_GET_DATA( AplParamRecFunctionMode ) 
             || APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT == APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
            if(  APL_SYS_PARAM_MEDIA_SELECT_SD == APL_PARAM_GET_DATA( AplParamMediaSelect ) ){
                m_pLabelUpperRight->setImage( IC_INTRVL );
                m_pLowerLeft->setVisible( false );
                m_pLowerRight->setVisible( false );
                m_pUpperRight->setVisible( true );
                m_pLowerLeftAndCenter->setVisible( false );
                m_pCenter->setVisible( false );
                m_pBothCenter->setVisible( false );
                return;
            }else if( APL_SYS_PARAM_MEDIA_SELECT_SD2 == APL_PARAM_GET_DATA( AplParamMediaSelect ) ){
                m_pLabelLowerRight->setImage( IC_INTRVL );
                m_pLowerLeft->setVisible( false );
                m_pLowerRight->setVisible( true );
                m_pUpperRight->setVisible( false );
                m_pLowerLeftAndCenter->setVisible( false );
                m_pCenter->setVisible( false );
                m_pBothCenter->setVisible( false );
                return;
            }
        }else if( APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP == APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
            if(  APL_SYS_PARAM_MEDIA_SELECT_SD == APL_PARAM_GET_DATA( AplParamMediaSelect ) ){
                m_pLabelUpperRight->setImage( IC_LOOP );
                m_pLowerLeft->setVisible( false );
                m_pLowerRight->setVisible( false );
                m_pUpperRight->setVisible( true );
                m_pLowerLeftAndCenter->setVisible( false );
                m_pCenter->setVisible( false );
                m_pBothCenter->setVisible( false );
                return;
            }else if( APL_SYS_PARAM_MEDIA_SELECT_SD2 == APL_PARAM_GET_DATA( AplParamMediaSelect ) ){
                m_pLabelLowerRight->setImage( IC_LOOP );
                m_pLowerLeft->setVisible( false );
                m_pLowerRight->setVisible( true );
                m_pUpperRight->setVisible( false );
                m_pLowerLeftAndCenter->setVisible( false );
                m_pCenter->setVisible( false );
                m_pBothCenter->setVisible( false );
                return;
            }
        }

        m_p2SlotFuncNull->setVisible( true );
        m_pLowerLeft->setVisible( false );
        m_pLowerRight->setVisible( false );
        m_pUpperRight->setVisible( false );
        m_pLowerLeftAndCenter->setVisible( false );
        m_pCenter->setVisible( false );
        m_pBothCenter->setVisible( false );
    }
    return;
}

void CtWindowHome::updateClipLayout(){

    // [SDI RAW]がOFF以外の場合は非表示
    if( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) != APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF ){
        m_pClipNull->setVisible( true );
        m_pClip->setVisible( false );
        return;
    }
    // [MAIN CODEC]がAVCHDの場合は非表示
    switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) ){
    case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS:    // 　同じ処理とPMがあります
    case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH:    // 　同じ処理とPMがあります
    case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA:    // 　同じ処理とPMがあります
    case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM:
        m_pClipNull->setVisible( true );
        m_pClip->setVisible( false );
        return;
    default:
        break;
    }
    updateClipNo();
    updateClipName();
    return;
}

void CtWindowHome::updateSceneFileName(){
    
    memset( m_SceneFileName, 0, sizeof( m_SceneFileName ) );

    int id = 0;
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
         id = AplParamSceneFileName1;   
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
        id = AplParamSceneFileName2;
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
        id = AplParamSceneFileName3;
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
        id = AplParamSceneFileName4;
        break;
    case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
        id = AplParamSceneFileName5;
        break;
    default:
        break;
    }

    APL_PARAM_GET_DATA_AREA( id, (unsigned char*)m_SceneFileName, AplParamSceneFileName1_Size );
    return;
}

CtWindowHome::~CtWindowHome()
{
	destroyWindow();
}

bool CtWindowHome::destroyWindow()
{
    CtTimer::getInstance()->cancelAlarm(CT_HOME_TIMER_ID, this );
	return true;
}

void CtWindowHome::moveFocus(bool Dir)
{
    if( m_bManualFunction ){
        return;
    }
	
	if( m_bHighLight ){
		if( Dir ){
			switch( m_FocusButton ){
			case ButtonIdFps:		m_FocusButton = ButtonIdColor;		break;
			case ButtonIdColor:		m_FocusButton = ButtonIdShutter;	break;
			case ButtonIdShutter:	m_FocusButton = ButtonIdEi;			break;
			case ButtonIdEi:		m_FocusButton = ButtonIdAudio;		break;
			case ButtonIdAudio:		m_FocusButton = ButtonIdWb;			break;
			case ButtonIdWb:		m_FocusButton = ButtonIdFps;		break;
			default:	break;
			}
		} else {
			switch( m_FocusButton ){
			case ButtonIdFps:		m_FocusButton = ButtonIdWb;			break;
			case ButtonIdColor:		m_FocusButton = ButtonIdFps;		break;
			case ButtonIdShutter:	m_FocusButton = ButtonIdColor;		break;
			case ButtonIdEi:		m_FocusButton = ButtonIdShutter;	break;
			case ButtonIdAudio:		m_FocusButton = ButtonIdEi;			break;
			case ButtonIdWb:		m_FocusButton = ButtonIdAudio;		break;
			default:	break;
			}
		}
	}
	updateFocus( true );
}

void CtWindowHome::moveFocus(const CtDirection Dir )
{
	if( m_bHighLight ){
	    switch( Dir ){
	    case DirUp:
	        switch( m_FocusButton ){
			case ButtonIdEi:		m_FocusButton = ButtonIdFps;	    break;
			case ButtonIdAudio:		m_FocusButton = ButtonIdColor;		break;
			case ButtonIdWb:		m_FocusButton = ButtonIdShutter;	break;
			default:	break;
	        }
	        break;
	    case DirDown:
	        switch( m_FocusButton ){
			case ButtonIdFps:		m_FocusButton = ButtonIdEi;		    break;
			case ButtonIdColor:		m_FocusButton = ButtonIdAudio;		break;
			case ButtonIdShutter:	m_FocusButton = ButtonIdWb;		    break;
			default:	break;
	        }
	        break;
	    case DirLeft:
	        switch( m_FocusButton ){
			case ButtonIdColor:		m_FocusButton = ButtonIdFps;		break;
			case ButtonIdShutter:	m_FocusButton = ButtonIdColor;		break;
			case ButtonIdAudio:		m_FocusButton = ButtonIdEi;			break;
			case ButtonIdWb:		m_FocusButton = ButtonIdAudio;		break;
			default:	break;
			}
	        break;
	    case DirRight:
	        switch( m_FocusButton ){
			case ButtonIdFps:		m_FocusButton = ButtonIdColor;		break;
			case ButtonIdColor:		m_FocusButton = ButtonIdShutter;	break;
			case ButtonIdEi:		m_FocusButton = ButtonIdAudio;		break;
			case ButtonIdAudio:		m_FocusButton = ButtonIdWb;			break;
			default:	break;
			}
	        break;
	    default:
	        break;
	    }
	}
	updateFocus( true );
}

void CtWindowHome::updateFocus(bool flag)
{
	CtButton*	ButtonList[ ButtonIdMax + 1 ] =
	{m_pButtonFps,m_pButtonColor,m_pButtonShutter,m_pButtonEi,m_pButtonAudio,m_pButtonWb};
	const CtStyle::CtProperty& prop =  CtStyle::getProperty();

    if( flag ){
        CtTimer::getInstance()->cancelAlarm(CT_HOME_TIMER_ID, this );
    	for( int i = 0 ; i < ButtonIdMax + 1; i++ ){
    		if( i == m_FocusButton ){
    			m_bHighLight = true;
				//m    			ButtonList[i]->setColor( prop.Button.Selected.Base );
                CtTimer::getInstance()->setAlarm(CT_HOME_TIMER_ID, 10000, this );
    		} else {
				//m    			ButtonList[i]->setColor( CtWindowHome::ImagColor );
    		}
    	}
    }else{
        CtTimer::getInstance()->cancelAlarm(CT_HOME_TIMER_ID, this );
        for( int i = 0 ; i < ButtonIdMax + 1; i++ ){
    		if( i == m_FocusButton ){
				//m    			ButtonList[i]->setColor( prop.Button.Selected.Base );
    			m_bHighLight = true;
    		} else {
				//m    			ButtonList[i]->setColor( CtWindowHome::ImagColor );
    		}
    	}
    }
}
