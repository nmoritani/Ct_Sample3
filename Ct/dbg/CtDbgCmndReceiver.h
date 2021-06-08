/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtDbgCmndReceiver
*/

#ifndef __CtDbgCmndReceiver_H__
#define __CtDbgCmndReceiver_H__

#include "CtObject.h"
#include "CtMsg.h"
#include "Ct.h"
#include "CtDbgCmnd.h"
#include "SysIf.h"
#include "CtDbgWindFuncRegister.h"
#include "CtMsgDbgCmnd.h"

using namespace CtDbgCmndDomain;

class CtDbgCmndReceiver :
	public CtObject
{
public:
	virtual void receiveMsg(const CtMsg& Msg);
	static CtDbgCmndReceiver* getInstance();
	~CtDbgCmndReceiver();

	// GroupâêÕ
	void cmndExec();

	// é¿çs
	void runWinTrans();
	void runRefInfo();
	void runVarietyFunc();
	void runShrtCutCmnd();
	void runSysKey();
	void runSysTouch();
	void runAplParam();
	void runAplEvnt();

private:
	CtMsgDbgCmnd* m_pCmdData;
	
	CtDbgCmndReceiver();
	
	SYS_KEY_STATUS m_keyStatus;
	SYS_TPANEL m_tPanel;
	static CtDbgCmndReceiver* m_pThis;

	unsigned long long  getSysKeyCode(unsigned short data, DbgCmndKeySrcId& keySrc);
	void dragAndSlideEvntExec(int x, int y);
	

	CtScreenSel			m_Sel;
	unsigned char		m_CmndGrp;
	unsigned char		m_CmndId;
	DbgCmndKeySrcId		m_KeySource;
	DbgCmndKeyActId		m_KeyAct;

	CtDbgWindFuncRegister* m_pFuncRegister;
};
#endif // __CtDbgCmndReceiver_H__
