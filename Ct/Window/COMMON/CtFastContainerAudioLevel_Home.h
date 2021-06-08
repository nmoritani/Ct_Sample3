/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element:			CtFastContainerAudioLevel_Home
 */


#ifndef __CtFastContainerAudioLevel_Home_H__
#define __CtFastContainerAudioLevel_Home_H__

#include "CtFastContainerAudioLevel.h"

class CtFastContainerAudioLevel_Home : public CtFastContainerAudioLevel
{
public:
	CtFastContainerAudioLevel_Home() ;
	virtual ~CtFastContainerAudioLevel_Home();
	
protected:
	virtual CtLayout* createLevelMeter();
	virtual void updateSegmentSub();
private:
	CtVector::Vector<CtWidget*> m_pHeadRooms;
};

#endif
