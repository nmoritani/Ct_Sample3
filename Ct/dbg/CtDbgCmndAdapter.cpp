#include <stdlib.h>
#include <string.h>

#include <CtPlatforms.h>

#include "CtWindowID.h"

#include "CtDbgCmndAdapter.h"
#include "CtDbgCmndReceiver.h"

#ifdef WIN32_GUI_SIM
	#include <msclr/gcroot.h>
using namespace System::Runtime::InteropServices;
#endif

CtDbgCmndAdapter::CtDbgCmndAdapter()
{
}

CtDbgCmndAdapter::~CtDbgCmndAdapter()
{
}

void* CtDbgCmndAdapter::operator new(size_t Size) throw()
{
	void *mem = NULL;
#ifndef WIN32_GUI_SIM
	if (syswrap_alloc_memory(ct_mpl, (UINT)Size, &mem) != SYSWRAP_ERR_OK) {
		CtDebugPrint(CtDbg, "!!! allocate error(%dbyte) !!!\n", Size);
		return NULL;
	}
#else
	mem = malloc(Size);
#endif
	//MPLDBG_ADD(mem, Size, CT_MPL_ID);

	return mem;
}

void CtDbgCmndAdapter::operator delete(void* pObj)
{
#ifndef WIN32_GUI_SIM
	SYSWRAP_ERROR er;
	er = syswrap_free_memory(ct_mpl, pObj);
#else
	free(pObj);
	//MPLDBG_DEL(pObj);
#endif
}

void CtDbgCmndAdapter::send_Msg(Cmd _cmd) {
#ifdef WIN32_GUI_SIM
	Cmd* pCmdData = (Cmd*)(void*)Marshal::AllocHGlobal(sizeof(_cmd));
	memcpy(pCmdData, &_cmd, sizeof(Cmd));
	
	CtMsgDbgCmnd* pMsg = (CtMsgDbgCmnd*)(void*)Marshal::AllocHGlobal(sizeof(CtMsgDbgCmnd));
	memset(pMsg, 0, sizeof(pMsg));
	pMsg->setPriority(1);
	pMsg->setData( (int*)pCmdData);
	pMsg->setCmdGrp((int)_cmd.cmdGrp);
	
#else
	Cmd* pCmdData = new Cmd(_cmd);
	CtMsgDbgCmnd* pMsg = new CtMsgDbgCmnd((int*)pCmdData);
#endif

	if (pMsg->sendMsg() != true) {
		operator delete(pMsg);
	}
}

void CtDbgCmndAdapter::send_Msg(CmdKey _cmd) {
#ifdef WIN32_GUI_SIM
	CmdKey* pCmdData = (CmdKey*)(void*)Marshal::AllocHGlobal(sizeof(_cmd));
	memcpy(pCmdData, &_cmd, sizeof(CmdKey));

	CtMsgDbgCmnd* pMsg = (CtMsgDbgCmnd*)(void*)Marshal::AllocHGlobal(sizeof(CtMsgDbgCmnd));
	memset(pMsg, 0, sizeof(pMsg));
	pMsg->setPriority(1);
	pMsg->setData((int*)pCmdData);
	pMsg->setCmdGrp((int)_cmd.cmdGrp);

#else
	Cmd* pCmdData = new Cmd(_cmd);
	CtMsgDbgCmnd* pMsg = new CtMsgDbgCmnd((int*)pCmdData);
#endif

	if (pMsg->sendMsg() != true) {
		operator delete(pMsg);
	}
}

void CtDbgCmndAdapter::send_Msg(CmdSys _cmd) {
#ifdef WIN32_GUI_SIM
	CmdSys* pCmdData = (CmdSys*)(void*)Marshal::AllocHGlobal(sizeof(_cmd));
	memcpy(pCmdData, &_cmd, sizeof(CmdSys));

	CtMsgDbgCmnd* pMsg = (CtMsgDbgCmnd*)(void*)Marshal::AllocHGlobal(sizeof(CtMsgDbgCmnd));
	memset(pMsg, 0, sizeof(pMsg));
	pMsg->setPriority(1);
	pMsg->setData((int*)pCmdData);
	pMsg->setCmdGrp((int)_cmd.cmdGrp);

#else
	Cmd* pCmdData = new Cmd(_cmd);
	CtMsgDbgCmnd* pMsg = new CtMsgDbgCmnd((int*)pCmdData);
#endif

	if (pMsg->sendMsg() != true) {
		operator delete(pMsg);
	}
}

