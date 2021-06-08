/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version: 7.5.1
 *  Element:          AplParamService
 */

#include "smDebugSerial.h"
#include "AplParamService.h"
#include "AplParamMainExclusionFunc.h"
#include "AplParamMainExclusionFuncK460.h"
#include "AplParamMainItemTypeFunc.h"
#include "AplParamMainItemTypeFuncK519.h"
#include "apl_param_sub_item_data.def"
#include "AplParamMainValueCheck.h"
 //## package Foundation::Manager

//#define ALL_MENU_ON

//## class AplParamService
AplParamService* AplParamService::m_pThis(NULL);


char AplParamService::m_SceneFileName[AplParamSceneFileName1_Size] = { 0 };

int AplParamService::pos = 0;

unsigned char AplParamService::m_MasterData[APL_PARAM_DATA_SIZE_MAX];

unsigned char AplParamService::m_CacheData[APL_PARAM_DATA_SIZE_MAX];

AplParamService::AplParamMainItem AplParamService::m_Item[AplParamIdMax] = {
	#include "apl_param_initial_data.def"
};

AplParamService::AplParamService() : m_updateChainCnt(0) {
    m_pExclutionFunc = NULL;
    m_pMainItemType = NULL;
    //#[ operation AplParamService()
    //コンストラクタでやっていた処理はinitialize()に引越し
    //#]
}

AplParamService::~AplParamService() {
    //#[ operation ~AplParamService()
    if( m_pExclutionFunc != NULL ){
    	delete m_pExclutionFunc;
    	m_pExclutionFunc = NULL;
    }
    if( m_pMainItemType != NULL ){
    	delete m_pMainItemType;
    	m_pMainItemType = NULL;
    }
    //#]
}

AplParamService* AplParamService::getInstance() {
    //#[ operation getInstance()
    if(NULL == m_pThis){ m_pThis = new AplParamService(); }	        
    return m_pThis;
    //#]
}

void AplParamService::fwupInitCheck() {
    //#[ operation fwupInitCheck()
    // ファームアップで領域が変わるときはここに処理を追加する
    //#]
}

