/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version: 7.5.1
 *  Element:          AplParamMainItemTypeFuncK519
 */


#include "AplParamMainItemTypeFuncK519.h"
#include "AplParamMainValueCheck.h"
#include "AplParamService.h"
//## package Foundation::Manager

//## class AplParamMainItemTypeFuncK519
AplParamMainItemTypeFuncK519::AplParamMainItemTypeFuncK519(AplParamService::AplParamMainItem* item, AplParamMainValueCheck& ValueCheck) : AplParamMainItemTypeFunc(item) {
    m_pValueCheck = NULL;
    //#[ operation AplParamMainItemTypeFuncK519(AplParamMainItem,AplParamMainValueCheck)
    m_pValueCheck = &ValueCheck;
    //#]
}

AplParamMainItemTypeFuncK519::~AplParamMainItemTypeFuncK519() {
}

AplParamState AplParamMainItemTypeFuncK519::AplParamTopMenu_ViewType(int id) {
    //#[ operation AplParamTopMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_TOP_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_THUMBNAIL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_CAMERA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_AUDIO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_VIDEO_OUT_LCD_VF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_RECORDING
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_NETWORK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_SYSTEM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_OTHERS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_OPTION
    	AplParamState_Invisible,	// APL_SYS_PARAM_TOP_MENU_SYSTEM_SETTINGS
    	AplParamState_Invisible,	// APL_SYS_PARAM_TOP_MENU_CAMERA_SETTINGS
    	AplParamState_Invisible,	// APL_SYS_PARAM_TOP_MENU_SCENE_FILE_SETTINGS
    	AplParamState_Invisible,	// APL_SYS_PARAM_TOP_MENU_REC_SETTINGS
    	AplParamState_Invisible,	// APL_SYS_PARAM_TOP_MENU_AUDIO_SETTINGS
    	AplParamState_Invisible,	// APL_SYS_PARAM_TOP_MENU_OUTPUT_SETTINGS
    	AplParamState_Invisible,	// APL_SYS_PARAM_TOP_MENU_FILE
    	AplParamState_Invisible,	// APL_SYS_PARAM_TOP_MENU_NETWORK_SETTINGS
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamPlayMode,
    	AplParamOptionMenuDisp,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamTopMenu].mState;
    // ---------------------------------------------------------
    
    // AplParamPlayMode
    switch( APL_PARAM_GET_DATA( AplParamPlayMode ) ){
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_TOP_MENU_CAMERA]		= AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_TOP_MENU_SCENE_FILE]	= AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_TOP_MENU_THUMBNAIL]		= AplParamState_Invisible;
    		break;
    	default:
    		break;
    }
    
    //モデル名判定
    char model[AplParamInfoModel_Size] = {0};
    APL_PARAM_GET_DATA_AREA(AplParamInfoModel,(UB*)model,AplParamInfoModel_Size);
    if( strncmp(model,"AG-CX350",AplParamInfoModel_Size) == 0 && APL_PARAM_GET_DATA( AplParamOptionMenuDisp ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_TOP_MENU_THUMBNAIL]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_CAMERA]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_SCENE_FILE]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_AUDIO]				= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_VIDEO_OUT_LCD_VF]	= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_RECORDING]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_NETWORK]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_SYSTEM]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_OTHERS]			= AplParamState_Invisible;
    }
    else
    {
    	Exclusion[APL_SYS_PARAM_TOP_MENU_OPTION]			= AplParamState_Invisible;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_TOP_MENU_MAX + 1 ; i++ ){
    	m_Item[AplParamTopMenu].sub_item[i].state =  Exclusion[i];
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamPlayBackMenu_ViewType(int id) {
    //#[ operation AplParamPlayBackMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_PLAYBACK_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAYBACK_MENU_CLIP_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAYBACK_MENU_RESUME_PLAY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAYBACK_MENU_SEEK_POS_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAYBACK_MENU_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAYBACK_MENU_REPEAT_PLAY
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamRecFormat,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamPlayBackMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // SEEK POS SEL ==============================
    // ②FILE FORMAT [P2]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_PLAYBACK_MENU_SEEK_POS_SEL]	= AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_PLAYBACK_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamPlayBackMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_PLAYBACK_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamPlayBackMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_PLAYBACK_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamPlaySlot_ViewType(int id) {
    //#[ operation AplParamPlaySlot_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_PLAY_SLOT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAY_SLOT_ALL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAY_SLOT_SLOT1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAY_SLOT_SLOT2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAY_SLOT_SAME_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAY_SLOT_MARKED
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PLAY_SLOT_TEXT_MEMO
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamRecFormat,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamPlaySlot].mState;
    // ---------------------------------------------------------
    
    
    // 機能で無効表示とする処理 ==================
    // ②FILE FORMAT [P2]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_PLAY_SLOT_MARKED]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_PLAY_SLOT_TEXT_MEMO]	= AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_PLAY_SLOT_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamPlaySlot, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_PLAY_SLOT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamPlaySlot].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_PLAY_SLOT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamClipMenu_ViewType(int id) {
    //#[ operation AplParamClipMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_CLIP_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_PROTECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_DELETE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_COPY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_REPAIR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_RE_CONNECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_INFORMATION
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamRecFormat,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamClipMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // PROTECT ===================================
    // ①FILE FORMAT [P2]時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) == APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_CLIP_MENU_PROTECT]		= AplParamState_VisibleInvalid;
    }
    
    // COPY ======================================
    // ①FILE FORMAT [MOV]時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) == APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY]			= AplParamState_VisibleInvalid;
    }
    
    // REPAIR ====================================
    // RE-CONNECT ================================
    // ②FILE FORMAT [P2]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_CLIP_MENU_REPAIR]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_CLIP_MENU_RE_CONNECT]	= AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_CLIP_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamClipMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_CLIP_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamClipMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_CLIP_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamThumbDisplayMenu_ViewType(int id) {
    //#[ operation AplParamThumbDisplayMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_THUMB_DISPLAY_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_THUMB_DISPLAY_MENU_INDICATOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_THUMB_DISPLAY_MENU_TEXT_MEMO_IND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_THUMB_DISPLAY_MENU_DATA
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamRecFormat,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamThumbDisplayMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // INDICATOR =================================
    // TEXT MEMO IND. ============================
    // ②FILE FORMAT [P2]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_THUMB_DISPLAY_MENU_INDICATOR]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_THUMB_DISPLAY_MENU_TEXT_MEMO_IND]	= AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_THUMB_DISPLAY_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamThumbDisplayMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_THUMB_DISPLAY_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamThumbDisplayMenu].sub_item[i].state =  Exclusion[i];
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamAudioChSettingsMenu_ViewType(int id) {
    //#[ operation AplParamAudioChSettingsMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3_LEVEL_CONTROL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4_LEVEL_CONTROL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_MIC_LOWCUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2_MIC_LOWCUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3_MIC_LOWCUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4_MIC_LOWCUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_LIMITER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2LIMITER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3LIMITER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4LIMITER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_HEAD_ROOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_IN_SELECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2_IN_SELECT
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamCh1Adjust,
    	AplParamCh2Adjust,
    	AplParamCh3Adjust,
    	AplParamCh4Adjust
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamAudioChSettingsMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // CH3 LEVEL CONTROL ===============================
    // ①CH3 LEVEL [AUTO]時無効
    if ( APL_PARAM_GET_DATA( AplParamCh3Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3_LEVEL_CONTROL] = AplParamState_VisibleInvalid;
    }
    
    // CH4 LEVEL CONTROL ===============================
    // ①CH4 LEVEL [AUTO]時無効
    if ( APL_PARAM_GET_DATA( AplParamCh4Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4_LEVEL_CONTROL] = AplParamState_VisibleInvalid;
    }
    
    // CH1 LIMITER ===============================
    // ①CH1 LEVEL [AUTO]時無効
    if ( APL_PARAM_GET_DATA( AplParamCh1Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_LIMITER] = AplParamState_VisibleInvalid;
    }
    
    // CH2 LIMITER ===============================
    // ①CH2 LEVEL [AUTO]時無効
    if ( APL_PARAM_GET_DATA( AplParamCh2Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2LIMITER] = AplParamState_VisibleInvalid;
    }
    
    // CH3 LIMITER ===============================
    // ①CH3 LEVEL [AUTO]時無効
    if ( APL_PARAM_GET_DATA( AplParamCh3Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3LIMITER] = AplParamState_VisibleInvalid;
    }
    
    // CH4 LIMITER ===============================
    // ①CH4 LEVEL [AUTO]時無効
    if ( APL_PARAM_GET_DATA( AplParamCh4Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4LIMITER] = AplParamState_VisibleInvalid;
    }
    
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamAudioChSettingsMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamAudioChSettingsMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamVideoOutLcdVfMenu_ViewType(int id) {
    //#[ operation AplParamVideoOutLcdVfMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_VIDEO_OUT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_SDI_OUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_HDMI_OUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_AV_OUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_VF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_HDR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_INDICATOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_LCD_VF_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_LCD_VF_FOCUS_ASSIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_LCD_VF_EI_ASSIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_LCD_VF_LEVEL_GAUGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_SD_DOWNCON_MODE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamOutputSelect,
    	AplParamSystemRecMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamVideoOutLcdVfMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // SDI OUT ===================================
    // ①VIDEO OUT SEL [AV + HDMI]時無効
    if ( APL_PARAM_GET_DATA( AplParamOutputSelect ) == APL_SYS_PARAM_OUTPUT_SELECT_HDMI_AV )
    {
    	Exclusion[APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_SDI_OUT]	= AplParamState_VisibleInvalid;
    }
    
    // AV OUT ====================================
    // ①VIDEO OUT SEL [SDI + HDMI]時無効
    if ( APL_PARAM_GET_DATA( AplParamOutputSelect ) == APL_SYS_PARAM_OUTPUT_SELECT_SDI_HDMI )
    {
    	Exclusion[APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_AV_OUT]	= AplParamState_VisibleInvalid;
    }
    
    // HDR ===================================
    // ①[720x480/576i] 時 無効（SDR固定）
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_HDR]	= AplParamState_VisibleInvalid;
    }
    
    // SD DOWNCON MODE ===========================
    // ①REC FORMAT [720x480/576i]時無効
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_SD_DOWNCON_MODE]	= AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamVideoOutLcdVfMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamSdiOutMenu_ViewType(int id) {
    //#[ operation AplParamSdiOutMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SDI_OUT_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_OUTPUT_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_OUT_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_3G6GSDI_OUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_SDI_REC_REMOTE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_SD_SDI_EDH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_SDI_OUT_CHAR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_SDI_OUT_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_HDR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_INDICATOR_DISP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_MARKER_DISP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_MENU_DISP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_OUT_MENU_SIGNAL_SEL
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSdiOutFormat,
    	AplParamRecFunctionMode,
    	AplParamSystemRecMode,
    	AplParamSceneGammaModeSel
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSdiOutMenu].mState;
    // ---------------------------------------------------------
#if 0
    // 機能で無効表示とする処理 ==================
    // OUT FORMAT ================================
    // AVSへ設定するプロパティ情報取得
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    // UHD(3840×2160)
    if ( VideoProperty.Width == 3840 && VideoProperty.Height == 2160 )
    {
    	switch ( VideoProperty.FrameRate )
    	{
    		case AVS_FRAME_RATE_30_P:
    		case AVS_FRAME_RATE_2398_P:
    			Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_OUT_FORMAT]	= AplParamState_VisibleInvalid;
    			break;
    		default:
    			break;
    	}
    }
    // (720×480)
    else if ( ( VideoProperty.Width == 720 && VideoProperty.Height == 480 )||
    		  ( VideoProperty.Width == 720 && VideoProperty.Height == 576 ) )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_OUT_FORMAT]	= AplParamState_VisibleInvalid;
    }
