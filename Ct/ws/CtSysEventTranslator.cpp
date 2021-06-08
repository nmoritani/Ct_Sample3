/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtSysEventTranslator
*/
#include "CtSysEventTranslator.h"
#include "CtEventInterface.h"

CtSysEventTranslator* CtSysEventTranslator::m_pThis(NULL);

CtSysEventTranslator::CtSysEventTranslator() :
	m_IsSlideEventReceive(false)
{
	setClassType(CtClassType_SysEventTranslator);
	SYS_Event_AddCallback((SYS_EVENT_CALLBACK)&CtSysEventTranslator::callbackSysSwitchEvent);
	SYS_TPanel_SetSlideEventEnable(TRUE);
	SYS_KEY_STATUS sysStatus = SYS_Key_GetStatus();
	m_PreDeck = sysStatus.Deck;
	m_PreDeck2 = sysStatus.Deck2;
	m_PreLanc = sysStatus.LancSw;
	m_LockSw = sysStatus.LockSw;
}

/* �f�X�g���N�^ */
CtSysEventTranslator::~CtSysEventTranslator()
{
	typedef CtList::list<CtKeyTimer*>::iterator Iterator;

	for (Iterator Itr = m_TimerList.begin(); Itr != m_TimerList.end(); ++Itr) {
		delete (*Itr);
		m_TimerList.remove(*Itr);
		if (m_TimerList.size() == 0 || Itr == m_TimerList.end()) {
			break;
		}
	}

	m_pThis = NULL;
}

/* �C���X�^���X�Ăяo�� (�V���O���g��) */
CtSysEventTranslator* CtSysEventTranslator::getInstance()
{
	if (m_pThis == NULL) {
		m_pThis = new CtSysEventTranslator();
	}
	return m_pThis;
}

