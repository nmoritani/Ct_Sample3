/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoVersionTop_H__
#define __CtInfoVersionTop_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoVersionTop : public CtContainer {
public :
    CtInfoVersionTop();

    virtual ~CtInfoVersionTop();

    CtLayout* createContainer();
    bool destroyContainer();

    CtButton* getTouchButton(CtPosition Pos);

	bool handleButtonEvent(const CtEventButton& Event);

protected:

private :
    CtVLayout *m_pBox;
    CtButton *m_pButtonDiagnostics;
    CtButton *m_pButtonSwitches;
};


#endif
