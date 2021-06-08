/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtReceiverId
*/

#ifndef __CtSysEventTranslator_H__
#define __CtSysEventTranslator_H__

#include "CtObject.h"
#include "CtEvent.h"
#include "CtList.h"
#include "CtKeyTimer.h"

class CtSysEventTranslator :
	public CtObject
{
public:
	virtual ~CtSysEventTranslator();
	static CtSysEventTranslator* getInstance();
	bool actionKey(SYS_KEY_STATUS& keyStatus);
	
private:
	CtSysEventTranslator();
	bool actionKeyDeck(unsigned long long keyDeck, unsigned long long keyChange, unsigned long long sysKey, CtEventKey::KeyCode keyCode);
	void maskKey(SYS_KEY_STATUS& status);
	static void callbackSysSwitchEvent(unsigned long event, SYS_EVENT_DATA data);
	bool startVirtualDialKey(unsigned long long syskey, unsigned long long keyDeck);
	bool endKeyTimer(CtEventKey::KeyCode ctKey);

	static CtSysEventTranslator* m_pThis;
	CtList::list<CtKeyTimer*> m_TimerList;
	bool m_IsSlideEventReceive;


	/* 前回のキー状態 */
	unsigned long long m_PreDeck;
	unsigned long long m_PreDeck2;
	unsigned long long m_PreLanc;
	
	// キー変更時のデバッグ
	CtEventKey::KeySource m_KeySrc;
	/* キーのマスク状態 */
	unsigned char m_LockSw;
};

#endif /* __CtSysEventTranslator_H__ */
