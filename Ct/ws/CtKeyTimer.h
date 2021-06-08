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
// �i���@�\
//@brief  �o�ߎ��Ԃɂ�菇���ʒm�Ԋu�����߂�N���X
class CtGradFastKeyTimer : public CtKeyTimer {
public:
	// Constructor
	//@brief Key �ʒmKey
	//@brief IntervalTime �����ʒm�Ԋu
	//@brief ThresholdTime ���x�ύX�Ԋu 
	//@brief GradTime �Ԋu��������
	//@brief MinTime �ŏ��Ԋu
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

