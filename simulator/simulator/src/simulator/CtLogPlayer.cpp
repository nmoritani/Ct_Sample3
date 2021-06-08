#include "CtLogPlayer.h"
#include "CtDbgCmndAdapter.h"

#include "resource.h"
#include <msclr/marshal.h>
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;
using namespace System;
using namespace CtDbgCmndDomain;

void beginReadLogThread(LPVOID lpVoid) {
	CtLogPlayer logPlay;
	logPlay.readLogAndExec(CtLogPlayer::thrdAtt.filePath);
	PostMessage(CtLogPlayer::thrdAtt.hWnd, WM_USER_END_THREAD, IDC_LOG_PLAY, 0);
	return;
}

void beginLogPlayThread(DWORD wParam) {
	CtLogPlayer logPlay;
	logPlay.cslLogPlayerRun();
	HWND hwnd = (HWND)wParam;
	PostMessage(hwnd, WM_USER_END_THREAD, IDC_LOG_PLAY, 0);
	return;
}

CtLogPlayer::CtLogPlayer()
{
	m_cntCmd = 0;
	m_strCmdList = gcnew cli::array<String^>(CntCmdMax);
}

CtLogPlayer::~CtLogPlayer() {
	m_cntCmd = 0;
}

void CtLogPlayer::logReadAndExtract() {
	HANDLE hStdOutput;
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	TCHAR szBuf[1024];
	COORD coord;
	DWORD dwReadByte;
	m_cntCmd = 0;
	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdOutput, &bufferInfo);

	coord.X = coord.Y = 0;

	for (int i = 0; i < bufferInfo.dwSize.Y; i++) {
		coord.Y = i;
		ReadConsoleOutputCharacter(hStdOutput, szBuf, bufferInfo.dwSize.X, coord, &dwReadByte);
		szBuf[dwReadByte - 1] = '\0';
		if (wcsncmp(szBuf, L"         ", 10) == 0) {
			continue;
		}
		String ^str = gcnew String(szBuf);
		if (extractLog(str)) {
			if (m_cntCmd >= CntCmdMax) {
				break;
			}
			m_cntCmd++;
		}
	}
	return;
}

bool CtLogPlayer::extractLog(System::String^ str) {
	int end = str->LastIndexOf(L"]");
	if (end == -1) return false;

	int start = str->LastIndexOf(L"[", end);
	if (start == -1) return false;

	String ^strDbgId;
	strDbgId = str->Substring(start + 1, end - start - 1);
	// CmdLogか判別
	if (strDbgId->ToString() != L"CtDbgIdCmd") {
		return false;
	}
	else {
		// Cmnd情報抽出
		// [CtDbgIdCmd]削除
		str = str->Remove(start, end);
		// Data部分のみの取出し
		int end = str->LastIndexOf(L")");
		if (end == -1) return 0;

		int start = str->LastIndexOf(L"(", end);
		if (start == -1) return 0;

		String^ strDbgLog = str->Substring(start + 1, end - start - 1);
		// Data形式に正規化
		array<String^>^ rmvStr = { L" ", L"(", L")" };
		for (unsigned int i = 0; i < sizeof(rmvStr) / sizeof(String^); i++) {
			strDbgLog = strDbgLog->Replace(rmvStr[i], L"");
		}
		m_strCmdList[m_cntCmd] = gcnew String(strDbgLog);
		return true;
	}
}

void CtLogPlayer::execCmd() {
	// Cmd実行
	for (int i = 0; i < m_cntCmd; i++) {
		cmndInterpreter(m_strCmdList[i]);
		Sleep(40);
	}
}

void CtLogPlayer::cslLogPlayerRun() {
	logReadAndExtract();
	// ConsoleLog情報のクリア
	Console::Clear();
	execCmd();
}

