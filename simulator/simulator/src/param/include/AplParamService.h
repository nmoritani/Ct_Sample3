/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version:	7.5.1
 *  Element:			AplParamService
 */


#ifndef Foundation_Manager_AplParamService_H
#define Foundation_Manager_AplParamService_H

#include <stdio.h>
#include <string.h>
#include <AplList.h>
#include <AplAlgorithm.h>
#include "AplObject.h"
#include "AplObserverParamService.h"
#include "AplParam.h"
#include "apl_sys_param_enum.h"
#include "SysIf.h"

class AplParamMainExclusionFunc;

class AplParamMainExclusionFuncK460;

class AplParamMainItemTypeFunc;

class AplParamMainItemTypeFuncK519;

class AplParamMainValueCheck;



// �p�����[�^�̃Z�b�g�ƃQ�b�g�p�}�N��
#define APL_PARAM()									AplParamService::getInstance()
#define APL_PARAM_GET_DATA(x)						AplParamService::getInstance()->getData(x)
#define APL_PARAM_GET_MASTER_DATA(x)				AplParamService::getInstance()->getDataFromMaster(x)
#define APL_PARAM_GET_INIT_DATA(x)					AplParamService::getInstance()->getDataFromInitialArea(x)
#define APL_PARAM_SET_DATA(x,y)						AplParamService::getInstance()->setData(x,y)
#define APL_PARAM_SET_CACHE_DATA(x,y)				AplParamService::getInstance()->setData(x,y,AplParamService::AplParamSaveTargetCache)
#define APL_PARAM_SET_MASTER_DATA(x,y)				AplParamService::getInstance()->setData(x,y,AplParamService::AplParamSaveTargetMaster)
#define APL_PARAM_SET_SYS_CACHE_DATA(x,y)			AplParamService::getInstance()->setData(x,y,AplParamService::AplParamSaveTargetSysCache)
#define APL_PARAM_FORCE_SET_DATA(x,y)				AplParamService::getInstance()->setData(x,y,AplParamService::AplParamSaveTargetAuto,AplParamService::AplParamSetType_Force)
#define APL_PARAM_FORCE_SET_CACHE_DATA(x,y)			AplParamService::getInstance()->setData(x,y,AplParamService::AplParamSaveTargetCache,AplParamService::AplParamSetType_Force)
#define APL_PARAM_FLUSH_DATA(x)						AplParamService::getInstance()->flashData(x)

#define APL_PARAM_GET_DATA_AREA(x,y,w)				AplParamService::getInstance()->getData(x,y,w)
#define APL_PARAM_GET_MASTER_DATA_AREA(x,y,w)		AplParamService::getInstance()->getDataFromMaster(x,y,w)
#define APL_PARAM_GET_INIT_DATA_AREA(x,y,w)			AplParamService::getInstance()->getDataFromInitialArea(x,y,w)
#define APL_PARAM_SET_DATA_AREA(x,y,w)				AplParamService::getInstance()->setData(x,y,w)
#define APL_PARAM_SET_CACHE_DATA_AREA(x,y,w)		AplParamService::getInstance()->setData(x,y,w,AplParamService::AplParamSaveTargetCache)
#define APL_PARAM_SET_MASTER_DATA_AREA(x,y,w)		AplParamService::getInstance()->setData(x,y,w,AplParamService::AplParamSaveTargetMaster)
#define APL_PARAM_SET_SYS_CACHE_DATA_AREA(x,y,w)	AplParamService::getInstance()->setData(x,y,w,AplParamService::AplParamSaveTargetSysCache)
#define APL_PARAM_FLUSH_DATA_AREA(x,y)				AplParamService::getInstance()->flashData(x,y)

#define APL_PARAM_EXEC_FAKE_UPDATE(x)				AplParamService::getInstance()->updateFakeChangeParam(x)

#define APL_PARAM_GET_PERSON_DATA(Data,Index)		AplParamService::getInstance()->getPersonData(&Data,Index)
#define APL_PARAM_SET_PERSON_DATA(Data,Index)		AplParamService::getInstance()->setPersonData(&Data,Index)