#endif
    
    // 3G-SDI OUT ================================
    // ①SDI OUT - OUT FORMAT [1920x1080p]以外時 無効
    if ( APL_PARAM_GET_DATA( AplParamSdiOutFormat ) != APL_SYS_PARAM_SDI_FORMAT_1920_1080P )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_3G6GSDI_OUT]	= AplParamState_VisibleInvalid;
    }
    // ②REC FORMAT [2160-59.94p],[2160-50.00p],[1080-59.94p],[1080-50.00p]以外時 無効
    switch ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) )
    {
    	case APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_60P_150M:
    	case APL_SYS_PARAM_RECMODE_MOV_HEVC_UHD_60P_200M:
    	case APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_60P_100M:
    	case APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_60P_200M:
    	case APL_SYS_PARAM_RECMODE_AVCHD_PS:
    	case APL_SYS_PARAM_RECMODE_P2_I100_FHD_60P:
    	case APL_SYS_PARAM_RECMODE_P2_I422_FHD_60P:
    	case APL_SYS_PARAM_RECMODE_P2_G25_FHD_60P:
    		break;
    	default:
    		Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_3G6GSDI_OUT]	= AplParamState_VisibleInvalid;
    		break;
    }
    
    // SD-SDI EDH ================================
    // ①SDI OUT - OUT FORMAT [720x480/576i]以外時 無効
    if ( APL_PARAM_GET_DATA( AplParamSdiOutFormat ) != APL_SYS_PARAM_SDI_FORMAT_720_480I &&
    	 APL_PARAM_GET_DATA( AplParamSdiOutFormat ) != APL_SYS_PARAM_SDI_FORMAT_720_576I )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_SD_SDI_EDH]	= AplParamState_VisibleInvalid;
    }
    
    // SDI REC REMOTE ============================
    // ①REC MODE [INTERVAL] / [ONE SHOT] 時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_SDI_REC_REMOTE]= AplParamState_VisibleInvalid;
    }
    
    // SDI OUT ZEBRA ============================
    // ①[GAMMA MODE SEL]=[HLG]時無効（OFF 固定）
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_SDI_OUT_ZEBRA]= AplParamState_VisibleInvalid;
    }
    
    // HDR ================================
    // ①[720x480/576i] 時 無効（SDR固定）
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_HDR] = AplParamState_VisibleInvalid;
    }
    // ②[720x480/576i] 時 無効（SDR固定）
    if ( APL_PARAM_GET_DATA( AplParamSdiOutFormat ) == APL_SYS_PARAM_SDI_FORMAT_720_480I ||
    	 APL_PARAM_GET_DATA( AplParamSdiOutFormat ) == APL_SYS_PARAM_SDI_FORMAT_720_576I )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_HDR] = AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SDI_OUT_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamSdiOutMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SDI_OUT_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSdiOutMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SDI_OUT_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamSdiOutFormat_ViewType(int id) {
    //#[ operation AplParamSdiOutFormat_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ] = {
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_SDI_FORMAT_4096_2160P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_SDI_FORMAT_3840_2160P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080I
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_SDI_FORMAT_1280_720P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_SDI_FORMAT_720_480I
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_SDI_FORMAT_720_576I
    };
    bool b480iDisp = false;
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemRecMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSdiOutFormat].mState;
    // ---------------------------------------------------------
#if 0
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    
    // UHD(3840×2160)
    if ( VideoProperty.Width == 3840 && VideoProperty.Height == 2160 )
    {
    	switch ( VideoProperty.FrameRate )
    	{
    		case AVS_FRAME_RATE_60_P:
    			Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]	= AplParamState_VisibleValid;
    			Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]	= AplParamState_VisibleValid;
    			break;
    		case AVS_FRAME_RATE_30_P:
    		case AVS_FRAME_RATE_2398_P:
    			Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]= AplParamState_VisibleValid;
    			break;
    		default:
    			break;
    	}
    }
    // FHD(1920×1080)
    else if ( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 )
    {
    	switch ( VideoProperty.FrameRate )
    	{
    		case AVS_FRAME_RATE_60_P:
    			Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]	= AplParamState_VisibleValid;
    			Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]	= AplParamState_VisibleValid;
    			b480iDisp = true;
    			break;
    		case AVS_FRAME_RATE_60_I:
    			Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]	= AplParamState_VisibleValid;
    			b480iDisp = true;
    			break;
    		case AVS_FRAME_RATE_30_P:
    		case AVS_FRAME_RATE_2398_P:
    			Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]= AplParamState_VisibleValid;
    			b480iDisp = true;
    			break;
    		default:
    			break;
    	}
    }
    // HD(1280×720)
    else if ( VideoProperty.Width == 1280 && VideoProperty.Height == 720 )
    {
    	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]	= AplParamState_VisibleValid;
    	b480iDisp = true;
    }
    else
    {
    	b480iDisp = true;
    }
    
    // NTSC/PAL
    if ( AplIfSys::ModelInfo_GetVideoSystem() == SYS_NTSC )
    {
    	if ( b480iDisp == true )
    	{
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_720_480I]= AplParamState_VisibleValid;
    	}
    	Exclusion[APL_SYS_PARAM_SDI_FORMAT_720_576I]	= AplParamState_Invisible;
    }
    else
    {
    	if ( b480iDisp == true )
    	{
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_720_576I]= AplParamState_VisibleValid;
    	}
    	Exclusion[APL_SYS_PARAM_SDI_FORMAT_720_480I]	= AplParamState_Invisible;
    }
#endif
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamSdiOutFormat, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSdiOutFormat].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamHdmiOutMenu_ViewType(int id) {
    //#[ operation AplParamHdmiOutMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_HDMI_OUT_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_OUT_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_TC_OUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_REC_REMOTE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_OUT_CHAR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_OUT_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_HDR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_INDICATOR_DISP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_MARKER_DISP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_MENU_DISP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_SIGNAL_SEL
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamRecFunctionMode,
    	AplParamHdmiTcOutput,
    	AplParamSystemRecMode,
    	AplParamHdmiOutFormat,
    	AplParamSceneGammaModeSel
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamHdmiOutMenu].mState;
    // ---------------------------------------------------------
#if 0
    // 機能で無効表示とする処理 ==================
    // OUT FORMAT ===========================
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    // FHD(1920×1080)
    if ( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 )
    {
    	switch ( VideoProperty.FrameRate )
    	{
    		case AVS_FRAME_RATE_60_P:
    			break;
    		default:
    			Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_OUT_FORMAT]	= AplParamState_VisibleInvalid;
    			break;
    	}
    }
    // HD(1280×720)
    else if ( VideoProperty.Width == 1280 && VideoProperty.Height == 720 )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_OUT_FORMAT]	= AplParamState_VisibleInvalid;
    }
    else if ( ( VideoProperty.Width == 720 && VideoProperty.Height == 480 ) ||
    		  ( VideoProperty.Width == 720 && VideoProperty.Height == 576 ) )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_OUT_FORMAT]	= AplParamState_VisibleInvalid;
    }
#endif

    // HDMI REC REMOTE ===========================
    // ①REC MODE [INTERVAL] / [ONE SHOT]時 無効
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_REC_REMOTE]= AplParamState_VisibleInvalid;
    }
    // ②HDMI TC OUT [ON]以外時 無効
    if ( APL_PARAM_GET_DATA( AplParamHdmiTcOutput ) != APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_REC_REMOTE]= AplParamState_VisibleInvalid;
    }
    
    // HDMI OUT ZEBRA ============================
    // ①[GAMMA MODE SEL]=[HLG]時無効（OFF 固定）
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_OUT_ZEBRA]= AplParamState_VisibleInvalid;
    }
    
    // HDMI OUT HDR ===========================
    // ①[720x480/576i] 時 無効（SDR固定）
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDR] = AplParamState_VisibleInvalid;
    }
    // ②[720x480/576p] 時 無効（SDR固定）
    if ( APL_PARAM_GET_DATA( AplParamHdmiOutFormat ) == APL_SYS_PARAM_HDMI_FORMAT_720_480P ||
    	 APL_PARAM_GET_DATA( AplParamHdmiOutFormat ) == APL_SYS_PARAM_HDMI_FORMAT_720_576P )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDR] = AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HDMI_OUT_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamHdmiOutMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HDMI_OUT_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamHdmiOutMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_HDMI_OUT_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamHdmiOutFormat_ViewType(int id) {
    //#[ operation AplParamHdmiOutFormat_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ] = {
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_4096_2160P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_3840_2160P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_1920_1080P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_1920_1080I
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_1280_720P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_720_480P
    	AplParamState_VisibleInvalid,	// APL_SYS_PARAM_HDMI_FORMAT_720_576P
    };
    bool b480pDisp = false;
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemRecMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamHdmiOutFormat].mState;
    // ---------------------------------------------------------
#if 0
    // AVSへ設定するプロパティ情報取得
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    
    // Bug4883
    // UHD(3840×2160)
    if ( VideoProperty.Width == 3840 && VideoProperty.Height == 2160 )
    {
    	switch ( VideoProperty.FrameRate )
    	{
    		case AVS_FRAME_RATE_60_P:
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]			= AplParamState_VisibleValid;
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]= AplParamState_VisibleValid;
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]			= AplParamState_VisibleValid;
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]			= AplParamState_VisibleValid;
    			break;
    		case AVS_FRAME_RATE_30_P:
    		case AVS_FRAME_RATE_2398_P:
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]			= AplParamState_VisibleValid;
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]			= AplParamState_VisibleValid;
    			break;
    		default:
    			break;
    	}
    }
    // FHD(1920×1080)
    else if ( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 )
    {
    	switch ( VideoProperty.FrameRate )
    	{
    		case AVS_FRAME_RATE_60_P:
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]			= AplParamState_VisibleValid;
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]			= AplParamState_VisibleValid;
    			break;
    		case AVS_FRAME_RATE_60_I:
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]			= AplParamState_VisibleValid;
    			break;
    		case AVS_FRAME_RATE_30_P:
    		case AVS_FRAME_RATE_2398_P:
    			Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]			= AplParamState_VisibleValid;
    			break;
    		default:
    			break;
    	}
    }
    // HD(1280×720)
    else if ( VideoProperty.Width == 1280 && VideoProperty.Height == 720 )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]	= AplParamState_VisibleValid;
    }
    else
    {
    	b480pDisp = true;
    }
    
    // NTSC/PAL
    if ( AplIfSys::ModelInfo_GetVideoSystem() == SYS_NTSC )
    {
    	if ( b480pDisp == true )
    	{
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]= AplParamState_VisibleValid;
    	}
    	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]	= AplParamState_Invisible;
    }
    else
    {
    	if ( b480pDisp == true )
    	{
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]= AplParamState_VisibleValid;
    	}
    	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]	= AplParamState_Invisible;
    }
