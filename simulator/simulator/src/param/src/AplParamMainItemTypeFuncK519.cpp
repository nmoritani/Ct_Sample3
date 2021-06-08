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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    //���f��������
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
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // SEEK POS SEL ==============================
    // �AFILE FORMAT [P2]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_PLAYBACK_MENU_SEEK_POS_SEL]	= AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_PLAYBACK_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamPlayBackMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // �AFILE FORMAT [P2]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_PLAY_SLOT_MARKED]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_PLAY_SLOT_TEXT_MEMO]	= AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_PLAY_SLOT_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamPlaySlot, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // PROTECT ===================================
    // �@FILE FORMAT [P2]������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) == APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_CLIP_MENU_PROTECT]		= AplParamState_VisibleInvalid;
    }
    
    // COPY ======================================
    // �@FILE FORMAT [MOV]������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) == APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY]			= AplParamState_VisibleInvalid;
    }
    
    // REPAIR ====================================
    // RE-CONNECT ================================
    // �AFILE FORMAT [P2]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_CLIP_MENU_REPAIR]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_CLIP_MENU_RE_CONNECT]	= AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_CLIP_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamClipMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // INDICATOR =================================
    // TEXT MEMO IND. ============================
    // �AFILE FORMAT [P2]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_THUMB_DISPLAY_MENU_INDICATOR]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_THUMB_DISPLAY_MENU_TEXT_MEMO_IND]	= AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_THUMB_DISPLAY_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamThumbDisplayMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // CH3 LEVEL CONTROL ===============================
    // �@CH3 LEVEL [AUTO]������
    if ( APL_PARAM_GET_DATA( AplParamCh3Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3_LEVEL_CONTROL] = AplParamState_VisibleInvalid;
    }
    
    // CH4 LEVEL CONTROL ===============================
    // �@CH4 LEVEL [AUTO]������
    if ( APL_PARAM_GET_DATA( AplParamCh4Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4_LEVEL_CONTROL] = AplParamState_VisibleInvalid;
    }
    
    // CH1 LIMITER ===============================
    // �@CH1 LEVEL [AUTO]������
    if ( APL_PARAM_GET_DATA( AplParamCh1Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH1_LIMITER] = AplParamState_VisibleInvalid;
    }
    
    // CH2 LIMITER ===============================
    // �@CH2 LEVEL [AUTO]������
    if ( APL_PARAM_GET_DATA( AplParamCh2Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH2LIMITER] = AplParamState_VisibleInvalid;
    }
    
    // CH3 LIMITER ===============================
    // �@CH3 LEVEL [AUTO]������
    if ( APL_PARAM_GET_DATA( AplParamCh3Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH3LIMITER] = AplParamState_VisibleInvalid;
    }
    
    // CH4 LIMITER ===============================
    // �@CH4 LEVEL [AUTO]������
    if ( APL_PARAM_GET_DATA( AplParamCh4Adjust ) == APL_SYS_PARAM_CH_ADJUST_AUTO )
    {
    	Exclusion[APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_CH4LIMITER] = AplParamState_VisibleInvalid;
    }
    
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_AUDIO_CH_SETTINGS_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamAudioChSettingsMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // SDI OUT ===================================
    // �@VIDEO OUT SEL [AV + HDMI]������
    if ( APL_PARAM_GET_DATA( AplParamOutputSelect ) == APL_SYS_PARAM_OUTPUT_SELECT_HDMI_AV )
    {
    	Exclusion[APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_SDI_OUT]	= AplParamState_VisibleInvalid;
    }
    
    // AV OUT ====================================
    // �@VIDEO OUT SEL [SDI + HDMI]������
    if ( APL_PARAM_GET_DATA( AplParamOutputSelect ) == APL_SYS_PARAM_OUTPUT_SELECT_SDI_HDMI )
    {
    	Exclusion[APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_AV_OUT]	= AplParamState_VisibleInvalid;
    }
    
    // HDR ===================================
    // �@[720x480/576i] �� �����iSDR�Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_HDR]	= AplParamState_VisibleInvalid;
    }
    
    // SD DOWNCON MODE ===========================
    // �@REC FORMAT [720x480/576i]������
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_VIDEO_OUT_LCD_VF_MENU_SD_DOWNCON_MODE]	= AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // OUT FORMAT ================================
    // AVS�֐ݒ肷��v���p�e�B���擾
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    // UHD(3840�~2160)
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
    // (720�~480)
    else if ( ( VideoProperty.Width == 720 && VideoProperty.Height == 480 )||
    		  ( VideoProperty.Width == 720 && VideoProperty.Height == 576 ) )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_OUT_FORMAT]	= AplParamState_VisibleInvalid;
    }
