#include "CtCmdLine.h"
#include <vector>
#include <sstream>
#include <string>
#include <msclr/marshal.h>
#include "resource.h"

#include "AplParam.h"
#include "CtDbgCmnd.h"
#include "CtWindowIDString.h"

using namespace System::Runtime::InteropServices;
using namespace CtDbgCmndDomain;
using namespace std;

static void CmdLineHelper();

void beginCmdLineHelperThread(DWORD wParam) {
	CmdLineHelper();
	HWND hwnd = (HWND)wParam;
	PostMessage(hwnd, WM_USER_END_THREAD, IDC_CMD_LINE, 0);
	return;
}

void CmdLineHelper() {
	using namespace System;
	ConsoleKeyInfo  cki;
	Console::TreatControlCAsInput = true;

	do
	{
		cki = Console::ReadKey();
		if (cki.Key == ConsoleKey::Tab) Console::WriteLine("Tab");
	} while (cki.Key != ConsoleKey::Escape);
}

void beginCmdLineThread(DWORD wParam) {
	System::Console::Title = "Mode::CmdLine";
	HANDLE       hStdInput;
	// 入力バッファをクリア
	hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(hStdInput);

	// Consoleを前面に出す
	HWND hwnd = GetConsoleWindow();
	SetForegroundWindow(hwnd);

	CtCmdLine cmdL;
	cmdL.actCmdLineMode();

	hwnd = (HWND)wParam;
	PostMessage(hwnd, WM_USER_END_THREAD, IDC_CMD_LINE, 0);
	return;
}


map<string, int> CtCmdLine::m_CmdGrpMap = {
	#include "CtCmdGrpList.def"
};
map<string, int> CtCmdLine::m_CmdIdMap = {
	#include "CtCmdListInfo.def"
};

