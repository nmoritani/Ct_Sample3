/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version:	7.5.1
 *  Element:			AplParamMainItemTypeFuncK460
 */


#ifndef Foundation_Manager_AplParamMainItemTypeFuncK460_H
#define Foundation_Manager_AplParamMainItemTypeFuncK460_H

#include <oxf.h>
#include "AplParamMainItemTypeFunc.h"
#include "AplParamService.h"
class AplDeckStatusService;

class AplNetworkEventService;

class AplParamService;

//## package Foundation::Manager

//## class AplParamMainItemTypeFuncK460
class AplParamMainItemTypeFuncK460 : public AplParamMainItemTypeFunc {
    ////    Constructors and destructors    ////
    
public :

    //## operation AplParamMainItemTypeFuncK460(AplParamMainItem)
    AplParamMainItemTypeFuncK460(AplParamService::AplParamMainItem* item);
    
    virtual ~AplParamMainItemTypeFuncK460();
    
    ////    Operations    ////
    
    //## operation AplParam3200BaseISO_ViewType(int)
    virtual AplParamState AplParam3200BaseISO_ViewType(int id);
    
    //## operation AplParam2500BaseISO_ViewType(int)
    virtual AplParamState AplParam2500BaseISO_ViewType(int id);
    
    //## operation AplParam3GSdiOutput_ViewType(int)
    virtual AplParamState AplParam3GSdiOutput_ViewType(int id);
    
    //## operation AplParam800BaseISO_ViewType(int)
    virtual AplParamState AplParam800BaseISO_ViewType(int id);
    
    //## operation AplParamAwb_ViewType(int)
    virtual AplParamState AplParamAwb_ViewType(int id);
    
    //## operation AplParamBand_ViewType(int)
    virtual AplParamState AplParamBand_ViewType(int id);
    
    //## operation AplParamCameraSettingsMenu_ViewType(int)
    virtual AplParamState AplParamCameraSettingsMenu_ViewType(int id);
    
    //## operation AplParamChannel_ViewType(int)
    virtual AplParamState AplParamChannel_ViewType(int id);
    
    //## operation AplParamChannel5G_ViewType(int)
    virtual AplParamState AplParamChannel5G_ViewType(int id);
    
    //## operation AplParamClipMenu_ViewType(int)
    virtual AplParamState AplParamClipMenu_ViewType(int id);
    
    //## operation AplParamColorHdmiOut_ViewType(int)
    virtual AplParamState AplParamColorHdmiOut_ViewType(int id);
    
    //## operation AplParamColorLcdOut_ViewType(int)
    virtual AplParamState AplParamColorLcdOut_ViewType(int id);
    
    //## operation AplParamColorMain_ViewType(int)
    virtual AplParamState AplParamColorMain_ViewType(int id);
    
    //## operation AplParamColorSdiOut_ViewType(int)
    virtual AplParamState AplParamColorSdiOut_ViewType(int id);
    
    //## operation AplParamColorSub_ViewType(int)
    virtual AplParamState AplParamColorSub_ViewType(int id);
    
    //## operation AplParamDhcpMode_ViewType(int)
    virtual AplParamState AplParamDhcpMode_ViewType(int id);
    
    //## operation AplParamEISSwitch_ViewType(int)
    virtual AplParamState AplParamEISSwitch_ViewType(int id);
    
    //## operation AplParamEncryption_ViewType(int)
    virtual AplParamState AplParamEncryption_ViewType(int id);
    
    //## operation AplParamFileSceneFileMenu_ViewType(int)
    virtual AplParamState AplParamFileSceneFileMenu_ViewType(int id);
    
    //## operation AplParamFileSetupFileMenu_ViewType(int)
    virtual AplParamState AplParamFileSetupFileMenu_ViewType(int id);
    
    //## operation AplParamFpsMenu_ViewType(int)
    virtual AplParamState AplParamFpsMenu_ViewType(int id);
    
