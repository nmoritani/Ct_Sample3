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



// パラメータのセットとゲット用マクロ
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

// データロードアップデートなし
#define APL_PARAM_LOAD_DATA(x,y)					AplParamService::getInstance()->loadData(x,y)
#define APL_PARAM_LOAD_DATA_AREA(x,y,w)				AplParamService::getInstance()->loadData(x,y,w)

// データ書き込み中
#define APL_PARAM_IS_WRITABLE(x)					AplParamService::getInstance()->isWritable(x)

#define APL_PARAM_DATA_OFFSET           (0x9600)     /* APL用のバイトデータ開始領域オフセット */
#define APL_PARAM_DATA_SIZE             (1968)       /* APL用のバイトデータ開始領域サイズ */


// シーンデータの名前サイズ
// AplParamSceneFileName* と同じサイズ
#define APL_PARAM_SCENEDATA_NAME_SIZE       		33


/*
* 生年月日と名前の情報を管理するための構造体など
*/
#define APL_PARAM_PERSON_DATA_NUM       3                                   /* 個人情報の数 */
#define APL_PARAM_PERSON_DATA_OFFSET(x) (sizeof(APL_PARAM_PERSON_DATA) * x) /* 指定した個人情報番号の先頭オフセット */
#define APL_PARAM_PERSON_NAME_SIZE      40                                  /* 名前のサイズ(文字数 x Unicodeサイズ) */

// シーンカスタム設定無効ID(未使用であることを定義付けるID)
#define APL_SCENECUSTOM_INVALID_ID (0x0000)

// シーンカスタム名の文字列長
#define APL_SCENECUSTOM_NAME_SIZE 7 /* 設定できる最大文字数(6文字) + 終端文字 */

// SCN 01.00でのみ使用するシーンカスタムデータサイズ
#define APL_SCENE_CUSTOM_DATE_SIZE 101

typedef unsigned short UH;
typedef unsigned char  UB;
typedef unsigned short UH;

/* 生年月日と名前管理用の構造体 */
typedef struct _APL_PARAM_PERSON_DATA {
	struct {
		UH  Year;                           //__attribute__((aligned(4)));    // 生年月日(年)
		UB  Month;                           //__attribute__((aligned(4)));    // 生年月日(月)
		UB  Day;                             //__attribute__((aligned(4)));    // 生年月日(日)
	} Date;
	UB  Name[APL_PARAM_PERSON_NAME_SIZE];    //__attribute__((aligned(4)));    // 名前
	UB  Rsv[32];                             //__attribute__((aligned(4)));    // 拡張予備領域
} APL_PARAM_PERSON_DATA;

/* <K460追加>---------------------------------------------- */
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
	AplParamState_VisibleValid,		/* 有効表示 */
	AplParamState_VisibleInvalid,	/* 無効表示  */
	AplParamState_Invisible,		/* 非表示 */
	AplParamState_End,				/* 終了 */
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

	AplParamResetType_WifiPicmateInfo = 0x00004000,	//未使用

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
        AplParamSaveTargetSysCache ///SYSのキャッシュだけ更新する
    } AplParamSaveTarget;

    ///シーンファイルNo定義
    ///シーン1～6 + ALL+BuckUp用
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
    
    ///シーンカスタムパラメータの型定義
    ///シーンカスタムテーブルで使用
    typedef enum AplSceneCustomDataType {
        AplSceneCustomDataType_BOOL = 0,
        AplSceneCustomDataType_B,
        AplSceneCustomDataType_UB,
        AplSceneCustomDataType_H,
        AplSceneCustomDataType_UH,
        AplSceneCustomDataType_W,
        AplSceneCustomDataType_UW
    } AplSceneCustomDataType;
    
    ///カスタムシーンに定義されるパラメータの情報構造体
    ///
    ///Id　シーンカスタムパラメータID
    ///SceneCustomParamIdList　　シーンごとのAplParamリスト
    ///MinValue　シーンカスタムパラメータ最小値
    ///MaxValue　シーンカスタムパラメータ最大値
    ///DataType　シーンカスタムパラメータの型
    typedef struct AplSceneCustomInfo {
        unsigned int Id;		//## attribute Id
        AplParamEepromId MenuParamId;		//## attribute MenuParamId
        AplParamEepromId SceneCustomParamIdList[AplSceneCustomNumberType_Max + 1];		//## attribute SceneCustomParamIdList
        int MinValue;		//## attribute MinValue
        int MaxValue;		//## attribute MaxValue
        AplSceneCustomDataType DataType;		//## attribute DataType
    } AplSceneCustomInfo;
    
    ///カスタムシーンパラメータの一つの情報を表す構造体
    ///Id シーンカスタムパラメータID
    ///Value　値
    typedef struct AplSceneCustomData {
        unsigned int Id;		//## attribute Id
        int Value;		//## attribute Value
    } AplSceneCustomData;
    
    ///全てのシーンとその設定値数分のAplSceneCustomDataを持つ構造体
    ///読み込んだシーン情報の保持、受け渡しに使用する
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
	
	// WinSim用関数
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

    ///idで指定されたAplParamの変化通知を疑似的に発生させる
    ///通常、変更のあった場合でのみ通知を行うが、変更通知を受けた時と同じシーケンスを通したい場合に使用する
    ///このAPIコールによって発生する通知には、現在設定されている値(すでに通知済)が設定される
    ///Observer側でパラメータの変更判定を行っている場合には効果がないので注意すること
    ///
    ///@param [in] id AplParamのID
    //## operation updateFakeChangeParam(int)
    void updateFakeChangeParam(int id);
    
private :

public :
    ///@brief 引数TargetSceneに指定したシーンカスタム番号にpNameで指定した文字列を保存する
    ///pNameで指定した文字列の終端文字もしくは保存領域サイズまで保存
    ///TargetSceneに1～6以外を指定した場合はなにもしない
    ///
    ///@param char* pName 保存する文字列
    ///@param APL_SYS_PARAM_SCENECUSTOM TargetScene シーンカスタム番号(1～6)
    //## operation setSceneCustomName(char*,const APL_SYS_PARAM_SCENECUSTOM)
    void setSceneCustomName(const char* pName, const APL_SYS_PARAM_SCENECUSTOM TargetScene);
    
    ///@brief 引数TargetSceneに指定したシーンカスタム番号の名前文字列を取得する
    ///TargetSceneに1～6以外を指定した場合はNULLが返る
    ///
    ///@param APL_SYS_PARAM_SCENECUSTOM TargetScene シーンカスタム番号(1～6)
    ///@return 名前文字列(終端文字含む)
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
        
    ///!< AplParam変更チェーンリスト。AplParamの変化通知を行い、オブザーバ側でさらにAplParamを変更した場合に追加していく
    AplContainer::list<AplObserverParamService::AplParamList*> m_updateChainList;		//## attribute m_updateChainList
    
    ///!< AplParam変更チェーン回数。
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
