/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version:	7.5.1
 *  Element:			AplParamMainExclusionFuncK460
 */


#ifndef Foundation_Manager_AplParamMainExclusionFuncK460_H
#define Foundation_Manager_AplParamMainExclusionFuncK460_H

#include "AplParamMainExclusionFunc.h"
class AplIfAvs;

class AplNetworkEventService;

class AplParamService;

//## package Foundation::Manager

//## class AplParamMainExclusionFuncK460
class AplParamMainExclusionFuncK460 : public AplParamMainExclusionFunc {
    ////    Constructors and destructors    ////
    
public :

    //## operation AplParamMainExclusionFuncK460()
    AplParamMainExclusionFuncK460();
    
    virtual ~AplParamMainExclusionFuncK460();
    
    ////    Operations    ////
    
    //## operation AplParamBalanceLevel_Exclusion(int)
    virtual void AplParamBalanceLevel_Exclusion(int id);
    
    //## operation AplParamColorBar_Exclusion(int)
    virtual void AplParamColorBar_Exclusion(int id);
    
    //## operation AplParamColorHdmiOut_Exclusion(int)
    virtual void AplParamColorHdmiOut_Exclusion(int id);
    
    //## operation AplParamColorLcdOut_Exclusion(int)
    virtual void AplParamColorLcdOut_Exclusion(int id);
    
    //## operation AplParamColorMain_Exclusion(int)
    virtual void AplParamColorMain_Exclusion(int id);
    
    //## operation AplParamColorSdiOut_Exclusion(int)
    virtual void AplParamColorSdiOut_Exclusion(int id);
    
    //## operation AplParamColorSub_Exclusion(int)
    virtual void AplParamColorSub_Exclusion(int id);
    
    //## operation AplParamDZoomUserSw_Exclusion(int)
    virtual void AplParamDZoomUserSw_Exclusion(int id);
    
    //## operation AplParamEISSwitch_Exclusion(int)
    virtual void AplParamEISSwitch_Exclusion(int id);
    
    //## operation AplParamGainIsoDispChg_Exclusion(int)
    virtual void AplParamGainIsoDispChg_Exclusion(int id);
    
    //## operation AplParamGainSelect_Exclusion(int)
    virtual void AplParamGainSelect_Exclusion(int id);
    
    //## operation AplParamEncryption_Exclusion(int)
    virtual void AplParamEncryption_Exclusion(int id);
    
    //## operation AplParamHdmiOutFormat_Exclusion(int)
    virtual void AplParamHdmiOutFormat_Exclusion(int id);
    
    //## operation AplParamHdmiOutMenuDisp_Exclusion(int)
    virtual void AplParamHdmiOutMenuDisp_Exclusion(int id);
    
    //## operation AplParamHdmiTcOutput_Exclusion(int)
    virtual void AplParamHdmiTcOutput_Exclusion(int id);
    
    //## operation AplParamLcdEIAssistSpotMeterDisp_Exclusion(int)
    virtual void AplParamLcdEIAssistSpotMeterDisp_Exclusion(int id);
    
    //## operation AplParamLcdIndicatorRecFuncMode_Exclusion(int)
    virtual void AplParamLcdIndicatorRecFuncMode_Exclusion(int id);
    
    //## operation AplParamLcdMarkerUserSw_Exclusion(int)
    virtual void AplParamLcdMarkerUserSw_Exclusion(int id);
    
    //## operation AplParamLimiterCH1_Exclusion(int)
    virtual void AplParamLimiterCH1_Exclusion(int id);
    
    //## operation AplParamLimiterCH2_Exclusion(int)
    virtual void AplParamLimiterCH2_Exclusion(int id);
    
    //## operation AplParamOutIndicatorRecFuncMode_Exclusion(int)
    virtual void AplParamOutIndicatorRecFuncMode_Exclusion(int id);
    
    //## operation AplParamPreRec_Exclusion(int)
    virtual void AplParamPreRec_Exclusion(int id);
    
    //## operation AplParamRecFunctionMode_Exclusion(int)
    virtual void AplParamRecFunctionMode_Exclusion(int id);
    
    //## operation AplParamRelayBackup_Exclusion(int)
    virtual void AplParamRelayBackup_Exclusion(int id);
    
    //## operation AplParamSceneBlackGamma_Exclusion(int)
    virtual void AplParamSceneBlackGamma_Exclusion(int id);
    
    //## operation AplParamSceneBlackGammaRange_Exclusion(int)
    virtual void AplParamSceneBlackGammaRange_Exclusion(int id);
    