void AplParamService::initialize() {
    //#[ operation initialize()
    fwupInitCheck();
    
    /* <K460追加>-------------------------------------------------------- */
    m_pExclutionFunc = new AplParamMainExclusionFuncK460();
	#ifdef ALL_MENU_ON
	m_pMainItemType = new AplParamMainItemTypeFunc( m_Item );
	#else
	m_pValueCheck = new AplParamMainValueCheck();
	m_pMainItemType = new AplParamMainItemTypeFuncK519( m_Item, *m_pValueCheck);
    #endif
    // マスターとキャッシュ保持領域を初期化
    pos = 0;
    memset(m_CacheData,  0, APL_PARAM_DATA_SIZE_MAX);
    memset(m_MasterData, 0, APL_PARAM_DATA_SIZE_MAX);
    //メモリ領域の取得
    for( int i=0 ; i<AplParamIdMax ; i++ ){
    	getMemory(m_Item[i].size, &m_Item[i].master, &m_Item[i].cache);
    	
		/* Excelで定義した初期値を取得 */
		switch( m_Item[i].initialType ){
			case AplParamInitialType_Ip:
    		case AplParamInitialType_Number:
				{
					int insert = m_Item[i].size -1;
					int val = 0;
					int count = 0;
    				/* 2文字で1byte */
    				if( (int)(strlen(m_Item[i].initialValue) / 2) <= m_Item[i].size ){
			    		for( int j = strlen(m_Item[i].initialValue) - 1 ; j >= 0 ; j-- ){
			    			/* Asciiを数字に変換 */
			    			if( m_Item[i].initialValue[j] >= 0x30 && m_Item[i].initialValue[j] <= 0x39 ){
			    				val = m_Item[i].initialValue[j] - 0x30;
			    			} else if( m_Item[i].initialValue[j] >= 0x41 && m_Item[i].initialValue[j] <= 0x46 ) {
			    				val = m_Item[i].initialValue[j] - 0x37;
			    			} else {
			    				/* 謎の文字 */
			    				break;
			    			}
			    			/* 2文字目を4bitシフト */
			    			m_Item[i].cache[insert]  |= val << ((count % 2) * 4);
			    			m_Item[i].master[insert] |= val << ((count % 2) * 4);
			    			/* 2回に1回書き込み位置を変更 */
			    			if( count % 2 ){
			    				insert--;
			    			}
			    			count++;
			    		}
    				}
				}
				break;
			case AplParamInitialType_String:
				{
    				/* 1文字で1byte */
    				if( (int)strlen(m_Item[i].initialValue) <= m_Item[i].size ){
			    		for( int j = 0 ; j < (int)strlen(m_Item[i].initialValue) ; j ++ ){
			    			m_Item[i].cache[j]  = m_Item[i].initialValue[j];
			    			m_Item[i].master[j] = m_Item[i].initialValue[j];
			    		}
    				}
				}
				break;
    		default:
				break;
		}
    }
    
    #if defined( APL_PARAM_SERVICE_DEBUG ) /* 初期値で取得したデータを表示 */
    /* for debug */
    smDebugPrintf( 1, "============================================================\n");
    for( int i=0 ; i<AplParamIdMax ; i++ ){
    	smDebugPrintf( 1, "[ id : %8d]\t", i);
    	/* サイズ表示 */
    	smDebugPrintf( 1, "[ size : %4d]\t", m_Item[i].size);
    	/* アドレス表示 */
    	smDebugPrintf( 1, "[ backupOffset : %4d]\t", m_Item[i].backupOffset);
    	smDebugPrintf( 1, "[ initialOffset : %4d]\t", m_Item[i].initialOffset);
    	/* キャッシュとマスターデータ表示 */
    	if( m_Item[i].initialType == AplParamInitialType_String ){
    		smDebugPrintf( 1, "%s", m_Item[i].cache);
    	} else {
    		smDebugPrintf( 1, "0x");
        	for( int j = 0 ; j < m_Item[i].size  ; j++ ){
        		smDebugPrintf( 1, "%02X", m_Item[i].cache[j]);
        	}
    	}
    	/* 状態表示 */
    	switch(m_Item[i].mState){
    	case AplParamState_VisibleValid:
    		smDebugPrintf( 1, "[ state : VisibleValid]\t");
    		break;
    	case AplParamState_VisibleInvalid:
    		smDebugPrintf( 1, "[ state : VisibleInvalid]\t");
    		break;
    	case AplParamState_Invisible:
    		smDebugPrintf( 1, "[ state : Invisible]\t");
    		break;
    	case AplParamState_End:
    		smDebugPrintf( 1, "[ state : End]\t");
    		break;
    	default:
    		smDebugPrintf( 1, "[ state : Unknown]\t");
    		break;
    	}
    	/* 状態更新関数 */
    	if( m_Item[i].state_func == NULL ){
    		smDebugPrintf( 1, "[ state_func : NULL]\t");
    	} else {
    		smDebugPrintf( 1, "[ state_func : Exist]\t");
    	}
    	
    	/* 状態更新関数 */
    	if( m_Item[i].exclusion_func == NULL ){
    		smDebugPrintf( 1, "[ exclusion_func : NULL]\t");
    	} else {
    		smDebugPrintf( 1, "[ exclusion_func : Exist]\t");
    	}
    	/* 通知有無 */
    	smDebugPrintf( 1, "[ update : %d]\t",m_Item[i].update_enable);
    	smDebugPrintf( 1, "[ exclusion : %d]\t",m_Item[i].exclusion_enable);
    	/* 初期化種別 */
    	smDebugPrintf( 1, "[ resetType : %08X]\t",m_Item[i].resetType);
    	
    	if( m_Item[i].sub_item == NULL ){
    		smDebugPrintf( 1, "[ sub_item : NONE]\t");
    	} else {
    		AplParamSubItem* subItem = m_Item[i].sub_item;
    		while( subItem->state != AplParamState_End ){
    			smDebugPrintf( 1, "[ sub_item(value) : %04d]\t", subItem->value);
    	    	switch(subItem->state){
    	    	case AplParamState_VisibleValid:
    	    		smDebugPrintf( 1, "[ sub_item(state) : VisibleValid]\t");
    	    		break;
    	    	case AplParamState_VisibleInvalid:
    	    		smDebugPrintf( 1, "[ sub_item(state) : VisibleInvalid]\t");
    	    		break;
    	    	case AplParamState_Invisible:
    	    		smDebugPrintf( 1, "[ sub_item(state) : Invisible]\t");
    	    		break;
    	    	case AplParamState_End:
    	    		smDebugPrintf( 1, "[ sub_item(state) : End]\t");
    	    		break;
    	    	default:
    	    		smDebugPrintf( 1, "[ sub_item(state) : Unknown]\t");
    	    		break;
    	    	}
    			if( subItem->state_func == NULL ){
    				smDebugPrintf( 1, "[ sub_item(state_func) : NULL]\t");
    			} else {
    				smDebugPrintf( 1, "[ sub_item(state_func) : Exist]\t");
    			}
    			subItem++;
    			dly_tsk( 5 );
    		}
    	}
    	
    	smDebugPrintf( 1, "\n" );
    	dly_tsk( 5 );
    }
    smDebugPrintf( 1, "============================================================\n");
    #endif
    
    
    /* ------------------------------------------------------------------ */
    
    setData(AplParamSceneSelectModeFlag, false);
    
    // 排他関連を処理
    if( m_pExclutionFunc != NULL ){
    	m_pExclutionFunc->execute( AplParamIdMax );
    }
    
    // 落ち着いたタイミングで表示状態を全て更新
    if( m_pMainItemType != NULL ){
    	m_pMainItemType->execute( AplParamIdMax );
    }
    //#]
}