// �f�[�^���[�h�A�b�v�f�[�g�Ȃ�
#define APL_PARAM_LOAD_DATA(x,y)					AplParamService::getInstance()->loadData(x,y)
#define APL_PARAM_LOAD_DATA_AREA(x,y,w)				AplParamService::getInstance()->loadData(x,y,w)

// �f�[�^�������ݒ�
#define APL_PARAM_IS_WRITABLE(x)					AplParamService::getInstance()->isWritable(x)

#define APL_PARAM_DATA_OFFSET           (0x9600)     /* APL�p�̃o�C�g�f�[�^�J�n�̈�I�t�Z�b�g */
#define APL_PARAM_DATA_SIZE             (1968)       /* APL�p�̃o�C�g�f�[�^�J�n�̈�T�C�Y */


// �V�[���f�[�^�̖��O�T�C�Y
// AplParamSceneFileName* �Ɠ����T�C�Y
#define APL_PARAM_SCENEDATA_NAME_SIZE       		33


/*
* ���N�����Ɩ��O�̏����Ǘ����邽�߂̍\���̂Ȃ�
*/
#define APL_PARAM_PERSON_DATA_NUM       3                                   /* �l���̐� */
#define APL_PARAM_PERSON_DATA_OFFSET(x) (sizeof(APL_PARAM_PERSON_DATA) * x) /* �w�肵���l���ԍ��̐擪�I�t�Z�b�g */
#define APL_PARAM_PERSON_NAME_SIZE      40                                  /* ���O�̃T�C�Y(������ x Unicode�T�C�Y) */

// �V�[���J�X�^���ݒ薳��ID(���g�p�ł��邱�Ƃ��`�t����ID)
#define APL_SCENECUSTOM_INVALID_ID (0x0000)

// �V�[���J�X�^�����̕�����
#define APL_SCENECUSTOM_NAME_SIZE 7 /* �ݒ�ł���ő啶����(6����) + �I�[���� */

// SCN 01.00�ł̂ݎg�p����V�[���J�X�^���f�[�^�T�C�Y
#define APL_SCENE_CUSTOM_DATE_SIZE 101

typedef unsigned short UH;
typedef unsigned char  UB;
typedef unsigned short UH;

/* ���N�����Ɩ��O�Ǘ��p�̍\���� */
typedef struct _APL_PARAM_PERSON_DATA {
	struct {
		UH  Year;                           //__attribute__((aligned(4)));    // ���N����(�N)
		UB  Month;                           //__attribute__((aligned(4)));    // ���N����(��)
		UB  Day;                             //__attribute__((aligned(4)));    // ���N����(��)
	} Date;
	UB  Name[APL_PARAM_PERSON_NAME_SIZE];    //__attribute__((aligned(4)));    // ���O
	UB  Rsv[32];                             //__attribute__((aligned(4)));    // �g���\���̈�
} APL_PARAM_PERSON_DATA;

/* <K460�ǉ�>---------------------------------------------- */
#define NAME_SIZE 20
#define GET_UB(value, a)	(unsigned char)((value & 0xFF << (a * 8)) >> (a * 8))

#define APL_EEPROM_BACKUP_S_ADDR	0x5C00
#define APL_EEPROM_BACKUP_SIZE		0x2000
#define APL_EEPROM_INITIAL_S_ADDR	0x7C00
#define APL_EEPROM_INITIAL_SIZE		0x2000
#define APL_EEPROM_STATIC_S_ADDR	0xA250
#define APL_EEPROM_STATIC_SIZE		0x0800

#define APL_EEPROM_OTHER_S_ADDR		0x04C0
#define APL_EEPROM_OTHER_SIZE		0x0004

typedef enum AplParamState {
	AplParamState_VisibleValid,		/* �L���\�� */
	AplParamState_VisibleInvalid,	/* �����\��  */
	AplParamState_Invisible,		/* ��\�� */
	AplParamState_End,				/* �I�� */
}AplParamState;

typedef AplParamState(*APL_PARAM_STATE_FUNC)(void);
typedef void(*APL_PARAM_EXCLUSION_FUNC)(void);

