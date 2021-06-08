/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version: 7.5.1
 *  Element:          AplParamMainValueCheck
 */


#include "AplParamMainValueCheck.h"
#include "AplParamService.h"
//## package Foundation::Manager

//## class AplParamMainValueCheck
AplParamMainValueCheck::AplParamMainValueCheck() {
    //#[ operation AplParamMainValueCheck()
    //#]
}

AplParamMainValueCheck::~AplParamMainValueCheck() {
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::valueCheck(int id, int value) {
    //#[ operation valueCheck(int,int)
    AplParamItemState rtn = AplParamItemState_VisibleValid;
    
    switch( id )
    {
    	case AplParamPlayBackMenu:				rtn = checkAplParamPlayBackMenu(value);				break;
    	case AplParamClipMenu:					rtn = checkAplParamClipMenu(value);					break;
    	case AplParamThumbDisplayMenu:			rtn = checkAplParamThumbDisplayMenu(value);			break;
    	case AplParamAudioChSettingsMenu:		rtn = checkAplParamAudioChSettingsMenu(value);		break;
    	case AplParamSdiOutMenu:				rtn = checkAplParamSdiOutMenu(value);				break;
    	case AplParamHdmiOutMenu:				rtn = checkAplParamHdmiOutMenu(value);				break;
    	case AplParamRecordingMenu:				rtn = checkAplParamRecordingMenu(value);			break;
    	case AplParamRecFunctionMenu:			rtn = checkAplParamRecFunctionMenu(value);			break;
    	case AplParamTCUBMenu:					rtn = checkAplParamTCUBMenu(value);					break;
    	case AplParamSystemMenu:				rtn = checkAplParamSystemMenu(value);				break;
    	case AplParamPlaySlot:					rtn = checkAplParamPlaySlot(value);					break;
    	case AplParamRecFunctionMode:			rtn = checkAplParamRecFunctionMode(value);			break;
    	case AplParamRecFormat59Hz:				rtn = checkAplParamRecFormat59Hz(value);			break;
    	case AplParamRecFormat50Hz:				rtn = checkAplParamRecFormat50Hz(value);			break;
    	case AplParamSuperGain:					rtn = checkAplParamSuperGain(value);				break;
    	case AplParamOisMode:					rtn = checkAplParamOisMode(value);					break;
    	case AplParamAgcMax:					rtn = checkAplParamAgcMax(value);					break;
    	case AplParamAutoShutterLimit:			rtn = checkAplParamAutoShutterLimit(value);			break;
    	case AplParamSceneMatrix:				rtn = checkAplParamSceneMatrix(value);				break;
    	case AplParamSdiOutFormat:				rtn = checkAplParamSdiOutFormat(value);				break;
    	case AplParamHdmiOutFormat:				rtn = checkAplParamHdmiOutFormat(value);			break;
    	case AplParamLcdMarkerFrameMarker:		rtn = checkAplParamLcdMarkerFrameMarker(value);		break;
    	case AplParamLcdFocusExpandMonocrome:	rtn = checkAplParamLcdFocusExpandMonocrome(value);	break;
    	case AplParamRelayBackup:				rtn = checkAplParamRelayBackup(value);				break;
    	case AplParamColorbarType:				rtn = checkAplParamColorbarType(value);				break;
    	case AplParamLanguage:					rtn = checkAplParamLanguage(value);					break;
    	case AplParamUserButton1:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton2:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton3:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton4:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton5:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton6:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton7:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton8:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton9:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton10:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton11:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton12:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamUserButton13:				rtn = checkAplParamUserButton(value);				break;
    	case AplParamFocusAssist:				rtn = checkAplParamFocusAssist(value);				break;
    	case AplParamFileMenu:					rtn = checkAplParamFileMenu(value);					break;
    	default:																					break;
    }
    
    return rtn;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamPlayBackMenu(int value) {
    //#[ operation checkAplParamPlayBackMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_PLAYBACK_MENU_CLIP_SEL:			return AplParamItemState_VisibleValid;	// CLIP SEL
    	case APL_SYS_PARAM_PLAYBACK_MENU_RESUME_PLAY:		return AplParamItemState_VisibleValid;	// RESUME PLAY
    	case APL_SYS_PARAM_PLAYBACK_MENU_SEEK_POS_SEL:		return inVisibleVerNoneK518();			// SEEK POS SEL
    	default:											break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamClipMenu(int value) {
    //#[ operation checkAplParamClipMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_CLIP_MENU_PROTECT:		return AplParamItemState_VisibleValid;	// PROTECT
    	case APL_SYS_PARAM_CLIP_MENU_DELETE:		return AplParamItemState_VisibleValid;	// DELETE
    	case APL_SYS_PARAM_CLIP_MENU_COPY:			return AplParamItemState_VisibleValid;	// COPY
    	case APL_SYS_PARAM_CLIP_MENU_REPAIR:		return inVisibleVerNoneK518();			// REPAIR
    	case APL_SYS_PARAM_CLIP_MENU_RE_CONNECT:	return inVisibleVerNoneK518();			// RE-CONNECT
    	case APL_SYS_PARAM_CLIP_MENU_INFORMATION:	return AplParamItemState_VisibleValid;	// INFORMATION
    	default:									break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamThumbDisplayMenu(int value) {
    //#[ operation checkAplParamThumbDisplayMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_THUMB_DISPLAY_MENU_INDICATOR:	return inVisibleVerNoneK518();			// INDICATOR
    	case APL_SYS_PARAM_THUMB_DISPLAY_MENU_TEXT_MEMO_IND:return inVisibleVerNoneK518();			// TEXT MEMO IND.
    	case APL_SYS_PARAM_THUMB_DISPLAY_MENU_DATA:			return AplParamItemState_VisibleValid;	// DATA
    	default:											break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamAudioChSettingsMenu(int value) {
    //#[ operation checkAplParamAudioChSettingsMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_LEVEL:			return AplParamItemState_VisibleValid;	// CH1 LEVEL
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2_LEVEL:			return AplParamItemState_VisibleValid;	// CH2 LEVEL
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3_LEVEL:			return inVisibleVerNone();				// CH3 LEVEL
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4_LEVEL:			return inVisibleVerNone();				// CH4 LEVEL
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3_LEVEL_CONTROL:	return inVisibleVerNone();				// CH3 LEVEL CONTROL
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4_LEVEL_CONTROL:	return inVisibleVerNone();				// CH4 LEVEL CONTROL
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_MIC_LOWCUT:		return AplParamItemState_VisibleValid;	// CH1 MIC LOWCUT
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2_MIC_LOWCUT:		return AplParamItemState_VisibleValid;	// CH2 MIC LOWCUT
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3_MIC_LOWCUT:		return inVisibleVerNone();				// CH3 MIC LOWCUT
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4_MIC_LOWCUT:		return inVisibleVerNone();				// CH4 MIC LOWCUT
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_LIMITER:			return AplParamItemState_VisibleValid;	// CH1 LIMITER
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2LIMITER:			return AplParamItemState_VisibleValid;	// CH2 LIMITER
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3LIMITER:			return inVisibleVerNone();				// CH3 LIMITER
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4LIMITER:			return inVisibleVerNone();				// CH4 LIMITER
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_HEAD_ROOM:			return AplParamItemState_VisibleValid;	// HEAD ROOM
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_IN_SELECT:		return AplParamItemState_Invisible;		//
    	case APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2_IN_SELECT:		return AplParamItemState_Invisible;		//
    	default:														break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamSdiOutMenu(int value) {
    //#[ operation checkAplParamSdiOutMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_SDI_OUT_MENU_OUTPUT_SW:		return AplParamItemState_VisibleValid;	// OUTPUT SW
    	case APL_SYS_PARAM_SDI_OUT_MENU_OUT_FORMAT:		return AplParamItemState_VisibleValid;	// OUT FORMAT
    	case APL_SYS_PARAM_SDI_OUT_MENU_3G6GSDI_OUT:	return AplParamItemState_VisibleValid;	// 3G?SDI OUT
    	case APL_SYS_PARAM_SDI_OUT_MENU_SDI_REC_REMOTE:	return AplParamItemState_VisibleValid;	// SDI REC REMOTE
    	case APL_SYS_PARAM_SDI_OUT_MENU_SD_SDI_EDH:		return AplParamItemState_VisibleValid;	// SD-SDI EDH
    	case APL_SYS_PARAM_SDI_OUT_MENU_SDI_OUT_CHAR:	return AplParamItemState_VisibleValid;	// SDI OUT CHAR
    	case APL_SYS_PARAM_SDI_OUT_MENU_SDI_OUT_ZEBRA:	return AplParamItemState_VisibleValid;	// SDI OUT ZEBRA
    	case APL_SYS_PARAM_SDI_OUT_MENU_HDR:			return AplParamItemState_VisibleValid;	// SDI OUT HDR
    	case APL_SYS_PARAM_SDI_OUT_MENU_INDICATOR_DISP:	return AplParamItemState_Invisible;		//
    	case APL_SYS_PARAM_SDI_OUT_MENU_MARKER_DISP:	return AplParamItemState_Invisible;		//
    	case APL_SYS_PARAM_SDI_OUT_MENU_MENU_DISP:		return AplParamItemState_Invisible;		//
    	case APL_SYS_PARAM_SDI_OUT_MENU_SIGNAL_SEL:		return AplParamItemState_Invisible;		//
    
    	default:											break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamHdmiOutMenu(int value) {
    //#[ operation checkAplParamHdmiOutMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_HDMI_OUT_MENU_OUT_FORMAT:		return AplParamItemState_VisibleValid;	// OUT FORMAT
    	case APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_TC_OUT:		return AplParamItemState_VisibleValid;	// HDMI TC OUT
    	case APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_REC_REMOTE:	return AplParamItemState_VisibleValid;	// HDMI REC REMOTE
    	case APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_OUT_CHAR:		return AplParamItemState_VisibleValid;	// HDMI OUT CHAR
    	case APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_OUT_ZEBRA:	return AplParamItemState_VisibleValid;	// HDMI OUT ZEBRA
    	case APL_SYS_PARAM_HDMI_OUT_MENU_HDR:				return AplParamItemState_VisibleValid;	// HDR
    	case APL_SYS_PARAM_HDMI_OUT_MENU_INDICATOR_DISP:	return AplParamItemState_Invisible;		// 
    	case APL_SYS_PARAM_HDMI_OUT_MENU_MARKER_DISP:		return AplParamItemState_Invisible;		// 
    	case APL_SYS_PARAM_HDMI_OUT_MENU_MENU_DISP:			return AplParamItemState_Invisible;		//
    	case APL_SYS_PARAM_HDMI_OUT_MENU_SIGNAL_SEL:		return AplParamItemState_Invisible;		//
    	default:											break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamRecordingMenu(int value) {
    //#[ operation checkAplParamRecordingMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_RECORDING_MENU_FORMAT:			return AplParamItemState_VisibleValid;	// FORMAT MEDIA
    	case APL_SYS_PARAM_RECORDING_MENU_CLIP_NAME:		return AplParamItemState_VisibleValid;	// CLIP NAME
    	case APL_SYS_PARAM_RECORDING_MENU_FILE_SPLIT:		return inVisibleVerNoneK518();			// FILE SPLIT
    	case APL_SYS_PARAM_RECORDING_MENU_2SLOT_FUNC:		return AplParamItemState_VisibleValid;	// 2 SLOTS FUNC.
    	case APL_SYS_PARAM_RECORDING_MENU_PRE_REC:			return AplParamItemState_VisibleValid;	// PRE REC
    	case APL_SYS_PARAM_RECORDING_MENU_REC_FUNC:			return AplParamItemState_VisibleValid;	// REC FUNCTION
    	case APL_SYS_PARAM_RECORDING_MENU_TC_UB:			return AplParamItemState_VisibleValid;	// TC/UB
    	case APL_SYS_PARAM_RECORDING_MENU_REC_COUNTER:		return AplParamItemState_VisibleValid;	// REC COUNTER
    	case APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP:		return AplParamItemState_VisibleValid;	// TIME STAMP
    	case APL_SYS_PARAM_RECORDING_MENU_REC_MEDIA_DATA:	return inVisibleVerNoneK518();			// REC META DATA
    	default:											break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamRecFunctionMenu(int value) {
    //#[ operation checkAplParamRecFunctionMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_REC_FUNCTION_MENU_REC_MODE:		return AplParamItemState_VisibleValid;	// REC MODE
    	case APL_SYS_PARAM_REC_FUNCTION_MENU_REC_MODE_HOLD:	return AplParamItemState_VisibleValid;	// REC MODE HOLD
    	case APL_SYS_PARAM_REC_FUNCTION_MENU_INTERVAL_TIME:	return AplParamItemState_VisibleValid;	// INTERVAL TIME
    	case APL_SYS_PARAM_REC_FUNCTION_MENU_ONE_SHOT_TIME:	return inVisibleVerNone();				// ONE SHOT TIME
    	case APL_SYS_PARAM_REC_FUNCTION_MENU_START_DELAY:	return inVisibleVerNone();				// START DELAY
    	default:											break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamTCUBMenu(int value) {
    //#[ operation checkAplParamTCUBMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_TCUB_MENU_SET_TC:				return AplParamItemState_VisibleValid;	// TC PRESET
    	case APL_SYS_PARAM_TCUB_MENU_SET_UB:				return AplParamItemState_VisibleValid;	// UB PRESET
    	case APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN:			return AplParamItemState_VisibleValid;	// FREE/REC RUN
    	case APL_SYS_PARAM_TCUB_MENU_DF_NDF:				return AplParamItemState_VisibleValid;	// DF/NDF
    	case APL_SYS_PARAM_TCUB_MENU_UB_MODE:				return AplParamItemState_VisibleValid;	// UB MODE
    	case APL_SYS_PARAM_TCUB_MENU_TC_IN_OUT_SEL:			return inVisibleK518();					// TC IN/OUT SEL
    	case APL_SYS_PARAM_TCUB_MENU_TC_OUT_REF:			return inVisibleK518();					// TC OUT REF
    	default:											break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamSystemMenu(int value) {
    //#[ operation checkAplParamSystemMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_SYSTEM_MENU_FREQ:					return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_FILE_FORMAT_59Hz:		return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_FILE_FORMAT_50Hz:		return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_59Hz:		return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_50Hz:		return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_59Hz:		return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_50Hz:		return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_59Hz:	return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_50Hz:	return AplParamItemState_VisibleValid;	// FREQUENCY
    	case APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE:			return inVisibleVerNoneK518();			// PROXY REC MODE
    	case APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_FORMAT:		return inVisibleVerNoneK518();			// PROXY REC FORMAT
    	case APL_SYS_PARAM_SYSTEM_MENU_ASPECT:					return AplParamItemState_VisibleValid;	// ASPECT
    	case APL_SYS_PARAM_SYSTEM_MENU_SHOOTING_MODE:			return AplParamItemState_VisibleValid;	// SHOOTING MODE
    	case APL_SYS_PARAM_SYSTEM_MENU_FILE_FORMAT:				return AplParamItemState_Invisible;		// FILE FORMAT
    	case APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT:				return AplParamItemState_Invisible;		// REC FORMAT
    	default:												break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamPlaySlot(int value) {
    //#[ operation checkAplParamPlaySlot(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_PLAY_SLOT_ALL:			return AplParamItemState_VisibleValid;	// ALL SLOT
    	case APL_SYS_PARAM_PLAY_SLOT_SLOT1:			return AplParamItemState_VisibleValid;	// SLOT1
    	case APL_SYS_PARAM_PLAY_SLOT_SLOT2:			return AplParamItemState_VisibleValid;	// SLOT2
    	case APL_SYS_PARAM_PLAY_SLOT_SAME_FORMAT:	return AplParamItemState_VisibleValid;	// SAME FORMAT
    	case APL_SYS_PARAM_PLAY_SLOT_MARKED:		return inVisibleVerNoneK518();			// MARKED
    	case APL_SYS_PARAM_PLAY_SLOT_TEXT_MEMO:		return inVisibleVerNoneK518();			// TEXT MEMO
    	default:									break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamRecFunctionMode(int value) {
    //#[ operation checkAplParamRecFunctionMode(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:	return AplParamItemState_VisibleValid;	// NORMAL
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:	return AplParamItemState_VisibleValid;	// INTERVAL
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:	return inVisibleVerNone();				// ONE SHOT
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:		return inVisibleVerNone();				// LOOP
    	default:										break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamRecFormat59Hz(int value) {
    //#[ operation checkAplParamRecFormat59Hz(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_P2:			return inVisibleVerNoneK518();			// P2
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_MOV:			return AplParamItemState_VisibleValid;	// MOV
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_AVCHD:		return AplParamItemState_VisibleValid;	// AVCHD
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_MP4:			return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_MP4_LPCM:	return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_MOV_LPCM:	return AplParamItemState_Invisible;
    	default:										break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamRecFormat50Hz(int value) {
    //#[ operation checkAplParamRecFormat50Hz(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_P2:			return inVisibleVerNoneK518();			// P2
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_MOV:			return AplParamItemState_VisibleValid;	// MOV
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_AVCHD:		return AplParamItemState_VisibleValid;	// AVCHD
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_MP4:			return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_MP4_LPCM:	return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_MOV_LPCM:	return AplParamItemState_Invisible;
    	default:										break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamSuperGain(int value) {
    //#[ operation checkAplParamSuperGain(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_SUPER_GAIN_24DB:			return AplParamItemState_VisibleValid;	// 24dB
    	case APL_SYS_PARAM_SUPER_GAIN_27DB:			return AplParamItemState_Invisible;		// 27dB
    	case APL_SYS_PARAM_SUPER_GAIN_30DB:			return AplParamItemState_VisibleValid;	// 30dB
    	case APL_SYS_PARAM_SUPER_GAIN_33DB:			return AplParamItemState_Invisible;		// 33dB
    	case APL_SYS_PARAM_SUPER_GAIN_36DB:			return AplParamItemState_VisibleValid;	// 36dB
    	default:									break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamOisMode(int value) {
    //#[ operation checkAplParamOisMode(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_OIS_MODE_OFF:			return AplParamItemState_VisibleValid;	// OFF
    	case APL_SYS_PARAM_OIS_MODE_ACTIVE:			return AplParamItemState_VisibleValid;	// ACTIVE
    	case APL_SYS_PARAM_OIS_MODE_STANDARD:		return AplParamItemState_Invisible;
    	default:									break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamAgcMax(int value) {
    //#[ operation checkAplParamAgcMax(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_AGC_MAX_0dB:			return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_3dB:			return AplParamItemState_VisibleValid;	// 3dB
    	case APL_SYS_PARAM_AGC_MAX_6dB:			return AplParamItemState_VisibleValid;	// 6dB
    	case APL_SYS_PARAM_AGC_MAX_9dB:			return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_12dB:		return AplParamItemState_VisibleValid;	// 12dB
    	case APL_SYS_PARAM_AGC_MAX_15dB:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_18dB:		return AplParamItemState_VisibleValid;	// 18dB
    	case APL_SYS_PARAM_AGC_MAX_21dB:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_24dB:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_27dB:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_30dB:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_33dB:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_36dB:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_39dB:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AGC_MAX_42dB:		return AplParamItemState_Invisible;
    	default:									break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamAutoShutterLimit(int value) {
    //#[ operation checkAplParamAutoShutterLimit(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_AUTO_SHUTTER_LIMIT_1_250:	return AplParamItemState_VisibleValid;	// 1/250
    	case APL_SYS_PARAM_AUTO_SHUTTER_LIMIT_1_125:	return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_AUTO_SHUTTER_LIMIT_1_120:	return AplParamItemState_VisibleValid;	// 1/120
    	case APL_SYS_PARAM_AUTO_SHUTTER_LIMIT_1_100:	return AplParamItemState_VisibleValid;	// 1/100
    	case APL_SYS_PARAM_AUTO_SHUTTER_LIMIT_OFF:		return AplParamItemState_Invisible;
    	default:										break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamSceneMatrix(int value) {
    //#[ operation checkAplParamSceneMatrix(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_MATRIX_NORM_1:	return AplParamItemState_VisibleValid;	// NORM1
    	case APL_SYS_PARAM_MATRIX_NORM_2:	return AplParamItemState_VisibleValid;	// NORM2
    	case APL_SYS_PARAM_MATRIX_FLUO:		return AplParamItemState_VisibleValid;	// FLUO
    	case APL_SYS_PARAM_MATRIX_CINELIKE:	return AplParamItemState_VisibleValid;	// CINELIKE
    	case APL_SYS_PARAM_MATRIX_STILL:	return AplParamItemState_Invisible;
    	default:							break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamSdiOutFormat(int value) {
    //#[ operation checkAplParamSdiOutFormat(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_SDI_FORMAT_4096_2160P:	return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_SDI_FORMAT_3840_2160P:	return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_SDI_FORMAT_1920_1080P:	return AplParamItemState_VisibleValid;	// 1920x1080p
    	case APL_SYS_PARAM_SDI_FORMAT_1920_1080I:	return AplParamItemState_VisibleValid;	// 1920x1080i
    	case APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF:	return AplParamItemState_VisibleValid;	// 1920x1080PsF
    	case APL_SYS_PARAM_SDI_FORMAT_1280_720P:	return AplParamItemState_VisibleValid;	// 1280x720p
    	case APL_SYS_PARAM_SDI_FORMAT_720_480I:		return AplParamItemState_VisibleValid;	// 720x480i
    	case APL_SYS_PARAM_SDI_FORMAT_720_576I:		return AplParamItemState_VisibleValid;	// 720x576i
    	default:							break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamHdmiOutFormat(int value) {
    //#[ operation checkAplParamHdmiOutFormat(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_HDMI_FORMAT_4096_2160P:			return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit:	return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_HDMI_FORMAT_3840_2160P:			return AplParamItemState_VisibleValid;	// 3840x2160p
    	case APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit:	return AplParamItemState_VisibleValid;	// 3840x2160p(420/8bit),
    	case APL_SYS_PARAM_HDMI_FORMAT_1920_1080P:			return AplParamItemState_VisibleValid;	// 1920x1080p
    	case APL_SYS_PARAM_HDMI_FORMAT_1920_1080I:			return AplParamItemState_VisibleValid;	// 1920x1080i
    	case APL_SYS_PARAM_HDMI_FORMAT_1280_720P:			return AplParamItemState_VisibleValid;	// 1280x720p
    	case APL_SYS_PARAM_HDMI_FORMAT_720_480P:			return AplParamItemState_VisibleValid;	// 720x480p
    	case APL_SYS_PARAM_HDMI_FORMAT_720_576P:			return AplParamItemState_VisibleValid;	// 720x576p
    	default:											break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamLcdMarkerFrameMarker(int value) {
    //#[ operation checkAplParamLcdMarkerFrameMarker(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_FRAMEMARKER_OFF:				return AplParamItemState_VisibleValid;	// OFF
    	case APL_SYS_PARAM_FRAMEMARKER_133_1:			return AplParamItemState_VisibleValid;	// 4:3
    	case APL_SYS_PARAM_FRAMEMARKER_144_1:			return AplParamItemState_VisibleValid;	// 13:9
    	case APL_SYS_PARAM_FRAMEMARKER_156_1:			return AplParamItemState_VisibleValid;	// 14:9
    	case APL_SYS_PARAM_FRAMEMARKER_178_1:			return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_FRAMEMARKER_185_1:			return AplParamItemState_VisibleValid;	// 1.85:1
    	case APL_SYS_PARAM_FRAMEMARKER_200_1:			return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_FRAMEMARKER_2201_1:			return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_FRAMEMARKER_235_1:			return AplParamItemState_VisibleValid;	// 2.35:1
    	case APL_SYS_PARAM_FRAMEMARKER_239_1:			return AplParamItemState_Invisible;
    	default:										break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamLcdFocusExpandMonocrome(int value) {
    //#[ operation checkAplParamLcdFocusExpandMonocrome(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_FOCUS_EXPAND_MONO_ON:				return AplParamItemState_VisibleValid;	// ON
    	case APL_SYS_PARAM_FOCUS_EXPAND_MONO_OFF:				return AplParamItemState_VisibleValid;	// OFF
    	case APL_SYS_PARAM_FOCUS_EXPAND_MONO_DURING_PEAKING:	return AplParamItemState_VisibleValid;	// DURING PEAKING
    	case APL_SYS_PARAM_FOCUS_EXPAND_MONO_DURING_PEAK_SQ:	return AplParamItemState_Invisible;
    	default:												break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamRelayBackup(int value) {
    //#[ operation checkAplParamRelayBackup(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_RELAY_BACKUP_OFF:		return AplParamItemState_VisibleValid;	// OFF
    	case APL_SYS_PARAM_RELAY_BACKUP_RELAY:		return AplParamItemState_VisibleValid;	// RELAY REC
    	case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:		return AplParamItemState_VisibleValid;	// BACKGR REC
    	case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:		return AplParamItemState_VisibleValid;	// SIMUL REC
    	case APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC:	return AplParamItemState_Invisible;
    	default:									break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamColorbarType(int value) {
    //#[ operation checkAplParamColorbarType(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_COLORBAR_TYPE1:		return AplParamItemState_VisibleValid;	// SMPTE
    	case APL_SYS_PARAM_COLORBAR_TYPE2:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_COLORBAR_TYPE3:		return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_COLORBAR_TYPEFULL:	return AplParamItemState_VisibleValid;	// FULL
    	default:								break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamLanguage(int value) {
    //#[ operation checkAplParamLanguage(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
	return AplParamItemState_VisibleValid;
    switch ( value )
    {
    	case APL_SYS_PARAM_LANGUAGE_JAPANESE:						break;
    	case APL_SYS_PARAM_LANGUAGE_ENGLISH:						break;
    	case APL_SYS_PARAM_LANGUAGE_GERMAN:							break;
    	case APL_SYS_PARAM_LANGUAGE_FRENCH:							break;
    	case APL_SYS_PARAM_LANGUAGE_ITALIA:							break;
    	case APL_SYS_PARAM_LANGUAGE_SPAIN:							break;
    	case APL_SYS_PARAM_LANGUAGE_DUTCH:							break;
    	case APL_SYS_PARAM_LANGUAGE_SWEDEN:							break;
    	case APL_SYS_PARAM_LANGUAGE_POLAND:							break;
    	case APL_SYS_PARAM_LANGUAGE_RUSSIA:							break;
    	case APL_SYS_PARAM_LANGUAGE_SCHINESE:						break;
    	case APL_SYS_PARAM_LANGUAGE_CZECH:							break;
    	case APL_SYS_PARAM_LANGUAGE_TURKISH:						break;
    	case APL_SYS_PARAM_LANGUAGE_HUNGARIAN:						break;
    	case APL_SYS_PARAM_LANGUAGE_ENGLISH_PAL:					return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_FRENCH_PAL:						return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_SPAIN_PAL:						return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_ARABIA:							return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_PERSIA:							return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_KOREA:							return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_TCHINESE_PAL:					return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_TCHINESE:						return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_THAI:							return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_HINDI:							return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_ENGLISH_JA:						return AplParamItemState_Invisible;
    	case APL_SYS_PARAM_LANGUAGE_PORTUGUESE:						return AplParamItemState_Invisible;
    	default:													return AplParamItemState_Invisible;
    }
    
//	if (AplIfSys::ModelInfo_GetModel() == SYS_K518)
	if (false)
		{
    	switch ( value )
    	{
    		case APL_SYS_PARAM_LANGUAGE_JAPANESE:					return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_ENGLISH:					return AplParamItemState_VisibleValid;	// ﾊﾆ
    		case APL_SYS_PARAM_LANGUAGE_GERMAN:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_FRENCH:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_ITALIA:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_SPAIN:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_DUTCH:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_SWEDEN:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_POLAND:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_RUSSIA:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_SCHINESE:					return AplParamItemState_VisibleValid;	// ﾃ・ｴﾊ｡ﾋ
    		case APL_SYS_PARAM_LANGUAGE_CZECH:						return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_TURKISH:					return AplParamItemState_Invisible;
    		case APL_SYS_PARAM_LANGUAGE_HUNGARIAN:					return AplParamItemState_Invisible;
    		default:												return AplParamItemState_Invisible;
    	}
    }
    else
    {
    	char model[AplParamInfoModel_Size] = {0};
    	APL_PARAM_GET_DATA_AREA(AplParamInfoModel,(UB*)model,AplParamInfoModel_Size);
    	if( strncmp(model,"AJ-UPX200E",AplParamInfoModel_Size) == 0 )
    	{
    		switch ( value )
    		{
    			case APL_SYS_PARAM_LANGUAGE_JAPANESE:				return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_ENGLISH:				return AplParamItemState_VisibleValid;	// ﾊﾆ
    			case APL_SYS_PARAM_LANGUAGE_GERMAN:					return AplParamItemState_VisibleValid;	// ﾆﾈ
    			case APL_SYS_PARAM_LANGUAGE_FRENCH:					return AplParamItemState_VisibleValid;	// ﾊｩ
    			case APL_SYS_PARAM_LANGUAGE_ITALIA:					return AplParamItemState_VisibleValid;	// ｰﾋ
    			case APL_SYS_PARAM_LANGUAGE_SPAIN:					return AplParamItemState_VisibleValid;	// ﾀｾ
    			case APL_SYS_PARAM_LANGUAGE_DUTCH:					return AplParamItemState_VisibleValid;	// ﾍ・    			case APL_SYS_PARAM_LANGUAGE_SWEDEN:					return AplParamItemState_VisibleValid;	// ･ｹ･ｦ･ｧ｡ｼ･ﾇ･・    			case APL_SYS_PARAM_LANGUAGE_POLAND:					return AplParamItemState_VisibleValid;	// ･ﾝ｡ｼ･鬣ﾉ
    			case APL_SYS_PARAM_LANGUAGE_RUSSIA:					return AplParamItemState_VisibleValid;	// ﾏｪ
    			case APL_SYS_PARAM_LANGUAGE_SCHINESE:				return AplParamItemState_Invisible;	
    			case APL_SYS_PARAM_LANGUAGE_CZECH:					return AplParamItemState_VisibleValid;	// ･ﾁ･ｧ･ｳ
    			case APL_SYS_PARAM_LANGUAGE_TURKISH:				return AplParamItemState_VisibleValid;	// ･ﾈ･・ｳ
    			case APL_SYS_PARAM_LANGUAGE_HUNGARIAN:				return AplParamItemState_VisibleValid;	// ･ﾏ･ｬ･遙ｼ
    			default:											return AplParamItemState_Invisible;
    		}
    	}
    	else if ( strncmp(model,"AJ-UPX200MC",AplParamInfoModel_Size) == 0 )
    	{
    		switch ( value )
    		{
    			case APL_SYS_PARAM_LANGUAGE_JAPANESE:				return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_ENGLISH:				return AplParamItemState_VisibleValid;	// ﾊﾆ
    			case APL_SYS_PARAM_LANGUAGE_GERMAN:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_FRENCH:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_ITALIA:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_SPAIN:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_DUTCH:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_SWEDEN:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_POLAND:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_RUSSIA:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_SCHINESE:				return AplParamItemState_VisibleValid;	// ﾃ・ｴﾊ｡ﾋ
    			case APL_SYS_PARAM_LANGUAGE_CZECH:					return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_TURKISH:				return AplParamItemState_Invisible;
    			case APL_SYS_PARAM_LANGUAGE_HUNGARIAN:				return AplParamItemState_Invisible;
    			default:											return AplParamItemState_Invisible;
    		}
    	}
    	else
    	{
    		switch( APL_PARAM_GET_DATA( AplParamUSeAreaSettings ) )
    		{
    			case APL_SYS_PARAM_USE_AREA_1:
    				switch ( value )
    				{
    					case APL_SYS_PARAM_LANGUAGE_JAPANESE:		return AplParamItemState_VisibleValid;	// ﾆ・    					case APL_SYS_PARAM_LANGUAGE_ENGLISH:		return AplParamItemState_VisibleValid;	// ﾊﾆ
    					case APL_SYS_PARAM_LANGUAGE_GERMAN:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_FRENCH:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_ITALIA:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SPAIN:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_DUTCH:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SWEDEN:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_POLAND:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_RUSSIA:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SCHINESE:		return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_CZECH:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_TURKISH:		return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_HUNGARIAN:		return AplParamItemState_Invisible;
    					default:									return AplParamItemState_Invisible;
    				}
    				break;
    			case APL_SYS_PARAM_USE_AREA_2:
    			default:
    				switch ( value )
    				{
    					case APL_SYS_PARAM_LANGUAGE_JAPANESE:		return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_ENGLISH:		return AplParamItemState_VisibleValid;	// ﾊﾆ
    					case APL_SYS_PARAM_LANGUAGE_GERMAN:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_FRENCH:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_ITALIA:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SPAIN:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_DUTCH:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SWEDEN:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_POLAND:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_RUSSIA:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SCHINESE:		return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_CZECH:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_TURKISH:		return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_HUNGARIAN:		return AplParamItemState_Invisible;
    					default:									return AplParamItemState_Invisible;
    				}
    				break;
    			case APL_SYS_PARAM_USE_AREA_3:
    			case APL_SYS_PARAM_USE_AREA_4:
    				switch ( value )
    				{
    					case APL_SYS_PARAM_LANGUAGE_JAPANESE:		return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_ENGLISH:		return AplParamItemState_VisibleValid;	// ﾊﾆ
    					case APL_SYS_PARAM_LANGUAGE_GERMAN:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_FRENCH:			return AplParamItemState_VisibleValid;	// ﾊｩ
    					case APL_SYS_PARAM_LANGUAGE_ITALIA:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SPAIN:			return AplParamItemState_VisibleValid;	// ﾀｾ
    					case APL_SYS_PARAM_LANGUAGE_DUTCH:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SWEDEN:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_POLAND:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_RUSSIA:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_SCHINESE:		return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_CZECH:			return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_TURKISH:		return AplParamItemState_Invisible;
    					case APL_SYS_PARAM_LANGUAGE_HUNGARIAN:		return AplParamItemState_Invisible;
    					default:									return AplParamItemState_Invisible;
    				}
    				break;
    		}
    	}		
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamUserButton(int value) {
    //#[ operation checkAplParamUserButton(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_USER_BUTTON_INH:
    	case APL_SYS_PARAM_USER_BUTTON_AWB:
    	case APL_SYS_PARAM_USER_BUTTON_DRS:
    	case APL_SYS_PARAM_USER_BUTTON_FLASH_BAND:
    	case APL_SYS_PARAM_USER_BUTTON_PUSH_AF:
    	case APL_SYS_PARAM_USER_BUTTON_S_GAIN:
    	case APL_SYS_PARAM_USER_BUTTON_AREA:
    	case APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE:
    	case APL_SYS_PARAM_USER_BUTTON_ATW:
    	case APL_SYS_PARAM_USER_BUTTON_ATW_LOCK:
    	case APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT:
    	case APL_SYS_PARAM_USER_BUTTON_BACKLIGHT:
    	case APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL:
    	case APL_SYS_PARAM_USER_BUTTON_IRIS:
    	case APL_SYS_PARAM_USER_BUTTON_SPOT_METER:
    	case APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO:
    	case APL_SYS_PARAM_USER_BUTTON_OIS_MODE:
    	case APL_SYS_PARAM_USER_BUTTON_IA_ZOOM:
    	case APL_SYS_PARAM_USER_BUTTON_D_ZOOM:
    	case APL_SYS_PARAM_USER_BUTTON_IR_MODE:
    	case APL_SYS_PARAM_USER_BUTTON_FZOOM:
    	case APL_SYS_PARAM_USER_BUTTON_PREREC:
    	case APL_SYS_PARAM_USER_BUTTON_VFR:
    	case APL_SYS_PARAM_USER_BUTTON_SUPERSLOW:
    	case APL_SYS_PARAM_USER_BUTTON_REC_CHECK:
    	case APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE:
    	case APL_SYS_PARAM_USER_BUTTON_LAST_CLIP:
    	case APL_SYS_PARAM_USER_BUTTON_SLOT_SEL:
    	case APL_SYS_PARAM_USER_BUTTON_FA:
    	case APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA:
    	case APL_SYS_PARAM_USER_BUTTON_WFM:
    	case APL_SYS_PARAM_USER_BUTTON_ZEBRA:
    	case APL_SYS_PARAM_USER_BUTTON_LEVEL:
    	case APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET:
    	case APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR:
    	case APL_SYS_PARAM_USER_BUTTON_EVF:
    	case APL_SYS_PARAM_USER_BUTTON_EVF_DTL:
    	case APL_SYS_PARAM_USER_BUTTON_MENU:
    	case APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE:
    	case APL_SYS_PARAM_USER_BUTTON_POWER_LCD:
    	case APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE:
    	case APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC:
    	case APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID:
    	case APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START:
    	case APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET:
    		return AplParamItemState_VisibleValid;
    	
    	case APL_SYS_PARAM_USER_BUTTON_REC_MEDIA:
    	case APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO:
    	case APL_SYS_PARAM_USER_BUTTON_SHOT_MARK:
    	case APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL:
    	case APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL:
    	case APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST:
    		return inVisibleVerNone();	// K517 or VUP
    	
    	default:
    		return AplParamItemState_Invisible;
    }
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamFocusAssist(int value) {
    //#[ operation checkAplParamFocusAssist(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_FOCUS_ASSIST_EXPAND:		return AplParamItemState_VisibleValid;
    	case APL_SYS_PARAM_FOCUS_ASSIST_PEAKING:	return AplParamItemState_VisibleValid;
    	case APL_SYS_PARAM_FOCUS_ASSIST_BOTH:		return AplParamItemState_Invisible;
    	default:									break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::checkAplParamFileMenu(int value) {
    //#[ operation checkAplParamFileMenu(int)
    // ﾀﾟﾄ・猯ﾜ､ｬｵ｡ｼ・r･ﾐ｡ｼ･ｸ･逾ﾇﾍｭｸ妤ｫﾌｵｸ妤ｫ､ｽﾄ熙ｹ､・    // ﾍｭｸ・AplParamItemState_VisibleValid
    // ﾌｵｸ・AplParamItemState_Invisible
    switch ( value )
    {
    	case APL_SYS_PARAM_FILE_MENU_LOAD_SAVE_SLOT:	return inVisibleVerNone();
    	case APL_SYS_PARAM_FILE_MENU_SCENE_FILE:		return AplParamItemState_VisibleValid;
    	case APL_SYS_PARAM_FILE_MENU_SETUP_FILE:		return AplParamItemState_VisibleValid;
    	case APL_SYS_PARAM_FILE_MENU_SETUP_FILE_MEM:	return AplParamItemState_VisibleValid;
    	default:										break;
    }
    
    return AplParamItemState_Invisible;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::inVisibleVerNoneK518() {
    //#[ operation inVisibleVerNoneK518()
    // K518
	//    if ( AplIfSys::ModelInfo_GetModel() == SYS_K518 )
	if ( false )
	{
    	return AplParamItemState_Invisible;
    }
    
    return inVisibleVerNone();
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::inVisibleVerNone() {
    //#[ operation inVisibleVerNone()
    // [SERVICE MENU]-[21]
    // ON､ﾇ､｢､・ﾐVUPｸ螟ﾎ･皈ﾋ･蝪ｼ､簣ｭｸ・    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	return AplParamItemState_VisibleValid;
    }
    
    // ｽ魎ﾐｲﾙ､ﾇ､ﾏﾉｽｼｨ､ｵ､ｻ､ﾊ､､
    if ( APL_PARAM_GET_DATA( AplParamVup ) == APL_SYS_PARAM_VUP_NONE )
    {
    	return AplParamItemState_Invisible;
    }
    
    return AplParamItemState_VisibleValid;
    //#]
}

AplParamMainValueCheck::AplParamItemState AplParamMainValueCheck::inVisibleK518() {
    //#[ operation inVisibleK518()
    // K518
	//    if ( AplIfSys::ModelInfo_GetModel() == SYS_K518 )
	if (false)
	{
    	return AplParamItemState_Invisible;
    }
    
    return AplParamItemState_VisibleValid;
    //#]
}