void AplParamService::addObserver(const AplObserverParamService& observer) {
    //#[ operation addObserver(AplObserverParamService)
    m_pObserver.push_back(const_cast<AplObserverParamService *>(&observer));
    //#]
}

void AplParamService::removeObserver(const AplObserverParamService& observer) {
    //#[ operation removeObserver(AplObserverParamService)
    m_pObserver.remove(const_cast<AplObserverParamService *>(&observer));
    //#]
}

int AplParamService::getData(int id) {
    //#[ operation getData(int)
    int ret = 0;
    
    /* テーブル範囲外 */
    if( id >= AplParamIdMax ){
    	//AplAssertEx( 0, "Bug!! AplParamId is Over the Table %d", id );
    	return (-1);
    }
    
    /* int型で返せないデータ */
    if( isCanReturnInt( id ) == false ){
    	//AplAssertEx( 0, "Bug!! AplParamId is Can not Return Int type %d", id );
    	return (-1);
    }
    
    /* 戻り値につめていく */
    for( int i = 0 ; i < m_Item[id].size ; i++ ){
    	ret |= m_Item[id].cache[m_Item[id].size-1-i] << 8 * i; 
    }
    
    return ret;
    //#]
}

int AplParamService::getDataFromMaster(int id) {
    //#[ operation getDataFromMaster(int)
    int ret = 0;
    
    /* テーブル範囲外 */
    if( id >= AplParamIdMax ){
    	//AplAssertEx( 0, "Bug!! AplParamId is Over the Table %d", id );
    	return (-1);
    }
    
    /* int型で返せないデータ */
    if( isCanReturnInt( id ) == false ){
    	//AplAssertEx( 0, "Bug!! AplParamId is Can not Return Int type %d", id );
    	return (-1);
    }
    
    /* 戻り値につめていく */
    for( int i = 0 ; i < m_Item[id].size ; i++ ){
    	ret |= m_Item[id].master[m_Item[id].size-1-i] << 8 * i; 
    }
    
    return ret;
    //#]
}

void AplParamService::getData(int id, unsigned char* Data, unsigned int Size) {
    //#[ operation getData(int,unsigned char,unsigned int)
    int DataSize = 0;
    
    if( id >= AplParamIdMax ){
    	return;
    }
    
    /* 戻り値につめる */
    DataSize = ((int)Size<m_Item[id].size)?Size:m_Item[id].size;
    memcpy( Data, m_Item[id].cache, DataSize );	
    
    return;
    //#]
}

void AplParamService::getDataFromMaster(int id, unsigned char* Data, unsigned int Size) {
    //#[ operation getDataFromMaster(int,unsigned char,unsigned int)
    int DataSize = 0;
    
    if( id >= AplParamIdMax ){
    	return;
    }
    
    /* 戻り値につめる */
    DataSize = ((int)Size<m_Item[id].size)?Size:m_Item[id].size;
    memcpy( Data, m_Item[id].master, DataSize );	
    
    return;
    //#]
}

