#pragma once
#include <map>
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "CtDbgCmndAdapter.h"

extern void beginCmdLineThread(DWORD wParam);
extern void beginCmdLineHelperThread(DWORD wParam);

class CtCmdLine
{
public:
	CtCmdLine();
	void actCmdLineMode();
	void showCmd_Manual(int grpId);
	void showCmd_Help();
	void showCmd_OdDebug(int Id, int CmndId, int data);
	CtDbgCmndAdapter m_cmdAda;
private:
	static std::map<std::string, int> m_CmdGrpMap;
	static std::map<std::string, int> m_CmdIdMap;
	static std::map<std::string, int> m_CmdParamArgMap;
};
