/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoSwitchesMiddle_H__
#define __CtInfoSwitchesMiddle_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoSwitchesMiddle : public CtContainer {
public :
    CtInfoSwitchesMiddle();

    virtual ~CtInfoSwitchesMiddle();

    CtLayout* createContainer();
	bool destroyContainer();

    virtual bool handleParamEvent(const CtEventParam& Param);
	
protected:

private :

    int getUserParamView(const int paramId);
    int getToggleView(const int paramId);

    bool inputMsgToStackLabel(CtStackLabel* m_pSLabel);

    void updateUser();

    CtLayout *m_pBox;

    CtStackLabel *m_pSLabelToggle;
    CtStackLabel *m_pSLabelUser1;
    CtStackLabel *m_pSLabelUser2;
    CtStackLabel *m_pSLabelUser3;
    CtStackLabel *m_pSLabelUser4;
    CtStackLabel *m_pSLabelUser5;
    CtStackLabel *m_pSLabelUser6;
    CtStackLabel *m_pSLabelUser7;
    CtStackLabel *m_pSLabelUser8;
    CtStackLabel *m_pSLabelUser9;
};

#endif
