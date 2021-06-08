/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerSpinBoxFanc_H__
#define __CtContainerSpinBoxFanc_H__

//#include "CtWindow.h"
#include "CtContainerSpinBox.h"
#include "CtMenuInfoSpinBox.h"
#include "AplParamService.h"
#include "CtParamBox.h"

class CtContainerSpinBoxFanc : public CtContainerSpinBox
{
/*** �萔 ***************************************/
public:
protected:
private:

/*** ���\�b�h ***********************************/
public:
	CtContainerSpinBoxFanc(CtWindowID id);
	virtual ~CtContainerSpinBoxFanc();

	virtual bool handleParamEvent(const CtEventParam& Param);

protected:

	virtual CtLayout* createLabel();

	virtual bool executionUp();
	virtual bool executionDown();
	virtual bool executionRet(bool bDestructor = false);
	virtual bool executionSet();

	virtual void checkInvalid();

private:

/*** �����o   ***********************************/
public:

protected:

private:
};

#endif