#endif
    
    // 3G-SDI OUT ================================
    // �@SDI OUT - OUT FORMAT [1920x1080p]�ȊO�� ����
    if ( APL_PARAM_GET_DATA( AplParamSdiOutFormat ) != APL_SYS_PARAM_SDI_FORMAT_1920_1080P )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_3G6GSDI_OUT]	= AplParamState_VisibleInvalid;
    }
    // �AREC FORMAT [2160-59.94p],[2160-50.00p],[1080-59.94p],[1080-50.00p]�ȊO�� ����
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
    // �@SDI OUT - OUT FORMAT [720x480/576i]�ȊO�� ����
    if ( APL_PARAM_GET_DATA( AplParamSdiOutFormat ) != APL_SYS_PARAM_SDI_FORMAT_720_480I &&
    	 APL_PARAM_GET_DATA( AplParamSdiOutFormat ) != APL_SYS_PARAM_SDI_FORMAT_720_576I )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_SD_SDI_EDH]	= AplParamState_VisibleInvalid;
    }
    
    // SDI REC REMOTE ============================
    // �@REC MODE [INTERVAL] / [ONE SHOT] ������
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_SDI_REC_REMOTE]= AplParamState_VisibleInvalid;
    }
    
    // SDI OUT ZEBRA ============================
    // �@[GAMMA MODE SEL]=[HLG]�������iOFF �Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_SDI_OUT_ZEBRA]= AplParamState_VisibleInvalid;
    }
    
    // HDR ================================
    // �@[720x480/576i] �� �����iSDR�Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_HDR] = AplParamState_VisibleInvalid;
    }
    // �A[720x480/576i] �� �����iSDR�Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSdiOutFormat ) == APL_SYS_PARAM_SDI_FORMAT_720_480I ||
    	 APL_PARAM_GET_DATA( AplParamSdiOutFormat ) == APL_SYS_PARAM_SDI_FORMAT_720_576I )
    {
    	Exclusion[APL_SYS_PARAM_SDI_OUT_MENU_HDR] = AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SDI_OUT_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamSdiOutMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // UHD(3840�~2160)
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
    // FHD(1920�~1080)
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
    // HD(1280�~720)
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamSdiOutFormat, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // OUT FORMAT ===========================
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    // FHD(1920�~1080)
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
    // HD(1280�~720)
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
    // �@REC MODE [INTERVAL] / [ONE SHOT]�� ����
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_REC_REMOTE]= AplParamState_VisibleInvalid;
    }
    // �AHDMI TC OUT [ON]�ȊO�� ����
    if ( APL_PARAM_GET_DATA( AplParamHdmiTcOutput ) != APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_REC_REMOTE]= AplParamState_VisibleInvalid;
    }
    
    // HDMI OUT ZEBRA ============================
    // �@[GAMMA MODE SEL]=[HLG]�������iOFF �Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_OUT_ZEBRA]= AplParamState_VisibleInvalid;
    }
    
    // HDMI OUT HDR ===========================
    // �@[720x480/576i] �� �����iSDR�Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDR] = AplParamState_VisibleInvalid;
    }
    // �A[720x480/576p] �� �����iSDR�Œ�j
    if ( APL_PARAM_GET_DATA( AplParamHdmiOutFormat ) == APL_SYS_PARAM_HDMI_FORMAT_720_480P ||
    	 APL_PARAM_GET_DATA( AplParamHdmiOutFormat ) == APL_SYS_PARAM_HDMI_FORMAT_720_576P )
    {
    	Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_HDR] = AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HDMI_OUT_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamHdmiOutMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // AVS�֐ݒ肷��v���p�e�B���擾
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    
    // Bug4883
    // UHD(3840�~2160)
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
    // FHD(1920�~1080)
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
    // HD(1280�~720)
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
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamHdmiOutFormat, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // SAFETY AREA ===============================
    // �@SAFETY MARKER [OFF]�� ����
    if ( APL_PARAM_GET_DATA( AplParamLcdMarkerSaftyMarkerType ) == APL_SYS_PARAM_SAFETY_MARKER_TYPE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_MARKER_MENU_SAFETY_AREA] = AplParamState_VisibleInvalid;
    }
    
    // FRAME MARKER ==============================
    // �@REC FORMAT [480i/576i],���� ASPECT [4:3] ������
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA &&
    	 APL_PARAM_GET_DATA( AplParamAspectCombert ) == APL_SYS_PARAM_ASPECT_COMBERT_SIDE_CROP )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_MARKER_MENU_FRAME_MARKER]= AplParamState_VisibleInvalid;
    }
    
    
    // FRAME COLOR ===============================
    // �@FRAME MARKER [OFF]�� ����
    if ( APL_PARAM_GET_DATA( AplParamLcdMarkerFrameMarker ) == APL_SYS_PARAM_FRAMEMARKER_OFF )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_MARKER_MENU_FRAME_COLOR] = AplParamState_VisibleInvalid;
    }
    
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // ZEBRA =====================================
    // ZEBRA1 DETECT =====================================
    // ZEBRA2 DETECT =====================================
    // ZEBRA2 =====================================
    // �@COLOR BAR�o�͒� ����
    if ( APL_PARAM_GET_DATA( AplParamColorBar ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA1_DETECT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2_DETECT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2] = AplParamState_VisibleInvalid;
    }
    
    // �A[GAMMA MODE SEL]=[HLG]�������iOFF �Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA1_DETECT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2_DETECT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_LCD_VF_EI_ASSIST_MENU_ZEBRA2] = AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    
    // CLIP NAME =================================
    // �@FILE FORMAT [MOV]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_CLIP_NAME]		= AplParamState_VisibleInvalid;
    }
    
    // FILE SPLIT ===============================
    // �AFILE FORMAT [P2]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_FILE_SPLIT]	= AplParamState_VisibleInvalid;
    }
    
    // 2 SLOTS FUNC. =============================
    // �@VFR SW [OFF]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_2SLOT_FUNC]		= AplParamState_VisibleInvalid;
    }
    // �APROXY REC MODE [MAIN & SUB]������
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) == APL_SYS_PARAM_PROXY_REC_MODE_P2_SD )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_2SLOT_FUNC]		= AplParamState_VisibleInvalid;
    }
    
    // PRE REC ===================================
    // �@VFR SW [OFF]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_PRE_REC]			= AplParamState_VisibleInvalid;
    }
    // �AREC MODE [NORMAL] �ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) != APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_PRE_REC]	= AplParamState_VisibleInvalid;
    }
    // �B2 SLOTS FUNC. [BACKGR REC] ������
    if ( APL_PARAM_GET_DATA( AplParamRelayBackup ) == APL_SYS_PARAM_RELAY_BACKUP_BACKUP )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_PRE_REC]	= AplParamState_VisibleInvalid;
    }
    // �CNETWORK FUNC [NDI|HX] ���F����
    if ( APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_PRE_REC]	= AplParamState_VisibleInvalid;
    }
    
    // TIME STAMP ================================
    // �@PROXY REC MODE [OFF]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) != APL_SYS_PARAM_PROXY_REC_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP]		= AplParamState_VisibleInvalid;
    }
    // �ANETWORK FUNC [STREAMING]/[NDI|HX] ���F����
    if ( APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_STREAMING ||
    	 APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP]		= AplParamState_VisibleInvalid;
    }
    // �BVFR SW [OFF]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP]		= AplParamState_VisibleInvalid;
    }
    // �CREC FORMAT [480i/576i]������
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) == APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_TIME_STAMP]		= AplParamState_VisibleInvalid;
    }
    
    // REC META DATA =============================
    // �AFILE FORMAT [P2]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_RECORDING_MENU_REC_MEDIA_DATA]	= AplParamState_VisibleInvalid;
    }
    
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_RECORDING_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecordingMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // �BPROXY REC MODE [OFF]�ȊO�� [ONE FILE] �I��s�i [SPLIT] �Ɋۂ߂�j
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) != APL_SYS_PARAM_PROXY_REC_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_FILE_SPLIT_ONE_FILE]	= AplParamState_VisibleInvalid;
    }
    // �C2 SLOTS FUNC. [BACKGR REC]�� [SHORT SPLIT] �I��s�i [SPLIT] �Ɋۂ߂�j
    if ( APL_PARAM_GET_DATA( AplParamRelayBackup ) == APL_SYS_PARAM_RELAY_BACKUP_BACKUP )
    {
    	Exclusion[APL_SYS_PARAM_FILE_SPLIT_SHORT_SPLIT]	= AplParamState_VisibleInvalid;
    }
    // �DREC MODE [NORMAL]�ȊO�� [SHORT SPLIT] �I��s�i [SPLIT] �Ɋۂ߂�j
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) != APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL )
    {
    	Exclusion[APL_SYS_PARAM_FILE_SPLIT_SHORT_SPLIT]	= AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // �APROXY REC MODE [OFF]�ȊO�� [BACKGR REC] �I��s�iOFF �Ɋۂ߂�j
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) != APL_SYS_PARAM_PROXY_REC_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
    // �BSTREAMING/NDI|HX ���F [BACKGR REC] �I��s�iOFF �Ɋۂ߂�j
    if ( APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_STREAMING ||
    	 APL_PARAM_GET_DATA( AplParamNetworkFunc ) == APL_SYS_PARAM_NETWORK_FUNC_NDI_HX )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
    // �CREC MODE [INTERVAL] / [ONE SHOT]�� [RELAY REC] �� [BACKGR REC] �I��s�iOFF �Ɋۂ߂�j
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
    // TODO 2018/07/19 MIZUTA
    // �d�l�s��
    // �DREC MODE [LOOP]�� (T.B.D)
    //if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP )
    //{
    //}
    // �EFILE FORMAT [AVCHD]�� [BACKGR REC] �I��s�iOFF �Ɋۂ߂�j
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) == APL_SYS_PARAM_REC_FORMAT_AVCHD )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
#if 0
    // �FREC FORMAT [FHD] �ȊO�� [BACKGR REC] �I��s�iOFF �Ɋۂ߂�j
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    if ( !( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 ) )
    {
    	Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP]	= AplParamState_VisibleInvalid;
    }