    //## operation AplParamGainIsoDispChg_ViewType(int)
    virtual AplParamState AplParamGainIsoDispChg_ViewType(int id);
    
    //## operation AplParamGainSelect_ViewType(int)
    virtual AplParamState AplParamGainSelect_ViewType(int id);
    
    //## operation AplParamGainSwitch_ViewType(int)
    virtual AplParamState AplParamGainSwitch_ViewType(int id);
    
    //## operation AplParamGateway_ViewType(int)
    virtual AplParamState AplParamGateway_ViewType(int id);
    
    //## operation AplParamHdmiOutFormat_ViewType(int)
    virtual AplParamState AplParamHdmiOutFormat_ViewType(int id);
    
    //## operation AplParamHdmiOutMenuDisp_ViewType(int)
    virtual AplParamState AplParamHdmiOutMenuDisp_ViewType(int id);
    
    //## operation AplParamHdmiRecRemote_ViewType(int)
    virtual AplParamState AplParamHdmiRecRemote_ViewType(int id);
    
    //## operation AplParamHdmiTcOutput_ViewType(int)
    virtual AplParamState AplParamHdmiTcOutput_ViewType(int id);
    
    //## operation AplParamISOSelect_ViewType(int)
    virtual AplParamState AplParamISOSelect_ViewType(int id);
    
    //## operation AplParamIpAddress_ViewType(int)
    virtual AplParamState AplParamIpAddress_ViewType(int id);
    
    //## operation AplParamLanguage_ViewType(int)
    virtual AplParamState AplParamLanguage_ViewType(int id);
    
    //## operation AplParamLcdEIAssistSpotMeterDisp_ViewType(int)
    virtual AplParamState AplParamLcdEIAssistSpotMeterDisp_ViewType(int id);
    
    //## operation AplParamLcdIndicatorMenu_ViewType(int)
    virtual AplParamState AplParamLcdIndicatorMenu_ViewType(int id);
    
    //## operation AplParamLcdIndicatorRecFuncMode_ViewType(int)
    virtual AplParamState AplParamLcdIndicatorRecFuncMode_ViewType(int id);
    
    //## operation AplParamLcdMarkerMenu_ViewType(int)
    virtual AplParamState AplParamLcdMarkerMenu_ViewType(int id);
    
    //## operation AplParamLimiterCH1_ViewType(int)
    virtual AplParamState AplParamLimiterCH1_ViewType(int id);
    
    //## operation AplParamLimiterCH2_ViewType(int)
    virtual AplParamState AplParamLimiterCH2_ViewType(int id);
    
    //## operation AplParamMyMacAddress_ViewType(int)
    virtual AplParamState AplParamMyMacAddress_ViewType(int id);
    
    //## operation AplParamMySecurityType_ViewType(int)
    virtual AplParamState AplParamMySecurityType_ViewType(int id);
    
    //## operation AplParamNativeISO_ViewType(int)
    virtual AplParamState AplParamNativeISO_ViewType(int id);
    
    //## operation AplParamNetworkPropertyMenu_ViewType(int)
    virtual AplParamState AplParamNetworkPropertyMenu_ViewType(int id);
    
    //## operation AplParamOutIndicatorMenu_ViewType(int)
    virtual AplParamState AplParamOutIndicatorMenu_ViewType(int id);
    
    //## operation AplParamOutIndicatorRecFuncMode_ViewType(int)
    virtual AplParamState AplParamOutIndicatorRecFuncMode_ViewType(int id);
    
    //## operation AplParamOutMarkerMenu_ViewType(int)
    virtual AplParamState AplParamOutMarkerMenu_ViewType(int id);
    
    //## operation AplParamPreRec_ViewType(int)
    virtual AplParamState AplParamPreRec_ViewType(int id);
    
    //## operation AplParamRecFunctionMode_ViewType(int)
    virtual AplParamState AplParamRecFunctionMode_ViewType(int id);
    