typedef enum AplParamResetType {
	AplParamResetType_Factory = 0x00000001,
	AplParamResetType_Menu = 0x00000002,
	AplParamResetType_Setup = 0x00000004,
	AplParamResetType_WifiAll = 0x00000008,
	AplParamResetType_WifiExceptPanaAuthInfo = 0x00000010,
	AplParamResetType_WifiExceptRemoteUserInfoAndNetworkInfo = 0x00000020,
	AplParamResetType_WifiNetworkInfo = 0x00000040,
	AplParamResetType_WifiRemoteUserInfo = 0x00000080,
	AplParamResetType_Scene1 = 0x00000100,
	AplParamResetType_Scene2 = 0x00000200,
	AplParamResetType_Scene3 = 0x00000400,
	AplParamResetType_Scene4 = 0x00000800,
	AplParamResetType_Scene5 = 0x00001000,
	AplParamResetType_Scene6 = 0x00002000,

	AplParamResetType_WifiPicmateInfo = 0x00004000,	//���g�p

	AplParamResetType_All = 0xFFFFFFFF,
}AplParamResetType;

typedef enum AplParamInitialType{
	AplParamInitialType_Number,
	AplParamInitialType_String,
	AplParamInitialType_Ip,
}AplParamInitialType;

#define GET_UB(value, a)	(unsigned char)((value & 0xFF << (a * 8)) >> (a * 8))

/* -------------------------------------------------------- */
//## package Foundation::Manager

//## class AplParamService
class AplParamService : public AplObject {
public :

    typedef enum AplParamSaveTarget {
        AplParamSaveTargetAuto,
        AplParamSaveTargetCache,
        AplParamSaveTargetMaster,
        AplParamSaveTargetSysCache ///SYS�̃L���b�V�������X�V����
    } AplParamSaveTarget;

    ///�V�[���t�@�C��No��`
    ///�V�[��1�`6 + ALL+BuckUp�p
    typedef enum AplSceneCustomNumberType {
        AplSceneCustomNumberType_1 = 0,
        AplSceneCustomNumberType_2,
        AplSceneCustomNumberType_3,
        AplSceneCustomNumberType_4,
        AplSceneCustomNumberType_5,
        AplSceneCustomNumberType_6,
        AplSceneCustomNumberType_Max,
        AplSceneCustomNumberType_ALL,
        AplSceneCustomNumberType_BuckUp
    } AplSceneCustomNumberType;
    
    ///�V�[���J�X�^���p�����[�^�̌^��`
    ///�V�[���J�X�^���e�[�u���Ŏg�p
    typedef enum AplSceneCustomDataType {
        AplSceneCustomDataType_BOOL = 0,
        AplSceneCustomDataType_B,
        AplSceneCustomDataType_UB,
        AplSceneCustomDataType_H,
        AplSceneCustomDataType_UH,
        AplSceneCustomDataType_W,
        AplSceneCustomDataType_UW
    } AplSceneCustomDataType;
    
    ///�J�X�^���V�[���ɒ�`�����p�����[�^�̏��\����
    ///
    ///Id�@�V�[���J�X�^���p�����[�^ID
    ///SceneCustomParamIdList�@�@�V�[�����Ƃ�AplParam���X�g
    ///MinValue�@�V�[���J�X�^���p�����[�^�ŏ��l
    ///MaxValue�@�V�[���J�X�^���p�����[�^�ő�l
    ///DataType�@�V�[���J�X�^���p�����[�^�̌^
    typedef struct AplSceneCustomInfo {
        unsigned int Id;		//## attribute Id
        AplParamEepromId MenuParamId;		//## attribute MenuParamId
        AplParamEepromId SceneCustomParamIdList[AplSceneCustomNumberType_Max + 1];		//## attribute SceneCustomParamIdList
        int MinValue;		//## attribute MinValue
        int MaxValue;		//## attribute MaxValue
        AplSceneCustomDataType DataType;		//## attribute DataType
    } AplSceneCustomInfo;
    
    ///�J�X�^���V�[���p�����[�^�̈�̏���\���\����
    ///Id �V�[���J�X�^���p�����[�^ID
    ///Value�@�l
    typedef struct AplSceneCustomData {
        unsigned int Id;		//## attribute Id
        int Value;		//## attribute Value
    } AplSceneCustomData;
    