#endif
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamHdmiOutFormat, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamHdmiOutFormat].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamLcdVfMarkerMenu_ViewType(int id) {
    //#[ operation AplParamLcdVfMarkerMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_LCD_VF_MARKER_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_MARKER_MENU_CENTER_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_MARKER_MENU_SAFETY_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_MARKER_MENU_SAFETY_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_MARKER_MENU_FRAME_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_MARKER_MENU_FRAME_COLOR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamLcdMarkerSaftyMarkerType,
    	AplParamLcdMarkerFrameMarker,
    	AplParamSystemRecMode,
    	AplParamAspectCombert,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamLcdVfMarkerMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // SAFETY AREA ===============================
    // ①SAFETY MARKER [OFF]時 無効
    if ( APL_PARAM_GET_DATA( AplParamLcdMarkerSaftyMarkerType ) == APL_SYS_PARAM_SAFETY_MARKER_TYPE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_MARKER_MENU_SAFETY_AREA] = AplParamState_VisibleInvalid;
    }
    
    // FRAME MARKER ==============================
    // ①REC FORMAT [480i/576i],かつ ASPECT [4:3] 時無効
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA &&
    	 APL_PARAM_GET_DATA( AplParamAspectCombert ) == APL_SYS_PARAM_ASPECT_COMBERT_SIDE_CROP )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_MARKER_MENU_FRAME_MARKER]= AplParamState_VisibleInvalid;
    }
    
    
    // FRAME COLOR ===============================
    // ①FRAME MARKER [OFF]時 無効
    if ( APL_PARAM_GET_DATA( AplParamLcdMarkerFrameMarker ) == APL_SYS_PARAM_FRAMEMARKER_OFF )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_MARKER_MENU_FRAME_COLOR] = AplParamState_VisibleInvalid;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_LCD_VF_MARKER_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLcdVfMarkerMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_LCD_VF_MARKER_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamLcdVfEiAssistMenu_ViewType(int id) {
    //#[ operation AplParamLcdVfEiAssistMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA1_DETECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2_DETECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_WFM_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_WFM_TRANS
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneGammaModeSel,
    	AplParamColorBar,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamLcdVfEiAssistMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // ZEBRA =====================================
    // ZEBRA1 DETECT =====================================
    // ZEBRA2 DETECT =====================================
    // ZEBRA2 =====================================
    // ①COLOR BAR出力中 無効
    if ( APL_PARAM_GET_DATA( AplParamColorBar ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA1_DETECT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2_DETECT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2] = AplParamState_VisibleInvalid;
    }
    
    // ②[GAMMA MODE SEL]=[HLG]時無効（OFF 固定）
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA1_DETECT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2_DETECT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2] = AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLcdVfEiAssistMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamRecordingMenu_ViewType(int id) {
    //#[ operation AplParamRecordingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_RECORDING_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_CLIP_NAME
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_FILE_SPLIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_2SLOT_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_PRE_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_REC_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_TC_UB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_REC_COUNTER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RECORDING_MENU_REC_MEDIA_DATA
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	//AplParamRecFormat,
    	AplParamSceneVFRMode,
    	AplParamProxyRecMode,
    	AplParamRecFunctionMode,
    	AplParamRelayBackup,
    	AplParamSystemRecMode,
    	AplParamNetworkFunc,
    	
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamRecordingMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    
    // CLIP NAME =================================
    // ①FILE FORMAT [MOV]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_CLIP_NAME]		= AplParamState_VisibleInvalid;
    }
    
    // FILE SPLIT ===============================
    // ②FILE FORMAT [P2]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_FILE_SPLIT]	= AplParamState_VisibleInvalid;
    }
    
    // 2 SLOTS FUNC. =============================
    // ①VFR SW [OFF]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_2SLOT_FUNC]		= AplParamState_VisibleInvalid;
    }
    // ②PROXY REC MODE [MAIN & SUB]時無効
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) == APL_SYS_PARAM_PROXY_REC_MODE_P2_SD )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_2SLOT_FUNC]		= AplParamState_VisibleInvalid;
    }
    
    // PRE REC ===================================
    // ①VFR SW [OFF]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_PRE_REC]			= AplParamState_VisibleInvalid;
    }
    // ②REC MODE [NORMAL] 以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) != APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_PRE_REC]	= AplParamState_VisibleInvalid;
    }
    // ③2 SLOTS FUNC. [BACKGR REC] 時無効
    if ( APL_PARAM_GET_DATA( AplParamRelayBackup ) == APL_SYS_PARAM_RELAY_BACKUP_BACKUP )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_PRE_REC]	= AplParamState_VisibleInvalid;
    }
    // ④NETWORK FUNC [NDI|HX] 時：無効
    if ( APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_PRE_REC]	= AplParamState_VisibleInvalid;
    }
    
    // TIME STAMP ================================
    // ①PROXY REC MODE [OFF]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) != APL_SYS_PARAM_PROXY_REC_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP]		= AplParamState_VisibleInvalid;
    }
    // ②NETWORK FUNC [STREAMING]/[NDI|HX] 時：無効
    if ( APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_STREAMING ||
    	 APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP]		= AplParamState_VisibleInvalid;
    }
    // ③VFR SW [OFF]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP]		= AplParamState_VisibleInvalid;
    }
    // ④REC FORMAT [480i/576i]時無効
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP]		= AplParamState_VisibleInvalid;
    }
    
    // REC META DATA =============================
    // ②FILE FORMAT [P2]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_REC_MEDIA_DATA]	= AplParamState_VisibleInvalid;
    }
    
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_RECORDING_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecordingMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_RECORDING_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamRecordingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_RECORDING_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamFileSplit_ViewType(int id) {
    //#[ operation AplParamFileSplit_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_FILE_SPLIT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SPLIT_ONE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SPLIT_SPLIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SPLIT_SHORT_SPLIT
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamProxyRecMode,
    	AplParamRelayBackup,
    	AplParamRecFunctionMode
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamFileSplit].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // ③PROXY REC MODE [OFF]以外時 [ONE FILE] 選択不可（ [SPLIT] に丸める）
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) != APL_SYS_PARAM_PROXY_REC_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_FILE_SPLIT_ONE_FILE]	= AplParamState_VisibleInvalid;
    }
    // ④2 SLOTS FUNC. [BACKGR REC]時 [SHORT SPLIT] 選択不可（ [SPLIT] に丸める）
    if ( APL_PARAM_GET_DATA( AplParamRelayBackup ) == APL_SYS_PARAM_RELAY_BACKUP_BACKUP )
    {
    	Exclusion[APL_SYS_PARAM_FILE_SPLIT_SHORT_SPLIT]	= AplParamState_VisibleInvalid;
    }
    // ⑤REC MODE [NORMAL]以外時 [SHORT SPLIT] 選択不可（ [SPLIT] に丸める）
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) != APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL )
    {
    	Exclusion[APL_SYS_PARAM_FILE_SPLIT_SHORT_SPLIT]	= AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FILE_SPLIT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamFileSplit].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_FILE_SPLIT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamRelayBackup_ViewType(int id) {
    //#[ operation AplParamRelayBackup_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RELAY_BACKUP_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RELAY_BACKUP_RELAY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RELAY_BACKUP_BACKUP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RELAY_BACKUP_SIMUL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamProxyRecMode,
    	AplParamRecFunctionMode,
    //	AplParamRecFormat,
    	AplParamSystemRecMode,
    	AplParamNetworkFunc,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamRelayBackup].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // ②PROXY REC MODE [OFF]以外時 [BACKGR REC] 選択不可（OFF に丸める）
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) != APL_SYS_PARAM_PROXY_REC_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
    // ③STREAMING/NDI|HX 時： [BACKGR REC] 選択不可（OFF に丸める）
    if ( APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_STREAMING ||
    	 APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
    // ④REC MODE [INTERVAL] / [ONE SHOT]時 [RELAY REC] と [BACKGR REC] 選択不可（OFF に丸める）
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
    // TODO 2018/07/19 MIZUTA
    // 仕様不明
    // ⑤REC MODE [LOOP]時 (T.B.D)
    //if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP )
    //{
    //}
    // ⑥FILE FORMAT [AVCHD]時 [BACKGR REC] 選択不可（OFF に丸める）
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) == APL_SYS_PARAM_REC_FORMAT_AVCHD )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
#if 0
    // ⑦REC FORMAT [FHD] 以外時 [BACKGR REC] 選択不可（OFF に丸める）
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    if ( !( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 ) )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
#endif
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_RELAY_BACKUP_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRelayBackup, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_RELAY_BACKUP_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamRelayBackup].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_RELAY_BACKUP_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamRecFunctionMenu_ViewType(int id) {
    //#[ operation AplParamRecFunctionMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MENU_REC_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MENU_REC_MODE_HOLD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MENU_INTERVAL_TIME
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MENU_ONE_SHOT_TIME
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MENU_START_DELAY
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneVFRMode,
    	AplParamRecFormat,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamRecFunctionMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // REC MODE ==================================
    // ②VFR SW [OFF]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_REC_FUNCTION_MENU_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // ④FILE FORMAT [AVCHD]時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) == APL_SYS_PARAM_REC_FORMAT_AVCHD )
    {
    	Exclusion[APL_SYS_PARAM_REC_FUNCTION_MENU_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FUNCTION_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecFunctionMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FUNCTION_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamRecFunctionMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_REC_FUNCTION_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamTCUBMenu_ViewType(int id) {
    //#[ operation AplParamTCUBMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_TCUB_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCUB_MENU_SET_TC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCUB_MENU_SET_UB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCUB_MENU_DF_NDF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCUB_MENU_UB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCUB_MENU_TC_IN_OUT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCUB_MENU_TC_OUT_REF
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUsersBitMode,
    	AplParamPreRec,
    	AplParamRecFunctionMode,
    	AplParamRelayBackup,
    	AplParamSceneVFRMode,
    	AplParamSystemRecMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamTCUBMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // UB PRESET =================================
    // ①UB MODE [USER]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamUsersBitMode ) != APL_SYS_PARAM_UB_MODE_USER )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_SET_UB]		= AplParamState_VisibleInvalid;
    }
    
    // FREE/REC RUN ==============================
    // ①PRE REC [OFF]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamPreRec ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN]	= AplParamState_VisibleInvalid;
    }
    // ②REC MODE [INTERVAL] / [ONE SHOT] 時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN]	= AplParamState_VisibleInvalid;
    }
    // ③2 SLOTS FUNC. [BACKGR REC] 時無効
    if ( APL_PARAM_GET_DATA( AplParamRelayBackup ) == APL_SYS_PARAM_RELAY_BACKUP_BACKUP )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN]	= AplParamState_VisibleInvalid;
    }
    // ④VFR SW [OFF]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN]	= AplParamState_VisibleInvalid;
    }
#if 0
    // DF/NDF ====================================
    // ①REC FORMAT [29.97p]/[59.94p]/[59.94i] 以外時無効
    if( AplIfSys::ModelInfo_GetVideoSystem() == SYS_PAL )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_DF_NDF]		= AplParamState_VisibleInvalid;
    }
    else
    {
    	AplIfAvs::AvsIfVideoProperty VideoProperty;
    	memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    	AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    	if ( VideoProperty.FrameRate != AVS_FRAME_RATE_30_P &&
    		 VideoProperty.FrameRate != AVS_FRAME_RATE_60_P &&
    		 VideoProperty.FrameRate != AVS_FRAME_RATE_60_I )
    	{
    		Exclusion[APL_SYS_PARAM_TCUB_MENU_DF_NDF]		= AplParamState_VisibleInvalid;
    	}
    }
#endif
    // ②REC MODE [INTERVAL] / [ONE SHOT] 時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_DF_NDF]		= AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_TCUB_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamTCUBMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_TCUB_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamTCUBMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_TCUB_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUsersBitMode_ViewType(int id) {
    //#[ operation AplParamUsersBitMode_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_UB_MODE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UB_MODE_FRAME_RATE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UB_MODE_USER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UB_MODE_TIME
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UB_MODE_DATE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UB_MODE_TC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UB_MODE_CLIP_NAME
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamRecFormat,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUsersBitMode].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // ①FILE FORMAT [MOV]以外時 [CLIP NAME]は選択不可
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_UB_MODE_CLIP_NAME]	= AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_UB_MODE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUsersBitMode].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_UB_MODE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamSystemMenu_ViewType(int id) {
    //#[ operation AplParamSystemMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SYSTEM_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_FREQ
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_FILE_FORMAT_59Hz
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_FILE_FORMAT_50Hz
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_59Hz
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_50Hz
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_59Hz
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_50Hz
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_59Hz
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_50Hz
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_ASPECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_SUPER_SLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_SHOOTING_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_FILE_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	//AplParamRecFormat,
    	AplParamSceneVFRMode,
    	AplParamRecFunctionMode,
    	AplParamFileSplit,
    	AplParamProxyRecMode,
    	AplParamSystemRecMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSystemMenu].mState;
    // ---------------------------------------------------------
