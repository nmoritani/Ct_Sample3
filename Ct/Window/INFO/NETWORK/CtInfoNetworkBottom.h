/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoNetworkBottom_H__
#define __CtInfoNetworkBottom_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoNetworkBottom : public CtContainer {
public :
    CtInfoNetworkBottom();

    virtual ~CtInfoNetworkBottom();

    CtLayout* createContainer();
    bool destroyContainer();

    CtButton* getTouchButton(CtPosition Pos);

	//mori    bool handleEvent(CtWidget* pButton, const CtEvent& Event);
	bool handleButtonEvent(const CtEventButton& Event);
	
protected:

private :
    CtVLayout *m_pBox;
    CtButton *m_pButtonAudio;
    CtButton *m_pButtonMedia;
};


#endif
