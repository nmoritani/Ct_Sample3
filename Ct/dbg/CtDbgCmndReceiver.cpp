/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtDbgCmndReceiver
*/
#include <stdlib.h>
#include "CtDbgCmndReceiver.h"
#include "CtInterface.h"
#include "CtEventInterface.h"
#include "CtDbgCmndAdapter.h"

#include "CtMsgDbgCmnd.h"
#include "CtDbgVarietyFunc.h"
#include "CtDbgClassInfo.h"
#include "CtMplDbg.h"
#include "CtWindowIDString.h"

CtDbgCmndReceiver* CtDbgCmndReceiver::m_pThis(NULL); /* static pointer */

CtDbgCmndReceiver::CtDbgCmndReceiver()
{
	setClassType(CtClassType_DbgCommandReceiver);
	memset(&m_keyStatus, 0, sizeof(m_keyStatus));
	m_pFuncRegister = new CtDbgWindFuncRegister();
}

void CtDbgCmndReceiver::receiveMsg(const CtMsg& Msg) {

	m_pCmdData = static_cast<CtMsgDbgCmnd*>(const_cast<CtMsg*>(&Msg));
	cmndExec( );

	// Free
	CtDbgCmndAdapter::Free(m_pCmdData);
	m_pCmdData = NULL;
}

CtDbgCmndReceiver::~CtDbgCmndReceiver()
{
	if (m_pFuncRegister != NULL)	delete m_pFuncRegister;

	m_pThis = NULL;
}

/* インスタンス呼び出し (シングルトン) */
CtDbgCmndReceiver* CtDbgCmndReceiver::getInstance()
{
	if (m_pThis == NULL) {
		m_pThis = new CtDbgCmndReceiver();
	}
	return m_pThis;
}

void CtDbgCmndReceiver::cmndExec() {
	if (m_pCmdData == NULL) return;

	switch (m_pCmdData->getCmdGrp() ) {
	case ID_WIND:
		runWinTrans();
		break;
	case ID_REF_INFO:
		runRefInfo();
		break;
	case ID_VAR_FUNC:
		runVarietyFunc();
		break;
	case ID_SHRT_CUT:
		runShrtCutCmnd();
		break;
	case ID_SYS_KEY:
		runSysKey();
		break;
	case ID_SYS_TOUCH:
		runSysTouch();
		break;
	case ID_APL_PARAM:
		runAplParam();
		break;
	case ID_APL_EVNT:
		runAplEvnt();
		break;
		//case ID_INVALID:
	case ID_EVENT_GROUP_MAX:
	default:
		CtDebugPrint(CtDbg, "Not Available This Cmnd Group\n");
		break;
	}
}