void AplParamService::setData(int id, int value, AplParamService::AplParamSaveTarget target) {
    //#[ operation setData(int,int,AplParamSaveTarget)
    bool ret = false;
    ret = _setData( id, value, target );
    if( ret == true ){
    	updateChangeParam(id, value);
    }
    
    return;
    //#]
}

bool AplParamService::_setData(int id, int value, AplParamService::AplParamSaveTarget target) {
    //#[ operation _setData(int,int,AplParamSaveTarget)
    int OldCache  = 0;
    int OldMaster = 0;
    
    /* サイズチェック(この関数は4Btyte以上をサポートしない) */
    if( isCanReturnInt( id ) == false){
    	return false;
    }
    
    /* Old値を取得 */
    OldCache  = getData( id );
    OldMaster = getDataFromMaster( id );
    
    /* 同一値設定チェック */
    switch(target){
    	case AplParamSaveTargetAuto:
    	case AplParamSaveTargetSysCache:
    		if( OldCache == value && OldMaster == value ) return false;
    		break;
    	case AplParamSaveTargetCache:
    		if( OldCache == value ) return false;
    		break;
    	case AplParamSaveTargetMaster:
    		if( OldMaster == value ) return false;
    		break;
    	default:
    		return false;
    }
    
    if( isBackupArea( id ) ){
    	switch(target){
    	  case AplParamSaveTargetAuto:
    	  case AplParamSaveTargetSysCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			#ifndef DEBUG_NO_WRITE
    			/* SYS内部変数に書き込み */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset + (m_Item[id].size - (i + 1)), m_Item[id].master[ m_Item[id].size - (i + 1) ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		if( target == AplParamSaveTargetAuto ){
    			/* SYS内部変数からEEPROMに書き込み */
    			//AplIfSys::Eep_FlushData(APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset, m_Item[id].size);
    		}
    		#endif
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			#ifndef DEBUG_NO_WRITE
    			/* SYS内部変数に書き込み */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset + m_Item[id].size - (i + 1), m_Item[id].master[ m_Item[id].size - (i + 1) ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		/* SYS内部変数からEEPROMに書き込み */
    		//AplIfSys::Eep_FlushData(APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset, m_Item[id].size);
    		#endif
    	  default:
    		return false;
    	}
    } else if( isStaticArea( id ) ){
    	switch(target){
    	  case AplParamSaveTargetAuto:
    	  case AplParamSaveTargetSysCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    	  default:
    		return false;
    	}
    } else if( isWorkArea( id ) ){
    	switch(target){
    	  case AplParamSaveTargetAuto:
    	  case AplParamSaveTargetSysCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			#ifndef DEBUG_NO_WRITE
    			/* SYS内部変数に書き込み */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset + m_Item[id].size - (i + 1), m_Item[id].master[ m_Item[id].size - (i + 1) ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		if( target == AplParamSaveTargetAuto ){
    			/* SYS内部変数からEEPROMに書き込み */
    			//AplIfSys::Eep_FlushData(APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset, m_Item[id].size);
    		}
    		#endif
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			#ifndef DEBUG_NO_WRITE
    			/* SYS内部変数に書き込み */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset + m_Item[id].size - (i + 1), m_Item[id].master[ m_Item[id].size - (i + 1) ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		/* SYS内部変数からEEPROMに書き込み */
    		//AplIfSys::Eep_FlushData(APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset, m_Item[id].size);
    		#endif
    
    	  default:
    		return false;
    	}
    } else {
    	switch(target){
    	  case AplParamSaveTargetAuto:
    	  case AplParamSaveTargetSysCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ]  = GET_UB(value, i);
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    	  default:
    		return false;
    	}
    }
    
    return m_Item[id].update_enable;
    
    //#]
}

void AplParamService::setData(int id, unsigned char* Data, unsigned int Size, const AplParamService::AplParamSaveTarget target) {
    //#[ operation setData(int,unsigned char,unsigned int,AplParamSaveTarget)
    bool ret = false;
    ret = _setData( id, Data, Size,target );
    if( ret == true ){
    	updateChangeParam(id, getData( id ));
    }
    //#]
}

bool AplParamService::_setData(int id, unsigned char* Data, unsigned int Size, const AplParamService::AplParamSaveTarget target) {
    //#[ operation _setData(int,unsigned char,unsigned int,AplParamSaveTarget)
    int DataSize = ((int)Size<m_Item[id].size)?Size:m_Item[id].size;
    
    /* 同一値設定チェック */
    switch(target){
    	case AplParamSaveTargetAuto:
    	case AplParamSaveTargetSysCache:
    		if( memcmp(  Data, m_Item[id].cache, DataSize ) == 0 && memcmp(  Data, m_Item[id].master, DataSize ) == 0 ) return false;
    		break;
    	case AplParamSaveTargetCache:
    		if( memcmp(  Data, m_Item[id].cache, DataSize ) == 0 ) return false;
    		break;
    	case AplParamSaveTargetMaster:
    		if( memcmp(  Data, m_Item[id].master, DataSize ) == 0 ) return false;
    		break;
    	default:
    		return false;
    }
    
    if( isBackupArea( id ) ){
    	switch(target){
    	  case AplParamSaveTargetAuto:
    	  case AplParamSaveTargetSysCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[i] = Data[i];
    			m_Item[id].master[i] = Data[i];
    			#ifndef DEBUG_NO_WRITE
    			/* SYS内部変数に書き込み */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset + i, m_Item[id].master[ i ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		if( target == AplParamSaveTargetAuto ){
    			/* SYS内部変数からEEPROMに書き込み */
    			//AplIfSys::Eep_FlushData(APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset, DataSize);
    		}
    		#endif
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].master[i] = Data[i];
    			#ifndef DEBUG_NO_WRITE
    			/* SYS内部変数に書き込み */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset + i, m_Item[id].master[ i ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		/* SYS内部変数からEEPROMに書き込み */
    		//AplIfSys::Eep_FlushData(APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset, DataSize);
    		#endif
    	  default:
    		return false;
    	}
    } else if( isStaticArea( id ) ){
    	switch(target){
    	  case AplParamSaveTargetAuto:
    	  case AplParamSaveTargetSysCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[i] = Data[i];
    			m_Item[id].master[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].master[i] = Data[i];
    		}
    	  default:
    		return false;
    	}
    } else if( isWorkArea( id ) ){
    	switch(target){
    	  case AplParamSaveTargetAuto:
    	  case AplParamSaveTargetSysCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[i] = Data[i];
    			m_Item[id].master[i] = Data[i];
    			#ifndef DEBUG_NO_WRITE
    			/* SYS内部変数に書き込み */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset + i, m_Item[id].master[ i ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		if( target == AplParamSaveTargetAuto ){
    			/* SYS内部変数からEEPROMに書き込み */
    			//AplIfSys::Eep_FlushData(APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset, DataSize);
    		}
    		#endif
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].master[i] = Data[i];
    			#ifndef DEBUG_NO_WRITE
    			/* SYS内部変数に書き込み */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset + i, m_Item[id].master[ i ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		/* SYS内部変数からEEPROMに書き込み */
    		//AplIfSys::Eep_FlushData(APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset, DataSize);
    		#endif
    
    	  default:
    		return false;
    	}
    } else {
    	switch(target){
    	  case AplParamSaveTargetAuto:
    	  case AplParamSaveTargetSysCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[i] = Data[i];
    			m_Item[id].master[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].cache[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* 内部変数に書き込み */
    			m_Item[id].master[i] = Data[i];
    		}
    	  default:
    		return false;
    	}
    }
    
    return m_Item[id].update_enable;
    
    //#]
}

void AplParamService::flashData(int id) {
    //#[ operation flashData(int)
    if( isBackupArea( id ) ){
    	//AplIfSys::Eep_FlushData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset, m_Item[id].size );
    } else if( isStaticArea( id ) ){
    	//固定値領域はFlushしない
    	////AplIfSys::Eep_FlushData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].initialOffset, m_Item[id].size );
    } else if( isWorkArea( id ) ){
    	//AplIfSys::Eep_FlushData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset, m_Item[id].size  );
    }
    //#]
}

void AplParamService::flashData(int id, int size) {
    //#[ operation flashData(int,int)
    if( isBackupArea( id ) ){
    	//AplIfSys::Eep_FlushData(APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset, size );
    } else if( isStaticArea( id ) ){
    	//固定値領域はFlushしない
    	////AplIfSys::Eep_FlushData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].initialOffset, size );
    } else if( isWorkArea( id ) ){
    	//AplIfSys::Eep_FlushData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset, size  );
    }
    //#]
}

void AplParamService::updateChangeParam(int id, int value) {
    //#[ operation updateChangeParam(int,int)
    typedef AplContainer::list<AplObserverParamService*>::iterator Iterator;
    
    //=============================
    // AplParam変更チェイン開始処理
    //=============================
    // カウンタが負数になっていればカウンタ処理の実装バグ
    //AplAssertEx( m_updateChainCnt >= 0, "Bug!! Call Counter Fraud %d", m_updateChainCnt );
    if ( m_updateChainCnt == 0 )
    {
    	// 新規シーケンスのAplParamList作成
    	// メモ：m_updateChainList.sizeが2以上の場合はupdateEndでsetDataが呼ばれたことになる
    	AplObserverParamService::AplParamList* pNewChainList = new AplObserverParamService::AplParamList();
    	m_updateChainList.push_back( pNewChainList );
    	
    	//AplDebugPrint( AplDbgIdManager, "AplParamService[updateStart] Seqid=0x%08X, SeqListSize=%d", (unsigned int)pNewChainList, m_updateChainList.size() );
    	
    	// 一意なIDとしてリストのアドレスをシーケンスIDとして通知
    	for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr )
    	{
    	    (*Itr)->updateStart( (unsigned int)pNewChainList );
    	}		
    }
    // 関数再起呼び出しカウンタ更新
    m_updateChainCnt++;
    
    //=============================
    // AplParam変更履歴更新
    //=============================
    AplObserverParamService::AplParamList* pUpdateList = m_updateChainList.back(); // 現在変更中のリスト( 同期なので必ず最後にある )
    
    // 同じAplParamを追加しないために、すでにコンテナに追加されていないか検索
    if ( AplContainer::find( pUpdateList->begin(), pUpdateList->end(), id ) == pUpdateList->end() )
    {
    	// 今回初めて変更したIDなので保持
    	//AplDebugPrint( AplDbgIdManager, "Change AplParam Seqid=0x%08X ParamId=%d ", (unsigned int)pUpdateList, id );
    	pUpdateList->push_back( id );
    }
    
    //=====================
    // AplParam変更通知
    //=====================
    for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr ){
    	//新仕様(IDと値を通知)
        (*Itr)->update(id,value);
        //旧仕様(IDのみ通知)
        (*Itr)->update(id);
    }
    
    //=====================
    // AplParam内での排他制御
    //=====================
    if( m_Item[id].exclusion_enable == true ){
    	if(m_pExclutionFunc != NULL){
    		m_pExclutionFunc->execute( id );
    	}
    }
    
    // 2017/03/31 TODO MIZUTA
    // 暫定対応で記録モードは「AplParamSystemRecMode」の値を見るようにしている
    // AplParamSystemRecModeの変化で切り替わってほしいのでダミーでAplParamMP4LPCMQuality59Hzの
    // 更新通知を投げている
    if ( id == AplParamSystemRecMode )
    {
    	//AplDebugPrint( AplDbgIdAlways, "setData:AplParamSystemRecMode=%d ", value );
    	for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr ){
    		//新仕様(IDと値を通知)
    		(*Itr)->update(AplParamMP4LPCMQuality59Hz,APL_PARAM_GET_DATA(AplParamMP4LPCMQuality59Hz));
    	}
    }
    
    //=============================
    // AplParam変更チェイン終了処理
    //=============================
    // 関数再起呼び出しカウンタ更新
    m_updateChainCnt--;
    
    if ( m_updateChainCnt == 0 )
    {
    
    	// 落ち着いたタイミングで表示状態を全て更新
    	if( m_pMainItemType != NULL ){
    		m_pMainItemType->execute( AplParamIdMax );
    	}
    
    	// 一意なIDとしてリストのアドレスをシーケンスIDとして通知
    	//AplDebugPrint( AplDbgIdManager, "AplParamService[updateEnd] Seqid=0x%08X, SeqListSize=%d, ChangeParamNum=%d", (unsigned int)pUpdateList, m_updateChainList.size(), pUpdateList->size() );
    	for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr )
    	{
    	    (*Itr)->updateEnd( (unsigned int)pUpdateList, *pUpdateList );
    	}
    	// 資源解放してから現在変更中だったリストを削除する
    	delete pUpdateList;
    	m_updateChainList.pop_back();
    	
    }
    //#]
}

