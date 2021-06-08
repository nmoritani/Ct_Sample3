/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoNetworkMiddle_H__
#define __CtInfoNetworkMiddle_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoNetworkMiddle : public CtContainer {
public :
    CtInfoNetworkMiddle();

    virtual ~CtInfoNetworkMiddle();

    CtLayout* createContainer();
	bool	  destroyContainer();

    virtual bool handleParamEvent(const CtEventParam& Param);
	
protected:

private :
    void updateNetworkSel();
    void updateIdAddress();
    void updateNetMask();
    void updateGateway();

    CtLayout *m_pBox;
    CtStackLabel *m_pLabelWlan;
    CtStackLabel *m_pLabelLink;
    CtHLayout *m_pNetworkSelLink;
    CtLabel *m_pIdAddressValue;
    CtLabel *m_pNetMaskValue;
    CtLabel *m_pGatewayValue;
};


#endif
