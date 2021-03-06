/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version:	7.5.1
 *  Element:			AplParamMainItemTypeFuncK519
 */


#ifndef Foundation_Manager_AplParamMainItemTypeFuncK519_H
#define Foundation_Manager_AplParamMainItemTypeFuncK519_H

#include "AplParamMainItemTypeFunc.h"
#include "AplParamService.h"
class AplDeckStatusService;

class AplIfAvs;

class AplNetworkEventService;

class AplParamMainValueCheck;

class AplParamService;

//## package Foundation::Manager

//## class AplParamMainItemTypeFuncK519
class AplParamMainItemTypeFuncK519 : public AplParamMainItemTypeFunc {
    ////    Constructors and destructors    ////
    
public :

    //## operation AplParamMainItemTypeFuncK519(AplParamMainItem,AplParamMainValueCheck)
    AplParamMainItemTypeFuncK519(AplParamService::AplParamMainItem* item, AplParamMainValueCheck& ValueCheck);
    
    virtual ~AplParamMainItemTypeFuncK519();
    
    ////    Operations    ////
    
    //## operation AplParamTopMenu_ViewType(int)
    virtual AplParamState AplParamTopMenu_ViewType(int id);
    
    //## operation AplParamPlayBackMenu_ViewType(int)
    virtual AplParamState AplParamPlayBackMenu_ViewType(int id);
    
    //## operation AplParamPlaySlot_ViewType(int)
    virtual AplParamState AplParamPlaySlot_ViewType(int id);
    
    //## operation AplParamClipMenu_ViewType(int)
    virtual AplParamState AplParamClipMenu_ViewType(int id);
    
    //## operation AplParamThumbDisplayMenu_ViewType(int)
    virtual AplParamState AplParamThumbDisplayMenu_ViewType(int id);
    
    //## operation AplParamAudioChSettingsMenu_ViewType(int)
    virtual AplParamState AplParamAudioChSettingsMenu_ViewType(int id);
    
    //## operation AplParamVideoOutLcdVfMenu_ViewType(int)
    virtual AplParamState AplParamVideoOutLcdVfMenu_ViewType(int id);
    
    //## operation AplParamSdiOutMenu_ViewType(int)
    virtual AplParamState AplParamSdiOutMenu_ViewType(int id);
    
    //## operation AplParamSdiOutFormat_ViewType(int)
    virtual AplParamState AplParamSdiOutFormat_ViewType(int id);
    
    //## operation AplParamHdmiOutMenu_ViewType(int)
    virtual AplParamState AplParamHdmiOutMenu_ViewType(int id);
    
    //## operation AplParamHdmiOutFormat_ViewType(int)
    virtual AplParamState AplParamHdmiOutFormat_ViewType(int id);
    
    //## operation AplParamLcdVfMarkerMenu_ViewType(int)
    virtual AplParamState AplParamLcdVfMarkerMenu_ViewType(int id);
    
    //## operation AplParamLcdVfEiAssistMenu_ViewType(int)
    virtual AplParamState AplParamLcdVfEiAssistMenu_ViewType(int id);
    
    //## operation AplParamRecordingMenu_ViewType(int)
    virtual AplParamState AplParamRecordingMenu_ViewType(int id);
    
    //## operation AplParamFileSplit_ViewType(int)
    virtual AplParamState AplParamFileSplit_ViewType(int id);
    
    //## operation AplParamRelayBackup_ViewType(int)
    virtual AplParamState AplParamRelayBackup_ViewType(int id);
    
    //## operation AplParamRecFunctionMenu_ViewType(int)
    virtual AplParamState AplParamRecFunctionMenu_ViewType(int id);
    
    //## operation AplParamTCUBMenu_ViewType(int)
    virtual AplParamState AplParamTCUBMenu_ViewType(int id);
    
    //## operation AplParamUsersBitMode_ViewType(int)
    virtual AplParamState AplParamUsersBitMode_ViewType(int id);
    
    //## operation AplParamSystemMenu_ViewType(int)
    virtual AplParamState AplParamSystemMenu_ViewType(int id);
    
    //## operation AplParamProxyRecFormat_ViewType(int)
    virtual AplParamState AplParamProxyRecFormat_ViewType(int id);
    
    //## operation AplParamLanguage_ViewType(int)
    virtual AplParamState AplParamLanguage_ViewType(int id);
    
    //## operation AplParamRecFormat59Hz_ViewType(int)
    virtual AplParamState AplParamRecFormat59Hz_ViewType(int id);
    
    //## operation AplParamRecFormat50Hz_ViewType(int)
    virtual AplParamState AplParamRecFormat50Hz_ViewType(int id);
    
    //## operation AplParamAudioVol_ViewType(int)
    virtual AplParamState AplParamAudioVol_ViewType(int id);
    
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
    
    //## operation AplParamUserButton10_ViewType(int)
    virtual AplParamState AplParamUserButton10_ViewType(int id);
    
    //## operation AplParamUserButton11_ViewType(int)
    virtual AplParamState AplParamUserButton11_ViewType(int id);
    
    //## operation AplParamUserButton12_ViewType(int)
    virtual AplParamState AplParamUserButton12_ViewType(int id);
    
