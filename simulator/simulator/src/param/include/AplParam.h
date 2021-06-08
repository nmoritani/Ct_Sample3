#ifndef _APL_PARAM_H_
#define _APL_PARAM_H_

#define APL_MENU_FACTSETTING_SIZE	0x01FF
#define APL_MENU_FIRSTSETTING_SIZE	0x00DF
#define APL_SCENE_CUSTOM_PARAM_NUM	1

typedef enum AplParamEepromId{
	AplParamTopMenu,	//TOP MENU
	AplParamRecFormat,	//FILE FORMAT
	AplParamSystemRecMode,	//コーデックの組み合わせ
	AplParamThumbnailMenu,	//THUMBNAIL
	AplParamPlayBackMenu,	//THUMBNAIL > PLAYBACK
	AplParamPlaySlot,	//CLIP SEL
	AplParamPlaySlotStateDecidion,	//CLIP SEL 内部状態判定用
	AplParamResume,	//RESUME PLAY
	AplParamSeekPosSel,	//SEEK POS SEL
	AplParamClipMenu,	//THUMBNAIL > CLIP
	AplParamCopyMenu,	//THUMBNAIL > CLIP > COPY
	AplParamCopyAllMenu,	//THUMBNAIL > CLIP > COPY > ALL
	AplParamCopySelectMenu,	//THUMBNAIL > CLIP > COPY > SELECT
	AplParamThumbDisplayMenu,	//THUMBNAIL > DISPLAY
	AplParamDisplayIndicator,	//(削除予定)INDICATOR
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
	AplParamATWRchGain,	//ATW TARGET　R
	AplParamATWBchGain,	//ATW TARGET　B
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
	AplParamSceneSyncScanSecValue_NTSC,	//SYNC SCAN TYPE=sec、59.94Hz
	AplParamSceneSyncScanSecValue_PAL,	//SYNC SCAN TYPE=sec、50Hz
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
	AplParamSceneSkinToneZebra,	//SKIN TONE　ZEBRA
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
	AplParamUserAccountNameInput,	//ユーザーアカウント名の入力値
	AplParamUserAccountPasswordInput,	//ユーザーアカウントパスワードの入力値
	AplParamUserAccountNum,	//登録ユーザー数
	AplParamIpRemotePort,	//PORT
	AplParamFTPClientMenu,	//NETWORK >FTP CLIENT
	AplParamStreamingMenu,	//NETWORK >STREAMING
	AplParamStreamingFormat,	//STREAMING FORMAT
	AplParamStreamingStartTrigger,	//START TRIGGER
	AplParamStreamingConnectionInfo,	//CONNECTION INFO.
	AplParamStreamingDataType,	//DATA TYPE
	AplParamStreamingReceiverUrl,	//RECEIVER URL 512文字+終端
	AplParamStreamingReceiverUrlMemory,	//RECEIVER URL MEMORY 512文字+終端
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
	AplParamLanDnsPrimaryUpdateDhcp,	//LAN PRIMARY DNS DHCPで割当完了
	AplParamLanDnsSecondaryUpdateDhcp,	//LAN SECONDARY DNS DHCPで割当完了
	AplParamLanIPv6SettingMenu,	//NETWORK >LAN PROPERTY >IPv6 SETTING
	AplParamLanEnableIPv6,	//LAN IPv6 ENABLE/DISABLE
	AplParamLanDhcpModeV6,	//LAN DHCP IPv6
	AplParamLanIpAddressV6,	//LAN IPアドレス(IPv6)
	AplParamLanPrefixLengthV6,	//LAN PREFIX　LENGTH(IPv6)
	AplParamLanGatewayV6,	//LAN DEFAULT GATEWAY(IPv6)
	AplParamLanDnsPrimaryV6,	//LAN PRIMARY DNS(IPv6)
	AplParamLanDnsSecondaryV6,	//LAN SECONDARY DNS(IPv6)
	AplParamLanDnsPrimaryV6UpdateDhcp,	//LAN PRIMARY DNS(IPv6) DHCPで割当完了
	AplParamLanDnsSecondaryV6UpdateDhcp,	//LAN SECONDARY DNS(IPv6) DHCPで割当完了
	AplParamWlanPropertyMenu,	//NETWORK >WLAN PROPERTY
	AplParamWlanMacAddress,	//WLAN設定 MACアドレス
	AplParamWlanMode,	//WLAN TYPE
	AplParamSsid,	//WLAN設定 SSID
	AplParamMySsid,	//WLAN設定 自機SSID
	AplParamInfraSsid,	//WLAN設定 InfraのSSID
	AplParamBand,	//バンド設定
	AplParamChannel,	//チャンネル設定
	AplParamChannel5G,	//チャンネル設定(5G)
	AplParamEncryption,	//WLAN設定 暗号種別
	AplParamMySecurityType,	//自機 暗号種別
	AplParamInfraEncryption,	//Infraの暗号化種別
	AplParamEncryptKey,	//暗号化キー
	AplParamMySecurityPass,	//自機 パスワード
	AplParamInfraEncryptionKey,	//Infraの暗号化キー
	AplParamWLanIPv4SettingMenu,	//NETWORK >WLAN PROPERTY >IPv4 SETTING
	AplParamDhcpMode,	//WLAN DHCP
	AplParamDhcp,	//DHCP
	AplParamDhcp_2nd,	//DHCP 2nd
	AplParamIpAddress,	//WLAN IP アドレス
	AplParamIpAddressDirect,	//IP アドレス Direct
	AplParamIpAddress_2nd,	//IP アドレス 2nd
	AplParamSubnet,	//WLAN サブネットマスク
	AplParamSubnetDirect,	//サブネットマスク Direct
	AplParamSubnet_2nd,	//サブネットマスク 2nd
	AplParamGateway,	//WLAN デフォルトゲートウェイ
	AplParamGatewayDirect,	//デフォルトゲートウェイ Direct
	AplParamGateway_2nd,	//デフォルトゲートウェイ 2nd
	AplParamDnsPrimary,	//WLAN DNS (プライマリ)
	AplParamDnsPrimaryUpdateDhcp,	//WLAN DNS (プライマリ) DHCPで割当完了
	AplParamDnsPrimaryDirect,	//DNS (プライマリ) Direct
	AplParamDnsPrimary_2nd,	//DNS (プライマリ) 2nd
	AplParamDnsSecondary,	//WLAN DNS (セカンダリ)
	AplParamDnsSecondaryUpdateDhcp,	//WLAN DNS (セカンダリ) DHCPで割当完了
	AplParamDnsSecondaryDirect,	//DNS (セカンダリ) Direct
	AplParamDnsSecondary_2nd,	//DNS (セカンダリ) 2nd
	AplParamWLanIPv6SettingMenu,	//NETWORK >LAN PROPERTY >IPv6 SETTING
	AplParamEnableIPv6,	//WLAN IPv6 ENABLE/DISABLE
	AplParamEnableIPv6Direct,	//WLAN DIRECT IPv6 ENABLE/DISABLE
	AplParamEnableIPv6Infra,	//WLAN INFRA IPv6 ENABLE/DISABLE
	AplParamDhcpModeV6,	//WLAN DHCP IPv6
	AplParamDhcpV6,	//WLAN DIRECT DHCP(IPv6)
	AplParamDhcpV6Infra,	//WLAN INFRA DHCP(IPv6)
	AplParamIpAddressV6,	//WLAN IPアドレス(IPv6)
	AplParamIpAddressV6Direct,	//WLAN DIRECT IPアドレス(IPv6)
	AplParamIpAddressV6Infra,	//WLAN INFRA IPアドレス(IPv6)
	AplParamPrefixLengthV6,	//WLAN プレフィックス長(IPv6)
	AplParamPrefixLengthV6Direct,	//WLAN DIRECT プレフィックス長(IPv6)
	AplParamPrefixLengthV6Infra,	//WLAN INFRA プレフィックス長(IPv6)
	AplParamGatewayV6,	//WLAN デフォルトゲートウェイ(IPv6)
	AplParamGatewayV6Direct,	//WLAN DIRECT デフォルトゲートウェイ(IPv6)
	AplParamGatewayV6Infra,	//WLAN INFRA デフォルトゲートウェイ(IPv6)
	AplParamDnsPrimaryV6,	//WLAN DNS (プライマリ)(IPv6)
	AplParamDnsPrimaryV6UpdateDhcp,	//WLAN DNS (プライマリ)(IPv6) DHCPで割当完了
	AplParamDnsPrimaryV6Direct,	//WLAN DIRECT DNS (プライマリ)(IPv6)
	AplParamDnsPrimaryV6Infra,	//WLAN INFRA DNS (プライマリ)(IPv6)
	AplParamDnsSecondaryV6,	//WLAN DNS (セカンダリ)(IPv6)
	AplParamDnsSecondaryV6UpdateDhcp,	//WLAN DNS (セカンダリ)(IPv6) DHCPで割当完了
	AplParamDnsSecondaryV6Direct,	//WLAN DIRECT DNS (セカンダリ)(IPv6)
	AplParamDnsSecondaryV6Infra,	//WLAN INFRA DNS (セカンダリ)(IPv6)
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
	AplParamColorbarType,	//カラーバータイプS1仕様
	AplParamColorBarTestTone,	//カラーバー時にテストトーンを出力するかどうか
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
	AplParamInfoMacAddr,	//MAC ADDRESS(廃止予定)
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
	AplParamSceneAchColorTempRGainCtrl,	//COLOR TEMP R GAIN制御値 Ach
	AplParamSceneAchColorTempGGainCtrl,	//COLOR TEMP B GAIN制御値 Ach
	AplParamSceneAchWhiteValueAWBResult,	//AWB実行結果 Ach
	AplParamSceneBchColorTempRGainCtrl,	//COLOR TEMP R GAIN制御値 Bch
	AplParamSceneBchColorTempGGainCtrl,	//COLOR TEMP B GAIN制御値 Bch
	AplParamSceneBchWhiteValueAWBResult,	//AWB実行結果 Bch
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
	AplParamSceneSyncScanSecValue_NTSC_S1,	//SYNC SCAN TYPE=sec、59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S2,	//SYNC SCAN TYPE=sec、59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S3,	//SYNC SCAN TYPE=sec、59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S4,	//SYNC SCAN TYPE=sec、59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S5,	//SYNC SCAN TYPE=sec、59.94Hz
	AplParamSceneSyncScanSecValue_NTSC_S6,	//SYNC SCAN TYPE=sec、59.94Hz
	AplParamSceneSyncScanSecValue_PAL_S1,	//SYNC SCAN TYPE=sec、50Hz
	AplParamSceneSyncScanSecValue_PAL_S2,	//SYNC SCAN TYPE=sec、50Hz
	AplParamSceneSyncScanSecValue_PAL_S3,	//SYNC SCAN TYPE=sec、50Hz
	AplParamSceneSyncScanSecValue_PAL_S4,	//SYNC SCAN TYPE=sec、50Hz
	AplParamSceneSyncScanSecValue_PAL_S5,	//SYNC SCAN TYPE=sec、50Hz
	AplParamSceneSyncScanSecValue_PAL_S6,	//SYNC SCAN TYPE=sec、50Hz
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
	AplParamSceneSkinToneZebra_S1,	//SKIN TONE　ZEBRA
	AplParamSceneSkinToneZebra_S2,	//SKIN TONE　ZEBRA
	AplParamSceneSkinToneZebra_S3,	//SKIN TONE　ZEBRA
	AplParamSceneSkinToneZebra_S4,	//SKIN TONE　ZEBRA
	AplParamSceneSkinToneZebra_S5,	//SKIN TONE　ZEBRA
	AplParamSceneSkinToneZebra_S6,	//SKIN TONE　ZEBRA
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
	AplParamSceneAchColorTempRGainCtrl_S1,	//COLOR TEMP R GAIN制御値 Ach
	AplParamSceneAchColorTempRGainCtrl_S2,	//COLOR TEMP R GAIN制御値 Ach
	AplParamSceneAchColorTempRGainCtrl_S3,	//COLOR TEMP R GAIN制御値 Ach
	AplParamSceneAchColorTempRGainCtrl_S4,	//COLOR TEMP R GAIN制御値 Ach
	AplParamSceneAchColorTempRGainCtrl_S5,	//COLOR TEMP R GAIN制御値 Ach
	AplParamSceneAchColorTempRGainCtrl_S6,	//COLOR TEMP R GAIN制御値 Ach
	AplParamSceneAchColorTempGGainCtrl_S1,	//COLOR TEMP B GAIN制御値 Ach
	AplParamSceneAchColorTempGGainCtrl_S2,	//COLOR TEMP B GAIN制御値 Ach
	AplParamSceneAchColorTempGGainCtrl_S3,	//COLOR TEMP B GAIN制御値 Ach
	AplParamSceneAchColorTempGGainCtrl_S4,	//COLOR TEMP B GAIN制御値 Ach
	AplParamSceneAchColorTempGGainCtrl_S5,	//COLOR TEMP B GAIN制御値 Ach
	AplParamSceneAchColorTempGGainCtrl_S6,	//COLOR TEMP B GAIN制御値 Ach
	AplParamSceneAchWhiteValueAWBResult_S1,	//AWB実行結果 Ach
	AplParamSceneAchWhiteValueAWBResult_S2,	//AWB実行結果 Ach
	AplParamSceneAchWhiteValueAWBResult_S3,	//AWB実行結果 Ach
	AplParamSceneAchWhiteValueAWBResult_S4,	//AWB実行結果 Ach
	AplParamSceneAchWhiteValueAWBResult_S5,	//AWB実行結果 Ach
	AplParamSceneAchWhiteValueAWBResult_S6,	//AWB実行結果 Ach
	AplParamSceneBchColorTempRGainCtrl_S1,	//COLOR TEMP R GAIN制御値 Bch
	AplParamSceneBchColorTempRGainCtrl_S2,	//COLOR TEMP R GAIN制御値 Bch
	AplParamSceneBchColorTempRGainCtrl_S3,	//COLOR TEMP R GAIN制御値 Bch
	AplParamSceneBchColorTempRGainCtrl_S4,	//COLOR TEMP R GAIN制御値 Bch
	AplParamSceneBchColorTempRGainCtrl_S5,	//COLOR TEMP R GAIN制御値 Bch
	AplParamSceneBchColorTempRGainCtrl_S6,	//COLOR TEMP R GAIN制御値 Bch
	AplParamSceneBchColorTempGGainCtrl_S1,	//COLOR TEMP B GAIN制御値 Bch
	AplParamSceneBchColorTempGGainCtrl_S2,	//COLOR TEMP B GAIN制御値 Bch
	AplParamSceneBchColorTempGGainCtrl_S3,	//COLOR TEMP B GAIN制御値 Bch
	AplParamSceneBchColorTempGGainCtrl_S4,	//COLOR TEMP B GAIN制御値 Bch
	AplParamSceneBchColorTempGGainCtrl_S5,	//COLOR TEMP B GAIN制御値 Bch
	AplParamSceneBchColorTempGGainCtrl_S6,	//COLOR TEMP B GAIN制御値 Bch
	AplParamSceneBchWhiteValueAWBResult_S1,	//AWB実行結果 Bch
	AplParamSceneBchWhiteValueAWBResult_S2,	//AWB実行結果 Bch
	AplParamSceneBchWhiteValueAWBResult_S3,	//AWB実行結果 Bch
	AplParamSceneBchWhiteValueAWBResult_S4,	//AWB実行結果 Bch
	AplParamSceneBchWhiteValueAWBResult_S5,	//AWB実行結果 Bch
	AplParamSceneBchWhiteValueAWBResult_S6,	//AWB実行結果 Bch
	AplParamMediaSelectPhoto,	//メディア選択（静止画）
	AplParamMediaSelect,	//メディア選択（動画）
	AplParamPlayMedia,	//再生対象メディア
	AplParamUSeAreaSettings,	//使用する地域
	AplParamFormatDate1,	//フォーマット履歴1：日時
	AplParamFormatSerialNumber1,	//フォーマット履歴1：カードシリアル番号
	AplParamFormatDate2,	//フォーマット履歴2：日時
	AplParamFormatSerialNumber2,	//フォーマット履歴2：カードシリアル番号
	AplParamFormatDate3,	//フォーマット履歴3：日時
	AplParamFormatSerialNumber3,	//フォーマット履歴3：カードシリアル番号
	AplParamFormatDate4,	//フォーマット履歴4：日時
	AplParamFormatSerialNumber4,	//フォーマット履歴4：カードシリアル番号
	AplParamFormatDate5,	//フォーマット履歴5：日時
	AplParamFormatSerialNumber5,	//フォーマット履歴5：カードシリアル番号
	AplParamFormatDate6,	//フォーマット履歴6：日時
	AplParamFormatSerialNumber6,	//フォーマット履歴6：カードシリアル番号
	AplParamFormatDate7,	//フォーマット履歴7：日時
	AplParamFormatSerialNumber7,	//フォーマット履歴7：カードシリアル番号
	AplParamFormatDate8,	//フォーマット履歴8：日時
	AplParamFormatSerialNumber8,	//フォーマット履歴8：カードシリアル番号
	AplParamFormatDate9,	//フォーマット履歴9：日時
	AplParamFormatSerialNumber9,	//フォーマット履歴9：カードシリアル番号
	AplParamFormatDate10,	//フォーマット履歴10：日時
	AplParamFormatSerialNumber10,	//フォーマット履歴10：カードシリアル番号
	AplParamFormatHistoryNum,	//フォーマット履歴番号
	AplParamABBErrInfo,	//ABBエラー情報
	AplParamAWBErrInfo,	//AWBエラー情報
	AplParamColorTempGMgCtrl,	//GMg制御値
	AplParamColorTempRGainCtrl,	//COLOR TEMP R GAIN制御値
	AplParamColorTempGGainCtrl,	//COLOR TEMP B GAIN制御値
	AplParamSuperGain,	//SUPER GAIN
	AplParamIrisModePro,	//アイリスモード(AUTO/MANUAL)
	AplParamNDFilter,	//SW操作用NDフィルター値
	AplParamNDFilterIr,	//SW操作用NDフィルター値(赤外線用)
	AplParamSetUb,	//ユーザー設定のUBの値
	AplParamDbgId,	//デバッグ用：APL デバッグ出力設定
	AplParamVFRValueIncrementFlg,	//デバッグ用：VFR値の自動インクリメントフラグ
	AplParamLifeStartYear,	//メニュー：時計設定開始年
	AplParamLifeEndYear,	//メニュー：時計設定終了年
	AplParamContinuousRecordTime,	//連続記録時間 [分単位] 
	AplParamContinuousIntervalRecTime,	//インターバル連続記録時間 [分単位] 
	AplParamContinuousPreRecTime,	//PRE-REC連続記録時間 [分単位]
	AplParamHeadPhoneDelayInterval,	//HP接続のディレイ間隔
	AplParamSetupVersion,	//セットアップバージョン(セットアップ情報Ver)
	AplParamSetupEepromVersion,	//セットアップバージョン(EEPROM配置Ver)
	AplParamSceneVersion,	//シーンバージョン(シーン情報Ver) カスタムシーン設定仕様書記載のバージョン情報
	AplParamSceneEepromVersion,	//シーンバージョン(EEPROM配置Ver) カスタムシーン設定仕様書記載のバージョン情報
	AplParamVup,	//バージョン管理
	AplParamGrade,	//サービスメニュー：VUP用メニュー表示選択
	AplParamAudioClip_VolHigh,	//オーディオクリップ情報(大)
	AplParamPhotoSound_VolHigh,	//カシャ音音量設定(大)
	AplParamBeepSound_VolHigh,	//ビープ音音量設定(大)
	AplParamAudioClip_VolMid,	//オーディオクリップ情報(中)
	AplParamPhotoSound_VolMid,	//カシャ音音量設定(中)
	AplParamBeepSound_VolMid,	//ビープ音音量設定(中)
	AplParamAudioClip_VolLow,	//オーディオクリップ情報(小)
	AplParamPhotoSound_VolLow,	//カシャ音音量設定(小)
	AplParamBeepSound_VolLow,	//ビープ音音量設定(小)
	AplParamRecBeep_VolHigh,	//オーディオクリップ情報(大)
	AplParamBatteryEnd_VolHigh,	//カシャ音音量設定(大)
	AplParamMediaEnd_VolHigh,	//ビープ音音量設定(大)
	AplParamRecBeep_VolMid,	//オーディオクリップ情報(中)
	AplParamBatteryEnd_VolMid,	//カシャ音音量設定(中)
	AplParamMediaEnd_VolMid,	//ビープ音音量設定(中)
	AplParamRecBeep_VolLow,	//オーディオクリップ情報(小)
	AplParamBatteryEnd_VolLow,	//カシャ音音量設定(小)
	AplParamMediaEnd_VolLow,	//ビープ音音量設定(小)
	AplParamBalanceAngleColorFarR,	//水準器色：ファー R
	AplParamBalanceAngleColorFarG,	//水準器色：ファー G
	AplParamBalanceAngleColorFarB,	//水準器色：ファー B
	AplParamBalanceAngleColorFarA,	//水準器色：ファー A
	AplParamBalanceAngleColorNearR,	//水準器色：ニア R
	AplParamBalanceAngleColorNearG,	//水準器色：ニア G
	AplParamBalanceAngleColorNearB,	//水準器色：ニア B
	AplParamBalanceAngleColorNearA,	//水準器色：ニア A
	AplParamBalanceAngleColorFocusLockR,	//水準器色：合焦 R
	AplParamBalanceAngleColorFocusLockG,	//水準器色：合焦 G
	AplParamBalanceAngleColorFocusLockB,	//水準器色：合焦 B
	AplParamBalanceAngleColorFocusLockA,	//水準器色：合焦 A
	AplParamFocusExpandStep,	//フォーカスエキスパンド移動量
	AplParamFocusExpandPosX,	//フォーカスエキスパンドX座標
	AplParamFocusExpandPosY,	//フォーカスエキスパンドY座標 
	AplParamSdDefReadSpeed,	//コピー: メディア速度  SDカード（DefaultSpeed） Read (上位バイト)
	AplParamSdDefWriteSpeed,	//コピー: メディア速度  SDカード（DefaultSpeed） Write (上位バイト)
	AplParamSdHighReadSpeed,	//コピー: メディア速度  SDカード（HighSpeed） Read (上位バイト)
	AplParamSdHighWriteSpeed,	//コピー: メディア速度  SDカード（HighSpeed） Write (上位バイト)
	AplParamHddReadSpeed,	//コピー: メディア速度  HDD Read (上位バイト)
	AplParamHddWriteSpeed,	//コピー: メディア速度  HDD Write (上位バイト)
	AplParamEsdReadSpeed,	//コピー: メディア速度  eSD Read (上位バイト)
	AplParamEsdWriteSpeed,	//コピー: メディア速度  eSD Write (上位バイト)
	AplParamCopyThreshold1,	//コピー: シーン切り替わり  切り替わり閾値 1 (上位バイト)
	AplParamCopyThreshold2,	//コピー: シーン切り替わり  切り替わり閾値 2 (上位バイト)
	AplParamSceneMultiplier1,	//コピー: シーン切り替わり  切り替わり乗数 1 (上位バイト)
	AplParamSceneMultiplier2,	//コピー: シーン切り替わり  切り替わり乗数 2 (上位バイト)
	AplParamSceneMultiplier3,	//コピー: シーン切り替わり  切り替わり乗数 3 (上位バイト)
	AplParamDiscFinalizeTime,	//コピー: ファイナライズ  ファイナライズ時間 (上位バイト)
	AplParamPITransRatio,	//コピー: トランスコード  60p → 60i 変換倍率
	AplParamPhotoSceneMultiplier1,	//コピー: シーン静止画 切り替わり  静止画 切り替わり乗数 1 (上位バイト)
	AplParamPhotoSceneMultiplier2,	//コピー: シーン静止画 切り替わり  静止画 切り替わり乗数 2 (上位バイト)
	AplParamPhotoSceneMultiplier3,	//コピー: シーン静止画 切り替わり  静止画 切り替わり乗数 3 (上位バイト)
	AplParamPCFriendlyEnable,	//PCフレンドリ (MP4)
	AplParamBDUsable,	//ブルーレイディスク使用
	AplParamAFRangeValueStep,	//AFエリア幅STEP
	AplParamSceneNum,	//シーン数
	AplParamGyroSensorX,	//ジャイロセンサー値X　ユーザー補正値
	AplParamGyroSensorY,	//ジャイロセンサー値Y　ユーザー補正値
	AplParamGyroSensorZ,	//ジャイロセンサー値Z　ユーザー補正値
	AplParamGyroSensorInitX,	//ジャイロセンサー値X　工場設定補正値
	AplParamGyroSensorInitY,	//ジャイロセンサー値Y　工場設定補正値
	AplParamGyroSensorInitZ,	//ジャイロセンサー値Z　工場設定補正値
	AplParamIrisDialCnt,	//Irisダイヤル動作カウンタ
	AplParamColorBar,	//カラーバー
	AplParamPlayMode,	//メニュー排他用。再生モードに入ったらONする
	AplParamDeckMode,	//APL内部のモード(AplParamPlayModeと類似)
	AplParamOptionMenuDisp,	//オプションメニュー表示フラグ
	AplParamAreaSelectDisplay,	//起動時のエリアセレクト画面表示フラグ
	AplParamEnableSceneFileLoad,	//シーンファイルLOAD許可フラグ
	AplParamEnableSceneFileSave,	//シーンファイルSAVE許可フラグ
	AplParamEnableSceneFileSaveAs,	//シーンファイルSAVE AS許可フラグ
	AplParamEnableSetupFileLoad,	//セットアップファイルLOAD許可フラグ
	AplParamEnableSetupFileSave,	//セットアップファイルSAVE許可フラグ
	AplParamEnableSetupFileSaveAs,	//セットアップファイルSAVE AS許可フラグ
	AplParamSDcardInOutStatus,	//SDカードの挿抜状態確認フラグ
	AplParamEnableSDWriteStatus,	//SD書き込み可能確認フラグ
	AplParamAlert,	//アラート
	AplParamAlertSubRecWarning,	//アラート：APL_SYS_PARAM_ALERT_SUB_REC_WARNING
	AplParamAlertSimulRecWarning,	//アラート：APL_SYS_PARAM_ALERT_SIMUL_REC_WARNING
	AplParamAlertBackGroundRecWarning,	//アラート：APL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING
	AplParamAlertFanStopped,	//アラート：APL_SYS_PARAM_ALERT_FAN_STOPPED
	AplParamAlertNotSupportCardSd1,	//アラート：APL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD
	AplParamAlertNotSupportCardSd2,	//アラート：APL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD
	AplParamAlertFormatErrorCardSd1,	//アラート：APL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD
	AplParamAlertFormatErrorCardSd2,	//アラート：APL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD
	AplParamAlertNotSDXCCardSd1,	//アラート：APL_SYS_PARAM_ALERT_NOT_SDXC_CARD
	AplParamAlertNotSDXCCardSd2,	//アラート：APL_SYS_PARAM_ALERT_NOT_SDXC_CARD
	AplParamAlertIncompatibleCardSd1,	//アラート：APL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD
	AplParamAlertIncompatibleCardSd2,	//アラート：APL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD
	AplParamAlertBackupBattEmpty,	//アラート：APL_SYS_PARAM_ALERT_BACKUP_BATT_EMPTY
	AplParamAlertClockReset,	//アラート：APL_SYS_PARAM_ALERT_CLOCK_RESET
	AplParamWarning,	//ワーニング
	AplParamWarningLowBattery,	//ワーニング：バッテリーアンダーカット
	AplParamWarningHighTemp,	//ワーニング：温度異常
	AplParamWarningRecWarning,	//ワーニング：記録中異常
	AplParamWarningCardErrorPlaying,	//ワーニング：記録再生中のカード異常
	AplParamWarningCardErrorSlot1,	//ワーニング：記録再生中のカード異常 SLOT1
	AplParamWarningCardErrorSlot2,	//ワーニング：記録再生中のカード異常 SLOT2
	AplParamWarningCardErrorPlayingSlot1,	//ワーニング：記録再生中のカード異常 SLOT1
	AplParamWarningCardErrorPlayingSlot2,	//ワーニング：記録再生中のカード異常 SLOT2
	AplParamWarningNoRemain,	//ワーニング：記録中にカード残量0
	AplParamWarningBatteryNearEnd,	//ワーニング：バッテリーニアエンド
	AplParamInfoErr,	//エラー情報
	AplParamSlot1ErrStatus,	//メディアエラー用Slot1
	AplParamSlot2ErrStatus,	//メディアエラー用Slot2
	AplParamRelayBackupErrStatus,	//2SlotFunc機能が無効時
	AplParamSlot1Status,	//Slot1状態
	AplParamSlot2Status,	//Slot2状態
	AplParamSlot1Remain,	//スロット1の残量
	AplParamSlot2Remain,	//スロット2の残量
	AplParamSlot1RemainAll,	//スロット1の全記録可能時間
	AplParamSlot2RemainAll,	//スロット2の全記録可能時間
	AplParamSlot1InOutStatus,	//スロット1メディアの挿抜状態
	AplParamSlot2InOutStatus,	//スロット2メディアの挿抜状態
	AplParamRecFunctionStatus,	//表示：特殊記録状態
	AplParamSdiRawRecStatus,	//表示：SdiRaw記録中
	AplParamSdiHdmiRecRemoteStatus,	//表示：SDI/HDMI Recリモート
	AplParamAutoTrackingWhiteLock,	//表示：ATWLock
	AplParamHomeClipFileName,	//表示：HOME画面用のCamNo./ReelNo./ClipNo.
	AplParamLifeMode,	//表示：ライフモードのON/OFF状態
	AplParamTestLowDisplay,	//表示：TEST LOW
	AplParamComDisplay,	//表示：COM
	AplParamWifiDongleState,	//ドングル状態
	AplParamWlanLinkState,	//表示：WLANのLINK状態
	AplParamWLanStatus,	//表示：WLAN電波強度(Wifi)
	AplParamTcValueLcd,	//表示：画面表示TC(LCD)
	AplParamTcValueHdmi,	//表示：画面表示TC(Hdmi)
	AplParamTcValueSdi,	//表示：画面表示TC(Sdi)
	AplParamUbValueLcd,	//表示：画面表示UB(LCD)
	AplParamUbValueHdmi,	//表示：画面表示UB(Hdmi)
	AplParamUbValueSdi,	//表示：画面表示UB(Sdi)
	AplParamDurationValueLcd,	//表示：画面表示Dudation(LCD)
	AplParamDurationValueHdmi,	//表示：画面表示Duration(Hdmi)
	AplParamDurationValueSdi,	//表示：画面表示Duration(Sdi)
	AplParamRecCounterTotalValue,	//表示：画面表示REC COUNTER TOTAL
	AplParamRecCounterClipValue,	//表示：画面表示REC COUNTER CLIP
	AplParamRecCounterClipPlayValue,	//表示：再生画面表示REC COUNTER CLIP
	AplParamZoomLensValid,	//表示：表示制御に使用するCVからの情報
	AplParamIrisLensValid,	//表示：表示制御に使用するCVからの情報
	AplParamBatteryRemainStatus,	//表示：バッテリー残量
	AplParamRecClipName,	//表示：クリップネーム
	AplParamPlayClipName,	//表示：再生アプリ用クリップネーム
	AplParamStatusPlay,	//表示：再生中ステータスアイコン
	AplParamStatusPlaySeekBar,	//表示：再生中シークバー進捗率
	AplParamPlayGeneralProgressBar,	//表示：再生編集系プログレスバーの進捗率
	AplParamPlayWaitingStatus,	//表示：クリップ表示準備中Waiting表示フラグ
	AplParamPlayMovIcon,	//表示：MOV用サムネイル画面アイコン
	AplParamPlayAvchdIcon,	//表示：AVCHD用サムネイル画面アイコン
	AplParamTcPlayValueLcd,	//表示：再生画面表示TC(LCD)
	AplParamTcPlayValueHdmi,	//表示：再生画面表示TC(Hdmi)
	AplParamTcPlayValueSdi,	//表示：再生画面表示TC(Sdi)
	AplParamUbPlayValueLcd,	//表示：再生画面表示UB(LCD)
	AplParamUbPlayValueHdmi,	//表示：再生画面表示UB(Hdmi)
	AplParamUbPlayValueSdi,	//表示：再生画面表示UB(Sdi)
	AplParamDurationPlayValueLcd,	//表示：再生画面表示Dudation(LCD)
	AplParamDurationPlayValueHdmi,	//表示：再生画面表示Duration(Hdmi)
	AplParamDurationPlayValueSdi,	//表示：再生画面表示Duration(Sdi)
	AplParamCopyDirection,	//表示：COPY方向表示用
	AplParamOverClipSd1,	//Info-Diag表示用フラグ
	AplParamOverClipSd2,	//Info-Diag表示用フラグ
	AplParamClockDate,	//メニュー表示：時計設定情報受渡し用
	AplParamDispClockDate,	//メニュー表示：時計情報描画用
	AplParamInfoSensorTemp,	//メニュー表示：センサー温度
	AplParamInfoIrisDial,	//メニュー表示：アイリスダイアル操作
	AplParamSetTc,	//メニュー表示：TC情報
	AplParamEditFileName,	//メニュー表示：シーンファイル/セットアップファイル名
	AplParamWlanMacAddressString,	//メニューに表示するMACアドレス(WLAN)
	AplParamLanMacAddressString,	//メニューに表示するMACアドレス(LAN)
	AplParamDispTc,	//TC情報描画用
	AplParamIrisVal,	//IRIS値描画用
	AplParamIrisValueControl,	//F値の値制御、取得
	AplParamZoomVal,	//ZOOM値描画用(値)
	AplParamZoomMm,	//ZOOM値描画用（mm）
	AplParamSpotMeterStopVal,	//輝度表示(STOP用)
	AplParamSpotMeterPerVal,	//輝度表示(％用)
	AplParamDfMode,	//画面表示DFモード
	AplParamDfModePlay,	//再生画面表示DFモード
	AplParamTcInSlave,	//TC SLAVE状態
	AplParamIrisDispFlg,	//アイリス動作モード
	AplParamGyroSensorDispX,	//ジャイロセンサー値X　表示用
	AplParamGyroSensorDispY,	//ジャイロセンサー値Y　表示用
	AplParamGyroSensorDispZ,	//ジャイロセンサー値Z　表示用
	AplParamLcdLevelGaugeBalanceAngle,	//傾き角度（水準器用）
	AplParamLcdLevelGaugeAoriAngle,	//あおり角度（水準器用）
	AplParamLcdLevelGaugeBalanceAngleInit,	//傾き角度（水準器用）工程初期設定
	AplParamLcdLevelGaugeAoriAngleInit,	//あおり角度（水準器用）工程初期設定
	AplParamLcdLevelGaugeBalanceAngleUser,	//傾き角度（水準器用）ユーザー設定
	AplParamLcdLevelGaugeAoriAngleUser,	//あおり角度（水準器用）ユーザー設定
	AplParamAudioLevelMeterCH1,	//オーディオレベルのCH1の目盛値
	AplParamAudioLevelMeterCH2,	//オーディオレベルのCH2の目盛値
	AplParamPowerLcdUserSw,	//UserSw用PowerLcd設定値
	AplParamLcdMarkerUserSw,	//UserSw用LcdMarker設定値
	AplParamLcdCleanViewUserSw,	//UserSw用Lcd Clean View設定値
	AplParamSpotMeterUserSw,	//UserSw用SpotMeter設定値
	AplParamLcdFocusAssistUserSw,	//UserSw用FocusAssist設定値
	AplParamLcdFocusExpandUserSw,	//UserSw用FocusExpand設定値
	AplParamLcdOpenIrisFocusAssistUserSw,	//UserSw用OpenIrisFocusAssist設定値
	AplParamLcdFocusExpandPosUserSw,	//UserSw用FocusExpandPosition設定値
	AplParamDZoomUserSw,	//UserSw用DZoom設定値
	AplParamHomeSw,	//モード切替用HomeSw押下判定
	AplParamAudioLevelMeterInvalid,	//オーディオレベルメータ無効状態
	AplParamLcdSw,	//LCDスイッチの状態
	AplParamIrisDispInfoType,	//アイリス表示情報種別
	AplParamFactCommandMenuType,	//メニューコマンドでの取得メニュー選択
	AplParamBeEepVer,	//BE EEPROM Ver (サービスメニュー)
	AplParamCamEepVer,	//CAM EEPROM Ver (サービスメニュー)
	AplParamBeSum,	//BE SUM (サービスメニュー)
	AplParamCamSum,	//CAM SUM (サービスメニュー)
	AplParamBeCrc,	//BE CRC (サービスメニュー)
	AplParamCamCrc,	//CAM CRC (サービスメニュー)
	AplParamWorldTimeMode,	//ワールドタイム設定
	AplParamFlashBandCorrection,	//フラッシュバンド補正
	AplParamRopControlIris,	//ROP中のIRIS操作優先
	AplParamHDCMovie_MakerID,	//HDC_MakerID1
	AplParamHDCMovie_ModelCode,	//HDC_ModelCode1
	AplParamSavedStreamingData,	//STREAMING設定データの有無
	AplParamTcFrameMax,	//TCプリセットのMAX値
	AplParamWifiLv4Limit,	//89FB～89FFはNETブロックが参照する値、変更するときは相談必要
	AplParamWifiLv3Limit,	//89FB～89FFはNETブロックが参照する値、変更するときは相談必要
	AplParamWifiLv2Limit,	//89FB～89FFはNETブロックが参照する値、変更するときは相談必要
	AplParamWifiLv1Limit,	//89FB～89FFはNETブロックが参照する値、変更するときは相談必要
	AplParamWifiLv0Limit,	//89FB～89FFはNETブロックが参照する値、変更するときは相談必要
	AplParamSystemSettingsMenu,	//SYSTEM SETTINGS MENU TOP
	AplParamSystemModeMenu,	//SYSTEM SETTINGS > SYSTEM MODE
	AplParamSystemModeFrequency,	//システム周波数
	AplParamSystemSdiRaw,	//SDI端子から出力するRAW画素数
	AplParamSystemSensorMode,	//センサーの駆動モード
	AplParamSystemMainPixel,	//メインレコーダーの記録画素数
	AplParamSystemMainCodec,	//メインレコーダーの記録コーデック
	AplParamSystemSubRec,	//サブレコーダーの記録コーデック
	AplParamColorSettingsMenu,	//SYSTEM SETTINGS > COLOR SETTINGS
	AplParamColorMain,	//メインレコーダーに記録される映像（カメラシステム全体）のカラー
	AplParamColorSub,	//サブレコーダーに記録される映像のカラー
	AplParamColorSdiOut,	//SDI端子からの出力イメージを設定
	AplParamColorHdmiOut,	//HDMI端子からの出力イメージ
	AplParamColorLcdOut,	//LCD端子からの出力イメージ
	AplParamUserToggle,	//〈TOGGLE/USER〉ボタンに割り当てる機能を設定
	AplParamSideLockMenu,	//SYSTEM SETTINGS > SIDE LOCK
	AplParamSideLockRecButton,	//カメラ本体の〈REC〉ボタンをロックするかどうか
	AplParamSideLockUser1Button,	//〈USER1〉ボタンをロックするかどうか
	AplParamSideLockUser2Button,	//〈USER2〉ボタンをロックするかどうか
	AplParamSideLockUser3Button,	//〈USER3〉ボタンをロックするかどうか
	AplParamSideLockUser4Button,	//〈USER4〉ボタンをロックするかどうか
	AplParamSideLockUser5Button,	//〈USER5〉ボタンをロックするかどうか
	AplParamSideLockUser6Button,	//〈USER6〉ボタンをロックするかどうか
	AplParamSideLockUser7Button,	//〈USER7〉ボタンをロックするかどうか
	AplParamSideLockThumbnailButton,	//〈THUMBNAIL〉ボタンをロックするかどうかを設定
	AplParamSideLockHomeButton,	//〈HOME〉ボタンをロックするかどうかを設定
	AplParamSideLockNdFilterButton,	//〈ND FILTER〉ボタンをロックするかどうかを設定
	AplParamSideLockIrisDial,	//〈IRIS DIAL〉ボタンをロックするかどうかを設定
	AplParamSideLockMenuButton,	//〈MENU〉ボタンをロックするかどうかを設定
	AplParamSideLockExitButton,	//〈EXIT〉ボタンをロックするかどうかを設定
	AplParamSideLockMultiDial,	//〈MULTI DIAL〉ボタンをロックするかどうかを設定
	AplParamPowerLed,	//電源ランプモード
	AplParamFanSpeed,	//ファンの回転速度を選択
	AplParamCameraSettingsMenu,	//CAMERA SETTINGS
	AplParamFpsMenu,	//CAMERA SETTINGS > FPS
	AplParamVFRMode,	//VFRモード
	AplParamVFRValue,	//現在選択中のVFR値
	AplParamVFRValueIndex,	//現在選択中のVFR
	AplParamVFRValueSystem,	//VFR Value リスト
	AplParamVFRValue1,	//VFR Value リスト
	AplParamVFRValue2,	//VFR Value リスト
	AplParamVFRValue3,	//VFR Value リスト
	AplParamVFRValue4,	//VFR Value リスト
	AplParamVFRValue5,	//VFR Value リスト
	AplParamVFRValue6,	//VFR Value リスト
	AplParamVFRValue7,	//VFR Value リスト
	AplParamVFRValue8,	//VFR Value リスト
	AplParamVFRValue9,	//VFR Value リスト
	AplParamVFRValue10,	//VFR Value リスト
	AplParamVFRValue11,	//VFR Value リスト
	AplParamVFRValue12,	//VFR Value リスト
	AplParamVFRValue13,	//VFR Value リスト
	AplParamVFRValue14,	//VFR Value リスト
	AplParamVFRValue15,	//VFR Value リスト
	AplParamVFRValue16,	//VFR Value リスト
	AplParamVFRValue17,	//VFR Value リスト
	AplParamVFRValue18,	//VFR Value リスト
	AplParamVFRValue19,	//VFR Value リスト
	AplParamVFRValue20,	//VFR Value リスト
	AplParamVFRValue21,	//VFR Value リスト
	AplParamVFRValue22,	//VFR Value リスト
	AplParamVFRValue23,	//VFR Value リスト
	AplParamVFRValue24,	//VFR Value リスト
	AplParamVFRValue25,	//VFR Value リスト
	AplParamVFRValue26,	//VFR Value リスト
	AplParamVFRValue27,	//VFR Value リスト
	AplParamVFRValue28,	//VFR Value リスト
	AplParamVFRValue29,	//VFR Value リスト
	AplParamVFRValue30,	//VFR Value リスト
	AplParamVFRValue31,	//VFR Value リスト
	AplParamVFRValue32,	//VFR Value リスト
	AplParamVFRValue33,	//VFR Value リスト
	AplParamVFRValue34,	//VFR Value リスト
	AplParamVFRValue35,	//VFR Value リスト
	AplParamVFRValue36,	//VFR Value リスト
	AplParamVFRValue37,	//VFR Value リスト
	AplParamVFRValue38,	//VFR Value リスト
	AplParamVFRValue39,	//VFR Value リスト
	AplParamVFRValue40,	//VFR Value リスト
	AplParamVFRValue41,	//VFR Value リスト
	AplParamVFRValue42,	//VFR Value リスト
	AplParamVFRValue43,	//VFR Value リスト
	AplParamVFRValue44,	//VFR Value リスト
	AplParamVFRValue45,	//VFR Value リスト
	AplParamVFRValue46,	//VFR Value リスト
	AplParamVFRValue47,	//VFR Value リスト
	AplParamVFRValue48,	//VFR Value リスト
	AplParamVFRValue49,	//VFR Value リスト
	AplParamVFRValue50,	//VFR Value リスト
	AplParamVFRValue51,	//VFR Value リスト
	AplParamVFRValue52,	//VFR Value リスト
	AplParamVFRValue53,	//VFR Value リスト
	AplParamVFRValue54,	//VFR Value リスト
	AplParamVFRValue55,	//VFR Value リスト
	AplParamVFRValue56,	//VFR Value リスト
	AplParamVFRValue57,	//VFR Value リスト
	AplParamVFRValue58,	//VFR Value リスト
	AplParamVFRValue59,	//VFR Value リスト
	AplParamVFRValue60,	//VFR Value リスト
	AplParamVFRValue61,	//VFR Value リスト
	AplParamVFRValue62,	//VFR Value リスト
	AplParamVFRValue63,	//VFR Value リスト
	AplParamVFRValue64,	//VFR Value リスト
	AplParamVFRValue65,	//VFR Value リスト
	AplParamVFRValue66,	//VFR Value リスト
	AplParamVFRValue67,	//VFR Value リスト
	AplParamVFRValue68,	//VFR Value リスト
	AplParamVFRValue69,	//VFR Value リスト
	AplParamVFRValue70,	//VFR Value リスト
	AplParamVFRValue71,	//VFR Value リスト
	AplParamVFRValue72,	//VFR Value リスト
	AplParamVFRValue73,	//VFR Value リスト
	AplParamVFRValue74,	//VFR Value リスト
	AplParamVFRValue75,	//VFR Value リスト
	AplParamVFRValue76,	//VFR Value リスト
	AplParamVFRValue77,	//VFR Value リスト
	AplParamVFRValue78,	//VFR Value リスト
	AplParamVFRValue79,	//VFR Value リスト
	AplParamVFRValue80,	//VFR Value リスト
	AplParamVFRValue81,	//VFR Value リスト
	AplParamVFRValue82,	//VFR Value リスト
	AplParamVFRValue83,	//VFR Value リスト
	AplParamVFRValue84,	//VFR Value リスト
	AplParamVFRValue85,	//VFR Value リスト
	AplParamVFRValue86,	//VFR Value リスト
	AplParamVFRValue87,	//VFR Value リスト
	AplParamVFRValue88,	//VFR Value リスト
	AplParamVFRValue89,	//VFR Value リスト
	AplParamVFRValue90,	//VFR Value リスト
	AplParamVFRValue91,	//VFR Value リスト
	AplParamVFRValue92,	//VFR Value リスト
	AplParamVFRValue93,	//VFR Value リスト
	AplParamVFRValue94,	//VFR Value リスト
	AplParamVFRValue95,	//VFR Value リスト
	AplParamVFRValue96,	//VFR Value リスト
	AplParamVFRValue97,	//VFR Value リスト
	AplParamVFRValue98,	//VFR Value リスト
	AplParamVFRValue99,	//VFR Value リスト
	AplParamVFRValue100,	//VFR Value リスト
	AplParamVFRValue101,	//VFR Value リスト
	AplParamVFRValue102,	//VFR Value リスト
	AplParamVFRValue103,	//VFR Value リスト
	AplParamVFRValue104,	//VFR Value リスト
	AplParamVFRValue105,	//VFR Value リスト
	AplParamVFRValue106,	//VFR Value リスト
	AplParamVFRValue107,	//VFR Value リスト
	AplParamVFRValue108,	//VFR Value リスト
	AplParamVFRValue109,	//VFR Value リスト
	AplParamVFRValue110,	//VFR Value リスト
	AplParamVFRValue111,	//VFR Value リスト
	AplParamVFRValue112,	//VFR Value リスト
	AplParamVFRValue113,	//VFR Value リスト
	AplParamVFRValue114,	//VFR Value リスト
	AplParamVFRValue115,	//VFR Value リスト
	AplParamVFRValue116,	//VFR Value リスト
	AplParamVFRValue117,	//VFR Value リスト
	AplParamVFRValue118,	//VFR Value リスト
	AplParamVFRValue119,	//VFR Value リスト
	AplParamVFRValue120,	//VFR Value リスト
	AplParamVFRValue121,	//VFR Value リスト
	AplParamVFRValue122,	//VFR Value リスト
	AplParamVFRValue123,	//VFR Value リスト
	AplParamVFRValue124,	//VFR Value リスト
	AplParamVFRValue125,	//VFR Value リスト
	AplParamVFRValue126,	//VFR Value リスト
	AplParamVFRValue127,	//VFR Value リスト
	AplParamVFRValue128,	//VFR Value リスト
	AplParamVFRValue129,	//VFR Value リスト
	AplParamVFRValue130,	//VFR Value リスト
	AplParamVFRValue131,	//VFR Value リスト
	AplParamVFRValue132,	//VFR Value リスト
	AplParamVFRValue133,	//VFR Value リスト
	AplParamVFRValue134,	//VFR Value リスト
	AplParamVFRValue135,	//VFR Value リスト
	AplParamVFRValue136,	//VFR Value リスト
	AplParamVFRValue137,	//VFR Value リスト
	AplParamVFRValue138,	//VFR Value リスト
	AplParamVFRValue139,	//VFR Value リスト
	AplParamVFRValue140,	//VFR Value リスト
	AplParamVFRValue141,	//VFR Value リスト
	AplParamVFRValue142,	//VFR Value リスト
	AplParamVFRValue143,	//VFR Value リスト
	AplParamVFRValue144,	//VFR Value リスト
	AplParamVFRValue145,	//VFR Value リスト
	AplParamVFRValue146,	//VFR Value リスト
	AplParamVFRValue147,	//VFR Value リスト
	AplParamVFRValue148,	//VFR Value リスト
	AplParamVFRValue149,	//VFR Value リスト
	AplParamVFRValue150,	//VFR Value リスト
	AplParamVFRValueIndexNTSC,	//現在選択中のVFR (NTSC)
	AplParamVFRValueSystemNTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue1NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue2NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue3NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue4NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue5NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue6NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue7NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue8NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue9NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue10NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue11NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue12NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue13NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue14NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue15NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue16NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue17NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue18NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue19NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue20NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue21NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue22NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue23NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue24NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue25NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue26NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue27NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue28NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue29NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue30NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue31NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue32NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue33NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue34NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue35NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue36NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue37NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue38NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue39NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue40NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue41NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue42NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue43NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue44NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue45NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue46NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue47NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue48NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue49NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue50NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue51NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue52NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue53NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue54NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue55NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue56NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue57NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue58NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue59NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue60NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue61NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue62NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue63NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue64NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue65NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue66NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue67NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue68NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue69NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue70NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue71NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue72NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue73NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue74NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue75NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue76NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue77NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue78NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue79NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue80NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue81NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue82NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue83NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue84NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue85NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue86NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue87NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue88NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue89NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue90NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue91NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue92NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue93NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue94NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue95NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue96NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue97NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue98NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue99NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue100NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue101NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue102NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue103NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue104NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue105NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue106NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue107NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue108NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue109NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue110NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue111NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue112NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue113NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue114NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue115NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue116NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue117NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue118NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue119NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue120NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue121NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue122NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue123NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue124NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue125NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue126NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue127NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue128NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue129NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue130NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue131NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue132NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue133NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue134NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue135NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue136NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue137NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue138NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue139NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue140NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue141NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue142NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue143NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue144NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue145NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue146NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue147NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue148NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue149NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValue150NTSC,	//VFR Value リスト (NTSC)
	AplParamVFRValueIndexPAL,	//現在選択中のVFR (PAL)
	AplParamVFRValueSystemPAL,	//VFR Value リスト (PAL)
	AplParamVFRValue1PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue2PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue3PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue4PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue5PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue6PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue7PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue8PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue9PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue10PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue11PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue12PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue13PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue14PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue15PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue16PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue17PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue18PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue19PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue20PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue21PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue22PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue23PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue24PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue25PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue26PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue27PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue28PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue29PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue30PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue31PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue32PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue33PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue34PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue35PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue36PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue37PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue38PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue39PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue40PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue41PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue42PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue43PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue44PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue45PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue46PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue47PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue48PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue49PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue50PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue51PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue52PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue53PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue54PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue55PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue56PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue57PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue58PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue59PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue60PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue61PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue62PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue63PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue64PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue65PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue66PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue67PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue68PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue69PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue70PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue71PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue72PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue73PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue74PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue75PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue76PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue77PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue78PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue79PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue80PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue81PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue82PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue83PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue84PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue85PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue86PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue87PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue88PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue89PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue90PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue91PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue92PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue93PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue94PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue95PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue96PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue97PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue98PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue99PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue100PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue101PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue102PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue103PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue104PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue105PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue106PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue107PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue108PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue109PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue110PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue111PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue112PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue113PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue114PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue115PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue116PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue117PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue118PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue119PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue120PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue121PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue122PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue123PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue124PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue125PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue126PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue127PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue128PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue129PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue130PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue131PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue132PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue133PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue134PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue135PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue136PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue137PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue138PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue139PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue140PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue141PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue142PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue143PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue144PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue145PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue146PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue147PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue148PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue149PAL,	//VFR Value リスト (PAL)
	AplParamVFRValue150PAL,	//VFR Value リスト (PAL)
	AplParamVFRSettingRangeMax,	//VFR 設定範囲最大値
	AplParamVFRSettingRangeMin,	//VFR 設定範囲最小値
	AplParamShutterMenu,	//CAMERA SETTINGS > SHUTTER
	AplParamShutterSwitch,	//マルチダイヤルのSETと連動
	AplParamShutterDispChg,	//シャッター表示切替
	AplParamShutterDegValue,	//現在選択中のSHUTTER (角度)
	AplParamShutterDegValueIndex,	//現在選択中のSHUTTER
	AplParamShutterDegValueHalf,	//角度表示用のハーフシャッター値
	AplParamShutterDegValue1,	//角度表示用のValueリスト
	AplParamShutterDegValue2,	//角度表示用のValueリスト
	AplParamShutterDegValue3,	//角度表示用のValueリスト
	AplParamShutterDegValue4,	//角度表示用のValueリスト
	AplParamShutterDegValue5,	//角度表示用のValueリスト
	AplParamShutterDegValue6,	//角度表示用のValueリスト
	AplParamShutterDegValue7,	//角度表示用のValueリスト
	AplParamShutterDegValue8,	//角度表示用のValueリスト
	AplParamShutterDegValue9,	//角度表示用のValueリスト
	AplParamShutterDegValue10,	//角度表示用のValueリスト
	AplParamShutterDegValue11,	//角度表示用のValueリスト
	AplParamShutterDegValueIndexNTSC,	//現在選択中のSHUTTER (角度/NTSC)
	AplParamShutterDegValueHalfNTSC,	//角度表示用のハーフシャッター値 (NTSC)
	AplParamShutterDegValue1NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue2NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue3NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue4NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue5NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue6NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue7NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue8NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue9NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue10NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValue11NTSC,	//角度表示用のValueリスト (NTSC)
	AplParamShutterDegValueIndexPAL,	//現在選択中のSHUTTER (角度/PAL)
	AplParamShutterDegValueHalfPAL,	//角度表示用のハーフシャッター値 (PAL)
	AplParamShutterDegValue1PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue2PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue3PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue4PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue5PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue6PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue7PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue8PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue9PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue10PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterDegValue11PAL,	//角度表示用のValueリスト (PAL)
	AplParamShutterSecValue,	//現在選択中のSHUTTER (時間)
	AplParamShutterSecValueHalf,	//時間表示用のハーフシャッター値
	AplParamShutterSecValue1,	//時間表示用のValueリスト
	AplParamShutterSecValue2,	//時間表示用のValueリスト
	AplParamShutterSecValue3,	//時間表示用のValueリスト
	AplParamShutterSecValue4,	//時間表示用のValueリスト
	AplParamShutterSecValue5,	//時間表示用のValueリスト
	AplParamShutterSecValue6,	//時間表示用のValueリスト
	AplParamShutterSecValue7,	//時間表示用のValueリスト
	AplParamShutterSecValue8,	//時間表示用のValueリスト
	AplParamShutterSecValue9,	//時間表示用のValueリスト
	AplParamShutterSecValue10,	//時間表示用のValueリスト
	AplParamShutterSecValue11,	//時間表示用のValueリスト
	AplParamShutterSecValueIndex,	//現在選択中のSHUTTER
	AplParamShutterSecValueIndexNTSC,	//現在選択中のSHUTTER (時間/NTSC)
	AplParamShutterSecValueHalfNTSC,	//時間表示用のハーフシャッター値 (NTSC)
	AplParamShutterSecValue1NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue2NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue3NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue4NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue5NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue6NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue7NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue8NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue9NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue10NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValue11NTSC,	//時間表示用のValueリスト (NTSC)
	AplParamShutterSecValueIndexPAL,	//現在選択中のSHUTTER (時間/PAL)
	AplParamShutterSecValueHalfPAL,	//時間表示用のハーフシャッター値 (PAL)
	AplParamShutterSecValue1PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue2PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue3PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue4PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue5PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue6PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue7PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue8PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue9PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue10PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecValue11PAL,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecSettingRangeMax,	//時間表示用のValueリスト (PAL)
	AplParamShutterSecSettingRangeMin,	//時間表示用のValueリスト (PAL)
	AplParamEIMenu,	//CAMERA SETTINGS > EI
	AplParamGainIsoDispChg,	//Gain/ISO表示切替
	AplParamISOSelect,	//使用するISOを選択する
	AplParamNativeISO,	//NATIVEのISOを選択
	AplParam800BaseISO,	//800BASEのISOを選択
	AplParam2500BaseISO,	//2500BASEのISOを選択
	AplParamNativeISOSdiRawNotVideo,	//NATIVEのISOを選択 (Sdi Raw [GAMMA]≠VIDEO)
	AplParamNativeISOSdiRawVideo,	//NATIVEのISOを選択 (Sdi Raw [GAMMA]=VIDEO)
	AplParamNativeISOSdiRaw2_2_K,	//NATIVEのISOを選択 (Sdi Raw SensorMode:2.2K)
	AplParamNativeISOSensor2_2_K,	//NATIVEのISOを選択 (SensorMode:2.2K)
	AplParamNativeISONotVideo,	//NATIVEのISOを選択 ([GAMMA]≠VIDEO)
	AplParamNativeISOVideo,	//NATIVEのISOを選択([GAMMA]=VIDEO)
	AplParam800BaseISOSdiRawNotVideo,	//800BASEのISOを選択 (Sdi Raw [GAMMA]≠VIDEO)
	AplParam800BaseISOSdiRawVideo,	//800BASEのISOを選択 (Sdi Raw [GAMMA]=VIDEO)
	AplParam800BaseISOSdiRaw2_2_K,	//800BASEのISOを選択 (Sdi Raw SensorMode:2.2K)
	AplParam800BaseISOSensor2_2_K,	//800BASEのISOを選択 (SensorMode:2.2K)
	AplParam800BaseISONotVideo,	//800BASEのISOを選択 ([GAMMA]≠VIDEO)
	AplParam800BaseISOVideo,	//800BASEのISOを選択([GAMMA]=VIDEO)
	AplParam2500BaseISOSdiRawNotVideo,	//2500BASEのISOを選択 (Sdi Raw [GAMMA]≠VIDEO)
	AplParam2500BaseISOSdiRawVideo,	//2500BASEのISOを選択 (Sdi Raw [GAMMA]=VIDEO)
	AplParam2500BaseISOSdiRaw2_2_K,	//2500BASEのISOを選択 (Sdi Raw SensorMode:2.2K)
	AplParam2500BaseISOSensor2_2_K,	//2500BASEのISOを選択 (SensorMode:2.2K)
	AplParam2500BaseISONotVideo,	//2500BASEのISOを選択 ([GAMMA]≠VIDEO)
	AplParam2500BaseISOVideo,	//2500BASEのISOを選択([GAMMA]=VIDEO)
	AplParam3200BaseISO,	//3200BASEのISOを選択
	AplParamGainSwitch,	//Gainのモード選択
	AplParamGainSelect,	//GainSelectの状態 (非EEPROM)
	AplParamGainSelectNormalNotVideo,	//GainSelectの状態 (SW = Normal、GAMMA ≠Video)
	AplParamGainSelectNormalVideo,	//GainSelectの状態 (SW = Normal、GAMMA = Video)
	AplParamGainSelectHighNotVideo,	//GainSelectの状態 (SW = High、GAMMA ≠Video)
	AplParamGainSelectHighVideo,	//GainSelectの状態 (SW = High、GAMMA =Video)
	AplParamGainSelectNormalSensor2_2_K,	//GainSelectの状態 (SensorMode:2.2K)
	AplParamGainSelectHighSensor2_2_K,	//GainSelectの状態 (SensorMode:2.2K)
	AplParamWhiteMenu,	//CAMERA SETTINGS > WHITE
	AplParamAwb,	//AWB動作  (非EEPROM)
	AplParamWhiteValueTemp,	//AWBの現在の選択値を保持 (K)
	AplParamWhiteValueGMg,	//AWBの現在の選択値を保持 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValueAWBResult,	//AWB実行結果
	AplParamWhiteValueIndex,	//現在選択中のWhiteValue選択中
	AplParamWhiteValueATWTemp,	//Index値の0始まり用のDummy
	AplParamWhiteValueATWGMg,	//Index値の0始まり用のDummy
	AplParamWhiteValueAWBMemoryTemp,	//AWBの値を保持 (K)
	AplParamWhiteValueAWBMemoryGMg,	//AWBの値を保持 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue1Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue1GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue2Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue2GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue3Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue3GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue4Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue4GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue5Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue5GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue6Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue6GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue7Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue7GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue8Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue8GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue9Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue9GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamWhiteValue10Temp,	//ADDで追加したWhiteの値 (K)
	AplParamWhiteValue10GMg,	//ADDで追加したWhiteの値 (GMg) -10.0～10.0で10倍した値で保持
	AplParamNRMenu,	//CAMERA SETTINGS > NR
	AplParamNRISO800,	//Noize ReductionのON/OFF
	AplParamNRISO2500,	//Noize ReductionのON/OFF
	AplParamNRISO3200,	//Noize ReductionのON/OFF
	AplParamLensSettingMenu,	//CAMERA SETTINGS > LENS SETTING
	AplParamAIrisLevelEffect,	//A. IRIS LEVEL EFFECT (0-100)
	AplParamAIrisPeakAve,	//A. IRIS PEAK/AVE
	AplParamIrisDial,	//絞り方向(アイリス方向)
	AplParamAfOffSet,	//AutoFocusの合焦位置
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
	AplParamCounterMode,	//カウンター表示切替 (TC/UB/Dur )
	AplParamAudioSettingsMenu,	//AUDIO SETTINGS
	AplParamInSelectCH1,	//CH1 IN SELECT
	AplParamInSelectCH2,	//CH2 IN SELECT
	AplParamSelInput1,	//音声入力信号設定1
	AplParamSelInput2,	//音声入力信号設定2
	AplParamMicPower1,	//外部マイク電源切替1
	AplParamMicPower2,	//外部マイク電源切替2
	AplParamHpMode,	//<PHONES>端子から出力する音声をモニター出力に合わせて遅延させるかどうか
	AplParamVolume,	//<PHONES>端子から出力する音声レベル
	AplParamRecBeepSoundMenu,	//AUDIO SETTINGS > REC BEEP SOUND
	AplParamRecBeepSoundMode,	//Recbeep音モード
	AplParamRecBeepVolume,	//Recbeep音量
	AplParamOutputSettingMenu,	//OUTPUT SETTING
	AplParamSdiOutSignalSelect,	//SDI端子からの出力信号選択
	AplParamSdiOutIndicatorDisp,	//SDI端子からの出力に[SDI/HDMI INDICATOR]で設定する項目の表示非表示
	AplParamSdiOutMarkerDisp,	//SDI端子からの出力に[SDI/HDMI MARKER]で設定する項目の表示非表示
	AplParamSdiOutMenuDisp,	//SDI端子からの出力にメニューの表示非表示
	AplParamHdmiOutSignalSelect,	//HDMI端子からの出力信号選択
	AplParamHdmiOutIndicatorDisp,	//HDMI端子からの出力に[SDI/HDMI INDICATOR]で設定する項目の表示非表示
	AplParamHdmiOutMarkerDisp,	//HDMI端子からの出力に[SDI/HDMI MARKER]で設定する項目の表示非表示
	AplParamHdmiOutMenuDisp,	//HDMI端子からの出力にメニューの表示非表示
	AplParamOutIndicatorMenu,	//OUTPUT SETTING > SDI/HDMI INDICATOR
	AplParamOutIndicatorCharLuminance,	//キャラクターの輝度を設定
	AplParamOutIndicatorClipName,	//記録Clip名
	AplParamOutIndicatorPixcelFreq,	//システムピクセルおよび周波数
	AplParamOutIndicatorMainColor,	//MAIN記録カラー設定
	AplParamOutIndicatorRecFormat,	//MAIN記録フォーマット
	AplParamOutIndicatorSlotStatus,	//SDカードスロット状態
	AplParamOutIndicator2SlotFunc,	//2スロット機能状態
	AplParamOutIndicatorTC,	//タイムコード
	AplParamOutIndicatorBatteryRemain,	//バッテリー残量アイコン
	AplParamOutIndicatorRecFuncMode,	//記録機能状態
	AplParamOutIndicatorRecRemote,	//SDI/HDMI出力へのREC指示状態
	AplParamOutIndicatorAudioLevelMeter,	//オーディオレベルメータ
	AplParamOutIndicatorFps,	//フレームレート
	AplParamOutIndicatorShutter,	//シャッター速度方向
	AplParamOutIndicatorEi,	//EI状態
	AplParamOutIndicatorWhite,	//ホワイトバランス
	AplParamOutIndicatorIrisZoom,	//EFレンズのIRIS/ZOOM情報
	AplParamOutIndicatorNdFilter,	//NDフィルター
	AplParamOutIndicatorEIS_DZOOM,	//EISおよびDZOOM情報
	AplParamOutIndicatorWlan,	//無線LAN接続状態
	AplParamOutIndicatorIRRec,	//IR RECモード
	AplParamOutIndicatorSpotMeter,	//SPOT METER
	AplParamOutIndicatorPlayBackStatus,	//再生状態
	AplParamOutMarkerMenu,	//OUTPUT SETTING > SDI/HDMI MARKER
	AplParamOutMarkerLuminance,	//マーカーの輝度
	AplParamOutMarkerCenterMarkerType,	//センターマーカーの切替
	AplParamOutMarkerSaftyMarkerType,	//セーフティーゾーンの枠の種類
	AplParamOutMarkerSafetyArea,	//セーフティーゾーンの枠の大きさ
	AplParamOutMarkerFrameMarker,	//フレームマーカーの画角
	AplParamOutMarkerFrameMarkerColor,	//フレームマーカーの色
	AplParamOutMarkerPlayBackMarker,	//SDI/HDMI端子からの再生映像出力にマーカ表示するかどうか
	AplParamLcdIndicatorMenu,	//OUTPUT SETTING > LCD INDICATOR
	AplParamLcdIndicatorCharLuminance,	//キャラクターの輝度を設定
	AplParamLcdIndicatorClipName,	//記録Clip名
	AplParamLcdIndicatorPixcelFreq,	//システムピクセルおよび周波数
	AplParamLcdIndicatorMainColor,	//MAIN記録カラー設定
	AplParamLcdIndicatorTC,	//タイムコード
	AplParamLcdIndicatorEi,	//EI状態
	AplParamLcdIndicatorIrisZoom,	//EFレンズのIRIS/ZOOM情報
	AplParamLcdIndicatorEIS_DZOOM,	//EISおよびDZOOM情報
	AplParamLcdIndicatorSpotMeter,	//SPOT METER
	AplParamLcdMarkerMenu,	//OUTPUT SETTING > LCD MARKER
	AplParamLcdMarkerLuminance,	//マーカーの輝度
	AplParamLcdMarkerPlayBackMarker,	//SDI/HDMI端子からの再生映像出力にマーカ表示するかどうか
	AplParamLcdFocusAssistMenu,	//OUTPUT SETTING > LCD FOCUS ASSIST
	AplParamZebra,	//ZEBRA
	AplParamZebraMode,	//ZEBRA MODE
	AplParamLcdFocusExpandPeakSqMode,	//PEAK./SQUARES MODE
	AplParamLcdFocusExpandOpenIrisMode,	//オープンアイリスフォーカスアシスト駆動時間
	AplParamLcdEIAssistMenu,	//OUTPUT SETTING > LCD EI ASSIST
	AplParamLcdEIAssistSpotMeterDisp,	//スポットメーター表示単位
	AplParamLcdEIAssistSpotMeterSize,	//スポットメーター表示サイズ
	AplParamNetworkSettingsMenu,	//NETWORK SETTING
	AplParamWirelessLanMode,	//外部機器とワイヤレスLANで接続するかどうか
	AplParamMyMacAddress,	//自分のMACアドレス
	AplParamNetworkFuncMenu,	//NETWORK SETTING > NETWORK FUNC
	AplParamUserAccountMode,	//ネットワーク認証で使用するユーザアカウント
	AplParamNetworkPropertyMenu,	//NETWORK SETTING > NETWORK PROPERTY
	AplParamNetworkToolMenu,	//OPTION
	AplParamUserAccountMenu,	//NETWORK SETTINGS>NETWORK FUNC>USER ACCOUNT
	AplParamConnectionHistoryMenu,	//NETWORK SETTINGS>CONNECTION HISTORY
	AplParamOptionMenu,	//OPTION
	AplParamVerDown,	//バージョンダウン後の初期設定
	AplParamRepeat,	//リピート再生
	AplParamFileNumberReset_HDD_SDP,	//ファイル番号リセット (HDD/内蔵メモリ SDP)
	AplParamFileNumberReset_HDD_MP4,	//ファイル番号リセット (HDD/内蔵メモリ MP4)
	AplParamFileNumberReset_SD_SDP,	//ファイル番号リセット (SD カード SDP)
	AplParamFileNumberReset_SD_MP4,	//ファイル番号リセット (SD カード MP4)
	AplParamJpegFileNo,	//静止画記録ファイルナンバー(SD)
	AplParamFolderNumber,	//静止画記録フォルダナンバー(SD)
	AplParamHDD_JpegFileNo,	//静止画記録ファイルナンバー(HDD)
	AplParamHDD_FolderNumber,	//静止画記録フォルダナンバー(HDD)
	AplParamUsbMode,	//USBモード
	AplParamUsbSW,	//USB入、切
	AplParamPowerOffOperation,	//電源OFF操作
	AplParamSuperGainSet,	//スーパーゲイン
	AplParamSuperGainIso,	//スーパーゲイン(ISO表示)
	AplParamSuperGainIsoSet,	//スーパーゲイン制御情報(ISO表示)
	AplParamSensitivityExtension,	//感度拡張
	AplParamFocusMode,	//ＡＦ／ＭＦ切換 （フォーカス切替）
	AplParamShutterMode,	//電子シャッター速度
	AplParamSynchroScanMode,	//シンクロスキャンモード
	AplParamIrisMode,	//絞り
	AplParamGainMode,	//ゲイン
	AplParamGainSW,	//ゲインスイッチ(AplCamバックアップ用)
	AplParamGainModeISO,	//ゲインISO
	AplParamWhiteBalanceMode,	//ホワイトバランス
	AplParamWbSemiPro,	//ホワイトバランス(業務用)
	AplParamWbMnlSemiPro,	//ホワイトバランスマニュアル設定(業務用)
	AplParamWhiteBalanceSetInfoA,	//ホワイトバランスセットの結果情報　A
	AplParamWhiteBalanceSetInfoB,	//ホワイトバランスセットの結果情報　B
	AplParamWhiteBalanceChannel,	//ホワイトバランス Ach / Bch
	AplParamVar,	//VARモード　色温度指定
	AplParamWBPreSet,	//WBプリセット
	AplParamMasterDetailPro,	//マスターディテール（セミプロ用）
	AplParamDetailCoringPro,	//ディテール　コアリング（セミプロ用）
	AplParamMasterPedestalPro,	//マスターペデスタル　上位（セミプロ用）
	AplParamChromaLevelPro,	//クロマレベル（セミプロ用）
	AplParamGammaPro,	//ガンマモード(セミプロ用)
	AplParamBlackGamma,	//黒ガンマ
	AplParamBlackGammaRange,	//黒ガンマ幅
	AplParamKneeMode,	//ニーモード
	AplParamKneeMasterPoint,	//ニーマスターポイント　上位（セミプロ用）
	AplParamKneeMasterSlope,	//ニーマスタースロープ
	AplParamSkinToneDtl,	//スキンディテール
	AplParamVDetailLevel,	//V ディテール
	AplParamAutoIrisLevelEffect,	//オートアイリスレベル
	AplParamAutoIrisLevelEffectValue,	//オートアイリスレベル効果
	AplParamDRS,	//DRS
	AplParamNrControl,	//NRコントロール
	AplParamKneeApeLevel,	//ニーAPEレベル
	AplParamDetailLevel,	//ディテールレベル
	AplParamAFConformity,	//AF追従設定
	AplParamAFRangeValue,	//AFエリア幅(上位バイト)
	AplParamAfAreaWidth,	//AF AREA WIDTH（削除予定）
	AplParamOpeningAngle,	//開角度(上位バイト)
	AplParamIsoLow,	//ISO Low
	AplParamIsoMid,	//ISO Mid
	AplParamIsoHigh,	//ISO High
	AplParamAgcMaxISO,	//AGC　MAX　ISO
	AplParamWFM,	//WFM
	AplParamWFMPos,	//WFM位置
	AplParamDispModeCheck,	//DISP MODE ボタン状態保持
	AplParamSubRecButton,	//サブ REC ボタン
	AplParamSubZoom,	//サブズーム
	AplParamToggleButtonWb,	//トグルボタン　WB
	AplParamToggleButtonGain,	//トグルボタン　ゲイン
	AplParamMicLevelValue,	//マイクレベル値
	AplParamAvComponent,	//コンポーネント/AV出力切り替え
	AplParamPowerLcd_Auto,	//パワー LCD Auto 設定
	AplParamBalanceShot,	//傾き補正
	AplParamDirectRec,	//DirectRec
	AplParamReStartMode,	//システムリセット後の起動モード
	AplParamLcdEvf,	//LCD/EVF
	AplParamDualCodecRec,	//デュアルコーデック記録
	AplParamPlayContent,	//再生対象コンテンツ
	AplParamMovieAspect,	//ASPECT
	AplParamVLogMode,	//V-LOGモード
	AplParamAreaSize,	//エリア機能　枠サイズ
	AplParamSafetyZone,	//セーフティゾーン領域表示種類( アスペクト比 16:9 )
	AplParamSafetyZone_4_3,	//セーフティゾーン領域表示( アスペクト比 4:3 )
	AplParamVideoOutOsd,	//OSD 表示と映像との同時出力
	AplParamAudioAlcLinked,	//オーディオALC連動
	AplParamAudioAlcCH1,	//オーディオALC1
	AplParamAudioAlcCH2,	//オーディオALC2
	AplParamVFRFps60p,	//VFR FPS(59.94Hz 60p) 
	AplParamVFRFps30p,	//VFR FPS(59.94H 30p) 
	AplParamVFRFps24p,	//VFR FPS(59.94Hz 24p) 
	AplParamVFRFps50p,	//VFR FPS(50.00Hz 50p) 
	AplParamVFRFps25p,	//VFR FPS(50.00Hz 25p) 
	AplParamDummyMenu,	//メニュー切り分け
	AplParam3DAdaptor,	//（削除候補）3D アダプター識別
	AplParam3DDisplay,	//（削除候補）3D テレビ出力
	AplParam3DOutput,	//（削除候補）3D 画像出力選択
	AplParam2D3DViewRec,	//（削除候補）2D/3D表示 (撮影モード)
	AplParam2D3DViewPlay,	//（削除候補）2D/3D表示 (再生モード)
	AplParam3D2DRecMode,	//（削除候補）3D / 2D 撮影モードの切替え
	AplParamConv2DTo3D,	//（削除候補）2D → 3D 変換
	AplParamPlay3DWarning,	//（削除候補）再生モード：3D警告表示
	AplParamPlayLcd3DOutput,	//（削除候補）液晶表示モード - 3D (再生モード)
	AplParamLcd2DOutput,	//（削除候補）液晶表示モード - 2D
	AplParamPanAngle,	//（削除候補）回転角度
	AplParamTiltAngle,	//（削除候補）チルト角度
	AplParamTiltSpeed,	//（削除候補）チルト速度
	AplParamPanTilterMode,	//（削除候補）リモートパンチルターモード
	AplParamPanTilterVerUpResult,	//（削除候補）パンチルターバージョンアップ結果
	AplParamPanTilterAutoConnectFlag,	//（削除候補）パンチルター自動接続フラグ
	AplParamTRFCurrentPagePlay,	//（削除候補）TRF ページ保持 (再生アプリ)
	AplParamDioramaExposure,	//（削除候補）明るさ(ジオラマ)
	AplParam8mmExposure,	//（削除候補）明るさ(8mm)
	AplParamSilentExposure,	//（削除候補）明るさ(サイレント)
	AplParamDioramaVividness,	//（削除候補）鮮やかさ(ジオラマ)
	AplParamEffect,	//（削除候補）動画エフェクト(選択)
	AplParam8mmShade,	//（削除候補）色合い(8mm)
	AplParamFaceRecognition,	//（削除候補）個人認証
	AplParamRecognitionNum,	//（削除候補）名前表示 (個人認証表示人数)
	AplParamEyeFiTransfer,	//（削除候補）Eye-Fi転送
	AplParamEyeFiFileSize,	//（削除候補）Eye-Fiファイルサイズ
	AplParamEyeFiPowerControl,	//（削除候補）Eye-Fi電源管理
	AplParamWifiSetConfirm,	//（削除候補）Wi-Fi設定誘導フラグ
	AplParamWifiMenuApSetConfirm,	//（削除候補）Wi-Fiメニュー AP設定誘導フラグ
	AplParamSubCamWb,	//（削除候補）サブカメラ WB
	AplParamSubCamFocus,	//（削除候補）サブカメラ フォーカス
	AplParamSubCamExposure,	//（削除候補）サブカメラ 明るさ調整
	AplParamSubCamPower,	//（削除候補）サブカメラ 電源
	AplParamSubCamWipePos,	//（削除候補）サブカメラ ワイプ位置
	AplParamSoundSceneSelect,	//（削除候補）サウンドシーンセレクト
	AplParamSoundSceneSelectGain,	//（削除候補）サウンドシーンセレクト　ゲイン
	AplParamSoundSceneSelectDirectivity,	//（削除候補）サウンドシーンセレクト　指向性
	AplParamSoundSceneSelectFrequencyHigh,	//（削除候補）サウンドシーンセレクト　F特-高域
	AplParamSoundSceneSelectFrequencyLow,	//（削除候補）サウンドシーンセレクト　F特-低域
	AplParamAeMode,	//（削除候補）シーンモード
	AplParamTimeLapseAeMode,	//（削除候補）シーンモード(インターバル記録専用)
	AplParamTitlePictureSetup,	//（削除候補）ムービースライドショー「タイトル設定」
	AplParamFavoriteScenePlay,	//（削除候補）ムービースライドショー「お気に入りシーン再生」
	AplParamBabyCalendar,	//（削除候補）ベビーカレンダー
	AplParamLastDispBaby,	//（削除候補）ベビーカレンダー　最終表示
	AplParamAnimationAssist,	//（削除候補）パラパラ写真モード
	AplParamHighSpeedMode,	//（削除候補）高速撮像モード
	AplParamSlowRecSetting,	//（削除候補）スーパースロー撮影設定
	AplParamSlowPlaySetting,	//（削除候補）スロー区間再生速度
	AplParamBurstShooting,	//（削除候補）高速連写
	AplParamLoopRec,	//（削除候補）ループ記録
	AplParamLoopRecAudio,	//（削除候補）ループ記録音声
	AplParamAudioRec,	//（削除候補）音声記録
	AplParamTimeLapse,	//（削除候補）インターバル記録（タイムラプス）
	AplParam24PMode,	//（削除候補）デジタルシネマ
	AplParamDCIMode,	//（削除候補）デジタルシネマカラー(DCC)
	AplParamMicChannel,	//（削除候補）5.1ch/2ch
	AplParamMicLevel,	//（削除候補）マイクレベル
	AplParamMicLevelAgc,	//（削除候補）マイクレベル設定 (AGC)
	AplParamZoomMic,	//（削除候補）ズームマイク
	AplParamMicMode,	//（削除候補）マイク設定
	AplParamBassEnphasis,	//（削除候補）バスコントロール
	AplParamWindNoiseCanceller,	//（削除候補）風音キャンセラー
	AplParamExtMicWarning,	//（削除候補）外部マイク警告表示
	AplParamPictureExposureCorection,	//（削除候補）画質調整(明るさ)
	AplParamPictureDetail,	//（削除候補）画質調整(シャープネス)
	AplParamPictureColorLevel,	//（削除候補）画質調整(色の濃さ)
	AplParamWBAdjustB,	//（削除候補）画質調整(WB微調整)BCｈ
	AplParamWBAdjust,	//（削除候補）画質調整(WB微調整)
	AplParamIAPlusExposure,	//（削除候補）明るさ(iA+)
	AplParamIAPlusWBAdjust,	//（削除候補）WB調整(iA)
	AplParamiAMode,	//（削除候補）おまかせIA
	AplParamMenuIAPlus,	//（削除候補）インテリジェントオートプラス(iA+)
	AplParamOisCustomize,	//（削除候補）手ブレ補正カスタマイズ
	AplParamOisEffectMode,	//（削除候補）手振れ補正効果モード
	AplParamMenuOisMode,	//（削除候補）手ブレ補正モード（メニュー設定項目）
	AplParamAutoAFAE,	//（削除候補）追っかけフォーカスON/OFF
	AplParamLedMode,	//（削除候補）ビデオライト (LEDライト)
	AplParamModulateVideoLightMode,	//（削除候補）調光ビデオライトモード
	AplParamFlashMode,	//（削除候補）フラッシュ
	AplParamFlashQuantityMode,	//（削除候補）フラッシュ明るさ
	AplParamRedEyeMode,	//（削除候補）赤目軽減
	AplParamAFLightMode,	//（削除候補）AF補助光
	AplParamContrastRevise,	//（削除候補）コントラスト視覚補正
	AplParamDarkRevise,	//（削除候補）暗部補正
	AplParamFade,	//（削除候補）フェード
	AplParamFadeColor,	//（削除候補）フェード色
	AplParamSlowShutter,	//（削除候補）オートスローシャッター (通常)
	AplParamBackLight,	//（削除候補）逆光補正
	AplParamBackLightForBackUp,	//（削除候補）逆光補正（バックアップ有り）
	AplParamTelmacro,	//（削除候補）テレマクロ
	AplParamNightMode,	//（削除候補）ナイトモード
	AplParamIRLight,	//（削除候補）赤外線ライト
	AplParamSelfTimer,	//（削除候補）セルフタイマー
	AplParamCursorAutoMove,	//（削除候補）文字カーソル自動移動
	AplParamPrevRecMode,	//（削除候補）前回の撮影モード
	AplParamRecPowerOffOperation,	//（削除候補）記録モードの電源OFF操作
	AplParamOsdMode,	//（削除候補）画面表示
	AplParamExtDisplay,	//（削除候補）外部出力表示
	AplParamDispFaceFrame,	//（削除候補）顔検出枠表示
	AplParamRecGridLine,	//（削除候補）撮影ガイドライン
	AplParamPlayGuideLine,	//（削除候補）再生ガイドライン
	AplParamLuminance,	//（削除候補）輝度表示
	AplParamHistogram,	//（削除候補）ヒストグラム表示
	AplParamUserButtonDisplay,	//（削除候補）USER ボタン表示
	AplParamOtherDisplay,	//（削除候補）その他情報の表示
	AplParamCardAndBattery,	//（削除候補）カード記録算容量・バッテリーマーク表示
	AplParamLensStatus,	//（削除候補）レンズ情報表示
	AplParamAudioLevelMeter,	//（削除候補）オーディオレベルメーター
	AplParamLevelMeter,	//（削除候補）オーディオレベルメーター表示
	AplParamLensCoverWarning,	//（削除候補）レンズカバー警告表示
	AplParamDateOsdMode,	//（削除候補）日時表示
	AplParamWarningSoundMode,	//（削除候補）お知らせ音
	AplParamShutterSoundMode,	//（削除候補）シャッター音
	AplParamAgs,	//（削除候補）うっかり撮り防止
	AplParamRimoconEnable,	//（削除候補）リモコン
	AplParamDemoMode,	//（削除候補）デモモード
	AplParamRecNaviMode,	//（削除候補）撮影アシスト
	AplParamMmr,	//（削除候補）マルチマニュアルリング
	AplParamPowerSave,	//（削除候補）エコモード (バッテリ)
	AplParamPowerSaveAC,	//（削除候補）エコモード (AC)
	AplParamPowerSaveACTime,	//（削除候補）エコモード (AC) 設定時間 (分)
	AplParamBootCamp,	//（削除候補）クイックパワーオン(起動時間)
	AplParamEvfBrightnessLevel,	//（削除候補）EVF 明るさ設定
	AplParamEvfExposure,	//（削除候補）EVF調整(明るさ)
	AplParamNormalTv,	//（削除候補）接続するテレビ
	AplParamVideoOutput,	//（削除候補）VIDEO出力
	AplParamHdmiUhdOutputLimit,	//（削除候補）HDMI UHD出力制限
	AplParamVideoSetup,	//（削除候補）ビデオセットアップ
	AplParamConponent,	//（削除候補）コンポーネント出力
	AplParamHdmiControl,	//（削除候補）ビエラリンク(VIERA　Link)
	AplParamWTHomeArea,	//（削除候補）ワールドタイム設定地域 (ホーム)
	AplParamWorldTimeInitialize,	//（削除候補）ワールドタイム 初期設定フラグ
	AplParamWTHomeSummerTime,	//（削除候補）ワールドタイム　ホームサマータイム
	AplParamWTTravelSummerTime,	//（削除候補）ワールドタイム　旅行先サマータイム
	AplParamClockLinkedSet,	//（削除候補）サマータイム時計連動設定
	AplParamPlayEffect,	//（削除候補）再生 - 効果設定
	AplParamMovieSlideshowEffectKind,	//（削除候補）ハイライト再生「再生効果」
	AplParamHighLightPlayTime,	//（削除候補）ハイライト再生時間
	AplParamSlideshowPlaySet,	//（削除候補）写真スライドショー「再生設定」
	AplParamSlideShowInterval,	//（削除候補）スライドショー間隔
	AplParamBgmInfo,	//（削除候補）音楽(BGM)
	AplParamMnlBgmInfo,	//（削除候補）音楽(BGM) マニュアルムービースライドショー用
	AplParamFilmRoll,	//（削除候補）フィルムロール間隔
	AplParamFilmRoleRequestedMinutes,	//（削除候補）フィルムロール間隔指定時間（分）
	AplParamPinPDisplay,	//（削除候補）PinP表示
	AplParamPinPPosition,	//（削除候補）PinP表示位置
	AplParamPinPSize,	//（削除候補）子画面機能
	AplParamOsdOffWithTally,	//（削除候補）タリー点灯時表示
	AplParamRemoconID,	//（削除候補）赤外線リモコンID
	AplParamZoomSpeed,	//（削除候補）ズーム速度(AW-RP50　リモコン)
	AplParamHDCom60SecStandby,	//（削除候補）HDコム60秒スタンバイ
	AplParamSelfReset,	//（削除候補）セルフリセット
	AplParamExposureCorectionControl,	//（削除候補）コントラスト操作
	AplParamIntermittentCapture,	//（削除候補）間欠写真記録
	AplParamAngleOfView,	//（削除候補）画角モード(ウェアラブル)
	AplParamWearableRecMode,	//（削除候補）撮影モード(ウェアラブル)
	AplParamTallyLedMode,	//（削除候補）撮影ランプ（民生モデル用）
	AplParamRecLamp,	//（削除候補）撮影ランプ（業務モデル用）
	AplParamSystemFrequencyEngineerFlag,	//（削除候補）デバッグシステム周波数切換フラグ
	AplParamSystemFrequencyVisiblity,	//（削除候補）24Pモード切換(システム周波数メニュー表示)
	AplParam4KUpdate,	//（削除候補）2UHDメニュー表示フラグ（デバッグ用）
	AplParamDebugMode,	//（削除候補）デバッグ情報
	AplParamDummyEnum1,	//（削除候補）コンパイル用のダミーENUM
	AplParamDummyEnum2,	//（削除候補）コンパイル用のダミーENUM
	AplParamDummyEnum3,	//（削除候補）コンパイル用のダミーENUM
	AplParamImageResolution,	//（削除候補）画像解像度
	AplParamAspect,	//（削除候補）画像横縦比 （アスペクト比）
	AplParamPictureSize,	//（削除候補）（動画）
	AplParamPictureSize_16_9,	//（削除候補）記録画素数（写真 16:9）
	AplParamPictureSize_3_2,	//（削除候補）（写真 3:2）
	AplParamPictureSize_4_3,	//（削除候補）記録画素数（写真 4:3）
	AplParamJpegQuality,	//（削除候補）クオリティ (写真画質)   【12春ではメニュー無】
	AplParam60PMode,	//（削除候補）60Pモード(ボタン)
	AplParamRecModeMP4,	//（削除候補）記録方式（PCフレンドリー）
	AplParamHDQuality,	//（削除候補）記録モード（HD）
	AplParamMP4Quality,	//（削除候補）記録モード（MP4）
	AplParamOutBits,	//（削除候補）出力ビット数
	AplParam2DRecMode59Hz,	//（削除候補）2D 記録フォーマット (59.9 Hz 用)
	AplParam2DRecMode50Hz,	//（削除候補）2D 記録フォーマット (50.0 Hz 用)
	AplParamHDQuality59Hz,	//（削除候補）[59.9 Hz 用]AVCHD
	AplParamHDQuality50Hz,	//（削除候補）[50 Hz 用]AVCHD
	AplParamMP4Quality59Hz,	//（削除候補）[59.9 Hz 用]MP4
	AplParamMP4Quality50Hz,	//（削除候補）[50 Hz 用]MP4
	AplParamMP4LPCMQuality59Hz,	//（削除候補）[59.9 Hz 用]MP4(LPCM)
	AplParamMP4LPCMQuality50Hz,	//（削除候補）[50 Hz 用]MP4(LPCM)
	AplParamMOVLPCMQuality59Hz,	//（削除候補）[59.9 Hz 用]MOV(LPCM)
	AplParamMOVLPCMQuality50Hz,	//（削除候補）[50 Hz 用]MOV(LPCM)
	AplParamRecFormat59Hz_OutBits_10Bit,	//（削除候補）撮影フォーマット（NTSC） 出力ビット数　10Bit用
	AplParamRecFormat50Hz_OutBits_10Bit,	//（削除候補）撮影フォーマット（PAL） 出力ビット数　10Bit用
	AplParamDigitalZoomMode,	//（削除候補）ズームモード
	AplParamDigitalZoomVal,	//デジタルズーム
	AplParamSubZoomSemiPro,	//（削除候補）サブズーム(業務用)
	AplParamEnableFastZoom,	//Fast Zoom
	AplParamShakeAmplitude,	//（削除候補）ブレ振幅
	AplParamShakeFrequency,	//（削除候補）ブレ周波数
	AplParamFocusTransition1,	//（削除候補）フォーカストランジション登録1
	AplParamFocusTransition2,	//（削除候補）フォーカストランジション登録2
	AplParamFocusTransition3,	//（削除候補）フォーカストランジション登録3
	AplParamFocusTransitionRec,	//（削除候補）フォーカストランジションレック
	AplParamFocusTransitionWait,	//（削除候補）フォーカストランジションウエイト
	AplParamFocusTransitionTime,	//（削除候補）フォーカストランジションタイム
	AplParamFocusExpandScale,	//（削除候補）フォーカスエキスパンド倍率
	AplParamMfAssist,	//（削除候補）MFアシスト
	AplParamMfAutoAssistMode,	//（削除候補）MFアシストモード
	AplParamFocusAssist2,	//（削除候補）フォーカスアシスト2
	AplParamPeakingColor,	//（削除候補）ピーキング色
	AplParamPeakingLevel,	//（削除候補）ピーキングレベル
	AplParamPeakingFreq,	//（削除候補）ピーキング周波数
	AplParamFocusRingDrive,	//（削除候補）フォーカスリング駆動切換
	AplParamFocusRing,	//（削除候補）フォーカス方向
	AplParamShutterRing,	//（削除候補）シャッター速度方向
	AplParamReverseRotationRing,	//（削除候補）ズームリング方向反転
	AplParamAgcMaxUhd,	//（削除候補）AGC MAX UHD (enum定義(型名)はAGC MAXの定義を使う)
	AplParamIRRecColor,	//（削除候補）赤外線撮影色
	AplParamIRLightForBackup,	//（削除候補）赤外線ライト(バックアップあり)
	AplParamIris,	//（削除候補）アイリス
	AplParamGamma,	//（削除候補）ガンマ（削除予定）
	AplParamWideAngleLensSet,	//（削除候補）ワイコンレンズ設定
	AplParamLowLux,	//（削除候補）LowLux
	AplParamMatrix,	//（削除候補）マトリックス
	AplParamChromaPhasePro,	//（削除候補）クロマフェーズ(セミプロ用)
	AplParamCustomAfFunction,	//（削除候補）カスタムAF機能
	AplParamB_B_Mg_Saturation,	//（削除候補）カラーコレクションB_B_Mg 彩度
	AplParamB_B_Mg_Phase,	//（削除候補）カラーコレクションB_B_Mg 色相
	AplParamMg_Saturation,	//（削除候補）カラーコレクションMg 彩度
	AplParamMg_Phase,	//（削除候補）カラーコレクションMg 色相
	AplParamMg_R_Saturation,	//（削除候補）カラーコレクションMg_R 彩度
	AplParamMg_R_Phase,	//（削除候補）カラーコレクションMg_R 色相
	AplParamR_Saturation,	//（削除候補）カラーコレクションR 彩度
	AplParamR_Phase,	//（削除候補）カラーコレクションR 色相
	AplParamR_R_Yl_Saturation,	//（削除候補）カラーコレクションR_R_Yl 彩度
	AplParamR_R_Yl_Phase,	//（削除候補）カラーコレクションR_R_Yl 色相
	AplParamB_Mg_Mg_Saturation,	//（削除候補）カラーコレクションB_Mg_Mg 彩度
	AplParamB_Mg_Mg_Phase,	//（削除候補）カラーコレクションB_Mg_Mg 色相
	AplParamR_Yl_Yl_Saturation,	//（削除候補）カラーコレクションR_Yl_Y 彩度
	AplParamR_Yl_Yl_Phase,	//（削除候補）カラーコレクションR_Yl_Y 色相
	AplParamYl_Saturation,	//（削除候補）カラーコレクションYl 彩度
	AplParamYl_Phase,	//（削除候補）カラーコレクションYl 色相
	AplParamYl_Yl_G_Saturation,	//（削除候補）カラーコレクションYl_YI_G 彩度
	AplParamYl_Yl_G_Phase,	//（削除候補）カラーコレクションYl_YI_G 色相
	AplParamG_Saturation,	//（削除候補）カラーコレクションG 彩度
	AplParamG_Phase,	//（削除候補）カラーコレクションG 色相
	AplParamG_Cy_Saturation,	//（削除候補）カラーコレクションG_Cy 彩度
	AplParamG_Cy_Phase,	//（削除候補）カラーコレクションG_Cy 色相
	AplParamCy_Saturation,	//（削除候補）カラーコレクションCy 彩度
	AplParamCy_Phase,	//（削除候補）カラーコレクションCy 色相
	AplParamCy_Cy_B_Saturation,	//（削除候補）カラーコレクションCy_Cy_B 彩度
	AplParamCy_Cy_B_Phase,	//（削除候補）カラーコレクションCy_Cy_B 色相
	AplParamYl_G_G_Saturation,	//（削除候補）カラーコレクションYl_G_G 彩度
	AplParamYl_G_G_Phase,	//（削除候補）カラーコレクションYI_G_G 色相
	AplParamCy_B_B_Saturation,	//（削除候補）カラーコレクションCy_B_B 彩度
	AplParamCy_B_B_Phase,	//（削除候補）カラーコレクションCy_B_B 色相
	AplParamB_Saturation,	//（削除候補）カラーコレクションB 彩度
	AplParamB_Phase,	//（削除候補）カラーコレクションB 色相
	AplParamScene1SynchroScan60p4K,	//（削除候補）【シーン1保持値】シンクロスキャン(60P) 4K（未使用）
	AplParamScene1SynchroScan50p4K,	//（削除候補）【シーン1保持値】シンクロスキャン(50P) 4K（未使用）
	AplParamScene1SynchroScan30p4K,	//（削除候補）【シーン1保持値】シンクロスキャン(30P) 4K（未使用）
	AplParamScene1SynchroScan25p4K,	//（削除候補）【シーン1保持値】シンクロスキャン(25P) 4K（未使用）
	AplParamScene1SynchroScan24p4K,	//（削除候補）【シーン1保持値】シンクロスキャン(24P) 4K（未使用）
	AplParamScene1SynchroScanN24p4K,	//（削除候補）【シーン1保持値】シンクロスキャン(24P native) 4K（未使用）
	AplParamScene1SynchroScan30pSkew4K,	//（削除候補）【シーン1保持値】シンクロスキャン(30P Skew) 4K（未使用）
	AplParamScene1SynchroScan24pSkew4K,	//（削除候補）【シーン1保持値】シンクロスキャン(24P Skew) 4K（未使用）
	AplParamScene1SynchroScanN24pSkew4K,	//（削除候補）【シーン1保持値】シンクロスキャン(24P Skew native) 4K（未使用）
	AplParamScene1SynchroScan25pSkew4K,	//（削除候補）【シーン1保持値】シンクロスキャン(25P Skew) 4K（未使用）
	AplParamScene1SynchroScan60p2K,	//（削除候補）【シーン1保持値】シンクロスキャン(60P) 2K（未使用）
	AplParamScene1SynchroScan50p2K,	//（削除候補）【シーン1保持値】シンクロスキャン(50P) 2K（未使用）
	AplParamScene1SynchroScan30p2K,	//（削除候補）【シーン1保持値】シンクロスキャン(30P) 2K（未使用）
	AplParamScene1SynchroScan25p2K,	//（削除候補）【シーン1保持値】シンクロスキャン(25P) 2K（未使用）
	AplParamScene1SynchroScan24p2K,	//（削除候補）【シーン1保持値】シンクロスキャン(24P) 2K（未使用）
	AplParamSceneFileName1,	//（削除候補）シーンファイル1の名前
	AplParamSceneFileName2,	//（削除候補）シーンファイル2の名前
	AplParamSceneFileName3,	//（削除候補）シーンファイル3の名前
	AplParamSceneFileName4,	//（削除候補）シーンファイル4の名前
	AplParamSceneFileName5,	//（削除候補）シーンファイル5の名前
	AplParamSceneFileName6,	//（削除候補）シーンファイル6の名前
	AplParamRemoteRecLink,	//（削除候補）リモート記録連動
	AplParamTestToneAdjustment,	//（削除候補）テストトーン調整
	AplParamHdmiOutputResolution,	//（削除候補）HDMI出力解像度
	AplParamSdiResolution,	//（削除候補）SDI出力解像度
	AplParamSdiAudioGainChg,	//（削除候補）SDI 音声ゲイン切換
	AplParamRingLED_Blue,	//（削除候補）リングLED(青)
	AplParamRingLED_Red,	//（削除候補）リングLED(赤)
	AplParamCounterReset,	//（削除候補）カウンタリセット要求
	AplParamSpotMeterVal,	//（削除候補）輝度表示値(未使用　削除予定)
	AplParamSceneCustom,	//（削除候補）カスタムシーン
	AplParamSceneSelectModeFlag,	//（削除候補）【画面外遷移時判定用フラグ】シーン選択画面
	AplParamDispZoomFocus,	//（削除候補）ズーム/フォーカス
	AplParamDispZoom,	//（削除候補）ZOOM/Focus表示設定 Zoom側
	AplParamDispFocus,	//（削除候補）ZOOM/Focus表示設定 Focus側
	AplParamDns,	//DNS
	AplParamPortNum,	//HTTPd ポート番号
	AplParamCameraTitle,	//カメラタイトル
	AplParamFriendlyName,	//フレンドリ名
	AplParamLastUser,	//リモート 最終使用ユーザー
	AplParamUserAuth,	//リモート ユーザ認証
	AplParamUserAuthNum,	//リモート ユーザ認証数
	AplParamUserAuthData1,	//リモート ユーザ認証情報 １
	AplParamUstVideoQuality,	//Ustream 回線品質
	AplParamUstVideoQuality2,	//Ustream 回線品質2
	AplParamCopyRetryTime,	//DIGAコピー リトライ時間(秒)
	AplParamDetectionArea,	//見守り 検知エリア
	AplParamCareerSenseOn,	//キャリアセンスON閾値
	AplParamCareerSenseOff,	//キャリアセンスOFF閾値
	AplParamDigaCopy,	//WifiMenu DIGAコピー有効判定用
	AplParamWiFiOnOff,	//Wi-Fi 有効無効
	AplParamDns_2nd,	//DNS 2nd
	AplParamDhcp_3rd,	//DHCP 3rd
	AplParamIpAddress_3rd,	//IP アドレス 3rd
	AplParamSubnet_3rd,	//サブネットマスク 3rd
	AplParamGateway_3rd,	//デフォルトゲートウェイ 3rd
	AplParamDns_3rd,	//DNS 3rd
	AplParamDnsPrimary_3rd,	//DNS (プライマリ) 3rd
	AplParamDnsSecondary_3rd,	//DNS (セカンダリ) 3rd
	AplParamHttpServer,	//HTTPサーバ設定
	AplParamHttpServerAccount,	//HTTPサーバアカウント設定
	AplParamUserAuthData2,	//リモート ユーザ認証情報 ２
	AplParamUserAuthData3,	//リモート ユーザ認証情報 ３
	AplParamUserAuthData4,	//リモート ユーザ認証情報 ４
	AplParamUserAuthData5,	//リモート ユーザ認証情報 ５
	AplParamUserAuthData6,	//リモート ユーザ認証情報 ６
	AplParamUserAuthData7,	//リモート ユーザ認証情報 ７
	AplParamUserAuthData8,	//リモート ユーザ認証情報 ８
	AplParamUserAuthData9,	//リモート ユーザ認証情報 ９
	AplParamApPriority1,	//AP接続優先順位１ (AP一覧で表示するもの)
	AplParamApPriority2,	//AP接続優先順位２ (AP一覧で表示するもの)
	AplParamApPriority3,	//AP接続優先順位３ (AP一覧で表示するもの)
	AplParamApLastSelected,	//最後にAP接続しにいったもの(APL_NET_PARAM_AP_PRIORITY)
	AplParamDeviceName,	//DLNA デバイス名 (DIGA、ぼうけんくん相手も？)
	AplParamPcBkupPcName,	//PCバックアップ PC名
	AplParamPcBkupIpAddress,	//PCバックアップ IPアドレス
	AplParamPcBkupWorkgroupName,	//PCバックアップ ワークグループ名
	AplParamPcBkupFolderName,	//PCバックアップ 共有フォルダ名
	AplParamPcBkupUserName,	//PCバックアップ ユーザ名
	AplParamPcBkupPassword,	//PCバックアップ パスワード
	AplParamHistory1,	//接続履歴 履歴１がさすインデックス番号
	AplParamHistory2,	//接続履歴 履歴２がさすインデックス番号
	AplParamHistory3,	//接続履歴 履歴３がさすインデックス番号
	AplParamHistory4,	//接続履歴 履歴４がさすインデックス番号
	AplParamHistory5,	//接続履歴 履歴５がさすインデックス番号
	AplParamHistory6,	//接続履歴 履歴６がさすインデックス番号
	AplParamHistory7,	//接続履歴 履歴７がさすインデックス番号
	AplParamHistory8,	//接続履歴 履歴８がさすインデックス番号
	AplParamHistory9,	//接続履歴 履歴９がさすインデックス番号
	AplParamHistory10,	//接続履歴 履歴１０がさすインデックス番号
	AplParamHistory11,	//接続履歴 履歴１１がさすインデックス番号
	AplParamHistory12,	//接続履歴 履歴１２がさすインデックス番号
	AplParamHistory13,	//接続履歴 履歴１３がさすインデックス番号
	AplParamHistory14,	//接続履歴 履歴１４がさすインデックス番号
	AplParamHistory15,	//接続履歴 履歴１５がさすインデックス番号
	AplParamHistory16,	//接続履歴 履歴１６がさすインデックス番号
	AplParamHistory17,	//接続履歴 履歴１７がさすインデックス番号
	AplParamHistory18,	//接続履歴 履歴１８がさすインデックス番号
	AplParamHistory19,	//接続履歴 履歴１９がさすインデックス番号
	AplParamHistory20,	//接続履歴 履歴２０がさすインデックス番号
	AplParamHistoryLast,	//最後につなげた接続履歴（０始まり:０は未使用）
	AplParamHttpAccountIndex1,	//HTTPサーバアカウント情報1が指すインデックス番号
	AplParamHttpAccountIndex2,	//HTTPサーバアカウント情報2が指すインデックス番号
	AplParamHttpAccountIndex3,	//HTTPサーバアカウント情報3が指すインデックス番号
	AplParamHttpAccountIndex4,	//HTTPサーバアカウント情報4が指すインデックス番号
	AplParamHttpAccountIndex5,	//HTTPサーバアカウント情報5が指すインデックス番号
	AplParamHttpAccountIndex6,	//HTTPサーバアカウント情報6が指すインデックス番号
	AplParamHttpAccountIndex7,	//HTTPサーバアカウント情報7が指すインデックス番号
	AplParamHttpAccountIndex8,	//HTTPサーバアカウント情報8が指すインデックス番号
	AplParamHttpAccountIndex9,	//HTTPサーバアカウント情報9が指すインデックス番号
	AplParamHttpAccountIndex10,	//HTTPサーバアカウント情報10が指すインデックス番号
	AplParamHttpAccountData1,	//HTTPサーバアカウント情報インデックス1
	AplParamHttpAccountData2,	//HTTPサーバアカウント情報インデックス2
	AplParamHttpAccountData3,	//HTTPサーバアカウント情報インデックス3
	AplParamHttpAccountData4,	//HTTPサーバアカウント情報インデックス4
	AplParamHttpAccountData5,	//HTTPサーバアカウント情報インデックス5
	AplParamHttpAccountData6,	//HTTPサーバアカウント情報インデックス6
	AplParamHttpAccountData7,	//HTTPサーバアカウント情報インデックス7
	AplParamHttpAccountData8,	//HTTPサーバアカウント情報インデックス8
	AplParamHttpAccountData9,	//HTTPサーバアカウント情報インデックス9
	AplParamHttpAccountData10,	//HTTPサーバアカウント情報インデックス10
	AplParamReconnectTimer,	//接続失敗時の再接続タイマー(ミリ秒) 0の時は何もしない
	AplParamNetParamVer,	//NetParamのバージョン
	AplParamCRTKeyUsageState,	//CRT鍵の使用状態
	AplParamCRTKey0Size,	//CRT鍵0のサイズ
	AplParamCRTKey0GenerateState,	//CRT鍵0の生成状態
	AplParamCRTKey1Size,	//CRT鍵1のサイズ
	AplParamCRTKey1GenerateState,	//CRT鍵1の生成状態
	AplParamSelfSignedCertSize,	//自己証明書サイズ
	AplParamSelfSignedCertGenerateState,	//自己証明書生成状態
	AplParamCACertSize,	//サーバー証明書サイズ
	AplParamCACertGenerateState,	//サーバー証明書生成状態
	AplParamIpAddressV6Input,	//WLAN IPアドレス(IPv6) 入力文字列
	AplParamGatewayV6Input,	//WLAN デフォルトゲートウェイ(IPv6) 入力文字列
	AplParamDnsPrimaryV6Input,	//WLAN DNS (プライマリ)(IPv6) 入力文字列
	AplParamDnsSecondaryV6Input,	//WLAN DNS (セカンダリ)(IPv6) 入力文字列
	AplParamLanIpAddressV6Input,	//LAN IP ADDRESS(IPv6) 入力文字列
	AplParamLanGatewayV6Input,	//LAN デフォルトゲートウェイ(IPv6) 入力文字列
	AplParamLanDnsPrimaryV6Input,	//LAN DNS (プライマリ)(IPv6) 入力文字列
	AplParamLanDnsSecondaryV6Input,	//LAN DNS (セカンダリ)(IPv6) 入力文字列
	AplParamFtpServerAddress,	//FTPサーバーアドレス(ディレクトリ名込み)
	AplParamFtpUserName,	//FTPユーザー名
	AplParamFtpPassword,	//FTPパスワード
	AplParamNtpServerAddress,	//NTPサーバーアドレス
	AplParamPriorityStreamAddr1,	//優先ストリームIPアドレス１
	AplParamPriorityStreamAddr2,	//優先ストリームIPアドレス２
	AplParamCSRSize,	//署名リクエストサイズ
	AplParamCSRGenerateState,	//署名リクエスト生成状態
	AplParamLastUser2,	//リモート 最終使用ユーザー 判定用
	AplParamAuthType,	//認証方式
	AplParamEasyIpLimit,	//IP簡単設定起動時間制限
	AplParamLiveviewJpegFPS,	//JPEGフレームレート
	AplParamLimitationControlTiltUp,	//パンチルタリミット Tilt Up
	AplParamLimitationControlTiltDown,	//パンチルタリミット Tilt Down
	AplParamLimitationControlPanLeft,	//パンチルタリミット Pan Left
	AplParamLimitationControlPanRight,	//パンチルタリミット Pan Right
	AplParamLiveviewImageResolution,	//画像解像度
	AplParamHttpdConnectionType,	//接続方法設定
	AplParamHttpsPortNum,	//HTTPSポート番号
	AplParamIpV6,	//IPv6
	AplParamMaxRtpPacketSize,	//RTP最大パケットサイズ
	AplParamHttpMaxSegmentSize,	//HTTP最大セグメントサイズ
	AplParamBandwidthCtrl,	//ネットワーク配信量制御
	AplParamFtpCtrlPortNum,	//FTP制御ポート番号
	AplParamFtpMode,	//FTPモード
	AplParamUseNtp,	//NTP使用
	AplParamNtpServerAddrSetting,	//NTPサーバーアドレス設定
	AplParamNtpServerPortNum,	//NTPサーバーポート番号
	AplParamNtpAdjustInterval,	//NTP時刻取得間隔
	AplParamUpnpAutoPortForwarding,	//UPnPポートフォワーディング
	AplParamPriorityMode,	//優先モード
	AplParamDateTimeDisplay,	//日時表示
	AplParamSummerTime,	//サマータイム
	AplParamSummerTimeStartDate,	//サマータイム開始時間
	AplParamSummerTimeEndDate,	//サマータイム終了時間
	AplParamAutomaticInstallationSoft,	//ソフトウェア自動インストール
	AplParamSmootherLiveVideo,	//映像のバッファリング
	AplParamRecLinkageTally,	//REC連動タリー
	AplParamInitialDisplayStreamIp,	//初期表示ストリーム(優先モードIP)
	AplParamInitialDisplayStreamIp60p,	//初期表示ストリーム(優先モードIP_60P)
	AplParamInitialDisplayStreamIpHdr,	//初期表示ストリーム(優先モードIP_HDR)
	AplParamInitialDisplayStreamSd,	//初期表示ストリーム(優先モードSDカード)
	AplParamInitialDisplayStreamSdHdr,	//初期表示ストリーム(優先モードSDカード_HDR)
	AplParamInitialDisplayStreamUsb,	//初期表示ストリーム(優先モードUSB)
	AplParamInitialDisplayStreamIp4k,	//初期表示ストリーム(優先モードIP 4K)
	AplParamInitialDisplayStreamSd4k,	//初期表示ストリーム(優先モードSDカード 4K)
	AplParamInitialDisplayStreamUsb4k,	//初期表示ストリーム(優先モードUSB 4K)
	AplParamInitialDisplayStreamHdmi4k,	//初期表示ストリーム(優先モードHDMI 4K)
	AplParamJpegImageInfo1_Ip,	//JPEG画像情報１(優先モードIP)
	AplParamJpegImageInfo2_Ip,	//JPEG画像情報２(優先モードIP)
	AplParamJpegImageInfo3_Ip,	//JPEG画像情報３(優先モードIP)
	AplParamJpegImageInfo1_Ip60p,	//JPEG画像情報１(優先モードIP_60P)
	AplParamJpegImageInfo2_Ip60p,	//JPEG画像情報２(優先モードIP_60P)
	AplParamJpegImageInfo3_Ip60p,	//JPEG画像情報３(優先モードIP_60P)
	AplParamJpegImageInfo1_IpHdr,	//JPEG画像情報１(優先モードIP_HDR)
	AplParamJpegImageInfo2_IpHdr,	//JPEG画像情報２(優先モードIP_HDR)
	AplParamJpegImageInfo3_IpHdr,	//JPEG画像情報３(優先モードIP_HDR)
	AplParamJpegImageInfo1_Sd,	//JPEG画像情報１(優先モードSDカード)
	AplParamJpegImageInfo2_Sd,	//JPEG画像情報２(優先モードSDカード)
	AplParamJpegImageInfo3_Sd,	//JPEG画像情報３(優先モードSDカード)
	AplParamJpegImageInfo1_SdHdr,	//JPEG画像情報１(優先モードSDカード_HDR)
	AplParamJpegImageInfo2_SdHdr,	//JPEG画像情報２(優先モードSDカード_HDR)
	AplParamJpegImageInfo3_SdHdr,	//JPEG画像情報３(優先モードSDカード_HDR)
	AplParamJpegImageInfo1_Usb,	//JPEG画像情報１(優先モードUSB)
	AplParamJpegImageInfo1_Ip4k,	//JPEG画像情報１(優先モードIP 4K)
	AplParamJpegImageInfo2_Ip4k,	//JPEG画像情報２(優先モードIP 4K)
	AplParamJpegImageInfo3_Ip4k,	//JPEG画像情報３(優先モードIP 4K)
	AplParamJpegImageInfo1_Sd4k,	//JPEG画像情報１(優先モードSDカード 4K)
	AplParamJpegImageInfo2_Sd4k,	//JPEG画像情報２(優先モードSDカード 4K)
	AplParamJpegImageInfo3_Sd4k,	//JPEG画像情報３(優先モードSDカード 4K)
	AplParamJpegImageInfo1_Usb4k,	//JPEG画像情報１(優先モードUSB 4K)
	AplParamJpegImageInfo2_Usb4k,	//JPEG画像情報２(優先モードUSB 4K)
	AplParamJpegImageInfo1_Hdmi4k,	//JPEG画像情報１(優先モードHDMI 4K)
	AplParamJpegImageInfo2_Hdmi4k,	//JPEG画像情報２(優先モードHDMI 4K)
	AplParamJpegImageInfo3_Hdmi4k,	//JPEG画像情報３(優先モードHDMI 4K)
	AplParamH264SendInfo1,	//H.264送信情報１
	AplParamH264SendInfo2,	//H.264送信情報２
	AplParamH264SendInfo3,	//H.264送信情報３
	AplParamH264SendInfo4,	//H.264送信情報４
	AplParamH264ImageInfo1_Ip,	//H.264画像情報１(優先モードIP)
	AplParamH264ImageInfo2_Ip,	//H.264画像情報２(優先モードIP)
	AplParamH264ImageInfo3_Ip,	//H.264画像情報３(優先モードIP)
	AplParamH264ImageInfo4_Ip,	//H.264画像情報４(優先モードIP)
	AplParamH264ImageInfo1_Ip60p,	//H.264画像情報１(優先モードIP_60P)
	AplParamH264ImageInfo2_Ip60p,	//H.264画像情報２(優先モードIP_60P)
	AplParamH264ImageInfo3_Ip60p,	//H.264画像情報３(優先モードIP_60P)
	AplParamH264ImageInfo1_IpHdr,	//H.264画像情報１(優先モードIP_HDR)
	AplParamH264ImageInfo1_Ip4k,	//H.264画像情報１(優先モードIP 4K)
	AplParamAudioBitrate,	//音声ビットレート
	AplParamHostAuth,	//ホスト認証
	AplParamPriorityStream,	//優先ストリーム
	AplParamPriorityStreamType,	//優先ストリームタイプ
	AplParamSdRecFormat_Sd,	//SDカード記録フォーマット(優先モードSD)
	AplParamSdRecFormat_SdHdr,	//SDカード記録フォーマット(優先モードSD_HDR)
	AplParamSdRecFormat_Sd4k,	//SDカード記録フォーマット(優先モードSD_4K)
	AplParamTimezone,	//タイムゾーン(エリア)
	AplParamAudioTransmission,	//Audio Transmission
	AplParamNetE2pVersion,	//EEPROMバージョン
	AplParamPrevPriorityMode,	//前回の優先モード
	AplParamRtspPortNum,	//RTSPポート番号
	AplParamOverlayCamTitle,	//カラーバーのカメラタイトル重畳
	AplParamH264ImageInfo1_Sd,	//H.264画像情報１(優先モードSD)
	AplParamH264ImageInfo1_SdFhd,	//H.264画像情報１(優先モードSD_FHD)
	AplParamJpegImageInfo1_Sd24p,	//JPEG画像情報１(優先モードSDカード_24P)
	AplParamJpegImageInfo1_SdFhd,	//JPEG画像情報１(優先モードSDカード_FHD)
	AplParamPrevPriorityModeSd,	//前回の優先モード(優先モードSD用)
	AplParamInitialDisplayStreamSdFhd,	//初期表示ストリーム(優先モードSD_FHDカード)
	AplParamInitialDisplayStreamSd24p,	//初期表示ストリーム(優先モードSD_24Pカード)
	AplParamH264ImageInfo1_Ip_Camhead,	//H.264画像情報１(優先モードIP)(カメラヘッド)
	AplParamH264ImageInfo1_Ip4k_Camhead,	//H.264画像情報１(優先モードIP 4K)(カメラヘッド)
	AplParamH264ImageInfo1_Sd_Camhead,	//H.264画像情報１(優先モードSD)(カメラヘッド)
	AplParamH264ImageInfo1_SdFhd_Camhead,	//H.264画像情報１(優先モードSD_FHD)(カメラヘッド)
	AplParamInitialDisplayStreamNdiHx,	//初期表示ストリーム(優先モードNDI_HX)
	AplParamH264ImageInfo1_NdiHx,	//H.264画像情報１(優先モードNDI_HX)
	AplParamH264ImageInfo2_NdiHx,	//H.264画像情報２(優先モードNDI_HX)
	AplParamJpegImageInfo1_NdiHx,	//JPEG画像情報１(優先モードNDI_HX)
	AplParamNdiHxLicenseKey,	//NDI-HXライセンスキー
	AplParamAudioVol,	//AudioVolume(K519用)
	AplParamSelectedClipNum,	//削除、コピー確認画面-選択クリップ数
	AplParamSimulErrSd1,	//ModeCheck(Status画面）表示用フラグ
	AplParamSimulErrSd2,	//ModeCheck(Status画面）表示用フラグ
	AplParamBlinkSd1,	//カード残量が2分以下の時の点滅用フラグ（タリー、OSD）
	AplParamBlinkSd2,	//カード残量が2分以下の時の点滅用フラグ（タリー、OSD）
	AplParamStreamingStatus,	//ストリーミング状態
	AplParamBondingDeviceStatus,	//ボンディング機器状態 文字列
	AplParamBondingConnectStatus,	//ボンディング機器状態 電波強度
	AplParamBondingBatteryRemain,	//ボンディング機器状態 バッテリー残量
	AplParamBondingError,	//ボンディング機器状態 エラー状態
	AplParamIpRemoteStatus,	//IPリモート状態
	AplParamTotalRemain,	//Slot1,2の総残量
	AplParamTotalCapacity,	//Slot1,2の総容量
	AplParamNetworkTally,	//ネットワーク経由でのTally要求
	AplParamBackGrErrSd1,	//ModeCheck(Status画面）表示用フラグ
	AplParamBackGrErrSd2,	//ModeCheck(Status画面）表示用フラグ
	AplParamBackUpTc,	//PowerOnRec時のTCバックアップ
	AplParamPowerOnRecStart,	//PowrOnRec開始フラグ
	AplParamNdFilterWarning,	//NdFilterWarning表示用
	AplParamIaZoomActFlag,	//iAズーム動作中フラグ表示用
	AplParamAutoIrisDispMode,	//オートアイリスモード設定表示用
	AplParamAreaMode,	//UserSwのArea
	AplParamAutoManualSwState,	//オートマニュアルSwの表示用
	AplParamSlot1CardStatus,	//SLOT1のカードアイコンのStatus表示用
	AplParamSlot1RecStatus,	//SLOT1の記録状態の表示用（赤丸点灯、赤丸点滅、P、なし）
	AplParamSlot2CardStatus,	//SLOT2のカードアイコンのStatus表示用
	AplParamSlot2RecStatus,	//SLOT2の記録状態の表示用（赤丸点灯、赤丸点滅、P、なし）
	AplParamShutterSpeedSec,	//シャッタースピード（時間）
	AplParamShutterSpeedSec60,	//シャッタースピード（時間）60
	AplParamShutterSpeedSec30,	//シャッタースピード（時間）30
	AplParamShutterSpeedSec24,	//シャッタースピード（時間）24
	AplParamShutterSpeedSec50,	//シャッタースピード（時間）50
	AplParamShutterSpeedSec25,	//シャッタースピード（時間）25
	AplParamSynchroScanSec,	//シンクロスキャン（時間）
	AplParamSynchroScanDeg,	//シンクロスキャン（角度）
	AplParamSuperGainExe,	//実施するスーパーゲイン
	AplParamFocusOSD_Num,	//Focus OSD表示用　値
	AplParamFocusOSD_MM,	//Focus OSD表示用　mm
	AplParamGainValue,	//Gain　値
	AplParamWhiteBalanceModeOSD,	//White Balance Mode　OSD表示用
	AplParamMmlModeSyncro,	//MmlのModeがSyncroになったことを通知する用
	AplParamUpButtonInvalid,	//上ボタンの排他用
	AplParamDownButtonInvalid,	//下ボタンの排他用
	AplParamReverseFocusDisplay,	//Focus表示反転情報
	AplParamBackUpCounter,	//PowerOnRec時のカウンター値バックアップ
	AplParamInfoPowerOnTimes,	//電源ON回数
	AplParamInfoServoZoom,	//ズームモーターカウント
	AplParamInfoGripZoom,	//グリップズームカウント
	AplParamInfoHandleZoom,	//ハンドルズームカウント
	AplParamInfoLcdOperation,	//LCDバックライト点灯時間 
	AplParamInfoEvfOperation,	//EVF点灯時間
	AplParamZoomCtrlValue,	//Zoom制御値
	AplParamFocusCtrlValue,	//Focus制御値
	AplParamIrisCtrlValue,	//Iris制御値
	AplParamUpdateEnd,	//UpdateEnd通知時に更新通知飛ばす
	AplParamStreamingInternalStatus,	//配信処理の動作状態(内部のステータス)
	AplParamNetworkFunc,	//NETWORK FUNC
	AplParamAutoIrisLevelEffectAdjust,	//A.IRIS LEVEL EFFECT調整値(OSD表示用)
	AplParamPlayPhotoShot,	//静止画切り出しステータス
	AplParamDZoomCtrlValue,	//DigitalZoom制御値
	AplParamForceAF,	//強制AF動作中判定
	AplParamRequestMountUpdateSd1,	//SD1のマウントアップデート要求
	AplParamRequestMountUpdateSd2,	//SD2のマウントアップデート要求
	AplParamMmFuncFrameRateInvalidFlag,	//MM機能のFrameRate有効判定用
	AplParamAutoIrisLevelEffectAdjustmentAmount,	//A.IRIS LEVEL EFFECT調整値(リング補正量)
	AplParamSynchroScanAddMode,	//シンクロスキャン動作中
	AplParamPlayP2Icon,	//表示：P2用サムネイル画面アイコン
	AplParamPlayP2StartIcon,	//表示：P2不良クリップ用サムネイル画面アイコン
	AplParamIdMax
} AplParamEepromId;
#endif /* _APL_PARAM_H_ */

#define APL_PARAM_DATA_SIZE_MAX	10172