#endif
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_RELAY_BACKUP_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRelayBackup, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // REC MODE ==================================
    // �AVFR SW [OFF]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_REC_FUNCTION_MENU_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // �CFILE FORMAT [AVCHD]������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) == APL_SYS_PARAM_REC_FORMAT_AVCHD )
    {
    	Exclusion[APL_SYS_PARAM_REC_FUNCTION_MENU_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FUNCTION_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecFunctionMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // UB PRESET =================================
    // �@UB MODE [USER]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamUsersBitMode ) != APL_SYS_PARAM_UB_MODE_USER )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_SET_UB]		= AplParamState_VisibleInvalid;
    }
    
    // FREE/REC RUN ==============================
    // �@PRE REC [OFF]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamPreRec ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN]	= AplParamState_VisibleInvalid;
    }
    // �AREC MODE [INTERVAL] / [ONE SHOT] ������
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN]	= AplParamState_VisibleInvalid;
    }
    // �B2 SLOTS FUNC. [BACKGR REC] ������
    if ( APL_PARAM_GET_DATA( AplParamRelayBackup ) == APL_SYS_PARAM_RELAY_BACKUP_BACKUP )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN]	= AplParamState_VisibleInvalid;
    }
    // �CVFR SW [OFF]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_FREE_REC_RUN]	= AplParamState_VisibleInvalid;
    }