map<string, int> CtCmdLine::m_CmdParamArgMap{
	#include "CtCmdParamArgList.def"
};
CtCmdLine::CtCmdLine()
{

}
void CtCmdLine::actCmdLineMode() {
	System::String^ str;
	char* delim = " ";

	std::vector<string> elems;
	string item;
	vector<string>::iterator strItr = elems.begin();

	while (1) {
		// init
		str = L"";
		elems.clear();
		item.clear();

		str = System::Console::ReadLine();

		if (str->ToString() == "") continue;

		char* strReadLine = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
		stringstream ss(strReadLine);
		Marshal::FreeHGlobal(System::IntPtr(strReadLine));

		while (getline(ss, item, *delim)) {
			if (!item.empty()) {
				elems.push_back(item);
			}
			else {
				break;
			}
		}
		if (elems[0].at(0) != ':') {
			cout << "Put a '':'' on CmdLiteral Head" << endl;
			continue;
		}
		else {
			// ":"を削除
			elems[0] = elems[0].substr(1, elems[0].size());
			if (elems[0].compare("quit") == 0) {
				// 終了条件
				break;
			}
			else {
				// CmdGrpの検索
				map<string, int>::iterator itr;
				itr = m_CmdGrpMap.find(elems[0]);
				if (itr == m_CmdGrpMap.end()) {
					cout << "Pls put - Command [help] " << endl;
					continue;
				}
				switch (itr->second) {
				case ID_WIND:
				{
					map<string, int>::iterator cmdIdItr;
					cmdIdItr = m_CmdIdMap.find(elems[0]);
					if (cmdIdItr == m_CmdIdMap.end()) {
						cout << "WinTransId: " << elems[0] << " は見つかりませんでした" << endl;
						continue;
					}
					else if (cmdIdItr->second == 0x2F) {
						showCmd_Manual(ID_WIND);
						return;
					}
					UINT winId = InvalidateWinID;
					switch (cmdIdItr->second) {
					case ID_CHANGE:
					case ID_POPUP:
					case ID_SWAP:
						if (elems.size() < 2) {
							cout << "引数オペランドが見つかりませんでした。" << endl;
							continue;
						}
						else {
							winId = CtWindowIDString::getWindowID(elems[1].c_str());
							if (winId == InvalidateWinID) {
								cout << "WindowID: " << elems[1] << " は見つかりませんでした" << endl;
								continue;
							}
						}
						break;
					default:
						winId = DefaultWinID;
						break;
					}
					m_cmdAda.rqCmndWindowTrans(ScreenAll, itr->second, cmdIdItr->second, winId);
				}
				break;
				case ID_APL_EVNT:
				{
					map<string, int>::iterator cmdIdItr;
					cmdIdItr = m_CmdIdMap.find(elems[0]);
					if (cmdIdItr == m_CmdIdMap.end()) {
						cout << "Ct::IF : " << elems[0] << " は見つかりませんでした" << endl;
						continue;
					}
					INT data = atoi(elems[1].c_str());
					m_cmdAda.rqCmndAplEvnt(ScreenAll, itr->second, cmdIdItr->second, data);
				}
				break;
				case ID_REF_INFO:
				{
					map<string, int>::iterator cmdIdItr;
					cmdIdItr = m_CmdIdMap.find(elems[0]);
					if (cmdIdItr == m_CmdIdMap.end()) {
						cout << "RefInfo: " << elems[0] << " は見つかりませんでした" << endl;
						continue;
					}
					m_cmdAda.rqCmndRefInfo(ScreenAll, itr->second, cmdIdItr->second, ID_INVALID);
				}
				break;
				case ID_SYS_KEY:
				{
					map<string, int>::iterator cmdIdItr;
					cmdIdItr = m_CmdIdMap.find(elems[1]);
					if (cmdIdItr == m_CmdIdMap.end()) {
						cout << "KeyEvent: " << elems[1] << " は見つかりませんでした" << endl;
						continue;
					}
					int data = 0;
					if (elems.size() > 2) {
						data = strtol(elems[2].c_str(), NULL, 0);
					}
					m_cmdAda.rqCmndSysKey(ScreenAll, itr->second, ID_DECK, cmdIdItr->second, data);
				}
				break;
				case ID_SYS_TOUCH:
				{
					map<string, int>::iterator cmdIdItr;
					cmdIdItr = m_CmdIdMap.find(elems[1]);
					if (cmdIdItr == m_CmdIdMap.end()) {
						cout << "TouchEvent: " << elems[0] << " は見つかりませんでした" << endl;
						continue;
					}
					int x = 0;
					if (elems.size() > 3) {
						x = strtol(elems[2].c_str(), NULL, 0);
					}
					int y = 0;
					if (elems.size() > 4) {
						y = strtol(elems[3].c_str(), NULL, 0);
					}
					m_cmdAda.rqCmndSysTouch(ScreenAll, itr->second, cmdIdItr->second, x, y);
				}
				break;
				case ID_APL_PARAM:
				{
					map<string, int>::iterator cmdIdItr;
					cmdIdItr = m_CmdIdMap.find(elems[1]);
					/*if (cmdIdItr == m_CmdIdMap.end()) {
						cout << "AplParamEventID : " << elems[1] << " は見つかりませんでした" << endl;
						continue;
					}*/
					map<string, int>::iterator cmdParamIdItr;
					cmdParamIdItr = m_CmdParamArgMap.find(elems[2]);
					/*if (cmdParamIdItr == m_CmdParamArgMap.end()) {
						cout << "AplParamId : " << elems[2] << " は見つかりませんでした" << endl;
						continue;
					}*/
					int paramId = atoi(elems[1].c_str());
					int data = atoi(elems[2].c_str());
					m_cmdAda.rqCmndAplParam(ScreenAll, /*itr->second*/ID_APL_PARAM, /*cmdIdItr->second*/ID_PARAM_NUM, paramId/*cmdParamIdItr->second*/, data);
				}
				break;
				case 0x1E:
				{
					if (elems.size() < 2) {
						continue;
					}

					map<string, int>::iterator cmdIdItr;
					cmdIdItr = m_CmdIdMap.find(elems[1]);
					int data = -1;

					if (cmdIdItr == m_CmdIdMap.end()) {
						cout << "ID : " << elems[1] << " は見つかりませんでした" << endl;
						continue;
					}

					if (elems.size() > 2) {
						data = strtol(elems[2].c_str(), NULL, 0);
					}
					showCmd_OdDebug(itr->second, cmdIdItr->second, data);
				}
				break;
				case 0x1F:// help
					showCmd_Help();
					break;
				default:
					break;
				}
			}
		}
		Sleep(50);
	}

	return;
}
void CtCmdLine::showCmd_Manual(int grpId) {
	cout << ":change "
		<< endl;
}

