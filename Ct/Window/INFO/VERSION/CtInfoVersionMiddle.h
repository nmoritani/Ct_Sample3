/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoVersionMiddle_H__
#define __CtInfoVersionMiddle_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoVersionMiddle : public CtContainer {
public :
    CtInfoVersionMiddle();

    virtual ~CtInfoVersionMiddle();

    CtLayout* createContainer();
	bool destroyContainer();

    virtual bool handleParamEvent(const CtEventParam& Param);
	
protected:

private :
    void updateModelValue();
    void updateSerialNoValue();
    void updateVersionValue();
    void updateBeSoftValue();
    void updateCamSoftValue();
    void updateActSoftValue();
    void updateFpgaValue();

    CtLayout *m_pBox;

    CtLabel *m_pModelValue;
    CtLabel *m_pSerialNoValue;
    CtLabel *m_pVersionValue;
    CtLabel *m_pBeSoftValue;
    CtLabel *m_pCamSoftValue;
    CtLabel *m_pActSoftValue;
    CtLabel *m_pFpgaValue;

};


#endif