bool CtSysEventTranslator::actionKey(SYS_KEY_STATUS& keyStatus)
{
	bool result = false;
	/* �g���L�[�̂ݑΉ� */
	/* ���s���тƂ� LongPress �̑Ή��Ƃ��͂��Ă��Ȃ� */

	/* �{�� LockSw */
	if (m_LockSw != keyStatus.LockSw) {
		m_LockSw = keyStatus.LockSw;
	}

	/* �L�[�̃}�X�N ���L�[�����̑O�Ɏ��{���邱�� */
	maskKey(keyStatus);

	/* �{�̃L�[ */
	unsigned long long change = m_PreDeck ^ keyStatus.Deck; /* �O��ʒm�L�[�Ƃ̍��������� */
	if (change) {
		m_KeySrc = CtEventKey::KeySource_Body;
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_UP, CtEventKey::KeyCode_Up);	/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_DOWN, CtEventKey::KeyCode_Down);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_LEFT, CtEventKey::KeyCode_Left);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_RIGHT, CtEventKey::KeyCode_Right);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_ENTER, CtEventKey::KeyCode_Enter);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_CAM_FUNC, CtEventKey::KeyCode_ManualFunction); /* �N���|������ *//* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_MNL_RING_PLUS, CtEventKey::KeyCode_MmrPlus); /* �N���|�����] *//* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_MNL_RING_MINUS, CtEventKey::KeyCode_MmrMinus); /* �N���|������] *//* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_MODE, CtEventKey::KeyCode_Thumb);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_MENU, CtEventKey::KeyCode_Menu);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_CANCEL, CtEventKey::KeyCode_Exit);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_AUDIO_PLUS, CtEventKey::KeyCode_AudioPlus);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck, change, SYS_KEY_AUDIO_MINUS, CtEventKey::KeyCode_AudioMinus);/* pgr2711 */
		m_PreDeck = keyStatus.Deck;
	}

	/* �{�̃L�[2 : �R�[�h���Ⴄ�����ŏ����� 1 �Ɠ��� */
	change = m_PreDeck2 ^ keyStatus.Deck2;
	if (change) {
		m_KeySrc = CtEventKey::KeySource_Body2;
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_CANCEL, CtEventKey::KeyCode_Exit);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_HOME, CtEventKey::KeyCode_Home);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY_MENU2, CtEventKey::KeyCode_Menu);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_IRIS_FUNC, CtEventKey::KeyCode_IrisFunc);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER1, CtEventKey::KeyCode_User1);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER2, CtEventKey::KeyCode_User2);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER3, CtEventKey::KeyCode_User3);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER4, CtEventKey::KeyCode_User4);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER5, CtEventKey::KeyCode_User5);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER6, CtEventKey::KeyCode_User6);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER7, CtEventKey::KeyCode_User7);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER8, CtEventKey::KeyCode_User8);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_USER9, CtEventKey::KeyCode_User9);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_TC, CtEventKey::KeyCode_Reset);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.Deck2, change, SYS_KEY2_CHECK, CtEventKey::KeyCode_DispCheck);/* pgr2711 */
		m_PreDeck2 = keyStatus.Deck2;
	}

	/* K519�ł�K460����Grip(Lanc)�����Ƃ��Ă������̂�Lanc�Ƃ��Ĉ���(SysPort�ύX�Ή��ɂ��)*/
	/* �����N�L�[ : �R�[�h���Ⴄ�����ŏ����� Deck1, Deck2 �Ɠ��� */
	/* Lanc��Focus/Zoom��GUI�ŏ������Ȃ� */
	change = m_PreLanc ^ keyStatus.LancSw;
	if (change) {
		m_KeySrc = CtEventKey::KeySource_Lanc;
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_MENU, CtEventKey::KeyCode_GripMenu);/* pgr2711 */
		//result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_DIAL_FUNC, CtEventKey::KeyCode_ManualFunction);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_RIGHT, CtEventKey::KeyCode_Right);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_EXECUTE, CtEventKey::KeyCode_ManualFunction);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_LEFT, CtEventKey::KeyCode_Left);/* pgr2711 */
		//result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_DIAL_PLUS, CtEventKey::KeyCode_MmrPlus);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_UP, CtEventKey::KeyCode_Up);/* pgr2711 */
		//result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_DIAL_MINUS, CtEventKey::KeyCode_MmrMinus);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_DOWN, CtEventKey::KeyCode_Down);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER1, CtEventKey::KeyCode_GripUser1);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER2, CtEventKey::KeyCode_GripUser2);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER3, CtEventKey::KeyCode_GripUser3);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER4, CtEventKey::KeyCode_GripUser4);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER5, CtEventKey::KeyCode_GripUser5);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER6, CtEventKey::KeyCode_GripUser6);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER7, CtEventKey::KeyCode_GripUser7);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER8, CtEventKey::KeyCode_GripUser8);/* pgr2711 */
		result |= actionKeyDeck(keyStatus.LancSw, change, SYS_LANC_USER9, CtEventKey::KeyCode_GripUser9);/* pgr2711 */
		m_PreLanc = keyStatus.LancSw;
	}
	return result;
}

/* �{�̃L�[�̃I�u�U�[�o�[�ʒm */
bool CtSysEventTranslator::actionKeyDeck(unsigned long long keyDeck, unsigned long long keyChange, unsigned long long sysKey, CtEventKey::KeyCode ctKey)
{
	bool result = false;
	if (keyChange & sysKey) {
		CtEventKey::KeyAction action = (keyDeck & sysKey) ? CtEventKey::Press : CtEventKey::Release;
		CtDebugPrint(CtDbgIdCmd, "(%d,%d,%d,%d,%d)\n", ScreenAll, ID_SYS_KEY, m_KeySrc, action, ctKey);

		result = CtEventKey(action, ctKey, CtEventKey::KeySource_Body).exec();

		if (action == CtEventKey::Press) {
			CtList::list<CtKeyTimer*>::iterator itr;
			for (itr = m_TimerList.begin(); itr != m_TimerList.end(); itr++) {
				if ((*itr)->getKeyCode() == ctKey) {
					// ����KeyTimer�͍쐬����Ă���̂Ŕ�����
					return result;
				}
			}
			CtKeyTimer *pTimer = new CtKeyTimer(ctKey, 250);
			m_TimerList.push_back(pTimer);
			// Dial�������݉񂵗p���z�L�[
			startVirtualDialKey(sysKey, keyDeck);
		}
		else if(action == CtEventKey::Release){
			endKeyTimer(ctKey);
			if (SYS_KEY_CAM_FUNC & (keyChange & sysKey)) {
				endKeyTimer(CtEventKey::KeyCode_DialPressUp);
				endKeyTimer(CtEventKey::KeyCode_DialPressDown);
			}
		}
	}
	return result;
}