void AplParamService::updateToInitialSetting(const AplObserverParamService::AplParamServiceResetInitialSettingType type) {
    //#[ operation updateToInitialSetting(AplParamServiceResetInitialSettingType)
    typedef AplContainer::list<AplObserverParamService*>::iterator Iterator;
        
    for(Iterator Itr = m_pObserver.begin(); Itr != m_pObserver.end(); ++ Itr ) {
        (*Itr)->updateToInitialSetting();
    	
    	// Bug62697対応
    	// カメラサービス側でAllとシーンで処理を分ける必要が出たため引数で渡すように変更
    	// 現状、カメラサービスでのみ以下を使用する
        (*Itr)->updateToInitialSetting(type);
    }
    
    //#]
}

void AplParamService::updateFakeChangeParam(int id) {
    //#[ operation updateFakeChangeParam(int)
    updateChangeParam( id, getData( id ) );
    //#]
}
void AplParamService::setSceneCustomName(const char* pName, const APL_SYS_PARAM_SCENECUSTOM TargetScene) {
    //#[ operation setSceneCustomName(char*,const APL_SYS_PARAM_SCENECUSTOM)
    // NET_EEPROMの領域を利用する。AplNetworkParamServiceの関数を呼び出す
	if (pName == NULL) {
		return;
	}

	unsigned char FileName[AplParamSceneFileName1_Size] = { 0 };
	int NameLength = strlen(pName);
	int FileNameMax = sizeof(FileName) - 1;
	unsigned int CopySize = (FileNameMax < NameLength) ? FileNameMax : NameLength;
	memcpy((char*)FileName, pName, CopySize);

	int id = 0;
	switch (TargetScene) {
	case APL_SYS_PARAM_SCENECUSTOM_SCENE1:
		id = AplParamSceneFileName1;
		break;
	case APL_SYS_PARAM_SCENECUSTOM_SCENE2:
		id = AplParamSceneFileName2;
		break;
	case APL_SYS_PARAM_SCENECUSTOM_SCENE3:
		id = AplParamSceneFileName3;
		break;
	case APL_SYS_PARAM_SCENECUSTOM_SCENE4:
		id = AplParamSceneFileName4;
		break;
	case APL_SYS_PARAM_SCENECUSTOM_SCENE5:
		id = AplParamSceneFileName5;
		break;
	case APL_SYS_PARAM_SCENECUSTOM_SCENE6:
		id = AplParamSceneFileName6;
		break;
	default:
		return;
	}

	APL_PARAM_SET_DATA_AREA(id, FileName, AplParamSceneFileName1_Size);
    //#]
}

