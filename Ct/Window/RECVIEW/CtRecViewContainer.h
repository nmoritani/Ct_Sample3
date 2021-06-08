/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtRecViewContainer
 */


#ifndef __CtRecViewContainer_H__
#define __CtRecViewContainer_H__

#include "CtContainer.h"
//#include "CtICManager.h"
 // RecView‰æ–Ê‚ÅScreenSelİ’èˆ—‚ğ‚·‚é‚½‚ß‚ÌƒNƒ‰ƒX

class CtRecViewContainer : public CtContainer {
public :
    CtRecViewContainer();
    CtRecViewContainer(CtScreenSel ScreenSel);
    virtual ~CtRecViewContainer();

    virtual bool setStatusMode(bool bStatusMode) { return false; };
	virtual CtScreenSel getDispIcModeSel() { return ScreenNone; };
	virtual CtScreenSel getDispIcModeSel(int IcId) {	return ScreenNone; };

protected:
	bool m_bStatusMode;
	virtual bool destroyContainer();
private :	
};

#endif
