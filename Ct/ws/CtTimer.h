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

///@brief アプリで使用するタイマ管理クラス
class CtTimer : public CtObject {
public :

    class CtTimerInfo;
    
    class CtTimerInfoAlarm;
    
    class CtTimerInfoCyclic;

	/// タイマー情報管理の基底クラス
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
    
    /// サイクリックタイマー情報管理クラス
    class CtTimerInfoCyclic : public CtTimerInfo {
    public :
        CtTimerInfoCyclic(int Uid, unsigned long Time, CtEventHandler* pObserver);
        ~CtTimerInfoCyclic();
        virtual bool update(CtTimerInfo* pTimerInfo, unsigned long CyclicTime, unsigned long TotalTime);
        virtual void notifyObserver(CtEventTimer& Timer);
    };
    
    /// アラームタイマー情報管理クラス
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
	
    /// タイマーサービスのポインタを取得する。
    static CtTimer* getInstance();
	
    /// サイクリックハンドラ
    static void CycHandler(VP_INT exinf);
	
	void receiveFlg(FLGPTN flgptn);

    /// 周期タイマー
    bool startCyclic(int Uid, unsigned long Time, CtEventHandler* pObserver);
	void stopCyclic(int Uid, CtEventHandler* pObserver);
	
    /// アラームタイマー
    bool setAlarm(int Uid, unsigned long Time, CtEventHandler* pObserver);
	void cancelAlarm(int Uid, CtEventHandler* pObserver);

	// TimerIDの起動確認
	bool isActTimerId(int Uid, CtEventHandler* pObserver);
	

	// ObjのTimerを全て削除
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