const char* AplParamService::getSceneCustomName(const APL_SYS_PARAM_SCENECUSTOM TargetScene) {
    //#[ operation getSceneCustomName(const APL_SYS_PARAM_SCENECUSTOM)
    // NET_EEPROMの領域を利用する。AplNetworkParamServiceの関数を呼び出す
    // 領域はAplParamServiceで確保している領域を返す。
    
    memset( m_SceneFileName, 0, sizeof( m_SceneFileName ) );
    
    int id = 0;
    switch ( TargetScene ) {
    	case APL_SYS_PARAM_SCENECUSTOM_SCENE1:
    		id = AplParamSceneFileName1;
    		break;
        case APL_SYS_PARAM_SCENECUSTOM_SCENE2:
        	id = AplParamSceneFileName2;
        	break;
        case APL_SYS_PARAM_SCENECUSTOM_SCENE3:
        	id = AplParamSceneFileName3;
        	break;
        case APL_SYS_PARAM_SCENECUSTOM_SCENE4:
        	id = AplParamSceneFileName4;
        	break;
        case APL_SYS_PARAM_SCENECUSTOM_SCENE5:
        	id = AplParamSceneFileName5;
        	break;
        case APL_SYS_PARAM_SCENECUSTOM_SCENE6:
        	id = AplParamSceneFileName6;
        	break;
        default:
        	//AplAssertEx( 0, "not supported." );
        	return m_SceneFileName;
    }
    
    APL_PARAM_GET_DATA_AREA( id, (unsigned char*)m_SceneFileName, AplParamSceneFileName1_Size );
    
    return m_SceneFileName;
    //#]
}

