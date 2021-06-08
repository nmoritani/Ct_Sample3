/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version:	7.5.1
 *  Element:			AplParamMainExclusionFunc
 */


#ifndef Foundation_Manager_AplParamMainExclusionFunc_H
#define Foundation_Manager_AplParamMainExclusionFunc_H

#include <oxf.h>
class AplParamService;

//## package Foundation::Manager

//## class AplParamMainExclusionFunc
class AplParamMainExclusionFunc {
    ////    Constructors and destructors    ////
    
public :

    //## operation AplParamMainExclusionFunc()
    AplParamMainExclusionFunc();
    
    //## operation ~AplParamMainExclusionFunc()
    virtual ~AplParamMainExclusionFunc();
    
    ////    Operations    ////
    
    //## operation execute(int)
    void execute(int id);
    
    //## operation AplParamRecFormat_Exclusion(int)
    virtual void AplParamRecFormat_Exclusion(int id);
    
    //## operation AplParamSystemRecMode_Exclusion(int)
    virtual void AplParamSystemRecMode_Exclusion(int id);
    
    //## operation AplParamPlaySlot_Exclusion(int)
    virtual void AplParamPlaySlot_Exclusion(int id);
    
    //## operation AplParamPlaySlotStateDecidion_Exclusion(int)
    virtual void AplParamPlaySlotStateDecidion_Exclusion(int id);
    
    //## operation AplParamGainLow_Exclusion(int)
    virtual void AplParamGainLow_Exclusion(int id);
    
    //## operation AplParamGainMid_Exclusion(int)
    virtual void AplParamGainMid_Exclusion(int id);
    
    //## operation AplParamGainHigh_Exclusion(int)
    virtual void AplParamGainHigh_Exclusion(int id);
    
    //## operation AplParamAFRange_Exclusion(int)
    virtual void AplParamAFRange_Exclusion(int id);
    
    //## operation AplParamRopControlZoomFocus_Exclusion(int)
    virtual void AplParamRopControlZoomFocus_Exclusion(int id);
    
    //## operation AplParamUserButton1_Exclusion(int)
    virtual void AplParamUserButton1_Exclusion(int id);
    
    //## operation AplParamUserButton2_Exclusion(int)
    virtual void AplParamUserButton2_Exclusion(int id);
    
    //## operation AplParamUserButton3_Exclusion(int)
    virtual void AplParamUserButton3_Exclusion(int id);
    
    //## operation AplParamUserButton4_Exclusion(int)
    virtual void AplParamUserButton4_Exclusion(int id);
    
    //## operation AplParamUserButton5_Exclusion(int)
    virtual void AplParamUserButton5_Exclusion(int id);
    
    //## operation AplParamUserButton6_Exclusion(int)
    virtual void AplParamUserButton6_Exclusion(int id);
    
    //## operation AplParamUserButton7_Exclusion(int)
    virtual void AplParamUserButton7_Exclusion(int id);
    
    //## operation AplParamUserButton8_Exclusion(int)
    virtual void AplParamUserButton8_Exclusion(int id);
    
    //## operation AplParamUserButton9_Exclusion(int)
    virtual void AplParamUserButton9_Exclusion(int id);
    
    //## operation AplParamUserButton10_Exclusion(int)
    virtual void AplParamUserButton10_Exclusion(int id);
    
    //## operation AplParamUserButton11_Exclusion(int)
    virtual void AplParamUserButton11_Exclusion(int id);
    
    //## operation AplParamUserButton12_Exclusion(int)
    virtual void AplParamUserButton12_Exclusion(int id);
    
    //## operation AplParamSceneFileName_Exclusion(int)
    virtual void AplParamSceneFileName_Exclusion(int id);
    
    //## operation AplParamSceneVFRMode_Exclusion(int)
    virtual void AplParamSceneVFRMode_Exclusion(int id);
    
    //## operation AplParamSceneVFRValue_Exclusion(int)
    virtual void AplParamSceneVFRValue_Exclusion(int id);
    
    //## operation AplParamSceneVFRValue_NTSC_Exclusion(int)
    virtual void AplParamSceneVFRValue_NTSC_Exclusion(int id);
    
    //## operation AplParamSceneVFRValue_PAL_Exclusion(int)
    virtual void AplParamSceneVFRValue_PAL_Exclusion(int id);
    
    //## operation AplParamSceneSyncScanType_Exclusion(int)
    virtual void AplParamSceneSyncScanType_Exclusion(int id);
    
