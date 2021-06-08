#pragma once
#include "CtObject.h"
#include "Ct.h"
/*
	コミット不要ファイル!!
	各自のローカルで編集すること
	→Templateな処理は後日追加するつもり(OKB)
*/
class CtDbgWindFuncRegister :
	public CtObject
{
public:
	static void windFunc1(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents);
	static void windFunc2(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents);
	static void windFunc3(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents);
	static void windFunc4(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents);
	static void windFuncAll(CtScreenSel screen, CtWindowID id, CtFuncID funcId, CtWindowContents* contents);
	CtDbgWindFuncRegister();
	~CtDbgWindFuncRegister();
};
