#include "CtDbgVarietyFunc.h"
#include "CtInterface.h"
#include "CtEventInterface.h"
#include "CtDbgClipManager.h"
#include "AplParamService.h"
#include "CtWindowContentsApInfo.h"
#include "CtWindowContentsUserInfo.h"
#include "CtWindowContentsFileInfo.h"
#include "CtMplDbg.h"
#include "CtDbgThumbnailFunc.h"

CtDbgVarietyFunc::CtDbgVarietyFunc()
{
}
CtDbgVarietyFunc::~CtDbgVarietyFunc()
{
}
void CtDbgVarietyFunc::varietyFunc1()
{
#if 1
	APL_PARAM_SET_DATA(AplParamIndicatorFullAuto, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicator2SlotFunc, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorStreaming, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorWlan, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorBatteryRemain, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorRecFormat, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorFps, APL_SYS_PARAM_SWITCH_OFF);

	APL_PARAM_SET_DATA(AplParamIndicatorBondingDevice, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorRecRemote, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorRecFuncMode, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorFbc, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorHdrDrs, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorOis, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorSceneFile, APL_SYS_PARAM_SWITCH_OFF);

	APL_PARAM_SET_DATA(AplParamIndicatorArea, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorAudioLevelMeter, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorGain, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorNdFilter, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorShutter, APL_SYS_PARAM_SWITCH_OFF);

	APL_PARAM_SET_DATA(AplParamIndicatorZoomFocus, APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_OFF);

	APL_PARAM_SET_DATA(AplParamLcdIndicatorSlotStatus, APL_SYS_PARAM_SWITCH_OFF);


	APL_PARAM_SET_DATA(AplParamIndicatorIris, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorWhite, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorDateTime, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorShootingMode, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorMultiManual, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorDZoom, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorIRRec, APL_SYS_PARAM_SWITCH_OFF);
	APL_PARAM_SET_DATA(AplParamIndicatorBondingDevice, APL_SYS_PARAM_SWITCH_OFF);
#else
	APL_PARAM_SET_DATA(AplParamStatusPlay, APL_SYS_PARAM_STATUS_PLAY_PLAYING);
#endif
}
void CtDbgVarietyFunc::varietyFunc2()
{
#if 1
	// €”õ
	APL_PARAM_SET_DATA_AREA(AplParamBondingDeviceStatus, (unsigned char*)"AAA", AplParamBondingDeviceStatus_Size);
	APL_PARAM_SET_DATA(AplParamAutoManualSwState, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamZoomLensValid, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamShutterSwitch, APL_SYS_PARAM_SWITCH_ON);
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamShootingMode, APL_SYS_PARAM_SHOOTING_MODE_HIGH_SENS);
	APL_PARAM_SET_DATA(AplParamNetworkDeviceSel, APL_SYS_PARAM_NETWORK_DEVICE_SEL_LAN);
	APL_PARAM_SET_DATA(AplParamBondingConnectStatus, APL_SYS_PARAM_BONDING_CONNECT_STATUS_LV0);
	dly_tsk(100);
	
	APL_PARAM_SET_DATA(AplParamBondingConnectStatus, APL_SYS_PARAM_BATTERY_REMAIN_PER_60);
	APL_PARAM_SET_DATA(AplParamBondingBatteryRemain, APL_SYS_PARAM_BATTERY_REMAIN_PER_60);
	APL_PARAM_SET_DATA(AplParamBondingError, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamSdiHdmiRecRemoteStatus, APL_SYS_PARAM_REC_REMOTE_STATUS_SDI_HDMI_RECORDING);
	APL_PARAM_SET_DATA(AplParamSdiRemote, APL_SYS_PARAM_SWITCH_ON);
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamRecFunctionMode, APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP);
	APL_PARAM_SET_DATA(AplParamRecFunctionStatus, APL_SYS_PARAM_REC_FUNC_STATE_LOOP);
	
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamSpotMeterUserSw, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamCounterMode, 3);
	APL_PARAM_SET_DATA(AplParamIrisLensValid, APL_SYS_PARAM_SWITCH_ON);
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamSlot1RecStatus, APL_SYS_PARAM_SLOT1_REC_STATUS_OFF);
	APL_PARAM_SET_DATA(AplParamSlot1CardStatus, APL_SYS_PARAM_SLOT1_CARD_STATUS_VALID);
	APL_PARAM_SET_DATA(AplParamSlot1ErrStatus, APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_ERR);
	APL_PARAM_SET_DATA(AplParamSystemRecMode, 63);
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamAutoIrisDispMode, 1);
	APL_PARAM_SET_DATA(AplParamIRRec, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamFlashBandCorrection, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamWLanStatus, APL_SYS_PARAM_WLAN_RADIO_LV4);
	APL_PARAM_SET_DATA(AplParamStreamingStatus, APL_SYS_PARAM_STREAMING_STATUS_RUN);
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamAreaMode, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamSceneDRS, APL_SYS_PARAM_SWITCH_ON);
	
	dly_tsk(100);
	
	APL_PARAM_SET_DATA(AplParamIndicatorFullAuto, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicator2SlotFunc, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorStreaming, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorWlan, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorBatteryRemain, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorRecFormat, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorFps, APL_SYS_PARAM_SWITCH_ON);
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamIndicatorBondingDevice, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorRecRemote, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorRecFuncMode, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorFbc, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorHdrDrs, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorOis, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorSceneFile, APL_SYS_PARAM_SWITCH_ON);
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamIndicatorArea, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorAudioLevelMeter, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorGain, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorNdFilter, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorShutter, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorIris, APL_SYS_PARAM_SWITCH_ON);
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamIndicatorIris, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorWhite, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorDateTime, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorShootingMode, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorMultiManual, APL_SYS_PARAM_SWITCH_ON);

	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamIndicatorZoomFocus, APL_SYS_PARAM_INDICATOR_ZOOMFOCUS_MM_FEET);
	APL_PARAM_SET_DATA(AplParamIndicatorMultiManual, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorSlotStatus, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamIndicatorBondingDevice, APL_SYS_PARAM_SWITCH_ON);
	
	dly_tsk(100);
	APL_PARAM_SET_DATA(AplParamIndicatorDZoom, APL_SYS_PARAM_SWITCH_ON);
	APL_PARAM_SET_DATA(AplParamLcdIndicatorIRRec, APL_SYS_PARAM_SWITCH_ON);
#else
	CtEventInterface::requestWindowCmd(CtEventWindow::Popup, Window_Message_INVALID);
#endif
}

void CtDbgVarietyFunc::varietyFunc3()
{
	CtDbgThumbnailFunc::getInstance()->setThumbnailClip(100);
}

void CtDbgVarietyFunc::varietyFunc4() 
{
}

void CtDbgVarietyFunc::varietyFunc5()
{
}

void CtDbgVarietyFunc::varietyFunc6() {
}

void CtDbgVarietyFunc::varietyFunc7()
{

}

void CtDbgVarietyFunc::varietyFunc8()
{
}