    //## operation AplParamSceneBlackBPedestal_Exclusion(int)
    virtual void AplParamSceneBlackBPedestal_Exclusion(int id);
    
    //## operation AplParamSceneBlackGPedestal_Exclusion(int)
    virtual void AplParamSceneBlackGPedestal_Exclusion(int id);
    
    //## operation AplParamSceneBlackMasterPedestal_Exclusion(int)
    virtual void AplParamSceneBlackMasterPedestal_Exclusion(int id);
    
    //## operation AplParamSceneBlackPedestalOffset_Exclusion(int)
    virtual void AplParamSceneBlackPedestalOffset_Exclusion(int id);
    
    //## operation AplParamSceneBlackRPedestal_Exclusion(int)
    virtual void AplParamSceneBlackRPedestal_Exclusion(int id);
    
    //## operation AplParamSceneChromaLevel_Exclusion(int)
    virtual void AplParamSceneChromaLevel_Exclusion(int id);
    
    //## operation AplParamSceneChromaPhase_Exclusion(int)
    virtual void AplParamSceneChromaPhase_Exclusion(int id);
    
    //## operation AplParamSceneColorCollectionSwitch_Exclusion(int)
    virtual void AplParamSceneColorCollectionSwitch_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_R_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_R_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_R_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_R_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P1_SUN_Exclusion(int)
    virtual void AplParamSceneColorCollection_P1_SUN_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P1_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P1_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P2_MON_Exclusion(int)
    virtual void AplParamSceneColorCollection_P2_MON_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P2_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P2_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P3_TUE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P3_TUE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P3_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P3_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_WED_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_WED_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Yl_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Yl_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P4_THU_Exclusion(int)
    virtual void AplParamSceneColorCollection_P4_THU_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P4_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P4_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P5_FRI_Exclusion(int)
    virtual void AplParamSceneColorCollection_P5_FRI_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P5_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P5_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_G_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_G_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_G_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_G_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P6_SUN_Exclusion(int)
    virtual void AplParamSceneColorCollection_P6_SUN_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P6_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P6_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Cy_MON_Exclusion(int)
    virtual void AplParamSceneColorCollection_Cy_MON_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Cy_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Cy_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P7_TUE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P7_TUE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P7_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P7_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_B_WED_Exclusion(int)
    virtual void AplParamSceneColorCollection_B_WED_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_B_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_B_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P8_THU_Exclusion(int)
    virtual void AplParamSceneColorCollection_P8_THU_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P8_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P8_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Mg_FRI_Exclusion(int)
    virtual void AplParamSceneColorCollection_Mg_FRI_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_Mg_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_Mg_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P9_SAT_Exclusion(int)
    virtual void AplParamSceneColorCollection_P9_SAT_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P9_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P9_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P10_SUN_Exclusion(int)
    virtual void AplParamSceneColorCollection_P10_SUN_Exclusion(int id);
    
    //## operation AplParamSceneColorCollection_P10_PHASE_Exclusion(int)
    virtual void AplParamSceneColorCollection_P10_PHASE_Exclusion(int id);
    
    //## operation AplParamSceneDetail_Exclusion(int)
    virtual void AplParamSceneDetail_Exclusion(int id);
    
    //## operation AplParamSceneDetailCoring_Exclusion(int)
    virtual void AplParamSceneDetailCoring_Exclusion(int id);
    
    //## operation AplParamSceneDetailFrequency_Exclusion(int)
    virtual void AplParamSceneDetailFrequency_Exclusion(int id);
    
    //## operation AplParamSceneDetailMasterLevel_Exclusion(int)
    virtual void AplParamSceneDetailMasterLevel_Exclusion(int id);
    
    //## operation AplParamSceneGammaSelect_Exclusion(int)
    virtual void AplParamSceneGammaSelect_Exclusion(int id);
    
    //## operation AplParamSceneGamutSelect_Exclusion(int)
    virtual void AplParamSceneGamutSelect_Exclusion(int id);
    
    //## operation AplParamSceneHlgKneeMode_Exclusion(int)
    virtual void AplParamSceneHlgKneeMode_Exclusion(int id);
    
    //## operation AplParamSceneHlgKneePoint_Exclusion(int)
    virtual void AplParamSceneHlgKneePoint_Exclusion(int id);
    
    //## operation AplParamSceneHlgKneeSlope_Exclusion(int)
    virtual void AplParamSceneHlgKneeSlope_Exclusion(int id);
    
    //## operation AplParamSceneHlgKneeSwitch_Exclusion(int)
    virtual void AplParamSceneHlgKneeSwitch_Exclusion(int id);
    
