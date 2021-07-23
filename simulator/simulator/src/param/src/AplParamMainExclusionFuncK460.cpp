/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version: 7.5.1
 *  Element:          AplParamMainExclusionFuncK460
 */

#pragma warning (disable:4805)
#include "AplParamMainExclusionFuncK460.h"
#include "AplParamService.h"

#include <CtPlatforms.h>

//## package Foundation::Manager

//## class AplParamMainExclusionFuncK460
AplParamMainExclusionFuncK460::AplParamMainExclusionFuncK460() : m_IsExecuteIdMaxForHdmiFormat(false), m_IsExecuteIdMaxForSdiFormat(false) {
    //#[ operation AplParamMainExclusionFuncK460()
    //#]
}

AplParamMainExclusionFuncK460::~AplParamMainExclusionFuncK460() {
}

void AplParamMainExclusionFuncK460::AplParamBalanceLevel_Exclusion(int id) {
    //#[ operation AplParamBalanceLevel_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamLcdFocusExpandUserSw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamLcdFocusExpandUserSw
    switch( APL_PARAM_GET_DATA( AplParamLcdFocusExpandUserSw ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    /* LEVEL GAUGE動作不安定により、復帰処理を暫定コメントアウト
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamBalanceLevel) ] == true ){
    	APL_PARAM_SET_DATA( AplParamBalanceLevel, APL_PARAM_GET_MASTER_DATA(AplParamBalanceLevel) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamBalanceLevel )] == false ){
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamBalanceLevel, i );
    			}
    		}
    	}
    }
    */
    //#]
}

void AplParamMainExclusionFuncK460::AplParamColorBar_Exclusion(int id) {
    //#[ operation AplParamColorBar_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合は設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamColorBar) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamColorBar, APL_PARAM_GET_MASTER_DATA(AplParamColorBar) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamColorBar )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_DATA( AplParamColorBar, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamColorHdmiOut_Exclusion(int id) {
    //#[ operation AplParamColorHdmiOut_Exclusion(int)
    //SDI RAW [OFF] 以外時： 無効
    //COLOR SETTING MAIN [V-Log] 以外時： 選択不可（MAINと同じSCENE名表示）
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorMain	
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // COLOR SETTING MAIN と同期させる
    switch( APL_PARAM_GET_DATA(AplParamColorMain) ){
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		APL_PARAM_SET_CACHE_DATA( AplParamColorHdmiOut, APL_PARAM_GET_DATA(AplParamColorMain) );
    		break;
    	default:
    		APL_PARAM_SET_DATA( AplParamColorHdmiOut, APL_PARAM_GET_MASTER_DATA(AplParamColorHdmiOut) );
    		break;
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamColorLcdOut_Exclusion(int id) {
    //#[ operation AplParamColorLcdOut_Exclusion(int)
    //SDI RAW [OFF] 以外時： 無効
    //COLOR SETTING MAIN [V-Log] 以外時： 選択不可（MAINと同じSCENE名表示）
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorMain	
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // COLOR SETTING MAIN と同期させる
    switch( APL_PARAM_GET_DATA(AplParamColorMain) ){
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		APL_PARAM_SET_CACHE_DATA( AplParamColorLcdOut, APL_PARAM_GET_DATA(AplParamColorMain) );
    		break;
    	default:
    		APL_PARAM_SET_DATA( AplParamColorLcdOut, APL_PARAM_GET_MASTER_DATA(AplParamColorLcdOut) );
    		break;
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamColorMain_Exclusion(int id) {
    //#[ operation AplParamColorMain_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_COLOR_MAIN_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_COLOR_MAIN_VLOG
    	true,	// APL_SYS_PARAM_COLOR_MAIN_DUMMY
    	true,	// APL_SYS_PARAM_COLOR_MAIN_SCENE1
    	true,	// APL_SYS_PARAM_COLOR_MAIN_SCENE2
    	true,	// APL_SYS_PARAM_COLOR_MAIN_SCENE3
    	true,	// APL_SYS_PARAM_COLOR_MAIN_SCENE4
    	true,	// APL_SYS_PARAM_COLOR_MAIN_SCENE5
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_DUMMY] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE1] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE2] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE3] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE4] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE5] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_DUMMY] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE1] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE2] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE3] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE4] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE5] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_DUMMY] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE1] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE2] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE3] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE4] = false;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE5] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamColorMain) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamColorMain, APL_PARAM_GET_MASTER_DATA(AplParamColorMain) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamColorMain )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_COLOR_MAIN_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamColorMain, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamColorSdiOut_Exclusion(int id) {
    //#[ operation AplParamColorSdiOut_Exclusion(int)
    //SDI RAW [OFF] 以外時： 無効
    //COLOR SETTING MAIN [V-Log] 以外時： 選択不可（MAINと同じSCENE名表示）
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorMain	
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // COLOR SETTING MAIN と同期させる
    switch( APL_PARAM_GET_DATA(AplParamColorMain) ){
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		APL_PARAM_SET_CACHE_DATA( AplParamColorSdiOut, APL_PARAM_GET_DATA(AplParamColorMain) );
    		break;
    	default:
    		APL_PARAM_SET_DATA( AplParamColorSdiOut, APL_PARAM_GET_MASTER_DATA(AplParamColorSdiOut) );
    		break;
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamColorSub_Exclusion(int id) {
    //#[ operation AplParamColorSub_Exclusion(int)
    //SDI RAW [OFF] 以外時： 無効
    //SUB REC [OFF] 時： 無効
    //COLOR SETTING MAIN [V-Log] 以外時： 選択不可（MAINと同じSCENE名表示）
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorMain,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    if (   APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF &&
    	 ( APL_PARAM_GET_DATA( AplParamVup ) == APL_SYS_PARAM_VUP_NONE ||APL_PARAM_GET_DATA( AplParamVup ) == APL_SYS_PARAM_VUP_1ST ) )
    {
    	APL_PARAM_SET_CACHE_DATA( AplParamColorSub, APL_SYS_PARAM_COLOR_SUB_VLOG );
    }
    else
    {
    	// COLOR SETTING MAIN と同期させる
    	switch( APL_PARAM_GET_DATA(AplParamColorMain) ){
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_CACHE_DATA( AplParamColorSub, APL_PARAM_GET_DATA(AplParamColorMain) );
    			break;
    		default:
    			APL_PARAM_SET_DATA( AplParamColorSub, APL_PARAM_GET_MASTER_DATA(AplParamColorSub) );
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamDZoomUserSw_Exclusion(int id) {
    //#[ operation AplParamDZoomUserSw_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamSystemSensorMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSensorMode
    switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) ){
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合は設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamDZoomUserSw) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamDZoomUserSw, APL_PARAM_GET_MASTER_DATA(AplParamDZoomUserSw) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamDZoomUserSw )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_DATA( AplParamDZoomUserSw, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamEISSwitch_Exclusion(int id) {
    //#[ operation AplParamEISSwitch_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamSystemSensorMode,
    	AplParamDZoomUserSw,
    	AplParamOisMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSensorMode
    switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) ){
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamDZoomUserSw
    switch( APL_PARAM_GET_DATA( AplParamDZoomUserSw ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamOisMode
    switch( APL_PARAM_GET_DATA( AplParamOisMode ) ){
    	case APL_SYS_PARAM_OIS_MODE_OFF:
    		break;
    	case APL_SYS_PARAM_OIS_MODE_ACTIVE:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_OIS_MODE_STANDARD:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合は設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamEISSwitch) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamEISSwitch, APL_PARAM_GET_MASTER_DATA(AplParamEISSwitch) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamEISSwitch )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_DATA( AplParamEISSwitch, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamGainIsoDispChg_Exclusion(int id) {
    //#[ operation AplParamGainIsoDispChg_Exclusion(int)
    // SDI ROW 		[OFF] 以外時 無効（内部はISO）
    
    bool Exclusion[ APL_SYS_PARAM_GAIN_ISO_DISP_CHG_MAX + 1 ] = {
    	true,  // APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN
    	true, // APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // SDI ROW
    switch( APL_PARAM_GET_DATA(AplParamSystemSdiRaw) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[ APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN ] = false;
    		break;
    	default:
    		break;
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamGainIsoDispChg) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamGainIsoDispChg, APL_PARAM_GET_MASTER_DATA(AplParamGainIsoDispChg) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamGainIsoDispChg) ] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_GAIN_ISO_DISP_CHG_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamGainIsoDispChg, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamGainSelect_Exclusion(int id) {
    //#[ operation AplParamGainSelect_Exclusion(int)
    // 
    // [GAIN MODE]=NORMALの時：
    //　　0/2/4/6/8/10([GAMMA]≠VIDEO)
    //　　0/2/4/6/8/10/12/14/16([GAMMA]=VIDEO)
    // [GAIN MODE]=HIGHの時：
    //　　0/2/4/6/8/10/12([GAMMA]≠VIDEO)
    //　　0/2/4/6/8/10/12/14/16/18([GAMMA]=VIDEO)
    //
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamGainSelect,
    	AplParamGainSwitch,
    	AplParamSceneGammaSelect,
    	AplParamSystemSensorMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamGainSwitch or AplParamSceneGammaSelect or Max(起動時)は読み込み
    if( id == AplParamGainSwitch || id == AplParamSceneGammaSelect || id == AplParamIdMax || id == AplParamSystemSensorMode ){
    	switch( APL_PARAM_GET_DATA(AplParamGainSwitch)){
    		case APL_SYS_PARAM_GAIN_SWITCH_NORMAL:
    			// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParamGainSelect, APL_PARAM_GET_DATA( AplParamGainSelectNormalSensor2_2_K ) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParamGainSelect, APL_PARAM_GET_DATA( AplParamGainSelectNormalVideo ) );
    				}
    				else
    				{
    					APL_PARAM_SET_DATA( AplParamGainSelect, APL_PARAM_GET_DATA( AplParamGainSelectNormalNotVideo ) );
    				}
    			}
    			break;
    		case APL_SYS_PARAM_GAIN_SWITCH_HIGH:
    			// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParamGainSelect, APL_PARAM_GET_DATA( AplParamGainSelectHighSensor2_2_K ) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParamGainSelect, APL_PARAM_GET_DATA( AplParamGainSelectHighVideo ) );
    				}
    				else
    				{
    					APL_PARAM_SET_DATA( AplParamGainSelect, APL_PARAM_GET_DATA( AplParamGainSelectHighNotVideo ) );
    				}
    			}
    			break;
    		default:
    			break;
    	}
    }
    
    // GainSelect 書き込み先と排他切替
    if( id == AplParamGainSelect ){
    	switch( APL_PARAM_GET_DATA(AplParamGainSwitch)){
    		case APL_SYS_PARAM_GAIN_SWITCH_NORMAL:
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParamGainSelectNormalSensor2_2_K, APL_PARAM_GET_DATA( AplParamGainSelect ) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParamGainSelectNormalVideo, APL_PARAM_GET_DATA( AplParamGainSelect ) );
    				}
    				else
    				{
    					APL_PARAM_SET_DATA( AplParamGainSelectNormalNotVideo, APL_PARAM_GET_DATA( AplParamGainSelect ) );
    				}
    			}
    			break;
    		case APL_SYS_PARAM_GAIN_SWITCH_HIGH:
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) ==  APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParamGainSelectHighSensor2_2_K, APL_PARAM_GET_DATA( AplParamGainSelect ) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParamGainSelectHighVideo, APL_PARAM_GET_DATA( AplParamGainSelect ) );
    				}
    				else
    				{
    					APL_PARAM_SET_DATA( AplParamGainSelectHighNotVideo, APL_PARAM_GET_DATA( AplParamGainSelect ) );
    				}
    			}
    			break;
    		default:
    			break;
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamEncryption_Exclusion(int id) {
    //#[ operation AplParamEncryption_Exclusion(int)
    // 無線LANモード [DIRZECT]設定時 [WPA2-AES]固定
    
    bool Exclusion[ APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ] = {
    	true,	// APL_NET_PARAM_SECURITY_TYPE_NONE
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WEP
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WPA_TKIP
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WPA_AES
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WPA2_TKIP
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WPA2_AES
    	true,	// APL_NET_PARAM_SECURITY_TYPE_AUTO
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWlanMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WEP] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA_TKIP] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA_AES] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA2_TKIP] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_AUTO] = false;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_SELECT:
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_MANUAL:
    		break;
    	case APL_NET_PARAM_WLAN_MODE_NONE:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamEncryption) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamEncryption, APL_PARAM_GET_MASTER_DATA(AplParamEncryption) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamEncryption )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamEncryption, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamHdmiOutFormat_Exclusion(int id) {
    //#[ operation AplParamHdmiOutFormat_Exclusion(int)
    // [OFF] 以外時： 無効
    // 上記①以外は、FREQ, MAIN_PIXEL で決定される。
    //　　「C-K460出力フォーマット仕様書」を参照
    
    bool Exclusion[ APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_4096_2160P
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_3840_2160P
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_1920_1080P
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_1920_1080I
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_1280_720P
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_720_480P
    	true,	// APL_SYS_PARAM_HDMI_FORMAT_720_576P
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	//AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamSystemMainPixel,
    	AplParamSystemSdiRaw,
    	AplParamHdmiOutSignalSelect,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Bug4883
    // 起動時に最初にid=AplParamSystemMainPixelで来てしまうことにより
    // 周波数切替時の設定値が意図通りにならない対策
    if ( m_IsExecuteIdMaxForHdmiFormat == false && id != AplParamIdMax )
    {
    	return;
    }
    
    m_IsExecuteIdMaxForHdmiFormat = true;
    
    // AplParamSystemModeFrequency
    // AplParamSystemMainPixel
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;	// SDI RAWがOFF以外の時はこの処理の下でtrueにする
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			default:
    				break;
    		}
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			default:
    				break;
    		}
    		break;
    
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			default:
    				break;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    				break;
    
    			default:
    				break;
    		}
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P] = true;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P] = true;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P] = true;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P] = false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P] = false;
    		break;
    	default:
    		break;
    }
    
    // AplParamHdmiOutSignalSelect
    switch( APL_PARAM_GET_DATA( AplParamHdmiOutSignalSelect ) ){
    	case APL_SYS_PARAM_HDMI_SIGNAL_SEL_1080P:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= false;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= false;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamHdmiOutFormat) ] == true )	/* parasoft-suppress  BD-PB-ARRAY */
    {
    	APL_PARAM_SET_DATA( AplParamHdmiOutFormat, APL_PARAM_GET_MASTER_DATA(AplParamHdmiOutFormat) );
    	return;
    }
    
    // Bug4883
    if( Exclusion[APL_PARAM_GET_DATA( AplParamHdmiOutFormat )] == false )		/* parasoft-suppress  BD-PB-ARRAY */
    {
    	if ( AplParamIdMax == id )
    	{
    
    		if ( APL_PARAM_GET_DATA( AplParamHdmiOutFormat ) == APL_SYS_PARAM_HDMI_FORMAT_720_480P )
    		{
    			if ( Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P] == true )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamHdmiOutFormat, APL_SYS_PARAM_HDMI_FORMAT_720_576P );
    				return;
    			}
    			else if ( Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P] == true )
    			{
    				return;
    			}
    		}
    		else if ( APL_PARAM_GET_DATA( AplParamHdmiOutFormat ) == APL_SYS_PARAM_HDMI_FORMAT_720_576P )
    		{
    			if ( Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P] == true )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamHdmiOutFormat, APL_SYS_PARAM_HDMI_FORMAT_720_480P );
    				return;
    			}
    			else if ( Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P] == true )
    			{
    				return;
    			}
    		}
    
    		switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    		
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    			default:
    				if ( Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P] == true )
    				{
    					APL_PARAM_SET_CACHE_DATA( AplParamHdmiOutFormat, APL_SYS_PARAM_HDMI_FORMAT_1920_1080P );
    					return;
    				}
    				break;
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    				if ( Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I] == true )
    				{
    					APL_PARAM_SET_CACHE_DATA( AplParamHdmiOutFormat, APL_SYS_PARAM_HDMI_FORMAT_1920_1080I );
    					return;
    				}
    				break;
    		}
    	}
    
    	for( int i = 0 ; i < APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ; i++ ){
    		if( Exclusion[i] == true ){
    			APL_PARAM_SET_CACHE_DATA( AplParamHdmiOutFormat, i );
    			
    			switch ( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) )
    			{
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    				default:
    					if ( i == APL_SYS_PARAM_HDMI_FORMAT_1920_1080P )
    					{
    						return;
    					}
    					break;
    
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    					if ( i == APL_SYS_PARAM_HDMI_FORMAT_1920_1080I )
    					{
    						return;
    					}
    					break;
    			}
    			
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamHdmiOutMenuDisp_Exclusion(int id) {
    //#[ operation AplParamHdmiOutMenuDisp_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamPlayMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamPlayMode
    switch( APL_PARAM_GET_DATA( AplParamPlayMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamHdmiOutMenuDisp) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamHdmiOutMenuDisp, APL_PARAM_GET_MASTER_DATA(AplParamHdmiOutMenuDisp) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamHdmiOutMenuDisp )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamHdmiOutMenuDisp, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamHdmiTcOutput_Exclusion(int id) {
    //#[ operation AplParamHdmiTcOutput_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamHdmiOutSignalSelect,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    // AplParamHdmiOutSignalSelect
    switch( APL_PARAM_GET_DATA( AplParamHdmiOutSignalSelect ) ){
    	case APL_SYS_PARAM_HDMI_SIGNAL_SEL_1080P:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamHdmiTcOutput) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamHdmiTcOutput, APL_PARAM_GET_MASTER_DATA(AplParamHdmiTcOutput) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamHdmiTcOutput )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamHdmiTcOutput, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamLcdEIAssistSpotMeterDisp_Exclusion(int id) {
    //#[ operation AplParamLcdEIAssistSpotMeterDisp_Exclusion(int)
    // MAIN COLOR [V-Log] に設定されているときのみ有効。　上記以外はグレーで％固定
    
    bool Exclusion[ APL_SYS_PARAM_SPOT_MATER_DISP_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SPOT_MATER_DISP_STOP
    	true,	// APL_SYS_PARAM_SPOT_MATER_DISP_PERCENT
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorMain,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = false;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = false;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = false;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = false;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamLcdEIAssistSpotMeterDisp) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamLcdEIAssistSpotMeterDisp, APL_PARAM_GET_MASTER_DATA(AplParamLcdEIAssistSpotMeterDisp) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamLcdEIAssistSpotMeterDisp )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SPOT_MATER_DISP_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamLcdEIAssistSpotMeterDisp, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamLcdIndicatorRecFuncMode_Exclusion(int id) {
    //#[ operation AplParamLcdIndicatorRecFuncMode_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF ){
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamLcdIndicatorRecFuncMode) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamLcdIndicatorRecFuncMode, APL_PARAM_GET_MASTER_DATA(AplParamLcdIndicatorRecFuncMode) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamLcdIndicatorRecFuncMode )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamLcdIndicatorRecFuncMode, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamLcdMarkerUserSw_Exclusion(int id) {
    //#[ operation AplParamLcdMarkerUserSw_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamLcdFocusAssistUserSw,
    	AplParamLcdFocusExpandUserSw,
    	AplParamColorBar,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamLcdFocusAssistUserSw
    switch( APL_PARAM_GET_DATA( AplParamLcdFocusAssistUserSw ) ){
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_OFF:
    		break;
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_PEAKING:
    		break;
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_SQUERES:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamLcdFocusExpandUserSw
    switch( APL_PARAM_GET_DATA( AplParamLcdFocusExpandUserSw ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamColorBar
    switch( APL_PARAM_GET_DATA( AplParamColorBar ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamLcdMarkerUserSw) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamLcdMarkerUserSw, APL_PARAM_GET_MASTER_DATA(AplParamLcdMarkerUserSw) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamLcdMarkerUserSw )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamLcdMarkerUserSw, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamLimiterCH1_Exclusion(int id) {
    //#[ operation AplParamLimiterCH1_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true, // APL_SYS_PARAM_SWITCH_OFF
    	true, // APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamCh1Adjust,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamCh1Adjust
    switch( APL_PARAM_GET_DATA( AplParamCh1Adjust ) ){
    	case APL_SYS_PARAM_CH_ADJUST_MANUAL:
    		break;
    	case APL_SYS_PARAM_CH_ADJUST_AUTO:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamLimiterCH1) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamLimiterCH1, APL_PARAM_GET_MASTER_DATA(AplParamLimiterCH1) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamLimiterCH1 )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamLimiterCH1, i );
    			}
    		}
    	}
    }
    
    
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamLimiterCH2_Exclusion(int id) {
    //#[ operation AplParamLimiterCH2_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true, // APL_SYS_PARAM_SWITCH_OFF
    	true, // APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamCh2Adjust,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamCh1Adjust
    switch( APL_PARAM_GET_DATA( AplParamCh2Adjust ) ){
    	case APL_SYS_PARAM_CH_ADJUST_MANUAL:
    		break;
    	case APL_SYS_PARAM_CH_ADJUST_AUTO:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamLimiterCH2) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamLimiterCH2, APL_PARAM_GET_MASTER_DATA(AplParamLimiterCH2) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamLimiterCH2 )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamLimiterCH2, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamOutIndicatorRecFuncMode_Exclusion(int id) {
    //#[ operation AplParamOutIndicatorRecFuncMode_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVup,
    	AplParamGrade
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF ){
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamOutIndicatorRecFuncMode) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamOutIndicatorRecFuncMode, APL_PARAM_GET_MASTER_DATA(AplParamOutIndicatorRecFuncMode) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamOutIndicatorRecFuncMode )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamOutIndicatorRecFuncMode, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamPreRec_Exclusion(int id) {
    //#[ operation AplParamPreRec_Exclusion(int)
    // REC SETTINGS-PRE REC
    // VFR SW		[ON] 時、[OFF] 固定
    // 撮影モード	[NORMAL]設定以外、[OFF] 固定
    // 2SLOT機能 	[BACKGR REC] 時、[OFF] 固定
    // 詳細は「K460記録フォーマット仕様書」参照
    
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true, // APL_SYS_PARAM_SWITCH_OFF
    	true, // APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVFRMode,
    	AplParamRecFunctionMode,
    	AplParamRelayBackup,
    	AplParamSystemSdiRaw
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // VFR SW
    if(  APL_PARAM_GET_DATA( AplParamVFRMode ) == APL_SYS_PARAM_SWITCH_ON){
    	Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    }
    
    // 撮影モード
    switch( APL_PARAM_GET_DATA(AplParamRecFunctionMode) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	default:
    		Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    		break;
    }
    
    // 2SLOT機能
    switch( APL_PARAM_GET_DATA(AplParamRelayBackup) ){
    	case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:
    		Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    		break;
    	default:
    		break;
    }
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    		break;
    	default:
    		break;
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamPreRec) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamPreRec, APL_PARAM_GET_MASTER_DATA(AplParamPreRec) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamPreRec) ] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamPreRec, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamRecFunctionMode_Exclusion(int id) {
    //#[ operation AplParamRecFunctionMode_Exclusion(int)
    // REC SETTINGS-REC FUNCTION-REC MODE
    // VFR SW		[ON]時、[NORMAL] 固定
    // SUBREC   	[ON]時、[LOOP]選択不可
    // 2SLOT機能  	[SIMUL REC] 選択時、[LOOP]選択不可
    //  　　	    [BACKGR REC] 選択時、[LOOP] 選択不可
    // 詳細は「K460記録フォーマット仕様書」参照
    
    bool Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_MAX + 1 ] = {
    	true, // APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL
    	true, // APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL
    	true, // APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT
    	true, // APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVFRMode,
    	AplParamSystemSubRec,
    	AplParamRelayBackup,
    	AplParamSystemSdiRaw,
    	AplParamSystemMainCodec,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // VFR SW
    if(  APL_PARAM_GET_DATA( AplParamVFRMode ) == APL_SYS_PARAM_SWITCH_ON ){
    	Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    	Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT ] = false;
    	Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    }
    
    // SUB REC
    if( APL_PARAM_GET_DATA(AplParamSystemSubRec) != APL_SYS_PARAM_SYSTEM_SUB_REC_OFF ){
    	Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    	Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    }
    
    // 撮影モード
    switch( APL_PARAM_GET_DATA(AplParamRelayBackup) ){
    	case APL_SYS_PARAM_RELAY_BACKUP_RELAY:
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    		break;
    	default:
    		break;
    }
    
    // SYSTEM FREQUENCY
    switch ( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) )
    {
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    		break;
    	default:
    		break;
    }		
    
    // MAIN CODEC
    switch ( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    {
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS:
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH:
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA:
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM:
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    		break;
    	default:
    		break;
    }		
    
    // SDI RAW
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT ] = false;
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT ] = false;
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT ] = false;
    		Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    		break;
    	default:
    		break;
    }
    
    switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    	case APL_SYS_PARAM_VUP_NONE:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL ] = false;
    			Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT ] = false;
    			Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    		}
    		break;
    	case APL_SYS_PARAM_VUP_1ST:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT ] = false;
    			Exclusion[ APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP ] = false;
    		}
    		break;
    		break;
    	case APL_SYS_PARAM_VUP_2ND:
    		break;
    	case APL_SYS_PARAM_VUP_3RD:
    		break;
    	case APL_SYS_PARAM_VUP_4TH:
    		break;
    	case APL_SYS_PARAM_VUP_5TH:
    		break;
    	default:
    		break;
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamRecFunctionMode) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamRecFunctionMode, APL_PARAM_GET_MASTER_DATA(AplParamRecFunctionMode) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamRecFunctionMode) ] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_REC_FUNCTION_MODE_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamRecFunctionMode, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamRelayBackup_Exclusion(int id) {
    //#[ operation AplParamRelayBackup_Exclusion(int)
    // SUBREC     [ON] 時、[OFF] 固定
    // 撮影モード [INTERVAL] 時、[BACKGR REC] 選択不可
    //			  [ONESHOT] 時、[BACKGR REC] 選択不可
    //			  [LOOP] 時、[SIMUL REC]、[BACKGR REC]選択不可
    // VFR SW 	  [ON] 時、[BACKGR REC] 選択不可
    
    bool Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_MAX + 1 ] = {
    	true, // APL_SYS_PARAM_RELAY_BACKUP_OFF
    	true, // APL_SYS_PARAM_RELAY_BACKUP_RELAY
    	true, // APL_SYS_PARAM_RELAY_BACKUP_BACKUP
    	true, // APL_SYS_PARAM_RELAY_BACKUP_SIMUL
    	false // APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSubRec,
    	AplParamRecFunctionMode,
    	AplParamVFRMode,
    	AplParamSystemSdiRaw,
    	AplParamSystemSensorMode,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // SUB REC
    if( APL_PARAM_GET_DATA(AplParamSystemSubRec) != APL_SYS_PARAM_SYSTEM_SUB_REC_OFF ){
    	Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_RELAY ]	= false;
    	Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_BACKUP ]	= false;
    	Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_SIMUL ]	= false;
    }
    
    // 撮影モード
    switch( APL_PARAM_GET_DATA(AplParamRecFunctionMode) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_BACKUP ]	= false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_RELAY ]	= false;
    		Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_BACKUP ]	= false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_BACKUP ]	= false;
    		Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_SIMUL ]	= false;
    		break;
    	default:
    		break;
    }
    
    // VFR SW/SENSOR MODE
    switch( APL_PARAM_GET_DATA(AplParamSystemSensorMode) ){
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    		if(  APL_PARAM_GET_DATA( AplParamVFRMode ) == APL_SYS_PARAM_SWITCH_ON){
    			Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_BACKUP ] = false;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K:
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    		if(  APL_PARAM_GET_DATA( AplParamVFRMode ) == APL_SYS_PARAM_SWITCH_ON){
    			Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_RELAY ]	= false;
    			Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_BACKUP ]	= false;
    			Exclusion[ APL_SYS_PARAM_RELAY_BACKUP_SIMUL ]	= false;
    		}
    		break;
    	default:
    		break;
    }
    
    // SDI RAW
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = false;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = false;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = false;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = false;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = false;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = false;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = false;
    		break;
    	default:
    		break;
    }
    
    // AplParamVup
    switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    	case APL_SYS_PARAM_VUP_NONE:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			// 下記だけだとバックアップ記録でバージョンダウンするとサイマルになってしまうので 
    			Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = false;
    			
    			// バックアップ記録の場合はここで初期値にしておく
    			if ( APL_PARAM_GET_DATA(AplParamRelayBackup) == APL_SYS_PARAM_RELAY_BACKUP_BACKUP )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamRelayBackup, APL_SYS_PARAM_RELAY_BACKUP_RELAY );
    			}
    		}
    		break;
    	case APL_SYS_PARAM_VUP_1ST:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			// 下記だけだとバックアップ記録でバージョンダウンするとサイマルになってしまうので 
    			Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = false;
    			
    			// バックアップ記録の場合はここで初期値にしておく
    			if ( APL_PARAM_GET_DATA(AplParamRelayBackup) == APL_SYS_PARAM_RELAY_BACKUP_BACKUP )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamRelayBackup, APL_SYS_PARAM_RELAY_BACKUP_RELAY );
    			}
    		}
    		break;
    	case APL_SYS_PARAM_VUP_2ND:
    		break;
    	case APL_SYS_PARAM_VUP_3RD:
    		break;
    	case APL_SYS_PARAM_VUP_4TH:
    		break;
    	case APL_SYS_PARAM_VUP_5TH:
    		break;
    	default:
    		break;
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamRelayBackup) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamRelayBackup, APL_PARAM_GET_MASTER_DATA(AplParamRelayBackup) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamRelayBackup) ] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		// Relay > OFF > 左記以外の順
    		if ( Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] == true )
    		{
    			APL_PARAM_SET_CACHE_DATA( AplParamRelayBackup, APL_SYS_PARAM_RELAY_BACKUP_RELAY );
    		}
    		else if ( Exclusion[APL_SYS_PARAM_RELAY_BACKUP_OFF] == true )
    		{
    			APL_PARAM_SET_CACHE_DATA( AplParamRelayBackup, APL_SYS_PARAM_RELAY_BACKUP_OFF );
    		}
    		else
    		{
    			for( int i = 0 ; i < APL_SYS_PARAM_RELAY_BACKUP_MAX + 1 ; i++ ){
    				if( Exclusion[i] == true ){
    					APL_PARAM_SET_CACHE_DATA( AplParamRelayBackup, i );
    				}
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneBlackGamma_Exclusion(int id) {
    //#[ operation AplParamSceneBlackGamma_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneBlackGamma
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneBlackGammaRange_Exclusion(int id) {
    //#[ operation AplParamSceneBlackGammaRange_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneBlackGammaRange
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneBlackBPedestal_Exclusion(int id) {
    //#[ operation AplParamSceneBlackBPedestal_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneBlackBPedestal
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneBlackGPedestal_Exclusion(int id) {
    //#[ operation AplParamSceneBlackGPedestal_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneBlackGPedestal
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneBlackMasterPedestal_Exclusion(int id) {
    //#[ operation AplParamSceneBlackMasterPedestal_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneBlackMasterPedestal
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneBlackPedestalOffset_Exclusion(int id) {
    //#[ operation AplParamSceneBlackPedestalOffset_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneBlackPedestalOffset
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneBlackRPedestal_Exclusion(int id) {
    //#[ operation AplParamSceneBlackRPedestal_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneBlackRPedestal
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneChromaLevel_Exclusion(int id) {
    //#[ operation AplParamSceneChromaLevel_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneChromaLevel
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneChromaPhase_Exclusion(int id) {
    //#[ operation AplParamSceneChromaPhase_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneChromaPhase
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollectionSwitch_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollectionSwitch_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollectionSwitch
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_R_SAT_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_R_SAT_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_R_SAT
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_R_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_R_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_R_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P1_SUN_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P1_SUN_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P1_SUN
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P1_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P1_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P1_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P2_MON_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P2_MON_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P2_MON
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P2_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P2_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P2_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P3_TUE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P3_TUE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P3_TUE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P3_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P3_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P3_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_Yl_WED_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_Yl_WED_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_Yl_WED
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_Yl_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_Yl_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_Yl_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P4_THU_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P4_THU_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P4_THU
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P4_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P4_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P4_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P5_FRI_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P5_FRI_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P5_FRI
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P5_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P5_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P5_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_G_SAT_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_G_SAT_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_G_SAT
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_G_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_G_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_G_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P6_SUN_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P6_SUN_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P6_SUN
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P6_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P6_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P6_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_Cy_MON_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_Cy_MON_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_Cy_MON
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_Cy_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_Cy_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_Cy_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P7_TUE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P7_TUE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P7_TUE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P7_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P7_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P7_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_B_WED_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_B_WED_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_B_WED
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_B_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_B_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_B_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P8_THU_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P8_THU_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P8_THU
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P8_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P8_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P8_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_Mg_FRI_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_Mg_FRI_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_Mg_FRI
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_Mg_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_Mg_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_Mg_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P9_SAT_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P9_SAT_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P9_SAT
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P9_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P9_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P9_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P10_SUN_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P10_SUN_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P10_SUN
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneColorCollection_P10_PHASE_Exclusion(int id) {
    //#[ operation AplParamSceneColorCollection_P10_PHASE_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneColorCollection_P10_PHASE
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneDetail_Exclusion(int id) {
    //#[ operation AplParamSceneDetail_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneDetail
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneDetailCoring_Exclusion(int id) {
    //#[ operation AplParamSceneDetailCoring_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneDetailCoring
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneDetailFrequency_Exclusion(int id) {
    //#[ operation AplParamSceneDetailFrequency_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneDetailFrequency
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneDetailMasterLevel_Exclusion(int id) {
    //#[ operation AplParamSceneDetailMasterLevel_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneDetailMasterLevel
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneGammaSelect_Exclusion(int id) {
    //#[ operation AplParamSceneGammaSelect_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneGammaSelect
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneGamutSelect_Exclusion(int id) {
    //#[ operation AplParamSceneGamutSelect_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneGamutSelect
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneHlgKneeMode_Exclusion(int id) {
    //#[ operation AplParamSceneHlgKneeMode_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneHlgKneeMode
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneHlgKneePoint_Exclusion(int id) {
    //#[ operation AplParamSceneHlgKneePoint_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneHlgKneePoint
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneHlgKneeSlope_Exclusion(int id) {
    //#[ operation AplParamSceneHlgKneeSlope_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneHlgKneeSlope
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneHlgKneeSwitch_Exclusion(int id) {
    //#[ operation AplParamSceneHlgKneeSwitch_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneHlgKneeSwitch
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneKneeMode_Exclusion(int id) {
    //#[ operation AplParamSceneKneeMode_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneKneeMode
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneKneePoint_Exclusion(int id) {
    //#[ operation AplParamSceneKneePoint_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneKneePoint
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneKneeSlope_Exclusion(int id) {
    //#[ operation AplParamSceneKneeSlope_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneKneeSlope
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneKneeSwitch_Exclusion(int id) {
    //#[ operation AplParamSceneKneeSwitch_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneKneeSwitch
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneMasterGamma_Exclusion(int id) {
    //#[ operation AplParamSceneMasterGamma_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneMasterGamma
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneMatrixSwitch_Exclusion(int id) {
    //#[ operation AplParamSceneMatrixSwitch_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneMatrixSwitch
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneMatrix_R_G_Exclusion(int id) {
    //#[ operation AplParamSceneMatrix_R_G_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneMatrix_R_G
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneMatrix_R_B_Exclusion(int id) {
    //#[ operation AplParamSceneMatrix_R_B_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneMatrix_R_B
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneMatrix_G_R_Exclusion(int id) {
    //#[ operation AplParamSceneMatrix_G_R_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneMatrix_G_R
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneMatrix_G_B_Exclusion(int id) {
    //#[ operation AplParamSceneMatrix_G_B_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneMatrix_G_B
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneMatrix_B_R_Exclusion(int id) {
    //#[ operation AplParamSceneMatrix_B_R_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneMatrix_B_R
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneMatrix_B_G_Exclusion(int id) {
    //#[ operation AplParamSceneMatrix_B_G_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneMatrix_B_G
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneSkinDetail1_Exclusion(int id) {
    //#[ operation AplParamSceneSkinDetail1_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneSkinDetail1
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneSkinDetail2_Exclusion(int id) {
    //#[ operation AplParamSceneSkinDetail2_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneSkinDetail2
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneSkinDetail3_Exclusion(int id) {
    //#[ operation AplParamSceneSkinDetail3_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneSkinDetail3
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneWhiteClipLevel_Exclusion(int id) {
    //#[ operation AplParamSceneWhiteClipLevel_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneWhiteClipLevel
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSceneWhiteClipSwitch_Exclusion(int id) {
    //#[ operation AplParamSceneWhiteClipSwitch_Exclusion(int)
    #undef	P_NAME
    #define P_NAME		AplParamSceneWhiteClipSwitch
    #define P_NAME_VLOG	P_NAME
    #define P_NAME_S1	P_NAME
    #define P_NAME_S2	P_NAME
    #define P_NAME_S3	P_NAME
    #define P_NAME_S4	P_NAME
    #define P_NAME_S5	P_NAME
    #define _P_NAME(x,y)	__P_NAME(x,y)
    #define __P_NAME(x,y)	x##y
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	P_NAME,
    	AplParamColorMain
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // 読み込み処理
    if( id == AplParamColorMain || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_VLOG ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S1 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S2 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S3 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S4 ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME, APL_PARAM_GET_DATA( P_NAME_S5 ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //書き込み処理
    if( id == P_NAME ){
    	switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    		case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    			APL_PARAM_SET_DATA( P_NAME_VLOG, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    			APL_PARAM_SET_DATA( P_NAME_S1, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    			APL_PARAM_SET_DATA( P_NAME_S2, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    			APL_PARAM_SET_DATA( P_NAME_S3, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    			APL_PARAM_SET_DATA( P_NAME_S4, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    			APL_PARAM_SET_DATA( P_NAME_S5, APL_PARAM_GET_DATA( P_NAME ) );
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSDIOut_Exclusion(int id) {
    //#[ operation AplParamSDIOut_Exclusion(int)
    // SDI ROW 		[OFF] 以外時： [ON] 固定
    
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,  // APL_SYS_PARAM_SWITCH_OFF
    	true, // APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // SDI ROW
    if( APL_PARAM_GET_DATA(AplParamSystemSdiRaw) != APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF ){
    	Exclusion[ APL_SYS_PARAM_SWITCH_OFF ] = false;
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSDIOut) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSDIOut, APL_PARAM_GET_MASTER_DATA(AplParamSDIOut) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamSDIOut) ] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSDIOut, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSdiOutFormat_Exclusion(int id) {
    //#[ operation AplParamSdiOutFormat_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SDI_FORMAT_4096_2160P
    	true,	// APL_SYS_PARAM_SDI_FORMAT_3840_2160P
    	true,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080P
    	true,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080I
    	true,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF
    	true,	// APL_SYS_PARAM_SDI_FORMAT_1280_720P
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	//AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamSystemSdiRaw,
    	AplParamSystemMainPixel,
    	AplParamSdiOutSignalSelect,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    if ( m_IsExecuteIdMaxForSdiFormat == false && id != AplParamIdMax )
    {
    	return;
    }
    
    m_IsExecuteIdMaxForSdiFormat = true;
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			default:
    				break;
    		}
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    		{
    			case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    			//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    				break;
    
    			case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    			//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    				break;
    
    			case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    			//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    				break;
    
    			default:
    				break;
    		}
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			default:
    				break;
    		}
    		break;
    
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			default:
    				break;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= false;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= false;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= false;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= false;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			default:
    				break;
    		}
    		break;
    	default:
    		break;
    }
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF] = false;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P] = false;
    		break;
    	default:
    		break;
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSdiOutFormat) ] == true )	/* parasoft-suppress  BD-PB-ARRAY */
    {
    	APL_PARAM_SET_DATA( AplParamSdiOutFormat, APL_PARAM_GET_MASTER_DATA(AplParamSdiOutFormat) );
    	return;
    }
    
    // Bug4883
    if( Exclusion[APL_PARAM_GET_DATA( AplParamSdiOutFormat )] == false )		/* parasoft-suppress  BD-PB-ARRAY */
    {
    	if ( AplParamIdMax == id )
    	{
    
    		switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    		
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    				if ( Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF] == true )
    				{
    					APL_PARAM_SET_CACHE_DATA( AplParamSdiOutFormat, APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF );
    					return;
    				}
    				break;
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    			case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    			default:
    				if ( Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I] == true )
    				{
    					APL_PARAM_SET_CACHE_DATA( AplParamSdiOutFormat, APL_SYS_PARAM_SDI_FORMAT_1920_1080I );
    					return;
    				}
    				break;
    		}
    	}
    
    	for( int i = 0 ; i < APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ; i++ ){
    		if( Exclusion[i] == true ){
    			APL_PARAM_SET_CACHE_DATA( AplParamSdiOutFormat, i );
    			
    			switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    			
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    					if ( i == APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF )
    					{
    						return;
    					}
    					break;
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    				default:
    					if ( i == APL_SYS_PARAM_SDI_FORMAT_1920_1080I )
    					{
    						return;
    					}
    					break;
    			}
    					
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSdiOutIndicatorDisp_Exclusion(int id) {
    //#[ operation AplParamSdiOutIndicatorDisp_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSdiOutIndicatorDisp) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSdiOutIndicatorDisp, APL_PARAM_GET_MASTER_DATA(AplParamSdiOutIndicatorDisp) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamSdiOutIndicatorDisp )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSdiOutIndicatorDisp, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSdiOutMarkerDisp_Exclusion(int id) {
    //#[ operation AplParamSdiOutMarkerDisp_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSdiOutMarkerDisp) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSdiOutMarkerDisp, APL_PARAM_GET_MASTER_DATA(AplParamSdiOutMarkerDisp) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamSdiOutMarkerDisp )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSdiOutMarkerDisp, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSdiOutMenuDisp_Exclusion(int id) {
    //#[ operation AplParamSdiOutMenuDisp_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamPlayMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamPlayMode
    switch( APL_PARAM_GET_DATA( AplParamPlayMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSdiOutMenuDisp) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSdiOutMenuDisp, APL_PARAM_GET_MASTER_DATA(AplParamSdiOutMenuDisp) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamSdiOutMenuDisp )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSdiOutMenuDisp, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSdiRemote_Exclusion(int id) {
    //#[ operation AplParamSdiRemote_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamRecFunctionMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSdiRemote) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSdiRemote, APL_PARAM_GET_MASTER_DATA(AplParamSdiRemote) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamSdiRemote )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSdiRemote, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSdiOutSignalSelect_Exclusion(int id) {
    //#[ operation AplParamSdiOutSignalSelect_Exclusion(int)
    // SDI ROW 		[OFF] 以外時： [NORMAL] 固定
    
    bool Exclusion[ APL_SYS_PARAM_SDI_SIGNAL_SEL_MAX + 1 ] = {
    	false,  // APL_SYS_PARAM_SDI_SIGNAL_SEL_NORMAL
    	true, // APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P
    	true, // APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I
    	true, // APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw
    };
    
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // SDI ROW
    if( APL_PARAM_GET_DATA(AplParamSystemSdiRaw) != APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF ){
    	Exclusion[ APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I ] = false;
    	Exclusion[ APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P ] = false;
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSdiOutSignalSelect) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSdiOutSignalSelect, APL_PARAM_GET_MASTER_DATA(AplParamSdiOutSignalSelect) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamSdiOutSignalSelect) ] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SDI_SIGNAL_SEL_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSdiOutSignalSelect, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamShutterDegValue_Exclusion(int id) {
    //#[ operation AplParamShutterDegValue_Exclusion(int)
    // 現在のVFRValue値を保持する
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamShutterDegValueIndex,
    	AplParamShutterDegValueHalf,
    	AplParamShutterDegValue1,
    	AplParamShutterDegValue2,
    	AplParamShutterDegValue3,
    	AplParamShutterDegValue4,
    	AplParamShutterDegValue5,
    	AplParamShutterDegValue6,
    	AplParamShutterDegValue7,
    	AplParamShutterDegValue8,
    	AplParamShutterDegValue9,
    	AplParamShutterDegValue10,
    	AplParamShutterDegValue11
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamShutterDegValueHalfを先頭として
    // Index Offset(0始まり) を加算したidに格納されている値を取得
    APL_PARAM_SET_DATA( AplParamShutterDegValue, APL_PARAM_GET_DATA( AplParamShutterDegValueHalf + APL_PARAM_GET_DATA( AplParamShutterDegValueIndex ) ) );
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamShutterDegValue1_Exclusion(int id) {
    //#[ operation AplParamShutterDegValue1_Exclusion(int)
    // VFR1に1~150の処理を記載しておく
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	//AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamShutterDegValue1,
    	AplParamShutterDegValue2,
    	AplParamShutterDegValue3,
    	AplParamShutterDegValue4,
    	AplParamShutterDegValue5,
    	AplParamShutterDegValue6,
    	AplParamShutterDegValue7,
    	AplParamShutterDegValue8,
    	AplParamShutterDegValue9,
    	AplParamShutterDegValue10,
    	AplParamShutterDegValue11	
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Freq or MAX(起動時) 読み込み
    if( id == AplParamIdMax || id == AplParamSystemModeFrequency ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			for( int i = 0 ; i < 11 ; i++ ){
    				APL_PARAM_SET_DATA( AplParamShutterDegValue1 + i, APL_PARAM_GET_DATA( AplParamShutterDegValue1PAL + i ) );
    			}
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    		default:
    			for( int i = 0 ; i < 11 ; i++ ){
    				APL_PARAM_SET_DATA( AplParamShutterDegValue1 + i, APL_PARAM_GET_DATA( AplParamShutterDegValue1NTSC + i ) );
    			}
    			break;
    	}
    }
    
    // 設定時：書き込み
    if( id >= AplParamShutterDegValue1 && id <= AplParamShutterDegValue11  ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			APL_PARAM_SET_DATA( AplParamShutterDegValue1PAL + (id - AplParamShutterDegValue1), APL_PARAM_GET_DATA( id ) );
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    		default:
    			APL_PARAM_SET_DATA( AplParamShutterDegValue1NTSC + (id - AplParamShutterDegValue1), APL_PARAM_GET_DATA( id ) );
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamShutterDegValueIndex_Exclusion(int id) {
    //#[ operation AplParamShutterDegValueIndex_Exclusion(int)
    // NTSC,PALで各EEPROMの値を取得してくる
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamShutterDegValueIndex
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Freq or Max(起動時)は読み込み
    if( id == AplParamSystemModeFrequency || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			APL_PARAM_SET_DATA( AplParamShutterDegValueIndex, APL_PARAM_GET_DATA( AplParamShutterDegValueIndexPAL ) );
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    			APL_PARAM_SET_DATA( AplParamShutterDegValueIndex, APL_PARAM_GET_DATA( AplParamShutterDegValueIndexNTSC ) );
    			break;
    		default:
    			break;
    	}
    }
    
    // Index 書き込み
    if( id == AplParamShutterDegValueIndex ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			APL_PARAM_SET_DATA( AplParamShutterDegValueIndexPAL, APL_PARAM_GET_DATA( AplParamShutterDegValueIndex ) );
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    			APL_PARAM_SET_DATA( AplParamShutterDegValueIndexNTSC, APL_PARAM_GET_DATA( AplParamShutterDegValueIndex ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamShutterSecValue_Exclusion(int id) {
    //#[ operation AplParamShutterSecValue_Exclusion(int)
    // 現在のVFRValue値を保持する
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamShutterSecValueIndex,
    	AplParamShutterSecValueHalf,
    	AplParamShutterSecValue1,
    	AplParamShutterSecValue2,
    	AplParamShutterSecValue3,
    	AplParamShutterSecValue4,
    	AplParamShutterSecValue5,
    	AplParamShutterSecValue6,
    	AplParamShutterSecValue7,
    	AplParamShutterSecValue8,
    	AplParamShutterSecValue9,
    	AplParamShutterSecValue10,
    	AplParamShutterSecValue11
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamShutterSecValueHalfを先頭として
    // Index Offset(0始まり) を加算したidに格納されている値を取得
    APL_PARAM_SET_DATA( AplParamShutterSecValue, APL_PARAM_GET_DATA( AplParamShutterSecValueHalf + APL_PARAM_GET_DATA( AplParamShutterSecValueIndex ) ) );
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamShutterSecValue1_Exclusion(int id) {
    //#[ operation AplParamShutterSecValue1_Exclusion(int)
    // VFR1に1~150の処理を記載しておく
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamShutterSecValue1,
    	AplParamShutterSecValue2,
    	AplParamShutterSecValue3,
    	AplParamShutterSecValue4,
    	AplParamShutterSecValue5,
    	AplParamShutterSecValue6,
    	AplParamShutterSecValue7,
    	AplParamShutterSecValue8,
    	AplParamShutterSecValue9,
    	AplParamShutterSecValue10,
    	AplParamShutterSecValue11	
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Freq or MAX(起動時) 読み込み
    if( id == AplParamIdMax || id == AplParamSystemModeFrequency ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			for( int i = 0 ; i < 11 ; i++ ){
    				APL_PARAM_SET_DATA( AplParamShutterSecValue1 + i, APL_PARAM_GET_DATA( AplParamShutterSecValue1PAL + i ) );
    			}
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    		default:
    			for( int i = 0 ; i < 11 ; i++ ){
    				APL_PARAM_SET_DATA( AplParamShutterSecValue1 + i, APL_PARAM_GET_DATA( AplParamShutterSecValue1NTSC + i ) );
    			}
    			break;
    	}
    }
    
    // 設定時：書き込み
    if( id >= AplParamShutterSecValue1 && id <= AplParamShutterSecValue11  ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			APL_PARAM_SET_DATA( AplParamShutterSecValue1PAL + (id - AplParamShutterSecValue1), APL_PARAM_GET_DATA( id ) );
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    		default:
    			APL_PARAM_SET_DATA( AplParamShutterSecValue1NTSC + (id - AplParamShutterSecValue1), APL_PARAM_GET_DATA( id ) );
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamShutterSecValueIndex_Exclusion(int id) {
    //#[ operation AplParamShutterSecValueIndex_Exclusion(int)
    // NTSC,PALで各EEPROMの値を取得してくる
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamShutterSecValueIndex,
    	AplParamShutterSecSettingRangeMax,
    	AplParamShutterSecSettingRangeMin
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    static char index_back;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Freq or Max(起動時)は読み込み
    if( id == AplParamSystemModeFrequency || id == AplParamIdMax ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndexPAL));
    			APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, APL_PARAM_GET_DATA( AplParamShutterSecValueIndexPAL ) );
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    			index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndexNTSC));
    			APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, APL_PARAM_GET_DATA( AplParamShutterSecValueIndexNTSC ) );
    			break;
    		default:
    			break;
    	}
    }
    
    // シャッタースピード設定範囲外の時の対応
    if( id == AplParamShutterSecValueIndex ){		/* AplParamShutterSecValueIndexの場合は、キャッシュで書き込み */
    	int indexTmp = APL_PARAM_GET_DATA( AplParamShutterSecValueIndex );
    	if(APL_PARAM_GET_DATA( AplParamShutterSecValueIndex ) == 0){
    		/* HALF SHUTTER時は範囲外検出しない */
    	}else{
    		if(APL_PARAM_GET_DATA(AplParamShutterSecValue) > APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMax)){
    			while(1){
    				if(indexTmp > 0){		/* Index値が負にならないようフェールセーフ */
    					indexTmp--;
    				}
    				if(indexTmp <= 0){
    					index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    					APL_PARAM_SET_CACHE_DATA( AplParamShutterSecValueIndex, 0 );
    					break;
    				}else if(APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp) <= APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMax)){
    					if(APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp) < APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMin)){
    						index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    						APL_PARAM_SET_CACHE_DATA( AplParamShutterSecValueIndex, 0 );
    					}else{
    						index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    						APL_PARAM_SET_CACHE_DATA( AplParamShutterSecValueIndex, indexTmp );
    					}
    					break;
    				}
    			}
    		}else if(APL_PARAM_GET_DATA(AplParamShutterSecValue) < APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMin)){
    			if((char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex)) <= index_back){		/* Indexが同じか下方向の場合 */
    				index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    				APL_PARAM_SET_CACHE_DATA( AplParamShutterSecValueIndex, 0 );		/* HALF SHUTTERに丸める */
    			}else{																	/* Indexが上方向の場合 */
    				while(1){
    					indexTmp++;
    					if(0 == APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp)){
    						index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    						APL_PARAM_SET_CACHE_DATA( AplParamShutterSecValueIndex, 0 );
    						break;
    					}else if(APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp) >= APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMin)){
    						if(APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp) > APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMax)){
    							index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    							APL_PARAM_SET_CACHE_DATA( AplParamShutterSecValueIndex, 0 );
    						}else{
    							index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    							APL_PARAM_SET_CACHE_DATA( AplParamShutterSecValueIndex, indexTmp );
    						}
    						break;
    					}
    				}
    			}
    		}
    	}
    }else{		/* AplParamShutterSecValueIndex以外の場合は、マスターへ書き込み */
    	int indexTmp = APL_PARAM_GET_DATA( AplParamShutterSecValueIndex );
    	if(APL_PARAM_GET_DATA( AplParamShutterSecValueIndex ) == 0){
    		/* HALF SHUTTER時は範囲外検出しない */
    	}else{
    		if(APL_PARAM_GET_DATA(AplParamShutterSecValue) > APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMax)){
    			while(1){
    				if(indexTmp > 0){		/* Index値が負にならないようフェールセーフ */
    					indexTmp--;
    				}
    				if(indexTmp <= 0){
    					index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    					APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, 0 );
    					break;
    				}else if(APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp) <= APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMax)){
    					if(APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp) < APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMin)){
    						index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    						APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, 0 );
    					}else{
    						index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    						APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, indexTmp );
    					}
    					break;
    				}
    			}
    		}else if(APL_PARAM_GET_DATA(AplParamShutterSecValue) < APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMin)){
    			if((char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex)) <= index_back){		/* Indexが同じか下方向の場合 */
    				index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    				APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, 0 );				/* HALF SHUTTERに丸める */
    			}else{																	/* Indexが上方向の場合 */
    				while(1){
    					indexTmp++;
    					if(0 == APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp)){
    						index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    						APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, 0 );
    						break;
    					}else if(APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp) >= APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMin)){
    						if(APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + indexTmp) > APL_PARAM_GET_DATA(AplParamShutterSecSettingRangeMax)){
    							index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    							APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, 0 );
    						}else{
    							index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    							APL_PARAM_SET_DATA( AplParamShutterSecValueIndex, indexTmp );
    						}
    						break;
    					}
    				}
    			}
    		}
    	}
    }
    
    // Index 書き込み
    if( id == AplParamShutterSecValueIndex ){
    	index_back = (char)(APL_PARAM_GET_DATA(AplParamShutterSecValueIndex));
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			APL_PARAM_SET_DATA( AplParamShutterSecValueIndexPAL, APL_PARAM_GET_DATA( AplParamShutterSecValueIndex ) );
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    			APL_PARAM_SET_DATA( AplParamShutterSecValueIndexNTSC, APL_PARAM_GET_DATA( AplParamShutterSecValueIndex ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSpotMeterUserSw_Exclusion(int id) {
    //#[ operation AplParamSpotMeterUserSw_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamLcdFocusAssistUserSw,
    	AplParamLcdFocusExpandUserSw,
    	AplParamColorBar,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    /* [Bug 4939] SQUARES [ON]の時はMarkerのみ非表示(MarkerServiceクラスで処理)
    // AplParamLcdFocusAssistUserSw
    switch( APL_PARAM_GET_DATA( AplParamLcdFocusAssistUserSw ) ){
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_OFF:
    		break;
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_PEAKING:
    		break;
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_SQUERES:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    */
    
    // bug 6150 【K460】【ST】LCDがEXPAND表示になっているとき、HDMI/SDIのマーカー類とSPOT METER（文字と□）が消える
    // 差し戻し
    // AplParamLcdFocusExpandUserSw
    switch( APL_PARAM_GET_DATA( AplParamLcdFocusExpandUserSw ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamColorBar
    switch( APL_PARAM_GET_DATA( AplParamColorBar ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSpotMeterUserSw) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSpotMeterUserSw, APL_PARAM_GET_MASTER_DATA(AplParamSpotMeterUserSw) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamSpotMeterUserSw )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSpotMeterUserSw, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSystemMainCodec_Exclusion(int id) {
    //#[ operation AplParamSystemMainCodec_Exclusion(int)
    //① FREQ./MAIN_PIXEL/SENSOR_MODEの組み合わせでの
    //　　排他必要。詳細は下記資料参照。
    //② [OFF] 以外時： 無効
    //詳細は「C-K460_記録フォーマット仕様書」を参照
    //
    
    bool Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_MAX + 1] = {
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA
    	true  // APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamSystemSensorMode,
    	AplParamSystemMainPixel,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Freq
    switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM             ] = false;	
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM             ] = false;		
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M ] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M ] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M  ] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH             ] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM             ] = false;	
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM             ] = false;	
    		break;
    	default:
    		break;
    }
    
    // Senser Mode
    switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) ){
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K        :
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K    :
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM             ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM             ] = false;		
    		break;
    	default:
    		break;
    }
    
    // MainPix
    switch(APL_PARAM_GET_DATA(AplParamSystemMainPixel)){
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM             ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM             ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = false;
    		if ( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ &&
    			 APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ &&
    			 APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ )
    		{
    			Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = false;
    		}
    		if ( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ &&
    			 APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ )
    		{
    			Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = false;
    		}
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM]				= false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720 :
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M  ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH             ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA             ] = false;
    		break;
    	default:
    		break;
    }
    
    
    // その他個別対応
    switch ( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) )
    {
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		switch ( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) )
    		{
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = false;
    				break;
    			
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				if ( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K )
    				{
    					Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = false;
    				}
    				break;
    			default:
    				break;
    		}
    		break;
    	
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		switch ( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) )
    		{
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				if ( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K ||
    					 APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    				{
    					Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = false;
    				}
    				break;
    			default:
    				break;
    		}
    		break;
    	default:
    		break;
    }
    
    //VUPで有効
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch ( APL_PARAM_GET_DATA( AplParamVup ) )
    	{
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( ( ( APL_PARAM_GET_DATA(AplParamSystemModeFrequency) == APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ )   ||
    				   ( APL_PARAM_GET_DATA(AplParamSystemModeFrequency) == APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ ) ) &&
    				( APL_PARAM_GET_DATA(AplParamSystemMainPixel)== APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080 ) )
    			{
    				Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M  ] = false;
    			}
    			Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = false;
    			Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = false;
    			Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M  ] = false;
    			break;
    			
    		default:
    			break;
    	}
    }
    
    // 排他制御
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSystemMainCodec) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSystemMainCodec, APL_PARAM_GET_MASTER_DATA(AplParamSystemMainCodec) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA(AplParamSystemMainCodec)] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < (APL_SYS_PARAM_SYSTEM_MAIN_CODEC_MAX + 1) ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSystemMainCodec, i );
    				break;
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSystemMainPixel_Exclusion(int id) {
    //#[ operation AplParamSystemMainPixel_Exclusion(int)
    //Freq [50i/59i] 時： [1920x1080] 固定
    //　　 [29p]/[25p]/[23p] 時： [1280x720] 選択不可
    //　　 [24p] 時： [3840x2160]/[1920x1080]/[1280x720] 選択不可
    //SDIRaw [OFF] 以外時： 無効
    //SenserMode [S35 MIX 2.8K]/[4/3 CROP&MIX 2.2K] 時：
    //　　       [4096x2160]/[3840x2160]/[1280x720] 選択不可
    bool Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_MAX + 1 ] = {	
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080
    	true, // APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080
    	true  // APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamSystemSensorMode
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // Freq
    switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		// [1920x1080] 固定
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160 ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160 ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080 ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720 ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720 ] = false; //[1280x720] 選択不可
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160 ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080 ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720 ] = false;
    		break;
    	default:
    		break;
    }
    
    // SenserMode
    if( (APL_PARAM_GET_DATA(AplParamSystemSensorMode) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K) || 
        (APL_PARAM_GET_DATA(AplParamSystemSensorMode) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K) ){
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160 ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160 ] = false;
    		Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720 ] = false;
    }
    
    /* 排他が必要な場合 */
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSystemMainPixel) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSystemMainPixel, APL_PARAM_GET_MASTER_DATA(AplParamSystemMainPixel) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamSystemMainPixel )] == false  ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < (APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_MAX + 1) ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSystemMainPixel, i );
    				break;
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSystemRecMode_Exclusion(int id) {
    //#[ operation AplParamSystemRecMode_Exclusion(int)
    #if 0
    /* 複数AplParam組み合わせで */
    /* 記録コーデックが決定される */
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamSystemMainPixel,
    	AplParamSystemSensorMode,
    	AplParamSystemMainCodec,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) )
    {
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:   
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) )
    		{   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160: 
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_4K_60P_150M);
    								break;
    							default:    
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0); 
    						break;
    				}
    				break;
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_60P_150M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_2K_60P_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M:   
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_2K_60P_200M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K: 
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_2K_60P_100M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}             
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_60P_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M:   
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_60P_200M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS:   
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_AVCHD_PS);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K: 
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_LPCM_HD_60P_100M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}             
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720:   
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_AVCHD_PM);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			default:       
    				AplAssert(0);
    				break;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:   
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) )
    		{   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_60I_50M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_60I_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_AVCHD_PH);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_AVCHD_HA);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			default:       
    				AplAssert(0);
    				break;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:     
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) )
    		{   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_4K_30P_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_4K_30P_150M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_4K_30P_400M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_30P_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_UHD_30P_150M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_UHD_30P_400M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_2K_30P_50M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_2K_30P_100M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_2K_30P_50M);
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_30P_50M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_30P_100M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_LPCM_HD_60P_50M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			default:       
    				AplAssert(0);
    				break;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:    
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) )
    		{   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_4K_2398P_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_4K_2398P_150M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_4K_2398P_400M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_UHD_2398P_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_UHD_2398P_150M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_UHD_2398P_400M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_2K_2398P_50M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_2K_2398P_100M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_2K_2398P_50M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_FHD_2398P_50M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_FHD_2398P_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_AVCHD_PH_2398P);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_LPCM_HD_2398P_50M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			default:       
    				AplAssert(0);
    				break;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:     
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) )
    		{   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_4K_24P_100M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_4K_24P_150M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_4K_24P_400M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) )
    				{
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422LONGGOP_2K_24P_50M);    
    								break;
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_422INTRA_2K_24P_100M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    						switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) )
    						{
    							case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M: 
    								APL_PARAM_SET_DATA( AplParamSystemRecMode, APL_SYS_PARAM_RECMODE_MOV_420LONGGOP_2K_24P_50M);    
    								break;
    							default:
    								AplAssert(0);
    								break;
    						}
    						break;
    					default:
    						AplAssert(0);
    						break;
    				}
    				break;   
    			default:       
    				AplAssert(0);
    				break;
    		}
    		break;
    	default:
    		AplAssert(0);
    		break;
    }
    #endif
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSystemSdiRaw_Exclusion(int id) {
    //#[ operation AplParamSystemSdiRaw_Exclusion(int)
    // Freq[50i/59i]時: [OFF]固定
    // Freq[50p/59p]時: [S35 5.7K]選択不可
    
    bool Exclusion[ APL_SYS_PARAM_SYSTEM_SDI_RAW_MAX + 1 ] = {
    	true, // APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF
    	true, // APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K
    	true, // APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K
    	true, // APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = false;
    		break;
    	default:
    		break;
    }
    
    // VUP1で有効
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	if ( APL_PARAM_GET_DATA( AplParamVup ) < APL_SYS_PARAM_VUP_1ST )
    	{
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K] = false;
    	}
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSystemSdiRaw) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSystemSdiRaw, APL_PARAM_GET_MASTER_DATA(AplParamSystemSdiRaw) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamSystemSdiRaw) ] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_SDI_RAW_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSystemSdiRaw, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSystemSensorMode_Exclusion(int id) {
    //#[ operation AplParamSystemSensorMode_Exclusion(int)
    // Freq[50i/59i]時: [S35 5.7K]固定
    // SDIRaw[OFF以外]時: 無効
    
    bool Exclusion[ APL_SYS_PARAM_SYSTEM_SENSOR_MODE_MAX + 1 ] = {
    	true, // APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K
    	true, // APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K
    	true, // APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Freq
    switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K    ] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K] = false;
    		break;
    	default:
    		break;
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSystemSensorMode) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSystemSensorMode, APL_PARAM_GET_MASTER_DATA(AplParamSystemSensorMode) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamSystemSensorMode) ] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_SENSOR_MODE_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSystemSensorMode, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamSystemSubRec_Exclusion(int id) {
    //#[ operation AplParamSystemSubRec_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SYSTEM_SUB_REC_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SYSTEM_SUB_REC_OFF
    	true,	// APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M
    	true,	// APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M
    	true,	// APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M
    	true,	// APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamSystemSdiRaw,
    	AplParamSystemSensorMode,
    	AplParamSystemMainPixel,
    	AplParamSystemMainCodec,
    	AplParamRelayBackup,
    	AplParamRecFunctionMode,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSensorMode
    switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) ){
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemMainPixel
    switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemMainCodec
    switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) ){
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRelayBackup
    switch( APL_PARAM_GET_DATA( AplParamRelayBackup ) ){
    	case APL_SYS_PARAM_RELAY_BACKUP_OFF:
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_RELAY:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = false;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = false;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = false;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = false;
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamSystemSubRec) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamSystemSubRec, APL_PARAM_GET_MASTER_DATA(AplParamSystemSubRec) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamSystemSubRec )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_SUB_REC_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamSystemSubRec, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamTCG_Exclusion(int id) {
    //#[ operation AplParamTCG_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_TCG_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_TCG_FREE
    	true,	// APL_SYS_PARAM_TCG_REC
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamPreRec,
    	AplParamRecFunctionMode,
    	AplParamRelayBackup,
    	AplParamVFRMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamPreRec
    switch( APL_PARAM_GET_DATA( AplParamPreRec ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_TCG_REC] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_TCG_FREE] = false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_TCG_FREE] = false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRelayBackup
    switch( APL_PARAM_GET_DATA( AplParamRelayBackup ) ){
    	case APL_SYS_PARAM_RELAY_BACKUP_OFF:
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_RELAY:
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:
    		Exclusion[APL_SYS_PARAM_TCG_REC] = false;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVFRMode
    switch( APL_PARAM_GET_DATA( AplParamVFRMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_TCG_FREE] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamTCG) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamTCG, APL_PARAM_GET_MASTER_DATA(AplParamTCG) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamTCG )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_TCG_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamTCG, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamTCMode_Exclusion(int id) {
    //#[ operation AplParamTCMode_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_TCMODE_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_TCMODE_DF
    	true,	// APL_SYS_PARAM_TCMODE_NDF
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamRecFunctionMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamTCMode) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamTCMode, APL_PARAM_GET_MASTER_DATA(AplParamTCMode) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamTCMode )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_TCMODE_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamTCMode, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamTimeStamp_Exclusion(int id) {
    //#[ operation AplParamTimeStamp_Exclusion(int)
    // SUB REC	[ON] 時、[OFF] 固定
    // VFR SW	[ON] 時、[OFF] 固定
    // [SYSTEM SETTINGS]-[COLOR SETTINGS]-[MAIN]が[V-Log] 時、[OFF] 固定
    
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true, // APL_SYS_PARAM_SWITCH_OFF
    	true, // APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSubRec,
    	AplParamVFRMode,
    	AplParamColorMain,
    	AplParamSystemSdiRaw,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // SUB REC
    if( APL_PARAM_GET_DATA(AplParamSystemSubRec) != APL_SYS_PARAM_SYSTEM_SUB_REC_OFF ){
    	Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    }
    
    // VFR SW
    if(  APL_PARAM_GET_DATA( AplParamVFRMode ) == APL_SYS_PARAM_SWITCH_ON ){
    	Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    }
    
    // COLOR MAIN
    if( APL_PARAM_GET_DATA( AplParamColorMain ) == APL_SYS_PARAM_COLOR_MAIN_VLOG ){
    	Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    }
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    		break;
    	default:
    		break;
    }
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[ APL_SYS_PARAM_SWITCH_ON ] = false;
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamTimeStamp) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamTimeStamp, APL_PARAM_GET_MASTER_DATA(AplParamTimeStamp) );
    } else {
    	if( Exclusion[ APL_PARAM_GET_DATA(AplParamTimeStamp) ] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamTimeStamp, i );
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamTouchAfSw_Exclusion(int id) {
    //#[ operation AplParamTouchAfSw_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamTouchAfSw) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamTouchAfSw, APL_PARAM_GET_MASTER_DATA(AplParamTouchAfSw) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamTouchAfSw )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamTouchAfSw, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton1_Exclusion(int id) {
    //#[ operation AplParamUserButton1_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton1,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton1) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton1, APL_SYS_PARAM_USER_BUTTON_PUSH_AF );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton1) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton1, APL_SYS_PARAM_USER_BUTTON_PUSH_AF );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton2_Exclusion(int id) {
    //#[ operation AplParamUserButton2_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton2,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton2) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton2, APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton2) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton2, APL_SYS_PARAM_USER_BUTTON_PEAK_SQ_FA );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton3_Exclusion(int id) {
    //#[ operation AplParamUserButton3_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton3,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton3) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton3, APL_SYS_PARAM_USER_BUTTON_SPOT_METER );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton3) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton3, APL_SYS_PARAM_USER_BUTTON_SPOT_METER );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton4_Exclusion(int id) {
    //#[ operation AplParamUserButton4_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton4,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton4) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton4, APL_SYS_PARAM_USER_BUTTON_EIS );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton4) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton4, APL_SYS_PARAM_USER_BUTTON_EIS );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton5_Exclusion(int id) {
    //#[ operation AplParamUserButton5_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton5,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton5) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton5, APL_SYS_PARAM_USER_BUTTON_WFM );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton5) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton5, APL_SYS_PARAM_USER_BUTTON_WFM );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton6_Exclusion(int id) {
    //#[ operation AplParamUserButton6_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton6,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton6) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton6, APL_SYS_PARAM_USER_BUTTON_AWB );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton6) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton6, APL_SYS_PARAM_USER_BUTTON_AWB );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton7_Exclusion(int id) {
    //#[ operation AplParamUserButton7_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton7,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton7) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton7, APL_SYS_PARAM_USER_BUTTON_SLOT_SEL );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton7) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton7, APL_SYS_PARAM_USER_BUTTON_SLOT_SEL );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton8_Exclusion(int id) {
    //#[ operation AplParamUserButton8_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton8,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton8) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton8, APL_SYS_PARAM_USER_BUTTON_FA );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton8) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton8, APL_SYS_PARAM_USER_BUTTON_FA );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamUserButton9_Exclusion(int id) {
    //#[ operation AplParamUserButton9_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserButton9,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton9) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton9, APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			if ( APL_PARAM_GET_DATA(AplParamUserButton9) == APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE )
    			{
    				APL_PARAM_SET_CACHE_DATA( AplParamUserButton9, APL_SYS_PARAM_USER_BUTTON_OPEN_IRIS_FA );
    			}
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			break;
    		default:
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamVFRMode_Exclusion(int id) {
    //#[ operation AplParamVFRMode_Exclusion(int)
    // 59.94i/50i 時 OFF固定且つ、第2階層[FPS]グレー 
    // AVCHD時 OFF固定且つ、第2階層[FPS]グレー
    
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamSystemMainCodec,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemMainCodec
    // AplParamSystemSdiRaw
    if ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) == APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) ){
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS:
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH:
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA:
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM:
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamVFRMode) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamVFRMode, APL_PARAM_GET_MASTER_DATA(AplParamVFRMode) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamVFRMode )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamVFRMode, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamVFRValue_Exclusion(int id) {
    //#[ operation AplParamVFRValue_Exclusion(int)
    // 現在のVFRValue値を保持する
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVFRValueIndex,
    	AplParamVFRValueSystem,
    	AplParamVFRValue1,
    	AplParamVFRValue2,
    	AplParamVFRValue3,
    	AplParamVFRValue4,
    	AplParamVFRValue5,
    	AplParamVFRValue6,
    	AplParamVFRValue7,
    	AplParamVFRValue8,
    	AplParamVFRValue9,
    	AplParamVFRValue10,
    	AplParamVFRValue11,
    	AplParamVFRValue12,
    	AplParamVFRValue13,
    	AplParamVFRValue14,
    	AplParamVFRValue15,
    	AplParamVFRValue16,
    	AplParamVFRValue17,
    	AplParamVFRValue18,
    	AplParamVFRValue19,
    	AplParamVFRValue20,
    	AplParamVFRValue21,
    	AplParamVFRValue22,
    	AplParamVFRValue23,
    	AplParamVFRValue24,
    	AplParamVFRValue25,
    	AplParamVFRValue26,
    	AplParamVFRValue27,
    	AplParamVFRValue28,
    	AplParamVFRValue29,
    	AplParamVFRValue30,
    	AplParamVFRValue31,
    	AplParamVFRValue32,
    	AplParamVFRValue33,
    	AplParamVFRValue34,
    	AplParamVFRValue35,
    	AplParamVFRValue36,
    	AplParamVFRValue37,
    	AplParamVFRValue38,
    	AplParamVFRValue39,
    	AplParamVFRValue40,
    	AplParamVFRValue41,
    	AplParamVFRValue42,
    	AplParamVFRValue43,
    	AplParamVFRValue44,
    	AplParamVFRValue45,
    	AplParamVFRValue46,
    	AplParamVFRValue47,
    	AplParamVFRValue48,
    	AplParamVFRValue49,
    	AplParamVFRValue50,
    	AplParamVFRValue51,
    	AplParamVFRValue52,
    	AplParamVFRValue53,
    	AplParamVFRValue54,
    	AplParamVFRValue55,
    	AplParamVFRValue56,
    	AplParamVFRValue57,
    	AplParamVFRValue58,
    	AplParamVFRValue59,
    	AplParamVFRValue60,
    	AplParamVFRValue61,
    	AplParamVFRValue62,
    	AplParamVFRValue63,
    	AplParamVFRValue64,
    	AplParamVFRValue65,
    	AplParamVFRValue66,
    	AplParamVFRValue67,
    	AplParamVFRValue68,
    	AplParamVFRValue69,
    	AplParamVFRValue70,
    	AplParamVFRValue71,
    	AplParamVFRValue72,
    	AplParamVFRValue73,
    	AplParamVFRValue74,
    	AplParamVFRValue75,
    	AplParamVFRValue76,
    	AplParamVFRValue77,
    	AplParamVFRValue78,
    	AplParamVFRValue79,
    	AplParamVFRValue80,
    	AplParamVFRValue81,
    	AplParamVFRValue82,
    	AplParamVFRValue83,
    	AplParamVFRValue84,
    	AplParamVFRValue85,
    	AplParamVFRValue86,
    	AplParamVFRValue87,
    	AplParamVFRValue88,
    	AplParamVFRValue89,
    	AplParamVFRValue90,
    	AplParamVFRValue91,
    	AplParamVFRValue92,
    	AplParamVFRValue93,
    	AplParamVFRValue94,
    	AplParamVFRValue95,
    	AplParamVFRValue96,
    	AplParamVFRValue97,
    	AplParamVFRValue98,
    	AplParamVFRValue99,
    	AplParamVFRValue100,
    	AplParamVFRValue101,
    	AplParamVFRValue102,
    	AplParamVFRValue103,
    	AplParamVFRValue104,
    	AplParamVFRValue105,
    	AplParamVFRValue106,
    	AplParamVFRValue107,
    	AplParamVFRValue108,
    	AplParamVFRValue109,
    	AplParamVFRValue110,
    	AplParamVFRValue111,
    	AplParamVFRValue112,
    	AplParamVFRValue113,
    	AplParamVFRValue114,
    	AplParamVFRValue115,
    	AplParamVFRValue116,
    	AplParamVFRValue117,
    	AplParamVFRValue118,
    	AplParamVFRValue119,
    	AplParamVFRValue120,
    	AplParamVFRValue121,
    	AplParamVFRValue122,
    	AplParamVFRValue123,
    	AplParamVFRValue124,
    	AplParamVFRValue125,
    	AplParamVFRValue126,
    	AplParamVFRValue127,
    	AplParamVFRValue128,
    	AplParamVFRValue129,
    	AplParamVFRValue130,
    	AplParamVFRValue131,
    	AplParamVFRValue132,
    	AplParamVFRValue133,
    	AplParamVFRValue134,
    	AplParamVFRValue135,
    	AplParamVFRValue136,
    	AplParamVFRValue137,
    	AplParamVFRValue138,
    	AplParamVFRValue139,
    	AplParamVFRValue140,
    	AplParamVFRValue141,
    	AplParamVFRValue142,
    	AplParamVFRValue143,
    	AplParamVFRValue144,
    	AplParamVFRValue145,
    	AplParamVFRValue146,
    	AplParamVFRValue147,
    	AplParamVFRValue148,
    	AplParamVFRValue149,
    	AplParamVFRValue150,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamVFRValueSystemを先頭として
    // Index Offset(0始まり) を加算したidに格納されている値を取得
    APL_PARAM_SET_DATA( AplParamVFRValue, APL_PARAM_GET_DATA( AplParamVFRValueSystem + APL_PARAM_GET_DATA( AplParamVFRValueIndex ) ) );
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamVFRValueIndex_Exclusion(int id) {
    //#[ operation AplParamVFRValueIndex_Exclusion(int)
    // NTSC,PALで各EEPROMの値を取得してくる
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamVFRValueIndex,
    	AplParamVFRSettingRangeMax,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
   

    // Index 書き込み
    if( id == AplParamVFRValueIndex ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			APL_PARAM_SET_DATA( AplParamVFRValueIndexPAL, APL_PARAM_GET_DATA( AplParamVFRValueIndex ) );
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    			APL_PARAM_SET_DATA( AplParamVFRValueIndexNTSC, APL_PARAM_GET_DATA( AplParamVFRValueIndex ) );
    			break;
    		default:
    			break;
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamVFRValueSystem_Exclusion(int id) {
    //#[ operation AplParamVFRValueSystem_Exclusion(int)
    // NTSC,PALで各EEPROMの値を取得してくる
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Freq
    switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    	// PAL系
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		APL_PARAM_SET_DATA( AplParamVFRValueSystem, 50 );
    		APL_PARAM_SET_DATA( AplParamVFRValueSystemPAL, 50 );
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		APL_PARAM_SET_DATA( AplParamVFRValueSystem, 25 );
    		APL_PARAM_SET_DATA( AplParamVFRValueSystemPAL, 25 );
    		break;
    	// NTSC系
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		APL_PARAM_SET_DATA( AplParamVFRValueSystem, 60 );
    		APL_PARAM_SET_DATA( AplParamVFRValueSystemNTSC, 60 );
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		APL_PARAM_SET_DATA( AplParamVFRValueSystem, 30 );
    		APL_PARAM_SET_DATA( AplParamVFRValueSystemNTSC, 30 );
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    		APL_PARAM_SET_DATA( AplParamVFRValueSystem, 24 );
    		APL_PARAM_SET_DATA( AplParamVFRValueSystemNTSC, 24 );
    		break;
    	default:
    		break;
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamVFRValue1_Exclusion(int id) {
    //#[ operation AplParamVFRValue1_Exclusion(int)
    // VFR1に1~150の処理を記載しておく
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	// AplParamSystemModeFrequency,	// Bug4874 切替後にシステムリセットがかかるので反応しなくていい
    	AplParamVFRValue1,
    	AplParamVFRValue2,
    	AplParamVFRValue3,
    	AplParamVFRValue4,
    	AplParamVFRValue5,
    	AplParamVFRValue6,
    	AplParamVFRValue7,
    	AplParamVFRValue8,
    	AplParamVFRValue9,
    	AplParamVFRValue10,
    	AplParamVFRValue11,
    	AplParamVFRValue12,
    	AplParamVFRValue13,
    	AplParamVFRValue14,
    	AplParamVFRValue15,
    	AplParamVFRValue16,
    	AplParamVFRValue17,
    	AplParamVFRValue18,
    	AplParamVFRValue19,
    	AplParamVFRValue20,
    	AplParamVFRValue21,
    	AplParamVFRValue22,
    	AplParamVFRValue23,
    	AplParamVFRValue24,
    	AplParamVFRValue25,
    	AplParamVFRValue26,
    	AplParamVFRValue27,
    	AplParamVFRValue28,
    	AplParamVFRValue29,
    	AplParamVFRValue30,
    	AplParamVFRValue31,
    	AplParamVFRValue32,
    	AplParamVFRValue33,
    	AplParamVFRValue34,
    	AplParamVFRValue35,
    	AplParamVFRValue36,
    	AplParamVFRValue37,
    	AplParamVFRValue38,
    	AplParamVFRValue39,
    	AplParamVFRValue40,
    	AplParamVFRValue41,
    	AplParamVFRValue42,
    	AplParamVFRValue43,
    	AplParamVFRValue44,
    	AplParamVFRValue45,
    	AplParamVFRValue46,
    	AplParamVFRValue47,
    	AplParamVFRValue48,
    	AplParamVFRValue49,
    	AplParamVFRValue50,
    	AplParamVFRValue51,
    	AplParamVFRValue52,
    	AplParamVFRValue53,
    	AplParamVFRValue54,
    	AplParamVFRValue55,
    	AplParamVFRValue56,
    	AplParamVFRValue57,
    	AplParamVFRValue58,
    	AplParamVFRValue59,
    	AplParamVFRValue60,
    	AplParamVFRValue61,
    	AplParamVFRValue62,
    	AplParamVFRValue63,
    	AplParamVFRValue64,
    	AplParamVFRValue65,
    	AplParamVFRValue66,
    	AplParamVFRValue67,
    	AplParamVFRValue68,
    	AplParamVFRValue69,
    	AplParamVFRValue70,
    	AplParamVFRValue71,
    	AplParamVFRValue72,
    	AplParamVFRValue73,
    	AplParamVFRValue74,
    	AplParamVFRValue75,
    	AplParamVFRValue76,
    	AplParamVFRValue77,
    	AplParamVFRValue78,
    	AplParamVFRValue79,
    	AplParamVFRValue80,
    	AplParamVFRValue81,
    	AplParamVFRValue82,
    	AplParamVFRValue83,
    	AplParamVFRValue84,
    	AplParamVFRValue85,
    	AplParamVFRValue86,
    	AplParamVFRValue87,
    	AplParamVFRValue88,
    	AplParamVFRValue89,
    	AplParamVFRValue90,
    	AplParamVFRValue91,
    	AplParamVFRValue92,
    	AplParamVFRValue93,
    	AplParamVFRValue94,
    	AplParamVFRValue95,
    	AplParamVFRValue96,
    	AplParamVFRValue97,
    	AplParamVFRValue98,
    	AplParamVFRValue99,
    	AplParamVFRValue100,
    	AplParamVFRValue101,
    	AplParamVFRValue102,
    	AplParamVFRValue103,
    	AplParamVFRValue104,
    	AplParamVFRValue105,
    	AplParamVFRValue106,
    	AplParamVFRValue107,
    	AplParamVFRValue108,
    	AplParamVFRValue109,
    	AplParamVFRValue110,
    	AplParamVFRValue111,
    	AplParamVFRValue112,
    	AplParamVFRValue113,
    	AplParamVFRValue114,
    	AplParamVFRValue115,
    	AplParamVFRValue116,
    	AplParamVFRValue117,
    	AplParamVFRValue118,
    	AplParamVFRValue119,
    	AplParamVFRValue120,
    	AplParamVFRValue121,
    	AplParamVFRValue122,
    	AplParamVFRValue123,
    	AplParamVFRValue124,
    	AplParamVFRValue125,
    	AplParamVFRValue126,
    	AplParamVFRValue127,
    	AplParamVFRValue128,
    	AplParamVFRValue129,
    	AplParamVFRValue130,
    	AplParamVFRValue131,
    	AplParamVFRValue132,
    	AplParamVFRValue133,
    	AplParamVFRValue134,
    	AplParamVFRValue135,
    	AplParamVFRValue136,
    	AplParamVFRValue137,
    	AplParamVFRValue138,
    	AplParamVFRValue139,
    	AplParamVFRValue140,
    	AplParamVFRValue141,
    	AplParamVFRValue142,
    	AplParamVFRValue143,
    	AplParamVFRValue144,
    	AplParamVFRValue145,
    	AplParamVFRValue146,
    	AplParamVFRValue147,
    	AplParamVFRValue148,
    	AplParamVFRValue149,
    	AplParamVFRValue150,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // Freq or MAX(起動時) 読み込み
    if( id == AplParamIdMax || id == AplParamSystemModeFrequency ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			for( int i = 0 ; i < 150 ; i++ ){
    				APL_PARAM_SET_DATA( AplParamVFRValue1 + i, APL_PARAM_GET_DATA( AplParamVFRValue1PAL + i ) );
    			}
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    		default:
    			for( int i = 0 ; i < 150 ; i++ ){
    				APL_PARAM_SET_DATA( AplParamVFRValue1 + i, APL_PARAM_GET_DATA( AplParamVFRValue1NTSC + i ) );
    			}
    			break;
    	}
    }
    
    // 設定時：書き込み
    if( id >= AplParamVFRValue1 && id <= AplParamVFRValue150  ){
    	switch( APL_PARAM_GET_DATA(AplParamSystemModeFrequency)){
    		// PAL系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    			APL_PARAM_SET_DATA( AplParamVFRValue1PAL + (id - AplParamVFRValue1), APL_PARAM_GET_DATA( id ) );
    			break;
    		// NTSC系
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:	
    		default:
    			APL_PARAM_SET_DATA( AplParamVFRValue1NTSC + (id - AplParamVFRValue1), APL_PARAM_GET_DATA( id ) );
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamWhiteValueTemp_Exclusion(int id) {
    //#[ operation AplParamWhiteValueTemp_Exclusion(int)
    // 現在のWHITE Value値を保持する
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWhiteValueAWBResult,
    	AplParamWhiteValueIndex,
    	AplParamWhiteValueATWTemp,
    	AplParamWhiteValueATWGMg,
    	AplParamWhiteValueAWBMemoryTemp,
    	AplParamWhiteValueAWBMemoryGMg,
    	AplParamWhiteValue1Temp,
    	AplParamWhiteValue1GMg,
    	AplParamWhiteValue2Temp,
    	AplParamWhiteValue2GMg,
    	AplParamWhiteValue3Temp,
    	AplParamWhiteValue3GMg,
    	AplParamWhiteValue4Temp,
    	AplParamWhiteValue4GMg,
    	AplParamWhiteValue5Temp,
    	AplParamWhiteValue5GMg,
    	AplParamWhiteValue6Temp,
    	AplParamWhiteValue6GMg,
    	AplParamWhiteValue7Temp,
    	AplParamWhiteValue7GMg,
    	AplParamWhiteValue8Temp,
    	AplParamWhiteValue8GMg,
    	AplParamWhiteValue9Temp,
    	AplParamWhiteValue9GMg,
    	AplParamWhiteValue10Temp,
    	AplParamWhiteValue10GMg,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamWhiteValueATWTempを先頭として
    // Index Offset(0始まり) を加算したidに格納されている値を取得
    APL_PARAM_SET_DATA( AplParamWhiteValueTemp, APL_PARAM_GET_DATA( AplParamWhiteValueATWTemp + (APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) * 2) ) );
    APL_PARAM_SET_DATA( AplParamWhiteValueGMg, APL_PARAM_GET_DATA( AplParamWhiteValueATWGMg + (APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) * 2) ) );
    //#]
}

void AplParamMainExclusionFuncK460::AplParamZebra_Exclusion(int id) {
    //#[ operation AplParamZebra_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorBar,
    	AplParamLcdFocusAssistUserSw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamLcdFocusAssistUserSw
    switch( APL_PARAM_GET_DATA( AplParamLcdFocusAssistUserSw ) ){
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_OFF:
    		break;
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_PEAKING:
    		break;
    	case APL_SYS_PARAM_FOCUS_ASSIST_USER_SW_SQUERES:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    // AplParamColorBar
    switch ( APL_PARAM_GET_DATA( AplParamColorBar ) )
    {
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	default:
    		break;
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamZebra) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamZebra, APL_PARAM_GET_MASTER_DATA(AplParamZebra) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamZebra )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamZebra, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamAudioLevelMeterInvalid_Exclusion(int id) {
    //#[ operation AplParamAudioLevelMeterInvalid_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVFRMode,
    	AplParamRecFunctionMode,
    	AplParamPlayMode,
    	AplParamVFRValueIndex,
    };
    
    // Default
    int setId = APL_SYS_PARAM_SWITCH_OFF;
    
    // AplParamPlayMode
    switch( APL_PARAM_GET_DATA( AplParamPlayMode ) ){
    	case APL_SYS_PARAM_SWITCH_ON:
    		setId = APL_SYS_PARAM_SWITCH_OFF;
    		goto EXCLUSION_RESULT;
    		break;
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	default:
    		break;
    }
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		setId = APL_SYS_PARAM_SWITCH_ON;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		setId = APL_SYS_PARAM_SWITCH_ON;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		break;
    	default:
    		break;
    	}
    
    // 排他条件をInvalid条件一つでも満たしたらONに設定
    EXCLUSION_RESULT:
    
    // 排他処理 ==================
    APL_PARAM_SET_DATA( AplParamAudioLevelMeterInvalid, setId);
    //#]
}

void AplParamMainExclusionFuncK460::AplParamNativeISO_Exclusion(int id) {
    //#[ operation AplParamNativeISO_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamNativeISO,
    	AplParamSceneGammaSelect,
    	AplParamSystemSensorMode,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamSceneGammaSelect or Max(起動時)は読み込み
    if( id == AplParamSceneGammaSelect || id == AplParamIdMax || id == AplParamSystemSensorMode || id == AplParamSystemSdiRaw )
    {
    	switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    	{
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    			APL_PARAM_SET_DATA( AplParamNativeISO, APL_PARAM_GET_DATA( AplParamNativeISOSdiRaw2_2_K) );
    			break;
    		
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    			if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    			{
    				APL_PARAM_SET_DATA( AplParamNativeISO, APL_PARAM_GET_DATA( AplParamNativeISOSdiRawVideo) );
    			}
    			else 
    			{
    				APL_PARAM_SET_DATA( AplParamNativeISO, APL_PARAM_GET_DATA( AplParamNativeISOSdiRawNotVideo) );
    			}
    			break;
    		
    		default:
    			// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParamNativeISO, APL_PARAM_GET_DATA( AplParamNativeISOSensor2_2_K) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParamNativeISO, APL_PARAM_GET_DATA( AplParamNativeISOVideo) );
    				}
    				else 
    				{
    					APL_PARAM_SET_DATA( AplParamNativeISO, APL_PARAM_GET_DATA( AplParamNativeISONotVideo) );
    				}
    			}
    			break;
    	}
    }
    
    // NativeISO 書き込み先と排他切替
    if( id == AplParamNativeISO ){
    
    	switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    	{
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    			APL_PARAM_SET_DATA( AplParamNativeISOSdiRaw2_2_K, APL_PARAM_GET_DATA( AplParamNativeISO) );
    			break;
    		
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    			if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    			{
    				APL_PARAM_SET_DATA( AplParamNativeISOSdiRawVideo, APL_PARAM_GET_DATA( AplParamNativeISO) );
    			}
    			else 
    			{
    				APL_PARAM_SET_DATA( AplParamNativeISOSdiRawNotVideo, APL_PARAM_GET_DATA( AplParamNativeISO) );
    			}
    			break;
    		
    		default:
    			// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParamNativeISOSensor2_2_K, APL_PARAM_GET_DATA( AplParamNativeISO ) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParamNativeISOVideo, APL_PARAM_GET_DATA( AplParamNativeISO ) );
    				}
    				else
    				{
    					APL_PARAM_SET_DATA( AplParamNativeISONotVideo, APL_PARAM_GET_DATA( AplParamNativeISO ) );
    				}
    			}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParam2500BaseISO_Exclusion(int id) {
    //#[ operation AplParam2500BaseISO_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParam2500BaseISO,
    	AplParamSceneGammaSelect,
    	AplParamSystemSensorMode,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamSceneGammaSelect or Max(起動時)は読み込み
    if( id == AplParamSceneGammaSelect || id == AplParamIdMax || id == AplParamSystemSensorMode || id == AplParamSystemSdiRaw )
    {
    	switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    	{
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    			APL_PARAM_SET_DATA( AplParam2500BaseISO, APL_PARAM_GET_DATA( AplParam2500BaseISOSdiRaw2_2_K) );
    			break;
    		
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    			if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    			{
    				APL_PARAM_SET_DATA( AplParam2500BaseISO, APL_PARAM_GET_DATA( AplParam2500BaseISOSdiRawVideo) );
    			}
    			else 
    			{
    				APL_PARAM_SET_DATA( AplParam2500BaseISO, APL_PARAM_GET_DATA( AplParam2500BaseISOSdiRawNotVideo) );
    			}
    			break;
    		
    		default:
    			// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParam2500BaseISO, APL_PARAM_GET_DATA( AplParam2500BaseISOSensor2_2_K) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParam2500BaseISO, APL_PARAM_GET_DATA( AplParam2500BaseISOVideo) );
    				}
    				else 
    				{
    					APL_PARAM_SET_DATA( AplParam2500BaseISO, APL_PARAM_GET_DATA( AplParam2500BaseISONotVideo) );
    				}
    			}
    			break;
    	}
    }
    
    // NativeISO 書き込み先と排他切替
    if( id == AplParam2500BaseISO ){
    
    	switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    	{
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    			APL_PARAM_SET_DATA( AplParam2500BaseISOSdiRaw2_2_K, APL_PARAM_GET_DATA( AplParam2500BaseISO) );
    			break;
    		
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    			if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    			{
    				APL_PARAM_SET_DATA( AplParam2500BaseISOSdiRawVideo, APL_PARAM_GET_DATA( AplParam2500BaseISO) );
    			}
    			else 
    			{
    				APL_PARAM_SET_DATA( AplParam2500BaseISOSdiRawNotVideo, APL_PARAM_GET_DATA( AplParam2500BaseISO) );
    			}
    			break;
    		
    		default:
    			// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParam2500BaseISOSensor2_2_K, APL_PARAM_GET_DATA( AplParam2500BaseISO ) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParam2500BaseISOVideo, APL_PARAM_GET_DATA( AplParam2500BaseISO ) );
    				}
    				else
    				{
    					APL_PARAM_SET_DATA( AplParam2500BaseISONotVideo, APL_PARAM_GET_DATA( AplParam2500BaseISO ) );
    				}
    			}
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParam800BaseISO_Exclusion(int id) {
    //#[ operation AplParam800BaseISO_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParam800BaseISO,
    	AplParamSceneGammaSelect,
    	AplParamSystemSensorMode,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    // AplParamSceneGammaSelect or Max(起動時)は読み込み
    if( id == AplParamSceneGammaSelect || id == AplParamIdMax || id == AplParamSystemSensorMode || id == AplParamSystemSdiRaw )
    {
    	switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    	{
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    			APL_PARAM_SET_DATA( AplParam800BaseISO, APL_PARAM_GET_DATA( AplParam800BaseISOSdiRaw2_2_K) );
    			break;
    		
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    			if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    			{
    				APL_PARAM_SET_DATA( AplParam800BaseISO, APL_PARAM_GET_DATA( AplParam800BaseISOSdiRawVideo) );
    			}
    			else 
    			{
    				APL_PARAM_SET_DATA( AplParam800BaseISO, APL_PARAM_GET_DATA( AplParam800BaseISOSdiRawNotVideo) );
    			}
    			break;
    		
    		default:
    			// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParam800BaseISO, APL_PARAM_GET_DATA( AplParam800BaseISOSensor2_2_K ) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParam800BaseISO, APL_PARAM_GET_DATA( AplParam800BaseISOVideo) );
    				}
    				else 
    				{
    					APL_PARAM_SET_DATA( AplParam800BaseISO, APL_PARAM_GET_DATA( AplParam800BaseISONotVideo) );
    				}
    			}
    			break;
    	}
    }
    
    // NativeISO 書き込み先と排他切替
    if( id == AplParam800BaseISO ){
    
    	switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    	{
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    			APL_PARAM_SET_DATA( AplParam800BaseISOSdiRaw2_2_K, APL_PARAM_GET_DATA( AplParam800BaseISO) );
    			break;
    		
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    			if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    			{
    				APL_PARAM_SET_DATA( AplParam800BaseISOSdiRawVideo, APL_PARAM_GET_DATA( AplParam800BaseISO) );
    			}
    			else 
    			{
    				APL_PARAM_SET_DATA( AplParam800BaseISOSdiRawNotVideo, APL_PARAM_GET_DATA( AplParam800BaseISO) );
    			}
    			break;
    		
    		default:
    			// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    			if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    			{
    				APL_PARAM_SET_DATA( AplParam800BaseISOSensor2_2_K, APL_PARAM_GET_DATA( AplParam800BaseISO ) );
    			}
    			else
    			{
    				if( APL_PARAM_GET_DATA(AplParamSceneGammaSelect) == APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    				{
    					APL_PARAM_SET_DATA( AplParam800BaseISOVideo, APL_PARAM_GET_DATA( AplParam800BaseISO ) );
    				}
    				else
    				{
    					APL_PARAM_SET_DATA( AplParam800BaseISONotVideo, APL_PARAM_GET_DATA( AplParam800BaseISO ) );
    				}
    			}
    			break;
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamMySecurityType_Exclusion(int id) {
    //#[ operation AplParamMySecurityType_Exclusion(int)
    bool Exclusion[ APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ] = {
    	true,	// APL_NET_PARAM_SECURITY_TYPE_NONE
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WEP
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WPA_TKIP
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WPA_AES
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WPA2_TKIP
    	true,	// APL_NET_PARAM_SECURITY_TYPE_WPA2_AES
    	true,	// APL_NET_PARAM_SECURITY_TYPE_AUTO
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWlanMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_NONE] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WEP] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA_TKIP] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA_AES] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA2_TKIP] = false;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_AUTO] = false;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_SELECT:
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_MANUAL:
    		break;
    	case APL_NET_PARAM_WLAN_MODE_NONE:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamMySecurityType) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamMySecurityType, APL_PARAM_GET_MASTER_DATA(AplParamMySecurityType) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamMySecurityType )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamMySecurityType, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamDhcpMode_Exclusion(int id) {
    //#[ operation AplParamDhcpMode_Exclusion(int)
    bool Exclusion[ APL_NET_PARAM_DHCP_MODE_MAX + 1 ] = {
    	true,	// APL_NET_PARAM_DHCP_MODE_OFF
    	true,	// APL_NET_PARAM_DHCP_MODE_CLIENT
    	true,	// APL_NET_PARAM_DHCP_MODE_SERVER
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWlanMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		Exclusion[APL_NET_PARAM_DHCP_MODE_CLIENT] = false;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_SELECT:
    		Exclusion[APL_NET_PARAM_DHCP_MODE_SERVER] = false;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_MANUAL:
    		Exclusion[APL_NET_PARAM_DHCP_MODE_SERVER] = false;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_NONE:
    		Exclusion[APL_NET_PARAM_DHCP_MODE_SERVER] = false;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamDhcpMode) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamDhcpMode, APL_PARAM_GET_MASTER_DATA(AplParamDhcpMode) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamDhcpMode )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_NET_PARAM_DHCP_MODE_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamDhcpMode, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamWhiteValueIndex_Exclusion(int id) {
    //#[ operation AplParamWhiteValueIndex_Exclusion(int)
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorMain,
    	AplParamIRRec,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		// V-Log時にATW無効。AWB MEMORYへ丸める
    		if(APL_PARAM_GET_DATA(AplParamWhiteValueIndex) == 0){
    			APL_PARAM_SET_DATA( AplParamWhiteValueIndex, 1 );
    		}
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamIRRec
    switch( APL_PARAM_GET_DATA( AplParamIRRec ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		// IR SHOOTING=ON時にATW無効。AWB MEMORYへ丸める
    		if(APL_PARAM_GET_DATA(AplParamWhiteValueIndex) == 0){
    			APL_PARAM_SET_DATA( AplParamWhiteValueIndex, 1 );
    		}
    		break;
    	default:
    		break;
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamChannel5G_Exclusion(int id) {
    //#[ operation AplParamChannel5G_Exclusion(int)
    bool Exclusion[ APL_NET_PARAM_CHANNEL5_MAX + 1 ] = {
    	true,	// APL_NET_PARAM_CHANNEL5_AUTO
    	true,	// APL_NET_PARAM_CHANNEL5_CH36
    	true,	// APL_NET_PARAM_CHANNEL5_CH40
    	true,	// APL_NET_PARAM_CHANNEL5_CH44
    	true,	// APL_NET_PARAM_CHANNEL5_CH48
    	true,	// APL_NET_PARAM_CHANNEL5_CH149
    	true,	// APL_NET_PARAM_CHANNEL5_CH153
    	true,	// APL_NET_PARAM_CHANNEL5_CH157
    	true,	// APL_NET_PARAM_CHANNEL5_CH161
    	true,	// APL_NET_PARAM_CHANNEL5_CH165
    	true,	// APL_NET_PARAM_CHANNEL5_CH100
    	true,	// APL_NET_PARAM_CHANNEL5_CH104
    	true,	// APL_NET_PARAM_CHANNEL5_CH108
    	true,	// APL_NET_PARAM_CHANNEL5_CH112
    	true,	// APL_NET_PARAM_CHANNEL5_CH116
    	true,	// APL_NET_PARAM_CHANNEL5_CH132
    	true,	// APL_NET_PARAM_CHANNEL5_CH136
    	true,	// APL_NET_PARAM_CHANNEL5_CH140
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWlanMode,
    	AplParamWifiDongleState,
    };
    
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    #define APL_CHANNEL_SETTING_TYPE_5G_DEFAULT	0x01UL
    #define APL_CHANNEL_SETTING_TYPE_5G_W58		0x02UL
    #define APL_CHANNEL_SETTING_TYPE_5G_W56		0x04UL
    
    unsigned int settingType = APL_CHANNEL_SETTING_TYPE_5G_DEFAULT;
    
    if (( settingType & APL_CHANNEL_SETTING_TYPE_5G_DEFAULT ) != APL_CHANNEL_SETTING_TYPE_5G_DEFAULT ) {
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH36] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH40] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH44] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH48] = false;
    }
    
    if (( settingType & APL_CHANNEL_SETTING_TYPE_5G_W58 ) != APL_CHANNEL_SETTING_TYPE_5G_W58 ) {
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH149] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH153] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH157] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH161] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH165] = false;
    }
    
    if (( settingType & APL_CHANNEL_SETTING_TYPE_5G_W56 ) != APL_CHANNEL_SETTING_TYPE_5G_W56 ) {
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH100] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH104] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH108] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH112] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH116] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH132] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH136] = false;
    	Exclusion[APL_NET_PARAM_CHANNEL5_CH140] = false;
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA( AplParamChannel5G ) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamChannel5G, APL_PARAM_GET_MASTER_DATA( AplParamChannel5G ) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamChannel5G )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_NET_PARAM_CHANNEL5_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamChannel5G, i );
    				break;
    			}
    		}
    	}
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamLcdMarkerLuminance_Exclusion(int id) {
    //#[ operation AplParamLcdMarkerLuminance_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    //VUPで有効
    // Bug5449
    // VUP1,2も非表示
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	APL_PARAM_SET_CACHE_DATA(AplParamLcdMarkerLuminance, 100);
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamOutIndicatorCharLuminance_Exclusion(int id) {
    //#[ operation AplParamOutIndicatorCharLuminance_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    //VUPで有効
    // Bug5449
    // VUP1,2も非表示
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	APL_PARAM_SET_CACHE_DATA(AplParamOutIndicatorCharLuminance, 100);
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamOutMarkerLuminance_Exclusion(int id) {
    //#[ operation AplParamOutMarkerLuminance_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    //VUPで有効
    // Bug5449
    // VUP1,2も非表示
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	APL_PARAM_SET_CACHE_DATA(AplParamOutMarkerLuminance, 100);
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamLcdIndicatorCharLuminance_Exclusion(int id) {
    //#[ operation AplParamLcdIndicatorCharLuminance_Exclusion(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    //VUPで有効
    // Bug5449
    // VUP1,2も非表示
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	APL_PARAM_SET_CACHE_DATA(AplParamLcdIndicatorCharLuminance, 100);
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamHdmiRecRemote_Exclusion(int id) {
    //#[ operation AplParamHdmiRecRemote_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_SWITCH_OFF
    	true,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamRecFunctionMode,
    	AplParamHdmiTcOutput,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamHdmiTcOutput
    switch( APL_PARAM_GET_DATA( AplParamHdmiTcOutput ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamHdmiRecRemote) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamHdmiRecRemote, APL_PARAM_GET_MASTER_DATA(AplParamHdmiRecRemote) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamHdmiRecRemote )] == false ){		/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamHdmiRecRemote, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamAlert_Exclusion(int id) {
    //#[ operation AplParamAlert_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_ALERT_MAX + 1 ] = {
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamAlertSubRecWarning,
    	AplParamAlertSimulRecWarning,
    	AplParamAlertBackGroundRecWarning,
    	AplParamAlertFanStopped,
    	AplParamAlertNotSupportCardSd1,
    	AplParamAlertNotSupportCardSd2,
    	AplParamAlertFormatErrorCardSd1,
    	AplParamAlertFormatErrorCardSd2,
    	AplParamAlertNotSDXCCardSd1,
    	AplParamAlertNotSDXCCardSd2,
    	AplParamAlertIncompatibleCardSd1,
    	AplParamAlertIncompatibleCardSd2,
    	AplParamAlertBackupBattEmpty,
    	AplParamAlertClockReset,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    int set = APL_SYS_PARAM_ALERT_NONE;
    if ( APL_PARAM_GET_DATA( AplParamAlertSubRecWarning ) == true )
    {
    	set = APL_SYS_PARAM_ALERT_SUB_REC_WARNING;
    }
    else if ( APL_PARAM_GET_DATA( AplParamAlertSimulRecWarning ) == true )
    {
    	set = APL_SYS_PARAM_ALERT_SIMUL_REC_WARNING;
    }
    else if ( APL_PARAM_GET_DATA( AplParamAlertBackGroundRecWarning ) == true )
    {
    	set = APL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING;
    }
    else if ( APL_PARAM_GET_DATA( AplParamAlertFanStopped ) == true )
    {
    	set = APL_SYS_PARAM_ALERT_FAN_STOPPED;
    }
    else if ( APL_PARAM_GET_DATA( AplParamAlertNotSupportCardSd1 ) == true || APL_PARAM_GET_DATA( AplParamAlertNotSupportCardSd2 ) == true )
    {
    	set = APL_SYS_PARAM_ALERT_NOT_SUPPORT_CARD;
    }
    else if ( APL_PARAM_GET_DATA( AplParamAlertFormatErrorCardSd1 ) == true || APL_PARAM_GET_DATA( AplParamAlertFormatErrorCardSd2 ) == true )
    {
    	set = APL_SYS_PARAM_ALERT_FORMAT_ERROR_CARD;
    }
    else if ( APL_PARAM_GET_DATA(AplParamSystemSdiRaw) == APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF &&( APL_PARAM_GET_DATA( AplParamAlertNotSDXCCardSd1 ) == true || APL_PARAM_GET_DATA( AplParamAlertNotSDXCCardSd2 ) == true ))
    {
    	set = APL_SYS_PARAM_ALERT_NOT_SDXC_CARD;
    }
    else if ( APL_PARAM_GET_DATA(AplParamSystemSdiRaw) == APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF &&( APL_PARAM_GET_DATA( AplParamAlertIncompatibleCardSd1 ) == true || APL_PARAM_GET_DATA( AplParamAlertIncompatibleCardSd2 ) == true ))
    {
    	set = APL_SYS_PARAM_ALERT_INCOMPATIBLE_CARD;
    }
    else if ( APL_PARAM_GET_DATA( AplParamAlertClockReset ) == true )
    {
    	set = APL_SYS_PARAM_ALERT_CLOCK_RESET;
    }
    else if ( APL_PARAM_GET_DATA( AplParamAlertBackupBattEmpty ) == true )
    {
    	set = APL_SYS_PARAM_ALERT_BACKUP_BATT_EMPTY;
    }
    
    APL_PARAM_SET_DATA( AplParamAlert, set );
    
    // FAN LOCKエラーの時に設定しないとカードアイコンが「Err」にならないのでフラグが立っていたら設定する
    if ( APL_PARAM_GET_DATA( AplParamAlertIncompatibleCardSd1 ) == true )
    {
    	// Bug6570 表示優先順位でWPが優先度高いのでWPが設定されている時は上書き設定しない
    	if ( APL_PARAM_GET_DATA( AplParamSlot1ErrStatus ) != APL_SYS_PARAM_SLOT1_ERR_STATUS_WP && APL_PARAM_GET_DATA( AplParamSlot1ErrStatus ) != APL_SYS_PARAM_SLOT1_ERR_STATUS_NO_REMAIN)
    	{
    		APL_PARAM_SET_DATA( AplParamSlot1ErrStatus, APL_SYS_PARAM_SLOT1_ERR_STATUS_INCOMPATIBLE_CARD );
    	}
    }
    if ( APL_PARAM_GET_DATA( AplParamAlertIncompatibleCardSd2 ) == true )
    {
    	// Bug6570 表示優先順位でWPが優先度高いのでWPが設定されている時は上書き設定しない
    	if ( APL_PARAM_GET_DATA( AplParamSlot2ErrStatus ) != APL_SYS_PARAM_SLOT2_ERR_STATUS_WP && APL_PARAM_GET_DATA( AplParamSlot2ErrStatus ) != APL_SYS_PARAM_SLOT2_ERR_STATUS_NO_REMAIN)
    	{
    		APL_PARAM_SET_DATA( AplParamSlot2ErrStatus, APL_SYS_PARAM_SLOT2_ERR_STATUS_INCOMPATIBLE_CARD );
    	}
    }
    
    if ( APL_PARAM_GET_DATA( AplParamAlertNotSDXCCardSd1 ) == true )		APL_PARAM_SET_DATA( AplParamSlot1ErrStatus, APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SDXC );
    if ( APL_PARAM_GET_DATA( AplParamAlertNotSDXCCardSd2 ) == true )		APL_PARAM_SET_DATA( AplParamSlot2ErrStatus, APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SDXC );
    
    if ( APL_PARAM_GET_DATA( AplParamAlertFormatErrorCardSd1 ) == true )	APL_PARAM_SET_DATA( AplParamSlot1ErrStatus, APL_SYS_PARAM_SLOT1_ERR_STATUS_FORMAT_ERROR );
    if ( APL_PARAM_GET_DATA( AplParamAlertFormatErrorCardSd2 ) == true )	APL_PARAM_SET_DATA( AplParamSlot2ErrStatus, APL_SYS_PARAM_SLOT2_ERR_STATUS_FORMAT_ERROR );
    
    if ( APL_PARAM_GET_DATA( AplParamAlertNotSupportCardSd1 ) == true )		APL_PARAM_SET_DATA( AplParamSlot1ErrStatus, APL_SYS_PARAM_SLOT1_ERR_STATUS_NOT_SUPPORTED );
    if ( APL_PARAM_GET_DATA( AplParamAlertNotSupportCardSd2 ) == true )		APL_PARAM_SET_DATA( AplParamSlot2ErrStatus, APL_SYS_PARAM_SLOT2_ERR_STATUS_NOT_SUPPORTED );
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamWarning_Exclusion(int id) {
    //#[ operation AplParamWarning_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_WARNING_MAX + 1 ] = {
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWarningLowBattery,
    	AplParamWarningHighTemp,
    	AplParamWarningRecWarning,
    	AplParamWarningCardErrorPlaying,
    	AplParamWarningCardErrorSlot1,
    	AplParamWarningCardErrorSlot2,
    	AplParamWarningCardErrorPlayingSlot1,
    	AplParamWarningCardErrorPlayingSlot2,
    	AplParamWarningNoRemain,
    	AplParamWarningBatteryNearEnd,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    int set = APL_SYS_PARAM_WARNING_NONE;
    if ( APL_PARAM_GET_DATA( AplParamWarningLowBattery ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_LOW_BATTERY;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningHighTemp ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_HIGH_TEMP;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningRecWarning ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_REC_WARNING;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningCardErrorPlaying ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningCardErrorSlot1 ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_CARD_ERROR_SLOT1;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningCardErrorSlot2 ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_CARD_ERROR_SLOT2;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningCardErrorPlayingSlot1 ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING_SLOT1;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningCardErrorPlayingSlot2 ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_CARD_ERROR_PLAYING_SLOT2;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningNoRemain ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_NO_REMAIN;
    }
    else if ( APL_PARAM_GET_DATA( AplParamWarningBatteryNearEnd ) == true )
    {
    	set = APL_SYS_PARAM_WARNING_BATTERY_NEAR_END;
    }
    
    APL_PARAM_SET_DATA( AplParamWarning, set );
    //#]
}

void AplParamMainExclusionFuncK460::AplParamHdmiOutSignalSelect_Exclusion(int id) {
    //#[ operation AplParamHdmiOutSignalSelect_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_HDMI_SIGNAL_SEL_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_HDMI_SIGNAL_SEL_HDMI
    	true,	// APL_SYS_PARAM_HDMI_SIGNAL_SEL_1080P
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVup,
    	AplParamGrade,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    // ---------------------------------------------------------
    
    
    // VUP1で有効
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	if ( APL_PARAM_GET_DATA( AplParamVup ) < APL_SYS_PARAM_VUP_1ST )
    	{
    		Exclusion[APL_SYS_PARAM_HDMI_SIGNAL_SEL_1080P] = false;
    	}
    }
    
    // 排他処理 ==================
    // MASTER値に戻せる状態にあれば戻す
    // 現在値が設定不能の場合はCACHEに設定可能なENUM値最少の値を設定する
    if( Exclusion[ APL_PARAM_GET_MASTER_DATA(AplParamHdmiOutSignalSelect) ] == true ){	/* parasoft-suppress  BD-PB-ARRAY */
    	APL_PARAM_SET_DATA( AplParamHdmiOutSignalSelect, APL_PARAM_GET_MASTER_DATA(AplParamHdmiOutSignalSelect) );
    } else {
    	if( Exclusion[APL_PARAM_GET_DATA( AplParamHdmiOutSignalSelect )] == false ){	/* parasoft-suppress  BD-PB-ARRAY */
    		for( int i = 0 ; i < APL_SYS_PARAM_HDMI_SIGNAL_SEL_MAX + 1 ; i++ ){
    			if( Exclusion[i] == true ){
    				APL_PARAM_SET_CACHE_DATA( AplParamHdmiOutSignalSelect, i );
    			}
    		}
    	}
    }
    
    //#]
}

void AplParamMainExclusionFuncK460::AplParamOverClipSd1_Exclusion(int id) {
    //#[ operation AplParamOverClipSd1_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_HDMI_SIGNAL_SEL_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_HDMI_SIGNAL_SEL_HDMI
    	true,	// APL_SYS_PARAM_HDMI_SIGNAL_SEL_1080P
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamAlert,
    	AplParamWarning,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    
    switch( APL_PARAM_GET_DATA( AplParamAlert )){
    	case APL_SYS_PARAM_ALERT_SUB_REC_WARNING:
    	case APL_SYS_PARAM_ALERT_SIMUL_REC_WARNING:
    	case APL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING:
    		break;
    	default:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	}
    if( Exclusion[APL_SYS_PARAM_SWITCH_ON] == false && APL_PARAM_GET_DATA( AplParamOverClipSd1) == APL_SYS_PARAM_SWITCH_ON){
    	APL_PARAM_SET_DATA( AplParamOverClipSd1, APL_SYS_PARAM_SWITCH_OFF);
    }
    //#]
}

void AplParamMainExclusionFuncK460::AplParamOverClipSd2_Exclusion(int id) {
    //#[ operation AplParamOverClipSd2_Exclusion(int)
    bool Exclusion[ APL_SYS_PARAM_HDMI_SIGNAL_SEL_MAX + 1 ] = {
    	true,	// APL_SYS_PARAM_HDMI_SIGNAL_SEL_HDMI
    	true,	// APL_SYS_PARAM_HDMI_SIGNAL_SEL_1080P
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamAlert,
    	AplParamWarning,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return;
    
    switch( APL_PARAM_GET_DATA( AplParamAlert )){
    	case APL_SYS_PARAM_ALERT_SUB_REC_WARNING:
    	case APL_SYS_PARAM_ALERT_SIMUL_REC_WARNING:
    	case APL_SYS_PARAM_ALERT_BACKGROUND_REC_WARNING:
    		break;
    	default:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	}
    switch( APL_PARAM_GET_DATA( AplParamWarning )){
    	case APL_SYS_PARAM_WARNING_REC_WARNING:
    		break;
    	default:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = false;
    		break;
    	}
    
    if( Exclusion[APL_SYS_PARAM_SWITCH_ON] == false && APL_PARAM_GET_DATA( AplParamOverClipSd2) == APL_SYS_PARAM_SWITCH_ON){
    	APL_PARAM_SET_DATA( AplParamOverClipSd2, APL_SYS_PARAM_SWITCH_OFF );
    }
    //#]
}