    //## operation AplParamRecFunctionOneShotTime_ViewType(int)
    virtual AplParamState AplParamRecFunctionOneShotTime_ViewType(int id);
    
    //## operation AplParamRecFunctionStartDelay_ViewType(int)
    virtual AplParamState AplParamRecFunctionStartDelay_ViewType(int id);
    
    //## operation AplParamRecSettingMenu_ViewType(int)
    virtual AplParamState AplParamRecSettingMenu_ViewType(int id);
    
    //## operation AplParamRelayBackup_ViewType(int)
    virtual AplParamState AplParamRelayBackup_ViewType(int id);
    
    //## operation AplParamSceneFileGammaMenu_ViewType(int)
    virtual AplParamState AplParamSceneFileGammaMenu_ViewType(int id);
    
    //## operation AplParamSceneFileHlgKneeMenu_ViewType(int)
    virtual AplParamState AplParamSceneFileHlgKneeMenu_ViewType(int id);
    
    //## operation AplParamSceneFileSettingMenu_ViewType(int)
    virtual AplParamState AplParamSceneFileSettingMenu_ViewType(int id);
    
    //## operation AplParamSceneFileWhiteClipMenu_ViewType(int)
    virtual AplParamState AplParamSceneFileWhiteClipMenu_ViewType(int id);
    
    //## operation AplParamSDIOut_ViewType(int)
    virtual AplParamState AplParamSDIOut_ViewType(int id);
    
    //## operation AplParamSdiOutFormat_ViewType(int)
    virtual AplParamState AplParamSdiOutFormat_ViewType(int id);
    
    //## operation AplParamSdiOutIndicatorDisp_ViewType(int)
    virtual AplParamState AplParamSdiOutIndicatorDisp_ViewType(int id);
    
    //## operation AplParamSdiOutMarkerDisp_ViewType(int)
    virtual AplParamState AplParamSdiOutMarkerDisp_ViewType(int id);
    
    //## operation AplParamSdiOutMenuDisp_ViewType(int)
    virtual AplParamState AplParamSdiOutMenuDisp_ViewType(int id);
    
    //## operation AplParamSdiOutSignalSelect_ViewType(int)
    virtual AplParamState AplParamSdiOutSignalSelect_ViewType(int id);
    
    //## operation AplParamSdiRemote_ViewType(int)
    virtual AplParamState AplParamSdiRemote_ViewType(int id);
    
    //## operation AplParamShutterDispChg_ViewType(int)
    virtual AplParamState AplParamShutterDispChg_ViewType(int id);
    
    //## operation AplParamShutterDegValue_ViewType(int)
    virtual AplParamState AplParamShutterDegValue_ViewType(int id);
    
    //## operation AplParamShutterMenu_ViewType(int)
    virtual AplParamState AplParamShutterMenu_ViewType(int id);
    
    //## operation AplParamShutterSecValue_ViewType(int)
    virtual AplParamState AplParamShutterSecValue_ViewType(int id);
    
    //## operation AplParamSubnet_ViewType(int)
    virtual AplParamState AplParamSubnet_ViewType(int id);
    
    //## operation AplParamSystemMainCodec_ViewType(int)
    virtual AplParamState AplParamSystemMainCodec_ViewType(int id);
    
    //## operation AplParamSystemMainPixel_ViewType(int)
    virtual AplParamState AplParamSystemMainPixel_ViewType(int id);
    
    //## operation AplParamSystemSdiRaw_ViewType(int)
    virtual AplParamState AplParamSystemSdiRaw_ViewType(int id);
    
    //## operation AplParamSystemSensorMode_ViewType(int)
    virtual AplParamState AplParamSystemSensorMode_ViewType(int id);
    
    //## operation AplParamSystemSettingsMenu_ViewType(int)
    virtual AplParamState AplParamSystemSettingsMenu_ViewType(int id);
    
    //## operation AplParamSystemSubRec_ViewType(int)
    virtual AplParamState AplParamSystemSubRec_ViewType(int id);
    
