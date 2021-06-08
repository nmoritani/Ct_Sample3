/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtEventReceiver
 */
#ifndef __CtKeyTimer_H__
#define __CtKeyTimer_H__

#include "CtEventHandler.h"
class CtGradFastKeyTimer;

const int CT_KEY_TIMER_ID = 0;

class CtKeyTimer : public CtEventHandler {
public:
	friend CtGradFastKeyTimer;
	CtKeyTimer(CtEventKey::KeyCode Key, unsigned long IntervalTime);
	
	bool handleTimerEvent(const CtEventTimer& Timer);

	CtEventKey::KeyCode getKeyCode();
	void setIntervalTime(unsigned long IntervalTime);
	virtual ~CtKeyTimer();

private:
	CtEventKey::KeyCode m_Key;
	unsigned long m_IntervalTime;
	unsigned long m_IntervalCount;
	CtGradFastKeyTimer* m_pFastKeyTimer;
	CtEventKey::KeyTimerLevel m_timLv;
};

inline CtEventKey::KeyCode CtKeyTimer::getKeyCode()
{
	return m_Key;
}
// 段速機能
//@brief  経過時間により順次通知間隔を狭めるクラス
class CtGradFastKeyTimer : public CtKeyTimer {
public:
	// Constructor
	//@brief Key 通知Key
	//@brief IntervalTime 初期通知間隔
	//@brief ThresholdTime 速度変更間隔 
	//@brief GradTime 間隔減少時間
	//@brief MinTime 最少間隔
	CtGradFastKeyTimer(CtEventKey::KeyCode Key, unsigned long FirstIntervalTime, unsigned long ThresholdTime, unsigned long GradTime, unsigned long MinTime);
	void setIntervalTime(unsigned long IntervalTime);
	virtual ~CtGradFastKeyTimer();
	bool handleTimerEvent(const CtEventTimer& Timer);
private:
	unsigned long m_ThresholdTime;
	unsigned long m_MinTime;
	unsigned long m_GradTime;
};

#endif

