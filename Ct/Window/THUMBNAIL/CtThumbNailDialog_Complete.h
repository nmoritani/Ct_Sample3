/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtThumbNailDialog_Complete
 */


#ifndef __CtThumbNailDialog_Complete_H__
#define __CtThumbNailDialog_Complete_H__

#include "CtWindowCommon.h"

class CtThumbNailDialog_Complete : public CtWindowMain
{

public:
	CtThumbNailDialog_Complete( CtWindowContents *pContents );
	~CtThumbNailDialog_Complete();

	bool handleButtonEvent(const CtEventButton& Button);
    bool handleKeyEvent(const CtEventKey& Key);

private:
	CtWindow* createWindow();
	bool destroyWindow();

	CtLayout* createMessage();
    CtLayout* createControl();

	CtButton* m_pButtonOK;	
};
#endif