void CtDbgCmndReceiver::runWinTrans() {
	CtInterface* pIfc = CtInterface::getInstance();
	m_Sel = (CtScreenSel)((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->screen;
	m_CmndId = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->cmdId;

	CtWindowID WindowID = (CtWindowID)((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->data;

	switch (m_CmndId) {
	case ID_CHANGE:
		pIfc->changeWindow(m_Sel, WindowID);
		break;
	case ID_RETURN:
		pIfc->returnWindow(m_Sel, WindowID);
		break;
	case ID_POPUP:
		pIfc->popupWindow(m_Sel, WindowID);
		break;
	case ID_CLOSE:
		pIfc->closeWindow(m_Sel, WindowID);
		break;
	case ID_SWAP:
		pIfc->swapWindow(m_Sel, WindowID);
		break;
	case ID_REMOVE:
		pIfc->removeWindow(m_Sel, WindowID);
		break;
	case ID_INVALID:
	case ID_WIN_TRANS_MAX:
	default:
		CtDebugPrint(CtDbg, "Not Available This Wind ID\n");
		return;
	}
}

#include "CtDbgWidgetTree.h"

void CtDbgCmndReceiver::runRefInfo() {
	m_CmndId = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->cmdId;
	m_Sel = (CtScreenSel)((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->screen;
	int data = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->data;

	CtInterface* pIfc = CtInterface::getInstance();
	switch (m_CmndId) {
	case ID_ROOT:
		// 取得時にLog出力される
		pIfc->getRootWindowID(m_Sel);
		break;
	case ID_CRNT:
	{
		// 取得時にLog出力される
		CtWindowID id = pIfc->getCurrentWindowID(m_Sel);
		CtDebugPrint(CtDbg, "CurrentWindow(%#x, %#010x, %s)\n", m_Sel, id, CtWindowIDString::getString(id));
	}
	break;
	case ID_OUTLINE:
		CtDbgWidgetTree::getInstance()->registCreateFinCall(data);
		pIfc->outputWindowOutline(m_Sel, pIfc->getCurrentWindowID(m_Sel));
		CtDbgWidgetTree::getInstance()->endCreateTreeData();
		break;
	case ID_CLASSINFO:
		CtDbgClassInfo::printClassInfo();
		break;
	case ID_MEMINFO:
		CtMplDbg::Output();
		break;
	case ID_INVALID:
	case ID_REF_INFO_MAX:
	default:
		CtDebugPrint(CtDbg, "Not Available This Cmnd ID\n");
		return;
	}
}

void CtDbgCmndReceiver::runVarietyFunc() {
	m_CmndId = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->cmdId;

	CtInterface* pIfc = CtInterface::getInstance();
	switch (m_CmndId) {
	case ID_VAR_FUNC_1:
		CtDbgVarietyFunc::varietyFunc1();
		break;
	case ID_VAR_FUNC_2:
		CtDbgVarietyFunc::varietyFunc2();
		break;
	case ID_VAR_FUNC_3:
		CtDbgVarietyFunc::varietyFunc3();
		break;
	case ID_VAR_FUNC_4:
		CtDbgVarietyFunc::varietyFunc4();
		break;
	case ID_VAR_FUNC_5:
		CtDbgVarietyFunc::varietyFunc5();
		break;
	case ID_VAR_FUNC_6:
		CtDbgVarietyFunc::varietyFunc6();
		break;
	case ID_VAR_FUNC_7:
		CtDbgVarietyFunc::varietyFunc7();
		break;
	case ID_VAR_FUNC_8:
		CtDbgVarietyFunc::varietyFunc8();
		break;
	case ID_INVALID:
	case ID_VAR_FUNC_MAX:
	default:
		CtDebugPrint(CtDbg, "Not Available This Cmnd ID\n");
		return;
	}
}

void CtDbgCmndReceiver::runShrtCutCmnd() {
	m_CmndId = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->cmdId;
	m_Sel = (CtScreenSel)((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->screen;

	CtInterface* pIfc = CtInterface::getInstance();
	CtWindowID winId = WindowNone;
	switch (m_CmndId) {
	case ID_SHRT_HOME:
		winId = Window_Home;
		break;
	case ID_SHRT_MENU:
		winId = WindowID_Menu_TOP;
		break;
	case ID_SHRT_VIEW:
		winId = Window_RecView;
		break;
	case ID_SHRT_THUM:
		winId = Window_ThumbNail;
		break;
	case ID_SHRT_INFO:
		winId = Window_Rec_Mode_Check;
		break;
	case ID_SHRT_PLAY:
		winId = Window_PlayView;
		break;
	case ID_SHRT_CLIP:
		winId = Window_ThumbNailClip;
		break;
	case ID_INVALID:
	case ID_SHRT_CUT_MAX:
	default:
		CtDebugPrint(CtDbg, "Not Available This Cmnd ID\n");
		return;
	}
	pIfc->popupWindow(m_Sel, (CtWindowID)winId);
}

void CtDbgCmndReceiver::runSysKey() {
	m_Sel = (CtScreenSel)((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->screen;
	m_KeySource = (DbgCmndKeySrcId)((CtDbgCmndAdapter::CmdKey*)(m_pCmdData->getData()))->keySource;
	m_KeyAct = (DbgCmndKeyActId)((CtDbgCmndAdapter::CmdKey*)(m_pCmdData->getData()))->keyAct;
	int data = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->data;

	CtInterface* pIfc = CtInterface::getInstance();
	
	switch (m_KeyAct) {
	case ID_INVALID:
	case ID_KEY_ACT_MAX:
		CtDebugPrint(CtDbg, "Not Available This KeyAct\n");
		return;
	default:
		break;
	}
	unsigned long long keyCode = getSysKeyCode(data, m_KeySource);
	switch (m_KeySource) {
	case ID_DECK:
		if (m_KeyAct != CtEventKey::Release) {
			m_keyStatus.Deck |= keyCode;
		}
		else {
			m_keyStatus.Deck &= ~keyCode;
		}
		break;
	case ID_DECK2:
		if (m_KeyAct != CtEventKey::Release) {
			m_keyStatus.Deck2 |= keyCode;
		}
		else {
			m_keyStatus.Deck2 &= ~keyCode;
		}
		break;
	case ID_GRIP:
		if (m_KeyAct != CtEventKey::Release) {
			// K519ではGripはLancで処理
			m_keyStatus.LancSw |= keyCode;
		}
		else {
			// K519ではGripはLancで処理
			m_keyStatus.LancSw &= ~keyCode;
		}
		break;
	case ID_Controller:
		pIfc->putRopEvent((CtEventKey::KeyCode)keyCode, (CtEventKey::KeyAction)m_KeyAct);
		return;
		break;
	case ID_REMOCON:
		break;
	case ID_CEC:
		break;
	case ID_SELF:
		break;
	case ID_INVALID:
	case ID_SRC_MAX:
	default:
		CtDebugPrint(CtDbg, "Not Available This KeySrc\n");
	}

	/* SYS 取得したキー情報を元にイベントを発行 */
	CtEventInterface::requestSysCmd(SYS_EVENT_KEY_STATUS_CHANGED, (SYS_EVENT_DATA&)m_keyStatus);
}

void CtDbgCmndReceiver::runSysTouch() {
	m_CmndId = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->cmdId;
	m_Sel = (CtScreenSel)((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->screen;
	int data = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->data;

	CtInterface* pIfc = CtInterface::getInstance();
	bool touched = true;
	unsigned long event = SYS_EVENT_TPANEL_TOUCHED;
	int x = ((CtDbgCmndAdapter::CmdSys*)(m_pCmdData->getData()))->posX;
	int y = ((CtDbgCmndAdapter::CmdSys*)(m_pCmdData->getData()))->posY;
	SYS_EVENT_DATA sysData = { 0 };

	switch (m_CmndId) {
	case ID_TCH_PRS:
		event = SYS_EVENT_TPANEL_TOUCHED;
		break;
	case ID_TCH_RLS:
	{
		touched = false;
		event = SYS_EVENT_TPANEL_RELEASED;
	}
	break;
	case ID_TCH_MV:
	case ID_TCH_SLIDE:
	{
		event = SYS_EVENT_TPANEL_DRAG;
		dragAndSlideEvntExec(x, y);
		return;
	}
	break;
	case ID_INVALID:
	case ID_TCH_MAX:
	default:
	{
		CtDebugPrint(CtDbg, "Not Available This Cmnd ID\n");
		return;
	}
	}

	/* SYS 取得したTouch情報を元にイベントを発行 */
	memset(&m_tPanel, 0, sizeof(m_tPanel));
	m_tPanel.Touched = touched;
	m_tPanel.X = x;
	m_tPanel.Y = y;
	m_tPanel.SlideStartX = m_tPanel.X;
	m_tPanel.SlideStartY = m_tPanel.Y;
	sysData.TPanel = m_tPanel;
	CtEventInterface::requestSysCmd(event, (SYS_EVENT_DATA&)sysData);
}

void CtDbgCmndReceiver::dragAndSlideEvntExec(int x, int y) {
	/* 前回通知した位置をバックアップ */
	SYS_EVENT_DATA sysData = { 0 };
	int preX = m_tPanel.X;
	int preY = m_tPanel.Y;

	m_tPanel.X = x;
	m_tPanel.Y = y;

	/* SlideStart は既に入っている */
	m_tPanel.SlidePreX = preX;
	m_tPanel.SlidePreY = preY;

	/* 前回と今回の位置変化でスピード、方向を決定 */
	int divX = m_tPanel.X - m_tPanel.SlidePreX;
	int divY = ((m_tPanel.Y - m_tPanel.SlidePreY) * 16) / 9; /* 同じ比率になるよう補正 */
	int displacement = (abs(divX) > abs(divY)) ? divX : divY; /* 変位量 */

	if (abs(divX) > abs(divY)) { /* X 方向の変位が大きい */
		m_tPanel.SlideDir = (divX > 0) ? SYS_TPANEL_SLIDE_RIGHT : SYS_TPANEL_SLIDE_LEFT;
		displacement = abs(divX);
	}
	else {					/* Y 方向の変位が大きい */
		m_tPanel.SlideDir = (divY > 0) ? SYS_TPANEL_SLIDE_DOWN : SYS_TPANEL_SLIDE_UP;
		displacement = abs(divY);
	}

	if (displacement == 0) {
		m_tPanel.SlideSpeed = 0;
	}
	else if (displacement < 20) {
		m_tPanel.SlideSpeed = 1;
	}
	else if (displacement < 40) {
		m_tPanel.SlideSpeed = 2;
	}
	else if (displacement < 60) {
		m_tPanel.SlideSpeed = 3;
	}
	else if (displacement < 80) {
		m_tPanel.SlideSpeed = 4;
	}
	else if (displacement < 100) {
		m_tPanel.SlideSpeed = 5;
	}
	else if (displacement < 120) {
		m_tPanel.SlideSpeed = 6;
	}
	else if (displacement < 140) {
		m_tPanel.SlideSpeed = 7;
	}
	else {
		m_tPanel.SlideSpeed = 8;
	}
	sysData.TPanel = m_tPanel;
	CtEventInterface::requestSysCmd(SYS_EVENT_TPANEL_DRAG, (SYS_EVENT_DATA&)sysData);
	CtEventInterface::requestSysCmd(SYS_EVENT_TPANEL_SLIDE, (SYS_EVENT_DATA&)sysData);
}

void CtDbgCmndReceiver::runAplParam() {
	CtInterface* pIfc = CtInterface::getInstance();
	
	unsigned int paramId = ((CtDbgCmndAdapter::CmdParam*)(m_pCmdData->getData()))->Id;
	m_CmndId = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->cmdId;
	int paramVal = ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->data;
	int size = AplParamService::getInstance()->getSize(paramId);

	switch (m_CmndId) {
	case ID_PARAM_NUM:
		//m_CmndData64Bit
		APL_PARAM_SET_DATA(paramId, paramVal);
		break;
	case ID_PARAM_IP:
	{
		int i = 0;
		if (size <= 4) {
			unsigned char _addrVal[4] = { 0 };
			_addrVal[0] = ((unsigned char*)paramVal)[0];
			_addrVal[1] = ((unsigned char*)paramVal)[1];
			_addrVal[2] = ((unsigned char*)paramVal)[2];
			_addrVal[3] = ((unsigned char*)paramVal)[3];
			APL_PARAM_SET_DATA_AREA((int)paramId, _addrVal, size);
		}
		else {
			unsigned char _addrVal[6] = { 0 };
			_addrVal[0] = ((unsigned char*)paramVal)[0];
			_addrVal[1] = ((unsigned char*)paramVal)[1];
			_addrVal[2] = ((unsigned char*)paramVal)[2];
			_addrVal[3] = ((unsigned char*)paramVal)[3];
			_addrVal[4] = ((unsigned char*)paramVal)[4];
			_addrVal[5] = ((unsigned char*)paramVal)[5];
			APL_PARAM_SET_DATA_AREA((int)paramId, _addrVal, size);
		}
		free((unsigned char*)paramVal);
	}
	break;
	case ID_PARAM_STRING:
	{
		int i = 0;
		APL_PARAM_SET_DATA_AREA((int)paramId, (unsigned char*)paramVal, size);
		free((unsigned char*)paramVal);
	}
	break;
	case ID_PARAM_MAX:
	default:
		CtDebugPrint(CtDbg, "Not Available This Cmnd ID\n");
		return;
	}
}

void CtDbgCmndReceiver::runAplEvnt() {
	CtInterface* pIfc = CtInterface::getInstance();

	switch (m_CmndId) {
	case ID_PERM_DRAW:
		pIfc->permitDrawing(m_Sel, ((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->data ? true : false);
		break;
	case ID_PERM_TRNS:
		pIfc->permitTransition(((CtDbgCmndAdapter::Cmd*)(m_pCmdData->getData()))->data ? true : false);
		break;
	case ID_EVNT_FILT:
		//pIfc->setEventFilter((CtWindowID)m_CmndData64Bit, );
		break;
	case ID_INVALID:
	case ID_APL_EVNT_MAX:
	default:
		CtDebugPrint(CtDbg, "Not Available This Cmnd ID\n");
		return;
	}
}

unsigned long long CtDbgCmndReceiver::getSysKeyCode(unsigned short data, DbgCmndKeySrcId& keySrc) {
	switch (data) {
	case ID_KEY_UP:
	{
		if (keySrc == ID_DECK) return SYS_KEY_UP;
		if (keySrc == ID_GRIP) return SYS_GRIP_UP;
	}
	break;
	case ID_KEY_DOWN:
	{
		if (keySrc == ID_DECK) return SYS_KEY_DOWN;
		if (keySrc == ID_GRIP) return SYS_GRIP_DOWN;
	}
	break;
	case ID_KEY_LEFT:
	{
		if (keySrc == ID_DECK) return SYS_KEY_LEFT;
		if (keySrc == ID_GRIP) return SYS_GRIP_LEFT;
	}
	break;
	case ID_KEY_RIGHT:
	{
		if (keySrc == ID_DECK) return SYS_KEY_RIGHT;
		if (keySrc == ID_GRIP) return SYS_GRIP_RIGHT;
	}
	return SYS_KEY_RIGHT;
	break;
	case ID_KEY_ENTER:
	{
		if (keySrc == ID_DECK) return SYS_KEY_ENTER;
		if (keySrc == ID_GRIP) return SYS_GRIP_EXECUTE;
	}
	return SYS_KEY_ENTER;
	break;
	case ID_KEY_DIAL_UP:
	{
		if (keySrc == ID_DECK)return SYS_KEY_MNL_RING_PLUS;
		if (keySrc == ID_GRIP)return SYS_GRIP_DIAL_PLUS;
	}
	break;
	case ID_KEY_DIAL_DOWN:
	{
		if (keySrc == ID_DECK)return SYS_KEY_MNL_RING_MINUS;
		if (keySrc == ID_GRIP)return SYS_GRIP_DIAL_MINUS;
	}
	break;
	case ID_KEY_DIAL_FUNC:
	{
		if (keySrc == ID_DECK)return SYS_KEY_CAM_FUNC;
		if (keySrc == ID_GRIP)return SYS_GRIP_DIAL_FUNC;
	}
	break;
	case ID_KEY_EXIT:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK;  return SYS_KEY_CANCEL; }
		if (keySrc == ID_GRIP)return 0;
	}
	break;
	case ID_KEY_MENU:
	{
		if (keySrc == ID_DECK) return SYS_KEY_MENU;
		if (keySrc == ID_GRIP) return SYS_GRIP_MENU;
	}
	break;
	case ID_KEY_HOME:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_HOME; }
		if (keySrc == ID_GRIP) { return 0; }
	}
	break;
	case ID_KEY_MODE:
	{
		if (keySrc == ID_DECK) return SYS_KEY_MODE;
		if (keySrc == ID_GRIP) return 0;
	}
	break;
	case ID_KEY_SHIFT:
	{
		if (keySrc == ID_DECK) return SYS_KEY_SHIFT;
	}
	break;
	case ID_KEY_LOCK_ON:
		return SYS_LOCK_SW_ON;
		break;
	case ID_KEY_LOCK_OFF:
		return SYS_LOCK_SW_OFF;
		break;
	case ID_KEY_USER1:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER1; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER1;
	}
	break;
	case ID_KEY_USER2:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER2; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER2;
	}
	break;
	case ID_KEY_USER3:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER3; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER3;
	}
	break;
	case ID_KEY_USER4:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER4; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER4;
	}
	break;
	case ID_KEY_USER5:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER5; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER5;
	}
	break;
	case ID_KEY_USER6:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER6; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER6;
	}
	break;
	case ID_KEY_USER7:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER7; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER7;
	}
	break;
	case ID_KEY_USER8:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER8; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER8;
	}
	break;
	case ID_KEY_USER9:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_USER9; }
		if (keySrc == ID_GRIP) return SYS_GRIP_USER9;
	}
	break;
	case ID_KEY_DISP_MODE:
	{
		if (keySrc == ID_DECK) { keySrc = ID_DECK2;  return SYS_KEY2_CHECK; }
	}
	break;
	case ID_INVALID:
	default:
		return 0;
		break;
	}
	return 0;
}
