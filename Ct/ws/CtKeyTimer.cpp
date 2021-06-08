#include "CtEvent.h"
#include "CtKeyTimer.h"
#include "CtTimer.h"

CtKeyTimer::CtKeyTimer(CtEventKey::KeyCode Key, unsigned long IntervalTime) :
	m_Key(Key),
	m_IntervalTime(IntervalTime),
	m_IntervalCount(0),
	m_pFastKeyTimer(NULL),
	m_timLv(CtEventKey::Level_Default)
{
	CtTimer::getInstance()->startCyclic(CT_KEY_TIMER_ID, IntervalTime, this);
}

CtKeyTimer::~CtKeyTimer()
{
	if (m_pFastKeyTimer != NULL) delete m_pFastKeyTimer;
	CtTimer::getInstance()->stopCyclic(CT_KEY_TIMER_ID, this);
}

bool CtKeyTimer::handleTimerEvent(const CtEventTimer& Timer)
{
	m_IntervalCount++;
	
	if ((m_IntervalCount * m_IntervalTime) / (1000 * m_timLv)) {
		if (m_timLv < CtEventKey::Level_Max) {
			m_timLv = (CtEventKey::KeyTimerLevel)(m_timLv + 1);
		}
	}
	if ((m_IntervalCount * m_IntervalTime) == 1000) {
		return CtEventKey(CtEventKey::LongPress, m_Key, CtEventKey::KeySource_Body, m_timLv).exec();
	}else if ((m_IntervalCount * m_IntervalTime) >= 1000 ) {
		return CtEventKey(CtEventKey::RepeatPress, m_Key, CtEventKey::KeySource_Body, m_timLv).exec();
	}

	return false;
}
void CtKeyTimer::setIntervalTime(unsigned long IntervalTime) {
	m_IntervalTime = IntervalTime;
}

CtGradFastKeyTimer::CtGradFastKeyTimer(CtEventKey::KeyCode Key, unsigned long FirstIntervalTime, unsigned long ThresholdTime, unsigned long GradTime, unsigned long MinTime) : CtKeyTimer(Key, FirstIntervalTime){
	m_ThresholdTime = ThresholdTime;
	m_GradTime = GradTime;
	m_MinTime = MinTime;
}

void CtGradFastKeyTimer::setIntervalTime(unsigned long IntervalTime) {
	m_IntervalTime = IntervalTime;
	// IntervalŽžŠÔ•ÏX‚É‚æ‚èCount‚ð‚à‚Ç‚·
	m_IntervalCount = 0;
	CtTimer::getInstance()->startCyclic(CT_KEY_TIMER_ID, IntervalTime, this);
}

CtGradFastKeyTimer::~CtGradFastKeyTimer() {

}

bool CtGradFastKeyTimer::handleTimerEvent(const CtEventTimer& Timer) {
	m_IntervalCount++;
	if (Timer.getTimeUid() != CT_KEY_TIMER_ID) {
		return false;
	}
	if ((m_IntervalCount * m_IntervalTime) >= m_ThresholdTime && m_MinTime < m_IntervalTime) {
		m_IntervalTime -= m_GradTime;
		if (m_IntervalTime < m_MinTime) {
			m_IntervalTime = m_MinTime;
		}
		setIntervalTime(m_IntervalTime);
	}
	return CtEventKey(CtEventKey::FastPress, m_Key, CtEventKey::KeySource_Body).exec();
}