#if 0
    // DF/NDF ====================================
    // �@REC FORMAT [29.97p]/[59.94p]/[59.94i] �ȊO������
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
    // �AREC MODE [INTERVAL] / [ONE SHOT] ������
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ||
    	 APL_PARAM_GET_DATA( AplParamRecFunctionMode ) == APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT )
    {
    	Exclusion[APL_SYS_PARAM_TCUB_MENU_DF_NDF]		= AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_TCUB_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamTCUBMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // �@FILE FORMAT [MOV]�ȊO�� [CLIP NAME]�͑I��s��
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_UB_MODE_CLIP_NAME]	= AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
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
    // �BFILE FORMAT [P2]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_P2 )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // �CREC FORMAT [AVC-Intra200]������
    switch ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) )
    {
    	case APL_SYS_PARAM_RECMODE_P2_I200_FHD_60I:
    	case APL_SYS_PARAM_RECMODE_P2_I200_HD_60P:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]	= AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    // �DVFR SW [OFF]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // �EREC MODE [NORMAL]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) != APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // �FFILE APLIT [ONE FILE]������
    if ( APL_PARAM_GET_DATA( AplParamFileSplit ) == APL_SYS_PARAM_FILE_SPLIT_ONE_FILE )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_MODE]		= AplParamState_VisibleInvalid;
    }
    // PROXY REC FORMAT ==========================
    // �BPROXY REC MODE [OFF]������
    if ( APL_PARAM_GET_DATA( AplParamProxyRecMode ) == APL_SYS_PARAM_PROXY_REC_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_PROXY_REC_FORMAT]	= AplParamState_VisibleInvalid;
    }
    // ASPECT ====================================
    // �@REC FORMAT [480i/576i]�ȊO������
    if ( APL_PARAM_GET_DATA( AplParamSystemRecMode ) != APL_SYS_PARAM_RECMODE_AVCHD_SA )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_ASPECT]				= AplParamState_VisibleInvalid;
    }
    
    // SUPER SLOW ============================
    // �@FILE FORMAT [MOV] �ȊO���F����
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_SUPER_SLOW]			= AplParamState_VisibleInvalid;
    }
    // �AREC FORMAT [1920�~1080] �ȊO���F����
#if 0
    if ( !( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 ) )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_SUPER_SLOW]			= AplParamState_VisibleInvalid;
    }
    // �AREC FORMAT [59.94i/50.00i] ���F����
    if ( VideoProperty.FrameRate == AVS_FRAME_RATE_60_I )
    {
    	Exclusion[APL_SYS_PARAM_SYSTEM_MENU_SUPER_SLOW]			= AplParamState_VisibleInvalid;
    }
#endif
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamSystemMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // AVS�֐ݒ肷��v���p�e�B���擾
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    
    // �CREC FORMAT [1920�~1080_59.94/50p]��[AVC-G6] �̂ݗL��
    if ( VideoProperty.Width == 1920 && VideoProperty.Height == 1080 && VideoProperty.FrameRate == AVS_FRAME_RATE_60_P )
    {
    	Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_LOW_2CH_MOV]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_HQ_2CH_MOV]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_SHQ_2CH_MOV]	= AplParamState_VisibleInvalid;
    }
#endif
    // �CREC FORMAT [AVC-Intra50]��[AVC-G6] �I��s�iHQ �Ɋۂ߂�j
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
    // �CREC FORMAT [1280�~720_59.94/50p] ��[LOW]    �I��s�iHQ �Ɋۂ߂�j
    if ( VideoProperty.Width == 1280 && VideoProperty.Height == 720 && VideoProperty.FrameRate == AVS_FRAME_RATE_60_P )
    {
    	Exclusion[APL_SYS_PARAM_PROXY_REC_FORMAT_LOW_2CH_MOV]	= AplParamState_VisibleInvalid;
    }