    //## operation AplParamTCG_ViewType(int)
    virtual AplParamState AplParamTCG_ViewType(int id);
    
    //## operation AplParamTCMenu_ViewType(int)
    virtual AplParamState AplParamTCMenu_ViewType(int id);
    
    //## operation AplParamTCMode_ViewType(int)
    virtual AplParamState AplParamTCMode_ViewType(int id);
    
    //## operation AplParamTimeStamp_ViewType(int)
    virtual AplParamState AplParamTimeStamp_ViewType(int id);
    
    //## operation AplParamTopMenu_ViewType(int)
    virtual AplParamState AplParamTopMenu_ViewType(int id);
    
    //## operation AplParamTouchAfSw_ViewType(int)
    virtual AplParamState AplParamTouchAfSw_ViewType(int id);
    
    //## operation AplParamUserButton1_ViewType(int)
    virtual AplParamState AplParamUserButton1_ViewType(int id);
    
    //## operation AplParamUserButton2_ViewType(int)
    virtual AplParamState AplParamUserButton2_ViewType(int id);
    
    //## operation AplParamUserButton3_ViewType(int)
    virtual AplParamState AplParamUserButton3_ViewType(int id);
    
    //## operation AplParamUserButton4_ViewType(int)
    virtual AplParamState AplParamUserButton4_ViewType(int id);
    
    //## operation AplParamUserButton5_ViewType(int)
    virtual AplParamState AplParamUserButton5_ViewType(int id);
    
    //## operation AplParamUserButton6_ViewType(int)
    virtual AplParamState AplParamUserButton6_ViewType(int id);
    
    //## operation AplParamUserButton7_ViewType(int)
    virtual AplParamState AplParamUserButton7_ViewType(int id);
    
    //## operation AplParamUserButton8_ViewType(int)
    virtual AplParamState AplParamUserButton8_ViewType(int id);
    
    //## operation AplParamUserButton9_ViewType(int)
    virtual AplParamState AplParamUserButton9_ViewType(int id);
    
    //## operation AplParamVFRMode_ViewType(int)
    virtual AplParamState AplParamVFRMode_ViewType(int id);
    
    //## operation AplParamVFRValue_ViewType(int)
    virtual AplParamState AplParamVFRValue_ViewType(int id);
    
    //## operation AplParamVFRValueIndex_ViewType(int)
    virtual AplParamState AplParamVFRValueIndex_ViewType(int id);
    
    //## operation AplParamWhiteMenu_ViewType(int)
    virtual AplParamState AplParamWhiteMenu_ViewType(int id);
    
    //## operation AplParamWhiteValueATWTemp_ViewType(int)
    virtual AplParamState AplParamWhiteValueATWTemp_ViewType(int id);
    
    //## operation AplParamWlanMacAddress_ViewType(int)
    virtual AplParamState AplParamWlanMacAddress_ViewType(int id);
    
    //## operation AplParamWLanStatus_ViewType(int)
    virtual AplParamState AplParamWLanStatus_ViewType(int id);
    
    //## operation AplParamUserAccountMenu_ViewType(int)
    virtual AplParamState AplParamUserAccountMenu_ViewType(int id);
    
    //## operation AplParamConnectionHistoryMenu_ViewType(int)
    virtual AplParamState AplParamConnectionHistoryMenu_ViewType(int id);
    
    //## operation AplParamVFRValue150_ViewType(int)
    virtual AplParamState AplParamVFRValue150_ViewType(int id);
    
    //## operation AplParamZebra_ViewType(int)
    virtual AplParamState AplParamZebra_ViewType(int id);
    
    //## operation AplParamGrade_ViewType(int)
    virtual AplParamState AplParamGrade_ViewType(int id);
    
    //## operation AplParamHdmiOutMenu_ViewType(int)
    virtual AplParamState AplParamHdmiOutMenu_ViewType(int id);
};

#endif