    //## operation AplParamSceneSyncScanSecValue_Exclusion(int)
    virtual void AplParamSceneSyncScanSecValue_Exclusion(int id);
    
    //## operation AplParamSceneSyncScanSecValue_NTSC_Exclusion(int)
    virtual void AplParamSceneSyncScanSecValue_NTSC_Exclusion(int id);
    
    //## operation AplParamSceneSyncScanSecValue_PAL_Exclusion(int)
    virtual void AplParamSceneSyncScanSecValue_PAL_Exclusion(int id);
    
    //## operation AplParamSceneSyncScanDegValue_Exclusion(int)
    virtual void AplParamSceneSyncScanDegValue_Exclusion(int id);
    
    //## operation AplParamSceneDetailMasterLevel_Exclusion(int)
    virtual void AplParamSceneDetailMasterLevel_Exclusion(int id);
    
    //## operation AplParamSceneDetailCoring_Exclusion(int)
    virtual void AplParamSceneDetailCoring_Exclusion(int id);
    
    //## operation AplParamSceneDetail_Exclusion(int)
    virtual void AplParamSceneDetail_Exclusion(int id);
    
    //## operation AplParamSceneVDetailLevel_Exclusion(int)
    virtual void AplParamSceneVDetailLevel_Exclusion(int id);
    
    //## operation AplParamSceneDetailFrequency_Exclusion(int)
    virtual void AplParamSceneDetailFrequency_Exclusion(int id);
    
    //## operation AplParamSceneDetailLevelDepend_Exclusion(int)
    virtual void AplParamSceneDetailLevelDepend_Exclusion(int id);
    
    //## operation AplParamSceneDetailKneeApeLvl_Exclusion(int)
    virtual void AplParamSceneDetailKneeApeLvl_Exclusion(int id);
    
    //## operation AplParamSceneDetailGainPlus_Exclusion(int)
    virtual void AplParamSceneDetailGainPlus_Exclusion(int id);
    
    //## operation AplParamSceneDetailGainMinus_Exclusion(int)
    virtual void AplParamSceneDetailGainMinus_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlA_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlA_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlB_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlB_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlC_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlC_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneZebra_Exclusion(int)
    virtual void AplParamSceneSkinToneZebra_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlDetectTable_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlDetectTable_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlEffect_A_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlEffect_A_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlICenter_A_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlICenter_A_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlIWidth_A_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlIWidth_A_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlQWidth_A_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlQWidth_A_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlQPhase_A_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlQPhase_A_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlEffect_B_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlEffect_B_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlICenter_B_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlICenter_B_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlIWidth_B_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlIWidth_B_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlQWidth_B_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlQWidth_B_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlQPhase_B_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlQPhase_B_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlEffect_C_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlEffect_C_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlICenter_C_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlICenter_C_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlIWidth_C_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlIWidth_C_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlQWidth_C_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlQWidth_C_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlQPhase_C_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlQPhase_C_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlEffect_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlEffect_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlICenter_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlICenter_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlIWidth_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlIWidth_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlQWidth_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlQWidth_Exclusion(int id);
    
    //## operation AplParamSceneSkinToneDtlQPhase_Exclusion(int)
    virtual void AplParamSceneSkinToneDtlQPhase_Exclusion(int id);
    
    //## operation AplParamSceneRGainAwbPre_Exclusion(int)
    virtual void AplParamSceneRGainAwbPre_Exclusion(int id);
    
    //## operation AplParamSceneBGainAwbPre_Exclusion(int)
    virtual void AplParamSceneBGainAwbPre_Exclusion(int id);
    
    //## operation AplParamSceneRGainAwbA_Exclusion(int)
    virtual void AplParamSceneRGainAwbA_Exclusion(int id);
    
    //## operation AplParamSceneBGainAwbA_Exclusion(int)
    virtual void AplParamSceneBGainAwbA_Exclusion(int id);
    
    //## operation AplParamSceneRGainAwbB_Exclusion(int)
    virtual void AplParamSceneRGainAwbB_Exclusion(int id);
    
    //## operation AplParamSceneBGainAwbB_Exclusion(int)
    virtual void AplParamSceneBGainAwbB_Exclusion(int id);
    
    //## operation AplParamSceneAwbAGainOffSet_Exclusion(int)
    virtual void AplParamSceneAwbAGainOffSet_Exclusion(int id);
    
    //## operation AplParamSceneAwbBGainOffSet_Exclusion(int)
    virtual void AplParamSceneAwbBGainOffSet_Exclusion(int id);
    