    //## operation AplParamSceneKneeMode_Exclusion(int)
    virtual void AplParamSceneKneeMode_Exclusion(int id);
    
    //## operation AplParamSceneKneePoint_Exclusion(int)
    virtual void AplParamSceneKneePoint_Exclusion(int id);
    
    //## operation AplParamSceneKneeSlope_Exclusion(int)
    virtual void AplParamSceneKneeSlope_Exclusion(int id);
    
    //## operation AplParamSceneKneeSwitch_Exclusion(int)
    virtual void AplParamSceneKneeSwitch_Exclusion(int id);
    
    //## operation AplParamSceneMasterGamma_Exclusion(int)
    virtual void AplParamSceneMasterGamma_Exclusion(int id);
    
    //## operation AplParamSceneMatrixSwitch_Exclusion(int)
    virtual void AplParamSceneMatrixSwitch_Exclusion(int id);
    
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
    
    //## operation AplParamSceneSkinDetail1_Exclusion(int)
    virtual void AplParamSceneSkinDetail1_Exclusion(int id);
    
    //## operation AplParamSceneSkinDetail2_Exclusion(int)
    virtual void AplParamSceneSkinDetail2_Exclusion(int id);
    
    //## operation AplParamSceneSkinDetail3_Exclusion(int)
    virtual void AplParamSceneSkinDetail3_Exclusion(int id);
    
    //## operation AplParamSceneWhiteClipLevel_Exclusion(int)
    virtual void AplParamSceneWhiteClipLevel_Exclusion(int id);
    
    //## operation AplParamSceneWhiteClipSwitch_Exclusion(int)
    virtual void AplParamSceneWhiteClipSwitch_Exclusion(int id);
    
    //## operation AplParamSDIOut_Exclusion(int)
    virtual void AplParamSDIOut_Exclusion(int id);
    
    //## operation AplParamSdiOutFormat_Exclusion(int)
    virtual void AplParamSdiOutFormat_Exclusion(int id);
    
    //## operation AplParamSdiOutIndicatorDisp_Exclusion(int)
    virtual void AplParamSdiOutIndicatorDisp_Exclusion(int id);
    
    //## operation AplParamSdiOutMarkerDisp_Exclusion(int)
    virtual void AplParamSdiOutMarkerDisp_Exclusion(int id);
    
    //## operation AplParamSdiOutMenuDisp_Exclusion(int)
    virtual void AplParamSdiOutMenuDisp_Exclusion(int id);
    
    //## operation AplParamSdiRemote_Exclusion(int)
    virtual void AplParamSdiRemote_Exclusion(int id);
    
    //## operation AplParamSdiOutSignalSelect_Exclusion(int)
    virtual void AplParamSdiOutSignalSelect_Exclusion(int id);
    
    //## operation AplParamShutterDegValue_Exclusion(int)
    virtual void AplParamShutterDegValue_Exclusion(int id);
    
    //## operation AplParamShutterDegValue1_Exclusion(int)
    virtual void AplParamShutterDegValue1_Exclusion(int id);
    
    //## operation AplParamShutterDegValueIndex_Exclusion(int)
    virtual void AplParamShutterDegValueIndex_Exclusion(int id);
    
    //## operation AplParamShutterSecValue_Exclusion(int)
    virtual void AplParamShutterSecValue_Exclusion(int id);
    
    //## operation AplParamShutterSecValue1_Exclusion(int)
    virtual void AplParamShutterSecValue1_Exclusion(int id);
    
    //## operation AplParamShutterSecValueIndex_Exclusion(int)
    virtual void AplParamShutterSecValueIndex_Exclusion(int id);
    
    //## operation AplParamSpotMeterUserSw_Exclusion(int)
    virtual void AplParamSpotMeterUserSw_Exclusion(int id);
    
    //## operation AplParamSystemMainCodec_Exclusion(int)
    virtual void AplParamSystemMainCodec_Exclusion(int id);
    
    //## operation AplParamSystemMainPixel_Exclusion(int)
    virtual void AplParamSystemMainPixel_Exclusion(int id);
    
    //## operation AplParamSystemRecMode_Exclusion(int)
    virtual void AplParamSystemRecMode_Exclusion(int id);
    
    //## operation AplParamSystemSdiRaw_Exclusion(int)
    virtual void AplParamSystemSdiRaw_Exclusion(int id);
    
    //## operation AplParamSystemSensorMode_Exclusion(int)
    virtual void AplParamSystemSensorMode_Exclusion(int id);
    