void CtCmdLine::showCmd_Help() {
	cout <<
		"----------------help-------------\n\
コマンド一覧\n\
コマンドの引数が[Arg]は省略可を意味します。\n\
名前の後にアスタリスク (*) がある場合は,\n\
そのコマンドが無効になっていることを意味します\n\
	\n\
:change\t\tArg\n\
:popup\t\tArg\n\
:return\t\t[Arg]\n\
:close\t\t[Arg]\n\
:swap\t\tArg\n\
:remove\t\t[Arg]\n\
:getcrnt\t[None]\n\
:getroot\t[None]\n\
:evtflt(*)\t[Arg]\n\
:permtrans\t[Arg]\n\
:permdraw\t[Arg]\n\
:outline\t[None]\n\
:putkey\tKeyAct\tKeyCode\n\
:puttouch(*)\tArg\n\
:putparam(*)\tArg\n\
:help\t\t[None]\n\
\n\
終了コマンド\n\
:quit\t\t\n"
<< endl;
}



#ifndef HANDLE
typedef void *HANDLE;
typedef unsigned long DWORD;
typedef unsigned long long DWORDLONG;
typedef unsigned char BYTE;
#endif

#include "wi_task.h"
#include "wi_mail_box.h"
#include "wi_fixed_mempool.h"
#include "wi_variable_mempool.h"

void CtCmdLine::showCmd_OdDebug(int Id, int CmndId, int data)
{
#ifdef WIN32_GUI_SIM
	switch (CmndId) {
	case ID_OD_ALL:
		for (int i = ID_OD_TSK; i < ID_OD_MAX; i++) {
			CmndId = (DbgCmndOdId)i;
			showCmd_OdDebug(Id, CmndId, data);
		}
		break;
	case ID_OD_TSK:
	{
		WITSKSTAT stat;

		CtDebugPrint(CtDbg, "--------------- TSK ---------------\n");
		CtDebugPrint(CtDbg, "TskId Prio Stat       Addr\n");
		for (int i = 0; i < 1000; i++) {
			if (wi_RefarenceTask(i, &stat) == E_OK) {
				CtDebugPrint(CtDbg, "%5d %4d %4d %#10x\n", i, stat.TaskPri, stat.TaskState, stat.TaskAdr);
			}
		}
	}
	break;
	case ID_OD_TBT:
	{
		// 未実装
		// VisualStudioでデバッグ中に並列スタック(ツールバー >> デバッグ >> ウィンドウ >> 並列スタック)を表示することで
		// 各スレッドのバックトレースの表示が可能
	}
	break;
	case ID_OD_TRG:
	{
		// 未実装
	}
	break;
	case ID_OD_MPF:
	{
		WIMPFSTAT stat;
		CtDebugPrint(CtDbg, "--------------- MPF ---------------\n");
		CtDebugPrint(CtDbg, "MpfId     MemBuf  BlockSize   BlockCnt       Free WaitId      Ext\n");
		for (int i = 0; i < 1000; i++) {
			if (wi_RefarenceFixedMemPool(i, &stat) == E_OK) {
				CtDebugPrint(CtDbg, "%5d %#10x %#10x %#10x %#10x %6d %p\n", i, stat.MemBuf, stat.BlockSize, stat.BlockCnt, stat.FreeBlock, stat.WaitId, stat.ExtInfo);
			}
		}
	}
	break;
	case ID_OD_MPL:
	{
		WIMPLSTAT stat;
		CtDebugPrint(CtDbg, "--------------- MPL ---------------\n");
		for (int i = 0; i < 1000; i++) {
			if (wi_RefarenceVarMemPool(i, &stat) == E_OK) {
				CtDebugPrint(CtDbg, "MpfId     MemBuf    MemSize  TotalFree    MaxFree WaitId      Ext\n");
				CtDebugPrint(CtDbg, "%5d %#10x %#10x %#10x %#10x %6d %p\n", i, stat.MemBuf, stat.MemSize, stat.TotalFreeSize, stat.MaxFreeSize, stat.WaitId, stat.ExtInfo);
				wi_RefarenceAllocatedVarMemPool(i);
			}
		}
	}
	break;
	case ID_OD_MBX:
	{
		WIMBXSTAT stat;

		CtDebugPrint(CtDbg, "--------------- MBX ---------------\n");
		CtDebugPrint(CtDbg, "MbxId    NextMsg WaitId      Ext\n");
		for (int i = 0; i < 1000; i++) {
			if (wi_RefarenceMailBox(i, &stat) == E_OK) {
				CtDebugPrint(CtDbg, "%5d %#10x %6d %p\n", i, stat.NextMsg, stat.WaitId, stat.ExtInfo);
			}
		}
	}
	break;
	}
#endif 
}