    ///�S�ẴV�[���Ƃ��̐ݒ�l������AplSceneCustomData�����\����
    ///�ǂݍ��񂾃V�[�����̕ێ��A�󂯓n���Ɏg�p����
    typedef struct AplSceneCustomDataList {
        AplSceneCustomData List[AplSceneCustomNumberType_Max][APL_SCENE_CUSTOM_PARAM_NUM];		//## attribute List
    } AplSceneCustomDataList;
    
    typedef struct AplParamSubItem {
        int value;		//## attribute value
        AplParamState state;		//## attribute state
    } AplParamSubItem;
    
    typedef struct AplParamMainItem {
        int size;		//## attribute size
        int backupOffset;		//## attribute backupOffset
        int initialOffset;		//## attribute initialOffset
        unsigned char* cache;		//## attribute cache
        unsigned char* master;		//## attribute master
        bool attribute;		//## attribute attribute
        const char* initialValue;		//## attribute initialValue
        AplParamState mState;		//## attribute mState
        bool update_enable;		//## attribute update_enable
        bool exclusion_enable;		//## attribute exclusion_enable
        AplParamResetType resetType;		//## attribute resetType
        AplParamSubItem* sub_item;		//## attribute sub_item
        int initialType;		//## attribute initialType
    } AplParamMainItem;
    
    ////    Constructors and destructors    ////

private :

    //## operation AplParamService()
    AplParamService();

public :

    //## operation ~AplParamService()
    ~AplParamService();
    
    ////    Operations    ////
    
    //## operation getInstance()
    static AplParamService* getInstance();
    
    //## operation fwupInitCheck()
    void fwupInitCheck();
    
    //## operation initialize()
    void initialize();
    
    //## operation addObserver(AplObserverParamService)
    void addObserver(const AplObserverParamService& observer);
    
    //## operation removeObserver(AplObserverParamService)
    void removeObserver(const AplObserverParamService& observer);
    
    //## operation getData(int)
    int getData(int id);
    
    //## operation getDataFromMaster(int)
    int getDataFromMaster(int id);
    
    //## operation getData(int,unsigned char,unsigned int)
    void getData(int id, unsigned char* Data, unsigned int Size);
    
    //## operation getDataFromMaster(int,unsigned char,unsigned int)
    void getDataFromMaster(int id, unsigned char* Data, unsigned int Size);
	
	// WinSim�p�֐�
	AplParamInitialType getParamDataType(int id);
	AplParamSubItem* getParamSubItem(int id);
    
    //## operation setData(int,int,AplParamSaveTarget)
    void setData(int id, int value, AplParamSaveTarget target = AplParamSaveTargetAuto);

	int getSize(int Id);
private :

    //## operation _setData(int,int,AplParamSaveTarget)
    bool _setData(int id, int value, AplParamSaveTarget target);

public :

    //## operation setData(int,unsigned char,unsigned int,AplParamSaveTarget)
    void setData(int id, unsigned char* Data, unsigned int Size, const AplParamSaveTarget target = AplParamSaveTargetAuto);

private :

    //## operation _setData(int,unsigned char,unsigned int,AplParamSaveTarget)
    bool _setData(int id, unsigned char* Data, unsigned int Size, const AplParamSaveTarget target);

public :

    //## operation flashData(int)
    void flashData(int id);
    
    //## operation flashData(int,int)
    void flashData(int id, int size);

private :

    //## operation updateChangeParam(int,int)
    void updateChangeParam(int id, int value);
    
    //## operation updateToInitialSetting(AplParamServiceResetInitialSettingType)
    void updateToInitialSetting(const AplObserverParamService::AplParamServiceResetInitialSettingType type);

public :

