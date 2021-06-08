/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */


#ifndef __CtContainerSpinBoxSpecial_H__
#define __CtContainerSpinBoxSpecial_H__

//#include "CtWindow.h"
#include "CtContainerSpinBox.h"
#include "CtMenuInfoSpinBox.h"
#include "AplParamService.h"
#include "CtParamBox.h"

class CtContainerSpinBoxSpecial : public CtContainerSpinBox
{
/*** �萔 ***************************************/
public:
protected:
private:

/*** ���\�b�h ***********************************/
public:
	CtContainerSpinBoxSpecial(CtWindowID id);
	virtual ~CtContainerSpinBoxSpecial();

	virtual bool handleParamEvent(const CtEventParam& Param);

protected:
	virtual CtLayout* createLabel();

	virtual bool executionUp();
	virtual bool executionDown();

private:

/*** �����o   ***********************************/
public:

protected:

private:
	CtStackLabel* m_pStack;

};

#endif
