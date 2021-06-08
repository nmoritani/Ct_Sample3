/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoSwitchesBottom_H__
#define __CtInfoSwitchesBottom_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoSwitchesBottom : public CtContainer {
public :
    CtInfoSwitchesBottom();

    virtual ~CtInfoSwitchesBottom();

    CtLayout* createContainer();
    bool destroyContainer();

    CtButton* getTouchButton(CtPosition Pos);

	//mori    bool handleEvent(CtWidget* pButton, const CtEvent& Event);
	bool handleButtonEvent(const CtEventButton& Event);
	
protected:

private :
    CtVLayout *m_pBox;
    CtButton *m_pButtonNetwork;
    CtButton *m_pButtonAudio;
    CtButton *m_pButtonMedia;
};


#endif
