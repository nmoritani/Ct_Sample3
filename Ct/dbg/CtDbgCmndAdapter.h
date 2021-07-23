#pragma once
#include "CtObject.h"
#include "CtDbgCmnd.h"
#include "CtMsgDbgCmnd.h"

using namespace  CtDbgCmndDomain;

class CtDbgCmndAdapter :
	public CtObject
{
public:
	typedef struct Cmd {
		int screen;
		int cmdGrp;
		int cmdId;
		int data;
		Cmd() {
			screen = 0;
			cmdGrp = 0;
			cmdId = 0;
			data = 0;
		}
		Cmd(Cmd& _Cmd) {
			screen = _Cmd.screen;
			cmdGrp = _Cmd.cmdGrp;
			cmdId = _Cmd.cmdId;
			data = _Cmd.data;
		}
		Cmd(int& _screen, int& _cmdGrp, int& _cmdId, int& _data) {
			screen = _screen;
			cmdGrp = _cmdGrp;
			cmdId = _cmdId;
			data = _data;
		}
	}Cmd;

	typedef struct CmdKey : Cmd {
		Cmd baseCmd;
		int keySource;
		int keyAct;
		CmdKey(Cmd& _cmd, int& _keySource, int& _keyAct) : Cmd(_cmd){
			keySource = _keySource;
			keyAct = _keyAct;
		}
	}CmdKey;

	typedef struct CmdSys : Cmd {
		Cmd baseCmd;
		int posX;
		int posY;
		CmdSys(Cmd& _cmd, int& _posX, int& _posY) : Cmd(_cmd) {
			posX = _posX;
			posY = _posY;
		}
	}CmdSys;

	typedef struct CmdParam : Cmd {
		Cmd baseCmd;
		int Id;
		CmdParam(Cmd& _cmd, int& _Id) : Cmd(_cmd) {
			Id = _Id;
		}
	}CmdParam;

	CtDbgCmndAdapter();
	~CtDbgCmndAdapter();

	void send_Msg(Cmd _cmd);
	void send_Msg(CmdKey _cmd);
	void send_Msg(CmdSys _cmd);
	void send_Msg(CmdParam _cmd);

	static void Free(CtMsgDbgCmnd* pMsg);
	
	void rqCmndWindowTrans(int screen, int cmndGrp, int cmndId, int cmndData);
	void rqCmndRefInfo(int screen, int cmndGrp, int cmndId, int cmndData);
	void rqCmndShrtCut(int screen, int cmndGrp, int cmndId, int cmndData);
	void rqCmndVarietyFunc(int screen, int cmndGrp, int cmndId, int cmndData);
	void rqCmndAplEvnt(int screen, int cmndGrp, int cmndId, int cmndData);

	void rqCmndSysKey(int screen, int cmndGrp, int keySrc, int keyAct, int cmndData);
	void rqCmndSysTouch(int screen, int cmndGrp, int cmndId, int posX, int posY);
	
	
	void rqCmndAplParam(int screen, int cmndGrp, int cmndId, int paramId, int paramValue);
	void rqCmndCtInit();
	// WinSimuÇ∆ItronÇÃêÿÇËï™ÇØ
	void *operator new(size_t Size) throw();
	void operator delete(void *pObj);
};

