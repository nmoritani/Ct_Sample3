/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWidgetControl
 */


#ifndef __CtFastDrawContainerSpotMeterVal_H__
#define __CtFastDrawContainerSpotMeterVal_H__

#include "CtRecViewContainer.h"
#include "CtHLayout.h"
#include "CtICManager.h"
#include "CtTimer.h"

//const int CT_SPOT_METER_TIMER_ID = 0;

class CtFastDrawContainerSpotMeterVal : public CtRecViewContainer {

	#define DigitNum 4		/* +0.0 */
	//#define SPOT_DISP_COUNT 0	// •œ‹AŽž‚É10V‘Ò‚¿‚·‚é
	enum {
		CT_TIMER_ID_SPOTMETER,
	};
	
public :
    CtFastDrawContainerSpotMeterVal();
    virtual ~CtFastDrawContainerSpotMeterVal();

	CtLayout* createContainer();
	bool destroyContainer();
	bool updateFastDraw();
	virtual bool setStatusMode(bool bStatusMode);
	//bool isDispSpotMeter();
	virtual bool startupContainer();

	bool handleParamEvent(const CtEventParam& Param);
	bool handleTimerEvent(const CtEventTimer& Timer);
protected:

private :
	CtHLayout*			m_pAll;
	//CtStackLabel*		m_pLabel[DigitNum];
	CtLabel*			m_pStopLabel;
	
	
	bool				m_bDisp;
	bool				updateDisp();
	int getCharIndex(char c);
	bool				draw();
	//int m_interval;
	//int m_interval_count;
	//int dispcouter;
	//bool m_Timer;
	CtLabel*			m_pSpotMeterVal;
};


#endif
