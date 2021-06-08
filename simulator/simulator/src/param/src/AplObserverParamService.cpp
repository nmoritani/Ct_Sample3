/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Rhapsody Version: 7.5.1
 *  Element:          AplObserverParamService
 */


#include "AplObserverParamService.h"
//## package Foundation::Manager

//## class AplObserverParamService
AplObserverParamService::~AplObserverParamService() {
    //#[ operation ~AplObserverParamService()
    //#]
}

void AplObserverParamService::update(int t_Id, int int_Data) {
    //#[ operation update(int,int)
    //#]
}

void AplObserverParamService::update(int t_Id) {
    //#[ operation update(int)
    //#]
}

void AplObserverParamService::updateToInitialSetting() {
    //#[ operation updateToInitialSetting()
    //#]
}

void AplObserverParamService::updateStart(unsigned int sequenceId) {
    //#[ operation updateStart(unsigned int)
    //#]
}

void AplObserverParamService::updateEnd(unsigned int sequenceId, const AplObserverParamService::AplParamList& updateIdList) {
    //#[ operation updateEnd(unsigned int,AplParamList)
    //#]
}

void AplObserverParamService::updateToInitialSetting(const AplObserverParamService::AplParamServiceResetInitialSettingType type) {
    //#[ operation updateToInitialSetting(AplParamServiceResetInitialSettingType)
    //#]
}

void AplObserverParamService::updateWriteStatus(int id, bool isWritable) {
    //#[ operation updateWriteStatus(int,bool)
    //#]
}