    //## operation AplParamSceneAchColorTemp_Exclusion(int)
    virtual void AplParamSceneAchColorTemp_Exclusion(int id);
    
    //## operation AplParamSceneAchColorTempRGain_Exclusion(int)
    virtual void AplParamSceneAchColorTempRGain_Exclusion(int id);
    
    //## operation AplParamSceneAchColorTempBGain_Exclusion(int)
    virtual void AplParamSceneAchColorTempBGain_Exclusion(int id);
    
    //## operation AplParamSceneAchColorTempGAxis_Exclusion(int)
    virtual void AplParamSceneAchColorTempGAxis_Exclusion(int id);
    
    //## operation AplParamSceneBchColorTemp_Exclusion(int)
    virtual void AplParamSceneBchColorTemp_Exclusion(int id);
    
    //## operation AplParamSceneBchColorTempRGain_Exclusion(int)
    virtual void AplParamSceneBchColorTempRGain_Exclusion(int id);
    
    //## operation AplParamSceneBchColorTempBGain_Exclusion(int)
    virtual void AplParamSceneBchColorTempBGain_Exclusion(int id);
    
    //## operation AplParamSceneBchColorTempGAxis_Exclusion(int)
    virtual void AplParamSceneBchColorTempGAxis_Exclusion(int id);
    
    //## operation AplParamSceneChromaLevel_Exclusion(int)
    virtual void AplParamSceneChromaLevel_Exclusion(int id);
    
    //## operation AplParamSceneChromaPhase_Exclusion(int)
    virtual void AplParamSceneChromaPhase_Exclusion(int id);
    
    //## operation AplParamSceneMatrix_Exclusion(int)
    virtual void AplParamSceneMatrix_Exclusion(int id);
    
    //## operation AplParamSceneMatrix_R_G_Exclusion(int)
    virtual void AplParamSceneMatrix_R_G_Exclusion(int id);
    
    //## operation AplParamSceneMatrix_R_B_Exclusion(int)
    virtual void AplParamSceneMatrix_R_B_Exclusion(int id);
    
    //## operation AplParamSceneMatrix_G_R_Exclusion(int)
    virtual void AplParamSceneMatrix_G_R_Exclusion(int id);
    
    //## operation AplParamSceneMatrix_G_B_Exclusion(int)
    virtual void AplParamSceneMatrix_G_B_Exclusion(int id);
    
    //## operation AplParamSceneMatrix_B_R_Exclusion(int)
    virtual void AplParamSceneMatrix_B_R_Exclusion(int id);
    
    //## operation AplParamSceneMatrix_B_G_Exclusion(int)
    virtual void AplParamSceneMatrix_B_G_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_R_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_R_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_R_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_R_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_R_R_Mg_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_R_R_Mg_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_R_R_Mg_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_R_R_Mg_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_R_Mg_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_R_Mg_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_R_Mg_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_R_Mg_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Mg_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_Mg_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Mg_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Mg_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Mg_B_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_Mg_B_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Mg_B_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Mg_B_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_B_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_B_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_B_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_B_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_B_Cy_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_B_Cy_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_B_Cy_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_B_Cy_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Cy_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_Cy_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Cy_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Cy_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Cy_G_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_Cy_G_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Cy_G_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Cy_G_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_G_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_G_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_G_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_G_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_G_Yl_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_G_Yl_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_G_Yl_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_G_Yl_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_G_Yl_Yl_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_G_Yl_Yl_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_G_Yl_Yl_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_G_Yl_Yl_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_Yl_R_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_Yl_R_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_Yl_R_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_Yl_R_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_R_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_R_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_R_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_R_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_R_R_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_R_R_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_R_R_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_R_R_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneMasterPed_Exclusion(int)
    virtual void AplParamSceneMasterPed_Exclusion(int id);
    
    //## operation AplParamSceneBlackRPedestal_Exclusion(int)
    virtual void AplParamSceneBlackRPedestal_Exclusion(int id);
    
    //## operation AplParamSceneBlackGPedestal_Exclusion(int)
    virtual void AplParamSceneBlackGPedestal_Exclusion(int id);
    
    //## operation AplParamSceneBlackBPedestal_Exclusion(int)
    virtual void AplParamSceneBlackBPedestal_Exclusion(int id);
    
    //## operation AplParamSceneBlackPedestalOffset_Exclusion(int)
    virtual void AplParamSceneBlackPedestalOffset_Exclusion(int id);
    
