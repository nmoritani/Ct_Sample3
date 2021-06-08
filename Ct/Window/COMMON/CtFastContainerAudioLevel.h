/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Rhapsody Version:	7.5.1
 *  Element:			CtFastContainerAudioLevel
 */


#ifndef __CtFastContainerAudioLevel_H__
#define __CtFastContainerAudioLevel_H__

#include "CtWindowCommon.h"
#include "CtRecViewContainer.h"

class CtFastContainerAudioLevel : public CtRecViewContainer
{
protected:
	static const int CT_TIMER_ID_LEVEL_PEAK = 0;
	static const short AUDIO_LEVEL_NUM_MAX = 18 + 1;

public:
	CtFastContainerAudioLevel();
	virtual ~CtFastContainerAudioLevel();
	CtLayout* createContainer();
	bool destroyContainer();
	virtual bool updateFastDraw();
	virtual bool handleParamEvent(const CtEventParam& Param);

protected:
	virtual CtLayout* createLevelMeter() {return NULL;};
	virtual void updateSegmentSub() {};// Headroom•\Ž¦’l
	virtual int getStandardSegment();
	
	bool updateFastDrawAudioLevel();

	bool isMute();
	short getCh1Level();
	short getCh2Level();
private:
	unsigned int m_Ch1FrameCount;
	unsigned int m_Ch2FrameCount;
protected:
	bool m_IsMute;		// RecView or PlayView
	void updateSegment();
	virtual bool updateAudioLevelMeterState(int int_Data);

protected:
	CtStackLabel* m_pLevelCh1;
	CtStackLabel* m_pLevelCh2;
	CtStackLabel* m_pLevelSwitchArea;
	CtLayout* m_pAllHeadRoom;
	int m_PreSeg;
	int m_Seg;
	int m_peakCh1;
	int m_peakCh2;
	CtVector::Vector<CtStackLabel*> m_pLevelSetCh1;
	CtVector::Vector<CtStackLabel*> m_pLevelSetCh2;
	

private:
#ifdef WIN32_GUI_SIM
	int value1;
	int value2;
#endif
};

#endif
