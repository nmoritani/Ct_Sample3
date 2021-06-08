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
    //�R���X�g���N�^�ł���Ă���������initialize()�Ɉ��z��
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
    // �t�@�[���A�b�v�ŗ̈悪�ς��Ƃ��͂����ɏ�����ǉ�����
    //#]
}

void AplParamService::initialize() {
    //#[ operation initialize()
    fwupInitCheck();
    
    /* <K460�ǉ�>-------------------------------------------------------- */
    m_pExclutionFunc = new AplParamMainExclusionFuncK460();
	#ifdef ALL_MENU_ON
	m_pMainItemType = new AplParamMainItemTypeFunc( m_Item );
	#else
	m_pValueCheck = new AplParamMainValueCheck();
	m_pMainItemType = new AplParamMainItemTypeFuncK519( m_Item, *m_pValueCheck);
    #endif
    // �}�X�^�[�ƃL���b�V���ێ��̈��������
    pos = 0;
    memset(m_CacheData,  0, APL_PARAM_DATA_SIZE_MAX);
    memset(m_MasterData, 0, APL_PARAM_DATA_SIZE_MAX);
    //�������̈�̎擾
    for( int i=0 ; i<AplParamIdMax ; i++ ){
    	getMemory(m_Item[i].size, &m_Item[i].master, &m_Item[i].cache);
    	
		/* Excel�Œ�`���������l���擾 */
		switch( m_Item[i].initialType ){
			case AplParamInitialType_Ip:
    		case AplParamInitialType_Number:
				{
					int insert = m_Item[i].size -1;
					int val = 0;
					int count = 0;
    				/* 2������1byte */
    				if( (int)(strlen(m_Item[i].initialValue) / 2) <= m_Item[i].size ){
			    		for( int j = strlen(m_Item[i].initialValue) - 1 ; j >= 0 ; j-- ){
			    			/* Ascii�𐔎��ɕϊ� */
			    			if( m_Item[i].initialValue[j] >= 0x30 && m_Item[i].initialValue[j] <= 0x39 ){
			    				val = m_Item[i].initialValue[j] - 0x30;
			    			} else if( m_Item[i].initialValue[j] >= 0x41 && m_Item[i].initialValue[j] <= 0x46 ) {
			    				val = m_Item[i].initialValue[j] - 0x37;
			    			} else {
			    				/* ��̕��� */
			    				break;
			    			}
			    			/* 2�����ڂ�4bit�V�t�g */
			    			m_Item[i].cache[insert]  |= val << ((count % 2) * 4);
			    			m_Item[i].master[insert] |= val << ((count % 2) * 4);
			    			/* 2���1�񏑂����݈ʒu��ύX */
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
    				/* 1������1byte */
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
    
    #if defined( APL_PARAM_SERVICE_DEBUG ) /* �����l�Ŏ擾�����f�[�^��\�� */
    /* for debug */
    smDebugPrintf( 1, "============================================================\n");
    for( int i=0 ; i<AplParamIdMax ; i++ ){
    	smDebugPrintf( 1, "[ id : %8d]\t", i);
    	/* �T�C�Y�\�� */
    	smDebugPrintf( 1, "[ size : %4d]\t", m_Item[i].size);
    	/* �A�h���X�\�� */
    	smDebugPrintf( 1, "[ backupOffset : %4d]\t", m_Item[i].backupOffset);
    	smDebugPrintf( 1, "[ initialOffset : %4d]\t", m_Item[i].initialOffset);
    	/* �L���b�V���ƃ}�X�^�[�f�[�^�\�� */
    	if( m_Item[i].initialType == AplParamInitialType_String ){
    		smDebugPrintf( 1, "%s", m_Item[i].cache);
    	} else {
    		smDebugPrintf( 1, "0x");
        	for( int j = 0 ; j < m_Item[i].size  ; j++ ){
        		smDebugPrintf( 1, "%02X", m_Item[i].cache[j]);
        	}
    	}
    	/* ��ԕ\�� */
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
    	/* ��ԍX�V�֐� */
    	if( m_Item[i].state_func == NULL ){
    		smDebugPrintf( 1, "[ state_func : NULL]\t");
    	} else {
    		smDebugPrintf( 1, "[ state_func : Exist]\t");
    	}
    	
    	/* ��ԍX�V�֐� */
    	if( m_Item[i].exclusion_func == NULL ){
    		smDebugPrintf( 1, "[ exclusion_func : NULL]\t");
    	} else {
    		smDebugPrintf( 1, "[ exclusion_func : Exist]\t");
    	}
    	/* �ʒm�L�� */
    	smDebugPrintf( 1, "[ update : %d]\t",m_Item[i].update_enable);
    	smDebugPrintf( 1, "[ exclusion : %d]\t",m_Item[i].exclusion_enable);
    	/* ��������� */
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
    
    // �r���֘A������
    if( m_pExclutionFunc != NULL ){
    	m_pExclutionFunc->execute( AplParamIdMax );
    }
    
    // �����������^�C�~���O�ŕ\����Ԃ�S�čX�V
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
    
    /* �e�[�u���͈͊O */
    if( id >= AplParamIdMax ){
    	//AplAssertEx( 0, "Bug!! AplParamId is Over the Table %d", id );
    	return (-1);
    }
    
    /* int�^�ŕԂ��Ȃ��f�[�^ */
    if( isCanReturnInt( id ) == false ){
    	//AplAssertEx( 0, "Bug!! AplParamId is Can not Return Int type %d", id );
    	return (-1);
    }
    
    /* �߂�l�ɂ߂Ă��� */
    for( int i = 0 ; i < m_Item[id].size ; i++ ){
    	ret |= m_Item[id].cache[m_Item[id].size-1-i] << 8 * i; 
    }
    
    return ret;
    //#]
}

int AplParamService::getDataFromMaster(int id) {
    //#[ operation getDataFromMaster(int)
    int ret = 0;
    
    /* �e�[�u���͈͊O */
    if( id >= AplParamIdMax ){
    	//AplAssertEx( 0, "Bug!! AplParamId is Over the Table %d", id );
    	return (-1);
    }
    
    /* int�^�ŕԂ��Ȃ��f�[�^ */
    if( isCanReturnInt( id ) == false ){
    	//AplAssertEx( 0, "Bug!! AplParamId is Can not Return Int type %d", id );
    	return (-1);
    }
    
    /* �߂�l�ɂ߂Ă��� */
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
    
    /* �߂�l�ɂ߂� */
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
    
    /* �߂�l�ɂ߂� */
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
    
    /* �T�C�Y�`�F�b�N(���̊֐���4Btyte�ȏ���T�|�[�g���Ȃ�) */
    if( isCanReturnInt( id ) == false){
    	return false;
    }
    
    /* Old�l���擾 */
    OldCache  = getData( id );
    OldMaster = getDataFromMaster( id );
    
    /* ����l�ݒ�`�F�b�N */
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
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			#ifndef DEBUG_NO_WRITE
    			/* SYS�����ϐ��ɏ������� */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset + (m_Item[id].size - (i + 1)), m_Item[id].master[ m_Item[id].size - (i + 1) ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		if( target == AplParamSaveTargetAuto ){
    			/* SYS�����ϐ�����EEPROM�ɏ������� */
    			//AplIfSys::Eep_FlushData(APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset, m_Item[id].size);
    		}
    		#endif
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			#ifndef DEBUG_NO_WRITE
    			/* SYS�����ϐ��ɏ������� */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset + m_Item[id].size - (i + 1), m_Item[id].master[ m_Item[id].size - (i + 1) ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		/* SYS�����ϐ�����EEPROM�ɏ������� */
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
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* �����ϐ��ɏ������� */
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
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			#ifndef DEBUG_NO_WRITE
    			/* SYS�����ϐ��ɏ������� */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset + m_Item[id].size - (i + 1), m_Item[id].master[ m_Item[id].size - (i + 1) ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		if( target == AplParamSaveTargetAuto ){
    			/* SYS�����ϐ�����EEPROM�ɏ������� */
    			//AplIfSys::Eep_FlushData(APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset, m_Item[id].size);
    		}
    		#endif
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    			#ifndef DEBUG_NO_WRITE
    			/* SYS�����ϐ��ɏ������� */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset + m_Item[id].size - (i + 1), m_Item[id].master[ m_Item[id].size - (i + 1) ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		/* SYS�����ϐ�����EEPROM�ɏ������� */
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
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ]  = GET_UB(value, i);
    			m_Item[id].master[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[ m_Item[id].size - (i + 1) ] = GET_UB(value, i);
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < m_Item[id].size ; i++ ){
    			/* �����ϐ��ɏ������� */
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
    
    /* ����l�ݒ�`�F�b�N */
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
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[i] = Data[i];
    			m_Item[id].master[i] = Data[i];
    			#ifndef DEBUG_NO_WRITE
    			/* SYS�����ϐ��ɏ������� */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset + i, m_Item[id].master[ i ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		if( target == AplParamSaveTargetAuto ){
    			/* SYS�����ϐ�����EEPROM�ɏ������� */
    			//AplIfSys::Eep_FlushData(APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset, DataSize);
    		}
    		#endif
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].master[i] = Data[i];
    			#ifndef DEBUG_NO_WRITE
    			/* SYS�����ϐ��ɏ������� */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_BACKUP_S_ADDR + m_Item[id].backupOffset + i, m_Item[id].master[ i ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		/* SYS�����ϐ�����EEPROM�ɏ������� */
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
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[i] = Data[i];
    			m_Item[id].master[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* �����ϐ��ɏ������� */
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
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[i] = Data[i];
    			m_Item[id].master[i] = Data[i];
    			#ifndef DEBUG_NO_WRITE
    			/* SYS�����ϐ��ɏ������� */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset + i, m_Item[id].master[ i ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		if( target == AplParamSaveTargetAuto ){
    			/* SYS�����ϐ�����EEPROM�ɏ������� */
    			//AplIfSys::Eep_FlushData(APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset, DataSize);
    		}
    		#endif
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].master[i] = Data[i];
    			#ifndef DEBUG_NO_WRITE
    			/* SYS�����ϐ��ɏ������� */
    			//AplIfSys::Eep_SetByteData( APL_EEPROM_STATIC_S_ADDR + m_Item[id].backupOffset + i, m_Item[id].master[ i ] );
    			#endif
    		}
    		#ifndef DEBUG_NO_WRITE
    		/* SYS�����ϐ�����EEPROM�ɏ������� */
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
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[i] = Data[i];
    			m_Item[id].master[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetCache:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* �����ϐ��ɏ������� */
    			m_Item[id].cache[i] = Data[i];
    		}
    		break;
    	  case AplParamSaveTargetMaster:
    		for( int i = 0; i < DataSize ; i++ ){
    			/* �����ϐ��ɏ������� */
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
    	//�Œ�l�̈��Flush���Ȃ�
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
    	//�Œ�l�̈��Flush���Ȃ�
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
    // AplParam�ύX�`�F�C���J�n����
    //=============================
    // �J�E���^�������ɂȂ��Ă���΃J�E���^�����̎����o�O
    //AplAssertEx( m_updateChainCnt >= 0, "Bug!! Call Counter Fraud %d", m_updateChainCnt );
    if ( m_updateChainCnt == 0 )
    {
    	// �V�K�V�[�P���X��AplParamList�쐬
    	// �����Fm_updateChainList.size��2�ȏ�̏ꍇ��updateEnd��setData���Ă΂ꂽ���ƂɂȂ�
    	AplObserverParamService::AplParamList* pNewChainList = new AplObserverParamService::AplParamList();
    	m_updateChainList.push_back( pNewChainList );
    	
    	//AplDebugPrint( AplDbgIdManager, "AplParamService[updateStart] Seqid=0x%08X, SeqListSize=%d", (unsigned int)pNewChainList, m_updateChainList.size() );
    	
    	// ��ӂ�ID�Ƃ��ă��X�g�̃A�h���X���V�[�P���XID�Ƃ��Ēʒm
    	for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr )
    	{
    	    (*Itr)->updateStart( (unsigned int)pNewChainList );
    	}		
    }
    // �֐��ċN�Ăяo���J�E���^�X�V
    m_updateChainCnt++;
    
    //=============================
    // AplParam�ύX�����X�V
    //=============================
    AplObserverParamService::AplParamList* pUpdateList = m_updateChainList.back(); // ���ݕύX���̃��X�g( �����Ȃ̂ŕK���Ō�ɂ��� )
    
    // ����AplParam��ǉ����Ȃ����߂ɁA���łɃR���e�i�ɒǉ�����Ă��Ȃ�������
    if ( AplContainer::find( pUpdateList->begin(), pUpdateList->end(), id ) == pUpdateList->end() )
    {
    	// ���񏉂߂ĕύX����ID�Ȃ̂ŕێ�
    	//AplDebugPrint( AplDbgIdManager, "Change AplParam Seqid=0x%08X ParamId=%d ", (unsigned int)pUpdateList, id );
    	pUpdateList->push_back( id );
    }
    
    //=====================
    // AplParam�ύX�ʒm
    //=====================
    for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr ){
    	//�V�d�l(ID�ƒl��ʒm)
        (*Itr)->update(id,value);
        //���d�l(ID�̂ݒʒm)
        (*Itr)->update(id);
    }
    
    //=====================
    // AplParam���ł̔r������
    //=====================
    if( m_Item[id].exclusion_enable == true ){
    	if(m_pExclutionFunc != NULL){
    		m_pExclutionFunc->execute( id );
    	}
    }
    
    // 2017/03/31 TODO MIZUTA
    // �b��Ή��ŋL�^���[�h�́uAplParamSystemRecMode�v�̒l������悤�ɂ��Ă���
    // AplParamSystemRecMode�̕ω��Ő؂�ւ���Ăق����̂Ń_�~�[��AplParamMP4LPCMQuality59Hz��
    // �X�V�ʒm�𓊂��Ă���
    if ( id == AplParamSystemRecMode )
    {
    	//AplDebugPrint( AplDbgIdAlways, "setData:AplParamSystemRecMode=%d ", value );
    	for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr ){
    		//�V�d�l(ID�ƒl��ʒm)
    		(*Itr)->update(AplParamMP4LPCMQuality59Hz,APL_PARAM_GET_DATA(AplParamMP4LPCMQuality59Hz));
    	}
    }
    
    //=============================
    // AplParam�ύX�`�F�C���I������
    //=============================
    // �֐��ċN�Ăяo���J�E���^�X�V
    m_updateChainCnt--;
    
    if ( m_updateChainCnt == 0 )
    {
    
    	// �����������^�C�~���O�ŕ\����Ԃ�S�čX�V
    	if( m_pMainItemType != NULL ){
    		m_pMainItemType->execute( AplParamIdMax );
    	}
    
    	// ��ӂ�ID�Ƃ��ă��X�g�̃A�h���X���V�[�P���XID�Ƃ��Ēʒm
    	//AplDebugPrint( AplDbgIdManager, "AplParamService[updateEnd] Seqid=0x%08X, SeqListSize=%d, ChangeParamNum=%d", (unsigned int)pUpdateList, m_updateChainList.size(), pUpdateList->size() );
    	for( Iterator Itr=m_pObserver.begin() ; Itr!=m_pObserver.end() ; ++Itr )
    	{
    	    (*Itr)->updateEnd( (unsigned int)pUpdateList, *pUpdateList );
    	}
    	// ����������Ă��猻�ݕύX�����������X�g���폜����
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
    	
    	// Bug62697�Ή�
    	// �J�����T�[�r�X����All�ƃV�[���ŏ����𕪂���K�v���o�����߈����œn���悤�ɕύX
    	// ����A�J�����T�[�r�X�ł݈̂ȉ����g�p����
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
    // NET_EEPROM�̗̈�𗘗p����BAplNetworkParamService�̊֐����Ăяo��
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
    // NET_EEPROM�̗̈�𗘗p����BAplNetworkParamService�̊֐����Ăяo��
    // �̈��AplParamService�Ŋm�ۂ��Ă���̈��Ԃ��B
    
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
    /* ������Static�Ŋm�ۂ����G���A����eAplParam�փf�[�^�̈�����蓖�Ă� */
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
    /* �w�肳�ꂽid���o�b�N�A�b�v�G���A���ǂ������肷�� */
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
    /* �w�肳�ꂽid���Œ�l�̈悩�ǂ������肷�� */
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
    /* �w�肳�ꂽid���A�v�����[�N�G���A���ǂ������肷�� */
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
    /* int�^�ŕԂ���f�[�^�̈悩�ǂ������肷�� */
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