bool AplParamService::getMemory(int size, unsigned char** master, unsigned char** cache) {
    //#[ operation getMemory(int,unsigned char,unsigned char)
    /* 内臓のStaticで確保したエリアから各AplParamへデータ領域を割り当てる */
    if( pos >= APL_PARAM_DATA_SIZE_MAX || pos + size > APL_PARAM_DATA_SIZE_MAX ){
    	//AplAssertEx( m_updateChainCnt >= 0, "Bug!! Master Cahce Data Resource" );
    	master = NULL;
    	cache = NULL;
    	return false;
    }
    
    *master = &m_MasterData[pos];
    *cache = &m_CacheData[pos];
    pos = pos + size;
    
    return true;
    //#]
}

bool AplParamService::isBackupArea(int id) {
    //#[ operation isBackupArea(int)
    /* 指定されたidがバックアップエリアかどうか判定する */
	#if 1
		return false;
	#else
    if( (m_Item[id].backupOffset != 0xFFFF) && (m_Item[id].initialOffset != 0xFFFF) ){
    	return true;
    } else {
    	return false;
    }
	#endif
    //#]
}

bool AplParamService::isStaticArea(int id) {
    //#[ operation isStaticArea(int)
    /* 指定されたidが固定値領域かどうか判定する */
	#if 1
		return false;
	#else
    if( (m_Item[id].backupOffset == 0xFFFF) && (m_Item[id].initialOffset != 0xFFFF) ){
    	return true;
    } else {
    	return false;
    }
	#endif
    //#]
}

