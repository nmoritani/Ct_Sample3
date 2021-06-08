/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtObserverParamService
 */


#ifndef CtObserverParamService_H
#define CtObserverParamService_H

#include "CtObject.h"

#include "AplObserverParamService.h"

class CtObserverParamService : public CtObject, public AplObserverParamService {
public :
    
    ////    Constructors and destructors    ////
	CtObserverParamService();
    virtual ~CtObserverParamService();
    
    ////    Operations    ////
    
    ///�V�d�l�ł��BID�ƒl��ʒm���܂��B
    virtual void update(int t_Id, int int_Data);
	virtual void updateWriteStatus(int id, bool isWritable);

};

#endif