#if 0
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    
    // 機能で無効表示とする処理 ==================
    // FILE FORMAT ============================
    // REC FORMAT ============================
    if ( AplIfSys::ModelInfo_GetVideoSystem() == SYS_NTSC )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_FILE_FORMAT_50Hz]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_50Hz]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_50Hz]	= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_50Hz]	= AplParamState_Invisible;
    }
    else
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_FILE_FORMAT_59Hz]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_59Hz]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_59Hz]	= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_59Hz]	= AplParamState_Invisible;
    }
#endif
    switch ( APL_PARAM_GET_DATA( AplParamRecFormat59Hz ) )
    {
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_P2:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_59Hz]	= AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_59Hz]	= AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_MOV:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_59Hz]		= AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_59Hz]	= AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_REC_FORMAT_59HZ_AVCHD:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_59Hz]		= AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_59Hz]	= AplParamState_Invisible;
    		break;
    	default:
    		break;
    }
    
    switch ( APL_PARAM_GET_DATA( AplParamRecFormat50Hz ) )
    {
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_P2:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_50Hz]	= AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_50Hz]	= AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_MOV:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_50Hz]		= AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_AVCHD_50Hz]	= AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_REC_FORMAT_50HZ_AVCHD:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_P2_50Hz]		= AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_REC_FORMAT_MOV_50Hz]	= AplParamState_Invisible;
    		break;
    	default:
    		break;
    }
    
    // PROXY REC MODE ============================
    // ③FILE FORMAT [P2]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // ④REC FORMAT [AVC-Intra200]時無効
    switch ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) )
    {
    	case APL_SYS_PARAM_RECMODE_P2_I200_FHD_60I:
    	case APL_SYS_PARAM_RECMODE_P2_I200_HD_60P:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]	= AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    // ⑤VFR SW [OFF]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // ⑥REC MODE [NORMAL]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) != APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // ⑦FILE APLIT [ONE FILE]時無効
    if ( APL_PARAM_GET_DATA( AplParamFileSplit ) == APL_SYS_PARAM_FILE_SPLIT_ONE_FILE )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // PROXY REC FORMAT ==========================
    // ③PROXY REC MODE [OFF]時無効
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) == APL_SYS_PARAM_PROXY_REC_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_FORMAT]	= AplParamState_VisibleInvalid;
    }
    // ASPECT ====================================
    // ①REC FORMAT [480i/576i]以外時無効
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) != APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_ASPECT]				= AplParamState_VisibleInvalid;
    }
    
    // SUPER SLOW ============================
    // ①FILE FORMAT [MOV] 以外時：無効
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_SUPER_SLOW]			= AplParamState_VisibleInvalid;
    }
    // ②REC FORMAT [1920×1080] 以外時：無効
#if 0
    if ( !( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 ) )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_SUPER_SLOW]			= AplParamState_VisibleInvalid;
    }
    // ②REC FORMAT [59.94i/50.00i] 時：無効
    if ( VideoProperty.FrameRate == AVS_FRAME_RATE_60_I )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_SUPER_SLOW]			= AplParamState_VisibleInvalid;
    }
#endif
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamSystemMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSystemMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SYSTEM_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamProxyRecFormat_ViewType(int id) {
    //#[ operation AplParamProxyRecFormat_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_PROXY_REC_FORMAT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PROXY_REC_FORMAT_LOW_2CH_MOV
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PROXY_REC_FORMAT_HQ_2CH_MOV
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PROXY_REC_FORMAT_SHQ_2CH_MOV
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_PROXY_REC_FORMAT_AVC_G6_2CH_MOV
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemRecMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamProxyRecFormat].mState;
    // ---------------------------------------------------------
#if 0
    // AVSへ設定するプロパティ情報取得
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    
    // ④REC FORMAT [1920×1080_59.94/50p]時[AVC-G6] のみ有効
    if ( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 && VideoProperty.FrameRate == AVS_FRAME_RATE_60_P )
    {
    	Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_LOW_2CH_MOV]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_HQ_2CH_MOV]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_SHQ_2CH_MOV]	= AplParamState_VisibleInvalid;
    }
#endif
    // ④REC FORMAT [AVC-Intra50]時[AVC-G6] 選択不可（HQ に丸める）
    switch ( APL_PARAM_GET_DATA(AplParamSystemRecMode) )
    {
    	case APL_SYS_PARAM_RECMODE_P2_I50_FHD_60I:
    	case APL_SYS_PARAM_RECMODE_P2_I50_HD_60P:
    		Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_AVC_G6_2CH_MOV]= AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
#if 0
    // ④REC FORMAT [1280×720_59.94/50p] 時[LOW]    選択不可（HQ に丸める）
    if ( VideoProperty.Width == 1280 && VideoProperty.Height == 720 && VideoProperty.FrameRate == AVS_FRAME_RATE_60_P )
    {
    	Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_LOW_2CH_MOV]	= AplParamState_VisibleInvalid;
    }
#endif
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_PROXY_REC_FORMAT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamProxyRecFormat].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_PROXY_REC_FORMAT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamLanguage_ViewType(int id) {
    //#[ operation AplParamLanguage_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_LANGUAGE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_JAPANESE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_ENGLISH_PAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_ENGLISH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_GERMAN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_FRENCH_PAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_FRENCH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_ITALIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_SPAIN_PAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_SPAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_DUTCH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_SWEDEN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_POLAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_RUSSIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_ARABIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_PERSIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_KOREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_SCHINESE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_TCHINESE_PAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_TCHINESE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_CZECH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_THAI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_HINDI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_ENGLISH_JA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_TURKISH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_HUNGARIAN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LANGUAGE_PORTUGUESE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUSeAreaSettings,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamLanguage].mState;
    // ---------------------------------------------------------
    
    for( int i = 0 ; i < APL_SYS_PARAM_LANGUAGE_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamLanguage, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_LANGUAGE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLanguage].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_LANGUAGE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamRecFormat59Hz_ViewType(int id) {
    //#[ operation AplParamRecFormat59Hz_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_REC_FORMAT_59HZ_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_59HZ_P2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_59HZ_MOV
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_59HZ_AVCHD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_59HZ_MP4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_59HZ_MP4_LPCM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_59HZ_MOV_LPCM
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamRecFormat59Hz].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FORMAT_59HZ_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecFormat59Hz, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FORMAT_59HZ_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamRecFormat59Hz].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_REC_FORMAT_59HZ_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamRecFormat50Hz_ViewType(int id) {
    //#[ operation AplParamRecFormat50Hz_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_REC_FORMAT_50HZ_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_50HZ_P2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_50HZ_MOV
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_50HZ_AVCHD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_50HZ_MP4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_50HZ_MP4_LPCM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FORMAT_50HZ_MOV_LPCM
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamRecFormat50Hz].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FORMAT_50HZ_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecFormat50Hz, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FORMAT_50HZ_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamRecFormat50Hz].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_REC_FORMAT_50HZ_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamAudioVol_ViewType(int id) {
    //#[ operation AplParamAudioVol_ViewType(int)
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton1_ViewType(int id) {
    //#[ operation AplParamUserButton1_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton1].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton1, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton1].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton2_ViewType(int id) {
    //#[ operation AplParamUserButton2_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton2].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton2, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton2].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton3_ViewType(int id) {
    //#[ operation AplParamUserButton3_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton3].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton3, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton3].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton4_ViewType(int id) {
    //#[ operation AplParamUserButton4_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton4].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton4, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton4].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton5_ViewType(int id) {
    //#[ operation AplParamUserButton5_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton5].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton5, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton5].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton6_ViewType(int id) {
    //#[ operation AplParamUserButton6_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton6].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton6, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton6].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton7_ViewType(int id) {
    //#[ operation AplParamUserButton7_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton7].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton7, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton7].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton8_ViewType(int id) {
    //#[ operation AplParamUserButton8_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton8].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton8, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton8].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton9_ViewType(int id) {
    //#[ operation AplParamUserButton9_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton9].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton9, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton9].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton10_ViewType(int id) {
    //#[ operation AplParamUserButton10_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton10].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton10, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton10].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton11_ViewType(int id) {
    //#[ operation AplParamUserButton11_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton11].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton11, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton11].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUserButton12_ViewType(int id) {
    //#[ operation AplParamUserButton12_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_BUTTON_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_INH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PUSH_AF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOTLIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BLACKFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WHITEFADE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ATW_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_D_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HISTOGRAM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PARALLAX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_R_IMAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CV_RESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_CHECK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LAST_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_3D_CHANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_MENU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FREEZE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_S_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CAPTURE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WIFI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_LIGHT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGROUND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FLASH_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FOCUS_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PREREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_WFM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_USB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AF_AREA_RANGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IA_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_V_LOG_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_EVF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_FA2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SLOT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SUPERSLOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BALANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOWLUX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_LOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_MID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_GAIN_HIGH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_ONE_PUSH_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LEVELGAGE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SDI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_HDMI_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_COLOR_BARS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_CLEAN_VIEW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCD_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_POWER_LCD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUTO_IRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_IRIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_YGET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_NETWORK_STREAM_START
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_DURING_UL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_UPLOAD_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_REC_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_TEXT_MEMO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_SHOT_MARK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_AUDIO_MON_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LOAD_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_CARD_READER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_BUTTON_LCDVF_HDR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserButton12].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton12, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserButton12].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_USER_BUTTON_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamFileMenu_ViewType(int id) {
    //#[ operation AplParamFileMenu_ViewType(int)
    AplParamState Exclusion[ APL_SYS_PARAM_FILE_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_MENU_LOAD_SAVE_SLOT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_MENU_SCENE_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_MENU_SETUP_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_MENU_SETUP_FILE_MEM
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamEnableSceneFileLoad,
    	AplParamEnableSceneFileSave,
    	AplParamEnableSceneFileSaveAs,
    	AplParamEnableSetupFileLoad,
    	AplParamEnableSetupFileSave,
    	AplParamEnableSetupFileSaveAs,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamFileMenu].mState;
    // ---------------------------------------------------------
    
    if ( APL_PARAM_GET_DATA( AplParamEnableSceneFileLoad ) == APL_SYS_PARAM_SWITCH_OFF &&
    	 APL_PARAM_GET_DATA( AplParamEnableSceneFileSave ) == APL_SYS_PARAM_SWITCH_OFF &&
    	 APL_PARAM_GET_DATA( AplParamEnableSceneFileSaveAs ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_FILE_MENU_SCENE_FILE] = AplParamState_VisibleInvalid;
    }
    
    if ( APL_PARAM_GET_DATA( AplParamEnableSetupFileLoad ) == APL_SYS_PARAM_SWITCH_OFF &&
    	 APL_PARAM_GET_DATA( AplParamEnableSetupFileSave ) == APL_SYS_PARAM_SWITCH_OFF &&
    	 APL_PARAM_GET_DATA( AplParamEnableSetupFileSaveAs ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_FILE_MENU_SETUP_FILE] = AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FILE_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamFileMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FILE_MENU_MAX + 1 ; i++ ){
    	m_Item[AplParamFileMenu].sub_item[i].state =  Exclusion[i];
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamSceneGammaSettingMenu_ViewType(int id) {
    //#[ operation AplParamSceneGammaSettingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_GAMMA_SETTING_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAMMA_SETTING_MENU_MASTER_GAMMA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAMMA_SETTING_MENU_F_REC_DYNAMIC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAMMA_SETTING_MENU_F_REC_BLACK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAMMA_SETTING_MENU_V_REC_KNEE_SLOPE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAMMA_SETTING_MENU_V_REC_KNEE_POINT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAMMA_SETTING_MENU_BLACK_GAMMA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAMMA_SETTING_MENU_BGAMMA_RANGE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneGammaModeSel,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSceneGammaSettingMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // MASTER GAMMA ===================================
    // [GAMMA MODE SEL]=[HLG]時はグレーアウト
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_MASTER_GAMMA]		= AplParamState_VisibleInvalid;
    }
    
    // F-REC DYNAMIC LVL ===================================
    // F-REC BLACK STR LVL ===================================
    // [FILM-REC]時以外はグレーアウト
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) != APL_SYS_PARAM_GAMMA_MODE_SEL_FILM_REC )
    {
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_F_REC_DYNAMIC]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_F_REC_BLACK]			= AplParamState_VisibleInvalid;
    }
    
    // V-REC KNEE SLOPE ===================================
    // V-REC KNEE POINT ===================================
    // [VIDEO-REC]時以外はグレーアウト
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) != APL_SYS_PARAM_GAMMA_MODE_SEL_VIDEO_REC )
    {
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_V_REC_KNEE_SLOPE]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_V_REC_KNEE_POINT]	= AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_GAMMA_SETTING_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSceneGammaSettingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_GAMMA_SETTING_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamSceneKneeSettingMenu_ViewType(int id) {
    //#[ operation AplParamSceneKneeSettingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_KNEE_SETTING_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_KNEE_SETTING_MENU_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_KNEE_SETTING_MENU_AKNEE_RESPONSE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_KNEE_SETTING_MENU_MASTER_POINT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_KNEE_SETTING_MENU_MASTER_SLOPE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_POINT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_SLOPE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneGammaModeSel,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSceneKneeSettingMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // KNEE MODE ===================================
    // A.KNEE RESPONSE ===================================
    // KNEE POINT ===================================
    // KNEE SLOPE ===================================
    // [GAMMA MODE SEL]=[HLG]時はグレーアウト
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_MODE]				= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_AKNEE_RESPONSE]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_MASTER_POINT]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_MASTER_SLOPE]		= AplParamState_VisibleInvalid;
    }
    
    // HLG KNEE SW ===================================
    // HLG KNEE POINT ===================================
    // HLG KNEE SLOPE ===================================
    // [GAMMA MODE SEL]=「HLG」時のみ有効
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) != APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_SW]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_POINT]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_SLOPE]	= AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_KNEE_SETTING_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSceneKneeSettingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_KNEE_SETTING_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamSceneFileMenu_ViewType(int id) {
    //#[ operation AplParamSceneFileMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SCENE_FILE_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_SELECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_NAME_EDIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_DATA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_VFR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_FRAME_RATE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_SYNC_SCAN_TYPE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_SYNC_SCAN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_MASTER_DTL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_DTL_CORING
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_DETAIL_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_SKIN_TONE_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_SKIN_TONE_B
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_SKIN_TONE_C
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_SKIN_TONE_ZEBRA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_SKIN_TONE_DTL_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_RB_GAIN_CTRL_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_COLOR_TEMP_A
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_COLOR_TEMP_B
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_CHROMA_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_CHROMA_PHASE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_MATRIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_MATRIX_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_COLOR_CORRECTION
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_MASTER_PED
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_RGB_BLACK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_GAMMA_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_GAMMA_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_KNEE_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_WHITE_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_DRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_DRS_EFFECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_DNR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_AIRIS_LEVEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_MENU_AIRIS_LEVEL_EFFECT
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemRecMode,
    	AplParamSuperSlowRec,
    	AplParamSceneVFRMode,
    	AplParamSceneGammaModeSel,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSceneFileMenu].mState;
    // ---------------------------------------------------------
    
    // 機能で無効表示とする処理 ==================
    // VFR ===================================
    // FILE FORMAT ① [MOV] 以外時：無効（OFF固定）
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_VFR]			= AplParamState_VisibleInvalid;
    }
