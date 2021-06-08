#ifndef _APL_PARAM_H_
#define _APL_PARAM_H_

#define APL_MENU_FACTSETTING_SIZE	0x01FF
#define APL_MENU_FIRSTSETTING_SIZE	0x00DF
#define APL_SCENE_CUSTOM_PARAM_NUM	1

typedef enum AplParamEepromId{
	AplParamTopMenu,	//TOP MENU
	AplParamRecFormat,	//FILE FORMAT
	AplParamSystemRecMode,	//�R�[�f�b�N�̑g�ݍ��킹
	AplParamThumbnailMenu,	//THUMBNAIL
	AplParamPlayBackMenu,	//THUMBNAIL > PLAYBACK
	AplParamPlaySlot,	//CLIP SEL
	AplParamPlaySlotStateDecidion,	//CLIP SEL ������Ԕ���p
	AplParamResume,	//RESUME PLAY
	AplParamSeekPosSel,	//SEEK POS SEL
	AplParamClipMenu,	//THUMBNAIL > CLIP
	AplParamCopyMenu,	//THUMBNAIL > CLIP > COPY
	AplParamCopyAllMenu,	//THUMBNAIL > CLIP > COPY > ALL
	AplParamCopySelectMenu,	//THUMBNAIL > CLIP > COPY > SELECT
	AplParamThumbDisplayMenu,	//THUMBNAIL > DISPLAY
	AplParamDisplayIndicator,	//(�폜�\��)INDICATOR
	AplParamDisplayIndicatorAllHide,	//INDICATOR ALL HIDE
	AplParamDisplayIndicatorMarker,	//INDICATOR MARKER
	AplParamDisplayIndicatorTextMemo,	//INDICATOR TEXT MEMO
	AplParamDisplayIndicatorProxy,	//INDICATOR PROXY
	AplParamTextMemoInd,	//TEXT MEMO IND.
	AplParamDisplayData,	//DATA
	AplParamCameraMenu,	//CAMERA
	AplParamSwModeMenu,	//CAMERA > SW MODE
	AplParamGainLow,	//LOW GAIN
	AplParamGainMid,	//MID GAIN
	AplParamGainHigh,	//HIGH GAIN
	AplParamSuperGainSW,	//SUPER GAIN
	AplParamOisMode,	//OIS
	AplParam4AxisOis,	//HYBRID O.I.S.
	AplParamOisModePro,	//O.I.S. MODE
	AplParamATWSet,	//ATW
	AplParamATWSpeed,	//ATW SPEED
	AplParamATWRchGain,	//ATW TARGET�@R
	AplParamATWBchGain,	//ATW TARGET�@B
	AplParamWhiteBalancePreSetMode,	//W.BAL PRESET
	AplParamWbVar,	//W.BAL VAR
	AplParamHZoomSpeed,	//H.ZOOM SPEED
	AplParamIAZoom,	//I.ZOOM
	AplParamPushAfMode,	//PUSH AF MODE
	AplParamMfAutoAssist,	//MF ASSIST
	AplParamFocusMacro,	//MACRO
	AplParamMacroMode,	//MACRO MODE
	AplParamAFSpeed,	//AF SPEED
	AplParamAFRange,	//AF AREA WIDTH
	AplParamAutoIrisSpeed,	//A.IRIS SPEED
	AplParamAIrisWindow,	//A.IRIS WINDOW
	AplParamAreaFunction,	//AREA MODE
	AplParamRopControlZoomFocus,	//ZOOM/FOCUS
	AplParamIRRec,	//IR SHOOTING
	AplParamAutoSwMenu,	//CAMERA > AUTO SW
	AplParamAutoSwitchAutoIris,	//A.IRIS
	AplParamAutoSwitchAGC,	//AGC
	AplParamAgcMax,	//AGC LIMIT
	AplParamAgcPoint,	//AGC POINT
	AplParamAutoSwitchAutoShutter,	//A.SHUTTER
	AplParamAutoShutterLimit,	//A.SHUTTER LIMIT
	AplParamAutoShutterPoint,	//A.SHUTTER POINT
	AplParamAutoSwitchATW,	//ATW
	AplParamAutoSwitchAutoFocus,	//AF
	AplParamUserSwitchesMenu,	//OTHERS > USER SWITCHES
	AplParamUserButton1,	//USER1
	AplParamUserButton2,	//USER2
	AplParamUserButton3,	//USER3
	AplParamUserButton4,	//USER4
	AplParamUserButton5,	//USER5
	AplParamUserButton6,	//USER6
	AplParamUserButton7,	//USER7
	AplParamUserButton8,	//USER8
	AplParamUserButton9,	//USER9
	AplParamUserButton10,	//USER10
	AplParamUserButton11,	//USER11
	AplParamUserButton12,	//USER12
	AplParamUserButton13,	//USER13
	AplParamSceneFileMenu,	//SCENE FILE
	AplParamSceneMode,	//FILE SELECT
	AplParamSceneFileName,	//FILE NAME
	AplParamSceneVFRMode,	//VFR
	AplParamSceneVFRValue,	//FRAME RATE
	AplParamSceneVFRValue_NTSC,	//FRAME RATE 59.94Hz
	AplParamSceneVFRValue_PAL,	//FRAME RATE 50Hz
	AplParamSceneSyncScanType,	//SYNC SCAN TYPE
	AplParamSceneSyncScanSecValue,	//SYNCHRO SCAN
	AplParamSceneSyncScanSecValue_NTSC,	//SYNC SCAN TYPE=sec�A59.94Hz
	AplParamSceneSyncScanSecValue_PAL,	//SYNC SCAN TYPE=sec�A50Hz
	AplParamSceneSyncScanDegValue,	//SYNC SCAN TYPE=deg
	AplParamSceneDetailMasterLevel,	//MASTER DTL
	AplParamSceneDetailCoring,	//DTL CORING
	AplParamSceneDetailSettingMenu,	//SCENE FILE > DETAIL SETTING
	AplParamSceneDetail,	//DETAIL
	AplParamSceneVDetailLevel,	//V.DTL LEVEL
	AplParamSceneDetailFrequency,	//DETAIL FREQUENCY
	AplParamSceneDetailLevelDepend,	//LEVEL DEPEND.
	AplParamSceneDetailKneeApeLvl,	//KNEE APE LVL
	AplParamSceneDetailGainPlus,	//DTL GAIN(+)
	AplParamSceneDetailGainMinus,	//DTL GAIN(-)
	AplParamSceneSkinToneDtlA,	//SKIN TONE DTL A
	AplParamSceneSkinToneDtlB,	//SKIN TONE DTL B
	AplParamSceneSkinToneDtlC,	//SKIN TONE DTL C
	AplParamSceneSkinToneZebra,	//SKIN TONE�@ZEBRA
	AplParamSceneSkinToneDtlSettingMenu,	//SCENE FILE > SKIN TONE DTL SETTING
	AplParamSceneSkinToneDtlDetectTable,	//DETECT TABLE
	AplParamSceneSkinToneDtlEffect_A,	//(A)SKIN DTL EFFECT
	AplParamSceneSkinToneDtlICenter_A,	//(A)I CENTER
	AplParamSceneSkinToneDtlIWidth_A,	//(A)I WIDTH
	AplParamSceneSkinToneDtlQWidth_A,	//(A)Q WIDTH
	AplParamSceneSkinToneDtlQPhase_A,	//(A)Q PHASE
	AplParamSceneSkinToneDtlEffect_B,	//(B)SKIN DTL EFFECT
	AplParamSceneSkinToneDtlICenter_B,	//(B)I CENTER
	AplParamSceneSkinToneDtlIWidth_B,	//(B)I WIDTH
	AplParamSceneSkinToneDtlQWidth_B,	//(B)Q WIDTH
	AplParamSceneSkinToneDtlQPhase_B,	//(B)Q PHASE
	AplParamSceneSkinToneDtlEffect_C,	//(C)SKIN DTL EFFECT
	AplParamSceneSkinToneDtlICenter_C,	//(C)I CENTER
	AplParamSceneSkinToneDtlIWidth_C,	//(C)I WIDTH
	AplParamSceneSkinToneDtlQWidth_C,	//(C)Q WIDTH
	AplParamSceneSkinToneDtlQPhase_C,	//(C)Q PHASE
	AplParamSceneSkinToneDtlEffect,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlICenter,	//I CENTER
	AplParamSceneSkinToneDtlIWidth,	//I WIDTH
	AplParamSceneSkinToneDtlQWidth,	//Q WIDTH
	AplParamSceneSkinToneDtlQPhase,	//Q PHASE
	AplParamSceneRBGainCtrlSetMenu,	//SCENE FILE > RB GAIN CONTROL SETTING
	AplParamSceneRGainAwbPre,	//R GAIN AWB PRE
	AplParamSceneBGainAwbPre,	//B GAIN AWB PRE
	AplParamSceneRGainAwbA,	//R GAIN AWB A
	AplParamSceneBGainAwbA,	//B GAIN AWB A
	AplParamSceneRGainAwbB,	//R GAIN AWB B
	AplParamSceneBGainAwbB,	//B GAIN AWB B
	AplParamSceneAwbAGainOffSet,	//AWB A GAIN OFFSET
	AplParamSceneAwbBGainOffSet,	//AWB B GAIN OFFSET
	AplParamSceneColorTempAchSetMenu,	//SCENE FILE > COLOR TEMP Ach SETTING
	AplParamSceneAchColorTemp,	//COLOR TEMP 
	AplParamSceneAchColorTempRGain,	//R Gain
	AplParamSceneAchColorTempBGain,	//B Gain 
	AplParamSceneAchColorTempGAxis,	//G AXIS
	AplParamSceneColorTempBchSetMenu,	//SCENE FILE > COLOR TEMP Bch SETTING
	AplParamSceneBchColorTemp,	//COLOR TEMP 
	AplParamSceneBchColorTempRGain,	//R Gain
	AplParamSceneBchColorTempBGain,	//B Gain 
	AplParamSceneBchColorTempGAxis,	//G AXIS
	AplParamSceneChromaLevel,	//CHROMA LEVEL
	AplParamSceneChromaPhase,	//CHROMA PHASE
	AplParamSceneMatrix,	//MATRIX
	AplParamSceneMatrixSetMenu,	//SCENE FILE > MATRIX SETTING
	AplParamSceneMatrix_R_G,	//MATRIX R-G
	AplParamSceneMatrix_R_B,	//MATRIX R-B
	AplParamSceneMatrix_G_R,	//MATRIX G-R
	AplParamSceneMatrix_G_B,	//MATRIX G-B
	AplParamSceneMatrix_B_R,	//MATRIX B-R
	AplParamSceneMatrix_B_G,	//MATRIX B-G
	AplParamSceneColorCorrectionSetMenu,	//SCENE FILE > COLOR CORRECTION SETTING
	AplParamSceneColorCollection_R_SAT,	//R(SAT)
	AplParamSceneColorCollection_R_PHASE,	//R(PHASE)
	AplParamSceneColorCollection_R_R_Mg_SAT,	//R-R-Mg(SAT)
	AplParamSceneColorCollection_R_R_Mg_PHASE,	//R-R-Mg(PHASE)
	AplParamSceneColorCollection_R_Mg_SAT,	//R-Mg(SAT)
	AplParamSceneColorCollection_R_Mg_PHASE,	//R-Mg(PHASE)
	AplParamSceneColorCollection_Mg_SAT,	//Mg(SAT)
	AplParamSceneColorCollection_Mg_PHASE,	//Mg(PHASE)
	AplParamSceneColorCollection_Mg_B_SAT,	//Mg-B(SAT)
	AplParamSceneColorCollection_Mg_B_PHASE,	//Mg-B(PHASE)
	AplParamSceneColorCollection_B_SAT,	//B(SAT)
	AplParamSceneColorCollection_B_PHASE,	//B(PHASE)
	AplParamSceneColorCollection_B_Cy_SAT,	//B-Cy(SAT)
	AplParamSceneColorCollection_B_Cy_PHASE,	//B-Cy(PHASE)
	AplParamSceneColorCollection_Cy_SAT,	//Cy(SAT)
	AplParamSceneColorCollection_Cy_PHASE,	//Cy(PHASE)
	AplParamSceneColorCollection_Cy_G_SAT,	//Cy-G(SAT)
	AplParamSceneColorCollection_Cy_G_PHASE,	//Cy-G(PHASE)
	AplParamSceneColorCollection_G_SAT,	//G(SAT)
	AplParamSceneColorCollection_G_PHASE,	//G(PHASE)
	AplParamSceneColorCollection_G_Yl_SAT,	//G-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_PHASE,	//G-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_Yl_SAT,	//G-Yl-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_Yl_PHASE,	//G-Yl-Yl(PHASE)
	AplParamSceneColorCollection_Yl_SAT,	//Yl(SAT)
	AplParamSceneColorCollection_Yl_PHASE,	//Yl(PHASE)
	AplParamSceneColorCollection_Yl_Yl_R_SAT,	//Yl-Yl-R(SAT)
	AplParamSceneColorCollection_Yl_Yl_R_PHASE,	//Yl-Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_SAT,	//Yl-R(SAT)
	AplParamSceneColorCollection_Yl_R_PHASE,	//Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_R_SAT,	//Yl-R-R(SAT)
	AplParamSceneColorCollection_Yl_R_R_PHASE,	//Yl-R-R(PHASE)
	AplParamSceneMasterPed,	//MASTER PED
	AplParamSceneRGBBlackCtrlSetMenu,	//SCENE FILE > RGB BLACK CONTROL SETTING
	AplParamSceneBlackRPedestal,	//R PED
	AplParamSceneBlackGPedestal,	//G PED
	AplParamSceneBlackBPedestal,	//B PED
	AplParamSceneBlackPedestalOffset,	//PEDESTAL OFFSET
	AplParamSceneGammaModeSel,	//GAMMA MODE SEL
	AplParamSceneGammaSettingMenu,	//SCENE FILE > GAMMA SETTING
	AplParamSceneMasterGamma,	//MASTER GAMMA
	AplParamSceneGammaFRecDynamicLvl,	//F-REC DYNAMIC LVL
	AplParamSceneGammaFRecBlackStrLvl,	//F-REC BLACK STR LVL
	AplParamSceneGammaVRecKneeSlope,	//V-REC KNEE SLOPE
	AplParamSceneGammaVRecKneePoint,	//V-REC KNEE POINT
	AplParamSceneBlackGamma,	//BLACK GAMMA
	AplParamSceneBlackGammaRange,	//B. GAMMA RANGE
	AplParamSceneKneeSettingMenu,	//SCENE FILE > KNEE SETTING
	AplParamSceneKneeMode,	//KNEE MODE
	AplParamSceneAKneeResponse,	//A.KNEE RESPONSE
	AplParamSceneKneePoint,	//KNEE MASTER POINT
	AplParamSceneKneeSlope,	//KNEE MASTER SLOPE
	AplParamSceneHlgKneeSwitch,	//HLG KNEE SW
	AplParamSceneHlgKneePoint,	//HLG KNEE POINT
	AplParamSceneHlgKneeSlope,	//HLG KNEE SLOPE
	AplParamSceneWhiteClipSettingMenu,	//SCENE FILE > WHITE CLIP SETTING
	AplParamSceneWhiteClipSwitch,	//WHITE CLIP
	AplParamSceneWhiteClipLevel,	//WHITE CLIP LVL
	AplParamSceneDRS,	//DRS
	AplParamSceneDRSEffectDepth,	//DRS EFFECT DEPTH
	AplParamSceneDNR,	//DNR
	AplParamSceneAutoIrisLevel,	//A.IRIS LEVEL
	AplParamSceneAutoIrisLevelEffect,	//A.IRIS LEVEL EFFECT
	AplParamAudioMenu,	//AUDIO
	AplParamAudioInputMenu,	//AUDIO > INPUT SETTINGS
	AplParamMicGain1,	//INPUT1 MIC LEVEL
	AplParamMicGain2,	//INPUT2 MIC LEVEL
	AplParamLineInputCH1,	//INPUT1 LINE LEVEL
	AplParamLineInputCH2,	//INPUT2 LINE LEVEL
	AplParamAudioChSettingsMenu,	//AUDIO > REC CH SETTINGS
	AplParamCh1Adjust,	//CH1 LEVEL
	AplParamCh2Adjust,	//CH2 LEVEL
	AplParamCh3Adjust,	//CH3 LEVEL
	AplParamCh4Adjust,	//CH4 LEVEL
	AplParamCh3LevelControl,	//CH3 LEVEL CONTROL
	AplParamCh4LevelControl,	//CH4 LEVEL CONTROL
	AplParamLowCut,	//CH1 MIC LOWCUT
	AplParamLowCut2,	//CH2 MIC LOWCUT
	AplParamLowCut3,	//CH3 MIC LOWCUT
	AplParamLowCut4,	//CH4 MIC LOWCUT
	AplParamLimiterCH1,	//CH1 LIMITER
	AplParamLimiterCH2,	//CH2 LIMITER
	AplParamLimiterCH3,	//CH3 LIMITER
	AplParamLimiterCH4,	//CH4 LIMITER
	AplParamHeadRoom,	//HEAD ROOM
	AplParamAudioOutputMenu,	//AUDIO > OUTPUT SETTINGS
	AplParamHpOut,	//AUDIO OUT
	AplParamAlarmMenu,	//AUDIO > ALARM
	AplParamBatteryEndAlarm,	//BATTERY END
	AplParamMediaEndAlarm,	//MEDIA END
	AplParamWarningAlarm,	//WARNING
	AplParamVideoOutLcdVfMenu,	//VIDEO OUT/LCD/VF
	AplParamOutputSelect,	//VIDEO OUT SEL
	AplParamSdiOutMenu,	//VIDEO OUT/LCD/VF > SDI OUT
	AplParamSDIOut,	//OUTPUT SW
	AplParamSdiOutFormat,	//OUT FORMAT
	AplParam3GSdiOutput,	//3G-SDI OUT
	AplParamSdiEdh,	//SD-SDI EDH
	AplParamSdiRemote,	//SDI REC REMOTE
	AplParamSdiOutChar,	//SDI OUT CHAR
	AplParamSdiOutZebra,	//SDI OUT ZEBRA
	AplParamSdiOutHdr,	//SDI OUT HDR
	AplParamHdmiOutMenu,	//VIDEO OUT/LCD/VF > HDMI OUT
	AplParamHdmiOutFormat,	//OUT FORMAT
	AplParamHdmiTcOutput,	//HDMI TC OUT
	AplParamHdmiRecRemote,	//HDMI REC REMOTE
	AplParamHdmiOutChar,	//HDMI OUT CHAR
	AplParamHdmiOutZebra,	//HDMI OUT ZEBRA
	AplParamHdmiOutHdr,	//HDMI OUT HDR
	AplParamAvOutMenu,	//VIDEO OUT/LCD/VF > AV OUT
	AplParamAvOutput,	//OUTPUT SW
	AplParamAvOutChar,	//AV OUT CHAR
	AplParamAvOutZebra,	//AV OUT ZEBRA
	AplParamDownConvMode,	//SD DOWNCON MODE
	AplParamLcdDisplayMenu,	//VIDEO OUT/LCD/VF > LCD
	AplParamLcdBrightness,	//BRIGHTNESS
	AplParamLcdColorLevel,	//COLOR LEVEL
	AplParamLcdContrast,	//CONTRAST
	AplParamPowerLcd,	//BACK LIGHT
	AplParamSelfShoot,	//SELF SHOOT
	AplParamVfDisplayMenu,	//VIDEO OUT/LCD/VF > VF
	AplParamEvfBrightness,	//BRIGHTNESS
	AplParamEvfColorLevel,	//COLOR LEVEL
	AplParamEvfContrast,	//CONTRAST
	AplParamEvfColor,	//VF COLOR
	AplParamEyeSensorSensitivity,	//EYE SENSOR
	AplParamLcdVfOutHdr,	//LCD/VF OUT HDR
	AplParamIndicatorMenu,	//VIDEO OUT/LCD/VF > INDICATOR
	AplParamIndicatorFullAuto,	//FULL AUTO
	AplParamLcdIndicatorSlotStatus,	//SLOT1/2 STATUS
	AplParamLcdIndicator2SlotFunc,	//2 SLOTS FUNC.
	AplParamIndicatorStreaming,	//STREAMING
	AplParamLcdIndicatorWlan,	//NETWORK
	AplParamLcdIndicatorBatteryRemain,	//BATTERY REMAIN
	AplParamLcdIndicatorRecFormat,	//REC FORMAT
	AplParamLcdIndicatorFps,	//FRAME RATE
	AplParamIndicatorBondingDevice,	//BONDING DEVICE
	AplParamLcdIndicatorRecRemote,	//REC REMOTE
	AplParamLcdIndicatorRecFuncMode,	//REC MODE
	AplParamIndicatorFbc,	//FBC
	AplParamIndicatorHdrDrs,	//HDR/DRS
	AplParamIndicatorOis,	//OIS
	AplParamIndicatorSceneFile,	//SCENE FILE
	AplParamIndicatorArea,	//AREA
	AplParamLcdIndicatorAudioLevelMeter,	//AUDIO LEVEL METER
	AplParamIndicatorGain,	//GAIN
	AplParamLcdIndicatorNdFilter,	//ND FILTER
	AplParamLcdIndicatorShutter,	//SHUTTER
	AplParamIndicatorIris,	//IRIS
	AplParamIndicatorZoomFocus,	//ZOOM/FOCUS
	AplParamLcdIndicatorWhite,	//WHITE BALANCE
	AplParamIndicatorDateTime,	//DATE/TIME
	AplParamIndicatorShootingMode,	//SHOOTING MODE
	AplParamIndicatorMultiManual,	//MULTI MANUAL
	AplParamIndicatorDZoom,	//D.ZOOM
	AplParamLcdIndicatorIRRec,	//IR REC
	AplParamLcdIndicatorPlayBackStatus,	//PLAYBACK STATUS
	AplParamLcdVfMarkerMenu,	//VIDEO OUT/LCD/VF > LCD/VF MARKER
	AplParamLcdMarkerCenterMarkerType,	//CENTER MARKER
	AplParamLcdMarkerSaftyMarkerType,	//SAFETY MARK
	AplParamLcdMarkerSafetyArea,	//SAFETY AREA
	AplParamLcdMarkerFrameMarker,	//FRAME MARKER
	AplParamLcdMarkerFrameMarkerColor,	//FRAME COLOR
	AplParamLcdVfFocusAssistMenu,	//VIDEO OUT/LCD/VF > LCD/VF FOCUS ASSIST
	AplParamFocusAssist,	//FOCUS ASSIST SW
	AplParamLcdFocusExpandMode,	//EXPAND MODE
	AplParamLcdFocusExpandValue,	//EXPAND VALUE
	AplParamLcdFocusExpandPeakLevel,	//PEAKING LEVEL
	AplParamLcdFocusExpandPeakColor,	//PEAKING COLOR
	AplParamLcdFocusExpandMonocrome,	//BLACK & WHITE
	AplParamEvfDtl,	//DETAIL
	AplParamEvfPeakLevel,	//DETAIL LEVEL
	AplParamEvfPeakFreq,	//DETAIL FREQ.
	AplParamLcdVfEiAssistMenu,	//VIDEO OUT/LCD/VF > LCD/VF EI ASSIST
	AplParamZebraPro,	//ZEBRA
	AplParamZebra1Level,	//ZEBRA1 DETECT
	AplParamZebra2Level,	//ZEBRA2 DETECT
	AplParamZebra2,	//ZEBRA2
	AplParamWFMMode,	//WFM MODE
	AplParamWFMTransParence,	//WFM TRANSPARENCE
	AplParamLcdLevelGaugeMenu,	//VIDEO OUT/LCD/VF > LCD/VF LEVEL GAUGE
	AplParamBalanceLevel,	//LEVEL GAUGE
	AplParamRecordingMenu,	//RECORDING
	AplParamClipNameMenu,	//RECORDING > CLIP NAME
	AplParamCameraNumber,	//CAM INDEX
	AplParamReelCount,	//NEXT CARD COUNT
	AplParamFileSplit,	//FILE SPLIT
	AplParamRelayBackup,	//2 SLOTS FUNC.
	AplParamPreRec,	//PRE REC
	AplParamRecFunctionMenu,	//RECORDING >REC FUNCTION
	AplParamRecFunctionMode,	//REC MODE
	AplParamRecModeHold,	//REC MODE HOLD
	AplParamRecFunctionIntervalTime,	//INTERVAL TIME
	AplParamRecFunctionOneShotTime,	//ONE SHOT TIME
	AplParamRecFunctionStartDelay,	//START DELAY
	AplParamTCUBMenu,	//RECORDING >TC/UB
	AplParamTCG,	//FREE/REC RUN
	AplParamTCMode,	//DF/NDF
	AplParamUsersBitMode,	//UB MODE
	AplParamTCInOutSelect,	//TC IN/OUT SEL
	AplParamTCOutRef,	//TC OUT REF
	AplParamRecCounter,	//REC COUNTER
	AplParamTimeStamp,	//TIME STAMP
	AplParamRecMetaDataMenu,	//RECORDING >REC META DATA
	AplParamRecmetaDataRecord,	//RECORD
	AplParamRecmetaDataUserClipName,	//USER CLIP NAME
	AplParamRecmetaDataStartTextMemo,	//START TEXT MEMO
	AplParamRecmetaDataCardSerial,	//CARD SERIAL
	AplParamNetworkMenu,	//NETWORK
	AplParamNetworkDeviceSel,	//DEVICE SEL
	AplParamIpRemoteMenu,	//NETWORK >IP REMOTE
	AplParamIpRemoteEnable,	//ENABLE
	AplParamUserAccountNameInput,	//���[�U�[�A�J�E���g���̓��͒l
	AplParamUserAccountPasswordInput,	//���[�U�[�A�J�E���g�p�X���[�h�̓��͒l
	AplParamUserAccountNum,	//�o�^���[�U�[��
	AplParamIpRemotePort,	//PORT
	AplParamFTPClientMenu,	//NETWORK >FTP CLIENT
	AplParamStreamingMenu,	//NETWORK >STREAMING
	AplParamStreamingFormat,	//STREAMING FORMAT
	AplParamStreamingStartTrigger,	//START TRIGGER
	AplParamStreamingConnectionInfo,	//CONNECTION INFO.
	AplParamStreamingDataType,	//DATA TYPE
	AplParamStreamingReceiverUrl,	//RECEIVER URL 512����+�I�[
	AplParamStreamingReceiverUrlMemory,	//RECEIVER URL MEMORY 512����+�I�[
	AplParamStreamingLoadSdCard,	//LOAD (SD CARD)
	AplParamStreamingSaveSdCard,	//SAVE (SD CARD)
	AplParamStreamingClearMemory,	//CLEAR (MEMORY)
	AplParamStreamingStart,	//START
	AplParamNdiHxMenu,	//NETWORK >NDI|HX
	AplParamNdiHxActivation,	//ACTIVATION
	AplParamNdiHxStreamingFormat,	//STREAMING FORMAT
	AplParamNdiHxClearActivation,	//CLEAR ACTIVATION
	AplParamLanPropertyMenu,	//NETWORK >LAN PROPERTY
	AplParamLanMacAddress,	//LAN MAC ADDRESS
	AplParamLanIPv4SettingMenu,	//NETWORK >LAN PROPERTY >IPv4 SETTING
	AplParamLanDhcpMode,	//LAN DHCP
	AplParamLanIpAddress,	//LAN IP ADDRESS
	AplParamLanSubnet,	//LAN SUBNET MASK
	AplParamLanGateway,	//LAN DEFAULT GATEWAY
	AplParamLanDnsPrimary,	//LAN PRIMARY DNS
	AplParamLanDnsSecondary,	//LAN SECONDARY DNS
	AplParamLanDnsPrimaryUpdateDhcp,	//LAN PRIMARY DNS DHCP�Ŋ�������
	AplParamLanDnsSecondaryUpdateDhcp,	//LAN SECONDARY DNS DHCP�Ŋ�������
	AplParamLanIPv6SettingMenu,	//NETWORK >LAN PROPERTY >IPv6 SETTING
	AplParamLanEnableIPv6,	//LAN IPv6 ENABLE/DISABLE
	AplParamLanDhcpModeV6,	//LAN DHCP IPv6
	AplParamLanIpAddressV6,	//LAN IP�A�h���X(IPv6)
	AplParamLanPrefixLengthV6,	//LAN PREFIX�@LENGTH(IPv6)
	AplParamLanGatewayV6,	//LAN DEFAULT GATEWAY(IPv6)
	AplParamLanDnsPrimaryV6,	//LAN PRIMARY DNS(IPv6)
	AplParamLanDnsSecondaryV6,	//LAN SECONDARY DNS(IPv6)
	AplParamLanDnsPrimaryV6UpdateDhcp,	//LAN PRIMARY DNS(IPv6) DHCP�Ŋ�������
	AplParamLanDnsSecondaryV6UpdateDhcp,	//LAN SECONDARY DNS(IPv6) DHCP�Ŋ�������
	AplParamWlanPropertyMenu,	//NETWORK >WLAN PROPERTY
	AplParamWlanMacAddress,	//WLAN�ݒ� MAC�A�h���X
	AplParamWlanMode,	//WLAN TYPE
	AplParamSsid,	//WLAN�ݒ� SSID
	AplParamMySsid,	//WLAN�ݒ� ���@SSID
	AplParamInfraSsid,	//WLAN�ݒ� Infra��SSID
	AplParamBand,	//�o���h�ݒ�
	AplParamChannel,	//�`�����l���ݒ�
	AplParamChannel5G,	//�`�����l���ݒ�(5G)
	AplParamEncryption,	//WLAN�ݒ� �Í����
	AplParamMySecurityType,	//���@ �Í����
	AplParamInfraEncryption,	//Infra�̈Í������
	AplParamEncryptKey,	//�Í����L�[
	AplParamMySecurityPass,	//���@ �p�X���[�h
	AplParamInfraEncryptionKey,	//Infra�̈Í����L�[
	AplParamWLanIPv4SettingMenu,	//NETWORK >WLAN PROPERTY >IPv4 SETTING
	AplParamDhcpMode,	//WLAN DHCP
	AplParamDhcp,	//DHCP
	AplParamDhcp_2nd,	//DHCP 2nd
	AplParamIpAddress,	//WLAN IP �A�h���X
	AplParamIpAddressDirect,	//IP �A�h���X Direct
	AplParamIpAddress_2nd,	//IP �A�h���X 2nd
	AplParamSubnet,	//WLAN �T�u�l�b�g�}�X�N
	AplParamSubnetDirect,	//�T�u�l�b�g�}�X�N Direct
	AplParamSubnet_2nd,	//�T�u�l�b�g�}�X�N 2nd
	AplParamGateway,	//WLAN �f�t�H���g�Q�[�g�E�F�C
	AplParamGatewayDirect,	//�f�t�H���g�Q�[�g�E�F�C Direct
	AplParamGateway_2nd,	//�f�t�H���g�Q�[�g�E�F�C 2nd
	AplParamDnsPrimary,	//WLAN DNS (�v���C�}��)
	AplParamDnsPrimaryUpdateDhcp,	//WLAN DNS (�v���C�}��) DHCP�Ŋ�������
	AplParamDnsPrimaryDirect,	//DNS (�v���C�}��) Direct
	AplParamDnsPrimary_2nd,	//DNS (�v���C�}��) 2nd
	AplParamDnsSecondary,	//WLAN DNS (�Z�J���_��)
	AplParamDnsSecondaryUpdateDhcp,	//WLAN DNS (�Z�J���_��) DHCP�Ŋ�������
	AplParamDnsSecondaryDirect,	//DNS (�Z�J���_��) Direct
	AplParamDnsSecondary_2nd,	//DNS (�Z�J���_��) 2nd
	AplParamWLanIPv6SettingMenu,	//NETWORK >LAN PROPERTY >IPv6 SETTING
	AplParamEnableIPv6,	//WLAN IPv6 ENABLE/DISABLE
	AplParamEnableIPv6Direct,	//WLAN DIRECT IPv6 ENABLE/DISABLE
	AplParamEnableIPv6Infra,	//WLAN INFRA IPv6 ENABLE/DISABLE
	AplParamDhcpModeV6,	//WLAN DHCP IPv6
	AplParamDhcpV6,	//WLAN DIRECT DHCP(IPv6)
	AplParamDhcpV6Infra,	//WLAN INFRA DHCP(IPv6)
	AplParamIpAddressV6,	//WLAN IP�A�h���X(IPv6)
	AplParamIpAddressV6Direct,	//WLAN DIRECT IP�A�h���X(IPv6)
	AplParamIpAddressV6Infra,	//WLAN INFRA IP�A�h���X(IPv6)
	AplParamPrefixLengthV6,	//WLAN �v���t�B�b�N�X��(IPv6)
	AplParamPrefixLengthV6Direct,	//WLAN DIRECT �v���t�B�b�N�X��(IPv6)
	AplParamPrefixLengthV6Infra,	//WLAN INFRA �v���t�B�b�N�X��(IPv6)
	AplParamGatewayV6,	//WLAN �f�t�H���g�Q�[�g�E�F�C(IPv6)
	AplParamGatewayV6Direct,	//WLAN DIRECT �f�t�H���g�Q�[�g�E�F�C(IPv6)
	AplParamGatewayV6Infra,	//WLAN INFRA �f�t�H���g�Q�[�g�E�F�C(IPv6)
	AplParamDnsPrimaryV6,	//WLAN DNS (�v���C�}��)(IPv6)
	AplParamDnsPrimaryV6UpdateDhcp,	//WLAN DNS (�v���C�}��)(IPv6) DHCP�Ŋ�������
	AplParamDnsPrimaryV6Direct,	//WLAN DIRECT DNS (�v���C�}��)(IPv6)
	AplParamDnsPrimaryV6Infra,	//WLAN INFRA DNS (�v���C�}��)(IPv6)
	AplParamDnsSecondaryV6,	//WLAN DNS (�Z�J���_��)(IPv6)
	AplParamDnsSecondaryV6UpdateDhcp,	//WLAN DNS (�Z�J���_��)(IPv6) DHCP�Ŋ�������
	AplParamDnsSecondaryV6Direct,	//WLAN DIRECT DNS (�Z�J���_��)(IPv6)
	AplParamDnsSecondaryV6Infra,	//WLAN INFRA DNS (�Z�J���_��)(IPv6)
	AplParamCellularPropertyMenu,	//NETWORK >CELLULAR PROPERTY
	AplParamNetInformationMenu,	//NETWORK >INFORMATION
	AplParamUtilityMenu,	//NETWORK >UTILITY
	AplParamEasyIpSetting,	//UTILITY-EASY IP SETTING
	AplParamEasyIpCameraTitle,	//UTILITY-EASY IP CAMERA TITLE
	AplParamSystemMenu,	//SYSTEM
	AplParamSystemFrequency,	//FREQUENCY
	AplParamRecFormat59Hz,	//FILE FORMAT(59.94Hz)
	AplParamRecFormat50Hz,	//FILE FORMAT(50.00Hz)
	AplParamP2Quality59Hz,	//REC FORMAT(P2/59.94Hz)
	AplParamP2Quality50Hz,	//REC FORMAT(P2/50.00Hz)
	AplParamMOVQuality59Hz,	//REC FORMAT(MOV/59.94Hz)
	AplParamMOVQuality50Hz,	//REC FORMAT(MOV/50.00Hz)
	AplParamAVCHDQuality59Hz,	//REC FORMAT(AVCHD/59.94Hz)
	AplParamAVCHDQuality50Hz,	//REC FORMAT(AVCHD/50.00Hz)
	AplParamProxyRecMode,	//PROXY REC MODE
	AplParamProxyRecFormat,	//PROXY REC FORMAT
	AplParamAspectCombert,	//ASPECT
	AplParamSuperSlowRec,	//SUPER SLOW
	AplParamShootingMode,	//SHOOTING MODE
	AplParamOthersMenu,	//OTHERS
	AplParamFileMenu,	//OTHERS > FILE
	AplParamLoadSaveSlot,	//LOAD/SAVE SLOT
	AplParamFileSceneFileMenu,	//OTHERS > FILE > SCENE FILE(SD CARD)
	AplParamFileSetupFileMenu,	//OTHERS > FILE > SETUP FILE(SD CARD)
	AplParamFileSetupMemFileMenu,	//OTHERS > FILE > SETUP FILE(MEMORY)
	AplParamColorBarsMenu,	//OTHERS > COLOR BARS
	AplParamColorbarType,	//�J���[�o�[�^�C�vS1�d�l
	AplParamColorBarTestTone,	//�J���[�o�[���Ƀe�X�g�g�[�����o�͂��邩�ǂ���
	AplParamLedFanMenu,	//OTHERS > LED
	AplParamTallyLed,	//TALLY LED
	AplParamAccessLed,	//ACCESS LED
	AplParamClockMenu,	//OTHERS > CLOCK
	AplParamDateFormatMode,	//DATE FORMAT
	AplParamWTTravelArea,	//TIME ZONE
	AplParamUSBDeviceMenu,	//OTHERS > USB DEVICE
	AplParamUsbMassStorageMode,	//MASS STORAGE MODE
	AplParamUsbServiceMode,	//USB SERVICE MODE
	AplParamInformationMenu,	//OTHERS > INFORMATION
	AplParamInfoModel,	//MODEL
	AplParamInfoSerialNo,	//SERIAL NO.
	AplParamInfoMacAddr,	//MAC ADDRESS(�p�~�\��)
	AplParamInfoMacAddrString,	//MAC ADDRESS
	AplParamInfoVersion,	//VERSION
	AplParamBeSoftVer,	//BE SOFT
	AplParamCamSoftVer,	//CAM SOFT
	AplParamActSoftVer,	//ACT SOFT
	AplParamFpgaVer,	//FPGA
	AplParamInfoTotalOperation,	//OPERATION TIME
	AplParamLanguageMenu,	//OTHERS > LANGUAGE
	AplParamLanguage,	//LANGUAGE
	AplParamInitializeMenu,	//OTHERS > ALL MENU INITIALIZE
	AplParamSceneAchColorTempRGainCtrl,	//COLOR TEMP R GAIN����l Ach
	AplParamSceneAchColorTempGGainCtrl,	//COLOR TEMP B GAIN����l Ach
	AplParamSceneAchWhiteValueAWBResult,	//AWB���s���� Ach
	AplParamSceneBchColorTempRGainCtrl,	//COLOR TEMP R GAIN����l Bch
	AplParamSceneBchColorTempGGainCtrl,	//COLOR TEMP B GAIN����l Bch
	AplParamSceneBchWhiteValueAWBResult,	//AWB���s���� Bch
	AplParamSceneFileName_S1,	//FILE NAME
	AplParamSceneFileName_S2,	//FILE NAME
	AplParamSceneFileName_S3,	//FILE NAME
	AplParamSceneFileName_S4,	//FILE NAME
	AplParamSceneFileName_S5,	//FILE NAME
	AplParamSceneFileName_S6,	//FILE NAME
	AplParamSceneVFRMode_S1,	//VFR
	AplParamSceneVFRMode_S2,	//VFR
	AplParamSceneVFRMode_S3,	//VFR
	AplParamSceneVFRMode_S4,	//VFR
	AplParamSceneVFRMode_S5,	//VFR
	AplParamSceneVFRMode_S6,	//VFR
	AplParamSceneVFRValue_NTSC_S1,	//FRAME RATE 59.94Hz
	AplParamSceneVFRValue_NTSC_S2,	//FRAME RATE 59.94Hz
	AplParamSceneVFRValue_NTSC_S3,	//FRAME RATE 59.94Hz
	AplParamSceneVFRValue_NTSC_S4,	//FRAME RATE 59.94Hz
	AplParamSceneVFRValue_NTSC_S5,	//FRAME RATE 59.94Hz
	AplParamSceneVFRValue_NTSC_S6,	//FRAME RATE 59.94Hz
	AplParamSceneVFRValue_PAL_S1,	//FRAME RATE 50Hz
	AplParamSceneVFRValue_PAL_S2,	//FRAME RATE 50Hz
	AplParamSceneVFRValue_PAL_S3,	//FRAME RATE 50Hz
	AplParamSceneVFRValue_PAL_S4,	//FRAME RATE 50Hz
	AplParamSceneVFRValue_PAL_S5,	//FRAME RATE 50Hz
	AplParamSceneVFRValue_PAL_S6,	//FRAME RATE 50Hz
	AplParamSceneSyncScanType_S1,	//SYNC SCAN TYPE
	AplParamSceneSyncScanType_S2,	//SYNC SCAN TYPE
	AplParamSceneSyncScanType_S3,	//SYNC SCAN TYPE
	AplParamSceneSyncScanType_S4,	//SYNC SCAN TYPE
	AplParamSceneSyncScanType_S5,	//SYNC SCAN TYPE
	AplParamSceneSyncScanType_S6,	//SYNC SCAN TYPE
	AplParamSceneSyncScanSecValue_NTSC_S1,	//SYNC SCAN TYPE=sec�A59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S2,	//SYNC SCAN TYPE=sec�A59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S3,	//SYNC SCAN TYPE=sec�A59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S4,	//SYNC SCAN TYPE=sec�A59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S5,	//SYNC SCAN TYPE=sec�A59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S6,	//SYNC SCAN TYPE=sec�A59.94Hz
	AplParamSceneSyncScanSecValue_PAL_S1,	//SYNC SCAN TYPE=sec�A50Hz
	AplParamSceneSyncScanSecValue_PAL_S2,	//SYNC SCAN TYPE=sec�A50Hz
	AplParamSceneSyncScanSecValue_PAL_S3,	//SYNC SCAN TYPE=sec�A50Hz
	AplParamSceneSyncScanSecValue_PAL_S4,	//SYNC SCAN TYPE=sec�A50Hz
	AplParamSceneSyncScanSecValue_PAL_S5,	//SYNC SCAN TYPE=sec�A50Hz
	AplParamSceneSyncScanSecValue_PAL_S6,	//SYNC SCAN TYPE=sec�A50Hz
	AplParamSceneSyncScanDegValue_S1,	//SYNC SCAN TYPE=deg
	AplParamSceneSyncScanDegValue_S2,	//SYNC SCAN TYPE=deg
	AplParamSceneSyncScanDegValue_S3,	//SYNC SCAN TYPE=deg
	AplParamSceneSyncScanDegValue_S4,	//SYNC SCAN TYPE=deg
	AplParamSceneSyncScanDegValue_S5,	//SYNC SCAN TYPE=deg
	AplParamSceneSyncScanDegValue_S6,	//SYNC SCAN TYPE=deg
	AplParamSceneDetailMasterLevel_S1,	//MASTER DTL
	AplParamSceneDetailMasterLevel_S2,	//MASTER DTL
	AplParamSceneDetailMasterLevel_S3,	//MASTER DTL
	AplParamSceneDetailMasterLevel_S4,	//MASTER DTL
	AplParamSceneDetailMasterLevel_S5,	//MASTER DTL
	AplParamSceneDetailMasterLevel_S6,	//MASTER DTL
	AplParamSceneDetailCoring_S1,	//DTL CORING
	AplParamSceneDetailCoring_S2,	//DTL CORING
	AplParamSceneDetailCoring_S3,	//DTL CORING
	AplParamSceneDetailCoring_S4,	//DTL CORING
	AplParamSceneDetailCoring_S5,	//DTL CORING
	AplParamSceneDetailCoring_S6,	//DTL CORING
	AplParamSceneDetail_S1,	//DETAIL
	AplParamSceneDetail_S2,	//DETAIL
	AplParamSceneDetail_S3,	//DETAIL
	AplParamSceneDetail_S4,	//DETAIL
	AplParamSceneDetail_S5,	//DETAIL
	AplParamSceneDetail_S6,	//DETAIL
	AplParamSceneVDetailLevel_S1,	//V.DTL LEVEL
	AplParamSceneVDetailLevel_S2,	//V.DTL LEVEL
	AplParamSceneVDetailLevel_S3,	//V.DTL LEVEL
	AplParamSceneVDetailLevel_S4,	//V.DTL LEVEL
	AplParamSceneVDetailLevel_S5,	//V.DTL LEVEL
	AplParamSceneVDetailLevel_S6,	//V.DTL LEVEL
	AplParamSceneDetailFrequency_S1,	//DETAIL FREQUENCY
	AplParamSceneDetailFrequency_S2,	//DETAIL FREQUENCY
	AplParamSceneDetailFrequency_S3,	//DETAIL FREQUENCY
	AplParamSceneDetailFrequency_S4,	//DETAIL FREQUENCY
	AplParamSceneDetailFrequency_S5,	//DETAIL FREQUENCY
	AplParamSceneDetailFrequency_S6,	//DETAIL FREQUENCY
	AplParamSceneDetailLevelDepend_S1,	//LEVEL DEPEND.
	AplParamSceneDetailLevelDepend_S2,	//LEVEL DEPEND.
	AplParamSceneDetailLevelDepend_S3,	//LEVEL DEPEND.
	AplParamSceneDetailLevelDepend_S4,	//LEVEL DEPEND.
	AplParamSceneDetailLevelDepend_S5,	//LEVEL DEPEND.
	AplParamSceneDetailLevelDepend_S6,	//LEVEL DEPEND.
	AplParamSceneDetailKneeApeLvl_S1,	//KNEE APE LVL
	AplParamSceneDetailKneeApeLvl_S2,	//KNEE APE LVL
	AplParamSceneDetailKneeApeLvl_S3,	//KNEE APE LVL
	AplParamSceneDetailKneeApeLvl_S4,	//KNEE APE LVL
	AplParamSceneDetailKneeApeLvl_S5,	//KNEE APE LVL
	AplParamSceneDetailKneeApeLvl_S6,	//KNEE APE LVL
	AplParamSceneDetailGainPlus_S1,	//DTL GAIN(+)
	AplParamSceneDetailGainPlus_S2,	//DTL GAIN(+)
	AplParamSceneDetailGainPlus_S3,	//DTL GAIN(+)
	AplParamSceneDetailGainPlus_S4,	//DTL GAIN(+)
	AplParamSceneDetailGainPlus_S5,	//DTL GAIN(+)
	AplParamSceneDetailGainPlus_S6,	//DTL GAIN(+)
	AplParamSceneDetailGainMinus_S1,	//DTL GAIN(-)
	AplParamSceneDetailGainMinus_S2,	//DTL GAIN(-)
	AplParamSceneDetailGainMinus_S3,	//DTL GAIN(-)
	AplParamSceneDetailGainMinus_S4,	//DTL GAIN(-)
	AplParamSceneDetailGainMinus_S5,	//DTL GAIN(-)
	AplParamSceneDetailGainMinus_S6,	//DTL GAIN(-)
	AplParamSceneSkinToneDtlA_S1,	//SKIN TONE DTL A
	AplParamSceneSkinToneDtlA_S2,	//SKIN TONE DTL A
	AplParamSceneSkinToneDtlA_S3,	//SKIN TONE DTL A
	AplParamSceneSkinToneDtlA_S4,	//SKIN TONE DTL A
	AplParamSceneSkinToneDtlA_S5,	//SKIN TONE DTL A
	AplParamSceneSkinToneDtlA_S6,	//SKIN TONE DTL A
	AplParamSceneSkinToneDtlB_S1,	//SKIN TONE DTL B
	AplParamSceneSkinToneDtlB_S2,	//SKIN TONE DTL B
	AplParamSceneSkinToneDtlB_S3,	//SKIN TONE DTL B
	AplParamSceneSkinToneDtlB_S4,	//SKIN TONE DTL B
	AplParamSceneSkinToneDtlB_S5,	//SKIN TONE DTL B
	AplParamSceneSkinToneDtlB_S6,	//SKIN TONE DTL B
	AplParamSceneSkinToneDtlC_S1,	//SKIN TONE DTL C
	AplParamSceneSkinToneDtlC_S2,	//SKIN TONE DTL C
	AplParamSceneSkinToneDtlC_S3,	//SKIN TONE DTL C
	AplParamSceneSkinToneDtlC_S4,	//SKIN TONE DTL C
	AplParamSceneSkinToneDtlC_S5,	//SKIN TONE DTL C
	AplParamSceneSkinToneDtlC_S6,	//SKIN TONE DTL C
	AplParamSceneSkinToneZebra_S1,	//SKIN TONE�@ZEBRA
	AplParamSceneSkinToneZebra_S2,	//SKIN TONE�@ZEBRA
	AplParamSceneSkinToneZebra_S3,	//SKIN TONE�@ZEBRA
	AplParamSceneSkinToneZebra_S4,	//SKIN TONE�@ZEBRA
	AplParamSceneSkinToneZebra_S5,	//SKIN TONE�@ZEBRA
	AplParamSceneSkinToneZebra_S6,	//SKIN TONE�@ZEBRA
	AplParamSceneSkinToneDtlDetectTable_S1,	//DETECT TABLE
	AplParamSceneSkinToneDtlDetectTable_S2,	//DETECT TABLE
	AplParamSceneSkinToneDtlDetectTable_S3,	//DETECT TABLE
	AplParamSceneSkinToneDtlDetectTable_S4,	//DETECT TABLE
	AplParamSceneSkinToneDtlDetectTable_S5,	//DETECT TABLE
	AplParamSceneSkinToneDtlDetectTable_S6,	//DETECT TABLE
	AplParamSceneSkinToneDtlEffect_A_S1,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_A_S2,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_A_S3,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_A_S4,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_A_S5,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_A_S6,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlICenter_A_S1,	//I CENTER
	AplParamSceneSkinToneDtlICenter_A_S2,	//I CENTER
	AplParamSceneSkinToneDtlICenter_A_S3,	//I CENTER
	AplParamSceneSkinToneDtlICenter_A_S4,	//I CENTER
	AplParamSceneSkinToneDtlICenter_A_S5,	//I CENTER
	AplParamSceneSkinToneDtlICenter_A_S6,	//I CENTER
	AplParamSceneSkinToneDtlIWidth_A_S1,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_A_S2,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_A_S3,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_A_S4,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_A_S5,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_A_S6,	//I WIDTH
	AplParamSceneSkinToneDtlQWidth_A_S1,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_A_S2,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_A_S3,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_A_S4,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_A_S5,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_A_S6,	//Q WIDTH
	AplParamSceneSkinToneDtlQPhase_A_S1,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_A_S2,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_A_S3,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_A_S4,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_A_S5,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_A_S6,	//Q PHASE
	AplParamSceneSkinToneDtlEffect_B_S1,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_B_S2,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_B_S3,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_B_S4,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_B_S5,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_B_S6,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlICenter_B_S1,	//I CENTER
	AplParamSceneSkinToneDtlICenter_B_S2,	//I CENTER
	AplParamSceneSkinToneDtlICenter_B_S3,	//I CENTER
	AplParamSceneSkinToneDtlICenter_B_S4,	//I CENTER
	AplParamSceneSkinToneDtlICenter_B_S5,	//I CENTER
	AplParamSceneSkinToneDtlICenter_B_S6,	//I CENTER
	AplParamSceneSkinToneDtlIWidth_B_S1,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_B_S2,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_B_S3,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_B_S4,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_B_S5,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_B_S6,	//I WIDTH
	AplParamSceneSkinToneDtlQWidth_B_S1,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_B_S2,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_B_S3,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_B_S4,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_B_S5,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_B_S6,	//Q WIDTH
	AplParamSceneSkinToneDtlQPhase_B_S1,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_B_S2,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_B_S3,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_B_S4,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_B_S5,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_B_S6,	//Q PHASE
	AplParamSceneSkinToneDtlEffect_C_S1,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_C_S2,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_C_S3,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_C_S4,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_C_S5,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlEffect_C_S6,	//SKIN DTL EFFECT
	AplParamSceneSkinToneDtlICenter_C_S1,	//I CENTER
	AplParamSceneSkinToneDtlICenter_C_S2,	//I CENTER
	AplParamSceneSkinToneDtlICenter_C_S3,	//I CENTER
	AplParamSceneSkinToneDtlICenter_C_S4,	//I CENTER
	AplParamSceneSkinToneDtlICenter_C_S5,	//I CENTER
	AplParamSceneSkinToneDtlICenter_C_S6,	//I CENTER
	AplParamSceneSkinToneDtlIWidth_C_S1,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_C_S2,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_C_S3,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_C_S4,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_C_S5,	//I WIDTH
	AplParamSceneSkinToneDtlIWidth_C_S6,	//I WIDTH
	AplParamSceneSkinToneDtlQWidth_C_S1,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_C_S2,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_C_S3,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_C_S4,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_C_S5,	//Q WIDTH
	AplParamSceneSkinToneDtlQWidth_C_S6,	//Q WIDTH
	AplParamSceneSkinToneDtlQPhase_C_S1,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_C_S2,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_C_S3,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_C_S4,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_C_S5,	//Q PHASE
	AplParamSceneSkinToneDtlQPhase_C_S6,	//Q PHASE
	AplParamSceneRGainAwbPre_S1,	//R GAIN AWB PRE
	AplParamSceneRGainAwbPre_S2,	//R GAIN AWB PRE
	AplParamSceneRGainAwbPre_S3,	//R GAIN AWB PRE
	AplParamSceneRGainAwbPre_S4,	//R GAIN AWB PRE
	AplParamSceneRGainAwbPre_S5,	//R GAIN AWB PRE
	AplParamSceneRGainAwbPre_S6,	//R GAIN AWB PRE
	AplParamSceneBGainAwbPre_S1,	//B GAIN AWB PRE
	AplParamSceneBGainAwbPre_S2,	//B GAIN AWB PRE
	AplParamSceneBGainAwbPre_S3,	//B GAIN AWB PRE
	AplParamSceneBGainAwbPre_S4,	//B GAIN AWB PRE
	AplParamSceneBGainAwbPre_S5,	//B GAIN AWB PRE
	AplParamSceneBGainAwbPre_S6,	//B GAIN AWB PRE
	AplParamSceneRGainAwbA_S1,	//R GAIN AWB A
	AplParamSceneRGainAwbA_S2,	//R GAIN AWB A
	AplParamSceneRGainAwbA_S3,	//R GAIN AWB A
	AplParamSceneRGainAwbA_S4,	//R GAIN AWB A
	AplParamSceneRGainAwbA_S5,	//R GAIN AWB A
	AplParamSceneRGainAwbA_S6,	//R GAIN AWB A
	AplParamSceneBGainAwbA_S1,	//B GAIN AWB A
	AplParamSceneBGainAwbA_S2,	//B GAIN AWB A
	AplParamSceneBGainAwbA_S3,	//B GAIN AWB A
	AplParamSceneBGainAwbA_S4,	//B GAIN AWB A
	AplParamSceneBGainAwbA_S5,	//B GAIN AWB A
	AplParamSceneBGainAwbA_S6,	//B GAIN AWB A
	AplParamSceneRGainAwbB_S1,	//R GAIN AWB B
	AplParamSceneRGainAwbB_S2,	//R GAIN AWB B
	AplParamSceneRGainAwbB_S3,	//R GAIN AWB B
	AplParamSceneRGainAwbB_S4,	//R GAIN AWB B
	AplParamSceneRGainAwbB_S5,	//R GAIN AWB B
	AplParamSceneRGainAwbB_S6,	//R GAIN AWB B
	AplParamSceneBGainAwbB_S1,	//B GAIN AWB B
	AplParamSceneBGainAwbB_S2,	//B GAIN AWB B
	AplParamSceneBGainAwbB_S3,	//B GAIN AWB B
	AplParamSceneBGainAwbB_S4,	//B GAIN AWB B
	AplParamSceneBGainAwbB_S5,	//B GAIN AWB B
	AplParamSceneBGainAwbB_S6,	//B GAIN AWB B
	AplParamSceneAwbAGainOffSet_S1,	//AWB A GAIN OFFSET
	AplParamSceneAwbAGainOffSet_S2,	//AWB A GAIN OFFSET
	AplParamSceneAwbAGainOffSet_S3,	//AWB A GAIN OFFSET
	AplParamSceneAwbAGainOffSet_S4,	//AWB A GAIN OFFSET
	AplParamSceneAwbAGainOffSet_S5,	//AWB A GAIN OFFSET
	AplParamSceneAwbAGainOffSet_S6,	//AWB A GAIN OFFSET
	AplParamSceneAwbBGainOffSet_S1,	//AWB B GAIN OFFSET
	AplParamSceneAwbBGainOffSet_S2,	//AWB B GAIN OFFSET
	AplParamSceneAwbBGainOffSet_S3,	//AWB B GAIN OFFSET
	AplParamSceneAwbBGainOffSet_S4,	//AWB B GAIN OFFSET
	AplParamSceneAwbBGainOffSet_S5,	//AWB B GAIN OFFSET
	AplParamSceneAwbBGainOffSet_S6,	//AWB B GAIN OFFSET
	AplParamSceneAchColorTemp_S1,	//COLOR TEMP 
	AplParamSceneAchColorTemp_S2,	//COLOR TEMP 
	AplParamSceneAchColorTemp_S3,	//COLOR TEMP 
	AplParamSceneAchColorTemp_S4,	//COLOR TEMP 
	AplParamSceneAchColorTemp_S5,	//COLOR TEMP 
	AplParamSceneAchColorTemp_S6,	//COLOR TEMP 
	AplParamSceneAchColorTempRGain_S1,	//R Gain
	AplParamSceneAchColorTempRGain_S2,	//R Gain
	AplParamSceneAchColorTempRGain_S3,	//R Gain
	AplParamSceneAchColorTempRGain_S4,	//R Gain
	AplParamSceneAchColorTempRGain_S5,	//R Gain
	AplParamSceneAchColorTempRGain_S6,	//R Gain
	AplParamSceneAchColorTempBGain_S1,	//B Gain 
	AplParamSceneAchColorTempBGain_S2,	//B Gain 
	AplParamSceneAchColorTempBGain_S3,	//B Gain 
	AplParamSceneAchColorTempBGain_S4,	//B Gain 
	AplParamSceneAchColorTempBGain_S5,	//B Gain 
	AplParamSceneAchColorTempBGain_S6,	//B Gain 
	AplParamSceneAchColorTempGAxis_S1,	//G AXIS
	AplParamSceneAchColorTempGAxis_S2,	//G AXIS
	AplParamSceneAchColorTempGAxis_S3,	//G AXIS
	AplParamSceneAchColorTempGAxis_S4,	//G AXIS
	AplParamSceneAchColorTempGAxis_S5,	//G AXIS
	AplParamSceneAchColorTempGAxis_S6,	//G AXIS
	AplParamSceneBchColorTemp_S1,	//COLOR TEMP 
	AplParamSceneBchColorTemp_S2,	//COLOR TEMP 
	AplParamSceneBchColorTemp_S3,	//COLOR TEMP 
	AplParamSceneBchColorTemp_S4,	//COLOR TEMP 
	AplParamSceneBchColorTemp_S5,	//COLOR TEMP 
	AplParamSceneBchColorTemp_S6,	//COLOR TEMP 
	AplParamSceneBchColorTempRGain_S1,	//R Gain
	AplParamSceneBchColorTempRGain_S2,	//R Gain
	AplParamSceneBchColorTempRGain_S3,	//R Gain
	AplParamSceneBchColorTempRGain_S4,	//R Gain
	AplParamSceneBchColorTempRGain_S5,	//R Gain
	AplParamSceneBchColorTempRGain_S6,	//R Gain
	AplParamSceneBchColorTempBGain_S1,	//B Gain 
	AplParamSceneBchColorTempBGain_S2,	//B Gain 
	AplParamSceneBchColorTempBGain_S3,	//B Gain 
	AplParamSceneBchColorTempBGain_S4,	//B Gain 
	AplParamSceneBchColorTempBGain_S5,	//B Gain 
	AplParamSceneBchColorTempBGain_S6,	//B Gain 
	AplParamSceneBchColorTempGAxis_S1,	//G AXIS
	AplParamSceneBchColorTempGAxis_S2,	//G AXIS
	AplParamSceneBchColorTempGAxis_S3,	//G AXIS
	AplParamSceneBchColorTempGAxis_S4,	//G AXIS
	AplParamSceneBchColorTempGAxis_S5,	//G AXIS
	AplParamSceneBchColorTempGAxis_S6,	//G AXIS
	AplParamSceneChromaLevel_S1,	//CHROMA LEVEL
	AplParamSceneChromaLevel_S2,	//CHROMA LEVEL
	AplParamSceneChromaLevel_S3,	//CHROMA LEVEL
	AplParamSceneChromaLevel_S4,	//CHROMA LEVEL
	AplParamSceneChromaLevel_S5,	//CHROMA LEVEL
	AplParamSceneChromaLevel_S6,	//CHROMA LEVEL
	AplParamSceneChromaPhase_S1,	//CHROMA PHASE
	AplParamSceneChromaPhase_S2,	//CHROMA PHASE
	AplParamSceneChromaPhase_S3,	//CHROMA PHASE
	AplParamSceneChromaPhase_S4,	//CHROMA PHASE
	AplParamSceneChromaPhase_S5,	//CHROMA PHASE
	AplParamSceneChromaPhase_S6,	//CHROMA PHASE
	AplParamSceneMatrix_S1,	//MATRIX
	AplParamSceneMatrix_S2,	//MATRIX
	AplParamSceneMatrix_S3,	//MATRIX
	AplParamSceneMatrix_S4,	//MATRIX
	AplParamSceneMatrix_S5,	//MATRIX
	AplParamSceneMatrix_S6,	//MATRIX
	AplParamSceneMatrix_R_G_S1,	//MATRIX R-G
	AplParamSceneMatrix_R_G_S2,	//MATRIX R-G
	AplParamSceneMatrix_R_G_S3,	//MATRIX R-G
	AplParamSceneMatrix_R_G_S4,	//MATRIX R-G
	AplParamSceneMatrix_R_G_S5,	//MATRIX R-G
	AplParamSceneMatrix_R_G_S6,	//MATRIX R-G
	AplParamSceneMatrix_R_B_S1,	//MATRIX R-B
	AplParamSceneMatrix_R_B_S2,	//MATRIX R-B
	AplParamSceneMatrix_R_B_S3,	//MATRIX R-B
	AplParamSceneMatrix_R_B_S4,	//MATRIX R-B
	AplParamSceneMatrix_R_B_S5,	//MATRIX R-B
	AplParamSceneMatrix_R_B_S6,	//MATRIX R-B
	AplParamSceneMatrix_G_R_S1,	//MATRIX G-R
	AplParamSceneMatrix_G_R_S2,	//MATRIX G-R
	AplParamSceneMatrix_G_R_S3,	//MATRIX G-R
	AplParamSceneMatrix_G_R_S4,	//MATRIX G-R
	AplParamSceneMatrix_G_R_S5,	//MATRIX G-R
	AplParamSceneMatrix_G_R_S6,	//MATRIX G-R
	AplParamSceneMatrix_G_B_S1,	//MATRIX G-B
	AplParamSceneMatrix_G_B_S2,	//MATRIX G-B
	AplParamSceneMatrix_G_B_S3,	//MATRIX G-B
	AplParamSceneMatrix_G_B_S4,	//MATRIX G-B
	AplParamSceneMatrix_G_B_S5,	//MATRIX G-B
	AplParamSceneMatrix_G_B_S6,	//MATRIX G-B
	AplParamSceneMatrix_B_R_S1,	//MATRIX B-R
	AplParamSceneMatrix_B_R_S2,	//MATRIX B-R
	AplParamSceneMatrix_B_R_S3,	//MATRIX B-R
	AplParamSceneMatrix_B_R_S4,	//MATRIX B-R
	AplParamSceneMatrix_B_R_S5,	//MATRIX B-R
	AplParamSceneMatrix_B_R_S6,	//MATRIX B-R
	AplParamSceneMatrix_B_G_S1,	//MATRIX B-G
	AplParamSceneMatrix_B_G_S2,	//MATRIX B-G
	AplParamSceneMatrix_B_G_S3,	//MATRIX B-G
	AplParamSceneMatrix_B_G_S4,	//MATRIX B-G
	AplParamSceneMatrix_B_G_S5,	//MATRIX B-G
	AplParamSceneMatrix_B_G_S6,	//MATRIX B-G
	AplParamSceneColorCollection_R_SAT_S1,	//R(SAT)
	AplParamSceneColorCollection_R_SAT_S2,	//R(SAT)
	AplParamSceneColorCollection_R_SAT_S3,	//R(SAT)
	AplParamSceneColorCollection_R_SAT_S4,	//R(SAT)
	AplParamSceneColorCollection_R_SAT_S5,	//R(SAT)
	AplParamSceneColorCollection_R_SAT_S6,	//R(SAT)
	AplParamSceneColorCollection_R_PHASE_S1,	//R(PHASE)
	AplParamSceneColorCollection_R_PHASE_S2,	//R(PHASE)
	AplParamSceneColorCollection_R_PHASE_S3,	//R(PHASE)
	AplParamSceneColorCollection_R_PHASE_S4,	//R(PHASE)
	AplParamSceneColorCollection_R_PHASE_S5,	//R(PHASE)
	AplParamSceneColorCollection_R_PHASE_S6,	//R(PHASE)
	AplParamSceneColorCollection_R_R_Mg_SAT_S1,	//R-R-Mg(SAT)
	AplParamSceneColorCollection_R_R_Mg_SAT_S2,	//R-R-Mg(SAT)
	AplParamSceneColorCollection_R_R_Mg_SAT_S3,	//R-R-Mg(SAT)
	AplParamSceneColorCollection_R_R_Mg_SAT_S4,	//R-R-Mg(SAT)
	AplParamSceneColorCollection_R_R_Mg_SAT_S5,	//R-R-Mg(SAT)
	AplParamSceneColorCollection_R_R_Mg_SAT_S6,	//R-R-Mg(SAT)
	AplParamSceneColorCollection_R_R_Mg_PHASE_S1,	//R-R-Mg(PHASE)
	AplParamSceneColorCollection_R_R_Mg_PHASE_S2,	//R-R-Mg(PHASE)
	AplParamSceneColorCollection_R_R_Mg_PHASE_S3,	//R-R-Mg(PHASE)
	AplParamSceneColorCollection_R_R_Mg_PHASE_S4,	//R-R-Mg(PHASE)
	AplParamSceneColorCollection_R_R_Mg_PHASE_S5,	//R-R-Mg(PHASE)
	AplParamSceneColorCollection_R_R_Mg_PHASE_S6,	//R-R-Mg(PHASE)
	AplParamSceneColorCollection_R_Mg_SAT_S1,	//R-Mg(SAT)
	AplParamSceneColorCollection_R_Mg_SAT_S2,	//R-Mg(SAT)
	AplParamSceneColorCollection_R_Mg_SAT_S3,	//R-Mg(SAT)
	AplParamSceneColorCollection_R_Mg_SAT_S4,	//R-Mg(SAT)
	AplParamSceneColorCollection_R_Mg_SAT_S5,	//R-Mg(SAT)
	AplParamSceneColorCollection_R_Mg_SAT_S6,	//R-Mg(SAT)
	AplParamSceneColorCollection_R_Mg_PHASE_S1,	//R-Mg(PHASE)
	AplParamSceneColorCollection_R_Mg_PHASE_S2,	//R-Mg(PHASE)
	AplParamSceneColorCollection_R_Mg_PHASE_S3,	//R-Mg(PHASE)
	AplParamSceneColorCollection_R_Mg_PHASE_S4,	//R-Mg(PHASE)
	AplParamSceneColorCollection_R_Mg_PHASE_S5,	//R-Mg(PHASE)
	AplParamSceneColorCollection_R_Mg_PHASE_S6,	//R-Mg(PHASE)
	AplParamSceneColorCollection_Mg_SAT_S1,	//Mg(SAT)
	AplParamSceneColorCollection_Mg_SAT_S2,	//Mg(SAT)
	AplParamSceneColorCollection_Mg_SAT_S3,	//Mg(SAT)
	AplParamSceneColorCollection_Mg_SAT_S4,	//Mg(SAT)
	AplParamSceneColorCollection_Mg_SAT_S5,	//Mg(SAT)
	AplParamSceneColorCollection_Mg_SAT_S6,	//Mg(SAT)
	AplParamSceneColorCollection_Mg_PHASE_S1,	//Mg(PHASE)
	AplParamSceneColorCollection_Mg_PHASE_S2,	//Mg(PHASE)
	AplParamSceneColorCollection_Mg_PHASE_S3,	//Mg(PHASE)
	AplParamSceneColorCollection_Mg_PHASE_S4,	//Mg(PHASE)
	AplParamSceneColorCollection_Mg_PHASE_S5,	//Mg(PHASE)
	AplParamSceneColorCollection_Mg_PHASE_S6,	//Mg(PHASE)
	AplParamSceneColorCollection_Mg_B_SAT_S1,	//Mg-B(SAT)
	AplParamSceneColorCollection_Mg_B_SAT_S2,	//Mg-B(SAT)
	AplParamSceneColorCollection_Mg_B_SAT_S3,	//Mg-B(SAT)
	AplParamSceneColorCollection_Mg_B_SAT_S4,	//Mg-B(SAT)
	AplParamSceneColorCollection_Mg_B_SAT_S5,	//Mg-B(SAT)
	AplParamSceneColorCollection_Mg_B_SAT_S6,	//Mg-B(SAT)
	AplParamSceneColorCollection_Mg_B_PHASE_S1,	//Mg-B(PHASE)
	AplParamSceneColorCollection_Mg_B_PHASE_S2,	//Mg-B(PHASE)
	AplParamSceneColorCollection_Mg_B_PHASE_S3,	//Mg-B(PHASE)
	AplParamSceneColorCollection_Mg_B_PHASE_S4,	//Mg-B(PHASE)
	AplParamSceneColorCollection_Mg_B_PHASE_S5,	//Mg-B(PHASE)
	AplParamSceneColorCollection_Mg_B_PHASE_S6,	//Mg-B(PHASE)
	AplParamSceneColorCollection_B_SAT_S1,	//B(SAT)
	AplParamSceneColorCollection_B_SAT_S2,	//B(SAT)
	AplParamSceneColorCollection_B_SAT_S3,	//B(SAT)
	AplParamSceneColorCollection_B_SAT_S4,	//B(SAT)
	AplParamSceneColorCollection_B_SAT_S5,	//B(SAT)
	AplParamSceneColorCollection_B_SAT_S6,	//B(SAT)
	AplParamSceneColorCollection_B_PHASE_S1,	//B(PHASE)
	AplParamSceneColorCollection_B_PHASE_S2,	//B(PHASE)
	AplParamSceneColorCollection_B_PHASE_S3,	//B(PHASE)
	AplParamSceneColorCollection_B_PHASE_S4,	//B(PHASE)
	AplParamSceneColorCollection_B_PHASE_S5,	//B(PHASE)
	AplParamSceneColorCollection_B_PHASE_S6,	//B(PHASE)
	AplParamSceneColorCollection_B_Cy_SAT_S1,	//B-Cy(SAT)
	AplParamSceneColorCollection_B_Cy_SAT_S2,	//B-Cy(SAT)
	AplParamSceneColorCollection_B_Cy_SAT_S3,	//B-Cy(SAT)
	AplParamSceneColorCollection_B_Cy_SAT_S4,	//B-Cy(SAT)
	AplParamSceneColorCollection_B_Cy_SAT_S5,	//B-Cy(SAT)
	AplParamSceneColorCollection_B_Cy_SAT_S6,	//B-Cy(SAT)
	AplParamSceneColorCollection_B_Cy_PHASE_S1,	//B-Cy(PHASE)
	AplParamSceneColorCollection_B_Cy_PHASE_S2,	//B-Cy(PHASE)
	AplParamSceneColorCollection_B_Cy_PHASE_S3,	//B-Cy(PHASE)
	AplParamSceneColorCollection_B_Cy_PHASE_S4,	//B-Cy(PHASE)
	AplParamSceneColorCollection_B_Cy_PHASE_S5,	//B-Cy(PHASE)
	AplParamSceneColorCollection_B_Cy_PHASE_S6,	//B-Cy(PHASE)
	AplParamSceneColorCollection_Cy_SAT_S1,	//Cy(SAT)
	AplParamSceneColorCollection_Cy_SAT_S2,	//Cy(SAT)
	AplParamSceneColorCollection_Cy_SAT_S3,	//Cy(SAT)
	AplParamSceneColorCollection_Cy_SAT_S4,	//Cy(SAT)
	AplParamSceneColorCollection_Cy_SAT_S5,	//Cy(SAT)
	AplParamSceneColorCollection_Cy_SAT_S6,	//Cy(SAT)
	AplParamSceneColorCollection_Cy_PHASE_S1,	//Cy(PHASE)
	AplParamSceneColorCollection_Cy_PHASE_S2,	//Cy(PHASE)
	AplParamSceneColorCollection_Cy_PHASE_S3,	//Cy(PHASE)
	AplParamSceneColorCollection_Cy_PHASE_S4,	//Cy(PHASE)
	AplParamSceneColorCollection_Cy_PHASE_S5,	//Cy(PHASE)
	AplParamSceneColorCollection_Cy_PHASE_S6,	//Cy(PHASE)
	AplParamSceneColorCollection_Cy_G_SAT_S1,	//Cy-G(SAT)
	AplParamSceneColorCollection_Cy_G_SAT_S2,	//Cy-G(SAT)
	AplParamSceneColorCollection_Cy_G_SAT_S3,	//Cy-G(SAT)
	AplParamSceneColorCollection_Cy_G_SAT_S4,	//Cy-G(SAT)
	AplParamSceneColorCollection_Cy_G_SAT_S5,	//Cy-G(SAT)
	AplParamSceneColorCollection_Cy_G_SAT_S6,	//Cy-G(SAT)
	AplParamSceneColorCollection_Cy_G_PHASE_S1,	//Cy-G(PHASE)
	AplParamSceneColorCollection_Cy_G_PHASE_S2,	//Cy-G(PHASE)
	AplParamSceneColorCollection_Cy_G_PHASE_S3,	//Cy-G(PHASE)
	AplParamSceneColorCollection_Cy_G_PHASE_S4,	//Cy-G(PHASE)
	AplParamSceneColorCollection_Cy_G_PHASE_S5,	//Cy-G(PHASE)
	AplParamSceneColorCollection_Cy_G_PHASE_S6,	//Cy-G(PHASE)
	AplParamSceneColorCollection_G_SAT_S1,	//G(SAT)
	AplParamSceneColorCollection_G_SAT_S2,	//G(SAT)
	AplParamSceneColorCollection_G_SAT_S3,	//G(SAT)
	AplParamSceneColorCollection_G_SAT_S4,	//G(SAT)
	AplParamSceneColorCollection_G_SAT_S5,	//G(SAT)
	AplParamSceneColorCollection_G_SAT_S6,	//G(SAT)
	AplParamSceneColorCollection_G_PHASE_S1,	//G(PHASE)
	AplParamSceneColorCollection_G_PHASE_S2,	//G(PHASE)
	AplParamSceneColorCollection_G_PHASE_S3,	//G(PHASE)
	AplParamSceneColorCollection_G_PHASE_S4,	//G(PHASE)
	AplParamSceneColorCollection_G_PHASE_S5,	//G(PHASE)
	AplParamSceneColorCollection_G_PHASE_S6,	//G(PHASE)
	AplParamSceneColorCollection_G_Yl_SAT_S1,	//G-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_SAT_S2,	//G-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_SAT_S3,	//G-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_SAT_S4,	//G-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_SAT_S5,	//G-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_SAT_S6,	//G-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_PHASE_S1,	//G-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_PHASE_S2,	//G-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_PHASE_S3,	//G-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_PHASE_S4,	//G-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_PHASE_S5,	//G-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_PHASE_S6,	//G-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_Yl_SAT_S1,	//G-Yl-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_Yl_SAT_S2,	//G-Yl-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_Yl_SAT_S3,	//G-Yl-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_Yl_SAT_S4,	//G-Yl-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_Yl_SAT_S5,	//G-Yl-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_Yl_SAT_S6,	//G-Yl-Yl(SAT)
	AplParamSceneColorCollection_G_Yl_Yl_PHASE_S1,	//G-Yl-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_Yl_PHASE_S2,	//G-Yl-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_Yl_PHASE_S3,	//G-Yl-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_Yl_PHASE_S4,	//G-Yl-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_Yl_PHASE_S5,	//G-Yl-Yl(PHASE)
	AplParamSceneColorCollection_G_Yl_Yl_PHASE_S6,	//G-Yl-Yl(PHASE)
	AplParamSceneColorCollection_Yl_SAT_S1,	//Yl(SAT)
	AplParamSceneColorCollection_Yl_SAT_S2,	//Yl(SAT)
	AplParamSceneColorCollection_Yl_SAT_S3,	//Yl(SAT)
	AplParamSceneColorCollection_Yl_SAT_S4,	//Yl(SAT)
	AplParamSceneColorCollection_Yl_SAT_S5,	//Yl(SAT)
	AplParamSceneColorCollection_Yl_SAT_S6,	//Yl(SAT)
	AplParamSceneColorCollection_Yl_PHASE_S1,	//Yl(PHASE)
	AplParamSceneColorCollection_Yl_PHASE_S2,	//Yl(PHASE)
	AplParamSceneColorCollection_Yl_PHASE_S3,	//Yl(PHASE)
	AplParamSceneColorCollection_Yl_PHASE_S4,	//Yl(PHASE)
	AplParamSceneColorCollection_Yl_PHASE_S5,	//Yl(PHASE)
	AplParamSceneColorCollection_Yl_PHASE_S6,	//Yl(PHASE)
	AplParamSceneColorCollection_Yl_Yl_R_SAT_S1,	//Yl-Yl-R(SAT)
	AplParamSceneColorCollection_Yl_Yl_R_SAT_S2,	//Yl-Yl-R(SAT)
	AplParamSceneColorCollection_Yl_Yl_R_SAT_S3,	//Yl-Yl-R(SAT)
	AplParamSceneColorCollection_Yl_Yl_R_SAT_S4,	//Yl-Yl-R(SAT)
	AplParamSceneColorCollection_Yl_Yl_R_SAT_S5,	//Yl-Yl-R(SAT)
	AplParamSceneColorCollection_Yl_Yl_R_SAT_S6,	//Yl-Yl-R(SAT)
	AplParamSceneColorCollection_Yl_Yl_R_PHASE_S1,	//Yl-Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_Yl_R_PHASE_S2,	//Yl-Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_Yl_R_PHASE_S3,	//Yl-Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_Yl_R_PHASE_S4,	//Yl-Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_Yl_R_PHASE_S5,	//Yl-Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_Yl_R_PHASE_S6,	//Yl-Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_SAT_S1,	//Yl-R(SAT)
	AplParamSceneColorCollection_Yl_R_SAT_S2,	//Yl-R(SAT)
	AplParamSceneColorCollection_Yl_R_SAT_S3,	//Yl-R(SAT)
	AplParamSceneColorCollection_Yl_R_SAT_S4,	//Yl-R(SAT)
	AplParamSceneColorCollection_Yl_R_SAT_S5,	//Yl-R(SAT)
	AplParamSceneColorCollection_Yl_R_SAT_S6,	//Yl-R(SAT)
	AplParamSceneColorCollection_Yl_R_PHASE_S1,	//Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_PHASE_S2,	//Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_PHASE_S3,	//Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_PHASE_S4,	//Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_PHASE_S5,	//Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_PHASE_S6,	//Yl-R(PHASE)
	AplParamSceneColorCollection_Yl_R_R_SAT_S1,	//Yl-R-R(SAT)
	AplParamSceneColorCollection_Yl_R_R_SAT_S2,	//Yl-R-R(SAT)
	AplParamSceneColorCollection_Yl_R_R_SAT_S3,	//Yl-R-R(SAT)
	AplParamSceneColorCollection_Yl_R_R_SAT_S4,	//Yl-R-R(SAT)
	AplParamSceneColorCollection_Yl_R_R_SAT_S5,	//Yl-R-R(SAT)
	AplParamSceneColorCollection_Yl_R_R_SAT_S6,	//Yl-R-R(SAT)
	AplParamSceneColorCollection_Yl_R_R_PHASE_S1,	//Yl-R-R(PHASE)
	AplParamSceneColorCollection_Yl_R_R_PHASE_S2,	//Yl-R-R(PHASE)
	AplParamSceneColorCollection_Yl_R_R_PHASE_S3,	//Yl-R-R(PHASE)
	AplParamSceneColorCollection_Yl_R_R_PHASE_S4,	//Yl-R-R(PHASE)
	AplParamSceneColorCollection_Yl_R_R_PHASE_S5,	//Yl-R-R(PHASE)
	AplParamSceneColorCollection_Yl_R_R_PHASE_S6,	//Yl-R-R(PHASE)
	AplParamSceneMasterPed_S1,	//MASTER PED
	AplParamSceneMasterPed_S2,	//MASTER PED
	AplParamSceneMasterPed_S3,	//MASTER PED
	AplParamSceneMasterPed_S4,	//MASTER PED
	AplParamSceneMasterPed_S5,	//MASTER PED
	AplParamSceneMasterPed_S6,	//MASTER PED
	AplParamSceneBlackRPedestal_S1,	//R PED
	AplParamSceneBlackRPedestal_S2,	//R PED
	AplParamSceneBlackRPedestal_S3,	//R PED
	AplParamSceneBlackRPedestal_S4,	//R PED
	AplParamSceneBlackRPedestal_S5,	//R PED
	AplParamSceneBlackRPedestal_S6,	//R PED
	AplParamSceneBlackGPedestal_S1,	//G PED
	AplParamSceneBlackGPedestal_S2,	//G PED
	AplParamSceneBlackGPedestal_S3,	//G PED
	AplParamSceneBlackGPedestal_S4,	//G PED
	AplParamSceneBlackGPedestal_S5,	//G PED
	AplParamSceneBlackGPedestal_S6,	//G PED
	AplParamSceneBlackBPedestal_S1,	//B PED
	AplParamSceneBlackBPedestal_S2,	//B PED
	AplParamSceneBlackBPedestal_S3,	//B PED
	AplParamSceneBlackBPedestal_S4,	//B PED
	AplParamSceneBlackBPedestal_S5,	//B PED
	AplParamSceneBlackBPedestal_S6,	//B PED
	AplParamSceneBlackPedestalOffset_S1,	//PEDESTAL OFFSET
	AplParamSceneBlackPedestalOffset_S2,	//PEDESTAL OFFSET
	AplParamSceneBlackPedestalOffset_S3,	//PEDESTAL OFFSET
	AplParamSceneBlackPedestalOffset_S4,	//PEDESTAL OFFSET
	AplParamSceneBlackPedestalOffset_S5,	//PEDESTAL OFFSET
	AplParamSceneBlackPedestalOffset_S6,	//PEDESTAL OFFSET
	AplParamSceneGammaModeSel_S1,	//GAMMA MODE SEL
	AplParamSceneGammaModeSel_S2,	//GAMMA MODE SEL
	AplParamSceneGammaModeSel_S3,	//GAMMA MODE SEL
	AplParamSceneGammaModeSel_S4,	//GAMMA MODE SEL
	AplParamSceneGammaModeSel_S5,	//GAMMA MODE SEL
	AplParamSceneGammaModeSel_S6,	//GAMMA MODE SEL
	AplParamSceneMasterGamma_S1,	//MASTER GAMMA
	AplParamSceneMasterGamma_S2,	//MASTER GAMMA
	AplParamSceneMasterGamma_S3,	//MASTER GAMMA
	AplParamSceneMasterGamma_S4,	//MASTER GAMMA
	AplParamSceneMasterGamma_S5,	//MASTER GAMMA
	AplParamSceneMasterGamma_S6,	//MASTER GAMMA
	AplParamSceneGammaFRecDynamicLvl_S1,	//F-REC DYNAMIC LVL
	AplParamSceneGammaFRecDynamicLvl_S2,	//F-REC DYNAMIC LVL
	AplParamSceneGammaFRecDynamicLvl_S3,	//F-REC DYNAMIC LVL
	AplParamSceneGammaFRecDynamicLvl_S4,	//F-REC DYNAMIC LVL
	AplParamSceneGammaFRecDynamicLvl_S5,	//F-REC DYNAMIC LVL
	AplParamSceneGammaFRecDynamicLvl_S6,	//F-REC DYNAMIC LVL
	AplParamSceneGammaFRecBlackStrLvl_S1,	//F-REC BLACK STR LVL
	AplParamSceneGammaFRecBlackStrLvl_S2,	//F-REC BLACK STR LVL
	AplParamSceneGammaFRecBlackStrLvl_S3,	//F-REC BLACK STR LVL
	AplParamSceneGammaFRecBlackStrLvl_S4,	//F-REC BLACK STR LVL
	AplParamSceneGammaFRecBlackStrLvl_S5,	//F-REC BLACK STR LVL
	AplParamSceneGammaFRecBlackStrLvl_S6,	//F-REC BLACK STR LVL
	AplParamSceneGammaVRecKneeSlope_S1,	//V-REC KNEE SLOPE
	AplParamSceneGammaVRecKneeSlope_S2,	//V-REC KNEE SLOPE
	AplParamSceneGammaVRecKneeSlope_S3,	//V-REC KNEE SLOPE
	AplParamSceneGammaVRecKneeSlope_S4,	//V-REC KNEE SLOPE
	AplParamSceneGammaVRecKneeSlope_S5,	//V-REC KNEE SLOPE
	AplParamSceneGammaVRecKneeSlope_S6,	//V-REC KNEE SLOPE
	AplParamSceneGammaVRecKneePoint_S1,	//V-REC KNEE POINT
	AplParamSceneGammaVRecKneePoint_S2,	//V-REC KNEE POINT
	AplParamSceneGammaVRecKneePoint_S3,	//V-REC KNEE POINT
	AplParamSceneGammaVRecKneePoint_S4,	//V-REC KNEE POINT
	AplParamSceneGammaVRecKneePoint_S5,	//V-REC KNEE POINT
	AplParamSceneGammaVRecKneePoint_S6,	//V-REC KNEE POINT
	AplParamSceneBlackGamma_S1,	//BLACK GAMMA
	AplParamSceneBlackGamma_S2,	//BLACK GAMMA
	AplParamSceneBlackGamma_S3,	//BLACK GAMMA
	AplParamSceneBlackGamma_S4,	//BLACK GAMMA
	AplParamSceneBlackGamma_S5,	//BLACK GAMMA
	AplParamSceneBlackGamma_S6,	//BLACK GAMMA
	AplParamSceneBlackGammaRange_S1,	//B. GAMMA RANGE
	AplParamSceneBlackGammaRange_S2,	//B. GAMMA RANGE
	AplParamSceneBlackGammaRange_S3,	//B. GAMMA RANGE
	AplParamSceneBlackGammaRange_S4,	//B. GAMMA RANGE
	AplParamSceneBlackGammaRange_S5,	//B. GAMMA RANGE
	AplParamSceneBlackGammaRange_S6,	//B. GAMMA RANGE
	AplParamSceneKneeMode_S1,	//KNEE MODE
	AplParamSceneKneeMode_S2,	//KNEE MODE
	AplParamSceneKneeMode_S3,	//KNEE MODE
	AplParamSceneKneeMode_S4,	//KNEE MODE
	AplParamSceneKneeMode_S5,	//KNEE MODE
	AplParamSceneKneeMode_S6,	//KNEE MODE
	AplParamSceneAKneeResponse_S1,	//A.KNEE RESPONSE
	AplParamSceneAKneeResponse_S2,	//A.KNEE RESPONSE
	AplParamSceneAKneeResponse_S3,	//A.KNEE RESPONSE
	AplParamSceneAKneeResponse_S4,	//A.KNEE RESPONSE
	AplParamSceneAKneeResponse_S5,	//A.KNEE RESPONSE
	AplParamSceneAKneeResponse_S6,	//A.KNEE RESPONSE
	AplParamSceneKneePoint_S1,	//KNEE MASTER POINT
	AplParamSceneKneePoint_S2,	//KNEE MASTER POINT
	AplParamSceneKneePoint_S3,	//KNEE MASTER POINT
	AplParamSceneKneePoint_S4,	//KNEE MASTER POINT
	AplParamSceneKneePoint_S5,	//KNEE MASTER POINT
	AplParamSceneKneePoint_S6,	//KNEE MASTER POINT
	AplParamSceneKneeSlope_S1,	//KNEE MASTER SLOPE
	AplParamSceneKneeSlope_S2,	//KNEE MASTER SLOPE
	AplParamSceneKneeSlope_S3,	//KNEE MASTER SLOPE
	AplParamSceneKneeSlope_S4,	//KNEE MASTER SLOPE
	AplParamSceneKneeSlope_S5,	//KNEE MASTER SLOPE
	AplParamSceneKneeSlope_S6,	//KNEE MASTER SLOPE
	AplParamSceneHlgKneeSwitch_S1,	//HLG KNEE SW
	AplParamSceneHlgKneeSwitch_S2,	//HLG KNEE SW
	AplParamSceneHlgKneeSwitch_S3,	//HLG KNEE SW
	AplParamSceneHlgKneeSwitch_S4,	//HLG KNEE SW
	AplParamSceneHlgKneeSwitch_S5,	//HLG KNEE SW
	AplParamSceneHlgKneeSwitch_S6,	//HLG KNEE SW
	AplParamSceneHlgKneePoint_S1,	//HLG KNEE POINT
	AplParamSceneHlgKneePoint_S2,	//HLG KNEE POINT
	AplParamSceneHlgKneePoint_S3,	//HLG KNEE POINT
	AplParamSceneHlgKneePoint_S4,	//HLG KNEE POINT
	AplParamSceneHlgKneePoint_S5,	//HLG KNEE POINT
	AplParamSceneHlgKneePoint_S6,	//HLG KNEE POINT
	AplParamSceneHlgKneeSlope_S1,	//HLG KNEE SLOPE
	AplParamSceneHlgKneeSlope_S2,	//HLG KNEE SLOPE
	AplParamSceneHlgKneeSlope_S3,	//HLG KNEE SLOPE
	AplParamSceneHlgKneeSlope_S4,	//HLG KNEE SLOPE
	AplParamSceneHlgKneeSlope_S5,	//HLG KNEE SLOPE
	AplParamSceneHlgKneeSlope_S6,	//HLG KNEE SLOPE
	AplParamSceneWhiteClipSwitch_S1,	//WHITE CLIP
	AplParamSceneWhiteClipSwitch_S2,	//WHITE CLIP
	AplParamSceneWhiteClipSwitch_S3,	//WHITE CLIP
	AplParamSceneWhiteClipSwitch_S4,	//WHITE CLIP
	AplParamSceneWhiteClipSwitch_S5,	//WHITE CLIP
	AplParamSceneWhiteClipSwitch_S6,	//WHITE CLIP
	AplParamSceneWhiteClipLevel_S1,	//WHITE CLIP LVL
	AplParamSceneWhiteClipLevel_S2,	//WHITE CLIP LVL
	AplParamSceneWhiteClipLevel_S3,	//WHITE CLIP LVL
	AplParamSceneWhiteClipLevel_S4,	//WHITE CLIP LVL
	AplParamSceneWhiteClipLevel_S5,	//WHITE CLIP LVL
	AplParamSceneWhiteClipLevel_S6,	//WHITE CLIP LVL
	AplParamSceneDRS_S1,	//DRS
	AplParamSceneDRS_S2,	//DRS
	AplParamSceneDRS_S3,	//DRS
	AplParamSceneDRS_S4,	//DRS
	AplParamSceneDRS_S5,	//DRS
	AplParamSceneDRS_S6,	//DRS
	AplParamSceneDRSEffectDepth_S1,	//DRS EFFECT DEPTH
	AplParamSceneDRSEffectDepth_S2,	//DRS EFFECT DEPTH
	AplParamSceneDRSEffectDepth_S3,	//DRS EFFECT DEPTH
	AplParamSceneDRSEffectDepth_S4,	//DRS EFFECT DEPTH
	AplParamSceneDRSEffectDepth_S5,	//DRS EFFECT DEPTH
	AplParamSceneDRSEffectDepth_S6,	//DRS EFFECT DEPTH
	AplParamSceneDNR_S1,	//DNR
	AplParamSceneDNR_S2,	//DNR
	AplParamSceneDNR_S3,	//DNR
	AplParamSceneDNR_S4,	//DNR
	AplParamSceneDNR_S5,	//DNR
	AplParamSceneDNR_S6,	//DNR
	AplParamSceneAutoIrisLevel_S1,	//A.IRIS LEVEL
	AplParamSceneAutoIrisLevel_S2,	//A.IRIS LEVEL
	AplParamSceneAutoIrisLevel_S3,	//A.IRIS LEVEL
	AplParamSceneAutoIrisLevel_S4,	//A.IRIS LEVEL
	AplParamSceneAutoIrisLevel_S5,	//A.IRIS LEVEL
	AplParamSceneAutoIrisLevel_S6,	//A.IRIS LEVEL
	AplParamSceneAutoIrisLevelEffect_S1,	//A.IRIS LEVEL EFFECT
	AplParamSceneAutoIrisLevelEffect_S2,	//A.IRIS LEVEL EFFECT
	AplParamSceneAutoIrisLevelEffect_S3,	//A.IRIS LEVEL EFFECT
	AplParamSceneAutoIrisLevelEffect_S4,	//A.IRIS LEVEL EFFECT
	AplParamSceneAutoIrisLevelEffect_S5,	//A.IRIS LEVEL EFFECT
	AplParamSceneAutoIrisLevelEffect_S6,	//A.IRIS LEVEL EFFECT
	AplParamSceneAchColorTempRGainCtrl_S1,	//COLOR TEMP R GAIN����l Ach
	AplParamSceneAchColorTempRGainCtrl_S2,	//COLOR TEMP R GAIN����l Ach
	AplParamSceneAchColorTempRGainCtrl_S3,	//COLOR TEMP R GAIN����l Ach
	AplParamSceneAchColorTempRGainCtrl_S4,	//COLOR TEMP R GAIN����l Ach
	AplParamSceneAchColorTempRGainCtrl_S5,	//COLOR TEMP R GAIN����l Ach
	AplParamSceneAchColorTempRGainCtrl_S6,	//COLOR TEMP R GAIN����l Ach
	AplParamSceneAchColorTempGGainCtrl_S1,	//COLOR TEMP B GAIN����l Ach
	AplParamSceneAchColorTempGGainCtrl_S2,	//COLOR TEMP B GAIN����l Ach
	AplParamSceneAchColorTempGGainCtrl_S3,	//COLOR TEMP B GAIN����l Ach
	AplParamSceneAchColorTempGGainCtrl_S4,	//COLOR TEMP B GAIN����l Ach
	AplParamSceneAchColorTempGGainCtrl_S5,	//COLOR TEMP B GAIN����l Ach
	AplParamSceneAchColorTempGGainCtrl_S6,	//COLOR TEMP B GAIN����l Ach
	AplParamSceneAchWhiteValueAWBResult_S1,	//AWB���s���� Ach
	AplParamSceneAchWhiteValueAWBResult_S2,	//AWB���s���� Ach
	AplParamSceneAchWhiteValueAWBResult_S3,	//AWB���s���� Ach
	AplParamSceneAchWhiteValueAWBResult_S4,	//AWB���s���� Ach
	AplParamSceneAchWhiteValueAWBResult_S5,	//AWB���s���� Ach
	AplParamSceneAchWhiteValueAWBResult_S6,	//AWB���s���� Ach
	AplParamSceneBchColorTempRGainCtrl_S1,	//COLOR TEMP R GAIN����l Bch
	AplParamSceneBchColorTempRGainCtrl_S2,	//COLOR TEMP R GAIN����l Bch
	AplParamSceneBchColorTempRGainCtrl_S3,	//COLOR TEMP R GAIN����l Bch
	AplParamSceneBchColorTempRGainCtrl_S4,	//COLOR TEMP R GAIN����l Bch
	AplParamSceneBchColorTempRGainCtrl_S5,	//COLOR TEMP R GAIN����l Bch
	AplParamSceneBchColorTempRGainCtrl_S6,	//COLOR TEMP R GAIN����l Bch
	AplParamSceneBchColorTempGGainCtrl_S1,	//COLOR TEMP B GAIN����l Bch
	AplParamSceneBchColorTempGGainCtrl_S2,	//COLOR TEMP B GAIN����l Bch
	AplParamSceneBchColorTempGGainCtrl_S3,	//COLOR TEMP B GAIN����l Bch
	AplParamSceneBchColorTempGGainCtrl_S4,	//COLOR TEMP B GAIN����l Bch
	AplParamSceneBchColorTempGGainCtrl_S5,	//COLOR TEMP B GAIN����l Bch
	AplParamSceneBchColorTempGGainCtrl_S6,	//COLOR TEMP B GAIN����l Bch
	AplParamSceneBchWhiteValueAWBResult_S1,	//AWB���s���� Bch
	AplParamSceneBchWhiteValueAWBResult_S2,	//AWB���s���� Bch
	AplParamSceneBchWhiteValueAWBResult_S3,	//AWB���s���� Bch
	AplParamSceneBchWhiteValueAWBResult_S4,	//AWB���s���� Bch
	AplParamSceneBchWhiteValueAWBResult_S5,	//AWB���s���� Bch
	AplParamSceneBchWhiteValueAWBResult_S6,	//AWB���s���� Bch
	AplParamMediaSelectPhoto,	//���f�B�A�I���i�Î~��j
	AplParamMediaSelect,	//���f�B�A�I���i����j
	AplParamPlayMedia,	//�Đ��Ώۃ��f�B�A
	AplParamUSeAreaSettings,	//�g�p����n��
	AplParamFormatDate1,	//�t�H�[�}�b�g����1�F����
	AplParamFormatSerialNumber1,	//�t�H�[�}�b�g����1�F�J�[�h�V���A���ԍ�
	AplParamFormatDate2,	//�t�H�[�}�b�g����2�F����
	AplParamFormatSerialNumber2,	//�t�H�[�}�b�g����2�F�J�[�h�V���A���ԍ�
	AplParamFormatDate3,	//�t�H�[�}�b�g����3�F����
	AplParamFormatSerialNumber3,	//�t�H�[�}�b�g����3�F�J�[�h�V���A���ԍ�
	AplParamFormatDate4,	//�t�H�[�}�b�g����4�F����
	AplParamFormatSerialNumber4,	//�t�H�[�}�b�g����4�F�J�[�h�V���A���ԍ�
	AplParamFormatDate5,	//�t�H�[�}�b�g����5�F����
	AplParamFormatSerialNumber5,	//�t�H�[�}�b�g����5�F�J�[�h�V���A���ԍ�
	AplParamFormatDate6,	//�t�H�[�}�b�g����6�F����
	AplParamFormatSerialNumber6,	//�t�H�[�}�b�g����6�F�J�[�h�V���A���ԍ�
	AplParamFormatDate7,	//�t�H�[�}�b�g����7�F����
	AplParamFormatSerialNumber7,	//�t�H�[�}�b�g����7�F�J�[�h�V���A���ԍ�
	AplParamFormatDate8,	//�t�H�[�}�b�g����8�F����
	AplParamFormatSerialNumber8,	//�t�H�[�}�b�g����8�F�J�[�h�V���A���ԍ�
	AplParamFormatDate9,	//�t�H�[�}�b�g����9�F����
	AplParamFormatSerialNumber9,	//�t�H�[�}�b�g����9�F�J�[�h�V���A���ԍ�
	AplParamFormatDate10,	//�t�H�[�}�b�g����10�F����
	AplParamFormatSerialNumber10,	//�t�H�[�}�b�g����10�F�J�[�h�V���A���ԍ�
	AplParamFormatHistoryNum,	//�t�H�[�}�b�g����ԍ�
	AplParamABBErrInfo,	//ABB�G���[���
	AplParamAWBErrInfo,	//AWB�G���[���
	AplParamColorTempGMgCtrl,	//GMg����l
	AplParamColorTempRGainCtrl,	//COLOR TEMP R GAIN����l
	AplParamColorTempGGainCtrl,	//COLOR TEMP B GAIN����l
	AplParamSuperGain,	//SUPER GAIN
	AplParamIrisModePro,	//�A�C���X���[�h(AUTO/MANUAL)
	AplParamNDFilter,	//SW����pND�t�B���^�[�l
	AplParamNDFilterIr,	//SW����pND�t�B���^�[�l(�ԊO���p)
	AplParamSetUb,	//���[�U�[�ݒ��UB�̒l
	AplParamDbgId,	//�f�o�b�O�p�FAPL �f�o�b�O�o�͐ݒ�
	AplParamVFRValueIncrementFlg,	//�f�o�b�O�p�FVFR�l�̎����C���N�������g�t���O
	AplParamLifeStartYear,	//���j���[�F���v�ݒ�J�n�N
	AplParamLifeEndYear,	//���j���[�F���v�ݒ�I���N
	AplParamContinuousRecordTime,	//�A���L�^���� [���P��] 
	AplParamContinuousIntervalRecTime,	//�C���^�[�o���A���L�^���� [���P��] 
	AplParamContinuousPreRecTime,	//PRE-REC�A���L�^���� [���P��]
	AplParamHeadPhoneDelayInterval,	//HP�ڑ��̃f�B���C�Ԋu
	AplParamSetupVersion,	//�Z�b�g�A�b�v�o�[�W����(�Z�b�g�A�b�v���Ver)
	AplParamSetupEepromVersion,	//�Z�b�g�A�b�v�o�[�W����(EEPROM�z�uVer)
	AplParamSceneVersion,	//�V�[���o�[�W����(�V�[�����Ver) �J�X�^���V�[���ݒ�d�l���L�ڂ̃o�[�W�������
	AplParamSceneEepromVersion,	//�V�[���o�[�W����(EEPROM�z�uVer) �J�X�^���V�[���ݒ�d�l���L�ڂ̃o�[�W�������
	AplParamVup,	//�o�[�W�����Ǘ�
	AplParamGrade,	//�T�[�r�X���j���[�FVUP�p���j���[�\���I��
	AplParamAudioClip_VolHigh,	//�I�[�f�B�I�N���b�v���(��)
	AplParamPhotoSound_VolHigh,	//�J�V�������ʐݒ�(��)
	AplParamBeepSound_VolHigh,	//�r�[�v�����ʐݒ�(��)
	AplParamAudioClip_VolMid,	//�I�[�f�B�I�N���b�v���(��)
	AplParamPhotoSound_VolMid,	//�J�V�������ʐݒ�(��)
	AplParamBeepSound_VolMid,	//�r�[�v�����ʐݒ�(��)
	AplParamAudioClip_VolLow,	//�I�[�f�B�I�N���b�v���(��)
	AplParamPhotoSound_VolLow,	//�J�V�������ʐݒ�(��)
	AplParamBeepSound_VolLow,	//�r�[�v�����ʐݒ�(��)
	AplParamRecBeep_VolHigh,	//�I�[�f�B�I�N���b�v���(��)
	AplParamBatteryEnd_VolHigh,	//�J�V�������ʐݒ�(��)
	AplParamMediaEnd_VolHigh,	//�r�[�v�����ʐݒ�(��)
	AplParamRecBeep_VolMid,	//�I�[�f�B�I�N���b�v���(��)
	AplParamBatteryEnd_VolMid,	//�J�V�������ʐݒ�(��)
	AplParamMediaEnd_VolMid,	//�r�[�v�����ʐݒ�(��)
	AplParamRecBeep_VolLow,	//�I�[�f�B�I�N���b�v���(��)
	AplParamBatteryEnd_VolLow,	//�J�V�������ʐݒ�(��)
	AplParamMediaEnd_VolLow,	//�r�[�v�����ʐݒ�(��)
	AplParamBalanceAngleColorFarR,	//������F�F�t�@�[ R
	AplParamBalanceAngleColorFarG,	//������F�F�t�@�[ G
	AplParamBalanceAngleColorFarB,	//������F�F�t�@�[ B
	AplParamBalanceAngleColorFarA,	//������F�F�t�@�[ A
	AplParamBalanceAngleColorNearR,	//������F�F�j�A R
	AplParamBalanceAngleColorNearG,	//������F�F�j�A G
	AplParamBalanceAngleColorNearB,	//������F�F�j�A B
	AplParamBalanceAngleColorNearA,	//������F�F�j�A A
	AplParamBalanceAngleColorFocusLockR,	//������F�F���� R
	AplParamBalanceAngleColorFocusLockG,	//������F�F���� G
	AplParamBalanceAngleColorFocusLockB,	//������F�F���� B
	AplParamBalanceAngleColorFocusLockA,	//������F�F���� A
	AplParamFocusExpandStep,	//�t�H�[�J�X�G�L�X�p���h�ړ���
	AplParamFocusExpandPosX,	//�t�H�[�J�X�G�L�X�p���hX���W
	AplParamFocusExpandPosY,	//�t�H�[�J�X�G�L�X�p���hY���W 
	AplParamSdDefReadSpeed,	//�R�s�[: ���f�B�A���x  SD�J�[�h�iDefaultSpeed�j Read (��ʃo�C�g)
	AplParamSdDefWriteSpeed,	//�R�s�[: ���f�B�A���x  SD�J�[�h�iDefaultSpeed�j Write (��ʃo�C�g)
	AplParamSdHighReadSpeed,	//�R�s�[: ���f�B�A���x  SD�J�[�h�iHighSpeed�j Read (��ʃo�C�g)
	AplParamSdHighWriteSpeed,	//�R�s�[: ���f�B�A���x  SD�J�[�h�iHighSpeed�j Write (��ʃo�C�g)
	AplParamHddReadSpeed,	//�R�s�[: ���f�B�A���x  HDD Read (��ʃo�C�g)
	AplParamHddWriteSpeed,	//�R�s�[: ���f�B�A���x  HDD Write (��ʃo�C�g)
	AplParamEsdReadSpeed,	//�R�s�[: ���f�B�A���x  eSD Read (��ʃo�C�g)
	AplParamEsdWriteSpeed,	//�R�s�[: ���f�B�A���x  eSD Write (��ʃo�C�g)
	AplParamCopyThreshold1,	//�R�s�[: �V�[���؂�ւ��  �؂�ւ��臒l 1 (��ʃo�C�g)
	AplParamCopyThreshold2,	//�R�s�[: �V�[���؂�ւ��  �؂�ւ��臒l 2 (��ʃo�C�g)
	AplParamSceneMultiplier1,	//�R�s�[: �V�[���؂�ւ��  �؂�ւ��搔 1 (��ʃo�C�g)
	AplParamSceneMultiplier2,	//�R�s�[: �V�[���؂�ւ��  �؂�ւ��搔 2 (��ʃo�C�g)
	AplParamSceneMultiplier3,	//�R�s�[: �V�[���؂�ւ��  �؂�ւ��搔 3 (��ʃo�C�g)
	AplParamDiscFinalizeTime,	//�R�s�[: �t�@�C�i���C�Y  �t�@�C�i���C�Y���� (��ʃo�C�g)
	AplParamPITransRatio,	//�R�s�[: �g�����X�R�[�h  60p �� 60i �ϊ��{��
	AplParamPhotoSceneMultiplier1,	//�R�s�[: �V�[���Î~�� �؂�ւ��  �Î~�� �؂�ւ��搔 1 (��ʃo�C�g)
	AplParamPhotoSceneMultiplier2,	//�R�s�[: �V�[���Î~�� �؂�ւ��  �Î~�� �؂�ւ��搔 2 (��ʃo�C�g)
	AplParamPhotoSceneMultiplier3,	//�R�s�[: �V�[���Î~�� �؂�ւ��  �Î~�� �؂�ւ��搔 3 (��ʃo�C�g)
	AplParamPCFriendlyEnable,	//PC�t�����h�� (MP4)
	AplParamBDUsable,	//�u���[���C�f�B�X�N�g�p
	AplParamAFRangeValueStep,	//AF�G���A��STEP
	AplParamSceneNum,	//�V�[����
	AplParamGyroSensorX,	//�W���C���Z���T�[�lX�@���[�U�[�␳�l
	AplParamGyroSensorY,	//�W���C���Z���T�[�lY�@���[�U�[�␳�l
	AplParamGyroSensorZ,	//�W���C���Z���T�[�lZ�@���[�U�[�␳�l
	AplParamGyroSensorInitX,	//�W���C���Z���T�[�lX�@�H��ݒ�␳�l
	AplParamGyroSensorInitY,	//�W���C���Z���T�[�lY�@�H��ݒ�␳�l
	AplParamGyroSensorInitZ,	//�W���C���Z���T�[�lZ�@�H��ݒ�␳�l
	AplParamIrisDialCnt,	//Iris�_�C��������J�E���^
	AplParamColorBar,	//�J���[�o�[
	AplParamPlayMode,	//���j���[�r���p�B�Đ����[�h�ɓ�������ON����
	AplParamDeckMode,	//APL�����̃��[�h(AplParamPlayMode�Ɨގ�)
	AplParamOptionMenuDisp,	//�I�v�V�������j���[�\���t���O
	AplParamAreaSelectDisplay,	//�N�����̃G���A�Z���N�g��ʕ\���t���O
	AplParamEnableSceneFileLoad,	//�V�[���t�@�C��LOAD���t���O
	AplParamEnableSceneFileSave,	//�V�[���t�@�C��SAVE���t���O
	AplParamEnableSceneFileSaveAs,	//�V�[���t�@�C��SAVE AS���t���O
	AplParamEnableSetupFileLoad,	//�Z�b�g�A�b�v�t�@�C��LOAD���t���O
	AplParamEnableSetupFileSave,	//�Z�b�g�A�b�v�t�@�C��SAVE���t���O
	AplParamEnableSetupFileSaveAs,	//�Z�b�g�A�b�v�t�@�C��SAVE AS���t���O
	AplParamSDcardInOutStatus,	//SD�J�[�h�̑}����Ԋm�F�t���O
	AplParamEnableSDWriteStatus,	//SD�������݉\�m�F�t���O
	AplParamAlert,	//�A���[�g
	AplParamAlertSubRecWarning,	//�A���[�g�FAPL_SYS_PARAM_ALERT_SUB_REC_WARNING
	AplParamAlertSimulRecWarning,	//�A���[�g�FAPL_SYS_PARAM_ALERT_SIMUL_REC_WARNING
	AplParamAlertBackGroundRecWarning,	//�A���[�g�FAPL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING
	AplParamAlertFanStopped,	//�A���[�g�FAPL_SYS_PARAM_ALERT_FAN_STOPPED
	AplParamAlertNotSupportCardSd1,	//�A���[�g�FAPL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD
	AplParamAlertNotSupportCardSd2,	//�A���[�g�FAPL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD
	AplParamAlertFormatErrorCardSd1,	//�A���[�g�FAPL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD
	AplParamAlertFormatErrorCardSd2,	//�A���[�g�FAPL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD
	AplParamAlertNotSDXCCardSd1,	//�A���[�g�FAPL_SYS_PARAM_ALERT_NOT_SDXC_CARD
	AplParamAlertNotSDXCCardSd2,	//�A���[�g�FAPL_SYS_PARAM_ALERT_NOT_SDXC_CARD
	AplParamAlertIncompatibleCardSd1,	//�A���[�g�FAPL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD
	AplParamAlertIncompatibleCardSd2,	//�A���[�g�FAPL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD
	AplParamAlertBackupBattEmpty,	//�A���[�g�FAPL_SYS_PARAM_ALERT_BACKUP_BATT_EMPTY
	AplParamAlertClockReset,	//�A���[�g�FAPL_SYS_PARAM_ALERT_CLOCK_RESET
	AplParamWarning,	//���[�j���O
	AplParamWarningLowBattery,	//���[�j���O�F�o�b�e���[�A���_�[�J�b�g
	AplParamWarningHighTemp,	//���[�j���O�F���x�ُ�
	AplParamWarningRecWarning,	//���[�j���O�F�L�^���ُ�
	AplParamWarningCardErrorPlaying,	//���[�j���O�F�L�^�Đ����̃J�[�h�ُ�
	AplParamWarningCardErrorSlot1,	//���[�j���O�F�L�^�Đ����̃J�[�h�ُ� SLOT1
	AplParamWarningCardErrorSlot2,	//���[�j���O�F�L�^�Đ����̃J�[�h�ُ� SLOT2
	AplParamWarningCardErrorPlayingSlot1,	//���[�j���O�F�L�^�Đ����̃J�[�h�ُ� SLOT1
	AplParamWarningCardErrorPlayingSlot2,	//���[�j���O�F�L�^�Đ����̃J�[�h�ُ� SLOT2
	AplParamWarningNoRemain,	//���[�j���O�F�L�^���ɃJ�[�h�c��0
	AplParamWarningBatteryNearEnd,	//���[�j���O�F�o�b�e���[�j�A�G���h
	AplParamInfoErr,	//�G���[���
	AplParamSlot1ErrStatus,	//���f�B�A�G���[�pSlot1
	AplParamSlot2ErrStatus,	//���f�B�A�G���[�pSlot2
	AplParamRelayBackupErrStatus,	//2SlotFunc�@�\��������
	AplParamSlot1Status,	//Slot1���
	AplParamSlot2Status,	//Slot2���
	AplParamSlot1Remain,	//�X���b�g1�̎c��
	AplParamSlot2Remain,	//�X���b�g2�̎c��
	AplParamSlot1RemainAll,	//�X���b�g1�̑S�L�^�\����
	AplParamSlot2RemainAll,	//�X���b�g2�̑S�L�^�\����
	AplParamSlot1InOutStatus,	//�X���b�g1���f�B�A�̑}�����
	AplParamSlot2InOutStatus,	//�X���b�g2���f�B�A�̑}�����
	AplParamRecFunctionStatus,	//�\���F����L�^���
	AplParamSdiRawRecStatus,	//�\���FSdiRaw�L�^��
	AplParamSdiHdmiRecRemoteStatus,	//�\���FSDI/HDMI Rec�����[�g
	AplParamAutoTrackingWhiteLock,	//�\���FATWLock
	AplParamHomeClipFileName,	//�\���FHOME��ʗp��CamNo./ReelNo./ClipNo.
	AplParamLifeMode,	//�\���F���C�t���[�h��ON/OFF���
	AplParamTestLowDisplay,	//�\���FTEST LOW
	AplParamComDisplay,	//�\���FCOM
	AplParamWifiDongleState,	//�h���O�����
	AplParamWlanLinkState,	//�\���FWLAN��LINK���
	AplParamWLanStatus,	//�\���FWLAN�d�g���x(Wifi)
	AplParamTcValueLcd,	//�\���F��ʕ\��TC(LCD)
	AplParamTcValueHdmi,	//�\���F��ʕ\��TC(Hdmi)
	AplParamTcValueSdi,	//�\���F��ʕ\��TC(Sdi)
	AplParamUbValueLcd,	//�\���F��ʕ\��UB(LCD)
	AplParamUbValueHdmi,	//�\���F��ʕ\��UB(Hdmi)
	AplParamUbValueSdi,	//�\���F��ʕ\��UB(Sdi)
	AplParamDurationValueLcd,	//�\���F��ʕ\��Dudation(LCD)
	AplParamDurationValueHdmi,	//�\���F��ʕ\��Duration(Hdmi)
	AplParamDurationValueSdi,	//�\���F��ʕ\��Duration(Sdi)
	AplParamRecCounterTotalValue,	//�\���F��ʕ\��REC COUNTER TOTAL
	AplParamRecCounterClipValue,	//�\���F��ʕ\��REC COUNTER CLIP
	AplParamRecCounterClipPlayValue,	//�\���F�Đ���ʕ\��REC COUNTER CLIP
	AplParamZoomLensValid,	//�\���F�\������Ɏg�p����CV����̏��
	AplParamIrisLensValid,	//�\���F�\������Ɏg�p����CV����̏��
	AplParamBatteryRemainStatus,	//�\���F�o�b�e���[�c��
	AplParamRecClipName,	//�\���F�N���b�v�l�[��
	AplParamPlayClipName,	//�\���F�Đ��A�v���p�N���b�v�l�[��
	AplParamStatusPlay,	//�\���F�Đ����X�e�[�^�X�A�C�R��
	AplParamStatusPlaySeekBar,	//�\���F�Đ����V�[�N�o�[�i����
	AplParamPlayGeneralProgressBar,	//�\���F�Đ��ҏW�n�v���O���X�o�[�̐i����
	AplParamPlayWaitingStatus,	//�\���F�N���b�v�\��������Waiting�\���t���O
	AplParamPlayMovIcon,	//�\���FMOV�p�T���l�C����ʃA�C�R��
	AplParamPlayAvchdIcon,	//�\���FAVCHD�p�T���l�C����ʃA�C�R��
	AplParamTcPlayValueLcd,	//�\���F�Đ���ʕ\��TC(LCD)
	AplParamTcPlayValueHdmi,	//�\���F�Đ���ʕ\��TC(Hdmi)
	AplParamTcPlayValueSdi,	//�\���F�Đ���ʕ\��TC(Sdi)
	AplParamUbPlayValueLcd,	//�\���F�Đ���ʕ\��UB(LCD)
	AplParamUbPlayValueHdmi,	//�\���F�Đ���ʕ\��UB(Hdmi)
	AplParamUbPlayValueSdi,	//�\���F�Đ���ʕ\��UB(Sdi)
	AplParamDurationPlayValueLcd,	//�\���F�Đ���ʕ\��Dudation(LCD)
	AplParamDurationPlayValueHdmi,	//�\���F�Đ���ʕ\��Duration(Hdmi)
	AplParamDurationPlayValueSdi,	//�\���F�Đ���ʕ\��Duration(Sdi)
	AplParamCopyDirection,	//�\���FCOPY�����\���p
	AplParamOverClipSd1,	//Info-Diag�\���p�t���O
	AplParamOverClipSd2,	//Info-Diag�\���p�t���O
	AplParamClockDate,	//���j���[�\���F���v�ݒ����n���p
	AplParamDispClockDate,	//���j���[�\���F���v���`��p
	AplParamInfoSensorTemp,	//���j���[�\���F�Z���T�[���x
	AplParamInfoIrisDial,	//���j���[�\���F�A�C���X�_�C�A������
	AplParamSetTc,	//���j���[�\���FTC���
	AplParamEditFileName,	//���j���[�\���F�V�[���t�@�C��/�Z�b�g�A�b�v�t�@�C����
	AplParamWlanMacAddressString,	//���j���[�ɕ\������MAC�A�h���X(WLAN)
	AplParamLanMacAddressString,	//���j���[�ɕ\������MAC�A�h���X(LAN)
	AplParamDispTc,	//TC���`��p
	AplParamIrisVal,	//IRIS�l�`��p
	AplParamIrisValueControl,	//F�l�̒l����A�擾
	AplParamZoomVal,	//ZOOM�l�`��p(�l)
	AplParamZoomMm,	//ZOOM�l�`��p�imm�j
	AplParamSpotMeterStopVal,	//�P�x�\��(STOP�p)
	AplParamSpotMeterPerVal,	//�P�x�\��(���p)
	AplParamDfMode,	//��ʕ\��DF���[�h
	AplParamDfModePlay,	//�Đ���ʕ\��DF���[�h
	AplParamTcInSlave,	//TC SLAVE���
	AplParamIrisDispFlg,	//�A�C���X���샂�[�h
	AplParamGyroSensorDispX,	//�W���C���Z���T�[�lX�@�\���p
	AplParamGyroSensorDispY,	//�W���C���Z���T�[�lY�@�\���p
	AplParamGyroSensorDispZ,	//�W���C���Z���T�[�lZ�@�\���p
	AplParamLcdLevelGaugeBalanceAngle,	//�X���p�x�i������p�j
	AplParamLcdLevelGaugeAoriAngle,	//������p�x�i������p�j
	AplParamLcdLevelGaugeBalanceAngleInit,	//�X���p�x�i������p�j�H�������ݒ�
	AplParamLcdLevelGaugeAoriAngleInit,	//������p�x�i������p�j�H�������ݒ�
	AplParamLcdLevelGaugeBalanceAngleUser,	//�X���p�x�i������p�j���[�U�[�ݒ�
	AplParamLcdLevelGaugeAoriAngleUser,	//������p�x�i������p�j���[�U�[�ݒ�
	AplParamAudioLevelMeterCH1,	//�I�[�f�B�I���x����CH1�̖ڐ��l
	AplParamAudioLevelMeterCH2,	//�I�[�f�B�I���x����CH2�̖ڐ��l
	AplParamPowerLcdUserSw,	//UserSw�pPowerLcd�ݒ�l
	AplParamLcdMarkerUserSw,	//UserSw�pLcdMarker�ݒ�l
	AplParamLcdCleanViewUserSw,	//UserSw�pLcd Clean View�ݒ�l
	AplParamSpotMeterUserSw,	//UserSw�pSpotMeter�ݒ�l
	AplParamLcdFocusAssistUserSw,	//UserSw�pFocusAssist�ݒ�l
	AplParamLcdFocusExpandUserSw,	//UserSw�pFocusExpand�ݒ�l
	AplParamLcdOpenIrisFocusAssistUserSw,	//UserSw�pOpenIrisFocusAssist�ݒ�l
	AplParamLcdFocusExpandPosUserSw,	//UserSw�pFocusExpandPosition�ݒ�l
	AplParamDZoomUserSw,	//UserSw�pDZoom�ݒ�l
	AplParamHomeSw,	//���[�h�ؑ֗pHomeSw��������
	AplParamAudioLevelMeterInvalid,	//�I�[�f�B�I���x�����[�^�������
	AplParamLcdSw,	//LCD�X�C�b�`�̏��
	AplParamIrisDispInfoType,	//�A�C���X�\�������
	AplParamFactCommandMenuType,	//���j���[�R�}���h�ł̎擾���j���[�I��
	AplParamBeEepVer,	//BE EEPROM Ver (�T�[�r�X���j���[)
	AplParamCamEepVer,	//CAM EEPROM Ver (�T�[�r�X���j���[)
	AplParamBeSum,	//BE SUM (�T�[�r�X���j���[)
	AplParamCamSum,	//CAM SUM (�T�[�r�X���j���[)
	AplParamBeCrc,	//BE CRC (�T�[�r�X���j���[)
	AplParamCamCrc,	//CAM CRC (�T�[�r�X���j���[)
	AplParamWorldTimeMode,	//���[���h�^�C���ݒ�
	AplParamFlashBandCorrection,	//�t���b�V���o���h�␳
	AplParamRopControlIris,	//ROP����IRIS����D��
	AplParamHDCMovie_MakerID,	//HDC_MakerID1
	AplParamHDCMovie_ModelCode,	//HDC_ModelCode1
	AplParamSavedStreamingData,	//STREAMING�ݒ�f�[�^�̗L��
	AplParamTcFrameMax,	//TC�v���Z�b�g��MAX�l
	AplParamWifiLv4Limit,	//89FB�`89FF��NET�u���b�N���Q�Ƃ���l�A�ύX����Ƃ��͑��k�K�v
	AplParamWifiLv3Limit,	//89FB�`89FF��NET�u���b�N���Q�Ƃ���l�A�ύX����Ƃ��͑��k�K�v
	AplParamWifiLv2Limit,	//89FB�`89FF��NET�u���b�N���Q�Ƃ���l�A�ύX����Ƃ��͑��k�K�v
	AplParamWifiLv1Limit,	//89FB�`89FF��NET�u���b�N���Q�Ƃ���l�A�ύX����Ƃ��͑��k�K�v
	AplParamWifiLv0Limit,	//89FB�`89FF��NET�u���b�N���Q�Ƃ���l�A�ύX����Ƃ��͑��k�K�v
	AplParamSystemSettingsMenu,	//SYSTEM SETTINGS MENU TOP
	AplParamSystemModeMenu,	//SYSTEM SETTINGS > SYSTEM MODE
	AplParamSystemModeFrequency,	//�V�X�e�����g��
	AplParamSystemSdiRaw,	//SDI�[�q����o�͂���RAW��f��
	AplParamSystemSensorMode,	//�Z���T�[�̋쓮���[�h
	AplParamSystemMainPixel,	//���C�����R�[�_�[�̋L�^��f��
	AplParamSystemMainCodec,	//���C�����R�[�_�[�̋L�^�R�[�f�b�N
	AplParamSystemSubRec,	//�T�u���R�[�_�[�̋L�^�R�[�f�b�N
	AplParamColorSettingsMenu,	//SYSTEM SETTINGS > COLOR SETTINGS
	AplParamColorMain,	//���C�����R�[�_�[�ɋL�^�����f���i�J�����V�X�e���S�́j�̃J���[
	AplParamColorSub,	//�T�u���R�[�_�[�ɋL�^�����f���̃J���[
	AplParamColorSdiOut,	//SDI�[�q����̏o�̓C���[�W��ݒ�
	AplParamColorHdmiOut,	//HDMI�[�q����̏o�̓C���[�W
	AplParamColorLcdOut,	//LCD�[�q����̏o�̓C���[�W
	AplParamUserToggle,	//�qTOGGLE/USER�r�{�^���Ɋ��蓖�Ă�@�\��ݒ�
	AplParamSideLockMenu,	//SYSTEM SETTINGS > SIDE LOCK
	AplParamSideLockRecButton,	//�J�����{�̂́qREC�r�{�^�������b�N���邩�ǂ���
	AplParamSideLockUser1Button,	//�qUSER1�r�{�^�������b�N���邩�ǂ���
	AplParamSideLockUser2Button,	//�qUSER2�r�{�^�������b�N���邩�ǂ���
	AplParamSideLockUser3Button,	//�qUSER3�r�{�^�������b�N���邩�ǂ���
	AplParamSideLockUser4Button,	//�qUSER4�r�{�^�������b�N���邩�ǂ���
	AplParamSideLockUser5Button,	//�qUSER5�r�{�^�������b�N���邩�ǂ���
	AplParamSideLockUser6Button,	//�qUSER6�r�{�^�������b�N���邩�ǂ���
	AplParamSideLockUser7Button,	//�qUSER7�r�{�^�������b�N���邩�ǂ���
	AplParamSideLockThumbnailButton,	//�qTHUMBNAIL�r�{�^�������b�N���邩�ǂ�����ݒ�
	AplParamSideLockHomeButton,	//�qHOME�r�{�^�������b�N���邩�ǂ�����ݒ�
	AplParamSideLockNdFilterButton,	//�qND FILTER�r�{�^�������b�N���邩�ǂ�����ݒ�
	AplParamSideLockIrisDial,	//�qIRIS DIAL�r�{�^�������b�N���邩�ǂ�����ݒ�
	AplParamSideLockMenuButton,	//�qMENU�r�{�^�������b�N���邩�ǂ�����ݒ�
	AplParamSideLockExitButton,	//�qEXIT�r�{�^�������b�N���邩�ǂ�����ݒ�
	AplParamSideLockMultiDial,	//�qMULTI DIAL�r�{�^�������b�N���邩�ǂ�����ݒ�
	AplParamPowerLed,	//�d�������v���[�h
	AplParamFanSpeed,	//�t�@���̉�]���x��I��
	AplParamCameraSettingsMenu,	//CAMERA SETTINGS
	AplParamFpsMenu,	//CAMERA SETTINGS > FPS
	AplParamVFRMode,	//VFR���[�h
	AplParamVFRValue,	//���ݑI�𒆂�VFR�l
	AplParamVFRValueIndex,	//���ݑI�𒆂�VFR
	AplParamVFRValueSystem,	//VFR Value ���X�g
	AplParamVFRValue1,	//VFR Value ���X�g
	AplParamVFRValue2,	//VFR Value ���X�g
	AplParamVFRValue3,	//VFR Value ���X�g
	AplParamVFRValue4,	//VFR Value ���X�g
	AplParamVFRValue5,	//VFR Value ���X�g
	AplParamVFRValue6,	//VFR Value ���X�g
	AplParamVFRValue7,	//VFR Value ���X�g
	AplParamVFRValue8,	//VFR Value ���X�g
	AplParamVFRValue9,	//VFR Value ���X�g
	AplParamVFRValue10,	//VFR Value ���X�g
	AplParamVFRValue11,	//VFR Value ���X�g
	AplParamVFRValue12,	//VFR Value ���X�g
	AplParamVFRValue13,	//VFR Value ���X�g
	AplParamVFRValue14,	//VFR Value ���X�g
	AplParamVFRValue15,	//VFR Value ���X�g
	AplParamVFRValue16,	//VFR Value ���X�g
	AplParamVFRValue17,	//VFR Value ���X�g
	AplParamVFRValue18,	//VFR Value ���X�g
	AplParamVFRValue19,	//VFR Value ���X�g
	AplParamVFRValue20,	//VFR Value ���X�g
	AplParamVFRValue21,	//VFR Value ���X�g
	AplParamVFRValue22,	//VFR Value ���X�g
	AplParamVFRValue23,	//VFR Value ���X�g
	AplParamVFRValue24,	//VFR Value ���X�g
	AplParamVFRValue25,	//VFR Value ���X�g
	AplParamVFRValue26,	//VFR Value ���X�g
	AplParamVFRValue27,	//VFR Value ���X�g
	AplParamVFRValue28,	//VFR Value ���X�g
	AplParamVFRValue29,	//VFR Value ���X�g
	AplParamVFRValue30,	//VFR Value ���X�g
	AplParamVFRValue31,	//VFR Value ���X�g
	AplParamVFRValue32,	//VFR Value ���X�g
	AplParamVFRValue33,	//VFR Value ���X�g
	AplParamVFRValue34,	//VFR Value ���X�g
	AplParamVFRValue35,	//VFR Value ���X�g
	AplParamVFRValue36,	//VFR Value ���X�g
	AplParamVFRValue37,	//VFR Value ���X�g
	AplParamVFRValue38,	//VFR Value ���X�g
	AplParamVFRValue39,	//VFR Value ���X�g
	AplParamVFRValue40,	//VFR Value ���X�g
	AplParamVFRValue41,	//VFR Value ���X�g
	AplParamVFRValue42,	//VFR Value ���X�g
	AplParamVFRValue43,	//VFR Value ���X�g
	AplParamVFRValue44,	//VFR Value ���X�g
	AplParamVFRValue45,	//VFR Value ���X�g
	AplParamVFRValue46,	//VFR Value ���X�g
	AplParamVFRValue47,	//VFR Value ���X�g
	AplParamVFRValue48,	//VFR Value ���X�g
	AplParamVFRValue49,	//VFR Value ���X�g
	AplParamVFRValue50,	//VFR Value ���X�g
	AplParamVFRValue51,	//VFR Value ���X�g
	AplParamVFRValue52,	//VFR Value ���X�g
	AplParamVFRValue53,	//VFR Value ���X�g
	AplParamVFRValue54,	//VFR Value ���X�g
	AplParamVFRValue55,	//VFR Value ���X�g
	AplParamVFRValue56,	//VFR Value ���X�g
	AplParamVFRValue57,	//VFR Value ���X�g
	AplParamVFRValue58,	//VFR Value ���X�g
	AplParamVFRValue59,	//VFR Value ���X�g
	AplParamVFRValue60,	//VFR Value ���X�g
	AplParamVFRValue61,	//VFR Value ���X�g
	AplParamVFRValue62,	//VFR Value ���X�g
	AplParamVFRValue63,	//VFR Value ���X�g
	AplParamVFRValue64,	//VFR Value ���X�g
	AplParamVFRValue65,	//VFR Value ���X�g
	AplParamVFRValue66,	//VFR Value ���X�g
	AplParamVFRValue67,	//VFR Value ���X�g
	AplParamVFRValue68,	//VFR Value ���X�g
	AplParamVFRValue69,	//VFR Value ���X�g
	AplParamVFRValue70,	//VFR Value ���X�g
	AplParamVFRValue71,	//VFR Value ���X�g
	AplParamVFRValue72,	//VFR Value ���X�g
	AplParamVFRValue73,	//VFR Value ���X�g
	AplParamVFRValue74,	//VFR Value ���X�g
	AplParamVFRValue75,	//VFR Value ���X�g
	AplParamVFRValue76,	//VFR Value ���X�g
	AplParamVFRValue77,	//VFR Value ���X�g
	AplParamVFRValue78,	//VFR Value ���X�g
	AplParamVFRValue79,	//VFR Value ���X�g
	AplParamVFRValue80,	//VFR Value ���X�g
	AplParamVFRValue81,	//VFR Value ���X�g
	AplParamVFRValue82,	//VFR Value ���X�g
	AplParamVFRValue83,	//VFR Value ���X�g
	AplParamVFRValue84,	//VFR Value ���X�g
	AplParamVFRValue85,	//VFR Value ���X�g
	AplParamVFRValue86,	//VFR Value ���X�g
	AplParamVFRValue87,	//VFR Value ���X�g
	AplParamVFRValue88,	//VFR Value ���X�g
	AplParamVFRValue89,	//VFR Value ���X�g
	AplParamVFRValue90,	//VFR Value ���X�g
	AplParamVFRValue91,	//VFR Value ���X�g
	AplParamVFRValue92,	//VFR Value ���X�g
	AplParamVFRValue93,	//VFR Value ���X�g
	AplParamVFRValue94,	//VFR Value ���X�g
	AplParamVFRValue95,	//VFR Value ���X�g
	AplParamVFRValue96,	//VFR Value ���X�g
	AplParamVFRValue97,	//VFR Value ���X�g
	AplParamVFRValue98,	//VFR Value ���X�g
	AplParamVFRValue99,	//VFR Value ���X�g
	AplParamVFRValue100,	//VFR Value ���X�g
	AplParamVFRValue101,	//VFR Value ���X�g
	AplParamVFRValue102,	//VFR Value ���X�g
	AplParamVFRValue103,	//VFR Value ���X�g
	AplParamVFRValue104,	//VFR Value ���X�g
	AplParamVFRValue105,	//VFR Value ���X�g
	AplParamVFRValue106,	//VFR Value ���X�g
	AplParamVFRValue107,	//VFR Value ���X�g
	AplParamVFRValue108,	//VFR Value ���X�g
	AplParamVFRValue109,	//VFR Value ���X�g
	AplParamVFRValue110,	//VFR Value ���X�g
	AplParamVFRValue111,	//VFR Value ���X�g
	AplParamVFRValue112,	//VFR Value ���X�g
	AplParamVFRValue113,	//VFR Value ���X�g
	AplParamVFRValue114,	//VFR Value ���X�g
	AplParamVFRValue115,	//VFR Value ���X�g
	AplParamVFRValue116,	//VFR Value ���X�g
	AplParamVFRValue117,	//VFR Value ���X�g
	AplParamVFRValue118,	//VFR Value ���X�g
	AplParamVFRValue119,	//VFR Value ���X�g
	AplParamVFRValue120,	//VFR Value ���X�g
	AplParamVFRValue121,	//VFR Value ���X�g
	AplParamVFRValue122,	//VFR Value ���X�g
	AplParamVFRValue123,	//VFR Value ���X�g
	AplParamVFRValue124,	//VFR Value ���X�g
	AplParamVFRValue125,	//VFR Value ���X�g
	AplParamVFRValue126,	//VFR Value ���X�g
	AplParamVFRValue127,	//VFR Value ���X�g
	AplParamVFRValue128,	//VFR Value ���X�g
	AplParamVFRValue129,	//VFR Value ���X�g
	AplParamVFRValue130,	//VFR Value ���X�g
	AplParamVFRValue131,	//VFR Value ���X�g
	AplParamVFRValue132,	//VFR Value ���X�g
	AplParamVFRValue133,	//VFR Value ���X�g
	AplParamVFRValue134,	//VFR Value ���X�g
	AplParamVFRValue135,	//VFR Value ���X�g
	AplParamVFRValue136,	//VFR Value ���X�g
	AplParamVFRValue137,	//VFR Value ���X�g
	AplParamVFRValue138,	//VFR Value ���X�g
	AplParamVFRValue139,	//VFR Value ���X�g
	AplParamVFRValue140,	//VFR Value ���X�g
	AplParamVFRValue141,	//VFR Value ���X�g
	AplParamVFRValue142,	//VFR Value ���X�g
	AplParamVFRValue143,	//VFR Value ���X�g
	AplParamVFRValue144,	//VFR Value ���X�g
	AplParamVFRValue145,	//VFR Value ���X�g
	AplParamVFRValue146,	//VFR Value ���X�g
	AplParamVFRValue147,	//VFR Value ���X�g
	AplParamVFRValue148,	//VFR Value ���X�g
	AplParamVFRValue149,	//VFR Value ���X�g
	AplParamVFRValue150,	//VFR Value ���X�g
	AplParamVFRValueIndexNTSC,	//���ݑI�𒆂�VFR (NTSC)
	AplParamVFRValueSystemNTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue1NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue2NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue3NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue4NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue5NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue6NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue7NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue8NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue9NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue10NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue11NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue12NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue13NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue14NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue15NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue16NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue17NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue18NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue19NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue20NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue21NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue22NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue23NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue24NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue25NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue26NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue27NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue28NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue29NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue30NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue31NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue32NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue33NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue34NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue35NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue36NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue37NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue38NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue39NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue40NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue41NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue42NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue43NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue44NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue45NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue46NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue47NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue48NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue49NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue50NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue51NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue52NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue53NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue54NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue55NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue56NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue57NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue58NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue59NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue60NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue61NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue62NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue63NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue64NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue65NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue66NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue67NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue68NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue69NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue70NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue71NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue72NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue73NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue74NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue75NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue76NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue77NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue78NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue79NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue80NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue81NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue82NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue83NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue84NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue85NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue86NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue87NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue88NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue89NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue90NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue91NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue92NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue93NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue94NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue95NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue96NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue97NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue98NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue99NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue100NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue101NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue102NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue103NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue104NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue105NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue106NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue107NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue108NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue109NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue110NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue111NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue112NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue113NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue114NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue115NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue116NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue117NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue118NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue119NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue120NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue121NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue122NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue123NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue124NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue125NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue126NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue127NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue128NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue129NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue130NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue131NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue132NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue133NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue134NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue135NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue136NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue137NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue138NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue139NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue140NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue141NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue142NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue143NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue144NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue145NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue146NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue147NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue148NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue149NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValue150NTSC,	//VFR Value ���X�g (NTSC)
	AplParamVFRValueIndexPAL,	//���ݑI�𒆂�VFR (PAL)
	AplParamVFRValueSystemPAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue1PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue2PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue3PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue4PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue5PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue6PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue7PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue8PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue9PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue10PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue11PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue12PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue13PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue14PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue15PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue16PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue17PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue18PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue19PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue20PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue21PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue22PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue23PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue24PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue25PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue26PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue27PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue28PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue29PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue30PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue31PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue32PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue33PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue34PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue35PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue36PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue37PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue38PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue39PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue40PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue41PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue42PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue43PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue44PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue45PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue46PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue47PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue48PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue49PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue50PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue51PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue52PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue53PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue54PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue55PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue56PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue57PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue58PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue59PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue60PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue61PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue62PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue63PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue64PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue65PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue66PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue67PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue68PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue69PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue70PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue71PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue72PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue73PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue74PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue75PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue76PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue77PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue78PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue79PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue80PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue81PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue82PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue83PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue84PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue85PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue86PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue87PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue88PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue89PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue90PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue91PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue92PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue93PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue94PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue95PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue96PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue97PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue98PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue99PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue100PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue101PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue102PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue103PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue104PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue105PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue106PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue107PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue108PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue109PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue110PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue111PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue112PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue113PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue114PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue115PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue116PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue117PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue118PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue119PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue120PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue121PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue122PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue123PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue124PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue125PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue126PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue127PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue128PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue129PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue130PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue131PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue132PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue133PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue134PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue135PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue136PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue137PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue138PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue139PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue140PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue141PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue142PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue143PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue144PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue145PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue146PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue147PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue148PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue149PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRValue150PAL,	//VFR Value ���X�g (PAL)
	AplParamVFRSettingRangeMax,	//VFR �ݒ�͈͍ő�l
	AplParamVFRSettingRangeMin,	//VFR �ݒ�͈͍ŏ��l
	AplParamShutterMenu,	//CAMERA SETTINGS > SHUTTER
	AplParamShutterSwitch,	//�}���`�_�C������SET�ƘA��
	AplParamShutterDispChg,	//�V���b�^�[�\���ؑ�
	AplParamShutterDegValue,	//���ݑI�𒆂�SHUTTER (�p�x)
	AplParamShutterDegValueIndex,	//���ݑI�𒆂�SHUTTER
	AplParamShutterDegValueHalf,	//�p�x�\���p�̃n�[�t�V���b�^�[�l
	AplParamShutterDegValue1,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue2,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue3,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue4,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue5,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue6,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue7,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue8,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue9,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue10,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValue11,	//�p�x�\���p��Value���X�g
	AplParamShutterDegValueIndexNTSC,	//���ݑI�𒆂�SHUTTER (�p�x/NTSC)
	AplParamShutterDegValueHalfNTSC,	//�p�x�\���p�̃n�[�t�V���b�^�[�l (NTSC)
	AplParamShutterDegValue1NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue2NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue3NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue4NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue5NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue6NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue7NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue8NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue9NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue10NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValue11NTSC,	//�p�x�\���p��Value���X�g (NTSC)
	AplParamShutterDegValueIndexPAL,	//���ݑI�𒆂�SHUTTER (�p�x/PAL)
	AplParamShutterDegValueHalfPAL,	//�p�x�\���p�̃n�[�t�V���b�^�[�l (PAL)
	AplParamShutterDegValue1PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue2PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue3PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue4PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue5PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue6PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue7PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue8PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue9PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue10PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterDegValue11PAL,	//�p�x�\���p��Value���X�g (PAL)
	AplParamShutterSecValue,	//���ݑI�𒆂�SHUTTER (����)
	AplParamShutterSecValueHalf,	//���ԕ\���p�̃n�[�t�V���b�^�[�l
	AplParamShutterSecValue1,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue2,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue3,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue4,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue5,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue6,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue7,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue8,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue9,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue10,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValue11,	//���ԕ\���p��Value���X�g
	AplParamShutterSecValueIndex,	//���ݑI�𒆂�SHUTTER
	AplParamShutterSecValueIndexNTSC,	//���ݑI�𒆂�SHUTTER (����/NTSC)
	AplParamShutterSecValueHalfNTSC,	//���ԕ\���p�̃n�[�t�V���b�^�[�l (NTSC)
	AplParamShutterSecValue1NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue2NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue3NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue4NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue5NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue6NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue7NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue8NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue9NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue10NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValue11NTSC,	//���ԕ\���p��Value���X�g (NTSC)
	AplParamShutterSecValueIndexPAL,	//���ݑI�𒆂�SHUTTER (����/PAL)
	AplParamShutterSecValueHalfPAL,	//���ԕ\���p�̃n�[�t�V���b�^�[�l (PAL)
	AplParamShutterSecValue1PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue2PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue3PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue4PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue5PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue6PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue7PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue8PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue9PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue10PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecValue11PAL,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecSettingRangeMax,	//���ԕ\���p��Value���X�g (PAL)
	AplParamShutterSecSettingRangeMin,	//���ԕ\���p��Value���X�g (PAL)
	AplParamEIMenu,	//CAMERA SETTINGS > EI
	AplParamGainIsoDispChg,	//Gain/ISO�\���ؑ�
	AplParamISOSelect,	//�g�p����ISO��I������
	AplParamNativeISO,	//NATIVE��ISO��I��
	AplParam800BaseISO,	//800BASE��ISO��I��
	AplParam2500BaseISO,	//2500BASE��ISO��I��
	AplParamNativeISOSdiRawNotVideo,	//NATIVE��ISO��I�� (Sdi Raw [GAMMA]��VIDEO)
	AplParamNativeISOSdiRawVideo,	//NATIVE��ISO��I�� (Sdi Raw [GAMMA]=VIDEO)
	AplParamNativeISOSdiRaw2_2_K,	//NATIVE��ISO��I�� (Sdi Raw SensorMode:2.2K)
	AplParamNativeISOSensor2_2_K,	//NATIVE��ISO��I�� (SensorMode:2.2K)
	AplParamNativeISONotVideo,	//NATIVE��ISO��I�� ([GAMMA]��VIDEO)
	AplParamNativeISOVideo,	//NATIVE��ISO��I��([GAMMA]=VIDEO)
	AplParam800BaseISOSdiRawNotVideo,	//800BASE��ISO��I�� (Sdi Raw [GAMMA]��VIDEO)
	AplParam800BaseISOSdiRawVideo,	//800BASE��ISO��I�� (Sdi Raw [GAMMA]=VIDEO)
	AplParam800BaseISOSdiRaw2_2_K,	//800BASE��ISO��I�� (Sdi Raw SensorMode:2.2K)
	AplParam800BaseISOSensor2_2_K,	//800BASE��ISO��I�� (SensorMode:2.2K)
	AplParam800BaseISONotVideo,	//800BASE��ISO��I�� ([GAMMA]��VIDEO)
	AplParam800BaseISOVideo,	//800BASE��ISO��I��([GAMMA]=VIDEO)
	AplParam2500BaseISOSdiRawNotVideo,	//2500BASE��ISO��I�� (Sdi Raw [GAMMA]��VIDEO)
	AplParam2500BaseISOSdiRawVideo,	//2500BASE��ISO��I�� (Sdi Raw [GAMMA]=VIDEO)
	AplParam2500BaseISOSdiRaw2_2_K,	//2500BASE��ISO��I�� (Sdi Raw SensorMode:2.2K)
	AplParam2500BaseISOSensor2_2_K,	//2500BASE��ISO��I�� (SensorMode:2.2K)
	AplParam2500BaseISONotVideo,	//2500BASE��ISO��I�� ([GAMMA]��VIDEO)
	AplParam2500BaseISOVideo,	//2500BASE��ISO��I��([GAMMA]=VIDEO)
	AplParam3200BaseISO,	//3200BASE��ISO��I��
	AplParamGainSwitch,	//Gain�̃��[�h�I��
	AplParamGainSelect,	//GainSelect�̏�� (��EEPROM)
	AplParamGainSelectNormalNotVideo,	//GainSelect�̏�� (SW = Normal�AGAMMA ��Video)
	AplParamGainSelectNormalVideo,	//GainSelect�̏�� (SW = Normal�AGAMMA = Video)
	AplParamGainSelectHighNotVideo,	//GainSelect�̏�� (SW = High�AGAMMA ��Video)
	AplParamGainSelectHighVideo,	//GainSelect�̏�� (SW = High�AGAMMA =Video)
	AplParamGainSelectNormalSensor2_2_K,	//GainSelect�̏�� (SensorMode:2.2K)
	AplParamGainSelectHighSensor2_2_K,	//GainSelect�̏�� (SensorMode:2.2K)
	AplParamWhiteMenu,	//CAMERA SETTINGS > WHITE
	AplParamAwb,	//AWB����  (��EEPROM)
	AplParamWhiteValueTemp,	//AWB�̌��݂̑I��l��ێ� (K)
	AplParamWhiteValueGMg,	//AWB�̌��݂̑I��l��ێ� (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValueAWBResult,	//AWB���s����
	AplParamWhiteValueIndex,	//���ݑI�𒆂�WhiteValue�I��
	AplParamWhiteValueATWTemp,	//Index�l��0�n�܂�p��Dummy
	AplParamWhiteValueATWGMg,	//Index�l��0�n�܂�p��Dummy
	AplParamWhiteValueAWBMemoryTemp,	//AWB�̒l��ێ� (K)
	AplParamWhiteValueAWBMemoryGMg,	//AWB�̒l��ێ� (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue1Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue1GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue2Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue2GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue3Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue3GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue4Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue4GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue5Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue5GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue6Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue6GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue7Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue7GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue8Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue8GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue9Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue9GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamWhiteValue10Temp,	//ADD�Œǉ�����White�̒l (K)
	AplParamWhiteValue10GMg,	//ADD�Œǉ�����White�̒l (GMg) -10.0�`10.0��10�{�����l�ŕێ�
	AplParamNRMenu,	//CAMERA SETTINGS > NR
	AplParamNRISO800,	//Noize Reduction��ON/OFF
	AplParamNRISO2500,	//Noize Reduction��ON/OFF
	AplParamNRISO3200,	//Noize Reduction��ON/OFF
	AplParamLensSettingMenu,	//CAMERA SETTINGS > LENS SETTING
	AplParamAIrisLevelEffect,	//A. IRIS LEVEL EFFECT (0-100)
	AplParamAIrisPeakAve,	//A. IRIS PEAK/AVE
	AplParamIrisDial,	//�i�����(�A�C���X����)
	AplParamAfOffSet,	//AutoFocus�̍��ňʒu
	AplParamTouchAfSw,	//TOUCH AF SW
	AplParamEISMenu,	//CAMERA SETTINGS > E.I.S
	AplParamEISSwitch,	//E.I.S SW
	AplParamZoomPosition,	//ZOOM POSITION
	AplParamZoomPositionValue,	//ZOOM POSITION VALUE
	AplParamAutoBlackBalanceMenu,	//CAMERA SETTINGS > AUTO BLACK BALANCE
	AplParamAutoBlackBalance,	//AUTO BLACK BALANCE
	AplParamSceneFileSettingMenu,	//SCENE FILE SETTING
	AplParamSceneFileSceneDataMenu,	//SCENE FILE SETTING > SCENE DATA
	AplParamSceneFileBlackMenu,	//SCENE FILE SETTING > BLACK
	AplParamSceneBlackMasterPedestal,	//BLACK M. PED
	AplParamSceneFileGamutMenu,	//SCENE FILE SETTING > GAMUT
	AplParamSceneGamutSelect,	//GAMUT SELECT
	AplParamSceneFileGammaMenu,	//SCENE FILE SETTING > GAMMA
	AplParamSceneGammaSelect,	//GAMMA SELECT
	AplParamSceneFileKneeMenu,	//SCENE FILE SETTING > KNEE
	AplParamSceneKneeSwitch,	//KNEE SW
	AplParamSceneFileHlgKneeMenu,	//SCENE FILE SETTING > HLG KNEE
	AplParamSceneHlgKneeMode,	//HLG KNEE MODE
	AplParamSceneFileWhiteClipMenu,	//SCENE FILE SETTING > WHITE CLIP
	AplParamSceneFileDetailMenu,	//SCENE FILE SETTING > DETAIL
	AplParamSceneFileSkinDetailMenu,	//SCENE FILE SETTING > SKIN DETAIL
	AplParamSceneSkinDetail1,	//SKIN DETAIL 1
	AplParamSceneSkinDetail2,	//SKIN DETAIL 2
	AplParamSceneSkinDetail3,	//SKIN DETAIL 3
	AplParamSceneFileChromaMenu,	//SCENE FILE SETTING > CHROMA
	AplParamSceneFileMatrixMenu,	//SCENE FILE SETTING > MATRIX
	AplParamSceneMatrixSwitch,	//MATRIX SW
	AplParamSceneFileColorCorrectionMenu,	//SCENE FILE SETTING > COLOR CORRECTION
	AplParamSceneColorCollectionSwitch,	//COLOR COLLECTION SW
	AplParamSceneColorCollection_P1_SUN,	//COLOR COLLECTION P1 (SAT)
	AplParamSceneColorCollection_P1_PHASE,	//COLOR COLLECTION P1 (PHASE)
	AplParamSceneColorCollection_P2_MON,	//COLOR COLLECTION P2 (SAT)
	AplParamSceneColorCollection_P2_PHASE,	//COLOR COLLECTION P2 (PHASE)
	AplParamSceneColorCollection_P3_TUE,	//COLOR COLLECTION P3 (SAT)
	AplParamSceneColorCollection_P3_PHASE,	//COLOR COLLECTION P3 (PHASE)
	AplParamSceneColorCollection_Yl_WED,	//COLOR COLLECTION Yl (SAT)
	AplParamSceneColorCollection_P4_THU,	//COLOR COLLECTION P4 (SAT)
	AplParamSceneColorCollection_P4_PHASE,	//COLOR COLLECTION P4 (PHASE)
	AplParamSceneColorCollection_P5_FRI,	//COLOR COLLECTION P5 (SAT)
	AplParamSceneColorCollection_P5_PHASE,	//COLOR COLLECTION P5 (PHASE)
	AplParamSceneColorCollection_P6_SUN,	//COLOR COLLECTION P6 (SAT)
	AplParamSceneColorCollection_P6_PHASE,	//COLOR COLLECTION P6 (PHASE)
	AplParamSceneColorCollection_Cy_MON,	//COLOR COLLECTION Cy (SAT)
	AplParamSceneColorCollection_P7_TUE,	//COLOR COLLECTION P7 (SAT)
	AplParamSceneColorCollection_P7_PHASE,	//COLOR COLLECTION P7 (PHASE)
	AplParamSceneColorCollection_B_WED,	//COLOR COLLECTION B (SAT)
	AplParamSceneColorCollection_P8_THU,	//COLOR COLLECTION P8 (SAT)
	AplParamSceneColorCollection_P8_PHASE,	//COLOR COLLECTION P8 (PHASE)
	AplParamSceneColorCollection_Mg_FRI,	//COLOR COLLECTION Mg (SAT)
	AplParamSceneColorCollection_P9_SAT,	//COLOR COLLECTION P9 (SAT)
	AplParamSceneColorCollection_P9_PHASE,	//COLOR COLLECTION P9 (PHASE)
	AplParamSceneColorCollection_P10_SUN,	//COLOR COLLECTION P10 (SAT)
	AplParamSceneColorCollection_P10_PHASE,	//COLOR COLLECTION P10 (PHASE)
	AplParamRecSettingMenu,	//REC SETTING
	AplParamCardsMediaMenu,	//REC SETTING > CARDS/MEDIA
	AplParamTCMenu,	//REC SETTING > TC
	AplParamCounterMode,	//�J�E���^�[�\���ؑ� (TC/UB/Dur )
	AplParamAudioSettingsMenu,	//AUDIO SETTINGS
	AplParamInSelectCH1,	//CH1 IN SELECT
	AplParamInSelectCH2,	//CH2 IN SELECT
	AplParamSelInput1,	//�������͐M���ݒ�1
	AplParamSelInput2,	//�������͐M���ݒ�2
	AplParamMicPower1,	//�O���}�C�N�d���ؑ�1
	AplParamMicPower2,	//�O���}�C�N�d���ؑ�2
	AplParamHpMode,	//<PHONES>�[�q����o�͂��鉹�������j�^�[�o�͂ɍ��킹�Ēx�������邩�ǂ���
	AplParamVolume,	//<PHONES>�[�q����o�͂��鉹�����x��
	AplParamRecBeepSoundMenu,	//AUDIO SETTINGS > REC BEEP SOUND
	AplParamRecBeepSoundMode,	//Recbeep�����[�h
	AplParamRecBeepVolume,	//Recbeep����
	AplParamOutputSettingMenu,	//OUTPUT SETTING
	AplParamSdiOutSignalSelect,	//SDI�[�q����̏o�͐M���I��
	AplParamSdiOutIndicatorDisp,	//SDI�[�q����̏o�͂�[SDI/HDMI INDICATOR]�Őݒ肷�鍀�ڂ̕\����\��
	AplParamSdiOutMarkerDisp,	//SDI�[�q����̏o�͂�[SDI/HDMI MARKER]�Őݒ肷�鍀�ڂ̕\����\��
	AplParamSdiOutMenuDisp,	//SDI�[�q����̏o�͂Ƀ��j���[�̕\����\��
	AplParamHdmiOutSignalSelect,	//HDMI�[�q����̏o�͐M���I��
	AplParamHdmiOutIndicatorDisp,	//HDMI�[�q����̏o�͂�[SDI/HDMI INDICATOR]�Őݒ肷�鍀�ڂ̕\����\��
	AplParamHdmiOutMarkerDisp,	//HDMI�[�q����̏o�͂�[SDI/HDMI MARKER]�Őݒ肷�鍀�ڂ̕\����\��
	AplParamHdmiOutMenuDisp,	//HDMI�[�q����̏o�͂Ƀ��j���[�̕\����\��
	AplParamOutIndicatorMenu,	//OUTPUT SETTING > SDI/HDMI INDICATOR
	AplParamOutIndicatorCharLuminance,	//�L�����N�^�[�̋P�x��ݒ�
	AplParamOutIndicatorClipName,	//�L�^Clip��
	AplParamOutIndicatorPixcelFreq,	//�V�X�e���s�N�Z������ю��g��
	AplParamOutIndicatorMainColor,	//MAIN�L�^�J���[�ݒ�
	AplParamOutIndicatorRecFormat,	//MAIN�L�^�t�H�[�}�b�g
	AplParamOutIndicatorSlotStatus,	//SD�J�[�h�X���b�g���
	AplParamOutIndicator2SlotFunc,	//2�X���b�g�@�\���
	AplParamOutIndicatorTC,	//�^�C���R�[�h
	AplParamOutIndicatorBatteryRemain,	//�o�b�e���[�c�ʃA�C�R��
	AplParamOutIndicatorRecFuncMode,	//�L�^�@�\���
	AplParamOutIndicatorRecRemote,	//SDI/HDMI�o�͂ւ�REC�w�����
	AplParamOutIndicatorAudioLevelMeter,	//�I�[�f�B�I���x�����[�^
	AplParamOutIndicatorFps,	//�t���[�����[�g
	AplParamOutIndicatorShutter,	//�V���b�^�[���x����
	AplParamOutIndicatorEi,	//EI���
	AplParamOutIndicatorWhite,	//�z���C�g�o�����X
	AplParamOutIndicatorIrisZoom,	//EF�����Y��IRIS/ZOOM���
	AplParamOutIndicatorNdFilter,	//ND�t�B���^�[
	AplParamOutIndicatorEIS_DZOOM,	//EIS�����DZOOM���
	AplParamOutIndicatorWlan,	//����LAN�ڑ����
	AplParamOutIndicatorIRRec,	//IR REC���[�h
	AplParamOutIndicatorSpotMeter,	//SPOT METER
	AplParamOutIndicatorPlayBackStatus,	//�Đ����
	AplParamOutMarkerMenu,	//OUTPUT SETTING > SDI/HDMI MARKER
	AplParamOutMarkerLuminance,	//�}�[�J�[�̋P�x
	AplParamOutMarkerCenterMarkerType,	//�Z���^�[�}�[�J�[�̐ؑ�
	AplParamOutMarkerSaftyMarkerType,	//�Z�[�t�e�B�[�]�[���̘g�̎��
	AplParamOutMarkerSafetyArea,	//�Z�[�t�e�B�[�]�[���̘g�̑傫��
	AplParamOutMarkerFrameMarker,	//�t���[���}�[�J�[�̉�p
	AplParamOutMarkerFrameMarkerColor,	//�t���[���}�[�J�[�̐F
	AplParamOutMarkerPlayBackMarker,	//SDI/HDMI�[�q����̍Đ��f���o�͂Ƀ}�[�J�\�����邩�ǂ���
	AplParamLcdIndicatorMenu,	//OUTPUT SETTING > LCD INDICATOR
	AplParamLcdIndicatorCharLuminance,	//�L�����N�^�[�̋P�x��ݒ�
	AplParamLcdIndicatorClipName,	//�L�^Clip��
	AplParamLcdIndicatorPixcelFreq,	//�V�X�e���s�N�Z������ю��g��
	AplParamLcdIndicatorMainColor,	//MAIN�L�^�J���[�ݒ�
	AplParamLcdIndicatorTC,	//�^�C���R�[�h
	AplParamLcdIndicatorEi,	//EI���
	AplParamLcdIndicatorIrisZoom,	//EF�����Y��IRIS/ZOOM���
	AplParamLcdIndicatorEIS_DZOOM,	//EIS�����DZOOM���
	AplParamLcdIndicatorSpotMeter,	//SPOT METER
	AplParamLcdMarkerMenu,	//OUTPUT SETTING > LCD MARKER
	AplParamLcdMarkerLuminance,	//�}�[�J�[�̋P�x
	AplParamLcdMarkerPlayBackMarker,	//SDI/HDMI�[�q����̍Đ��f���o�͂Ƀ}�[�J�\�����邩�ǂ���
	AplParamLcdFocusAssistMenu,	//OUTPUT SETTING > LCD FOCUS ASSIST
	AplParamZebra,	//ZEBRA
	AplParamZebraMode,	//ZEBRA MODE
	AplParamLcdFocusExpandPeakSqMode,	//PEAK./SQUARES MODE
	AplParamLcdFocusExpandOpenIrisMode,	//�I�[�v���A�C���X�t�H�[�J�X�A�V�X�g�쓮����
	AplParamLcdEIAssistMenu,	//OUTPUT SETTING > LCD EI ASSIST
	AplParamLcdEIAssistSpotMeterDisp,	//�X�|�b�g���[�^�[�\���P��
	AplParamLcdEIAssistSpotMeterSize,	//�X�|�b�g���[�^�[�\���T�C�Y
	AplParamNetworkSettingsMenu,	//NETWORK SETTING
	AplParamWirelessLanMode,	//�O���@��ƃ��C�����XLAN�Őڑ����邩�ǂ���
	AplParamMyMacAddress,	//������MAC�A�h���X
	AplParamNetworkFuncMenu,	//NETWORK SETTING > NETWORK FUNC
	AplParamUserAccountMode,	//�l�b�g���[�N�F�؂Ŏg�p���郆�[�U�A�J�E���g
	AplParamNetworkPropertyMenu,	//NETWORK SETTING > NETWORK PROPERTY
	AplParamNetworkToolMenu,	//OPTION
	AplParamUserAccountMenu,	//NETWORK SETTINGS>NETWORK FUNC>USER ACCOUNT
	AplParamConnectionHistoryMenu,	//NETWORK SETTINGS>CONNECTION HISTORY
	AplParamOptionMenu,	//OPTION
	AplParamVerDown,	//�o�[�W�����_�E����̏����ݒ�
	AplParamRepeat,	//���s�[�g�Đ�
	AplParamFileNumberReset_HDD_SDP,	//�t�@�C���ԍ����Z�b�g (HDD/���������� SDP)
	AplParamFileNumberReset_HDD_MP4,	//�t�@�C���ԍ����Z�b�g (HDD/���������� MP4)
	AplParamFileNumberReset_SD_SDP,	//�t�@�C���ԍ����Z�b�g (SD �J�[�h SDP)
	AplParamFileNumberReset_SD_MP4,	//�t�@�C���ԍ����Z�b�g (SD �J�[�h MP4)
	AplParamJpegFileNo,	//�Î~��L�^�t�@�C���i���o�[(SD)
	AplParamFolderNumber,	//�Î~��L�^�t�H���_�i���o�[(SD)
	AplParamHDD_JpegFileNo,	//�Î~��L�^�t�@�C���i���o�[(HDD)
	AplParamHDD_FolderNumber,	//�Î~��L�^�t�H���_�i���o�[(HDD)
	AplParamUsbMode,	//USB���[�h
	AplParamUsbSW,	//USB���A��
	AplParamPowerOffOperation,	//�d��OFF����
	AplParamSuperGainSet,	//�X�[�p�[�Q�C��
	AplParamSuperGainIso,	//�X�[�p�[�Q�C��(ISO�\��)
	AplParamSuperGainIsoSet,	//�X�[�p�[�Q�C��������(ISO�\��)
	AplParamSensitivityExtension,	//���x�g��
	AplParamFocusMode,	//�`�e�^�l�e�؊� �i�t�H�[�J�X�ؑցj
	AplParamShutterMode,	//�d�q�V���b�^�[���x
	AplParamSynchroScanMode,	//�V���N���X�L�������[�h
	AplParamIrisMode,	//�i��
	AplParamGainMode,	//�Q�C��
	AplParamGainSW,	//�Q�C���X�C�b�`(AplCam�o�b�N�A�b�v�p)
	AplParamGainModeISO,	//�Q�C��ISO
	AplParamWhiteBalanceMode,	//�z���C�g�o�����X
	AplParamWbSemiPro,	//�z���C�g�o�����X(�Ɩ��p)
	AplParamWbMnlSemiPro,	//�z���C�g�o�����X�}�j���A���ݒ�(�Ɩ��p)
	AplParamWhiteBalanceSetInfoA,	//�z���C�g�o�����X�Z�b�g�̌��ʏ��@A
	AplParamWhiteBalanceSetInfoB,	//�z���C�g�o�����X�Z�b�g�̌��ʏ��@B
	AplParamWhiteBalanceChannel,	//�z���C�g�o�����X Ach / Bch
	AplParamVar,	//VAR���[�h�@�F���x�w��
	AplParamWBPreSet,	//WB�v���Z�b�g
	AplParamMasterDetailPro,	//�}�X�^�[�f�B�e�[���i�Z�~�v���p�j
	AplParamDetailCoringPro,	//�f�B�e�[���@�R�A�����O�i�Z�~�v���p�j
	AplParamMasterPedestalPro,	//�}�X�^�[�y�f�X�^���@��ʁi�Z�~�v���p�j
	AplParamChromaLevelPro,	//�N���}���x���i�Z�~�v���p�j
	AplParamGammaPro,	//�K���}���[�h(�Z�~�v���p)
	AplParamBlackGamma,	//���K���}
	AplParamBlackGammaRange,	//���K���}��
	AplParamKneeMode,	//�j�[���[�h
	AplParamKneeMasterPoint,	//�j�[�}�X�^�[�|�C���g�@��ʁi�Z�~�v���p�j
	AplParamKneeMasterSlope,	//�j�[�}�X�^�[�X���[�v
	AplParamSkinToneDtl,	//�X�L���f�B�e�[��
	AplParamVDetailLevel,	//V �f�B�e�[��
	AplParamAutoIrisLevelEffect,	//�I�[�g�A�C���X���x��
	AplParamAutoIrisLevelEffectValue,	//�I�[�g�A�C���X���x������
	AplParamDRS,	//DRS
	AplParamNrControl,	//NR�R���g���[��
	AplParamKneeApeLevel,	//�j�[APE���x��
	AplParamDetailLevel,	//�f�B�e�[�����x��
	AplParamAFConformity,	//AF�Ǐ]�ݒ�
	AplParamAFRangeValue,	//AF�G���A��(��ʃo�C�g)
	AplParamAfAreaWidth,	//AF AREA WIDTH�i�폜�\��j
	AplParamOpeningAngle,	//�J�p�x(��ʃo�C�g)
	AplParamIsoLow,	//ISO Low
	AplParamIsoMid,	//ISO Mid
	AplParamIsoHigh,	//ISO High
	AplParamAgcMaxISO,	//AGC�@MAX�@ISO
	AplParamWFM,	//WFM
	AplParamWFMPos,	//WFM�ʒu
	AplParamDispModeCheck,	//DISP MODE �{�^����ԕێ�
	AplParamSubRecButton,	//�T�u REC �{�^��
	AplParamSubZoom,	//�T�u�Y�[��
	AplParamToggleButtonWb,	//�g�O���{�^���@WB
	AplParamToggleButtonGain,	//�g�O���{�^���@�Q�C��
	AplParamMicLevelValue,	//�}�C�N���x���l
	AplParamAvComponent,	//�R���|�[�l���g/AV�o�͐؂�ւ�
	AplParamPowerLcd_Auto,	//�p���[ LCD Auto �ݒ�
	AplParamBalanceShot,	//�X���␳
	AplParamDirectRec,	//DirectRec
	AplParamReStartMode,	//�V�X�e�����Z�b�g��̋N�����[�h
	AplParamLcdEvf,	//LCD/EVF
	AplParamDualCodecRec,	//�f���A���R�[�f�b�N�L�^
	AplParamPlayContent,	//�Đ��ΏۃR���e���c
	AplParamMovieAspect,	//ASPECT
	AplParamVLogMode,	//V-LOG���[�h
	AplParamAreaSize,	//�G���A�@�\�@�g�T�C�Y
	AplParamSafetyZone,	//�Z�[�t�e�B�]�[���̈�\�����( �A�X�y�N�g�� 16:9 )
	AplParamSafetyZone_4_3,	//�Z�[�t�e�B�]�[���̈�\��( �A�X�y�N�g�� 4:3 )
	AplParamVideoOutOsd,	//OSD �\���Ɖf���Ƃ̓����o��
	AplParamAudioAlcLinked,	//�I�[�f�B�IALC�A��
	AplParamAudioAlcCH1,	//�I�[�f�B�IALC1
	AplParamAudioAlcCH2,	//�I�[�f�B�IALC2
	AplParamVFRFps60p,	//VFR FPS(59.94Hz 60p) 
	AplParamVFRFps30p,	//VFR FPS(59.94H 30p) 
	AplParamVFRFps24p,	//VFR FPS(59.94Hz 24p) 
	AplParamVFRFps50p,	//VFR FPS(50.00Hz 50p) 
	AplParamVFRFps25p,	//VFR FPS(50.00Hz 25p) 
	AplParamDummyMenu,	//���j���[�؂蕪��
	AplParam3DAdaptor,	//�i�폜���j3D �A�_�v�^�[����
	AplParam3DDisplay,	//�i�폜���j3D �e���r�o��
	AplParam3DOutput,	//�i�폜���j3D �摜�o�͑I��
	AplParam2D3DViewRec,	//�i�폜���j2D/3D�\�� (�B�e���[�h)
	AplParam2D3DViewPlay,	//�i�폜���j2D/3D�\�� (�Đ����[�h)
	AplParam3D2DRecMode,	//�i�폜���j3D / 2D �B�e���[�h�̐ؑւ�
	AplParamConv2DTo3D,	//�i�폜���j2D �� 3D �ϊ�
	AplParamPlay3DWarning,	//�i�폜���j�Đ����[�h�F3D�x���\��
	AplParamPlayLcd3DOutput,	//�i�폜���j�t���\�����[�h - 3D (�Đ����[�h)
	AplParamLcd2DOutput,	//�i�폜���j�t���\�����[�h - 2D
	AplParamPanAngle,	//�i�폜���j��]�p�x
	AplParamTiltAngle,	//�i�폜���j�`���g�p�x
	AplParamTiltSpeed,	//�i�폜���j�`���g���x
	AplParamPanTilterMode,	//�i�폜���j�����[�g�p���`���^�[���[�h
	AplParamPanTilterVerUpResult,	//�i�폜���j�p���`���^�[�o�[�W�����A�b�v����
	AplParamPanTilterAutoConnectFlag,	//�i�폜���j�p���`���^�[�����ڑ��t���O
	AplParamTRFCurrentPagePlay,	//�i�폜���jTRF �y�[�W�ێ� (�Đ��A�v��)
	AplParamDioramaExposure,	//�i�폜���j���邳(�W�I���})
	AplParam8mmExposure,	//�i�폜���j���邳(8mm)
	AplParamSilentExposure,	//�i�폜���j���邳(�T�C�����g)
	AplParamDioramaVividness,	//�i�폜���j�N�₩��(�W�I���})
	AplParamEffect,	//�i�폜���j����G�t�F�N�g(�I��)
	AplParam8mmShade,	//�i�폜���j�F����(8mm)
	AplParamFaceRecognition,	//�i�폜���j�l�F��
	AplParamRecognitionNum,	//�i�폜���j���O�\�� (�l�F�ؕ\���l��)
	AplParamEyeFiTransfer,	//�i�폜���jEye-Fi�]��
	AplParamEyeFiFileSize,	//�i�폜���jEye-Fi�t�@�C���T�C�Y
	AplParamEyeFiPowerControl,	//�i�폜���jEye-Fi�d���Ǘ�
	AplParamWifiSetConfirm,	//�i�폜���jWi-Fi�ݒ�U���t���O
	AplParamWifiMenuApSetConfirm,	//�i�폜���jWi-Fi���j���[ AP�ݒ�U���t���O
	AplParamSubCamWb,	//�i�폜���j�T�u�J���� WB
	AplParamSubCamFocus,	//�i�폜���j�T�u�J���� �t�H�[�J�X
	AplParamSubCamExposure,	//�i�폜���j�T�u�J���� ���邳����
	AplParamSubCamPower,	//�i�폜���j�T�u�J���� �d��
	AplParamSubCamWipePos,	//�i�폜���j�T�u�J���� ���C�v�ʒu
	AplParamSoundSceneSelect,	//�i�폜���j�T�E���h�V�[���Z���N�g
	AplParamSoundSceneSelectGain,	//�i�폜���j�T�E���h�V�[���Z���N�g�@�Q�C��
	AplParamSoundSceneSelectDirectivity,	//�i�폜���j�T�E���h�V�[���Z���N�g�@�w����
	AplParamSoundSceneSelectFrequencyHigh,	//�i�폜���j�T�E���h�V�[���Z���N�g�@F��-����
	AplParamSoundSceneSelectFrequencyLow,	//�i�폜���j�T�E���h�V�[���Z���N�g�@F��-���
	AplParamAeMode,	//�i�폜���j�V�[�����[�h
	AplParamTimeLapseAeMode,	//�i�폜���j�V�[�����[�h(�C���^�[�o���L�^��p)
	AplParamTitlePictureSetup,	//�i�폜���j���[�r�[�X���C�h�V���[�u�^�C�g���ݒ�v
	AplParamFavoriteScenePlay,	//�i�폜���j���[�r�[�X���C�h�V���[�u���C�ɓ���V�[���Đ��v
	AplParamBabyCalendar,	//�i�폜���j�x�r�[�J�����_�[
	AplParamLastDispBaby,	//�i�폜���j�x�r�[�J�����_�[�@�ŏI�\��
	AplParamAnimationAssist,	//�i�폜���j�p���p���ʐ^���[�h
	AplParamHighSpeedMode,	//�i�폜���j�����B�����[�h
	AplParamSlowRecSetting,	//�i�폜���j�X�[�p�[�X���[�B�e�ݒ�
	AplParamSlowPlaySetting,	//�i�폜���j�X���[��ԍĐ����x
	AplParamBurstShooting,	//�i�폜���j�����A��
	AplParamLoopRec,	//�i�폜���j���[�v�L�^
	AplParamLoopRecAudio,	//�i�폜���j���[�v�L�^����
	AplParamAudioRec,	//�i�폜���j�����L�^
	AplParamTimeLapse,	//�i�폜���j�C���^�[�o���L�^�i�^�C�����v�X�j
	AplParam24PMode,	//�i�폜���j�f�W�^���V�l�}
	AplParamDCIMode,	//�i�폜���j�f�W�^���V�l�}�J���[(DCC)
	AplParamMicChannel,	//�i�폜���j5.1ch/2ch
	AplParamMicLevel,	//�i�폜���j�}�C�N���x��
	AplParamMicLevelAgc,	//�i�폜���j�}�C�N���x���ݒ� (AGC)
	AplParamZoomMic,	//�i�폜���j�Y�[���}�C�N
	AplParamMicMode,	//�i�폜���j�}�C�N�ݒ�
	AplParamBassEnphasis,	//�i�폜���j�o�X�R���g���[��
	AplParamWindNoiseCanceller,	//�i�폜���j�����L�����Z���[
	AplParamExtMicWarning,	//�i�폜���j�O���}�C�N�x���\��
	AplParamPictureExposureCorection,	//�i�폜���j�掿����(���邳)
	AplParamPictureDetail,	//�i�폜���j�掿����(�V���[�v�l�X)
	AplParamPictureColorLevel,	//�i�폜���j�掿����(�F�̔Z��)
	AplParamWBAdjustB,	//�i�폜���j�掿����(WB������)BC��
	AplParamWBAdjust,	//�i�폜���j�掿����(WB������)
	AplParamIAPlusExposure,	//�i�폜���j���邳(iA+)
	AplParamIAPlusWBAdjust,	//�i�폜���jWB����(iA)
	AplParamiAMode,	//�i�폜���j���܂���IA
	AplParamMenuIAPlus,	//�i�폜���j�C���e���W�F���g�I�[�g�v���X(iA+)
	AplParamOisCustomize,	//�i�폜���j��u���␳�J�X�^�}�C�Y
	AplParamOisEffectMode,	//�i�폜���j��U��␳���ʃ��[�h
	AplParamMenuOisMode,	//�i�폜���j��u���␳���[�h�i���j���[�ݒ荀�ځj
	AplParamAutoAFAE,	//�i�폜���j�ǂ������t�H�[�J�XON/OFF
	AplParamLedMode,	//�i�폜���j�r�f�I���C�g (LED���C�g)
	AplParamModulateVideoLightMode,	//�i�폜���j�����r�f�I���C�g���[�h
	AplParamFlashMode,	//�i�폜���j�t���b�V��
	AplParamFlashQuantityMode,	//�i�폜���j�t���b�V�����邳
	AplParamRedEyeMode,	//�i�폜���j�Ԗڌy��
	AplParamAFLightMode,	//�i�폜���jAF�⏕��
	AplParamContrastRevise,	//�i�폜���j�R���g���X�g���o�␳
	AplParamDarkRevise,	//�i�폜���j�Õ��␳
	AplParamFade,	//�i�폜���j�t�F�[�h
	AplParamFadeColor,	//�i�폜���j�t�F�[�h�F
	AplParamSlowShutter,	//�i�폜���j�I�[�g�X���[�V���b�^�[ (�ʏ�)
	AplParamBackLight,	//�i�폜���j�t���␳
	AplParamBackLightForBackUp,	//�i�폜���j�t���␳�i�o�b�N�A�b�v�L��j
	AplParamTelmacro,	//�i�폜���j�e���}�N��
	AplParamNightMode,	//�i�폜���j�i�C�g���[�h
	AplParamIRLight,	//�i�폜���j�ԊO�����C�g
	AplParamSelfTimer,	//�i�폜���j�Z���t�^�C�}�[
	AplParamCursorAutoMove,	//�i�폜���j�����J�[�\�������ړ�
	AplParamPrevRecMode,	//�i�폜���j�O��̎B�e���[�h
	AplParamRecPowerOffOperation,	//�i�폜���j�L�^���[�h�̓d��OFF����
	AplParamOsdMode,	//�i�폜���j��ʕ\��
	AplParamExtDisplay,	//�i�폜���j�O���o�͕\��
	AplParamDispFaceFrame,	//�i�폜���j�猟�o�g�\��
	AplParamRecGridLine,	//�i�폜���j�B�e�K�C�h���C��
	AplParamPlayGuideLine,	//�i�폜���j�Đ��K�C�h���C��
	AplParamLuminance,	//�i�폜���j�P�x�\��
	AplParamHistogram,	//�i�폜���j�q�X�g�O�����\��
	AplParamUserButtonDisplay,	//�i�폜���jUSER �{�^���\��
	AplParamOtherDisplay,	//�i�폜���j���̑����̕\��
	AplParamCardAndBattery,	//�i�폜���j�J�[�h�L�^�Z�e�ʁE�o�b�e���[�}�[�N�\��
	AplParamLensStatus,	//�i�폜���j�����Y���\��
	AplParamAudioLevelMeter,	//�i�폜���j�I�[�f�B�I���x�����[�^�[
	AplParamLevelMeter,	//�i�폜���j�I�[�f�B�I���x�����[�^�[�\��
	AplParamLensCoverWarning,	//�i�폜���j�����Y�J�o�[�x���\��
	AplParamDateOsdMode,	//�i�폜���j�����\��
	AplParamWarningSoundMode,	//�i�폜���j���m�点��
	AplParamShutterSoundMode,	//�i�폜���j�V���b�^�[��
	AplParamAgs,	//�i�폜���j��������B��h�~
	AplParamRimoconEnable,	//�i�폜���j�����R��
	AplParamDemoMode,	//�i�폜���j�f�����[�h
	AplParamRecNaviMode,	//�i�폜���j�B�e�A�V�X�g
	AplParamMmr,	//�i�폜���j�}���`�}�j���A�������O
	AplParamPowerSave,	//�i�폜���j�G�R���[�h (�o�b�e��)
	AplParamPowerSaveAC,	//�i�폜���j�G�R���[�h (AC)
	AplParamPowerSaveACTime,	//�i�폜���j�G�R���[�h (AC) �ݒ莞�� (��)
	AplParamBootCamp,	//�i�폜���j�N�C�b�N�p���[�I��(�N������)
	AplParamEvfBrightnessLevel,	//�i�폜���jEVF ���邳�ݒ�
	AplParamEvfExposure,	//�i�폜���jEVF����(���邳)
	AplParamNormalTv,	//�i�폜���j�ڑ�����e���r
	AplParamVideoOutput,	//�i�폜���jVIDEO�o��
	AplParamHdmiUhdOutputLimit,	//�i�폜���jHDMI UHD�o�͐���
	AplParamVideoSetup,	//�i�폜���j�r�f�I�Z�b�g�A�b�v
	AplParamConponent,	//�i�폜���j�R���|�[�l���g�o��
	AplParamHdmiControl,	//�i�폜���j�r�G�������N(VIERA�@Link)
	AplParamWTHomeArea,	//�i�폜���j���[���h�^�C���ݒ�n�� (�z�[��)
	AplParamWorldTimeInitialize,	//�i�폜���j���[���h�^�C�� �����ݒ�t���O
	AplParamWTHomeSummerTime,	//�i�폜���j���[���h�^�C���@�z�[���T�}�[�^�C��
	AplParamWTTravelSummerTime,	//�i�폜���j���[���h�^�C���@���s��T�}�[�^�C��
	AplParamClockLinkedSet,	//�i�폜���j�T�}�[�^�C�����v�A���ݒ�
	AplParamPlayEffect,	//�i�폜���j�Đ� - ���ʐݒ�
	AplParamMovieSlideshowEffectKind,	//�i�폜���j�n�C���C�g�Đ��u�Đ����ʁv
	AplParamHighLightPlayTime,	//�i�폜���j�n�C���C�g�Đ�����
	AplParamSlideshowPlaySet,	//�i�폜���j�ʐ^�X���C�h�V���[�u�Đ��ݒ�v
	AplParamSlideShowInterval,	//�i�폜���j�X���C�h�V���[�Ԋu
	AplParamBgmInfo,	//�i�폜���j���y(BGM)
	AplParamMnlBgmInfo,	//�i�폜���j���y(BGM) �}�j���A�����[�r�[�X���C�h�V���[�p
	AplParamFilmRoll,	//�i�폜���j�t�B�������[���Ԋu
	AplParamFilmRoleRequestedMinutes,	//�i�폜���j�t�B�������[���Ԋu�w�莞�ԁi���j
	AplParamPinPDisplay,	//�i�폜���jPinP�\��
	AplParamPinPPosition,	//�i�폜���jPinP�\���ʒu
	AplParamPinPSize,	//�i�폜���j�q��ʋ@�\
	AplParamOsdOffWithTally,	//�i�폜���j�^���[�_�����\��
	AplParamRemoconID,	//�i�폜���j�ԊO�������R��ID
	AplParamZoomSpeed,	//�i�폜���j�Y�[�����x(AW-RP50�@�����R��)
	AplParamHDCom60SecStandby,	//�i�폜���jHD�R��60�b�X�^���o�C
	AplParamSelfReset,	//�i�폜���j�Z���t���Z�b�g
	AplParamExposureCorectionControl,	//�i�폜���j�R���g���X�g����
	AplParamIntermittentCapture,	//�i�폜���j�Ԍ��ʐ^�L�^
	AplParamAngleOfView,	//�i�폜���j��p���[�h(�E�F�A���u��)
	AplParamWearableRecMode,	//�i�폜���j�B�e���[�h(�E�F�A���u��)
	AplParamTallyLedMode,	//�i�폜���j�B�e�����v�i�������f���p�j
	AplParamRecLamp,	//�i�폜���j�B�e�����v�i�Ɩ����f���p�j
	AplParamSystemFrequencyEngineerFlag,	//�i�폜���j�f�o�b�O�V�X�e�����g���؊��t���O
	AplParamSystemFrequencyVisiblity,	//�i�폜���j24P���[�h�؊�(�V�X�e�����g�����j���[�\��)
	AplParam4KUpdate,	//�i�폜���j2UHD���j���[�\���t���O�i�f�o�b�O�p�j
	AplParamDebugMode,	//�i�폜���j�f�o�b�O���
	AplParamDummyEnum1,	//�i�폜���j�R���p�C���p�̃_�~�[ENUM
	AplParamDummyEnum2,	//�i�폜���j�R���p�C���p�̃_�~�[ENUM
	AplParamDummyEnum3,	//�i�폜���j�R���p�C���p�̃_�~�[ENUM
	AplParamImageResolution,	//�i�폜���j�摜�𑜓x
	AplParamAspect,	//�i�폜���j�摜���c�� �i�A�X�y�N�g��j
	AplParamPictureSize,	//�i�폜���j�i����j
	AplParamPictureSize_16_9,	//�i�폜���j�L�^��f���i�ʐ^ 16:9�j
	AplParamPictureSize_3_2,	//�i�폜���j�i�ʐ^ 3:2�j
	AplParamPictureSize_4_3,	//�i�폜���j�L�^��f���i�ʐ^ 4:3�j
	AplParamJpegQuality,	//�i�폜���j�N�I���e�B (�ʐ^�掿)   �y12�t�ł̓��j���[���z
	AplParam60PMode,	//�i�폜���j60P���[�h(�{�^��)
	AplParamRecModeMP4,	//�i�폜���j�L�^�����iPC�t�����h���[�j
	AplParamHDQuality,	//�i�폜���j�L�^���[�h�iHD�j
	AplParamMP4Quality,	//�i�폜���j�L�^���[�h�iMP4�j
	AplParamOutBits,	//�i�폜���j�o�̓r�b�g��
	AplParam2DRecMode59Hz,	//�i�폜���j2D �L�^�t�H�[�}�b�g (59.9 Hz �p)
	AplParam2DRecMode50Hz,	//�i�폜���j2D �L�^�t�H�[�}�b�g (50.0 Hz �p)
	AplParamHDQuality59Hz,	//�i�폜���j[59.9 Hz �p]AVCHD
	AplParamHDQuality50Hz,	//�i�폜���j[50 Hz �p]AVCHD
	AplParamMP4Quality59Hz,	//�i�폜���j[59.9 Hz �p]MP4
	AplParamMP4Quality50Hz,	//�i�폜���j[50 Hz �p]MP4
	AplParamMP4LPCMQuality59Hz,	//�i�폜���j[59.9 Hz �p]MP4(LPCM)
	AplParamMP4LPCMQuality50Hz,	//�i�폜���j[50 Hz �p]MP4(LPCM)
	AplParamMOVLPCMQuality59Hz,	//�i�폜���j[59.9 Hz �p]MOV(LPCM)
	AplParamMOVLPCMQuality50Hz,	//�i�폜���j[50 Hz �p]MOV(LPCM)
	AplParamRecFormat59Hz_OutBits_10Bit,	//�i�폜���j�B�e�t�H�[�}�b�g�iNTSC�j �o�̓r�b�g���@10Bit�p
	AplParamRecFormat50Hz_OutBits_10Bit,	//�i�폜���j�B�e�t�H�[�}�b�g�iPAL�j �o�̓r�b�g���@10Bit�p
	AplParamDigitalZoomMode,	//�i�폜���j�Y�[�����[�h
	AplParamDigitalZoomVal,	//�f�W�^���Y�[��
	AplParamSubZoomSemiPro,	//�i�폜���j�T�u�Y�[��(�Ɩ��p)
	AplParamEnableFastZoom,	//Fast Zoom
	AplParamShakeAmplitude,	//�i�폜���j�u���U��
	AplParamShakeFrequency,	//�i�폜���j�u�����g��
	AplParamFocusTransition1,	//�i�폜���j�t�H�[�J�X�g�����W�V�����o�^1
	AplParamFocusTransition2,	//�i�폜���j�t�H�[�J�X�g�����W�V�����o�^2
	AplParamFocusTransition3,	//�i�폜���j�t�H�[�J�X�g�����W�V�����o�^3
	AplParamFocusTransitionRec,	//�i�폜���j�t�H�[�J�X�g�����W�V�������b�N
	AplParamFocusTransitionWait,	//�i�폜���j�t�H�[�J�X�g�����W�V�����E�G�C�g
	AplParamFocusTransitionTime,	//�i�폜���j�t�H�[�J�X�g�����W�V�����^�C��
	AplParamFocusExpandScale,	//�i�폜���j�t�H�[�J�X�G�L�X�p���h�{��
	AplParamMfAssist,	//�i�폜���jMF�A�V�X�g
	AplParamMfAutoAssistMode,	//�i�폜���jMF�A�V�X�g���[�h
	AplParamFocusAssist2,	//�i�폜���j�t�H�[�J�X�A�V�X�g2
	AplParamPeakingColor,	//�i�폜���j�s�[�L���O�F
	AplParamPeakingLevel,	//�i�폜���j�s�[�L���O���x��
	AplParamPeakingFreq,	//�i�폜���j�s�[�L���O���g��
	AplParamFocusRingDrive,	//�i�폜���j�t�H�[�J�X�����O�쓮�؊�
	AplParamFocusRing,	//�i�폜���j�t�H�[�J�X����
	AplParamShutterRing,	//�i�폜���j�V���b�^�[���x����
	AplParamReverseRotationRing,	//�i�폜���j�Y�[�������O�������]
	AplParamAgcMaxUhd,	//�i�폜���jAGC MAX UHD (enum��`(�^��)��AGC MAX�̒�`���g��)
	AplParamIRRecColor,	//�i�폜���j�ԊO���B�e�F
	AplParamIRLightForBackup,	//�i�폜���j�ԊO�����C�g(�o�b�N�A�b�v����)
	AplParamIris,	//�i�폜���j�A�C���X
	AplParamGamma,	//�i�폜���j�K���}�i�폜�\��j
	AplParamWideAngleLensSet,	//�i�폜���j���C�R�������Y�ݒ�
	AplParamLowLux,	//�i�폜���jLowLux
	AplParamMatrix,	//�i�폜���j�}�g���b�N�X
	AplParamChromaPhasePro,	//�i�폜���j�N���}�t�F�[�Y(�Z�~�v���p)
	AplParamCustomAfFunction,	//�i�폜���j�J�X�^��AF�@�\
	AplParamB_B_Mg_Saturation,	//�i�폜���j�J���[�R���N�V����B_B_Mg �ʓx
	AplParamB_B_Mg_Phase,	//�i�폜���j�J���[�R���N�V����B_B_Mg �F��
	AplParamMg_Saturation,	//�i�폜���j�J���[�R���N�V����Mg �ʓx
	AplParamMg_Phase,	//�i�폜���j�J���[�R���N�V����Mg �F��
	AplParamMg_R_Saturation,	//�i�폜���j�J���[�R���N�V����Mg_R �ʓx
	AplParamMg_R_Phase,	//�i�폜���j�J���[�R���N�V����Mg_R �F��
	AplParamR_Saturation,	//�i�폜���j�J���[�R���N�V����R �ʓx
	AplParamR_Phase,	//�i�폜���j�J���[�R���N�V����R �F��
	AplParamR_R_Yl_Saturation,	//�i�폜���j�J���[�R���N�V����R_R_Yl �ʓx
	AplParamR_R_Yl_Phase,	//�i�폜���j�J���[�R���N�V����R_R_Yl �F��
	AplParamB_Mg_Mg_Saturation,	//�i�폜���j�J���[�R���N�V����B_Mg_Mg �ʓx
	AplParamB_Mg_Mg_Phase,	//�i�폜���j�J���[�R���N�V����B_Mg_Mg �F��
	AplParamR_Yl_Yl_Saturation,	//�i�폜���j�J���[�R���N�V����R_Yl_Y �ʓx
	AplParamR_Yl_Yl_Phase,	//�i�폜���j�J���[�R���N�V����R_Yl_Y �F��
	AplParamYl_Saturation,	//�i�폜���j�J���[�R���N�V����Yl �ʓx
	AplParamYl_Phase,	//�i�폜���j�J���[�R���N�V����Yl �F��
	AplParamYl_Yl_G_Saturation,	//�i�폜���j�J���[�R���N�V����Yl_YI_G �ʓx
	AplParamYl_Yl_G_Phase,	//�i�폜���j�J���[�R���N�V����Yl_YI_G �F��
	AplParamG_Saturation,	//�i�폜���j�J���[�R���N�V����G �ʓx
	AplParamG_Phase,	//�i�폜���j�J���[�R���N�V����G �F��
	AplParamG_Cy_Saturation,	//�i�폜���j�J���[�R���N�V����G_Cy �ʓx
	AplParamG_Cy_Phase,	//�i�폜���j�J���[�R���N�V����G_Cy �F��
	AplParamCy_Saturation,	//�i�폜���j�J���[�R���N�V����Cy �ʓx
	AplParamCy_Phase,	//�i�폜���j�J���[�R���N�V����Cy �F��
	AplParamCy_Cy_B_Saturation,	//�i�폜���j�J���[�R���N�V����Cy_Cy_B �ʓx
	AplParamCy_Cy_B_Phase,	//�i�폜���j�J���[�R���N�V����Cy_Cy_B �F��
	AplParamYl_G_G_Saturation,	//�i�폜���j�J���[�R���N�V����Yl_G_G �ʓx
	AplParamYl_G_G_Phase,	//�i�폜���j�J���[�R���N�V����YI_G_G �F��
	AplParamCy_B_B_Saturation,	//�i�폜���j�J���[�R���N�V����Cy_B_B �ʓx
	AplParamCy_B_B_Phase,	//�i�폜���j�J���[�R���N�V����Cy_B_B �F��
	AplParamB_Saturation,	//�i�폜���j�J���[�R���N�V����B �ʓx
	AplParamB_Phase,	//�i�폜���j�J���[�R���N�V����B �F��
	AplParamScene1SynchroScan60p4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(60P) 4K�i���g�p�j
	AplParamScene1SynchroScan50p4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(50P) 4K�i���g�p�j
	AplParamScene1SynchroScan30p4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(30P) 4K�i���g�p�j
	AplParamScene1SynchroScan25p4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(25P) 4K�i���g�p�j
	AplParamScene1SynchroScan24p4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(24P) 4K�i���g�p�j
	AplParamScene1SynchroScanN24p4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(24P native) 4K�i���g�p�j
	AplParamScene1SynchroScan30pSkew4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(30P Skew) 4K�i���g�p�j
	AplParamScene1SynchroScan24pSkew4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(24P Skew) 4K�i���g�p�j
	AplParamScene1SynchroScanN24pSkew4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(24P Skew native) 4K�i���g�p�j
	AplParamScene1SynchroScan25pSkew4K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(25P Skew) 4K�i���g�p�j
	AplParamScene1SynchroScan60p2K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(60P) 2K�i���g�p�j
	AplParamScene1SynchroScan50p2K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(50P) 2K�i���g�p�j
	AplParamScene1SynchroScan30p2K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(30P) 2K�i���g�p�j
	AplParamScene1SynchroScan25p2K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(25P) 2K�i���g�p�j
	AplParamScene1SynchroScan24p2K,	//�i�폜���j�y�V�[��1�ێ��l�z�V���N���X�L����(24P) 2K�i���g�p�j
	AplParamSceneFileName1,	//�i�폜���j�V�[���t�@�C��1�̖��O
	AplParamSceneFileName2,	//�i�폜���j�V�[���t�@�C��2�̖��O
	AplParamSceneFileName3,	//�i�폜���j�V�[���t�@�C��3�̖��O
	AplParamSceneFileName4,	//�i�폜���j�V�[���t�@�C��4�̖��O
	AplParamSceneFileName5,	//�i�폜���j�V�[���t�@�C��5�̖��O
	AplParamSceneFileName6,	//�i�폜���j�V�[���t�@�C��6�̖��O
	AplParamRemoteRecLink,	//�i�폜���j�����[�g�L�^�A��
	AplParamTestToneAdjustment,	//�i�폜���j�e�X�g�g�[������
	AplParamHdmiOutputResolution,	//�i�폜���jHDMI�o�͉𑜓x
	AplParamSdiResolution,	//�i�폜���jSDI�o�͉𑜓x
	AplParamSdiAudioGainChg,	//�i�폜���jSDI �����Q�C���؊�
	AplParamRingLED_Blue,	//�i�폜���j�����OLED(��)
	AplParamRingLED_Red,	//�i�폜���j�����OLED(��)
	AplParamCounterReset,	//�i�폜���j�J�E���^���Z�b�g�v��
	AplParamSpotMeterVal,	//�i�폜���j�P�x�\���l(���g�p�@�폜�\��)
	AplParamSceneCustom,	//�i�폜���j�J�X�^���V�[��
	AplParamSceneSelectModeFlag,	//�i�폜���j�y��ʊO�J�ڎ�����p�t���O�z�V�[���I�����
	AplParamDispZoomFocus,	//�i�폜���j�Y�[��/�t�H�[�J�X
	AplParamDispZoom,	//�i�폜���jZOOM/Focus�\���ݒ� Zoom��
	AplParamDispFocus,	//�i�폜���jZOOM/Focus�\���ݒ� Focus��
	AplParamDns,	//DNS
	AplParamPortNum,	//HTTPd �|�[�g�ԍ�
	AplParamCameraTitle,	//�J�����^�C�g��
	AplParamFriendlyName,	//�t�����h����
	AplParamLastUser,	//�����[�g �ŏI�g�p���[�U�[
	AplParamUserAuth,	//�����[�g ���[�U�F��
	AplParamUserAuthNum,	//�����[�g ���[�U�F�ؐ�
	AplParamUserAuthData1,	//�����[�g ���[�U�F�؏�� �P
	AplParamUstVideoQuality,	//Ustream ����i��
	AplParamUstVideoQuality2,	//Ustream ����i��2
	AplParamCopyRetryTime,	//DIGA�R�s�[ ���g���C����(�b)
	AplParamDetectionArea,	//����� ���m�G���A
	AplParamCareerSenseOn,	//�L�����A�Z���XON臒l
	AplParamCareerSenseOff,	//�L�����A�Z���XOFF臒l
	AplParamDigaCopy,	//WifiMenu DIGA�R�s�[�L������p
	AplParamWiFiOnOff,	//Wi-Fi �L������
	AplParamDns_2nd,	//DNS 2nd
	AplParamDhcp_3rd,	//DHCP 3rd
	AplParamIpAddress_3rd,	//IP �A�h���X 3rd
	AplParamSubnet_3rd,	//�T�u�l�b�g�}�X�N 3rd
	AplParamGateway_3rd,	//�f�t�H���g�Q�[�g�E�F�C 3rd
	AplParamDns_3rd,	//DNS 3rd
	AplParamDnsPrimary_3rd,	//DNS (�v���C�}��) 3rd
	AplParamDnsSecondary_3rd,	//DNS (�Z�J���_��) 3rd
	AplParamHttpServer,	//HTTP�T�[�o�ݒ�
	AplParamHttpServerAccount,	//HTTP�T�[�o�A�J�E���g�ݒ�
	AplParamUserAuthData2,	//�����[�g ���[�U�F�؏�� �Q
	AplParamUserAuthData3,	//�����[�g ���[�U�F�؏�� �R
	AplParamUserAuthData4,	//�����[�g ���[�U�F�؏�� �S
	AplParamUserAuthData5,	//�����[�g ���[�U�F�؏�� �T
	AplParamUserAuthData6,	//�����[�g ���[�U�F�؏�� �U
	AplParamUserAuthData7,	//�����[�g ���[�U�F�؏�� �V
	AplParamUserAuthData8,	//�����[�g ���[�U�F�؏�� �W
	AplParamUserAuthData9,	//�����[�g ���[�U�F�؏�� �X
	AplParamApPriority1,	//AP�ڑ��D�揇�ʂP (AP�ꗗ�ŕ\���������)
	AplParamApPriority2,	//AP�ڑ��D�揇�ʂQ (AP�ꗗ�ŕ\���������)
	AplParamApPriority3,	//AP�ڑ��D�揇�ʂR (AP�ꗗ�ŕ\���������)
	AplParamApLastSelected,	//�Ō��AP�ڑ����ɂ���������(APL_NET_PARAM_AP_PRIORITY)
	AplParamDeviceName,	//DLNA �f�o�C�X�� (DIGA�A�ڂ����񂭂񑊎���H)
	AplParamPcBkupPcName,	//PC�o�b�N�A�b�v PC��
	AplParamPcBkupIpAddress,	//PC�o�b�N�A�b�v IP�A�h���X
	AplParamPcBkupWorkgroupName,	//PC�o�b�N�A�b�v ���[�N�O���[�v��
	AplParamPcBkupFolderName,	//PC�o�b�N�A�b�v ���L�t�H���_��
	AplParamPcBkupUserName,	//PC�o�b�N�A�b�v ���[�U��
	AplParamPcBkupPassword,	//PC�o�b�N�A�b�v �p�X���[�h
	AplParamHistory1,	//�ڑ����� �����P�������C���f�b�N�X�ԍ�
	AplParamHistory2,	//�ڑ����� �����Q�������C���f�b�N�X�ԍ�
	AplParamHistory3,	//�ڑ����� �����R�������C���f�b�N�X�ԍ�
	AplParamHistory4,	//�ڑ����� �����S�������C���f�b�N�X�ԍ�
	AplParamHistory5,	//�ڑ����� �����T�������C���f�b�N�X�ԍ�
	AplParamHistory6,	//�ڑ����� �����U�������C���f�b�N�X�ԍ�
	AplParamHistory7,	//�ڑ����� �����V�������C���f�b�N�X�ԍ�
	AplParamHistory8,	//�ڑ����� �����W�������C���f�b�N�X�ԍ�
	AplParamHistory9,	//�ڑ����� �����X�������C���f�b�N�X�ԍ�
	AplParamHistory10,	//�ڑ����� �����P�O�������C���f�b�N�X�ԍ�
	AplParamHistory11,	//�ڑ����� �����P�P�������C���f�b�N�X�ԍ�
	AplParamHistory12,	//�ڑ����� �����P�Q�������C���f�b�N�X�ԍ�
	AplParamHistory13,	//�ڑ����� �����P�R�������C���f�b�N�X�ԍ�
	AplParamHistory14,	//�ڑ����� �����P�S�������C���f�b�N�X�ԍ�
	AplParamHistory15,	//�ڑ����� �����P�T�������C���f�b�N�X�ԍ�
	AplParamHistory16,	//�ڑ����� �����P�U�������C���f�b�N�X�ԍ�
	AplParamHistory17,	//�ڑ����� �����P�V�������C���f�b�N�X�ԍ�
	AplParamHistory18,	//�ڑ����� �����P�W�������C���f�b�N�X�ԍ�
	AplParamHistory19,	//�ڑ����� �����P�X�������C���f�b�N�X�ԍ�
	AplParamHistory20,	//�ڑ����� �����Q�O�������C���f�b�N�X�ԍ�
	AplParamHistoryLast,	//�Ō�ɂȂ����ڑ������i�O�n�܂�:�O�͖��g�p�j
	AplParamHttpAccountIndex1,	//HTTP�T�[�o�A�J�E���g���1���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex2,	//HTTP�T�[�o�A�J�E���g���2���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex3,	//HTTP�T�[�o�A�J�E���g���3���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex4,	//HTTP�T�[�o�A�J�E���g���4���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex5,	//HTTP�T�[�o�A�J�E���g���5���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex6,	//HTTP�T�[�o�A�J�E���g���6���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex7,	//HTTP�T�[�o�A�J�E���g���7���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex8,	//HTTP�T�[�o�A�J�E���g���8���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex9,	//HTTP�T�[�o�A�J�E���g���9���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountIndex10,	//HTTP�T�[�o�A�J�E���g���10���w���C���f�b�N�X�ԍ�
	AplParamHttpAccountData1,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X1
	AplParamHttpAccountData2,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X2
	AplParamHttpAccountData3,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X3
	AplParamHttpAccountData4,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X4
	AplParamHttpAccountData5,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X5
	AplParamHttpAccountData6,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X6
	AplParamHttpAccountData7,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X7
	AplParamHttpAccountData8,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X8
	AplParamHttpAccountData9,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X9
	AplParamHttpAccountData10,	//HTTP�T�[�o�A�J�E���g���C���f�b�N�X10
	AplParamReconnectTimer,	//�ڑ����s���̍Đڑ��^�C�}�[(�~���b) 0�̎��͉������Ȃ�
	AplParamNetParamVer,	//NetParam�̃o�[�W����
	AplParamCRTKeyUsageState,	//CRT���̎g�p���
	AplParamCRTKey0Size,	//CRT��0�̃T�C�Y
	AplParamCRTKey0GenerateState,	//CRT��0�̐������
	AplParamCRTKey1Size,	//CRT��1�̃T�C�Y
	AplParamCRTKey1GenerateState,	//CRT��1�̐������
	AplParamSelfSignedCertSize,	//���ȏؖ����T�C�Y
	AplParamSelfSignedCertGenerateState,	//���ȏؖ����������
	AplParamCACertSize,	//�T�[�o�[�ؖ����T�C�Y
	AplParamCACertGenerateState,	//�T�[�o�[�ؖ����������
	AplParamIpAddressV6Input,	//WLAN IP�A�h���X(IPv6) ���͕�����
	AplParamGatewayV6Input,	//WLAN �f�t�H���g�Q�[�g�E�F�C(IPv6) ���͕�����
	AplParamDnsPrimaryV6Input,	//WLAN DNS (�v���C�}��)(IPv6) ���͕�����
	AplParamDnsSecondaryV6Input,	//WLAN DNS (�Z�J���_��)(IPv6) ���͕�����
	AplParamLanIpAddressV6Input,	//LAN IP ADDRESS(IPv6) ���͕�����
	AplParamLanGatewayV6Input,	//LAN �f�t�H���g�Q�[�g�E�F�C(IPv6) ���͕�����
	AplParamLanDnsPrimaryV6Input,	//LAN DNS (�v���C�}��)(IPv6) ���͕�����
	AplParamLanDnsSecondaryV6Input,	//LAN DNS (�Z�J���_��)(IPv6) ���͕�����
	AplParamFtpServerAddress,	//FTP�T�[�o�[�A�h���X(�f�B���N�g��������)
	AplParamFtpUserName,	//FTP���[�U�[��
	AplParamFtpPassword,	//FTP�p�X���[�h
	AplParamNtpServerAddress,	//NTP�T�[�o�[�A�h���X
	AplParamPriorityStreamAddr1,	//�D��X�g���[��IP�A�h���X�P
	AplParamPriorityStreamAddr2,	//�D��X�g���[��IP�A�h���X�Q
	AplParamCSRSize,	//�������N�G�X�g�T�C�Y
	AplParamCSRGenerateState,	//�������N�G�X�g�������
	AplParamLastUser2,	//�����[�g �ŏI�g�p���[�U�[ ����p
	AplParamAuthType,	//�F�ؕ���
	AplParamEasyIpLimit,	//IP�ȒP�ݒ�N�����Ԑ���
	AplParamLiveviewJpegFPS,	//JPEG�t���[�����[�g
	AplParamLimitationControlTiltUp,	//�p���`���^���~�b�g Tilt Up
	AplParamLimitationControlTiltDown,	//�p���`���^���~�b�g Tilt Down
	AplParamLimitationControlPanLeft,	//�p���`���^���~�b�g Pan Left
	AplParamLimitationControlPanRight,	//�p���`���^���~�b�g Pan Right
	AplParamLiveviewImageResolution,	//�摜�𑜓x
	AplParamHttpdConnectionType,	//�ڑ����@�ݒ�
	AplParamHttpsPortNum,	//HTTPS�|�[�g�ԍ�
	AplParamIpV6,	//IPv6
	AplParamMaxRtpPacketSize,	//RTP�ő�p�P�b�g�T�C�Y
	AplParamHttpMaxSegmentSize,	//HTTP�ő�Z�O�����g�T�C�Y
	AplParamBandwidthCtrl,	//�l�b�g���[�N�z�M�ʐ���
	AplParamFtpCtrlPortNum,	//FTP����|�[�g�ԍ�
	AplParamFtpMode,	//FTP���[�h
	AplParamUseNtp,	//NTP�g�p
	AplParamNtpServerAddrSetting,	//NTP�T�[�o�[�A�h���X�ݒ�
	AplParamNtpServerPortNum,	//NTP�T�[�o�[�|�[�g�ԍ�
	AplParamNtpAdjustInterval,	//NTP�����擾�Ԋu
	AplParamUpnpAutoPortForwarding,	//UPnP�|�[�g�t�H���[�f�B���O
	AplParamPriorityMode,	//�D�惂�[�h
	AplParamDateTimeDisplay,	//�����\��
	AplParamSummerTime,	//�T�}�[�^�C��
	AplParamSummerTimeStartDate,	//�T�}�[�^�C���J�n����
	AplParamSummerTimeEndDate,	//�T�}�[�^�C���I������
	AplParamAutomaticInstallationSoft,	//�\�t�g�E�F�A�����C���X�g�[��
	AplParamSmootherLiveVideo,	//�f���̃o�b�t�@�����O
	AplParamRecLinkageTally,	//REC�A���^���[
	AplParamInitialDisplayStreamIp,	//�����\���X�g���[��(�D�惂�[�hIP)
	AplParamInitialDisplayStreamIp60p,	//�����\���X�g���[��(�D�惂�[�hIP_60P)
	AplParamInitialDisplayStreamIpHdr,	//�����\���X�g���[��(�D�惂�[�hIP_HDR)
	AplParamInitialDisplayStreamSd,	//�����\���X�g���[��(�D�惂�[�hSD�J�[�h)
	AplParamInitialDisplayStreamSdHdr,	//�����\���X�g���[��(�D�惂�[�hSD�J�[�h_HDR)
	AplParamInitialDisplayStreamUsb,	//�����\���X�g���[��(�D�惂�[�hUSB)
	AplParamInitialDisplayStreamIp4k,	//�����\���X�g���[��(�D�惂�[�hIP 4K)
	AplParamInitialDisplayStreamSd4k,	//�����\���X�g���[��(�D�惂�[�hSD�J�[�h 4K)
	AplParamInitialDisplayStreamUsb4k,	//�����\���X�g���[��(�D�惂�[�hUSB 4K)
	AplParamInitialDisplayStreamHdmi4k,	//�����\���X�g���[��(�D�惂�[�hHDMI 4K)
	AplParamJpegImageInfo1_Ip,	//JPEG�摜���P(�D�惂�[�hIP)
	AplParamJpegImageInfo2_Ip,	//JPEG�摜���Q(�D�惂�[�hIP)
	AplParamJpegImageInfo3_Ip,	//JPEG�摜���R(�D�惂�[�hIP)
	AplParamJpegImageInfo1_Ip60p,	//JPEG�摜���P(�D�惂�[�hIP_60P)
	AplParamJpegImageInfo2_Ip60p,	//JPEG�摜���Q(�D�惂�[�hIP_60P)
	AplParamJpegImageInfo3_Ip60p,	//JPEG�摜���R(�D�惂�[�hIP_60P)
	AplParamJpegImageInfo1_IpHdr,	//JPEG�摜���P(�D�惂�[�hIP_HDR)
	AplParamJpegImageInfo2_IpHdr,	//JPEG�摜���Q(�D�惂�[�hIP_HDR)
	AplParamJpegImageInfo3_IpHdr,	//JPEG�摜���R(�D�惂�[�hIP_HDR)
	AplParamJpegImageInfo1_Sd,	//JPEG�摜���P(�D�惂�[�hSD�J�[�h)
	AplParamJpegImageInfo2_Sd,	//JPEG�摜���Q(�D�惂�[�hSD�J�[�h)
	AplParamJpegImageInfo3_Sd,	//JPEG�摜���R(�D�惂�[�hSD�J�[�h)
	AplParamJpegImageInfo1_SdHdr,	//JPEG�摜���P(�D�惂�[�hSD�J�[�h_HDR)
	AplParamJpegImageInfo2_SdHdr,	//JPEG�摜���Q(�D�惂�[�hSD�J�[�h_HDR)
	AplParamJpegImageInfo3_SdHdr,	//JPEG�摜���R(�D�惂�[�hSD�J�[�h_HDR)
	AplParamJpegImageInfo1_Usb,	//JPEG�摜���P(�D�惂�[�hUSB)
	AplParamJpegImageInfo1_Ip4k,	//JPEG�摜���P(�D�惂�[�hIP 4K)
	AplParamJpegImageInfo2_Ip4k,	//JPEG�摜���Q(�D�惂�[�hIP 4K)
	AplParamJpegImageInfo3_Ip4k,	//JPEG�摜���R(�D�惂�[�hIP 4K)
	AplParamJpegImageInfo1_Sd4k,	//JPEG�摜���P(�D�惂�[�hSD�J�[�h 4K)
	AplParamJpegImageInfo2_Sd4k,	//JPEG�摜���Q(�D�惂�[�hSD�J�[�h 4K)
	AplParamJpegImageInfo3_Sd4k,	//JPEG�摜���R(�D�惂�[�hSD�J�[�h 4K)
	AplParamJpegImageInfo1_Usb4k,	//JPEG�摜���P(�D�惂�[�hUSB 4K)
	AplParamJpegImageInfo2_Usb4k,	//JPEG�摜���Q(�D�惂�[�hUSB 4K)
	AplParamJpegImageInfo1_Hdmi4k,	//JPEG�摜���P(�D�惂�[�hHDMI 4K)
	AplParamJpegImageInfo2_Hdmi4k,	//JPEG�摜���Q(�D�惂�[�hHDMI 4K)
	AplParamJpegImageInfo3_Hdmi4k,	//JPEG�摜���R(�D�惂�[�hHDMI 4K)
	AplParamH264SendInfo1,	//H.264���M���P
	AplParamH264SendInfo2,	//H.264���M���Q
	AplParamH264SendInfo3,	//H.264���M���R
	AplParamH264SendInfo4,	//H.264���M���S
	AplParamH264ImageInfo1_Ip,	//H.264�摜���P(�D�惂�[�hIP)
	AplParamH264ImageInfo2_Ip,	//H.264�摜���Q(�D�惂�[�hIP)
	AplParamH264ImageInfo3_Ip,	//H.264�摜���R(�D�惂�[�hIP)
	AplParamH264ImageInfo4_Ip,	//H.264�摜���S(�D�惂�[�hIP)
	AplParamH264ImageInfo1_Ip60p,	//H.264�摜���P(�D�惂�[�hIP_60P)
	AplParamH264ImageInfo2_Ip60p,	//H.264�摜���Q(�D�惂�[�hIP_60P)
	AplParamH264ImageInfo3_Ip60p,	//H.264�摜���R(�D�惂�[�hIP_60P)
	AplParamH264ImageInfo1_IpHdr,	//H.264�摜���P(�D�惂�[�hIP_HDR)
	AplParamH264ImageInfo1_Ip4k,	//H.264�摜���P(�D�惂�[�hIP 4K)
	AplParamAudioBitrate,	//�����r�b�g���[�g
	AplParamHostAuth,	//�z�X�g�F��
	AplParamPriorityStream,	//�D��X�g���[��
	AplParamPriorityStreamType,	//�D��X�g���[���^�C�v
	AplParamSdRecFormat_Sd,	//SD�J�[�h�L�^�t�H�[�}�b�g(�D�惂�[�hSD)
	AplParamSdRecFormat_SdHdr,	//SD�J�[�h�L�^�t�H�[�}�b�g(�D�惂�[�hSD_HDR)
	AplParamSdRecFormat_Sd4k,	//SD�J�[�h�L�^�t�H�[�}�b�g(�D�惂�[�hSD_4K)
	AplParamTimezone,	//�^�C���]�[��(�G���A)
	AplParamAudioTransmission,	//Audio Transmission
	AplParamNetE2pVersion,	//EEPROM�o�[�W����
	AplParamPrevPriorityMode,	//�O��̗D�惂�[�h
	AplParamRtspPortNum,	//RTSP�|�[�g�ԍ�
	AplParamOverlayCamTitle,	//�J���[�o�[�̃J�����^�C�g���d��
	AplParamH264ImageInfo1_Sd,	//H.264�摜���P(�D�惂�[�hSD)
	AplParamH264ImageInfo1_SdFhd,	//H.264�摜���P(�D�惂�[�hSD_FHD)
	AplParamJpegImageInfo1_Sd24p,	//JPEG�摜���P(�D�惂�[�hSD�J�[�h_24P)
	AplParamJpegImageInfo1_SdFhd,	//JPEG�摜���P(�D�惂�[�hSD�J�[�h_FHD)
	AplParamPrevPriorityModeSd,	//�O��̗D�惂�[�h(�D�惂�[�hSD�p)
	AplParamInitialDisplayStreamSdFhd,	//�����\���X�g���[��(�D�惂�[�hSD_FHD�J�[�h)
	AplParamInitialDisplayStreamSd24p,	//�����\���X�g���[��(�D�惂�[�hSD_24P�J�[�h)
	AplParamH264ImageInfo1_Ip_Camhead,	//H.264�摜���P(�D�惂�[�hIP)(�J�����w�b�h)
	AplParamH264ImageInfo1_Ip4k_Camhead,	//H.264�摜���P(�D�惂�[�hIP 4K)(�J�����w�b�h)
	AplParamH264ImageInfo1_Sd_Camhead,	//H.264�摜���P(�D�惂�[�hSD)(�J�����w�b�h)
	AplParamH264ImageInfo1_SdFhd_Camhead,	//H.264�摜���P(�D�惂�[�hSD_FHD)(�J�����w�b�h)
	AplParamInitialDisplayStreamNdiHx,	//�����\���X�g���[��(�D�惂�[�hNDI_HX)
	AplParamH264ImageInfo1_NdiHx,	//H.264�摜���P(�D�惂�[�hNDI_HX)
	AplParamH264ImageInfo2_NdiHx,	//H.264�摜���Q(�D�惂�[�hNDI_HX)
	AplParamJpegImageInfo1_NdiHx,	//JPEG�摜���P(�D�惂�[�hNDI_HX)
	AplParamNdiHxLicenseKey,	//NDI-HX���C�Z���X�L�[
	AplParamAudioVol,	//AudioVolume(K519�p)
	AplParamSelectedClipNum,	//�폜�A�R�s�[�m�F���-�I���N���b�v��
	AplParamSimulErrSd1,	//ModeCheck(Status��ʁj�\���p�t���O
	AplParamSimulErrSd2,	//ModeCheck(Status��ʁj�\���p�t���O
	AplParamBlinkSd1,	//�J�[�h�c�ʂ�2���ȉ��̎��̓_�ŗp�t���O�i�^���[�AOSD�j
	AplParamBlinkSd2,	//�J�[�h�c�ʂ�2���ȉ��̎��̓_�ŗp�t���O�i�^���[�AOSD�j
	AplParamStreamingStatus,	//�X�g���[�~���O���
	AplParamBondingDeviceStatus,	//�{���f�B���O�@���� ������
	AplParamBondingConnectStatus,	//�{���f�B���O�@���� �d�g���x
	AplParamBondingBatteryRemain,	//�{���f�B���O�@���� �o�b�e���[�c��
	AplParamBondingError,	//�{���f�B���O�@���� �G���[���
	AplParamIpRemoteStatus,	//IP�����[�g���
	AplParamTotalRemain,	//Slot1,2�̑��c��
	AplParamTotalCapacity,	//Slot1,2�̑��e��
	AplParamNetworkTally,	//�l�b�g���[�N�o�R�ł�Tally�v��
	AplParamBackGrErrSd1,	//ModeCheck(Status��ʁj�\���p�t���O
	AplParamBackGrErrSd2,	//ModeCheck(Status��ʁj�\���p�t���O
	AplParamBackUpTc,	//PowerOnRec����TC�o�b�N�A�b�v
	AplParamPowerOnRecStart,	//PowrOnRec�J�n�t���O
	AplParamNdFilterWarning,	//NdFilterWarning�\���p
	AplParamIaZoomActFlag,	//iA�Y�[�����쒆�t���O�\���p
	AplParamAutoIrisDispMode,	//�I�[�g�A�C���X���[�h�ݒ�\���p
	AplParamAreaMode,	//UserSw��Area
	AplParamAutoManualSwState,	//�I�[�g�}�j���A��Sw�̕\���p
	AplParamSlot1CardStatus,	//SLOT1�̃J�[�h�A�C�R����Status�\���p
	AplParamSlot1RecStatus,	//SLOT1�̋L�^��Ԃ̕\���p�i�Ԋۓ_���A�Ԋۓ_�ŁAP�A�Ȃ��j
	AplParamSlot2CardStatus,	//SLOT2�̃J�[�h�A�C�R����Status�\���p
	AplParamSlot2RecStatus,	//SLOT2�̋L�^��Ԃ̕\���p�i�Ԋۓ_���A�Ԋۓ_�ŁAP�A�Ȃ��j
	AplParamShutterSpeedSec,	//�V���b�^�[�X�s�[�h�i���ԁj
	AplParamShutterSpeedSec60,	//�V���b�^�[�X�s�[�h�i���ԁj60
	AplParamShutterSpeedSec30,	//�V���b�^�[�X�s�[�h�i���ԁj30
	AplParamShutterSpeedSec24,	//�V���b�^�[�X�s�[�h�i���ԁj24
	AplParamShutterSpeedSec50,	//�V���b�^�[�X�s�[�h�i���ԁj50
	AplParamShutterSpeedSec25,	//�V���b�^�[�X�s�[�h�i���ԁj25
	AplParamSynchroScanSec,	//�V���N���X�L�����i���ԁj
	AplParamSynchroScanDeg,	//�V���N���X�L�����i�p�x�j
	AplParamSuperGainExe,	//���{����X�[�p�[�Q�C��
	AplParamFocusOSD_Num,	//Focus OSD�\���p�@�l
	AplParamFocusOSD_MM,	//Focus OSD�\���p�@mm
	AplParamGainValue,	//Gain�@�l
	AplParamWhiteBalanceModeOSD,	//White Balance Mode�@OSD�\���p
	AplParamMmlModeSyncro,	//Mml��Mode��Syncro�ɂȂ������Ƃ�ʒm����p
	AplParamUpButtonInvalid,	//��{�^���̔r���p
	AplParamDownButtonInvalid,	//���{�^���̔r���p
	AplParamReverseFocusDisplay,	//Focus�\�����]���
	AplParamBackUpCounter,	//PowerOnRec���̃J�E���^�[�l�o�b�N�A�b�v
	AplParamInfoPowerOnTimes,	//�d��ON��
	AplParamInfoServoZoom,	//�Y�[�����[�^�[�J�E���g
	AplParamInfoGripZoom,	//�O���b�v�Y�[���J�E���g
	AplParamInfoHandleZoom,	//�n���h���Y�[���J�E���g
	AplParamInfoLcdOperation,	//LCD�o�b�N���C�g�_������ 
	AplParamInfoEvfOperation,	//EVF�_������
	AplParamZoomCtrlValue,	//Zoom����l
	AplParamFocusCtrlValue,	//Focus����l
	AplParamIrisCtrlValue,	//Iris����l
	AplParamUpdateEnd,	//UpdateEnd�ʒm���ɍX�V�ʒm��΂�
	AplParamStreamingInternalStatus,	//�z�M�����̓�����(�����̃X�e�[�^�X)
	AplParamNetworkFunc,	//NETWORK FUNC
	AplParamAutoIrisLevelEffectAdjust,	//A.IRIS LEVEL EFFECT�����l(OSD�\���p)
	AplParamPlayPhotoShot,	//�Î~��؂�o���X�e�[�^�X
	AplParamDZoomCtrlValue,	//DigitalZoom����l
	AplParamForceAF,	//����AF���쒆����
	AplParamRequestMountUpdateSd1,	//SD1�̃}�E���g�A�b�v�f�[�g�v��
	AplParamRequestMountUpdateSd2,	//SD2�̃}�E���g�A�b�v�f�[�g�v��
	AplParamMmFuncFrameRateInvalidFlag,	//MM�@�\��FrameRate�L������p
	AplParamAutoIrisLevelEffectAdjustmentAmount,	//A.IRIS LEVEL EFFECT�����l(�����O�␳��)
	AplParamSynchroScanAddMode,	//�V���N���X�L�������쒆
	AplParamPlayP2Icon,	//�\���FP2�p�T���l�C����ʃA�C�R��
	AplParamPlayP2StartIcon,	//�\���FP2�s�ǃN���b�v�p�T���l�C����ʃA�C�R��
	AplParamIdMax
} AplParamEepromId;
#endif /* _APL_PARAM_H_ */

#define APL_PARAM_DATA_SIZE_MAX	10172

