/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version: 7.5.1
 *  Element:          CtFlash
 */


#include "CtFlash.h"
#include "CtTimer.h"


CtFlash* CtFlash::m_pInstance = NULL;

#define FLUSH_CYCTIME	250
#define FLUSH_1SEC		1000

CtFlash::CtFlashInfo::CtFlashInfo(CtEventFlash::Frequency Freq, CtEventHandler* pObserver) :
	m_pObserver(pObserver),
	m_Frequency(Freq)
{
	setClassType(CtClassType_FlashInfo);
}

CtFlash::CtFlashInfo::~CtFlashInfo()
{
}

CtFlash::CtFlash() :
	m_025Cnt(0),
	m_05Cnt(0),
	m_1Cnt(0),
	m_2Cnt(0)
{
   setClassType(CtClassType_Flash);

   CtTimer::getInstance()->startCyclic(CT_FLASH_TIMER_ID, FLUSH_CYCTIME, this);
   
   return;
}

CtFlash::~CtFlash()
{
	CtTimer::getInstance()->stopCyclic(CT_FLASH_TIMER_ID, this);
	
	if (m_InfoList.size() > 0)
		m_InfoList.clear();
	
    return;
}

CtFlash* CtFlash::getInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new CtFlash();

	return m_pInstance;
}

bool CtFlash::startFlash(CtEventFlash::Frequency Frequency, CtEventHandler* pObserver)
{
	bool bRet = false;
	
	if (pObserver == NULL)
		return false;
	
    CtFlashInfo* pFlashInfo = new CtFlashInfo(Frequency, pObserver);
	if ((bRet = addFlash(*pFlashInfo)) != true) {
		delete pFlashInfo;
	}
	
	return bRet;
}

void CtFlash::stopFlash(CtEventHandler *pObserver)
{
	if (pObserver == NULL)
		return;
	
	removeFlash(pObserver);
}

bool CtFlash::addFlash(CtFlash::CtFlashInfo& FlashInfo)
{
    typedef CtList::list<CtFlashInfo*>::iterator Iterator;
	
	CtEventFlash::Frequency Frequency = FlashInfo.getFrequency();

	for (Iterator Itr = m_InfoList.begin(); Itr != m_InfoList.end(); ++Itr) {
		if (((*Itr) != NULL) && ((*Itr)->getObserver() == FlashInfo.getObserver())) {
			return false;
		}
	}
	FlashInfo.getObserver()->setUseFlag(EventFlash);
	m_InfoList.push_back(&FlashInfo);
	
    return true;
}

void CtFlash::removeFlash(CtEventHandler *pObserver)
{
	if (pObserver == NULL)
		return;
	
	CtList::list<CtFlashInfo*>::iterator Itr = m_InfoList.begin();
	while (Itr != m_InfoList.end()) {
		if (((*Itr) != NULL) && (*Itr)->getObserver() == pObserver) {
			pObserver->clearUseFlag(EventFlash);
			delete (*Itr);
			Itr = m_InfoList.erase(Itr);
		}
		else {	++Itr;	}
	}
}

bool CtFlash::handleTimerEvent(const CtEventTimer& Timer)
{
    typedef CtList::list<CtFlashInfo*>::iterator Iterator;
	bool bShow = true;
	CtEventFlash::Frequency frequency = CtEventFlash::Freq_025Hz;
	bool bRet = false;
	
	m_2Cnt   = (m_2Cnt +1) % 2;
	m_1Cnt   = (m_1Cnt +1) % 4;
	m_05Cnt  = (m_05Cnt +1) % 8;
	m_025Cnt = (m_025Cnt +1) % 16;
            
	for (Iterator Itr = m_InfoList.begin(); Itr != m_InfoList.end(); ++Itr) {
		switch (frequency = (*Itr)->getFrequency()) {
		case CtEventFlash::Freq_025Hz:
			if (m_025Cnt / 8)	bShow = false;
			else				bShow = true;
			break;
		case CtEventFlash::Freq_05Hz:
			if (m_05Cnt / 4)	bShow = false;
			else				bShow = true;
			break;
		case CtEventFlash::Freq_1Hz:
			if (m_1Cnt / 2)		bShow = false;
			else				bShow = true;
			break;
		case CtEventFlash::Freq_2Hz:
			if (m_2Cnt)			bShow = false;
			else				bShow = true;
			break;
		default:
			break;
		}

		if ((*Itr)->setShowing(bShow) != true)
			continue;
		
		CtEventFlash pFlash = CtEventFlash(frequency, bShow);
		if ((*Itr)->getObserver()->handleFlashEvent(pFlash) == true)
			bRet = true;
	}
	
	return bRet;
}

bool CtFlash::isFlashing(CtEventHandler* pObserver)
{
	CtList::list<CtFlashInfo*>::iterator Itr = m_InfoList.begin();
	
	while (Itr != m_InfoList.end()) {
		if ((*Itr)->getObserver() == pObserver) {
			return true;
		}
		else { ++Itr; }
	}
	return false;
}

bool CtFlash::isShowing(CtEventHandler* pObserver)
{
	CtList::list<CtFlashInfo*>::iterator Itr = m_InfoList.begin();
	
	while (Itr != m_InfoList.end()) {
		if ((*Itr)->getObserver() == pObserver) {
			return (*Itr)->isShowing();
		}
		else { ++Itr; }
	}
	return true;
}

CtEventFlash::Frequency CtFlash::getFrequency(CtEventHandler* pObserver)
{
	CtList::list<CtFlashInfo*>::iterator Itr = m_InfoList.begin();
	
	while (Itr != m_InfoList.end()) {
		if ((*Itr)->getObserver() == pObserver) {
			return (*Itr)->getFrequency();
		}
		else { ++Itr; }
	}
	return CtEventFlash::Freq_Invalid;
}
