/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version: 7.5.1
 *  Element:          CtTimer
 */

#include "CtTimer.h"
#include "CtEventInterface.h"

#include <CtPlatforms.h>

CtTimer* CtTimer::m_pInstance = NULL;
const unsigned long CtTimer::m_CyclicTime(10);
unsigned long CtTimer::m_TotalTime(0);
unsigned long CtTimer::m_PrevTime(0);
const unsigned long CtTimer::m_TimeMax(0xFFFFFFFF);

CtTimer::CtTimerInfo::CtTimerInfo(int Uid, unsigned long Time, CtEventHandler* pObserver) :
	m_pObserver(pObserver),
	m_Time(Time),
	m_bAlive(true),
	m_Uid(Uid)
{
	m_StartTime = m_TotalTime;
}

CtTimer::CtTimerInfo::~CtTimerInfo()
{
}

void CtTimer::CtTimerInfo::notifyObserver(CtEventTimer& Timer)
{
	return;
}

CtEventHandler* CtTimer::CtTimerInfo::getObserver()
{
	return m_pObserver;
}

void CtTimer::CtTimerInfo::setAlive(bool bAlive)
{
	m_bAlive = bAlive;
}
bool CtTimer::CtTimerInfo::isAlive()
{
	return m_bAlive;
}

bool CtTimer::CtTimerInfo::isTimeout(unsigned long startTime, unsigned long interval, unsigned long currentTime)
{
	unsigned long diffTime = 0;

	if (startTime <= currentTime) {
		diffTime = currentTime - startTime;
	}
	else {
		// 開始時刻の方が現在時刻より大きいとき(現在時刻がオーバーフローしたとき)
		diffTime = m_TimeMax - startTime;
		diffTime += currentTime;
	}

	if (diffTime >= interval) {
		return true;
	}

	return false;
}

int CtTimer::CtTimerInfo::getTimerId() {
	return m_Uid;
}

CtTimer::CtTimerInfoCyclic::CtTimerInfoCyclic(int Uid, unsigned long Time, CtEventHandler* pObserver) : CtTimerInfo(Uid, Time, pObserver)
{
	setClassType(CtClassType_TimerInfoCyclic);
}

CtTimer::CtTimerInfoCyclic::~CtTimerInfoCyclic()
{
}

bool CtTimer::CtTimerInfoCyclic::update(CtTimer::CtTimerInfo* pTimerInfo, unsigned long CyclicTime, unsigned long TotalTime)
{
	if (isTimeout(m_StartTime, m_Time, TotalTime) == true) {
		m_StartTime += m_Time;
		return true;
	}

	return false;
}

void CtTimer::CtTimerInfoCyclic::notifyObserver(CtEventTimer& Timer)
{
	if (Timer.getInstance() == NULL)	return;
	const_cast<CtEventTimer&>(Timer).operationCmd();
}

CtTimer::CtTimerInfoAlarm::CtTimerInfoAlarm(int Uid, unsigned long Time, CtEventHandler* pObserver) : CtTimerInfo(Uid, Time, pObserver), m_isTimeout(false)
{
	setClassType(CtClassType_TimerInfoAlarm);
}

CtTimer::CtTimerInfoAlarm::~CtTimerInfoAlarm()
{
}

bool CtTimer::CtTimerInfoAlarm::update(CtTimer::CtTimerInfo* pTimerInfo, unsigned long CyclicTime, unsigned long TotalTime)
{
	if (m_isTimeout == false) {
		if (isTimeout(m_StartTime, m_Time, TotalTime) == true) {
			m_isTimeout = true;
			return true;
		}
	}

	return false;
}

void CtTimer::CtTimerInfoAlarm::notifyObserver(CtEventTimer& Timer)
{
	const_cast<CtEventTimer&>(Timer).operationCmd();

	// アラームはObserver実行が終われば無効状態になる
	m_pInstance->removeTimer(Timer.getTimeUid(), (CtEventHandler*)Timer.getInstance());
}

CtTimer::CtTimer()
{
	setClassType(CtClassType_Timer);

	syswrap_start_cyclic_handler(&ct_cyclic_handler);
	return;
}

CtTimer::~CtTimer()
{
	// m_ColTimerに要素が残っていたらAssert
	CtAssert(m_ColTimerInfo.size() > 0);
	m_ColTimerInfo.clear();

	return;
}

CtTimer* CtTimer::getInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new CtTimer();

	return m_pInstance;
}

bool CtTimer::addTimer(CtTimer::CtTimerInfo& TimerInfo)
{
	typedef CtList::list<CtTimerInfo*>::iterator Iterator;

	for (Iterator Itr = m_ColTimerInfo.begin(); Itr != m_ColTimerInfo.end(); ++Itr) {
		if (((*Itr)->isAlive() == true) && (*Itr)->getObserver() == TimerInfo.getObserver() && (*Itr)->getTimerId() == TimerInfo.getTimerId()) {
			// UniqueIDの同じTimerInfoの再始動
			// TimerInfoの古い方を捨てる
			(*Itr)->setAlive(false);
			break;
		}
	}
	TimerInfo.getObserver()->setUseFlag(EventTimer);
	m_ColTimerInfo.push_back(&TimerInfo);

	//	CtDebugPrint(CtDbg, "#### Timer Register (%d) ####\n", m_ColTimerInfo.size());

	return true;
}

