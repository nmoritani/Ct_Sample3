/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowHourMeter
*/

#ifndef __CtFactWindowHourMeter_H__
#define __CtFactWindowHourMeter_H__

#include "CtWindowCommon.h"
#include "CtWindowContentsFactHourMeter.h"
#include "CtContainerCtrlButton.h"


class CtFactWindowHourMeter : public CtWindowMain
{
public:
	CtFactWindowHourMeter(CtWindowContents* pContents);
	~CtFactWindowHourMeter();
	CtWindow* createWindow();
    bool handleButtonEvent(const CtEventButton& Button);
	bool handleKeyEvent(const CtEventKey& Key);

private:
	bool destroyWindow();

private:
	CtWindowContentsFactHourMeter* m_pContents;
};

#endif