    ///id�Ŏw�肳�ꂽAplParam�̕ω��ʒm���^���I�ɔ���������
    ///�ʏ�A�ύX�̂������ꍇ�ł̂ݒʒm���s�����A�ύX�ʒm���󂯂����Ɠ����V�[�P���X��ʂ������ꍇ�Ɏg�p����
    ///����API�R�[���ɂ���Ĕ�������ʒm�ɂ́A���ݐݒ肳��Ă���l(���łɒʒm��)���ݒ肳���
    ///Observer���Ńp�����[�^�̕ύX������s���Ă���ꍇ�ɂ͌��ʂ��Ȃ��̂Œ��ӂ��邱��
    ///
    ///@param [in] id AplParam��ID
    //## operation updateFakeChangeParam(int)
    void updateFakeChangeParam(int id);
    
private :

public :
    ///@brief ����TargetScene�Ɏw�肵���V�[���J�X�^���ԍ���pName�Ŏw�肵���������ۑ�����
    ///pName�Ŏw�肵��������̏I�[�����������͕ۑ��̈�T�C�Y�܂ŕۑ�
    ///TargetScene��1�`6�ȊO���w�肵���ꍇ�͂Ȃɂ����Ȃ�
    ///
    ///@param char* pName �ۑ����镶����
    ///@param APL_SYS_PARAM_SCENECUSTOM TargetScene �V�[���J�X�^���ԍ�(1�`6)
    //## operation setSceneCustomName(char*,const APL_SYS_PARAM_SCENECUSTOM)
    void setSceneCustomName(const char* pName, const APL_SYS_PARAM_SCENECUSTOM TargetScene);
    
    ///@brief ����TargetScene�Ɏw�肵���V�[���J�X�^���ԍ��̖��O��������擾����
    ///TargetScene��1�`6�ȊO���w�肵���ꍇ��NULL���Ԃ�
    ///
    ///@param APL_SYS_PARAM_SCENECUSTOM TargetScene �V�[���J�X�^���ԍ�(1�`6)
    ///@return ���O������(�I�[�����܂�)
    //## operation getSceneCustomName(const APL_SYS_PARAM_SCENECUSTOM)
    const char* getSceneCustomName(const APL_SYS_PARAM_SCENECUSTOM TargetScene);

private :

public :

private :

    //## operation getMemory(int,unsigned char,unsigned char)
    bool getMemory(int size, unsigned char** master, unsigned char** cache);
    
    //## operation isBackupArea(int)
    bool isBackupArea(int id);
    
    //## operation isStaticArea(int)
    bool isStaticArea(int id);
    
    //## operation isWorkArea(int)
    bool isWorkArea(int id);
    
    //## operation isCanReturnInt(int)
    bool isCanReturnInt(int id);

public :

    //## operation getParamState(int)
    AplParamMainItem* getParamState(int id);
    
	//## operation isWritable(int)
    bool isWritable(int id);
    
    //## operation updateWriteStatus(int,bool)
    void updateWriteStatus(int id, bool isWritable);
    
    ////    Attributes    ////

private :

    static AplParamService* m_pThis;		//## attribute m_pThis
        
    ///!< AplParam�ύX�`�F�[�����X�g�BAplParam�̕ω��ʒm���s���A�I�u�U�[�o���ł����AplParam��ύX�����ꍇ�ɒǉ����Ă���
    AplContainer::list<AplObserverParamService::AplParamList*> m_updateChainList;		//## attribute m_updateChainList
    
    ///!< AplParam�ύX�`�F�[���񐔁B
    int m_updateChainCnt;		//## attribute m_updateChainCnt
    
    
    
    static char m_SceneFileName[AplParamSceneFileName1_Size];		//## attribute m_SceneFileName
    
    static int pos;		//## attribute pos
    
    static unsigned char m_MasterData[APL_PARAM_DATA_SIZE_MAX];		//## attribute m_MasterData
    
    static unsigned char m_CacheData[APL_PARAM_DATA_SIZE_MAX];		//## attribute m_CacheData
    
    static AplParamMainItem m_Item[AplParamIdMax];		//## attribute m_Item
    
    ////    Relations and components    ////
    
    AplParamMainExclusionFunc* m_pExclutionFunc;
    
    AplParamMainItemTypeFunc* m_pMainItemType;
    
    AplContainer::list<AplObserverParamService*> m_pObserver;

	AplParamMainValueCheck* m_pValueCheck;

};

#endif