    //## operation AplParamSceneGammaModeSel_Exclusion(int)
    virtual void AplParamSceneGammaModeSel_Exclusion(int id);
    
    //## operation AplParamSceneMasterGamma_Exclusion(int)
    virtual void AplParamSceneMasterGamma_Exclusion(int id);
    
    //## operation AplParamSceneGammaFRecDynamicLvl_Exclusion(int)
    virtual void AplParamSceneGammaFRecDynamicLvl_Exclusion(int id);
    
    //## operation AplParamSceneGammaFRecBlackStrLvl_Exclusion(int)
    virtual void AplParamSceneGammaFRecBlackStrLvl_Exclusion(int id);
    
    //## operation AplParamSceneGammaVRecKneeSlope_Exclusion(int)
    virtual void AplParamSceneGammaVRecKneeSlope_Exclusion(int id);
    
    //## operation AplParamSceneGammaVRecKneePoint_Exclusion(int)
    virtual void AplParamSceneGammaVRecKneePoint_Exclusion(int id);
    
    //## operation AplParamSceneBlackGamma_Exclusion(int)
    virtual void AplParamSceneBlackGamma_Exclusion(int id);
    
    //## operation AplParamSceneBlackGammaRange_Exclusion(int)
    virtual void AplParamSceneBlackGammaRange_Exclusion(int id);
    
    //## operation AplParamSceneKneeMode_Exclusion(int)
    virtual void AplParamSceneKneeMode_Exclusion(int id);
    
    //## operation AplParamSceneAKneeResponse_Exclusion(int)
    virtual void AplParamSceneAKneeResponse_Exclusion(int id);
    
    //## operation AplParamSceneKneePoint_Exclusion(int)
    virtual void AplParamSceneKneePoint_Exclusion(int id);
    
    //## operation AplParamSceneKneeSlope_Exclusion(int)
    virtual void AplParamSceneKneeSlope_Exclusion(int id);
    
    //## operation AplParamSceneHlgKneeSwitch_Exclusion(int)
    virtual void AplParamSceneHlgKneeSwitch_Exclusion(int id);
    
    //## operation AplParamSceneHlgKneePoint_Exclusion(int)
    virtual void AplParamSceneHlgKneePoint_Exclusion(int id);
    
    //## operation AplParamSceneHlgKneeSlope_Exclusion(int)
    virtual void AplParamSceneHlgKneeSlope_Exclusion(int id);
    
    //## operation AplParamSceneWhiteClipSwitch_Exclusion(int)
    virtual void AplParamSceneWhiteClipSwitch_Exclusion(int id);
    
    //## operation AplParamSceneWhiteClipLevel_Exclusion(int)
    virtual void AplParamSceneWhiteClipLevel_Exclusion(int id);
    
    //## operation AplParamSceneDRS_Exclusion(int)
    virtual void AplParamSceneDRS_Exclusion(int id);
    
    //## operation AplParamSceneDRSEffectDepth_Exclusion(int)
    virtual void AplParamSceneDRSEffectDepth_Exclusion(int id);
    
    //## operation AplParamSceneDNR_Exclusion(int)
    virtual void AplParamSceneDNR_Exclusion(int id);
    
    //## operation AplParamSceneAutoIrisLevel_Exclusion(int)
    virtual void AplParamSceneAutoIrisLevel_Exclusion(int id);
    
    //## operation AplParamSceneAutoIrisLevelEffect_Exclusion(int)
    virtual void AplParamSceneAutoIrisLevelEffect_Exclusion(int id);
    
    //## operation AplParamSdiOutFormat_Exclusion(int)
    virtual void AplParamSdiOutFormat_Exclusion(int id);
    
    //## operation AplParamSdiEdh_Exclusion(int)
    virtual void AplParamSdiEdh_Exclusion(int id);
    
    //## operation AplParamSdiRemote_Exclusion(int)
    virtual void AplParamSdiRemote_Exclusion(int id);
    
    //## operation AplParamSdiOutZebra_Exclusion(int)
    virtual void AplParamSdiOutZebra_Exclusion(int id);
    
    //## operation AplParamSdiOutHdr_Exclusion(int)
    virtual void AplParamSdiOutHdr_Exclusion(int id);
    
    //## operation AplParamHdmiOutFormat_Exclusion(int)
    virtual void AplParamHdmiOutFormat_Exclusion(int id);
    
