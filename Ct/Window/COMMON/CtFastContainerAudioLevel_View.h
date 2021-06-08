/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element:			CtFastContainerAudioLevel_View
 */


#ifndef __CtFastContainerAudioLevel_View_H__
#define __CtFastContainerAudioLevel_View_H__

#include "CtFastContainerAudioLevel.h"

class CtFastContainerAudioLevel_View : public CtFastContainerAudioLevel
{
public:
	CtFastContainerAudioLevel_View(bool isRec);
	bool handleParamEvent(const CtEventParam& Param);
	virtual bool updateAudioLevelMeterState(int int_Data);
protected:
	virtual void updateSegmentSub();// Headroom•\Ž¦’l
	virtual CtLayout* createLevelMeter();
private:
	bool m_bRec;
	CtStackLabel* m_pHeadRoomBase;
};

#endif
