/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version:	7.5.1
 *  Element:			AplObserverParamService
 */


#ifndef Foundation_Manager_AplObserverParamService_H
#define Foundation_Manager_AplObserverParamService_H

#include <oxf.h>
#include <AplList.h>
#include <AplAlgorithm.h>
#include "kernel.h"
//## package Foundation::Manager

//## class AplObserverParamService
class AplObserverParamService {
public :

    typedef AplContainer::list<int> AplParamList;
    
    typedef enum AplParamServiceResetInitialSettingType {
        AplParamServiceResetInitialSetting_All,
        AplParamServiceResetInitialSetting_SceneCustom
    } AplParamServiceResetInitialSettingType;
    
    ////    Constructors and destructors    ////
    
    //## operation ~AplObserverParamService()
    virtual ~AplObserverParamService() = 0;
    
    ////    Operations    ////
    
    ///新仕様です。IDと値を通知します。
    //## operation update(int,int)
    virtual void update(int t_Id, int int_Data);
    
    ///旧仕様です。いずれ旧仕様は削除し新仕様(IDと値の通知)に移行します
    //## operation update(int)
    virtual void update(int t_Id);
    
    ///notified when updating to initial setting
    //## operation updateToInitialSetting()
    virtual void updateToInitialSetting();
    
    ///@brief
    ///AplParamの変更通知開始を通知します。<br>
    ///AplParamの変更チェイン(AplParam変化通知によるAplParam変更)が終わった場合にupdateEndでこの関数のシーケンスIDを引数に渡します。<br>
    ///
    ///@param[in] sequenceId 一意なID。
    ///@since 2014/02
    ///@note
    ///<pre>
    ///通知シーケンスsample.
    ///■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
    ///ClassAがAplParamService::setData( AplParamXXX, 0 )コール
    ///AplObserverParamService実装クラスがそのupdate通知でさらに
    ///AplParamService::setData( AplParamYYY, 0 )をコールした場合
    ///■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
    ///AplObserverParamService実装クラス::updateStart( 一意な値ZZZ )
    ///↓
    ///AplObserverParamService実装クラス::update( AplParamXXX, 0 )
    ///↓
    ///AplObserverParamService実装クラス::update( AplParamYYY, 0 )
    ///↓
    ///AplObserverParamService実装クラス::updateEnd( 一意な値ZZZ,  AplParamXXXとAplParamYYYを格納したリスト )
    ///
    ///■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
    ///ClassAがAplParamService::setData( AplParamXXX, 0 )コール
    ///AplObserverParamService実装クラスがそのupdateEndでさらに
    ///AplParamService::setData( AplParamYYY, 0 )をコールした場合
    ///■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
    ///AplObserverParamService実装クラス::updateStart( 一意な値ZZZ )
    ///↓
    ///AplObserverParamService実装クラス::update( AplParamXXX, 0 )
    ///↓
    ///AplObserverParamService実装クラス::updateEnd( 一意な値ZZZ,  AplParamXXXを格納したリスト )
    ///↓
    ///AplObserverParamService実装クラス::updateStart( 一意な値KKK)
    ///↓
    ///AplObserverParamService実装クラス::update( AplParamYYY, 0 )
    ///↓
    ///AplObserverParamService実装クラス::updateEnd( 一意な値KKK, AplParamYYYを格納したリスト )
    ///</pre>
    ///
    ///
    ///
    //## operation updateStart(unsigned int)
    virtual void updateStart(unsigned int sequenceId);
    
    ///@brief
    ///AplParamの変更通知終了を通知します。<br>
    ///
    ///@param[in] sequenceId 一意なID。
    ///@param[in] updateIdList updateを行ったAplParamのリスト
    ///@since 2014/02
    ///@see AplObserverParamService#updateStart
    //## operation updateEnd(unsigned int,AplParamList)
    virtual void updateEnd(unsigned int sequenceId, const AplParamList& updateIdList);
    
    ///notified when updating to initial setting
    //## operation updateToInitialSetting(AplParamServiceResetInitialSettingType)
    virtual void updateToInitialSetting(const AplParamServiceResetInitialSettingType type);

    virtual void updateWriteStatus(int id, bool isWritable);
};

#endif
