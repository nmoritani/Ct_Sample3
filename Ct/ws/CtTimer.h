/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtTimerType
 */


#ifndef __CtTimer_H__
#define __CtTimer_H__

#include "kernel.h"

#include <CtList.h>
#include "CtObject.h"
#include "CtEvent.h"
#include "CtEventHandler.h"

typedef enum CtTimerType {
    CtTimerType_Cyclic,
    CtTimerType_Alarm
} CtTimerType;

///@brief �A�v���Ŏg�p����^�C�}�Ǘ��N���X
class CtTimer : public CtObject {
public :

    class CtTimerInfo;
    
    class CtTimerInfoAlarm;
    
    class CtTimerInfoCyclic;

	/// �^�C�}�[���Ǘ��̊��N���X
    class CtTimerInfo : public CtObject {
    public :
        CtTimerInfo(int  Uid, unsigned long Time, CtEventHandler* pObserver);
        virtual ~CtTimerInfo();
        virtual bool update(CtTimerInfo* pTimerInfo, unsigned long CyclicTime, unsigned long TotalTime) = 0;
        virtual void notifyObserver(CtEventTimer& Timer) = 0;
		CtEventHandler* getObserver();
		virtual void setAlive(bool bAlive);
		virtual bool isAlive();
		int getTimerId();
    protected :
    	bool isTimeout(unsigned long startTime, unsigned long interval, unsigned long currentTime);
    	
		unsigned long m_Time;
        unsigned long m_StartTime;
		bool m_bAlive;
		CtEventHandler* m_pObserver;
	private:
		int m_Uid;
    };
    
    /// �T�C�N���b�N�^�C�}�[���Ǘ��N���X
    class CtTimerInfoCyclic : public CtTimerInfo {
    public :
        CtTimerInfoCyclic(int Uid, unsigned long Time, CtEventHandler* pObserver);
        ~CtTimerInfoCyclic();
        virtual bool update(CtTimerInfo* pTimerInfo, unsigned long CyclicTime, unsigned long TotalTime);
        virtual void notifyObserver(CtEventTimer& Timer);
    };
    
    /// �A���[���^�C�}�[���Ǘ��N���X
    class CtTimerInfoAlarm : public CtTimerInfo {
    public :
        CtTimerInfoAlarm(int Uid, unsigned long Time, CtEventHandler* pObserver);
        ~CtTimerInfoAlarm();
        virtual bool update(CtTimerInfo* pTimerInfo, unsigned long CyclicTime, unsigned long TotalTime);
        virtual void notifyObserver(CtEventTimer& Timer);
    private :
    	bool m_isTimeout;
    };

public :
    ~CtTimer();
	
    /// �^�C�}�[�T�[�r�X�̃|�C���^���擾����B
    static CtTimer* getInstance();
	
    /// �T�C�N���b�N�n���h��
    static void CycHandler(VP_INT exinf);
	
	void receiveFlg(FLGPTN flgptn);

    /// �����^�C�}�[
    bool startCyclic(int Uid, unsigned long Time, CtEventHandler* pObserver);
	void stopCyclic(int Uid, CtEventHandler* pObserver);
	
    /// �A���[���^�C�}�[
    bool setAlarm(int Uid, unsigned long Time, CtEventHandler* pObserver);
	void cancelAlarm(int Uid, CtEventHandler* pObserver);

	// TimerID�̋N���m�F
	bool isActTimerId(int Uid, CtEventHandler* pObserver);
	

	// Obj��Timer��S�č폜
	void stopTimer(CtEventHandler* pObserver);
	
    bool checkTimeout();

private :
    CtTimer();
    bool addTimer(CtTimerInfo& TimerInfo);
    void removeTimer(int Uid, CtEventHandler* pObserver);
	
private :
    static const unsigned long m_CyclicTime;
    static unsigned long m_TotalTime;
    static unsigned long m_PrevTime;
	static const unsigned long m_TimeMax;
    static CtTimer* m_pInstance;
	
    CtList::list<CtTimerInfo*> m_ColTimerInfo;
};

#endif