#if 0
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    // REC FORMAT ② [59.94i/50.00i] 時：無効（OFF固定）
    if ( VideoProperty.FrameRate == AVS_FRAME_RATE_60_I )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_VFR]			= AplParamState_VisibleInvalid;
    }
#endif
    // ③[SUPER SLOW] が [ON] 時 ： 無効（ON固定）
    if ( APL_PARAM_GET_DATA( AplParamSuperSlowRec ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_VFR]			= AplParamState_VisibleInvalid;
    }
    
    // FRAME RATE ===================================
    //① [OFF] 時 ： 無効（グレーアウト）
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_FRAME_RATE]		= AplParamState_VisibleInvalid;
    }
    //  [SUPER SLOW] が [ON] 時 ： 無効
    if ( APL_PARAM_GET_DATA( AplParamSuperSlowRec ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_FRAME_RATE]		= AplParamState_VisibleInvalid;
    }
    
    
    // WHITE CLIP ===================================
    // WHITE CLIP LEVEL ===================================
    // [GAMMA MODE SEL]=[HLG]時はグレーアウト
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_WHITE_CLIP]		= AplParamState_VisibleInvalid;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SCENE_FILE_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSceneFileMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SCENE_FILE_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamStreamingMenu_ViewType(int id) {
    //#[ operation AplParamStreamingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_STREAMING_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_STREAMING_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_QOS_MAX_RATE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_QOS_MIN_RATE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_STREAMING_LATENCY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_START_TRIGGER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_CONNECT_INFO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_DATA_TYPE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_RECEIVER_URL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_LOAD_CARD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_SAVE_CARD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_CLEAR_MEM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_MENU_START
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamStreamingDataType,
    	AplParamStreamingConnectionInfo,
    	AplParamStreamingStartTrigger,
    	AplParamSDcardInOutStatus,
    	AplParamWLanStatus,
    	AplParamSavedStreamingData,
    	AplParamRecFormat59Hz,
    	AplParamRecFormat50Hz,
    	AplParamP2Quality59Hz,
    	AplParamP2Quality50Hz,
    	AplParamMOVQuality59Hz,
    	AplParamMOVQuality50Hz,
    	AplParamAVCHDQuality59Hz,
    	AplParamAVCHDQuality50Hz,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamStreamingMenu].mState;
    // ---------------------------------------------------------
#if 0
    APL_SYS_PARAM_RECMODE recMode = (APL_SYS_PARAM_RECMODE)APL_PARAM_GET_DATA( AplParamSystemRecMode );
    if ( APL_PARAM()->isAVCHD( recMode ) == true ) {
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_STREAMING_FORMAT] = AplParamState_VisibleInvalid;
    }
    else {
    	AplIfAvs::AvsIfVideoProperty VideoProperty;
    	memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    	AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode( recMode ), VideoProperty );
    	
    	switch ( VideoProperty.Height ) {
    	case 1080:
    	case 720:
    		// 1080、720は排他無し
    		break;
    	default:
    		// UHDは排他
    		Exclusion[APL_SYS_PARAM_STREAMING_MENU_STREAMING_FORMAT] = AplParamState_VisibleInvalid;
    		break;	
    	}
    }
#endif
    // AplParamStreamingDataType
    if (( APL_PARAM_GET_DATA( AplParamStreamingConnectionInfo ) == APL_SYS_PARAM_STREAMING_CONNECTION_INFO_MEMORY ) &&
    	( APL_PARAM_GET_DATA( AplParamStreamingDataType ) == APL_SYS_PARAM_STREAMING_DATA_TYPE_GENERAL ))
    {
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_RECEIVER_URL] = AplParamState_VisibleValid;
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_SAVE_CARD] = AplParamState_VisibleValid;
    }
    else
    {
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_RECEIVER_URL] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_SAVE_CARD] = AplParamState_VisibleInvalid;
    }
    
    // AplParamStreamingStartTrigger
    if ( APL_PARAM_GET_DATA( AplParamStreamingStartTrigger ) == APL_SYS_PARAM_STREAMING_START_TRIGGER_RECEIVER )
    {
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_CONNECT_INFO] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_RECEIVER_URL] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_START] = AplParamState_VisibleInvalid;
    }
    
    //	AplParamSDcardInOutStatus
    switch( APL_PARAM_GET_DATA( AplParamSDcardInOutStatus ) ){
     	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_STREAMING_MENU_LOAD_CARD] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_STREAMING_MENU_SAVE_CARD] = AplParamState_VisibleInvalid;
       		break;
       	case APL_SYS_PARAM_SWITCH_ON:
       		break;
       	default:
       		break;
    }
    
    // WLAN、LANの接続状態
    switch ( APL_PARAM_GET_DATA( AplParamWLanStatus ) ) {
    case APL_SYS_PARAM_WLAN_DISCONNECT:
    case APL_SYS_PARAM_WLAN_LAN_DISCONNECT:
    case APL_SYS_PARAM_WLAN_DISABLE:
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_START] = AplParamState_VisibleInvalid;
    	break;
    default:
    	break;
    }
    
    // STREAMING設定ファイルの保存状態
    if ( APL_PARAM_GET_DATA( AplParamSavedStreamingData ) == APL_SYS_PARAM_SWITCH_OFF ) {
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_CLEAR_MEM] = AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_STREAMING_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamStreamingMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_STREAMING_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamStreamingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_STREAMING_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamNetworkDeviceSel_ViewType(int id) {
    //#[ operation AplParamNetworkDeviceSel_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_NETWORK_DEVICE_SEL_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_DEVICE_SEL_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_DEVICE_SEL_LAN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_DEVICE_SEL_WLAN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_DEVICE_SEL_CELLULAR
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamNetworkDeviceSel].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_DEVICE_SEL_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamNetworkDeviceSel, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_DEVICE_SEL_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[ AplParamNetworkDeviceSel].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_NETWORK_DEVICE_SEL_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamNetworkFunc_ViewType(int id) {
    //#[ operation AplParamNetworkFunc_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_NETWORK_FUNC_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_FUNC_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_FUNC_FTP_CLIENT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_FUNC_STREAMING
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_FUNC_NDI_HX
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamNdiHxActivation,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamNetworkFunc].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_FUNC_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamNetworkFunc, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_FUNC_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamNetworkFunc].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_NETWORK_FUNC_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamNetworkMenu_ViewType(int id) {
    //#[ operation AplParamNetworkMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_NETWORK_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_DEVICE_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_NETWORK_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_IP_REMOTE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_FTP_CLIENT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_STREAMING
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_NDIHX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_LAN_PROPERTY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_WLAN_PROPERTY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_CELLULAR_PROPERTY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_INFORMATION
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_MENU_UTILITY
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamNetworkDeviceSel,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamNetworkMenu].mState;
    // ---------------------------------------------------------
    
    // DEVICE SEL
    switch ( APL_PARAM_GET_DATA( AplParamNetworkDeviceSel ) ) {
    case APL_SYS_PARAM_NETWORK_DEVICE_SEL_LAN:
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_WLAN_PROPERTY] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_CELLULAR_PROPERTY] = AplParamState_VisibleInvalid;
    	break;
    case APL_SYS_PARAM_NETWORK_DEVICE_SEL_WLAN:
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_LAN_PROPERTY] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_CELLULAR_PROPERTY] = AplParamState_VisibleInvalid;
    	break;
    case APL_SYS_PARAM_NETWORK_DEVICE_SEL_CELLULAR:
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_LAN_PROPERTY] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_WLAN_PROPERTY] = AplParamState_VisibleInvalid;
    	break;
    default:
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_LAN_PROPERTY] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_WLAN_PROPERTY] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_NETWORK_MENU_CELLULAR_PROPERTY] = AplParamState_VisibleInvalid;
    	break;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamNetworkMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamNetworkMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_NETWORK_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamStreamingDataType_ViewType(int id) {
    //#[ operation AplParamStreamingDataType_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_STREAMING_DATA_TYPE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_DATA_TYPE_GENERAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_DATA_TYPE_P2CAST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_DATA_TYPE_LIVEU
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_DATA_TYPE_TVU
    };
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamStreamingDataType].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_STREAMING_DATA_TYPE_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamStreamingDataType, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_STREAMING_DATA_TYPE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamStreamingDataType].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_STREAMING_DATA_TYPE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamNetInformationMenu_ViewType(int id) {
    //#[ operation AplParamNetInformationMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_NET_INFORMATION_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NET_INFORMATION_MENU_NETWORK_ID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NET_INFORMATION_MENU_STATUS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NET_INFORMATION_MENU_LOG
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NET_INFORMATION_MENU_SAVE_LOG
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSDcardInOutStatus,
    	AplParamEnableSDWriteStatus,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamStreamingDataType].mState;
    // ---------------------------------------------------------
    
    // AplParamIdMax
    // AplParamSDcardInOutStatus
    if (( APL_PARAM_GET_DATA( AplParamSDcardInOutStatus ) == APL_SYS_PARAM_SWITCH_ON ) &&
    	( APL_PARAM_GET_DATA( AplParamEnableSDWriteStatus ) == APL_SYS_PARAM_SWITCH_ON ))
    {
    	Exclusion[APL_SYS_PARAM_NET_INFORMATION_MENU_SAVE_LOG] = AplParamState_VisibleValid;
    }
    else
    {
    	Exclusion[APL_SYS_PARAM_NET_INFORMATION_MENU_SAVE_LOG] = AplParamState_VisibleInvalid;
    }
    
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NET_INFORMATION_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamNetInformationMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NET_INFORMATION_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamNetInformationMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_NET_INFORMATION_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamFTPClientMenu_ViewType(int id) {
    //#[ operation AplParamFTPClientMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_FTP_CLIENT_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_CONNECT_INFO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_DATA_TYPE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_SERVER_URL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_LOGIN_USER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_LOGIN_PASS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_LOAD_CARD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_SAVE_CARD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_CLEAR_MEMORY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_REC_DURING_UP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_AUTO_UP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FTP_CLIENT_MENU_UP_LIST
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamFTPClientMenu].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FTP_CLIENT_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamFTPClientMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FTP_CLIENT_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamFTPClientMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_FTP_CLIENT_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamCellularPropertyMenu_ViewType(int id) {
    //#[ operation AplParamCellularPropertyMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_APN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_USER_ID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_PASS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_DIAL_NO
    };
    				
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamCellularPropertyMenu].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamCellularPropertyMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamCellularPropertyMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamIpRemoteMenu_ViewType(int id) {
    //#[ operation AplParamIpRemoteMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_IP_REMOTE_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IP_REMOTE_MENU_ENABLE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IP_REMOTE_MENU_USER_ACCOUNT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IP_REMOTE_MENU_ACCOUNT_LIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IP_REMOTE_MENU_PORT
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserAccountNum,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamIpRemoteMenu].mState;
    // ---------------------------------------------------------