    //## operation AplParamHdmiRecRemote_Exclusion(int)
    virtual void AplParamHdmiRecRemote_Exclusion(int id);
    
    //## operation AplParamHdmiOutZebra_Exclusion(int)
    virtual void AplParamHdmiOutZebra_Exclusion(int id);
    
    //## operation AplParamHdmiOutHdr_Exclusion(int)
    virtual void AplParamHdmiOutHdr_Exclusion(int id);
    
    //## operation AplParamAvOutZebra_Exclusion(int)
    virtual void AplParamAvOutZebra_Exclusion(int id);
    
    //## operation AplParamLcdVfOutHdr_Exclusion(int)
    virtual void AplParamLcdVfOutHdr_Exclusion(int id);
    
    //## operation AplParamIndicatorDateTime_Exclusion(int)
    virtual void AplParamIndicatorDateTime_Exclusion(int id);
    
    //## operation AplParamLcdMarkerFrameMarker_Exclusion(int)
    virtual void AplParamLcdMarkerFrameMarker_Exclusion(int id);
    
    //## operation AplParamZebraPro_Exclusion(int)
    virtual void AplParamZebraPro_Exclusion(int id);
    
    //## operation AplParamFileSplit_Exclusion(int)
    virtual void AplParamFileSplit_Exclusion(int id);
    
    //## operation AplParamRelayBackup_Exclusion(int)
    virtual void AplParamRelayBackup_Exclusion(int id);
    
    //## operation AplParamPreRec_Exclusion(int)
    virtual void AplParamPreRec_Exclusion(int id);
    
    //## operation AplParamRecFunctionMode_Exclusion(int)
    virtual void AplParamRecFunctionMode_Exclusion(int id);
    
    //## operation AplParamTCG_Exclusion(int)
    virtual void AplParamTCG_Exclusion(int id);
    
    //## operation AplParamTCMode_Exclusion(int)
    virtual void AplParamTCMode_Exclusion(int id);
    
    //## operation AplParamUsersBitMode_Exclusion(int)
    virtual void AplParamUsersBitMode_Exclusion(int id);
    
    //## operation AplParamTimeStamp_Exclusion(int)
    virtual void AplParamTimeStamp_Exclusion(int id);
    
    //## operation AplParamIpRemoteEnable_Exclusion(int)
    virtual void AplParamIpRemoteEnable_Exclusion(int id);
    
    //## operation AplParamStreamingFormat_Exclusion(int)
    virtual void AplParamStreamingFormat_Exclusion(int id);
    
    //## operation AplParamStreamingReceiverUrl_Exclusion(int)
    virtual void AplParamStreamingReceiverUrl_Exclusion(int id);
    
    //## operation AplParamStreamingStart_Exclusion(int)
    virtual void AplParamStreamingStart_Exclusion(int id);
    
    //## operation AplParamNdiHxStreamingFormat_Exclusion(int)
    virtual void AplParamNdiHxStreamingFormat_Exclusion(int id);
    
    //## operation AplParamLanDhcpMode_Exclusion(int)
    virtual void AplParamLanDhcpMode_Exclusion(int id);
    
    //## operation AplParamLanDhcpModeV6_Exclusion(int)
    virtual void AplParamLanDhcpModeV6_Exclusion(int id);
    
    //## operation AplParamBand_Exclusion(int)
    virtual void AplParamBand_Exclusion(int id);
    
    //## operation AplParamChannel_Exclusion(int)
    virtual void AplParamChannel_Exclusion(int id);
    
    //## operation AplParamChannel5G_Exclusion(int)
    virtual void AplParamChannel5G_Exclusion(int id);
    
    //## operation AplParamEncryption_Exclusion(int)
    virtual void AplParamEncryption_Exclusion(int id);
    
    //## operation AplParamMySecurityType_Exclusion(int)
    virtual void AplParamMySecurityType_Exclusion(int id);
    
    //## operation AplParamDhcpMode_Exclusion(int)
    virtual void AplParamDhcpMode_Exclusion(int id);
    
    //## operation AplParamDhcpModeV6_Exclusion(int)
    virtual void AplParamDhcpModeV6_Exclusion(int id);
    
    //## operation AplParamEasyIpSetting_Exclusion(int)
    virtual void AplParamEasyIpSetting_Exclusion(int id);
    
    //## operation AplParamRecFormat59Hz_Exclusion(int)
    virtual void AplParamRecFormat59Hz_Exclusion(int id);
    
