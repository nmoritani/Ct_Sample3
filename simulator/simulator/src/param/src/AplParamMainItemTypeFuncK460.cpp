/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version: 7.5.1
 *  Element:          AplParamMainItemTypeFuncK460
 */


#include "AplParamMainItemTypeFuncK460.h"
#include "AplParamService.h"
#include <CtPlatforms.h>
//## package Foundation::Manager

//## class AplParamMainItemTypeFuncK460
AplParamMainItemTypeFuncK460::AplParamMainItemTypeFuncK460(AplParamService::AplParamMainItem* item) : AplParamMainItemTypeFunc(item) {
    //#[ operation AplParamMainItemTypeFuncK460(AplParamMainItem)
    //#]
}

AplParamMainItemTypeFuncK460::~AplParamMainItemTypeFuncK460() {
}

AplParamState AplParamMainItemTypeFuncK460::AplParam3200BaseISO_ViewType(int id) {
    //#[ operation AplParam3200BaseISO_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_3200BASE_ISO_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_1250
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_1600
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_2000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_2500
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_2800
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_3200
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_4000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_5000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_6400
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_8000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_10000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3200BASE_ISO_12800
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamISOSelect,
    	AplParamGainIsoDispChg,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParam3200BaseISO].mState;
    // ---------------------------------------------------------
    
    
    // AplParamISOSelect
    switch( APL_PARAM_GET_DATA( AplParamISOSelect ) ){
    	case APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY:
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_1250] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_1600] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_4000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_5000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_6400] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_8000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_10000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_12800] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_ISO_SELECT_800BASE:
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_1250] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_1600] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_4000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_5000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_6400] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_8000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_10000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_12800] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_ISO_SELECT_3200BASE:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamGainIsoDispChg
    switch( APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN:
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_1250] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_1600] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2500] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_2800] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_3200] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_4000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_5000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_6400] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_8000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_10000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_3200BASE_ISO_12800] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_3200BASE_ISO_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParam3200BaseISO].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_3200BASE_ISO_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParam2500BaseISO_ViewType(int id) {
    //#[ operation AplParam2500BaseISO_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_2500BASE_ISO_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_640
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_800
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_1000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_1250
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_1600
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_2000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_2500
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_3200
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_4000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_5000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_6400
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_8000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_10000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_12800
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_16000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_20000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_2500BASE_ISO_25600
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneGammaSelect,
    	AplParamISOSelect,
    	AplParamGainIsoDispChg,
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
    if( l == idnum ) return m_Item[AplParam2500BaseISO].mState;
    // ---------------------------------------------------------
    
    // AplParamSystemSdiRaw
    switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    {
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_640] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_800] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1000] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1250] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1600] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2000] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2500] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_3200] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_4000] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_5000] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_6400] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_8000] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_10000] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_2500BASE_ISO_12800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_16000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_20000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_25600] = AplParamState_VisibleInvalid;
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    			default:
    				Exclusion[APL_SYS_PARAM_2500BASE_ISO_640] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_2500BASE_ISO_800] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1250] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1600] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2500] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_3200] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_4000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_5000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_6400] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_8000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_10000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_12800] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_16000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_20000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_25600] = AplParamState_VisibleInvalid;
    				break;
    			case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_640] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_800] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1250] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1600] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2500] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_3200] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_4000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_5000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_6400] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_8000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_10000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_12800] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_16000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_20000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_2500BASE_ISO_25600] = AplParamState_VisibleInvalid;
    				break;
    		}
    		break;
    
    	default:
    		// AplParamSceneGammaSelect
    		// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    		if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    		{
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_640] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_800] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1000] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1250] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1600] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2000] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2500] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_3200] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_4000] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_5000] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_6400] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_8000] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_10000] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_2500BASE_ISO_12800] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_2500BASE_ISO_16000] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_2500BASE_ISO_20000] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_2500BASE_ISO_25600] = AplParamState_VisibleInvalid;
    		}
    		else
    		{
    			switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    				default:
    					Exclusion[APL_SYS_PARAM_2500BASE_ISO_640] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_2500BASE_ISO_800] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1250] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1600] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2500] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_3200] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_4000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_5000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_6400] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_8000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_10000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_12800] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_16000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_20000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_25600] = AplParamState_VisibleInvalid;
    					break;
    				case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_640] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_800] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1250] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_1600] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_2500] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_3200] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_4000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_5000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_6400] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_8000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_10000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_12800] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_16000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_20000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_2500BASE_ISO_25600] = AplParamState_VisibleInvalid;
    					break;
    			}
    		}
    		break;
    }
    
    // AplParamISOSelect
    switch( APL_PARAM_GET_DATA( AplParamISOSelect ) ){
    	case APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY:
    	case APL_SYS_PARAM_ISO_SELECT_800BASE:
    	case APL_SYS_PARAM_ISO_SELECT_3200BASE:
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_640] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_1000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_1250] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_1600] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_2000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_2500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_4000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_5000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_6400] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_8000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_10000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_12800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_16000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_20000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_25600] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_ISO_SELECT_2500BASE:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamGainIsoDispChg
    switch( APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN:
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_640] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_800] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_1000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_1250] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_1600] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_2000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_2500] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_3200] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_4000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_5000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_6400] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_8000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_10000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_12800] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_16000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_20000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_2500BASE_ISO_25600] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_2500BASE_ISO_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParam2500BaseISO].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_2500BASE_ISO_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParam3GSdiOutput_ViewType(int id) {
    //#[ operation AplParam3GSdiOutput_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_3GSDI_OUT_PUT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamSystemModeFrequency,
    	AplParamSdiOutSignalSelect,
    	AplParamSdiOutFormat,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParam3GSdiOutput].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // AplParamSdiOutSignalSelect
    switch( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) ){
    	case APL_SYS_PARAM_SDI_SIGNAL_SEL_NORMAL:
    	case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    		break;
    	case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    		break;
    	case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    		Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // [SDI OUT]SIGNALSEL NORMAL
    if ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) == APL_SYS_PARAM_SDI_SIGNAL_SEL_NORMAL ||
    	 APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) == APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI )
    {
    	// AplParamSdiOutFormat
    	switch( APL_PARAM_GET_DATA( AplParamSdiOutFormat ) ){
    		case APL_SYS_PARAM_SDI_FORMAT_4096_2160P:
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SDI_FORMAT_3840_2160P:
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SDI_FORMAT_1920_1080P:
    			// AplParamSystemModeFrequency
    			switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    				case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    					Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    					break;
    				default:
    					break;
    			}
    			break;
    		case APL_SYS_PARAM_SDI_FORMAT_1920_1080I:
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF:
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SDI_FORMAT_1280_720P:
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELA] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_3GSDI_OUT_PUT_LEVELB] = AplParamState_VisibleInvalid;
    			break;
    		default:
    			break;
    	}
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_3GSDI_OUT_PUT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParam3GSdiOutput].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_3GSDI_OUT_PUT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParam800BaseISO_ViewType(int id) {
    //#[ operation AplParam800BaseISO_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_800BASE_ISO_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_200
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_250
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_320
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_400
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_500
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_640
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_800
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_1000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_1250
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_1600
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_2000
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_2500
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_3200
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_800BASE_ISO_4000
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamISOSelect,
    	AplParamGainIsoDispChg,
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
    if( l == idnum ) return m_Item[AplParam800BaseISO].mState;
    // ---------------------------------------------------------
    
    
    // AplParamISOSelect
    switch( APL_PARAM_GET_DATA( AplParamISOSelect ) ){
    	case APL_SYS_PARAM_ISO_SELECT_800BASE:
    		break;
    	case APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY:
    	case APL_SYS_PARAM_ISO_SELECT_3200BASE:
    	case APL_SYS_PARAM_ISO_SELECT_2500BASE:
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_250] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_320] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_400] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_640] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_1000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_1250] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_1600] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_2000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_2500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_4000] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // AplParamSystemSdiRaw
    switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    {
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		//Exclusion[APL_SYS_PARAM_800BASE_ISO_200] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_800BASE_ISO_250] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_800BASE_ISO_320] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_800BASE_ISO_400] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_800BASE_ISO_500] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_800BASE_ISO_640] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_800BASE_ISO_800] = AplParamState_VisibleInvalid;
    		//Exclusion[APL_SYS_PARAM_800BASE_ISO_1000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_1250] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_1600] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_2000] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_2500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_4000] = AplParamState_VisibleInvalid;
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    			default:
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_200] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_250] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_320] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_400] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_500] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_640] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_800] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_1000] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_1250] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_1600] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_2000] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_2500] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_3200] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_4000] = AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_200] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_250] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_320] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_400] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_500] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_640] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_800] = AplParamState_VisibleInvalid;
    				//Exclusion[APL_SYS_PARAM_800BASE_ISO_1000] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_1250] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_1600] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_2000] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_2500] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_3200] = AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_800BASE_ISO_4000] = AplParamState_VisibleInvalid;
    				break;
    		}
    		break;
    
    	default:
    		// AplParamSceneGammaSelect
    		// AplParamSystemSensorMode
    		// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    		if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    		{
    			//Exclusion[APL_SYS_PARAM_800BASE_ISO_200] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_800BASE_ISO_250] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_800BASE_ISO_320] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_800BASE_ISO_400] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_800BASE_ISO_500] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_800BASE_ISO_640] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_800BASE_ISO_800] = AplParamState_VisibleInvalid;
    			//Exclusion[APL_SYS_PARAM_800BASE_ISO_1000] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_800BASE_ISO_1250] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_800BASE_ISO_1600] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_800BASE_ISO_2000] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_800BASE_ISO_2500] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_800BASE_ISO_3200] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_800BASE_ISO_4000] = AplParamState_VisibleInvalid;
    		}
    		else
    		{
    			switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    				default:
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_200] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_250] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_320] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_400] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_500] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_640] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_800] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_1000] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_1250] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_1600] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_2000] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_2500] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_3200] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_4000] = AplParamState_VisibleInvalid;
    					break;
    			
    				case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_200] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_250] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_320] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_400] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_500] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_640] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_800] = AplParamState_VisibleInvalid;
    					//Exclusion[APL_SYS_PARAM_800BASE_ISO_1000] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_1250] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_1600] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_2000] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_2500] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_3200] = AplParamState_VisibleInvalid;
    					Exclusion[APL_SYS_PARAM_800BASE_ISO_4000] = AplParamState_VisibleInvalid;
    					break;
    			}
    		}
    		break;
    }
    
    // AplParamGainIsoDispChg
    switch( APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN:
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_200] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_250] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_320] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_400] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_500] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_640] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_800] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_1000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_1250] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_1600] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_2000] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_2500] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_3200] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_800BASE_ISO_4000] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_800BASE_ISO_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParam800BaseISO].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_800BASE_ISO_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamAwb_ViewType(int id) {
    //#[ operation AplParamAwb_ViewType(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWhiteValueIndex,
       	AplParamIRRec,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamAwb].mState;
    // ---------------------------------------------------------
    
    // WHITE VALUEがMEMORY以外の場合は無効
    // Index:1 == AWB MEMORY
    if( APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) != 1 /* AWB MEMORY */ ){
    	return AplParamState_VisibleInvalid;
    // 赤外線ONの場合は無効
    } else if( APL_PARAM_GET_DATA( AplParamIRRec ) == APL_SYS_PARAM_SWITCH_ON ){
    	return AplParamState_VisibleInvalid;
    } else {
    	return AplParamState_VisibleValid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamBand_ViewType(int id) {
    //#[ operation AplParamBand_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_NET_PARAM_BAND_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_NET_PARAM_BAND_2_4G
    	AplParamState_VisibleValid,	// APL_NET_PARAM_BAND_5G
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
    if( l == idnum ) return m_Item[AplParamBand].mState;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_SELECT:
    		Exclusion[APL_NET_PARAM_BAND_2_4G] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_BAND_5G] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_MANUAL:
    		Exclusion[APL_NET_PARAM_BAND_2_4G] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_BAND_5G] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_NONE:
    		Exclusion[APL_NET_PARAM_BAND_2_4G] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_BAND_5G] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_NET_PARAM_BAND_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamBand].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_NET_PARAM_BAND_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamCameraSettingsMenu_ViewType(int id) {
    //#[ operation AplParamCameraSettingsMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_CAMERA_SETTINGS_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_FPS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_SHUTTER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_EI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_WHITE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_NR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_LENS_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_IR_SHOOTING
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_EIS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CAMERA_SETTINGS_MENU_AUTO_BLACK_BALANCE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemModeFrequency,
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
    if( l == idnum ) return m_Item[AplParamCameraSettingsMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_CAMERA_SETTINGS_MENU_FPS] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_CAMERA_SETTINGS_MENU_FPS] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemMainCodec
    // AplParamSystemSdiRaw
    if ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) == APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF )
    {
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
    			Exclusion[APL_SYS_PARAM_CAMERA_SETTINGS_MENU_FPS] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH:
    			Exclusion[APL_SYS_PARAM_CAMERA_SETTINGS_MENU_FPS] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA:
    			Exclusion[APL_SYS_PARAM_CAMERA_SETTINGS_MENU_FPS] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM:
    			Exclusion[APL_SYS_PARAM_CAMERA_SETTINGS_MENU_FPS] = AplParamState_VisibleInvalid;
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_CAMERA_SETTINGS_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamCameraSettingsMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_CAMERA_SETTINGS_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamChannel_ViewType(int id) {
    //#[ operation AplParamChannel_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_NET_PARAM_CHANNEL24_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL24_AUTO
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL24_CH1
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL24_CH6
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL24_CH11
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
    if( l == idnum ) return m_Item[AplParamChannel].mState;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_SELECT:
    		Exclusion[APL_NET_PARAM_CHANNEL24_AUTO] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH6] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH11] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_MANUAL:
    		Exclusion[APL_NET_PARAM_CHANNEL24_AUTO] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH6] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH11] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_NONE:
    		Exclusion[APL_NET_PARAM_CHANNEL24_AUTO] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH6] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL24_CH11] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_NET_PARAM_CHANNEL24_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamChannel].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_NET_PARAM_CHANNEL24_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamChannel5G_ViewType(int id) {
    //#[ operation AplParamChannel5G_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_NET_PARAM_CHANNEL5_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_AUTO
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH36
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH40
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH44
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH48
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH149
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH153
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH157
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH161
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH165
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH100
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH104
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH108
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH112
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH116
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH132
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH136
    	AplParamState_VisibleValid,	// APL_NET_PARAM_CHANNEL5_CH140
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
    if( l == idnum ) return m_Item[AplParamChannel5G].mState;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		{
    			#define APL_CHANNEL_ITEM_TYPE_5G_DEFAULT	0x01UL
    			#define APL_CHANNEL_ITEM_TYPE_5G_W58		0x02UL
    			#define APL_CHANNEL_ITEM_TYPE_5G_W56		0x04UL
    			
    			unsigned int ItemType = APL_CHANNEL_ITEM_TYPE_5G_DEFAULT;
    			
    			
    			if (( ItemType & APL_CHANNEL_ITEM_TYPE_5G_DEFAULT ) != APL_CHANNEL_ITEM_TYPE_5G_DEFAULT ) {
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH36] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH40] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH44] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH48] = AplParamState_Invisible;
    			}
    			
    			if (( ItemType & APL_CHANNEL_ITEM_TYPE_5G_W58 ) != APL_CHANNEL_ITEM_TYPE_5G_W58 ) {
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH149] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH153] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH157] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH161] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH165] = AplParamState_Invisible;
    			}
    			
    			if (( ItemType & APL_CHANNEL_ITEM_TYPE_5G_W56 ) != APL_CHANNEL_ITEM_TYPE_5G_W56 ) {
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH100] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH104] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH108] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH112] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH116] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH132] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH136] = AplParamState_Invisible;
    				Exclusion[APL_NET_PARAM_CHANNEL5_CH140] = AplParamState_Invisible;
    			}
    		}
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_SELECT:
    	case APL_NET_PARAM_WLAN_MODE_INFRA_MANUAL:
    	case APL_NET_PARAM_WLAN_MODE_NONE:
    		Exclusion[APL_NET_PARAM_CHANNEL5_AUTO] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH36] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH40] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH44] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH48] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH149] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH153] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH157] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH161] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH165] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH100] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH104] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH108] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH112] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH116] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH132] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH136] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_CHANNEL5_CH140] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_NET_PARAM_CHANNEL5_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamChannel5G].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_NET_PARAM_CHANNEL5_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamClipMenu_ViewType(int id) {
    //#[ operation AplParamClipMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_CLIP_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_PROTECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_DELETE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_COPY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CLIP_MENU_INFORMATION
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemMainCodec,
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
    
    
    // AplParamSystemMainCodec
    switch( APL_PARAM_GET_DATA( AplParamSystemMainCodec ) ){
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M:
    		Exclusion[APL_SYS_PARAM_CLIP_MENU_COPY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM:
    		break;
    	default:
    		break;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamColorHdmiOut_ViewType(int id) {
    //#[ operation AplParamColorHdmiOut_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_COLOR_HDMI_OUT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_HDMI_OUT_VLOG
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_HDMI_OUT_V709
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5
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
    if( l == idnum ) return m_Item[AplParamColorHdmiOut].mState;
    // ---------------------------------------------------------
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_HDMI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COLOR_HDMI_OUT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamColorHdmiOut].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_COLOR_HDMI_OUT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamColorLcdOut_ViewType(int id) {
    //#[ operation AplParamColorLcdOut_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_COLOR_LCD_OUT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_LCD_OUT_VLOG
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_LCD_OUT_V709
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5
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
    if( l == idnum ) return m_Item[AplParamColorLcdOut].mState;
    // ---------------------------------------------------------
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_LCD_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COLOR_LCD_OUT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamColorLcdOut].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_COLOR_LCD_OUT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamColorMain_ViewType(int id) {
    //#[ operation AplParamColorMain_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_COLOR_MAIN_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_MAIN_VLOG
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_MAIN_DUMMY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_MAIN_SCENE1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_MAIN_SCENE2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_MAIN_SCENE3
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_MAIN_SCENE4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_MAIN_SCENE5
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
    if( l == idnum ) return m_Item[AplParamColorMain].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_DUMMY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_DUMMY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_DUMMY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_MAIN_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COLOR_MAIN_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamColorMain].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_COLOR_MAIN_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamColorSdiOut_ViewType(int id) {
    //#[ operation AplParamColorSdiOut_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_COLOR_SDI_OUT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SDI_OUT_VLOG
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SDI_OUT_V709
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamColorMain,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamColorSdiOut].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SDI_OUT_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COLOR_SDI_OUT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamColorSdiOut].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_COLOR_SDI_OUT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamColorSub_ViewType(int id) {
    //#[ operation AplParamColorSub_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_COLOR_SUB_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SUB_VLOG
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SUB_V709
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SUB_SCENE1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SUB_SCENE2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SUB_SCENE3
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SUB_SCENE4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_COLOR_SUB_SCENE5
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamSystemSubRec,
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
    if( l == idnum ) return m_Item[AplParamColorSub].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSubRec
    switch( APL_PARAM_GET_DATA( AplParamSystemSubRec ) ){
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_OFF:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVup
    switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    	case APL_SYS_PARAM_VUP_NONE:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_Invisible;
    		}
    		break;
    	case APL_SYS_PARAM_VUP_1ST:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_VLOG] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_V709] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE1] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE2] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE3] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE4] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_COLOR_SUB_SCENE5] = AplParamState_Invisible;
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
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_COLOR_SUB_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamColorSub].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_COLOR_SUB_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamDhcpMode_ViewType(int id) {
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
    	AplParamWlanMode,
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
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		Exclusion[APL_NET_PARAM_DHCP_MODE_CLIENT] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_SELECT:
    		Exclusion[APL_NET_PARAM_DHCP_MODE_SERVER] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_MANUAL:
    		Exclusion[APL_NET_PARAM_DHCP_MODE_SERVER] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_NONE:
    		Exclusion[APL_NET_PARAM_DHCP_MODE_SERVER] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamEISSwitch_ViewType(int id) {
    //#[ operation AplParamEISSwitch_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamEISSwitch].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamDZoomUserSw
    switch( APL_PARAM_GET_DATA( AplParamDZoomUserSw ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamOisMode
    switch( APL_PARAM_GET_DATA( AplParamOisMode ) ){
    	case APL_SYS_PARAM_OIS_MODE_OFF:
    		break;
    	case APL_SYS_PARAM_OIS_MODE_ACTIVE:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_OIS_MODE_STANDARD:
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
    	m_Item[AplParamEISSwitch].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamEncryption_ViewType(int id) {
    //#[ operation AplParamEncryption_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_NONE
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WEP
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WPA_TKIP
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WPA_AES
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WPA2_TKIP
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WPA2_AES
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_AUTO
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
    if( l == idnum ) return m_Item[AplParamEncryption].mState;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_NONE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WEP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA_TKIP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA_AES] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA2_TKIP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_AUTO] = AplParamState_VisibleInvalid;
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
    for( int i = 0 ; i < APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamEncryption].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamFileSceneFileMenu_ViewType(int id) {
    //#[ operation AplParamFileSceneFileMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
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
    for( int i = 0 ; i < APL_SYS_PARAM_FILE_SCENE_FILE_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamFileSceneFileMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_FILE_SCENE_FILE_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamFileSetupFileMenu_ViewType(int id) {
    //#[ operation AplParamFileSetupFileMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
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
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamFileSetupFileMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_FILE_SETUP_FILE_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamFpsMenu_ViewType(int id) {
    //#[ operation AplParamFpsMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_FPS_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FPS_MENU_VFR_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FPS_MENU_VALUE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FPS_MENU_ADD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FPS_MENU_EDIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_FPS_MENU_DELETE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemModeFrequency,
    	AplParamSystemMainCodec,
    	AplParamVFRValueIndex,
    	AplParamVFRMode,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamFpsMenu].mState;
    // ---------------------------------------------------------
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		if ( APL_PARAM_GET_DATA( AplParamVFRValueIndex ) == 0 /* SYSTEM FREQ */)
    		{
    			Exclusion[APL_SYS_PARAM_FPS_MENU_EDIT] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_FPS_MENU_DELETE] = AplParamState_VisibleInvalid;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_FPS_MENU_VFR_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_VALUE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_ADD] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_EDIT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_DELETE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_FPS_MENU_VFR_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_VALUE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_ADD] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_EDIT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_DELETE] = AplParamState_VisibleInvalid;
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
    			Exclusion[APL_SYS_PARAM_FPS_MENU_VFR_SW] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_FPS_MENU_VALUE] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_FPS_MENU_ADD] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_FPS_MENU_EDIT] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_FPS_MENU_DELETE] = AplParamState_VisibleInvalid;
    			break;
    		default:
    			break;
    	}
    }
    
    // AplParamVFRMode
    switch( APL_PARAM_GET_DATA( AplParamVFRMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_FPS_MENU_VALUE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_ADD] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_EDIT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_FPS_MENU_DELETE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    bool bFull = true;
    for( int i = 0 ; i < 151 ; i++ )
    {
    	if ( APL_PARAM_GET_DATA(AplParamVFRValueSystem + i) == 0 )
    	{
    		bFull = false;
    		break;
    	}
    }
    if ( bFull == true )
    {
    	Exclusion[APL_SYS_PARAM_FPS_MENU_ADD] = AplParamState_VisibleInvalid;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_FPS_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamFpsMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_FPS_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamGainIsoDispChg_ViewType(int id) {
    //#[ operation AplParamGainIsoDispChg_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_GAIN_ISO_DISP_CHG_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO
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
    if( l == idnum ) return m_Item[AplParamGainIsoDispChg].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_GAIN_ISO_DISP_CHG_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamGainIsoDispChg].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_GAIN_ISO_DISP_CHG_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamGainSelect_ViewType(int id) {
    //#[ operation AplParamGainSelect_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_GAIN_SELECT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_M12
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_M10
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_M8
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_M6
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_M4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_M2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_0
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P6
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P8
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P10
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P12
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P14
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P16
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P18
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P20
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P22
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P24
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SELECT_P26
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamGainSwitch,
    	AplParamSceneGammaSelect,
    	AplParamGainIsoDispChg,
    	AplParamSystemSensorMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamGainSelect].mState;
    // ---------------------------------------------------------
    
    
    // AplParamGainSwitch
    // AplParamSceneGammaSelect
    // Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    {
    	if ( APL_PARAM_GET_DATA( AplParamGainSwitch ) == APL_SYS_PARAM_GAIN_SWITCH_NORMAL )
    	{
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M12] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M10] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M8]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M6]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M4]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M2]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_0]   = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P2]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P4]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P6]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P8]  = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P10] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P12] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P14] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P16] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P18] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P20] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P22] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P24] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P26] = AplParamState_Invisible;
    	}
    	else
    	{
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M12] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M10] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M8]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M6]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M4]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M2]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_0]   = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P2]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P4]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P6]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P8]  = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P10] = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P12] = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P14] = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P16] = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P18] = AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P20] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P22] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P24] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P26] = AplParamState_Invisible;
    	}
    }
    else
    {
    	if ( APL_PARAM_GET_DATA( AplParamGainSwitch ) == APL_SYS_PARAM_GAIN_SWITCH_NORMAL )
    	{
    		if ( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) != APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    		{
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M12] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M10] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M8]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M6]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M4]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M2]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_0]   = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P2]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P4]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P6]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P8]  = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P10] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P12] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P14] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P16] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P18] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P20] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P22] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P24] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P26] = AplParamState_Invisible;
    		}
    		else
    		{
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_M12] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_M10] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_M8]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M6]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M4]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M2]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_0]   = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P2]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P4]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P6]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P8]  = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P10] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P12] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P14] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P16] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P18] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P20] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P22] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P24] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P26] = AplParamState_Invisible;
    		}
    	}
    	else
    	{
    		if ( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) != APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO )
    		{
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_M12] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_M10] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M8]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M6]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M4]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M2]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_0]   = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P2]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P4]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P6]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P8]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P10] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P12] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P14] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P16] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P18] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P20] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P22] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P24] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_P26] = AplParamState_Invisible;
    		}
    		else
    		{
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_M12] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_M10] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_GAIN_SELECT_M8]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M6]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M4]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_M2]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_0]   = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P2]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P4]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P6]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P8]  = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P10] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P12] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P14] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P16] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P18] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P20] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P22] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P24] = AplParamState_Invisible;
    	//		Exclusion[APL_SYS_PARAM_GAIN_SELECT_P26] = AplParamState_Invisible;
    		}
    	}
    }
    
    if ( APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) == APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO )
    {
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M12] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M10] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M8]  = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M6]  = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M4]  = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_M2]  = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_0]   = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P2]  = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P4]  = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P6]  = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P8]  = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P10] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P12] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P14] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P16] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P18] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P20] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P22] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P24] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_GAIN_SELECT_P26] = AplParamState_Invisible;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_GAIN_SELECT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamGainSelect].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_GAIN_SELECT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamGainSwitch_ViewType(int id) {
    //#[ operation AplParamGainSwitch_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_GAIN_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SWITCH_NORMAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_GAIN_SWITCH_HIGH
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamGainIsoDispChg,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamGainSwitch].mState;
    // ---------------------------------------------------------
    
    
    // AplParamGainIsoDispChg
    switch( APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN:
    		break;
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO:
    		Exclusion[APL_SYS_PARAM_GAIN_SWITCH_NORMAL] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_GAIN_SWITCH_HIGH] = AplParamState_Invisible;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_GAIN_SWITCH_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamGainSwitch].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_GAIN_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamGateway_ViewType(int id) {
    //#[ operation AplParamGateway_ViewType(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamDhcpMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamGateway].mState;
    // ---------------------------------------------------------
    
    
    // AplParamDhcpMode
    switch( APL_PARAM_GET_DATA( AplParamDhcpMode ) ){
    	case APL_NET_PARAM_DHCP_MODE_CLIENT:
    		return AplParamState_Invisible;
    	case APL_NET_PARAM_DHCP_MODE_OFF:
    	case APL_NET_PARAM_DHCP_MODE_SERVER:
    	default:
    		return AplParamState_VisibleValid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamHdmiOutFormat_ViewType(int id) {
    //#[ operation AplParamHdmiOutFormat_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_4096_2160P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_3840_2160P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_1920_1080P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_1920_1080I
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_1280_720P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_720_480P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_FORMAT_720_576P
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamSystemMainPixel,
    	AplParamSystemModeFrequency,
    	AplParamHdmiOutSignalSelect,
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
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			default:
    				break;
    		}
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_Invisible;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_Invisible;
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			default:
    				break;
    		}
    		break;
    
    
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			default:
    				break;
    		}
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
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
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    	default:
    		break;
    }
    
    // AplParamHdmiOutSignalSelect
    switch( APL_PARAM_GET_DATA( AplParamHdmiOutSignalSelect ) ){
    	case APL_SYS_PARAM_HDMI_SIGNAL_SEL_1080P:
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_4096_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_3840_2160P_420_8bit]	= AplParamState_VisibleInvalid;
    	//	Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1920_1080I]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_1280_720P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_480P]				= AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_HDMI_FORMAT_720_576P]				= AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
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
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_HDMI_FORMAT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamHdmiOutMenuDisp_ViewType(int id) {
    //#[ operation AplParamHdmiOutMenuDisp_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamHdmiOutMenuDisp].mState;
    // ---------------------------------------------------------
    
    // AplParamPlayMode
    switch( APL_PARAM_GET_DATA( AplParamPlayMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    	m_Item[AplParamHdmiOutMenuDisp].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamHdmiRecRemote_ViewType(int id) {
    //#[ operation AplParamHdmiRecRemote_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamHdmiRecRemote].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamHdmiTcOutput
    switch( APL_PARAM_GET_DATA( AplParamHdmiTcOutput ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
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
    	m_Item[AplParamHdmiRecRemote].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamHdmiTcOutput_ViewType(int id) {
    //#[ operation AplParamHdmiTcOutput_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamHdmiTcOutput].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // AplParamHdmiOutSignalSelect
    switch( APL_PARAM_GET_DATA( AplParamHdmiOutSignalSelect ) ){
    	case APL_SYS_PARAM_HDMI_SIGNAL_SEL_1080P:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    	m_Item[AplParamHdmiTcOutput].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamISOSelect_ViewType(int id) {
    //#[ operation AplParamISOSelect_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_ISO_SELECT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_ISO_SELECT_800BASE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_ISO_SELECT_3200BASE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_ISO_SELECT_2500BASE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamGainIsoDispChg,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamISOSelect].mState;
    // ---------------------------------------------------------
    
    
    // AplParamGainIsoDispChg
    switch( APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN:
    		Exclusion[APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_ISO_SELECT_800BASE] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_ISO_SELECT_3200BASE] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_ISO_SELECT_2500BASE] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_ISO_SELECT_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamISOSelect].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_ISO_SELECT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamIpAddress_ViewType(int id) {
    //#[ operation AplParamIpAddress_ViewType(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamDhcpMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamIpAddress].mState;
    // ---------------------------------------------------------
    
    
    // AplParamDhcpMode
    switch( APL_PARAM_GET_DATA( AplParamDhcpMode ) ){
    	case APL_NET_PARAM_DHCP_MODE_CLIENT:
    		return AplParamState_Invisible;
    	case APL_NET_PARAM_DHCP_MODE_OFF:
    	case APL_NET_PARAM_DHCP_MODE_SERVER:
    	default:
    		return AplParamState_VisibleValid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamLanguage_ViewType(int id) {
    //#[ operation AplParamLanguage_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    char model[AplParamInfoModel_Size] = {0};
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
    
    //モデル名判定
    APL_PARAM_GET_DATA_AREA(AplParamInfoModel,(UB*)model,AplParamInfoModel_Size);
    if( strncmp(model,"AU-EVA1E",AplParamInfoModel_Size) == 0 )
    {
    	Exclusion[APL_SYS_PARAM_LANGUAGE_JAPANESE]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH_PAL]	= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH]		= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_GERMAN]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_FRENCH_PAL]	= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_FRENCH]		= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_ITALIA]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_SPAIN_PAL]		= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_SPAIN]			= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_DUTCH]			= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_SWEDEN]		= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_POLAND]		= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_RUSSIA]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_ARABIA]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_PERSIA]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_KOREA]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_SCHINESE]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_TCHINESE_PAL]	= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_TCHINESE]		= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_CZECH]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_THAI]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_HINDI]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH_JA]	= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_TURKISH]		= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_HUNGARIAN]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_PORTUGUESE]	= AplParamState_Invisible;
    }
    else if ( strncmp(model,"AU-EVA1MC",AplParamInfoModel_Size) == 0 )
    {
    	Exclusion[APL_SYS_PARAM_LANGUAGE_JAPANESE]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH_PAL]	= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_GERMAN]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_FRENCH_PAL]	= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_FRENCH]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_ITALIA]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_SPAIN_PAL]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_SPAIN]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_DUTCH]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_SWEDEN]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_POLAND]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_RUSSIA]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_ARABIA]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_PERSIA]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_KOREA]			= AplParamState_Invisible;
    //	Exclusion[APL_SYS_PARAM_LANGUAGE_SCHINESE]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_TCHINESE_PAL]	= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_TCHINESE]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_CZECH]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_THAI]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_HINDI]			= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH_JA]	= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_TURKISH]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_HUNGARIAN]		= AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_LANGUAGE_PORTUGUESE]	= AplParamState_Invisible;
    }
    else
    {
    	switch( APL_PARAM_GET_DATA( AplParamUSeAreaSettings ) )
    	{
    		case APL_SYS_PARAM_USE_AREA_NTSC2:
    		case APL_SYS_PARAM_USE_AREA_PAL:
    			Exclusion[APL_SYS_PARAM_LANGUAGE_JAPANESE]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH_PAL]	= AplParamState_Invisible;
    		//	Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_GERMAN]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_FRENCH_PAL]	= AplParamState_Invisible;
    		//	Exclusion[APL_SYS_PARAM_LANGUAGE_FRENCH]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_ITALIA]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_SPAIN_PAL]		= AplParamState_Invisible;
    		//	Exclusion[APL_SYS_PARAM_LANGUAGE_SPAIN]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_DUTCH]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_SWEDEN]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_POLAND]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_RUSSIA]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_ARABIA]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_PERSIA]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_KOREA]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_SCHINESE]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_TCHINESE_PAL]	= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_TCHINESE]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_CZECH]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_THAI]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_HINDI]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH_JA]	= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_TURKISH]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_HUNGARIAN]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_PORTUGUESE]	= AplParamState_Invisible;
    			break;
    		default:
    			Exclusion[APL_SYS_PARAM_LANGUAGE_JAPANESE]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH_PAL]	= AplParamState_Invisible;
    		//	Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_GERMAN]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_FRENCH_PAL]	= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_FRENCH]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_ITALIA]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_SPAIN_PAL]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_SPAIN]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_DUTCH]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_SWEDEN]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_POLAND]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_RUSSIA]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_ARABIA]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_PERSIA]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_KOREA]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_SCHINESE]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_TCHINESE_PAL]	= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_TCHINESE]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_CZECH]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_THAI]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_HINDI]			= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_ENGLISH_JA]	= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_TURKISH]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_HUNGARIAN]		= AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LANGUAGE_PORTUGUESE]	= AplParamState_Invisible;
    			break;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamLcdEIAssistSpotMeterDisp_ViewType(int id) {
    //#[ operation AplParamLcdEIAssistSpotMeterDisp_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SPOT_MATER_DISP_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SPOT_MATER_DISP_STOP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SPOT_MATER_DISP_PERCENT
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
    if( l == idnum ) return m_Item[AplParamLcdEIAssistSpotMeterDisp].mState;
    // ---------------------------------------------------------
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    		Exclusion[APL_SYS_PARAM_SPOT_MATER_DISP_STOP] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SPOT_MATER_DISP_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLcdEIAssistSpotMeterDisp].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SPOT_MATER_DISP_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamLcdIndicatorMenu_ViewType(int id) {
    //#[ operation AplParamLcdIndicatorMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_LCD_INDICATOR_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_CHAR_LUMINANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_CLIP_NAME
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_PIXEL_FREQ
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_MAIN_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_REC_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_SLOT_STATUS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_2SLOT_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_TC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_BATTERY_REMAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_REC_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_REC_REMOTE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_AUDIO_LEVEL_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_FPS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_SHUTTER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_EI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_WHITE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_IRIS_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_ND_FILTER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_EIS_DZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_WLAN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_INDICATOR_MENU_PLAYBACK_STATUS
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
    if( l == idnum ) return m_Item[AplParamLcdIndicatorMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    // AplParamGrade
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_LCD_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_LCD_INDICATOR_MENU_REC_MODE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_LCD_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			Exclusion[APL_SYS_PARAM_LCD_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			Exclusion[APL_SYS_PARAM_LCD_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			Exclusion[APL_SYS_PARAM_LCD_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			Exclusion[APL_SYS_PARAM_LCD_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_LCD_INDICATOR_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLcdIndicatorMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_LCD_INDICATOR_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamLcdIndicatorRecFuncMode_ViewType(int id) {
    //#[ operation AplParamLcdIndicatorRecFuncMode_ViewType(int)
    // VUP1で有効
    if ( ( APL_PARAM_GET_DATA( AplParamVup ) < APL_SYS_PARAM_VUP_1ST ) &&
    	 ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF ) )
    {
    	return AplParamState_Invisible;
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamLcdMarkerMenu_ViewType(int id) {
    //#[ operation AplParamLcdMarkerMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_LCD_MARKER_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_MARKER_MENU_CENTER_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_MARKER_MENU_SAFETY_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_MARKER_MENU_SAFETY_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_MARKER_MENU_FRAME_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_MARKER_MENU_FRAME_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_LCD_MARKER_MENU_PLAYBACK_MARKER
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamLcdMarkerFrameMarkerColor,
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
    if( l == idnum ) return m_Item[AplParamLcdMarkerMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamLcdMarkerFrameMarkerColor
    switch( APL_PARAM_GET_DATA( AplParamLcdMarkerFrameMarkerColor ) ){
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_WHITE:
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_BLACK:
    		Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_RED:
    		Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_GREEN:
    		Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_BLUE:
    		Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_YELLOW:
    		Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // AplParamVup
    // AplParamGrade
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			Exclusion[APL_SYS_PARAM_LCD_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_LCD_MARKER_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamLcdMarkerMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_LCD_MARKER_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamLimiterCH1_ViewType(int id) {
    //#[ operation AplParamLimiterCH1_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamLimiterCH1].mState;
    // ---------------------------------------------------------
    
    
    // AplParamCh1Adjust
    switch( APL_PARAM_GET_DATA( AplParamCh1Adjust ) ){
    	case APL_SYS_PARAM_CH_ADJUST_MANUAL:
    		break;
    	case APL_SYS_PARAM_CH_ADJUST_AUTO:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_Invisible;
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
    	m_Item[AplParamLimiterCH1].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamLimiterCH2_ViewType(int id) {
    //#[ operation AplParamLimiterCH2_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamLimiterCH2].mState;
    // ---------------------------------------------------------
    
    
    // AplParamCh1Adjust
    switch( APL_PARAM_GET_DATA( AplParamCh2Adjust ) ){
    	case APL_SYS_PARAM_CH_ADJUST_MANUAL:
    		break;
    	case APL_SYS_PARAM_CH_ADJUST_AUTO:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_Invisible;
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
    	m_Item[AplParamLimiterCH2].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamMyMacAddress_ViewType(int id) {
    //#[ operation AplParamMyMacAddress_ViewType(int)
    // 常時グレー表示
    return AplParamState_VisibleInvalid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamMySecurityType_ViewType(int id) {
    //#[ operation AplParamMySecurityType_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_NONE
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WEP
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WPA_TKIP
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WPA_AES
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WPA2_TKIP
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_WPA2_AES
    	AplParamState_VisibleValid,	// APL_NET_PARAM_SECURITY_TYPE_AUTO
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
    if( l == idnum ) return m_Item[AplParamMySecurityType].mState;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_NONE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WEP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA_TKIP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA_AES] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_WPA2_TKIP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_NET_PARAM_SECURITY_TYPE_AUTO] = AplParamState_VisibleInvalid;
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
    for( int i = 0 ; i < APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamMySecurityType].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_NET_PARAM_SECURITY_TYPE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamNativeISO_ViewType(int id) {
    //#[ operation AplParamNativeISO_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_NATIVE_ISO_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NATIVE_ISO_800
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NATIVE_ISO_3200
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NATIVE_ISO_2500
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NATIVE_ISO_400
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NATIVE_ISO_1250
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamISOSelect,
    	AplParamSceneGammaSelect,
    	AplParamGainIsoDispChg,
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
    if( l == idnum ) return m_Item[AplParamNativeISO].mState;
    // ---------------------------------------------------------
    
    
    // AplParamISOSelect
    switch( APL_PARAM_GET_DATA( AplParamISOSelect ) ){
    	case APL_SYS_PARAM_ISO_SELECT_NATIVE_ONLY:
    		break;
    	case APL_SYS_PARAM_ISO_SELECT_800BASE:
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_2500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_ISO_SELECT_3200BASE:
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_2500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_ISO_SELECT_2500BASE:
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_2500] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSdiRaw
    switch ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) )
    {
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_800] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_2500] = AplParamState_VisibleInvalid;
    		break;
    
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    			case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V255570L1:
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    				break;
    			case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V504580L1:
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    				break;
    			case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VXXXXXXL1:
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    				break;
    			case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_800] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_2500] = AplParamState_Invisible;
    				break;
    			case APL_SYS_PARAM_SCENE_GAMMA_SELECT_HLG:
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    				Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    				break;
    			default:
    				break;
    		}
    		break;
    
    	default:
    		// AplParamSceneGammaSelect
    		// Bug6768 2.2Kモード時のEI仕様変更（減感対応）
    		if( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K )
    		{
    			Exclusion[APL_SYS_PARAM_NATIVE_ISO_800] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_NATIVE_ISO_2500] = AplParamState_VisibleInvalid;
    		}
    		else
    		{
    			switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    				case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V255570L1:
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    					break;
    				case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V504580L1:
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    					break;
    				case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VXXXXXXL1:
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    					break;
    				case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_800] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_2500] = AplParamState_Invisible;
    					break;
    				case APL_SYS_PARAM_SCENE_GAMMA_SELECT_HLG:
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    					Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    					break;
    				default:
    					break;
    			}
    		}
    		break;
    }
    
    // AplParamGainIsoDispChg
    switch( APL_PARAM_GET_DATA( AplParamGainIsoDispChg ) ){
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_GAIN:
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_800] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_3200] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_2500] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_400] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_NATIVE_ISO_1250] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_GAIN_ISO_DISP_CHG_ISO:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NATIVE_ISO_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamNativeISO].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_NATIVE_ISO_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamNetworkPropertyMenu_ViewType(int id) {
    //#[ operation AplParamNetworkPropertyMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_NETWORK_PROPERTY_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_MAC_ADDRESS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_TYPE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_SSID
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_BAND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_CHANNEL_24
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_CHANNEL_5
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_ENCRYPTION
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_ENCRYPT_KEY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_DHCP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_IP_ADDRESS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_SUB_NET_MASK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_DEFAULT_GATE_WAY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_PRIMARY_DNS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_NETWORK_PROPERTY_MENU_SECONDARY_DNS
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWlanMode,
    	AplParamDhcpMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamNetworkPropertyMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamWlanMode
    switch( APL_PARAM_GET_DATA( AplParamWlanMode ) ){
    	case APL_NET_PARAM_WLAN_MODE_DIRECT:
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_MAC_ADDRESS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_ENCRYPTION] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_SELECT:
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_MAC_ADDRESS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_SSID] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_BAND] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_CHANNEL_24] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_CHANNEL_5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_INFRA_MANUAL:
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_MAC_ADDRESS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_BAND] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_CHANNEL_24] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_CHANNEL_5] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_WLAN_MODE_NONE:
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_MAC_ADDRESS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_BAND] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_CHANNEL_24] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_CHANNEL_5] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamDhcpMode
    switch( APL_PARAM_GET_DATA( AplParamDhcpMode ) ){
    	case APL_NET_PARAM_DHCP_MODE_OFF:
    		break;
    	case APL_NET_PARAM_DHCP_MODE_CLIENT:
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_IP_ADDRESS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_SUB_NET_MASK] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_NETWORK_PROPERTY_MENU_DEFAULT_GATE_WAY] = AplParamState_VisibleInvalid;
    		break;
    	case APL_NET_PARAM_DHCP_MODE_SERVER:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_NETWORK_PROPERTY_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamNetworkPropertyMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_NETWORK_PROPERTY_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamOutIndicatorMenu_ViewType(int id) {
    //#[ operation AplParamOutIndicatorMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_OUT_INDICATOR_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_CHAR_LUMINANCE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_CLIP_NAME
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_PIXEL_FREQ
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_MAIN_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_REC_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_SLOT_STATUS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_2SLOT_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_TC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_BATTERY_REMAIN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_REC_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_REC_REMOTE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_AUDIO_LEVEL_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_FPS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_SHUTTER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_EI
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_WHITE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_IRIS_ZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_ND_FILTER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_EIS_DZOOM
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_WLAN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_IR_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_SPOT_METER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_INDICATOR_MENU_PLAYBACK_STATUS
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
    if( l == idnum ) return m_Item[AplParamOutIndicatorMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_OUT_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_OUT_INDICATOR_MENU_REC_MODE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_OUT_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			Exclusion[APL_SYS_PARAM_OUT_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			Exclusion[APL_SYS_PARAM_OUT_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			Exclusion[APL_SYS_PARAM_OUT_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			Exclusion[APL_SYS_PARAM_OUT_INDICATOR_MENU_CHAR_LUMINANCE] = AplParamState_Invisible;
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_OUT_INDICATOR_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamOutIndicatorMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_OUT_INDICATOR_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamOutIndicatorRecFuncMode_ViewType(int id) {
    //#[ operation AplParamOutIndicatorRecFuncMode_ViewType(int)
    // VUP1で有効
    if ( ( APL_PARAM_GET_DATA( AplParamVup ) < APL_SYS_PARAM_VUP_1ST ) &&
    	 ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF ) )
    {
    	return AplParamState_Invisible;
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamOutMarkerMenu_ViewType(int id) {
    //#[ operation AplParamOutMarkerMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_OUT_MARKER_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_MARKER_MENU_CENTER_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_MARKER_MENU_SAFETY_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_MARKER_MENU_SAFETY_AREA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_MARKER_MENU_FRAME_MARKER
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_MARKER_MENU_FRAME_COLOR
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_OUT_MARKER_MENU_PLAYBACK_MARKER
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamOutMarkerFrameMarkerColor,
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
    if( l == idnum ) return m_Item[AplParamOutMarkerMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamOutMarkerFrameMarkerColor
    switch( APL_PARAM_GET_DATA( AplParamOutMarkerFrameMarkerColor ) ){
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_WHITE:
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_BLACK:
    		Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_RED:
    		Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_GREEN:
    		Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_BLUE:
    		Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_FRAMEMARKER_COLOR_YELLOW:
    		Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // AplParamVup
    // AplParamGrade
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_2ND:
    			Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_3RD:
    			Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_4TH:
    			Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_5TH:
    			Exclusion[APL_SYS_PARAM_OUT_MARKER_MENU_MARKER_LUMINANVE] = AplParamState_Invisible;
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_OUT_MARKER_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamOutMarkerMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_OUT_MARKER_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamPreRec_ViewType(int id) {
    //#[ operation AplParamPreRec_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVFRMode,
    	AplParamRecFunctionMode,
    	AplParamRelayBackup,
    	AplParamSystemSdiRaw,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamPreRec].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVFRMode
    switch( APL_PARAM_GET_DATA( AplParamVFRMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC:
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    	m_Item[AplParamPreRec].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamRecFunctionMode_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamRecFunctionMode].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVFRMode
    switch( APL_PARAM_GET_DATA( AplParamVFRMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSubRec
    switch( APL_PARAM_GET_DATA( AplParamSystemSubRec ) ){
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRelayBackup
    switch( APL_PARAM_GET_DATA( AplParamRelayBackup ) ){
    	case APL_SYS_PARAM_RELAY_BACKUP_OFF:
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_RELAY:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC:
    		break;
    	default:
    		break;
    }
    
    // SYSTEM FREQUENCY
    switch ( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) )
    {
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }		
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    	case APL_SYS_PARAM_VUP_NONE:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_Invisible;
    		}
    		break;
    	case APL_SYS_PARAM_VUP_1ST:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamRecFunctionOneShotTime_ViewType(int id) {
    //#[ operation AplParamRecFunctionOneShotTime_ViewType(int)
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
    if( l == idnum ) return m_Item[AplParamRecFunctionOneShotTime].mState;
    
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			return AplParamState_Invisible;
    		case APL_SYS_PARAM_VUP_1ST:
    			return AplParamState_Invisible;
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
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamRecFunctionStartDelay_ViewType(int id) {
    //#[ operation AplParamRecFunctionStartDelay_ViewType(int)
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
    if( l == idnum ) return m_Item[AplParamRecFunctionStartDelay].mState;
    
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			return AplParamState_Invisible;
    		case APL_SYS_PARAM_VUP_1ST:
    			return AplParamState_Invisible;
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
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamRecSettingMenu_ViewType(int id) {
    //#[ operation AplParamRecSettingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_REC_SETTINGS_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_SETTINGS_MENU_CARDS_MEDIA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_SETTINGS_MENU_CLIP_NAME
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_SETTINGS_MENU_2SLOTS_FUNC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_SETTINGS_MENU_PRE_REC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_SETTINGS_MENU_REC_FUNCTION
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_SETTINGS_MENU_TC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_REC_SETTINGS_MENU_TIME_STAMP
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
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
    if( l == idnum ) return m_Item[AplParamRecSettingMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_2SLOTS_FUNC] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_PRE_REC] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_REC_FUNCTION] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_TIME_STAMP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_2SLOTS_FUNC] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_PRE_REC] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_REC_FUNCTION] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_TIME_STAMP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_2SLOTS_FUNC] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_PRE_REC] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_REC_FUNCTION] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_TIME_STAMP] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVup
    switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    	case APL_SYS_PARAM_VUP_NONE:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_REC_FUNCTION] = AplParamState_Invisible;
    		}
    		break;
    	case APL_SYS_PARAM_VUP_1ST:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[APL_SYS_PARAM_REC_SETTINGS_MENU_TIME_STAMP] = AplParamState_Invisible;
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
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_REC_SETTINGS_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamRecSettingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_REC_SETTINGS_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamRelayBackup_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamRelayBackup].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSubRec
    switch( APL_PARAM_GET_DATA( AplParamSystemSubRec ) ){
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVFRMode
    switch( APL_PARAM_GET_DATA( AplParamVFRMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) ){
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    	default:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K:
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    		if ( APL_PARAM_GET_DATA( AplParamVFRMode ) == APL_SYS_PARAM_SWITCH_ON )
    		{
    			Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    			Exclusion[APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC] = AplParamState_VisibleInvalid;
    		}
    		break;
    }
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_RELAY] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_SIMUL] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVup
    switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    	case APL_SYS_PARAM_VUP_NONE:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_Invisible;
    		}
    		break;
    	case APL_SYS_PARAM_VUP_1ST:
    		if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    		{
    			Exclusion[APL_SYS_PARAM_RELAY_BACKUP_BACKUP] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamSceneFileGammaMenu_ViewType(int id) {
    //#[ operation AplParamSceneFileGammaMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_GAMMA_SELECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_MASTER_GAMMA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_BLACK_GAMMA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_B_GAMMA_RANGE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneGammaSelect,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSceneFileGammaMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSceneGammaSelect
    switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V255570L1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_MASTER_GAMMA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_BLACK_GAMMA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_B_GAMMA_RANGE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V504580L1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_MASTER_GAMMA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_BLACK_GAMMA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_B_GAMMA_RANGE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VXXXXXXL1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_MASTER_GAMMA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_BLACK_GAMMA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_B_GAMMA_RANGE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_HLG:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_MASTER_GAMMA] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSceneFileGammaMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SCENE_FILE_GAMMA_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSceneFileHlgKneeMenu_ViewType(int id) {
    //#[ operation AplParamSceneFileHlgKneeMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_POINT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SLOPE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneGammaSelect,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSceneFileHlgKneeMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSceneGammaSelect
    switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V255570L1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_MODE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_POINT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SLOPE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V504580L1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_MODE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_POINT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SLOPE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VXXXXXXL1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_MODE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_POINT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SLOPE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_MODE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_POINT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_SLOPE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_HLG:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSceneFileHlgKneeMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SCENE_FILE_HLG_KNEE_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSceneFileSettingMenu_ViewType(int id) {
    //#[ operation AplParamSceneFileSettingMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_NAME_EDIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_SCENE_DATA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_BLACK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_GAMUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_GAMMA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_KNEE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_HLG_KNEE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_WHITE_CLIP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_DETAIL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_SKIN_DETAIL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_CHROMA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_MATRIX
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_COLOR_CORRECTION
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorMain,
    	AplParamSceneGammaSelect,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSceneFileSettingMenu].mState;
    // ---------------------------------------------------------
    
    // AplParamSceneGammaSelect
    switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V255570L1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_KNEE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_HLG_KNEE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_WHITE_CLIP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V504580L1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_KNEE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_HLG_KNEE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_WHITE_CLIP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VXXXXXXL1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_KNEE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_HLG_KNEE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_WHITE_CLIP] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_HLG_KNEE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_HLG:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_KNEE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_WHITE_CLIP] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SCENE_FILE_SETTINGS_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSceneFileSettingMenu].sub_item[i].state =  Exclusion[i];
    }
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		return AplParamState_VisibleInvalid;
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE1:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE2:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE3:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE4:
    	case APL_SYS_PARAM_COLOR_MAIN_SCENE5:
    	default:
    		return AplParamState_VisibleValid;
    }
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSceneFileWhiteClipMenu_ViewType(int id) {
    //#[ operation AplParamSceneFileWhiteClipMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_LEVEL
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSceneGammaSelect,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSceneFileWhiteClipMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSceneGammaSelect
    switch( APL_PARAM_GET_DATA( AplParamSceneGammaSelect ) ){
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V255570L1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_LEVEL] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_V504580L1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_LEVEL] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VXXXXXXL1:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_LEVEL] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_VIDEO:
    		break;
    	case APL_SYS_PARAM_SCENE_GAMMA_SELECT_HLG:
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_SW] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_LEVEL] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSceneFileWhiteClipMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SCENE_FILE_WHITE_CLIP_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSDIOut_ViewType(int id) {
    //#[ operation AplParamSDIOut_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamSDIOut].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
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
    	m_Item[AplParamSDIOut].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSdiOutFormat_ViewType(int id) {
    //#[ operation AplParamSdiOutFormat_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_FORMAT_4096_2160P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_FORMAT_3840_2160P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080I
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_FORMAT_1280_720P
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamSdiOutSignalSelect,
    	AplParamSystemModeFrequency,
    	AplParamSystemMainPixel,
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
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
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
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    			//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    				break;
    
    			case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    			//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    				Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
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
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
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
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
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
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
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
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
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
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					default:
    						break;
    				}
    				break;
    
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    				switch ( APL_PARAM_GET_DATA( AplParamSdiOutSignalSelect ) )
    				{
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
    						break;
    
    					case APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI:
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P]		= AplParamState_VisibleInvalid;				
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P]		= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I]		= AplParamState_VisibleInvalid;
    					//	Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF]	= AplParamState_VisibleInvalid;
    						Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P]		= AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_4096_2160P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_3840_2160P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080I] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1920_1080PsF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_FORMAT_1280_720P] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
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
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SDI_FORMAT_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSdiOutIndicatorDisp_ViewType(int id) {
    //#[ operation AplParamSdiOutIndicatorDisp_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamSdiOutIndicatorDisp].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    	m_Item[AplParamSdiOutIndicatorDisp].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSdiOutMarkerDisp_ViewType(int id) {
    //#[ operation AplParamSdiOutMarkerDisp_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamSdiOutMarkerDisp].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    	m_Item[AplParamSdiOutMarkerDisp].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSdiOutMenuDisp_ViewType(int id) {
    //#[ operation AplParamSdiOutMenuDisp_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamSdiOutMenuDisp].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // AplParamPlayMode
    switch( APL_PARAM_GET_DATA( AplParamPlayMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    	m_Item[AplParamSdiOutMenuDisp].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSdiOutSignalSelect_ViewType(int id) {
    //#[ operation AplParamSdiOutSignalSelect_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SDI_SIGNAL_SEL_MAX + 1 ] = {
    	AplParamState_Invisible,	// APL_SYS_PARAM_SDI_SIGNAL_SEL_NORMAL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SDI_SIGNAL_SEL_SDI
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
    if( l == idnum ) return m_Item[AplParamSdiOutSignalSelect].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SDI_SIGNAL_SEL_1080P] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SDI_SIGNAL_SEL_1080I] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SDI_SIGNAL_SEL_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSdiOutSignalSelect].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SDI_SIGNAL_SEL_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSdiRemote_ViewType(int id) {
    //#[ operation AplParamSdiRemote_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamSdiRemote].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
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
    	m_Item[AplParamSdiRemote].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamShutterDispChg_ViewType(int id) {
    //#[ operation AplParamShutterDispChg_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SHUTTER_DISP_CHG_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_DISP_CHG_DEGREE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamShutterSwitch,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamShutterDispChg].mState;
    // ---------------------------------------------------------
    
    
    // AplParamShutterSwitch
    switch( APL_PARAM_GET_DATA( AplParamShutterSwitch ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_DISP_CHG_DEGREE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SHUTTER_DISP_CHG_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamShutterDispChg].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SHUTTER_DISP_CHG_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamShutterDegValue_ViewType(int id) {
    //#[ operation AplParamShutterDegValue_ViewType(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamShutterDispChg,
    	AplParamShutterSwitch,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamVFRValue].mState;
    // ---------------------------------------------------------
    
    
    // AplParamShutterDispChg
    switch( APL_PARAM_GET_DATA( AplParamShutterDispChg ) ){
    	case APL_SYS_PARAM_SHUTTER_DISP_CHG_DEGREE:
    		if( APL_PARAM_GET_DATA( AplParamShutterSwitch ) == APL_SYS_PARAM_SWITCH_OFF ){
    			return AplParamState_VisibleInvalid;
    		}else{
    			return AplParamState_VisibleValid;
    		}
    	case APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND:
    	default:
    		return AplParamState_Invisible;
    }
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamShutterMenu_ViewType(int id) {
    //#[ operation AplParamShutterMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SHUTTER_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_SW
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_SEC_VALUE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_SEC_ADD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_SEC_EDIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_SEC_DELETE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_DEG_VALUE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_DEG_ADD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_DEG_EDIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_DEG_DELETE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_VALUE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_ADD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_EDIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SHUTTER_MENU_DELETE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamShutterDispChg,
    	AplParamShutterDegValueIndex,
    	AplParamShutterSecValueIndex,
       	AplParamShutterSwitch,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamShutterMenu].mState;
    // ---------------------------------------------------------
    
    // ADD DEG
    bool bFull = true;
    for( int i = 1 ; i < 12 ; i++ )
    {
    	if ( APL_PARAM_GET_DATA(AplParamShutterDegValueHalf + i) == 0 )
    	{
    		bFull = false;
    		break;
    	}
    }
    if ( bFull == true )
    {
    	Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_ADD] = AplParamState_VisibleInvalid;
    }
    
    // ADD SEC
    bFull = true;
    for( int i = 1 ; i < 12 ; i++ )
    {
    	if ( APL_PARAM_GET_DATA(AplParamShutterSecValueHalf + i) == 0 )
    	{
    		bFull = false;
    		break;
    	}
    }
    if ( bFull == true )
    {
    	Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_ADD] = AplParamState_VisibleInvalid;
    }
    
    if ( APL_PARAM_GET_DATA( AplParamShutterDegValueIndex ) == 0 /* HALF SHUTTER */ )
    {
    	Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_EDIT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_DELETE] = AplParamState_VisibleInvalid;
    }
    
    if ( APL_PARAM_GET_DATA( AplParamShutterSecValueIndex ) == 0 /* HALF SHUTTER */ )
    {
    	Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_EDIT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_DELETE] = AplParamState_VisibleInvalid;
    }
    
    // AplParamShutterSwitch
    switch( APL_PARAM_GET_DATA( AplParamShutterSwitch ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_MODE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_VALUE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_ADD] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_EDIT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_DELETE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_VALUE] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_ADD] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_EDIT] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_DELETE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    // AplParamShutterDispChg
    switch( APL_PARAM_GET_DATA( AplParamShutterDispChg ) ){
    	case APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND:
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_VALUE] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_ADD] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_EDIT] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_DEG_DELETE] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_SHUTTER_DISP_CHG_DEGREE:
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_VALUE] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_ADD] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_EDIT] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SHUTTER_MENU_SEC_DELETE] = AplParamState_Invisible;
    		break;
    	default:
    		break;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SHUTTER_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamShutterMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SHUTTER_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamShutterSecValue_ViewType(int id) {
    //#[ operation AplParamShutterSecValue_ViewType(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamShutterDispChg,
    	AplParamShutterSwitch,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamVFRValue].mState;
    // ---------------------------------------------------------
    
    
    // AplParamShutterDispChg
    switch( APL_PARAM_GET_DATA( AplParamShutterDispChg ) ){
    	case APL_SYS_PARAM_SHUTTER_DISP_CHG_SECOND:
    		if( APL_PARAM_GET_DATA( AplParamShutterSwitch ) == APL_SYS_PARAM_SWITCH_OFF ){
    			return AplParamState_VisibleInvalid;
    		}else{
    			return AplParamState_VisibleValid;
    		}
    	case APL_SYS_PARAM_SHUTTER_DISP_CHG_DEGREE:
    	default:
    		return AplParamState_Invisible;
    }
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSubnet_ViewType(int id) {
    //#[ operation AplParamSubnet_ViewType(int)
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamDhcpMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSubnet].mState;
    // ---------------------------------------------------------
    
    
    // AplParamDhcpMode
    switch( APL_PARAM_GET_DATA( AplParamDhcpMode ) ){
    	case APL_NET_PARAM_DHCP_MODE_CLIENT:
    		return AplParamState_Invisible;
    	case APL_NET_PARAM_DHCP_MODE_OFF:
    	case APL_NET_PARAM_DHCP_MODE_SERVER:
    	default:
    		return AplParamState_VisibleValid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSystemMainCodec_ViewType(int id) {
    //#[ operation AplParamSystemMainCodec_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemModeFrequency,
    	AplParamSystemSdiRaw,
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
    if( l == idnum ) return m_Item[AplParamSystemMainCodec].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSensorMode
    switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) ){
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemMainPixel
    switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		if ( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ &&
    			 APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ &&
    			 APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ )
    		{
    			Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		}
    		if ( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ &&
    			 APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) != APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ )
    		{
    			Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
    		}
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_150M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PS] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA] = AplParamState_VisibleInvalid;
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
    				Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
    				break;
    			
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    			case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    				if ( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K )
    				{
    					Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
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
    					Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_CODEC_420LONGGOP_100M] = AplParamState_VisibleInvalid;
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
    				Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422LONGGOP_50M  ] = AplParamState_Invisible;
    			}
    			Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_400M  ] = AplParamState_Invisible;
    			Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_200M  ] = AplParamState_Invisible;
    			Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_CODEC_422INTRA_100M  ] = AplParamState_Invisible;
    			break;
    						
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_MAIN_CODEC_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSystemMainCodec].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_MAIN_CODEC].state = AplParamState_VisibleValid;
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SYSTEM_MAIN_CODEC_MAX + 1 ){
    		m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_MAIN_CODEC].state = AplParamState_Invisible;
    		return AplParamState_Invisible;
    	}
    	m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_MAIN_CODEC].state = AplParamState_VisibleInvalid;
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSystemMainPixel_ViewType(int id) {
    //#[ operation AplParamSystemMainPixel_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemModeFrequency,
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
    if( l == idnum ) return m_Item[AplParamSystemMainPixel].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSensorMode
    switch( APL_PARAM_GET_DATA( AplParamSystemSensorMode ) ){
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSystemMainPixel].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_MAIN_PIXEL].state = AplParamState_VisibleValid;
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_MAX + 1 ){
    		m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_MAIN_PIXEL].state = AplParamState_Invisible;
    		return AplParamState_Invisible;
    	}
    		m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_MAIN_PIXEL].state = AplParamState_VisibleInvalid;
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSystemSdiRaw_ViewType(int id) {
    //#[ operation AplParamSystemSdiRaw_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SYSTEM_SDI_RAW_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemModeFrequency,
    	AplParamVup,
    	AplParamGrade,
    	AplParamDeckMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSystemSdiRaw].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    // VUP1で有効
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	if ( APL_PARAM_GET_DATA( AplParamVup ) < APL_SYS_PARAM_VUP_1ST )
    	{
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K] = AplParamState_Invisible;
    	}
    }
    
    // AplParamDeckMode
    switch( APL_PARAM_GET_DATA( AplParamDeckMode ) ){
    case APL_SYS_PARAM_DECK_MODE_PLAY:
    	Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K] = AplParamState_VisibleInvalid;
    	break;
    default:
    	break;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_SDI_RAW_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSystemSdiRaw].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_SDI_RAW].state = AplParamState_VisibleValid;
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SYSTEM_SDI_RAW_MAX + 1 ){
    		m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_SDI_RAW].state = AplParamState_Invisible;
    		return AplParamState_Invisible;
    	}
    	
    	m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_SDI_RAW].state = AplParamState_VisibleInvalid;
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSystemSensorMode_ViewType(int id) {
    //#[ operation AplParamSystemSensorMode_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SYSTEM_SENSOR_MODE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemSdiRaw,
    	AplParamSystemModeFrequency,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamSystemSensorMode].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_57K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_S35_MIX_28K] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SENSOR_MODE_4_3_CROPMIX_22K] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_SENSOR_MODE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSystemSensorMode].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_SENSOR_MODE].state = AplParamState_VisibleValid;
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SYSTEM_SENSOR_MODE_MAX + 1 ){
    		m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_SENSOR_MODE].state = AplParamState_Invisible;
    		return AplParamState_Invisible;
    	}
    	m_Item[AplParamSystemModeMenu].sub_item[APL_SYS_PARAM_SYSTEM_MODE_MENU_SENSOR_MODE].state = AplParamState_VisibleInvalid;
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSystemSettingsMenu_ViewType(int id) {
    //#[ operation AplParamSystemSettingsMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SYSTE_SETTINGS_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_SYSTEM_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_COLOR_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_USER_SWITCHES
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_SIDE_LOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_LED_FAN
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_LCD_DISPLAY
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_CLOCK
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_INFORMATION
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_LANGUAGE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTE_SETTINGS_MENU_INITIALIZE
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
    if( l == idnum ) return m_Item[AplParamSystemSettingsMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamUSeAreaSettings
    char model[AplParamInfoModel_Size] = {0};
    APL_PARAM_GET_DATA_AREA(AplParamInfoModel,(UB*)model,AplParamInfoModel_Size);
    if( strncmp(model,"AU-EVA1",AplParamInfoModel_Size) == 0 )
    {
    	switch( APL_PARAM_GET_DATA( AplParamUSeAreaSettings ) ){
    		case APL_SYS_PARAM_USE_AREA_NTSC1:
    			Exclusion[APL_SYS_PARAM_SYSTE_SETTINGS_MENU_LANGUAGE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_USE_AREA_NTSC2:
    			break;
    		case APL_SYS_PARAM_USE_AREA_PAL:
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTE_SETTINGS_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSystemSettingsMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SYSTE_SETTINGS_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamSystemSubRec_ViewType(int id) {
    //#[ operation AplParamSystemSubRec_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SYSTEM_SUB_REC_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SUB_REC_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemModeFrequency,
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
    if( l == idnum ) return m_Item[AplParamSystemSubRec].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemMainPixel
    switch( APL_PARAM_GET_DATA( AplParamSystemMainPixel ) ){
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_4096_2160:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_3840_2160:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_2048_1080:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1920_1080:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_PIXEL_1280_720:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRelayBackup
    switch( APL_PARAM_GET_DATA( AplParamRelayBackup ) ){
    	case APL_SYS_PARAM_RELAY_BACKUP_OFF:
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_RELAY:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_BACKUP:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_SIMUL:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_RELAY_BACKUP_DUAL_CODEC:
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_VisibleInvalid;
    		Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_OFF] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_OFF] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M] = AplParamState_Invisible;
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
    for( int i = 0 ; i < APL_SYS_PARAM_SYSTEM_SUB_REC_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamSystemSubRec].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SYSTEM_SUB_REC_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamTCG_ViewType(int id) {
    //#[ operation AplParamTCG_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_TCG_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCG_FREE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCG_REC
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
    if( l == idnum ) return m_Item[AplParamTCG].mState;
    // ---------------------------------------------------------
    
    
    // AplParamPreRec
    switch( APL_PARAM_GET_DATA( AplParamPreRec ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_TCG_REC] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamRecFunctionMode
    switch( APL_PARAM_GET_DATA( AplParamRecFunctionMode ) ){
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_NORMAL:
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_INTERVAL:
    		Exclusion[APL_SYS_PARAM_TCG_FREE] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_TCG_FREE] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_TCG_REC] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_TCG_FREE] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_TCG_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamTCG].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_TCG_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamTCMenu_ViewType(int id) {
    //#[ operation AplParamTCMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_TC_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TC_MENU_SET_TC
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TC_MENU_SET_UB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TC_MENU_COUNTER_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TC_MENU_TCG
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TC_MENU_TC_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TC_MENU_UB_MODE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TC_MENU_TC_IN_OUT_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TC_MENU_TC_OUT_REF
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUsersBitMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamTCMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamUsersBitMode
    switch( APL_PARAM_GET_DATA( AplParamUsersBitMode ) ){
    	case APL_SYS_PARAM_UB_MODE_FRAME_RATE:
    		Exclusion[APL_SYS_PARAM_TC_MENU_SET_UB] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_UB_MODE_USER:
    		break;
    	case APL_SYS_PARAM_UB_MODE_TIME:
    		Exclusion[APL_SYS_PARAM_TC_MENU_SET_UB] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_UB_MODE_DATE:
    		Exclusion[APL_SYS_PARAM_TC_MENU_SET_UB] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_UB_MODE_CLIP_NAME:
    		Exclusion[APL_SYS_PARAM_TC_MENU_SET_UB] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_TC_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamTCMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_TC_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamTCMode_ViewType(int id) {
    //#[ operation AplParamTCMode_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_TCMODE_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCMODE_DF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TCMODE_NDF
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemModeFrequency,
    	AplParamRecFunctionMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamTCMode].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = AplParamState_VisibleInvalid;
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
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_ONE_SHOT:
    		Exclusion[APL_SYS_PARAM_TCMODE_DF] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_REC_FUNCTION_MODE_LOOP:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_TCMODE_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamTCMode].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_TCMODE_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamTimeStamp_ViewType(int id) {
    //#[ operation AplParamTimeStamp_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamTimeStamp].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemSubRec
    switch( APL_PARAM_GET_DATA( AplParamSystemSubRec ) ){
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_12M:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_12M:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_2480_1080_6M:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SUB_REC_1920_1080_6M:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVFRMode
    switch( APL_PARAM_GET_DATA( AplParamVFRMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_COLOR_MAIN_DUMMY:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    
    
    // AplParamSystemSdiRaw
    switch( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) ){
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF:
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_S35_57K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_4K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_SDI_RAW_CROP_MIX_2K:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_Invisible;
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_Invisible;
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
    for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamTimeStamp].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamTopMenu_ViewType(int id) {
    //#[ operation AplParamTopMenu_ViewType(int)
    /* TODO:EE画面やTHUMB画面で出さないものは対応必要 */
    int validnum = 0;
    int invisiblenum = 0;
    char model[AplParamInfoModel_Size] = {0};
    AplParamState Exclusion[ APL_SYS_PARAM_TOP_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_THUMBNAIL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_SYSTEM_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_CAMERA_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_SCENE_FILE_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_REC_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_AUDIO_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_OUTPUT_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_FILE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_NETWORK_SETTINGS
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_TOP_MENU_OPTION
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorMain,
    	AplParamInfoModel,
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
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		Exclusion[APL_SYS_PARAM_TOP_MENU_SCENE_FILE_SETTINGS] = AplParamState_VisibleInvalid;
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
    
    // AplParamPlayMode
    switch( APL_PARAM_GET_DATA( AplParamPlayMode ) ){
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_TOP_MENU_CAMERA_SETTINGS] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_TOP_MENU_SCENE_FILE_SETTINGS] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_TOP_MENU_THUMBNAIL] = AplParamState_Invisible;
    		break;
    	default:
    		break;
    }
    
    //モデル名判定
    APL_PARAM_GET_DATA_AREA(AplParamInfoModel,(UB*)model,AplParamInfoModel_Size);
    if( strncmp(model,"AU-EVA1",AplParamInfoModel_Size) == 0 && APL_PARAM_GET_DATA( AplParamOptionMenuDisp ) == APL_SYS_PARAM_SWITCH_ON )
    {
    	Exclusion[APL_SYS_PARAM_TOP_MENU_THUMBNAIL] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_SYSTEM_SETTINGS] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_CAMERA_SETTINGS] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_SCENE_FILE_SETTINGS] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_REC_SETTINGS] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_AUDIO_SETTINGS] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_OUTPUT_SETTINGS] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_FILE] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_TOP_MENU_NETWORK_SETTINGS] = AplParamState_Invisible;
    }
    else
    {
    	Exclusion[APL_SYS_PARAM_TOP_MENU_OPTION] = AplParamState_Invisible;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_TOP_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamTopMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 1 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_TOP_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamTouchAfSw_ViewType(int id) {
    //#[ operation AplParamTouchAfSw_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
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
    if( l == idnum ) return m_Item[AplParamTouchAfSw].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    // AplParamGrade
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	Exclusion[APL_SYS_PARAM_SWITCH_OFF] = AplParamState_Invisible;
    	Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_Invisible;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamTouchAfSw].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton1_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton1].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton2_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton2].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton3_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton3].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton4_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton4].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton5_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton5].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton6_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton6].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton7_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton7].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton8_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton8].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamUserButton9_ViewType(int id) {
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
    if( l == idnum ) return m_Item[AplParamUserButton9].mState;
    // ---------------------------------------------------------
    
    
    // AplParamVup
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	switch( APL_PARAM_GET_DATA( AplParamVup ) ){
    		case APL_SYS_PARAM_VUP_NONE:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
    			break;
    		case APL_SYS_PARAM_VUP_1ST:
    			Exclusion[APL_SYS_PARAM_USER_BUTTON_BACKGR_PAUSE] = AplParamState_Invisible;
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

AplParamState AplParamMainItemTypeFuncK460::AplParamVFRMode_ViewType(int id) {
    //#[ operation AplParamVFRMode_ViewType(int)
    // Bug4570
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamSystemModeFrequency,
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
    if( l == idnum ) return m_Item[AplParamVFRMode].mState;
    // ---------------------------------------------------------
    
    
    // AplParamSystemModeFrequency
    switch( APL_PARAM_GET_DATA( AplParamSystemModeFrequency ) ){
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_2398pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_24pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_25pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_30pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60pHZ:
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_50iHZ:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	case APL_SYS_PARAM_SYSTEM_MODE_FREQUENCY_60iHZ:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    		break;
    	default:
    		break;
    }
    
    
    // AplParamSystemMainCodec
    // AplParamSystemSdiRaw
    if ( APL_PARAM_GET_DATA( AplParamSystemSdiRaw ) == APL_SYS_PARAM_SYSTEM_SDI_RAW_OFF )
    {
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
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PH:
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_HA:
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    			break;
    		case APL_SYS_PARAM_SYSTEM_MAIN_CODEC_PM:
    			Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
    			break;
    		default:
    			break;
    	}
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_SWITCH_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamVFRMode].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamVFRValue_ViewType(int id) {
    //#[ operation AplParamVFRValue_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVFRMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamVFRValue].mState;
    // ---------------------------------------------------------
    
    // AplParamVFRMode
    switch( APL_PARAM_GET_DATA( AplParamVFRMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		return AplParamState_VisibleInvalid;
    	case APL_SYS_PARAM_SWITCH_ON:
    	default:
    		return AplParamState_VisibleValid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamVFRValueIndex_ViewType(int id) {
    //#[ operation AplParamVFRValueIndex_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVFRMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamVFRValue].mState;
    // ---------------------------------------------------------
    
    // AplParamVFRMode
    switch( APL_PARAM_GET_DATA( AplParamVFRMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		return AplParamState_VisibleInvalid;
    	case APL_SYS_PARAM_SWITCH_ON:
    	default:
    		return AplParamState_VisibleValid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamWhiteMenu_ViewType(int id) {
    //#[ operation AplParamWhiteMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_WHITE_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WHITE_MENU_AWB
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WHITE_MENU_VALUE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WHITE_MENU_ADD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WHITE_MENU_EDIT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WHITE_MENU_DELETE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWhiteValueIndex,
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
    if( l == idnum ) return m_Item[AplParamWhiteMenu].mState;
    // ---------------------------------------------------------
    
    
    // AplParamWhiteValueTemp
    if( APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) == 0 /* ATW */ ||
    	APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) == 1 /* AWB MEMORY */ ){
    	Exclusion[APL_SYS_PARAM_WHITE_MENU_EDIT] = AplParamState_VisibleInvalid;
    	Exclusion[APL_SYS_PARAM_WHITE_MENU_DELETE] = AplParamState_VisibleInvalid;
    }
    
    if ( APL_PARAM_GET_DATA( AplParamWhiteValue10Temp ) != 0 )
    {
    	Exclusion[APL_SYS_PARAM_WHITE_MENU_ADD] = AplParamState_VisibleInvalid;
    }
    
    // Bug5127
    // ATWの時はADDはグレーアウト
    if ( APL_PARAM_GET_DATA( AplParamWhiteValueIndex ) == 0 /* ATW */ )
    {
    	Exclusion[APL_SYS_PARAM_WHITE_MENU_ADD] = AplParamState_VisibleInvalid;
    }
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_WHITE_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamWhiteMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_WHITE_MENU_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamWhiteValueATWTemp_ViewType(int id) {
    //#[ operation AplParamWhiteValueATWTemp_ViewType(int)
    
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
    if( l == idnum ) return m_Item[AplParamWhiteValueTemp].mState;
    // ---------------------------------------------------------
    
    
    // AplParamColorMain
    switch( APL_PARAM_GET_DATA( AplParamColorMain ) ){
    	case APL_SYS_PARAM_COLOR_MAIN_VLOG:
    		return AplParamState_Invisible;
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
    		return AplParamState_Invisible;
    	default:
    		break;
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamWlanMacAddress_ViewType(int id) {
    //#[ operation AplParamWlanMacAddress_ViewType(int)
    // 常時グレー表示
    return AplParamState_VisibleInvalid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamWLanStatus_ViewType(int id) {
    //#[ operation AplParamWLanStatus_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_WLAN_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_DISCONNECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_P2ROP_LV0
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_P2ROP_LV1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_P2ROP_LV2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_P2ROP_LV3
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_P2ROP_LV4
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_RADIO_LV0
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_RADIO_LV1
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_RADIO_LV2
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_RADIO_LV3
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_WLAN_RADIO_LV4
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamWirelessLanMode,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamWLanStatus].mState;
    // ---------------------------------------------------------
    
    
    // AplParamWirelessLanMode
    switch( APL_PARAM_GET_DATA( AplParamWirelessLanMode ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		Exclusion[APL_SYS_PARAM_WLAN_DISCONNECT] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_P2ROP_LV0] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_P2ROP_LV1] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_P2ROP_LV2] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_P2ROP_LV3] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_P2ROP_LV4] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_RADIO_LV0] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_RADIO_LV1] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_RADIO_LV2] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_RADIO_LV3] = AplParamState_Invisible;
    		Exclusion[APL_SYS_PARAM_WLAN_RADIO_LV4] = AplParamState_Invisible;
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		break;
    	default:
    		break;
    }
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_WLAN_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamWLanStatus].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_WLAN_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamUserAccountMenu_ViewType(int id) {
    //#[ operation AplParamUserAccountMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_USER_ACCOUNT_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_ACCOUNT_MENU_ADD
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_USER_ACCOUNT_MENU_DELETE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamUserAccountMenu,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamUserAccountMenu].mState;
    // ---------------------------------------------------------
    
   
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_USER_ACCOUNT_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamUserAccountMenu].sub_item[i].state =  Exclusion[i];
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamConnectionHistoryMenu_ViewType(int id) {
    //#[ operation AplParamConnectionHistoryMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_CONNECTION_HISTORY_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CONNECTION_HISTORY_MENU_SELECT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_CONNECTION_HISTORY_MENU_DELETE
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamConnectionHistoryMenu,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamConnectionHistoryMenu].mState;
    // ---------------------------------------------------------
    
    
    // 排他処理 ==================
    for( int i = 0 ; i < APL_SYS_PARAM_CONNECTION_HISTORY_MENU_MAX + 1 ; i++ ){
    	if( Exclusion[i] == AplParamState_VisibleValid ){
    		validnum++;
    	}
    	if( Exclusion[i] == AplParamState_Invisible ){
    		invisiblenum++;
    	}
    	m_Item[AplParamConnectionHistoryMenu].sub_item[i].state =  Exclusion[i];
    }
    
    if ( invisiblenum > 0 ) {
    	return AplParamState_VisibleInvalid;
    }
    
    return AplParamState_VisibleValid;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamVFRValue150_ViewType(int id) {
    //#[ operation AplParamVFRValue150_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamVFRMode,
    	AplParamVFRValue,
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
    if( l == idnum ) return m_Item[AplParamVFRValue].mState;
    // ---------------------------------------------------------
    
    AplParamState setData = AplParamState_VisibleValid;
    int cnt = 0;
    
    for(cnt = AplParamVFRValue1; cnt <= AplParamVFRValue150; cnt++){
    	if((AplParamState_VisibleValid == setData) && ( APL_PARAM_GET_DATA( cnt ) > APL_PARAM_GET_DATA( AplParamVFRSettingRangeMax ) )){
    		setData = AplParamState_VisibleInvalid;
    	}
    	m_Item[cnt].mState = setData;
    }
    
    return m_Item[AplParamVFRValue150].mState;
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamZebra_ViewType(int id) {
    //#[ operation AplParamZebra_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_SWITCH_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_OFF
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_SWITCH_ON
    };
    
    // 反応が必要なAplParamID ----------------------------------
    int idlist[] = {
    	AplParamIdMax,
    	AplParamColorBar,
    };
    int idnum = sizeof( idlist ) / sizeof( idlist[0] );
    int l;
    for ( l = 0 ; l < idnum ; l++ ){
    	if( id == idlist[l] ){
    		break;
    	}
    }
    if( l == idnum ) return m_Item[AplParamZebra].mState;
    // ---------------------------------------------------------
    
    
    // AplParamColorBar
    switch( APL_PARAM_GET_DATA( AplParamColorBar ) ){
    	case APL_SYS_PARAM_SWITCH_OFF:
    		break;
    	case APL_SYS_PARAM_SWITCH_ON:
    		Exclusion[APL_SYS_PARAM_SWITCH_ON] = AplParamState_VisibleInvalid;
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
    	m_Item[AplParamZebra].sub_item[i].state =  Exclusion[i];
    }
    
    if( validnum >= 2 ) {
    	return AplParamState_VisibleValid;
    } else {
    	if( invisiblenum == APL_SYS_PARAM_SWITCH_MAX + 1 ){
    		return AplParamState_Invisible;
    	}
    	return AplParamState_VisibleInvalid;
    }
    
    
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamGrade_ViewType(int id) {
    //#[ operation AplParamGrade_ViewType(int)
    #ifdef ALLOPT_MP_RELEASE
    return AplParamState_Invisible;
    #else
    return AplParamState_VisibleValid;
    #endif
    //#]
}

AplParamState AplParamMainItemTypeFuncK460::AplParamHdmiOutMenu_ViewType(int id) {
    //#[ operation AplParamHdmiOutMenu_ViewType(int)
    int validnum = 0;
    int invisiblenum = 0;
    AplParamState Exclusion[ APL_SYS_PARAM_HDMI_OUT_MENU_MAX + 1 ] = {
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_SIGNAL_SEL
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_OUT_FORMAT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_TC_OUT
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_HDMI_REC_REMOTE
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_INDICATOR_DISP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_MARKER_DISP
    	AplParamState_VisibleValid,	// APL_SYS_PARAM_HDMI_OUT_MENU_MENU_DISP
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
    if( l == idnum ) return m_Item[AplParamHdmiOutMenu].mState;
    // ---------------------------------------------------------
    
    
    // VUP1で有効
    if ( APL_PARAM_GET_DATA( AplParamGrade ) == APL_SYS_PARAM_SWITCH_OFF )
    {
    	if ( APL_PARAM_GET_DATA( AplParamVup ) < APL_SYS_PARAM_VUP_1ST )
    	{
    		Exclusion[APL_SYS_PARAM_HDMI_OUT_MENU_SIGNAL_SEL] = AplParamState_Invisible;
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
