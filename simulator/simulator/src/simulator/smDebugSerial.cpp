/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   smDebugSerial (シミュレーター用なので、シリアルの変わりに出力ウィンドウに出す)
 */

#include "smDebugSerial.h"
#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <windows.h>
#include <tchar.h>

static char s_afile_path[_MAX_PATH];
static char *s_pfile_path = NULL;

static bool create_logfile_name()
{
	TCHAR path[_MAX_PATH];
	TCHAR* ptmp;

	if (NULL != s_pfile_path) {
		return true;
	}

	//シミュレータのexeを置いているパスを取得
	if (!::GetModuleFileName(NULL, path, sizeof(path))) {
		return false;
	}

	//ファイル名を削除してexe置き場のパスを取り出し
	ptmp = _tcsrchr(path, _T('\\')); // \の最後の出現位置を取得
	if (ptmp == NULL) return false;

	//ファイル名を削除してディレクトリパスのみにする
	ptmp = _tcsinc(ptmp);   //一文字進める
	*ptmp = _T('\0');

	//パスにlogファイル名を追加
	wcscat_s(path, _MAX_PATH, _T("log.txt"));

	//TCHAR型配列をchar型配列に変換
	WideCharToMultiByte(CP_ACP, 0, path, -1, s_afile_path, sizeof(s_afile_path), NULL, NULL);

	s_pfile_path = s_afile_path;

	return true;
}


static void writeLogFile(char *msg)
{
	FILE *pFile;
	errno_t error;

	const char *mode = (NULL == s_pfile_path) ? "w" : "a";

	if (!create_logfile_name()) return;

	error = fopen_s(&pFile, s_pfile_path, mode);
	if (0 != error) {
		return;
	}
	fprintf(pFile, msg);
	fclose(pFile);
}

unsigned char smDebugPrintf(int dmyLevel, const char *format, ...)
{
	va_list vl;
	char logdata[256] = {0};

	if (format == NULL) {
		return 1;
	}

	va_start(vl, format);
	_vsnprintf_s(logdata, sizeof(logdata), format, vl);
	va_end(vl);

	OutputDebugStringA(logdata);

	std::cout << logdata;

    writeLogFile(logdata);

	return 0;
}
