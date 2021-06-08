/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoMediaMiddle_H__
#define __CtInfoMediaMiddle_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoMediaMiddle : public CtContainer {
public :
    CtInfoMediaMiddle();

    virtual ~CtInfoMediaMiddle();

    CtLayout* createContainer();
	bool destroyContainer();

    virtual bool handleParamEvent(const CtEventParam& Param);
	
protected:

private :
    void setStackLabel(CtStackLabel *m_pSLabel);

    void updateSlot();
    bool isErrorDispSlot1();
    bool isErrorDispSlot2();

    bool isDispSlot1Remain();
    bool isDispSlot2Remain();

    CtLayout *m_pBox;

    CtStackLabel *m_pSlot1Error;
    CtStackLabel *m_pSlot2Error;
    CtLabel *m_pSlot1Value;
    CtLabel *m_pSlot2Value;
    CtLabel *m_pSlot1Remain;
    CtLabel *m_pSlot2Remain;
};


#endif