void CtDbgCmndAdapter::send_Msg(CmdParam _cmd) {
#ifdef WIN32_GUI_SIM
	CmdParam* pCmdData = (CmdParam*)(void*)Marshal::AllocHGlobal(sizeof(_cmd));
	memcpy(pCmdData, &_cmd, sizeof(CmdParam));

	CtMsgDbgCmnd* pMsg = (CtMsgDbgCmnd*)(void*)Marshal::AllocHGlobal(sizeof(CtMsgDbgCmnd));
	memset(pMsg, 0, sizeof(pMsg));
	pMsg->setPriority(1);
	pMsg->setData((int*)pCmdData);
	pMsg->setCmdGrp((int)_cmd.cmdGrp);

#else
	Cmd* pCmdData = new Cmd(_cmd);
	CtMsgDbgCmnd* pMsg = new CtMsgDbgCmnd((int*)pCmdData);
#endif

	if (pMsg->sendMsg() != true) {
		operator delete(pMsg);
	}
}
void CtDbgCmndAdapter::Free(CtMsgDbgCmnd* pMsg) {
#ifdef WIN32_GUI_SIM
	Marshal::FreeHGlobal(System::IntPtr(pMsg));
#else
	if (pMsg != NULL) delete pMsg;
#endif
}

void CtDbgCmndAdapter::rqCmndWindowTrans(int screen, int cmndGrp, int cmndId, int cmndData) {
	Cmd _cmd(screen, cmndGrp, cmndId, cmndData);
	send_Msg(_cmd);
}

void CtDbgCmndAdapter::rqCmndRefInfo(int screen, int cmndGrp, int cmndId, int cmndData) {
	Cmd _cmd(screen, cmndGrp, cmndId, cmndData);
	send_Msg(_cmd);
}

void CtDbgCmndAdapter::rqCmndShrtCut(int screen, int cmndGrp, int cmndId, int cmndData) {
	Cmd _cmd( screen, cmndGrp, cmndId, cmndData );
	send_Msg(_cmd);
}

void CtDbgCmndAdapter::rqCmndSysKey(int screen, int cmndGrp, int keySrc, int keyAct, int cmndData) {
	int cmdId = 0;
	Cmd _cmd(screen, cmndGrp, cmdId, cmndData);
	CmdKey _cmdKey( _cmd, keySrc, keyAct);
	send_Msg(_cmdKey);
};

void CtDbgCmndAdapter::rqCmndVarietyFunc(int screen, int cmndGrp, int cmndId, int cmndData) {
	Cmd _cmd(screen, cmndGrp, cmndId, cmndData);
	send_Msg(_cmd);
}

void CtDbgCmndAdapter::rqCmndAplEvnt(int screen, int cmndGrp, int cmndId, int cmndData) {
	Cmd _cmd(screen, cmndGrp, cmndId, cmndData);
	send_Msg(_cmd);
}

void CtDbgCmndAdapter::rqCmndSysTouch(int screen, int cmndGrp, int cmndId, int posX, int posY) {
	int cmndData = 0;
	Cmd _cmd(screen, cmndGrp, cmndId, cmndData);
	CmdSys _cmdSys(_cmd, posX, posY);
	send_Msg(_cmdSys);
}

void CtDbgCmndAdapter::rqCmndAplParam(int screen, int cmndGrp, int cmndId, int paramId, int paramValue) {
	Cmd _cmd(screen, cmndGrp, cmndId, paramValue);
	CmdParam _cmdParam(_cmd, paramId);
	send_Msg(_cmdParam);
}

#include "CtDbgThread.h"
#include "CtMainThread.h"
#include "CtDrawThread.h"

void CtDbgCmndAdapter::rqCmndCtInit() {
#ifdef WIN32_GUI_SIM
	CtDbgThread *pDbg = NULL;
	CtMainThread *pMain = NULL;
	CtDrawThread *pDraw = NULL;

	if ((pDbg = CtDbgThread::getInstance()) != NULL)
		pDbg->startThread();

	if ((pMain = CtMainThread::getInstance()) != NULL)
		pMain->startThread();
#endif
	return;
}
