/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtObserverParamService
 */


#include "CtObserverParamService.h"
#include "CtComMainThread.h"
#include "AplParamService.h"
#include "CtEventInterface.h"

CtObserverParamService::CtObserverParamService()
{
	(AplParamService::getInstance())->addObserver(*this);
}

CtObserverParamService::~CtObserverParamService()
{
	(AplParamService::getInstance())->removeObserver(*this);
}

void CtObserverParamService::update(int t_Id, int int_Data)
{
	CtEventInterface::requestParamCmd(t_Id, int_Data);
}

void CtObserverParamService::updateWriteStatus(int id, bool isWritable)
{
	//CtParamIdReadWriteFlag rwId = ReadWriteUnknown;
	//if( isWritable == true){
	//	rwId = WriteValid;
	//}else{
	//	rwId = WriteInValid;
	//}
	//CtEventInterface::requestParamCmd(id, APL_PARAM()->getData(id), rwId);
}