bool CtSysEventTranslator::startVirtualDialKey(unsigned long long sysKey, unsigned long long keyDeck) {
	CtEventKey::KeyCode startKey = CtEventKey::KeyCode_Invalid;
	CtEventKey::KeyCode endKey = CtEventKey::KeyCode_Invalid;
	if (sysKey == SYS_KEY_MNL_RING_PLUS && SYS_KEY_CAM_FUNC & keyDeck) {
		startKey = CtEventKey::KeyCode_DialPressUp;
		endKey = CtEventKey::KeyCode_DialPressDown;
	}
	else if (sysKey == SYS_KEY_MNL_RING_MINUS && SYS_KEY_CAM_FUNC & keyDeck) {
		startKey = CtEventKey::KeyCode_DialPressDown;
		endKey = CtEventKey::KeyCode_DialPressUp;
	}
	if (startKey == CtEventKey::KeyCode_Invalid) {
		return false;
	}
	
	CtList::list<CtKeyTimer*>::iterator itr;
	for (itr = m_TimerList.begin(); itr != m_TimerList.end(); itr++) {
		if ((*itr)->getKeyCode() == startKey) {
			endKeyTimer(endKey);
			// ����KeyTimer�͍쐬����Ă���̂Ŕ�����
			return false;
		}
	}

	CtKeyTimer *pTimer = new CtKeyTimer(startKey, 250);
	m_TimerList.push_back(pTimer);
	// �Ώ�Key�I��
	endKeyTimer(endKey);
	return CtEventKey(CtEventKey::Press, startKey, CtEventKey::KeySource_Body).exec();
}

bool CtSysEventTranslator::endKeyTimer(CtEventKey::KeyCode ctKey) {
	CtList::list<CtKeyTimer*>::iterator Itr = m_TimerList.begin();
	while (Itr != m_TimerList.end()) {
		if ((*Itr)->getKeyCode() == ctKey) {
			delete (*Itr);
			Itr = m_TimerList.erase(Itr);
		}
		else { ++Itr; }
	}
	return false;
}

/* �L�[�̃}�X�N���� */
void CtSysEventTranslator::maskKey(SYS_KEY_STATUS& status)
{
	unsigned long long maskDeck = 0;
	unsigned long long maskDeck2 = 0;

	if (m_LockSw == SYS_LOCK_SW_ON) {
		if (APL_SYS_PARAM_SIDE_LOCK_LOCK == APL_PARAM_GET_DATA(AplParamSideLockMultiDial)) {
			maskDeck |= (SYS_KEY_CAM_FUNC | SYS_KEY_MNL_RING_PLUS | SYS_KEY_MNL_RING_MINUS);
		}
		if (APL_SYS_PARAM_SIDE_LOCK_LOCK == APL_PARAM_GET_DATA(AplParamSideLockExitButton)) {
			maskDeck2 |= SYS_KEY2_CANCEL;
		}
	}

	/* �}�X�N���ꂽ�L�[�͓��삳���Ȃ� */
	status.Deck &= ~maskDeck;
	status.Deck2 &= ~maskDeck2;
}

/* SYS �擾�����L�[�������ɃC�x���g�𔭍s */
void CtSysEventTranslator::callbackSysSwitchEvent(unsigned long event, SYS_EVENT_DATA data)
{
	if (m_pThis) {
		CtEventInterface::requestSysCmd(event, data);
	}
}