#endif
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FORMAT_59HZ_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecFormat59Hz, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FORMAT_50HZ_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecFormat50Hz, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton1, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton2, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton3, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton4, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton5, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton6, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton7, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton8, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton9, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton10, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton11, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_BUTTON_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamUserButton12, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FILE_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamFileMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // MASTER GAMMA ===================================
    // [GAMMA MODE SEL]=[HLG]���̓O���[�A�E�g
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_MASTER_GAMMA]		= AplParamState_VisibleInvalid;
    }
    
    // F-REC DYNAMIC LVL ===================================
    // F-REC BLACK STR LVL ===================================
    // [FILM-REC]���ȊO�̓O���[�A�E�g
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) != APL_SYS_PARAM_GAMMA_MODE_SEL_FILM_REC )
    {
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_F_REC_DYNAMIC]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_F_REC_BLACK]			= AplParamState_VisibleInvalid;
    }
    
    // V-REC KNEE SLOPE ===================================
    // V-REC KNEE POINT ===================================
    // [VIDEO-REC]���ȊO�̓O���[�A�E�g
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) != APL_SYS_PARAM_GAMMA_MODE_SEL_VIDEO_REC )
    {
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_V_REC_KNEE_SLOPE]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_GAMMA_SETTING_MENU_V_REC_KNEE_POINT]	= AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // KNEE MODE ===================================
    // A.KNEE RESPONSE ===================================
    // KNEE POINT ===================================
    // KNEE SLOPE ===================================
    // [GAMMA MODE SEL]=[HLG]���̓O���[�A�E�g
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
    // [GAMMA MODE SEL]=�uHLG�v���̂ݗL��
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) != APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_SW]		= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_POINT]	= AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_KNEE_SETTING_MENU_HLG_KNEE_SLOPE]	= AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �@�\�Ŗ����\���Ƃ��鏈�� ==================
    // VFR ===================================
    // FILE FORMAT �@ [MOV] �ȊO���F�����iOFF�Œ�j
    if ( APL_PARAM_GET_DATA( AplParamRecFormat ) != APL_SYS_PARAM_REC_FORMAT_MOV )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_VFR]			= AplParamState_VisibleInvalid;
    }
#if 0
    AplIfAvs::AvsIfVideoProperty VideoProperty;
    memset( &VideoProperty, 0, sizeof( VideoProperty ) );
    AplIfAvs::GetVideoProperty( APL_PARAM()->convAvsVideoMode((APL_SYS_PARAM_RECMODE)(APL_PARAM_GET_DATA(AplParamSystemRecMode))), VideoProperty );
    // REC FORMAT �A [59.94i/50.00i] ���F�����iOFF�Œ�j
    if ( VideoProperty.FrameRate == AVS_FRAME_RATE_60_I )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_VFR]			= AplParamState_VisibleInvalid;
    }