void CtLogPlayer::saveLog() {
	FILE* outputfile;
	System::String^ dirPath = ".\\saveLog";
	System::String^ fileName = "\\saveLog";
	System::String^ ext = ".txt";

	if (!IO::Directory::Exists(dirPath)) {
		// 出力先dir作成
		System::IO::Directory::CreateDirectory(dirPath);
	}
	else {
		int cnt = 1;
		do {
			if (!IO::File::Exists(dirPath + fileName + cnt.ToString() + ext)) {
				// File名の被りなし
				fileName += cnt.ToString();
				break;
			}
			else {
				cnt++;
			}
		} while (cnt < 999);
	}
	char* strFilePath = (char*)(void*)Marshal::StringToHGlobalAnsi(dirPath + fileName + ext);
	outputfile = fopen(strFilePath, "w");
	Marshal::FreeHGlobal(IntPtr(strFilePath));
	if (outputfile == NULL) {
		Console::WriteLine("cannot open\n");
		return;
	}
	// CmndLineのコマンドをファイルに書き出す
	logReadAndExtract();
	// Cmnd Dump
	for (int i = 0; i < m_cntCmd; i++) {
		char* strCmnd = (char*)(void*)Marshal::StringToHGlobalAnsi(m_strCmdList[i]);
		fputs("[CtDbgIdCmd](", outputfile);
		fprintf(outputfile, strCmnd);
		fputs(")\n", outputfile);
		Marshal::FreeHGlobal(IntPtr(strCmnd));
	}
	fclose(outputfile);
}

void CtLogPlayer::readLogAndExec(String^ filePath) {
	using System::IO::StreamReader;
	StreamReader^ fin;
	try {
		fin = gcnew StreamReader(filePath);
	} catch (Exception^ e) {
		Console::WriteLine("The process failed: " + e->Message);
		return;
	}
	m_cntCmd = 0;
	Console::Clear();

	while (true) {
		String ^ s = fin->ReadLine();
		if (s == nullptr) break;
		if (extractLog(s)) {
			m_cntCmd++;
		}
	}
	fin->Close();
	execCmd();
}

void CtLogPlayer::cmndInterpreter(System::String^ _StrdbgCmd) {

	// Dataの分割
	array<String^>^ pos = _StrdbgCmd->Split(',');
	CtDbgCmndAdapter dbgCmd;

	// CmndGrp取り出し
	int cmndGrp = ID_EVENT_GROUP_MAX;
	if (int::TryParse(pos[1], cmndGrp) == false) return;
	int scrnSel = SCREEN_ALL;
	int::TryParse(pos[0], scrnSel);

	switch (cmndGrp) {
	case ID_WIND:
	{
		int cmndId = ID_INVALID;
		int::TryParse(pos[2], cmndId);

		unsigned int winId = ID_INVALID;
		UINT::TryParse(pos[3], winId);
		dbgCmd.rqCmndWindowTrans(scrnSel, cmndGrp, cmndId, winId);
	}
	break;
	case ID_SYS_KEY:
	{
		UINT keySrc = ID_INVALID;
		UINT::TryParse(pos[2], keySrc);
		UINT keyAct = ID_INVALID;
		UINT::TryParse(pos[3], keyAct);
		USHORT ctKey = ID_INVALID;
		USHORT::TryParse(pos[3], ctKey);
		USHORT data = (CtEventKey::KeyCode)ctKey;
		dbgCmd.rqCmndSysKey(scrnSel, cmndGrp, keySrc, keyAct, data);
	}
	break;
	case ID_SYS_TOUCH:
	{
		int cmndId = ID_INVALID;
		int::TryParse(pos[2], cmndId);

		unsigned short posX = ID_INVALID;
		USHORT::TryParse(pos[3], posX);
		unsigned short posY = ID_INVALID;
		USHORT::TryParse(pos[4], posY);

		dbgCmd.rqCmndSysTouch(scrnSel, cmndGrp, cmndId, posX, posY);
	}
	break;
	case ID_APL_PARAM:
	{
		int cmndId = ID_INVALID;
		int::TryParse(pos[2], cmndId);
		UINT paramId = ID_INVALID;
		UINT::TryParse(pos[3], paramId);
		long long paramVal = ID_INVALID;
		LONGLONG::TryParse(pos[4], paramVal);
		dbgCmd.rqCmndAplParam(scrnSel, cmndGrp, cmndId, paramId, paramVal);
	}
	break;
	case ID_APL_EVNT:
	{
		int cmndId = ID_INVALID;
		int::TryParse(pos[2], cmndId);

		unsigned int data = ID_INVALID;
		UINT::TryParse(pos[3], data);
		dbgCmd.rqCmndAplEvnt(scrnSel, cmndGrp, cmndId, data);
	}
	break;
	case ID_EVENT_GROUP_MAX:
	default:
		return;
		break;
	}
}