#if 0
    int accountNum = APL_PARAM_GET_DATA( AplParamUserAccountNum );
    if ( accountNum == 0 ) {
    	Exclusion[APL_SYS_PARAM_IP_REMOTE_MENU_ACCOUNT_LIST] = AplParamState_VisibleInvalid;
    }
    else if ( accountNum >= APL_NET_HTTP_SERVER_ACCOUNT_NUM ) {
    	Exclusion[APL_SYS_PARAM_IP_REMOTE_MENU_USER_ACCOUNT] = AplParamState_VisibleInvalid;
    }
#endif
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_IP_REMOTE_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamIpRemoteMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_IP_REMOTE_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamIpRemoteMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_IP_REMOTE_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamAvOutMenu_ViewType(int id) {
    //#[ operation AplParamAvOutMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_AV_OUT_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AV_OUT_MENU_OUTPUT_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AV_OUT_MENU_CHAR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_AV_OUT_MENU_ZEBRA
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneGammaModeSel,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamAvOutMenu].mState;
    // ---------------------------------------------------------
    
    // AV OUT ZEBRA ================================
    // ①[GAMMA MODE SEL]=[HLG]時無効（OFF 固定）
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_AV_OUT_MENU_ZEBRA]= AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_AV_OUT_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamAvOutMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_AV_OUT_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamIndicatorMenu_ViewType(int id) {
    //#[ operation AplParamIndicatorMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_INDICATOR_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_FULLAUTO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_SLOTSTATUS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_2SLOTFUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_STREAMING
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_NETWORK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_BATTERYREMAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_RECFORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_FRAMERATE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_BONDINGDEVICE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_RECREMOTE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_RECMODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_FBC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_HDRDRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_OIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_SCENEFILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_AUDIOLEVELMETER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_NDFILTER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_SHUTTER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_IIRS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_ZOOMFOCUS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_WHITE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_DATETIME
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_SHOOTINGMODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_MULTIMANUAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_DZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_IRREC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_INDICATOR_MENU_PLAYBACKSTATUS
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamTimeStamp
    	
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamIndicatorMenu].mState;
    // ---------------------------------------------------------
    
    // DATE/TIME ================================
    // ① [TIME STAMP] が [OFF] 以外時：無効（OFF 固定）
    if ( APL_PARAM_GET_DATA( AplParamTimeStamp ) != APL_SYS_PARAM_TIMESTAMP_OFF )
    {
    	Exclusion[APL_SYS_PARAM_INDICATOR_MENU_DATETIME] = AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_INDICATOR_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamIndicatorMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_INDICATOR_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamIndicatorMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_INDICATOR_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamRecFunctionMode_ViewType(int id) {
    //#[ operation AplParamRecFunctionMode_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamRecFunctionMode].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FUNCTION_MODE_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecFunctionMode, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FUNCTION_MODE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamRecFunctionMode].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_REC_FUNCTION_MODE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamSwModeMenu_ViewType(int id) {
    //#[ operation AplParamSwModeMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWMODE_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_LOW_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_MID_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_HIGH_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_SUPER_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_OIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_HYBRID_OIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_OIS_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_ATW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_ATW_SPEED
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_ATW_TARGET_R
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_ATW_TARGET_B
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_WBAL_PRESET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_WBAL_VAR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_HZOOM_SPEED
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_IZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_PUSH_AF_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_MF_ASSIST
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_MACRO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_MACRO_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_AF_SPEED
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_AF_AREA_WIDTH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_AIRIS_SPEED
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_AIRIS_WINDOW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_AREA_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_ZOOM_FOCUS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWMODE_MENU_IR_SHOOTING
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamOisMode,
    	AplParamSuperSlowRec,
    	AplParamSceneVFRMode,
    	AplParamWhiteBalancePreSetMode
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSwModeMenu].mState;
    // ---------------------------------------------------------
    
    // HYBRID O.I.S. ================================
    // ① [O.I.S.] が [OFF] 時：無効（グレーアウト）
    if ( APL_PARAM_GET_DATA( AplParamOisMode ) == APL_SYS_PARAM_OIS_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_HYBRID_OIS]= AplParamState_VisibleInvalid;
    }
    // ② [SUPER SLOW] が [ON] 時：無効（グレーアウト）
    if ( APL_PARAM_GET_DATA( AplParamSuperSlowRec ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_HYBRID_OIS]= AplParamState_VisibleInvalid;
    }
    // ③ [VFR] が [ON] 時：無効（グレーアウト）
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_HYBRID_OIS]= AplParamState_VisibleInvalid;
    }
    
    // O.I.S. MODE ================================
    // ① [O.I.S.] が [OFF] 時：無効（グレーアウト）
    if ( APL_PARAM_GET_DATA( AplParamOisMode ) == APL_SYS_PARAM_OIS_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_OIS_MODE]= AplParamState_VisibleInvalid;
    }
    
    // W.BAL VAR ================================
    // ① [W.BAL PRESET] ＝　[5600K]　or　[3200K]　設定時　：無効（グレーアウト）
    if ( APL_PARAM_GET_DATA( AplParamWhiteBalancePreSetMode ) == APL_SYS_PARAM_WB_PRE_SET_MODE_3200K ||
    	 APL_PARAM_GET_DATA( AplParamWhiteBalancePreSetMode ) == APL_SYS_PARAM_WB_PRE_SET_MODE_5600K )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_WBAL_VAR]= AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SWMODE_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamSwModeMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SWMODE_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSwModeMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWMODE_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamFileSceneFileMenu_ViewType(int id) {
    //#[ operation AplParamFileSceneFileMenu_ViewType(int)
    AplParamState Exclusion[ APL_SYS_PARAM_FILE_SCENE_FILE_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SCENE_FILE_MENU_LOAD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SCENE_FILE_MENU_SAVE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SCENE_FILE_MENU_SAVE_AS
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamEnableSceneFileLoad,
    	AplParamEnableSceneFileSave,
    	AplParamEnableSceneFileSaveAs,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamFileSceneFileMenu].mState;
    // ---------------------------------------------------------
    
    // AplParamEnableSceneFileLoad
    switch( APL_PARAM_GET_DATA( AplParamEnableSceneFileLoad ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_FILE_SCENE_FILE_MENU_LOAD] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamEnableSceneFileSave
    switch( APL_PARAM_GET_DATA( AplParamEnableSceneFileSave ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_FILE_SCENE_FILE_MENU_SAVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    // AplParamEnableSceneFileSaveAs
    switch( APL_PARAM_GET_DATA( AplParamEnableSceneFileSaveAs ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_FILE_SCENE_FILE_MENU_SAVE_AS] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FILE_SCENE_FILE_MENU_MAX + 1 ; i++ )
    {
    	m_Item[AplParamFileSceneFileMenu].sub_item[i].state =  Exclusion[i];
    }
    
    return AplParamState_VisibleValid;
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamFileSetupFileMenu_ViewType(int id) {
    //#[ operation AplParamFileSetupFileMenu_ViewType(int)
    AplParamState Exclusion[ APL_SYS_PARAM_FILE_SETUP_FILE_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SETUP_FILE_MENU_LOAD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SETUP_FILE_MENU_SAVE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FILE_SETUP_FILE_MENU_SAVE_AS
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamEnableSetupFileLoad,
    	AplParamEnableSetupFileSave,
    	AplParamEnableSetupFileSaveAs,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamFileSetupFileMenu].mState;
    // ---------------------------------------------------------
    
    // AplParamEnableSetupFileLoad
    switch( APL_PARAM_GET_DATA( AplParamEnableSetupFileLoad ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_FILE_SETUP_FILE_MENU_LOAD] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    // AplParamEnableSetupFileSave
    switch( APL_PARAM_GET_DATA( AplParamEnableSetupFileSave ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_FILE_SETUP_FILE_MENU_SAVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    // AplParamEnableSetupFileSaveAs
    switch( APL_PARAM_GET_DATA( AplParamEnableSetupFileSaveAs ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_FILE_SETUP_FILE_MENU_SAVE_AS] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FILE_SETUP_FILE_MENU_MAX + 1 ; i++ ){
    	m_Item[AplParamFileSetupFileMenu].sub_item[i].state =  Exclusion[i];
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamOthersMenu_ViewType(int id) {
    //#[ operation AplParamOthersMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_OTHERS_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OTHERS_MENU_FILE
    	AplParamState_Invisible,	// APL_SYS_PARAM_OTHERS_MENU_USER_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OTHERS_MENU_COLOR_BAR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OTHERS_MENU_LED
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OTHERS_MENU_CLOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OTHERS_MENU_USB_DEVICE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OTHERS_MENU_INFORMATION
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OTHERS_MENU_LANGUAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OTHERS_MENU_INIT
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamOthersMenu].mState;
    // ---------------------------------------------------------
    
    // 本体品番AG-CX350 AREA2はLANGUAGE非表示
    char model[AplParamInfoModel_Size] = {0};
    APL_PARAM_GET_DATA_AREA(AplParamInfoModel,(UB*)model,AplParamInfoModel_Size);
    if( strncmp(model,"AG-CX350",AplParamInfoModel_Size) == 0 && APL_PARAM_GET_DATA( AplParamUSeAreaSettings ) == APL_SYS_PARAM_USE_AREA_2 )
    {
    	Exclusion[APL_SYS_PARAM_OTHERS_MENU_LANGUAGE] = AplParamState_Invisible;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_OTHERS_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamOthersMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_OTHERS_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamWlanPropertyMenu_ViewType(int id) {
    //#[ operation AplParamWlanPropertyMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_WLAN_PROPERTY_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_MAC_ADR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_TYPE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_CHANNEL_24GHZ
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_CHANNEL_5GHZ
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_ENCRYPTION
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_ENCRYPT_KEY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_IPV4_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_PROPERTY_MENU_IPV6_SET
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamWlanPropertyMenu].mState;
    // ---------------------------------------------------------
    
    // BAND ================================
    // ⑤[WIRELESS PROPERTY]-[TYPE]が[DIRECT]以外選択時、グレーアウト
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) != APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_BAND]= AplParamState_VisibleInvalid;
    }
    
    // CHANNEL(2.4GHz) ================================
    // ⑤[WIRELESS PROPERTY]-[TYPE]が[DIRECT]以外選択時、グレーアウト
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) != APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_CHANNEL_24GHZ]= AplParamState_VisibleInvalid;
    }
    
    // CHANNEL(5GHz) ================================
    // ⑤[WIRELESS PROPERTY]-[TYPE]が[DIRECT]以外選択時、グレーアウト
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) != APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_CHANNEL_5GHZ]= AplParamState_VisibleInvalid;
    }
    
    // ENCRYPTION ================================
    // ⑤[WIRELESS PROPERTY]-[TYPE]が[DIRECT]選択時、[WPA2-AES]固定（グレー）
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) == APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_ENCRYPTION]= AplParamState_VisibleInvalid;
    }
    
    // ENCRYPT KEY ================================
    // ⑨ENCRYPTIONがNONEならグレーアウト　値は保持
    if ( APL_PARAM_GET_DATA( AplParamEncryption ) == APL_NET_PARAM_SECURITY_TYPE_NONE )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_ENCRYPT_KEY] = AplParamState_VisibleInvalid;
    }
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_WLAN_PROPERTY_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamWlanPropertyMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_WLAN_PROPERTY_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamWlanPropertyMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_WLAN_PROPERTY_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamLanDhcpModeV6_ViewType(int id) {
    //#[ operation AplParamLanDhcpModeV6_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_NET_PARAM_DHCP_MODE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_NET_PARAM_DHCP_MODE_OFF
    	AplParamState_VisibleValid,	// APL_NET_PARAM_DHCP_MODE_CLIENT
    	AplParamState_VisibleValid,	// APL_NET_PARAM_DHCP_MODE_SERVER
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamLanDhcpModeV6].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_NET_PARAM_DHCP_MODE_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamLanDhcpModeV6, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_NET_PARAM_DHCP_MODE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLanDhcpModeV6].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_NET_PARAM_DHCP_MODE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamHpOut_ViewType(int id) {
    //#[ operation AplParamHpOut_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_HP_OUT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HP_OUT_CH1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HP_OUT_CH2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HP_OUT_STEREO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HP_OUT_MIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HP_OUT_CH3
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HP_OUT_CH4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HP_OUT_CH34_STEREO
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HP_OUT_CH34_MIX
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamHpOut].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HP_OUT_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamHpOut, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HP_OUT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamHpOut].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_HP_OUT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamLanIPv6SettingMenu_ViewType(int id) {
    //#[ operation AplParamLanIPv6SettingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_IPV6_SET_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV6_SET_MENU_ENABLE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV6_SET_MENU_DHCP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV6_SET_MENU_IP_ADR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV6_SET_MENU_PREFIX_LEN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV6_SET_MENU_DEFAULT_GATEWAY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV6_SET_MENU_PRIMARY_DNS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV6_SET_MENU_SECONDARY_DNS
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamLanEnableIPv6,
    	AplParamLanDhcpModeV6,
    	AplParamLanDnsPrimaryV6UpdateDhcp,
    	AplParamLanDnsSecondaryV6UpdateDhcp,
    };
    
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamLanIPv6SettingMenu].mState;
    // ---------------------------------------------------------
    
    if ( APL_PARAM_GET_DATA( AplParamLanEnableIPv6 ) == APL_SYS_PARAM_SWITCH_ON ) {
    	// IPv6 ENALBE
    	
    	if ( APL_PARAM_GET_DATA( AplParamLanDhcpModeV6 ) == APL_NET_PARAM_DHCP_MODE_CLIENT ) {
    		// DHCP CLIENT
    		Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_IP_ADR] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_PREFIX_LEN] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_DEFAULT_GATEWAY] = AplParamState_VisibleInvalid;
    	
    		// DNSはDHCPで割当てられたらグレーアウト
    		if ( APL_PARAM_GET_DATA( AplParamLanDnsPrimaryV6UpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    			Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_PRIMARY_DNS] = AplParamState_VisibleInvalid;
    		}
    		
    		if ( APL_PARAM_GET_DATA( AplParamLanDnsSecondaryV6UpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    			Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_SECONDARY_DNS] = AplParamState_VisibleInvalid;
    		}
    	}
    }
    else {
    	// IPv6 DISABLE
    	Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_DHCP] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_IP_ADR] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_PREFIX_LEN] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_DEFAULT_GATEWAY] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_PRIMARY_DNS] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV6_SET_MENU_SECONDARY_DNS] = AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_IPV6_SET_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLanIPv6SettingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_IPV6_SET_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamWLanIPv4SettingMenu_ViewType(int id) {
    //#[ operation AplParamWLanIPv4SettingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_IPV4_SET_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_DHCP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_IP_ADR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_SUBNET_MASK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_DEFAULT_GATEWAY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_PRIMARY_DNS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_SECONDARY_DNS
    };
     
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamDhcpMode,
    	AplParamDnsPrimaryUpdateDhcp,
    	AplParamDnsSecondaryUpdateDhcp,
    };
    
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamWLanIPv4SettingMenu].mState;
    // ---------------------------------------------------------
    
    // DHCP CLIENT
    if ( APL_PARAM_GET_DATA( AplParamDhcpMode ) == APL_NET_PARAM_DHCP_MODE_CLIENT ) {
    	Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_IP_ADR] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_SUBNET_MASK] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_DEFAULT_GATEWAY] = AplParamState_VisibleInvalid;
    
    	// DNSはDHCPで割当てられたらグレーアウト
    	if ( APL_PARAM_GET_DATA( AplParamDnsPrimaryUpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    		Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_PRIMARY_DNS] = AplParamState_VisibleInvalid;
    	}
    	
    	if ( APL_PARAM_GET_DATA( AplParamDnsSecondaryUpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    		Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_SECONDARY_DNS] = AplParamState_VisibleInvalid;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_IPV4_SET_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamWLanIPv4SettingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_IPV4_SET_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamLanIPv4SettingMenu_ViewType(int id) {
    //#[ operation AplParamLanIPv4SettingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_IPV4_SET_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_DHCP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_IP_ADR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_SUBNET_MASK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_DEFAULT_GATEWAY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_PRIMARY_DNS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_IPV4_SET_MENU_SECONDARY_DNS
    };
     
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamLanDhcpMode,
    	AplParamLanDnsPrimaryUpdateDhcp,
    	AplParamLanDnsSecondaryUpdateDhcp,
    };
    
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamLanIPv4SettingMenu].mState;
    // ---------------------------------------------------------
    
    // DHCP CLIENT
    if ( APL_PARAM_GET_DATA( AplParamLanDhcpMode ) == APL_NET_PARAM_DHCP_MODE_CLIENT ) {
    	Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_IP_ADR] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_SUBNET_MASK] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_DEFAULT_GATEWAY] = AplParamState_VisibleInvalid;
    
    	// DNSはDHCPで割当てられたらグレーアウト
    	if ( APL_PARAM_GET_DATA( AplParamLanDnsPrimaryUpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    		Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_PRIMARY_DNS] = AplParamState_VisibleInvalid;
    	}
    	
    	if ( APL_PARAM_GET_DATA( AplParamLanDnsSecondaryUpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    		Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_SECONDARY_DNS] = AplParamState_VisibleInvalid;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_IPV4_SET_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLanIPv4SettingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_IPV4_SET_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamNdiHxMenu_ViewType(int id) {
    //#[ operation AplParamNdiHxMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_NDI_HX_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_MENU_ACTIVATION
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_MENU_STREAM_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_MENU_CLEAR_ACTIVATION
    };
    				
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamNdiHxActivation,
    	AplParamRecFormat59Hz,
    	AplParamRecFormat50Hz,
    	AplParamP2Quality59Hz,
    	AplParamP2Quality50Hz,
    	AplParamMOVQuality59Hz,
    	AplParamMOVQuality50Hz,
    	AplParamAVCHDQuality59Hz,
    	AplParamAVCHDQuality50Hz,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamNdiHxMenu].mState;
    // ---------------------------------------------------------