#endif
    // �B[SUPER SLOW] �� [ON] �� �F �����iON�Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSuperSlowRec ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_VFR]			= AplParamState_VisibleInvalid;
    }
    
    // FRAME RATE ===================================
    //�@ [OFF] �� �F �����i�O���[�A�E�g�j
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_FRAME_RATE]		= AplParamState_VisibleInvalid;
    }
    //  [SUPER SLOW] �� [ON] �� �F ����
    if ( APL_PARAM_GET_DATA( AplParamSuperSlowRec ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_FRAME_RATE]		= AplParamState_VisibleInvalid;
    }
    
    
    // WHITE CLIP ===================================
    // WHITE CLIP LEVEL ===================================
    // [GAMMA MODE SEL]=[HLG]���̓O���[�A�E�g
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_SCENE_FILE_MENU_WHITE_CLIP]		= AplParamState_VisibleInvalid;
    }
    
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    		// 1080�A720�͔r������
    		break;
    	default:
    		// UHD�͔r��
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
    
    // WLAN�ALAN�̐ڑ����
    switch ( APL_PARAM_GET_DATA( AplParamWLanStatus ) ) {
    case APL_SYS_PARAM_WLAN_DISCONNECT:
    case APL_SYS_PARAM_WLAN_LAN_DISCONNECT:
    case APL_SYS_PARAM_WLAN_DISABLE:
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_START] = AplParamState_VisibleInvalid;
    	break;
    default:
    	break;
    }
    
    // STREAMING�ݒ�t�@�C���̕ۑ����
    if ( APL_PARAM_GET_DATA( AplParamSavedStreamingData ) == APL_SYS_PARAM_SWITCH_OFF ) {
    	Exclusion[APL_SYS_PARAM_STREAMING_MENU_CLEAR_MEM] = AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_STREAMING_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamStreamingMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_DEVICE_SEL_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamNetworkDeviceSel, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_FUNC_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamNetworkFunc, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamNetworkMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_STREAMING_DATA_TYPE_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamStreamingDataType, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NET_INFORMATION_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamNetInformationMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FTP_CLIENT_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamFTPClientMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    				
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_CELLULAR_PROPERTY_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamCellularPropertyMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_IP_REMOTE_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamIpRemoteMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // �@[GAMMA MODE SEL]=[HLG]�������iOFF �Œ�j
    if ( APL_PARAM_GET_DATA( AplParamSceneGammaModeSel ) == APL_SYS_PARAM_GAMMA_MODE_SEL_HLG )
    {
    	Exclusion[APL_SYS_PARAM_AV_OUT_MENU_ZEBRA]= AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // �@ [TIME STAMP] �� [OFF] �ȊO���F�����iOFF �Œ�j
    if ( APL_PARAM_GET_DATA( AplParamTimeStamp ) != APL_SYS_PARAM_TIMESTAMP_OFF )
    {
    	Exclusion[APL_SYS_PARAM_INDICATOR_MENU_DATETIME] = AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_INDICATOR_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamIndicatorMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_FUNCTION_MODE_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamRecFunctionMode, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // �@ [O.I.S.] �� [OFF] ���F�����i�O���[�A�E�g�j
    if ( APL_PARAM_GET_DATA( AplParamOisMode ) == APL_SYS_PARAM_OIS_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_HYBRID_OIS]= AplParamState_VisibleInvalid;
    }
    // �A [SUPER SLOW] �� [ON] ���F�����i�O���[�A�E�g�j
    if ( APL_PARAM_GET_DATA( AplParamSuperSlowRec ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_HYBRID_OIS]= AplParamState_VisibleInvalid;
    }
    // �B [VFR] �� [ON] ���F�����i�O���[�A�E�g�j
    if ( APL_PARAM_GET_DATA( AplParamSceneVFRMode ) != APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_HYBRID_OIS]= AplParamState_VisibleInvalid;
    }
    
    // O.I.S. MODE ================================
    // �@ [O.I.S.] �� [OFF] ���F�����i�O���[�A�E�g�j
    if ( APL_PARAM_GET_DATA( AplParamOisMode ) == APL_SYS_PARAM_OIS_MODE_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_OIS_MODE]= AplParamState_VisibleInvalid;
    }
    
    // W.BAL VAR ================================
    // �@ [W.BAL PRESET] ���@[5600K]�@or�@[3200K]�@�ݒ莞�@�F�����i�O���[�A�E�g�j
    if ( APL_PARAM_GET_DATA( AplParamWhiteBalancePreSetMode ) == APL_SYS_PARAM_WB_PRE_SET_MODE_3200K ||
    	 APL_PARAM_GET_DATA( AplParamWhiteBalancePreSetMode ) == APL_SYS_PARAM_WB_PRE_SET_MODE_5600K )
    {
    	Exclusion[APL_SYS_PARAM_SWMODE_MENU_WBAL_VAR]= AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SWMODE_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamSwModeMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �{�̕i��AG-CX350 AREA2��LANGUAGE��\��
    char model[AplParamInfoModel_Size] = {0};
    APL_PARAM_GET_DATA_AREA(AplParamInfoModel,(UB*)model,AplParamInfoModel_Size);
    if( strncmp(model,"AG-CX350",AplParamInfoModel_Size) == 0 && APL_PARAM_GET_DATA( AplParamUSeAreaSettings ) == APL_SYS_PARAM_USE_AREA_2 )
    {
    	Exclusion[APL_SYS_PARAM_OTHERS_MENU_LANGUAGE] = AplParamState_Invisible;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // �D[WIRELESS PROPERTY]-[TYPE]��[DIRECT]�ȊO�I�����A�O���[�A�E�g
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) != APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_BAND]= AplParamState_VisibleInvalid;
    }
    
    // CHANNEL(2.4GHz) ================================
    // �D[WIRELESS PROPERTY]-[TYPE]��[DIRECT]�ȊO�I�����A�O���[�A�E�g
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) != APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_CHANNEL_24GHZ]= AplParamState_VisibleInvalid;
    }
    
    // CHANNEL(5GHz) ================================
    // �D[WIRELESS PROPERTY]-[TYPE]��[DIRECT]�ȊO�I�����A�O���[�A�E�g
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) != APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_CHANNEL_5GHZ]= AplParamState_VisibleInvalid;
    }
    
    // ENCRYPTION ================================
    // �D[WIRELESS PROPERTY]-[TYPE]��[DIRECT]�I�����A[WPA2-AES]�Œ�i�O���[�j
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) == APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_ENCRYPTION]= AplParamState_VisibleInvalid;
    }
    
    // ENCRYPT KEY ================================
    // �HENCRYPTION��NONE�Ȃ�O���[�A�E�g�@�l�͕ێ�
    if ( APL_PARAM_GET_DATA( AplParamEncryption ) == APL_NET_PARAM_SECURITY_TYPE_NONE )
    {
    	Exclusion[APL_SYS_PARAM_WLAN_PROPERTY_MENU_ENCRYPT_KEY] = AplParamState_VisibleInvalid;
    }
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_WLAN_PROPERTY_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamWlanPropertyMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_NET_PARAM_DHCP_MODE_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamLanDhcpModeV6, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_HP_OUT_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamHpOut, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    	
    		// DNS��DHCP�Ŋ����Ă�ꂽ��O���[�A�E�g
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
    
    // �r������ ==================
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
     
    // �������K�v��AplParamID ----------------------------------
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
    
    	// DNS��DHCP�Ŋ����Ă�ꂽ��O���[�A�E�g
    	if ( APL_PARAM_GET_DATA( AplParamDnsPrimaryUpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    		Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_PRIMARY_DNS] = AplParamState_VisibleInvalid;
    	}
    	
    	if ( APL_PARAM_GET_DATA( AplParamDnsSecondaryUpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    		Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_SECONDARY_DNS] = AplParamState_VisibleInvalid;
    	}
    }
    
    // �r������ ==================
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
     
    // �������K�v��AplParamID ----------------------------------
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
    
    	// DNS��DHCP�Ŋ����Ă�ꂽ��O���[�A�E�g
    	if ( APL_PARAM_GET_DATA( AplParamLanDnsPrimaryUpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    		Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_PRIMARY_DNS] = AplParamState_VisibleInvalid;
    	}
    	
    	if ( APL_PARAM_GET_DATA( AplParamLanDnsSecondaryUpdateDhcp ) == APL_SYS_PARAM_SWITCH_ON ) {
    		Exclusion[APL_SYS_PARAM_IPV4_SET_MENU_SECONDARY_DNS] = AplParamState_VisibleInvalid;
    	}
    }
    
    // �r������ ==================
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
    				
    
    // �������K�v��AplParamID ----------------------------------
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
    		// 720��VUP���r���͖���
    		break;
    	default:
    		// UHD�͔r��
    		Exclusion[APL_SYS_PARAM_NDI_HX_MENU_STREAM_FORMAT] = AplParamState_VisibleInvalid;
    		break;	
    	}
    }
