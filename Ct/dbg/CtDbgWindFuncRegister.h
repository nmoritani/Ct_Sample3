#pragma once
#include "CtObject.h"
#include "Ct.h"
/*
	�R�~�b�g�s�v�t�@�C��!!
	�e���̃��[�J���ŕҏW���邱��
	��Template�ȏ����͌���ǉ��������(OKB)
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