bool AplParamService::isWorkArea(int id) {
    //#[ operation isWorkArea(int)
    /* 指定されたidがアプリワークエリアかどうか判定する */
	#if 1
		return false;
	#else
    if( (m_Item[id].backupOffset != 0xFFFF) && (m_Item[id].initialOffset == 0xFFFF) ){
    	return true;
    } else {
    	return false;
    }
	#endif
    //#]
}

bool AplParamService::isCanReturnInt(int id) {
    //#[ operation isCanReturnInt(int)
    /* int型で返せるデータ領域かどうか判定する */
    return m_Item[id].size <= 4;
    //#]
}

AplParamService::AplParamMainItem* AplParamService::getParamState(int id) {
    //#[ operation getParamState(int)
    if( id >= AplParamIdMax ){
    	return NULL;
    }
    
    return &m_Item[id];
    //#]
}

bool AplParamService::isWritable(int id) {
    //#[ operation isWritable(int)
    /*
	if ( m_pAsyncEventController == NULL ) {
    	return true;
    }
    
    return m_pAsyncEventController->isWritable( id );
	*/
	return true;
    //#]
}

void AplParamService::updateWriteStatus(int id, bool isWritable) {
    //#[ operation updateWriteStatus(int,bool)
    typedef AplContainer::list<AplObserverParamService*>::iterator Iterator;
    
    for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr )
    {
    	(*Itr)->updateWriteStatus( id, isWritable );
    }
    //#]
}

AplParamInitialType AplParamService::getParamDataType(int id){
	return (AplParamInitialType)m_Item[id].initialType;
}

AplParamService::AplParamSubItem* AplParamService::getParamSubItem(int id){
	return (AplParamService::AplParamSubItem*)m_Item[id].sub_item;
}

int AplParamService::getSize(int Id) {
	//#[ operation getSize(int)
	if (Id >= AplParamIdMax)
	{
		return 0;
	}

	return m_Item[Id].size;	/* pgr0869 *//* parasoft-suppress  BD-PB-ARRAY */
										 //#]
}
