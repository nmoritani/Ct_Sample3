/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoMediaTop_H__
#define __CtInfoMediaTop_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoMediaTop : public CtContainer {
public :
    CtInfoMediaTop();

    virtual ~CtInfoMediaTop();

    CtLayout* createContainer();
    bool destroyContainer();

    CtButton* getTouchButton(CtPosition Pos);

	//mori    bool handleEvent(CtWidget* pButton, const CtEvent& Event);
	bool handleButtonEvent(const CtEventButton& Event);
	
protected:

private :
    CtLayout *m_pBox;
    CtButton *m_pButtonDiagnostics;
    CtButton *m_pButtonVersion;
    CtButton *m_pButtonSwitches;
};


#endif
