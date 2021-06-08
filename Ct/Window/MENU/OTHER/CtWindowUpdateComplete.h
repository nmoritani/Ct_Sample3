/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowUpdateComplete
 */


#ifndef __CtWindowUpdateComplete_H__
#define __CtWindowUpdateComplete_H__

#include "CtWindowCommon.h"

class CtWindowUpdateComplete : public CtWindowMain
{
public:
	CtWindowUpdateComplete();
	~CtWindowUpdateComplete();

	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleKeyEvent(const CtEventKey& Key);

private:
	CtWindow* createWindow();
	bool destroyWindow();

	CtButton* m_pOk;

};
#endif