#endif
    if ( APL_PARAM_GET_DATA( AplParamNdiHxActivation ) == APL_SYS_PARAM_SWITCH_OFF ) {
    	Exclusion[APL_SYS_PARAM_NDI_HX_MENU_STREAM_FORMAT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_NDI_HX_MENU_CLEAR_ACTIVATION] = AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // [DIRECT]�I�����ACLIENT�O���[�A�E�g
    if ( APL_PARAM_GET_DATA( AplParamWlanMode ) == APL_NET_PARAM_WLAN_MODE_DIRECT )
    {
    	Exclusion[APL_NET_PARAM_DHCP_MODE_CLIENT] = AplParamState_VisibleInvalid;
    }
    else
    {
    //  [DIRECT]�ȊO�I�����ASERVER�O���[�A�E�g
    	Exclusion[APL_NET_PARAM_DHCP_MODE_SERVER] = AplParamState_VisibleInvalid;
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COPY_SELECT_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamCopySelectMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
    
    // �������K�v��AplParamID ----------------------------------
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
    
    // VUP/�@�퍷���Ŕ�\���Ƃ��鏈�� ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COPY_ALL_MENU_MAX + 1 ; i++ ){
    	if ( AplParamMainValueCheck::AplParamItemState_Invisible == m_pValueCheck->valueCheck( AplParamCopyAllMenu, i ) ) {
    		Exclusion[i] = AplParamState_Invisible;
    	}
    }
    
    // �r������ ==================
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