    //## operation AplParamRecFormat50Hz_Exclusion(int)
    virtual void AplParamRecFormat50Hz_Exclusion(int id);
    
    //## operation AplParamMOVQuality59Hz_Exclusion(int)
    virtual void AplParamMOVQuality59Hz_Exclusion(int id);
    
    //## operation AplParamMOVQuality50Hz_Exclusion(int)
    virtual void AplParamMOVQuality50Hz_Exclusion(int id);
    
    //## operation AplParamProxyRecMode_Exclusion(int)
    virtual void AplParamProxyRecMode_Exclusion(int id);
    
    //## operation AplParamProxyRecFormat_Exclusion(int)
    virtual void AplParamProxyRecFormat_Exclusion(int id);
    
    //## operation AplParamSuperSlowRec_Exclusion(int)
    virtual void AplParamSuperSlowRec_Exclusion(int id);
    
    //## operation AplParamSceneAchColorTempRGainCtrl_Exclusion(int)
    virtual void AplParamSceneAchColorTempRGainCtrl_Exclusion(int id);
    
    //## operation AplParamSceneAchColorTempGGainCtrl_Exclusion(int)
    virtual void AplParamSceneAchColorTempGGainCtrl_Exclusion(int id);
    
    //## operation AplParamSceneAchWhiteValueAWBResult_Exclusion(int)
    virtual void AplParamSceneAchWhiteValueAWBResult_Exclusion(int id);
    
    //## operation AplParamSceneBchColorTempRGainCtrl_Exclusion(int)
    virtual void AplParamSceneBchColorTempRGainCtrl_Exclusion(int id);
    
    //## operation AplParamSceneBchColorTempGGainCtrl_Exclusion(int)
    virtual void AplParamSceneBchColorTempGGainCtrl_Exclusion(int id);
    
    //## operation AplParamSceneBchWhiteValueAWBResult_Exclusion(int)
    virtual void AplParamSceneBchWhiteValueAWBResult_Exclusion(int id);
    
    //## operation AplParamSuperGain_Exclusion(int)
    virtual void AplParamSuperGain_Exclusion(int id);
    
    //## operation AplParamColorBar_Exclusion(int)
    virtual void AplParamColorBar_Exclusion(int id);
    
    //## operation AplParamAlert_Exclusion(int)
    virtual void AplParamAlert_Exclusion(int id);
    
    //## operation AplParamWarning_Exclusion(int)
    virtual void AplParamWarning_Exclusion(int id);
    
    //## operation AplParamOverClipSd1_Exclusion(int)
    virtual void AplParamOverClipSd1_Exclusion(int id);
    
    //## operation AplParamOverClipSd2_Exclusion(int)
    virtual void AplParamOverClipSd2_Exclusion(int id);
    
    //## operation AplParamLcdMarkerUserSw_Exclusion(int)
    virtual void AplParamLcdMarkerUserSw_Exclusion(int id);
    
    //## operation AplParamSpotMeterUserSw_Exclusion(int)
    virtual void AplParamSpotMeterUserSw_Exclusion(int id);
    
    //## operation AplParamLcdFocusExpandUserSw_Exclusion(int)
    virtual void AplParamLcdFocusExpandUserSw_Exclusion(int id);
    
    //## operation AplParamDZoomUserSw_Exclusion(int)
    virtual void AplParamDZoomUserSw_Exclusion(int id);
    
    //## operation AplParamAudioLevelMeterInvalid_Exclusion(int)
    virtual void AplParamAudioLevelMeterInvalid_Exclusion(int id);
    
    //## operation AplParamTcFrameMax_Exclusion(int)
    virtual void AplParamTcFrameMax_Exclusion(int id);
    
    //## operation AplParamWFM_Exclusion(int)
    virtual void AplParamWFM_Exclusion(int id);
    
    //## operation AplParamAudioVol_Exclusion(int)
    virtual void AplParamAudioVol_Exclusion(int id);
    
    //## operation AplParamAreaMode_Exclusion(int)
    virtual void AplParamAreaMode_Exclusion(int id);
    
    //## operation AplParamSuperGainExe_Exclusion(int)
    virtual void AplParamSuperGainExe_Exclusion(int id);
    
    //## operation AplParamNetworkFunc_Exclusion(int)
    virtual void AplParamNetworkFunc_Exclusion(int id);
    
    //## operation AplParamAutoIrisLevelEffectAdjust_Exclusion(int)
    virtual void AplParamAutoIrisLevelEffectAdjust_Exclusion(int id);
};

#endif
