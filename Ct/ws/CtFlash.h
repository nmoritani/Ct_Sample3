/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtFlash
 */


#ifndef __CtFlash_H__
#define __CtFlash_H__

#include <CtList.h>
#include "CtObject.h"
#include "CtEvent.h"
#include "CtEventHandler.h"

const int CT_FLASH_TIMER_ID = 0;

class CtFlash : public CtEventHandler {
public :
    class CtFlashInfo;
    class CtFlashInfo : public CtObject {
    public :
        CtFlashInfo(CtEventFlash::Frequency Frequency, CtEventHandler* pObserver);
        virtual ~CtFlashInfo();
		CtEventHandler* getObserver();
		CtEventFlash::Frequency getFrequency();
		bool isShowing();
		bool setShowing(bool bShowing);
	private:
		CtEventFlash::Frequency m_Frequency;
		CtEventHandler* m_pObserver;
		bool m_bShowing;
    };
public :
    virtual ~CtFlash();
	
    static CtFlash* getInstance();
	
    bool startFlash(CtEventFlash::Frequency Frequency, CtEventHandler* pObserver);
	void stopFlash(CtEventHandler* pObserver);
	bool isFlashing(CtEventHandler* pObserver);
	bool isShowing(CtEventHandler* pObserver);
	CtEventFlash::Frequency getFrequency(CtEventHandler* pObserver);
	virtual bool handleTimerEvent(const CtEventTimer& Timer);
	
private :
    CtFlash();
    bool addFlash(CtFlashInfo& FlashInfo);
    void removeFlash(CtEventHandler* pObserver);

private :
    static CtFlash* m_pInstance;
	unsigned long m_Counter;
	unsigned long m_025Cnt;
	unsigned long m_05Cnt;
	unsigned long m_1Cnt;
	unsigned long m_2Cnt;
	
    CtList::list<CtFlashInfo*> m_InfoList;
};

inline CtEventFlash::Frequency CtFlash::CtFlashInfo::getFrequency()
{
	return m_Frequency;
}

inline bool CtFlash::CtFlashInfo::isShowing()
{
	return m_bShowing;
}

inline bool CtFlash::CtFlashInfo::setShowing(bool bShowing)
{
	if (m_bShowing == bShowing)
		return false;
	
	m_bShowing = bShowing;
	return true;
}

inline CtEventHandler* CtFlash::CtFlashInfo::getObserver()
{
	return m_pObserver;
}

#endif
