#pragma once
#include <Windows.h>
#include <WinUser.h>

using namespace System;

extern void beginLogPlayThread(DWORD wParam);
extern void beginReadLogThread(LPVOID lpVoid);

typedef ref struct _THREAD_ATTRIBUTE {
	HWND hWnd;
	String^ filePath;
}threadAttribute;

ref class CtLogPlayer
{
public:
	static threadAttribute thrdAtt;
	int CntCmdMax = 1000;
	CtLogPlayer();
	~CtLogPlayer();
	// @brief ConsoleLogからLogCmndを抜き出す
	// @brief 戻り値なし : 取得したLogCmndの個数
	void logReadAndExtract(void);
	// @brief 抽出したLogCmndを指定した個数分実行
	// @brief 戻り値なし
	void execCmd();
	// @brief ConsoleのLog履歴からCmndを取得し実行する
	// @brief 戻り値なし
	void cslLogPlayerRun();
	// @brief LogファイルからCmndを実行する
	// @brief 戻り値なし
	void saveLog();
	// @brief 文言を解釈し、実行する
	// @brief 戻り値なし
	void cmndInterpreter(System::String^ _StrdbgCmd);
	// @brief Logファイルを選択しファイル内のCmndを実行
	// @brief 戻り値なし
	void readLogAndExec(String^ filePath);
	// @brief DebugPrintからCmndを抽出する
	bool extractLog(System::String^ str);

	// 抽出したコマンドリスト
	cli::array<String^>^ m_strCmdList;
	int m_cntCmd;
};