#if 0
    APL_SYS_PARAM_RECMODE recMode = (APL_SYS_PARAM_RECMODE)APL_PARAM_GET_DATA( AplParamSystemRecMode );
    if ( APL_PARAM()->isAVCHD( recMode ) == true ) {
    	Exclusion[APL_SYS_PARAM_NDI_HX_MENU_STREAM_FORMAT] = AplParamState_VisibleInvalid;
    }
    else {
    	AplIfAvs::AvsIfVideoProperty VideoProperty;
    	memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    	AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode( recMode ), VideoProperty );
    	
    	switch ( VideoProperty.Height ) {
    	case 1080:
    		if ( VideoProperty.FrameRate == AVS_FRAME_RATE_2398_P ) {
    			Exclusion[APL_SYS_PARAM_NDI_HX_MENU_STREAM_FORMAT] = AplParamState_VisibleInvalid;
    		}
    		break;
    	case 720:
    		// 720はVUP且つ排他は無し
    		break;
    	default:
    		// UHDは排他
    		Exclusion[APL_SYS_PARAM_NDI_HX_MENU_STREAM_FORMAT] = AplParamState_VisibleInvalid;
    		break;	
    	}
    }
#endif
    if ( APL_PARAM_GET_DATA( AplParamNdiHxActivation ) == APL_SYS_PARAM_SWITCH_OFF ) {
    	Exclusion[APL_SYS_PARAM_NDI_HX_MENU_STREAM_FORMAT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_NDI_HX_MENU_CLEAR_ACTIVATION] = AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NDI_HX_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamNdiHxMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_NDI_HX_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamUtilityMenu_ViewType(int id) {
    //#[ operation AplParamUtilityMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_UTILITY_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UTILITY_MENU_INIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UTILITY_MENU_EASY_IP_SET
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_UTILITY_MENU_EASY_IP_CAMERA_TITLE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamEasyIpSetting,
    	AplParamNetworkFunc,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUtilityMenu].mState;
    // ---------------------------------------------------------
    
    if ( APL_PARAM_GET_DATA( AplParamEasyIpSetting ) == APL_NET_PARAM_EASY_IP_SETTING_DISABLE ) {
    	Exclusion[APL_SYS_PARAM_UTILITY_MENU_EASY_IP_CAMERA_TITLE] = AplParamState_VisibleInvalid;
    }
    
    if ( APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX ) {
    	Exclusion[APL_SYS_PARAM_UTILITY_MENU_EASY_IP_SET] = AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_UTILITY_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUtilityMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_UTILITY_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamStreamingStart_ViewType(int id) {
    //#[ operation AplParamStreamingStart_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamStreamingStatus,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamStreamingStart].mState;
    // ---------------------------------------------------------
    
    switch ( APL_PARAM_GET_DATA( AplParamStreamingStatus ) ) {
    case APL_SYS_PARAM_STREAMING_STATUS_RUN:
    case APL_SYS_PARAM_STREAMING_STATUS_WAIT:
    	Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    	break;
    case APL_SYS_PARAM_STREAMING_STATUS_STOP:
    	Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    	break;
    default:
    	break;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamStreamingStart].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamStreamingFormat_ViewType(int id) {
    //#[ operation AplParamStreamingFormat_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_STREAMING_FORMAT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamRecFormat59Hz,
    	AplParamRecFormat50Hz,
    	AplParamP2Quality59Hz,
    	AplParamP2Quality50Hz,
    	AplParamMOVQuality59Hz,
    	AplParamMOVQuality50Hz,
    	AplParamAVCHDQuality59Hz,
    	AplParamAVCHDQuality50Hz,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamStreamingFormat].mState;
    // ---------------------------------------------------------
    
    int invalidTable1080_60p[] = {
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M,
    };
    
    int invalidTable1080_50p[] = {
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M,
    };
    
    int invalidTable1080_30p[] = {
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M,
    };
    
    int invalidTable1080_25p[] = {
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M,
    };
    
    int invalidTable1080_24p[] = {
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M,
    };
    
    int invalidTable720_60p[] = {
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M,
    };
    
    int invalidTable720_50p[] = {
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_20M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_6M,
    	APL_SYS_PARAM_STREAMING_FORMAT_1080_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_60_3M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_50_14M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_50_8M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_720_50_3M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_30_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_25_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_8M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_2M,
    	APL_SYS_PARAM_STREAMING_FORMAT_720_24_1M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_30_0_7M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_360_25_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_360_24_0_7M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_30_0_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_4M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_1_5M,
    	//APL_SYS_PARAM_STREAMING_FORMAT_180_25_0_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_4M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_1_5M,
    	APL_SYS_PARAM_STREAMING_FORMAT_180_24_0_5M,
    };
#if 0
    APL_SYS_PARAM_RECMODE recMode = (APL_SYS_PARAM_RECMODE)APL_PARAM_GET_DATA( AplParamSystemRecMode );
    if ( APL_PARAM()->isAVCHD( recMode ) == true ) {
    	for( UW i = 0 ; i < APL_SYS_PARAM_STREAMING_FORMAT_MAX + 1 ; i++ ){
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    else {
    	AplIfAvs::AvsIfVideoProperty VideoProperty;
    	memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    	AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode( recMode ), VideoProperty );
    	
    	bool isNtsc = false;
    	if ( AplIfSys::ModelInfo_GetVideoSystem() == SYS_NTSC ) {
    		isNtsc = true;
    	}
    	
    	switch ( VideoProperty.Height ) {
    	case 1080:
    		switch ( VideoProperty.FrameRate ) {
    		case AVS_FRAME_RATE_60_P:
    			if ( isNtsc == true ) {
    				for( UW i = 0 ; i < ( sizeof(invalidTable1080_60p) / sizeof(int) ) ; i++ ){
    					Exclusion[invalidTable1080_60p[i]] = AplParamState_Invisible;
    				}
    			}
    			else {
    				for( UW i = 0 ; i < ( sizeof(invalidTable1080_50p) / sizeof(int) ) ; i++ ){
    					Exclusion[invalidTable1080_50p[i]] = AplParamState_Invisible;
    				}
    			}
    			break;
    		case AVS_FRAME_RATE_2398_P:
    			for( UW i = 0 ; i < ( sizeof(invalidTable1080_24p) / sizeof(int) ) ; i++ ){
    				Exclusion[invalidTable1080_24p[i]] = AplParamState_Invisible;
    			}
    			break;
    		default:
    			if ( isNtsc == true ) {
    				for( UW i = 0 ; i < ( sizeof(invalidTable1080_30p) / sizeof(int) ) ; i++ ){
    					Exclusion[invalidTable1080_30p[i]] = AplParamState_Invisible;
    				}
    			}
    			else {
    				for( UW i = 0 ; i < ( sizeof(invalidTable1080_25p) / sizeof(int) ) ; i++ ){
    					Exclusion[invalidTable1080_25p[i]] = AplParamState_Invisible;
    				}
    			}
    			break;
    		}
    		break;
    	case 720:
    		if ( isNtsc == true ) {
    			for( UW i = 0 ; i < ( sizeof(invalidTable720_60p) / sizeof(int) ) ; i++ ){
    				Exclusion[invalidTable720_60p[i]] = AplParamState_Invisible;
    			}
    		}
    		else {
    			for( UW i = 0 ; i < ( sizeof(invalidTable720_50p) / sizeof(int) ) ; i++ ){
    				Exclusion[invalidTable720_50p[i]] = AplParamState_Invisible;
    			}
    		}
    		break;
    	default:
    		for( UW i = 0 ; i < APL_SYS_PARAM_STREAMING_FORMAT_MAX + 1 ; i++ ){
    			Exclusion[i] = AplParamState_Invisible;
    		}
    		break;	
    	}
    }
#endif
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_STREAMING_FORMAT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamStreamingFormat].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_STREAMING_FORMAT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamNdiHxStreamingFormat_ViewType(int id) {
    //#[ operation AplParamNdiHxStreamingFormat_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_24M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_16M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_10M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_24M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_16M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_10M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_10M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_6M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_10M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_6M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_10M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_6M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_14M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_10M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_6M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_4M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_2M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_8M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_4M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_2M
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamRecFormat59Hz,
    	AplParamRecFormat50Hz,
    	AplParamP2Quality59Hz,
    	AplParamP2Quality50Hz,
    	AplParamMOVQuality59Hz,
    	AplParamMOVQuality50Hz,
    	AplParamAVCHDQuality59Hz,
    	AplParamAVCHDQuality50Hz,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamNdiHxStreamingFormat].mState;
    // ---------------------------------------------------------
    
    int invalidTable1080_60p[] = {
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_24M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_16M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_10M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_6M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_14M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_10M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_2M,
    };
    
    int invalidTable1080_50p[] = {
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_8M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_24M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_16M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_10M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_6M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_14M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_10M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_2M,
    };
    
    int invalidTable1080_30p[] = {
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_8M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_14M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_10M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_6M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_8M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_4M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_2M,
    };
    
    int invalidTable1080_25p[] = {
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_8M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_14M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_10M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_6M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_8M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_4M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_2M,
    };
    
    int invalidTable720_60p[] = {
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_6M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_14M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_10M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_2M,
    };
    
    int invalidTable720_50p[] = {
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_60_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_24M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_16M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_50_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_30_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_1080_25_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_14M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_10M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_60_6M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_14M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_10M,
    	//APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_50_6M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_30_2M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_8M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_4M,
    	APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_720_25_2M,
    };
#if 0
    APL_SYS_PARAM_RECMODE recMode = (APL_SYS_PARAM_RECMODE)APL_PARAM_GET_DATA( AplParamSystemRecMode );
    if ( APL_PARAM()->isAVCHD( recMode ) == true ) {
    	for( UW i = 0 ; i < APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_MAX + 1 ; i++ ){
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    else {
    	AplIfAvs::AvsIfVideoProperty VideoProperty;
    	memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    	AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode( recMode ), VideoProperty );
    	
    	bool isNtsc = false;
    	if ( AplIfSys::ModelInfo_GetVideoSystem() == SYS_NTSC ) {
    		isNtsc = true;
    	}
    	
    	switch ( VideoProperty.Height ) {
    	case 1080:
    		switch ( VideoProperty.FrameRate ) {
    		case AVS_FRAME_RATE_60_P:
    			if ( isNtsc == true ) {
    				for( UW i = 0 ; i < ( sizeof(invalidTable1080_60p) / sizeof(int) ) ; i++ ){
    					Exclusion[invalidTable1080_60p[i]] = AplParamState_Invisible;
    				}
    			}
    			else {
    				for( UW i = 0 ; i < ( sizeof(invalidTable1080_50p) / sizeof(int) ) ; i++ ){
    					Exclusion[invalidTable1080_50p[i]] = AplParamState_Invisible;
    				}
    			}
    			break;
    		case AVS_FRAME_RATE_2398_P:
    			for( UW i = 0 ; i < APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_MAX + 1 ; i++ ){
    				Exclusion[i] = AplParamState_Invisible;
    			}
    			break;
    		default:
    			if ( isNtsc == true ) {
    				for( UW i = 0 ; i < ( sizeof(invalidTable1080_30p) / sizeof(int) ) ; i++ ){
    					Exclusion[i] = AplParamState_Invisible;
    				}
    			}
    			else {
    				for( UW i = 0 ; i < ( sizeof(invalidTable1080_25p) / sizeof(int) ) ; i++ ){
    					Exclusion[i] = AplParamState_Invisible;
    				}
    			}
    			break;
    		}
    		break;
    	case 720:
    		if ( isNtsc == true ) {
    			for( UW i = 0 ; i < ( sizeof(invalidTable720_60p) / sizeof(int) ) ; i++ ){
    				Exclusion[i] = AplParamState_Invisible;
    			}
    		}
    		else {
    			for( UW i = 0 ; i < ( sizeof(invalidTable720_50p) / sizeof(int) ) ; i++ ){
    				Exclusion[i] = AplParamState_Invisible;
    			}
    		}
    		break;
    	default:
    		for( UW i = 0 ; i < APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_MAX + 1 ; i++ ){
    			Exclusion[i] = AplParamState_Invisible;
    		}
    		break;	
    	}
    }
#endif
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamNdiHxStreamingFormat].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_NDI_HX_STREAMING_FORMAT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamDhcpMode_ViewType(int id) {
    //#[ operation AplParamDhcpMode_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_NET_PARAM_DHCP_MODE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_NET_PARAM_DHCP_MODE_OFF
    	AplParamState_VisibleValid,	// APL_NET_PARAM_DHCP_MODE_CLIENT
    	AplParamState_VisibleValid,	// APL_NET_PARAM_DHCP_MODE_SERVER
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamDhcpMode].mState;
    // ---------------------------------------------------------
    
    // [DIRECT]選択時、CLIENTグレーアウト
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) == APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_NET_PARAM_DHCP_MODE_CLIENT] = AplParamState_VisibleInvalid;
    }
    else
    {
    //  [DIRECT]以外選択時、SERVERグレーアウト
    	Exclusion[APL_NET_PARAM_DHCP_MODE_SERVER] = AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_NET_PARAM_DHCP_MODE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamDhcpMode].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_NET_PARAM_DHCP_MODE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamCopySelectMenu_ViewType(int id) {
    //#[ operation AplParamCopySelectMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_COPY_SELECT_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COPY_SELECT_MENU_SLOT1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COPY_SELECT_MENU_SLOT2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COPY_SELECT_MENU_ALL
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamCopySelectMenu].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COPY_SELECT_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamCopySelectMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COPY_SELECT_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamCopySelectMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_COPY_SELECT_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK519::AplParamCopyAllMenu_ViewType(int id) {
    //#[ operation AplParamCopyAllMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_COPY_ALL_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COPY_ALL_MENU_SLOT1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COPY_ALL_MENU_SLOT2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COPY_ALL_MENU_ALL
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamCopyAllMenu].mState;
    // ---------------------------------------------------------
    
    // VUP/機種差分で非表示とする処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COPY_ALL_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamCopyAllMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COPY_ALL_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamCopyAllMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_COPY_ALL_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}