    //## operation AplParamSystemSubRec_Exclusion(int)
    virtual void AplParamSystemSubRec_Exclusion(int id);
    
    //## operation AplParamTCG_Exclusion(int)
    virtual void AplParamTCG_Exclusion(int id);
    
    //## operation AplParamTCMode_Exclusion(int)
    virtual void AplParamTCMode_Exclusion(int id);
    
    //## operation AplParamTimeStamp_Exclusion(int)
    virtual void AplParamTimeStamp_Exclusion(int id);
    
    //## operation AplParamTouchAfSw_Exclusion(int)
    virtual void AplParamTouchAfSw_Exclusion(int id);
    
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
    
    //## operation AplParamVFRMode_Exclusion(int)
    virtual void AplParamVFRMode_Exclusion(int id);
    
    //## operation AplParamVFRValue_Exclusion(int)
    virtual void AplParamVFRValue_Exclusion(int id);
    
    //## operation AplParamVFRValueIndex_Exclusion(int)
    virtual void AplParamVFRValueIndex_Exclusion(int id);
    
    //## operation AplParamVFRValueSystem_Exclusion(int)
    virtual void AplParamVFRValueSystem_Exclusion(int id);
    
    //## operation AplParamVFRValue1_Exclusion(int)
    virtual void AplParamVFRValue1_Exclusion(int id);
    
    //## operation AplParamWhiteValueTemp_Exclusion(int)
    virtual void AplParamWhiteValueTemp_Exclusion(int id);
    
    //## operation AplParamZebra_Exclusion(int)
    virtual void AplParamZebra_Exclusion(int id);
    
    //## operation AplParamAudioLevelMeterInvalid_Exclusion(int)
    virtual void AplParamAudioLevelMeterInvalid_Exclusion(int id);
    
    //## operation AplParamNativeISO_Exclusion(int)
    virtual void AplParamNativeISO_Exclusion(int id);
    
    //## operation AplParam2500BaseISO_Exclusion(int)
    virtual void AplParam2500BaseISO_Exclusion(int id);
    
    //## operation AplParam800BaseISO_Exclusion(int)
    virtual void AplParam800BaseISO_Exclusion(int id);
    
    //## operation AplParamMySecurityType_Exclusion(int)
    virtual void AplParamMySecurityType_Exclusion(int id);
    
    //## operation AplParamDhcpMode_Exclusion(int)
    virtual void AplParamDhcpMode_Exclusion(int id);
    
    //## operation AplParamWhiteValueIndex_Exclusion(int)
    virtual void AplParamWhiteValueIndex_Exclusion(int id);
    
    //## operation AplParamChannel5G_Exclusion(int)
    virtual void AplParamChannel5G_Exclusion(int id);
    
    //## operation AplParamLcdMarkerLuminance_Exclusion(int)
    virtual void AplParamLcdMarkerLuminance_Exclusion(int id);
    
    //## operation AplParamOutIndicatorCharLuminance_Exclusion(int)
    virtual void AplParamOutIndicatorCharLuminance_Exclusion(int id);
    
    //## operation AplParamOutMarkerLuminance_Exclusion(int)
    virtual void AplParamOutMarkerLuminance_Exclusion(int id);
    
    //## operation AplParamLcdIndicatorCharLuminance_Exclusion(int)
    virtual void AplParamLcdIndicatorCharLuminance_Exclusion(int id);
    
    //## operation AplParamHdmiRecRemote_Exclusion(int)
    virtual void AplParamHdmiRecRemote_Exclusion(int id);
    
    //## operation AplParamAlert_Exclusion(int)
    virtual void AplParamAlert_Exclusion(int id);
    
    //## operation AplParamWarning_Exclusion(int)
    virtual void AplParamWarning_Exclusion(int id);
    
    //## operation AplParamHdmiOutSignalSelect_Exclusion(int)
    virtual void AplParamHdmiOutSignalSelect_Exclusion(int id);
    
    //## operation AplParamOverClipSd1_Exclusion(int)
    virtual void AplParamOverClipSd1_Exclusion(int id);
    
    //## operation AplParamOverClipSd2_Exclusion(int)
    virtual void AplParamOverClipSd2_Exclusion(int id);
    
    ////    Attributes    ////

private :

    bool m_IsExecuteIdMaxForHdmiFormat;		//## attribute m_IsExecuteIdMaxForHdmiFormat
    
    bool m_IsExecuteIdMaxForSdiFormat;		//## attribute m_IsExecuteIdMaxForSdiFormat
};

#endif