void CtTimer::removeTimer(int Uid, CtEventHandler *pObserver)
{
	typedef CtList::list<CtTimerInfo*>::iterator Iterator;

	if (pObserver == NULL)
		return;

	for (Iterator Itr = m_ColTimerInfo.begin(); Itr != m_ColTimerInfo.end(); ++Itr) {
		if ((*Itr)->getObserver() == pObserver && (*Itr)->getTimerId() == Uid) {
			(*Itr)->setAlive(false);
			pObserver->clearUseFlag(EventTimer);
		}
	}
	//	CtDebugPrint(CtDbg, "#### Timer unRegister (%d) ####\n", m_ColTimerInfo.size());
	return;
}

void CtTimer::receiveFlg(unsigned int flgptn)
{
	checkTimeout();
	m_PrevTime = m_TotalTime;
}

void CtTimer::CycHandler()
{
	m_TotalTime += m_CyclicTime;
	
	CtComMainThread::setEvent(CtComMainThread::FLGPTN_MAIN_TIMER);

	return;
}

bool CtTimer::startCyclic(int Uid, unsigned long Time, CtEventHandler* pObserver)
{
	if (pObserver == NULL)
		return false;

	CtTimerInfo* pTimerInfo = new CtTimerInfoCyclic(Uid, Time, pObserver);	/* pgr0541	*/
	return addTimer(*pTimerInfo);
}

void CtTimer::stopCyclic(int Uid, CtEventHandler *pObserver)
{
	if (pObserver == NULL)
		return;

	removeTimer(Uid, pObserver);

	//	CtDebugPrint(CtDbg, "#### Timer unRegister (%d) ####\n", m_ColTimerInfo.size());
	return;
}

bool CtTimer::setAlarm(int Uid, unsigned long Time, CtEventHandler* pObserver)
{
	if (pObserver == NULL)
		return false;

	CtTimerInfo* pTimerInfo = new CtTimerInfoAlarm(Uid, Time, pObserver);	/* pgr0541	*/
	return addTimer(*pTimerInfo);
}

void CtTimer::cancelAlarm(int Uid, CtEventHandler* pObserver)
{
	if (pObserver == NULL)
		return;

	removeTimer(Uid, pObserver);
}

bool CtTimer::isActTimerId(int Uid, CtEventHandler* pObserver) {
	if (pObserver == NULL)
		return false;

	typedef CtList::list<CtTimerInfo*>::iterator Iterator;
	for (Iterator Itr = m_ColTimerInfo.begin(); Itr != m_ColTimerInfo.end(); ++Itr) {
		if ((*Itr)->getObserver() == pObserver && (*Itr)->getTimerId() == Uid) {
			return (*Itr)->isAlive();
		}
	}
	
	return false;
}


void CtTimer::stopTimer(CtEventHandler *pObserver)
{
	if (pObserver == NULL)
		return;

	typedef CtList::list<CtTimerInfo*>::iterator Iterator;
	
	for (Iterator Itr = m_ColTimerInfo.begin(); Itr != m_ColTimerInfo.end(); ++Itr) {
		if ((*Itr)->getObserver() == pObserver) {
			pObserver->clearUseFlag(EventTimer);
			(*Itr)->setAlive(false);
		}
	}
	//	CtDebugPrint(CtDbg, "#### Timer unRegister (%d) ####\n", m_ColTimerInfo.size());
	return;
}

bool CtTimer::checkTimeout()
{
	bool bRet = false;
	typedef CtList::list<CtTimerInfo*>::iterator Iterator;
	int size = 0;

	if (m_ColTimerInfo.size() <= 0) {
		m_TotalTime = 0;
		return bRet;
	}

	for (Iterator Itr = m_ColTimerInfo.begin(); Itr != m_ColTimerInfo.end(); ++Itr) {
		if (((*Itr)->isAlive() == true) && ((*Itr)->update((*Itr), m_CyclicTime, m_TotalTime) == true)) {
			CtEventTimer Timer = CtEventTimer((*Itr)->getTimerId(), (*Itr)->getObserver(), m_TotalTime - m_PrevTime);
			// EventのExecメソッドは各TimerInfoクラスのnotifyObserverメソッドで行う(再描画、Alarmクラスの破棄のため)
			(*Itr)->notifyObserver(Timer);
		}
	}

	Iterator Itr = m_ColTimerInfo.begin();
	while (Itr != m_ColTimerInfo.end()) {
		if ((*Itr)->isAlive() == false) {
			delete (*Itr);
			Itr = m_ColTimerInfo.erase(Itr);
		}
		else {	++Itr;	}
	}
	return bRet;
}

