/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version: 7.5.1
 *  Element:          AplParamMainItemTypeFunc
 */


#include "AplParamMainItemTypeFunc.h"
#include "AplParamService.h"
//## package Foundation::Manager

//## class AplParamMainItemTypeFunc
AplParamMainItemTypeFunc::AplParamMainItemTypeFunc(AplParamService::AplParamMainItem* item) : m_Item(NULL) {
    //#[ operation AplParamMainItemTypeFunc(AplParamMainItem)
    m_Item = item;
    //#]
}

AplParamMainItemTypeFunc::~AplParamMainItemTypeFunc() {
}

void AplParamMainItemTypeFunc::execute(int id) {
    //#[ operation execute(int)
    
    for( int i=0 ; i<AplParamIdMax ; i++ ){
    m_Item[i].mState = AplParamState_VisibleValid;
    }
    m_Item[AplParamTopMenu].mState = AplParamTopMenu_ViewType(id);
    m_Item[AplParamPlayBackMenu].mState = AplParamPlayBackMenu_ViewType(id);
    m_Item[AplParamPlaySlot].mState = AplParamPlaySlot_ViewType(id);
    m_Item[AplParamPlaySlotStateDecidion].mState = AplParamPlaySlotStateDecidion_ViewType(id);
    m_Item[AplParamSeekPosSel].mState = AplParamSeekPosSel_ViewType(id);
    m_Item[AplParamClipMenu].mState = AplParamClipMenu_ViewType(id);
    m_Item[AplParamCopyAllMenu].mState = AplParamCopyAllMenu_ViewType(id);
    m_Item[AplParamCopySelectMenu].mState = AplParamCopySelectMenu_ViewType(id);
    m_Item[AplParamThumbDisplayMenu].mState = AplParamThumbDisplayMenu_ViewType(id);
    m_Item[AplParamSwModeMenu].mState = AplParamSwModeMenu_ViewType(id);
    m_Item[AplParamGainLow].mState = AplParamGainLow_ViewType(id);
    m_Item[AplParamGainMid].mState = AplParamGainMid_ViewType(id);
    m_Item[AplParamGainHigh].mState = AplParamGainHigh_ViewType(id);
    m_Item[AplParamUserButton1].mState = AplParamUserButton1_ViewType(id);
    m_Item[AplParamUserButton2].mState = AplParamUserButton2_ViewType(id);
    m_Item[AplParamUserButton3].mState = AplParamUserButton3_ViewType(id);
    m_Item[AplParamUserButton4].mState = AplParamUserButton4_ViewType(id);
    m_Item[AplParamUserButton5].mState = AplParamUserButton5_ViewType(id);
    m_Item[AplParamUserButton6].mState = AplParamUserButton6_ViewType(id);
    m_Item[AplParamUserButton7].mState = AplParamUserButton7_ViewType(id);
    m_Item[AplParamUserButton8].mState = AplParamUserButton8_ViewType(id);
    m_Item[AplParamUserButton9].mState = AplParamUserButton9_ViewType(id);
    m_Item[AplParamUserButton10].mState = AplParamUserButton10_ViewType(id);
    m_Item[AplParamUserButton11].mState = AplParamUserButton11_ViewType(id);
    m_Item[AplParamUserButton12].mState = AplParamUserButton12_ViewType(id);
    m_Item[AplParamSceneFileMenu].mState = AplParamSceneFileMenu_ViewType(id);
    m_Item[AplParamSceneGammaSettingMenu].mState = AplParamSceneGammaSettingMenu_ViewType(id);
    m_Item[AplParamSceneKneeSettingMenu].mState = AplParamSceneKneeSettingMenu_ViewType(id);
    m_Item[AplParamAudioChSettingsMenu].mState = AplParamAudioChSettingsMenu_ViewType(id);
    m_Item[AplParamHpOut].mState = AplParamHpOut_ViewType(id);
    m_Item[AplParamVideoOutLcdVfMenu].mState = AplParamVideoOutLcdVfMenu_ViewType(id);
    m_Item[AplParamSdiOutMenu].mState = AplParamSdiOutMenu_ViewType(id);
    m_Item[AplParamSdiOutFormat].mState = AplParamSdiOutFormat_ViewType(id);
    m_Item[AplParamHdmiOutMenu].mState = AplParamHdmiOutMenu_ViewType(id);
    m_Item[AplParamHdmiOutFormat].mState = AplParamHdmiOutFormat_ViewType(id);
    m_Item[AplParamAvOutMenu].mState = AplParamAvOutMenu_ViewType(id);
    m_Item[AplParamVfDisplayMenu].mState = AplParamVfDisplayMenu_ViewType(id);
    m_Item[AplParamIndicatorMenu].mState = AplParamIndicatorMenu_ViewType(id);
    m_Item[AplParamLcdVfMarkerMenu].mState = AplParamLcdVfMarkerMenu_ViewType(id);
    m_Item[AplParamLcdVfEiAssistMenu].mState = AplParamLcdVfEiAssistMenu_ViewType(id);
    m_Item[AplParamRecordingMenu].mState = AplParamRecordingMenu_ViewType(id);
    m_Item[AplParamFileSplit].mState = AplParamFileSplit_ViewType(id);
    m_Item[AplParamRelayBackup].mState = AplParamRelayBackup_ViewType(id);
    m_Item[AplParamRecFunctionMenu].mState = AplParamRecFunctionMenu_ViewType(id);
    m_Item[AplParamRecFunctionMode].mState = AplParamRecFunctionMode_ViewType(id);
    m_Item[AplParamTCUBMenu].mState = AplParamTCUBMenu_ViewType(id);
    m_Item[AplParamUsersBitMode].mState = AplParamUsersBitMode_ViewType(id);
    m_Item[AplParamNetworkMenu].mState = AplParamNetworkMenu_ViewType(id);
    m_Item[AplParamNetworkDeviceSel].mState = AplParamNetworkDeviceSel_ViewType(id);
    m_Item[AplParamIpRemoteMenu].mState = AplParamIpRemoteMenu_ViewType(id);
    m_Item[AplParamFTPClientMenu].mState = AplParamFTPClientMenu_ViewType(id);
    m_Item[AplParamStreamingMenu].mState = AplParamStreamingMenu_ViewType(id);
    m_Item[AplParamStreamingFormat].mState = AplParamStreamingFormat_ViewType(id);
    m_Item[AplParamStreamingDataType].mState = AplParamStreamingDataType_ViewType(id);
    m_Item[AplParamStreamingStart].mState = AplParamStreamingStart_ViewType(id);
    m_Item[AplParamNdiHxMenu].mState = AplParamNdiHxMenu_ViewType(id);
    m_Item[AplParamNdiHxStreamingFormat].mState = AplParamNdiHxStreamingFormat_ViewType(id);
    m_Item[AplParamLanPropertyMenu].mState = AplParamLanPropertyMenu_ViewType(id);
    m_Item[AplParamLanMacAddress].mState = AplParamLanMacAddress_ViewType(id);
    m_Item[AplParamLanIPv4SettingMenu].mState = AplParamLanIPv4SettingMenu_ViewType(id);
    m_Item[AplParamLanDhcpMode].mState = AplParamLanDhcpMode_ViewType(id);
    m_Item[AplParamLanIpAddress].mState = AplParamLanIpAddress_ViewType(id);
    m_Item[AplParamLanSubnet].mState = AplParamLanSubnet_ViewType(id);
    m_Item[AplParamLanGateway].mState = AplParamLanGateway_ViewType(id);
    m_Item[AplParamLanIPv6SettingMenu].mState = AplParamLanIPv6SettingMenu_ViewType(id);
    m_Item[AplParamLanDhcpModeV6].mState = AplParamLanDhcpModeV6_ViewType(id);
    m_Item[AplParamWlanPropertyMenu].mState = AplParamWlanPropertyMenu_ViewType(id);
    m_Item[AplParamWlanMacAddress].mState = AplParamWlanMacAddress_ViewType(id);
    m_Item[AplParamBand].mState = AplParamBand_ViewType(id);
    m_Item[AplParamChannel].mState = AplParamChannel_ViewType(id);
    m_Item[AplParamChannel5G].mState = AplParamChannel5G_ViewType(id);
    m_Item[AplParamEncryption].mState = AplParamEncryption_ViewType(id);
    m_Item[AplParamMySecurityType].mState = AplParamMySecurityType_ViewType(id);
    m_Item[AplParamWLanIPv4SettingMenu].mState = AplParamWLanIPv4SettingMenu_ViewType(id);
    m_Item[AplParamDhcpMode].mState = AplParamDhcpMode_ViewType(id);
    m_Item[AplParamIpAddress].mState = AplParamIpAddress_ViewType(id);
    m_Item[AplParamSubnet].mState = AplParamSubnet_ViewType(id);
    m_Item[AplParamGateway].mState = AplParamGateway_ViewType(id);
    m_Item[AplParamWLanIPv6SettingMenu].mState = AplParamWLanIPv6SettingMenu_ViewType(id);
    m_Item[AplParamDhcpModeV6].mState = AplParamDhcpModeV6_ViewType(id);
    m_Item[AplParamCellularPropertyMenu].mState = AplParamCellularPropertyMenu_ViewType(id);
    m_Item[AplParamNetInformationMenu].mState = AplParamNetInformationMenu_ViewType(id);
    m_Item[AplParamUtilityMenu].mState = AplParamUtilityMenu_ViewType(id);
    m_Item[AplParamSystemMenu].mState = AplParamSystemMenu_ViewType(id);
    m_Item[AplParamRecFormat59Hz].mState = AplParamRecFormat59Hz_ViewType(id);
    m_Item[AplParamRecFormat50Hz].mState = AplParamRecFormat50Hz_ViewType(id);
    m_Item[AplParamMOVQuality59Hz].mState = AplParamMOVQuality59Hz_ViewType(id);
    m_Item[AplParamMOVQuality50Hz].mState = AplParamMOVQuality50Hz_ViewType(id);
    m_Item[AplParamProxyRecFormat].mState = AplParamProxyRecFormat_ViewType(id);
    m_Item[AplParamOthersMenu].mState = AplParamOthersMenu_ViewType(id);
    m_Item[AplParamFileMenu].mState = AplParamFileMenu_ViewType(id);
    m_Item[AplParamFileSceneFileMenu].mState = AplParamFileSceneFileMenu_ViewType(id);
    m_Item[AplParamFileSetupFileMenu].mState = AplParamFileSetupFileMenu_ViewType(id);
    m_Item[AplParamFileSetupMemFileMenu].mState = AplParamFileSetupMemFileMenu_ViewType(id);
    m_Item[AplParamInfoMacAddr].mState = AplParamInfoMacAddr_ViewType(id);
    m_Item[AplParamInfoMacAddrString].mState = AplParamInfoMacAddrString_ViewType(id);
    m_Item[AplParamLanguage].mState = AplParamLanguage_ViewType(id);
    m_Item[AplParamWLanStatus].mState = AplParamWLanStatus_ViewType(id);
    m_Item[AplParamSystemSettingsMenu].mState = AplParamSystemSettingsMenu_ViewType(id);
    m_Item[AplParamMyMacAddress].mState = AplParamMyMacAddress_ViewType(id);
    m_Item[AplParamNetworkPropertyMenu].mState = AplParamNetworkPropertyMenu_ViewType(id);
    m_Item[AplParamUserAccountMenu].mState = AplParamUserAccountMenu_ViewType(id);
    m_Item[AplParamConnectionHistoryMenu].mState = AplParamConnectionHistoryMenu_ViewType(id);
    m_Item[AplParamAudioVol].mState = AplParamAudioVol_ViewType(id);
    m_Item[AplParamNetworkFunc].mState = AplParamNetworkFunc_ViewType(id);
    
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamTopMenu_ViewType(int id) {
    //#[ operation AplParamTopMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamPlayBackMenu_ViewType(int id) {
    //#[ operation AplParamPlayBackMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamPlaySlot_ViewType(int id) {
    //#[ operation AplParamPlaySlot_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamPlaySlotStateDecidion_ViewType(int id) {
    //#[ operation AplParamPlaySlotStateDecidion_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSeekPosSel_ViewType(int id) {
    //#[ operation AplParamSeekPosSel_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamClipMenu_ViewType(int id) {
    //#[ operation AplParamClipMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamCopyAllMenu_ViewType(int id) {
    //#[ operation AplParamCopyAllMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamCopySelectMenu_ViewType(int id) {
    //#[ operation AplParamCopySelectMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamThumbDisplayMenu_ViewType(int id) {
    //#[ operation AplParamThumbDisplayMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSwModeMenu_ViewType(int id) {
    //#[ operation AplParamSwModeMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamGainLow_ViewType(int id) {
    //#[ operation AplParamGainLow_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamGainMid_ViewType(int id) {
    //#[ operation AplParamGainMid_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamGainHigh_ViewType(int id) {
    //#[ operation AplParamGainHigh_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton1_ViewType(int id) {
    //#[ operation AplParamUserButton1_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton2_ViewType(int id) {
    //#[ operation AplParamUserButton2_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton3_ViewType(int id) {
    //#[ operation AplParamUserButton3_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton4_ViewType(int id) {
    //#[ operation AplParamUserButton4_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton5_ViewType(int id) {
    //#[ operation AplParamUserButton5_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton6_ViewType(int id) {
    //#[ operation AplParamUserButton6_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton7_ViewType(int id) {
    //#[ operation AplParamUserButton7_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton8_ViewType(int id) {
    //#[ operation AplParamUserButton8_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton9_ViewType(int id) {
    //#[ operation AplParamUserButton9_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton10_ViewType(int id) {
    //#[ operation AplParamUserButton10_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton11_ViewType(int id) {
    //#[ operation AplParamUserButton11_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserButton12_ViewType(int id) {
    //#[ operation AplParamUserButton12_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSceneFileMenu_ViewType(int id) {
    //#[ operation AplParamSceneFileMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSceneGammaSettingMenu_ViewType(int id) {
    //#[ operation AplParamSceneGammaSettingMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSceneKneeSettingMenu_ViewType(int id) {
    //#[ operation AplParamSceneKneeSettingMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamAudioChSettingsMenu_ViewType(int id) {
    //#[ operation AplParamAudioChSettingsMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamHpOut_ViewType(int id) {
    //#[ operation AplParamHpOut_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamVideoOutLcdVfMenu_ViewType(int id) {
    //#[ operation AplParamVideoOutLcdVfMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSdiOutMenu_ViewType(int id) {
    //#[ operation AplParamSdiOutMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSdiOutFormat_ViewType(int id) {
    //#[ operation AplParamSdiOutFormat_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamHdmiOutMenu_ViewType(int id) {
    //#[ operation AplParamHdmiOutMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamHdmiOutFormat_ViewType(int id) {
    //#[ operation AplParamHdmiOutFormat_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamAvOutMenu_ViewType(int id) {
    //#[ operation AplParamAvOutMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamVfDisplayMenu_ViewType(int id) {
    //#[ operation AplParamVfDisplayMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamIndicatorMenu_ViewType(int id) {
    //#[ operation AplParamIndicatorMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLcdVfMarkerMenu_ViewType(int id) {
    //#[ operation AplParamLcdVfMarkerMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLcdVfEiAssistMenu_ViewType(int id) {
    //#[ operation AplParamLcdVfEiAssistMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamRecordingMenu_ViewType(int id) {
    //#[ operation AplParamRecordingMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamFileSplit_ViewType(int id) {
    //#[ operation AplParamFileSplit_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamRelayBackup_ViewType(int id) {
    //#[ operation AplParamRelayBackup_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamRecFunctionMenu_ViewType(int id) {
    //#[ operation AplParamRecFunctionMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamRecFunctionMode_ViewType(int id) {
    //#[ operation AplParamRecFunctionMode_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamTCUBMenu_ViewType(int id) {
    //#[ operation AplParamTCUBMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUsersBitMode_ViewType(int id) {
    //#[ operation AplParamUsersBitMode_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamNetworkMenu_ViewType(int id) {
    //#[ operation AplParamNetworkMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamNetworkDeviceSel_ViewType(int id) {
    //#[ operation AplParamNetworkDeviceSel_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamIpRemoteMenu_ViewType(int id) {
    //#[ operation AplParamIpRemoteMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamFTPClientMenu_ViewType(int id) {
    //#[ operation AplParamFTPClientMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamStreamingMenu_ViewType(int id) {
    //#[ operation AplParamStreamingMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamStreamingFormat_ViewType(int id) {
    //#[ operation AplParamStreamingFormat_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamStreamingDataType_ViewType(int id) {
    //#[ operation AplParamStreamingDataType_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamStreamingStart_ViewType(int id) {
    //#[ operation AplParamStreamingStart_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamNdiHxMenu_ViewType(int id) {
    //#[ operation AplParamNdiHxMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamNdiHxStreamingFormat_ViewType(int id) {
    //#[ operation AplParamNdiHxStreamingFormat_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanPropertyMenu_ViewType(int id) {
    //#[ operation AplParamLanPropertyMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanMacAddress_ViewType(int id) {
    //#[ operation AplParamLanMacAddress_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanIPv4SettingMenu_ViewType(int id) {
    //#[ operation AplParamLanIPv4SettingMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanDhcpMode_ViewType(int id) {
    //#[ operation AplParamLanDhcpMode_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanIpAddress_ViewType(int id) {
    //#[ operation AplParamLanIpAddress_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanSubnet_ViewType(int id) {
    //#[ operation AplParamLanSubnet_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanGateway_ViewType(int id) {
    //#[ operation AplParamLanGateway_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanIPv6SettingMenu_ViewType(int id) {
    //#[ operation AplParamLanIPv6SettingMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanDhcpModeV6_ViewType(int id) {
    //#[ operation AplParamLanDhcpModeV6_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamWlanPropertyMenu_ViewType(int id) {
    //#[ operation AplParamWlanPropertyMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamWlanMacAddress_ViewType(int id) {
    //#[ operation AplParamWlanMacAddress_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamBand_ViewType(int id) {
    //#[ operation AplParamBand_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamChannel_ViewType(int id) {
    //#[ operation AplParamChannel_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamChannel5G_ViewType(int id) {
    //#[ operation AplParamChannel5G_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamEncryption_ViewType(int id) {
    //#[ operation AplParamEncryption_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamMySecurityType_ViewType(int id) {
    //#[ operation AplParamMySecurityType_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamWLanIPv4SettingMenu_ViewType(int id) {
    //#[ operation AplParamWLanIPv4SettingMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamDhcpMode_ViewType(int id) {
    //#[ operation AplParamDhcpMode_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamIpAddress_ViewType(int id) {
    //#[ operation AplParamIpAddress_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSubnet_ViewType(int id) {
    //#[ operation AplParamSubnet_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamGateway_ViewType(int id) {
    //#[ operation AplParamGateway_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamWLanIPv6SettingMenu_ViewType(int id) {
    //#[ operation AplParamWLanIPv6SettingMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamDhcpModeV6_ViewType(int id) {
    //#[ operation AplParamDhcpModeV6_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamCellularPropertyMenu_ViewType(int id) {
    //#[ operation AplParamCellularPropertyMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamNetInformationMenu_ViewType(int id) {
    //#[ operation AplParamNetInformationMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUtilityMenu_ViewType(int id) {
    //#[ operation AplParamUtilityMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSystemMenu_ViewType(int id) {
    //#[ operation AplParamSystemMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamRecFormat59Hz_ViewType(int id) {
    //#[ operation AplParamRecFormat59Hz_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamRecFormat50Hz_ViewType(int id) {
    //#[ operation AplParamRecFormat50Hz_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamMOVQuality59Hz_ViewType(int id) {
    //#[ operation AplParamMOVQuality59Hz_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamMOVQuality50Hz_ViewType(int id) {
    //#[ operation AplParamMOVQuality50Hz_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamProxyRecFormat_ViewType(int id) {
    //#[ operation AplParamProxyRecFormat_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamOthersMenu_ViewType(int id) {
    //#[ operation AplParamOthersMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamFileMenu_ViewType(int id) {
    //#[ operation AplParamFileMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamFileSceneFileMenu_ViewType(int id) {
    //#[ operation AplParamFileSceneFileMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamFileSetupFileMenu_ViewType(int id) {
    //#[ operation AplParamFileSetupFileMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamFileSetupMemFileMenu_ViewType(int id) {
    //#[ operation AplParamFileSetupMemFileMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamInfoMacAddr_ViewType(int id) {
    //#[ operation AplParamInfoMacAddr_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamInfoMacAddrString_ViewType(int id) {
    //#[ operation AplParamInfoMacAddrString_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamLanguage_ViewType(int id) {
    //#[ operation AplParamLanguage_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamWLanStatus_ViewType(int id) {
    //#[ operation AplParamWLanStatus_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamSystemSettingsMenu_ViewType(int id) {
    //#[ operation AplParamSystemSettingsMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamMyMacAddress_ViewType(int id) {
    //#[ operation AplParamMyMacAddress_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamNetworkPropertyMenu_ViewType(int id) {
    //#[ operation AplParamNetworkPropertyMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamUserAccountMenu_ViewType(int id) {
    //#[ operation AplParamUserAccountMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamConnectionHistoryMenu_ViewType(int id) {
    //#[ operation AplParamConnectionHistoryMenu_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamAudioVol_ViewType(int id) {
    //#[ operation AplParamAudioVol_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFunc::AplParamNetworkFunc_ViewType(int id) {
    //#[ operation AplParamNetworkFunc_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}
