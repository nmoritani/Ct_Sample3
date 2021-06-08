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
	// @brief ConsoleLog����LogCmnd�𔲂��o��
	// @brief �߂�l�Ȃ� : �擾����LogCmnd�̌�
	void logReadAndExtract(void);
	// @brief ���o����LogCmnd���w�肵���������s
	// @brief �߂�l�Ȃ�
	void execCmd();
	// @brief Console��Log��������Cmnd���擾�����s����
	// @brief �߂�l�Ȃ�
	void cslLogPlayerRun();
	// @brief Log�t�@�C������Cmnd�����s����
	// @brief �߂�l�Ȃ�
	void saveLog();
	// @brief ���������߂��A���s����
	// @brief �߂�l�Ȃ�
	void cmndInterpreter(System::String^ _StrdbgCmd);
	// @brief Log�t�@�C����I�����t�@�C������Cmnd�����s
	// @brief �߂�l�Ȃ�
	void readLogAndExec(String^ filePath);
	// @brief DebugPrint����Cmnd�𒊏o����
	bool extractLog(System::String^ str);

	// ���o�����R�}���h���X�g
	cli::array<String^>^ m_strCmdList;
	int m_cntCmd;
};
