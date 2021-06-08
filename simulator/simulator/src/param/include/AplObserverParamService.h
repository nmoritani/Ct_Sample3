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
    
    ///�V�d�l�ł��BID�ƒl��ʒm���܂��B
    //## operation update(int,int)
    virtual void update(int t_Id, int int_Data);
    
    ///���d�l�ł��B�����ꋌ�d�l�͍폜���V�d�l(ID�ƒl�̒ʒm)�Ɉڍs���܂�
    //## operation update(int)
    virtual void update(int t_Id);
    
    ///notified when updating to initial setting
    //## operation updateToInitialSetting()
    virtual void updateToInitialSetting();
    
    ///@brief
    ///AplParam�̕ύX�ʒm�J�n��ʒm���܂��B<br>
    ///AplParam�̕ύX�`�F�C��(AplParam�ω��ʒm�ɂ��AplParam�ύX)���I������ꍇ��updateEnd�ł��̊֐��̃V�[�P���XID�������ɓn���܂��B<br>
    ///
    ///@param[in] sequenceId ��ӂ�ID�B
    ///@since 2014/02
    ///@note
    ///<pre>
    ///�ʒm�V�[�P���Xsample.
    ///������������������������������������������������������������
    ///ClassA��AplParamService::setData( AplParamXXX, 0 )�R�[��
    ///AplObserverParamService�����N���X������update�ʒm�ł����
    ///AplParamService::setData( AplParamYYY, 0 )���R�[�������ꍇ
    ///������������������������������������������������������������
    ///AplObserverParamService�����N���X::updateStart( ��ӂȒlZZZ )
    ///��
    ///AplObserverParamService�����N���X::update( AplParamXXX, 0 )
    ///��
    ///AplObserverParamService�����N���X::update( AplParamYYY, 0 )
    ///��
    ///AplObserverParamService�����N���X::updateEnd( ��ӂȒlZZZ,  AplParamXXX��AplParamYYY���i�[�������X�g )
    ///
    ///������������������������������������������������������������
    ///ClassA��AplParamService::setData( AplParamXXX, 0 )�R�[��
    ///AplObserverParamService�����N���X������updateEnd�ł����
    ///AplParamService::setData( AplParamYYY, 0 )���R�[�������ꍇ
    ///������������������������������������������������������������
    ///AplObserverParamService�����N���X::updateStart( ��ӂȒlZZZ )
    ///��
    ///AplObserverParamService�����N���X::update( AplParamXXX, 0 )
    ///��
    ///AplObserverParamService�����N���X::updateEnd( ��ӂȒlZZZ,  AplParamXXX���i�[�������X�g )
    ///��
    ///AplObserverParamService�����N���X::updateStart( ��ӂȒlKKK)
    ///��
    ///AplObserverParamService�����N���X::update( AplParamYYY, 0 )
    ///��
    ///AplObserverParamService�����N���X::updateEnd( ��ӂȒlKKK, AplParamYYY���i�[�������X�g )
    ///</pre>
    ///
    ///
    ///
    //## operation updateStart(unsigned int)
    virtual void updateStart(unsigned int sequenceId);
    
    ///@brief
    ///AplParam�̕ύX�ʒm�I����ʒm���܂��B<br>
    ///
    ///@param[in] sequenceId ��ӂ�ID�B
    ///@param[in] updateIdList update���s����AplParam�̃��X�g
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