    //## operation AplParamFileMenu_ViewType(int)
    virtual AplParamState AplParamFileMenu_ViewType(int id);
    
    //## operation AplParamSceneGammaSettingMenu_ViewType(int)
    virtual AplParamState AplParamSceneGammaSettingMenu_ViewType(int id);
    
    //## operation AplParamSceneKneeSettingMenu_ViewType(int)
    virtual AplParamState AplParamSceneKneeSettingMenu_ViewType(int id);
    
    //## operation AplParamSceneFileMenu_ViewType(int)
    virtual AplParamState AplParamSceneFileMenu_ViewType(int id);
    
    //## operation AplParamStreamingMenu_ViewType(int)
    virtual AplParamState AplParamStreamingMenu_ViewType(int id);
    
    //## operation AplParamNetworkDeviceSel_ViewType(int)
    virtual AplParamState AplParamNetworkDeviceSel_ViewType(int id);
    
    //## operation AplParamNetworkFunc_ViewType(int)
    virtual AplParamState AplParamNetworkFunc_ViewType(int id);
    
    //## operation AplParamNetworkMenu_ViewType(int)
    virtual AplParamState AplParamNetworkMenu_ViewType(int id);
    
    //## operation AplParamStreamingDataType_ViewType(int)
    virtual AplParamState AplParamStreamingDataType_ViewType(int id);
    
    //## operation AplParamNetInformationMenu_ViewType(int)
    virtual AplParamState AplParamNetInformationMenu_ViewType(int id);
    
    //## operation AplParamFTPClientMenu_ViewType(int)
    virtual AplParamState AplParamFTPClientMenu_ViewType(int id);
    
    //## operation AplParamCellularPropertyMenu_ViewType(int)
    virtual AplParamState AplParamCellularPropertyMenu_ViewType(int id);
    
    //## operation AplParamIpRemoteMenu_ViewType(int)
    virtual AplParamState AplParamIpRemoteMenu_ViewType(int id);
    
    //## operation AplParamAvOutMenu_ViewType(int)
    virtual AplParamState AplParamAvOutMenu_ViewType(int id);
    
    //## operation AplParamIndicatorMenu_ViewType(int)
    virtual AplParamState AplParamIndicatorMenu_ViewType(int id);
    
    //## operation AplParamRecFunctionMode_ViewType(int)
    virtual AplParamState AplParamRecFunctionMode_ViewType(int id);
    
    //## operation AplParamSwModeMenu_ViewType(int)
    virtual AplParamState AplParamSwModeMenu_ViewType(int id);
    
    //## operation AplParamFileSceneFileMenu_ViewType(int)
    virtual AplParamState AplParamFileSceneFileMenu_ViewType(int id);
    
    //## operation AplParamFileSetupFileMenu_ViewType(int)
    virtual AplParamState AplParamFileSetupFileMenu_ViewType(int id);
    
    //## operation AplParamOthersMenu_ViewType(int)
    virtual AplParamState AplParamOthersMenu_ViewType(int id);
    
    //## operation AplParamWlanPropertyMenu_ViewType(int)
    virtual AplParamState AplParamWlanPropertyMenu_ViewType(int id);
    
    //## operation AplParamLanDhcpModeV6_ViewType(int)
    virtual AplParamState AplParamLanDhcpModeV6_ViewType(int id);
    
    //## operation AplParamHpOut_ViewType(int)
    virtual AplParamState AplParamHpOut_ViewType(int id);
    
    //## operation AplParamLanIPv6SettingMenu_ViewType(int)
    virtual AplParamState AplParamLanIPv6SettingMenu_ViewType(int id);
    
    //## operation AplParamWLanIPv4SettingMenu_ViewType(int)
    virtual AplParamState AplParamWLanIPv4SettingMenu_ViewType(int id);
    
    //## operation AplParamLanIPv4SettingMenu_ViewType(int)
    virtual AplParamState AplParamLanIPv4SettingMenu_ViewType(int id);
    
    //## operation AplParamNdiHxMenu_ViewType(int)
    virtual AplParamState AplParamNdiHxMenu_ViewType(int id);
    
    //## operation AplParamUtilityMenu_ViewType(int)
    virtual AplParamState AplParamUtilityMenu_ViewType(int id);
    
    //## operation AplParamStreamingStart_ViewType(int)
    virtual AplParamState AplParamStreamingStart_ViewType(int id);
    
    //## operation AplParamStreamingFormat_ViewType(int)
    virtual AplParamState AplParamStreamingFormat_ViewType(int id);
    
    //## operation AplParamNdiHxStreamingFormat_ViewType(int)
    virtual AplParamState AplParamNdiHxStreamingFormat_ViewType(int id);
    
    //## operation AplParamDhcpMode_ViewType(int)
    virtual AplParamState AplParamDhcpMode_ViewType(int id);
    
    //## operation AplParamCopySelectMenu_ViewType(int)
    virtual AplParamState AplParamCopySelectMenu_ViewType(int id);
    
    //## operation AplParamCopyAllMenu_ViewType(int)
    virtual AplParamState AplParamCopyAllMenu_ViewType(int id);
    
    ////    Relations and components    ////

private :

    AplParamMainValueCheck* m_pValueCheck;
};

#endif
