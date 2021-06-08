/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerCom_H_
#define __CtContainerCom_H_

#include "Ct.h"
#include "CtWidget.h"
#include "AplParamService.h"
#include "CtWindowCommon.h"
#include "CtRecViewContainer.h"

class CtContainerCom : public CtRecViewContainer{
public :

	CtContainerCom();

	virtual ~CtContainerCom();

	virtual CtLayout* createContainer();

	virtual bool destroyContainer();
	
	virtual bool handleParamEvent(const CtEventParam& Param);
	
private :
	void updateCom();

	/**********************  attributes **********************/
	CtLabel*						m_pCom;

	bool							m_ComModeFlash;
};

#endif
